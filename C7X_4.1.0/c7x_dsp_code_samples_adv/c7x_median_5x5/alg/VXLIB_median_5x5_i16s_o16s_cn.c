/*
* module name       : c7x_median_5x5
*
* module descripton : Computes a 5x5 2D-median filter
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#include "VXLIB_median_5x5_i16s_o16s_cn.h"

#define MIN_VAL(a, b) ((a)<(b))?(a):(b)
#define MAX_VAL(a, b) ((a)>(b))?(a):(b)

VXLIB_STATUS VXLIB_median_5x5_i16s_o16s_cn(void *pIn,
                                           VXLIB_bufParams2D_t *pInParams,
                                           void *pOut,
                                           VXLIB_bufParams2D_t *pOutParams)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#ifdef VXLIB_CHECK_PARAMS
    status = VXLIB_median_5x5_i16s_o16s_checkParams_cn(pIn, pInParams, pOut, pOutParams);
    if( status == VXLIB_SUCCESS )
#endif
    {
    int16_t *pSrc, *pDst;
    int32_t i, j, l, m;

    int32_t outCols = pOutParams->dim_x;
    int32_t outRows = pOutParams->dim_y;

    int32_t numBytes;
    int32_t stride_y_in, stride_y_out;

    int16_t tempBuf[6 * 5];

    numBytes = VXLIB_sizeof(pInParams->data_type);
    stride_y_in = pInParams->stride_y / numBytes;

    numBytes = VXLIB_sizeof(pOutParams->data_type);
    stride_y_out = pOutParams->stride_y / numBytes;

    for(j = 0; j < outRows; j+=2)
    {
        for(i = 0; i < outCols; i++)
        {
            int16_t o7;
            int16_t o8;
            int16_t o9;
            int16_t o10;
            int16_t o11;
            int16_t o12;

            pSrc = (int16_t *)pIn  + (j * stride_y_in) + i;
            pDst = (int16_t *)pOut + (j * stride_y_out) + i;

            //Fetch common 20 elements between row 1 and row 5
            for(l = 1; l < 5; l++)
            {
                for(m = 0; m < 5; m++)
                {
                   tempBuf[((l-1) * 5) + m] = pSrc[(l * stride_y_in) + m];
                }
            }

            {
            //Sort Network
            int16_t a0   = MIN_VAL(tempBuf[0], tempBuf[16]);
            int16_t a16  = MAX_VAL(tempBuf[0], tempBuf[16]);
            int16_t a1   = MIN_VAL(tempBuf[1], tempBuf[17]);
            int16_t a17  = MAX_VAL(tempBuf[1], tempBuf[17]);
            int16_t a2   = MIN_VAL(tempBuf[2], tempBuf[18]);
            int16_t a18  = MAX_VAL(tempBuf[2], tempBuf[18]);
            int16_t a3   = MIN_VAL(tempBuf[3], tempBuf[19]);
            int16_t a19  = MAX_VAL(tempBuf[3], tempBuf[19]);

            int16_t b0  = MIN_VAL( a0, tempBuf[8]);
            int16_t b8  = MAX_VAL( a0, tempBuf[8]);
            int16_t b1  = MIN_VAL( a1, tempBuf[9]);
            int16_t b9  = MAX_VAL( a1, tempBuf[9]);
            int16_t b2  = MIN_VAL( a2, tempBuf[10]);
            int16_t b10 = MAX_VAL( a2, tempBuf[10]);
            int16_t b3  = MIN_VAL( a3, tempBuf[11]);
            int16_t b11 = MAX_VAL( a3, tempBuf[11]);

            int16_t b4   = MIN_VAL(tempBuf[4], tempBuf[12]);
            int16_t b12  = MAX_VAL(tempBuf[4], tempBuf[12]);
            int16_t b5   = MIN_VAL(tempBuf[5], tempBuf[13]);
            int16_t b13  = MAX_VAL(tempBuf[5], tempBuf[13]);
            int16_t b6   = MIN_VAL(tempBuf[6], tempBuf[14]);
            int16_t b14  = MAX_VAL(tempBuf[6], tempBuf[14]);
            int16_t b7   = MIN_VAL(tempBuf[7], tempBuf[15]);
            int16_t b15  = MAX_VAL(tempBuf[7], tempBuf[15]);

            int16_t c8  = MIN_VAL( b8,   a16 );
            int16_t c16 = MAX_VAL( b8,   a16 );
            int16_t c9  = MIN_VAL( b9,   a17 );
            int16_t c17 = MAX_VAL( b9,   a17 );
            int16_t c10 = MIN_VAL( b10,  a18 );
            int16_t c18 = MAX_VAL( b10,  a18 );
            int16_t c11 = MIN_VAL( b11,  a19 );
            int16_t c19 = MAX_VAL( b11,  a19 );

            int16_t d0 = MIN_VAL( b0,  b4 );
            int16_t d4 = MAX_VAL( b0,  b4 );
            int16_t d1 = MIN_VAL( b1,  b5 );
            int16_t d5 = MAX_VAL( b1,  b5 );
            int16_t d2 = MIN_VAL( b2,  b6 );
            int16_t d6 = MAX_VAL( b2,  b6 );
            int16_t d3 = MIN_VAL( b3,  b7 );
            int16_t d7 = MAX_VAL( b3,  b7 );

            int16_t d8  = MIN_VAL( c8,   b12 );
            int16_t d12 = MAX_VAL( c8,   b12 );
            int16_t d9  = MIN_VAL( c9,   b13 );
            int16_t d13 = MAX_VAL( c9,   b13 );
            int16_t d10 = MIN_VAL( c10,  b14 );
            int16_t d14 = MAX_VAL( c10,  b14 );
            int16_t d11 = MIN_VAL( c11,  b15 );
            int16_t d15 = MAX_VAL( c11,  b15 );

            int16_t e4  = MIN_VAL( d4,  c16 );
            int16_t e16 = MAX_VAL( d4,  c16 );
            int16_t e5  = MIN_VAL( d5,  c17 );
            int16_t e17 = MAX_VAL( d5,  c17 );
            int16_t e6  = MIN_VAL( d6,  c18 );
            int16_t e18 = MAX_VAL( d6,  c18 );
            int16_t e7  = MIN_VAL( d7,  c19 );
            int16_t e19 = MAX_VAL( d7,  c19 );

            int16_t f4  = MIN_VAL( e4, d8  );
            int16_t f8  = MAX_VAL( e4, d8  );
            int16_t f5  = MIN_VAL( e5, d9  );
            int16_t f9  = MAX_VAL( e5, d9  );
            int16_t f6  = MIN_VAL( e6, d10 );
            int16_t f10 = MAX_VAL( e6, d10 );
            int16_t f7  = MIN_VAL( e7, d11 );
            int16_t f11 = MAX_VAL( e7, d11 );

            int16_t f12 = MIN_VAL( d12 , e16 );
            int16_t f16 = MAX_VAL( d12 , e16 );
            int16_t f13 = MIN_VAL( d13 , e17 );
            int16_t f17 = MAX_VAL( d13 , e17 );
            int16_t f14 = MIN_VAL( d14 , e18 );
            int16_t f18 = MAX_VAL( d14 , e18 );
            int16_t f15 = MIN_VAL( d15 , e19 );
            int16_t f19 = MAX_VAL( d15 , e19 );

            int16_t g0 = MIN_VAL( d0, d2 );
            int16_t g2 = MAX_VAL( d0, d2 );
            int16_t g1 = MIN_VAL( d1, d3 );
            int16_t g3 = MAX_VAL( d1, d3 );

            int16_t g4 = MIN_VAL( f4, f6 );
            int16_t g6 = MAX_VAL( f4, f6 );
            int16_t g5 = MIN_VAL( f5, f7 );
            int16_t g7 = MAX_VAL( f5, f7 );

            int16_t g8  = MIN_VAL( f8, f10 );
            int16_t g10 = MAX_VAL( f8, f10 );
            int16_t g9  = MIN_VAL( f9, f11 );
            int16_t g11 = MAX_VAL( f9, f11 );

            int16_t g12 = MIN_VAL( f12, f14 );
            int16_t g14 = MAX_VAL( f12, f14 );
            int16_t g13 = MIN_VAL( f13, f15 );
            int16_t g15 = MAX_VAL( f13, f15 );

            int16_t g16 = MIN_VAL( f16, f18 );
            int16_t g18 = MAX_VAL( f16, f18 );
            int16_t g17 = MIN_VAL( f17, f19 );
            int16_t g19 = MAX_VAL( f17, f19 );

            int16_t h2  = MIN_VAL( g2, g16 );
            int16_t h16 = MAX_VAL( g2, g16 );
            int16_t h3  = MIN_VAL( g3, g17 );
            int16_t h17 = MAX_VAL( g3, g17 );

            int16_t i2 = MIN_VAL( h2, g8 );
            int16_t i8 = MAX_VAL( h2, g8 );
            int16_t i3 = MIN_VAL( h3, g9 );
            int16_t i9 = MAX_VAL( h3, g9 );

            int16_t i6  = MIN_VAL( g6, g12 );
            int16_t i12 = MAX_VAL( g6, g12 );
            int16_t i7  = MIN_VAL( g7, g13 );
            int16_t i13 = MAX_VAL( g7, g13 );

            int16_t i10 = MIN_VAL( g10, h16 );
            int16_t i16 = MAX_VAL( g10, h16 );
            int16_t i11 = MIN_VAL( g11, h17 );
            int16_t i17 = MAX_VAL( g11, h17 );

            int16_t j2 = MIN_VAL( i2,  g4 );
            int16_t j4 = MAX_VAL( i2,  g4 );
            int16_t j3 = MIN_VAL( i3,  g5 );
            int16_t j5 = MAX_VAL( i3,  g5 );

            int16_t j6 = MIN_VAL( i6,  i8 );
            int16_t j8 = MAX_VAL( i6,  i8 );
            int16_t j7 = MIN_VAL( i7,  i9 );
            int16_t j9 = MAX_VAL( i7,  i9 );

            int16_t j10 = MIN_VAL( i10,  i12 );
            int16_t j12 = MAX_VAL( i10,  i12 );
            int16_t j11 = MIN_VAL( i11,  i13 );
            int16_t j13 = MAX_VAL( i11,  i13 );

            int16_t j14 = MIN_VAL( g14,  i16);
            int16_t j16 = MAX_VAL( g14,  i16);
            int16_t j15 = MIN_VAL( g15,  i17);
            int16_t j17 = MAX_VAL( g15,  i17);

            // truncated stages begin here; not all cmp/swaps are truncated
            int16_t k1 = MAX_VAL( g0, g1 );
            int16_t k3 = MAX_VAL( j2, j3 );
            int16_t k5 = MAX_VAL( j4, j5 );
            int16_t k7 = MAX_VAL( j6, j7 );

            int16_t k8  = MIN_VAL( j8,   j9 );
            int16_t k9  = MAX_VAL( j8,   j9 );
            int16_t k10 = MIN_VAL( j10, j11 );
            int16_t k11 = MAX_VAL( j10, j11 );

            int16_t k12 = MIN_VAL( j12, j13 );
            int16_t k14 = MIN_VAL( j14, j15 );
            int16_t k16 = MIN_VAL( j16, j17 );
            int16_t k18 = MIN_VAL( g18, g19 );

            int16_t l1  = MIN_VAL( k1, k16 );
            int16_t l16 = MAX_VAL( k1, k16 );
            int16_t l3  = MIN_VAL( k3, k18 );
            int16_t l18 = MAX_VAL( k3, k18 );

            int16_t m5  = MIN_VAL( k5, k12 );
            int16_t m12 = MAX_VAL( k5, k12 );
            int16_t m7  = MIN_VAL( k7, k14 );
            int16_t m14 = MAX_VAL( k7, k14 );

            int16_t m8  = MAX_VAL( l1,   k8 );
            int16_t m9  = MIN_VAL( k9,  l16 );
            int16_t m10 = MAX_VAL( l3,  k10 );
            int16_t m11 = MIN_VAL( k11, l18 );

            int16_t n7  = MIN_VAL( m7, m10 );
            int16_t n10 = MAX_VAL( m7, m10 );

            int16_t n8 = MAX_VAL( m5, m8 );

            int16_t n9  = MIN_VAL( m9, m12 );
            int16_t n12 = MAX_VAL( m9, m12 );

            int16_t n11 = MIN_VAL( m11, m14 );

            // Final stage of 20 => 6 sorting network:
            o7  = MIN_VAL( n7,   n8  );
            o8  = MAX_VAL( n7,   n8  );
            o9  = MIN_VAL( n9,   n10 );
            o10 = MAX_VAL( n9,   n10 );
            o11 = MIN_VAL( n11,  n12 );
            o12 = MAX_VAL( n11,  n12 );

//            printf("%d %d %d %d %d %d \n", o7, o8, o9, o10, o11, o12);
            }

            //Fetch row 0 elements
            for(m = 0; m < 5; m++)
            {
                tempBuf[m] = pSrc[m];
            }

            // Upper output (output 0)
            {
            int16_t p1 = MIN_VAL(tempBuf[0], tempBuf[4]);
            int16_t p9 = MAX_VAL(tempBuf[0], tempBuf[4]);

            int16_t q1 = MIN_VAL(p1, tempBuf[2]);
            int16_t q5 = MAX_VAL(p1, tempBuf[2]);
            int16_t q3 = MIN_VAL(tempBuf[1], tempBuf[3]);
            int16_t q7 = MAX_VAL(tempBuf[1], tempBuf[3]);

            int16_t Q5 = MIN_VAL(q5, p9);
            int16_t Q9 = MAX_VAL(q5, p9);

            int16_t r1 = MIN_VAL(q1, q3);
            int16_t r3 = MAX_VAL(q1, q3);
            int16_t r5 = MIN_VAL(Q5, q7);
            int16_t r7 = MAX_VAL(Q5, q7);

            int16_t s3 = MIN_VAL(r3, Q9);
            int16_t s9 = MAX_VAL(r3, Q9);

            int16_t t3 = MIN_VAL(s3, r5);
            int16_t t5 = MAX_VAL(s3, r5);

            int16_t t7 = MIN_VAL(r7, s9);
            int16_t t9 = MAX_VAL(r7, s9);

            int16_t u1 = MAX_VAL(o7, r1);
            int16_t u3 = MAX_VAL(o8, t3);
            int16_t u5 = MAX_VAL(o9, t5);
            int16_t u6 = MIN_VAL(o10, t7);
            int16_t u8 = MIN_VAL(o11, t9);

            int16_t v3 = MIN_VAL(u3, o12);
            int16_t v8 = MAX_VAL(u1, u8);

            int16_t w5 = MIN_VAL(u5, v8);
            int16_t w6 = MAX_VAL(v3, u6);

            int16_t x5 = MIN_VAL(w5, w6);

            pDst[0] = x5;
            }
            //Fetch row 5 elements
            for(m = 0; m < 5; m++)
            {
                tempBuf[m] = pSrc[(5 * stride_y_in) + m];
            }

            // Lower output (output 1)
            {
            int16_t p1 = MIN_VAL(tempBuf[0], tempBuf[4]);
            int16_t p9 = MAX_VAL(tempBuf[0], tempBuf[4]);

            int16_t q1 = MIN_VAL(p1, tempBuf[2]);
            int16_t q5 = MAX_VAL(p1, tempBuf[2]);
            int16_t q3 = MIN_VAL(tempBuf[1], tempBuf[3]);
            int16_t q7 = MAX_VAL(tempBuf[1], tempBuf[3]);

            int16_t Q5 = MIN_VAL(q5, p9);
            int16_t Q9 = MAX_VAL(q5, p9);

            int16_t r1 = MIN_VAL(q1, q3);
            int16_t r3 = MAX_VAL(q1, q3);
            int16_t r5 = MIN_VAL(Q5, q7);
            int16_t r7 = MAX_VAL(Q5, q7);

            int16_t s3 = MIN_VAL(r3, Q9);
            int16_t s9 = MAX_VAL(r3, Q9);

            int16_t t3 = MIN_VAL(s3, r5);
            int16_t t5 = MAX_VAL(s3, r5);

            int16_t t7 = MIN_VAL(r7, s9);
            int16_t t9 = MAX_VAL(r7, s9);

            int16_t u1 = MAX_VAL(o7, r1);
            int16_t u3 = MAX_VAL(o8, t3);
            int16_t u5 = MAX_VAL(o9, t5);
            int16_t u6 = MIN_VAL(o10, t7);
            int16_t u8 = MIN_VAL(o11, t9);

            int16_t v3 = MIN_VAL(u3, o12);
            int16_t v8 = MAX_VAL(u1, u8);

            int16_t w5 = MIN_VAL(u5, v8);
            int16_t w6 = MAX_VAL(v3, u6);

            int16_t x5 = MIN_VAL(w5, w6);

            pDst[stride_y_out] = x5;
            }
        }
    }
    }
    return (status);
}

VXLIB_STATUS VXLIB_median_5x5_i16s_o16s_checkParams_cn(void *pIn,
                                                       VXLIB_bufParams2D_t *pInParams,
                                                       void *pOut,
                                                       VXLIB_bufParams2D_t *pOutParams)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

    return (status);
}
