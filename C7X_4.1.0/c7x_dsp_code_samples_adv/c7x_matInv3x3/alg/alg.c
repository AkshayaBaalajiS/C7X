/*
* module name       : c7x_matInv3x3
*
* module descripton : Does 3x3 matrix inverse
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
#include "VXLIB_matInv_i32f_o32f.h"

#ifndef STATIC_INPUT
#include <dumpData.h>
#endif

#ifndef _HOST_EMULATION
#define PROFILE_READ   __TSC
#endif

#pragma DATA_SECTION(invMat, ".l2Mem");
float invMat[NUM_MAT * MAX_MAT_ROWS * MAX_MAT_COLS];

#pragma DATA_SECTION(validOut, ".l2Mem");
uint8_t validOut[NUM_MAT];

#pragma DATA_SECTION(pOutSum, ".l2Mem");
float pOutSum[4];

#pragma DATA_SECTION(pBlock, ".l2Mem");
uint8_t pBlock[VXLIB_matInv_i32f_o32f_PBLOCK_SIZE];

extern float inMat[NUM_MAT * MAX_MAT_ROWS * MAX_MAT_COLS];
extern float refInvMat3x3[NUM_MAT * MAX_MAT_ROWS * MAX_MAT_COLS];

int test_main(uint32_t *pProfile)
{
    float *pInMat;
    float *pOutInvMat;
    float *pRefInvMat;

    uint8_t *pValidOut;

    int32_t result, ctr;

    VXLIB_bufParams3D_t inMatParams;
    VXLIB_bufParams3D_t outMatParams;

    uint64_t t0, t1;

#ifndef _IEEE_FLOAT
    __FPCR = 0x10;
#endif

#ifdef STATIC_INPUT
    /* Input data */
    pInMat   = (float *)&inMat[0];
#else
    pInMat = (float *)&inMat[0];

    for(i = 0; i < NUM_MAT * CUR_TEST_MAT_ROW * CUR_TEST_MAT_ROW; i++)
    {
      pInMat[i] = (float)(rand() +  (i % 8));
    }

    dumData(pInMat, NUM_MAT * CUR_TEST_MAT_ROW * CUR_TEST_MAT_ROW, PRINTV_FLOAT, "inMat", "w");
#endif

    /* Output Data */
    pOutInvMat  = (float   *)&invMat[0];
    pValidOut   = (uint8_t *)&validOut[0];

    /*Reference Data*/
    pRefInvMat  = (float   *)&refInvMat3x3[0];

    /*Dimension x is the cols for SIMD_WIDTH matrices interleaved*/
    inMatParams.dim_x = CUR_TEST_MAT_COL*SIMD_WIDTH;
    inMatParams.dim_y = CUR_TEST_MAT_ROW;

    /*Dimension x is the cols for SIMD_WIDTH matrices interleaved*/
    outMatParams.dim_x = CUR_TEST_MAT_COL*SIMD_WIDTH;
    outMatParams.dim_y = CUR_TEST_MAT_ROW;

    VXLIB_matInv_i32f_o32f_init
    (
       pInMat,
       &inMatParams,
       pOutInvMat,
       &outMatParams,
       pValidOut,
       NUM_MAT,
       pBlock
    );

#ifndef _HOST_EMULATION
    t0 = PROFILE_READ;
#endif

    VXLIB_matInv_i32f_o32f_kernel
    (
       pInMat,
       &inMatParams,
       pOutInvMat,
       &outMatParams,
       pValidOut,
       NUM_MAT,
       pBlock
    );
#ifndef _HOST_EMULATION
    t1 = PROFILE_READ;
#endif

    pProfile[0] = (t1 - t0);

#ifdef ERROR_REPORT
    printf("Comparing results! \n");
#endif

    result = 1;

    for(ctr = 0; ctr < (NUM_MAT * CUR_TEST_MAT_ROW * CUR_TEST_MAT_COL); ctr++)
    {
        float diff1 = __abs(pRefInvMat[ctr] - pOutInvMat[ctr]);
        float val1  = diff1 / pRefInvMat[ctr];

        float tolerance = 0.05F;

        if( val1 > tolerance )
        {
#ifdef ERROR_REPORT
            printf("Mismatch at ctr = %d, val1 = %f, pRefInvMat[ctr] = %f, pOutInvMat[ctr] = %f, tolerance = %f\n", ctr, val1, pRefInvMat[ctr], pOutInvMat[ctr], tolerance);
#endif
            result = 0;

#ifdef _EXIT_FAILURE
            exit(EXIT_FAILURE);
#endif
        }
    }

    return result;
}
