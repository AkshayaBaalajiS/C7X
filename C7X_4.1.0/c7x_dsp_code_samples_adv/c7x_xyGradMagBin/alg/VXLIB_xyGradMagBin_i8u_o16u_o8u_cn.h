/*
* module name       : c7x_xyGradMagBin
*
* module descripton : Computes X/Y Gradients and Orientation
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#ifndef _VXLIB_XYGRADMAGBIN_I8U_O16U_O8U_CN_H_
#define _VXLIB_XYGRADMAGBIN_I8U_O16U_O8U_CN_H_ 1

#include "VXLIB_types.h"

VXLIB_STATUS VXLIB_xyGradMagBin_i8u_o16u_o8u_cn(void *pIn,
                                                VXLIB_bufParams2D_t *pInParams,
                                                void *pMag,
                                                VXLIB_bufParams2D_t *pMagParams,
                                                void *pBins,
                                                VXLIB_bufParams2D_t *pBinParams,
                                                int16_t *pCosTbl,
                                                int16_t *pSinTbl,
                                                int32_t numBins);

#endif /*_VXLIB_XYGRADMAGBIN_I8U_O16U_O8U_CN_H_*/
