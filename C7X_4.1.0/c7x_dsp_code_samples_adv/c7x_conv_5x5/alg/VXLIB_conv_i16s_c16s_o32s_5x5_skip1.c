/*
* module name       : c7x_conv_5x5
*
* module descripton : 5x5 convolution
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#include "VXLIB_conv_i16s_c16s_o32s_5x5_skip1.h"

#ifdef _DISPLAY_PARAMS
#include "paramv.h"
#endif

#define SE_PARAM_BASE      (0x0000)
#define SE_PARAM_OFFSET    (SE_PARAM_BASE)
#define SA0_PARAM_OFFSET   (SE_PARAM_OFFSET  + SE_PARAM_SIZE)
#define SA1_PARAM_OFFSET   (SA0_PARAM_OFFSET + SA_PARAM_SIZE)
#define SA2_PARAM_OFFSET   (SA1_PARAM_OFFSET + SA_PARAM_SIZE)

#define MASK0_PARAM_OFFSET (SA2_PARAM_OFFSET + SA_PARAM_SIZE)
#define MASK1_PARAM_OFFSET (MASK0_PARAM_OFFSET + SA_PARAM_SIZE)

#define INP_SIMD_WIDTH_SHIFT       (5) /* 2^5 = 32 16b elements in a 512b vector */
#define INP_SIMD_WIDTH             (1 << INP_SIMD_WIDTH_SHIFT)
#define INP_SIMD_WIDTH_RND         (INP_SIMD_WIDTH >> 1)
#define NUM_INP_SIMD_BLOCKS(width) (((width) >> INP_SIMD_WIDTH_SHIFT) + (((width) - (((width) >> INP_SIMD_WIDTH_SHIFT) << INP_SIMD_WIDTH_SHIFT)) > 0 ? 1 : 0))

VXLIB_STATUS VXLIB_conv_i16s_c16s_o32s_5x5_skip1_init
(
    int16_t *src,
    VXLIB_bufParams3D_t *src_addr,
    int16_t *weights,
    VXLIB_bufParams3D_t *wgt_addr,
    int16_t *bias,
    VXLIB_bufParams3D_t *bias_addr,
    int32_t *dst,
    VXLIB_bufParams3D_t *dst_addr,
    uint32_t shiftQ,
    uint32_t coeffQ,
    void *pBlock
)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#if defined(VXLIB_CHECK_PARAMS) || defined(VXLIB_CONV_I16S_C16S_O32S_5x5_SKIP1_CHECK_PARAMS)
    status = VXLIB_conv_i16s_c16s_o32s_5x5_skip1_checkParams(src, src_addr, weights, wgt_addr, bias, bias_addr, shiftQ, coeffQ, pBlock);
    if( status == VXLIB_SUCCESS )
