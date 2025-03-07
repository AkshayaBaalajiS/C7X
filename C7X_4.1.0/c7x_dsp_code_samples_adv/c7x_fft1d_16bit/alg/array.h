/*
* module name       : c7x_fft1d_16bit
*
* module descripton : Computes 1D FFT for 16bit samples
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#include <stdint.h>

typedef struct {
    int16_t *staticIn0;
    uint32_t *shiftVector;
    int16_t *staticOut;
    int16_t *twiddleFactors;
    uint32_t numShifts;
    uint32_t numPoints;
} fft1d_i16sc_c16sc_o16sc_testParams_t;

void fft1d_i16sc_c16sc_o16sc_getTestParams(fft1d_i16sc_c16sc_o16sc_testParams_t * *params, int32_t *numTests);

#define ALIGN_128BYTES __attribute__((aligned(128)))

#define MAX_NUMPOINTS 16384
