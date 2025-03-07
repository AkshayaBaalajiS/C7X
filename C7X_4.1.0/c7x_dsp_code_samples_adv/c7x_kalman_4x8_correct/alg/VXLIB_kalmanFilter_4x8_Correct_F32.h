/*
* module name       : c7x_kalman_4x8_correct
*
* module descripton : Does a 4x8 (constant velocity) Kalman filter update
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#ifndef VXLIB_KALMANFILTER4X8_CORRECT_F32_H_
#define VXLIB_KALMANFILTER4X8_CORRECT_F32_H_ 1

#include "VXLIB_kalmanFilter.h"

#define VXLIB_KALMANFILTER_4X8_CORRECT_F32_PBLOCK_SIZE (2048)

void VXLIB_kalmanFilter_4x8_Correct_F32_init(VXLIB_kalmanFilter_4x8_F32 *KF,
                                            const VXLIB_F32 *restrict Z,
                                            VXLIB_F32 *restrict Residual,
                                            void *pBlock);

void VXLIB_kalmanFilter_4x8_Correct_F32_kernel(VXLIB_kalmanFilter_4x8_F32 *KF,
                                       const VXLIB_F32 *restrict Z,
                                       VXLIB_F32 *restrict Residual,
                                       void *pBlock);

#endif /* VXLIB_KALMANFILTER4X8_CORRECT_F32_H_ */
