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

#include "cslr_DMC.h"
#include "cslr_UMC.h"
#include "csl_c7xecr.h"
#include "csl_c7xl2cc.h"

#ifdef __cplusplus
extern "C" {
#endif

    void CSL_c7xSetL1DCacheSize(uint64_t l1dmod)
    {
        volatile uint64_t       value;
        value = CSL_c7xGetL1DCFG() & ~CSL_DMC_L1DCFG_L1DMODE_MASK;
        value |= (l1dmod << CSL_DMC_L1DCFG_L1DMODE_SHIFT) & CSL_DMC_L1DCFG_L1DMODE_MASK;
        CSL_c7xSetL1DCFG(value);
        return;
    }

   void CSL_c7xSetL2CacheSize(uint64_t l2mod)
    {
        uint64_t       size;
        size = (l2mod << CSL_UMC_L2CFG_L2MODE_SHIFT) & CSL_UMC_L2CFG_L2MODE_MASK;
        CSL_c7xSetL2CC(size);
        return;
    }


#ifdef __cplusplus
}
#endif
