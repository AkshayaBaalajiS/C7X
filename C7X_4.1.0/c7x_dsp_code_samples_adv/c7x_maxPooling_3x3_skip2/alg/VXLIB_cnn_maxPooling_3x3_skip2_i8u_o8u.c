/*
* module name       : c7x_maxPooling_3x3_skip2
*
* module descripton : Max Pooling, 3x3 window, skip 2 positions horz/vert
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#include "VXLIB_cnn_maxPooling_3x3_skip2_i8u_o8u.h"

#ifdef _DISPLAY_PARAMS
#include "paramv.h"
#endif

#define VERSION1 (0) //Horizontal access
#define VERSION4 (1) //Horizontal with scalar merge

/* Write the SE param at offset of 0 from the base address */
#define SE0_PARAM_BASE (0x0000)

#define SE0_PARAM_OFFSET   (SE0_PARAM_BASE)
#define SE1_PARAM_OFFSET   (SE0_PARAM_OFFSET + SE_PARAM_SIZE)
#define SA0_PARAM_OFFSET   (SE1_PARAM_OFFSET + SE_PARAM_SIZE)

#define SIMD_WIDTH_SHIFT        (6) /* 2^6 = 64-8b elements in a 512b vector */
#define SIMD_WIDTH              (1 << SIMD_WIDTH_SHIFT)
#define SIMD_WIDTH_RND          (SIMD_WIDTH >> 1)
#define NUM_SIMD_BLOCKS(width)  (((width) >> SIMD_WIDTH_SHIFT) + (((width) - (((width) >> SIMD_WIDTH_SHIFT) << SIMD_WIDTH_SHIFT)) > 0 ? 1 : 0))

#define SIMD_WIDTH_SHIFT_OUT        (5) /* 2^5 = 32-8b elements in a 256b vector */
#define SIMD_WIDTH_OUT              (1 << SIMD_WIDTH_SHIFT_OUT)
#define SIMD_WIDTH_RND_OUT          (SIMD_WIDTH_OUT >> 1)
#define NUM_SIMD_BLOCKS_OUT(width)  (((width) >> SIMD_WIDTH_SHIFT_OUT) + (((width) - (((width) >> SIMD_WIDTH_SHIFT_OUT) << SIMD_WIDTH_SHIFT_OUT)) > 0 ? 1 : 0))

#define NUM_BLOCKS(width, stride) (((width) / stride) + (((width) - (((width) / stride) * stride)) > 0 ? 1 : 0))

VXLIB_STATUS VXLIB_cnnMaxPooling_3x3_skip2_i8u_o8u_init
(
  uint8_t   src[],
  const VXLIB_bufParams3D_t *srcAddr,
  uint8_t   dst[],
  const VXLIB_bufParams3D_t *dstAddr,
  void *pBlock
)
{
  __STRM_TEMPLATE seTemplate;
  __STRM_TEMPLATE saTemplate;

  __SE_FLAGS seFlags;
  __SA_FLAGS saFlags;

  __STRM_PARAM_5D seParam;
  __STRM_PARAM_4D saParam;

  int32_t stride_y, stride_z;
  int32_t numLines, numCh, inWidth, outWidth, outHeight;
  int32_t numBytes;

  inWidth  = srcAddr->dim_x;
  numLines = dstAddr->dim_y;
  numCh    = srcAddr->dim_z;

  seFlags = __SE_FLAGS_default();

  seFlags.ELETYPE = __SE_ELETYPE_8BIT;
  seFlags.VECLEN  = __SE_VECLEN_64ELEMS;
  seFlags.DECDIM1 = __SE_DECDIM_DIM2;

  seParam.DECDIM1_WIDTH = inWidth;
  seParam.ICNT0 = 64;
  seParam.ICNT1 = 2;
  seParam.ICNT2 = NUM_BLOCKS(inWidth, 62);
  seParam.ICNT3 = numLines;
  seParam.ICNT4 = numCh;

  numBytes = VXLIB_sizeof(srcAddr->data_type);
  stride_y = srcAddr->stride_y / numBytes;
  stride_z = srcAddr->stride_z / numBytes;

  seParam.DIM1 = stride_y << 1;
  seParam.DIM2 = SIMD_WIDTH - 2;
  seParam.DIM3 = stride_y << 1;
  seParam.DIM4 = stride_z;

  /* SETUP SE TEMPLATE */
  seTemplate = __SE_SET_PARAM_5D(&seParam, &seFlags);
  *stov_ptr(__STRM_TEMPLATE, (uint32_t*)((uint8_t *)pBlock + SE0_PARAM_OFFSET)) = seTemplate;

  seFlags = __SE_FLAGS_default();

  seFlags.ELETYPE = __SE_ELETYPE_8BIT;
  seFlags.VECLEN  = __SE_VECLEN_64ELEMS;
  seFlags.DECDIM1 = __SE_DECDIM_DIM1;

  seParam.DECDIM1_WIDTH = inWidth;
  seParam.ICNT0 = 64;
  seParam.ICNT1 = NUM_BLOCKS(inWidth, 62);
  seParam.ICNT2 = numLines;
  seParam.ICNT3 = numCh;
  seParam.ICNT4 = 1;

  numBytes = VXLIB_sizeof(srcAddr->data_type);
  stride_y = srcAddr->stride_y / numBytes;
  stride_z = srcAddr->stride_z / numBytes;

  seParam.DIM1 = SIMD_WIDTH - 2;
  seParam.DIM2 = stride_y << 1;
  seParam.DIM3 = stride_z;
  seParam.DIM4 = 0;

  /* SETUP SE TEMPLATE */
  seTemplate = __SE_SET_PARAM_5D(&seParam, &seFlags);
  *stov_ptr(__STRM_TEMPLATE, (uint32_t*)((uint8_t *)pBlock + SE1_PARAM_OFFSET)) = seTemplate;

  numBytes = VXLIB_sizeof(dstAddr->data_type);
  stride_y = dstAddr->stride_y / numBytes;
  stride_z = dstAddr->stride_z / numBytes;

  saFlags = __SA_FLAGS_default();

  /* Prepare SA 0 tempate to store output */
  saFlags.VECLEN  = __SA_VECLEN_32ELEMS;
  saFlags.DECDIM1 = __SA_DECDIM_DIM1;

  outWidth  = dstAddr->dim_x;
  outHeight = dstAddr->dim_y;

  /* ITERATION COUNTERS */
  saParam.DECDIM1_WIDTH = outWidth;
  saParam.ICNT0 = SIMD_WIDTH_OUT - 1;
  saParam.ICNT1 = NUM_BLOCKS(outWidth, 31);
  saParam.ICNT2 = outHeight;
  saParam.ICNT3 = dstAddr->dim_z;

  /* DIMENSIONS */
  saParam.DIM1  = SIMD_WIDTH_OUT - 1;
  saParam.DIM2  = stride_y;
  saParam.DIM3  = stride_z;

  saTemplate = __SA_SET_PARAM_4D(&saParam, &saFlags);
  *stov_ptr(__STRM_TEMPLATE, (uint32_t*)((uint8_t *)pBlock + SA0_PARAM_OFFSET)) = saTemplate;

  return (VXLIB_SUCCESS);
}

