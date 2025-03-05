/*****************************************************************************/
/*  C7X_VPRED.H                                                              */
/*                                                                           */
/* Copyright (c) 2022 Texas Instruments Incorporated                         */
/* http://www.ti.com/                                                        */
/*                                                                           */
/*  Redistribution and  use in source  and binary forms, with  or without    */
/*  modification,  are permitted provided  that the  following conditions    */
/*  are met:                                                                 */
/*                                                                           */
/*     Redistributions  of source  code must  retain the  above copyright    */
/*     notice, this list of conditions and the following disclaimer.         */
/*                                                                           */
/*     Redistributions in binary form  must reproduce the above copyright    */
/*     notice, this  list of conditions  and the following  disclaimer in    */
/*     the  documentation  and/or   other  materials  provided  with  the    */
/*     distribution.                                                         */
/*                                                                           */
/*     Neither the  name of Texas Instruments Incorporated  nor the names    */
/*     of its  contributors may  be used to  endorse or  promote products    */
/*     derived  from   this  software  without   specific  prior  written    */
/*     permission.                                                           */
/*                                                                           */
/*  THIS SOFTWARE  IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS    */
/*  "AS IS"  AND ANY  EXPRESS OR IMPLIED  WARRANTIES, INCLUDING,  BUT NOT    */
/*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR    */
/*  A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT    */
/*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,    */
/*  SPECIAL,  EXEMPLARY,  OR CONSEQUENTIAL  DAMAGES  (INCLUDING, BUT  NOT    */
/*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,    */
/*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY    */
/*  THEORY OF  LIABILITY, WHETHER IN CONTRACT, STRICT  LIABILITY, OR TORT    */
/*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE    */
/*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.     */
/*                                                                           */
/*****************************************************************************/
#ifndef C7X_H_INCLUDE
#error "This file can only be included by parent header c7x.h"
#endif

#ifndef C7X_VPRED_H
#define C7X_VPRED_H

#include <ti_he_impl/c7x_load_stores.h>

/*****************************************************************************/
/* CONVERT TO/FROM A VECTOR PREDICATE FROM/TO A BOOLEAN VECTOR               */
/*                                                                           */
/* Note: Because boolean vectors are always intepreted as vectors of single  */
/* 1-bit values, the corresponding "__vpred" must be interpreted as "char"   */
/* format.  This means that the bits are scaled for halfword, word, or long. */
/*****************************************************************************/
extern __bool2   __create_bool2(__vpred);
extern __bool3   __create_bool3(__vpred);
extern __bool4   __create_bool4(__vpred);
extern __bool8   __create_bool8(__vpred);
extern __bool16  __create_bool16(__vpred);
extern __bool32  __create_bool32(__vpred);
#if __C7X_VEC_SIZE_BITS__ >= 512
extern __bool64  __create_bool64(__vpred);
#endif

extern __vpred  __create_vpred(__bool2);
extern __vpred  __create_vpred(__bool3);
extern __vpred  __create_vpred(__bool4);
extern __vpred  __create_vpred(__bool8);
extern __vpred  __create_vpred(__bool16);
extern __vpred  __create_vpred(__bool32);
#if __C7X_VEC_SIZE_BITS__ >= 512
extern __vpred  __create_vpred(__bool64);
#endif
extern __vpred  __create_vpred(uint64_t);


extern uint64_t  __create_scalar(__vpred);

/*****************************************************************************/
/* VECTOR PREDICATE TO REGISTER INTERFACE                                    */
/*****************************************************************************/
extern __vpred      _mvrp       (int64_t);
extern int64_t      _mvpb       (__vpred);
extern int64_t      _mvph       (__vpred);
extern int64_t      _mvpw       (__vpred);
extern int64_t      _mvpd       (__vpred);

/*****************************************************************************/
/* VECTOR LOADS AND PREDICATED VECTOR LOADS                                  */
/*                                                                           */
/* On C7120 and later devices, implicit predication occurs on loads that use */
/* streaming address generator (SA) operands. If an SA may be used as an     */
/* operand to a load AND that SA may generate predicates with one or more    */
/* predicate bits off, then a predicated load must be used to avoid          */
/* unexpected behavior. Use the following idiom with implicitly predicated   */
/* SA loads:                                                                 */
/*                                                                           */
/* __vpred pred = __SA0_VPRED(char2);                                        */
/* char2* ptr = __SA0ADV(char2, base_ptr);                                   */
/* char2 data = __vload_pred(pred, ptr);                                     */
/*                                                                           */
/* If implicit predication is not available (C7100), the idiom is malformed, */
/* or the compiler fails to optimize the idiom, an equivalent series of      */
/* instructions will instead be generated to load and then predicate.        */
/*****************************************************************************/
/* VLD2B, VLD4B, VLD8B, VLD16B, VLD32B, VLD64B */
/*
int8_t     __vload_pred(__vpred,  const int8_t*);
__char2    __vload_pred(__vpred,  const __char2*);
__char4    __vload_pred(__vpred,  const __char4*);
__char8    __vload_pred(__vpred,  const __char8*);
__char16   __vload_pred(__vpred,  const __char16*);
__char32   __vload_pred(__vpred,  const __char32*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__char64   __vload_pred(__vpred,  const __char64*);
#endif
uint8_t    __vload_pred(__vpred,  const uint8_t*);
__uchar2   __vload_pred(__vpred,  const __uchar2*);
__uchar4   __vload_pred(__vpred,  const __uchar4*);
__uchar8   __vload_pred(__vpred,  const __uchar8*);
__uchar16  __vload_pred(__vpred,  const __uchar16*);
__uchar32  __vload_pred(__vpred,  const __uchar32*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__uchar64  __vload_pred(__vpred,  const __uchar64*);
#endif
*/

/* VLD2H, VLD4H, VLD8H, VLD16H, VLD32H */
/*
int16_t     __vload_pred(__vpred,  const int16_t*);
__short2    __vload_pred(__vpred,  const __short2*);
__short4    __vload_pred(__vpred,  const __short4*);
__short8    __vload_pred(__vpred,  const __short8*);
__short16   __vload_pred(__vpred,  const __short16*);
__short32   __vload_pred(__vpred,  const __short32*);
uint16_t    __vload_pred(__vpred,  const uint16_t*);
__ushort2   __vload_pred(__vpred,  const __ushort2*);
__ushort4   __vload_pred(__vpred,  const __ushort4*);
__ushort8   __vload_pred(__vpred,  const __ushort8*);
__ushort16  __vload_pred(__vpred,  const __ushort16*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__ushort32  __vload_pred(__vpred,  const __ushort32*);
#endif
*/

/* VLDHSWAPB */
/*
__cchar     __vload_pred(__vpred,  const __cchar*);
__cchar2    __vload_pred(__vpred,  const __cchar2*);
__cchar4    __vload_pred(__vpred,  const __cchar4*);
__cchar8    __vload_pred(__vpred,  const __cchar8*);
__cchar16   __vload_pred(__vpred,  const __cchar16*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__cchar32   __vload_pred(__vpred,  const __cchar32*);
#endif
*/

/* VLD2W, VLD4W, VLD8W, VLD16W */
/*
int32_t   __vload_pred(__vpred,  const int32_t*);
__int2    __vload_pred(__vpred,  const __int2*);
__int4    __vload_pred(__vpred,  const __int4*);
__int8    __vload_pred(__vpred,  const __int8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__int16   __vload_pred(__vpred,  const __int16*);
#endif
uint32_t  __vload_pred(__vpred,  const uint32_t*);
__uint2   __vload_pred(__vpred,  const __uint2*);
__uint4   __vload_pred(__vpred,  const __uint4*);
__uint8   __vload_pred(__vpred,  const __uint8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__uint16  __vload_pred(__vpred,  const __uint16*);
#endif
float       __vload_pred(__vpred, const float*);
__float2    __vload_pred(__vpred,  const __float2*);
__float4    __vload_pred(__vpred,  const __float4*);
__float8    __vload_pred(__vpred,  const __float8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__float16   __vload_pred(__vpred,  const __float16*);
#endif
*/

/* VLDWSWAPH */
/*
__cshort     __vload_pred(__vpred,  const __cshort*);
__cshort2    __vload_pred(__vpred,  const __cshort2*);
__cshort4    __vload_pred(__vpred,  const __cshort4*);
__cshort8    __vload_pred(__vpred,  const __cshort8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__cshort16   __vload_pred(__vpred,  const __cshort16*);
#endif
*/

/* VLD1D, VLD2D, VLD4D, VLD8D */
/*
int64_t     __vload_pred(__vpred,  const int64_t*);
__long2    __vload_pred(__vpred,  const __long2*);
__long4    __vload_pred(__vpred,  const __long4*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__long8    __vload_pred(__vpred,  const __long8*);
#endif
uint64_t    __vload_pred(__vpred,  const uint64_t*);
__ulong2   __vload_pred(__vpred,  const __ulong2*);
__ulong4   __vload_pred(__vpred,  const __ulong4*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__ulong8   __vload_pred(__vpred,  const __ulong8*);
#endif
double    __vload_pred(__vpred,  const double*);
__double2    __vload_pred(__vpred,  const __double2*);
__double4    __vload_pred(__vpred,  const __double4*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__double8    __vload_pred(__vpred,  const __double8*);
#endif
*/

/* VLDDSWAPW */
/*
__cint    __vload_pred(__vpred,  const __cint*);
__cint2    __vload_pred(__vpred,  const __cint2*);
__cint4    __vload_pred(__vpred,  const __cint4*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__cint8    __vload_pred(__vpred,  const __cint8*);
#endif
__cfloat    __vload_pred(__vpred,  const __cfloat*);
__cfloat2    __vload_pred(__vpred,  const __cfloat2*);
__cfloat4    __vload_pred(__vpred,  const __cfloat4*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__cfloat8    __vload_pred(__vpred,  const __cfloat8*);
#endif
*/

/* VLDDUP2B, VLDDUP4B, VLDDUP8B, VLDDUP16B, VLDDUP32B, VLDDUP64B */
/*
#if __C7X_VEC_SIZE_BITS__ == 512
__char64       __vload_pred_dup(__vpred,  const __char32*);
__char64       __vload_pred_dup(__vpred,  const __char16*);
__char64       __vload_pred_dup(__vpred,  const __char8*);
__char64       __vload_pred_dup(__vpred,  const __char4*);
__char64       __vload_pred_dup(__vpred,  const __char2*);
__char64       __vload_pred_dup(__vpred,  const int8_t*);
__uchar64      __vload_pred_dup(__vpred,  const __uchar32*);
__uchar64      __vload_pred_dup(__vpred,  const __uchar16*);
__uchar64      __vload_pred_dup(__vpred,  const __uchar8*);
__uchar64      __vload_pred_dup(__vpred,  const __uchar4*);
__uchar64      __vload_pred_dup(__vpred,  const __uchar2*);
__uchar64      __vload_pred_dup(__vpred,  const __uchar*);
#elif __C7X_VEC_SIZE_BITS__ == 256
__char32       __vload_pred_dup(__vpred,  const __char16*);
__char32       __vload_pred_dup(__vpred,  const __char8*);
__char32       __vload_pred_dup(__vpred,  const __char4*);
__char32       __vload_pred_dup(__vpred,  const __char2*);
__char32       __vload_pred_dup(__vpred,  const int8_t*);
__uchar32      __vload_pred_dup(__vpred,  const __uchar16*);
__uchar32      __vload_pred_dup(__vpred,  const __uchar8*);
__uchar32      __vload_pred_dup(__vpred,  const __uchar4*);
__uchar32      __vload_pred_dup(__vpred,  const __uchar2*);
__uchar32      __vload_pred_dup(__vpred,  const __uchar*);
#endif
*/

/* VLDDUP2H, VLDDUP4H, VLDDUP8H, VLDDUP16H, VLDDUP32H */
/*
#if __C7X_VEC_SIZE_BITS__ == 512
__short32      __vload_pred_dup(__vpred,  const __short16*);
__short32      __vload_pred_dup(__vpred,  const __short8*);
__short32      __vload_pred_dup(__vpred,  const __short4*);
__short32      __vload_pred_dup(__vpred,  const __short2*);
__short32      __vload_pred_dup(__vpred,  const int16_t*);
__ushort32     __vload_pred_dup(__vpred,  const __ushort16*);
__ushort32     __vload_pred_dup(__vpred,  const __ushort8*);
__ushort32     __vload_pred_dup(__vpred,  const __ushort4*);
__ushort32     __vload_pred_dup(__vpred,  const __ushort2*);
__ushort32     __vload_pred_dup(__vpred,  const __ushort*);
#elif __C7X_VEC_SIZE_BITS__ == 256
__short16      __vload_pred_dup(__vpred,  const __short8*);
__short16      __vload_pred_dup(__vpred,  const __short4*);
__short16      __vload_pred_dup(__vpred,  const __short2*);
__short16      __vload_pred_dup(__vpred,  const int16_t*);
__ushort16     __vload_pred_dup(__vpred,  const __ushort8*);
__ushort16     __vload_pred_dup(__vpred,  const __ushort4*);
__ushort16     __vload_pred_dup(__vpred,  const __ushort2*);
__ushort16     __vload_pred_dup(__vpred,  const __ushort*);
#endif
*/

