/*****************************************************************************/
/*  C6X_HE_MIGRATION.H v#####                                                */
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
#ifndef C6X_HE_MIGRATION_H
#define C6X_HE_MIGRATION_H

#include <stdint.h>

#include "vector.h"
#include "vector_funcs.h"
#include "c7x_he_cr.h"

/*****************************************************************************/
/* How to use this file                                                      */
/*****************************************************************************/
/*---------------------------------------------------------------------------*/
/* This header file provides definitions for macros and intrinsics for the   */
/* purpose of compiling code that is specific to the C6000 family of DSPs    */
/* using host emulation.                                                     */
/*                                                                           */
/* Please refer to the C700 Host Emulation User's guide and c6x_migration.h  */
/* found within the C7000 compiler installation package for detailed         */
/* instructions on how to use this file.                                     */
/*                                                                           */
/* The three sections of this file are as follows:                           */
/*   1. Predefined macros                                                    */
/*     Macros and keywords that would have been defined internally by the    */
/*     C6000 compiler, but do not exist within the C7000 compiler.           */
/*   2. Legacy types                                                         */
/*     Definitions and explanations of types that exist in the C6000         */
/*     programming model, but not in the C7000 programming model. Also       */
/*     contains examples of how to migrate current projects to use the C7000 */
/*     OpenCL vector type programming model.                                 */
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
/*     be emulated by a different instruction or instructions. In these      */
/*     cases, a comment describing the behavior and an example of a C7000    */
/*     styled emulation of the builtin will be provided.                     */
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
    #define __BIG_ENDIAN   1
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
/* OpenCL native vector types.                                               */
/*                                                                           */
/* The definition of __x128_t is found in modules/c7x_c_funcs/c7x_c_funcs.h. */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* __x128_t Generators                                                       */
/*                                                                           */
/* Replace with OpenCL initializations, e.g.:                                */
/* double2 = (double2)(1.0, 2.0); // Instead of _dto128(1.0, 2.0);           */
/* int4 = (int4)(x, y, z, h);     // Instead of _llto128(itoll(h, z),        */
/*                                //                     itoll(y, x));       */
/*---------------------------------------------------------------------------*/
__x128_t _dup32_128(uint32_t src);
__x128_t _ito128(uint32_t src1, uint32_t src2, uint32_t src3, uint32_t src4);
__x128_t _fto128(float src1, float src2, float src3 , float src4);
__x128_t _llto128(int64_t src1, int64_t src2);
__x128_t _dto128(double src1, double src2);

/*---------------------------------------------------------------------------*/
/* __x128_t Accessors                                                        */
/*                                                                           */
/* Replace with OpenCL accessors, e.g.:                                      */
/* int4 a = (int4)(1, 2, 3, 4);                                              */
/* a.s3   // Instead of _get32_128(a, 3);                                    */
/* a.even // Instead of _itoll(_get32_128(a, 0), _get32_128(a, 2));          */
/* a.hi   // Instead of _hi128(a);                                           */
/* a.lo   // Instead of _lo128(a);                                           */
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
class __float2_t
{
    public:
        // Default constructor
        __float2_t() {} 

        // Can be loaded/stored from other __float2_t 
        __float2_t (const __float2_t& obj)
        {
            this->set(obj.data.s0, obj.data.s1);
        }

        // Sets values of a __float2_t
        // Should use ftod instead
        void set(uint32_t hi, uint32_t lo)
        {
            this->data = uint2(hi,lo);
        }    
        
        uint32_t get_hi()
        {
            return this->data.s0;
        }   

        uint32_t get_lo()
        {
            return this->data.s1;
        }

    private:
        uint2 data;
};
__float2_t _ftof2(float a, float b);

/*---------------------------------------------------------------------------*/
/* Conversions from 16-bit precision ints to __float2_t                      */
/*                                                                           */
/* C7000 ISA:                                                                */
/*   VINTHSPL                                                                */
/*   VINTHSPUL                                                               */
/*   VINTHSPH                                                                */
/*   VINTHSPUH                                                               */
/*---------------------------------------------------------------------------*/
__float2_t _dinthsp(uint32_t src1);
__float2_t _dinthspu(uint32_t src1);

/*---------------------------------------------------------------------------*/
/* Conversion from 32-bit precision ints to __float2_t                       */
/*                                                                           */
/* C7000 ISA:                                                                */
/*   VINTSP                                                                  */
/*   VINTSPU                                                                 */
/*---------------------------------------------------------------------------*/
__float2_t _dintsp(int64_t src1);
__float2_t _dintspu(int64_t src1);

