/*
* module name       : c7x_kalman_4x8_correct
*
* module descripton : Does a 4x8 (constant velocity) Kalman filter update
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#include "VXLIB_kalmanFilter.h"
#include "VXLIB_kalmanFilter_4x8_Correct_F32.h"
#include <math.h> /* For floor function */
#include <float.h> /* For FLT_MIN, FLT_MAX etc.*/

#define MASK_BASE      (0x0000)

#define MASK1_OFFSET   (MASK_BASE)
#define MASK2_OFFSET   (MASK1_OFFSET + 64)
#define MASK3_OFFSET   (MASK2_OFFSET + 64)
#define MASK4_OFFSET   (MASK3_OFFSET + 64)
#define MASK5_OFFSET   (MASK4_OFFSET + 64)

#define MASK6_OFFSET   (MASK5_OFFSET + 64)
#define MASK7_OFFSET   (MASK6_OFFSET + 64)
#define MASK8_OFFSET   (MASK7_OFFSET + 64)
#define MASK9_OFFSET   (MASK8_OFFSET + 64)

#define MASKA_OFFSET   (MASK9_OFFSET + 64)
#define MASKB_OFFSET   (MASKA_OFFSET + 64)

#define MASKC_OFFSET   (MASKB_OFFSET + 64)
#define MASKD_OFFSET   (MASKC_OFFSET + 64)
#define MASKE_OFFSET   (MASKD_OFFSET + 64)
#define MASKF_OFFSET   (MASKE_OFFSET + 64)
#define MASK10_OFFSET  (MASKF_OFFSET + 64)
#define MASK11_OFFSET  (MASK10_OFFSET + 64)
#define MASK12_OFFSET  (MASK11_OFFSET + 64)

static inline float16 VXLIB_oneByXVecF32(float16 vX)
{

    float16    f2Pkd = (float16)2.0f;
    float16    vX0,vY;
    __vpred    vp;

    vY  = __abs(vX);
    vX0 = __recip(vX);

    vX0 = vX0 * (f2Pkd - (vX0 * vX));

    vX0 = vX0 * (f2Pkd - (vX0 * vX));

    /* If input value is higher or equal to FLT_MAX
    */
    vp  = __cmp_le_pred((float16)FLT_MAX, vY);

    vX0 = __select(vp,(float16)FLT_MIN,vX0);

    /* If input value is lesser or equal to FLT_MIN
    */
    vp  = __cmp_le_pred(vY, (float16)FLT_MIN);

    vX0 = __select(vp,(float16)FLT_MAX,vX0);

    return (vX0);
}

