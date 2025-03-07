/*
* module name       : c7x_fft1d_16bit
*
* module descripton : Computes 1D FFT for 16bit samples
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#include "FFTLIB_fft1d_i16sc_c16sc_o16sc.h"

#define TRACE_ON   (0)

#if TRACE_ON
#include "../../../common/printv.h"
#include <stdio.h>
#endif

#define SE_PARAM_BASE    (0x0000)
#define SE_LOOP1_PARAM_OFFSET (SE_PARAM_BASE)
#define SE_LOOP2_PARAM_OFFSET (SE_LOOP1_PARAM_OFFSET + SE_PARAM_SIZE)
#define SE_LOOP3_PARAM_OFFSET (SE_LOOP2_PARAM_OFFSET + SE_PARAM_SIZE)
#define SE_LOOP4_PARAM_OFFSET (SE_LOOP3_PARAM_OFFSET + SE_PARAM_SIZE)
#define SE_LOOP5_PARAM_OFFSET (SE_LOOP4_PARAM_OFFSET + SE_PARAM_SIZE)
#define SE_TWID_PARAM_OFFSET  (SE_LOOP5_PARAM_OFFSET + SE_PARAM_SIZE)
#define SA_LOOP1_PARAM_OFFSET (SE_TWID_PARAM_OFFSET + SE_PARAM_SIZE)
#define SA_LOOP2_PARAM_OFFSET (SA_LOOP1_PARAM_OFFSET + SA_PARAM_SIZE)
#define SA_LOOP3_PARAM_OFFSET (SA_LOOP2_PARAM_OFFSET + SA_PARAM_SIZE)

FFTLIB_STATUS FFTLIB_fft1d_i16sc_c16sc_o16sc_init(int16_t * pX,
                                                  FFTLIB_bufParams1D_t * bufParamsX,
                                                  int16_t * pW,
                                                  FFTLIB_bufParams1D_t * bufParamsW,
                                                  int16_t * pY,
                                                  FFTLIB_bufParams1D_t * bufParamsY,
                                                  uint32_t * pShift,
                                                  FFTLIB_bufParams1D_t * bufParamsShift,
                                                  void *pBlock)
{
    FFTLIB_STATUS    status = FFTLIB_SUCCESS;

#if defined(FFTLIB_CHECK_PARAMS) || defined(FFTLIB_FFT1D_I16SC_C16SC_O16SC_CHECK_PARAMS)
    status = FFTLIB_fft1d_i16sc_c16sc_o16sc_checkParams(pX, bufParamsX,
                                                        pW, bufParamsW,
                                                        pY, bufParamsY,
                                                        pShift, bufParamsShift,
                                                        pBlock);
    if( status == FFTLIB_SUCCESS )
#endif
    {
        uint32_t numPoints;
        uint32_t numPointsPerDft;
        uint32_t seCnt1, seCnt2, seCnt3, seCnt4;
        __SE_FLAGS se0_flags;
        __SE_FLAGS se1_flags;
        __SA_FLAGS sa0_flags;
        __STRM_TEMPLATE se0_param;
        __STRM_TEMPLATE se1_param;
        __STRM_TEMPLATE sa0_param;

        numPoints = bufParamsX->dim_x >> 1;
        numPointsPerDft = numPoints;
        seCnt1 = numPoints >> 2;
        seCnt2 = numPoints >> 6;
        seCnt3 = 1;
        seCnt4 = numPoints >> 4;

        se0_param = (__STRM_TEMPLATE)(0);
        se0_param = __set_ICNT0(se0_param, 16);     /* 16-point vectors processed in one shot */
        se0_param = __set_ICNT1_DIM1(se0_param, 4,  /* 4 quarters(Offsets: 0, N/4, N/2, 3N/4) */
                                     seCnt1);
        se0_param = __set_ICNT2_DIM2(se0_param,     /* Number of 8-point fetches within each  */
                                     seCnt2,        /* quarter                                */
                               16);
        se0_param = __set_ICNT3_DIM3(se0_param,     /* Number of DFT's  */
                                     seCnt3,
                                     numPointsPerDft);

        se0_flags           = __SE_FLAGS_default();
        se0_flags.ELETYPE   = __SE_ELETYPE_16BIT_CMPLX_SWAP;
        se0_flags.VECLEN    = __SE_VECLEN_16ELEMS;
        se0_flags.DIMFMT    = __SE_DIMFMT_4D;
        se0_param = __set_SE_FLAGS(se0_param, &se0_flags, NULL);
        *stov_ptr(uint16, (uint32_t *)((uint8_t *)pBlock + SE_LOOP1_PARAM_OFFSET)) = se0_param;

        se1_param = (__STRM_TEMPLATE)(0);
        se1_param = __set_ICNT0(se1_param, 16);     /* 16-point vectors processed in one shot */
        se1_param = __set_ICNT1_DIM1(se1_param, 3,  /* Twiddle factors for x1, x2 and x3      */
                                     seCnt1);
        se1_param = __set_ICNT2_DIM2(se1_param,     /* Number of 8-point fetches within each  */
                                     seCnt2,        /* quarter                                */
                                     16);
        se1_param = __set_ICNT3_DIM3(se1_param,     /* Number of DFT's                        */
                                     seCnt3,
                                     0);

        se1_flags           = __SE_FLAGS_default();
        se1_flags.ELETYPE   = __SE_ELETYPE_16BIT_CMPLX_SWAP;
        se1_flags.VECLEN    = __SE_VECLEN_16ELEMS;
        se1_flags.DIMFMT    = __SE_DIMFMT_4D;
        se1_param = __set_SE_FLAGS(se1_param, &se1_flags, NULL);
        *stov_ptr(uint16, (uint32_t *)((uint8_t *)pBlock + SE_TWID_PARAM_OFFSET)) = se1_param;

        sa0_param = (__STRM_TEMPLATE)(0);
        sa0_param = __set_ICNT0(sa0_param, 16);
        sa0_param = __set_ICNT1_DIM1(sa0_param, 4,  /* Save to each of the 4 quarters         */
                                     seCnt1);
        sa0_param = __set_ICNT2_DIM2(sa0_param,     /* Number of 8-point stores within each   */
                                     seCnt2,        /* quarter                                */
                                     16);
        sa0_param = __set_ICNT3_DIM3(sa0_param,
                                     seCnt3,              /* Number of DFT's                        */
                                     numPointsPerDft);

        sa0_flags           = __SA_FLAGS_default();
        sa0_flags.VECLEN    = __SA_VECLEN_16ELEMS;
        sa0_flags.DIMFMT    = __SA_DIMFMT_4D;
        sa0_param = __set_SA_FLAGS(sa0_param, &sa0_flags);
        *stov_ptr(uint16, (uint32_t *)((uint8_t *)pBlock + SA_LOOP1_PARAM_OFFSET)) = sa0_param;

        se0_param = (__STRM_TEMPLATE)(0);
        se0_param = __set_ICNT0(se0_param, 16);
        se0_param = __set_ICNT1_DIM1(se0_param, 4,  /* Process four 16-point DFTs in one shot */
                                     16);
        se0_param = __set_ICNT2_DIM2(se0_param,
                                     seCnt2, 64);   /* One-fourth the the number of DFT's     */

        se0_flags           = __SE_FLAGS_default();
        se0_flags.ELETYPE   = __SE_ELETYPE_16BIT_CMPLX_SWAP;
        se0_flags.TRANSPOSE = __SE_TRANSPOSE_128BIT;
        se0_flags.VECLEN    = __SE_VECLEN_16ELEMS;
        se0_flags.DIMFMT    = __SE_DIMFMT_3D;
        se0_param = __set_SE_FLAGS(se0_param, &se0_flags, NULL);
        *stov_ptr(uint16, (uint32_t *)((uint8_t *)pBlock + SE_LOOP2_PARAM_OFFSET)) = se0_param;

        sa0_param = (__STRM_TEMPLATE)(0);
        sa0_param = __set_ICNT0(sa0_param,
                               numPoints);

        sa0_flags           = __SA_FLAGS_default();
        sa0_flags.VECLEN    = __SA_VECLEN_16ELEMS;
        sa0_flags.DIMFMT    = __SA_DIMFMT_1D;
        sa0_param = __set_SA_FLAGS(sa0_param, &sa0_flags);
        *stov_ptr(uint16, (uint32_t *)((uint8_t *)pBlock + SA_LOOP2_PARAM_OFFSET)) = sa0_param;

        se0_param = (__STRM_TEMPLATE)(0);
        se0_param = __set_ICNT0(se0_param, 32);
        se0_param = __set_ICNT1_DIM1(se0_param, 2, 32);   /* Process two 16-point DFTs in one shot */
        se0_param = __set_ICNT2_DIM2(se0_param,
                               seCnt2, 64);

        se0_flags           = __SE_FLAGS_default();
        se0_flags.ELETYPE   = __SE_ELETYPE_16BIT_CMPLX_SWAP;
        se0_flags.TRANSPOSE = __SE_TRANSPOSE_256BIT;/* Using 256BIT transpose required  */
                                                    /* 16-byte alignment on pX          */
        se0_flags.VECLEN    = __SE_VECLEN_16ELEMS;
        se0_flags.DIMFMT    = __SE_DIMFMT_3D;
        se0_param = __set_SE_FLAGS(se0_param, &se0_flags, NULL);
        *stov_ptr(uint16, (uint32_t *)((uint8_t *)pBlock + SE_LOOP3_PARAM_OFFSET)) = se0_param;

        sa0_param = (__STRM_TEMPLATE)(0);
        sa0_param = __set_ICNT0(sa0_param,
                                numPoints);

        sa0_flags           = __SA_FLAGS_default();
        sa0_flags.VECLEN    = __SA_VECLEN_16ELEMS;
        sa0_flags.DIMFMT    = __SA_DIMFMT_1D;
        sa0_param = __set_SA_FLAGS(sa0_param, &sa0_flags);
        *stov_ptr(uint16, (uint32_t *)((uint8_t *)pBlock + SA_LOOP3_PARAM_OFFSET)) = sa0_param;

        se0_param = (__STRM_TEMPLATE)(0);
        se0_param = __set_ICNT0(se0_param, seCnt4);
        se0_param = __set_ICNT1_DIM1(se0_param, 16, /* Fetch 16 points separated by           */
                                     seCnt4);       /* (numPoints >> 4). This fetch pattern   */
                                                    /* can be used for bit reversal           */

        se0_flags           = __SE_FLAGS_default();
        se0_flags.ELETYPE   = __SE_ELETYPE_16BIT_CMPLX_SWAP;
        se0_flags.TRANSPOSE = __SE_TRANSPOSE_32BIT;
        se0_flags.VECLEN    = __SE_VECLEN_16ELEMS;
        se0_flags.DIMFMT    = __SE_DIMFMT_2D;
        se0_param = __set_SE_FLAGS(se0_param, &se0_flags, NULL);
        *stov_ptr(uint16, (uint32_t *)((uint8_t *)pBlock + SE_LOOP4_PARAM_OFFSET)) = se0_param;

        se0_param = (__STRM_TEMPLATE)(0);
        se0_param = __set_ICNT0(se0_param, seCnt4);
        se0_param = __set_ICNT1_DIM1(se0_param, 16, /* Fetch 16 points separated by           */
                                     seCnt4);       /* (numPoints >> 4). This fetch pattern   */
                                                    /* can be used for bit reversal           */

        se0_flags           = __SE_FLAGS_default();
        se0_flags.ELETYPE   = __SE_ELETYPE_16BIT_CMPLX_SWAP;
        se0_flags.TRANSPOSE = __SE_TRANSPOSE_32BIT;
        se0_flags.VECLEN    = __SE_VECLEN_16ELEMS;
        se0_flags.DIMFMT    = __SE_DIMFMT_2D;
        se0_param = __set_SE_FLAGS(se0_param, &se0_flags, NULL);
        *stov_ptr(uint16, (uint32_t *)((uint8_t *)pBlock + SE_LOOP5_PARAM_OFFSET)) = se0_param;
    }
    return (status);
}

