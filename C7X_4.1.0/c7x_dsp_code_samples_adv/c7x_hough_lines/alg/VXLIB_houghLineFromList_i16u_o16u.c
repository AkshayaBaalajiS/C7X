/*
* module name       : c7x_hough_lines
*
* module descripton : Computes Hough Lines
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#include "VXLIB_houghLineFromList_i16u_o16u.h"
#ifndef _HOST_EMULATION
#include "c7x_luthist.h"
#else
#include "lut.h"
#endif

#ifdef _DISPLAY_PARAMS
#include "paramv.h"
#endif

#define MIN(a,b) ((a)<(b) ? (a) : (b))

#define SIMD_WIDTH_SHIFT       (5) /* 2^5 = 32x16b elements in a 512b vector */
#define HALF_SIMD_WIDTH_SHIFT  (4) /* 2^5 = 32x16b elements in a 512b vector */
#define SIMD_WIDTH             (1 << SIMD_WIDTH_SHIFT)
#define HALF_SIMD_WIDTH        (1 << HALF_SIMD_WIDTH_SHIFT)
#define SIMD_WIDTH_RND         (SIMD_WIDTH >> 1)
#define ALIGN_SIMD_WIDTH(a)    (((a) + SIMD_WIDTH-1) & ~(SIMD_WIDTH-1))
#define ALIGN_HALF_SIMD_WIDTH(a) (((a) + (SIMD_WIDTH>>1)-1) & ~((SIMD_WIDTH>>1)-1))
#define DIVIDE_RNDUP_SIMD_WIDTH(a)   (((a) + SIMD_WIDTH-1)>>SIMD_WIDTH_SHIFT)
#define DIVIDE_SIMD_WIDTH(a)         ((a)>>SIMD_WIDTH_SHIFT)
#define NUM_SIMD_BLOCKS(width) (((width) + (SIMD_WIDTH - 1)) >> SIMD_WIDTH_SHIFT)
#define NUM_HALF_SIMD_BLOCKS(width) (((width) + (SIMD_WIDTH - 2)) >> HALF_SIMD_WIDTH_SHIFT)


#define SE_PARAM_BASE (0x0000)

#define SE0_PARAM_OFFSET (SE_PARAM_BASE)

