/*
* module name       : c7x_NV12ToRGB
*
* module descripton : Converts NV12 to RGB planar format
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#include "VXLIB_convert_NV12_to_RGBpl_cn.h"

VXLIB_STATUS VXLIB_convert_NV12_to_RGBpl_cn
(
    uint8_t *yData,
    VXLIB_bufParams2D_t *y_addr,
    uint8_t *cbcrData,
    VXLIB_bufParams2D_t *cbcr_addr,
    uint8_t *rgbData,
    VXLIB_bufParams3D_t *rgb_addr,
    const int16_t coeff[5]
)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#ifdef VXLIB_CHECK_PARAMS
    status = VXLIB_convert_NV12_to_RGBpl_checkParams_cn(yData, y_addr, cbcrData, cbcr_addr, rgbData, rgb_addr, coeff);
    if( status == VXLIB_SUCCESS )
#endif
    {
        int32_t    i, j, ii;         /* Loop counters                    */
        int32_t     y0, y1, y2, y3;   /* Individual Y components          */
        int32_t     cb, cr;           /* Color difference components      */
        int32_t     y0t, y1t, y2t, y3t; /* Temporary Y values               */
        int32_t     rt, gt, bt;       /* Temporary RGB values             */
        int32_t     r0, g0, b0;       /* Individual RGB components        */
        int32_t     r1, g1, b1;       /* Individual RGB components        */
        int32_t     r2, g2, b2;       /* Individual RGB components        */
        int32_t     r3, g3, b3;       /* Individual RGB components        */
        int32_t     r0t, g0t, b0t;    /* Truncated RGB components         */
        int32_t     r1t, g1t, b1t;    /* Truncated RGB components         */
        int32_t     r2t, g2t, b2t;    /* Truncated RGB components         */
        int32_t     r3t, g3t, b3t;    /* Truncated RGB components         */
        int32_t     r0s, g0s, b0s;    /* Saturated RGB components         */
        int32_t     r1s, g1s, b1s;    /* Saturated RGB components         */
        int32_t     r2s, g2s, b2s;    /* Saturated RGB components         */
        int32_t     r3s, g3s, b3s;    /* Saturated RGB components         */
        int16_t     luma = coeff[0];  /* Luma scaling coefficient.        */
        int16_t     r_cr = coeff[1];  /* Cr's contribution to Red.        */
        int16_t     g_cb = coeff[2];  /* Cb's contribution to Green.      */
        int16_t     g_cr = coeff[3];  /* Cr's contribution to Green.      */
        int16_t     b_cb = coeff[4];  /* Cb's contribution to Blue.       */

        uint8_t *restrict    y_row0;
        uint8_t *restrict    y_row1;
        uint8_t *restrict    cbcr_InData;
        uint32_t             width, height;
        int32_t              pitch;
        uint8_t *restrict    r_OutData;
        uint8_t *restrict    g_OutData;
        uint8_t *restrict    b_OutData;

        width   =   rgb_addr->dim_x;
        height  =   rgb_addr->dim_y;
        pitch   =   rgb_addr->stride_y;
        r_OutData = (uint8_t *)rgbData;
        g_OutData = (uint8_t *)rgbData + (height * pitch);
        b_OutData = (uint8_t *)rgbData + (height * pitch * 2);

        for( i = 0; i < height / 2; i++ ) {
            ii = 0;

            for( j = 0; j < (width / 2); j++ ) {
                /*  0   1   2   3  */
                /*  y0 cr0 y1 cb0  */

                /* ---------------------------------------------------------------- */
                /*  The Cb and Cr channels come in biased upwards by 128, so        */
                /*  subtract the bias here before performing the multiplies for     */
                /*  the color space conversion itself.  Also handle Y's upward      */
                /*  bias of 16 here.                                                */
                /* ---------------------------------------------------------------- */
                y_row0 = (uint8_t *)yData + (pitch * 2 * i) + (2 * j);
                y_row1 = (uint8_t *)yData + (pitch * ((2 * i) + 1)) + (2 * j);
                cbcr_InData = (uint8_t *)cbcrData + (pitch * i) + (2 * j);
                y0 = y_row0[0]  - 16;
                y1 = y_row0[1]  - 16;
                y2 = y_row1[0]  - 16;
                y3 = y_row1[1]  - 16;
                cb = cbcr_InData[0] - 128;
                cr = cbcr_InData[1] - 128;

                /* ================================================================ */
                /*  Convert YCrCb data to RGB format using the following matrix:    */
                /*                                                                  */
                /*      [ coeff[0] 0.0000   coeff[1] ]   [ Y' -  16 ]     [ R']     */
                /*      [ coeff[0] coeff[2] coeff[3] ] * [ Cb - 128 ]  =  [ G']     */
                /*      [ coeff[0] coeff[4] 0.0000   ]   [ Cr - 128 ]     [ B']     */
                /*                                                                  */
                /*  We use signed Q13 coefficients for the coefficients to make     */
                /*  good use of our 16-bit multiplier.  Although a larger Q-point   */
                /*  may be used with unsigned coefficients, signed coefficients     */
                /*  add a bit of flexibility to the kernel without significant      */
                /*  loss of precision.                                              */
                /* ================================================================ */

                /* ---------------------------------------------------------------- */
                /*  Calculate chroma channel's contribution to RGB.                 */
                /* ---------------------------------------------------------------- */
                rt  = r_cr * (int16_t)cr;
                gt  = g_cb * (int16_t)cb + g_cr * (int16_t)cr;
                bt  = b_cb * (int16_t)cb;

                /* ---------------------------------------------------------------- */
                /*  Calculate intermediate luma values.  Include bias of 16 here.   */
                /* ---------------------------------------------------------------- */
                y0t = luma * (int16_t)y0;
                y1t = luma * (int16_t)y1;
                y2t = luma * (int16_t)y2;
                y3t = luma * (int16_t)y3;
                /* ---------------------------------------------------------------- */
                /*  Mix luma, chroma channels.                                      */
                /* ---------------------------------------------------------------- */

                r0  = y0t + rt;
                r1  = y1t + rt;
                g0  = y0t + gt;
                g1  = y1t + gt;
                b0  = y0t + bt;
                b1  = y1t + bt;

                r2  = y2t + rt;
                r3  = y3t + rt;
                g2  = y2t + gt;
                g3  = y3t + gt;
                b2  = y2t + bt;
                b3  = y3t + bt;

                /* ================================================================ */
                /*  At this point in the calculation, the RGB components are        */
                /*  nominally in the format below.  If the color is outside the     */
                /*  our RGB gamut, some of the sign bits may be non-zero,           */
                /*  triggering saturation.                                          */
                /*                                                                  */
                /*                  3     2 2        1 1                            */
                /*                  1     1 0        3 2         0                  */
                /*                 [ SIGN  | COLOR    | FRACTION ]                  */
                /*                                                                  */
                /*  This gives us an 8-bit range for each of the R, G, and B        */
                /*  components.  (The transform matrix is designed to transform     */
                /*  8-bit Y/C values into 8-bit R,G,B values.)  To get our final    */
                /*  8:8:8 result, we "divide" our R, G and B components.            */
                /*  "Divide" is in quotation marks because this step requires no    */
                /*  actual work.  The code merely treats the numbers as having a    */
                /*  different Q-point.                                              */
                /* ================================================================ */

                /* ---------------------------------------------------------------- */
                /*  Shift away the fractional portion, and then saturate to the     */
                /*  RGB 8:8:8 gamut.                                                */
                /* ---------------------------------------------------------------- */
                r0t = r0 >> 13; /* 16; */
                g0t = g0 >> 13; /* 15; */
                b0t = b0 >> 13; /* 16; */
                r1t = r1 >> 13; /* 16; */
                g1t = g1 >> 13; /* 15; */
                b1t = b1 >> 13; /* 16; */

                r2t = r2 >> 13; /* 16; */
                g2t = g2 >> 13; /* 15; */
                b2t = b2 >> 13; /* 16; */
                r3t = r3 >> 13; /* 16; */
                g3t = g3 >> 13; /* 15; */
                b3t = b3 >> 13; /* 16; */

                r0s = r0t < 0 ? 0 : r0t > 255 ? 255 : r0t;
                g0s = g0t < 0 ? 0 : g0t > 255 ? 255 : g0t;
                b0s = b0t < 0 ? 0 : b0t > 255 ? 255 : b0t;
                r1s = r1t < 0 ? 0 : r1t > 255 ? 255 : r1t;
                g1s = g1t < 0 ? 0 : g1t > 255 ? 255 : g1t;
                b1s = b1t < 0 ? 0 : b1t > 255 ? 255 : b1t;

                r2s = r2t < 0 ? 0 : r2t > 255 ? 255 : r2t;
                g2s = g2t < 0 ? 0 : g2t > 255 ? 255 : g2t;
                b2s = b2t < 0 ? 0 : b2t > 255 ? 255 : b2t;
                r3s = r3t < 0 ? 0 : r3t > 255 ? 255 : r3t;
                g3s = g3t < 0 ? 0 : g3t > 255 ? 255 : g3t;
                b3s = b3t < 0 ? 0 : b3t > 255 ? 255 : b3t;

                /* ---------------------------------------------------------------- */
                /*  Store resulting pixels to memory.                               */
                /* ---------------------------------------------------------------- */
                *(r_OutData + (pitch * i << 1) + ii + 0) = r0s;
                *(r_OutData + (pitch * i << 1) + ii + 1) = r1s;
                *(g_OutData + (pitch * i << 1) + ii + 0) = g0s;
                *(g_OutData + (pitch * i << 1) + ii + 1) = g1s;
                *(b_OutData + (pitch * i << 1) + ii + 0) = b0s;
                *(b_OutData + (pitch * i << 1) + ii + 1) = b1s;

                *(r_OutData + pitch * ((i << 1) + 1) + ii + 0) = r2s;
                *(r_OutData + pitch * ((i << 1) + 1) + ii + 1) = r3s;
                *(g_OutData + pitch * ((i << 1) + 1) + ii + 0) = g2s;
                *(g_OutData + pitch * ((i << 1) + 1) + ii + 1) = g3s;
                *(b_OutData + pitch * ((i << 1) + 1) + ii + 0) = b2s;
                *(b_OutData + pitch * ((i << 1) + 1) + ii + 1) = b3s;

                ii += 2;
            }
        }
    }
    return (status);

}

VXLIB_STATUS VXLIB_convert_NV12_to_RGBpl_checkParams_cn
(
    uint8_t *yData,
    VXLIB_bufParams2D_t *y_addr,
    uint8_t *cbcrData,
    VXLIB_bufParams2D_t *cbcr_addr,
    uint8_t *rgbData,
    VXLIB_bufParams2D_t *rgb_addr,
    const int16_t coeff[5]
)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

    return (status);
}
/* ======================================================================== */
/*  End of file:  VXLIB_convert_NV12_to_RGBpl_cn.c                      */
/* ======================================================================== */
