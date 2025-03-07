/*
* module name       : c7x_kalman_4x8_predict
*
* module descripton : Does a 4x8 (constant velocity) Kalman filter predict
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#ifndef VXLIB_KALMANFILTER_4X8_PREDICT_F32_H_
#define VXLIB_KALMANFILTER_4X8_PREDICT_F32_H_ 1

#include "VXLIB_kalmanFilter.h"

#define VXLIB_KALMANFILTER_4X8_PREDICT_F32_PBLOCK_SIZE (512)

void VXLIB_kalmanFilter_4x8_Predict_F32_init(VXLIB_kalmanFilter_4x8_F32 *KF, void *pBlock);
void VXLIB_kalmanFilter_4x8_Predict_F32_kernel(VXLIB_kalmanFilter_4x8_F32 *KF, void *pBlock);

#endif /* VXLIB_KALMANFILTER_4X8_PREDICT_F32_H_ */