void VXLIB_matrix_inverse_4x4_F32(VXLIB_F32 *temp2_F32,
                                 int16_t factor,
                                 VXLIB_F32 *inv_temp)
{
    VXLIB_D64   inv[16];

    VXLIB_D64   p03_05, p04_09, p05_0D, p06_44, p07_48, p08_4C, p09_84, p0A_88, p0B_8C, p0C_C4, p0D_C8, p0E_CC,
                p0F_11, p10_19, p11_1D, p12_50, p13_58, p14_5C, p15_90, p16_98, p17_9C, p19_D8, p1A_DC, p18_D0,
                p1B_21, p1C_25, p1D_2D, p1E_60, p1F_64, p20_6C, p21_A0, p22_A4, p2C_AC, p23_E0, p2D_EC, p24_E4,
                p01_35, p00_31, p02_39, p25_70, p26_74, p27_78, p28_B0, p29_B4, p2E_B8, p2A_F0, p2B_F4, p2F_F8;

    VXLIB_D64   det_D64;

    VXLIB_F32   t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, tA, tB, tC, tD, tE, tF;

    VXLIB_F32   diff00_FA_EB, diff01_F6_E7, diff02_B6_A7, diff07_E5_D6,
                diff03_F9_DB, diff04_F5_D7, diff05_B5_97, diff08_A5_96,
                diff0A_B2_A3, diff09_F2_E3, diff0B_F1_D3, diff0C_B1_93,
                diff0E_A1_92, diff06_E9_DA, diff0F_72_63, diff10_71_53,
                diff0D_E1_D2, diff11_61_52;

    VXLIB_F32   t00_FA, t01_EB, t02_F6, t03_E7, t04_B6, t05_A7, t06_F9, t07_DB, t08_F5, t09_D7, t0A_B5, t0B_97,
                t0C_E9, t0D_DA, t0E_E5, t0F_D6, t10_A5, t11_96, t12_F2, t13_E3, t14_B2, t15_A3, t16_D3, t17_F1,
                t18_B1, t19_93, t1A_D2, t1B_E1, t1C_92, t1D_A1, t1F_72, t1E_63, t20_71, t21_53, t22_61, t23_52;

    VXLIB_F32   det_F32;

    int32_t     im_F32;

    t0 = temp2_F32[0];
    t1 = temp2_F32[1];
    t2 = temp2_F32[2];
    t3 = temp2_F32[3];
    t4 = temp2_F32[4];
    t5 = temp2_F32[5];
    t6 = temp2_F32[6];
    t7 = temp2_F32[7];
    t8 = temp2_F32[8];
    t9 = temp2_F32[9];
    tA = temp2_F32[10];
    tB = temp2_F32[11];
    tC = temp2_F32[12];
    tD = temp2_F32[13];
    tE = temp2_F32[14];
    tF = temp2_F32[15];

    /*no intrinsic MPYSP inst*/
    t00_FA = tF * tA;
    t01_EB = tE * tB;
    t02_F6 = tF * t6;
    t03_E7 = tE * t7;
    t04_B6 = tB * t6;
    t05_A7 = tA * t7;
    t06_F9 = tF * t9;
    t07_DB = tD * tB;
    t08_F5 = tF * t5;
    t09_D7 = tD * t7;
    t0A_B5 = tB * t5;
    t0B_97 = t9 * t7;
    t0C_E9 = tE * t9;
    t0D_DA = tD * tA;
    t0E_E5 = tE * t5;
    t0F_D6 = tD * t6;

    t10_A5 = tA * t5;
    t11_96 = t9 * t6;
    t12_F2 = tF * t2;
    t13_E3 = tE * t3;
    t14_B2 = tB * t2;
    t15_A3 = tA * t3;
    t16_D3 = tD * t3;
    t17_F1 = tF * t1;
    t18_B1 = tB * t1;
    t19_93 = t9 * t3;
    t1A_D2 = tD * t2;
    t1B_E1 = tE * t1;
    t1C_92 = t9 * t2;
    t1D_A1 = tA * t1;
    t1E_63 = t6 * t3;
    t1F_72 = t7 * t2;

    t20_71 = t7 * t1;
    t21_53 = t5 * t3;
    t22_61 = t6 * t1;
    t23_52 = t5 * t2;

    diff00_FA_EB=  t00_FA - t01_EB;
    diff01_F6_E7=  t02_F6 - t03_E7;
    diff02_B6_A7=  t04_B6 - t05_A7;
    diff03_F9_DB=  t06_F9 - t07_DB;
    diff04_F5_D7=  t08_F5 - t09_D7;
    diff05_B5_97=  t0A_B5 - t0B_97;
    diff06_E9_DA=  t0C_E9 - t0D_DA;
    diff07_E5_D6=  t0E_E5 - t0F_D6;
    diff08_A5_96=  t10_A5 - t11_96;
    diff09_F2_E3=  t12_F2 - t13_E3;
    diff0A_B2_A3=  t14_B2 - t15_A3;
    diff0B_F1_D3= -t16_D3 + t17_F1;
    diff0C_B1_93=  t18_B1 - t19_93;
    diff0D_E1_D2= -t1A_D2 + t1B_E1;
    diff0E_A1_92= -t1C_92 + t1D_A1;
    diff0F_72_63= -t1E_63 + t1F_72;
    diff10_71_53=  t20_71 - t21_53;
    diff11_61_52=  t22_61 - t23_52;

    p00_31 = __mpy_ext(diff02_B6_A7, t1);
    p01_35 = __mpy_ext(diff0A_B2_A3, t5);
    p02_39 = __mpy_ext(diff0F_72_63, t9);
    p03_05 = __mpy_ext(diff00_FA_EB, t5);
    p04_09 = __mpy_ext(diff01_F6_E7, t9);
    p05_0D = __mpy_ext(diff02_B6_A7, tD);
    p06_44 = __mpy_ext(diff00_FA_EB, t4);
    p07_48 = __mpy_ext(diff01_F6_E7, t8);
    p08_4C = __mpy_ext(diff02_B6_A7, tC);
    p09_84 = __mpy_ext(diff03_F9_DB, t4);
    p0A_88 = __mpy_ext(diff04_F5_D7, t8);
    p0B_8C = __mpy_ext(diff05_B5_97, tC);
    p0C_C4 = __mpy_ext(diff06_E9_DA, t4);
    p0D_C8 = __mpy_ext(diff07_E5_D6, t8);
    p0E_CC = __mpy_ext(diff08_A5_96, tC);
    p0F_11 = __mpy_ext(diff00_FA_EB, t1);

    p10_19 = __mpy_ext(diff09_F2_E3, t9);
    p11_1D = __mpy_ext(diff0A_B2_A3, tD);
    p12_50 = __mpy_ext(diff00_FA_EB, t0);
    p13_58 = __mpy_ext(diff09_F2_E3, t8);
    p14_5C = __mpy_ext(diff0A_B2_A3, tC);
    p15_90 = __mpy_ext(diff03_F9_DB, t0);
    p16_98 = __mpy_ext(diff0B_F1_D3, t8);
    p17_9C = __mpy_ext(diff0C_B1_93, tC);
    p18_D0 = __mpy_ext(diff06_E9_DA, t0);
    p19_D8 = __mpy_ext(diff0D_E1_D2, t8);
    p1A_DC = __mpy_ext(diff0E_A1_92, tC);
    p1B_21 = __mpy_ext(diff01_F6_E7, t1);
    p1C_25 = __mpy_ext(diff09_F2_E3, t5);
    p1D_2D = __mpy_ext(diff0F_72_63, tD);
    p1E_60 = __mpy_ext(diff01_F6_E7, t0);
    p1F_64 = __mpy_ext(diff09_F2_E3, t4);

    p20_6C = __mpy_ext(diff0F_72_63, tC);
    p21_A0 = __mpy_ext(diff04_F5_D7, t0);
    p22_A4 = __mpy_ext(diff0B_F1_D3, t4);
    p23_E0 = __mpy_ext(diff07_E5_D6, t0);
    p24_E4 = __mpy_ext(diff0D_E1_D2, t4);
    p25_70 = __mpy_ext(diff02_B6_A7, t0);
    p26_74 = __mpy_ext(diff0A_B2_A3, t4);
    p27_78 = __mpy_ext(diff0F_72_63, t8);
    p28_B0 = __mpy_ext(diff05_B5_97, t0);
    p29_B4 = __mpy_ext(diff0C_B1_93, t4);
    p2A_F0 = __mpy_ext(diff08_A5_96, t0);
    p2B_F4 = __mpy_ext(diff0E_A1_92, t4);

    p2C_AC = __mpy_ext(diff10_71_53, t4);
    p2D_EC = __mpy_ext(diff11_61_52, tC);
    p2E_B8 = __mpy_ext(diff10_71_53, t8);
    p2F_F8 = __mpy_ext(diff11_61_52, t8);


    inv[0]  =  (p03_05 - p04_09)  + p05_0D;
    inv[4]  =  (-p06_44 + p07_48) - p08_4C;
    inv[8]  =  (p09_84 - p0A_88)  + p0B_8C;
    inv[12] =  (-p0C_C4 + p0D_C8) - p0E_CC;

    inv[1]  =  (-p0F_11 - p10_19) - p11_1D;
    inv[5]  =  (p12_50 - p13_58)  + p14_5C;
    inv[9]  =  (-p15_90 + p16_98) - p17_9C;
    inv[13] =  (p18_D0 - p19_D8)  + p1A_DC;

    inv[2]  =  (p1B_21 - p1C_25)  + p1D_2D;
    inv[6]  =  (-p1E_60 + p1F_64) - p20_6C;
    inv[10] =  (p21_A0 - p22_A4)  + p2C_AC;
    inv[14] =  (-p23_E0 + p24_E4) - p2D_EC;

    inv[3]  =  (-p00_31 + p01_35) - p02_39;
    inv[7]  =  (p25_70 - p26_74)  + p27_78;
    inv[11] =  (-p28_B0 + p29_B4) - p2E_B8;
    inv[15] =  (p2A_F0 - p2B_F4)  + p2F_F8;

    det_D64 =((VXLIB_D64)t0 * inv[0]) + ((VXLIB_D64)t1 * inv[4]) + ((VXLIB_D64)t2 * inv[8]) +
              ((VXLIB_D64)t3 * inv[12]);

    det_D64 = 1.0 / ((VXLIB_D64)factor * det_D64);
    det_F32=(VXLIB_F32) det_D64;

    for( im_F32 = 0; im_F32 < 16; im_F32++ ) {
        inv_temp[im_F32] = ((VXLIB_F32)inv[im_F32] * det_F32);
    }
}

