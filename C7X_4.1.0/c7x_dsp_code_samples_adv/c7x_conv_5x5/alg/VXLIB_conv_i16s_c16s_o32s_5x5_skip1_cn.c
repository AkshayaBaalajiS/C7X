/*
* module name       : c7x_conv_5x5
*
* module descripton : 5x5 convolution
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#include "VXLIB_conv_i16s_c16s_o32s_5x5_skip1_cn.h"

VXLIB_STATUS VXLIB_conv_i16s_c16s_o32s_5x5_skip1_cn
(
    int16_t *src,
    VXLIB_bufParams3D_t *src_addr,
    int16_t *weights,
    VXLIB_bufParams3D_t *weights_addr,
    int16_t *bias,
    VXLIB_bufParams3D_t *bias_addr,
    int32_t *dst,
    VXLIB_bufParams3D_t *dst_addr,
    uint32_t shiftQ,
    uint32_t coeffQ
)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#ifdef VXLIB_CHECK_PARAMS
    status = VXLIB_conv_i16s_c16s_o32s_5x5_skip1_checkParams_cn(src, src_addr, weights, weights_addr, bias, bias_addr, dst, dst_addr, shiftQ, coeffQ);
    if( status == VXLIB_SUCCESS )
#endif
    {
        int16_t *restrict    pInData;
	int16_t *restrict    pWeightData;
	int32_t *restrict    pOutData;
	int16_t *restrict    pBiasValue;
    	uint32_t             numInCh, numOutCh;
    	int32_t             inChIdx, outChIdx;
    	int32_t              accmPrevBlock, round;

    	int32_t    ctrX, ctrY;
    	uint32_t   outCols, outRows, outPitch;
    	uint32_t   inPitch, inRows;
    	uint32_t   wgtPitch, wgtRows, wgtCols;
        int32_t    numBytes;

    	outCols  = dst_addr->dim_x;
    	outRows  = dst_addr->dim_y;

    	inRows   = src_addr->dim_y;

    	wgtCols  = weights_addr->dim_x;
    	wgtRows  = weights_addr->dim_y;

        numInCh  = src_addr->dim_z;
        numOutCh = dst_addr->dim_z;

    	pOutData   = dst;
    	pBiasValue = bias;

        numBytes = VXLIB_sizeof(src_addr->data_type);
    	inPitch  = src_addr->stride_y / numBytes;

        numBytes = VXLIB_sizeof(dst_addr->data_type);
    	outPitch = dst_addr->stride_y / numBytes;

        numBytes = VXLIB_sizeof(weights_addr->data_type);
    	wgtPitch = weights_addr->stride_y / numBytes;

    	round = (shiftQ == 0) ? 0 : (1 << (shiftQ - 1));

        for( outChIdx = 0; outChIdx < numOutCh; outChIdx++ )
        {
            accmPrevBlock   = pBiasValue[outChIdx] << (coeffQ - shiftQ);

            for( ctrY = 0; ctrY < outRows; ctrY++ )
            {
    		for( ctrX = 0; ctrX < outCols; ctrX++ )
        	{
                    int32_t    idx, idy;
                    int32_t     accm = 0;

                    for( inChIdx = 0; inChIdx < numInCh; inChIdx++ )
                    {
                        pInData     = (int16_t *)src + (inChIdx * inPitch * inRows) + (ctrY * inPitch) + ctrX;
                        pWeightData = (int16_t *)weights + (inChIdx * wgtPitch * wgtRows) + (outChIdx * numInCh * wgtPitch * wgtRows);

                        for( idy = 0; idy < wgtRows; idy++ )
                        {
                            for( idx = 0; idx < wgtCols; idx++ )
                            {
                                accm += (pInData[idx] * pWeightData[idx]);
                            }

                            pInData     += inPitch;
                            pWeightData += wgtPitch;
                        }

                    }

                    pOutData[(outChIdx * outPitch * outRows) + (ctrY * outPitch) + ctrX] = ((accm + round) >> shiftQ) + accmPrevBlock;
                }
            }
        }
    }
    return (status);
}

VXLIB_STATUS VXLIB_conv_i16s_c16s_o32s_5x5_skip1_checkParams_cn
(
    int16_t *src,
    VXLIB_bufParams3D_t *src_addr,
    int16_t *weights,
    VXLIB_bufParams3D_t *wgt_addr,
    int16_t *bias,
    VXLIB_bufParams3D_t *bias_addr,
    int32_t *dst,
    VXLIB_bufParams3D_t *dst_addr,
    uint32_t shiftQ,
    uint32_t coeffQ
)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

    return (status);
}

/* ======================================================================== */
/*  End of file:  VXLIB_conv_i16s_c16s_o32s_5x5_skip1_cn.c                  */
/* ======================================================================== */
