/*
* module name       : c7x_fast9Corners
*
* module descripton : Computes FAST9 corners
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#include "VXLIB_fastCornersDetect_i8u.h"

#ifdef _DISPLAY_PARAMS
#include "paramv.h"
#endif

#define FAST9_DIAMETER (6)

#define SIMD_WIDTH_SHIFT_8BIT       (6) /* 2^6 = 64x8b elements in a 512b vector */
#define SIMD_WIDTH_8BIT             (1 << SIMD_WIDTH_SHIFT_8BIT)
#define SIMD_WIDTH_RND_8BIT         (SIMD_WIDTH_8BIT >> 1)
#define ALIGN_SIMD_WIDTH_8BIT(a)    (((a) + SIMD_WIDTH_8BIT-1) & ~(SIMD_WIDTH_8BIT-1))
#define NUM_SIMD_BLOCKS_8BIT(width) (((width) + (SIMD_WIDTH_8BIT - 1)) >> SIMD_WIDTH_SHIFT_8BIT)


#define SIMD_WIDTH_SHIFT_16BIT       (5) /* 2^5 = 32x16b elements in a 512b vector */
#define SIMD_WIDTH_16BIT             (1 << SIMD_WIDTH_SHIFT_16BIT)
#define SIMD_WIDTH_RND_16BIT         (SIMD_WIDTH_16BIT >> 1)
#define ALIGN_SIMD_WIDTH_16BIT(a)    (((a) + SIMD_WIDTH_16BIT-1) & ~(SIMD_WIDTH_16BIT-1))
#define NUM_SIMD_BLOCKS_16BIT(width) (((width) + (SIMD_WIDTH_16BIT - 1)) >> SIMD_WIDTH_SHIFT_16BIT)

#define CONFIG_PARAM_BASE        (0x0000)
#define SE_COPY_PARAM_OFFSET     (CONFIG_PARAM_BASE)
#define SA_COPY_PARAM_OFFSET     (SE_COPY_PARAM_OFFSET + SE_PARAM_SIZE)
#define COPY_MASK_OFFSET         (SA_COPY_PARAM_OFFSET + SA_PARAM_SIZE)
#define SE_STAGE1_PARAM1_OFFSET  (COPY_MASK_OFFSET        + SE_PARAM_SIZE)
#define SE_STAGE1_PARAM2_OFFSET  (SE_STAGE1_PARAM1_OFFSET + SE_PARAM_SIZE)
#define SA_STAGE1_PARAM1_OFFSET  (SE_STAGE1_PARAM2_OFFSET + SE_PARAM_SIZE)
#define SE_STAGE1_MASK1_OFFSET   (SA_STAGE1_PARAM1_OFFSET + SA_PARAM_SIZE)
#define SE_STAGE1_MASK2_OFFSET   (SE_STAGE1_MASK1_OFFSET  + SE_PARAM_SIZE)
#define SE_STAGE1_MASK3_OFFSET   (SE_STAGE1_MASK2_OFFSET  + SE_PARAM_SIZE)
#define SE_STAGE2_PARAM1_OFFSET  (SE_STAGE1_MASK3_OFFSET  + SE_PARAM_SIZE)
#define SA_STAGE2_PARAM1_OFFSET  (SE_STAGE2_PARAM1_OFFSET + SE_PARAM_SIZE)
#define SE_STAGE3_PARAM1_OFFSET  (SA_STAGE2_PARAM1_OFFSET + SA_PARAM_SIZE)

#define HOP_DIST    (16)
#define GET_NUM_HOPS(a) (a) < (HOP_DIST) ? 1 : (((a) + ((HOP_DIST)/2))/(HOP_DIST))

