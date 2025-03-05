/*
* module name       : c7x_fast9Corners
*
* module descripton : Computes FAST9 corners
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#ifndef VXLIB_FASTCORNERSDETECT_I8U_CN_H_
#define VXLIB_FASTCORNERSDETECT_I8U_CN_H_ 1

#include "VXLIB_types.h"

VXLIB_STATUS    VXLIB_fastCornersDetect_i8u_cn(uint8_t src[],
                                      VXLIB_bufParams2D_t * src_addr,
                                      uint16_t corners[],
                                      uint32_t corners_capacity,
                                      uint8_t strength_thresh,
                                      uint32_t *num_corners);

VXLIB_STATUS    VXLIB_fastCornersDetect_i8u_checkParams_cn(uint8_t src[],
                                                  VXLIB_bufParams2D_t * src_addr);

#endif
