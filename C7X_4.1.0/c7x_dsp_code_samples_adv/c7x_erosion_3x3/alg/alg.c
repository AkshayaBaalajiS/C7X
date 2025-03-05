/*
* module name       : c7x_erosion_3x3
*
* module descripton : 3x3 greyscale erosion
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
#include "memory.h"
#include "VXLIB_erode_3x3_i8u_o8u.h"
#include "VXLIB_erode_3x3_i8u_o8u_cn.h"

#define ERROR_REPORT (0)

#ifndef _HOST_EMULATION
#define PROFILE_READ   __TSC
#endif

extern uint8_t refQC[QC512_SIZE];

#pragma DATA_SECTION(outQC, ".outQC");
ALIGN_128BYTES uint8_t outQC[QC512_SIZE];

#pragma DATA_SECTION(inData, ".inData")
ALIGN_128BYTES uint8_t inData[(INPUT_STRIDE * INPUT_HEIGHT) + BANK_PADDING];

#pragma DATA_SECTION(outData, ".outData")
ALIGN_128BYTES uint8_t outData[(OUTPUT_STRIDE * OUTPUT_HEIGHT) + BANK_PADDING];

#pragma DATA_SECTION(refData, ".refData")
ALIGN_128BYTES uint8_t refData[(OUTPUT_STRIDE * OUTPUT_HEIGHT) + BANK_PADDING];

#pragma DATA_SECTION(pOutSum, ".pOutSum");
ALIGN_128BYTES uint32_t pOutSum[4];

#pragma DATA_SECTION(pBlock, ".pBlock")
ALIGN_128BYTES uint8_t pBlock[VXLIB_ERODE_3X3_I8U_O8U_PBLOCK_SIZE];

int test_main(uint32_t *pProfile)
{
    uint8_t *pIn;
    uint8_t *pOut;
    uint8_t *pRef;

    VXLIB_bufParams2D_t sInBlockParams;
    VXLIB_bufParams2D_t sOutBlockParams;

    int32_t result;
    int32_t blkX, blkY;

    uint64_t t0, t1;

    int32_t inSize  = INPUT_STRIDE  * INPUT_HEIGHT;

    sInBlockParams.dim_x     = INPUT_WIDTH;
    sInBlockParams.dim_y     = INPUT_HEIGHT;
    sInBlockParams.stride_y  = INPUT_STRIDE;
    sInBlockParams.data_type = VXLIB_UINT8;

    sOutBlockParams.dim_x     = OUTPUT_WIDTH;
    sOutBlockParams.dim_y     = OUTPUT_HEIGHT;
    sOutBlockParams.stride_y  = OUTPUT_STRIDE;
    sOutBlockParams.data_type = VXLIB_UINT8;

    /* Input data */
    pIn     = (uint8_t *)alignAddress(&inData[0], MEMORY_BANK0);
    /* Output Data */
    pOut    = (uint8_t *)alignAddress(&outData[0], MEMORY_BANK2);
    /* Reference Data */
    pRef    = (uint8_t *)alignAddress(&refData[0], MEMORY_BANK2);

    fillRandFast(pIn, inSize, MEMORY_ELEM_8BIT, 256);

    VXLIB_erode_3x3_i8u_o8u_init
    (
       (void *)pIn,
       &sInBlockParams,
       (void *)pOut,
       &sOutBlockParams,
       &pBlock
    );

#ifndef _HOST_EMULATION
    t0 = PROFILE_READ;
#endif

    VXLIB_erode_3x3_i8u_o8u_kernel
    (
       (void *)pIn,
       &sInBlockParams,
       (void *)pOut,
       &sOutBlockParams,
       &pBlock
    );

#ifndef _HOST_EMULATION
    t1 = PROFILE_READ;
#endif

    pProfile[0] = (t1 - t0);

    VXLIB_erode_3x3_i8u_o8u_cn
    (
       pIn,
       &sInBlockParams,
       pRef,
       &sOutBlockParams
    );

#if(ERROR_REPORT)
    printf("Comparing results! \n");
#endif

    result = 1;

    for(blkY = 0; blkY < OUTPUT_HEIGHT; blkY++)
    {
      for(blkX = 0; blkX < OUTPUT_WIDTH; blkX++)
      {
        int32_t offset = (blkY * OUTPUT_STRIDE) + blkX;

        if(pRef[offset] != pOut[offset])
        {
#if(ERROR_REPORT)
          printf("Mismatch at blkX = %d, blkY = %d, pRef = %d, pOut = %d\n", blkX, blkY, pRef[offset], pOut[offset]);
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
