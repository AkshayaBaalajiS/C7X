/*
* module name       : c7x_fast9Corners
*
* module descripton : Computes FAST9 corners
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/
#include <stdint.h>

#define FAST9_DIAMETER (6)

#define INPUT_WIDTH    (256)
#define INPUT_HEIGHT   (64)
#define INPUT_SIZE     (INPUT_WIDTH * INPUT_HEIGHT)

#define OUTPUT_WIDTH  (INPUT_WIDTH  - FAST9_DIAMETER)
#define OUTPUT_HEIGHT (INPUT_HEIGHT - FAST9_DIAMETER)
#define OUTPUT_SIZE   (OUTPUT_WIDTH * OUTPUT_HEIGHT)

#define SCRATCH_SIZE   ((4 * INPUT_SIZE) + (OUTPUT_SIZE * 2 * 2) + OUTPUT_SIZE)

#define ALIGN_128BYTES __attribute__((aligned(128)))
