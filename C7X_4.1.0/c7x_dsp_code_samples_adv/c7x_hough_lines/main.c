/*
* module name       : c7x_hough_lines
*
* module descripton : Computes Hough Lines
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef _HOST_EMULATION
#include "c7x_host_emulation.h"
#else
#include <c7x.h>
#include "enable_cache_mmu.h"
#include "csl_dspcachec7.h"
#endif

#pragma DATA_SECTION(profile, ".profile")
uint32_t profile[8];

extern const uint64_t pte_lvl0[512];

int test_main(uint32_t *pProfile);

int main()
{
    int32_t result;

#ifndef _HOST_EMULATION
    enable_cache_mmu((uint64_t)pte_lvl0);

    /* Configure L1D as 16KB cache and 32KB SRAM */
    CSL_c7xSetL1DCacheSize(3);
#endif

    result = test_main(&profile[0]);

    if(result == 1)
      printf("Test Pass!\n");
    else
      printf("Test Fail!\n");

#ifndef _HOST_EMULATION
    printf("Cycles - Run1: %8d \n", profile[0]);

    /* Configure L1D as 32KB cache and 16KB SRAM */
    CSL_c7xSetL1DCacheSize(4);
#endif

    return (0);

}