void copyInput_init
(
    uint8_t *restrict pSrc,
    uint8_t *restrict pDst,
    int32_t inWidth,
    int32_t inHeight,
    int32_t inStride,
    int32_t outStride,
    void *pBlock
)
{
    __STRM_TEMPLATE seTemplate;
    __STRM_TEMPLATE saTemplate;

    __SE_FLAGS seFlags;
    __SA_FLAGS saFlags;

    __STRM_PARAM_3D s3DParam;

    seFlags = __SE_FLAGS_default();

    seFlags.ELETYPE   = __SE_ELETYPE_8BIT;
    seFlags.VECLEN    = __SE_VECLEN_64ELEMS;
    seFlags.DECDIM1   = __SE_DECDIM_DIM1;

    int32_t num_hops = GET_NUM_HOPS(inWidth);

    s3DParam.DECDIM1_WIDTH = inWidth;
    s3DParam.ICNT0 = SIMD_WIDTH_8BIT;
    s3DParam.ICNT1 = num_hops;
    s3DParam.ICNT2 = inHeight;

    s3DParam.DIM1  = HOP_DIST;
    s3DParam.DIM2  = inStride;

    seTemplate = __SE_SET_PARAM_3D(&s3DParam, &seFlags);
    *stov_ptr(__STRM_TEMPLATE,  (uint32_t *)((uint8_t *)pBlock + SE_COPY_PARAM_OFFSET)) = seTemplate;

    saFlags = __SA_FLAGS_default();

    saFlags.VECLEN = __SA_VECLEN_64ELEMS;

    s3DParam.ICNT0 = SIMD_WIDTH_8BIT * num_hops;
    s3DParam.ICNT1 = inHeight;
    s3DParam.ICNT2 = 1;

    s3DParam.DIM1 = SIMD_WIDTH_8BIT * num_hops;
    s3DParam.DIM2 = 0;

    saTemplate = __SA_SET_PARAM_3D(&s3DParam, &saFlags);
    *stov_ptr(__STRM_TEMPLATE, (uint32_t *)((uint8_t *)pBlock + SA_COPY_PARAM_OFFSET)) = saTemplate;

    ulong8 vMask = (ulong8)(0);

    vMask.s0 = 0x0706050403020100;
    vMask.s1 = 0x0908070605040302;
    vMask.s2 = 0x0B0A090807060504;
    vMask.s3 = 0x0D0C0B0A09080706;
    vMask.s4 = 0x0F0E0D0C0B0A0908;
    vMask.s5 = 0x11100F0E0D0C0B0A;
    vMask.s6 = 0x131211100F0E0D0C;
    vMask.s7 = 0x1514131211100F0E;

    *stov_ptr(uchar64, (uint8_t *)pBlock + COPY_MASK_OFFSET) = __as_uchar64(vMask);

    return;
}

