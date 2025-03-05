/*
* module name       : c7x_conv_5x5
*
* module descripton : 5x5 convolution
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#ifndef VXLIB_CONV_I16S_C16S_O32S_5X5_SKIP1_CN_H_
#define VXLIB_CONV_I16S_C16S_O32S_5X5_SKIP1_CN_H_ 1

#include "VXLIB_types.h"

VXLIB_STATUS VXLIB_conv_i16s_c16s_o32s_5x5_skip1_cn
(
    int16_t *src,
    VXLIB_bufParams3D_t *src_addr,
    int16_t *weights,
    VXLIB_bufParams3D_t *weights_addr,
    int16_t *bias,
    VXLIB_bufParams3D_t *bias_addr,
    int32_t *dst,
    VXLIB_bufParams3D_t *dst_addr,
    uint32_t shiftQ,
    uint32_t coeffQ
);

VXLIB_STATUS VXLIB_conv_i16s_c16s_o32s_5x5_skip1_checkParams_cn
(
    int16_t *src,
    VXLIB_bufParams3D_t *src_addr,
    int16_t *weights,
    VXLIB_bufParams3D_t *weights_addr,
    int16_t *bias,
    VXLIB_bufParams3D_t *bias_addr,
    int32_t *dst,
    VXLIB_bufParams3D_t *dst_addr,
    uint32_t shiftQ,
    uint32_t coeffQ
);

#endif /* VXLIB_CONV_I16S_C16S_O32S_5X5_SKIP1_CN_H_ */

/* ======================================================================== */
/*  End of file:  VXLIB_conv_i16s_c16s_o32s_5x5_skip1_cn.h                  */
/* ======================================================================== */
