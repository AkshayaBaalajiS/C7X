/*
* module name       : c7x_common
*
* module descripton : Common utility functions
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#ifndef _COMMON_VXLIB_TYPES_H_
#define _COMMON_VXLIB_TYPES_H_ 1

/* This header is needed to be included in OpenCL programs which link
 * against VXLIB, but OpenCL doesn't need the following headers */
#ifndef __OPENCL_VERSION__
#include <stdlib.h>
#include <stdint.h>
#include "VXLIB_bufParams.h"
#endif

typedef double VXLIB_D64;          /*!< Double precision floating point */
typedef float VXLIB_F32;           /*!< Single precision floating point */

/*! \brief The enumeration of all status codes. */
typedef enum {
    VXLIB_SUCCESS = 0,                          /*!< No Error */
    VXLIB_ERR_FAILURE = 1,                      /*!< Unspecified Error */
    VXLIB_ERR_INVALID_VALUE = 2,                /*!< Invalid parameter value */
    VXLIB_ERR_INVALID_TYPE = 3,                 /*!< Invalid parameter type (VXLIB_data_type_e data_type) */
    VXLIB_ERR_INVALID_DIMENSION = 4,            /*!< Dimension parameter (width/height) is too big/small */
    VXLIB_ERR_NULL_POINTER = 5,                 /*!< Unsupported null pointer condition */
    VXLIB_ERR_NOT_IMPLEMENTED = 6,              /*!< Parameter configuration is not supported/implemented */
    VXLIB_ERR_NOT_EQUAL_WIDTH_STRIDE = 7,       /*!< Stride should be equal to width * element size */
    VXLIB_ERR_NOT_ALIGNED_PTRS_STRIDES = 8,     /*!< Pointers and stride values are not aligned to documented value  */
    VXLIB_ERR_NOT_ALIGNED_WIDTHS = 9,           /*!< Width values are not aligned to documented value */
    VXLIB_ERR_BUFFER_TOO_SMALL = 10,            /*!< Buffer size not large enough */
    VXLIB_ERROR_MAX = 11
} VXLIB_STATUS_NAME;

typedef VXLIB_STATUS_NAME VXLIB_STATUS;    /*!< return value for all VXLIB functions */

#define VXLIB_min(x, y) (((x) < (y)) ? (x) : (y)) /*!< A macro to return the minimum of 2 values. */
#define VXLIB_max(x, y) (((x) < (y)) ? (y) : (x)) /*!< A macro to return the maximum of 2 values. */

#define VXLIB_CONVERT_POLICY_WRAP 0U        /*!< Defines overflow policy to wrap */
#define VXLIB_CONVERT_POLICY_SATURATE 1U    /*!< Defines overflow policy to saturate */

#define VXLIB_INTERPOLATION_TYPE_NEAREST_NEIGHBOR 0U    /*!< Defines interpolation type to nearest neighbor interpolation */
#define VXLIB_INTERPOLATION_TYPE_BILINEAR 1U            /*!< Defines interpolation type to bilinear interpolation */
#define VXLIB_INTERPOLATION_TYPE_AREA 2U                /*!< Defines interpolation type to area interpolation */


#define VXLIB_COLOR_SPACE_NONE 0x0          /*!< Defines no specific color space */
#define VXLIB_COLOR_SPACE_BT601_525 0x1     /*!< Defines BT601_525 color space */
#define VXLIB_COLOR_SPACE_BT601_625 0x2     /*!< Defines BT601_625 color space */
#define VXLIB_COLOR_SPACE_BT709 0x3         /*!< Defines BT709 color space */
#define VXLIB_COLOR_SPACE_DEFAULT 0x3       /*!< Defines default color space */

#define VXLIB_TERM_ITERATIONS 0U    /*!< Defines termination criteria as number of iterations */
#define VXLIB_TERM_EPSILON 1U       /*!< Defines termination criteria as epsilon */
#define VXLIB_TERM_BOTH 2U          /*!< Defines termination criteria as the earlier of number of iterations or epsilon */

#endif /* _COMMON_VXLIB_TYPES_H_ */

/* ======================================================================== */
/*  End of file:  VXLIB_types.h                                             */
/* ======================================================================== */
