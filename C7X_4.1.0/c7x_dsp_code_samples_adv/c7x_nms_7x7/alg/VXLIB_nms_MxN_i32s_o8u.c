/*
* module name       : c7x_nms
*
* module descripton : Computes 7x7 window Non Maximum Suppression
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#include "VXLIB_nms_MxN_i32s_o8u.h"
#include <limits.h>

#ifdef _DISPLAY_PARAMS
#include "paramv.h"
#endif

#define SIMD_WIDTH_SHIFT       (4) /* 2^4 = 16x32b elements in a 512b vector */
#define SIMD_WIDTH             (1 << SIMD_WIDTH_SHIFT)
#define SIMD_WIDTH_RND         (SIMD_WIDTH >> 1)
#define ALIGN_SIMD_WIDTH(a)    (((a) + SIMD_WIDTH-1) & ~(SIMD_WIDTH-1))
#define NUM_SIMD_BLOCKS(width) (((width) + (SIMD_WIDTH - 1)) >> SIMD_WIDTH_SHIFT)

#define CONFIG_PARAM_BASE       (0x0000)
#define SE_PARAM_STAGE1_OFFSET  (CONFIG_PARAM_BASE)
#define SA_PARAM_STAGE1_OFFSET  (SE_PARAM_STAGE1_OFFSET  + SE_PARAM_SIZE)
#define SE_PARAM_STAGE2_OFFSET  (SA_PARAM_STAGE1_OFFSET  + SA_PARAM_SIZE)
#define SA_PARAM_STAGE2_OFFSET  (SE_PARAM_STAGE2_OFFSET  + SE_PARAM_SIZE)
#define SE0_PARAM_STAGE3_OFFSET (SA_PARAM_STAGE2_OFFSET  + SA_PARAM_SIZE)
#define SE1_PARAM_STAGE3_OFFSET (SE0_PARAM_STAGE3_OFFSET + SE_PARAM_SIZE)
#define SA_PARAM_STAGE3_OFFSET  (SE1_PARAM_STAGE3_OFFSET + SE_PARAM_SIZE)