FFTLIB_STATUS FFTLIB_fft1d_i16sc_c16sc_o16sc_kernel(int16_t * pX,
                                                    FFTLIB_bufParams1D_t * bufParamsX,
                                                    int16_t * pW,
                                                    FFTLIB_bufParams1D_t * bufParamsW,
                                                    int16_t * pY,
                                                    FFTLIB_bufParams1D_t * bufParamsY,
                                                    uint32_t * pShift,
                                                    FFTLIB_bufParams1D_t * bufParamsShift,
                                                    void *pBlock)
{
    uint32_t k;
    FFTLIB_STATUS    status = FFTLIB_SUCCESS;
    uint32_t numPoints;
    uint32_t numPointsPerDft;
    uint32_t numLeadingZeros;
    uint32_t offsetBitReverse;
    uint32_t seCnt1, seCnt2, seCnt3;
    __STRM_TEMPLATE se0_param;
    __STRM_TEMPLATE se1_param;
    __STRM_TEMPLATE sa0_param;
    cshort_ptr pXLocal;
    cshort_ptr pYLocal;
    cshort_ptr pWLocal;
    cshort_ptr pY0;
    cshort_ptr pY1;
    cshort_ptr pY2;
    cshort_ptr pY3;
    cshort_ptr pY4;
    cshort_ptr pY5;
    cshort_ptr pY6;
    cshort_ptr pY7;
    cshort16 vX_0, vX_N_4, vX_N_2, vX_3N_4;
    cshort16 vSum1, vSum2, vDiff1, vDiff2;
    cshort16 vTwX1, vTwX2, vTwX3;
    cshort16 vX0Temp, vX1Temp, vX2Temp, vX3Temp;
    cshort16 vX0, vX1, vX2, vX3;
    cshort16 vX_0_1, vX_N_4_1, vX_N_2_1, vX_3N_4_1;
    cshort16 vSum1_1, vSum2_1, vDiff1_1, vDiff2_1;
    cshort16 vX0_1, vX1_1, vX2_1, vX3_1;
    cshort16 vX0_2PtDft_1, vX0_2PtDft_2;
    cshort16 vX1_2PtDft_1, vX1_2PtDft_2;
    cshort16 vX2_2PtDft_1, vX2_2PtDft_2;
    cshort16 vX3_2PtDft_1, vX3_2PtDft_2;
    cshort twTemp;
    uint32_t stageIndex;
    uint16 vShift;

#ifdef FFTLIB_CHECK_PARAMS
    status = FFTLIB_fft1d_i16sc_c16sc_o16sc_checkParams(pX, bufParamsX,
                                                        pW, bufParamsW,
                                                        pY, bufParamsY,
                                                        pShift, bufParamsShift,
                                                        pBlock);
    if( status == FFTLIB_SUCCESS )
#endif
    {
        numPoints = bufParamsX->dim_x >> 1;
        numPointsPerDft = numPoints;
        stageIndex = 0;

        se0_param =  *stov_ptr(uint16, (uint32_t *)((uint8_t *)pBlock + SE_LOOP1_PARAM_OFFSET));
        se1_param =  *stov_ptr(uint16, (uint32_t *)((uint8_t *)pBlock + SE_TWID_PARAM_OFFSET));
        sa0_param =  *stov_ptr(uint16, (uint32_t *)((uint8_t *)pBlock + SA_LOOP1_PARAM_OFFSET));
        seCnt1 = numPointsPerDft >> 2;
        seCnt2 = numPointsPerDft >> 6;
        seCnt3 = 1;

        pXLocal = (cshort *)(pX);
        pWLocal = (cshort *)(pW);
        pYLocal = (cshort *)(pY);

        while (numPointsPerDft >= 64) {
            se0_param = __set_ICNT1_DIM1(se0_param,
                                         4,         /* 4 quarters(Offsets: 0, N/4, N/2, 3N/4) */
                                         seCnt1);
            se0_param = __set_ICNT2_DIM2(se0_param,
                                         seCnt2,    /* Number of 8-point fetches within       */
                                         16);       /* each quarter                           */
            se0_param = __set_ICNT3_DIM3(se0_param,
                                         seCnt3,    /* Number of DFT's                        */
                                         numPointsPerDft);
            __SE0_OPEN((void *)pXLocal, se0_param);

            se1_param = __set_ICNT1_DIM1(se1_param, /* Twiddle factors for x1, x2 and x3      */
                                         3,
                                         seCnt1);
            se1_param = __set_ICNT2_DIM2(se1_param, /* Number of 8-point fetches within each  */
                                         seCnt2,    /* quarter                                */
                                         16);
            se1_param = __set_ICNT3_DIM3(se1_param, /* Number of DFT's                        */
                                         seCnt3,
                                         0);
            __SE1_OPEN((void *)pWLocal, se1_param);

            sa0_param = __set_ICNT1_DIM1(sa0_param, 4,/* Save to each of the 4 quarters         */
                                         seCnt1);
            sa0_param = __set_ICNT2_DIM2(sa0_param,
                                         seCnt2,    /* Number of 8-point stores within        */
                                                    /* each quarter                           */
                                         16);
            sa0_param = __set_ICNT3_DIM3(sa0_param,
                                         seCnt3,    /* Number of DFT's                        */
                                         numPointsPerDft);
            __SA0_OPEN(sa0_param);

            /* Obtain the right shift value for the current stage */
            vShift = __vload_dup((uint32_t *)(pShift+stageIndex));

            for (k = 0; k < numPoints; k += 64) {

                vX_0    = __SE0ADV(cshort16);
                vX_N_4  = __SE0ADV(cshort16);
                vX_N_2  = __SE0ADV(cshort16);
                vX_3N_4 = __SE0ADV(cshort16);

                vSum1   = vX_0 + vX_N_2;
                vSum2   = vX_N_4 + vX_3N_4;
                vDiff1  = vX_0 - vX_N_2;
                vDiff2  = vX_N_4 - vX_3N_4;

                vTwX1 = __SE1ADV(cshort16);
                vTwX2 = __SE1ADV(cshort16);
                vTwX3 = __SE1ADV(cshort16);

                vX0Temp = vSum1 + vSum2;
                vX1Temp = vDiff1 - __vcrot90h_vv(vDiff2);
                vX2Temp = vSum1 - vSum2;
                vX3Temp = vDiff1 + __vcrot90h_vv(vDiff2);

                vX0 = vX0Temp;
                vX1 = __cmpy_fx(vX1Temp, vTwX1);
                vX2 = __cmpy_fx(vX2Temp, vTwX2);
                vX3 = __cmpy_fx(vX3Temp, vTwX3);

                *__SA0ADV(cshort16, pXLocal) = __as_cshort16(__shift_right_round(__as_short32(vX0), vShift));
                *__SA0ADV(cshort16, pXLocal) = __as_cshort16(__shift_right_round(__as_short32(vX2), vShift));
                *__SA0ADV(cshort16, pXLocal) = __as_cshort16(__shift_right_round(__as_short32(vX1), vShift));
                *__SA0ADV(cshort16, pXLocal) = __as_cshort16(__shift_right_round(__as_short32(vX3), vShift));
            }
            __SA0_CLOSE();
            __SE0_CLOSE();
            __SE1_CLOSE();

            numPointsPerDft >>= 2;
            pWLocal += numPointsPerDft*3;
            seCnt1 >>= 2;
            seCnt2 >>= 2;
            seCnt3 <<= 2;
            stageIndex++;
        }

        vShift = __vload_dup((uint32_t *)(pShift+stageIndex));
        if (numPointsPerDft == 16)
        {
            uchar64 vXPermCtrl  = (uchar64)(0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                                            0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
                                            0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
                                            0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F,
                                            0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
                                            0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F,
                                            0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
                                            0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F);
            uchar64 vX0X2_01, vX1X3_01, vX0X2_23, vX1X3_23;
            uchar64 vXPermOut;
            cshort4 vTwX1CShort4, vTwX2CShort4, vTwX3CShort4;
            cshort8 vTwX1CShort8, vTwX2CShort8, vTwX3CShort8;

            se0_param =  *stov_ptr(uint16, (uint32_t *)((uint8_t *)pBlock + SE_LOOP2_PARAM_OFFSET));
            __SE0_OPEN((void *)pXLocal, se0_param);

            sa0_param =  *stov_ptr(uint16, (uint32_t *)((uint8_t *)pBlock + SA_LOOP2_PARAM_OFFSET));
            __SA0_OPEN(sa0_param);

            vTwX1CShort4 = *((cshort4 *)pWLocal);
            vTwX1CShort8 = (cshort8)(vTwX1CShort4, vTwX1CShort4);
            vTwX1 = (cshort16)(vTwX1CShort8, vTwX1CShort8);

            vTwX2CShort4 = *((cshort4 *)(pWLocal+4));
            vTwX2CShort8 = (cshort8)(vTwX2CShort4, vTwX2CShort4);
            vTwX2 = (cshort16)(vTwX2CShort8, vTwX2CShort8);

            vTwX3CShort4 = *((cshort4 *)(pWLocal+8));
            vTwX3CShort8 = (cshort8)(vTwX3CShort4, vTwX3CShort4);
            vTwX3 = (cshort16)(vTwX3CShort8, vTwX3CShort8);

            for (k = 0; k < numPoints; k += 64)
            {
                vX_0    = __SE0ADV(cshort16);
                vX_N_4  = __SE0ADV(cshort16);
                vX_N_2  = __SE0ADV(cshort16);
                vX_3N_4 = __SE0ADV(cshort16);

                vSum1   = vX_0 + vX_N_2;
                vSum2   = vX_N_4 + vX_3N_4;
                vDiff1  = vX_0 - vX_N_2;
                vDiff2  = vX_N_4 - vX_3N_4;

                vX0Temp = vSum1 + vSum2;
                vX1Temp = vDiff1 - __vcrot90h_vv(vDiff2);
                vX2Temp = vSum1 - vSum2;
                vX3Temp = vDiff1 + __vcrot90h_vv(vDiff2);

                vX0 = vX0Temp;
                vX1 = __cmpy_fx(vX1Temp, vTwX1);
                vX2 = __cmpy_fx(vX2Temp, vTwX2);
                vX3 = __cmpy_fx(vX3Temp, vTwX3);

                vX0X2_01 = (uchar64)(__as_uchar64(vX0).lo, __as_uchar64(vX2).lo);
                vX1X3_01 = (uchar64)(__as_uchar64(vX1).lo, __as_uchar64(vX3).lo);
                vX0X2_23 = (uchar64)(__as_uchar64(vX0).hi, __as_uchar64(vX2).hi);
                vX1X3_23 = (uchar64)(__as_uchar64(vX1).hi, __as_uchar64(vX3).hi);

                vXPermOut = __vpermeeq_yvvv(vXPermCtrl, vX1X3_01, vX0X2_01);
                *__SA0ADV(cshort16, pXLocal) = __as_cshort16(__shift_right_round(__as_short32(vXPermOut), vShift));
                vXPermOut = __vpermooq_yvvv(vXPermCtrl, vX1X3_01, vX0X2_01);
                *__SA0ADV(cshort16, pXLocal) = __as_cshort16(__shift_right_round(__as_short32(vXPermOut), vShift));
                vXPermOut = __vpermeeq_yvvv(vXPermCtrl, vX1X3_23, vX0X2_23);
                *__SA0ADV(cshort16, pXLocal) = __as_cshort16(__shift_right_round(__as_short32(vXPermOut), vShift));
                vXPermOut = __vpermooq_yvvv(vXPermCtrl, vX1X3_23, vX0X2_23);
                *__SA0ADV(cshort16, pXLocal) = __as_cshort16(__shift_right_round(__as_short32(vXPermOut), vShift));
            }
            __SA0_CLOSE();
            __SE0_CLOSE();
        }
        else
        {
            /* 32-point stage */
            se0_param =  *stov_ptr(uint16, (uint32_t *)((uint8_t *)pBlock + SE_LOOP3_PARAM_OFFSET));
            __SE0_OPEN((void *)pXLocal, se0_param);

            sa0_param =  *stov_ptr(uint16, (uint32_t *)((uint8_t *)pBlock + SA_LOOP3_PARAM_OFFSET));
            __SA0_OPEN(sa0_param);

            vTwX1 = *((cshort16 *)pWLocal);
            vTwX1 = (cshort16)(vTwX1.lo, vTwX1.lo);
            vTwX2 = *((cshort16 *)(pWLocal+8));
            vTwX2 = (cshort16)(vTwX2.lo, vTwX2.lo);
            vTwX3 = *((cshort16 *)(pWLocal+16));
            vTwX3 = (cshort16)(vTwX3.lo, vTwX3.lo);

            for (k = 0; k < numPoints; k += 64) {
                vX_0    = __SE0ADV(cshort16);
                vX_N_4  = __SE0ADV(cshort16);
                vX_N_2  = __SE0ADV(cshort16);
                vX_3N_4 = __SE0ADV(cshort16);

                vSum1   = vX_0 + vX_N_2;
                vSum2   = vX_N_4 + vX_3N_4;
                vDiff1  = vX_0 - vX_N_2;
                vDiff2  = vX_N_4 - vX_3N_4;

                vX0Temp = vSum1 + vSum2;
                vX1Temp = vDiff1 - __vcrot90h_vv(vDiff2);
                vX2Temp = vSum1 - vSum2;
                vX3Temp = vDiff1 + __vcrot90h_vv(vDiff2);

                vX0 = vX0Temp;
                vX1 = __cmpy_fx(vX1Temp, vTwX1);
                vX2 = __cmpy_fx(vX2Temp, vTwX2);
                vX3 = __cmpy_fx(vX3Temp, vTwX3);

                *__SA0ADV(cshort16, pXLocal) = __as_cshort16(__shift_right_round(__as_short32((cshort16)(vX0.lo, vX2.lo)), vShift));
                *__SA0ADV(cshort16, pXLocal) = __as_cshort16(__shift_right_round(__as_short32((cshort16)(vX1.lo, vX3.lo)), vShift));
                *__SA0ADV(cshort16, pXLocal) = __as_cshort16(__shift_right_round(__as_short32((cshort16)(vX0.hi, vX2.hi)), vShift));
                *__SA0ADV(cshort16, pXLocal) = __as_cshort16(__shift_right_round(__as_short32((cshort16)(vX1.hi, vX3.hi)), vShift));
            }
            __SE0_CLOSE();
            __SA0_CLOSE();
        }
        numPointsPerDft >>= 2;
        pWLocal += numPointsPerDft*3;
        stageIndex++;
        vShift = __vload_dup((uint32_t *)(pShift+stageIndex));

        if (numPointsPerDft == 4)
        {
            /* 4-point stage with bit-reversal */
            se0_param =  *stov_ptr(uint16, (uint32_t *)((uint8_t *)pBlock + SE_LOOP4_PARAM_OFFSET));
            __SE0_OPEN((void *)pXLocal, se0_param);

            numLeadingZeros = __norm((int32_t)(numPoints-1))+1;

            pY0 = stov_ptr(cshort, &pYLocal[0x00000000u]);
            pY1 = stov_ptr(cshort, &pYLocal[0x40000000u >> numLeadingZeros]);
            pY2 = stov_ptr(cshort, &pYLocal[0x80000000u >> numLeadingZeros]);
            pY3 = stov_ptr(cshort, &pYLocal[0xC0000000u >> numLeadingZeros]);

            for (k = 0; k < numPoints >> 4; k += 4)
            {
                offsetBitReverse = __bit_reverse(k) >> numLeadingZeros;

                vX_0    = __SE0ADV(cshort16);
                vX_N_4  = __SE0ADV(cshort16);
                vX_N_2  = __SE0ADV(cshort16);
                vX_3N_4 = __SE0ADV(cshort16);

                vSum1   = vX_0 + vX_N_2;
                vSum2   = vX_N_4 + vX_3N_4;
                vDiff1  = vX_0 - vX_N_2;
                vDiff2  = vX_N_4 - vX_3N_4;

                vX0 = vSum1 + vSum2;
                vX1 = vDiff1 - __vcrot90h_vv(vDiff2);
                vX2 = vSum1 - vSum2;
                vX3 = vDiff1 + __vcrot90h_vv(vDiff2);

                __vstore_reverse_bit((cshort16 *)&pY0[offsetBitReverse], __as_cshort16(__shift_right_round(__as_short32(vX0), vShift)));
                __vstore_reverse_bit((cshort16 *)&pY1[offsetBitReverse], __as_cshort16(__shift_right_round(__as_short32(vX1), vShift)));
                __vstore_reverse_bit((cshort16 *)&pY2[offsetBitReverse], __as_cshort16(__shift_right_round(__as_short32(vX2), vShift)));
                __vstore_reverse_bit((cshort16 *)&pY3[offsetBitReverse], __as_cshort16(__shift_right_round(__as_short32(vX3), vShift)));
            }
            __SE0_CLOSE();
        }
        else
        {
            /* 4-point stage followed by 2-point stage with bit-reversal */
            se0_param =  *stov_ptr(uint16, (uint32_t *)((uint8_t *)pBlock + SE_LOOP5_PARAM_OFFSET));
            __SE0_OPEN((void *)pXLocal, se0_param);

            numLeadingZeros = __norm((int32_t)(numPoints-1))+1;

            pWLocal += 1;
            twTemp = *pWLocal;
            vTwX1 = (cshort16)(twTemp, twTemp, twTemp, twTemp,
                               twTemp, twTemp, twTemp, twTemp,
                               twTemp, twTemp, twTemp, twTemp,
                               twTemp, twTemp, twTemp, twTemp);
            pWLocal += 2;
            twTemp = *pWLocal;
            vTwX2 = (cshort16)(twTemp, twTemp, twTemp, twTemp,
                               twTemp, twTemp, twTemp, twTemp,
                               twTemp, twTemp, twTemp, twTemp,
                               twTemp, twTemp, twTemp, twTemp);
            pWLocal += 2;
            twTemp = *pWLocal;
            vTwX3 = (cshort16)(twTemp, twTemp, twTemp, twTemp,
                               twTemp, twTemp, twTemp, twTemp,
                               twTemp, twTemp, twTemp, twTemp,
                               twTemp, twTemp, twTemp, twTemp);

            pY0 = &pYLocal[0x00000000u];
            pY1 = &pYLocal[0x80000000u >> numLeadingZeros];
            pY2 = &pYLocal[0x20000000u >> numLeadingZeros];
            pY3 = &pYLocal[0xA0000000u >> numLeadingZeros];
            pY4 = &pYLocal[0x40000000u >> numLeadingZeros];
            pY5 = &pYLocal[0xC0000000u >> numLeadingZeros];
            pY6 = &pYLocal[0x60000000u >> numLeadingZeros];
            pY7 = &pYLocal[0xE0000000u >> numLeadingZeros];

            for (k = 0; k < numPoints >> 4; k += 8)
            {
                offsetBitReverse = __bit_reverse(k) >> numLeadingZeros;

                /* Interleaving vX_x and vX_x_1 in SE fetches optimizes
                 * for SE tiling in transpose mode                      */
                vX_0      = __SE0ADV(cshort16);
                vX_0_1    = __SE0ADV(cshort16);
                vX_N_4    = __SE0ADV(cshort16);
                vX_N_4_1  = __SE0ADV(cshort16);
                vX_N_2    = __SE0ADV(cshort16);
                vX_N_2_1  = __SE0ADV(cshort16);
                vX_3N_4   = __SE0ADV(cshort16);
                vX_3N_4_1 = __SE0ADV(cshort16);

                vSum1   = vX_0 + vX_N_2;
                vSum2   = vX_N_4 + vX_3N_4;
                vDiff1  = vX_0 - vX_N_2;
                vDiff2  = vX_N_4 - vX_3N_4;

                vX0 = vSum1 + vSum2;
                vX1 = vDiff1 - __vcrot90h_vv(vDiff2);
                vX2 = vSum1 - vSum2;
                vX3 = vDiff1 + __vcrot90h_vv(vDiff2);

                vSum1_1   = vX_0_1 + vX_N_2_1;
                vSum2_1   = vX_N_4_1 + vX_3N_4_1;
                vDiff1_1  = vX_0_1 - vX_N_2_1;
                vDiff2_1  = vX_N_4_1 - vX_3N_4_1;

                vX0Temp = vSum1_1 + vSum2_1;
                vX1Temp = vDiff1_1 - __vcrot90h_vv(vDiff2_1);
                vX2Temp = vSum1_1 - vSum2_1;
                vX3Temp = vDiff1_1 + __vcrot90h_vv(vDiff2_1);

                vX0_1 = vX0Temp;
                vX1_1 = __cmpy_fx(vX1Temp, vTwX1);
                vX2_1 = __cmpy_fx(vX2Temp, vTwX2);
                vX3_1 = __cmpy_fx(vX3Temp, vTwX3);

                vX0_2PtDft_1 = vX0 + vX0_1;
                vX0_2PtDft_2 = vX0 - vX0_1;
                vX1_2PtDft_1 = vX1 + vX1_1;
                vX1_2PtDft_2 = vX1 - vX1_1;
                vX2_2PtDft_1 = vX2 + vX2_1;
                vX2_2PtDft_2 = vX2 - vX2_1;
                vX3_2PtDft_1 = vX3 + vX3_1;
                vX3_2PtDft_2 = vX3 - vX3_1;

                __vstore_reverse_bit((cshort16 *)&pY0[offsetBitReverse], __as_cshort16(__shift_right_round(__as_short32(vX0_2PtDft_1), vShift)));
                __vstore_reverse_bit((cshort16 *)&pY1[offsetBitReverse], __as_cshort16(__shift_right_round(__as_short32(vX0_2PtDft_2), vShift)));
                __vstore_reverse_bit((cshort16 *)&pY2[offsetBitReverse], __as_cshort16(__shift_right_round(__as_short32(vX1_2PtDft_1), vShift)));
                __vstore_reverse_bit((cshort16 *)&pY3[offsetBitReverse], __as_cshort16(__shift_right_round(__as_short32(vX1_2PtDft_2), vShift)));
                __vstore_reverse_bit((cshort16 *)&pY4[offsetBitReverse], __as_cshort16(__shift_right_round(__as_short32(vX2_2PtDft_1), vShift)));
                __vstore_reverse_bit((cshort16 *)&pY5[offsetBitReverse], __as_cshort16(__shift_right_round(__as_short32(vX2_2PtDft_2), vShift)));
                __vstore_reverse_bit((cshort16 *)&pY6[offsetBitReverse], __as_cshort16(__shift_right_round(__as_short32(vX3_2PtDft_1), vShift)));
                __vstore_reverse_bit((cshort16 *)&pY7[offsetBitReverse], __as_cshort16(__shift_right_round(__as_short32(vX3_2PtDft_2), vShift)));
            }
            __SE0_CLOSE();
        }
    }
    return (status);
}

