/*
* module name       : c7x_NV12ToRGB
*
* module descripton : Converts NV12 to RGB planar format
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#include "VXLIB_convert_NV12_to_RGBpl.h"

#ifdef _DISPLAY_PARAMS
#include "paramv.h"
#endif

#define SE_PARAM_BASE     (0x0000)
#define SE0_PARAM_OFFSET  (SE_PARAM_BASE)
#define SE1_PARAM_OFFSET  (SE0_PARAM_OFFSET + SE_PARAM_SIZE)
#define SA_PARAM_OFFSET   (SE1_PARAM_OFFSET + SE_PARAM_SIZE)
#define MASK_OFFSET       (SA_PARAM_OFFSET  + SA_PARAM_SIZE)

#define SIMD_WIDTH_SHIFT       (5) /* 2^5 = 32-32b elements in a 512b vector */
#define SIMD_WIDTH             (1 << SIMD_WIDTH_SHIFT)
#define SIMD_WIDTH_RND         (SIMD_WIDTH >> 1)
#define NUM_SIMD_BLOCKS(width) (((width) >> SIMD_WIDTH_SHIFT) + (((width) - (((width) >> SIMD_WIDTH_SHIFT) << SIMD_WIDTH_SHIFT)) > 0 ? 1 : 0))

VXLIB_STATUS VXLIB_convert_NV12_to_RGBpl_init
(
    uint8_t *yData,
    VXLIB_bufParams2D_t *y_addr,
    uint8_t *cbcrData,
    VXLIB_bufParams2D_t *cbcr_addr,
    uint8_t *rgbData,
    VXLIB_bufParams3D_t *rgb_addr,
    const int16_t coeff[5],
    void *pBlock
)
{
    VXLIB_STATUS status = VXLIB_SUCCESS;

#ifdef VXLIB_CHECK_PARAMS
    status = VXLIB_convert_NV12_to_RGBpl_checkParams(yData, y_addr, cbcrData, cbcr_addr, rgbData, rgb_addr, coeff, pBlock);
    if( status == VXLIB_SUCCESS )
#endif
    {
        /* IMPORTANT: Initialize params to 0 before setting stream parameters */
        __STRM_TEMPLATE seTemplate;
        __STRM_TEMPLATE saTemplate;

        __SE_FLAGS seFlags;
        __SA_FLAGS saFlags;

        __STRM_PARAM_3D seParams;
        __STRM_PARAM_3D saParams;

        seFlags = __SE_FLAGS_default();

        seFlags.ELETYPE   = __SE_ELETYPE_8BIT;
        seFlags.PROMOTE   = __SE_PROMOTE_2X_ZEROEXT;
        seFlags.VECLEN    = __SE_VECLEN_32ELEMS;

        seParams.ICNT0 = SIMD_WIDTH;
        seParams.ICNT1 = y_addr->dim_y;
        seParams.ICNT2 = NUM_SIMD_BLOCKS(y_addr->dim_x);

        seParams.DIM1 = y_addr->stride_y;
        seParams.DIM2 = SIMD_WIDTH;

        seTemplate = __SE_SET_PARAM_3D(&seParams, &seFlags);
        *stov_ptr(__STRM_TEMPLATE, (uint32_t*)((uint8_t *)pBlock + SE0_PARAM_OFFSET)) = seTemplate;

        seFlags = __SE_FLAGS_default();

        seFlags.ELETYPE   = __SE_ELETYPE_8BIT;
        seFlags.PROMOTE   = __SE_PROMOTE_2X_ZEROEXT;
        seFlags.VECLEN    = __SE_VECLEN_32ELEMS;

        seParams.ICNT0 = SIMD_WIDTH;
        seParams.ICNT1 = cbcr_addr->dim_y;
        seParams.ICNT2 = NUM_SIMD_BLOCKS(cbcr_addr->dim_x);

        seParams.DIM1 = cbcr_addr->stride_y;
        seParams.DIM2 = SIMD_WIDTH;

        seTemplate = __SE_SET_PARAM_3D(&seParams, &seFlags);
        *stov_ptr(__STRM_TEMPLATE, (uint32_t*)((uint8_t *)pBlock + SE1_PARAM_OFFSET)) = seTemplate;

        /* Prepare SA tempate to store output */
        saFlags = __SA_FLAGS_default();

        saFlags.DECDIM1 = __SA_DECDIM_DIM2;
        saFlags.VECLEN = __SA_VECLEN_32ELEMS;

        /* ITERATION COUNTERS */
        saParams.DECDIM1_WIDTH = rgb_addr->dim_x;
        saParams.ICNT0 = SIMD_WIDTH;
        saParams.ICNT1 = rgb_addr->dim_y;
        saParams.ICNT2 = NUM_SIMD_BLOCKS(rgb_addr->dim_x);

        saParams.DIM1 = rgb_addr->stride_y;
        saParams.DIM2 = SIMD_WIDTH;

        saTemplate = __SA_SET_PARAM_3D(&saParams, &saFlags);
        *stov_ptr(__STRM_TEMPLATE, (uint32_t*)((uint8_t *)pBlock + SA_PARAM_OFFSET)) = saTemplate;

        ulong8 vMask;

        vMask.s0 = 0x2322212003020100;
        vMask.s1 = 0x2726252407060504;
        vMask.s2 = 0x2b2a29280b0a0908;
        vMask.s3 = 0x2f2e2d2c0f0e0d0c;
        vMask.s4 = 0x3332313013121110;
        vMask.s5 = 0x3736353417161514;
        vMask.s6 = 0x3b3a39381b1a1918;
        vMask.s7 = 0x3f3e3d3c1f1e1d1c;

        *stov_ptr(uchar64, (uint8_t*)((uint8_t *)pBlock + MASK_OFFSET)) = __as_uchar64(vMask);

    }

    return (status);
}

