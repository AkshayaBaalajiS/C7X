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

#define SIMD_WIDTH (32)

void fir1D(int16_t *pIn, int16_t *pCoeff, int16_t *pOut, int32_t inputSize, int32_t coeffSize)
{
    int32_t i, j;
    int32_t outputSize;

    outputSize = inputSize - coeffSize + 1;
    
    /* Loop iterates for OUTPUT_SIZE/SIMD_WIDTH */
    for(j = 0; j < outputSize; j+=SIMD_WIDTH) {
        
        /* Initialize output vector */
        short32 vOut = (short32)(0);
    
        /* Loop iterates for number of coefficients */
        for(i = 0; i < coeffSize; i++) {

            /* Read a vector of 32-16b elements from input Array */
            short32 vIn = *stov_ptr(short32, (int16_t *)(pIn + j + i));

            /* Load and duplicate each coefficient 32 times */
            short32 vCoeff = (short32)(pCoeff[i]);
    
            /* Multiply input with coefficient and accumulate the result */
            vOut += (vIn * vCoeff);
        }    

        /* Store the result */
        *stov_ptr(short32, (int16_t *)(pOut + j)) = vOut;
    }

    return;
}




