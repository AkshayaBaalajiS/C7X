/*
* module name       : c7x_matInv3x3
*
* module descripton : Does 3x3 matrix inverse
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#include "stdio.h"
#include "VXLIB_matInv_i32f_o32f.h"
#include "float.h"

//#define TRACE_ON

#ifdef TRACE_ON
#include "../../../common/printv.h"
#include <stdio.h>
#endif

#define PROFILE_READ   __TSC

#define SIMD_WIDTH (16)
/*-----------------------------------------------------------------------------*/
/* Write the SE param at offset of 0 from the base address.                    */
/*-----------------------------------------------------------------------------*/
#define SE0_PARAM_BASE (0x0000)

#define SE0_PARAM_OFFSET   (SE0_PARAM_BASE)
#define SA0_PARAM_OFFSET   (SE0_PARAM_OFFSET + SE_PARAM_SIZE)
#define VDOTP_PARAM_OFFSET (SA0_PARAM_OFFSET + SA_PARAM_SIZE)

VXLIB_STATUS VXLIB_matInv_i32f_o32f_kernel(void * restrict matAtAPtr,
                                          VXLIB_bufParams3D_t *pInMatParams,
                                          void * restrict resultPtr,
                                          VXLIB_bufParams3D_t *pOutMatParams,
                                          uint8_t * restrict valid,
                                          int32_t numMat,
                                          void * restrict pBlock)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

    int32_t              ctr;
    float16_ptr restrict    resultPtrL = stov_ptr(float16, (float *)resultPtr);
    __STRM_TEMPLATE seTemplate0;

    seTemplate0 = *stov_ptr(__STRM_TEMPLATE, (uint32_t*)((uint8_t *)pBlock + SE0_PARAM_OFFSET));
    __SE0_OPEN((void*)(matAtAPtr), seTemplate0);

    for( ctr = 0; ctr < numMat; ctr += SIMD_WIDTH ) {
        float16    a1, a2, a3, b1, b2, b3, c1, c2, c3;
        float16    d1, d2, d3, d4, d5, d6;
        float16    det, invDet;

        a1 = __SE0ADV(float16);
        a2 = __SE0ADV(float16);
        a3 = __SE0ADV(float16);

        b1 = __SE0ADV(float16); // redundant read
        b2 = __SE0ADV(float16);
        b3 = __SE0ADV(float16);

        c1 = __SE0ADV(float16); // redundant read
        c2 = __SE0ADV(float16); // redundant read
        c3 = __SE0ADV(float16);

#ifdef TRACE_ON
        PRINTV("a1",__as_long8(a1),PRINTV_FLOAT,PRINTV_HEX_OFF);
        PRINTV("a2",__as_long8(a2),PRINTV_FLOAT,PRINTV_HEX_OFF);
        PRINTV("a3",__as_long8(a3),PRINTV_FLOAT,PRINTV_HEX_OFF);
        PRINTV("b2",__as_long8(b2),PRINTV_FLOAT,PRINTV_HEX_OFF);
        PRINTV("b3",__as_long8(b3),PRINTV_FLOAT,PRINTV_HEX_OFF);
        PRINTV("c3",__as_long8(c3),PRINTV_FLOAT,PRINTV_HEX_OFF);
#endif

        /* Co-factor calculation Starts
        */
        /* Row 1 b2*c3 - b3*b3*/
        d1 = (b2 * c3) - (b3 * b3);

        /* Row 1 b3*a3 - a2*c3*/
        d2 = (b3 * a3) - (a2 * c3);

        /* Row 1 a2*b3 - b2*a3*/
        d3 = (a2 * b3) - (b2 * a3);

        /* Row 1 a1*c3 - a3*a3*/
        d4 = (a1 * c3) - (a3 * a3);

        /* Row 1 a2*a3 - a1*b3 */
        d5 = (a2 * a3) - (a1 * b3);

        /* Row 1 a1*b2 - a2*a2*/
        d6 = (a1 * b2) - (a2 * a2);

        /* Co-factor calculation Ends
        */
        det    = ((a1 * d1) + (a3 * d3)) + (a2 * d2);

#ifdef TRACE_ON
            PRINTV("det", __as_long8(det), PRINTV_FLOAT, PRINTV_HEX_OFF);
#endif

        /*
         * invDet = 1.0f/det;
         */
        invDet = __recip(det);
        invDet = invDet * ((float16)(2.0f) - (det * invDet));
        invDet = invDet * ((float16)(2.0f) - (det * invDet));

#ifdef TRACE_ON
            PRINTV("invDet", __as_long8(invDet), PRINTV_FLOAT, PRINTV_HEX_OFF);
#endif
        /*
         * if(det > FLT_EPSILON)
         *   valid[i] = 0xff;
         * else
         *   valid[i] = 0x00;
         */
        __vpred temp0 = __cmp_le_pred((float16)FLT_EPSILON,det);
        temp0         = __decimate_char(temp0, temp0);
        temp0         = __decimate_char(temp0, temp0);

        *stov_ptr(char16, (int8_t*)valid) = __as_char16(__expand(temp0).lo.lo);

        *stov_ptr(float16, (float *)resultPtrL) = invDet*d1;
        resultPtrL++;
        *stov_ptr(float16, (float *)resultPtrL) = invDet*d2;
        resultPtrL++;
        *stov_ptr(float16, (float *)resultPtrL) = invDet*d3;
        resultPtrL++;

        *stov_ptr(float16, (float *)resultPtrL) = invDet*d2;
        resultPtrL++;
        *stov_ptr(float16, (float *)resultPtrL) = invDet*d4;
        resultPtrL++;
        *stov_ptr(float16, (float *)resultPtrL) = invDet*d5;
        resultPtrL++;

        *stov_ptr(float16, (float *)resultPtrL) = invDet*d3;
        resultPtrL++;
        *stov_ptr(float16, (float *)resultPtrL) = invDet*d5;
        resultPtrL++;
        *stov_ptr(float16, (float *)resultPtrL) = invDet*d6;
        resultPtrL++;

        valid      += SIMD_WIDTH;
    }
    __SE0_CLOSE();

    return status;
}

