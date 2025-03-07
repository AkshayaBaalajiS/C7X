/*
* module name       : c7x_harris_score_3x3
*
* module descripton : Computes Harris Score for 3x3 window
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/
#include "array.h"
#include "memory.h"

#pragma DATA_SECTION(".refQC")
ALIGN_128BYTES uint8_t  refQC[QC512_SIZE] = {
  90, 193, 107,   2, 248, 132,  49,   0,  28, 236, 216,   3, 229,  98,  22,   3,  51, 227, 194,   0,  39,  76, 132,   2, 252,  24,  26,   2, 250, 113,  48,   1,  30, 143, 228,   3,  17,  94, 212,   3,  72, 114,  32,   2, 149, 112, 207,   2,  92, 130,  87,   2, 155, 135,  85,   3,  44, 161,   4,   1, 210, 100, 111,   0};
