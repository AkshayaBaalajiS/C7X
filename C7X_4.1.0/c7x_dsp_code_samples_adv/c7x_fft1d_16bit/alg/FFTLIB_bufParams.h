/*
* module name       : c7x_fft1d_16bit
*
* module descripton : Computes 1D FFT for 16bit samples
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#ifndef FFTLIB_BUFPARAMS_H_
#define FFTLIB_BUFPARAMS_H_

#include "VXLIB_bufParams.h"

/* ----------------------------------------------------------------
 *  MISRAC Rule 8.5 Deviation: This header file contains definitions
 *  for the following inline funtions.  These functions are shared
 *  among more than one VXLIB kernel, so it is better to have them
 *  in a common header file than to replicate the code.
 * ---------------------------------------------------------------- */
#define FFTLIB_sizeof VXLIB_sizeof


/*! \brief The enumeration of all data types. */
#define FFTLIB_dataType_e VXLIB_dataType_e

#define FFTLIB_INT8  VXLIB_INT8
#define FFTLIB_INT16 VXLIB_INT16
#define FFTLIB_INT32 VXLIB_INT32
#define FFTLIB_INT64 VXLIB_INT64

#define FFTLIB_UINT8  VXLIB_UINT8
#define FFTLIB_UINT16 VXLIB_UINT16
#define FFTLIB_UINT32 VXLIB_UINT32
#define FFTLIB_UINT64 VXLIB_UINT64

#define FFTLIB_FLOAT16  VXLIB_FLOAT16
#define FFTLIB_FLOAT32  VXLIB_FLOAT32
#define FFTLIB_FLOAT64  VXLIB_FLOAT64


/*! \brief The enumeration of multidimensional buffer types. */
#define FFTLIB_dimension_e VXLIB_dimension_e
#define FFTLIB_2D   VXLIB_2D
#define FFTLIB_3D   VXLIB_3D
#define FFTLIB_4D   VXLIB_4D
#define FFTLIB_5D   VXLIB_5D
#define FFTLIB_6D   VXLIB_6D


/*! \brief The structure of for a 2 dimensional buffer descriptor. */
#define FFTLIB_bufParams1D_t VXLIB_bufParams1D_t

/*! \brief The structure of for a 2 dimensional buffer descriptor. */
#define FFTLIB_bufParams2D_t VXLIB_bufParams2D_t

#endif /* FFTLIB_BUFPARAMS_H_ */