/*---------------------------------------------------------------------------*/
/* Conversion from __float2_t to 16-bit precision ints                       */
/*                                                                           */
/* C7000 ISA:                                                                */
/*   VSPINTHPK                                                               */
/*                                                                           */
/* See Also:                                                                 */
/*   VSPINTH                                                                 */
/*---------------------------------------------------------------------------*/
uint32_t _dspinth(__float2_t src1);

/*---------------------------------------------------------------------------*/
/* Conversion from __float2_t to 2 32-bit precision ints                     */
/*                                                                           */
/* C7000 ISA:                                                                */
/*   VSPINT                                                                  */
/*---------------------------------------------------------------------------*/
int64_t _dspint(__float2_t src1);

/*---------------------------------------------------------------------------*/
/* Reinterpretation between 64-bit integers and __float2_t                   */
/*                                                                           */
/* Note: When using host emulation, a distinction must be made between       */
/* __float2_t and a double. This is due to host hardware limitations and is  */
/* decribed in more detail in the C7000 host emulation user's guide. A double*/
/* data type should only be used when the intended result is a double        */
/* precision floating point number. If the desired result is 2 floating point*/
/* types to leverage SIMD capabilities, a __float2_t type must be used in    */
/* host emulation.                                                           */ 
/*                                                                           */
/* As a direct result of the distinction between a double and a __float2_t,  */
/* the definitions of _lltof2 and _lltod are distinct in host emulation. A   */
/* full list of intrinsics that have distinct definitions in host emulation  */
/* can be found in the C7000 host emulation user's guide.                    */
/*---------------------------------------------------------------------------*/
__float2_t _lltof2(int64_t arg);
int64_t _f2toll(__float2_t arg);

/*---------------------------------------------------------------------------*/
/* __float2_t accessor methods. Used to grab lo/hi portions of a __float2_t. */
/*---------------------------------------------------------------------------*/
float _hif2(__float2_t arg);
float _lof2(__float2_t arg);

/*---------------------------------------------------------------------------*/
/* There is no difference between _amem and _mem for C7000, as all loads     */
/* and stores have unaligned capability. Replace these intrinsics with basic */
/* C dereference operators on a pointer to an OpenCL vector.                 */
/*---------------------------------------------------------------------------*/
#define _amem8_f2        _amemd8
#define _amem8_f2_const  _amemd8_const
#define _mem8_f2         _memd8
#define _mem8_f2_const   _memd8_const

/*---------------------------------------------------------------------------*/
/* Rather than use the PACKW or PACKWDLY4 instruction, use _fdmv_f2 or       */
/* _fdmvd_f2 to obtain a __float2_t from two float values. PACK instructions */
/* are used to obtain double results, which are different than float2_t types*/
/* in host emulation.                                                        */
/*---------------------------------------------------------------------------*/
__float2_t _fdmv_f2(float arg1, float arg2);
__float2_t _fdmvd_f2(float arg1, float arg2);

/*---------------------------------------------------------------------------*/
/* After changing references to __x128_t to use OpenCL vectors, replace      */
/* these two operations with OpenCL-style vector accessors.                  */
/*                                                                           */
/* e.g.:                                                                     */
/* float2 _hif2_128(float4 src) { return src.hi; }                           */
/*                                                                           */
/* To access __float2_t members of an __x128_t in host emulation, use the    */
/* the following intrinsics.                                                 */
/*---------------------------------------------------------------------------*/
__float2_t _hif2_128(__x128_t src);
__float2_t _lof2_128(__x128_t src);

/*---------------------------------------------------------------------------*/
/* After changing references to __x128_t to use OpenCL vectors, replace      */
/* this intrinsic with an OpenCL initialization.                             */
/*                                                                           */
/* e.g.:                                                                     */
/* float4 _f2to128(float2 src1, float2 src2)                                 */
/* {                                                                         */
/*   return (float4)(src1, src2);                                            */
/* }                                                                         */
/*                                                                           */
/* To convert two __float2_t types into one __x128_t, use the following      */
/* intrinsic.                                                                */
/*---------------------------------------------------------------------------*/
__x128_t _f2to128(__float2_t src1, __float2_t src2);

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
/* __int40_t _labs(__int40_t);       VABSD    */
/* __int40_t _ldotp2(int, int);      VDOTP2HD */
/* unsigned _lnorm(__int40_t);       VNORMD   */
/* __int40_t _lsadd(int, __int40_t); ADDD     */
/* __int40_t _lssub(int, __int40_t); SUBD     */
/* int _sat(__int40_t);              VSATLW   */

