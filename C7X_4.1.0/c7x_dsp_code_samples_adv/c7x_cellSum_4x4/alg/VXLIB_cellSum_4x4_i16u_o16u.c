/*
* module name       : c7x_cellSum_4x4
*
* module descripton : Computes 4x4 non-overlapping cell sums
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#include "VXLIB_cellSum_4x4_i16u_o16u.h"

#ifdef _DISPLAY_PARAMS
#include "paramv.h"
#endif

#define SE0_PARAM_BASE (0x0000)

#define SE0_PARAM_OFFSET   (SE0_PARAM_BASE)
#define SA0_PARAM_OFFSET   (SE0_PARAM_OFFSET + SE_PARAM_SIZE)
#define VDOTP_PARAM_OFFSET (SA0_PARAM_OFFSET + SA_PARAM_SIZE)

#define SIMD_WIDTH_SHIFT_IN        (5) /* 2^5 = 32 16b elements in a 512b vector */
#define SIMD_WIDTH_IN              (1 << SIMD_WIDTH_SHIFT_IN)
#define SIMD_WIDTH_RND_IN          (SIMD_WIDTH_IN >> 1)
#define NUM_SIMD_BLOCKS_IN(width)  (((width) >> SIMD_WIDTH_SHIFT_IN) + (((width) - (((width) >> SIMD_WIDTH_SHIFT_IN) << SIMD_WIDTH_SHIFT_IN)) > 0 ? 1 : 0))

#define SIMD_WIDTH_SHIFT_OUT        (4) /* 2^4 = 16 32b elements in a 512b vector */
#define SIMD_WIDTH_OUT              (1 << SIMD_WIDTH_SHIFT_OUT)
#define SIMD_WIDTH_RND_OUT          (SIMD_WIDTH_OUT >> 1)
#define NUM_SIMD_BLOCKS_OUT(width)  (((width) >> SIMD_WIDTH_SHIFT_OUT) + (((width) - (((width) >> SIMD_WIDTH_SHIFT_OUT) << SIMD_WIDTH_SHIFT_OUT)) > 0 ? 1 : 0))

#define NUM_CELLS(blockSize, cellSize, cellStride)  ((((blockSize) - (cellSize)) / (cellStride)) + 1)

VXLIB_STATUS VXLIB_cellSum_4x4_i16u_o16u_init(void *pMagPlanes,
                                              VXLIB_bufParams3D_t *pMagPlanesParams,
                                              void *pHOGPlanes,
                                              VXLIB_bufParams3D_t *pHOGPlanesParams,
                                              int32_t numBins,
                                              void *pBlock)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#if defined(VXLIB_CHECK_PARAMS) || defined(VXLIB_CELLSUM_4x4_I16U_O16U_CHECK_PARAMS)
    status = VXLIB_cellSum_4x4_i16u_o16u_checkParams(pMagPlanes, pMagPlanesParams, pHOGPlanes, pHOGPlanesParams, numBins, pBlock);
    if( status == VXLIB_SUCCESS )
#endif
    {
        __STRM_TEMPLATE seTemplate;
        __STRM_TEMPLATE saTemplate;

        __SE_FLAGS seFlags;
        __SA_FLAGS saFlags;

        __STRM_PARAM_5D seParam;
        __STRM_PARAM_4D saParam;

        int32_t outHeight;
        int32_t numBytes;
        int32_t stride_y, stride_z;
        int32_t cellSize   = 4;
        int32_t cellStride = 4;

        outHeight = NUM_CELLS(pMagPlanesParams->dim_y, cellSize, cellStride);

        seFlags = __SE_FLAGS_default();

        if ((pMagPlanesParams->data_type == VXLIB_INT8) || (pMagPlanesParams->data_type == VXLIB_UINT8))
        {
            seFlags.ELETYPE   = __SE_ELETYPE_8BIT;
            seFlags.PROMOTE   = __SE_PROMOTE_2X_ZEROEXT;
        }
        else
        {
            seFlags.ELETYPE   = __SE_ELETYPE_16BIT;
            seFlags.PROMOTE   = __SE_PROMOTE_OFF;
        }

        seFlags.VECLEN    = __SE_VECLEN_32ELEMS;

        seParam.ICNT0 = SIMD_WIDTH_IN;
        seParam.ICNT1 = cellSize;
        seParam.ICNT2 = outHeight;
        seParam.ICNT3 = NUM_SIMD_BLOCKS_IN(pMagPlanesParams->dim_x) >> 1;
        seParam.ICNT4 = numBins;

        numBytes = VXLIB_sizeof(pMagPlanesParams->data_type);
        stride_y = pMagPlanesParams->stride_y / numBytes;
        stride_z = pMagPlanesParams->stride_z / numBytes;

        seParam.DIM1  = stride_y;
        seParam.DIM2  = cellStride * stride_y;
        seParam.DIM3  = (SIMD_WIDTH_IN << 1);
        seParam.DIM4  = stride_z;

        /* SETUP SE TEMPLATE */
        seTemplate = __SE_SET_PARAM_5D(&seParam, &seFlags);
        *stov_ptr(__STRM_TEMPLATE, (uint32_t*)((uint8_t *)pBlock + SE0_PARAM_OFFSET)) = seTemplate;

        numBytes = VXLIB_sizeof(pHOGPlanesParams->data_type);
        stride_y = pHOGPlanesParams->stride_y / numBytes;

        saFlags = __SA_FLAGS_default();

        /* Prepare SA 0 tempate to store output */
        saFlags.DECDIM1   = __SA_DECDIM_DIM2;
        saFlags.VECLEN    = __SA_VECLEN_16ELEMS;

        /* ITERATION COUNTERS */
        saParam.DECDIM1_WIDTH = pHOGPlanesParams->dim_x;
        saParam.ICNT0 = SIMD_WIDTH_OUT;
        saParam.ICNT1 = outHeight;
        saParam.ICNT2 = NUM_SIMD_BLOCKS_OUT(pHOGPlanesParams->dim_x);
        saParam.ICNT3 = numBins;

        /* DIMENSIONS */
        saParam.DIM1  = stride_y;
        saParam.DIM2  = SIMD_WIDTH_OUT;
        saParam.DIM3  = outHeight * stride_y;

        saTemplate = __SA_SET_PARAM_4D(&saParam, &saFlags);
        *stov_ptr(__STRM_TEMPLATE, (uint32_t*)((uint8_t *)pBlock + SA0_PARAM_OFFSET)) = saTemplate;
    }

    return (status);
}

