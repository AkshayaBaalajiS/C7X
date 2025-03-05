/*
* module name       : c7x_nms
*
* module descripton : Computes 7x7 window Non Maximum Suppression
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#include "VXLIB_nms_MxN_i32s_o8u_cn.h"

VXLIB_STATUS VXLIB_nms_MxN_i32s_o8u_cn(const int32_t src[restrict],
                               const VXLIB_bufParams2D_t *src_addr,
                               uint8_t dst[restrict],
                               const VXLIB_bufParams2D_t *dst_addr,
                               uint8_t winWidth,
                               uint8_t winHeight,
                               int32_t threshold)
{

    VXLIB_STATUS    status = VXLIB_SUCCESS;

#ifdef VXLIB_CHECK_PARAMS
    status = VXLIB_nms_MxN_i32s_o8u_checkParams_cn(src, src_addr, dst, dst_addr, winWidth, winHeight);
    if( status == VXLIB_SUCCESS )
#endif
    {
    int32_t x, y, i, j, k, l, o;
    int32_t outWidth, outHeight;
    int32_t start_x, start_y;
    int32_t inputStride, outputStride;

    outWidth = VXLIB_min(dst_addr->dim_x, src_addr->dim_x-(winWidth-1));
    outHeight = VXLIB_min(dst_addr->dim_y, src_addr->dim_y-(winHeight-1));
    inputStride= src_addr->stride_y / sizeof(src[0]);
    outputStride= dst_addr->stride_y / sizeof(dst[0]);

    start_x = (winWidth - 1)/2;
    start_y = (winHeight - 1)/2;

    for (y = start_y; y < outHeight+start_y; y++)
    {
        for (x = start_x; x < outWidth+start_x; x++)
        {
            int32_t v = 0;
            int32_t max = 0;
            i = (y * inputStride) + x;
            v = src[i];
            for (l = (y - start_y); l < (y + winHeight- start_y); l++)
            {
                for (k = (x - start_x); k < (x + winWidth- start_x); k++)
                {
                    j = (l * inputStride) + k;
                    if (max < src[j])
                        max = src[j];
                }
            }
            o = ((y-start_y) * outputStride) + (x-start_x); // Output starts from upper left corner
            if ((v == max) && (v > threshold))
                dst[o] = 255;
            else
                dst[o] = 0;
        }
      }
    }
    return (status);
}

VXLIB_STATUS VXLIB_nms_MxN_i32s_o8u_checkParams_cn(const int32_t src[restrict],
                               const VXLIB_bufParams2D_t *src_addr,
                               uint8_t dst[restrict],
                               const VXLIB_bufParams2D_t *dst_addr,
                               uint8_t winWidth,
                               uint8_t winHeight)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

    if( (src == NULL) || (dst == NULL) ) {
        status = VXLIB_ERR_NULL_POINTER;
    } else if( src_addr->dim_x < dst_addr->dim_x ||
                (src_addr->dim_y - (winWidth -1)) < dst_addr->dim_y ||
                src_addr->stride_y < src_addr->dim_x ||
                dst_addr->stride_y < dst_addr->dim_x*sizeof(dst[0]) ) {
        status = VXLIB_ERR_INVALID_DIMENSION;
    } else if((src_addr->data_type != VXLIB_INT32) ||
               (dst_addr->data_type != VXLIB_UINT8)) {
        status = VXLIB_ERR_INVALID_TYPE;
    }
    return (status);
}
