/*
* module name       : c7x_cellSum_4x4
*
* module descripton : Computes 4x4 non-overlapping cell sums
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
#define PROFILE_READ   __TSC
#endif

#include "array.h"
#include "VXLIB_bufParams.h"
#include "VXLIB_cellSum_4x4_i16u_o16u.h"
#include "VXLIB_cellSum_4x4_i16u_o16u_cn.h"

#define ERROR_REPORT (0)

extern uint16_t locMatData[INPUT_STRIDE * INPUT_HEIGHT * NUM_BINS];
extern uint16_t hogRefData[OUTPUT_WIDTH * OUTPUT_HEIGHT * NUM_BINS];

#pragma DATA_SECTION(hogOutData, ".hogOutData");
ALIGN_128BYTES uint16_t  hogOutData[OUTPUT_WIDTH * OUTPUT_HEIGHT * NUM_BINS];

#pragma DATA_SECTION(pOutSum, ".pOutSum");
ALIGN_128BYTES uint32_t pOutSum[4];

#pragma DATA_SECTION(pBlock, ".pBlock");
ALIGN_128BYTES uint8_t pBlock[VXLIB_CELLSUM_4x4_I16U_O16U_PBLOCK_SIZE];

int test_main(uint32_t *pProfile)
{
    uint16_t *pLocMat;
    uint16_t *pHogRef;
    uint16_t *pHog;

    VXLIB_bufParams3D_t sMatBlockParams;
    VXLIB_bufParams3D_t sHOGBlockParams;

    int32_t result;
    int32_t blkX, blkY, bin;
    int32_t cellSize, cellStride;

    uint64_t t0, t1;

    cellSize   = CELL_SIZE;
    cellStride = CELL_STRIDE;

    sMatBlockParams.dim_x     = INPUT_WIDTH;
    sMatBlockParams.dim_y     = INPUT_HEIGHT;
    sMatBlockParams.stride_y  = INPUT_STRIDE * sizeof(uint16_t);
    sMatBlockParams.dim_z     = NUM_BINS;
    sMatBlockParams.stride_z  = sMatBlockParams.dim_y * sMatBlockParams.stride_y;
    sMatBlockParams.data_type = VXLIB_UINT16;

    sHOGBlockParams.dim_x     = FEAT_WIDTH(sMatBlockParams.dim_x, cellSize, cellStride);
    sHOGBlockParams.dim_y     = FEAT_HEIGHT(sMatBlockParams.dim_y, cellSize, cellStride);
    sHOGBlockParams.stride_y  = FEAT_PITCH(sHOGBlockParams.dim_x) * sizeof(uint16_t);
    sHOGBlockParams.dim_z     = NUM_BINS;
    sHOGBlockParams.stride_z  = sHOGBlockParams.dim_y * sHOGBlockParams.stride_y;
    sHOGBlockParams.data_type = VXLIB_UINT16;

    /* Input data */
    pLocMat    = (uint16_t *)&locMatData[0];
    pHogRef    = (uint16_t *)&hogRefData[0];

    /* Output Data */
    pHog       = (uint16_t *)&hogOutData[0];

    t0 = t1 = 0;

    VXLIB_cellSum_4x4_i16u_o16u_init
    (
        pLocMat,
        &sMatBlockParams,
        pHog,
        &sHOGBlockParams,
        NUM_BINS,
        pBlock
    );

#ifndef _HOST_EMULATION
    t0 = PROFILE_READ;
#endif

    VXLIB_cellSum_4x4_i16u_o16u_kernel
    (
        pLocMat,
        &sMatBlockParams,
        pHog,
        &sHOGBlockParams,
        NUM_BINS,
        pBlock
    );

#ifndef _HOST_EMULATION
    t1 = PROFILE_READ;
#endif

    pProfile[0] = (t1 - t0);

#if(ERROR_REPORT)
    printf("Comparing results! \n");
#endif

    result = 1;

    for(bin = 0; bin < NUM_BINS; bin++)
    {
        for(blkY = 0; blkY < OUTPUT_HEIGHT; blkY++)
        {
            for(blkX = 0; blkX < OUTPUT_WIDTH; blkX++)
            {
                int32_t offset = (bin * OUTPUT_WIDTH * OUTPUT_HEIGHT) + (blkY * OUTPUT_WIDTH) + blkX;
                if(pHog[offset] != pHogRef[offset])
                {
#if(ERROR_REPORT)
                   printf("Mismatch at bin = %d, blkX = %d, blkY = %d, pHog = %d, pHogRef = %d\n", bin, blkX, blkY, pHog[offset], pHogRef[offset]);
#endif
                   result = 0;

#ifdef _EXIT_FAILURE
                   exit(EXIT_FAILURE);
#endif
                }
            }
        }
    }

    return result;
}
