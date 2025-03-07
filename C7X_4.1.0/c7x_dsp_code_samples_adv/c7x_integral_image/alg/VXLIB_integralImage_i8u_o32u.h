/*
* module name       : c7x_integral_image
*
* module descripton : Computes integral image
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#ifndef VXLIB_INTEGRALIMAGE_I8U_O32U_H_
#define VXLIB_INTEGRALIMAGE_I8U_O32U_H_ 1

#include "VXLIB_types.h"

#define VXLIB_INTEGRALIMAGE_I8U_O32U_PBLOCK_SIZE (512)
#define CACHE_LINE_SIZE (32)

VXLIB_STATUS VXLIB_integralImage_i8u_o32u_init(void *src,
                                               VXLIB_bufParams2D_t *src_addr,
                                               void *dst,
                                               VXLIB_bufParams2D_t *dst_addr,
                                               uint32_t *prevRow,
                                               uint32_t *prevCol,
                                               uint32_t *prevRowUpdate,
                                               void *pBlock);

VXLIB_STATUS VXLIB_integralImage_i8u_o32u_kernel(void *src,
                                                 VXLIB_bufParams2D_t *src_addr,
                                                 void *dst,
                                                 VXLIB_bufParams2D_t *dst_addr,
                                                 uint32_t *prevRow,
                                                 uint32_t *prevCol,
                                                 uint32_t *prevRowUpdate,
                                                 void *pBlock);

VXLIB_STATUS VXLIB_integralImage_i8u_o32u_checkParams(void *src,
                                                      VXLIB_bufParams2D_t *src_addr,
                                                      void *dst,
                                                      VXLIB_bufParams2D_t *dst_addr,
                                                      uint32_t *prevRow,
                                                      uint32_t *prevCol,
                                                      uint32_t *prevRowUpdate,
                                                      void *pBlock);
#endif
