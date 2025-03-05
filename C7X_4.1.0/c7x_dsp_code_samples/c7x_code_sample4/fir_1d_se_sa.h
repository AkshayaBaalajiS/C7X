/*
* module name       : c7x_sample4
*
* module descripton : 1D FIR filter using C7x vector types, Streaming Engine and Streaming Address generator
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#ifndef FIR_1D_SE_SA_H_
#define FIR_1D_SE_SA_H_ 1

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifndef _HOST_EMULATION
#include <c7x.h>
#define PROFILE_READ   __TSC
#else
#include "c7x_host_emulation.h"
#endif

void fir_1d_se_sa_init(int16_t *pIn, int16_t *pCoeff, int16_t *pOut, int32_t inputSize, int32_t coeffSize, uint8_t *pBlock);
void fir_1d_se_sa(int16_t *pIn, int16_t *pCoeff, int16_t *pOut, int32_t inputSize, int32_t coeffSize, uint8_t *pBlock);
void fir_1d_se_sa_cn(int16_t *pIn, int16_t *pCoeff, int16_t *pOut_cn, int32_t inputSize, int32_t coeffSize);

#endif //FIR_1D_SE_SA_H_
