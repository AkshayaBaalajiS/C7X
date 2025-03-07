/*
* module name       : c7x_median_5x5
*
* module descripton : Computes a 5x5 2D-median filter
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#include "VXLIB_median_5x5_i16s_o16s.h"

#ifdef _DISPLAY_PARAMS
#include "paramv.h"
#endif

#define SIMD_WIDTH_SHIFT       (5) /* 2^5 = 32 16b elements in a 512b vector */
#define SIMD_WIDTH             (1 << SIMD_WIDTH_SHIFT)
#define SIMD_WIDTH_RND         (SIMD_WIDTH >> 1)
#define NUM_SIMD_BLOCKS(width) (((width) >> SIMD_WIDTH_SHIFT) + (((width) - (((width) >> SIMD_WIDTH_SHIFT) << SIMD_WIDTH_SHIFT)) > 0 ? 1 : 0))

#define CONFIG_PARAM_BASE  (0x0000)
#define SE0_PARAM_OFFSET   (CONFIG_PARAM_BASE)
#define SE1_PARAM_OFFSET   (SE0_PARAM_OFFSET + SE_PARAM_SIZE)
#define SA0_PARAM_OFFSET   (SE1_PARAM_OFFSET + SE_PARAM_SIZE)
#define PERM_PARAM_OFFSET  (SA0_PARAM_OFFSET + SA_PARAM_SIZE)

#pragma CODE_SECTION(VXLIB_median_5x5_i16s_o16s_init, ".text:optimized");
VXLIB_STATUS VXLIB_median_5x5_i16s_o16s_init(void *pIn,
                                             VXLIB_bufParams2D_t *pInParams,
                                             void *pOut,
                                             VXLIB_bufParams2D_t *pOutParams,
                                             void *pBlock)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#if defined(VXLIB_CHECK_PARAMS) || defined(VXLIB_MEDIAN_I16S_O16S_CHECK_PARAMS)
    status = VXLIB_median_5x5_i16s_o16s_checkParams(pIn, pInParams, pOut, pOutParams, pBlock);
    if( status == VXLIB_SUCCESS )
