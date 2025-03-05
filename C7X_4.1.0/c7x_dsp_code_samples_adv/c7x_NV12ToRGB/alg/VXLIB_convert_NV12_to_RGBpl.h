/*
* module name       : c7x_NV12ToRGB
*
* module descripton : Converts NV12 to RGB planar format
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#ifndef VXLIB_CONVERT_NV12_TO_RGBPL_H_
#define VXLIB_CONVERT_NV12_TO_RGBPL_H_ 1

#include "VXLIB_types.h"

#define VXLIB_CONVERT_NV12_TO_RGBPL_PBLOCK_SIZE (512)

VXLIB_STATUS VXLIB_convert_NV12_to_RGBpl_init
(
    uint8_t *yData,
    VXLIB_bufParams2D_t *y_addr,
    uint8_t *cbcrData,
    VXLIB_bufParams2D_t *cbcr_addr,
    uint8_t *rgbData,
    VXLIB_bufParams3D_t *rgb_addr,
    const int16_t coeff[5],
    void *pBlock
);

VXLIB_STATUS VXLIB_convert_NV12_to_RGBpl_kernel
(
    uint8_t *yData,
    VXLIB_bufParams2D_t *y_addr,
    uint8_t *cbcrData,
    VXLIB_bufParams2D_t *cbcr_addr,
    uint8_t *rgbData,
    VXLIB_bufParams3D_t *rgb_addr,
    const int16_t coeff[5],
    void *pBlock
);

VXLIB_STATUS VXLIB_convert_NV12_to_RGBpl_checkParams
(
    uint8_t *yData,
    VXLIB_bufParams2D_t *y_addr,
    uint8_t *cbcrData,
    VXLIB_bufParams2D_t *cbcr_addr,
    uint8_t *rgbData,
    VXLIB_bufParams3D_t *rgb_addr,
    const int16_t coeff[5],
    void *pBlock
);

#endif /* VXLIB_convert_NV12_to_RGBpl_H_ */
