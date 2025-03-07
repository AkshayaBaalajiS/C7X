/*
* module name       : c7x_xyGradMagBin
*
* module descripton : Computes X/Y Gradients and Orientation
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#include "VXLIB_xyGradMagBin_i8u_o16u_o8u.h"

#ifdef _DISPLAY_PARAMS
#include "paramv.h"
#endif

#define MIN_ERR   (0x7FFFFFFF)
#define MIN_INDEX (0)

#define SE_PARAM_BASE    (0x0000)
#define SE0_PARAM_OFFSET (SE_PARAM_BASE)
#define SE1_PARAM_OFFSET (SE0_PARAM_OFFSET + SE_PARAM_SIZE)
#define SA0_PARAM_OFFSET (SE1_PARAM_OFFSET + SE_PARAM_SIZE)
#define SA1_PARAM_OFFSET (SA0_PARAM_OFFSET + SA_PARAM_SIZE)

#define SIMD_WIDTH_SHIFT       (5) /* 2^5 = 32 16b elements in a 512b vector */
#define SIMD_WIDTH             (1 << SIMD_WIDTH_SHIFT)
#define SIMD_WIDTH_RND         (SIMD_WIDTH >> 1)
#define NUM_SIMD_BLOCKS(width) (((width) >> SIMD_WIDTH_SHIFT) + (((width) - (((width) >> SIMD_WIDTH_SHIFT) << SIMD_WIDTH_SHIFT)) > 0 ? 1 : 0))

/*-----------------------------------------------------------------------------*/
/* Func: VXLIB_xyGradMagBin_i8u_o16u_o8u_init                                  */
/*                                                                             */
/* Args: U16 inCols                                                            */
/*            - width of the input ROI.                                        */
/*       U16 inRows                                                            */
/*            - height of the input ROI.                                       */
/* Return: None                                                                */
/* Desc  : This function sets up streaming engine parameters needed            */
/*         to fetch data for XY gradients computation.                         */
/*-----------------------------------------------------------------------------*/
#pragma CODE_SECTION(VXLIB_xyGradMagBin_i8u_o16u_o8u_init, ".text:optimized");
VXLIB_STATUS VXLIB_xyGradMagBin_i8u_o16u_o8u_init(void *pIn,
                                                   VXLIB_bufParams2D_t *pInParams,
                                                   void *pMag,
                                                   VXLIB_bufParams2D_t *pMagParams,
                                                   void *pBins,
                                                   VXLIB_bufParams2D_t *pBinParams,
                                                   uint32_t *pCosSinTbl,
                                                   int32_t numBins,
                                                   void *pBlock)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#if defined(VXLIB_CHECK_PARAMS) || defined(VXLIB_XYGRADMAGBIN_I8U_O16U_O8U_CHECK_PARAMS)
    status = VXLIB_xyGradMagBin_i8u_o16u_o8u_checkParams(pIn, pInParams, pMag, pMagParams, pBins, pBinParams, pCosSinTbl, numBins, pBlock);
    if( status == VXLIB_SUCCESS )
