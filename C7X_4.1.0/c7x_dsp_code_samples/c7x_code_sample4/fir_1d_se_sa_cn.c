/*
* module name       : c7x_sample4
*
* module descripton : 1D FIR filter using C7x vector types, Streaming Engine and Streaming Address generator
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#include "fir_1d_se_sa.h"

void fir_1d_se_sa_cn(int16_t *pIn, int16_t *pCoeff, int16_t *pOut, int32_t inputSize, int32_t coeffSize)
{
    int16_t *pSrc;
    int32_t i, j;
    int32_t sum;

    for(i = 0; i < (inputSize - coeffSize + 1); i++)
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



