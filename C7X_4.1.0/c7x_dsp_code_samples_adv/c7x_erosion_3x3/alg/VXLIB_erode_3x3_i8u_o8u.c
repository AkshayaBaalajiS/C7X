/*
* module name       : c7x_erosion_3x3
*
* module descripton : 3x3 greyscale erosion
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#include "VXLIB_erode_3x3_i8u_o8u.h"

#ifdef _DISPLAY_PARAMS
#include "paramv.h"
#endif

#define SE_PARAM_BASE    (0x0000)
#define SE_PARAM_OFFSET (SE_PARAM_BASE)
#define SA_PARAM_OFFSET (SE_PARAM_OFFSET + SE_PARAM_SIZE)
#define SA_PARAM_PRED_OFFSET (SA_PARAM_OFFSET + SA_PARAM_SIZE)

#define SIMD_WIDTH_SHIFT       (6) /* 2^6 = 64 8b elements in a 512b vector */
#define SIMD_WIDTH             (1 << SIMD_WIDTH_SHIFT)
#define SIMD_WIDTH_RND         (SIMD_WIDTH >> 1)
#define NUM_SIMD_BLOCKS(width) (((width) >> SIMD_WIDTH_SHIFT) + (((width) - (((width) >> SIMD_WIDTH_SHIFT) << SIMD_WIDTH_SHIFT)) > 0 ? 1 : 0))

VXLIB_STATUS VXLIB_erode_3x3_i8u_o8u_init(void *pIn,
                                          VXLIB_bufParams2D_t *pInParams,
                                          void *pOut,
                                          VXLIB_bufParams2D_t *pOutParams,
                                          void *pBlock)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#if defined(VXLIB_CHECK_PARAMS) || defined(VXLIB_ERODE_3X3_I8U_O8U_CHECK_PARAMS)
    status = VXLIB_erode_3x3_i8u_o8u_checkParams(src, src_addr, dst, dst_addr, pBlock);
    if( status == VXLIB_SUCCESS )
#endif
    {
        __STRM_TEMPLATE seTemplate;
        __STRM_TEMPLATE saTemplate;

        __SE_FLAGS seFlags;
        __SA_FLAGS saFlags;

        __STRM_PARAM_4D seParam;
        __STRM_PARAM_3D saParam;

        int32_t bit_depth_in  = VXLIB_sizeof(pInParams->data_type);
        int32_t inStride      = pInParams->stride_y / bit_depth_in;

        int32_t bit_depth_out = VXLIB_sizeof(pOutParams->data_type);
        int32_t outStride     = pOutParams->stride_y / bit_depth_out;

        int32_t inWidth   = pInParams->dim_x;
        int32_t inHeight  = pInParams->dim_y;

        int32_t outWidth  = pOutParams->dim_x;
        int32_t outHeight = pOutParams->dim_y;

        seFlags = __SE_FLAGS_default();

        seFlags.ELETYPE = __SE_ELETYPE_8BIT;
        seFlags.VECLEN  = __SE_VECLEN_64ELEMS;

        seParam.ICNT0 = SIMD_WIDTH;
        seParam.ICNT1 = 3;
        seParam.ICNT2 = inHeight >> 1;
        seParam.ICNT3 = NUM_SIMD_BLOCKS(inWidth);

        seParam.DIM1  = 1;
        seParam.DIM2  = inStride << 1;
        seParam.DIM3  = SIMD_WIDTH;

        seTemplate = __SE_SET_PARAM_4D(&seParam, &seFlags);
        *stov_ptr(__STRM_TEMPLATE, (uint32_t*)((uint8_t *)pBlock + SE_PARAM_OFFSET)) = seTemplate;

        /* Prepare SA 0 tempate to store output */
        saFlags = __SA_FLAGS_default();

        saFlags.DECDIM1   = __SA_DECDIM_DIM2;
        saFlags.VECLEN    = __SA_VECLEN_64ELEMS;

        /* ITERATION COUNTERS */
        saParam.DECDIM1_WIDTH = outWidth;
        saParam.ICNT0 = SIMD_WIDTH;
        saParam.ICNT1 = outHeight;
        saParam.ICNT2 = NUM_SIMD_BLOCKS(inWidth);

        /* DIMENSIONS */
        saParam.DIM1  = outStride;
        saParam.DIM2  = SIMD_WIDTH;

        saTemplate = __SA_SET_PARAM_3D(&saParam, &saFlags);
        *stov_ptr(__STRM_TEMPLATE, (uint32_t*)((uint8_t *)pBlock + SA_PARAM_OFFSET)) = saTemplate;

        /* Prepare SA 1 tempate to generate scalar predicate counter */
        saFlags = __SA_FLAGS_default();

        saFlags.VECLEN = __SA_VECLEN_2ELEMS;

        /* ITERATION COUNTERS */
        saParam.ICNT0 = inHeight;
        saParam.ICNT1 = NUM_SIMD_BLOCKS(inWidth);
        saParam.ICNT2 = 1;

        /* DIMENSIONS */
        saParam.DIM1  = 0;
        saParam.DIM2  = 0;

        saTemplate = __SA_SET_PARAM_3D(&saParam, &saFlags);
        *stov_ptr(__STRM_TEMPLATE, (uint32_t*)((uint8_t *)pBlock + SA_PARAM_PRED_OFFSET)) = saTemplate;

    }
    return (status);
}

