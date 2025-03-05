/*****************************************************************************/
/*  C6X_MIGRATION.H                                                          */
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
#ifndef C6X_MIGRATION_H
#define C6X_MIGRATION_H

#include <stdint.h>
#include <c7x.h>

#include <ti_he_impl/vector.h>
#include <ti_he_impl/vector_funcs.h>


/*****************************************************************************/
/* How to use this file                                                      */
/*****************************************************************************/
/*---------------------------------------------------------------------------*/
/* This header file provides definitions for C6000 specific macros and       */
/* intrinsics.  The implementations of these intrinsics may be as routines   */
/* that will be inlined.                                                     */
/*                                                                           */
/* It is meant as a reference that can be modified and included in           */
/* projects in place of the c6x.h header file provided with the Texas        */
/* Instruments C6000 C/C++ Compiler installation package.                    */
/*                                                                           */
/* The three sections of this file are as follows:                           */
/*   1. Predefined macros                                                    */
/*     Macros and keywords that would have been defined internally by the    */
/*     C6000 compiler, but do not exist within the C7000 compiler.           */
/*   2. Legacy types                                                         */
/*     Definitions and explanations of types that exist in the C6000         */
/*     programming model, but not in the C7000 programming model. Also       */
/*     contains examples of how to migrate current projects to use the C7000 */
/*     vector programming model.                                             */
/*   3. Legacy intrinsics                                                    */
/*     Declarations of builtin functions defined for the C6000 programming   */
/*     model that are no longer supported for C7000.                         */
/*                                                                           */
/*     Some of the builtin functions have a C7000 instruction that provides  */
/*     identical functionality. These functions are marked with a comment    */
/*     that contains the equivalent C7000 mnemonic to use. This mnemonic is  */
/*     a key that can be used to search through the c7x.h header file to     */
/*     find an equivalent C/C++ idiom using the C7000 programming model.     */
/*                                                                           */
/*     Instructions which do not contain a mapping to a C7000 mnemonic must  */
/*     be emulated by a different instruction or instructions.               */
/*---------------------------------------------------------------------------*/

/*****************************************************************************/
/* Predefined Macros for Legacy Types                                        */
/*****************************************************************************/
/*---------------------------------------------------------------------------*/
/* Target and subtarget macros                                               */
/* These macros allow for the compilation of code that has been specialized  */
/* for C6000, but is being compiled as-is for C7000. The specific subtarget  */
/* being emulated by this list of macros is C6600.                           */
/*                                                                           */
/* For C7000-specialized code, use the C7000-specific target macros          */
/* __C7000__ or __C7100__.                                                   */
/*---------------------------------------------------------------------------*/
#define _TMS320C6X        1
#define __TMS320C6X__     1
#define _TMS320C6600      1
#define _TMS320C6740      1
#define _TMS320C6700_PLUS 1
#define _TMS320C67_PLUS   1
#define _TMS320C6700      1
#define _TMS320C64_PLUS   1
#define _TMS320C6400_PLUS 1
#define _TMS320C6400      1
#define __C6X_MIGRATION__ 1

/*---------------------------------------------------------------------------*/
/* __TI_ELFABI__                                                             */
/* This macro is deprecated. Use __TI_EABI__ in its place                    */
/*---------------------------------------------------------------------------*/
#define __TI_ELFABI__ __TI_EABI__

/*---------------------------------------------------------------------------*/
/* _LITTLE_ENDIAN and _BIG_ENDIAN                                            */
/* These macros are deprecated. Use __little_endian__ and __big_endian__.    */
/*---------------------------------------------------------------------------*/
#if __little_endian__
    #define _LITTLE_ENDIAN 1
#elif __big_endian__
    #define _BIG_ENDIAN    1
#endif

/*---------------------------------------------------------------------------*/
/* The near and far keywords are not supported on C7000, but are defined     */
/* as empty macros for legacy code support.                                  */
/*---------------------------------------------------------------------------*/
#define near
#define _near
#define __near
#define far
#define _far
#define __far

/*---------------------------------------------------------------------------*/
/* C6000's delayed move is not supported on C7000 as a delayed move.         */
/*---------------------------------------------------------------------------*/
static inline int32_t _mvd(int32_t s1)
{
    return s1;
}

/*****************************************************************************/
/* __x128_t                                                                  */
/*****************************************************************************/
/*---------------------------------------------------------------------------*/
/* The __x128_t type is a legacy type used for representing vectors.         */
/*                                                                           */
/* It is defined as an opaque container, meaning that only intrinsics may    */
/* use or modify its contents. Therefore, direct accesses to its contents    */
/* through C are undefined behavior.                                         */
/*                                                                           */
/* When migrating code from C6000 to C7000, replace uses of __x128_t with    */
/* vector types.                                                             */
/*---------------------------------------------------------------------------*/
/* The definition of __x128_t is found in ti_he_impl/c7x_c_funcs.h.          */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* __x128_t Generators                                                       */
/*                                                                           */
/* Replace with vector initializations, e.g.:                                */
/* double2 = double2(1.0, 2.0);   // Instead of _dto128(1.0, 2.0);           */
/* int4 = int4(x, y, z, h);       // Instead of _llto128(itoll(h, z),        */
/*                                //                     itoll(y, x));       */
/*---------------------------------------------------------------------------*/
__x128_t _dup32_128(uint32_t src);
__x128_t _fto128(float src1, float src2, float src3 , float src4);
__x128_t _ito128(uint32_t src1, uint32_t src2, uint32_t src3, uint32_t src4);
__x128_t _dto128(double src1, double src2);
__x128_t _llto128(int64_t src1, int64_t src2);

/*---------------------------------------------------------------------------*/
/* __x128_t Accessors                                                        */
/*                                                                           */
/* Replace with vector accessors, e.g.:                                      */
/* int4 a = int4(1, 2, 3, 4);                                                */
/* a.s[3]   // Instead of _get32_128(a, 3);                                  */
/* a.even() // Instead of _itoll(_get32_128(a, 0), _get32_128(a, 2));        */
/* a.hi()   // Instead of _hi128(a);                                         */
/* a.lo()   // Instead of _lo128(a);                                         */
/*---------------------------------------------------------------------------*/
int64_t _hi128(__x128_t src);
int64_t _lo128(__x128_t src);
double _hid128(__x128_t src);
double _lod128(__x128_t src);

uint32_t _get32_128(__x128_t src, uint32_t index);
float _get32f_128(__x128_t src, uint32_t index);

/*****************************************************************************/
/* __float2_t                                                                */
/*****************************************************************************/
/*---------------------------------------------------------------------------*/
/* __float2_t is a legacy type that replaced the use of 'double' for packed  */
/* 32-bit float data.                                                        */
/*                                                                           */
/* Replace uses of this type with the vector type 'float2'.                  */
/*---------------------------------------------------------------------------*/
/* For host emulation, there must be a distinction between a double type and */
/* a __float2_t type. This is because the size of a double cannot be         */
/* guaranteed to be 64 bits on every host system, which is a problem if the  */
/* double is meant to represent 2 floating point types in a SIMD operation.  */
/* As a result, in host emulation, __float2_t exists as a separate class type*/
/* and is not simply typedef'ed as a double. The __float2_t type should be   */
/* treated as an opaque container type, meaning that all accesses and        */
/* initializations should be done via intrinsics. The __float2_t type        */
/* constructors and its methods should not be used and are not supported in  */
/* the C7000 programming model. This limitation is described in more detail  */
/* in the C7000 host emulation user's guide.                                 */
/*---------------------------------------------------------------------------*/
struct __float2_t
{
    uint64_t data;
};

