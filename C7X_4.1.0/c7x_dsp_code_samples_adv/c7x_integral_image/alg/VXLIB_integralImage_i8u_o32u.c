/*
* module name       : c7x_integral_image
*
* module descripton : Computes integral image
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#include "VXLIB_integralImage_i8u_o32u.h"

#ifdef _DISPLAY_PARAMS
#include "paramv.h"
#endif

#define SIMD_WIDTH_SHIFT       (4) /* 2^4 = 16 32b elements in a 512b vector */
#define SIMD_WIDTH             (1 << SIMD_WIDTH_SHIFT)
#define SIMD_WIDTH_RND         (SIMD_WIDTH >> 1)
#define NUM_SIMD_BLOCKS(width) (((width) >> SIMD_WIDTH_SHIFT) + (((width) - (((width) >> SIMD_WIDTH_SHIFT) << SIMD_WIDTH_SHIFT)) > 0 ? 1 : 0))

#define CONFIG_PARAM_BASE  (0x0000)
#define SE0_PARAM_OFFSET   (CONFIG_PARAM_BASE)
#define SE1_PARAM_OFFSET   (SE0_PARAM_OFFSET + SE_PARAM_SIZE)
#define SA0_PARAM_OFFSET   (SE1_PARAM_OFFSET + SE_PARAM_SIZE)
#define SA1_PARAM_OFFSET   (SA0_PARAM_OFFSET + SA_PARAM_SIZE)
#define VDOTP_PARAM_OFFSET (SA1_PARAM_OFFSET + SA_PARAM_SIZE)

VXLIB_STATUS VXLIB_integralImage_i8u_o32u_init(void *pIn,
                                               VXLIB_bufParams2D_t *pInParams,
                                               void *pOut,
                                               VXLIB_bufParams2D_t *pOutParams,
                                               uint32_t *pPrevRow,
                                               uint32_t *pPrevCol,
                                               uint32_t *pPrevRowUpdate,
                                               void *pBlock)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#if defined(VXLIB_CHECK_PARAMS) || defined(VXLIB_INTEGRALIMAGE_I8U_O32U_CHECK_PARAMS)
    status = VXLIB_integralImage_i8u_o32u_checkParams(pIn, pInParams, pOut, pOutParams, pPrevRow, pPrevCol, pPrevRowUpdate, pBlock);
    if( status == VXLIB_SUCCESS )
