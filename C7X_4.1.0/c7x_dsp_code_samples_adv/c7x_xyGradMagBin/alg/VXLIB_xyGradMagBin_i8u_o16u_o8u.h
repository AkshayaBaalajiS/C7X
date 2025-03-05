/*
* module name       : c7x_xyGradMagBin
*
* module descripton : Computes X/Y Gradients and Orientation
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#ifndef VXLIB_XYGRADMAGBIN_I8U_O16U_O8U_H_
#define VXLIB_XYGRADMAGBIN_I8U_O16U_O8U_H_ 1

#include "VXLIB_types.h"

#define VXLIB_XYGRADMAGBIN_I8U_O16U_O8U_PBLOCK_SIZE (256)

VXLIB_STATUS VXLIB_xyGradMagBin_i8u_o16u_o8u_init(void *pIn,
                                                  VXLIB_bufParams2D_t *pInParams,
                                                  void *pMag,
                                                  VXLIB_bufParams2D_t *pMagParams,
                                                  void *pBins,
                                                  VXLIB_bufParams2D_t *pBinParams,
                                                  uint32_t *pCosSinTbl,
                                                  int32_t numBins,
                                                  void *pBlock);

VXLIB_STATUS VXLIB_xyGradMagBin_i8u_o16u_o8u_kernel(void *pIn,
                                                    VXLIB_bufParams2D_t *pInParams,
                                                    void *pMag,
                                                    VXLIB_bufParams2D_t *pMagParams,
                                                    void *pBins,
                                                    VXLIB_bufParams2D_t *pBinParams,
                                                    uint32_t *pCosSinTbl,
                                                    int32_t numBins,
                                                    void *pBlock);

VXLIB_STATUS VXLIB_xyGradMagBin_i8u_o16u_o8u_checkParams(void *pIn,
                                                         VXLIB_bufParams2D_t *pInParams,
                                                         void *pMag,
                                                         VXLIB_bufParams2D_t *pMagParams,
                                                         void *pBins,
                                                         VXLIB_bufParams2D_t *pBinParams,
                                                         uint32_t *pCosSinTbl,
                                                         int32_t numBins,
                                                         void *pBlock);

#endif /* _VXLIB_XYGRADIENTSMAGNITUDEANDORIENTATION_H_ */