VXLIB_STATUS VXLIB_fastCornersDetect_i8u_init
(
    const uint8_t src[],
    const VXLIB_bufParams2D_t *src_addr,
    uint32_t corners[],
    uint32_t corners_capacity,
    uint8_t strength_thresh,
    uint32_t *num_corners,
    uint8_t scratch[],
    void *pBlock
)
{
    VXLIB_STATUS status = VXLIB_SUCCESS;
    __STRM_TEMPLATE seTemplate;
    __STRM_TEMPLATE saTemplate;

    __SE_FLAGS seFlags;
    __SA_FLAGS saFlags;

    __STRM_PARAM_3D s3DParam;

#if defined(VXLIB_CHECK_PARAMS) || defined(VXLIB_FASTCORNERSDETECT_I8U_CHECK_PARAMS)
    status = VXLIB_fastCornersDetect_i8u_checkParams(src, src_addr, corners, corners_capacity, strength_thresh, num_corners, scratch);
    if( status == VXLIB_SUCCESS )
#endif
    {
        int32_t inWidth  = src_addr->dim_x;
        int32_t inHeight = src_addr->dim_y;

        int32_t inBitDepth = VXLIB_sizeof(src_addr->data_type);
        int32_t inStride = src_addr->stride_y / inBitDepth;

        int32_t outWidth  = inWidth  - FAST9_DIAMETER;
        int32_t outHeight = inHeight - FAST9_DIAMETER;

        int32_t num_hops = GET_NUM_HOPS(inWidth);

        copyInput_init(NULL, NULL, inWidth, inHeight, inStride, inStride, pBlock);

        seFlags = __SE_FLAGS_default();

        seFlags.ELETYPE   = __SE_ELETYPE_64BIT;
        seFlags.TRANSPOSE = __SE_TRANSPOSE_64BIT;
        seFlags.VECLEN    = __SE_VECLEN_8ELEMS;

        s3DParam.ICNT0 = (((outWidth + 2) >> 2) << 1);
        s3DParam.ICNT1 = 8;
        s3DParam.ICNT2 = (outHeight + 1) >> 1;

        s3DParam.DIM1  = ((SIMD_WIDTH_8BIT * num_hops) / 8);
        s3DParam.DIM2  = ((SIMD_WIDTH_8BIT * num_hops) / 8) * 2;

        seTemplate = __SE_SET_PARAM_3D(&s3DParam, &seFlags);
        *stov_ptr(__STRM_TEMPLATE, (uint32_t *)((uint8_t *)pBlock + SE_STAGE1_PARAM1_OFFSET)) = seTemplate;

        saFlags = __SA_FLAGS_default();

        saFlags.VECLEN = __SA_VECLEN_8ELEMS;

        s3DParam.ICNT0 = ((outWidth  + 2) >> 2) * 8;
        s3DParam.ICNT1 = (outHeight + 1) >> 1;
        s3DParam.ICNT2 = 1;

        s3DParam.DIM1  = (((outWidth  + 2) >> 2) << 2) * 4;
        s3DParam.DIM2  = 0;

        saTemplate = __SA_SET_PARAM_3D(&s3DParam, &saFlags);
        *stov_ptr(__STRM_TEMPLATE, (uint32_t *)((uint8_t *)pBlock + SA_STAGE1_PARAM1_OFFSET)) = saTemplate;

        ulong8 vMASK = (ulong8)(0);

        vMASK.s0 = 0x1e15160d0c0b0403;
        vMASK.s1 = 0x3c35342d2e26261e;
        vMASK.s2 = 0x283120293a3b3233;
        vMASK.s3 = 0x0a11020918201018;
        vMASK.s4 = 0x1f16170e0d0c0504;
        vMASK.s5 = 0x3d36352e2f27271f;
        vMASK.s6 = 0x2932212a3b3c3334;
        vMASK.s7 = 0x0b12030a19211119;

        *stov_ptr(uchar64, (uint8_t *)pBlock + SE_STAGE1_MASK1_OFFSET) = __as_uchar64(vMASK);

        vMASK.s0 = 0x401b401b401b401b;
        vMASK.s1 = 0x401b401b401b401b;
        vMASK.s2 = 0x401b401b401b401b;
        vMASK.s3 = 0x401b401b401b401b;
        vMASK.s4 = 0x401c401c401c401c;
        vMASK.s5 = 0x401c401c401c401c;
        vMASK.s6 = 0x401c401c401c401c;
        vMASK.s7 = 0x401c401c401c401c;

        *stov_ptr(uchar64, (uint8_t *)pBlock + SE_STAGE1_MASK2_OFFSET) = __as_uchar64(vMASK);

        vMASK.s0 = 0x4023402340234023;
        vMASK.s1 = 0x4023402340234023;
        vMASK.s2 = 0x4023402340234023;
        vMASK.s3 = 0x4023402340234023;
        vMASK.s4 = 0x4024402440244024;
        vMASK.s5 = 0x4024402440244024;
        vMASK.s6 = 0x4024402440244024;
        vMASK.s7 = 0x4024402440244024;

        *stov_ptr(uchar64, (uint8_t *)pBlock + SE_STAGE1_MASK3_OFFSET) = __as_uchar64(vMASK);

        seFlags = __SE_FLAGS_default();

        seFlags.ELETYPE   = __SE_ELETYPE_16BIT;
        seFlags.VECLEN    = __SE_VECLEN_32ELEMS;

        s3DParam.ICNT0 = outWidth;
        s3DParam.ICNT1 = outHeight;
        s3DParam.ICNT2 = 1;

        s3DParam.DIM1  = ((outWidth  + 2) >> 2) << 2;
        s3DParam.DIM2  = 0;

        seTemplate = __SE_SET_PARAM_3D(&s3DParam, &seFlags);
        *stov_ptr(__STRM_TEMPLATE, (uint32_t *)((uint8_t *)pBlock + SE_STAGE2_PARAM1_OFFSET)) = seTemplate;

        saFlags = __SA_FLAGS_default();

        saFlags.VECLEN = __SA_VECLEN_32ELEMS;

        s3DParam.ICNT0 = outWidth;
        s3DParam.ICNT1 = outHeight;
        s3DParam.ICNT2 = 1;

        s3DParam.DIM1 = ((outWidth + 31) / 32) * 32;
        s3DParam.DIM2 = 0;

        saTemplate = __SA_SET_PARAM_3D(&s3DParam, &saFlags);
        *stov_ptr(__STRM_TEMPLATE, (uint32_t *)((uint8_t *)pBlock + SA_STAGE2_PARAM1_OFFSET)) = saTemplate;

        seFlags = __SE_FLAGS_default();

        seFlags.ELETYPE   = __SE_ELETYPE_8BIT;
        seFlags.PROMOTE   = __SE_PROMOTE_4X_ZEROEXT;
        seFlags.VECLEN    = __SE_VECLEN_16ELEMS;

        s3DParam.ICNT0 = outWidth;
        s3DParam.ICNT1 = outHeight;
        s3DParam.ICNT2 = 1;

        s3DParam.DIM1  = ((outWidth + 31) / 32) * 32;
        s3DParam.DIM2  = 0;

        seTemplate = __SE_SET_PARAM_3D(&s3DParam, &seFlags);
        *stov_ptr(__STRM_TEMPLATE, (uint32_t *)((uint8_t *)pBlock + SE_STAGE3_PARAM1_OFFSET)) = seTemplate;
    }

    return (status);
}


