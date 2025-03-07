/*
* module name       : c7x_mmu
*
* module descripton : MMU page table, cache enable operations
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/
#ifndef CSL_C7XL2CC_H_
#define CSL_C7XL2CC_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void     CSL_c7xSetL2CC(uint64_t param);
uint64_t CSL_c7xGetL2CC(void);

#ifdef __cplusplus
}
#endif

#endif             /* end of CSL_C7XECR_H_ definition */
