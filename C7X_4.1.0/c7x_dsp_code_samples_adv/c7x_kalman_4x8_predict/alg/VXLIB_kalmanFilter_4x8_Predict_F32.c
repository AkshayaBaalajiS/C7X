/*
* module name       : c7x_kalman_4x8_predict
*
* module descripton : Does a 4x8 (constant velocity) Kalman filter predict
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#include "VXLIB_kalmanFilter.h"
#include "VXLIB_kalmanFilter_4x8_Predict_F32.h"

#define MASK_BASE      (0x0000)
#define MASK1_OFFSET   (MASK_BASE)
#define MASK2_OFFSET   (MASK1_OFFSET + 64)
#define MASK3_OFFSET   (MASK2_OFFSET + 64)
#define MASK4_OFFSET   (MASK3_OFFSET + 64)
#define MASK5_OFFSET   (MASK4_OFFSET + 64)

#define SIMD_WIDTH_SHIFT       (4) /* 2^4 = 16 32b elements in a 512b vector */
#define SIMD_WIDTH             (1 << SIMD_WIDTH_SHIFT)
#define SIMD_WIDTH_RND         (SIMD_WIDTH >> 1)
#define NUM_SIMD_BLOCKS(width) (((width) >> SIMD_WIDTH_SHIFT) + (((width) - (((width) >> SIMD_WIDTH_SHIFT) << SIMD_WIDTH_SHIFT)) > 0 ? 1 : 0))

void VXLIB_kalmanFilter_4x8_Predict_F32_init(VXLIB_kalmanFilter_4x8_F32 *KF, void *pBlock)
{

  uint8_t mask1[64] = { 0,  1,  2,  3, 16, 17, 18, 19, 32, 33, 34, 35, 48, 49, 50, 51,
                        4,  5,  6,  7, 20, 21, 22, 23, 36, 37, 38, 39, 52, 53, 54, 55,
                        8,  9, 10, 11, 24, 25, 26, 27, 40, 41, 42, 43, 56, 57, 58, 59,
                       12, 13, 14, 15, 28, 29, 30, 31, 44, 45, 46, 47, 60, 61, 62, 63};

  uint8_t mask2[64] = { 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
                       32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47,
                       16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
                       48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63};

  uint8_t mask3[64] = { 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
                       16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
                        0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
                       16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31};

  uint8_t mask4[64] = { 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47,
                        48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63,
                        32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47,
                        48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63};

  uint8_t mask5[64] = { 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
                       16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
                       32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47,
                       48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63};

  *stov_ptr(uchar64, ((uint8_t *)pBlock + MASK1_OFFSET)) = *stov_ptr(uchar64, (uint8_t *)mask1);
  *stov_ptr(uchar64, ((uint8_t *)pBlock + MASK2_OFFSET)) = *stov_ptr(uchar64, (uint8_t *)mask2);
  *stov_ptr(uchar64, ((uint8_t *)pBlock + MASK3_OFFSET)) = *stov_ptr(uchar64, (uint8_t *)mask3);
  *stov_ptr(uchar64, ((uint8_t *)pBlock + MASK4_OFFSET)) = *stov_ptr(uchar64, (uint8_t *)mask4);
  *stov_ptr(uchar64, ((uint8_t *)pBlock + MASK5_OFFSET)) = *stov_ptr(uchar64, (uint8_t *)mask5);
}



void matadd_8x8_i32f_i32f_o32f(void *pA, void *pB, void *pC, void *pBlock)
{
    int32_t ctr;

    for(ctr = 0; ctr < 4; ctr++)
    {
        float16 matARow10 = *stov_ptr(float16, (float *)pA + (ctr * 16));
        float16 matBRow10 = *stov_ptr(float16, (float *)pB + (ctr * 16));

        *stov_ptr(float16, (float *)pC + (ctr * 16)) = matARow10 + matBRow10;
    }

}

