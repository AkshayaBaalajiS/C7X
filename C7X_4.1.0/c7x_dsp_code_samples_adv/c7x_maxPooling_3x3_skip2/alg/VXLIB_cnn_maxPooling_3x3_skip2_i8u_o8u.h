/*
* module name       : c7x_maxPooling_3x3_skip2
*
* module descripton : Max Pooling, 3x3 window, skip 2 positions horz/vert
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#ifndef VXLIB_CNNMAXPOOLING_3x3_SKIP2_I8U_O8U_H_
#define VXLIB_CNNMAXPOOLING_3x3_SKIP2_I8U_O8U_H_ 1

#include "VXLIB_types.h"

#define VXLIB_CNNMAXPOOLING_3x3_SKIP2_I8U_O8U_PBLOCK_SIZE (256)

VXLIB_STATUS VXLIB_cnnMaxPooling_3x3_skip2_i8u_o8u_init
(
  uint8_t   src[],
  const VXLIB_bufParams3D_t *srcAddr,
  uint8_t   dst[],
  const VXLIB_bufParams3D_t *dstAddr,
  void *pBlock
);

VXLIB_STATUS VXLIB_cnnMaxPooling_3x3_skip2_i8u_o8u_kernel
(
  uint8_t   src[],
  const VXLIB_bufParams3D_t *srcAddr,
  uint8_t   dst[],
  const VXLIB_bufParams3D_t *dstAddr,
  void *pBlock
);
#endif
