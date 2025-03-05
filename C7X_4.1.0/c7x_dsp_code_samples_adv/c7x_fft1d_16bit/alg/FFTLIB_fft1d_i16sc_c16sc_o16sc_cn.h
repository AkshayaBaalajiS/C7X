/*
* module name       : c7x_fft1d_16bit
*
* module descripton : Computes 1D FFT for 16bit samples
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#ifndef FFTLIB_FFT1D_I16SC_C16SC_O16SC_CN_H_
#define FFTLIB_FFT1D_I16SC_C16SC_O16SC_CN_H_ 1

#include "FFTLIB_types.h"

FFTLIB_STATUS FFTLIB_fft1d_i16sc_c16sc_o16sc_cn(int16_t * pX,
                                                FFTLIB_bufParams1D_t * bufParamsX,
                                                int16_t * pW,
                                                FFTLIB_bufParams1D_t * bufParamsW,
                                                int16_t * pY,
                                                FFTLIB_bufParams1D_t * bufParamsY,
                                                uint32_t * pShift,
                                                FFTLIB_bufParams1D_t * bufParamsShift);

FFTLIB_STATUS FFTLIB_fft1d_i16sc_c16sc_o16sc_checkParams_cn(int16_t * pX,
                                                            FFTLIB_bufParams1D_t * bufParamsX,
                                                            int16_t * pW,
                                                            FFTLIB_bufParams1D_t * bufParamsW,
                                                            int16_t * pY,
                                                            FFTLIB_bufParams1D_t * bufParamsY,
                                                            uint32_t * pShift,
                                                            FFTLIB_bufParams1D_t * bufParamsShift);

#endif /* FFTLIB_FFT1D_I16SC_C16SC_O16SC_CN_H_ */