VXLIB_STATUS VXLIB_erode_3x3_i8u_o8u_kernel(void *pIn,
                                            VXLIB_bufParams2D_t *pInParams,
                                            void *pOut,
                                            VXLIB_bufParams2D_t *pOutParams,
                                            void *pBlock)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#if defined(VXLIB_CHECK_PARAMS) || defined(VXLIB_ERODE_3X3_I8U_O8U_CHECK_PARAMS)
    status = VXLIB_erode_3x3_i8u_o8u_checkParams(src, src_addr, dst, dst_addr, pBlock);
    if( status == VXLIB_SUCCESS )
#endif
    {
        __STRM_TEMPLATE seTemplate;
        __STRM_TEMPLATE saTemplate;

        uchar64 vMinA, vMinB, vMinC, vRes, vK255;
        __vpred vpStore;

        int32_t blkX, blkY;
        int32_t numBlocks, numRows;

        int32_t bit_depth_in  = VXLIB_sizeof(pInParams->data_type);
        int32_t inStride      = pInParams->stride_y  / bit_depth_in;

        int32_t inWidth   = pInParams->dim_x;
        int32_t inHeight  = pInParams->dim_y;

        seTemplate = *stov_ptr(__STRM_TEMPLATE, (uint32_t*)((uint8_t *)pBlock + SE_PARAM_OFFSET));
        __SE0_OPEN((void *)pIn, seTemplate);
        __SE1_OPEN((void *)((uint8_t *)pIn + inStride), seTemplate);

#ifdef _DISPLAY_PARAMS
        displaySEParam((void *)pIn, seTemplate, PARAMV_SE0);
        displaySEParam((void *)((uint8_t *)pIn + inStride), seTemplate, PARAMV_SE1);
#endif

        saTemplate = *stov_ptr(__STRM_TEMPLATE, (uint32_t*)((uint8_t *)pBlock + SA_PARAM_OFFSET));
        __SA0_OPEN(saTemplate);

#ifdef _DISPLAY_PARAMS
        displaySAParam((void *)pOut, saTemplate, PARAMV_SA0);
#endif

        saTemplate = *stov_ptr(__STRM_TEMPLATE, (uint32_t*)((uint8_t *)pBlock + SA_PARAM_PRED_OFFSET));
        __SA1_OPEN(saTemplate);

#ifdef _DISPLAY_PARAMS
        displaySAParam((void *)NULL, saTemplate, PARAMV_SA1);
#endif

        numBlocks = NUM_SIMD_BLOCKS(inWidth);
        numRows   = inHeight >> 1;

        vMinA = (uchar64)(255);
        vMinB = (uchar64)(255);
        vMinC = (uchar64)(255);
        vRes  = (uchar64)(255);
        vK255 = (uchar64)(255);

#pragma MUST_ITERATE(1,,)
        for(blkX = 0; blkX < numBlocks; blkX++)
        {
#pragma MUST_ITERATE(1,,)
            for(blkY = 0; blkY < numRows; blkY++)
            {
                /* Here we are using SA to generate offsets, so vector pointer is set to NULL */
                uint8_t *pVal = vtos_ptr(uint8_t, __SA1ADV(uchar2, NULL));
                uint64_t val = (uint64_t)pVal;

                vMinA = __min(__SE0ADV(uchar64), vK255);
                vMinA = __min(__SE0ADV(uchar64), vMinA);
                vMinA = __min(__SE0ADV(uchar64), vMinA);

                vRes  = __min(vMinA, vMinC);
                vMinC = __min(vMinA, vMinB);

                if (val) {
                  vpStore = __SA0_VPRED(uchar64);
                  __vstore_pred(vpStore, __SA0ADV(uchar64, pOut), vRes);
                }

                vMinB = __min(__SE1ADV(uchar64), vK255);
                vMinB = __min(__SE1ADV(uchar64), vMinB);
                vMinB = __min(__SE1ADV(uchar64), vMinB);

                vRes   = __min(vMinB, vMinC);
                vMinC  = __min(vMinA, vMinB);

                if (val) {
                  vpStore = __SA0_VPRED(uchar64);
                  __vstore_pred(vpStore, __SA0ADV(uchar64, pOut), vRes);
                }

            }
        }

        __SA1_CLOSE();
        __SA0_CLOSE();
        __SE1_CLOSE();
        __SE0_CLOSE();
    }
    return (status);
}

VXLIB_STATUS VXLIB_erode_3x3_i8u_o8u_checkParams(void *src,
                                                 VXLIB_bufParams2D_t *src_addr,
                                                 void *dst,
                                                 VXLIB_bufParams2D_t *dst_addr,
                                                 void *pBlock)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

    return (status);
}
