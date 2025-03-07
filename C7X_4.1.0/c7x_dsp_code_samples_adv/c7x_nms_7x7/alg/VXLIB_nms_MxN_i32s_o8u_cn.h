/*
* module name       : c7x_nms
*
* module descripton : Computes 7x7 window Non Maximum Suppression
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#ifndef VXLIB_NMS_MxN_I32S_O8S_CN_H_
#define VXLIB_NMS_MxN_I32S_O8S_CN_H_ 1

#include "VXLIB_types.h"

VXLIB_STATUS VXLIB_nms_MxN_i32s_o8u_cn(const int32_t src[restrict],
                               const VXLIB_bufParams2D_t *src_addr,
                               uint8_t dst[restrict],
                               const VXLIB_bufParams2D_t *dst_addr,
                               uint8_t winWidth,
                               uint8_t winHeight,
                               int32_t threshold);


VXLIB_STATUS VXLIB_nms_MxN_i32s_o8u_checkParams_cn(const int32_t src[restrict],
                               const VXLIB_bufParams2D_t *src_addr,
                               uint8_t dst[restrict],
                               const VXLIB_bufParams2D_t *dst_addr,
                               uint8_t winWidth,
                               uint8_t winHeight);


#endif
