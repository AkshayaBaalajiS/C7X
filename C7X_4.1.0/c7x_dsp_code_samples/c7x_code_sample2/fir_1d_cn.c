/*
* module name       : c7x_sample2
*
* module descripton : 1D FIR filter using C7x vector types
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#include "fir_1d.h"

void fir1D_cn(int16_t *pIn, int16_t *pCoeff, int16_t *pOut, int32_t inputSize, int32_t coeffSize)
{
    int16_t *pSrc;
    int32_t i, j;
    int32_t sum;
    int32_t outputSize;
    
    outputSize = inputSize - coeffSize + 1;
    
    for(i = 0; i < outputSize; i++)
    {
        pSrc = (int16_t *)&pIn[i];
        sum = 0;
        for(j = 0; j < coeffSize; j++)
        {
            sum += pSrc[j] * pCoeff[j];
        }
        pOut[i] = sum;
    }
}



