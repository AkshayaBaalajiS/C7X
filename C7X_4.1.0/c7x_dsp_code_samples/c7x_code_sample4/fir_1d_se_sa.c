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

#define SIMD_WIDTH (32)

#define SE0_PARAM_OFFSET (0)
#define SE1_PARAM_OFFSET (SE0_PARAM_OFFSET + SE_PARAM_SIZE)
#define SA0_PARAM_OFFSET (SE1_PARAM_OFFSET + SE_PARAM_SIZE)

void fir_1d_se_sa_init(int16_t *pIn, int16_t *pCoeff, int16_t *pOut, int32_t inputSize, int32_t coeffSize, uint8_t *pBlock)
{
    __STRM_TEMPLATE seTemplate;
    __STRM_TEMPLATE saTemplate;

    __SE_FLAGS seFlags;
    __SA_FLAGS saFlags;

    __STRM_PARAM_3D seParam;
    __STRM_PARAM_3D saParam;

    int32_t outputSize;
    
    //Setup Streaming Engine 0 to fetch input data
    seFlags = __SE_FLAGS_default();

    seFlags.ELETYPE = __SE_ELETYPE_16BIT;           
    seFlags.VECLEN  = __SE_VECLEN_32ELEMS;

    seParam.ICNT0 = SIMD_WIDTH;
    seParam.ICNT1 = coeffSize;             seParam.DIM1 = 1;          //Stride by 1 element
    seParam.ICNT2 = inputSize/SIMD_WIDTH;  seParam.DIM2 = SIMD_WIDTH; //Stride by 32 elements

    seTemplate = __SE_SET_PARAM_3D(&seParam, &seFlags);

    *stov_ptr(__STRM_TEMPLATE, (uint32_t *)&pBlock[SE0_PARAM_OFFSET]) = seTemplate;

    //Setup Streaming Engine 1 to fetch and duplicate coefficients
    seFlags = __SE_FLAGS_default();

    seFlags.ELETYPE   = __SE_ELETYPE_16BIT;           
    seFlags.ELEDUP     = __SE_ELEDUP_32X;             
    seFlags.VECLEN    = __SE_VECLEN_32ELEMS;         

    seParam.ICNT0 = coeffSize;
    seParam.ICNT1 = inputSize/SIMD_WIDTH;  seParam.DIM1  = 0;
    seParam.ICNT2 = 1;                     seParam.DIM2  = 0;

    seTemplate = __SE_SET_PARAM_3D(&seParam, &seFlags);

    *stov_ptr(__STRM_TEMPLATE, (uint32_t *)&pBlock[SE1_PARAM_OFFSET]) = seTemplate;

    //Setup Address generator to store output result
    saFlags = __SA_FLAGS_default();

    saFlags.VECLEN    = __SA_VECLEN_32ELEMS;

    outputSize = inputSize - coeffSize + 1;
    saParam.ICNT0 = outputSize;
    saParam.ICNT1 = 1;  saParam.DIM1 = 0;
    saParam.ICNT2 = 1;  saParam.DIM2 = 0;

    saTemplate = __SA_SET_PARAM_3D(&saParam, &saFlags);

    *stov_ptr(__STRM_TEMPLATE, (uint32_t *)&pBlock[SA0_PARAM_OFFSET]) = saTemplate;
}

void fir_1d_se_sa(int16_t *pIn, int16_t *pCoeff, int16_t *pOut, int32_t inputSize, int32_t coeffSize, uint8_t *pBlock)
{
    __STRM_TEMPLATE seTemplate;
    __STRM_TEMPLATE saTemplate;
    
    int32_t i, j;
    int32_t outputSize;
    
    /* Read template and open Streaming Engine 0 */
    seTemplate = *stov_ptr(__STRM_TEMPLATE, (uint32_t *)&pBlock[SE0_PARAM_OFFSET]);
    __SE0_OPEN(pIn, seTemplate);

    /* Read template and open Streaming Engine 1 */
    seTemplate = *stov_ptr(__STRM_TEMPLATE, (uint32_t *)&pBlock[SE1_PARAM_OFFSET]);
    __SE1_OPEN(pCoeff, seTemplate);

    /* Read template and open Address Generator 0 */
    saTemplate = *stov_ptr(__STRM_TEMPLATE, (uint32_t *)&pBlock[SA0_PARAM_OFFSET]);
    __SA0_OPEN(saTemplate);
    
    outputSize = inputSize - coeffSize + 1;
    
    /* Loop iterates for OUTPUT_SIZE/SIMD_WIDTH */
    for(j = 0; j < outputSize; j+=SIMD_WIDTH) {
        
        /* Initialize output vector */
        short32 vOut = (short32)(0);
    
        /* Loop iterates for number of coefficients */
        for(i = 0; i < coeffSize; i++) {

            /* Read a vector of 32-16b elements from input Array */
            short32 vIn = __SE0ADV(short32);

            /* Load and duplicate each coefficient 32 times */
            short32 vCoeff = __SE1ADV(short32);
    
            /* Multiply input with coefficient and accumulate the result */
            vOut += (vIn * vCoeff);
        }
    
        /* Store the result using SA */
        *__SA0ADV(short32, pOut) = vOut;
    }

    /* Close Streaming Engine and Address Generator */
    __SA0_CLOSE();
    __SE1_CLOSE();
    __SE0_CLOSE();
    
}