VXLIB_STATUS VXLIB_cellSum_4x4_i16u_o16u_kernel(void *pMagPlanes,
                                                VXLIB_bufParams3D_t *pMagPlanesParams,
                                                void *pHOGPlanes,
                                                VXLIB_bufParams3D_t *pHOGPlanesParams,
                                                int32_t numBins,
                                                void *pBlock)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#if defined(VXLIB_CHECK_PARAMS) || defined(VXLIB_CELLSUM_4x4_I16U_O16U_CHECK_PARAMS)
    status = VXLIB_cellSum_4x4_i16u_o16u_checkParams(pMagPlanes, pMagPlanesParams, pHOGPlanes, pHOGPlanesParams, numBins, pBlock);
    if( status == VXLIB_SUCCESS )
#endif
    {
        __STRM_TEMPLATE seTemplate, saTemplate;

        int32_t bin, blkX, blkY;
        int32_t numBlocks, numRows;
        int32_t cellSize   = 4;
        int32_t cellStride = 4;

        int16_t *restrict pOut;

        seTemplate = *stov_ptr(__STRM_TEMPLATE, (uint32_t*)((uint8_t *)pBlock + SE0_PARAM_OFFSET));
        __SE0_OPEN((void *)pMagPlanes, seTemplate);
        __SE1_OPEN((void *)((int16_t *)pMagPlanes + SIMD_WIDTH_IN), seTemplate);

#ifdef _DISPLAY_PARAMS
        displaySEParam((void *)pMagPlanes, seTemplate, PARAMV_SE0);
        displaySEParam((void *)((int16_t *)pMagPlanes + SIMD_WIDTH_IN), seTemplate, PARAMV_SE1);
#endif
        saTemplate = *stov_ptr(__STRM_TEMPLATE, (uint32_t*)((uint8_t *)pBlock + SA0_PARAM_OFFSET));
        __SA0_OPEN(saTemplate);

        numRows = NUM_CELLS(pMagPlanesParams->dim_y, cellSize, cellStride);

        pOut = (int16_t *)pHOGPlanes;

        short32 vK1 = (short32)(1);

#ifdef _DISPLAY_PARAMS
        displaySAParam((void *)pOut, saTemplate, PARAMV_SA0);
#endif

        numBlocks = NUM_SIMD_BLOCKS_IN(pMagPlanesParams->dim_x) >> 1;

#pragma MUST_ITERATE(1,,)
        for(bin = 0; bin < numBins; bin++)
        {
#pragma MUST_ITERATE(1,,)
            for(blkX = 0; blkX < numBlocks; blkX++)
            {
#pragma MUST_ITERATE(1,,)
                for(blkY = 0; blkY < numRows; blkY++)
                {
                    int16 vRes; vRes = __vdotp4hw_wwv(__SE0ADV(short32), __SE1ADV(short32), vK1, vK1);

                    vRes = vRes + __vdotp4hw_wwv(__SE0ADV(short32), __SE1ADV(short32), vK1, vK1);
                    vRes = vRes + __vdotp4hw_wwv(__SE0ADV(short32), __SE1ADV(short32), vK1, vK1);
                    vRes = vRes + __vdotp4hw_wwv(__SE0ADV(short32), __SE1ADV(short32), vK1, vK1);

                    vRes = __deal_stride2(vRes);

                    __vpred vpStore = __SA0_VPRED(int16);
                    __vstore_pred_packl(vpStore, __SA0ADV(short16, pOut), vRes);
                }
            }
        }

        __SA0_CLOSE();
        __SE1_CLOSE();
        __SE0_CLOSE();
    }

    return (status);
}

VXLIB_STATUS VXLIB_cellSum_4x4_i16u_o16u_checkParams(void *pMagPlanes,
                                                     VXLIB_bufParams3D_t *pMagPlanesParams,
                                                     void *pHOGPlanes,
                                                     VXLIB_bufParams3D_t *pHOGPlanesParams,
                                                     int32_t numBins,
                                                     void *pBlock)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

    return (status);
}
