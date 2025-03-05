/*
* module name       : c7x_mergeSort
*
* module descripton : Performs sorting of 512, 32-bit elements
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
#include "VXLIB_mergeSort_i32s_o32s.h"
#include "VXLIB_mergeSort_i32s_o32s_cn.h"

#define ERROR_REPORT (0)

#ifndef _HOST_EMULATION
#define PROFILE_READ   __TSC
#endif

extern int32_t  inData[INPUT_SIZE];
extern int32_t  refData[INPUT_SIZE];

#pragma DATA_SECTION(tmpData, ".tmpData");
ALIGN_128BYTES int32_t  tmpData[INPUT_SIZE];

#pragma DATA_SECTION(pOutSum, ".pOutSum");
ALIGN_128BYTES uint32_t pOutSum[4];

#pragma DATA_SECTION(pBlock, ".prmBlock");
ALIGN_128BYTES uint8_t pBlock[VXLIB_MERGE_SORT_I32S_O32S_PBLOCK_SIZE];

int test_main(uint32_t *pProfile)
{
    int32_t  *pIn;
    int32_t  *pTmp;
    int32_t  *pRef;

    int32_t result;
    int32_t ctr;

    uint64_t t0, t1;

    /* Input data */
    pIn   = (int32_t *)&inData[0];
    pRef  = (int32_t *)&refData[0];
    pTmp  = (int32_t *)&tmpData[0];

    VXLIB_mergeSort_i32s_o32s_init(pIn, pTmp, INPUT_SIZE, pBlock);

#ifndef _HOST_EMULATION
    t0 = PROFILE_READ;
#endif

    VXLIB_mergeSort_i32s_o32s_kernel(pIn, pTmp, INPUT_SIZE, pBlock);

#ifndef _HOST_EMULATION
    t1 = PROFILE_READ;
#endif

    pProfile[0] = (t1 - t0);

#if(ERROR_REPORT)
    printf("Comparing results! \n");
#endif

    result = 1;

    for(ctr = 0; ctr < INPUT_SIZE; ctr++)
    {
         if(pIn[ctr] != pRef[ctr])
         {
#if(ERROR_REPORT)
            printf("Mismatch at ctr = %d, pIn = %d, pRef = %d\n", ctr, pIn[ctr], pRef[ctr]);
#endif
            result = 0;

#ifdef _EXIT_FAILURE
            exit(EXIT_FAILURE);
#endif

         }
    }

    return result;
}