void VXLIB_kalmanFilter_4x8_Correct_F32_init(VXLIB_kalmanFilter_4x8_F32 *KF,
                                            const VXLIB_F32 *restrict Z,
                                            VXLIB_F32 *restrict Residual,
                                            void *pBlock)
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

  uint8_t mask6[64] = { 0,  1,  2,  3, 16, 17, 18, 19, 32, 33, 34, 35, 48, 49, 50, 51,
                        0,  1,  2,  3, 16, 17, 18, 19, 32, 33, 34, 35, 48, 49, 50, 51,
                        0,  1,  2,  3, 16, 17, 18, 19, 32, 33, 34, 35, 48, 49, 50, 51,
                        0,  1,  2,  3, 16, 17, 18, 19, 32, 33, 34, 35, 48, 49, 50, 51};

  uint8_t mask7[64] = { 4,  5,  6,  7, 20, 21, 22, 23, 36, 37, 38, 39, 52, 53, 54, 55,
                        4,  5,  6,  7, 20, 21, 22, 23, 36, 37, 38, 39, 52, 53, 54, 55,
                        4,  5,  6,  7, 20, 21, 22, 23, 36, 37, 38, 39, 52, 53, 54, 55,
                        4,  5,  6,  7, 20, 21, 22, 23, 36, 37, 38, 39, 52, 53, 54, 55};

  uint8_t mask8[64] = { 8,  9, 10, 11, 24, 25, 26, 27, 40, 41, 42, 43, 56, 57, 58, 59,
                        8,  9, 10, 11, 24, 25, 26, 27, 40, 41, 42, 43, 56, 57, 58, 59,
                        8,  9, 10, 11, 24, 25, 26, 27, 40, 41, 42, 43, 56, 57, 58, 59,
                        8,  9, 10, 11, 24, 25, 26, 27, 40, 41, 42, 43, 56, 57, 58, 59};

  uint8_t mask9[64] = {12, 13, 14, 15, 28, 29, 30, 31, 44, 45, 46, 47, 60, 61, 62, 63,
                       12, 13, 14, 15, 28, 29, 30, 31, 44, 45, 46, 47, 60, 61, 62, 63,
                       12, 13, 14, 15, 28, 29, 30, 31, 44, 45, 46, 47, 60, 61, 62, 63,
                       12, 13, 14, 15, 28, 29, 30, 31, 44, 45, 46, 47, 60, 61, 62, 63};

  uint8_t maskA[64] = { 0,  1,  2,  3,  4,  5,  6,  7,  0,  1,  2,  3,  4,  5,  6,  7,
                       16, 17, 18, 19, 20, 21, 22, 23, 16, 17, 18, 19, 20, 21, 22, 23,
                       32, 33, 34, 35, 36, 37, 38, 39, 32, 33, 34, 35, 36, 37, 38, 39,
                       48, 49, 50, 51, 52, 53, 54, 55, 48, 49, 50, 51, 52, 53, 54, 55};

  uint8_t maskB[64] = { 8,  9, 10, 11, 12, 13, 14, 15,  8,  9, 10, 11, 12, 13, 14, 15,
                       24, 25, 26, 27, 28, 29, 30, 31, 24, 25, 26, 27, 28, 29, 30, 31,
                       40, 41, 42, 43, 44, 45, 46, 47, 40, 41, 42, 43, 44, 45, 46, 47,
                       56, 57, 58, 59, 60, 61, 62, 63, 56, 57, 58, 59, 60, 61, 62, 63};

  uint8_t maskC[64] = { 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
                        0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
                        0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
                        0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15};

  uint8_t maskD[64] = {16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
                       16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
                       16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
                       16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31};

  uint8_t maskE[64] = {32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47,
                       32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47,
                       32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47,
                       32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47};

  uint8_t maskF[64] = {48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63,
                       48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63,
                       48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63,
                       48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63};

  uint8_t mask10[64] = { 0,  1,  2,  3,  4,  5,  6,  7,  0,  1,  2,  3,  4,  5,  6,  7,
                         8,  9, 10, 11, 12, 13, 14, 15,  8,  9, 10, 11, 12, 13, 14, 15,
                        16, 17, 18, 19, 20, 21, 22, 23, 16, 17, 18, 19, 20, 21, 22, 23,
                        24, 25, 26, 27, 28, 29, 30, 31, 24, 25, 26, 27, 28, 29, 30, 31};

  uint8_t mask11[64] = { 0,  1,  2,  3,  4,  5,  6,  7,  0,  1,  2,  3,  4,  5,  6,  7,
                         0,  1,  2,  3,  4,  5,  6,  7,  0,  1,  2,  3,  4,  5,  6,  7,
                         8,  9, 10, 11, 12, 13, 14, 15,  8,  9, 10, 11, 12, 13, 14, 15,
                         8,  9, 10, 11, 12, 13, 14, 15,  8,  9, 10, 11, 12, 13, 14, 15};

  uint8_t mask12[64] = { 0,  1,  2,  3,  8,  9, 10, 11, 16, 17, 18, 19, 24, 25, 26, 27,
                        32, 33, 34, 35, 40, 41, 42, 43, 48, 49, 50, 51, 56, 57, 58, 59,
                         4,  5,  6,  7, 12, 13, 14, 15, 20, 21, 22, 23, 28, 29, 30, 31,
                        36, 37, 38, 39, 44, 45, 46, 47, 52, 53, 54, 55, 60, 61, 62, 63};

  *((uchar64 *)((uint8_t *)pBlock + MASK1_OFFSET)) = *((uchar64 *)mask1);
  *((uchar64 *)((uint8_t *)pBlock + MASK2_OFFSET)) = *((uchar64 *)mask2);
  *((uchar64 *)((uint8_t *)pBlock + MASK3_OFFSET)) = *((uchar64 *)mask3);
  *((uchar64 *)((uint8_t *)pBlock + MASK4_OFFSET)) = *((uchar64 *)mask4);
  *((uchar64 *)((uint8_t *)pBlock + MASK5_OFFSET)) = *((uchar64 *)mask5);

  *((uchar64 *)((uint8_t *)pBlock + MASK6_OFFSET)) = *((uchar64 *)mask6);
  *((uchar64 *)((uint8_t *)pBlock + MASK7_OFFSET)) = *((uchar64 *)mask7);
  *((uchar64 *)((uint8_t *)pBlock + MASK8_OFFSET)) = *((uchar64 *)mask8);
  *((uchar64 *)((uint8_t *)pBlock + MASK9_OFFSET)) = *((uchar64 *)mask9);

  *((uchar64 *)((uint8_t *)pBlock + MASKA_OFFSET)) = *((uchar64 *)maskA);
  *((uchar64 *)((uint8_t *)pBlock + MASKB_OFFSET)) = *((uchar64 *)maskB);

  *((uchar64 *)((uint8_t *)pBlock + MASKC_OFFSET)) = *((uchar64 *)maskC);
  *((uchar64 *)((uint8_t *)pBlock + MASKD_OFFSET)) = *((uchar64 *)maskD);
  *((uchar64 *)((uint8_t *)pBlock + MASKE_OFFSET)) = *((uchar64 *)maskE);
  *((uchar64 *)((uint8_t *)pBlock + MASKF_OFFSET)) = *((uchar64 *)maskF);
  *((uchar64 *)((uint8_t *)pBlock + MASK10_OFFSET)) = *((uchar64 *)mask10);

  *((uchar64 *)((uint8_t *)pBlock + MASK11_OFFSET)) = *((uchar64 *)mask11);
  *((uchar64 *)((uint8_t *)pBlock + MASK12_OFFSET)) = *((uchar64 *)mask12);
}

