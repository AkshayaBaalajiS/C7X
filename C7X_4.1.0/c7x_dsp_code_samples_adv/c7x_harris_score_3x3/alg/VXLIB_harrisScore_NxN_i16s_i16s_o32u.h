/*
* module name       : c7x_harris_score_3x3
*
* module descripton : Computes Harris Score for 3x3 window
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#ifndef VXLIB_HARRISSCORE_NXN_I16S_I16S_O32U_H_
#define VXLIB_HARRISSCORE_NXN_I16S_I16S_O32U_H_ 1

#include "VXLIB_types.h"

#ifdef _DISPLAY_PARAMS
#include "paramv.h"
#endif

#define VXLIB_HARRISSCORE_NXN_I16S_I16S_O32U_PBLOCK_SIZE (576)

#define SE_PARAM_BASE (0x0000)

#define SE0_STAGE1_PARAM_OFFSET (SE_PARAM_BASE)
#define SE1_STAGE1_PARAM_OFFSET (SE0_STAGE1_PARAM_OFFSET + SE_PARAM_SIZE)
#define SE0_STAGE2_PARAM_OFFSET (SE1_STAGE1_PARAM_OFFSET + SE_PARAM_SIZE)
#define SE1_STAGE2_PARAM_OFFSET (SE0_STAGE2_PARAM_OFFSET + SE_PARAM_SIZE)
#define SE_STAGE3_PARAM_OFFSET  (SE1_STAGE2_PARAM_OFFSET + SE_PARAM_SIZE)

#define SA_STAGE1_PARAM_OFFSET (SE_STAGE3_PARAM_OFFSET + SE_PARAM_SIZE)
#define SA_STAGE2_PARAM_OFFSET (SA_STAGE1_PARAM_OFFSET + SA_PARAM_SIZE)
#define SA_STAGE3_PARAM_OFFSET (SA_STAGE2_PARAM_OFFSET + SA_PARAM_SIZE)
#define MASK_OFFSET            (SA_STAGE3_PARAM_OFFSET + SA_PARAM_SIZE)

#define IN_SIMD_WIDTH_SHIFT       (5) /* 2^5 = 32 16b elements in a 512b vector */
#define IN_SIMD_WIDTH             (1 << IN_SIMD_WIDTH_SHIFT)
#define IN_SIMD_WIDTH_RND         (IN_SIMD_WIDTH >> 1)
#define NUM_IN_SIMD_BLOCKS(width) (((width) >> IN_SIMD_WIDTH_SHIFT) + (((width) - (((width) >> IN_SIMD_WIDTH_SHIFT) << IN_SIMD_WIDTH_SHIFT)) > 0 ? 1 : 0))

#define OUT_SIMD_WIDTH_SHIFT       (4) /* 2^4 = 16 32b elements in a 512b vector */
#define OUT_SIMD_WIDTH             (1 << OUT_SIMD_WIDTH_SHIFT)
#define OUT_SIMD_WIDTH_RND         (OUT_SIMD_WIDTH >> 1)
#define NUM_OUT_SIMD_BLOCKS(width) (((width) >> OUT_SIMD_WIDTH_SHIFT) + (((width) - (((width) >> OUT_SIMD_WIDTH_SHIFT) << OUT_SIMD_WIDTH_SHIFT)) > 0 ? 1 : 0))


VXLIB_STATUS VXLIB_harrisScore_NxN_i16s_i16s_o32u_init(int16_t gradx[],
                                                       VXLIB_bufParams2D_t * gradx_addr,
                                                       int16_t grady[],
                                                       VXLIB_bufParams2D_t * grady_addr,
                                                       uint32_t dst[],
                                                       VXLIB_bufParams2D_t * dst_addr,
                                                       uint32_t scratch[],
                                                       uint8_t block_size,
                                                       void *pBlock);
VXLIB_STATUS VXLIB_harrisScore_NxN_i16s_i16s_o32u_checkParams(int16_t gradx[],
                                                              VXLIB_bufParams2D_t * gradx_addr,
                                                              int16_t grady[],
                                                              VXLIB_bufParams2D_t * grady_addr,
                                                              uint32_t dst[],
                                                              VXLIB_bufParams2D_t * dst_addr,
                                                              uint32_t scratch[],
                                                              uint8_t block_size,
                                                              void *pBlock);