VXLIB_STATUS VXLIB_nms_MxN_i32s_o8u_init
(
  const int32_t              src[restrict],
  const VXLIB_bufParams2D_t *src_addr,
  uint8_t                    dst[restrict],
  const VXLIB_bufParams2D_t *dst_addr,
  int32_t                    scratch1[restrict],
  int32_t                    scratch2[restrict],
  uint8_t                    winWidth,
  uint8_t                    winHeight,
  int32_t                    threshold,
  void                      *pBlock
)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

    {
        __STRM_TEMPLATE seTemplate;
        __STRM_TEMPLATE saTemplate;

        __SE_FLAGS seFlags;
        __SA_FLAGS saFlags;

        __STRM_PARAM_4D seParam;
        __STRM_PARAM_3D saParam;

        int32_t bit_depth_in  = VXLIB_sizeof(src_addr->data_type);
        int32_t inStride      = src_addr->stride_y / bit_depth_in;

        int32_t bit_depth_out = VXLIB_sizeof(dst_addr->data_type);
        int32_t outStride     = dst_addr->stride_y / bit_depth_out;

        int32_t inWidth   = src_addr->dim_x;
        int32_t inHeight  = src_addr->dim_y;

        int32_t outWidth  = dst_addr->dim_x;
        int32_t outHeight = dst_addr->dim_y;

        /* Stage 1 - Horizontal max */
        seFlags = __SE_FLAGS_default();

        seFlags.ELETYPE = __SE_ELETYPE_32BIT;
        seFlags.VECLEN  = __SE_VECLEN_16ELEMS;
        seFlags.DECDIM1 = __SE_DECDIM_DIM3;

        seParam.DECDIM1_WIDTH = inWidth;
        seParam.ICNT0 = SIMD_WIDTH;
        seParam.ICNT1 = winWidth;
        seParam.ICNT2 = inHeight >> 1;
        seParam.ICNT3 = NUM_SIMD_BLOCKS(inWidth);

        seParam.DIM1  = 1;
        seParam.DIM2  = inStride << 1;
        seParam.DIM3  = SIMD_WIDTH;

        seTemplate = __SE_SET_PARAM_4D(&seParam, &seFlags);
        *stov_ptr(uint16, (uint32_t *)((uint8_t *)pBlock + SE_PARAM_STAGE1_OFFSET)) = seTemplate;

        /* Prepare SA 0 tempate to store output */
        saFlags = __SA_FLAGS_default();

        saFlags.VECLEN    = __SA_VECLEN_16ELEMS;
        saFlags.DECDIM1   = __SA_DECDIM_DIM2;

        /* ITERATION COUNTERS */
        saParam.DECDIM1_WIDTH = outWidth;
        saParam.ICNT0 = SIMD_WIDTH;
        saParam.ICNT1 = inHeight;
        saParam.ICNT2 = NUM_SIMD_BLOCKS(outWidth);

        /* DIMENSIONS */
        saParam.DIM1  = outStride;
        saParam.DIM2  = SIMD_WIDTH;

        saTemplate = __SA_SET_PARAM_3D(&saParam, &saFlags);
        *stov_ptr(uint16, (uint32_t *)((uint8_t *)pBlock + SA_PARAM_STAGE1_OFFSET)) = saTemplate;

        /* Stage 2 - Vertical max */
        seFlags = __SE_FLAGS_default();

        seFlags.ELETYPE = __SE_ELETYPE_32BIT;
        seFlags.VECLEN  = __SE_VECLEN_16ELEMS;
        seFlags.DECDIM1 = __SE_DECDIM_DIM3;

        seParam.DECDIM1_WIDTH = outWidth;
        seParam.ICNT0 = SIMD_WIDTH;
        seParam.ICNT1 = winHeight;
        seParam.ICNT2 = outHeight;
        seParam.ICNT3 = NUM_SIMD_BLOCKS(outWidth);

        seParam.DIM1  = outStride;
        seParam.DIM2  = outStride;
        seParam.DIM3  = SIMD_WIDTH;

        seTemplate = __SE_SET_PARAM_4D(&seParam, &seFlags);
        *stov_ptr(uint16, (uint32_t *)((uint8_t *)pBlock + SE_PARAM_STAGE2_OFFSET)) = seTemplate;

        /* Prepare SA 0 tempate to store output */
        saFlags = __SA_FLAGS_default();

        saFlags.VECLEN    = __SA_VECLEN_16ELEMS;
        saFlags.DECDIM1   = __SA_DECDIM_DIM2;

        /* ITERATION COUNTERS */
        saParam.DECDIM1_WIDTH = outWidth;
        saParam.ICNT0 = SIMD_WIDTH;
        saParam.ICNT1 = outHeight;
        saParam.ICNT2 = NUM_SIMD_BLOCKS(outWidth);

        /* DIMENSIONS */
        saParam.DIM1  = outStride;
        saParam.DIM2  = SIMD_WIDTH;

        saTemplate = __SA_SET_PARAM_3D(&saParam, &saFlags);
        *stov_ptr(uint16, (uint32_t *)((uint8_t *)pBlock + SA_PARAM_STAGE2_OFFSET)) = saTemplate;

        /* Stage 3 - NMS */
        seFlags = __SE_FLAGS_default();

        seFlags.ELETYPE = __SE_ELETYPE_32BIT;
        seFlags.VECLEN  = __SE_VECLEN_16ELEMS;

        // ITERATION COUNTERS
        seParam.ICNT0 = outWidth;
        seParam.ICNT1 = outHeight;
        seParam.ICNT2 = 1;
        seParam.ICNT3 = 1;

        // DIMENSIONS IN BYTES;
        seParam.DIM1  = outStride;
        seParam.DIM2  = 0;
        seParam.DIM3  = 0;

        // SETUP TEMPLATE VECTOR BASED ON SETTINGS
        seTemplate = __SE_SET_PARAM_4D(&seParam, &seFlags);
        *stov_ptr(uint16, (uint32_t *)((uint8_t *)pBlock + SE0_PARAM_STAGE3_OFFSET)) = seTemplate;

        //Prepare SE 3 tempate to fetch Input for the 2nd loop
        seFlags = __SE_FLAGS_default();

        seFlags.ELETYPE   = __SE_ELETYPE_32BIT;
        seFlags.VECLEN    = __SE_VECLEN_16ELEMS;

        // ITERATION COUNTERS
        seParam.ICNT0 = outWidth;
        seParam.ICNT1 = outHeight;
        seParam.ICNT2 = 1;
        seParam.ICNT3 = 1;

        // DIMENSIONS IN BYTES;
        seParam.DIM1 = inStride;
        seParam.DIM2 = 0;
        seParam.DIM3 = 0;

        // SETUP TEMPLATE VECTOR BASED ON SETTINGS
        seTemplate = __SE_SET_PARAM_4D(&seParam, &seFlags);
        *stov_ptr(uint16, (uint32_t *)((uint8_t *)pBlock + SE1_PARAM_STAGE3_OFFSET)) = seTemplate;

        //Prepare SA 2 tempate to store Output for the 2nd loop
        saFlags = __SA_FLAGS_default();

        saFlags.VECLEN  = __SA_VECLEN_16ELEMS;

        // ITERATION COUNTERS
        saParam.ICNT0 = outWidth;
        saParam.ICNT1 = outHeight;
        saParam.ICNT2 = 1;

        // DIMENSIONS
        saParam.DIM1  = outStride;
        saParam.DIM2  = 0;

        // SETUP TEMPLATE VECTOR BASED ON SETTINGS
        seTemplate = __SA_SET_PARAM_3D(&saParam, &saFlags);
        *stov_ptr(uint16, (uint32_t *)((uint8_t *)pBlock + SA_PARAM_STAGE3_OFFSET)) = seTemplate;

    }

    return (status);
}

