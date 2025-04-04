/*
* module name       : c7x_sobelX_3x3
*
* module descripton : Computes Sobel X gradients across 3x3 window
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/
#include <stdint.h>

#define ALIGN_64BYTES(width) (((width + 63) >> 6) << 6)

#define INPUT_WIDTH   (128 * 3)
#define INPUT_HEIGHT  (256)
#define INPUT_STRIDE  (ALIGN_64BYTES(INPUT_WIDTH))

#define OUTPUT_WIDTH  (INPUT_WIDTH  - 2)
#define OUTPUT_HEIGHT (INPUT_HEIGHT - 2)
#define OUTPUT_STRIDE (ALIGN_64BYTES(OUTPUT_WIDTH))

#define ALIGN_128BYTES __attribute__((aligned(128)))
