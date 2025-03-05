/*
* module name       : c7x_harris_score_3x3
*
* module descripton : Computes Harris Score for 3x3 window
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/
#include "VXLIB_harrisScore_NxN_i16s_i16s_o32u_cn.h"

VXLIB_STATUS VXLIB_harrisScore_NxN_i16s_i16s_o32u_cn(int16_t gradx[],
                                                     VXLIB_bufParams2D_t * gradx_addr,
                                                     int16_t grady[],
                                                     VXLIB_bufParams2D_t * grady_addr,
                                                     uint32_t dst[],
                                                     VXLIB_bufParams2D_t * dst_addr,
                                                     uint8_t blk_size)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#ifdef VXLIB_CHECK_PARAMS
    status = VXLIB_harrisScore_NxN_i16s_i16s_o32u_checkParams_cn(gradx, gradx_addr, grady, grady_addr, dst, dst_addr, blk_size);
    if( status == VXLIB_SUCCESS )
#endif
    {
        uint32_t  x, y, i, j;

        int32_t outWidth  = VXLIB_min(dst_addr->dim_x, gradx_addr->dim_x - (blk_size - 1));
        int32_t outHeight = VXLIB_min(dst_addr->dim_y, gradx_addr->dim_y - (blk_size - 1));

        int32_t srcBitDepth = VXLIB_sizeof(gradx_addr->data_type);
        int32_t dstBitDepth = VXLIB_sizeof(dst_addr->data_type);

        int32_t inPitch   = gradx_addr->stride_y/srcBitDepth;
        int32_t outPitch  = dst_addr->stride_y/dstBitDepth;

        for(y=0; y < outHeight; y++) {
            for(x=0; x < outWidth; x++) {

                uint32_t sum_ix2   = 0;
                uint32_t sum_iy2   = 0;

                for (j = 0; j < blk_size; j++)
                {
                    for (i = 0; i < blk_size; i++)
                    {
                        int16_t gx = gradx[ ((y + j) * inPitch) + (x + i)];
                        int16_t gy = grady[ ((y + j) * inPitch) + (x + i)];

                        sum_ix2 += (gx * gx);
                        sum_iy2 += (gy * gy);

                    }
                }

                dst[(y * outPitch) +x] = sum_ix2 + sum_iy2;
            }
        }
    }
    return (status);
}

VXLIB_STATUS VXLIB_harrisScore_NxN_i16s_i16s_o32u_checkParams_cn(int16_t gradx[],
                                                                 VXLIB_bufParams2D_t * gradx_addr,
                                                                 int16_t grady[],
                                                                 VXLIB_bufParams2D_t * grady_addr,
                                                                 uint32_t dst[],
                                                                 VXLIB_bufParams2D_t * dst_addr,
                                                                 uint8_t blk_size)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

    return (status);
}

/* ======================================================================== */
/*  End of file:  VXLIB_harrisScore_NxN_i16s_i16s_o32u_cn.c                 */
/* ======================================================================== */