void VXLIB_kalmanFilter_4x8_Correct_F32_stage1(void *pA, void *pB, void *pC, void *pBlock)
{
  int32_t ctr;

  uchar64 matBRow10 = *((uchar64 *)pB);
  uchar64 matBRow32 = *((uchar64 *)((float *)pB + 16));

  uchar64 vMask6 = *((uchar64 *)((uint8_t *)pBlock + MASK6_OFFSET));
  uchar64 vMask7 = *((uchar64 *)((uint8_t *)pBlock + MASK7_OFFSET));
  uchar64 vMask8 = *((uchar64 *)((uint8_t *)pBlock + MASK8_OFFSET));
  uchar64 vMask9 = *((uchar64 *)((uint8_t *)pBlock + MASK9_OFFSET));

  uchar64 vMaskA = *((uchar64 *)((uint8_t *)pBlock + MASKA_OFFSET));
  uchar64 vMaskB = *((uchar64 *)((uint8_t *)pBlock + MASKB_OFFSET));

  for(ctr = 0; ctr < 2; ctr++)
  {
    float16 matCRow0, matCRow1;
    float16 matCRow = (float16)(0.0f);

    uchar64 matARow0 = *((uchar64 *)((float *)pA + (ctr * 32)));
    uchar64 matARow1 = *((uchar64 *)((float *)pA + (ctr * 32) + 16));

    uchar64 matARow  = __permute_even_even_long(vMaskA, matARow1, matARow0);

    uchar64 matBRow00 = __permute_even_even_int(vMask6, matBRow32, matBRow10);
    uchar64 matBRow11 = __permute_odd_odd_int(vMask6, matBRow32, matBRow10);

    __vmatmpysp_vww(__as_float16(matARow), __as_float16(matBRow00), __as_float16(matBRow11), matCRow0, matCRow1);

    matCRow = matCRow + matCRow0;
    matCRow = matCRow + matCRow1;

    matARow = __permute_odd_odd_long(vMaskA, matARow1, matARow0);

    matBRow00 = __permute_even_even_int(vMask7, matBRow32, matBRow10);
    matBRow11 = __permute_odd_odd_int(vMask7, matBRow32, matBRow10);

    __vmatmpysp_vww(__as_float16(matARow), __as_float16(matBRow00), __as_float16(matBRow11), matCRow0, matCRow1);

    matCRow = matCRow + matCRow0;
    matCRow = matCRow + matCRow1;

    matARow0 = *((uchar64 *)((float *)pA));
    matARow1 = *((uchar64 *)((float *)pA + 16));

    matARow = __permute_even_even_long(vMaskB, matARow1, matARow0);

    matBRow00 = __permute_even_even_int(vMask8, matBRow32, matBRow10);
    matBRow11 = __permute_odd_odd_int(vMask8, matBRow32, matBRow10);

    __vmatmpysp_vww(__as_float16(matARow), __as_float16(matBRow00), __as_float16(matBRow11), matCRow0, matCRow1);

    matCRow = matCRow + matCRow0;
    matCRow = matCRow + matCRow1;

    matARow = __permute_odd_odd_long(vMaskB, matARow1, matARow0);

    matBRow00 = __permute_even_even_int(vMask9, matBRow32, matBRow10);
    matBRow11 = __permute_odd_odd_int(vMask9, matBRow32, matBRow10);

    __vmatmpysp_vww(__as_float16(matARow), __as_float16(matBRow00), __as_float16(matBRow11), matCRow0, matCRow1);

    matCRow = matCRow + matCRow0;
    matCRow = matCRow + matCRow1;

    *((float16 *)pC + ctr) = matCRow;
  }
}
void VXLIB_kalmanFilter_4x8_Correct_F32_stage2(void *pA, void *pB, void *pC, void *pBlock)
{
    uchar64 matBRow10 = *((uchar64 *)pB);
    uchar64 matBRow32 = *((uchar64 *)((float *)pB + 16));

    uchar64 vMaskA = *((uchar64 *)((uint8_t *)pBlock + MASKA_OFFSET));
    uchar64 vMaskB = *((uchar64 *)((uint8_t *)pBlock + MASKB_OFFSET));

    uchar64 vMaskC = *((uchar64 *)((uint8_t *)pBlock + MASKC_OFFSET));
    uchar64 vMaskD = *((uchar64 *)((uint8_t *)pBlock + MASKD_OFFSET));
    uchar64 vMaskE = *((uchar64 *)((uint8_t *)pBlock + MASKE_OFFSET));
    uchar64 vMaskF = *((uchar64 *)((uint8_t *)pBlock + MASKF_OFFSET));

    float16 matCRow0, matCRow1;
    float16 matCRow = (float16)(0.0f);

    uchar64 matARow0 = *((uchar64 *)pA);
    uchar64 matARow1 = *((uchar64 *)((float *)pA + 16));

    uchar64 matARow  = __permute_even_even_long(vMaskA, matARow1, matARow0);

    uchar64 matBRow00 = __permute(vMaskC, matBRow10);
    uchar64 matBRow11 = __permute(vMaskD, matBRow10);

    __vmatmpysp_vww(__as_float16(matARow), __as_float16(matBRow00), __as_float16(matBRow11), matCRow0, matCRow1);

    matCRow = matCRow + matCRow0;
    matCRow = matCRow + matCRow1;

    matARow = __permute_odd_odd_long(vMaskA, matARow1, matARow0);

    matBRow00 = __permute(vMaskE, matBRow10);
    matBRow11 = __permute(vMaskF, matBRow10);

    __vmatmpysp_vww(__as_float16(matARow), __as_float16(matBRow00), __as_float16(matBRow11), matCRow0, matCRow1);

    matCRow = matCRow + matCRow0;
    matCRow = matCRow + matCRow1;

    matARow0 = *((uchar64 *)((float *)pA));
    matARow1 = *((uchar64 *)((float *)pA + 16));

    matARow = __permute_even_even_long(vMaskB, matARow1, matARow0);

    matBRow00 = __permute(vMaskC, matBRow32);
    matBRow11 = __permute(vMaskD, matBRow32);

    __vmatmpysp_vww(__as_float16(matARow), __as_float16(matBRow00), __as_float16(matBRow11), matCRow0, matCRow1);

    matCRow = matCRow + matCRow0;
    matCRow = matCRow + matCRow1;

    matARow = __permute_odd_odd_long(vMaskB, matARow1, matARow0);

    matBRow00 = __permute(vMaskE, matBRow32);
    matBRow11 = __permute(vMaskF, matBRow32);

    __vmatmpysp_vww(__as_float16(matARow), __as_float16(matBRow00), __as_float16(matBRow11), matCRow0, matCRow1);

    matCRow = matCRow + matCRow0;
    matCRow = matCRow + matCRow1;

    *((float16 *)pC) = matCRow;
}