/*---------------------------------------------------------------------------*/
/* Vector style conversions to help mimic the typedef of double to __float2_t*/
/*---------------------------------------------------------------------------*/
#define _AS_CONV_F2T(name, type) \
static inline type __as_ ## name(const __float2_t &src) \
{ return __as_ ## name(src.data); }

_AS_CONV_F2T(long, int64_t)
_AS_CONV_F2T(ulong, uint64_t)
_AS_CONV_F2T(double, double)
_AS_CONV_F2T(int2, int2)
_AS_CONV_F2T(uint2, uint2)
_AS_CONV_F2T(cint, cint)
_AS_CONV_F2T(float2, float2)
_AS_CONV_F2T(cfloat, cfloat)
_AS_CONV_F2T(short4, short4)
_AS_CONV_F2T(ushort4, ushort4)
_AS_CONV_F2T(cshort2, cshort2)
_AS_CONV_F2T(char8, char8)
_AS_CONV_F2T(uchar8, uchar8)
_AS_CONV_F2T(cchar4, cchar4)

/*---------------------------------------------------------------------------*/
/* __as_float2_t provided for compatibility between host emulation and cl7x  */
/* where the type of __float2_t differs. For cl7x, this is __as_double(),    */
/* for host emulation, this is an initialization of the struct.              */
/*---------------------------------------------------------------------------*/
#define __as_float2_t(x) (__float2_t{__as_ulong(x)})

/*---------------------------------------------------------------------------*/
/* Conversions from 16-bit precision ints to __float2_t                      */
/*                                                                           */
/* C7000 ISA:                                                                */
/*   VINTHSPL                                                                */
/*   VINTHSPUL                                                               */
/*   VINTHSPH                                                                */
/*   VINTHSPUH                                                               */
/*                                                                           */
/* However, in some situations, converting 16-bit integers to 32-bit         */
/* integers first may yield superior performance.  For example, VUNPKW       */
/* followed by VINTSP or VINTSPU.                                            */
/*---------------------------------------------------------------------------*/
static inline __float2_t _dinthsp(uint32_t s1)
{
    return __as_float2_t(__convert_float2(__as_short2(s1)));
}

static inline __float2_t _dinthspu(uint32_t s1)
{
    return __as_float2_t(__convert_float2(__as_ushort2(s1)));
}

/*---------------------------------------------------------------------------*/
/* Conversion from 32-bit precision ints to __float2_t                       */
/*                                                                           */
/* C7000 ISA:                                                                */
/*   VINTSP                                                                  */
/*   VINTSPU                                                                 */
/*---------------------------------------------------------------------------*/
static inline __float2_t _dintsp(int64_t s1)
{
    return __as_float2_t(__int_to_float(__as_int2(s1)));
}

static inline __float2_t _dintspu(int64_t s1)
{
    return __as_float2_t(__int_to_float(__as_uint2(s1)));
}

/*---------------------------------------------------------------------------*/
/* Conversion from __float2_t to 16-bit precision ints                       */
/*                                                                           */
/* C7000 ISA:                                                                */
/*   VSPINTHPK                                                               */
/*                                                                           */
/* See Also:                                                                 */
/*   VSPINTH                                                                 */
/*                                                                           */
/* However, in some situations, converting to 32-bit integers first may      */
/* yield superior performance due to data layout.  For example, VSPINT       */
/* followed by VHPACKL.                                                      */
/*---------------------------------------------------------------------------*/
static inline uint32_t _dspinth(__float2_t s1)
{
    return __as_uint(__convert_short2(__float_to_int(__as_float2(s1))));
}

/*---------------------------------------------------------------------------*/
/* Conversion from __float2_t to 2 32-bit precision ints                     */
/*                                                                           */
/* C7000 ISA:                                                                */
/*   VSPINT                                                                  */
/*---------------------------------------------------------------------------*/
static inline int64_t _dspint(__float2_t s1)
{
    return __as_long(__float_to_int(__as_float2(s1)));
}

/*---------------------------------------------------------------------------*/
/* Reinterpretation between 64-bit integers and __float2_t                   */
/*                                                                           */
/* Replace the __float2_t type with the float2 vector type, then use vector  */
/* reinterpret casts (as_double, as_float2)                                  */
/*---------------------------------------------------------------------------*/
#define _lltof2  __as_float2_t
#define _f2toll(x)  ((int64_t)__as_long(x))

/*---------------------------------------------------------------------------*/
/* Replace __float2_t with the float2 vector type, and use vector            */
/* initialization, e.g.: float2(float, float)                                */
/*---------------------------------------------------------------------------*/
static inline __float2_t _ftof2(float s1, float s2)
{
    return __as_float2_t(__float2(s2, s1));
}

/*---------------------------------------------------------------------------*/
/* Replace __float2_t with the float2 vector type, then use vector accessors */
/* e.g.: float2.hi(), float2.lo()                                            */
/*---------------------------------------------------------------------------*/
static inline float _hif2(__float2_t s1)
{
    return __as_float2(s1).s[1];
}
static inline float _lof2(__float2_t s1)
{
    return __as_float2(s1).s[0];
}

/*---------------------------------------------------------------------------*/
/* There is no difference between _amem and _mem for C7000, as all loads     */
/* and stores have unaligned capability. Replace these intrinsics with basic */
/* C dereference operators on a pointer to a vector.                         */
/*---------------------------------------------------------------------------*/
#define _amem8_f2(p)       (*(__float2_t*)(char*)(p))
#define _amem8_f2_const(p) (*(__float2_t*)(char*)(p))
#define _mem8_f2(p)        (*(__float2_t*)(char*)(p))
#define _mem8_f2_const(p)  (*(__float2_t*)(char*)(p))

/*---------------------------------------------------------------------------*/
/* Use the PACKW or PACKWDLY4 instruction, reinterpret casting each source   */
/* to int if needed, and then casting the result to a float2.                */
/*---------------------------------------------------------------------------*/
/* No delay for instructions with just a pack (same for _dmvd) */
#define _fdmv_f2   _ftof2
#define _fdmvd_f2  _ftof2

/*---------------------------------------------------------------------------*/
/* After changing references to __x128_t to use vectors, replace these two   */
/* operations with vector accessors.                                         */
/*                                                                           */
/* e.g.:                                                                     */
/* float2 _hif2_128(float4 src) { return src.hi(); }                         */
/*---------------------------------------------------------------------------*/
#define _hif2_128(x)  (__as_float2_t(_hi128(x)))
#define _lof2_128(x)  (__as_float2_t(_lo128(x)))

/*---------------------------------------------------------------------------*/
/* After changing references to __x128_t to use vectors, replace this        */
/* intrinsic with an vector initialization.                                  */
/*---------------------------------------------------------------------------*/
#define _f2to128(x,y) (_llto128(__as_long(x),__as_long(y)))

/*---------------------------------------------------------------------------*/
/* Accessing the SAT bit or Floating Point status bits                       */
/*                                                                           */
/* These bits are set in the C7x FSR control register.  Access to the FSR is */
/* provided by the following API that can be used in legacy C6x source code. */
/* An 8bit value is returned containing the following fields:                */
/*                                                                           */
/* Bit 7: SAT   - Result is saturated Fixed Point Flag (C6X OPERATIONS ONLY) */
/* Bit 6: UNORD - Compare result is unordered Floating Point Flag            */
/* Bit 5: DEN   - Source is a Denorm Floating Point Flag                     */
/* Bit 4: INEX  - Result is inexact Floating Point Flag                      */
/* Bit 3: UNDER - Result is underflow Floating Point Flag                    */
/* Bit 2: OVER  - Result is overflow Floating Point Flag                     */
/* Bit 1: DIV0  - Divide by zero Floating Point Flag                         */
/* Bit 0: INVAL - Invalid Operations Floating Point Flag                     */
/*                                                                           */
/*    e.g.: uint8_t fsr_val = __get_C7X_FSR();                               */
/*                                                                           */
/* Please refer to the CPU micro architecture guide for more information on  */
/* how to interpret the FSR bits layout.                                     */
/*                                                                           */
/* NOTE: Accessing the SAT bit of the FSR is applicable only when migrating  */
/* C6000 supported operations using the legacy C6000 intrinsics defined in   */
/* this file. Accessing the SAT bit is NOT SUPPORTED for C7000 operations.   */
/*---------------------------------------------------------------------------*/
/* __get_C7x_FSR() not provided due to not being able to handle x86 FP       */
/* operations. CODEGEN-4223.                                                 */
/* #define __get_C7X_FSR() __get_fsr_double(sizeof(double)) */

/*****************************************************************************/
/* __int40_t                                                                 */
/*****************************************************************************/
/*---------------------------------------------------------------------------*/
/* __int40_t is a legacy type that provided extended precision integer       */
/* arithmetic that was natively supported by C6000 subtargets. The 40-bit    */
/* type is not supported on C7000, and the following intrinsics must be      */
/* migrated manually to 64-bit arithmetic.                                   */
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/* Conversions between double-precision floating point and __int40_t         */
/*---------------------------------------------------------------------------*/
/* __int40_t _dtol(double);                   */
/* double _ltod(__int40_t);                   */

/*---------------------------------------------------------------------------*/
/* 40-bit intrinsics                                                         */
/*---------------------------------------------------------------------------*/
/* __int40_t _labs(__int40_t);           VABSD    */
/* __int40_t _ldotp2(int32_t, int32_t);  VDOTP2HD */
/* uint32_t _lnorm(__int40_t);           VNORMD   */
/* __int40_t _lsadd(int32_t, __int40_t); ADDD     */
/* __int40_t _lssub(int32_t, __int40_t); SUBD     */
/* int32_t _sat(__int40_t);              VSATLW   */

/*---------------------------------------------------------------------------*/
/* C7x int40 saturating conversions                                          */
/*---------------------------------------------------------------------------*/
/* int64_t = __long_to_int40_sat(int64_t);        VSATDL   */
/* int2 = __int40_to_int_sat(int64_t);            VSATLW   */

/*****************************************************************************/
/* Legacy vector types                                                       */
/*****************************************************************************/
/*---------------------------------------------------------------------------*/
/* C6000 defined long as either 32 or 40 bits, depending on certain          */
/* configurations. For 64-bit vectors, C6000 defined longlong vectors.       */
/*                                                                           */
/* C7000 defines long as 64 bits and uses long vectors. longlong vector      */
/* types are defined here for migration, but code leveraging the longlong    */
/* vector types should be migrated to use long vectors.                      */
/*---------------------------------------------------------------------------*/
#if !__TI_STRICT_ANSI_MODE__
typedef int64_t  longlong;
typedef __long2  longlong2;
//typedef __long3  longlong3;
typedef __long4  longlong4;
typedef __long8  longlong8;
typedef __long16 longlong16;

typedef __ulong   ulonglong;
typedef __ulong2  ulonglong2;
//typedef __ulong3  ulonglong3;
typedef __ulong4  ulonglong4;
typedef __ulong8  ulonglong8;
typedef __ulong16 ulonglong16;
#endif
typedef int64_t  __longlong;
typedef __long2  __longlong2;
//typedef __long3  __longlong3;
typedef __long4  __longlong4;
typedef __long8  __longlong8;
typedef __long16 __longlong16;

typedef __ulong   __ulonglong;
typedef __ulong2  __ulonglong2;
//typedef __ulong3  __ulonglong3;
typedef __ulong4  __ulonglong4;
typedef __ulong8  __ulonglong8;
typedef __ulong16 __ulonglong16;

/*****************************************************************************/
/* Legacy C6X Intrinsics                                                     */
/*****************************************************************************/
/*---------------------------------------------------------------------------*/
/* The following intrinsics were defined on C6000 to separate aligned and    */
/* unaligned loads and stores of 2, 4, and 8 byte data.                      */
/*                                                                           */
/* On C7000, all loads and stores are unaligned, so the intrinsics may be    */
/* broken down into native C dereferences.                                   */
/*---------------------------------------------------------------------------*/
#define _amem2(p)         (*(uint16_t*)(char*)(p))
#define _amem2_const(p)   (*(uint16_t*)(char*)(p))
#define _amem4(p)         (*(uint32_t*)(char*)(p))
#define _amem4_const(p)   (*(uint32_t*)(char*)(p))
#define _amem8(p)         (*(uint64_t*)(char*)(p))
#define _amem8_const(p)   (*(uint64_t*)(char*)(p))
#define _amemd8(p)        (*(double*)(char*)(p))
#define _amemd8_const(p)  (*(double*)(char*)(p))
#define _mem2(p)          (*(uint16_t*)(char*)(p))
#define _mem2_const(p)    (*(uint16_t*)(char*)(p))
#define _mem4(p)          (*(uint32_t*)(char*)(p))
#define _mem4_const(p)    (*(uint32_t*)(char*)(p))
#define _mem8(p)          (*(uint64_t*)(char*)(p))
#define _mem8_const(p)    (*(uint64_t*)(char*)(p))
#define _memd8(p)         (*(double*)(char*)(p))
#define _memd8_const(p)   (*(double*)(char*)(p))

/*---------------------------------------------------------------------------*/
/* The following declarations are C6000 intrinsics which are supported       */
/* by the C7000 ISA. A C7000 instruction mnemonic preceding the declaration  */
/* denotes that there is a direct translation available for migration.       */
/*                                                                           */
/* Operand types and C idioms for the C7000 instructions are described in    */
/* c7x.h, and can be searched through using the mnemonic as a key.           */
/*---------------------------------------------------------------------------*/
/* VADDSP */
static inline __float2_t _daddsp(__float2_t s1, __float2_t s2)
{
    return __as_float2_t(__as_float2(s1) + __as_float2(s2));
}
/* VSUBSP */
static inline __float2_t _dsubsp(__float2_t s1, __float2_t s2)
{
    return __as_float2_t(__as_float2(s1) - __as_float2(s2));
}
/* VMPYSP */
static inline __float2_t _dmpysp(__float2_t s1, __float2_t s2)
{
    return __as_float2_t(__as_float2(s1) * __as_float2(s2));
}
/* VCMPYSP */
__x128_t _cmpysp(__float2_t, __float2_t);

/* VCCMATMPYHW */
__x128_t _ccmatmpy(int64_t, __x128_t);
/* VCCMATMPYR1HH */
int64_t _ccmatmpyr1(int64_t, __x128_t);
/* VCMATMPYHW */
__x128_t _cmatmpy(int64_t, __x128_t);
/* VCMATMPYR1HH */
int64_t _cmatmpyr1(int64_t, __x128_t);
/* VCMPYR1WW */
static inline int64_t _cmpy32r1(int64_t s1, int64_t s2)
{
    return __as_long(__cmpy_fx(__as_cint(s1), __as_cint(s2)));
}
/* VCMPYHW */
static inline int64_t _cmpy(uint32_t s1, uint32_t s2)
{
    return __as_long(__cmpy_ext(__as_cshort(s1), __as_cshort(s2)));
}
/* VCMPYHW */
__x128_t _dcmpy(int64_t, int64_t);
/* VCMPYRHH */
static inline uint32_t _cmpyr(uint32_t s1, uint32_t s2)
{
    return __as_uint(__cmpyr_fx(__as_cshort(s1), __as_cshort(s2)));
}
/* VCCMPYR1HH */
static inline int64_t _dccmpyr1(int64_t s1, int64_t s2)
{
    return __as_long(__cmpy_conj_fx(__as_cshort2(s1), __as_cshort2(s2)));
}
/* VCMPYR1HH */
static inline uint32_t _cmpyr1(uint32_t s1, uint32_t s2)
{
    return __as_uint(__cmpy_fx(__as_cshort(s1), __as_cshort(s2)));
}
/* VCMPYR1HH */
static inline int64_t _dcmpyr1(int64_t s1, int64_t s2)
{
    return __as_long(__cmpy_fx(__as_cshort2(s1), __as_cshort2(s2)));
}
/* VCCMPYHW */
__x128_t _dccmpy(int64_t, int64_t);
/* VCCMPYR1WW */
static inline int64_t _ccmpy32r1(int64_t s1, int64_t s2)
{
    return __as_long(__cmpy_conj_fx(__as_cint(s1), __as_cint(s2)));
}
/* VDOTP4HW */
int64_t _ddotp4h(__x128_t, __x128_t);
/* VDOTP4SUHW */
int64_t _ddotpsu4h(__x128_t, __x128_t);
/* C6DMPYHW */
__x128_t _dmpy2(int64_t, int64_t);
/* C6DMPYSUBH */
__x128_t _dmpysu4(int64_t, int64_t);
/* C6DMPYUHW */
__x128_t _dmpyu2(int64_t, int64_t);
/* C6DMPYUBH */
__x128_t _dmpyu4(int64_t, int64_t);
/* C6DSMPYHW */
__x128_t _dsmpy2(int64_t, int64_t);
/* VMPYWW */
__x128_t _qmpy32(__x128_t, __x128_t);
/* VMPYSP */
__x128_t _qmpysp(__x128_t, __x128_t);
/* VSMPYR1WW */
__x128_t _qsmpy32r1(__x128_t, __x128_t);

/* VABSW */
static inline int32_t _abs(int32_t s1)
{
    return __abs(s1);
}
/* VABSH */
static inline int32_t _abs2(int32_t s1)
{
    return __as_int(__abs(__as_short2(s1)));
}
/* VADDH */
static inline int32_t _add2(int32_t s1, int32_t s2)
{
    return __as_int(__as_short2(s1) + __as_short2(s2));
}
/* VADDB */
static inline int32_t _add4(int32_t s1, int32_t s2)
{
    return __as_int(__as_char4(s1) + __as_char4(s2));
}
/* VAVGH */
static inline int32_t _avg2(int32_t s1, int32_t s2)
{
    return __as_int(__rhadd(__as_short2(s1), __as_short2(s2)));
}
/* VAVGUB */
static inline uint32_t _avgu4(uint32_t s1, uint32_t s2)
{
    return __as_uint(__rhadd(__as_uchar4(s1), __as_uchar4(s2)));
}
/* VBITCNTB */
static inline uint32_t _bitc4(uint32_t s1)
{
    return __as_uint(__popcount(__as_char4(s1)));
}
/* VBITRW */
static inline uint32_t _bitr(uint32_t s1)
{
    return __as_uint(__bit_reverse(__as_int(s1)));
}
/* CLR */
static inline uint32_t _clr(uint32_t s1, uint32_t s2, uint32_t s3)
{
    uint64_t e_s2 = (((uint64_t) s2) << 59) >> 54;
    uint64_t e_s3 = (((uint64_t) s3) << 59) >> 59;
    uint64_t tmp  = e_s2 | e_s3;
    return __as_uint(__clear(s1, (uint32_t) tmp));
}
/* CLR */
static inline uint32_t _clrr(uint32_t s1, int32_t s2)
{
    return __as_uint(__clear(s1, __as_uint(s2)));
}
/* VCROT270H */
static inline int32_t _crot270(int32_t s1)
{
    return __as_int(__crot270(__as_cshort(s1)));
}
/* VCROT90H */
static inline int32_t _crot90(int32_t s1)
{
    return __as_int(__crot90(__as_cshort(s1)));
}
/* VADDW */
static inline int64_t _dadd(int64_t s1, int64_t s2)
{
    return __as_long(__as_int2(s1) + __as_int2(s2));
}
/* VADDH */
static inline int64_t _dadd2(int64_t s1, int64_t s2)
{
    return __as_long(__as_short4(s1) + __as_short4(s2));
}
/* VADDW */
static inline int64_t _dadd_c(int32_t s1, int64_t s2)
{
    return __as_long(__int2(s1) + __as_int2(s2));
} /* _dadd_c */
/* VAPYSH */
static inline int64_t _dapys2(int64_t s1, int64_t s2)
{
    return __as_long(__apply_sign(__as_short4(s2), __as_short4(s1)));
}
/* VAVGH */
static inline int64_t _davg2(int64_t s1, int64_t s2)
{
    return __as_long(__rhadd(__as_short4(s1), __as_short4(s2)));
}
/* VAVGNRH */
static inline int64_t _davgnr2(int64_t s1, int64_t s2)
{
    return __as_long(__hadd(__as_short4(s1), __as_short4(s2)));
}
/* VAVGNRUB */
static inline int64_t _davgnru4(int64_t s1, int64_t s2)
{
    return __as_long(__hadd(__as_uchar8(s1), __as_uchar8(s2)));
}
/* VAVGUB */
static inline int64_t _davgu4(int64_t s1, int64_t s2)
{
    return __as_long(__rhadd(__as_uchar8(s1), __as_uchar8(s2)));
}
/* C6DCMPEQH */
static inline uint32_t _dcmpeq2(int64_t s1, int64_t s2)
{
    return __as_uchar(__c6dcmpeqh_ddr(__as_short4(s1), __as_short4(s2)));
}
/* C6DCMPEQB */
static inline uint32_t _dcmpeq4(int64_t s1, int64_t s2)
{
    return __as_uchar(__c6dcmpeqb_ddr(__as_char8(s1), __as_char8(s2)));
}
/* C6DCMPGTH */
static inline uint32_t _dcmpgt2(int64_t s1, int64_t s2)
{
    return __as_uchar(__c6dcmpgth_ddr(__as_short4(s1), __as_short4(s2)));
}
/* C6DCMPGTUB */
static inline uint32_t _dcmpgtu4(int64_t s1, int64_t s2)
{
    return __c6dcmpgtub_ddr(__as_uchar8(s1), __as_uchar8(s2));
}
/* VCROT270H */
static inline int64_t _dcrot270(int64_t s1)
{
    return __as_long(__crot270(__as_cshort2(s1)));
}
/* VCROT90H */
static inline int64_t _dcrot90(int64_t s1)
{
    return __as_long(__crot90(__as_cshort2(s1)));
}
/* C6DDOTP2HHW */
static inline int64_t _ddotph2(int64_t s1, uint32_t s2)
{
    return __as_long(__c6ddotp2hhw_drd(__as_short4(s1), __as_short2(s2)));
}
/* C6DDOTP2HRHH */
static inline uint32_t _ddotph2r(int64_t s1, uint32_t s2)
{
    return __as_uint(__c6ddotp2hrhh_drr(__as_short4(s1), __as_short2(s2)));
}
/* C6DDOTP2LHW */
static inline int64_t _ddotpl2(int64_t s1, uint32_t s2)
{
    return __as_long(__c6ddotp2lhw_drd(__as_short4(s1), __as_short2(s2)));
}
/* C6DDOTP2LRHH */
static inline uint32_t _ddotpl2r(int64_t s1, uint32_t s2)
{
    return __as_uint(__c6ddotp2lrhh_drr(__as_short4(s1), __as_short2(s2)));
}
/* VBITDEALW */
static inline uint32_t _deal(uint32_t s1)
{
    return __as_uint(__deal_bit(__as_uint(s1)));
}
/* VMAXH */
static inline int64_t _dmax2(int64_t s1, int64_t s2)
{
    return __as_long(__max(__as_short4(s1), __as_short4(s2)));
}
/* VMAXUB */
static inline int64_t _dmaxu4(int64_t s1, int64_t s2)
{
    return __as_long(__max(__as_uchar8(s1), __as_uchar8(s2)));
}
/* VMINH */
static inline int64_t _dmin2(int64_t s1, int64_t s2)
{
    return __as_long(__min(__as_short4(s1), __as_short4(s2)));
}
/* VMINUB */
static inline int64_t _dminu4(int64_t s1, int64_t s2)
{
    return __as_long(__min(__as_uchar8(s1), __as_uchar8(s2)));
}
/* PACKW */
static inline int64_t _dmv(uint32_t s1, uint32_t s2)
{
    return __as_long(__uint2(s2, s1));
}
/* No delay for instructions with just a pack (same for _fdmvd) */
#define _dmvd(s1, s2) _dmv(__as_uint(s1), __as_uint(s2))
/* VDOTP2HW */
static inline int32_t _dotp2(int32_t s1, int32_t s2)
{
    return __dotp2(__as_short2(s1), __as_short2(s2));
}
/*---------------------------------------------------------------------------*/
/* Although VDOTP4HW may be used to emulate _dotp4h, it may be beneficial to */
/* instead use VDOTP4HD to avoid the need for double vector inputs.          */
/*---------------------------------------------------------------------------*/
static inline int32_t _dotp4h(int64_t s1, int64_t s2)
{
    return __saturate(__dotp4_ext(__as_short4(s1), __as_short4(s2)), (uint8_t)(32));
}
/* VDOTP4HD */
static inline int64_t _dotp4hll(int64_t s1, int64_t s2)
{
    return __dotp4_ext(__as_short4(s1), __as_short4(s2));
}
/*---------------------------------------------------------------------------*/
/* Although C6DOTPN2HW may be used to emulate _dotpn2, it may be beneficial  */
/* to instead use VDOTP2NWD to allow for vectorization.                      */
/*---------------------------------------------------------------------------*/
static inline int32_t _dotpn2(int32_t s1, int32_t s2)
{
    return __dotp2_negate(__as_short2(s1), __as_short2(s2));
}
/*---------------------------------------------------------------------------*/
/* Although C6DOTPN2RSUHH may be used to emulate _dotpnrsu2, it may be       */
/* beneficial to instead use VDOTP2NWD to allow for vectorization.           */
/*---------------------------------------------------------------------------*/
static inline int32_t _dotpnrsu2(int32_t s1, uint32_t s2)
{
    return __dotp2_negate(__as_short2(s1), __as_ushort2(s2));
}
#define _dotpnrus2(u, s) _dotpnrsu2((s), (u))
/*---------------------------------------------------------------------------*/
/* Although C6DOTP2RSUHW may be used to emulate _dotprsu2, it may be         */
/* beneficial to instead use VDOTP2SUHW to allow for vectorization.          */
/*---------------------------------------------------------------------------*/
/* C6DOTP2RSUHW */
static inline int32_t _dotprsu2(int32_t s1, uint32_t s2)
{
    return __dotp2_fx_ext(__as_short2(s1), __as_ushort2(s2));
}
/* VDOTP4SUBW */
static inline int32_t _dotpsu4(int32_t s1, uint32_t s2)
{
    return __as_int(__dotp4_ext(__as_char4(s1), __as_uchar4(s2)));
}
#define _dotpus4(u, s) _dotpsu4((s), (u))
/* VDOTP4SUHW */
static inline int32_t _dotpsu4h(int64_t s1, int64_t s2)
{
#if defined(__C7100__) || defined(__C7120__)
    __long8 v1, v2, v3, v4;
    v1.s[0] = s1;
    v3.s[0] = s2;
    return __vdotp4suhw_wwv(__as_short32(v1),  __as_short32(v2),
                            __as_ushort32(v3), __as_ushort32(v4)).s[0];
#else
    /* CODEGEN-8870: Deinterleave slows; but direct intrinsic not available. */
    /* CODEGEN-9069: Direct intrinsics for scaling operations not available. */
    return __dotp4(__as_short4(s1), __as_ushort4(s2));
#endif
}
/* VDOTP4SUHD */
static inline int64_t _dotpsu4hll(int64_t s1, int64_t s2)
{
    return __dotp4_ext(__as_short4(s1), __as_ushort4(s2));
}
/* VDOTP4UBW */
static inline uint32_t _dotpu4(uint32_t s1, uint32_t s2)
{
    return __dotp4_ext(__as_uchar4(s1), __as_uchar4(s2));
}
/* VPACKP2 */
static inline int64_t _dpack2(uint32_t s1, uint32_t s2)
{
    __char8 tmp1 = __as_char8((uint64_t) s1);
    __char8 tmp2 = __as_char8((uint64_t) s2);
    return __as_long(__pack_even(__as_short4(tmp1), __as_short4(tmp2)));
}
/* VPACKH2 */
static inline int64_t _dpackh2(int64_t s1, int64_t s2)
{
    return __as_long(__pack_high(__as_short4(s1), __as_short4(s2)));
}
/* VPACKH4 */
static inline int64_t _dpackh4(int64_t s1, int64_t s2)
{
    return __as_long(__pack_high(__as_char8(s1), __as_char8(s2)));
}
/* VPACKHL2 */
static inline int64_t _dpackhl2(int64_t s1, int64_t s2)
{
    return __as_long(__pack_high_low(__as_short4(s1), __as_short4(s2)));
}
/* VPACKL2 */
static inline int64_t _dpackl2(int64_t s1, int64_t s2)
{
    return __as_long(__pack_low(__as_short4(s1), __as_short4(s2)));
}
/* VPACKL4 */
static inline int64_t _dpackl4(int64_t s1, int64_t s2)
{
    return __as_long(__pack_low(__as_char8(s1), __as_char8(s2)));
}
/* VPACKLH2 */
static inline int64_t _dpacklh2(int64_t s1, int64_t s2)
{
    return __as_long(__pack_low_high(__as_short4(s1), __as_short4(s2)));
}
/* VPACKLH4 */
static inline int64_t _dpacklh4(uint32_t s1, uint32_t s2)
{
    __short4 tmp1 = __as_short4((uint64_t) s1);
    __short4 tmp2 = __as_short4((uint64_t) s2);
    return __as_long(__pack_low_high(__as_char8(tmp1), __as_char8(tmp2)));
}
/* PACKX2 */
static inline int64_t _dpackx2(uint32_t s1, uint32_t s2)
{
    return __as_long(__pack_even_cross(__as_short2(s1), __as_short2(s2)));
}
/* VDPINT */
static inline int32_t _dpint(double s1)
{
    return __double_to_int(s1).s[0];
}
/* VSADDW */
static inline int64_t _dsadd(int64_t s1, int64_t s2)
{
    return __as_long(__add_sat(__as_int2(s1), __as_int2(s2)));
}
/* VSADDH */
static inline int64_t _dsadd2(int64_t s1, int64_t s2)
{
    return __as_long(__add_sat(__as_short4(s1), __as_short4(s2)));
}
/* VSHLW */
static inline int64_t _dshl(int64_t s1, uint32_t s2)
{
    return __as_long(__as_int2(s1) << __int2(s2));
}
/* VSHLH */
static inline int64_t _dshl2(int64_t s1, uint32_t s2)
{
    return __as_long(__shift_left(__as_short4(s1), __int2(s2)));
}
/* VSHRW */
static inline int64_t _dshr(int64_t s1, uint32_t s2)
{
    return __as_long(__as_int2(s1) >> __int2(s2));
}
/* VSHRH */
static inline int64_t _dshr2(int64_t s1, uint32_t s2)
{
    return __as_long(__shift_right(__as_short4(s1), __int2(s2)));
}
/* VSHRUW */
static inline int64_t _dshru(int64_t s1, uint32_t s2)
{
    return __as_long(__as_uint2(s1) >> __uint2(s2));
}
/* VSHRUH */
static inline int64_t _dshru2(int64_t s1, uint32_t s2)
{
    return __as_long(__shift_right(__as_ushort4(s1), __uint2(s2)));
}
/* C6DSPACKU4 */
static inline int64_t _dspacku4(int64_t s1, int64_t s2)
{
    return __as_long(__c6dspacku4_ddd(__as_short4(s1), __as_short4(s2)));
}
/* VSSUBW */
static inline int64_t _dssub(int64_t s1, int64_t s2)
{
    return __as_long(__sub_sat(__as_int2(s1), __as_int2(s2)));
}
/* VSSUBH */
static inline int64_t _dssub2(int64_t s1, int64_t s2)
{
    return __as_long(__sub_sat(__as_short4(s1), __as_short4(s2)));
}
/* VSUBW */
static inline int64_t _dsub(int64_t s1, int64_t s2)
{
    return __as_long(__as_int2(s1) - __as_int2(s2));
}
/* VSUBH */
static inline int64_t _dsub2(int64_t s1, int64_t s2)
{
    return __as_long(__as_short4(s1) - __as_short4(s2));
}
/* XPND4H */
static inline int64_t _dxpnd2(uint32_t s1)
{
    return __as_long(__expand_lsb_pack_short((uint8_t) s1));
}
/* XPND8B */
static inline int64_t _dxpnd4(uint32_t s1)
{
    return __as_long(__expand_lsb_pack_char((uint8_t) s1));
}
/* EXT */
static inline int32_t _ext(int32_t s1, uint32_t s2, uint32_t s3)
{
    return (s1 << s2) >> s3;
}
/* EXTU */
static inline uint32_t _extu(uint32_t s1, uint32_t s2, uint32_t s3)
{
    return (s1 << s2) >> s3;
}
/* VABSDP */
static inline double _fabs(double s1)
{
    return __abs(s1);
}
/* VABSSP */
static inline float _fabsf(float s1)
{
    return __abs(s1);
}
/* PACKW */
static inline double _fdmv(float s1, float s2)
{
    return __as_double(__float2(s2, s1));
}
/* No delay for instructions with just a pack (same for _dmvd) */
#define _fdmvd(s1, s2) _fdmv(s1, s2)
/* VGMPYW */
static inline uint32_t _gmpy(uint32_t s1, uint32_t s2)
{
    return __gmpy(s1, s2);
}
/* VGMPYB */
static inline int32_t _gmpy4(int32_t s1, int32_t s2)
{
    return __as_int(__gmpy(__as_uchar4(s1), __as_uchar4(s2)));
}
/* VLMBDW */
static inline uint32_t _lmbd(uint32_t s1, uint32_t s2)
{
    return __leftmost_bit_detect(s2, s1);
}
/* VMAXH */
static inline int32_t _max2(int32_t s1, int32_t s2)
{
    return __as_int(__max(__as_short2(s1), __as_short2(s2)));
}
/* VMAXUB */
static inline uint32_t _maxu4(uint32_t s1, uint32_t s2)
{
    return __as_uint(__max(__as_uchar4(s1), __as_uchar4(s2)));
}
/* VMINH */
static inline int32_t _min2(int32_t s1, int32_t s2)
{
    return __as_int(__min(__as_short2(s1), __as_short2(s2)));
}
/* VMINUB */
static inline uint32_t _minu4(uint32_t s1, uint32_t s2)
{
    return __as_uint(__min(__as_uchar4(s1), __as_uchar4(s2)));
}
/*---------------------------------------------------------------------------*/
/* Although VMPYHW may be used to emulate _mpy, it may be beneficial to      */
/* instead use VMPYWW to avoid the need for double vector outputs.           */
/*---------------------------------------------------------------------------*/
static inline int32_t _mpy(int32_t s1, int32_t s2)
{
    return ((int16_t)s1)*((int16_t)s2);
}
/* C6MPY2IR */
static inline int64_t _mpy2ir(uint32_t s1, int32_t s2)
{
    return __as_long(__mpy_fx(__as_short2(s1), s2));
}
/*---------------------------------------------------------------------------*/
/* Although VMPYHW may be used to emulate _mpy2ll, it may be beneficial to   */
/* instead use VMPYWW to avoid the need for double vector outputs.           */
/*---------------------------------------------------------------------------*/
static inline int64_t _mpy2ll(int32_t s1, int32_t s2)
{
    return __as_long(__convert_int2(__as_short2(s1)) * __convert_int2(__as_short2(s2)));
}
/* VMPYWW */
static inline int32_t _mpy32(int32_t s1, int32_t s2)
{
    return s1 * s2;
}
/*---------------------------------------------------------------------------*/
/* Although VMPYWD may be used to emulate _mpy32ll it may be beneficial to   */
/* instead use VMPYDD to avoid the need for double vector outputs.           */
/*---------------------------------------------------------------------------*/
static inline int64_t _mpy32ll(int32_t s1, int32_t s2)
{
    return (int64_t)s1 * (int64_t)s2;
}
#define _mpy32l(s1, s2) _mpy32ll((s1), (s2))
/*---------------------------------------------------------------------------*/
/* Although VMPYSUWD may be used to emulate _mpy32su it may be beneficial to */
/* instead use VMPYDD to avoid the need for double vector outputs.           */
/*---------------------------------------------------------------------------*/
static inline int64_t _mpy32su(int32_t s1, uint32_t s2)
{
    return (int64_t)s1 * (int64_t)s2;
}
#define _mpy32us(u, s) _mpy32su((s), (u))
/*---------------------------------------------------------------------------*/
/* Although VMPYUWD may be used to emulate _mpy32u, it may be beneficial to  */
/* instead use VMPYDD to avoid the need for double vector outputs.           */
/*---------------------------------------------------------------------------*/
/* VMPYUWD */
static inline int64_t _mpy32u(uint32_t s1, uint32_t s2)
{
    return (int64_t)s1 * (int64_t)s2;
}
/* C6MPYHIR */
static inline int32_t _mpyhir(int32_t s1, int32_t s2)
{
    return __c6mpyhir_rrr(__as_short2(s1), s2);
}
#define _mpyihr(src1, src2) _mpyhir((src2), (src1))
/* VMPYWD */
static inline int64_t _mpyidll(int32_t s1, int32_t s2)
{
    return __mpy_ext(s1, s2);
}
/* C6MPYLIR */
static inline int32_t _mpylir(int32_t s1, int32_t s2)
{
    return __c6mpylir_rrr(__as_short2(s1), s2);
}
#define _mpyilr(src1, src2) _mpylir((src2), (src1))
/* VMPYSP2DP */
static inline double _mpysp2dp(float s1, float s2)
{
    return __mpy_ext(s1, s2);
}
/*---------------------------------------------------------------------------*/
/* Although VMPYSUHW may be used to emulate _mpysu, it may be beneficial to  */
/* instead use VMPYWW to avoid the need for double vector outputs.           */
/*---------------------------------------------------------------------------*/
static inline int32_t _mpysu(int32_t s1, uint32_t s2)
{
    return ((int32_t)__as_short2(s1).s[0]) * ((int32_t)__as_ushort2(s2).s[0]);
}
#define _mpyus(u, s) _mpysu((s), (u))
/* VMPYSUBH */
static inline int64_t _mpysu4ll(int32_t s1, uint32_t s2)
{
    return __as_long(__convert_short4(__as_char4(s1)) * __convert_short4(__as_uchar4(s2)));
}
#define _mpyus4ll(src1, src2) _mpysu4ll((src2), (src1))
/*---------------------------------------------------------------------------*/
/* Although VMPYUHW may be used to emulate _mpyu, it may be beneficial to    */
/* instead use VMPYWW to avoid the need for double vector outputs.           */
/*---------------------------------------------------------------------------*/
static inline uint32_t _mpyu(uint32_t s1, uint32_t s2)
{
    return __as_ushort2(s1).s[0] * __as_ushort2(s2).s[0];
}
/*---------------------------------------------------------------------------*/
/* Although VMPYUHW may be used to emulate _mpyu2, it may be beneficial to   */
/* instead use VMPYWW to avoid the need for double vector outputs.           */
/*---------------------------------------------------------------------------*/
/* VMPYUHW */
static inline int64_t _mpyu2(uint32_t s1, uint32_t s2)
{
    return __as_long(__convert_uint2(__as_ushort2(s1)) * __convert_uint2(__as_ushort2(s2)));
}
/* VMPYUBH */
static inline int64_t _mpyu4ll(uint32_t s1, uint32_t s2)
{
    return __as_long(__mpy_ext(__as_uchar4(s1), __as_uchar4(s2)));
}
/* VNORMW */
static inline uint32_t _norm(int32_t s1)
{
    return __norm(s1);
}
/* VPACKP2 */
static inline uint32_t _pack2(uint32_t s1, uint32_t s2)
{
    return __as_uint(__ushort2(__as_ushort2(s2).s[0], __as_ushort2(s1).s[0]));
}
/* VPACKH2 */
static inline uint32_t _packh2(uint32_t s1, uint32_t s2)
{
    return __as_uint(__pack_high(__as_short2(s1), __as_short2(s2)));
}
/* VPACKH4 */
static inline uint32_t _packh4(uint32_t s1, uint32_t s2)
{
    return __as_uint(__pack_high(__as_char4(s1), __as_char4(s2)));
}
/* VPACKHL2 */
static inline uint32_t _packhl2(uint32_t s1, uint32_t s2)
{
    return __as_uint(__pack_high_low(__as_short2(s1), __as_short2(s2)));
}
/* VPACKL4 */
static inline uint32_t _packl4(uint32_t s1, uint32_t s2)
{
    return __as_uint(__pack_low(__as_char4(s1), __as_char4(s2)));
}
/* VPACKLH2 */
static inline uint32_t _packlh2(uint32_t s1, uint32_t s2)
{
    return __as_uint(__pack_low_high(__as_short2(s1), __as_short2(s2)));
}
#define _swap2(src) _packlh2((src), (src))
/* VRCPDP */
static inline double _rcpdp(double s1)
{
    return __recip(s1);
}
/* VRCPSP */
static inline float _rcpsp(float s1)
{
    return __recip(s1);
}
/* VROTLW */
static inline uint32_t _rotl(uint32_t s1, uint32_t s2)
{
    return __as_uint(__rotate_left(__as_int(s1), s2));
}
/* VRPACKH */
static inline uint32_t _rpack2(uint32_t s1, uint32_t s2)
{
    return __as_uint(__pack_shift_sat(__as_int(s1), __as_int(s2)));
}
/* VRSQRDP */
static inline double _rsqrdp(double s1)
{
    return __recip_sqrt(s1);
}
/* VRSQRSP */
static inline float _rsqrsp(float s1)
{
    return __recip_sqrt(s1);
}
/* VSADDW */
static inline int32_t _sadd(int32_t s1, int32_t s2)
{
    return __add_sat(s1, s2);
}
/* VSADDH */
static inline int32_t _sadd2(int32_t s1, int32_t s2)
{
    return __as_int(__add_sat(__as_short2(s1), __as_short2(s2)));
}
/* VSADDUB */
static inline uint32_t _saddu4(uint32_t s1, uint32_t s2)
{
    return __as_uint(__add_sat(__as_uchar4(s1), __as_uchar4(s2)));
}
/* VSADDUSH */
static inline int32_t _saddus2(uint32_t s1, int32_t s2)
{
    return __as_int(__add_sat(__as_ushort2(s1), __as_short2(s2)));
}
#define _saddsu2(src1, src2) _saddus2((src2), (src1))
/* SET */
static inline uint32_t _set(uint32_t s1, uint32_t s2, uint32_t s3)
{
    uint64_t e_s2 = (((uint64_t) s2) << 59) >> 54;
    uint64_t e_s3 = (((uint64_t) s3) << 59) >> 59;
    uint64_t tmp  = e_s2 | e_s3;
    return __as_uint(__set(s1, (uint32_t) tmp));
}
/* SET */
static inline uint32_t _setr(uint32_t s1, int32_t s2)
{
    return __set(__as_int(s1), s2);
}
/* VBITSHFLW */
static inline uint32_t _shfl(uint32_t s1)
{
    return __shuffle_bit(s1);
}
/* VSHFL3 */
static inline int64_t _shfl3(uint32_t s1, uint32_t s2)
{
    return __shuffle_3way(__as_uint2((uint64_t) s1),
                          __as_uint2((uint64_t) s2));
}
/* VSHLH */
static inline uint32_t _shl2(uint32_t s1, uint32_t s2)
{
    return __as_uint(__shift_left(__as_short2(s1), (int32_t)s2));
}
/* VSHLMB */
static inline uint32_t _shlmb(uint32_t s1, uint32_t s2)
{
    return __shift_left_merge(__as_int(s1), __as_char4(s2));
}
/* VSHRH */
static inline int32_t _shr2(int32_t s1, uint32_t s2)
{
    return __as_int(__shift_right(__as_short2(s1), (int32_t)s2));
}
/* VSHRMB */
static inline uint32_t _shrmb(uint32_t s1, uint32_t s2)
{
    return __shift_right_merge(__as_int(s1), __as_char4(s2));
}
/* VSHRUH */
static inline uint32_t _shru2(uint32_t s1, uint32_t s2)
{
    return __as_uint(__shift_right(__as_ushort2(s1), s2));
}
/* VSMPYHW */
static inline int32_t _smpy(int32_t s1, int32_t s2)
{
    return __mpy_sat_ext(__as_short2(s1).s[0], __as_short2(s2).s[0]);
}
/* VSMPYHW */
static inline int64_t _smpy2ll(int32_t s1, int32_t s2)
{
    return __as_long(__mpy_sat_ext(__as_short2(s1), __as_short2(s2)));
}
/* VSMPYWW */
static inline int32_t _smpy32(int32_t s1, int32_t s2)
{
    return __mpy_sat(s1, s2);
}
/* VSPACKWH */
static inline int32_t _spack2(int32_t s1, int32_t s2)
{
    return __as_int(__pack_sat(s1, s2));
}
/* C6DSPACKU4 */
static inline uint32_t _spacku4(int32_t s1, int32_t s2)
{
    __short4 tmp = __as_short4(__int2(s2, s1));
    return __as_uint2(__c6dspacku4_ddd(tmp, tmp)).s[0];
}
/* VSPINT */
static inline int32_t _spint(float s1)
{
    return __float_to_int(s1);
}
/* VSPINTHPK */
static inline uint32_t _spinth(float s1)
{
#if defined(__C7100__) || defined(__C7120__)
    /*-------------------------------------------------------------------------
    * NOTE: Implemented differently in host emulation for swizzle syntax. In
    * cl7x version, the following is used:
    * return __as_uint(__vspinthpk_vv(tmp1).s01);
    *-------------------------------------------------------------------------*/
    __float16 tmp1;
    tmp1.s[0] = s1;
    return __as_uint16(__vspinthpk_vv(tmp1)).s[0];
#else
    /* CODEGEN-9069: Direct intrinsics for scaling operations not available. */
    return __as_uint(__float_to_short(s1));
#endif
}
/* VSSHLW */
static inline int32_t _sshl(int32_t s1, uint32_t s2)
{
    return __shift_left_sat(s1, s2);
}
/* VSSHVLW */
static inline int32_t _sshvl(int32_t s1, int32_t s2)
{
    return __shift_left_var_sat(s1, s2);
}
/* VSSHVRW */
static inline int32_t _sshvr(int32_t s1, int32_t s2)
{
    return __shift_right_var_sat(s1, s2);
}
/* VSSUBW */
static inline int32_t _ssub(int32_t s1, int32_t s2)
{
    return __sub_sat(s1, s2);
}
/* VSSUBH */
static inline int32_t _ssub2(int32_t s1, int32_t s2)
{
    return __as_int(__sub_sat(__as_short2(s1), __as_short2(s2)));
}
/* VSUBH */
static inline int32_t _sub2(int32_t s1, int32_t s2)
{
    return __as_int(__as_short2(s1) - __as_short2(s2));
}
/* VSUBB */
static inline int32_t _sub4(int32_t s1, int32_t s2)
{
    return __as_int(__as_char4(s1) - __as_char4(s2));
}
/* VSUBABSB */
static inline int32_t _subabs4(int32_t s1, int32_t s2)
{
    return __as_int(__abs_diff(__as_uchar4(s1), __as_uchar4(s2)));
}
/* VSUBCW */
static inline uint32_t _subc(uint32_t s1, uint32_t s2)
{
    return __sub_cond(s1, s2);
}
/* VSWAPB */
static inline uint32_t _swap4(uint32_t s1)
{
    return __as_uint(__swap(__as_char4(s1)));
}
/* VUNPKLH */
static inline int64_t _unpkh2(uint32_t s1)
{
    __uint2 tmp;
    tmp = __as_uint2((uint64_t) s1);
    return __as_long(__unpack_low(__as_short4(tmp)));
}
/* VUNPKLUH */
static inline int64_t _unpkhu2(uint32_t s1)
{
    __uint2 tmp;
    tmp = __as_uint2((uint64_t) s1);
    return __as_long(__unpack_low(__as_ushort4(tmp)));
}
/* VUNPKHUB */
static inline uint32_t _unpkhu4(uint32_t s1)
{
    return __as_uint(__unpack_high(__as_uchar4(s1)));
}
/* VUNPKLUB */
static inline uint32_t _unpklu4(uint32_t s1)
{
    return __as_uint(__unpack_low(__as_uchar4(s1)));
}
/* VXORW */
static inline int64_t _xorll_c(int32_t s1, int64_t s2)
{
    return __as_long(__int2(s1) ^ __as_int2(s2));
} /* _xorll_c */
/* VXORMPYW */
static inline uint32_t _xormpy(uint32_t s1, uint32_t s2)
{
    return __mpy_xor(s1, s2);
}
/* XPND4H */
static inline uint32_t _xpnd2(uint32_t s1)
{
    /*-------------------------------------------------------------------------
    * NOTE: Implemented differently in host emulation for swizzle syntax. In
    * cl7x version, the following is used:
    * return __as_uint(__expand_lsb_pack_short((unsigned char) s1).s01);
    *-------------------------------------------------------------------------*/
    return __as_uint2(__expand_lsb_pack_short((uint8_t) s1)).s[0];
}
/* XPND8B */
static inline uint32_t _xpnd4(uint32_t s1)
{
    /*-------------------------------------------------------------------------
    * NOTE: Implemented differently in host emulation for swizzle syntax. In
    * cl7x version, the following is used:
    * return __as_uint(__expand_lsb_pack_char((unsigned char) s1).s0123);
    *-------------------------------------------------------------------------*/
    return __as_uint2(__expand_lsb_pack_char((uint8_t) s1)).s[0];
}

/*---------------------------------------------------------------------------*/
/* The add-sub operation is not supported on C7000 and must be split into    */
/* its constituent operations.                                               */
/*---------------------------------------------------------------------------*/
/* VADDW/VSUBW */
static inline int64_t _addsub(int32_t s1, int32_t s2)
{
    return __as_long(__int2(s1 - s2, s1 + s2));
}
/* VADDH/VSUBH */
static inline int64_t _addsub2(uint32_t s1, uint32_t s2)
{
    __short2 tmp1 = __as_short2(s1) + __as_short2(s2);
    __short2 tmp2 = __as_short2(s1) - __as_short2(s2);
    return __as_long(__int2(__as_int(tmp2), __as_int(tmp1)));
}
/* VSADDW/VSSUBW */
static inline int64_t _saddsub(int32_t s1, int32_t s2)
{
    return __as_long(__int2(__sub_sat(s1,s2), __add_sat(s1, s2)));
}
/* VSADDH/VSSUBH */
static inline int64_t _saddsub2(uint32_t s1, uint32_t s2)
{
    __short2 tmp1 = __add_sat(__as_short2(s1), __as_short2(s2));
    __short2 tmp2 = __sub_sat(__as_short2(s1), __as_short2(s2));
    return __as_long(__short4(tmp2, tmp1));
}

/*---------------------------------------------------------------------------*/
/* Complex single-precision floating point multiplies are emulated with      */
/* a complex multiply to intermediate results, and then the operation is     */
/* finished by either adding or subtracting the intermediate results.        */
/*---------------------------------------------------------------------------*/
/* VCMPYSP/VSUBSP */
static inline __float2_t _complex_conjugate_mpysp(__float2_t s1, __float2_t s2)
{
    return __as_float2_t(__complex_conjugate_multiply(__as_cfloat(s1),
                                                      __as_cfloat(s2)));
}
/* VCMPYSP/VADDSP */
static inline __float2_t _complex_mpysp(__float2_t s1, __float2_t s2)
{
    return __as_float2_t(__as_cfloat(s1) * __as_cfloat(s2));
}

/* C6DCMPEQH */
static inline int32_t _cmpeq2(int32_t s1, int32_t s2)
{
    int8_t tmp = __c6dcmpeqh_ddr(__as_short4((uint64_t)s1),
                                 __as_short4((uint64_t)s2));
    return tmp & 0x3;
}
/* C6DCMPEQB */
static inline int32_t _cmpeq4(int32_t s1, int32_t s2)
{
    int8_t tmp = __c6dcmpeqb_ddr(__as_char8((uint64_t)s1),
                                 __as_char8((uint64_t)s2));
    return tmp & 0xF;
}
/* C6DCMPGTH */
static inline int32_t _cmpgt2(int32_t s1, int32_t s2)
{
    int8_t tmp = __c6dcmpgth_ddr(__as_short4((uint64_t)s1),
                                 __as_short4((uint64_t)s2));
    return tmp & 0x3;
}
#define _cmplt2(src1, src2) _cmpgt2((src2), (src1))
/* C6DCMPGTUB */
static inline uint32_t _cmpgtu4(uint32_t s1, uint32_t s2)
{
    int8_t tmp = __c6dcmpgtub_ddr(__as_uchar8((uint64_t)s1),
                                  __as_uchar8((uint64_t)s2));
    return tmp & 0xF;
}
#define _cmpltu4(src1, src2) _cmpgtu4((src2), (src1))

/*---------------------------------------------------------------------------*/
/* _unpkbu4 uses the VUNPKLUB and VUNPKHUB to unpack the low and high 2      */
/* bytes of the argument, and then constructs the result.                    */
/*---------------------------------------------------------------------------*/
static inline int64_t _unpkbu4(uint32_t s1)
{
    return __as_long(__ushort4(__unpack_low(__as_uchar4(s1)),
                               __unpack_high(__as_uchar4(s1))));
}

/*---------------------------------------------------------------------------*/
/* The following intrinsics reinterpret values as another type. For C7000,   */
/* the same effect can be achieved by using the vector reinterpret cast.     */
/*---------------------------------------------------------------------------*/
/* uint32_t _ftoi(float);    */
#define _ftoi  __as_uint

/* float _itof(uint32_t);    */
#define _itof  __as_float

/* int64_t _dtoll(double); */
#define _dtoll(x) ((int64_t)__as_long(x))

/* double _lltod(int64_t); */
#define _lltod __as_double

/*---------------------------------------------------------------------------*/
/* The following intrinsics pack two 32-bit values and then reinterpret the  */
/* value as a 64-bit scalar type. For C7000, vector reinterpret casts can be */
/* used to achieve the same behavior.                                        */
/*                                                                           */
/* Note: Because C7000 cannot individually address the low and high 32-bits  */
/*       of a 64-bit register, these intrinsics will impact performance.     */
/*---------------------------------------------------------------------------*/
static inline double _ftod(float s1, float s2)
{
    return __as_double(__float2(s2, s1));
}
static inline double _itod(uint32_t s1, uint32_t s2)
{
    return __as_double(__uint2(s2, s1));
}

static inline int64_t _itoll(uint32_t s1, uint32_t s2)
{
    return __as_long(__uint2(s2, s1));
}

/*---------------------------------------------------------------------------*/
/* The following two intrinsics are register variants of the EXT/EXTU        */
/* instructions. There are no register versions of these instructions on     */
/* C7000, and so they must be emulated.                                      */
/*                                                                           */
/* When migrating, if the shift values are know to fit into the 6-bit        */
/* boundaries, the shift values can be stored separately and the extractions */
/* can be removed.                                                           */
/*---------------------------------------------------------------------------*/
static inline int32_t _extr(int32_t s1, int32_t s2)
{
    /* Performs about the same, may be conditionally optimized in future */
    uint32_t tmp1 = (((uint32_t)s2) >> 5) & 0x1F;
    uint32_t tmp2 = ((uint32_t)s2) & 0x1F;
    return (s1 << tmp1) >> tmp2;
}
static inline uint32_t _extur(uint32_t s1, int32_t s2)
{
    /* Performs about the same, may be conditionally optimized in future */
    uint32_t tmp1 = (((uint32_t)s2) >> 5) & 0x1F;
    uint32_t tmp2 = ((uint32_t)s2) & 0x1F;
    return (s1 << tmp1) >> tmp2;
}

/*---------------------------------------------------------------------------*/
/* All logical operations on C7000 are 64-bits wide, but even when sign      */
/* extension occurs, the upper 32 bits are just repeats of the sign bit so   */
/* the result doesn't change.                                                */
/*---------------------------------------------------------------------------*/
/* LANDD */
static inline int32_t _land(int32_t s1, int32_t s2)
{
    return __logical_and(s1, s2);
}
/* LANDND */
static inline int32_t _landn(int32_t s1, int32_t s2)
{
    return __logical_andn(s1, s2);
}
/* LORD */
static inline int32_t _lor(int32_t s1, int32_t s2)
{
    return __logical_or(s1, s2);
}

/*---------------------------------------------------------------------------*/
/* 2-point dot products between 2 16-bit sources and 4 8-bit sources are not */
/* natively supported on C7000. To emulate this using C7000's instruction    */
/* set, follow these steps:                                                  */
/*   1. Unpack the 4 8-bit source values to 4 16-bit values                  */
/*   2. Duplicate the 2 16-bit source values into 4 16-bit values            */
/*   3. Perform a 2-point 16-bit dot product                                 */
/*---------------------------------------------------------------------------*/
static inline int64_t _ddotp4(uint32_t s1, uint32_t s2)
{
    __short4 tmp1 = __as_short4(__uint2(s1, s1));
    __short4 tmp2 = __short4(__unpack_low(__as_char4(s2)),
                             __unpack_high(__as_char4(s2)));
    return __as_long(__dotp2(tmp1, tmp2));
}

/*---------------------------------------------------------------------------*/
/* The _lo and _hi intrinsics perform the same operation as vector accessors */
/* on C7000. Behavior can be replicated exactly by using both accessors and  */
/* reinterpret casts.                                                        */
/*---------------------------------------------------------------------------*/
static inline uint32_t _lo(double s1)
{
    return __as_uint2(s1).s[0];
}
static inline float _lof(double s1)
{
    return __as_float2(s1).s[0];
}
static inline uint32_t _loll(int64_t s1)
{
    return __as_uint2(s1).s[0];
}
static inline uint32_t _hi(double s1)
{
    return __as_uint2(s1).s[1];
}
static inline float _hif(double s1)
{
    return __as_float2(s1).s[1];
}
static inline uint32_t _hill(int64_t s1)
{
    return __as_uint2(s1).s[1];
}

/*---------------------------------------------------------------------------*/
/* The following intrinsics multiply the high 16 bits of one source with     */
/* the high 16 bits of the other source. The _smpyh variant saturates        */
/* the result if it does not fit into a signed 32-bit container.             */
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/* Although VMPYHW may be used to emulate _mpyh, it may be beneficial to     */
/* instead use VMPYWW to avoid the need for double vector outputs.           */
/*---------------------------------------------------------------------------*/
static inline int32_t _mpyh(int32_t s1, int32_t s2)
{
    return ((int32_t)__as_short2(s1).s[1]) * ((int32_t)__as_short2(s2).s[1]);
}
/*---------------------------------------------------------------------------*/
/* Although VMPYUHW may be used to emulate _mpyhu, it may be beneficial to   */
/* instead use VMPYWW to avoid the need for double vector outputs.           */
/*---------------------------------------------------------------------------*/
/* VMPYUHW */
static inline uint32_t _mpyhu(uint32_t s1, uint32_t s2)
{
    return ((int32_t)__as_ushort2(s1).s[1]) * ((int32_t)__as_ushort2(s2).s[1]);
}
/*---------------------------------------------------------------------------*/
/* Although VMPYHSUW may be used to emulate _mpyh, it may be beneficial to   */
/* instead use VMPYWW to avoid the need for double vector outputs.           */
/*---------------------------------------------------------------------------*/
static inline int32_t _mpyhsu(int32_t s1, uint32_t s2)
{
    return __as_short2(s1).s[1] * __as_ushort2(s2).s[1];
}
/* VSMPYHW */
static inline int32_t _smpyh(int32_t s1, int32_t s2)
{
    return __mpy_sat_ext(__as_short2(s1).s[1], __as_short2(s2).s[1]);
}
#define _mpyhus(u, s) _mpyhsu((s), (u))

/*---------------------------------------------------------------------------*/
/* The following intrinsics multiply the high 16 bits of one source with     */
/* the low 16 bits of the other source. The _smpyhl and _smpylh variants     */
/* saturate the result if it does not fit into a signed 32-bit container.    */
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/* Although VMPYHW may be used to emulate _mpyhl, it may be beneficial to    */
/* instead use VMPYWW to avoid the need for double vector outputs.           */
/*---------------------------------------------------------------------------*/
static inline int32_t _mpyhl(int32_t s1, int32_t s2)
{
    return __as_short2(s1).s[1] * __as_short2(s2).s[0];
}
/*---------------------------------------------------------------------------*/
/* Although VMPYUHW may be used to emulate _mpyhlu, it may be beneficial to  */
/* instead use VMPYWW to avoid the need for double vector outputs.           */
/*---------------------------------------------------------------------------*/
static inline uint32_t _mpyhlu(uint32_t s1, uint32_t s2)
{
    return __as_ushort2(s1).s[1] * __as_ushort2(s2).s[0];
}
/*---------------------------------------------------------------------------*/
/* Although VMPYSUHW may be used to emulate _mpyhslu, it may be beneficial to*/
/* instead use VMPYWW to avoid the need for double vector outputs.           */
/*---------------------------------------------------------------------------*/
static inline int32_t _mpyhslu(int32_t s1, uint32_t s2)
{
    return __as_short2(s1).s[1] * __as_ushort2(s2).s[0];
}
/*---------------------------------------------------------------------------*/
/* Although VMPYSUHW may be used to emulate _mpyhuls, it may be beneficial to*/
/* instead use VMPYWW to avoid the need for double vector outputs.           */
/*---------------------------------------------------------------------------*/
static inline int32_t _mpyhuls(uint32_t s1, int32_t s2)
{
    return __as_ushort2(s1).s[1] * __as_short2(s2).s[0];
}
/* VSMPYHW */
static inline int32_t _smpyhl(int32_t s1, int32_t s2)
{
    return __mpy_sat_ext(__as_short2(s1).s[1], __as_short2(s2).s[0]);
}
#define _mpylh(l, h) _mpyhl((h), (l))
#define _mpylhu(l, h) _mpyhlu((h), (l))
#define _mpylshu(ls, hu) _mpyhuls((hu), (ls))
#define _mpyluhs(lu, hs) _mpyhslu((hs), (lu))
#define _smpylh(l, h) _smpyhl((h), (l))

/*---------------------------------------------------------------------------*/
/* The following intrinsics multiply the low or high 16 bits of the first    */
/* source with a signed 32 bit second source to return a signed 64-bit       */
/* value. Because this 16-to-32 bit multiply is not supported natively, the  */
/* 16-bit source must be extended to 32 bits.                                */
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/* Although VMPYHD may be used to emulate _mpyhill, it may be beneficial to  */
/* instead use VMPYDD to avoid the need for double vector outputs.           */
/*---------------------------------------------------------------------------*/
static inline int64_t _mpyhill(int32_t s1, int32_t s2)
{
    return ((int64_t)__as_short2(s1).s[1]) * ((int64_t)s2);
}
#define _mpyihll(src1, src2) _mpyhill((src2), (src1))
/*---------------------------------------------------------------------------*/
/* Although VMPYHD may be used to emulate _mpylill, it may be beneficial to  */
/* instead use VMPYDD to avoid the need for double vector outputs.           */
/*---------------------------------------------------------------------------*/
static inline int64_t _mpylill(int32_t s1, int32_t s2)
{
    return ((int64_t)__as_short2(s1).s[0]) * ((int64_t)s2);
}
#define _mpyilll(src1, src2) _mpylill((src2), (src1))

/*---------------------------------------------------------------------------*/
/* The _mpyspdp intrinsic multiplies a float with a double and returns a     */
/* double. This operation is not native on C7000, and must be emulated.      */
/*---------------------------------------------------------------------------*/
static inline double _mpyspdp(float s1, double s2)
{
    return (((double)s1) * s2);
}

/*---------------------------------------------------------------------------*/
/* Deprecated intrinsics that use double as a vector container should no     */
/* longer be used.  The following definitions are only provided for          */
/* compatibility with existing code.                                         */
/*---------------------------------------------------------------------------*/
#define _mpy2(x,y)   _lltod(_mpy2ll((x),(y)))
#define _smpy2(x,y)  _lltod(_smpy2ll((x),(y)))
#define _mpyhi(x,y)  _lltod(_mpyhill((x),(y)))
#define _mpyli(x,y)  _lltod(_mpylill((x),(y)))
#define _mpysu4(x,y) _lltod(_mpysu4ll((x),(y)))
#define _mpyu4(x,y)  _lltod(_mpyu4ll((x),(y)))

/*---------------------------------------------------------------------------*/
/* _mfence stalls until the completion of all CPU-triggered memory           */
/* transactions.  The __memory_fence operation on C7x for all colors is the  */
/* equivalent.                                                               */
/*---------------------------------------------------------------------------*/
#define _mfence() __memory_fence(__MFENCE_ALL_COLORS)

#endif /* C6X_MIGRATION_H */