/*******************************************************************
   KERNEL INITIALIZTION
********************************************************************/
VXLIB_STATUS VXLIB_houghLineFromList_i16u_o16u_init
(
    uint16_t * restrict pEdgeMapList,
    uint16_t * restrict pOutHoughSpace,
    uint16_t outBlkWidth,
    uint16_t outBlkHeight,
    uint32_t listSize,
    uint16_t thetaRange,
    uint16_t rhoMaxLength,
    const int16_t *pSIN,
    const int16_t *pCOS,
    void *pBlock
)
{
    VXLIB_STATUS status = VXLIB_SUCCESS;

    __STRM_TEMPLATE seTemplate;
    __SE_FLAGS seFlags;
    __STRM_PARAM_3D seParam;
    __sLTCRFlags_t lutflags;
    int32_t tableSize, numParallelTable;

    /*Setting up Stream buffer0      */

    seParam.ICNT0 = 2*ALIGN_HALF_SIMD_WIDTH(listSize);
    seParam.ICNT1 = 1;
    seParam.ICNT2 = 1;

    seParam.DIM1  = 0;
    seParam.DIM2  = 0;

    seFlags = __SE_FLAGS_default();

    seFlags.ELETYPE   = __SE_ELETYPE_16BIT;
    seFlags.VECLEN    = __SE_VECLEN_32ELEMS;

    seTemplate = __SE_SET_PARAM_3D(&seParam, &seFlags);
    *stov_ptr(uint16, (uint32_t *)((uint8_t*)pBlock + SE0_PARAM_OFFSET)) = seTemplate;

    /*------------------------------------------------------------------------*/
    /* Enable LUT/HIST feature by setting TSR register.                       */
    /*------------------------------------------------------------------------*/
    __LUT_SET_LTER(__LUT_ENABLE_0);
    __LUT_SET_LTER(__LUT_ENABLE_1);

    /*------------------------------------------------------------------------*/
    /* Setup base address for 1st and 2nd overlapping table.                  */
    /*------------------------------------------------------------------------*/
    __LUT_SET_LTBR(__LUT_SET0, 0x0000);
    __LUT_SET_LTBR(__LUT_SET1, 0x0000);

    /* Calculate number of parallel tables */
    tableSize= (rhoMaxLength+1)*2; /* Size in bytes, also we need to take into account an extra dummy bin #rhoMaxLength */
    numParallelTable= (32*1024)/tableSize;
    if (numParallelTable >= 16) {
        lutflags.NUMTBLS       = __LUT_NUM_TBL_16;
    }
    else if (numParallelTable >= 8) {
        lutflags.NUMTBLS       = __LUT_NUM_TBL_8;
        }
    else if (numParallelTable >= 4) {
        lutflags.NUMTBLS       = __LUT_NUM_TBL_4;
        }
    else if (numParallelTable >= 2) {
        lutflags.NUMTBLS       = __LUT_NUM_TBL_2;
        }
    else if (numParallelTable >= 1){
        lutflags.NUMTBLS       = __LUT_NUM_TBL_1;
        }
    else {
        status = VXLIB_ERR_INVALID_VALUE;
        goto Exit;
        }

    /*------------------------------------------------------------------------*/
    /* Setup configuration parameters for 1st table. (Histogram write)        */
    /*------------------------------------------------------------------------*/
    lutflags.INTERPOLATION = __LUT_INTERP_OFF;
    lutflags.SATURATION    = __LUT_SAT_OFF;
    lutflags.SIGNUNSIGN    = __LUT_UNSIGNED;
    lutflags.ELETYPE       = __LUT_ELETYPE_16BIT;
    lutflags.TBLSIZE       = __LUT_TBL_SIZE_32KBYTES;
    lutflags.WEIGHTSIZE    = __LUT_WSIZE_8BIT;
    lutflags.PROMOTION     = __LUT_PROMOTE_OFF;

    /*------------------------------------------------------------------------*/
    /* Write the configuration to LTCR0 register, indicated by VLIB_LUT_SET0  */
    /*------------------------------------------------------------------------*/
    __LUT_SET_LTCR(__LUT_SET0, __lut_set_param(&lutflags));

    /*------------------------------------------------------------------------*/
    /* Setup configuration parameters for 1st table.                          */
    /*------------------------------------------------------------------------*/
    lutflags.ELETYPE       = __LUT_ELETYPE_16BIT;
    lutflags.PROMOTION     = __LUT_PROMOTE_2X;

    /*------------------------------------------------------------------------*/
    /* Write the configuration to LTCR0 register, indicated by VLIB_LUT_SET1  */
    /*------------------------------------------------------------------------*/
    __LUT_SET_LTCR(__LUT_SET1, __lut_set_param(&lutflags));


Exit:
    return status;
}


