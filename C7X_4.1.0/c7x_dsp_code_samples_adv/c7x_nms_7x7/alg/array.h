/*
* module name       : c7x_nms
*
* module descripton : Computes 7x7 window Non Maximum Suppression
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/
#include <stdint.h>

#define ALIGN_64BYTES(width) (((width + 63) >> 6) << 6)

#define INPUT_WIDTH   (192)
#define INPUT_HEIGHT  (128)
#define INPUT_STRIDE  (ALIGN_64BYTES(INPUT_WIDTH))

#define WINDOW_SIZE    (7)
#define OUTPUT_WIDTH  (INPUT_WIDTH  - (WINDOW_SIZE -1))
#define OUTPUT_HEIGHT (INPUT_HEIGHT - (WINDOW_SIZE -1))
#define OUTPUT_STRIDE (ALIGN_64BYTES(OUTPUT_WIDTH))

#define THRESHOLD      (100)
#define SCRATCH1_SIZE  (OUTPUT_STRIDE * INPUT_HEIGHT)
#define SCRATCH2_SIZE  (OUTPUT_STRIDE * OUTPUT_HEIGHT)

#define ALIGN_128BYTES __attribute__((aligned(128)))