/*****************************************************************************/
/* Legacy OpenCL vector types                                                */
/*****************************************************************************/
/*---------------------------------------------------------------------------*/
/* OpenCL v1.2 defines the long type as a 64-bit integer value, while C6000  */
/* defined it as either 32 or 40 bits, depending on certain configurations.  */
/* Because of this, C6000 could not use the OpenCL vector types based off of */
/* the 64-bit OpenCL long, instead supporting a new type as an extension     */
/* named 'longlong'.                                                         */
/*                                                                           */
/* The long type on C7000 is 64 bits, matching the OpenCL specification.     */
/*                                                                           */
/* The extension vector types are defined here for migration, but code       */
/* leveraging the 'longlong' type should be migrated to using the standard   */
/* long type specifier.                                                      */
/*---------------------------------------------------------------------------*/

typedef long2  __long2;
//typedef long3  __long3;
typedef long4  __long4;
typedef long8  __long8;

typedef ulong2  __ulong2;
//typedef ulong3  __ulong3;
typedef ulong4  __ulong4;
typedef ulong8  __ulong8;

#if !__TI_STRICT_ANSI_MODE__
typedef int64_t     longlong;
typedef __long2  longlong2;
//typedef __long3  longlong3;
typedef __long4  longlong4;
typedef __long8  longlong8;

typedef __ulong   ulonglong;
typedef __ulong2  ulonglong2;
//typedef __ulong3  ulonglong3;
typedef __ulong4  ulonglong4;
typedef __ulong8  ulonglong8;
#endif
typedef int64_t     __longlong;
typedef __long2  __longlong2;
//typedef __long3  __longlong3;
typedef __long4  __longlong4;
typedef __long8  __longlong8;

