/*
* module name       : c7x_nms
*
* module descripton : Computes 7x7 window Non Maximum Suppression
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
#include "VXLIB_nms_MxN_i32s_o8u.h"
#include "VXLIB_nms_MxN_i32s_o8u_cn.h"

#define ERROR_REPORT (0)

#ifndef _HOST_EMULATION
#define PROFILE_READ   __TSC
#endif

extern uint8_t refQC[QC512_SIZE];

#pragma DATA_SECTION(outQC, ".outQC");
ALIGN_128BYTES uint8_t outQC[QC512_SIZE];

#pragma DATA_SECTION(inData, ".inData")
ALIGN_128BYTES int32_t inData[(INPUT_STRIDE * INPUT_HEIGHT) + BANK_PADDING];

#pragma DATA_SECTION(outData, ".outData")
ALIGN_128BYTES uint8_t outData[(OUTPUT_STRIDE * OUTPUT_HEIGHT) + BANK_PADDING];

#pragma DATA_SECTION(scratch1Data, ".scratch1Data")
ALIGN_128BYTES int32_t scratch1Data[SCRATCH1_SIZE + BANK_PADDING];

#pragma DATA_SECTION(scratch2Data, ".scratch2Data")
ALIGN_128BYTES int32_t scratch2Data[SCRATCH2_SIZE + BANK_PADDING];

#pragma DATA_SECTION(pOutSum, ".pOutSum")
ALIGN_128BYTES uint32_t pOutSum[4];

#pragma DATA_SECTION(pBlock, ".pBlock")
ALIGN_128BYTES uint8_t pBlock[VXLIB_NMS_MxN_I32S_O8U_PBLOCK_SIZE];

int test_main(uint32_t *pProfile)
{
    int32_t *pIn;
    uint8_t *pOut;
    int32_t *pScratch1;
    int32_t *pScratch2;

    uint8_t *pRefQC;
    uint8_t *pOutQC;

    VXLIB_bufParams2D_t sInBlockParams;
    VXLIB_bufParams2D_t sOutBlockParams;

    int32_t result;
    int32_t ctr;

    uint64_t t0, t1;

    int32_t inSize = INPUT_STRIDE * INPUT_HEIGHT;
    int32_t outSize = OUTPUT_STRIDE * OUTPUT_HEIGHT;

    sInBlockParams.dim_x     = INPUT_WIDTH;
    sInBlockParams.dim_y     = INPUT_HEIGHT;
    sInBlockParams.stride_y  = INPUT_STRIDE * sizeof(int32_t);
    sInBlockParams.data_type = VXLIB_INT32;

    sOutBlockParams.dim_x     = OUTPUT_WIDTH;
    sOutBlockParams.dim_y     = OUTPUT_HEIGHT;
    sOutBlockParams.stride_y  = OUTPUT_STRIDE * sizeof(uint8_t);
    sOutBlockParams.data_type = VXLIB_UINT8;

    /* Input data */
    pIn       = (int32_t *)alignAddress(&inData[0], MEMORY_BANK0);
    /* Output Data */
    pOut      = (uint8_t *)alignAddress(&outData[0], MEMORY_BANK0);
    pScratch1 = (int32_t *)alignAddress(&scratch1Data[0], MEMORY_BANK1);
    pScratch2 = (int32_t *)alignAddress(&scratch2Data[0], MEMORY_BANK2);
    /* Reference QC */
    pRefQC = (uint8_t *)&refQC[0];
    /* Output QC    */
    pOutQC = (uint8_t *)&outQC[0];

    fillRandFast(pIn, inSize, MEMORY_ELEM_32BIT, 1024);

    memsetFast(pOut, 0, outSize, MEMORY_ELEM_8BIT);

       VXLIB_nms_MxN_i32s_o8u_init
       (
         pIn,
         &sInBlockParams,
         pOut,
         &sOutBlockParams,
         pScratch1,
         pScratch2,
         WINDOW_SIZE,
         WINDOW_SIZE,
         THRESHOLD,
         &pBlock
       );

#ifndef _HOST_EMULATION
      t0 = PROFILE_READ;
#endif

       VXLIB_nms_MxN_i32s_o8u_kernel
       (
         pIn,
         &sInBlockParams,
         pOut,
         &sOutBlockParams,
         pScratch1,
         pScratch2,
         WINDOW_SIZE,
         WINDOW_SIZE,
         THRESHOLD,
         &pBlock
       );

#ifndef _HOST_EMULATION
      t1 = PROFILE_READ;
#endif

    pProfile[0] = (t1 - t0);

#if(ERROR_REPORT)
    printf("Comparing results! \n");
#endif

    qc512(pOutQC, (uint8_t *)pOut, outSize);

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

    return result;
}
