/*
* module name       : c7x_nms
*
* module descripton : Computes 7x7 window Non Maximum Suppression
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/
#include "array.h"
#include "memory.h"

#pragma DATA_SECTION(refQC, ".refQC")
ALIGN_128BYTES uint8_t  refQC[QC512_SIZE] = {
 255, 255, 255,   0,   0,   0, 255, 255, 255, 255,   0, 255, 255,   0, 255, 255,   0, 255, 255, 255, 255,   0,   0, 255,   0, 255, 255, 255,   0, 255,   0, 255, 255,   0, 255,   0,   0,   0, 255, 255,   0,   0, 255, 255,   0, 255, 255, 255,   0,   0,   0, 255,   0, 255, 255,   0,   0, 255, 255,   0, 255,   0,   0, 255};
