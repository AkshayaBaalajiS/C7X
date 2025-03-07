/*
* module name       : c7x_fft1d_16bit
*
* module descripton : Computes 1D FFT for 16bit samples
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
#include "FFTLIB_bufParams.h"
#include "FFTLIB_fft1d_i16sc_c16sc_o16sc_cn.h"
#include "FFTLIB_fft1d_i16sc_c16sc_o16sc.h"

#ifndef _HOST_EMULATION
#define PROFILE_READ   __TSC
#endif

#pragma DATA_SECTION(outData, ".outData");
ALIGN_128BYTES int16_t  outData[MAX_NUMPOINTS*2];

#pragma DATA_SECTION(inData, ".inData");
ALIGN_128BYTES int16_t  inData[MAX_NUMPOINTS*2];

#pragma DATA_SECTION(pOutSum, ".pOutSum");
ALIGN_128BYTES uint32_t pOutSum[4];

#pragma DATA_SECTION(pBlock, ".pBlock");
ALIGN_128BYTES uint8_t pBlock[FFTLIB_FFT1D_I16SC_C16SC_O16SC_PBLOCK_SIZE];

int test_main(uint32_t *pProfile)
{
   int32_t    tpi;
   fft1d_i16sc_c16sc_o16sc_testParams_t *prm;

   uint64_t t0, t1;

   int32_t numTests;
   int32_t result;
   int32_t k;
   FFTLIB_bufParams1D_t bufParamsData;
   FFTLIB_bufParams1D_t bufParamsShift;
   uint32_t numPoints;
   uint32_t numShifts;
   int16_t *pX, *pW, *pY;
   uint32_t *pShift;

   fft1d_i16sc_c16sc_o16sc_getTestParams(&prm, &numTests);

   result = 1;
   for( tpi=0; tpi < numTests; tpi++ ) {
      numPoints = prm[tpi].numPoints;
      numShifts = prm[tpi].numShifts;

      bufParamsData.dim_x = numPoints*2;
      bufParamsData.data_type = FFTLIB_INT16;
      pX = &inData[0];
      pY = &outData[0];
      pW = &prm[tpi].twiddleFactors[0];

      bufParamsShift.dim_x = numShifts;
      bufParamsShift.data_type = FFTLIB_UINT32;
      pShift = &prm[tpi].shiftVector[0];

      FFTLIB_fft1d_i16sc_c16sc_o16sc_init((int16_t *)pX, &bufParamsData,
                                          (int16_t *)pW, &bufParamsData,
                                          (int16_t *)pY, &bufParamsData,
                                          (uint32_t *)pShift, &bufParamsShift,
                                          pBlock);

      for (k = 0; k < numPoints*2; k++) {
          pX[k] = prm[tpi].staticIn0[k];
      }

#ifndef _HOST_EMULATION
      t0 = PROFILE_READ;
#endif

      FFTLIB_fft1d_i16sc_c16sc_o16sc_kernel((int16_t *)pX, &bufParamsData,
                                            (int16_t *)pW, &bufParamsData,
                                            (int16_t *)pY, &bufParamsData,
                                            (uint32_t *)pShift, &bufParamsShift,
                                            pBlock);

#ifndef _HOST_EMULATION
      t1 = PROFILE_READ;
#endif

      pProfile[0] = (t1 - t0);

#if(ERROR_REPORT)
      printf("Comparing results! \n");
#endif

      result = 1;
      for (k = 0; k < numPoints*2; k++) {
         if (pY[k] != prm[tpi].staticOut[k]) {
#if(ERROR_REPORT)
            printf("Mismatch at k = %d, pY = %d, staticOut = %d\n", k, pY[k], prm[tpi].staticOut[k]);
#endif
            result = 0;

#ifdef _EXIT_FAILURE
            exit(EXIT_FAILURE);
#endif
         }
      }

      if (!result)
         break;
   }

   return result;
}
