/*
* module name       : c7x_cellSum_4x4
*
* module descripton : Computes 4x4 non-overlapping cell sums
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#include "VXLIB_cellSum_4x4_i16u_o16u_cn.h"

VXLIB_STATUS VXLIB_cellSum_4x4_i16u_o16u_cn(void *pMagPlanes,
                                            VXLIB_bufParams3D_t *pMagPlanesParams,
                                            void *pHOGPlanes,
                                            VXLIB_bufParams3D_t *pHOGPlanesParams,
                                            int32_t numBins)

{
    VXLIB_STATUS    status = VXLIB_SUCCESS;
    int32_t cellSize   = 4;
    int32_t cellStride = 4;

#if defined(VXLIB_CHECK_PARAMS) || defined(VXLIB_CELLSUM_4x4_I16U_O16U_CHECK_PARAMS)
    status = VXLIB_cellSum_4x4_i16u_o16u_cn_checkParams(pMagPlanes, pMagPlanesParams, pHOGPlanes, pHOGPlanesParams, numBins, pBlock);
    if( status == VXLIB_SUCCESS )
#endif
    {
        int32_t dim0, dim1, dim2;
        int32_t cellX, cellY;
        int32_t stride_y_mag, stride_z_mag;
        int32_t stride_y_hog, stride_z_hog;
        int32_t numBytes;

        numBytes = VXLIB_sizeof(pMagPlanesParams->data_type);
        stride_y_mag = pMagPlanesParams->stride_y / numBytes;
        stride_z_mag = pMagPlanesParams->stride_z / numBytes;

        numBytes = VXLIB_sizeof(pHOGPlanesParams->data_type);
        stride_y_hog = pHOGPlanesParams->stride_y / numBytes;
        stride_z_hog = pHOGPlanesParams->stride_z / numBytes;

        if(pMagPlanesParams->data_type == VXLIB_UINT8)
        {
            uint8_t *pSrc;
            uint16_t *pDst;

            for(dim2 = 0; dim2 < numBins; dim2++)
            {
                pSrc = (uint8_t  *)pMagPlanes + (stride_z_mag * dim2);
                pDst = (uint16_t *)pHOGPlanes + (stride_z_hog * dim2);

                for(dim1 = 0; dim1 < pHOGPlanesParams->dim_y; dim1++)
                {
                    for(dim0 = 0; dim0 < pHOGPlanesParams->dim_x; dim0++)
                    {
                        int32_t startX, startY;
                        int32_t dstOffset;
                        int32_t cellSum;

                        startX = dim0 * cellStride;
                        startY = dim1 * cellStride;

                        if(((startX + cellSize) > pMagPlanesParams->dim_x) ||
                           ((startY + cellSize) > pMagPlanesParams->dim_y))
                        {
                            continue;
                        }

                        cellSum = 0;
                        for(cellY = 0; cellY < cellSize; cellY++)
                        {
                            for(cellX = 0; cellX < cellSize; cellX++)
                            {
                                int32_t srcOffset;

                                srcOffset = ((startY + cellY) * stride_y_mag) + startX + cellX;
                                cellSum += pSrc[srcOffset];
                            }
                        }

                        dstOffset = (dim1 * stride_y_hog) + dim0;
                        pDst[dstOffset] = cellSum;
                    }
                }
            }
        }
        else if(pMagPlanesParams->data_type == VXLIB_UINT16)
        {
            uint16_t *pSrc;
            uint16_t *pDst;

            for(dim2 = 0; dim2 < numBins; dim2++)
            {
                pSrc = (uint16_t *)pMagPlanes + (stride_z_mag * dim2);
                pDst = (uint16_t *)pHOGPlanes + (stride_z_hog * dim2);

                for(dim1 = 0; dim1 < pHOGPlanesParams->dim_y; dim1++)
                {
                    for(dim0 = 0; dim0 < pHOGPlanesParams->dim_x; dim0++)
                    {
                        int32_t startX, startY;
                        int32_t dstOffset;
                        int32_t cellSum;

                        startX = dim0 * cellStride;
                        startY = dim1 * cellStride;

                        if(((startX + cellSize) > pMagPlanesParams->dim_x) ||
                           ((startY + cellSize) > pMagPlanesParams->dim_y))
                        {
                            continue;
                        }

                        cellSum = 0;
                        for(cellY = 0; cellY < cellSize; cellY++)
                        {
                            for(cellX = 0; cellX < cellSize; cellX++)
                            {
                                int32_t srcOffset;

                                srcOffset = ((startY + cellY) * stride_y_mag) + startX + cellX;
                                cellSum += pSrc[srcOffset];
                            }
                        }

                        dstOffset = (dim1 * stride_y_hog) + dim0;
                        pDst[dstOffset] = cellSum;
                    }
                }
            }
        }
    }

    return (status);
}

VXLIB_STATUS VXLIB_cellSum_4x4_i16u_o16u_cn_checkParams(void *pMagPlanes,
                                                        VXLIB_bufParams3D_t *pMagPlanesParams,
                                                        void *pHOGPlanes,
                                                        VXLIB_bufParams3D_t *pHOGPlanesParams,
                                                        int32_t numBins)

{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

    return (status);
}
