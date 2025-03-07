/*
* module name       : c7x_mergeSort
*
* module descripton : Performs sorting of 512, 32-bit elements
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#ifndef _VXLIB_MERGE_SORT_I32S_O32S_CN_H_
#define _VXLIB_MERGE_SORT_I32S_O32S_CN_H_ 1

#include "VXLIB_types.h"

VXLIB_STATUS    VXLIB_mergeSort_i32s_o32s_cn(int32_t dat[],
                                             int16_t dat_size);

VXLIB_STATUS    VXLIB_mergeSort_i32s_o32s_checkParams_cn(int32_t dat[],
                                                         int16_t dat_size);
#endif /* _VXLIB_MERGE_SORT_I32S_O32S_CN_H_ */