#endif
    {
        __STRM_TEMPLATE seTemplate;
        __STRM_TEMPLATE saTemplate;

        __SE_FLAGS se0Flags;
        __SE_FLAGS se1Flags;

        __SA_FLAGS sa0Flags;
        __SA_FLAGS sa1Flags;

        __STRM_PARAM_4D se0Param;
        __STRM_PARAM_4D se1Param;

        __STRM_PARAM_3D sa0Param;
        __STRM_PARAM_3D sa1Param;

        int32_t bit_depth_in  = VXLIB_sizeof(pInParams->data_type);
        int32_t bit_depth_mag = VXLIB_sizeof(pMagParams->data_type);
        int32_t bit_depth_bin = VXLIB_sizeof(pBinParams->data_type);

        int32_t stride_in  = pInParams->stride_y  / bit_depth_in;
        int32_t stride_mag = pMagParams->stride_y / bit_depth_mag;
        int32_t stride_bin = pBinParams->stride_y / bit_depth_bin;

        /*-------------------------------------------------------------------------*/
        /* SE 0 is programmed to fetch pixels from the top and bottom pixels.      */
        /* In one read 32 16bit pixels are read from SE0 holding registers.        */
        /*                                                                         */
        /*        SE0 ->  T                                                        */
        /*            L   P   R                                                    */
        /*        SE0 ->  B                                                        */
        /*                                                                         */
        /* ICNT0 = 32 pixels in 16 bit precision along horizontal direction.       */
        /* ICNT1 = 2 x ICNT0 pixel lines.                                          */
        /* ICNT2 = Continue for the rest of the 32 x inRows - 2 pixels.            */
        /* ICNT3 = Kernel runs for 1 32 x inRows block                             */
        /*-------------------------------------------------------------------------*/
        se0Param.ICNT0 = SIMD_WIDTH;
        se0Param.ICNT1 = 2;
        se0Param.ICNT2 = pMagParams->dim_y;
        se0Param.ICNT3 = NUM_SIMD_BLOCKS(pMagParams->dim_x);

        /*-------------------------------------------------------------------------*/
        /* Jumps for SE 0                                                          */
        /* DIM1 - After fetching 32 Top pixels jump to fetch 32 Bot pixels         */
        /* DIM2 - After ICNT1 jump to the next line.                               */
        /* DIM3 - Kernel runs for 1 32 x inRows block                              */
        /*-------------------------------------------------------------------------*/
        se0Param.DIM1  = stride_in * 2;
        se0Param.DIM2  = stride_in;
        se0Param.DIM3  = SIMD_WIDTH;

        se0Flags = __SE_FLAGS_default();

        se0Flags.ELETYPE   = __SE_ELETYPE_8BIT;
        se0Flags.PROMOTE   = __SE_PROMOTE_2X_ZEROEXT;
        se0Flags.VECLEN    = __SE_VECLEN_32ELEMS;

        seTemplate = __SE_SET_PARAM_4D(&se0Param, &se0Flags);
        *stov_ptr(uint16, (uint32_t *)((uint8_t *)pBlock + SE0_PARAM_OFFSET)) = seTemplate;

        /*-------------------------------------------------------------------------*/
        /* SE 1 is programmed to fetch pixels from left and right of each pixel.   */
        /* In one read 32 16bit pixels are read from SE1 holding registers.        */
        /*                                                                         */
        /*                T                                                        */
        /*     SE1 -> L   P   R  <- SE1                                            */
        /*                B                                                        */
        /*                                                                         */
        /* ICNT0 = 32 pixels in 16 bit precision along horizontal direction.       */
        /* ICNT1 = 2 x ICNT0 pixel lines.                                          */
        /* ICNT2 = Continue for the rest of the 32 x inRows - 2 pixels.            */
        /* ICNT3 = Kernel runs for 1 32 x inRows block                             */
        /*-------------------------------------------------------------------------*/
        se1Param.ICNT0 = SIMD_WIDTH;
        se1Param.ICNT1 = 2;
        se1Param.ICNT2 = pMagParams->dim_y;
        se1Param.ICNT3 = NUM_SIMD_BLOCKS(pMagParams->dim_x);

        /*-------------------------------------------------------------------------*/
        /* Jumps for SE 1                                                          */
        /* DIM1 - After fetching 32 Bottom pixels jump back to previous row        */
        /*        1 - inCols to fetch Right Pixels. The jump here is negative.     */
        /* DIM2 - After ICNT1 jump to the next line.                               */
        /* DIM3 - Kernel runs for 1 32 x inRows block                              */
        /*-------------------------------------------------------------------------*/
        se1Param.DIM1 = 2;
        se1Param.DIM2 = stride_in;
        se1Param.DIM3 = SIMD_WIDTH;

        se1Flags = __SE_FLAGS_default();

        se1Flags.ELETYPE   = __SE_ELETYPE_8BIT;
        se1Flags.PROMOTE   = __SE_PROMOTE_2X_ZEROEXT;
        se1Flags.VECLEN    = __SE_VECLEN_32ELEMS;

        seTemplate = __SE_SET_PARAM_4D(&se1Param, &se1Flags);
        *stov_ptr(uint16, (uint32_t *)((uint8_t *)pBlock + SE1_PARAM_OFFSET)) = seTemplate;

        /* Prepare SA 0 tempate to store output */
        sa0Flags = __SA_FLAGS_default();
        sa0Flags.DECDIM1  = __SA_DECDIM_DIM2;
        sa0Flags.VECLEN   = __SA_VECLEN_32ELEMS;

        /* ITERATION COUNTERS */
        sa0Param.DECDIM1_WIDTH = pBinParams->dim_x;
        sa0Param.ICNT0 = SIMD_WIDTH;
        sa0Param.ICNT1 = pBinParams->dim_y;
        sa0Param.ICNT2 = NUM_SIMD_BLOCKS(pBinParams->dim_x);

        /* DIMENSIONS */
        sa0Param.DIM1  = stride_bin;
        sa0Param.DIM2  = SIMD_WIDTH;

        saTemplate = __SA_SET_PARAM_3D(&sa0Param, &sa0Flags);
        *stov_ptr(uint16, (uint32_t *)((uint8_t *)pBlock + SA0_PARAM_OFFSET)) = saTemplate;

        /* Prepare SA 1 tempate to store output */
        sa1Flags = __SA_FLAGS_default();
        sa1Flags.DECDIM1  = __SA_DECDIM_DIM2;
        sa1Flags.VECLEN   = __SA_VECLEN_32ELEMS;

        /* ITERATION COUNTERS */
        sa1Param.DECDIM1_WIDTH = pMagParams->dim_x;
        sa1Param.ICNT0 = SIMD_WIDTH;
        sa1Param.ICNT1 = pMagParams->dim_y;
        sa1Param.ICNT2 = NUM_SIMD_BLOCKS(pMagParams->dim_x);

        /* DIMENSIONS */
        sa1Param.DIM1  = stride_mag;
        sa1Param.DIM2  = SIMD_WIDTH;

        saTemplate = __SA_SET_PARAM_3D(&sa1Param, &sa1Flags);
        *stov_ptr(uint16, (uint32_t *)((uint8_t *)pBlock + SA1_PARAM_OFFSET)) = saTemplate;
    }
       return (status);
}

