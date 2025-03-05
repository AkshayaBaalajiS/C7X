/*
* module name       : c7x_harris_score_3x3
*
* module descripton : Computes Harris Score for 3x3 window
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
#include "VXLIB_harrisScore_NxN_i16s_i16s_o32u.h"
#include "VXLIB_harrisScore_NxN_i16s_i16s_o32u_cn.h"

#define ERROR_REPORT (0)

#ifndef _HOST_EMULATION
#define PROFILE_READ   __TSC
#endif

extern uint8_t refQC[QC512_SIZE];

#pragma DATA_SECTION(".outQC");
ALIGN_128BYTES uint8_t outQC[QC512_SIZE];

#pragma DATA_SECTION(".gradXData")
ALIGN_128BYTES int16_t gradXData[INPUT_STRIDE * INPUT_HEIGHT];

#pragma DATA_SECTION(".gradYData")
ALIGN_128BYTES int16_t gradYData[INPUT_STRIDE * INPUT_HEIGHT];

#pragma DATA_SECTION(".outData")
ALIGN_128BYTES uint32_t outData[OUTPUT_STRIDE * OUTPUT_HEIGHT];

#pragma DATA_SECTION(".scratchData")
ALIGN_128BYTES uint32_t scratchData[SCRATCH_SIZE];

#pragma DATA_SECTION(".pBlock")
ALIGN_128BYTES uint8_t pBlock[VXLIB_HARRISSCORE_NXN_I16S_I16S_O32U_PBLOCK_SIZE];

extern "C" int test_main(uint32_t *pProfile);

int test_main(uint32_t *pProfile)
{
    int16_t *pGradX;
    int16_t *pGradY;

    uint32_t *pOut;

    uint8_t *pRefQC;
    uint8_t *pOutQC;

    VXLIB_bufParams2D_t sGradXBlockParams;
    VXLIB_bufParams2D_t sGradYBlockParams;
    VXLIB_bufParams2D_t sOutBlockParams;

    int32_t result;
    uint64_t t0, t1;

    int32_t ctr;
    int32_t inSize  = INPUT_STRIDE * INPUT_HEIGHT;
    int32_t outSize = OUTPUT_STRIDE * OUTPUT_HEIGHT;

    sGradXBlockParams.dim_x     = INPUT_WIDTH;
    sGradXBlockParams.dim_y     = INPUT_HEIGHT;
    sGradXBlockParams.stride_y  = INPUT_STRIDE * sizeof(int16_t);
    sGradXBlockParams.data_type = VXLIB_INT16;

    sGradYBlockParams.dim_x     = INPUT_WIDTH;
    sGradYBlockParams.dim_y     = INPUT_HEIGHT;
    sGradYBlockParams.stride_y  = INPUT_STRIDE * sizeof(int16_t);
    sGradYBlockParams.data_type = VXLIB_INT16;

    sOutBlockParams.dim_x     = OUTPUT_WIDTH;
    sOutBlockParams.dim_y     = OUTPUT_HEIGHT;
    sOutBlockParams.stride_y  = OUTPUT_STRIDE * sizeof(uint32_t);
    sOutBlockParams.data_type = VXLIB_INT32;

    /* Input data */
    pGradX  = (int16_t  *)&gradXData[0];
    pGradY  = (int16_t  *)&gradYData[0];

    /* Output Data */
    pOut    = (uint32_t *)&outData[0];

    /* Reference QC */
    pRefQC = (uint8_t *)&refQC[0];
    /* Output QC    */
    pOutQC = (uint8_t *)&outQC[0];

    fillRandFast(pGradX, inSize, MEMORY_ELEM_16BIT, 2048);
    fillRandFast(pGradY, inSize, MEMORY_ELEM_16BIT, 2048);

    memsetFast(pOut, 0, outSize, MEMORY_ELEM_32BIT);

       VXLIB_harrisScore_NxN_i16s_i16s_o32u_init
       (
          pGradX,
          &sGradXBlockParams,
          pGradY,
          &sGradYBlockParams,
          pOut,
          &sOutBlockParams,
          &scratchData[0],
          BLOCK_SIZE,
          &pBlock
       );

#ifndef _HOST_EMULATION
      t0 = PROFILE_READ;
#endif

       VXLIB_harrisScore_NxN_i16s_i16s_o32u_kernel<3>(
          pGradX,
          &sGradXBlockParams,
          pGradY,
          &sGradYBlockParams,
          pOut,
          &sOutBlockParams,
          &scratchData[0],
          BLOCK_SIZE,
          &pBlock
       );

#ifndef _HOST_EMULATION
      t1 = PROFILE_READ;
#endif

    pProfile[0] = (t1 - t0);


#if(ERROR_REPORT)
    printf("Comparing results! \n");
#endif

    qc512(pOutQC, (uint8_t *)pOut, outSize * sizeof(uint32_t));

    result = 1;

    for(ctr = 0; ctr < QC512_SIZE; ctr++)
    {
      if(pRefQC[ctr] != pOutQC[ctr])
      {
#if(ERROR_REPORT)
        printf("Mismatch at ctr = %d, ref QC = %d, out QC = %d\n", ctr, pRefQC[ctr], pOutQC[ctr]);
#endif
        result = 0;

#ifdef _EXIT_FAILURE
        exit(EXIT_FAILURE);
#endif
      }
    }

#if(ERROR_REPORT)
    if(result == 1)
        printf("Test Pass!\n");
    else
        printf("Test Fail!\n");
#endif

    return result;
}
