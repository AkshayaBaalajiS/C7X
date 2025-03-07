/*
* module name       : c7x_sobelX_3x3
*
* module descripton : Computes Sobel X gradients across 3x3 window
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#ifndef VXLIB_SOBELX_3X3_I8U_O16S_H_
#define VXLIB_SOBELX_3X3_I8U_O16S_H_ 1

#include "VXLIB_types.h"

#define VXLIB_SOBELX_3X3_I8U_O16S_PBLOCK_SIZE (256)

VXLIB_STATUS    VXLIB_sobelX_3x3_i8u_o16s_init(const uint8_t src[restrict],
        const VXLIB_bufParams2D_t *src_addr,
        int16_t dst[restrict],
        const VXLIB_bufParams2D_t *dst_addr,
        void *pBlock);


VXLIB_STATUS    VXLIB_sobelX_3x3_i8u_o16s_kernel(const uint8_t src[restrict],
        const VXLIB_bufParams2D_t *src_addr,
        int16_t dst[restrict],
        const VXLIB_bufParams2D_t *dst_addr,
        void *pBlock);

VXLIB_STATUS    VXLIB_sobelX_3x3_i8u_o16s_checkParams(const uint8_t src[restrict],
        const VXLIB_bufParams2D_t *src_addr,
        const int16_t dst[restrict],
        const VXLIB_bufParams2D_t *dst_addr);

#endif