void matvecmpy_8x8_i32f_i32f_o32f(void *pA, void *pB, void *pC, void *pBlock)
{
  float16 vA02, vA13;

  uchar64 matBRow10 = *stov_ptr(uchar64, (uint8_t *)pB);
  uchar64 matBRow32 = *stov_ptr(uchar64, (uint8_t *)((float *)pB + 16));
  uchar64 matBRow54 = *stov_ptr(uchar64, (uint8_t *)((float *)pB + 32));
  uchar64 matBRow76 = *stov_ptr(uchar64, (uint8_t *)((float *)pB + 48));

  uchar64 vMask1 = *stov_ptr(uchar64, ((uint8_t *)pBlock + MASK1_OFFSET));
  uchar64 vV0 = __permute_even_even_int(vMask1, matBRow32, matBRow10);
  uchar64 vV1 = __permute_odd_odd_int(vMask1, matBRow32, matBRow10);
  uchar64 vV2 = __permute_even_even_int(vMask1, matBRow76, matBRow54);
  uchar64 vV3 = __permute_odd_odd_int(vMask1, matBRow76, matBRow54);

  uchar64 vMask2 = *stov_ptr(uchar64, ((uint8_t *)pBlock + MASK2_OFFSET));
  uchar64 vI0 = __permute_low_low(vMask2, vV2, vV0);
  uchar64 vI1 = __permute_high_high(vMask2, vV2, vV0);
  uchar64 vI2 = __permute_low_low(vMask2, vV3, vV1);
  uchar64 vI3 = __permute_high_high(vMask2, vV3, vV1);

  float16 vA0 = __vload_dup((float *)pA + 0);
  float16 vA2 = __vload_dup((float *)pA + 2);

  vA02.lo = vA0.lo;
  vA02.hi = vA2.lo;

  float16 vRes = vA02 * __as_float16(vI0);

  float16 vAcc = vRes;

  float16 vA1 = __vload_dup((float *)pA + 1);
  float16 vA3 = __vload_dup((float *)pA + 3);

  vA13.lo = vA1.lo;
  vA13.hi = vA3.lo;

  vRes = vA13 * __as_float16(vI2);
  vAcc = vAcc + vRes;

  vA0 = __vload_dup((float *)pA + 4);
  vA2 = __vload_dup((float *)pA + 6);

  vA02.lo = vA0.lo;
  vA02.hi = vA2.lo;

  vRes = vA02 * __as_float16(vI1);
  vAcc = vAcc + vRes;

  vA1 = __vload_dup((float *)pA + 5);
  vA3 = __vload_dup((float *)pA + 7);

  vA13.lo = vA1.lo;
  vA13.hi = vA3.lo;

  vRes = vA13 * __as_float16(vI3);
  vAcc = vAcc + vRes;

  *stov_ptr(float8, (float *)pC) = vAcc.lo + vAcc.hi;

  return;
}

void matmpy_8x8_i32f_i32f_o32f(void *pA, void *pB, void *pC, void *pBlock)
{

  int32_t ctr;

  uchar64 matBRow10 = *stov_ptr(uchar64, (uint8_t *)pB);
  uchar64 matBRow32 = *stov_ptr(uchar64, (uint8_t *)((float *)pB + 16));
  uchar64 matBRow54 = *stov_ptr(uchar64, (uint8_t *)((float *)pB + 32));
  uchar64 matBRow76 = *stov_ptr(uchar64, (uint8_t *)((float *)pB + 48));

  uchar64 vMask3 = *stov_ptr(uchar64, ((uint8_t *)pBlock + MASK3_OFFSET));
  uchar64 vMask4 = *stov_ptr(uchar64, ((uint8_t *)pBlock + MASK4_OFFSET));
  uchar64 vMask5 = *stov_ptr(uchar64, ((uint8_t *)pBlock + MASK5_OFFSET));

  for(ctr = 0; ctr < 4; ctr++)
  {
    float16 matCRow = (float16)(0.0f);
    float16 matCRow0, matCRow1;

    ulong8 matARow0 = __vload_dup((__ulong *)pA + 0 + (ctr * 8));
    ulong8 matARow1 = __vload_dup((__ulong *)pA + 4 + (ctr * 8));
    float16 matARow = __as_float16(__permute_low_low(vMask5, __as_uchar64(matARow1), __as_uchar64(matARow0)));

    float16 matBRow00 = __as_float16(__permute(vMask3, matBRow10));
    float16 matBRow11 = __as_float16(__permute(vMask4, matBRow10));

    __vmatmpysp_vww(matARow, matBRow00, matBRow11, matCRow0, matCRow1);

    matCRow = matCRow + matCRow0;
    matCRow = matCRow + matCRow1;

    matARow0 = __vload_dup((__ulong *)pA + 1 + (ctr * 8));
    matARow1 = __vload_dup((__ulong *)pA + 5 + (ctr * 8));
    matARow = __as_float16(__permute_low_low(vMask5, __as_uchar64(matARow1), __as_uchar64(matARow0)));

    matBRow00 = __as_float16(__permute(vMask3, matBRow32));
    matBRow11 = __as_float16(__permute(vMask4, matBRow32));

    __vmatmpysp_vww(__as_float16(matARow), matBRow00, matBRow11, matCRow0, matCRow1);

    matCRow = matCRow + matCRow0;
    matCRow = matCRow + matCRow1;

    matARow0 = __vload_dup((__ulong *)pA + 2 + (ctr * 8));
    matARow1 = __vload_dup((__ulong *)pA + 6 + (ctr * 8));
    matARow = __as_float16(__permute_low_low(vMask5, __as_uchar64(matARow1), __as_uchar64(matARow0)));

    matBRow00 = __as_float16(__permute(vMask3, matBRow54));
    matBRow11 = __as_float16(__permute(vMask4, matBRow54));

    __vmatmpysp_vww(__as_float16(matARow), matBRow00, matBRow11, matCRow0, matCRow1);

    matCRow = matCRow + matCRow0;
    matCRow = matCRow + matCRow1;

    matARow0 = __vload_dup((__ulong *)pA + 3 + (ctr * 8));
    matARow1 = __vload_dup((__ulong *)pA + 7 + (ctr * 8));
    matARow = __as_float16(__permute_low_low(vMask5, __as_uchar64(matARow1), __as_uchar64(matARow0)));

    matBRow00 = __as_float16(__permute(vMask3, matBRow76));
    matBRow11 = __as_float16(__permute(vMask4, matBRow76));

    __vmatmpysp_vww(__as_float16(matARow), matBRow00, matBRow11, matCRow0, matCRow1);

    matCRow = matCRow + matCRow0;
    matCRow = matCRow + matCRow1;

    *stov_ptr(float16, (float *)pC + (ctr * 16)) = matCRow;
  }

}

