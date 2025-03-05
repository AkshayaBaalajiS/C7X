/*
* module name       : c7x_erosion_3x3
*
* module descripton : 3x3 greyscale erosion
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#include "VXLIB_erode_3x3_i8u_o8u_cn.h"

VXLIB_STATUS VXLIB_erode_3x3_i8u_o8u_cn(uint8_t src[],
                                  VXLIB_bufParams2D_t *src_addr,
                                  uint8_t dst[],
                                  VXLIB_bufParams2D_t *dst_addr)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#ifdef VXLIB_CHECK_PARAMS
    status = VXLIB_erode_3x3_i8u_o8u_checkParams_cn(src, src_addr, dst, dst_addr);
    if( status == VXLIB_SUCCESS )
#endif
    {
        int32_t x, y, j, k;
        int32_t outWidth = VXLIB_min(dst_addr->dim_x, src_addr->dim_x-2);
        int32_t outHeight = VXLIB_min(dst_addr->dim_y, src_addr->dim_y-2);

        for(y=0; y < outHeight; y++) {
            for(x=0; x < outWidth; x++) {
                uint8_t min = 255;
                for(j=0; j < 3; j++) {
                    for(k=0; k < 3; k++) {
                        min = VXLIB_min(src[(y+j)*src_addr->stride_y + (x+k)], min);
                    }
                }
                dst[y*dst_addr->stride_y + x] = min;
            }
        }
    }
    return (status);
}

VXLIB_STATUS VXLIB_erode_3x3_i8u_o8u_checkParams_cn(uint8_t src[],
                                           VXLIB_bufParams2D_t *src_addr,
                                           uint8_t dst[],
                                           VXLIB_bufParams2D_t *dst_addr)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

    if((src == NULL) || (dst == NULL)) {
        status = VXLIB_ERR_NULL_POINTER;
    } else if( src_addr->dim_x < dst_addr->dim_x ||
                (src_addr->dim_y-2) < dst_addr->dim_y ||
                src_addr->stride_y < src_addr->dim_x ||
                dst_addr->stride_y < dst_addr->dim_x ) {
        status = VXLIB_ERR_INVALID_DIMENSION;
    } else if((src_addr->data_type != VXLIB_UINT8) ||
               (dst_addr->data_type != VXLIB_UINT8)) {
        status = VXLIB_ERR_INVALID_TYPE;
    }
    return (status);
}