#endif
    {
        __STRM_TEMPLATE seTemplate;
        __STRM_TEMPLATE saTemplate;

        __SE_FLAGS seFlags;
        __SA_FLAGS saFlags;

        __STRM_PARAM_3D seParam;
        __STRM_PARAM_3D saParam;

        int32_t numBytes;
        int32_t stride_y_out;

        seParam.ICNT0 = SIMD_WIDTH;
        seParam.ICNT1 = pInParams->dim_y;
        seParam.ICNT2 = NUM_SIMD_BLOCKS(pInParams->dim_x);

        seParam.DIM1  = pInParams->stride_y;
        seParam.DIM2  = SIMD_WIDTH;

        seFlags = __SE_FLAGS_default();

        seFlags.ELETYPE   = __SE_ELETYPE_8BIT;
        seFlags.PROMOTE   = __SE_PROMOTE_2X_ZEROEXT;
        seFlags.VECLEN    = __SE_VECLEN_16ELEMS;

        // SETUP TEMPLATE VECTOR BASED ON SETTINGS
        seTemplate = __SE_SET_PARAM_3D(&seParam, &seFlags);
        *stov_ptr(uint16, (uint32_t *)((uint8_t *)pBlock + SE0_PARAM_OFFSET)) = seTemplate;

        seFlags = __SE_FLAGS_default();

        seFlags.ELETYPE   = __SE_ELETYPE_32BIT;
        seFlags.ELEDUP    = __SE_ELEDUP_16X;
        seFlags.VECLEN    = __SE_VECLEN_16ELEMS;

        seParam.ICNT0 = 16;
        seParam.ICNT1 = pOutParams->dim_y/16;
        seParam.ICNT2 = NUM_SIMD_BLOCKS(pOutParams->dim_x);

        seParam.DIM1  = CACHE_LINE_SIZE;
        seParam.DIM2  = 0;

        // SETUP TEMPLATE VECTOR BASED ON SETTINGS
        seTemplate = __SE_SET_PARAM_3D(&seParam, &seFlags);
        *stov_ptr(uint16, (uint32_t *)((uint8_t *)pBlock + SE1_PARAM_OFFSET)) = seTemplate;

        //Prepare SA 0 tempate to store Output
        saFlags = __SA_FLAGS_default();

        saFlags.DECDIM1  = __SA_DECDIM_DIM2;
        saFlags.VECLEN   = __SA_VECLEN_16ELEMS;

        // ITERATION COUNTERS
        saParam.DECDIM1_WIDTH = pOutParams->dim_x;
        saParam.ICNT0 = SIMD_WIDTH;
        saParam.ICNT1 = pOutParams->dim_y;
        saParam.ICNT2 = NUM_SIMD_BLOCKS(pOutParams->dim_x);

        numBytes = VXLIB_sizeof(pOutParams->data_type);
        stride_y_out = pOutParams->stride_y / numBytes;

        // DIMENSIONS
        saParam.DIM1  = stride_y_out;
        saParam.DIM2  = SIMD_WIDTH;

        // SETUP TEMPLATE VECTOR BASED ON SETTINGS
        saTemplate = __SA_SET_PARAM_3D(&saParam, &saFlags);
        *stov_ptr(uint16, (uint32_t *)((uint8_t *)pBlock + SA0_PARAM_OFFSET)) = saTemplate;

        //Prepare SA 1 tempate to store partials
        saFlags = __SA_FLAGS_default();

        saFlags.VECLEN   = __SA_VECLEN_1ELEM;

        // ITERATION COUNTERS
        saParam.ICNT0 = 16;
        saParam.ICNT1 = pOutParams->dim_y/16;
        saParam.ICNT2 = NUM_SIMD_BLOCKS(pOutParams->dim_x);

        // DIMENSIONS
        saParam.DIM1  = CACHE_LINE_SIZE;
        saParam.DIM2  = 0;

        // SETUP TEMPLATE VECTOR BASED ON SETTINGS
        saTemplate = __SA_SET_PARAM_3D(&saParam, &saFlags);
        *stov_ptr(uint16, (uint32_t *)((uint8_t *)pBlock + SA1_PARAM_OFFSET)) = saTemplate;

        ulong8  vHorzSumMask = (ulong8) 0x0000000000000000;
        // Combine a 256 bit mask to obtain 0 to 15 integral sums.
        vHorzSumMask.s0 = 0x000F000700030001;
        vHorzSumMask.s1 = 0x00FF007F003F001F;
        vHorzSumMask.s2 = 0x0FFF07FF03FF01FF;
        vHorzSumMask.s3 = 0xFFFF7FFF3FFF1FFF;

        *stov_ptr(ushort32, (uint16_t *)((uint8_t *)pBlock + VDOTP_PARAM_OFFSET)) = __as_ushort32(vHorzSumMask);
    }
    return (status);
}

VXLIB_STATUS VXLIB_integralImage_i8u_o32u_kernel(void *pIn,
                                                 VXLIB_bufParams2D_t *pInParams,
                                                 void *pOut,
                                                 VXLIB_bufParams2D_t *pOutParams,
                                                 uint32_t *pPrevRow,
                                                 uint32_t *pPrevCol,
                                                 uint32_t *pPrevRowUpdate,
                                                 void *pBlock)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#if defined(VXLIB_CHECK_PARAMS) || defined(VXLIB_INTEGRALIMAGE_I8U_O32U_CHECK_PARAMS)
    status = VXLIB_integralImage_i8u_o32u_checkParams(pIn, pInParams, pOut, pOutParams, pPrevRow, pPrevCol, pPrevRowUpdate, pBlock);
    if( status == VXLIB_SUCCESS )
