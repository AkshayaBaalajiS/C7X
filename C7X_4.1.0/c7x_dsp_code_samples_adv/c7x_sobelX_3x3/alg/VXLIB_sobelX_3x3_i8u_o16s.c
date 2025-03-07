/*
* module name       : c7x_sobelX_3x3
*
* module descripton : Computes Sobel X gradients across 3x3 window
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/
#include "VXLIB_sobelX_3x3_i8u_o16s.h"

#ifdef _DISPLAY_PARAMS
#include "paramv.h"
#endif

#define SIMD_WIDTH_SHIFT        (5) /* 2^5 = 32 16b elements in a 512b vector */
#define SIMD_WIDTH              (1 << SIMD_WIDTH_SHIFT)
#define SIMD_WIDTH_RND          (SIMD_WIDTH >> 1)
#define NUM_SIMD_BLOCKS(width)  (((width) >> SIMD_WIDTH_SHIFT) + (((width) - (((width) >> SIMD_WIDTH_SHIFT) << SIMD_WIDTH_SHIFT)) > 0 ? 1 : 0))

#define CONFIG_PARAM_BASE  (0x0000)
#define SE0_PARAM_OFFSET   (CONFIG_PARAM_BASE)
#define SE1_PARAM_OFFSET   (SE0_PARAM_OFFSET + SE_PARAM_SIZE)
#define SA0_PARAM_OFFSET   (SE1_PARAM_OFFSET + SE_PARAM_SIZE)

VXLIB_STATUS VXLIB_sobelX_3x3_i8u_o16s_init
(
  const uint8_t src[restrict],
  const VXLIB_bufParams2D_t *srcAddr,
  int16_t dst[restrict],
  const VXLIB_bufParams2D_t *dstAddr,
  void *pBlock
)
{
  __STRM_TEMPLATE seTemplate;
  __STRM_TEMPLATE saTemplate;

  __SE_FLAGS seFlags;
  __SA_FLAGS saFlags;

  __STRM_PARAM_4D seParam;
  __STRM_PARAM_3D saParam;

  int32_t stride_y;
  int32_t numLines, inWidth;
  int32_t numBytes;

  inWidth  = srcAddr->dim_x;
  numLines = srcAddr->dim_y >> 1;

  seFlags = __SE_FLAGS_default();

  seFlags.ELETYPE = __SE_ELETYPE_8BIT;
  seFlags.PROMOTE = __SE_PROMOTE_2X_ZEROEXT;
  seFlags.VECLEN  = __SE_VECLEN_32ELEMS;
  seFlags.DECDIM1 = __SE_DECDIM_DIM3;

  seParam.DECDIM1_WIDTH = inWidth;
  seParam.ICNT0 = SIMD_WIDTH;
  seParam.ICNT1 = 2;
  seParam.ICNT2 = numLines;
  seParam.ICNT3 = NUM_SIMD_BLOCKS(inWidth);

  numBytes = VXLIB_sizeof(srcAddr->data_type);
  stride_y = srcAddr->stride_y / numBytes;

  seParam.DIM1 = 2;
  seParam.DIM2 = stride_y << 1;
  seParam.DIM3 = SIMD_WIDTH;

  /* SETUP SE TEMPLATE */
  seTemplate = __SE_SET_PARAM_4D(&seParam, &seFlags);
  *stov_ptr(__STRM_TEMPLATE, (uint32_t*)((uint8_t *)pBlock + SE0_PARAM_OFFSET)) = seTemplate;

  /* SETUP SE TEMPLATE */
  seTemplate = __SE_SET_PARAM_4D(&seParam, &seFlags);
  *stov_ptr(__STRM_TEMPLATE, (uint32_t*)((uint8_t *)pBlock + SE1_PARAM_OFFSET)) = seTemplate;

  numBytes = VXLIB_sizeof(dstAddr->data_type);
  stride_y = dstAddr->stride_y / numBytes;

  saFlags = __SA_FLAGS_default();

  /* Prepare SA 0 tempate to store output */
  saFlags.VECLEN  = __SA_VECLEN_32ELEMS;
  saFlags.DECDIM1 = __SA_DECDIM_DIM2;

  /* ITERATION COUNTERS */
  saParam.DECDIM1_WIDTH = dstAddr->dim_x;
  saParam.ICNT0 = SIMD_WIDTH;
  saParam.ICNT1 = dstAddr->dim_y;
  saParam.ICNT2 = NUM_SIMD_BLOCKS(dstAddr->dim_x);

  /* DIMENSIONS */
  saParam.DIM1  = stride_y;
  saParam.DIM2  = SIMD_WIDTH;

  saTemplate = __SA_SET_PARAM_3D(&saParam, &saFlags);
  *stov_ptr(__STRM_TEMPLATE, (uint32_t*)((uint8_t *)pBlock + SA0_PARAM_OFFSET)) = saTemplate;

  return (VXLIB_SUCCESS);
}


