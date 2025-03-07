/*
* module name       : c7x_mergeSort
*
* module descripton : Performs sorting of 512, 32-bit elements
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#ifndef _VXLIB_MERGE_SORT_I32S_O32S_H_
#define _VXLIB_MERGE_SORT_I32S_O32S_H_ 1

#include "VXLIB_types.h"

#define VXLIB_MERGE_SORT_I32S_O32S_PBLOCK_SIZE (2048)

VXLIB_STATUS    VXLIB_mergeSort_i32s_o32s_init(int32_t dat[restrict],
                                               int32_t out[restrict],
                                               int16_t dat_size,
                                               void *pBlock);

VXLIB_STATUS    VXLIB_mergeSort_i32s_o32s_kernel(int32_t dat[restrict],
                                                 int32_t out[restrict],
                                                 int16_t dat_size,
                                                 void *pBlock);

VXLIB_STATUS VXLIB_mergeSort_i32s_o32s_checkParams(int32_t dat[restrict],
                                                   int32_t out[restrict],
                                                   int16_t dat_size,
                                                   void *pBlock);
#endif /* _VXLIB_MERGE_SORT_I32S_O32S_H_ */
