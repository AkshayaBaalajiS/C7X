/*
* module name       : c7x_sample1
*
* module descripton : Addition of two array using C7x vector types
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#include "add_arrays.h"

void addArrays_cn(int16_t *pInA, int16_t *pInB, int16_t *pOutC, int32_t arraySize)
{
    int32_t ctr;

    for(ctr = 0; ctr < arraySize; ctr++)
    {
        pOutC[ctr] = pInA[ctr] + pInB[ctr];
    }
}