#endif
    {
        /* IMPORTANT: Initialize params to 0 before setting stream parameters */
        __STRM_TEMPLATE seTemplate;
        __STRM_TEMPLATE saTemplate;

        __SE_FLAGS seFlags;
        __SA_FLAGS saFlags;

        __STRM_PARAM_6D seParams;
        __STRM_PARAM_6D saParams;

        ulong8 vMask;

        int32_t srcBitDepth = VXLIB_sizeof(src_addr->data_type);
        int32_t dstBitDepth = VXLIB_sizeof(dst_addr->data_type);
        int32_t wgtBitDepth = VXLIB_sizeof(wgt_addr->data_type);

        int32_t srcStride = src_addr->stride_y / srcBitDepth;
        int32_t dstStride = dst_addr->stride_y / dstBitDepth;

        int32_t numInCh  = src_addr->dim_z;
        int32_t numOutCh = dst_addr->dim_z;

        seFlags = __SE_FLAGS_default();

        seFlags.ELETYPE   = __SE_ELETYPE_16BIT;
        seFlags.VECLEN    = __SE_VECLEN_32ELEMS;

        seParams.ICNT0 = (src_addr->dim_x > INP_SIMD_WIDTH)?INP_SIMD_WIDTH:src_addr->dim_x;
        seParams.ICNT1 = 2;
        seParams.ICNT2 = wgt_addr->dim_y;
        seParams.ICNT3 = numInCh;
        seParams.ICNT4 = NUM_INP_SIMD_BLOCKS(dst_addr->dim_x);
        seParams.ICNT5 = dst_addr->dim_y;

        seParams.DIM1 = 4;
        seParams.DIM2 = srcStride;
        seParams.DIM3 = src_addr->stride_z / srcBitDepth;
        seParams.DIM4 = INP_SIMD_WIDTH;
        seParams.DIM5 = srcStride;

        seTemplate = __SE_SET_PARAM_6D(&seParams, &seFlags);
        *stov_ptr(__STRM_TEMPLATE, (uint32_t*)((uint8_t *)pBlock + SE_PARAM_OFFSET)) = seTemplate;

        /* Prepare SA 0 tempate to store output */
        saFlags = __SA_FLAGS_default();
        saFlags.VECLEN  = __SA_VECLEN_32ELEMS;

        /* ITERATION COUNTERS */
        saParams.ICNT0 = (dst_addr->dim_x > INP_SIMD_WIDTH)?INP_SIMD_WIDTH:dst_addr->dim_x;
        saParams.ICNT1 = NUM_INP_SIMD_BLOCKS(dst_addr->dim_x);
        saParams.ICNT2 = dst_addr->dim_y;
        saParams.ICNT3 = numOutCh;
        saParams.ICNT4 = 1;
        saParams.ICNT5 = 1;

        saParams.DIM1 = INP_SIMD_WIDTH;
        saParams.DIM2 = dstStride;
        saParams.DIM3 = dst_addr->stride_z / dstBitDepth;
        saParams.DIM4 = 0;
        saParams.DIM5 = 0;

        saTemplate = __SA_SET_PARAM_6D(&saParams, &saFlags);
        *stov_ptr(__STRM_TEMPLATE, (uint32_t*)((uint8_t *)pBlock + SA0_PARAM_OFFSET)) = saTemplate;

        /* Prepare SA 1 tempate to load weights */
        saFlags = __SA_FLAGS_default();
        saFlags.VECLEN = __SA_VECLEN_8ELEMS;

        /* ITERATION COUNTERS */
        saParams.ICNT0 = ((wgt_addr->stride_y / wgtBitDepth) * wgt_addr->dim_y);
        saParams.ICNT1 = numInCh;
        saParams.ICNT2 = NUM_INP_SIMD_BLOCKS(dst_addr->dim_x);
        saParams.ICNT3 = dst_addr->dim_y;
        saParams.ICNT4 = numOutCh;
        saParams.ICNT5 = 1;

        saParams.DIM1 = ((wgt_addr->stride_y / wgtBitDepth) * wgt_addr->dim_y);
        saParams.DIM2 = 0;
        saParams.DIM3 = 0;
        saParams.DIM4 = ((wgt_addr->stride_y / wgtBitDepth) * wgt_addr->dim_y) * numInCh;
        saParams.DIM5 = 0;

        saTemplate = __SA_SET_PARAM_6D(&saParams, &saFlags);
        *stov_ptr(__STRM_TEMPLATE, (uint32_t*)((uint8_t *)pBlock + SA1_PARAM_OFFSET)) = saTemplate;

        vMask.s0 = 0x0706050403020100;
        vMask.s1 = 0x0706050403020100;
        vMask.s2 = 0x0706050403020100;
        vMask.s3 = 0x0706050403020100;
        vMask.s4 = 0x0706050403020100;
        vMask.s5 = 0x0706050403020100;
        vMask.s6 = 0x0706050403020100;
        vMask.s7 = 0x0706050403020100;

        *stov_ptr(uchar64, (uint8_t*)((uint8_t *)pBlock + MASK0_PARAM_OFFSET)) = __as_uchar64(vMask);

        vMask.s0 = 0x0F0E0D0C0B0A0908;
        vMask.s1 = 0x0F0E0D0C0B0A0908;
        vMask.s2 = 0x0F0E0D0C0B0A0908;
        vMask.s3 = 0x0F0E0D0C0B0A0908;
        vMask.s4 = 0x0F0E0D0C0B0A0908;
        vMask.s5 = 0x0F0E0D0C0B0A0908;
        vMask.s6 = 0x0F0E0D0C0B0A0908;
        vMask.s7 = 0x0F0E0D0C0B0A0908;

        *stov_ptr(uchar64, (uint8_t*)((uint8_t *)pBlock + MASK1_PARAM_OFFSET)) = __as_uchar64(vMask);
    }

    return (status);
}

VXLIB_STATUS VXLIB_conv_i16s_c16s_o32s_5x5_skip1_kernel
(
    int16_t *src,
    VXLIB_bufParams3D_t *src_addr,
    int16_t *weights,
    VXLIB_bufParams3D_t *wgt_addr,
    int16_t *bias,
    VXLIB_bufParams3D_t *bias_addr,
    int32_t *dst,
    VXLIB_bufParams3D_t *dst_addr,
    uint32_t shiftQ,
    uint32_t coeffQ,
    void *pBlock
)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#if defined(VXLIB_CHECK_PARAMS) || defined(VXLIB_CONV_I16S_C16S_O32S_5x5_SKIP1_CHECK_PARAMS)
    status = VXLIB_conv_i16s_c16s_o32s_5x5_skip1_checkParams(src, src_addr, weights, wgt_addr, bias, bias_addr, shiftQ, coeffQ, pBlock);
    if( status == VXLIB_SUCCESS )
