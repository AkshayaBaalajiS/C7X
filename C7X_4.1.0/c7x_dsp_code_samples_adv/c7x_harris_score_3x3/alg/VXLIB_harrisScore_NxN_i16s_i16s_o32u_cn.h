/*
* module name       : c7x_harris_score_3x3
*
* module descripton : Computes Harris Score for 3x3 window
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#ifndef _VXLIB_HARRISSCORE_NXN_I16S_I16S_O32U_CN_H_
#define _VXLIB_HARRISSCORE_NXN_I16S_I16S_O32U_CN_H_ 1

#include "VXLIB_types.h"

VXLIB_STATUS VXLIB_harrisScore_NxN_i16s_i16s_o32u_cn(int16_t gradx[],
                                                     VXLIB_bufParams2D_t * gradx_addr,
                                                     int16_t grady[],
                                                     VXLIB_bufParams2D_t * grady_addr,
                                                     uint32_t dst[],
                                                     VXLIB_bufParams2D_t * dst_addr,
                                                     uint8_t blk_size);

VXLIB_STATUS VXLIB_harrisScore_NxN_i16s_i16s_o32u_checkParams_cn(int16_t gradx[],
                                                     VXLIB_bufParams2D_t * gradx_addr,
                                                     int16_t grady[],
                                                     VXLIB_bufParams2D_t * grady_addr,
                                                     uint32_t dst[],
                                                     VXLIB_bufParams2D_t * dst_addr,
                                                     uint8_t blk_size);

#endif

/* ======================================================================== */
/*  End of file:  VXLIB_harrisScore_NxN_i16s_i16s_o32u_cn.h                 */
/* ======================================================================== */