#endif
    {
        __STRM_TEMPLATE seTemplate;
        __STRM_TEMPLATE saTemplate;

        uint16 vSum, vHorzSum;
        ushort32 vHorSumMask;
        int32_t i, j;

        int32_t outCols = pOutParams->dim_x;
        int32_t outRows = pOutParams->dim_y;

        int32_t numBlocks;

        //Read template and open stream 0
        seTemplate = *stov_ptr(uint16, (uint32_t *)((uint8_t *)pBlock + SE0_PARAM_OFFSET));
        __SE0_OPEN((void*)pIn, seTemplate);

#ifdef _DISPLAY_PARAMS
        displaySEParam((void *)pIn, seTemplate, PARAMV_SE0);
#endif

        //Read template and open agen 0
        saTemplate = *stov_ptr(uint16, (uint32_t *)((uint8_t *)pBlock + SA0_PARAM_OFFSET));
        __SA0_OPEN(saTemplate);

#ifdef _DISPLAY_PARAMS
        displaySAParam((void *)pOut, saTemplate, PARAMV_SA0);
#endif

        vHorSumMask = *stov_ptr(ushort32, (uint16_t *)((uint8_t *)pBlock + VDOTP_PARAM_OFFSET));

        numBlocks = NUM_SIMD_BLOCKS(outCols);

        //Read template and open stream 1
        seTemplate = *stov_ptr(uint16, (uint32_t *)((uint8_t *)pBlock + SE1_PARAM_OFFSET));

        //Read template and open agen 1
        saTemplate = *stov_ptr(uint16, (uint32_t *)((uint8_t *)pBlock + SA1_PARAM_OFFSET));

#pragma MUST_ITERATE(1,,)
        for (i = 0; i < numBlocks; i++)
        {
            uint32_t *restrict pPing;
            uint32_t *restrict pPong;

            vSum = *stov_ptr(uint16, (uint32_t*) &pPrevRow[i * SIMD_WIDTH]);

            if(i & 1)
            {
              pPong = (uint32_t *)pPrevCol;
              pPing = (uint32_t *)(pPrevCol + 16);
            }
            else
            {
              pPing = (uint32_t *)pPrevCol;
              pPong = (uint32_t *)(pPrevCol + 16);
            }

            __SE1_OPEN((void *)pPing, seTemplate);
            __SA1_OPEN(saTemplate);

#ifdef _DISPLAY_PARAMS
        displaySEParam((void *)pLastCol, seTemplate, PARAMV_SE1);
        displaySAParam((void *)pLastCol, saTemplate, PARAMV_SA1);
#endif

#pragma MUST_ITERATE(1,,)
            for(j = 0; j < outRows; j++)
            {
                vHorzSum   = __dot_posneg256_mask(vHorSumMask, (ushort16)0, __SE0ADV(ushort16));
                vHorzSum   = vHorzSum + __SE1ADV(uint16);

                vSum = vSum + vHorzSum;
                *__SA1ADV(uint, pPong) = vHorzSum.sF;

                __vpred vpStore = __SA0_VPRED(uint16);
                __vstore_pred(vpStore, __SA0ADV(uint16, pOut), vSum);
            }
            __SE1_CLOSE();
            __SA1_CLOSE();

            *stov_ptr(uint16, (uint32_t *) &pPrevRow[i * SIMD_WIDTH]) = vSum;
        }

        //Close agen
        __SA0_CLOSE();
        //Close streams
        __SE0_CLOSE();
    }

    return (status);
}

VXLIB_STATUS VXLIB_integralImage_i8u_o32u_checkParams(void *src,
                                                      VXLIB_bufParams2D_t *src_addr,
                                                      void *dst,
                                                      VXLIB_bufParams2D_t *dst_addr,
                                                      uint32_t *prevRow,
                                                      uint32_t *prevCol,
                                                      uint32_t *prevRowUpdate,
                                                      void *pBlock)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

    return (status);
}
