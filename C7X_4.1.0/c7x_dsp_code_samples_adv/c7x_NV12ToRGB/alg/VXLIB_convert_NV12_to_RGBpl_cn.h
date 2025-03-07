/*
* module name       : c7x_NV12ToRGB
*
* module descripton : Converts NV12 to RGB planar format
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#ifndef VXLIB_CONVERT_NV12_TO_RGBPL_CN_H_
#define VXLIB_CONVERT_NV12_TO_RGBPL_CN_H_ 1

#include "VXLIB_types.h"

VXLIB_STATUS VXLIB_convert_NV12_to_RGBpl_cn
(
    uint8_t *yData,
    VXLIB_bufParams2D_t *y_addr,
    uint8_t *cbcrData,
    VXLIB_bufParams2D_t *cbcr_addr,
    uint8_t *rgbData,
    VXLIB_bufParams3D_t *rgb_addr,
    const int16_t coeff[5]
);

#endif /* VXLIB_CONVERT_NV12_TO_RGBPL_CN_H_ */
