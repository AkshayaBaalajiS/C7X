/*
* module name       : c7x_common
*
* module descripton : Common utility functions
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/
#ifdef _HOST_EMULATION
#include <c7x_host_emulation.h>
#else
#include <c7x.h>
#endif

#include <stdio.h>

#define PARAMV_SE0 (0)
#define PARAMV_SE1 (1)

#define PARAMV_SA0 (0)
#define PARAMV_SA1 (1)
#define PARAMV_SA2 (2)
#define PARAMV_SA3 (3)

void displaySEParam(void *baseAddr, __STRM_TEMPLATE param, int32_t seNum);
void displaySAParam(void *baseAddr, __STRM_TEMPLATE param, int32_t saNum);
