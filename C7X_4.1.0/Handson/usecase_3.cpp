#ifndef FIR_1D_SE_H_
#define FIR_1D_SE_H_ 1

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
// #include "c7x.h"
#include "c7x_host_emulation.h"
// #include</home/akshayabaalaji-s/C7X/TI_C7X_DSP_TRAINING/ti-cgt-c7000_4.1.0.LTS/host_emulation/include/C7100/c7x.h>
#define SIMD_WIDTH (32)

#define SE0_PARAM_OFFSET (0)
#define SE1_PARAM_OFFSET (SE0_PARAM_OFFSET + SE_PARAM_SIZE)

#ifndef _HOST_EMULATION
#define PROFILE_READ   __TSC
#else
#include <c7x_host_emulation.h>
#endif

void fir_1d_se_init(int16_t *pIn, int16_t *pCoeff, int16_t *pOut, int32_t inputSize, int32_t coeffSize, uint8_t *pBlock);
void fir_1d_se(int16_t *pIn, int16_t *pCoeff, int16_t *pOut, int32_t inputSize, int32_t coeffSize, uint8_t *pBlock);
void fir_1d_se_cn(int16_t *pIn, int16_t *pCoeff, int16_t *pOut_cn, int32_t inputSize, int32_t coeffSize);

#endif //FIR_1D_SE_H_


#define INPUT_SIZE (96)
#define COEFF_SIZE (7)
#define OUTPUT_SIZE (INPUT_SIZE)

uint8_t pBlock[128];

#ifndef _HOST_EMULATION
int64_t t0,t1,t2;
#endif

void fir_1d_se_init(int16_t *pIn, int16_t *pCoeff, int16_t *pOut, int32_t inputSize, int32_t coeffSize, uint8_t *pBlock)
{
    __STRM_TEMPLATE seTemplate;
    __SE_FLAGS seFlags;
    __STRM_PARAM_3D seParam;

    //Setup Streaming Engine 0 to fetch input data
    seFlags = __SE_FLAGS_default();

    seFlags.ELETYPE  = __SE_ELETYPE_16BIT;           
    seFlags.VECLEN   = __SE_VECLEN_32ELEMS;

    seParam.ICNT0 = SIMD_WIDTH;
    seParam.ICNT1 = coeffSize;              seParam.DIM1 = 1;          //Stride by 1 element
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
    seParam.ICNT2 = 1;                      seParam.DIM2  = 0;

    seTemplate = __SE_SET_PARAM_3D(&seParam, &seFlags);

    *stov_ptr(__STRM_TEMPLATE, (uint32_t *)&pBlock[SE1_PARAM_OFFSET]) = seTemplate;
}

void fir_1d_se(int16_t *pIn, int16_t *pCoeff, int16_t *pOut, int32_t inputSize, int32_t coeffSize, uint8_t *pBlock)
{
    __STRM_TEMPLATE seTemplate;
    
    int32_t i, j;
    int32_t outputSize;
    
    /* Read template and open Streaming Engine 0 */
    seTemplate = *stov_ptr(__STRM_TEMPLATE, (uint32_t *)&pBlock[SE0_PARAM_OFFSET]);
    __SE0_OPEN(pIn, seTemplate);

    /* Read template and open Streaming Engine 1 */
    seTemplate = *stov_ptr(__STRM_TEMPLATE, (uint32_t *)&pBlock[SE1_PARAM_OFFSET]);
    __SE1_OPEN(pCoeff, seTemplate);

    outputSize = (inputSize - coeffSize + 1);
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
    
        /* Store the result */
        *stov_ptr(short32, (int16_t *)(pOut + j)) = vOut;
    }

    /* Close Streaming Engine */
    __SE1_CLOSE();
    __SE0_CLOSE();
    
    return;
}


void fir_1d_se_cn(int16_t *pIn, int16_t *pCoeff, int16_t *pOut, int32_t outputSize, int32_t coeffSize)
{
    int16_t *pSrc;
    int32_t i, j;
    int32_t sum;

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


int main(int argc, char **argv)
{
    int16_t *pIn;
    int16_t *pCoeff;
    int16_t *pOut, *pOut_cn;
    int32_t ctr, fail;

    //Allocate input memory
    pIn = (int16_t *)malloc(INPUT_SIZE * sizeof(int16_t));

    if(pIn == NULL)
    {
        printf("Unable to allocate input memory!\n");
        return 0;
    }

    //Allocate output memory for optimized code
    pOut = (int16_t *)malloc(OUTPUT_SIZE * sizeof(int16_t));

    if(pOut == NULL)
    {
        printf("Unable to allocate output memory!\n");
        return 0;
    }

    //Allocate output memory for natural C code
    pOut_cn = (int16_t *)malloc(OUTPUT_SIZE * sizeof(int16_t));

    if(pOut_cn == NULL)
    {
        printf("Unable to allocate output memory!\n");
        return 0;
    }

    //Allocate coeff memory
    pCoeff = (int16_t *)malloc(COEFF_SIZE * sizeof(int16_t));

    if(pCoeff == NULL)
    {
        printf("Unable to allocate coeff memory!\n");
        return 0;
    }

    //Initialize input memory
    for(ctr = 0; ctr < INPUT_SIZE; ctr++)
    {
       pIn[ctr] = ctr;
    }

    //Initialize coeff memory
    for(ctr = 0; ctr < COEFF_SIZE; ctr++)
    {
       pCoeff[ctr] = ctr;
    }

    //Clear the output memories
    memset(pOut, 0, OUTPUT_SIZE * sizeof(int16_t));
    memset(pOut_cn, 0, OUTPUT_SIZE * sizeof(int16_t));

    //Call init to setup params
    fir_1d_se_init(pIn, pCoeff, pOut, INPUT_SIZE, COEFF_SIZE, &pBlock[0]);

#ifndef _HOST_EMULATION    
    t0 = PROFILE_READ;
#endif

    //Call the optimized kernel
    fir_1d_se(pIn, pCoeff, pOut, INPUT_SIZE, COEFF_SIZE, &pBlock[0]);

#ifndef _HOST_EMULATION    
    t1 = PROFILE_READ;
#endif

    //Call the natural C kernel
    fir_1d_se_cn(pIn, pCoeff, pOut_cn, INPUT_SIZE, COEFF_SIZE);

#ifndef _HOST_EMULATION   
    t2 = PROFILE_READ;

    printf("Total cycles     : Opt = %5ld, Natc = %5ld\n", (t1 - t0), (t2 - t1));
    printf("Cycles per Input : Opt = %5.2f, Natc = %5.2f\n", (float)(t1 - t0)/INPUT_SIZE, (float)(t2 - t1)/INPUT_SIZE);
    printf("Cycles per Output: Opt = %5.2f, Natc = %5.2f\n", (float)(t1 - t0)/OUTPUT_SIZE, (float)(t2 - t1)/OUTPUT_SIZE);
    
#endif

    //Compare outputs
    fail = 0;
    for(ctr = 0; ctr < (INPUT_SIZE - COEFF_SIZE + 1); ctr++)
    {
        if(pOut[ctr] != pOut_cn[ctr])
        {
            printf("Mismatch at %3d, opt = %5d, natc = %5d\n", ctr, pOut[ctr], pOut_cn[ctr]);
            fail = 1;
        }
    }
 
    //Report results
    if(fail)
       printf("Test Failed!\n");
    else
       printf("Test Pass!\n");

    //Free memories
    free(pCoeff); 
    free(pOut_cn);
    free(pOut);
    free(pIn);

    return 0;
}