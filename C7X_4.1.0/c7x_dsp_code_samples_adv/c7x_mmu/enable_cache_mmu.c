/*
* module name       : c7x_mmu
*
* module descripton : MMU page table, cache enable operations
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#include <stdint.h>
#include "csl_c7xecr.h"

void enable_cache_mmu(uint64_t ttbr)
{

    uint64_t          tcr;
    uint64_t          mar;
    uint64_t          scr;

    tcr = 0x0000000000002a21U;
    scr = 0x80000000000000c1U;
    mar = 0x3D3D3D2915032A00U;

    CSL_c7xSetTCR0(tcr);    //ECR785
    CSL_c7xSetTBR0(ttbr);   //ECR787
    CSL_c7xSetMAR(mar);     //ECR789
    CSL_c7xSetSCR(scr);     //ECR784  *** This register has to be last ***

}