VXLIB_STATUS VXLIB_matInv_i32f_o32f_init(void *pInMat,
                                            VXLIB_bufParams3D_t *pInMatParams,
                                            void *pOutMat,
                                            VXLIB_bufParams3D_t *pOutMatParams,
                                            uint8_t * valid,
                                            int32_t numMat,
                                            void* pBlock)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

    #if defined(VXLIB_CHECK_PARAMS) || defined(VXLIB_matInv_i32f_o32f_CHECK_PARAMS)
    status = VXLIB_matInv_i32f_o32f_checkParams(pInMat, pInMatParams, pOutMat, pOutMatParams, valid, numMat, pBlock);
    if( status == VXLIB_SUCCESS )
    #endif
    {

        __STRM_TEMPLATE seTemplate0;
        __SE_FLAGS se0_flags;

        se0_flags = __SE_FLAGS_default();
        se0_flags.DIMFMT    = __SE_DIMFMT_3D;
        se0_flags.DIR       = __SE_DIR_INC;
        se0_flags.TRANSPOSE = __SE_TRANSPOSE_OFF;
        se0_flags.ELETYPE   = __SE_ELETYPE_32BIT;
        se0_flags.PROMOTE   = __SE_PROMOTE_OFF;
        se0_flags.GRPDUP    = __SE_GRPDUP_OFF;
        se0_flags.ELEDUP    = __SE_ELEDUP_OFF;
        se0_flags.DECIM     = __SE_DECIM_OFF;
        se0_flags.DECDIM1   = __SE_DECDIM_DIM0;
        se0_flags.DECDIM2   = __SE_DECDIM_DIM0;
        se0_flags.LEZR      = __SE_LEZR_OFF;
        se0_flags.VECLEN    = __SE_VECLEN_16ELEMS;

        seTemplate0 = (uint16)(0);
        seTemplate0 = __set_ICNT0(seTemplate0, SIMD_WIDTH);
        seTemplate0 = __set_ICNT1_DIM1(seTemplate0, 9, SIMD_WIDTH);
        seTemplate0 = __set_ICNT2_DIM2(seTemplate0, (numMat + SIMD_WIDTH - 1)/SIMD_WIDTH, 9*SIMD_WIDTH);
        seTemplate0 = __set_SE_FLAGS(seTemplate0, &se0_flags, NULL);
        *stov_ptr(__STRM_TEMPLATE, (uint32_t*)((uint8_t *)pBlock + SE0_PARAM_OFFSET)) = seTemplate0;
    }

return (status);
}

VXLIB_STATUS VXLIB_matInv_i32f_o32f_checkParams(void *pInMat,
                                         VXLIB_bufParams3D_t *pInMatParams,
                                         void *pOutMat,
                                         VXLIB_bufParams3D_t *pOutMatParams,
                                         uint8_t * valid,
                                         int32_t numMat,
                                         void* pBlock)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;
    int32_t numCols = VXLIB_yByXF32(pInMatParams->dim_x, SIMD_WIDTH);
    int32_t numRows = pInMatParams->dim_y;

    if(numCols != numRows){
      status = VXLIB_ERR_FAILURE;
    }

    if(numCols*SIMD_WIDTH != pInMatParams->stride_y){
      status = VXLIB_ERR_FAILURE;
    }
    return (status);
}
