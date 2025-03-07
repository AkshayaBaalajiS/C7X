/*
* module name       : c7x_cellSum_4x4
*
* module descripton : Computes 4x4 non-overlapping cell sums
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#ifndef _VXLIB_CELLSUM_4x4_I16U_O16U_H_
#define _VXLIB_CELLSUM_4x4_I16U_O16U_H_ 1

#include "VXLIB_types.h"

#define VXLIB_CELLSUM_4x4_I16U_O16U_PBLOCK_SIZE (256)

VXLIB_STATUS VXLIB_cellSum_4x4_i16u_o16u_init(void *pMagPlanes,
                                              VXLIB_bufParams3D_t *pMagPlanesParams,
                                              void *pHOGPlanes,
                                              VXLIB_bufParams3D_t *pHOGPlanesParams,
                                              int32_t numBins,
                                              void *pBlock);

VXLIB_STATUS VXLIB_cellSum_4x4_i16u_o16u_kernel(void *pMagPlanes,
                                                VXLIB_bufParams3D_t *pMagPlanesParams,
                                                void *pHOGPlanes,
                                                VXLIB_bufParams3D_t *pHOGPlanesParams,
                                                int32_t numBins,
                                                void *pBlock);

VXLIB_STATUS VXLIB_cellSum_4x4_i16u_o16u_checkParams(void *pMagPlanes,
                                                     VXLIB_bufParams3D_t *pMagPlanesParams,
                                                     void *pHOGPlanes,
                                                     VXLIB_bufParams3D_t *pHOGPlanesParams,
                                                     int32_t numBins,
                                                     void *pBlock);
#endif /* _VXLIB_CELLSUM_4x4_I16U_O16U_H_ */
