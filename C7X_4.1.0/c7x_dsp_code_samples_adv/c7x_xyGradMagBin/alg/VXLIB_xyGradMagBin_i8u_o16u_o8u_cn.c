/*
* module name       : c7x_xyGradMagBin
*
* module descripton : Computes X/Y Gradients and Orientation
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#include "VXLIB_xyGradMagBin_i8u_o16u_o8u_cn.h"

#define MIN_ERROR (0x7FFFFFFF)
#define MIN_INDEX (0)
#define ABS(a) (((a) < 0)?(-(a)):(a))

VXLIB_STATUS VXLIB_xyGradMagBin_i8u_o16u_o8u_cn(void *pIn,
                                                VXLIB_bufParams2D_t *pInParams,
                                                void *pMag,
                                                VXLIB_bufParams2D_t *pMagParams,
                                                void *pBins,
                                                VXLIB_bufParams2D_t *pBinParams,
                                                int16_t *pCosTbl,
                                                int16_t *pSinTbl,
                                                int32_t numBins)
{

    VXLIB_STATUS    status = VXLIB_SUCCESS;

#ifdef VXLIB_CHECK_PARAMS
    status = VXLIB_xyGradMagBin_i8u_o16u_o8u_checkParams_cn(pIn, pInParams, pMag, pMagParams, pBins, pBinParams, pCosTbl, pSinTbl, numBins);
    if( status == VXLIB_SUCCESS )
#endif
    {
        uint8_t *pTop;
        uint8_t *pBot;
        uint8_t *pLeft;
        uint8_t *pRight;

        uint16_t *pMagBlk;
        uint8_t  *pBinBlk;
        int32_t dim_x, dim_y;
        int32_t dim0, dim1, ctr;

        int32_t bit_depth_in  = VXLIB_sizeof(pInParams->data_type);
        int32_t bit_depth_mag = VXLIB_sizeof(pMagParams->data_type);
        int32_t bit_depth_bin = VXLIB_sizeof(pBinParams->data_type);

        int32_t stride_in  = pInParams->stride_y  / bit_depth_in;
        int32_t stride_mag = pMagParams->stride_y / bit_depth_mag;
        int32_t stride_bin = pBinParams->stride_y / bit_depth_bin;

        dim_x    = pMagParams->dim_x;
        dim_y    = pMagParams->dim_y;

        pTop   = (uint8_t *)pIn + 1;
        pBot   = (uint8_t *)pIn + (stride_in * 2) + 1;
        pLeft  = (uint8_t *)pIn + stride_in;
        pRight = (uint8_t *)pIn + stride_in + 2;

        pMagBlk   = (uint16_t *)pMag;
        pBinBlk   = (uint8_t  *)pBins;

        for(dim1 = 0; dim1 < dim_y; dim1++)
        {
            int32_t err, idx;
            int32_t curErr;

            for(dim0 = 0; dim0 < dim_x; dim0++)
            {
                int32_t srcOffset = (dim1 * stride_in) + dim0;
                int32_t magOffset = (dim1 * stride_mag) + dim0;
                int32_t binOffset = (dim1 * stride_bin) + dim0;
                int32_t Gy = pBot[srcOffset] - pTop[srcOffset];
                int32_t Gx = pRight[srcOffset] - pLeft[srcOffset];

                int32_t mag = ABS(Gx) + ABS(Gy);

                pMagBlk[magOffset] = (uint16_t) mag;

                err = MIN_ERROR;
                idx = MIN_INDEX;

                for(ctr = 0; ctr < numBins; ctr++)
                {
                    curErr = ABS((Gy * pCosTbl[ctr]) - (Gx * pSinTbl[ctr]));
                    if(err > curErr)
                    {
                        err = curErr;
                        idx = ctr;
                    }
                }
                if((Gy == 0) && (Gx < 0))
                {
                    pBinBlk[binOffset] = numBins - 1;
                }
                else
                {
                    pBinBlk[binOffset] = idx;
                }
            }
        }
    }

    return (status);
}

VXLIB_STATUS VXLIB_xyGradMagBin_i8u_o16u_o8u_checkParams_cn(void *pIn,
                                            VXLIB_bufParams2D_t *pInParams,
                                            void *pMag,
                                            VXLIB_bufParams2D_t *pMagParams,
                                            void *pBins,
                                            VXLIB_bufParams2D_t *pBinParams,
                                            int16_t *pCosTbl,
                                            int16_t *pSinTbl,
                                            int32_t numBins)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;


    return status;
}
