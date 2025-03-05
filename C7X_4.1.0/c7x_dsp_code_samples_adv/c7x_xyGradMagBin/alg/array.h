/*
* module name       : c7x_xyGradMagBin
*
* module descripton : Computes X/Y Gradients and Orientation
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/
#include <stdint.h>

#define ALIGN_64BYTES(width) (((width + 63) >> 6) << 6)

#define INPUT_WIDTH   (66)
#define INPUT_HEIGHT  (66)
#define INPUT_STRIDE  (ALIGN_64BYTES(INPUT_WIDTH))

#define OUTPUT_WIDTH  (INPUT_WIDTH  - 2)
#define OUTPUT_HEIGHT (INPUT_HEIGHT - 2)
#define OUTPUT_STRIDE (ALIGN_64BYTES(OUTPUT_WIDTH))

#define NUM_BINS      (6)

#define ALIGN_128BYTES __attribute__((aligned(128)))
