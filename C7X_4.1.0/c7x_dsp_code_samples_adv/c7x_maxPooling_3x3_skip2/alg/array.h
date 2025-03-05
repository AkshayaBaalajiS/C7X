/*
* module name       : c7x_maxPooling_3x3_skip2
*
* module descripton : Max Pooling, 3x3 window, skip 2 positions horz/vert
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/
#include <stdint.h>

#define INPUT_WIDTH   (251)
#define INPUT_HEIGHT  (66)
#define INPUT_STRIDE  (256)

#define KERNEL_WIDTH  (3)
#define KERNEL_HEIGHT (3)
#define KERNEL_STRIDE (2)

#define NUM_CH        (4)

#define POOL_WIDTH(width, kernelSize, kernelStride)  ((((width) - (kernelSize))/(kernelStride)) + 1)
#define POOL_HEIGHT(height, kernelSize, kernelStride) ((((height) - (kernelSize))/(kernelStride)) + 1)
#define POOL_PITCH(width) ((((width) + 8) >> 4) << 4)

#define OUTPUT_WIDTH   (POOL_WIDTH(INPUT_WIDTH, KERNEL_WIDTH, KERNEL_STRIDE))
#define OUTPUT_HEIGHT  (POOL_HEIGHT(INPUT_HEIGHT, KERNEL_HEIGHT, KERNEL_STRIDE))
#define OUTPUT_STRIDE  (POOL_PITCH(OUTPUT_WIDTH))

#define ALIGN_128BYTES __attribute__((aligned(128)))
