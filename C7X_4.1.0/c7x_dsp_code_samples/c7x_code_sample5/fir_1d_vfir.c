/*
* module name       : c7x_sample5
*
* module descripton : 1D FIR filter using VFIR instruction
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#include "fir_1d_vfir.h"

#define SIMD_WIDTH (32)
#define SE0_PARAM_OFFSET (0)
#define SA0_PARAM_OFFSET (SE0_PARAM_OFFSET + SE_PARAM_SIZE)

void fir_1d_vfir_init(int16_t *pIn, int16_t *pCoeff, int16_t *pOut, int32_t inputSize, int32_t coeffSize, uint8_t *pBlock)
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

    seFlags.ELETYPE   = __SE_ELETYPE_16BIT;           
    seFlags.VECLEN    = __SE_VECLEN_32ELEMS;

    seParam.ICNT0 = inputSize;
    seParam.ICNT1 = 1;  seParam.DIM1 = 0;
    seParam.ICNT2 = 1;  seParam.DIM2 = 0;

    seTemplate = __SE_SET_PARAM_3D(&seParam, &seFlags);

    *stov_ptr(__STRM_TEMPLATE, (uint32_t *)&pBlock[SE0_PARAM_OFFSET]) = seTemplate;

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

void fir_1d_vfir(int16_t *pIn, int16_t *pCoeff, int16_t *pOut, int32_t inputSize, int32_t coeffSize, uint8_t *pBlock)
{
    __STRM_TEMPLATE seTemplate;
    __STRM_TEMPLATE saTemplate;
    
    int32_t j;
    int32_t outputSize;
    
    /* Read template and open Streaming Engine 0 */
    seTemplate = *stov_ptr(__STRM_TEMPLATE, (uint32_t *)&pBlock[SE0_PARAM_OFFSET]);
    __SE0_OPEN(pIn, seTemplate);
    __SE1_OPEN(pIn + SIMD_WIDTH, seTemplate);

    /* Read template and open Address Generator 0 */
    saTemplate = *stov_ptr(__STRM_TEMPLATE, (uint32_t *)&pBlock[SA0_PARAM_OFFSET]);
    __SA0_OPEN(saTemplate);

    /* Read 4-16b coefficients as 1-64b value and load duplicate to fill vCoeff vector */
    ulong8 vCoeff = __vload_dup((ulong *)pCoeff);

    outputSize = inputSize - coeffSize + 1;
    
    /* Loop iterates for OUTPUT_SIZE/SIMD_WIDTH */
    for(j = 0; j < outputSize; j+=SIMD_WIDTH) {
    
        int16 vOutLo, vOutHi;
        short32 vOut;
    
        /* USE VFIR4HW to compute 1D FIR of 4 tap filter. */
        __vfir4hw_vww(__as_short32(vCoeff), __SE_REG_PAIR_0_ADV, vOutLo, vOutHi);
    
        /* Pack and Saturate 32-bit results to 16-bits */
        vOut = __pack_sat(vOutHi, vOutLo);
    
        /* Store the result */
        *__SA0ADV(short32, pOut) = __deal_stride2(vOut);
    }

    /* Close Streaming Engine and Address Generator */
    __SA0_CLOSE();
    __SE1_CLOSE();
    __SE0_CLOSE();
    
}



