/*
* module name       : c7x_sobelX_3x3
*
* module descripton : Computes Sobel X gradients across 3x3 window
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/
#include "array.h"
#include "memory.h"

#pragma DATA_SECTION(refQC, ".refQC")
ALIGN_128BYTES uint8_t  refQC[QC512_SIZE] = {
  97,   3, 137,   3,  39, 252, 182,   0, 157,   0,  42,   0, 247,   0, 172,   1,  71,   3,  46, 254, 211, 252, 144,   2,  45, 252, 135,   1,  63,   2, 117,   1,  70,   2,  83,   0, 162, 255,  20,   0,  51,   1, 122, 254, 199,   0, 217,   0, 234,   1,  24,   1,  16,   3, 161, 253, 221,   3,  43,   3, 247, 255, 111,   3};