/* VLDDUP2W, VLDDUP4W, VLDDUP8W, VLDDUP16W */
/*
#if __C7X_VEC_SIZE_BITS__ == 512
__int16        __vload_pred_dup(__vpred,  const __int8*);
__int16        __vload_pred_dup(__vpred,  const __int4*);
__int16        __vload_pred_dup(__vpred,  const __int2*);
__int16        __vload_pred_dup(__vpred,  const int32_t*);
__uint16       __vload_pred_dup(__vpred,  const __uint8*);
__uint16       __vload_pred_dup(__vpred,  const __uint4*);
__uint16       __vload_pred_dup(__vpred,  const __uint2*);
__uint16       __vload_pred_dup(__vpred,  const __uint*);
__float16      __vload_pred_dup(__vpred,  const __float8*);
__float16      __vload_pred_dup(__vpred,  const __float4*);
__float16      __vload_pred_dup(__vpred,  const __float2*);
__float16      __vload_pred_dup(__vpred,  const float*);
#elif __C7X_VEC_SIZE_BITS__ == 256
__int8        __vload_pred_dup(__vpred,  const __int4*);
__int8        __vload_pred_dup(__vpred,  const __int2*);
__int8        __vload_pred_dup(__vpred,  const int32_t*);
__uint8       __vload_pred_dup(__vpred,  const __uint4*);
__uint8       __vload_pred_dup(__vpred,  const __uint2*);
__uint8       __vload_pred_dup(__vpred,  const __uint*);
__float8      __vload_pred_dup(__vpred,  const __float4*);
__float8      __vload_pred_dup(__vpred,  const __float2*);
__float8      __vload_pred_dup(__vpred,  const float*);
#endif
*/

/* VLDDUP2D, VLDDUP4D, VLDDUP8D */
/*
#if __C7X_VEC_SIZE_BITS__ == 512
__long8        __vload_pred_dup(__vpred,  const __long4*);
__long8        __vload_pred_dup(__vpred,  const __long2*);
__long8        __vload_pred_dup(__vpred,  const int64_t*);
__ulong8       __vload_pred_dup(__vpred,  const __ulong4*);
__ulong8       __vload_pred_dup(__vpred,  const __ulong2*);
__ulong8       __vload_pred_dup(__vpred,  const __ulong*);
__double8      __vload_pred_dup(__vpred,  const __double4*);
__double8      __vload_pred_dup(__vpred,  const __double2*);
__double8      __vload_pred_dup(__vpred,  const double*);
#elif __C7X_VEC_SIZE_BITS__ == 256
__long4        __vload_pred_dup(__vpred,  const __long2*);
__long4        __vload_pred_dup(__vpred,  const int64_t*);
__ulong4       __vload_pred_dup(__vpred,  const __ulong2*);
__ulong4       __vload_pred_dup(__vpred,  const __ulong*);
__double4      __vload_pred_dup(__vpred,  const __double2*);
__double4      __vload_pred_dup(__vpred,  const double*);
#endif
*/

/* VLDDUP4G8H, VLDDUP8G4H */
/*
#if __C7X_VEC_SIZE_BITS__ == 512
__short32      __vload_pred_dup_vec(__vpred,  const __short8*);
__ushort32     __vload_pred_dup_vec(__vpred,  const __ushort8*);
__short32      __vload_pred_dup_vec(__vpred,  const __short4*);
__ushort32     __vload_pred_dup_vec(__vpred,  const __ushort4*);
#endif
*/

/* VLDBUNPKH, VLDBUNPKHU */
/*
int16_t        __vload_pred_unpack_short(__vpred,  const int8_t*);
__short2     __vload_pred_unpack_short(__vpred,  const __char2*);
__short4     __vload_pred_unpack_short(__vpred,  const __char4*);
__short8     __vload_pred_unpack_short(__vpred,  const __char8*);
__short16    __vload_pred_unpack_short(__vpred,  const __char16*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__short32    __vload_pred_unpack_short(__vpred,  const __char32*);
#endif

uint16_t     __vload_pred_unpack_short(__vpred,  const __uchar*);
__ushort2    __vload_pred_unpack_short(__vpred,  const __uchar2*);
__ushort4    __vload_pred_unpack_short(__vpred,  const __uchar4*);
__ushort8    __vload_pred_unpack_short(__vpred,  const __uchar8*);
__ushort16   __vload_pred_unpack_short(__vpred,  const __uchar16*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__ushort32   __vload_pred_unpack_short(__vpred,  const __uchar32*);
#endif
*/

/* VLDBUNPKW, VLDBUNPKWU */
/*
int32_t          __vload_pred_unpack_int(__vpred,  const int8_t*);
__int2       __vload_pred_unpack_int(__vpred,  const __char2*);
__int4       __vload_pred_unpack_int(__vpred,  const __char4*);
__int8       __vload_pred_unpack_int(__vpred,  const __char8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__int16      __vload_pred_unpack_int(__vpred,  const __char16*);
#endif

uint32_t       __vload_pred_unpack_int(__vpred,  const __uchar*);
__uint2      __vload_pred_unpack_int(__vpred,  const __uchar2*);
__uint4      __vload_pred_unpack_int(__vpred,  const __uchar4*);
__uint8      __vload_pred_unpack_int(__vpred,  const __uchar8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__uint16     __vload_pred_unpack_int(__vpred,  const __uchar16*);
#endif
*/

/* VLDHUNPKW, VLDHUNPKWU */
/*
int32_t          __vload_pred_unpack_int(__vpred,  const int16_t*);
__int2       __vload_pred_unpack_int(__vpred,  const __short2*);
__int4       __vload_pred_unpack_int(__vpred,  const __short4*);
__int8       __vload_pred_unpack_int(__vpred,  const __short8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__int16      __vload_pred_unpack_int(__vpred,  const __short16*);
#endif

uint32_t       __vload_pred_unpack_int(__vpred,  const __ushort*);
__uint2      __vload_pred_unpack_int(__vpred,  const __ushort2*);
__uint4      __vload_pred_unpack_int(__vpred,  const __ushort4*);
__uint8      __vload_pred_unpack_int(__vpred,  const __ushort8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__uint16     __vload_pred_unpack_int(__vpred,  const __ushort16*);
#endif
*/

/* VLDBUNPKD, VLDBUNPKDU */
/*
int64_t         __vload_pred_unpack_long(__vpred,  const int8_t*);
__long2      __vload_pred_unpack_long(__vpred,  const __char2*);
__long4      __vload_pred_unpack_long(__vpred,  const __char4*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__long8      __vload_pred_unpack_long(__vpred,  const __char8*);
#endif

uint64_t      __vload_pred_unpack_long(__vpred,  const __uchar*);
__ulong2     __vload_pred_unpack_long(__vpred,  const __uchar2*);
__ulong4     __vload_pred_unpack_long(__vpred,  const __uchar4*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__ulong8     __vload_pred_unpack_long(__vpred,  const __uchar8*);
#endif
*/

/* VLDHUNPKD, VLDHUNPKDU */
/*
int64_t         __vload_pred_unpack_long(__vpred,  const int16_t*);
__long2      __vload_pred_unpack_long(__vpred,  const __short2*);
__long4      __vload_pred_unpack_long(__vpred,  const __short4*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__long8      __vload_pred_unpack_long(__vpred,  const __short8*);
#endif

uint64_t      __vload_pred_unpack_long(__vpred,  const __ushort*);
__ulong2     __vload_pred_unpack_long(__vpred,  const __ushort2*);
__ulong4     __vload_pred_unpack_long(__vpred,  const __ushort4*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__ulong8     __vload_pred_unpack_long(__vpred,  const __ushort8*);
#endif
*/

/* VLDWUNPKD, VLDWUNPKDU */
/*
int64_t         __vload_pred_unpack_long(__vpred,  const int32_t*);
__long2      __vload_pred_unpack_long(__vpred,  const __int2*);
__long4      __vload_pred_unpack_long(__vpred,  const __int4*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__long8      __vload_pred_unpack_long(__vpred,  const __int8*);
#endif
uint64_t      __vload_pred_unpack_long(__vpred,  const __uint*);
__ulong2     __vload_pred_unpack_long(__vpred,  const __uint2*);
__ulong4     __vload_pred_unpack_long(__vpred,  const __uint4*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__ulong8     __vload_pred_unpack_long(__vpred,  const __uint8*);
#endif
*/

/* VLDEBUNPKW, VLDEHUNPKW */
/*
int32_t          __vload_pred_deinterleave_int(__vpred,  const __char2*);
__int2       __vload_pred_deinterleave_int(__vpred,  const __char4*);
__int4       __vload_pred_deinterleave_int(__vpred,  const __char8*);
__int8       __vload_pred_deinterleave_int(__vpred,  const __char16*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__int16      __vload_pred_deinterleave_int(__vpred,  const __char32*);
#endif

int32_t          __vload_pred_deinterleave_int(__vpred,  const __short2*);
__int2       __vload_pred_deinterleave_int(__vpred,  const __short4*);
__int4       __vload_pred_deinterleave_int(__vpred,  const __short8*);
__int8       __vload_pred_deinterleave_int(__vpred,  const __short16*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__int16      __vload_pred_deinterleave_int(__vpred,  const __short32*);
#endif
*/

/* VLDEBUNPKWU, VLDEHUNPKWU */
/*
uint32_t        __vload_pred_deinterleave_int(__vpred,  const __uchar2*);
__uint2       __vload_pred_deinterleave_int(__vpred,  const __uchar4*);
__uint4       __vload_pred_deinterleave_int(__vpred,  const __uchar8*);
__uint8       __vload_pred_deinterleave_int(__vpred,  const __uchar16*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__uint16      __vload_pred_deinterleave_int(__vpred,  const __uchar32*);
#endif

uint32_t        __vload_pred_deinterleave_int(__vpred,  const __ushort2*);
__uint2       __vload_pred_deinterleave_int(__vpred,  const __ushort4*);
__uint4       __vload_pred_deinterleave_int(__vpred,  const __ushort8*);
__uint8       __vload_pred_deinterleave_int(__vpred,  const __ushort16*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__uint16      __vload_pred_deinterleave_int(__vpred,  const __ushort32*);
#endif
*/

/* VLDEBUNPKD, VLDEHUNPKD */
/*
int64_t          __vload_pred_deinterleave_long(__vpred,  const __char2*);
__long2       __vload_pred_deinterleave_long(__vpred,  const __char4*);
__long4       __vload_pred_deinterleave_long(__vpred,  const __char8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__long8       __vload_pred_deinterleave_long(__vpred,  const __char16*);
#endif

int64_t          __vload_pred_deinterleave_long(__vpred,  const __short2*);
__long2       __vload_pred_deinterleave_long(__vpred,  const __short4*);
__long4       __vload_pred_deinterleave_long(__vpred,  const __short8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__long8       __vload_pred_deinterleave_long(__vpred,  const __short16*);
#endif
*/

/* VLDEBUNPKDU, VLDEHUNPKDU */
/*
uint64_t        __vload_pred_deinterleave_long(__vpred,  const __uchar2*);
__ulong2       __vload_pred_deinterleave_long(__vpred,  const __uchar4*);
__ulong4       __vload_pred_deinterleave_long(__vpred,  const __uchar8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__ulong8       __vload_pred_deinterleave_long(__vpred,  const __uchar16*);
#endif

uint64_t        __vload_pred_deinterleave_long(__vpred,  const __ushort2*);
__ulong2       __vload_pred_deinterleave_long(__vpred,  const __ushort4*);
__ulong4       __vload_pred_deinterleave_long(__vpred,  const __ushort8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__ulong8       __vload_pred_deinterleave_long(__vpred,  const __ushort16*);
#endif
*/

/*****************************************************************************/
/* VECTOR STORES AND PREDICATED VECTOR STORES                                */
/*                                                                           */
/* On all C7000 devices, implicit predication occurs on stores that use      */
/* streaming address generator (SA) operands. If an SA may be used as an     */
/* operand to a store AND that SA may generate predicates with one or more   */
/* predicate bits off, then a predicated store must be used to avoid         */
/* unexpected behavior. Use the following idiom with implicitly predicated   */
/* SA stores:                                                                */
/*                                                                           */
/* __vpred pred = __SA0_VPRED(char2);                                        */
/* char2 *ptr = __SA0ADV(char2, base_ptr);                                   */
/* __vstore_pred(pred, ptr, data);                                           */
/*                                                                           */
/* If the idiom is malformed or the compiler fails to optimize the idiom, an */
/* equivalent series of instructions will instead be generated to create the */
/* predicate and then store with explicit predication.                       */
/*****************************************************************************/
/* VSTPINTLB, VSTPINTLH, VSTPINTLW, VSTPINLD - STORES EVERY EVEN ELEMENT */
/*
#if __C7X_VEC_SIZE_BITS__ == 512
void  __vstore_pred_interleave(__vpred,  __char64*,  __char64,  __char64);
void  __vstore_pred_interleave(__vpred,  __short32*, __short32, __short32);
void  __vstore_pred_interleave(__vpred,  __int16*,   __int16,   __int16);
void  __vstore_pred_interleave(__vpred,  __long8*,   __long8,   __long8);
void  __vstore_pred_interleave(__vpred,  __uchar64*, __uchar64, __uchar64);
void  __vstore_pred_interleave(__vpred,  __ushort32*,__ushort32,__ushort32);
void  __vstore_pred_interleave(__vpred,  __uint16*,  __uint16,  __uint16);
void  __vstore_pred_interleave(__vpred,  __ulong8*,  __ulong8,  __ulong8);
#elif __C7X_VEC_SIZE_BITS__ == 256
void  __vstore_pred_interleave(__vpred,  __char32*,  __char32,  __char32);
void  __vstore_pred_interleave(__vpred,  __short16*, __short16, __short16);
void  __vstore_pred_interleave(__vpred,  __int8*,   __int8,   __int8);
void  __vstore_pred_interleave(__vpred,  __long4*,   __long4,   __long4);
void  __vstore_pred_interleave(__vpred,  __uchar32*, __uchar32, __uchar32);
void  __vstore_pred_interleave(__vpred,  __ushort16*,__ushort16,__ushort16);
void  __vstore_pred_interleave(__vpred,  __uint8*,  __uint8,  __uint8);
void  __vstore_pred_interleave(__vpred,  __ulong4*,  __ulong4,  __ulong4);
#endif
*/

