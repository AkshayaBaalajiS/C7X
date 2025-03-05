/*
* module name       : c7x_integral_image
*
* module descripton : Computes integral image
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#include <stdint.h>

#define INPUT_WIDTH   (128)
#define INPUT_HEIGHT  (128)
#define OUTPUT_WIDTH  (INPUT_WIDTH)
#define OUTPUT_HEIGHT (INPUT_HEIGHT)

#define ALIGN_128BYTES __attribute__((aligned(128)))
