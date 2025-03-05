/*
* module name       : c7x_cellSum_4x4
*
* module descripton : Computes 4x4 non-overlapping cell sums
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/
#include <stdint.h>

#define CELL_SIZE     (4)
#define CELL_STRIDE   (4)
#define NUM_BINS      (2)
#define INPUT_WIDTH   (256 + 128) //Width is modified to skew L2 banks every row
#define INPUT_HEIGHT  (128)
#define INPUT_STRIDE  (INPUT_WIDTH)

#define FEAT_WIDTH(width, cellSize, cellStride)  ((((width) - (cellSize))/(cellStride)) + 1)
#define FEAT_HEIGHT(height, cellSize, cellStride) (((height - (cellSize))/(cellStride)) + 1)
#define FEAT_PITCH(width) (((width + 8) >> 4) << 4)

#define OUTPUT_WIDTH  (FEAT_WIDTH(INPUT_WIDTH, CELL_SIZE, CELL_STRIDE))
#define OUTPUT_HEIGHT (FEAT_HEIGHT(INPUT_HEIGHT, CELL_SIZE, CELL_STRIDE))

#define ALIGN_128BYTES __attribute__((aligned(128)))