/* VSTPINTLB4 - STORES EVERY FOURTH ELEMENT */
/*
#if __C7X_VEC_SIZE_BITS__ == 512
void  __vstore_pred_interleave4(__vpred,  __char32*,  __char64,   __char64);
void  __vstore_pred_interleave4(__vpred,  __uchar32*, __uchar64,  __uchar64);
#elif __C7X_VEC_SIZE_BITS__ == 256
void  __vstore_pred_interleave4(__vpred,  __char16*,  __char32,   __char32);
void  __vstore_pred_interleave4(__vpred,  __uchar16*, __uchar32,  __uchar32);
#endif
*/

#ifndef __C7100__
/* VSTPINTHB, VSTPINTHH, VSTPINTHW, VSTPINTHD - STORES EVERY EVEN ELEMENT */
/*
#if __C7X_VEC_SIZE_BITS__ == 512
void  __vstore_pred_interleave_odd(__vpred,  __char64*,  __char64,  __char64);
void  __vstore_pred_interleave_odd(__vpred,  __short32*, __short32, __short32);
void  __vstore_pred_interleave_odd(__vpred,  __int16*,   __int16,   __int16);
void  __vstore_pred_interleave_odd(__vpred,  __long8*,   __long8,   __long8);
void  __vstore_pred_interleave_odd(__vpred,  __uchar64*, __uchar64, __uchar64);
void  __vstore_pred_interleave_odd(__vpred,  __ushort32*,__ushort32,__ushort32);
void  __vstore_pred_interleave_odd(__vpred,  __uint16*,  __uint16,  __uint16);
void  __vstore_pred_interleave_odd(__vpred,  __ulong8*,  __ulong8,  __ulong8);
#elif __C7X_VEC_SIZE_BITS__ == 256
void  __vstore_pred_interleave_odd(__vpred,  __char32*,  __char32,  __char32);
void  __vstore_pred_interleave_odd(__vpred,  __short16*, __short16, __short16);
void  __vstore_pred_interleave_odd(__vpred,  __int8*,   __int8,   __int8);
void  __vstore_pred_interleave_odd(__vpred,  __long4*,   __long4,   __long4);
void  __vstore_pred_interleave_odd(__vpred,  __uchar32*, __uchar32, __uchar32);
void  __vstore_pred_interleave_odd(__vpred,  __ushort16*,__ushort16,__ushort16);
void  __vstore_pred_interleave_odd(__vpred,  __uint8*,  __uint8,  __uint8);
void  __vstore_pred_interleave_odd(__vpred,  __ulong4*,  __ulong4,  __ulong4);
#endif
*/

/* VSTPLLINTB, VSTPLLINTH, VSTPLLINTW, VSTPLLINTH - STORES LOW VECTOR HALVES */
/*
#if __C7X_VEC_SIZE_BITS__ == 512
void  __vstore_pred_interleave_low_low(__vpred,  __char64*,  __char64,  __char64);
void  __vstore_pred_interleave_low_low(__vpred,  __short32*, __short32, __short32);
void  __vstore_pred_interleave_low_low(__vpred,  __int16*,   __int16,   __int16);
void  __vstore_pred_interleave_low_low(__vpred,  __long8*,   __long8,   __long8);
void  __vstore_pred_interleave_low_low(__vpred,  __uchar64*, __uchar64, __uchar64);
void  __vstore_pred_interleave_low_low(__vpred,  __ushort32*,__ushort32,__ushort32);
void  __vstore_pred_interleave_low_low(__vpred,  __uint16*,  __uint16,  __uint16);
void  __vstore_pred_interleave_low_low(__vpred,  __ulong8*,  __ulong8,  __ulong8);
#elif __C7X_VEC_SIZE_BITS__ == 256
void  __vstore_pred_interleave_low_low(__vpred,  __char32*,  __char32,  __char32);
void  __vstore_pred_interleave_low_low(__vpred,  __short16*, __short16, __short16);
void  __vstore_pred_interleave_low_low(__vpred,  __int8*,   __int8,   __int8);
void  __vstore_pred_interleave_low_low(__vpred,  __long4*,   __long4,   __long4);
void  __vstore_pred_interleave_low_low(__vpred,  __uchar32*, __uchar32, __uchar32);
void  __vstore_pred_interleave_low_low(__vpred,  __ushort16*,__ushort16,__ushort16);
void  __vstore_pred_interleave_low_low(__vpred,  __uint8*,  __uint8,  __uint8);
void  __vstore_pred_interleave_low_low(__vpred,  __ulong4*,  __ulong4,  __ulong4);
#endif
*/

/* VSTPLLINTB, VSTPLLINTH, VSTPLLINTW, VSTPLLINTH - STORES LOW VECTOR HALVES */
/* Convenience form */
/*
#if __C7X_VEC_SIZE_BITS__ == 512
void  __vstore_pred_interleave_low_low(__vpred,  __char64*,  __char32,  __char32);
void  __vstore_pred_interleave_low_low(__vpred,  __short32*, __short16, __short16);
void  __vstore_pred_interleave_low_low(__vpred,  __int16*,   __int8,   __int8);
void  __vstore_pred_interleave_low_low(__vpred,  __long8*,   __long4,   __long4);
void  __vstore_pred_interleave_low_low(__vpred,  __uchar64*, __uchar32, __uchar32);
void  __vstore_pred_interleave_low_low(__vpred,  __ushort32*,__ushort16,__ushort16);
void  __vstore_pred_interleave_low_low(__vpred,  __uint16*,  __uint8,  __uint8);
void  __vstore_pred_interleave_low_low(__vpred,  __ulong8*,  __ulong4,  __ulong4);
#elif __C7X_VEC_SIZE_BITS__ == 256
void  __vstore_pred_interleave_low_low(__vpred,  __char32*,  __char16,  __char16);
void  __vstore_pred_interleave_low_low(__vpred,  __short16*, __short8, __short8);
void  __vstore_pred_interleave_low_low(__vpred,  __int8*,   __int4,   __int4);
void  __vstore_pred_interleave_low_low(__vpred,  __long4*,   __long2,   __long2);
void  __vstore_pred_interleave_low_low(__vpred,  __uchar32*, __uchar16, __uchar16);
void  __vstore_pred_interleave_low_low(__vpred,  __ushort16*,__ushort8,__ushort8);
void  __vstore_pred_interleave_low_low(__vpred,  __uint8*,  __uint4,  __uint4);
void  __vstore_pred_interleave_low_low(__vpred,  __ulong4*,  __ulong2,  __ulong2);
#endif
*/

/* VSTPHHINTB, VSTPHHINTH, VSTPHHINTW, VSTPHHINTH - STORES HIGH VECTOR HALVES */
/*
#if __C7X_VEC_SIZE_BITS__ == 512
void  __vstore_pred_interleave_high_high(__vpred,  __char64*,  __char64,  __char64);
void  __vstore_pred_interleave_high_high(__vpred,  __short32*, __short32, __short32);
void  __vstore_pred_interleave_high_high(__vpred,  __int16*,   __int16,   __int16);
void  __vstore_pred_interleave_high_high(__vpred,  __long8*,   __long8,   __long8);
void  __vstore_pred_interleave_high_high(__vpred,  __uchar64*, __uchar64, __uchar64);
void  __vstore_pred_interleave_high_high(__vpred,  __ushort32*,__ushort32,__ushort32);
void  __vstore_pred_interleave_high_high(__vpred,  __uint16*,  __uint16,  __uint16);
void  __vstore_pred_interleave_high_high(__vpred,  __ulong8*,  __ulong8,  __ulong8);
#elif __C7X_VEC_SIZE_BITS__ == 256
void  __vstore_pred_interleave_high_high(__vpred,  __char32*,  __char32,  __char32);
void  __vstore_pred_interleave_high_high(__vpred,  __short16*, __short16, __short16);
void  __vstore_pred_interleave_high_high(__vpred,  __int8*,   __int8,   __int8);
void  __vstore_pred_interleave_high_high(__vpred,  __long4*,   __long4,   __long4);
void  __vstore_pred_interleave_high_high(__vpred,  __uchar32*, __uchar32, __uchar32);
void  __vstore_pred_interleave_high_high(__vpred,  __ushort16*,__ushort16,__ushort16);
void  __vstore_pred_interleave_high_high(__vpred,  __uint8*,  __uint8,  __uint8);
void  __vstore_pred_interleave_high_high(__vpred,  __ulong4*,  __ulong4,  __ulong4);
#endif
*/
#endif /* ! __C7100__ */

/* VSTP2B, VSTP4B, VSTP8B, VSTP16B, VSTP32B, VSTP64B */
/*
void  __vstore_pred(__vpred,  __char2*,   __char2);
void  __vstore_pred(__vpred,  __char4*,   __char4);
void  __vstore_pred(__vpred,  __char8*,   __char8);
void  __vstore_pred(__vpred,  __char16*,  __char16);
void  __vstore_pred(__vpred,  __char32*,  __char32);
#if __C7X_VEC_SIZE_BITS__ >= 512
void  __vstore_pred(__vpred,  __char64*,  __char64);
#endif
void  __vstore_pred(__vpred,  __uchar2*,  __uchar2);
void  __vstore_pred(__vpred,  __uchar4*,  __uchar4);
void  __vstore_pred(__vpred,  __uchar8*,  __uchar8);
void  __vstore_pred(__vpred,  __uchar16*, __uchar16);
void  __vstore_pred(__vpred,  __uchar32*, __uchar32);
#if __C7X_VEC_SIZE_BITS__ >= 512
void  __vstore_pred(__vpred,  __uchar64*, __uchar64);
#endif
*/

/* VSTP2H, VSTP4H, VSTP8H, VSTP16H, VSTP32H */
/*
void  __vstore_pred(__vpred,  __short2*, __short2);
void  __vstore_pred(__vpred,  __short4*, __short4);
void  __vstore_pred(__vpred,  __short8*, __short8);
void  __vstore_pred(__vpred,  __short16*, __short16);
#if __C7X_VEC_SIZE_BITS__ >= 512
void  __vstore_pred(__vpred,  __short32*, __short32);
#endif
void  __vstore_pred(__vpred,  __ushort2*, __ushort2);
void  __vstore_pred(__vpred,  __ushort4*, __ushort4);
void  __vstore_pred(__vpred,  __ushort8*, __ushort8);
void  __vstore_pred(__vpred,  __ushort16*, __ushort16);
#if __C7X_VEC_SIZE_BITS__ >= 512
void  __vstore_pred(__vpred,  __ushort32*, __ushort32);
#endif
void  __vstore_pred(__vpred,  __cchar2*, __cchar2);
void  __vstore_pred(__vpred,  __cchar4*, __cchar4);
void  __vstore_pred(__vpred,  __cchar8*, __cchar8);
void  __vstore_pred(__vpred,  __cchar16*, __cchar16);
#if __C7X_VEC_SIZE_BITS__ >= 512
void  __vstore_pred(__vpred,  __cchar32*, __cchar32);
#endif
*/

/* VSTP2W, VSTP4W, VSTP8W, VSTP16W */
/*
void  __vstore_pred(__vpred,  __int2*,     __int2);
void  __vstore_pred(__vpred,  __int4*,     __int4);
void  __vstore_pred(__vpred,  __int8*,     __int8);
#if __C7X_VEC_SIZE_BITS__ >= 512
void  __vstore_pred(__vpred,  __int16*,    __int16);
#endif
void  __vstore_pred(__vpred,  __uint2*,    __uint2);
void  __vstore_pred(__vpred,  __uint4*,    __uint4);
void  __vstore_pred(__vpred,  __uint8*,    __uint8);
#if __C7X_VEC_SIZE_BITS__ >= 512
void  __vstore_pred(__vpred,  __uint16*,   __uint16);
#endif
void  __vstore_pred(__vpred,  __float2*,   __float2);
void  __vstore_pred(__vpred,  __float4*,   __float4);
void  __vstore_pred(__vpred,  __float8*,   __float8);
#if __C7X_VEC_SIZE_BITS__ >= 512
void  __vstore_pred(__vpred,  __float16*,  __float16);
#endif
void  __vstore_pred(__vpred,  __cshort2*,  __cshort2);
void  __vstore_pred(__vpred,  __cshort4*,  __cshort4);
void  __vstore_pred(__vpred,  __cshort8*,  __cshort8);
#if __C7X_VEC_SIZE_BITS__ >= 512
void  __vstore_pred(__vpred,  __cshort16*, __cshort16);
#endif
*/