void copyInput
(
    uint8_t *restrict pSrc,
    uint8_t *restrict pDst,
    int32_t inWidth,
    int32_t inHeight,
    int32_t inStride,
    int32_t outStride,
    void *pBlock
)
{
    __STRM_TEMPLATE seTemplate;
    __STRM_TEMPLATE saTemplate;

    int32_t idX, idY;

    seTemplate = *stov_ptr(__STRM_TEMPLATE, (uint32_t *)((uint8_t *)pBlock + SE_COPY_PARAM_OFFSET));
    __SE0_OPEN((void *)pSrc, seTemplate);

#ifdef _DISPLAY_PARAMS
        displaySEParam((void *)pSrc, seTemplate, PARAMV_SE0);
#endif

    saTemplate = *stov_ptr(__STRM_TEMPLATE, (uint32_t *)((uint8_t *)pBlock + SA_COPY_PARAM_OFFSET));
    __SA0_OPEN(saTemplate);

#ifdef _DISPLAY_PARAMS
        displaySAParam((void *)pDst, saTemplate, PARAMV_SA0);
#endif

    uchar64 vMask = *stov_ptr(uchar64, (uint8_t *)pBlock + COPY_MASK_OFFSET);

    int32_t num_hops = GET_NUM_HOPS(inWidth);

#pragma MUST_ITERATE(1,,)
    for(idY = 0; idY < inHeight; idY++)
    {
#pragma MUST_ITERATE(1,,)
        for(idX = 0; idX < num_hops; idX++)
        {
            __vpred vpStore = __SA0_VPRED(uchar64);
            __vstore_pred(vpStore, __SA0ADV(uchar64, pDst), __permute(vMask, __SE0ADV(uchar64)));
        }
    }

    __SA0_CLOSE();
    __SE0_CLOSE();

    return;
}