typedef __ulong   __ulonglong;
typedef __ulong2  __ulonglong2;
//typedef __ulong3  __ulonglong3;
typedef __ulong4  __ulonglong4;
typedef __ulong8  __ulonglong8;

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
#define _amem2(p)         (*(unsigned short*)(char*)(p))
#define _amem2_const(p)   (*(unsigned short*)(char*)(p))
#define _amem4(p)         (*(unsigned int*)(char*)(p))
#define _amem4_const(p)   (*(unsigned int*)(char*)(p))
#define _amem8(p)         (*(unsigned long*)(char*)(p))
#define _amem8_const(p)   (*(unsigned long*)(char*)(p))
#define _amemd8(p)        (*(double*)(char*)(p))
#define _amemd8_const(p)  (*(double*)(char*)(p))
#define _mem2(p)          (*(unsigned short*)(char*)(p))
#define _mem2_const(p)    (*(unsigned short*)(char*)(p))
#define _mem4(p)          (*(unsigned int*)(char*)(p))
#define _mem4_const(p)    (*(unsigned int*)(char*)(p))
#define _mem8(p)          (*(unsigned long*)(char*)(p))
#define _mem8_const(p)    (*(unsigned long*)(char*)(p))
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
__float2_t _daddsp(__float2_t, __float2_t);
/* VSUBSP */
__float2_t _dsubsp(__float2_t, __float2_t);
/* VMPYSP */
__float2_t _dmpysp(__float2_t, __float2_t);
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
int64_t _cmpy32r1(int64_t, int64_t);
/* VCMPYHW */
int64_t _cmpy(uint32_t, uint32_t);
/* VCMPYHW */
__x128_t _dcmpy(int64_t, int64_t);
/* VCMPYRHH */
uint32_t _cmpyr(uint32_t, uint32_t);
/* VCCMPYR1HH */
int64_t _dccmpyr1(int64_t, int64_t);
/* VCMPYR1HH */
uint32_t _cmpyr1(uint32_t, uint32_t);
/* VCMPYR1HH */
int64_t _dcmpyr1(int64_t, int64_t);
/* VCCMPYHW */
__x128_t _dccmpy(int64_t, int64_t);
/* VCCMPYR1WW */
int64_t _ccmpy32r1(int64_t, int64_t);
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
int32_t _abs(int32_t);
/* VABSH */
int32_t _abs2(int32_t);
/* VADDH */
int32_t _add2(int32_t, int32_t);
/* VADDB */
int32_t _add4(int32_t, int32_t);
/* VAVGH */
int32_t _avg2(int32_t, int32_t);
/* VAVGUB */
uint32_t _avgu4(uint32_t, uint32_t);
/* VBITCNTB */
uint32_t _bitc4(uint32_t);
/* VBITRW */
uint32_t _bitr(uint32_t);
/* CLR */
uint32_t _clr(uint32_t, uint32_t, uint32_t);
/* CLR */
uint32_t _clrr(uint32_t, int32_t);
/* VCROT270H */
int32_t _crot270(int32_t);
/* VCROT90H */
int32_t _crot90(int32_t);
/* VADDW */
int64_t _dadd(int64_t, int64_t);
/* VADDH */
int64_t _dadd2(int64_t, int64_t);
/* VADDW */
int64_t _dadd_c(int32_t, int64_t);
/* VAPYSH */
int64_t _dapys2(int64_t, int64_t);
/* VAVGH */
int64_t _davg2(int64_t, int64_t);
/* VAVGNRH */
int64_t _davgnr2(int64_t, int64_t);
/* VAVGNRUB */
int64_t _davgnru4(int64_t, int64_t);
/* VAVGUB */
int64_t _davgu4(int64_t, int64_t);
/* C6DCMPEQH */
uint32_t _dcmpeq2(int64_t, int64_t);
/* C6DCMPPEQB */
uint32_t _dcmpeq4(int64_t, int64_t);
/* C6DCMPGTH */
uint32_t _dcmpgt2(int64_t, int64_t);
/* C6DCMPGTUB */
uint32_t _dcmpgtu4(int64_t, int64_t);
/* VCROT270H */
int64_t _dcrot270(int64_t);
/* VCROT90H */
int64_t _dcrot90(int64_t);
/* C6DDOTP2HHW */
int64_t _ddotph2(int64_t, uint32_t);
/* C6DDOTP2HRHH */
uint32_t _ddotph2r(int64_t, uint32_t);
/* C6DDOTP2LHW */
int64_t _ddotpl2(int64_t, uint32_t);
/* C6DDOTP2LRHH */
uint32_t _ddotpl2r(int64_t, uint32_t);
/* VBITDEALW */
uint32_t _deal(uint32_t);
/* VMAXH */
int64_t _dmax2(int64_t, int64_t);
/* VMAXUB */
int64_t _dmaxu4(int64_t, int64_t);
/* VMINH */
int64_t _dmin2(int64_t, int64_t);
/* VMINUB */
int64_t _dminu4(int64_t, int64_t);
/* PACKW */
int64_t _dmv(uint32_t, uint32_t);
/* PACKWDLY4 */
int64_t _dmvd(int32_t, int32_t);
/* VDOTP2HW */
int32_t _dotp2(int32_t, int32_t);
/* VDOTP4HW */
int32_t _dotp4h(int64_t, int64_t);
/* VDOTP4HD */
int64_t _dotp4hll(int64_t, int64_t);
/* C6DOTPN2HW */
int32_t _dotpn2(int32_t, int32_t);
/* C6DOTPN2RSUHH */
int32_t _dotpnrsu2(int32_t, uint32_t);
#define _dotpnrus2(u, s) _dotpnrsu2((s), (u))
/* C6DOTP2RSUHW */
int32_t _dotprsu2(int32_t, uint32_t);
/* VDOTP4SUBW */
int32_t _dotpsu4(int32_t, uint32_t);
#define _dotpus4(u, s) _dotpsu4((s), (u))
/* VDOTP4SUHW */
int32_t _dotpsu4h(int64_t, int64_t);
/* VDOTP4SUHD */
int64_t _dotpsu4hll(int64_t, int64_t);
/* VDOTP4UBW */
uint32_t _dotpu4(uint32_t, uint32_t);
/* PACKP2 */
int64_t _dpack2(uint32_t, uint32_t);
/* DPACKH2 */
int64_t _dpackh2(int64_t, int64_t);
/* DPACKH4 */
int64_t _dpackh4(int64_t, int64_t);
/* DPACKHL2 */
int64_t _dpackhl2(int64_t, int64_t);
/* DPACKL2 */
int64_t _dpackl2(int64_t, int64_t);
/* DPACKL4 */
int64_t _dpackl4(int64_t, int64_t);
/* DPACKLH2 */
int64_t _dpacklh2(int64_t, int64_t);
/* PACKLH4 */
int64_t _dpacklh4(uint32_t, uint32_t);
/* PACKX2 */
int64_t _dpackx2(uint32_t, uint32_t);
/* VDPINT */
int32_t _dpint(double);
/* VSADDW */
int64_t _dsadd(int64_t, int64_t);
/* VSADDH */
int64_t _dsadd2(int64_t, int64_t);
/* VSHLW */
int64_t _dshl(int64_t, uint32_t);
/* VSHLH */
int64_t _dshl2(int64_t, uint32_t);
/* VSHRW */
int64_t _dshr(int64_t, uint32_t);
/* VSHRH */
int64_t _dshr2(int64_t, uint32_t);
/* VSHRUW */
int64_t _dshru(int64_t, uint32_t);
/* VSHRUH */
int64_t _dshru2(int64_t, uint32_t);
/* C6DSPACKU4 */
int64_t _dspacku4(int64_t, int64_t);
/* VSSUBW */
int64_t _dssub(int64_t, int64_t);
/* VSSUBH */
int64_t _dssub2(int64_t, int64_t);
/* VSUBW */
int64_t _dsub(int64_t, int64_t);
/* VSUBH */
int64_t _dsub2(int64_t, int64_t);
/* XPND4H */
int64_t _dxpnd2(uint32_t);
/* XPND8B */
int64_t _dxpnd4(uint32_t);
/* EXT */
int32_t _ext(int32_t, uint32_t, uint32_t);
/* EXTU */
uint32_t _extu(uint32_t, uint32_t, uint32_t);
/* VABSDP */
double _fabs(double);
/* VABSSP */
float _fabsf(float);
/* PACKW */
double _fdmv(float, float);
/* PACKWDLY4 */
double _fdmvd(float, float);
/* VGMPYW */
uint32_t _gmpy(uint32_t, uint32_t);
/* VGMPYB */
int32_t _gmpy4(int32_t, int32_t);
/* VLMBDW */
uint32_t _lmbd(uint32_t, uint32_t);
/* VMAXH */
int32_t _max2(int32_t, int32_t);
/* VMAXUB */
uint32_t _maxu4(uint32_t, uint32_t);
/* VMINH */
int32_t _min2(int32_t, int32_t);
/* VMINUB */
uint32_t _minu4(uint32_t, uint32_t);
/* VMPYHW */
int32_t _mpy(int32_t, int32_t);
/* C6MPY2IR */
int64_t _mpy2ir(uint32_t, int32_t);
/* VMPYHW */
int64_t _mpy2ll(int32_t, int32_t);
/* VMPYWW */
int32_t _mpy32(int32_t, int32_t);
/* VMPYWD */
int64_t _mpy32ll(int32_t, int32_t);
#define _mpy32l(s1, s2) _mpy32ll((s1), (s2))
/* VMPYSUWD */
int64_t _mpy32su(int32_t, uint32_t);
#define _mpy32us(u, s) _mpy32su((s), (u))
/* VMPYUWD */
int64_t _mpy32u(uint32_t, uint32_t);
/* C6MPYHIR */
int32_t _mpyhir(int32_t, int32_t);
#define _mpyihr(src1, src2) _mpyhir((src2), (src1))
/* VMPYWD */
int64_t _mpyidll(int32_t, int32_t);
/* C6MPYLIR */
int32_t _mpylir(int32_t, int32_t);
#define _mpyilr(src1, src2) _mpylir((src2), (src1))
/* VMPYSP2DP */
double _mpysp2dp(float, float);
/* VMPYSUHW */
int32_t _mpysu(int32_t, uint32_t);
#define _mpyus(u, s) _mpysu((s), (u))
/* VMPYSUBH */
int64_t _mpysu4ll(int32_t, uint32_t);
#define _mpyus4ll(src1, src2) _mpysu4ll((src2), (src1))
/* VMPYUHW */
uint32_t _mpyu(uint32_t, uint32_t);
/* VMPYUHW */
int64_t _mpyu2(uint32_t, uint32_t);
/* VMPYUBH */
int64_t _mpyu4ll(uint32_t, uint32_t);
/* MVDLY4 */
uint32_t _mvd(uint32_t);
/* VNORMW */
uint32_t _norm(int32_t);
/* PACKP2 */
uint32_t _pack2(uint32_t, uint32_t);
/* DPACKH2 */
uint32_t _packh2(uint32_t, uint32_t);
/* DPACKH4 */
uint32_t _packh4(uint32_t, uint32_t);
/* DPACKHL2 */
uint32_t _packhl2(uint32_t, uint32_t);
/* DPACKL4 */
uint32_t _packl4(uint32_t, uint32_t);
/* DPACKLH2 */
uint32_t _packlh2(uint32_t, uint32_t);
#define _swap2(src) _packlh2((src), (src))
/* VRCPDP */
double _rcpdp(double);
/* VRCPSP */
float _rcpsp(float);
/* VROTLW */
uint32_t _rotl(uint32_t, uint32_t);
/* VRPACKH */
uint32_t _rpack2(uint32_t, uint32_t);
/* VRSQRDP */
double _rsqrdp(double);
/* VRSQRSP */
float _rsqrsp(float);
/* VSADDW */
int32_t _sadd(int32_t, int32_t);
/* VSADDH */
int32_t _sadd2(int32_t, int32_t);
/* VSADDUB */
uint32_t _saddu4(uint32_t, uint32_t);
/* VSADDUSH */
int32_t _saddus2(uint32_t, int32_t);
#define _saddsu2(src1, src2) _saddus2((src2), (src1))
/* SET */
uint32_t _set(uint32_t, uint32_t, uint32_t);
/* SET */
uint32_t _setr(uint32_t, int32_t);
/* VBITSHFLW */
uint32_t _shfl(uint32_t);
/* VSHFL3 */
int64_t _shfl3(uint32_t, uint32_t);
/* VSHLH */
uint32_t _shl2(uint32_t, uint32_t);
/* VSHLMB */
uint32_t _shlmb(uint32_t, uint32_t);
/* VSHRH */
int32_t _shr2(int32_t, uint32_t);
/* VSHRMB */
uint32_t _shrmb(uint32_t, uint32_t);
/* VSHRUH */
uint32_t _shru2(uint32_t, uint32_t);
/* SMPYHW */
int32_t _smpy(int32_t, int32_t);
/* VSMPYHW */
int64_t _smpy2ll(int32_t, int32_t);
/* VSMPYWW */
int32_t _smpy32(int32_t, int32_t);
/* VSPACKWH */
int32_t _spack2(int32_t, int32_t);
/* C6DSPACKU4 */
uint32_t _spacku4(int32_t, int32_t);
/* VSPINT */
int32_t _spint(float);
/* VSPINTHPK */
uint32_t _spinth(float);
/* VSSHLW */
int32_t _sshl(int32_t, uint32_t);
/* VSSHVLW */
int32_t _sshvl(int32_t, int32_t);
/* VSSHVRW */
int32_t _sshvr(int32_t, int32_t);
/* VSSUBW */
int32_t _ssub(int32_t, int32_t);
/* VSSUBH */
int32_t _ssub2(int32_t, int32_t);
/* VSUBH */
int32_t _sub2(int32_t, int32_t);
/* VSUBB */
int32_t _sub4(int32_t, int32_t);
/* VSUBABSB */
int32_t _subabs4(int32_t, int32_t);
/* VSUBCW */
uint32_t _subc(uint32_t, uint32_t);
/* VSWAPB */
uint32_t _swap4(uint32_t);
/* VUNPKLH */
int64_t _unpkh2(uint32_t);
/* VUNPKLUH */
int64_t _unpkhu2(uint32_t);
/* VUNPKHUB */
uint32_t _unpkhu4(uint32_t);
/* VUNPKLUB */
uint32_t _unpklu4(uint32_t);
/* VXORW */
int64_t _xorll_c(int32_t, int64_t);
/* VXORMPYW */
uint32_t _xormpy(uint32_t, uint32_t);
/* XPND4H */
uint32_t _xpnd2(uint32_t);
/* XPND8B */
uint32_t _xpnd4(uint32_t);