#endif
    {
    	int32_t numInCh, numOutCh;
    	int32_t outChIdx;
    	int32_t round_val;

    	int32_t ctrX;
    	int32_t outRows;

        int32_t *pOutDataLo;
        int32_t *pOutDataHi;

        int32_t numInItr, numOutItr;

        __STRM_TEMPLATE seTemplate;
        __STRM_TEMPLATE saTemplate;

        uchar64 vMask0, vMask1;

    	  outRows  = dst_addr->dim_y;

        numInCh  = src_addr->dim_z;
        numOutCh = dst_addr->dim_z;

      	round_val = (shiftQ == 0) ? 0 : (1 << (shiftQ - 1));
        int16 vRnd = (int16)(round_val);
        int16 vShiftQ = (int16)(shiftQ);

        numOutItr = NUM_INP_SIMD_BLOCKS(dst_addr->dim_x) * outRows;
        numInItr  = 5 * numInCh;

        pOutDataLo = (int32_t *)dst;
        pOutDataHi = (int32_t *)dst + (INP_SIMD_WIDTH/2);

        saTemplate = *stov_ptr(__STRM_TEMPLATE, (uint32_t*)((uint8_t *)pBlock+ SA0_PARAM_OFFSET));
        __SA0_OPEN(saTemplate);

#ifdef _DISPLAY_PARAMS
        displaySAParam((void *)pOutDataLo, saTemplate, PARAMV_SA0);
#endif

        saTemplate = *stov_ptr(__STRM_TEMPLATE, (uint32_t*)((uint8_t *)pBlock+ SA1_PARAM_OFFSET));
        __SA1_OPEN(saTemplate);

#ifdef _DISPLAY_PARAMS
        displaySAParam((void *)weights, saTemplate, PARAMV_SA1);
#endif

        seTemplate = *stov_ptr(__STRM_TEMPLATE, (uint32_t*)((uint8_t *)pBlock+ SE_PARAM_OFFSET));

#ifdef _DISPLAY_PARAMS
        displaySEParam((void *)src, seTemplate, PARAMV_SE0);
        displaySEParam((void *)(src + INP_SIMD_WIDTH), seTemplate, PARAMV_SE1);
#endif

        vMask0 = *stov_ptr(uchar64, (uint8_t*)((uint8_t *)pBlock+ MASK0_PARAM_OFFSET));
        vMask1 = *stov_ptr(uchar64, (uint8_t*)((uint8_t *)pBlock+ MASK1_PARAM_OFFSET));

#pragma MUST_ITERATE(1,,)
        for( outChIdx = 0; outChIdx < numOutCh; outChIdx++ )
        {
            int32_t biasVal = bias[outChIdx];
            int16 vBias = (int16)(biasVal);

            __SE0_OPEN((void *)src, seTemplate);
            __SE1_OPEN((void *)(src + INP_SIMD_WIDTH), seTemplate);

            int16 vAccPrevLo = vBias << (int16)(coeffQ - shiftQ);
            int16 vAccPrevHi = vBias << (int16)(coeffQ - shiftQ);

#pragma MUST_ITERATE(1,,)
            for(ctrX = 0; ctrX < numOutItr; ctrX++)
            {
                int32_t idx;

                int16 vAccLo = (int16)(0);
                int16 vAccHi = (int16)(0);

#pragma MUST_ITERATE(1,,)
                for(idx = 0; idx < numInItr; idx++)
                {
                    int16 vRes0Lo, vRes0Hi;
                    int16 vRes1Lo, vRes1Hi;

                    short32 vCoeff = *__SA1ADV(short32, weights);

                    uchar64 vCoeff0 = __permute(vMask0, __as_uchar64(vCoeff));
                    uchar64 vCoeff1 = __permute(vMask1, __as_uchar64(vCoeff));

                    __vfir4hw_vww(__as_short32(vCoeff0), __SE_REG_PAIR_0_ADV, vRes0Lo, vRes0Hi);
                    __vfir4hw_vww(__as_short32(vCoeff1), __SE_REG_PAIR_0_ADV, vRes1Lo, vRes1Hi);

                    vAccLo = vAccLo + vRes0Lo + vRes1Lo;
                    vAccHi = vAccHi + vRes0Hi + vRes1Hi;

                }

                int16 vOutLo = ((__as_int16(vAccLo) + vRnd) >> vShiftQ) + vAccPrevLo;
                int16 vOutHi = ((__as_int16(vAccHi) + vRnd) >> vShiftQ) + vAccPrevHi;

                __vpred vpStore   = __SA0_VPRED(short32);
                __vpred vpStoreLo = __pdupl2h_pp(vpStore);
                __vpred vpStoreHi = __pduph2h_pp(vpStore);

                __vstore_pred(vpStoreLo, __SA0(int16, pOutDataLo), vOutLo);
                __vstore_pred(vpStoreHi, __SA0ADV(int16, pOutDataHi), vOutHi);
            }
            __SE1_CLOSE();
            __SE0_CLOSE();
        }

        __SA1_CLOSE();
        __SA0_CLOSE();
    }

    return (status);
}

VXLIB_STATUS VXLIB_conv_i16s_c16s_o32s_5x5_skip1_checkParams
(
    int16_t *src,
    VXLIB_bufParams3D_t *src_addr,
    int16_t *weights,
    VXLIB_bufParams3D_t *wgt_addr,
    int16_t *bias,
    VXLIB_bufParams3D_t *bias_addr,
    int32_t *dst,
    VXLIB_bufParams3D_t *dst_addr,
    uint32_t shiftQ,
    uint32_t coeffQ,
    void *pBlock
)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

    return (status);
}

/* ======================================================================== */
/*  End of file:  VXLIB_conv_i16s_c16s_o32s_5x5_skip1.c                     */
/* ======================================================================== */