/* VSTP2D, VSTP4D, VSTP8D */
/*
void  __vstore_pred(__vpred,  int64_t*,    int64_t);
void  __vstore_pred(__vpred,  __long2*,   __long2);
void  __vstore_pred(__vpred,  __long4*,   __long4);
#if __C7X_VEC_SIZE_BITS__ >= 512
void  __vstore_pred(__vpred,  __long8*,   __long8);
#endif
void  __vstore_pred(__vpred,  uint64_t*,   uint64_t);
void  __vstore_pred(__vpred,  __ulong2*,  __ulong2);
void  __vstore_pred(__vpred,  __ulong4*,  __ulong4);
#if __C7X_VEC_SIZE_BITS__ >= 512
void  __vstore_pred(__vpred,  __ulong8*,  __ulong8);
#endif
void  __vstore_pred(__vpred,  double*,  double);
void  __vstore_pred(__vpred,  __double2*, __double2);
void  __vstore_pred(__vpred,  __double4*, __double4);
#if __C7X_VEC_SIZE_BITS__ >= 512
void  __vstore_pred(__vpred,  __double8*, __double8);
#endif
void  __vstore_pred(__vpred,  __cint*,    __cint);
void  __vstore_pred(__vpred,  __cint2*,   __cint2);
void  __vstore_pred(__vpred,  __cint4*,   __cint4);
#if __C7X_VEC_SIZE_BITS__ >= 512
void  __vstore_pred(__vpred,  __cint8*,   __cint8);
#endif
void  __vstore_pred(__vpred,  __cfloat*,  __cfloat);
void  __vstore_pred(__vpred,  __cfloat2*, __cfloat2);
void  __vstore_pred(__vpred,  __cfloat4*, __cfloat4);
#if __C7X_VEC_SIZE_BITS__ >= 512
void  __vstore_pred(__vpred,  __cfloat8*, __cfloat8);
#endif
*/

/* VSTPBSVPACKL, VSTPBSVPACKH, VSTPBSVPACKHS1: PRED CORRESPONDS TO SRC DATA */
/*
#if __C7X_VEC_SIZE_BITS__ == 512
void  __vstore_pred_packl(__vpred,    __char32*,  __short32);
void  __vstore_pred_packl(__vpred,    __uchar32*, __ushort32);
void  __vstore_pred_packh(__vpred,    __char32*,  __short32);
void  __vstore_pred_packh(__vpred,    __uchar32*, __ushort32);
void  __vstore_pred_packhs1(__vpred,  __char32*,  __short32);
void  __vstore_pred_packhs1(__vpred,  __uchar32*, __ushort32);
#if __C7X_VEC_SIZE_BITS__ == 256
void  __vstore_pred_packl(__vpred,    __char16*,  __short16);
void  __vstore_pred_packl(__vpred,    __uchar16*, __ushort16);
void  __vstore_pred_packh(__vpred,    __char16*,  __short16);
void  __vstore_pred_packh(__vpred,    __uchar16*, __ushort16);
void  __vstore_pred_packhs1(__vpred,  __char16*,  __short16);
void  __vstore_pred_packhs1(__vpred,  __uchar16*, __ushort16);
#endif
*/

/* VSTPHSVPACKL, VSTPHSVPACKH, VSTPHSVPACKHS1: PRED CORRESPONDS TO SRC DATA */
/*
#if __C7X_VEC_SIZE_BITS__ == 512
void  __vstore_pred_packl(__vpred,    __short16*,  __int16);
void  __vstore_pred_packl(__vpred,    __ushort16*, __uint16);
void  __vstore_pred_packh(__vpred,    __short16*,  __int16);
void  __vstore_pred_packh(__vpred,    __ushort16*, __uint16);
void  __vstore_pred_packhs1(__vpred,  __short16*,  __int16);
void  __vstore_pred_packhs1(__vpred,  __ushort16*, __uint16);
#if __C7X_VEC_SIZE_BITS__ == 256
void  __vstore_pred_packl(__vpred,    __short8*,  __int8);
void  __vstore_pred_packl(__vpred,    __ushort8*, __uint8);
void  __vstore_pred_packh(__vpred,    __short8*,  __int8);
void  __vstore_pred_packh(__vpred,    __ushort8*, __uint8);
void  __vstore_pred_packhs1(__vpred,  __short8*,  __int8);
void  __vstore_pred_packhs1(__vpred,  __ushort8*, __uint8);
#endif
*/

/* VSTPWSVPACKB: PRED CORRESPONDS TO SRC DATA */
#if __C7X_VEC_SIZE_BITS__ == 256
extern void  __vstore_pred_pack_byte(__vpred,  __char8*,  __int8);
extern void  __vstore_pred_pack_byte(__vpred,  __uchar8*, __uint8);
#elif __C7X_VEC_SIZE_BITS__ == 512
extern void  __vstore_pred_pack_byte(__vpred,  __char16*,  __int16);
extern void  __vstore_pred_pack_byte(__vpred,  __uchar16*, __uint16);
#endif


/* VSTPWSVPACKL, VSTPWSVPACKH, VSTPWSVPACKHS1: PRED CORRESPONDS TO SRC DATA */
/*
#if __C7X_VEC_SIZE_BITS__ == 512
void  __vstore_pred_packl(__vpred,    __int8*,  __long8);
void  __vstore_pred_packl(__vpred,    __uint8*, __ulong8);
void  __vstore_pred_packh(__vpred,    __int8*,  __long8);
void  __vstore_pred_packh(__vpred,    __uint8*, __ulong8);
void  __vstore_pred_packhs1(__vpred,  __int8*,  __long8);
void  __vstore_pred_packhs1(__vpred,  __uint8*, __ulong8);
#if __C7X_VEC_SIZE_BITS__ == 256
void  __vstore_pred_packl(__vpred,    __int4*,  __long4);
void  __vstore_pred_packl(__vpred,    __uint4*, __ulong4);
void  __vstore_pred_packh(__vpred,    __int4*,  __long4);
void  __vstore_pred_packh(__vpred,    __uint4*, __ulong4);
void  __vstore_pred_packhs1(__vpred,  __int4*,  __long4);
void  __vstore_pred_packhs1(__vpred,  __uint4*, __ulong4);
#endif
*/

/* VSTPDSVPACKL, VSTPDSVPACKH, VSTPDSVPACKHS1: PRED CORRESPONDS TO SRC DATA */
#if __C7X_VEC_SIZE_BITS__ == 256
extern void  __vstore_pred_packl_long(__vpred,    __long2*,  __long4);
extern void  __vstore_pred_packl_long(__vpred,    __ulong2*, __ulong4);
extern void  __vstore_pred_packh_long(__vpred,    __long2*,  __long4);
extern void  __vstore_pred_packh_long(__vpred,    __ulong2*, __ulong4);
extern void  __vstore_pred_packhs1_long(__vpred,  __long2*,  __long4);
extern void  __vstore_pred_packhs1_long(__vpred,  __ulong2*, __ulong4);
#elif __C7X_VEC_SIZE_BITS__ == 512
extern void  __vstore_pred_packl_long(__vpred,    __long4*,  __long8);
extern void  __vstore_pred_packl_long(__vpred,    __ulong4*, __ulong8);
extern void  __vstore_pred_packh_long(__vpred,    __long4*,  __long8);
extern void  __vstore_pred_packh_long(__vpred,    __ulong4*, __ulong8);
extern void  __vstore_pred_packhs1_long(__vpred,  __long4*,  __long8);
extern void  __vstore_pred_packhs1_long(__vpred,  __ulong4*, __ulong8);
#endif


/* VSTPBPACKL, VSTPBPACKH, VSTPBPACKHS1: PRED CORRESPONDS TO PACKED DATA */
/*
#if __C7X_VEC_SIZE_BITS__ == 512
void  __vstore_pred_packl_2src(__vpred,    __char64*, __short32,  __short32);
void  __vstore_pred_packl_2src(__vpred,    __uchar64*, __ushort32, __ushort32);
void  __vstore_pred_packh_2src(__vpred,    __char64*, __short32,  __short32);
void  __vstore_pred_packh_2src(__vpred,    __uchar64*, __ushort32, __ushort32);
void  __vstore_pred_packhs1_2src(__vpred,  __char64*, __short32,  __short32);
void  __vstore_pred_packhs1_2src(__vpred,  __uchar64*, __ushort32, __ushort32);
#if __C7X_VEC_SIZE_BITS__ == 256
void  __vstore_pred_packl_2src(__vpred,    __char32*, __short16,  __short16);
void  __vstore_pred_packl_2src(__vpred,    __uchar32*, __ushort16, __ushort16);
void  __vstore_pred_packh_2src(__vpred,    __char32*, __short16,  __short16);
void  __vstore_pred_packh_2src(__vpred,    __uchar32*, __ushort16, __ushort16);
void  __vstore_pred_packhs1_2src(__vpred,  __char32*, __short16,  __short16);
void  __vstore_pred_packhs1_2src(__vpred,  __uchar32*, __ushort16, __ushort16);
#endif
*/

/* VSTPHPACKL, VSTPHPACKH, VSTPHPACKHS1: PRED CORRESPONDS TO PACKED DATA */
/*
#if __C7X_VEC_SIZE_BITS__ == 512
void  __vstore_pred_packl_2src(__vpred,    __short32*, __int16,   __int16);
void  __vstore_pred_packl_2src(__vpred,    __ushort32*, __uint16, __uint16);
void  __vstore_pred_packh_2src(__vpred,    __short32*, __int16,   __int16);
void  __vstore_pred_packh_2src(__vpred,    __ushort32*, __uint16, __uint16);
void  __vstore_pred_packhs1_2src(__vpred,  __short32*, __int16,   __int16);
void  __vstore_pred_packhs1_2src(__vpred,  __ushort32*, __uint16, __uint16);
#if __C7X_VEC_SIZE_BITS__ == 256
void  __vstore_pred_packl_2src(__vpred,    __short16*, __int8,   __int8);
void  __vstore_pred_packl_2src(__vpred,    __ushort16*, __uint8, __uint8);
void  __vstore_pred_packh_2src(__vpred,    __short16*, __int8,   __int8);
void  __vstore_pred_packh_2src(__vpred,    __ushort16*, __uint8, __uint8);
void  __vstore_pred_packhs1_2src(__vpred,  __short16*, __int8,   __int8);
void  __vstore_pred_packhs1_2src(__vpred,  __ushort16*, __uint8, __uint8);
#endif
*/

/* VSTPWPACKB: PRED CORRESPONDS TO PACKED DATA */

#if __C7X_VEC_SIZE_BITS__ == 256
extern void  __vstore_pred_pack_byte_2src(__vpred,  __char16*,  __int8,  __int8);
extern void  __vstore_pred_pack_byte_2src(__vpred,  __uchar16*, __uint8, __uint8);
#elif __C7X_VEC_SIZE_BITS__ == 512
extern void __vstore_pred_pack_byte_2src(__vpred, __char32*,  __int16,  __int16);
extern void __vstore_pred_pack_byte_2src(__vpred, __uchar32*, __uint16, __uint16);
#endif


/* VSTPWPACKL, VSTPWPACKH, VSTPWPACKHS1: PRED CORRESPONDS TO PACKED DATA */
/*
#if __C7X_VEC_SIZE_BITS__ == 512
void  __vstore_pred_packl_2src(__vpred,    __int16*, __long8,  __long8);
void  __vstore_pred_packl_2src(__vpred,    __uint16*, __ulong8, __ulong8);
void  __vstore_pred_packh_2src(__vpred,    __int16*, __long8,   __long8);
void  __vstore_pred_packh_2src(__vpred,    __uint16*, __ulong8, __ulong8);
void  __vstore_pred_packhs1_2src(__vpred,  __int16*, __long8,   __long8);
void  __vstore_pred_packhs1_2src(__vpred,  __uint16*, __ulong8, __ulong8);
#if __C7X_VEC_SIZE_BITS__ == 256
void  __vstore_pred_packl_2src(__vpred,    __int8*, __long4,  __long4);
void  __vstore_pred_packl_2src(__vpred,    __uint8*, __ulong4, __ulong4);
void  __vstore_pred_packh_2src(__vpred,    __int8*, __long4,   __long4);
void  __vstore_pred_packh_2src(__vpred,    __uint8*, __ulong4, __ulong4);
void  __vstore_pred_packhs1_2src(__vpred,  __int8*, __long4,   __long4);
void  __vstore_pred_packhs1_2src(__vpred,  __uint8*, __ulong4, __ulong4);
#endif
*/

/* VSTPDPACKL, VSTPDPACKH, VSTPDPACKHS1: PRED CORRESPONDS TO PACKED DATA */
#if __C7X_VEC_SIZE_BITS__ == 256
void  __vstore_pred_packl_long_2src(__vpred,    __long4*, __long4, __long4);
void  __vstore_pred_packl_long_2src(__vpred,    __ulong4*, __ulong4,__ulong4);
void  __vstore_pred_packh_long_2src(__vpred,    __long4*, __long4, __long4);
void  __vstore_pred_packh_long_2src(__vpred,    __ulong4*, __ulong4,__ulong4);
void  __vstore_pred_packhs1_long_2src(__vpred,  __long4*, __long4, __long4);
void  __vstore_pred_packhs1_long_2src(__vpred,  __ulong4*, __ulong4,__ulong4);
#elif __C7X_VEC_SIZE_BITS__ == 512
void  __vstore_pred_packl_long_2src(__vpred,    __long8*, __long8, __long8);
void  __vstore_pred_packl_long_2src(__vpred,    __ulong8*, __ulong8,__ulong8);
void  __vstore_pred_packh_long_2src(__vpred,    __long8*, __long8, __long8);
void  __vstore_pred_packh_long_2src(__vpred,    __ulong8*, __ulong8,__ulong8);
void  __vstore_pred_packhs1_long_2src(__vpred,  __long8*, __long8, __long8);
void  __vstore_pred_packhs1_long_2src(__vpred,  __ulong8*, __ulong8,__ulong8);
#endif