void VXLIB_kalmanFilter_4x8_Correct_F32_stage4(void *pA, void *pB, void *pC, void *pBlock)
{
    uchar64 matBRow10 = *((uchar64 *)pB);

    uchar64 vMaskA = *((uchar64 *)((uint8_t *)pBlock + MASKA_OFFSET));
    uchar64 vMaskB = *((uchar64 *)((uint8_t *)pBlock + MASKB_OFFSET));

    uchar64 vMaskC = *((uchar64 *)((uint8_t *)pBlock + MASKC_OFFSET));
    uchar64 vMaskD = *((uchar64 *)((uint8_t *)pBlock + MASKD_OFFSET));
    uchar64 vMaskE = *((uchar64 *)((uint8_t *)pBlock + MASKE_OFFSET));
    uchar64 vMaskF = *((uchar64 *)((uint8_t *)pBlock + MASKF_OFFSET));

    int32_t ctr;

  for(ctr = 0; ctr < 2; ctr++)
  {
    float16 matCRow0, matCRow1;
    float16 matCRow = (float16)(0.0f);

    uchar64 matARow0 = *((uchar64 *)((float *)pA + (ctr * 16)));

    uchar64 matARow  = __permute(vMaskA, matARow0);

    uchar64 matBRow00 = __permute(vMaskC, matBRow10);
    uchar64 matBRow11 = __permute(vMaskD, matBRow10);

    __vmatmpysp_vww(__as_float16(matARow), __as_float16(matBRow00), __as_float16(matBRow11), matCRow0, matCRow1);

    matCRow = matCRow + matCRow0;
    matCRow = matCRow + matCRow1;

    matARow = __permute(vMaskB, matARow0);

    matBRow00 = __permute(vMaskE, matBRow10);
    matBRow11 = __permute(vMaskF, matBRow10);

    __vmatmpysp_vww(__as_float16(matARow), __as_float16(matBRow00), __as_float16(matBRow11), matCRow0, matCRow1);

    matCRow = matCRow + matCRow0;
    matCRow = matCRow + matCRow1;

    *((float16 *)pC + ctr) = matCRow;
  }

}

