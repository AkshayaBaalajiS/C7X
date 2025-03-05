/*
* module name       : c7x_sample1
*
* module descripton : Addition of two array using C7x vector types
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#ifndef ADD_ARRAYS_H_
#define ADD_ARRAYS_H_ 1

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef _HOST_EMULATION
#include "c7x_host_emulation.h"
#else
#include <vcop/vcop.h>
#include <c7x.h>

#define PROFILE_READ   __TSC
#endif



void addArrays(int16_t *pInA, int16_t *pInB, int16_t *pOutC, int32_t arraySize);
void addArrays_cn(int16_t *pInA, int16_t *pInB, int16_t *pOutC, int32_t arraySize);

#endif //ADD_ARRAYS_H_