#if (!defined(FFTLIB_REMOVE_CHECK_PARAMS) && !defined(FFTLIB_FFT1D_I16SC_C16SC_O16SC_REMOVE_CHECK_PARAMS)) || (defined(FFTLIB_CHECK_PARAMS)) || (defined(FFTLIB_FFT1D_I16SC_C16SC_O16SC_CHECK_PARAMS))

FFTLIB_STATUS FFTLIB_fft1d_i16sc_c16sc_o16sc_checkParams(int16_t * pX,
                                                         FFTLIB_bufParams1D_t * bufParamsX,
                                                         int16_t * pW,
                                                         FFTLIB_bufParams1D_t * bufParamsW,
                                                         int16_t * pY,
                                                         FFTLIB_bufParams1D_t * bufParamsY,
                                                         uint32_t * pShift,
                                                         FFTLIB_bufParams1D_t * bufParamsShift,
                                                         void *pBlock)
{
    FFTLIB_STATUS    status = FFTLIB_SUCCESS;

    if((pX == NULL) || (pW == NULL) || (pY == NULL) || (pShift == NULL) || (pBlock == NULL) ) {
        status = FFTLIB_ERR_NULL_POINTER;
    } else if( bufParamsX->dim_x != bufParamsW->dim_x ||
               bufParamsX->dim_x != bufParamsY->dim_x) {
        status = FFTLIB_ERR_INVALID_DIMENSION;
    } else if(bufParamsX->dim_x < 64*2) {           /* Minimum number of points is 64        */
        status = FFTLIB_ERR_INVALID_DIMENSION;
    } else if((bufParamsX->data_type != FFTLIB_INT16) ||
              (bufParamsW->data_type != FFTLIB_INT16) ||
              (bufParamsY->data_type != FFTLIB_INT16) ) {
        status = FFTLIB_ERR_INVALID_TYPE;
    } else if(bufParamsShift->data_type != FFTLIB_UINT32) {
        status = FFTLIB_ERR_INVALID_TYPE;
    } else if(((uint64_t)pX) & 0xFu) {               /* pX must be 16-byte aligned for a       */
        status = FFTLIB_ERR_NOT_ALIGNED_PTRS_STRIDES;/* streaming engine configuration         */
    } else if(((1u << (bufParamsShift->dim_x*2))*2 != bufParamsX->dim_x) &&    /* check for powers of 4 */
              ((1u << (bufParamsShift->dim_x*2))*2*2 != bufParamsX->dim_x) ) { /* check for powers of 2 */
        status = FFTLIB_ERR_INVALID_DIMENSION;
    }
    return (status);
}

#endif
