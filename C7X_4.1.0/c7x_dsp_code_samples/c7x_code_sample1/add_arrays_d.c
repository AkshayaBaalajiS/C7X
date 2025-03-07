/*
* module name       : c7x_sample1
*
* module descripton : Addition of two array using C7x vector types
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#include <add_arrays.h>

#define ARRAY_SIZE  (96)

#ifndef _HOST_EMULATION
int64_t t0,t1,t2;
#endif

int main(int argc, char **argv)
{
    int16_t *pInA, *pInB;
    int16_t *pOutC, *pOutC_cn;
    int32_t ctr, fail;

    //Allocate input memory
    pInA = (int16_t *)malloc(ARRAY_SIZE * sizeof(int16_t));

    if(pInA == NULL)
    {
        printf("Unable to allocate input memory!\n");
        return 0;
    }

    pInB = (int16_t *)malloc(ARRAY_SIZE * sizeof(int16_t));

    if(pInB == NULL)
    {
        printf("Unable to allocate input memory!\n");
        return 0;
    }

    //Allocate output memory for optimized code
    pOutC = (int16_t *)malloc(ARRAY_SIZE * sizeof(int16_t));

    if(pOutC == NULL)
    {
        printf("Unable to allocate output memory!\n");
        return 0;
    }

    //Allocate output memory for natural C code
    pOutC_cn = (int16_t *)malloc(ARRAY_SIZE * sizeof(int16_t));

    if(pOutC_cn == NULL)
    {
        printf("Unable to allocate output memory!\n");
        return 0;
    }

    //Initialize input memory
    for(ctr = 0; ctr < ARRAY_SIZE; ctr++)
    {
       pInA[ctr] = ctr;
       pInB[ctr] = ctr;
    }

    //Clear the output memories
    memset(pOutC, 0, ARRAY_SIZE * sizeof(int16_t));
    memset(pOutC_cn, 0, ARRAY_SIZE * sizeof(int16_t));

#ifndef _HOST_EMULATION
    t0 = PROFILE_READ;
#endif

    //Call the optimized kernel
    addArrays(pInA, pInB, pOutC, ARRAY_SIZE);

#ifndef _HOST_EMULATION
    t1 = PROFILE_READ;
#endif

    //Call the natural C kernel
    addArrays_cn(pInA, pInB, pOutC_cn, ARRAY_SIZE);

#ifndef _HOST_EMULATION
    t2 = PROFILE_READ;

    printf("Total cycles     : Opt = %5ld, Natc = %5ld\n", (t1 - t0), (t2 - t1));
    printf("Cycles per Input : Opt = %5.2f, Natc = %5.2f\n", (float)(t1 - t0)/ARRAY_SIZE, (float)(t2 - t1)/ARRAY_SIZE);
    printf("Cycles per Input : Opt = %5.2f, Natc = %5.2f\n", (float)(t1 - t0)/ARRAY_SIZE, (float)(t2 - t1)/ARRAY_SIZE);
#endif

    //Compare outputs
    fail = 0;
    for(ctr = 0; ctr < ARRAY_SIZE; ctr++)
    {
        if(pOutC[ctr] != pOutC_cn[ctr])
        {
            printf("Mismatch at %3d, opt = %5d, natc = %5d\n", ctr, pOutC[ctr], pOutC_cn[ctr]);
            fail = 1;
        }
    }

    //Report results
    if(fail)
       printf("Test Failed!\n");
    else
       printf("Test Pass!\n");

    //Free memories
    free(pOutC_cn);
    free(pOutC);
    free(pInB);
    free(pInA);

    return 0;
}