template <int UNROLL_COUNT>
VXLIB_STATUS VXLIB_harrisScore_NxN_i16s_i16s_o32u_kernel(int16_t gradx[],
                                                         VXLIB_bufParams2D_t * gradx_addr,
                                                         int16_t grady[],
                                                         VXLIB_bufParams2D_t * grady_addr,
                                                         uint32_t dst[],
                                                         VXLIB_bufParams2D_t * dst_addr,
                                                         uint32_t scratch[],
                                                         uint8_t block_size,
                                                         void *pBlock);

template <int UNROLL_COUNT>
VXLIB_STATUS VXLIB_harrisScore_NxN_i16s_i16s_o32u_kernel(int16_t *gradx,
                                                         VXLIB_bufParams2D_t * gradx_addr,
                                                         int16_t *grady,
                                                         VXLIB_bufParams2D_t * grady_addr,
                                                         uint32_t *dst,
                                                         VXLIB_bufParams2D_t * dst_addr,
                                                         uint32_t *scratch,
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

        int32_t blkX, blkY, ctr, numBlocks;
        int32_t inWidth, outWidth, outHeight, count;

        int32_t stage1_size;

        uint32_t *pS1GxxOut;
        uint32_t *pS1GyyOut;

        int32_t srcBitDepth = VXLIB_sizeof(gradx_addr->data_type);
        int32_t srcStride = gradx_addr->stride_y / srcBitDepth;

        inWidth = gradx_addr->dim_x;
        outWidth = dst_addr->dim_x;
        outHeight = dst_addr->dim_y;

        stage1_size = srcStride * dst_addr->dim_y * sizeof(uint32_t);

        pS1GxxOut = (uint32_t *)scratch;
        pS1GyyOut = (uint32_t *)((uint8_t *)scratch + stage1_size);

        /*----------------------------------------------------*/
        /* Stage 1 - Produce Sum of Gxx in vertical direction */
        /*----------------------------------------------------*/
        seTemplate = *stov_ptr(__STRM_TEMPLATE, (uint32_t *)((uint8_t *)pBlock + SE0_STAGE1_PARAM_OFFSET));
        __SE0_OPEN((void *)gradx, seTemplate);

#ifdef _DISPLAY_PARAMS
        displaySEParam((void *)gradx, seTemplate, PARAMV_SE0);
#endif

        seTemplate = *stov_ptr(__STRM_TEMPLATE, (uint32_t *)((uint8_t *)pBlock + SE1_STAGE1_PARAM_OFFSET));
        __SE1_OPEN((void *)gradx, seTemplate);

#ifdef _DISPLAY_PARAMS
        displaySEParam((void *)gradx, seTemplate, PARAMV_SE1);
#endif

        saTemplate = *stov_ptr(__STRM_TEMPLATE, (uint32_t *)((uint8_t *)pBlock + SA_STAGE1_PARAM_OFFSET));
        __SA0_OPEN(saTemplate);

#ifdef _DISPLAY_PARAMS
        displaySAParam((void *)pS1GxxOut, saTemplate, PARAMV_SA0);
#endif

        uchar64 vMask = *stov_ptr(uchar64, (uint8_t *)((uint8_t *)pBlock + MASK_OFFSET));

        numBlocks = NUM_IN_SIMD_BLOCKS(inWidth);
        count = outHeight - 1;

#pragma MUST_ITERATE(1,,)
        for(blkX = 0; blkX < numBlocks; blkX++)
        {
            int16 vAcc_lo = (int16)(0);
            int16 vAcc_hi = (int16)(0);

#pragma MUST_ITERATE(1,,)
            for(ctr = 0; ctr < blk_size; ctr++)
            {
              int16 vGxx_lo, vGxx_hi;
              short32 vGx_a = __SE0ADV(short32);

              __vmpyhw_vvw(vGx_a, vGx_a, vGxx_lo, vGxx_hi);

              vAcc_lo = vAcc_lo + vGxx_lo;
              vAcc_hi = vAcc_hi + vGxx_hi;
            }

#pragma MUST_ITERATE(1,,)
            for(blkY = 0; blkY < count; blkY++)
            {
              //de-interleave and write output
              uchar64 vOut_lo = __permute_low_low(vMask, __as_uchar64(vAcc_hi), __as_uchar64(vAcc_lo));
              uchar64 vOut_hi = __permute_high_high(vMask, __as_uchar64(vAcc_hi), __as_uchar64(vAcc_lo));

              *__SA0ADV(int16, pS1GxxOut) = __as_int16(vOut_lo);
              *__SA0ADV(int16, pS1GxxOut) = __as_int16(vOut_hi);

              //Read N + 1 line
              int16 vGxx_a_lo, vGxx_a_hi;
              short32 vGx_a = __SE0ADV(short32);

              __vmpyhw_vvw(vGx_a, vGx_a, vGxx_a_lo, vGxx_a_hi);

              //Read 1st line
              int16 vGxx_b_lo, vGxx_b_hi;
              short32 vGx_b = __SE1ADV(short32);

              __vmpyhw_vvw(vGx_b, vGx_b, vGxx_b_lo, vGxx_b_hi);

              //Add N+1th line and subtract 1st line
              vAcc_lo = vAcc_lo - vGxx_b_lo + vGxx_a_lo;
              vAcc_hi = vAcc_hi - vGxx_b_hi + vGxx_a_hi;

            }

              //de-interleave and write output
              uchar64 vOut_lo = __permute_low_low(vMask, __as_uchar64(vAcc_hi), __as_uchar64(vAcc_lo));
              uchar64 vOut_hi = __permute_high_high(vMask, __as_uchar64(vAcc_hi), __as_uchar64(vAcc_lo));

              *__SA0ADV(int16, pS1GxxOut) = __as_int16(vOut_lo);
              *__SA0ADV(int16, pS1GxxOut) = __as_int16(vOut_hi);
        }

        __SA0_CLOSE();
        __SE1_CLOSE();
        __SE0_CLOSE();

        /*----------------------------------------------------*/
        /* Stage 1 - Produce Sum of Gyy in vertical direction */
        /*----------------------------------------------------*/
        seTemplate = *stov_ptr(__STRM_TEMPLATE, (uint32_t *)((uint8_t *)pBlock + SE0_STAGE1_PARAM_OFFSET));
        __SE0_OPEN((void *)grady, seTemplate);

#ifdef _DISPLAY_PARAMS
        displaySEParam((void *)grady, seTemplate, PARAMV_SE0);
#endif

        seTemplate = *stov_ptr(__STRM_TEMPLATE, (uint32_t *)((uint8_t *)pBlock + SE1_STAGE1_PARAM_OFFSET));
        __SE1_OPEN((void *)grady, seTemplate);

#ifdef _DISPLAY_PARAMS
        displaySEParam((void *)grady, seTemplate, PARAMV_SE1);
#endif

        saTemplate = *stov_ptr(__STRM_TEMPLATE, (uint32_t *)((uint8_t *)pBlock + SA_STAGE1_PARAM_OFFSET));
        __SA0_OPEN(saTemplate);

#ifdef _DISPLAY_PARAMS
        displaySAParam((void *)pS1GyyOut, saTemplate, PARAMV_SA0);
#endif

        numBlocks = NUM_IN_SIMD_BLOCKS(inWidth);
        count = outHeight - 1;

#pragma MUST_ITERATE(1,,)
        for(blkX = 0; blkX < numBlocks; blkX++)
        {
            int16 vAcc_lo = (int16)(0);
            int16 vAcc_hi = (int16)(0);
#pragma MUST_ITERATE(1,,)
            for(ctr = 0; ctr < blk_size; ctr++)
            {
              int16 vGyy_lo, vGyy_hi;
              short32 vGy_a = __SE0ADV(short32);

              __vmpyhw_vvw(vGy_a, vGy_a, vGyy_lo, vGyy_hi);

              vAcc_lo = vAcc_lo + vGyy_lo;
              vAcc_hi = vAcc_hi + vGyy_hi;
            }

#pragma MUST_ITERATE(1,,)
            for(blkY = 0; blkY < count; blkY++)
            {
              //de-interleave and write output
              uchar64 vOut_lo = __permute_low_low(vMask, __as_uchar64(vAcc_hi), __as_uchar64(vAcc_lo));
              uchar64 vOut_hi = __permute_high_high(vMask, __as_uchar64(vAcc_hi), __as_uchar64(vAcc_lo));

              *__SA0ADV(int16, pS1GyyOut) = __as_int16(vOut_lo);
              *__SA0ADV(int16, pS1GyyOut) = __as_int16(vOut_hi);

              //Read N + 1 line
              int16 vGyy_a_lo, vGyy_a_hi;
              short32 vGy_a = __SE0ADV(short32);

              __vmpyhw_vvw(vGy_a, vGy_a, vGyy_a_lo, vGyy_a_hi);

              //Read 1st line
              int16 vGyy_b_lo, vGyy_b_hi;
              short32 vGy_b = __SE1ADV(short32);

              __vmpyhw_vvw(vGy_b, vGy_b, vGyy_b_lo, vGyy_b_hi);

              //Add N+1th line and subtract 1st line
              vAcc_lo = vAcc_lo - vGyy_b_lo + vGyy_a_lo;
              vAcc_hi = vAcc_hi - vGyy_b_hi + vGyy_a_hi;

            }

              //de-interleave and write output
              uchar64 vOut_lo = __permute_low_low(vMask, __as_uchar64(vAcc_hi), __as_uchar64(vAcc_lo));
              uchar64 vOut_hi = __permute_high_high(vMask, __as_uchar64(vAcc_hi), __as_uchar64(vAcc_lo));

              *__SA0ADV(int16, pS1GyyOut) = __as_int16(vOut_lo);
              *__SA0ADV(int16, pS1GyyOut) = __as_int16(vOut_hi);
        }

        __SA0_CLOSE();
        __SE1_CLOSE();
        __SE0_CLOSE();

        /*------------------------------------------------------*/
        /* Stage 2 - Produce output Gxx + Gyy                   */
        /*------------------------------------------------------*/
        seTemplate = *stov_ptr(__STRM_TEMPLATE, (uint32_t *)((uint8_t *)pBlock + SE_STAGE3_PARAM_OFFSET));

        __SE0_OPEN((void *)pS1GxxOut, seTemplate);
        __SE1_OPEN((void *)pS1GyyOut, seTemplate);

#ifdef _DISPLAY_PARAMS
        displaySEParam((void *)pS1GxxOut, seTemplate, PARAMV_SE0);
        displaySEParam((void *)pS1GyyOut, seTemplate, PARAMV_SE1);
#endif

        saTemplate = *stov_ptr(__STRM_TEMPLATE, (uint32_t *)((uint8_t *)pBlock + SA_STAGE3_PARAM_OFFSET));
        __SA0_OPEN(saTemplate);

#ifdef _DISPLAY_PARAMS
        displaySAParam((void *)dst, saTemplate, PARAMV_SA0);
#endif

        numBlocks = NUM_OUT_SIMD_BLOCKS(outWidth);

#pragma MUST_ITERATE(1,,)
        for(blkY = 0; blkY < outHeight; blkY++)
        {
#pragma MUST_ITERATE(1,,)
          for(blkX = 0; blkX < numBlocks; blkX++)
          {
            int16 vAcc0 = (int16)(0);
            int16 vAcc1 = (int16)(0);

            [[TI::unroll(UNROLL_COUNT)]]
            for(ctr = 0; ctr < UNROLL_COUNT; ctr++)
            {
              vAcc0 = vAcc0 + __SE0ADV(int16);
              vAcc1 = vAcc1 + __SE1ADV(int16);
            }

            int16 vSum = vAcc0 + vAcc1;

            __vpred vpStore = __SA0_VPRED(int16);
            __vstore_pred(vpStore, __SA0ADV(int16, dst), vSum);
          }
        }

        __SA0_CLOSE();
        __SE1_CLOSE();
        __SE0_CLOSE();

    }
    return (status);
}


#endif /* VXLIB_HARRISSCORE_NXN_I16S_I16S_O32U_H_ */
/* ======================================================================== */
/*  End of file:  VXLIB_harrisScore_NxN_i16s_i16s_o32u.h                    */
/* ======================================================================== */
