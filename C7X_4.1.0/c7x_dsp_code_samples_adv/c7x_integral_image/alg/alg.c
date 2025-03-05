/*
* module name       : c7x_integral_image
*
* module descripton : Computes integral image
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
#include "VXLIB_integralImage_i8u_o32u.h"
#include "VXLIB_integralImage_i8u_o32u_cn.h"

#define ERROR_REPORT (0)

#ifndef _HOST_EMULATION
#define PROFILE_READ   __TSC
#endif

extern uint8_t refQC[QC512_SIZE];

#pragma DATA_SECTION(outQC, ".outQC");
ALIGN_128BYTES uint8_t outQC[QC512_SIZE];

#pragma DATA_SECTION(inData, ".inData");
ALIGN_128BYTES uint8_t inData[(INPUT_WIDTH * INPUT_HEIGHT) + BANK_PADDING];

#pragma DATA_SECTION(outData, ".outData")
ALIGN_128BYTES uint32_t outData[(OUTPUT_WIDTH * OUTPUT_HEIGHT) + BANK_PADDING];

#pragma DATA_SECTION(pOutSum, ".pOutSum");
ALIGN_128BYTES uint32_t pOutSum[4];

#pragma DATA_SECTION(prevRowData, ".prevRowData")
ALIGN_128BYTES uint32_t prevRowData[OUTPUT_WIDTH + BANK_PADDING];

#pragma DATA_SECTION(prevColData, ".prevColData")
ALIGN_128BYTES uint32_t prevColData[(OUTPUT_HEIGHT * CACHE_LINE_SIZE) + BANK_PADDING];

#pragma DATA_SECTION(pBlock, ".pBlock")
ALIGN_128BYTES uint8_t pBlock[VXLIB_INTEGRALIMAGE_I8U_O32U_PBLOCK_SIZE];

int test_main(uint32_t *pProfile)
{
    uint8_t  *pIn;
    uint32_t *pOut;
    uint32_t *pPrevRow;
    uint32_t *pPrevCol;

    uint8_t *pRefQC;
    uint8_t *pOutQC;

    VXLIB_bufParams2D_t sInBlockParams;
    VXLIB_bufParams2D_t sOutBlockParams;

    int32_t result;
    int32_t ctr;

    uint64_t t0, t1;

    int32_t inSize  = INPUT_WIDTH * INPUT_HEIGHT;
    int32_t outSize = OUTPUT_HEIGHT * OUTPUT_WIDTH;

    sInBlockParams.dim_x     = INPUT_WIDTH;
    sInBlockParams.dim_y     = INPUT_HEIGHT;
    sInBlockParams.stride_y  = sInBlockParams.dim_x * sizeof(uint8_t);
    sInBlockParams.data_type = VXLIB_UINT8;

    sOutBlockParams.dim_x     = OUTPUT_WIDTH;
    sOutBlockParams.dim_y     = OUTPUT_HEIGHT;
    sOutBlockParams.stride_y  = sOutBlockParams.dim_x * sizeof(uint32_t);
    sOutBlockParams.data_type = VXLIB_UINT32;

    /* Input data */
    pIn    = (uint8_t  *)alignAddress(&inData[0], MEMORY_BANK0);
    /* Output Data */
    pOut   = (uint32_t *)alignAddress(&outData[0], MEMORY_BANK1);

    /* Reference QC */
    pRefQC = (uint8_t *)&refQC[0];
    /* Output QC    */
    pOutQC = (uint8_t *)&outQC[0];

    pPrevRow = (uint32_t *)alignAddress(&prevRowData[0], MEMORY_BANK2);
    pPrevCol = (uint32_t *)alignAddress(&prevColData[0], MEMORY_BANK3);

    fillRandFast(pIn, inSize, MEMORY_ELEM_8BIT, 256);

    memsetFast(pOut, 0, outSize, MEMORY_ELEM_32BIT);
    memsetFast(pPrevRow, 0, OUTPUT_WIDTH, MEMORY_ELEM_32BIT);
    memsetFast(pPrevCol, 0, (OUTPUT_HEIGHT * CACHE_LINE_SIZE), MEMORY_ELEM_32BIT);

    VXLIB_integralImage_i8u_o32u_init
    (
        (void *)pIn,
        &sInBlockParams,
        (void *)pOut,
        &sOutBlockParams,
        pPrevRow,
        pPrevCol,
        NULL,
        &pBlock
    );

#ifndef _HOST_EMULATION
    t0 = PROFILE_READ;
#endif

    VXLIB_integralImage_i8u_o32u_kernel
    (
        (void *)pIn,
        &sInBlockParams,
        (void *)pOut,
        &sOutBlockParams,
        pPrevRow,
        pPrevCol,
        NULL,
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

    return result;
}
