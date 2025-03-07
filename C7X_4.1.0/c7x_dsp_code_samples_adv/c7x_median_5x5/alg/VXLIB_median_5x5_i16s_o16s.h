/*
* module name       : c7x_median_5x5
*
* module descripton : Computes a 5x5 2D-median filter
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#ifndef VXLIB_MEDIAN_5X5_I16S_O16S_H_
#define VXLIB_MEDIAN_5X5_I16S_O16S_H_ 1

#include "VXLIB_types.h"

#define VXLIB_MEDIAN_5X5_I16S_O16S_PBLOCK_SIZE (256)

VXLIB_STATUS VXLIB_median_5x5_i16s_o16s_init(void *pIn,
                                             VXLIB_bufParams2D_t *pInParams,
                                             void *pOut,
                                             VXLIB_bufParams2D_t *pOutParams,
                                             void *pBlock);

VXLIB_STATUS VXLIB_median_5x5_i16s_o16s_kernel(void *pIn,
                                               VXLIB_bufParams2D_t *pInParams,
                                               void *pOut,
                                               VXLIB_bufParams2D_t *pOutParams,
                                               void *pBlock);

VXLIB_STATUS VXLIB_median_5x5_i16s_o16s_checkParams(void *pIn,
                                                    VXLIB_bufParams2D_t *pInParams,
                                                    void *pOut,
                                                    VXLIB_bufParams2D_t *pOutParams,
                                                    void *pBlock);
#endif /* VXLIB_MEDIAN_5X5_I16S_O16S_H_ */
