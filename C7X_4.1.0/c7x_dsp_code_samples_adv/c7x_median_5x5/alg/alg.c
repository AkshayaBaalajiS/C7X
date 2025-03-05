/*
* module name       : c7x_median_5x5
*
* module descripton : Computes a 5x5 2D-median filter
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
#include "VXLIB_median_5x5_i16s_o16s.h"
#include "VXLIB_median_5x5_i16s_o16s_cn.h"

#define ERROR_REPORT (0)

#ifndef _HOST_EMULATION
#define PROFILE_READ   __TSC
#endif

extern int16_t  inData[INPUT_STRIDE * INPUT_HEIGHT];
extern int16_t  refData[OUTPUT_STRIDE * OUTPUT_HEIGHT];

#pragma DATA_SECTION(outData, ".outData");
ALIGN_128BYTES uint16_t  outData[OUTPUT_STRIDE * OUTPUT_HEIGHT];

#pragma DATA_SECTION(pOutSum, ".pOutSum");
ALIGN_128BYTES uint32_t pOutSum[4];

#pragma DATA_SECTION(pBlock, ".pBlock");
ALIGN_128BYTES uint8_t pBlock[VXLIB_MEDIAN_5X5_I16S_O16S_PBLOCK_SIZE];

int test_main(uint32_t *pProfile)
{
    int16_t  *pIn;
    int16_t  *pOut;
    int16_t  *pRef;

    VXLIB_bufParams2D_t sInParams;
    VXLIB_bufParams2D_t sOutParams;

    int32_t result;
    int32_t blkX, blkY;

    uint64_t t0, t1;

    sInParams.dim_x     = INPUT_WIDTH;
    sInParams.dim_y     = INPUT_HEIGHT;
    sInParams.stride_y  = INPUT_STRIDE * sizeof(int16_t);
    sInParams.data_type = VXLIB_INT16;

    sOutParams.dim_x     = OUTPUT_WIDTH;
    sOutParams.dim_y     = OUTPUT_HEIGHT;
    sOutParams.stride_y  = OUTPUT_STRIDE * sizeof(int16_t);
    sOutParams.data_type = VXLIB_INT16;

    /* Input data */
    pIn   = (int16_t *)&inData[0];
    pRef  = (int16_t *)&refData[0];

    /* Output Data */
    pOut  = (int16_t *)&outData[0];

       VXLIB_median_5x5_i16s_o16s_init
       (
          pIn,
          &sInParams,
          pOut,
          &sOutParams,
          pBlock
       );

#ifndef _HOST_EMULATION
      t0 = PROFILE_READ;
#endif

       VXLIB_median_5x5_i16s_o16s_kernel
       (
          pIn,
          &sInParams,
          pOut,
          &sOutParams,
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

    for(blkY = 0; blkY < OUTPUT_HEIGHT; blkY++)
    {
        for(blkX = 0; blkX < OUTPUT_WIDTH; blkX++)
        {
             int32_t offset = (blkY * OUTPUT_STRIDE) + blkX;
             if(pOut[offset] != pRef[offset])
             {
#if(ERROR_REPORT)
                printf("Mismatch at blkX = %d, blkY = %d, pOut = %d, pRef = %d\n", blkX, blkY, pOut[offset], pRef[offset]);
#endif
                result = 0;

#ifdef _EXIT_FAILURE
                exit(EXIT_FAILURE);
#endif

             }
        }
    }

    return result;
}
