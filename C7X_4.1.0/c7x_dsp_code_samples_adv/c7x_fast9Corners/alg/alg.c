/*
* module name       : c7x_fast9Corners
*
* module descripton : Computes FAST9 corners
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
#include "VXLIB_fastCornersDetect_i8u.h"
#include "VXLIB_fastCornersDetect_i8u_cn.h"
#include <stdio.h>

#define ERROR_REPORT (0)

#ifndef _HOST_EMULATION
#define PROFILE_READ   __TSC
#endif

extern uint8_t inData[INPUT_SIZE];
extern uint32_t outRefData[OUTPUT_SIZE];

#pragma DATA_SECTION(outData, ".outData")
ALIGN_128BYTES uint32_t outData[OUTPUT_SIZE];

#pragma DATA_SECTION(scratchData, ".scratchData")
ALIGN_128BYTES uint8_t scratchData[SCRATCH_SIZE];

#pragma DATA_SECTION(pOutSum, ".pOutSum");
ALIGN_128BYTES uint32_t pOutSum[4];

#pragma DATA_SECTION(pBlock, ".pBlock")
ALIGN_128BYTES uint8_t pBlock[VXLIB_FASTCORNERSDETECT_I8U_PBLOCK_SIZE];

int test_main(uint32_t *pProfile)
{
    uint8_t *pIn;
    uint32_t *pOut;
    uint32_t *pOutRef;

    VXLIB_bufParams2D_t sInBlockParams;

    int32_t result;
    int32_t ctr;

    uint32_t cornersCapacity;
    uint8_t threshold_strength;
    uint32_t numCorners;

    uint64_t t0, t1;

    sInBlockParams.dim_x     = INPUT_WIDTH;
    sInBlockParams.dim_y     = INPUT_HEIGHT;
    sInBlockParams.stride_y  = sInBlockParams.dim_x;
    sInBlockParams.data_type = VXLIB_UINT8;

    /* Input data */
    pIn     = (uint8_t *)&inData[0];
    pOutRef = (uint32_t *)&outRefData[0];

    /* Output Data */
    pOut   = (uint32_t *)&outData[0];

    cornersCapacity = OUTPUT_WIDTH * OUTPUT_HEIGHT;
    threshold_strength = 50;

    numCorners = 0;

    VXLIB_fastCornersDetect_i8u_init
    (
       pIn,
       &sInBlockParams,
       pOut,
       cornersCapacity,
       threshold_strength,
       &numCorners,
       scratchData,
       pBlock
    );

#ifndef _HOST_EMULATION
    t0 = PROFILE_READ;
#endif

    VXLIB_fastCornersDetect_i8u_kernel
    (
       pIn,
       &sInBlockParams,
       pOut,
       cornersCapacity,
       threshold_strength,
       &numCorners,
       scratchData,
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

    if(numCorners == 0)
    {
        result = 0;
    }

    for(ctr = 0; ctr < numCorners; ctr++)
    {
         if(pOut[ctr] != pOutRef[ctr])
         {
#if(ERROR_REPORT)
            uint16_t x1, y1, x2, y2;
            x1 = (uint16_t)(pOut[ctr] & 0xFFFF);
            y1 = (uint16_t)((pOut[ctr] >> 16) & 0xFFFF);

            x2 = (uint16_t)(pOutRef[ctr] & 0xFFFF);
            y2 = (uint16_t)((pOutRef[ctr] >> 16) & 0xFFFF);

            printf("Mismatch at ctr = %d, pOut: y = %d, x = %d, pOutRef: y = %d, x = %d \n", ctr, y1, x1, y2, x2);
#endif
            result = 0;

#ifdef _EXIT_FAILURE
            exit(EXIT_FAILURE);
#endif

         }
    }

    return result;
}