/* VSTPBITRWH */
/*
#if __C7X_VEC_SIZE_BITS__ == 512
void  __vstore_pred_reverse_bit(__vpred,  __cshort16*, __cshort16);
#if __C7X_VEC_SIZE_BITS__ == 256
void  __vstore_pred_reverse_bit(__vpred,  __cshort8*, __cshort8);
#endif
*/

/* VSTPBITRDW */
/*
#if __C7X_VEC_SIZE_BITS__ == 512
void  __vstore_pred_reverse_bit(__vpred,  __cint8*,   __cint8);
void  __vstore_pred_reverse_bit(__vpred,  __cfloat8*, __cfloat8);
#if __C7X_VEC_SIZE_BITS__ == 256
void  __vstore_pred_reverse_bit(__vpred,  __cint4*,   __cint4);
void  __vstore_pred_reverse_bit(__vpred,  __cfloat4*, __cfloat4);
#endif
*/

/* STPREDB  (C syntax):
        __vpred src;
        *(__vpred *)ptr = src;
*/

/* STPREDB - store predicate according to type byte (every bit) */
extern void  __store_predicate_char(uint64_t*, __vpred);

/* STPREDH - store predicate according to type int16_t (every 2-bits) */
extern void  __store_predicate_short(uint32_t*, __vpred);

/* STPREDW - store predicate according to type int32_t (every 4-bits) */
extern void  __store_predicate_int(uint16_t*, __vpred);

/* STPREDD - store predicate according to type int64_t (every 8-bits) */
extern void  __store_predicate_long(uint8_t*, __vpred);


/*----------------------------------------------------------------------------*/
/* ID: __pack_vpred                                                           */
/*----------------------------------------------------------------------------*/
/* Non-Scaling Implementations (cannot vectorize) */

/* BITPACK */
extern __vpred __pack_vpred(uint64_t, uint8_t);
extern __vpred __pack_vpred(__vpred, uint8_t);


/*----------------------------------------------------------------------------*/
/* ID: __expand_vpred                                                         */
/*----------------------------------------------------------------------------*/
/* Non-Scaling Implementations (cannot vectorize) */

/* BITXPND */
extern __vpred __expand_vpred(uint64_t, uint8_t);
extern __vpred __expand_vpred(__vpred, uint8_t);


/* AUTOGEN MARKER */
/*----------------------------------------------------------------------------*/
/* ID: __add                                                                  */
/*----------------------------------------------------------------------------*/