VXLIB_STATUS VXLIB_convert_NV12_to_RGBpl_kernel
(
    uint8_t *yData,
    VXLIB_bufParams2D_t *y_addr,
    uint8_t *cbcrData,
    VXLIB_bufParams2D_t *cbcr_addr,
    uint8_t *rgbData,
    VXLIB_bufParams3D_t *rgb_addr,
    const int16_t coeff[5],
    void *pBlock
)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#ifdef VXLIB_CHECK_PARAMS
    status = VXLIB_convert_NV12_to_RGBpl_checkParams(yData, y_addr, cbcrData, cbcr_addr, rgbData, rgb_addr, coeff, pBlock);
    if( status == VXLIB_SUCCESS )
#endif
    {
        __STRM_TEMPLATE seTemplate;
        __STRM_TEMPLATE saTemplate;

        uchar64 vMask;

        uint8_t *restrict pRDataLo;
        uint8_t *restrict pGDataLo;
        uint8_t *restrict pBDataLo;

        uint8_t *restrict pRDataHi;
        uint8_t *restrict pGDataHi;
        uint8_t *restrict pBDataHi;

        int16_t luma = coeff[0];  /* Luma scaling coefficient.    */
        int16_t r_cr = coeff[1];  /* Cr's contribution to Red.    */
        int16_t g_cb = coeff[2];  /* Cb's contribution to Green.  */
        int16_t g_cr = coeff[3];  /* Cr's contribution to Green.  */
        int16_t b_cb = coeff[4];  /* Cb's contribution to Blue.   */

        uint32_t g_cr_g_cb = (g_cr << 16) | (g_cb & 0xFFFF);
        uint32_t r_cr_b_cb = (r_cr << 16) | (b_cb & 0XFFFF);

        uint32_t width, height;
        int32_t  pitch;
        int32_t  numBlks, numLines;
        int32_t  i, j;

        width   = rgb_addr->dim_x;
        height  = rgb_addr->dim_y;
        pitch   = rgb_addr->stride_y;
        numBlks = NUM_SIMD_BLOCKS(width);
        numLines = height >> 1;

        pRDataLo = (uint8_t *)rgbData;
        pGDataLo = (uint8_t *)rgbData + (height * pitch);
        pBDataLo = (uint8_t *)rgbData + (height * pitch * 2);

        pRDataHi = pRDataLo + (SIMD_WIDTH >> 1);
        pGDataHi = pGDataLo + (SIMD_WIDTH >> 1);
        pBDataHi = pBDataLo + (SIMD_WIDTH >> 1);

        seTemplate = *stov_ptr(__STRM_TEMPLATE, (uint32_t*)((uint8_t *)pBlock+ SE0_PARAM_OFFSET));
        __SE0_OPEN((void *)yData, seTemplate);

#ifdef _DISPLAY_PARAMS
        displaySEParam((void *)yData, seTemplate, PARAMV_SE0);
#endif

        seTemplate = *stov_ptr(__STRM_TEMPLATE, (uint32_t*)((uint8_t *)pBlock+ SE1_PARAM_OFFSET));
        __SE1_OPEN((void *)cbcrData, seTemplate);

#ifdef _DISPLAY_PARAMS
        displaySEParam((void *)cbcrData, seTemplate, PARAMV_SE1);
#endif

        saTemplate = *stov_ptr(__STRM_TEMPLATE, (uint32_t*)((uint8_t *)pBlock+ SA_PARAM_OFFSET));
        __SA0_OPEN(saTemplate);
        __SA1_OPEN(saTemplate);
        __SA2_OPEN(saTemplate);

#ifdef _DISPLAY_PARAMS
        displaySAParam((void *)pRDataLo, saTemplate, PARAMV_SA0);
        displaySAParam((void *)pGDataHi, saTemplate, PARAMV_SA1);
        displaySAParam((void *)pBDataHi, saTemplate, PARAMV_SA2);
#endif

        vMask = *stov_ptr(uchar64, (uint8_t*)((uint8_t *)pBlock + MASK_OFFSET));

        short32 vWgtY      = (short32)(luma);
        short32 vWgtGcrGcb = __as_short32((uint16)(g_cr_g_cb));
        short32 vWgtBcrRcb = __as_short32((uint16)(r_cr_b_cb));

#pragma MUST_ITERATE(1,,)
        for( j = 0; j < numBlks; j++ )
        {
#pragma MUST_ITERATE(1,,)
            for( i = 0; i < numLines; i++ )
            {
                uchar64 vOutLo, vOutHi;

                /* ---------------------------------------------------------------- */
                /*  The Cb and Cr channels come in biased upwards by 128, so        */
                /*  subtract the bias here before performing the multiplies for     */
                /*  the color space conversion itself.  Also handle Y's upward      */
                /*  bias of 16 here.                                                */
                /* ---------------------------------------------------------------- */

                short32 vY10   = __SE0ADV(short32) - (short32)(16);
                short32 vY32   = __SE0ADV(short32) - (short32)(16);
                short32 vCrCb  = __SE1ADV(short32) - (short32)(128);

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
                int16 vBt, vRt, vGt;

                __vmpyhw_vvw(vCrCb, vWgtBcrRcb, vBt, vRt);
                vGt = __dotp2(vCrCb, vWgtGcrGcb);

                /* ---------------------------------------------------------------- */
                /*  Calculate intermediate luma values.  Include bias of 16 here.   */
                /* ---------------------------------------------------------------- */
                int16 vY0t, vY1t, vY2t, vY3t;

                __vmpyhw_vvw(vY10, vWgtY, vY0t, vY1t);
                __vmpyhw_vvw(vY32, vWgtY, vY2t, vY3t);

                /* ---------------------------------------------------------------- */
                /*  Mix luma, chroma channels.                                      */
                /* ---------------------------------------------------------------- */

                int16 vR0 = vY0t + vRt;
                int16 vR1 = vY1t + vRt;
                int16 vG0 = vY0t + vGt;
                int16 vG1 = vY1t + vGt;
                int16 vB0 = vY0t + vBt;
                int16 vB1 = vY1t + vBt;

                int16 vR2 = vY2t + vRt;
                int16 vR3 = vY3t + vRt;
                int16 vG2 = vY2t + vGt;
                int16 vG3 = vY3t + vGt;
                int16 vB2 = vY2t + vBt;
                int16 vB3 = vY3t + vBt;

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

                int16 vR0t = __shift_right(vR0, (int16)(13));  /* 16; */
                int16 vG0t = __shift_right(vG0, (int16)(13));  /* 15; */
                int16 vB0t = __shift_right(vB0, (int16)(13));  /* 16; */

                int16 vR1t = __shift_right(vR1, (int16)(13));  /* 16; */
                int16 vG1t = __shift_right(vG1, (int16)(13));  /* 15; */
                int16 vB1t = __shift_right(vB1, (int16)(13));  /* 16; */

                int16 vR2t = __shift_right(vR2, (int16)(13));  /* 16; */
                int16 vG2t = __shift_right(vG2, (int16)(13));  /* 15; */
                int16 vB2t = __shift_right(vB2, (int16)(13));  /* 16; */

                int16 vR3t = __shift_right(vR3, (int16)(13));  /* 16; */
                int16 vG3t = __shift_right(vG3, (int16)(13));  /* 15; */
                int16 vB3t = __shift_right(vB3, (int16)(13));  /* 16; */

                uint16 vR0s = __saturate_s2u(vR0t, (uchar16)(8));
                uint16 vG0s = __saturate_s2u(vG0t, (uchar16)(8));
                uint16 vB0s = __saturate_s2u(vB0t, (uchar16)(8));

                uint16 vR1s = __saturate_s2u(vR1t, (uchar16)(8));
                uint16 vG1s = __saturate_s2u(vG1t, (uchar16)(8));
                uint16 vB1s = __saturate_s2u(vB1t, (uchar16)(8));

                uint16 vR2s = __saturate_s2u(vR2t, (uchar16)(8));
                uint16 vG2s = __saturate_s2u(vG2t, (uchar16)(8));
                uint16 vB2s = __saturate_s2u(vB2t, (uchar16)(8));

                uint16 vR3s = __saturate_s2u(vR3t, (uchar16)(8));
                uint16 vG3s = __saturate_s2u(vG3t, (uchar16)(8));
                uint16 vB3s = __saturate_s2u(vB3t, (uchar16)(8));

                /* ---------------------------------------------------------------- */
                /*  Store resulting pixels to memory.                               */
                /* ---------------------------------------------------------------- */
                __vpred vpStore   = __SA0_VPRED(short32);
                __vpred vpStoreLo = __pdupl2h_pp(vpStore);
                __vpred vpStoreHi = __pduph2h_pp(vpStore);

                vOutLo = __permute_low_low(vMask, __as_uchar64(vR1s), __as_uchar64(vR0s));
                vOutHi = __permute_high_high(vMask, __as_uchar64(vR1s), __as_uchar64(vR0s));

                __vstore_pred_pack_byte(vpStoreLo, __SA0(uchar16, pRDataLo), __as_uint16(vOutLo));
                __vstore_pred_pack_byte(vpStoreHi, __SA0ADV(uchar16, pRDataHi), __as_uint16(vOutHi));

                vOutLo = __permute_low_low(vMask, __as_uchar64(vG1s), __as_uchar64(vG0s));
                vOutHi = __permute_high_high(vMask, __as_uchar64(vG1s), __as_uchar64(vG0s));

                __vstore_pred_pack_byte(vpStoreLo, __SA1(uchar16, pGDataLo), __as_uint16(vOutLo));
                __vstore_pred_pack_byte(vpStoreHi, __SA1ADV(uchar16, pGDataHi), __as_uint16(vOutHi));

                vOutLo = __permute_low_low(vMask, __as_uchar64(vB1s), __as_uchar64(vB0s));
                vOutHi = __permute_high_high(vMask, __as_uchar64(vB1s), __as_uchar64(vB0s));

                __vstore_pred_pack_byte(vpStoreLo, __SA2(uchar16, pBDataLo), __as_uint16(vOutLo));
                __vstore_pred_pack_byte(vpStoreHi, __SA2ADV(uchar16, pBDataHi), __as_uint16(vOutHi));

                vpStore   = __SA0_VPRED(short32);
                vpStoreLo = __pdupl2h_pp(vpStore);
                vpStoreHi = __pduph2h_pp(vpStore);

                vOutLo = __permute_low_low(vMask, __as_uchar64(vR3s), __as_uchar64(vR2s));
                vOutHi = __permute_high_high(vMask, __as_uchar64(vR3s), __as_uchar64(vR2s));

                __vstore_pred_pack_byte(vpStoreLo, __SA0(uchar16, pRDataLo), __as_uint16(vOutLo));
                __vstore_pred_pack_byte(vpStoreHi, __SA0ADV(uchar16, pRDataHi), __as_uint16(vOutHi));

                vOutLo = __permute_low_low(vMask, __as_uchar64(vG3s), __as_uchar64(vG2s));
                vOutHi = __permute_high_high(vMask, __as_uchar64(vG3s), __as_uchar64(vG2s));

                __vstore_pred_pack_byte(vpStoreLo, __SA1(uchar16, pGDataLo), __as_uint16(vOutLo));
                __vstore_pred_pack_byte(vpStoreHi, __SA1ADV(uchar16, pGDataHi), __as_uint16(vOutHi));

                vOutLo = __permute_low_low(vMask, __as_uchar64(vB3s), __as_uchar64(vB2s));
                vOutHi = __permute_high_high(vMask, __as_uchar64(vB3s), __as_uchar64(vB2s));

                __vstore_pred_pack_byte(vpStoreLo, __SA2(uchar16, pBDataLo), __as_uint16(vOutLo));
                __vstore_pred_pack_byte(vpStoreHi, __SA2ADV(uchar16, pBDataHi), __as_uint16(vOutHi));

            }
        }

        __SE0_CLOSE();
        __SE1_CLOSE();

        __SA0_CLOSE();
        __SA1_CLOSE();
        __SA2_CLOSE();

    }
    return (status);

}

VXLIB_STATUS VXLIB_convert_NV12_to_RGBpl_checkParams
(
    uint8_t *yData,
    VXLIB_bufParams2D_t *y_addr,
    uint8_t *cbcrData,
    VXLIB_bufParams2D_t *cbcr_addr,
    uint8_t *rgbData,
    VXLIB_bufParams3D_t *rgb_addr,
    const int16_t coeff[5],
    void *pBlock
)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

    return (status);
}
