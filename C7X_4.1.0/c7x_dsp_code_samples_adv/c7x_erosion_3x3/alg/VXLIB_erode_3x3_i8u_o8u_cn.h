/*
* module name       : c7x_erosion_3x3
*
* module descripton : 3x3 greyscale erosion
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#ifndef VXLIB_ERODE_3X3_I8U_O8U_CN_H_
#define VXLIB_ERODE_3X3_I8U_O8U_CN_H_ 1

#include "VXLIB_types.h"

VXLIB_STATUS    VXLIB_erode_3x3_i8u_o8u_cn(uint8_t src[],
                                     VXLIB_bufParams2D_t * src_addr,
                                     uint8_t dst[],
                                     VXLIB_bufParams2D_t * dst_addr);

VXLIB_STATUS    VXLIB_erode_3x3_i8u_o8u_checkParams_cn(uint8_t src[],
                                                 VXLIB_bufParams2D_t * src_addr,
                                                 uint8_t dst[],
                                                 VXLIB_bufParams2D_t * dst_addr);

#endif
