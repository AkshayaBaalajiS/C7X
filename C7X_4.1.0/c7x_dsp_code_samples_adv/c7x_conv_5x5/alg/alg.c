/*
* module name       : c7x_conv_5x5
*
* module descripton : 5x5 convolution
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifdef _HOST_EMULATION
#include "c7x_host_emulation.h"
#else
#include <c7x.h>
#endif

#include "array.h"
#include "VXLIB_conv_i16s_c16s_o32s_5x5_skip1.h"
#include "VXLIB_conv_i16s_c16s_o32s_5x5_skip1_cn.h"

#define ERROR_REPORT (0)

#ifndef _HOST_EMULATION
#define PROFILE_READ   __TSC
#endif

extern int16_t inData[INPUT_STRIDE * INPUT_HEIGHT * INPUT_CH];
extern int16_t wgtData[KERNEL_STRIDE * KERNEL_HEIGHT * INPUT_CH * OUTPUT_CH];
extern int16_t biasData[OUTPUT_CH];
extern int32_t outRefData[OUTPUT_STRIDE * OUTPUT_HEIGHT * OUTPUT_CH];

#pragma DATA_SECTION(outData, ".outData")
ALIGN_128BYTES int32_t outData[OUTPUT_STRIDE * OUTPUT_HEIGHT * OUTPUT_CH];

#pragma DATA_SECTION(pOutSum, ".pOutSum");
ALIGN_128BYTES uint32_t pOutSum[4];

#pragma DATA_SECTION(pBlock, ".pBlock")
ALIGN_128BYTES uint8_t pBlock[VXLIB_CONV_I16S_C16S_O32S_5X5_SKIP1_PBLOCK_SIZE];

const int16_t conv_5x5_kernel [KERNEL_STRIDE * KERNEL_HEIGHT] =
{
    -1, -1, -1, -1, -1, 0, 0, 0,
    -1,  2,  2,  2, -1, 0, 0, 0,
    -1,  2,  8,  2, -1, 0, 0, 0,
    -1,  2,  2,  2, -1, 0, 0, 0,
    -1, -1, -1, -1, -1, 0, 0, 0,
};

int test_main(uint32_t *pProfile)
{
    int16_t *pIn;
    int16_t *pWeights;
    int16_t *pBias;
    int32_t *pOut;

    int32_t *pOutRef;

    VXLIB_bufParams3D_t sInBlockParams;
    VXLIB_bufParams3D_t sOutBlockParams;
    VXLIB_bufParams3D_t sWgtBlockParams;
    VXLIB_bufParams3D_t sBiasBlockParams;

    int32_t result;
    int32_t blkX, blkY, ch;
    int32_t shiftQ, coeffQ;

    uint64_t t0, t1;

    sInBlockParams.dim_x     = INPUT_WIDTH;
    sInBlockParams.dim_y     = INPUT_HEIGHT;
    sInBlockParams.stride_y  = INPUT_STRIDE * sizeof(int16_t);
    sInBlockParams.dim_z     = INPUT_CH;
    sInBlockParams.stride_z  = INPUT_STRIDE * INPUT_HEIGHT * sizeof(int16_t);
    sInBlockParams.data_type = VXLIB_INT16;

    sWgtBlockParams.dim_x     = KERNEL_WIDTH;
    sWgtBlockParams.dim_y     = KERNEL_HEIGHT;
    sWgtBlockParams.stride_y  = KERNEL_STRIDE * sizeof(int16_t);
    sWgtBlockParams.dim_z     = INPUT_CH * OUTPUT_CH;
    sWgtBlockParams.stride_z  = KERNEL_STRIDE * KERNEL_HEIGHT * sizeof(int16_t);
    sWgtBlockParams.data_type = VXLIB_INT16;

    sBiasBlockParams.dim_x     = OUTPUT_CH;
    sBiasBlockParams.dim_y     = 1;
    sBiasBlockParams.stride_y  = 0;
    sBiasBlockParams.dim_z     = 1;
    sBiasBlockParams.stride_z  = 0;
    sBiasBlockParams.data_type = VXLIB_INT16;

    sOutBlockParams.dim_x     = OUTPUT_WIDTH;
    sOutBlockParams.dim_y     = OUTPUT_HEIGHT;
    sOutBlockParams.stride_y  = OUTPUT_STRIDE * sizeof(int32_t);
    sOutBlockParams.dim_z     = OUTPUT_CH;
    sOutBlockParams.stride_z  = OUTPUT_STRIDE * OUTPUT_HEIGHT * sizeof(int32_t);
    sOutBlockParams.data_type = VXLIB_INT32;

    /* Input data */
    pIn      = (int16_t *)&inData[0];
    pWeights = (int16_t *)&wgtData[0];
    pBias    = (int16_t *)&biasData[0];
    pOutRef  = (int32_t *)&outRefData[0];

    /* Output Data */
    pOut = (int32_t *)&outData[0];

    shiftQ = 2;
    coeffQ = 4;

    VXLIB_conv_i16s_c16s_o32s_5x5_skip1_init
    (
        pIn,
        &sInBlockParams,
        pWeights,
        &sWgtBlockParams,
        pBias,
        &sBiasBlockParams,
        pOut,
        &sOutBlockParams,
        shiftQ,
        coeffQ,
        &pBlock
    );

#ifndef _HOST_EMULATION
    t0 = PROFILE_READ;
#endif

    VXLIB_conv_i16s_c16s_o32s_5x5_skip1_kernel
    (
        pIn,
        &sInBlockParams,
        pWeights,
        &sWgtBlockParams,
        pBias,
        &sBiasBlockParams,
        pOut,
        &sOutBlockParams,
        shiftQ,
        coeffQ,
        &pBlock
    );

#ifndef _HOST_EMULATION
    t1 = PROFILE_READ;
#endif


    pProfile[0] = (t1 - t0);

#if(ERROR_REPORT)
    printf("Comparing results! \n");
#endif

    result = 1;

    for(ch = 0; ch < OUTPUT_CH; ch++)
    {
        for(blkY = 0; blkY < OUTPUT_HEIGHT; blkY++)
        {
            for(blkX = 0; blkX < OUTPUT_WIDTH; blkX++)
            {
                int32_t offset = (ch * OUTPUT_STRIDE * OUTPUT_HEIGHT) + (blkY * OUTPUT_STRIDE) + blkX;
                if(pOut[offset] != pOutRef[offset])
                {
#if(ERROR_REPORT)
                    printf("Mismatch at blkX = %d, blkY = %d, pOut = %d, pOutRef = %d\n", blkX, blkY, pOut[offset], pOutRef[offset]);
#endif
                    result = 0;
                }
            }
        }
    }

    return result;
}