#endif
    {
        __STRM_TEMPLATE seTemplate;
        __STRM_TEMPLATE saTemplate;

        __SE_FLAGS seFlags;
        __STRM_PARAM_6D seParam;

        __SA_FLAGS saFlags;
        __STRM_PARAM_4D saParam;

        int32_t numBytes, stride_y;

        int32_t outCols = pOutParams->dim_x;
        int32_t outRows = pOutParams->dim_y;

        numBytes = VXLIB_sizeof(pInParams->data_type);
        stride_y = pInParams->stride_y / numBytes;

        //Prepare SE 0 tempate to fetch Input
        seFlags = __SE_FLAGS_default();

        seFlags.ELETYPE   = __SE_ELETYPE_16BIT;
        seFlags.VECLEN    = __SE_VECLEN_32ELEMS;

        // ITERATION COUNTERS
        seParam.ICNT0 = SIMD_WIDTH;
        seParam.ICNT1 = 5;
        seParam.ICNT2 = 3;
        seParam.ICNT3 = outRows >> 1;
        seParam.ICNT4 = NUM_SIMD_BLOCKS(outCols);
        seParam.ICNT5 = 1;

        // DIMENSIONS IN BYTES
        seParam.DIM1  = 1;
        seParam.DIM2  = stride_y * 2;
        seParam.DIM3  = stride_y * 2;
        seParam.DIM4  = SIMD_WIDTH;
        seParam.DIM5  = 1;

       // SETUP TEMPLATE VECTOR BASED ON SETTINGS
       seTemplate = __SE_SET_PARAM_6D(&seParam, &seFlags);
       *stov_ptr(uint16, (uint32_t *)((uint8_t *)pBlock + SE0_PARAM_OFFSET)) = seTemplate;

        //Prepare SE 1 tempate to fetch Coeff
        seFlags = __SE_FLAGS_default();

        seFlags.ELETYPE   = __SE_ELETYPE_16BIT;
        seFlags.VECLEN    = __SE_VECLEN_32ELEMS;

        // ITERATION COUNTERS
        seParam.ICNT0 = SIMD_WIDTH;
        seParam.ICNT1 = 5;
        seParam.ICNT2 = 3;
        seParam.ICNT3 = outRows >> 1;
        seParam.ICNT4 = NUM_SIMD_BLOCKS(outCols);
        seParam.ICNT5 = 1;

        // DIMENSIONS IN BYTES
        seParam.DIM1  = 1;
        seParam.DIM2  = -stride_y * 2;
        seParam.DIM3  = stride_y * 2;
        seParam.DIM4  = SIMD_WIDTH;
        seParam.DIM5  = 1;

        // SETUP TEMPLATE VECTOR BASED ON SETTINGS
        seTemplate = __SE_SET_PARAM_6D(&seParam, &seFlags);
        *stov_ptr(uint16, (uint32_t *)((uint8_t *)pBlock + SE1_PARAM_OFFSET)) = seTemplate;

        //Prepare SA 0 tempate to store Output
        saFlags = __SA_FLAGS_default();

        saFlags.DECDIM1 = __SA_DECDIM_DIM3;
        saFlags.VECLEN = __SA_VECLEN_32ELEMS;

        numBytes = VXLIB_sizeof(pOutParams->data_type);
        stride_y = pOutParams->stride_y / numBytes;

        // ITERATION COUNTERS
        saParam.DECDIM1_WIDTH = outCols;
        saParam.ICNT0 = SIMD_WIDTH;
        saParam.ICNT1 = 2;
        saParam.ICNT2 = outRows >> 1;
        saParam.ICNT3 = NUM_SIMD_BLOCKS(outCols);

        // DIMENSIONS
        saParam.DIM1  = stride_y;
        saParam.DIM2  = stride_y * 2;
        saParam.DIM3  = SIMD_WIDTH;

        // SETUP TEMPLATE VECTOR BASED ON SETTINGS
        saTemplate = __SA_SET_PARAM_4D(&saParam, &saFlags);
        *stov_ptr(uint16, (uint32_t *)((uint8_t *)pBlock + SA0_PARAM_OFFSET)) = saTemplate;
   }
   return (status);
}

#pragma CODE_SECTION(VXLIB_median_5x5_i16s_o16s_kernel, ".text:optimized");
VXLIB_STATUS VXLIB_median_5x5_i16s_o16s_kernel(void *pIn,
                                               VXLIB_bufParams2D_t *pInParams,
                                               void *pOut,
                                               VXLIB_bufParams2D_t *pOutParams,
                                               void *pBlock)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#if defined(VXLIB_CHECK_PARAMS) || defined(VXLIB_MEDIAN_I16S_O16S_CHECK_PARAMS)
    status = VXLIB_median_5x5_i16s_o16s_checkParams(pIn, pInParams, pOut, pOutParams, pBlock);
    if( status == VXLIB_SUCCESS )
