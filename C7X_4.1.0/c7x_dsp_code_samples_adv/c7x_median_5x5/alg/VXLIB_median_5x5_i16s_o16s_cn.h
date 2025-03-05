/*
* module name       : c7x_median_5x5
*
* module descripton : Computes a 5x5 2D-median filter
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#ifndef _VXLIB_MEDIAN_5x5_I16S_O16S_CN_H_
#define _VXLIB_MEDIAN_5x5_I16S_O16S_CN_H_ 1

#include "VXLIB_types.h"

VXLIB_STATUS VXLIB_median_5x5_i16s_o16s_cn(void *pIn,
                                           VXLIB_bufParams2D_t *pInParams,
                                           void *pOut,
                                           VXLIB_bufParams2D_t *pOutParams);

#endif /* _VXLIB_MEDIAN_5x5_I16S_O16S_CN_H_ */
