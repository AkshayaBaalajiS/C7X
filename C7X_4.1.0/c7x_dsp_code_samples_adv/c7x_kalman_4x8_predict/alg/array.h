/*
* module name       : c7x_kalman_4x8_predict
*
* module descripton : Does a 4x8 (constant velocity) Kalman filter predict
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/
#include <stdint.h>

#define SD_4x8  (8)
#define MD_4x8  (4)
#define NUM_ITR (3)

#define ALIGN_128BYTES __attribute__((aligned(128)))
