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

void addArrays(int16_t *pInA, int16_t *pInB, int16_t *pOutC, int32_t arraySize)
{
    int32_t ctr;
    
    for(ctr = 0; ctr < arraySize; ctr+=32)
    {
        //Read a vector of 32-16b elements from input Array A
        short32 vInA = *stov_ptr(short32, (int16_t *)(pInA + ctr));
    
        //Read a vector of 32-16b elements from input Array A
        short32 vInB = *stov_ptr(short32, (int16_t *)(pInB + ctr));
    
        //Added 32-16b elements in parallel
        // '+' operator is overloaded to pick up the right instruction under the hood
        short32 vOutC = vInA + vInB;
    
        //Store 32-16b elements to output array C
        *stov_ptr(short32, (int16_t *)(pOutC + ctr)) = vOutC;
    }
}



