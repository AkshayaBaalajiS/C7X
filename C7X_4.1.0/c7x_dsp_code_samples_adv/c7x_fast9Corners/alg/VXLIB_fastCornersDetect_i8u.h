/*
* module name       : c7x_fast9Corners
*
* module descripton : Computes FAST9 corners
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#ifndef VXLIB_FASTCORNERSDETECT_I8U_H_
#define VXLIB_FASTCORNERSDETECT_I8U_H_ 1

#include "VXLIB_types.h"

#define VXLIB_FASTCORNERSDETECT_I8U_PBLOCK_SIZE (1280) 

VXLIB_STATUS    VXLIB_fastCornersDetect_i8u_init(const uint8_t src[],
                                         const VXLIB_bufParams2D_t * src_addr,
                                         uint32_t corners[],
                                         uint32_t corners_capacity,
                                         uint8_t strength_thresh,
                                         uint32_t *num_corners,
                                         uint8_t scratch[],
                                         void *pBlock);

VXLIB_STATUS    VXLIB_fastCornersDetect_i8u_kernel(const uint8_t src[],
                                         const VXLIB_bufParams2D_t * src_addr,
                                         uint32_t corners[],
                                         uint32_t corners_capacity,
                                         uint8_t strength_thresh,
                                         uint32_t *num_corners,
                                         uint8_t scratch[],
                                         void *pBlock);

VXLIB_STATUS    VXLIB_fastCornersDetect_i8u_checkParams(const uint8_t src[],
                                                     const VXLIB_bufParams2D_t * src_addr,
                                                     const uint32_t corners[],
                                                     uint32_t corners_capacity,
                                                     uint8_t strength_thresh,
                                                     const uint32_t *num_corners,
                                                     const uint8_t scratch[],
                                                     void *pBlock);


#endif
