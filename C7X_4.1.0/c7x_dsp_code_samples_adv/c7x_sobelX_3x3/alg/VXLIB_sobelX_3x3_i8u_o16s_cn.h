/*
* module name       : c7x_sobelX_3x3
*
* module descripton : Computes Sobel X gradients across 3x3 window
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#ifndef VXLIB_SOBELX_3X3_I8U_O16S_CN_H_
#define VXLIB_SOBELX_3X3_I8U_O16S_CN_H_ 1

#include "VXLIB_types.h"

VXLIB_STATUS    VXLIB_sobelX_3x3_i8u_o16s_cn(uint8_t src[],
                                     VXLIB_bufParams2D_t * src_addr,
                                     int16_t dst[],
                                     VXLIB_bufParams2D_t * dst_addr);

VXLIB_STATUS    VXLIB_sobelX_3x3_i8u_o16s_checkParams_cn(uint8_t src[],
                                                 VXLIB_bufParams2D_t * src_addr,
                                                 int16_t dst[],
                                                 VXLIB_bufParams2D_t * dst_addr);

#endif
