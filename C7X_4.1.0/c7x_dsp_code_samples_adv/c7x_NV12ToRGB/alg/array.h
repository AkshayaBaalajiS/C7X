/*
* module name       : c7x_NV12ToRGB
*
* module descripton : Converts NV12 to RGB planar format
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/
#include <stdint.h>

#define ALIGN_64BYTES(width) (((width + 63) >> 6) << 6)

#define INPUT_WIDTH   (36)
#define INPUT_HEIGHT  (36 * 8)
#define INPUT_STRIDE  (ALIGN_64BYTES(INPUT_WIDTH))

#define OUTPUT_WIDTH  (INPUT_WIDTH)
#define OUTPUT_HEIGHT (INPUT_HEIGHT)
#define OUTPUT_CH     (3)
#define OUTPUT_STRIDE (ALIGN_64BYTES(OUTPUT_WIDTH))

#define ALIGN_128BYTES __attribute__((aligned(128)))
