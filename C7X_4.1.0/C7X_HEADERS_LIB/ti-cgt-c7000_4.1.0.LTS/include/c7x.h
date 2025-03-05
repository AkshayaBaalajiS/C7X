/*****************************************************************************/
/*  C7X.H                                                                    */
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
#ifndef __C7X_H
#define __C7X_H
#define __C7X_H_INCLUDE__

#include <stdbool.h>

#define __RD           __attribute__((memread))
#define __WR           __attribute__((memwrite))
#define __IMPURE       __attribute__((impure))
#define __OVERLOADABLE __attribute__((overloadable))
#define __BIF    __attribute__((builtin))
#define __BIFM   __BIF __IMPURE
#define __OVBIF  __BIF __OVERLOADABLE
#define __OVBIFM __BIFM __OVERLOADABLE

#define __CST(lb, ub) __attribute__((constrange((lb), (ub))))
#define __CST_RANGE __CST(0, 0x7ffffff)

/*****************************************************************************/
/* VECTOR POINTER CONVERSION INTRINSICS                                      */
/* (Deprecated in favor of C-style casts)                                    */
/*                                                                           */
/* These intrinsics are used to convert between vector type pointers and     */
/* component element type pointers. Use of these intrinsics is required when */
/* using the host emulation package and are defined here for compatiblity    */
/* when porting programs to the C7000 compiler.                              */
/*****************************************************************************/
/* C-style cast: uchar64* p = (uchar64*)(pointer);                           */
#define stov_ptr(type, addr) (type*)(addr)
/* C-style cast: uint8_t *p = (uint8_t*)(pointer);                           */
#define vtos_ptr(type, addr) (type*)(addr)
/* C-style cast: cint* p = (cint*)(pointer);                                 */
#define stoc_ptr(type, addr) (type*)(addr)
/* C-style cast: int32_t* p = (int32_t*)(pointer);                           */
#define ctos_ptr(type, addr) (type*)(addr)


/*****************************************************************************/
/* Include the CR (Control Register) set.                                    */
/*****************************************************************************/
#include <c7x_cr.h>

/*****************************************************************************/
/* Include the ECR (Extended Control Register) set.                          */
/*****************************************************************************/
#include <c7x_ecr.h>

/*****************************************************************************/
/* Include low-level "vpred" operations, some of which are overloaded below. */
/*****************************************************************************/
#include <c7x_vpred.h>

/*****************************************************************************/
/* FLAG STATUS REGISTER (FSR) CONTROL REGISTER ACCESS                        */
/*                                                                           */
/* This API is provided to assist the user in extracting pertinent floating  */
/* point status bit information for floating point instructions.  The result */
/* is an 8bit value containing the following fields:                         */
/*                                                                           */
/* Bit 7: SAT   - NOT SUPPORTED FOR C7000 OPERATIONS                         */
/* Bit 6: UNORD - Compare result is unordered Floating Point Flag            */
/* Bit 5: DEN   - Source is a Denorm Floating Point Flag                     */
/* Bit 4: INEX  - Result is inexact Floating Point Flag                      */
/* Bit 3: UNDER - Result is underflow Floating Point Flag                    */
/* Bit 2: OVER  - Result is overflow Floating Point Flag                     */
/* Bit 1: DIV0  - Divide by zero Floating Point Flag                         */
/* Bit 0: INVAL - Invalid Operations Floating Point Flag                     */
/*                                                                           */
/* Please specify the scalar or vector floating point type as an argument    */
/* corresponding to the size of the pertinent floating point data, and the   */
/* API will return an "OR" of the data bits for all pertinent vector lanes   */
/* in a single, 8bit chunk of data.                                          */
/*                                                                           */
/*        e.g.:                                                              */
/*              float4 a = ... ;                                             */
/*              float4 b = ... ;                                             */
/*              float4 c = a * b;                                            */
/*              uint8_t fsr_val = __get_FSR(float4);                         */
/*                                                                           */
/* NOTE: Accessing the SAT-bit is NOT SUPPORTED for C7000 operations.  It is */
/* only supported for C6000 legacy operations to facilitate compatibility on */
/* legacy C6000 source code (see c6x_migration.h).                           */
/*****************************************************************************/
#define __get_FSR(type) __get_fsr_##type(sizeof(type))

/*****************************************************************************/
/* GTSC CONTROL REGISTER ACCESS                                              */
/*****************************************************************************/
#define __get_GTSC(opt) __get_indexed(__GTSC, opt)

/*****************************************************************************/
/* INSTRUCTION CACHE FLUSH AND REFRESH                                       */
/*****************************************************************************/
typedef enum __attribute__((__packed__))
{
    __IINVAL_MMUNONE = 0,
    __IINVAL_MMU0    = 1,
    __IINVAL_MMU1    = 2,
    __IINVAL_MMUALL  = 3
} __IINVAL_TYPE;
void __BIFM __instr_cache_invalidate(__CST(0,3) __IINVAL_TYPE);

/*****************************************************************************/
/* BOOLEAN VECTOR CREATION                                                   */
/*                                                                           */
/* Create a boolean vector as a mask of 'k' consecutive booleans set to true */
/*****************************************************************************/
__bool2 __OVBIF __mask_bool2(__uint);
__bool2 __OVBIF __mask_bool2(__CST(0, 2) __uchar);

__bool3 __OVBIF __mask_bool3(__uint);
__bool3 __OVBIF __mask_bool3(__CST(0, 3) __uchar);

__bool4 __OVBIF __mask_bool4(__uint);
__bool4 __OVBIF __mask_bool4(__CST(0, 4) __uchar);

__bool8 __OVBIF __mask_bool8(__uint);
__bool8 __OVBIF __mask_bool8(__CST(0, 8) __uchar);

__bool16 __OVBIF __mask_bool16(__uint);
__bool16 __OVBIF __mask_bool16(__CST(0, 16) __uchar);

__bool32 __OVBIF __mask_bool32(__uint);
__bool32 __OVBIF __mask_bool32(__CST(0, 32) __uchar);

#if __C7X_VEC_SIZE_BITS__ >= 512
__bool64 __OVBIF __mask_bool64(__uint);
__bool64 __OVBIF __mask_bool64(__CST(0, 64) __uchar);
#endif


/*****************************************************************************/
/* BOOLEAN VECTOR CONVERSION                                                 */
/*****************************************************************************/
__bool2  __OVBIF __reduce_bool2(__bool3);
__bool2  __OVBIF __reduce_bool2(__bool4);
__bool2  __OVBIF __reduce_bool2(__bool8);
__bool2  __OVBIF __reduce_bool2(__bool16);
__bool2  __OVBIF __reduce_bool2(__bool32);
#if __C7X_VEC_SIZE_BITS__ >= 512
__bool2  __OVBIF __reduce_bool2(__bool64);
#endif

__bool3  __OVBIF __extend_bool3(__bool2);
__bool3  __OVBIF __reduce_bool3(__bool4);
__bool3  __OVBIF __reduce_bool3(__bool8);
__bool3  __OVBIF __reduce_bool3(__bool16);
__bool3  __OVBIF __reduce_bool3(__bool32);
#if __C7X_VEC_SIZE_BITS__ >= 512
__bool3  __OVBIF __reduce_bool3(__bool64);
#endif

__bool4  __OVBIF __extend_bool4(__bool2);
__bool4  __OVBIF __extend_bool4(__bool3);
__bool4  __OVBIF __reduce_bool4(__bool8);
__bool4  __OVBIF __reduce_bool4(__bool16);
__bool4  __OVBIF __reduce_bool4(__bool32);
#if __C7X_VEC_SIZE_BITS__ >= 512
__bool4  __OVBIF __reduce_bool4(__bool64);
#endif

__bool8  __OVBIF __extend_bool8(__bool2);
__bool8  __OVBIF __extend_bool8(__bool3);
__bool8  __OVBIF __extend_bool8(__bool4);
__bool8  __OVBIF __reduce_bool8(__bool16);
__bool8  __OVBIF __reduce_bool8(__bool32);
#if __C7X_VEC_SIZE_BITS__ >= 512
__bool8  __OVBIF __reduce_bool8(__bool64);
#endif

__bool16  __OVBIF __extend_bool16(__bool2);
__bool16  __OVBIF __extend_bool16(__bool3);
__bool16  __OVBIF __extend_bool16(__bool4);
__bool16  __OVBIF __extend_bool16(__bool8);
__bool16  __OVBIF __reduce_bool16(__bool32);
#if __C7X_VEC_SIZE_BITS__ >= 512
__bool16  __OVBIF __reduce_bool16(__bool64);
#endif

__bool32  __OVBIF __extend_bool32(__bool2);
__bool32  __OVBIF __extend_bool32(__bool3);
__bool32  __OVBIF __extend_bool32(__bool4);
__bool32  __OVBIF __extend_bool32(__bool8);
__bool32  __OVBIF __extend_bool32(__bool16);
#if __C7X_VEC_SIZE_BITS__ >= 512
__bool32  __OVBIF __reduce_bool32(__bool64);
#endif

#if __C7X_VEC_SIZE_BITS__ >= 512
__bool64  __OVBIF __extend_bool64(__bool2);
__bool64  __OVBIF __extend_bool64(__bool3);
__bool64  __OVBIF __extend_bool64(__bool4);
__bool64  __OVBIF __extend_bool64(__bool8);
__bool64  __OVBIF __extend_bool64(__bool16);
__bool64  __OVBIF __extend_bool64(__bool32);
#endif

__bool2  __OVBIF __create_bool2(__ulong);
__bool3  __OVBIF __create_bool3(__ulong);
__bool4  __OVBIF __create_bool4(__ulong);
__bool8  __OVBIF __create_bool8(__ulong);
__bool16  __OVBIF __create_bool16(__ulong);
__bool32  __OVBIF __create_bool32(__ulong);
#if __C7X_VEC_SIZE_BITS__ >= 512
__bool64  __OVBIF __create_bool64(__ulong);
#endif

__ulong __OVBIF __create_scalar(__bool2);
__ulong __OVBIF __create_scalar(__bool3);
__ulong __OVBIF __create_scalar(__bool4);
__ulong __OVBIF __create_scalar(__bool8);
__ulong __OVBIF __create_scalar(__bool16);
__ulong __OVBIF __create_scalar(__bool32);
#if __C7X_VEC_SIZE_BITS__ >= 512
__ulong __OVBIF __create_scalar(__bool64);
#endif

/*****************************************************************************/
/* STREAMING ENGINE / ADDRESS GENERATOR COMMON CONTROLS                      */
/*                                                                           */
/* PLEASE REFER TO c7x_strm.h (INCLUDED BELOW) FOR MORE INFORMATION ON SETUP */
/* AND USE                                                                   */
/*****************************************************************************/
/* LOOKUP TABLE / HISTOGRAM COMMON CONTROLS                                  */
/*                                                                           */
/* PLEASE REFER TO c7x_luthist.h (INCLUDED BELOW) FOR MORE INFORMATION ON    */
/* SETUP AND USE                                                             */
/*****************************************************************************/

/*****************************************************************************/
/*                                                                           */
/* Vector Data Types in TI Compiler                                          */
/*                                                                           */
/* A vector data type name consists of the following:                        */
/* - main part: char, short, int, long, float, double                        */
/* - prefix: 'c' for complex (TI extension!!)                                */
/* - prefix: 'u' for unsigned, can not be specified for complex vectors      */
/* - suffix: digits for number of elements in the vector                     */
/*           (valid values: 2,3,4,8,16,32,64)                                */
/*                                                                           */
/*                                                                           */
/* e.g. uint2: a 64-bit vector consisting of 2 unsigned int elements         */
/* e.g. char4: a 32-bit vector consisting of 4 signed chars                  */
/* e.g. cfloat: a 64-bit complex float consisting of a float real (R) and    */
/*              a float imaginary (I)                                        */
/* e.g. cshort4: a 128-bit vector consisting of 4 complex signed shorts      */
/*                                                                           */
/* - The TI compiler defines extended width vectors up to and including      */
/*   512-bits, in addition to vectors with up to 16 elements.                */
/*                                                                           */
/* Note on complex:                                                          */
/*   Complex values on C7000 follow C99 Standard rules in memory, with the   */
/*   real part in mem[0] and imaginary part in mem[1].                       */
/*                                                                           */
/*   Two accessors are available.                                            */
/*    - .r() returns the real parts of each complex in a vector              */
/*    - .i() returns the imaginary parts of each complex in a vector         */
/*                                                                           */
/*****************************************************************************/
/*****************************************************************************/
/* The following native vector types are defined by the compiler as of v1.0  */
/* of the C7000 compiler.                                                    */
/* In strict mode, only vector types beginning with double underscores are   */
/* defined, otherwise equivalents with no underscores may be used.           */
/*****************************************************************************/
/*****************************************************************************/
/* Built-in base types                                                       */
/* NOTE: When using host emulation, a host emulation compatible type must    */
/*       also be used.                                                       */
/*****************************************************************************/
/* Native cl7x type:            Host emulation compatible type:              */
/* signed char                  int8_t                                       */
/* unsigned char                uint8_t                                      */
/* short                        int16_t                                      */
/* unsigned short               uint16_t                                     */
/* int                          int32_t                                      */
/* unsigned int                 uint32_t                                     */
/* long                         int64_t                                      */
/* unsigned long                uint64_t                                     */
/* float                        float                                        */
/* double                       double                                       */
/*****************************************************************************/
/* Non-complex vector data types                                             */
/*****************************************************************************/
/* __uchar  is equivalent to unsigned char                                   */
/* __ushort is equivalent to unsigned short                                  */
/* __uint   is equivalent to unsigned int                                    */
/* __ulong  is equivalent to unsigned long                                   */
/*                                                                           */
/* __char2  is equivalent to a vector of 2  signed char                      */
/* __char3  is equivalent to a vector of 3  signed char                      */
/* __char4  is equivalent to a vector of 4  signed char                      */
/* __char8  is equivalent to a vector of 8  signed char                      */
/* __char16 is equivalent to a vector of 16 signed char                      */
/* __char32 is equivalent to a vector of 32 signed char                      */
/* __char64 is equivalent to a vector of 64 signed char                      */
/*                                                                           */
/* __uchar2  is equivalent to a vector of 2  __uchar                         */
/* __uchar3  is equivalent to a vector of 3  __uchar                         */
/* __uchar4  is equivalent to a vector of 4  __uchar                         */
/* __uchar8  is equivalent to a vector of 8  __uchar                         */
/* __uchar16 is equivalent to a vector of 16 __uchar                         */
/* __uchar32 is equivalent to a vector of 32 __uchar                         */
/* __uchar64 is equivalent to a vector of 64 __uchar                         */
/*                                                                           */
/* __short2  is equivalent to a vector of 2  short                           */
/* __short3  is equivalent to a vector of 3  short                           */
/* __short4  is equivalent to a vector of 4  short                           */
/* __short8  is equivalent to a vector of 8  short                           */
/* __short16 is equivalent to a vector of 16 short                           */
/* __short32 is equivalent to a vector of 32 short                           */
/*                                                                           */
/* __ushort2  is equivalent to a vector of 2  __ushort                       */
/* __ushort3  is equivalent to a vector of 3  __ushort                       */
/* __ushort4  is equivalent to a vector of 4  __ushort                       */
/* __ushort8  is equivalent to a vector of 8  __ushort                       */
/* __ushort16 is equivalent to a vector of 16 __ushort                       */
/* __ushort32 is equivalent to a vector of 32 __ushort                       */
/*                                                                           */
/* __int2  is equivalent to a vector of 2  int                               */
/* __int3  is equivalent to a vector of 3  int                               */
/* __int4  is equivalent to a vector of 4  int                               */
/* __int8  is equivalent to a vector of 8  int                               */
/* __int16 is equivalent to a vector of 16 int                               */
/*                                                                           */
/* __uint2  is equivalent to a vector of 2  __uint                           */
/* __uint3  is equivalent to a vector of 3  __uint                           */
/* __uint4  is equivalent to a vector of 4  __uint                           */
/* __uint8  is equivalent to a vector of 8  __uint                           */
/* __uint16 is equivalent to a vector of 16 __uint                           */
/*                                                                           */
/* __long2  is equivalent to a vector of 2  long                             */
/* __long3  is equivalent to a vector of 3  long                             */
/* __long4  is equivalent to a vector of 4  long                             */
/* __long8  is equivalent to a vector of 8  long                             */
/*                                                                           */
/* __ulong2  is equivalent to a vector of 2  __ulong                         */
/* __ulong3  is equivalent to a vector of 3  __ulong                         */
/* __ulong4  is equivalent to a vector of 4  __ulong                         */
/* __ulong8  is equivalent to a vector of 8  __ulong                         */
/*                                                                           */
/* __float2  is equivalent to a vector of 2  float                           */
/* __float3  is equivalent to a vector of 3  float                           */
/* __float4  is equivalent to a vector of 4  float                           */
/* __float8  is equivalent to a vector of 8  float                           */
/* __float16 is equivalent to a vector of 16 float                           */
/*                                                                           */
/* __double2  is equivalent to a vector of 2  double                         */
/* __double3  is equivalent to a vector of 3  double                         */
/* __double4  is equivalent to a vector of 4  double                         */
/* __double8  is equivalent to a vector of 8  double                         */
/*****************************************************************************/
/* Complex data type and complex vector data types                           */
/*****************************************************************************/
/* __cchar      is equivalent to a complex signed char                       */
/* __cchar2     is equivalent to a vector of 2  complex signed char          */
/* __cchar4     is equivalent to a vector of 4  complex signed char          */
/* __cchar8     is equivalent to a vector of 8  complex signed char          */
/* __cchar16    is equivalent to a vector of 16 complex signed char          */
/* __cchar32    is equivalent to a vector of 32 complex signed char          */
/*                                                                           */
/* __cshort     is equivalent to a complex short                             */
/* __cshort2    is equivalent to a vector of 2  complex short                */
/* __cshort4    is equivalent to a vector of 4  complex short                */
/* __cshort8    is equivalent to a vector of 8  complex short                */
/* __cshort16   is equivalent to a vector of 16 complex short                */
/*                                                                           */
/* __cint       is equivalent to a complex int                               */
/* __cint2      is equivalent to a vector of 2 complex int                   */
/* __cint4      is equivalent to a vector of 4 complex int                   */
/* __cint8      is equivalent to a vector of 8 complex int                   */
/*                                                                           */
/* __clong      is equivalent to a complex long                              */
/* __clong2     is equivalent to a vector of 2 complex long                  */
/* __clong4     is equivalent to a vector of 4 complex long                  */
/*                                                                           */
/* __cfloat     is equivalent to a complex float                             */
/* __cfloat2    is equivalent to a vector of 2 complex float                 */
/* __cfloat4    is equivalent to a vector of 4 complex float                 */
/* __cfloat8    is equivalent to a vector of 8 complex float                 */
/*                                                                           */
/* __cdouble    is equivalent to a complex double                            */
/* __cdouble2   is equivalent to a vector of 2 complex double                */
/* __cdouble4   is equivalent to a vector of 4 complex double                */
/*****************************************************************************/

/* Complex multiply pseudo-instruction: VCMPYSP + VADDSP */
__cfloat  __OVBIF __complex_multiply          (__cfloat,  __cfloat);
__cfloat2 __OVBIF __complex_multiply          (__cfloat2, __cfloat2);
__cfloat4 __OVBIF __complex_multiply          (__cfloat4, __cfloat4);
#if __C7X_VEC_SIZE_BITS__ >= 512
__cfloat8 __OVBIF __complex_multiply          (__cfloat8, __cfloat8);
#endif

/* Complex Conjugate multiply pseudo-instruction: VCMPYSP + VSUBSP */
__cfloat  __OVBIF __complex_conjugate_multiply(__cfloat,  __cfloat);
__cfloat2 __OVBIF __complex_conjugate_multiply(__cfloat2, __cfloat2);
__cfloat4 __OVBIF __complex_conjugate_multiply(__cfloat4, __cfloat4);
#if __C7X_VEC_SIZE_BITS__ >= 512
__cfloat8 __OVBIF __complex_conjugate_multiply(__cfloat8, __cfloat8);
#endif

/*
cfloat  __OVBIF __conj_cmpy(__cfloat,  __cfloat);
cfloat2 __OVBIF __conj_cmpy(__cfloat2, __cfloat2);
cfloat4 __OVBIF __conj_cmpy(__cfloat4, __cfloat4);
#if __C7X_VEC_SIZE_BITS__ >= 512
cfloat8 __OVBIF __conj_cmpy(__cfloat8, __cfloat8);
#endif
*/

/* Use __complex_conjugate_multiply() instead of __conj_cmpy(). CODEGEN-9989. */
#define __conj_cmpy(a,b) __complex_conjugate_multiply((a),(b))

/* Floating point VMATMPY pseudo-instruction: VMATMPYSP + VADDSP */
/* The VMATMPYSP instruction does not exist on the 750[2|4] architectures */
#if __C7X_VEC_SIZE_BITS__ == 512
/* Floating point VMATMPY pseudo-instruction: VMATMPYSP + VADDSP */
__float2 __OVBIF __float_matmpy(__float2, __float4);
__float4 __OVBIF __float_matmpy(__float4, __float8);
__float8 __OVBIF __float_matmpy(__float8, __float16);
#endif

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
/* bool2 pred = __SA0_BOOL(char2);                                           */
/* char2* ptr = __SA0ADV(char2, base_ptr);                                   */
/* char2 data = __vload_pred(pred, ptr);                                     */
/*                                                                           */
/* If implicit predication is not available (C7100), the idiom is malformed, */
/* or the compiler fails to optimize the idiom, an equivalent series of      */
/* instructions will instead be generated to load and then predicate.        */
/*****************************************************************************/
/* VLD8B, VLD16B, VLD32B, VLD64B */
__char2   __OVBIF __vload_pred(__bool2, __RD const __char2*);
__char4   __OVBIF __vload_pred(__bool4, __RD const __char4*);
__char8   __OVBIF __vload_pred(__bool8, __RD const __char8*);
__char16  __OVBIF __vload_pred(__bool16, __RD const __char16*);
__char32  __OVBIF __vload_pred(__bool32, __RD const __char32*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__char64  __OVBIF __vload_pred(__bool64, __RD const __char64*);
#endif

__uchar2  __OVBIF __vload_pred(__bool2, __RD const __uchar2*);
__uchar4  __OVBIF __vload_pred(__bool4, __RD const __uchar4*);
__uchar8  __OVBIF __vload_pred(__bool8, __RD const __uchar8*);
__uchar16 __OVBIF __vload_pred(__bool16, __RD const __uchar16*);
__uchar32 __OVBIF __vload_pred(__bool32, __RD const __uchar32*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__uchar64 __OVBIF __vload_pred(__bool64, __RD const __uchar64*);
#endif

/* VLD4H, VLD8H, VLD16H, VLD32H */
__short2   __OVBIF __vload_pred(__bool2, __RD const __short2*);
__short4   __OVBIF __vload_pred(__bool4, __RD const __short4*);
__short8   __OVBIF __vload_pred(__bool8, __RD const __short8*);
__short16  __OVBIF __vload_pred(__bool16, __RD const __short16*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__short32  __OVBIF __vload_pred(__bool32, __RD const __short32*);
#endif

__ushort2  __OVBIF __vload_pred(__bool2, __RD const __ushort2*);
__ushort4  __OVBIF __vload_pred(__bool4, __RD const __ushort4*);
__ushort8  __OVBIF __vload_pred(__bool8, __RD const __ushort8*);
__ushort16 __OVBIF __vload_pred(__bool16, __RD const __ushort16*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__ushort32 __OVBIF __vload_pred(__bool32, __RD const __ushort32*);
#endif

/* VLDHSWAPB */
__cchar2   __OVBIF __vload_pred(__bool2, __RD const __cchar2*);
__cchar4   __OVBIF __vload_pred(__bool4, __RD const __cchar4*);
__cchar8   __OVBIF __vload_pred(__bool8, __RD const __cchar8*);
__cchar16  __OVBIF __vload_pred(__bool16, __RD const __cchar16*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__cchar32  __OVBIF __vload_pred(__bool32, __RD const __cchar32*);
#endif

/* VLD2W, VLD4W, VLD8W, VLD16W */
__int2   __OVBIF __vload_pred(__bool2, __RD const __int2*);
__int4   __OVBIF __vload_pred(__bool4, __RD const __int4*);
__int8   __OVBIF __vload_pred(__bool8, __RD const __int8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__int16  __OVBIF __vload_pred(__bool16, __RD const __int16*);
#endif

__uint2  __OVBIF __vload_pred(__bool2, __RD const __uint2*);
__uint4  __OVBIF __vload_pred(__bool4, __RD const __uint4*);
__uint8  __OVBIF __vload_pred(__bool8, __RD const __uint8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__uint16 __OVBIF __vload_pred(__bool16, __RD const __uint16*);
#endif

__float2   __OVBIF __vload_pred(__bool2, __RD const __float2*);
__float4   __OVBIF __vload_pred(__bool4, __RD const __float4*);
__float8   __OVBIF __vload_pred(__bool8, __RD const __float8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__float16  __OVBIF __vload_pred(__bool16, __RD const __float16*);
#endif

/* VLDWSWAPH */
__cshort2   __OVBIF __vload_pred(__bool2, __RD const __cshort2*);
__cshort4   __OVBIF __vload_pred(__bool4, __RD const __cshort4*);
__cshort8   __OVBIF __vload_pred(__bool8, __RD const __cshort8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__cshort16  __OVBIF __vload_pred(__bool16, __RD const __cshort16*);
#endif

/* VLD2D, VLD4D, VLD8D */
__long2     __OVBIF __vload_pred(__bool2, __RD const __long2*);
__long4     __OVBIF __vload_pred(__bool4, __RD const __long4*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__long8     __OVBIF __vload_pred(__bool8, __RD const __long8*);
#endif

__ulong2    __OVBIF __vload_pred(__bool2, __RD const __ulong2*);
__ulong4    __OVBIF __vload_pred(__bool4, __RD const __ulong4*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__ulong8    __OVBIF __vload_pred(__bool8, __RD const __ulong8*);
#endif

__double2   __OVBIF __vload_pred(__bool2, __RD const __double2*);
__double4   __OVBIF __vload_pred(__bool4, __RD const __double4*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__double8   __OVBIF __vload_pred(__bool8, __RD const __double8*);
#endif

/* VLDDSWAPW */
__cint2   __OVBIF __vload_pred(__bool2, __RD const __cint2*);
__cint4   __OVBIF __vload_pred(__bool4, __RD const __cint4*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__cint8   __OVBIF __vload_pred(__bool8, __RD const __cint8*);
#endif
__cfloat2   __OVBIF __vload_pred(__bool2, __RD const __cfloat2*);
__cfloat4   __OVBIF __vload_pred(__bool4, __RD const __cfloat4*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__cfloat8   __OVBIF __vload_pred(__bool8, __RD const __cfloat8*);
#endif

/* VLDDUP2B, VLDDUP4B, VLDDUP8B, VLDDUP16B, VLDDUP32B, VLDDUP64B */
#if __C7X_VEC_SIZE_BITS__ == 512
__char64      __OVBIF __vload_dup(__RD const __char32*);
__char64      __OVBIF __vload_dup(__RD const __char16*);
__char64      __OVBIF __vload_dup(__RD const __char8*);
__char64      __OVBIF __vload_dup(__RD const __char4*);
__char64      __OVBIF __vload_dup(__RD const __char2*);
__char64      __OVBIF __vload_dup(__RD const signed char*);
__uchar64     __OVBIF __vload_dup(__RD const __uchar32*);
__uchar64     __OVBIF __vload_dup(__RD const __uchar16*);
__uchar64     __OVBIF __vload_dup(__RD const __uchar8*);
__uchar64     __OVBIF __vload_dup(__RD const __uchar4*);
__uchar64     __OVBIF __vload_dup(__RD const __uchar2*);
__uchar64     __OVBIF __vload_dup(__RD const __uchar*);

__char64      __OVBIF __vload_pred_dup(__bool32, __RD const __char32*);
__char64      __OVBIF __vload_pred_dup(__bool16, __RD const __char16*);
__char64      __OVBIF __vload_pred_dup(__bool8, __RD const __char8*);
__char64      __OVBIF __vload_pred_dup(__bool4, __RD const __char4*);
__char64      __OVBIF __vload_pred_dup(__bool2, __RD const __char2*);
__uchar64     __OVBIF __vload_pred_dup(__bool32, __RD const __uchar32*);
__uchar64     __OVBIF __vload_pred_dup(__bool16, __RD const __uchar16*);
__uchar64     __OVBIF __vload_pred_dup(__bool8, __RD const __uchar8*);
__uchar64     __OVBIF __vload_pred_dup(__bool4, __RD const __uchar4*);
__uchar64     __OVBIF __vload_pred_dup(__bool2, __RD const __uchar2*);
#elif __C7X_VEC_SIZE_BITS__ == 256
__char32      __OVBIF __vload_dup(__RD const __char16*);
__char32      __OVBIF __vload_dup(__RD const __char8*);
__char32      __OVBIF __vload_dup(__RD const __char4*);
__char32      __OVBIF __vload_dup(__RD const __char2*);
__char32      __OVBIF __vload_dup(__RD const signed char*);
__uchar32     __OVBIF __vload_dup(__RD const __uchar16*);
__uchar32     __OVBIF __vload_dup(__RD const __uchar8*);
__uchar32     __OVBIF __vload_dup(__RD const __uchar4*);
__uchar32     __OVBIF __vload_dup(__RD const __uchar2*);
__uchar32     __OVBIF __vload_dup(__RD const __uchar*);

__char32      __OVBIF __vload_pred_dup(__bool16, __RD const __char16*);
__char32      __OVBIF __vload_pred_dup(__bool8, __RD const __char8*);
__char32      __OVBIF __vload_pred_dup(__bool4, __RD const __char4*);
__char32      __OVBIF __vload_pred_dup(__bool2, __RD const __char2*);
__uchar32     __OVBIF __vload_pred_dup(__bool16, __RD const __uchar16*);
__uchar32     __OVBIF __vload_pred_dup(__bool8, __RD const __uchar8*);
__uchar32     __OVBIF __vload_pred_dup(__bool4, __RD const __uchar4*);
__uchar32     __OVBIF __vload_pred_dup(__bool2, __RD const __uchar2*);
#endif

/* VLDDUP2H, VLDDUP4H, VLDDUP8H, VLDDUP16H, VLDDUP32H */
#if __C7X_VEC_SIZE_BITS__ == 512
__short32     __OVBIF __vload_dup(__RD const __short16*);
__short32     __OVBIF __vload_dup(__RD const __short8*);
__short32     __OVBIF __vload_dup(__RD const __short4*);
__short32     __OVBIF __vload_dup(__RD const __short2*);
__short32     __OVBIF __vload_dup(__RD const short*);
__ushort32    __OVBIF __vload_dup(__RD const __ushort16*);
__ushort32    __OVBIF __vload_dup(__RD const __ushort8*);
__ushort32    __OVBIF __vload_dup(__RD const __ushort4*);
__ushort32    __OVBIF __vload_dup(__RD const __ushort2*);
__ushort32    __OVBIF __vload_dup(__RD const __ushort*);

__short32     __OVBIF __vload_pred_dup(__bool16, __RD const __short16*);
__short32     __OVBIF __vload_pred_dup(__bool8, __RD const __short8*);
__short32     __OVBIF __vload_pred_dup(__bool4, __RD const __short4*);
__short32     __OVBIF __vload_pred_dup(__bool2, __RD const __short2*);
__ushort32    __OVBIF __vload_pred_dup(__bool16, __RD const __ushort16*);
__ushort32    __OVBIF __vload_pred_dup(__bool8, __RD const __ushort8*);
__ushort32    __OVBIF __vload_pred_dup(__bool4, __RD const __ushort4*);
__ushort32    __OVBIF __vload_pred_dup(__bool2, __RD const __ushort2*);
#elif __C7X_VEC_SIZE_BITS__ == 256
__short16     __OVBIF __vload_dup(__RD const __short8*);
__short16     __OVBIF __vload_dup(__RD const __short4*);
__short16     __OVBIF __vload_dup(__RD const __short2*);
__short16     __OVBIF __vload_dup(__RD const short*);
__ushort16    __OVBIF __vload_dup(__RD const __ushort8*);
__ushort16    __OVBIF __vload_dup(__RD const __ushort4*);
__ushort16    __OVBIF __vload_dup(__RD const __ushort2*);
__ushort16    __OVBIF __vload_dup(__RD const __ushort*);

__short16     __OVBIF __vload_pred_dup(__bool8, __RD const __short8*);
__short16     __OVBIF __vload_pred_dup(__bool4, __RD const __short4*);
__short16     __OVBIF __vload_pred_dup(__bool2, __RD const __short2*);
__ushort16    __OVBIF __vload_pred_dup(__bool8, __RD const __ushort8*);
__ushort16    __OVBIF __vload_pred_dup(__bool4, __RD const __ushort4*);
__ushort16    __OVBIF __vload_pred_dup(__bool2, __RD const __ushort2*);
#endif

/* VLDDUP2W, VLDDUP4W, VLDDUP8W, VLDDUP16W */
#if __C7X_VEC_SIZE_BITS__ == 512
__int16       __OVBIF __vload_dup(__RD const __int8*);
__int16       __OVBIF __vload_dup(__RD const __int4*);
__int16       __OVBIF __vload_dup(__RD const __int2*);
__int16       __OVBIF __vload_dup(__RD const int*);
__uint16      __OVBIF __vload_dup(__RD const __uint8*);
__uint16      __OVBIF __vload_dup(__RD const __uint4*);
__uint16      __OVBIF __vload_dup(__RD const __uint2*);
__uint16      __OVBIF __vload_dup(__RD const __uint*);
__float16     __OVBIF __vload_dup(__RD const __float8*);
__float16     __OVBIF __vload_dup(__RD const __float4*);
__float16     __OVBIF __vload_dup(__RD const __float2*);
__float16     __OVBIF __vload_dup(__RD const float*);

__int16       __OVBIF __vload_pred_dup(__bool8, __RD const __int8*);
__int16       __OVBIF __vload_pred_dup(__bool4, __RD const __int4*);
__int16       __OVBIF __vload_pred_dup(__bool2, __RD const __int2*);
__uint16      __OVBIF __vload_pred_dup(__bool8, __RD const __uint8*);
__uint16      __OVBIF __vload_pred_dup(__bool4, __RD const __uint4*);
__uint16      __OVBIF __vload_pred_dup(__bool2, __RD const __uint2*);
__float16     __OVBIF __vload_pred_dup(__bool8, __RD const __float8*);
__float16     __OVBIF __vload_pred_dup(__bool4, __RD const __float4*);
__float16     __OVBIF __vload_pred_dup(__bool2, __RD const __float2*);
#elif __C7X_VEC_SIZE_BITS__ == 256
__int8       __OVBIF __vload_dup(__RD const __int4*);
__int8       __OVBIF __vload_dup(__RD const __int2*);
__int8       __OVBIF __vload_dup(__RD const int*);
__uint8      __OVBIF __vload_dup(__RD const __uint4*);
__uint8      __OVBIF __vload_dup(__RD const __uint2*);
__uint8      __OVBIF __vload_dup(__RD const __uint*);
__float8     __OVBIF __vload_dup(__RD const __float4*);
__float8     __OVBIF __vload_dup(__RD const __float2*);
__float8     __OVBIF __vload_dup(__RD const float*);

__int8       __OVBIF __vload_pred_dup(__bool4, __RD const __int4*);
__int8       __OVBIF __vload_pred_dup(__bool2, __RD const __int2*);
__uint8      __OVBIF __vload_pred_dup(__bool4, __RD const __uint4*);
__uint8      __OVBIF __vload_pred_dup(__bool2, __RD const __uint2*);
__float8     __OVBIF __vload_pred_dup(__bool4, __RD const __float4*);
__float8     __OVBIF __vload_pred_dup(__bool2, __RD const __float2*);
#endif

/* VLDDUP2D, VLDDUP4D, VLDDUP8D */
#if __C7X_VEC_SIZE_BITS__ == 512
__long8       __OVBIF __vload_dup(__RD const __long4*);
__long8       __OVBIF __vload_dup(__RD const __long2*);
__long8       __OVBIF __vload_dup(__RD const long*);
__ulong8      __OVBIF __vload_dup(__RD const __ulong4*);
__ulong8      __OVBIF __vload_dup(__RD const __ulong2*);
__ulong8      __OVBIF __vload_dup(__RD const __ulong*);
__double8     __OVBIF __vload_dup(__RD const __double4*);
__double8     __OVBIF __vload_dup(__RD const __double2*);
__double8     __OVBIF __vload_dup(__RD const double*);

__long8       __OVBIF __vload_pred_dup(__bool4, __RD const __long4*);
__long8       __OVBIF __vload_pred_dup(__bool2, __RD const __long2*);
__ulong8      __OVBIF __vload_pred_dup(__bool4, __RD const __ulong4*);
__ulong8      __OVBIF __vload_pred_dup(__bool2, __RD const __ulong2*);
__double8     __OVBIF __vload_pred_dup(__bool4, __RD const __double4*);
__double8     __OVBIF __vload_pred_dup(__bool2, __RD const __double2*);
#elif __C7X_VEC_SIZE_BITS__ == 256
__long4       __OVBIF __vload_dup(__RD const __long2*);
__long4       __OVBIF __vload_dup(__RD const long*);
__ulong4      __OVBIF __vload_dup(__RD const __ulong2*);
__ulong4      __OVBIF __vload_dup(__RD const __ulong*);
__double4     __OVBIF __vload_dup(__RD const __double2*);
__double4     __OVBIF __vload_dup(__RD const double*);

__long4       __OVBIF __vload_pred_dup(__bool2, __RD const __long2*);
__ulong4      __OVBIF __vload_pred_dup(__bool2, __RD const __ulong2*);
__double4     __OVBIF __vload_pred_dup(__bool2, __RD const __double2*);
#endif

/* VLDDUP4G8H, VLDDUP8G4H */
#if __C7X_VEC_SIZE_BITS__ >= 512
__short32     __OVBIF __vload_dup_vec(__RD const __short8*);
__ushort32    __OVBIF __vload_dup_vec(__RD const __ushort8*);
__short32     __OVBIF __vload_dup_vec(__RD const __short4*);
__ushort32    __OVBIF __vload_dup_vec(__RD const __ushort4*);

__short32     __OVBIF __vload_pred_dup_vec(__bool8, __RD const __short8*);
__ushort32    __OVBIF __vload_pred_dup_vec(__bool8, __RD const __ushort8*);
__short32     __OVBIF __vload_pred_dup_vec(__bool4, __RD const __short4*);
__ushort32    __OVBIF __vload_pred_dup_vec(__bool4, __RD const __ushort4*);
#endif

/* VLDBUNPKH, VLDBUNPKHU */
short       __OVBIF __vload_unpack_short(__RD const signed char*);
__short2    __OVBIF __vload_unpack_short(__RD const __char2*);
__short4    __OVBIF __vload_unpack_short(__RD const __char4*);
__short8    __OVBIF __vload_unpack_short(__RD const __char8*);
__short16   __OVBIF __vload_unpack_short(__RD const __char16*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__short32   __OVBIF __vload_unpack_short(__RD const __char32*);
#endif
__ushort    __OVBIF __vload_unpack_short(__RD const __uchar*);
__ushort2   __OVBIF __vload_unpack_short(__RD const __uchar2*);
__ushort4   __OVBIF __vload_unpack_short(__RD const __uchar4*);
__ushort8   __OVBIF __vload_unpack_short(__RD const __uchar8*);
__ushort16  __OVBIF __vload_unpack_short(__RD const __uchar16*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__ushort32  __OVBIF __vload_unpack_short(__RD const __uchar32*);
#endif

__short2    __OVBIF __vload_pred_unpack_short(__bool2, __RD const __char2*);
__short4    __OVBIF __vload_pred_unpack_short(__bool4, __RD const __char4*);
__short8    __OVBIF __vload_pred_unpack_short(__bool8, __RD const __char8*);
__short16   __OVBIF __vload_pred_unpack_short(__bool16, __RD const __char16*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__short32   __OVBIF __vload_pred_unpack_short(__bool32, __RD const __char32*);
#endif

__ushort2   __OVBIF __vload_pred_unpack_short(__bool2, __RD const __uchar2*);
__ushort4   __OVBIF __vload_pred_unpack_short(__bool4, __RD const __uchar4*);
__ushort8   __OVBIF __vload_pred_unpack_short(__bool8, __RD const __uchar8*);
__ushort16  __OVBIF __vload_pred_unpack_short(__bool16, __RD const __uchar16*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__ushort32  __OVBIF __vload_pred_unpack_short(__bool32, __RD const __uchar32*);
#endif

/* VLDBUNPKW, VLDBUNPKWU */
int         __OVBIF __vload_unpack_int(__RD const signed char*);
__int2      __OVBIF __vload_unpack_int(__RD const __char2*);
__int4      __OVBIF __vload_unpack_int(__RD const __char4*);
__int8      __OVBIF __vload_unpack_int(__RD const __char8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__int16     __OVBIF __vload_unpack_int(__RD const __char16*);
#endif

__uint      __OVBIF __vload_unpack_int(__RD const __uchar*);
__uint2     __OVBIF __vload_unpack_int(__RD const __uchar2*);
__uint4     __OVBIF __vload_unpack_int(__RD const __uchar4*);
__uint8     __OVBIF __vload_unpack_int(__RD const __uchar8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__uint16    __OVBIF __vload_unpack_int(__RD const __uchar16*);
#endif

__int2      __OVBIF __vload_pred_unpack_int(__bool2, __RD const __char2*);
__int4      __OVBIF __vload_pred_unpack_int(__bool4, __RD const __char4*);
__int8      __OVBIF __vload_pred_unpack_int(__bool8, __RD const __char8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__int16     __OVBIF __vload_pred_unpack_int(__bool16, __RD const __char16*);
#endif

__uint2     __OVBIF __vload_pred_unpack_int(__bool2, __RD const __uchar2*);
__uint4     __OVBIF __vload_pred_unpack_int(__bool4, __RD const __uchar4*);
__uint8     __OVBIF __vload_pred_unpack_int(__bool8, __RD const __uchar8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__uint16    __OVBIF __vload_pred_unpack_int(__bool16, __RD const __uchar16*);
#endif

/* VLDHUNPKW, VLDHUNPKWU */
int         __OVBIF __vload_unpack_int(__RD const short*);
__int2      __OVBIF __vload_unpack_int(__RD const __short2*);
__int4      __OVBIF __vload_unpack_int(__RD const __short4*);
__int8      __OVBIF __vload_unpack_int(__RD const __short8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__int16     __OVBIF __vload_unpack_int(__RD const __short16*);
#endif

__uint      __OVBIF __vload_unpack_int(__RD const __ushort*);
__uint2     __OVBIF __vload_unpack_int(__RD const __ushort2*);
__uint4     __OVBIF __vload_unpack_int(__RD const __ushort4*);
__uint8     __OVBIF __vload_unpack_int(__RD const __ushort8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__uint16    __OVBIF __vload_unpack_int(__RD const __ushort16*);
#endif

__int2      __OVBIF __vload_pred_unpack_int(__bool2, __RD const __short2*);
__int4      __OVBIF __vload_pred_unpack_int(__bool4, __RD const __short4*);
__int8      __OVBIF __vload_pred_unpack_int(__bool8, __RD const __short8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__int16     __OVBIF __vload_pred_unpack_int(__bool16, __RD const __short16*);
#endif

__uint2     __OVBIF __vload_pred_unpack_int(__bool2, __RD const __ushort2*);
__uint4     __OVBIF __vload_pred_unpack_int(__bool4, __RD const __ushort4*);
__uint8     __OVBIF __vload_pred_unpack_int(__bool8, __RD const __ushort8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__uint16    __OVBIF __vload_pred_unpack_int(__bool16, __RD const __ushort16*);
#endif

/* VLDBUNPKD, VLDBUNPKDU */
long        __OVBIF __vload_unpack_long(__RD const signed char*);
__long2     __OVBIF __vload_unpack_long(__RD const __char2*);
__long4     __OVBIF __vload_unpack_long(__RD const __char4*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__long8     __OVBIF __vload_unpack_long(__RD const __char8*);
#endif

__ulong     __OVBIF __vload_unpack_long(__RD const __uchar*);
__ulong2    __OVBIF __vload_unpack_long(__RD const __uchar2*);
__ulong4    __OVBIF __vload_unpack_long(__RD const __uchar4*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__ulong8    __OVBIF __vload_unpack_long(__RD const __uchar8*);
#endif

__long2     __OVBIF __vload_pred_unpack_long(__bool2, __RD const __char2*);
__long4     __OVBIF __vload_pred_unpack_long(__bool4, __RD const __char4*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__long8     __OVBIF __vload_pred_unpack_long(__bool8, __RD const __char8*);
#endif

__ulong2    __OVBIF __vload_pred_unpack_long(__bool2, __RD const __uchar2*);
__ulong4    __OVBIF __vload_pred_unpack_long(__bool4, __RD const __uchar4*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__ulong8    __OVBIF __vload_pred_unpack_long(__bool8, __RD const __uchar8*);
#endif

/* VLDHUNPKD, VLDHUNPKDU */
long        __OVBIF __vload_unpack_long(__RD const short*);
__long2     __OVBIF __vload_unpack_long(__RD const __short2*);
__long4     __OVBIF __vload_unpack_long(__RD const __short4*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__long8     __OVBIF __vload_unpack_long(__RD const __short8*);
#endif

__ulong     __OVBIF __vload_unpack_long(__RD const __ushort*);
__ulong2    __OVBIF __vload_unpack_long(__RD const __ushort2*);
__ulong4    __OVBIF __vload_unpack_long(__RD const __ushort4*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__ulong8    __OVBIF __vload_unpack_long(__RD const __ushort8*);
#endif

__long2     __OVBIF __vload_pred_unpack_long(__bool2, __RD const __short2*);
__long4     __OVBIF __vload_pred_unpack_long(__bool4, __RD const __short4*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__long8     __OVBIF __vload_pred_unpack_long(__bool8, __RD const __short8*);
#endif

__ulong2    __OVBIF __vload_pred_unpack_long(__bool2, __RD const __ushort2*);
__ulong4    __OVBIF __vload_pred_unpack_long(__bool4, __RD const __ushort4*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__ulong8    __OVBIF __vload_pred_unpack_long(__bool8, __RD const __ushort8*);
#endif

/* VLDWUNPKD, VLDWUNPKDU */
long        __OVBIF __vload_unpack_long(__RD const int*);
__long2     __OVBIF __vload_unpack_long(__RD const __int2*);
__long4     __OVBIF __vload_unpack_long(__RD const __int4*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__long8     __OVBIF __vload_unpack_long(__RD const __int8*);
#endif

__ulong     __OVBIF __vload_unpack_long(__RD const __uint*);
__ulong2    __OVBIF __vload_unpack_long(__RD const __uint2*);
__ulong4    __OVBIF __vload_unpack_long(__RD const __uint4*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__ulong8    __OVBIF __vload_unpack_long(__RD const __uint8*);
#endif

__long2     __OVBIF __vload_pred_unpack_long(__bool2, __RD const __int2*);
__long4     __OVBIF __vload_pred_unpack_long(__bool4, __RD const __int4*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__long8     __OVBIF __vload_pred_unpack_long(__bool8, __RD const __int8*);
#endif

__ulong2    __OVBIF __vload_pred_unpack_long(__bool2, __RD const __uint2*);
__ulong4    __OVBIF __vload_pred_unpack_long(__bool4, __RD const __uint4*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__ulong8    __OVBIF __vload_pred_unpack_long(__bool8, __RD const __uint8*);
#endif

/* VLDEBUNPKW, VLDEHUNPKW */
int         __OVBIF __vload_deinterleave_int(__RD const __char2*);
__int2      __OVBIF __vload_deinterleave_int(__RD const __char4*);
__int4      __OVBIF __vload_deinterleave_int(__RD const __char8*);
__int8      __OVBIF __vload_deinterleave_int(__RD const __char16*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__int16     __OVBIF __vload_deinterleave_int(__RD const __char32*);
#endif

int         __OVBIF __vload_deinterleave_int(__RD const __short2*);
__int2      __OVBIF __vload_deinterleave_int(__RD const __short4*);
__int4      __OVBIF __vload_deinterleave_int(__RD const __short8*);
__int8      __OVBIF __vload_deinterleave_int(__RD const __short16*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__int16     __OVBIF __vload_deinterleave_int(__RD const __short32*);
#endif

int         __OVBIF __vload_pred_deinterleave_int(__bool2, __RD const __char2*);
__int2      __OVBIF __vload_pred_deinterleave_int(__bool4, __RD const __char4*);
__int4      __OVBIF __vload_pred_deinterleave_int(__bool8, __RD const __char8*);
__int8      __OVBIF __vload_pred_deinterleave_int(__bool16, __RD const __char16*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__int16     __OVBIF __vload_pred_deinterleave_int(__bool32, __RD const __char32*);
#endif

int         __OVBIF __vload_pred_deinterleave_int(__bool2, __RD const __short2*);
__int2      __OVBIF __vload_pred_deinterleave_int(__bool4, __RD const __short4*);
__int4      __OVBIF __vload_pred_deinterleave_int(__bool8, __RD const __short8*);
__int8      __OVBIF __vload_pred_deinterleave_int(__bool16, __RD const __short16*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__int16     __OVBIF __vload_pred_deinterleave_int(__bool32, __RD const __short32*);
#endif

/* VLDEBUNPKWU, VLDEHUNPKWU */
__uint       __OVBIF __vload_deinterleave_int(__RD const __uchar2*);
__uint2      __OVBIF __vload_deinterleave_int(__RD const __uchar4*);
__uint4      __OVBIF __vload_deinterleave_int(__RD const __uchar8*);
__uint8      __OVBIF __vload_deinterleave_int(__RD const __uchar16*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__uint16     __OVBIF __vload_deinterleave_int(__RD const __uchar32*);
#endif

__uint       __OVBIF __vload_deinterleave_int(__RD const __ushort2*);
__uint2      __OVBIF __vload_deinterleave_int(__RD const __ushort4*);
__uint4      __OVBIF __vload_deinterleave_int(__RD const __ushort8*);
__uint8      __OVBIF __vload_deinterleave_int(__RD const __ushort16*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__uint16     __OVBIF __vload_deinterleave_int(__RD const __ushort32*);
#endif

__uint       __OVBIF __vload_pred_deinterleave_int(__bool2, __RD const __uchar2*);
__uint2      __OVBIF __vload_pred_deinterleave_int(__bool4, __RD const __uchar4*);
__uint4      __OVBIF __vload_pred_deinterleave_int(__bool8, __RD const __uchar8*);
__uint8      __OVBIF __vload_pred_deinterleave_int(__bool16, __RD const __uchar16*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__uint16     __OVBIF __vload_pred_deinterleave_int(__bool32, __RD const __uchar32*);
#endif

__uint       __OVBIF __vload_pred_deinterleave_int(__bool2, __RD const __ushort2*);
__uint2      __OVBIF __vload_pred_deinterleave_int(__bool4, __RD const __ushort4*);
__uint4      __OVBIF __vload_pred_deinterleave_int(__bool8, __RD const __ushort8*);
__uint8      __OVBIF __vload_pred_deinterleave_int(__bool16, __RD const __ushort16*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__uint16     __OVBIF __vload_pred_deinterleave_int(__bool32, __RD const __ushort32*);
#endif

/* VLDEBUNPKD, VLDEHUNPKD */
long         __OVBIF __vload_deinterleave_long(__RD const __char2*);
__long2      __OVBIF __vload_deinterleave_long(__RD const __char4*);
__long4      __OVBIF __vload_deinterleave_long(__RD const __char8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__long8      __OVBIF __vload_deinterleave_long(__RD const __char16*);
#endif

long         __OVBIF __vload_deinterleave_long(__RD const __short2*);
__long2      __OVBIF __vload_deinterleave_long(__RD const __short4*);
__long4      __OVBIF __vload_deinterleave_long(__RD const __short8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__long8      __OVBIF __vload_deinterleave_long(__RD const __short16*);
#endif

long         __OVBIF __vload_pred_deinterleave_long(__bool2, __RD const __char2*);
__long2      __OVBIF __vload_pred_deinterleave_long(__bool4, __RD const __char4*);
__long4      __OVBIF __vload_pred_deinterleave_long(__bool8, __RD const __char8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__long8      __OVBIF __vload_pred_deinterleave_long(__bool16, __RD const __char16*);
#endif

long         __OVBIF __vload_pred_deinterleave_long(__bool2, __RD const __short2*);
__long2      __OVBIF __vload_pred_deinterleave_long(__bool4, __RD const __short4*);
__long4      __OVBIF __vload_pred_deinterleave_long(__bool8, __RD const __short8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__long8      __OVBIF __vload_pred_deinterleave_long(__bool16, __RD const __short16*);
#endif

/* VLDEBUNPKDU, VLDEHUNPKDU */
__ulong       __OVBIF __vload_deinterleave_long(__RD const __uchar2*);
__ulong2      __OVBIF __vload_deinterleave_long(__RD const __uchar4*);
__ulong4      __OVBIF __vload_deinterleave_long(__RD const __uchar8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__ulong8      __OVBIF __vload_deinterleave_long(__RD const __uchar16*);
#endif

__ulong       __OVBIF __vload_deinterleave_long(__RD const __ushort2*);
__ulong2      __OVBIF __vload_deinterleave_long(__RD const __ushort4*);
__ulong4      __OVBIF __vload_deinterleave_long(__RD const __ushort8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__ulong8      __OVBIF __vload_deinterleave_long(__RD const __ushort16*);
#endif

__ulong       __OVBIF __vload_pred_deinterleave_long(__bool2, __RD const __uchar2*);
__ulong2      __OVBIF __vload_pred_deinterleave_long(__bool4, __RD const __uchar4*);
__ulong4      __OVBIF __vload_pred_deinterleave_long(__bool8, __RD const __uchar8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__ulong8      __OVBIF __vload_pred_deinterleave_long(__bool16, __RD const __uchar16*);
#endif

__ulong       __OVBIF __vload_pred_deinterleave_long(__bool2, __RD const __ushort2*);
__ulong2      __OVBIF __vload_pred_deinterleave_long(__bool4, __RD const __ushort4*);
__ulong4      __OVBIF __vload_pred_deinterleave_long(__bool8, __RD const __ushort8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__ulong8      __OVBIF __vload_pred_deinterleave_long(__bool16, __RD const __ushort16*);
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
/* bool2 pred = __SA0_BOOL(char2);                                           */
/* char2* ptr = __SA0ADV(char2, base_ptr);                                   */
/* __vstore_pred(pred, ptr, data);                                           */
/*                                                                           */
/* If the idiom is malformed or the compiler fails to optimize the idiom, an */
/* equivalent series of instructions will instead be generated to create the */
/* predicate and then store with explicit predication.                       */
/*****************************************************************************/
/* VSTINTLB, VSTINTLH, VSTINTLW, VSTINTLD - STORES EVERY EVEN ELEMENT */
#if __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_interleave(__WR __char64*,   __char64,   __char64);
void __OVBIFM __vstore_interleave(__WR __short32*,  __short32,  __short32);
void __OVBIFM __vstore_interleave(__WR __int16*,    __int16,    __int16);
void __OVBIFM __vstore_interleave(__WR __long8*,    __long8,    __long8);
void __OVBIFM __vstore_interleave(__WR __uchar64*,  __uchar64,  __uchar64);
void __OVBIFM __vstore_interleave(__WR __ushort32*, __ushort32, __ushort32);
void __OVBIFM __vstore_interleave(__WR __uint16*,   __uint16,   __uint16);
void __OVBIFM __vstore_interleave(__WR __ulong8*,   __ulong8,   __ulong8);
#elif __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_interleave(__WR __char32*,   __char32,   __char32);
void __OVBIFM __vstore_interleave(__WR __short16*,  __short16,  __short16);
void __OVBIFM __vstore_interleave(__WR __int8*,    __int8,    __int8);
void __OVBIFM __vstore_interleave(__WR __long4*,    __long4,    __long4);
void __OVBIFM __vstore_interleave(__WR __uchar32*,  __uchar32,  __uchar32);
void __OVBIFM __vstore_interleave(__WR __ushort16*, __ushort16, __ushort16);
void __OVBIFM __vstore_interleave(__WR __uint8*,   __uint8,   __uint8);
void __OVBIFM __vstore_interleave(__WR __ulong4*,   __ulong4,   __ulong4);
#endif

#ifndef __C7100__
/* VSTINTHB, VSTINTHH, VSTINTHW, VSTINTHD - STORES EVERY ODD ELEMENT */
#if __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_interleave_odd(__WR __char64*,   __char64,   __char64);
void __OVBIFM __vstore_interleave_odd(__WR __short32*,  __short32,  __short32);
void __OVBIFM __vstore_interleave_odd(__WR __int16*,    __int16,    __int16);
void __OVBIFM __vstore_interleave_odd(__WR __long8*,    __long8,    __long8);
void __OVBIFM __vstore_interleave_odd(__WR __uchar64*,  __uchar64,  __uchar64);
void __OVBIFM __vstore_interleave_odd(__WR __ushort32*, __ushort32, __ushort32);
void __OVBIFM __vstore_interleave_odd(__WR __uint16*,   __uint16,   __uint16);
void __OVBIFM __vstore_interleave_odd(__WR __ulong8*,   __ulong8,   __ulong8);
#elif __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_interleave_odd(__WR __char32*,   __char32,   __char32);
void __OVBIFM __vstore_interleave_odd(__WR __short16*,  __short16,  __short16);
void __OVBIFM __vstore_interleave_odd(__WR __int8*,    __int8,    __int8);
void __OVBIFM __vstore_interleave_odd(__WR __long4*,    __long4,    __long4);
void __OVBIFM __vstore_interleave_odd(__WR __uchar32*,  __uchar32,  __uchar32);
void __OVBIFM __vstore_interleave_odd(__WR __ushort16*, __ushort16, __ushort16);
void __OVBIFM __vstore_interleave_odd(__WR __uint8*,   __uint8,   __uint8);
void __OVBIFM __vstore_interleave_odd(__WR __ulong4*,   __ulong4,   __ulong4);
#endif
#endif /* ! __C7100__ */

/* VSTINTLB4 - STORES EVERY FOURTH ELEMENT */
#if __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_interleave4(__WR __char32*,   __char64,   __char64);
void __OVBIFM __vstore_interleave4(__WR __uchar32*,  __uchar64,  __uchar64);
#elif __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_interleave4(__WR __char16*,   __char32,   __char32);
void __OVBIFM __vstore_interleave4(__WR __uchar16*,  __uchar32,  __uchar32);
#endif

#ifndef __C7100__
/* VSTLLINTB, VSTLLINTH, VSTLLINTW, VSTLLINTD - STORES LOW VECTOR HALVES */
#if __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_interleave_low_low(__WR __char64*,   __char64,   __char64);
void __OVBIFM __vstore_interleave_low_low(__WR __short32*,  __short32,  __short32);
void __OVBIFM __vstore_interleave_low_low(__WR __int16*,    __int16,    __int16);
void __OVBIFM __vstore_interleave_low_low(__WR __long8*,    __long8,    __long8);
void __OVBIFM __vstore_interleave_low_low(__WR __uchar64*,  __uchar64,  __uchar64);
void __OVBIFM __vstore_interleave_low_low(__WR __ushort32*, __ushort32, __ushort32);
void __OVBIFM __vstore_interleave_low_low(__WR __uint16*,   __uint16,   __uint16);
void __OVBIFM __vstore_interleave_low_low(__WR __ulong8*,   __ulong8,   __ulong8);
#elif __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_interleave_low_low(__WR __char32*,   __char32,   __char32);
void __OVBIFM __vstore_interleave_low_low(__WR __short16*,  __short16,  __short16);
void __OVBIFM __vstore_interleave_low_low(__WR __int8*,    __int8,    __int8);
void __OVBIFM __vstore_interleave_low_low(__WR __long4*,    __long4,    __long4);
void __OVBIFM __vstore_interleave_low_low(__WR __uchar32*,  __uchar32,  __uchar32);
void __OVBIFM __vstore_interleave_low_low(__WR __ushort16*, __ushort16, __ushort16);
void __OVBIFM __vstore_interleave_low_low(__WR __uint8*,   __uint8,   __uint8);
void __OVBIFM __vstore_interleave_low_low(__WR __ulong4*,   __ulong4,   __ulong4);
#endif

/* Half-vector form of VSTLLINT[BHWD]. */  
#if __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_interleave_low_low(__WR __char64*,   __char32,   __char32);
void __OVBIFM __vstore_interleave_low_low(__WR __short32*,  __short16,  __short16);
void __OVBIFM __vstore_interleave_low_low(__WR __int16*,    __int8,    __int8);
void __OVBIFM __vstore_interleave_low_low(__WR __long8*,    __long4,    __long4);
void __OVBIFM __vstore_interleave_low_low(__WR __uchar64*,  __uchar32,  __uchar32);
void __OVBIFM __vstore_interleave_low_low(__WR __ushort32*, __ushort16, __ushort16);
void __OVBIFM __vstore_interleave_low_low(__WR __uint16*,   __uint8,   __uint8);
void __OVBIFM __vstore_interleave_low_low(__WR __ulong8*,   __ulong4,   __ulong4);
#elif __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_interleave_low_low(__WR __char32*,   __char16,   __char16);
void __OVBIFM __vstore_interleave_low_low(__WR __short16*,  __short8,  __short8);
void __OVBIFM __vstore_interleave_low_low(__WR __int8*,    __int4,    __int4);
void __OVBIFM __vstore_interleave_low_low(__WR __long4*,    __long2,    __long2);
void __OVBIFM __vstore_interleave_low_low(__WR __uchar32*,  __uchar16,  __uchar16);
void __OVBIFM __vstore_interleave_low_low(__WR __ushort16*, __ushort8, __ushort8);
void __OVBIFM __vstore_interleave_low_low(__WR __uint8*,   __uint4,   __uint4);
void __OVBIFM __vstore_interleave_low_low(__WR __ulong4*,   __ulong2,   __ulong2);
#endif

/* VSTHHINTB, VSTHHINTH, VSTHHINTW, VSTHHINTD - STORES HIGH VECTOR HALVES */
#if __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_interleave_high_high(__WR __char64*,   __char64,   __char64);
void __OVBIFM __vstore_interleave_high_high(__WR __short32*,  __short32,  __short32);
void __OVBIFM __vstore_interleave_high_high(__WR __int16*,    __int16,    __int16);
void __OVBIFM __vstore_interleave_high_high(__WR __long8*,    __long8,    __long8);
void __OVBIFM __vstore_interleave_high_high(__WR __uchar64*,  __uchar64,  __uchar64);
void __OVBIFM __vstore_interleave_high_high(__WR __ushort32*, __ushort32, __ushort32);
void __OVBIFM __vstore_interleave_high_high(__WR __uint16*,   __uint16,   __uint16);
void __OVBIFM __vstore_interleave_high_high(__WR __ulong8*,   __ulong8,   __ulong8);
#elif __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_interleave_high_high(__WR __char32*,   __char32,   __char32);
void __OVBIFM __vstore_interleave_high_high(__WR __short16*,  __short16,  __short16);
void __OVBIFM __vstore_interleave_high_high(__WR __int8*,    __int8,    __int8);
void __OVBIFM __vstore_interleave_high_high(__WR __long4*,    __long4,    __long4);
void __OVBIFM __vstore_interleave_high_high(__WR __uchar32*,  __uchar32,  __uchar32);
void __OVBIFM __vstore_interleave_high_high(__WR __ushort16*, __ushort16, __ushort16);
void __OVBIFM __vstore_interleave_high_high(__WR __uint8*,   __uint8,   __uint8);
void __OVBIFM __vstore_interleave_high_high(__WR __ulong4*,   __ulong4,   __ulong4);
#endif
#endif /* ! __C7100__ */

/* VSTPINTLB, VSTPINTLH, VSTPINTLW, VSTPINTLD - STORES EVERY EVEN ELEMENT */
#if __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_pred_interleave(__bool64, __WR __char64*,  __char64,  __char64);
void __OVBIFM __vstore_pred_interleave(__bool32, __WR __short32*, __short32, __short32);
void __OVBIFM __vstore_pred_interleave(__bool16, __WR __int16*,   __int16,   __int16);
void __OVBIFM __vstore_pred_interleave(__bool8, __WR __long8*,   __long8,   __long8);
void __OVBIFM __vstore_pred_interleave(__bool64, __WR __uchar64*, __uchar64, __uchar64);
void __OVBIFM __vstore_pred_interleave(__bool32, __WR __ushort32*,__ushort32,__ushort32);
void __OVBIFM __vstore_pred_interleave(__bool16, __WR __uint16*,  __uint16,  __uint16);
void __OVBIFM __vstore_pred_interleave(__bool8, __WR __ulong8*,  __ulong8,  __ulong8);
#elif __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_pred_interleave(__bool32, __WR __char32*,  __char32,  __char32);
void __OVBIFM __vstore_pred_interleave(__bool16, __WR __short16*, __short16, __short16);
void __OVBIFM __vstore_pred_interleave(__bool8, __WR __int8*,   __int8,   __int8);
void __OVBIFM __vstore_pred_interleave(__bool4, __WR __long4*,   __long4,   __long4);
void __OVBIFM __vstore_pred_interleave(__bool32, __WR __uchar32*, __uchar32, __uchar32);
void __OVBIFM __vstore_pred_interleave(__bool16, __WR __ushort16*,__ushort16,__ushort16);
void __OVBIFM __vstore_pred_interleave(__bool8, __WR __uint8*,  __uint8,  __uint8);
void __OVBIFM __vstore_pred_interleave(__bool4, __WR __ulong4*,  __ulong4,  __ulong4);
#endif

#ifndef __C7100__
/* VSTPINTHB, VSTPINTHH, VSTPINTHW, VSTPINTHD - STORES EVERY ODD ELEMENT */
#if __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_pred_interleave_odd(__bool64, __WR __char64*,  __char64,  __char64);
void __OVBIFM __vstore_pred_interleave_odd(__bool32, __WR __short32*, __short32, __short32);
void __OVBIFM __vstore_pred_interleave_odd(__bool16, __WR __int16*,   __int16,   __int16);
void __OVBIFM __vstore_pred_interleave_odd(__bool8, __WR __long8*,   __long8,   __long8);
void __OVBIFM __vstore_pred_interleave_odd(__bool64, __WR __uchar64*, __uchar64, __uchar64);
void __OVBIFM __vstore_pred_interleave_odd(__bool32, __WR __ushort32*,__ushort32,__ushort32);
void __OVBIFM __vstore_pred_interleave_odd(__bool16, __WR __uint16*,  __uint16,  __uint16);
void __OVBIFM __vstore_pred_interleave_odd(__bool8, __WR __ulong8*,  __ulong8,  __ulong8);
#elif __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_pred_interleave_odd(__bool32, __WR __char32*,  __char32,  __char32);
void __OVBIFM __vstore_pred_interleave_odd(__bool16, __WR __short16*, __short16, __short16);
void __OVBIFM __vstore_pred_interleave_odd(__bool8, __WR __int8*,   __int8,   __int8);
void __OVBIFM __vstore_pred_interleave_odd(__bool4, __WR __long4*,   __long4,   __long4);
void __OVBIFM __vstore_pred_interleave_odd(__bool32, __WR __uchar32*, __uchar32, __uchar32);
void __OVBIFM __vstore_pred_interleave_odd(__bool16, __WR __ushort16*,__ushort16,__ushort16);
void __OVBIFM __vstore_pred_interleave_odd(__bool8, __WR __uint8*,  __uint8,  __uint8);
void __OVBIFM __vstore_pred_interleave_odd(__bool4, __WR __ulong4*,  __ulong4,  __ulong4);
#endif
#endif /* ! __C7100__ */

/* VSTPINTLB4 - STORES EVERY FOURTH ELEMENT */
#if __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_pred_interleave4(__bool32, __WR __char32*,  __char64,   __char64);
void __OVBIFM __vstore_pred_interleave4(__bool32, __WR __uchar32*, __uchar64,  __uchar64);
#elif __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_pred_interleave4(__bool16, __WR __char16*,  __char32,   __char32);
void __OVBIFM __vstore_pred_interleave4(__bool16, __WR __uchar16*, __uchar32,  __uchar32);
#endif

#ifndef __C7100__
/* VSTPLLINTB, VSTPLLINTH, VSTPLLINTW, VSTPLLINTD - STORES LOW VECTOR HALVES */
#if __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_pred_interleave_low_low(__bool64, __WR __char64*,  __char64,  __char64);
void __OVBIFM __vstore_pred_interleave_low_low(__bool32, __WR __short32*, __short32, __short32);
void __OVBIFM __vstore_pred_interleave_low_low(__bool16, __WR __int16*,   __int16,   __int16);
void __OVBIFM __vstore_pred_interleave_low_low(__bool8, __WR __long8*,   __long8,   __long8);
void __OVBIFM __vstore_pred_interleave_low_low(__bool64, __WR __uchar64*, __uchar64, __uchar64);
void __OVBIFM __vstore_pred_interleave_low_low(__bool32, __WR __ushort32*,__ushort32,__ushort32);
void __OVBIFM __vstore_pred_interleave_low_low(__bool16, __WR __uint16*,  __uint16,  __uint16);
void __OVBIFM __vstore_pred_interleave_low_low(__bool8, __WR __ulong8*,  __ulong8,  __ulong8);
#elif __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_pred_interleave_low_low(__bool32, __WR __char32*,  __char32,  __char32);
void __OVBIFM __vstore_pred_interleave_low_low(__bool16, __WR __short16*, __short16, __short16);
void __OVBIFM __vstore_pred_interleave_low_low(__bool8, __WR __int8*,   __int8,   __int8);
void __OVBIFM __vstore_pred_interleave_low_low(__bool4, __WR __long4*,   __long4,   __long4);
void __OVBIFM __vstore_pred_interleave_low_low(__bool32, __WR __uchar32*, __uchar32, __uchar32);
void __OVBIFM __vstore_pred_interleave_low_low(__bool16, __WR __ushort16*,__ushort16,__ushort16);
void __OVBIFM __vstore_pred_interleave_low_low(__bool8, __WR __uint8*,  __uint8,  __uint8);
void __OVBIFM __vstore_pred_interleave_low_low(__bool4, __WR __ulong4*,  __ulong4,  __ulong4);
#endif

/* Half-vector form of VSTPLLINT[BHWD]. */
#if __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_pred_interleave_low_low(__bool64, __WR __char64*,  __char32,  __char32);
void __OVBIFM __vstore_pred_interleave_low_low(__bool32, __WR __short32*, __short16, __short16);
void __OVBIFM __vstore_pred_interleave_low_low(__bool16, __WR __int16*,   __int8,   __int8);
void __OVBIFM __vstore_pred_interleave_low_low(__bool8, __WR __long8*,   __long4,   __long4);
void __OVBIFM __vstore_pred_interleave_low_low(__bool64, __WR __uchar64*, __uchar32, __uchar32);
void __OVBIFM __vstore_pred_interleave_low_low(__bool32, __WR __ushort32*,__ushort16,__ushort16);
void __OVBIFM __vstore_pred_interleave_low_low(__bool16, __WR __uint16*,  __uint8,  __uint8);
void __OVBIFM __vstore_pred_interleave_low_low(__bool8, __WR __ulong8*,  __ulong4,  __ulong4);
#elif __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_pred_interleave_low_low(__bool32, __WR __char32*,  __char16,  __char16);
void __OVBIFM __vstore_pred_interleave_low_low(__bool16, __WR __short16*, __short8, __short8);
void __OVBIFM __vstore_pred_interleave_low_low(__bool8, __WR __int8*,   __int4,   __int4);
void __OVBIFM __vstore_pred_interleave_low_low(__bool4, __WR __long4*,   __long2,   __long2);
void __OVBIFM __vstore_pred_interleave_low_low(__bool32, __WR __uchar32*, __uchar16, __uchar16);
void __OVBIFM __vstore_pred_interleave_low_low(__bool16, __WR __ushort16*,__ushort8,__ushort8);
void __OVBIFM __vstore_pred_interleave_low_low(__bool8, __WR __uint8*,  __uint4,  __uint4);
void __OVBIFM __vstore_pred_interleave_low_low(__bool4, __WR __ulong4*,  __ulong2,  __ulong2);
#endif

/* VSTPHHINTB, VSTPHHINTH, VSTPHHINTW, VSTPHHINTD - STORES HIGH VECTOR HALVES */
#if __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_pred_interleave_high_high(__bool64, __WR __char64*,  __char64,  __char64);
void __OVBIFM __vstore_pred_interleave_high_high(__bool32, __WR __short32*, __short32, __short32);
void __OVBIFM __vstore_pred_interleave_high_high(__bool16, __WR __int16*,   __int16,   __int16);
void __OVBIFM __vstore_pred_interleave_high_high(__bool8, __WR __long8*,   __long8,   __long8);
void __OVBIFM __vstore_pred_interleave_high_high(__bool64, __WR __uchar64*, __uchar64, __uchar64);
void __OVBIFM __vstore_pred_interleave_high_high(__bool32, __WR __ushort32*,__ushort32,__ushort32);
void __OVBIFM __vstore_pred_interleave_high_high(__bool16, __WR __uint16*,  __uint16,  __uint16);
void __OVBIFM __vstore_pred_interleave_high_high(__bool8, __WR __ulong8*,  __ulong8,  __ulong8);
#elif __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_pred_interleave_high_high(__bool32, __WR __char32*,  __char32,  __char32);
void __OVBIFM __vstore_pred_interleave_high_high(__bool16, __WR __short16*, __short16, __short16);
void __OVBIFM __vstore_pred_interleave_high_high(__bool8, __WR __int8*,   __int8,   __int8);
void __OVBIFM __vstore_pred_interleave_high_high(__bool4, __WR __long4*,   __long4,   __long4);
void __OVBIFM __vstore_pred_interleave_high_high(__bool32, __WR __uchar32*, __uchar32, __uchar32);
void __OVBIFM __vstore_pred_interleave_high_high(__bool16, __WR __ushort16*,__ushort16,__ushort16);
void __OVBIFM __vstore_pred_interleave_high_high(__bool8, __WR __uint8*,  __uint8,  __uint8);
void __OVBIFM __vstore_pred_interleave_high_high(__bool4, __WR __ulong4*,  __ulong4,  __ulong4);
#endif
#endif /* ! __C7100__ */

/* VSTP2B, VSTP4B, VSTP8B, VSTP16B, VSTP32B, VSTP64B */
void __OVBIFM __vstore_pred(__bool2,  __WR __char2*,   __char2);
void __OVBIFM __vstore_pred(__bool4,  __WR __char4*,   __char4);
void __OVBIFM __vstore_pred(__bool8,  __WR __char8*,   __char8);
void __OVBIFM __vstore_pred(__bool16, __WR __char16*,  __char16);
void __OVBIFM __vstore_pred(__bool32, __WR __char32*,  __char32);
#if __C7X_VEC_SIZE_BITS__ >= 512
void __OVBIFM __vstore_pred(__bool64, __WR __char64*,  __char64);
#endif

void __OVBIFM __vstore_pred(__bool2,  __WR __uchar2*,  __uchar2);
void __OVBIFM __vstore_pred(__bool4,  __WR __uchar4*,  __uchar4);
void __OVBIFM __vstore_pred(__bool8,  __WR __uchar8*,  __uchar8);
void __OVBIFM __vstore_pred(__bool16, __WR __uchar16*, __uchar16);
void __OVBIFM __vstore_pred(__bool32, __WR __uchar32*, __uchar32);
#if __C7X_VEC_SIZE_BITS__ >= 512
void __OVBIFM __vstore_pred(__bool64, __WR __uchar64*, __uchar64);
#endif

/* VSTP2H, VSTP4H, VSTP8H, VSTP16H, VSTP32H */
void __OVBIFM __vstore_pred(__bool2,  __WR __short2*, __short2);
void __OVBIFM __vstore_pred(__bool4,  __WR __short4*, __short4);
void __OVBIFM __vstore_pred(__bool8,  __WR __short8*, __short8);
void __OVBIFM __vstore_pred(__bool16, __WR __short16*, __short16);
#if __C7X_VEC_SIZE_BITS__ >= 512
void __OVBIFM __vstore_pred(__bool32, __WR __short32*, __short32);
#endif

void __OVBIFM __vstore_pred(__bool2,  __WR __ushort2*, __ushort2);
void __OVBIFM __vstore_pred(__bool4,  __WR __ushort4*, __ushort4);
void __OVBIFM __vstore_pred(__bool8,  __WR __ushort8*, __ushort8);
void __OVBIFM __vstore_pred(__bool16, __WR __ushort16*, __ushort16);
#if __C7X_VEC_SIZE_BITS__ >= 512
void __OVBIFM __vstore_pred(__bool32, __WR __ushort32*, __ushort32);
#endif

void __OVBIFM __vstore_pred(__bool2,  __WR __cchar2*, __cchar2);
void __OVBIFM __vstore_pred(__bool4,  __WR __cchar4*, __cchar4);
void __OVBIFM __vstore_pred(__bool8,  __WR __cchar8*, __cchar8);
void __OVBIFM __vstore_pred(__bool16, __WR __cchar16*, __cchar16);
#if __C7X_VEC_SIZE_BITS__ >= 512
void __OVBIFM __vstore_pred(__bool32, __WR __cchar32*, __cchar32);
#endif

/* VSTP2W, VSTP4W, VSTP8W, VSTP16W */
void __OVBIFM __vstore_pred(__bool2,  __WR __int2*,     __int2);
void __OVBIFM __vstore_pred(__bool4,  __WR __int4*,     __int4);
void __OVBIFM __vstore_pred(__bool8,  __WR __int8*,     __int8);
#if __C7X_VEC_SIZE_BITS__ >= 512
void __OVBIFM __vstore_pred(__bool16, __WR __int16*,    __int16);
#endif

void __OVBIFM __vstore_pred(__bool2,  __WR __uint2*,    __uint2);
void __OVBIFM __vstore_pred(__bool4,  __WR __uint4*,    __uint4);
void __OVBIFM __vstore_pred(__bool8,  __WR __uint8*,    __uint8);
#if __C7X_VEC_SIZE_BITS__ >= 512
void __OVBIFM __vstore_pred(__bool16, __WR __uint16*,   __uint16);
#endif

void __OVBIFM __vstore_pred(__bool2,  __WR __float2*,   __float2);
void __OVBIFM __vstore_pred(__bool4,  __WR __float4*,   __float4);
void __OVBIFM __vstore_pred(__bool8,  __WR __float8*,   __float8);
#if __C7X_VEC_SIZE_BITS__ >= 512
void __OVBIFM __vstore_pred(__bool16, __WR __float16*,  __float16);
#endif

void __OVBIFM __vstore_pred(__bool2,  __WR __cshort2*,  __cshort2);
void __OVBIFM __vstore_pred(__bool4,  __WR __cshort4*,  __cshort4);
void __OVBIFM __vstore_pred(__bool8,  __WR __cshort8*,  __cshort8);
#if __C7X_VEC_SIZE_BITS__ >= 512
void __OVBIFM __vstore_pred(__bool16, __WR __cshort16*, __cshort16);
#endif

/* VSTP2D, VSTP4D, VSTP8D */
void __OVBIFM __vstore_pred(__bool2, __WR __long2*,   __long2);
void __OVBIFM __vstore_pred(__bool4, __WR __long4*,   __long4);
#if __C7X_VEC_SIZE_BITS__ >= 512
void __OVBIFM __vstore_pred(__bool8, __WR __long8*,   __long8);
#endif

void __OVBIFM __vstore_pred(__bool2, __WR __ulong2*,  __ulong2);
void __OVBIFM __vstore_pred(__bool4, __WR __ulong4*,  __ulong4);
#if __C7X_VEC_SIZE_BITS__ >= 512
void __OVBIFM __vstore_pred(__bool8, __WR __ulong8*,  __ulong8);
#endif

void __OVBIFM __vstore_pred(__bool2, __WR __double2*, __double2);
void __OVBIFM __vstore_pred(__bool4, __WR __double4*, __double4);
#if __C7X_VEC_SIZE_BITS__ >= 512
void __OVBIFM __vstore_pred(__bool8, __WR __double8*, __double8);
#endif

void __OVBIFM __vstore_pred(__bool2, __WR __cint2*,   __cint2);
void __OVBIFM __vstore_pred(__bool4, __WR __cint4*,   __cint4);
#if __C7X_VEC_SIZE_BITS__ >= 512
void __OVBIFM __vstore_pred(__bool8, __WR __cint8*,   __cint8);
#endif

void __OVBIFM __vstore_pred(__bool2, __WR __cfloat2*, __cfloat2);
void __OVBIFM __vstore_pred(__bool4, __WR __cfloat4*, __cfloat4);
#if __C7X_VEC_SIZE_BITS__ >= 512
void __OVBIFM __vstore_pred(__bool8, __WR __cfloat8*, __cfloat8);
#endif

/* VSTPBSVPACKL, VSTPBSVPACKH, VSTPBSVPACKHS1: PRED CORRESPONDS TO SRC DATA */
#if __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_pred_packl(__bool16,   __WR __char16*,  __short16);
void __OVBIFM __vstore_pred_packl(__bool16,   __WR __uchar16*, __ushort16);
void __OVBIFM __vstore_pred_packh(__bool16,   __WR __char16*,  __short16);
void __OVBIFM __vstore_pred_packh(__bool16,   __WR __uchar16*, __ushort16);
void __OVBIFM __vstore_pred_packhs1(__bool16, __WR __char16*,  __short16);
void __OVBIFM __vstore_pred_packhs1(__bool16, __WR __uchar16*, __ushort16);
#elif __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_pred_packl(__bool32,   __WR __char32*,  __short32);
void __OVBIFM __vstore_pred_packl(__bool32,   __WR __uchar32*, __ushort32);
void __OVBIFM __vstore_pred_packh(__bool32,   __WR __char32*,  __short32);
void __OVBIFM __vstore_pred_packh(__bool32,   __WR __uchar32*, __ushort32);
void __OVBIFM __vstore_pred_packhs1(__bool32, __WR __char32*,  __short32);
void __OVBIFM __vstore_pred_packhs1(__bool32, __WR __uchar32*, __ushort32);
#endif

/* VSTPHSVPACKL, VSTPHSVPACKH, VSTPHSVPACKHS1: PRED CORRESPONDS TO SRC DATA */
#if __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_pred_packl(__bool8,   __WR __short8*,  __int8);
void __OVBIFM __vstore_pred_packl(__bool8,   __WR __ushort8*, __uint8);
void __OVBIFM __vstore_pred_packh(__bool8,   __WR __short8*,  __int8);
void __OVBIFM __vstore_pred_packh(__bool8,   __WR __ushort8*, __uint8);
void __OVBIFM __vstore_pred_packhs1(__bool8, __WR __short8*,  __int8);
void __OVBIFM __vstore_pred_packhs1(__bool8, __WR __ushort8*, __uint8);
#elif __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_pred_packl(__bool16,   __WR __short16*,  __int16);
void __OVBIFM __vstore_pred_packl(__bool16,   __WR __ushort16*, __uint16);
void __OVBIFM __vstore_pred_packh(__bool16,   __WR __short16*,  __int16);
void __OVBIFM __vstore_pred_packh(__bool16,   __WR __ushort16*, __uint16);
void __OVBIFM __vstore_pred_packhs1(__bool16, __WR __short16*,  __int16);
void __OVBIFM __vstore_pred_packhs1(__bool16, __WR __ushort16*, __uint16);
#endif

/* VSTPWSVPACKB: PRED CORRESPONDS TO SRC DATA */
#if __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_pred_pack_byte(__bool8, __WR __char8*,  __int8);
void __OVBIFM __vstore_pred_pack_byte(__bool8, __WR __uchar8*, __uint8);
#elif __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_pred_pack_byte(__bool16, __WR __char16*,  __int16);
void __OVBIFM __vstore_pred_pack_byte(__bool16, __WR __uchar16*, __uint16);
#endif

/* VSTPWSVPACKL, VSTPWSVPACKH, VSTPWSVPACKHS1: PRED CORRESPONDS TO SRC DATA */
#if __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_pred_packl(__bool4,   __WR __int4*,  __long4);
void __OVBIFM __vstore_pred_packl(__bool4,   __WR __uint4*, __ulong4);
void __OVBIFM __vstore_pred_packh(__bool4,   __WR __int4*,  __long4);
void __OVBIFM __vstore_pred_packh(__bool4,   __WR __uint4*, __ulong4);
void __OVBIFM __vstore_pred_packhs1(__bool4, __WR __int4*,  __long4);
void __OVBIFM __vstore_pred_packhs1(__bool4, __WR __uint4*, __ulong4);
#elif __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_pred_packl(__bool8,   __WR __int8*,  __long8);
void __OVBIFM __vstore_pred_packl(__bool8,   __WR __uint8*, __ulong8);
void __OVBIFM __vstore_pred_packh(__bool8,   __WR __int8*,  __long8);
void __OVBIFM __vstore_pred_packh(__bool8,   __WR __uint8*, __ulong8);
void __OVBIFM __vstore_pred_packhs1(__bool8, __WR __int8*,  __long8);
void __OVBIFM __vstore_pred_packhs1(__bool8, __WR __uint8*, __ulong8);
#endif

/* VSTPBPACKL, VSTPBPACKH, VSTPBPACKHS1: PRED CORRESPONDS TO PACKED DATA */
#if __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_pred_packl_2src(__bool32,   __WR __char32*, __short16,  __short16);
void __OVBIFM __vstore_pred_packl_2src(__bool32,   __WR __uchar32*, __ushort16, __ushort16);
void __OVBIFM __vstore_pred_packh_2src(__bool32,   __WR __char32*, __short16,  __short16);
void __OVBIFM __vstore_pred_packh_2src(__bool32,   __WR __uchar32*, __ushort16, __ushort16);
void __OVBIFM __vstore_pred_packhs1_2src(__bool32, __WR __char32*, __short16,  __short16);
void __OVBIFM __vstore_pred_packhs1_2src(__bool32, __WR __uchar32*, __ushort16, __ushort16);
#elif __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_pred_packl_2src(__bool64,   __WR __char64*, __short32,  __short32);
void __OVBIFM __vstore_pred_packl_2src(__bool64,   __WR __uchar64*, __ushort32, __ushort32);
void __OVBIFM __vstore_pred_packh_2src(__bool64,   __WR __char64*, __short32,  __short32);
void __OVBIFM __vstore_pred_packh_2src(__bool64,   __WR __uchar64*, __ushort32, __ushort32);
void __OVBIFM __vstore_pred_packhs1_2src(__bool64, __WR __char64*, __short32,  __short32);
void __OVBIFM __vstore_pred_packhs1_2src(__bool64, __WR __uchar64*, __ushort32, __ushort32);
#endif

/* VSTPHPACKL, VSTPHPACKH, VSTPHPACKHS1: PRED CORRESPONDS TO PACKED DATA */
#if __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_pred_packl_2src(__bool16,   __WR __short16*, __int8,   __int8);
void __OVBIFM __vstore_pred_packl_2src(__bool16,   __WR __ushort16*, __uint8, __uint8);
void __OVBIFM __vstore_pred_packh_2src(__bool16,   __WR __short16*, __int8,   __int8);
void __OVBIFM __vstore_pred_packh_2src(__bool16,   __WR __ushort16*, __uint8, __uint8);
void __OVBIFM __vstore_pred_packhs1_2src(__bool16, __WR __short16*, __int8,   __int8);
void __OVBIFM __vstore_pred_packhs1_2src(__bool16, __WR __ushort16*, __uint8, __uint8);
#elif __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_pred_packl_2src(__bool32,   __WR __short32*, __int16,   __int16);
void __OVBIFM __vstore_pred_packl_2src(__bool32,   __WR __ushort32*, __uint16, __uint16);
void __OVBIFM __vstore_pred_packh_2src(__bool32,   __WR __short32*, __int16,   __int16);
void __OVBIFM __vstore_pred_packh_2src(__bool32,   __WR __ushort32*, __uint16, __uint16);
void __OVBIFM __vstore_pred_packhs1_2src(__bool32, __WR __short32*, __int16,   __int16);
void __OVBIFM __vstore_pred_packhs1_2src(__bool32, __WR __ushort32*, __uint16, __uint16);
#endif

/* VSTPWPACKB: PRED CORRESPONDS TO PACKED DATA */
#if __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_pred_pack_byte_2src(__bool16, __WR __char16*, __int8,  __int8);
void __OVBIFM __vstore_pred_pack_byte_2src(__bool16, __WR __uchar16*, __uint8, __uint8);
#elif __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_pred_pack_byte_2src(__bool32, __WR __char32*, __int16,  __int16);
void __OVBIFM __vstore_pred_pack_byte_2src(__bool32, __WR __uchar32*, __uint16, __uint16);
#endif

/* VSTPWPACKL, VSTPWPACKH, VSTPWPACKHS1: PRED CORRESPONDS TO PACKED DATA */
#if __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_pred_packl_2src(__bool8,   __WR __int8*, __long4,  __long4);
void __OVBIFM __vstore_pred_packl_2src(__bool8,   __WR __uint8*, __ulong4, __ulong4);
void __OVBIFM __vstore_pred_packh_2src(__bool8,   __WR __int8*, __long4,   __long4);
void __OVBIFM __vstore_pred_packh_2src(__bool8,   __WR __uint8*, __ulong4, __ulong4);
void __OVBIFM __vstore_pred_packhs1_2src(__bool8, __WR __int8*, __long4,   __long4);
void __OVBIFM __vstore_pred_packhs1_2src(__bool8, __WR __uint8*, __ulong4, __ulong4);
#elif __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_pred_packl_2src(__bool16,   __WR __int16*, __long8,  __long8);
void __OVBIFM __vstore_pred_packl_2src(__bool16,   __WR __uint16*, __ulong8, __ulong8);
void __OVBIFM __vstore_pred_packh_2src(__bool16,   __WR __int16*, __long8,   __long8);
void __OVBIFM __vstore_pred_packh_2src(__bool16,   __WR __uint16*, __ulong8, __ulong8);
void __OVBIFM __vstore_pred_packhs1_2src(__bool16, __WR __int16*, __long8,   __long8);
void __OVBIFM __vstore_pred_packhs1_2src(__bool16, __WR __uint16*, __ulong8, __ulong8);
#endif

/* VSTPDPACKL, VSTPDPACKH, VSTPDPACKHS1: PRED CORRESPONDS TO PACKED DATA */
#if __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_pred_packl_long_2src(__bool4,   __WR __long4*, __long4, __long4);
void __OVBIFM __vstore_pred_packl_long_2src(__bool4,   __WR __ulong4*, __ulong4,__ulong4);
void __OVBIFM __vstore_pred_packh_long_2src(__bool4,   __WR __long4*, __long4, __long4);
void __OVBIFM __vstore_pred_packh_long_2src(__bool4,   __WR __ulong4*, __ulong4,__ulong4);
void __OVBIFM __vstore_pred_packhs1_long_2src(__bool4, __WR __long4*, __long4, __long4);
void __OVBIFM __vstore_pred_packhs1_long_2src(__bool4, __WR __ulong4*, __ulong4,__ulong4);
#elif __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_pred_packl_long_2src(__bool8,   __WR __long8*, __long8, __long8);
void __OVBIFM __vstore_pred_packl_long_2src(__bool8,   __WR __ulong8*, __ulong8,__ulong8);
void __OVBIFM __vstore_pred_packh_long_2src(__bool8,   __WR __long8*, __long8, __long8);
void __OVBIFM __vstore_pred_packh_long_2src(__bool8,   __WR __ulong8*, __ulong8,__ulong8);
void __OVBIFM __vstore_pred_packhs1_long_2src(__bool8, __WR __long8*, __long8, __long8);
void __OVBIFM __vstore_pred_packhs1_long_2src(__bool8, __WR __ulong8*, __ulong8,__ulong8);
#endif

/* VSTPBITRWH */
#if __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_pred_reverse_bit(__bool16, __WR __cshort16*, __cshort16);
#elif __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_pred_reverse_bit(__bool8, __WR __cshort8*, __cshort8);
#endif

/* VSTPBITRDW */
#if __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_pred_reverse_bit(__bool8, __WR __cint8*,   __cint8);
void __OVBIFM __vstore_pred_reverse_bit(__bool8, __WR __cfloat8*, __cfloat8);
#elif __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_pred_reverse_bit(__bool4, __WR __cint4*,   __cint4);
void __OVBIFM __vstore_pred_reverse_bit(__bool4, __WR __cfloat4*, __cfloat4);
#endif

/* STKW, ST0KW */
void __BIFM __vstore_const       (__WR __uint*,   __CST_RANGE __uint);

/* VSTK2W, VST0K2W */
void __BIFM __vstore_const_uint2 (__WR __uint2*,  __CST_RANGE __uint);

/* VSTK4W, VST0K4W */
void __BIFM __vstore_const_uint4 (__WR __uint4*,  __CST_RANGE __uint);

/* VSTK8W, VST0K8W */
void __BIFM __vstore_const_uint8 (__WR __uint8*,  __CST_RANGE __uint);

/* VSTK16W, VST0K16W */
#if __C7X_VEC_SIZE_BITS__ >= 512
void __BIFM __vstore_const_uint16(__WR __uint16*, __CST_RANGE __uint);
#endif

/* VSTBSVPACKL, VSTBSVPACKH, VSTBSVPACKHS1 */
#if __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_packl(__WR __char16*, __short16);
void __OVBIFM __vstore_packl(__WR __uchar16*, __ushort16);
void __OVBIFM __vstore_packh(__WR __char16*, __short16);
void __OVBIFM __vstore_packh(__WR __uchar16*, __ushort16);
void __OVBIFM __vstore_packhs1(__WR __char16*, __short16);
void __OVBIFM __vstore_packhs1(__WR __uchar16*, __ushort16);
#elif __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_packl(__WR __char32*, __short32);
void __OVBIFM __vstore_packl(__WR __uchar32*, __ushort32);
void __OVBIFM __vstore_packh(__WR __char32*, __short32);
void __OVBIFM __vstore_packh(__WR __uchar32*, __ushort32);
void __OVBIFM __vstore_packhs1(__WR __char32*, __short32);
void __OVBIFM __vstore_packhs1(__WR __uchar32*, __ushort32);
#endif

/* VSTHSVPACKL, VSTHSVPACKH, VSTHSVPACKHS1 */
#if __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_packl(__WR __short8*, __int8);
void __OVBIFM __vstore_packl(__WR __ushort8*, __uint8);
void __OVBIFM __vstore_packh(__WR __short8*, __int8);
void __OVBIFM __vstore_packh(__WR __ushort8*, __uint8);
void __OVBIFM __vstore_packhs1(__WR __short8*, __int8);
void __OVBIFM __vstore_packhs1(__WR __ushort8*, __uint8);
#elif __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_packl(__WR __short16*, __int16);
void __OVBIFM __vstore_packl(__WR __ushort16*, __uint16);
void __OVBIFM __vstore_packh(__WR __short16*, __int16);
void __OVBIFM __vstore_packh(__WR __ushort16*, __uint16);
void __OVBIFM __vstore_packhs1(__WR __short16*, __int16);
void __OVBIFM __vstore_packhs1(__WR __ushort16*, __uint16);
#endif

/* VSTWSVPACKB */
#if __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_pack_byte(__WR __char8*, __int8);
void __OVBIFM __vstore_pack_byte(__WR __uchar8*, __uint8);
#elif __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_pack_byte(__WR __char16*, __int16);
void __OVBIFM __vstore_pack_byte(__WR __uchar16*, __uint16);
#endif

/* VSTWSVPACKL, VSTWSVPACKH, VSTWSVPACKHS1 */
#if __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_packl(__WR __int4*, __long4);
void __OVBIFM __vstore_packl(__WR __uint4*, __ulong4);
void __OVBIFM __vstore_packh(__WR __int4*, __long4);
void __OVBIFM __vstore_packh(__WR __uint4*, __ulong4);
void __OVBIFM __vstore_packhs1(__WR __int4*, __long4);
void __OVBIFM __vstore_packhs1(__WR __uint4*, __ulong4);
#elif __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_packl(__WR __int8*, __long8);
void __OVBIFM __vstore_packl(__WR __uint8*, __ulong8);
void __OVBIFM __vstore_packh(__WR __int8*, __long8);
void __OVBIFM __vstore_packh(__WR __uint8*, __ulong8);
void __OVBIFM __vstore_packhs1(__WR __int8*, __long8);
void __OVBIFM __vstore_packhs1(__WR __uint8*, __ulong8);
#endif

/* VSTDSVPACKL, VSTDSVPACKH, VSTDSVPACKHS1 */
#if __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_packl(__WR __long2*, __long4);
void __OVBIFM __vstore_packl(__WR __ulong2*, __ulong4);
void __OVBIFM __vstore_packh(__WR __long2*, __long4);
void __OVBIFM __vstore_packh(__WR __ulong2*, __ulong4);
void __OVBIFM __vstore_packhs1(__WR __long2*, __long4);
void __OVBIFM __vstore_packhs1(__WR __ulong2*, __ulong4);
#elif __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_packl(__WR __long4*, __long8);
void __OVBIFM __vstore_packl(__WR __ulong4*, __ulong8);
void __OVBIFM __vstore_packh(__WR __long4*, __long8);
void __OVBIFM __vstore_packh(__WR __ulong4*, __ulong8);
void __OVBIFM __vstore_packhs1(__WR __long4*, __long8);
void __OVBIFM __vstore_packhs1(__WR __ulong4*, __ulong8);
#endif

/* VSTBPACKL, VSTBPACKH, VSTBPACKHS1 */
#if __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_packl_2src(__WR __char32*, __short16, __short16);
void __OVBIFM __vstore_packl_2src(__WR __uchar32*, __ushort16, __ushort16);
void __OVBIFM __vstore_packh_2src(__WR __char32*, __short16, __short16);
void __OVBIFM __vstore_packh_2src(__WR __uchar32*, __ushort16, __ushort16);
void __OVBIFM __vstore_packhs1_2src(__WR __char32*, __short16, __short16);
void __OVBIFM __vstore_packhs1_2src(__WR __uchar32*, __ushort16, __ushort16);
#elif __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_packl_2src(__WR __char64*, __short32, __short32);
void __OVBIFM __vstore_packl_2src(__WR __uchar64*, __ushort32, __ushort32);
void __OVBIFM __vstore_packh_2src(__WR __char64*, __short32, __short32);
void __OVBIFM __vstore_packh_2src(__WR __uchar64*, __ushort32, __ushort32);
void __OVBIFM __vstore_packhs1_2src(__WR __char64*, __short32, __short32);
void __OVBIFM __vstore_packhs1_2src(__WR __uchar64*, __ushort32, __ushort32);
#endif

/* VSTHPACKL, VSTHPACKH, VSTHPACKHS1 */
#if __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_packl_2src(__WR __short16*, __int8, __int8);
void __OVBIFM __vstore_packl_2src(__WR __ushort16*, __uint8, __uint8);
void __OVBIFM __vstore_packh_2src(__WR __short16*, __int8, __int8);
void __OVBIFM __vstore_packh_2src(__WR __ushort16*, __uint8, __uint8);
void __OVBIFM __vstore_packhs1_2src(__WR __short16*, __int8, __int8);
void __OVBIFM __vstore_packhs1_2src(__WR __ushort16*, __uint8, __uint8);
#elif __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_packl_2src(__WR __short32*, __int16, __int16);
void __OVBIFM __vstore_packl_2src(__WR __ushort32*, __uint16, __uint16);
void __OVBIFM __vstore_packh_2src(__WR __short32*, __int16, __int16);
void __OVBIFM __vstore_packh_2src(__WR __ushort32*, __uint16, __uint16);
void __OVBIFM __vstore_packhs1_2src(__WR __short32*, __int16, __int16);
void __OVBIFM __vstore_packhs1_2src(__WR __ushort32*, __uint16, __uint16);
#endif

/* VSTWPACKB */
#if __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_pack_byte_2src(__WR __char16*, __int8, __int8);
void __OVBIFM __vstore_pack_byte_2src(__WR __uchar16*, __uint8, __uint8);
#elif __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_pack_byte_2src(__WR __char32*, __int16, __int16);
void __OVBIFM __vstore_pack_byte_2src(__WR __uchar32*, __uint16, __uint16);
#endif

/* VSTWPACKL, VSTWPACKH, VSTWPACKHS1 */
#if __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_packl_2src(__WR __int8*, __long4, __long4);
void __OVBIFM __vstore_packl_2src(__WR __uint8*, __ulong4, __ulong4);
void __OVBIFM __vstore_packh_2src(__WR __int8*, __long4, __long4);
void __OVBIFM __vstore_packh_2src(__WR __uint8*, __ulong4, __ulong4);
void __OVBIFM __vstore_packhs1_2src(__WR __int8*, __long4, __long4);
void __OVBIFM __vstore_packhs1_2src(__WR __uint8*, __ulong4, __ulong4);
#elif __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_packl_2src(__WR __int16*, __long8, __long8);
void __OVBIFM __vstore_packl_2src(__WR __uint16*, __ulong8, __ulong8);
void __OVBIFM __vstore_packh_2src(__WR __int16*, __long8, __long8);
void __OVBIFM __vstore_packh_2src(__WR __uint16*, __ulong8, __ulong8);
void __OVBIFM __vstore_packhs1_2src(__WR __int16*, __long8, __long8);
void __OVBIFM __vstore_packhs1_2src(__WR __uint16*, __ulong8, __ulong8);
#endif

/* VSTDPACKL, VSTDPACKH, VSTDPACKHS1 */
#if __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_packl_2src(__WR __long4*, __long4, __long4);
void __OVBIFM __vstore_packl_2src(__WR __ulong4*, __ulong4, __ulong4);
void __OVBIFM __vstore_packh_2src(__WR __long4*, __long4, __long4);
void __OVBIFM __vstore_packh_2src(__WR __ulong4*, __ulong4, __ulong4);
void __OVBIFM __vstore_packhs1_2src(__WR __long4*, __long4, __long4);
void __OVBIFM __vstore_packhs1_2src(__WR __ulong4*, __ulong4, __ulong4);
#elif __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_packl_2src(__WR __long8*, __long8, __long8);
void __OVBIFM __vstore_packl_2src(__WR __ulong8*, __ulong8, __ulong8);
void __OVBIFM __vstore_packh_2src(__WR __long8*, __long8, __long8);
void __OVBIFM __vstore_packh_2src(__WR __ulong8*, __ulong8, __ulong8);
void __OVBIFM __vstore_packhs1_2src(__WR __long8*, __long8, __long8);
void __OVBIFM __vstore_packhs1_2src(__WR __ulong8*, __ulong8, __ulong8);
#endif

/* VSTBITRWH */
#if __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_reverse_bit(__WR __short32*, __short32);
void __OVBIFM __vstore_reverse_bit(__WR __ushort32*, __ushort32);
void __OVBIFM __vstore_reverse_bit(__WR __cshort16*, __cshort16);
#elif __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_reverse_bit(__WR __short16*, __short16);
void __OVBIFM __vstore_reverse_bit(__WR __ushort16*, __ushort16);
void __OVBIFM __vstore_reverse_bit(__WR __cshort8*, __cshort8);
#endif

/* VSTBITRDW */
#if __C7X_VEC_SIZE_BITS__ == 512
void __OVBIFM __vstore_reverse_bit(__WR __int16*, __int16);
void __OVBIFM __vstore_reverse_bit(__WR __uint16*, __uint16);
void __OVBIFM __vstore_reverse_bit(__WR __float16*, __float16);
void __OVBIFM __vstore_reverse_bit(__WR __cint8*, __cint8);
void __OVBIFM __vstore_reverse_bit(__WR __cfloat8*, __cfloat8);
#elif __C7X_VEC_SIZE_BITS__ == 256
void __OVBIFM __vstore_reverse_bit(__WR __int8*, __int8);
void __OVBIFM __vstore_reverse_bit(__WR __uint8*, __uint8);
void __OVBIFM __vstore_reverse_bit(__WR __float8*, __float8);
void __OVBIFM __vstore_reverse_bit(__WR __cint4*, __cint4);
void __OVBIFM __vstore_reverse_bit(__WR __cfloat4*, __cfloat4);
#endif

/* ASW */
int      __OVBIFM __atomic_swap(__WR int*, int, int);

/* ASD */
long     __OVBIFM __atomic_swap(__WR long*, long, long);

/* CASW */
int      __OVBIFM __atomic_compare_swap(__WR int*, int, int);

/* CASD */
long     __OVBIFM __atomic_compare_swap(__WR long*, long, long);

/* PFS */
void __BIFM __prefetch(void*, __CST(0, 31) unsigned);

/* MTAG argument */
typedef enum __attribute__((__packed__))
{
    __MTAG_COLOR0        = 0x0,
    __MTAG_COLOR1        = 0x1,
    __MTAG_SWITCH_COLORS = 0x1f
} __MTAG_COLOR;

/* MTAG */
void __BIFM __mtag(__CST(0, 31) __MTAG_COLOR);

/* MFENCE/MFENCEST argument */
typedef enum __attribute__((__packed__))
{
    __MFENCE_COLOR0     = 0x0,
    __MFENCE_COLOR1     = 0x1,
    __MFENCE_ALL_COLORS = 0x1f
} __MFENCE_COLOR;

/* MFENCE */
void __BIFM __memory_fence(__CST(0, 31) __MFENCE_COLOR);

/* MFENCEST */
void __BIFM __memory_fence_store(__CST(0, 31) __MFENCE_COLOR);

/*-----------------------------------------------------------------------------
* Extract and Duplicate
*-----------------------------------------------------------------------------
* VGETDUPB (C syntax -- using intrinsic or cast):
*         char64 src, dst;
*         dst = __duplicate(src.s[10]);  OR
*         dst = char64(src.s[10]);
*
* VGETDUPH (C syntax -- using intrinsic or cast):
*         short32 src, dst;
*         dst = __duplicate(src.s[10]);   OR
*         dst = short32(src.s[10]);
*
* VGETDUPW (C syntax -- using intrinsic or cast):
*         int16 src, dst;
*         dst = __duplicate(src.s[7]);   OR
*         dst = int16(src.s[7]);
*
* VGETDUPD (C syntax -- using intrinsic or cast):
*         long8 src, dst;
*         dst = __duplicate(src.s[7]);   OR
*         dst = long8(src.s[7]);
*----------------------------------------------------------------------------*/

/******************************************************************************/
/* The following is a full list of intrinsics and operations available using  */
/* vector types. In addition, each example will also show the C7000           */
/* instruction to which the intrinsic will map.                               */
/*                                                                            */
/* In cases of vectors, constants must be converted to the proper vector type */
/* for the intrinsic to match properly.                                       */
/* E.g: For a vector addition of char8 a by constant 4, the code should be    */
/*      written: a + char8(4)                                                 */
/*                                                                            */
/* NOTE:                                                                      */
/*                                                                            */
/* There are a handful of complicated instructions that cannot be accessed    */
/* using the below vector intrinsics or C idioms. Please refer to the list of */
/* direct-mapped intrinsics listed in c7x_direct.h for the following          */
/* instructions:                                                              */
/*                                                                            */
/*  'EXTV'                                                                    */
/*  'EXTUV'                                                                   */
/*  'REPLACEV'                                                                */
/*  'VFIR8HD'                                                                 */
/*  'VFIR8HW'                                                                 */
/*  'VFIR8SUHD'                                                               */
/*  'VFIR8SUHW'                                                               */
/*  'VFIR8UHD'                                                                */
/*  'VFIR8UHW'                                                                */
/*  'VMATMPYHD'                                                               */
/*  'VMATMPYSP'                                                               */
/*  'VMATMPYSUHD'                                                             */
/*  'VMATMPYSUHW'                                                             */
/*  'VMATMPYUHD'                                                              */
/*  'VMATMPYUHW'                                                              */
/*  'VMATMPYUSHD'                                                             */
/*  'VSAD16OU16H16W'                                                          */
/*  'VSAD16OU8H16W'                                                           */
/*  'VSAD8OU16B32H'                                                           */
/*  'VSADM16OU16H16W'                                                         */
/*  'VSADM16OU8H16W'                                                          */
/*  'VSADM8OU16B32H'                                                          */
/*  'VDSAD16OU8H8W'                                                           */
/*  'VDSAD8OU16B16H'                                                          */
/*  'VDSADM16OU8H8W'                                                          */
/*  'VDSADM8OU16B16H'                                                         */
/*  'VCDOTPM2OPN16B32H'                                                       */
/*  'VCDOTPM2OPN1H32H'                                                        */
/*  'VCDOTPM2OPN8H16W'                                                        */
/*  'VCDOTPM2OPN8W16W'                                                        */
/*  'VCDOTPM32OPN16B32H'                                                      */
/*                                                                            */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* ID: __gather_set_bits                                                      */
/*----------------------------------------------------------------------------*/
/* VGATHERB */
__char2 __OVBIF __gather_set_bits(__bool2, __char2);
__char3 __OVBIF __gather_set_bits(__bool3, __char3);
__char4 __OVBIF __gather_set_bits(__bool4, __char4);
__char8 __OVBIF __gather_set_bits(__bool8, __char8);
__char16 __OVBIF __gather_set_bits(__bool16, __char16);
__char32 __OVBIF __gather_set_bits(__bool32, __char32);
#if __C7X_VEC_SIZE_BITS__ >= 512
__char64 __OVBIF __gather_set_bits(__bool64, __char64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __gather_unset_bits                                                    */
/*----------------------------------------------------------------------------*/
/* VGATHERNB */
__char2 __OVBIF __gather_unset_bits(__bool2, __char2);
__char3 __OVBIF __gather_unset_bits(__bool3, __char3);
__char4 __OVBIF __gather_unset_bits(__bool4, __char4);
__char8 __OVBIF __gather_unset_bits(__bool8, __char8);
__char16 __OVBIF __gather_unset_bits(__bool16, __char16);
__char32 __OVBIF __gather_unset_bits(__bool32, __char32);
#if __C7X_VEC_SIZE_BITS__ >= 512
__char64 __OVBIF __gather_unset_bits(__bool64, __char64);
#endif

/******************************************************************************/
/* __SE_REG and __SE_REG_PAIR Streaming Engine Operands                       */
/*                                                                            */
/* Some intrinsics, such as __matmpy() and __matmpy_u2s() below, take a       */
/* streaming engine operand, which is an enumeration with values representing */
/* which streaming engine to use as well as whether that streaming engine     */
/* advances. All other values are invalid and will produce an error.          */
/******************************************************************************/
typedef enum __attribute__((__packed__))
{
    __SE_REG_0     = 0,
    __SE_REG_0_ADV = 1,
    __SE_REG_1     = 2,
    __SE_REG_1_ADV = 3,
    __SE_REG_LAST  = 3 /* Don't use directly. */
} __SE_REG;

typedef enum __attribute__((__packed__))
{
    __SE_REG_PAIR_0     = 0,
    __SE_REG_PAIR_0_ADV = 1,
    __SE_REG_PAIR_LAST  = 1 /* Don't use directly. */
} __SE_REG_PAIR;

/*----------------------------------------------------------------------------*/
/* ID: __matmpy                                                               */
/*----------------------------------------------------------------------------*/
/* VMATMPYHW */
/*
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __matmpy(__SE_REG, __SE_REG);
#endif
*/

/*----------------------------------------------------------------------------*/
/* ID: __matmpy_u2s                                                           */
/*----------------------------------------------------------------------------*/
/* VMATMPYUSHW */
/*
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __matmpy_u2s(__SE_REG, __SE_REG);
#endif
*/

/*----------------------------------------------------------------------------*/
/* ID: __popcount_gather                                                      */
/*----------------------------------------------------------------------------*/
/* PCNTGATHERB */
/*
void __popcount_gather(bool2, uint&, bool2&);
void __popcount_gather(bool3, uint&, bool3&);
void __popcount_gather(bool4, uint&, bool4&);
void __popcount_gather(bool8, uint&, bool8&);
void __popcount_gather(bool16, uint&, bool16&);
void __popcount_gather(bool32, uint&, bool32&);
#if __C7X_VEC_SIZE_BITS__ >= 512
void __popcount_gather(bool64, uint&, bool64&);
#endif
*/

/*----------------------------------------------------------------------------*/
/* ID: __rightmost_bit_detect                                                 */
/*----------------------------------------------------------------------------*/
/* PRMBDB */
__uint __OVBIF __rightmost_bit_detect(__bool2);
__uint __OVBIF __rightmost_bit_detect(__bool3);
__uint __OVBIF __rightmost_bit_detect(__bool4);
__uint __OVBIF __rightmost_bit_detect(__bool8);
__uint __OVBIF __rightmost_bit_detect(__bool16);
__uint __OVBIF __rightmost_bit_detect(__bool32);
#if __C7X_VEC_SIZE_BITS__ >= 512
__uint __OVBIF __rightmost_bit_detect(__bool64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __scatter_set_bits                                                     */
/*----------------------------------------------------------------------------*/
/* VSCATTERB */
__char2 __OVBIF __scatter_set_bits(__bool2, __char2);
__char3 __OVBIF __scatter_set_bits(__bool3, __char3);
__char4 __OVBIF __scatter_set_bits(__bool4, __char4);
__char8 __OVBIF __scatter_set_bits(__bool8, __char8);
__char16 __OVBIF __scatter_set_bits(__bool16, __char16);
__char32 __OVBIF __scatter_set_bits(__bool32, __char32);
#if __C7X_VEC_SIZE_BITS__ >= 512
__char64 __OVBIF __scatter_set_bits(__bool64, __char64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __scatter_unset_bits                                                   */
/*----------------------------------------------------------------------------*/
/* VSCATTERNB */
__char2 __OVBIF __scatter_unset_bits(__bool2, __char2);
__char3 __OVBIF __scatter_unset_bits(__bool3, __char3);
__char4 __OVBIF __scatter_unset_bits(__bool4, __char4);
__char8 __OVBIF __scatter_unset_bits(__bool8, __char8);
__char16 __OVBIF __scatter_unset_bits(__bool16, __char16);
__char32 __OVBIF __scatter_unset_bits(__bool32, __char32);
#if __C7X_VEC_SIZE_BITS__ >= 512
__char64 __OVBIF __scatter_unset_bits(__bool64, __char64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: SCONV                                                                  */
/*----------------------------------------------------------------------------*/
/*

VBUNPKD
long = __convert_long(signed char);
long2 = __convert_long2(char2);
long3 = __convert_long3(char3);
long4 = __convert_long4(char4);
long8 = __convert_long8(char8);
clong = __convert_clong(cchar);
clong2 = __convert_clong2(cchar2);
clong4 = __convert_clong4(cchar4);

VBUNPKDU
ulong = __convert_ulong(uchar);
ulong2 = __convert_ulong2(uchar2);
ulong3 = __convert_ulong3(uchar3);
ulong4 = __convert_ulong4(uchar4);
ulong8 = __convert_ulong8(uchar8);
long = __convert_long(uchar);
long2 = __convert_long2(uchar2);
long3 = __convert_long3(uchar3);
long4 = __convert_long4(uchar4);
long8 = __convert_long8(uchar8);

VBUNPKH
short = __convert_short(signed char);
short2 = __convert_short2(char2);
short3 = __convert_short3(char3);
short4 = __convert_short4(char4);
short8 = __convert_short8(char8);
short16 = __convert_short16(char16);
short32 = __convert_short32(char32);
cshort = __convert_cshort(cchar);
cshort2 = __convert_cshort2(cchar2);
cshort4 = __convert_cshort4(cchar4);
cshort8 = __convert_cshort8(cchar8);
cshort16 = __convert_cshort16(cchar16);

VBUNPKHU
ushort = __convert_ushort(uchar);
ushort2 = __convert_ushort2(uchar2);
ushort3 = __convert_ushort3(uchar3);
ushort4 = __convert_ushort4(uchar4);
ushort8 = __convert_ushort8(uchar8);
ushort16 = __convert_ushort16(uchar16);
ushort32 = __convert_ushort32(uchar32);
short = __convert_short(uchar);
short2 = __convert_short2(uchar2);
short3 = __convert_short3(uchar3);
short4 = __convert_short4(uchar4);
short8 = __convert_short8(uchar8);
short16 = __convert_short16(uchar16);
short32 = __convert_short32(uchar32);

VBUNPKW
int = __convert_int(signed char);
int2 = __convert_int2(char2);
int3 = __convert_int3(char3);
int4 = __convert_int4(char4);
int8 = __convert_int8(char8);
int16 = __convert_int16(char16);
cint = __convert_cint(cchar);
cint2 = __convert_cint2(cchar2);
cint4 = __convert_cint4(cchar4);
cint8 = __convert_cint8(cchar8);

VBUNPKWU
uint = __convert_uint(uchar);
uint2 = __convert_uint2(uchar2);
uint3 = __convert_uint3(uchar3);
uint4 = __convert_uint4(uchar4);
uint8 = __convert_uint8(uchar8);
uint16 = __convert_uint16(uchar16);
int = __convert_int(uchar);
int2 = __convert_int2(uchar2);
int3 = __convert_int3(uchar3);
int4 = __convert_int4(uchar4);
int8 = __convert_int8(uchar8);
int16 = __convert_int16(uchar16);

VHUNPKD
long = __convert_long(short);
long2 = __convert_long2(short2);
long3 = __convert_long3(short3);
long4 = __convert_long4(short4);
long8 = __convert_long8(short8);
clong = __convert_clong(cshort);
clong2 = __convert_clong2(cshort2);
clong4 = __convert_clong4(cshort4);

VHUNPKDU
ulong = __convert_ulong(ushort);
ulong2 = __convert_ulong2(ushort2);
ulong3 = __convert_ulong3(ushort3);
ulong4 = __convert_ulong4(ushort4);
ulong8 = __convert_ulong8(ushort8);
long = __convert_long(ushort);
long2 = __convert_long2(ushort2);
long3 = __convert_long3(ushort3);
long4 = __convert_long4(ushort4);
long8 = __convert_long8(ushort8);

VHUNPKW
int = __convert_int(short);
int2 = __convert_int2(short2);
int3 = __convert_int3(short3);
int4 = __convert_int4(short4);
int8 = __convert_int8(short8);
int16 = __convert_int16(short16);
cint = __convert_cint(cshort);
cint2 = __convert_cint2(cshort2);
cint4 = __convert_cint4(cshort4);
cint8 = __convert_cint8(cshort8);

VHUNPKWU
uint = __convert_uint(ushort);
uint2 = __convert_uint2(ushort2);
uint3 = __convert_uint3(ushort3);
uint4 = __convert_uint4(ushort4);
uint8 = __convert_uint8(ushort8);
uint16 = __convert_uint16(ushort16);
int = __convert_int(ushort);
int2 = __convert_int2(ushort2);
int3 = __convert_int3(ushort3);
int4 = __convert_int4(ushort4);
int8 = __convert_int8(ushort8);
int16 = __convert_int16(ushort16);

VINTSP
float = __convert_float(int);
float2 = __convert_float2(int2);
float3 = __convert_float3(int3);
float4 = __convert_float4(int4);
float8 = __convert_float8(int8);
float16 = __convert_float16(int16);

VINTSPU
float = __convert_float(uint);
float2 = __convert_float2(uint2);
float3 = __convert_float3(uint3);
float4 = __convert_float4(uint4);
float8 = __convert_float8(uint8);
float16 = __convert_float16(uint16);

VSPTRUNC
int = __convert_int(float);
int2 = __convert_int2(float2);
int3 = __convert_int3(float3);
int4 = __convert_int4(float4);
int8 = __convert_int8(float8);
int16 = __convert_int16(float16);

VWUNPKD
long = __convert_long(int);
long2 = __convert_long2(int2);
long3 = __convert_long3(int3);
long4 = __convert_long4(int4);
long8 = __convert_long8(int8);
clong = __convert_clong(cint);
clong2 = __convert_clong2(cint2);
clong4 = __convert_clong4(cint4);

VWUNPKDU
ulong = __convert_ulong(uint);
ulong2 = __convert_ulong2(uint2);
ulong3 = __convert_ulong3(uint3);
ulong4 = __convert_ulong4(uint4);
ulong8 = __convert_ulong8(uint8);
long = __convert_long(uint);
long2 = __convert_long2(uint2);
long3 = __convert_long3(uint3);
long4 = __convert_long4(uint4);
long8 = __convert_long8(uint8);

*/

/*----------------------------------------------------------------------------*/
/* ID: __shuffle (Convenience form of __shuffle_stride2_low_low)              */
/*----------------------------------------------------------------------------*/
/* VSHFL2DLL */
__ulong2 __OVBIF __shuffle(__ulong, __ulong);
__long2 __OVBIF __shuffle(long, long);
__double2 __OVBIF __shuffle(double, double);
__cint2 __OVBIF __shuffle(__cint, __cint);
__cfloat2 __OVBIF __shuffle(__cfloat, __cfloat);
__ulong4 __OVBIF __shuffle(__ulong2, __ulong2);
__long4 __OVBIF __shuffle(__long2, __long2);
__double4 __OVBIF __shuffle(__double2, __double2);
__cint4 __OVBIF __shuffle(__cint2, __cint2);
__cfloat4 __OVBIF __shuffle(__cfloat2, __cfloat2);
#if __C7X_VEC_SIZE_BITS__ >= 512
__ulong8 __OVBIF __shuffle(__ulong4, __ulong4);
__long8 __OVBIF __shuffle(__long4, __long4);
__double8 __OVBIF __shuffle(__double4, __double4);
__cint8 __OVBIF __shuffle(__cint4, __cint4);
__cfloat8 __OVBIF __shuffle(__cfloat4, __cfloat4);
#endif

/* VSHFL2HLL */
__ushort2 __OVBIF __shuffle(__ushort, __ushort);
__ushort4 __OVBIF __shuffle(__ushort2, __ushort2);
__ushort8 __OVBIF __shuffle(__ushort4, __ushort4);
__short2 __OVBIF __shuffle(short, short);
__short4 __OVBIF __shuffle(__short2, __short2);
__short8 __OVBIF __shuffle(__short4, __short4);
__cchar2 __OVBIF __shuffle(__cchar, __cchar);
__cchar4 __OVBIF __shuffle(__cchar2, __cchar2);
__cchar8 __OVBIF __shuffle(__cchar4, __cchar4);
__ushort16 __OVBIF __shuffle(__ushort8, __ushort8);
__short16 __OVBIF __shuffle(__short8, __short8);
__cchar16 __OVBIF __shuffle(__cchar8, __cchar8);
#if __C7X_VEC_SIZE_BITS__ >= 512
__ushort32 __OVBIF __shuffle(__ushort16, __ushort16);
__short32 __OVBIF __shuffle(__short16, __short16);
__cchar32 __OVBIF __shuffle(__cchar16, __cchar16);
#endif

/* VSHFL2WLL */
__uint2 __OVBIF __shuffle(__uint, __uint);
__uint4 __OVBIF __shuffle(__uint2, __uint2);
__int2 __OVBIF __shuffle(int, int);
__int4 __OVBIF __shuffle(__int2, __int2);
__float2 __OVBIF __shuffle(float, float);
__float4 __OVBIF __shuffle(__float2, __float2);
__cshort2 __OVBIF __shuffle(__cshort, __cshort);
__cshort4 __OVBIF __shuffle(__cshort2, __cshort2);
__uint8 __OVBIF __shuffle(__uint4, __uint4);
__int8 __OVBIF __shuffle(__int4, __int4);
__float8 __OVBIF __shuffle(__float4, __float4);
__cshort8 __OVBIF __shuffle(__cshort4, __cshort4);
#if __C7X_VEC_SIZE_BITS__ >= 512
__uint16 __OVBIF __shuffle(__uint8, __uint8);
__int16 __OVBIF __shuffle(__int8, __int8);
__float16 __OVBIF __shuffle(__float8, __float8);
__cshort16 __OVBIF __shuffle(__cshort8, __cshort8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __popcount                                                             */
/*----------------------------------------------------------------------------*/
/* PBITCNTB */
__uint __OVBIF __popcount(__bool2);
__uint __OVBIF __popcount(__bool3);
__uint __OVBIF __popcount(__bool4);
__uint __OVBIF __popcount(__bool8);
__uint __OVBIF __popcount(__bool16);
__uint __OVBIF __popcount(__bool32);
#if __C7X_VEC_SIZE_BITS__ >= 512
__uint __OVBIF __popcount(__bool64);
#endif

/* AUTOGEN MARKER */
/*----------------------------------------------------------------------------*/
/* ID: ANDB                                                                   */
/*----------------------------------------------------------------------------*/
/*

ANDD, ANDW, VANDW
signed char = signed char & signed char;
signed char = signed char & (signed char)(k);
char2 = char2 & char2;
char2 = char2 & (char2)(k);
char3 = char3 & char3;
char3 = char3 & (char3)(k);
char4 = char4 & char4;
char4 = char4 & (char4)(k);
char8 = char8 & char8;
char16 = char16 & char16;
char32 = char32 & char32;
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = char64 & char64;
#endif
uchar = uchar & uchar;
uchar = uchar & (uchar)(k);
uchar2 = uchar2 & uchar2;
uchar2 = uchar2 & (uchar2)(k);
uchar3 = uchar3 & uchar3;
uchar3 = uchar3 & (uchar3)(k);
uchar4 = uchar4 & uchar4;
uchar4 = uchar4 & (uchar4)(k);
uchar8 = uchar8 & uchar8;
uchar16 = uchar16 & uchar16;
uchar32 = uchar32 & uchar32;
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = uchar64 & uchar64;
#endif
short = short & short;
short = short & (short)(k);
short2 = short2 & short2;
short2 = short2 & (short2)(k);
short3 = short3 & short3;
short4 = short4 & short4;
short8 = short8 & short8;
short16 = short16 & short16;
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = short32 & short32;
#endif
ushort = ushort & ushort;
ushort = ushort & (ushort)(k);
ushort2 = ushort2 & ushort2;
ushort2 = ushort2 & (ushort2)(k);
ushort3 = ushort3 & ushort3;
ushort4 = ushort4 & ushort4;
ushort8 = ushort8 & ushort8;
ushort16 = ushort16 & ushort16;
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = ushort32 & ushort32;
#endif
int = int & int;
int = int & (int)(k);
int2 = int2 & int2;
int2 = int2 & (int2)(k);
int3 = int3 & int3;
int3 = int3 & (int3)(k);
int4 = int4 & int4;
int4 = int4 & (int4)(k);
int8 = int8 & int8;
int8 = int8 & (int8)(k);
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = int16 & int16;
int16 = int16 & (int16)(k);
#endif
uint = uint & uint;
uint = uint & (uint)(k);
uint2 = uint2 & uint2;
uint2 = uint2 & (uint2)(k);
uint3 = uint3 & uint3;
uint3 = uint3 & (uint3)(k);
uint4 = uint4 & uint4;
uint4 = uint4 & (uint4)(k);
uint8 = uint8 & uint8;
uint8 = uint8 & (uint8)(k);
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = uint16 & uint16;
uint16 = uint16 & (uint16)(k);
#endif

ANDD, VANDW
long = long & long;
long = long & (long)(k);
long2 = long2 & long2;
long3 = long3 & long3;
long4 = long4 & long4;
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = long8 & long8;
#endif
ulong = ulong & ulong;
ulong = ulong & (ulong)(k);
ulong2 = ulong2 & ulong2;
ulong3 = ulong3 & ulong3;
ulong4 = ulong4 & ulong4;
#if __C7X_VEC_SIZE_BITS__ == 512
ulong8 = ulong8 & ulong8;
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: DIV                                                                    */
/*----------------------------------------------------------------------------*/
/*

DIVW
int = int / int;

DIVUW
uint = uint / uint;

DIVDW
long = long / int;

DIVUDW
ulong = ulong / uint;

*/

/*----------------------------------------------------------------------------*/
/* ID: MINUS                                                                  */
/*----------------------------------------------------------------------------*/
/*

VSUBB
signed char = signed char - signed char;
signed char = signed char - (signed char)(k);
char2 = char2 - char2;
char2 = char2 - (char2)(k);
char3 = char3 - char3;
char3 = char3 - (char3)(k);
char4 = char4 - char4;
char4 = char4 - (char4)(k);
char8 = char8 - char8;
char8 = char8 - (char8)(k);
char16 = char16 - char16;
char16 = char16 - (char16)(k);
char32 = char32 - char32;
char32 = char32 - (char32)(k);
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = char64 - char64;
char64 = char64 - (char64)(k);
#endif
uchar = uchar - uchar;
uchar = uchar - (uchar)(k);
uchar2 = uchar2 - uchar2;
uchar2 = uchar2 - (uchar2)(k);
uchar3 = uchar3 - uchar3;
uchar3 = uchar3 - (uchar3)(k);
uchar4 = uchar4 - uchar4;
uchar4 = uchar4 - (uchar4)(k);
uchar8 = uchar8 - uchar8;
uchar8 = uchar8 - (uchar8)(k);
uchar16 = uchar16 - uchar16;
uchar16 = uchar16 - (uchar16)(k);
uchar32 = uchar32 - uchar32;
uchar32 = uchar32 - (uchar32)(k);
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = uchar64 - uchar64;
uchar64 = uchar64 - (uchar64)(k);
#endif
cchar = cchar - cchar;
cchar2 = cchar2 - cchar2;
cchar4 = cchar4 - cchar4;
cchar8 = cchar8 - cchar8;
cchar16 = cchar16 - cchar16;
#if __C7X_VEC_SIZE_BITS__ == 512
cchar32 = cchar32 - cchar32;
#endif

VSUBH
short = short - short;
short = short - (short)(k);
short2 = short2 - short2;
short2 = short2 - (short2)(k);
short3 = short3 - short3;
short3 = short3 - (short3)(k);
short4 = short4 - short4;
short4 = short4 - (short4)(k);
short8 = short8 - short8;
short8 = short8 - (short8)(k);
short16 = short16 - short16;
short16 = short16 - (short16)(k);
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = short32 - short32;
short32 = short32 - (short32)(k);
#endif
ushort = ushort - ushort;
ushort = ushort - (ushort)(k);
ushort2 = ushort2 - ushort2;
ushort2 = ushort2 - (ushort2)(k);
ushort3 = ushort3 - ushort3;
ushort3 = ushort3 - (ushort3)(k);
ushort4 = ushort4 - ushort4;
ushort4 = ushort4 - (ushort4)(k);
ushort8 = ushort8 - ushort8;
ushort8 = ushort8 - (ushort8)(k);
ushort16 = ushort16 - ushort16;
ushort16 = ushort16 - (ushort16)(k);
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = ushort32 - ushort32;
ushort32 = ushort32 - (ushort32)(k);
#endif
cshort = cshort - cshort;
cshort2 = cshort2 - cshort2;
cshort4 = cshort4 - cshort4;
cshort8 = cshort8 - cshort8;
#if __C7X_VEC_SIZE_BITS__ == 512
cshort16 = cshort16 - cshort16;
#endif

SUBW, VSUBW
int = int - int;
int = int - (int)(k);
int2 = int2 - int2;
int2 = int2 - (int2)(k);
int3 = int3 - int3;
int3 = int3 - (int3)(k);
int4 = int4 - int4;
int4 = int4 - (int4)(k);
int8 = int8 - int8;
int8 = int8 - (int8)(k);
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = int16 - int16;
int16 = int16 - (int16)(k);
#endif
uint = uint - uint;
uint = uint - (uint)(k);
uint2 = uint2 - uint2;
uint2 = uint2 - (uint2)(k);
uint3 = uint3 - uint3;
uint3 = uint3 - (uint3)(k);
uint4 = uint4 - uint4;
uint4 = uint4 - (uint4)(k);
uint8 = uint8 - uint8;
uint8 = uint8 - (uint8)(k);
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = uint16 - uint16;
uint16 = uint16 - (uint16)(k);
#endif

SUBSP, VSUBSP
float = float - float;
float2 = float2 - float2;
float3 = float3 - float3;
float4 = float4 - float4;
float8 = float8 - float8;
#if __C7X_VEC_SIZE_BITS__ == 512
float16 = float16 - float16;
#endif

VSUBW
cint = cint - cint;
cint2 = cint2 - cint2;
cint4 = cint4 - cint4;
#if __C7X_VEC_SIZE_BITS__ == 512
cint8 = cint8 - cint8;
#endif

VSUBSP
cfloat = cfloat - cfloat;
cfloat2 = cfloat2 - cfloat2;
cfloat4 = cfloat4 - cfloat4;
#if __C7X_VEC_SIZE_BITS__ == 512
cfloat8 = cfloat8 - cfloat8;
#endif

SUBD, VSUBD
long = long - long;
long = long - (long)(k);
long2 = long2 - long2;
long2 = long2 - (long2)(k);
long3 = long3 - long3;
long3 = long3 - (long3)(k);
long4 = long4 - long4;
long4 = long4 - (long4)(k);
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = long8 - long8;
long8 = long8 - (long8)(k);
#endif
ulong = ulong - ulong;
ulong = ulong - (ulong)(k);
ulong2 = ulong2 - ulong2;
ulong2 = ulong2 - (ulong2)(k);
ulong3 = ulong3 - ulong3;
ulong3 = ulong3 - (ulong3)(k);
ulong4 = ulong4 - ulong4;
ulong4 = ulong4 - (ulong4)(k);
#if __C7X_VEC_SIZE_BITS__ == 512
ulong8 = ulong8 - ulong8;
ulong8 = ulong8 - (ulong8)(k);
#endif

SUBDP, VSUBDP
double = double - double;
double2 = double2 - double2;
double3 = double3 - double3;
double4 = double4 - double4;
#if __C7X_VEC_SIZE_BITS__ == 512
double8 = double8 - double8;
#endif

VSUBD
clong = clong - clong;
clong2 = clong2 - clong2;
#if __C7X_VEC_SIZE_BITS__ == 512
clong4 = clong4 - clong4;
#endif

VSUBDP
cdouble = cdouble - cdouble;
cdouble2 = cdouble2 - cdouble2;
#if __C7X_VEC_SIZE_BITS__ == 512
cdouble4 = cdouble4 - cdouble4;
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: MOD                                                                    */
/*----------------------------------------------------------------------------*/
/*

MODW
int = int % int;

MODUW
uint = uint % uint;

MODDW
long = long % int;

MODUDW
ulong = ulong % uint;

*/

/*----------------------------------------------------------------------------*/
/* ID: MULT                                                                   */
/*----------------------------------------------------------------------------*/
/*

VMPYBB
signed char = signed char * signed char;
char2 = char2 * char2;
char3 = char3 * char3;
char4 = char4 * char4;
char8 = char8 * char8;
char16 = char16 * char16;
char32 = char32 * char32;
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = char64 * char64;
#endif
uchar = uchar * uchar;
uchar2 = uchar2 * uchar2;
uchar3 = uchar3 * uchar3;
uchar4 = uchar4 * uchar4;
uchar8 = uchar8 * uchar8;
uchar16 = uchar16 * uchar16;
uchar32 = uchar32 * uchar32;
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = uchar64 * uchar64;
#endif

VMPYHH
short = short * short;
short2 = short2 * short2;
short3 = short3 * short3;
short4 = short4 * short4;
short8 = short8 * short8;
short16 = short16 * short16;
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = short32 * short32;
#endif

MPYHW
int = short * short;

MPYSUHW
int = short * ushort;

VMPYHH
ushort = ushort * ushort;
ushort2 = ushort2 * ushort2;
ushort3 = ushort3 * ushort3;
ushort4 = ushort4 * ushort4;
ushort8 = ushort8 * ushort8;
ushort16 = ushort16 * ushort16;
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = ushort32 * ushort32;
#endif

MPYUHW
uint = ushort * ushort;

MPYWW, VMPYWW
int = int * int;
int2 = int2 * int2;
int3 = int3 * int3;
int4 = int4 * int4;
int8 = int8 * int8;
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = int16 * int16;
#endif
uint = uint * uint;
uint2 = uint2 * uint2;
uint3 = uint3 * uint3;
uint4 = uint4 * uint4;
uint8 = uint8 * uint8;
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = uint16 * uint16;
#endif

MPYSP, VMPYSP
float = float * float;
float2 = float2 * float2;
float3 = float3 * float3;
float4 = float4 * float4;
float8 = float8 * float8;
#if __C7X_VEC_SIZE_BITS__ == 512
float16 = float16 * float16;
#endif

MPYDD, VMPYDD
long = long * long;
long2 = long2 * long2;
long3 = long3 * long3;
long4 = long4 * long4;
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = long8 * long8;
#endif
ulong = ulong * ulong;
ulong2 = ulong2 * ulong2;
ulong3 = ulong3 * ulong3;
ulong4 = ulong4 * ulong4;
#if __C7X_VEC_SIZE_BITS__ == 512
ulong8 = ulong8 * ulong8;
#endif

MPYDP, VMPYDP
double = double * double;
double2 = double2 * double2;
double3 = double3 * double3;
double4 = double4 * double4;
#if __C7X_VEC_SIZE_BITS__ == 512
double8 = double8 * double8;
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: ORB                                                                    */
/*----------------------------------------------------------------------------*/
/*

ORD, ORW, VORW
signed char = signed char | signed char;
signed char = signed char | (signed char)(k);
char2 = char2 | char2;
char2 = char2 | (char2)(k);
char3 = char3 | char3;
char3 = char3 | (char3)(k);
char4 = char4 | char4;
char4 = char4 | (char4)(k);
char8 = char8 | char8;
char16 = char16 | char16;
char32 = char32 | char32;
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = char64 | char64;
#endif
uchar = uchar | uchar;
uchar = uchar | (uchar)(k);
uchar2 = uchar2 | uchar2;
uchar2 = uchar2 | (uchar2)(k);
uchar3 = uchar3 | uchar3;
uchar3 = uchar3 | (uchar3)(k);
uchar4 = uchar4 | uchar4;
uchar4 = uchar4 | (uchar4)(k);
uchar8 = uchar8 | uchar8;
uchar16 = uchar16 | uchar16;
uchar32 = uchar32 | uchar32;
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = uchar64 | uchar64;
#endif
short = short | short;
short = short | (short)(k);
short2 = short2 | short2;
short2 = short2 | (short2)(k);
short3 = short3 | short3;
short4 = short4 | short4;
short8 = short8 | short8;
short16 = short16 | short16;
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = short32 | short32;
#endif
ushort = ushort | ushort;
ushort = ushort | (ushort)(k);
ushort2 = ushort2 | ushort2;
ushort2 = ushort2 | (ushort2)(k);
ushort3 = ushort3 | ushort3;
ushort4 = ushort4 | ushort4;
ushort8 = ushort8 | ushort8;
ushort16 = ushort16 | ushort16;
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = ushort32 | ushort32;
#endif
int = int | int;
int = int | (int)(k);
int2 = int2 | int2;
int2 = int2 | (int2)(k);
int3 = int3 | int3;
int3 = int3 | (int3)(k);
int4 = int4 | int4;
int4 = int4 | (int4)(k);
int8 = int8 | int8;
int8 = int8 | (int8)(k);
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = int16 | int16;
int16 = int16 | (int16)(k);
#endif
uint = uint | uint;
uint = uint | (uint)(k);
uint2 = uint2 | uint2;
uint2 = uint2 | (uint2)(k);
uint3 = uint3 | uint3;
uint3 = uint3 | (uint3)(k);
uint4 = uint4 | uint4;
uint4 = uint4 | (uint4)(k);
uint8 = uint8 | uint8;
uint8 = uint8 | (uint8)(k);
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = uint16 | uint16;
uint16 = uint16 | (uint16)(k);
#endif

ORD, VORW
long = long | long;
long = long | (long)(k);
long2 = long2 | long2;
long3 = long3 | long3;
long4 = long4 | long4;
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = long8 | long8;
#endif
ulong = ulong | ulong;
ulong = ulong | (ulong)(k);
ulong2 = ulong2 | ulong2;
ulong3 = ulong3 | ulong3;
ulong4 = ulong4 | ulong4;
#if __C7X_VEC_SIZE_BITS__ == 512
ulong8 = ulong8 | ulong8;
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: PLUS                                                                   */
/*----------------------------------------------------------------------------*/
/*

VADDB
signed char = signed char + signed char;
signed char = signed char + (signed char)(k);
char2 = char2 + char2;
char2 = char2 + (char2)(k);
char3 = char3 + char3;
char3 = char3 + (char3)(k);
char4 = char4 + char4;
char4 = char4 + (char4)(k);
char8 = char8 + char8;
char8 = char8 + (char8)(k);
char16 = char16 + char16;
char16 = char16 + (char16)(k);
char32 = char32 + char32;
char32 = char32 + (char32)(k);
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = char64 + char64;
char64 = char64 + (char64)(k);
#endif
uchar = uchar + uchar;
uchar = uchar + (uchar)(k);
uchar2 = uchar2 + uchar2;
uchar2 = uchar2 + (uchar2)(k);
uchar3 = uchar3 + uchar3;
uchar3 = uchar3 + (uchar3)(k);
uchar4 = uchar4 + uchar4;
uchar4 = uchar4 + (uchar4)(k);
uchar8 = uchar8 + uchar8;
uchar8 = uchar8 + (uchar8)(k);
uchar16 = uchar16 + uchar16;
uchar16 = uchar16 + (uchar16)(k);
uchar32 = uchar32 + uchar32;
uchar32 = uchar32 + (uchar32)(k);
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = uchar64 + uchar64;
uchar64 = uchar64 + (uchar64)(k);
#endif
cchar = cchar + cchar;
cchar2 = cchar2 + cchar2;
cchar4 = cchar4 + cchar4;
cchar8 = cchar8 + cchar8;
cchar16 = cchar16 + cchar16;
#if __C7X_VEC_SIZE_BITS__ == 512
cchar32 = cchar32 + cchar32;
#endif

VADDH
short = short + short;
short = short + (short)(k);
short2 = short2 + short2;
short2 = short2 + (short2)(k);
short3 = short3 + short3;
short3 = short3 + (short3)(k);
short4 = short4 + short4;
short4 = short4 + (short4)(k);
short8 = short8 + short8;
short8 = short8 + (short8)(k);
short16 = short16 + short16;
short16 = short16 + (short16)(k);
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = short32 + short32;
short32 = short32 + (short32)(k);
#endif
ushort = ushort + ushort;
ushort = ushort + (ushort)(k);
ushort2 = ushort2 + ushort2;
ushort2 = ushort2 + (ushort2)(k);
ushort3 = ushort3 + ushort3;
ushort3 = ushort3 + (ushort3)(k);
ushort4 = ushort4 + ushort4;
ushort4 = ushort4 + (ushort4)(k);
ushort8 = ushort8 + ushort8;
ushort8 = ushort8 + (ushort8)(k);
ushort16 = ushort16 + ushort16;
ushort16 = ushort16 + (ushort16)(k);
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = ushort32 + ushort32;
ushort32 = ushort32 + (ushort32)(k);
#endif
cshort = cshort + cshort;
cshort2 = cshort2 + cshort2;
cshort4 = cshort4 + cshort4;
cshort8 = cshort8 + cshort8;
#if __C7X_VEC_SIZE_BITS__ == 512
cshort16 = cshort16 + cshort16;
#endif

ADDW, VADDW
int = int + int;
int = int + (int)(k);
int2 = int2 + int2;
int2 = int2 + (int2)(k);
int3 = int3 + int3;
int3 = int3 + (int3)(k);
int4 = int4 + int4;
int4 = int4 + (int4)(k);
int8 = int8 + int8;
int8 = int8 + (int8)(k);
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = int16 + int16;
int16 = int16 + (int16)(k);
#endif
uint = uint + uint;
uint = uint + (uint)(k);
uint2 = uint2 + uint2;
uint2 = uint2 + (uint2)(k);
uint3 = uint3 + uint3;
uint3 = uint3 + (uint3)(k);
uint4 = uint4 + uint4;
uint4 = uint4 + (uint4)(k);
uint8 = uint8 + uint8;
uint8 = uint8 + (uint8)(k);
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = uint16 + uint16;
uint16 = uint16 + (uint16)(k);
#endif

ADDSP, VADDSP
float = float + float;
float2 = float2 + float2;
float3 = float3 + float3;
float4 = float4 + float4;
float8 = float8 + float8;
#if __C7X_VEC_SIZE_BITS__ == 512
float16 = float16 + float16;
#endif

VADDW
cint = cint + cint;
cint2 = cint2 + cint2;
cint4 = cint4 + cint4;
#if __C7X_VEC_SIZE_BITS__ == 512
cint8 = cint8 + cint8;
#endif

VADDSP
cfloat = cfloat + cfloat;
cfloat2 = cfloat2 + cfloat2;
cfloat4 = cfloat4 + cfloat4;
#if __C7X_VEC_SIZE_BITS__ == 512
cfloat8 = cfloat8 + cfloat8;
#endif

ADDD, VADDD
long = long + long;
long = long + (long)(k);
long2 = long2 + long2;
long2 = long2 + (long2)(k);
long3 = long3 + long3;
long3 = long3 + (long3)(k);
long4 = long4 + long4;
long4 = long4 + (long4)(k);
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = long8 + long8;
long8 = long8 + (long8)(k);
#endif
ulong = ulong + ulong;
ulong = ulong + (ulong)(k);
ulong2 = ulong2 + ulong2;
ulong2 = ulong2 + (ulong2)(k);
ulong3 = ulong3 + ulong3;
ulong3 = ulong3 + (ulong3)(k);
ulong4 = ulong4 + ulong4;
ulong4 = ulong4 + (ulong4)(k);
#if __C7X_VEC_SIZE_BITS__ == 512
ulong8 = ulong8 + ulong8;
ulong8 = ulong8 + (ulong8)(k);
#endif

ADDDP, VADDDP
double = double + double;
double2 = double2 + double2;
double3 = double3 + double3;
double4 = double4 + double4;
#if __C7X_VEC_SIZE_BITS__ == 512
double8 = double8 + double8;
#endif

VADDD
clong = clong + clong;
clong2 = clong2 + clong2;
#if __C7X_VEC_SIZE_BITS__ == 512
clong4 = clong4 + clong4;
#endif

VADDDP
cdouble = cdouble + cdouble;
cdouble2 = cdouble2 + cdouble2;
#if __C7X_VEC_SIZE_BITS__ == 512
cdouble4 = cdouble4 + cdouble4;
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: SLL                                                                    */
/*----------------------------------------------------------------------------*/
/*

VSHLB
signed char = signed char << (signed char)(k={0-63});
char2 = char2 << (char2)(k={0-63});
char3 = char3 << (char3)(k={0-63});
char4 = char4 << (char4)(k={0-63});
char8 = char8 << (char8)(k={0-63});
char16 = char16 << (char16)(k={0-63});
char32 = char32 << (char32)(k={0-63});
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = char64 << (char64)(k={0-63});
#endif
uchar = uchar << (uchar)(k={0-63});
uchar2 = uchar2 << (uchar2)(k={0-63});
uchar3 = uchar3 << (uchar3)(k={0-63});
uchar4 = uchar4 << (uchar4)(k={0-63});
uchar8 = uchar8 << (uchar8)(k={0-63});
uchar16 = uchar16 << (uchar16)(k={0-63});
uchar32 = uchar32 << (uchar32)(k={0-63});
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = uchar64 << (uchar64)(k={0-63});
#endif

VSHLH
short = short << (short)(k={0-63});
short2 = short2 << (short2)(k={0-63});
short3 = short3 << (short3)(k={0-63});
short4 = short4 << (short4)(k={0-63});
short8 = short8 << (short8)(k={0-63});
short16 = short16 << (short16)(k={0-63});
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = short32 << (short32)(k={0-63});
#endif
ushort = ushort << (ushort)(k={0-63});
ushort2 = ushort2 << (ushort2)(k={0-63});
ushort3 = ushort3 << (ushort3)(k={0-63});
ushort4 = ushort4 << (ushort4)(k={0-63});
ushort8 = ushort8 << (ushort8)(k={0-63});
ushort16 = ushort16 << (ushort16)(k={0-63});
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = ushort32 << (ushort32)(k={0-63});
#endif

SHLW
int = int << (uchar)(k={0-63});

SHLW, VSHLW
int = int << int;
int = int << (int)(k);
int2 = int2 << int2;
int2 = int2 << (int2)(k);
int3 = int3 << int3;
int3 = int3 << (int3)(k);
int4 = int4 << int4;
int4 = int4 << (int4)(k);
int8 = int8 << int8;
int8 = int8 << (int8)(k);
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = int16 << int16;
int16 = int16 << (int16)(k);
#endif

SHLW
uint = uint << (uchar)(k={0-63});

SHLW, VSHLW
uint = uint << uint;
uint = uint << (uint)(k);
uint2 = uint2 << uint2;
uint2 = uint2 << (uint2)(k);
uint3 = uint3 << uint3;
uint3 = uint3 << (uint3)(k);
uint4 = uint4 << uint4;
uint4 = uint4 << (uint4)(k);
uint8 = uint8 << uint8;
uint8 = uint8 << (uint8)(k);
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = uint16 << uint16;
uint16 = uint16 << (uint16)(k);
#endif

SHLD
long = long << (uchar)(k={0-63});
long = long << int;

VSHLD
long = long << long;
long = long << (long)(k);
long2 = long2 << long2;
long2 = long2 << (long2)(k);
long3 = long3 << long3;
long3 = long3 << (long3)(k);
long4 = long4 << long4;
long4 = long4 << (long4)(k);
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = long8 << long8;
long8 = long8 << (long8)(k);
#endif

SHLD
ulong = ulong << (uchar)(k={0-63});
ulong = ulong << uint;

VSHLD
ulong = ulong << ulong;
ulong = ulong << (ulong)(k);
ulong2 = ulong2 << ulong2;
ulong2 = ulong2 << (ulong2)(k);
ulong3 = ulong3 << ulong3;
ulong3 = ulong3 << (ulong3)(k);
ulong4 = ulong4 << ulong4;
ulong4 = ulong4 << (ulong4)(k);
#if __C7X_VEC_SIZE_BITS__ == 512
ulong8 = ulong8 << ulong8;
ulong8 = ulong8 << (ulong8)(k);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: SRL                                                                    */
/*----------------------------------------------------------------------------*/
/*

SHRW
int = int >> (uchar)(k={0-63});

SHRW, VSHRW
int = int >> int;
int = int >> (int)(k);
int2 = int2 >> int2;
int2 = int2 >> (int2)(k);
int3 = int3 >> int3;
int3 = int3 >> (int3)(k);
int4 = int4 >> int4;
int4 = int4 >> (int4)(k);
int8 = int8 >> int8;
int8 = int8 >> (int8)(k);
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = int16 >> int16;
int16 = int16 >> (int16)(k);
#endif

SHRUW
uint = uint >> (uchar)(k={0-63});

SHRUW, VSHRUW
uint = uint >> uint;
uint = uint >> (uint)(k);
uint2 = uint2 >> uint2;
uint2 = uint2 >> (uint2)(k);
uint3 = uint3 >> uint3;
uint3 = uint3 >> (uint3)(k);
uint4 = uint4 >> uint4;
uint4 = uint4 >> (uint4)(k);
uint8 = uint8 >> uint8;
uint8 = uint8 >> (uint8)(k);
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = uint16 >> uint16;
uint16 = uint16 >> (uint16)(k);
#endif

SHRD
long = long >> (uchar)(k={0-63});
long = long >> int;

VSHRD
long = long >> long;
long = long >> (long)(k);
long2 = long2 >> long2;
long2 = long2 >> (long2)(k);
long3 = long3 >> long3;
long3 = long3 >> (long3)(k);
long4 = long4 >> long4;
long4 = long4 >> (long4)(k);
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = long8 >> long8;
long8 = long8 >> (long8)(k);
#endif

SHRUD
ulong = ulong >> (uchar)(k={0-63});
ulong = ulong >> uint;

VSHRUD
ulong = ulong >> ulong;
ulong = ulong >> (ulong)(k);
ulong2 = ulong2 >> ulong2;
ulong2 = ulong2 >> (ulong2)(k);
ulong3 = ulong3 >> ulong3;
ulong3 = ulong3 >> (ulong3)(k);
ulong4 = ulong4 >> ulong4;
ulong4 = ulong4 >> (ulong4)(k);
#if __C7X_VEC_SIZE_BITS__ == 512
ulong8 = ulong8 >> ulong8;
ulong8 = ulong8 >> (ulong8)(k);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: XORB                                                                   */
/*----------------------------------------------------------------------------*/
/*

VXORW, XORD, XORW
signed char = signed char ^ signed char;
signed char = signed char ^ (signed char)(k);
char2 = char2 ^ char2;
char2 = char2 ^ (char2)(k);
char3 = char3 ^ char3;
char3 = char3 ^ (char3)(k);
char4 = char4 ^ char4;
char4 = char4 ^ (char4)(k);
char8 = char8 ^ char8;
char16 = char16 ^ char16;
char32 = char32 ^ char32;
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = char64 ^ char64;
#endif
uchar = uchar ^ uchar;
uchar = uchar ^ (uchar)(k);
uchar2 = uchar2 ^ uchar2;
uchar2 = uchar2 ^ (uchar2)(k);
uchar3 = uchar3 ^ uchar3;
uchar3 = uchar3 ^ (uchar3)(k);
uchar4 = uchar4 ^ uchar4;
uchar4 = uchar4 ^ (uchar4)(k);
uchar8 = uchar8 ^ uchar8;
uchar16 = uchar16 ^ uchar16;
uchar32 = uchar32 ^ uchar32;
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = uchar64 ^ uchar64;
#endif
short = short ^ short;
short = short ^ (short)(k);
short2 = short2 ^ short2;
short2 = short2 ^ (short2)(k);
short3 = short3 ^ short3;
short4 = short4 ^ short4;
short8 = short8 ^ short8;
short16 = short16 ^ short16;
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = short32 ^ short32;
#endif
ushort = ushort ^ ushort;
ushort = ushort ^ (ushort)(k);
ushort2 = ushort2 ^ ushort2;
ushort2 = ushort2 ^ (ushort2)(k);
ushort3 = ushort3 ^ ushort3;
ushort4 = ushort4 ^ ushort4;
ushort8 = ushort8 ^ ushort8;
ushort16 = ushort16 ^ ushort16;
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = ushort32 ^ ushort32;
#endif
int = int ^ int;
int = int ^ (int)(k);
int2 = int2 ^ int2;
int2 = int2 ^ (int2)(k);
int3 = int3 ^ int3;
int3 = int3 ^ (int3)(k);
int4 = int4 ^ int4;
int4 = int4 ^ (int4)(k);
int8 = int8 ^ int8;
int8 = int8 ^ (int8)(k);
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = int16 ^ int16;
int16 = int16 ^ (int16)(k);
#endif
uint = uint ^ uint;
uint = uint ^ (uint)(k);
uint2 = uint2 ^ uint2;
uint2 = uint2 ^ (uint2)(k);
uint3 = uint3 ^ uint3;
uint3 = uint3 ^ (uint3)(k);
uint4 = uint4 ^ uint4;
uint4 = uint4 ^ (uint4)(k);
uint8 = uint8 ^ uint8;
uint8 = uint8 ^ (uint8)(k);
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = uint16 ^ uint16;
uint16 = uint16 ^ (uint16)(k);
#endif

VXORW, XORD
long = long ^ long;
long = long ^ (long)(k);
long2 = long2 ^ long2;
long3 = long3 ^ long3;
long4 = long4 ^ long4;
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = long8 ^ long8;
#endif
ulong = ulong ^ ulong;
ulong = ulong ^ (ulong)(k);
ulong2 = ulong2 ^ ulong2;
ulong3 = ulong3 ^ ulong3;
ulong4 = ulong4 ^ ulong4;
#if __C7X_VEC_SIZE_BITS__ == 512
ulong8 = ulong8 ^ ulong8;
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __abs                                                                  */
/*----------------------------------------------------------------------------*/
/*
VABSB
*/
signed char __OVBIF __abs(signed char);
__char2 __OVBIF __abs(__char2);
__char3 __OVBIF __abs(__char3);
__char4 __OVBIF __abs(__char4);
__char8 __OVBIF __abs(__char8);
__char16 __OVBIF __abs(__char16);
__char32 __OVBIF __abs(__char32);
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __abs(__char64);
#endif
__cchar __OVBIF __abs(__cchar);
__cchar2 __OVBIF __abs(__cchar2);
__cchar4 __OVBIF __abs(__cchar4);
__cchar8 __OVBIF __abs(__cchar8);
__cchar16 __OVBIF __abs(__cchar16);
#if __C7X_VEC_SIZE_BITS__ == 512
__cchar32 __OVBIF __abs(__cchar32);
#endif
/*
VABSH
*/
short __OVBIF __abs(short);
__short2 __OVBIF __abs(__short2);
__short3 __OVBIF __abs(__short3);
__short4 __OVBIF __abs(__short4);
__short8 __OVBIF __abs(__short8);
__short16 __OVBIF __abs(__short16);
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __abs(__short32);
#endif
__cshort __OVBIF __abs(__cshort);
__cshort2 __OVBIF __abs(__cshort2);
__cshort4 __OVBIF __abs(__cshort4);
__cshort8 __OVBIF __abs(__cshort8);
#if __C7X_VEC_SIZE_BITS__ == 512
__cshort16 __OVBIF __abs(__cshort16);
#endif
/*
VABSW
*/
int __OVBIF __abs(int);
__int2 __OVBIF __abs(__int2);
__int3 __OVBIF __abs(__int3);
__int4 __OVBIF __abs(__int4);
__int8 __OVBIF __abs(__int8);
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __abs(__int16);
#endif
/*
VABSSP
*/
float __OVBIF __abs(float);
__float2 __OVBIF __abs(__float2);
__float3 __OVBIF __abs(__float3);
__float4 __OVBIF __abs(__float4);
__float8 __OVBIF __abs(__float8);
#if __C7X_VEC_SIZE_BITS__ == 512
__float16 __OVBIF __abs(__float16);
#endif
/*
VABSW
*/
__cint __OVBIF __abs(__cint);
__cint2 __OVBIF __abs(__cint2);
__cint4 __OVBIF __abs(__cint4);
#if __C7X_VEC_SIZE_BITS__ == 512
__cint8 __OVBIF __abs(__cint8);
#endif
/*
VABSSP
*/
__cfloat __OVBIF __abs(__cfloat);
__cfloat2 __OVBIF __abs(__cfloat2);
__cfloat4 __OVBIF __abs(__cfloat4);
#if __C7X_VEC_SIZE_BITS__ == 512
__cfloat8 __OVBIF __abs(__cfloat8);
#endif
/*
VABSD
*/
long __OVBIF __abs(long);
__long2 __OVBIF __abs(__long2);
__long3 __OVBIF __abs(__long3);
__long4 __OVBIF __abs(__long4);
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __abs(__long8);
#endif
/*
VABSDP
*/
double __OVBIF __abs(double);
__double2 __OVBIF __abs(__double2);
__double3 __OVBIF __abs(__double3);
__double4 __OVBIF __abs(__double4);
#if __C7X_VEC_SIZE_BITS__ == 512
__double8 __OVBIF __abs(__double8);
#endif
/*
VABSD
*/
__clong __OVBIF __abs(__clong);
__clong2 __OVBIF __abs(__clong2);
#if __C7X_VEC_SIZE_BITS__ == 512
__clong4 __OVBIF __abs(__clong4);
#endif
/*
VABSDP
*/
__cdouble __OVBIF __abs(__cdouble);
__cdouble2 __OVBIF __abs(__cdouble2);
#if __C7X_VEC_SIZE_BITS__ == 512
__cdouble4 __OVBIF __abs(__cdouble4);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __abs_diff                                                             */
/*----------------------------------------------------------------------------*/
/*
VSUBABSB
*/
__uchar __OVBIF __abs_diff(__uchar, __uchar);
__uchar2 __OVBIF __abs_diff(__uchar2, __uchar2);
__uchar3 __OVBIF __abs_diff(__uchar3, __uchar3);
__uchar4 __OVBIF __abs_diff(__uchar4, __uchar4);
__uchar8 __OVBIF __abs_diff(__uchar8, __uchar8);
__uchar16 __OVBIF __abs_diff(__uchar16, __uchar16);
__uchar32 __OVBIF __abs_diff(__uchar32, __uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __abs_diff(__uchar64, __uchar64);
#endif
/*
VSUBABSH
*/
__ushort __OVBIF __abs_diff(__ushort, __ushort);
__ushort2 __OVBIF __abs_diff(__ushort2, __ushort2);
__ushort3 __OVBIF __abs_diff(__ushort3, __ushort3);
__ushort4 __OVBIF __abs_diff(__ushort4, __ushort4);
__ushort8 __OVBIF __abs_diff(__ushort8, __ushort8);
__ushort16 __OVBIF __abs_diff(__ushort16, __ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __abs_diff(__ushort32, __ushort32);
#endif
/*
VSUBABSW
*/
__uint __OVBIF __abs_diff(__uint, __uint);
__uint2 __OVBIF __abs_diff(__uint2, __uint2);
__uint3 __OVBIF __abs_diff(__uint3, __uint3);
__uint4 __OVBIF __abs_diff(__uint4, __uint4);
__uint8 __OVBIF __abs_diff(__uint8, __uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __abs_diff(__uint16, __uint16);
#endif
/*
VSUBABSD
*/
__ulong __OVBIF __abs_diff(__ulong, __ulong);
__ulong2 __OVBIF __abs_diff(__ulong2, __ulong2);
__ulong3 __OVBIF __abs_diff(__ulong3, __ulong3);
__ulong4 __OVBIF __abs_diff(__ulong4, __ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __abs_diff(__ulong8, __ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __add                                                                  */
/*----------------------------------------------------------------------------*/
/*
VADDCB
*/
__char2 __OVBIF __add(__bool2, __char2, __char2);
__char3 __OVBIF __add(__bool3, __char3, __char3);
__char4 __OVBIF __add(__bool4, __char4, __char4);
__char8 __OVBIF __add(__bool8, __char8, __char8);
__char16 __OVBIF __add(__bool16, __char16, __char16);
__char32 __OVBIF __add(__bool32, __char32, __char32);
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __add(__bool64, __char64, __char64);
#endif
__uchar2 __OVBIF __add(__bool2, __uchar2, __uchar2);
__uchar3 __OVBIF __add(__bool3, __uchar3, __uchar3);
__uchar4 __OVBIF __add(__bool4, __uchar4, __uchar4);
__uchar8 __OVBIF __add(__bool8, __uchar8, __uchar8);
__uchar16 __OVBIF __add(__bool16, __uchar16, __uchar16);
__uchar32 __OVBIF __add(__bool32, __uchar32, __uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __add(__bool64, __uchar64, __uchar64);
#endif
/*
VADDCH
*/
__short2 __OVBIF __add(__bool2, __short2, __short2);
__short3 __OVBIF __add(__bool3, __short3, __short3);
__short4 __OVBIF __add(__bool4, __short4, __short4);
__short8 __OVBIF __add(__bool8, __short8, __short8);
__short16 __OVBIF __add(__bool16, __short16, __short16);
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __add(__bool32, __short32, __short32);
#endif
__ushort2 __OVBIF __add(__bool2, __ushort2, __ushort2);
__ushort3 __OVBIF __add(__bool3, __ushort3, __ushort3);
__ushort4 __OVBIF __add(__bool4, __ushort4, __ushort4);
__ushort8 __OVBIF __add(__bool8, __ushort8, __ushort8);
__ushort16 __OVBIF __add(__bool16, __ushort16, __ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __add(__bool32, __ushort32, __ushort32);
#endif
/*
VADDCW
*/
__int2 __OVBIF __add(__bool2, __int2, __int2);
__int3 __OVBIF __add(__bool3, __int3, __int3);
__int4 __OVBIF __add(__bool4, __int4, __int4);
__int8 __OVBIF __add(__bool8, __int8, __int8);
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __add(__bool16, __int16, __int16);
#endif
__uint2 __OVBIF __add(__bool2, __uint2, __uint2);
__uint3 __OVBIF __add(__bool3, __uint3, __uint3);
__uint4 __OVBIF __add(__bool4, __uint4, __uint4);
__uint8 __OVBIF __add(__bool8, __uint8, __uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __add(__bool16, __uint16, __uint16);
#endif
/*
VADDCD
*/
__long2 __OVBIF __add(__bool2, __long2, __long2);
__long3 __OVBIF __add(__bool3, __long3, __long3);
__long4 __OVBIF __add(__bool4, __long4, __long4);
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __add(__bool8, __long8, __long8);
#endif
__ulong2 __OVBIF __add(__bool2, __ulong2, __ulong2);
__ulong3 __OVBIF __add(__bool3, __ulong3, __ulong3);
__ulong4 __OVBIF __add(__bool4, __ulong4, __ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __add(__bool8, __ulong8, __ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __add_sat                                                              */
/*----------------------------------------------------------------------------*/
/*
VSADDB
*/
signed char __OVBIF __add_sat(signed char, signed char);
/*
signed char __OVBIF __add_sat(signed char, signed char __CST(-128, 127));
*/
__char2 __OVBIF __add_sat(__char2, __char2);
/*
__char2 __OVBIF __add_sat(__char2, __char2 __CST(-128, 127));
*/
__char3 __OVBIF __add_sat(__char3, __char3);
/*
__char3 __OVBIF __add_sat(__char3, __char3 __CST(-128, 127));
*/
__char4 __OVBIF __add_sat(__char4, __char4);
/*
__char4 __OVBIF __add_sat(__char4, __char4 __CST(-128, 127));
*/
__char8 __OVBIF __add_sat(__char8, __char8);
/*
__char8 __OVBIF __add_sat(__char8, __char8 __CST(-128, 127));
*/
__char16 __OVBIF __add_sat(__char16, __char16);
/*
__char16 __OVBIF __add_sat(__char16, __char16 __CST(-128, 127));
*/
__char32 __OVBIF __add_sat(__char32, __char32);
/*
__char32 __OVBIF __add_sat(__char32, __char32 __CST(-128, 127));
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __add_sat(__char64, __char64);
/*
__char64 __OVBIF __add_sat(__char64, __char64 __CST(-128, 127));
*/
#endif
/*
VSADDUSB
*/
__uchar __OVBIF __add_sat(__uchar, signed char);
__uchar2 __OVBIF __add_sat(__uchar2, __char2);
__uchar3 __OVBIF __add_sat(__uchar3, __char3);
__uchar4 __OVBIF __add_sat(__uchar4, __char4);
__uchar8 __OVBIF __add_sat(__uchar8, __char8);
__uchar16 __OVBIF __add_sat(__uchar16, __char16);
__uchar32 __OVBIF __add_sat(__uchar32, __char32);
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __add_sat(__uchar64, __char64);
#endif
/*
VSADDUB
*/
__uchar __OVBIF __add_sat(__uchar, __uchar);
__uchar2 __OVBIF __add_sat(__uchar2, __uchar2);
__uchar3 __OVBIF __add_sat(__uchar3, __uchar3);
__uchar4 __OVBIF __add_sat(__uchar4, __uchar4);
__uchar8 __OVBIF __add_sat(__uchar8, __uchar8);
__uchar16 __OVBIF __add_sat(__uchar16, __uchar16);
__uchar32 __OVBIF __add_sat(__uchar32, __uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __add_sat(__uchar64, __uchar64);
#endif
/*
VSADDB
*/
__cchar __OVBIF __add_sat(__cchar, __cchar);
__cchar2 __OVBIF __add_sat(__cchar2, __cchar2);
__cchar4 __OVBIF __add_sat(__cchar4, __cchar4);
__cchar8 __OVBIF __add_sat(__cchar8, __cchar8);
__cchar16 __OVBIF __add_sat(__cchar16, __cchar16);
#if __C7X_VEC_SIZE_BITS__ == 512
__cchar32 __OVBIF __add_sat(__cchar32, __cchar32);
#endif
/*
VSADDH
*/
short __OVBIF __add_sat(short, short);
/*
short __OVBIF __add_sat(short, short __CST(-32768, 32767));
*/
__short2 __OVBIF __add_sat(__short2, __short2);
/*
__short2 __OVBIF __add_sat(__short2, __short2 __CST(-32768, 32767));
*/
__short3 __OVBIF __add_sat(__short3, __short3);
/*
__short3 __OVBIF __add_sat(__short3, __short3 __CST(-32768, 32767));
*/
__short4 __OVBIF __add_sat(__short4, __short4);
/*
__short4 __OVBIF __add_sat(__short4, __short4 __CST(-32768, 32767));
*/
__short8 __OVBIF __add_sat(__short8, __short8);
/*
__short8 __OVBIF __add_sat(__short8, __short8 __CST(-32768, 32767));
*/
__short16 __OVBIF __add_sat(__short16, __short16);
/*
__short16 __OVBIF __add_sat(__short16, __short16 __CST(-32768, 32767));
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __add_sat(__short32, __short32);
/*
__short32 __OVBIF __add_sat(__short32, __short32 __CST(-32768, 32767));
*/
#endif
/*
VSADDUSH
*/
__ushort __OVBIF __add_sat(__ushort, short);
__ushort2 __OVBIF __add_sat(__ushort2, __short2);
__ushort3 __OVBIF __add_sat(__ushort3, __short3);
__ushort4 __OVBIF __add_sat(__ushort4, __short4);
__ushort8 __OVBIF __add_sat(__ushort8, __short8);
__ushort16 __OVBIF __add_sat(__ushort16, __short16);
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __add_sat(__ushort32, __short32);
#endif
/*
VSADDUH
*/
__ushort __OVBIF __add_sat(__ushort, __ushort);
__ushort2 __OVBIF __add_sat(__ushort2, __ushort2);
__ushort3 __OVBIF __add_sat(__ushort3, __ushort3);
__ushort4 __OVBIF __add_sat(__ushort4, __ushort4);
__ushort8 __OVBIF __add_sat(__ushort8, __ushort8);
__ushort16 __OVBIF __add_sat(__ushort16, __ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __add_sat(__ushort32, __ushort32);
#endif
/*
VSADDH
*/
__cshort __OVBIF __add_sat(__cshort, __cshort);
__cshort2 __OVBIF __add_sat(__cshort2, __cshort2);
__cshort4 __OVBIF __add_sat(__cshort4, __cshort4);
__cshort8 __OVBIF __add_sat(__cshort8, __cshort8);
#if __C7X_VEC_SIZE_BITS__ == 512
__cshort16 __OVBIF __add_sat(__cshort16, __cshort16);
#endif
/*
VSADDW
*/
int __OVBIF __add_sat(int, int);
/*
int __OVBIF __add_sat(int, int __CST(-2147483648, 2147483647));
*/
__int2 __OVBIF __add_sat(__int2, __int2);
/*
__int2 __OVBIF __add_sat(__int2, __int2 __CST(-2147483648, 2147483647));
*/
__int3 __OVBIF __add_sat(__int3, __int3);
/*
__int3 __OVBIF __add_sat(__int3, __int3 __CST(-2147483648, 2147483647));
*/
__int4 __OVBIF __add_sat(__int4, __int4);
/*
__int4 __OVBIF __add_sat(__int4, __int4 __CST(-2147483648, 2147483647));
*/
__int8 __OVBIF __add_sat(__int8, __int8);
/*
__int8 __OVBIF __add_sat(__int8, __int8 __CST(-2147483648, 2147483647));
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __add_sat(__int16, __int16);
/*
__int16 __OVBIF __add_sat(__int16, __int16 __CST(-2147483648, 2147483647));
*/
#endif
/*
VSADDUSW
*/
__uint __OVBIF __add_sat(__uint, int);
__uint2 __OVBIF __add_sat(__uint2, __int2);
__uint3 __OVBIF __add_sat(__uint3, __int3);
__uint4 __OVBIF __add_sat(__uint4, __int4);
__uint8 __OVBIF __add_sat(__uint8, __int8);
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __add_sat(__uint16, __int16);
#endif
/*
VSADDUW
*/
__uint __OVBIF __add_sat(__uint, __uint);
__uint2 __OVBIF __add_sat(__uint2, __uint2);
__uint3 __OVBIF __add_sat(__uint3, __uint3);
__uint4 __OVBIF __add_sat(__uint4, __uint4);
__uint8 __OVBIF __add_sat(__uint8, __uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __add_sat(__uint16, __uint16);
#endif
/*
VSADDW
*/
__cint __OVBIF __add_sat(__cint, __cint);
__cint2 __OVBIF __add_sat(__cint2, __cint2);
__cint4 __OVBIF __add_sat(__cint4, __cint4);
#if __C7X_VEC_SIZE_BITS__ == 512
__cint8 __OVBIF __add_sat(__cint8, __cint8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __and                                                                  */
/*----------------------------------------------------------------------------*/
/*
AND
*/
__bool2 __OVBIF __and(__bool2, __bool2);
__bool3 __OVBIF __and(__bool3, __bool3);
__bool4 __OVBIF __and(__bool4, __bool4);
__bool8 __OVBIF __and(__bool8, __bool8);
__bool16 __OVBIF __and(__bool16, __bool16);
__bool32 __OVBIF __and(__bool32, __bool32);
#if __C7X_VEC_SIZE_BITS__ == 512
__bool64 __OVBIF __and(__bool64, __bool64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __andn                                                                 */
/*----------------------------------------------------------------------------*/
/*
ANDND, ANDNW, VANDNW
*/
signed char __OVBIF __andn(signed char, signed char);
/*
signed char __OVBIF __andn(signed char, signed char __CST(-128, 127));
*/
__char2 __OVBIF __andn(__char2, __char2);
/*
__char2 __OVBIF __andn(__char2, __char2 __CST(-128, 127));
*/
__char3 __OVBIF __andn(__char3, __char3);
/*
__char3 __OVBIF __andn(__char3, __char3 __CST(-128, 127));
*/
__char4 __OVBIF __andn(__char4, __char4);
/*
__char4 __OVBIF __andn(__char4, __char4 __CST(-128, 127));
*/
__char8 __OVBIF __andn(__char8, __char8);
__char16 __OVBIF __andn(__char16, __char16);
__char32 __OVBIF __andn(__char32, __char32);
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __andn(__char64, __char64);
#endif
__uchar __OVBIF __andn(__uchar, __uchar);
/*
__uchar __OVBIF __andn(__uchar, __uchar __CST(0, 255));
*/
__uchar2 __OVBIF __andn(__uchar2, __uchar2);
/*
__uchar2 __OVBIF __andn(__uchar2, __uchar2 __CST(0, 255));
*/
__uchar3 __OVBIF __andn(__uchar3, __uchar3);
/*
__uchar3 __OVBIF __andn(__uchar3, __uchar3 __CST(0, 255));
*/
__uchar4 __OVBIF __andn(__uchar4, __uchar4);
/*
__uchar4 __OVBIF __andn(__uchar4, __uchar4 __CST(0, 255));
*/
__uchar8 __OVBIF __andn(__uchar8, __uchar8);
__uchar16 __OVBIF __andn(__uchar16, __uchar16);
__uchar32 __OVBIF __andn(__uchar32, __uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __andn(__uchar64, __uchar64);
#endif
short __OVBIF __andn(short, short);
/*
short __OVBIF __andn(short, short __CST(-32768, 32767));
*/
__short2 __OVBIF __andn(__short2, __short2);
/*
__short2 __OVBIF __andn(__short2, __short2 __CST(-32768, 32767));
*/
__short3 __OVBIF __andn(__short3, __short3);
__short4 __OVBIF __andn(__short4, __short4);
__short8 __OVBIF __andn(__short8, __short8);
__short16 __OVBIF __andn(__short16, __short16);
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __andn(__short32, __short32);
#endif
__ushort __OVBIF __andn(__ushort, __ushort);
/*
__ushort __OVBIF __andn(__ushort, __ushort __CST(0, 65535));
*/
__ushort2 __OVBIF __andn(__ushort2, __ushort2);
/*
__ushort2 __OVBIF __andn(__ushort2, __ushort2 __CST(0, 65535));
*/
__ushort3 __OVBIF __andn(__ushort3, __ushort3);
__ushort4 __OVBIF __andn(__ushort4, __ushort4);
__ushort8 __OVBIF __andn(__ushort8, __ushort8);
__ushort16 __OVBIF __andn(__ushort16, __ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __andn(__ushort32, __ushort32);
#endif
int __OVBIF __andn(int, int);
/*
int __OVBIF __andn(int, int __CST(-2147483648, 2147483647));
*/
__int2 __OVBIF __andn(__int2, __int2);
/*
__int2 __OVBIF __andn(__int2, __int2 __CST(-2147483648, 2147483647));
*/
__int3 __OVBIF __andn(__int3, __int3);
/*
__int3 __OVBIF __andn(__int3, __int3 __CST(-2147483648, 2147483647));
*/
__int4 __OVBIF __andn(__int4, __int4);
/*
__int4 __OVBIF __andn(__int4, __int4 __CST(-2147483648, 2147483647));
*/
__int8 __OVBIF __andn(__int8, __int8);
/*
__int8 __OVBIF __andn(__int8, __int8 __CST(-2147483648, 2147483647));
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __andn(__int16, __int16);
/*
__int16 __OVBIF __andn(__int16, __int16 __CST(-2147483648, 2147483647));
*/
#endif
__uint __OVBIF __andn(__uint, __uint);
/*
__uint __OVBIF __andn(__uint, __uint __CST(0, 4294967295));
*/
__uint2 __OVBIF __andn(__uint2, __uint2);
/*
__uint2 __OVBIF __andn(__uint2, __uint2 __CST(0, 4294967295));
*/
__uint3 __OVBIF __andn(__uint3, __uint3);
/*
__uint3 __OVBIF __andn(__uint3, __uint3 __CST(0, 4294967295));
*/
__uint4 __OVBIF __andn(__uint4, __uint4);
/*
__uint4 __OVBIF __andn(__uint4, __uint4 __CST(0, 4294967295));
*/
__uint8 __OVBIF __andn(__uint8, __uint8);
/*
__uint8 __OVBIF __andn(__uint8, __uint8 __CST(0, 4294967295));
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __andn(__uint16, __uint16);
/*
__uint16 __OVBIF __andn(__uint16, __uint16 __CST(0, 4294967295));
*/
#endif
/*
ANDND, VANDNW
*/
long __OVBIF __andn(long, long);
/*
long __OVBIF __andn(long, long __CST(-2147483648, 2147483647));
*/
__long2 __OVBIF __andn(__long2, __long2);
__long3 __OVBIF __andn(__long3, __long3);
__long4 __OVBIF __andn(__long4, __long4);
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __andn(__long8, __long8);
#endif
__ulong __OVBIF __andn(__ulong, __ulong);
/*
__ulong __OVBIF __andn(__ulong, __ulong __CST(0, 2147483647));
*/
__ulong2 __OVBIF __andn(__ulong2, __ulong2);
__ulong3 __OVBIF __andn(__ulong3, __ulong3);
__ulong4 __OVBIF __andn(__ulong4, __ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __andn(__ulong8, __ulong8);
#endif
/*
ANDN
*/
__bool2 __OVBIF __andn(__bool2, __bool2);
__bool3 __OVBIF __andn(__bool3, __bool3);
__bool4 __OVBIF __andn(__bool4, __bool4);
__bool8 __OVBIF __andn(__bool8, __bool8);
__bool16 __OVBIF __andn(__bool16, __bool16);
__bool32 __OVBIF __andn(__bool32, __bool32);
#if __C7X_VEC_SIZE_BITS__ == 512
__bool64 __OVBIF __andn(__bool64, __bool64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __apply_sign                                                           */
/*----------------------------------------------------------------------------*/
/*
VAPYSB
*/
signed char __OVBIF __apply_sign(signed char, signed char);
__char2 __OVBIF __apply_sign(__char2, __char2);
__char3 __OVBIF __apply_sign(__char3, __char3);
__char4 __OVBIF __apply_sign(__char4, __char4);
__char8 __OVBIF __apply_sign(__char8, __char8);
__char16 __OVBIF __apply_sign(__char16, __char16);
__char32 __OVBIF __apply_sign(__char32, __char32);
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __apply_sign(__char64, __char64);
#endif
/*
VAPYSH
*/
short __OVBIF __apply_sign(short, short);
__short2 __OVBIF __apply_sign(__short2, __short2);
__short3 __OVBIF __apply_sign(__short3, __short3);
__short4 __OVBIF __apply_sign(__short4, __short4);
__short8 __OVBIF __apply_sign(__short8, __short8);
__short16 __OVBIF __apply_sign(__short16, __short16);
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __apply_sign(__short32, __short32);
#endif
/*
VAPYSW
*/
int __OVBIF __apply_sign(int, int);
__int2 __OVBIF __apply_sign(__int2, __int2);
__int3 __OVBIF __apply_sign(__int3, __int3);
__int4 __OVBIF __apply_sign(__int4, __int4);
__int8 __OVBIF __apply_sign(__int8, __int8);
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __apply_sign(__int16, __int16);
#endif
/*
VAPYSD
*/
long __OVBIF __apply_sign(long, long);
__long2 __OVBIF __apply_sign(__long2, __long2);
__long3 __OVBIF __apply_sign(__long3, __long3);
__long4 __OVBIF __apply_sign(__long4, __long4);
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __apply_sign(__long8, __long8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __binary_log                                                           */
/*----------------------------------------------------------------------------*/
/*
VBINLOGW
*/
__uint __OVBIF __binary_log(__uint);
__uint2 __OVBIF __binary_log(__uint2);
__uint3 __OVBIF __binary_log(__uint3);
__uint4 __OVBIF __binary_log(__uint4);
__uint8 __OVBIF __binary_log(__uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __binary_log(__uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __bit_reverse                                                          */
/*----------------------------------------------------------------------------*/
/*
VBITRW
*/
int __OVBIF __bit_reverse(int);
__int2 __OVBIF __bit_reverse(__int2);
__int3 __OVBIF __bit_reverse(__int3);
__int4 __OVBIF __bit_reverse(__int4);
__int8 __OVBIF __bit_reverse(__int8);
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __bit_reverse(__int16);
#endif
__uint __OVBIF __bit_reverse(__uint);
__uint2 __OVBIF __bit_reverse(__uint2);
__uint3 __OVBIF __bit_reverse(__uint3);
__uint4 __OVBIF __bit_reverse(__uint4);
__uint8 __OVBIF __bit_reverse(__uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __bit_reverse(__uint16);
#endif
/*
VBITRD
*/
long __OVBIF __bit_reverse(long);
__long2 __OVBIF __bit_reverse(__long2);
__long3 __OVBIF __bit_reverse(__long3);
__long4 __OVBIF __bit_reverse(__long4);
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __bit_reverse(__long8);
#endif
__ulong __OVBIF __bit_reverse(__ulong);
__ulong2 __OVBIF __bit_reverse(__ulong2);
__ulong3 __OVBIF __bit_reverse(__ulong3);
__ulong4 __OVBIF __bit_reverse(__ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __bit_reverse(__ulong8);
#endif
/*
BITR
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__bool32 __OVBIF __bit_reverse(__bool32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__bool64 __OVBIF __bit_reverse(__bool64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __bit_transpose                                                        */
/*----------------------------------------------------------------------------*/
/*
VBITTRAN8B
*/
__uchar8 __OVBIF __bit_transpose(__uchar8);
__uchar16 __OVBIF __bit_transpose(__uchar16);
__uchar32 __OVBIF __bit_transpose(__uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __bit_transpose(__uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __classify                                                             */
/*----------------------------------------------------------------------------*/
/*
VCLASSSP
*/
int __OVBIF __classify(float);
__int2 __OVBIF __classify(__float2);
__int3 __OVBIF __classify(__float3);
__int4 __OVBIF __classify(__float4);
__int8 __OVBIF __classify(__float8);
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __classify(__float16);
#endif
/*
VCLASSDP
*/
long __OVBIF __classify(double);
__long2 __OVBIF __classify(__double2);
__long3 __OVBIF __classify(__double3);
__long4 __OVBIF __classify(__double4);
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __classify(__double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __clear                                                                */
/*----------------------------------------------------------------------------*/
/*
CLR
*/
__uint __BIF __clear(__uint, __uint);

/*----------------------------------------------------------------------------*/
/* ID: __cmatmpy_ext                                                          */
/*----------------------------------------------------------------------------*/
/*
VCMATMPYHW
*/
__cint2 __OVBIF __cmatmpy_ext(__cshort2, __cshort4);
__cint4 __OVBIF __cmatmpy_ext(__cshort4, __cshort8);
#if __C7X_VEC_SIZE_BITS__ == 512
__cint8 __OVBIF __cmatmpy_ext(__cshort8, __cshort16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __cmatmpy_fx                                                           */
/*----------------------------------------------------------------------------*/
/*
VCMATMPYR1HH
*/
__cshort2 __OVBIF __cmatmpy_fx(__cshort2, __cshort4);
__cshort4 __OVBIF __cmatmpy_fx(__cshort4, __cshort8);
#if __C7X_VEC_SIZE_BITS__ == 512
__cshort8 __OVBIF __cmatmpy_fx(__cshort8, __cshort16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __cmp_eq                                                               */
/*----------------------------------------------------------------------------*/
/*
CMPEQW
*/
int __OVBIF __cmp_eq(int, int);
/*
int __OVBIF __cmp_eq(int, int __CST(-2147483648, 2147483647));
*/
/*
CMPEQSP
*/
int __OVBIF __cmp_eq(float, float);
/*
CMPEQD
*/
int __OVBIF __cmp_eq(long, int __CST(-2147483648, 2147483647));
int __OVBIF __cmp_eq(long, long);
/*
CMPEQDP
*/
int __OVBIF __cmp_eq(double, double);

/*----------------------------------------------------------------------------*/
/* ID: __cmp_eq_bool                                                          */
/*----------------------------------------------------------------------------*/
/*
VCMPEQB
*/
__bool2 __OVBIF __cmp_eq_bool(__char2, __char2);
__bool3 __OVBIF __cmp_eq_bool(__char3, __char3);
__bool4 __OVBIF __cmp_eq_bool(__char4, __char4);
__bool8 __OVBIF __cmp_eq_bool(__char8, __char8);
__bool16 __OVBIF __cmp_eq_bool(__char16, __char16);
__bool32 __OVBIF __cmp_eq_bool(__char32, __char32);
#if __C7X_VEC_SIZE_BITS__ == 512
__bool64 __OVBIF __cmp_eq_bool(__char64, __char64);
#endif
__bool2 __OVBIF __cmp_eq_bool(__uchar2, __uchar2);
__bool3 __OVBIF __cmp_eq_bool(__uchar3, __uchar3);
__bool4 __OVBIF __cmp_eq_bool(__uchar4, __uchar4);
__bool8 __OVBIF __cmp_eq_bool(__uchar8, __uchar8);
__bool16 __OVBIF __cmp_eq_bool(__uchar16, __uchar16);
__bool32 __OVBIF __cmp_eq_bool(__uchar32, __uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
__bool64 __OVBIF __cmp_eq_bool(__uchar64, __uchar64);
#endif
/*
VCMPEQH
*/
__bool2 __OVBIF __cmp_eq_bool(__short2, __short2);
__bool3 __OVBIF __cmp_eq_bool(__short3, __short3);
__bool4 __OVBIF __cmp_eq_bool(__short4, __short4);
__bool8 __OVBIF __cmp_eq_bool(__short8, __short8);
__bool16 __OVBIF __cmp_eq_bool(__short16, __short16);
#if __C7X_VEC_SIZE_BITS__ == 512
__bool32 __OVBIF __cmp_eq_bool(__short32, __short32);
#endif
__bool2 __OVBIF __cmp_eq_bool(__ushort2, __ushort2);
__bool3 __OVBIF __cmp_eq_bool(__ushort3, __ushort3);
__bool4 __OVBIF __cmp_eq_bool(__ushort4, __ushort4);
__bool8 __OVBIF __cmp_eq_bool(__ushort8, __ushort8);
__bool16 __OVBIF __cmp_eq_bool(__ushort16, __ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
__bool32 __OVBIF __cmp_eq_bool(__ushort32, __ushort32);
#endif
/*
VCMPEQW
*/
__bool2 __OVBIF __cmp_eq_bool(__int2, __int2);
__bool3 __OVBIF __cmp_eq_bool(__int3, __int3);
__bool4 __OVBIF __cmp_eq_bool(__int4, __int4);
__bool8 __OVBIF __cmp_eq_bool(__int8, __int8);
#if __C7X_VEC_SIZE_BITS__ == 512
__bool16 __OVBIF __cmp_eq_bool(__int16, __int16);
#endif
__bool2 __OVBIF __cmp_eq_bool(__uint2, __uint2);
__bool3 __OVBIF __cmp_eq_bool(__uint3, __uint3);
__bool4 __OVBIF __cmp_eq_bool(__uint4, __uint4);
__bool8 __OVBIF __cmp_eq_bool(__uint8, __uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
__bool16 __OVBIF __cmp_eq_bool(__uint16, __uint16);
#endif
/*
VCMPEQSP
*/
__bool2 __OVBIF __cmp_eq_bool(__float2, __float2);
__bool3 __OVBIF __cmp_eq_bool(__float3, __float3);
__bool4 __OVBIF __cmp_eq_bool(__float4, __float4);
__bool8 __OVBIF __cmp_eq_bool(__float8, __float8);
#if __C7X_VEC_SIZE_BITS__ == 512
__bool16 __OVBIF __cmp_eq_bool(__float16, __float16);
#endif
/*
VCMPEQD
*/
__bool2 __OVBIF __cmp_eq_bool(__long2, __long2);
__bool3 __OVBIF __cmp_eq_bool(__long3, __long3);
__bool4 __OVBIF __cmp_eq_bool(__long4, __long4);
#if __C7X_VEC_SIZE_BITS__ == 512
__bool8 __OVBIF __cmp_eq_bool(__long8, __long8);
#endif
__bool2 __OVBIF __cmp_eq_bool(__ulong2, __ulong2);
__bool3 __OVBIF __cmp_eq_bool(__ulong3, __ulong3);
__bool4 __OVBIF __cmp_eq_bool(__ulong4, __ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
__bool8 __OVBIF __cmp_eq_bool(__ulong8, __ulong8);
#endif
/*
VCMPEQDP
*/
__bool2 __OVBIF __cmp_eq_bool(__double2, __double2);
__bool3 __OVBIF __cmp_eq_bool(__double3, __double3);
__bool4 __OVBIF __cmp_eq_bool(__double4, __double4);
#if __C7X_VEC_SIZE_BITS__ == 512
__bool8 __OVBIF __cmp_eq_bool(__double8, __double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __cmp_ge                                                               */
/*----------------------------------------------------------------------------*/
/*
CMPGEW
*/
int __OVBIF __cmp_ge(int, int);
/*
int __OVBIF __cmp_ge(int, int __CST(-2147483648, 2147483647));
*/
/*
CMPGEUW
*/
int __OVBIF __cmp_ge(__uint, __uint);
/*
int __OVBIF __cmp_ge(__uint, __uint __CST(0, 4294967295));
*/
/*
CMPGED
*/
int __OVBIF __cmp_ge(long, int __CST(-2147483648, 2147483647));
int __OVBIF __cmp_ge(long, long);
/*
CMPGEUD
*/
int __OVBIF __cmp_ge(__ulong, __uint __CST(0, 4294967295));
int __OVBIF __cmp_ge(__ulong, __ulong);

/*----------------------------------------------------------------------------*/
/* ID: __cmp_ge_bool                                                          */
/*----------------------------------------------------------------------------*/
/*
VCMPGEB
*/
__bool2 __OVBIF __cmp_ge_bool(__char2, __char2);
__bool3 __OVBIF __cmp_ge_bool(__char3, __char3);
__bool4 __OVBIF __cmp_ge_bool(__char4, __char4);
__bool8 __OVBIF __cmp_ge_bool(__char8, __char8);
__bool16 __OVBIF __cmp_ge_bool(__char16, __char16);
__bool32 __OVBIF __cmp_ge_bool(__char32, __char32);
#if __C7X_VEC_SIZE_BITS__ == 512
__bool64 __OVBIF __cmp_ge_bool(__char64, __char64);
#endif
/*
VCMPGEUB
*/
__bool2 __OVBIF __cmp_ge_bool(__uchar2, __uchar2);
__bool3 __OVBIF __cmp_ge_bool(__uchar3, __uchar3);
__bool4 __OVBIF __cmp_ge_bool(__uchar4, __uchar4);
__bool8 __OVBIF __cmp_ge_bool(__uchar8, __uchar8);
__bool16 __OVBIF __cmp_ge_bool(__uchar16, __uchar16);
__bool32 __OVBIF __cmp_ge_bool(__uchar32, __uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
__bool64 __OVBIF __cmp_ge_bool(__uchar64, __uchar64);
#endif
/*
VCMPGEH
*/
__bool2 __OVBIF __cmp_ge_bool(__short2, __short2);
__bool3 __OVBIF __cmp_ge_bool(__short3, __short3);
__bool4 __OVBIF __cmp_ge_bool(__short4, __short4);
__bool8 __OVBIF __cmp_ge_bool(__short8, __short8);
__bool16 __OVBIF __cmp_ge_bool(__short16, __short16);
#if __C7X_VEC_SIZE_BITS__ == 512
__bool32 __OVBIF __cmp_ge_bool(__short32, __short32);
#endif
/*
VCMPGEUH
*/
__bool2 __OVBIF __cmp_ge_bool(__ushort2, __ushort2);
__bool3 __OVBIF __cmp_ge_bool(__ushort3, __ushort3);
__bool4 __OVBIF __cmp_ge_bool(__ushort4, __ushort4);
__bool8 __OVBIF __cmp_ge_bool(__ushort8, __ushort8);
__bool16 __OVBIF __cmp_ge_bool(__ushort16, __ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
__bool32 __OVBIF __cmp_ge_bool(__ushort32, __ushort32);
#endif
/*
VCMPGEW
*/
__bool2 __OVBIF __cmp_ge_bool(__int2, __int2);
__bool3 __OVBIF __cmp_ge_bool(__int3, __int3);
__bool4 __OVBIF __cmp_ge_bool(__int4, __int4);
__bool8 __OVBIF __cmp_ge_bool(__int8, __int8);
#if __C7X_VEC_SIZE_BITS__ == 512
__bool16 __OVBIF __cmp_ge_bool(__int16, __int16);
#endif
/*
VCMPGEUW
*/
__bool2 __OVBIF __cmp_ge_bool(__uint2, __uint2);
__bool3 __OVBIF __cmp_ge_bool(__uint3, __uint3);
__bool4 __OVBIF __cmp_ge_bool(__uint4, __uint4);
__bool8 __OVBIF __cmp_ge_bool(__uint8, __uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
__bool16 __OVBIF __cmp_ge_bool(__uint16, __uint16);
#endif
/*
VCMPLESP
*/
__bool2 __OVBIF __cmp_ge_bool(__float2, __float2);
__bool3 __OVBIF __cmp_ge_bool(__float3, __float3);
__bool4 __OVBIF __cmp_ge_bool(__float4, __float4);
__bool8 __OVBIF __cmp_ge_bool(__float8, __float8);
#if __C7X_VEC_SIZE_BITS__ == 512
__bool16 __OVBIF __cmp_ge_bool(__float16, __float16);
#endif
/*
VCMPGED
*/
__bool2 __OVBIF __cmp_ge_bool(__long2, __long2);
__bool3 __OVBIF __cmp_ge_bool(__long3, __long3);
__bool4 __OVBIF __cmp_ge_bool(__long4, __long4);
#if __C7X_VEC_SIZE_BITS__ == 512
__bool8 __OVBIF __cmp_ge_bool(__long8, __long8);
#endif
/*
VCMPGEUD
*/
__bool2 __OVBIF __cmp_ge_bool(__ulong2, __ulong2);
__bool3 __OVBIF __cmp_ge_bool(__ulong3, __ulong3);
__bool4 __OVBIF __cmp_ge_bool(__ulong4, __ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
__bool8 __OVBIF __cmp_ge_bool(__ulong8, __ulong8);
#endif
/*
VCMPLEDP
*/
__bool2 __OVBIF __cmp_ge_bool(__double2, __double2);
__bool3 __OVBIF __cmp_ge_bool(__double3, __double3);
__bool4 __OVBIF __cmp_ge_bool(__double4, __double4);
#if __C7X_VEC_SIZE_BITS__ == 512
__bool8 __OVBIF __cmp_ge_bool(__double8, __double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __cmp_gt                                                               */
/*----------------------------------------------------------------------------*/
/*
CMPGTW
*/
int __OVBIF __cmp_gt(int, int);
/*
int __OVBIF __cmp_gt(int, int __CST(-2147483648, 2147483647));
*/
/*
CMPGTUW
*/
int __OVBIF __cmp_gt(__uint, __uint);
/*
int __OVBIF __cmp_gt(__uint, __uint __CST(0, 4294967295));
*/
/*
CMPGTD
*/
int __OVBIF __cmp_gt(long, int __CST(-2147483648, 2147483647));
int __OVBIF __cmp_gt(long, long);
/*
CMPGTUD
*/
int __OVBIF __cmp_gt(__ulong, __uint __CST(0, 4294967295));
int __OVBIF __cmp_gt(__ulong, __ulong);

/*----------------------------------------------------------------------------*/
/* ID: __cmp_gt_bool                                                          */
/*----------------------------------------------------------------------------*/
/*
VCMPGTB
*/
__bool2 __OVBIF __cmp_gt_bool(__char2, __char2);
__bool3 __OVBIF __cmp_gt_bool(__char3, __char3);
__bool4 __OVBIF __cmp_gt_bool(__char4, __char4);
__bool8 __OVBIF __cmp_gt_bool(__char8, __char8);
__bool16 __OVBIF __cmp_gt_bool(__char16, __char16);
__bool32 __OVBIF __cmp_gt_bool(__char32, __char32);
#if __C7X_VEC_SIZE_BITS__ == 512
__bool64 __OVBIF __cmp_gt_bool(__char64, __char64);
#endif
/*
VCMPGTUB
*/
__bool2 __OVBIF __cmp_gt_bool(__uchar2, __uchar2);
__bool3 __OVBIF __cmp_gt_bool(__uchar3, __uchar3);
__bool4 __OVBIF __cmp_gt_bool(__uchar4, __uchar4);
__bool8 __OVBIF __cmp_gt_bool(__uchar8, __uchar8);
__bool16 __OVBIF __cmp_gt_bool(__uchar16, __uchar16);
__bool32 __OVBIF __cmp_gt_bool(__uchar32, __uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
__bool64 __OVBIF __cmp_gt_bool(__uchar64, __uchar64);
#endif
/*
VCMPGTH
*/
__bool2 __OVBIF __cmp_gt_bool(__short2, __short2);
__bool3 __OVBIF __cmp_gt_bool(__short3, __short3);
__bool4 __OVBIF __cmp_gt_bool(__short4, __short4);
__bool8 __OVBIF __cmp_gt_bool(__short8, __short8);
__bool16 __OVBIF __cmp_gt_bool(__short16, __short16);
#if __C7X_VEC_SIZE_BITS__ == 512
__bool32 __OVBIF __cmp_gt_bool(__short32, __short32);
#endif
/*
VCMPGTUH
*/
__bool2 __OVBIF __cmp_gt_bool(__ushort2, __ushort2);
__bool3 __OVBIF __cmp_gt_bool(__ushort3, __ushort3);
__bool4 __OVBIF __cmp_gt_bool(__ushort4, __ushort4);
__bool8 __OVBIF __cmp_gt_bool(__ushort8, __ushort8);
__bool16 __OVBIF __cmp_gt_bool(__ushort16, __ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
__bool32 __OVBIF __cmp_gt_bool(__ushort32, __ushort32);
#endif
/*
VCMPGTW
*/
__bool2 __OVBIF __cmp_gt_bool(__int2, __int2);
__bool3 __OVBIF __cmp_gt_bool(__int3, __int3);
__bool4 __OVBIF __cmp_gt_bool(__int4, __int4);
__bool8 __OVBIF __cmp_gt_bool(__int8, __int8);
#if __C7X_VEC_SIZE_BITS__ == 512
__bool16 __OVBIF __cmp_gt_bool(__int16, __int16);
#endif
/*
VCMPGTUW
*/
__bool2 __OVBIF __cmp_gt_bool(__uint2, __uint2);
__bool3 __OVBIF __cmp_gt_bool(__uint3, __uint3);
__bool4 __OVBIF __cmp_gt_bool(__uint4, __uint4);
__bool8 __OVBIF __cmp_gt_bool(__uint8, __uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
__bool16 __OVBIF __cmp_gt_bool(__uint16, __uint16);
#endif
/*
VCMPLTSP
*/
__bool2 __OVBIF __cmp_gt_bool(__float2, __float2);
__bool3 __OVBIF __cmp_gt_bool(__float3, __float3);
__bool4 __OVBIF __cmp_gt_bool(__float4, __float4);
__bool8 __OVBIF __cmp_gt_bool(__float8, __float8);
#if __C7X_VEC_SIZE_BITS__ == 512
__bool16 __OVBIF __cmp_gt_bool(__float16, __float16);
#endif
/*
VCMPGTD
*/
__bool2 __OVBIF __cmp_gt_bool(__long2, __long2);
__bool3 __OVBIF __cmp_gt_bool(__long3, __long3);
__bool4 __OVBIF __cmp_gt_bool(__long4, __long4);
#if __C7X_VEC_SIZE_BITS__ == 512
__bool8 __OVBIF __cmp_gt_bool(__long8, __long8);
#endif
/*
VCMPGTUD
*/
__bool2 __OVBIF __cmp_gt_bool(__ulong2, __ulong2);
__bool3 __OVBIF __cmp_gt_bool(__ulong3, __ulong3);
__bool4 __OVBIF __cmp_gt_bool(__ulong4, __ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
__bool8 __OVBIF __cmp_gt_bool(__ulong8, __ulong8);
#endif
/*
VCMPLTDP
*/
__bool2 __OVBIF __cmp_gt_bool(__double2, __double2);
__bool3 __OVBIF __cmp_gt_bool(__double3, __double3);
__bool4 __OVBIF __cmp_gt_bool(__double4, __double4);
#if __C7X_VEC_SIZE_BITS__ == 512
__bool8 __OVBIF __cmp_gt_bool(__double8, __double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __cmp_le                                                               */
/*----------------------------------------------------------------------------*/
/*
CMPLESP
*/
int __OVBIF __cmp_le(float, float);
/*
CMPLEDP
*/
int __OVBIF __cmp_le(double, double);

/*----------------------------------------------------------------------------*/
/* ID: __cmp_le_bool                                                          */
/*----------------------------------------------------------------------------*/
/*
VCMPGEB
*/
__bool2 __OVBIF __cmp_le_bool(__char2, __char2);
__bool3 __OVBIF __cmp_le_bool(__char3, __char3);
__bool4 __OVBIF __cmp_le_bool(__char4, __char4);
__bool8 __OVBIF __cmp_le_bool(__char8, __char8);
__bool16 __OVBIF __cmp_le_bool(__char16, __char16);
__bool32 __OVBIF __cmp_le_bool(__char32, __char32);
#if __C7X_VEC_SIZE_BITS__ == 512
__bool64 __OVBIF __cmp_le_bool(__char64, __char64);
#endif
/*
VCMPGEUB
*/
__bool2 __OVBIF __cmp_le_bool(__uchar2, __uchar2);
__bool3 __OVBIF __cmp_le_bool(__uchar3, __uchar3);
__bool4 __OVBIF __cmp_le_bool(__uchar4, __uchar4);
__bool8 __OVBIF __cmp_le_bool(__uchar8, __uchar8);
__bool16 __OVBIF __cmp_le_bool(__uchar16, __uchar16);
__bool32 __OVBIF __cmp_le_bool(__uchar32, __uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
__bool64 __OVBIF __cmp_le_bool(__uchar64, __uchar64);
#endif
/*
VCMPGEH
*/
__bool2 __OVBIF __cmp_le_bool(__short2, __short2);
__bool3 __OVBIF __cmp_le_bool(__short3, __short3);
__bool4 __OVBIF __cmp_le_bool(__short4, __short4);
__bool8 __OVBIF __cmp_le_bool(__short8, __short8);
__bool16 __OVBIF __cmp_le_bool(__short16, __short16);
#if __C7X_VEC_SIZE_BITS__ == 512
__bool32 __OVBIF __cmp_le_bool(__short32, __short32);
#endif
/*
VCMPGEUH
*/
__bool2 __OVBIF __cmp_le_bool(__ushort2, __ushort2);
__bool3 __OVBIF __cmp_le_bool(__ushort3, __ushort3);
__bool4 __OVBIF __cmp_le_bool(__ushort4, __ushort4);
__bool8 __OVBIF __cmp_le_bool(__ushort8, __ushort8);
__bool16 __OVBIF __cmp_le_bool(__ushort16, __ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
__bool32 __OVBIF __cmp_le_bool(__ushort32, __ushort32);
#endif
/*
VCMPGEW
*/
__bool2 __OVBIF __cmp_le_bool(__int2, __int2);
__bool3 __OVBIF __cmp_le_bool(__int3, __int3);
__bool4 __OVBIF __cmp_le_bool(__int4, __int4);
__bool8 __OVBIF __cmp_le_bool(__int8, __int8);
#if __C7X_VEC_SIZE_BITS__ == 512
__bool16 __OVBIF __cmp_le_bool(__int16, __int16);
#endif
/*
VCMPGEUW
*/
__bool2 __OVBIF __cmp_le_bool(__uint2, __uint2);
__bool3 __OVBIF __cmp_le_bool(__uint3, __uint3);
__bool4 __OVBIF __cmp_le_bool(__uint4, __uint4);
__bool8 __OVBIF __cmp_le_bool(__uint8, __uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
__bool16 __OVBIF __cmp_le_bool(__uint16, __uint16);
#endif
/*
VCMPLESP
*/
__bool2 __OVBIF __cmp_le_bool(__float2, __float2);
__bool3 __OVBIF __cmp_le_bool(__float3, __float3);
__bool4 __OVBIF __cmp_le_bool(__float4, __float4);
__bool8 __OVBIF __cmp_le_bool(__float8, __float8);
#if __C7X_VEC_SIZE_BITS__ == 512
__bool16 __OVBIF __cmp_le_bool(__float16, __float16);
#endif
/*
VCMPGED
*/
__bool2 __OVBIF __cmp_le_bool(__long2, __long2);
__bool3 __OVBIF __cmp_le_bool(__long3, __long3);
__bool4 __OVBIF __cmp_le_bool(__long4, __long4);
#if __C7X_VEC_SIZE_BITS__ == 512
__bool8 __OVBIF __cmp_le_bool(__long8, __long8);
#endif
/*
VCMPGEUD
*/
__bool2 __OVBIF __cmp_le_bool(__ulong2, __ulong2);
__bool3 __OVBIF __cmp_le_bool(__ulong3, __ulong3);
__bool4 __OVBIF __cmp_le_bool(__ulong4, __ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
__bool8 __OVBIF __cmp_le_bool(__ulong8, __ulong8);
#endif
/*
VCMPLEDP
*/
__bool2 __OVBIF __cmp_le_bool(__double2, __double2);
__bool3 __OVBIF __cmp_le_bool(__double3, __double3);
__bool4 __OVBIF __cmp_le_bool(__double4, __double4);
#if __C7X_VEC_SIZE_BITS__ == 512
__bool8 __OVBIF __cmp_le_bool(__double8, __double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __cmp_lt                                                               */
/*----------------------------------------------------------------------------*/
/*
CMPLTSP
*/
int __OVBIF __cmp_lt(float, float);
/*
CMPLTDP
*/
int __OVBIF __cmp_lt(double, double);

/*----------------------------------------------------------------------------*/
/* ID: __cmp_lt_bool                                                          */
/*----------------------------------------------------------------------------*/
/*
VCMPGTB
*/
__bool2 __OVBIF __cmp_lt_bool(__char2, __char2);
__bool3 __OVBIF __cmp_lt_bool(__char3, __char3);
__bool4 __OVBIF __cmp_lt_bool(__char4, __char4);
__bool8 __OVBIF __cmp_lt_bool(__char8, __char8);
__bool16 __OVBIF __cmp_lt_bool(__char16, __char16);
__bool32 __OVBIF __cmp_lt_bool(__char32, __char32);
#if __C7X_VEC_SIZE_BITS__ == 512
__bool64 __OVBIF __cmp_lt_bool(__char64, __char64);
#endif
/*
VCMPGTUB
*/
__bool2 __OVBIF __cmp_lt_bool(__uchar2, __uchar2);
__bool3 __OVBIF __cmp_lt_bool(__uchar3, __uchar3);
__bool4 __OVBIF __cmp_lt_bool(__uchar4, __uchar4);
__bool8 __OVBIF __cmp_lt_bool(__uchar8, __uchar8);
__bool16 __OVBIF __cmp_lt_bool(__uchar16, __uchar16);
__bool32 __OVBIF __cmp_lt_bool(__uchar32, __uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
__bool64 __OVBIF __cmp_lt_bool(__uchar64, __uchar64);
#endif
/*
VCMPGTH
*/
__bool2 __OVBIF __cmp_lt_bool(__short2, __short2);
__bool3 __OVBIF __cmp_lt_bool(__short3, __short3);
__bool4 __OVBIF __cmp_lt_bool(__short4, __short4);
__bool8 __OVBIF __cmp_lt_bool(__short8, __short8);
__bool16 __OVBIF __cmp_lt_bool(__short16, __short16);
#if __C7X_VEC_SIZE_BITS__ == 512
__bool32 __OVBIF __cmp_lt_bool(__short32, __short32);
#endif
/*
VCMPGTUH
*/
__bool2 __OVBIF __cmp_lt_bool(__ushort2, __ushort2);
__bool3 __OVBIF __cmp_lt_bool(__ushort3, __ushort3);
__bool4 __OVBIF __cmp_lt_bool(__ushort4, __ushort4);
__bool8 __OVBIF __cmp_lt_bool(__ushort8, __ushort8);
__bool16 __OVBIF __cmp_lt_bool(__ushort16, __ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
__bool32 __OVBIF __cmp_lt_bool(__ushort32, __ushort32);
#endif
/*
VCMPGTW
*/
__bool2 __OVBIF __cmp_lt_bool(__int2, __int2);
__bool3 __OVBIF __cmp_lt_bool(__int3, __int3);
__bool4 __OVBIF __cmp_lt_bool(__int4, __int4);
__bool8 __OVBIF __cmp_lt_bool(__int8, __int8);
#if __C7X_VEC_SIZE_BITS__ == 512
__bool16 __OVBIF __cmp_lt_bool(__int16, __int16);
#endif
/*
VCMPGTUW
*/
__bool2 __OVBIF __cmp_lt_bool(__uint2, __uint2);
__bool3 __OVBIF __cmp_lt_bool(__uint3, __uint3);
__bool4 __OVBIF __cmp_lt_bool(__uint4, __uint4);
__bool8 __OVBIF __cmp_lt_bool(__uint8, __uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
__bool16 __OVBIF __cmp_lt_bool(__uint16, __uint16);
#endif
/*
VCMPLTSP
*/
__bool2 __OVBIF __cmp_lt_bool(__float2, __float2);
__bool3 __OVBIF __cmp_lt_bool(__float3, __float3);
__bool4 __OVBIF __cmp_lt_bool(__float4, __float4);
__bool8 __OVBIF __cmp_lt_bool(__float8, __float8);
#if __C7X_VEC_SIZE_BITS__ == 512
__bool16 __OVBIF __cmp_lt_bool(__float16, __float16);
#endif
/*
VCMPGTD
*/
__bool2 __OVBIF __cmp_lt_bool(__long2, __long2);
__bool3 __OVBIF __cmp_lt_bool(__long3, __long3);
__bool4 __OVBIF __cmp_lt_bool(__long4, __long4);
#if __C7X_VEC_SIZE_BITS__ == 512
__bool8 __OVBIF __cmp_lt_bool(__long8, __long8);
#endif
/*
VCMPGTUD
*/
__bool2 __OVBIF __cmp_lt_bool(__ulong2, __ulong2);
__bool3 __OVBIF __cmp_lt_bool(__ulong3, __ulong3);
__bool4 __OVBIF __cmp_lt_bool(__ulong4, __ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
__bool8 __OVBIF __cmp_lt_bool(__ulong8, __ulong8);
#endif
/*
VCMPLTDP
*/
__bool2 __OVBIF __cmp_lt_bool(__double2, __double2);
__bool3 __OVBIF __cmp_lt_bool(__double3, __double3);
__bool4 __OVBIF __cmp_lt_bool(__double4, __double4);
#if __C7X_VEC_SIZE_BITS__ == 512
__bool8 __OVBIF __cmp_lt_bool(__double8, __double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __cmpy_conj_ext                                                        */
/*----------------------------------------------------------------------------*/
/*
VCCMPYHW
*/
__cint __OVBIF __cmpy_conj_ext(__cshort, __cshort);
__cint2 __OVBIF __cmpy_conj_ext(__cshort2, __cshort2);
__cint4 __OVBIF __cmpy_conj_ext(__cshort4, __cshort4);
#if __C7X_VEC_SIZE_BITS__ == 512
__cint8 __OVBIF __cmpy_conj_ext(__cshort8, __cshort8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __cmpy_conj_fx                                                         */
/*----------------------------------------------------------------------------*/
/*
VCCMPYR1HH
*/
__cshort __OVBIF __cmpy_conj_fx(__cshort, __cshort);
__cshort2 __OVBIF __cmpy_conj_fx(__cshort2, __cshort2);
__cshort4 __OVBIF __cmpy_conj_fx(__cshort4, __cshort4);
__cshort8 __OVBIF __cmpy_conj_fx(__cshort8, __cshort8);
#if __C7X_VEC_SIZE_BITS__ == 512
__cshort16 __OVBIF __cmpy_conj_fx(__cshort16, __cshort16);
#endif
/*
VCCMPYR1WW
*/
__cint __OVBIF __cmpy_conj_fx(__cint, __cint);
__cint2 __OVBIF __cmpy_conj_fx(__cint2, __cint2);
__cint4 __OVBIF __cmpy_conj_fx(__cint4, __cint4);
#if __C7X_VEC_SIZE_BITS__ == 512
__cint8 __OVBIF __cmpy_conj_fx(__cint8, __cint8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __cmpy_ext                                                             */
/*----------------------------------------------------------------------------*/
/*
VCMPYHW
*/
__cint __OVBIF __cmpy_ext(__cshort, __cshort);
__cint2 __OVBIF __cmpy_ext(__cshort2, __cshort2);
__cint4 __OVBIF __cmpy_ext(__cshort4, __cshort4);
#if __C7X_VEC_SIZE_BITS__ == 512
__cint8 __OVBIF __cmpy_ext(__cshort8, __cshort8);
#endif
/*
VCMPYSP
*/
__float4 __OVBIF __cmpy_ext(__cfloat, __cfloat);
__float8 __OVBIF __cmpy_ext(__cfloat2, __cfloat2);
#if __C7X_VEC_SIZE_BITS__ == 512
__float16 __OVBIF __cmpy_ext(__cfloat4, __cfloat4);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __cmpy_fx                                                              */
/*----------------------------------------------------------------------------*/
/*
VCMPYR1HH
*/
__cshort __OVBIF __cmpy_fx(__cshort, __cshort);
__cshort2 __OVBIF __cmpy_fx(__cshort2, __cshort2);
__cshort4 __OVBIF __cmpy_fx(__cshort4, __cshort4);
__cshort8 __OVBIF __cmpy_fx(__cshort8, __cshort8);
#if __C7X_VEC_SIZE_BITS__ == 512
__cshort16 __OVBIF __cmpy_fx(__cshort16, __cshort16);
#endif
/*
VCMPYR1WW
*/
__cint __OVBIF __cmpy_fx(__cint, __cint);
__cint2 __OVBIF __cmpy_fx(__cint2, __cint2);
__cint4 __OVBIF __cmpy_fx(__cint4, __cint4);
#if __C7X_VEC_SIZE_BITS__ == 512
__cint8 __OVBIF __cmpy_fx(__cint8, __cint8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __cmpyr_fx                                                             */
/*----------------------------------------------------------------------------*/
/*
VCMPYRHH
*/
__cshort __OVBIF __cmpyr_fx(__cshort, __cshort);
__cshort2 __OVBIF __cmpyr_fx(__cshort2, __cshort2);
__cshort4 __OVBIF __cmpyr_fx(__cshort4, __cshort4);
__cshort8 __OVBIF __cmpyr_fx(__cshort8, __cshort8);
#if __C7X_VEC_SIZE_BITS__ == 512
__cshort16 __OVBIF __cmpyr_fx(__cshort16, __cshort16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __compress_set_bits_left                                               */
/*----------------------------------------------------------------------------*/
/*
COMPRESSL
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__bool32 __OVBIF __compress_set_bits_left(__bool32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__bool64 __OVBIF __compress_set_bits_left(__bool64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __compress_set_bits_right                                              */
/*----------------------------------------------------------------------------*/
/*
COMPRESSR
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__bool32 __OVBIF __compress_set_bits_right(__bool32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__bool64 __OVBIF __compress_set_bits_right(__bool64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __conj_cmatmpy_ext                                                     */
/*----------------------------------------------------------------------------*/
/*
VCCMATMPYHW
*/
__cint2 __OVBIF __conj_cmatmpy_ext(__cshort2, __cshort4);
__cint4 __OVBIF __conj_cmatmpy_ext(__cshort4, __cshort8);
#if __C7X_VEC_SIZE_BITS__ == 512
__cint8 __OVBIF __conj_cmatmpy_ext(__cshort8, __cshort16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __conj_cmatmpy_fx                                                      */
/*----------------------------------------------------------------------------*/
/*
VCCMATMPYR1HH
*/
__cshort2 __OVBIF __conj_cmatmpy_fx(__cshort2, __cshort4);
__cshort4 __OVBIF __conj_cmatmpy_fx(__cshort4, __cshort8);
#if __C7X_VEC_SIZE_BITS__ == 512
__cshort8 __OVBIF __conj_cmatmpy_fx(__cshort8, __cshort16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __crot270                                                              */
/*----------------------------------------------------------------------------*/
/*
VCROT270H
*/
__cshort __OVBIF __crot270(__cshort);
__cshort2 __OVBIF __crot270(__cshort2);
__cshort4 __OVBIF __crot270(__cshort4);
__cshort8 __OVBIF __crot270(__cshort8);
#if __C7X_VEC_SIZE_BITS__ == 512
__cshort16 __OVBIF __crot270(__cshort16);
#endif
/*
VCROT270W
*/
__cint __OVBIF __crot270(__cint);
__cint2 __OVBIF __crot270(__cint2);
__cint4 __OVBIF __crot270(__cint4);
#if __C7X_VEC_SIZE_BITS__ == 512
__cint8 __OVBIF __crot270(__cint8);
#endif
/*
VCROT270SP
*/
__cfloat __OVBIF __crot270(__cfloat);
__cfloat2 __OVBIF __crot270(__cfloat2);
__cfloat4 __OVBIF __crot270(__cfloat4);
#if __C7X_VEC_SIZE_BITS__ == 512
__cfloat8 __OVBIF __crot270(__cfloat8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __crot90                                                               */
/*----------------------------------------------------------------------------*/
/*
VCROT90H
*/
__cshort __OVBIF __crot90(__cshort);
__cshort2 __OVBIF __crot90(__cshort2);
__cshort4 __OVBIF __crot90(__cshort4);
__cshort8 __OVBIF __crot90(__cshort8);
#if __C7X_VEC_SIZE_BITS__ == 512
__cshort16 __OVBIF __crot90(__cshort16);
#endif
/*
VCROT90W
*/
__cint __OVBIF __crot90(__cint);
__cint2 __OVBIF __crot90(__cint2);
__cint4 __OVBIF __crot90(__cint4);
#if __C7X_VEC_SIZE_BITS__ == 512
__cint8 __OVBIF __crot90(__cint8);
#endif
/*
VCROT90SP
*/
__cfloat __OVBIF __crot90(__cfloat);
__cfloat2 __OVBIF __crot90(__cfloat2);
__cfloat4 __OVBIF __crot90(__cfloat4);
#if __C7X_VEC_SIZE_BITS__ == 512
__cfloat8 __OVBIF __crot90(__cfloat8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __deal_bit                                                             */
/*----------------------------------------------------------------------------*/
/*
VBITDEALW
*/
int __OVBIF __deal_bit(int);
__int2 __OVBIF __deal_bit(__int2);
__int3 __OVBIF __deal_bit(__int3);
__int4 __OVBIF __deal_bit(__int4);
__int8 __OVBIF __deal_bit(__int8);
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __deal_bit(__int16);
#endif
__uint __OVBIF __deal_bit(__uint);
__uint2 __OVBIF __deal_bit(__uint2);
__uint3 __OVBIF __deal_bit(__uint3);
__uint4 __OVBIF __deal_bit(__uint4);
__uint8 __OVBIF __deal_bit(__uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __deal_bit(__uint16);
#endif
/*
VBITDEALD
*/
long __OVBIF __deal_bit(long);
__long2 __OVBIF __deal_bit(__long2);
__long3 __OVBIF __deal_bit(__long3);
__long4 __OVBIF __deal_bit(__long4);
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __deal_bit(__long8);
#endif
__ulong __OVBIF __deal_bit(__ulong);
__ulong2 __OVBIF __deal_bit(__ulong2);
__ulong3 __OVBIF __deal_bit(__ulong3);
__ulong4 __OVBIF __deal_bit(__ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __deal_bit(__ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __deal_stride2                                                         */
/*----------------------------------------------------------------------------*/
/*
VDEAL2B
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __OVBIF __deal_stride2(__char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __deal_stride2(__char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __OVBIF __deal_stride2(__uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __deal_stride2(__uchar64);
#endif
/*
VDEAL2H
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cchar16 __OVBIF __deal_stride2(__cchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cchar32 __OVBIF __deal_stride2(__cchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __OVBIF __deal_stride2(__short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __deal_stride2(__short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __OVBIF __deal_stride2(__ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __deal_stride2(__ushort32);
#endif
/*
VDEAL2W
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cshort8 __OVBIF __deal_stride2(__cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cshort16 __OVBIF __deal_stride2(__cshort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __OVBIF __deal_stride2(__int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __deal_stride2(__int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __OVBIF __deal_stride2(__uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __deal_stride2(__uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__float8 __OVBIF __deal_stride2(__float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__float16 __OVBIF __deal_stride2(__float16);
#endif
/*
VDEAL2D
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cint4 __OVBIF __deal_stride2(__cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cint8 __OVBIF __deal_stride2(__cint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cfloat4 __OVBIF __deal_stride2(__cfloat4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cfloat8 __OVBIF __deal_stride2(__cfloat8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __OVBIF __deal_stride2(__long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __deal_stride2(__long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __OVBIF __deal_stride2(__ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __deal_stride2(__ulong8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__double4 __OVBIF __deal_stride2(__double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__double8 __OVBIF __deal_stride2(__double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __deal_stride4                                                         */
/*----------------------------------------------------------------------------*/
/*
VDEAL4B
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __OVBIF __deal_stride4(__char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __deal_stride4(__char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __OVBIF __deal_stride4(__uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __deal_stride4(__uchar64);
#endif
/*
VDEAL4H
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cchar16 __OVBIF __deal_stride4(__cchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cchar32 __OVBIF __deal_stride4(__cchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __OVBIF __deal_stride4(__short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __deal_stride4(__short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __OVBIF __deal_stride4(__ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __deal_stride4(__ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __decimate                                                             */
/*----------------------------------------------------------------------------*/
/*
DECIMATEB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__bool32 __BIF __decimate(__bool32, __bool32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__bool64 __BIF __decimate(__bool64, __bool64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __dot_posneg128_mask                                                   */
/*----------------------------------------------------------------------------*/
/*
VDOTPMPN16W8D
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __BIF __dot_posneg128_mask(__ushort32, __ushort8, __int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __dot_posneg128_mask_ext                                               */
/*----------------------------------------------------------------------------*/
/*
VDOTPMPNU16W8D
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __BIF __dot_posneg128_mask_ext(__ushort32, __ushort8, __uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __dot_posneg256_mask                                                   */
/*----------------------------------------------------------------------------*/
/*
VDOTPMPN16H16W
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __dot_posneg256_mask(__ushort32, __ushort16, __short16);
#endif
/*
VDOTPMPNU16H16W
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __dot_posneg256_mask(__ushort32, __ushort16, __ushort16);
#endif
/*
VDOTPMPN32H8W
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__int8 __OVBIF __dot_posneg256_mask(__uint8, __uint8, __short32);
#endif
/*
VDOTPMPNU32H8W
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__uint8 __OVBIF __dot_posneg256_mask(__uint8, __uint8, __ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __dot_posneg512_mask                                                   */
/*----------------------------------------------------------------------------*/
/*
VDOTPMPN16B32H
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __dot_posneg512_mask(__ushort32, __ushort32, __char16);
#endif
/*
VDOTPMPN32B16H
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__short16 __OVBIF __dot_posneg512_mask(__uint16, __uint16, __char32);
#endif
/*
VDOTPMPNU32B16H
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort16 __OVBIF __dot_posneg512_mask(__uint16, __uint16, __uchar32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __dot_posneg512_mask_ext                                               */
/*----------------------------------------------------------------------------*/
/*
VDOTPMPN32B16W
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __dot_posneg512_mask_ext(__uint16, __uint16, __char32);
#endif
/*
VDOTPMPNU32B16W
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __dot_posneg512_mask_ext(__uint16, __uint16, __uchar32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __dotp2                                                                */
/*----------------------------------------------------------------------------*/
/*
VDOTP2SUBH
*/
short __OVBIF __dotp2(__char2, __uchar2);
__short2 __OVBIF __dotp2(__char4, __uchar4);
__short4 __OVBIF __dotp2(__char8, __uchar8);
__short8 __OVBIF __dotp2(__char16, __uchar16);
__short16 __OVBIF __dotp2(__char32, __uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __dotp2(__char64, __uchar64);
#endif
/*
VDOTP2UBH
*/
__ushort __OVBIF __dotp2(__uchar2, __uchar2);
__ushort2 __OVBIF __dotp2(__uchar4, __uchar4);
__ushort4 __OVBIF __dotp2(__uchar8, __uchar8);
__ushort8 __OVBIF __dotp2(__uchar16, __uchar16);
__ushort16 __OVBIF __dotp2(__uchar32, __uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __dotp2(__uchar64, __uchar64);
#endif
/*
VDOTP2HW
*/
int __OVBIF __dotp2(__short2, __short2);
__int2 __OVBIF __dotp2(__short4, __short4);
__int4 __OVBIF __dotp2(__short8, __short8);
__int8 __OVBIF __dotp2(__short16, __short16);
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __dotp2(__short32, __short32);
#endif
/*
VDOTP2SUHW
*/
int __OVBIF __dotp2(__short2, __ushort2);
__int2 __OVBIF __dotp2(__short4, __ushort4);
__int4 __OVBIF __dotp2(__short8, __ushort8);
__int8 __OVBIF __dotp2(__short16, __ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __dotp2(__short32, __ushort32);
#endif
/*
VDOTP2UHW
*/
__uint __OVBIF __dotp2(__ushort2, __ushort2);
__uint2 __OVBIF __dotp2(__ushort4, __ushort4);
__uint4 __OVBIF __dotp2(__ushort8, __ushort8);
__uint8 __OVBIF __dotp2(__ushort16, __ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __dotp2(__ushort32, __ushort32);
#endif
/*
VCDOTP2HW
*/
__cint __OVBIF __dotp2(__cshort2, __cshort2);
__cint2 __OVBIF __dotp2(__cshort4, __cshort4);
__cint4 __OVBIF __dotp2(__cshort8, __cshort8);
#if __C7X_VEC_SIZE_BITS__ == 512
__cint8 __OVBIF __dotp2(__cshort16, __cshort16);
#endif
/*
VDOTP2WD
*/
long __OVBIF __dotp2(__int2, __int2);
__long2 __OVBIF __dotp2(__int4, __int4);
__long4 __OVBIF __dotp2(__int8, __int8);
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __dotp2(__int16, __int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __dotp2_conj                                                           */
/*----------------------------------------------------------------------------*/
/*
VCCDOTP2HW
*/
__cint __OVBIF __dotp2_conj(__cshort2, __cshort2);
__cint2 __OVBIF __dotp2_conj(__cshort4, __cshort4);
__cint4 __OVBIF __dotp2_conj(__cshort8, __cshort8);
#if __C7X_VEC_SIZE_BITS__ == 512
__cint8 __OVBIF __dotp2_conj(__cshort16, __cshort16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __dotp2_cross                                                          */
/*----------------------------------------------------------------------------*/
/*
VDOTP2XWD
*/
long __OVBIF __dotp2_cross(__int2, __int2);
__long2 __OVBIF __dotp2_cross(__int4, __int4);
__long4 __OVBIF __dotp2_cross(__int8, __int8);
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __dotp2_cross(__int16, __int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __dotp2_cross_negate                                                   */
/*----------------------------------------------------------------------------*/
/*
VDOTP2NXWD
*/
long __OVBIF __dotp2_cross_negate(__int2, __int2);
__long2 __OVBIF __dotp2_cross_negate(__int4, __int4);
__long4 __OVBIF __dotp2_cross_negate(__int8, __int8);
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __dotp2_cross_negate(__int16, __int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __dotp2_ext                                                            */
/*----------------------------------------------------------------------------*/
/*
VDOTP2HD
*/
long __OVBIF __dotp2_ext(__short2, __short2);
__long2 __OVBIF __dotp2_ext(__short4, __short4);
__long4 __OVBIF __dotp2_ext(__short8, __short8);
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __dotp2_ext(__short16, __short16);
#endif
/*
VDOTP2SUHD
*/
long __OVBIF __dotp2_ext(__short2, __ushort2);
__long2 __OVBIF __dotp2_ext(__short4, __ushort4);
__long4 __OVBIF __dotp2_ext(__short8, __ushort8);
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __dotp2_ext(__short16, __ushort16);
#endif
/*
VDOTP2UHD
*/
__ulong __OVBIF __dotp2_ext(__ushort2, __ushort2);
__ulong2 __OVBIF __dotp2_ext(__ushort4, __ushort4);
__ulong4 __OVBIF __dotp2_ext(__ushort8, __ushort8);
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __dotp2_ext(__ushort16, __ushort16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __dotp2_fx_ext                                                         */
/*----------------------------------------------------------------------------*/
/*
C6DOTP2RSUHW
*/
int __BIF __dotp2_fx_ext(__short2, __ushort2);

/*----------------------------------------------------------------------------*/
/* ID: __dotp2_negate                                                         */
/*----------------------------------------------------------------------------*/
/*
C6DOTPN2HW
*/
int __OVBIF __dotp2_negate(__short2, __short2);
/*
C6DOTPN2RSUHH
*/
int __OVBIF __dotp2_negate(__short2, __ushort2);
/*
VDOTP2NWD
*/
long __OVBIF __dotp2_negate(__int2, __int2);
__long2 __OVBIF __dotp2_negate(__int4, __int4);
__long4 __OVBIF __dotp2_negate(__int8, __int8);
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __dotp2_negate(__int16, __int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __dotp4                                                                */
/*----------------------------------------------------------------------------*/
/*
VDOTP4HW
*/
int __OVBIF __dotp4(__short4, __short4);
__int2 __OVBIF __dotp4(__short8, __short8);
__int4 __OVBIF __dotp4(__short16, __short16);
#if __C7X_VEC_SIZE_BITS__ == 512
__int8 __OVBIF __dotp4(__short32, __short32);
#endif
/*
VDOTP4SUHW
*/
int __OVBIF __dotp4(__short4, __ushort4);
__int2 __OVBIF __dotp4(__short8, __ushort8);
__int4 __OVBIF __dotp4(__short16, __ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
__int8 __OVBIF __dotp4(__short32, __ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __dotp4_ext                                                            */
/*----------------------------------------------------------------------------*/
/*
VDOTP4SUBW
*/
int __OVBIF __dotp4_ext(__char4, __uchar4);
__int2 __OVBIF __dotp4_ext(__char8, __uchar8);
__int4 __OVBIF __dotp4_ext(__char16, __uchar16);
__int8 __OVBIF __dotp4_ext(__char32, __uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __dotp4_ext(__char64, __uchar64);
#endif
/*
VDOTP4UBW
*/
__uint __OVBIF __dotp4_ext(__uchar4, __uchar4);
__uint2 __OVBIF __dotp4_ext(__uchar8, __uchar8);
__uint4 __OVBIF __dotp4_ext(__uchar16, __uchar16);
__uint8 __OVBIF __dotp4_ext(__uchar32, __uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __dotp4_ext(__uchar64, __uchar64);
#endif
/*
VDOTP4HD
*/
long __OVBIF __dotp4_ext(__short4, __short4);
__long2 __OVBIF __dotp4_ext(__short8, __short8);
__long4 __OVBIF __dotp4_ext(__short16, __short16);
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __dotp4_ext(__short32, __short32);
#endif
/*
VDOTP4SUHD
*/
long __OVBIF __dotp4_ext(__short4, __ushort4);
__long2 __OVBIF __dotp4_ext(__short8, __ushort8);
__long4 __OVBIF __dotp4_ext(__short16, __ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __dotp4_ext(__short32, __ushort32);
#endif
/*
VDOTP4UHD
*/
__ulong __OVBIF __dotp4_ext(__ushort4, __ushort4);
__ulong2 __OVBIF __dotp4_ext(__ushort8, __ushort8);
__ulong4 __OVBIF __dotp4_ext(__ushort16, __ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __dotp4_ext(__ushort32, __ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __dotp8_ext                                                            */
/*----------------------------------------------------------------------------*/
/*
VDOTP8SUBW
*/
__int2 __OVBIF __dotp8_ext(__char8, __uchar8);
__int4 __OVBIF __dotp8_ext(__char16, __uchar16);
__int8 __OVBIF __dotp8_ext(__char32, __uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __dotp8_ext(__char64, __uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __double_to_float                                                      */
/*----------------------------------------------------------------------------*/
/*
VDPSP
*/
__float2 __OVBIF __double_to_float(double);
__float4 __OVBIF __double_to_float(__double2);
__float8 __OVBIF __double_to_float(__double4);
#if __C7X_VEC_SIZE_BITS__ == 512
__float16 __OVBIF __double_to_float(__double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __double_to_int                                                        */
/*----------------------------------------------------------------------------*/
/*
VDPINT
*/
__int2 __OVBIF __double_to_int(double);
__int4 __OVBIF __double_to_int(__double2);
__int8 __OVBIF __double_to_int(__double4);
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __double_to_int(__double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __double_to_int_rtz                                                    */
/*----------------------------------------------------------------------------*/
/*
VDPTRUNC
*/
__int2 __OVBIF __double_to_int_rtz(double);
__int4 __OVBIF __double_to_int_rtz(__double2);
__int8 __OVBIF __double_to_int_rtz(__double4);
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __double_to_int_rtz(__double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __dual_horizontal_add_skip1                                            */
/*----------------------------------------------------------------------------*/
/*
VHADDEOW4D
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__long4 __OVBIF __dual_horizontal_add_skip1(__int16, __int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __OVBIF __dual_horizontal_add_skip1(__int8, __int8);
#endif
/*
VHADDUEOW4D
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong4 __OVBIF __dual_horizontal_add_skip1(__uint16, __uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __OVBIF __dual_horizontal_add_skip1(__uint8, __uint8);
#endif
/*
VHADDEOW4D
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__clong2 __OVBIF __dual_horizontal_add_skip1(__cint8, __cint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__clong2 __OVBIF __dual_horizontal_add_skip1(__cint4, __cint4);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __dual_sort_lo_asc_hi_asc                                              */
/*----------------------------------------------------------------------------*/
/*
VDSORTIIH
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__short16 __OVBIF __dual_sort_lo_asc_hi_asc(__short16);
__short32 __OVBIF __dual_sort_lo_asc_hi_asc(__short32);
#endif
/*
VDSORTIIUH
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort16 __OVBIF __dual_sort_lo_asc_hi_asc(__ushort16);
__ushort32 __OVBIF __dual_sort_lo_asc_hi_asc(__ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __dual_sort_lo_asc_hi_asc_perm                                         */
/*----------------------------------------------------------------------------*/
/*
VDSORTPIIH
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar32 __OVBIF __dual_sort_lo_asc_hi_asc_perm(__short16);
__uchar64 __OVBIF __dual_sort_lo_asc_hi_asc_perm(__short32);
#endif
/*
VDSORTPIIUH
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar32 __OVBIF __dual_sort_lo_asc_hi_asc_perm(__ushort16);
__uchar64 __OVBIF __dual_sort_lo_asc_hi_asc_perm(__ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __dual_sort_lo_asc_hi_desc                                             */
/*----------------------------------------------------------------------------*/
/*
VDSORTIDH
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __dual_sort_lo_asc_hi_desc(__short32);
#endif
/*
VDSORTIDUH
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __dual_sort_lo_asc_hi_desc(__ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __dual_sort_lo_asc_hi_desc_perm                                        */
/*----------------------------------------------------------------------------*/
/*
VDSORTPIDH
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __dual_sort_lo_asc_hi_desc_perm(__short32);
#endif
/*
VDSORTPIDUH
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __dual_sort_lo_asc_hi_desc_perm(__ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __dual_sort_lo_desc_hi_asc                                             */
/*----------------------------------------------------------------------------*/
/*
VDSORTDIH
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __dual_sort_lo_desc_hi_asc(__short32);
#endif
/*
VDSORTDIUH
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __dual_sort_lo_desc_hi_asc(__ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __dual_sort_lo_desc_hi_asc_perm                                        */
/*----------------------------------------------------------------------------*/
/*
VDSORTPDIH
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __dual_sort_lo_desc_hi_asc_perm(__short32);
#endif
/*
VDSORTPDIUH
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __dual_sort_lo_desc_hi_asc_perm(__ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __dual_sort_lo_desc_hi_desc                                            */
/*----------------------------------------------------------------------------*/
/*
VDSORTDDH
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__short16 __OVBIF __dual_sort_lo_desc_hi_desc(__short16);
__short32 __OVBIF __dual_sort_lo_desc_hi_desc(__short32);
#endif
/*
VDSORTDDUH
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort16 __OVBIF __dual_sort_lo_desc_hi_desc(__ushort16);
__ushort32 __OVBIF __dual_sort_lo_desc_hi_desc(__ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __dual_sort_lo_desc_hi_desc_perm                                       */
/*----------------------------------------------------------------------------*/
/*
VDSORTPDDH
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar32 __OVBIF __dual_sort_lo_desc_hi_desc_perm(__short16);
__uchar64 __OVBIF __dual_sort_lo_desc_hi_desc_perm(__short32);
#endif
/*
VDSORTPDDUH
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar32 __OVBIF __dual_sort_lo_desc_hi_desc_perm(__ushort16);
__uchar64 __OVBIF __dual_sort_lo_desc_hi_desc_perm(__ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __duplicate                                                            */
/*----------------------------------------------------------------------------*/
/*
VDUPB
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __duplicate(signed char);
/*
__char64 __OVBIF __duplicate(signed char __CST(-128, 127));
*/
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __OVBIF __duplicate(signed char);
/*
__char32 __OVBIF __duplicate(signed char __CST(-128, 127));
*/
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __duplicate(__uchar);
/*
__uchar64 __OVBIF __duplicate(__uchar __CST(0, 255));
*/
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __OVBIF __duplicate(__uchar);
/*
__uchar32 __OVBIF __duplicate(__uchar __CST(0, 255));
*/
#endif
/*
VDUPH
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__cchar32 __OVBIF __duplicate(__cchar);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cchar16 __OVBIF __duplicate(__cchar);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __duplicate(short);
/*
__short32 __OVBIF __duplicate(short __CST(-32768, 32767));
*/
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __OVBIF __duplicate(short);
/*
__short16 __OVBIF __duplicate(short __CST(-32768, 32767));
*/
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __duplicate(__ushort);
/*
__ushort32 __OVBIF __duplicate(__ushort __CST(0, 65535));
*/
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __OVBIF __duplicate(__ushort);
/*
__ushort16 __OVBIF __duplicate(__ushort __CST(0, 65535));
*/
#endif
/*
VDUPW
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__cshort16 __OVBIF __duplicate(__cshort);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cshort8 __OVBIF __duplicate(__cshort);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __duplicate(int);
/*
__int16 __OVBIF __duplicate(int __CST(-2147483648, 2147483647));
*/
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __OVBIF __duplicate(int);
/*
__int8 __OVBIF __duplicate(int __CST(-2147483648, 2147483647));
*/
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __duplicate(__uint);
/*
__uint16 __OVBIF __duplicate(__uint __CST(0, 4294967295));
*/
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __OVBIF __duplicate(__uint);
/*
__uint8 __OVBIF __duplicate(__uint __CST(0, 4294967295));
*/
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__float16 __OVBIF __duplicate(float);
/*
__float16 __OVBIF __duplicate(float k);
*/
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__float8 __OVBIF __duplicate(float);
/*
__float8 __OVBIF __duplicate(float k);
*/
#endif
/*
VDUPD
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__cint8 __OVBIF __duplicate(__cint);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cint4 __OVBIF __duplicate(__cint);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cfloat8 __OVBIF __duplicate(__cfloat);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cfloat4 __OVBIF __duplicate(__cfloat);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __duplicate(long);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __OVBIF __duplicate(long);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __duplicate(__ulong);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __OVBIF __duplicate(__ulong);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__double8 __OVBIF __duplicate(double);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__double4 __OVBIF __duplicate(double);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __duplicate16                                                          */
/*----------------------------------------------------------------------------*/
/*
VDUP16B
*/
__char16 __OVBIF __duplicate16(signed char);
__char32 __OVBIF __duplicate16(__char2);
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __duplicate16(__char4);
#endif
__uchar16 __OVBIF __duplicate16(__uchar);
__uchar32 __OVBIF __duplicate16(__uchar2);
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __duplicate16(__uchar4);
#endif
/*
VDUP16H
*/
__cchar16 __OVBIF __duplicate16(__cchar);
#if __C7X_VEC_SIZE_BITS__ == 512
__cchar32 __OVBIF __duplicate16(__cchar2);
#endif
__short16 __OVBIF __duplicate16(short);
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __duplicate16(__short2);
#endif
__ushort16 __OVBIF __duplicate16(__ushort);
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __duplicate16(__ushort2);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __duplicate2                                                           */
/*----------------------------------------------------------------------------*/
/*
VDUP2B
*/
__char2 __OVBIF __duplicate2(signed char);
__char4 __OVBIF __duplicate2(__char2);
__char8 __OVBIF __duplicate2(__char4);
__char16 __OVBIF __duplicate2(__char8);
__char32 __OVBIF __duplicate2(__char16);
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __duplicate2(__char32);
#endif
__uchar2 __OVBIF __duplicate2(__uchar);
__uchar4 __OVBIF __duplicate2(__uchar2);
__uchar8 __OVBIF __duplicate2(__uchar4);
__uchar16 __OVBIF __duplicate2(__uchar8);
__uchar32 __OVBIF __duplicate2(__uchar16);
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __duplicate2(__uchar32);
#endif
/*
VDUP2H
*/
__cchar2 __OVBIF __duplicate2(__cchar);
__cchar4 __OVBIF __duplicate2(__cchar2);
__cchar8 __OVBIF __duplicate2(__cchar4);
__cchar16 __OVBIF __duplicate2(__cchar8);
#if __C7X_VEC_SIZE_BITS__ == 512
__cchar32 __OVBIF __duplicate2(__cchar16);
#endif
__short2 __OVBIF __duplicate2(short);
__short4 __OVBIF __duplicate2(__short2);
__short8 __OVBIF __duplicate2(__short4);
__short16 __OVBIF __duplicate2(__short8);
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __duplicate2(__short16);
#endif
__ushort2 __OVBIF __duplicate2(__ushort);
__ushort4 __OVBIF __duplicate2(__ushort2);
__ushort8 __OVBIF __duplicate2(__ushort4);
__ushort16 __OVBIF __duplicate2(__ushort8);
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __duplicate2(__ushort16);
#endif
/*
VDUP2W
*/
__cshort2 __OVBIF __duplicate2(__cshort);
__cshort4 __OVBIF __duplicate2(__cshort2);
__cshort8 __OVBIF __duplicate2(__cshort4);
#if __C7X_VEC_SIZE_BITS__ == 512
__cshort16 __OVBIF __duplicate2(__cshort8);
#endif
__int2 __OVBIF __duplicate2(int);
__int4 __OVBIF __duplicate2(__int2);
__int8 __OVBIF __duplicate2(__int4);
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __duplicate2(__int8);
#endif
__uint2 __OVBIF __duplicate2(__uint);
__uint4 __OVBIF __duplicate2(__uint2);
__uint8 __OVBIF __duplicate2(__uint4);
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __duplicate2(__uint8);
#endif
__float2 __OVBIF __duplicate2(float);
__float4 __OVBIF __duplicate2(__float2);
__float8 __OVBIF __duplicate2(__float4);
#if __C7X_VEC_SIZE_BITS__ == 512
__float16 __OVBIF __duplicate2(__float8);
#endif
/*
VDUP2D
*/
__cint2 __OVBIF __duplicate2(__cint);
__cint4 __OVBIF __duplicate2(__cint2);
#if __C7X_VEC_SIZE_BITS__ == 512
__cint8 __OVBIF __duplicate2(__cint4);
#endif
__cfloat2 __OVBIF __duplicate2(__cfloat);
__cfloat4 __OVBIF __duplicate2(__cfloat2);
#if __C7X_VEC_SIZE_BITS__ == 512
__cfloat8 __OVBIF __duplicate2(__cfloat4);
#endif
__long2 __OVBIF __duplicate2(long);
__long4 __OVBIF __duplicate2(__long2);
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __duplicate2(__long4);
#endif
__ulong2 __OVBIF __duplicate2(__ulong);
__ulong4 __OVBIF __duplicate2(__ulong2);
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __duplicate2(__ulong4);
#endif
__double2 __OVBIF __duplicate2(double);
__double4 __OVBIF __duplicate2(__double2);
#if __C7X_VEC_SIZE_BITS__ == 512
__double8 __OVBIF __duplicate2(__double4);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __duplicate32                                                          */
/*----------------------------------------------------------------------------*/
/*
VDUP32B
*/
__char32 __OVBIF __duplicate32(signed char);
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __duplicate32(__char2);
#endif
__uchar32 __OVBIF __duplicate32(__uchar);
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __duplicate32(__uchar2);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __duplicate4                                                           */
/*----------------------------------------------------------------------------*/
/*
VDUP4B
*/
__char4 __OVBIF __duplicate4(signed char);
__char8 __OVBIF __duplicate4(__char2);
__char16 __OVBIF __duplicate4(__char4);
__char32 __OVBIF __duplicate4(__char8);
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __duplicate4(__char16);
#endif
__uchar4 __OVBIF __duplicate4(__uchar);
__uchar8 __OVBIF __duplicate4(__uchar2);
__uchar16 __OVBIF __duplicate4(__uchar4);
__uchar32 __OVBIF __duplicate4(__uchar8);
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __duplicate4(__uchar16);
#endif
/*
VDUP4H
*/
__cchar4 __OVBIF __duplicate4(__cchar);
__cchar8 __OVBIF __duplicate4(__cchar2);
__cchar16 __OVBIF __duplicate4(__cchar4);
#if __C7X_VEC_SIZE_BITS__ == 512
__cchar32 __OVBIF __duplicate4(__cchar8);
#endif
__short4 __OVBIF __duplicate4(short);
__short8 __OVBIF __duplicate4(__short2);
__short16 __OVBIF __duplicate4(__short4);
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __duplicate4(__short8);
#endif
__ushort4 __OVBIF __duplicate4(__ushort);
__ushort8 __OVBIF __duplicate4(__ushort2);
__ushort16 __OVBIF __duplicate4(__ushort4);
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __duplicate4(__ushort8);
#endif
/*
VDUP4W
*/
__cshort4 __OVBIF __duplicate4(__cshort);
__cshort8 __OVBIF __duplicate4(__cshort2);
#if __C7X_VEC_SIZE_BITS__ == 512
__cshort16 __OVBIF __duplicate4(__cshort4);
#endif
__int4 __OVBIF __duplicate4(int);
__int8 __OVBIF __duplicate4(__int2);
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __duplicate4(__int4);
#endif
__uint4 __OVBIF __duplicate4(__uint);
__uint8 __OVBIF __duplicate4(__uint2);
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __duplicate4(__uint4);
#endif
__float4 __OVBIF __duplicate4(float);
__float8 __OVBIF __duplicate4(__float2);
#if __C7X_VEC_SIZE_BITS__ == 512
__float16 __OVBIF __duplicate4(__float4);
#endif
/*
VDUP4D
*/
__cint4 __OVBIF __duplicate4(__cint);
#if __C7X_VEC_SIZE_BITS__ == 512
__cint8 __OVBIF __duplicate4(__cint2);
#endif
__cfloat4 __OVBIF __duplicate4(__cfloat);
#if __C7X_VEC_SIZE_BITS__ == 512
__cfloat8 __OVBIF __duplicate4(__cfloat2);
#endif
__long4 __OVBIF __duplicate4(long);
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __duplicate4(__long2);
#endif
__ulong4 __OVBIF __duplicate4(__ulong);
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __duplicate4(__ulong2);
#endif
__double4 __OVBIF __duplicate4(double);
#if __C7X_VEC_SIZE_BITS__ == 512
__double8 __OVBIF __duplicate4(__double2);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __duplicate8                                                           */
/*----------------------------------------------------------------------------*/
/*
VDUP8B
*/
__char8 __OVBIF __duplicate8(signed char);
__char16 __OVBIF __duplicate8(__char2);
__char32 __OVBIF __duplicate8(__char4);
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __duplicate8(__char8);
#endif
__uchar8 __OVBIF __duplicate8(__uchar);
__uchar16 __OVBIF __duplicate8(__uchar2);
__uchar32 __OVBIF __duplicate8(__uchar4);
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __duplicate8(__uchar8);
#endif
/*
VDUP8H
*/
__cchar8 __OVBIF __duplicate8(__cchar);
__cchar16 __OVBIF __duplicate8(__cchar2);
#if __C7X_VEC_SIZE_BITS__ == 512
__cchar32 __OVBIF __duplicate8(__cchar4);
#endif
__short8 __OVBIF __duplicate8(short);
__short16 __OVBIF __duplicate8(__short2);
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __duplicate8(__short4);
#endif
__ushort8 __OVBIF __duplicate8(__ushort);
__ushort16 __OVBIF __duplicate8(__ushort2);
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __duplicate8(__ushort4);
#endif
/*
VDUP8W
*/
__cshort8 __OVBIF __duplicate8(__cshort);
#if __C7X_VEC_SIZE_BITS__ == 512
__cshort16 __OVBIF __duplicate8(__cshort2);
#endif
__int8 __OVBIF __duplicate8(int);
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __duplicate8(__int2);
#endif
__uint8 __OVBIF __duplicate8(__uint);
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __duplicate8(__uint2);
#endif
__float8 __OVBIF __duplicate8(float);
#if __C7X_VEC_SIZE_BITS__ == 512
__float16 __OVBIF __duplicate8(__float2);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __duplicate_pred_high                                                  */
/*----------------------------------------------------------------------------*/
/*
PDUPH2B
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__bool32 __BIF __duplicate_pred_high(__bool32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__bool64 __BIF __duplicate_pred_high(__bool64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __duplicate_pred_low                                                   */
/*----------------------------------------------------------------------------*/
/*
PDUPL2B
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__bool32 __BIF __duplicate_pred_low(__bool32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__bool64 __BIF __duplicate_pred_low(__bool64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __expand                                                               */
/*----------------------------------------------------------------------------*/
/*
VPXPND
*/
__char2 __OVBIF __expand(__bool2);
__char3 __OVBIF __expand(__bool3);
__char4 __OVBIF __expand(__bool4);
__char8 __OVBIF __expand(__bool8);
__char16 __OVBIF __expand(__bool16);
__char32 __OVBIF __expand(__bool32);
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __expand(__bool64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __expand_lsb_pack_char                                                 */
/*----------------------------------------------------------------------------*/
/*
XPND8B
*/
__char8 __OVBIF __expand_lsb_pack_char(signed char);
__uchar8 __OVBIF __expand_lsb_pack_char(__uchar);

/*----------------------------------------------------------------------------*/
/* ID: __expand_lsb_pack_short                                                */
/*----------------------------------------------------------------------------*/
/*
XPND4H
*/
__short4 __OVBIF __expand_lsb_pack_short(signed char);
__ushort4 __OVBIF __expand_lsb_pack_short(__uchar);

/*----------------------------------------------------------------------------*/
/* ID: __float_to_half_float                                                  */
/*----------------------------------------------------------------------------*/
/*
VSPHP
*/
__uint __OVBIF __float_to_half_float(float);
__uint2 __OVBIF __float_to_half_float(__float2);
__uint3 __OVBIF __float_to_half_float(__float3);
__uint4 __OVBIF __float_to_half_float(__float4);
__uint8 __OVBIF __float_to_half_float(__float8);
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __float_to_half_float(__float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __float_to_int                                                         */
/*----------------------------------------------------------------------------*/
/*
VSPINT
*/
int __OVBIF __float_to_int(float);
__int2 __OVBIF __float_to_int(__float2);
__int3 __OVBIF __float_to_int(__float3);
__int4 __OVBIF __float_to_int(__float4);
__int8 __OVBIF __float_to_int(__float8);
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __float_to_int(__float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __float_to_int_rtz                                                     */
/*----------------------------------------------------------------------------*/
/*
VSPTRUNC
*/
int __OVBIF __float_to_int_rtz(float);
__int2 __OVBIF __float_to_int_rtz(__float2);
__int3 __OVBIF __float_to_int_rtz(__float3);
__int4 __OVBIF __float_to_int_rtz(__float4);
__int8 __OVBIF __float_to_int_rtz(__float8);
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __float_to_int_rtz(__float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __float_to_short                                                       */
/*----------------------------------------------------------------------------*/
/*
VSPINTH
*/
__short2 __OVBIF __float_to_short(float);
__short4 __OVBIF __float_to_short(__float2);
__short8 __OVBIF __float_to_short(__float4);
__short16 __OVBIF __float_to_short(__float8);
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __float_to_short(__float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __get_vector_element                                                   */
/*----------------------------------------------------------------------------*/
/*
VGETB
*/
#if __C7X_VEC_SIZE_BITS__ == 512
signed char __OVBIF __get_vector_element(__char64, __uint);
/*
signed char __OVBIF __get_vector_element(__char64, __uint __CST(0, 63));
*/
#endif
signed char __OVBIF __get_vector_element(__char32, __uint);
/*
signed char __OVBIF __get_vector_element(__char32, __uint __CST(0, 63));
*/
signed char __OVBIF __get_vector_element(__char16, __uint);
/*
signed char __OVBIF __get_vector_element(__char16, __uint __CST(0, 63));
*/
signed char __OVBIF __get_vector_element(__char8, __uint);
/*
signed char __OVBIF __get_vector_element(__char8, __uint __CST(0, 63));
*/
signed char __OVBIF __get_vector_element(__char4, __uint);
/*
signed char __OVBIF __get_vector_element(__char4, __uint __CST(0, 63));
*/
signed char __OVBIF __get_vector_element(__char3, __uint);
/*
signed char __OVBIF __get_vector_element(__char3, __uint __CST(0, 63));
*/
signed char __OVBIF __get_vector_element(__char2, __uint);
/*
signed char __OVBIF __get_vector_element(__char2, __uint __CST(0, 63));
*/
/*
VGETUB
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar __OVBIF __get_vector_element(__uchar64, __uint);
/*
__uchar __OVBIF __get_vector_element(__uchar64, __uint __CST(0, 63));
*/
#endif
__uchar __OVBIF __get_vector_element(__uchar32, __uint);
/*
__uchar __OVBIF __get_vector_element(__uchar32, __uint __CST(0, 63));
*/
__uchar __OVBIF __get_vector_element(__uchar16, __uint);
/*
__uchar __OVBIF __get_vector_element(__uchar16, __uint __CST(0, 63));
*/
__uchar __OVBIF __get_vector_element(__uchar8, __uint);
/*
__uchar __OVBIF __get_vector_element(__uchar8, __uint __CST(0, 63));
*/
__uchar __OVBIF __get_vector_element(__uchar4, __uint);
/*
__uchar __OVBIF __get_vector_element(__uchar4, __uint __CST(0, 63));
*/
__uchar __OVBIF __get_vector_element(__uchar3, __uint);
/*
__uchar __OVBIF __get_vector_element(__uchar3, __uint __CST(0, 63));
*/
__uchar __OVBIF __get_vector_element(__uchar2, __uint);
/*
__uchar __OVBIF __get_vector_element(__uchar2, __uint __CST(0, 63));
*/
/*
VGETH
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__cchar __OVBIF __get_vector_element(__cchar32, __uint);
/*
__cchar __OVBIF __get_vector_element(__cchar32, __uint __CST(0, 63));
*/
#endif
__cchar __OVBIF __get_vector_element(__cchar16, __uint);
/*
__cchar __OVBIF __get_vector_element(__cchar16, __uint __CST(0, 63));
*/
__cchar __OVBIF __get_vector_element(__cchar8, __uint);
/*
__cchar __OVBIF __get_vector_element(__cchar8, __uint __CST(0, 63));
*/
__cchar __OVBIF __get_vector_element(__cchar4, __uint);
/*
__cchar __OVBIF __get_vector_element(__cchar4, __uint __CST(0, 63));
*/
__cchar __OVBIF __get_vector_element(__cchar2, __uint);
/*
__cchar __OVBIF __get_vector_element(__cchar2, __uint __CST(0, 63));
*/
#if __C7X_VEC_SIZE_BITS__ == 512
short __OVBIF __get_vector_element(__short32, __uint);
/*
short __OVBIF __get_vector_element(__short32, __uint __CST(0, 63));
*/
#endif
short __OVBIF __get_vector_element(__short16, __uint);
/*
short __OVBIF __get_vector_element(__short16, __uint __CST(0, 63));
*/
short __OVBIF __get_vector_element(__short8, __uint);
/*
short __OVBIF __get_vector_element(__short8, __uint __CST(0, 63));
*/
short __OVBIF __get_vector_element(__short4, __uint);
/*
short __OVBIF __get_vector_element(__short4, __uint __CST(0, 63));
*/
short __OVBIF __get_vector_element(__short3, __uint);
/*
short __OVBIF __get_vector_element(__short3, __uint __CST(0, 63));
*/
short __OVBIF __get_vector_element(__short2, __uint);
/*
short __OVBIF __get_vector_element(__short2, __uint __CST(0, 63));
*/
/*
VGETUH
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort __OVBIF __get_vector_element(__ushort32, __uint);
/*
__ushort __OVBIF __get_vector_element(__ushort32, __uint __CST(0, 63));
*/
#endif
__ushort __OVBIF __get_vector_element(__ushort16, __uint);
/*
__ushort __OVBIF __get_vector_element(__ushort16, __uint __CST(0, 63));
*/
__ushort __OVBIF __get_vector_element(__ushort8, __uint);
/*
__ushort __OVBIF __get_vector_element(__ushort8, __uint __CST(0, 63));
*/
__ushort __OVBIF __get_vector_element(__ushort4, __uint);
/*
__ushort __OVBIF __get_vector_element(__ushort4, __uint __CST(0, 63));
*/
__ushort __OVBIF __get_vector_element(__ushort3, __uint);
/*
__ushort __OVBIF __get_vector_element(__ushort3, __uint __CST(0, 63));
*/
__ushort __OVBIF __get_vector_element(__ushort2, __uint);
/*
__ushort __OVBIF __get_vector_element(__ushort2, __uint __CST(0, 63));
*/
/*
VGETW
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__cshort __OVBIF __get_vector_element(__cshort16, __uint);
/*
__cshort __OVBIF __get_vector_element(__cshort16, __uint __CST(0, 63));
*/
#endif
__cshort __OVBIF __get_vector_element(__cshort8, __uint);
/*
__cshort __OVBIF __get_vector_element(__cshort8, __uint __CST(0, 63));
*/
__cshort __OVBIF __get_vector_element(__cshort4, __uint);
/*
__cshort __OVBIF __get_vector_element(__cshort4, __uint __CST(0, 63));
*/
__cshort __OVBIF __get_vector_element(__cshort2, __uint);
/*
__cshort __OVBIF __get_vector_element(__cshort2, __uint __CST(0, 63));
*/
#if __C7X_VEC_SIZE_BITS__ == 512
int __OVBIF __get_vector_element(__int16, __uint);
/*
int __OVBIF __get_vector_element(__int16, __uint __CST(0, 63));
*/
#endif
int __OVBIF __get_vector_element(__int8, __uint);
/*
int __OVBIF __get_vector_element(__int8, __uint __CST(0, 63));
*/
int __OVBIF __get_vector_element(__int4, __uint);
/*
int __OVBIF __get_vector_element(__int4, __uint __CST(0, 63));
*/
int __OVBIF __get_vector_element(__int3, __uint);
/*
int __OVBIF __get_vector_element(__int3, __uint __CST(0, 63));
*/
int __OVBIF __get_vector_element(__int2, __uint);
/*
int __OVBIF __get_vector_element(__int2, __uint __CST(0, 63));
*/
/*
VGETUW
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__uint __OVBIF __get_vector_element(__uint16, __uint);
/*
__uint __OVBIF __get_vector_element(__uint16, __uint __CST(0, 63));
*/
#endif
__uint __OVBIF __get_vector_element(__uint8, __uint);
/*
__uint __OVBIF __get_vector_element(__uint8, __uint __CST(0, 63));
*/
__uint __OVBIF __get_vector_element(__uint4, __uint);
/*
__uint __OVBIF __get_vector_element(__uint4, __uint __CST(0, 63));
*/
__uint __OVBIF __get_vector_element(__uint3, __uint);
/*
__uint __OVBIF __get_vector_element(__uint3, __uint __CST(0, 63));
*/
__uint __OVBIF __get_vector_element(__uint2, __uint);
/*
__uint __OVBIF __get_vector_element(__uint2, __uint __CST(0, 63));
*/
/*
VGETUW, VGETW
*/
#if __C7X_VEC_SIZE_BITS__ == 512
float __OVBIF __get_vector_element(__float16, __uint);
/*
float __OVBIF __get_vector_element(__float16, __uint __CST(0, 63));
*/
#endif
float __OVBIF __get_vector_element(__float8, __uint);
/*
float __OVBIF __get_vector_element(__float8, __uint __CST(0, 63));
*/
float __OVBIF __get_vector_element(__float4, __uint);
/*
float __OVBIF __get_vector_element(__float4, __uint __CST(0, 63));
*/
float __OVBIF __get_vector_element(__float3, __uint);
/*
float __OVBIF __get_vector_element(__float3, __uint __CST(0, 63));
*/
float __OVBIF __get_vector_element(__float2, __uint);
/*
float __OVBIF __get_vector_element(__float2, __uint __CST(0, 63));
*/
/*
VGETD
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__cint __OVBIF __get_vector_element(__cint8, __uint);
/*
__cint __OVBIF __get_vector_element(__cint8, __uint __CST(0, 63));
*/
#endif
__cint __OVBIF __get_vector_element(__cint4, __uint);
/*
__cint __OVBIF __get_vector_element(__cint4, __uint __CST(0, 63));
*/
__cint __OVBIF __get_vector_element(__cint2, __uint);
/*
__cint __OVBIF __get_vector_element(__cint2, __uint __CST(0, 63));
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__cfloat __OVBIF __get_vector_element(__cfloat8, __uint);
/*
__cfloat __OVBIF __get_vector_element(__cfloat8, __uint __CST(0, 63));
*/
#endif
__cfloat __OVBIF __get_vector_element(__cfloat4, __uint);
/*
__cfloat __OVBIF __get_vector_element(__cfloat4, __uint __CST(0, 63));
*/
__cfloat __OVBIF __get_vector_element(__cfloat2, __uint);
/*
__cfloat __OVBIF __get_vector_element(__cfloat2, __uint __CST(0, 63));
*/
#if __C7X_VEC_SIZE_BITS__ == 512
long __OVBIF __get_vector_element(__long8, __uint);
/*
long __OVBIF __get_vector_element(__long8, __uint __CST(0, 63));
*/
#endif
long __OVBIF __get_vector_element(__long4, __uint);
/*
long __OVBIF __get_vector_element(__long4, __uint __CST(0, 63));
*/
long __OVBIF __get_vector_element(__long3, __uint);
/*
long __OVBIF __get_vector_element(__long3, __uint __CST(0, 63));
*/
long __OVBIF __get_vector_element(__long2, __uint);
/*
long __OVBIF __get_vector_element(__long2, __uint __CST(0, 63));
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong __OVBIF __get_vector_element(__ulong8, __uint);
/*
__ulong __OVBIF __get_vector_element(__ulong8, __uint __CST(0, 63));
*/
#endif
__ulong __OVBIF __get_vector_element(__ulong4, __uint);
/*
__ulong __OVBIF __get_vector_element(__ulong4, __uint __CST(0, 63));
*/
__ulong __OVBIF __get_vector_element(__ulong3, __uint);
/*
__ulong __OVBIF __get_vector_element(__ulong3, __uint __CST(0, 63));
*/
__ulong __OVBIF __get_vector_element(__ulong2, __uint);
/*
__ulong __OVBIF __get_vector_element(__ulong2, __uint __CST(0, 63));
*/
#if __C7X_VEC_SIZE_BITS__ == 512
double __OVBIF __get_vector_element(__double8, __uint);
/*
double __OVBIF __get_vector_element(__double8, __uint __CST(0, 63));
*/
#endif
double __OVBIF __get_vector_element(__double4, __uint);
/*
double __OVBIF __get_vector_element(__double4, __uint __CST(0, 63));
*/
double __OVBIF __get_vector_element(__double3, __uint);
/*
double __OVBIF __get_vector_element(__double3, __uint __CST(0, 63));
*/
double __OVBIF __get_vector_element(__double2, __uint);
/*
double __OVBIF __get_vector_element(__double2, __uint __CST(0, 63));
*/

/*----------------------------------------------------------------------------*/
/* ID: __gmpy                                                                 */
/*----------------------------------------------------------------------------*/
/*
VGMPYB
*/
__uchar __OVBIF __gmpy(__uchar, __uchar);
__uchar2 __OVBIF __gmpy(__uchar2, __uchar2);
__uchar3 __OVBIF __gmpy(__uchar3, __uchar3);
__uchar4 __OVBIF __gmpy(__uchar4, __uchar4);
__uchar8 __OVBIF __gmpy(__uchar8, __uchar8);
__uchar16 __OVBIF __gmpy(__uchar16, __uchar16);
__uchar32 __OVBIF __gmpy(__uchar32, __uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __gmpy(__uchar64, __uchar64);
#endif
/*
VGMPYW
*/
__uint __OVBIF __gmpy(__uint, __uint);
__uint2 __OVBIF __gmpy(__uint2, __uint2);
__uint3 __OVBIF __gmpy(__uint3, __uint3);
__uint4 __OVBIF __gmpy(__uint4, __uint4);
__uint8 __OVBIF __gmpy(__uint8, __uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __gmpy(__uint16, __uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __hadd                                                                 */
/*----------------------------------------------------------------------------*/
/*
VAVGNRB
*/
signed char __OVBIF __hadd(signed char, signed char);
__char2 __OVBIF __hadd(__char2, __char2);
__char3 __OVBIF __hadd(__char3, __char3);
__char4 __OVBIF __hadd(__char4, __char4);
__char8 __OVBIF __hadd(__char8, __char8);
__char16 __OVBIF __hadd(__char16, __char16);
__char32 __OVBIF __hadd(__char32, __char32);
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __hadd(__char64, __char64);
#endif
/*
VAVGNRUB
*/
__uchar __OVBIF __hadd(__uchar, __uchar);
__uchar2 __OVBIF __hadd(__uchar2, __uchar2);
__uchar3 __OVBIF __hadd(__uchar3, __uchar3);
__uchar4 __OVBIF __hadd(__uchar4, __uchar4);
__uchar8 __OVBIF __hadd(__uchar8, __uchar8);
__uchar16 __OVBIF __hadd(__uchar16, __uchar16);
__uchar32 __OVBIF __hadd(__uchar32, __uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __hadd(__uchar64, __uchar64);
#endif
/*
VAVGNRH
*/
short __OVBIF __hadd(short, short);
__short2 __OVBIF __hadd(__short2, __short2);
__short3 __OVBIF __hadd(__short3, __short3);
__short4 __OVBIF __hadd(__short4, __short4);
__short8 __OVBIF __hadd(__short8, __short8);
__short16 __OVBIF __hadd(__short16, __short16);
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __hadd(__short32, __short32);
#endif
/*
VAVGNRUH
*/
__ushort __OVBIF __hadd(__ushort, __ushort);
__ushort2 __OVBIF __hadd(__ushort2, __ushort2);
__ushort3 __OVBIF __hadd(__ushort3, __ushort3);
__ushort4 __OVBIF __hadd(__ushort4, __ushort4);
__ushort8 __OVBIF __hadd(__ushort8, __ushort8);
__ushort16 __OVBIF __hadd(__ushort16, __ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __hadd(__ushort32, __ushort32);
#endif
/*
VAVGNRW
*/
int __OVBIF __hadd(int, int);
__int2 __OVBIF __hadd(__int2, __int2);
__int3 __OVBIF __hadd(__int3, __int3);
__int4 __OVBIF __hadd(__int4, __int4);
__int8 __OVBIF __hadd(__int8, __int8);
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __hadd(__int16, __int16);
#endif
/*
VAVGNRUW
*/
__uint __OVBIF __hadd(__uint, __uint);
__uint2 __OVBIF __hadd(__uint2, __uint2);
__uint3 __OVBIF __hadd(__uint3, __uint3);
__uint4 __OVBIF __hadd(__uint4, __uint4);
__uint8 __OVBIF __hadd(__uint8, __uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __hadd(__uint16, __uint16);
#endif
/*
VAVGNRD
*/
long __OVBIF __hadd(long, long);
__long2 __OVBIF __hadd(__long2, __long2);
__long3 __OVBIF __hadd(__long3, __long3);
__long4 __OVBIF __hadd(__long4, __long4);
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __hadd(__long8, __long8);
#endif
/*
VAVGNRUD
*/
__ulong __OVBIF __hadd(__ulong, __ulong);
__ulong2 __OVBIF __hadd(__ulong2, __ulong2);
__ulong3 __OVBIF __hadd(__ulong3, __ulong3);
__ulong4 __OVBIF __hadd(__ulong4, __ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __hadd(__ulong8, __ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __half_float_to_float                                                  */
/*----------------------------------------------------------------------------*/
/*
VHPSP
*/
float __OVBIF __half_float_to_float(__uint);
__float2 __OVBIF __half_float_to_float(__uint2);
__float3 __OVBIF __half_float_to_float(__uint3);
__float4 __OVBIF __half_float_to_float(__uint4);
__float8 __OVBIF __half_float_to_float(__uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
__float16 __OVBIF __half_float_to_float(__uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __half_float_to_int                                                    */
/*----------------------------------------------------------------------------*/
/*
VHPINT
*/
int __OVBIF __half_float_to_int(__uint);
__int2 __OVBIF __half_float_to_int(__uint2);
__int3 __OVBIF __half_float_to_int(__uint3);
__int4 __OVBIF __half_float_to_int(__uint4);
__int8 __OVBIF __half_float_to_int(__uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __half_float_to_int(__uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __high_char_to_short                                                   */
/*----------------------------------------------------------------------------*/
/*
VBUNPKHH
*/
short __OVBIF __high_char_to_short(__char2);
__short2 __OVBIF __high_char_to_short(__char4);
__short4 __OVBIF __high_char_to_short(__char8);
__short8 __OVBIF __high_char_to_short(__char16);
__short16 __OVBIF __high_char_to_short(__char32);
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __high_char_to_short(__char64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __high_float_to_double                                                 */
/*----------------------------------------------------------------------------*/
/*
VSPDPH
*/
double __OVBIF __high_float_to_double(__float2);
__double2 __OVBIF __high_float_to_double(__float4);
__double4 __OVBIF __high_float_to_double(__float8);
#if __C7X_VEC_SIZE_BITS__ == 512
__double8 __OVBIF __high_float_to_double(__float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __high_half_int_to_float                                               */
/*----------------------------------------------------------------------------*/
/*
VINTHSPH
*/
__float2 __OVBIF __high_half_int_to_float(__short4);
__float4 __OVBIF __high_half_int_to_float(__short8);
__float8 __OVBIF __high_half_int_to_float(__short16);
#if __C7X_VEC_SIZE_BITS__ == 512
__float16 __OVBIF __high_half_int_to_float(__short32);
#endif
/*
VINTHSPUH
*/
__float2 __OVBIF __high_half_int_to_float(__ushort4);
__float4 __OVBIF __high_half_int_to_float(__ushort8);
__float8 __OVBIF __high_half_int_to_float(__ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
__float16 __OVBIF __high_half_int_to_float(__ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __high_int_to_double                                                   */
/*----------------------------------------------------------------------------*/
/*
VINTDPH
*/
double __OVBIF __high_int_to_double(__int2);
__double2 __OVBIF __high_int_to_double(__int4);
__double4 __OVBIF __high_int_to_double(__int8);
#if __C7X_VEC_SIZE_BITS__ == 512
__double8 __OVBIF __high_int_to_double(__int16);
#endif
/*
VINTDPUH
*/
double __OVBIF __high_int_to_double(__uint2);
__double2 __OVBIF __high_int_to_double(__uint4);
__double4 __OVBIF __high_int_to_double(__uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
__double8 __OVBIF __high_int_to_double(__uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __high_int_to_long                                                     */
/*----------------------------------------------------------------------------*/
/*
VWUNPKDH
*/
long __OVBIF __high_int_to_long(__int2);
__long2 __OVBIF __high_int_to_long(__int4);
__long4 __OVBIF __high_int_to_long(__int8);
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __high_int_to_long(__int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __high_short_to_int                                                    */
/*----------------------------------------------------------------------------*/
/*
VHUNPKWH
*/
int __OVBIF __high_short_to_int(__short2);
__int2 __OVBIF __high_short_to_int(__short4);
__int4 __OVBIF __high_short_to_int(__short8);
__int8 __OVBIF __high_short_to_int(__short16);
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __high_short_to_int(__short32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __high_uchar_to_ushort                                                 */
/*----------------------------------------------------------------------------*/
/*
VBUNPKUHH
*/
__ushort __OVBIF __high_uchar_to_ushort(__uchar2);
__ushort2 __OVBIF __high_uchar_to_ushort(__uchar4);
__ushort4 __OVBIF __high_uchar_to_ushort(__uchar8);
__ushort8 __OVBIF __high_uchar_to_ushort(__uchar16);
__ushort16 __OVBIF __high_uchar_to_ushort(__uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __high_uchar_to_ushort(__uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __high_uint_to_ulong                                                   */
/*----------------------------------------------------------------------------*/
/*
VWUNPKUDH
*/
__ulong __OVBIF __high_uint_to_ulong(__uint2);
__ulong2 __OVBIF __high_uint_to_ulong(__uint4);
__ulong4 __OVBIF __high_uint_to_ulong(__uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __high_uint_to_ulong(__uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __high_ushort_to_uint                                                  */
/*----------------------------------------------------------------------------*/
/*
VHUNPKUWH
*/
__uint __OVBIF __high_ushort_to_uint(__ushort2);
__uint2 __OVBIF __high_ushort_to_uint(__ushort4);
__uint4 __OVBIF __high_ushort_to_uint(__ushort8);
__uint8 __OVBIF __high_ushort_to_uint(__ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __high_ushort_to_uint(__ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __horizontal_add                                                       */
/*----------------------------------------------------------------------------*/
/*
VHADDB1D
*/
#if __C7X_VEC_SIZE_BITS__ == 512
long __OVBIF __horizontal_add(__char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
long __OVBIF __horizontal_add(__char32);
#endif
/*
VHADDUB1D
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong __OVBIF __horizontal_add(__uchar64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong __OVBIF __horizontal_add(__uchar32);
#endif
/*
VHADDH1D
*/
#if __C7X_VEC_SIZE_BITS__ == 512
long __OVBIF __horizontal_add(__short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
long __OVBIF __horizontal_add(__short16);
#endif
/*
VHADDUH1D
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong __OVBIF __horizontal_add(__ushort32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong __OVBIF __horizontal_add(__ushort16);
#endif
/*
VHADDW1D
*/
#if __C7X_VEC_SIZE_BITS__ == 512
long __OVBIF __horizontal_add(__int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
long __OVBIF __horizontal_add(__int8);
#endif
/*
VHADDUW1D
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong __OVBIF __horizontal_add(__uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong __OVBIF __horizontal_add(__uint8);
#endif
/*
VHADDD1D
*/
#if __C7X_VEC_SIZE_BITS__ == 512
long __OVBIF __horizontal_add(__long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
long __OVBIF __horizontal_add(__long4);
#endif
/*
VHADDUD1D
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong __OVBIF __horizontal_add(__ulong8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong __OVBIF __horizontal_add(__ulong4);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __horizontal_add_skip1                                                 */
/*----------------------------------------------------------------------------*/
/*
VHADDEOH2W
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__int2 __OVBIF __horizontal_add_skip1(__short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__int2 __OVBIF __horizontal_add_skip1(__short16);
#endif
/*
VHADDUEOH2W
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__uint2 __OVBIF __horizontal_add_skip1(__ushort32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uint2 __OVBIF __horizontal_add_skip1(__ushort16);
#endif
/*
VHADDEOH2W
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__cint __OVBIF __horizontal_add_skip1(__cshort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cint __OVBIF __horizontal_add_skip1(__cshort8);
#endif
/*
VHADDEOW2D
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__long2 __OVBIF __horizontal_add_skip1(__int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__long2 __OVBIF __horizontal_add_skip1(__int8);
#endif
/*
VHADDUEOW2D
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong2 __OVBIF __horizontal_add_skip1(__uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong2 __OVBIF __horizontal_add_skip1(__uint8);
#endif
/*
VHADDEOW2D
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__clong __OVBIF __horizontal_add_skip1(__cint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__clong __OVBIF __horizontal_add_skip1(__cint4);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __horizontal_xor                                                       */
/*----------------------------------------------------------------------------*/
/*
VHXORB1B
*/
#if __C7X_VEC_SIZE_BITS__ == 512
short __OVBIF __horizontal_xor(__char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
short __OVBIF __horizontal_xor(__char32);
#endif
/*
VHXORH1H
*/
#if __C7X_VEC_SIZE_BITS__ == 512
short __OVBIF __horizontal_xor(__short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
short __OVBIF __horizontal_xor(__short16);
#endif
/*
VHXORW1W
*/
#if __C7X_VEC_SIZE_BITS__ == 512
int __OVBIF __horizontal_xor(__int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
int __OVBIF __horizontal_xor(__int8);
#endif
/*
VHXORD1D
*/
#if __C7X_VEC_SIZE_BITS__ == 512
long __OVBIF __horizontal_xor(__long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
long __OVBIF __horizontal_xor(__long4);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __int40_to_int_sat                                                     */
/*----------------------------------------------------------------------------*/
/*
VSATLW
*/
long __OVBIF __int40_to_int_sat(long);
__long2 __OVBIF __int40_to_int_sat(__long2);
__long3 __OVBIF __int40_to_int_sat(__long3);
__long4 __OVBIF __int40_to_int_sat(__long4);
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __int40_to_int_sat(__long8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __int_to_float                                                         */
/*----------------------------------------------------------------------------*/
/*
VINTSP
*/
float __OVBIF __int_to_float(int);
__float2 __OVBIF __int_to_float(__int2);
__float3 __OVBIF __int_to_float(__int3);
__float4 __OVBIF __int_to_float(__int4);
__float8 __OVBIF __int_to_float(__int8);
#if __C7X_VEC_SIZE_BITS__ == 512
__float16 __OVBIF __int_to_float(__int16);
#endif
/*
VINTSPU
*/
float __OVBIF __int_to_float(__uint);
__float2 __OVBIF __int_to_float(__uint2);
__float3 __OVBIF __int_to_float(__uint3);
__float4 __OVBIF __int_to_float(__uint4);
__float8 __OVBIF __int_to_float(__uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
__float16 __OVBIF __int_to_float(__uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __int_to_half_float                                                    */
/*----------------------------------------------------------------------------*/
/*
VINTHP
*/
__uint __OVBIF __int_to_half_float(int);
__uint2 __OVBIF __int_to_half_float(__int2);
__uint3 __OVBIF __int_to_half_float(__int3);
__uint4 __OVBIF __int_to_half_float(__int4);
__uint8 __OVBIF __int_to_half_float(__int8);
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __int_to_half_float(__int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __int_to_short_sat                                                     */
/*----------------------------------------------------------------------------*/
/*
VSATWH
*/
int __OVBIF __int_to_short_sat(int);
__int2 __OVBIF __int_to_short_sat(__int2);
__int3 __OVBIF __int_to_short_sat(__int3);
__int4 __OVBIF __int_to_short_sat(__int4);
__int8 __OVBIF __int_to_short_sat(__int8);
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __int_to_short_sat(__int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __leftmost_bit_detect                                                  */
/*----------------------------------------------------------------------------*/
/*
VLMBDB
*/
__uchar __OVBIF __leftmost_bit_detect(__uchar, __uchar);
__uchar2 __OVBIF __leftmost_bit_detect(__uchar2, __uchar2);
__uchar3 __OVBIF __leftmost_bit_detect(__uchar3, __uchar3);
__uchar4 __OVBIF __leftmost_bit_detect(__uchar4, __uchar4);
__uchar8 __OVBIF __leftmost_bit_detect(__uchar8, __uchar8);
__uchar16 __OVBIF __leftmost_bit_detect(__uchar16, __uchar16);
__uchar32 __OVBIF __leftmost_bit_detect(__uchar32, __uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __leftmost_bit_detect(__uchar64, __uchar64);
#endif
/*
VLMBDH
*/
__ushort __OVBIF __leftmost_bit_detect(__ushort, __ushort);
__ushort2 __OVBIF __leftmost_bit_detect(__ushort2, __ushort2);
__ushort3 __OVBIF __leftmost_bit_detect(__ushort3, __ushort3);
__ushort4 __OVBIF __leftmost_bit_detect(__ushort4, __ushort4);
__ushort8 __OVBIF __leftmost_bit_detect(__ushort8, __ushort8);
__ushort16 __OVBIF __leftmost_bit_detect(__ushort16, __ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __leftmost_bit_detect(__ushort32, __ushort32);
#endif
/*
VLMBDW
*/
__uint __OVBIF __leftmost_bit_detect(__uint, __uint);
__uint2 __OVBIF __leftmost_bit_detect(__uint2, __uint2);
__uint3 __OVBIF __leftmost_bit_detect(__uint3, __uint3);
__uint4 __OVBIF __leftmost_bit_detect(__uint4, __uint4);
__uint8 __OVBIF __leftmost_bit_detect(__uint8, __uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __leftmost_bit_detect(__uint16, __uint16);
#endif
/*
VLMBDD
*/
__ulong __OVBIF __leftmost_bit_detect(__ulong, __ulong);
__ulong2 __OVBIF __leftmost_bit_detect(__ulong2, __ulong2);
__ulong3 __OVBIF __leftmost_bit_detect(__ulong3, __ulong3);
__ulong4 __OVBIF __leftmost_bit_detect(__ulong4, __ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __leftmost_bit_detect(__ulong8, __ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __leftmost_bit_detect_one                                              */
/*----------------------------------------------------------------------------*/
/*
VLMBD1B
*/
__uchar __OVBIF __leftmost_bit_detect_one(__uchar);
__uchar2 __OVBIF __leftmost_bit_detect_one(__uchar2);
__uchar3 __OVBIF __leftmost_bit_detect_one(__uchar3);
__uchar4 __OVBIF __leftmost_bit_detect_one(__uchar4);
__uchar8 __OVBIF __leftmost_bit_detect_one(__uchar8);
__uchar16 __OVBIF __leftmost_bit_detect_one(__uchar16);
__uchar32 __OVBIF __leftmost_bit_detect_one(__uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __leftmost_bit_detect_one(__uchar64);
#endif
/*
VLMBD1H
*/
__ushort __OVBIF __leftmost_bit_detect_one(__ushort);
__ushort2 __OVBIF __leftmost_bit_detect_one(__ushort2);
__ushort3 __OVBIF __leftmost_bit_detect_one(__ushort3);
__ushort4 __OVBIF __leftmost_bit_detect_one(__ushort4);
__ushort8 __OVBIF __leftmost_bit_detect_one(__ushort8);
__ushort16 __OVBIF __leftmost_bit_detect_one(__ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __leftmost_bit_detect_one(__ushort32);
#endif
/*
VLMBD1W
*/
__uint __OVBIF __leftmost_bit_detect_one(__uint);
__uint2 __OVBIF __leftmost_bit_detect_one(__uint2);
__uint3 __OVBIF __leftmost_bit_detect_one(__uint3);
__uint4 __OVBIF __leftmost_bit_detect_one(__uint4);
__uint8 __OVBIF __leftmost_bit_detect_one(__uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __leftmost_bit_detect_one(__uint16);
#endif
/*
VLMBD1D
*/
__ulong __OVBIF __leftmost_bit_detect_one(__ulong);
__ulong2 __OVBIF __leftmost_bit_detect_one(__ulong2);
__ulong3 __OVBIF __leftmost_bit_detect_one(__ulong3);
__ulong4 __OVBIF __leftmost_bit_detect_one(__ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __leftmost_bit_detect_one(__ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __leftmost_bit_detect_zero                                             */
/*----------------------------------------------------------------------------*/
/*
VLMBD0B
*/
__uchar __OVBIF __leftmost_bit_detect_zero(__uchar);
__uchar2 __OVBIF __leftmost_bit_detect_zero(__uchar2);
__uchar3 __OVBIF __leftmost_bit_detect_zero(__uchar3);
__uchar4 __OVBIF __leftmost_bit_detect_zero(__uchar4);
__uchar8 __OVBIF __leftmost_bit_detect_zero(__uchar8);
__uchar16 __OVBIF __leftmost_bit_detect_zero(__uchar16);
__uchar32 __OVBIF __leftmost_bit_detect_zero(__uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __leftmost_bit_detect_zero(__uchar64);
#endif
/*
VLMBD0H
*/
__ushort __OVBIF __leftmost_bit_detect_zero(__ushort);
__ushort2 __OVBIF __leftmost_bit_detect_zero(__ushort2);
__ushort3 __OVBIF __leftmost_bit_detect_zero(__ushort3);
__ushort4 __OVBIF __leftmost_bit_detect_zero(__ushort4);
__ushort8 __OVBIF __leftmost_bit_detect_zero(__ushort8);
__ushort16 __OVBIF __leftmost_bit_detect_zero(__ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __leftmost_bit_detect_zero(__ushort32);
#endif
/*
VLMBD0W
*/
__uint __OVBIF __leftmost_bit_detect_zero(__uint);
__uint2 __OVBIF __leftmost_bit_detect_zero(__uint2);
__uint3 __OVBIF __leftmost_bit_detect_zero(__uint3);
__uint4 __OVBIF __leftmost_bit_detect_zero(__uint4);
__uint8 __OVBIF __leftmost_bit_detect_zero(__uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __leftmost_bit_detect_zero(__uint16);
#endif
/*
VLMBD0D
*/
__ulong __OVBIF __leftmost_bit_detect_zero(__ulong);
__ulong2 __OVBIF __leftmost_bit_detect_zero(__ulong2);
__ulong3 __OVBIF __leftmost_bit_detect_zero(__ulong3);
__ulong4 __OVBIF __leftmost_bit_detect_zero(__ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __leftmost_bit_detect_zero(__ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __logical_and                                                          */
/*----------------------------------------------------------------------------*/
/*
LANDD
*/
int __BIF __logical_and(long, long);

/*----------------------------------------------------------------------------*/
/* ID: __logical_andn                                                         */
/*----------------------------------------------------------------------------*/
/*
LANDND
*/
int __BIF __logical_andn(long, long);

/*----------------------------------------------------------------------------*/
/* ID: __logical_or                                                           */
/*----------------------------------------------------------------------------*/
/*
LORD
*/
int __BIF __logical_or(long, long);

/*----------------------------------------------------------------------------*/
/* ID: __long_to_int40_sat                                                    */
/*----------------------------------------------------------------------------*/
/*
VSATDL
*/
long __OVBIF __long_to_int40_sat(long);
__long2 __OVBIF __long_to_int40_sat(__long2);
__long3 __OVBIF __long_to_int40_sat(__long3);
__long4 __OVBIF __long_to_int40_sat(__long4);
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __long_to_int40_sat(__long8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __long_to_int_sat                                                      */
/*----------------------------------------------------------------------------*/
/*
VSATDW
*/
long __OVBIF __long_to_int_sat(long);
__long2 __OVBIF __long_to_int_sat(__long2);
__long3 __OVBIF __long_to_int_sat(__long3);
__long4 __OVBIF __long_to_int_sat(__long4);
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __long_to_int_sat(__long8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __low_char_to_short                                                    */
/*----------------------------------------------------------------------------*/
/*
VBUNPKHL
*/
short __OVBIF __low_char_to_short(__char2);
__short2 __OVBIF __low_char_to_short(__char4);
__short4 __OVBIF __low_char_to_short(__char8);
__short8 __OVBIF __low_char_to_short(__char16);
__short16 __OVBIF __low_char_to_short(__char32);
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __low_char_to_short(__char64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __low_float_to_double                                                  */
/*----------------------------------------------------------------------------*/
/*
VSPDPL
*/
double __OVBIF __low_float_to_double(__float2);
__double2 __OVBIF __low_float_to_double(__float4);
__double4 __OVBIF __low_float_to_double(__float8);
#if __C7X_VEC_SIZE_BITS__ == 512
__double8 __OVBIF __low_float_to_double(__float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __low_half_int_to_float                                                */
/*----------------------------------------------------------------------------*/
/*
VINTHSPL
*/
__float2 __OVBIF __low_half_int_to_float(__short4);
__float4 __OVBIF __low_half_int_to_float(__short8);
__float8 __OVBIF __low_half_int_to_float(__short16);
#if __C7X_VEC_SIZE_BITS__ == 512
__float16 __OVBIF __low_half_int_to_float(__short32);
#endif
/*
VINTHSPUL
*/
__float2 __OVBIF __low_half_int_to_float(__ushort4);
__float4 __OVBIF __low_half_int_to_float(__ushort8);
__float8 __OVBIF __low_half_int_to_float(__ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
__float16 __OVBIF __low_half_int_to_float(__ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __low_int_to_double                                                    */
/*----------------------------------------------------------------------------*/
/*
VINTDPL
*/
double __OVBIF __low_int_to_double(__int2);
__double2 __OVBIF __low_int_to_double(__int4);
__double4 __OVBIF __low_int_to_double(__int8);
#if __C7X_VEC_SIZE_BITS__ == 512
__double8 __OVBIF __low_int_to_double(__int16);
#endif
/*
VINTDPUL
*/
double __OVBIF __low_int_to_double(__uint2);
__double2 __OVBIF __low_int_to_double(__uint4);
__double4 __OVBIF __low_int_to_double(__uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
__double8 __OVBIF __low_int_to_double(__uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __low_int_to_long                                                      */
/*----------------------------------------------------------------------------*/
/*
VWUNPKDL
*/
long __OVBIF __low_int_to_long(__int2);
__long2 __OVBIF __low_int_to_long(__int4);
__long4 __OVBIF __low_int_to_long(__int8);
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __low_int_to_long(__int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __low_short_to_int                                                     */
/*----------------------------------------------------------------------------*/
/*
VHUNPKWL
*/
int __OVBIF __low_short_to_int(__short2);
__int2 __OVBIF __low_short_to_int(__short4);
__int4 __OVBIF __low_short_to_int(__short8);
__int8 __OVBIF __low_short_to_int(__short16);
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __low_short_to_int(__short32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __low_uchar_to_ushort                                                  */
/*----------------------------------------------------------------------------*/
/*
VBUNPKUHL
*/
__ushort __OVBIF __low_uchar_to_ushort(__uchar2);
__ushort2 __OVBIF __low_uchar_to_ushort(__uchar4);
__ushort4 __OVBIF __low_uchar_to_ushort(__uchar8);
__ushort8 __OVBIF __low_uchar_to_ushort(__uchar16);
__ushort16 __OVBIF __low_uchar_to_ushort(__uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __low_uchar_to_ushort(__uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __low_uint_to_ulong                                                    */
/*----------------------------------------------------------------------------*/
/*
VWUNPKUDL
*/
__ulong __OVBIF __low_uint_to_ulong(__uint2);
__ulong2 __OVBIF __low_uint_to_ulong(__uint4);
__ulong4 __OVBIF __low_uint_to_ulong(__uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __low_uint_to_ulong(__uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __low_ushort_to_uint                                                   */
/*----------------------------------------------------------------------------*/
/*
VHUNPKUWL
*/
__uint __OVBIF __low_ushort_to_uint(__ushort2);
__uint2 __OVBIF __low_ushort_to_uint(__ushort4);
__uint4 __OVBIF __low_ushort_to_uint(__ushort8);
__uint8 __OVBIF __low_ushort_to_uint(__ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __low_ushort_to_uint(__ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __max                                                                  */
/*----------------------------------------------------------------------------*/
/*
VMAXB
*/
signed char __OVBIF __max(signed char, signed char);
__char2 __OVBIF __max(__char2, __char2);
__char3 __OVBIF __max(__char3, __char3);
__char4 __OVBIF __max(__char4, __char4);
__char8 __OVBIF __max(__char8, __char8);
__char16 __OVBIF __max(__char16, __char16);
__char32 __OVBIF __max(__char32, __char32);
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __max(__char64, __char64);
#endif
/*
VMAXUB
*/
__uchar __OVBIF __max(__uchar, __uchar);
__uchar2 __OVBIF __max(__uchar2, __uchar2);
__uchar3 __OVBIF __max(__uchar3, __uchar3);
__uchar4 __OVBIF __max(__uchar4, __uchar4);
__uchar8 __OVBIF __max(__uchar8, __uchar8);
__uchar16 __OVBIF __max(__uchar16, __uchar16);
__uchar32 __OVBIF __max(__uchar32, __uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __max(__uchar64, __uchar64);
#endif
/*
VMAXH
*/
short __OVBIF __max(short, short);
__short2 __OVBIF __max(__short2, __short2);
__short3 __OVBIF __max(__short3, __short3);
__short4 __OVBIF __max(__short4, __short4);
__short8 __OVBIF __max(__short8, __short8);
__short16 __OVBIF __max(__short16, __short16);
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __max(__short32, __short32);
#endif
/*
VMAXUH
*/
__ushort __OVBIF __max(__ushort, __ushort);
__ushort2 __OVBIF __max(__ushort2, __ushort2);
__ushort3 __OVBIF __max(__ushort3, __ushort3);
__ushort4 __OVBIF __max(__ushort4, __ushort4);
__ushort8 __OVBIF __max(__ushort8, __ushort8);
__ushort16 __OVBIF __max(__ushort16, __ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __max(__ushort32, __ushort32);
#endif
/*
VMAXW
*/
int __OVBIF __max(int, int);
__int2 __OVBIF __max(__int2, __int2);
__int3 __OVBIF __max(__int3, __int3);
__int4 __OVBIF __max(__int4, __int4);
__int8 __OVBIF __max(__int8, __int8);
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __max(__int16, __int16);
#endif
/*
VMAXUW
*/
__uint __OVBIF __max(__uint, __uint);
__uint2 __OVBIF __max(__uint2, __uint2);
__uint3 __OVBIF __max(__uint3, __uint3);
__uint4 __OVBIF __max(__uint4, __uint4);
__uint8 __OVBIF __max(__uint8, __uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __max(__uint16, __uint16);
#endif
/*
VMAXSP
*/
float __OVBIF __max(float, float);
__float2 __OVBIF __max(__float2, __float2);
__float3 __OVBIF __max(__float3, __float3);
__float4 __OVBIF __max(__float4, __float4);
__float8 __OVBIF __max(__float8, __float8);
#if __C7X_VEC_SIZE_BITS__ == 512
__float16 __OVBIF __max(__float16, __float16);
#endif
/*
VMAXD
*/
long __OVBIF __max(long, long);
__long2 __OVBIF __max(__long2, __long2);
__long3 __OVBIF __max(__long3, __long3);
__long4 __OVBIF __max(__long4, __long4);
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __max(__long8, __long8);
#endif
/*
VMAXUD
*/
__ulong __OVBIF __max(__ulong, __ulong);
__ulong2 __OVBIF __max(__ulong2, __ulong2);
__ulong3 __OVBIF __max(__ulong3, __ulong3);
__ulong4 __OVBIF __max(__ulong4, __ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __max(__ulong8, __ulong8);
#endif
/*
VMAXDP
*/
double __OVBIF __max(double, double);
__double2 __OVBIF __max(__double2, __double2);
__double3 __OVBIF __max(__double3, __double3);
__double4 __OVBIF __max(__double4, __double4);
#if __C7X_VEC_SIZE_BITS__ == 512
__double8 __OVBIF __max(__double8, __double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __max_circ                                                             */
/*----------------------------------------------------------------------------*/
/*
VCMAXB
*/
signed char __OVBIF __max_circ(signed char, signed char);
__char2 __OVBIF __max_circ(__char2, __char2);
__char3 __OVBIF __max_circ(__char3, __char3);
__char4 __OVBIF __max_circ(__char4, __char4);
__char8 __OVBIF __max_circ(__char8, __char8);
__char16 __OVBIF __max_circ(__char16, __char16);
__char32 __OVBIF __max_circ(__char32, __char32);
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __max_circ(__char64, __char64);
#endif
/*
VCMAXH
*/
short __OVBIF __max_circ(short, short);
__short2 __OVBIF __max_circ(__short2, __short2);
__short3 __OVBIF __max_circ(__short3, __short3);
__short4 __OVBIF __max_circ(__short4, __short4);
__short8 __OVBIF __max_circ(__short8, __short8);
__short16 __OVBIF __max_circ(__short16, __short16);
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __max_circ(__short32, __short32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __max_circ_bool                                                        */
/*----------------------------------------------------------------------------*/
/*

VCMAXPB
void __max_circ_bool(char2, char2&, bool2&);
void __max_circ_bool(char3, char3&, bool3&);
void __max_circ_bool(char4, char4&, bool4&);
void __max_circ_bool(char8, char8&, bool8&);
void __max_circ_bool(char16, char16&, bool16&);
void __max_circ_bool(char32, char32&, bool32&);
#if __C7X_VEC_SIZE_BITS__ == 512
void __max_circ_bool(char64, char64&, bool64&);
#endif

VCMAXPH
void __max_circ_bool(short2, short2&, bool2&);
void __max_circ_bool(short3, short3&, bool3&);
void __max_circ_bool(short4, short4&, bool4&);
void __max_circ_bool(short8, short8&, bool8&);
void __max_circ_bool(short16, short16&, bool16&);
#if __C7X_VEC_SIZE_BITS__ == 512
void __max_circ_bool(short32, short32&, bool32&);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __max_index_bool                                                       */
/*----------------------------------------------------------------------------*/
/*

VMAXPB
void __max_index_bool(char2, char2&, bool2&);
void __max_index_bool(char3, char3&, bool3&);
void __max_index_bool(char4, char4&, bool4&);
void __max_index_bool(char8, char8&, bool8&);
void __max_index_bool(char16, char16&, bool16&);
void __max_index_bool(char32, char32&, bool32&);
#if __C7X_VEC_SIZE_BITS__ == 512
void __max_index_bool(char64, char64&, bool64&);
#endif

VMAXUPB
void __max_index_bool(uchar2, uchar2&, bool2&);
void __max_index_bool(uchar3, uchar3&, bool3&);
void __max_index_bool(uchar4, uchar4&, bool4&);
void __max_index_bool(uchar8, uchar8&, bool8&);
void __max_index_bool(uchar16, uchar16&, bool16&);
void __max_index_bool(uchar32, uchar32&, bool32&);
#if __C7X_VEC_SIZE_BITS__ == 512
void __max_index_bool(uchar64, uchar64&, bool64&);
#endif

VMAXPH
void __max_index_bool(short2, short2&, bool2&);
void __max_index_bool(short3, short3&, bool3&);
void __max_index_bool(short4, short4&, bool4&);
void __max_index_bool(short8, short8&, bool8&);
void __max_index_bool(short16, short16&, bool16&);
#if __C7X_VEC_SIZE_BITS__ == 512
void __max_index_bool(short32, short32&, bool32&);
#endif

VMAXUPH
void __max_index_bool(ushort2, ushort2&, bool2&);
void __max_index_bool(ushort3, ushort3&, bool3&);
void __max_index_bool(ushort4, ushort4&, bool4&);
void __max_index_bool(ushort8, ushort8&, bool8&);
void __max_index_bool(ushort16, ushort16&, bool16&);
#if __C7X_VEC_SIZE_BITS__ == 512
void __max_index_bool(ushort32, ushort32&, bool32&);
#endif

VMAXPW
void __max_index_bool(int2, int2&, bool2&);
void __max_index_bool(int3, int3&, bool3&);
void __max_index_bool(int4, int4&, bool4&);
void __max_index_bool(int8, int8&, bool8&);
#if __C7X_VEC_SIZE_BITS__ == 512
void __max_index_bool(int16, int16&, bool16&);
#endif

VMAXUPW
void __max_index_bool(uint2, uint2&, bool2&);
void __max_index_bool(uint3, uint3&, bool3&);
void __max_index_bool(uint4, uint4&, bool4&);
void __max_index_bool(uint8, uint8&, bool8&);
#if __C7X_VEC_SIZE_BITS__ == 512
void __max_index_bool(uint16, uint16&, bool16&);
#endif

VMAXPD
void __max_index_bool(long2, long2&, bool2&);
void __max_index_bool(long3, long3&, bool3&);
void __max_index_bool(long4, long4&, bool4&);
#if __C7X_VEC_SIZE_BITS__ == 512
void __max_index_bool(long8, long8&, bool8&);
#endif

VMAXUPD
void __max_index_bool(ulong2, ulong2&, bool2&);
void __max_index_bool(ulong3, ulong3&, bool3&);
void __max_index_bool(ulong4, ulong4&, bool4&);
#if __C7X_VEC_SIZE_BITS__ == 512
void __max_index_bool(ulong8, ulong8&, bool8&);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __min                                                                  */
/*----------------------------------------------------------------------------*/
/*
VMINB
*/
signed char __OVBIF __min(signed char, signed char);
__char2 __OVBIF __min(__char2, __char2);
__char3 __OVBIF __min(__char3, __char3);
__char4 __OVBIF __min(__char4, __char4);
__char8 __OVBIF __min(__char8, __char8);
__char16 __OVBIF __min(__char16, __char16);
__char32 __OVBIF __min(__char32, __char32);
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __min(__char64, __char64);
#endif
/*
VMINUB
*/
__uchar __OVBIF __min(__uchar, __uchar);
__uchar2 __OVBIF __min(__uchar2, __uchar2);
__uchar3 __OVBIF __min(__uchar3, __uchar3);
__uchar4 __OVBIF __min(__uchar4, __uchar4);
__uchar8 __OVBIF __min(__uchar8, __uchar8);
__uchar16 __OVBIF __min(__uchar16, __uchar16);
__uchar32 __OVBIF __min(__uchar32, __uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __min(__uchar64, __uchar64);
#endif
/*
VMINH
*/
short __OVBIF __min(short, short);
__short2 __OVBIF __min(__short2, __short2);
__short3 __OVBIF __min(__short3, __short3);
__short4 __OVBIF __min(__short4, __short4);
__short8 __OVBIF __min(__short8, __short8);
__short16 __OVBIF __min(__short16, __short16);
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __min(__short32, __short32);
#endif
/*
VMINUH
*/
__ushort __OVBIF __min(__ushort, __ushort);
__ushort2 __OVBIF __min(__ushort2, __ushort2);
__ushort3 __OVBIF __min(__ushort3, __ushort3);
__ushort4 __OVBIF __min(__ushort4, __ushort4);
__ushort8 __OVBIF __min(__ushort8, __ushort8);
__ushort16 __OVBIF __min(__ushort16, __ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __min(__ushort32, __ushort32);
#endif
/*
VMINW
*/
int __OVBIF __min(int, int);
__int2 __OVBIF __min(__int2, __int2);
__int3 __OVBIF __min(__int3, __int3);
__int4 __OVBIF __min(__int4, __int4);
__int8 __OVBIF __min(__int8, __int8);
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __min(__int16, __int16);
#endif
/*
VMINUW
*/
__uint __OVBIF __min(__uint, __uint);
__uint2 __OVBIF __min(__uint2, __uint2);
__uint3 __OVBIF __min(__uint3, __uint3);
__uint4 __OVBIF __min(__uint4, __uint4);
__uint8 __OVBIF __min(__uint8, __uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __min(__uint16, __uint16);
#endif
/*
VMINSP
*/
float __OVBIF __min(float, float);
__float2 __OVBIF __min(__float2, __float2);
__float3 __OVBIF __min(__float3, __float3);
__float4 __OVBIF __min(__float4, __float4);
__float8 __OVBIF __min(__float8, __float8);
#if __C7X_VEC_SIZE_BITS__ == 512
__float16 __OVBIF __min(__float16, __float16);
#endif
/*
VMIND
*/
long __OVBIF __min(long, long);
__long2 __OVBIF __min(__long2, __long2);
__long3 __OVBIF __min(__long3, __long3);
__long4 __OVBIF __min(__long4, __long4);
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __min(__long8, __long8);
#endif
/*
VMINUD
*/
__ulong __OVBIF __min(__ulong, __ulong);
__ulong2 __OVBIF __min(__ulong2, __ulong2);
__ulong3 __OVBIF __min(__ulong3, __ulong3);
__ulong4 __OVBIF __min(__ulong4, __ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __min(__ulong8, __ulong8);
#endif
/*
VMINDP
*/
double __OVBIF __min(double, double);
__double2 __OVBIF __min(__double2, __double2);
__double3 __OVBIF __min(__double3, __double3);
__double4 __OVBIF __min(__double4, __double4);
#if __C7X_VEC_SIZE_BITS__ == 512
__double8 __OVBIF __min(__double8, __double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __min_index_bool                                                       */
/*----------------------------------------------------------------------------*/
/*

VMINPB
void __min_index_bool(char2, char2&, bool2&);
void __min_index_bool(char3, char3&, bool3&);
void __min_index_bool(char4, char4&, bool4&);
void __min_index_bool(char8, char8&, bool8&);
void __min_index_bool(char16, char16&, bool16&);
void __min_index_bool(char32, char32&, bool32&);
#if __C7X_VEC_SIZE_BITS__ == 512
void __min_index_bool(char64, char64&, bool64&);
#endif

VMINUPB
void __min_index_bool(uchar2, uchar2&, bool2&);
void __min_index_bool(uchar3, uchar3&, bool3&);
void __min_index_bool(uchar4, uchar4&, bool4&);
void __min_index_bool(uchar8, uchar8&, bool8&);
void __min_index_bool(uchar16, uchar16&, bool16&);
void __min_index_bool(uchar32, uchar32&, bool32&);
#if __C7X_VEC_SIZE_BITS__ == 512
void __min_index_bool(uchar64, uchar64&, bool64&);
#endif

VMINPH
void __min_index_bool(short2, short2&, bool2&);
void __min_index_bool(short3, short3&, bool3&);
void __min_index_bool(short4, short4&, bool4&);
void __min_index_bool(short8, short8&, bool8&);
void __min_index_bool(short16, short16&, bool16&);
#if __C7X_VEC_SIZE_BITS__ == 512
void __min_index_bool(short32, short32&, bool32&);
#endif

VMINUPH
void __min_index_bool(ushort2, ushort2&, bool2&);
void __min_index_bool(ushort3, ushort3&, bool3&);
void __min_index_bool(ushort4, ushort4&, bool4&);
void __min_index_bool(ushort8, ushort8&, bool8&);
void __min_index_bool(ushort16, ushort16&, bool16&);
#if __C7X_VEC_SIZE_BITS__ == 512
void __min_index_bool(ushort32, ushort32&, bool32&);
#endif

VMINPW
void __min_index_bool(int2, int2&, bool2&);
void __min_index_bool(int3, int3&, bool3&);
void __min_index_bool(int4, int4&, bool4&);
void __min_index_bool(int8, int8&, bool8&);
#if __C7X_VEC_SIZE_BITS__ == 512
void __min_index_bool(int16, int16&, bool16&);
#endif

VMINUPW
void __min_index_bool(uint2, uint2&, bool2&);
void __min_index_bool(uint3, uint3&, bool3&);
void __min_index_bool(uint4, uint4&, bool4&);
void __min_index_bool(uint8, uint8&, bool8&);
#if __C7X_VEC_SIZE_BITS__ == 512
void __min_index_bool(uint16, uint16&, bool16&);
#endif

VMINPD
void __min_index_bool(long2, long2&, bool2&);
void __min_index_bool(long3, long3&, bool3&);
void __min_index_bool(long4, long4&, bool4&);
#if __C7X_VEC_SIZE_BITS__ == 512
void __min_index_bool(long8, long8&, bool8&);
#endif

VMINUPD
void __min_index_bool(ulong2, ulong2&, bool2&);
void __min_index_bool(ulong3, ulong3&, bool3&);
void __min_index_bool(ulong4, ulong4&, bool4&);
#if __C7X_VEC_SIZE_BITS__ == 512
void __min_index_bool(ulong8, ulong8&, bool8&);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __mpy_ext                                                              */
/*----------------------------------------------------------------------------*/
/*
VMPYSUBH
*/
short __OVBIF __mpy_ext(signed char, __uchar);
__short2 __OVBIF __mpy_ext(__char2, __uchar2);
__short3 __OVBIF __mpy_ext(__char3, __uchar3);
__short4 __OVBIF __mpy_ext(__char4, __uchar4);
__short8 __OVBIF __mpy_ext(__char8, __uchar8);
__short16 __OVBIF __mpy_ext(__char16, __uchar16);
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __mpy_ext(__char32, __uchar32);
#endif
/*
VMPYUBH
*/
__ushort __OVBIF __mpy_ext(__uchar, __uchar);
__ushort2 __OVBIF __mpy_ext(__uchar2, __uchar2);
__ushort3 __OVBIF __mpy_ext(__uchar3, __uchar3);
__ushort4 __OVBIF __mpy_ext(__uchar4, __uchar4);
__ushort8 __OVBIF __mpy_ext(__uchar8, __uchar8);
__ushort16 __OVBIF __mpy_ext(__uchar16, __uchar16);
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __mpy_ext(__uchar32, __uchar32);
#endif
/*
MPYHW, VMPYHW
*/
int __OVBIF __mpy_ext(short, short);
__int2 __OVBIF __mpy_ext(__short2, __short2);
__int3 __OVBIF __mpy_ext(__short3, __short3);
__int4 __OVBIF __mpy_ext(__short4, __short4);
__int8 __OVBIF __mpy_ext(__short8, __short8);
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __mpy_ext(__short16, __short16);
#endif
/*
MPYSUHW, VMPYSUHW
*/
int __OVBIF __mpy_ext(short, __ushort);
__int2 __OVBIF __mpy_ext(__short2, __ushort2);
__int3 __OVBIF __mpy_ext(__short3, __ushort3);
__int4 __OVBIF __mpy_ext(__short4, __ushort4);
__int8 __OVBIF __mpy_ext(__short8, __ushort8);
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __mpy_ext(__short16, __ushort16);
#endif
/*
MPYUHW, VMPYUHW
*/
__uint __OVBIF __mpy_ext(__ushort, __ushort);
__uint2 __OVBIF __mpy_ext(__ushort2, __ushort2);
__uint3 __OVBIF __mpy_ext(__ushort3, __ushort3);
__uint4 __OVBIF __mpy_ext(__ushort4, __ushort4);
__uint8 __OVBIF __mpy_ext(__ushort8, __ushort8);
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __mpy_ext(__ushort16, __ushort16);
#endif
/*
VMPYWD
*/
long __OVBIF __mpy_ext(int, int);
__long2 __OVBIF __mpy_ext(__int2, __int2);
__long3 __OVBIF __mpy_ext(__int3, __int3);
__long4 __OVBIF __mpy_ext(__int4, __int4);
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __mpy_ext(__int8, __int8);
#endif
/*
VMPYSUWD
*/
long __OVBIF __mpy_ext(int, __uint);
__long2 __OVBIF __mpy_ext(__int2, __uint2);
__long3 __OVBIF __mpy_ext(__int3, __uint3);
__long4 __OVBIF __mpy_ext(__int4, __uint4);
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __mpy_ext(__int8, __uint8);
#endif
/*
VMPYUWD
*/
__ulong __OVBIF __mpy_ext(__uint, __uint);
__ulong2 __OVBIF __mpy_ext(__uint2, __uint2);
__ulong3 __OVBIF __mpy_ext(__uint3, __uint3);
__ulong4 __OVBIF __mpy_ext(__uint4, __uint4);
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __mpy_ext(__uint8, __uint8);
#endif
/*
VMPYSP2DP
*/
double __OVBIF __mpy_ext(float, float);
__double2 __OVBIF __mpy_ext(__float2, __float2);
__double3 __OVBIF __mpy_ext(__float3, __float3);
__double4 __OVBIF __mpy_ext(__float4, __float4);
#if __C7X_VEC_SIZE_BITS__ == 512
__double8 __OVBIF __mpy_ext(__float8, __float8);
#endif
/*
VMPYUDQ
*/
__ulong2 __OVBIF __mpy_ext(__ulong, __ulong);
__ulong4 __OVBIF __mpy_ext(__ulong2, __ulong2);
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __mpy_ext(__ulong4, __ulong4);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __mpy_fx                                                               */
/*----------------------------------------------------------------------------*/
/*
C6MPY2IR
*/
__int2 __BIF __mpy_fx(__short2, int);

/*----------------------------------------------------------------------------*/
/* ID: __mpy_sat                                                              */
/*----------------------------------------------------------------------------*/
/*
VSMPYWW
*/
int __OVBIF __mpy_sat(int, int);
__int2 __OVBIF __mpy_sat(__int2, __int2);
__int3 __OVBIF __mpy_sat(__int3, __int3);
__int4 __OVBIF __mpy_sat(__int4, __int4);
__int8 __OVBIF __mpy_sat(__int8, __int8);
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __mpy_sat(__int16, __int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __mpy_sat_ext                                                          */
/*----------------------------------------------------------------------------*/
/*
SMPYHW, VSMPYHW
*/
int __OVBIF __mpy_sat_ext(short, short);
__int2 __OVBIF __mpy_sat_ext(__short2, __short2);
__int3 __OVBIF __mpy_sat_ext(__short3, __short3);
__int4 __OVBIF __mpy_sat_ext(__short4, __short4);
__int8 __OVBIF __mpy_sat_ext(__short8, __short8);
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __mpy_sat_ext(__short16, __short16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __mpy_sat_fxq15                                                        */
/*----------------------------------------------------------------------------*/
/*
VSMPYR1HH
*/
short __OVBIF __mpy_sat_fxq15(short, short);
__short2 __OVBIF __mpy_sat_fxq15(__short2, __short2);
__short3 __OVBIF __mpy_sat_fxq15(__short3, __short3);
__short4 __OVBIF __mpy_sat_fxq15(__short4, __short4);
__short8 __OVBIF __mpy_sat_fxq15(__short8, __short8);
__short16 __OVBIF __mpy_sat_fxq15(__short16, __short16);
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __mpy_sat_fxq15(__short32, __short32);
#endif
/*
VSMPYRSUHH
*/
short __OVBIF __mpy_sat_fxq15(short, __ushort);
__short2 __OVBIF __mpy_sat_fxq15(__short2, __ushort2);
__short3 __OVBIF __mpy_sat_fxq15(__short3, __ushort3);
__short4 __OVBIF __mpy_sat_fxq15(__short4, __ushort4);
__short8 __OVBIF __mpy_sat_fxq15(__short8, __ushort8);
__short16 __OVBIF __mpy_sat_fxq15(__short16, __ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __mpy_sat_fxq15(__short32, __ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __mpy_sat_fxq16                                                        */
/*----------------------------------------------------------------------------*/
/*
VSMPYRUHH
*/
__ushort __OVBIF __mpy_sat_fxq16(__ushort, __ushort);
__ushort2 __OVBIF __mpy_sat_fxq16(__ushort2, __ushort2);
__ushort3 __OVBIF __mpy_sat_fxq16(__ushort3, __ushort3);
__ushort4 __OVBIF __mpy_sat_fxq16(__ushort4, __ushort4);
__ushort8 __OVBIF __mpy_sat_fxq16(__ushort8, __ushort8);
__ushort16 __OVBIF __mpy_sat_fxq16(__ushort16, __ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __mpy_sat_fxq16(__ushort32, __ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __mpy_sat_fxq16_15                                                     */
/*----------------------------------------------------------------------------*/
/*
VSMPYR17WW
*/
int __OVBIF __mpy_sat_fxq16_15(int, int);
__int2 __OVBIF __mpy_sat_fxq16_15(__int2, __int2);
__int3 __OVBIF __mpy_sat_fxq16_15(__int3, __int3);
__int4 __OVBIF __mpy_sat_fxq16_15(__int4, __int4);
__int8 __OVBIF __mpy_sat_fxq16_15(__int8, __int8);
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __mpy_sat_fxq16_15(__int16, __int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __mpy_sat_fxq31                                                        */
/*----------------------------------------------------------------------------*/
/*
VSMPYR1WW
*/
int __OVBIF __mpy_sat_fxq31(int, int);
__int2 __OVBIF __mpy_sat_fxq31(__int2, __int2);
__int3 __OVBIF __mpy_sat_fxq31(__int3, __int3);
__int4 __OVBIF __mpy_sat_fxq31(__int4, __int4);
__int8 __OVBIF __mpy_sat_fxq31(__int8, __int8);
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __mpy_sat_fxq31(__int16, __int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __mpy_xor                                                              */
/*----------------------------------------------------------------------------*/
/*
VXORMPYW
*/
__uint __OVBIF __mpy_xor(__uint, __uint);
__uint2 __OVBIF __mpy_xor(__uint2, __uint2);
__uint3 __OVBIF __mpy_xor(__uint3, __uint3);
__uint4 __OVBIF __mpy_xor(__uint4, __uint4);
__uint8 __OVBIF __mpy_xor(__uint8, __uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __mpy_xor(__uint16, __uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __nand                                                                 */
/*----------------------------------------------------------------------------*/
/*
NANDD, NANDW, VNANDW
*/
signed char __OVBIF __nand(signed char, signed char);
__char2 __OVBIF __nand(__char2, __char2);
__char3 __OVBIF __nand(__char3, __char3);
__char4 __OVBIF __nand(__char4, __char4);
__char8 __OVBIF __nand(__char8, __char8);
__char16 __OVBIF __nand(__char16, __char16);
__char32 __OVBIF __nand(__char32, __char32);
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __nand(__char64, __char64);
#endif
__uchar __OVBIF __nand(__uchar, __uchar);
__uchar2 __OVBIF __nand(__uchar2, __uchar2);
__uchar3 __OVBIF __nand(__uchar3, __uchar3);
__uchar4 __OVBIF __nand(__uchar4, __uchar4);
__uchar8 __OVBIF __nand(__uchar8, __uchar8);
__uchar16 __OVBIF __nand(__uchar16, __uchar16);
__uchar32 __OVBIF __nand(__uchar32, __uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __nand(__uchar64, __uchar64);
#endif
short __OVBIF __nand(short, short);
__short2 __OVBIF __nand(__short2, __short2);
__short3 __OVBIF __nand(__short3, __short3);
__short4 __OVBIF __nand(__short4, __short4);
__short8 __OVBIF __nand(__short8, __short8);
__short16 __OVBIF __nand(__short16, __short16);
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __nand(__short32, __short32);
#endif
__ushort __OVBIF __nand(__ushort, __ushort);
__ushort2 __OVBIF __nand(__ushort2, __ushort2);
__ushort3 __OVBIF __nand(__ushort3, __ushort3);
__ushort4 __OVBIF __nand(__ushort4, __ushort4);
__ushort8 __OVBIF __nand(__ushort8, __ushort8);
__ushort16 __OVBIF __nand(__ushort16, __ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __nand(__ushort32, __ushort32);
#endif
int __OVBIF __nand(int, int);
__int2 __OVBIF __nand(__int2, __int2);
__int3 __OVBIF __nand(__int3, __int3);
__int4 __OVBIF __nand(__int4, __int4);
__int8 __OVBIF __nand(__int8, __int8);
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __nand(__int16, __int16);
#endif
__uint __OVBIF __nand(__uint, __uint);
__uint2 __OVBIF __nand(__uint2, __uint2);
__uint3 __OVBIF __nand(__uint3, __uint3);
__uint4 __OVBIF __nand(__uint4, __uint4);
__uint8 __OVBIF __nand(__uint8, __uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __nand(__uint16, __uint16);
#endif
/*
NANDD, VNANDW
*/
long __OVBIF __nand(long, long);
/*
long __OVBIF __nand(long, long __CST(-2147483648, 2147483647));
*/
__long2 __OVBIF __nand(__long2, __long2);
__long3 __OVBIF __nand(__long3, __long3);
__long4 __OVBIF __nand(__long4, __long4);
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __nand(__long8, __long8);
#endif
__ulong __OVBIF __nand(__ulong, __ulong);
/*
__ulong __OVBIF __nand(__ulong, __ulong __CST(0, 2147483647));
*/
__ulong2 __OVBIF __nand(__ulong2, __ulong2);
__ulong3 __OVBIF __nand(__ulong3, __ulong3);
__ulong4 __OVBIF __nand(__ulong4, __ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __nand(__ulong8, __ulong8);
#endif
/*
NAND
*/
__bool2 __OVBIF __nand(__bool2, __bool2);
__bool3 __OVBIF __nand(__bool3, __bool3);
__bool4 __OVBIF __nand(__bool4, __bool4);
__bool8 __OVBIF __nand(__bool8, __bool8);
__bool16 __OVBIF __nand(__bool16, __bool16);
__bool32 __OVBIF __nand(__bool32, __bool32);
#if __C7X_VEC_SIZE_BITS__ == 512
__bool64 __OVBIF __nand(__bool64, __bool64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __negate                                                               */
/*----------------------------------------------------------------------------*/
/*
NOT
*/
__bool2 __OVBIF __negate(__bool2);
__bool3 __OVBIF __negate(__bool3);
__bool4 __OVBIF __negate(__bool4);
__bool8 __OVBIF __negate(__bool8);
__bool16 __OVBIF __negate(__bool16);
__bool32 __OVBIF __negate(__bool32);
#if __C7X_VEC_SIZE_BITS__ == 512
__bool64 __OVBIF __negate(__bool64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __nor                                                                  */
/*----------------------------------------------------------------------------*/
/*
NORD, NORW, VNORW
*/
signed char __OVBIF __nor(signed char, signed char);
__char2 __OVBIF __nor(__char2, __char2);
__char3 __OVBIF __nor(__char3, __char3);
__char4 __OVBIF __nor(__char4, __char4);
__char8 __OVBIF __nor(__char8, __char8);
__char16 __OVBIF __nor(__char16, __char16);
__char32 __OVBIF __nor(__char32, __char32);
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __nor(__char64, __char64);
#endif
__uchar __OVBIF __nor(__uchar, __uchar);
__uchar2 __OVBIF __nor(__uchar2, __uchar2);
__uchar3 __OVBIF __nor(__uchar3, __uchar3);
__uchar4 __OVBIF __nor(__uchar4, __uchar4);
__uchar8 __OVBIF __nor(__uchar8, __uchar8);
__uchar16 __OVBIF __nor(__uchar16, __uchar16);
__uchar32 __OVBIF __nor(__uchar32, __uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __nor(__uchar64, __uchar64);
#endif
short __OVBIF __nor(short, short);
__short2 __OVBIF __nor(__short2, __short2);
__short3 __OVBIF __nor(__short3, __short3);
__short4 __OVBIF __nor(__short4, __short4);
__short8 __OVBIF __nor(__short8, __short8);
__short16 __OVBIF __nor(__short16, __short16);
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __nor(__short32, __short32);
#endif
__ushort __OVBIF __nor(__ushort, __ushort);
__ushort2 __OVBIF __nor(__ushort2, __ushort2);
__ushort3 __OVBIF __nor(__ushort3, __ushort3);
__ushort4 __OVBIF __nor(__ushort4, __ushort4);
__ushort8 __OVBIF __nor(__ushort8, __ushort8);
__ushort16 __OVBIF __nor(__ushort16, __ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __nor(__ushort32, __ushort32);
#endif
int __OVBIF __nor(int, int);
__int2 __OVBIF __nor(__int2, __int2);
__int3 __OVBIF __nor(__int3, __int3);
__int4 __OVBIF __nor(__int4, __int4);
__int8 __OVBIF __nor(__int8, __int8);
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __nor(__int16, __int16);
#endif
__uint __OVBIF __nor(__uint, __uint);
__uint2 __OVBIF __nor(__uint2, __uint2);
__uint3 __OVBIF __nor(__uint3, __uint3);
__uint4 __OVBIF __nor(__uint4, __uint4);
__uint8 __OVBIF __nor(__uint8, __uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __nor(__uint16, __uint16);
#endif
/*
NORD, VNORW
*/
long __OVBIF __nor(long, long);
/*
long __OVBIF __nor(long, long __CST(-2147483648, 2147483647));
*/
__long2 __OVBIF __nor(__long2, __long2);
__long3 __OVBIF __nor(__long3, __long3);
__long4 __OVBIF __nor(__long4, __long4);
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __nor(__long8, __long8);
#endif
__ulong __OVBIF __nor(__ulong, __ulong);
/*
__ulong __OVBIF __nor(__ulong, __ulong __CST(0, 2147483647));
*/
__ulong2 __OVBIF __nor(__ulong2, __ulong2);
__ulong3 __OVBIF __nor(__ulong3, __ulong3);
__ulong4 __OVBIF __nor(__ulong4, __ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __nor(__ulong8, __ulong8);
#endif
/*
NOR
*/
__bool2 __OVBIF __nor(__bool2, __bool2);
__bool3 __OVBIF __nor(__bool3, __bool3);
__bool4 __OVBIF __nor(__bool4, __bool4);
__bool8 __OVBIF __nor(__bool8, __bool8);
__bool16 __OVBIF __nor(__bool16, __bool16);
__bool32 __OVBIF __nor(__bool32, __bool32);
#if __C7X_VEC_SIZE_BITS__ == 512
__bool64 __OVBIF __nor(__bool64, __bool64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __norm                                                                 */
/*----------------------------------------------------------------------------*/
/*
VNORMB
*/
signed char __OVBIF __norm(signed char);
__char2 __OVBIF __norm(__char2);
__char3 __OVBIF __norm(__char3);
__char4 __OVBIF __norm(__char4);
__char8 __OVBIF __norm(__char8);
__char16 __OVBIF __norm(__char16);
__char32 __OVBIF __norm(__char32);
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __norm(__char64);
#endif
/*
VNORMH
*/
short __OVBIF __norm(short);
__short2 __OVBIF __norm(__short2);
__short3 __OVBIF __norm(__short3);
__short4 __OVBIF __norm(__short4);
__short8 __OVBIF __norm(__short8);
__short16 __OVBIF __norm(__short16);
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __norm(__short32);
#endif
/*
VNORMW
*/
int __OVBIF __norm(int);
__int2 __OVBIF __norm(__int2);
__int3 __OVBIF __norm(__int3);
__int4 __OVBIF __norm(__int4);
__int8 __OVBIF __norm(__int8);
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __norm(__int16);
#endif
/*
VNORMD
*/
long __OVBIF __norm(long);
__long2 __OVBIF __norm(__long2);
__long3 __OVBIF __norm(__long3);
__long4 __OVBIF __norm(__long4);
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __norm(__long8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __norm_and_shift_elem_pair                                             */
/*----------------------------------------------------------------------------*/
/*
VNORM2UH
*/
__ushort2 __OVBIF __norm_and_shift_elem_pair(__ushort2);
__ushort4 __OVBIF __norm_and_shift_elem_pair(__ushort4);
__ushort8 __OVBIF __norm_and_shift_elem_pair(__ushort8);
__ushort16 __OVBIF __norm_and_shift_elem_pair(__ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __norm_and_shift_elem_pair(__ushort32);
#endif
/*
VNORM2UW
*/
__uint2 __OVBIF __norm_and_shift_elem_pair(__uint2);
__uint4 __OVBIF __norm_and_shift_elem_pair(__uint4);
__uint8 __OVBIF __norm_and_shift_elem_pair(__uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __norm_and_shift_elem_pair(__uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __or                                                                   */
/*----------------------------------------------------------------------------*/
/*
OR
*/
__bool2 __OVBIF __or(__bool2, __bool2);
__bool3 __OVBIF __or(__bool3, __bool3);
__bool4 __OVBIF __or(__bool4, __bool4);
__bool8 __OVBIF __or(__bool8, __bool8);
__bool16 __OVBIF __or(__bool16, __bool16);
__bool32 __OVBIF __or(__bool32, __bool32);
#if __C7X_VEC_SIZE_BITS__ == 512
__bool64 __OVBIF __or(__bool64, __bool64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __orn                                                                  */
/*----------------------------------------------------------------------------*/
/*
ORND, ORNW, VORNW
*/
signed char __OVBIF __orn(signed char, signed char);
/*
signed char __OVBIF __orn(signed char, signed char __CST(-128, 127));
*/
__char2 __OVBIF __orn(__char2, __char2);
/*
__char2 __OVBIF __orn(__char2, __char2 __CST(-128, 127));
*/
__char3 __OVBIF __orn(__char3, __char3);
/*
__char3 __OVBIF __orn(__char3, __char3 __CST(-128, 127));
*/
__char4 __OVBIF __orn(__char4, __char4);
/*
__char4 __OVBIF __orn(__char4, __char4 __CST(-128, 127));
*/
__char8 __OVBIF __orn(__char8, __char8);
__char16 __OVBIF __orn(__char16, __char16);
__char32 __OVBIF __orn(__char32, __char32);
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __orn(__char64, __char64);
#endif
__uchar __OVBIF __orn(__uchar, __uchar);
/*
__uchar __OVBIF __orn(__uchar, __uchar __CST(0, 255));
*/
__uchar2 __OVBIF __orn(__uchar2, __uchar2);
/*
__uchar2 __OVBIF __orn(__uchar2, __uchar2 __CST(0, 255));
*/
__uchar3 __OVBIF __orn(__uchar3, __uchar3);
/*
__uchar3 __OVBIF __orn(__uchar3, __uchar3 __CST(0, 255));
*/
__uchar4 __OVBIF __orn(__uchar4, __uchar4);
/*
__uchar4 __OVBIF __orn(__uchar4, __uchar4 __CST(0, 255));
*/
__uchar8 __OVBIF __orn(__uchar8, __uchar8);
__uchar16 __OVBIF __orn(__uchar16, __uchar16);
__uchar32 __OVBIF __orn(__uchar32, __uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __orn(__uchar64, __uchar64);
#endif
short __OVBIF __orn(short, short);
/*
short __OVBIF __orn(short, short __CST(-32768, 32767));
*/
__short2 __OVBIF __orn(__short2, __short2);
/*
__short2 __OVBIF __orn(__short2, __short2 __CST(-32768, 32767));
*/
__short3 __OVBIF __orn(__short3, __short3);
__short4 __OVBIF __orn(__short4, __short4);
__short8 __OVBIF __orn(__short8, __short8);
__short16 __OVBIF __orn(__short16, __short16);
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __orn(__short32, __short32);
#endif
__ushort __OVBIF __orn(__ushort, __ushort);
/*
__ushort __OVBIF __orn(__ushort, __ushort __CST(0, 65535));
*/
__ushort2 __OVBIF __orn(__ushort2, __ushort2);
/*
__ushort2 __OVBIF __orn(__ushort2, __ushort2 __CST(0, 65535));
*/
__ushort3 __OVBIF __orn(__ushort3, __ushort3);
__ushort4 __OVBIF __orn(__ushort4, __ushort4);
__ushort8 __OVBIF __orn(__ushort8, __ushort8);
__ushort16 __OVBIF __orn(__ushort16, __ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __orn(__ushort32, __ushort32);
#endif
int __OVBIF __orn(int, int);
/*
int __OVBIF __orn(int, int __CST(-2147483648, 2147483647));
*/
__int2 __OVBIF __orn(__int2, __int2);
/*
__int2 __OVBIF __orn(__int2, __int2 __CST(-2147483648, 2147483647));
*/
__int3 __OVBIF __orn(__int3, __int3);
/*
__int3 __OVBIF __orn(__int3, __int3 __CST(-2147483648, 2147483647));
*/
__int4 __OVBIF __orn(__int4, __int4);
/*
__int4 __OVBIF __orn(__int4, __int4 __CST(-2147483648, 2147483647));
*/
__int8 __OVBIF __orn(__int8, __int8);
/*
__int8 __OVBIF __orn(__int8, __int8 __CST(-2147483648, 2147483647));
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __orn(__int16, __int16);
/*
__int16 __OVBIF __orn(__int16, __int16 __CST(-2147483648, 2147483647));
*/
#endif
__uint __OVBIF __orn(__uint, __uint);
/*
__uint __OVBIF __orn(__uint, __uint __CST(0, 4294967295));
*/
__uint2 __OVBIF __orn(__uint2, __uint2);
/*
__uint2 __OVBIF __orn(__uint2, __uint2 __CST(0, 4294967295));
*/
__uint3 __OVBIF __orn(__uint3, __uint3);
/*
__uint3 __OVBIF __orn(__uint3, __uint3 __CST(0, 4294967295));
*/
__uint4 __OVBIF __orn(__uint4, __uint4);
/*
__uint4 __OVBIF __orn(__uint4, __uint4 __CST(0, 4294967295));
*/
__uint8 __OVBIF __orn(__uint8, __uint8);
/*
__uint8 __OVBIF __orn(__uint8, __uint8 __CST(0, 4294967295));
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __orn(__uint16, __uint16);
/*
__uint16 __OVBIF __orn(__uint16, __uint16 __CST(0, 4294967295));
*/
#endif
/*
ORND, VORNW
*/
long __OVBIF __orn(long, long);
/*
long __OVBIF __orn(long, long __CST(-2147483648, 2147483647));
*/
__long2 __OVBIF __orn(__long2, __long2);
__long3 __OVBIF __orn(__long3, __long3);
__long4 __OVBIF __orn(__long4, __long4);
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __orn(__long8, __long8);
#endif
__ulong __OVBIF __orn(__ulong, __ulong);
/*
__ulong __OVBIF __orn(__ulong, __ulong __CST(0, 2147483647));
*/
__ulong2 __OVBIF __orn(__ulong2, __ulong2);
__ulong3 __OVBIF __orn(__ulong3, __ulong3);
__ulong4 __OVBIF __orn(__ulong4, __ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __orn(__ulong8, __ulong8);
#endif
/*
ORN
*/
__bool2 __OVBIF __orn(__bool2, __bool2);
__bool3 __OVBIF __orn(__bool3, __bool3);
__bool4 __OVBIF __orn(__bool4, __bool4);
__bool8 __OVBIF __orn(__bool8, __bool8);
__bool16 __OVBIF __orn(__bool16, __bool16);
__bool32 __OVBIF __orn(__bool32, __bool32);
#if __C7X_VEC_SIZE_BITS__ == 512
__bool64 __OVBIF __orn(__bool64, __bool64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __outer_product_matmpy                                                 */
/*----------------------------------------------------------------------------*/
/*
VOPMATMPYSP
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__float4 __OVBIF __outer_product_matmpy(__float2, __float2);
__float8 __OVBIF __outer_product_matmpy(__float4, __float4);
__float16 __OVBIF __outer_product_matmpy(__float8, __float8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __pack                                                                 */
/*----------------------------------------------------------------------------*/
/*
PACKW
*/
__cshort2 __OVBIF __pack(__cshort, __cshort);
__int2 __OVBIF __pack(int, int);
__uint2 __OVBIF __pack(__uint, __uint);
__float2 __OVBIF __pack(float, float);

/*----------------------------------------------------------------------------*/
/* ID: __pack_consec_high                                                     */
/*----------------------------------------------------------------------------*/
/*
VBPACKH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __OVBIF __pack_consec_high(__char32, __char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __pack_consec_high(__char64, __char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __OVBIF __pack_consec_high(__uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __pack_consec_high(__uchar64, __uchar64);
#endif
/*
VHPACKH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cchar16 __OVBIF __pack_consec_high(__cchar16, __cchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cchar32 __OVBIF __pack_consec_high(__cchar32, __cchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __OVBIF __pack_consec_high(__short16, __short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __pack_consec_high(__short32, __short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __OVBIF __pack_consec_high(__ushort16, __ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __pack_consec_high(__ushort32, __ushort32);
#endif
/*
VWPACKH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cshort8 __OVBIF __pack_consec_high(__cshort8, __cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cshort16 __OVBIF __pack_consec_high(__cshort16, __cshort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __OVBIF __pack_consec_high(__int8, __int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __pack_consec_high(__int16, __int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __OVBIF __pack_consec_high(__uint8, __uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __pack_consec_high(__uint16, __uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__float8 __OVBIF __pack_consec_high(__float8, __float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__float16 __OVBIF __pack_consec_high(__float16, __float16);
#endif
/*
VDPACKH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cint4 __OVBIF __pack_consec_high(__cint4, __cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cint8 __OVBIF __pack_consec_high(__cint8, __cint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cfloat4 __OVBIF __pack_consec_high(__cfloat4, __cfloat4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cfloat8 __OVBIF __pack_consec_high(__cfloat8, __cfloat8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __OVBIF __pack_consec_high(__long4, __long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __pack_consec_high(__long8, __long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __OVBIF __pack_consec_high(__ulong4, __ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __pack_consec_high(__ulong8, __ulong8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__double4 __OVBIF __pack_consec_high(__double4, __double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__double8 __OVBIF __pack_consec_high(__double8, __double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __pack_consec_low                                                      */
/*----------------------------------------------------------------------------*/
/*
VBPACKL
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __OVBIF __pack_consec_low(__char32, __char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __pack_consec_low(__char64, __char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __OVBIF __pack_consec_low(__uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __pack_consec_low(__uchar64, __uchar64);
#endif
/*
VHPACKL
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cchar16 __OVBIF __pack_consec_low(__cchar16, __cchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cchar32 __OVBIF __pack_consec_low(__cchar32, __cchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __OVBIF __pack_consec_low(__short16, __short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __pack_consec_low(__short32, __short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __OVBIF __pack_consec_low(__ushort16, __ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __pack_consec_low(__ushort32, __ushort32);
#endif
/*
VWPACKL
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cshort8 __OVBIF __pack_consec_low(__cshort8, __cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cshort16 __OVBIF __pack_consec_low(__cshort16, __cshort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __OVBIF __pack_consec_low(__int8, __int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __pack_consec_low(__int16, __int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __OVBIF __pack_consec_low(__uint8, __uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __pack_consec_low(__uint16, __uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__float8 __OVBIF __pack_consec_low(__float8, __float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__float16 __OVBIF __pack_consec_low(__float16, __float16);
#endif
/*
VDPACKL
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cint4 __OVBIF __pack_consec_low(__cint4, __cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cint8 __OVBIF __pack_consec_low(__cint8, __cint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cfloat4 __OVBIF __pack_consec_low(__cfloat4, __cfloat4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cfloat8 __OVBIF __pack_consec_low(__cfloat8, __cfloat8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __OVBIF __pack_consec_low(__long4, __long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __pack_consec_low(__long8, __long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __OVBIF __pack_consec_low(__ulong4, __ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __pack_consec_low(__ulong8, __ulong8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__double4 __OVBIF __pack_consec_low(__double4, __double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__double8 __OVBIF __pack_consec_low(__double8, __double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __pack_even                                                            */
/*----------------------------------------------------------------------------*/
/*
VPACKP2
*/
__cchar4 __OVBIF __pack_even(__cchar4, __cchar4);
__cchar8 __OVBIF __pack_even(__cchar8, __cchar8);
__cchar16 __OVBIF __pack_even(__cchar16, __cchar16);
#if __C7X_VEC_SIZE_BITS__ == 512
__cchar32 __OVBIF __pack_even(__cchar32, __cchar32);
#endif
__short4 __OVBIF __pack_even(__short4, __short4);
__short8 __OVBIF __pack_even(__short8, __short8);
__short16 __OVBIF __pack_even(__short16, __short16);
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __pack_even(__short32, __short32);
#endif
__ushort4 __OVBIF __pack_even(__ushort4, __ushort4);
__ushort8 __OVBIF __pack_even(__ushort8, __ushort8);
__ushort16 __OVBIF __pack_even(__ushort16, __ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __pack_even(__ushort32, __ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __pack_even_cross                                                      */
/*----------------------------------------------------------------------------*/
/*
PACKX2
*/
__cchar4 __OVBIF __pack_even_cross(__cchar2, __cchar2);
/*
VPACKX2
*/
__cchar4 __OVBIF __pack_even_cross(__cchar4, __cchar4);
__cchar8 __OVBIF __pack_even_cross(__cchar8, __cchar8);
__cchar16 __OVBIF __pack_even_cross(__cchar16, __cchar16);
#if __C7X_VEC_SIZE_BITS__ == 512
__cchar32 __OVBIF __pack_even_cross(__cchar32, __cchar32);
#endif
/*
PACKX2
*/
__short4 __OVBIF __pack_even_cross(__short2, __short2);
/*
VPACKX2
*/
__short4 __OVBIF __pack_even_cross(__short4, __short4);
__short8 __OVBIF __pack_even_cross(__short8, __short8);
__short16 __OVBIF __pack_even_cross(__short16, __short16);
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __pack_even_cross(__short32, __short32);
#endif
/*
PACKX2
*/
__ushort4 __OVBIF __pack_even_cross(__ushort2, __ushort2);
/*
VPACKX2
*/
__ushort4 __OVBIF __pack_even_cross(__ushort4, __ushort4);
__ushort8 __OVBIF __pack_even_cross(__ushort8, __ushort8);
__ushort16 __OVBIF __pack_even_cross(__ushort16, __ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __pack_even_cross(__ushort32, __ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __pack_high                                                            */
/*----------------------------------------------------------------------------*/
/*
VPACKH4
*/
__char4 __OVBIF __pack_high(__char4, __char4);
__char8 __OVBIF __pack_high(__char8, __char8);
__char16 __OVBIF __pack_high(__char16, __char16);
__char32 __OVBIF __pack_high(__char32, __char32);
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __pack_high(__char64, __char64);
#endif
__uchar4 __OVBIF __pack_high(__uchar4, __uchar4);
__uchar8 __OVBIF __pack_high(__uchar8, __uchar8);
__uchar16 __OVBIF __pack_high(__uchar16, __uchar16);
__uchar32 __OVBIF __pack_high(__uchar32, __uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __pack_high(__uchar64, __uchar64);
#endif
/*
VPACKH2
*/
__cchar2 __OVBIF __pack_high(__cchar2, __cchar2);
__cchar4 __OVBIF __pack_high(__cchar4, __cchar4);
__cchar8 __OVBIF __pack_high(__cchar8, __cchar8);
__cchar16 __OVBIF __pack_high(__cchar16, __cchar16);
#if __C7X_VEC_SIZE_BITS__ == 512
__cchar32 __OVBIF __pack_high(__cchar32, __cchar32);
#endif
__short2 __OVBIF __pack_high(__short2, __short2);
__short4 __OVBIF __pack_high(__short4, __short4);
__short8 __OVBIF __pack_high(__short8, __short8);
__short16 __OVBIF __pack_high(__short16, __short16);
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __pack_high(__short32, __short32);
#endif
__ushort2 __OVBIF __pack_high(__ushort2, __ushort2);
__ushort4 __OVBIF __pack_high(__ushort4, __ushort4);
__ushort8 __OVBIF __pack_high(__ushort8, __ushort8);
__ushort16 __OVBIF __pack_high(__ushort16, __ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __pack_high(__ushort32, __ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __pack_high_low                                                        */
/*----------------------------------------------------------------------------*/
/*
VPACKHL2
*/
__cchar2 __OVBIF __pack_high_low(__cchar2, __cchar2);
__cchar4 __OVBIF __pack_high_low(__cchar4, __cchar4);
__cchar8 __OVBIF __pack_high_low(__cchar8, __cchar8);
__cchar16 __OVBIF __pack_high_low(__cchar16, __cchar16);
#if __C7X_VEC_SIZE_BITS__ == 512
__cchar32 __OVBIF __pack_high_low(__cchar32, __cchar32);
#endif
__short2 __OVBIF __pack_high_low(__short2, __short2);
__short4 __OVBIF __pack_high_low(__short4, __short4);
__short8 __OVBIF __pack_high_low(__short8, __short8);
__short16 __OVBIF __pack_high_low(__short16, __short16);
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __pack_high_low(__short32, __short32);
#endif
__ushort2 __OVBIF __pack_high_low(__ushort2, __ushort2);
__ushort4 __OVBIF __pack_high_low(__ushort4, __ushort4);
__ushort8 __OVBIF __pack_high_low(__ushort8, __ushort8);
__ushort16 __OVBIF __pack_high_low(__ushort16, __ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __pack_high_low(__ushort32, __ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __pack_low                                                             */
/*----------------------------------------------------------------------------*/
/*
VPACKL4
*/
__char4 __OVBIF __pack_low(__char4, __char4);
__char8 __OVBIF __pack_low(__char8, __char8);
__char16 __OVBIF __pack_low(__char16, __char16);
__char32 __OVBIF __pack_low(__char32, __char32);
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __pack_low(__char64, __char64);
#endif
__uchar4 __OVBIF __pack_low(__uchar4, __uchar4);
__uchar8 __OVBIF __pack_low(__uchar8, __uchar8);
__uchar16 __OVBIF __pack_low(__uchar16, __uchar16);
__uchar32 __OVBIF __pack_low(__uchar32, __uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __pack_low(__uchar64, __uchar64);
#endif
/*
VPACKL2
*/
__cchar2 __OVBIF __pack_low(__cchar2, __cchar2);
__cchar4 __OVBIF __pack_low(__cchar4, __cchar4);
__cchar8 __OVBIF __pack_low(__cchar8, __cchar8);
__cchar16 __OVBIF __pack_low(__cchar16, __cchar16);
#if __C7X_VEC_SIZE_BITS__ == 512
__cchar32 __OVBIF __pack_low(__cchar32, __cchar32);
#endif
__short2 __OVBIF __pack_low(__short2, __short2);
__short4 __OVBIF __pack_low(__short4, __short4);
__short8 __OVBIF __pack_low(__short8, __short8);
__short16 __OVBIF __pack_low(__short16, __short16);
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __pack_low(__short32, __short32);
#endif
__ushort2 __OVBIF __pack_low(__ushort2, __ushort2);
__ushort4 __OVBIF __pack_low(__ushort4, __ushort4);
__ushort8 __OVBIF __pack_low(__ushort8, __ushort8);
__ushort16 __OVBIF __pack_low(__ushort16, __ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __pack_low(__ushort32, __ushort32);
#endif
/*
VPACKW
*/
__cshort2 __OVBIF __pack_low(__cshort2, __cshort2);
__cshort4 __OVBIF __pack_low(__cshort4, __cshort4);
__cshort8 __OVBIF __pack_low(__cshort8, __cshort8);
#if __C7X_VEC_SIZE_BITS__ == 512
__cshort16 __OVBIF __pack_low(__cshort16, __cshort16);
#endif
__int2 __OVBIF __pack_low(__int2, __int2);
__int4 __OVBIF __pack_low(__int4, __int4);
__int8 __OVBIF __pack_low(__int8, __int8);
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __pack_low(__int16, __int16);
#endif
__uint2 __OVBIF __pack_low(__uint2, __uint2);
__uint4 __OVBIF __pack_low(__uint4, __uint4);
__uint8 __OVBIF __pack_low(__uint8, __uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __pack_low(__uint16, __uint16);
#endif
__float2 __OVBIF __pack_low(__float2, __float2);
__float4 __OVBIF __pack_low(__float4, __float4);
__float8 __OVBIF __pack_low(__float8, __float8);
#if __C7X_VEC_SIZE_BITS__ == 512
__float16 __OVBIF __pack_low(__float16, __float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __pack_low_high                                                        */
/*----------------------------------------------------------------------------*/
/*
VPACKLH4
*/
__char8 __OVBIF __pack_low_high(__char8, __char8);
__char16 __OVBIF __pack_low_high(__char16, __char16);
__char32 __OVBIF __pack_low_high(__char32, __char32);
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __pack_low_high(__char64, __char64);
#endif
__uchar8 __OVBIF __pack_low_high(__uchar8, __uchar8);
__uchar16 __OVBIF __pack_low_high(__uchar16, __uchar16);
__uchar32 __OVBIF __pack_low_high(__uchar32, __uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __pack_low_high(__uchar64, __uchar64);
#endif
/*
VPACKLH2
*/
__cchar2 __OVBIF __pack_low_high(__cchar2, __cchar2);
__cchar4 __OVBIF __pack_low_high(__cchar4, __cchar4);
__cchar8 __OVBIF __pack_low_high(__cchar8, __cchar8);
__cchar16 __OVBIF __pack_low_high(__cchar16, __cchar16);
#if __C7X_VEC_SIZE_BITS__ == 512
__cchar32 __OVBIF __pack_low_high(__cchar32, __cchar32);
#endif
__short2 __OVBIF __pack_low_high(__short2, __short2);
__short4 __OVBIF __pack_low_high(__short4, __short4);
__short8 __OVBIF __pack_low_high(__short8, __short8);
__short16 __OVBIF __pack_low_high(__short16, __short16);
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __pack_low_high(__short32, __short32);
#endif
__ushort2 __OVBIF __pack_low_high(__ushort2, __ushort2);
__ushort4 __OVBIF __pack_low_high(__ushort4, __ushort4);
__ushort8 __OVBIF __pack_low_high(__ushort8, __ushort8);
__ushort16 __OVBIF __pack_low_high(__ushort16, __ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __pack_low_high(__ushort32, __ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __pack_sat                                                             */
/*----------------------------------------------------------------------------*/
/*
VSPACKHB
*/
__char2 __OVBIF __pack_sat(short, short);
__char4 __OVBIF __pack_sat(__short2, __short2);
__char8 __OVBIF __pack_sat(__short4, __short4);
__char16 __OVBIF __pack_sat(__short8, __short8);
__char32 __OVBIF __pack_sat(__short16, __short16);
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __pack_sat(__short32, __short32);
#endif
/*
VSPACKWH
*/
__short2 __OVBIF __pack_sat(int, int);
__short4 __OVBIF __pack_sat(__int2, __int2);
__short8 __OVBIF __pack_sat(__int4, __int4);
__short16 __OVBIF __pack_sat(__int8, __int8);
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __pack_sat(__int16, __int16);
#endif
/*
VSPACKDW
*/
__int2 __OVBIF __pack_sat(long, long);
__int4 __OVBIF __pack_sat(__long2, __long2);
__int8 __OVBIF __pack_sat(__long4, __long4);
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __pack_sat(__long8, __long8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __pack_shift_sat                                                       */
/*----------------------------------------------------------------------------*/
/*
VRPACKH
*/
__short2 __OVBIF __pack_shift_sat(int, int);
__short4 __OVBIF __pack_shift_sat(__int2, __int2);
__short8 __OVBIF __pack_shift_sat(__int4, __int4);
__short16 __OVBIF __pack_shift_sat(__int8, __int8);
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __pack_shift_sat(__int16, __int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __pack_usat                                                            */
/*----------------------------------------------------------------------------*/
/*
VSPACKUHB
*/
__uchar2 __OVBIF __pack_usat(short, short);
__uchar4 __OVBIF __pack_usat(__short2, __short2);
__uchar8 __OVBIF __pack_usat(__short4, __short4);
__uchar16 __OVBIF __pack_usat(__short8, __short8);
__uchar32 __OVBIF __pack_usat(__short16, __short16);
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __pack_usat(__short32, __short32);
#endif
/*
VSPACKUWH
*/
__ushort2 __OVBIF __pack_usat(int, int);
__ushort4 __OVBIF __pack_usat(__int2, __int2);
__ushort8 __OVBIF __pack_usat(__int4, __int4);
__ushort16 __OVBIF __pack_usat(__int8, __int8);
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __pack_usat(__int16, __int16);
#endif
/*
VSPACKUDW
*/
__uint2 __OVBIF __pack_usat(long, long);
__uint4 __OVBIF __pack_usat(__long2, __long2);
__uint8 __OVBIF __pack_usat(__long4, __long4);
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __pack_usat(__long8, __long8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __parallel_pack_dup_16way                                              */
/*----------------------------------------------------------------------------*/
/*
VPPACKDUP16W
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __parallel_pack_dup_16way(__bool16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __parallel_pack_dup_8way                                               */
/*----------------------------------------------------------------------------*/
/*
VPPACKDUP8W
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __parallel_pack_dup_8way(__bool8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __permute                                                              */
/*----------------------------------------------------------------------------*/
/*
VPERM
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __BIF __permute(__uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __permute(__uchar64, __uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __permute_cntrl                                                        */
/*----------------------------------------------------------------------------*/
/*
VPERM
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __BIF __permute_cntrl(__uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __permute_cntrl(__uchar64, __uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __permute_even_even_char                                               */
/*----------------------------------------------------------------------------*/
/*
VPERMEEB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __BIF __permute_even_even_char(__uchar32, __uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __permute_even_even_char(__uchar64, __uchar64, __uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __permute_even_even_int                                                */
/*----------------------------------------------------------------------------*/
/*
VPERMEEW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __BIF __permute_even_even_int(__uchar32, __uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __permute_even_even_int(__uchar64, __uchar64, __uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __permute_even_even_long                                               */
/*----------------------------------------------------------------------------*/
/*
VPERMEED
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __BIF __permute_even_even_long(__uchar32, __uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __permute_even_even_long(__uchar64, __uchar64, __uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __permute_even_even_quad                                               */
/*----------------------------------------------------------------------------*/
/*
VPERMEEQ
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __BIF __permute_even_even_quad(__uchar32, __uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __permute_even_even_quad(__uchar64, __uchar64, __uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __permute_even_even_short                                              */
/*----------------------------------------------------------------------------*/
/*
VPERMEEH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __BIF __permute_even_even_short(__uchar32, __uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __permute_even_even_short(__uchar64, __uchar64, __uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __permute_even_odd_char                                                */
/*----------------------------------------------------------------------------*/
/*
VPERMEOB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __BIF __permute_even_odd_char(__uchar32, __uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __permute_even_odd_char(__uchar64, __uchar64, __uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __permute_even_odd_int                                                 */
/*----------------------------------------------------------------------------*/
/*
VPERMEOW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __BIF __permute_even_odd_int(__uchar32, __uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __permute_even_odd_int(__uchar64, __uchar64, __uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __permute_even_odd_long                                                */
/*----------------------------------------------------------------------------*/
/*
VPERMEOD
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __BIF __permute_even_odd_long(__uchar32, __uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __permute_even_odd_long(__uchar64, __uchar64, __uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __permute_even_odd_quad                                                */
/*----------------------------------------------------------------------------*/
/*
VPERMEOQ
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __BIF __permute_even_odd_quad(__uchar32, __uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __permute_even_odd_quad(__uchar64, __uchar64, __uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __permute_even_odd_short                                               */
/*----------------------------------------------------------------------------*/
/*
VPERMEOH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __BIF __permute_even_odd_short(__uchar32, __uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __permute_even_odd_short(__uchar64, __uchar64, __uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __permute_high_high                                                    */
/*----------------------------------------------------------------------------*/
/*
VPERMHH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __BIF __permute_high_high(__uchar32, __uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __permute_high_high(__uchar64, __uchar64, __uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __permute_low_high                                                     */
/*----------------------------------------------------------------------------*/
/*
VPERMLH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __BIF __permute_low_high(__uchar32, __uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __permute_low_high(__uchar64, __uchar64, __uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __permute_low_low                                                      */
/*----------------------------------------------------------------------------*/
/*
VPERMLL
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __BIF __permute_low_low(__uchar32, __uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __permute_low_low(__uchar64, __uchar64, __uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __permute_odd_odd_char                                                 */
/*----------------------------------------------------------------------------*/
/*
VPERMOOB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __BIF __permute_odd_odd_char(__uchar32, __uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __permute_odd_odd_char(__uchar64, __uchar64, __uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __permute_odd_odd_int                                                  */
/*----------------------------------------------------------------------------*/
/*
VPERMOOW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __BIF __permute_odd_odd_int(__uchar32, __uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __permute_odd_odd_int(__uchar64, __uchar64, __uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __permute_odd_odd_long                                                 */
/*----------------------------------------------------------------------------*/
/*
VPERMOOD
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __BIF __permute_odd_odd_long(__uchar32, __uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __permute_odd_odd_long(__uchar64, __uchar64, __uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __permute_odd_odd_quad                                                 */
/*----------------------------------------------------------------------------*/
/*
VPERMOOQ
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __BIF __permute_odd_odd_quad(__uchar32, __uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __permute_odd_odd_quad(__uchar64, __uchar64, __uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __permute_odd_odd_short                                                */
/*----------------------------------------------------------------------------*/
/*
VPERMOOH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __BIF __permute_odd_odd_short(__uchar32, __uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __permute_odd_odd_short(__uchar64, __uchar64, __uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __popcount                                                             */
/*----------------------------------------------------------------------------*/
/*
VBITCNTB
*/
signed char __OVBIF __popcount(signed char);
__char2 __OVBIF __popcount(__char2);
__char3 __OVBIF __popcount(__char3);
__char4 __OVBIF __popcount(__char4);
__char8 __OVBIF __popcount(__char8);
__char16 __OVBIF __popcount(__char16);
__char32 __OVBIF __popcount(__char32);
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __popcount(__char64);
#endif
__uchar __OVBIF __popcount(__uchar);
__uchar2 __OVBIF __popcount(__uchar2);
__uchar3 __OVBIF __popcount(__uchar3);
__uchar4 __OVBIF __popcount(__uchar4);
__uchar8 __OVBIF __popcount(__uchar8);
__uchar16 __OVBIF __popcount(__uchar16);
__uchar32 __OVBIF __popcount(__uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __popcount(__uchar64);
#endif
/*
VBITCNTH
*/
short __OVBIF __popcount(short);
__short2 __OVBIF __popcount(__short2);
__short3 __OVBIF __popcount(__short3);
__short4 __OVBIF __popcount(__short4);
__short8 __OVBIF __popcount(__short8);
__short16 __OVBIF __popcount(__short16);
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __popcount(__short32);
#endif
__ushort __OVBIF __popcount(__ushort);
__ushort2 __OVBIF __popcount(__ushort2);
__ushort3 __OVBIF __popcount(__ushort3);
__ushort4 __OVBIF __popcount(__ushort4);
__ushort8 __OVBIF __popcount(__ushort8);
__ushort16 __OVBIF __popcount(__ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __popcount(__ushort32);
#endif
/*
VBITCNTW
*/
int __OVBIF __popcount(int);
__int2 __OVBIF __popcount(__int2);
__int3 __OVBIF __popcount(__int3);
__int4 __OVBIF __popcount(__int4);
__int8 __OVBIF __popcount(__int8);
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __popcount(__int16);
#endif
__uint __OVBIF __popcount(__uint);
__uint2 __OVBIF __popcount(__uint2);
__uint3 __OVBIF __popcount(__uint3);
__uint4 __OVBIF __popcount(__uint4);
__uint8 __OVBIF __popcount(__uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __popcount(__uint16);
#endif
/*
VBITCNTD
*/
long __OVBIF __popcount(long);
__long2 __OVBIF __popcount(__long2);
__long3 __OVBIF __popcount(__long3);
__long4 __OVBIF __popcount(__long4);
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __popcount(__long8);
#endif
__ulong __OVBIF __popcount(__ulong);
__ulong2 __OVBIF __popcount(__ulong2);
__ulong3 __OVBIF __popcount(__ulong3);
__ulong4 __OVBIF __popcount(__ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __popcount(__ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __recip                                                                */
/*----------------------------------------------------------------------------*/
/*
VRCPSP
*/
float __OVBIF __recip(float);
__float2 __OVBIF __recip(__float2);
__float3 __OVBIF __recip(__float3);
__float4 __OVBIF __recip(__float4);
__float8 __OVBIF __recip(__float8);
#if __C7X_VEC_SIZE_BITS__ == 512
__float16 __OVBIF __recip(__float16);
#endif
/*
VRCPDP
*/
double __OVBIF __recip(double);
__double2 __OVBIF __recip(__double2);
__double3 __OVBIF __recip(__double3);
__double4 __OVBIF __recip(__double4);
#if __C7X_VEC_SIZE_BITS__ == 512
__double8 __OVBIF __recip(__double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __recip_sqrt                                                           */
/*----------------------------------------------------------------------------*/
/*
VRSQRSP
*/
float __OVBIF __recip_sqrt(float);
__float2 __OVBIF __recip_sqrt(__float2);
__float3 __OVBIF __recip_sqrt(__float3);
__float4 __OVBIF __recip_sqrt(__float4);
__float8 __OVBIF __recip_sqrt(__float8);
#if __C7X_VEC_SIZE_BITS__ == 512
__float16 __OVBIF __recip_sqrt(__float16);
#endif
/*
VRSQRDP
*/
double __OVBIF __recip_sqrt(double);
__double2 __OVBIF __recip_sqrt(__double2);
__double3 __OVBIF __recip_sqrt(__double3);
__double4 __OVBIF __recip_sqrt(__double4);
#if __C7X_VEC_SIZE_BITS__ == 512
__double8 __OVBIF __recip_sqrt(__double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __replace                                                              */
/*----------------------------------------------------------------------------*/
/*
REPLACE, VREPLACE
*/
long __OVBIF __replace(long, signed char __CST(0, 63), signed char __CST(0, 63), long);
__long2 __OVBIF __replace(__long2, __char2 __CST(0, 63), __char2 __CST(0, 63), __long2);
__long3 __OVBIF __replace(__long3, __char3 __CST(0, 63), __char3 __CST(0, 63), __long3);
__long4 __OVBIF __replace(__long4, __char4 __CST(0, 63), __char4 __CST(0, 63), __long4);
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __replace(__long8, __char8 __CST(0, 63), __char8 __CST(0, 63), __long8);
#endif
__ulong __OVBIF __replace(__ulong, __uchar __CST(0, 63), __uchar __CST(0, 63), __ulong);
__ulong2 __OVBIF __replace(__ulong2, __uchar2 __CST(0, 63), __uchar2 __CST(0, 63), __ulong2);
__ulong3 __OVBIF __replace(__ulong3, __uchar3 __CST(0, 63), __uchar3 __CST(0, 63), __ulong3);
__ulong4 __OVBIF __replace(__ulong4, __uchar4 __CST(0, 63), __uchar4 __CST(0, 63), __ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __replace(__ulong8, __uchar8 __CST(0, 63), __uchar8 __CST(0, 63), __ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __reverse                                                              */
/*----------------------------------------------------------------------------*/
/*
VREVERSEB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __OVBIF __reverse(__char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __reverse(__char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __OVBIF __reverse(__uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __reverse(__uchar64);
#endif
/*
VREVERSEH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cchar16 __OVBIF __reverse(__cchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cchar32 __OVBIF __reverse(__cchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __OVBIF __reverse(__short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __reverse(__short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __OVBIF __reverse(__ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __reverse(__ushort32);
#endif
/*
VREVERSEW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cshort8 __OVBIF __reverse(__cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cshort16 __OVBIF __reverse(__cshort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __OVBIF __reverse(__int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __reverse(__int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __OVBIF __reverse(__uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __reverse(__uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__float8 __OVBIF __reverse(__float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__float16 __OVBIF __reverse(__float16);
#endif
/*
VREVERSED
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cint4 __OVBIF __reverse(__cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cint8 __OVBIF __reverse(__cint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cfloat4 __OVBIF __reverse(__cfloat4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cfloat8 __OVBIF __reverse(__cfloat8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __OVBIF __reverse(__long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __reverse(__long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __OVBIF __reverse(__ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __reverse(__ulong8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__double4 __OVBIF __reverse(__double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__double8 __OVBIF __reverse(__double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __rhadd                                                                */
/*----------------------------------------------------------------------------*/
/*
VAVGB
*/
signed char __OVBIF __rhadd(signed char, signed char);
__char2 __OVBIF __rhadd(__char2, __char2);
__char3 __OVBIF __rhadd(__char3, __char3);
__char4 __OVBIF __rhadd(__char4, __char4);
__char8 __OVBIF __rhadd(__char8, __char8);
__char16 __OVBIF __rhadd(__char16, __char16);
__char32 __OVBIF __rhadd(__char32, __char32);
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __rhadd(__char64, __char64);
#endif
/*
VAVGUB
*/
__uchar __OVBIF __rhadd(__uchar, __uchar);
__uchar2 __OVBIF __rhadd(__uchar2, __uchar2);
__uchar3 __OVBIF __rhadd(__uchar3, __uchar3);
__uchar4 __OVBIF __rhadd(__uchar4, __uchar4);
__uchar8 __OVBIF __rhadd(__uchar8, __uchar8);
__uchar16 __OVBIF __rhadd(__uchar16, __uchar16);
__uchar32 __OVBIF __rhadd(__uchar32, __uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __rhadd(__uchar64, __uchar64);
#endif
/*
VAVGH
*/
short __OVBIF __rhadd(short, short);
__short2 __OVBIF __rhadd(__short2, __short2);
__short3 __OVBIF __rhadd(__short3, __short3);
__short4 __OVBIF __rhadd(__short4, __short4);
__short8 __OVBIF __rhadd(__short8, __short8);
__short16 __OVBIF __rhadd(__short16, __short16);
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __rhadd(__short32, __short32);
#endif
/*
VAVGUH
*/
__ushort __OVBIF __rhadd(__ushort, __ushort);
__ushort2 __OVBIF __rhadd(__ushort2, __ushort2);
__ushort3 __OVBIF __rhadd(__ushort3, __ushort3);
__ushort4 __OVBIF __rhadd(__ushort4, __ushort4);
__ushort8 __OVBIF __rhadd(__ushort8, __ushort8);
__ushort16 __OVBIF __rhadd(__ushort16, __ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __rhadd(__ushort32, __ushort32);
#endif
/*
VAVGW
*/
int __OVBIF __rhadd(int, int);
__int2 __OVBIF __rhadd(__int2, __int2);
__int3 __OVBIF __rhadd(__int3, __int3);
__int4 __OVBIF __rhadd(__int4, __int4);
__int8 __OVBIF __rhadd(__int8, __int8);
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __rhadd(__int16, __int16);
#endif
/*
VAVGUW
*/
__uint __OVBIF __rhadd(__uint, __uint);
__uint2 __OVBIF __rhadd(__uint2, __uint2);
__uint3 __OVBIF __rhadd(__uint3, __uint3);
__uint4 __OVBIF __rhadd(__uint4, __uint4);
__uint8 __OVBIF __rhadd(__uint8, __uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __rhadd(__uint16, __uint16);
#endif
/*
VAVGD
*/
long __OVBIF __rhadd(long, long);
__long2 __OVBIF __rhadd(__long2, __long2);
__long3 __OVBIF __rhadd(__long3, __long3);
__long4 __OVBIF __rhadd(__long4, __long4);
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __rhadd(__long8, __long8);
#endif
/*
VAVGUD
*/
__ulong __OVBIF __rhadd(__ulong, __ulong);
__ulong2 __OVBIF __rhadd(__ulong2, __ulong2);
__ulong3 __OVBIF __rhadd(__ulong3, __ulong3);
__ulong4 __OVBIF __rhadd(__ulong4, __ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __rhadd(__ulong8, __ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __rotate_left                                                          */
/*----------------------------------------------------------------------------*/
/*
VROTLB
*/
__uchar __OVBIF __rotate_left(__uchar, __uchar __CST(0, 63));
__uchar2 __OVBIF __rotate_left(__uchar2, __uchar2 __CST(0, 63));
__uchar3 __OVBIF __rotate_left(__uchar3, __uchar3 __CST(0, 63));
__uchar4 __OVBIF __rotate_left(__uchar4, __uchar4 __CST(0, 63));
__uchar8 __OVBIF __rotate_left(__uchar8, __uchar8 __CST(0, 63));
__uchar16 __OVBIF __rotate_left(__uchar16, __uchar16 __CST(0, 63));
__uchar32 __OVBIF __rotate_left(__uchar32, __uchar32 __CST(0, 63));
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __rotate_left(__uchar64, __uchar64 __CST(0, 63));
#endif
__uchar4 __OVBIF __rotate_left(__uchar4, __uint);
__uchar8 __OVBIF __rotate_left(__uchar8, __uint2);
__uchar16 __OVBIF __rotate_left(__uchar16, __uint4);
__uchar32 __OVBIF __rotate_left(__uchar32, __uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __rotate_left(__uchar64, __uint16);
#endif
/*
VROTLH
*/
__ushort __OVBIF __rotate_left(__ushort, __ushort __CST(0, 63));
__ushort2 __OVBIF __rotate_left(__ushort2, __ushort2 __CST(0, 63));
__ushort3 __OVBIF __rotate_left(__ushort3, __ushort3 __CST(0, 63));
__ushort4 __OVBIF __rotate_left(__ushort4, __ushort4 __CST(0, 63));
__ushort8 __OVBIF __rotate_left(__ushort8, __ushort8 __CST(0, 63));
__ushort16 __OVBIF __rotate_left(__ushort16, __ushort16 __CST(0, 63));
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __rotate_left(__ushort32, __ushort32 __CST(0, 63));
#endif
__ushort2 __OVBIF __rotate_left(__ushort2, __uint);
__ushort4 __OVBIF __rotate_left(__ushort4, __uint2);
__ushort8 __OVBIF __rotate_left(__ushort8, __uint4);
__ushort16 __OVBIF __rotate_left(__ushort16, __uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __rotate_left(__ushort32, __uint16);
#endif
/*
VROTLW
*/
int __OVBIF __rotate_left(int, __uchar __CST(0, 63));
__int2 __OVBIF __rotate_left(__int2, __uchar2 __CST(0, 63));
__int3 __OVBIF __rotate_left(__int3, __uchar3 __CST(0, 63));
__int4 __OVBIF __rotate_left(__int4, __uchar4 __CST(0, 63));
__int8 __OVBIF __rotate_left(__int8, __uchar8 __CST(0, 63));
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __rotate_left(__int16, __uchar16 __CST(0, 63));
#endif
int __OVBIF __rotate_left(int, __uint);
__int2 __OVBIF __rotate_left(__int2, __uint2);
__int3 __OVBIF __rotate_left(__int3, __uint3);
__int4 __OVBIF __rotate_left(__int4, __uint4);
__int8 __OVBIF __rotate_left(__int8, __uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __rotate_left(__int16, __uint16);
#endif
/*
VROTLD
*/
__ulong __OVBIF __rotate_left(__ulong, __uchar __CST(0, 63));
__ulong2 __OVBIF __rotate_left(__ulong2, __uchar2 __CST(0, 63));
__ulong3 __OVBIF __rotate_left(__ulong3, __uchar3 __CST(0, 63));
__ulong4 __OVBIF __rotate_left(__ulong4, __uchar4 __CST(0, 63));
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __rotate_left(__ulong8, __uchar8 __CST(0, 63));
#endif
__ulong __OVBIF __rotate_left(__ulong, __ulong);
__ulong2 __OVBIF __rotate_left(__ulong2, __ulong2);
__ulong3 __OVBIF __rotate_left(__ulong3, __ulong3);
__ulong4 __OVBIF __rotate_left(__ulong4, __ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __rotate_left(__ulong8, __ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __saturate                                                             */
/*----------------------------------------------------------------------------*/
/*
VGSATH
*/
short __OVBIF __saturate(short, __uchar __CST(0, 63));
__short2 __OVBIF __saturate(__short2, __uchar2 __CST(0, 63));
__short3 __OVBIF __saturate(__short3, __uchar3 __CST(0, 63));
__short4 __OVBIF __saturate(__short4, __uchar4 __CST(0, 63));
__short8 __OVBIF __saturate(__short8, __uchar8 __CST(0, 63));
__short16 __OVBIF __saturate(__short16, __uchar16 __CST(0, 63));
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __saturate(__short32, __uchar32 __CST(0, 63));
#endif
/*
VGSATUH
*/
__ushort __OVBIF __saturate(__ushort, __uchar __CST(0, 63));
__ushort2 __OVBIF __saturate(__ushort2, __uchar2 __CST(0, 63));
__ushort3 __OVBIF __saturate(__ushort3, __uchar3 __CST(0, 63));
__ushort4 __OVBIF __saturate(__ushort4, __uchar4 __CST(0, 63));
__ushort8 __OVBIF __saturate(__ushort8, __uchar8 __CST(0, 63));
__ushort16 __OVBIF __saturate(__ushort16, __uchar16 __CST(0, 63));
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __saturate(__ushort32, __uchar32 __CST(0, 63));
#endif
/*
VGSATW
*/
int __OVBIF __saturate(int, __uchar __CST(0, 63));
__int2 __OVBIF __saturate(__int2, __uchar2 __CST(0, 63));
__int3 __OVBIF __saturate(__int3, __uchar3 __CST(0, 63));
__int4 __OVBIF __saturate(__int4, __uchar4 __CST(0, 63));
__int8 __OVBIF __saturate(__int8, __uchar8 __CST(0, 63));
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __saturate(__int16, __uchar16 __CST(0, 63));
#endif
/*
VGSATUW
*/
__uint __OVBIF __saturate(__uint, __uchar __CST(0, 63));
__uint2 __OVBIF __saturate(__uint2, __uchar2 __CST(0, 63));
__uint3 __OVBIF __saturate(__uint3, __uchar3 __CST(0, 63));
__uint4 __OVBIF __saturate(__uint4, __uchar4 __CST(0, 63));
__uint8 __OVBIF __saturate(__uint8, __uchar8 __CST(0, 63));
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __saturate(__uint16, __uchar16 __CST(0, 63));
#endif
/*
VGSATD
*/
long __OVBIF __saturate(long, __uchar __CST(0, 63));
__long2 __OVBIF __saturate(__long2, __uchar2 __CST(0, 63));
__long3 __OVBIF __saturate(__long3, __uchar3 __CST(0, 63));
__long4 __OVBIF __saturate(__long4, __uchar4 __CST(0, 63));
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __saturate(__long8, __uchar8 __CST(0, 63));
#endif
/*
VGSATUD
*/
__ulong __OVBIF __saturate(__ulong, __uchar __CST(0, 63));
__ulong2 __OVBIF __saturate(__ulong2, __uchar2 __CST(0, 63));
__ulong3 __OVBIF __saturate(__ulong3, __uchar3 __CST(0, 63));
__ulong4 __OVBIF __saturate(__ulong4, __uchar4 __CST(0, 63));
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __saturate(__ulong8, __uchar8 __CST(0, 63));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __saturate_s2u                                                         */
/*----------------------------------------------------------------------------*/
/*
VGSATSUH
*/
__ushort __OVBIF __saturate_s2u(short, __uchar __CST(0, 63));
__ushort2 __OVBIF __saturate_s2u(__short2, __uchar2 __CST(0, 63));
__ushort3 __OVBIF __saturate_s2u(__short3, __uchar3 __CST(0, 63));
__ushort4 __OVBIF __saturate_s2u(__short4, __uchar4 __CST(0, 63));
__ushort8 __OVBIF __saturate_s2u(__short8, __uchar8 __CST(0, 63));
__ushort16 __OVBIF __saturate_s2u(__short16, __uchar16 __CST(0, 63));
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __saturate_s2u(__short32, __uchar32 __CST(0, 63));
#endif
/*
VGSATSUW
*/
__uint __OVBIF __saturate_s2u(int, __uchar __CST(0, 63));
__uint2 __OVBIF __saturate_s2u(__int2, __uchar2 __CST(0, 63));
__uint3 __OVBIF __saturate_s2u(__int3, __uchar3 __CST(0, 63));
__uint4 __OVBIF __saturate_s2u(__int4, __uchar4 __CST(0, 63));
__uint8 __OVBIF __saturate_s2u(__int8, __uchar8 __CST(0, 63));
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __saturate_s2u(__int16, __uchar16 __CST(0, 63));
#endif
/*
VGSATSUD
*/
__ulong __OVBIF __saturate_s2u(long, __uchar __CST(0, 63));
__ulong2 __OVBIF __saturate_s2u(__long2, __uchar2 __CST(0, 63));
__ulong3 __OVBIF __saturate_s2u(__long3, __uchar3 __CST(0, 63));
__ulong4 __OVBIF __saturate_s2u(__long4, __uchar4 __CST(0, 63));
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __saturate_s2u(__long8, __uchar8 __CST(0, 63));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __scale                                                                */
/*----------------------------------------------------------------------------*/
/*
VSCALESP
*/
float __OVBIF __scale(float, __uint);
__float2 __OVBIF __scale(__float2, __uint2);
__float3 __OVBIF __scale(__float3, __uint3);
__float4 __OVBIF __scale(__float4, __uint4);
__float8 __OVBIF __scale(__float8, __uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
__float16 __OVBIF __scale(__float16, __uint16);
#endif
/*
VSCALEDP
*/
double __OVBIF __scale(double, __ulong);
__double2 __OVBIF __scale(__double2, __ulong2);
__double3 __OVBIF __scale(__double3, __ulong3);
__double4 __OVBIF __scale(__double4, __ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
__double8 __OVBIF __scale(__double8, __ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __select                                                               */
/*----------------------------------------------------------------------------*/
/*
VSEL
*/
__char2 __OVBIF __select(__bool2, __char2, __char2);
__char3 __OVBIF __select(__bool3, __char3, __char3);
__char4 __OVBIF __select(__bool4, __char4, __char4);
__char8 __OVBIF __select(__bool8, __char8, __char8);
__char16 __OVBIF __select(__bool16, __char16, __char16);
__char32 __OVBIF __select(__bool32, __char32, __char32);
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __select(__bool64, __char64, __char64);
#endif
__uchar2 __OVBIF __select(__bool2, __uchar2, __uchar2);
__uchar3 __OVBIF __select(__bool3, __uchar3, __uchar3);
__uchar4 __OVBIF __select(__bool4, __uchar4, __uchar4);
__uchar8 __OVBIF __select(__bool8, __uchar8, __uchar8);
__uchar16 __OVBIF __select(__bool16, __uchar16, __uchar16);
__uchar32 __OVBIF __select(__bool32, __uchar32, __uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __select(__bool64, __uchar64, __uchar64);
#endif
__cchar2 __OVBIF __select(__bool2, __cchar2, __cchar2);
__cchar4 __OVBIF __select(__bool4, __cchar4, __cchar4);
__cchar8 __OVBIF __select(__bool8, __cchar8, __cchar8);
__cchar16 __OVBIF __select(__bool16, __cchar16, __cchar16);
#if __C7X_VEC_SIZE_BITS__ == 512
__cchar32 __OVBIF __select(__bool32, __cchar32, __cchar32);
#endif
__short2 __OVBIF __select(__bool2, __short2, __short2);
__short3 __OVBIF __select(__bool3, __short3, __short3);
__short4 __OVBIF __select(__bool4, __short4, __short4);
__short8 __OVBIF __select(__bool8, __short8, __short8);
__short16 __OVBIF __select(__bool16, __short16, __short16);
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __select(__bool32, __short32, __short32);
#endif
__ushort2 __OVBIF __select(__bool2, __ushort2, __ushort2);
__ushort3 __OVBIF __select(__bool3, __ushort3, __ushort3);
__ushort4 __OVBIF __select(__bool4, __ushort4, __ushort4);
__ushort8 __OVBIF __select(__bool8, __ushort8, __ushort8);
__ushort16 __OVBIF __select(__bool16, __ushort16, __ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __select(__bool32, __ushort32, __ushort32);
#endif
__cshort2 __OVBIF __select(__bool2, __cshort2, __cshort2);
__cshort4 __OVBIF __select(__bool4, __cshort4, __cshort4);
__cshort8 __OVBIF __select(__bool8, __cshort8, __cshort8);
#if __C7X_VEC_SIZE_BITS__ == 512
__cshort16 __OVBIF __select(__bool16, __cshort16, __cshort16);
#endif
__int2 __OVBIF __select(__bool2, __int2, __int2);
/*
__int2 __OVBIF __select(__bool2, __int2, __int2 __CST(-2147483648, 2147483647));
*/
__int3 __OVBIF __select(__bool3, __int3, __int3);
/*
__int3 __OVBIF __select(__bool3, __int3, __int3 __CST(-2147483648, 2147483647));
*/
__int4 __OVBIF __select(__bool4, __int4, __int4);
/*
__int4 __OVBIF __select(__bool4, __int4, __int4 __CST(-2147483648, 2147483647));
*/
__int8 __OVBIF __select(__bool8, __int8, __int8);
/*
__int8 __OVBIF __select(__bool8, __int8, __int8 __CST(-2147483648, 2147483647));
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __select(__bool16, __int16, __int16);
/*
__int16 __OVBIF __select(__bool16, __int16, __int16 __CST(-2147483648, 2147483647));
*/
#endif
__uint2 __OVBIF __select(__bool2, __uint2, __uint2);
/*
__uint2 __OVBIF __select(__bool2, __uint2, __uint2 __CST(0, 4294967295));
*/
__uint3 __OVBIF __select(__bool3, __uint3, __uint3);
/*
__uint3 __OVBIF __select(__bool3, __uint3, __uint3 __CST(0, 4294967295));
*/
__uint4 __OVBIF __select(__bool4, __uint4, __uint4);
/*
__uint4 __OVBIF __select(__bool4, __uint4, __uint4 __CST(0, 4294967295));
*/
__uint8 __OVBIF __select(__bool8, __uint8, __uint8);
/*
__uint8 __OVBIF __select(__bool8, __uint8, __uint8 __CST(0, 4294967295));
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __select(__bool16, __uint16, __uint16);
/*
__uint16 __OVBIF __select(__bool16, __uint16, __uint16 __CST(0, 4294967295));
*/
#endif
__float2 __OVBIF __select(__bool2, __float2, __float2);
/*
__float2 __OVBIF __select(__bool2, __float2, __float2 k);
*/
__float3 __OVBIF __select(__bool3, __float3, __float3);
/*
__float3 __OVBIF __select(__bool3, __float3, __float3 k);
*/
__float4 __OVBIF __select(__bool4, __float4, __float4);
/*
__float4 __OVBIF __select(__bool4, __float4, __float4 k);
*/
__float8 __OVBIF __select(__bool8, __float8, __float8);
/*
__float8 __OVBIF __select(__bool8, __float8, __float8 k);
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__float16 __OVBIF __select(__bool16, __float16, __float16);
/*
__float16 __OVBIF __select(__bool16, __float16, __float16 k);
*/
#endif
__cint2 __OVBIF __select(__bool2, __cint2, __cint2);
__cint4 __OVBIF __select(__bool4, __cint4, __cint4);
#if __C7X_VEC_SIZE_BITS__ == 512
__cint8 __OVBIF __select(__bool8, __cint8, __cint8);
#endif
__cfloat2 __OVBIF __select(__bool2, __cfloat2, __cfloat2);
__cfloat4 __OVBIF __select(__bool4, __cfloat4, __cfloat4);
#if __C7X_VEC_SIZE_BITS__ == 512
__cfloat8 __OVBIF __select(__bool8, __cfloat8, __cfloat8);
#endif
__long2 __OVBIF __select(__bool2, __long2, __long2);
__long3 __OVBIF __select(__bool3, __long3, __long3);
__long4 __OVBIF __select(__bool4, __long4, __long4);
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __select(__bool8, __long8, __long8);
#endif
__ulong2 __OVBIF __select(__bool2, __ulong2, __ulong2);
__ulong3 __OVBIF __select(__bool3, __ulong3, __ulong3);
__ulong4 __OVBIF __select(__bool4, __ulong4, __ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __select(__bool8, __ulong8, __ulong8);
#endif
__double2 __OVBIF __select(__bool2, __double2, __double2);
__double3 __OVBIF __select(__bool3, __double3, __double3);
__double4 __OVBIF __select(__bool4, __double4, __double4);
#if __C7X_VEC_SIZE_BITS__ == 512
__double8 __OVBIF __select(__bool8, __double8, __double8);
#endif
__clong2 __OVBIF __select(__bool2, __clong2, __clong2);
#if __C7X_VEC_SIZE_BITS__ == 512
__clong4 __OVBIF __select(__bool4, __clong4, __clong4);
#endif
__cdouble2 __OVBIF __select(__bool2, __cdouble2, __cdouble2);
#if __C7X_VEC_SIZE_BITS__ == 512
__cdouble4 __OVBIF __select(__bool4, __cdouble4, __cdouble4);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __set                                                                  */
/*----------------------------------------------------------------------------*/
/*
SET
*/
int __BIF __set(int, int);

/*----------------------------------------------------------------------------*/
/* ID: __set_vector_element                                                   */
/*----------------------------------------------------------------------------*/
/*
VPUTB
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __set_vector_element(signed char, signed char __CST(0, 63), __char64);
#endif
__char32 __OVBIF __set_vector_element(signed char, signed char __CST(0, 63), __char32);
__char16 __OVBIF __set_vector_element(signed char, signed char __CST(0, 63), __char16);
__char8 __OVBIF __set_vector_element(signed char, signed char __CST(0, 63), __char8);
__char4 __OVBIF __set_vector_element(signed char, signed char __CST(0, 63), __char4);
__char3 __OVBIF __set_vector_element(signed char, signed char __CST(0, 63), __char3);
__char2 __OVBIF __set_vector_element(signed char, signed char __CST(0, 63), __char2);
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __set_vector_element(__uchar, __uchar __CST(0, 63), __uchar64);
#endif
__uchar32 __OVBIF __set_vector_element(__uchar, __uchar __CST(0, 63), __uchar32);
__uchar16 __OVBIF __set_vector_element(__uchar, __uchar __CST(0, 63), __uchar16);
__uchar8 __OVBIF __set_vector_element(__uchar, __uchar __CST(0, 63), __uchar8);
__uchar4 __OVBIF __set_vector_element(__uchar, __uchar __CST(0, 63), __uchar4);
__uchar3 __OVBIF __set_vector_element(__uchar, __uchar __CST(0, 63), __uchar3);
__uchar2 __OVBIF __set_vector_element(__uchar, __uchar __CST(0, 63), __uchar2);
/*
VPUTH
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__cchar32 __OVBIF __set_vector_element(__cchar, signed char __CST(0, 63), __cchar32);
#endif
__cchar16 __OVBIF __set_vector_element(__cchar, signed char __CST(0, 63), __cchar16);
__cchar8 __OVBIF __set_vector_element(__cchar, signed char __CST(0, 63), __cchar8);
__cchar4 __OVBIF __set_vector_element(__cchar, signed char __CST(0, 63), __cchar4);
__cchar2 __OVBIF __set_vector_element(__cchar, signed char __CST(0, 63), __cchar2);
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __set_vector_element(short, signed char __CST(0, 63), __short32);
#endif
__short16 __OVBIF __set_vector_element(short, signed char __CST(0, 63), __short16);
__short8 __OVBIF __set_vector_element(short, signed char __CST(0, 63), __short8);
__short4 __OVBIF __set_vector_element(short, signed char __CST(0, 63), __short4);
__short3 __OVBIF __set_vector_element(short, signed char __CST(0, 63), __short3);
__short2 __OVBIF __set_vector_element(short, signed char __CST(0, 63), __short2);
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __set_vector_element(__ushort, __uchar __CST(0, 63), __ushort32);
#endif
__ushort16 __OVBIF __set_vector_element(__ushort, __uchar __CST(0, 63), __ushort16);
__ushort8 __OVBIF __set_vector_element(__ushort, __uchar __CST(0, 63), __ushort8);
__ushort4 __OVBIF __set_vector_element(__ushort, __uchar __CST(0, 63), __ushort4);
__ushort3 __OVBIF __set_vector_element(__ushort, __uchar __CST(0, 63), __ushort3);
__ushort2 __OVBIF __set_vector_element(__ushort, __uchar __CST(0, 63), __ushort2);
/*
VPUTW
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__cshort16 __OVBIF __set_vector_element(__cshort, signed char __CST(0, 63), __cshort16);
#endif
__cshort8 __OVBIF __set_vector_element(__cshort, signed char __CST(0, 63), __cshort8);
__cshort4 __OVBIF __set_vector_element(__cshort, signed char __CST(0, 63), __cshort4);
__cshort2 __OVBIF __set_vector_element(__cshort, signed char __CST(0, 63), __cshort2);
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __set_vector_element(int, signed char __CST(0, 63), __int16);
#endif
__int8 __OVBIF __set_vector_element(int, signed char __CST(0, 63), __int8);
__int4 __OVBIF __set_vector_element(int, signed char __CST(0, 63), __int4);
__int3 __OVBIF __set_vector_element(int, signed char __CST(0, 63), __int3);
__int2 __OVBIF __set_vector_element(int, signed char __CST(0, 63), __int2);
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __set_vector_element(__uint, __uchar __CST(0, 63), __uint16);
#endif
__uint8 __OVBIF __set_vector_element(__uint, __uchar __CST(0, 63), __uint8);
__uint4 __OVBIF __set_vector_element(__uint, __uchar __CST(0, 63), __uint4);
__uint3 __OVBIF __set_vector_element(__uint, __uchar __CST(0, 63), __uint3);
__uint2 __OVBIF __set_vector_element(__uint, __uchar __CST(0, 63), __uint2);
#if __C7X_VEC_SIZE_BITS__ == 512
__float16 __OVBIF __set_vector_element(float, signed char __CST(0, 63), __float16);
#endif
__float8 __OVBIF __set_vector_element(float, signed char __CST(0, 63), __float8);
__float4 __OVBIF __set_vector_element(float, signed char __CST(0, 63), __float4);
__float3 __OVBIF __set_vector_element(float, signed char __CST(0, 63), __float3);
__float2 __OVBIF __set_vector_element(float, signed char __CST(0, 63), __float2);
#if __C7X_VEC_SIZE_BITS__ == 512
__float16 __OVBIF __set_vector_element(float, __uchar __CST(0, 63), __float16);
#endif
__float8 __OVBIF __set_vector_element(float, __uchar __CST(0, 63), __float8);
__float4 __OVBIF __set_vector_element(float, __uchar __CST(0, 63), __float4);
__float3 __OVBIF __set_vector_element(float, __uchar __CST(0, 63), __float3);
__float2 __OVBIF __set_vector_element(float, __uchar __CST(0, 63), __float2);
/*
VPUTD
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__cint8 __OVBIF __set_vector_element(__cint, signed char __CST(0, 63), __cint8);
#endif
__cint4 __OVBIF __set_vector_element(__cint, signed char __CST(0, 63), __cint4);
__cint2 __OVBIF __set_vector_element(__cint, signed char __CST(0, 63), __cint2);
#if __C7X_VEC_SIZE_BITS__ == 512
__cfloat8 __OVBIF __set_vector_element(__cfloat, signed char __CST(0, 63), __cfloat8);
#endif
__cfloat4 __OVBIF __set_vector_element(__cfloat, signed char __CST(0, 63), __cfloat4);
__cfloat2 __OVBIF __set_vector_element(__cfloat, signed char __CST(0, 63), __cfloat2);
#if __C7X_VEC_SIZE_BITS__ == 512
__cfloat8 __OVBIF __set_vector_element(__cfloat, __uchar __CST(0, 63), __cfloat8);
#endif
__cfloat4 __OVBIF __set_vector_element(__cfloat, __uchar __CST(0, 63), __cfloat4);
__cfloat2 __OVBIF __set_vector_element(__cfloat, __uchar __CST(0, 63), __cfloat2);
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __set_vector_element(long, signed char __CST(0, 63), __long8);
#endif
__long4 __OVBIF __set_vector_element(long, signed char __CST(0, 63), __long4);
__long3 __OVBIF __set_vector_element(long, signed char __CST(0, 63), __long3);
__long2 __OVBIF __set_vector_element(long, signed char __CST(0, 63), __long2);
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __set_vector_element(__ulong, __uchar __CST(0, 63), __ulong8);
#endif
__ulong4 __OVBIF __set_vector_element(__ulong, __uchar __CST(0, 63), __ulong4);
__ulong3 __OVBIF __set_vector_element(__ulong, __uchar __CST(0, 63), __ulong3);
__ulong2 __OVBIF __set_vector_element(__ulong, __uchar __CST(0, 63), __ulong2);
#if __C7X_VEC_SIZE_BITS__ == 512
__double8 __OVBIF __set_vector_element(double, signed char __CST(0, 63), __double8);
#endif
__double4 __OVBIF __set_vector_element(double, signed char __CST(0, 63), __double4);
__double3 __OVBIF __set_vector_element(double, signed char __CST(0, 63), __double3);
__double2 __OVBIF __set_vector_element(double, signed char __CST(0, 63), __double2);
#if __C7X_VEC_SIZE_BITS__ == 512
__double8 __OVBIF __set_vector_element(double, __uchar __CST(0, 63), __double8);
#endif
__double4 __OVBIF __set_vector_element(double, __uchar __CST(0, 63), __double4);
__double3 __OVBIF __set_vector_element(double, __uchar __CST(0, 63), __double3);
__double2 __OVBIF __set_vector_element(double, __uchar __CST(0, 63), __double2);

/*----------------------------------------------------------------------------*/
/* ID: __shift_left                                                           */
/*----------------------------------------------------------------------------*/
/*
VSHLB
*/
signed char __OVBIF __shift_left(signed char, signed char __CST(0, 63));
__char2 __OVBIF __shift_left(__char2, __char2 __CST(0, 63));
__char3 __OVBIF __shift_left(__char3, __char3 __CST(0, 63));
__char4 __OVBIF __shift_left(__char4, __char4 __CST(0, 63));
__char8 __OVBIF __shift_left(__char8, __char8 __CST(0, 63));
__char16 __OVBIF __shift_left(__char16, __char16 __CST(0, 63));
__char32 __OVBIF __shift_left(__char32, __char32 __CST(0, 63));
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __shift_left(__char64, __char64 __CST(0, 63));
#endif
__char4 __OVBIF __shift_left(__char4, int);
__char8 __OVBIF __shift_left(__char8, __int2);
__char16 __OVBIF __shift_left(__char16, __int4);
__char32 __OVBIF __shift_left(__char32, __int8);
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __shift_left(__char64, __int16);
#endif
__uchar __OVBIF __shift_left(__uchar, __uchar __CST(0, 63));
__uchar2 __OVBIF __shift_left(__uchar2, __uchar2 __CST(0, 63));
__uchar3 __OVBIF __shift_left(__uchar3, __uchar3 __CST(0, 63));
__uchar4 __OVBIF __shift_left(__uchar4, __uchar4 __CST(0, 63));
__uchar8 __OVBIF __shift_left(__uchar8, __uchar8 __CST(0, 63));
__uchar16 __OVBIF __shift_left(__uchar16, __uchar16 __CST(0, 63));
__uchar32 __OVBIF __shift_left(__uchar32, __uchar32 __CST(0, 63));
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __shift_left(__uchar64, __uchar64 __CST(0, 63));
#endif
__uchar4 __OVBIF __shift_left(__uchar4, __uint);
__uchar8 __OVBIF __shift_left(__uchar8, __uint2);
__uchar16 __OVBIF __shift_left(__uchar16, __uint4);
__uchar32 __OVBIF __shift_left(__uchar32, __uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __shift_left(__uchar64, __uint16);
#endif
/*
VSHLH
*/
short __OVBIF __shift_left(short, short __CST(0, 63));
__short2 __OVBIF __shift_left(__short2, __short2 __CST(0, 63));
__short3 __OVBIF __shift_left(__short3, __short3 __CST(0, 63));
__short4 __OVBIF __shift_left(__short4, __short4 __CST(0, 63));
__short8 __OVBIF __shift_left(__short8, __short8 __CST(0, 63));
__short16 __OVBIF __shift_left(__short16, __short16 __CST(0, 63));
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __shift_left(__short32, __short32 __CST(0, 63));
#endif
__short2 __OVBIF __shift_left(__short2, int);
__short4 __OVBIF __shift_left(__short4, __int2);
__short8 __OVBIF __shift_left(__short8, __int4);
__short16 __OVBIF __shift_left(__short16, __int8);
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __shift_left(__short32, __int16);
#endif
__ushort __OVBIF __shift_left(__ushort, __ushort __CST(0, 63));
__ushort2 __OVBIF __shift_left(__ushort2, __ushort2 __CST(0, 63));
__ushort3 __OVBIF __shift_left(__ushort3, __ushort3 __CST(0, 63));
__ushort4 __OVBIF __shift_left(__ushort4, __ushort4 __CST(0, 63));
__ushort8 __OVBIF __shift_left(__ushort8, __ushort8 __CST(0, 63));
__ushort16 __OVBIF __shift_left(__ushort16, __ushort16 __CST(0, 63));
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __shift_left(__ushort32, __ushort32 __CST(0, 63));
#endif
__ushort2 __OVBIF __shift_left(__ushort2, __uint);
__ushort4 __OVBIF __shift_left(__ushort4, __uint2);
__ushort8 __OVBIF __shift_left(__ushort8, __uint4);
__ushort16 __OVBIF __shift_left(__ushort16, __uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __shift_left(__ushort32, __uint16);
#endif
/*
SHLW
*/
int __OVBIF __shift_left(int, __uchar __CST(0, 63));
/*
SHLW, VSHLW
*/
int __OVBIF __shift_left(int, int);
/*
int __OVBIF __shift_left(int, int __CST(0, 63));
*/
__int2 __OVBIF __shift_left(__int2, __int2);
/*
__int2 __OVBIF __shift_left(__int2, __int2 __CST(0, 63));
*/
__int3 __OVBIF __shift_left(__int3, __int3);
/*
__int3 __OVBIF __shift_left(__int3, __int3 __CST(0, 63));
*/
__int4 __OVBIF __shift_left(__int4, __int4);
/*
__int4 __OVBIF __shift_left(__int4, __int4 __CST(0, 63));
*/
__int8 __OVBIF __shift_left(__int8, __int8);
/*
__int8 __OVBIF __shift_left(__int8, __int8 __CST(0, 63));
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __shift_left(__int16, __int16);
/*
__int16 __OVBIF __shift_left(__int16, __int16 __CST(0, 63));
*/
#endif
/*
SHLW
*/
__uint __OVBIF __shift_left(__uint, __uchar __CST(0, 63));
/*
SHLW, VSHLW
*/
__uint __OVBIF __shift_left(__uint, __uint);
/*
__uint __OVBIF __shift_left(__uint, __uint __CST(0, 63));
*/
__uint2 __OVBIF __shift_left(__uint2, __uint2);
/*
__uint2 __OVBIF __shift_left(__uint2, __uint2 __CST(0, 63));
*/
__uint3 __OVBIF __shift_left(__uint3, __uint3);
/*
__uint3 __OVBIF __shift_left(__uint3, __uint3 __CST(0, 63));
*/
__uint4 __OVBIF __shift_left(__uint4, __uint4);
/*
__uint4 __OVBIF __shift_left(__uint4, __uint4 __CST(0, 63));
*/
__uint8 __OVBIF __shift_left(__uint8, __uint8);
/*
__uint8 __OVBIF __shift_left(__uint8, __uint8 __CST(0, 63));
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __shift_left(__uint16, __uint16);
/*
__uint16 __OVBIF __shift_left(__uint16, __uint16 __CST(0, 63));
*/
#endif
/*
SHLD
*/
long __OVBIF __shift_left(long, __uchar __CST(0, 63));
long __OVBIF __shift_left(long, int);
/*
VSHLD
*/
long __OVBIF __shift_left(long, long);
/*
long __OVBIF __shift_left(long, long __CST(0, 63));
*/
__long2 __OVBIF __shift_left(__long2, __long2);
/*
__long2 __OVBIF __shift_left(__long2, __long2 __CST(0, 63));
*/
__long3 __OVBIF __shift_left(__long3, __long3);
/*
__long3 __OVBIF __shift_left(__long3, __long3 __CST(0, 63));
*/
__long4 __OVBIF __shift_left(__long4, __long4);
/*
__long4 __OVBIF __shift_left(__long4, __long4 __CST(0, 63));
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __shift_left(__long8, __long8);
/*
__long8 __OVBIF __shift_left(__long8, __long8 __CST(0, 63));
*/
#endif
/*
SHLD
*/
__ulong __OVBIF __shift_left(__ulong, __uchar __CST(0, 63));
__ulong __OVBIF __shift_left(__ulong, __uint);
/*
VSHLD
*/
__ulong __OVBIF __shift_left(__ulong, __ulong);
/*
__ulong __OVBIF __shift_left(__ulong, __ulong __CST(0, 63));
*/
__ulong2 __OVBIF __shift_left(__ulong2, __ulong2);
/*
__ulong2 __OVBIF __shift_left(__ulong2, __ulong2 __CST(0, 63));
*/
__ulong3 __OVBIF __shift_left(__ulong3, __ulong3);
/*
__ulong3 __OVBIF __shift_left(__ulong3, __ulong3 __CST(0, 63));
*/
__ulong4 __OVBIF __shift_left(__ulong4, __ulong4);
/*
__ulong4 __OVBIF __shift_left(__ulong4, __ulong4 __CST(0, 63));
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __shift_left(__ulong8, __ulong8);
/*
__ulong8 __OVBIF __shift_left(__ulong8, __ulong8 __CST(0, 63));
*/
#endif

/*----------------------------------------------------------------------------*/
/* ID: __shift_left_conditional                                               */
/*----------------------------------------------------------------------------*/
/*
VSHLCB
*/
__char2 __OVBIF __shift_left_conditional(__bool2, __char2, __char2);
__char3 __OVBIF __shift_left_conditional(__bool3, __char3, __char3);
__char4 __OVBIF __shift_left_conditional(__bool4, __char4, __char4);
__char8 __OVBIF __shift_left_conditional(__bool8, __char8, __char8);
__char16 __OVBIF __shift_left_conditional(__bool16, __char16, __char16);
__char32 __OVBIF __shift_left_conditional(__bool32, __char32, __char32);
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __shift_left_conditional(__bool64, __char64, __char64);
#endif
__uchar2 __OVBIF __shift_left_conditional(__bool2, __uchar2, __uchar2);
__uchar3 __OVBIF __shift_left_conditional(__bool3, __uchar3, __uchar3);
__uchar4 __OVBIF __shift_left_conditional(__bool4, __uchar4, __uchar4);
__uchar8 __OVBIF __shift_left_conditional(__bool8, __uchar8, __uchar8);
__uchar16 __OVBIF __shift_left_conditional(__bool16, __uchar16, __uchar16);
__uchar32 __OVBIF __shift_left_conditional(__bool32, __uchar32, __uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __shift_left_conditional(__bool64, __uchar64, __uchar64);
#endif
/*
VSHLCH
*/
__short2 __OVBIF __shift_left_conditional(__bool2, __short2, __short2);
__short3 __OVBIF __shift_left_conditional(__bool3, __short3, __short3);
__short4 __OVBIF __shift_left_conditional(__bool4, __short4, __short4);
__short8 __OVBIF __shift_left_conditional(__bool8, __short8, __short8);
__short16 __OVBIF __shift_left_conditional(__bool16, __short16, __short16);
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __shift_left_conditional(__bool32, __short32, __short32);
#endif
__ushort2 __OVBIF __shift_left_conditional(__bool2, __ushort2, __ushort2);
__ushort3 __OVBIF __shift_left_conditional(__bool3, __ushort3, __ushort3);
__ushort4 __OVBIF __shift_left_conditional(__bool4, __ushort4, __ushort4);
__ushort8 __OVBIF __shift_left_conditional(__bool8, __ushort8, __ushort8);
__ushort16 __OVBIF __shift_left_conditional(__bool16, __ushort16, __ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __shift_left_conditional(__bool32, __ushort32, __ushort32);
#endif
/*
VSHLCW
*/
__int2 __OVBIF __shift_left_conditional(__bool2, __int2, __int2);
__int3 __OVBIF __shift_left_conditional(__bool3, __int3, __int3);
__int4 __OVBIF __shift_left_conditional(__bool4, __int4, __int4);
__int8 __OVBIF __shift_left_conditional(__bool8, __int8, __int8);
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __shift_left_conditional(__bool16, __int16, __int16);
#endif
__uint2 __OVBIF __shift_left_conditional(__bool2, __uint2, __uint2);
__uint3 __OVBIF __shift_left_conditional(__bool3, __uint3, __uint3);
__uint4 __OVBIF __shift_left_conditional(__bool4, __uint4, __uint4);
__uint8 __OVBIF __shift_left_conditional(__bool8, __uint8, __uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __shift_left_conditional(__bool16, __uint16, __uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __shift_left_full                                                      */
/*----------------------------------------------------------------------------*/
/*
VSHL
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __shift_left_full(__ulong8, __uchar __CST(1, 64));
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __OVBIF __shift_left_full(__ulong4, __uchar __CST(1, 64));
__ulong4 __OVBIF __shift_left_full(__ulong4, __ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __shift_left_full(__ulong8, __ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __shift_left_merge                                                     */
/*----------------------------------------------------------------------------*/
/*
VSHLM1B
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __shift_left_merge(__char64, signed char);
#endif
/*
VSHLM1B, VSHLM2B
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __OVBIF __shift_left_merge(__char32, signed char);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __shift_left_merge(__char64, __char2);
#endif
/*
VSHLM2B, VSHLM4B
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __OVBIF __shift_left_merge(__char32, __char2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __shift_left_merge(__char64, __char4);
#endif
/*
VSHLM4B, VSHLM8B
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __OVBIF __shift_left_merge(__char32, __char4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __shift_left_merge(__char64, __char8);
#endif
/*
VSHLM16B, VSHLM8B
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __OVBIF __shift_left_merge(__char32, __char8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __shift_left_merge(__char64, __char16);
#endif
/*
VSHLM16B
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __OVBIF __shift_left_merge(__char32, __char16);
#endif
/*
VSHLMB
*/
int __OVBIF __shift_left_merge(int, __char4);
__int2 __OVBIF __shift_left_merge(__int2, __char8);
__int4 __OVBIF __shift_left_merge(__int4, __char16);
__int8 __OVBIF __shift_left_merge(__int8, __char32);
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __shift_left_merge(__int16, __char64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __shift_left_round_sat                                                 */
/*----------------------------------------------------------------------------*/
/*
VSSHLRHB
*/
__char4 __OVBIF __shift_left_round_sat(__short2, __uchar __CST(0, 63));
__char8 __OVBIF __shift_left_round_sat(__short4, __uchar2 __CST(0, 63));
__char16 __OVBIF __shift_left_round_sat(__short8, __uchar4 __CST(0, 63));
__char32 __OVBIF __shift_left_round_sat(__short16, __uchar8 __CST(0, 63));
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __shift_left_round_sat(__short32, __uchar16 __CST(0, 63));
#endif
__char4 __OVBIF __shift_left_round_sat(__short2, __uint);
__char8 __OVBIF __shift_left_round_sat(__short4, __uint2);
__char16 __OVBIF __shift_left_round_sat(__short8, __uint4);
__char32 __OVBIF __shift_left_round_sat(__short16, __uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __shift_left_round_sat(__short32, __uint16);
#endif
/*
VSSHLURHB
*/
__uchar4 __OVBIF __shift_left_round_sat(__ushort2, __uchar __CST(0, 63));
__uchar8 __OVBIF __shift_left_round_sat(__ushort4, __uchar2 __CST(0, 63));
__uchar16 __OVBIF __shift_left_round_sat(__ushort8, __uchar4 __CST(0, 63));
__uchar32 __OVBIF __shift_left_round_sat(__ushort16, __uchar8 __CST(0, 63));
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __shift_left_round_sat(__ushort32, __uchar16 __CST(0, 63));
#endif
__uchar4 __OVBIF __shift_left_round_sat(__ushort2, __uint);
__uchar8 __OVBIF __shift_left_round_sat(__ushort4, __uint2);
__uchar16 __OVBIF __shift_left_round_sat(__ushort8, __uint4);
__uchar32 __OVBIF __shift_left_round_sat(__ushort16, __uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __shift_left_round_sat(__ushort32, __uint16);
#endif
/*
VSSHLRWH
*/
__short2 __OVBIF __shift_left_round_sat(int, __uchar __CST(0, 63));
__short4 __OVBIF __shift_left_round_sat(__int2, __uchar2 __CST(0, 63));
__short8 __OVBIF __shift_left_round_sat(__int4, __uchar4 __CST(0, 63));
__short16 __OVBIF __shift_left_round_sat(__int8, __uchar8 __CST(0, 63));
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __shift_left_round_sat(__int16, __uchar16 __CST(0, 63));
#endif
__short2 __OVBIF __shift_left_round_sat(int, __uint);
__short4 __OVBIF __shift_left_round_sat(__int2, __uint2);
__short8 __OVBIF __shift_left_round_sat(__int4, __uint4);
__short16 __OVBIF __shift_left_round_sat(__int8, __uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __shift_left_round_sat(__int16, __uint16);
#endif
/*
VSSHLURWH
*/
__ushort2 __OVBIF __shift_left_round_sat(__uint, __uchar __CST(0, 63));
__ushort4 __OVBIF __shift_left_round_sat(__uint2, __uchar2 __CST(0, 63));
__ushort8 __OVBIF __shift_left_round_sat(__uint4, __uchar4 __CST(0, 63));
__ushort16 __OVBIF __shift_left_round_sat(__uint8, __uchar8 __CST(0, 63));
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __shift_left_round_sat(__uint16, __uchar16 __CST(0, 63));
#endif
__ushort2 __OVBIF __shift_left_round_sat(__uint, __uint);
__ushort4 __OVBIF __shift_left_round_sat(__uint2, __uint2);
__ushort8 __OVBIF __shift_left_round_sat(__uint4, __uint4);
__ushort16 __OVBIF __shift_left_round_sat(__uint8, __uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __shift_left_round_sat(__uint16, __uint16);
#endif
/*
VSSHLRDW
*/
__int2 __OVBIF __shift_left_round_sat(long, __uchar __CST(0, 63));
__int4 __OVBIF __shift_left_round_sat(__long2, __uchar2 __CST(0, 63));
__int8 __OVBIF __shift_left_round_sat(__long4, __uchar4 __CST(0, 63));
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __shift_left_round_sat(__long8, __uchar8 __CST(0, 63));
#endif
__int2 __OVBIF __shift_left_round_sat(long, __ulong);
__int4 __OVBIF __shift_left_round_sat(__long2, __ulong2);
__int8 __OVBIF __shift_left_round_sat(__long4, __ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __shift_left_round_sat(__long8, __ulong8);
#endif
/*
VSSHLURDW
*/
__uint2 __OVBIF __shift_left_round_sat(__ulong, __uchar __CST(0, 63));
__uint4 __OVBIF __shift_left_round_sat(__ulong2, __uchar2 __CST(0, 63));
__uint8 __OVBIF __shift_left_round_sat(__ulong4, __uchar4 __CST(0, 63));
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __shift_left_round_sat(__ulong8, __uchar8 __CST(0, 63));
#endif
__uint2 __OVBIF __shift_left_round_sat(__ulong, __ulong);
__uint4 __OVBIF __shift_left_round_sat(__ulong2, __ulong2);
__uint8 __OVBIF __shift_left_round_sat(__ulong4, __ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __shift_left_round_sat(__ulong8, __ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __shift_left_round_sat_to_unsigned                                     */
/*----------------------------------------------------------------------------*/
/*
VSSHLSURHB
*/
__uchar4 __OVBIF __shift_left_round_sat_to_unsigned(__short2, __uchar __CST(0, 63));
__uchar8 __OVBIF __shift_left_round_sat_to_unsigned(__short4, __uchar2 __CST(0, 63));
__uchar16 __OVBIF __shift_left_round_sat_to_unsigned(__short8, __uchar4 __CST(0, 63));
__uchar32 __OVBIF __shift_left_round_sat_to_unsigned(__short16, __uchar8 __CST(0, 63));
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __shift_left_round_sat_to_unsigned(__short32, __uchar16 __CST(0, 63));
#endif
__uchar4 __OVBIF __shift_left_round_sat_to_unsigned(__short2, __uint);
__uchar8 __OVBIF __shift_left_round_sat_to_unsigned(__short4, __uint2);
__uchar16 __OVBIF __shift_left_round_sat_to_unsigned(__short8, __uint4);
__uchar32 __OVBIF __shift_left_round_sat_to_unsigned(__short16, __uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __shift_left_round_sat_to_unsigned(__short32, __uint16);
#endif
/*
VSSHLSURWH
*/
__ushort2 __OVBIF __shift_left_round_sat_to_unsigned(int, __uchar __CST(0, 63));
__ushort4 __OVBIF __shift_left_round_sat_to_unsigned(__int2, __uchar2 __CST(0, 63));
__ushort8 __OVBIF __shift_left_round_sat_to_unsigned(__int4, __uchar4 __CST(0, 63));
__ushort16 __OVBIF __shift_left_round_sat_to_unsigned(__int8, __uchar8 __CST(0, 63));
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __shift_left_round_sat_to_unsigned(__int16, __uchar16 __CST(0, 63));
#endif
__ushort2 __OVBIF __shift_left_round_sat_to_unsigned(int, __uint);
__ushort4 __OVBIF __shift_left_round_sat_to_unsigned(__int2, __uint2);
__ushort8 __OVBIF __shift_left_round_sat_to_unsigned(__int4, __uint4);
__ushort16 __OVBIF __shift_left_round_sat_to_unsigned(__int8, __uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __shift_left_round_sat_to_unsigned(__int16, __uint16);
#endif
/*
VSSHLSURDW
*/
__uint2 __OVBIF __shift_left_round_sat_to_unsigned(long, __uchar __CST(0, 63));
__uint4 __OVBIF __shift_left_round_sat_to_unsigned(__long2, __uchar2 __CST(0, 63));
__uint8 __OVBIF __shift_left_round_sat_to_unsigned(__long4, __uchar4 __CST(0, 63));
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __shift_left_round_sat_to_unsigned(__long8, __uchar8 __CST(0, 63));
#endif
__uint2 __OVBIF __shift_left_round_sat_to_unsigned(long, __ulong);
__uint4 __OVBIF __shift_left_round_sat_to_unsigned(__long2, __ulong2);
__uint8 __OVBIF __shift_left_round_sat_to_unsigned(__long4, __ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __shift_left_round_sat_to_unsigned(__long8, __ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __shift_left_sat                                                       */
/*----------------------------------------------------------------------------*/
/*
VSSHLH
*/
short __OVBIF __shift_left_sat(short, __uchar __CST(0, 63));
__short2 __OVBIF __shift_left_sat(__short2, __uchar2 __CST(0, 63));
__short3 __OVBIF __shift_left_sat(__short3, __uchar3 __CST(0, 63));
__short4 __OVBIF __shift_left_sat(__short4, __uchar4 __CST(0, 63));
__short8 __OVBIF __shift_left_sat(__short8, __uchar8 __CST(0, 63));
__short16 __OVBIF __shift_left_sat(__short16, __uchar16 __CST(0, 63));
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __shift_left_sat(__short32, __uchar32 __CST(0, 63));
#endif
__short2 __OVBIF __shift_left_sat(__short2, __uint);
__short4 __OVBIF __shift_left_sat(__short4, __uint2);
__short8 __OVBIF __shift_left_sat(__short8, __uint4);
__short16 __OVBIF __shift_left_sat(__short16, __uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __shift_left_sat(__short32, __uint16);
#endif
/*
VSSHLUH
*/
__ushort __OVBIF __shift_left_sat(__ushort, __uchar __CST(0, 63));
__ushort2 __OVBIF __shift_left_sat(__ushort2, __uchar2 __CST(0, 63));
__ushort3 __OVBIF __shift_left_sat(__ushort3, __uchar3 __CST(0, 63));
__ushort4 __OVBIF __shift_left_sat(__ushort4, __uchar4 __CST(0, 63));
__ushort8 __OVBIF __shift_left_sat(__ushort8, __uchar8 __CST(0, 63));
__ushort16 __OVBIF __shift_left_sat(__ushort16, __uchar16 __CST(0, 63));
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __shift_left_sat(__ushort32, __uchar32 __CST(0, 63));
#endif
__ushort2 __OVBIF __shift_left_sat(__ushort2, __uint);
__ushort4 __OVBIF __shift_left_sat(__ushort4, __uint2);
__ushort8 __OVBIF __shift_left_sat(__ushort8, __uint4);
__ushort16 __OVBIF __shift_left_sat(__ushort16, __uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __shift_left_sat(__ushort32, __uint16);
#endif
/*
VSSHLW
*/
int __OVBIF __shift_left_sat(int, __uchar __CST(0, 63));
__int2 __OVBIF __shift_left_sat(__int2, __uchar2 __CST(0, 63));
__int3 __OVBIF __shift_left_sat(__int3, __uchar3 __CST(0, 63));
__int4 __OVBIF __shift_left_sat(__int4, __uchar4 __CST(0, 63));
__int8 __OVBIF __shift_left_sat(__int8, __uchar8 __CST(0, 63));
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __shift_left_sat(__int16, __uchar16 __CST(0, 63));
#endif
int __OVBIF __shift_left_sat(int, __uint);
__int2 __OVBIF __shift_left_sat(__int2, __uint2);
__int3 __OVBIF __shift_left_sat(__int3, __uint3);
__int4 __OVBIF __shift_left_sat(__int4, __uint4);
__int8 __OVBIF __shift_left_sat(__int8, __uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __shift_left_sat(__int16, __uint16);
#endif
/*
VSSHLUW
*/
__uint __OVBIF __shift_left_sat(__uint, __uchar __CST(0, 63));
__uint2 __OVBIF __shift_left_sat(__uint2, __uchar2 __CST(0, 63));
__uint3 __OVBIF __shift_left_sat(__uint3, __uchar3 __CST(0, 63));
__uint4 __OVBIF __shift_left_sat(__uint4, __uchar4 __CST(0, 63));
__uint8 __OVBIF __shift_left_sat(__uint8, __uchar8 __CST(0, 63));
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __shift_left_sat(__uint16, __uchar16 __CST(0, 63));
#endif
__uint __OVBIF __shift_left_sat(__uint, __uint);
__uint2 __OVBIF __shift_left_sat(__uint2, __uint2);
__uint3 __OVBIF __shift_left_sat(__uint3, __uint3);
__uint4 __OVBIF __shift_left_sat(__uint4, __uint4);
__uint8 __OVBIF __shift_left_sat(__uint8, __uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __shift_left_sat(__uint16, __uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __shift_left_sat_to_unsigned                                           */
/*----------------------------------------------------------------------------*/
/*
VSSHLSUH
*/
__ushort __OVBIF __shift_left_sat_to_unsigned(short, __uchar __CST(0, 63));
__ushort2 __OVBIF __shift_left_sat_to_unsigned(__short2, __uchar2 __CST(0, 63));
__ushort3 __OVBIF __shift_left_sat_to_unsigned(__short3, __uchar3 __CST(0, 63));
__ushort4 __OVBIF __shift_left_sat_to_unsigned(__short4, __uchar4 __CST(0, 63));
__ushort8 __OVBIF __shift_left_sat_to_unsigned(__short8, __uchar8 __CST(0, 63));
__ushort16 __OVBIF __shift_left_sat_to_unsigned(__short16, __uchar16 __CST(0, 63));
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __shift_left_sat_to_unsigned(__short32, __uchar32 __CST(0, 63));
#endif
__ushort2 __OVBIF __shift_left_sat_to_unsigned(__short2, __uint);
__ushort4 __OVBIF __shift_left_sat_to_unsigned(__short4, __uint2);
__ushort8 __OVBIF __shift_left_sat_to_unsigned(__short8, __uint4);
__ushort16 __OVBIF __shift_left_sat_to_unsigned(__short16, __uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __shift_left_sat_to_unsigned(__short32, __uint16);
#endif
/*
VSSHLSUW
*/
__uint __OVBIF __shift_left_sat_to_unsigned(int, __uchar __CST(0, 63));
__uint2 __OVBIF __shift_left_sat_to_unsigned(__int2, __uchar2 __CST(0, 63));
__uint3 __OVBIF __shift_left_sat_to_unsigned(__int3, __uchar3 __CST(0, 63));
__uint4 __OVBIF __shift_left_sat_to_unsigned(__int4, __uchar4 __CST(0, 63));
__uint8 __OVBIF __shift_left_sat_to_unsigned(__int8, __uchar8 __CST(0, 63));
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __shift_left_sat_to_unsigned(__int16, __uchar16 __CST(0, 63));
#endif
__uint __OVBIF __shift_left_sat_to_unsigned(int, __uint);
__uint2 __OVBIF __shift_left_sat_to_unsigned(__int2, __uint2);
__uint3 __OVBIF __shift_left_sat_to_unsigned(__int3, __uint3);
__uint4 __OVBIF __shift_left_sat_to_unsigned(__int4, __uint4);
__uint8 __OVBIF __shift_left_sat_to_unsigned(__int8, __uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __shift_left_sat_to_unsigned(__int16, __uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __shift_left_var                                                       */
/*----------------------------------------------------------------------------*/
/*
VSHVLW
*/
int __OVBIF __shift_left_var(int, int);
__int2 __OVBIF __shift_left_var(__int2, __int2);
__int3 __OVBIF __shift_left_var(__int3, __int3);
__int4 __OVBIF __shift_left_var(__int4, __int4);
__int8 __OVBIF __shift_left_var(__int8, __int8);
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __shift_left_var(__int16, __int16);
#endif
/*
VSHVLUW
*/
__uint __OVBIF __shift_left_var(__uint, int);
__uint2 __OVBIF __shift_left_var(__uint2, __int2);
__uint3 __OVBIF __shift_left_var(__uint3, __int3);
__uint4 __OVBIF __shift_left_var(__uint4, __int4);
__uint8 __OVBIF __shift_left_var(__uint8, __int8);
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __shift_left_var(__uint16, __int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __shift_left_var_sat                                                   */
/*----------------------------------------------------------------------------*/
/*
VSSHVLW
*/
int __OVBIF __shift_left_var_sat(int, int);
__int2 __OVBIF __shift_left_var_sat(__int2, __int2);
__int3 __OVBIF __shift_left_var_sat(__int3, __int3);
__int4 __OVBIF __shift_left_var_sat(__int4, __int4);
__int8 __OVBIF __shift_left_var_sat(__int8, __int8);
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __shift_left_var_sat(__int16, __int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __shift_right                                                          */
/*----------------------------------------------------------------------------*/
/*
VSHRB
*/
signed char __OVBIF __shift_right(signed char, signed char __CST(0, 63));
__char2 __OVBIF __shift_right(__char2, __char2 __CST(0, 63));
__char3 __OVBIF __shift_right(__char3, __char3 __CST(0, 63));
__char4 __OVBIF __shift_right(__char4, __char4 __CST(0, 63));
__char8 __OVBIF __shift_right(__char8, __char8 __CST(0, 63));
__char16 __OVBIF __shift_right(__char16, __char16 __CST(0, 63));
__char32 __OVBIF __shift_right(__char32, __char32 __CST(0, 63));
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __shift_right(__char64, __char64 __CST(0, 63));
#endif
__char4 __OVBIF __shift_right(__char4, int);
__char8 __OVBIF __shift_right(__char8, __int2);
__char16 __OVBIF __shift_right(__char16, __int4);
__char32 __OVBIF __shift_right(__char32, __int8);
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __shift_right(__char64, __int16);
#endif
/*
VSHRUB
*/
__uchar __OVBIF __shift_right(__uchar, __uchar __CST(0, 63));
__uchar2 __OVBIF __shift_right(__uchar2, __uchar2 __CST(0, 63));
__uchar3 __OVBIF __shift_right(__uchar3, __uchar3 __CST(0, 63));
__uchar4 __OVBIF __shift_right(__uchar4, __uchar4 __CST(0, 63));
__uchar8 __OVBIF __shift_right(__uchar8, __uchar8 __CST(0, 63));
__uchar16 __OVBIF __shift_right(__uchar16, __uchar16 __CST(0, 63));
__uchar32 __OVBIF __shift_right(__uchar32, __uchar32 __CST(0, 63));
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __shift_right(__uchar64, __uchar64 __CST(0, 63));
#endif
__uchar4 __OVBIF __shift_right(__uchar4, __uint);
__uchar8 __OVBIF __shift_right(__uchar8, __uint2);
__uchar16 __OVBIF __shift_right(__uchar16, __uint4);
__uchar32 __OVBIF __shift_right(__uchar32, __uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __shift_right(__uchar64, __uint16);
#endif
/*
VSHRH
*/
short __OVBIF __shift_right(short, short __CST(0, 63));
__short2 __OVBIF __shift_right(__short2, __short2 __CST(0, 63));
__short3 __OVBIF __shift_right(__short3, __short3 __CST(0, 63));
__short4 __OVBIF __shift_right(__short4, __short4 __CST(0, 63));
__short8 __OVBIF __shift_right(__short8, __short8 __CST(0, 63));
__short16 __OVBIF __shift_right(__short16, __short16 __CST(0, 63));
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __shift_right(__short32, __short32 __CST(0, 63));
#endif
__short2 __OVBIF __shift_right(__short2, int);
__short4 __OVBIF __shift_right(__short4, __int2);
__short8 __OVBIF __shift_right(__short8, __int4);
__short16 __OVBIF __shift_right(__short16, __int8);
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __shift_right(__short32, __int16);
#endif
/*
VSHRUH
*/
__ushort __OVBIF __shift_right(__ushort, __ushort __CST(0, 63));
__ushort2 __OVBIF __shift_right(__ushort2, __ushort2 __CST(0, 63));
__ushort3 __OVBIF __shift_right(__ushort3, __ushort3 __CST(0, 63));
__ushort4 __OVBIF __shift_right(__ushort4, __ushort4 __CST(0, 63));
__ushort8 __OVBIF __shift_right(__ushort8, __ushort8 __CST(0, 63));
__ushort16 __OVBIF __shift_right(__ushort16, __ushort16 __CST(0, 63));
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __shift_right(__ushort32, __ushort32 __CST(0, 63));
#endif
__ushort2 __OVBIF __shift_right(__ushort2, __uint);
__ushort4 __OVBIF __shift_right(__ushort4, __uint2);
__ushort8 __OVBIF __shift_right(__ushort8, __uint4);
__ushort16 __OVBIF __shift_right(__ushort16, __uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __shift_right(__ushort32, __uint16);
#endif
/*
SHRW
*/
int __OVBIF __shift_right(int, __uchar __CST(0, 63));
/*
SHRW, VSHRW
*/
int __OVBIF __shift_right(int, int);
/*
int __OVBIF __shift_right(int, int __CST(0, 63));
*/
__int2 __OVBIF __shift_right(__int2, __int2);
/*
__int2 __OVBIF __shift_right(__int2, __int2 __CST(0, 63));
*/
__int3 __OVBIF __shift_right(__int3, __int3);
/*
__int3 __OVBIF __shift_right(__int3, __int3 __CST(0, 63));
*/
__int4 __OVBIF __shift_right(__int4, __int4);
/*
__int4 __OVBIF __shift_right(__int4, __int4 __CST(0, 63));
*/
__int8 __OVBIF __shift_right(__int8, __int8);
/*
__int8 __OVBIF __shift_right(__int8, __int8 __CST(0, 63));
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __shift_right(__int16, __int16);
/*
__int16 __OVBIF __shift_right(__int16, __int16 __CST(0, 63));
*/
#endif
/*
SHRUW
*/
__uint __OVBIF __shift_right(__uint, __uchar __CST(0, 63));
/*
SHRUW, VSHRUW
*/
__uint __OVBIF __shift_right(__uint, __uint);
/*
__uint __OVBIF __shift_right(__uint, __uint __CST(0, 63));
*/
__uint2 __OVBIF __shift_right(__uint2, __uint2);
/*
__uint2 __OVBIF __shift_right(__uint2, __uint2 __CST(0, 63));
*/
__uint3 __OVBIF __shift_right(__uint3, __uint3);
/*
__uint3 __OVBIF __shift_right(__uint3, __uint3 __CST(0, 63));
*/
__uint4 __OVBIF __shift_right(__uint4, __uint4);
/*
__uint4 __OVBIF __shift_right(__uint4, __uint4 __CST(0, 63));
*/
__uint8 __OVBIF __shift_right(__uint8, __uint8);
/*
__uint8 __OVBIF __shift_right(__uint8, __uint8 __CST(0, 63));
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __shift_right(__uint16, __uint16);
/*
__uint16 __OVBIF __shift_right(__uint16, __uint16 __CST(0, 63));
*/
#endif
/*
SHRD
*/
long __OVBIF __shift_right(long, __uchar __CST(0, 63));
long __OVBIF __shift_right(long, int);
/*
VSHRD
*/
long __OVBIF __shift_right(long, long);
/*
long __OVBIF __shift_right(long, long __CST(0, 63));
*/
__long2 __OVBIF __shift_right(__long2, __long2);
/*
__long2 __OVBIF __shift_right(__long2, __long2 __CST(0, 63));
*/
__long3 __OVBIF __shift_right(__long3, __long3);
/*
__long3 __OVBIF __shift_right(__long3, __long3 __CST(0, 63));
*/
__long4 __OVBIF __shift_right(__long4, __long4);
/*
__long4 __OVBIF __shift_right(__long4, __long4 __CST(0, 63));
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __shift_right(__long8, __long8);
/*
__long8 __OVBIF __shift_right(__long8, __long8 __CST(0, 63));
*/
#endif
/*
SHRUD
*/
__ulong __OVBIF __shift_right(__ulong, __uchar __CST(0, 63));
__ulong __OVBIF __shift_right(__ulong, __uint);
/*
VSHRUD
*/
__ulong __OVBIF __shift_right(__ulong, __ulong);
/*
__ulong __OVBIF __shift_right(__ulong, __ulong __CST(0, 63));
*/
__ulong2 __OVBIF __shift_right(__ulong2, __ulong2);
/*
__ulong2 __OVBIF __shift_right(__ulong2, __ulong2 __CST(0, 63));
*/
__ulong3 __OVBIF __shift_right(__ulong3, __ulong3);
/*
__ulong3 __OVBIF __shift_right(__ulong3, __ulong3 __CST(0, 63));
*/
__ulong4 __OVBIF __shift_right(__ulong4, __ulong4);
/*
__ulong4 __OVBIF __shift_right(__ulong4, __ulong4 __CST(0, 63));
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __shift_right(__ulong8, __ulong8);
/*
__ulong8 __OVBIF __shift_right(__ulong8, __ulong8 __CST(0, 63));
*/
#endif

/*----------------------------------------------------------------------------*/
/* ID: __shift_right_full                                                     */
/*----------------------------------------------------------------------------*/
/*
VSHR
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __shift_right_full(__long8, __uchar __CST(1, 64));
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __OVBIF __shift_right_full(__long4, __uchar __CST(1, 64));
__long4 __OVBIF __shift_right_full(__long4, __ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __shift_right_full(__long8, __ulong8);
#endif
/*
VSHRU
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __shift_right_full(__ulong8, __uchar __CST(1, 64));
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __OVBIF __shift_right_full(__ulong4, __uchar __CST(1, 64));
__ulong4 __OVBIF __shift_right_full(__ulong4, __ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __shift_right_full(__ulong8, __ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __shift_right_merge                                                    */
/*----------------------------------------------------------------------------*/
/*
VSHRM1B
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __shift_right_merge(__char64, signed char);
#endif
/*
VSHRM1B, VSHRM2B
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __OVBIF __shift_right_merge(__char32, signed char);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __shift_right_merge(__char64, __char2);
#endif
/*
VSHRM2B, VSHRM4B
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __OVBIF __shift_right_merge(__char32, __char2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __shift_right_merge(__char64, __char4);
#endif
/*
VSHRM4B, VSHRM8B
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __OVBIF __shift_right_merge(__char32, __char4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __shift_right_merge(__char64, __char8);
#endif
/*
VSHRM16B, VSHRM8B
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __OVBIF __shift_right_merge(__char32, __char8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __shift_right_merge(__char64, __char16);
#endif
/*
VSHRM16B
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __OVBIF __shift_right_merge(__char32, __char16);
#endif
/*
VSHRMB
*/
int __OVBIF __shift_right_merge(int, __char4);
__int2 __OVBIF __shift_right_merge(__int2, __char8);
__int4 __OVBIF __shift_right_merge(__int4, __char16);
__int8 __OVBIF __shift_right_merge(__int8, __char32);
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __shift_right_merge(__int16, __char64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __shift_right_round                                                    */
/*----------------------------------------------------------------------------*/
/*
VSHRRB
*/
signed char __OVBIF __shift_right_round(signed char, __uchar __CST(0, 63));
__char2 __OVBIF __shift_right_round(__char2, __uchar2 __CST(0, 63));
__char3 __OVBIF __shift_right_round(__char3, __uchar3 __CST(0, 63));
__char4 __OVBIF __shift_right_round(__char4, __uchar4 __CST(0, 63));
__char8 __OVBIF __shift_right_round(__char8, __uchar8 __CST(0, 63));
__char16 __OVBIF __shift_right_round(__char16, __uchar16 __CST(0, 63));
__char32 __OVBIF __shift_right_round(__char32, __uchar32 __CST(0, 63));
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __shift_right_round(__char64, __uchar64 __CST(0, 63));
#endif
__char4 __OVBIF __shift_right_round(__char4, __uint);
__char8 __OVBIF __shift_right_round(__char8, __uint2);
__char16 __OVBIF __shift_right_round(__char16, __uint4);
__char32 __OVBIF __shift_right_round(__char32, __uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __shift_right_round(__char64, __uint16);
#endif
/*
VSHRURB
*/
__uchar __OVBIF __shift_right_round(__uchar, __uchar __CST(0, 63));
__uchar2 __OVBIF __shift_right_round(__uchar2, __uchar2 __CST(0, 63));
__uchar3 __OVBIF __shift_right_round(__uchar3, __uchar3 __CST(0, 63));
__uchar4 __OVBIF __shift_right_round(__uchar4, __uchar4 __CST(0, 63));
__uchar8 __OVBIF __shift_right_round(__uchar8, __uchar8 __CST(0, 63));
__uchar16 __OVBIF __shift_right_round(__uchar16, __uchar16 __CST(0, 63));
__uchar32 __OVBIF __shift_right_round(__uchar32, __uchar32 __CST(0, 63));
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __shift_right_round(__uchar64, __uchar64 __CST(0, 63));
#endif
__uchar4 __OVBIF __shift_right_round(__uchar4, __uint);
__uchar8 __OVBIF __shift_right_round(__uchar8, __uint2);
__uchar16 __OVBIF __shift_right_round(__uchar16, __uint4);
__uchar32 __OVBIF __shift_right_round(__uchar32, __uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __shift_right_round(__uchar64, __uint16);
#endif
/*
VSHRRH
*/
short __OVBIF __shift_right_round(short, __uchar __CST(0, 63));
__short2 __OVBIF __shift_right_round(__short2, __uchar2 __CST(0, 63));
__short3 __OVBIF __shift_right_round(__short3, __uchar3 __CST(0, 63));
__short4 __OVBIF __shift_right_round(__short4, __uchar4 __CST(0, 63));
__short8 __OVBIF __shift_right_round(__short8, __uchar8 __CST(0, 63));
__short16 __OVBIF __shift_right_round(__short16, __uchar16 __CST(0, 63));
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __shift_right_round(__short32, __uchar32 __CST(0, 63));
#endif
__short2 __OVBIF __shift_right_round(__short2, __uint);
__short4 __OVBIF __shift_right_round(__short4, __uint2);
__short8 __OVBIF __shift_right_round(__short8, __uint4);
__short16 __OVBIF __shift_right_round(__short16, __uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __shift_right_round(__short32, __uint16);
#endif
/*
VSHRURH
*/
__ushort __OVBIF __shift_right_round(__ushort, __uchar __CST(0, 63));
__ushort2 __OVBIF __shift_right_round(__ushort2, __uchar2 __CST(0, 63));
__ushort3 __OVBIF __shift_right_round(__ushort3, __uchar3 __CST(0, 63));
__ushort4 __OVBIF __shift_right_round(__ushort4, __uchar4 __CST(0, 63));
__ushort8 __OVBIF __shift_right_round(__ushort8, __uchar8 __CST(0, 63));
__ushort16 __OVBIF __shift_right_round(__ushort16, __uchar16 __CST(0, 63));
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __shift_right_round(__ushort32, __uchar32 __CST(0, 63));
#endif
__ushort2 __OVBIF __shift_right_round(__ushort2, __uint);
__ushort4 __OVBIF __shift_right_round(__ushort4, __uint2);
__ushort8 __OVBIF __shift_right_round(__ushort8, __uint4);
__ushort16 __OVBIF __shift_right_round(__ushort16, __uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __shift_right_round(__ushort32, __uint16);
#endif
/*
VSHRRW
*/
int __OVBIF __shift_right_round(int, __uchar __CST(0, 63));
__int2 __OVBIF __shift_right_round(__int2, __uchar2 __CST(0, 63));
__int3 __OVBIF __shift_right_round(__int3, __uchar3 __CST(0, 63));
__int4 __OVBIF __shift_right_round(__int4, __uchar4 __CST(0, 63));
__int8 __OVBIF __shift_right_round(__int8, __uchar8 __CST(0, 63));
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __shift_right_round(__int16, __uchar16 __CST(0, 63));
#endif
int __OVBIF __shift_right_round(int, __uint);
__int2 __OVBIF __shift_right_round(__int2, __uint2);
__int3 __OVBIF __shift_right_round(__int3, __uint3);
__int4 __OVBIF __shift_right_round(__int4, __uint4);
__int8 __OVBIF __shift_right_round(__int8, __uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __shift_right_round(__int16, __uint16);
#endif
/*
VSHRURW
*/
__uint __OVBIF __shift_right_round(__uint, __uchar __CST(0, 63));
__uint2 __OVBIF __shift_right_round(__uint2, __uchar2 __CST(0, 63));
__uint3 __OVBIF __shift_right_round(__uint3, __uchar3 __CST(0, 63));
__uint4 __OVBIF __shift_right_round(__uint4, __uchar4 __CST(0, 63));
__uint8 __OVBIF __shift_right_round(__uint8, __uchar8 __CST(0, 63));
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __shift_right_round(__uint16, __uchar16 __CST(0, 63));
#endif
__uint __OVBIF __shift_right_round(__uint, __uint);
__uint2 __OVBIF __shift_right_round(__uint2, __uint2);
__uint3 __OVBIF __shift_right_round(__uint3, __uint3);
__uint4 __OVBIF __shift_right_round(__uint4, __uint4);
__uint8 __OVBIF __shift_right_round(__uint8, __uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __shift_right_round(__uint16, __uint16);
#endif
/*
VSHRRD
*/
long __OVBIF __shift_right_round(long, __uchar __CST(0, 63));
__long2 __OVBIF __shift_right_round(__long2, __uchar2 __CST(0, 63));
__long3 __OVBIF __shift_right_round(__long3, __uchar3 __CST(0, 63));
__long4 __OVBIF __shift_right_round(__long4, __uchar4 __CST(0, 63));
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __shift_right_round(__long8, __uchar8 __CST(0, 63));
#endif
long __OVBIF __shift_right_round(long, __ulong);
__long2 __OVBIF __shift_right_round(__long2, __ulong2);
__long3 __OVBIF __shift_right_round(__long3, __ulong3);
__long4 __OVBIF __shift_right_round(__long4, __ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __shift_right_round(__long8, __ulong8);
#endif
/*
VSHRURD
*/
__ulong __OVBIF __shift_right_round(__ulong, __uchar __CST(0, 63));
__ulong2 __OVBIF __shift_right_round(__ulong2, __uchar2 __CST(0, 63));
__ulong3 __OVBIF __shift_right_round(__ulong3, __uchar3 __CST(0, 63));
__ulong4 __OVBIF __shift_right_round(__ulong4, __uchar4 __CST(0, 63));
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __shift_right_round(__ulong8, __uchar8 __CST(0, 63));
#endif
__ulong __OVBIF __shift_right_round(__ulong, __ulong);
__ulong2 __OVBIF __shift_right_round(__ulong2, __ulong2);
__ulong3 __OVBIF __shift_right_round(__ulong3, __ulong3);
__ulong4 __OVBIF __shift_right_round(__ulong4, __ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __shift_right_round(__ulong8, __ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __shift_right_var                                                      */
/*----------------------------------------------------------------------------*/
/*
VSHVRW
*/
int __OVBIF __shift_right_var(int, int);
__int2 __OVBIF __shift_right_var(__int2, __int2);
__int3 __OVBIF __shift_right_var(__int3, __int3);
__int4 __OVBIF __shift_right_var(__int4, __int4);
__int8 __OVBIF __shift_right_var(__int8, __int8);
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __shift_right_var(__int16, __int16);
#endif
/*
VSHVRUW
*/
__uint __OVBIF __shift_right_var(__uint, int);
__uint2 __OVBIF __shift_right_var(__uint2, __int2);
__uint3 __OVBIF __shift_right_var(__uint3, __int3);
__uint4 __OVBIF __shift_right_var(__uint4, __int4);
__uint8 __OVBIF __shift_right_var(__uint8, __int8);
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __shift_right_var(__uint16, __int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __shift_right_var_sat                                                  */
/*----------------------------------------------------------------------------*/
/*
VSSHVRW
*/
int __OVBIF __shift_right_var_sat(int, int);
__int2 __OVBIF __shift_right_var_sat(__int2, __int2);
__int3 __OVBIF __shift_right_var_sat(__int3, __int3);
__int4 __OVBIF __shift_right_var_sat(__int4, __int4);
__int8 __OVBIF __shift_right_var_sat(__int8, __int8);
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __shift_right_var_sat(__int16, __int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __short_to_char_sat                                                    */
/*----------------------------------------------------------------------------*/
/*
VSATHB
*/
short __OVBIF __short_to_char_sat(short);
__short2 __OVBIF __short_to_char_sat(__short2);
__short3 __OVBIF __short_to_char_sat(__short3);
__short4 __OVBIF __short_to_char_sat(__short4);
__short8 __OVBIF __short_to_char_sat(__short8);
__short16 __OVBIF __short_to_char_sat(__short16);
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __short_to_char_sat(__short32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __shuffle_3way                                                         */
/*----------------------------------------------------------------------------*/
/*
VSHFL3
*/
long __OVBIF __shuffle_3way(__int2, __int2);
__long2 __OVBIF __shuffle_3way(__int4, __int4);
__long4 __OVBIF __shuffle_3way(__int8, __int8);
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __shuffle_3way(__int16, __int16);
#endif
__ulong __OVBIF __shuffle_3way(__uint2, __uint2);
__ulong2 __OVBIF __shuffle_3way(__uint4, __uint4);
__ulong4 __OVBIF __shuffle_3way(__uint8, __uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __shuffle_3way(__uint16, __uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __shuffle_bit                                                          */
/*----------------------------------------------------------------------------*/
/*
VBITSHFLW
*/
int __OVBIF __shuffle_bit(int);
__int2 __OVBIF __shuffle_bit(__int2);
__int3 __OVBIF __shuffle_bit(__int3);
__int4 __OVBIF __shuffle_bit(__int4);
__int8 __OVBIF __shuffle_bit(__int8);
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __shuffle_bit(__int16);
#endif
__uint __OVBIF __shuffle_bit(__uint);
__uint2 __OVBIF __shuffle_bit(__uint2);
__uint3 __OVBIF __shuffle_bit(__uint3);
__uint4 __OVBIF __shuffle_bit(__uint4);
__uint8 __OVBIF __shuffle_bit(__uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __shuffle_bit(__uint16);
#endif
/*
VBITSHFLD
*/
long __OVBIF __shuffle_bit(long);
__long2 __OVBIF __shuffle_bit(__long2);
__long3 __OVBIF __shuffle_bit(__long3);
__long4 __OVBIF __shuffle_bit(__long4);
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __shuffle_bit(__long8);
#endif
__ulong __OVBIF __shuffle_bit(__ulong);
__ulong2 __OVBIF __shuffle_bit(__ulong2);
__ulong3 __OVBIF __shuffle_bit(__ulong3);
__ulong4 __OVBIF __shuffle_bit(__ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __shuffle_bit(__ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __shuffle_stride2                                                      */
/*----------------------------------------------------------------------------*/
/*
VSHFL2B
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __OVBIF __shuffle_stride2(__char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __shuffle_stride2(__char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __OVBIF __shuffle_stride2(__uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __shuffle_stride2(__uchar64);
#endif
/*
VSHFL2H
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cchar16 __OVBIF __shuffle_stride2(__cchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cchar32 __OVBIF __shuffle_stride2(__cchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __OVBIF __shuffle_stride2(__short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __shuffle_stride2(__short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __OVBIF __shuffle_stride2(__ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __shuffle_stride2(__ushort32);
#endif
/*
VSHFL2W
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cshort8 __OVBIF __shuffle_stride2(__cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cshort16 __OVBIF __shuffle_stride2(__cshort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __OVBIF __shuffle_stride2(__int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __shuffle_stride2(__int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __OVBIF __shuffle_stride2(__uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __shuffle_stride2(__uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__float8 __OVBIF __shuffle_stride2(__float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__float16 __OVBIF __shuffle_stride2(__float16);
#endif
/*
VSHFL2D
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cint4 __OVBIF __shuffle_stride2(__cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cint8 __OVBIF __shuffle_stride2(__cint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cfloat4 __OVBIF __shuffle_stride2(__cfloat4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cfloat8 __OVBIF __shuffle_stride2(__cfloat8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __OVBIF __shuffle_stride2(__long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __shuffle_stride2(__long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __OVBIF __shuffle_stride2(__ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __shuffle_stride2(__ulong8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__double4 __OVBIF __shuffle_stride2(__double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__double8 __OVBIF __shuffle_stride2(__double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __shuffle_stride2_even_even                                            */
/*----------------------------------------------------------------------------*/
/*
VSHFL2DEE
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cint4 __OVBIF __shuffle_stride2_even_even(__cint4, __cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cint8 __OVBIF __shuffle_stride2_even_even(__cint8, __cint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cfloat4 __OVBIF __shuffle_stride2_even_even(__cfloat4, __cfloat4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cfloat8 __OVBIF __shuffle_stride2_even_even(__cfloat8, __cfloat8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __OVBIF __shuffle_stride2_even_even(__long4, __long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __shuffle_stride2_even_even(__long8, __long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __OVBIF __shuffle_stride2_even_even(__ulong4, __ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __shuffle_stride2_even_even(__ulong8, __ulong8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__double4 __OVBIF __shuffle_stride2_even_even(__double4, __double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__double8 __OVBIF __shuffle_stride2_even_even(__double8, __double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __shuffle_stride2_even_odd                                             */
/*----------------------------------------------------------------------------*/
/*
VSHFL2DEO
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cint4 __OVBIF __shuffle_stride2_even_odd(__cint4, __cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cint8 __OVBIF __shuffle_stride2_even_odd(__cint8, __cint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cfloat4 __OVBIF __shuffle_stride2_even_odd(__cfloat4, __cfloat4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cfloat8 __OVBIF __shuffle_stride2_even_odd(__cfloat8, __cfloat8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __OVBIF __shuffle_stride2_even_odd(__long4, __long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __shuffle_stride2_even_odd(__long8, __long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __OVBIF __shuffle_stride2_even_odd(__ulong4, __ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __shuffle_stride2_even_odd(__ulong8, __ulong8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__double4 __OVBIF __shuffle_stride2_even_odd(__double4, __double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__double8 __OVBIF __shuffle_stride2_even_odd(__double8, __double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __shuffle_stride2_high_high                                            */
/*----------------------------------------------------------------------------*/
/*
VSHFL2HHH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cchar16 __OVBIF __shuffle_stride2_high_high(__cchar16, __cchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cchar32 __OVBIF __shuffle_stride2_high_high(__cchar32, __cchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __OVBIF __shuffle_stride2_high_high(__short16, __short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __shuffle_stride2_high_high(__short32, __short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __OVBIF __shuffle_stride2_high_high(__ushort16, __ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __shuffle_stride2_high_high(__ushort32, __ushort32);
#endif
/*
VSHFL2WHH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cshort8 __OVBIF __shuffle_stride2_high_high(__cshort8, __cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cshort16 __OVBIF __shuffle_stride2_high_high(__cshort16, __cshort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __OVBIF __shuffle_stride2_high_high(__int8, __int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __shuffle_stride2_high_high(__int16, __int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __OVBIF __shuffle_stride2_high_high(__uint8, __uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __shuffle_stride2_high_high(__uint16, __uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__float8 __OVBIF __shuffle_stride2_high_high(__float8, __float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__float16 __OVBIF __shuffle_stride2_high_high(__float16, __float16);
#endif
/*
VSHFL2DHH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cint4 __OVBIF __shuffle_stride2_high_high(__cint4, __cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cint8 __OVBIF __shuffle_stride2_high_high(__cint8, __cint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cfloat4 __OVBIF __shuffle_stride2_high_high(__cfloat4, __cfloat4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cfloat8 __OVBIF __shuffle_stride2_high_high(__cfloat8, __cfloat8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __OVBIF __shuffle_stride2_high_high(__long4, __long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __shuffle_stride2_high_high(__long8, __long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __OVBIF __shuffle_stride2_high_high(__ulong4, __ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __shuffle_stride2_high_high(__ulong8, __ulong8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__double4 __OVBIF __shuffle_stride2_high_high(__double4, __double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__double8 __OVBIF __shuffle_stride2_high_high(__double8, __double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __shuffle_stride2_low_high                                             */
/*----------------------------------------------------------------------------*/
/*
VSHFL2DLH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cint4 __OVBIF __shuffle_stride2_low_high(__cint4, __cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cint8 __OVBIF __shuffle_stride2_low_high(__cint8, __cint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cfloat4 __OVBIF __shuffle_stride2_low_high(__cfloat4, __cfloat4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cfloat8 __OVBIF __shuffle_stride2_low_high(__cfloat8, __cfloat8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __OVBIF __shuffle_stride2_low_high(__long4, __long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __shuffle_stride2_low_high(__long8, __long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __OVBIF __shuffle_stride2_low_high(__ulong4, __ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __shuffle_stride2_low_high(__ulong8, __ulong8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__double4 __OVBIF __shuffle_stride2_low_high(__double4, __double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__double8 __OVBIF __shuffle_stride2_low_high(__double8, __double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __shuffle_stride2_low_low                                              */
/*----------------------------------------------------------------------------*/
/*
VSHFL2HLL
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cchar16 __OVBIF __shuffle_stride2_low_low(__cchar16, __cchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cchar32 __OVBIF __shuffle_stride2_low_low(__cchar32, __cchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __OVBIF __shuffle_stride2_low_low(__short16, __short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __shuffle_stride2_low_low(__short32, __short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __OVBIF __shuffle_stride2_low_low(__ushort16, __ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __shuffle_stride2_low_low(__ushort32, __ushort32);
#endif
/*
VSHFL2WLL
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cshort8 __OVBIF __shuffle_stride2_low_low(__cshort8, __cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cshort16 __OVBIF __shuffle_stride2_low_low(__cshort16, __cshort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __OVBIF __shuffle_stride2_low_low(__int8, __int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __shuffle_stride2_low_low(__int16, __int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __OVBIF __shuffle_stride2_low_low(__uint8, __uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __shuffle_stride2_low_low(__uint16, __uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__float8 __OVBIF __shuffle_stride2_low_low(__float8, __float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__float16 __OVBIF __shuffle_stride2_low_low(__float16, __float16);
#endif
/*
VSHFL2DLL
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cint4 __OVBIF __shuffle_stride2_low_low(__cint4, __cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cint8 __OVBIF __shuffle_stride2_low_low(__cint8, __cint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cfloat4 __OVBIF __shuffle_stride2_low_low(__cfloat4, __cfloat4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cfloat8 __OVBIF __shuffle_stride2_low_low(__cfloat8, __cfloat8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __OVBIF __shuffle_stride2_low_low(__long4, __long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __shuffle_stride2_low_low(__long8, __long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __OVBIF __shuffle_stride2_low_low(__ulong4, __ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __shuffle_stride2_low_low(__ulong8, __ulong8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__double4 __OVBIF __shuffle_stride2_low_low(__double4, __double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__double8 __OVBIF __shuffle_stride2_low_low(__double8, __double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __shuffle_stride2_odd_odd                                              */
/*----------------------------------------------------------------------------*/
/*
VSHFL2DOO
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cint4 __OVBIF __shuffle_stride2_odd_odd(__cint4, __cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cint8 __OVBIF __shuffle_stride2_odd_odd(__cint8, __cint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cfloat4 __OVBIF __shuffle_stride2_odd_odd(__cfloat4, __cfloat4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cfloat8 __OVBIF __shuffle_stride2_odd_odd(__cfloat8, __cfloat8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __OVBIF __shuffle_stride2_odd_odd(__long4, __long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __shuffle_stride2_odd_odd(__long8, __long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __OVBIF __shuffle_stride2_odd_odd(__ulong4, __ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __shuffle_stride2_odd_odd(__ulong8, __ulong8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__double4 __OVBIF __shuffle_stride2_odd_odd(__double4, __double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__double8 __OVBIF __shuffle_stride2_odd_odd(__double8, __double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __shuffle_stride4                                                      */
/*----------------------------------------------------------------------------*/
/*
VSHFL4B
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __OVBIF __shuffle_stride4(__char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __shuffle_stride4(__char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __OVBIF __shuffle_stride4(__uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __shuffle_stride4(__uchar64);
#endif
/*
VSHFL4H
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cchar16 __OVBIF __shuffle_stride4(__cchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cchar32 __OVBIF __shuffle_stride4(__cchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __OVBIF __shuffle_stride4(__short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __shuffle_stride4(__short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __OVBIF __shuffle_stride4(__ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __shuffle_stride4(__ushort32);
#endif
/*
VSHFL4W
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cshort8 __OVBIF __shuffle_stride4(__cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cshort16 __OVBIF __shuffle_stride4(__cshort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __OVBIF __shuffle_stride4(__int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __shuffle_stride4(__int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __OVBIF __shuffle_stride4(__uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __shuffle_stride4(__uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__float8 __OVBIF __shuffle_stride4(__float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__float16 __OVBIF __shuffle_stride4(__float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __sort_asc                                                             */
/*----------------------------------------------------------------------------*/
/*
VSORTIH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __OVBIF __sort_asc(__short16);
#endif
/*
VSORTIUH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __OVBIF __sort_asc(__ushort16);
#endif
/*
VSORTIW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __OVBIF __sort_asc(__int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __sort_asc(__int16);
#endif
/*
VSORTIUW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __OVBIF __sort_asc(__uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __sort_asc(__uint16);
#endif
/*
VSORTISP
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__float8 __OVBIF __sort_asc(__float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__float16 __OVBIF __sort_asc(__float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __sort_asc_perm                                                        */
/*----------------------------------------------------------------------------*/
/*
VSORTPIW
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __sort_asc_perm(__int16);
#endif
/*
VSORTPIUW
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __sort_asc_perm(__uint16);
#endif
/*
VSORTPISP
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __sort_asc_perm(__float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __sort_desc                                                            */
/*----------------------------------------------------------------------------*/
/*
VSORTDH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __OVBIF __sort_desc(__short16);
#endif
/*
VSORTDUH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __OVBIF __sort_desc(__ushort16);
#endif
/*
VSORTDW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __OVBIF __sort_desc(__int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __sort_desc(__int16);
#endif
/*
VSORTDUW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __OVBIF __sort_desc(__uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __sort_desc(__uint16);
#endif
/*
VSORTDSP
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__float8 __OVBIF __sort_desc(__float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__float16 __OVBIF __sort_desc(__float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __sort_desc_perm                                                       */
/*----------------------------------------------------------------------------*/
/*
VSORTPDW
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __sort_desc_perm(__int16);
#endif
/*
VSORTPDUW
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __sort_desc_perm(__uint16);
#endif
/*
VSORTPDSP
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __sort_desc_perm(__float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __sub_cond                                                             */
/*----------------------------------------------------------------------------*/
/*
VSUBCW
*/
__uint __OVBIF __sub_cond(__uint, __uint);
__uint2 __OVBIF __sub_cond(__uint2, __uint2);
__uint3 __OVBIF __sub_cond(__uint3, __uint3);
__uint4 __OVBIF __sub_cond(__uint4, __uint4);
__uint8 __OVBIF __sub_cond(__uint8, __uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __sub_cond(__uint16, __uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __sub_reverse                                                          */
/*----------------------------------------------------------------------------*/
/*
VSUBRB
*/
signed char __OVBIF __sub_reverse(signed char, signed char);
/*
signed char __OVBIF __sub_reverse(signed char, signed char __CST(-128, 127));
*/
__char2 __OVBIF __sub_reverse(__char2, __char2);
/*
__char2 __OVBIF __sub_reverse(__char2, __char2 __CST(-128, 127));
*/
__char3 __OVBIF __sub_reverse(__char3, __char3);
/*
__char3 __OVBIF __sub_reverse(__char3, __char3 __CST(-128, 127));
*/
__char4 __OVBIF __sub_reverse(__char4, __char4);
/*
__char4 __OVBIF __sub_reverse(__char4, __char4 __CST(-128, 127));
*/
__char8 __OVBIF __sub_reverse(__char8, __char8);
/*
__char8 __OVBIF __sub_reverse(__char8, __char8 __CST(-128, 127));
*/
__char16 __OVBIF __sub_reverse(__char16, __char16);
/*
__char16 __OVBIF __sub_reverse(__char16, __char16 __CST(-128, 127));
*/
__char32 __OVBIF __sub_reverse(__char32, __char32);
/*
__char32 __OVBIF __sub_reverse(__char32, __char32 __CST(-128, 127));
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __sub_reverse(__char64, __char64);
/*
__char64 __OVBIF __sub_reverse(__char64, __char64 __CST(-128, 127));
*/
#endif
__uchar __OVBIF __sub_reverse(__uchar, __uchar);
/*
__uchar __OVBIF __sub_reverse(__uchar, __uchar __CST(0, 255));
*/
__uchar2 __OVBIF __sub_reverse(__uchar2, __uchar2);
/*
__uchar2 __OVBIF __sub_reverse(__uchar2, __uchar2 __CST(0, 255));
*/
__uchar3 __OVBIF __sub_reverse(__uchar3, __uchar3);
/*
__uchar3 __OVBIF __sub_reverse(__uchar3, __uchar3 __CST(0, 255));
*/
__uchar4 __OVBIF __sub_reverse(__uchar4, __uchar4);
/*
__uchar4 __OVBIF __sub_reverse(__uchar4, __uchar4 __CST(0, 255));
*/
__uchar8 __OVBIF __sub_reverse(__uchar8, __uchar8);
/*
__uchar8 __OVBIF __sub_reverse(__uchar8, __uchar8 __CST(0, 255));
*/
__uchar16 __OVBIF __sub_reverse(__uchar16, __uchar16);
/*
__uchar16 __OVBIF __sub_reverse(__uchar16, __uchar16 __CST(0, 255));
*/
__uchar32 __OVBIF __sub_reverse(__uchar32, __uchar32);
/*
__uchar32 __OVBIF __sub_reverse(__uchar32, __uchar32 __CST(0, 255));
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __sub_reverse(__uchar64, __uchar64);
/*
__uchar64 __OVBIF __sub_reverse(__uchar64, __uchar64 __CST(0, 255));
*/
#endif
__cchar __OVBIF __sub_reverse(__cchar, __cchar);
__cchar2 __OVBIF __sub_reverse(__cchar2, __cchar2);
__cchar4 __OVBIF __sub_reverse(__cchar4, __cchar4);
__cchar8 __OVBIF __sub_reverse(__cchar8, __cchar8);
__cchar16 __OVBIF __sub_reverse(__cchar16, __cchar16);
#if __C7X_VEC_SIZE_BITS__ == 512
__cchar32 __OVBIF __sub_reverse(__cchar32, __cchar32);
#endif
/*
VSUBRH
*/
short __OVBIF __sub_reverse(short, short);
/*
short __OVBIF __sub_reverse(short, short __CST(-32768, 32767));
*/
__short2 __OVBIF __sub_reverse(__short2, __short2);
/*
__short2 __OVBIF __sub_reverse(__short2, __short2 __CST(-32768, 32767));
*/
__short3 __OVBIF __sub_reverse(__short3, __short3);
/*
__short3 __OVBIF __sub_reverse(__short3, __short3 __CST(-32768, 32767));
*/
__short4 __OVBIF __sub_reverse(__short4, __short4);
/*
__short4 __OVBIF __sub_reverse(__short4, __short4 __CST(-32768, 32767));
*/
__short8 __OVBIF __sub_reverse(__short8, __short8);
/*
__short8 __OVBIF __sub_reverse(__short8, __short8 __CST(-32768, 32767));
*/
__short16 __OVBIF __sub_reverse(__short16, __short16);
/*
__short16 __OVBIF __sub_reverse(__short16, __short16 __CST(-32768, 32767));
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __sub_reverse(__short32, __short32);
/*
__short32 __OVBIF __sub_reverse(__short32, __short32 __CST(-32768, 32767));
*/
#endif
__ushort __OVBIF __sub_reverse(__ushort, __ushort);
/*
__ushort __OVBIF __sub_reverse(__ushort, __ushort __CST(0, 65535));
*/
__ushort2 __OVBIF __sub_reverse(__ushort2, __ushort2);
/*
__ushort2 __OVBIF __sub_reverse(__ushort2, __ushort2 __CST(0, 65535));
*/
__ushort3 __OVBIF __sub_reverse(__ushort3, __ushort3);
/*
__ushort3 __OVBIF __sub_reverse(__ushort3, __ushort3 __CST(0, 65535));
*/
__ushort4 __OVBIF __sub_reverse(__ushort4, __ushort4);
/*
__ushort4 __OVBIF __sub_reverse(__ushort4, __ushort4 __CST(0, 65535));
*/
__ushort8 __OVBIF __sub_reverse(__ushort8, __ushort8);
/*
__ushort8 __OVBIF __sub_reverse(__ushort8, __ushort8 __CST(0, 65535));
*/
__ushort16 __OVBIF __sub_reverse(__ushort16, __ushort16);
/*
__ushort16 __OVBIF __sub_reverse(__ushort16, __ushort16 __CST(0, 65535));
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __sub_reverse(__ushort32, __ushort32);
/*
__ushort32 __OVBIF __sub_reverse(__ushort32, __ushort32 __CST(0, 65535));
*/
#endif
__cshort __OVBIF __sub_reverse(__cshort, __cshort);
__cshort2 __OVBIF __sub_reverse(__cshort2, __cshort2);
__cshort4 __OVBIF __sub_reverse(__cshort4, __cshort4);
__cshort8 __OVBIF __sub_reverse(__cshort8, __cshort8);
#if __C7X_VEC_SIZE_BITS__ == 512
__cshort16 __OVBIF __sub_reverse(__cshort16, __cshort16);
#endif
/*
SUBRW, VSUBRW
*/
int __OVBIF __sub_reverse(int, int);
/*
int __OVBIF __sub_reverse(int, int __CST(-2147483648, 2147483647));
*/
__int2 __OVBIF __sub_reverse(__int2, __int2);
/*
__int2 __OVBIF __sub_reverse(__int2, __int2 __CST(-2147483648, 2147483647));
*/
__int3 __OVBIF __sub_reverse(__int3, __int3);
/*
__int3 __OVBIF __sub_reverse(__int3, __int3 __CST(-2147483648, 2147483647));
*/
__int4 __OVBIF __sub_reverse(__int4, __int4);
/*
__int4 __OVBIF __sub_reverse(__int4, __int4 __CST(-2147483648, 2147483647));
*/
__int8 __OVBIF __sub_reverse(__int8, __int8);
/*
__int8 __OVBIF __sub_reverse(__int8, __int8 __CST(-2147483648, 2147483647));
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __sub_reverse(__int16, __int16);
/*
__int16 __OVBIF __sub_reverse(__int16, __int16 __CST(-2147483648, 2147483647));
*/
#endif
__uint __OVBIF __sub_reverse(__uint, __uint);
/*
__uint __OVBIF __sub_reverse(__uint, __uint __CST(0, 4294967295));
*/
__uint2 __OVBIF __sub_reverse(__uint2, __uint2);
/*
__uint2 __OVBIF __sub_reverse(__uint2, __uint2 __CST(0, 4294967295));
*/
__uint3 __OVBIF __sub_reverse(__uint3, __uint3);
/*
__uint3 __OVBIF __sub_reverse(__uint3, __uint3 __CST(0, 4294967295));
*/
__uint4 __OVBIF __sub_reverse(__uint4, __uint4);
/*
__uint4 __OVBIF __sub_reverse(__uint4, __uint4 __CST(0, 4294967295));
*/
__uint8 __OVBIF __sub_reverse(__uint8, __uint8);
/*
__uint8 __OVBIF __sub_reverse(__uint8, __uint8 __CST(0, 4294967295));
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __sub_reverse(__uint16, __uint16);
/*
__uint16 __OVBIF __sub_reverse(__uint16, __uint16 __CST(0, 4294967295));
*/
#endif
/*
VSUBRW
*/
__cint __OVBIF __sub_reverse(__cint, __cint);
__cint2 __OVBIF __sub_reverse(__cint2, __cint2);
__cint4 __OVBIF __sub_reverse(__cint4, __cint4);
#if __C7X_VEC_SIZE_BITS__ == 512
__cint8 __OVBIF __sub_reverse(__cint8, __cint8);
#endif
/*
SUBRD, VSUBRD
*/
long __OVBIF __sub_reverse(long, long);
/*
long __OVBIF __sub_reverse(long, long __CST(-2147483648, 2147483647));
*/
__long2 __OVBIF __sub_reverse(__long2, __long2);
/*
__long2 __OVBIF __sub_reverse(__long2, __long2 __CST(-2147483648, 2147483647));
*/
__long3 __OVBIF __sub_reverse(__long3, __long3);
/*
__long3 __OVBIF __sub_reverse(__long3, __long3 __CST(-2147483648, 2147483647));
*/
__long4 __OVBIF __sub_reverse(__long4, __long4);
/*
__long4 __OVBIF __sub_reverse(__long4, __long4 __CST(-2147483648, 2147483647));
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __sub_reverse(__long8, __long8);
/*
__long8 __OVBIF __sub_reverse(__long8, __long8 __CST(-2147483648, 2147483647));
*/
#endif
__ulong __OVBIF __sub_reverse(__ulong, __ulong);
/*
__ulong __OVBIF __sub_reverse(__ulong, __ulong __CST(0, 2147483647));
*/
__ulong2 __OVBIF __sub_reverse(__ulong2, __ulong2);
/*
__ulong2 __OVBIF __sub_reverse(__ulong2, __ulong2 __CST(0, 2147483647));
*/
__ulong3 __OVBIF __sub_reverse(__ulong3, __ulong3);
/*
__ulong3 __OVBIF __sub_reverse(__ulong3, __ulong3 __CST(0, 2147483647));
*/
__ulong4 __OVBIF __sub_reverse(__ulong4, __ulong4);
/*
__ulong4 __OVBIF __sub_reverse(__ulong4, __ulong4 __CST(0, 2147483647));
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __sub_reverse(__ulong8, __ulong8);
/*
__ulong8 __OVBIF __sub_reverse(__ulong8, __ulong8 __CST(0, 2147483647));
*/
#endif
/*
VSUBRD
*/
__clong __OVBIF __sub_reverse(__clong, __clong);
__clong2 __OVBIF __sub_reverse(__clong2, __clong2);
#if __C7X_VEC_SIZE_BITS__ == 512
__clong4 __OVBIF __sub_reverse(__clong4, __clong4);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __sub_sat                                                              */
/*----------------------------------------------------------------------------*/
/*
VSSUBB
*/
signed char __OVBIF __sub_sat(signed char, signed char);
/*
signed char __OVBIF __sub_sat(signed char, signed char __CST(-128, 127));
*/
__char2 __OVBIF __sub_sat(__char2, __char2);
/*
__char2 __OVBIF __sub_sat(__char2, __char2 __CST(-128, 127));
*/
__char3 __OVBIF __sub_sat(__char3, __char3);
/*
__char3 __OVBIF __sub_sat(__char3, __char3 __CST(-128, 127));
*/
__char4 __OVBIF __sub_sat(__char4, __char4);
/*
__char4 __OVBIF __sub_sat(__char4, __char4 __CST(-128, 127));
*/
__char8 __OVBIF __sub_sat(__char8, __char8);
/*
__char8 __OVBIF __sub_sat(__char8, __char8 __CST(-128, 127));
*/
__char16 __OVBIF __sub_sat(__char16, __char16);
/*
__char16 __OVBIF __sub_sat(__char16, __char16 __CST(-128, 127));
*/
__char32 __OVBIF __sub_sat(__char32, __char32);
/*
__char32 __OVBIF __sub_sat(__char32, __char32 __CST(-128, 127));
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __sub_sat(__char64, __char64);
/*
__char64 __OVBIF __sub_sat(__char64, __char64 __CST(-128, 127));
*/
#endif
__cchar __OVBIF __sub_sat(__cchar, __cchar);
__cchar2 __OVBIF __sub_sat(__cchar2, __cchar2);
__cchar4 __OVBIF __sub_sat(__cchar4, __cchar4);
__cchar8 __OVBIF __sub_sat(__cchar8, __cchar8);
__cchar16 __OVBIF __sub_sat(__cchar16, __cchar16);
#if __C7X_VEC_SIZE_BITS__ == 512
__cchar32 __OVBIF __sub_sat(__cchar32, __cchar32);
#endif
/*
VSSUBH
*/
short __OVBIF __sub_sat(short, short);
/*
short __OVBIF __sub_sat(short, short __CST(-32768, 32767));
*/
__short2 __OVBIF __sub_sat(__short2, __short2);
/*
__short2 __OVBIF __sub_sat(__short2, __short2 __CST(-32768, 32767));
*/
__short3 __OVBIF __sub_sat(__short3, __short3);
/*
__short3 __OVBIF __sub_sat(__short3, __short3 __CST(-32768, 32767));
*/
__short4 __OVBIF __sub_sat(__short4, __short4);
/*
__short4 __OVBIF __sub_sat(__short4, __short4 __CST(-32768, 32767));
*/
__short8 __OVBIF __sub_sat(__short8, __short8);
/*
__short8 __OVBIF __sub_sat(__short8, __short8 __CST(-32768, 32767));
*/
__short16 __OVBIF __sub_sat(__short16, __short16);
/*
__short16 __OVBIF __sub_sat(__short16, __short16 __CST(-32768, 32767));
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __sub_sat(__short32, __short32);
/*
__short32 __OVBIF __sub_sat(__short32, __short32 __CST(-32768, 32767));
*/
#endif
__cshort __OVBIF __sub_sat(__cshort, __cshort);
__cshort2 __OVBIF __sub_sat(__cshort2, __cshort2);
__cshort4 __OVBIF __sub_sat(__cshort4, __cshort4);
__cshort8 __OVBIF __sub_sat(__cshort8, __cshort8);
#if __C7X_VEC_SIZE_BITS__ == 512
__cshort16 __OVBIF __sub_sat(__cshort16, __cshort16);
#endif
/*
VSSUBW
*/
int __OVBIF __sub_sat(int, int);
/*
int __OVBIF __sub_sat(int, int __CST(-2147483648, 2147483647));
*/
__int2 __OVBIF __sub_sat(__int2, __int2);
/*
__int2 __OVBIF __sub_sat(__int2, __int2 __CST(-2147483648, 2147483647));
*/
__int3 __OVBIF __sub_sat(__int3, __int3);
/*
__int3 __OVBIF __sub_sat(__int3, __int3 __CST(-2147483648, 2147483647));
*/
__int4 __OVBIF __sub_sat(__int4, __int4);
/*
__int4 __OVBIF __sub_sat(__int4, __int4 __CST(-2147483648, 2147483647));
*/
__int8 __OVBIF __sub_sat(__int8, __int8);
/*
__int8 __OVBIF __sub_sat(__int8, __int8 __CST(-2147483648, 2147483647));
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __sub_sat(__int16, __int16);
/*
__int16 __OVBIF __sub_sat(__int16, __int16 __CST(-2147483648, 2147483647));
*/
#endif
__cint __OVBIF __sub_sat(__cint, __cint);
__cint2 __OVBIF __sub_sat(__cint2, __cint2);
__cint4 __OVBIF __sub_sat(__cint4, __cint4);
#if __C7X_VEC_SIZE_BITS__ == 512
__cint8 __OVBIF __sub_sat(__cint8, __cint8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __swap                                                                 */
/*----------------------------------------------------------------------------*/
/*
VSWAPB
*/
__char2 __OVBIF __swap(__char2);
__char4 __OVBIF __swap(__char4);
__char8 __OVBIF __swap(__char8);
__char16 __OVBIF __swap(__char16);
__char32 __OVBIF __swap(__char32);
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __swap(__char64);
#endif
__uchar2 __OVBIF __swap(__uchar2);
__uchar4 __OVBIF __swap(__uchar4);
__uchar8 __OVBIF __swap(__uchar8);
__uchar16 __OVBIF __swap(__uchar16);
__uchar32 __OVBIF __swap(__uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __swap(__uchar64);
#endif
/*
VSWAPH
*/
__cchar2 __OVBIF __swap(__cchar2);
__cchar4 __OVBIF __swap(__cchar4);
__cchar8 __OVBIF __swap(__cchar8);
__cchar16 __OVBIF __swap(__cchar16);
#if __C7X_VEC_SIZE_BITS__ == 512
__cchar32 __OVBIF __swap(__cchar32);
#endif
__short2 __OVBIF __swap(__short2);
__short4 __OVBIF __swap(__short4);
__short8 __OVBIF __swap(__short8);
__short16 __OVBIF __swap(__short16);
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __swap(__short32);
#endif
__ushort2 __OVBIF __swap(__ushort2);
__ushort4 __OVBIF __swap(__ushort4);
__ushort8 __OVBIF __swap(__ushort8);
__ushort16 __OVBIF __swap(__ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __swap(__ushort32);
#endif
/*
VSWAPW
*/
__cshort2 __OVBIF __swap(__cshort2);
__cshort4 __OVBIF __swap(__cshort4);
__cshort8 __OVBIF __swap(__cshort8);
#if __C7X_VEC_SIZE_BITS__ == 512
__cshort16 __OVBIF __swap(__cshort16);
#endif
__int2 __OVBIF __swap(__int2);
__int4 __OVBIF __swap(__int4);
__int8 __OVBIF __swap(__int8);
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __swap(__int16);
#endif
__uint2 __OVBIF __swap(__uint2);
__uint4 __OVBIF __swap(__uint4);
__uint8 __OVBIF __swap(__uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __swap(__uint16);
#endif
__float2 __OVBIF __swap(__float2);
__float4 __OVBIF __swap(__float4);
__float8 __OVBIF __swap(__float8);
#if __C7X_VEC_SIZE_BITS__ == 512
__float16 __OVBIF __swap(__float16);
#endif
/*
VSWAPD
*/
__cint2 __OVBIF __swap(__cint2);
__cint4 __OVBIF __swap(__cint4);
#if __C7X_VEC_SIZE_BITS__ == 512
__cint8 __OVBIF __swap(__cint8);
#endif
__cfloat2 __OVBIF __swap(__cfloat2);
__cfloat4 __OVBIF __swap(__cfloat4);
#if __C7X_VEC_SIZE_BITS__ == 512
__cfloat8 __OVBIF __swap(__cfloat8);
#endif
__long2 __OVBIF __swap(__long2);
__long4 __OVBIF __swap(__long4);
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __swap(__long8);
#endif
__ulong2 __OVBIF __swap(__ulong2);
__ulong4 __OVBIF __swap(__ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __swap(__ulong8);
#endif
__double2 __OVBIF __swap(__double2);
__double4 __OVBIF __swap(__double4);
#if __C7X_VEC_SIZE_BITS__ == 512
__double8 __OVBIF __swap(__double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __unpack_high                                                          */
/*----------------------------------------------------------------------------*/
/*
VUNPKHB
*/
__short2 __OVBIF __unpack_high(__char4);
__short4 __OVBIF __unpack_high(__char8);
__short8 __OVBIF __unpack_high(__char16);
__short16 __OVBIF __unpack_high(__char32);
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __unpack_high(__char64);
#endif
/*
VUNPKHUB
*/
__ushort2 __OVBIF __unpack_high(__uchar4);
__ushort4 __OVBIF __unpack_high(__uchar8);
__ushort8 __OVBIF __unpack_high(__uchar16);
__ushort16 __OVBIF __unpack_high(__uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __unpack_high(__uchar64);
#endif
/*
VUNPKHH
*/
__int2 __OVBIF __unpack_high(__short4);
__int4 __OVBIF __unpack_high(__short8);
__int8 __OVBIF __unpack_high(__short16);
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __unpack_high(__short32);
#endif
/*
VUNPKHUH
*/
__uint2 __OVBIF __unpack_high(__ushort4);
__uint4 __OVBIF __unpack_high(__ushort8);
__uint8 __OVBIF __unpack_high(__ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __unpack_high(__ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __unpack_low                                                           */
/*----------------------------------------------------------------------------*/
/*
VUNPKLB
*/
__short2 __OVBIF __unpack_low(__char4);
__short4 __OVBIF __unpack_low(__char8);
__short8 __OVBIF __unpack_low(__char16);
__short16 __OVBIF __unpack_low(__char32);
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __unpack_low(__char64);
#endif
/*
VUNPKLUB
*/
__ushort2 __OVBIF __unpack_low(__uchar4);
__ushort4 __OVBIF __unpack_low(__uchar8);
__ushort8 __OVBIF __unpack_low(__uchar16);
__ushort16 __OVBIF __unpack_low(__uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __unpack_low(__uchar64);
#endif
/*
VUNPKLH
*/
__int2 __OVBIF __unpack_low(__short4);
__int4 __OVBIF __unpack_low(__short8);
__int8 __OVBIF __unpack_low(__short16);
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __unpack_low(__short32);
#endif
/*
VUNPKLUH
*/
__uint2 __OVBIF __unpack_low(__ushort4);
__uint4 __OVBIF __unpack_low(__ushort8);
__uint8 __OVBIF __unpack_low(__ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __unpack_low(__ushort32);
#endif
/*
VUNPKLW
*/
long __OVBIF __unpack_low(__int2);
__long2 __OVBIF __unpack_low(__int4);
__long4 __OVBIF __unpack_low(__int8);
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __unpack_low(__int16);
#endif
/*
VUNPKLUW
*/
__ulong __OVBIF __unpack_low(__uint2);
__ulong2 __OVBIF __unpack_low(__uint4);
__ulong4 __OVBIF __unpack_low(__uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __unpack_low(__uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __xnor                                                                 */
/*----------------------------------------------------------------------------*/
/*
VXNORW, XNORD, XNORW
*/
signed char __OVBIF __xnor(signed char, signed char);
__char2 __OVBIF __xnor(__char2, __char2);
__char3 __OVBIF __xnor(__char3, __char3);
__char4 __OVBIF __xnor(__char4, __char4);
__char8 __OVBIF __xnor(__char8, __char8);
__char16 __OVBIF __xnor(__char16, __char16);
__char32 __OVBIF __xnor(__char32, __char32);
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __xnor(__char64, __char64);
#endif
__uchar __OVBIF __xnor(__uchar, __uchar);
__uchar2 __OVBIF __xnor(__uchar2, __uchar2);
__uchar3 __OVBIF __xnor(__uchar3, __uchar3);
__uchar4 __OVBIF __xnor(__uchar4, __uchar4);
__uchar8 __OVBIF __xnor(__uchar8, __uchar8);
__uchar16 __OVBIF __xnor(__uchar16, __uchar16);
__uchar32 __OVBIF __xnor(__uchar32, __uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __xnor(__uchar64, __uchar64);
#endif
short __OVBIF __xnor(short, short);
__short2 __OVBIF __xnor(__short2, __short2);
__short3 __OVBIF __xnor(__short3, __short3);
__short4 __OVBIF __xnor(__short4, __short4);
__short8 __OVBIF __xnor(__short8, __short8);
__short16 __OVBIF __xnor(__short16, __short16);
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __xnor(__short32, __short32);
#endif
__ushort __OVBIF __xnor(__ushort, __ushort);
__ushort2 __OVBIF __xnor(__ushort2, __ushort2);
__ushort3 __OVBIF __xnor(__ushort3, __ushort3);
__ushort4 __OVBIF __xnor(__ushort4, __ushort4);
__ushort8 __OVBIF __xnor(__ushort8, __ushort8);
__ushort16 __OVBIF __xnor(__ushort16, __ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __xnor(__ushort32, __ushort32);
#endif
int __OVBIF __xnor(int, int);
__int2 __OVBIF __xnor(__int2, __int2);
__int3 __OVBIF __xnor(__int3, __int3);
__int4 __OVBIF __xnor(__int4, __int4);
__int8 __OVBIF __xnor(__int8, __int8);
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __xnor(__int16, __int16);
#endif
__uint __OVBIF __xnor(__uint, __uint);
__uint2 __OVBIF __xnor(__uint2, __uint2);
__uint3 __OVBIF __xnor(__uint3, __uint3);
__uint4 __OVBIF __xnor(__uint4, __uint4);
__uint8 __OVBIF __xnor(__uint8, __uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __xnor(__uint16, __uint16);
#endif
/*
VXNORW, XNORD
*/
long __OVBIF __xnor(long, long);
/*
long __OVBIF __xnor(long, long __CST(-2147483648, 2147483647));
*/
__long2 __OVBIF __xnor(__long2, __long2);
__long3 __OVBIF __xnor(__long3, __long3);
__long4 __OVBIF __xnor(__long4, __long4);
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __xnor(__long8, __long8);
#endif
__ulong __OVBIF __xnor(__ulong, __ulong);
/*
__ulong __OVBIF __xnor(__ulong, __ulong __CST(0, 2147483647));
*/
__ulong2 __OVBIF __xnor(__ulong2, __ulong2);
__ulong3 __OVBIF __xnor(__ulong3, __ulong3);
__ulong4 __OVBIF __xnor(__ulong4, __ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __xnor(__ulong8, __ulong8);
#endif
/*
XNOR
*/
__bool2 __OVBIF __xnor(__bool2, __bool2);
__bool3 __OVBIF __xnor(__bool3, __bool3);
__bool4 __OVBIF __xnor(__bool4, __bool4);
__bool8 __OVBIF __xnor(__bool8, __bool8);
__bool16 __OVBIF __xnor(__bool16, __bool16);
__bool32 __OVBIF __xnor(__bool32, __bool32);
#if __C7X_VEC_SIZE_BITS__ == 512
__bool64 __OVBIF __xnor(__bool64, __bool64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __xor                                                                  */
/*----------------------------------------------------------------------------*/
/*
XOR
*/
__bool2 __OVBIF __xor(__bool2, __bool2);
__bool3 __OVBIF __xor(__bool3, __bool3);
__bool4 __OVBIF __xor(__bool4, __bool4);
__bool8 __OVBIF __xor(__bool8, __bool8);
__bool16 __OVBIF __xor(__bool16, __bool16);
__bool32 __OVBIF __xor(__bool32, __bool32);
#if __C7X_VEC_SIZE_BITS__ == 512
__bool64 __OVBIF __xor(__bool64, __bool64);
#endif

/* AUTOGEN MARKER */

#include <c7x_direct.h>

#ifdef __DEPRECATED_API__
#include <c7x_strm_deprecated.h>
#include <c7x_mma_deprecated.h>
#else
#include <c7x_strm.h>
#include <c7x_mma.h>
#endif

#include <c7x_luthist.h>
#include <c7x_iluthist.h>

#undef __RD
#undef __WR
#undef __IMPURE
#undef __OVERLOADABLE
#undef __BIF
#undef __BIFM
#undef __OVBIF
#undef __OVBIFM
#undef __CST
#undef __CST_RANGE

#undef __C7X_H_INCLUDE__
#endif /* __C7X_H */
