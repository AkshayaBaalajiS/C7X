/*
* module name       : c7x_harris_score_3x3
*
* module descripton : Computes Harris Score for 3x3 window
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/
#include <stdint.h>

#define ALIGN_64BYTES(width) ((((width) + 63) >> 6) << 6)

#define INPUT_WIDTH   (128)
#define INPUT_HEIGHT  (64)
#define INPUT_STRIDE  (ALIGN_64BYTES(INPUT_WIDTH))

#define BLOCK_SIZE    (3)
#define OUTPUT_WIDTH  (INPUT_WIDTH  - (BLOCK_SIZE - 1))
#define OUTPUT_HEIGHT (INPUT_HEIGHT - (BLOCK_SIZE - 1))
#define OUTPUT_STRIDE (ALIGN_64BYTES(OUTPUT_WIDTH))

#define SCRATCH_SIZE  (2 * (INPUT_STRIDE * OUTPUT_HEIGHT)) + (2 * OUTPUT_HEIGHT * OUTPUT_STRIDE)

#define ALIGN_128BYTES __attribute__((aligned(128)))