VXLIB_STATUS VXLIB_fastCornersDetect_i8u_kernel
(
    const uint8_t src[],
    const VXLIB_bufParams2D_t *src_addr,
    uint32_t corners[],
    uint32_t corners_capacity,
    uint8_t strength_thresh,
    uint32_t *num_corners,
    uint8_t scratch[],
    void *pBlock
)
{
    VXLIB_STATUS status = VXLIB_SUCCESS;

    __STRM_TEMPLATE seTemplate;
    __STRM_TEMPLATE saTemplate;

#if defined(VXLIB_CHECK_PARAMS) || defined(VXLIB_FASTCORNERSDETECT_I8U_CHECK_PARAMS)
    status = VXLIB_fastCornersDetect_i8u_checkParams(src, src_addr, corners, corners_capacity, strength_thresh, num_corners, scratch);
    if( status == VXLIB_SUCCESS )
#endif
    {
        int32_t inWidth  = src_addr->dim_x;
        int32_t inHeight = src_addr->dim_y;

        int32_t inBitDepth = VXLIB_sizeof(src_addr->data_type);
        int32_t inStride = src_addr->stride_y / inBitDepth;

        int32_t outWidth  = inWidth  - FAST9_DIAMETER;
        int32_t outHeight = inHeight - FAST9_DIAMETER;

        uint8_t *restrict pSrc1;
        uint8_t *restrict pSrc2;

        uint64_t *restrict pDstT1;
        uint64_t *restrict pDstB1;
        uint64_t *restrict pDstT2;
        uint64_t *restrict pDstB2;

        uint8_t *restrict pMask;

        int32_t blkX, blkY;
        int32_t outStride;

        int32_t num_hops = GET_NUM_HOPS(inWidth);

        short32 vTh1 = (short32) strength_thresh;
        short32 vTh2 = (short32) -strength_thresh;

        outStride = ((outWidth + 2) >> 2) << 2;

        pSrc1  = (uint8_t  *)src;
        pSrc2  = (uint8_t  *)scratch;
        pDstT1 = (uint64_t *)((uint8_t  *)pSrc2  + (SIMD_WIDTH_8BIT * num_hops * inHeight));
        pDstB1 = (uint64_t *)((uint16_t *)pDstT1 + outStride);
        pDstT2 = (uint64_t *)((uint16_t *)pDstT1 + (outStride * outHeight));
        pDstB2 = (uint64_t *)((uint16_t *)pDstT2 + outStride);
        pMask  = (uint8_t  *)((uint16_t *)pDstT2 + (outStride * outHeight));

        copyInput(pSrc1, pSrc2, inWidth, inHeight, inStride, inStride, pBlock);

        seTemplate = *stov_ptr(__STRM_TEMPLATE, (uint32_t *)((uint8_t *)pBlock + SE_STAGE1_PARAM1_OFFSET));
        __SE0_OPEN((void *)pSrc2, seTemplate);

#ifdef _DISPLAY_PARAMS
        displaySEParam((void *)pSrc2, seTemplate, PARAMV_SE0);
#endif

        saTemplate = *stov_ptr(__STRM_TEMPLATE, (uint32_t *)((uint8_t *)pBlock + SA_STAGE1_PARAM1_OFFSET));
        __SA0_OPEN(saTemplate);

#ifdef _DISPLAY_PARAMS
        displaySAParam((void *)pDstT2, saTemplate, PARAMV_SA0);
        displaySAParam((void *)pDstB2, saTemplate, PARAMV_SA0);
#endif

        uchar64 vMask1 = *stov_ptr(uchar64, (uint8_t *)pBlock + SE_STAGE1_MASK1_OFFSET);
        uchar64 vMask2 = *stov_ptr(uchar64, (uint8_t *)pBlock + SE_STAGE1_MASK2_OFFSET);
        uchar64 vMask3 = *stov_ptr(uchar64, (uint8_t *)pBlock + SE_STAGE1_MASK3_OFFSET);

#pragma MUST_ITERATE(1,,)
        for(blkY = 0; blkY < outHeight; blkY+=2)
        {
#pragma MUST_ITERATE(1,,)
            for(blkX = 0; blkX < outWidth; blkX+=4)
            {
                uchar64 vIn;

                short32 vTop10, vTop32;
                short32 vBot10, vBot32;

                short32 vT10, vT32;
                short32 vB10, vB32;

                short32 vTDiff10, vTDiff32;
                short32 vBDiff10, vBDiff32;

                __vpred vpT10, vpT32;
                __vpred vpB10, vpB32;
                __vpred vpT3210, vpB3210;

                vIn    = __permute(vMask1, __SE0(uchar64));
                vTop10 = __as_short32(__unpack_low(vIn));
                vBot10 = __as_short32(__unpack_high(vIn));

                vT10 = __as_short32(__permute(vMask2, __SE0(uchar64)));
                vB10 = __as_short32(__permute(vMask3, __SE0ADV(uchar64)));

                vTDiff10 = vT10 - vTop10;
                vBDiff10 = vB10 - vBot10;

                vIn    = __permute(vMask1, __SE0(uchar64));
                vTop32 = __as_short32(__unpack_low(vIn));
                vBot32 = __as_short32(__unpack_high(vIn));

                vT32 = __as_short32(__permute(vMask2, __SE0(uchar64)));
                vB32 = __as_short32(__permute(vMask3, __SE0ADV(uchar64)));

                vTDiff32 = vT32 - vTop32;
                vBDiff32 = vB32 - vBot32;

                vpT10   = __cmp_gt_pred(vTDiff10, vTh1);
                vpT32   = __cmp_gt_pred(vTDiff32, vTh1);
                vpB10   = __cmp_gt_pred(vBDiff10, vTh1);
                vpB32   = __cmp_gt_pred(vBDiff32, vTh1);
                vpT3210 = __decimateb_ppp(vpT32, vpT10);
                vpB3210 = __decimateb_ppp(vpB32, vpB10);

                __store_predicate_char( __SA0(ulong, pDstT1), vpT3210);
                __store_predicate_char( __SA0(ulong, pDstB1), vpB3210);

                vpT10   = __cmp_gt_pred(vTh2, vTDiff10);
                vpT32   = __cmp_gt_pred(vTh2, vTDiff32);
                vpB10   = __cmp_gt_pred(vTh2, vBDiff10);
                vpB32   = __cmp_gt_pred(vTh2, vBDiff32);
                vpT3210 = __decimateb_ppp(vpT32, vpT10);
                vpB3210 = __decimateb_ppp(vpB32, vpB10);

                __store_predicate_char( __SA0(ulong, pDstT2),  vpT3210);
                __store_predicate_char( __SA0ADV(ulong, pDstB2), vpB3210);

            }
        }

        __SE0_CLOSE();
        __SA0_CLOSE();

        seTemplate = *stov_ptr(__STRM_TEMPLATE, (uint32_t *)((uint8_t *)pBlock + SE_STAGE2_PARAM1_OFFSET));
        __SE0_OPEN((void *)pDstT1, seTemplate);
        __SE1_OPEN((void *)pDstT2, seTemplate);

#ifdef _DISPLAY_PARAMS
        displaySEParam((void *)pDstT1, seTemplate, PARAMV_SE0);
        displaySEParam((void *)pDstT2, seTemplate, PARAMV_SE1);
#endif
        saTemplate = *stov_ptr(__STRM_TEMPLATE, (uint32_t *)((uint8_t *)pBlock + SA_STAGE2_PARAM1_OFFSET));
        __SA0_OPEN(saTemplate);

#ifdef _DISPLAY_PARAMS
        displaySAParam((void *)pMask, saTemplate, PARAMV_SA0);
#endif

#pragma MUST_ITERATE(1,,)
        for (blkY = 0; blkY < outHeight; blkY++)
        {
#pragma MUST_ITERATE(1,,)
            for (blkX = 0; blkX < outWidth; blkX+=SIMD_WIDTH_16BIT)
            {
                ushort32 var0, var2, var4, var6;
                short32 res;

                var4 = __vrotlh_vkv(__SE0(ushort32), (ushort32)(1));
                var6 = __vrotlh_vkv(__SE1(ushort32), (ushort32)(1));

                var0 = __SE0ADV(ushort32) & var4;
                var2 = __SE1ADV(ushort32) & var6;

                var4 = __vrotlh_vkv(var0, (ushort32)(2));
                var6 = __vrotlh_vkv(var2, (ushort32)(2));

                var0 = var0 & var4;
                var2 = var2 & var6;

                var4 = __vrotlh_vkv(var0, (ushort32)(4));
                var6 = __vrotlh_vkv(var2, (ushort32)(4));

                var0 = var0 & var4;
                var2 = var2 & var6;

                var4 = __vrotlh_vkv(var0, (ushort32)(1));
                var6 = __vrotlh_vkv(var2, (ushort32)(1));

                var0 = var0 & var4;
                var2 = var2 & var6;

                var0  = var0 | var2;

                __vpred pred0 = __cmp_eq_pred( (short32)(0), __as_short32(var0));
                res= __select( pred0, (short32)(0), (short32)(1));
                __vstore_packl(__SA0ADV(char32, pMask), res);
           }
        }

       __SE0_CLOSE();
       __SE1_CLOSE();
       __SA0_CLOSE();


        seTemplate = *stov_ptr(__STRM_TEMPLATE, (uint32_t *)((uint8_t *)pBlock + SE_STAGE3_PARAM1_OFFSET));
       __SE0_OPEN((void *)pMask, seTemplate);

       int32_t numCornersIn= 0;
       uint16 vWidth;
       uint16 vHeight= (uint16)(3<<16);
       uint16 vCoord;
       uint16 v00010000, v16, vOne;
       uint16 vWidthInit;

       v00010000 = (uint16)(0x00010000);
       v16       = (uint16)(16);
       vOne      = (uint16)(1);

       vWidthInit.s0= 0; vWidthInit.s1= 1; vWidthInit.s2= 2; vWidthInit.s3= 3;
       vWidthInit.s4= 4; vWidthInit.s5= 5; vWidthInit.s6= 6; vWidthInit.s7= 7;
       vWidthInit.s8= 8; vWidthInit.s9= 9; vWidthInit.sA= 10; vWidthInit.sB= 11;
       vWidthInit.sC= 12; vWidthInit.sD= 13; vWidthInit.sE= 14; vWidthInit.sF= 15;

       vWidthInit= vWidthInit + (uint16)(3);

#pragma MUST_ITERATE(1,,)
       for (blkY = 0; blkY < outHeight; blkY++)
       {
           uint32_t numElements = outWidth;
           vWidth= vWidthInit;
#pragma MUST_ITERATE(1,,)
           for (blkX = 0; blkX < outWidth; blkX += 16)
           {
                vpred vpflag1= __vcmpeqw_vvp(__SE0ADV(uint16), vOne);

                vCoord= vHeight | vWidth;
                vCoord= __as_uint16(__vgatherb_pvv(vpflag1, __as_char64(vCoord)));
                vpflag1 = __compressr_pp(vpflag1);

                if (numCornersIn < corners_capacity)
                {
                   uint16_ptr pOut = stov_ptr(uint16, (uint32_t *)&corners[numCornersIn]);
                    __vstore_pred(vpflag1, pOut, vCoord);
                }

                numCornersIn = numCornersIn + __pbitcntw_pr(vpflag1);
                vWidth= vWidth + v16;
                numElements= numElements - 16;
           }
           vHeight= vHeight + v00010000;
       }

       *num_corners= numCornersIn;

       __SE0_CLOSE();

    }

    return (status);
}

