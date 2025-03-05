/*****************************************************************************/
/*  C7X_VPRED.H                                                              */
/*                                                                           */
/* Copyright (c) 2015 Texas Instruments Incorporated                         */
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
#ifndef __C7X_H_INCLUDE__
#error "This file can only be included by parent header c7x.h"
#endif

#ifndef __C7X_VPRED_H
#define __C7X_VPRED_H

/*****************************************************************************/
/* CONVERT TO/FROM A VECTOR PREDICATE FROM/TO A BOOLEAN VECTOR               */
/*                                                                           */
/* Note: Because boolean vectors are always interpreted as vectors of single */
/* 1-bit values, the corresponding "__vpred" must be interpreted as "char"   */
/* format.  This means that the bits are scaled for halfword, word, or long. */
/*****************************************************************************/
__bool2  __OVBIF __create_bool2(__vpred);
__bool3  __OVBIF __create_bool3(__vpred);
__bool4  __OVBIF __create_bool4(__vpred);
__bool8  __OVBIF __create_bool8(__vpred);
__bool16 __OVBIF __create_bool16(__vpred);
__bool32 __OVBIF __create_bool32(__vpred);
#if __C7X_VEC_SIZE_BITS__ >= 512
__bool64 __OVBIF __create_bool64(__vpred);
#endif

__vpred __OVBIF __create_vpred(__bool2);
__vpred __OVBIF __create_vpred(__bool3);
__vpred __OVBIF __create_vpred(__bool4);
__vpred __OVBIF __create_vpred(__bool8);
__vpred __OVBIF __create_vpred(__bool16);
__vpred __OVBIF __create_vpred(__bool32);
#if __C7X_VEC_SIZE_BITS__ >= 512
__vpred __OVBIF __create_vpred(__bool64);
#endif
__vpred __OVBIF __create_vpred(__ulong);

__ulong __OVBIF __create_scalar(__vpred);