void matmpy_8x8T_i32f_i32f_o32f(void *pA, void *pB, void *pC, void *pBlock)
{

  int32_t ctr;

  float16 matBRow10 = *stov_ptr(float16, (float *)pB);
  float16 matBRow32 = *stov_ptr(float16, ((float *)pB + 16));
  float16 matBRow54 = *stov_ptr(float16, ((float *)pB + 32));
  float16 matBRow76 = *stov_ptr(float16, ((float *)pB + 48));

  uchar64 vMask1 = *stov_ptr(uchar64, ((uint8_t *)pBlock + MASK1_OFFSET));
  uchar64 vV0 = __permute_even_even_int(vMask1, __as_uchar64(matBRow32), __as_uchar64(matBRow10));
  uchar64 vV1 = __permute_odd_odd_int(vMask1, __as_uchar64(matBRow32), __as_uchar64(matBRow10));
  uchar64 vV2 = __permute_even_even_int(vMask1, __as_uchar64(matBRow76), __as_uchar64(matBRow54));
  uchar64 vV3 = __permute_odd_odd_int(vMask1, __as_uchar64(matBRow76), __as_uchar64(matBRow54));

  uchar64 vMask2 = *stov_ptr(uchar64, ((uint8_t *)pBlock + MASK2_OFFSET));
  float16 vI0 = __as_float16(__permute_low_low(vMask2, vV2, vV0));
  float16 vI1 = __as_float16(__permute_high_high(vMask2, vV2, vV0));
  float16 vI2 = __as_float16(__permute_low_low(vMask2, vV3, vV1));
  float16 vI3 = __as_float16(__permute_high_high(vMask2, vV3, vV1));

  uchar64 vMask3 = *stov_ptr(uchar64, ((uint8_t *)pBlock + MASK3_OFFSET));
  uchar64 vMask4 = *stov_ptr(uchar64, ((uint8_t *)pBlock + MASK4_OFFSET));
  uchar64 vMask5 = *stov_ptr(uchar64, ((uint8_t *)pBlock + MASK5_OFFSET));

  for(ctr = 0; ctr < 4; ctr++)
  {
    float16 matCRow = (float16)(0.0f);
    float16 matCRow0, matCRow1;

    ulong8 matARow0 = __vload_dup((__ulong *)pA + 0 + (ctr * 8));
    ulong8 matARow1 = __vload_dup((__ulong *)pA + 4 + (ctr * 8));

    float16 matARow = __as_float16(__permute_low_low(vMask5, __as_uchar64(matARow1), __as_uchar64(matARow0)));

    float16 matBRow00 = __as_float16(__permute(vMask3, __as_uchar64(vI0)));
    float16 matBRow11 = __as_float16(__permute(vMask3, __as_uchar64(vI2)));

    __vmatmpysp_vww(matARow, matBRow00, matBRow11, matCRow0, matCRow1);

    matCRow = matCRow + matCRow0;
    matCRow = matCRow + matCRow1;

    matARow0 = __vload_dup((__ulong *)pA + 1 + (ctr * 8));
    matARow1 = __vload_dup((__ulong *)pA + 5 + (ctr * 8));

    matARow = __as_float16(__permute_low_low(vMask5, __as_uchar64(matARow1), __as_uchar64(matARow0)));

    matBRow00 = __as_float16(__permute(vMask4, __as_uchar64(vI0)));
    matBRow11 = __as_float16(__permute(vMask4, __as_uchar64(vI2)));

    __vmatmpysp_vww(__as_float16(matARow), matBRow00, matBRow11, matCRow0, matCRow1);

    matCRow = matCRow + matCRow0;
    matCRow = matCRow + matCRow1;

    matARow0 = __vload_dup((__ulong *)pA + 2 + (ctr * 8));
    matARow1 = __vload_dup((__ulong *)pA + 6 + (ctr * 8));

    matARow = __as_float16(__permute_low_low(vMask5, __as_uchar64(matARow1), __as_uchar64(matARow0)));

    matBRow00 = __as_float16(__permute(vMask3, __as_uchar64(vI1)));
    matBRow11 = __as_float16(__permute(vMask3, __as_uchar64(vI3)));

    __vmatmpysp_vww(__as_float16(matARow), matBRow00, matBRow11, matCRow0, matCRow1);

    matCRow = matCRow + matCRow0;
    matCRow = matCRow + matCRow1;

    matARow0 = __vload_dup((__ulong *)pA + 3 + (ctr * 8));
    matARow1 = __vload_dup((__ulong *)pA + 7 + (ctr * 8));

    matARow = __as_float16(__permute_low_low(vMask5, __as_uchar64(matARow1), __as_uchar64(matARow0)));

    matBRow00 = __as_float16(__permute(vMask4, __as_uchar64(vI1)));
    matBRow11 = __as_float16(__permute(vMask4, __as_uchar64(vI3)));

    __vmatmpysp_vww(__as_float16(matARow), matBRow00, matBRow11, matCRow0, matCRow1);

    matCRow = matCRow + matCRow0;
    matCRow = matCRow + matCRow1;

    *stov_ptr(float16, (float *)pC + (ctr * 16)) = matCRow;
  }
}

