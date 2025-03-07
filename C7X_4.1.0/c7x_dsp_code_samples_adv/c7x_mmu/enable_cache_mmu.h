/*
* module name       : c7x_mmu
*
* module descripton : MMU page table, cache enable operations
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#ifndef _ENABLE_CACHE_MMU_H_
#define _ENABLE_CACHE_MMU_H_

#ifdef __cplusplus

extern "C" {
#endif

#include <stdint.h>

//--------------------------------------------------------------------------------
//  Function: set_TTBR
//         Enable the Instruction Cache in SCTLR_EL1
//
//  Parameters:
//      None
//
//  Returns:
//      None
//
//--------------------------------------------------------------------------------
void enable_cache_mmu(uint64_t ttbr);


#ifdef __cplusplus
}
#endif  // extern "C"

#endif