/*---------------------------------------------------------------------------*/
/* The add-sub operation is not supported on C7000 and must be split into    */
/* its constituent operations.                                               */
/*---------------------------------------------------------------------------*/
/* VADDW/VSUBW */
int64_t _addsub(int32_t, int32_t);
/* VADDH/VSUBH */
int64_t _addsub2(uint32_t, uint32_t);
/* VSADDW/VSSUBW */
int64_t _saddsub(int32_t, int32_t);
/* VSADDH/VSSUBH */
int64_t _saddsub2(uint32_t, uint32_t);

/*---------------------------------------------------------------------------*/
/* Complex single-precision floating point multiplies are emulated with      */
/* a complex multiply to intermediate results, and then the operation is     */
/* finished by either adding or subtracting the intermediate results.        */
/*---------------------------------------------------------------------------*/
/* VCMPYSP/VSUBSP */
double _complex_conjugate_mpysp(double, double);
/* VCMPYSP/VADDSP */
double _complex_mpysp(double, double);

/*---------------------------------------------------------------------------*/
/* These 4 intrinsics are emulated by extracting a subset of the bits from   */
/* the result of a DCMPP instruction by using an ANDW instruction. For C7X   */
/* migration, use the vector predicates generated by the vector comparison   */
/* operations.                                                               */
/*---------------------------------------------------------------------------*/
/* VCMPEQH */
int32_t _cmpeq2(int32_t, int32_t);
/* VCMPEQB */
int32_t _cmpeq4(int32_t, int32_t);
/* VCMPGTH */
int32_t _cmpgt2(int32_t, int32_t);
#define _cmplt2(src1, src2) _cmpgt2((src2), (src1))
/* VCMPGTUB */
uint32_t _cmpgtu4(uint32_t, uint32_t);
#define _cmpltu4(src1, src2) _cmpgtu4((src2), (src1))

