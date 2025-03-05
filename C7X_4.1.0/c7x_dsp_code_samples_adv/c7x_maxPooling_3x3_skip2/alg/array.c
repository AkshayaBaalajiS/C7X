/*
* module name       : c7x_maxPooling_3x3_skip2
*
* module descripton : Max Pooling, 3x3 window, skip 2 positions horz/vert
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/
#include "array.h"
#include "memory.h"

#pragma DATA_SECTION(refQC, ".refQC")
ALIGN_128BYTES uint8_t  refQC[QC512_SIZE] = {
 106, 236,  17,  73, 189,   0, 238,  31,  53, 121, 139, 124,  60,  21,  64,  77,  23, 136, 177,  57, 115,  97,  15, 158, 151,  72, 211,  84, 206,  38,  49,  57,  41, 126,  75,  82,  33,  97,  12,  54,  10,  66, 226, 103, 100,  43,  98,  15,  17, 123,  54, 122,  54,  72, 104,  66, 173, 108,   7, 177, 100,  76,  78, 254};
