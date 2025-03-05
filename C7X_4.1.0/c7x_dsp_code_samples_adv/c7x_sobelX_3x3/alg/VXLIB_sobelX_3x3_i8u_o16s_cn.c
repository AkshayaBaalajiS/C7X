/*
* module name       : c7x_sobelX_3x3
*
* module descripton : Computes Sobel X gradients across 3x3 window
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#include "VXLIB_sobelX_3x3_i8u_o16s_cn.h"

VXLIB_STATUS VXLIB_sobelX_3x3_i8u_o16s_cn(uint8_t src[],
                                  VXLIB_bufParams2D_t *src_addr,
                                  int16_t dst[],
                                  VXLIB_bufParams2D_t *dst_addr)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#ifdef VXLIB_CHECK_PARAMS
    status = VXLIB_sobelX_3x3_i8u_o16s_checkParams_cn(src, src_addr, dst, dst_addr);
    if( status == VXLIB_SUCCESS )
#endif
    {
        int32_t x, y;
        int32_t sum;
        int32_t outWidth, outHeight;

        outWidth = VXLIB_min(dst_addr->dim_x, src_addr->dim_x-2);
        outHeight = VXLIB_min(dst_addr->dim_y, src_addr->dim_y-2);
        for(y=0; y < outHeight; y++) {
            for(x=0; x < outWidth; x++) {
                sum =   src[(y+0)*src_addr->stride_y + (x+0)]*-1 +
                        src[(y+0)*src_addr->stride_y + (x+1)]* 0 +
                        src[(y+0)*src_addr->stride_y + (x+2)]* 1 +
                        src[(y+1)*src_addr->stride_y + (x+0)]*-2 +
                        src[(y+1)*src_addr->stride_y + (x+1)]* 0 +
                        src[(y+1)*src_addr->stride_y + (x+2)]* 2 +
                        src[(y+2)*src_addr->stride_y + (x+0)]*-1 +
                        src[(y+2)*src_addr->stride_y + (x+1)]* 0 +
                        src[(y+2)*src_addr->stride_y + (x+2)]* 1;

                dst[y*dst_addr->stride_y/2 + x] = sum;
            }
        }
    }
    return (status);
}

VXLIB_STATUS VXLIB_sobelX_3x3_i8u_o16s_checkParams_cn(uint8_t src[],
                                           VXLIB_bufParams2D_t *src_addr,
                                           int16_t dst[],
                                           VXLIB_bufParams2D_t *dst_addr)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

    if( (src == NULL) || (dst == NULL) ) {
        status = VXLIB_ERR_NULL_POINTER;
    } else if( src_addr->dim_x < dst_addr->dim_x ||
                (src_addr->dim_y-2) < dst_addr->dim_y ||
                src_addr->stride_y < src_addr->dim_x ||
                dst_addr->stride_y < dst_addr->dim_x*2 ) {
        status = VXLIB_ERR_INVALID_DIMENSION;
    } else if((src_addr->data_type != VXLIB_UINT8) ||
               (dst_addr->data_type != VXLIB_INT16)) {
        status = VXLIB_ERR_INVALID_TYPE;
    }
    return (status);
}