/*---------------------------------------------------------------------------*/
/* _unpkbu4 uses the VUNPKLUB and VUNPKHUB to unpack the low and high 2      */
/* bytes of the argument, and then constructs the result. An equivalent C7X  */
/* piece of code would look like:                                            */
/*                                                                           */
/* ushort4 _unpkbu4(uchar4 src)                                              */
/* {                                                                         */
/*   ushort4 dst;                                                            */
/*   dst.lo = __unpack_low(src);                                             */
/*   dst.hi = __unpack_high(src);                                            */
/*   return dst;                                                             */
/* }                                                                         */
/*---------------------------------------------------------------------------*/
int64_t _unpkbu4(uint32_t);

/*---------------------------------------------------------------------------*/
/* The following intrinsics reinterpret values as another type. For C7000,   */
/* the same effect can be achieved by using the OpenCL-style reinterpret     */
/* cast. For example, to cast from int32_t to float (_itof):                 */
/*                                                                           */
/* float _itof(int32_t src)                                                  */
/* {                                                                         */
/*   return as_float(src);                                                   */
/* }                                                                         */
/*---------------------------------------------------------------------------*/
/* uint32_t _ftoi(float);    */
#define _ftoi  __as_uint

/* float _itof(uint32_t);    */
#define _itof  __as_float

