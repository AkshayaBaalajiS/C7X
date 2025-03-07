/*
* module name       : c7x_hough_lines
*
* module descripton : Computes Hough Lines
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
#include "VXLIB_houghLineFromList_i16u_o16u.h"

#define ERROR_REPORT (0)

#ifndef _HOST_EMULATION
#define PROFILE_READ   __TSC
#endif

extern int16_t sinTable[THETA_RANGE];
extern int16_t cosTable[THETA_RANGE];
extern uint16_t edgeMapList[2 * EDGE_MAP_LIST_SIZE];
extern uint16_t refHoughSpace[THETA_RANGE * RHO_RANGE];

#pragma DATA_SECTION(outHoughSpace, ".outHoughSpace")
ALIGN_128BYTES uint16_t outHoughSpace[THETA_RANGE * RHO_RANGE];

#pragma DATA_SECTION(pOutSum, ".pOutSum");
ALIGN_128BYTES uint32_t pOutSum[4];

#pragma DATA_SECTION(pBlock, ".pBlock")
ALIGN_128BYTES uint8_t pBlock[VXLIB_HOUGHLINE_FROM_LIST_I16U_O16U_PBLOCK_SIZE];

int test_main(uint32_t *pProfile)
{
    uint16_t *pIn;
    uint16_t *pOut;
    uint16_t *pOutRef;

    int16_t *pSin;
    int16_t *pCos;

    int32_t result;
    int32_t rho, theta;

    uint64_t t0, t1;

    /* Input data */
    pIn     = (uint16_t *)&edgeMapList[0];
    pSin    = (int16_t  *)&sinTable[0];
    pCos    = (int16_t  *)&cosTable[0];

    /* Output Data */
    pOut    = (uint16_t  *)&outHoughSpace[0];
    pOutRef = (uint16_t  *)&refHoughSpace[0];

    VXLIB_houghLineFromList_i16u_o16u_init
    (
        pIn,
        pOut,
        BLOCK_WIDTH,
        BLOCK_HEIGHT,
        EDGE_MAP_LIST_SIZE,
        THETA_RANGE,
        RHO_RANGE,
        pSin,
        pCos,
        &pBlock
    );

#ifndef _HOST_EMULATION
      t0 = PROFILE_READ;
#endif

    VXLIB_houghLineFromList_i16u_o16u_kernel
    (
        pIn,
        pOut,
        BLOCK_WIDTH,
        BLOCK_HEIGHT,
        EDGE_MAP_LIST_SIZE,
        THETA_RANGE,
        RHO_RANGE,
        pSin,
        pCos,
        &pBlock
    );

#ifndef _HOST_EMULATION
      t1 = PROFILE_READ;
#endif

    pProfile[0] = (t1 - t0);

#if(ERROR_REPORT)
    printf("Comparing results! \n");
#endif

    result = 1;

    for(theta = 0; theta < THETA_RANGE; theta++)
    {
        for(rho = 0; rho < RHO_RANGE; rho++)
        {
             int32_t offset = (theta * RHO_RANGE) + rho;
             if(pOut[offset] != pOutRef[offset])
             {
#if(ERROR_REPORT)
                printf("Mismatch at rho = %d, theta = %d, pOut = %d, pOutRef = %d\n", rho, theta, pOut[offset], pOutRef[offset]);
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
