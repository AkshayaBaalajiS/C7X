/*
* module name       : c7x_median_5x5
*
* module descripton : Computes a 5x5 2D-median filter
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/
#include <stdint.h>

#define ALIGN_64BYTES(width) (((width + 63) >> 6) << 6)

#define KERNEL_SIZE   (5)
#define INPUT_WIDTH   (36)
#define INPUT_HEIGHT  (36)
#define INPUT_STRIDE  (ALIGN_64BYTES(INPUT_WIDTH))

#define OUTPUT_WIDTH  (INPUT_WIDTH  - KERNEL_SIZE + 1)
#define OUTPUT_HEIGHT (INPUT_HEIGHT - KERNEL_SIZE + 1)
#define OUTPUT_STRIDE (ALIGN_64BYTES(OUTPUT_WIDTH))

#define ALIGN_128BYTES __attribute__((aligned(128)))
