/*
* module name       : c7x_fft1d_16bit
*
* module descripton : Computes 1D FFT for 16bit samples
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#ifndef _COMMON_FFTLIB_TYPES_H_
#define _COMMON_FFTLIB_TYPES_H_ 1

#include "VXLIB_types.h"
#include "FFTLIB_bufParams.h"

#define FFTLIB_STATUS 					        	   VXLIB_STATUS
#define FFTLIB_SUCCESS 					        	   VXLIB_SUCCESS
#define FFTLIB_ERR_FAILURE    				       VXLIB_ERR_FAILURE                      /*!< Unspecified Error */
#define FFTLIB_ERR_INVALID_VALUE    	  	   VXLIB_ERR_INVALID_VALUE				        /*!< Invalid parameter value */
#define FFTLIB_ERR_INVALID_TYPE    		  	   VXLIB_ERR_INVALID_TYPE                 /*!< Invalid parameter type (VXLIB_dataType_e dataType) */
#define FFTLIB_ERR_INVALID_DIMENSION         VXLIB_ERR_INVALID_DIMENSION            /*!< Dimension parameter (width/height) is too big/small */
#define FFTLIB_ERR_NULL_POINTER    			     VXLIB_ERR_NULL_POINTER                 /*!< Unsupported null pointer condition */
#define FFTLIB_ERR_NOT_IMPLEMENTED    	   	 VXLIB_ERR_NOT_IMPLEMENTED              /*!< Parameter configuration is not supported/implemented */
#define FFTLIB_ERR_NOT_EQUAL_WIDTH_STRIDE    VXLIB_ERR_NOT_EQUAL_WIDTH_STRIDE       /*!< Stride should be equal to width * element size */
#define FFTLIB_ERR_NOT_ALIGNED_PTRS_STRIDES  VXLIB_ERR_NOT_ALIGNED_PTRS_STRIDES     /*!< Pointers and stride values are not aligned to documented value  */
#define FFTLIB_ERR_NOT_ALIGNED_WIDTHS    	   VXLIB_ERR_NOT_ALIGNED_WIDTHS           /*!< Width values are not aligned to documented value */
#define FFTLIB_ERR_BUFFER_TOO_SMALL    		   VXLIB_ERR_BUFFER_TOO_SMALL             /*!< Buffer size not large enough */
#define FFTLIB_ERROR_MAX    				         VXLIB_ERROR_MAX


#define FFTLIB_D64 VXLIB_D64
#define FFTLIB_F32 VXLIB_F32


#define FFTLIB_min VXLIB_min
#define FFTLIB_max VXLIB_max

#define VXLIB_CONVERT_POLICY_WRAP 0U        /*!< Defines overflow policy to wrap */
#define VXLIB_CONVERT_POLICY_SATURATE 1U    /*!< Defines overflow policy to saturate */


#endif /* _COMMON_FFTLIB_TYPES_H_ */

/* ======================================================================== */
/*  End of file:  FFTLIB_types.h                                             */
/* ======================================================================== */
