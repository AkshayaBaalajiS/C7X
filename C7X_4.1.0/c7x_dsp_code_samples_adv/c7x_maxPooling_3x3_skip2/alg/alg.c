/*
* module name       : c7x_maxPooling_3x3_skip2
*
* module descripton : Max Pooling, 3x3 window, skip 2 positions horz/vert
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
#include "VXLIB_bufParams.h"
#include "VXLIB_cnn_maxPooling_3x3_skip2_i8u_o8u.h"
#include "VXLIB_cnn_maxPooling_3x3_skip2_i8u_o8u_cn.h"

#define ERROR_REPORT (0)

#ifndef _HOST_EMULATION
#define PROFILE_READ   __TSC
#endif

extern uint8_t refQC[QC512_SIZE];

#pragma DATA_SECTION(outQC, ".outQC");
ALIGN_128BYTES uint8_t outQC[QC512_SIZE];

#pragma DATA_SECTION(inData, ".inData");
ALIGN_128BYTES uint8_t inData[(INPUT_STRIDE * INPUT_HEIGHT * NUM_CH) + BANK_PADDING];

#pragma DATA_SECTION(outData, ".outData");
ALIGN_128BYTES uint8_t  outData[(OUTPUT_STRIDE * OUTPUT_HEIGHT * NUM_CH) + BANK_PADDING];

#pragma DATA_SECTION(pOutSum, ".pOutSum");
ALIGN_128BYTES uint32_t pOutSum[4];

#pragma DATA_SECTION(pBlock, ".pBlock");
ALIGN_128BYTES uint8_t pBlock[VXLIB_CNNMAXPOOLING_3x3_SKIP2_I8U_O8U_PBLOCK_SIZE];

int test_main(uint32_t *pProfile)
{
    uint8_t *pIn;
    uint8_t *pOut;

    uint8_t *pRefQC;
    uint8_t *pOutQC;

    VXLIB_bufParams3D_t sInParams;
    VXLIB_bufParams3D_t sOutParams;

    int32_t result;
    uint64_t t0, t1;

    int32_t inSize  = INPUT_STRIDE  * INPUT_HEIGHT  * NUM_CH;
    int32_t outSize = OUTPUT_STRIDE * OUTPUT_HEIGHT * NUM_CH;
    int32_t ctr;

    sInParams.dim_x     = INPUT_WIDTH;
    sInParams.dim_y     = INPUT_HEIGHT;
    sInParams.stride_y  = INPUT_STRIDE;
    sInParams.dim_z     = NUM_CH;
    sInParams.stride_z  = sInParams.dim_y * sInParams.stride_y;
    sInParams.data_type = VXLIB_UINT8;

    sOutParams.dim_x     = OUTPUT_WIDTH;
    sOutParams.dim_y     = OUTPUT_HEIGHT;
    sOutParams.stride_y  = OUTPUT_STRIDE;
    sOutParams.dim_z     = NUM_CH;
    sOutParams.stride_z  = sOutParams.dim_y * sOutParams.stride_y;
    sOutParams.data_type = VXLIB_UINT8;

    /* Input data */
    pIn    = (uint8_t *)alignAddress(&inData[0], MEMORY_BANK0);
    /* Output Data */
    pOut  = (uint8_t *)alignAddress(&outData[0], MEMORY_BANK1);
    /* Reference QC */
    pRefQC = (uint8_t *)&refQC[0];
    /* Output QC    */
    pOutQC = (uint8_t *)&outQC[0];

    fillRandFast(pIn, inSize, MEMORY_ELEM_8BIT, 256);

    memsetFast(pOut, 0, outSize, MEMORY_ELEM_8BIT);

       VXLIB_cnnMaxPooling_3x3_skip2_i8u_o8u_init
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

       VXLIB_cnnMaxPooling_3x3_skip2_i8u_o8u_kernel
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

    qc512(pOutQC, pOut, outSize);

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
