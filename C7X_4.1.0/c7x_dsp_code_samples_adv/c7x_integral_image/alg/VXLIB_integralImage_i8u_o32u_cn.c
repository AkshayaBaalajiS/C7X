/*
* module name       : c7x_integral_image
*
* module descripton : Computes integral image
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#include "VXLIB_integralImage_i8u_o32u_cn.h"

VXLIB_STATUS VXLIB_integralImage_i8u_o32u_cn(uint8_t src[],
                                     VXLIB_bufParams2D_t *src_addr,
                                     uint32_t dst[],
                                     VXLIB_bufParams2D_t *dst_addr)
{
    uint32_t        x, y, srcIndex, dstIndex;
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#ifdef VXLIB_CHECK_PARAMS
    status = VXLIB_integralImage_i8u_o32u_checkParams_cn(src, src_addr, dst, dst_addr);
    if( status == VXLIB_SUCCESS )
#endif
    {
        for( y = 0; y < src_addr->dim_y; y++ ) {
            srcIndex = y * src_addr->stride_y;
            dstIndex = y * (dst_addr->stride_y / sizeof(uint32_t));
            if( y == 0 ) {
                dst[y * dst_addr->stride_y] = src[y * src_addr->stride_y];

                for( x = 1; x < src_addr->dim_x; x++ ) {
                    srcIndex = x;
                    dstIndex = x;
                    dst[dstIndex] = dst[dstIndex - 1] + src[srcIndex];
                }
            } else {
                dst[y * dst_addr->stride_y / sizeof(uint32_t)] =  dst[(y - 1) * dst_addr->stride_y / sizeof(uint32_t)]
                                                                   + src[y * src_addr->stride_y];

                for( x = 1; x < src_addr->dim_x; x++ ) {
                    srcIndex = (y * src_addr->stride_y) + x;
                    dstIndex = (y * dst_addr->stride_y / sizeof(uint32_t)) + x;
                    dst[dstIndex] = src[srcIndex] + dst[dstIndex - 1]
                                    + dst[(y - 1) * dst_addr->stride_y / sizeof(uint32_t) + x]
                                    - dst[(y - 1) * dst_addr->stride_y / sizeof(uint32_t) + (x - 1)];
                }
            }
        }
    }
    return (status);
}

VXLIB_STATUS VXLIB_integralImage_i8u_o32u_checkParams_cn(uint8_t src[],
                                                 VXLIB_bufParams2D_t *src_addr,
                                                 uint32_t dst[],
                                                 VXLIB_bufParams2D_t *dst_addr)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

    if((src == NULL) || (dst == NULL)) {
        status = VXLIB_ERR_NULL_POINTER;
    } else if((src_addr->dim_x != dst_addr->dim_x) ||
              (src_addr->dim_y != dst_addr->dim_y) ||
              (src_addr->stride_y < src_addr->dim_x) ||
              (dst_addr->stride_y < (4 * dst_addr->dim_x))) {
        status = VXLIB_ERR_INVALID_DIMENSION;
    } else if((src_addr->data_type != VXLIB_UINT8) ||
               (dst_addr->data_type != VXLIB_UINT32)) {
        status = VXLIB_ERR_INVALID_TYPE;
    }
    return (status);
}