void VXLIB_kalmanFilter_4x8_Correct_F32_stage5(void *pA, void *pB, void *pC, void *pBlock)
{

  uchar64 matBRow10 = *((uchar64 *)pB);
  uchar64 matBRow32 = *((uchar64 *)((float *)pB + 16));

  uchar64 vMask1  = *((uchar64 *)((uint8_t *)pBlock + MASK1_OFFSET));
  uchar64 vMask10 = *((uchar64 *)((uint8_t *)pBlock + MASK10_OFFSET));

  {
    float16 matCRow0, matCRow1;
    float16 matCRow = (float16)(0.0f);

    uchar64 matARow0 = *((uchar64 *)pA);

    uchar64 matARow  = __permute(vMask10, matARow0);

    uchar64 matBRow00 = __permute_even_even_int(vMask1, matBRow32, matBRow10);
    uchar64 matBRow11 = __permute_odd_odd_int(vMask1, matBRow32, matBRow10);

    __vmatmpysp_vww(__as_float16(matARow), __as_float16(matBRow00), __as_float16(matBRow11), matCRow0, matCRow1);

    matCRow = matCRow + matCRow0;
    matCRow = matCRow + matCRow1;

    float8 vTempC8 = matCRow.lo + matCRow.hi;

    *((float4 *)pC) = vTempC8.lo + vTempC8.hi;
  }
}

