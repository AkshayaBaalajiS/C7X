/*
* module name       : c7x_common
*
* module descripton : Common utility functions
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/
#ifndef MEMORY_H_
#define MEMORY_H_ 1

#include "VXLIB_types.h"

#define QC512_SIZE (64)

#define MEMORY_ELEM_8BIT  (1)
#define MEMORY_ELEM_16BIT (2)
#define MEMORY_ELEM_32BIT (4)

#define MEMORY_BANK0 (0)
#define MEMORY_BANK1 (1)
#define MEMORY_BANK2 (2)
#define MEMORY_BANK3 (3)

#define BANK_PADDING (512)

#ifdef __cplusplus
extern "C" {
#endif

void fillRandFast(void *array, int32_t size, uint8_t elementSize, uint32_t wrapVal);
void qc512(uint8_t* out, const uint8_t* in, size_t inlen);
void memsetFast(void *array, uint32_t value, int32_t size, uint8_t elementSize);
void * alignAddress(void *pBase, int32_t bank_opt);

#ifdef __cplusplus
}
#endif

#endif
