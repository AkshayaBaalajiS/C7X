/*
* module name       : c7x_maxPooling_3x3_skip2
*
* module descripton : Max Pooling, 3x3 window, skip 2 positions horz/vert
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#ifndef VXLIB_CNNMAXPOOLING_3x3_SKIP2_I8U_O8U_CN_H_
#define VXLIB_CNNMAXPOOLING_3x3_SKIP2_I8U_O8U_CN_H_ 1

#include "VXLIB_types.h"

VXLIB_STATUS VXLIB_cnnMaxPooling_3x3_skip2_i8u_o8u_cn
(
  uint8_t   src[],
  VXLIB_bufParams3D_t srcAddr[],
  uint8_t   dst[],
  VXLIB_bufParams3D_t dstAddr[],
  uint16_t  kernelW,
  uint16_t  kernelH,
  uint16_t  strideW,
  uint16_t  strideH
);
#endif