void VXLIB_kalmanFilter_4x8_Correct_F32_stage6(void *pA, void *pB, void *pC, void *pBlock)
{
  uchar64 matBRow10 = *((uchar64 *)pB);
  uchar64 matBRow32 = *((uchar64 *)((float *)pB + 16));

  uchar64 vMask11 = *((uchar64 *)((uint8_t *)pBlock + MASK11_OFFSET));
  uchar64 vMask12 = *((uchar64 *)((uint8_t *)pBlock + MASK12_OFFSET));

  {
    float16 matCRow0, matCRow1;
    float16 matCRow = (float16)(0.0f);

    uchar64 matARow0 = *((uchar64 *)pA);

    uchar64 matARow  = __permute(vMask11, matARow0);

    uchar64 matBRow00 = __permute_even_even_int(vMask12, matBRow32, matBRow10);
    uchar64 matBRow11 = __permute_odd_odd_int(vMask12, matBRow32, matBRow10);

    __vmatmpysp_vww(__as_float16(matARow), __as_float16(matBRow00), __as_float16(matBRow11), matCRow0, matCRow1);

    matCRow = matCRow + matCRow0;
    matCRow = matCRow + matCRow1;

    *((float8 *)pC) = matCRow.lo + matCRow.hi;
  }
}

void VXLIB_kalmanFilter_4x8_Correct_F32_stage7(void *pA, void *pB, void *pC, void *pBlock)
{
  int32_t ctr;

  uchar64 matBRow10 = *((uchar64 *)pB);
  uchar64 matBRow32 = *((uchar64 *)((float *)pB + 16));

  uchar64 vMask3 = *((uchar64 *)((uint8_t *)pBlock + MASK3_OFFSET));
  uchar64 vMask4 = *((uchar64 *)((uint8_t *)pBlock + MASK4_OFFSET));
  uchar64 vMask5 = *((uchar64 *)((uint8_t *)pBlock + MASK5_OFFSET));

  for(ctr = 0; ctr < 4; ctr++)
  {
    float16 matCRow = (float16)(0.0f);
    float16 matCRow0, matCRow1;

    ulong8 matARow0 = __vload_dup((__ulong *)pA + 0 + (ctr * 4));
    ulong8 matARow1 = __vload_dup((__ulong *)pA + 2 + (ctr * 4));
    float16 matARow = __as_float16(__permute_low_low(vMask5, __as_uchar64(matARow1), __as_uchar64(matARow0)));

    float16 matBRow00 = __as_float16(__permute(vMask3, matBRow10));
    float16 matBRow11 = __as_float16(__permute(vMask4, matBRow10));

    __vmatmpysp_vww(matARow, matBRow00, matBRow11, matCRow0, matCRow1);

    matCRow = matCRow + matCRow0;
    matCRow = matCRow + matCRow1;

    matARow0 = __vload_dup((__ulong *)pA + 1 + (ctr * 4));
    matARow1 = __vload_dup((__ulong *)pA + 3 + (ctr * 4));
    matARow = __as_float16(__permute_low_low(vMask5, __as_uchar64(matARow1), __as_uchar64(matARow0)));

    matBRow00 = __as_float16(__permute(vMask3, matBRow32));
    matBRow11 = __as_float16(__permute(vMask4, matBRow32));

    __vmatmpysp_vww(__as_float16(matARow), matBRow00, matBRow11, matCRow0, matCRow1);

    matCRow = matCRow + matCRow0;
    matCRow = matCRow + matCRow1;

    *((float16 *)pC + ctr) = matCRow;
  }
}

void VXLIB_kalmanFilter_4x8_Correct_F32_stage8(void *pA, void *pB, void *pC, void *pBlock)
{
  int32_t ctr;

  uchar64 matBRow10 = *((uchar64 *)pB);
  uchar64 matBRow32 = *((uchar64 *)((float *)pB + 16));
  uchar64 matBRow54 = *((uchar64 *)((float *)pB + 32));
  uchar64 matBRow76 = *((uchar64 *)((float *)pB + 48));

  uchar64 vMask3 = *((uchar64 *)((uint8_t *)pBlock + MASK3_OFFSET));
  uchar64 vMask4 = *((uchar64 *)((uint8_t *)pBlock + MASK4_OFFSET));
  uchar64 vMask5 = *((uchar64 *)((uint8_t *)pBlock + MASK5_OFFSET));

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

    *((float16 *)pC + ctr) = matCRow;
  }
}

