/*
* module name       : c7x_nms
*
* module descripton : Computes 7x7 window Non Maximum Suppression
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
#endif

    result = test_main(&profile[0]);

    if(result == 1)
      printf("Test Pass!\n");
    else
      printf("Test Fail!\n");

#ifndef _HOST_EMULATION
    printf("CPU Cycles : %8d \n", profile[0]);
#endif

    return (0);
}
