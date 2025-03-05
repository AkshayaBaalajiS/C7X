/*
* module name       : c7x_conv_5x5
*
* module descripton : 5x5 convolution
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#include <stdint.h>

#define ALIGN_64BYTES(width) (((width + 63) >> 6) << 6)

#define KERNEL_WIDTH   (5)
#define KERNEL_HEIGHT  (5)
#define KERNEL_STRIDE  (8)

#define INPUT_WIDTH   (36)
#define INPUT_HEIGHT  (36)
#define INPUT_STRIDE  (ALIGN_64BYTES(INPUT_WIDTH))
#define INPUT_CH      (3)

#define OUTPUT_WIDTH  (INPUT_WIDTH - KERNEL_WIDTH + 1)
#define OUTPUT_HEIGHT (INPUT_HEIGHT - KERNEL_HEIGHT + 1)
#define OUTPUT_STRIDE (ALIGN_64BYTES(OUTPUT_WIDTH))
#define OUTPUT_CH     (16)

#define ALIGN_128BYTES __attribute__((aligned(128)))
