/*
* module name       : c7x_integral_image
*
* module descripton : Computes integral image
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#ifndef VXLIB_INTEGRALIMAGE_I8U_O32U_CN_H_
#define VXLIB_INTEGRALIMAGE_I8U_O32U_CN_H_ 1

#include "VXLIB_types.h"

VXLIB_STATUS    VXLIB_integralImage_i8u_o32u_cn(uint8_t src0[],
                                        VXLIB_bufParams2D_t * src0_addr,
                                        uint32_t dst[],
                                        VXLIB_bufParams2D_t * dst_addr);

VXLIB_STATUS    VXLIB_integralImage_i8u_o32u_checkParams_cn(uint8_t src0[],
                                                    VXLIB_bufParams2D_t * src0_addr,
                                                    uint32_t dst[],
                                                    VXLIB_bufParams2D_t * dst_addr);

#endif