/*****************************************************************************/
/* VECTOR PREDICATE TO REGISTER INTERFACE                                    */
/*****************************************************************************/
__vpred  __BIF _mvrp       (long);
long     __BIF _mvpb       (__vpred);
long     __BIF _mvph       (__vpred);
long     __BIF _mvpw       (__vpred);
long     __BIF _mvpd       (__vpred);

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
signed char    __OVBIF __vload_pred(__vpred, __RD const signed char*);
__char2   __OVBIF __vload_pred(__vpred, __RD const __char2*);
__char4   __OVBIF __vload_pred(__vpred, __RD const __char4*);
__char8   __OVBIF __vload_pred(__vpred, __RD const __char8*);
__char16  __OVBIF __vload_pred(__vpred, __RD const __char16*);
__char32  __OVBIF __vload_pred(__vpred, __RD const __char32*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__char64  __OVBIF __vload_pred(__vpred, __RD const __char64*);
#endif
unsigned char   __OVBIF __vload_pred(__vpred, __RD const unsigned char*);
__uchar2  __OVBIF __vload_pred(__vpred, __RD const __uchar2*);
__uchar4  __OVBIF __vload_pred(__vpred, __RD const __uchar4*);
__uchar8  __OVBIF __vload_pred(__vpred, __RD const __uchar8*);
__uchar16 __OVBIF __vload_pred(__vpred, __RD const __uchar16*);
__uchar32 __OVBIF __vload_pred(__vpred, __RD const __uchar32*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__uchar64 __OVBIF __vload_pred(__vpred, __RD const __uchar64*);
#endif

/* VLD2H, VLD4H, VLD8H, VLD16H, VLD32H */
short      __OVBIF __vload_pred(__vpred, __RD const short*);
__short2   __OVBIF __vload_pred(__vpred, __RD const __short2*);
__short4   __OVBIF __vload_pred(__vpred, __RD const __short4*);
__short8   __OVBIF __vload_pred(__vpred, __RD const __short8*);
__short16  __OVBIF __vload_pred(__vpred, __RD const __short16*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__short32  __OVBIF __vload_pred(__vpred, __RD const __short32*);
#endif
unsigned short    __OVBIF __vload_pred(__vpred, __RD const unsigned short*);
__ushort2  __OVBIF __vload_pred(__vpred, __RD const __ushort2*);
__ushort4  __OVBIF __vload_pred(__vpred, __RD const __ushort4*);
__ushort8  __OVBIF __vload_pred(__vpred, __RD const __ushort8*);
__ushort16 __OVBIF __vload_pred(__vpred, __RD const __ushort16*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__ushort32 __OVBIF __vload_pred(__vpred, __RD const __ushort32*);
#endif

/* VLDHSWAPB */
__cchar   __OVBIF __vload_pred(__vpred, __RD const __cchar*);
__cchar2   __OVBIF __vload_pred(__vpred, __RD const __cchar2*);
__cchar4   __OVBIF __vload_pred(__vpred, __RD const __cchar4*);
__cchar8   __OVBIF __vload_pred(__vpred, __RD const __cchar8*);
__cchar16  __OVBIF __vload_pred(__vpred, __RD const __cchar16*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__cchar32  __OVBIF __vload_pred(__vpred, __RD const __cchar32*);
#endif

/* VLD2W, VLD4W, VLD8W, VLD16W */
int      __OVBIF __vload_pred(__vpred, __RD const int*);
__int2   __OVBIF __vload_pred(__vpred, __RD const __int2*);
__int4   __OVBIF __vload_pred(__vpred, __RD const __int4*);
__int8   __OVBIF __vload_pred(__vpred, __RD const __int8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__int16  __OVBIF __vload_pred(__vpred, __RD const __int16*);
#endif

unsigned int  __OVBIF __vload_pred(__vpred, __RD const unsigned int*);
__uint2  __OVBIF __vload_pred(__vpred, __RD const __uint2*);
__uint4  __OVBIF __vload_pred(__vpred, __RD const __uint4*);
__uint8  __OVBIF __vload_pred(__vpred, __RD const __uint8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__uint16 __OVBIF __vload_pred(__vpred, __RD const __uint16*);
#endif

float      __OVBIF __vload_pred(__vpred, __RD const float*);
__float2   __OVBIF __vload_pred(__vpred, __RD const __float2*);
__float4   __OVBIF __vload_pred(__vpred, __RD const __float4*);
__float8   __OVBIF __vload_pred(__vpred, __RD const __float8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__float16  __OVBIF __vload_pred(__vpred, __RD const __float16*);
#endif

/* VLDWSWAPH */
__cshort   __OVBIF __vload_pred(__vpred, __RD const __cshort*);
__cshort2   __OVBIF __vload_pred(__vpred, __RD const __cshort2*);
__cshort4   __OVBIF __vload_pred(__vpred, __RD const __cshort4*);
__cshort8   __OVBIF __vload_pred(__vpred, __RD const __cshort8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__cshort16  __OVBIF __vload_pred(__vpred, __RD const __cshort16*);
#endif

/* VLD1D, VLD2D, VLD4D, VLD8D */
long      __OVBIF __vload_pred(__vpred, __RD const long*);
__long2   __OVBIF __vload_pred(__vpred, __RD const __long2*);
__long4   __OVBIF __vload_pred(__vpred, __RD const __long4*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__long8   __OVBIF __vload_pred(__vpred, __RD const __long8*);
#endif
unsigned long  __OVBIF __vload_pred(__vpred, __RD const unsigned long*);
__ulong   __OVBIF __vload_pred(__vpred, __RD const __ulong*);
__ulong2  __OVBIF __vload_pred(__vpred, __RD const __ulong2*);
__ulong4  __OVBIF __vload_pred(__vpred, __RD const __ulong4*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__ulong8  __OVBIF __vload_pred(__vpred, __RD const __ulong8*);
#endif
double      __OVBIF __vload_pred(__vpred, __RD const double*);
__double2   __OVBIF __vload_pred(__vpred, __RD const __double2*);
__double4   __OVBIF __vload_pred(__vpred, __RD const __double4*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__double8   __OVBIF __vload_pred(__vpred, __RD const __double8*);
#endif

/* VLDDSWAPW */
__cint   __OVBIF __vload_pred(__vpred, __RD const __cint*);
__cint2   __OVBIF __vload_pred(__vpred, __RD const __cint2*);
__cint4   __OVBIF __vload_pred(__vpred, __RD const __cint4*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__cint8   __OVBIF __vload_pred(__vpred, __RD const __cint8*);
#endif
__cfloat   __OVBIF __vload_pred(__vpred, __RD const __cfloat*);
__cfloat2   __OVBIF __vload_pred(__vpred, __RD const __cfloat2*);
__cfloat4   __OVBIF __vload_pred(__vpred, __RD const __cfloat4*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__cfloat8   __OVBIF __vload_pred(__vpred, __RD const __cfloat8*);
#endif

/* VLDDUP2B, VLDDUP4B, VLDDUP8B, VLDDUP16B, VLDDUP32B, VLDDUP64B */
#if __C7X_VEC_SIZE_BITS__ == 512
__char64      __OVBIF __vload_pred_dup(__vpred, __RD const __char32*);
__char64      __OVBIF __vload_pred_dup(__vpred, __RD const __char16*);
__char64      __OVBIF __vload_pred_dup(__vpred, __RD const __char8*);
__char64      __OVBIF __vload_pred_dup(__vpred, __RD const __char4*);
__char64      __OVBIF __vload_pred_dup(__vpred, __RD const __char2*);
__char64      __OVBIF __vload_pred_dup(__vpred, __RD const signed char*);
__uchar64     __OVBIF __vload_pred_dup(__vpred, __RD const __uchar32*);
__uchar64     __OVBIF __vload_pred_dup(__vpred, __RD const __uchar16*);
__uchar64     __OVBIF __vload_pred_dup(__vpred, __RD const __uchar8*);
__uchar64     __OVBIF __vload_pred_dup(__vpred, __RD const __uchar4*);
__uchar64     __OVBIF __vload_pred_dup(__vpred, __RD const __uchar2*);
__uchar64     __OVBIF __vload_pred_dup(__vpred, __RD const __uchar*);
#elif __C7X_VEC_SIZE_BITS__ == 256
__char32      __OVBIF __vload_pred_dup(__vpred, __RD const __char16*);
__char32      __OVBIF __vload_pred_dup(__vpred, __RD const __char8*);
__char32      __OVBIF __vload_pred_dup(__vpred, __RD const __char4*);
__char32      __OVBIF __vload_pred_dup(__vpred, __RD const __char2*);
__char32      __OVBIF __vload_pred_dup(__vpred, __RD const signed char*);
__uchar32     __OVBIF __vload_pred_dup(__vpred, __RD const __uchar16*);
__uchar32     __OVBIF __vload_pred_dup(__vpred, __RD const __uchar8*);
__uchar32     __OVBIF __vload_pred_dup(__vpred, __RD const __uchar4*);
__uchar32     __OVBIF __vload_pred_dup(__vpred, __RD const __uchar2*);
__uchar32     __OVBIF __vload_pred_dup(__vpred, __RD const __uchar*);
#endif

/* VLDDUP2H, VLDDUP4H, VLDDUP8H, VLDDUP16H, VLDDUP32H */
#if __C7X_VEC_SIZE_BITS__ == 512
__short32     __OVBIF __vload_pred_dup(__vpred, __RD const __short16*);
__short32     __OVBIF __vload_pred_dup(__vpred, __RD const __short8*);
__short32     __OVBIF __vload_pred_dup(__vpred, __RD const __short4*);
__short32     __OVBIF __vload_pred_dup(__vpred, __RD const __short2*);
__short32     __OVBIF __vload_pred_dup(__vpred, __RD const short*);
__ushort32    __OVBIF __vload_pred_dup(__vpred, __RD const __ushort16*);
__ushort32    __OVBIF __vload_pred_dup(__vpred, __RD const __ushort8*);
__ushort32    __OVBIF __vload_pred_dup(__vpred, __RD const __ushort4*);
__ushort32    __OVBIF __vload_pred_dup(__vpred, __RD const __ushort2*);
__ushort32    __OVBIF __vload_pred_dup(__vpred, __RD const __ushort*);
#elif __C7X_VEC_SIZE_BITS__ == 256
__short16     __OVBIF __vload_pred_dup(__vpred, __RD const __short8*);
__short16     __OVBIF __vload_pred_dup(__vpred, __RD const __short4*);
__short16     __OVBIF __vload_pred_dup(__vpred, __RD const __short2*);
__short16     __OVBIF __vload_pred_dup(__vpred, __RD const short*);
__ushort16    __OVBIF __vload_pred_dup(__vpred, __RD const __ushort8*);
__ushort16    __OVBIF __vload_pred_dup(__vpred, __RD const __ushort4*);
__ushort16    __OVBIF __vload_pred_dup(__vpred, __RD const __ushort2*);
__ushort16    __OVBIF __vload_pred_dup(__vpred, __RD const __ushort*);
#endif

/* VLDDUP2W, VLDDUP4W, VLDDUP8W, VLDDUP16W */
#if __C7X_VEC_SIZE_BITS__ == 512
__int16       __OVBIF __vload_pred_dup(__vpred, __RD const __int8*);
__int16       __OVBIF __vload_pred_dup(__vpred, __RD const __int4*);
__int16       __OVBIF __vload_pred_dup(__vpred, __RD const __int2*);
__int16       __OVBIF __vload_pred_dup(__vpred, __RD const int*);
__uint16      __OVBIF __vload_pred_dup(__vpred, __RD const __uint8*);
__uint16      __OVBIF __vload_pred_dup(__vpred, __RD const __uint4*);
__uint16      __OVBIF __vload_pred_dup(__vpred, __RD const __uint2*);
__uint16      __OVBIF __vload_pred_dup(__vpred, __RD const __uint*);
__float16     __OVBIF __vload_pred_dup(__vpred, __RD const __float8*);
__float16     __OVBIF __vload_pred_dup(__vpred, __RD const __float4*);
__float16     __OVBIF __vload_pred_dup(__vpred, __RD const __float2*);
__float16     __OVBIF __vload_pred_dup(__vpred, __RD const float*);
#elif __C7X_VEC_SIZE_BITS__ == 256
__int8       __OVBIF __vload_pred_dup(__vpred, __RD const __int4*);
__int8       __OVBIF __vload_pred_dup(__vpred, __RD const __int2*);
__int8       __OVBIF __vload_pred_dup(__vpred, __RD const int*);
__uint8      __OVBIF __vload_pred_dup(__vpred, __RD const __uint4*);
__uint8      __OVBIF __vload_pred_dup(__vpred, __RD const __uint2*);
__uint8      __OVBIF __vload_pred_dup(__vpred, __RD const __uint*);
__float8     __OVBIF __vload_pred_dup(__vpred, __RD const __float4*);
__float8     __OVBIF __vload_pred_dup(__vpred, __RD const __float2*);
__float8     __OVBIF __vload_pred_dup(__vpred, __RD const float*);
#endif

/* VLDDUP2D, VLDDUP4D, VLDDUP8D */
#if __C7X_VEC_SIZE_BITS__ == 512
__long8       __OVBIF __vload_pred_dup(__vpred, __RD const __long4*);
__long8       __OVBIF __vload_pred_dup(__vpred, __RD const __long2*);
__long8       __OVBIF __vload_pred_dup(__vpred, __RD const long*);
__ulong8      __OVBIF __vload_pred_dup(__vpred, __RD const __ulong4*);
__ulong8      __OVBIF __vload_pred_dup(__vpred, __RD const __ulong2*);
__ulong8      __OVBIF __vload_pred_dup(__vpred, __RD const __ulong*);
__double8     __OVBIF __vload_pred_dup(__vpred, __RD const __double4*);
__double8     __OVBIF __vload_pred_dup(__vpred, __RD const __double2*);
__double8     __OVBIF __vload_pred_dup(__vpred, __RD const double*);
#elif __C7X_VEC_SIZE_BITS__ == 256
__long4       __OVBIF __vload_pred_dup(__vpred, __RD const __long2*);
__long4       __OVBIF __vload_pred_dup(__vpred, __RD const long*);
__ulong4      __OVBIF __vload_pred_dup(__vpred, __RD const __ulong2*);
__ulong4      __OVBIF __vload_pred_dup(__vpred, __RD const __ulong*);
__double4     __OVBIF __vload_pred_dup(__vpred, __RD const __double2*);
__double4     __OVBIF __vload_pred_dup(__vpred, __RD const double*);
#endif

/* VLDDUP4G8H, VLDDUP8G4H */
/* these instructions are only on 512-bit architectures */
#if __C7X_VEC_SIZE_BITS__ == 512
__short32     __OVBIF __vload_pred_dup_vec(__vpred, __RD const __short8*);
__ushort32    __OVBIF __vload_pred_dup_vec(__vpred, __RD const __ushort8*);
__short32     __OVBIF __vload_pred_dup_vec(__vpred, __RD const __short4*);
__ushort32    __OVBIF __vload_pred_dup_vec(__vpred, __RD const __ushort4*);
#endif

/* VLDBUNPKH, VLDBUNPKHU */
short       __OVBIF __vload_pred_unpack_short(__vpred, __RD const signed char*);
__short2    __OVBIF __vload_pred_unpack_short(__vpred, __RD const __char2*);
__short4    __OVBIF __vload_pred_unpack_short(__vpred, __RD const __char4*);
__short8    __OVBIF __vload_pred_unpack_short(__vpred, __RD const __char8*);
__short16   __OVBIF __vload_pred_unpack_short(__vpred, __RD const __char16*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__short32   __OVBIF __vload_pred_unpack_short(__vpred, __RD const __char32*);
#endif
__ushort    __OVBIF __vload_pred_unpack_short(__vpred, __RD const __uchar*);
__ushort2   __OVBIF __vload_pred_unpack_short(__vpred, __RD const __uchar2*);
__ushort4   __OVBIF __vload_pred_unpack_short(__vpred, __RD const __uchar4*);
__ushort8   __OVBIF __vload_pred_unpack_short(__vpred, __RD const __uchar8*);
__ushort16  __OVBIF __vload_pred_unpack_short(__vpred, __RD const __uchar16*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__ushort32  __OVBIF __vload_pred_unpack_short(__vpred, __RD const __uchar32*);
#endif

/* VLDBUNPKW, VLDBUNPKWU */
int         __OVBIF __vload_pred_unpack_int(__vpred, __RD const signed char*);
__int2      __OVBIF __vload_pred_unpack_int(__vpred, __RD const __char2*);
__int4      __OVBIF __vload_pred_unpack_int(__vpred, __RD const __char4*);
__int8      __OVBIF __vload_pred_unpack_int(__vpred, __RD const __char8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__int16     __OVBIF __vload_pred_unpack_int(__vpred, __RD const __char16*);
#endif
__uint      __OVBIF __vload_pred_unpack_int(__vpred, __RD const __uchar*);
__uint2     __OVBIF __vload_pred_unpack_int(__vpred, __RD const __uchar2*);
__uint4     __OVBIF __vload_pred_unpack_int(__vpred, __RD const __uchar4*);
__uint8     __OVBIF __vload_pred_unpack_int(__vpred, __RD const __uchar8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__uint16    __OVBIF __vload_pred_unpack_int(__vpred, __RD const __uchar16*);
#endif

/* VLDHUNPKW, VLDHUNPKWU */
int         __OVBIF __vload_pred_unpack_int(__vpred, __RD const short*);
__int2      __OVBIF __vload_pred_unpack_int(__vpred, __RD const __short2*);
__int4      __OVBIF __vload_pred_unpack_int(__vpred, __RD const __short4*);
__int8      __OVBIF __vload_pred_unpack_int(__vpred, __RD const __short8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__int16     __OVBIF __vload_pred_unpack_int(__vpred, __RD const __short16*);
#endif
__uint      __OVBIF __vload_pred_unpack_int(__vpred, __RD const __ushort*);
__uint2     __OVBIF __vload_pred_unpack_int(__vpred, __RD const __ushort2*);
__uint4     __OVBIF __vload_pred_unpack_int(__vpred, __RD const __ushort4*);
__uint8     __OVBIF __vload_pred_unpack_int(__vpred, __RD const __ushort8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__uint16    __OVBIF __vload_pred_unpack_int(__vpred, __RD const __ushort16*);
#endif

/* VLDBUNPKD, VLDBUNPKDU */
long        __OVBIF __vload_pred_unpack_long(__vpred, __RD const signed char*);
__long2     __OVBIF __vload_pred_unpack_long(__vpred, __RD const __char2*);
__long4     __OVBIF __vload_pred_unpack_long(__vpred, __RD const __char4*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__long8     __OVBIF __vload_pred_unpack_long(__vpred, __RD const __char8*);
#endif
__ulong     __OVBIF __vload_pred_unpack_long(__vpred, __RD const __uchar*);
__ulong2    __OVBIF __vload_pred_unpack_long(__vpred, __RD const __uchar2*);
__ulong4    __OVBIF __vload_pred_unpack_long(__vpred, __RD const __uchar4*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__ulong8    __OVBIF __vload_pred_unpack_long(__vpred, __RD const __uchar8*);
#endif

/* VLDHUNPKD, VLDHUNPKDU */
long        __OVBIF __vload_pred_unpack_long(__vpred, __RD const short*);
__long2     __OVBIF __vload_pred_unpack_long(__vpred, __RD const __short2*);
__long4     __OVBIF __vload_pred_unpack_long(__vpred, __RD const __short4*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__long8     __OVBIF __vload_pred_unpack_long(__vpred, __RD const __short8*);
#endif
__ulong     __OVBIF __vload_pred_unpack_long(__vpred, __RD const __ushort*);
__ulong2    __OVBIF __vload_pred_unpack_long(__vpred, __RD const __ushort2*);
__ulong4    __OVBIF __vload_pred_unpack_long(__vpred, __RD const __ushort4*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__ulong8    __OVBIF __vload_pred_unpack_long(__vpred, __RD const __ushort8*);
#endif

/* VLDWUNPKD, VLDWUNPKDU */
long        __OVBIF __vload_pred_unpack_long(__vpred, __RD const int*);
__long2     __OVBIF __vload_pred_unpack_long(__vpred, __RD const __int2*);
__long4     __OVBIF __vload_pred_unpack_long(__vpred, __RD const __int4*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__long8     __OVBIF __vload_pred_unpack_long(__vpred, __RD const __int8*);
#endif
__ulong     __OVBIF __vload_pred_unpack_long(__vpred, __RD const __uint*);
__ulong2    __OVBIF __vload_pred_unpack_long(__vpred, __RD const __uint2*);
__ulong4    __OVBIF __vload_pred_unpack_long(__vpred, __RD const __uint4*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__ulong8    __OVBIF __vload_pred_unpack_long(__vpred, __RD const __uint8*);
#endif

/* VLDEBUNPKW, VLDEHUNPKW */
int         __OVBIF __vload_pred_deinterleave_int(__vpred, __RD const __char2*);
__int2      __OVBIF __vload_pred_deinterleave_int(__vpred, __RD const __char4*);
__int4      __OVBIF __vload_pred_deinterleave_int(__vpred, __RD const __char8*);
__int8      __OVBIF __vload_pred_deinterleave_int(__vpred, __RD const __char16*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__int16     __OVBIF __vload_pred_deinterleave_int(__vpred, __RD const __char32*);
#endif
int         __OVBIF __vload_pred_deinterleave_int(__vpred, __RD const __short2*);
__int2      __OVBIF __vload_pred_deinterleave_int(__vpred, __RD const __short4*);
__int4      __OVBIF __vload_pred_deinterleave_int(__vpred, __RD const __short8*);
__int8      __OVBIF __vload_pred_deinterleave_int(__vpred, __RD const __short16*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__int16     __OVBIF __vload_pred_deinterleave_int(__vpred, __RD const __short32*);
#endif

/* VLDEBUNPKWU, VLDEHUNPKWU */
__uint       __OVBIF __vload_pred_deinterleave_int(__vpred, __RD const __uchar2*);
__uint2      __OVBIF __vload_pred_deinterleave_int(__vpred, __RD const __uchar4*);
__uint4      __OVBIF __vload_pred_deinterleave_int(__vpred, __RD const __uchar8*);
__uint8      __OVBIF __vload_pred_deinterleave_int(__vpred, __RD const __uchar16*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__uint16     __OVBIF __vload_pred_deinterleave_int(__vpred, __RD const __uchar32*);
#endif
__uint       __OVBIF __vload_pred_deinterleave_int(__vpred, __RD const __ushort2*);
__uint2      __OVBIF __vload_pred_deinterleave_int(__vpred, __RD const __ushort4*);
__uint4      __OVBIF __vload_pred_deinterleave_int(__vpred, __RD const __ushort8*);
__uint8      __OVBIF __vload_pred_deinterleave_int(__vpred, __RD const __ushort16*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__uint16     __OVBIF __vload_pred_deinterleave_int(__vpred, __RD const __ushort32*);
#endif

/* VLDEBUNPKD, VLDEHUNPKD */
long         __OVBIF __vload_pred_deinterleave_long(__vpred, __RD const __char2*);
__long2      __OVBIF __vload_pred_deinterleave_long(__vpred, __RD const __char4*);
__long4      __OVBIF __vload_pred_deinterleave_long(__vpred, __RD const __char8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__long8      __OVBIF __vload_pred_deinterleave_long(__vpred, __RD const __char16*);
#endif
long         __OVBIF __vload_pred_deinterleave_long(__vpred, __RD const __short2*);
__long2      __OVBIF __vload_pred_deinterleave_long(__vpred, __RD const __short4*);
__long4      __OVBIF __vload_pred_deinterleave_long(__vpred, __RD const __short8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__long8      __OVBIF __vload_pred_deinterleave_long(__vpred, __RD const __short16*);
#endif

/* VLDEBUNPKDU, VLDEHUNPKDU */
__ulong       __OVBIF __vload_pred_deinterleave_long(__vpred, __RD const __uchar2*);
__ulong2      __OVBIF __vload_pred_deinterleave_long(__vpred, __RD const __uchar4*);
__ulong4      __OVBIF __vload_pred_deinterleave_long(__vpred, __RD const __uchar8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__ulong8      __OVBIF __vload_pred_deinterleave_long(__vpred, __RD const __uchar16*);
#endif
__ulong       __OVBIF __vload_pred_deinterleave_long(__vpred, __RD const __ushort2*);
__ulong2      __OVBIF __vload_pred_deinterleave_long(__vpred, __RD const __ushort4*);
__ulong4      __OVBIF __vload_pred_deinterleave_long(__vpred, __RD const __ushort8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__ulong8      __OVBIF __vload_pred_deinterleave_long(__vpred, __RD const __ushort16*);
#endif

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
#if __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_pred_interleave(__vpred, __WR __char64*,  __char64,  __char64);
void __OVBIFM __vstore_pred_interleave(__vpred, __WR __short32*, __short32, __short32);
void __OVBIFM __vstore_pred_interleave(__vpred, __WR __int16*,   __int16,   __int16);
void __OVBIFM __vstore_pred_interleave(__vpred, __WR __long8*,   __long8,   __long8);
void __OVBIFM __vstore_pred_interleave(__vpred, __WR __uchar64*, __uchar64, __uchar64);
void __OVBIFM __vstore_pred_interleave(__vpred, __WR __ushort32*,__ushort32,__ushort32);
void __OVBIFM __vstore_pred_interleave(__vpred, __WR __uint16*,  __uint16,  __uint16);
void __OVBIFM __vstore_pred_interleave(__vpred, __WR __ulong8*,  __ulong8,  __ulong8);
#elif __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_pred_interleave(__vpred, __WR __char32*,  __char32,  __char32);
void __OVBIFM __vstore_pred_interleave(__vpred, __WR __short16*, __short16, __short16);
void __OVBIFM __vstore_pred_interleave(__vpred, __WR __int8*,   __int8,   __int8);
void __OVBIFM __vstore_pred_interleave(__vpred, __WR __long4*,   __long4,   __long4);
void __OVBIFM __vstore_pred_interleave(__vpred, __WR __uchar32*, __uchar32, __uchar32);
void __OVBIFM __vstore_pred_interleave(__vpred, __WR __ushort16*,__ushort16,__ushort16);
void __OVBIFM __vstore_pred_interleave(__vpred, __WR __uint8*,  __uint8,  __uint8);
void __OVBIFM __vstore_pred_interleave(__vpred, __WR __ulong4*,  __ulong4,  __ulong4);
#endif

/* VSTPINTLB4 - STORES EVERY FOURTH ELEMENT */
#if __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_pred_interleave4(__vpred, __WR __char32*,  __char64,   __char64);
void __OVBIFM __vstore_pred_interleave4(__vpred, __WR __uchar32*, __uchar64,  __uchar64);
#elif __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_pred_interleave4(__vpred, __WR __char16*,  __char32,   __char32);
void __OVBIFM __vstore_pred_interleave4(__vpred, __WR __uchar16*, __uchar32,  __uchar32);
#endif

#ifndef __C7100__
/* VSTPINTHB, VSTPINTHH, VSTPINTHW, VSTPINTHD - STORES EVERY EVEN ELEMENT */
#if __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_pred_interleave_odd(__vpred, __WR __char64*,  __char64,  __char64);
void __OVBIFM __vstore_pred_interleave_odd(__vpred, __WR __short32*, __short32, __short32);
void __OVBIFM __vstore_pred_interleave_odd(__vpred, __WR __int16*,   __int16,   __int16);
void __OVBIFM __vstore_pred_interleave_odd(__vpred, __WR __long8*,   __long8,   __long8);
void __OVBIFM __vstore_pred_interleave_odd(__vpred, __WR __uchar64*, __uchar64, __uchar64);
void __OVBIFM __vstore_pred_interleave_odd(__vpred, __WR __ushort32*,__ushort32,__ushort32);
void __OVBIFM __vstore_pred_interleave_odd(__vpred, __WR __uint16*,  __uint16,  __uint16);
void __OVBIFM __vstore_pred_interleave_odd(__vpred, __WR __ulong8*,  __ulong8,  __ulong8);
#elif __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_pred_interleave_odd(__vpred, __WR __char32*,  __char32,  __char32);
void __OVBIFM __vstore_pred_interleave_odd(__vpred, __WR __short16*, __short16, __short16);
void __OVBIFM __vstore_pred_interleave_odd(__vpred, __WR __int8*,   __int8,   __int8);
void __OVBIFM __vstore_pred_interleave_odd(__vpred, __WR __long4*,   __long4,   __long4);
void __OVBIFM __vstore_pred_interleave_odd(__vpred, __WR __uchar32*, __uchar32, __uchar32);
void __OVBIFM __vstore_pred_interleave_odd(__vpred, __WR __ushort16*,__ushort16,__ushort16);
void __OVBIFM __vstore_pred_interleave_odd(__vpred, __WR __uint8*,  __uint8,  __uint8);
void __OVBIFM __vstore_pred_interleave_odd(__vpred, __WR __ulong4*,  __ulong4,  __ulong4);
#endif

/* VSTPLLINTB, VSTPLLINTH, VSTPLLINTW, VSTPLLINTH - STORES LOW VECTOR HALVES */
#if __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_pred_interleave_low_low(__vpred, __WR __char64*,  __char64,  __char64);
void __OVBIFM __vstore_pred_interleave_low_low(__vpred, __WR __short32*, __short32, __short32);
void __OVBIFM __vstore_pred_interleave_low_low(__vpred, __WR __int16*,   __int16,   __int16);
void __OVBIFM __vstore_pred_interleave_low_low(__vpred, __WR __long8*,   __long8,   __long8);
void __OVBIFM __vstore_pred_interleave_low_low(__vpred, __WR __uchar64*, __uchar64, __uchar64);
void __OVBIFM __vstore_pred_interleave_low_low(__vpred, __WR __ushort32*,__ushort32,__ushort32);
void __OVBIFM __vstore_pred_interleave_low_low(__vpred, __WR __uint16*,  __uint16,  __uint16);
void __OVBIFM __vstore_pred_interleave_low_low(__vpred, __WR __ulong8*,  __ulong8,  __ulong8);
#elif __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_pred_interleave_low_low(__vpred, __WR __char32*,  __char32,  __char32);
void __OVBIFM __vstore_pred_interleave_low_low(__vpred, __WR __short16*, __short16, __short16);
void __OVBIFM __vstore_pred_interleave_low_low(__vpred, __WR __int8*,   __int8,   __int8);
void __OVBIFM __vstore_pred_interleave_low_low(__vpred, __WR __long4*,   __long4,   __long4);
void __OVBIFM __vstore_pred_interleave_low_low(__vpred, __WR __uchar32*, __uchar32, __uchar32);
void __OVBIFM __vstore_pred_interleave_low_low(__vpred, __WR __ushort16*,__ushort16,__ushort16);
void __OVBIFM __vstore_pred_interleave_low_low(__vpred, __WR __uint8*,  __uint8,  __uint8);
void __OVBIFM __vstore_pred_interleave_low_low(__vpred, __WR __ulong4*,  __ulong4,  __ulong4);
#endif

/* VSTPLLINTB, VSTPLLINTH, VSTPLLINTW, VSTPLLINTH - Interleave all of the half-vectors. */
#if __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_pred_interleave_low_low(__vpred, __WR __char64*,  __char32,  __char32);
void __OVBIFM __vstore_pred_interleave_low_low(__vpred, __WR __short32*, __short16, __short16);
void __OVBIFM __vstore_pred_interleave_low_low(__vpred, __WR __int16*,   __int8,   __int8);
void __OVBIFM __vstore_pred_interleave_low_low(__vpred, __WR __long8*,   __long4,   __long4);
void __OVBIFM __vstore_pred_interleave_low_low(__vpred, __WR __uchar64*, __uchar32, __uchar32);
void __OVBIFM __vstore_pred_interleave_low_low(__vpred, __WR __ushort32*,__ushort16,__ushort16);
void __OVBIFM __vstore_pred_interleave_low_low(__vpred, __WR __uint16*,  __uint8,  __uint8);
void __OVBIFM __vstore_pred_interleave_low_low(__vpred, __WR __ulong8*,  __ulong4,  __ulong4);
#elif __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_pred_interleave_low_low(__vpred, __WR __char32*,  __char16,  __char16);
void __OVBIFM __vstore_pred_interleave_low_low(__vpred, __WR __short16*, __short8, __short8);
void __OVBIFM __vstore_pred_interleave_low_low(__vpred, __WR __int8*,   __int4,   __int4);
void __OVBIFM __vstore_pred_interleave_low_low(__vpred, __WR __long4*,   __long2,   __long2);
void __OVBIFM __vstore_pred_interleave_low_low(__vpred, __WR __uchar32*, __uchar16, __uchar16);
void __OVBIFM __vstore_pred_interleave_low_low(__vpred, __WR __ushort16*,__ushort8,__ushort8);
void __OVBIFM __vstore_pred_interleave_low_low(__vpred, __WR __uint8*,  __uint4,  __uint4);
void __OVBIFM __vstore_pred_interleave_low_low(__vpred, __WR __ulong4*,  __ulong2,  __ulong2);
#endif

/* VSTPHHINTB, VSTPHHINTH, VSTPHHINTW, VSTPHHINTH - STORES HIGH VECTOR HALVES */
#if __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_pred_interleave_high_high(__vpred, __WR __char64*,  __char64,  __char64);
void __OVBIFM __vstore_pred_interleave_high_high(__vpred, __WR __short32*, __short32, __short32);
void __OVBIFM __vstore_pred_interleave_high_high(__vpred, __WR __int16*,   __int16,   __int16);
void __OVBIFM __vstore_pred_interleave_high_high(__vpred, __WR __long8*,   __long8,   __long8);
void __OVBIFM __vstore_pred_interleave_high_high(__vpred, __WR __uchar64*, __uchar64, __uchar64);
void __OVBIFM __vstore_pred_interleave_high_high(__vpred, __WR __ushort32*,__ushort32,__ushort32);
void __OVBIFM __vstore_pred_interleave_high_high(__vpred, __WR __uint16*,  __uint16,  __uint16);
void __OVBIFM __vstore_pred_interleave_high_high(__vpred, __WR __ulong8*,  __ulong8,  __ulong8);
#elif __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_pred_interleave_high_high(__vpred, __WR __char32*,  __char32,  __char32);
void __OVBIFM __vstore_pred_interleave_high_high(__vpred, __WR __short16*, __short16, __short16);
void __OVBIFM __vstore_pred_interleave_high_high(__vpred, __WR __int8*,   __int8,   __int8);
void __OVBIFM __vstore_pred_interleave_high_high(__vpred, __WR __long4*,   __long4,   __long4);
void __OVBIFM __vstore_pred_interleave_high_high(__vpred, __WR __uchar32*, __uchar32, __uchar32);
void __OVBIFM __vstore_pred_interleave_high_high(__vpred, __WR __ushort16*,__ushort16,__ushort16);
void __OVBIFM __vstore_pred_interleave_high_high(__vpred, __WR __uint8*,  __uint8,  __uint8);
void __OVBIFM __vstore_pred_interleave_high_high(__vpred, __WR __ulong4*,  __ulong4,  __ulong4);
#endif
#endif /* ! __C7100__ */

/* VSTP2B, VSTP4B, VSTP8B, VSTP16B, VSTP32B, VSTP64B */
void __OVBIFM __vstore_pred(__vpred, __WR signed char*,    signed char);
void __OVBIFM __vstore_pred(__vpred, __WR __char2*,   __char2);
void __OVBIFM __vstore_pred(__vpred, __WR __char4*,   __char4);
void __OVBIFM __vstore_pred(__vpred, __WR __char8*,   __char8);
void __OVBIFM __vstore_pred(__vpred, __WR __char16*,  __char16);
void __OVBIFM __vstore_pred(__vpred, __WR __char32*,  __char32);
#if __C7X_VEC_SIZE_BITS__ >= 512
void __OVBIFM __vstore_pred(__vpred, __WR __char64*,  __char64);
#endif
void __OVBIFM __vstore_pred(__vpred, __WR unsigned char*,  unsigned char);
void __OVBIFM __vstore_pred(__vpred, __WR __uchar2*,  __uchar2);
void __OVBIFM __vstore_pred(__vpred, __WR __uchar4*,  __uchar4);
void __OVBIFM __vstore_pred(__vpred, __WR __uchar8*,  __uchar8);
void __OVBIFM __vstore_pred(__vpred, __WR __uchar16*, __uchar16);
void __OVBIFM __vstore_pred(__vpred, __WR __uchar32*, __uchar32);
#if __C7X_VEC_SIZE_BITS__ >= 512
void __OVBIFM __vstore_pred(__vpred, __WR __uchar64*, __uchar64);
#endif

/* VSTP2H, VSTP4H, VSTP8H, VSTP16H, VSTP32H */
void __OVBIFM __vstore_pred(__vpred, __WR short*,    short); 
void __OVBIFM __vstore_pred(__vpred, __WR __short2*, __short2);
void __OVBIFM __vstore_pred(__vpred, __WR __short4*, __short4);
void __OVBIFM __vstore_pred(__vpred, __WR __short8*, __short8);
void __OVBIFM __vstore_pred(__vpred, __WR __short16*, __short16);
#if __C7X_VEC_SIZE_BITS__ >= 512
void __OVBIFM __vstore_pred(__vpred, __WR __short32*, __short32);
#endif
void __OVBIFM __vstore_pred(__vpred, __WR unsigned short*, unsigned short);
void __OVBIFM __vstore_pred(__vpred, __WR __ushort2*, __ushort2);
void __OVBIFM __vstore_pred(__vpred, __WR __ushort4*, __ushort4);
void __OVBIFM __vstore_pred(__vpred, __WR __ushort8*, __ushort8);
void __OVBIFM __vstore_pred(__vpred, __WR __ushort16*, __ushort16);
#if __C7X_VEC_SIZE_BITS__ >= 512
void __OVBIFM __vstore_pred(__vpred, __WR __ushort32*, __ushort32);
#endif
void __OVBIFM __vstore_pred(__vpred, __WR __cchar2*, __cchar2);
void __OVBIFM __vstore_pred(__vpred, __WR __cchar4*, __cchar4);
void __OVBIFM __vstore_pred(__vpred, __WR __cchar8*, __cchar8);
void __OVBIFM __vstore_pred(__vpred, __WR __cchar16*, __cchar16);
#if __C7X_VEC_SIZE_BITS__ >= 512
void __OVBIFM __vstore_pred(__vpred, __WR __cchar32*, __cchar32);
#endif

/* VSTP2W, VSTP4W, VSTP8W, VSTP16W */

void __OVBIFM __vstore_pred(__vpred, __WR int*,      int); 
void __OVBIFM __vstore_pred(__vpred, __WR __int2*,     __int2);
void __OVBIFM __vstore_pred(__vpred, __WR __int4*,     __int4);
void __OVBIFM __vstore_pred(__vpred, __WR __int8*,     __int8);
#if __C7X_VEC_SIZE_BITS__ >= 512
void __OVBIFM __vstore_pred(__vpred, __WR __int16*,    __int16);
#endif
void __OVBIFM __vstore_pred(__vpred, __WR unsigned int*,   unsigned int);
void __OVBIFM __vstore_pred(__vpred, __WR __uint2*,    __uint2);
void __OVBIFM __vstore_pred(__vpred, __WR __uint4*,    __uint4);
void __OVBIFM __vstore_pred(__vpred, __WR __uint8*,    __uint8);
#if __C7X_VEC_SIZE_BITS__ >= 512
void __OVBIFM __vstore_pred(__vpred, __WR __uint16*,   __uint16);
#endif

void __OVBIFM __vstore_pred(__vpred, __WR float*,      float);
void __OVBIFM __vstore_pred(__vpred, __WR __float2*,   __float2);
void __OVBIFM __vstore_pred(__vpred, __WR __float4*,   __float4);
void __OVBIFM __vstore_pred(__vpred, __WR __float8*,   __float8);
#if __C7X_VEC_SIZE_BITS__ >= 512
void __OVBIFM __vstore_pred(__vpred, __WR __float16*,  __float16);
#endif
void __OVBIFM __vstore_pred(__vpred, __WR __cshort2*,  __cshort2);
void __OVBIFM __vstore_pred(__vpred, __WR __cshort4*,  __cshort4);
void __OVBIFM __vstore_pred(__vpred, __WR __cshort8*,  __cshort8);
#if __C7X_VEC_SIZE_BITS__ >= 512
void __OVBIFM __vstore_pred(__vpred, __WR __cshort16*, __cshort16);
#endif

/* VSTP2D, VSTP4D, VSTP8D */
void __OVBIFM __vstore_pred(__vpred, __WR long*,      long);
void __OVBIFM __vstore_pred(__vpred, __WR __long2*,   __long2);
void __OVBIFM __vstore_pred(__vpred, __WR __long4*,   __long4);
#if __C7X_VEC_SIZE_BITS__ >= 512
void __OVBIFM __vstore_pred(__vpred, __WR __long8*,   __long8);
#endif
void __OVBIFM __vstore_pred(__vpred, __WR unsigned long*,  unsigned long);
void __OVBIFM __vstore_pred(__vpred, __WR __ulong*,   __ulong);
void __OVBIFM __vstore_pred(__vpred, __WR __ulong2*,  __ulong2);
void __OVBIFM __vstore_pred(__vpred, __WR __ulong4*,  __ulong4);
#if __C7X_VEC_SIZE_BITS__ >= 512
void __OVBIFM __vstore_pred(__vpred, __WR __ulong8*,  __ulong8);
#endif

void __OVBIFM __vstore_pred(__vpred, __WR double*,    double);
void __OVBIFM __vstore_pred(__vpred, __WR __double2*, __double2);
void __OVBIFM __vstore_pred(__vpred, __WR __double4*, __double4);
#if __C7X_VEC_SIZE_BITS__ >= 512
void __OVBIFM __vstore_pred(__vpred, __WR __double8*, __double8);
#endif

void __OVBIFM __vstore_pred(__vpred, __WR __cint*,    __cint);
void __OVBIFM __vstore_pred(__vpred, __WR __cint2*,   __cint2);
void __OVBIFM __vstore_pred(__vpred, __WR __cint4*,   __cint4);
#if __C7X_VEC_SIZE_BITS__ >= 512
void __OVBIFM __vstore_pred(__vpred, __WR __cint8*,   __cint8);
#endif

void __OVBIFM __vstore_pred(__vpred, __WR __cfloat*,  __cfloat);
void __OVBIFM __vstore_pred(__vpred, __WR __cfloat2*, __cfloat2);
void __OVBIFM __vstore_pred(__vpred, __WR __cfloat4*, __cfloat4);
#if __C7X_VEC_SIZE_BITS__ >= 512
void __OVBIFM __vstore_pred(__vpred, __WR __cfloat8*, __cfloat8);
#endif

/* VSTPBSVPACKL, VSTPBSVPACKH, VSTPBSVPACKHS1: PRED CORRESPONDS TO SRC DATA */
#if __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_pred_packl(__vpred,   __WR __char16*,  __short16);
void __OVBIFM __vstore_pred_packl(__vpred,   __WR __uchar16*, __ushort16);
void __OVBIFM __vstore_pred_packh(__vpred,   __WR __char16*,  __short16);
void __OVBIFM __vstore_pred_packh(__vpred,   __WR __uchar16*, __ushort16);
void __OVBIFM __vstore_pred_packhs1(__vpred, __WR __char16*,  __short16);
void __OVBIFM __vstore_pred_packhs1(__vpred, __WR __uchar16*, __ushort16);
#elif __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_pred_packl(__vpred,   __WR __char32*,  __short32);
void __OVBIFM __vstore_pred_packl(__vpred,   __WR __uchar32*, __ushort32);
void __OVBIFM __vstore_pred_packh(__vpred,   __WR __char32*,  __short32);
void __OVBIFM __vstore_pred_packh(__vpred,   __WR __uchar32*, __ushort32);
void __OVBIFM __vstore_pred_packhs1(__vpred, __WR __char32*,  __short32);
void __OVBIFM __vstore_pred_packhs1(__vpred, __WR __uchar32*, __ushort32);
#endif

/* VSTPHSVPACKL, VSTPHSVPACKH, VSTPHSVPACKHS1: PRED CORRESPONDS TO SRC DATA */
#if __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_pred_packl(__vpred,   __WR __short8*,  __int8);
void __OVBIFM __vstore_pred_packl(__vpred,   __WR __ushort8*, __uint8);
void __OVBIFM __vstore_pred_packh(__vpred,   __WR __short8*,  __int8);
void __OVBIFM __vstore_pred_packh(__vpred,   __WR __ushort8*, __uint8);
void __OVBIFM __vstore_pred_packhs1(__vpred, __WR __short8*,  __int8);
void __OVBIFM __vstore_pred_packhs1(__vpred, __WR __ushort8*, __uint8);
#elif __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_pred_packl(__vpred,   __WR __short16*,  __int16);
void __OVBIFM __vstore_pred_packl(__vpred,   __WR __ushort16*, __uint16);
void __OVBIFM __vstore_pred_packh(__vpred,   __WR __short16*,  __int16);
void __OVBIFM __vstore_pred_packh(__vpred,   __WR __ushort16*, __uint16);
void __OVBIFM __vstore_pred_packhs1(__vpred, __WR __short16*,  __int16);
void __OVBIFM __vstore_pred_packhs1(__vpred, __WR __ushort16*, __uint16);
#endif

/* VSTPWSVPACKB: PRED CORRESPONDS TO SRC DATA */
#if __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_pred_pack_byte(__vpred, __WR __char8*,  __int8);
void __OVBIFM __vstore_pred_pack_byte(__vpred, __WR __uchar8*, __uint8);
#elif __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_pred_pack_byte(__vpred, __WR __char16*,  __int16);
void __OVBIFM __vstore_pred_pack_byte(__vpred, __WR __uchar16*, __uint16);
#endif

/* VSTPWSVPACKL, VSTPWSVPACKH, VSTPWSVPACKHS1: PRED CORRESPONDS TO SRC DATA */
#if __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_pred_packl(__vpred,   __WR __int4*,  __long4);
void __OVBIFM __vstore_pred_packl(__vpred,   __WR __uint4*, __ulong4);
void __OVBIFM __vstore_pred_packh(__vpred,   __WR __int4*,  __long4);
void __OVBIFM __vstore_pred_packh(__vpred,   __WR __uint4*, __ulong4);
void __OVBIFM __vstore_pred_packhs1(__vpred, __WR __int4*,  __long4);
void __OVBIFM __vstore_pred_packhs1(__vpred, __WR __uint4*, __ulong4);
#elif __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_pred_packl(__vpred,   __WR __int8*,  __long8);
void __OVBIFM __vstore_pred_packl(__vpred,   __WR __uint8*, __ulong8);
void __OVBIFM __vstore_pred_packh(__vpred,   __WR __int8*,  __long8);
void __OVBIFM __vstore_pred_packh(__vpred,   __WR __uint8*, __ulong8);
void __OVBIFM __vstore_pred_packhs1(__vpred, __WR __int8*,  __long8);
void __OVBIFM __vstore_pred_packhs1(__vpred, __WR __uint8*, __ulong8);
#endif

/* VSTPDSVPACKL, VSTPDSVPACKH, VSTPDSVPACKHS1: PRED CORRESPONDS TO SRC DATA */
#if __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_pred_packl_long(__vpred,   __WR __long2*,  __long4);
void __OVBIFM __vstore_pred_packl_long(__vpred,   __WR __ulong2*, __ulong4);
void __OVBIFM __vstore_pred_packh_long(__vpred,   __WR __long2*,  __long4);
void __OVBIFM __vstore_pred_packh_long(__vpred,   __WR __ulong2*, __ulong4);
void __OVBIFM __vstore_pred_packhs1_long(__vpred, __WR __long2*,  __long4);
void __OVBIFM __vstore_pred_packhs1_long(__vpred, __WR __ulong2*, __ulong4);
#elif __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_pred_packl_long(__vpred,   __WR __long4*,  __long8);
void __OVBIFM __vstore_pred_packl_long(__vpred,   __WR __ulong4*, __ulong8);
void __OVBIFM __vstore_pred_packh_long(__vpred,   __WR __long4*,  __long8);
void __OVBIFM __vstore_pred_packh_long(__vpred,   __WR __ulong4*, __ulong8);
void __OVBIFM __vstore_pred_packhs1_long(__vpred, __WR __long4*,  __long8);
void __OVBIFM __vstore_pred_packhs1_long(__vpred, __WR __ulong4*, __ulong8);
#endif

/* VSTPBPACKL, VSTPBPACKH, VSTPBPACKHS1: PRED CORRESPONDS TO PACKED DATA */
#if __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_pred_packl_2src(__vpred,   __WR __char32*, __short16,  __short16);
void __OVBIFM __vstore_pred_packl_2src(__vpred,   __WR __uchar32*, __ushort16, __ushort16);
void __OVBIFM __vstore_pred_packh_2src(__vpred,   __WR __char32*, __short16,  __short16);
void __OVBIFM __vstore_pred_packh_2src(__vpred,   __WR __uchar32*, __ushort16, __ushort16);
void __OVBIFM __vstore_pred_packhs1_2src(__vpred, __WR __char32*, __short16,  __short16);
void __OVBIFM __vstore_pred_packhs1_2src(__vpred, __WR __uchar32*, __ushort16, __ushort16);
#elif __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_pred_packl_2src(__vpred,   __WR __char64*, __short32,  __short32);
void __OVBIFM __vstore_pred_packl_2src(__vpred,   __WR __uchar64*, __ushort32, __ushort32);
void __OVBIFM __vstore_pred_packh_2src(__vpred,   __WR __char64*, __short32,  __short32);
void __OVBIFM __vstore_pred_packh_2src(__vpred,   __WR __uchar64*, __ushort32, __ushort32);
void __OVBIFM __vstore_pred_packhs1_2src(__vpred, __WR __char64*, __short32,  __short32);
void __OVBIFM __vstore_pred_packhs1_2src(__vpred, __WR __uchar64*, __ushort32, __ushort32);
#endif

/* VSTPHPACKL, VSTPHPACKH, VSTPHPACKHS1: PRED CORRESPONDS TO PACKED DATA */
#if __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_pred_packl_2src(__vpred,   __WR __short16*, __int8,   __int8);
void __OVBIFM __vstore_pred_packl_2src(__vpred,   __WR __ushort16*, __uint8, __uint8);
void __OVBIFM __vstore_pred_packh_2src(__vpred,   __WR __short16*, __int8,   __int8);
void __OVBIFM __vstore_pred_packh_2src(__vpred,   __WR __ushort16*, __uint8, __uint8);
void __OVBIFM __vstore_pred_packhs1_2src(__vpred, __WR __short16*, __int8,   __int8);
void __OVBIFM __vstore_pred_packhs1_2src(__vpred, __WR __ushort16*, __uint8, __uint8);
#elif __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_pred_packl_2src(__vpred,   __WR __short32*, __int16,   __int16);
void __OVBIFM __vstore_pred_packl_2src(__vpred,   __WR __ushort32*, __uint16, __uint16);
void __OVBIFM __vstore_pred_packh_2src(__vpred,   __WR __short32*, __int16,   __int16);
void __OVBIFM __vstore_pred_packh_2src(__vpred,   __WR __ushort32*, __uint16, __uint16);
void __OVBIFM __vstore_pred_packhs1_2src(__vpred, __WR __short32*, __int16,   __int16);
void __OVBIFM __vstore_pred_packhs1_2src(__vpred, __WR __ushort32*, __uint16, __uint16);
#endif

/* VSTPWPACKB: PRED CORRESPONDS TO PACKED DATA */
#if __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_pred_pack_byte_2src(__vpred, __WR __char16*, __int8,  __int8);
void __OVBIFM __vstore_pred_pack_byte_2src(__vpred, __WR __uchar16*, __uint8, __uint8);
#elif __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_pred_pack_byte_2src(__vpred, __WR __char32*, __int16,  __int16);
void __OVBIFM __vstore_pred_pack_byte_2src(__vpred, __WR __uchar32*, __uint16, __uint16);
#endif

/* VSTPWPACKL, VSTPWPACKH, VSTPWPACKHS1: PRED CORRESPONDS TO PACKED DATA */
#if __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_pred_packl_2src(__vpred,   __WR __int8*, __long4,  __long4);
void __OVBIFM __vstore_pred_packl_2src(__vpred,   __WR __uint8*, __ulong4, __ulong4);
void __OVBIFM __vstore_pred_packh_2src(__vpred,   __WR __int8*, __long4,   __long4);
void __OVBIFM __vstore_pred_packh_2src(__vpred,   __WR __uint8*, __ulong4, __ulong4);
void __OVBIFM __vstore_pred_packhs1_2src(__vpred, __WR __int8*, __long4,   __long4);
void __OVBIFM __vstore_pred_packhs1_2src(__vpred, __WR __uint8*, __ulong4, __ulong4);
#elif __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_pred_packl_2src(__vpred,   __WR __int16*, __long8,  __long8);
void __OVBIFM __vstore_pred_packl_2src(__vpred,   __WR __uint16*, __ulong8, __ulong8);
void __OVBIFM __vstore_pred_packh_2src(__vpred,   __WR __int16*, __long8,   __long8);
void __OVBIFM __vstore_pred_packh_2src(__vpred,   __WR __uint16*, __ulong8, __ulong8);
void __OVBIFM __vstore_pred_packhs1_2src(__vpred, __WR __int16*, __long8,   __long8);
void __OVBIFM __vstore_pred_packhs1_2src(__vpred, __WR __uint16*, __ulong8, __ulong8);
#endif

/* VSTPDPACKL, VSTPDPACKH, VSTPDPACKHS1: PRED CORRESPONDS TO PACKED DATA */
#if __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_pred_packl_long_2src(__vpred,   __WR __long4*, __long4, __long4);
void __OVBIFM __vstore_pred_packl_long_2src(__vpred,   __WR __ulong4*, __ulong4,__ulong4);
void __OVBIFM __vstore_pred_packh_long_2src(__vpred,   __WR __long4*, __long4, __long4);
void __OVBIFM __vstore_pred_packh_long_2src(__vpred,   __WR __ulong4*, __ulong4,__ulong4);
void __OVBIFM __vstore_pred_packhs1_long_2src(__vpred, __WR __long4*, __long4, __long4);
void __OVBIFM __vstore_pred_packhs1_long_2src(__vpred, __WR __ulong4*, __ulong4,__ulong4);
#elif __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_pred_packl_long_2src(__vpred,   __WR __long8*, __long8, __long8);
void __OVBIFM __vstore_pred_packl_long_2src(__vpred,   __WR __ulong8*, __ulong8,__ulong8);
void __OVBIFM __vstore_pred_packh_long_2src(__vpred,   __WR __long8*, __long8, __long8);
void __OVBIFM __vstore_pred_packh_long_2src(__vpred,   __WR __ulong8*, __ulong8,__ulong8);
void __OVBIFM __vstore_pred_packhs1_long_2src(__vpred, __WR __long8*, __long8, __long8);
void __OVBIFM __vstore_pred_packhs1_long_2src(__vpred, __WR __ulong8*, __ulong8,__ulong8);
#endif

/* VSTPBITRWH */
#if __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_pred_reverse_bit(__vpred, __WR __cshort16*, __cshort16);
#elif __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_pred_reverse_bit(__vpred, __WR __cshort8*, __cshort8);
#endif

/* VSTPBITRDW */
#if __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_pred_reverse_bit(__vpred, __WR __cint8*,   __cint8);
void __OVBIFM __vstore_pred_reverse_bit(__vpred, __WR __cfloat8*, __cfloat8);
#elif __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_pred_reverse_bit(__vpred, __WR __cint4*,   __cint4);
void __OVBIFM __vstore_pred_reverse_bit(__vpred, __WR __cfloat4*, __cfloat4);
#endif

/* STPREDB  (C syntax):
        __vpred src;
        *(__vpred *)ptr = src;
*/

/* STPREDB - store predicate according to type byte (every bit) */
void __BIFM __store_predicate_char(__WR __ulong*, __vpred);

/* STPREDH - store predicate according to type short (every 2-bits) */
void __BIFM __store_predicate_short(__WR __uint*, __vpred);

/* STPREDW - store predicate according to type int (every 4-bits) */
void __BIFM __store_predicate_int(__WR __ushort*, __vpred);

/* STPREDD - store predicate according to type long (every 8-bits) */
void __BIFM __store_predicate_long(__WR __uchar*, __vpred);


/*----------------------------------------------------------------------------*/
/* ID: __pack_vpred                                                           */
/*----------------------------------------------------------------------------*/
/* Non-Scaling Implementations (cannot vectorize) */
/*
BITPACK
*/
__vpred __OVBIF __pack_vpred(unsigned long, __CST(0, 63) unsigned char);
__vpred __OVBIF __pack_vpred(__vpred, __CST(0, 63) unsigned char);

/*----------------------------------------------------------------------------*/
/* ID: __expand_vpred                                                         */
/*----------------------------------------------------------------------------*/
/* Non-Scaling Implementations (cannot vectorize) */
/*
BITXPND
*/
__vpred __OVBIF __expand_vpred(unsigned long, __CST(0, 63) unsigned char);
__vpred __OVBIF __expand_vpred(__vpred, __CST(0, 63) unsigned char);

/* AUTOGEN MARKER */
/*----------------------------------------------------------------------------*/
/* ID: __add                                                                  */
/*----------------------------------------------------------------------------*/
/*
VADDCB
*/
signed char __OVBIF __add(__vpred, signed char, signed char);
__char2 __OVBIF __add(__vpred, __char2, __char2);
__char3 __OVBIF __add(__vpred, __char3, __char3);
__char4 __OVBIF __add(__vpred, __char4, __char4);
__char8 __OVBIF __add(__vpred, __char8, __char8);
__char16 __OVBIF __add(__vpred, __char16, __char16);
__char32 __OVBIF __add(__vpred, __char32, __char32);
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __add(__vpred, __char64, __char64);
#endif
__uchar __OVBIF __add(__vpred, __uchar, __uchar);
__uchar2 __OVBIF __add(__vpred, __uchar2, __uchar2);
__uchar3 __OVBIF __add(__vpred, __uchar3, __uchar3);
__uchar4 __OVBIF __add(__vpred, __uchar4, __uchar4);
__uchar8 __OVBIF __add(__vpred, __uchar8, __uchar8);
__uchar16 __OVBIF __add(__vpred, __uchar16, __uchar16);
__uchar32 __OVBIF __add(__vpred, __uchar32, __uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __add(__vpred, __uchar64, __uchar64);
#endif
/*
VADDCH
*/
short __OVBIF __add(__vpred, short, short);
__short2 __OVBIF __add(__vpred, __short2, __short2);
__short3 __OVBIF __add(__vpred, __short3, __short3);
__short4 __OVBIF __add(__vpred, __short4, __short4);
__short8 __OVBIF __add(__vpred, __short8, __short8);
__short16 __OVBIF __add(__vpred, __short16, __short16);
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __add(__vpred, __short32, __short32);
#endif
__ushort __OVBIF __add(__vpred, __ushort, __ushort);
__ushort2 __OVBIF __add(__vpred, __ushort2, __ushort2);
__ushort3 __OVBIF __add(__vpred, __ushort3, __ushort3);
__ushort4 __OVBIF __add(__vpred, __ushort4, __ushort4);
__ushort8 __OVBIF __add(__vpred, __ushort8, __ushort8);
__ushort16 __OVBIF __add(__vpred, __ushort16, __ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __add(__vpred, __ushort32, __ushort32);
#endif
/*
VADDCW
*/
int __OVBIF __add(__vpred, int, int);
__int2 __OVBIF __add(__vpred, __int2, __int2);
__int3 __OVBIF __add(__vpred, __int3, __int3);
__int4 __OVBIF __add(__vpred, __int4, __int4);
__int8 __OVBIF __add(__vpred, __int8, __int8);
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __add(__vpred, __int16, __int16);
#endif
__uint __OVBIF __add(__vpred, __uint, __uint);
__uint2 __OVBIF __add(__vpred, __uint2, __uint2);
__uint3 __OVBIF __add(__vpred, __uint3, __uint3);
__uint4 __OVBIF __add(__vpred, __uint4, __uint4);
__uint8 __OVBIF __add(__vpred, __uint8, __uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __add(__vpred, __uint16, __uint16);
#endif
/*
VADDCD
*/
long __OVBIF __add(__vpred, long, long);
__long2 __OVBIF __add(__vpred, __long2, __long2);
__long3 __OVBIF __add(__vpred, __long3, __long3);
__long4 __OVBIF __add(__vpred, __long4, __long4);
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __add(__vpred, __long8, __long8);
#endif
__ulong __OVBIF __add(__vpred, __ulong, __ulong);
__ulong2 __OVBIF __add(__vpred, __ulong2, __ulong2);
__ulong3 __OVBIF __add(__vpred, __ulong3, __ulong3);
__ulong4 __OVBIF __add(__vpred, __ulong4, __ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __add(__vpred, __ulong8, __ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __and                                                                  */
/*----------------------------------------------------------------------------*/
/*
AND
*/
__vpred __OVBIF __and(__vpred, __vpred);

/*----------------------------------------------------------------------------*/
/* ID: __andn                                                                 */
/*----------------------------------------------------------------------------*/
/*
ANDN
*/
__vpred __OVBIF __andn(__vpred, __vpred);

/*----------------------------------------------------------------------------*/
/* ID: __bit_reverse                                                          */
/*----------------------------------------------------------------------------*/
/*
BITR
*/
__vpred __OVBIF __bit_reverse(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __cmp_eq_pred                                                          */
/*----------------------------------------------------------------------------*/
/*
VCMPEQB
*/
__vpred __OVBIF __cmp_eq_pred(signed char, signed char);
__vpred __OVBIF __cmp_eq_pred(__char2, __char2);
__vpred __OVBIF __cmp_eq_pred(__char3, __char3);
__vpred __OVBIF __cmp_eq_pred(__char4, __char4);
__vpred __OVBIF __cmp_eq_pred(__char8, __char8);
__vpred __OVBIF __cmp_eq_pred(__char16, __char16);
__vpred __OVBIF __cmp_eq_pred(__char32, __char32);
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __OVBIF __cmp_eq_pred(__char64, __char64);
#endif
__vpred __OVBIF __cmp_eq_pred(__uchar, __uchar);
__vpred __OVBIF __cmp_eq_pred(__uchar2, __uchar2);
__vpred __OVBIF __cmp_eq_pred(__uchar3, __uchar3);
__vpred __OVBIF __cmp_eq_pred(__uchar4, __uchar4);
__vpred __OVBIF __cmp_eq_pred(__uchar8, __uchar8);
__vpred __OVBIF __cmp_eq_pred(__uchar16, __uchar16);
__vpred __OVBIF __cmp_eq_pred(__uchar32, __uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __OVBIF __cmp_eq_pred(__uchar64, __uchar64);
#endif
/*
VCMPEQH
*/
__vpred __OVBIF __cmp_eq_pred(short, short);
__vpred __OVBIF __cmp_eq_pred(__short2, __short2);
__vpred __OVBIF __cmp_eq_pred(__short3, __short3);
__vpred __OVBIF __cmp_eq_pred(__short4, __short4);
__vpred __OVBIF __cmp_eq_pred(__short8, __short8);
__vpred __OVBIF __cmp_eq_pred(__short16, __short16);
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __OVBIF __cmp_eq_pred(__short32, __short32);
#endif
__vpred __OVBIF __cmp_eq_pred(__ushort, __ushort);
__vpred __OVBIF __cmp_eq_pred(__ushort2, __ushort2);
__vpred __OVBIF __cmp_eq_pred(__ushort3, __ushort3);
__vpred __OVBIF __cmp_eq_pred(__ushort4, __ushort4);
__vpred __OVBIF __cmp_eq_pred(__ushort8, __ushort8);
__vpred __OVBIF __cmp_eq_pred(__ushort16, __ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __OVBIF __cmp_eq_pred(__ushort32, __ushort32);
#endif
/*
VCMPEQW
*/
__vpred __OVBIF __cmp_eq_pred(int, int);
__vpred __OVBIF __cmp_eq_pred(__int2, __int2);
__vpred __OVBIF __cmp_eq_pred(__int3, __int3);
__vpred __OVBIF __cmp_eq_pred(__int4, __int4);
__vpred __OVBIF __cmp_eq_pred(__int8, __int8);
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __OVBIF __cmp_eq_pred(__int16, __int16);
#endif
__vpred __OVBIF __cmp_eq_pred(__uint, __uint);
__vpred __OVBIF __cmp_eq_pred(__uint2, __uint2);
__vpred __OVBIF __cmp_eq_pred(__uint3, __uint3);
__vpred __OVBIF __cmp_eq_pred(__uint4, __uint4);
__vpred __OVBIF __cmp_eq_pred(__uint8, __uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __OVBIF __cmp_eq_pred(__uint16, __uint16);
#endif
/*
VCMPEQSP
*/
__vpred __OVBIF __cmp_eq_pred(float, float);
__vpred __OVBIF __cmp_eq_pred(__float2, __float2);
__vpred __OVBIF __cmp_eq_pred(__float3, __float3);
__vpred __OVBIF __cmp_eq_pred(__float4, __float4);
__vpred __OVBIF __cmp_eq_pred(__float8, __float8);
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __OVBIF __cmp_eq_pred(__float16, __float16);
#endif
/*
VCMPEQD
*/
__vpred __OVBIF __cmp_eq_pred(long, long);
__vpred __OVBIF __cmp_eq_pred(__long2, __long2);
__vpred __OVBIF __cmp_eq_pred(__long3, __long3);
__vpred __OVBIF __cmp_eq_pred(__long4, __long4);
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __OVBIF __cmp_eq_pred(__long8, __long8);
#endif
__vpred __OVBIF __cmp_eq_pred(__ulong, __ulong);
__vpred __OVBIF __cmp_eq_pred(__ulong2, __ulong2);
__vpred __OVBIF __cmp_eq_pred(__ulong3, __ulong3);
__vpred __OVBIF __cmp_eq_pred(__ulong4, __ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __OVBIF __cmp_eq_pred(__ulong8, __ulong8);
#endif
/*
VCMPEQDP
*/
__vpred __OVBIF __cmp_eq_pred(double, double);
__vpred __OVBIF __cmp_eq_pred(__double2, __double2);
__vpred __OVBIF __cmp_eq_pred(__double3, __double3);
__vpred __OVBIF __cmp_eq_pred(__double4, __double4);
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __OVBIF __cmp_eq_pred(__double8, __double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __cmp_ge_pred                                                          */
/*----------------------------------------------------------------------------*/
/*
VCMPGEB
*/
__vpred __OVBIF __cmp_ge_pred(signed char, signed char);
__vpred __OVBIF __cmp_ge_pred(__char2, __char2);
__vpred __OVBIF __cmp_ge_pred(__char3, __char3);
__vpred __OVBIF __cmp_ge_pred(__char4, __char4);
__vpred __OVBIF __cmp_ge_pred(__char8, __char8);
__vpred __OVBIF __cmp_ge_pred(__char16, __char16);
__vpred __OVBIF __cmp_ge_pred(__char32, __char32);
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __OVBIF __cmp_ge_pred(__char64, __char64);
#endif
/*
VCMPGEUB
*/
__vpred __OVBIF __cmp_ge_pred(__uchar, __uchar);
__vpred __OVBIF __cmp_ge_pred(__uchar2, __uchar2);
__vpred __OVBIF __cmp_ge_pred(__uchar3, __uchar3);
__vpred __OVBIF __cmp_ge_pred(__uchar4, __uchar4);
__vpred __OVBIF __cmp_ge_pred(__uchar8, __uchar8);
__vpred __OVBIF __cmp_ge_pred(__uchar16, __uchar16);
__vpred __OVBIF __cmp_ge_pred(__uchar32, __uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __OVBIF __cmp_ge_pred(__uchar64, __uchar64);
#endif
/*
VCMPGEH
*/
__vpred __OVBIF __cmp_ge_pred(short, short);
__vpred __OVBIF __cmp_ge_pred(__short2, __short2);
__vpred __OVBIF __cmp_ge_pred(__short3, __short3);
__vpred __OVBIF __cmp_ge_pred(__short4, __short4);
__vpred __OVBIF __cmp_ge_pred(__short8, __short8);
__vpred __OVBIF __cmp_ge_pred(__short16, __short16);
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __OVBIF __cmp_ge_pred(__short32, __short32);
#endif
/*
VCMPGEUH
*/
__vpred __OVBIF __cmp_ge_pred(__ushort, __ushort);
__vpred __OVBIF __cmp_ge_pred(__ushort2, __ushort2);
__vpred __OVBIF __cmp_ge_pred(__ushort3, __ushort3);
__vpred __OVBIF __cmp_ge_pred(__ushort4, __ushort4);
__vpred __OVBIF __cmp_ge_pred(__ushort8, __ushort8);
__vpred __OVBIF __cmp_ge_pred(__ushort16, __ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __OVBIF __cmp_ge_pred(__ushort32, __ushort32);
#endif
/*
VCMPGEW
*/
__vpred __OVBIF __cmp_ge_pred(int, int);
__vpred __OVBIF __cmp_ge_pred(__int2, __int2);
__vpred __OVBIF __cmp_ge_pred(__int3, __int3);
__vpred __OVBIF __cmp_ge_pred(__int4, __int4);
__vpred __OVBIF __cmp_ge_pred(__int8, __int8);
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __OVBIF __cmp_ge_pred(__int16, __int16);
#endif
/*
VCMPGEUW
*/
__vpred __OVBIF __cmp_ge_pred(__uint, __uint);
__vpred __OVBIF __cmp_ge_pred(__uint2, __uint2);
__vpred __OVBIF __cmp_ge_pred(__uint3, __uint3);
__vpred __OVBIF __cmp_ge_pred(__uint4, __uint4);
__vpred __OVBIF __cmp_ge_pred(__uint8, __uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __OVBIF __cmp_ge_pred(__uint16, __uint16);
#endif
/*
VCMPLESP
*/
__vpred __OVBIF __cmp_ge_pred(float, float);
__vpred __OVBIF __cmp_ge_pred(__float2, __float2);
__vpred __OVBIF __cmp_ge_pred(__float3, __float3);
__vpred __OVBIF __cmp_ge_pred(__float4, __float4);
__vpred __OVBIF __cmp_ge_pred(__float8, __float8);
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __OVBIF __cmp_ge_pred(__float16, __float16);
#endif
/*
VCMPGED
*/
__vpred __OVBIF __cmp_ge_pred(long, long);
__vpred __OVBIF __cmp_ge_pred(__long2, __long2);
__vpred __OVBIF __cmp_ge_pred(__long3, __long3);
__vpred __OVBIF __cmp_ge_pred(__long4, __long4);
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __OVBIF __cmp_ge_pred(__long8, __long8);
#endif
/*
VCMPGEUD
*/
__vpred __OVBIF __cmp_ge_pred(__ulong, __ulong);
__vpred __OVBIF __cmp_ge_pred(__ulong2, __ulong2);
__vpred __OVBIF __cmp_ge_pred(__ulong3, __ulong3);
__vpred __OVBIF __cmp_ge_pred(__ulong4, __ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __OVBIF __cmp_ge_pred(__ulong8, __ulong8);
#endif
/*
VCMPLEDP
*/
__vpred __OVBIF __cmp_ge_pred(double, double);
__vpred __OVBIF __cmp_ge_pred(__double2, __double2);
__vpred __OVBIF __cmp_ge_pred(__double3, __double3);
__vpred __OVBIF __cmp_ge_pred(__double4, __double4);
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __OVBIF __cmp_ge_pred(__double8, __double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __cmp_gt_pred                                                          */
/*----------------------------------------------------------------------------*/
/*
VCMPGTB
*/
__vpred __OVBIF __cmp_gt_pred(signed char, signed char);
__vpred __OVBIF __cmp_gt_pred(__char2, __char2);
__vpred __OVBIF __cmp_gt_pred(__char3, __char3);
__vpred __OVBIF __cmp_gt_pred(__char4, __char4);
__vpred __OVBIF __cmp_gt_pred(__char8, __char8);
__vpred __OVBIF __cmp_gt_pred(__char16, __char16);
__vpred __OVBIF __cmp_gt_pred(__char32, __char32);
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __OVBIF __cmp_gt_pred(__char64, __char64);
#endif
/*
VCMPGTUB
*/
__vpred __OVBIF __cmp_gt_pred(__uchar, __uchar);
__vpred __OVBIF __cmp_gt_pred(__uchar2, __uchar2);
__vpred __OVBIF __cmp_gt_pred(__uchar3, __uchar3);
__vpred __OVBIF __cmp_gt_pred(__uchar4, __uchar4);
__vpred __OVBIF __cmp_gt_pred(__uchar8, __uchar8);
__vpred __OVBIF __cmp_gt_pred(__uchar16, __uchar16);
__vpred __OVBIF __cmp_gt_pred(__uchar32, __uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __OVBIF __cmp_gt_pred(__uchar64, __uchar64);
#endif
/*
VCMPGTH
*/
__vpred __OVBIF __cmp_gt_pred(short, short);
__vpred __OVBIF __cmp_gt_pred(__short2, __short2);
__vpred __OVBIF __cmp_gt_pred(__short3, __short3);
__vpred __OVBIF __cmp_gt_pred(__short4, __short4);
__vpred __OVBIF __cmp_gt_pred(__short8, __short8);
__vpred __OVBIF __cmp_gt_pred(__short16, __short16);
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __OVBIF __cmp_gt_pred(__short32, __short32);
#endif
/*
VCMPGTUH
*/
__vpred __OVBIF __cmp_gt_pred(__ushort, __ushort);
__vpred __OVBIF __cmp_gt_pred(__ushort2, __ushort2);
__vpred __OVBIF __cmp_gt_pred(__ushort3, __ushort3);
__vpred __OVBIF __cmp_gt_pred(__ushort4, __ushort4);
__vpred __OVBIF __cmp_gt_pred(__ushort8, __ushort8);
__vpred __OVBIF __cmp_gt_pred(__ushort16, __ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __OVBIF __cmp_gt_pred(__ushort32, __ushort32);
#endif
/*
VCMPGTW
*/
__vpred __OVBIF __cmp_gt_pred(int, int);
__vpred __OVBIF __cmp_gt_pred(__int2, __int2);
__vpred __OVBIF __cmp_gt_pred(__int3, __int3);
__vpred __OVBIF __cmp_gt_pred(__int4, __int4);
__vpred __OVBIF __cmp_gt_pred(__int8, __int8);
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __OVBIF __cmp_gt_pred(__int16, __int16);
#endif
/*
VCMPGTUW
*/
__vpred __OVBIF __cmp_gt_pred(__uint, __uint);
__vpred __OVBIF __cmp_gt_pred(__uint2, __uint2);
__vpred __OVBIF __cmp_gt_pred(__uint3, __uint3);
__vpred __OVBIF __cmp_gt_pred(__uint4, __uint4);
__vpred __OVBIF __cmp_gt_pred(__uint8, __uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __OVBIF __cmp_gt_pred(__uint16, __uint16);
#endif
/*
VCMPLTSP
*/
__vpred __OVBIF __cmp_gt_pred(float, float);
__vpred __OVBIF __cmp_gt_pred(__float2, __float2);
__vpred __OVBIF __cmp_gt_pred(__float3, __float3);
__vpred __OVBIF __cmp_gt_pred(__float4, __float4);
__vpred __OVBIF __cmp_gt_pred(__float8, __float8);
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __OVBIF __cmp_gt_pred(__float16, __float16);
#endif
/*
VCMPGTD
*/
__vpred __OVBIF __cmp_gt_pred(long, long);
__vpred __OVBIF __cmp_gt_pred(__long2, __long2);
__vpred __OVBIF __cmp_gt_pred(__long3, __long3);
__vpred __OVBIF __cmp_gt_pred(__long4, __long4);
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __OVBIF __cmp_gt_pred(__long8, __long8);
#endif
/*
VCMPGTUD
*/
__vpred __OVBIF __cmp_gt_pred(__ulong, __ulong);
__vpred __OVBIF __cmp_gt_pred(__ulong2, __ulong2);
__vpred __OVBIF __cmp_gt_pred(__ulong3, __ulong3);
__vpred __OVBIF __cmp_gt_pred(__ulong4, __ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __OVBIF __cmp_gt_pred(__ulong8, __ulong8);
#endif
/*
VCMPLTDP
*/
__vpred __OVBIF __cmp_gt_pred(double, double);
__vpred __OVBIF __cmp_gt_pred(__double2, __double2);
__vpred __OVBIF __cmp_gt_pred(__double3, __double3);
__vpred __OVBIF __cmp_gt_pred(__double4, __double4);
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __OVBIF __cmp_gt_pred(__double8, __double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __cmp_le_pred                                                          */
/*----------------------------------------------------------------------------*/
/*
VCMPGEB
*/
__vpred __OVBIF __cmp_le_pred(signed char, signed char);
__vpred __OVBIF __cmp_le_pred(__char2, __char2);
__vpred __OVBIF __cmp_le_pred(__char3, __char3);
__vpred __OVBIF __cmp_le_pred(__char4, __char4);
__vpred __OVBIF __cmp_le_pred(__char8, __char8);
__vpred __OVBIF __cmp_le_pred(__char16, __char16);
__vpred __OVBIF __cmp_le_pred(__char32, __char32);
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __OVBIF __cmp_le_pred(__char64, __char64);
#endif
/*
VCMPGEUB
*/
__vpred __OVBIF __cmp_le_pred(__uchar, __uchar);
__vpred __OVBIF __cmp_le_pred(__uchar2, __uchar2);
__vpred __OVBIF __cmp_le_pred(__uchar3, __uchar3);
__vpred __OVBIF __cmp_le_pred(__uchar4, __uchar4);
__vpred __OVBIF __cmp_le_pred(__uchar8, __uchar8);
__vpred __OVBIF __cmp_le_pred(__uchar16, __uchar16);
__vpred __OVBIF __cmp_le_pred(__uchar32, __uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __OVBIF __cmp_le_pred(__uchar64, __uchar64);
#endif
/*
VCMPGEH
*/
__vpred __OVBIF __cmp_le_pred(short, short);
__vpred __OVBIF __cmp_le_pred(__short2, __short2);
__vpred __OVBIF __cmp_le_pred(__short3, __short3);
__vpred __OVBIF __cmp_le_pred(__short4, __short4);
__vpred __OVBIF __cmp_le_pred(__short8, __short8);
__vpred __OVBIF __cmp_le_pred(__short16, __short16);
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __OVBIF __cmp_le_pred(__short32, __short32);
#endif
/*
VCMPGEUH
*/
__vpred __OVBIF __cmp_le_pred(__ushort, __ushort);
__vpred __OVBIF __cmp_le_pred(__ushort2, __ushort2);
__vpred __OVBIF __cmp_le_pred(__ushort3, __ushort3);
__vpred __OVBIF __cmp_le_pred(__ushort4, __ushort4);
__vpred __OVBIF __cmp_le_pred(__ushort8, __ushort8);
__vpred __OVBIF __cmp_le_pred(__ushort16, __ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __OVBIF __cmp_le_pred(__ushort32, __ushort32);
#endif
/*
VCMPGEW
*/
__vpred __OVBIF __cmp_le_pred(int, int);
__vpred __OVBIF __cmp_le_pred(__int2, __int2);
__vpred __OVBIF __cmp_le_pred(__int3, __int3);
__vpred __OVBIF __cmp_le_pred(__int4, __int4);
__vpred __OVBIF __cmp_le_pred(__int8, __int8);
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __OVBIF __cmp_le_pred(__int16, __int16);
#endif
/*
VCMPGEUW
*/
__vpred __OVBIF __cmp_le_pred(__uint, __uint);
__vpred __OVBIF __cmp_le_pred(__uint2, __uint2);
__vpred __OVBIF __cmp_le_pred(__uint3, __uint3);
__vpred __OVBIF __cmp_le_pred(__uint4, __uint4);
__vpred __OVBIF __cmp_le_pred(__uint8, __uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __OVBIF __cmp_le_pred(__uint16, __uint16);
#endif
/*
VCMPLESP
*/
__vpred __OVBIF __cmp_le_pred(float, float);
__vpred __OVBIF __cmp_le_pred(__float2, __float2);
__vpred __OVBIF __cmp_le_pred(__float3, __float3);
__vpred __OVBIF __cmp_le_pred(__float4, __float4);
__vpred __OVBIF __cmp_le_pred(__float8, __float8);
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __OVBIF __cmp_le_pred(__float16, __float16);
#endif
/*
VCMPGED
*/
__vpred __OVBIF __cmp_le_pred(long, long);
__vpred __OVBIF __cmp_le_pred(__long2, __long2);
__vpred __OVBIF __cmp_le_pred(__long3, __long3);
__vpred __OVBIF __cmp_le_pred(__long4, __long4);
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __OVBIF __cmp_le_pred(__long8, __long8);
#endif
/*
VCMPGEUD
*/
__vpred __OVBIF __cmp_le_pred(__ulong, __ulong);
__vpred __OVBIF __cmp_le_pred(__ulong2, __ulong2);
__vpred __OVBIF __cmp_le_pred(__ulong3, __ulong3);
__vpred __OVBIF __cmp_le_pred(__ulong4, __ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __OVBIF __cmp_le_pred(__ulong8, __ulong8);
#endif
/*
VCMPLEDP
*/
__vpred __OVBIF __cmp_le_pred(double, double);
__vpred __OVBIF __cmp_le_pred(__double2, __double2);
__vpred __OVBIF __cmp_le_pred(__double3, __double3);
__vpred __OVBIF __cmp_le_pred(__double4, __double4);
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __OVBIF __cmp_le_pred(__double8, __double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __cmp_lt_pred                                                          */
/*----------------------------------------------------------------------------*/
/*
VCMPGTB
*/
__vpred __OVBIF __cmp_lt_pred(signed char, signed char);
__vpred __OVBIF __cmp_lt_pred(__char2, __char2);
__vpred __OVBIF __cmp_lt_pred(__char3, __char3);
__vpred __OVBIF __cmp_lt_pred(__char4, __char4);
__vpred __OVBIF __cmp_lt_pred(__char8, __char8);
__vpred __OVBIF __cmp_lt_pred(__char16, __char16);
__vpred __OVBIF __cmp_lt_pred(__char32, __char32);
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __OVBIF __cmp_lt_pred(__char64, __char64);
#endif
/*
VCMPGTUB
*/
__vpred __OVBIF __cmp_lt_pred(__uchar, __uchar);
__vpred __OVBIF __cmp_lt_pred(__uchar2, __uchar2);
__vpred __OVBIF __cmp_lt_pred(__uchar3, __uchar3);
__vpred __OVBIF __cmp_lt_pred(__uchar4, __uchar4);
__vpred __OVBIF __cmp_lt_pred(__uchar8, __uchar8);
__vpred __OVBIF __cmp_lt_pred(__uchar16, __uchar16);
__vpred __OVBIF __cmp_lt_pred(__uchar32, __uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __OVBIF __cmp_lt_pred(__uchar64, __uchar64);
#endif
/*
VCMPGTH
*/
__vpred __OVBIF __cmp_lt_pred(short, short);
__vpred __OVBIF __cmp_lt_pred(__short2, __short2);
__vpred __OVBIF __cmp_lt_pred(__short3, __short3);
__vpred __OVBIF __cmp_lt_pred(__short4, __short4);
__vpred __OVBIF __cmp_lt_pred(__short8, __short8);
__vpred __OVBIF __cmp_lt_pred(__short16, __short16);
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __OVBIF __cmp_lt_pred(__short32, __short32);
#endif
/*
VCMPGTUH
*/
__vpred __OVBIF __cmp_lt_pred(__ushort, __ushort);
__vpred __OVBIF __cmp_lt_pred(__ushort2, __ushort2);
__vpred __OVBIF __cmp_lt_pred(__ushort3, __ushort3);
__vpred __OVBIF __cmp_lt_pred(__ushort4, __ushort4);
__vpred __OVBIF __cmp_lt_pred(__ushort8, __ushort8);
__vpred __OVBIF __cmp_lt_pred(__ushort16, __ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __OVBIF __cmp_lt_pred(__ushort32, __ushort32);
#endif
/*
VCMPGTW
*/
__vpred __OVBIF __cmp_lt_pred(int, int);
__vpred __OVBIF __cmp_lt_pred(__int2, __int2);
__vpred __OVBIF __cmp_lt_pred(__int3, __int3);
__vpred __OVBIF __cmp_lt_pred(__int4, __int4);
__vpred __OVBIF __cmp_lt_pred(__int8, __int8);
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __OVBIF __cmp_lt_pred(__int16, __int16);
#endif
/*
VCMPGTUW
*/
__vpred __OVBIF __cmp_lt_pred(__uint, __uint);
__vpred __OVBIF __cmp_lt_pred(__uint2, __uint2);
__vpred __OVBIF __cmp_lt_pred(__uint3, __uint3);
__vpred __OVBIF __cmp_lt_pred(__uint4, __uint4);
__vpred __OVBIF __cmp_lt_pred(__uint8, __uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __OVBIF __cmp_lt_pred(__uint16, __uint16);
#endif
/*
VCMPLTSP
*/
__vpred __OVBIF __cmp_lt_pred(float, float);
__vpred __OVBIF __cmp_lt_pred(__float2, __float2);
__vpred __OVBIF __cmp_lt_pred(__float3, __float3);
__vpred __OVBIF __cmp_lt_pred(__float4, __float4);
__vpred __OVBIF __cmp_lt_pred(__float8, __float8);
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __OVBIF __cmp_lt_pred(__float16, __float16);
#endif
/*
VCMPGTD
*/
__vpred __OVBIF __cmp_lt_pred(long, long);
__vpred __OVBIF __cmp_lt_pred(__long2, __long2);
__vpred __OVBIF __cmp_lt_pred(__long3, __long3);
__vpred __OVBIF __cmp_lt_pred(__long4, __long4);
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __OVBIF __cmp_lt_pred(__long8, __long8);
#endif
/*
VCMPGTUD
*/
__vpred __OVBIF __cmp_lt_pred(__ulong, __ulong);
__vpred __OVBIF __cmp_lt_pred(__ulong2, __ulong2);
__vpred __OVBIF __cmp_lt_pred(__ulong3, __ulong3);
__vpred __OVBIF __cmp_lt_pred(__ulong4, __ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __OVBIF __cmp_lt_pred(__ulong8, __ulong8);
#endif
/*
VCMPLTDP
*/
__vpred __OVBIF __cmp_lt_pred(double, double);
__vpred __OVBIF __cmp_lt_pred(__double2, __double2);
__vpred __OVBIF __cmp_lt_pred(__double3, __double3);
__vpred __OVBIF __cmp_lt_pred(__double4, __double4);
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __OVBIF __cmp_lt_pred(__double8, __double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __compress_set_bits_left                                               */
/*----------------------------------------------------------------------------*/
/*
COMPRESSL
*/
__vpred __OVBIF __compress_set_bits_left(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __compress_set_bits_right                                              */
/*----------------------------------------------------------------------------*/
/*
COMPRESSR
*/
__vpred __OVBIF __compress_set_bits_right(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __decimate_char                                                        */
/*----------------------------------------------------------------------------*/
/*
DECIMATEB
*/
__vpred __BIF __decimate_char(__vpred, __vpred);

/*----------------------------------------------------------------------------*/
/* ID: __decimate_int                                                         */
/*----------------------------------------------------------------------------*/
/*
DECIMATEW
*/
__vpred __BIF __decimate_int(__vpred, __vpred);

/*----------------------------------------------------------------------------*/
/* ID: __decimate_long                                                        */
/*----------------------------------------------------------------------------*/
/*
DECIMATED
*/
__vpred __BIF __decimate_long(__vpred, __vpred);

/*----------------------------------------------------------------------------*/
/* ID: __decimate_short                                                       */
/*----------------------------------------------------------------------------*/
/*
DECIMATEH
*/
__vpred __BIF __decimate_short(__vpred, __vpred);

/*----------------------------------------------------------------------------*/
/* ID: __duplicate_pred_high_char                                             */
/*----------------------------------------------------------------------------*/
/*
PDUPH2B
*/
__vpred __BIF __duplicate_pred_high_char(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __duplicate_pred_high_int                                              */
/*----------------------------------------------------------------------------*/
/*
PDUPH2W
*/
__vpred __BIF __duplicate_pred_high_int(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __duplicate_pred_high_long                                             */
/*----------------------------------------------------------------------------*/
/*
PDUPH2D
*/
__vpred __BIF __duplicate_pred_high_long(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __duplicate_pred_high_short                                            */
/*----------------------------------------------------------------------------*/
/*
PDUPH2H
*/
__vpred __BIF __duplicate_pred_high_short(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __duplicate_pred_low_char                                              */
/*----------------------------------------------------------------------------*/
/*
PDUPL2B
*/
__vpred __BIF __duplicate_pred_low_char(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __duplicate_pred_low_int                                               */
/*----------------------------------------------------------------------------*/
/*
PDUPL2W
*/
__vpred __BIF __duplicate_pred_low_int(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __duplicate_pred_low_long                                              */
/*----------------------------------------------------------------------------*/
/*
PDUPL2D
*/
__vpred __BIF __duplicate_pred_low_long(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __duplicate_pred_low_short                                             */
/*----------------------------------------------------------------------------*/
/*
PDUPL2H
*/
__vpred __BIF __duplicate_pred_low_short(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __expand                                                               */
/*----------------------------------------------------------------------------*/
/*
VPXPND
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __OVBIF __expand(__vpred);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __expand(__vpred);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __gather_set_bits                                                      */
/*----------------------------------------------------------------------------*/
/*
VGATHERB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __OVBIF __gather_set_bits(__vpred, __char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __gather_set_bits(__vpred, __char64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __gather_unset_bits                                                    */
/*----------------------------------------------------------------------------*/
/*
VGATHERNB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __OVBIF __gather_unset_bits(__vpred, __char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __gather_unset_bits(__vpred, __char64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __mask_char                                                            */
/*----------------------------------------------------------------------------*/
/*
MASKB
*/
__vpred __OVBIF __mask_char(__uchar __CST(0, 63));
__vpred __OVBIF __mask_char(__uint);

/*----------------------------------------------------------------------------*/
/* ID: __mask_int                                                             */
/*----------------------------------------------------------------------------*/
/*
MASKW
*/
__vpred __OVBIF __mask_int(__uchar __CST(0, 63));
__vpred __OVBIF __mask_int(__uint);

/*----------------------------------------------------------------------------*/
/* ID: __mask_long                                                            */
/*----------------------------------------------------------------------------*/
/*
MASKD
*/
__vpred __OVBIF __mask_long(__uchar __CST(0, 63));
__vpred __OVBIF __mask_long(__uint);

/*----------------------------------------------------------------------------*/
/* ID: __mask_short                                                           */
/*----------------------------------------------------------------------------*/
/*
MASKH
*/
__vpred __OVBIF __mask_short(__uchar __CST(0, 63));
__vpred __OVBIF __mask_short(__uint);

/*----------------------------------------------------------------------------*/
/* ID: __max_circ_pred                                                        */
/*----------------------------------------------------------------------------*/
/*

VCMAXPB
void __max_circ_pred(signed char, signed char&, __vpred&);
void __max_circ_pred(char2, char2&, __vpred&);
void __max_circ_pred(char3, char3&, __vpred&);
void __max_circ_pred(char4, char4&, __vpred&);
void __max_circ_pred(char8, char8&, __vpred&);
void __max_circ_pred(char16, char16&, __vpred&);
void __max_circ_pred(char32, char32&, __vpred&);
#if __C7X_VEC_SIZE_BITS__ == 512
void __max_circ_pred(char64, char64&, __vpred&);
#endif

VCMAXPH
void __max_circ_pred(short, short&, __vpred&);
void __max_circ_pred(short2, short2&, __vpred&);
void __max_circ_pred(short3, short3&, __vpred&);
void __max_circ_pred(short4, short4&, __vpred&);
void __max_circ_pred(short8, short8&, __vpred&);
void __max_circ_pred(short16, short16&, __vpred&);
#if __C7X_VEC_SIZE_BITS__ == 512
void __max_circ_pred(short32, short32&, __vpred&);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __max_index                                                            */
/*----------------------------------------------------------------------------*/
/*

VMAXPB
void __max_index(signed char, signed char&, __vpred&);
void __max_index(char2, char2&, __vpred&);
void __max_index(char3, char3&, __vpred&);
void __max_index(char4, char4&, __vpred&);
void __max_index(char8, char8&, __vpred&);
void __max_index(char16, char16&, __vpred&);
void __max_index(char32, char32&, __vpred&);
#if __C7X_VEC_SIZE_BITS__ == 512
void __max_index(char64, char64&, __vpred&);
#endif

VMAXUPB
void __max_index(uchar, uchar&, __vpred&);
void __max_index(uchar2, uchar2&, __vpred&);
void __max_index(uchar3, uchar3&, __vpred&);
void __max_index(uchar4, uchar4&, __vpred&);
void __max_index(uchar8, uchar8&, __vpred&);
void __max_index(uchar16, uchar16&, __vpred&);
void __max_index(uchar32, uchar32&, __vpred&);
#if __C7X_VEC_SIZE_BITS__ == 512
void __max_index(uchar64, uchar64&, __vpred&);
#endif

VMAXPH
void __max_index(short, short&, __vpred&);
void __max_index(short2, short2&, __vpred&);
void __max_index(short3, short3&, __vpred&);
void __max_index(short4, short4&, __vpred&);
void __max_index(short8, short8&, __vpred&);
void __max_index(short16, short16&, __vpred&);
#if __C7X_VEC_SIZE_BITS__ == 512
void __max_index(short32, short32&, __vpred&);
#endif

VMAXUPH
void __max_index(ushort, ushort&, __vpred&);
void __max_index(ushort2, ushort2&, __vpred&);
void __max_index(ushort3, ushort3&, __vpred&);
void __max_index(ushort4, ushort4&, __vpred&);
void __max_index(ushort8, ushort8&, __vpred&);
void __max_index(ushort16, ushort16&, __vpred&);
#if __C7X_VEC_SIZE_BITS__ == 512
void __max_index(ushort32, ushort32&, __vpred&);
#endif

VMAXPW
void __max_index(int, int&, __vpred&);
void __max_index(int2, int2&, __vpred&);
void __max_index(int3, int3&, __vpred&);
void __max_index(int4, int4&, __vpred&);
void __max_index(int8, int8&, __vpred&);
#if __C7X_VEC_SIZE_BITS__ == 512
void __max_index(int16, int16&, __vpred&);
#endif

VMAXUPW
void __max_index(uint, uint&, __vpred&);
void __max_index(uint2, uint2&, __vpred&);
void __max_index(uint3, uint3&, __vpred&);
void __max_index(uint4, uint4&, __vpred&);
void __max_index(uint8, uint8&, __vpred&);
#if __C7X_VEC_SIZE_BITS__ == 512
void __max_index(uint16, uint16&, __vpred&);
#endif

VMAXPD
void __max_index(long, long&, __vpred&);
void __max_index(long2, long2&, __vpred&);
void __max_index(long3, long3&, __vpred&);
void __max_index(long4, long4&, __vpred&);
#if __C7X_VEC_SIZE_BITS__ == 512
void __max_index(long8, long8&, __vpred&);
#endif

VMAXUPD
void __max_index(ulong, ulong&, __vpred&);
void __max_index(ulong2, ulong2&, __vpred&);
void __max_index(ulong3, ulong3&, __vpred&);
void __max_index(ulong4, ulong4&, __vpred&);
#if __C7X_VEC_SIZE_BITS__ == 512
void __max_index(ulong8, ulong8&, __vpred&);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __min_index                                                            */
/*----------------------------------------------------------------------------*/
/*

VMINPB
void __min_index(signed char, signed char&, __vpred&);
void __min_index(char2, char2&, __vpred&);
void __min_index(char3, char3&, __vpred&);
void __min_index(char4, char4&, __vpred&);
void __min_index(char8, char8&, __vpred&);
void __min_index(char16, char16&, __vpred&);
void __min_index(char32, char32&, __vpred&);
#if __C7X_VEC_SIZE_BITS__ == 512
void __min_index(char64, char64&, __vpred&);
#endif

VMINUPB
void __min_index(uchar, uchar&, __vpred&);
void __min_index(uchar2, uchar2&, __vpred&);
void __min_index(uchar3, uchar3&, __vpred&);
void __min_index(uchar4, uchar4&, __vpred&);
void __min_index(uchar8, uchar8&, __vpred&);
void __min_index(uchar16, uchar16&, __vpred&);
void __min_index(uchar32, uchar32&, __vpred&);
#if __C7X_VEC_SIZE_BITS__ == 512
void __min_index(uchar64, uchar64&, __vpred&);
#endif

VMINPH
void __min_index(short, short&, __vpred&);
void __min_index(short2, short2&, __vpred&);
void __min_index(short3, short3&, __vpred&);
void __min_index(short4, short4&, __vpred&);
void __min_index(short8, short8&, __vpred&);
void __min_index(short16, short16&, __vpred&);
#if __C7X_VEC_SIZE_BITS__ == 512
void __min_index(short32, short32&, __vpred&);
#endif

VMINUPH
void __min_index(ushort, ushort&, __vpred&);
void __min_index(ushort2, ushort2&, __vpred&);
void __min_index(ushort3, ushort3&, __vpred&);
void __min_index(ushort4, ushort4&, __vpred&);
void __min_index(ushort8, ushort8&, __vpred&);
void __min_index(ushort16, ushort16&, __vpred&);
#if __C7X_VEC_SIZE_BITS__ == 512
void __min_index(ushort32, ushort32&, __vpred&);
#endif

VMINPW
void __min_index(int, int&, __vpred&);
void __min_index(int2, int2&, __vpred&);
void __min_index(int3, int3&, __vpred&);
void __min_index(int4, int4&, __vpred&);
void __min_index(int8, int8&, __vpred&);
#if __C7X_VEC_SIZE_BITS__ == 512
void __min_index(int16, int16&, __vpred&);
#endif

VMINUPW
void __min_index(uint, uint&, __vpred&);
void __min_index(uint2, uint2&, __vpred&);
void __min_index(uint3, uint3&, __vpred&);
void __min_index(uint4, uint4&, __vpred&);
void __min_index(uint8, uint8&, __vpred&);
#if __C7X_VEC_SIZE_BITS__ == 512
void __min_index(uint16, uint16&, __vpred&);
#endif

VMINPD
void __min_index(long, long&, __vpred&);
void __min_index(long2, long2&, __vpred&);
void __min_index(long3, long3&, __vpred&);
void __min_index(long4, long4&, __vpred&);
#if __C7X_VEC_SIZE_BITS__ == 512
void __min_index(long8, long8&, __vpred&);
#endif

VMINUPD
void __min_index(ulong, ulong&, __vpred&);
void __min_index(ulong2, ulong2&, __vpred&);
void __min_index(ulong3, ulong3&, __vpred&);
void __min_index(ulong4, ulong4&, __vpred&);
#if __C7X_VEC_SIZE_BITS__ == 512
void __min_index(ulong8, ulong8&, __vpred&);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __nand                                                                 */
/*----------------------------------------------------------------------------*/
/*
NAND
*/
__vpred __OVBIF __nand(__vpred, __vpred);

/*----------------------------------------------------------------------------*/
/* ID: __negate                                                               */
/*----------------------------------------------------------------------------*/
/*
NOT
*/
__vpred __OVBIF __negate(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __nor                                                                  */
/*----------------------------------------------------------------------------*/
/*
NOR
*/
__vpred __OVBIF __nor(__vpred, __vpred);

/*----------------------------------------------------------------------------*/
/* ID: __or                                                                   */
/*----------------------------------------------------------------------------*/
/*
OR
*/
__vpred __OVBIF __or(__vpred, __vpred);

/*----------------------------------------------------------------------------*/
/* ID: __orn                                                                  */
/*----------------------------------------------------------------------------*/
/*
ORN
*/
__vpred __OVBIF __orn(__vpred, __vpred);

/*----------------------------------------------------------------------------*/
/* ID: __parallel_pack_dup_16way                                              */
/*----------------------------------------------------------------------------*/
/*
VPPACKDUP16W
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __parallel_pack_dup_16way(__vpred);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __parallel_pack_dup_8way                                               */
/*----------------------------------------------------------------------------*/
/*
VPPACKDUP8W
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __parallel_pack_dup_8way(__vpred);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __popcount_char                                                        */
/*----------------------------------------------------------------------------*/
/*
PBITCNTB
*/
__uint __BIF __popcount_char(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __popcount_gather_char                                                 */
/*----------------------------------------------------------------------------*/
/*

PCNTGATHERB
void __popcount_gather_char(__vpred, uint&, __vpred&);

*/

/*----------------------------------------------------------------------------*/
/* ID: __popcount_gather_int                                                  */
/*----------------------------------------------------------------------------*/
/*

PCNTGATHERW
void __popcount_gather_int(__vpred, uint&, __vpred&);

*/

/*----------------------------------------------------------------------------*/
/* ID: __popcount_gather_long                                                 */
/*----------------------------------------------------------------------------*/
/*

PCNTGATHERD
void __popcount_gather_long(__vpred, uint&, __vpred&);

*/

/*----------------------------------------------------------------------------*/
/* ID: __popcount_gather_short                                                */
/*----------------------------------------------------------------------------*/
/*

PCNTGATHERH
void __popcount_gather_short(__vpred, uint&, __vpred&);

*/

/*----------------------------------------------------------------------------*/
/* ID: __popcount_int                                                         */
/*----------------------------------------------------------------------------*/
/*
PBITCNTW
*/
__uint __BIF __popcount_int(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __popcount_long                                                        */
/*----------------------------------------------------------------------------*/
/*
PBITCNTD
*/
__uint __BIF __popcount_long(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __popcount_short                                                       */
/*----------------------------------------------------------------------------*/
/*
PBITCNTH
*/
__uint __BIF __popcount_short(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __rightmost_bit_detect_char                                            */
/*----------------------------------------------------------------------------*/
/*
PRMBDB
*/
__uint __BIF __rightmost_bit_detect_char(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __rightmost_bit_detect_int                                             */
/*----------------------------------------------------------------------------*/
/*
PRMBDW
*/
__uint __BIF __rightmost_bit_detect_int(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __rightmost_bit_detect_long                                            */
/*----------------------------------------------------------------------------*/
/*
PRMBDD
*/
__uint __BIF __rightmost_bit_detect_long(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __rightmost_bit_detect_short                                           */
/*----------------------------------------------------------------------------*/
/*
PRMBDH
*/
__uint __BIF __rightmost_bit_detect_short(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __scatter_set_bits                                                     */
/*----------------------------------------------------------------------------*/
/*
VSCATTERB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __OVBIF __scatter_set_bits(__vpred, __char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __scatter_set_bits(__vpred, __char64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __scatter_unset_bits                                                   */
/*----------------------------------------------------------------------------*/
/*
VSCATTERNB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __OVBIF __scatter_unset_bits(__vpred, __char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __scatter_unset_bits(__vpred, __char64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __select                                                               */
/*----------------------------------------------------------------------------*/
/*
VSEL
*/
signed char __OVBIF __select(__vpred, signed char, signed char);
__char2 __OVBIF __select(__vpred, __char2, __char2);
__char3 __OVBIF __select(__vpred, __char3, __char3);
__char4 __OVBIF __select(__vpred, __char4, __char4);
__char8 __OVBIF __select(__vpred, __char8, __char8);
__char16 __OVBIF __select(__vpred, __char16, __char16);
__char32 __OVBIF __select(__vpred, __char32, __char32);
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __select(__vpred, __char64, __char64);
#endif
__uchar __OVBIF __select(__vpred, __uchar, __uchar);
__uchar2 __OVBIF __select(__vpred, __uchar2, __uchar2);
__uchar3 __OVBIF __select(__vpred, __uchar3, __uchar3);
__uchar4 __OVBIF __select(__vpred, __uchar4, __uchar4);
__uchar8 __OVBIF __select(__vpred, __uchar8, __uchar8);
__uchar16 __OVBIF __select(__vpred, __uchar16, __uchar16);
__uchar32 __OVBIF __select(__vpred, __uchar32, __uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __select(__vpred, __uchar64, __uchar64);
#endif
__cchar __OVBIF __select(__vpred, __cchar, __cchar);
__cchar2 __OVBIF __select(__vpred, __cchar2, __cchar2);
__cchar4 __OVBIF __select(__vpred, __cchar4, __cchar4);
__cchar8 __OVBIF __select(__vpred, __cchar8, __cchar8);
__cchar16 __OVBIF __select(__vpred, __cchar16, __cchar16);
#if __C7X_VEC_SIZE_BITS__ == 512
__cchar32 __OVBIF __select(__vpred, __cchar32, __cchar32);
#endif
short __OVBIF __select(__vpred, short, short);
__short2 __OVBIF __select(__vpred, __short2, __short2);
__short3 __OVBIF __select(__vpred, __short3, __short3);
__short4 __OVBIF __select(__vpred, __short4, __short4);
__short8 __OVBIF __select(__vpred, __short8, __short8);
__short16 __OVBIF __select(__vpred, __short16, __short16);
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __select(__vpred, __short32, __short32);
#endif
__ushort __OVBIF __select(__vpred, __ushort, __ushort);
__ushort2 __OVBIF __select(__vpred, __ushort2, __ushort2);
__ushort3 __OVBIF __select(__vpred, __ushort3, __ushort3);
__ushort4 __OVBIF __select(__vpred, __ushort4, __ushort4);
__ushort8 __OVBIF __select(__vpred, __ushort8, __ushort8);
__ushort16 __OVBIF __select(__vpred, __ushort16, __ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __select(__vpred, __ushort32, __ushort32);
#endif
__cshort __OVBIF __select(__vpred, __cshort, __cshort);
__cshort2 __OVBIF __select(__vpred, __cshort2, __cshort2);
__cshort4 __OVBIF __select(__vpred, __cshort4, __cshort4);
__cshort8 __OVBIF __select(__vpred, __cshort8, __cshort8);
#if __C7X_VEC_SIZE_BITS__ == 512
__cshort16 __OVBIF __select(__vpred, __cshort16, __cshort16);
#endif
int __OVBIF __select(__vpred, int, int);
/*
int __OVBIF __select(__vpred, int, int __CST(-2147483648, 2147483647));
*/
__int2 __OVBIF __select(__vpred, __int2, __int2);
/*
__int2 __OVBIF __select(__vpred, __int2, __int2 __CST(-2147483648, 2147483647));
*/
__int3 __OVBIF __select(__vpred, __int3, __int3);
/*
__int3 __OVBIF __select(__vpred, __int3, __int3 __CST(-2147483648, 2147483647));
*/
__int4 __OVBIF __select(__vpred, __int4, __int4);
/*
__int4 __OVBIF __select(__vpred, __int4, __int4 __CST(-2147483648, 2147483647));
*/
__int8 __OVBIF __select(__vpred, __int8, __int8);
/*
__int8 __OVBIF __select(__vpred, __int8, __int8 __CST(-2147483648, 2147483647));
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __select(__vpred, __int16, __int16);
/*
__int16 __OVBIF __select(__vpred, __int16, __int16 __CST(-2147483648, 2147483647));
*/
#endif
__uint __OVBIF __select(__vpred, __uint, __uint);
/*
__uint __OVBIF __select(__vpred, __uint, __uint __CST(0, 4294967295));
*/
__uint2 __OVBIF __select(__vpred, __uint2, __uint2);
/*
__uint2 __OVBIF __select(__vpred, __uint2, __uint2 __CST(0, 4294967295));
*/
__uint3 __OVBIF __select(__vpred, __uint3, __uint3);
/*
__uint3 __OVBIF __select(__vpred, __uint3, __uint3 __CST(0, 4294967295));
*/
__uint4 __OVBIF __select(__vpred, __uint4, __uint4);
/*
__uint4 __OVBIF __select(__vpred, __uint4, __uint4 __CST(0, 4294967295));
*/
__uint8 __OVBIF __select(__vpred, __uint8, __uint8);
/*
__uint8 __OVBIF __select(__vpred, __uint8, __uint8 __CST(0, 4294967295));
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __select(__vpred, __uint16, __uint16);
/*
__uint16 __OVBIF __select(__vpred, __uint16, __uint16 __CST(0, 4294967295));
*/
#endif
float __OVBIF __select(__vpred, float, float);
/*
float __OVBIF __select(__vpred, float, float k);
*/
__float2 __OVBIF __select(__vpred, __float2, __float2);
/*
__float2 __OVBIF __select(__vpred, __float2, __float2 k);
*/
__float3 __OVBIF __select(__vpred, __float3, __float3);
/*
__float3 __OVBIF __select(__vpred, __float3, __float3 k);
*/
__float4 __OVBIF __select(__vpred, __float4, __float4);
/*
__float4 __OVBIF __select(__vpred, __float4, __float4 k);
*/
__float8 __OVBIF __select(__vpred, __float8, __float8);
/*
__float8 __OVBIF __select(__vpred, __float8, __float8 k);
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__float16 __OVBIF __select(__vpred, __float16, __float16);
/*
__float16 __OVBIF __select(__vpred, __float16, __float16 k);
*/
#endif
__cint __OVBIF __select(__vpred, __cint, __cint);
__cint2 __OVBIF __select(__vpred, __cint2, __cint2);
__cint4 __OVBIF __select(__vpred, __cint4, __cint4);
#if __C7X_VEC_SIZE_BITS__ == 512
__cint8 __OVBIF __select(__vpred, __cint8, __cint8);
#endif
__cfloat __OVBIF __select(__vpred, __cfloat, __cfloat);
__cfloat2 __OVBIF __select(__vpred, __cfloat2, __cfloat2);
__cfloat4 __OVBIF __select(__vpred, __cfloat4, __cfloat4);
#if __C7X_VEC_SIZE_BITS__ == 512
__cfloat8 __OVBIF __select(__vpred, __cfloat8, __cfloat8);
#endif
long __OVBIF __select(__vpred, long, long);
__long2 __OVBIF __select(__vpred, __long2, __long2);
__long3 __OVBIF __select(__vpred, __long3, __long3);
__long4 __OVBIF __select(__vpred, __long4, __long4);
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __select(__vpred, __long8, __long8);
#endif
__ulong __OVBIF __select(__vpred, __ulong, __ulong);
__ulong2 __OVBIF __select(__vpred, __ulong2, __ulong2);
__ulong3 __OVBIF __select(__vpred, __ulong3, __ulong3);
__ulong4 __OVBIF __select(__vpred, __ulong4, __ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __select(__vpred, __ulong8, __ulong8);
#endif
double __OVBIF __select(__vpred, double, double);
__double2 __OVBIF __select(__vpred, __double2, __double2);
__double3 __OVBIF __select(__vpred, __double3, __double3);
__double4 __OVBIF __select(__vpred, __double4, __double4);
#if __C7X_VEC_SIZE_BITS__ == 512
__double8 __OVBIF __select(__vpred, __double8, __double8);
#endif
__clong __OVBIF __select(__vpred, __clong, __clong);
__clong2 __OVBIF __select(__vpred, __clong2, __clong2);
#if __C7X_VEC_SIZE_BITS__ == 512
__clong4 __OVBIF __select(__vpred, __clong4, __clong4);
#endif
__cdouble __OVBIF __select(__vpred, __cdouble, __cdouble);
__cdouble2 __OVBIF __select(__vpred, __cdouble2, __cdouble2);
#if __C7X_VEC_SIZE_BITS__ == 512
__cdouble4 __OVBIF __select(__vpred, __cdouble4, __cdouble4);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __shift_left_conditional                                               */
/*----------------------------------------------------------------------------*/
/*
VSHLCB
*/
signed char __OVBIF __shift_left_conditional(__vpred, signed char, signed char);
__char2 __OVBIF __shift_left_conditional(__vpred, __char2, __char2);
__char3 __OVBIF __shift_left_conditional(__vpred, __char3, __char3);
__char4 __OVBIF __shift_left_conditional(__vpred, __char4, __char4);
__char8 __OVBIF __shift_left_conditional(__vpred, __char8, __char8);
__char16 __OVBIF __shift_left_conditional(__vpred, __char16, __char16);
__char32 __OVBIF __shift_left_conditional(__vpred, __char32, __char32);
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __shift_left_conditional(__vpred, __char64, __char64);
#endif
__uchar __OVBIF __shift_left_conditional(__vpred, __uchar, __uchar);
__uchar2 __OVBIF __shift_left_conditional(__vpred, __uchar2, __uchar2);
__uchar3 __OVBIF __shift_left_conditional(__vpred, __uchar3, __uchar3);
__uchar4 __OVBIF __shift_left_conditional(__vpred, __uchar4, __uchar4);
__uchar8 __OVBIF __shift_left_conditional(__vpred, __uchar8, __uchar8);
__uchar16 __OVBIF __shift_left_conditional(__vpred, __uchar16, __uchar16);
__uchar32 __OVBIF __shift_left_conditional(__vpred, __uchar32, __uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __shift_left_conditional(__vpred, __uchar64, __uchar64);
#endif
/*
VSHLCH
*/
short __OVBIF __shift_left_conditional(__vpred, short, short);
__short2 __OVBIF __shift_left_conditional(__vpred, __short2, __short2);
__short3 __OVBIF __shift_left_conditional(__vpred, __short3, __short3);
__short4 __OVBIF __shift_left_conditional(__vpred, __short4, __short4);
__short8 __OVBIF __shift_left_conditional(__vpred, __short8, __short8);
__short16 __OVBIF __shift_left_conditional(__vpred, __short16, __short16);
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __shift_left_conditional(__vpred, __short32, __short32);
#endif
__ushort __OVBIF __shift_left_conditional(__vpred, __ushort, __ushort);
__ushort2 __OVBIF __shift_left_conditional(__vpred, __ushort2, __ushort2);
__ushort3 __OVBIF __shift_left_conditional(__vpred, __ushort3, __ushort3);
__ushort4 __OVBIF __shift_left_conditional(__vpred, __ushort4, __ushort4);
__ushort8 __OVBIF __shift_left_conditional(__vpred, __ushort8, __ushort8);
__ushort16 __OVBIF __shift_left_conditional(__vpred, __ushort16, __ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __shift_left_conditional(__vpred, __ushort32, __ushort32);
#endif
/*
VSHLCW
*/
int __OVBIF __shift_left_conditional(__vpred, int, int);
__int2 __OVBIF __shift_left_conditional(__vpred, __int2, __int2);
__int3 __OVBIF __shift_left_conditional(__vpred, __int3, __int3);
__int4 __OVBIF __shift_left_conditional(__vpred, __int4, __int4);
__int8 __OVBIF __shift_left_conditional(__vpred, __int8, __int8);
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __shift_left_conditional(__vpred, __int16, __int16);
#endif
__uint __OVBIF __shift_left_conditional(__vpred, __uint, __uint);
__uint2 __OVBIF __shift_left_conditional(__vpred, __uint2, __uint2);
__uint3 __OVBIF __shift_left_conditional(__vpred, __uint3, __uint3);
__uint4 __OVBIF __shift_left_conditional(__vpred, __uint4, __uint4);
__uint8 __OVBIF __shift_left_conditional(__vpred, __uint8, __uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __shift_left_conditional(__vpred, __uint16, __uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __xnor                                                                 */
/*----------------------------------------------------------------------------*/
/*
XNOR
*/
__vpred __OVBIF __xnor(__vpred, __vpred);

/*----------------------------------------------------------------------------*/
/* ID: __xor                                                                  */
/*----------------------------------------------------------------------------*/
/*
XOR
*/
__vpred __OVBIF __xor(__vpred, __vpred);

/* AUTOGEN MARKER */

#endif /* __C7X_VPRED_H */