void VXLIB_kalmanFilter_4x8_Predict_F32_kernel(VXLIB_kalmanFilter_4x8_F32 *KF, void *pBlock)
{

    VXLIB_F32 *restrict    P      = KF->errorCov;
    VXLIB_F32 *restrict    Pnew   = KF->predictedErrorCov;
    VXLIB_F32 *restrict    Q      = KF->processNoiseCov;
    VXLIB_F32             *pTemp2 = KF->temp2;
    VXLIB_F32 *restrict    A      = KF->transition;
    VXLIB_F32             *pTemp1 = KF->temp1;
    VXLIB_F32 *restrict    X      = KF->state;
    VXLIB_F32 *restrict    Xnew   = KF->predictedState;

    /* Compute Xnew = A * X == Xnew = X' * A' */
    matvecmpy_8x8_i32f_i32f_o32f((void *)X, (void *)A, (void *)Xnew, pBlock);

    /* Compute pTemp1 = A * P */
    matmpy_8x8_i32f_i32f_o32f((void *)A, (void *)P, (void *)pTemp1, pBlock);

    /* Compute pTemp2 = (A * P) * A' */
    matmpy_8x8T_i32f_i32f_o32f((void *)pTemp1, (void *)A, (void *)pTemp2, pBlock);

    /* Compute Pnew = (A * P) * A' + Q */
    matadd_8x8_i32f_i32f_o32f((void *)pTemp2, (void *)Q, (void *)Pnew, pBlock);

}

/* ======================================================================== */
/*  End of file:  VXLIB_kalmanFilter_4x8_Predict_F32.c                      */
/* ======================================================================== */
