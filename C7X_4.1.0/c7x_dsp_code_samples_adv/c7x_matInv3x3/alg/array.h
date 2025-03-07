/*
* module name       : c7x_matInv3x3
*
* module descripton : Does 3x3 matrix inverse
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/
#include <stdint.h>

#define NUM_MAT      (160)
#define VEC_LEN      (16)
#define SIMD_WIDTH   (16)
#define MAX_MAT_ROWS (3)
#define MAX_MAT_COLS (MAX_MAT_ROWS)
#define CUR_TEST_MAT_ROW (MAX_MAT_ROWS)
#define CUR_TEST_MAT_COL (CUR_TEST_MAT_ROW)

#define SCRATCH_SIZE (MAX_MAT_ROWS * SIMD_WIDTH * 4)

#ifndef __C7X_HOSTEM__
#define ALIGN_128BYTES __attribute__((aligned(128)))
#else
#define ALIGN_128BYTES __declspec(align(128))
#endif
