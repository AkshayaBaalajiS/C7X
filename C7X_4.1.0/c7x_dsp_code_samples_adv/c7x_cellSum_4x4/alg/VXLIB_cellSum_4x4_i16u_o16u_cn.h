/*
* module name       : c7x_cellSum_4x4
*
* module descripton : Computes 4x4 non-overlapping cell sums
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#ifndef _VXLIB_CELLSUM_4x4_I16U_O16U_CN_H_
#define _VXLIB_CELLSUM_4x4_I16U_O16U_CN_H_ 1

#include "VXLIB_types.h"

VXLIB_STATUS VXLIB_cellSum_4x4_i16u_o16u_cn(void *pMagPlanes,
                                            VXLIB_bufParams3D_t *pMagPlanesParams,
                                            void *pHOGPlanes,
                                            VXLIB_bufParams3D_t *pHOGPlanesParams,
                                            int32_t numBins);

#endif /* _VXLIB_CELLSUM_4x4_I16U_O16U_CN_H_ */