/*-----------------------------------------------------------------------------*/
/* Func: VXLIB_xyGradMagBin_i8u_o16u_o8u_kernel                                */
/*                                                                             */
/* Args: U16 inCols                                                            */
/*            - width of the input ROI.                                        */
/*       U16 inRows                                                            */
/*            - height of the input ROI.                                       */
/*       U08 * pIn                                                             */
/*            - input pointer to buffer of 8-bit data.                         */
/*       U16 * pOut                                                            */
/*            - output pointer to buffer of 16-bit data.                       */
/*       S16 * pGradX                                                          */
/*            - output pointer to buffer of 16-bit data.                       */
/*       S16 * pGradY                                                          */
/*            - output pointer to buffer of 16-bit data.                       */
/* Return: None                                                                */
/*                                                                             */
/* Desc  : In this function, the stream buffer fetch data in a zig zag         */
/*         manner such that both vertical and horizontal gradient can be       */
/*         computed using SIMD subtraction. The input 8-bit data is promoted   */
/*         to 16-bit data. This results in 32 way SIMD by using double vector  */
/*         operations. The kernel works on 32x32 block providing X gradient,   */
/*         Y gradient and Magnitude of X and Y gradients.                      */
/*-----------------------------------------------------------------------------*/
#pragma CODE_SECTION(VXLIB_xyGradMagBin_i8u_o16u_o8u_kernel, ".text:optimized");
VXLIB_STATUS VXLIB_xyGradMagBin_i8u_o16u_o8u_kernel(void *pIn,
                                                    VXLIB_bufParams2D_t *pInParams,
                                                    void *pMag,
                                                    VXLIB_bufParams2D_t *pMagParams,
                                                    void *pBins,
                                                    VXLIB_bufParams2D_t *pBinParams,
                                                    uint32_t *pCosSinTbl,
                                                    int32_t numBins,
                                                    void *pBlock)
{

    VXLIB_STATUS    status = VXLIB_SUCCESS;

#if defined(VXLIB_CHECK_PARAMS) || defined(VXLIB_XYGRADMAGBIN_I8U_O16U_O8U_CHECK_PARAMS)
    status = VXLIB_xyGradMagBin_i8u_o16u_o8u_checkParams(pIn, pInParams, pMag, pMagParams, pBins, pBinParams, pCosSinTbl, numBins, pBlock);
    if( status == VXLIB_SUCCESS )
#endif
    {
        uint16 seTemplate;
        uint16 saTemplate;

        int32_t k, ctr, blkX;
        int32_t numBlocks, numRows, numItr;

        int32_t bit_depth_in  = VXLIB_sizeof(pInParams->data_type);
        int32_t bit_depth_mag = VXLIB_sizeof(pMagParams->data_type);
        int32_t bit_depth_bin = VXLIB_sizeof(pBinParams->data_type);

        int32_t stride_in  = pInParams->stride_y  / bit_depth_in;
        __vpred vpStore;

        /*-------------------------------------------------------------------------*/
        /* Permute configuration for a short interleaving                          */
        /*-------------------------------------------------------------------------*/
        ulong8 vIntlvPattern;
        vIntlvPattern.s0 = 0x2322030221200100;
        vIntlvPattern.s1 = 0x2726070625240504;
        vIntlvPattern.s2 = 0x2b2a0b0a29280908;
        vIntlvPattern.s3 = 0x2f2e0f0e2d2c0d0c;
        vIntlvPattern.s4 = 0x3332131231301110;
        vIntlvPattern.s5 = 0x3736171635341514;
        vIntlvPattern.s6 = 0x3b3a1b1a39381918;
        vIntlvPattern.s7 = 0x3f3e1f1e3d3c1d1c;

        seTemplate = *stov_ptr(uint16, (uint32_t *)((uint8_t *)pBlock + SE0_PARAM_OFFSET));
        __SE0_OPEN((void *)((uint8_t *)pIn + 1), seTemplate);

#ifdef _DISPLAY_PARAMS
        displaySEParam((void *)((uint8_t *)pIn + 1), seTemplate, PARAMV_SE0);
#endif

        seTemplate = *stov_ptr(uint16, (uint32_t *)((uint8_t *)pBlock + SE1_PARAM_OFFSET));
        __SE1_OPEN((void *)((uint8_t *)pIn + stride_in), seTemplate);

#ifdef _DISPLAY_PARAMS
        displaySEParam((void *)((uint8_t *)pIn + stride_in), seTemplate, PARAMV_SE1);
#endif

        saTemplate = *stov_ptr(uint16, (uint32_t *)((uint8_t *)pBlock + SA0_PARAM_OFFSET));
        __SA0_OPEN(saTemplate);

#ifdef _DISPLAY_PARAMS
        displaySAParam((void *)pBins, saTemplate, PARAMV_SA0);
#endif

        saTemplate = *stov_ptr(uint16, (uint32_t *)((uint8_t *)pBlock + SA1_PARAM_OFFSET));
        __SA1_OPEN(saTemplate);

#ifdef _DISPLAY_PARAMS
        displaySAParam((void *)pMag, saTemplate, PARAMV_SA1);
#endif

        numBlocks = NUM_SIMD_BLOCKS(pMagParams->dim_x);
        numRows   = pMagParams->dim_y;
        numItr    = numRows >> 1;

#pragma MUST_ITERATE(1,,)
        for(blkX = 0; blkX < numBlocks; blkX++)
        {
            /*-------------------------------------------------------------------------*/
            /* Iterate for input inRows - 2 number of times as the first and last row  */
            /* of the output image is always 0.                                        */
            /*-------------------------------------------------------------------------*/
#pragma MUST_ITERATE(1,,)
            for(ctr = 0; ctr < numItr; ctr++)
            {
                 /*--------------------------------------------------------------------*/
                 /* Compute VECTOR SIMD sub of 32 values,(N+1) - (N-1), bot - top      */
                 /* Compute VECTOR SIMD sub of 32 values,(N+1) - (N-1), right - left   */
                 /*--------------------------------------------------------------------*/

                 short32 vTop  = __SE0ADV(short32);
                 short32 vLeft = __SE1ADV(short32);

                 short32 vGy  = __SE0ADV(short32) - vTop;
                 short32 vGx  = __SE1ADV(short32) - vLeft;

                 short32 vTopb  = __SE0ADV(short32);
                 short32 vLeftb = __SE1ADV(short32);

                 short32 vGyb  = __SE0ADV(short32) - vTopb;
                 short32 vGxb  = __SE1ADV(short32) - vLeftb;

                 /*--------------------------------------------------------------------*/
                 /* Compute the orientation bin                                        */
                 /*--------------------------------------------------------------------*/
                 int16 vMinErr0 = (int16)MIN_ERR;
                 int16 vMinErr1 = (int16)MIN_ERR;
                 int16 vMinIdx0 = (int16)MIN_INDEX;
                 int16 vMinIdx1 = (int16)MIN_INDEX;

                 int16 vMinErr0b = (int16)MIN_ERR;
                 int16 vMinErr1b = (int16)MIN_ERR;
                 int16 vMinIdx0b = (int16)MIN_INDEX;
                 int16 vMinIdx1b = (int16)MIN_INDEX;

                 /*--------------------------------------------------------------------*/
                 /* Interleaved vGx and vGy                                            */
                 /*--------------------------------------------------------------------*/
                 short32 vGe = __as_short32(__permute_low_low(__as_uchar64(vIntlvPattern), __as_uchar64(vGy), __as_uchar64(vGx)));
                 short32 vGo = __as_short32(__permute_high_high(__as_uchar64(vIntlvPattern), __as_uchar64(vGy), __as_uchar64(vGx)));

                 short32 vGeb = __as_short32(__permute_low_low(__as_uchar64(vIntlvPattern), __as_uchar64(vGyb), __as_uchar64(vGxb)));
                 short32 vGob = __as_short32(__permute_high_high(__as_uchar64(vIntlvPattern), __as_uchar64(vGyb), __as_uchar64(vGxb)));

                 int16 vBin = (int16)0;

#pragma MUST_ITERATE(1,,)
                 for(k = 0; k < numBins; k++)
                 {
                    __vpred vpMask0, vpMask1, vpMask0b, vpMask1b;

                    /*----------------------------------------------------------------*/
                    /* Load and duplicate sin and cos values, negate sin              */
                    /*----------------------------------------------------------------*/
                    short32 vCosSin = __as_short32(__vload_dup((pCosSinTbl + k)));

                    /*-----------------------------------------------------------------*/
                    /* Compute dot product, take absolute value                        */
                    /*-----------------------------------------------------------------*/
                    int16 vCurrErr0 = __abs(__dotp2(vGe, vCosSin));
                    int16 vCurrErr1 = __abs(__dotp2(vGo, vCosSin));

                    int16 vCurrErr0b = __abs(__dotp2(vGeb, vCosSin));
                    int16 vCurrErr1b = __abs(__dotp2(vGob, vCosSin));

                    /*-----------------------------------------------------------------*/
                    /* Keep track of the index of the maximum                          */
                    /* if(err > currErr) {                                             */
                    /*  err = currErr;                                                 */
                    /*  idx = k;                                                       */
                    /* }                                                               */
                    /*-----------------------------------------------------------------*/
                    __min_index(vCurrErr0, vMinErr0, vpMask0);
                    __min_index(vCurrErr1, vMinErr1, vpMask1);

                    __min_index(vCurrErr0b, vMinErr0b, vpMask0b);
                    __min_index(vCurrErr1b, vMinErr1b, vpMask1b);

                    /* Another approach is to use a two int16 index vectors and to pack
                       them in the end. */
                    vMinIdx0 = __select(vpMask0, vBin, vMinIdx0);
                    vMinIdx1 = __select(vpMask1, vBin, vMinIdx1);

                    vMinIdx0b = __select(vpMask0b, vBin, vMinIdx0b);
                    vMinIdx1b = __select(vpMask1b, vBin, vMinIdx1b);
                    vBin += (int16)1;
                }
                // pack vMinIdx0 and vMinIdx1
                short32 vOutBin  = __pack_consec_low_short(__as_short32(vMinIdx1), __as_short32(vMinIdx0));
                short32 vOutBinb = __pack_consec_low_short(__as_short32(vMinIdx1b), __as_short32(vMinIdx0b));

                /*--------------------------------------------------------------------*/
                /* Select the bin (with correct handle about out of range             */
                /*                                                                    */
                /* if(vGy == 0 && vGx < 0) {                                          */
                /*     outBin[(icount-1) *(pitch-2) + (jcount-1)] = numBins-1;        */
                /* }                                                                  */
                /* else {                                                             */
                /*     outBin[(icount-1)*(pitch-2) + (jcount-1)] = idx;               */
                /* }                                                                  */
                /*--------------------------------------------------------------------*/
                __vpred pred2 = __cmp_eq_pred(vGy, (short32)0);
                __vpred pred3 = __cmp_gt_pred((short32)0, vGx);
                __vpred pred4 = __and_ppp(pred2, pred3);
                vOutBin = __select(pred4, (short32)(numBins-1), vOutBin);

                pred2 = __cmp_eq_pred(vGyb, (short32)0);
                pred3 = __cmp_gt_pred( (short32)0, vGxb);
                pred4 = __and_ppp(pred2, pred3);
                vOutBinb = __select(pred4, (short32)(numBins-1), vOutBinb);

                /*--------------------------------------------------------------------*/
                /* Store the 32 unsigned 8bit bins.                                   */
                /*--------------------------------------------------------------------*/
                vpStore = __SA0_VPRED(ushort32);
                __vstore_pred_packl(vpStore, __SA0ADV(uchar32, pBins), __as_ushort32(vOutBin));
                vpStore = __SA0_VPRED(ushort32);
                __vstore_pred_packl(vpStore, __SA0ADV(uchar32, pBins), __as_ushort32(vOutBinb));

                /*--------------------------------------------------------------------*/
                /* SIMD add the absolute values of X/Y gradients to get the result.   */
                /*--------------------------------------------------------------------*/
                short32 vMag  = __abs(vGx)  + __abs(vGy);
                short32 vMagb = __abs(vGxb) + __abs(vGyb);

                /*--------------------------------------------------------------------*/
                /* Store the 32 16bit result in pOut array.                           */
                /*--------------------------------------------------------------------*/
                vpStore = __SA1_VPRED(short32);
                __vstore_pred(vpStore, __SA1ADV(short32, pMag), vMag);
                vpStore = __SA1_VPRED(short32);
                __vstore_pred(vpStore, __SA1ADV(short32, pMag), vMagb);
            }
        }
        /*-------------------------------------------------------------------------*/
        /* Close the stream buffer after usage.                                    */
        /*-------------------------------------------------------------------------*/
        __SA1_CLOSE();
        __SA0_CLOSE();

        __SE1_CLOSE();
        __SE0_CLOSE();
    }

    return (status);
}

#pragma CODE_SECTION(VXLIB_xyGradMagBin_i8u_o16u_o8u_checkParams, ".text:optimized");
VXLIB_STATUS VXLIB_xyGradMagBin_i8u_o16u_o8u_checkParams(void *pIn,
                                                     VXLIB_bufParams2D_t *pInParams,
                                                     void *pMag,
                                                     VXLIB_bufParams2D_t *pMagParams,
                                                     void *pBins,
                                                     VXLIB_bufParams2D_t *pBinParams,
                                                     uint32_t *pCosSinTbl,
                                                     int32_t numBins,
                                                     void *pBlock)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

    return (status);

}