/* int64_t _dtoll(double); */
#define _dtoll __as_longlong

/* double _lltod(int64_t); */
#define _lltod __as_double

/*---------------------------------------------------------------------------*/
/* The following intrinsics pack two 32-bit values and then reinterpret the  */
/* value as a 64-bit scalar type. For C7000, OpenCL-style reinterpret casts  */
/* can be used to achieve the same behavior.                                 */
/*                                                                           */
/* Note: Because C7000 cannot individually address the low and high 32-bits  */
/*       of a 64-bit register, these intrinsics will impact performance.     */
/*                                                                           */
/* An example for _itod:                                                     */
/*                                                                           */
/* double _itod(int32_t src1, int32_t src2)                                  */
/* {                                                                         */
/*   int2 tsrc = (int2)(src1, src2);                                         */
/*   return as_double(tsrc);                                                 */
/* }                                                                         */
/*---------------------------------------------------------------------------*/
double _ftod(float, float);
double _itod(uint32_t, uint32_t);
int64_t _itoll(uint32_t, uint32_t);

/*---------------------------------------------------------------------------*/
/* The following two intrinsics are register variants of the EXT/EXTU        */
/* instructions. There are no register versions of these instructions on     */
/* C7000, and so they must be emulated.                                      */
/*                                                                           */
/* When migrating, if the shift values are know to fit into the 6-bit        */
/* boundaries, the shift values can be stored separately and the extractions */
/* can be removed.                                                           */
/*                                                                           */
/* int32_t _extr(int32_t src1, int32_t src2)                                 */
/* {                                                                         */
/*   uint lshift = (((uint32_t)shift_vals << 54) >> 59);                     */
/*   uint rshift = (((uint32_t)shift_vals << 59) >> 59);                     */
/*   return (src1 << lshift) >> rshift;                                      */
/* }                                                                         */
/*---------------------------------------------------------------------------*/
int32_t _extr(int32_t, int32_t);
uint32_t _extur(uint32_t, int32_t);

/*---------------------------------------------------------------------------*/
/* All logical operations on C7000 are 64-bits wide, so the following        */
/* intrinsics are emulated by zeroing out the top 64 bits of a register      */
/* and returning the result of the corresponding C7000 instruction.          */
/*---------------------------------------------------------------------------*/
/* LANDD */
int32_t _land(int32_t, int32_t);
/* LANDND */
int32_t _landn(int32_t, int32_t);
/* LORD */
int32_t _lor(int32_t, int32_t);

/*---------------------------------------------------------------------------*/
/* 4-point dot products between 2 16-bit sources and 4 8-bit sources are not */
/* natively supported on C7000. To emulate this using C7000's instruction    */
/* set, follow these steps:                                                  */
/*   1. Unpack the 4 8-bit source values to 4 16-bit values                  */
/*   2. Duplicate the 2 16-bit source values into 4 16-bit values            */
/*   3. Perform a 4-point 16-bit dot product                                 */
/*                                                                           */
/* In C code using OpenCL and C7000 intrinsics:                              */
/*                                                                           */
/* int2 _ddotp4(short2 src1, char4 src2)                                     */
/* {                                                                         */
/*   short4 tsrc1 = (short4)(src1, src1);                                    */
/*   short4 tsrc2 = (short4)(__unpack_low(src2), __unpack_high(src2));       */
/*   return __dotp4(tsrc1, tsrc2);                                           */
/* }                                                                         */
/*---------------------------------------------------------------------------*/
int64_t _ddotp4(uint32_t, uint32_t);