VXLIB_STATUS VXLIB_cnnMaxPooling_3x3_skip2_i8u_o8u_kernel
(
  uint8_t   src[],
  const VXLIB_bufParams3D_t *srcAddr,
  uint8_t   dst[],
  const VXLIB_bufParams3D_t *dstAddr,
  void *pBlock
)
{

  __STRM_TEMPLATE seTemplate;
  __STRM_TEMPLATE saTemplate;

  int32_t row, col, ch;
  int32_t numRows, numCh, outWidth;
  int32_t inStride;
  int32_t numBytes, numBlocks;

  uint8_t *restrict pIn0;
  uint8_t *restrict pIn1;

  uint8_t *restrict pOut;

  numBytes = VXLIB_sizeof(srcAddr->data_type);
  inStride = srcAddr->stride_y / numBytes;

  pIn0 = src;
  pIn1 = src + inStride;

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

  pOut = dst;

#ifdef _DISPLAY_PARAMS
  displaySAParam((void *)pOut, saTemplate, PARAMV_SA0);
#endif

  outWidth = dstAddr->dim_x;
  numRows  = dstAddr->dim_y;
  numCh    = srcAddr->dim_z;

  numBlocks = NUM_BLOCKS(outWidth, 31);

#pragma MUST_ITERATE(1,,)
  for(ch = 0; ch < numCh; ch++)
  {
#pragma MUST_ITERATE(1,,)
    for (row = 0; row < numRows; row++)
    {
#pragma MUST_ITERATE(1,,)
      for (col = 0; col < numBlocks; col++)
      {
         uchar64 vMax0, vOut;
         uchar64 vIn0, vIn1, vIn2;
         vpred vpStore;

         vIn0 = __SE0ADV(uchar64);
         vIn1 = __SE1ADV(uchar64);
         vIn2 = __SE0ADV(uchar64);

         vMax0 = __max(vIn0, vIn1);
         vMax0 = __max(vMax0, vIn2);

         long8 vMax2 = __shift_right_full(__as_long8(vMax0), (uchar)(8));
         long8 vMax3 = __shift_right_full(vMax2, (uchar)(8));

         vMax0 = __max(vMax0, __as_uchar64(vMax2));
         vMax0 = __max(vMax0, __as_uchar64(vMax3));

         vOut    = __deal_stride2(vMax0);

         vpStore = __SA0_VPRED(uchar32);
         __vstore_pred(vpStore, __SA0ADV(uchar32, pOut), vOut.lo);

      }
    }
  }

  __SA0_CLOSE();
  __SE1_CLOSE();
  __SE0_CLOSE();

  return (VXLIB_SUCCESS);
}
