/*
* module name       : c7x_xyGradMagBin
*
* module descripton : Computes X/Y Gradients and Orientation
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
#include "VXLIB_xyGradMagBin_i8u_o16u_o8u.h"
#include "VXLIB_xyGradMagBin_i8u_o16u_o8u_cn.h"

#define Q_FACTOR      (14)
#define TB_PI (3.14159265358979323846)

#define ERROR_REPORT (0)

#ifndef _HOST_EMULATION
#define PROFILE_READ   __TSC
#endif

extern uint8_t  lumaData[INPUT_STRIDE * INPUT_HEIGHT];
extern uint8_t  binRefData[OUTPUT_STRIDE * OUTPUT_HEIGHT];
extern uint16_t magRefData[OUTPUT_STRIDE * OUTPUT_HEIGHT];

extern int16_t cosTbl[NUM_BINS];
extern int16_t sinTbl[NUM_BINS];
extern int16_t cosSinTbl[NUM_BINS*2];

#pragma DATA_SECTION(binOutData, ".binOutData");
ALIGN_128BYTES uint8_t  binOutData[OUTPUT_STRIDE * OUTPUT_HEIGHT];

#pragma DATA_SECTION(magOutData, ".magOutData");
ALIGN_128BYTES uint16_t magOutData[OUTPUT_STRIDE * OUTPUT_HEIGHT];

#pragma DATA_SECTION(pOutSum, ".pOutSum");
ALIGN_128BYTES uint32_t pOutSum[4];

#pragma DATA_SECTION(pBlock, ".pBlock");
ALIGN_128BYTES uint8_t pBlock[VXLIB_XYGRADMAGBIN_I8U_O16U_O8U_PBLOCK_SIZE];

int test_main(uint32_t *pProfile)
{
    uint8_t  *pLuma;
    uint8_t  *pBin;
    uint16_t *pMag;

    uint8_t  *pBinRef;
    uint16_t *pMagRef;

    int16_t *pCosSinTbl;

    VXLIB_bufParams2D_t sLumaBlockParams;
    VXLIB_bufParams2D_t sMagBlockParams;
    VXLIB_bufParams2D_t sBinBlockParams;

    int32_t result;
    int32_t blkX, blkY;

    uint64_t t0, t1;

    sLumaBlockParams.dim_x     = INPUT_WIDTH;
    sLumaBlockParams.dim_y     = INPUT_HEIGHT;
    sLumaBlockParams.stride_y  = INPUT_STRIDE;
    sLumaBlockParams.data_type = VXLIB_UINT8;

    sBinBlockParams.dim_x     = OUTPUT_WIDTH;
    sBinBlockParams.dim_y     = OUTPUT_HEIGHT;
    sBinBlockParams.stride_y  = OUTPUT_STRIDE;
    sBinBlockParams.data_type = VXLIB_UINT8;

    sMagBlockParams.dim_x     = OUTPUT_WIDTH;
    sMagBlockParams.dim_y     = OUTPUT_HEIGHT;
    sMagBlockParams.stride_y  = OUTPUT_STRIDE * sizeof(uint16_t);
    sMagBlockParams.data_type = VXLIB_UINT16;

    /* Input data */
    pLuma      = (uint8_t  *)&lumaData[0];
    pMagRef    = (uint16_t *)&magRefData[0];
    pBinRef    = (uint8_t  *)&binRefData[0];
    pCosSinTbl = (int16_t  *)&cosSinTbl[0];

    /* Output Data */
    pMag = (uint16_t *)&magOutData[0];
    pBin = (uint8_t  *)&binOutData[0];

       VXLIB_xyGradMagBin_i8u_o16u_o8u_init
       (
          (void *)pLuma,
          &sLumaBlockParams,
          (void *)pMag,
          &sMagBlockParams,
          (void *)pBin,
          &sBinBlockParams,
          (uint32_t *)pCosSinTbl,
          NUM_BINS,
          &pBlock
       );

#ifndef _HOST_EMULATION
      t0 = PROFILE_READ;
#endif

       VXLIB_xyGradMagBin_i8u_o16u_o8u_kernel
       (
          (void *)pLuma,
          &sLumaBlockParams,
          (void *)pMag,
          &sMagBlockParams,
          (void *)pBin,
          &sBinBlockParams,
          (uint32_t *)pCosSinTbl,
          NUM_BINS,
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

    for(blkY = 0; blkY < OUTPUT_HEIGHT; blkY++)
    {
        for(blkX = 0; blkX < OUTPUT_WIDTH; blkX++)
        {
             int32_t offset = (blkY * OUTPUT_STRIDE) + blkX;
             if(pMag[offset] != pMagRef[offset])
             {
#if(ERROR_REPORT)
                printf("Mismatch at blkX = %d, blkY = %d, pMag = %d, pMagRef = %d\n", blkX, blkY, pMag[offset], pMagRef[offset]);
#endif
                result = 0;
             }

             if(pBin[offset] != pBinRef[offset])
             {
#if(ERROR_REPORT)
                printf("Mismatch at blkX = %d, blkY = %d, pBin = %d, pBinRef = %d\n", blkX, blkY, pBin[offset], pBinRef[offset]);
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
