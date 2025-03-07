/*
* module name       : c7x_hough_lines
*
* module descripton : Computes Hough Lines
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#include <stdint.h>

#define BLOCK_WIDTH   (640)
#define BLOCK_HEIGHT  (480)

#define THETA_RANGE (267)
#define RHO_RANGE (267)
#define EDGE_MAP_LIST_SIZE (3835)

#define ALIGN_128BYTES __attribute__((aligned(128)))