VXLIB_STATUS VXLIB_nms_MxN_i32s_o8u_kernel
(
  const int32_t              src[restrict],
  const VXLIB_bufParams2D_t *src_addr,
  uint8_t                    dst[restrict],
  const VXLIB_bufParams2D_t *dst_addr,
  int32_t                    scratch1[restrict],
  int32_t                    scratch2[restrict],
  uint8_t                    winWidth,
  uint8_t                    winHeight,
  int32_t                    threshold,
  void                      *pBlock
)
{
    VXLIB_STATUS  status = VXLIB_SUCCESS;

    {
        __STRM_TEMPLATE seTemplate;
        __STRM_TEMPLATE saTemplate;

        int16 vMaxA, vMaxB, vKMax;
        int16 vThres, v255, vZero;

        __vpred vpStore;

        int32_t *pIn1;
        int32_t *pIn2;
        int32_t *pScratch1;
        int32_t *pScratch2;
        int32_t *pPix;
        uint8_t *pOut1;

        int32_t blkX, blkY, x, y;
        int32_t numBlocks, numRows;

        int32_t bit_depth_in  = VXLIB_sizeof(src_addr->data_type);
        int32_t inStride      = src_addr->stride_y  / bit_depth_in;

        int32_t inWidth   = src_addr->dim_x;
        int32_t inHeight  = src_addr->dim_y;

        int32_t outWidth  = dst_addr->dim_x;
        int32_t outHeight = dst_addr->dim_y;

        pIn1 = (int32_t *)src;
        pIn2 = (int32_t *)src + inStride;

        seTemplate = *stov_ptr(uint16, (uint32_t *)((uint8_t *)pBlock + SE_PARAM_STAGE1_OFFSET));
        __SE0_OPEN((void *)pIn1, seTemplate);
        __SE1_OPEN((void *)pIn2, seTemplate);

#ifdef _DISPLAY_PARAMS
        displaySEParam((void *)pIn1, seTemplate, PARAMV_SE0);
        displaySEParam((void *)pIn2, seTemplate, PARAMV_SE1);
#endif

        pScratch1 = (int32_t *)scratch1;

        saTemplate = *stov_ptr(uint16, (uint32_t *)((uint8_t *)pBlock + SA_PARAM_STAGE1_OFFSET));
        __SA0_OPEN(saTemplate);

#ifdef _DISPLAY_PARAMS
        displaySAParam((void *)pScratch1, saTemplate, PARAMV_SA0);
#endif

        numBlocks = NUM_SIMD_BLOCKS(inWidth);
        numRows   = inHeight >> 1;

        vMaxA = (int16)(INT_MIN);
        vMaxB = (int16)(INT_MIN);
        vKMax = (int16)(INT_MIN);

#pragma MUST_ITERATE(1,,)
        for(blkX = 0; blkX < numBlocks; blkX++)
        {
#pragma MUST_ITERATE(1,,)
          for(blkY = 0; blkY < numRows; blkY++)
          {
            vMaxA = __max(__SE0ADV(int16), vKMax);
            vMaxA = __max(__SE0ADV(int16), vMaxA);
            vMaxA = __max(__SE0ADV(int16), vMaxA);
            vMaxA = __max(__SE0ADV(int16), vMaxA);
            vMaxA = __max(__SE0ADV(int16), vMaxA);
            vMaxA = __max(__SE0ADV(int16), vMaxA);
            vMaxA = __max(__SE0ADV(int16), vMaxA);

            vpStore = __SA0_VPRED(int16);
            __vstore_pred(vpStore, __SA0ADV(int16, pScratch1), vMaxA);

            vMaxB = __max(__SE1ADV(int16), vKMax);
            vMaxB = __max(__SE1ADV(int16), vMaxB);
            vMaxB = __max(__SE1ADV(int16), vMaxB);
            vMaxB = __max(__SE1ADV(int16), vMaxB);
            vMaxB = __max(__SE1ADV(int16), vMaxB);
            vMaxB = __max(__SE1ADV(int16), vMaxB);
            vMaxB = __max(__SE1ADV(int16), vMaxB);

            vpStore = __SA0_VPRED(int16);
            __vstore_pred(vpStore, __SA0ADV(int16, pScratch1), vMaxB);
          }
        }

        __SA0_CLOSE();
        __SE1_CLOSE();
        __SE0_CLOSE();

        pScratch1 = (int32_t *)scratch1;

        seTemplate = *stov_ptr(uint16, (uint32_t *)((uint8_t *)pBlock + SE_PARAM_STAGE2_OFFSET));
        __SE0_OPEN((void *)pScratch1, seTemplate);

#ifdef _DISPLAY_PARAMS
        displaySEParam((void *)pScratch1, seTemplate, PARAMV_SE0);
#endif

        pScratch2 = (int32_t *)scratch2;

        saTemplate = *stov_ptr(uint16, (uint32_t *)((uint8_t *)pBlock + SA_PARAM_STAGE2_OFFSET));
        __SA0_OPEN(saTemplate);

#ifdef _DISPLAY_PARAMS
        displaySAParam((void *)pScratch2, saTemplate, PARAMV_SA0);
#endif

        numBlocks = NUM_SIMD_BLOCKS(outWidth);
        vKMax = (int16)(INT_MIN);

#pragma MUST_ITERATE(1,,)
        for(blkX = 0; blkX < numBlocks; blkX++)
        {
#pragma MUST_ITERATE(1,,)
          for(blkY = 0; blkY < outHeight; blkY++)
          {
            vMaxA = __max(__SE0ADV(int16), vKMax);
            vMaxA = __max(__SE0ADV(int16), vMaxA);
            vMaxA = __max(__SE0ADV(int16), vMaxA);
            vMaxA = __max(__SE0ADV(int16), vMaxA);
            vMaxA = __max(__SE0ADV(int16), vMaxA);
            vMaxA = __max(__SE0ADV(int16), vMaxA);
            vMaxA = __max(__SE0ADV(int16), vMaxA);

            vpStore = __SA0_VPRED(int16);
            __vstore_pred(vpStore, __SA0ADV(int16, pScratch2), vMaxA);

          }
        }

        __SA0_CLOSE();
        __SE0_CLOSE();

        /* Read template and open stream 0 and 1 for the third loop */
        seTemplate = *stov_ptr(uint16, (uint32_t *)((uint8_t*)pBlock + SE0_PARAM_STAGE3_OFFSET));
        __SE0_OPEN((void*)pScratch2, seTemplate);

#ifdef _DISPLAY_PARAMS
        displaySEParam((void *)pScratch2, seTemplate, PARAMV_SE0);
#endif

        pPix = (int32_t *)&src[((winHeight - 1)/2) * inStride + (winWidth - 1)/2];

        seTemplate = *stov_ptr(uint16, (uint32_t *)((uint8_t*)pBlock + SE1_PARAM_STAGE3_OFFSET));
        __SE1_OPEN((void*)pPix, seTemplate);

#ifdef _DISPLAY_PARAMS
        displaySEParam((void *)pPix, seTemplate, PARAMV_SE1);
#endif

        pOut1 = (uint8_t *)dst;

        /* Read template and open address gen 0 for the third loop */
        saTemplate = *stov_ptr(uint16, (uint32_t *)((uint8_t*)pBlock + SA_PARAM_STAGE3_OFFSET));
        __SA0_OPEN(saTemplate);

#ifdef _DISPLAY_PARAMS
        displaySAParam((void *)pOut1, saTemplate, PARAMV_SA0);
#endif

        vThres = (int16)(threshold);
        v255   = (int16)(255);
        vZero  = (int16)(0);

#pragma MUST_ITERATE(1,,)
        for(y = 0; y < outHeight; y++)
        {
#pragma MUST_ITERATE(1,,)
          for (x = 0; x < outWidth; x+=SIMD_WIDTH)
          {
            int16 vMax0 = __SE0ADV(int16);
            int16 vPix0 = __SE1ADV(int16);

            __vpred pred0 = __cmp_eq_pred(vPix0, vMax0);

            pred0 = __and_ppp(pred0, __cmp_gt_pred(vPix0, vThres));

            vMax0 = __select(pred0, v255, vZero);

            __vpred vpStore0 = __SA0_VPRED(uint16);
            __vstore_pred_pack_byte(vpStore0, __SA0ADV(uchar16, (uint8_t *)pOut1), __as_uint16(vMax0));
          }
        }

        __SA0_CLOSE();
        __SE0_CLOSE();
        __SE1_CLOSE();

    }

    return (status);
}
