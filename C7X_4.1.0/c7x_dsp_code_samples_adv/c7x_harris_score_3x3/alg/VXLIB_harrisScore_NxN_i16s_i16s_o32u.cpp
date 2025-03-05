/*
* module name       : c7x_harris_score_3x3
*
* module descripton : Computes Harris Score for 3x3 window
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#include "VXLIB_harrisScore_NxN_i16s_i16s_o32u.h"

VXLIB_STATUS VXLIB_harrisScore_NxN_i16s_i16s_o32u_init(int16_t gradx[],
                                                       VXLIB_bufParams2D_t * gradx_addr,
                                                       int16_t grady[],
                                                       VXLIB_bufParams2D_t * grady_addr,
                                                       uint32_t dst[],
                                                       VXLIB_bufParams2D_t * dst_addr,
                                                       uint32_t scratch[],
                                                       uint8_t blk_size,
                                                       void *pBlock)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#ifdef VXLIB_CHECK_PARAMS
    status = VXLIB_harrisScore_NxN_i16s_i16s_o32u_checkParams_cn(gradx, gradx_addr, grady, grady_addr, dst, dst_addr, scratch, blk_size, pBlock);
    if( status == VXLIB_SUCCESS )
#endif
    {
        __STRM_TEMPLATE seTemplate;
        __STRM_TEMPLATE saTemplate;

        __SE_FLAGS seFlags;
        __SA_FLAGS saFlags;

        __STRM_PARAM_3D se3DParams;
        __STRM_PARAM_4D se4DParams;
        __STRM_PARAM_3D sa3DParams;

        int32_t srcBitDepth = VXLIB_sizeof(gradx_addr->data_type);
        int32_t dstBitDepth = VXLIB_sizeof(dst_addr->data_type);

        int32_t srcStride = gradx_addr->stride_y / srcBitDepth;
        int32_t dstStride = dst_addr->stride_y / dstBitDepth;

        int32_t srcWidth  = gradx_addr->dim_x;
        int32_t srcHeight = gradx_addr->dim_y;

        int32_t dstWidth  = dst_addr->dim_x;
        int32_t dstHeight = dst_addr->dim_y;
        /*-------------------------------------------------------*/
        /* Stage 1 - Produce Gxx, Gyy in vertical direction      */
        /*-------------------------------------------------------*/
        seFlags = __SE_FLAGS_default();

        seFlags.ELETYPE   = __SE_ELETYPE_16BIT;
        seFlags.VECLEN    = __SE_VECLEN_32ELEMS;
        seFlags.DECDIM1   = __SE_DECDIM_DIM2;

        //Leading stream should load all input rows
        se3DParams.DECDIM1_WIDTH = srcWidth;
        se3DParams.ICNT0 = IN_SIMD_WIDTH;
        se3DParams.ICNT1 = srcHeight;
        se3DParams.ICNT2 = NUM_IN_SIMD_BLOCKS(srcWidth);

        se3DParams.DIM1 = srcStride;
        se3DParams.DIM2 = IN_SIMD_WIDTH;

        seTemplate = __SE_SET_PARAM_3D(&se3DParams, &seFlags);
        *stov_ptr(__STRM_TEMPLATE, (uint32_t *)((uint8_t *)pBlock + SE0_STAGE1_PARAM_OFFSET)) = seTemplate;

        //Trailing stream should load only output rows - 1
        se3DParams.ICNT1 = dstHeight - 1;

        seTemplate = __SE_SET_PARAM_3D(&se3DParams, &seFlags);
        *stov_ptr(__STRM_TEMPLATE, (uint32_t *)((uint8_t *)pBlock + SE1_STAGE1_PARAM_OFFSET)) = seTemplate;

        saFlags = __SA_FLAGS_default();

        saFlags.VECLEN  = __SA_VECLEN_16ELEMS;  /* 16, 32-bit elements per store */
        saFlags.DECDIM1 = __SA_DECDIM_DIM2;

        sa3DParams.DECDIM1_WIDTH = srcWidth;
        sa3DParams.ICNT0 = IN_SIMD_WIDTH;
        sa3DParams.ICNT1 = dstHeight;
        sa3DParams.ICNT2 = NUM_IN_SIMD_BLOCKS(srcWidth);

        sa3DParams.DIM1 = srcStride;
        sa3DParams.DIM2 = IN_SIMD_WIDTH;

        saTemplate = __SA_SET_PARAM_3D(&sa3DParams, &saFlags);
        *stov_ptr(__STRM_TEMPLATE, (uint32_t *)((uint8_t *)pBlock + SA_STAGE1_PARAM_OFFSET)) = saTemplate;

        /*-------------------------------------------------------*/
        /* Stage 2 - Produce output Gxx + Gyy                    */
        /*-------------------------------------------------------*/

        seFlags = __SE_FLAGS_default();

        seFlags.ELETYPE   = __SE_ELETYPE_32BIT;
        seFlags.VECLEN    = __SE_VECLEN_16ELEMS;
        seFlags.DECDIM1   = __SE_DECDIM_DIM2;

        se4DParams.DECDIM1_WIDTH = srcWidth;
        se4DParams.ICNT0 = OUT_SIMD_WIDTH;
        se4DParams.ICNT1 = blk_size;
        se4DParams.ICNT2 = NUM_OUT_SIMD_BLOCKS(dstWidth);
        se4DParams.ICNT3 = dstHeight;

        se4DParams.DIM1 = 1;
        se4DParams.DIM2 = OUT_SIMD_WIDTH;
        se4DParams.DIM3 = srcStride;

        seTemplate = __SE_SET_PARAM_4D(&se4DParams, &seFlags);
        *stov_ptr(__STRM_TEMPLATE, (uint32_t *)((uint8_t *)pBlock + SE_STAGE3_PARAM_OFFSET)) = seTemplate;

        saFlags = __SA_FLAGS_default();

        saFlags.VECLEN  = __SA_VECLEN_16ELEMS;
        saFlags.DECDIM1 = __SA_DECDIM_DIM1;

        sa3DParams.DECDIM1_WIDTH = dstWidth;
        sa3DParams.ICNT0 = OUT_SIMD_WIDTH;
        sa3DParams.ICNT1 = NUM_OUT_SIMD_BLOCKS(dstWidth);
        sa3DParams.ICNT2 = dstHeight;

        sa3DParams.DIM1 = OUT_SIMD_WIDTH;
        sa3DParams.DIM2 = dstStride;

        saTemplate = __SA_SET_PARAM_3D(&sa3DParams, &saFlags);
        *stov_ptr(__STRM_TEMPLATE, (uint32_t *)((uint8_t *)pBlock + SA_STAGE3_PARAM_OFFSET)) = saTemplate;

        ulong8 vMask;

        // Form permute pattern to interleave 32-bit results
        vMask.s0 = 0x2322212003020100;
        vMask.s1 = 0x2726252407060504;
        vMask.s2 = 0x2B2A29280B0A0908;
        vMask.s3 = 0x2F2E2D2C0F0E0D0C;
        vMask.s4 = 0x3332313013121110;
        vMask.s5 = 0x3736353417161514;
        vMask.s6 = 0x3B3A39381B1A1918;
        vMask.s7 = 0x3F3E3D3C1F1E1D1C;

        *stov_ptr(uchar64, (uint8_t *)((uint8_t *)pBlock + MASK_OFFSET)) = __as_uchar64(vMask);
    }

    return (status);
}

VXLIB_STATUS VXLIB_harrisScore_NxN_i16s_i16s_o32u_checkParams(int16_t gradx[],
                                                              VXLIB_bufParams2D_t * gradx_addr,
                                                              int16_t grady[],
                                                              VXLIB_bufParams2D_t * grady_addr,
                                                              uint32_t dst[],
                                                              VXLIB_bufParams2D_t * dst_addr,
                                                              uint32_t scratch[],
                                                              uint8_t blk_size,
                                                              void *pBlock)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

    return (status);
}
