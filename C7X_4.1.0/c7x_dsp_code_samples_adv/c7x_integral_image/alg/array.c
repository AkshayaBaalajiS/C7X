/*
* module name       : c7x_integral_image
*
* module descripton : Computes integral image
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#include "array.h"
#include "memory.h"

#pragma DATA_SECTION(refQC, ".refQC")
ALIGN_128BYTES uint8_t  refQC[QC512_SIZE] = {
 163, 236,  21,   0, 163, 215,   5,   0,  41,  43,   4,   0,  52, 225,   3,   0, 207,  21,  13,   0,  58,  18,   5,   0, 139,  51,   9,   0, 248, 138,   1,   0, 127,  38,  17,   0, 242, 243,  12,   0,  71,  15,  11,   0,   9,  63,  16,   0,  79, 249,  10,   0, 175,  61,  22,   0, 149,  71,  10,   0, 167, 173,  24,   0};
