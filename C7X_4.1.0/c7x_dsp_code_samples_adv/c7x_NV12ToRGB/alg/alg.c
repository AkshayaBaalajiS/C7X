/*
* module name       : c7x_NV12ToRGB
*
* module descripton : Converts NV12 to RGB planar format
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
#include "VXLIB_convert_NV12_to_RGBpl.h"
#include "VXLIB_convert_NV12_to_RGBpl_cn.h"

#define ERROR_REPORT (0)

#ifndef _HOST_EMULATION
#define PROFILE_READ   __TSC
#endif

extern uint8_t yData[INPUT_STRIDE * INPUT_HEIGHT];
extern uint8_t cbcrData[INPUT_STRIDE * INPUT_HEIGHT];
extern uint8_t rgbRefData[OUTPUT_STRIDE * OUTPUT_HEIGHT * OUTPUT_CH];

#pragma DATA_SECTION(rgbOutData, ".rgbOutData")
ALIGN_128BYTES uint8_t rgbOutData[OUTPUT_STRIDE * OUTPUT_HEIGHT * OUTPUT_CH];

#pragma DATA_SECTION(pOutSum, ".pOutSum");
ALIGN_128BYTES uint32_t pOutSum[4];

#pragma DATA_SECTION(pBlock, ".pBlock")
ALIGN_128BYTES uint8_t pBlock[VXLIB_CONVERT_NV12_TO_RGBPL_PBLOCK_SIZE];

const int16_t coeff[5] = { 0x2000, 0x2BDD, -0x0AC5, -0x1658, 0x3770 };

int test_main(uint32_t *pProfile)
{
    uint8_t *pY;
    uint8_t *pCbCr;
    uint8_t *pRGBOut;
    uint8_t *pRGBRef;

    VXLIB_bufParams2D_t sYBlockParams;
    VXLIB_bufParams2D_t sCbCrBlockParams;
    VXLIB_bufParams3D_t sRGBBlockParams;

    int32_t result;
    int32_t blkX, blkY;

    uint64_t t0, t1;

    sYBlockParams.dim_x     = INPUT_WIDTH;
    sYBlockParams.dim_y     = INPUT_HEIGHT;
    sYBlockParams.stride_y  = INPUT_STRIDE;
    sYBlockParams.data_type = VXLIB_UINT8;

    sCbCrBlockParams.dim_x     = INPUT_WIDTH;
    sCbCrBlockParams.dim_y     = INPUT_HEIGHT >> 1;
    sCbCrBlockParams.stride_y  = INPUT_STRIDE;
    sCbCrBlockParams.data_type = VXLIB_UINT8;

    sRGBBlockParams.dim_x     = OUTPUT_WIDTH;
    sRGBBlockParams.dim_y     = OUTPUT_HEIGHT;
    sRGBBlockParams.stride_y  = OUTPUT_STRIDE;
    sRGBBlockParams.dim_z     = OUTPUT_CH;
    sRGBBlockParams.stride_z  = OUTPUT_STRIDE * OUTPUT_HEIGHT;
    sRGBBlockParams.data_type = VXLIB_UINT8;

    /* Input data */
    pY      = (uint8_t *)&yData[0];
    pCbCr   = (uint8_t *)&cbcrData[0];
    pRGBRef = (uint8_t *)&rgbRefData[0];

    /* Output Data */
    pRGBOut = (uint8_t *)&rgbOutData[0];

    VXLIB_convert_NV12_to_RGBpl_init
    (
       pY,
       &sYBlockParams,
       pCbCr,
       &sCbCrBlockParams,
       pRGBOut,
       &sRGBBlockParams,
       coeff,
       &pBlock
    );

#ifndef _HOST_EMULATION
    t0 = PROFILE_READ;
#endif

    VXLIB_convert_NV12_to_RGBpl_kernel
    (
       pY,
       &sYBlockParams,
       pCbCr,
       &sCbCrBlockParams,
       pRGBOut,
       &sRGBBlockParams,
       coeff,
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
             if(pRGBOut[offset] != pRGBRef[offset])
             {
#if(ERROR_REPORT)
                printf("Mismatch at blkX = %d, blkY = %d, pRGB = %d, pRGBRef = %d\n", blkX, blkY, pRGBOut[offset], pRGBRef[offset]);
#endif
                result = 0;
             }
        }
    }

    return result;
}
