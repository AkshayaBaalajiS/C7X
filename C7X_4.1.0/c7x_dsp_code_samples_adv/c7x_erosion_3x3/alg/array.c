/*
* module name       : c7x_erosion_3x3
*
* module descripton : 3x3 greyscale erosion
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/
#include "array.h"
#include "memory.h"

#pragma DATA_SECTION(refQC, ".refQC")
ALIGN_128BYTES uint8_t  refQC[QC512_SIZE] = {
  89, 234, 162, 106, 242, 255,   0, 133,  42,  81, 205, 120, 239, 118,  91,  47, 162,  52, 118,  60,  15, 249, 222, 220, 200, 164,  68, 249,   3, 200, 239, 187, 203, 107, 184, 134,  83, 167,  21,  76, 248,  93, 132, 220,  73, 187, 212, 152, 192,  17, 224, 206,  61, 100, 101,  99, 110, 194, 223,  32, 103, 233,   1, 242};
