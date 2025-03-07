/*
* module name       : c7x_erosion_3x3
*
* module descripton : 3x3 greyscale erosion
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/
#include <stdint.h>

#define ALIGN_64BYTES(width) (((width + 63) >> 6) << 6)

#define INPUT_WIDTH   (256 * 3)
#define INPUT_HEIGHT  (256)
#define INPUT_STRIDE  (INPUT_WIDTH)

#define OUTPUT_WIDTH  (INPUT_WIDTH  - 2)
#define OUTPUT_HEIGHT (INPUT_HEIGHT - 2)
#define OUTPUT_STRIDE (INPUT_WIDTH)

#define ALIGN_128BYTES __attribute__((aligned(128)))