VXLIB_STATUS VXLIB_sobelX_3x3_i8u_o16s_kernel
(
  const uint8_t src[restrict],
  const VXLIB_bufParams2D_t *srcAddr,
  int16_t dst[restrict],
  const VXLIB_bufParams2D_t *dstAddr,
  void *pBlock
)
{
  __STRM_TEMPLATE seTemplate;
  __STRM_TEMPLATE saTemplate;

  int32_t row, col;
  int32_t numRows, numBlocks;
  int32_t inStride;
  int32_t numBytes;

  uint8_t *restrict pIn0;
  uint8_t *restrict pIn1;

  int16_t *restrict pOut;

  short32 vSum1, vSum2, vOutLo, vOutHi, vDiff1, vDiff2;

  numBytes = VXLIB_sizeof(srcAddr->data_type);
  inStride = srcAddr->stride_y / numBytes;

  pIn0 = (uint8_t *)src;
  pIn1 = (uint8_t *)src + inStride;

  seTemplate = *stov_ptr(__STRM_TEMPLATE, (uint32_t*)((uint8_t *)pBlock + SE0_PARAM_OFFSET));
  __SE0_OPEN((void *)pIn0, seTemplate);

#ifdef _DISPLAY_PARAMS
  displaySEParam((void *)pIn0, seTemplate, PARAMV_SE0);
#endif

  seTemplate = *stov_ptr(__STRM_TEMPLATE, (uint32_t*)((uint8_t *)pBlock + SE1_PARAM_OFFSET));
  __SE1_OPEN((void *)pIn1, seTemplate);

#ifdef _DISPLAY_PARAMS
  displaySEParam((void *)pIn1, seTemplate, PARAMV_SE1);
#endif

  saTemplate = *stov_ptr(__STRM_TEMPLATE, (uint32_t*)((uint8_t *)pBlock + SA0_PARAM_OFFSET));
  __SA0_OPEN(saTemplate);

  pOut = (int16_t *)dst;

#ifdef _DISPLAY_PARAMS
  displaySAParam((void *)pOut, saTemplate, PARAMV_SA0);
#endif

  numBlocks  = NUM_SIMD_BLOCKS(srcAddr->dim_x);
  numRows    = srcAddr->dim_y >> 1;

#pragma MUST_ITERATE(1,,)
  for (col = 0; col < numBlocks; col++)
  {
#pragma MUST_ITERATE(1,,)
    for (row = 0; row < numRows; row++)
    {
      short32 vRow0Col01 = __SE0ADV(short32);
      short32 vRow0Col2x = __SE0ADV(short32);

      vDiff1  = vRow0Col2x - vRow0Col01;
      vSum1   = vDiff2 + vDiff1;
      vOutLo  = vSum1  + vSum2;

      if(row) {
        vpred vpStore = __SA0_VPRED(short32);
        __vstore_pred(vpStore, __SA0ADV(short32, pOut), vOutLo);
      }

      short32 vRow1Col01 = __SE1ADV(short32);
      short32 vRow1Col2x = __SE1ADV(short32);

      vDiff2  = vRow1Col2x - vRow1Col01;
      vSum2   = vDiff1 + vDiff2;
      vOutHi  = vSum1  + vSum2;

      if(row) {
        vpred vpStore = __SA0_VPRED(short32);
        __vstore_pred(vpStore, __SA0ADV(short32, pOut), vOutHi);
      }
    }
  }

  __SA0_CLOSE();
  __SE1_CLOSE();
  __SE0_CLOSE();

  return (VXLIB_SUCCESS);
}

#if (!defined(VXLIB_REMOVE_CHECK_PARAMS) && !defined(VXLIB_SOBELX_3x3_I8U_O16S_REMOVE_CHECK_PARAMS)) || (defined(VXLIB_CHECK_PARAMS)) || (defined(VXLIB_SOBELX_3x3_I8U_O16S_CHECK_PARAMS))

VXLIB_STATUS VXLIB_sobelX_3x3_i8u_o16s_checkParams
(
  const uint8_t src[],
  const VXLIB_bufParams2D_t *src_addr,
  const int16_t dst[],
  const VXLIB_bufParams2D_t *dst_addr
)
{
    return (VXLIB_SUCCESS);
}

#endif
