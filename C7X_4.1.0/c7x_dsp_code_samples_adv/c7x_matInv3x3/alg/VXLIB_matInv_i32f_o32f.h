/*
* module name       : c7x_matInv3x3
*
* module descripton : Does 3x3 matrix inverse
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#ifndef _VXLIB_matInv_i32f_o32f_H_
#define _VXLIB_matInv_i32f_o32f_H_ 1

#include "VXLIB_types.h"
#include "VXLIB_inlines.h"

#define VXLIB_matInv_i32f_o32f_PBLOCK_SIZE (256)
#ifdef __C7X_HOSTEM__
#define restrict
#endif

#define STATIC_INPUT
//#define ERROR_REPORT

VXLIB_STATUS VXLIB_matInv_i32f_o32f_init(void * restrict pInMat,
                                         VXLIB_bufParams3D_t *pInMatParams,
                                         void * restrict pOutMat,
                                         VXLIB_bufParams3D_t *pOutMatParams,
                                         uint8_t * restrict valid,
                                         int32_t numMat,
                                         void * restrict pBlock);

VXLIB_STATUS VXLIB_matInv_i32f_o32f_kernel(void * restrict pInMat,
    VXLIB_bufParams3D_t *pInMatParams,
    void * restrict pOutMat,
    VXLIB_bufParams3D_t *pOutMatParams,
    uint8_t * restrict valid,
    int32_t numMat,
    void * restrict pBlock);

VXLIB_STATUS VXLIB_matInv_i32f_o32f_checkParams(void * restrict pInMat,
    VXLIB_bufParams3D_t *pInMatParams,
    void * restrict pOutMat,
    VXLIB_bufParams3D_t *pOutMatParams,
    uint8_t * restrict valid,
    int32_t numMat,
    void * restrict pBlock);
#endif /* _VXLIB_matInv_i32f_o32f_H_ */