void VXLIB_kalmanFilter_4x8_Correct_F32_stage9(void *pA, void *pB, void *pC, void *pBlock)
{
    int32_t ctr;

    for(ctr = 0; ctr < 4; ctr++)
    {
        float16 matARow10 = *((float16 *)pA + ctr);
        float16 matBRow10 = *((float16 *)pB + ctr);

        *((float16 *)pC + ctr) = matARow10 - matBRow10;
    }
}

void VXLIB_kalmanFilter_4x8_Correct_F32_kernel
(
    VXLIB_kalmanFilter_4x8_F32 *KF,
    const VXLIB_F32 *restrict Z,
    VXLIB_F32 *restrict Residual,
    void *pBlock
)
{
    VXLIB_F32 *restrict    X      = KF->state;
    VXLIB_F32 *restrict    Xnew   = KF->predictedState;
    VXLIB_F32 *restrict    P      = KF->errorCov;
    VXLIB_F32 *restrict    Pnew   = KF->predictedErrorCov;
    VXLIB_F32 *restrict    H      = KF->measurement;
    VXLIB_F32 *restrict    R      = KF->measurementNoiseCov;
    VXLIB_F32             *pTemp1 = KF->temp1;
    VXLIB_F32             *pTemp2 = KF->temp2;
    VXLIB_F32             *pTemp3 = KF->temp3;
    VXLIB_F32 *restrict    K      = KF->kalmanGain;

    int32_t     factor = 2 * KF->scaleFactor;

    //Stage 1
    /* kalman gain*/
    /*K = P1*H'; [8x8 * 8x4] = 8x4*/
    VXLIB_kalmanFilter_4x8_Correct_F32_stage1((void *)Pnew, (void *)H, (void *)pTemp1, pBlock);

    //Stage 2
    /*pTemp2 = H*(P1*H') [4x8 * 8x4] = 4x4*/
    VXLIB_kalmanFilter_4x8_Correct_F32_stage2((void *)H, (void *)pTemp1, (void *)pTemp2, pBlock);

    // Stage 3
    /*pTemp2 = (H*P1*H') + R* [4x4 + 4x4] = 4x4 */
    float16 vTemp2 = *((float16 *)&pTemp2[0]);
    float16 vR     = *((float16 *)&R[0]);
    vTemp2 = vTemp2 + vR;
    float16 vFactor = VXLIB_oneByXVecF32((float16)factor);
    *((float16 *)&pTemp2[0]) = vTemp2 * vFactor;

    /* compute inverse of pTemp2*/
    /* pTemp2 is a 4x4 matrix inv[4x4]*/
    VXLIB_matrix_inverse_4x4_F32(pTemp2, (int16_t)factor, pTemp3);

    //Stage 4
    /* K = K* inv((H*P1*H') + R) [8x4 * 4x4] = 8x4 */
    VXLIB_kalmanFilter_4x8_Correct_F32_stage4((void *)pTemp1, (void *)pTemp3, (void *)K, pBlock);

    //Stage 5
    /* pTemp1 = H*X1 [4x8 * 8x1] = 4x1*/
    //Also equivalent to [1x8 * 8x4] = 1x4
    VXLIB_kalmanFilter_4x8_Correct_F32_stage5((void *)Xnew, (void *)H, (void *)pTemp1, pBlock);

    //Stage 6
    /* Residual = Z - H*X1 [4x1 - 4x1] = 4x1*/
    float4 vTemp1    = *((float4 *)&pTemp1[0]);
    float4 vZ        = *((float4 *)&Z[0]);
    float4 vResidual = vZ - vTemp1;
    *((float4 *)&Residual[0]) = vResidual;

    /* K*Residual [8x4 * 4x1] = 8x1 */
    //Also equivalent to [1x4 * 4*8] = 1x8
    VXLIB_kalmanFilter_4x8_Correct_F32_stage6((void *)Residual, (void *)K, (void *)pTemp2, pBlock);

    float8 vTemp2_1  = *((float8 *)&pTemp2[0]);
    float8 vXnew     = *((float8 *)&Xnew[0]);
    float8 vX        = vXnew + vTemp2_1;
    *((float8 *)&X[0]) = vX;

    //Stage 7
    /* update error covariance*/
    /* K*H [8x4 * 4x8] = 8x8 */
    VXLIB_kalmanFilter_4x8_Correct_F32_stage7((void *)K, (void *)H, (void *)pTemp2, pBlock);

    //Stage 8
    /* (K*H)*Pnew [8x8 * 8x8] = 8x8 */
    VXLIB_kalmanFilter_4x8_Correct_F32_stage8((void *)pTemp2, (void *)Pnew, (void *)pTemp3, pBlock);

    //Stage 9
    /* Pnew - ((K*H)*Pnew) [8x8 - 8x8] = 8x8 */
    VXLIB_kalmanFilter_4x8_Correct_F32_stage9((void *)Pnew, (void *)pTemp3, (void *)P, pBlock);

}
