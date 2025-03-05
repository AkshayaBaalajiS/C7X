/*
* module name       : c7x_fast9Corners
*
* module descripton : Computes FAST9 corners
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#include "VXLIB_fastCornersDetect_i8u_cn.h"

#define PERMUTATIONS 16
#define APERTURE 3

static uint8_t indexes[PERMUTATIONS][9] =
{
    {  0,  1,  2,  3,  4,  5,  6,  7,  8 },
    { 15,  0,  1,  2,  3,  4,  5,  6,  7 },
    { 14, 15,  0,  1,  2,  3,  4,  5,  6 },
    { 13, 14, 15,  0,  1,  2,  3,  4,  5 },
    { 12, 13, 14, 15,  0,  1,  2,  3,  4 },
    { 11, 12, 13, 14, 15,  0,  1,  2,  3 },
    { 10, 11, 12, 13, 14, 15,  0,  1,  2 },
    {  9, 10, 11, 12, 13, 14, 15,  0,  1 },
    {  8,  9, 10, 11, 12, 13, 14, 15,  0 },
    {  7,  8,  9, 10, 11, 12, 13, 14, 15 },
    {  6,  7,  8,  9, 10, 11, 12, 13, 14 },
    {  5,  6,  7,  8,  9, 10, 11, 12, 13 },
    {  4,  5,  6,  7,  8,  9, 10, 11, 12 },
    {  3,  4,  5,  6,  7,  8,  9, 10, 11 },
    {  2,  3,  4,  5,  6,  7,  8,  9, 10 },
    {  1,  2,  3,  4,  5,  6,  7,  8,  9 }
};

/* offsets from "p" */
static int32_t    offsets[16][2] =
{
    {  0, -3 },
    {  1, -3 },
    {  2, -2 },
    {  3, -1 },
    {  3,  0 },
    {  3,  1 },
    {  2,  2 },
    {  1,  3 },
    {  0,  3 },
    { -1,  3 },
    { -2,  2 },
    { -3,  1 },
    { -3,  0 },
    { -3, -1 },
    { -2, -2 },
    { -1, -3 },
};


static bool VXLIB_IsFastCorner(const uint8_t *buf, uint8_t p, uint8_t tolerance)
{
    int32_t    i, a, j, v;

    for( a = 0; a < PERMUTATIONS; a++ ) {
        bool    isacorner = true;

        for( i = 0; i < (sizeof(indexes[a]) / sizeof(indexes[a][0])); i++ ) {
            j = indexes[a][i];
            v = buf[j];
            if( v <= (p + tolerance)) {
                isacorner = false;
            }
        }

        if( isacorner == true ) {
            return (isacorner);
        }
        isacorner = true;

        for( i = 0; i < (sizeof(indexes[a]) / sizeof(indexes[a][0])); i++ ) {
            j = indexes[a][i];
            v = buf[j];
            if( v >= (p - tolerance)) {
                isacorner = false;
            }
        }

        if( isacorner == true ) {
            return (isacorner);
        }
    }

    return (false);
}

static uint8_t VXLIB_GetFastCornerStrength(int32_t x, int32_t y, uint8_t src[],
                                           VXLIB_bufParams2D_t *src_addr,
                                           uint8_t tolerance)
{
    if( x < APERTURE || y < APERTURE || x >= src_addr->dim_x - APERTURE || y >= src_addr->dim_y - APERTURE ) {
        return (0);
    }
    {
        uint32_t    srcIndex0 = (y * src_addr->stride_y) + x;
        uint32_t    srcIndex1;
        uint8_t     buf[16], c;
        int32_t     j;
        uint8_t     a, b = 255;

        for( j = 0; j < 16; j++ ) {
            srcIndex1 = ((y + offsets[j][1]) * src_addr->stride_y) + (x + offsets[j][0]);
            buf[j] = src[srcIndex1];
        }

        if( !VXLIB_IsFastCorner(buf, src[srcIndex0], tolerance)) {
            return (0);
        }
        a = tolerance;

        while( b - a > 1 ) {
            c = (a + b) / 2;
            if( VXLIB_IsFastCorner(buf, src[srcIndex0], c)) {
                a = c;
            } else {
                b = c;
            }
        }

        return (a);
    }
}

VXLIB_STATUS VXLIB_fastCornersDetect_i8u_cn(uint8_t src[],
                                   VXLIB_bufParams2D_t *src_addr,
                                   uint16_t corners[],
                                   uint32_t corners_capacity,
                                   uint8_t strength_thresh,
                                   uint32_t *num_corners)
{
    uint32_t        x, y;
    uint8_t         strength;
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#ifdef VXLIB_CHECK_PARAMS
    status = VXLIB_fastCornersDetect_i8u_checkParams_cn(src, src_addr);
    if( status == VXLIB_SUCCESS )
#endif
    {
        *num_corners = 0;
        for( y = APERTURE; y < (int32_t)(src_addr->dim_y - APERTURE); y++ ) {
            for( x = APERTURE; x < (int32_t)(src_addr->dim_x - APERTURE); x++ ) {
                strength = VXLIB_GetFastCornerStrength(x, y, src, src_addr, strength_thresh);
                if( strength > 0 ) {
                    if( 0 ) {
                        if( strength >= VXLIB_GetFastCornerStrength(x - 1, y - 1, src, src_addr, strength_thresh) &&
                            strength >= VXLIB_GetFastCornerStrength(x, y - 1, src, src_addr, strength_thresh) &&
                            strength >= VXLIB_GetFastCornerStrength(x + 1, y - 1, src, src_addr, strength_thresh) &&
                            strength >= VXLIB_GetFastCornerStrength(x - 1, y, src, src_addr, strength_thresh) &&
                            strength > VXLIB_GetFastCornerStrength(x + 1, y, src, src_addr, strength_thresh) &&
                            strength > VXLIB_GetFastCornerStrength(x - 1, y + 1, src, src_addr, strength_thresh) &&
                            strength > VXLIB_GetFastCornerStrength(x, y + 1, src, src_addr, strength_thresh) &&
                            strength > VXLIB_GetFastCornerStrength(x + 1, y + 1, src, src_addr, strength_thresh)) {
                            ;
                        } else {
                            continue;
                        }
                    }
                    if( *num_corners < corners_capacity ) {
                        corners[*num_corners*2+0] = x;
                        corners[*num_corners*2+1] = y;
                        //corners[*num_corners*3+2] = strength;
                    }
                    ++(*num_corners);
                }
            }
        }
    }
    return (status);
}

VXLIB_STATUS VXLIB_fastCornersDetect_i8u_checkParams_cn(uint8_t src[],
                                               VXLIB_bufParams2D_t *src_addr)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

    if((src == NULL)) {
        status = VXLIB_ERR_NULL_POINTER;
    } else if( src_addr->stride_y < src_addr->dim_x ) {
        status = VXLIB_ERR_INVALID_DIMENSION;
    } else if(src_addr->data_type != VXLIB_UINT8) {
        status = VXLIB_ERR_INVALID_TYPE;
    }
    return (status);
}