VXLIB_STATUS VXLIB_fastCornersDetect_i8u_checkParams
(
    const uint8_t src[],
    const VXLIB_bufParams2D_t *src_addr,
    const uint32_t corners[],
    uint32_t corners_capacity,
    uint8_t strength_thresh,
    const uint32_t *num_corners,
    const uint8_t scratch[],
    void *pBlock
)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

    if((src == NULL) || (corners == NULL) || (num_corners == NULL) || (scratch == NULL) || (pBlock == NULL)) {
        status = VXLIB_ERR_NULL_POINTER;
    } else if (((uint64_t)scratch & 3) != NULL) {
        status = VXLIB_ERR_NOT_ALIGNED_PTRS_STRIDES;
    } else if( src_addr->stride_y < src_addr->dim_x ) {
        status = VXLIB_ERR_INVALID_DIMENSION;
    } else if( src_addr->stride_y & 3 ) {
        status = VXLIB_ERR_INVALID_DIMENSION;
    } else if( corners_capacity & 15 ) {
        status = VXLIB_ERR_INVALID_DIMENSION;
    } else if(src_addr->data_type != VXLIB_UINT8) {
        status = VXLIB_ERR_INVALID_TYPE;
    } else {
        status = VXLIB_SUCCESS;
    }
    return (status);
}
