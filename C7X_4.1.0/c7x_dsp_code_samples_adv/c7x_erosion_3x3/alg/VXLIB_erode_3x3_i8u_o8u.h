/*
* module name       : c7x_erosion_3x3
*
* module descripton : 3x3 greyscale erosion
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#ifndef VXLIB_ERODE_3X3_I8U_O8U_H_
#define VXLIB_ERODE_3X3_I8U_O8U_H_ 1

#include "VXLIB_types.h"

#define VXLIB_ERODE_3X3_I8U_O8U_PBLOCK_SIZE (256)

VXLIB_STATUS VXLIB_erode_3x3_i8u_o8u_init(void *src,
                                          VXLIB_bufParams2D_t *src_addr,
                                          void *dst,
                                          VXLIB_bufParams2D_t *dst_addr,
                                          void *pBlock);

VXLIB_STATUS VXLIB_erode_3x3_i8u_o8u_kernel(void *src,
                                            VXLIB_bufParams2D_t *src_addr,
                                            void *dst,
                                            VXLIB_bufParams2D_t *dst_addr,
                                            void *pBlock);

VXLIB_STATUS VXLIB_erode_3x3_i8u_o8u_checkParams(void *src,
                                                 VXLIB_bufParams2D_t *src_addr,
                                                 void *dst,
                                                 VXLIB_bufParams2D_t *dst_addr,
                                                 void *pBlock);
#endif /* VXLIB_ERODE_3X3_I8U_O8U_H_ */