/*---------------------------------------------------------------------------*/
/* The _lo and _hi intrinsics perform the same operation as OpenCL accessors */
/* on C7000. Behavior can be replicated exactly by using both accessors and  */
/* reinterpret casts.                                                        */
/*                                                                           */
/* Example:                                                                  */
/*                                                                           */
/* uint _hi(double src)                                                      */
/* {                                                                         */
/*   uint2 tsrc = as_uint2(src);                                             */
/*   return tsrc.hi; // Or tsrc.s1 or tsrc.[1]                               */
/* }                                                                         */
/*---------------------------------------------------------------------------*/
uint32_t _lo(double);
float _lof(double);
uint32_t _loll(int64_t);
uint32_t _hi(double);
float _hif(double);
uint32_t _hill(int64_t);

/*---------------------------------------------------------------------------*/
/* The following intrinsics multiply the high 16 bits of one source with     */
/* the high 16 bits of the other source. The _smpyh variant saturates        */
/* the result if it does not fit into a signed 32-bit container.             */
/*                                                                           */
/* Behavior can be replicated with OpenCL vectors and accessors, e.g.:       */
/*                                                                           */
/* int32_t _mpyh(short2 src1, short2 src2)                                   */
/* {                                                                         */
/*   return __mpy_ext(src1.hi, src2.hi);                                     */
/* }                                                                         */
/*---------------------------------------------------------------------------*/
/* VMPYHW */
int32_t _mpyh(int32_t, int32_t);
/* VMPYUHW */
uint32_t _mpyhu(uint32_t, uint32_t);
/* VMPYSUHW */
int32_t _mpyhsu(int32_t, uint32_t);
/* VSMPYHW */
int32_t _smpyh(int32_t, int32_t);
#define _mpyhus(u, s) _mpyhsu((s), (u))

/*---------------------------------------------------------------------------*/
/* The following intrinsics multiply the high 16 bits of one source with     */
/* the low 16 bits of the other source. The _smpyhl and _smpylh variants     */
/* saturate the result if it does not fit into a signed 32-bit container.    */
/*                                                                           */
/* Behavior can be replicated with OpenCL vectors and accessors, e.g.:       */
/*                                                                           */
/* int32_t _mpyhslu(short2 src1, ushort2 src2)                               */
/* {                                                                         */
/*   return __mpy_ext(src1.hi, src2.lo);                                     */
/* }                                                                         */
/*---------------------------------------------------------------------------*/
/* VMPYHW */
int32_t _mpyhl(int32_t, int32_t);
/* VMPYUHW */
uint32_t _mpyhlu(uint32_t, uint32_t);
/* VMPYSUHW */
int32_t _mpyhslu(int32_t, uint32_t);
/* VMPYSUHW */
int32_t _mpyhuls(uint32_t, int32_t);
/* VSMPYHW */
int32_t _smpyhl(int32_t, int32_t);
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
/*                                                                           */
/* Behavior can be replicated with OpenCL vectors and accessors, e.g.:       */
/*                                                                           */
/* int64_t _mpyhill(short2 src1, int32_t src2)                               */
/* {                                                                         */
/*   return __mpy_ext(convert_int(src1.hi), src2.lo);                        */
/* }                                                                         */
/*---------------------------------------------------------------------------*/
/* VMPYWD */
int64_t _mpyhill(int32_t, int32_t);
#define _mpyihll(src1, src2) _mpyhill((src2), (src1))
/* VMPYWD */
int64_t _mpylill(int32_t, int32_t);
#define _mpyilll(src1, src2) _mpylill((src2), (src1))

/*---------------------------------------------------------------------------*/
/* The _mpyspdp intrinsic multiplies a float with a double and returns a     */
/* double. This operation is not native on C7000, and must be emulated.      */
/*                                                                           */
/* double _mpyspdp(float src1, double src2)                                  */
/* {                                                                         */
/*   double tsrc1 = convert_double(src1);                                    */
/*   return (tsrc1 * src2);                                                  */
/* }                                                                         */
/*---------------------------------------------------------------------------*/
double _mpyspdp(float, double);

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

#endif /* C6X_HE_MIGRATION_H */
