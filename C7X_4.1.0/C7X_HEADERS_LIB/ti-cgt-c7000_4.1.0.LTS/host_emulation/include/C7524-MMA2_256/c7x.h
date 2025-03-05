/*****************************************************************************/
/*  C7X.H                                                                    */
/*                                                                           */
/* Copyright (c) 2017 Texas Instruments Incorporated                         */
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

/*****************************************************************************/
/*  This is the top level required for all C7000 host emulation programs.    */
/*  When writing a program for use with the C7000 host emulation package,    */
/*  the macro __C7X_HOSTEM__ should be defined on the command line. This     */
/*  can be used to differentiate host emulation code from target code if     */
/*  needed. Section 3.3 of the C7000 Host Emulation User's guide contains an */
/*  example program that illustrates how to include this header and the      */
/*  __C7X_HOSTEM__ macro.                                                    */
/*****************************************************************************/

#ifndef C7X_H
#define C7X_H
#define C7X_H_INCLUDE

#include <stdbool.h>

/* If we suspect that this is being compiled in big endian, fail. */
#if defined(__BIG_ENDIAN__) || defined (__big_endian__)
#error "Big endian is not supported in host emulation."
#endif

#define __little_endian__ 1

#define __C7X_HOSTEM__ 1

#define __C7000__ 1
#include <ti_he_impl/targ_defs.h>
#include <ti_he_impl/version.h>

#include <ti_he_impl/vector.h>
#include <ti_he_impl/vector_funcs.h>

/* Include stdlib.h to ensure __max, __min are def'd before undef. */
#include <stdlib.h>
/* __MINGW32__ is defined in both 32 bit and 64 bit MINGW */
#if defined(_MSC_VER) || defined(__MINGW32__)
#undef __max
#undef __min
#endif

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
int64_t __get_GTSC(uint32_t opt);

template<typename CNTRL_REG>
uint64_t __get_indexed(CNTRL_REG &src, uint32_t idx)
{
    return src.get(idx);
}

template<typename CNTRL_REG>
void __set_indexed(CNTRL_REG &dst, uint32_t idx, uint64_t src)
{
    dst.set(idx, src);
}

/*****************************************************************************/
/* INSTRUCTION CACHE FLUSH AND REFRESH                                       */
/*****************************************************************************/
typedef enum
{
    __IINVAL_MMUNONE = 0,
    __IINVAL_MMU0    = 1,
    __IINVAL_MMU1    = 2,
    __IINVAL_MMUALL  = 3
} __IINVAL_TYPE;
void __instr_cache_invalidate(__IINVAL_TYPE);

/*****************************************************************************/
/* BOOLEAN VECTOR CREATION                                                   */
/*                                                                           */
/* Create a boolean vector as a mask of 'k' consecutive booleans set to true */
/*****************************************************************************/
extern bool2  __mask_bool2(uint32_t);
extern bool2  __mask_bool2(uint8_t);

extern bool3  __mask_bool3(uint32_t);
extern bool3  __mask_bool3(uint8_t);

extern bool4  __mask_bool4(uint32_t);
extern bool4  __mask_bool4(uint8_t);

extern bool8  __mask_bool8(uint32_t);
extern bool8  __mask_bool8(uint8_t);

extern bool16 __mask_bool16(uint32_t);
extern bool16 __mask_bool16(uint8_t);

extern bool32 __mask_bool32(uint32_t);
extern bool32 __mask_bool32(uint8_t);

#if __C7X_VEC_SIZE_BITS__ >= 512
extern bool64 __mask_bool64(uint32_t);
extern bool64 __mask_bool64(uint8_t);
#endif


/*****************************************************************************/
/* BOOLEAN VECTOR CONVERSION                                                 */
/*****************************************************************************/
extern __bool2   __reduce_bool2(__bool3);
extern __bool2   __reduce_bool2(__bool4);
extern __bool2   __reduce_bool2(__bool8);
extern __bool2   __reduce_bool2(__bool16);
extern __bool2   __reduce_bool2(__bool32);
#if __C7X_VEC_SIZE_BITS__ >= 512
extern __bool2   __reduce_bool2(__bool64);
#endif

extern __bool3   __extend_bool3(__bool2);
extern __bool3   __reduce_bool3(__bool4);
extern __bool3   __reduce_bool3(__bool8);
extern __bool3   __reduce_bool3(__bool16);
extern __bool3   __reduce_bool3(__bool32);
#if __C7X_VEC_SIZE_BITS__ >= 512
extern __bool3   __reduce_bool3(__bool64);
#endif

extern __bool4   __extend_bool4(__bool2);
extern __bool4   __extend_bool4(__bool3);
extern __bool4   __reduce_bool4(__bool8);
extern __bool4   __reduce_bool4(__bool16);
extern __bool4   __reduce_bool4(__bool32);
#if __C7X_VEC_SIZE_BITS__ >= 512
extern __bool4   __reduce_bool4(__bool64);
#endif

extern __bool8   __extend_bool8(__bool2);
extern __bool8   __extend_bool8(__bool3);
extern __bool8   __extend_bool8(__bool4);
extern __bool8   __reduce_bool8(__bool16);
extern __bool8   __reduce_bool8(__bool32);
#if __C7X_VEC_SIZE_BITS__ >= 512
extern __bool8   __reduce_bool8(__bool64);
#endif

extern __bool16   __extend_bool16(__bool2);
extern __bool16   __extend_bool16(__bool3);
extern __bool16   __extend_bool16(__bool4);
extern __bool16   __extend_bool16(__bool8);
extern __bool16   __reduce_bool16(__bool32);
#if __C7X_VEC_SIZE_BITS__ >= 512
extern __bool16   __reduce_bool16(__bool64);
#endif

extern __bool32   __extend_bool32(__bool2);
extern __bool32   __extend_bool32(__bool3);
extern __bool32   __extend_bool32(__bool4);
extern __bool32   __extend_bool32(__bool8);
extern __bool32   __extend_bool32(__bool16);
#if __C7X_VEC_SIZE_BITS__ >= 512
extern __bool32   __reduce_bool32(__bool64);
#endif

#if __C7X_VEC_SIZE_BITS__ >= 512
extern __bool64   __extend_bool64(__bool2);
extern __bool64   __extend_bool64(__bool3);
extern __bool64   __extend_bool64(__bool4);
extern __bool64   __extend_bool64(__bool8);
extern __bool64   __extend_bool64(__bool16);
extern __bool64   __extend_bool64(__bool32);
#endif

extern __bool2   __create_bool2(uint64_t);
extern __bool3   __create_bool3(uint64_t);
extern __bool4   __create_bool4(uint64_t);
extern __bool8   __create_bool8(uint64_t);
extern __bool16   __create_bool16(uint64_t);
extern __bool32   __create_bool32(uint64_t);
#if __C7X_VEC_SIZE_BITS__ >= 512
extern __bool64   __create_bool64(uint64_t);
#endif

extern uint64_t  __create_scalar(__bool2);
extern uint64_t  __create_scalar(__bool3);
extern uint64_t  __create_scalar(__bool4);
extern uint64_t  __create_scalar(__bool8);
extern uint64_t  __create_scalar(__bool16);
extern uint64_t  __create_scalar(__bool32);
#if __C7X_VEC_SIZE_BITS__ >= 512
extern uint64_t  __create_scalar(__bool64);
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
extern __cfloat   __complex_multiply          (__cfloat,  __cfloat);
extern __cfloat2  __complex_multiply          (__cfloat2, __cfloat2);
extern __cfloat4  __complex_multiply          (__cfloat4, __cfloat4);
#if __C7X_VEC_SIZE_BITS__ >= 512
extern __cfloat8  __complex_multiply          (__cfloat8, __cfloat8);
#endif

/* Complex Conjugate multiply pseudo-instruction: VCMPYSP + VSUBSP */
extern __cfloat   __complex_conjugate_multiply(__cfloat,  __cfloat);
extern __cfloat2  __complex_conjugate_multiply(__cfloat2, __cfloat2);
extern __cfloat4  __complex_conjugate_multiply(__cfloat4, __cfloat4);
#if __C7X_VEC_SIZE_BITS__ >= 512
extern __cfloat8  __complex_conjugate_multiply(__cfloat8, __cfloat8);
#endif

extern cfloat   __conj_cmpy(__cfloat,  __cfloat);
extern cfloat2  __conj_cmpy(__cfloat2, __cfloat2);
extern cfloat4  __conj_cmpy(__cfloat4, __cfloat4);
#if __C7X_VEC_SIZE_BITS__ >= 512
extern cfloat8  __conj_cmpy(__cfloat8, __cfloat8);
#endif

/* Use __complex_conjugate_multiply() instead of __conj_cmpy(). CODEGEN-9989. */
#define __conj_cmpy(a,b) __complex_conjugate_multiply((a),(b))

/* Floating point VMATMPY pseudo-instruction: VMATMPYSP + VADDSP */
/* The VMATMPYSP instruction does not exist on the 750[2|4] architectures */
#if __C7X_VEC_SIZE_BITS__ == 512
/* Floating point VMATMPY pseudo-instruction: VMATMPYSP + VADDSP */
extern __float2  __float_matmpy(__float2, __float4);
extern __float4  __float_matmpy(__float4, __float8);
extern __float8  __float_matmpy(__float8, __float16);
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
extern __char2    __vload_pred(__bool2,  const __char2*);
extern __char4    __vload_pred(__bool4,  const __char4*);
extern __char8    __vload_pred(__bool8,  const __char8*);
extern __char16   __vload_pred(__bool16,  const __char16*);
extern __char32   __vload_pred(__bool32,  const __char32*);
#if __C7X_VEC_SIZE_BITS__ >= 512
extern __char64   __vload_pred(__bool64,  const __char64*);
#endif

extern __uchar2   __vload_pred(__bool2,  const __uchar2*);
extern __uchar4   __vload_pred(__bool4,  const __uchar4*);
extern __uchar8   __vload_pred(__bool8,  const __uchar8*);
extern __uchar16  __vload_pred(__bool16,  const __uchar16*);
extern __uchar32  __vload_pred(__bool32,  const __uchar32*);
#if __C7X_VEC_SIZE_BITS__ >= 512
extern __uchar64  __vload_pred(__bool64,  const __uchar64*);
#endif

/* VLD4H, VLD8H, VLD16H, VLD32H */
extern __short2    __vload_pred(__bool2,  const __short2*);
extern __short4    __vload_pred(__bool4,  const __short4*);
extern __short8    __vload_pred(__bool8,  const __short8*);
extern __short16   __vload_pred(__bool16,  const __short16*);
#if __C7X_VEC_SIZE_BITS__ >= 512
extern __short32   __vload_pred(__bool32,  const __short32*);
#endif

extern __ushort2   __vload_pred(__bool2,  const __ushort2*);
extern __ushort4   __vload_pred(__bool4,  const __ushort4*);
extern __ushort8   __vload_pred(__bool8,  const __ushort8*);
extern __ushort16  __vload_pred(__bool16,  const __ushort16*);
#if __C7X_VEC_SIZE_BITS__ >= 512
extern __ushort32  __vload_pred(__bool32,  const __ushort32*);
#endif

/* VLDHSWAPB */
extern __cchar2    __vload_pred(__bool2,  const __cchar2*);
extern __cchar4    __vload_pred(__bool4,  const __cchar4*);
extern __cchar8    __vload_pred(__bool8,  const __cchar8*);
extern __cchar16   __vload_pred(__bool16,  const __cchar16*);
#if __C7X_VEC_SIZE_BITS__ >= 512
extern __cchar32   __vload_pred(__bool32,  const __cchar32*);
#endif

/* VLD2W, VLD4W, VLD8W, VLD16W */
extern __int2    __vload_pred(__bool2,  const __int2*);
extern __int4    __vload_pred(__bool4,  const __int4*);
extern __int8    __vload_pred(__bool8,  const __int8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
extern __int16   __vload_pred(__bool16,  const __int16*);
#endif

extern __uint2   __vload_pred(__bool2,  const __uint2*);
extern __uint4   __vload_pred(__bool4,  const __uint4*);
extern __uint8   __vload_pred(__bool8,  const __uint8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
extern __uint16  __vload_pred(__bool16,  const __uint16*);
#endif

extern __float2    __vload_pred(__bool2,  const __float2*);
extern __float4    __vload_pred(__bool4,  const __float4*);
extern __float8    __vload_pred(__bool8,  const __float8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
extern __float16   __vload_pred(__bool16,  const __float16*);
#endif

/* VLDWSWAPH */
extern __cshort2    __vload_pred(__bool2,  const __cshort2*);
extern __cshort4    __vload_pred(__bool4,  const __cshort4*);
extern __cshort8    __vload_pred(__bool8,  const __cshort8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
extern __cshort16   __vload_pred(__bool16,  const __cshort16*);
#endif

/* VLD2D, VLD4D, VLD8D */
extern __long2      __vload_pred(__bool2,  const __long2*);
extern __long4      __vload_pred(__bool4,  const __long4*);
#if __C7X_VEC_SIZE_BITS__ >= 512
extern __long8      __vload_pred(__bool8,  const __long8*);
#endif

extern __ulong2     __vload_pred(__bool2,  const __ulong2*);
extern __ulong4     __vload_pred(__bool4,  const __ulong4*);
#if __C7X_VEC_SIZE_BITS__ >= 512
extern __ulong8     __vload_pred(__bool8,  const __ulong8*);
#endif

extern __double2    __vload_pred(__bool2,  const __double2*);
extern __double4    __vload_pred(__bool4,  const __double4*);
#if __C7X_VEC_SIZE_BITS__ >= 512
extern __double8    __vload_pred(__bool8,  const __double8*);
#endif

/* VLDDSWAPW */
extern __cint2    __vload_pred(__bool2,  const __cint2*);
extern __cint4    __vload_pred(__bool4,  const __cint4*);
#if __C7X_VEC_SIZE_BITS__ >= 512
extern __cint8    __vload_pred(__bool8,  const __cint8*);
#endif
extern __cfloat2    __vload_pred(__bool2,  const __cfloat2*);
extern __cfloat4    __vload_pred(__bool4,  const __cfloat4*);
#if __C7X_VEC_SIZE_BITS__ >= 512
extern __cfloat8    __vload_pred(__bool8,  const __cfloat8*);
#endif

/* VLDDUP2B, VLDDUP4B, VLDDUP8B, VLDDUP16B, VLDDUP32B, VLDDUP64B */
#if __C7X_VEC_SIZE_BITS__ == 512
/*
__char64       __vload_dup(const __char32*);
__char64       __vload_dup(const __char16*);
__char64       __vload_dup(const __char8*);
__char64       __vload_dup(const __char4*);
__char64       __vload_dup(const __char2*);
__char64       __vload_dup(const int8_t*);
__uchar64      __vload_dup(const __uchar32*);
__uchar64      __vload_dup(const __uchar16*);
__uchar64      __vload_dup(const __uchar8*);
__uchar64      __vload_dup(const __uchar4*);
__uchar64      __vload_dup(const __uchar2*);
__uchar64      __vload_dup(const __uchar*);
*/

extern __char64       __vload_pred_dup(__bool32,  const __char32*);
extern __char64       __vload_pred_dup(__bool16,  const __char16*);
extern __char64       __vload_pred_dup(__bool8,  const __char8*);
extern __char64       __vload_pred_dup(__bool4,  const __char4*);
extern __char64       __vload_pred_dup(__bool2,  const __char2*);
extern __uchar64      __vload_pred_dup(__bool32,  const __uchar32*);
extern __uchar64      __vload_pred_dup(__bool16,  const __uchar16*);
extern __uchar64      __vload_pred_dup(__bool8,  const __uchar8*);
extern __uchar64      __vload_pred_dup(__bool4,  const __uchar4*);
extern __uchar64      __vload_pred_dup(__bool2,  const __uchar2*);
#elif __C7X_VEC_SIZE_BITS__ == 256
/*
__char32       __vload_dup(const __char16*);
__char32       __vload_dup(const __char8*);
__char32       __vload_dup(const __char4*);
__char32       __vload_dup(const __char2*);
__char32       __vload_dup(const int8_t*);
__uchar32      __vload_dup(const __uchar16*);
__uchar32      __vload_dup(const __uchar8*);
__uchar32      __vload_dup(const __uchar4*);
__uchar32      __vload_dup(const __uchar2*);
__uchar32      __vload_dup(const __uchar*);
*/

extern __char32       __vload_pred_dup(__bool16,  const __char16*);
extern __char32       __vload_pred_dup(__bool8,  const __char8*);
extern __char32       __vload_pred_dup(__bool4,  const __char4*);
extern __char32       __vload_pred_dup(__bool2,  const __char2*);
extern __uchar32      __vload_pred_dup(__bool16,  const __uchar16*);
extern __uchar32      __vload_pred_dup(__bool8,  const __uchar8*);
extern __uchar32      __vload_pred_dup(__bool4,  const __uchar4*);
extern __uchar32      __vload_pred_dup(__bool2,  const __uchar2*);
#endif

/* VLDDUP2H, VLDDUP4H, VLDDUP8H, VLDDUP16H, VLDDUP32H */
#if __C7X_VEC_SIZE_BITS__ == 512
/*
__short32      __vload_dup(const __short16*);
__short32      __vload_dup(const __short8*);
__short32      __vload_dup(const __short4*);
__short32      __vload_dup(const __short2*);
__short32      __vload_dup(const int16_t*);
__ushort32     __vload_dup(const __ushort16*);
__ushort32     __vload_dup(const __ushort8*);
__ushort32     __vload_dup(const __ushort4*);
__ushort32     __vload_dup(const __ushort2*);
__ushort32     __vload_dup(const __ushort*);
*/

extern __short32      __vload_pred_dup(__bool16,  const __short16*);
extern __short32      __vload_pred_dup(__bool8,  const __short8*);
extern __short32      __vload_pred_dup(__bool4,  const __short4*);
extern __short32      __vload_pred_dup(__bool2,  const __short2*);
extern __ushort32     __vload_pred_dup(__bool16,  const __ushort16*);
extern __ushort32     __vload_pred_dup(__bool8,  const __ushort8*);
extern __ushort32     __vload_pred_dup(__bool4,  const __ushort4*);
extern __ushort32     __vload_pred_dup(__bool2,  const __ushort2*);
#elif __C7X_VEC_SIZE_BITS__ == 256
/*
__short16      __vload_dup(const __short8*);
__short16      __vload_dup(const __short4*);
__short16      __vload_dup(const __short2*);
__short16      __vload_dup(const int16_t*);
__ushort16     __vload_dup(const __ushort8*);
__ushort16     __vload_dup(const __ushort4*);
__ushort16     __vload_dup(const __ushort2*);
__ushort16     __vload_dup(const __ushort*);
*/

extern __short16      __vload_pred_dup(__bool8,  const __short8*);
extern __short16      __vload_pred_dup(__bool4,  const __short4*);
extern __short16      __vload_pred_dup(__bool2,  const __short2*);
extern __ushort16     __vload_pred_dup(__bool8,  const __ushort8*);
extern __ushort16     __vload_pred_dup(__bool4,  const __ushort4*);
extern __ushort16     __vload_pred_dup(__bool2,  const __ushort2*);
#endif

/* VLDDUP2W, VLDDUP4W, VLDDUP8W, VLDDUP16W */
#if __C7X_VEC_SIZE_BITS__ == 512
/*
__int16        __vload_dup(const __int8*);
__int16        __vload_dup(const __int4*);
__int16        __vload_dup(const __int2*);
__int16        __vload_dup(const int32_t*);
__uint16       __vload_dup(const __uint8*);
__uint16       __vload_dup(const __uint4*);
__uint16       __vload_dup(const __uint2*);
__uint16       __vload_dup(const __uint*);
__float16      __vload_dup(const __float8*);
__float16      __vload_dup(const __float4*);
__float16      __vload_dup(const __float2*);
__float16      __vload_dup(const float*);
*/

extern __int16        __vload_pred_dup(__bool8,  const __int8*);
extern __int16        __vload_pred_dup(__bool4,  const __int4*);
extern __int16        __vload_pred_dup(__bool2,  const __int2*);
extern __uint16       __vload_pred_dup(__bool8,  const __uint8*);
extern __uint16       __vload_pred_dup(__bool4,  const __uint4*);
extern __uint16       __vload_pred_dup(__bool2,  const __uint2*);
extern __float16      __vload_pred_dup(__bool8,  const __float8*);
extern __float16      __vload_pred_dup(__bool4,  const __float4*);
extern __float16      __vload_pred_dup(__bool2,  const __float2*);
#elif __C7X_VEC_SIZE_BITS__ == 256
/*
__int8        __vload_dup(const __int4*);
__int8        __vload_dup(const __int2*);
__int8        __vload_dup(const int32_t*);
__uint8       __vload_dup(const __uint4*);
__uint8       __vload_dup(const __uint2*);
__uint8       __vload_dup(const __uint*);
__float8      __vload_dup(const __float4*);
__float8      __vload_dup(const __float2*);
__float8      __vload_dup(const float*);
*/

extern __int8        __vload_pred_dup(__bool4,  const __int4*);
extern __int8        __vload_pred_dup(__bool2,  const __int2*);
extern __uint8       __vload_pred_dup(__bool4,  const __uint4*);
extern __uint8       __vload_pred_dup(__bool2,  const __uint2*);
extern __float8      __vload_pred_dup(__bool4,  const __float4*);
extern __float8      __vload_pred_dup(__bool2,  const __float2*);
#endif

/* VLDDUP2D, VLDDUP4D, VLDDUP8D */
#if __C7X_VEC_SIZE_BITS__ == 512
/*
__long8        __vload_dup(const __long4*);
__long8        __vload_dup(const __long2*);
__long8        __vload_dup(const int64_t*);
__ulong8       __vload_dup(const __ulong4*);
__ulong8       __vload_dup(const __ulong2*);
__ulong8       __vload_dup(const __ulong*);
__double8      __vload_dup(const __double4*);
__double8      __vload_dup(const __double2*);
__double8      __vload_dup(const double*);
*/

extern __long8        __vload_pred_dup(__bool4,  const __long4*);
extern __long8        __vload_pred_dup(__bool2,  const __long2*);
extern __ulong8       __vload_pred_dup(__bool4,  const __ulong4*);
extern __ulong8       __vload_pred_dup(__bool2,  const __ulong2*);
extern __double8      __vload_pred_dup(__bool4,  const __double4*);
extern __double8      __vload_pred_dup(__bool2,  const __double2*);
#elif __C7X_VEC_SIZE_BITS__ == 256
/*
__long4        __vload_dup(const __long2*);
__long4        __vload_dup(const int64_t*);
__ulong4       __vload_dup(const __ulong2*);
__ulong4       __vload_dup(const __ulong*);
__double4      __vload_dup(const __double2*);
__double4      __vload_dup(const double*);
*/

extern __long4        __vload_pred_dup(__bool2,  const __long2*);
extern __ulong4       __vload_pred_dup(__bool2,  const __ulong2*);
extern __double4      __vload_pred_dup(__bool2,  const __double2*);
#endif

/* VLDDUP4G8H, VLDDUP8G4H */
#if __C7X_VEC_SIZE_BITS__ >= 512
/*
__short32      __vload_dup_vec(const __short8*);
__ushort32     __vload_dup_vec(const __ushort8*);
__short32      __vload_dup_vec(const __short4*);
__ushort32     __vload_dup_vec(const __ushort4*);
*/

extern __short32      __vload_pred_dup_vec(__bool8,  const __short8*);
extern __ushort32     __vload_pred_dup_vec(__bool8,  const __ushort8*);
extern __short32      __vload_pred_dup_vec(__bool4,  const __short4*);
extern __ushort32     __vload_pred_dup_vec(__bool4,  const __ushort4*);
#endif

/* VLDBUNPKH, VLDBUNPKHU */
/*
int16_t      __vload_unpack_short(const int8_t*);
__short2     __vload_unpack_short(const __char2*);
__short4     __vload_unpack_short(const __char4*);
__short8     __vload_unpack_short(const __char8*);
__short16    __vload_unpack_short(const __char16*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__short32    __vload_unpack_short(const __char32*);
#endif
uint16_t     __vload_unpack_short(const __uchar*);
__ushort2    __vload_unpack_short(const __uchar2*);
__ushort4    __vload_unpack_short(const __uchar4*);
__ushort8    __vload_unpack_short(const __uchar8*);
__ushort16   __vload_unpack_short(const __uchar16*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__ushort32   __vload_unpack_short(const __uchar32*);
#endif
*/

extern __short2     __vload_pred_unpack_short(__bool2,  const __char2*);
extern __short4     __vload_pred_unpack_short(__bool4,  const __char4*);
extern __short8     __vload_pred_unpack_short(__bool8,  const __char8*);
extern __short16    __vload_pred_unpack_short(__bool16,  const __char16*);
#if __C7X_VEC_SIZE_BITS__ >= 512
extern __short32    __vload_pred_unpack_short(__bool32,  const __char32*);
#endif

extern __ushort2    __vload_pred_unpack_short(__bool2,  const __uchar2*);
extern __ushort4    __vload_pred_unpack_short(__bool4,  const __uchar4*);
extern __ushort8    __vload_pred_unpack_short(__bool8,  const __uchar8*);
extern __ushort16   __vload_pred_unpack_short(__bool16,  const __uchar16*);
#if __C7X_VEC_SIZE_BITS__ >= 512
extern __ushort32   __vload_pred_unpack_short(__bool32,  const __uchar32*);
#endif

/* VLDBUNPKW, VLDBUNPKWU */
/*
int32_t      __vload_unpack_int(const int8_t*);
__int2       __vload_unpack_int(const __char2*);
__int4       __vload_unpack_int(const __char4*);
__int8       __vload_unpack_int(const __char8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__int16      __vload_unpack_int(const __char16*);
#endif

uint32_t     __vload_unpack_int(const __uchar*);
__uint2      __vload_unpack_int(const __uchar2*);
__uint4      __vload_unpack_int(const __uchar4*);
__uint8      __vload_unpack_int(const __uchar8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__uint16     __vload_unpack_int(const __uchar16*);
#endif
*/

extern __int2       __vload_pred_unpack_int(__bool2,  const __char2*);
extern __int4       __vload_pred_unpack_int(__bool4,  const __char4*);
extern __int8       __vload_pred_unpack_int(__bool8,  const __char8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
extern __int16      __vload_pred_unpack_int(__bool16,  const __char16*);
#endif

extern __uint2      __vload_pred_unpack_int(__bool2,  const __uchar2*);
extern __uint4      __vload_pred_unpack_int(__bool4,  const __uchar4*);
extern __uint8      __vload_pred_unpack_int(__bool8,  const __uchar8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
extern __uint16     __vload_pred_unpack_int(__bool16,  const __uchar16*);
#endif

/* VLDHUNPKW, VLDHUNPKWU */
/*
int32_t      __vload_unpack_int(const int16_t*);
__int2       __vload_unpack_int(const __short2*);
__int4       __vload_unpack_int(const __short4*);
__int8       __vload_unpack_int(const __short8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__int16      __vload_unpack_int(const __short16*);
#endif

uint32_t     __vload_unpack_int(const __ushort*);
__uint2      __vload_unpack_int(const __ushort2*);
__uint4      __vload_unpack_int(const __ushort4*);
__uint8      __vload_unpack_int(const __ushort8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__uint16     __vload_unpack_int(const __ushort16*);
#endif
*/

extern __int2       __vload_pred_unpack_int(__bool2,  const __short2*);
extern __int4       __vload_pred_unpack_int(__bool4,  const __short4*);
extern __int8       __vload_pred_unpack_int(__bool8,  const __short8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
extern __int16      __vload_pred_unpack_int(__bool16,  const __short16*);
#endif

extern __uint2      __vload_pred_unpack_int(__bool2,  const __ushort2*);
extern __uint4      __vload_pred_unpack_int(__bool4,  const __ushort4*);
extern __uint8      __vload_pred_unpack_int(__bool8,  const __ushort8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
extern __uint16     __vload_pred_unpack_int(__bool16,  const __ushort16*);
#endif

/* VLDBUNPKD, VLDBUNPKDU */
/*
int64_t      __vload_unpack_long(const int8_t*);
__long2      __vload_unpack_long(const __char2*);
__long4      __vload_unpack_long(const __char4*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__long8      __vload_unpack_long(const __char8*);
#endif

uint64_t     __vload_unpack_long(const __uchar*);
__ulong2     __vload_unpack_long(const __uchar2*);
__ulong4     __vload_unpack_long(const __uchar4*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__ulong8     __vload_unpack_long(const __uchar8*);
#endif
*/

extern __long2      __vload_pred_unpack_long(__bool2,  const __char2*);
extern __long4      __vload_pred_unpack_long(__bool4,  const __char4*);
#if __C7X_VEC_SIZE_BITS__ >= 512
extern __long8      __vload_pred_unpack_long(__bool8,  const __char8*);
#endif

extern __ulong2     __vload_pred_unpack_long(__bool2,  const __uchar2*);
extern __ulong4     __vload_pred_unpack_long(__bool4,  const __uchar4*);
#if __C7X_VEC_SIZE_BITS__ >= 512
extern __ulong8     __vload_pred_unpack_long(__bool8,  const __uchar8*);
#endif

/* VLDHUNPKD, VLDHUNPKDU */
/*
int64_t      __vload_unpack_long(const int16_t*);
__long2      __vload_unpack_long(const __short2*);
__long4      __vload_unpack_long(const __short4*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__long8      __vload_unpack_long(const __short8*);
#endif

uint64_t     __vload_unpack_long(const __ushort*);
__ulong2     __vload_unpack_long(const __ushort2*);
__ulong4     __vload_unpack_long(const __ushort4*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__ulong8     __vload_unpack_long(const __ushort8*);
#endif
*/

extern __long2      __vload_pred_unpack_long(__bool2,  const __short2*);
extern __long4      __vload_pred_unpack_long(__bool4,  const __short4*);
#if __C7X_VEC_SIZE_BITS__ >= 512
extern __long8      __vload_pred_unpack_long(__bool8,  const __short8*);
#endif

extern __ulong2     __vload_pred_unpack_long(__bool2,  const __ushort2*);
extern __ulong4     __vload_pred_unpack_long(__bool4,  const __ushort4*);
#if __C7X_VEC_SIZE_BITS__ >= 512
extern __ulong8     __vload_pred_unpack_long(__bool8,  const __ushort8*);
#endif

/* VLDWUNPKD, VLDWUNPKDU */
/*
int64_t      __vload_unpack_long(const int32_t*);
__long2      __vload_unpack_long(const __int2*);
__long4      __vload_unpack_long(const __int4*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__long8      __vload_unpack_long(const __int8*);
#endif

uint64_t     __vload_unpack_long(const __uint*);
__ulong2     __vload_unpack_long(const __uint2*);
__ulong4     __vload_unpack_long(const __uint4*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__ulong8     __vload_unpack_long(const __uint8*);
#endif
*/

extern __long2      __vload_pred_unpack_long(__bool2,  const __int2*);
extern __long4      __vload_pred_unpack_long(__bool4,  const __int4*);
#if __C7X_VEC_SIZE_BITS__ >= 512
extern __long8      __vload_pred_unpack_long(__bool8,  const __int8*);
#endif

extern __ulong2     __vload_pred_unpack_long(__bool2,  const __uint2*);
extern __ulong4     __vload_pred_unpack_long(__bool4,  const __uint4*);
#if __C7X_VEC_SIZE_BITS__ >= 512
extern __ulong8     __vload_pred_unpack_long(__bool8,  const __uint8*);
#endif

/* VLDEBUNPKW, VLDEHUNPKW */
/*
int32_t      __vload_deinterleave_int(const __char2*);
__int2       __vload_deinterleave_int(const __char4*);
__int4       __vload_deinterleave_int(const __char8*);
__int8       __vload_deinterleave_int(const __char16*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__int16      __vload_deinterleave_int(const __char32*);
#endif

int32_t      __vload_deinterleave_int(const __short2*);
__int2       __vload_deinterleave_int(const __short4*);
__int4       __vload_deinterleave_int(const __short8*);
__int8       __vload_deinterleave_int(const __short16*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__int16      __vload_deinterleave_int(const __short32*);
#endif
*/

extern int32_t      __vload_pred_deinterleave_int(__bool2,  const __char2*);
extern __int2       __vload_pred_deinterleave_int(__bool4,  const __char4*);
extern __int4       __vload_pred_deinterleave_int(__bool8,  const __char8*);
extern __int8       __vload_pred_deinterleave_int(__bool16,  const __char16*);
#if __C7X_VEC_SIZE_BITS__ >= 512
extern __int16      __vload_pred_deinterleave_int(__bool32,  const __char32*);
#endif

extern int32_t      __vload_pred_deinterleave_int(__bool2,  const __short2*);
extern __int2       __vload_pred_deinterleave_int(__bool4,  const __short4*);
extern __int4       __vload_pred_deinterleave_int(__bool8,  const __short8*);
extern __int8       __vload_pred_deinterleave_int(__bool16,  const __short16*);
#if __C7X_VEC_SIZE_BITS__ >= 512
extern __int16      __vload_pred_deinterleave_int(__bool32,  const __short32*);
#endif

/* VLDEBUNPKWU, VLDEHUNPKWU */
/*
uint32_t      __vload_deinterleave_int(const __uchar2*);
__uint2       __vload_deinterleave_int(const __uchar4*);
__uint4       __vload_deinterleave_int(const __uchar8*);
__uint8       __vload_deinterleave_int(const __uchar16*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__uint16      __vload_deinterleave_int(const __uchar32*);
#endif

uint32_t      __vload_deinterleave_int(const __ushort2*);
__uint2       __vload_deinterleave_int(const __ushort4*);
__uint4       __vload_deinterleave_int(const __ushort8*);
__uint8       __vload_deinterleave_int(const __ushort16*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__uint16      __vload_deinterleave_int(const __ushort32*);
#endif
*/

extern uint32_t      __vload_pred_deinterleave_int(__bool2,  const __uchar2*);
extern __uint2       __vload_pred_deinterleave_int(__bool4,  const __uchar4*);
extern __uint4       __vload_pred_deinterleave_int(__bool8,  const __uchar8*);
extern __uint8       __vload_pred_deinterleave_int(__bool16,  const __uchar16*);
#if __C7X_VEC_SIZE_BITS__ >= 512
extern __uint16      __vload_pred_deinterleave_int(__bool32,  const __uchar32*);
#endif

extern uint32_t      __vload_pred_deinterleave_int(__bool2,  const __ushort2*);
extern __uint2       __vload_pred_deinterleave_int(__bool4,  const __ushort4*);
extern __uint4       __vload_pred_deinterleave_int(__bool8,  const __ushort8*);
extern __uint8       __vload_pred_deinterleave_int(__bool16,  const __ushort16*);
#if __C7X_VEC_SIZE_BITS__ >= 512
extern __uint16      __vload_pred_deinterleave_int(__bool32,  const __ushort32*);
#endif

/* VLDEBUNPKD, VLDEHUNPKD */
/*
int64_t       __vload_deinterleave_long(const __char2*);
__long2       __vload_deinterleave_long(const __char4*);
__long4       __vload_deinterleave_long(const __char8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__long8       __vload_deinterleave_long(const __char16*);
#endif

int64_t       __vload_deinterleave_long(const __short2*);
__long2       __vload_deinterleave_long(const __short4*);
__long4       __vload_deinterleave_long(const __short8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__long8       __vload_deinterleave_long(const __short16*);
#endif
*/

extern int64_t       __vload_pred_deinterleave_long(__bool2,  const __char2*);
extern __long2       __vload_pred_deinterleave_long(__bool4,  const __char4*);
extern __long4       __vload_pred_deinterleave_long(__bool8,  const __char8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
extern __long8       __vload_pred_deinterleave_long(__bool16,  const __char16*);
#endif

extern int64_t       __vload_pred_deinterleave_long(__bool2,  const __short2*);
extern __long2       __vload_pred_deinterleave_long(__bool4,  const __short4*);
extern __long4       __vload_pred_deinterleave_long(__bool8,  const __short8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
extern __long8       __vload_pred_deinterleave_long(__bool16,  const __short16*);
#endif

/* VLDEBUNPKDU, VLDEHUNPKDU */
/*
uint64_t       __vload_deinterleave_long(const __uchar2*);
__ulong2       __vload_deinterleave_long(const __uchar4*);
__ulong4       __vload_deinterleave_long(const __uchar8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__ulong8       __vload_deinterleave_long(const __uchar16*);
#endif

uint64_t       __vload_deinterleave_long(const __ushort2*);
__ulong2       __vload_deinterleave_long(const __ushort4*);
__ulong4       __vload_deinterleave_long(const __ushort8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
__ulong8       __vload_deinterleave_long(const __ushort16*);
#endif
*/

extern uint64_t       __vload_pred_deinterleave_long(__bool2,  const __uchar2*);
extern __ulong2       __vload_pred_deinterleave_long(__bool4,  const __uchar4*);
extern __ulong4       __vload_pred_deinterleave_long(__bool8,  const __uchar8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
extern __ulong8       __vload_pred_deinterleave_long(__bool16,  const __uchar16*);
#endif

extern uint64_t       __vload_pred_deinterleave_long(__bool2,  const __ushort2*);
extern __ulong2       __vload_pred_deinterleave_long(__bool4,  const __ushort4*);
extern __ulong4       __vload_pred_deinterleave_long(__bool8,  const __ushort8*);
#if __C7X_VEC_SIZE_BITS__ >= 512
extern __ulong8       __vload_pred_deinterleave_long(__bool16,  const __ushort16*);
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
/*
#if __C7X_VEC_SIZE_BITS__ == 512
void  __vstore_interleave(__char64*,   __char64,   __char64);
void  __vstore_interleave(__short32*,  __short32,  __short32);
void  __vstore_interleave(__int16*,    __int16,    __int16);
void  __vstore_interleave(__long8*,    __long8,    __long8);
void  __vstore_interleave(__uchar64*,  __uchar64,  __uchar64);
void  __vstore_interleave(__ushort32*, __ushort32, __ushort32);
void  __vstore_interleave(__uint16*,   __uint16,   __uint16);
void  __vstore_interleave(__ulong8*,   __ulong8,   __ulong8);
#elif __C7X_VEC_SIZE_BITS__ == 256
void  __vstore_interleave(__char32*,   __char32,   __char32);
void  __vstore_interleave(__short16*,  __short16,  __short16);
void  __vstore_interleave(__int8*,    __int8,    __int8);
void  __vstore_interleave(__long4*,    __long4,    __long4);
void  __vstore_interleave(__uchar32*,  __uchar32,  __uchar32);
void  __vstore_interleave(__ushort16*, __ushort16, __ushort16);
void  __vstore_interleave(__uint8*,   __uint8,   __uint8);
void  __vstore_interleave(__ulong4*,   __ulong4,   __ulong4);
#endif
*/

#ifndef __C7100__
/* VSTINTHB, VSTINTHH, VSTINTHW, VSTINTHD - STORES EVERY ODD ELEMENT */
/*
#if __C7X_VEC_SIZE_BITS__ == 512
void  __vstore_interleave_odd(__char64*,   __char64,   __char64);
void  __vstore_interleave_odd(__short32*,  __short32,  __short32);
void  __vstore_interleave_odd(__int16*,    __int16,    __int16);
void  __vstore_interleave_odd(__long8*,    __long8,    __long8);
void  __vstore_interleave_odd(__uchar64*,  __uchar64,  __uchar64);
void  __vstore_interleave_odd(__ushort32*, __ushort32, __ushort32);
void  __vstore_interleave_odd(__uint16*,   __uint16,   __uint16);
void  __vstore_interleave_odd(__ulong8*,   __ulong8,   __ulong8);
#elif __C7X_VEC_SIZE_BITS__ == 256
void  __vstore_interleave_odd(__char32*,   __char32,   __char32);
void  __vstore_interleave_odd(__short16*,  __short16,  __short16);
void  __vstore_interleave_odd(__int8*,    __int8,    __int8);
void  __vstore_interleave_odd(__long4*,    __long4,    __long4);
void  __vstore_interleave_odd(__uchar32*,  __uchar32,  __uchar32);
void  __vstore_interleave_odd(__ushort16*, __ushort16, __ushort16);
void  __vstore_interleave_odd(__uint8*,   __uint8,   __uint8);
void  __vstore_interleave_odd(__ulong4*,   __ulong4,   __ulong4);
#endif
*/
#endif /* ! __C7100__ */

/* VSTINTLB4 - STORES EVERY FOURTH ELEMENT */
/*
#if __C7X_VEC_SIZE_BITS__ == 512
void  __vstore_interleave4(__char32*,   __char64,   __char64);
void  __vstore_interleave4(__uchar32*,  __uchar64,  __uchar64);
#elif __C7X_VEC_SIZE_BITS__ == 256
void  __vstore_interleave4(__char16*,   __char32,   __char32);
void  __vstore_interleave4(__uchar16*,  __uchar32,  __uchar32);
#endif
*/

#ifndef __C7100__
/* VSTLLINTB, VSTLLINTH, VSTLLINTW, VSTLLINTD - STORES LOW VECTOR HALVES */
/*
#if __C7X_VEC_SIZE_BITS__ == 512
void  __vstore_interleave_low_low(__char64*,   __char64,   __char64);
void  __vstore_interleave_low_low(__short32*,  __short32,  __short32);
void  __vstore_interleave_low_low(__int16*,    __int16,    __int16);
void  __vstore_interleave_low_low(__long8*,    __long8,    __long8);
void  __vstore_interleave_low_low(__uchar64*,  __uchar64,  __uchar64);
void  __vstore_interleave_low_low(__ushort32*, __ushort32, __ushort32);
void  __vstore_interleave_low_low(__uint16*,   __uint16,   __uint16);
void  __vstore_interleave_low_low(__ulong8*,   __ulong8,   __ulong8);
#elif __C7X_VEC_SIZE_BITS__ == 256
void  __vstore_interleave_low_low(__char32*,   __char32,   __char32);
void  __vstore_interleave_low_low(__short16*,  __short16,  __short16);
void  __vstore_interleave_low_low(__int8*,    __int8,    __int8);
void  __vstore_interleave_low_low(__long4*,    __long4,    __long4);
void  __vstore_interleave_low_low(__uchar32*,  __uchar32,  __uchar32);
void  __vstore_interleave_low_low(__ushort16*, __ushort16, __ushort16);
void  __vstore_interleave_low_low(__uint8*,   __uint8,   __uint8);
void  __vstore_interleave_low_low(__ulong4*,   __ulong4,   __ulong4);
#endif
*/

/* Half-vector form of VSTLLINT[BHWD]. */  
/*
#if __C7X_VEC_SIZE_BITS__ == 512
void  __vstore_interleave_low_low(__char64*,   __char32,   __char32);
void  __vstore_interleave_low_low(__short32*,  __short16,  __short16);
void  __vstore_interleave_low_low(__int16*,    __int8,    __int8);
void  __vstore_interleave_low_low(__long8*,    __long4,    __long4);
void  __vstore_interleave_low_low(__uchar64*,  __uchar32,  __uchar32);
void  __vstore_interleave_low_low(__ushort32*, __ushort16, __ushort16);
void  __vstore_interleave_low_low(__uint16*,   __uint8,   __uint8);
void  __vstore_interleave_low_low(__ulong8*,   __ulong4,   __ulong4);
#elif __C7X_VEC_SIZE_BITS__ == 256
void  __vstore_interleave_low_low(__char32*,   __char16,   __char16);
void  __vstore_interleave_low_low(__short16*,  __short8,  __short8);
void  __vstore_interleave_low_low(__int8*,    __int4,    __int4);
void  __vstore_interleave_low_low(__long4*,    __long2,    __long2);
void  __vstore_interleave_low_low(__uchar32*,  __uchar16,  __uchar16);
void  __vstore_interleave_low_low(__ushort16*, __ushort8, __ushort8);
void  __vstore_interleave_low_low(__uint8*,   __uint4,   __uint4);
void  __vstore_interleave_low_low(__ulong4*,   __ulong2,   __ulong2);
#endif
*/

/* VSTHHINTB, VSTHHINTH, VSTHHINTW, VSTHHINTD - STORES HIGH VECTOR HALVES */
/*
#if __C7X_VEC_SIZE_BITS__ == 512
void  __vstore_interleave_high_high(__char64*,   __char64,   __char64);
void  __vstore_interleave_high_high(__short32*,  __short32,  __short32);
void  __vstore_interleave_high_high(__int16*,    __int16,    __int16);
void  __vstore_interleave_high_high(__long8*,    __long8,    __long8);
void  __vstore_interleave_high_high(__uchar64*,  __uchar64,  __uchar64);
void  __vstore_interleave_high_high(__ushort32*, __ushort32, __ushort32);
void  __vstore_interleave_high_high(__uint16*,   __uint16,   __uint16);
void  __vstore_interleave_high_high(__ulong8*,   __ulong8,   __ulong8);
#elif __C7X_VEC_SIZE_BITS__ == 256
void  __vstore_interleave_high_high(__char32*,   __char32,   __char32);
void  __vstore_interleave_high_high(__short16*,  __short16,  __short16);
void  __vstore_interleave_high_high(__int8*,    __int8,    __int8);
void  __vstore_interleave_high_high(__long4*,    __long4,    __long4);
void  __vstore_interleave_high_high(__uchar32*,  __uchar32,  __uchar32);
void  __vstore_interleave_high_high(__ushort16*, __ushort16, __ushort16);
void  __vstore_interleave_high_high(__uint8*,   __uint8,   __uint8);
void  __vstore_interleave_high_high(__ulong4*,   __ulong4,   __ulong4);
#endif
*/
#endif /* ! __C7100__ */

/* VSTPINTLB, VSTPINTLH, VSTPINTLW, VSTPINTLD - STORES EVERY EVEN ELEMENT */
#if __C7X_VEC_SIZE_BITS__ == 512
extern void  __vstore_pred_interleave(__bool64,  __char64*,  __char64,  __char64);
extern void  __vstore_pred_interleave(__bool32,  __short32*, __short32, __short32);
extern void  __vstore_pred_interleave(__bool16,  __int16*,   __int16,   __int16);
extern void  __vstore_pred_interleave(__bool8,  __long8*,   __long8,   __long8);
extern void  __vstore_pred_interleave(__bool64,  __uchar64*, __uchar64, __uchar64);
extern void  __vstore_pred_interleave(__bool32,  __ushort32*,__ushort32,__ushort32);
extern void  __vstore_pred_interleave(__bool16,  __uint16*,  __uint16,  __uint16);
extern void  __vstore_pred_interleave(__bool8,  __ulong8*,  __ulong8,  __ulong8);
#elif __C7X_VEC_SIZE_BITS__ == 256
extern void  __vstore_pred_interleave(__bool32,  __char32*,  __char32,  __char32);
extern void  __vstore_pred_interleave(__bool16,  __short16*, __short16, __short16);
extern void  __vstore_pred_interleave(__bool8,  __int8*,   __int8,   __int8);
extern void  __vstore_pred_interleave(__bool4,  __long4*,   __long4,   __long4);
extern void  __vstore_pred_interleave(__bool32,  __uchar32*, __uchar32, __uchar32);
extern void  __vstore_pred_interleave(__bool16,  __ushort16*,__ushort16,__ushort16);
extern void  __vstore_pred_interleave(__bool8,  __uint8*,  __uint8,  __uint8);
extern void  __vstore_pred_interleave(__bool4,  __ulong4*,  __ulong4,  __ulong4);
#endif

#ifndef __C7100__
/* VSTPINTHB, VSTPINTHH, VSTPINTHW, VSTPINTHD - STORES EVERY ODD ELEMENT */
#if __C7X_VEC_SIZE_BITS__ == 512
extern void  __vstore_pred_interleave_odd(__bool64,  __char64*,  __char64,  __char64);
extern void  __vstore_pred_interleave_odd(__bool32,  __short32*, __short32, __short32);
extern void  __vstore_pred_interleave_odd(__bool16,  __int16*,   __int16,   __int16);
extern void  __vstore_pred_interleave_odd(__bool8,  __long8*,   __long8,   __long8);
extern void  __vstore_pred_interleave_odd(__bool64,  __uchar64*, __uchar64, __uchar64);
extern void  __vstore_pred_interleave_odd(__bool32,  __ushort32*,__ushort32,__ushort32);
extern void  __vstore_pred_interleave_odd(__bool16,  __uint16*,  __uint16,  __uint16);
extern void  __vstore_pred_interleave_odd(__bool8,  __ulong8*,  __ulong8,  __ulong8);
#elif __C7X_VEC_SIZE_BITS__ == 256
extern void  __vstore_pred_interleave_odd(__bool32,  __char32*,  __char32,  __char32);
extern void  __vstore_pred_interleave_odd(__bool16,  __short16*, __short16, __short16);
extern void  __vstore_pred_interleave_odd(__bool8,  __int8*,   __int8,   __int8);
extern void  __vstore_pred_interleave_odd(__bool4,  __long4*,   __long4,   __long4);
extern void  __vstore_pred_interleave_odd(__bool32,  __uchar32*, __uchar32, __uchar32);
extern void  __vstore_pred_interleave_odd(__bool16,  __ushort16*,__ushort16,__ushort16);
extern void  __vstore_pred_interleave_odd(__bool8,  __uint8*,  __uint8,  __uint8);
extern void  __vstore_pred_interleave_odd(__bool4,  __ulong4*,  __ulong4,  __ulong4);
#endif
#endif /* ! __C7100__ */

/* VSTPINTLB4 - STORES EVERY FOURTH ELEMENT */
#if __C7X_VEC_SIZE_BITS__ == 512
extern void  __vstore_pred_interleave4(__bool32,  __char32*,  __char64,   __char64);
extern void  __vstore_pred_interleave4(__bool32,  __uchar32*, __uchar64,  __uchar64);
#elif __C7X_VEC_SIZE_BITS__ == 256
extern void  __vstore_pred_interleave4(__bool16,  __char16*,  __char32,   __char32);
extern void  __vstore_pred_interleave4(__bool16,  __uchar16*, __uchar32,  __uchar32);
#endif

#ifndef __C7100__
/* VSTPLLINTB, VSTPLLINTH, VSTPLLINTW, VSTPLLINTD - STORES LOW VECTOR HALVES */
#if __C7X_VEC_SIZE_BITS__ == 512
extern void  __vstore_pred_interleave_low_low(__bool64,  __char64*,  __char64,  __char64);
extern void  __vstore_pred_interleave_low_low(__bool32,  __short32*, __short32, __short32);
extern void  __vstore_pred_interleave_low_low(__bool16,  __int16*,   __int16,   __int16);
extern void  __vstore_pred_interleave_low_low(__bool8,  __long8*,   __long8,   __long8);
extern void  __vstore_pred_interleave_low_low(__bool64,  __uchar64*, __uchar64, __uchar64);
extern void  __vstore_pred_interleave_low_low(__bool32,  __ushort32*,__ushort32,__ushort32);
extern void  __vstore_pred_interleave_low_low(__bool16,  __uint16*,  __uint16,  __uint16);
extern void  __vstore_pred_interleave_low_low(__bool8,  __ulong8*,  __ulong8,  __ulong8);
#elif __C7X_VEC_SIZE_BITS__ == 256
extern void  __vstore_pred_interleave_low_low(__bool32,  __char32*,  __char32,  __char32);
extern void  __vstore_pred_interleave_low_low(__bool16,  __short16*, __short16, __short16);
extern void  __vstore_pred_interleave_low_low(__bool8,  __int8*,   __int8,   __int8);
extern void  __vstore_pred_interleave_low_low(__bool4,  __long4*,   __long4,   __long4);
extern void  __vstore_pred_interleave_low_low(__bool32,  __uchar32*, __uchar32, __uchar32);
extern void  __vstore_pred_interleave_low_low(__bool16,  __ushort16*,__ushort16,__ushort16);
extern void  __vstore_pred_interleave_low_low(__bool8,  __uint8*,  __uint8,  __uint8);
extern void  __vstore_pred_interleave_low_low(__bool4,  __ulong4*,  __ulong4,  __ulong4);
#endif

/* Half-vector form of VSTPLLINT[BHWD]. */
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __vstore_pred_interleave_low_low(__bool64, __char64*,  __char32,  __char32);
extern void __vstore_pred_interleave_low_low(__bool32, __short32*, __short16, __short16);
extern void __vstore_pred_interleave_low_low(__bool16, __int16*,   __int8,   __int8);
extern void __vstore_pred_interleave_low_low(__bool8, __long8*,   __long4,   __long4);
extern void __vstore_pred_interleave_low_low(__bool64, __uchar64*, __uchar32, __uchar32);
extern void __vstore_pred_interleave_low_low(__bool32, __ushort32*,__ushort16,__ushort16);
extern void __vstore_pred_interleave_low_low(__bool16, __uint16*,  __uint8,  __uint8);
extern void __vstore_pred_interleave_low_low(__bool8, __ulong8*,  __ulong4,  __ulong4);
#elif __C7X_VEC_SIZE_BITS__ == 256
extern void __vstore_pred_interleave_low_low(__bool32, __char32*,  __char16,  __char16);
extern void __vstore_pred_interleave_low_low(__bool16, __short16*, __short8, __short8);
extern void __vstore_pred_interleave_low_low(__bool8, __int8*,   __int4,   __int4);
extern void __vstore_pred_interleave_low_low(__bool4, __long4*,   __long2,   __long2);
extern void __vstore_pred_interleave_low_low(__bool32, __uchar32*, __uchar16, __uchar16);
extern void __vstore_pred_interleave_low_low(__bool16, __ushort16*,__ushort8,__ushort8);
extern void __vstore_pred_interleave_low_low(__bool8, __uint8*,  __uint4,  __uint4);
extern void __vstore_pred_interleave_low_low(__bool4, __ulong4*,  __ulong2,  __ulong2);
#endif

/* VSTPHHINTB, VSTPHHINTH, VSTPHHINTW, VSTPHHINTD - STORES HIGH VECTOR HALVES */
#if __C7X_VEC_SIZE_BITS__ == 512
extern void  __vstore_pred_interleave_high_high(__bool64,  __char64*,  __char64,  __char64);
extern void  __vstore_pred_interleave_high_high(__bool32,  __short32*, __short32, __short32);
extern void  __vstore_pred_interleave_high_high(__bool16,  __int16*,   __int16,   __int16);
extern void  __vstore_pred_interleave_high_high(__bool8,  __long8*,   __long8,   __long8);
extern void  __vstore_pred_interleave_high_high(__bool64,  __uchar64*, __uchar64, __uchar64);
extern void  __vstore_pred_interleave_high_high(__bool32,  __ushort32*,__ushort32,__ushort32);
extern void  __vstore_pred_interleave_high_high(__bool16,  __uint16*,  __uint16,  __uint16);
extern void  __vstore_pred_interleave_high_high(__bool8,  __ulong8*,  __ulong8,  __ulong8);
#elif __C7X_VEC_SIZE_BITS__ == 256
extern void  __vstore_pred_interleave_high_high(__bool32,  __char32*,  __char32,  __char32);
extern void  __vstore_pred_interleave_high_high(__bool16,  __short16*, __short16, __short16);
extern void  __vstore_pred_interleave_high_high(__bool8,  __int8*,   __int8,   __int8);
extern void  __vstore_pred_interleave_high_high(__bool4,  __long4*,   __long4,   __long4);
extern void  __vstore_pred_interleave_high_high(__bool32,  __uchar32*, __uchar32, __uchar32);
extern void  __vstore_pred_interleave_high_high(__bool16,  __ushort16*,__ushort16,__ushort16);
extern void  __vstore_pred_interleave_high_high(__bool8,  __uint8*,  __uint8,  __uint8);
extern void  __vstore_pred_interleave_high_high(__bool4,  __ulong4*,  __ulong4,  __ulong4);
#endif
#endif /* ! __C7100__ */

/* VSTP2B, VSTP4B, VSTP8B, VSTP16B, VSTP32B, VSTP64B */
extern void  __vstore_pred(__bool2,   __char2*,   __char2);
extern void  __vstore_pred(__bool4,   __char4*,   __char4);
extern void  __vstore_pred(__bool8,   __char8*,   __char8);
extern void  __vstore_pred(__bool16,  __char16*,  __char16);
extern void  __vstore_pred(__bool32,  __char32*,  __char32);
#if __C7X_VEC_SIZE_BITS__ >= 512
extern void  __vstore_pred(__bool64,  __char64*,  __char64);
#endif

extern void  __vstore_pred(__bool2,   __uchar2*,  __uchar2);
extern void  __vstore_pred(__bool4,   __uchar4*,  __uchar4);
extern void  __vstore_pred(__bool8,   __uchar8*,  __uchar8);
extern void  __vstore_pred(__bool16,  __uchar16*, __uchar16);
extern void  __vstore_pred(__bool32,  __uchar32*, __uchar32);
#if __C7X_VEC_SIZE_BITS__ >= 512
extern void  __vstore_pred(__bool64,  __uchar64*, __uchar64);
#endif

/* VSTP2H, VSTP4H, VSTP8H, VSTP16H, VSTP32H */
extern void  __vstore_pred(__bool2,   __short2*, __short2);
extern void  __vstore_pred(__bool4,   __short4*, __short4);
extern void  __vstore_pred(__bool8,   __short8*, __short8);
extern void  __vstore_pred(__bool16,  __short16*, __short16);
#if __C7X_VEC_SIZE_BITS__ >= 512
extern void  __vstore_pred(__bool32,  __short32*, __short32);
#endif

extern void  __vstore_pred(__bool2,   __ushort2*, __ushort2);
extern void  __vstore_pred(__bool4,   __ushort4*, __ushort4);
extern void  __vstore_pred(__bool8,   __ushort8*, __ushort8);
extern void  __vstore_pred(__bool16,  __ushort16*, __ushort16);
#if __C7X_VEC_SIZE_BITS__ >= 512
extern void  __vstore_pred(__bool32,  __ushort32*, __ushort32);
#endif

extern void  __vstore_pred(__bool2,   __cchar2*, __cchar2);
extern void  __vstore_pred(__bool4,   __cchar4*, __cchar4);
extern void  __vstore_pred(__bool8,   __cchar8*, __cchar8);
extern void  __vstore_pred(__bool16,  __cchar16*, __cchar16);
#if __C7X_VEC_SIZE_BITS__ >= 512
extern void  __vstore_pred(__bool32,  __cchar32*, __cchar32);
#endif

/* VSTP2W, VSTP4W, VSTP8W, VSTP16W */
extern void  __vstore_pred(__bool2,   __int2*,     __int2);
extern void  __vstore_pred(__bool4,   __int4*,     __int4);
extern void  __vstore_pred(__bool8,   __int8*,     __int8);
#if __C7X_VEC_SIZE_BITS__ >= 512
extern void  __vstore_pred(__bool16,  __int16*,    __int16);
#endif

extern void  __vstore_pred(__bool2,   __uint2*,    __uint2);
extern void  __vstore_pred(__bool4,   __uint4*,    __uint4);
extern void  __vstore_pred(__bool8,   __uint8*,    __uint8);
#if __C7X_VEC_SIZE_BITS__ >= 512
extern void  __vstore_pred(__bool16,  __uint16*,   __uint16);
#endif

extern void  __vstore_pred(__bool2,   __float2*,   __float2);
extern void  __vstore_pred(__bool4,   __float4*,   __float4);
extern void  __vstore_pred(__bool8,   __float8*,   __float8);
#if __C7X_VEC_SIZE_BITS__ >= 512
extern void  __vstore_pred(__bool16,  __float16*,  __float16);
#endif

extern void  __vstore_pred(__bool2,   __cshort2*,  __cshort2);
extern void  __vstore_pred(__bool4,   __cshort4*,  __cshort4);
extern void  __vstore_pred(__bool8,   __cshort8*,  __cshort8);
#if __C7X_VEC_SIZE_BITS__ >= 512
extern void  __vstore_pred(__bool16,  __cshort16*, __cshort16);
#endif

/* VSTP2D, VSTP4D, VSTP8D */
extern void  __vstore_pred(__bool2,  __long2*,   __long2);
extern void  __vstore_pred(__bool4,  __long4*,   __long4);
#if __C7X_VEC_SIZE_BITS__ >= 512
extern void  __vstore_pred(__bool8,  __long8*,   __long8);
#endif

extern void  __vstore_pred(__bool2,  __ulong2*,  __ulong2);
extern void  __vstore_pred(__bool4,  __ulong4*,  __ulong4);
#if __C7X_VEC_SIZE_BITS__ >= 512
extern void  __vstore_pred(__bool8,  __ulong8*,  __ulong8);
#endif

extern void  __vstore_pred(__bool2,  __double2*, __double2);
extern void  __vstore_pred(__bool4,  __double4*, __double4);
#if __C7X_VEC_SIZE_BITS__ >= 512
extern void  __vstore_pred(__bool8,  __double8*, __double8);
#endif

extern void  __vstore_pred(__bool2,  __cint2*,   __cint2);
extern void  __vstore_pred(__bool4,  __cint4*,   __cint4);
#if __C7X_VEC_SIZE_BITS__ >= 512
extern void  __vstore_pred(__bool8,  __cint8*,   __cint8);
#endif

extern void  __vstore_pred(__bool2,  __cfloat2*, __cfloat2);
extern void  __vstore_pred(__bool4,  __cfloat4*, __cfloat4);
#if __C7X_VEC_SIZE_BITS__ >= 512
extern void  __vstore_pred(__bool8,  __cfloat8*, __cfloat8);
#endif

/* VSTPBSVPACKL, VSTPBSVPACKH, VSTPBSVPACKHS1: PRED CORRESPONDS TO SRC DATA */
#if __C7X_VEC_SIZE_BITS__ == 256
extern void  __vstore_pred_packl(__bool16,    __char16*,  __short16);
extern void  __vstore_pred_packl(__bool16,    __uchar16*, __ushort16);
extern void  __vstore_pred_packh(__bool16,    __char16*,  __short16);
extern void  __vstore_pred_packh(__bool16,    __uchar16*, __ushort16);
extern void  __vstore_pred_packhs1(__bool16,  __char16*,  __short16);
extern void  __vstore_pred_packhs1(__bool16,  __uchar16*, __ushort16);
#elif __C7X_VEC_SIZE_BITS__ == 512
extern void  __vstore_pred_packl(__bool32,    __char32*,  __short32);
extern void  __vstore_pred_packl(__bool32,    __uchar32*, __ushort32);
extern void  __vstore_pred_packh(__bool32,    __char32*,  __short32);
extern void  __vstore_pred_packh(__bool32,    __uchar32*, __ushort32);
extern void  __vstore_pred_packhs1(__bool32,  __char32*,  __short32);
extern void  __vstore_pred_packhs1(__bool32,  __uchar32*, __ushort32);
#endif

/* VSTPHSVPACKL, VSTPHSVPACKH, VSTPHSVPACKHS1: PRED CORRESPONDS TO SRC DATA */
#if __C7X_VEC_SIZE_BITS__ == 256
extern void  __vstore_pred_packl(__bool8,    __short8*,  __int8);
extern void  __vstore_pred_packl(__bool8,    __ushort8*, __uint8);
extern void  __vstore_pred_packh(__bool8,    __short8*,  __int8);
extern void  __vstore_pred_packh(__bool8,    __ushort8*, __uint8);
extern void  __vstore_pred_packhs1(__bool8,  __short8*,  __int8);
extern void  __vstore_pred_packhs1(__bool8,  __ushort8*, __uint8);
#elif __C7X_VEC_SIZE_BITS__ == 512
extern void  __vstore_pred_packl(__bool16,    __short16*,  __int16);
extern void  __vstore_pred_packl(__bool16,    __ushort16*, __uint16);
extern void  __vstore_pred_packh(__bool16,    __short16*,  __int16);
extern void  __vstore_pred_packh(__bool16,    __ushort16*, __uint16);
extern void  __vstore_pred_packhs1(__bool16,  __short16*,  __int16);
extern void  __vstore_pred_packhs1(__bool16,  __ushort16*, __uint16);
#endif

/* VSTPWSVPACKB: PRED CORRESPONDS TO SRC DATA */
#if __C7X_VEC_SIZE_BITS__ == 256
extern void  __vstore_pred_pack_byte(__bool8,  __char8*,  __int8);
extern void  __vstore_pred_pack_byte(__bool8,  __uchar8*, __uint8);
#elif __C7X_VEC_SIZE_BITS__ == 512
extern void  __vstore_pred_pack_byte(__bool16,  __char16*,  __int16);
extern void  __vstore_pred_pack_byte(__bool16,  __uchar16*, __uint16);
#endif

/* VSTPWSVPACKL, VSTPWSVPACKH, VSTPWSVPACKHS1: PRED CORRESPONDS TO SRC DATA */
#if __C7X_VEC_SIZE_BITS__ == 256
extern void  __vstore_pred_packl(__bool4,    __int4*,  __long4);
extern void  __vstore_pred_packl(__bool4,    __uint4*, __ulong4);
extern void  __vstore_pred_packh(__bool4,    __int4*,  __long4);
extern void  __vstore_pred_packh(__bool4,    __uint4*, __ulong4);
extern void  __vstore_pred_packhs1(__bool4,  __int4*,  __long4);
extern void  __vstore_pred_packhs1(__bool4,  __uint4*, __ulong4);
#elif __C7X_VEC_SIZE_BITS__ == 512
extern void  __vstore_pred_packl(__bool8,    __int8*,  __long8);
extern void  __vstore_pred_packl(__bool8,    __uint8*, __ulong8);
extern void  __vstore_pred_packh(__bool8,    __int8*,  __long8);
extern void  __vstore_pred_packh(__bool8,    __uint8*, __ulong8);
extern void  __vstore_pred_packhs1(__bool8,  __int8*,  __long8);
extern void  __vstore_pred_packhs1(__bool8,  __uint8*, __ulong8);
#endif

/* VSTPBPACKL, VSTPBPACKH, VSTPBPACKHS1: PRED CORRESPONDS TO PACKED DATA */
#if __C7X_VEC_SIZE_BITS__ == 256
extern void  __vstore_pred_packl_2src(__bool32,    __char32*, __short16,  __short16);
extern void  __vstore_pred_packl_2src(__bool32,    __uchar32*, __ushort16, __ushort16);
extern void  __vstore_pred_packh_2src(__bool32,    __char32*, __short16,  __short16);
extern void  __vstore_pred_packh_2src(__bool32,    __uchar32*, __ushort16, __ushort16);
extern void  __vstore_pred_packhs1_2src(__bool32,  __char32*, __short16,  __short16);
extern void  __vstore_pred_packhs1_2src(__bool32,  __uchar32*, __ushort16, __ushort16);
#elif __C7X_VEC_SIZE_BITS__ == 512
extern void  __vstore_pred_packl_2src(__bool64,    __char64*, __short32,  __short32);
extern void  __vstore_pred_packl_2src(__bool64,    __uchar64*, __ushort32, __ushort32);
extern void  __vstore_pred_packh_2src(__bool64,    __char64*, __short32,  __short32);
extern void  __vstore_pred_packh_2src(__bool64,    __uchar64*, __ushort32, __ushort32);
extern void  __vstore_pred_packhs1_2src(__bool64,  __char64*, __short32,  __short32);
extern void  __vstore_pred_packhs1_2src(__bool64,  __uchar64*, __ushort32, __ushort32);
#endif

/* VSTPHPACKL, VSTPHPACKH, VSTPHPACKHS1: PRED CORRESPONDS TO PACKED DATA */
#if __C7X_VEC_SIZE_BITS__ == 256
extern void  __vstore_pred_packl_2src(__bool16,    __short16*, __int8,   __int8);
extern void  __vstore_pred_packl_2src(__bool16,    __ushort16*, __uint8, __uint8);
extern void  __vstore_pred_packh_2src(__bool16,    __short16*, __int8,   __int8);
extern void  __vstore_pred_packh_2src(__bool16,    __ushort16*, __uint8, __uint8);
extern void  __vstore_pred_packhs1_2src(__bool16,  __short16*, __int8,   __int8);
extern void  __vstore_pred_packhs1_2src(__bool16,  __ushort16*, __uint8, __uint8);
#elif __C7X_VEC_SIZE_BITS__ == 512
extern void  __vstore_pred_packl_2src(__bool32,    __short32*, __int16,   __int16);
extern void  __vstore_pred_packl_2src(__bool32,    __ushort32*, __uint16, __uint16);
extern void  __vstore_pred_packh_2src(__bool32,    __short32*, __int16,   __int16);
extern void  __vstore_pred_packh_2src(__bool32,    __ushort32*, __uint16, __uint16);
extern void  __vstore_pred_packhs1_2src(__bool32,  __short32*, __int16,   __int16);
extern void  __vstore_pred_packhs1_2src(__bool32,  __ushort32*, __uint16, __uint16);
#endif

/* VSTPWPACKB: PRED CORRESPONDS TO PACKED DATA */
#if __C7X_VEC_SIZE_BITS__ == 256
extern void  __vstore_pred_pack_byte_2src(__bool16,  __char16*, __int8,  __int8);
extern void  __vstore_pred_pack_byte_2src(__bool16,  __uchar16*, __uint8, __uint8);
#elif __C7X_VEC_SIZE_BITS__ == 512
extern void  __vstore_pred_pack_byte_2src(__bool32,  __char32*, __int16,  __int16);
extern void  __vstore_pred_pack_byte_2src(__bool32,  __uchar32*, __uint16, __uint16);
#endif

/* VSTPWPACKL, VSTPWPACKH, VSTPWPACKHS1: PRED CORRESPONDS TO PACKED DATA */
#if __C7X_VEC_SIZE_BITS__ == 256
extern void  __vstore_pred_packl_2src(__bool8,    __int8*, __long4,  __long4);
extern void  __vstore_pred_packl_2src(__bool8,    __uint8*, __ulong4, __ulong4);
extern void  __vstore_pred_packh_2src(__bool8,    __int8*, __long4,   __long4);
extern void  __vstore_pred_packh_2src(__bool8,    __uint8*, __ulong4, __ulong4);
extern void  __vstore_pred_packhs1_2src(__bool8,  __int8*, __long4,   __long4);
extern void  __vstore_pred_packhs1_2src(__bool8,  __uint8*, __ulong4, __ulong4);
#elif __C7X_VEC_SIZE_BITS__ == 512
extern void  __vstore_pred_packl_2src(__bool16,    __int16*, __long8,  __long8);
extern void  __vstore_pred_packl_2src(__bool16,    __uint16*, __ulong8, __ulong8);
extern void  __vstore_pred_packh_2src(__bool16,    __int16*, __long8,   __long8);
extern void  __vstore_pred_packh_2src(__bool16,    __uint16*, __ulong8, __ulong8);
extern void  __vstore_pred_packhs1_2src(__bool16,  __int16*, __long8,   __long8);
extern void  __vstore_pred_packhs1_2src(__bool16,  __uint16*, __ulong8, __ulong8);
#endif

/* VSTPDPACKL, VSTPDPACKH, VSTPDPACKHS1: PRED CORRESPONDS TO PACKED DATA */
#if __C7X_VEC_SIZE_BITS__ == 256
extern void  __vstore_pred_packl_long_2src(__bool4,    __long4*, __long4, __long4);
extern void  __vstore_pred_packl_long_2src(__bool4,    __ulong4*, __ulong4,__ulong4);
extern void  __vstore_pred_packh_long_2src(__bool4,    __long4*, __long4, __long4);
extern void  __vstore_pred_packh_long_2src(__bool4,    __ulong4*, __ulong4,__ulong4);
extern void  __vstore_pred_packhs1_long_2src(__bool4,  __long4*, __long4, __long4);
extern void  __vstore_pred_packhs1_long_2src(__bool4,  __ulong4*, __ulong4,__ulong4);
#elif __C7X_VEC_SIZE_BITS__ == 512
extern void  __vstore_pred_packl_long_2src(__bool8,    __long8*, __long8, __long8);
extern void  __vstore_pred_packl_long_2src(__bool8,    __ulong8*, __ulong8,__ulong8);
extern void  __vstore_pred_packh_long_2src(__bool8,    __long8*, __long8, __long8);
extern void  __vstore_pred_packh_long_2src(__bool8,    __ulong8*, __ulong8,__ulong8);
extern void  __vstore_pred_packhs1_long_2src(__bool8,  __long8*, __long8, __long8);
extern void  __vstore_pred_packhs1_long_2src(__bool8,  __ulong8*, __ulong8,__ulong8);
#endif

/* VSTPBITRWH */
#if __C7X_VEC_SIZE_BITS__ == 512
extern void  __vstore_pred_reverse_bit(__bool16,  __cshort16*, __cshort16);
#elif __C7X_VEC_SIZE_BITS__ == 256
extern void  __vstore_pred_reverse_bit(__bool8,  __cshort8*, __cshort8);
#endif

/* VSTPBITRDW */
#if __C7X_VEC_SIZE_BITS__ == 512
extern void  __vstore_pred_reverse_bit(__bool8,  __cint8*,   __cint8);
extern void  __vstore_pred_reverse_bit(__bool8,  __cfloat8*, __cfloat8);
#elif __C7X_VEC_SIZE_BITS__ == 256
extern void  __vstore_pred_reverse_bit(__bool4,  __cint4*,   __cint4);
extern void  __vstore_pred_reverse_bit(__bool4,  __cfloat4*, __cfloat4);
#endif

/* STKW, ST0KW */
extern void  __vstore_const       (uint32_t*,    uint32_t);

/* VSTK2W, VST0K2W */
extern void  __vstore_const_uint2 (__uint2*,   uint32_t);

/* VSTK4W, VST0K4W */
extern void  __vstore_const_uint4 (__uint4*,   uint32_t);

/* VSTK8W, VST0K8W */
extern void  __vstore_const_uint8 (__uint8*,   uint32_t);

/* VSTK16W, VST0K16W */
#if __C7X_VEC_SIZE_BITS__ >= 512
extern void  __vstore_const_uint16(__uint16*,  uint32_t);
#endif

/* VSTBSVPACKL, VSTBSVPACKH, VSTBSVPACKHS1 */
/*
#if __C7X_VEC_SIZE_BITS__ == 256
void  __vstore_packl(__char16*, __short16);
void  __vstore_packl(__uchar16*, __ushort16);
void  __vstore_packh(__char16*, __short16);
void  __vstore_packh(__uchar16*, __ushort16);
void  __vstore_packhs1(__char16*, __short16);
void  __vstore_packhs1(__uchar16*, __ushort16);
#elif __C7X_VEC_SIZE_BITS__ == 512
void  __vstore_packl(__char32*, __short32);
void  __vstore_packl(__uchar32*, __ushort32);
void  __vstore_packh(__char32*, __short32);
void  __vstore_packh(__uchar32*, __ushort32);
void  __vstore_packhs1(__char32*, __short32);
void  __vstore_packhs1(__uchar32*, __ushort32);
#endif
*/

/* VSTHSVPACKL, VSTHSVPACKH, VSTHSVPACKHS1 */
/*
#if __C7X_VEC_SIZE_BITS__ == 256
void  __vstore_packl(__short8*, __int8);
void  __vstore_packl(__ushort8*, __uint8);
void  __vstore_packh(__short8*, __int8);
void  __vstore_packh(__ushort8*, __uint8);
void  __vstore_packhs1(__short8*, __int8);
void  __vstore_packhs1(__ushort8*, __uint8);
#elif __C7X_VEC_SIZE_BITS__ == 512
void  __vstore_packl(__short16*, __int16);
void  __vstore_packl(__ushort16*, __uint16);
void  __vstore_packh(__short16*, __int16);
void  __vstore_packh(__ushort16*, __uint16);
void  __vstore_packhs1(__short16*, __int16);
void  __vstore_packhs1(__ushort16*, __uint16);
#endif
*/

/* VSTWSVPACKB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern void  __vstore_pack_byte(__char8*, __int8);
extern void  __vstore_pack_byte(__uchar8*, __uint8);
#elif __C7X_VEC_SIZE_BITS__ == 512
extern void  __vstore_pack_byte(__char16*, __int16);
extern void  __vstore_pack_byte(__uchar16*, __uint16);
#endif

/* VSTWSVPACKL, VSTWSVPACKH, VSTWSVPACKHS1 */
/*
#if __C7X_VEC_SIZE_BITS__ == 256
void  __vstore_packl(__int4*, __long4);
void  __vstore_packl(__uint4*, __ulong4);
void  __vstore_packh(__int4*, __long4);
void  __vstore_packh(__uint4*, __ulong4);
void  __vstore_packhs1(__int4*, __long4);
void  __vstore_packhs1(__uint4*, __ulong4);
#elif __C7X_VEC_SIZE_BITS__ == 512
void  __vstore_packl(__int8*, __long8);
void  __vstore_packl(__uint8*, __ulong8);
void  __vstore_packh(__int8*, __long8);
void  __vstore_packh(__uint8*, __ulong8);
void  __vstore_packhs1(__int8*, __long8);
void  __vstore_packhs1(__uint8*, __ulong8);
#endif
*/

/* VSTDSVPACKL, VSTDSVPACKH, VSTDSVPACKHS1 */
/*
#if __C7X_VEC_SIZE_BITS__ == 256
void  __vstore_packl(__long2*, __long4);
void  __vstore_packl(__ulong2*, __ulong4);
void  __vstore_packh(__long2*, __long4);
void  __vstore_packh(__ulong2*, __ulong4);
void  __vstore_packhs1(__long2*, __long4);
void  __vstore_packhs1(__ulong2*, __ulong4);
#elif __C7X_VEC_SIZE_BITS__ == 512
void  __vstore_packl(__long4*, __long8);
void  __vstore_packl(__ulong4*, __ulong8);
void  __vstore_packh(__long4*, __long8);
void  __vstore_packh(__ulong4*, __ulong8);
void  __vstore_packhs1(__long4*, __long8);
void  __vstore_packhs1(__ulong4*, __ulong8);
#endif
*/

/* VSTBPACKL, VSTBPACKH, VSTBPACKHS1 */
/*
#if __C7X_VEC_SIZE_BITS__ == 256
void  __vstore_packl_2src(__char32*, __short16, __short16);
void  __vstore_packl_2src(__uchar32*, __ushort16, __ushort16);
void  __vstore_packh_2src(__char32*, __short16, __short16);
void  __vstore_packh_2src(__uchar32*, __ushort16, __ushort16);
void  __vstore_packhs1_2src(__char32*, __short16, __short16);
void  __vstore_packhs1_2src(__uchar32*, __ushort16, __ushort16);
#elif __C7X_VEC_SIZE_BITS__ == 512
void  __vstore_packl_2src(__char64*, __short32, __short32);
void  __vstore_packl_2src(__uchar64*, __ushort32, __ushort32);
void  __vstore_packh_2src(__char64*, __short32, __short32);
void  __vstore_packh_2src(__uchar64*, __ushort32, __ushort32);
void  __vstore_packhs1_2src(__char64*, __short32, __short32);
void  __vstore_packhs1_2src(__uchar64*, __ushort32, __ushort32);
#endif
*/

/* VSTHPACKL, VSTHPACKH, VSTHPACKHS1 */
/*
#if __C7X_VEC_SIZE_BITS__ == 256
void  __vstore_packl_2src(__short16*, __int8, __int8);
void  __vstore_packl_2src(__ushort16*, __uint8, __uint8);
void  __vstore_packh_2src(__short16*, __int8, __int8);
void  __vstore_packh_2src(__ushort16*, __uint8, __uint8);
void  __vstore_packhs1_2src(__short16*, __int8, __int8);
void  __vstore_packhs1_2src(__ushort16*, __uint8, __uint8);
#elif __C7X_VEC_SIZE_BITS__ == 512
void  __vstore_packl_2src(__short32*, __int16, __int16);
void  __vstore_packl_2src(__ushort32*, __uint16, __uint16);
void  __vstore_packh_2src(__short32*, __int16, __int16);
void  __vstore_packh_2src(__ushort32*, __uint16, __uint16);
void  __vstore_packhs1_2src(__short32*, __int16, __int16);
void  __vstore_packhs1_2src(__ushort32*, __uint16, __uint16);
#endif
*/

/* VSTWPACKB */
#if __C7X_VEC_SIZE_BITS__ == 256
void  __vstore_pack_byte_2src(__char16*, __int8, __int8);
void  __vstore_pack_byte_2src(__uchar16*, __uint8, __uint8);
#elif __C7X_VEC_SIZE_BITS__ == 512
void  __vstore_pack_byte_2src(__char32*, __int16, __int16);
void  __vstore_pack_byte_2src(__uchar32*, __uint16, __uint16);
#endif

/* VSTWPACKL, VSTWPACKH, VSTWPACKHS1 */
/*
#if __C7X_VEC_SIZE_BITS__ == 256
void  __vstore_packl_2src(__int8*, __long4, __long4);
void  __vstore_packl_2src(__uint8*, __ulong4, __ulong4);
void  __vstore_packh_2src(__int8*, __long4, __long4);
void  __vstore_packh_2src(__uint8*, __ulong4, __ulong4);
void  __vstore_packhs1_2src(__int8*, __long4, __long4);
void  __vstore_packhs1_2src(__uint8*, __ulong4, __ulong4);
#elif __C7X_VEC_SIZE_BITS__ == 512
void  __vstore_packl_2src(__int16*, __long8, __long8);
void  __vstore_packl_2src(__uint16*, __ulong8, __ulong8);
void  __vstore_packh_2src(__int16*, __long8, __long8);
void  __vstore_packh_2src(__uint16*, __ulong8, __ulong8);
void  __vstore_packhs1_2src(__int16*, __long8, __long8);
void  __vstore_packhs1_2src(__uint16*, __ulong8, __ulong8);
#endif
*/

/* VSTDPACKL, VSTDPACKH, VSTDPACKHS1 */
/*
#if __C7X_VEC_SIZE_BITS__ == 256
void  __vstore_packl_2src(__long4*, __long4, __long4);
void  __vstore_packl_2src(__ulong4*, __ulong4, __ulong4);
void  __vstore_packh_2src(__long4*, __long4, __long4);
void  __vstore_packh_2src(__ulong4*, __ulong4, __ulong4);
void  __vstore_packhs1_2src(__long4*, __long4, __long4);
void  __vstore_packhs1_2src(__ulong4*, __ulong4, __ulong4);
#elif __C7X_VEC_SIZE_BITS__ == 512
void  __vstore_packl_2src(__long8*, __long8, __long8);
void  __vstore_packl_2src(__ulong8*, __ulong8, __ulong8);
void  __vstore_packh_2src(__long8*, __long8, __long8);
void  __vstore_packh_2src(__ulong8*, __ulong8, __ulong8);
void  __vstore_packhs1_2src(__long8*, __long8, __long8);
void  __vstore_packhs1_2src(__ulong8*, __ulong8, __ulong8);
#endif
*/

/* VSTBITRWH */
/*
#if __C7X_VEC_SIZE_BITS__ == 512
void  __vstore_reverse_bit(__short32*, __short32);
void  __vstore_reverse_bit(__ushort32*, __ushort32);
void  __vstore_reverse_bit(__cshort16*, __cshort16);
#elif __C7X_VEC_SIZE_BITS__ == 256
void  __vstore_reverse_bit(__short16*, __short16);
void  __vstore_reverse_bit(__ushort16*, __ushort16);
void  __vstore_reverse_bit(__cshort8*, __cshort8);
#endif
*/

/* VSTBITRDW */
/*
#if __C7X_VEC_SIZE_BITS__ == 512
void  __vstore_reverse_bit(__int16*, __int16);
void  __vstore_reverse_bit(__uint16*, __uint16);
void  __vstore_reverse_bit(__float16*, __float16);
void  __vstore_reverse_bit(__cint8*, __cint8);
void  __vstore_reverse_bit(__cfloat8*, __cfloat8);
#elif __C7X_VEC_SIZE_BITS__ == 256
void  __vstore_reverse_bit(__int8*, __int8);
void  __vstore_reverse_bit(__uint8*, __uint8);
void  __vstore_reverse_bit(__float8*, __float8);
void  __vstore_reverse_bit(__cint4*, __cint4);
void  __vstore_reverse_bit(__cfloat4*, __cfloat4);
#endif
*/

/* ASW */
extern int32_t       __atomic_swap(int32_t*, int32_t, int32_t);

/* ASD */
extern int64_t      __atomic_swap(int64_t*, int64_t, int64_t);

/* CASW */
extern int32_t       __atomic_compare_swap(int32_t*, int32_t, int32_t);

/* CASD */
extern int64_t      __atomic_compare_swap(int64_t*, int64_t, int64_t);

/* PFS */
extern void  __prefetch(void*,  unsigned);

/* MTAG argument */
typedef enum
{
    __MTAG_COLOR0        = 0x0,
    __MTAG_COLOR1        = 0x1,
    __MTAG_SWITCH_COLORS = 0x1f
} __MTAG_COLOR;

/* MTAG */
extern void  __mtag(__MTAG_COLOR);

/* MFENCE/MFENCEST argument */
typedef enum
{
    __MFENCE_COLOR0     = 0x0,
    __MFENCE_COLOR1     = 0x1,
    __MFENCE_ALL_COLORS = 0x1f
} __MFENCE_COLOR;

/* MFENCE */
extern void  __memory_fence(__MFENCE_COLOR);

/* MFENCEST */
extern void  __memory_fence_store(__MFENCE_COLOR);

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
extern char2 __gather_set_bits(bool2, char2);
extern char3 __gather_set_bits(bool3, char3);
extern char4 __gather_set_bits(bool4, char4);
extern char8 __gather_set_bits(bool8, char8);
extern char16 __gather_set_bits(bool16, char16);
extern char32 __gather_set_bits(bool32, char32);
#if __C7X_VEC_SIZE_BITS__ >= 512
extern char64 __gather_set_bits(bool64, char64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __gather_unset_bits                                                    */
/*----------------------------------------------------------------------------*/
/* VGATHERNB */
extern char2 __gather_unset_bits(bool2, char2);
extern char3 __gather_unset_bits(bool3, char3);
extern char4 __gather_unset_bits(bool4, char4);
extern char8 __gather_unset_bits(bool8, char8);
extern char16 __gather_unset_bits(bool16, char16);
extern char32 __gather_unset_bits(bool32, char32);
#if __C7X_VEC_SIZE_BITS__ >= 512
extern char64 __gather_unset_bits(bool64, char64);
#endif

/******************************************************************************/
/* __SE_REG and __SE_REG_PAIR Streaming Engine Operands                       */
/*                                                                            */
/* Some intrinsics, such as __matmpy() and __matmpy_u2s() below, take a       */
/* streaming engine operand, which is an enumeration with values representing */
/* which streaming engine to use as well as whether that streaming engine     */
/* advances. All other values are invalid and will produce an error.          */
/******************************************************************************/
typedef enum
{
    __SE_REG_0     = 0,
    __SE_REG_0_ADV = 1,
    __SE_REG_1     = 2,
    __SE_REG_1_ADV = 3,
    __SE_REG_LAST  = 3 /* Don't use directly. */
} __SE_REG;

typedef enum
{
    __SE_REG_PAIR_0     = 0,
    __SE_REG_PAIR_0_ADV = 1,
    __SE_REG_PAIR_LAST  = 1 /* Don't use directly. */
} __SE_REG_PAIR;

/*----------------------------------------------------------------------------*/
/* ID: __matmpy                                                               */
/*----------------------------------------------------------------------------*/
/* VMATMPYHW */
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __matmpy(__SE_REG, __SE_REG);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __matmpy_u2s                                                           */
/*----------------------------------------------------------------------------*/
/* VMATMPYUSHW */
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __matmpy_u2s(__SE_REG, __SE_REG);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __popcount_gather                                                      */
/*----------------------------------------------------------------------------*/
/* PCNTGATHERB */
extern void __popcount_gather(bool2, uint32_t&, bool2&);
extern void __popcount_gather(bool3, uint32_t&, bool3&);
extern void __popcount_gather(bool4, uint32_t&, bool4&);
extern void __popcount_gather(bool8, uint32_t&, bool8&);
extern void __popcount_gather(bool16, uint32_t&, bool16&);
extern void __popcount_gather(bool32, uint32_t&, bool32&);
#if __C7X_VEC_SIZE_BITS__ >= 512
extern void __popcount_gather(bool64, uint32_t&, bool64&);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __rightmost_bit_detect                                                 */
/*----------------------------------------------------------------------------*/
/* PRMBDB */
extern uint32_t __rightmost_bit_detect(bool2);
extern uint32_t __rightmost_bit_detect(bool3);
extern uint32_t __rightmost_bit_detect(bool4);
extern uint32_t __rightmost_bit_detect(bool8);
extern uint32_t __rightmost_bit_detect(bool16);
extern uint32_t __rightmost_bit_detect(bool32);
#if __C7X_VEC_SIZE_BITS__ >= 512
extern uint32_t __rightmost_bit_detect(bool64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __scatter_set_bits                                                     */
/*----------------------------------------------------------------------------*/
/* VSCATTERB */
extern char2 __scatter_set_bits(bool2, char2);
extern char3 __scatter_set_bits(bool3, char3);
extern char4 __scatter_set_bits(bool4, char4);
extern char8 __scatter_set_bits(bool8, char8);
extern char16 __scatter_set_bits(bool16, char16);
extern char32 __scatter_set_bits(bool32, char32);
#if __C7X_VEC_SIZE_BITS__ >= 512
extern char64 __scatter_set_bits(bool64, char64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __scatter_unset_bits                                                   */
/*----------------------------------------------------------------------------*/
/* VSCATTERNB */
extern char2 __scatter_unset_bits(bool2, char2);
extern char3 __scatter_unset_bits(bool3, char3);
extern char4 __scatter_unset_bits(bool4, char4);
extern char8 __scatter_unset_bits(bool8, char8);
extern char16 __scatter_unset_bits(bool16, char16);
extern char32 __scatter_unset_bits(bool32, char32);
#if __C7X_VEC_SIZE_BITS__ >= 512
extern char64 __scatter_unset_bits(bool64, char64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: SCONV                                                                  */
/*----------------------------------------------------------------------------*/
/*

VBUNPKD
int64_t = __convert_long(int8_t);
long2 = __convert_long2(char2);
long3 = __convert_long3(char3);
long4 = __convert_long4(char4);
long8 = __convert_long8(char8);
clong = __convert_clong(cchar);
clong2 = __convert_clong2(cchar2);
clong4 = __convert_clong4(cchar4);

VBUNPKDU
uint64_t = __convert_ulong(uint8_t);
ulong2 = __convert_ulong2(uchar2);
ulong3 = __convert_ulong3(uchar3);
ulong4 = __convert_ulong4(uchar4);
ulong8 = __convert_ulong8(uchar8);
int64_t = __convert_long(uint8_t);
long2 = __convert_long2(uchar2);
long3 = __convert_long3(uchar3);
long4 = __convert_long4(uchar4);
long8 = __convert_long8(uchar8);

VBUNPKH
int16_t = __convert_short(int8_t);
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
uint16_t = __convert_ushort(uint8_t);
ushort2 = __convert_ushort2(uchar2);
ushort3 = __convert_ushort3(uchar3);
ushort4 = __convert_ushort4(uchar4);
ushort8 = __convert_ushort8(uchar8);
ushort16 = __convert_ushort16(uchar16);
ushort32 = __convert_ushort32(uchar32);
int16_t = __convert_short(uint8_t);
short2 = __convert_short2(uchar2);
short3 = __convert_short3(uchar3);
short4 = __convert_short4(uchar4);
short8 = __convert_short8(uchar8);
short16 = __convert_short16(uchar16);
short32 = __convert_short32(uchar32);

VBUNPKW
int32_t = __convert_int(int8_t);
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
uint32_t = __convert_uint(uint8_t);
uint2 = __convert_uint2(uchar2);
uint3 = __convert_uint3(uchar3);
uint4 = __convert_uint4(uchar4);
uint8 = __convert_uint8(uchar8);
uint16 = __convert_uint16(uchar16);
int32_t = __convert_int(uint8_t);
int2 = __convert_int2(uchar2);
int3 = __convert_int3(uchar3);
int4 = __convert_int4(uchar4);
int8 = __convert_int8(uchar8);
int16 = __convert_int16(uchar16);

VHUNPKD
int64_t = __convert_long(int16_t);
long2 = __convert_long2(short2);
long3 = __convert_long3(short3);
long4 = __convert_long4(short4);
long8 = __convert_long8(short8);
clong = __convert_clong(cshort);
clong2 = __convert_clong2(cshort2);
clong4 = __convert_clong4(cshort4);

VHUNPKDU
uint64_t = __convert_ulong(uint16_t);
ulong2 = __convert_ulong2(ushort2);
ulong3 = __convert_ulong3(ushort3);
ulong4 = __convert_ulong4(ushort4);
ulong8 = __convert_ulong8(ushort8);
int64_t = __convert_long(uint16_t);
long2 = __convert_long2(ushort2);
long3 = __convert_long3(ushort3);
long4 = __convert_long4(ushort4);
long8 = __convert_long8(ushort8);

VHUNPKW
int32_t = __convert_int(int16_t);
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
uint32_t = __convert_uint(uint16_t);
uint2 = __convert_uint2(ushort2);
uint3 = __convert_uint3(ushort3);
uint4 = __convert_uint4(ushort4);
uint8 = __convert_uint8(ushort8);
uint16 = __convert_uint16(ushort16);
int32_t = __convert_int(uint16_t);
int2 = __convert_int2(ushort2);
int3 = __convert_int3(ushort3);
int4 = __convert_int4(ushort4);
int8 = __convert_int8(ushort8);
int16 = __convert_int16(ushort16);

VINTSP
float = __convert_float(int32_t);
float2 = __convert_float2(int2);
float3 = __convert_float3(int3);
float4 = __convert_float4(int4);
float8 = __convert_float8(int8);
float16 = __convert_float16(int16);

VINTSPU
float = __convert_float(uint32_t);
float2 = __convert_float2(uint2);
float3 = __convert_float3(uint3);
float4 = __convert_float4(uint4);
float8 = __convert_float8(uint8);
float16 = __convert_float16(uint16);

VSPTRUNC
int32_t = __convert_int(float);
int2 = __convert_int2(float2);
int3 = __convert_int3(float3);
int4 = __convert_int4(float4);
int8 = __convert_int8(float8);
int16 = __convert_int16(float16);

VWUNPKD
int64_t = __convert_long(int32_t);
long2 = __convert_long2(int2);
long3 = __convert_long3(int3);
long4 = __convert_long4(int4);
long8 = __convert_long8(int8);
clong = __convert_clong(cint);
clong2 = __convert_clong2(cint2);
clong4 = __convert_clong4(cint4);

VWUNPKDU
uint64_t = __convert_ulong(uint32_t);
ulong2 = __convert_ulong2(uint2);
ulong3 = __convert_ulong3(uint3);
ulong4 = __convert_ulong4(uint4);
ulong8 = __convert_ulong8(uint8);
int64_t = __convert_long(uint32_t);
long2 = __convert_long2(uint2);
long3 = __convert_long3(uint3);
long4 = __convert_long4(uint4);
long8 = __convert_long8(uint8);

*/

/*----------------------------------------------------------------------------*/
/* ID: __shuffle (Convenience form of __shuffle_stride2_low_low)              */
/*----------------------------------------------------------------------------*/
/* VSHFL2DLL */
extern long2 __shuffle(int64_t, int64_t);
extern long4 __shuffle(long2, long2);
extern double2 __shuffle(double, double);
extern double4 __shuffle(double2, double2);
extern cfloat2 __shuffle(cfloat, cfloat);
extern cfloat4 __shuffle(cfloat2, cfloat2);
extern ulong2 __shuffle(uint64_t, uint64_t);
extern ulong4 __shuffle(ulong2, ulong2);
extern cint2 __shuffle(cint, cint);
extern cint4 __shuffle(cint2, cint2);
#if __C7X_VEC_SIZE_BITS__ >= 512
extern long8 __shuffle(long4, long4);
extern double8 __shuffle(double4, double4);
extern cfloat8 __shuffle(cfloat4, cfloat4);
extern ulong8 __shuffle(ulong4, ulong4);
extern cint8 __shuffle(cint4, cint4);
#endif

/* VSHFL2HLL */
extern short2 __shuffle(int16_t, int16_t);
extern short4 __shuffle(short2, short2);
extern short8 __shuffle(short4, short4);
extern ushort2 __shuffle(uint16_t, uint16_t);
extern ushort4 __shuffle(ushort2, ushort2);
extern ushort8 __shuffle(ushort4, ushort4);
extern cchar2 __shuffle(cchar, cchar);
extern cchar4 __shuffle(cchar2, cchar2);
extern cchar8 __shuffle(cchar4, cchar4);
extern short16 __shuffle(short8, short8);
extern ushort16 __shuffle(ushort8, ushort8);
extern cchar16 __shuffle(cchar8, cchar8);
#if __C7X_VEC_SIZE_BITS__ >= 512
extern short32 __shuffle(short16, short16);
extern ushort32 __shuffle(ushort16, ushort16);
extern cchar32 __shuffle(cchar16, cchar16);
#endif

/* VSHFL2WLL */
extern int2 __shuffle(int32_t, int32_t);
extern int4 __shuffle(int2, int2);
extern float2 __shuffle(float, float);
extern float4 __shuffle(float2, float2);
extern uint2 __shuffle(uint32_t, uint32_t);
extern uint4 __shuffle(uint2, uint2);
extern cshort2 __shuffle(cshort, cshort);
extern cshort4 __shuffle(cshort2, cshort2);
extern int8 __shuffle(int4, int4);
extern float8 __shuffle(float4, float4);
extern uint8 __shuffle(uint4, uint4);
extern cshort8 __shuffle(cshort4, cshort4);
#if __C7X_VEC_SIZE_BITS__ >= 512
extern int16 __shuffle(int8, int8);
extern float16 __shuffle(float8, float8);
extern uint16 __shuffle(uint8, uint8);
extern cshort16 __shuffle(cshort8, cshort8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __popcount                                                             */
/*----------------------------------------------------------------------------*/
/* PBITCNTB */
extern uint32_t __popcount(bool2);
extern uint32_t __popcount(bool3);
extern uint32_t __popcount(bool4);
extern uint32_t __popcount(bool8);
extern uint32_t __popcount(bool16);
extern uint32_t __popcount(bool32);
#if __C7X_VEC_SIZE_BITS__ >= 512
extern uint32_t __popcount(bool64);
#endif

/* AUTOGEN MARKER */
/*----------------------------------------------------------------------------*/
/* ID: ANDB                                                                   */
/*----------------------------------------------------------------------------*/
/*

ANDD, ANDW, VANDW
int8_t = int8_t & int8_t;
int8_t = int8_t & int8_t(k);
char2 = char2 & char2;
char2 = char2 & char2(k);
char3 = char3 & char3;
char3 = char3 & char3(k);
char4 = char4 & char4;
char4 = char4 & char4(k);
char8 = char8 & char8;
char16 = char16 & char16;
char32 = char32 & char32;
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = char64 & char64;
#endif
uint8_t = uint8_t & uint8_t;
uint8_t = uint8_t & uint8_t(k);
uchar2 = uchar2 & uchar2;
uchar2 = uchar2 & uchar2(k);
uchar3 = uchar3 & uchar3;
uchar3 = uchar3 & uchar3(k);
uchar4 = uchar4 & uchar4;
uchar4 = uchar4 & uchar4(k);
uchar8 = uchar8 & uchar8;
uchar16 = uchar16 & uchar16;
uchar32 = uchar32 & uchar32;
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = uchar64 & uchar64;
#endif
int16_t = int16_t & int16_t;
int16_t = int16_t & int16_t(k);
short2 = short2 & short2;
short2 = short2 & short2(k);
short3 = short3 & short3;
short4 = short4 & short4;
short8 = short8 & short8;
short16 = short16 & short16;
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = short32 & short32;
#endif
uint16_t = uint16_t & uint16_t;
uint16_t = uint16_t & uint16_t(k);
ushort2 = ushort2 & ushort2;
ushort2 = ushort2 & ushort2(k);
ushort3 = ushort3 & ushort3;
ushort4 = ushort4 & ushort4;
ushort8 = ushort8 & ushort8;
ushort16 = ushort16 & ushort16;
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = ushort32 & ushort32;
#endif
int32_t = int32_t & int32_t;
int32_t = int32_t & int32_t(k);
int2 = int2 & int2;
int2 = int2 & int2(k);
int3 = int3 & int3;
int3 = int3 & int3(k);
int4 = int4 & int4;
int4 = int4 & int4(k);
int8 = int8 & int8;
int8 = int8 & int8(k);
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = int16 & int16;
int16 = int16 & int16(k);
#endif
uint32_t = uint32_t & uint32_t;
uint32_t = uint32_t & uint32_t(k);
uint2 = uint2 & uint2;
uint2 = uint2 & uint2(k);
uint3 = uint3 & uint3;
uint3 = uint3 & uint3(k);
uint4 = uint4 & uint4;
uint4 = uint4 & uint4(k);
uint8 = uint8 & uint8;
uint8 = uint8 & uint8(k);
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = uint16 & uint16;
uint16 = uint16 & uint16(k);
#endif

ANDD, VANDW
int64_t = int64_t & int64_t;
int64_t = int64_t & int64_t(k);
long2 = long2 & long2;
long3 = long3 & long3;
long4 = long4 & long4;
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = long8 & long8;
#endif
uint64_t = uint64_t & uint64_t;
uint64_t = uint64_t & uint64_t(k);
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
int32_t = int32_t / int32_t;

DIVUW
uint32_t = uint32_t / uint32_t;

DIVDW
int64_t = int64_t / int32_t;

DIVUDW
uint64_t = uint64_t / uint32_t;

*/

/*----------------------------------------------------------------------------*/
/* ID: MINUS                                                                  */
/*----------------------------------------------------------------------------*/
/*

VSUBB
int8_t = int8_t - int8_t;
int8_t = int8_t - int8_t(k);
char2 = char2 - char2;
char2 = char2 - char2(k);
char3 = char3 - char3;
char3 = char3 - char3(k);
char4 = char4 - char4;
char4 = char4 - char4(k);
char8 = char8 - char8;
char8 = char8 - char8(k);
char16 = char16 - char16;
char16 = char16 - char16(k);
char32 = char32 - char32;
char32 = char32 - char32(k);
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = char64 - char64;
char64 = char64 - char64(k);
#endif
uint8_t = uint8_t - uint8_t;
uint8_t = uint8_t - uint8_t(k);
uchar2 = uchar2 - uchar2;
uchar2 = uchar2 - uchar2(k);
uchar3 = uchar3 - uchar3;
uchar3 = uchar3 - uchar3(k);
uchar4 = uchar4 - uchar4;
uchar4 = uchar4 - uchar4(k);
uchar8 = uchar8 - uchar8;
uchar8 = uchar8 - uchar8(k);
uchar16 = uchar16 - uchar16;
uchar16 = uchar16 - uchar16(k);
uchar32 = uchar32 - uchar32;
uchar32 = uchar32 - uchar32(k);
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = uchar64 - uchar64;
uchar64 = uchar64 - uchar64(k);
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
int16_t = int16_t - int16_t;
int16_t = int16_t - int16_t(k);
short2 = short2 - short2;
short2 = short2 - short2(k);
short3 = short3 - short3;
short3 = short3 - short3(k);
short4 = short4 - short4;
short4 = short4 - short4(k);
short8 = short8 - short8;
short8 = short8 - short8(k);
short16 = short16 - short16;
short16 = short16 - short16(k);
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = short32 - short32;
short32 = short32 - short32(k);
#endif
uint16_t = uint16_t - uint16_t;
uint16_t = uint16_t - uint16_t(k);
ushort2 = ushort2 - ushort2;
ushort2 = ushort2 - ushort2(k);
ushort3 = ushort3 - ushort3;
ushort3 = ushort3 - ushort3(k);
ushort4 = ushort4 - ushort4;
ushort4 = ushort4 - ushort4(k);
ushort8 = ushort8 - ushort8;
ushort8 = ushort8 - ushort8(k);
ushort16 = ushort16 - ushort16;
ushort16 = ushort16 - ushort16(k);
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = ushort32 - ushort32;
ushort32 = ushort32 - ushort32(k);
#endif
cshort = cshort - cshort;
cshort2 = cshort2 - cshort2;
cshort4 = cshort4 - cshort4;
cshort8 = cshort8 - cshort8;
#if __C7X_VEC_SIZE_BITS__ == 512
cshort16 = cshort16 - cshort16;
#endif

SUBW, VSUBW
int32_t = int32_t - int32_t;
int32_t = int32_t - int32_t(k);
int2 = int2 - int2;
int2 = int2 - int2(k);
int3 = int3 - int3;
int3 = int3 - int3(k);
int4 = int4 - int4;
int4 = int4 - int4(k);
int8 = int8 - int8;
int8 = int8 - int8(k);
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = int16 - int16;
int16 = int16 - int16(k);
#endif
uint32_t = uint32_t - uint32_t;
uint32_t = uint32_t - uint32_t(k);
uint2 = uint2 - uint2;
uint2 = uint2 - uint2(k);
uint3 = uint3 - uint3;
uint3 = uint3 - uint3(k);
uint4 = uint4 - uint4;
uint4 = uint4 - uint4(k);
uint8 = uint8 - uint8;
uint8 = uint8 - uint8(k);
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = uint16 - uint16;
uint16 = uint16 - uint16(k);
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
int64_t = int64_t - int64_t;
int64_t = int64_t - int64_t(k);
long2 = long2 - long2;
long2 = long2 - long2(k);
long3 = long3 - long3;
long3 = long3 - long3(k);
long4 = long4 - long4;
long4 = long4 - long4(k);
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = long8 - long8;
long8 = long8 - long8(k);
#endif
uint64_t = uint64_t - uint64_t;
uint64_t = uint64_t - uint64_t(k);
ulong2 = ulong2 - ulong2;
ulong2 = ulong2 - ulong2(k);
ulong3 = ulong3 - ulong3;
ulong3 = ulong3 - ulong3(k);
ulong4 = ulong4 - ulong4;
ulong4 = ulong4 - ulong4(k);
#if __C7X_VEC_SIZE_BITS__ == 512
ulong8 = ulong8 - ulong8;
ulong8 = ulong8 - ulong8(k);
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
int32_t = int32_t % int32_t;

MODUW
uint32_t = uint32_t % uint32_t;

MODDW
int64_t = int64_t % int32_t;

MODUDW
uint64_t = uint64_t % uint32_t;

*/

/*----------------------------------------------------------------------------*/
/* ID: MULT                                                                   */
/*----------------------------------------------------------------------------*/
/*

VMPYBB
int8_t = int8_t * int8_t;
char2 = char2 * char2;
char3 = char3 * char3;
char4 = char4 * char4;
char8 = char8 * char8;
char16 = char16 * char16;
char32 = char32 * char32;
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = char64 * char64;
#endif
uint8_t = uint8_t * uint8_t;
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
int16_t = int16_t * int16_t;
short2 = short2 * short2;
short3 = short3 * short3;
short4 = short4 * short4;
short8 = short8 * short8;
short16 = short16 * short16;
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = short32 * short32;
#endif

MPYHW
int32_t = int16_t * int16_t;

MPYSUHW
int32_t = int16_t * uint16_t;

VMPYHH
uint16_t = uint16_t * uint16_t;
ushort2 = ushort2 * ushort2;
ushort3 = ushort3 * ushort3;
ushort4 = ushort4 * ushort4;
ushort8 = ushort8 * ushort8;
ushort16 = ushort16 * ushort16;
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = ushort32 * ushort32;
#endif

MPYUHW
uint32_t = uint16_t * uint16_t;

MPYWW, VMPYWW
int32_t = int32_t * int32_t;
int2 = int2 * int2;
int3 = int3 * int3;
int4 = int4 * int4;
int8 = int8 * int8;
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = int16 * int16;
#endif
uint32_t = uint32_t * uint32_t;
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
int64_t = int64_t * int64_t;
long2 = long2 * long2;
long3 = long3 * long3;
long4 = long4 * long4;
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = long8 * long8;
#endif
uint64_t = uint64_t * uint64_t;
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
int8_t = int8_t | int8_t;
int8_t = int8_t | int8_t(k);
char2 = char2 | char2;
char2 = char2 | char2(k);
char3 = char3 | char3;
char3 = char3 | char3(k);
char4 = char4 | char4;
char4 = char4 | char4(k);
char8 = char8 | char8;
char16 = char16 | char16;
char32 = char32 | char32;
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = char64 | char64;
#endif
uint8_t = uint8_t | uint8_t;
uint8_t = uint8_t | uint8_t(k);
uchar2 = uchar2 | uchar2;
uchar2 = uchar2 | uchar2(k);
uchar3 = uchar3 | uchar3;
uchar3 = uchar3 | uchar3(k);
uchar4 = uchar4 | uchar4;
uchar4 = uchar4 | uchar4(k);
uchar8 = uchar8 | uchar8;
uchar16 = uchar16 | uchar16;
uchar32 = uchar32 | uchar32;
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = uchar64 | uchar64;
#endif
int16_t = int16_t | int16_t;
int16_t = int16_t | int16_t(k);
short2 = short2 | short2;
short2 = short2 | short2(k);
short3 = short3 | short3;
short4 = short4 | short4;
short8 = short8 | short8;
short16 = short16 | short16;
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = short32 | short32;
#endif
uint16_t = uint16_t | uint16_t;
uint16_t = uint16_t | uint16_t(k);
ushort2 = ushort2 | ushort2;
ushort2 = ushort2 | ushort2(k);
ushort3 = ushort3 | ushort3;
ushort4 = ushort4 | ushort4;
ushort8 = ushort8 | ushort8;
ushort16 = ushort16 | ushort16;
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = ushort32 | ushort32;
#endif
int32_t = int32_t | int32_t;
int32_t = int32_t | int32_t(k);
int2 = int2 | int2;
int2 = int2 | int2(k);
int3 = int3 | int3;
int3 = int3 | int3(k);
int4 = int4 | int4;
int4 = int4 | int4(k);
int8 = int8 | int8;
int8 = int8 | int8(k);
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = int16 | int16;
int16 = int16 | int16(k);
#endif
uint32_t = uint32_t | uint32_t;
uint32_t = uint32_t | uint32_t(k);
uint2 = uint2 | uint2;
uint2 = uint2 | uint2(k);
uint3 = uint3 | uint3;
uint3 = uint3 | uint3(k);
uint4 = uint4 | uint4;
uint4 = uint4 | uint4(k);
uint8 = uint8 | uint8;
uint8 = uint8 | uint8(k);
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = uint16 | uint16;
uint16 = uint16 | uint16(k);
#endif

ORD, VORW
int64_t = int64_t | int64_t;
int64_t = int64_t | int64_t(k);
long2 = long2 | long2;
long3 = long3 | long3;
long4 = long4 | long4;
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = long8 | long8;
#endif
uint64_t = uint64_t | uint64_t;
uint64_t = uint64_t | uint64_t(k);
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
int8_t = int8_t + int8_t;
int8_t = int8_t + int8_t(k);
char2 = char2 + char2;
char2 = char2 + char2(k);
char3 = char3 + char3;
char3 = char3 + char3(k);
char4 = char4 + char4;
char4 = char4 + char4(k);
char8 = char8 + char8;
char8 = char8 + char8(k);
char16 = char16 + char16;
char16 = char16 + char16(k);
char32 = char32 + char32;
char32 = char32 + char32(k);
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = char64 + char64;
char64 = char64 + char64(k);
#endif
uint8_t = uint8_t + uint8_t;
uint8_t = uint8_t + uint8_t(k);
uchar2 = uchar2 + uchar2;
uchar2 = uchar2 + uchar2(k);
uchar3 = uchar3 + uchar3;
uchar3 = uchar3 + uchar3(k);
uchar4 = uchar4 + uchar4;
uchar4 = uchar4 + uchar4(k);
uchar8 = uchar8 + uchar8;
uchar8 = uchar8 + uchar8(k);
uchar16 = uchar16 + uchar16;
uchar16 = uchar16 + uchar16(k);
uchar32 = uchar32 + uchar32;
uchar32 = uchar32 + uchar32(k);
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = uchar64 + uchar64;
uchar64 = uchar64 + uchar64(k);
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
int16_t = int16_t + int16_t;
int16_t = int16_t + int16_t(k);
short2 = short2 + short2;
short2 = short2 + short2(k);
short3 = short3 + short3;
short3 = short3 + short3(k);
short4 = short4 + short4;
short4 = short4 + short4(k);
short8 = short8 + short8;
short8 = short8 + short8(k);
short16 = short16 + short16;
short16 = short16 + short16(k);
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = short32 + short32;
short32 = short32 + short32(k);
#endif
uint16_t = uint16_t + uint16_t;
uint16_t = uint16_t + uint16_t(k);
ushort2 = ushort2 + ushort2;
ushort2 = ushort2 + ushort2(k);
ushort3 = ushort3 + ushort3;
ushort3 = ushort3 + ushort3(k);
ushort4 = ushort4 + ushort4;
ushort4 = ushort4 + ushort4(k);
ushort8 = ushort8 + ushort8;
ushort8 = ushort8 + ushort8(k);
ushort16 = ushort16 + ushort16;
ushort16 = ushort16 + ushort16(k);
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = ushort32 + ushort32;
ushort32 = ushort32 + ushort32(k);
#endif
cshort = cshort + cshort;
cshort2 = cshort2 + cshort2;
cshort4 = cshort4 + cshort4;
cshort8 = cshort8 + cshort8;
#if __C7X_VEC_SIZE_BITS__ == 512
cshort16 = cshort16 + cshort16;
#endif

ADDW, VADDW
int32_t = int32_t + int32_t;
int32_t = int32_t + int32_t(k);
int2 = int2 + int2;
int2 = int2 + int2(k);
int3 = int3 + int3;
int3 = int3 + int3(k);
int4 = int4 + int4;
int4 = int4 + int4(k);
int8 = int8 + int8;
int8 = int8 + int8(k);
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = int16 + int16;
int16 = int16 + int16(k);
#endif
uint32_t = uint32_t + uint32_t;
uint32_t = uint32_t + uint32_t(k);
uint2 = uint2 + uint2;
uint2 = uint2 + uint2(k);
uint3 = uint3 + uint3;
uint3 = uint3 + uint3(k);
uint4 = uint4 + uint4;
uint4 = uint4 + uint4(k);
uint8 = uint8 + uint8;
uint8 = uint8 + uint8(k);
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = uint16 + uint16;
uint16 = uint16 + uint16(k);
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
int64_t = int64_t + int64_t;
int64_t = int64_t + int64_t(k);
long2 = long2 + long2;
long2 = long2 + long2(k);
long3 = long3 + long3;
long3 = long3 + long3(k);
long4 = long4 + long4;
long4 = long4 + long4(k);
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = long8 + long8;
long8 = long8 + long8(k);
#endif
uint64_t = uint64_t + uint64_t;
uint64_t = uint64_t + uint64_t(k);
ulong2 = ulong2 + ulong2;
ulong2 = ulong2 + ulong2(k);
ulong3 = ulong3 + ulong3;
ulong3 = ulong3 + ulong3(k);
ulong4 = ulong4 + ulong4;
ulong4 = ulong4 + ulong4(k);
#if __C7X_VEC_SIZE_BITS__ == 512
ulong8 = ulong8 + ulong8;
ulong8 = ulong8 + ulong8(k);
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
int8_t = int8_t << int8_t(k={0-63});
char2 = char2 << char2(k={0-63});
char3 = char3 << char3(k={0-63});
char4 = char4 << char4(k={0-63});
char8 = char8 << char8(k={0-63});
char16 = char16 << char16(k={0-63});
char32 = char32 << char32(k={0-63});
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = char64 << char64(k={0-63});
#endif
uint8_t = uint8_t << uint8_t(k={0-63});
uchar2 = uchar2 << uchar2(k={0-63});
uchar3 = uchar3 << uchar3(k={0-63});
uchar4 = uchar4 << uchar4(k={0-63});
uchar8 = uchar8 << uchar8(k={0-63});
uchar16 = uchar16 << uchar16(k={0-63});
uchar32 = uchar32 << uchar32(k={0-63});
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = uchar64 << uchar64(k={0-63});
#endif

VSHLH
int16_t = int16_t << int16_t(k={0-63});
short2 = short2 << short2(k={0-63});
short3 = short3 << short3(k={0-63});
short4 = short4 << short4(k={0-63});
short8 = short8 << short8(k={0-63});
short16 = short16 << short16(k={0-63});
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = short32 << short32(k={0-63});
#endif
uint16_t = uint16_t << uint16_t(k={0-63});
ushort2 = ushort2 << ushort2(k={0-63});
ushort3 = ushort3 << ushort3(k={0-63});
ushort4 = ushort4 << ushort4(k={0-63});
ushort8 = ushort8 << ushort8(k={0-63});
ushort16 = ushort16 << ushort16(k={0-63});
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = ushort32 << ushort32(k={0-63});
#endif

SHLW
int32_t = int32_t << uint8_t(k={0-63});

SHLW, VSHLW
int32_t = int32_t << int32_t;
int32_t = int32_t << int32_t(k);
int2 = int2 << int2;
int2 = int2 << int2(k);
int3 = int3 << int3;
int3 = int3 << int3(k);
int4 = int4 << int4;
int4 = int4 << int4(k);
int8 = int8 << int8;
int8 = int8 << int8(k);
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = int16 << int16;
int16 = int16 << int16(k);
#endif

SHLW
uint32_t = uint32_t << uint8_t(k={0-63});

SHLW, VSHLW
uint32_t = uint32_t << uint32_t;
uint32_t = uint32_t << uint32_t(k);
uint2 = uint2 << uint2;
uint2 = uint2 << uint2(k);
uint3 = uint3 << uint3;
uint3 = uint3 << uint3(k);
uint4 = uint4 << uint4;
uint4 = uint4 << uint4(k);
uint8 = uint8 << uint8;
uint8 = uint8 << uint8(k);
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = uint16 << uint16;
uint16 = uint16 << uint16(k);
#endif

SHLD
int64_t = int64_t << uint8_t(k={0-63});
int64_t = int64_t << int32_t;

VSHLD
int64_t = int64_t << int64_t;
int64_t = int64_t << int64_t(k);
long2 = long2 << long2;
long2 = long2 << long2(k);
long3 = long3 << long3;
long3 = long3 << long3(k);
long4 = long4 << long4;
long4 = long4 << long4(k);
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = long8 << long8;
long8 = long8 << long8(k);
#endif

SHLD
uint64_t = uint64_t << uint8_t(k={0-63});
uint64_t = uint64_t << uint32_t;

VSHLD
uint64_t = uint64_t << uint64_t;
uint64_t = uint64_t << uint64_t(k);
ulong2 = ulong2 << ulong2;
ulong2 = ulong2 << ulong2(k);
ulong3 = ulong3 << ulong3;
ulong3 = ulong3 << ulong3(k);
ulong4 = ulong4 << ulong4;
ulong4 = ulong4 << ulong4(k);
#if __C7X_VEC_SIZE_BITS__ == 512
ulong8 = ulong8 << ulong8;
ulong8 = ulong8 << ulong8(k);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: SRL                                                                    */
/*----------------------------------------------------------------------------*/
/*

SHRW
int32_t = int32_t >> uint8_t(k={0-63});

SHRW, VSHRW
int32_t = int32_t >> int32_t;
int32_t = int32_t >> int32_t(k);
int2 = int2 >> int2;
int2 = int2 >> int2(k);
int3 = int3 >> int3;
int3 = int3 >> int3(k);
int4 = int4 >> int4;
int4 = int4 >> int4(k);
int8 = int8 >> int8;
int8 = int8 >> int8(k);
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = int16 >> int16;
int16 = int16 >> int16(k);
#endif

SHRUW
uint32_t = uint32_t >> uint8_t(k={0-63});

SHRUW, VSHRUW
uint32_t = uint32_t >> uint32_t;
uint32_t = uint32_t >> uint32_t(k);
uint2 = uint2 >> uint2;
uint2 = uint2 >> uint2(k);
uint3 = uint3 >> uint3;
uint3 = uint3 >> uint3(k);
uint4 = uint4 >> uint4;
uint4 = uint4 >> uint4(k);
uint8 = uint8 >> uint8;
uint8 = uint8 >> uint8(k);
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = uint16 >> uint16;
uint16 = uint16 >> uint16(k);
#endif

SHRD
int64_t = int64_t >> uint8_t(k={0-63});
int64_t = int64_t >> int32_t;

VSHRD
int64_t = int64_t >> int64_t;
int64_t = int64_t >> int64_t(k);
long2 = long2 >> long2;
long2 = long2 >> long2(k);
long3 = long3 >> long3;
long3 = long3 >> long3(k);
long4 = long4 >> long4;
long4 = long4 >> long4(k);
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = long8 >> long8;
long8 = long8 >> long8(k);
#endif

SHRUD
uint64_t = uint64_t >> uint8_t(k={0-63});
uint64_t = uint64_t >> uint32_t;

VSHRUD
uint64_t = uint64_t >> uint64_t;
uint64_t = uint64_t >> uint64_t(k);
ulong2 = ulong2 >> ulong2;
ulong2 = ulong2 >> ulong2(k);
ulong3 = ulong3 >> ulong3;
ulong3 = ulong3 >> ulong3(k);
ulong4 = ulong4 >> ulong4;
ulong4 = ulong4 >> ulong4(k);
#if __C7X_VEC_SIZE_BITS__ == 512
ulong8 = ulong8 >> ulong8;
ulong8 = ulong8 >> ulong8(k);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: XORB                                                                   */
/*----------------------------------------------------------------------------*/
/*

VXORW, XORD, XORW
int8_t = int8_t ^ int8_t;
int8_t = int8_t ^ int8_t(k);
char2 = char2 ^ char2;
char2 = char2 ^ char2(k);
char3 = char3 ^ char3;
char3 = char3 ^ char3(k);
char4 = char4 ^ char4;
char4 = char4 ^ char4(k);
char8 = char8 ^ char8;
char16 = char16 ^ char16;
char32 = char32 ^ char32;
#if __C7X_VEC_SIZE_BITS__ == 512
char64 = char64 ^ char64;
#endif
uint8_t = uint8_t ^ uint8_t;
uint8_t = uint8_t ^ uint8_t(k);
uchar2 = uchar2 ^ uchar2;
uchar2 = uchar2 ^ uchar2(k);
uchar3 = uchar3 ^ uchar3;
uchar3 = uchar3 ^ uchar3(k);
uchar4 = uchar4 ^ uchar4;
uchar4 = uchar4 ^ uchar4(k);
uchar8 = uchar8 ^ uchar8;
uchar16 = uchar16 ^ uchar16;
uchar32 = uchar32 ^ uchar32;
#if __C7X_VEC_SIZE_BITS__ == 512
uchar64 = uchar64 ^ uchar64;
#endif
int16_t = int16_t ^ int16_t;
int16_t = int16_t ^ int16_t(k);
short2 = short2 ^ short2;
short2 = short2 ^ short2(k);
short3 = short3 ^ short3;
short4 = short4 ^ short4;
short8 = short8 ^ short8;
short16 = short16 ^ short16;
#if __C7X_VEC_SIZE_BITS__ == 512
short32 = short32 ^ short32;
#endif
uint16_t = uint16_t ^ uint16_t;
uint16_t = uint16_t ^ uint16_t(k);
ushort2 = ushort2 ^ ushort2;
ushort2 = ushort2 ^ ushort2(k);
ushort3 = ushort3 ^ ushort3;
ushort4 = ushort4 ^ ushort4;
ushort8 = ushort8 ^ ushort8;
ushort16 = ushort16 ^ ushort16;
#if __C7X_VEC_SIZE_BITS__ == 512
ushort32 = ushort32 ^ ushort32;
#endif
int32_t = int32_t ^ int32_t;
int32_t = int32_t ^ int32_t(k);
int2 = int2 ^ int2;
int2 = int2 ^ int2(k);
int3 = int3 ^ int3;
int3 = int3 ^ int3(k);
int4 = int4 ^ int4;
int4 = int4 ^ int4(k);
int8 = int8 ^ int8;
int8 = int8 ^ int8(k);
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = int16 ^ int16;
int16 = int16 ^ int16(k);
#endif
uint32_t = uint32_t ^ uint32_t;
uint32_t = uint32_t ^ uint32_t(k);
uint2 = uint2 ^ uint2;
uint2 = uint2 ^ uint2(k);
uint3 = uint3 ^ uint3;
uint3 = uint3 ^ uint3(k);
uint4 = uint4 ^ uint4;
uint4 = uint4 ^ uint4(k);
uint8 = uint8 ^ uint8;
uint8 = uint8 ^ uint8(k);
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = uint16 ^ uint16;
uint16 = uint16 ^ uint16(k);
#endif

VXORW, XORD
int64_t = int64_t ^ int64_t;
int64_t = int64_t ^ int64_t(k);
long2 = long2 ^ long2;
long3 = long3 ^ long3;
long4 = long4 ^ long4;
#if __C7X_VEC_SIZE_BITS__ == 512
long8 = long8 ^ long8;
#endif
uint64_t = uint64_t ^ uint64_t;
uint64_t = uint64_t ^ uint64_t(k);
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

/* VABSB */
extern int8_t __abs(int8_t);
extern char2 __abs(char2);
extern char3 __abs(char3);
extern char4 __abs(char4);
extern char8 __abs(char8);
extern char16 __abs(char16);
extern char32 __abs(char32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __abs(char64);
#endif
extern cchar __abs(cchar);
extern cchar2 __abs(cchar2);
extern cchar4 __abs(cchar4);
extern cchar8 __abs(cchar8);
extern cchar16 __abs(cchar16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern cchar32 __abs(cchar32);
#endif

/* VABSH */
extern int16_t __abs(int16_t);
extern short2 __abs(short2);
extern short3 __abs(short3);
extern short4 __abs(short4);
extern short8 __abs(short8);
extern short16 __abs(short16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __abs(short32);
#endif
extern cshort __abs(cshort);
extern cshort2 __abs(cshort2);
extern cshort4 __abs(cshort4);
extern cshort8 __abs(cshort8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern cshort16 __abs(cshort16);
#endif

/* VABSW */
extern int32_t __abs(int32_t);
extern int2 __abs(int2);
extern int3 __abs(int3);
extern int4 __abs(int4);
extern int8 __abs(int8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __abs(int16);
#endif

/* VABSSP */
extern float __abs(float);
extern float2 __abs(float2);
extern float3 __abs(float3);
extern float4 __abs(float4);
extern float8 __abs(float8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern float16 __abs(float16);
#endif

/* VABSW */
extern cint __abs(cint);
extern cint2 __abs(cint2);
extern cint4 __abs(cint4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern cint8 __abs(cint8);
#endif

/* VABSSP */
extern cfloat __abs(cfloat);
extern cfloat2 __abs(cfloat2);
extern cfloat4 __abs(cfloat4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern cfloat8 __abs(cfloat8);
#endif

/* VABSD */
extern int64_t __abs(int64_t);
extern long2 __abs(long2);
extern long3 __abs(long3);
extern long4 __abs(long4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __abs(long8);
#endif

/* VABSDP */
extern double __abs(double);
extern double2 __abs(double2);
extern double3 __abs(double3);
extern double4 __abs(double4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern double8 __abs(double8);
#endif

/* VABSD */
extern clong __abs(clong);
extern clong2 __abs(clong2);
#if __C7X_VEC_SIZE_BITS__ == 512
extern clong4 __abs(clong4);
#endif

/* VABSDP */
extern cdouble __abs(cdouble);
extern cdouble2 __abs(cdouble2);
#if __C7X_VEC_SIZE_BITS__ == 512
extern cdouble4 __abs(cdouble4);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __abs_diff                                                             */
/*----------------------------------------------------------------------------*/

/* VSUBABSB */
extern uint8_t __abs_diff(uint8_t, uint8_t);
extern uchar2 __abs_diff(uchar2, uchar2);
extern uchar3 __abs_diff(uchar3, uchar3);
extern uchar4 __abs_diff(uchar4, uchar4);
extern uchar8 __abs_diff(uchar8, uchar8);
extern uchar16 __abs_diff(uchar16, uchar16);
extern uchar32 __abs_diff(uchar32, uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __abs_diff(uchar64, uchar64);
#endif

/* VSUBABSH */
extern uint16_t __abs_diff(uint16_t, uint16_t);
extern ushort2 __abs_diff(ushort2, ushort2);
extern ushort3 __abs_diff(ushort3, ushort3);
extern ushort4 __abs_diff(ushort4, ushort4);
extern ushort8 __abs_diff(ushort8, ushort8);
extern ushort16 __abs_diff(ushort16, ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __abs_diff(ushort32, ushort32);
#endif

/* VSUBABSW */
extern uint32_t __abs_diff(uint32_t, uint32_t);
extern uint2 __abs_diff(uint2, uint2);
extern uint3 __abs_diff(uint3, uint3);
extern uint4 __abs_diff(uint4, uint4);
extern uint8 __abs_diff(uint8, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __abs_diff(uint16, uint16);
#endif

/* VSUBABSD */
extern uint64_t __abs_diff(uint64_t, uint64_t);
extern ulong2 __abs_diff(ulong2, ulong2);
extern ulong3 __abs_diff(ulong3, ulong3);
extern ulong4 __abs_diff(ulong4, ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __abs_diff(ulong8, ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __add                                                                  */
/*----------------------------------------------------------------------------*/

/* VADDCB */
extern char2 __add(bool2, char2, char2);
extern char3 __add(bool3, char3, char3);
extern char4 __add(bool4, char4, char4);
extern char8 __add(bool8, char8, char8);
extern char16 __add(bool16, char16, char16);
extern char32 __add(bool32, char32, char32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __add(bool64, char64, char64);
#endif
extern uchar2 __add(bool2, uchar2, uchar2);
extern uchar3 __add(bool3, uchar3, uchar3);
extern uchar4 __add(bool4, uchar4, uchar4);
extern uchar8 __add(bool8, uchar8, uchar8);
extern uchar16 __add(bool16, uchar16, uchar16);
extern uchar32 __add(bool32, uchar32, uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __add(bool64, uchar64, uchar64);
#endif

/* VADDCH */
extern short2 __add(bool2, short2, short2);
extern short3 __add(bool3, short3, short3);
extern short4 __add(bool4, short4, short4);
extern short8 __add(bool8, short8, short8);
extern short16 __add(bool16, short16, short16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __add(bool32, short32, short32);
#endif
extern ushort2 __add(bool2, ushort2, ushort2);
extern ushort3 __add(bool3, ushort3, ushort3);
extern ushort4 __add(bool4, ushort4, ushort4);
extern ushort8 __add(bool8, ushort8, ushort8);
extern ushort16 __add(bool16, ushort16, ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __add(bool32, ushort32, ushort32);
#endif

/* VADDCW */
extern int2 __add(bool2, int2, int2);
extern int3 __add(bool3, int3, int3);
extern int4 __add(bool4, int4, int4);
extern int8 __add(bool8, int8, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __add(bool16, int16, int16);
#endif
extern uint2 __add(bool2, uint2, uint2);
extern uint3 __add(bool3, uint3, uint3);
extern uint4 __add(bool4, uint4, uint4);
extern uint8 __add(bool8, uint8, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __add(bool16, uint16, uint16);
#endif

/* VADDCD */
extern long2 __add(bool2, long2, long2);
extern long3 __add(bool3, long3, long3);
extern long4 __add(bool4, long4, long4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __add(bool8, long8, long8);
#endif
extern ulong2 __add(bool2, ulong2, ulong2);
extern ulong3 __add(bool3, ulong3, ulong3);
extern ulong4 __add(bool4, ulong4, ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __add(bool8, ulong8, ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __add_sat                                                              */
/*----------------------------------------------------------------------------*/

/* VSADDB */
extern int8_t __add_sat(int8_t, int8_t);
/* int8_t __add_sat(int8_t, int8_t(k)); */
extern char2 __add_sat(char2, char2);
/* char2 __add_sat(char2, char2(k)); */
extern char3 __add_sat(char3, char3);
/* char3 __add_sat(char3, char3(k)); */
extern char4 __add_sat(char4, char4);
/* char4 __add_sat(char4, char4(k)); */
extern char8 __add_sat(char8, char8);
/* char8 __add_sat(char8, char8(k)); */
extern char16 __add_sat(char16, char16);
/* char16 __add_sat(char16, char16(k)); */
extern char32 __add_sat(char32, char32);
/* char32 __add_sat(char32, char32(k)); */
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __add_sat(char64, char64);
/* char64 __add_sat(char64, char64(k)); */
#endif

/* VSADDUSB */
extern uint8_t __add_sat(uint8_t, int8_t);
extern uchar2 __add_sat(uchar2, char2);
extern uchar3 __add_sat(uchar3, char3);
extern uchar4 __add_sat(uchar4, char4);
extern uchar8 __add_sat(uchar8, char8);
extern uchar16 __add_sat(uchar16, char16);
extern uchar32 __add_sat(uchar32, char32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __add_sat(uchar64, char64);
#endif

/* VSADDUB */
extern uint8_t __add_sat(uint8_t, uint8_t);
extern uchar2 __add_sat(uchar2, uchar2);
extern uchar3 __add_sat(uchar3, uchar3);
extern uchar4 __add_sat(uchar4, uchar4);
extern uchar8 __add_sat(uchar8, uchar8);
extern uchar16 __add_sat(uchar16, uchar16);
extern uchar32 __add_sat(uchar32, uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __add_sat(uchar64, uchar64);
#endif

/* VSADDB */
extern cchar __add_sat(cchar, cchar);
extern cchar2 __add_sat(cchar2, cchar2);
extern cchar4 __add_sat(cchar4, cchar4);
extern cchar8 __add_sat(cchar8, cchar8);
extern cchar16 __add_sat(cchar16, cchar16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern cchar32 __add_sat(cchar32, cchar32);
#endif

/* VSADDH */
extern int16_t __add_sat(int16_t, int16_t);
/* int16_t __add_sat(int16_t, int16_t(k)); */
extern short2 __add_sat(short2, short2);
/* short2 __add_sat(short2, short2(k)); */
extern short3 __add_sat(short3, short3);
/* short3 __add_sat(short3, short3(k)); */
extern short4 __add_sat(short4, short4);
/* short4 __add_sat(short4, short4(k)); */
extern short8 __add_sat(short8, short8);
/* short8 __add_sat(short8, short8(k)); */
extern short16 __add_sat(short16, short16);
/* short16 __add_sat(short16, short16(k)); */
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __add_sat(short32, short32);
/* short32 __add_sat(short32, short32(k)); */
#endif

/* VSADDUSH */
extern uint16_t __add_sat(uint16_t, int16_t);
extern ushort2 __add_sat(ushort2, short2);
extern ushort3 __add_sat(ushort3, short3);
extern ushort4 __add_sat(ushort4, short4);
extern ushort8 __add_sat(ushort8, short8);
extern ushort16 __add_sat(ushort16, short16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __add_sat(ushort32, short32);
#endif

/* VSADDUH */
extern uint16_t __add_sat(uint16_t, uint16_t);
extern ushort2 __add_sat(ushort2, ushort2);
extern ushort3 __add_sat(ushort3, ushort3);
extern ushort4 __add_sat(ushort4, ushort4);
extern ushort8 __add_sat(ushort8, ushort8);
extern ushort16 __add_sat(ushort16, ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __add_sat(ushort32, ushort32);
#endif

/* VSADDH */
extern cshort __add_sat(cshort, cshort);
extern cshort2 __add_sat(cshort2, cshort2);
extern cshort4 __add_sat(cshort4, cshort4);
extern cshort8 __add_sat(cshort8, cshort8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern cshort16 __add_sat(cshort16, cshort16);
#endif

/* VSADDW */
extern int32_t __add_sat(int32_t, int32_t);
/* int32_t __add_sat(int32_t, int32_t(k)); */
extern int2 __add_sat(int2, int2);
/* int2 __add_sat(int2, int2(k)); */
extern int3 __add_sat(int3, int3);
/* int3 __add_sat(int3, int3(k)); */
extern int4 __add_sat(int4, int4);
/* int4 __add_sat(int4, int4(k)); */
extern int8 __add_sat(int8, int8);
/* int8 __add_sat(int8, int8(k)); */
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __add_sat(int16, int16);
/* int16 __add_sat(int16, int16(k)); */
#endif

/* VSADDUSW */
extern uint32_t __add_sat(uint32_t, int32_t);
extern uint2 __add_sat(uint2, int2);
extern uint3 __add_sat(uint3, int3);
extern uint4 __add_sat(uint4, int4);
extern uint8 __add_sat(uint8, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __add_sat(uint16, int16);
#endif

/* VSADDUW */
extern uint32_t __add_sat(uint32_t, uint32_t);
extern uint2 __add_sat(uint2, uint2);
extern uint3 __add_sat(uint3, uint3);
extern uint4 __add_sat(uint4, uint4);
extern uint8 __add_sat(uint8, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __add_sat(uint16, uint16);
#endif

/* VSADDW */
extern cint __add_sat(cint, cint);
extern cint2 __add_sat(cint2, cint2);
extern cint4 __add_sat(cint4, cint4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern cint8 __add_sat(cint8, cint8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __and                                                                  */
/*----------------------------------------------------------------------------*/

/* AND */
extern bool2 __and(bool2, bool2);
extern bool3 __and(bool3, bool3);
extern bool4 __and(bool4, bool4);
extern bool8 __and(bool8, bool8);
extern bool16 __and(bool16, bool16);
extern bool32 __and(bool32, bool32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern bool64 __and(bool64, bool64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __andn                                                                 */
/*----------------------------------------------------------------------------*/

/* ANDND, ANDNW, VANDNW */
extern int8_t __andn(int8_t, int8_t);
/* int8_t __andn(int8_t, int8_t(k)); */
extern char2 __andn(char2, char2);
/* char2 __andn(char2, char2(k)); */
extern char3 __andn(char3, char3);
/* char3 __andn(char3, char3(k)); */
extern char4 __andn(char4, char4);
/* char4 __andn(char4, char4(k)); */
extern char8 __andn(char8, char8);
extern char16 __andn(char16, char16);
extern char32 __andn(char32, char32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __andn(char64, char64);
#endif
extern uint8_t __andn(uint8_t, uint8_t);
/* uint8_t __andn(uint8_t, uint8_t(k)); */
extern uchar2 __andn(uchar2, uchar2);
/* uchar2 __andn(uchar2, uchar2(k)); */
extern uchar3 __andn(uchar3, uchar3);
/* uchar3 __andn(uchar3, uchar3(k)); */
extern uchar4 __andn(uchar4, uchar4);
/* uchar4 __andn(uchar4, uchar4(k)); */
extern uchar8 __andn(uchar8, uchar8);
extern uchar16 __andn(uchar16, uchar16);
extern uchar32 __andn(uchar32, uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __andn(uchar64, uchar64);
#endif
extern int16_t __andn(int16_t, int16_t);
/* int16_t __andn(int16_t, int16_t(k)); */
extern short2 __andn(short2, short2);
/* short2 __andn(short2, short2(k)); */
extern short3 __andn(short3, short3);
extern short4 __andn(short4, short4);
extern short8 __andn(short8, short8);
extern short16 __andn(short16, short16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __andn(short32, short32);
#endif
extern uint16_t __andn(uint16_t, uint16_t);
/* uint16_t __andn(uint16_t, uint16_t(k)); */
extern ushort2 __andn(ushort2, ushort2);
/* ushort2 __andn(ushort2, ushort2(k)); */
extern ushort3 __andn(ushort3, ushort3);
extern ushort4 __andn(ushort4, ushort4);
extern ushort8 __andn(ushort8, ushort8);
extern ushort16 __andn(ushort16, ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __andn(ushort32, ushort32);
#endif
extern int32_t __andn(int32_t, int32_t);
/* int32_t __andn(int32_t, int32_t(k)); */
extern int2 __andn(int2, int2);
/* int2 __andn(int2, int2(k)); */
extern int3 __andn(int3, int3);
/* int3 __andn(int3, int3(k)); */
extern int4 __andn(int4, int4);
/* int4 __andn(int4, int4(k)); */
extern int8 __andn(int8, int8);
/* int8 __andn(int8, int8(k)); */
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __andn(int16, int16);
/* int16 __andn(int16, int16(k)); */
#endif
extern uint32_t __andn(uint32_t, uint32_t);
/* uint32_t __andn(uint32_t, uint32_t(k)); */
extern uint2 __andn(uint2, uint2);
/* uint2 __andn(uint2, uint2(k)); */
extern uint3 __andn(uint3, uint3);
/* uint3 __andn(uint3, uint3(k)); */
extern uint4 __andn(uint4, uint4);
/* uint4 __andn(uint4, uint4(k)); */
extern uint8 __andn(uint8, uint8);
/* uint8 __andn(uint8, uint8(k)); */
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __andn(uint16, uint16);
/* uint16 __andn(uint16, uint16(k)); */
#endif

/* ANDND, VANDNW */
extern int64_t __andn(int64_t, int64_t);
/* int64_t __andn(int64_t, int64_t(k)); */
extern long2 __andn(long2, long2);
extern long3 __andn(long3, long3);
extern long4 __andn(long4, long4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __andn(long8, long8);
#endif
extern uint64_t __andn(uint64_t, uint64_t);
/* uint64_t __andn(uint64_t, uint64_t(k)); */
extern ulong2 __andn(ulong2, ulong2);
extern ulong3 __andn(ulong3, ulong3);
extern ulong4 __andn(ulong4, ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __andn(ulong8, ulong8);
#endif

/* ANDN */
extern bool2 __andn(bool2, bool2);
extern bool3 __andn(bool3, bool3);
extern bool4 __andn(bool4, bool4);
extern bool8 __andn(bool8, bool8);
extern bool16 __andn(bool16, bool16);
extern bool32 __andn(bool32, bool32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern bool64 __andn(bool64, bool64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __apply_sign                                                           */
/*----------------------------------------------------------------------------*/

/* VAPYSB */
extern int8_t __apply_sign(int8_t, int8_t);
extern char2 __apply_sign(char2, char2);
extern char3 __apply_sign(char3, char3);
extern char4 __apply_sign(char4, char4);
extern char8 __apply_sign(char8, char8);
extern char16 __apply_sign(char16, char16);
extern char32 __apply_sign(char32, char32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __apply_sign(char64, char64);
#endif

/* VAPYSH */
extern int16_t __apply_sign(int16_t, int16_t);
extern short2 __apply_sign(short2, short2);
extern short3 __apply_sign(short3, short3);
extern short4 __apply_sign(short4, short4);
extern short8 __apply_sign(short8, short8);
extern short16 __apply_sign(short16, short16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __apply_sign(short32, short32);
#endif

/* VAPYSW */
extern int32_t __apply_sign(int32_t, int32_t);
extern int2 __apply_sign(int2, int2);
extern int3 __apply_sign(int3, int3);
extern int4 __apply_sign(int4, int4);
extern int8 __apply_sign(int8, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __apply_sign(int16, int16);
#endif

/* VAPYSD */
extern int64_t __apply_sign(int64_t, int64_t);
extern long2 __apply_sign(long2, long2);
extern long3 __apply_sign(long3, long3);
extern long4 __apply_sign(long4, long4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __apply_sign(long8, long8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __binary_log                                                           */
/*----------------------------------------------------------------------------*/

/* VBINLOGW */
extern uint32_t __binary_log(uint32_t);
extern uint2 __binary_log(uint2);
extern uint3 __binary_log(uint3);
extern uint4 __binary_log(uint4);
extern uint8 __binary_log(uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __binary_log(uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __bit_reverse                                                          */
/*----------------------------------------------------------------------------*/

/* VBITRW */
extern int32_t __bit_reverse(int32_t);
extern int2 __bit_reverse(int2);
extern int3 __bit_reverse(int3);
extern int4 __bit_reverse(int4);
extern int8 __bit_reverse(int8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __bit_reverse(int16);
#endif
extern uint32_t __bit_reverse(uint32_t);
extern uint2 __bit_reverse(uint2);
extern uint3 __bit_reverse(uint3);
extern uint4 __bit_reverse(uint4);
extern uint8 __bit_reverse(uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __bit_reverse(uint16);
#endif

/* VBITRD */
extern int64_t __bit_reverse(int64_t);
extern long2 __bit_reverse(long2);
extern long3 __bit_reverse(long3);
extern long4 __bit_reverse(long4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __bit_reverse(long8);
#endif
extern uint64_t __bit_reverse(uint64_t);
extern ulong2 __bit_reverse(ulong2);
extern ulong3 __bit_reverse(ulong3);
extern ulong4 __bit_reverse(ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __bit_reverse(ulong8);
#endif

/* BITR */
#if __C7X_VEC_SIZE_BITS__ == 256
extern bool32 __bit_reverse(bool32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern bool64 __bit_reverse(bool64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __bit_transpose                                                        */
/*----------------------------------------------------------------------------*/

/* VBITTRAN8B */
extern uchar8 __bit_transpose(uchar8);
extern uchar16 __bit_transpose(uchar16);
extern uchar32 __bit_transpose(uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __bit_transpose(uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __classify                                                             */
/*----------------------------------------------------------------------------*/

/* VCLASSSP */
extern int32_t __classify(float);
extern int2 __classify(float2);
extern int3 __classify(float3);
extern int4 __classify(float4);
extern int8 __classify(float8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __classify(float16);
#endif

/* VCLASSDP */
extern int64_t __classify(double);
extern long2 __classify(double2);
extern long3 __classify(double3);
extern long4 __classify(double4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __classify(double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __clear                                                                */
/*----------------------------------------------------------------------------*/

/* CLR */
extern uint32_t __clear(uint32_t, uint32_t);

/*----------------------------------------------------------------------------*/
/* ID: __cmatmpy_ext                                                          */
/*----------------------------------------------------------------------------*/

/* VCMATMPYHW */
extern cint2 __cmatmpy_ext(cshort2, cshort4);
extern cint4 __cmatmpy_ext(cshort4, cshort8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern cint8 __cmatmpy_ext(cshort8, cshort16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __cmatmpy_fx                                                           */
/*----------------------------------------------------------------------------*/

/* VCMATMPYR1HH */
extern cshort2 __cmatmpy_fx(cshort2, cshort4);
extern cshort4 __cmatmpy_fx(cshort4, cshort8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern cshort8 __cmatmpy_fx(cshort8, cshort16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __cmp_eq                                                               */
/*----------------------------------------------------------------------------*/

/* CMPEQW */
extern int32_t __cmp_eq(int32_t, int32_t);
/* int32_t __cmp_eq(int32_t, int32_t(k)); */

/* CMPEQSP */
extern int32_t __cmp_eq(float, float);

/* CMPEQD */
extern int32_t __cmp_eq(int64_t, int32_t/*(k)*/);
extern int32_t __cmp_eq(int64_t, int64_t);

/* CMPEQDP */
extern int32_t __cmp_eq(double, double);

/*----------------------------------------------------------------------------*/
/* ID: __cmp_eq_bool                                                          */
/*----------------------------------------------------------------------------*/

/* VCMPEQB */
extern bool2 __cmp_eq_bool(char2, char2);
extern bool3 __cmp_eq_bool(char3, char3);
extern bool4 __cmp_eq_bool(char4, char4);
extern bool8 __cmp_eq_bool(char8, char8);
extern bool16 __cmp_eq_bool(char16, char16);
extern bool32 __cmp_eq_bool(char32, char32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern bool64 __cmp_eq_bool(char64, char64);
#endif
extern bool2 __cmp_eq_bool(uchar2, uchar2);
extern bool3 __cmp_eq_bool(uchar3, uchar3);
extern bool4 __cmp_eq_bool(uchar4, uchar4);
extern bool8 __cmp_eq_bool(uchar8, uchar8);
extern bool16 __cmp_eq_bool(uchar16, uchar16);
extern bool32 __cmp_eq_bool(uchar32, uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern bool64 __cmp_eq_bool(uchar64, uchar64);
#endif

/* VCMPEQH */
extern bool2 __cmp_eq_bool(short2, short2);
extern bool3 __cmp_eq_bool(short3, short3);
extern bool4 __cmp_eq_bool(short4, short4);
extern bool8 __cmp_eq_bool(short8, short8);
extern bool16 __cmp_eq_bool(short16, short16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern bool32 __cmp_eq_bool(short32, short32);
#endif
extern bool2 __cmp_eq_bool(ushort2, ushort2);
extern bool3 __cmp_eq_bool(ushort3, ushort3);
extern bool4 __cmp_eq_bool(ushort4, ushort4);
extern bool8 __cmp_eq_bool(ushort8, ushort8);
extern bool16 __cmp_eq_bool(ushort16, ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern bool32 __cmp_eq_bool(ushort32, ushort32);
#endif

/* VCMPEQW */
extern bool2 __cmp_eq_bool(int2, int2);
extern bool3 __cmp_eq_bool(int3, int3);
extern bool4 __cmp_eq_bool(int4, int4);
extern bool8 __cmp_eq_bool(int8, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern bool16 __cmp_eq_bool(int16, int16);
#endif
extern bool2 __cmp_eq_bool(uint2, uint2);
extern bool3 __cmp_eq_bool(uint3, uint3);
extern bool4 __cmp_eq_bool(uint4, uint4);
extern bool8 __cmp_eq_bool(uint8, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern bool16 __cmp_eq_bool(uint16, uint16);
#endif

/* VCMPEQSP */
extern bool2 __cmp_eq_bool(float2, float2);
extern bool3 __cmp_eq_bool(float3, float3);
extern bool4 __cmp_eq_bool(float4, float4);
extern bool8 __cmp_eq_bool(float8, float8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern bool16 __cmp_eq_bool(float16, float16);
#endif

/* VCMPEQD */
extern bool2 __cmp_eq_bool(long2, long2);
extern bool3 __cmp_eq_bool(long3, long3);
extern bool4 __cmp_eq_bool(long4, long4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern bool8 __cmp_eq_bool(long8, long8);
#endif
extern bool2 __cmp_eq_bool(ulong2, ulong2);
extern bool3 __cmp_eq_bool(ulong3, ulong3);
extern bool4 __cmp_eq_bool(ulong4, ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern bool8 __cmp_eq_bool(ulong8, ulong8);
#endif

/* VCMPEQDP */
extern bool2 __cmp_eq_bool(double2, double2);
extern bool3 __cmp_eq_bool(double3, double3);
extern bool4 __cmp_eq_bool(double4, double4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern bool8 __cmp_eq_bool(double8, double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __cmp_ge                                                               */
/*----------------------------------------------------------------------------*/

/* CMPGEW */
extern int32_t __cmp_ge(int32_t, int32_t);
/* int32_t __cmp_ge(int32_t, int32_t(k)); */

/* CMPGEUW */
extern int32_t __cmp_ge(uint32_t, uint32_t);
/* int32_t __cmp_ge(uint32_t, uint32_t(k)); */

/* CMPGED */
extern int32_t __cmp_ge(int64_t, int32_t/*(k)*/);
extern int32_t __cmp_ge(int64_t, int64_t);

/* CMPGEUD */
extern int32_t __cmp_ge(uint64_t, uint32_t/*(k)*/);
extern int32_t __cmp_ge(uint64_t, uint64_t);

/*----------------------------------------------------------------------------*/
/* ID: __cmp_ge_bool                                                          */
/*----------------------------------------------------------------------------*/

/* VCMPGEB */
extern bool2 __cmp_ge_bool(char2, char2);
extern bool3 __cmp_ge_bool(char3, char3);
extern bool4 __cmp_ge_bool(char4, char4);
extern bool8 __cmp_ge_bool(char8, char8);
extern bool16 __cmp_ge_bool(char16, char16);
extern bool32 __cmp_ge_bool(char32, char32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern bool64 __cmp_ge_bool(char64, char64);
#endif

/* VCMPGEUB */
extern bool2 __cmp_ge_bool(uchar2, uchar2);
extern bool3 __cmp_ge_bool(uchar3, uchar3);
extern bool4 __cmp_ge_bool(uchar4, uchar4);
extern bool8 __cmp_ge_bool(uchar8, uchar8);
extern bool16 __cmp_ge_bool(uchar16, uchar16);
extern bool32 __cmp_ge_bool(uchar32, uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern bool64 __cmp_ge_bool(uchar64, uchar64);
#endif

/* VCMPGEH */
extern bool2 __cmp_ge_bool(short2, short2);
extern bool3 __cmp_ge_bool(short3, short3);
extern bool4 __cmp_ge_bool(short4, short4);
extern bool8 __cmp_ge_bool(short8, short8);
extern bool16 __cmp_ge_bool(short16, short16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern bool32 __cmp_ge_bool(short32, short32);
#endif

/* VCMPGEUH */
extern bool2 __cmp_ge_bool(ushort2, ushort2);
extern bool3 __cmp_ge_bool(ushort3, ushort3);
extern bool4 __cmp_ge_bool(ushort4, ushort4);
extern bool8 __cmp_ge_bool(ushort8, ushort8);
extern bool16 __cmp_ge_bool(ushort16, ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern bool32 __cmp_ge_bool(ushort32, ushort32);
#endif

/* VCMPGEW */
extern bool2 __cmp_ge_bool(int2, int2);
extern bool3 __cmp_ge_bool(int3, int3);
extern bool4 __cmp_ge_bool(int4, int4);
extern bool8 __cmp_ge_bool(int8, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern bool16 __cmp_ge_bool(int16, int16);
#endif

/* VCMPGEUW */
extern bool2 __cmp_ge_bool(uint2, uint2);
extern bool3 __cmp_ge_bool(uint3, uint3);
extern bool4 __cmp_ge_bool(uint4, uint4);
extern bool8 __cmp_ge_bool(uint8, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern bool16 __cmp_ge_bool(uint16, uint16);
#endif

/* VCMPLESP */
extern bool2 __cmp_ge_bool(float2, float2);
extern bool3 __cmp_ge_bool(float3, float3);
extern bool4 __cmp_ge_bool(float4, float4);
extern bool8 __cmp_ge_bool(float8, float8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern bool16 __cmp_ge_bool(float16, float16);
#endif

/* VCMPGED */
extern bool2 __cmp_ge_bool(long2, long2);
extern bool3 __cmp_ge_bool(long3, long3);
extern bool4 __cmp_ge_bool(long4, long4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern bool8 __cmp_ge_bool(long8, long8);
#endif

/* VCMPGEUD */
extern bool2 __cmp_ge_bool(ulong2, ulong2);
extern bool3 __cmp_ge_bool(ulong3, ulong3);
extern bool4 __cmp_ge_bool(ulong4, ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern bool8 __cmp_ge_bool(ulong8, ulong8);
#endif

/* VCMPLEDP */
extern bool2 __cmp_ge_bool(double2, double2);
extern bool3 __cmp_ge_bool(double3, double3);
extern bool4 __cmp_ge_bool(double4, double4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern bool8 __cmp_ge_bool(double8, double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __cmp_gt                                                               */
/*----------------------------------------------------------------------------*/

/* CMPGTW */
extern int32_t __cmp_gt(int32_t, int32_t);
/* int32_t __cmp_gt(int32_t, int32_t(k)); */

/* CMPGTUW */
extern int32_t __cmp_gt(uint32_t, uint32_t);
/* int32_t __cmp_gt(uint32_t, uint32_t(k)); */

/* CMPGTD */
extern int32_t __cmp_gt(int64_t, int32_t/*(k)*/);
extern int32_t __cmp_gt(int64_t, int64_t);

/* CMPGTUD */
extern int32_t __cmp_gt(uint64_t, uint32_t/*(k)*/);
extern int32_t __cmp_gt(uint64_t, uint64_t);

/*----------------------------------------------------------------------------*/
/* ID: __cmp_gt_bool                                                          */
/*----------------------------------------------------------------------------*/

/* VCMPGTB */
extern bool2 __cmp_gt_bool(char2, char2);
extern bool3 __cmp_gt_bool(char3, char3);
extern bool4 __cmp_gt_bool(char4, char4);
extern bool8 __cmp_gt_bool(char8, char8);
extern bool16 __cmp_gt_bool(char16, char16);
extern bool32 __cmp_gt_bool(char32, char32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern bool64 __cmp_gt_bool(char64, char64);
#endif

/* VCMPGTUB */
extern bool2 __cmp_gt_bool(uchar2, uchar2);
extern bool3 __cmp_gt_bool(uchar3, uchar3);
extern bool4 __cmp_gt_bool(uchar4, uchar4);
extern bool8 __cmp_gt_bool(uchar8, uchar8);
extern bool16 __cmp_gt_bool(uchar16, uchar16);
extern bool32 __cmp_gt_bool(uchar32, uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern bool64 __cmp_gt_bool(uchar64, uchar64);
#endif

/* VCMPGTH */
extern bool2 __cmp_gt_bool(short2, short2);
extern bool3 __cmp_gt_bool(short3, short3);
extern bool4 __cmp_gt_bool(short4, short4);
extern bool8 __cmp_gt_bool(short8, short8);
extern bool16 __cmp_gt_bool(short16, short16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern bool32 __cmp_gt_bool(short32, short32);
#endif

/* VCMPGTUH */
extern bool2 __cmp_gt_bool(ushort2, ushort2);
extern bool3 __cmp_gt_bool(ushort3, ushort3);
extern bool4 __cmp_gt_bool(ushort4, ushort4);
extern bool8 __cmp_gt_bool(ushort8, ushort8);
extern bool16 __cmp_gt_bool(ushort16, ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern bool32 __cmp_gt_bool(ushort32, ushort32);
#endif

/* VCMPGTW */
extern bool2 __cmp_gt_bool(int2, int2);
extern bool3 __cmp_gt_bool(int3, int3);
extern bool4 __cmp_gt_bool(int4, int4);
extern bool8 __cmp_gt_bool(int8, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern bool16 __cmp_gt_bool(int16, int16);
#endif

/* VCMPGTUW */
extern bool2 __cmp_gt_bool(uint2, uint2);
extern bool3 __cmp_gt_bool(uint3, uint3);
extern bool4 __cmp_gt_bool(uint4, uint4);
extern bool8 __cmp_gt_bool(uint8, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern bool16 __cmp_gt_bool(uint16, uint16);
#endif

/* VCMPLTSP */
extern bool2 __cmp_gt_bool(float2, float2);
extern bool3 __cmp_gt_bool(float3, float3);
extern bool4 __cmp_gt_bool(float4, float4);
extern bool8 __cmp_gt_bool(float8, float8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern bool16 __cmp_gt_bool(float16, float16);
#endif

/* VCMPGTD */
extern bool2 __cmp_gt_bool(long2, long2);
extern bool3 __cmp_gt_bool(long3, long3);
extern bool4 __cmp_gt_bool(long4, long4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern bool8 __cmp_gt_bool(long8, long8);
#endif

/* VCMPGTUD */
extern bool2 __cmp_gt_bool(ulong2, ulong2);
extern bool3 __cmp_gt_bool(ulong3, ulong3);
extern bool4 __cmp_gt_bool(ulong4, ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern bool8 __cmp_gt_bool(ulong8, ulong8);
#endif

/* VCMPLTDP */
extern bool2 __cmp_gt_bool(double2, double2);
extern bool3 __cmp_gt_bool(double3, double3);
extern bool4 __cmp_gt_bool(double4, double4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern bool8 __cmp_gt_bool(double8, double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __cmp_le                                                               */
/*----------------------------------------------------------------------------*/

/* CMPLESP */
extern int32_t __cmp_le(float, float);

/* CMPLEDP */
extern int32_t __cmp_le(double, double);

/*----------------------------------------------------------------------------*/
/* ID: __cmp_le_bool                                                          */
/*----------------------------------------------------------------------------*/

/* VCMPGEB */
extern bool2 __cmp_le_bool(char2, char2);
extern bool3 __cmp_le_bool(char3, char3);
extern bool4 __cmp_le_bool(char4, char4);
extern bool8 __cmp_le_bool(char8, char8);
extern bool16 __cmp_le_bool(char16, char16);
extern bool32 __cmp_le_bool(char32, char32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern bool64 __cmp_le_bool(char64, char64);
#endif

/* VCMPGEUB */
extern bool2 __cmp_le_bool(uchar2, uchar2);
extern bool3 __cmp_le_bool(uchar3, uchar3);
extern bool4 __cmp_le_bool(uchar4, uchar4);
extern bool8 __cmp_le_bool(uchar8, uchar8);
extern bool16 __cmp_le_bool(uchar16, uchar16);
extern bool32 __cmp_le_bool(uchar32, uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern bool64 __cmp_le_bool(uchar64, uchar64);
#endif

/* VCMPGEH */
extern bool2 __cmp_le_bool(short2, short2);
extern bool3 __cmp_le_bool(short3, short3);
extern bool4 __cmp_le_bool(short4, short4);
extern bool8 __cmp_le_bool(short8, short8);
extern bool16 __cmp_le_bool(short16, short16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern bool32 __cmp_le_bool(short32, short32);
#endif

/* VCMPGEUH */
extern bool2 __cmp_le_bool(ushort2, ushort2);
extern bool3 __cmp_le_bool(ushort3, ushort3);
extern bool4 __cmp_le_bool(ushort4, ushort4);
extern bool8 __cmp_le_bool(ushort8, ushort8);
extern bool16 __cmp_le_bool(ushort16, ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern bool32 __cmp_le_bool(ushort32, ushort32);
#endif

/* VCMPGEW */
extern bool2 __cmp_le_bool(int2, int2);
extern bool3 __cmp_le_bool(int3, int3);
extern bool4 __cmp_le_bool(int4, int4);
extern bool8 __cmp_le_bool(int8, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern bool16 __cmp_le_bool(int16, int16);
#endif

/* VCMPGEUW */
extern bool2 __cmp_le_bool(uint2, uint2);
extern bool3 __cmp_le_bool(uint3, uint3);
extern bool4 __cmp_le_bool(uint4, uint4);
extern bool8 __cmp_le_bool(uint8, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern bool16 __cmp_le_bool(uint16, uint16);
#endif

/* VCMPLESP */
extern bool2 __cmp_le_bool(float2, float2);
extern bool3 __cmp_le_bool(float3, float3);
extern bool4 __cmp_le_bool(float4, float4);
extern bool8 __cmp_le_bool(float8, float8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern bool16 __cmp_le_bool(float16, float16);
#endif

/* VCMPGED */
extern bool2 __cmp_le_bool(long2, long2);
extern bool3 __cmp_le_bool(long3, long3);
extern bool4 __cmp_le_bool(long4, long4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern bool8 __cmp_le_bool(long8, long8);
#endif

/* VCMPGEUD */
extern bool2 __cmp_le_bool(ulong2, ulong2);
extern bool3 __cmp_le_bool(ulong3, ulong3);
extern bool4 __cmp_le_bool(ulong4, ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern bool8 __cmp_le_bool(ulong8, ulong8);
#endif

/* VCMPLEDP */
extern bool2 __cmp_le_bool(double2, double2);
extern bool3 __cmp_le_bool(double3, double3);
extern bool4 __cmp_le_bool(double4, double4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern bool8 __cmp_le_bool(double8, double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __cmp_lt                                                               */
/*----------------------------------------------------------------------------*/

/* CMPLTSP */
extern int32_t __cmp_lt(float, float);

/* CMPLTDP */
extern int32_t __cmp_lt(double, double);

/*----------------------------------------------------------------------------*/
/* ID: __cmp_lt_bool                                                          */
/*----------------------------------------------------------------------------*/

/* VCMPGTB */
extern bool2 __cmp_lt_bool(char2, char2);
extern bool3 __cmp_lt_bool(char3, char3);
extern bool4 __cmp_lt_bool(char4, char4);
extern bool8 __cmp_lt_bool(char8, char8);
extern bool16 __cmp_lt_bool(char16, char16);
extern bool32 __cmp_lt_bool(char32, char32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern bool64 __cmp_lt_bool(char64, char64);
#endif

/* VCMPGTUB */
extern bool2 __cmp_lt_bool(uchar2, uchar2);
extern bool3 __cmp_lt_bool(uchar3, uchar3);
extern bool4 __cmp_lt_bool(uchar4, uchar4);
extern bool8 __cmp_lt_bool(uchar8, uchar8);
extern bool16 __cmp_lt_bool(uchar16, uchar16);
extern bool32 __cmp_lt_bool(uchar32, uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern bool64 __cmp_lt_bool(uchar64, uchar64);
#endif

/* VCMPGTH */
extern bool2 __cmp_lt_bool(short2, short2);
extern bool3 __cmp_lt_bool(short3, short3);
extern bool4 __cmp_lt_bool(short4, short4);
extern bool8 __cmp_lt_bool(short8, short8);
extern bool16 __cmp_lt_bool(short16, short16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern bool32 __cmp_lt_bool(short32, short32);
#endif

/* VCMPGTUH */
extern bool2 __cmp_lt_bool(ushort2, ushort2);
extern bool3 __cmp_lt_bool(ushort3, ushort3);
extern bool4 __cmp_lt_bool(ushort4, ushort4);
extern bool8 __cmp_lt_bool(ushort8, ushort8);
extern bool16 __cmp_lt_bool(ushort16, ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern bool32 __cmp_lt_bool(ushort32, ushort32);
#endif

/* VCMPGTW */
extern bool2 __cmp_lt_bool(int2, int2);
extern bool3 __cmp_lt_bool(int3, int3);
extern bool4 __cmp_lt_bool(int4, int4);
extern bool8 __cmp_lt_bool(int8, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern bool16 __cmp_lt_bool(int16, int16);
#endif

/* VCMPGTUW */
extern bool2 __cmp_lt_bool(uint2, uint2);
extern bool3 __cmp_lt_bool(uint3, uint3);
extern bool4 __cmp_lt_bool(uint4, uint4);
extern bool8 __cmp_lt_bool(uint8, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern bool16 __cmp_lt_bool(uint16, uint16);
#endif

/* VCMPLTSP */
extern bool2 __cmp_lt_bool(float2, float2);
extern bool3 __cmp_lt_bool(float3, float3);
extern bool4 __cmp_lt_bool(float4, float4);
extern bool8 __cmp_lt_bool(float8, float8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern bool16 __cmp_lt_bool(float16, float16);
#endif

/* VCMPGTD */
extern bool2 __cmp_lt_bool(long2, long2);
extern bool3 __cmp_lt_bool(long3, long3);
extern bool4 __cmp_lt_bool(long4, long4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern bool8 __cmp_lt_bool(long8, long8);
#endif

/* VCMPGTUD */
extern bool2 __cmp_lt_bool(ulong2, ulong2);
extern bool3 __cmp_lt_bool(ulong3, ulong3);
extern bool4 __cmp_lt_bool(ulong4, ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern bool8 __cmp_lt_bool(ulong8, ulong8);
#endif

/* VCMPLTDP */
extern bool2 __cmp_lt_bool(double2, double2);
extern bool3 __cmp_lt_bool(double3, double3);
extern bool4 __cmp_lt_bool(double4, double4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern bool8 __cmp_lt_bool(double8, double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __cmpy_conj_ext                                                        */
/*----------------------------------------------------------------------------*/

/* VCCMPYHW */
extern cint __cmpy_conj_ext(cshort, cshort);
extern cint2 __cmpy_conj_ext(cshort2, cshort2);
extern cint4 __cmpy_conj_ext(cshort4, cshort4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern cint8 __cmpy_conj_ext(cshort8, cshort8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __cmpy_conj_fx                                                         */
/*----------------------------------------------------------------------------*/

/* VCCMPYR1HH */
extern cshort __cmpy_conj_fx(cshort, cshort);
extern cshort2 __cmpy_conj_fx(cshort2, cshort2);
extern cshort4 __cmpy_conj_fx(cshort4, cshort4);
extern cshort8 __cmpy_conj_fx(cshort8, cshort8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern cshort16 __cmpy_conj_fx(cshort16, cshort16);
#endif

/* VCCMPYR1WW */
extern cint __cmpy_conj_fx(cint, cint);
extern cint2 __cmpy_conj_fx(cint2, cint2);
extern cint4 __cmpy_conj_fx(cint4, cint4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern cint8 __cmpy_conj_fx(cint8, cint8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __cmpy_ext                                                             */
/*----------------------------------------------------------------------------*/

/* VCMPYHW */
extern cint __cmpy_ext(cshort, cshort);
extern cint2 __cmpy_ext(cshort2, cshort2);
extern cint4 __cmpy_ext(cshort4, cshort4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern cint8 __cmpy_ext(cshort8, cshort8);
#endif

/* VCMPYSP */
extern float4 __cmpy_ext(cfloat, cfloat);
extern float8 __cmpy_ext(cfloat2, cfloat2);
#if __C7X_VEC_SIZE_BITS__ == 512
extern float16 __cmpy_ext(cfloat4, cfloat4);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __cmpy_fx                                                              */
/*----------------------------------------------------------------------------*/

/* VCMPYR1HH */
extern cshort __cmpy_fx(cshort, cshort);
extern cshort2 __cmpy_fx(cshort2, cshort2);
extern cshort4 __cmpy_fx(cshort4, cshort4);
extern cshort8 __cmpy_fx(cshort8, cshort8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern cshort16 __cmpy_fx(cshort16, cshort16);
#endif

/* VCMPYR1WW */
extern cint __cmpy_fx(cint, cint);
extern cint2 __cmpy_fx(cint2, cint2);
extern cint4 __cmpy_fx(cint4, cint4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern cint8 __cmpy_fx(cint8, cint8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __cmpyr_fx                                                             */
/*----------------------------------------------------------------------------*/

/* VCMPYRHH */
extern cshort __cmpyr_fx(cshort, cshort);
extern cshort2 __cmpyr_fx(cshort2, cshort2);
extern cshort4 __cmpyr_fx(cshort4, cshort4);
extern cshort8 __cmpyr_fx(cshort8, cshort8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern cshort16 __cmpyr_fx(cshort16, cshort16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __compress_set_bits_left                                               */
/*----------------------------------------------------------------------------*/

/* COMPRESSL */
#if __C7X_VEC_SIZE_BITS__ == 256
extern bool32 __compress_set_bits_left(bool32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern bool64 __compress_set_bits_left(bool64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __compress_set_bits_right                                              */
/*----------------------------------------------------------------------------*/

/* COMPRESSR */
#if __C7X_VEC_SIZE_BITS__ == 256
extern bool32 __compress_set_bits_right(bool32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern bool64 __compress_set_bits_right(bool64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __conj_cmatmpy_ext                                                     */
/*----------------------------------------------------------------------------*/

/* VCCMATMPYHW */
extern cint2 __conj_cmatmpy_ext(cshort2, cshort4);
extern cint4 __conj_cmatmpy_ext(cshort4, cshort8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern cint8 __conj_cmatmpy_ext(cshort8, cshort16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __conj_cmatmpy_fx                                                      */
/*----------------------------------------------------------------------------*/

/* VCCMATMPYR1HH */
extern cshort2 __conj_cmatmpy_fx(cshort2, cshort4);
extern cshort4 __conj_cmatmpy_fx(cshort4, cshort8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern cshort8 __conj_cmatmpy_fx(cshort8, cshort16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __crot270                                                              */
/*----------------------------------------------------------------------------*/

/* VCROT270H */
extern cshort __crot270(cshort);
extern cshort2 __crot270(cshort2);
extern cshort4 __crot270(cshort4);
extern cshort8 __crot270(cshort8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern cshort16 __crot270(cshort16);
#endif

/* VCROT270W */
extern cint __crot270(cint);
extern cint2 __crot270(cint2);
extern cint4 __crot270(cint4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern cint8 __crot270(cint8);
#endif

/* VCROT270SP */
extern cfloat __crot270(cfloat);
extern cfloat2 __crot270(cfloat2);
extern cfloat4 __crot270(cfloat4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern cfloat8 __crot270(cfloat8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __crot90                                                               */
/*----------------------------------------------------------------------------*/

/* VCROT90H */
extern cshort __crot90(cshort);
extern cshort2 __crot90(cshort2);
extern cshort4 __crot90(cshort4);
extern cshort8 __crot90(cshort8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern cshort16 __crot90(cshort16);
#endif

/* VCROT90W */
extern cint __crot90(cint);
extern cint2 __crot90(cint2);
extern cint4 __crot90(cint4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern cint8 __crot90(cint8);
#endif

/* VCROT90SP */
extern cfloat __crot90(cfloat);
extern cfloat2 __crot90(cfloat2);
extern cfloat4 __crot90(cfloat4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern cfloat8 __crot90(cfloat8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __deal_bit                                                             */
/*----------------------------------------------------------------------------*/

/* VBITDEALW */
extern int32_t __deal_bit(int32_t);
extern int2 __deal_bit(int2);
extern int3 __deal_bit(int3);
extern int4 __deal_bit(int4);
extern int8 __deal_bit(int8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __deal_bit(int16);
#endif
extern uint32_t __deal_bit(uint32_t);
extern uint2 __deal_bit(uint2);
extern uint3 __deal_bit(uint3);
extern uint4 __deal_bit(uint4);
extern uint8 __deal_bit(uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __deal_bit(uint16);
#endif

/* VBITDEALD */
extern int64_t __deal_bit(int64_t);
extern long2 __deal_bit(long2);
extern long3 __deal_bit(long3);
extern long4 __deal_bit(long4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __deal_bit(long8);
#endif
extern uint64_t __deal_bit(uint64_t);
extern ulong2 __deal_bit(ulong2);
extern ulong3 __deal_bit(ulong3);
extern ulong4 __deal_bit(ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __deal_bit(ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __deal_stride2                                                         */
/*----------------------------------------------------------------------------*/

/* VDEAL2B */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __deal_stride2(char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __deal_stride2(char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __deal_stride2(uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __deal_stride2(uchar64);
#endif

/* VDEAL2H */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cchar16 __deal_stride2(cchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cchar32 __deal_stride2(cchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __deal_stride2(short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __deal_stride2(short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __deal_stride2(ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __deal_stride2(ushort32);
#endif

/* VDEAL2W */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cshort8 __deal_stride2(cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cshort16 __deal_stride2(cshort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __deal_stride2(int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __deal_stride2(int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __deal_stride2(uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __deal_stride2(uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern float8 __deal_stride2(float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern float16 __deal_stride2(float16);
#endif

/* VDEAL2D */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cint4 __deal_stride2(cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cint8 __deal_stride2(cint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cfloat4 __deal_stride2(cfloat4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cfloat8 __deal_stride2(cfloat8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __deal_stride2(long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __deal_stride2(long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __deal_stride2(ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __deal_stride2(ulong8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern double4 __deal_stride2(double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern double8 __deal_stride2(double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __deal_stride4                                                         */
/*----------------------------------------------------------------------------*/

/* VDEAL4B */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __deal_stride4(char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __deal_stride4(char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __deal_stride4(uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __deal_stride4(uchar64);
#endif

/* VDEAL4H */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cchar16 __deal_stride4(cchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cchar32 __deal_stride4(cchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __deal_stride4(short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __deal_stride4(short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __deal_stride4(ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __deal_stride4(ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __decimate                                                             */
/*----------------------------------------------------------------------------*/

/* DECIMATEB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern bool32 __decimate(bool32, bool32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern bool64 __decimate(bool64, bool64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __dot_posneg128_mask                                                   */
/*----------------------------------------------------------------------------*/

/* VDOTPMPN16W8D */
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __dot_posneg128_mask(ushort32, ushort8, int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __dot_posneg128_mask_ext                                               */
/*----------------------------------------------------------------------------*/

/* VDOTPMPNU16W8D */
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __dot_posneg128_mask_ext(ushort32, ushort8, uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __dot_posneg256_mask                                                   */
/*----------------------------------------------------------------------------*/

/* VDOTPMPN16H16W */
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __dot_posneg256_mask(ushort32, ushort16, short16);
#endif

/* VDOTPMPNU16H16W */
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __dot_posneg256_mask(ushort32, ushort16, ushort16);
#endif

/* VDOTPMPN32H8W */
#if __C7X_VEC_SIZE_BITS__ == 512
extern int8 __dot_posneg256_mask(uint8, uint8, short32);
#endif

/* VDOTPMPNU32H8W */
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint8 __dot_posneg256_mask(uint8, uint8, ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __dot_posneg512_mask                                                   */
/*----------------------------------------------------------------------------*/

/* VDOTPMPN16B32H */
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __dot_posneg512_mask(ushort32, ushort32, char16);
#endif

/* VDOTPMPN32B16H */
#if __C7X_VEC_SIZE_BITS__ == 512
extern short16 __dot_posneg512_mask(uint16, uint16, char32);
#endif

/* VDOTPMPNU32B16H */
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort16 __dot_posneg512_mask(uint16, uint16, uchar32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __dot_posneg512_mask_ext                                               */
/*----------------------------------------------------------------------------*/

/* VDOTPMPN32B16W */
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __dot_posneg512_mask_ext(uint16, uint16, char32);
#endif

/* VDOTPMPNU32B16W */
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __dot_posneg512_mask_ext(uint16, uint16, uchar32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __dotp2                                                                */
/*----------------------------------------------------------------------------*/

/* VDOTP2SUBH */
extern int16_t __dotp2(char2, uchar2);
extern short2 __dotp2(char4, uchar4);
extern short4 __dotp2(char8, uchar8);
extern short8 __dotp2(char16, uchar16);
extern short16 __dotp2(char32, uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __dotp2(char64, uchar64);
#endif

/* VDOTP2UBH */
extern uint16_t __dotp2(uchar2, uchar2);
extern ushort2 __dotp2(uchar4, uchar4);
extern ushort4 __dotp2(uchar8, uchar8);
extern ushort8 __dotp2(uchar16, uchar16);
extern ushort16 __dotp2(uchar32, uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __dotp2(uchar64, uchar64);
#endif

/* VDOTP2HW */
extern int32_t __dotp2(short2, short2);
extern int2 __dotp2(short4, short4);
extern int4 __dotp2(short8, short8);
extern int8 __dotp2(short16, short16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __dotp2(short32, short32);
#endif

/* VDOTP2SUHW */
extern int32_t __dotp2(short2, ushort2);
extern int2 __dotp2(short4, ushort4);
extern int4 __dotp2(short8, ushort8);
extern int8 __dotp2(short16, ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __dotp2(short32, ushort32);
#endif

/* VDOTP2UHW */
extern uint32_t __dotp2(ushort2, ushort2);
extern uint2 __dotp2(ushort4, ushort4);
extern uint4 __dotp2(ushort8, ushort8);
extern uint8 __dotp2(ushort16, ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __dotp2(ushort32, ushort32);
#endif

/* VCDOTP2HW */
extern cint __dotp2(cshort2, cshort2);
extern cint2 __dotp2(cshort4, cshort4);
extern cint4 __dotp2(cshort8, cshort8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern cint8 __dotp2(cshort16, cshort16);
#endif

/* VDOTP2WD */
extern int64_t __dotp2(int2, int2);
extern long2 __dotp2(int4, int4);
extern long4 __dotp2(int8, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __dotp2(int16, int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __dotp2_conj                                                           */
/*----------------------------------------------------------------------------*/

/* VCCDOTP2HW */
extern cint __dotp2_conj(cshort2, cshort2);
extern cint2 __dotp2_conj(cshort4, cshort4);
extern cint4 __dotp2_conj(cshort8, cshort8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern cint8 __dotp2_conj(cshort16, cshort16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __dotp2_cross                                                          */
/*----------------------------------------------------------------------------*/

/* VDOTP2XWD */
extern int64_t __dotp2_cross(int2, int2);
extern long2 __dotp2_cross(int4, int4);
extern long4 __dotp2_cross(int8, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __dotp2_cross(int16, int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __dotp2_cross_negate                                                   */
/*----------------------------------------------------------------------------*/

/* VDOTP2NXWD */
extern int64_t __dotp2_cross_negate(int2, int2);
extern long2 __dotp2_cross_negate(int4, int4);
extern long4 __dotp2_cross_negate(int8, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __dotp2_cross_negate(int16, int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __dotp2_ext                                                            */
/*----------------------------------------------------------------------------*/

/* VDOTP2HD */
extern int64_t __dotp2_ext(short2, short2);
extern long2 __dotp2_ext(short4, short4);
extern long4 __dotp2_ext(short8, short8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __dotp2_ext(short16, short16);
#endif

/* VDOTP2SUHD */
extern int64_t __dotp2_ext(short2, ushort2);
extern long2 __dotp2_ext(short4, ushort4);
extern long4 __dotp2_ext(short8, ushort8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __dotp2_ext(short16, ushort16);
#endif

/* VDOTP2UHD */
extern uint64_t __dotp2_ext(ushort2, ushort2);
extern ulong2 __dotp2_ext(ushort4, ushort4);
extern ulong4 __dotp2_ext(ushort8, ushort8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __dotp2_ext(ushort16, ushort16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __dotp2_fx_ext                                                         */
/*----------------------------------------------------------------------------*/

/* C6DOTP2RSUHW */
extern int32_t __dotp2_fx_ext(short2, ushort2);

/*----------------------------------------------------------------------------*/
/* ID: __dotp2_negate                                                         */
/*----------------------------------------------------------------------------*/

/* C6DOTPN2HW */
extern int32_t __dotp2_negate(short2, short2);

/* C6DOTPN2RSUHH */
extern int32_t __dotp2_negate(short2, ushort2);

/* VDOTP2NWD */
extern int64_t __dotp2_negate(int2, int2);
extern long2 __dotp2_negate(int4, int4);
extern long4 __dotp2_negate(int8, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __dotp2_negate(int16, int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __dotp4                                                                */
/*----------------------------------------------------------------------------*/

/* VDOTP4HW */
extern int32_t __dotp4(short4, short4);
extern int2 __dotp4(short8, short8);
extern int4 __dotp4(short16, short16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern int8 __dotp4(short32, short32);
#endif

/* VDOTP4SUHW */
extern int32_t __dotp4(short4, ushort4);
extern int2 __dotp4(short8, ushort8);
extern int4 __dotp4(short16, ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern int8 __dotp4(short32, ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __dotp4_ext                                                            */
/*----------------------------------------------------------------------------*/

/* VDOTP4SUBW */
extern int32_t __dotp4_ext(char4, uchar4);
extern int2 __dotp4_ext(char8, uchar8);
extern int4 __dotp4_ext(char16, uchar16);
extern int8 __dotp4_ext(char32, uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __dotp4_ext(char64, uchar64);
#endif

/* VDOTP4UBW */
extern uint32_t __dotp4_ext(uchar4, uchar4);
extern uint2 __dotp4_ext(uchar8, uchar8);
extern uint4 __dotp4_ext(uchar16, uchar16);
extern uint8 __dotp4_ext(uchar32, uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __dotp4_ext(uchar64, uchar64);
#endif

/* VDOTP4HD */
extern int64_t __dotp4_ext(short4, short4);
extern long2 __dotp4_ext(short8, short8);
extern long4 __dotp4_ext(short16, short16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __dotp4_ext(short32, short32);
#endif

/* VDOTP4SUHD */
extern int64_t __dotp4_ext(short4, ushort4);
extern long2 __dotp4_ext(short8, ushort8);
extern long4 __dotp4_ext(short16, ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __dotp4_ext(short32, ushort32);
#endif

/* VDOTP4UHD */
extern uint64_t __dotp4_ext(ushort4, ushort4);
extern ulong2 __dotp4_ext(ushort8, ushort8);
extern ulong4 __dotp4_ext(ushort16, ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __dotp4_ext(ushort32, ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __dotp8_ext                                                            */
/*----------------------------------------------------------------------------*/

/* VDOTP8SUBW */
extern int2 __dotp8_ext(char8, uchar8);
extern int4 __dotp8_ext(char16, uchar16);
extern int8 __dotp8_ext(char32, uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __dotp8_ext(char64, uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __double_to_float                                                      */
/*----------------------------------------------------------------------------*/

/* VDPSP */
extern float2 __double_to_float(double);
extern float4 __double_to_float(double2);
extern float8 __double_to_float(double4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern float16 __double_to_float(double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __double_to_int                                                        */
/*----------------------------------------------------------------------------*/

/* VDPINT */
extern int2 __double_to_int(double);
extern int4 __double_to_int(double2);
extern int8 __double_to_int(double4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __double_to_int(double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __double_to_int_rtz                                                    */
/*----------------------------------------------------------------------------*/

/* VDPTRUNC */
extern int2 __double_to_int_rtz(double);
extern int4 __double_to_int_rtz(double2);
extern int8 __double_to_int_rtz(double4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __double_to_int_rtz(double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __dual_horizontal_add_skip1                                            */
/*----------------------------------------------------------------------------*/

/* VHADDEOW4D */
#if __C7X_VEC_SIZE_BITS__ == 512
extern long4 __dual_horizontal_add_skip1(int16, int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __dual_horizontal_add_skip1(int8, int8);
#endif

/* VHADDUEOW4D */
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong4 __dual_horizontal_add_skip1(uint16, uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __dual_horizontal_add_skip1(uint8, uint8);
#endif

/* VHADDEOW4D */
#if __C7X_VEC_SIZE_BITS__ == 512
extern clong2 __dual_horizontal_add_skip1(cint8, cint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern clong2 __dual_horizontal_add_skip1(cint4, cint4);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __dual_sort_lo_asc_hi_asc                                              */
/*----------------------------------------------------------------------------*/

/* VDSORTIIH */
#if __C7X_VEC_SIZE_BITS__ == 512
extern short16 __dual_sort_lo_asc_hi_asc(short16);
extern short32 __dual_sort_lo_asc_hi_asc(short32);
#endif

/* VDSORTIIUH */
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort16 __dual_sort_lo_asc_hi_asc(ushort16);
extern ushort32 __dual_sort_lo_asc_hi_asc(ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __dual_sort_lo_asc_hi_asc_perm                                         */
/*----------------------------------------------------------------------------*/

/* VDSORTPIIH */
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar32 __dual_sort_lo_asc_hi_asc_perm(short16);
extern uchar64 __dual_sort_lo_asc_hi_asc_perm(short32);
#endif

/* VDSORTPIIUH */
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar32 __dual_sort_lo_asc_hi_asc_perm(ushort16);
extern uchar64 __dual_sort_lo_asc_hi_asc_perm(ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __dual_sort_lo_asc_hi_desc                                             */
/*----------------------------------------------------------------------------*/

/* VDSORTIDH */
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __dual_sort_lo_asc_hi_desc(short32);
#endif

/* VDSORTIDUH */
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __dual_sort_lo_asc_hi_desc(ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __dual_sort_lo_asc_hi_desc_perm                                        */
/*----------------------------------------------------------------------------*/

/* VDSORTPIDH */
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __dual_sort_lo_asc_hi_desc_perm(short32);
#endif

/* VDSORTPIDUH */
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __dual_sort_lo_asc_hi_desc_perm(ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __dual_sort_lo_desc_hi_asc                                             */
/*----------------------------------------------------------------------------*/

/* VDSORTDIH */
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __dual_sort_lo_desc_hi_asc(short32);
#endif

/* VDSORTDIUH */
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __dual_sort_lo_desc_hi_asc(ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __dual_sort_lo_desc_hi_asc_perm                                        */
/*----------------------------------------------------------------------------*/

/* VDSORTPDIH */
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __dual_sort_lo_desc_hi_asc_perm(short32);
#endif

/* VDSORTPDIUH */
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __dual_sort_lo_desc_hi_asc_perm(ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __dual_sort_lo_desc_hi_desc                                            */
/*----------------------------------------------------------------------------*/

/* VDSORTDDH */
#if __C7X_VEC_SIZE_BITS__ == 512
extern short16 __dual_sort_lo_desc_hi_desc(short16);
extern short32 __dual_sort_lo_desc_hi_desc(short32);
#endif

/* VDSORTDDUH */
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort16 __dual_sort_lo_desc_hi_desc(ushort16);
extern ushort32 __dual_sort_lo_desc_hi_desc(ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __dual_sort_lo_desc_hi_desc_perm                                       */
/*----------------------------------------------------------------------------*/

/* VDSORTPDDH */
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar32 __dual_sort_lo_desc_hi_desc_perm(short16);
extern uchar64 __dual_sort_lo_desc_hi_desc_perm(short32);
#endif

/* VDSORTPDDUH */
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar32 __dual_sort_lo_desc_hi_desc_perm(ushort16);
extern uchar64 __dual_sort_lo_desc_hi_desc_perm(ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __duplicate                                                            */
/*----------------------------------------------------------------------------*/

/* VDUPB */
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __duplicate(int8_t);
/* char64 __duplicate(int8_t(k)); */
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __duplicate(int8_t);
/* char32 __duplicate(int8_t(k)); */
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __duplicate(uint8_t);
/* uchar64 __duplicate(uint8_t(k)); */
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __duplicate(uint8_t);
/* uchar32 __duplicate(uint8_t(k)); */
#endif

/* VDUPH */
#if __C7X_VEC_SIZE_BITS__ == 512
extern cchar32 __duplicate(cchar);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cchar16 __duplicate(cchar);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __duplicate(int16_t);
/* short32 __duplicate(int16_t(k)); */
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __duplicate(int16_t);
/* short16 __duplicate(int16_t(k)); */
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __duplicate(uint16_t);
/* ushort32 __duplicate(uint16_t(k)); */
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __duplicate(uint16_t);
/* ushort16 __duplicate(uint16_t(k)); */
#endif

/* VDUPW */
#if __C7X_VEC_SIZE_BITS__ == 512
extern cshort16 __duplicate(cshort);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cshort8 __duplicate(cshort);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __duplicate(int32_t);
/* int16 __duplicate(int32_t(k)); */
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __duplicate(int32_t);
/* int8 __duplicate(int32_t(k)); */
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __duplicate(uint32_t);
/* uint16 __duplicate(uint32_t(k)); */
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __duplicate(uint32_t);
/* uint8 __duplicate(uint32_t(k)); */
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern float16 __duplicate(float);
/* float16 __duplicate(float(k)); */
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern float8 __duplicate(float);
/* float8 __duplicate(float(k)); */
#endif

/* VDUPD */
#if __C7X_VEC_SIZE_BITS__ == 512
extern cint8 __duplicate(cint);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cint4 __duplicate(cint);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cfloat8 __duplicate(cfloat);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cfloat4 __duplicate(cfloat);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __duplicate(int64_t);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __duplicate(int64_t);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __duplicate(uint64_t);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __duplicate(uint64_t);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern double8 __duplicate(double);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern double4 __duplicate(double);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __duplicate16                                                          */
/*----------------------------------------------------------------------------*/

/* VDUP16B */
extern char16 __duplicate16(int8_t);
extern char32 __duplicate16(char2);
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __duplicate16(char4);
#endif
extern uchar16 __duplicate16(uint8_t);
extern uchar32 __duplicate16(uchar2);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __duplicate16(uchar4);
#endif

/* VDUP16H */
extern cchar16 __duplicate16(cchar);
#if __C7X_VEC_SIZE_BITS__ == 512
extern cchar32 __duplicate16(cchar2);
#endif
extern short16 __duplicate16(int16_t);
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __duplicate16(short2);
#endif
extern ushort16 __duplicate16(uint16_t);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __duplicate16(ushort2);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __duplicate2                                                           */
/*----------------------------------------------------------------------------*/

/* VDUP2B */
extern char2 __duplicate2(int8_t);
extern char4 __duplicate2(char2);
extern char8 __duplicate2(char4);
extern char16 __duplicate2(char8);
extern char32 __duplicate2(char16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __duplicate2(char32);
#endif
extern uchar2 __duplicate2(uint8_t);
extern uchar4 __duplicate2(uchar2);
extern uchar8 __duplicate2(uchar4);
extern uchar16 __duplicate2(uchar8);
extern uchar32 __duplicate2(uchar16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __duplicate2(uchar32);
#endif

/* VDUP2H */
extern cchar2 __duplicate2(cchar);
extern cchar4 __duplicate2(cchar2);
extern cchar8 __duplicate2(cchar4);
extern cchar16 __duplicate2(cchar8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern cchar32 __duplicate2(cchar16);
#endif
extern short2 __duplicate2(int16_t);
extern short4 __duplicate2(short2);
extern short8 __duplicate2(short4);
extern short16 __duplicate2(short8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __duplicate2(short16);
#endif
extern ushort2 __duplicate2(uint16_t);
extern ushort4 __duplicate2(ushort2);
extern ushort8 __duplicate2(ushort4);
extern ushort16 __duplicate2(ushort8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __duplicate2(ushort16);
#endif

/* VDUP2W */
extern cshort2 __duplicate2(cshort);
extern cshort4 __duplicate2(cshort2);
extern cshort8 __duplicate2(cshort4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern cshort16 __duplicate2(cshort8);
#endif
extern int2 __duplicate2(int32_t);
extern int4 __duplicate2(int2);
extern int8 __duplicate2(int4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __duplicate2(int8);
#endif
extern uint2 __duplicate2(uint32_t);
extern uint4 __duplicate2(uint2);
extern uint8 __duplicate2(uint4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __duplicate2(uint8);
#endif
extern float2 __duplicate2(float);
extern float4 __duplicate2(float2);
extern float8 __duplicate2(float4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern float16 __duplicate2(float8);
#endif

/* VDUP2D */
extern cint2 __duplicate2(cint);
extern cint4 __duplicate2(cint2);
#if __C7X_VEC_SIZE_BITS__ == 512
extern cint8 __duplicate2(cint4);
#endif
extern cfloat2 __duplicate2(cfloat);
extern cfloat4 __duplicate2(cfloat2);
#if __C7X_VEC_SIZE_BITS__ == 512
extern cfloat8 __duplicate2(cfloat4);
#endif
extern long2 __duplicate2(int64_t);
extern long4 __duplicate2(long2);
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __duplicate2(long4);
#endif
extern ulong2 __duplicate2(uint64_t);
extern ulong4 __duplicate2(ulong2);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __duplicate2(ulong4);
#endif
extern double2 __duplicate2(double);
extern double4 __duplicate2(double2);
#if __C7X_VEC_SIZE_BITS__ == 512
extern double8 __duplicate2(double4);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __duplicate32                                                          */
/*----------------------------------------------------------------------------*/

/* VDUP32B */
extern char32 __duplicate32(int8_t);
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __duplicate32(char2);
#endif
extern uchar32 __duplicate32(uint8_t);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __duplicate32(uchar2);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __duplicate4                                                           */
/*----------------------------------------------------------------------------*/

/* VDUP4B */
extern char4 __duplicate4(int8_t);
extern char8 __duplicate4(char2);
extern char16 __duplicate4(char4);
extern char32 __duplicate4(char8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __duplicate4(char16);
#endif
extern uchar4 __duplicate4(uint8_t);
extern uchar8 __duplicate4(uchar2);
extern uchar16 __duplicate4(uchar4);
extern uchar32 __duplicate4(uchar8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __duplicate4(uchar16);
#endif

/* VDUP4H */
extern cchar4 __duplicate4(cchar);
extern cchar8 __duplicate4(cchar2);
extern cchar16 __duplicate4(cchar4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern cchar32 __duplicate4(cchar8);
#endif
extern short4 __duplicate4(int16_t);
extern short8 __duplicate4(short2);
extern short16 __duplicate4(short4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __duplicate4(short8);
#endif
extern ushort4 __duplicate4(uint16_t);
extern ushort8 __duplicate4(ushort2);
extern ushort16 __duplicate4(ushort4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __duplicate4(ushort8);
#endif

/* VDUP4W */
extern cshort4 __duplicate4(cshort);
extern cshort8 __duplicate4(cshort2);
#if __C7X_VEC_SIZE_BITS__ == 512
extern cshort16 __duplicate4(cshort4);
#endif
extern int4 __duplicate4(int32_t);
extern int8 __duplicate4(int2);
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __duplicate4(int4);
#endif
extern uint4 __duplicate4(uint32_t);
extern uint8 __duplicate4(uint2);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __duplicate4(uint4);
#endif
extern float4 __duplicate4(float);
extern float8 __duplicate4(float2);
#if __C7X_VEC_SIZE_BITS__ == 512
extern float16 __duplicate4(float4);
#endif

/* VDUP4D */
extern cint4 __duplicate4(cint);
#if __C7X_VEC_SIZE_BITS__ == 512
extern cint8 __duplicate4(cint2);
#endif
extern cfloat4 __duplicate4(cfloat);
#if __C7X_VEC_SIZE_BITS__ == 512
extern cfloat8 __duplicate4(cfloat2);
#endif
extern long4 __duplicate4(int64_t);
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __duplicate4(long2);
#endif
extern ulong4 __duplicate4(uint64_t);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __duplicate4(ulong2);
#endif
extern double4 __duplicate4(double);
#if __C7X_VEC_SIZE_BITS__ == 512
extern double8 __duplicate4(double2);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __duplicate8                                                           */
/*----------------------------------------------------------------------------*/

/* VDUP8B */
extern char8 __duplicate8(int8_t);
extern char16 __duplicate8(char2);
extern char32 __duplicate8(char4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __duplicate8(char8);
#endif
extern uchar8 __duplicate8(uint8_t);
extern uchar16 __duplicate8(uchar2);
extern uchar32 __duplicate8(uchar4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __duplicate8(uchar8);
#endif

/* VDUP8H */
extern cchar8 __duplicate8(cchar);
extern cchar16 __duplicate8(cchar2);
#if __C7X_VEC_SIZE_BITS__ == 512
extern cchar32 __duplicate8(cchar4);
#endif
extern short8 __duplicate8(int16_t);
extern short16 __duplicate8(short2);
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __duplicate8(short4);
#endif
extern ushort8 __duplicate8(uint16_t);
extern ushort16 __duplicate8(ushort2);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __duplicate8(ushort4);
#endif

/* VDUP8W */
extern cshort8 __duplicate8(cshort);
#if __C7X_VEC_SIZE_BITS__ == 512
extern cshort16 __duplicate8(cshort2);
#endif
extern int8 __duplicate8(int32_t);
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __duplicate8(int2);
#endif
extern uint8 __duplicate8(uint32_t);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __duplicate8(uint2);
#endif
extern float8 __duplicate8(float);
#if __C7X_VEC_SIZE_BITS__ == 512
extern float16 __duplicate8(float2);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __duplicate_pred_high                                                  */
/*----------------------------------------------------------------------------*/

/* PDUPH2B */
#if __C7X_VEC_SIZE_BITS__ == 256
extern bool32 __duplicate_pred_high(bool32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern bool64 __duplicate_pred_high(bool64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __duplicate_pred_low                                                   */
/*----------------------------------------------------------------------------*/

/* PDUPL2B */
#if __C7X_VEC_SIZE_BITS__ == 256
extern bool32 __duplicate_pred_low(bool32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern bool64 __duplicate_pred_low(bool64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __expand                                                               */
/*----------------------------------------------------------------------------*/

/* VPXPND */
extern char2 __expand(bool2);
extern char3 __expand(bool3);
extern char4 __expand(bool4);
extern char8 __expand(bool8);
extern char16 __expand(bool16);
extern char32 __expand(bool32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __expand(bool64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __expand_lsb_pack_char                                                 */
/*----------------------------------------------------------------------------*/

/* XPND8B */
extern char8 __expand_lsb_pack_char(int8_t);
extern uchar8 __expand_lsb_pack_char(uint8_t);

/*----------------------------------------------------------------------------*/
/* ID: __expand_lsb_pack_short                                                */
/*----------------------------------------------------------------------------*/

/* XPND4H */
extern short4 __expand_lsb_pack_short(int8_t);
extern ushort4 __expand_lsb_pack_short(uint8_t);

/*----------------------------------------------------------------------------*/
/* ID: __float_to_half_float                                                  */
/*----------------------------------------------------------------------------*/

/* VSPHP */
extern uint32_t __float_to_half_float(float);
extern uint2 __float_to_half_float(float2);
extern uint3 __float_to_half_float(float3);
extern uint4 __float_to_half_float(float4);
extern uint8 __float_to_half_float(float8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __float_to_half_float(float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __float_to_int                                                         */
/*----------------------------------------------------------------------------*/

/* VSPINT */
extern int32_t __float_to_int(float);
extern int2 __float_to_int(float2);
extern int3 __float_to_int(float3);
extern int4 __float_to_int(float4);
extern int8 __float_to_int(float8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __float_to_int(float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __float_to_int_rtz                                                     */
/*----------------------------------------------------------------------------*/

/* VSPTRUNC */
extern int32_t __float_to_int_rtz(float);
extern int2 __float_to_int_rtz(float2);
extern int3 __float_to_int_rtz(float3);
extern int4 __float_to_int_rtz(float4);
extern int8 __float_to_int_rtz(float8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __float_to_int_rtz(float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __float_to_short                                                       */
/*----------------------------------------------------------------------------*/

/* VSPINTH */
extern short2 __float_to_short(float);
extern short4 __float_to_short(float2);
extern short8 __float_to_short(float4);
extern short16 __float_to_short(float8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __float_to_short(float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __get_vector_element                                                   */
/*----------------------------------------------------------------------------*/

/* VGETB */
#if __C7X_VEC_SIZE_BITS__ == 512
extern int8_t __get_vector_element(char64, uint32_t);
/* int8_t __get_vector_element(char64, uint32_t(k)); */
#endif
extern int8_t __get_vector_element(char32, uint32_t);
/* int8_t __get_vector_element(char32, uint32_t(k)); */
extern int8_t __get_vector_element(char16, uint32_t);
/* int8_t __get_vector_element(char16, uint32_t(k)); */
extern int8_t __get_vector_element(char8, uint32_t);
/* int8_t __get_vector_element(char8, uint32_t(k)); */
extern int8_t __get_vector_element(char4, uint32_t);
/* int8_t __get_vector_element(char4, uint32_t(k)); */
extern int8_t __get_vector_element(char3, uint32_t);
/* int8_t __get_vector_element(char3, uint32_t(k)); */
extern int8_t __get_vector_element(char2, uint32_t);
/* int8_t __get_vector_element(char2, uint32_t(k)); */

/* VGETUB */
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint8_t __get_vector_element(uchar64, uint32_t);
/* uint8_t __get_vector_element(uchar64, uint32_t(k)); */
#endif
extern uint8_t __get_vector_element(uchar32, uint32_t);
/* uint8_t __get_vector_element(uchar32, uint32_t(k)); */
extern uint8_t __get_vector_element(uchar16, uint32_t);
/* uint8_t __get_vector_element(uchar16, uint32_t(k)); */
extern uint8_t __get_vector_element(uchar8, uint32_t);
/* uint8_t __get_vector_element(uchar8, uint32_t(k)); */
extern uint8_t __get_vector_element(uchar4, uint32_t);
/* uint8_t __get_vector_element(uchar4, uint32_t(k)); */
extern uint8_t __get_vector_element(uchar3, uint32_t);
/* uint8_t __get_vector_element(uchar3, uint32_t(k)); */
extern uint8_t __get_vector_element(uchar2, uint32_t);
/* uint8_t __get_vector_element(uchar2, uint32_t(k)); */

/* VGETH */
#if __C7X_VEC_SIZE_BITS__ == 512
extern cchar __get_vector_element(cchar32, uint32_t);
/* cchar __get_vector_element(cchar32, uint32_t(k)); */
#endif
extern cchar __get_vector_element(cchar16, uint32_t);
/* cchar __get_vector_element(cchar16, uint32_t(k)); */
extern cchar __get_vector_element(cchar8, uint32_t);
/* cchar __get_vector_element(cchar8, uint32_t(k)); */
extern cchar __get_vector_element(cchar4, uint32_t);
/* cchar __get_vector_element(cchar4, uint32_t(k)); */
extern cchar __get_vector_element(cchar2, uint32_t);
/* cchar __get_vector_element(cchar2, uint32_t(k)); */
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16_t __get_vector_element(short32, uint32_t);
/* int16_t __get_vector_element(short32, uint32_t(k)); */
#endif
extern int16_t __get_vector_element(short16, uint32_t);
/* int16_t __get_vector_element(short16, uint32_t(k)); */
extern int16_t __get_vector_element(short8, uint32_t);
/* int16_t __get_vector_element(short8, uint32_t(k)); */
extern int16_t __get_vector_element(short4, uint32_t);
/* int16_t __get_vector_element(short4, uint32_t(k)); */
extern int16_t __get_vector_element(short3, uint32_t);
/* int16_t __get_vector_element(short3, uint32_t(k)); */
extern int16_t __get_vector_element(short2, uint32_t);
/* int16_t __get_vector_element(short2, uint32_t(k)); */

/* VGETUH */
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16_t __get_vector_element(ushort32, uint32_t);
/* uint16_t __get_vector_element(ushort32, uint32_t(k)); */
#endif
extern uint16_t __get_vector_element(ushort16, uint32_t);
/* uint16_t __get_vector_element(ushort16, uint32_t(k)); */
extern uint16_t __get_vector_element(ushort8, uint32_t);
/* uint16_t __get_vector_element(ushort8, uint32_t(k)); */
extern uint16_t __get_vector_element(ushort4, uint32_t);
/* uint16_t __get_vector_element(ushort4, uint32_t(k)); */
extern uint16_t __get_vector_element(ushort3, uint32_t);
/* uint16_t __get_vector_element(ushort3, uint32_t(k)); */
extern uint16_t __get_vector_element(ushort2, uint32_t);
/* uint16_t __get_vector_element(ushort2, uint32_t(k)); */

/* VGETW */
#if __C7X_VEC_SIZE_BITS__ == 512
extern cshort __get_vector_element(cshort16, uint32_t);
/* cshort __get_vector_element(cshort16, uint32_t(k)); */
#endif
extern cshort __get_vector_element(cshort8, uint32_t);
/* cshort __get_vector_element(cshort8, uint32_t(k)); */
extern cshort __get_vector_element(cshort4, uint32_t);
/* cshort __get_vector_element(cshort4, uint32_t(k)); */
extern cshort __get_vector_element(cshort2, uint32_t);
/* cshort __get_vector_element(cshort2, uint32_t(k)); */
#if __C7X_VEC_SIZE_BITS__ == 512
extern int32_t __get_vector_element(int16, uint32_t);
/* int32_t __get_vector_element(int16, uint32_t(k)); */
#endif
extern int32_t __get_vector_element(int8, uint32_t);
/* int32_t __get_vector_element(int8, uint32_t(k)); */
extern int32_t __get_vector_element(int4, uint32_t);
/* int32_t __get_vector_element(int4, uint32_t(k)); */
extern int32_t __get_vector_element(int3, uint32_t);
/* int32_t __get_vector_element(int3, uint32_t(k)); */
extern int32_t __get_vector_element(int2, uint32_t);
/* int32_t __get_vector_element(int2, uint32_t(k)); */

/* VGETUW */
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint32_t __get_vector_element(uint16, uint32_t);
/* uint32_t __get_vector_element(uint16, uint32_t(k)); */
#endif
extern uint32_t __get_vector_element(uint8, uint32_t);
/* uint32_t __get_vector_element(uint8, uint32_t(k)); */
extern uint32_t __get_vector_element(uint4, uint32_t);
/* uint32_t __get_vector_element(uint4, uint32_t(k)); */
extern uint32_t __get_vector_element(uint3, uint32_t);
/* uint32_t __get_vector_element(uint3, uint32_t(k)); */
extern uint32_t __get_vector_element(uint2, uint32_t);
/* uint32_t __get_vector_element(uint2, uint32_t(k)); */

/* VGETUW, VGETW */
#if __C7X_VEC_SIZE_BITS__ == 512
extern float __get_vector_element(float16, uint32_t);
/* float __get_vector_element(float16, uint32_t(k)); */
#endif
extern float __get_vector_element(float8, uint32_t);
/* float __get_vector_element(float8, uint32_t(k)); */
extern float __get_vector_element(float4, uint32_t);
/* float __get_vector_element(float4, uint32_t(k)); */
extern float __get_vector_element(float3, uint32_t);
/* float __get_vector_element(float3, uint32_t(k)); */
extern float __get_vector_element(float2, uint32_t);
/* float __get_vector_element(float2, uint32_t(k)); */

/* VGETD */
#if __C7X_VEC_SIZE_BITS__ == 512
extern cint __get_vector_element(cint8, uint32_t);
/* cint __get_vector_element(cint8, uint32_t(k)); */
#endif
extern cint __get_vector_element(cint4, uint32_t);
/* cint __get_vector_element(cint4, uint32_t(k)); */
extern cint __get_vector_element(cint2, uint32_t);
/* cint __get_vector_element(cint2, uint32_t(k)); */
#if __C7X_VEC_SIZE_BITS__ == 512
extern cfloat __get_vector_element(cfloat8, uint32_t);
/* cfloat __get_vector_element(cfloat8, uint32_t(k)); */
#endif
extern cfloat __get_vector_element(cfloat4, uint32_t);
/* cfloat __get_vector_element(cfloat4, uint32_t(k)); */
extern cfloat __get_vector_element(cfloat2, uint32_t);
/* cfloat __get_vector_element(cfloat2, uint32_t(k)); */
#if __C7X_VEC_SIZE_BITS__ == 512
extern int64_t __get_vector_element(long8, uint32_t);
/* int64_t __get_vector_element(long8, uint32_t(k)); */
#endif
extern int64_t __get_vector_element(long4, uint32_t);
/* int64_t __get_vector_element(long4, uint32_t(k)); */
extern int64_t __get_vector_element(long3, uint32_t);
/* int64_t __get_vector_element(long3, uint32_t(k)); */
extern int64_t __get_vector_element(long2, uint32_t);
/* int64_t __get_vector_element(long2, uint32_t(k)); */
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint64_t __get_vector_element(ulong8, uint32_t);
/* uint64_t __get_vector_element(ulong8, uint32_t(k)); */
#endif
extern uint64_t __get_vector_element(ulong4, uint32_t);
/* uint64_t __get_vector_element(ulong4, uint32_t(k)); */
extern uint64_t __get_vector_element(ulong3, uint32_t);
/* uint64_t __get_vector_element(ulong3, uint32_t(k)); */
extern uint64_t __get_vector_element(ulong2, uint32_t);
/* uint64_t __get_vector_element(ulong2, uint32_t(k)); */
#if __C7X_VEC_SIZE_BITS__ == 512
extern double __get_vector_element(double8, uint32_t);
/* double __get_vector_element(double8, uint32_t(k)); */
#endif
extern double __get_vector_element(double4, uint32_t);
/* double __get_vector_element(double4, uint32_t(k)); */
extern double __get_vector_element(double3, uint32_t);
/* double __get_vector_element(double3, uint32_t(k)); */
extern double __get_vector_element(double2, uint32_t);
/* double __get_vector_element(double2, uint32_t(k)); */

/*----------------------------------------------------------------------------*/
/* ID: __gmpy                                                                 */
/*----------------------------------------------------------------------------*/

/* VGMPYB */
extern uint8_t __gmpy(uint8_t, uint8_t);
extern uchar2 __gmpy(uchar2, uchar2);
extern uchar3 __gmpy(uchar3, uchar3);
extern uchar4 __gmpy(uchar4, uchar4);
extern uchar8 __gmpy(uchar8, uchar8);
extern uchar16 __gmpy(uchar16, uchar16);
extern uchar32 __gmpy(uchar32, uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __gmpy(uchar64, uchar64);
#endif

/* VGMPYW */
extern uint32_t __gmpy(uint32_t, uint32_t);
extern uint2 __gmpy(uint2, uint2);
extern uint3 __gmpy(uint3, uint3);
extern uint4 __gmpy(uint4, uint4);
extern uint8 __gmpy(uint8, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __gmpy(uint16, uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __hadd                                                                 */
/*----------------------------------------------------------------------------*/

/* VAVGNRB */
extern int8_t __hadd(int8_t, int8_t);
extern char2 __hadd(char2, char2);
extern char3 __hadd(char3, char3);
extern char4 __hadd(char4, char4);
extern char8 __hadd(char8, char8);
extern char16 __hadd(char16, char16);
extern char32 __hadd(char32, char32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __hadd(char64, char64);
#endif

/* VAVGNRUB */
extern uint8_t __hadd(uint8_t, uint8_t);
extern uchar2 __hadd(uchar2, uchar2);
extern uchar3 __hadd(uchar3, uchar3);
extern uchar4 __hadd(uchar4, uchar4);
extern uchar8 __hadd(uchar8, uchar8);
extern uchar16 __hadd(uchar16, uchar16);
extern uchar32 __hadd(uchar32, uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __hadd(uchar64, uchar64);
#endif

/* VAVGNRH */
extern int16_t __hadd(int16_t, int16_t);
extern short2 __hadd(short2, short2);
extern short3 __hadd(short3, short3);
extern short4 __hadd(short4, short4);
extern short8 __hadd(short8, short8);
extern short16 __hadd(short16, short16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __hadd(short32, short32);
#endif

/* VAVGNRUH */
extern uint16_t __hadd(uint16_t, uint16_t);
extern ushort2 __hadd(ushort2, ushort2);
extern ushort3 __hadd(ushort3, ushort3);
extern ushort4 __hadd(ushort4, ushort4);
extern ushort8 __hadd(ushort8, ushort8);
extern ushort16 __hadd(ushort16, ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __hadd(ushort32, ushort32);
#endif

/* VAVGNRW */
extern int32_t __hadd(int32_t, int32_t);
extern int2 __hadd(int2, int2);
extern int3 __hadd(int3, int3);
extern int4 __hadd(int4, int4);
extern int8 __hadd(int8, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __hadd(int16, int16);
#endif

/* VAVGNRUW */
extern uint32_t __hadd(uint32_t, uint32_t);
extern uint2 __hadd(uint2, uint2);
extern uint3 __hadd(uint3, uint3);
extern uint4 __hadd(uint4, uint4);
extern uint8 __hadd(uint8, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __hadd(uint16, uint16);
#endif

/* VAVGNRD */
extern int64_t __hadd(int64_t, int64_t);
extern long2 __hadd(long2, long2);
extern long3 __hadd(long3, long3);
extern long4 __hadd(long4, long4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __hadd(long8, long8);
#endif

/* VAVGNRUD */
extern uint64_t __hadd(uint64_t, uint64_t);
extern ulong2 __hadd(ulong2, ulong2);
extern ulong3 __hadd(ulong3, ulong3);
extern ulong4 __hadd(ulong4, ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __hadd(ulong8, ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __half_float_to_float                                                  */
/*----------------------------------------------------------------------------*/

/* VHPSP */
extern float __half_float_to_float(uint32_t);
extern float2 __half_float_to_float(uint2);
extern float3 __half_float_to_float(uint3);
extern float4 __half_float_to_float(uint4);
extern float8 __half_float_to_float(uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern float16 __half_float_to_float(uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __half_float_to_int                                                    */
/*----------------------------------------------------------------------------*/

/* VHPINT */
extern int32_t __half_float_to_int(uint32_t);
extern int2 __half_float_to_int(uint2);
extern int3 __half_float_to_int(uint3);
extern int4 __half_float_to_int(uint4);
extern int8 __half_float_to_int(uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __half_float_to_int(uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __high_char_to_short                                                   */
/*----------------------------------------------------------------------------*/

/* VBUNPKHH */
extern int16_t __high_char_to_short(char2);
extern short2 __high_char_to_short(char4);
extern short4 __high_char_to_short(char8);
extern short8 __high_char_to_short(char16);
extern short16 __high_char_to_short(char32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __high_char_to_short(char64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __high_float_to_double                                                 */
/*----------------------------------------------------------------------------*/

/* VSPDPH */
extern double __high_float_to_double(float2);
extern double2 __high_float_to_double(float4);
extern double4 __high_float_to_double(float8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern double8 __high_float_to_double(float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __high_half_int_to_float                                               */
/*----------------------------------------------------------------------------*/

/* VINTHSPH */
extern float2 __high_half_int_to_float(short4);
extern float4 __high_half_int_to_float(short8);
extern float8 __high_half_int_to_float(short16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern float16 __high_half_int_to_float(short32);
#endif

/* VINTHSPUH */
extern float2 __high_half_int_to_float(ushort4);
extern float4 __high_half_int_to_float(ushort8);
extern float8 __high_half_int_to_float(ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern float16 __high_half_int_to_float(ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __high_int_to_double                                                   */
/*----------------------------------------------------------------------------*/

/* VINTDPH */
extern double __high_int_to_double(int2);
extern double2 __high_int_to_double(int4);
extern double4 __high_int_to_double(int8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern double8 __high_int_to_double(int16);
#endif

/* VINTDPUH */
extern double __high_int_to_double(uint2);
extern double2 __high_int_to_double(uint4);
extern double4 __high_int_to_double(uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern double8 __high_int_to_double(uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __high_int_to_long                                                     */
/*----------------------------------------------------------------------------*/

/* VWUNPKDH */
extern int64_t __high_int_to_long(int2);
extern long2 __high_int_to_long(int4);
extern long4 __high_int_to_long(int8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __high_int_to_long(int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __high_short_to_int                                                    */
/*----------------------------------------------------------------------------*/

/* VHUNPKWH */
extern int32_t __high_short_to_int(short2);
extern int2 __high_short_to_int(short4);
extern int4 __high_short_to_int(short8);
extern int8 __high_short_to_int(short16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __high_short_to_int(short32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __high_uchar_to_ushort                                                 */
/*----------------------------------------------------------------------------*/

/* VBUNPKUHH */
extern uint16_t __high_uchar_to_ushort(uchar2);
extern ushort2 __high_uchar_to_ushort(uchar4);
extern ushort4 __high_uchar_to_ushort(uchar8);
extern ushort8 __high_uchar_to_ushort(uchar16);
extern ushort16 __high_uchar_to_ushort(uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __high_uchar_to_ushort(uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __high_uint_to_ulong                                                   */
/*----------------------------------------------------------------------------*/

/* VWUNPKUDH */
extern uint64_t __high_uint_to_ulong(uint2);
extern ulong2 __high_uint_to_ulong(uint4);
extern ulong4 __high_uint_to_ulong(uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __high_uint_to_ulong(uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __high_ushort_to_uint                                                  */
/*----------------------------------------------------------------------------*/

/* VHUNPKUWH */
extern uint32_t __high_ushort_to_uint(ushort2);
extern uint2 __high_ushort_to_uint(ushort4);
extern uint4 __high_ushort_to_uint(ushort8);
extern uint8 __high_ushort_to_uint(ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __high_ushort_to_uint(ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __horizontal_add                                                       */
/*----------------------------------------------------------------------------*/

/* VHADDB1D */
#if __C7X_VEC_SIZE_BITS__ == 512
extern int64_t __horizontal_add(char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern int64_t __horizontal_add(char32);
#endif

/* VHADDUB1D */
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint64_t __horizontal_add(uchar64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint64_t __horizontal_add(uchar32);
#endif

/* VHADDH1D */
#if __C7X_VEC_SIZE_BITS__ == 512
extern int64_t __horizontal_add(short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern int64_t __horizontal_add(short16);
#endif

/* VHADDUH1D */
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint64_t __horizontal_add(ushort32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint64_t __horizontal_add(ushort16);
#endif

/* VHADDW1D */
#if __C7X_VEC_SIZE_BITS__ == 512
extern int64_t __horizontal_add(int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern int64_t __horizontal_add(int8);
#endif

/* VHADDUW1D */
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint64_t __horizontal_add(uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint64_t __horizontal_add(uint8);
#endif

/* VHADDD1D */
#if __C7X_VEC_SIZE_BITS__ == 512
extern int64_t __horizontal_add(long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern int64_t __horizontal_add(long4);
#endif

/* VHADDUD1D */
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint64_t __horizontal_add(ulong8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint64_t __horizontal_add(ulong4);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __horizontal_add_skip1                                                 */
/*----------------------------------------------------------------------------*/

/* VHADDEOH2W */
#if __C7X_VEC_SIZE_BITS__ == 512
extern int2 __horizontal_add_skip1(short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern int2 __horizontal_add_skip1(short16);
#endif

/* VHADDUEOH2W */
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint2 __horizontal_add_skip1(ushort32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint2 __horizontal_add_skip1(ushort16);
#endif

/* VHADDEOH2W */
#if __C7X_VEC_SIZE_BITS__ == 512
extern cint __horizontal_add_skip1(cshort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cint __horizontal_add_skip1(cshort8);
#endif

/* VHADDEOW2D */
#if __C7X_VEC_SIZE_BITS__ == 512
extern long2 __horizontal_add_skip1(int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern long2 __horizontal_add_skip1(int8);
#endif

/* VHADDUEOW2D */
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong2 __horizontal_add_skip1(uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong2 __horizontal_add_skip1(uint8);
#endif

/* VHADDEOW2D */
#if __C7X_VEC_SIZE_BITS__ == 512
extern clong __horizontal_add_skip1(cint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern clong __horizontal_add_skip1(cint4);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __horizontal_xor                                                       */
/*----------------------------------------------------------------------------*/

/* VHXORB1B */
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16_t __horizontal_xor(char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern int16_t __horizontal_xor(char32);
#endif

/* VHXORH1H */
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16_t __horizontal_xor(short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern int16_t __horizontal_xor(short16);
#endif

/* VHXORW1W */
#if __C7X_VEC_SIZE_BITS__ == 512
extern int32_t __horizontal_xor(int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern int32_t __horizontal_xor(int8);
#endif

/* VHXORD1D */
#if __C7X_VEC_SIZE_BITS__ == 512
extern int64_t __horizontal_xor(long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern int64_t __horizontal_xor(long4);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __int40_to_int_sat                                                     */
/*----------------------------------------------------------------------------*/

/* VSATLW */
extern int64_t __int40_to_int_sat(int64_t);
extern long2 __int40_to_int_sat(long2);
extern long3 __int40_to_int_sat(long3);
extern long4 __int40_to_int_sat(long4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __int40_to_int_sat(long8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __int_to_float                                                         */
/*----------------------------------------------------------------------------*/

/* VINTSP */
extern float __int_to_float(int32_t);
extern float2 __int_to_float(int2);
extern float3 __int_to_float(int3);
extern float4 __int_to_float(int4);
extern float8 __int_to_float(int8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern float16 __int_to_float(int16);
#endif

/* VINTSPU */
extern float __int_to_float(uint32_t);
extern float2 __int_to_float(uint2);
extern float3 __int_to_float(uint3);
extern float4 __int_to_float(uint4);
extern float8 __int_to_float(uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern float16 __int_to_float(uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __int_to_half_float                                                    */
/*----------------------------------------------------------------------------*/

/* VINTHP */
extern uint32_t __int_to_half_float(int32_t);
extern uint2 __int_to_half_float(int2);
extern uint3 __int_to_half_float(int3);
extern uint4 __int_to_half_float(int4);
extern uint8 __int_to_half_float(int8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __int_to_half_float(int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __int_to_short_sat                                                     */
/*----------------------------------------------------------------------------*/

/* VSATWH */
extern int32_t __int_to_short_sat(int32_t);
extern int2 __int_to_short_sat(int2);
extern int3 __int_to_short_sat(int3);
extern int4 __int_to_short_sat(int4);
extern int8 __int_to_short_sat(int8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __int_to_short_sat(int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __leftmost_bit_detect                                                  */
/*----------------------------------------------------------------------------*/

/* VLMBDB */
extern uint8_t __leftmost_bit_detect(uint8_t, uint8_t);
extern uchar2 __leftmost_bit_detect(uchar2, uchar2);
extern uchar3 __leftmost_bit_detect(uchar3, uchar3);
extern uchar4 __leftmost_bit_detect(uchar4, uchar4);
extern uchar8 __leftmost_bit_detect(uchar8, uchar8);
extern uchar16 __leftmost_bit_detect(uchar16, uchar16);
extern uchar32 __leftmost_bit_detect(uchar32, uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __leftmost_bit_detect(uchar64, uchar64);
#endif

/* VLMBDH */
extern uint16_t __leftmost_bit_detect(uint16_t, uint16_t);
extern ushort2 __leftmost_bit_detect(ushort2, ushort2);
extern ushort3 __leftmost_bit_detect(ushort3, ushort3);
extern ushort4 __leftmost_bit_detect(ushort4, ushort4);
extern ushort8 __leftmost_bit_detect(ushort8, ushort8);
extern ushort16 __leftmost_bit_detect(ushort16, ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __leftmost_bit_detect(ushort32, ushort32);
#endif

/* VLMBDW */
extern uint32_t __leftmost_bit_detect(uint32_t, uint32_t);
extern uint2 __leftmost_bit_detect(uint2, uint2);
extern uint3 __leftmost_bit_detect(uint3, uint3);
extern uint4 __leftmost_bit_detect(uint4, uint4);
extern uint8 __leftmost_bit_detect(uint8, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __leftmost_bit_detect(uint16, uint16);
#endif

/* VLMBDD */
extern uint64_t __leftmost_bit_detect(uint64_t, uint64_t);
extern ulong2 __leftmost_bit_detect(ulong2, ulong2);
extern ulong3 __leftmost_bit_detect(ulong3, ulong3);
extern ulong4 __leftmost_bit_detect(ulong4, ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __leftmost_bit_detect(ulong8, ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __leftmost_bit_detect_one                                              */
/*----------------------------------------------------------------------------*/

/* VLMBD1B */
extern uint8_t __leftmost_bit_detect_one(uint8_t);
extern uchar2 __leftmost_bit_detect_one(uchar2);
extern uchar3 __leftmost_bit_detect_one(uchar3);
extern uchar4 __leftmost_bit_detect_one(uchar4);
extern uchar8 __leftmost_bit_detect_one(uchar8);
extern uchar16 __leftmost_bit_detect_one(uchar16);
extern uchar32 __leftmost_bit_detect_one(uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __leftmost_bit_detect_one(uchar64);
#endif

/* VLMBD1H */
extern uint16_t __leftmost_bit_detect_one(uint16_t);
extern ushort2 __leftmost_bit_detect_one(ushort2);
extern ushort3 __leftmost_bit_detect_one(ushort3);
extern ushort4 __leftmost_bit_detect_one(ushort4);
extern ushort8 __leftmost_bit_detect_one(ushort8);
extern ushort16 __leftmost_bit_detect_one(ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __leftmost_bit_detect_one(ushort32);
#endif

/* VLMBD1W */
extern uint32_t __leftmost_bit_detect_one(uint32_t);
extern uint2 __leftmost_bit_detect_one(uint2);
extern uint3 __leftmost_bit_detect_one(uint3);
extern uint4 __leftmost_bit_detect_one(uint4);
extern uint8 __leftmost_bit_detect_one(uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __leftmost_bit_detect_one(uint16);
#endif

/* VLMBD1D */
extern uint64_t __leftmost_bit_detect_one(uint64_t);
extern ulong2 __leftmost_bit_detect_one(ulong2);
extern ulong3 __leftmost_bit_detect_one(ulong3);
extern ulong4 __leftmost_bit_detect_one(ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __leftmost_bit_detect_one(ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __leftmost_bit_detect_zero                                             */
/*----------------------------------------------------------------------------*/

/* VLMBD0B */
extern uint8_t __leftmost_bit_detect_zero(uint8_t);
extern uchar2 __leftmost_bit_detect_zero(uchar2);
extern uchar3 __leftmost_bit_detect_zero(uchar3);
extern uchar4 __leftmost_bit_detect_zero(uchar4);
extern uchar8 __leftmost_bit_detect_zero(uchar8);
extern uchar16 __leftmost_bit_detect_zero(uchar16);
extern uchar32 __leftmost_bit_detect_zero(uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __leftmost_bit_detect_zero(uchar64);
#endif

/* VLMBD0H */
extern uint16_t __leftmost_bit_detect_zero(uint16_t);
extern ushort2 __leftmost_bit_detect_zero(ushort2);
extern ushort3 __leftmost_bit_detect_zero(ushort3);
extern ushort4 __leftmost_bit_detect_zero(ushort4);
extern ushort8 __leftmost_bit_detect_zero(ushort8);
extern ushort16 __leftmost_bit_detect_zero(ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __leftmost_bit_detect_zero(ushort32);
#endif

/* VLMBD0W */
extern uint32_t __leftmost_bit_detect_zero(uint32_t);
extern uint2 __leftmost_bit_detect_zero(uint2);
extern uint3 __leftmost_bit_detect_zero(uint3);
extern uint4 __leftmost_bit_detect_zero(uint4);
extern uint8 __leftmost_bit_detect_zero(uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __leftmost_bit_detect_zero(uint16);
#endif

/* VLMBD0D */
extern uint64_t __leftmost_bit_detect_zero(uint64_t);
extern ulong2 __leftmost_bit_detect_zero(ulong2);
extern ulong3 __leftmost_bit_detect_zero(ulong3);
extern ulong4 __leftmost_bit_detect_zero(ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __leftmost_bit_detect_zero(ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __logical_and                                                          */
/*----------------------------------------------------------------------------*/

/* LANDD */
extern int32_t __logical_and(int64_t, int64_t);

/*----------------------------------------------------------------------------*/
/* ID: __logical_andn                                                         */
/*----------------------------------------------------------------------------*/

/* LANDND */
extern int32_t __logical_andn(int64_t, int64_t);

/*----------------------------------------------------------------------------*/
/* ID: __logical_or                                                           */
/*----------------------------------------------------------------------------*/

/* LORD */
extern int32_t __logical_or(int64_t, int64_t);

/*----------------------------------------------------------------------------*/
/* ID: __long_to_int40_sat                                                    */
/*----------------------------------------------------------------------------*/

/* VSATDL */
extern int64_t __long_to_int40_sat(int64_t);
extern long2 __long_to_int40_sat(long2);
extern long3 __long_to_int40_sat(long3);
extern long4 __long_to_int40_sat(long4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __long_to_int40_sat(long8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __long_to_int_sat                                                      */
/*----------------------------------------------------------------------------*/

/* VSATDW */
extern int64_t __long_to_int_sat(int64_t);
extern long2 __long_to_int_sat(long2);
extern long3 __long_to_int_sat(long3);
extern long4 __long_to_int_sat(long4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __long_to_int_sat(long8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __low_char_to_short                                                    */
/*----------------------------------------------------------------------------*/

/* VBUNPKHL */
extern int16_t __low_char_to_short(char2);
extern short2 __low_char_to_short(char4);
extern short4 __low_char_to_short(char8);
extern short8 __low_char_to_short(char16);
extern short16 __low_char_to_short(char32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __low_char_to_short(char64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __low_float_to_double                                                  */
/*----------------------------------------------------------------------------*/

/* VSPDPL */
extern double __low_float_to_double(float2);
extern double2 __low_float_to_double(float4);
extern double4 __low_float_to_double(float8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern double8 __low_float_to_double(float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __low_half_int_to_float                                                */
/*----------------------------------------------------------------------------*/

/* VINTHSPL */
extern float2 __low_half_int_to_float(short4);
extern float4 __low_half_int_to_float(short8);
extern float8 __low_half_int_to_float(short16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern float16 __low_half_int_to_float(short32);
#endif

/* VINTHSPUL */
extern float2 __low_half_int_to_float(ushort4);
extern float4 __low_half_int_to_float(ushort8);
extern float8 __low_half_int_to_float(ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern float16 __low_half_int_to_float(ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __low_int_to_double                                                    */
/*----------------------------------------------------------------------------*/

/* VINTDPL */
extern double __low_int_to_double(int2);
extern double2 __low_int_to_double(int4);
extern double4 __low_int_to_double(int8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern double8 __low_int_to_double(int16);
#endif

/* VINTDPUL */
extern double __low_int_to_double(uint2);
extern double2 __low_int_to_double(uint4);
extern double4 __low_int_to_double(uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern double8 __low_int_to_double(uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __low_int_to_long                                                      */
/*----------------------------------------------------------------------------*/

/* VWUNPKDL */
extern int64_t __low_int_to_long(int2);
extern long2 __low_int_to_long(int4);
extern long4 __low_int_to_long(int8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __low_int_to_long(int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __low_short_to_int                                                     */
/*----------------------------------------------------------------------------*/

/* VHUNPKWL */
extern int32_t __low_short_to_int(short2);
extern int2 __low_short_to_int(short4);
extern int4 __low_short_to_int(short8);
extern int8 __low_short_to_int(short16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __low_short_to_int(short32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __low_uchar_to_ushort                                                  */
/*----------------------------------------------------------------------------*/

/* VBUNPKUHL */
extern uint16_t __low_uchar_to_ushort(uchar2);
extern ushort2 __low_uchar_to_ushort(uchar4);
extern ushort4 __low_uchar_to_ushort(uchar8);
extern ushort8 __low_uchar_to_ushort(uchar16);
extern ushort16 __low_uchar_to_ushort(uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __low_uchar_to_ushort(uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __low_uint_to_ulong                                                    */
/*----------------------------------------------------------------------------*/

/* VWUNPKUDL */
extern uint64_t __low_uint_to_ulong(uint2);
extern ulong2 __low_uint_to_ulong(uint4);
extern ulong4 __low_uint_to_ulong(uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __low_uint_to_ulong(uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __low_ushort_to_uint                                                   */
/*----------------------------------------------------------------------------*/

/* VHUNPKUWL */
extern uint32_t __low_ushort_to_uint(ushort2);
extern uint2 __low_ushort_to_uint(ushort4);
extern uint4 __low_ushort_to_uint(ushort8);
extern uint8 __low_ushort_to_uint(ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __low_ushort_to_uint(ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __max                                                                  */
/*----------------------------------------------------------------------------*/

/* VMAXB */
extern int8_t __max(int8_t, int8_t);
extern char2 __max(char2, char2);
extern char3 __max(char3, char3);
extern char4 __max(char4, char4);
extern char8 __max(char8, char8);
extern char16 __max(char16, char16);
extern char32 __max(char32, char32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __max(char64, char64);
#endif

/* VMAXUB */
extern uint8_t __max(uint8_t, uint8_t);
extern uchar2 __max(uchar2, uchar2);
extern uchar3 __max(uchar3, uchar3);
extern uchar4 __max(uchar4, uchar4);
extern uchar8 __max(uchar8, uchar8);
extern uchar16 __max(uchar16, uchar16);
extern uchar32 __max(uchar32, uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __max(uchar64, uchar64);
#endif

/* VMAXH */
extern int16_t __max(int16_t, int16_t);
extern short2 __max(short2, short2);
extern short3 __max(short3, short3);
extern short4 __max(short4, short4);
extern short8 __max(short8, short8);
extern short16 __max(short16, short16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __max(short32, short32);
#endif

/* VMAXUH */
extern uint16_t __max(uint16_t, uint16_t);
extern ushort2 __max(ushort2, ushort2);
extern ushort3 __max(ushort3, ushort3);
extern ushort4 __max(ushort4, ushort4);
extern ushort8 __max(ushort8, ushort8);
extern ushort16 __max(ushort16, ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __max(ushort32, ushort32);
#endif

/* VMAXW */
extern int32_t __max(int32_t, int32_t);
extern int2 __max(int2, int2);
extern int3 __max(int3, int3);
extern int4 __max(int4, int4);
extern int8 __max(int8, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __max(int16, int16);
#endif

/* VMAXUW */
extern uint32_t __max(uint32_t, uint32_t);
extern uint2 __max(uint2, uint2);
extern uint3 __max(uint3, uint3);
extern uint4 __max(uint4, uint4);
extern uint8 __max(uint8, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __max(uint16, uint16);
#endif

/* VMAXSP */
extern float __max(float, float);
extern float2 __max(float2, float2);
extern float3 __max(float3, float3);
extern float4 __max(float4, float4);
extern float8 __max(float8, float8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern float16 __max(float16, float16);
#endif

/* VMAXD */
extern int64_t __max(int64_t, int64_t);
extern long2 __max(long2, long2);
extern long3 __max(long3, long3);
extern long4 __max(long4, long4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __max(long8, long8);
#endif

/* VMAXUD */
extern uint64_t __max(uint64_t, uint64_t);
extern ulong2 __max(ulong2, ulong2);
extern ulong3 __max(ulong3, ulong3);
extern ulong4 __max(ulong4, ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __max(ulong8, ulong8);
#endif

/* VMAXDP */
extern double __max(double, double);
extern double2 __max(double2, double2);
extern double3 __max(double3, double3);
extern double4 __max(double4, double4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern double8 __max(double8, double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __max_circ                                                             */
/*----------------------------------------------------------------------------*/

/* VCMAXB */
extern int8_t __max_circ(int8_t, int8_t);
extern char2 __max_circ(char2, char2);
extern char3 __max_circ(char3, char3);
extern char4 __max_circ(char4, char4);
extern char8 __max_circ(char8, char8);
extern char16 __max_circ(char16, char16);
extern char32 __max_circ(char32, char32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __max_circ(char64, char64);
#endif

/* VCMAXH */
extern int16_t __max_circ(int16_t, int16_t);
extern short2 __max_circ(short2, short2);
extern short3 __max_circ(short3, short3);
extern short4 __max_circ(short4, short4);
extern short8 __max_circ(short8, short8);
extern short16 __max_circ(short16, short16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __max_circ(short32, short32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __max_circ_bool                                                        */
/*----------------------------------------------------------------------------*/

/* VCMAXPB */
extern void __max_circ_bool(char2, char2&, bool2&);
extern void __max_circ_bool(char3, char3&, bool3&);
extern void __max_circ_bool(char4, char4&, bool4&);
extern void __max_circ_bool(char8, char8&, bool8&);
extern void __max_circ_bool(char16, char16&, bool16&);
extern void __max_circ_bool(char32, char32&, bool32&);
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __max_circ_bool(char64, char64&, bool64&);
#endif

/* VCMAXPH */
extern void __max_circ_bool(short2, short2&, bool2&);
extern void __max_circ_bool(short3, short3&, bool3&);
extern void __max_circ_bool(short4, short4&, bool4&);
extern void __max_circ_bool(short8, short8&, bool8&);
extern void __max_circ_bool(short16, short16&, bool16&);
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __max_circ_bool(short32, short32&, bool32&);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __max_index_bool                                                       */
/*----------------------------------------------------------------------------*/

/* VMAXPB */
extern void __max_index_bool(char2, char2&, bool2&);
extern void __max_index_bool(char3, char3&, bool3&);
extern void __max_index_bool(char4, char4&, bool4&);
extern void __max_index_bool(char8, char8&, bool8&);
extern void __max_index_bool(char16, char16&, bool16&);
extern void __max_index_bool(char32, char32&, bool32&);
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __max_index_bool(char64, char64&, bool64&);
#endif

/* VMAXUPB */
extern void __max_index_bool(uchar2, uchar2&, bool2&);
extern void __max_index_bool(uchar3, uchar3&, bool3&);
extern void __max_index_bool(uchar4, uchar4&, bool4&);
extern void __max_index_bool(uchar8, uchar8&, bool8&);
extern void __max_index_bool(uchar16, uchar16&, bool16&);
extern void __max_index_bool(uchar32, uchar32&, bool32&);
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __max_index_bool(uchar64, uchar64&, bool64&);
#endif

/* VMAXPH */
extern void __max_index_bool(short2, short2&, bool2&);
extern void __max_index_bool(short3, short3&, bool3&);
extern void __max_index_bool(short4, short4&, bool4&);
extern void __max_index_bool(short8, short8&, bool8&);
extern void __max_index_bool(short16, short16&, bool16&);
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __max_index_bool(short32, short32&, bool32&);
#endif

/* VMAXUPH */
extern void __max_index_bool(ushort2, ushort2&, bool2&);
extern void __max_index_bool(ushort3, ushort3&, bool3&);
extern void __max_index_bool(ushort4, ushort4&, bool4&);
extern void __max_index_bool(ushort8, ushort8&, bool8&);
extern void __max_index_bool(ushort16, ushort16&, bool16&);
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __max_index_bool(ushort32, ushort32&, bool32&);
#endif

/* VMAXPW */
extern void __max_index_bool(int2, int2&, bool2&);
extern void __max_index_bool(int3, int3&, bool3&);
extern void __max_index_bool(int4, int4&, bool4&);
extern void __max_index_bool(int8, int8&, bool8&);
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __max_index_bool(int16, int16&, bool16&);
#endif

/* VMAXUPW */
extern void __max_index_bool(uint2, uint2&, bool2&);
extern void __max_index_bool(uint3, uint3&, bool3&);
extern void __max_index_bool(uint4, uint4&, bool4&);
extern void __max_index_bool(uint8, uint8&, bool8&);
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __max_index_bool(uint16, uint16&, bool16&);
#endif

/* VMAXPD */
extern void __max_index_bool(long2, long2&, bool2&);
extern void __max_index_bool(long3, long3&, bool3&);
extern void __max_index_bool(long4, long4&, bool4&);
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __max_index_bool(long8, long8&, bool8&);
#endif

/* VMAXUPD */
extern void __max_index_bool(ulong2, ulong2&, bool2&);
extern void __max_index_bool(ulong3, ulong3&, bool3&);
extern void __max_index_bool(ulong4, ulong4&, bool4&);
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __max_index_bool(ulong8, ulong8&, bool8&);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __min                                                                  */
/*----------------------------------------------------------------------------*/

/* VMINB */
extern int8_t __min(int8_t, int8_t);
extern char2 __min(char2, char2);
extern char3 __min(char3, char3);
extern char4 __min(char4, char4);
extern char8 __min(char8, char8);
extern char16 __min(char16, char16);
extern char32 __min(char32, char32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __min(char64, char64);
#endif

/* VMINUB */
extern uint8_t __min(uint8_t, uint8_t);
extern uchar2 __min(uchar2, uchar2);
extern uchar3 __min(uchar3, uchar3);
extern uchar4 __min(uchar4, uchar4);
extern uchar8 __min(uchar8, uchar8);
extern uchar16 __min(uchar16, uchar16);
extern uchar32 __min(uchar32, uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __min(uchar64, uchar64);
#endif

/* VMINH */
extern int16_t __min(int16_t, int16_t);
extern short2 __min(short2, short2);
extern short3 __min(short3, short3);
extern short4 __min(short4, short4);
extern short8 __min(short8, short8);
extern short16 __min(short16, short16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __min(short32, short32);
#endif

/* VMINUH */
extern uint16_t __min(uint16_t, uint16_t);
extern ushort2 __min(ushort2, ushort2);
extern ushort3 __min(ushort3, ushort3);
extern ushort4 __min(ushort4, ushort4);
extern ushort8 __min(ushort8, ushort8);
extern ushort16 __min(ushort16, ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __min(ushort32, ushort32);
#endif

/* VMINW */
extern int32_t __min(int32_t, int32_t);
extern int2 __min(int2, int2);
extern int3 __min(int3, int3);
extern int4 __min(int4, int4);
extern int8 __min(int8, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __min(int16, int16);
#endif

/* VMINUW */
extern uint32_t __min(uint32_t, uint32_t);
extern uint2 __min(uint2, uint2);
extern uint3 __min(uint3, uint3);
extern uint4 __min(uint4, uint4);
extern uint8 __min(uint8, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __min(uint16, uint16);
#endif

/* VMINSP */
extern float __min(float, float);
extern float2 __min(float2, float2);
extern float3 __min(float3, float3);
extern float4 __min(float4, float4);
extern float8 __min(float8, float8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern float16 __min(float16, float16);
#endif

/* VMIND */
extern int64_t __min(int64_t, int64_t);
extern long2 __min(long2, long2);
extern long3 __min(long3, long3);
extern long4 __min(long4, long4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __min(long8, long8);
#endif

/* VMINUD */
extern uint64_t __min(uint64_t, uint64_t);
extern ulong2 __min(ulong2, ulong2);
extern ulong3 __min(ulong3, ulong3);
extern ulong4 __min(ulong4, ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __min(ulong8, ulong8);
#endif

/* VMINDP */
extern double __min(double, double);
extern double2 __min(double2, double2);
extern double3 __min(double3, double3);
extern double4 __min(double4, double4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern double8 __min(double8, double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __min_index_bool                                                       */
/*----------------------------------------------------------------------------*/

/* VMINPB */
extern void __min_index_bool(char2, char2&, bool2&);
extern void __min_index_bool(char3, char3&, bool3&);
extern void __min_index_bool(char4, char4&, bool4&);
extern void __min_index_bool(char8, char8&, bool8&);
extern void __min_index_bool(char16, char16&, bool16&);
extern void __min_index_bool(char32, char32&, bool32&);
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __min_index_bool(char64, char64&, bool64&);
#endif

/* VMINUPB */
extern void __min_index_bool(uchar2, uchar2&, bool2&);
extern void __min_index_bool(uchar3, uchar3&, bool3&);
extern void __min_index_bool(uchar4, uchar4&, bool4&);
extern void __min_index_bool(uchar8, uchar8&, bool8&);
extern void __min_index_bool(uchar16, uchar16&, bool16&);
extern void __min_index_bool(uchar32, uchar32&, bool32&);
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __min_index_bool(uchar64, uchar64&, bool64&);
#endif

/* VMINPH */
extern void __min_index_bool(short2, short2&, bool2&);
extern void __min_index_bool(short3, short3&, bool3&);
extern void __min_index_bool(short4, short4&, bool4&);
extern void __min_index_bool(short8, short8&, bool8&);
extern void __min_index_bool(short16, short16&, bool16&);
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __min_index_bool(short32, short32&, bool32&);
#endif

/* VMINUPH */
extern void __min_index_bool(ushort2, ushort2&, bool2&);
extern void __min_index_bool(ushort3, ushort3&, bool3&);
extern void __min_index_bool(ushort4, ushort4&, bool4&);
extern void __min_index_bool(ushort8, ushort8&, bool8&);
extern void __min_index_bool(ushort16, ushort16&, bool16&);
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __min_index_bool(ushort32, ushort32&, bool32&);
#endif

/* VMINPW */
extern void __min_index_bool(int2, int2&, bool2&);
extern void __min_index_bool(int3, int3&, bool3&);
extern void __min_index_bool(int4, int4&, bool4&);
extern void __min_index_bool(int8, int8&, bool8&);
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __min_index_bool(int16, int16&, bool16&);
#endif

/* VMINUPW */
extern void __min_index_bool(uint2, uint2&, bool2&);
extern void __min_index_bool(uint3, uint3&, bool3&);
extern void __min_index_bool(uint4, uint4&, bool4&);
extern void __min_index_bool(uint8, uint8&, bool8&);
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __min_index_bool(uint16, uint16&, bool16&);
#endif

/* VMINPD */
extern void __min_index_bool(long2, long2&, bool2&);
extern void __min_index_bool(long3, long3&, bool3&);
extern void __min_index_bool(long4, long4&, bool4&);
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __min_index_bool(long8, long8&, bool8&);
#endif

/* VMINUPD */
extern void __min_index_bool(ulong2, ulong2&, bool2&);
extern void __min_index_bool(ulong3, ulong3&, bool3&);
extern void __min_index_bool(ulong4, ulong4&, bool4&);
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __min_index_bool(ulong8, ulong8&, bool8&);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __mpy_ext                                                              */
/*----------------------------------------------------------------------------*/

/* VMPYSUBH */
extern int16_t __mpy_ext(int8_t, uint8_t);
extern short2 __mpy_ext(char2, uchar2);
extern short3 __mpy_ext(char3, uchar3);
extern short4 __mpy_ext(char4, uchar4);
extern short8 __mpy_ext(char8, uchar8);
extern short16 __mpy_ext(char16, uchar16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __mpy_ext(char32, uchar32);
#endif

/* VMPYUBH */
extern uint16_t __mpy_ext(uint8_t, uint8_t);
extern ushort2 __mpy_ext(uchar2, uchar2);
extern ushort3 __mpy_ext(uchar3, uchar3);
extern ushort4 __mpy_ext(uchar4, uchar4);
extern ushort8 __mpy_ext(uchar8, uchar8);
extern ushort16 __mpy_ext(uchar16, uchar16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __mpy_ext(uchar32, uchar32);
#endif

/* MPYHW, VMPYHW */
extern int32_t __mpy_ext(int16_t, int16_t);
extern int2 __mpy_ext(short2, short2);
extern int3 __mpy_ext(short3, short3);
extern int4 __mpy_ext(short4, short4);
extern int8 __mpy_ext(short8, short8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __mpy_ext(short16, short16);
#endif

/* MPYSUHW, VMPYSUHW */
extern int32_t __mpy_ext(int16_t, uint16_t);
extern int2 __mpy_ext(short2, ushort2);
extern int3 __mpy_ext(short3, ushort3);
extern int4 __mpy_ext(short4, ushort4);
extern int8 __mpy_ext(short8, ushort8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __mpy_ext(short16, ushort16);
#endif

/* MPYUHW, VMPYUHW */
extern uint32_t __mpy_ext(uint16_t, uint16_t);
extern uint2 __mpy_ext(ushort2, ushort2);
extern uint3 __mpy_ext(ushort3, ushort3);
extern uint4 __mpy_ext(ushort4, ushort4);
extern uint8 __mpy_ext(ushort8, ushort8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __mpy_ext(ushort16, ushort16);
#endif

/* VMPYWD */
extern int64_t __mpy_ext(int32_t, int32_t);
extern long2 __mpy_ext(int2, int2);
extern long3 __mpy_ext(int3, int3);
extern long4 __mpy_ext(int4, int4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __mpy_ext(int8, int8);
#endif

/* VMPYSUWD */
extern int64_t __mpy_ext(int32_t, uint32_t);
extern long2 __mpy_ext(int2, uint2);
extern long3 __mpy_ext(int3, uint3);
extern long4 __mpy_ext(int4, uint4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __mpy_ext(int8, uint8);
#endif

/* VMPYUWD */
extern uint64_t __mpy_ext(uint32_t, uint32_t);
extern ulong2 __mpy_ext(uint2, uint2);
extern ulong3 __mpy_ext(uint3, uint3);
extern ulong4 __mpy_ext(uint4, uint4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __mpy_ext(uint8, uint8);
#endif

/* VMPYSP2DP */
extern double __mpy_ext(float, float);
extern double2 __mpy_ext(float2, float2);
extern double3 __mpy_ext(float3, float3);
extern double4 __mpy_ext(float4, float4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern double8 __mpy_ext(float8, float8);
#endif

/* VMPYUDQ */
extern ulong2 __mpy_ext(uint64_t, uint64_t);
extern ulong4 __mpy_ext(ulong2, ulong2);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __mpy_ext(ulong4, ulong4);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __mpy_fx                                                               */
/*----------------------------------------------------------------------------*/

/* C6MPY2IR */
extern int2 __mpy_fx(short2, int32_t);

/*----------------------------------------------------------------------------*/
/* ID: __mpy_sat                                                              */
/*----------------------------------------------------------------------------*/

/* VSMPYWW */
extern int32_t __mpy_sat(int32_t, int32_t);
extern int2 __mpy_sat(int2, int2);
extern int3 __mpy_sat(int3, int3);
extern int4 __mpy_sat(int4, int4);
extern int8 __mpy_sat(int8, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __mpy_sat(int16, int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __mpy_sat_ext                                                          */
/*----------------------------------------------------------------------------*/

/* SMPYHW, VSMPYHW */
extern int32_t __mpy_sat_ext(int16_t, int16_t);
extern int2 __mpy_sat_ext(short2, short2);
extern int3 __mpy_sat_ext(short3, short3);
extern int4 __mpy_sat_ext(short4, short4);
extern int8 __mpy_sat_ext(short8, short8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __mpy_sat_ext(short16, short16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __mpy_sat_fxq15                                                        */
/*----------------------------------------------------------------------------*/

/* VSMPYR1HH */
extern int16_t __mpy_sat_fxq15(int16_t, int16_t);
extern short2 __mpy_sat_fxq15(short2, short2);
extern short3 __mpy_sat_fxq15(short3, short3);
extern short4 __mpy_sat_fxq15(short4, short4);
extern short8 __mpy_sat_fxq15(short8, short8);
extern short16 __mpy_sat_fxq15(short16, short16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __mpy_sat_fxq15(short32, short32);
#endif

/* VSMPYRSUHH */
extern int16_t __mpy_sat_fxq15(int16_t, uint16_t);
extern short2 __mpy_sat_fxq15(short2, ushort2);
extern short3 __mpy_sat_fxq15(short3, ushort3);
extern short4 __mpy_sat_fxq15(short4, ushort4);
extern short8 __mpy_sat_fxq15(short8, ushort8);
extern short16 __mpy_sat_fxq15(short16, ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __mpy_sat_fxq15(short32, ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __mpy_sat_fxq16                                                        */
/*----------------------------------------------------------------------------*/

/* VSMPYRUHH */
extern uint16_t __mpy_sat_fxq16(uint16_t, uint16_t);
extern ushort2 __mpy_sat_fxq16(ushort2, ushort2);
extern ushort3 __mpy_sat_fxq16(ushort3, ushort3);
extern ushort4 __mpy_sat_fxq16(ushort4, ushort4);
extern ushort8 __mpy_sat_fxq16(ushort8, ushort8);
extern ushort16 __mpy_sat_fxq16(ushort16, ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __mpy_sat_fxq16(ushort32, ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __mpy_sat_fxq16_15                                                     */
/*----------------------------------------------------------------------------*/

/* VSMPYR17WW */
extern int32_t __mpy_sat_fxq16_15(int32_t, int32_t);
extern int2 __mpy_sat_fxq16_15(int2, int2);
extern int3 __mpy_sat_fxq16_15(int3, int3);
extern int4 __mpy_sat_fxq16_15(int4, int4);
extern int8 __mpy_sat_fxq16_15(int8, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __mpy_sat_fxq16_15(int16, int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __mpy_sat_fxq31                                                        */
/*----------------------------------------------------------------------------*/

/* VSMPYR1WW */
extern int32_t __mpy_sat_fxq31(int32_t, int32_t);
extern int2 __mpy_sat_fxq31(int2, int2);
extern int3 __mpy_sat_fxq31(int3, int3);
extern int4 __mpy_sat_fxq31(int4, int4);
extern int8 __mpy_sat_fxq31(int8, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __mpy_sat_fxq31(int16, int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __mpy_xor                                                              */
/*----------------------------------------------------------------------------*/

/* VXORMPYW */
extern uint32_t __mpy_xor(uint32_t, uint32_t);
extern uint2 __mpy_xor(uint2, uint2);
extern uint3 __mpy_xor(uint3, uint3);
extern uint4 __mpy_xor(uint4, uint4);
extern uint8 __mpy_xor(uint8, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __mpy_xor(uint16, uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __nand                                                                 */
/*----------------------------------------------------------------------------*/

/* NANDD, NANDW, VNANDW */
extern int8_t __nand(int8_t, int8_t);
extern char2 __nand(char2, char2);
extern char3 __nand(char3, char3);
extern char4 __nand(char4, char4);
extern char8 __nand(char8, char8);
extern char16 __nand(char16, char16);
extern char32 __nand(char32, char32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __nand(char64, char64);
#endif
extern uint8_t __nand(uint8_t, uint8_t);
extern uchar2 __nand(uchar2, uchar2);
extern uchar3 __nand(uchar3, uchar3);
extern uchar4 __nand(uchar4, uchar4);
extern uchar8 __nand(uchar8, uchar8);
extern uchar16 __nand(uchar16, uchar16);
extern uchar32 __nand(uchar32, uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __nand(uchar64, uchar64);
#endif
extern int16_t __nand(int16_t, int16_t);
extern short2 __nand(short2, short2);
extern short3 __nand(short3, short3);
extern short4 __nand(short4, short4);
extern short8 __nand(short8, short8);
extern short16 __nand(short16, short16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __nand(short32, short32);
#endif
extern uint16_t __nand(uint16_t, uint16_t);
extern ushort2 __nand(ushort2, ushort2);
extern ushort3 __nand(ushort3, ushort3);
extern ushort4 __nand(ushort4, ushort4);
extern ushort8 __nand(ushort8, ushort8);
extern ushort16 __nand(ushort16, ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __nand(ushort32, ushort32);
#endif
extern int32_t __nand(int32_t, int32_t);
extern int2 __nand(int2, int2);
extern int3 __nand(int3, int3);
extern int4 __nand(int4, int4);
extern int8 __nand(int8, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __nand(int16, int16);
#endif
extern uint32_t __nand(uint32_t, uint32_t);
extern uint2 __nand(uint2, uint2);
extern uint3 __nand(uint3, uint3);
extern uint4 __nand(uint4, uint4);
extern uint8 __nand(uint8, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __nand(uint16, uint16);
#endif

/* NANDD, VNANDW */
extern int64_t __nand(int64_t, int64_t);
/* int64_t __nand(int64_t, int64_t(k)); */
extern long2 __nand(long2, long2);
extern long3 __nand(long3, long3);
extern long4 __nand(long4, long4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __nand(long8, long8);
#endif
extern uint64_t __nand(uint64_t, uint64_t);
/* uint64_t __nand(uint64_t, uint64_t(k)); */
extern ulong2 __nand(ulong2, ulong2);
extern ulong3 __nand(ulong3, ulong3);
extern ulong4 __nand(ulong4, ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __nand(ulong8, ulong8);
#endif

/* NAND */
extern bool2 __nand(bool2, bool2);
extern bool3 __nand(bool3, bool3);
extern bool4 __nand(bool4, bool4);
extern bool8 __nand(bool8, bool8);
extern bool16 __nand(bool16, bool16);
extern bool32 __nand(bool32, bool32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern bool64 __nand(bool64, bool64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __negate                                                               */
/*----------------------------------------------------------------------------*/

/* NOT */
extern bool2 __negate(bool2);
extern bool3 __negate(bool3);
extern bool4 __negate(bool4);
extern bool8 __negate(bool8);
extern bool16 __negate(bool16);
extern bool32 __negate(bool32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern bool64 __negate(bool64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __nor                                                                  */
/*----------------------------------------------------------------------------*/

/* NORD, NORW, VNORW */
extern int8_t __nor(int8_t, int8_t);
extern char2 __nor(char2, char2);
extern char3 __nor(char3, char3);
extern char4 __nor(char4, char4);
extern char8 __nor(char8, char8);
extern char16 __nor(char16, char16);
extern char32 __nor(char32, char32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __nor(char64, char64);
#endif
extern uint8_t __nor(uint8_t, uint8_t);
extern uchar2 __nor(uchar2, uchar2);
extern uchar3 __nor(uchar3, uchar3);
extern uchar4 __nor(uchar4, uchar4);
extern uchar8 __nor(uchar8, uchar8);
extern uchar16 __nor(uchar16, uchar16);
extern uchar32 __nor(uchar32, uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __nor(uchar64, uchar64);
#endif
extern int16_t __nor(int16_t, int16_t);
extern short2 __nor(short2, short2);
extern short3 __nor(short3, short3);
extern short4 __nor(short4, short4);
extern short8 __nor(short8, short8);
extern short16 __nor(short16, short16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __nor(short32, short32);
#endif
extern uint16_t __nor(uint16_t, uint16_t);
extern ushort2 __nor(ushort2, ushort2);
extern ushort3 __nor(ushort3, ushort3);
extern ushort4 __nor(ushort4, ushort4);
extern ushort8 __nor(ushort8, ushort8);
extern ushort16 __nor(ushort16, ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __nor(ushort32, ushort32);
#endif
extern int32_t __nor(int32_t, int32_t);
extern int2 __nor(int2, int2);
extern int3 __nor(int3, int3);
extern int4 __nor(int4, int4);
extern int8 __nor(int8, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __nor(int16, int16);
#endif
extern uint32_t __nor(uint32_t, uint32_t);
extern uint2 __nor(uint2, uint2);
extern uint3 __nor(uint3, uint3);
extern uint4 __nor(uint4, uint4);
extern uint8 __nor(uint8, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __nor(uint16, uint16);
#endif

/* NORD, VNORW */
extern int64_t __nor(int64_t, int64_t);
/* int64_t __nor(int64_t, int64_t(k)); */
extern long2 __nor(long2, long2);
extern long3 __nor(long3, long3);
extern long4 __nor(long4, long4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __nor(long8, long8);
#endif
extern uint64_t __nor(uint64_t, uint64_t);
/* uint64_t __nor(uint64_t, uint64_t(k)); */
extern ulong2 __nor(ulong2, ulong2);
extern ulong3 __nor(ulong3, ulong3);
extern ulong4 __nor(ulong4, ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __nor(ulong8, ulong8);
#endif

/* NOR */
extern bool2 __nor(bool2, bool2);
extern bool3 __nor(bool3, bool3);
extern bool4 __nor(bool4, bool4);
extern bool8 __nor(bool8, bool8);
extern bool16 __nor(bool16, bool16);
extern bool32 __nor(bool32, bool32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern bool64 __nor(bool64, bool64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __norm                                                                 */
/*----------------------------------------------------------------------------*/

/* VNORMB */
extern int8_t __norm(int8_t);
extern char2 __norm(char2);
extern char3 __norm(char3);
extern char4 __norm(char4);
extern char8 __norm(char8);
extern char16 __norm(char16);
extern char32 __norm(char32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __norm(char64);
#endif

/* VNORMH */
extern int16_t __norm(int16_t);
extern short2 __norm(short2);
extern short3 __norm(short3);
extern short4 __norm(short4);
extern short8 __norm(short8);
extern short16 __norm(short16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __norm(short32);
#endif

/* VNORMW */
extern int32_t __norm(int32_t);
extern int2 __norm(int2);
extern int3 __norm(int3);
extern int4 __norm(int4);
extern int8 __norm(int8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __norm(int16);
#endif

/* VNORMD */
extern int64_t __norm(int64_t);
extern long2 __norm(long2);
extern long3 __norm(long3);
extern long4 __norm(long4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __norm(long8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __norm_and_shift_elem_pair                                             */
/*----------------------------------------------------------------------------*/

/* VNORM2UH */
extern ushort2 __norm_and_shift_elem_pair(ushort2);
extern ushort4 __norm_and_shift_elem_pair(ushort4);
extern ushort8 __norm_and_shift_elem_pair(ushort8);
extern ushort16 __norm_and_shift_elem_pair(ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __norm_and_shift_elem_pair(ushort32);
#endif

/* VNORM2UW */
extern uint2 __norm_and_shift_elem_pair(uint2);
extern uint4 __norm_and_shift_elem_pair(uint4);
extern uint8 __norm_and_shift_elem_pair(uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __norm_and_shift_elem_pair(uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __or                                                                   */
/*----------------------------------------------------------------------------*/

/* OR */
extern bool2 __or(bool2, bool2);
extern bool3 __or(bool3, bool3);
extern bool4 __or(bool4, bool4);
extern bool8 __or(bool8, bool8);
extern bool16 __or(bool16, bool16);
extern bool32 __or(bool32, bool32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern bool64 __or(bool64, bool64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __orn                                                                  */
/*----------------------------------------------------------------------------*/

/* ORND, ORNW, VORNW */
extern int8_t __orn(int8_t, int8_t);
/* int8_t __orn(int8_t, int8_t(k)); */
extern char2 __orn(char2, char2);
/* char2 __orn(char2, char2(k)); */
extern char3 __orn(char3, char3);
/* char3 __orn(char3, char3(k)); */
extern char4 __orn(char4, char4);
/* char4 __orn(char4, char4(k)); */
extern char8 __orn(char8, char8);
extern char16 __orn(char16, char16);
extern char32 __orn(char32, char32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __orn(char64, char64);
#endif
extern uint8_t __orn(uint8_t, uint8_t);
/* uint8_t __orn(uint8_t, uint8_t(k)); */
extern uchar2 __orn(uchar2, uchar2);
/* uchar2 __orn(uchar2, uchar2(k)); */
extern uchar3 __orn(uchar3, uchar3);
/* uchar3 __orn(uchar3, uchar3(k)); */
extern uchar4 __orn(uchar4, uchar4);
/* uchar4 __orn(uchar4, uchar4(k)); */
extern uchar8 __orn(uchar8, uchar8);
extern uchar16 __orn(uchar16, uchar16);
extern uchar32 __orn(uchar32, uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __orn(uchar64, uchar64);
#endif
extern int16_t __orn(int16_t, int16_t);
/* int16_t __orn(int16_t, int16_t(k)); */
extern short2 __orn(short2, short2);
/* short2 __orn(short2, short2(k)); */
extern short3 __orn(short3, short3);
extern short4 __orn(short4, short4);
extern short8 __orn(short8, short8);
extern short16 __orn(short16, short16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __orn(short32, short32);
#endif
extern uint16_t __orn(uint16_t, uint16_t);
/* uint16_t __orn(uint16_t, uint16_t(k)); */
extern ushort2 __orn(ushort2, ushort2);
/* ushort2 __orn(ushort2, ushort2(k)); */
extern ushort3 __orn(ushort3, ushort3);
extern ushort4 __orn(ushort4, ushort4);
extern ushort8 __orn(ushort8, ushort8);
extern ushort16 __orn(ushort16, ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __orn(ushort32, ushort32);
#endif
extern int32_t __orn(int32_t, int32_t);
/* int32_t __orn(int32_t, int32_t(k)); */
extern int2 __orn(int2, int2);
/* int2 __orn(int2, int2(k)); */
extern int3 __orn(int3, int3);
/* int3 __orn(int3, int3(k)); */
extern int4 __orn(int4, int4);
/* int4 __orn(int4, int4(k)); */
extern int8 __orn(int8, int8);
/* int8 __orn(int8, int8(k)); */
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __orn(int16, int16);
/* int16 __orn(int16, int16(k)); */
#endif
extern uint32_t __orn(uint32_t, uint32_t);
/* uint32_t __orn(uint32_t, uint32_t(k)); */
extern uint2 __orn(uint2, uint2);
/* uint2 __orn(uint2, uint2(k)); */
extern uint3 __orn(uint3, uint3);
/* uint3 __orn(uint3, uint3(k)); */
extern uint4 __orn(uint4, uint4);
/* uint4 __orn(uint4, uint4(k)); */
extern uint8 __orn(uint8, uint8);
/* uint8 __orn(uint8, uint8(k)); */
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __orn(uint16, uint16);
/* uint16 __orn(uint16, uint16(k)); */
#endif

/* ORND, VORNW */
extern int64_t __orn(int64_t, int64_t);
/* int64_t __orn(int64_t, int64_t(k)); */
extern long2 __orn(long2, long2);
extern long3 __orn(long3, long3);
extern long4 __orn(long4, long4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __orn(long8, long8);
#endif
extern uint64_t __orn(uint64_t, uint64_t);
/* uint64_t __orn(uint64_t, uint64_t(k)); */
extern ulong2 __orn(ulong2, ulong2);
extern ulong3 __orn(ulong3, ulong3);
extern ulong4 __orn(ulong4, ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __orn(ulong8, ulong8);
#endif

/* ORN */
extern bool2 __orn(bool2, bool2);
extern bool3 __orn(bool3, bool3);
extern bool4 __orn(bool4, bool4);
extern bool8 __orn(bool8, bool8);
extern bool16 __orn(bool16, bool16);
extern bool32 __orn(bool32, bool32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern bool64 __orn(bool64, bool64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __outer_product_matmpy                                                 */
/*----------------------------------------------------------------------------*/

/* VOPMATMPYSP */
#if __C7X_VEC_SIZE_BITS__ == 512
extern float4 __outer_product_matmpy(float2, float2);
extern float8 __outer_product_matmpy(float4, float4);
extern float16 __outer_product_matmpy(float8, float8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __pack                                                                 */
/*----------------------------------------------------------------------------*/

/* PACKW */
extern cshort2 __pack(cshort, cshort);
extern int2 __pack(int32_t, int32_t);
extern uint2 __pack(uint32_t, uint32_t);
extern float2 __pack(float, float);

/*----------------------------------------------------------------------------*/
/* ID: __pack_consec_high                                                     */
/*----------------------------------------------------------------------------*/

/* VBPACKH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __pack_consec_high(char32, char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __pack_consec_high(char64, char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __pack_consec_high(uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __pack_consec_high(uchar64, uchar64);
#endif

/* VHPACKH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cchar16 __pack_consec_high(cchar16, cchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cchar32 __pack_consec_high(cchar32, cchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __pack_consec_high(short16, short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __pack_consec_high(short32, short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __pack_consec_high(ushort16, ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __pack_consec_high(ushort32, ushort32);
#endif

/* VWPACKH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cshort8 __pack_consec_high(cshort8, cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cshort16 __pack_consec_high(cshort16, cshort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __pack_consec_high(int8, int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __pack_consec_high(int16, int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __pack_consec_high(uint8, uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __pack_consec_high(uint16, uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern float8 __pack_consec_high(float8, float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern float16 __pack_consec_high(float16, float16);
#endif

/* VDPACKH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cint4 __pack_consec_high(cint4, cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cint8 __pack_consec_high(cint8, cint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cfloat4 __pack_consec_high(cfloat4, cfloat4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cfloat8 __pack_consec_high(cfloat8, cfloat8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __pack_consec_high(long4, long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __pack_consec_high(long8, long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __pack_consec_high(ulong4, ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __pack_consec_high(ulong8, ulong8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern double4 __pack_consec_high(double4, double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern double8 __pack_consec_high(double8, double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __pack_consec_low                                                      */
/*----------------------------------------------------------------------------*/

/* VBPACKL */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __pack_consec_low(char32, char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __pack_consec_low(char64, char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __pack_consec_low(uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __pack_consec_low(uchar64, uchar64);
#endif

/* VHPACKL */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cchar16 __pack_consec_low(cchar16, cchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cchar32 __pack_consec_low(cchar32, cchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __pack_consec_low(short16, short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __pack_consec_low(short32, short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __pack_consec_low(ushort16, ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __pack_consec_low(ushort32, ushort32);
#endif

/* VWPACKL */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cshort8 __pack_consec_low(cshort8, cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cshort16 __pack_consec_low(cshort16, cshort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __pack_consec_low(int8, int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __pack_consec_low(int16, int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __pack_consec_low(uint8, uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __pack_consec_low(uint16, uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern float8 __pack_consec_low(float8, float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern float16 __pack_consec_low(float16, float16);
#endif

/* VDPACKL */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cint4 __pack_consec_low(cint4, cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cint8 __pack_consec_low(cint8, cint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cfloat4 __pack_consec_low(cfloat4, cfloat4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cfloat8 __pack_consec_low(cfloat8, cfloat8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __pack_consec_low(long4, long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __pack_consec_low(long8, long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __pack_consec_low(ulong4, ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __pack_consec_low(ulong8, ulong8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern double4 __pack_consec_low(double4, double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern double8 __pack_consec_low(double8, double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __pack_even                                                            */
/*----------------------------------------------------------------------------*/

/* VPACKP2 */
extern cchar4 __pack_even(cchar4, cchar4);
extern cchar8 __pack_even(cchar8, cchar8);
extern cchar16 __pack_even(cchar16, cchar16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern cchar32 __pack_even(cchar32, cchar32);
#endif
extern short4 __pack_even(short4, short4);
extern short8 __pack_even(short8, short8);
extern short16 __pack_even(short16, short16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __pack_even(short32, short32);
#endif
extern ushort4 __pack_even(ushort4, ushort4);
extern ushort8 __pack_even(ushort8, ushort8);
extern ushort16 __pack_even(ushort16, ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __pack_even(ushort32, ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __pack_even_cross                                                      */
/*----------------------------------------------------------------------------*/

/* PACKX2 */
extern cchar4 __pack_even_cross(cchar2, cchar2);

/* VPACKX2 */
extern cchar4 __pack_even_cross(cchar4, cchar4);
extern cchar8 __pack_even_cross(cchar8, cchar8);
extern cchar16 __pack_even_cross(cchar16, cchar16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern cchar32 __pack_even_cross(cchar32, cchar32);
#endif

/* PACKX2 */
extern short4 __pack_even_cross(short2, short2);

/* VPACKX2 */
extern short4 __pack_even_cross(short4, short4);
extern short8 __pack_even_cross(short8, short8);
extern short16 __pack_even_cross(short16, short16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __pack_even_cross(short32, short32);
#endif

/* PACKX2 */
extern ushort4 __pack_even_cross(ushort2, ushort2);

/* VPACKX2 */
extern ushort4 __pack_even_cross(ushort4, ushort4);
extern ushort8 __pack_even_cross(ushort8, ushort8);
extern ushort16 __pack_even_cross(ushort16, ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __pack_even_cross(ushort32, ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __pack_high                                                            */
/*----------------------------------------------------------------------------*/

/* VPACKH4 */
extern char4 __pack_high(char4, char4);
extern char8 __pack_high(char8, char8);
extern char16 __pack_high(char16, char16);
extern char32 __pack_high(char32, char32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __pack_high(char64, char64);
#endif
extern uchar4 __pack_high(uchar4, uchar4);
extern uchar8 __pack_high(uchar8, uchar8);
extern uchar16 __pack_high(uchar16, uchar16);
extern uchar32 __pack_high(uchar32, uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __pack_high(uchar64, uchar64);
#endif

/* VPACKH2 */
extern cchar2 __pack_high(cchar2, cchar2);
extern cchar4 __pack_high(cchar4, cchar4);
extern cchar8 __pack_high(cchar8, cchar8);
extern cchar16 __pack_high(cchar16, cchar16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern cchar32 __pack_high(cchar32, cchar32);
#endif
extern short2 __pack_high(short2, short2);
extern short4 __pack_high(short4, short4);
extern short8 __pack_high(short8, short8);
extern short16 __pack_high(short16, short16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __pack_high(short32, short32);
#endif
extern ushort2 __pack_high(ushort2, ushort2);
extern ushort4 __pack_high(ushort4, ushort4);
extern ushort8 __pack_high(ushort8, ushort8);
extern ushort16 __pack_high(ushort16, ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __pack_high(ushort32, ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __pack_high_low                                                        */
/*----------------------------------------------------------------------------*/

/* VPACKHL2 */
extern cchar2 __pack_high_low(cchar2, cchar2);
extern cchar4 __pack_high_low(cchar4, cchar4);
extern cchar8 __pack_high_low(cchar8, cchar8);
extern cchar16 __pack_high_low(cchar16, cchar16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern cchar32 __pack_high_low(cchar32, cchar32);
#endif
extern short2 __pack_high_low(short2, short2);
extern short4 __pack_high_low(short4, short4);
extern short8 __pack_high_low(short8, short8);
extern short16 __pack_high_low(short16, short16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __pack_high_low(short32, short32);
#endif
extern ushort2 __pack_high_low(ushort2, ushort2);
extern ushort4 __pack_high_low(ushort4, ushort4);
extern ushort8 __pack_high_low(ushort8, ushort8);
extern ushort16 __pack_high_low(ushort16, ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __pack_high_low(ushort32, ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __pack_low                                                             */
/*----------------------------------------------------------------------------*/

/* VPACKL4 */
extern char4 __pack_low(char4, char4);
extern char8 __pack_low(char8, char8);
extern char16 __pack_low(char16, char16);
extern char32 __pack_low(char32, char32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __pack_low(char64, char64);
#endif
extern uchar4 __pack_low(uchar4, uchar4);
extern uchar8 __pack_low(uchar8, uchar8);
extern uchar16 __pack_low(uchar16, uchar16);
extern uchar32 __pack_low(uchar32, uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __pack_low(uchar64, uchar64);
#endif

/* VPACKL2 */
extern cchar2 __pack_low(cchar2, cchar2);
extern cchar4 __pack_low(cchar4, cchar4);
extern cchar8 __pack_low(cchar8, cchar8);
extern cchar16 __pack_low(cchar16, cchar16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern cchar32 __pack_low(cchar32, cchar32);
#endif
extern short2 __pack_low(short2, short2);
extern short4 __pack_low(short4, short4);
extern short8 __pack_low(short8, short8);
extern short16 __pack_low(short16, short16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __pack_low(short32, short32);
#endif
extern ushort2 __pack_low(ushort2, ushort2);
extern ushort4 __pack_low(ushort4, ushort4);
extern ushort8 __pack_low(ushort8, ushort8);
extern ushort16 __pack_low(ushort16, ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __pack_low(ushort32, ushort32);
#endif

/* VPACKW */
extern cshort2 __pack_low(cshort2, cshort2);
extern cshort4 __pack_low(cshort4, cshort4);
extern cshort8 __pack_low(cshort8, cshort8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern cshort16 __pack_low(cshort16, cshort16);
#endif
extern int2 __pack_low(int2, int2);
extern int4 __pack_low(int4, int4);
extern int8 __pack_low(int8, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __pack_low(int16, int16);
#endif
extern uint2 __pack_low(uint2, uint2);
extern uint4 __pack_low(uint4, uint4);
extern uint8 __pack_low(uint8, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __pack_low(uint16, uint16);
#endif
extern float2 __pack_low(float2, float2);
extern float4 __pack_low(float4, float4);
extern float8 __pack_low(float8, float8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern float16 __pack_low(float16, float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __pack_low_high                                                        */
/*----------------------------------------------------------------------------*/

/* VPACKLH4 */
extern char8 __pack_low_high(char8, char8);
extern char16 __pack_low_high(char16, char16);
extern char32 __pack_low_high(char32, char32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __pack_low_high(char64, char64);
#endif
extern uchar8 __pack_low_high(uchar8, uchar8);
extern uchar16 __pack_low_high(uchar16, uchar16);
extern uchar32 __pack_low_high(uchar32, uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __pack_low_high(uchar64, uchar64);
#endif

/* VPACKLH2 */
extern cchar2 __pack_low_high(cchar2, cchar2);
extern cchar4 __pack_low_high(cchar4, cchar4);
extern cchar8 __pack_low_high(cchar8, cchar8);
extern cchar16 __pack_low_high(cchar16, cchar16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern cchar32 __pack_low_high(cchar32, cchar32);
#endif
extern short2 __pack_low_high(short2, short2);
extern short4 __pack_low_high(short4, short4);
extern short8 __pack_low_high(short8, short8);
extern short16 __pack_low_high(short16, short16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __pack_low_high(short32, short32);
#endif
extern ushort2 __pack_low_high(ushort2, ushort2);
extern ushort4 __pack_low_high(ushort4, ushort4);
extern ushort8 __pack_low_high(ushort8, ushort8);
extern ushort16 __pack_low_high(ushort16, ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __pack_low_high(ushort32, ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __pack_sat                                                             */
/*----------------------------------------------------------------------------*/

/* VSPACKHB */
extern char2 __pack_sat(int16_t, int16_t);
extern char4 __pack_sat(short2, short2);
extern char8 __pack_sat(short4, short4);
extern char16 __pack_sat(short8, short8);
extern char32 __pack_sat(short16, short16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __pack_sat(short32, short32);
#endif

/* VSPACKWH */
extern short2 __pack_sat(int32_t, int32_t);
extern short4 __pack_sat(int2, int2);
extern short8 __pack_sat(int4, int4);
extern short16 __pack_sat(int8, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __pack_sat(int16, int16);
#endif

/* VSPACKDW */
extern int2 __pack_sat(int64_t, int64_t);
extern int4 __pack_sat(long2, long2);
extern int8 __pack_sat(long4, long4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __pack_sat(long8, long8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __pack_shift_sat                                                       */
/*----------------------------------------------------------------------------*/

/* VRPACKH */
extern short2 __pack_shift_sat(int32_t, int32_t);
extern short4 __pack_shift_sat(int2, int2);
extern short8 __pack_shift_sat(int4, int4);
extern short16 __pack_shift_sat(int8, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __pack_shift_sat(int16, int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __pack_usat                                                            */
/*----------------------------------------------------------------------------*/

/* VSPACKUHB */
extern uchar2 __pack_usat(int16_t, int16_t);
extern uchar4 __pack_usat(short2, short2);
extern uchar8 __pack_usat(short4, short4);
extern uchar16 __pack_usat(short8, short8);
extern uchar32 __pack_usat(short16, short16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __pack_usat(short32, short32);
#endif

/* VSPACKUWH */
extern ushort2 __pack_usat(int32_t, int32_t);
extern ushort4 __pack_usat(int2, int2);
extern ushort8 __pack_usat(int4, int4);
extern ushort16 __pack_usat(int8, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __pack_usat(int16, int16);
#endif

/* VSPACKUDW */
extern uint2 __pack_usat(int64_t, int64_t);
extern uint4 __pack_usat(long2, long2);
extern uint8 __pack_usat(long4, long4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __pack_usat(long8, long8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __parallel_pack_dup_16way                                              */
/*----------------------------------------------------------------------------*/

/* VPPACKDUP16W */
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __parallel_pack_dup_16way(bool16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __parallel_pack_dup_8way                                               */
/*----------------------------------------------------------------------------*/

/* VPPACKDUP8W */
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __parallel_pack_dup_8way(bool8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __permute                                                              */
/*----------------------------------------------------------------------------*/

/* VPERM */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __permute(uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __permute(uchar64, uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __permute_cntrl                                                        */
/*----------------------------------------------------------------------------*/

/* VPERM */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __permute_cntrl(uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __permute_cntrl(uchar64, uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __permute_even_even_char                                               */
/*----------------------------------------------------------------------------*/

/* VPERMEEB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __permute_even_even_char(uchar32, uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __permute_even_even_char(uchar64, uchar64, uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __permute_even_even_int                                                */
/*----------------------------------------------------------------------------*/

/* VPERMEEW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __permute_even_even_int(uchar32, uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __permute_even_even_int(uchar64, uchar64, uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __permute_even_even_long                                               */
/*----------------------------------------------------------------------------*/

/* VPERMEED */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __permute_even_even_long(uchar32, uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __permute_even_even_long(uchar64, uchar64, uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __permute_even_even_quad                                               */
/*----------------------------------------------------------------------------*/

/* VPERMEEQ */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __permute_even_even_quad(uchar32, uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __permute_even_even_quad(uchar64, uchar64, uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __permute_even_even_short                                              */
/*----------------------------------------------------------------------------*/

/* VPERMEEH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __permute_even_even_short(uchar32, uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __permute_even_even_short(uchar64, uchar64, uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __permute_even_odd_char                                                */
/*----------------------------------------------------------------------------*/

/* VPERMEOB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __permute_even_odd_char(uchar32, uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __permute_even_odd_char(uchar64, uchar64, uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __permute_even_odd_int                                                 */
/*----------------------------------------------------------------------------*/

/* VPERMEOW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __permute_even_odd_int(uchar32, uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __permute_even_odd_int(uchar64, uchar64, uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __permute_even_odd_long                                                */
/*----------------------------------------------------------------------------*/

/* VPERMEOD */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __permute_even_odd_long(uchar32, uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __permute_even_odd_long(uchar64, uchar64, uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __permute_even_odd_quad                                                */
/*----------------------------------------------------------------------------*/

/* VPERMEOQ */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __permute_even_odd_quad(uchar32, uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __permute_even_odd_quad(uchar64, uchar64, uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __permute_even_odd_short                                               */
/*----------------------------------------------------------------------------*/

/* VPERMEOH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __permute_even_odd_short(uchar32, uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __permute_even_odd_short(uchar64, uchar64, uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __permute_high_high                                                    */
/*----------------------------------------------------------------------------*/

/* VPERMHH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __permute_high_high(uchar32, uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __permute_high_high(uchar64, uchar64, uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __permute_low_high                                                     */
/*----------------------------------------------------------------------------*/

/* VPERMLH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __permute_low_high(uchar32, uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __permute_low_high(uchar64, uchar64, uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __permute_low_low                                                      */
/*----------------------------------------------------------------------------*/

/* VPERMLL */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __permute_low_low(uchar32, uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __permute_low_low(uchar64, uchar64, uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __permute_odd_odd_char                                                 */
/*----------------------------------------------------------------------------*/

/* VPERMOOB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __permute_odd_odd_char(uchar32, uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __permute_odd_odd_char(uchar64, uchar64, uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __permute_odd_odd_int                                                  */
/*----------------------------------------------------------------------------*/

/* VPERMOOW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __permute_odd_odd_int(uchar32, uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __permute_odd_odd_int(uchar64, uchar64, uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __permute_odd_odd_long                                                 */
/*----------------------------------------------------------------------------*/

/* VPERMOOD */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __permute_odd_odd_long(uchar32, uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __permute_odd_odd_long(uchar64, uchar64, uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __permute_odd_odd_quad                                                 */
/*----------------------------------------------------------------------------*/

/* VPERMOOQ */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __permute_odd_odd_quad(uchar32, uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __permute_odd_odd_quad(uchar64, uchar64, uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __permute_odd_odd_short                                                */
/*----------------------------------------------------------------------------*/

/* VPERMOOH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __permute_odd_odd_short(uchar32, uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __permute_odd_odd_short(uchar64, uchar64, uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __popcount                                                             */
/*----------------------------------------------------------------------------*/

/* VBITCNTB */
extern int8_t __popcount(int8_t);
extern char2 __popcount(char2);
extern char3 __popcount(char3);
extern char4 __popcount(char4);
extern char8 __popcount(char8);
extern char16 __popcount(char16);
extern char32 __popcount(char32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __popcount(char64);
#endif
extern uint8_t __popcount(uint8_t);
extern uchar2 __popcount(uchar2);
extern uchar3 __popcount(uchar3);
extern uchar4 __popcount(uchar4);
extern uchar8 __popcount(uchar8);
extern uchar16 __popcount(uchar16);
extern uchar32 __popcount(uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __popcount(uchar64);
#endif

/* VBITCNTH */
extern int16_t __popcount(int16_t);
extern short2 __popcount(short2);
extern short3 __popcount(short3);
extern short4 __popcount(short4);
extern short8 __popcount(short8);
extern short16 __popcount(short16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __popcount(short32);
#endif
extern uint16_t __popcount(uint16_t);
extern ushort2 __popcount(ushort2);
extern ushort3 __popcount(ushort3);
extern ushort4 __popcount(ushort4);
extern ushort8 __popcount(ushort8);
extern ushort16 __popcount(ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __popcount(ushort32);
#endif

/* VBITCNTW */
extern int32_t __popcount(int32_t);
extern int2 __popcount(int2);
extern int3 __popcount(int3);
extern int4 __popcount(int4);
extern int8 __popcount(int8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __popcount(int16);
#endif
extern uint32_t __popcount(uint32_t);
extern uint2 __popcount(uint2);
extern uint3 __popcount(uint3);
extern uint4 __popcount(uint4);
extern uint8 __popcount(uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __popcount(uint16);
#endif

/* VBITCNTD */
extern int64_t __popcount(int64_t);
extern long2 __popcount(long2);
extern long3 __popcount(long3);
extern long4 __popcount(long4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __popcount(long8);
#endif
extern uint64_t __popcount(uint64_t);
extern ulong2 __popcount(ulong2);
extern ulong3 __popcount(ulong3);
extern ulong4 __popcount(ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __popcount(ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __recip                                                                */
/*----------------------------------------------------------------------------*/

/* VRCPSP */
extern float __recip(float);
extern float2 __recip(float2);
extern float3 __recip(float3);
extern float4 __recip(float4);
extern float8 __recip(float8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern float16 __recip(float16);
#endif

/* VRCPDP */
extern double __recip(double);
extern double2 __recip(double2);
extern double3 __recip(double3);
extern double4 __recip(double4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern double8 __recip(double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __recip_sqrt                                                           */
/*----------------------------------------------------------------------------*/

/* VRSQRSP */
extern float __recip_sqrt(float);
extern float2 __recip_sqrt(float2);
extern float3 __recip_sqrt(float3);
extern float4 __recip_sqrt(float4);
extern float8 __recip_sqrt(float8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern float16 __recip_sqrt(float16);
#endif

/* VRSQRDP */
extern double __recip_sqrt(double);
extern double2 __recip_sqrt(double2);
extern double3 __recip_sqrt(double3);
extern double4 __recip_sqrt(double4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern double8 __recip_sqrt(double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __replace                                                              */
/*----------------------------------------------------------------------------*/

/* REPLACE, VREPLACE */
extern int64_t __replace(int64_t, int8_t/*(k={0-63})*/, int8_t/*(k={0-63})*/, int64_t);
extern long2 __replace(long2, char2/*(k={0-63})*/, char2/*(k={0-63})*/, long2);
extern long3 __replace(long3, char3/*(k={0-63})*/, char3/*(k={0-63})*/, long3);
extern long4 __replace(long4, char4/*(k={0-63})*/, char4/*(k={0-63})*/, long4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __replace(long8, char8/*(k={0-63})*/, char8/*(k={0-63})*/, long8);
#endif
extern uint64_t __replace(uint64_t, uint8_t/*(k={0-63})*/, uint8_t/*(k={0-63})*/, uint64_t);
extern ulong2 __replace(ulong2, uchar2/*(k={0-63})*/, uchar2/*(k={0-63})*/, ulong2);
extern ulong3 __replace(ulong3, uchar3/*(k={0-63})*/, uchar3/*(k={0-63})*/, ulong3);
extern ulong4 __replace(ulong4, uchar4/*(k={0-63})*/, uchar4/*(k={0-63})*/, ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __replace(ulong8, uchar8/*(k={0-63})*/, uchar8/*(k={0-63})*/, ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __reverse                                                              */
/*----------------------------------------------------------------------------*/

/* VREVERSEB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __reverse(char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __reverse(char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __reverse(uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __reverse(uchar64);
#endif

/* VREVERSEH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cchar16 __reverse(cchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cchar32 __reverse(cchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __reverse(short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __reverse(short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __reverse(ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __reverse(ushort32);
#endif

/* VREVERSEW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cshort8 __reverse(cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cshort16 __reverse(cshort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __reverse(int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __reverse(int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __reverse(uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __reverse(uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern float8 __reverse(float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern float16 __reverse(float16);
#endif

/* VREVERSED */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cint4 __reverse(cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cint8 __reverse(cint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cfloat4 __reverse(cfloat4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cfloat8 __reverse(cfloat8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __reverse(long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __reverse(long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __reverse(ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __reverse(ulong8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern double4 __reverse(double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern double8 __reverse(double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __rhadd                                                                */
/*----------------------------------------------------------------------------*/

/* VAVGB */
extern int8_t __rhadd(int8_t, int8_t);
extern char2 __rhadd(char2, char2);
extern char3 __rhadd(char3, char3);
extern char4 __rhadd(char4, char4);
extern char8 __rhadd(char8, char8);
extern char16 __rhadd(char16, char16);
extern char32 __rhadd(char32, char32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __rhadd(char64, char64);
#endif

/* VAVGUB */
extern uint8_t __rhadd(uint8_t, uint8_t);
extern uchar2 __rhadd(uchar2, uchar2);
extern uchar3 __rhadd(uchar3, uchar3);
extern uchar4 __rhadd(uchar4, uchar4);
extern uchar8 __rhadd(uchar8, uchar8);
extern uchar16 __rhadd(uchar16, uchar16);
extern uchar32 __rhadd(uchar32, uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __rhadd(uchar64, uchar64);
#endif

/* VAVGH */
extern int16_t __rhadd(int16_t, int16_t);
extern short2 __rhadd(short2, short2);
extern short3 __rhadd(short3, short3);
extern short4 __rhadd(short4, short4);
extern short8 __rhadd(short8, short8);
extern short16 __rhadd(short16, short16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __rhadd(short32, short32);
#endif

/* VAVGUH */
extern uint16_t __rhadd(uint16_t, uint16_t);
extern ushort2 __rhadd(ushort2, ushort2);
extern ushort3 __rhadd(ushort3, ushort3);
extern ushort4 __rhadd(ushort4, ushort4);
extern ushort8 __rhadd(ushort8, ushort8);
extern ushort16 __rhadd(ushort16, ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __rhadd(ushort32, ushort32);
#endif

/* VAVGW */
extern int32_t __rhadd(int32_t, int32_t);
extern int2 __rhadd(int2, int2);
extern int3 __rhadd(int3, int3);
extern int4 __rhadd(int4, int4);
extern int8 __rhadd(int8, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __rhadd(int16, int16);
#endif

/* VAVGUW */
extern uint32_t __rhadd(uint32_t, uint32_t);
extern uint2 __rhadd(uint2, uint2);
extern uint3 __rhadd(uint3, uint3);
extern uint4 __rhadd(uint4, uint4);
extern uint8 __rhadd(uint8, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __rhadd(uint16, uint16);
#endif

/* VAVGD */
extern int64_t __rhadd(int64_t, int64_t);
extern long2 __rhadd(long2, long2);
extern long3 __rhadd(long3, long3);
extern long4 __rhadd(long4, long4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __rhadd(long8, long8);
#endif

/* VAVGUD */
extern uint64_t __rhadd(uint64_t, uint64_t);
extern ulong2 __rhadd(ulong2, ulong2);
extern ulong3 __rhadd(ulong3, ulong3);
extern ulong4 __rhadd(ulong4, ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __rhadd(ulong8, ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __rotate_left                                                          */
/*----------------------------------------------------------------------------*/

/* VROTLB */
extern uint8_t __rotate_left(uint8_t, uint8_t/*(k={0-63})*/);
extern uchar2 __rotate_left(uchar2, uchar2/*(k={0-63})*/);
extern uchar3 __rotate_left(uchar3, uchar3/*(k={0-63})*/);
extern uchar4 __rotate_left(uchar4, uchar4/*(k={0-63})*/);
extern uchar8 __rotate_left(uchar8, uchar8/*(k={0-63})*/);
extern uchar16 __rotate_left(uchar16, uchar16/*(k={0-63})*/);
extern uchar32 __rotate_left(uchar32, uchar32/*(k={0-63})*/);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __rotate_left(uchar64, uchar64/*(k={0-63})*/);
#endif
extern uchar4 __rotate_left(uchar4, uint32_t);
extern uchar8 __rotate_left(uchar8, uint2);
extern uchar16 __rotate_left(uchar16, uint4);
extern uchar32 __rotate_left(uchar32, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __rotate_left(uchar64, uint16);
#endif

/* VROTLH */
extern uint16_t __rotate_left(uint16_t, uint16_t/*(k={0-63})*/);
extern ushort2 __rotate_left(ushort2, ushort2/*(k={0-63})*/);
extern ushort3 __rotate_left(ushort3, ushort3/*(k={0-63})*/);
extern ushort4 __rotate_left(ushort4, ushort4/*(k={0-63})*/);
extern ushort8 __rotate_left(ushort8, ushort8/*(k={0-63})*/);
extern ushort16 __rotate_left(ushort16, ushort16/*(k={0-63})*/);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __rotate_left(ushort32, ushort32/*(k={0-63})*/);
#endif
extern ushort2 __rotate_left(ushort2, uint32_t);
extern ushort4 __rotate_left(ushort4, uint2);
extern ushort8 __rotate_left(ushort8, uint4);
extern ushort16 __rotate_left(ushort16, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __rotate_left(ushort32, uint16);
#endif

/* VROTLW */
extern int32_t __rotate_left(int32_t, uint8_t/*(k={0-63})*/);
extern int2 __rotate_left(int2, uchar2/*(k={0-63})*/);
extern int3 __rotate_left(int3, uchar3/*(k={0-63})*/);
extern int4 __rotate_left(int4, uchar4/*(k={0-63})*/);
extern int8 __rotate_left(int8, uchar8/*(k={0-63})*/);
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __rotate_left(int16, uchar16/*(k={0-63})*/);
#endif
extern int32_t __rotate_left(int32_t, uint32_t);
extern int2 __rotate_left(int2, uint2);
extern int3 __rotate_left(int3, uint3);
extern int4 __rotate_left(int4, uint4);
extern int8 __rotate_left(int8, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __rotate_left(int16, uint16);
#endif

/* VROTLD */
extern uint64_t __rotate_left(uint64_t, uint8_t/*(k={0-63})*/);
extern ulong2 __rotate_left(ulong2, uchar2/*(k={0-63})*/);
extern ulong3 __rotate_left(ulong3, uchar3/*(k={0-63})*/);
extern ulong4 __rotate_left(ulong4, uchar4/*(k={0-63})*/);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __rotate_left(ulong8, uchar8/*(k={0-63})*/);
#endif
extern uint64_t __rotate_left(uint64_t, uint64_t);
extern ulong2 __rotate_left(ulong2, ulong2);
extern ulong3 __rotate_left(ulong3, ulong3);
extern ulong4 __rotate_left(ulong4, ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __rotate_left(ulong8, ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __saturate                                                             */
/*----------------------------------------------------------------------------*/

/* VGSATH */
extern int16_t __saturate(int16_t, uint8_t/*(k={0-63})*/);
extern short2 __saturate(short2, uchar2/*(k={0-63})*/);
extern short3 __saturate(short3, uchar3/*(k={0-63})*/);
extern short4 __saturate(short4, uchar4/*(k={0-63})*/);
extern short8 __saturate(short8, uchar8/*(k={0-63})*/);
extern short16 __saturate(short16, uchar16/*(k={0-63})*/);
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __saturate(short32, uchar32/*(k={0-63})*/);
#endif

/* VGSATUH */
extern uint16_t __saturate(uint16_t, uint8_t/*(k={0-63})*/);
extern ushort2 __saturate(ushort2, uchar2/*(k={0-63})*/);
extern ushort3 __saturate(ushort3, uchar3/*(k={0-63})*/);
extern ushort4 __saturate(ushort4, uchar4/*(k={0-63})*/);
extern ushort8 __saturate(ushort8, uchar8/*(k={0-63})*/);
extern ushort16 __saturate(ushort16, uchar16/*(k={0-63})*/);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __saturate(ushort32, uchar32/*(k={0-63})*/);
#endif

/* VGSATW */
extern int32_t __saturate(int32_t, uint8_t/*(k={0-63})*/);
extern int2 __saturate(int2, uchar2/*(k={0-63})*/);
extern int3 __saturate(int3, uchar3/*(k={0-63})*/);
extern int4 __saturate(int4, uchar4/*(k={0-63})*/);
extern int8 __saturate(int8, uchar8/*(k={0-63})*/);
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __saturate(int16, uchar16/*(k={0-63})*/);
#endif

/* VGSATUW */
extern uint32_t __saturate(uint32_t, uint8_t/*(k={0-63})*/);
extern uint2 __saturate(uint2, uchar2/*(k={0-63})*/);
extern uint3 __saturate(uint3, uchar3/*(k={0-63})*/);
extern uint4 __saturate(uint4, uchar4/*(k={0-63})*/);
extern uint8 __saturate(uint8, uchar8/*(k={0-63})*/);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __saturate(uint16, uchar16/*(k={0-63})*/);
#endif

/* VGSATD */
extern int64_t __saturate(int64_t, uint8_t/*(k={0-63})*/);
extern long2 __saturate(long2, uchar2/*(k={0-63})*/);
extern long3 __saturate(long3, uchar3/*(k={0-63})*/);
extern long4 __saturate(long4, uchar4/*(k={0-63})*/);
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __saturate(long8, uchar8/*(k={0-63})*/);
#endif

/* VGSATUD */
extern uint64_t __saturate(uint64_t, uint8_t/*(k={0-63})*/);
extern ulong2 __saturate(ulong2, uchar2/*(k={0-63})*/);
extern ulong3 __saturate(ulong3, uchar3/*(k={0-63})*/);
extern ulong4 __saturate(ulong4, uchar4/*(k={0-63})*/);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __saturate(ulong8, uchar8/*(k={0-63})*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __saturate_s2u                                                         */
/*----------------------------------------------------------------------------*/

/* VGSATSUH */
extern uint16_t __saturate_s2u(int16_t, uint8_t/*(k={0-63})*/);
extern ushort2 __saturate_s2u(short2, uchar2/*(k={0-63})*/);
extern ushort3 __saturate_s2u(short3, uchar3/*(k={0-63})*/);
extern ushort4 __saturate_s2u(short4, uchar4/*(k={0-63})*/);
extern ushort8 __saturate_s2u(short8, uchar8/*(k={0-63})*/);
extern ushort16 __saturate_s2u(short16, uchar16/*(k={0-63})*/);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __saturate_s2u(short32, uchar32/*(k={0-63})*/);
#endif

/* VGSATSUW */
extern uint32_t __saturate_s2u(int32_t, uint8_t/*(k={0-63})*/);
extern uint2 __saturate_s2u(int2, uchar2/*(k={0-63})*/);
extern uint3 __saturate_s2u(int3, uchar3/*(k={0-63})*/);
extern uint4 __saturate_s2u(int4, uchar4/*(k={0-63})*/);
extern uint8 __saturate_s2u(int8, uchar8/*(k={0-63})*/);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __saturate_s2u(int16, uchar16/*(k={0-63})*/);
#endif

/* VGSATSUD */
extern uint64_t __saturate_s2u(int64_t, uint8_t/*(k={0-63})*/);
extern ulong2 __saturate_s2u(long2, uchar2/*(k={0-63})*/);
extern ulong3 __saturate_s2u(long3, uchar3/*(k={0-63})*/);
extern ulong4 __saturate_s2u(long4, uchar4/*(k={0-63})*/);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __saturate_s2u(long8, uchar8/*(k={0-63})*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __scale                                                                */
/*----------------------------------------------------------------------------*/

/* VSCALESP */
extern float __scale(float, uint32_t);
extern float2 __scale(float2, uint2);
extern float3 __scale(float3, uint3);
extern float4 __scale(float4, uint4);
extern float8 __scale(float8, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern float16 __scale(float16, uint16);
#endif

/* VSCALEDP */
extern double __scale(double, uint64_t);
extern double2 __scale(double2, ulong2);
extern double3 __scale(double3, ulong3);
extern double4 __scale(double4, ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern double8 __scale(double8, ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __select                                                               */
/*----------------------------------------------------------------------------*/

/* VSEL */
extern char2 __select(bool2, char2, char2);
extern char3 __select(bool3, char3, char3);
extern char4 __select(bool4, char4, char4);
extern char8 __select(bool8, char8, char8);
extern char16 __select(bool16, char16, char16);
extern char32 __select(bool32, char32, char32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __select(bool64, char64, char64);
#endif
extern uchar2 __select(bool2, uchar2, uchar2);
extern uchar3 __select(bool3, uchar3, uchar3);
extern uchar4 __select(bool4, uchar4, uchar4);
extern uchar8 __select(bool8, uchar8, uchar8);
extern uchar16 __select(bool16, uchar16, uchar16);
extern uchar32 __select(bool32, uchar32, uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __select(bool64, uchar64, uchar64);
#endif
extern cchar2 __select(bool2, cchar2, cchar2);
extern cchar4 __select(bool4, cchar4, cchar4);
extern cchar8 __select(bool8, cchar8, cchar8);
extern cchar16 __select(bool16, cchar16, cchar16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern cchar32 __select(bool32, cchar32, cchar32);
#endif
extern short2 __select(bool2, short2, short2);
extern short3 __select(bool3, short3, short3);
extern short4 __select(bool4, short4, short4);
extern short8 __select(bool8, short8, short8);
extern short16 __select(bool16, short16, short16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __select(bool32, short32, short32);
#endif
extern ushort2 __select(bool2, ushort2, ushort2);
extern ushort3 __select(bool3, ushort3, ushort3);
extern ushort4 __select(bool4, ushort4, ushort4);
extern ushort8 __select(bool8, ushort8, ushort8);
extern ushort16 __select(bool16, ushort16, ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __select(bool32, ushort32, ushort32);
#endif
extern cshort2 __select(bool2, cshort2, cshort2);
extern cshort4 __select(bool4, cshort4, cshort4);
extern cshort8 __select(bool8, cshort8, cshort8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern cshort16 __select(bool16, cshort16, cshort16);
#endif
extern int2 __select(bool2, int2, int2);
/* int2 __select(bool2, int2, int2(k)); */
extern int3 __select(bool3, int3, int3);
/* int3 __select(bool3, int3, int3(k)); */
extern int4 __select(bool4, int4, int4);
/* int4 __select(bool4, int4, int4(k)); */
extern int8 __select(bool8, int8, int8);
/* int8 __select(bool8, int8, int8(k)); */
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __select(bool16, int16, int16);
/* int16 __select(bool16, int16, int16(k)); */
#endif
extern uint2 __select(bool2, uint2, uint2);
/* uint2 __select(bool2, uint2, uint2(k)); */
extern uint3 __select(bool3, uint3, uint3);
/* uint3 __select(bool3, uint3, uint3(k)); */
extern uint4 __select(bool4, uint4, uint4);
/* uint4 __select(bool4, uint4, uint4(k)); */
extern uint8 __select(bool8, uint8, uint8);
/* uint8 __select(bool8, uint8, uint8(k)); */
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __select(bool16, uint16, uint16);
/* uint16 __select(bool16, uint16, uint16(k)); */
#endif
extern float2 __select(bool2, float2, float2);
/* float2 __select(bool2, float2, float2(k)); */
extern float3 __select(bool3, float3, float3);
/* float3 __select(bool3, float3, float3(k)); */
extern float4 __select(bool4, float4, float4);
/* float4 __select(bool4, float4, float4(k)); */
extern float8 __select(bool8, float8, float8);
/* float8 __select(bool8, float8, float8(k)); */
#if __C7X_VEC_SIZE_BITS__ == 512
extern float16 __select(bool16, float16, float16);
/* float16 __select(bool16, float16, float16(k)); */
#endif
extern cint2 __select(bool2, cint2, cint2);
extern cint4 __select(bool4, cint4, cint4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern cint8 __select(bool8, cint8, cint8);
#endif
extern cfloat2 __select(bool2, cfloat2, cfloat2);
extern cfloat4 __select(bool4, cfloat4, cfloat4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern cfloat8 __select(bool8, cfloat8, cfloat8);
#endif
extern long2 __select(bool2, long2, long2);
extern long3 __select(bool3, long3, long3);
extern long4 __select(bool4, long4, long4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __select(bool8, long8, long8);
#endif
extern ulong2 __select(bool2, ulong2, ulong2);
extern ulong3 __select(bool3, ulong3, ulong3);
extern ulong4 __select(bool4, ulong4, ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __select(bool8, ulong8, ulong8);
#endif
extern double2 __select(bool2, double2, double2);
extern double3 __select(bool3, double3, double3);
extern double4 __select(bool4, double4, double4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern double8 __select(bool8, double8, double8);
#endif
extern clong2 __select(bool2, clong2, clong2);
#if __C7X_VEC_SIZE_BITS__ == 512
extern clong4 __select(bool4, clong4, clong4);
#endif
extern cdouble2 __select(bool2, cdouble2, cdouble2);
#if __C7X_VEC_SIZE_BITS__ == 512
extern cdouble4 __select(bool4, cdouble4, cdouble4);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __set                                                                  */
/*----------------------------------------------------------------------------*/

/* SET */
extern int32_t __set(int32_t, int32_t);

/*----------------------------------------------------------------------------*/
/* ID: __set_vector_element                                                   */
/*----------------------------------------------------------------------------*/

/* VPUTB */
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __set_vector_element(int8_t, int8_t/*(k={0-63})*/, char64);
#endif
extern char32 __set_vector_element(int8_t, int8_t/*(k={0-63})*/, char32);
extern char16 __set_vector_element(int8_t, int8_t/*(k={0-63})*/, char16);
extern char8 __set_vector_element(int8_t, int8_t/*(k={0-63})*/, char8);
extern char4 __set_vector_element(int8_t, int8_t/*(k={0-63})*/, char4);
extern char3 __set_vector_element(int8_t, int8_t/*(k={0-63})*/, char3);
extern char2 __set_vector_element(int8_t, int8_t/*(k={0-63})*/, char2);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __set_vector_element(uint8_t, uint8_t/*(k={0-63})*/, uchar64);
#endif
extern uchar32 __set_vector_element(uint8_t, uint8_t/*(k={0-63})*/, uchar32);
extern uchar16 __set_vector_element(uint8_t, uint8_t/*(k={0-63})*/, uchar16);
extern uchar8 __set_vector_element(uint8_t, uint8_t/*(k={0-63})*/, uchar8);
extern uchar4 __set_vector_element(uint8_t, uint8_t/*(k={0-63})*/, uchar4);
extern uchar3 __set_vector_element(uint8_t, uint8_t/*(k={0-63})*/, uchar3);
extern uchar2 __set_vector_element(uint8_t, uint8_t/*(k={0-63})*/, uchar2);

/* VPUTH */
#if __C7X_VEC_SIZE_BITS__ == 512
extern cchar32 __set_vector_element(cchar, int8_t/*(k={0-63})*/, cchar32);
#endif
extern cchar16 __set_vector_element(cchar, int8_t/*(k={0-63})*/, cchar16);
extern cchar8 __set_vector_element(cchar, int8_t/*(k={0-63})*/, cchar8);
extern cchar4 __set_vector_element(cchar, int8_t/*(k={0-63})*/, cchar4);
extern cchar2 __set_vector_element(cchar, int8_t/*(k={0-63})*/, cchar2);
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __set_vector_element(int16_t, int8_t/*(k={0-63})*/, short32);
#endif
extern short16 __set_vector_element(int16_t, int8_t/*(k={0-63})*/, short16);
extern short8 __set_vector_element(int16_t, int8_t/*(k={0-63})*/, short8);
extern short4 __set_vector_element(int16_t, int8_t/*(k={0-63})*/, short4);
extern short3 __set_vector_element(int16_t, int8_t/*(k={0-63})*/, short3);
extern short2 __set_vector_element(int16_t, int8_t/*(k={0-63})*/, short2);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __set_vector_element(uint16_t, uint8_t/*(k={0-63})*/, ushort32);
#endif
extern ushort16 __set_vector_element(uint16_t, uint8_t/*(k={0-63})*/, ushort16);
extern ushort8 __set_vector_element(uint16_t, uint8_t/*(k={0-63})*/, ushort8);
extern ushort4 __set_vector_element(uint16_t, uint8_t/*(k={0-63})*/, ushort4);
extern ushort3 __set_vector_element(uint16_t, uint8_t/*(k={0-63})*/, ushort3);
extern ushort2 __set_vector_element(uint16_t, uint8_t/*(k={0-63})*/, ushort2);

/* VPUTW */
#if __C7X_VEC_SIZE_BITS__ == 512
extern cshort16 __set_vector_element(cshort, int8_t/*(k={0-63})*/, cshort16);
#endif
extern cshort8 __set_vector_element(cshort, int8_t/*(k={0-63})*/, cshort8);
extern cshort4 __set_vector_element(cshort, int8_t/*(k={0-63})*/, cshort4);
extern cshort2 __set_vector_element(cshort, int8_t/*(k={0-63})*/, cshort2);
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __set_vector_element(int32_t, int8_t/*(k={0-63})*/, int16);
#endif
extern int8 __set_vector_element(int32_t, int8_t/*(k={0-63})*/, int8);
extern int4 __set_vector_element(int32_t, int8_t/*(k={0-63})*/, int4);
extern int3 __set_vector_element(int32_t, int8_t/*(k={0-63})*/, int3);
extern int2 __set_vector_element(int32_t, int8_t/*(k={0-63})*/, int2);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __set_vector_element(uint32_t, uint8_t/*(k={0-63})*/, uint16);
#endif
extern uint8 __set_vector_element(uint32_t, uint8_t/*(k={0-63})*/, uint8);
extern uint4 __set_vector_element(uint32_t, uint8_t/*(k={0-63})*/, uint4);
extern uint3 __set_vector_element(uint32_t, uint8_t/*(k={0-63})*/, uint3);
extern uint2 __set_vector_element(uint32_t, uint8_t/*(k={0-63})*/, uint2);
#if __C7X_VEC_SIZE_BITS__ == 512
extern float16 __set_vector_element(float, int8_t/*(k={0-63})*/, float16);
#endif
extern float8 __set_vector_element(float, int8_t/*(k={0-63})*/, float8);
extern float4 __set_vector_element(float, int8_t/*(k={0-63})*/, float4);
extern float3 __set_vector_element(float, int8_t/*(k={0-63})*/, float3);
extern float2 __set_vector_element(float, int8_t/*(k={0-63})*/, float2);
#if __C7X_VEC_SIZE_BITS__ == 512
extern float16 __set_vector_element(float, uint8_t/*(k={0-63})*/, float16);
#endif
extern float8 __set_vector_element(float, uint8_t/*(k={0-63})*/, float8);
extern float4 __set_vector_element(float, uint8_t/*(k={0-63})*/, float4);
extern float3 __set_vector_element(float, uint8_t/*(k={0-63})*/, float3);
extern float2 __set_vector_element(float, uint8_t/*(k={0-63})*/, float2);

/* VPUTD */
#if __C7X_VEC_SIZE_BITS__ == 512
extern cint8 __set_vector_element(cint, int8_t/*(k={0-63})*/, cint8);
#endif
extern cint4 __set_vector_element(cint, int8_t/*(k={0-63})*/, cint4);
extern cint2 __set_vector_element(cint, int8_t/*(k={0-63})*/, cint2);
#if __C7X_VEC_SIZE_BITS__ == 512
extern cfloat8 __set_vector_element(cfloat, int8_t/*(k={0-63})*/, cfloat8);
#endif
extern cfloat4 __set_vector_element(cfloat, int8_t/*(k={0-63})*/, cfloat4);
extern cfloat2 __set_vector_element(cfloat, int8_t/*(k={0-63})*/, cfloat2);
#if __C7X_VEC_SIZE_BITS__ == 512
extern cfloat8 __set_vector_element(cfloat, uint8_t/*(k={0-63})*/, cfloat8);
#endif
extern cfloat4 __set_vector_element(cfloat, uint8_t/*(k={0-63})*/, cfloat4);
extern cfloat2 __set_vector_element(cfloat, uint8_t/*(k={0-63})*/, cfloat2);
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __set_vector_element(int64_t, int8_t/*(k={0-63})*/, long8);
#endif
extern long4 __set_vector_element(int64_t, int8_t/*(k={0-63})*/, long4);
extern long3 __set_vector_element(int64_t, int8_t/*(k={0-63})*/, long3);
extern long2 __set_vector_element(int64_t, int8_t/*(k={0-63})*/, long2);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __set_vector_element(uint64_t, uint8_t/*(k={0-63})*/, ulong8);
#endif
extern ulong4 __set_vector_element(uint64_t, uint8_t/*(k={0-63})*/, ulong4);
extern ulong3 __set_vector_element(uint64_t, uint8_t/*(k={0-63})*/, ulong3);
extern ulong2 __set_vector_element(uint64_t, uint8_t/*(k={0-63})*/, ulong2);
#if __C7X_VEC_SIZE_BITS__ == 512
extern double8 __set_vector_element(double, int8_t/*(k={0-63})*/, double8);
#endif
extern double4 __set_vector_element(double, int8_t/*(k={0-63})*/, double4);
extern double3 __set_vector_element(double, int8_t/*(k={0-63})*/, double3);
extern double2 __set_vector_element(double, int8_t/*(k={0-63})*/, double2);
#if __C7X_VEC_SIZE_BITS__ == 512
extern double8 __set_vector_element(double, uint8_t/*(k={0-63})*/, double8);
#endif
extern double4 __set_vector_element(double, uint8_t/*(k={0-63})*/, double4);
extern double3 __set_vector_element(double, uint8_t/*(k={0-63})*/, double3);
extern double2 __set_vector_element(double, uint8_t/*(k={0-63})*/, double2);

/*----------------------------------------------------------------------------*/
/* ID: __shift_left                                                           */
/*----------------------------------------------------------------------------*/

/* VSHLB */
extern int8_t __shift_left(int8_t, int8_t/*(k={0-63})*/);
extern char2 __shift_left(char2, char2/*(k={0-63})*/);
extern char3 __shift_left(char3, char3/*(k={0-63})*/);
extern char4 __shift_left(char4, char4/*(k={0-63})*/);
extern char8 __shift_left(char8, char8/*(k={0-63})*/);
extern char16 __shift_left(char16, char16/*(k={0-63})*/);
extern char32 __shift_left(char32, char32/*(k={0-63})*/);
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __shift_left(char64, char64/*(k={0-63})*/);
#endif
extern char4 __shift_left(char4, int32_t);
extern char8 __shift_left(char8, int2);
extern char16 __shift_left(char16, int4);
extern char32 __shift_left(char32, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __shift_left(char64, int16);
#endif
extern uint8_t __shift_left(uint8_t, uint8_t/*(k={0-63})*/);
extern uchar2 __shift_left(uchar2, uchar2/*(k={0-63})*/);
extern uchar3 __shift_left(uchar3, uchar3/*(k={0-63})*/);
extern uchar4 __shift_left(uchar4, uchar4/*(k={0-63})*/);
extern uchar8 __shift_left(uchar8, uchar8/*(k={0-63})*/);
extern uchar16 __shift_left(uchar16, uchar16/*(k={0-63})*/);
extern uchar32 __shift_left(uchar32, uchar32/*(k={0-63})*/);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __shift_left(uchar64, uchar64/*(k={0-63})*/);
#endif
extern uchar4 __shift_left(uchar4, uint32_t);
extern uchar8 __shift_left(uchar8, uint2);
extern uchar16 __shift_left(uchar16, uint4);
extern uchar32 __shift_left(uchar32, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __shift_left(uchar64, uint16);
#endif

/* VSHLH */
extern int16_t __shift_left(int16_t, int16_t/*(k={0-63})*/);
extern short2 __shift_left(short2, short2/*(k={0-63})*/);
extern short3 __shift_left(short3, short3/*(k={0-63})*/);
extern short4 __shift_left(short4, short4/*(k={0-63})*/);
extern short8 __shift_left(short8, short8/*(k={0-63})*/);
extern short16 __shift_left(short16, short16/*(k={0-63})*/);
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __shift_left(short32, short32/*(k={0-63})*/);
#endif
extern short2 __shift_left(short2, int32_t);
extern short4 __shift_left(short4, int2);
extern short8 __shift_left(short8, int4);
extern short16 __shift_left(short16, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __shift_left(short32, int16);
#endif
extern uint16_t __shift_left(uint16_t, uint16_t/*(k={0-63})*/);
extern ushort2 __shift_left(ushort2, ushort2/*(k={0-63})*/);
extern ushort3 __shift_left(ushort3, ushort3/*(k={0-63})*/);
extern ushort4 __shift_left(ushort4, ushort4/*(k={0-63})*/);
extern ushort8 __shift_left(ushort8, ushort8/*(k={0-63})*/);
extern ushort16 __shift_left(ushort16, ushort16/*(k={0-63})*/);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __shift_left(ushort32, ushort32/*(k={0-63})*/);
#endif
extern ushort2 __shift_left(ushort2, uint32_t);
extern ushort4 __shift_left(ushort4, uint2);
extern ushort8 __shift_left(ushort8, uint4);
extern ushort16 __shift_left(ushort16, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __shift_left(ushort32, uint16);
#endif

/* SHLW */
extern int32_t __shift_left(int32_t, uint8_t/*(k={0-63})*/);

/* SHLW, VSHLW */
extern int32_t __shift_left(int32_t, int32_t);
/* int32_t __shift_left(int32_t, int32_t(k)); */
extern int2 __shift_left(int2, int2);
/* int2 __shift_left(int2, int2(k)); */
extern int3 __shift_left(int3, int3);
/* int3 __shift_left(int3, int3(k)); */
extern int4 __shift_left(int4, int4);
/* int4 __shift_left(int4, int4(k)); */
extern int8 __shift_left(int8, int8);
/* int8 __shift_left(int8, int8(k)); */
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __shift_left(int16, int16);
/* int16 __shift_left(int16, int16(k)); */
#endif

/* SHLW */
extern uint32_t __shift_left(uint32_t, uint8_t/*(k={0-63})*/);

/* SHLW, VSHLW */
extern uint32_t __shift_left(uint32_t, uint32_t);
/* uint32_t __shift_left(uint32_t, uint32_t(k)); */
extern uint2 __shift_left(uint2, uint2);
/* uint2 __shift_left(uint2, uint2(k)); */
extern uint3 __shift_left(uint3, uint3);
/* uint3 __shift_left(uint3, uint3(k)); */
extern uint4 __shift_left(uint4, uint4);
/* uint4 __shift_left(uint4, uint4(k)); */
extern uint8 __shift_left(uint8, uint8);
/* uint8 __shift_left(uint8, uint8(k)); */
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __shift_left(uint16, uint16);
/* uint16 __shift_left(uint16, uint16(k)); */
#endif

/* SHLD */
extern int64_t __shift_left(int64_t, uint8_t/*(k={0-63})*/);
extern int64_t __shift_left(int64_t, int32_t);

/* VSHLD */
extern int64_t __shift_left(int64_t, int64_t);
/* int64_t __shift_left(int64_t, int64_t(k)); */
extern long2 __shift_left(long2, long2);
/* long2 __shift_left(long2, long2(k)); */
extern long3 __shift_left(long3, long3);
/* long3 __shift_left(long3, long3(k)); */
extern long4 __shift_left(long4, long4);
/* long4 __shift_left(long4, long4(k)); */
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __shift_left(long8, long8);
/* long8 __shift_left(long8, long8(k)); */
#endif

/* SHLD */
extern uint64_t __shift_left(uint64_t, uint8_t/*(k={0-63})*/);
extern uint64_t __shift_left(uint64_t, uint32_t);

/* VSHLD */
extern uint64_t __shift_left(uint64_t, uint64_t);
/* uint64_t __shift_left(uint64_t, uint64_t(k)); */
extern ulong2 __shift_left(ulong2, ulong2);
/* ulong2 __shift_left(ulong2, ulong2(k)); */
extern ulong3 __shift_left(ulong3, ulong3);
/* ulong3 __shift_left(ulong3, ulong3(k)); */
extern ulong4 __shift_left(ulong4, ulong4);
/* ulong4 __shift_left(ulong4, ulong4(k)); */
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __shift_left(ulong8, ulong8);
/* ulong8 __shift_left(ulong8, ulong8(k)); */
#endif

/*----------------------------------------------------------------------------*/
/* ID: __shift_left_conditional                                               */
/*----------------------------------------------------------------------------*/

/* VSHLCB */
extern char2 __shift_left_conditional(bool2, char2, char2);
extern char3 __shift_left_conditional(bool3, char3, char3);
extern char4 __shift_left_conditional(bool4, char4, char4);
extern char8 __shift_left_conditional(bool8, char8, char8);
extern char16 __shift_left_conditional(bool16, char16, char16);
extern char32 __shift_left_conditional(bool32, char32, char32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __shift_left_conditional(bool64, char64, char64);
#endif
extern uchar2 __shift_left_conditional(bool2, uchar2, uchar2);
extern uchar3 __shift_left_conditional(bool3, uchar3, uchar3);
extern uchar4 __shift_left_conditional(bool4, uchar4, uchar4);
extern uchar8 __shift_left_conditional(bool8, uchar8, uchar8);
extern uchar16 __shift_left_conditional(bool16, uchar16, uchar16);
extern uchar32 __shift_left_conditional(bool32, uchar32, uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __shift_left_conditional(bool64, uchar64, uchar64);
#endif

/* VSHLCH */
extern short2 __shift_left_conditional(bool2, short2, short2);
extern short3 __shift_left_conditional(bool3, short3, short3);
extern short4 __shift_left_conditional(bool4, short4, short4);
extern short8 __shift_left_conditional(bool8, short8, short8);
extern short16 __shift_left_conditional(bool16, short16, short16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __shift_left_conditional(bool32, short32, short32);
#endif
extern ushort2 __shift_left_conditional(bool2, ushort2, ushort2);
extern ushort3 __shift_left_conditional(bool3, ushort3, ushort3);
extern ushort4 __shift_left_conditional(bool4, ushort4, ushort4);
extern ushort8 __shift_left_conditional(bool8, ushort8, ushort8);
extern ushort16 __shift_left_conditional(bool16, ushort16, ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __shift_left_conditional(bool32, ushort32, ushort32);
#endif

/* VSHLCW */
extern int2 __shift_left_conditional(bool2, int2, int2);
extern int3 __shift_left_conditional(bool3, int3, int3);
extern int4 __shift_left_conditional(bool4, int4, int4);
extern int8 __shift_left_conditional(bool8, int8, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __shift_left_conditional(bool16, int16, int16);
#endif
extern uint2 __shift_left_conditional(bool2, uint2, uint2);
extern uint3 __shift_left_conditional(bool3, uint3, uint3);
extern uint4 __shift_left_conditional(bool4, uint4, uint4);
extern uint8 __shift_left_conditional(bool8, uint8, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __shift_left_conditional(bool16, uint16, uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __shift_left_full                                                      */
/*----------------------------------------------------------------------------*/

/* VSHL */
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __shift_left_full(ulong8, uint8_t/*(k={1-64})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __shift_left_full(ulong4, uint8_t/*(k={1-64})*/);
extern ulong4 __shift_left_full(ulong4, ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __shift_left_full(ulong8, ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __shift_left_merge                                                     */
/*----------------------------------------------------------------------------*/

/* VSHLM1B */
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __shift_left_merge(char64, int8_t);
#endif

/* VSHLM1B, VSHLM2B */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __shift_left_merge(char32, int8_t);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __shift_left_merge(char64, char2);
#endif

/* VSHLM2B, VSHLM4B */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __shift_left_merge(char32, char2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __shift_left_merge(char64, char4);
#endif

/* VSHLM4B, VSHLM8B */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __shift_left_merge(char32, char4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __shift_left_merge(char64, char8);
#endif

/* VSHLM16B, VSHLM8B */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __shift_left_merge(char32, char8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __shift_left_merge(char64, char16);
#endif

/* VSHLM16B */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __shift_left_merge(char32, char16);
#endif

/* VSHLMB */
extern int32_t __shift_left_merge(int32_t, char4);
extern int2 __shift_left_merge(int2, char8);
extern int4 __shift_left_merge(int4, char16);
extern int8 __shift_left_merge(int8, char32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __shift_left_merge(int16, char64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __shift_left_round_sat                                                 */
/*----------------------------------------------------------------------------*/

/* VSSHLRHB */
extern char4 __shift_left_round_sat(short2, uint8_t/*(k={0-63})*/);
extern char8 __shift_left_round_sat(short4, uchar2/*(k={0-63})*/);
extern char16 __shift_left_round_sat(short8, uchar4/*(k={0-63})*/);
extern char32 __shift_left_round_sat(short16, uchar8/*(k={0-63})*/);
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __shift_left_round_sat(short32, uchar16/*(k={0-63})*/);
#endif
extern char4 __shift_left_round_sat(short2, uint32_t);
extern char8 __shift_left_round_sat(short4, uint2);
extern char16 __shift_left_round_sat(short8, uint4);
extern char32 __shift_left_round_sat(short16, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __shift_left_round_sat(short32, uint16);
#endif

/* VSSHLURHB */
extern uchar4 __shift_left_round_sat(ushort2, uint8_t/*(k={0-63})*/);
extern uchar8 __shift_left_round_sat(ushort4, uchar2/*(k={0-63})*/);
extern uchar16 __shift_left_round_sat(ushort8, uchar4/*(k={0-63})*/);
extern uchar32 __shift_left_round_sat(ushort16, uchar8/*(k={0-63})*/);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __shift_left_round_sat(ushort32, uchar16/*(k={0-63})*/);
#endif
extern uchar4 __shift_left_round_sat(ushort2, uint32_t);
extern uchar8 __shift_left_round_sat(ushort4, uint2);
extern uchar16 __shift_left_round_sat(ushort8, uint4);
extern uchar32 __shift_left_round_sat(ushort16, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __shift_left_round_sat(ushort32, uint16);
#endif

/* VSSHLRWH */
extern short2 __shift_left_round_sat(int32_t, uint8_t/*(k={0-63})*/);
extern short4 __shift_left_round_sat(int2, uchar2/*(k={0-63})*/);
extern short8 __shift_left_round_sat(int4, uchar4/*(k={0-63})*/);
extern short16 __shift_left_round_sat(int8, uchar8/*(k={0-63})*/);
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __shift_left_round_sat(int16, uchar16/*(k={0-63})*/);
#endif
extern short2 __shift_left_round_sat(int32_t, uint32_t);
extern short4 __shift_left_round_sat(int2, uint2);
extern short8 __shift_left_round_sat(int4, uint4);
extern short16 __shift_left_round_sat(int8, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __shift_left_round_sat(int16, uint16);
#endif

/* VSSHLURWH */
extern ushort2 __shift_left_round_sat(uint32_t, uint8_t/*(k={0-63})*/);
extern ushort4 __shift_left_round_sat(uint2, uchar2/*(k={0-63})*/);
extern ushort8 __shift_left_round_sat(uint4, uchar4/*(k={0-63})*/);
extern ushort16 __shift_left_round_sat(uint8, uchar8/*(k={0-63})*/);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __shift_left_round_sat(uint16, uchar16/*(k={0-63})*/);
#endif
extern ushort2 __shift_left_round_sat(uint32_t, uint32_t);
extern ushort4 __shift_left_round_sat(uint2, uint2);
extern ushort8 __shift_left_round_sat(uint4, uint4);
extern ushort16 __shift_left_round_sat(uint8, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __shift_left_round_sat(uint16, uint16);
#endif

/* VSSHLRDW */
extern int2 __shift_left_round_sat(int64_t, uint8_t/*(k={0-63})*/);
extern int4 __shift_left_round_sat(long2, uchar2/*(k={0-63})*/);
extern int8 __shift_left_round_sat(long4, uchar4/*(k={0-63})*/);
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __shift_left_round_sat(long8, uchar8/*(k={0-63})*/);
#endif
extern int2 __shift_left_round_sat(int64_t, uint64_t);
extern int4 __shift_left_round_sat(long2, ulong2);
extern int8 __shift_left_round_sat(long4, ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __shift_left_round_sat(long8, ulong8);
#endif

/* VSSHLURDW */
extern uint2 __shift_left_round_sat(uint64_t, uint8_t/*(k={0-63})*/);
extern uint4 __shift_left_round_sat(ulong2, uchar2/*(k={0-63})*/);
extern uint8 __shift_left_round_sat(ulong4, uchar4/*(k={0-63})*/);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __shift_left_round_sat(ulong8, uchar8/*(k={0-63})*/);
#endif
extern uint2 __shift_left_round_sat(uint64_t, uint64_t);
extern uint4 __shift_left_round_sat(ulong2, ulong2);
extern uint8 __shift_left_round_sat(ulong4, ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __shift_left_round_sat(ulong8, ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __shift_left_round_sat_to_unsigned                                     */
/*----------------------------------------------------------------------------*/

/* VSSHLSURHB */
extern uchar4 __shift_left_round_sat_to_unsigned(short2, uint8_t/*(k={0-63})*/);
extern uchar8 __shift_left_round_sat_to_unsigned(short4, uchar2/*(k={0-63})*/);
extern uchar16 __shift_left_round_sat_to_unsigned(short8, uchar4/*(k={0-63})*/);
extern uchar32 __shift_left_round_sat_to_unsigned(short16, uchar8/*(k={0-63})*/);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __shift_left_round_sat_to_unsigned(short32, uchar16/*(k={0-63})*/);
#endif
extern uchar4 __shift_left_round_sat_to_unsigned(short2, uint32_t);
extern uchar8 __shift_left_round_sat_to_unsigned(short4, uint2);
extern uchar16 __shift_left_round_sat_to_unsigned(short8, uint4);
extern uchar32 __shift_left_round_sat_to_unsigned(short16, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __shift_left_round_sat_to_unsigned(short32, uint16);
#endif

/* VSSHLSURWH */
extern ushort2 __shift_left_round_sat_to_unsigned(int32_t, uint8_t/*(k={0-63})*/);
extern ushort4 __shift_left_round_sat_to_unsigned(int2, uchar2/*(k={0-63})*/);
extern ushort8 __shift_left_round_sat_to_unsigned(int4, uchar4/*(k={0-63})*/);
extern ushort16 __shift_left_round_sat_to_unsigned(int8, uchar8/*(k={0-63})*/);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __shift_left_round_sat_to_unsigned(int16, uchar16/*(k={0-63})*/);
#endif
extern ushort2 __shift_left_round_sat_to_unsigned(int32_t, uint32_t);
extern ushort4 __shift_left_round_sat_to_unsigned(int2, uint2);
extern ushort8 __shift_left_round_sat_to_unsigned(int4, uint4);
extern ushort16 __shift_left_round_sat_to_unsigned(int8, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __shift_left_round_sat_to_unsigned(int16, uint16);
#endif

/* VSSHLSURDW */
extern uint2 __shift_left_round_sat_to_unsigned(int64_t, uint8_t/*(k={0-63})*/);
extern uint4 __shift_left_round_sat_to_unsigned(long2, uchar2/*(k={0-63})*/);
extern uint8 __shift_left_round_sat_to_unsigned(long4, uchar4/*(k={0-63})*/);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __shift_left_round_sat_to_unsigned(long8, uchar8/*(k={0-63})*/);
#endif
extern uint2 __shift_left_round_sat_to_unsigned(int64_t, uint64_t);
extern uint4 __shift_left_round_sat_to_unsigned(long2, ulong2);
extern uint8 __shift_left_round_sat_to_unsigned(long4, ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __shift_left_round_sat_to_unsigned(long8, ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __shift_left_sat                                                       */
/*----------------------------------------------------------------------------*/

/* VSSHLH */
extern int16_t __shift_left_sat(int16_t, uint8_t/*(k={0-63})*/);
extern short2 __shift_left_sat(short2, uchar2/*(k={0-63})*/);
extern short3 __shift_left_sat(short3, uchar3/*(k={0-63})*/);
extern short4 __shift_left_sat(short4, uchar4/*(k={0-63})*/);
extern short8 __shift_left_sat(short8, uchar8/*(k={0-63})*/);
extern short16 __shift_left_sat(short16, uchar16/*(k={0-63})*/);
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __shift_left_sat(short32, uchar32/*(k={0-63})*/);
#endif
extern short2 __shift_left_sat(short2, uint32_t);
extern short4 __shift_left_sat(short4, uint2);
extern short8 __shift_left_sat(short8, uint4);
extern short16 __shift_left_sat(short16, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __shift_left_sat(short32, uint16);
#endif

/* VSSHLUH */
extern uint16_t __shift_left_sat(uint16_t, uint8_t/*(k={0-63})*/);
extern ushort2 __shift_left_sat(ushort2, uchar2/*(k={0-63})*/);
extern ushort3 __shift_left_sat(ushort3, uchar3/*(k={0-63})*/);
extern ushort4 __shift_left_sat(ushort4, uchar4/*(k={0-63})*/);
extern ushort8 __shift_left_sat(ushort8, uchar8/*(k={0-63})*/);
extern ushort16 __shift_left_sat(ushort16, uchar16/*(k={0-63})*/);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __shift_left_sat(ushort32, uchar32/*(k={0-63})*/);
#endif
extern ushort2 __shift_left_sat(ushort2, uint32_t);
extern ushort4 __shift_left_sat(ushort4, uint2);
extern ushort8 __shift_left_sat(ushort8, uint4);
extern ushort16 __shift_left_sat(ushort16, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __shift_left_sat(ushort32, uint16);
#endif

/* VSSHLW */
extern int32_t __shift_left_sat(int32_t, uint8_t/*(k={0-63})*/);
extern int2 __shift_left_sat(int2, uchar2/*(k={0-63})*/);
extern int3 __shift_left_sat(int3, uchar3/*(k={0-63})*/);
extern int4 __shift_left_sat(int4, uchar4/*(k={0-63})*/);
extern int8 __shift_left_sat(int8, uchar8/*(k={0-63})*/);
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __shift_left_sat(int16, uchar16/*(k={0-63})*/);
#endif
extern int32_t __shift_left_sat(int32_t, uint32_t);
extern int2 __shift_left_sat(int2, uint2);
extern int3 __shift_left_sat(int3, uint3);
extern int4 __shift_left_sat(int4, uint4);
extern int8 __shift_left_sat(int8, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __shift_left_sat(int16, uint16);
#endif

/* VSSHLUW */
extern uint32_t __shift_left_sat(uint32_t, uint8_t/*(k={0-63})*/);
extern uint2 __shift_left_sat(uint2, uchar2/*(k={0-63})*/);
extern uint3 __shift_left_sat(uint3, uchar3/*(k={0-63})*/);
extern uint4 __shift_left_sat(uint4, uchar4/*(k={0-63})*/);
extern uint8 __shift_left_sat(uint8, uchar8/*(k={0-63})*/);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __shift_left_sat(uint16, uchar16/*(k={0-63})*/);
#endif
extern uint32_t __shift_left_sat(uint32_t, uint32_t);
extern uint2 __shift_left_sat(uint2, uint2);
extern uint3 __shift_left_sat(uint3, uint3);
extern uint4 __shift_left_sat(uint4, uint4);
extern uint8 __shift_left_sat(uint8, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __shift_left_sat(uint16, uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __shift_left_sat_to_unsigned                                           */
/*----------------------------------------------------------------------------*/

/* VSSHLSUH */
extern uint16_t __shift_left_sat_to_unsigned(int16_t, uint8_t/*(k={0-63})*/);
extern ushort2 __shift_left_sat_to_unsigned(short2, uchar2/*(k={0-63})*/);
extern ushort3 __shift_left_sat_to_unsigned(short3, uchar3/*(k={0-63})*/);
extern ushort4 __shift_left_sat_to_unsigned(short4, uchar4/*(k={0-63})*/);
extern ushort8 __shift_left_sat_to_unsigned(short8, uchar8/*(k={0-63})*/);
extern ushort16 __shift_left_sat_to_unsigned(short16, uchar16/*(k={0-63})*/);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __shift_left_sat_to_unsigned(short32, uchar32/*(k={0-63})*/);
#endif
extern ushort2 __shift_left_sat_to_unsigned(short2, uint32_t);
extern ushort4 __shift_left_sat_to_unsigned(short4, uint2);
extern ushort8 __shift_left_sat_to_unsigned(short8, uint4);
extern ushort16 __shift_left_sat_to_unsigned(short16, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __shift_left_sat_to_unsigned(short32, uint16);
#endif

/* VSSHLSUW */
extern uint32_t __shift_left_sat_to_unsigned(int32_t, uint8_t/*(k={0-63})*/);
extern uint2 __shift_left_sat_to_unsigned(int2, uchar2/*(k={0-63})*/);
extern uint3 __shift_left_sat_to_unsigned(int3, uchar3/*(k={0-63})*/);
extern uint4 __shift_left_sat_to_unsigned(int4, uchar4/*(k={0-63})*/);
extern uint8 __shift_left_sat_to_unsigned(int8, uchar8/*(k={0-63})*/);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __shift_left_sat_to_unsigned(int16, uchar16/*(k={0-63})*/);
#endif
extern uint32_t __shift_left_sat_to_unsigned(int32_t, uint32_t);
extern uint2 __shift_left_sat_to_unsigned(int2, uint2);
extern uint3 __shift_left_sat_to_unsigned(int3, uint3);
extern uint4 __shift_left_sat_to_unsigned(int4, uint4);
extern uint8 __shift_left_sat_to_unsigned(int8, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __shift_left_sat_to_unsigned(int16, uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __shift_left_var                                                       */
/*----------------------------------------------------------------------------*/

/* VSHVLW */
extern int32_t __shift_left_var(int32_t, int32_t);
extern int2 __shift_left_var(int2, int2);
extern int3 __shift_left_var(int3, int3);
extern int4 __shift_left_var(int4, int4);
extern int8 __shift_left_var(int8, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __shift_left_var(int16, int16);
#endif

/* VSHVLUW */
extern uint32_t __shift_left_var(uint32_t, int32_t);
extern uint2 __shift_left_var(uint2, int2);
extern uint3 __shift_left_var(uint3, int3);
extern uint4 __shift_left_var(uint4, int4);
extern uint8 __shift_left_var(uint8, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __shift_left_var(uint16, int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __shift_left_var_sat                                                   */
/*----------------------------------------------------------------------------*/

/* VSSHVLW */
extern int32_t __shift_left_var_sat(int32_t, int32_t);
extern int2 __shift_left_var_sat(int2, int2);
extern int3 __shift_left_var_sat(int3, int3);
extern int4 __shift_left_var_sat(int4, int4);
extern int8 __shift_left_var_sat(int8, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __shift_left_var_sat(int16, int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __shift_right                                                          */
/*----------------------------------------------------------------------------*/

/* VSHRB */
extern int8_t __shift_right(int8_t, int8_t/*(k={0-63})*/);
extern char2 __shift_right(char2, char2/*(k={0-63})*/);
extern char3 __shift_right(char3, char3/*(k={0-63})*/);
extern char4 __shift_right(char4, char4/*(k={0-63})*/);
extern char8 __shift_right(char8, char8/*(k={0-63})*/);
extern char16 __shift_right(char16, char16/*(k={0-63})*/);
extern char32 __shift_right(char32, char32/*(k={0-63})*/);
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __shift_right(char64, char64/*(k={0-63})*/);
#endif
extern char4 __shift_right(char4, int32_t);
extern char8 __shift_right(char8, int2);
extern char16 __shift_right(char16, int4);
extern char32 __shift_right(char32, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __shift_right(char64, int16);
#endif

/* VSHRUB */
extern uint8_t __shift_right(uint8_t, uint8_t/*(k={0-63})*/);
extern uchar2 __shift_right(uchar2, uchar2/*(k={0-63})*/);
extern uchar3 __shift_right(uchar3, uchar3/*(k={0-63})*/);
extern uchar4 __shift_right(uchar4, uchar4/*(k={0-63})*/);
extern uchar8 __shift_right(uchar8, uchar8/*(k={0-63})*/);
extern uchar16 __shift_right(uchar16, uchar16/*(k={0-63})*/);
extern uchar32 __shift_right(uchar32, uchar32/*(k={0-63})*/);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __shift_right(uchar64, uchar64/*(k={0-63})*/);
#endif
extern uchar4 __shift_right(uchar4, uint32_t);
extern uchar8 __shift_right(uchar8, uint2);
extern uchar16 __shift_right(uchar16, uint4);
extern uchar32 __shift_right(uchar32, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __shift_right(uchar64, uint16);
#endif

/* VSHRH */
extern int16_t __shift_right(int16_t, int16_t/*(k={0-63})*/);
extern short2 __shift_right(short2, short2/*(k={0-63})*/);
extern short3 __shift_right(short3, short3/*(k={0-63})*/);
extern short4 __shift_right(short4, short4/*(k={0-63})*/);
extern short8 __shift_right(short8, short8/*(k={0-63})*/);
extern short16 __shift_right(short16, short16/*(k={0-63})*/);
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __shift_right(short32, short32/*(k={0-63})*/);
#endif
extern short2 __shift_right(short2, int32_t);
extern short4 __shift_right(short4, int2);
extern short8 __shift_right(short8, int4);
extern short16 __shift_right(short16, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __shift_right(short32, int16);
#endif

/* VSHRUH */
extern uint16_t __shift_right(uint16_t, uint16_t/*(k={0-63})*/);
extern ushort2 __shift_right(ushort2, ushort2/*(k={0-63})*/);
extern ushort3 __shift_right(ushort3, ushort3/*(k={0-63})*/);
extern ushort4 __shift_right(ushort4, ushort4/*(k={0-63})*/);
extern ushort8 __shift_right(ushort8, ushort8/*(k={0-63})*/);
extern ushort16 __shift_right(ushort16, ushort16/*(k={0-63})*/);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __shift_right(ushort32, ushort32/*(k={0-63})*/);
#endif
extern ushort2 __shift_right(ushort2, uint32_t);
extern ushort4 __shift_right(ushort4, uint2);
extern ushort8 __shift_right(ushort8, uint4);
extern ushort16 __shift_right(ushort16, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __shift_right(ushort32, uint16);
#endif

/* SHRW */
extern int32_t __shift_right(int32_t, uint8_t/*(k={0-63})*/);

/* SHRW, VSHRW */
extern int32_t __shift_right(int32_t, int32_t);
/* int32_t __shift_right(int32_t, int32_t(k)); */
extern int2 __shift_right(int2, int2);
/* int2 __shift_right(int2, int2(k)); */
extern int3 __shift_right(int3, int3);
/* int3 __shift_right(int3, int3(k)); */
extern int4 __shift_right(int4, int4);
/* int4 __shift_right(int4, int4(k)); */
extern int8 __shift_right(int8, int8);
/* int8 __shift_right(int8, int8(k)); */
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __shift_right(int16, int16);
/* int16 __shift_right(int16, int16(k)); */
#endif

/* SHRUW */
extern uint32_t __shift_right(uint32_t, uint8_t/*(k={0-63})*/);

/* SHRUW, VSHRUW */
extern uint32_t __shift_right(uint32_t, uint32_t);
/* uint32_t __shift_right(uint32_t, uint32_t(k)); */
extern uint2 __shift_right(uint2, uint2);
/* uint2 __shift_right(uint2, uint2(k)); */
extern uint3 __shift_right(uint3, uint3);
/* uint3 __shift_right(uint3, uint3(k)); */
extern uint4 __shift_right(uint4, uint4);
/* uint4 __shift_right(uint4, uint4(k)); */
extern uint8 __shift_right(uint8, uint8);
/* uint8 __shift_right(uint8, uint8(k)); */
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __shift_right(uint16, uint16);
/* uint16 __shift_right(uint16, uint16(k)); */
#endif

/* SHRD */
extern int64_t __shift_right(int64_t, uint8_t/*(k={0-63})*/);
extern int64_t __shift_right(int64_t, int32_t);

/* VSHRD */
extern int64_t __shift_right(int64_t, int64_t);
/* int64_t __shift_right(int64_t, int64_t(k)); */
extern long2 __shift_right(long2, long2);
/* long2 __shift_right(long2, long2(k)); */
extern long3 __shift_right(long3, long3);
/* long3 __shift_right(long3, long3(k)); */
extern long4 __shift_right(long4, long4);
/* long4 __shift_right(long4, long4(k)); */
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __shift_right(long8, long8);
/* long8 __shift_right(long8, long8(k)); */
#endif

/* SHRUD */
extern uint64_t __shift_right(uint64_t, uint8_t/*(k={0-63})*/);
extern uint64_t __shift_right(uint64_t, uint32_t);

/* VSHRUD */
extern uint64_t __shift_right(uint64_t, uint64_t);
/* uint64_t __shift_right(uint64_t, uint64_t(k)); */
extern ulong2 __shift_right(ulong2, ulong2);
/* ulong2 __shift_right(ulong2, ulong2(k)); */
extern ulong3 __shift_right(ulong3, ulong3);
/* ulong3 __shift_right(ulong3, ulong3(k)); */
extern ulong4 __shift_right(ulong4, ulong4);
/* ulong4 __shift_right(ulong4, ulong4(k)); */
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __shift_right(ulong8, ulong8);
/* ulong8 __shift_right(ulong8, ulong8(k)); */
#endif

/*----------------------------------------------------------------------------*/
/* ID: __shift_right_full                                                     */
/*----------------------------------------------------------------------------*/

/* VSHR */
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __shift_right_full(long8, uint8_t/*(k={1-64})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __shift_right_full(long4, uint8_t/*(k={1-64})*/);
extern long4 __shift_right_full(long4, ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __shift_right_full(long8, ulong8);
#endif

/* VSHRU */
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __shift_right_full(ulong8, uint8_t/*(k={1-64})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __shift_right_full(ulong4, uint8_t/*(k={1-64})*/);
extern ulong4 __shift_right_full(ulong4, ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __shift_right_full(ulong8, ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __shift_right_merge                                                    */
/*----------------------------------------------------------------------------*/

/* VSHRM1B */
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __shift_right_merge(char64, int8_t);
#endif

/* VSHRM1B, VSHRM2B */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __shift_right_merge(char32, int8_t);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __shift_right_merge(char64, char2);
#endif

/* VSHRM2B, VSHRM4B */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __shift_right_merge(char32, char2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __shift_right_merge(char64, char4);
#endif

/* VSHRM4B, VSHRM8B */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __shift_right_merge(char32, char4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __shift_right_merge(char64, char8);
#endif

/* VSHRM16B, VSHRM8B */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __shift_right_merge(char32, char8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __shift_right_merge(char64, char16);
#endif

/* VSHRM16B */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __shift_right_merge(char32, char16);
#endif

/* VSHRMB */
extern int32_t __shift_right_merge(int32_t, char4);
extern int2 __shift_right_merge(int2, char8);
extern int4 __shift_right_merge(int4, char16);
extern int8 __shift_right_merge(int8, char32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __shift_right_merge(int16, char64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __shift_right_round                                                    */
/*----------------------------------------------------------------------------*/

/* VSHRRB */
extern int8_t __shift_right_round(int8_t, uint8_t/*(k={0-63})*/);
extern char2 __shift_right_round(char2, uchar2/*(k={0-63})*/);
extern char3 __shift_right_round(char3, uchar3/*(k={0-63})*/);
extern char4 __shift_right_round(char4, uchar4/*(k={0-63})*/);
extern char8 __shift_right_round(char8, uchar8/*(k={0-63})*/);
extern char16 __shift_right_round(char16, uchar16/*(k={0-63})*/);
extern char32 __shift_right_round(char32, uchar32/*(k={0-63})*/);
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __shift_right_round(char64, uchar64/*(k={0-63})*/);
#endif
extern char4 __shift_right_round(char4, uint32_t);
extern char8 __shift_right_round(char8, uint2);
extern char16 __shift_right_round(char16, uint4);
extern char32 __shift_right_round(char32, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __shift_right_round(char64, uint16);
#endif

/* VSHRURB */
extern uint8_t __shift_right_round(uint8_t, uint8_t/*(k={0-63})*/);
extern uchar2 __shift_right_round(uchar2, uchar2/*(k={0-63})*/);
extern uchar3 __shift_right_round(uchar3, uchar3/*(k={0-63})*/);
extern uchar4 __shift_right_round(uchar4, uchar4/*(k={0-63})*/);
extern uchar8 __shift_right_round(uchar8, uchar8/*(k={0-63})*/);
extern uchar16 __shift_right_round(uchar16, uchar16/*(k={0-63})*/);
extern uchar32 __shift_right_round(uchar32, uchar32/*(k={0-63})*/);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __shift_right_round(uchar64, uchar64/*(k={0-63})*/);
#endif
extern uchar4 __shift_right_round(uchar4, uint32_t);
extern uchar8 __shift_right_round(uchar8, uint2);
extern uchar16 __shift_right_round(uchar16, uint4);
extern uchar32 __shift_right_round(uchar32, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __shift_right_round(uchar64, uint16);
#endif

/* VSHRRH */
extern int16_t __shift_right_round(int16_t, uint8_t/*(k={0-63})*/);
extern short2 __shift_right_round(short2, uchar2/*(k={0-63})*/);
extern short3 __shift_right_round(short3, uchar3/*(k={0-63})*/);
extern short4 __shift_right_round(short4, uchar4/*(k={0-63})*/);
extern short8 __shift_right_round(short8, uchar8/*(k={0-63})*/);
extern short16 __shift_right_round(short16, uchar16/*(k={0-63})*/);
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __shift_right_round(short32, uchar32/*(k={0-63})*/);
#endif
extern short2 __shift_right_round(short2, uint32_t);
extern short4 __shift_right_round(short4, uint2);
extern short8 __shift_right_round(short8, uint4);
extern short16 __shift_right_round(short16, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __shift_right_round(short32, uint16);
#endif

/* VSHRURH */
extern uint16_t __shift_right_round(uint16_t, uint8_t/*(k={0-63})*/);
extern ushort2 __shift_right_round(ushort2, uchar2/*(k={0-63})*/);
extern ushort3 __shift_right_round(ushort3, uchar3/*(k={0-63})*/);
extern ushort4 __shift_right_round(ushort4, uchar4/*(k={0-63})*/);
extern ushort8 __shift_right_round(ushort8, uchar8/*(k={0-63})*/);
extern ushort16 __shift_right_round(ushort16, uchar16/*(k={0-63})*/);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __shift_right_round(ushort32, uchar32/*(k={0-63})*/);
#endif
extern ushort2 __shift_right_round(ushort2, uint32_t);
extern ushort4 __shift_right_round(ushort4, uint2);
extern ushort8 __shift_right_round(ushort8, uint4);
extern ushort16 __shift_right_round(ushort16, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __shift_right_round(ushort32, uint16);
#endif

/* VSHRRW */
extern int32_t __shift_right_round(int32_t, uint8_t/*(k={0-63})*/);
extern int2 __shift_right_round(int2, uchar2/*(k={0-63})*/);
extern int3 __shift_right_round(int3, uchar3/*(k={0-63})*/);
extern int4 __shift_right_round(int4, uchar4/*(k={0-63})*/);
extern int8 __shift_right_round(int8, uchar8/*(k={0-63})*/);
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __shift_right_round(int16, uchar16/*(k={0-63})*/);
#endif
extern int32_t __shift_right_round(int32_t, uint32_t);
extern int2 __shift_right_round(int2, uint2);
extern int3 __shift_right_round(int3, uint3);
extern int4 __shift_right_round(int4, uint4);
extern int8 __shift_right_round(int8, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __shift_right_round(int16, uint16);
#endif

/* VSHRURW */
extern uint32_t __shift_right_round(uint32_t, uint8_t/*(k={0-63})*/);
extern uint2 __shift_right_round(uint2, uchar2/*(k={0-63})*/);
extern uint3 __shift_right_round(uint3, uchar3/*(k={0-63})*/);
extern uint4 __shift_right_round(uint4, uchar4/*(k={0-63})*/);
extern uint8 __shift_right_round(uint8, uchar8/*(k={0-63})*/);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __shift_right_round(uint16, uchar16/*(k={0-63})*/);
#endif
extern uint32_t __shift_right_round(uint32_t, uint32_t);
extern uint2 __shift_right_round(uint2, uint2);
extern uint3 __shift_right_round(uint3, uint3);
extern uint4 __shift_right_round(uint4, uint4);
extern uint8 __shift_right_round(uint8, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __shift_right_round(uint16, uint16);
#endif

/* VSHRRD */
extern int64_t __shift_right_round(int64_t, uint8_t/*(k={0-63})*/);
extern long2 __shift_right_round(long2, uchar2/*(k={0-63})*/);
extern long3 __shift_right_round(long3, uchar3/*(k={0-63})*/);
extern long4 __shift_right_round(long4, uchar4/*(k={0-63})*/);
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __shift_right_round(long8, uchar8/*(k={0-63})*/);
#endif
extern int64_t __shift_right_round(int64_t, uint64_t);
extern long2 __shift_right_round(long2, ulong2);
extern long3 __shift_right_round(long3, ulong3);
extern long4 __shift_right_round(long4, ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __shift_right_round(long8, ulong8);
#endif

/* VSHRURD */
extern uint64_t __shift_right_round(uint64_t, uint8_t/*(k={0-63})*/);
extern ulong2 __shift_right_round(ulong2, uchar2/*(k={0-63})*/);
extern ulong3 __shift_right_round(ulong3, uchar3/*(k={0-63})*/);
extern ulong4 __shift_right_round(ulong4, uchar4/*(k={0-63})*/);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __shift_right_round(ulong8, uchar8/*(k={0-63})*/);
#endif
extern uint64_t __shift_right_round(uint64_t, uint64_t);
extern ulong2 __shift_right_round(ulong2, ulong2);
extern ulong3 __shift_right_round(ulong3, ulong3);
extern ulong4 __shift_right_round(ulong4, ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __shift_right_round(ulong8, ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __shift_right_var                                                      */
/*----------------------------------------------------------------------------*/

/* VSHVRW */
extern int32_t __shift_right_var(int32_t, int32_t);
extern int2 __shift_right_var(int2, int2);
extern int3 __shift_right_var(int3, int3);
extern int4 __shift_right_var(int4, int4);
extern int8 __shift_right_var(int8, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __shift_right_var(int16, int16);
#endif

/* VSHVRUW */
extern uint32_t __shift_right_var(uint32_t, int32_t);
extern uint2 __shift_right_var(uint2, int2);
extern uint3 __shift_right_var(uint3, int3);
extern uint4 __shift_right_var(uint4, int4);
extern uint8 __shift_right_var(uint8, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __shift_right_var(uint16, int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __shift_right_var_sat                                                  */
/*----------------------------------------------------------------------------*/

/* VSSHVRW */
extern int32_t __shift_right_var_sat(int32_t, int32_t);
extern int2 __shift_right_var_sat(int2, int2);
extern int3 __shift_right_var_sat(int3, int3);
extern int4 __shift_right_var_sat(int4, int4);
extern int8 __shift_right_var_sat(int8, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __shift_right_var_sat(int16, int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __short_to_char_sat                                                    */
/*----------------------------------------------------------------------------*/

/* VSATHB */
extern int16_t __short_to_char_sat(int16_t);
extern short2 __short_to_char_sat(short2);
extern short3 __short_to_char_sat(short3);
extern short4 __short_to_char_sat(short4);
extern short8 __short_to_char_sat(short8);
extern short16 __short_to_char_sat(short16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __short_to_char_sat(short32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __shuffle_3way                                                         */
/*----------------------------------------------------------------------------*/

/* VSHFL3 */
extern int64_t __shuffle_3way(int2, int2);
extern long2 __shuffle_3way(int4, int4);
extern long4 __shuffle_3way(int8, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __shuffle_3way(int16, int16);
#endif
extern uint64_t __shuffle_3way(uint2, uint2);
extern ulong2 __shuffle_3way(uint4, uint4);
extern ulong4 __shuffle_3way(uint8, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __shuffle_3way(uint16, uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __shuffle_bit                                                          */
/*----------------------------------------------------------------------------*/

/* VBITSHFLW */
extern int32_t __shuffle_bit(int32_t);
extern int2 __shuffle_bit(int2);
extern int3 __shuffle_bit(int3);
extern int4 __shuffle_bit(int4);
extern int8 __shuffle_bit(int8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __shuffle_bit(int16);
#endif
extern uint32_t __shuffle_bit(uint32_t);
extern uint2 __shuffle_bit(uint2);
extern uint3 __shuffle_bit(uint3);
extern uint4 __shuffle_bit(uint4);
extern uint8 __shuffle_bit(uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __shuffle_bit(uint16);
#endif

/* VBITSHFLD */
extern int64_t __shuffle_bit(int64_t);
extern long2 __shuffle_bit(long2);
extern long3 __shuffle_bit(long3);
extern long4 __shuffle_bit(long4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __shuffle_bit(long8);
#endif
extern uint64_t __shuffle_bit(uint64_t);
extern ulong2 __shuffle_bit(ulong2);
extern ulong3 __shuffle_bit(ulong3);
extern ulong4 __shuffle_bit(ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __shuffle_bit(ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __shuffle_stride2                                                      */
/*----------------------------------------------------------------------------*/

/* VSHFL2B */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __shuffle_stride2(char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __shuffle_stride2(char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __shuffle_stride2(uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __shuffle_stride2(uchar64);
#endif

/* VSHFL2H */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cchar16 __shuffle_stride2(cchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cchar32 __shuffle_stride2(cchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __shuffle_stride2(short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __shuffle_stride2(short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __shuffle_stride2(ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __shuffle_stride2(ushort32);
#endif

/* VSHFL2W */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cshort8 __shuffle_stride2(cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cshort16 __shuffle_stride2(cshort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __shuffle_stride2(int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __shuffle_stride2(int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __shuffle_stride2(uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __shuffle_stride2(uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern float8 __shuffle_stride2(float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern float16 __shuffle_stride2(float16);
#endif

/* VSHFL2D */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cint4 __shuffle_stride2(cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cint8 __shuffle_stride2(cint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cfloat4 __shuffle_stride2(cfloat4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cfloat8 __shuffle_stride2(cfloat8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __shuffle_stride2(long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __shuffle_stride2(long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __shuffle_stride2(ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __shuffle_stride2(ulong8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern double4 __shuffle_stride2(double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern double8 __shuffle_stride2(double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __shuffle_stride2_even_even                                            */
/*----------------------------------------------------------------------------*/

/* VSHFL2DEE */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cint4 __shuffle_stride2_even_even(cint4, cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cint8 __shuffle_stride2_even_even(cint8, cint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cfloat4 __shuffle_stride2_even_even(cfloat4, cfloat4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cfloat8 __shuffle_stride2_even_even(cfloat8, cfloat8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __shuffle_stride2_even_even(long4, long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __shuffle_stride2_even_even(long8, long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __shuffle_stride2_even_even(ulong4, ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __shuffle_stride2_even_even(ulong8, ulong8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern double4 __shuffle_stride2_even_even(double4, double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern double8 __shuffle_stride2_even_even(double8, double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __shuffle_stride2_even_odd                                             */
/*----------------------------------------------------------------------------*/

/* VSHFL2DEO */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cint4 __shuffle_stride2_even_odd(cint4, cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cint8 __shuffle_stride2_even_odd(cint8, cint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cfloat4 __shuffle_stride2_even_odd(cfloat4, cfloat4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cfloat8 __shuffle_stride2_even_odd(cfloat8, cfloat8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __shuffle_stride2_even_odd(long4, long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __shuffle_stride2_even_odd(long8, long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __shuffle_stride2_even_odd(ulong4, ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __shuffle_stride2_even_odd(ulong8, ulong8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern double4 __shuffle_stride2_even_odd(double4, double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern double8 __shuffle_stride2_even_odd(double8, double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __shuffle_stride2_high_high                                            */
/*----------------------------------------------------------------------------*/

/* VSHFL2HHH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cchar16 __shuffle_stride2_high_high(cchar16, cchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cchar32 __shuffle_stride2_high_high(cchar32, cchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __shuffle_stride2_high_high(short16, short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __shuffle_stride2_high_high(short32, short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __shuffle_stride2_high_high(ushort16, ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __shuffle_stride2_high_high(ushort32, ushort32);
#endif

/* VSHFL2WHH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cshort8 __shuffle_stride2_high_high(cshort8, cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cshort16 __shuffle_stride2_high_high(cshort16, cshort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __shuffle_stride2_high_high(int8, int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __shuffle_stride2_high_high(int16, int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __shuffle_stride2_high_high(uint8, uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __shuffle_stride2_high_high(uint16, uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern float8 __shuffle_stride2_high_high(float8, float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern float16 __shuffle_stride2_high_high(float16, float16);
#endif

/* VSHFL2DHH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cint4 __shuffle_stride2_high_high(cint4, cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cint8 __shuffle_stride2_high_high(cint8, cint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cfloat4 __shuffle_stride2_high_high(cfloat4, cfloat4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cfloat8 __shuffle_stride2_high_high(cfloat8, cfloat8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __shuffle_stride2_high_high(long4, long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __shuffle_stride2_high_high(long8, long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __shuffle_stride2_high_high(ulong4, ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __shuffle_stride2_high_high(ulong8, ulong8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern double4 __shuffle_stride2_high_high(double4, double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern double8 __shuffle_stride2_high_high(double8, double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __shuffle_stride2_low_high                                             */
/*----------------------------------------------------------------------------*/

/* VSHFL2DLH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cint4 __shuffle_stride2_low_high(cint4, cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cint8 __shuffle_stride2_low_high(cint8, cint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cfloat4 __shuffle_stride2_low_high(cfloat4, cfloat4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cfloat8 __shuffle_stride2_low_high(cfloat8, cfloat8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __shuffle_stride2_low_high(long4, long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __shuffle_stride2_low_high(long8, long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __shuffle_stride2_low_high(ulong4, ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __shuffle_stride2_low_high(ulong8, ulong8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern double4 __shuffle_stride2_low_high(double4, double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern double8 __shuffle_stride2_low_high(double8, double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __shuffle_stride2_low_low                                              */
/*----------------------------------------------------------------------------*/

/* VSHFL2HLL */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cchar16 __shuffle_stride2_low_low(cchar16, cchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cchar32 __shuffle_stride2_low_low(cchar32, cchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __shuffle_stride2_low_low(short16, short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __shuffle_stride2_low_low(short32, short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __shuffle_stride2_low_low(ushort16, ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __shuffle_stride2_low_low(ushort32, ushort32);
#endif

/* VSHFL2WLL */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cshort8 __shuffle_stride2_low_low(cshort8, cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cshort16 __shuffle_stride2_low_low(cshort16, cshort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __shuffle_stride2_low_low(int8, int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __shuffle_stride2_low_low(int16, int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __shuffle_stride2_low_low(uint8, uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __shuffle_stride2_low_low(uint16, uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern float8 __shuffle_stride2_low_low(float8, float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern float16 __shuffle_stride2_low_low(float16, float16);
#endif

/* VSHFL2DLL */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cint4 __shuffle_stride2_low_low(cint4, cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cint8 __shuffle_stride2_low_low(cint8, cint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cfloat4 __shuffle_stride2_low_low(cfloat4, cfloat4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cfloat8 __shuffle_stride2_low_low(cfloat8, cfloat8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __shuffle_stride2_low_low(long4, long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __shuffle_stride2_low_low(long8, long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __shuffle_stride2_low_low(ulong4, ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __shuffle_stride2_low_low(ulong8, ulong8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern double4 __shuffle_stride2_low_low(double4, double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern double8 __shuffle_stride2_low_low(double8, double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __shuffle_stride2_odd_odd                                              */
/*----------------------------------------------------------------------------*/

/* VSHFL2DOO */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cint4 __shuffle_stride2_odd_odd(cint4, cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cint8 __shuffle_stride2_odd_odd(cint8, cint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cfloat4 __shuffle_stride2_odd_odd(cfloat4, cfloat4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cfloat8 __shuffle_stride2_odd_odd(cfloat8, cfloat8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __shuffle_stride2_odd_odd(long4, long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __shuffle_stride2_odd_odd(long8, long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __shuffle_stride2_odd_odd(ulong4, ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __shuffle_stride2_odd_odd(ulong8, ulong8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern double4 __shuffle_stride2_odd_odd(double4, double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern double8 __shuffle_stride2_odd_odd(double8, double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __shuffle_stride4                                                      */
/*----------------------------------------------------------------------------*/

/* VSHFL4B */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __shuffle_stride4(char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __shuffle_stride4(char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __shuffle_stride4(uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __shuffle_stride4(uchar64);
#endif

/* VSHFL4H */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cchar16 __shuffle_stride4(cchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cchar32 __shuffle_stride4(cchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __shuffle_stride4(short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __shuffle_stride4(short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __shuffle_stride4(ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __shuffle_stride4(ushort32);
#endif

/* VSHFL4W */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cshort8 __shuffle_stride4(cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cshort16 __shuffle_stride4(cshort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __shuffle_stride4(int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __shuffle_stride4(int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __shuffle_stride4(uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __shuffle_stride4(uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern float8 __shuffle_stride4(float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern float16 __shuffle_stride4(float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __sort_asc                                                             */
/*----------------------------------------------------------------------------*/

/* VSORTIH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __sort_asc(short16);
#endif

/* VSORTIUH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __sort_asc(ushort16);
#endif

/* VSORTIW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __sort_asc(int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __sort_asc(int16);
#endif

/* VSORTIUW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __sort_asc(uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __sort_asc(uint16);
#endif

/* VSORTISP */
#if __C7X_VEC_SIZE_BITS__ == 256
extern float8 __sort_asc(float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern float16 __sort_asc(float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __sort_asc_perm                                                        */
/*----------------------------------------------------------------------------*/

/* VSORTPIW */
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __sort_asc_perm(int16);
#endif

/* VSORTPIUW */
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __sort_asc_perm(uint16);
#endif

/* VSORTPISP */
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __sort_asc_perm(float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __sort_desc                                                            */
/*----------------------------------------------------------------------------*/

/* VSORTDH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __sort_desc(short16);
#endif

/* VSORTDUH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __sort_desc(ushort16);
#endif

/* VSORTDW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __sort_desc(int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __sort_desc(int16);
#endif

/* VSORTDUW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __sort_desc(uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __sort_desc(uint16);
#endif

/* VSORTDSP */
#if __C7X_VEC_SIZE_BITS__ == 256
extern float8 __sort_desc(float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern float16 __sort_desc(float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __sort_desc_perm                                                       */
/*----------------------------------------------------------------------------*/

/* VSORTPDW */
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __sort_desc_perm(int16);
#endif

/* VSORTPDUW */
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __sort_desc_perm(uint16);
#endif

/* VSORTPDSP */
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __sort_desc_perm(float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __sub_cond                                                             */
/*----------------------------------------------------------------------------*/

/* VSUBCW */
extern uint32_t __sub_cond(uint32_t, uint32_t);
extern uint2 __sub_cond(uint2, uint2);
extern uint3 __sub_cond(uint3, uint3);
extern uint4 __sub_cond(uint4, uint4);
extern uint8 __sub_cond(uint8, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __sub_cond(uint16, uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __sub_reverse                                                          */
/*----------------------------------------------------------------------------*/

/* VSUBRB */
extern int8_t __sub_reverse(int8_t, int8_t);
/* int8_t __sub_reverse(int8_t, int8_t(k)); */
extern char2 __sub_reverse(char2, char2);
/* char2 __sub_reverse(char2, char2(k)); */
extern char3 __sub_reverse(char3, char3);
/* char3 __sub_reverse(char3, char3(k)); */
extern char4 __sub_reverse(char4, char4);
/* char4 __sub_reverse(char4, char4(k)); */
extern char8 __sub_reverse(char8, char8);
/* char8 __sub_reverse(char8, char8(k)); */
extern char16 __sub_reverse(char16, char16);
/* char16 __sub_reverse(char16, char16(k)); */
extern char32 __sub_reverse(char32, char32);
/* char32 __sub_reverse(char32, char32(k)); */
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __sub_reverse(char64, char64);
/* char64 __sub_reverse(char64, char64(k)); */
#endif
extern uint8_t __sub_reverse(uint8_t, uint8_t);
/* uint8_t __sub_reverse(uint8_t, uint8_t(k)); */
extern uchar2 __sub_reverse(uchar2, uchar2);
/* uchar2 __sub_reverse(uchar2, uchar2(k)); */
extern uchar3 __sub_reverse(uchar3, uchar3);
/* uchar3 __sub_reverse(uchar3, uchar3(k)); */
extern uchar4 __sub_reverse(uchar4, uchar4);
/* uchar4 __sub_reverse(uchar4, uchar4(k)); */
extern uchar8 __sub_reverse(uchar8, uchar8);
/* uchar8 __sub_reverse(uchar8, uchar8(k)); */
extern uchar16 __sub_reverse(uchar16, uchar16);
/* uchar16 __sub_reverse(uchar16, uchar16(k)); */
extern uchar32 __sub_reverse(uchar32, uchar32);
/* uchar32 __sub_reverse(uchar32, uchar32(k)); */
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __sub_reverse(uchar64, uchar64);
/* uchar64 __sub_reverse(uchar64, uchar64(k)); */
#endif
extern cchar __sub_reverse(cchar, cchar);
extern cchar2 __sub_reverse(cchar2, cchar2);
extern cchar4 __sub_reverse(cchar4, cchar4);
extern cchar8 __sub_reverse(cchar8, cchar8);
extern cchar16 __sub_reverse(cchar16, cchar16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern cchar32 __sub_reverse(cchar32, cchar32);
#endif

/* VSUBRH */
extern int16_t __sub_reverse(int16_t, int16_t);
/* int16_t __sub_reverse(int16_t, int16_t(k)); */
extern short2 __sub_reverse(short2, short2);
/* short2 __sub_reverse(short2, short2(k)); */
extern short3 __sub_reverse(short3, short3);
/* short3 __sub_reverse(short3, short3(k)); */
extern short4 __sub_reverse(short4, short4);
/* short4 __sub_reverse(short4, short4(k)); */
extern short8 __sub_reverse(short8, short8);
/* short8 __sub_reverse(short8, short8(k)); */
extern short16 __sub_reverse(short16, short16);
/* short16 __sub_reverse(short16, short16(k)); */
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __sub_reverse(short32, short32);
/* short32 __sub_reverse(short32, short32(k)); */
#endif
extern uint16_t __sub_reverse(uint16_t, uint16_t);
/* uint16_t __sub_reverse(uint16_t, uint16_t(k)); */
extern ushort2 __sub_reverse(ushort2, ushort2);
/* ushort2 __sub_reverse(ushort2, ushort2(k)); */
extern ushort3 __sub_reverse(ushort3, ushort3);
/* ushort3 __sub_reverse(ushort3, ushort3(k)); */
extern ushort4 __sub_reverse(ushort4, ushort4);
/* ushort4 __sub_reverse(ushort4, ushort4(k)); */
extern ushort8 __sub_reverse(ushort8, ushort8);
/* ushort8 __sub_reverse(ushort8, ushort8(k)); */
extern ushort16 __sub_reverse(ushort16, ushort16);
/* ushort16 __sub_reverse(ushort16, ushort16(k)); */
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __sub_reverse(ushort32, ushort32);
/* ushort32 __sub_reverse(ushort32, ushort32(k)); */
#endif
extern cshort __sub_reverse(cshort, cshort);
extern cshort2 __sub_reverse(cshort2, cshort2);
extern cshort4 __sub_reverse(cshort4, cshort4);
extern cshort8 __sub_reverse(cshort8, cshort8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern cshort16 __sub_reverse(cshort16, cshort16);
#endif

/* SUBRW, VSUBRW */
extern int32_t __sub_reverse(int32_t, int32_t);
/* int32_t __sub_reverse(int32_t, int32_t(k)); */
extern int2 __sub_reverse(int2, int2);
/* int2 __sub_reverse(int2, int2(k)); */
extern int3 __sub_reverse(int3, int3);
/* int3 __sub_reverse(int3, int3(k)); */
extern int4 __sub_reverse(int4, int4);
/* int4 __sub_reverse(int4, int4(k)); */
extern int8 __sub_reverse(int8, int8);
/* int8 __sub_reverse(int8, int8(k)); */
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __sub_reverse(int16, int16);
/* int16 __sub_reverse(int16, int16(k)); */
#endif
extern uint32_t __sub_reverse(uint32_t, uint32_t);
/* uint32_t __sub_reverse(uint32_t, uint32_t(k)); */
extern uint2 __sub_reverse(uint2, uint2);
/* uint2 __sub_reverse(uint2, uint2(k)); */
extern uint3 __sub_reverse(uint3, uint3);
/* uint3 __sub_reverse(uint3, uint3(k)); */
extern uint4 __sub_reverse(uint4, uint4);
/* uint4 __sub_reverse(uint4, uint4(k)); */
extern uint8 __sub_reverse(uint8, uint8);
/* uint8 __sub_reverse(uint8, uint8(k)); */
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __sub_reverse(uint16, uint16);
/* uint16 __sub_reverse(uint16, uint16(k)); */
#endif

/* VSUBRW */
extern cint __sub_reverse(cint, cint);
extern cint2 __sub_reverse(cint2, cint2);
extern cint4 __sub_reverse(cint4, cint4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern cint8 __sub_reverse(cint8, cint8);
#endif

/* SUBRD, VSUBRD */
extern int64_t __sub_reverse(int64_t, int64_t);
/* int64_t __sub_reverse(int64_t, int64_t(k)); */
extern long2 __sub_reverse(long2, long2);
/* long2 __sub_reverse(long2, long2(k)); */
extern long3 __sub_reverse(long3, long3);
/* long3 __sub_reverse(long3, long3(k)); */
extern long4 __sub_reverse(long4, long4);
/* long4 __sub_reverse(long4, long4(k)); */
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __sub_reverse(long8, long8);
/* long8 __sub_reverse(long8, long8(k)); */
#endif
extern uint64_t __sub_reverse(uint64_t, uint64_t);
/* uint64_t __sub_reverse(uint64_t, uint64_t(k)); */
extern ulong2 __sub_reverse(ulong2, ulong2);
/* ulong2 __sub_reverse(ulong2, ulong2(k)); */
extern ulong3 __sub_reverse(ulong3, ulong3);
/* ulong3 __sub_reverse(ulong3, ulong3(k)); */
extern ulong4 __sub_reverse(ulong4, ulong4);
/* ulong4 __sub_reverse(ulong4, ulong4(k)); */
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __sub_reverse(ulong8, ulong8);
/* ulong8 __sub_reverse(ulong8, ulong8(k)); */
#endif

/* VSUBRD */
extern clong __sub_reverse(clong, clong);
extern clong2 __sub_reverse(clong2, clong2);
#if __C7X_VEC_SIZE_BITS__ == 512
extern clong4 __sub_reverse(clong4, clong4);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __sub_sat                                                              */
/*----------------------------------------------------------------------------*/

/* VSSUBB */
extern int8_t __sub_sat(int8_t, int8_t);
/* int8_t __sub_sat(int8_t, int8_t(k)); */
extern char2 __sub_sat(char2, char2);
/* char2 __sub_sat(char2, char2(k)); */
extern char3 __sub_sat(char3, char3);
/* char3 __sub_sat(char3, char3(k)); */
extern char4 __sub_sat(char4, char4);
/* char4 __sub_sat(char4, char4(k)); */
extern char8 __sub_sat(char8, char8);
/* char8 __sub_sat(char8, char8(k)); */
extern char16 __sub_sat(char16, char16);
/* char16 __sub_sat(char16, char16(k)); */
extern char32 __sub_sat(char32, char32);
/* char32 __sub_sat(char32, char32(k)); */
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __sub_sat(char64, char64);
/* char64 __sub_sat(char64, char64(k)); */
#endif
extern cchar __sub_sat(cchar, cchar);
extern cchar2 __sub_sat(cchar2, cchar2);
extern cchar4 __sub_sat(cchar4, cchar4);
extern cchar8 __sub_sat(cchar8, cchar8);
extern cchar16 __sub_sat(cchar16, cchar16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern cchar32 __sub_sat(cchar32, cchar32);
#endif

/* VSSUBH */
extern int16_t __sub_sat(int16_t, int16_t);
/* int16_t __sub_sat(int16_t, int16_t(k)); */
extern short2 __sub_sat(short2, short2);
/* short2 __sub_sat(short2, short2(k)); */
extern short3 __sub_sat(short3, short3);
/* short3 __sub_sat(short3, short3(k)); */
extern short4 __sub_sat(short4, short4);
/* short4 __sub_sat(short4, short4(k)); */
extern short8 __sub_sat(short8, short8);
/* short8 __sub_sat(short8, short8(k)); */
extern short16 __sub_sat(short16, short16);
/* short16 __sub_sat(short16, short16(k)); */
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __sub_sat(short32, short32);
/* short32 __sub_sat(short32, short32(k)); */
#endif
extern cshort __sub_sat(cshort, cshort);
extern cshort2 __sub_sat(cshort2, cshort2);
extern cshort4 __sub_sat(cshort4, cshort4);
extern cshort8 __sub_sat(cshort8, cshort8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern cshort16 __sub_sat(cshort16, cshort16);
#endif

/* VSSUBW */
extern int32_t __sub_sat(int32_t, int32_t);
/* int32_t __sub_sat(int32_t, int32_t(k)); */
extern int2 __sub_sat(int2, int2);
/* int2 __sub_sat(int2, int2(k)); */
extern int3 __sub_sat(int3, int3);
/* int3 __sub_sat(int3, int3(k)); */
extern int4 __sub_sat(int4, int4);
/* int4 __sub_sat(int4, int4(k)); */
extern int8 __sub_sat(int8, int8);
/* int8 __sub_sat(int8, int8(k)); */
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __sub_sat(int16, int16);
/* int16 __sub_sat(int16, int16(k)); */
#endif
extern cint __sub_sat(cint, cint);
extern cint2 __sub_sat(cint2, cint2);
extern cint4 __sub_sat(cint4, cint4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern cint8 __sub_sat(cint8, cint8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __swap                                                                 */
/*----------------------------------------------------------------------------*/

/* VSWAPB */
extern char2 __swap(char2);
extern char4 __swap(char4);
extern char8 __swap(char8);
extern char16 __swap(char16);
extern char32 __swap(char32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __swap(char64);
#endif
extern uchar2 __swap(uchar2);
extern uchar4 __swap(uchar4);
extern uchar8 __swap(uchar8);
extern uchar16 __swap(uchar16);
extern uchar32 __swap(uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __swap(uchar64);
#endif

/* VSWAPH */
extern cchar2 __swap(cchar2);
extern cchar4 __swap(cchar4);
extern cchar8 __swap(cchar8);
extern cchar16 __swap(cchar16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern cchar32 __swap(cchar32);
#endif
extern short2 __swap(short2);
extern short4 __swap(short4);
extern short8 __swap(short8);
extern short16 __swap(short16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __swap(short32);
#endif
extern ushort2 __swap(ushort2);
extern ushort4 __swap(ushort4);
extern ushort8 __swap(ushort8);
extern ushort16 __swap(ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __swap(ushort32);
#endif

/* VSWAPW */
extern cshort2 __swap(cshort2);
extern cshort4 __swap(cshort4);
extern cshort8 __swap(cshort8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern cshort16 __swap(cshort16);
#endif
extern int2 __swap(int2);
extern int4 __swap(int4);
extern int8 __swap(int8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __swap(int16);
#endif
extern uint2 __swap(uint2);
extern uint4 __swap(uint4);
extern uint8 __swap(uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __swap(uint16);
#endif
extern float2 __swap(float2);
extern float4 __swap(float4);
extern float8 __swap(float8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern float16 __swap(float16);
#endif

/* VSWAPD */
extern cint2 __swap(cint2);
extern cint4 __swap(cint4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern cint8 __swap(cint8);
#endif
extern cfloat2 __swap(cfloat2);
extern cfloat4 __swap(cfloat4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern cfloat8 __swap(cfloat8);
#endif
extern long2 __swap(long2);
extern long4 __swap(long4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __swap(long8);
#endif
extern ulong2 __swap(ulong2);
extern ulong4 __swap(ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __swap(ulong8);
#endif
extern double2 __swap(double2);
extern double4 __swap(double4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern double8 __swap(double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __unpack_high                                                          */
/*----------------------------------------------------------------------------*/

/* VUNPKHB */
extern short2 __unpack_high(char4);
extern short4 __unpack_high(char8);
extern short8 __unpack_high(char16);
extern short16 __unpack_high(char32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __unpack_high(char64);
#endif

/* VUNPKHUB */
extern ushort2 __unpack_high(uchar4);
extern ushort4 __unpack_high(uchar8);
extern ushort8 __unpack_high(uchar16);
extern ushort16 __unpack_high(uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __unpack_high(uchar64);
#endif

/* VUNPKHH */
extern int2 __unpack_high(short4);
extern int4 __unpack_high(short8);
extern int8 __unpack_high(short16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __unpack_high(short32);
#endif

/* VUNPKHUH */
extern uint2 __unpack_high(ushort4);
extern uint4 __unpack_high(ushort8);
extern uint8 __unpack_high(ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __unpack_high(ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __unpack_low                                                           */
/*----------------------------------------------------------------------------*/

/* VUNPKLB */
extern short2 __unpack_low(char4);
extern short4 __unpack_low(char8);
extern short8 __unpack_low(char16);
extern short16 __unpack_low(char32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __unpack_low(char64);
#endif

/* VUNPKLUB */
extern ushort2 __unpack_low(uchar4);
extern ushort4 __unpack_low(uchar8);
extern ushort8 __unpack_low(uchar16);
extern ushort16 __unpack_low(uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __unpack_low(uchar64);
#endif

/* VUNPKLH */
extern int2 __unpack_low(short4);
extern int4 __unpack_low(short8);
extern int8 __unpack_low(short16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __unpack_low(short32);
#endif

/* VUNPKLUH */
extern uint2 __unpack_low(ushort4);
extern uint4 __unpack_low(ushort8);
extern uint8 __unpack_low(ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __unpack_low(ushort32);
#endif

/* VUNPKLW */
extern int64_t __unpack_low(int2);
extern long2 __unpack_low(int4);
extern long4 __unpack_low(int8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __unpack_low(int16);
#endif

/* VUNPKLUW */
extern uint64_t __unpack_low(uint2);
extern ulong2 __unpack_low(uint4);
extern ulong4 __unpack_low(uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __unpack_low(uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __xnor                                                                 */
/*----------------------------------------------------------------------------*/

/* VXNORW, XNORD, XNORW */
extern int8_t __xnor(int8_t, int8_t);
extern char2 __xnor(char2, char2);
extern char3 __xnor(char3, char3);
extern char4 __xnor(char4, char4);
extern char8 __xnor(char8, char8);
extern char16 __xnor(char16, char16);
extern char32 __xnor(char32, char32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __xnor(char64, char64);
#endif
extern uint8_t __xnor(uint8_t, uint8_t);
extern uchar2 __xnor(uchar2, uchar2);
extern uchar3 __xnor(uchar3, uchar3);
extern uchar4 __xnor(uchar4, uchar4);
extern uchar8 __xnor(uchar8, uchar8);
extern uchar16 __xnor(uchar16, uchar16);
extern uchar32 __xnor(uchar32, uchar32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __xnor(uchar64, uchar64);
#endif
extern int16_t __xnor(int16_t, int16_t);
extern short2 __xnor(short2, short2);
extern short3 __xnor(short3, short3);
extern short4 __xnor(short4, short4);
extern short8 __xnor(short8, short8);
extern short16 __xnor(short16, short16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __xnor(short32, short32);
#endif
extern uint16_t __xnor(uint16_t, uint16_t);
extern ushort2 __xnor(ushort2, ushort2);
extern ushort3 __xnor(ushort3, ushort3);
extern ushort4 __xnor(ushort4, ushort4);
extern ushort8 __xnor(ushort8, ushort8);
extern ushort16 __xnor(ushort16, ushort16);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __xnor(ushort32, ushort32);
#endif
extern int32_t __xnor(int32_t, int32_t);
extern int2 __xnor(int2, int2);
extern int3 __xnor(int3, int3);
extern int4 __xnor(int4, int4);
extern int8 __xnor(int8, int8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __xnor(int16, int16);
#endif
extern uint32_t __xnor(uint32_t, uint32_t);
extern uint2 __xnor(uint2, uint2);
extern uint3 __xnor(uint3, uint3);
extern uint4 __xnor(uint4, uint4);
extern uint8 __xnor(uint8, uint8);
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __xnor(uint16, uint16);
#endif

/* VXNORW, XNORD */
extern int64_t __xnor(int64_t, int64_t);
/* int64_t __xnor(int64_t, int64_t(k)); */
extern long2 __xnor(long2, long2);
extern long3 __xnor(long3, long3);
extern long4 __xnor(long4, long4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __xnor(long8, long8);
#endif
extern uint64_t __xnor(uint64_t, uint64_t);
/* uint64_t __xnor(uint64_t, uint64_t(k)); */
extern ulong2 __xnor(ulong2, ulong2);
extern ulong3 __xnor(ulong3, ulong3);
extern ulong4 __xnor(ulong4, ulong4);
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __xnor(ulong8, ulong8);
#endif

/* XNOR */
extern bool2 __xnor(bool2, bool2);
extern bool3 __xnor(bool3, bool3);
extern bool4 __xnor(bool4, bool4);
extern bool8 __xnor(bool8, bool8);
extern bool16 __xnor(bool16, bool16);
extern bool32 __xnor(bool32, bool32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern bool64 __xnor(bool64, bool64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __xor                                                                  */
/*----------------------------------------------------------------------------*/

/* XOR */
extern bool2 __xor(bool2, bool2);
extern bool3 __xor(bool3, bool3);
extern bool4 __xor(bool4, bool4);
extern bool8 __xor(bool8, bool8);
extern bool16 __xor(bool16, bool16);
extern bool32 __xor(bool32, bool32);
#if __C7X_VEC_SIZE_BITS__ == 512
extern bool64 __xor(bool64, bool64);
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


#undef C7X_H_INCLUDE
#endif /* C7X_H */
