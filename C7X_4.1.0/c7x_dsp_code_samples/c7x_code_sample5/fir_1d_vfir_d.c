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

#define INPUT_SIZE (98)
#define COEFF_SIZE (3)
#define OUTPUT_SIZE (INPUT_SIZE)

uint8_t pBlock[256];

#ifndef _HOST_EMULATION
int64_t t0,t1,t2;
#endif

int main(int argc, char **argv)
{
    uint64_t t0,t1,t2;
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
    pOut = (int16_t *)malloc(INPUT_SIZE * sizeof(int16_t));

    if(pOut == NULL)
    {
        printf("Unable to allocate output memory!\n");
        return 0;
    }

    //Allocate output memory for natural C code
    pOut_cn = (int16_t *)malloc(INPUT_SIZE * sizeof(int16_t));

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
    fir_1d_vfir_init(pIn, pCoeff, pOut, INPUT_SIZE, COEFF_SIZE, &pBlock[0]);

#ifndef _HOST_EMULATION    
    t0 = PROFILE_READ;
#endif

    //Call the optimized kernel
    fir_1d_vfir(pIn, pCoeff, pOut, INPUT_SIZE, COEFF_SIZE, &pBlock[0]);

#ifndef _HOST_EMULATION    
    t1 = PROFILE_READ;
#endif

    //Call the natural C kernel
    fir_1d_vfir_cn(pIn, pCoeff, pOut_cn, INPUT_SIZE, COEFF_SIZE);

#ifndef _HOST_EMULATION 
    t2 = PROFILE_READ;

    printf("Total cycles     : Opt = %5ld,  Natc = %5ld\n", (t1 - t0), (t2 - t1));
    printf("Cycles per Input : Opt = %5.2f, Natc = %5.2f\n", (float)(t1 - t0)/INPUT_SIZE, (float)(t2 - t1)/INPUT_SIZE);
    printf("Cycles per Output: Opt = %5.2f, Natc = %5.2f\n", (float)(t1 - t0)/OUTPUT_SIZE, (float)(t2 - t1)/OUTPUT_SIZE);
#endif

    //Compare outputs 
    //ther vfir4h_vww instruction is acting weirdly waiting for a fix.

    fail = 0;
    for(ctr = 0; ctr < (INPUT_SIZE - COEFF_SIZE + 1); ctr++)
    {
        if(pOut[ctr] != pOut_cn[ctr])
        {
            printf("Mismatch at %3d, opt = %5d, natc = %5d\n", ctr, pOut[ctr], pOut_cn[ctr]);
            fail = 1;
            break;
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