#endif
    {
        uint16 strmTemplate;
        int32_t i, j;

        int32_t outCols = pOutParams->dim_x;
        int32_t outRows = pOutParams->dim_y;

        int32_t numBytes;
        int32_t stride_y_in;

        numBytes = VXLIB_sizeof(pInParams->data_type);
        stride_y_in = pInParams->stride_y / numBytes;

        //Read strmTemplate and open stream 0
        strmTemplate = *stov_ptr(uint16, (uint32_t *)((uint8_t *)pBlock + SE0_PARAM_OFFSET));
        __SE0_OPEN((void*)((int16_t *)pIn + (1 * stride_y_in)), strmTemplate);

#ifdef _DISPLAY_PARAMS
        displaySEParam((void*)((int16_t *)pIn + (1 * stride_y_in)), strmTemplate, PARAMV_SE0);
#endif

        //Read strmTemplate and open stream 1
        strmTemplate = *stov_ptr(uint16, (uint32_t *)((uint8_t *)pBlock + SE1_PARAM_OFFSET));
        __SE1_OPEN((void*)((int16_t *)pIn + (4 * stride_y_in)), strmTemplate);

#ifdef _DISPLAY_PARAMS
        displaySEParam((void*)((int16_t *)pIn + (4 * stride_y_in)), strmTemplate, PARAMV_SE1);
#endif

        //Read strmTemplate and open agen 0
        strmTemplate = *stov_ptr(uint16, (uint32_t *)((uint8_t *)pBlock + SA0_PARAM_OFFSET));
        __SA0_OPEN(strmTemplate);

#ifdef _DISPLAY_PARAMS
        displaySAParam((void*)pOut, strmTemplate, PARAMV_SA0);
#endif

#pragma MUST_ITERATE(1,,)
        for(i = 0; i < outCols; i+=SIMD_WIDTH)
        {
#pragma MUST_ITERATE(1,,)
            for(j = 0; j < outRows; j+=2)
            {
                short32 o7;
                short32 o8;
                short32 o9;
                short32 o10;
                short32 o11;
                short32 o12;

                __vpred vpStore;

                {
                    //Sort Network
                    short32 t0   = __SE1ADV(short32); //pSrc[15];
                    short32 a0   = __min(__SE0(short32), __SE1(short32));       //__min(pSrc[0], pSrc[16]);
                    short32 a16  = __max(__SE0ADV(short32), __SE1ADV(short32)); //__max(pSrc[0], pSrc[16]);
                    short32 a1   = __min(__SE0(short32), __SE1(short32));       //__min(pSrc[1], pSrc[17]);
                    short32 a17  = __max(__SE0ADV(short32), __SE1ADV(short32)); //__max(pSrc[1], pSrc[17]);
                    short32 a2   = __min(__SE0(short32), __SE1(short32));       //__min(pSrc[2], pSrc[18]);
                    short32 a18  = __max(__SE0ADV(short32), __SE1ADV(short32)); //__max(pSrc[2], pSrc[18]);
                    short32 a3   = __min(__SE0(short32), __SE1(short32));       //__min(pSrc[3], pSrc[19]);
                    short32 a19  = __max(__SE0ADV(short32), __SE1ADV(short32)); //__max(pSrc[3], pSrc[19]);

                    short32 t1   = __SE0ADV(short32); //pSrc[4];
                    short32 b2   = __min(a2, __SE0(short32));    //__min( a2, pSrc[10]);
                    short32 b10  = __max(a2, __SE0ADV(short32)); //__max( a2, pSrc[10]);
                    short32 b3   = __min(a3, __SE0(short32));    //__min( a3, pSrc[11]);
                    short32 b11  = __max(a3, __SE0ADV(short32)); //__max( a3, pSrc[11]);
                    short32 b4   = __min(t1, __SE0(short32));       //__min(pSrc[4], pSrc[12]);
                    short32 b12  = __max(t1, __SE0ADV(short32)); //__max(pSrc[4], pSrc[12]);
                    short32 b5   = __min(__SE1(short32), __SE0(short32));       //__min(pSrc[5], pSrc[13]);
                    short32 b13  = __max(__SE1ADV(short32), __SE0ADV(short32)); //__max(pSrc[5], pSrc[13]);
                    short32 b6   = __min(__SE1(short32), __SE0(short32));       //__min(pSrc[6], pSrc[14]);
                    short32 b14  = __max(__SE1ADV(short32), __SE0ADV(short32)); //__max(pSrc[6], pSrc[14]);
                    short32 b7   = __min(__SE1(short32), t0);       //__min(pSrc[7], pSrc[15]);
                    short32 b15  = __max(__SE1ADV(short32), t0); //__max(pSrc[7], pSrc[15]);
                    short32 b0  = __min(a0, __SE1(short32));    //__min( a0, pSrc[8]);
                    short32 b8  = __max(a0, __SE1ADV(short32)); //__max( a0, pSrc[8]);
                    short32 b1  = __min(a1, __SE1(short32));    //__min( a1, pSrc[9]);
                    short32 b9  = __max(a1, __SE1ADV(short32)); //__max( a1, pSrc[9]);

                    short32 c8  = __min( b8,   a16 );
                    short32 c16 = __max( b8,   a16 );
                    short32 c9  = __min( b9,   a17 );
                    short32 c17 = __max( b9,   a17 );
                    short32 c10 = __min( b10,  a18 );
                    short32 c18 = __max( b10,  a18 );
                    short32 c11 = __min( b11,  a19 );
                    short32 c19 = __max( b11,  a19 );

                    short32 d0 = __min( b0,  b4 );
                    short32 d4 = __max( b0,  b4 );
                    short32 d1 = __min( b1,  b5 );
                    short32 d5 = __max( b1,  b5 );
                    short32 d2 = __min( b2,  b6 );
                    short32 d6 = __max( b2,  b6 );
                    short32 d3 = __min( b3,  b7 );
                    short32 d7 = __max( b3,  b7 );

                    short32 d8  = __min( c8,   b12 );
                    short32 d12 = __max( c8,   b12 );
                    short32 d9  = __min( c9,   b13 );
                    short32 d13 = __max( c9,   b13 );
                    short32 d10 = __min( c10,  b14 );
                    short32 d14 = __max( c10,  b14 );
                    short32 d11 = __min( c11,  b15 );
                    short32 d15 = __max( c11,  b15 );

                    short32 e4  = __min( d4,  c16 );
                    short32 e16 = __max( d4,  c16 );
                    short32 e5  = __min( d5,  c17 );
                    short32 e17 = __max( d5,  c17 );
                    short32 e6  = __min( d6,  c18 );
                    short32 e18 = __max( d6,  c18 );
                    short32 e7  = __min( d7,  c19 );
                    short32 e19 = __max( d7,  c19 );

                    short32 f4  = __min( e4, d8  );
                    short32 f8  = __max( e4, d8  );
                    short32 f5  = __min( e5, d9  );
                    short32 f9  = __max( e5, d9  );
                    short32 f6  = __min( e6, d10 );
                    short32 f10 = __max( e6, d10 );
                    short32 f7  = __min( e7, d11 );
                    short32 f11 = __max( e7, d11 );

                    short32 f12 = __min( d12 , e16 );
                    short32 f16 = __max( d12 , e16 );
                    short32 f13 = __min( d13 , e17 );
                    short32 f17 = __max( d13 , e17 );
                    short32 f14 = __min( d14 , e18 );
                    short32 f18 = __max( d14 , e18 );
                    short32 f15 = __min( d15 , e19 );
                    short32 f19 = __max( d15 , e19 );

                    short32 g0 = __min( d0, d2 );
                    short32 g2 = __max( d0, d2 );
                    short32 g1 = __min( d1, d3 );
                    short32 g3 = __max( d1, d3 );

                    short32 g4 = __min( f4, f6 );
                    short32 g6 = __max( f4, f6 );
                    short32 g5 = __min( f5, f7 );
                    short32 g7 = __max( f5, f7 );

                    short32 g8  = __min( f8, f10 );
                    short32 g10 = __max( f8, f10 );
                    short32 g9  = __min( f9, f11 );
                    short32 g11 = __max( f9, f11 );

                    short32 g12 = __min( f12, f14 );
                    short32 g14 = __max( f12, f14 );
                    short32 g13 = __min( f13, f15 );
                    short32 g15 = __max( f13, f15 );

                    short32 g16 = __min( f16, f18 );
                    short32 g18 = __max( f16, f18 );
                    short32 g17 = __min( f17, f19 );
                    short32 g19 = __max( f17, f19 );

                    short32 h2  = __min( g2, g16 );
                    short32 h16 = __max( g2, g16 );
                    short32 h3  = __min( g3, g17 );
                    short32 h17 = __max( g3, g17 );

                    short32 i2 = __min( h2, g8 );
                    short32 i8 = __max( h2, g8 );
                    short32 i3 = __min( h3, g9 );
                    short32 i9 = __max( h3, g9 );

                    short32 i6  = __min( g6, g12 );
                    short32 i12 = __max( g6, g12 );
                    short32 i7  = __min( g7, g13 );
                    short32 i13 = __max( g7, g13 );

                    short32 i10 = __min( g10, h16 );
                    short32 i16 = __max( g10, h16 );
                    short32 i11 = __min( g11, h17 );
                    short32 i17 = __max( g11, h17 );

                    short32 j2 = __min( i2,  g4 );
                    short32 j4 = __max( i2,  g4 );
                    short32 j3 = __min( i3,  g5 );
                    short32 j5 = __max( i3,  g5 );

                    short32 j6 = __min( i6,  i8 );
                    short32 j8 = __max( i6,  i8 );
                    short32 j7 = __min( i7,  i9 );
                    short32 j9 = __max( i7,  i9 );

                    short32 j10 = __min( i10,  i12 );
                    short32 j12 = __max( i10,  i12 );
                    short32 j11 = __min( i11,  i13 );
                    short32 j13 = __max( i11,  i13 );

                    short32 j14 = __min( g14,  i16);
                    short32 j16 = __max( g14,  i16);
                    short32 j15 = __min( g15,  i17);
                    short32 j17 = __max( g15,  i17);

                    // truncated stages begin here; not all cmp/swaps are truncated
                    short32 k1 = __max( g0, g1 );
                    short32 k3 = __max( j2, j3 );
                    short32 k5 = __max( j4, j5 );
                    short32 k7 = __max( j6, j7 );

                    short32 k8  = __min( j8,   j9 );
                    short32 k9  = __max( j8,   j9 );
                    short32 k10 = __min( j10, j11 );
                    short32 k11 = __max( j10, j11 );

                    short32 k12 = __min( j12, j13 );
                    short32 k14 = __min( j14, j15 );
                    short32 k16 = __min( j16, j17 );
                    short32 k18 = __min( g18, g19 );

                    short32 l1  = __min( k1, k16 );
                    short32 l16 = __max( k1, k16 );
                    short32 l3  = __min( k3, k18 );
                    short32 l18 = __max( k3, k18 );

                    short32 m5  = __min( k5, k12 );
                    short32 m12 = __max( k5, k12 );
                    short32 m7  = __min( k7, k14 );
                    short32 m14 = __max( k7, k14 );

                    short32 m8  = __max( l1,   k8 );
                    short32 m9  = __min( k9,  l16 );
                    short32 m10 = __max( l3,  k10 );
                    short32 m11 = __min( k11, l18 );

                    short32 n7  = __min( m7, m10 );
                    short32 n10 = __max( m7, m10 );

                    short32 n8 = __max( m5, m8 );

                    short32 n9  = __min( m9, m12 );
                    short32 n12 = __max( m9, m12 );

                    short32 n11 = __min( m11, m14 );

                    // Final stage of 20 => 6 sorting network:
                    o7  = __min( n7,   n8  );
                    o8  = __max( n7,   n8  );
                    o9  = __min( n9,   n10 );
                    o10 = __max( n9,   n10 );
                    o11 = __min( n11,  n12 );
                    o12 = __max( n11,  n12 );
                }

                // Upper output (output 0)
                {
                    short32 t0 = __SE1ADV(short32); //pSrc[0]
                    short32 t1 = __SE1ADV(short32); //pSrc[1]
                    short32 t2 = __SE1ADV(short32); //pSrc[2]
                    short32 q3 = __min(t1, __SE1(short32));   //__min(pSrc[1], pSrc[3]);
                    short32 q7 = __max(t1, __SE1ADV(short32));//__max(pSrc[1], pSrc[3]);
                    short32 p1 = __min(t0, __SE1(short32));   //__min(pSrc[0], pSrc[4]);
                    short32 p9 = __max(t0, __SE1ADV(short32));//__max(pSrc[0], pSrc[4]);
                    short32 q1 = __min(p1, t2); //__min(p1, pSrc[2]);
                    short32 q5 = __max(p1, t2); //__max(p1, pSrc[2]);
                    short32 Q5 = __min(q5, p9);
                    short32 Q9 = __max(q5, p9);

                    short32 r1 = __min(q1, q3);
                    short32 r3 = __max(q1, q3);
                    short32 r5 = __min(Q5, q7);
                    short32 r7 = __max(Q5, q7);

                    short32 s3 = __min(r3, Q9);
                    short32 s9 = __max(r3, Q9);

                    short32 t3 = __min(s3, r5);
                    short32 t5 = __max(s3, r5);

                    short32 t7 = __min(r7, s9);
                    short32 t9 = __max(r7, s9);

                    short32 u1 = __max(o7, r1);
                    short32 u3 = __max(o8, t3);
                    short32 u5 = __max(o9, t5);
                    short32 u6 = __min(o10, t7);
                    short32 u8 = __min(o11, t9);

                    short32 v3 = __min(u3, o12);
                    short32 v8 = __max(u1, u8);

                    short32 w5 = __min(u5, v8);
                    short32 w6 = __max(v3, u6);

                    short32 x5 = __min(w5, w6);

                    vpStore = __SA0_VPRED(short32);

                    __vstore_pred(vpStore, __SA0ADV(short32, pOut), x5);
                }

                // Lower output (output 1)
                {
                    short32 t0 = __SE0ADV(short32); //pSrc[0]
                    short32 t1 = __SE0ADV(short32); //pSrc[1]
                    short32 t2 = __SE0ADV(short32); //pSrc[2]

                    short32 q3 = __min(t1, __SE0(short32));   //__min(pSrc[1], pSrc[3]);
                    short32 q7 = __max(t1, __SE0ADV(short32));//__max(pSrc[1], pSrc[3]);

                    short32 p1 = __min(t0, __SE0(short32));   //__min(pSrc[0], pSrc[4]);
                    short32 p9 = __max(t0, __SE0ADV(short32));//__max(pSrc[0], pSrc[4]);

                    short32 q1 = __min(p1, t2); //__min(p1, pSrc[2]);
                    short32 q5 = __max(p1, t2); //__max(p1, pSrc[2]);

                    short32 Q5 = __min(q5, p9);
                    short32 Q9 = __max(q5, p9);

                    short32 r1 = __min(q1, q3);
                    short32 r3 = __max(q1, q3);
                    short32 r5 = __min(Q5, q7);
                    short32 r7 = __max(Q5, q7);

                    short32 s3 = __min(r3, Q9);
                    short32 s9 = __max(r3, Q9);

                    short32 t3 = __min(s3, r5);
                    short32 t5 = __max(s3, r5);

                    short32 t7 = __min(r7, s9);
                    short32 t9 = __max(r7, s9);

                    short32 u1 = __max(o7, r1);
                    short32 u3 = __max(o8, t3);
                    short32 u5 = __max(o9, t5);
                    short32 u6 = __min(o10, t7);
                    short32 u8 = __min(o11, t9);

                    short32 v3 = __min(u3, o12);
                    short32 v8 = __max(u1, u8);

                    short32 w5 = __min(u5, v8);
                    short32 w6 = __max(v3, u6);

                    short32 x5 = __min(w5, w6);

                    vpStore = __SA0_VPRED(short32);

                    __vstore_pred(vpStore, __SA0ADV(short32, pOut), x5);

                }
            }
        }

        //Close streams
        __SE0_CLOSE();
        __SE1_CLOSE();

        //Close agen
        __SA0_CLOSE();
    }

    return (status);
}

#pragma CODE_SECTION(VXLIB_median_5x5_i16s_o16s_checkParams, ".text:optimized");
VXLIB_STATUS VXLIB_median_5x5_i16s_o16s_checkParams(void *pIn,
                                                    VXLIB_bufParams2D_t *pInParams,
                                                    void *pOut,
                                                    VXLIB_bufParams2D_t *pOutParams,
                                                    void *pBlock)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

    return (status);

}
