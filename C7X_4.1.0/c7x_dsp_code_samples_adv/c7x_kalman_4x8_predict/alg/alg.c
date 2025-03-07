/*
* module name       : c7x_kalman_4x8_predict
*
* module descripton : Does a 4x8 (constant velocity) Kalman filter predict
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
#include "VXLIB_kalmanFilter.h"
#include "VXLIB_kalmanFilter_4x8_Predict_F32.h"
#include <stdio.h>

#define ERROR_REPORT (0)

#ifndef _HOST_EMULATION
#define PROFILE_READ   __TSC
#endif

#define NUM_OBJECTS (16)

#define VXLIB_MAX_10p5    1024
#define VXLIB_MAX_12p4    4096
#define VXLIB_MAX_13p2    8192
#define VXLIB_MAX_16p16   65536

#define ABS(x) (((x) > 0)?(x):(-(x)))

extern float initState[NUM_ITR][SD_4x8];
extern float initCovariance[NUM_ITR][SD_4x8 * SD_4x8];
extern float predState[NUM_ITR][SD_4x8];
extern float predCovariance[NUM_ITR][SD_4x8 * SD_4x8];
extern float measurement[NUM_ITR][MD_4x8];
extern float correctedState[NUM_ITR][SD_4x8];
extern float correctedCovariance[NUM_ITR][SD_4x8 * SD_4x8];

#pragma DATA_SECTION(sKF, ".sKF");
ALIGN_128BYTES VXLIB_kalmanFilter_4x8_F32 sKF;

#pragma DATA_SECTION(pBlock, ".pBlock")
ALIGN_128BYTES uint8_t pBlock[VXLIB_KALMANFILTER_4X8_PREDICT_F32_PBLOCK_SIZE];

int test_main(uint32_t *pProfile)
{
    VXLIB_kalmanFilter_4x8_F32 *pKF;

    int32_t result;
    int32_t ctr, i;

    uint64_t t0, t1;

#ifndef _IEEE_FLOAT
    __FPCR = 0x10;
#endif

    pKF = &sKF;

    memset(pKF, 0, sizeof(VXLIB_kalmanFilter_4x8_F32));

    pKF->scaleFactor = 5;

    for( i=0; i < SD_4x8; i++ ) {
        int32_t index = i * SD_4x8 + i;
        pKF->errorCov[index]   = 1000;
        pKF->transition[index] = 1;
        if( i < MD_4x8 ) {
            pKF->measurement[index] = 1;
        }
    }

    pKF->transition[2]  = 1;
    pKF->transition[4]  = 0.5;
    pKF->transition[9]  = 1;
    pKF->transition[11] = 0.5;
    pKF->transition[16] = 1;
    pKF->transition[23] = 1;

    pKF->measurementNoiseCov[0]  = 2500;
    pKF->measurementNoiseCov[5]  = 2500;
    pKF->measurementNoiseCov[10] = 100;
    pKF->measurementNoiseCov[15] = 100;

    pKF->processNoiseCov[0]  = 0.25;
    pKF->processNoiseCov[1]  = 0.25;
    pKF->processNoiseCov[2]  = 0.25;
    pKF->processNoiseCov[6]  = 0.25;
    pKF->processNoiseCov[7]  = 0.2500;
    pKF->processNoiseCov[8]  = 0.5000;
    pKF->processNoiseCov[12] = 0.25;
    pKF->processNoiseCov[13] = 0.5000;
    pKF->processNoiseCov[14] = 1.000;

    pKF->processNoiseCov[21] = 0.25;
    pKF->processNoiseCov[22] = 0.25;
    pKF->processNoiseCov[23] = 0.25;
    pKF->processNoiseCov[27] = 0.25;
    pKF->processNoiseCov[28] = 0.2500;
    pKF->processNoiseCov[29] = 0.5000;
    pKF->processNoiseCov[33] = 0.25;
    pKF->processNoiseCov[34] = 0.5000;
    pKF->processNoiseCov[35] = 1.000;

    pKF->state[0] = 190;
    pKF->state[1] = 190;
    pKF->state[2] = 0;
    pKF->state[3] = 0;
    pKF->state[4] = 0;
    pKF->state[5] = 0;
    pKF->state[6] = 0;
    pKF->state[7] = 0;

    result  = 1;

    VXLIB_kalmanFilter_4x8_Predict_F32_init(pKF, &pBlock);

#ifndef _HOST_EMULATION
    t0 = PROFILE_READ;
#endif

    for(ctr = 0; ctr < NUM_OBJECTS; ctr++) {
          VXLIB_kalmanFilter_4x8_Predict_F32_kernel(pKF, &pBlock);
    }

#ifndef _HOST_EMULATION
    t1 = PROFILE_READ;
#endif

    pProfile[0] = (t1 - t0);

#if(ERROR_REPORT)
    printf("Comparing results! \n");
#endif

       for(ctr = 0; ctr < SD_4x8; ctr++)
       {
          if(ABS(pKF->predictedState[ctr] - predState[0][ctr]) > 0.0001)
          {
#if(ERROR_REPORT)
             printf("State Mismatch at ctr = %d, pOut = %f, pOutRef = %f, diff = %f \n", ctr, pKF->predictedState[ctr], predState[0][ctr], (pKF->predictedState[ctr] - predState[0][ctr]));
#endif
             result = 0;
          }
      }

       for(ctr = 0; ctr < (SD_4x8 * SD_4x8); ctr++)
       {
          if(ABS(pKF->predictedErrorCov[ctr] - predCovariance[0][ctr]) > 0.0001)
          {
#if(ERROR_REPORT)
             printf("Covariance Mismatch at ctr = %d, pOut = %f, pOutRef = %f, diff = %f \n", ctr,
                      pKF->predictedErrorCov[ctr], predCovariance[0][ctr], (pKF->predictedErrorCov[ctr] - predCovariance[0][ctr]));
#endif
             result = 0;
          }
      }

   return result;
}