/* VADDCB */
extern int8_t __add(__vpred, int8_t, int8_t);
extern char2 __add(__vpred, char2, char2);
extern char3 __add(__vpred, char3, char3);
extern char4 __add(__vpred, char4, char4);
extern char8 __add(__vpred, char8, char8);
extern char16 __add(__vpred, char16, char16);
extern char32 __add(__vpred, char32, char32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __add(__vpred, char64, char64);
#endif
extern uint8_t __add(__vpred, uint8_t, uint8_t);
extern uchar2 __add(__vpred, uchar2, uchar2);
extern uchar3 __add(__vpred, uchar3, uchar3);
extern uchar4 __add(__vpred, uchar4, uchar4);
extern uchar8 __add(__vpred, uchar8, uchar8);
extern uchar16 __add(__vpred, uchar16, uchar16);
extern uchar32 __add(__vpred, uchar32, uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __add(__vpred, uchar64, uchar64);
#endif

/* VADDCH */
extern int16_t __add(__vpred, int16_t, int16_t);
extern short2 __add(__vpred, short2, short2);
extern short3 __add(__vpred, short3, short3);
extern short4 __add(__vpred, short4, short4);
extern short8 __add(__vpred, short8, short8);
extern short16 __add(__vpred, short16, short16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __add(__vpred, short32, short32);
#endif
extern uint16_t __add(__vpred, uint16_t, uint16_t);
extern ushort2 __add(__vpred, ushort2, ushort2);
extern ushort3 __add(__vpred, ushort3, ushort3);
extern ushort4 __add(__vpred, ushort4, ushort4);
extern ushort8 __add(__vpred, ushort8, ushort8);
extern ushort16 __add(__vpred, ushort16, ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __add(__vpred, ushort32, ushort32);
#endif

/* VADDCW */
extern int32_t __add(__vpred, int32_t, int32_t);
extern int2 __add(__vpred, int2, int2);
extern int3 __add(__vpred, int3, int3);
extern int4 __add(__vpred, int4, int4);
extern int8 __add(__vpred, int8, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __add(__vpred, int16, int16);
#endif
extern uint32_t __add(__vpred, uint32_t, uint32_t);
extern uint2 __add(__vpred, uint2, uint2);
extern uint3 __add(__vpred, uint3, uint3);
extern uint4 __add(__vpred, uint4, uint4);
extern uint8 __add(__vpred, uint8, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __add(__vpred, uint16, uint16);
#endif

/* VADDCD */
extern int64_t __add(__vpred, int64_t, int64_t);
extern long2 __add(__vpred, long2, long2);
extern long3 __add(__vpred, long3, long3);
extern long4 __add(__vpred, long4, long4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __add(__vpred, long8, long8);
#endif
extern uint64_t __add(__vpred, uint64_t, uint64_t);
extern ulong2 __add(__vpred, ulong2, ulong2);
extern ulong3 __add(__vpred, ulong3, ulong3);
extern ulong4 __add(__vpred, ulong4, ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __add(__vpred, ulong8, ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __and                                                                  */
/*----------------------------------------------------------------------------*/

/* AND */
extern __vpred __and(__vpred, __vpred);

/*----------------------------------------------------------------------------*/
/* ID: __andn                                                                 */
/*----------------------------------------------------------------------------*/

/* ANDN */
extern __vpred __andn(__vpred, __vpred);

/*----------------------------------------------------------------------------*/
/* ID: __bit_reverse                                                          */
/*----------------------------------------------------------------------------*/

/* BITR */
extern __vpred __bit_reverse(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __cmp_eq_pred                                                          */
/*----------------------------------------------------------------------------*/

/* VCMPEQB */
extern __vpred __cmp_eq_pred(int8_t, int8_t);
extern __vpred __cmp_eq_pred(char2, char2);
extern __vpred __cmp_eq_pred(char3, char3);
extern __vpred __cmp_eq_pred(char4, char4);
extern __vpred __cmp_eq_pred(char8, char8);
extern __vpred __cmp_eq_pred(char16, char16);
extern __vpred __cmp_eq_pred(char32, char32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __cmp_eq_pred(char64, char64);
#endif
extern __vpred __cmp_eq_pred(uint8_t, uint8_t);
extern __vpred __cmp_eq_pred(uchar2, uchar2);
extern __vpred __cmp_eq_pred(uchar3, uchar3);
extern __vpred __cmp_eq_pred(uchar4, uchar4);
extern __vpred __cmp_eq_pred(uchar8, uchar8);
extern __vpred __cmp_eq_pred(uchar16, uchar16);
extern __vpred __cmp_eq_pred(uchar32, uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __cmp_eq_pred(uchar64, uchar64);
#endif

/* VCMPEQH */
extern __vpred __cmp_eq_pred(int16_t, int16_t);
extern __vpred __cmp_eq_pred(short2, short2);
extern __vpred __cmp_eq_pred(short3, short3);
extern __vpred __cmp_eq_pred(short4, short4);
extern __vpred __cmp_eq_pred(short8, short8);
extern __vpred __cmp_eq_pred(short16, short16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __cmp_eq_pred(short32, short32);
#endif
extern __vpred __cmp_eq_pred(uint16_t, uint16_t);
extern __vpred __cmp_eq_pred(ushort2, ushort2);
extern __vpred __cmp_eq_pred(ushort3, ushort3);
extern __vpred __cmp_eq_pred(ushort4, ushort4);
extern __vpred __cmp_eq_pred(ushort8, ushort8);
extern __vpred __cmp_eq_pred(ushort16, ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __cmp_eq_pred(ushort32, ushort32);
#endif

/* VCMPEQW */
extern __vpred __cmp_eq_pred(int32_t, int32_t);
extern __vpred __cmp_eq_pred(int2, int2);
extern __vpred __cmp_eq_pred(int3, int3);
extern __vpred __cmp_eq_pred(int4, int4);
extern __vpred __cmp_eq_pred(int8, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __cmp_eq_pred(int16, int16);
#endif
extern __vpred __cmp_eq_pred(uint32_t, uint32_t);
extern __vpred __cmp_eq_pred(uint2, uint2);
extern __vpred __cmp_eq_pred(uint3, uint3);
extern __vpred __cmp_eq_pred(uint4, uint4);
extern __vpred __cmp_eq_pred(uint8, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __cmp_eq_pred(uint16, uint16);
#endif

/* VCMPEQSP */
extern __vpred __cmp_eq_pred(float, float);
extern __vpred __cmp_eq_pred(float2, float2);
extern __vpred __cmp_eq_pred(float3, float3);
extern __vpred __cmp_eq_pred(float4, float4);
extern __vpred __cmp_eq_pred(float8, float8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __cmp_eq_pred(float16, float16);
#endif

/* VCMPEQD */
extern __vpred __cmp_eq_pred(int64_t, int64_t);
extern __vpred __cmp_eq_pred(long2, long2);
extern __vpred __cmp_eq_pred(long3, long3);
extern __vpred __cmp_eq_pred(long4, long4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __cmp_eq_pred(long8, long8);
#endif
extern __vpred __cmp_eq_pred(uint64_t, uint64_t);
extern __vpred __cmp_eq_pred(ulong2, ulong2);
extern __vpred __cmp_eq_pred(ulong3, ulong3);
extern __vpred __cmp_eq_pred(ulong4, ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __cmp_eq_pred(ulong8, ulong8);
#endif

/* VCMPEQDP */
extern __vpred __cmp_eq_pred(double, double);
extern __vpred __cmp_eq_pred(double2, double2);
extern __vpred __cmp_eq_pred(double3, double3);
extern __vpred __cmp_eq_pred(double4, double4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __cmp_eq_pred(double8, double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __cmp_ge_pred                                                          */
/*----------------------------------------------------------------------------*/

/* VCMPGEB */
extern __vpred __cmp_ge_pred(int8_t, int8_t);
extern __vpred __cmp_ge_pred(char2, char2);
extern __vpred __cmp_ge_pred(char3, char3);
extern __vpred __cmp_ge_pred(char4, char4);
extern __vpred __cmp_ge_pred(char8, char8);
extern __vpred __cmp_ge_pred(char16, char16);
extern __vpred __cmp_ge_pred(char32, char32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __cmp_ge_pred(char64, char64);
#endif

/* VCMPGEUB */
extern __vpred __cmp_ge_pred(uint8_t, uint8_t);
extern __vpred __cmp_ge_pred(uchar2, uchar2);
extern __vpred __cmp_ge_pred(uchar3, uchar3);
extern __vpred __cmp_ge_pred(uchar4, uchar4);
extern __vpred __cmp_ge_pred(uchar8, uchar8);
extern __vpred __cmp_ge_pred(uchar16, uchar16);
extern __vpred __cmp_ge_pred(uchar32, uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __cmp_ge_pred(uchar64, uchar64);
#endif

/* VCMPGEH */
extern __vpred __cmp_ge_pred(int16_t, int16_t);
extern __vpred __cmp_ge_pred(short2, short2);
extern __vpred __cmp_ge_pred(short3, short3);
extern __vpred __cmp_ge_pred(short4, short4);
extern __vpred __cmp_ge_pred(short8, short8);
extern __vpred __cmp_ge_pred(short16, short16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __cmp_ge_pred(short32, short32);
#endif

/* VCMPGEUH */
extern __vpred __cmp_ge_pred(uint16_t, uint16_t);
extern __vpred __cmp_ge_pred(ushort2, ushort2);
extern __vpred __cmp_ge_pred(ushort3, ushort3);
extern __vpred __cmp_ge_pred(ushort4, ushort4);
extern __vpred __cmp_ge_pred(ushort8, ushort8);
extern __vpred __cmp_ge_pred(ushort16, ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __cmp_ge_pred(ushort32, ushort32);
#endif

/* VCMPGEW */
extern __vpred __cmp_ge_pred(int32_t, int32_t);
extern __vpred __cmp_ge_pred(int2, int2);
extern __vpred __cmp_ge_pred(int3, int3);
extern __vpred __cmp_ge_pred(int4, int4);
extern __vpred __cmp_ge_pred(int8, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __cmp_ge_pred(int16, int16);
#endif

/* VCMPGEUW */
extern __vpred __cmp_ge_pred(uint32_t, uint32_t);
extern __vpred __cmp_ge_pred(uint2, uint2);
extern __vpred __cmp_ge_pred(uint3, uint3);
extern __vpred __cmp_ge_pred(uint4, uint4);
extern __vpred __cmp_ge_pred(uint8, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __cmp_ge_pred(uint16, uint16);
#endif

/* VCMPLESP */
extern __vpred __cmp_ge_pred(float, float);
extern __vpred __cmp_ge_pred(float2, float2);
extern __vpred __cmp_ge_pred(float3, float3);
extern __vpred __cmp_ge_pred(float4, float4);
extern __vpred __cmp_ge_pred(float8, float8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __cmp_ge_pred(float16, float16);
#endif

/* VCMPGED */
extern __vpred __cmp_ge_pred(int64_t, int64_t);
extern __vpred __cmp_ge_pred(long2, long2);
extern __vpred __cmp_ge_pred(long3, long3);
extern __vpred __cmp_ge_pred(long4, long4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __cmp_ge_pred(long8, long8);
#endif

/* VCMPGEUD */
extern __vpred __cmp_ge_pred(uint64_t, uint64_t);
extern __vpred __cmp_ge_pred(ulong2, ulong2);
extern __vpred __cmp_ge_pred(ulong3, ulong3);
extern __vpred __cmp_ge_pred(ulong4, ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __cmp_ge_pred(ulong8, ulong8);
#endif

/* VCMPLEDP */
extern __vpred __cmp_ge_pred(double, double);
extern __vpred __cmp_ge_pred(double2, double2);
extern __vpred __cmp_ge_pred(double3, double3);
extern __vpred __cmp_ge_pred(double4, double4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __cmp_ge_pred(double8, double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __cmp_gt_pred                                                          */
/*----------------------------------------------------------------------------*/

/* VCMPGTB */
extern __vpred __cmp_gt_pred(int8_t, int8_t);
extern __vpred __cmp_gt_pred(char2, char2);
extern __vpred __cmp_gt_pred(char3, char3);
extern __vpred __cmp_gt_pred(char4, char4);
extern __vpred __cmp_gt_pred(char8, char8);
extern __vpred __cmp_gt_pred(char16, char16);
extern __vpred __cmp_gt_pred(char32, char32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __cmp_gt_pred(char64, char64);
#endif

/* VCMPGTUB */
extern __vpred __cmp_gt_pred(uint8_t, uint8_t);
extern __vpred __cmp_gt_pred(uchar2, uchar2);
extern __vpred __cmp_gt_pred(uchar3, uchar3);
extern __vpred __cmp_gt_pred(uchar4, uchar4);
extern __vpred __cmp_gt_pred(uchar8, uchar8);
extern __vpred __cmp_gt_pred(uchar16, uchar16);
extern __vpred __cmp_gt_pred(uchar32, uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __cmp_gt_pred(uchar64, uchar64);
#endif

/* VCMPGTH */
extern __vpred __cmp_gt_pred(int16_t, int16_t);
extern __vpred __cmp_gt_pred(short2, short2);
extern __vpred __cmp_gt_pred(short3, short3);
extern __vpred __cmp_gt_pred(short4, short4);
extern __vpred __cmp_gt_pred(short8, short8);
extern __vpred __cmp_gt_pred(short16, short16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __cmp_gt_pred(short32, short32);
#endif

/* VCMPGTUH */
extern __vpred __cmp_gt_pred(uint16_t, uint16_t);
extern __vpred __cmp_gt_pred(ushort2, ushort2);
extern __vpred __cmp_gt_pred(ushort3, ushort3);
extern __vpred __cmp_gt_pred(ushort4, ushort4);
extern __vpred __cmp_gt_pred(ushort8, ushort8);
extern __vpred __cmp_gt_pred(ushort16, ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __cmp_gt_pred(ushort32, ushort32);
#endif

/* VCMPGTW */
extern __vpred __cmp_gt_pred(int32_t, int32_t);
extern __vpred __cmp_gt_pred(int2, int2);
extern __vpred __cmp_gt_pred(int3, int3);
extern __vpred __cmp_gt_pred(int4, int4);
extern __vpred __cmp_gt_pred(int8, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __cmp_gt_pred(int16, int16);
#endif

/* VCMPGTUW */
extern __vpred __cmp_gt_pred(uint32_t, uint32_t);
extern __vpred __cmp_gt_pred(uint2, uint2);
extern __vpred __cmp_gt_pred(uint3, uint3);
extern __vpred __cmp_gt_pred(uint4, uint4);
extern __vpred __cmp_gt_pred(uint8, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __cmp_gt_pred(uint16, uint16);
#endif

/* VCMPLTSP */
extern __vpred __cmp_gt_pred(float, float);
extern __vpred __cmp_gt_pred(float2, float2);
extern __vpred __cmp_gt_pred(float3, float3);
extern __vpred __cmp_gt_pred(float4, float4);
extern __vpred __cmp_gt_pred(float8, float8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __cmp_gt_pred(float16, float16);
#endif

/* VCMPGTD */
extern __vpred __cmp_gt_pred(int64_t, int64_t);
extern __vpred __cmp_gt_pred(long2, long2);
extern __vpred __cmp_gt_pred(long3, long3);
extern __vpred __cmp_gt_pred(long4, long4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __cmp_gt_pred(long8, long8);
#endif

/* VCMPGTUD */
extern __vpred __cmp_gt_pred(uint64_t, uint64_t);
extern __vpred __cmp_gt_pred(ulong2, ulong2);
extern __vpred __cmp_gt_pred(ulong3, ulong3);
extern __vpred __cmp_gt_pred(ulong4, ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __cmp_gt_pred(ulong8, ulong8);
#endif

/* VCMPLTDP */
extern __vpred __cmp_gt_pred(double, double);
extern __vpred __cmp_gt_pred(double2, double2);
extern __vpred __cmp_gt_pred(double3, double3);
extern __vpred __cmp_gt_pred(double4, double4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __cmp_gt_pred(double8, double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __cmp_le_pred                                                          */
/*----------------------------------------------------------------------------*/

/* VCMPGEB */
extern __vpred __cmp_le_pred(int8_t, int8_t);
extern __vpred __cmp_le_pred(char2, char2);
extern __vpred __cmp_le_pred(char3, char3);
extern __vpred __cmp_le_pred(char4, char4);
extern __vpred __cmp_le_pred(char8, char8);
extern __vpred __cmp_le_pred(char16, char16);
extern __vpred __cmp_le_pred(char32, char32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __cmp_le_pred(char64, char64);
#endif

/* VCMPGEUB */
extern __vpred __cmp_le_pred(uint8_t, uint8_t);
extern __vpred __cmp_le_pred(uchar2, uchar2);
extern __vpred __cmp_le_pred(uchar3, uchar3);
extern __vpred __cmp_le_pred(uchar4, uchar4);
extern __vpred __cmp_le_pred(uchar8, uchar8);
extern __vpred __cmp_le_pred(uchar16, uchar16);
extern __vpred __cmp_le_pred(uchar32, uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __cmp_le_pred(uchar64, uchar64);
#endif

/* VCMPGEH */
extern __vpred __cmp_le_pred(int16_t, int16_t);
extern __vpred __cmp_le_pred(short2, short2);
extern __vpred __cmp_le_pred(short3, short3);
extern __vpred __cmp_le_pred(short4, short4);
extern __vpred __cmp_le_pred(short8, short8);
extern __vpred __cmp_le_pred(short16, short16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __cmp_le_pred(short32, short32);
#endif

/* VCMPGEUH */
extern __vpred __cmp_le_pred(uint16_t, uint16_t);
extern __vpred __cmp_le_pred(ushort2, ushort2);
extern __vpred __cmp_le_pred(ushort3, ushort3);
extern __vpred __cmp_le_pred(ushort4, ushort4);
extern __vpred __cmp_le_pred(ushort8, ushort8);
extern __vpred __cmp_le_pred(ushort16, ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __cmp_le_pred(ushort32, ushort32);
#endif

/* VCMPGEW */
extern __vpred __cmp_le_pred(int32_t, int32_t);
extern __vpred __cmp_le_pred(int2, int2);
extern __vpred __cmp_le_pred(int3, int3);
extern __vpred __cmp_le_pred(int4, int4);
extern __vpred __cmp_le_pred(int8, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __cmp_le_pred(int16, int16);
#endif

/* VCMPGEUW */
extern __vpred __cmp_le_pred(uint32_t, uint32_t);
extern __vpred __cmp_le_pred(uint2, uint2);
extern __vpred __cmp_le_pred(uint3, uint3);
extern __vpred __cmp_le_pred(uint4, uint4);
extern __vpred __cmp_le_pred(uint8, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __cmp_le_pred(uint16, uint16);
#endif

/* VCMPLESP */
extern __vpred __cmp_le_pred(float, float);
extern __vpred __cmp_le_pred(float2, float2);
extern __vpred __cmp_le_pred(float3, float3);
extern __vpred __cmp_le_pred(float4, float4);
extern __vpred __cmp_le_pred(float8, float8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __cmp_le_pred(float16, float16);
#endif

/* VCMPGED */
extern __vpred __cmp_le_pred(int64_t, int64_t);
extern __vpred __cmp_le_pred(long2, long2);
extern __vpred __cmp_le_pred(long3, long3);
extern __vpred __cmp_le_pred(long4, long4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __cmp_le_pred(long8, long8);
#endif

/* VCMPGEUD */
extern __vpred __cmp_le_pred(uint64_t, uint64_t);
extern __vpred __cmp_le_pred(ulong2, ulong2);
extern __vpred __cmp_le_pred(ulong3, ulong3);
extern __vpred __cmp_le_pred(ulong4, ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __cmp_le_pred(ulong8, ulong8);
#endif

/* VCMPLEDP */
extern __vpred __cmp_le_pred(double, double);
extern __vpred __cmp_le_pred(double2, double2);
extern __vpred __cmp_le_pred(double3, double3);
extern __vpred __cmp_le_pred(double4, double4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __cmp_le_pred(double8, double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __cmp_lt_pred                                                          */
/*----------------------------------------------------------------------------*/

/* VCMPGTB */
extern __vpred __cmp_lt_pred(int8_t, int8_t);
extern __vpred __cmp_lt_pred(char2, char2);
extern __vpred __cmp_lt_pred(char3, char3);
extern __vpred __cmp_lt_pred(char4, char4);
extern __vpred __cmp_lt_pred(char8, char8);
extern __vpred __cmp_lt_pred(char16, char16);
extern __vpred __cmp_lt_pred(char32, char32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __cmp_lt_pred(char64, char64);
#endif

/* VCMPGTUB */
extern __vpred __cmp_lt_pred(uint8_t, uint8_t);
extern __vpred __cmp_lt_pred(uchar2, uchar2);
extern __vpred __cmp_lt_pred(uchar3, uchar3);
extern __vpred __cmp_lt_pred(uchar4, uchar4);
extern __vpred __cmp_lt_pred(uchar8, uchar8);
extern __vpred __cmp_lt_pred(uchar16, uchar16);
extern __vpred __cmp_lt_pred(uchar32, uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __cmp_lt_pred(uchar64, uchar64);
#endif

/* VCMPGTH */
extern __vpred __cmp_lt_pred(int16_t, int16_t);
extern __vpred __cmp_lt_pred(short2, short2);
extern __vpred __cmp_lt_pred(short3, short3);
extern __vpred __cmp_lt_pred(short4, short4);
extern __vpred __cmp_lt_pred(short8, short8);
extern __vpred __cmp_lt_pred(short16, short16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __cmp_lt_pred(short32, short32);
#endif

/* VCMPGTUH */
extern __vpred __cmp_lt_pred(uint16_t, uint16_t);
extern __vpred __cmp_lt_pred(ushort2, ushort2);
extern __vpred __cmp_lt_pred(ushort3, ushort3);
extern __vpred __cmp_lt_pred(ushort4, ushort4);
extern __vpred __cmp_lt_pred(ushort8, ushort8);
extern __vpred __cmp_lt_pred(ushort16, ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __cmp_lt_pred(ushort32, ushort32);
#endif

/* VCMPGTW */
extern __vpred __cmp_lt_pred(int32_t, int32_t);
extern __vpred __cmp_lt_pred(int2, int2);
extern __vpred __cmp_lt_pred(int3, int3);
extern __vpred __cmp_lt_pred(int4, int4);
extern __vpred __cmp_lt_pred(int8, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __cmp_lt_pred(int16, int16);
#endif

/* VCMPGTUW */
extern __vpred __cmp_lt_pred(uint32_t, uint32_t);
extern __vpred __cmp_lt_pred(uint2, uint2);
extern __vpred __cmp_lt_pred(uint3, uint3);
extern __vpred __cmp_lt_pred(uint4, uint4);
extern __vpred __cmp_lt_pred(uint8, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __cmp_lt_pred(uint16, uint16);
#endif

/* VCMPLTSP */
extern __vpred __cmp_lt_pred(float, float);
extern __vpred __cmp_lt_pred(float2, float2);
extern __vpred __cmp_lt_pred(float3, float3);
extern __vpred __cmp_lt_pred(float4, float4);
extern __vpred __cmp_lt_pred(float8, float8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __cmp_lt_pred(float16, float16);
#endif

/* VCMPGTD */
extern __vpred __cmp_lt_pred(int64_t, int64_t);
extern __vpred __cmp_lt_pred(long2, long2);
extern __vpred __cmp_lt_pred(long3, long3);
extern __vpred __cmp_lt_pred(long4, long4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __cmp_lt_pred(long8, long8);
#endif

/* VCMPGTUD */
extern __vpred __cmp_lt_pred(uint64_t, uint64_t);
extern __vpred __cmp_lt_pred(ulong2, ulong2);
extern __vpred __cmp_lt_pred(ulong3, ulong3);
extern __vpred __cmp_lt_pred(ulong4, ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __cmp_lt_pred(ulong8, ulong8);
#endif

/* VCMPLTDP */
extern __vpred __cmp_lt_pred(double, double);
extern __vpred __cmp_lt_pred(double2, double2);
extern __vpred __cmp_lt_pred(double3, double3);
extern __vpred __cmp_lt_pred(double4, double4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __cmp_lt_pred(double8, double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __compress_set_bits_left                                               */
/*----------------------------------------------------------------------------*/

/* COMPRESSL */
extern __vpred __compress_set_bits_left(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __compress_set_bits_right                                              */
/*----------------------------------------------------------------------------*/

/* COMPRESSR */
extern __vpred __compress_set_bits_right(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __decimate_char                                                        */
/*----------------------------------------------------------------------------*/

/* DECIMATEB */
extern __vpred __decimate_char(__vpred, __vpred);

/*----------------------------------------------------------------------------*/
/* ID: __decimate_int                                                         */
/*----------------------------------------------------------------------------*/

/* DECIMATEW */
extern __vpred __decimate_int(__vpred, __vpred);

/*----------------------------------------------------------------------------*/
/* ID: __decimate_long                                                        */
/*----------------------------------------------------------------------------*/

/* DECIMATED */
extern __vpred __decimate_long(__vpred, __vpred);

/*----------------------------------------------------------------------------*/
/* ID: __decimate_short                                                       */
/*----------------------------------------------------------------------------*/

/* DECIMATEH */
extern __vpred __decimate_short(__vpred, __vpred);

/*----------------------------------------------------------------------------*/
/* ID: __duplicate_pred_high_char                                             */
/*----------------------------------------------------------------------------*/

/* PDUPH2B */
extern __vpred __duplicate_pred_high_char(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __duplicate_pred_high_int                                              */
/*----------------------------------------------------------------------------*/

/* PDUPH2W */
extern __vpred __duplicate_pred_high_int(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __duplicate_pred_high_long                                             */
/*----------------------------------------------------------------------------*/

/* PDUPH2D */
extern __vpred __duplicate_pred_high_long(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __duplicate_pred_high_short                                            */
/*----------------------------------------------------------------------------*/

/* PDUPH2H */
extern __vpred __duplicate_pred_high_short(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __duplicate_pred_low_char                                              */
/*----------------------------------------------------------------------------*/

/* PDUPL2B */
extern __vpred __duplicate_pred_low_char(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __duplicate_pred_low_int                                               */
/*----------------------------------------------------------------------------*/

/* PDUPL2W */
extern __vpred __duplicate_pred_low_int(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __duplicate_pred_low_long                                              */
/*----------------------------------------------------------------------------*/

/* PDUPL2D */
extern __vpred __duplicate_pred_low_long(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __duplicate_pred_low_short                                             */
/*----------------------------------------------------------------------------*/

/* PDUPL2H */
extern __vpred __duplicate_pred_low_short(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __expand                                                               */
/*----------------------------------------------------------------------------*/

/* VPXPND */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __expand(__vpred);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __expand(__vpred);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __gather_set_bits                                                      */
/*----------------------------------------------------------------------------*/

/* VGATHERB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __gather_set_bits(__vpred, char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __gather_set_bits(__vpred, char64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __gather_unset_bits                                                    */
/*----------------------------------------------------------------------------*/

/* VGATHERNB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __gather_unset_bits(__vpred, char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __gather_unset_bits(__vpred, char64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __mask_char                                                            */
/*----------------------------------------------------------------------------*/

/* MASKB */
extern __vpred __mask_char(uint8_t/*(k={0-63})*/);
extern __vpred __mask_char(uint32_t);

/*----------------------------------------------------------------------------*/
/* ID: __mask_int                                                             */
/*----------------------------------------------------------------------------*/

/* MASKW */
extern __vpred __mask_int(uint8_t/*(k={0-63})*/);
extern __vpred __mask_int(uint32_t);

/*----------------------------------------------------------------------------*/
/* ID: __mask_long                                                            */
/*----------------------------------------------------------------------------*/

/* MASKD */
extern __vpred __mask_long(uint8_t/*(k={0-63})*/);
extern __vpred __mask_long(uint32_t);

/*----------------------------------------------------------------------------*/
/* ID: __mask_short                                                           */
/*----------------------------------------------------------------------------*/

/* MASKH */
extern __vpred __mask_short(uint8_t/*(k={0-63})*/);
extern __vpred __mask_short(uint32_t);

/*----------------------------------------------------------------------------*/
/* ID: __max_circ_pred                                                        */
/*----------------------------------------------------------------------------*/

/* VCMAXPB */
extern void __max_circ_pred(int8_t, int8_t&, __vpred&);
extern void __max_circ_pred(char2, char2&, __vpred&);
extern void __max_circ_pred(char3, char3&, __vpred&);
extern void __max_circ_pred(char4, char4&, __vpred&);
extern void __max_circ_pred(char8, char8&, __vpred&);
extern void __max_circ_pred(char16, char16&, __vpred&);
extern void __max_circ_pred(char32, char32&, __vpred&);
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __max_circ_pred(char64, char64&, __vpred&);
#endif

/* VCMAXPH */
extern void __max_circ_pred(int16_t, int16_t&, __vpred&);
extern void __max_circ_pred(short2, short2&, __vpred&);
extern void __max_circ_pred(short3, short3&, __vpred&);
extern void __max_circ_pred(short4, short4&, __vpred&);
extern void __max_circ_pred(short8, short8&, __vpred&);
extern void __max_circ_pred(short16, short16&, __vpred&);
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __max_circ_pred(short32, short32&, __vpred&);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __max_index                                                            */
/*----------------------------------------------------------------------------*/

/* VMAXPB */
extern void __max_index(int8_t, int8_t&, __vpred&);
extern void __max_index(char2, char2&, __vpred&);
extern void __max_index(char3, char3&, __vpred&);
extern void __max_index(char4, char4&, __vpred&);
extern void __max_index(char8, char8&, __vpred&);
extern void __max_index(char16, char16&, __vpred&);
extern void __max_index(char32, char32&, __vpred&);
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __max_index(char64, char64&, __vpred&);
#endif

/* VMAXUPB */
extern void __max_index(uint8_t, uint8_t&, __vpred&);
extern void __max_index(uchar2, uchar2&, __vpred&);
extern void __max_index(uchar3, uchar3&, __vpred&);
extern void __max_index(uchar4, uchar4&, __vpred&);
extern void __max_index(uchar8, uchar8&, __vpred&);
extern void __max_index(uchar16, uchar16&, __vpred&);
extern void __max_index(uchar32, uchar32&, __vpred&);
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __max_index(uchar64, uchar64&, __vpred&);
#endif

/* VMAXPH */
extern void __max_index(int16_t, int16_t&, __vpred&);
extern void __max_index(short2, short2&, __vpred&);
extern void __max_index(short3, short3&, __vpred&);
extern void __max_index(short4, short4&, __vpred&);
extern void __max_index(short8, short8&, __vpred&);
extern void __max_index(short16, short16&, __vpred&);
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __max_index(short32, short32&, __vpred&);
#endif

/* VMAXUPH */
extern void __max_index(uint16_t, uint16_t&, __vpred&);
extern void __max_index(ushort2, ushort2&, __vpred&);
extern void __max_index(ushort3, ushort3&, __vpred&);
extern void __max_index(ushort4, ushort4&, __vpred&);
extern void __max_index(ushort8, ushort8&, __vpred&);
extern void __max_index(ushort16, ushort16&, __vpred&);
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __max_index(ushort32, ushort32&, __vpred&);
#endif

/* VMAXPW */
extern void __max_index(int32_t, int32_t&, __vpred&);
extern void __max_index(int2, int2&, __vpred&);
extern void __max_index(int3, int3&, __vpred&);
extern void __max_index(int4, int4&, __vpred&);
extern void __max_index(int8, int8&, __vpred&);
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __max_index(int16, int16&, __vpred&);
#endif

/* VMAXUPW */
extern void __max_index(uint32_t, uint32_t&, __vpred&);
extern void __max_index(uint2, uint2&, __vpred&);
extern void __max_index(uint3, uint3&, __vpred&);
extern void __max_index(uint4, uint4&, __vpred&);
extern void __max_index(uint8, uint8&, __vpred&);
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __max_index(uint16, uint16&, __vpred&);
#endif

/* VMAXPD */
extern void __max_index(int64_t, int64_t&, __vpred&);
extern void __max_index(long2, long2&, __vpred&);
extern void __max_index(long3, long3&, __vpred&);
extern void __max_index(long4, long4&, __vpred&);
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __max_index(long8, long8&, __vpred&);
#endif

/* VMAXUPD */
extern void __max_index(uint64_t, uint64_t&, __vpred&);
extern void __max_index(ulong2, ulong2&, __vpred&);
extern void __max_index(ulong3, ulong3&, __vpred&);
extern void __max_index(ulong4, ulong4&, __vpred&);
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __max_index(ulong8, ulong8&, __vpred&);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __min_index                                                            */
/*----------------------------------------------------------------------------*/

/* VMINPB */
extern void __min_index(int8_t, int8_t&, __vpred&);
extern void __min_index(char2, char2&, __vpred&);
extern void __min_index(char3, char3&, __vpred&);
extern void __min_index(char4, char4&, __vpred&);
extern void __min_index(char8, char8&, __vpred&);
extern void __min_index(char16, char16&, __vpred&);
extern void __min_index(char32, char32&, __vpred&);
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __min_index(char64, char64&, __vpred&);
#endif

/* VMINUPB */
extern void __min_index(uint8_t, uint8_t&, __vpred&);
extern void __min_index(uchar2, uchar2&, __vpred&);
extern void __min_index(uchar3, uchar3&, __vpred&);
extern void __min_index(uchar4, uchar4&, __vpred&);
extern void __min_index(uchar8, uchar8&, __vpred&);
extern void __min_index(uchar16, uchar16&, __vpred&);
extern void __min_index(uchar32, uchar32&, __vpred&);
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __min_index(uchar64, uchar64&, __vpred&);
#endif

/* VMINPH */
extern void __min_index(int16_t, int16_t&, __vpred&);
extern void __min_index(short2, short2&, __vpred&);
extern void __min_index(short3, short3&, __vpred&);
extern void __min_index(short4, short4&, __vpred&);
extern void __min_index(short8, short8&, __vpred&);
extern void __min_index(short16, short16&, __vpred&);
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __min_index(short32, short32&, __vpred&);
#endif

/* VMINUPH */
extern void __min_index(uint16_t, uint16_t&, __vpred&);
extern void __min_index(ushort2, ushort2&, __vpred&);
extern void __min_index(ushort3, ushort3&, __vpred&);
extern void __min_index(ushort4, ushort4&, __vpred&);
extern void __min_index(ushort8, ushort8&, __vpred&);
extern void __min_index(ushort16, ushort16&, __vpred&);
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __min_index(ushort32, ushort32&, __vpred&);
#endif

/* VMINPW */
extern void __min_index(int32_t, int32_t&, __vpred&);
extern void __min_index(int2, int2&, __vpred&);
extern void __min_index(int3, int3&, __vpred&);
extern void __min_index(int4, int4&, __vpred&);
extern void __min_index(int8, int8&, __vpred&);
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __min_index(int16, int16&, __vpred&);
#endif

/* VMINUPW */
extern void __min_index(uint32_t, uint32_t&, __vpred&);
extern void __min_index(uint2, uint2&, __vpred&);
extern void __min_index(uint3, uint3&, __vpred&);
extern void __min_index(uint4, uint4&, __vpred&);
extern void __min_index(uint8, uint8&, __vpred&);
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __min_index(uint16, uint16&, __vpred&);
#endif

/* VMINPD */
extern void __min_index(int64_t, int64_t&, __vpred&);
extern void __min_index(long2, long2&, __vpred&);
extern void __min_index(long3, long3&, __vpred&);
extern void __min_index(long4, long4&, __vpred&);
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __min_index(long8, long8&, __vpred&);
#endif

/* VMINUPD */
extern void __min_index(uint64_t, uint64_t&, __vpred&);
extern void __min_index(ulong2, ulong2&, __vpred&);
extern void __min_index(ulong3, ulong3&, __vpred&);
extern void __min_index(ulong4, ulong4&, __vpred&);
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __min_index(ulong8, ulong8&, __vpred&);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __nand                                                                 */
/*----------------------------------------------------------------------------*/

/* NAND */
extern __vpred __nand(__vpred, __vpred);

/*----------------------------------------------------------------------------*/
/* ID: __negate                                                               */
/*----------------------------------------------------------------------------*/

/* NOT */
extern __vpred __negate(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __nor                                                                  */
/*----------------------------------------------------------------------------*/

/* NOR */
extern __vpred __nor(__vpred, __vpred);

/*----------------------------------------------------------------------------*/
/* ID: __or                                                                   */
/*----------------------------------------------------------------------------*/

/* OR */
extern __vpred __or(__vpred, __vpred);

/*----------------------------------------------------------------------------*/
/* ID: __orn                                                                  */
/*----------------------------------------------------------------------------*/

/* ORN */
extern __vpred __orn(__vpred, __vpred);

/*----------------------------------------------------------------------------*/
/* ID: __parallel_pack_dup_16way                                              */
/*----------------------------------------------------------------------------*/

/* VPPACKDUP16W */
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __parallel_pack_dup_16way(__vpred);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __parallel_pack_dup_8way                                               */
/*----------------------------------------------------------------------------*/

/* VPPACKDUP8W */
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __parallel_pack_dup_8way(__vpred);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __popcount_char                                                        */
/*----------------------------------------------------------------------------*/

/* PBITCNTB */
extern uint32_t __popcount_char(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __popcount_gather_char                                                 */
/*----------------------------------------------------------------------------*/

/* PCNTGATHERB */
extern void __popcount_gather_char(__vpred, uint32_t&, __vpred&);

/*----------------------------------------------------------------------------*/
/* ID: __popcount_gather_int                                                  */
/*----------------------------------------------------------------------------*/

/* PCNTGATHERW */
extern void __popcount_gather_int(__vpred, uint32_t&, __vpred&);

/*----------------------------------------------------------------------------*/
/* ID: __popcount_gather_long                                                 */
/*----------------------------------------------------------------------------*/

/* PCNTGATHERD */
extern void __popcount_gather_long(__vpred, uint32_t&, __vpred&);

/*----------------------------------------------------------------------------*/
/* ID: __popcount_gather_short                                                */
/*----------------------------------------------------------------------------*/

/* PCNTGATHERH */
extern void __popcount_gather_short(__vpred, uint32_t&, __vpred&);

/*----------------------------------------------------------------------------*/
/* ID: __popcount_int                                                         */
/*----------------------------------------------------------------------------*/

/* PBITCNTW */
extern uint32_t __popcount_int(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __popcount_long                                                        */
/*----------------------------------------------------------------------------*/

/* PBITCNTD */
extern uint32_t __popcount_long(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __popcount_short                                                       */
/*----------------------------------------------------------------------------*/

/* PBITCNTH */
extern uint32_t __popcount_short(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __rightmost_bit_detect_char                                            */
/*----------------------------------------------------------------------------*/

/* PRMBDB */
extern uint32_t __rightmost_bit_detect_char(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __rightmost_bit_detect_int                                             */
/*----------------------------------------------------------------------------*/

/* PRMBDW */
extern uint32_t __rightmost_bit_detect_int(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __rightmost_bit_detect_long                                            */
/*----------------------------------------------------------------------------*/

/* PRMBDD */
extern uint32_t __rightmost_bit_detect_long(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __rightmost_bit_detect_short                                           */
/*----------------------------------------------------------------------------*/

/* PRMBDH */
extern uint32_t __rightmost_bit_detect_short(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __scatter_set_bits                                                     */
/*----------------------------------------------------------------------------*/

/* VSCATTERB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __scatter_set_bits(__vpred, char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __scatter_set_bits(__vpred, char64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __scatter_unset_bits                                                   */
/*----------------------------------------------------------------------------*/

/* VSCATTERNB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __scatter_unset_bits(__vpred, char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __scatter_unset_bits(__vpred, char64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __select                                                               */
/*----------------------------------------------------------------------------*/

/* VSEL */
extern int8_t __select(__vpred, int8_t, int8_t);
extern char2 __select(__vpred, char2, char2);
extern char3 __select(__vpred, char3, char3);
extern char4 __select(__vpred, char4, char4);
extern char8 __select(__vpred, char8, char8);
extern char16 __select(__vpred, char16, char16);
extern char32 __select(__vpred, char32, char32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __select(__vpred, char64, char64);
#endif
extern uint8_t __select(__vpred, uint8_t, uint8_t);
extern uchar2 __select(__vpred, uchar2, uchar2);
extern uchar3 __select(__vpred, uchar3, uchar3);
extern uchar4 __select(__vpred, uchar4, uchar4);
extern uchar8 __select(__vpred, uchar8, uchar8);
extern uchar16 __select(__vpred, uchar16, uchar16);
extern uchar32 __select(__vpred, uchar32, uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __select(__vpred, uchar64, uchar64);
#endif
extern cchar __select(__vpred, cchar, cchar);
extern cchar2 __select(__vpred, cchar2, cchar2);
extern cchar4 __select(__vpred, cchar4, cchar4);
extern cchar8 __select(__vpred, cchar8, cchar8);
extern cchar16 __select(__vpred, cchar16, cchar16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern cchar32 __select(__vpred, cchar32, cchar32);
#endif
extern int16_t __select(__vpred, int16_t, int16_t);
extern short2 __select(__vpred, short2, short2);
extern short3 __select(__vpred, short3, short3);
extern short4 __select(__vpred, short4, short4);
extern short8 __select(__vpred, short8, short8);
extern short16 __select(__vpred, short16, short16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __select(__vpred, short32, short32);
#endif
extern uint16_t __select(__vpred, uint16_t, uint16_t);
extern ushort2 __select(__vpred, ushort2, ushort2);
extern ushort3 __select(__vpred, ushort3, ushort3);
extern ushort4 __select(__vpred, ushort4, ushort4);
extern ushort8 __select(__vpred, ushort8, ushort8);
extern ushort16 __select(__vpred, ushort16, ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __select(__vpred, ushort32, ushort32);
#endif
extern cshort __select(__vpred, cshort, cshort);
extern cshort2 __select(__vpred, cshort2, cshort2);
extern cshort4 __select(__vpred, cshort4, cshort4);
extern cshort8 __select(__vpred, cshort8, cshort8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern cshort16 __select(__vpred, cshort16, cshort16);
#endif
extern int32_t __select(__vpred, int32_t, int32_t);
/* int32_t __select(__vpred, int32_t, int32_t(k)); */
extern int2 __select(__vpred, int2, int2);
/* int2 __select(__vpred, int2, int2(k)); */
extern int3 __select(__vpred, int3, int3);
/* int3 __select(__vpred, int3, int3(k)); */
extern int4 __select(__vpred, int4, int4);
/* int4 __select(__vpred, int4, int4(k)); */
extern int8 __select(__vpred, int8, int8);
/* int8 __select(__vpred, int8, int8(k)); */
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __select(__vpred, int16, int16);
/* int16 __select(__vpred, int16, int16(k)); */
#endif
extern uint32_t __select(__vpred, uint32_t, uint32_t);
/* uint32_t __select(__vpred, uint32_t, uint32_t(k)); */
extern uint2 __select(__vpred, uint2, uint2);
/* uint2 __select(__vpred, uint2, uint2(k)); */
extern uint3 __select(__vpred, uint3, uint3);
/* uint3 __select(__vpred, uint3, uint3(k)); */
extern uint4 __select(__vpred, uint4, uint4);
/* uint4 __select(__vpred, uint4, uint4(k)); */
extern uint8 __select(__vpred, uint8, uint8);
/* uint8 __select(__vpred, uint8, uint8(k)); */
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __select(__vpred, uint16, uint16);
/* uint16 __select(__vpred, uint16, uint16(k)); */
#endif
extern float __select(__vpred, float, float);
/* float __select(__vpred, float, float(k)); */
extern float2 __select(__vpred, float2, float2);
/* float2 __select(__vpred, float2, float2(k)); */
extern float3 __select(__vpred, float3, float3);
/* float3 __select(__vpred, float3, float3(k)); */
extern float4 __select(__vpred, float4, float4);
/* float4 __select(__vpred, float4, float4(k)); */
extern float8 __select(__vpred, float8, float8);
/* float8 __select(__vpred, float8, float8(k)); */
#if __C7X_VEC_SIZE_BITS__ == 512
extern float16 __select(__vpred, float16, float16);
/* float16 __select(__vpred, float16, float16(k)); */
#endif
extern cint __select(__vpred, cint, cint);
extern cint2 __select(__vpred, cint2, cint2);
extern cint4 __select(__vpred, cint4, cint4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern cint8 __select(__vpred, cint8, cint8);
#endif
extern cfloat __select(__vpred, cfloat, cfloat);
extern cfloat2 __select(__vpred, cfloat2, cfloat2);
extern cfloat4 __select(__vpred, cfloat4, cfloat4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern cfloat8 __select(__vpred, cfloat8, cfloat8);
#endif
extern int64_t __select(__vpred, int64_t, int64_t);
extern long2 __select(__vpred, long2, long2);
extern long3 __select(__vpred, long3, long3);
extern long4 __select(__vpred, long4, long4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __select(__vpred, long8, long8);
#endif
extern uint64_t __select(__vpred, uint64_t, uint64_t);
extern ulong2 __select(__vpred, ulong2, ulong2);
extern ulong3 __select(__vpred, ulong3, ulong3);
extern ulong4 __select(__vpred, ulong4, ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __select(__vpred, ulong8, ulong8);
#endif
extern double __select(__vpred, double, double);
extern double2 __select(__vpred, double2, double2);
extern double3 __select(__vpred, double3, double3);
extern double4 __select(__vpred, double4, double4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern double8 __select(__vpred, double8, double8);
#endif
extern clong __select(__vpred, clong, clong);
extern clong2 __select(__vpred, clong2, clong2);
#if __C7X_VEC_SIZE_BITS__ == 512
extern clong4 __select(__vpred, clong4, clong4);
#endif
extern cdouble __select(__vpred, cdouble, cdouble);
extern cdouble2 __select(__vpred, cdouble2, cdouble2);
#if __C7X_VEC_SIZE_BITS__ == 512
extern cdouble4 __select(__vpred, cdouble4, cdouble4);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __shift_left_conditional                                               */
/*----------------------------------------------------------------------------*/

/* VSHLCB */
extern int8_t __shift_left_conditional(__vpred, int8_t, int8_t);
extern char2 __shift_left_conditional(__vpred, char2, char2);
extern char3 __shift_left_conditional(__vpred, char3, char3);
extern char4 __shift_left_conditional(__vpred, char4, char4);
extern char8 __shift_left_conditional(__vpred, char8, char8);
extern char16 __shift_left_conditional(__vpred, char16, char16);
extern char32 __shift_left_conditional(__vpred, char32, char32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __shift_left_conditional(__vpred, char64, char64);
#endif
extern uint8_t __shift_left_conditional(__vpred, uint8_t, uint8_t);
extern uchar2 __shift_left_conditional(__vpred, uchar2, uchar2);
extern uchar3 __shift_left_conditional(__vpred, uchar3, uchar3);
extern uchar4 __shift_left_conditional(__vpred, uchar4, uchar4);
extern uchar8 __shift_left_conditional(__vpred, uchar8, uchar8);
extern uchar16 __shift_left_conditional(__vpred, uchar16, uchar16);
extern uchar32 __shift_left_conditional(__vpred, uchar32, uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __shift_left_conditional(__vpred, uchar64, uchar64);
#endif

/* VSHLCH */
extern int16_t __shift_left_conditional(__vpred, int16_t, int16_t);
extern short2 __shift_left_conditional(__vpred, short2, short2);
extern short3 __shift_left_conditional(__vpred, short3, short3);
extern short4 __shift_left_conditional(__vpred, short4, short4);
extern short8 __shift_left_conditional(__vpred, short8, short8);
extern short16 __shift_left_conditional(__vpred, short16, short16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __shift_left_conditional(__vpred, short32, short32);
#endif
extern uint16_t __shift_left_conditional(__vpred, uint16_t, uint16_t);
extern ushort2 __shift_left_conditional(__vpred, ushort2, ushort2);
extern ushort3 __shift_left_conditional(__vpred, ushort3, ushort3);
extern ushort4 __shift_left_conditional(__vpred, ushort4, ushort4);
extern ushort8 __shift_left_conditional(__vpred, ushort8, ushort8);
extern ushort16 __shift_left_conditional(__vpred, ushort16, ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __shift_left_conditional(__vpred, ushort32, ushort32);
#endif

/* VSHLCW */
extern int32_t __shift_left_conditional(__vpred, int32_t, int32_t);
extern int2 __shift_left_conditional(__vpred, int2, int2);
extern int3 __shift_left_conditional(__vpred, int3, int3);
extern int4 __shift_left_conditional(__vpred, int4, int4);
extern int8 __shift_left_conditional(__vpred, int8, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __shift_left_conditional(__vpred, int16, int16);
#endif
extern uint32_t __shift_left_conditional(__vpred, uint32_t, uint32_t);
extern uint2 __shift_left_conditional(__vpred, uint2, uint2);
extern uint3 __shift_left_conditional(__vpred, uint3, uint3);
extern uint4 __shift_left_conditional(__vpred, uint4, uint4);
extern uint8 __shift_left_conditional(__vpred, uint8, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __shift_left_conditional(__vpred, uint16, uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __xnor                                                                 */
/*----------------------------------------------------------------------------*/

/* XNOR */
extern __vpred __xnor(__vpred, __vpred);

/*----------------------------------------------------------------------------*/
/* ID: __xor                                                                  */
/*----------------------------------------------------------------------------*/

/* XOR */
extern __vpred __xor(__vpred, __vpred);

/* AUTOGEN MARKER */

#endif /* C7X_VPRED_H */