VXLIB_STATUS VXLIB_houghLineFromList_i16u_o16u_kernel(uint16_t * restrict pEdgeMapList,
                             uint16_t * restrict pOutHoughSpace,
                             uint16_t outBlkWidth,
                             uint16_t outBlkHeight,
                             uint32_t listSize,
                             uint16_t thetaRange,
                             uint16_t rhoMaxLength,
                             const int16_t *pSIN,
                             const int16_t *pCOS,
                             void *pBlock
                             )
{
    int32_t i;
    int32_t sinCos;
    int32_t theta;
    int32_t normLength, diameterNormLength;
    int32_t loopCnt1, loopCnt2;

    int16       vNormLength;
    short32     vSinCos;
    short32      vYX;
    int16       vYsinXcos;
    int16       vYsinXcosNormLength;
    uint16      vRo, vRhoMax;
    int16       vDiameterNormLength;

    VXLIB_STATUS    status = VXLIB_SUCCESS;

    /*Loading SE Param from L1D SRAM*/
   __STRM_TEMPLATE vSETemplate = *stov_ptr(uint16, (uint32_t *)((uint8_t*)pBlock + SE0_PARAM_OFFSET));

#ifdef _DISPLAY_PARAMS
        displaySEParam((void *)pEdgeMapList, vSETemplate, PARAMV_SE0);
#endif

    /* Diameter of Hough Space (actually max abs value of r)*/
    int32_t diameter = SQRTof2_Q8 * __max(outBlkWidth, outBlkHeight);

    float f_diameter = __int_to_float(diameter);
    float f_normLength = __int_to_float(rhoMaxLength<<15);
    float r_diameter = __recip(f_diameter);

    f_normLength = f_normLength * r_diameter;
    normLength= __float_to_int(f_normLength-(float)0.5);//-0.5 as integer is truncated not rounded
    diameterNormLength = diameter*normLength + 32768;

    vNormLength = (int16) (normLength);
    vDiameterNormLength = (int16) (diameterNormLength);

    vRhoMax = (uint16)(rhoMaxLength);

    loopCnt1 = thetaRange;
    loopCnt2 = rhoMaxLength;

#pragma MUST_ITERATE(1,,)
    for (theta=0; theta < loopCnt1; theta++){

#pragma MUST_ITERATE(1,,)
        //Initialize LUT set 0
        for(i = 0; i < loopCnt2; i+=4) {
            __lookup_init(__LUT_SET0, (ushort32)(0), (uint)(i));
        }

        /* Opening up Stream buffer0*/
        __SE0_OPEN((void*)pEdgeMapList, vSETemplate);

        /* Merging Sin(Q) and Cosine(Q) into a variable, useful for dot product format */
        sinCos     = ((pSIN[theta]<<16)| pCOS[theta]);
        /* scaler to Vector*/
        vSinCos = __as_short32(__duplicate(sinCos));

        loopCnt1 = (listSize>>HALF_SIMD_WIDTH_SHIFT);
#pragma MUST_ITERATE(1,,)
        for (i=0; i < loopCnt1; i++){
            vYX= __SE0ADV(short32);
            vYsinXcos = __dotp2(vYX,vSinCos);

            /* rho1 = (uint16_t) ( ( r1*normLength + s ) >> 16); */
            vYsinXcosNormLength = vYsinXcos * vNormLength;

            /* Hist table address */
            vRo = __as_uint16(vDiameterNormLength + vYsinXcosNormLength);
            vRo = vRo >> 16;

            /* Hist update */
            __hist(__LUT_SET0,vRo );
        }

        /* If listSize was not multiple of 16, take care of the leftovers */
        int32_t numElementsComputed= (listSize>>HALF_SIMD_WIDTH_SHIFT)<<HALF_SIMD_WIDTH_SHIFT;
        if (numElementsComputed != listSize) {
            vYX= __SE0ADV(short32);
            vYsinXcos = __dotp2(vYX,vSinCos);

            /* rho1 = (uint16_t) ( ( r1*normLength + s ) >> 16); */
            vYsinXcosNormLength = vYsinXcos * vNormLength;

            /* Hist table address */
            vRo = __as_uint16(vDiameterNormLength + vYsinXcosNormLength);
            vRo = vRo >> 16;

            /* Modify the last elements so they map to the dummy bin #rhoMaxLength*/
            __vpred validFlag = __mask_int(listSize - numElementsComputed);
            vRo= __select(validFlag, vRo, vRhoMax);

            __hist(__LUT_SET0,vRo);
        }

        __SE0_CLOSE();

        /* merge histograms */
        uint16_t *restrict hpOutHoughSpace = (uint16_t*)&pOutHoughSpace[rhoMaxLength*theta];
        uint16 v_i = (uint16)0;

        loopCnt1 = rhoMaxLength;

#pragma MUST_ITERATE(1,,)
        for (i=0; i < loopCnt1; i++){
            /* Hist table Read */
            uint16    v_outData = __lookup_read_uint(__LUT_SET1, v_i);
            /* merge 16 histogram: parallel horizontal add */
            ulong  merge_data = __horizontal_add(v_outData);
            /* update hough space with merge data */
            *hpOutHoughSpace++ = (uint16_t)merge_data;
            v_i = v_i + 1;
        }
    }
    return status;
}

/* ======================================================================== */
/*  End of file:  VXLIB_houghLineFromList.c                                  */
/* ======================================================================== */
