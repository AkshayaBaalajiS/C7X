/*****************************************************************************/
/*  C7X_HE_INTRINSICS.H v#####                                               */
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
#ifndef C7X_HE_INTR_H
#define C7X_HE_INTR_H

#include "vector.h"
#include "vector_funcs.h"
#include "c7x_he_strm.h"
#include "c7x_he_cr.h"

#ifdef _MSC_VER
#undef __max
#undef __min
/* __MINGW32__ is defined in both 32 bit and 64 bit MINGW */
#elif defined __MINGW32__
#undef __max
#undef __min
#endif

/*****************************************************************************/
/* NOTE OF CLARIFICATION: Functions that are declared with a reference to a  */
/* vector type are declared using the EQUIV_ACCESS_T<DEPTH> type alias, e.g.:*/
/*                                                                           */
/* void __max_circ_pred(char2 a,char2::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);*/
/*                                                                           */
/* This requires no special action on the part of the user, who from the     */
/* point of view of the source code ought to interpret this declaration as   */
/* being no different than the following:                                    */
/*                                                                           */
/*   void __max_circ_pred(char2 a, char2& b, __vpred& c);                    */
/*                                                                           */
/* This means that the user may pass a variable of the corresponding vector  */
/* type to the function, and a reference will be used to write data into the */
/* variable as output. The EQUIV_ACCESS_T type alias is an implementation    */
/* detail of the C7x host emulation framework to provide writable access     */
/* via the vector type reference argument.                                   */
/*****************************************************************************/

int8_t __abs(int8_t a);
char2 __abs(char2 a);
char4 __abs(char4 a);
char8 __abs(char8 a);
char16 __abs(char16 a);
char32 __abs(char32 a);
char64 __abs(char64 a);
cchar __abs(cchar a);
cchar2 __abs(cchar2 a);
cchar4 __abs(cchar4 a);
cchar8 __abs(cchar8 a);
cchar16 __abs(cchar16 a);
cchar32 __abs(cchar32 a);
int64_t __abs(int64_t a);
long2 __abs(long2 a);
long4 __abs(long4 a);
long8 __abs(long8 a);
clong __abs(clong a);
clong2 __abs(clong2 a);
clong4 __abs(clong4 a);
double __abs(double a);
double2 __abs(double2 a);
double4 __abs(double4 a);
double8 __abs(double8 a);
cdouble __abs(cdouble a);
cdouble2 __abs(cdouble2 a);
cdouble4 __abs(cdouble4 a);
int16_t __abs(int16_t a);
short2 __abs(short2 a);
short4 __abs(short4 a);
short8 __abs(short8 a);
short16 __abs(short16 a);
short32 __abs(short32 a);
cshort __abs(cshort a);
cshort2 __abs(cshort2 a);
cshort4 __abs(cshort4 a);
cshort8 __abs(cshort8 a);
cshort16 __abs(cshort16 a);
float __abs(float a);
float2 __abs(float2 a);
float4 __abs(float4 a);
float8 __abs(float8 a);
float16 __abs(float16 a);
cfloat __abs(cfloat a);
cfloat2 __abs(cfloat2 a);
cfloat4 __abs(cfloat4 a);
cfloat8 __abs(cfloat8 a);
int32_t __abs(int32_t a);
int2 __abs(int2 a);
int4 __abs(int4 a);
int8 __abs(int8 a);
int16 __abs(int16 a);
cint __abs(cint a);
cint2 __abs(cint2 a);
cint4 __abs(cint4 a);
cint8 __abs(cint8 a);
uint8_t __abs_diff(uint8_t a, uint8_t b);
uchar2 __abs_diff(uchar2 a, uchar2 b);
uchar4 __abs_diff(uchar4 a, uchar4 b);
uchar8 __abs_diff(uchar8 a, uchar8 b);
uchar16 __abs_diff(uchar16 a, uchar16 b);
uchar32 __abs_diff(uchar32 a, uchar32 b);
uchar64 __abs_diff(uchar64 a, uchar64 b);
uint64_t __abs_diff(uint64_t a, uint64_t b);
ulong2 __abs_diff(ulong2 a, ulong2 b);
ulong4 __abs_diff(ulong4 a, ulong4 b);
ulong8 __abs_diff(ulong8 a, ulong8 b);
uint16_t __abs_diff(uint16_t a, uint16_t b);
ushort2 __abs_diff(ushort2 a, ushort2 b);
ushort4 __abs_diff(ushort4 a, ushort4 b);
ushort8 __abs_diff(ushort8 a, ushort8 b);
ushort16 __abs_diff(ushort16 a, ushort16 b);
ushort32 __abs_diff(ushort32 a, ushort32 b);
uint32_t __abs_diff(uint32_t a, uint32_t b);
uint2 __abs_diff(uint2 a, uint2 b);
uint4 __abs_diff(uint4 a, uint4 b);
uint8 __abs_diff(uint8 a, uint8 b);
uint16 __abs_diff(uint16 a, uint16 b);
int8_t __add(__vpred a, int8_t b, int8_t c);
char2 __add(__vpred a, char2 b, char2 c);
char4 __add(__vpred a, char4 b, char4 c);
char8 __add(__vpred a, char8 b, char8 c);
char16 __add(__vpred a, char16 b, char16 c);
char32 __add(__vpred a, char32 b, char32 c);
char64 __add(__vpred a, char64 b, char64 c);
uint8_t __add(__vpred a, uint8_t b, uint8_t c);
uchar2 __add(__vpred a, uchar2 b, uchar2 c);
uchar4 __add(__vpred a, uchar4 b, uchar4 c);
uchar8 __add(__vpred a, uchar8 b, uchar8 c);
uchar16 __add(__vpred a, uchar16 b, uchar16 c);
uchar32 __add(__vpred a, uchar32 b, uchar32 c);
uchar64 __add(__vpred a, uchar64 b, uchar64 c);
int64_t __add(__vpred a, int64_t b, int64_t c);
long2 __add(__vpred a, long2 b, long2 c);
long4 __add(__vpred a, long4 b, long4 c);
long8 __add(__vpred a, long8 b, long8 c);
uint64_t __add(__vpred a, uint64_t b, uint64_t c);
ulong2 __add(__vpred a, ulong2 b, ulong2 c);
ulong4 __add(__vpred a, ulong4 b, ulong4 c);
ulong8 __add(__vpred a, ulong8 b, ulong8 c);
int16_t __add(__vpred a, int16_t b, int16_t c);
short2 __add(__vpred a, short2 b, short2 c);
short4 __add(__vpred a, short4 b, short4 c);
short8 __add(__vpred a, short8 b, short8 c);
short16 __add(__vpred a, short16 b, short16 c);
short32 __add(__vpred a, short32 b, short32 c);
uint16_t __add(__vpred a, uint16_t b, uint16_t c);
ushort2 __add(__vpred a, ushort2 b, ushort2 c);
ushort4 __add(__vpred a, ushort4 b, ushort4 c);
ushort8 __add(__vpred a, ushort8 b, ushort8 c);
ushort16 __add(__vpred a, ushort16 b, ushort16 c);
ushort32 __add(__vpred a, ushort32 b, ushort32 c);
int32_t __add(__vpred a, int32_t b, int32_t c);
int2 __add(__vpred a, int2 b, int2 c);
int4 __add(__vpred a, int4 b, int4 c);
int8 __add(__vpred a, int8 b, int8 c);
int16 __add(__vpred a, int16 b, int16 c);
uint32_t __add(__vpred a, uint32_t b, uint32_t c);
uint2 __add(__vpred a, uint2 b, uint2 c);
uint4 __add(__vpred a, uint4 b, uint4 c);
uint8 __add(__vpred a, uint8 b, uint8 c);
uint16 __add(__vpred a, uint16 b, uint16 c);
int8_t __add_sat(int8_t a, int8_t b);
char2 __add_sat(char2 a, char2 b);
char4 __add_sat(char4 a, char4 b);
char8 __add_sat(char8 a, char8 b);
char16 __add_sat(char16 a, char16 b);
char32 __add_sat(char32 a, char32 b);
char64 __add_sat(char64 a, char64 b);
cchar __add_sat(cchar a, cchar b);
cchar2 __add_sat(cchar2 a, cchar2 b);
cchar4 __add_sat(cchar4 a, cchar4 b);
cchar8 __add_sat(cchar8 a, cchar8 b);
cchar16 __add_sat(cchar16 a, cchar16 b);
cchar32 __add_sat(cchar32 a, cchar32 b);
int16_t __add_sat(int16_t a, int16_t b);
short2 __add_sat(short2 a, short2 b);
short4 __add_sat(short4 a, short4 b);
short8 __add_sat(short8 a, short8 b);
short16 __add_sat(short16 a, short16 b);
short32 __add_sat(short32 a, short32 b);
cshort __add_sat(cshort a, cshort b);
cshort2 __add_sat(cshort2 a, cshort2 b);
cshort4 __add_sat(cshort4 a, cshort4 b);
cshort8 __add_sat(cshort8 a, cshort8 b);
cshort16 __add_sat(cshort16 a, cshort16 b);
uint8_t __add_sat(uint8_t a, uint8_t b);
uchar2 __add_sat(uchar2 a, uchar2 b);
uchar4 __add_sat(uchar4 a, uchar4 b);
uchar8 __add_sat(uchar8 a, uchar8 b);
uchar16 __add_sat(uchar16 a, uchar16 b);
uchar32 __add_sat(uchar32 a, uchar32 b);
uchar64 __add_sat(uchar64 a, uchar64 b);
uint16_t __add_sat(uint16_t a, uint16_t b);
ushort2 __add_sat(ushort2 a, ushort2 b);
ushort4 __add_sat(ushort4 a, ushort4 b);
ushort8 __add_sat(ushort8 a, ushort8 b);
ushort16 __add_sat(ushort16 a, ushort16 b);
ushort32 __add_sat(ushort32 a, ushort32 b);
uint8_t __add_sat(uint8_t a, int8_t b);
uchar2 __add_sat(uchar2 a, char2 b);
uchar4 __add_sat(uchar4 a, char4 b);
uchar8 __add_sat(uchar8 a, char8 b);
uchar16 __add_sat(uchar16 a, char16 b);
uchar32 __add_sat(uchar32 a, char32 b);
uchar64 __add_sat(uchar64 a, char64 b);
uint16_t __add_sat(uint16_t a, int16_t b);
ushort2 __add_sat(ushort2 a, short2 b);
ushort4 __add_sat(ushort4 a, short4 b);
ushort8 __add_sat(ushort8 a, short8 b);
ushort16 __add_sat(ushort16 a, short16 b);
ushort32 __add_sat(ushort32 a, short32 b);
uint32_t __add_sat(uint32_t a, int32_t b);
uint2 __add_sat(uint2 a, int2 b);
uint4 __add_sat(uint4 a, int4 b);
uint8 __add_sat(uint8 a, int8 b);
uint16 __add_sat(uint16 a, int16 b);
uint32_t __add_sat(uint32_t a, uint32_t b);
uint2 __add_sat(uint2 a, uint2 b);
uint4 __add_sat(uint4 a, uint4 b);
uint8 __add_sat(uint8 a, uint8 b);
uint16 __add_sat(uint16 a, uint16 b);
int32_t __add_sat(int32_t a, int32_t b);
int2 __add_sat(int2 a, int2 b);
int4 __add_sat(int4 a, int4 b);
int8 __add_sat(int8 a, int8 b);
int16 __add_sat(int16 a, int16 b);
cint __add_sat(cint a, cint b);
cint2 __add_sat(cint2 a, cint2 b);
cint4 __add_sat(cint4 a, cint4 b);
cint8 __add_sat(cint8 a, cint8 b);
int64_t __addd_ddd(int64_t a, int64_t b);
uint64_t __addd_ddd(uint64_t a, uint64_t b);
int64_t __addd_dkd(int64_t a, int64_t b);
uint64_t __addd_dkd(uint64_t a, uint64_t b);
double __adddp_ddd(double a, double b);
float __addsp_rrr(float a, float b);
int32_t __addw_rkr(int32_t a, int32_t b);
uint32_t __addw_rkr(uint32_t a, uint32_t b);
int32_t __addw_rrr(int32_t a, int32_t b);
uint32_t __addw_rrr(uint32_t a, uint32_t b);
__vpred __and(__vpred a, __vpred b);
__vpred __and_ppp(__vpred a, __vpred b);
char8 __andd_ddd(char8 a, char8 b);
short4 __andd_ddd(short4 a, short4 b);
int2 __andd_ddd(int2 a, int2 b);
int64_t __andd_ddd(int64_t a, int64_t b);
uchar8 __andd_ddd(uchar8 a, uchar8 b);
ushort4 __andd_ddd(ushort4 a, ushort4 b);
uint2 __andd_ddd(uint2 a, uint2 b);
uint64_t __andd_ddd(uint64_t a, uint64_t b);
int64_t __andd_dkd(int64_t a, int64_t b);
uint64_t __andd_dkd(uint64_t a, uint64_t b);
__vpred __andn(__vpred a, __vpred b);
int8_t __andn(int8_t a, int8_t b);
char2 __andn(char2 a, char2 b);
char4 __andn(char4 a, char4 b);
char8 __andn(char8 a, char8 b);
int16_t __andn(int16_t a, int16_t b);
short2 __andn(short2 a, short2 b);
short4 __andn(short4 a, short4 b);
int32_t __andn(int32_t a, int32_t b);
int2 __andn(int2 a, int2 b);
int64_t __andn(int64_t a, int64_t b);
uint8_t __andn(uint8_t a, uint8_t b);
uchar2 __andn(uchar2 a, uchar2 b);
uchar4 __andn(uchar4 a, uchar4 b);
uchar8 __andn(uchar8 a, uchar8 b);
uint16_t __andn(uint16_t a, uint16_t b);
ushort2 __andn(ushort2 a, ushort2 b);
ushort4 __andn(ushort4 a, ushort4 b);
uint32_t __andn(uint32_t a, uint32_t b);
uint2 __andn(uint2 a, uint2 b);
uint64_t __andn(uint64_t a, uint64_t b);
char16 __andn(char16 a, char16 b);
char32 __andn(char32 a, char32 b);
char64 __andn(char64 a, char64 b);
short8 __andn(short8 a, short8 b);
short16 __andn(short16 a, short16 b);
short32 __andn(short32 a, short32 b);
int4 __andn(int4 a, int4 b);
int8 __andn(int8 a, int8 b);
int16 __andn(int16 a, int16 b);
long2 __andn(long2 a, long2 b);
long4 __andn(long4 a, long4 b);
long8 __andn(long8 a, long8 b);
__vpred __andn_ppp(__vpred a, __vpred b);
char8 __andnd_ddd(char8 a, char8 b);
short4 __andnd_ddd(short4 a, short4 b);
int2 __andnd_ddd(int2 a, int2 b);
int64_t __andnd_ddd(int64_t a, int64_t b);
uchar8 __andnd_ddd(uchar8 a, uchar8 b);
ushort4 __andnd_ddd(ushort4 a, ushort4 b);
uint2 __andnd_ddd(uint2 a, uint2 b);
uint64_t __andnd_ddd(uint64_t a, uint64_t b);
int64_t __andnd_dkd(int64_t a, int64_t b);
uint64_t __andnd_dkd(uint64_t a, uint64_t b);
char4 __andnw_rkr(char4 a, char4 b);
short2 __andnw_rkr(short2 a, short2 b);
int32_t __andnw_rkr(int32_t a, int32_t b);
uchar4 __andnw_rkr(uchar4 a, uchar4 b);
ushort2 __andnw_rkr(ushort2 a, ushort2 b);
uint32_t __andnw_rkr(uint32_t a, uint32_t b);
char4 __andnw_rrr(char4 a, char4 b);
short2 __andnw_rrr(short2 a, short2 b);
int32_t __andnw_rrr(int32_t a, int32_t b);
uchar4 __andnw_rrr(uchar4 a, uchar4 b);
ushort2 __andnw_rrr(ushort2 a, ushort2 b);
uint32_t __andnw_rrr(uint32_t a, uint32_t b);
char4 __andw_rkr(char4 a, char4 b);
short2 __andw_rkr(short2 a, short2 b);
int32_t __andw_rkr(int32_t a, int32_t b);
uchar4 __andw_rkr(uchar4 a, uchar4 b);
ushort2 __andw_rkr(ushort2 a, ushort2 b);
uint32_t __andw_rkr(uint32_t a, uint32_t b);
char4 __andw_rrr(char4 a, char4 b);
short2 __andw_rrr(short2 a, short2 b);
int32_t __andw_rrr(int32_t a, int32_t b);
uchar4 __andw_rrr(uchar4 a, uchar4 b);
ushort2 __andw_rrr(ushort2 a, ushort2 b);
uint32_t __andw_rrr(uint32_t a, uint32_t b);
int8_t __apply_sign(int8_t a, int8_t b);
char2 __apply_sign(char2 a, char2 b);
char4 __apply_sign(char4 a, char4 b);
char8 __apply_sign(char8 a, char8 b);
char16 __apply_sign(char16 a, char16 b);
char32 __apply_sign(char32 a, char32 b);
char64 __apply_sign(char64 a, char64 b);
int64_t __apply_sign(int64_t a, int64_t b);
long2 __apply_sign(long2 a, long2 b);
long4 __apply_sign(long4 a, long4 b);
long8 __apply_sign(long8 a, long8 b);
int16_t __apply_sign(int16_t a, int16_t b);
short2 __apply_sign(short2 a, short2 b);
short4 __apply_sign(short4 a, short4 b);
short8 __apply_sign(short8 a, short8 b);
short16 __apply_sign(short16 a, short16 b);
short32 __apply_sign(short32 a, short32 b);
int32_t __apply_sign(int32_t a, int32_t b);
int2 __apply_sign(int2 a, int2 b);
int4 __apply_sign(int4 a, int4 b);
int8 __apply_sign(int8 a, int8 b);
int16 __apply_sign(int16 a, int16 b);
uint32_t __binary_log(uint32_t a);
uint2 __binary_log(uint2 a);
uint4 __binary_log(uint4 a);
uint8 __binary_log(uint8 a);
uint16 __binary_log(uint16 a);
__vpred __expand_vpred(uint64_t a, uint8_t b);
__vpred __expand_vpred(__vpred a, uint8_t b);
__vpred __pack_vpred(uint64_t a, uint8_t b);
__vpred __pack_vpred(__vpred a, uint8_t b);
__vpred __bit_reverse(__vpred a);
int64_t __bit_reverse(int64_t a);
long2 __bit_reverse(long2 a);
long4 __bit_reverse(long4 a);
long8 __bit_reverse(long8 a);
uint64_t __bit_reverse(uint64_t a);
ulong2 __bit_reverse(ulong2 a);
ulong4 __bit_reverse(ulong4 a);
ulong8 __bit_reverse(ulong8 a);
int32_t __bit_reverse(int32_t a);
int2 __bit_reverse(int2 a);
int4 __bit_reverse(int4 a);
int8 __bit_reverse(int8 a);
int16 __bit_reverse(int16 a);
uint32_t __bit_reverse(uint32_t a);
uint2 __bit_reverse(uint2 a);
uint4 __bit_reverse(uint4 a);
uint8 __bit_reverse(uint8 a);
uint16 __bit_reverse(uint16 a);
uchar8 __bit_transpose(uchar8 a);
uchar16 __bit_transpose(uchar16 a);
uchar32 __bit_transpose(uchar32 a);
uchar64 __bit_transpose(uchar64 a);
__vpred __bitr_pp(__vpred a);
uint8_t __c6dcmpeqb_ddr(char8 a, char8 b);
uint8_t __c6dcmpeqh_ddr(short4 a, short4 b);
uint8_t __c6dcmpgth_ddr(short4 a, short4 b);
uint8_t __c6dcmpgtub_ddr(uchar8 a, uchar8 b);
int2 __c6ddotp2hhw_drd(short4 a, short2 b);
short2 __c6ddotp2hrhh_drr(short4 a, short2 b);
int2 __c6ddotp2lhw_drd(short4 a, short2 b);
short2 __c6ddotp2lrhh_drr(short4 a, short2 b);
void __c6dmpyhw_vvw(short32 a, short32 b, int16::EQUIV_ACCESS_T<0>& c, int16::EQUIV_ACCESS_T<0>& d);
void __c6dmpysubh_vvw(char32 a, uchar32 b, short16::EQUIV_ACCESS_T<0>& c, short16::EQUIV_ACCESS_T<0>& d);
void __c6dmpyubh_vvw(uchar32 a, uchar32 b, ushort16::EQUIV_ACCESS_T<0>& c, ushort16::EQUIV_ACCESS_T<0>& d);
void __c6dmpyuhw_vvw(ushort16 a, ushort16 b, uint8::EQUIV_ACCESS_T<0>& c, uint8::EQUIV_ACCESS_T<0>& d);
int32_t __c6dotp2rsuhw_rrr(short2 a, ushort2 b);
int32_t __c6dotpn2hw_rrr(short2 a, short2 b);
int16_t __c6dotpn2rsuhh_rrr(short2 a, ushort2 b);
void __c6dsmpyhw_vvw(short32 a, short32 b, int16::EQUIV_ACCESS_T<0>& c, int16::EQUIV_ACCESS_T<0>& d);
uchar8 __c6dspacku4_ddd(short4 a, short4 b);
int2 __c6mpy2ir_rrd(short2 a, int32_t b);
int32_t __c6mpyhir_rrr(short2 a, int32_t b);
int32_t __c6mpylir_rrr(short2 a, int32_t b);
int64_t __classify(double a);
long2 __classify(double2 a);
long4 __classify(double4 a);
long8 __classify(double8 a);
int32_t __classify(float a);
int2 __classify(float2 a);
int4 __classify(float4 a);
int8 __classify(float8 a);
int16 __classify(float16 a);
uint32_t __clear(uint32_t a, uint32_t b);
uint32_t __clr_rrr(uint32_t a, uint32_t b);
cint2 __cmatmpy_ext(cshort2 a, cshort4 b);
cint4 __cmatmpy_ext(cshort4 a, cshort8 b);
cint8 __cmatmpy_ext(cshort8 a, cshort16 b);
cshort2 __cmatmpy_fx(cshort2 a, cshort4 b);
cshort4 __cmatmpy_fx(cshort4 a, cshort8 b);
cshort8 __cmatmpy_fx(cshort8 a, cshort16 b);
int32_t __cmp_eq(int64_t a, int64_t b);
int32_t __cmp_eq(int64_t a, int32_t b);
int32_t __cmp_eq(double a, double b);
int32_t __cmp_eq(float a, float b);
int32_t __cmp_eq(int32_t a, int32_t b);
__vpred __cmp_eq_pred(int8_t a, int8_t b);
__vpred __cmp_eq_pred(char2 a, char2 b);
__vpred __cmp_eq_pred(char4 a, char4 b);
__vpred __cmp_eq_pred(char8 a, char8 b);
__vpred __cmp_eq_pred(char16 a, char16 b);
__vpred __cmp_eq_pred(char32 a, char32 b);
__vpred __cmp_eq_pred(char64 a, char64 b);
__vpred __cmp_eq_pred(uint8_t a, uint8_t b);
__vpred __cmp_eq_pred(uchar2 a, uchar2 b);
__vpred __cmp_eq_pred(uchar4 a, uchar4 b);
__vpred __cmp_eq_pred(uchar8 a, uchar8 b);
__vpred __cmp_eq_pred(uchar16 a, uchar16 b);
__vpred __cmp_eq_pred(uchar32 a, uchar32 b);
__vpred __cmp_eq_pred(uchar64 a, uchar64 b);
__vpred __cmp_eq_pred(int64_t a, int64_t b);
__vpred __cmp_eq_pred(long2 a, long2 b);
__vpred __cmp_eq_pred(long4 a, long4 b);
__vpred __cmp_eq_pred(long8 a, long8 b);
__vpred __cmp_eq_pred(uint64_t a, uint64_t b);
__vpred __cmp_eq_pred(ulong2 a, ulong2 b);
__vpred __cmp_eq_pred(ulong4 a, ulong4 b);
__vpred __cmp_eq_pred(ulong8 a, ulong8 b);
__vpred __cmp_eq_pred(double a, double b);
__vpred __cmp_eq_pred(double2 a, double2 b);
__vpred __cmp_eq_pred(double4 a, double4 b);
__vpred __cmp_eq_pred(double8 a, double8 b);
__vpred __cmp_eq_pred(int16_t a, int16_t b);
__vpred __cmp_eq_pred(short2 a, short2 b);
__vpred __cmp_eq_pred(short4 a, short4 b);
__vpred __cmp_eq_pred(short8 a, short8 b);
__vpred __cmp_eq_pred(short16 a, short16 b);
__vpred __cmp_eq_pred(short32 a, short32 b);
__vpred __cmp_eq_pred(uint16_t a, uint16_t b);
__vpred __cmp_eq_pred(ushort2 a, ushort2 b);
__vpred __cmp_eq_pred(ushort4 a, ushort4 b);
__vpred __cmp_eq_pred(ushort8 a, ushort8 b);
__vpred __cmp_eq_pred(ushort16 a, ushort16 b);
__vpred __cmp_eq_pred(ushort32 a, ushort32 b);
__vpred __cmp_eq_pred(float a, float b);
__vpred __cmp_eq_pred(float2 a, float2 b);
__vpred __cmp_eq_pred(float4 a, float4 b);
__vpred __cmp_eq_pred(float8 a, float8 b);
__vpred __cmp_eq_pred(float16 a, float16 b);
__vpred __cmp_eq_pred(int32_t a, int32_t b);
__vpred __cmp_eq_pred(int2 a, int2 b);
__vpred __cmp_eq_pred(int4 a, int4 b);
__vpred __cmp_eq_pred(int8 a, int8 b);
__vpred __cmp_eq_pred(int16 a, int16 b);
__vpred __cmp_eq_pred(uint32_t a, uint32_t b);
__vpred __cmp_eq_pred(uint2 a, uint2 b);
__vpred __cmp_eq_pred(uint4 a, uint4 b);
__vpred __cmp_eq_pred(uint8 a, uint8 b);
__vpred __cmp_eq_pred(uint16 a, uint16 b);
int32_t __cmp_ge(int64_t a, int64_t b);
int32_t __cmp_ge(int64_t a, int32_t b);
int32_t __cmp_ge(uint64_t a, uint64_t b);
int32_t __cmp_ge(uint64_t a, uint32_t b);
int32_t __cmp_ge(uint32_t a, uint32_t b);
int32_t __cmp_ge(int32_t a, int32_t b);
__vpred __cmp_ge_pred(int8_t a, int8_t b);
__vpred __cmp_ge_pred(char2 a, char2 b);
__vpred __cmp_ge_pred(char4 a, char4 b);
__vpred __cmp_ge_pred(char8 a, char8 b);
__vpred __cmp_ge_pred(char16 a, char16 b);
__vpred __cmp_ge_pred(char32 a, char32 b);
__vpred __cmp_ge_pred(char64 a, char64 b);
__vpred __cmp_ge_pred(int64_t a, int64_t b);
__vpred __cmp_ge_pred(long2 a, long2 b);
__vpred __cmp_ge_pred(long4 a, long4 b);
__vpred __cmp_ge_pred(long8 a, long8 b);
__vpred __cmp_ge_pred(int16_t a, int16_t b);
__vpred __cmp_ge_pred(short2 a, short2 b);
__vpred __cmp_ge_pred(short4 a, short4 b);
__vpred __cmp_ge_pred(short8 a, short8 b);
__vpred __cmp_ge_pred(short16 a, short16 b);
__vpred __cmp_ge_pred(short32 a, short32 b);
__vpred __cmp_ge_pred(uint8_t a, uint8_t b);
__vpred __cmp_ge_pred(uchar2 a, uchar2 b);
__vpred __cmp_ge_pred(uchar4 a, uchar4 b);
__vpred __cmp_ge_pred(uchar8 a, uchar8 b);
__vpred __cmp_ge_pred(uchar16 a, uchar16 b);
__vpred __cmp_ge_pred(uchar32 a, uchar32 b);
__vpred __cmp_ge_pred(uchar64 a, uchar64 b);
__vpred __cmp_ge_pred(uint64_t a, uint64_t b);
__vpred __cmp_ge_pred(ulong2 a, ulong2 b);
__vpred __cmp_ge_pred(ulong4 a, ulong4 b);
__vpred __cmp_ge_pred(ulong8 a, ulong8 b);
__vpred __cmp_ge_pred(uint16_t a, uint16_t b);
__vpred __cmp_ge_pred(ushort2 a, ushort2 b);
__vpred __cmp_ge_pred(ushort4 a, ushort4 b);
__vpred __cmp_ge_pred(ushort8 a, ushort8 b);
__vpred __cmp_ge_pred(ushort16 a, ushort16 b);
__vpred __cmp_ge_pred(ushort32 a, ushort32 b);
__vpred __cmp_ge_pred(uint32_t a, uint32_t b);
__vpred __cmp_ge_pred(uint2 a, uint2 b);
__vpred __cmp_ge_pred(uint4 a, uint4 b);
__vpred __cmp_ge_pred(uint8 a, uint8 b);
__vpred __cmp_ge_pred(uint16 a, uint16 b);
__vpred __cmp_ge_pred(int32_t a, int32_t b);
__vpred __cmp_ge_pred(int2 a, int2 b);
__vpred __cmp_ge_pred(int4 a, int4 b);
__vpred __cmp_ge_pred(int8 a, int8 b);
__vpred __cmp_ge_pred(int16 a, int16 b);
int32_t __cmp_gt(int64_t a, int64_t b);
int32_t __cmp_gt(int64_t a, int32_t b);
int32_t __cmp_gt(uint64_t a, uint64_t b);
int32_t __cmp_gt(uint64_t a, uint32_t b);
int32_t __cmp_gt(uint32_t a, uint32_t b);
int32_t __cmp_gt(int32_t a, int32_t b);
__vpred __cmp_gt_pred(int8_t a, int8_t b);
__vpred __cmp_gt_pred(char2 a, char2 b);
__vpred __cmp_gt_pred(char4 a, char4 b);
__vpred __cmp_gt_pred(char8 a, char8 b);
__vpred __cmp_gt_pred(char16 a, char16 b);
__vpred __cmp_gt_pred(char32 a, char32 b);
__vpred __cmp_gt_pred(char64 a, char64 b);
__vpred __cmp_gt_pred(int64_t a, int64_t b);
__vpred __cmp_gt_pred(long2 a, long2 b);
__vpred __cmp_gt_pred(long4 a, long4 b);
__vpred __cmp_gt_pred(long8 a, long8 b);
__vpred __cmp_gt_pred(int16_t a, int16_t b);
__vpred __cmp_gt_pred(short2 a, short2 b);
__vpred __cmp_gt_pred(short4 a, short4 b);
__vpred __cmp_gt_pred(short8 a, short8 b);
__vpred __cmp_gt_pred(short16 a, short16 b);
__vpred __cmp_gt_pred(short32 a, short32 b);
__vpred __cmp_gt_pred(uint8_t a, uint8_t b);
__vpred __cmp_gt_pred(uchar2 a, uchar2 b);
__vpred __cmp_gt_pred(uchar4 a, uchar4 b);
__vpred __cmp_gt_pred(uchar8 a, uchar8 b);
__vpred __cmp_gt_pred(uchar16 a, uchar16 b);
__vpred __cmp_gt_pred(uchar32 a, uchar32 b);
__vpred __cmp_gt_pred(uchar64 a, uchar64 b);
__vpred __cmp_gt_pred(uint64_t a, uint64_t b);
__vpred __cmp_gt_pred(ulong2 a, ulong2 b);
__vpred __cmp_gt_pred(ulong4 a, ulong4 b);
__vpred __cmp_gt_pred(ulong8 a, ulong8 b);
__vpred __cmp_gt_pred(uint16_t a, uint16_t b);
__vpred __cmp_gt_pred(ushort2 a, ushort2 b);
__vpred __cmp_gt_pred(ushort4 a, ushort4 b);
__vpred __cmp_gt_pred(ushort8 a, ushort8 b);
__vpred __cmp_gt_pred(ushort16 a, ushort16 b);
__vpred __cmp_gt_pred(ushort32 a, ushort32 b);
__vpred __cmp_gt_pred(uint32_t a, uint32_t b);
__vpred __cmp_gt_pred(uint2 a, uint2 b);
__vpred __cmp_gt_pred(uint4 a, uint4 b);
__vpred __cmp_gt_pred(uint8 a, uint8 b);
__vpred __cmp_gt_pred(uint16 a, uint16 b);
__vpred __cmp_gt_pred(int32_t a, int32_t b);
__vpred __cmp_gt_pred(int2 a, int2 b);
__vpred __cmp_gt_pred(int4 a, int4 b);
__vpred __cmp_gt_pred(int8 a, int8 b);
__vpred __cmp_gt_pred(int16 a, int16 b);
int32_t __cmp_le(double a, double b);
int32_t __cmp_le(float a, float b);
__vpred __cmp_le_pred(double a, double b);
__vpred __cmp_le_pred(double2 a, double2 b);
__vpred __cmp_le_pred(double4 a, double4 b);
__vpred __cmp_le_pred(double8 a, double8 b);
__vpred __cmp_le_pred(float a, float b);
__vpred __cmp_le_pred(float2 a, float2 b);
__vpred __cmp_le_pred(float4 a, float4 b);
__vpred __cmp_le_pred(float8 a, float8 b);
__vpred __cmp_le_pred(float16 a, float16 b);
int32_t __cmp_lt(double a, double b);
int32_t __cmp_lt(float a, float b);
__vpred __cmp_lt_pred(double a, double b);
__vpred __cmp_lt_pred(double2 a, double2 b);
__vpred __cmp_lt_pred(double4 a, double4 b);
__vpred __cmp_lt_pred(double8 a, double8 b);
__vpred __cmp_lt_pred(float a, float b);
__vpred __cmp_lt_pred(float2 a, float2 b);
__vpred __cmp_lt_pred(float4 a, float4 b);
__vpred __cmp_lt_pred(float8 a, float8 b);
__vpred __cmp_lt_pred(float16 a, float16 b);
int32_t __cmpeqd_ddr(int64_t a, int64_t b);
int32_t __cmpeqd_dkr(int64_t a, int32_t b);
int32_t __cmpeqdp_ddr(double a, double b);
int32_t __cmpeqsp_rrr(float a, float b);
int32_t __cmpeqw_rkr(int32_t a, int32_t b);
int32_t __cmpeqw_rrr(int32_t a, int32_t b);
int32_t __cmpged_ddr(int64_t a, int64_t b);
int32_t __cmpged_dkr(int64_t a, int32_t b);
int32_t __cmpgeud_ddr(uint64_t a, uint64_t b);
int32_t __cmpgeud_dkr(uint64_t a, uint32_t b);
int32_t __cmpgeuw_rkr(uint32_t a, uint32_t b);
int32_t __cmpgeuw_rrr(uint32_t a, uint32_t b);
int32_t __cmpgew_rkr(int32_t a, int32_t b);
int32_t __cmpgew_rrr(int32_t a, int32_t b);
int32_t __cmpgtd_ddr(int64_t a, int64_t b);
int32_t __cmpgtd_dkr(int64_t a, int32_t b);
int32_t __cmpgtud_ddr(uint64_t a, uint64_t b);
int32_t __cmpgtud_dkr(uint64_t a, uint32_t b);
int32_t __cmpgtuw_rkr(uint32_t a, uint32_t b);
int32_t __cmpgtuw_rrr(uint32_t a, uint32_t b);
int32_t __cmpgtw_rkr(int32_t a, int32_t b);
int32_t __cmpgtw_rrr(int32_t a, int32_t b);
int32_t __cmpledp_ddr(double a, double b);
int32_t __cmplesp_rrr(float a, float b);
int32_t __cmpltdp_ddr(double a, double b);
int32_t __cmpltsp_rrr(float a, float b);
cint __cmpy_conj_ext(cshort a, cshort b);
cint2 __cmpy_conj_ext(cshort2 a, cshort2 b);
cint4 __cmpy_conj_ext(cshort4 a, cshort4 b);
cint8 __cmpy_conj_ext(cshort8 a, cshort8 b);
cshort __cmpy_conj_fx(cshort a, cshort b);
cshort2 __cmpy_conj_fx(cshort2 a, cshort2 b);
cshort4 __cmpy_conj_fx(cshort4 a, cshort4 b);
cshort8 __cmpy_conj_fx(cshort8 a, cshort8 b);
cshort16 __cmpy_conj_fx(cshort16 a, cshort16 b);
cint __cmpy_conj_fx(cint a, cint b);
cint2 __cmpy_conj_fx(cint2 a, cint2 b);
cint4 __cmpy_conj_fx(cint4 a, cint4 b);
cint8 __cmpy_conj_fx(cint8 a, cint8 b);
cint __cmpy_ext(cshort a, cshort b);
cint2 __cmpy_ext(cshort2 a, cshort2 b);
cint4 __cmpy_ext(cshort4 a, cshort4 b);
cint8 __cmpy_ext(cshort8 a, cshort8 b);
float4 __cmpy_ext(cfloat a, cfloat b);
float8 __cmpy_ext(cfloat2 a, cfloat2 b);
float16 __cmpy_ext(cfloat4 a, cfloat4 b);
cshort __cmpy_fx(cshort a, cshort b);
cshort2 __cmpy_fx(cshort2 a, cshort2 b);
cshort4 __cmpy_fx(cshort4 a, cshort4 b);
cshort8 __cmpy_fx(cshort8 a, cshort8 b);
cshort16 __cmpy_fx(cshort16 a, cshort16 b);
cint __cmpy_fx(cint a, cint b);
cint2 __cmpy_fx(cint2 a, cint2 b);
cint4 __cmpy_fx(cint4 a, cint4 b);
cint8 __cmpy_fx(cint8 a, cint8 b);
cshort __cmpyr_fx(cshort a, cshort b);
cshort2 __cmpyr_fx(cshort2 a, cshort2 b);
cshort4 __cmpyr_fx(cshort4 a, cshort4 b);
cshort8 __cmpyr_fx(cshort8 a, cshort8 b);
cshort16 __cmpyr_fx(cshort16 a, cshort16 b);
__vpred __compress_set_bits_left(__vpred a);
__vpred __compress_set_bits_right(__vpred a);
__vpred __compressl_pp(__vpred a);
__vpred __compressr_pp(__vpred a);
cint2 __conj_cmatmpy_ext(cshort2 a, cshort4 b);
cint4 __conj_cmatmpy_ext(cshort4 a, cshort8 b);
cint8 __conj_cmatmpy_ext(cshort8 a, cshort16 b);
cshort2 __conj_cmatmpy_fx(cshort2 a, cshort4 b);
cshort4 __conj_cmatmpy_fx(cshort4 a, cshort8 b);
cshort8 __conj_cmatmpy_fx(cshort8 a, cshort16 b);
cshort __crot270(cshort a);
cshort2 __crot270(cshort2 a);
cshort4 __crot270(cshort4 a);
cshort8 __crot270(cshort8 a);
cshort16 __crot270(cshort16 a);
cfloat __crot270(cfloat a);
cfloat2 __crot270(cfloat2 a);
cfloat4 __crot270(cfloat4 a);
cfloat8 __crot270(cfloat8 a);
cint __crot270(cint a);
cint2 __crot270(cint2 a);
cint4 __crot270(cint4 a);
cint8 __crot270(cint8 a);
cshort __crot90(cshort a);
cshort2 __crot90(cshort2 a);
cshort4 __crot90(cshort4 a);
cshort8 __crot90(cshort8 a);
cshort16 __crot90(cshort16 a);
cfloat __crot90(cfloat a);
cfloat2 __crot90(cfloat2 a);
cfloat4 __crot90(cfloat4 a);
cfloat8 __crot90(cfloat8 a);
cint __crot90(cint a);
cint2 __crot90(cint2 a);
cint4 __crot90(cint4 a);
cint8 __crot90(cint8 a);
int64_t __deal_bit(int64_t a);
long2 __deal_bit(long2 a);
long4 __deal_bit(long4 a);
long8 __deal_bit(long8 a);
uint64_t __deal_bit(uint64_t a);
ulong2 __deal_bit(ulong2 a);
ulong4 __deal_bit(ulong4 a);
ulong8 __deal_bit(ulong8 a);
int32_t __deal_bit(int32_t a);
int2 __deal_bit(int2 a);
int4 __deal_bit(int4 a);
int8 __deal_bit(int8 a);
int16 __deal_bit(int16 a);
uint32_t __deal_bit(uint32_t a);
uint2 __deal_bit(uint2 a);
uint4 __deal_bit(uint4 a);
uint8 __deal_bit(uint8 a);
uint16 __deal_bit(uint16 a);
uchar64 __deal_stride2(uchar64 a);
char64 __deal_stride2(char64 a);
ushort32 __deal_stride2(ushort32 a);
short32 __deal_stride2(short32 a);
uint16 __deal_stride2(uint16 a);
int16 __deal_stride2(int16 a);
uchar64 __deal_stride4(uchar64 a);
char64 __deal_stride4(char64 a);
ushort32 __deal_stride4(ushort32 a);
short32 __deal_stride4(short32 a);
__vpred __decimate_char(__vpred a, __vpred b);
__vpred __decimate_int(__vpred a, __vpred b);
__vpred __decimate_long(__vpred a, __vpred b);
__vpred __decimate_short(__vpred a, __vpred b);
__vpred __decimateb_ppp(__vpred a, __vpred b);
__vpred __decimated_ppp(__vpred a, __vpred b);
__vpred __decimateh_ppp(__vpred a, __vpred b);
__vpred __decimatew_ppp(__vpred a, __vpred b);
int64_t __divdw_drd(int64_t a, int32_t b);
uint64_t __divudw_drd(uint64_t a, uint32_t b);
uint32_t __divuw_rrr(uint32_t a, uint32_t b);
int32_t __divw_rrr(int32_t a, int32_t b);
long8 __dot_posneg128_mask(ushort32 a, ushort8 b, int16 c);
ulong8 __dot_posneg128_mask_ext(ushort32 a, ushort8 b, uint16 c);
int16 __dot_posneg256_mask(ushort32 a, ushort16 b, short16 c);
int8 __dot_posneg256_mask(uint8 a, uint8 b, short32 c);
uint16 __dot_posneg256_mask(ushort32 a, ushort16 b, ushort16 c);
uint8 __dot_posneg256_mask(uint8 a, uint8 b, ushort32 c);
short32 __dot_posneg512_mask(ushort32 a, ushort32 b, char16 c);
short16 __dot_posneg512_mask(uint16 a, uint16 b, char32 c);
ushort16 __dot_posneg512_mask(uint16 a, uint16 b, uchar32 c);
int16 __dot_posneg512_mask_ext(uint16 a, uint16 b, char32 c);
uint16 __dot_posneg512_mask_ext(uint16 a, uint16 b, uchar32 c);
cint __dotp2(cshort2 a, cshort2 b);
cint2 __dotp2(cshort4 a, cshort4 b);
cint4 __dotp2(cshort8 a, cshort8 b);
cint8 __dotp2(cshort16 a, cshort16 b);
int32_t __dotp2(short2 a, short2 b);
int2 __dotp2(short4 a, short4 b);
int4 __dotp2(short8 a, short8 b);
int8 __dotp2(short16 a, short16 b);
int16 __dotp2(short32 a, short32 b);
int16_t __dotp2(char2 a, uchar2 b);
short2 __dotp2(char4 a, uchar4 b);
short4 __dotp2(char8 a, uchar8 b);
short8 __dotp2(char16 a, uchar16 b);
short16 __dotp2(char32 a, uchar32 b);
short32 __dotp2(char64 a, uchar64 b);
int32_t __dotp2(short2 a, ushort2 b);
int2 __dotp2(short4 a, ushort4 b);
int4 __dotp2(short8 a, ushort8 b);
int8 __dotp2(short16 a, ushort16 b);
int16 __dotp2(short32 a, ushort32 b);
uint16_t __dotp2(uchar2 a, uchar2 b);
ushort2 __dotp2(uchar4 a, uchar4 b);
ushort4 __dotp2(uchar8 a, uchar8 b);
ushort8 __dotp2(uchar16 a, uchar16 b);
ushort16 __dotp2(uchar32 a, uchar32 b);
ushort32 __dotp2(uchar64 a, uchar64 b);
uint32_t __dotp2(ushort2 a, ushort2 b);
uint2 __dotp2(ushort4 a, ushort4 b);
uint4 __dotp2(ushort8 a, ushort8 b);
uint8 __dotp2(ushort16 a, ushort16 b);
uint16 __dotp2(ushort32 a, ushort32 b);
int64_t __dotp2(int2 a, int2 b);
long2 __dotp2(int4 a, int4 b);
long4 __dotp2(int8 a, int8 b);
long8 __dotp2(int16 a, int16 b);
cint __dotp2_conj(cshort2 a, cshort2 b);
cint2 __dotp2_conj(cshort4 a, cshort4 b);
cint4 __dotp2_conj(cshort8 a, cshort8 b);
cint8 __dotp2_conj(cshort16 a, cshort16 b);
int64_t __dotp2_cross(int2 a, int2 b);
long2 __dotp2_cross(int4 a, int4 b);
long4 __dotp2_cross(int8 a, int8 b);
long8 __dotp2_cross(int16 a, int16 b);
int64_t __dotp2_cross_negate(int2 a, int2 b);
long2 __dotp2_cross_negate(int4 a, int4 b);
long4 __dotp2_cross_negate(int8 a, int8 b);
long8 __dotp2_cross_negate(int16 a, int16 b);
int64_t __dotp2_ext(short2 a, short2 b);
long2 __dotp2_ext(short4 a, short4 b);
long4 __dotp2_ext(short8 a, short8 b);
long8 __dotp2_ext(short16 a, short16 b);
int64_t __dotp2_ext(short2 a, ushort2 b);
long2 __dotp2_ext(short4 a, ushort4 b);
long4 __dotp2_ext(short8 a, ushort8 b);
long8 __dotp2_ext(short16 a, ushort16 b);
uint64_t __dotp2_ext(ushort2 a, ushort2 b);
ulong2 __dotp2_ext(ushort4 a, ushort4 b);
ulong4 __dotp2_ext(ushort8 a, ushort8 b);
ulong8 __dotp2_ext(ushort16 a, ushort16 b);
int32_t __dotp2_fx_ext(short2 a, ushort2 b);
int64_t __dotp2_negate(int2 a, int2 b);
long2 __dotp2_negate(int4 a, int4 b);
long4 __dotp2_negate(int8 a, int8 b);
long8 __dotp2_negate(int16 a, int16 b);
int32_t __dotp4(short4 a, short4 b);
int2 __dotp4(short8 a, short8 b);
int4 __dotp4(short16 a, short16 b);
int8 __dotp4(short32 a, short32 b);
int32_t __dotp4(short4 a, ushort4 b);
int2 __dotp4(short8 a, ushort8 b);
int4 __dotp4(short16 a, ushort16 b);
int8 __dotp4(short32 a, ushort32 b);
int64_t __dotp4_ext(short4 a, short4 b);
long2 __dotp4_ext(short8 a, short8 b);
long4 __dotp4_ext(short16 a, short16 b);
long8 __dotp4_ext(short32 a, short32 b);
int32_t __dotp4_ext(char4 a, uchar4 b);
int2 __dotp4_ext(char8 a, uchar8 b);
int4 __dotp4_ext(char16 a, uchar16 b);
int8 __dotp4_ext(char32 a, uchar32 b);
int16 __dotp4_ext(char64 a, uchar64 b);
int64_t __dotp4_ext(short4 a, ushort4 b);
long2 __dotp4_ext(short8 a, ushort8 b);
long4 __dotp4_ext(short16 a, ushort16 b);
long8 __dotp4_ext(short32 a, ushort32 b);
uint32_t __dotp4_ext(uchar4 a, uchar4 b);
uint2 __dotp4_ext(uchar8 a, uchar8 b);
uint4 __dotp4_ext(uchar16 a, uchar16 b);
uint8 __dotp4_ext(uchar32 a, uchar32 b);
uint16 __dotp4_ext(uchar64 a, uchar64 b);
uint64_t __dotp4_ext(ushort4 a, ushort4 b);
ulong2 __dotp4_ext(ushort8 a, ushort8 b);
ulong4 __dotp4_ext(ushort16 a, ushort16 b);
ulong8 __dotp4_ext(ushort32 a, ushort32 b);
int2 __dotp8_ext(char8 a, uchar8 b);
int4 __dotp8_ext(char16 a, uchar16 b);
int8 __dotp8_ext(char32 a, uchar32 b);
int16 __dotp8_ext(char64 a, uchar64 b);
float2 __double_to_float(double a);
float4 __double_to_float(double2 a);
float8 __double_to_float(double4 a);
float16 __double_to_float(double8 a);
int2 __double_to_int(double a);
int4 __double_to_int(double2 a);
int8 __double_to_int(double4 a);
int16 __double_to_int(double8 a);
int2 __double_to_int_rtz(double a);
int4 __double_to_int_rtz(double2 a);
int8 __double_to_int_rtz(double4 a);
int16 __double_to_int_rtz(double8 a);
long4 __dual_horizontal_add_skip1(int16 a, int16 b);
clong2 __dual_horizontal_add_skip1(cint8 a, cint8 b);
ulong4 __dual_horizontal_add_skip1(uint16 a, uint16 b);
short16 __dual_sort_lo_asc_hi_asc(short16 a);
short32 __dual_sort_lo_asc_hi_asc(short32 a);
ushort16 __dual_sort_lo_asc_hi_asc(ushort16 a);
ushort32 __dual_sort_lo_asc_hi_asc(ushort32 a);
uchar32 __dual_sort_lo_asc_hi_asc_perm(short16 a);
uchar64 __dual_sort_lo_asc_hi_asc_perm(short32 a);
uchar32 __dual_sort_lo_asc_hi_asc_perm(ushort16 a);
uchar64 __dual_sort_lo_asc_hi_asc_perm(ushort32 a);
short32 __dual_sort_lo_asc_hi_desc(short32 a);
ushort32 __dual_sort_lo_asc_hi_desc(ushort32 a);
uchar64 __dual_sort_lo_asc_hi_desc_perm(short32 a);
uchar64 __dual_sort_lo_asc_hi_desc_perm(ushort32 a);
short32 __dual_sort_lo_desc_hi_asc(short32 a);
ushort32 __dual_sort_lo_desc_hi_asc(ushort32 a);
uchar64 __dual_sort_lo_desc_hi_asc_perm(short32 a);
uchar64 __dual_sort_lo_desc_hi_asc_perm(ushort32 a);
short16 __dual_sort_lo_desc_hi_desc(short16 a);
short32 __dual_sort_lo_desc_hi_desc(short32 a);
ushort16 __dual_sort_lo_desc_hi_desc(ushort16 a);
ushort32 __dual_sort_lo_desc_hi_desc(ushort32 a);
uchar32 __dual_sort_lo_desc_hi_desc_perm(short16 a);
uchar64 __dual_sort_lo_desc_hi_desc_perm(short32 a);
uchar32 __dual_sort_lo_desc_hi_desc_perm(ushort16 a);
uchar64 __dual_sort_lo_desc_hi_desc_perm(ushort32 a);
char64 __duplicate(char4 a);
cchar32 __duplicate(cchar2 a);
uchar64 __duplicate(uchar4 a);
short32 __duplicate(short2 a);
cshort16 __duplicate(cshort a);
ushort32 __duplicate(ushort2 a);
char64 __duplicate(char32 a);
cchar32 __duplicate(cchar16 a);
uchar64 __duplicate(uchar32 a);
long8 __duplicate(long4 a);
clong4 __duplicate(clong2 a);
ulong8 __duplicate(ulong4 a);
short32 __duplicate(short16 a);
cshort16 __duplicate(cshort8 a);
ushort32 __duplicate(ushort16 a);
int16 __duplicate(int8 a);
cint8 __duplicate(cint4 a);
uint16 __duplicate(uint8 a);
char64 __duplicate(char2 a);
cchar32 __duplicate(cchar a);
uchar64 __duplicate(uchar2 a);
char64 __duplicate(char16 a);
cchar32 __duplicate(cchar8 a);
uchar64 __duplicate(uchar16 a);
long8 __duplicate(long2 a);
clong4 __duplicate(clong a);
ulong8 __duplicate(ulong2 a);
short32 __duplicate(short8 a);
cshort16 __duplicate(cshort4 a);
ushort32 __duplicate(ushort8 a);
int16 __duplicate(int4 a);
cint8 __duplicate(cint2 a);
uint16 __duplicate(uint4 a);
char64 __duplicate(char8 a);
cchar32 __duplicate(cchar4 a);
uchar64 __duplicate(uchar8 a);
short32 __duplicate(short4 a);
cshort16 __duplicate(cshort2 a);
ushort32 __duplicate(ushort4 a);
int16 __duplicate(int2 a);
cint8 __duplicate(cint a);
uint16 __duplicate(uint2 a);
char64 __duplicate(int8_t a);
uchar64 __duplicate(uint8_t a);
long8 __duplicate(int64_t a);
ulong8 __duplicate(uint64_t a);
short32 __duplicate(int16_t a);
ushort32 __duplicate(uint16_t a);
int16 __duplicate(int32_t a);
uint16 __duplicate(uint32_t a);
__vpred __duplicate_pred_high_char(__vpred a);
__vpred __duplicate_pred_high_int(__vpred a);
__vpred __duplicate_pred_high_long(__vpred a);
__vpred __duplicate_pred_high_short(__vpred a);
__vpred __duplicate_pred_low_char(__vpred a);
__vpred __duplicate_pred_low_int(__vpred a);
__vpred __duplicate_pred_low_long(__vpred a);
__vpred __duplicate_pred_low_short(__vpred a);
char64 __expand(__vpred a);
uchar8 __expand_lsb_pack_char(uint8_t a);
char8 __expand_lsb_pack_char(int8_t a);
ushort4 __expand_lsb_pack_short(uint8_t a);
short4 __expand_lsb_pack_short(int8_t a);
int64_t __ext_dkkd(char8 a, uint8_t b, uint8_t c);
int64_t __ext_dkkd(short4 a, uint8_t b, uint8_t c);
int64_t __ext_dkkd(int2 a, uint8_t b, uint8_t c);
int64_t __ext_dkkd(int64_t a, uint8_t b, uint8_t c);
uint64_t __extu_dkkd(uchar8 a, uint8_t b, uint8_t c);
uint64_t __extu_dkkd(ushort4 a, uint8_t b, uint8_t c);
uint64_t __extu_dkkd(uint2 a, uint8_t b, uint8_t c);
uint64_t __extu_dkkd(uint64_t a, uint8_t b, uint8_t c);
uint64_t __extuv_vkkkd(ulong8 a, uint8_t b, uint8_t c, uint8_t d);
int64_t __extv_vkkkd(long8 a, uint8_t b, uint8_t c, uint8_t d);
int32_t __float_to_int(float a);
int2 __float_to_int(float2 a);
int4 __float_to_int(float4 a);
int8 __float_to_int(float8 a);
int16 __float_to_int(float16 a);
int32_t __float_to_int_rtz(float a);
int2 __float_to_int_rtz(float2 a);
int4 __float_to_int_rtz(float4 a);
int8 __float_to_int_rtz(float8 a);
int16 __float_to_int_rtz(float16 a);
short2 __float_to_short(float a);
short4 __float_to_short(float2 a);
short8 __float_to_short(float4 a);
short16 __float_to_short(float8 a);
short32 __float_to_short(float16 a);
char64 __gather_set_bits(__vpred a, char64 b);
char64 __gather_unset_bits(__vpred a, char64 b);
uint8_t __gmpy(uint8_t a, uint8_t b);
uchar2 __gmpy(uchar2 a, uchar2 b);
uchar4 __gmpy(uchar4 a, uchar4 b);
uchar8 __gmpy(uchar8 a, uchar8 b);
uchar16 __gmpy(uchar16 a, uchar16 b);
uchar32 __gmpy(uchar32 a, uchar32 b);
uchar64 __gmpy(uchar64 a, uchar64 b);
uint32_t __gmpy(uint32_t a, uint32_t b);
uint2 __gmpy(uint2 a, uint2 b);
uint4 __gmpy(uint4 a, uint4 b);
uint8 __gmpy(uint8 a, uint8 b);
uint16 __gmpy(uint16 a, uint16 b);
int8_t __hadd(int8_t a, int8_t b);
char2 __hadd(char2 a, char2 b);
char4 __hadd(char4 a, char4 b);
char8 __hadd(char8 a, char8 b);
char16 __hadd(char16 a, char16 b);
char32 __hadd(char32 a, char32 b);
char64 __hadd(char64 a, char64 b);
int64_t __hadd(int64_t a, int64_t b);
long2 __hadd(long2 a, long2 b);
long4 __hadd(long4 a, long4 b);
long8 __hadd(long8 a, long8 b);
int16_t __hadd(int16_t a, int16_t b);
short2 __hadd(short2 a, short2 b);
short4 __hadd(short4 a, short4 b);
short8 __hadd(short8 a, short8 b);
short16 __hadd(short16 a, short16 b);
short32 __hadd(short32 a, short32 b);
uint8_t __hadd(uint8_t a, uint8_t b);
uchar2 __hadd(uchar2 a, uchar2 b);
uchar4 __hadd(uchar4 a, uchar4 b);
uchar8 __hadd(uchar8 a, uchar8 b);
uchar16 __hadd(uchar16 a, uchar16 b);
uchar32 __hadd(uchar32 a, uchar32 b);
uchar64 __hadd(uchar64 a, uchar64 b);
uint64_t __hadd(uint64_t a, uint64_t b);
ulong2 __hadd(ulong2 a, ulong2 b);
ulong4 __hadd(ulong4 a, ulong4 b);
ulong8 __hadd(ulong8 a, ulong8 b);
uint16_t __hadd(uint16_t a, uint16_t b);
ushort2 __hadd(ushort2 a, ushort2 b);
ushort4 __hadd(ushort4 a, ushort4 b);
ushort8 __hadd(ushort8 a, ushort8 b);
ushort16 __hadd(ushort16 a, ushort16 b);
ushort32 __hadd(ushort32 a, ushort32 b);
uint32_t __hadd(uint32_t a, uint32_t b);
uint2 __hadd(uint2 a, uint2 b);
uint4 __hadd(uint4 a, uint4 b);
uint8 __hadd(uint8 a, uint8 b);
uint16 __hadd(uint16 a, uint16 b);
int32_t __hadd(int32_t a, int32_t b);
int2 __hadd(int2 a, int2 b);
int4 __hadd(int4 a, int4 b);
int8 __hadd(int8 a, int8 b);
int16 __hadd(int16 a, int16 b);
int16_t __high_char_to_short(char2 a);
short2 __high_char_to_short(char4 a);
short4 __high_char_to_short(char8 a);
short8 __high_char_to_short(char16 a);
short16 __high_char_to_short(char32 a);
short32 __high_char_to_short(char64 a);
double __high_float_to_double(float2 a);
double2 __high_float_to_double(float4 a);
double4 __high_float_to_double(float8 a);
double8 __high_float_to_double(float16 a);
float2 __high_half_int_to_float(short4 a);
float4 __high_half_int_to_float(short8 a);
float8 __high_half_int_to_float(short16 a);
float16 __high_half_int_to_float(short32 a);
float2 __high_half_int_to_float(ushort4 a);
float4 __high_half_int_to_float(ushort8 a);
float8 __high_half_int_to_float(ushort16 a);
float16 __high_half_int_to_float(ushort32 a);
double __high_int_to_double(int2 a);
double2 __high_int_to_double(int4 a);
double4 __high_int_to_double(int8 a);
double8 __high_int_to_double(int16 a);
double __high_int_to_double(uint2 a);
double2 __high_int_to_double(uint4 a);
double4 __high_int_to_double(uint8 a);
double8 __high_int_to_double(uint16 a);
int64_t __high_int_to_long(int2 a);
long2 __high_int_to_long(int4 a);
long4 __high_int_to_long(int8 a);
long8 __high_int_to_long(int16 a);
int32_t __high_short_to_int(short2 a);
int2 __high_short_to_int(short4 a);
int4 __high_short_to_int(short8 a);
int8 __high_short_to_int(short16 a);
int16 __high_short_to_int(short32 a);
uint16_t __high_uchar_to_ushort(uchar2 a);
ushort2 __high_uchar_to_ushort(uchar4 a);
ushort4 __high_uchar_to_ushort(uchar8 a);
ushort8 __high_uchar_to_ushort(uchar16 a);
ushort16 __high_uchar_to_ushort(uchar32 a);
ushort32 __high_uchar_to_ushort(uchar64 a);
uint64_t __high_uint_to_ulong(uint2 a);
ulong2 __high_uint_to_ulong(uint4 a);
ulong4 __high_uint_to_ulong(uint8 a);
ulong8 __high_uint_to_ulong(uint16 a);
uint32_t __high_ushort_to_uint(ushort2 a);
uint2 __high_ushort_to_uint(ushort4 a);
uint4 __high_ushort_to_uint(ushort8 a);
uint8 __high_ushort_to_uint(ushort16 a);
uint16 __high_ushort_to_uint(ushort32 a);
int64_t __horizontal_add(int16 a);
int64_t __horizontal_add(short32 a);
int64_t __horizontal_add(char64 a);
int64_t __horizontal_add(long8 a);
uint64_t __horizontal_add(uint16 a);
uint64_t __horizontal_add(ushort32 a);
uint64_t __horizontal_add(uchar64 a);
uint64_t __horizontal_add(ulong8 a);
int2 __horizontal_add_skip1(short32 a);
cint __horizontal_add_skip1(cshort16 a);
long2 __horizontal_add_skip1(int16 a);
clong __horizontal_add_skip1(cint8 a);
uint2 __horizontal_add_skip1(ushort32 a);
ulong2 __horizontal_add_skip1(uint16 a);
int32_t __horizontal_xor(int16 a);
int16_t __horizontal_xor(short32 a);
int16_t __horizontal_xor(char64 a);
int64_t __horizontal_xor(long8 a);
int64_t __int40_to_int_sat(int64_t a);
long2 __int40_to_int_sat(long2 a);
long4 __int40_to_int_sat(long4 a);
long8 __int40_to_int_sat(long8 a);
float __int_to_float(int32_t a);
float2 __int_to_float(int2 a);
float4 __int_to_float(int4 a);
float8 __int_to_float(int8 a);
float16 __int_to_float(int16 a);
float __int_to_float(uint32_t a);
float2 __int_to_float(uint2 a);
float4 __int_to_float(uint4 a);
float8 __int_to_float(uint8 a);
float16 __int_to_float(uint16 a);
int32_t __int_to_short_sat(int32_t a);
int2 __int_to_short_sat(int2 a);
int4 __int_to_short_sat(int4 a);
int8 __int_to_short_sat(int8 a);
int16 __int_to_short_sat(int16 a);
int32_t __landd_ddr(int64_t a, int64_t b);
int32_t __landnd_ddr(int64_t a, int64_t b);
uint8_t __leftmost_bit_detect(uint8_t a, uint8_t b);
uchar2 __leftmost_bit_detect(uchar2 a, uchar2 b);
uchar4 __leftmost_bit_detect(uchar4 a, uchar4 b);
uchar8 __leftmost_bit_detect(uchar8 a, uchar8 b);
uchar16 __leftmost_bit_detect(uchar16 a, uchar16 b);
uchar32 __leftmost_bit_detect(uchar32 a, uchar32 b);
uchar64 __leftmost_bit_detect(uchar64 a, uchar64 b);
uint64_t __leftmost_bit_detect(uint64_t a, uint64_t b);
ulong2 __leftmost_bit_detect(ulong2 a, ulong2 b);
ulong4 __leftmost_bit_detect(ulong4 a, ulong4 b);
ulong8 __leftmost_bit_detect(ulong8 a, ulong8 b);
uint16_t __leftmost_bit_detect(uint16_t a, uint16_t b);
ushort2 __leftmost_bit_detect(ushort2 a, ushort2 b);
ushort4 __leftmost_bit_detect(ushort4 a, ushort4 b);
ushort8 __leftmost_bit_detect(ushort8 a, ushort8 b);
ushort16 __leftmost_bit_detect(ushort16 a, ushort16 b);
ushort32 __leftmost_bit_detect(ushort32 a, ushort32 b);
uint32_t __leftmost_bit_detect(uint32_t a, uint32_t b);
uint2 __leftmost_bit_detect(uint2 a, uint2 b);
uint4 __leftmost_bit_detect(uint4 a, uint4 b);
uint8 __leftmost_bit_detect(uint8 a, uint8 b);
uint16 __leftmost_bit_detect(uint16 a, uint16 b);
uint8_t __leftmost_bit_detect_one(uint8_t a);
uchar2 __leftmost_bit_detect_one(uchar2 a);
uchar4 __leftmost_bit_detect_one(uchar4 a);
uchar8 __leftmost_bit_detect_one(uchar8 a);
uchar16 __leftmost_bit_detect_one(uchar16 a);
uchar32 __leftmost_bit_detect_one(uchar32 a);
uchar64 __leftmost_bit_detect_one(uchar64 a);
uint64_t __leftmost_bit_detect_one(uint64_t a);
ulong2 __leftmost_bit_detect_one(ulong2 a);
ulong4 __leftmost_bit_detect_one(ulong4 a);
ulong8 __leftmost_bit_detect_one(ulong8 a);
uint16_t __leftmost_bit_detect_one(uint16_t a);
ushort2 __leftmost_bit_detect_one(ushort2 a);
ushort4 __leftmost_bit_detect_one(ushort4 a);
ushort8 __leftmost_bit_detect_one(ushort8 a);
ushort16 __leftmost_bit_detect_one(ushort16 a);
ushort32 __leftmost_bit_detect_one(ushort32 a);
uint32_t __leftmost_bit_detect_one(uint32_t a);
uint2 __leftmost_bit_detect_one(uint2 a);
uint4 __leftmost_bit_detect_one(uint4 a);
uint8 __leftmost_bit_detect_one(uint8 a);
uint16 __leftmost_bit_detect_one(uint16 a);
uint8_t __leftmost_bit_detect_zero(uint8_t a);
uchar2 __leftmost_bit_detect_zero(uchar2 a);
uchar4 __leftmost_bit_detect_zero(uchar4 a);
uchar8 __leftmost_bit_detect_zero(uchar8 a);
uchar16 __leftmost_bit_detect_zero(uchar16 a);
uchar32 __leftmost_bit_detect_zero(uchar32 a);
uchar64 __leftmost_bit_detect_zero(uchar64 a);
uint64_t __leftmost_bit_detect_zero(uint64_t a);
ulong2 __leftmost_bit_detect_zero(ulong2 a);
ulong4 __leftmost_bit_detect_zero(ulong4 a);
ulong8 __leftmost_bit_detect_zero(ulong8 a);
uint16_t __leftmost_bit_detect_zero(uint16_t a);
ushort2 __leftmost_bit_detect_zero(ushort2 a);
ushort4 __leftmost_bit_detect_zero(ushort4 a);
ushort8 __leftmost_bit_detect_zero(ushort8 a);
ushort16 __leftmost_bit_detect_zero(ushort16 a);
ushort32 __leftmost_bit_detect_zero(ushort32 a);
uint32_t __leftmost_bit_detect_zero(uint32_t a);
uint2 __leftmost_bit_detect_zero(uint2 a);
uint4 __leftmost_bit_detect_zero(uint4 a);
uint8 __leftmost_bit_detect_zero(uint8 a);
uint16 __leftmost_bit_detect_zero(uint16 a);
int32_t __logical_and(int64_t a, int64_t b);
int32_t __logical_andn(int64_t a, int64_t b);
int32_t __logical_or(int64_t a, int64_t b);
int64_t __long_to_int40_sat(int64_t a);
long2 __long_to_int40_sat(long2 a);
long4 __long_to_int40_sat(long4 a);
long8 __long_to_int40_sat(long8 a);
int64_t __long_to_int_sat(int64_t a);
long2 __long_to_int_sat(long2 a);
long4 __long_to_int_sat(long4 a);
long8 __long_to_int_sat(long8 a);
int32_t __lord_ddr(int64_t a, int64_t b);
int16_t __low_char_to_short(char2 a);
short2 __low_char_to_short(char4 a);
short4 __low_char_to_short(char8 a);
short8 __low_char_to_short(char16 a);
short16 __low_char_to_short(char32 a);
short32 __low_char_to_short(char64 a);
double __low_float_to_double(float2 a);
double2 __low_float_to_double(float4 a);
double4 __low_float_to_double(float8 a);
double8 __low_float_to_double(float16 a);
float2 __low_half_int_to_float(short4 a);
float4 __low_half_int_to_float(short8 a);
float8 __low_half_int_to_float(short16 a);
float16 __low_half_int_to_float(short32 a);
float2 __low_half_int_to_float(ushort4 a);
float4 __low_half_int_to_float(ushort8 a);
float8 __low_half_int_to_float(ushort16 a);
float16 __low_half_int_to_float(ushort32 a);
double __low_int_to_double(int2 a);
double2 __low_int_to_double(int4 a);
double4 __low_int_to_double(int8 a);
double8 __low_int_to_double(int16 a);
double __low_int_to_double(uint2 a);
double2 __low_int_to_double(uint4 a);
double4 __low_int_to_double(uint8 a);
double8 __low_int_to_double(uint16 a);
int64_t __low_int_to_long(int2 a);
long2 __low_int_to_long(int4 a);
long4 __low_int_to_long(int8 a);
long8 __low_int_to_long(int16 a);
int32_t __low_short_to_int(short2 a);
int2 __low_short_to_int(short4 a);
int4 __low_short_to_int(short8 a);
int8 __low_short_to_int(short16 a);
int16 __low_short_to_int(short32 a);
uint16_t __low_uchar_to_ushort(uchar2 a);
ushort2 __low_uchar_to_ushort(uchar4 a);
ushort4 __low_uchar_to_ushort(uchar8 a);
ushort8 __low_uchar_to_ushort(uchar16 a);
ushort16 __low_uchar_to_ushort(uchar32 a);
ushort32 __low_uchar_to_ushort(uchar64 a);
uint64_t __low_uint_to_ulong(uint2 a);
ulong2 __low_uint_to_ulong(uint4 a);
ulong4 __low_uint_to_ulong(uint8 a);
ulong8 __low_uint_to_ulong(uint16 a);
uint32_t __low_ushort_to_uint(ushort2 a);
uint2 __low_ushort_to_uint(ushort4 a);
uint4 __low_ushort_to_uint(ushort8 a);
uint8 __low_ushort_to_uint(ushort16 a);
uint16 __low_ushort_to_uint(ushort32 a);
__vpred __mask_char(uint32_t a);
__vpred __mask_char(uint8_t a);
__vpred __mask_int(uint32_t a);
__vpred __mask_int(uint8_t a);
__vpred __mask_long(uint32_t a);
__vpred __mask_long(uint8_t a);
__vpred __mask_short(uint32_t a);
__vpred __mask_short(uint8_t a);
__vpred __maskb_kp(uint8_t a);
__vpred __maskb_rp(uint32_t a);
__vpred __maskd_kp(uint8_t a);
__vpred __maskd_rp(uint32_t a);
__vpred __maskh_kp(uint8_t a);
__vpred __maskh_rp(uint32_t a);
__vpred __maskw_kp(uint8_t a);
__vpred __maskw_rp(uint32_t a);
int16 __matmpy(__SE_REG a, __SE_REG b);
int16 __matmpy_u2s(__SE_REG a, __SE_REG b);
int8_t __max(int8_t a, int8_t b);
char2 __max(char2 a, char2 b);
char4 __max(char4 a, char4 b);
char8 __max(char8 a, char8 b);
char16 __max(char16 a, char16 b);
char32 __max(char32 a, char32 b);
char64 __max(char64 a, char64 b);
int64_t __max(int64_t a, int64_t b);
long2 __max(long2 a, long2 b);
long4 __max(long4 a, long4 b);
long8 __max(long8 a, long8 b);
double __max(double a, double b);
double2 __max(double2 a, double2 b);
double4 __max(double4 a, double4 b);
double8 __max(double8 a, double8 b);
int16_t __max(int16_t a, int16_t b);
short2 __max(short2 a, short2 b);
short4 __max(short4 a, short4 b);
short8 __max(short8 a, short8 b);
short16 __max(short16 a, short16 b);
short32 __max(short32 a, short32 b);
float __max(float a, float b);
float2 __max(float2 a, float2 b);
float4 __max(float4 a, float4 b);
float8 __max(float8 a, float8 b);
float16 __max(float16 a, float16 b);
uint8_t __max(uint8_t a, uint8_t b);
uchar2 __max(uchar2 a, uchar2 b);
uchar4 __max(uchar4 a, uchar4 b);
uchar8 __max(uchar8 a, uchar8 b);
uchar16 __max(uchar16 a, uchar16 b);
uchar32 __max(uchar32 a, uchar32 b);
uchar64 __max(uchar64 a, uchar64 b);
uint64_t __max(uint64_t a, uint64_t b);
ulong2 __max(ulong2 a, ulong2 b);
ulong4 __max(ulong4 a, ulong4 b);
ulong8 __max(ulong8 a, ulong8 b);
uint16_t __max(uint16_t a, uint16_t b);
ushort2 __max(ushort2 a, ushort2 b);
ushort4 __max(ushort4 a, ushort4 b);
ushort8 __max(ushort8 a, ushort8 b);
ushort16 __max(ushort16 a, ushort16 b);
ushort32 __max(ushort32 a, ushort32 b);
uint32_t __max(uint32_t a, uint32_t b);
uint2 __max(uint2 a, uint2 b);
uint4 __max(uint4 a, uint4 b);
uint8 __max(uint8 a, uint8 b);
uint16 __max(uint16 a, uint16 b);
int32_t __max(int32_t a, int32_t b);
int2 __max(int2 a, int2 b);
int4 __max(int4 a, int4 b);
int8 __max(int8 a, int8 b);
int16 __max(int16 a, int16 b);
int8_t __max_circ(int8_t a, int8_t b);
char2 __max_circ(char2 a, char2 b);
char4 __max_circ(char4 a, char4 b);
char8 __max_circ(char8 a, char8 b);
char16 __max_circ(char16 a, char16 b);
char32 __max_circ(char32 a, char32 b);
char64 __max_circ(char64 a, char64 b);
int16_t __max_circ(int16_t a, int16_t b);
short2 __max_circ(short2 a, short2 b);
short4 __max_circ(short4 a, short4 b);
short8 __max_circ(short8 a, short8 b);
short16 __max_circ(short16 a, short16 b);
short32 __max_circ(short32 a, short32 b);
void __max_circ_pred(int8_t a, int8_t& b, __vpred& c);
template <size_t DEPTH>
void __max_circ_pred(char2 a, char2::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
template <size_t DEPTH>
void __max_circ_pred(char4 a, char4::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
template <size_t DEPTH>
void __max_circ_pred(char8 a, char8::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
template <size_t DEPTH>
void __max_circ_pred(char16 a, char16::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
template <size_t DEPTH>
void __max_circ_pred(char32 a, char32::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
template <size_t DEPTH>
void __max_circ_pred(char64 a, char64::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
void __max_circ_pred(int16_t a, int16_t& b, __vpred& c);
template <size_t DEPTH>
void __max_circ_pred(short2 a, short2::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
template <size_t DEPTH>
void __max_circ_pred(short4 a, short4::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
template <size_t DEPTH>
void __max_circ_pred(short8 a, short8::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
template <size_t DEPTH>
void __max_circ_pred(short16 a, short16::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
template <size_t DEPTH>
void __max_circ_pred(short32 a, short32::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
void __max_index(int8_t a, int8_t& b, __vpred& c);
template <size_t DEPTH>
void __max_index(char2 a, char2::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
template <size_t DEPTH>
void __max_index(char4 a, char4::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
template <size_t DEPTH>
void __max_index(char8 a, char8::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
template <size_t DEPTH>
void __max_index(char16 a, char16::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
template <size_t DEPTH>
void __max_index(char32 a, char32::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
template <size_t DEPTH>
void __max_index(char64 a, char64::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
void __max_index(int64_t a, int64_t& b, __vpred& c);
template <size_t DEPTH>
void __max_index(long2 a, long2::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
template <size_t DEPTH>
void __max_index(long4 a, long4::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
template <size_t DEPTH>
void __max_index(long8 a, long8::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
void __max_index(int16_t a, int16_t& b, __vpred& c);
template <size_t DEPTH>
void __max_index(short2 a, short2::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
template <size_t DEPTH>
void __max_index(short4 a, short4::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
template <size_t DEPTH>
void __max_index(short8 a, short8::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
template <size_t DEPTH>
void __max_index(short16 a, short16::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
template <size_t DEPTH>
void __max_index(short32 a, short32::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
void __max_index(int32_t a, int32_t& b, __vpred& c);
template <size_t DEPTH>
void __max_index(int2 a, int2::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
template <size_t DEPTH>
void __max_index(int4 a, int4::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
template <size_t DEPTH>
void __max_index(int8 a, int8::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
template <size_t DEPTH>
void __max_index(int16 a, int16::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
void __max_index(uint8_t a, uint8_t& b, __vpred& c);
template <size_t DEPTH>
void __max_index(uchar2 a, uchar2::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
template <size_t DEPTH>
void __max_index(uchar4 a, uchar4::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
template <size_t DEPTH>
void __max_index(uchar8 a, uchar8::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
template <size_t DEPTH>
void __max_index(uchar16 a, uchar16::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
template <size_t DEPTH>
void __max_index(uchar32 a, uchar32::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
template <size_t DEPTH>
void __max_index(uchar64 a, uchar64::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
void __max_index(uint64_t a, uint64_t& b, __vpred& c);
template <size_t DEPTH>
void __max_index(ulong2 a, ulong2::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
template <size_t DEPTH>
void __max_index(ulong4 a, ulong4::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
template <size_t DEPTH>
void __max_index(ulong8 a, ulong8::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
void __max_index(uint16_t a, uint16_t& b, __vpred& c);
template <size_t DEPTH>
void __max_index(ushort2 a, ushort2::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
template <size_t DEPTH>
void __max_index(ushort4 a, ushort4::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
template <size_t DEPTH>
void __max_index(ushort8 a, ushort8::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
template <size_t DEPTH>
void __max_index(ushort16 a, ushort16::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
template <size_t DEPTH>
void __max_index(ushort32 a, ushort32::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
void __max_index(uint32_t a, uint32_t& b, __vpred& c);
template <size_t DEPTH>
void __max_index(uint2 a, uint2::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
template <size_t DEPTH>
void __max_index(uint4 a, uint4::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
template <size_t DEPTH>
void __max_index(uint8 a, uint8::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
template <size_t DEPTH>
void __max_index(uint16 a, uint16::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
int8_t __min(int8_t a, int8_t b);
char2 __min(char2 a, char2 b);
char4 __min(char4 a, char4 b);
char8 __min(char8 a, char8 b);
char16 __min(char16 a, char16 b);
char32 __min(char32 a, char32 b);
char64 __min(char64 a, char64 b);
int64_t __min(int64_t a, int64_t b);
long2 __min(long2 a, long2 b);
long4 __min(long4 a, long4 b);
long8 __min(long8 a, long8 b);
double __min(double a, double b);
double2 __min(double2 a, double2 b);
double4 __min(double4 a, double4 b);
double8 __min(double8 a, double8 b);
int16_t __min(int16_t a, int16_t b);
short2 __min(short2 a, short2 b);
short4 __min(short4 a, short4 b);
short8 __min(short8 a, short8 b);
short16 __min(short16 a, short16 b);
short32 __min(short32 a, short32 b);
float __min(float a, float b);
float2 __min(float2 a, float2 b);
float4 __min(float4 a, float4 b);
float8 __min(float8 a, float8 b);
float16 __min(float16 a, float16 b);
uint8_t __min(uint8_t a, uint8_t b);
uchar2 __min(uchar2 a, uchar2 b);
uchar4 __min(uchar4 a, uchar4 b);
uchar8 __min(uchar8 a, uchar8 b);
uchar16 __min(uchar16 a, uchar16 b);
uchar32 __min(uchar32 a, uchar32 b);
uchar64 __min(uchar64 a, uchar64 b);
uint64_t __min(uint64_t a, uint64_t b);
ulong2 __min(ulong2 a, ulong2 b);
ulong4 __min(ulong4 a, ulong4 b);
ulong8 __min(ulong8 a, ulong8 b);
uint16_t __min(uint16_t a, uint16_t b);
ushort2 __min(ushort2 a, ushort2 b);
ushort4 __min(ushort4 a, ushort4 b);
ushort8 __min(ushort8 a, ushort8 b);
ushort16 __min(ushort16 a, ushort16 b);
ushort32 __min(ushort32 a, ushort32 b);
uint32_t __min(uint32_t a, uint32_t b);
uint2 __min(uint2 a, uint2 b);
uint4 __min(uint4 a, uint4 b);
uint8 __min(uint8 a, uint8 b);
uint16 __min(uint16 a, uint16 b);
int32_t __min(int32_t a, int32_t b);
int2 __min(int2 a, int2 b);
int4 __min(int4 a, int4 b);
int8 __min(int8 a, int8 b);
int16 __min(int16 a, int16 b);
void __min_index(int8_t a, int8_t& b, __vpred& c);
template <size_t DEPTH>
void __min_index(char2 a, char2::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
template <size_t DEPTH>
void __min_index(char4 a, char4::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
template <size_t DEPTH>
void __min_index(char8 a, char8::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
template <size_t DEPTH>
void __min_index(char16 a, char16::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
template <size_t DEPTH>
void __min_index(char32 a, char32::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
template <size_t DEPTH>
void __min_index(char64 a, char64::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
void __min_index(int64_t a, int64_t& b, __vpred& c);
template <size_t DEPTH>
void __min_index(long2 a, long2::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
template <size_t DEPTH>
void __min_index(long4 a, long4::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
template <size_t DEPTH>
void __min_index(long8 a, long8::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
void __min_index(int16_t a, int16_t& b, __vpred& c);
template <size_t DEPTH>
void __min_index(short2 a, short2::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
template <size_t DEPTH>
void __min_index(short4 a, short4::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
template <size_t DEPTH>
void __min_index(short8 a, short8::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
template <size_t DEPTH>
void __min_index(short16 a, short16::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
template <size_t DEPTH>
void __min_index(short32 a, short32::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
void __min_index(int32_t a, int32_t& b, __vpred& c);
template <size_t DEPTH>
void __min_index(int2 a, int2::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
template <size_t DEPTH>
void __min_index(int4 a, int4::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
template <size_t DEPTH>
void __min_index(int8 a, int8::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
template <size_t DEPTH>
void __min_index(int16 a, int16::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
void __min_index(uint8_t a, uint8_t& b, __vpred& c);
template <size_t DEPTH>
void __min_index(uchar2 a, uchar2::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
template <size_t DEPTH>
void __min_index(uchar4 a, uchar4::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
template <size_t DEPTH>
void __min_index(uchar8 a, uchar8::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
template <size_t DEPTH>
void __min_index(uchar16 a, uchar16::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
template <size_t DEPTH>
void __min_index(uchar32 a, uchar32::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
template <size_t DEPTH>
void __min_index(uchar64 a, uchar64::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
void __min_index(uint64_t a, uint64_t& b, __vpred& c);
template <size_t DEPTH>
void __min_index(ulong2 a, ulong2::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
template <size_t DEPTH>
void __min_index(ulong4 a, ulong4::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
template <size_t DEPTH>
void __min_index(ulong8 a, ulong8::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
void __min_index(uint16_t a, uint16_t& b, __vpred& c);
template <size_t DEPTH>
void __min_index(ushort2 a, ushort2::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
template <size_t DEPTH>
void __min_index(ushort4 a, ushort4::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
template <size_t DEPTH>
void __min_index(ushort8 a, ushort8::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
template <size_t DEPTH>
void __min_index(ushort16 a, ushort16::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
template <size_t DEPTH>
void __min_index(ushort32 a, ushort32::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
void __min_index(uint32_t a, uint32_t& b, __vpred& c);
template <size_t DEPTH>
void __min_index(uint2 a, uint2::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
template <size_t DEPTH>
void __min_index(uint4 a, uint4::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
template <size_t DEPTH>
void __min_index(uint8 a, uint8::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
template <size_t DEPTH>
void __min_index(uint16 a, uint16::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c);
int64_t __moddw_drd(int64_t a, int32_t b);
uint64_t __modudw_drd(uint64_t a, uint32_t b);
uint32_t __moduw_rrr(uint32_t a, uint32_t b);
int32_t __modw_rrr(int32_t a, int32_t b);
int32_t __mpy_ext(int16_t a, int16_t b);
int32_t __mpy_ext(int16_t a, uint16_t b);
uint32_t __mpy_ext(uint16_t a, uint16_t b);
int2 __mpy_ext(short2 a, short2 b);
int4 __mpy_ext(short4 a, short4 b);
int8 __mpy_ext(short8 a, short8 b);
int16 __mpy_ext(short16 a, short16 b);
double __mpy_ext(float a, float b);
double2 __mpy_ext(float2 a, float2 b);
double4 __mpy_ext(float4 a, float4 b);
double8 __mpy_ext(float8 a, float8 b);
int16_t __mpy_ext(int8_t a, uint8_t b);
short2 __mpy_ext(char2 a, uchar2 b);
short4 __mpy_ext(char4 a, uchar4 b);
short8 __mpy_ext(char8 a, uchar8 b);
short16 __mpy_ext(char16 a, uchar16 b);
short32 __mpy_ext(char32 a, uchar32 b);
int2 __mpy_ext(short2 a, ushort2 b);
int4 __mpy_ext(short4 a, ushort4 b);
int8 __mpy_ext(short8 a, ushort8 b);
int16 __mpy_ext(short16 a, ushort16 b);
int64_t __mpy_ext(int32_t a, uint32_t b);
long2 __mpy_ext(int2 a, uint2 b);
long4 __mpy_ext(int4 a, uint4 b);
long8 __mpy_ext(int8 a, uint8 b);
uint16_t __mpy_ext(uint8_t a, uint8_t b);
ushort2 __mpy_ext(uchar2 a, uchar2 b);
ushort4 __mpy_ext(uchar4 a, uchar4 b);
ushort8 __mpy_ext(uchar8 a, uchar8 b);
ushort16 __mpy_ext(uchar16 a, uchar16 b);
ushort32 __mpy_ext(uchar32 a, uchar32 b);
ulong2 __mpy_ext(uint64_t a, uint64_t b);
ulong4 __mpy_ext(ulong2 a, ulong2 b);
ulong8 __mpy_ext(ulong4 a, ulong4 b);
uint2 __mpy_ext(ushort2 a, ushort2 b);
uint4 __mpy_ext(ushort4 a, ushort4 b);
uint8 __mpy_ext(ushort8 a, ushort8 b);
uint16 __mpy_ext(ushort16 a, ushort16 b);
uint64_t __mpy_ext(uint32_t a, uint32_t b);
ulong2 __mpy_ext(uint2 a, uint2 b);
ulong4 __mpy_ext(uint4 a, uint4 b);
ulong8 __mpy_ext(uint8 a, uint8 b);
int64_t __mpy_ext(int32_t a, int32_t b);
long2 __mpy_ext(int2 a, int2 b);
long4 __mpy_ext(int4 a, int4 b);
long8 __mpy_ext(int8 a, int8 b);
int2 __mpy_fx(short2 a, int32_t b);
int32_t __mpy_sat(int32_t a, int32_t b);
int2 __mpy_sat(int2 a, int2 b);
int4 __mpy_sat(int4 a, int4 b);
int8 __mpy_sat(int8 a, int8 b);
int16 __mpy_sat(int16 a, int16 b);
int32_t __mpy_sat_ext(int16_t a, int16_t b);
int2 __mpy_sat_ext(short2 a, short2 b);
int4 __mpy_sat_ext(short4 a, short4 b);
int8 __mpy_sat_ext(short8 a, short8 b);
int16 __mpy_sat_ext(short16 a, short16 b);
int16_t __mpy_sat_fxq15(int16_t a, int16_t b);
short2 __mpy_sat_fxq15(short2 a, short2 b);
short4 __mpy_sat_fxq15(short4 a, short4 b);
short8 __mpy_sat_fxq15(short8 a, short8 b);
short16 __mpy_sat_fxq15(short16 a, short16 b);
short32 __mpy_sat_fxq15(short32 a, short32 b);
int16_t __mpy_sat_fxq15(int16_t a, uint16_t b);
short2 __mpy_sat_fxq15(short2 a, ushort2 b);
short4 __mpy_sat_fxq15(short4 a, ushort4 b);
short8 __mpy_sat_fxq15(short8 a, ushort8 b);
short16 __mpy_sat_fxq15(short16 a, ushort16 b);
short32 __mpy_sat_fxq15(short32 a, ushort32 b);
uint16_t __mpy_sat_fxq16(uint16_t a, uint16_t b);
ushort2 __mpy_sat_fxq16(ushort2 a, ushort2 b);
ushort4 __mpy_sat_fxq16(ushort4 a, ushort4 b);
ushort8 __mpy_sat_fxq16(ushort8 a, ushort8 b);
ushort16 __mpy_sat_fxq16(ushort16 a, ushort16 b);
ushort32 __mpy_sat_fxq16(ushort32 a, ushort32 b);
int32_t __mpy_sat_fxq16_15(int32_t a, int32_t b);
int2 __mpy_sat_fxq16_15(int2 a, int2 b);
int4 __mpy_sat_fxq16_15(int4 a, int4 b);
int8 __mpy_sat_fxq16_15(int8 a, int8 b);
int16 __mpy_sat_fxq16_15(int16 a, int16 b);
int32_t __mpy_sat_fxq31(int32_t a, int32_t b);
int2 __mpy_sat_fxq31(int2 a, int2 b);
int4 __mpy_sat_fxq31(int4 a, int4 b);
int8 __mpy_sat_fxq31(int8 a, int8 b);
int16 __mpy_sat_fxq31(int16 a, int16 b);
uint32_t __mpy_xor(uint32_t a, uint32_t b);
uint2 __mpy_xor(uint2 a, uint2 b);
uint4 __mpy_xor(uint4 a, uint4 b);
uint8 __mpy_xor(uint8 a, uint8 b);
uint16 __mpy_xor(uint16 a, uint16 b);
int64_t __mpydd_ddd(int64_t a, int64_t b);
uint64_t __mpydd_ddd(uint64_t a, uint64_t b);
double __mpydp_ddd(double a, double b);
int32_t __mpyhw_rrr(int16_t a, int16_t b);
float __mpysp_rrr(float a, float b);
int32_t __mpysuhw_rrr(int16_t a, uint16_t b);
uint32_t __mpyuhw_rrr(uint16_t a, uint16_t b);
int32_t __mpyww_rrr(int32_t a, int32_t b);
uint32_t __mpyww_rrr(uint32_t a, uint32_t b);
__vpred __nand(__vpred a, __vpred b);
int8_t __nand(int8_t a, int8_t b);
char2 __nand(char2 a, char2 b);
char4 __nand(char4 a, char4 b);
char8 __nand(char8 a, char8 b);
int16_t __nand(int16_t a, int16_t b);
short2 __nand(short2 a, short2 b);
short4 __nand(short4 a, short4 b);
int32_t __nand(int32_t a, int32_t b);
int2 __nand(int2 a, int2 b);
int64_t __nand(int64_t a, int64_t b);
uint8_t __nand(uint8_t a, uint8_t b);
uchar2 __nand(uchar2 a, uchar2 b);
uchar4 __nand(uchar4 a, uchar4 b);
uchar8 __nand(uchar8 a, uchar8 b);
uint16_t __nand(uint16_t a, uint16_t b);
ushort2 __nand(ushort2 a, ushort2 b);
ushort4 __nand(ushort4 a, ushort4 b);
uint32_t __nand(uint32_t a, uint32_t b);
uint2 __nand(uint2 a, uint2 b);
uint64_t __nand(uint64_t a, uint64_t b);
char16 __nand(char16 a, char16 b);
char32 __nand(char32 a, char32 b);
char64 __nand(char64 a, char64 b);
short8 __nand(short8 a, short8 b);
short16 __nand(short16 a, short16 b);
short32 __nand(short32 a, short32 b);
int4 __nand(int4 a, int4 b);
int8 __nand(int8 a, int8 b);
int16 __nand(int16 a, int16 b);
long2 __nand(long2 a, long2 b);
long4 __nand(long4 a, long4 b);
long8 __nand(long8 a, long8 b);
uchar16 __nand(uchar16 a, uchar16 b);
uchar32 __nand(uchar32 a, uchar32 b);
uchar64 __nand(uchar64 a, uchar64 b);
ushort8 __nand(ushort8 a, ushort8 b);
ushort16 __nand(ushort16 a, ushort16 b);
ushort32 __nand(ushort32 a, ushort32 b);
uint4 __nand(uint4 a, uint4 b);
uint8 __nand(uint8 a, uint8 b);
uint16 __nand(uint16 a, uint16 b);
ulong2 __nand(ulong2 a, ulong2 b);
ulong4 __nand(ulong4 a, ulong4 b);
ulong8 __nand(ulong8 a, ulong8 b);
__vpred __nand_ppp(__vpred a, __vpred b);
char8 __nandd_ddd(char8 a, char8 b);
short4 __nandd_ddd(short4 a, short4 b);
int2 __nandd_ddd(int2 a, int2 b);
int64_t __nandd_ddd(int64_t a, int64_t b);
uchar8 __nandd_ddd(uchar8 a, uchar8 b);
ushort4 __nandd_ddd(ushort4 a, ushort4 b);
uint2 __nandd_ddd(uint2 a, uint2 b);
uint64_t __nandd_ddd(uint64_t a, uint64_t b);
int64_t __nandd_dkd(int64_t a, int64_t b);
uint64_t __nandd_dkd(uint64_t a, uint64_t b);
char4 __nandw_rrr(char4 a, char4 b);
short2 __nandw_rrr(short2 a, short2 b);
int32_t __nandw_rrr(int32_t a, int32_t b);
uchar4 __nandw_rrr(uchar4 a, uchar4 b);
ushort2 __nandw_rrr(ushort2 a, ushort2 b);
uint32_t __nandw_rrr(uint32_t a, uint32_t b);
__vpred __negate(__vpred a);
__vpred __nor(__vpred a, __vpred b);
int8_t __nor(int8_t a, int8_t b);
char2 __nor(char2 a, char2 b);
char4 __nor(char4 a, char4 b);
char8 __nor(char8 a, char8 b);
int16_t __nor(int16_t a, int16_t b);
short2 __nor(short2 a, short2 b);
short4 __nor(short4 a, short4 b);
int32_t __nor(int32_t a, int32_t b);
int2 __nor(int2 a, int2 b);
int64_t __nor(int64_t a, int64_t b);
uint8_t __nor(uint8_t a, uint8_t b);
uchar2 __nor(uchar2 a, uchar2 b);
uchar4 __nor(uchar4 a, uchar4 b);
uchar8 __nor(uchar8 a, uchar8 b);
uint16_t __nor(uint16_t a, uint16_t b);
ushort2 __nor(ushort2 a, ushort2 b);
ushort4 __nor(ushort4 a, ushort4 b);
uint32_t __nor(uint32_t a, uint32_t b);
uint2 __nor(uint2 a, uint2 b);
uint64_t __nor(uint64_t a, uint64_t b);
char16 __nor(char16 a, char16 b);
char32 __nor(char32 a, char32 b);
char64 __nor(char64 a, char64 b);
short8 __nor(short8 a, short8 b);
short16 __nor(short16 a, short16 b);
short32 __nor(short32 a, short32 b);
int4 __nor(int4 a, int4 b);
int8 __nor(int8 a, int8 b);
int16 __nor(int16 a, int16 b);
long2 __nor(long2 a, long2 b);
long4 __nor(long4 a, long4 b);
long8 __nor(long8 a, long8 b);
__vpred __nor_ppp(__vpred a, __vpred b);
char8 __nord_ddd(char8 a, char8 b);
short4 __nord_ddd(short4 a, short4 b);
int2 __nord_ddd(int2 a, int2 b);
int64_t __nord_ddd(int64_t a, int64_t b);
uchar8 __nord_ddd(uchar8 a, uchar8 b);
ushort4 __nord_ddd(ushort4 a, ushort4 b);
uint2 __nord_ddd(uint2 a, uint2 b);
uint64_t __nord_ddd(uint64_t a, uint64_t b);
int64_t __nord_dkd(int64_t a, int64_t b);
uint64_t __nord_dkd(uint64_t a, uint64_t b);
int8_t __norm(int8_t a);
char2 __norm(char2 a);
char4 __norm(char4 a);
char8 __norm(char8 a);
char16 __norm(char16 a);
char32 __norm(char32 a);
char64 __norm(char64 a);
int64_t __norm(int64_t a);
long2 __norm(long2 a);
long4 __norm(long4 a);
long8 __norm(long8 a);
int16_t __norm(int16_t a);
short2 __norm(short2 a);
short4 __norm(short4 a);
short8 __norm(short8 a);
short16 __norm(short16 a);
short32 __norm(short32 a);
int32_t __norm(int32_t a);
int2 __norm(int2 a);
int4 __norm(int4 a);
int8 __norm(int8 a);
int16 __norm(int16 a);
ushort2 __norm_and_shift_elem_pair(ushort2 a);
ushort4 __norm_and_shift_elem_pair(ushort4 a);
ushort8 __norm_and_shift_elem_pair(ushort8 a);
ushort16 __norm_and_shift_elem_pair(ushort16 a);
ushort32 __norm_and_shift_elem_pair(ushort32 a);
uint2 __norm_and_shift_elem_pair(uint2 a);
uint4 __norm_and_shift_elem_pair(uint4 a);
uint8 __norm_and_shift_elem_pair(uint8 a);
uint16 __norm_and_shift_elem_pair(uint16 a);
char4 __norw_rrr(char4 a, char4 b);
short2 __norw_rrr(short2 a, short2 b);
int32_t __norw_rrr(int32_t a, int32_t b);
uchar4 __norw_rrr(uchar4 a, uchar4 b);
ushort2 __norw_rrr(ushort2 a, ushort2 b);
uint32_t __norw_rrr(uint32_t a, uint32_t b);
__vpred __not_pp(__vpred a);
__vpred __or(__vpred a, __vpred b);
__vpred __or_ppp(__vpred a, __vpred b);
char8 __ord_ddd(char8 a, char8 b);
short4 __ord_ddd(short4 a, short4 b);
int2 __ord_ddd(int2 a, int2 b);
int64_t __ord_ddd(int64_t a, int64_t b);
uchar8 __ord_ddd(uchar8 a, uchar8 b);
ushort4 __ord_ddd(ushort4 a, ushort4 b);
uint2 __ord_ddd(uint2 a, uint2 b);
uint64_t __ord_ddd(uint64_t a, uint64_t b);
int64_t __ord_dkd(int64_t a, int64_t b);
uint64_t __ord_dkd(uint64_t a, uint64_t b);
__vpred __orn(__vpred a, __vpred b);
int8_t __orn(int8_t a, int8_t b);
char2 __orn(char2 a, char2 b);
char4 __orn(char4 a, char4 b);
char8 __orn(char8 a, char8 b);
int16_t __orn(int16_t a, int16_t b);
short2 __orn(short2 a, short2 b);
short4 __orn(short4 a, short4 b);
int32_t __orn(int32_t a, int32_t b);
int2 __orn(int2 a, int2 b);
int64_t __orn(int64_t a, int64_t b);
uint8_t __orn(uint8_t a, uint8_t b);
uchar2 __orn(uchar2 a, uchar2 b);
uchar4 __orn(uchar4 a, uchar4 b);
uchar8 __orn(uchar8 a, uchar8 b);
uint16_t __orn(uint16_t a, uint16_t b);
ushort2 __orn(ushort2 a, ushort2 b);
ushort4 __orn(ushort4 a, ushort4 b);
uint32_t __orn(uint32_t a, uint32_t b);
uint2 __orn(uint2 a, uint2 b);
uint64_t __orn(uint64_t a, uint64_t b);
char16 __orn(char16 a, char16 b);
char32 __orn(char32 a, char32 b);
char64 __orn(char64 a, char64 b);
short8 __orn(short8 a, short8 b);
short16 __orn(short16 a, short16 b);
short32 __orn(short32 a, short32 b);
int4 __orn(int4 a, int4 b);
int8 __orn(int8 a, int8 b);
int16 __orn(int16 a, int16 b);
long2 __orn(long2 a, long2 b);
long4 __orn(long4 a, long4 b);
long8 __orn(long8 a, long8 b);
__vpred __orn_ppp(__vpred a, __vpred b);
char8 __ornd_ddd(char8 a, char8 b);
short4 __ornd_ddd(short4 a, short4 b);
int2 __ornd_ddd(int2 a, int2 b);
int64_t __ornd_ddd(int64_t a, int64_t b);
uchar8 __ornd_ddd(uchar8 a, uchar8 b);
ushort4 __ornd_ddd(ushort4 a, ushort4 b);
uint2 __ornd_ddd(uint2 a, uint2 b);
uint64_t __ornd_ddd(uint64_t a, uint64_t b);
int64_t __ornd_dkd(int64_t a, int64_t b);
uint64_t __ornd_dkd(uint64_t a, uint64_t b);
char4 __ornw_rkr(char4 a, char4 b);
short2 __ornw_rkr(short2 a, short2 b);
int32_t __ornw_rkr(int32_t a, int32_t b);
uchar4 __ornw_rkr(uchar4 a, uchar4 b);
ushort2 __ornw_rkr(ushort2 a, ushort2 b);
uint32_t __ornw_rkr(uint32_t a, uint32_t b);
char4 __ornw_rrr(char4 a, char4 b);
short2 __ornw_rrr(short2 a, short2 b);
int32_t __ornw_rrr(int32_t a, int32_t b);
uchar4 __ornw_rrr(uchar4 a, uchar4 b);
ushort2 __ornw_rrr(ushort2 a, ushort2 b);
uint32_t __ornw_rrr(uint32_t a, uint32_t b);
char4 __orw_rkr(char4 a, char4 b);
short2 __orw_rkr(short2 a, short2 b);
int32_t __orw_rkr(int32_t a, int32_t b);
uchar4 __orw_rkr(uchar4 a, uchar4 b);
ushort2 __orw_rkr(ushort2 a, ushort2 b);
uint32_t __orw_rkr(uint32_t a, uint32_t b);
char4 __orw_rrr(char4 a, char4 b);
short2 __orw_rrr(short2 a, short2 b);
int32_t __orw_rrr(int32_t a, int32_t b);
uchar4 __orw_rrr(uchar4 a, uchar4 b);
ushort2 __orw_rrr(ushort2 a, ushort2 b);
uint32_t __orw_rrr(uint32_t a, uint32_t b);
float4 __outer_product_matmpy(float2 a, float2 b);
float8 __outer_product_matmpy(float4 a, float4 b);
float16 __outer_product_matmpy(float8 a, float8 b);
char64 __pack_consec_high_char(char64 a, char64 b);
uchar64 __pack_consec_high_char(uchar64 a, uchar64 b);
uint16 __pack_consec_high_int(uint16 a, uint16 b);
int16 __pack_consec_high_int(int16 a, int16 b);
long8 __pack_consec_high_long(long8 a, long8 b);
ulong8 __pack_consec_high_long(ulong8 a, ulong8 b);
short32 __pack_consec_high_short(short32 a, short32 b);
ushort32 __pack_consec_high_short(ushort32 a, ushort32 b);
char64 __pack_consec_low_char(char64 a, char64 b);
uchar64 __pack_consec_low_char(uchar64 a, uchar64 b);
uint16 __pack_consec_low_int(uint16 a, uint16 b);
int16 __pack_consec_low_int(int16 a, int16 b);
long8 __pack_consec_low_long(long8 a, long8 b);
ulong8 __pack_consec_low_long(ulong8 a, ulong8 b);
short32 __pack_consec_low_short(short32 a, short32 b);
ushort32 __pack_consec_low_short(ushort32 a, ushort32 b);
char8 __pack_even_cross_short(char4 a, char4 b);
short4 __pack_even_cross_short(short2 a, short2 b);
int2 __pack_even_cross_short(int32_t a, int32_t b);
uchar8 __pack_even_cross_short(uchar4 a, uchar4 b);
ushort4 __pack_even_cross_short(ushort2 a, ushort2 b);
uint2 __pack_even_cross_short(uint32_t a, uint32_t b);
char8 __pack_even_cross_short(char8 a, char8 b);
char16 __pack_even_cross_short(char16 a, char16 b);
char32 __pack_even_cross_short(char32 a, char32 b);
char64 __pack_even_cross_short(char64 a, char64 b);
short4 __pack_even_cross_short(short4 a, short4 b);
short8 __pack_even_cross_short(short8 a, short8 b);
short16 __pack_even_cross_short(short16 a, short16 b);
short32 __pack_even_cross_short(short32 a, short32 b);
int2 __pack_even_cross_short(int2 a, int2 b);
int4 __pack_even_cross_short(int4 a, int4 b);
int8 __pack_even_cross_short(int8 a, int8 b);
int16 __pack_even_cross_short(int16 a, int16 b);
int64_t __pack_even_cross_short(int64_t a, int64_t b);
long2 __pack_even_cross_short(long2 a, long2 b);
long4 __pack_even_cross_short(long4 a, long4 b);
long8 __pack_even_cross_short(long8 a, long8 b);
uchar8 __pack_even_cross_short(uchar8 a, uchar8 b);
uchar16 __pack_even_cross_short(uchar16 a, uchar16 b);
uchar32 __pack_even_cross_short(uchar32 a, uchar32 b);
uchar64 __pack_even_cross_short(uchar64 a, uchar64 b);
ushort4 __pack_even_cross_short(ushort4 a, ushort4 b);
ushort8 __pack_even_cross_short(ushort8 a, ushort8 b);
ushort16 __pack_even_cross_short(ushort16 a, ushort16 b);
ushort32 __pack_even_cross_short(ushort32 a, ushort32 b);
uint2 __pack_even_cross_short(uint2 a, uint2 b);
uint4 __pack_even_cross_short(uint4 a, uint4 b);
uint8 __pack_even_cross_short(uint8 a, uint8 b);
uint16 __pack_even_cross_short(uint16 a, uint16 b);
uint64_t __pack_even_cross_short(uint64_t a, uint64_t b);
ulong2 __pack_even_cross_short(ulong2 a, ulong2 b);
ulong4 __pack_even_cross_short(ulong4 a, ulong4 b);
ulong8 __pack_even_cross_short(ulong8 a, ulong8 b);
char8 __pack_even_short(char8 a, char8 b);
char16 __pack_even_short(char16 a, char16 b);
char32 __pack_even_short(char32 a, char32 b);
char64 __pack_even_short(char64 a, char64 b);
short4 __pack_even_short(short4 a, short4 b);
short8 __pack_even_short(short8 a, short8 b);
short16 __pack_even_short(short16 a, short16 b);
short32 __pack_even_short(short32 a, short32 b);
int2 __pack_even_short(int2 a, int2 b);
int4 __pack_even_short(int4 a, int4 b);
int8 __pack_even_short(int8 a, int8 b);
int16 __pack_even_short(int16 a, int16 b);
int64_t __pack_even_short(int64_t a, int64_t b);
long2 __pack_even_short(long2 a, long2 b);
long4 __pack_even_short(long4 a, long4 b);
long8 __pack_even_short(long8 a, long8 b);
uchar8 __pack_even_short(uchar8 a, uchar8 b);
uchar16 __pack_even_short(uchar16 a, uchar16 b);
uchar32 __pack_even_short(uchar32 a, uchar32 b);
uchar64 __pack_even_short(uchar64 a, uchar64 b);
ushort4 __pack_even_short(ushort4 a, ushort4 b);
ushort8 __pack_even_short(ushort8 a, ushort8 b);
ushort16 __pack_even_short(ushort16 a, ushort16 b);
ushort32 __pack_even_short(ushort32 a, ushort32 b);
uint2 __pack_even_short(uint2 a, uint2 b);
uint4 __pack_even_short(uint4 a, uint4 b);
uint8 __pack_even_short(uint8 a, uint8 b);
uint16 __pack_even_short(uint16 a, uint16 b);
uint64_t __pack_even_short(uint64_t a, uint64_t b);
ulong2 __pack_even_short(ulong2 a, ulong2 b);
ulong4 __pack_even_short(ulong4 a, ulong4 b);
ulong8 __pack_even_short(ulong8 a, ulong8 b);
char2 __pack_high_char(char2 a, char2 b);
char4 __pack_high_char(char4 a, char4 b);
char8 __pack_high_char(char8 a, char8 b);
char16 __pack_high_char(char16 a, char16 b);
char32 __pack_high_char(char32 a, char32 b);
char64 __pack_high_char(char64 a, char64 b);
int16_t __pack_high_char(int16_t a, int16_t b);
short2 __pack_high_char(short2 a, short2 b);
short4 __pack_high_char(short4 a, short4 b);
short8 __pack_high_char(short8 a, short8 b);
short16 __pack_high_char(short16 a, short16 b);
short32 __pack_high_char(short32 a, short32 b);
int32_t __pack_high_char(int32_t a, int32_t b);
int2 __pack_high_char(int2 a, int2 b);
int4 __pack_high_char(int4 a, int4 b);
int8 __pack_high_char(int8 a, int8 b);
int16 __pack_high_char(int16 a, int16 b);
int64_t __pack_high_char(int64_t a, int64_t b);
long2 __pack_high_char(long2 a, long2 b);
long4 __pack_high_char(long4 a, long4 b);
long8 __pack_high_char(long8 a, long8 b);
char4 __pack_high_low_short(char4 a, char4 b);
char8 __pack_high_low_short(char8 a, char8 b);
char16 __pack_high_low_short(char16 a, char16 b);
char32 __pack_high_low_short(char32 a, char32 b);
char64 __pack_high_low_short(char64 a, char64 b);
short2 __pack_high_low_short(short2 a, short2 b);
short4 __pack_high_low_short(short4 a, short4 b);
short8 __pack_high_low_short(short8 a, short8 b);
short16 __pack_high_low_short(short16 a, short16 b);
short32 __pack_high_low_short(short32 a, short32 b);
int32_t __pack_high_low_short(int32_t a, int32_t b);
int2 __pack_high_low_short(int2 a, int2 b);
int4 __pack_high_low_short(int4 a, int4 b);
int8 __pack_high_low_short(int8 a, int8 b);
int16 __pack_high_low_short(int16 a, int16 b);
int64_t __pack_high_low_short(int64_t a, int64_t b);
long2 __pack_high_low_short(long2 a, long2 b);
long4 __pack_high_low_short(long4 a, long4 b);
long8 __pack_high_low_short(long8 a, long8 b);
char4 __pack_high_short(char4 a, char4 b);
char8 __pack_high_short(char8 a, char8 b);
char16 __pack_high_short(char16 a, char16 b);
char32 __pack_high_short(char32 a, char32 b);
char64 __pack_high_short(char64 a, char64 b);
short2 __pack_high_short(short2 a, short2 b);
short4 __pack_high_short(short4 a, short4 b);
short8 __pack_high_short(short8 a, short8 b);
short16 __pack_high_short(short16 a, short16 b);
short32 __pack_high_short(short32 a, short32 b);
int32_t __pack_high_short(int32_t a, int32_t b);
int2 __pack_high_short(int2 a, int2 b);
int4 __pack_high_short(int4 a, int4 b);
int8 __pack_high_short(int8 a, int8 b);
int16 __pack_high_short(int16 a, int16 b);
int64_t __pack_high_short(int64_t a, int64_t b);
long2 __pack_high_short(long2 a, long2 b);
long4 __pack_high_short(long4 a, long4 b);
long8 __pack_high_short(long8 a, long8 b);
char2 __pack_low_char(char2 a, char2 b);
char4 __pack_low_char(char4 a, char4 b);
char8 __pack_low_char(char8 a, char8 b);
char16 __pack_low_char(char16 a, char16 b);
char32 __pack_low_char(char32 a, char32 b);
char64 __pack_low_char(char64 a, char64 b);
int16_t __pack_low_char(int16_t a, int16_t b);
short2 __pack_low_char(short2 a, short2 b);
short4 __pack_low_char(short4 a, short4 b);
short8 __pack_low_char(short8 a, short8 b);
short16 __pack_low_char(short16 a, short16 b);
short32 __pack_low_char(short32 a, short32 b);
int32_t __pack_low_char(int32_t a, int32_t b);
int2 __pack_low_char(int2 a, int2 b);
int4 __pack_low_char(int4 a, int4 b);
int8 __pack_low_char(int8 a, int8 b);
int16 __pack_low_char(int16 a, int16 b);
int64_t __pack_low_char(int64_t a, int64_t b);
long2 __pack_low_char(long2 a, long2 b);
long4 __pack_low_char(long4 a, long4 b);
long8 __pack_low_char(long8 a, long8 b);
char8 __pack_low_high_char(char8 a, char8 b);
char16 __pack_low_high_char(char16 a, char16 b);
char32 __pack_low_high_char(char32 a, char32 b);
char64 __pack_low_high_char(char64 a, char64 b);
short4 __pack_low_high_char(short4 a, short4 b);
short8 __pack_low_high_char(short8 a, short8 b);
short16 __pack_low_high_char(short16 a, short16 b);
short32 __pack_low_high_char(short32 a, short32 b);
int2 __pack_low_high_char(int2 a, int2 b);
int4 __pack_low_high_char(int4 a, int4 b);
int8 __pack_low_high_char(int8 a, int8 b);
int16 __pack_low_high_char(int16 a, int16 b);
int64_t __pack_low_high_char(int64_t a, int64_t b);
long2 __pack_low_high_char(long2 a, long2 b);
long4 __pack_low_high_char(long4 a, long4 b);
long8 __pack_low_high_char(long8 a, long8 b);
uchar8 __pack_low_high_char(uchar8 a, uchar8 b);
uchar16 __pack_low_high_char(uchar16 a, uchar16 b);
uchar32 __pack_low_high_char(uchar32 a, uchar32 b);
uchar64 __pack_low_high_char(uchar64 a, uchar64 b);
ushort4 __pack_low_high_char(ushort4 a, ushort4 b);
ushort8 __pack_low_high_char(ushort8 a, ushort8 b);
ushort16 __pack_low_high_char(ushort16 a, ushort16 b);
ushort32 __pack_low_high_char(ushort32 a, ushort32 b);
uint2 __pack_low_high_char(uint2 a, uint2 b);
uint4 __pack_low_high_char(uint4 a, uint4 b);
uint8 __pack_low_high_char(uint8 a, uint8 b);
uint16 __pack_low_high_char(uint16 a, uint16 b);
uint64_t __pack_low_high_char(uint64_t a, uint64_t b);
ulong2 __pack_low_high_char(ulong2 a, ulong2 b);
ulong4 __pack_low_high_char(ulong4 a, ulong4 b);
ulong8 __pack_low_high_char(ulong8 a, ulong8 b);
char4 __pack_low_high_short(char4 a, char4 b);
char8 __pack_low_high_short(char8 a, char8 b);
char16 __pack_low_high_short(char16 a, char16 b);
char32 __pack_low_high_short(char32 a, char32 b);
char64 __pack_low_high_short(char64 a, char64 b);
short2 __pack_low_high_short(short2 a, short2 b);
short4 __pack_low_high_short(short4 a, short4 b);
short8 __pack_low_high_short(short8 a, short8 b);
short16 __pack_low_high_short(short16 a, short16 b);
short32 __pack_low_high_short(short32 a, short32 b);
int32_t __pack_low_high_short(int32_t a, int32_t b);
int2 __pack_low_high_short(int2 a, int2 b);
int4 __pack_low_high_short(int4 a, int4 b);
int8 __pack_low_high_short(int8 a, int8 b);
int16 __pack_low_high_short(int16 a, int16 b);
int64_t __pack_low_high_short(int64_t a, int64_t b);
long2 __pack_low_high_short(long2 a, long2 b);
long4 __pack_low_high_short(long4 a, long4 b);
long8 __pack_low_high_short(long8 a, long8 b);
uchar4 __pack_low_high_short(uchar4 a, uchar4 b);
uchar8 __pack_low_high_short(uchar8 a, uchar8 b);
uchar16 __pack_low_high_short(uchar16 a, uchar16 b);
uchar32 __pack_low_high_short(uchar32 a, uchar32 b);
uchar64 __pack_low_high_short(uchar64 a, uchar64 b);
ushort2 __pack_low_high_short(ushort2 a, ushort2 b);
ushort4 __pack_low_high_short(ushort4 a, ushort4 b);
ushort8 __pack_low_high_short(ushort8 a, ushort8 b);
ushort16 __pack_low_high_short(ushort16 a, ushort16 b);
ushort32 __pack_low_high_short(ushort32 a, ushort32 b);
uint32_t __pack_low_high_short(uint32_t a, uint32_t b);
uint2 __pack_low_high_short(uint2 a, uint2 b);
uint4 __pack_low_high_short(uint4 a, uint4 b);
uint8 __pack_low_high_short(uint8 a, uint8 b);
uint16 __pack_low_high_short(uint16 a, uint16 b);
uint64_t __pack_low_high_short(uint64_t a, uint64_t b);
ulong2 __pack_low_high_short(ulong2 a, ulong2 b);
ulong4 __pack_low_high_short(ulong4 a, ulong4 b);
ulong8 __pack_low_high_short(ulong8 a, ulong8 b);
char8 __pack_low_int(char4 a, char4 b);
short4 __pack_low_int(short2 a, short2 b);
int2 __pack_low_int(int32_t a, int32_t b);
uchar8 __pack_low_int(uchar4 a, uchar4 b);
ushort4 __pack_low_int(ushort2 a, ushort2 b);
uint2 __pack_low_int(uint32_t a, uint32_t b);
int2 __pack_low_int(int2 a, int2 b);
int4 __pack_low_int(int4 a, int4 b);
int8 __pack_low_int(int8 a, int8 b);
int16 __pack_low_int(int16 a, int16 b);
uint2 __pack_low_int(uint2 a, uint2 b);
uint4 __pack_low_int(uint4 a, uint4 b);
uint8 __pack_low_int(uint8 a, uint8 b);
uint16 __pack_low_int(uint16 a, uint16 b);
char4 __pack_low_short(char4 a, char4 b);
char8 __pack_low_short(char8 a, char8 b);
char16 __pack_low_short(char16 a, char16 b);
char32 __pack_low_short(char32 a, char32 b);
char64 __pack_low_short(char64 a, char64 b);
short2 __pack_low_short(short2 a, short2 b);
short4 __pack_low_short(short4 a, short4 b);
short8 __pack_low_short(short8 a, short8 b);
short16 __pack_low_short(short16 a, short16 b);
short32 __pack_low_short(short32 a, short32 b);
int32_t __pack_low_short(int32_t a, int32_t b);
int2 __pack_low_short(int2 a, int2 b);
int4 __pack_low_short(int4 a, int4 b);
int8 __pack_low_short(int8 a, int8 b);
int16 __pack_low_short(int16 a, int16 b);
int64_t __pack_low_short(int64_t a, int64_t b);
long2 __pack_low_short(long2 a, long2 b);
long4 __pack_low_short(long4 a, long4 b);
long8 __pack_low_short(long8 a, long8 b);
int2 __pack_sat(int64_t a, int64_t b);
int4 __pack_sat(long2 a, long2 b);
int8 __pack_sat(long4 a, long4 b);
int16 __pack_sat(long8 a, long8 b);
char2 __pack_sat(int16_t a, int16_t b);
char4 __pack_sat(short2 a, short2 b);
char8 __pack_sat(short4 a, short4 b);
char16 __pack_sat(short8 a, short8 b);
char32 __pack_sat(short16 a, short16 b);
char64 __pack_sat(short32 a, short32 b);
uint2 __pack_usat(int64_t a, int64_t b);
uint4 __pack_usat(long2 a, long2 b);
uint8 __pack_usat(long4 a, long4 b);
uint16 __pack_usat(long8 a, long8 b);
uchar2 __pack_usat(int16_t a, int16_t b);
uchar4 __pack_usat(short2 a, short2 b);
uchar8 __pack_usat(short4 a, short4 b);
uchar16 __pack_usat(short8 a, short8 b);
uchar32 __pack_usat(short16 a, short16 b);
uchar64 __pack_usat(short32 a, short32 b);
ushort2 __pack_usat(int32_t a, int32_t b);
ushort4 __pack_usat(int2 a, int2 b);
ushort8 __pack_usat(int4 a, int4 b);
ushort16 __pack_usat(int8 a, int8 b);
ushort32 __pack_usat(int16 a, int16 b);
short2 __pack_sat(int32_t a, int32_t b);
short4 __pack_sat(int2 a, int2 b);
short8 __pack_sat(int4 a, int4 b);
short16 __pack_sat(int8 a, int8 b);
short32 __pack_sat(int16 a, int16 b);
short2 __pack_shift_sat(int32_t a, int32_t b);
short4 __pack_shift_sat(int2 a, int2 b);
short8 __pack_shift_sat(int4 a, int4 b);
short16 __pack_shift_sat(int8 a, int8 b);
short32 __pack_shift_sat(int16 a, int16 b);
char8 __packw_rrd(char4 a, char4 b);
short4 __packw_rrd(short2 a, short2 b);
int2 __packw_rrd(int32_t a, int32_t b);
uchar8 __packw_rrd(uchar4 a, uchar4 b);
ushort4 __packw_rrd(ushort2 a, ushort2 b);
uint2 __packw_rrd(uint32_t a, uint32_t b);
int64_t __packwdly4_rrd(int32_t a, int32_t b);
uint64_t __packwdly4_rrd(uint32_t a, uint32_t b);
char8 __packx2_rrd(char4 a, char4 b);
short4 __packx2_rrd(short2 a, short2 b);
int2 __packx2_rrd(int32_t a, int32_t b);
uchar8 __packx2_rrd(uchar4 a, uchar4 b);
ushort4 __packx2_rrd(ushort2 a, ushort2 b);
uint2 __packx2_rrd(uint32_t a, uint32_t b);
uint16 __parallel_pack_dup_16way(__vpred a);
uint16 __parallel_pack_dup_8way(__vpred a);
uint32_t __pbitcntb_pr(__vpred a);
uint32_t __pbitcntd_pr(__vpred a);
uint32_t __pbitcnth_pr(__vpred a);
uint32_t __pbitcntw_pr(__vpred a);
void __pcntgatherb_prp(__vpred a, uint32_t& b, __vpred& c);
void __pcntgatherd_prp(__vpred a, uint32_t& b, __vpred& c);
void __pcntgatherh_prp(__vpred a, uint32_t& b, __vpred& c);
void __pcntgatherw_prp(__vpred a, uint32_t& b, __vpred& c);
__vpred __pduph2b_pp(__vpred a);
__vpred __pduph2d_pp(__vpred a);
__vpred __pduph2h_pp(__vpred a);
__vpred __pduph2w_pp(__vpred a);
__vpred __pdupl2b_pp(__vpred a);
__vpred __pdupl2d_pp(__vpred a);
__vpred __pdupl2h_pp(__vpred a);
__vpred __pdupl2w_pp(__vpred a);
uchar64 __permute(uchar64 a, uchar64 b);
uchar64 __permute_cntrl(uchar64 a, uchar64 b);
uchar64 __permute_even_even_char(uchar64 a, uchar64 b, uchar64 c);
uchar64 __permute_even_even_int(uchar64 a, uchar64 b, uchar64 c);
uchar64 __permute_even_even_long(uchar64 a, uchar64 b, uchar64 c);
uchar64 __permute_even_even_quad(uchar64 a, uchar64 b, uchar64 c);
uchar64 __permute_even_even_short(uchar64 a, uchar64 b, uchar64 c);
uchar64 __permute_even_odd_char(uchar64 a, uchar64 b, uchar64 c);
uchar64 __permute_even_odd_int(uchar64 a, uchar64 b, uchar64 c);
uchar64 __permute_even_odd_long(uchar64 a, uchar64 b, uchar64 c);
uchar64 __permute_even_odd_quad(uchar64 a, uchar64 b, uchar64 c);
uchar64 __permute_even_odd_short(uchar64 a, uchar64 b, uchar64 c);
uchar64 __permute_high_high(uchar64 a, uchar64 b, uchar64 c);
uchar64 __permute_low_high(uchar64 a, uchar64 b, uchar64 c);
uchar64 __permute_low_low(uchar64 a, uchar64 b, uchar64 c);
uchar64 __permute_odd_odd_char(uchar64 a, uchar64 b, uchar64 c);
uchar64 __permute_odd_odd_int(uchar64 a, uchar64 b, uchar64 c);
uchar64 __permute_odd_odd_long(uchar64 a, uchar64 b, uchar64 c);
uchar64 __permute_odd_odd_quad(uchar64 a, uchar64 b, uchar64 c);
uchar64 __permute_odd_odd_short(uchar64 a, uchar64 b, uchar64 c);
int8_t __popcount(int8_t a);
char2 __popcount(char2 a);
char4 __popcount(char4 a);
char8 __popcount(char8 a);
char16 __popcount(char16 a);
char32 __popcount(char32 a);
char64 __popcount(char64 a);
uint8_t __popcount(uint8_t a);
uchar2 __popcount(uchar2 a);
uchar4 __popcount(uchar4 a);
uchar8 __popcount(uchar8 a);
uchar16 __popcount(uchar16 a);
uchar32 __popcount(uchar32 a);
uchar64 __popcount(uchar64 a);
int64_t __popcount(int64_t a);
long2 __popcount(long2 a);
long4 __popcount(long4 a);
long8 __popcount(long8 a);
uint64_t __popcount(uint64_t a);
ulong2 __popcount(ulong2 a);
ulong4 __popcount(ulong4 a);
ulong8 __popcount(ulong8 a);
int16_t __popcount(int16_t a);
short2 __popcount(short2 a);
short4 __popcount(short4 a);
short8 __popcount(short8 a);
short16 __popcount(short16 a);
short32 __popcount(short32 a);
uint16_t __popcount(uint16_t a);
ushort2 __popcount(ushort2 a);
ushort4 __popcount(ushort4 a);
ushort8 __popcount(ushort8 a);
ushort16 __popcount(ushort16 a);
ushort32 __popcount(ushort32 a);
int32_t __popcount(int32_t a);
int2 __popcount(int2 a);
int4 __popcount(int4 a);
int8 __popcount(int8 a);
int16 __popcount(int16 a);
uint32_t __popcount(uint32_t a);
uint2 __popcount(uint2 a);
uint4 __popcount(uint4 a);
uint8 __popcount(uint8 a);
uint16 __popcount(uint16 a);
uint32_t __popcount_char(__vpred a);
void __popcount_gather_char(__vpred a, uint32_t& b, __vpred& c);
void __popcount_gather_int(__vpred a, uint32_t& b, __vpred& c);
void __popcount_gather_long(__vpred a, uint32_t& b, __vpred& c);
void __popcount_gather_short(__vpred a, uint32_t& b, __vpred& c);
uint32_t __popcount_int(__vpred a);
uint32_t __popcount_long(__vpred a);
uint32_t __popcount_short(__vpred a);
uint32_t __prmbdb_pr(__vpred a);
uint32_t __prmbdd_pr(__vpred a);
uint32_t __prmbdh_pr(__vpred a);
uint32_t __prmbdw_pr(__vpred a);
double __recip(double a);
double2 __recip(double2 a);
double4 __recip(double4 a);
double8 __recip(double8 a);
float __recip(float a);
float2 __recip(float2 a);
float4 __recip(float4 a);
float8 __recip(float8 a);
float16 __recip(float16 a);
double __recip_sqrt(double a);
double2 __recip_sqrt(double2 a);
double4 __recip_sqrt(double4 a);
double8 __recip_sqrt(double8 a);
float __recip_sqrt(float a);
float2 __recip_sqrt(float2 a);
float4 __recip_sqrt(float4 a);
float8 __recip_sqrt(float8 a);
float16 __recip_sqrt(float16 a);
uint64_t __replace(uint64_t a, uint8_t b, uint8_t c, uint64_t d);
int64_t __replace(int64_t a, int8_t b, int8_t c, int64_t d);
ulong2 __replace(ulong2 a, uchar2 b, uchar2 c, ulong2 d);
ulong4 __replace(ulong4 a, uchar4 b, uchar4 c, ulong4 d);
ulong8 __replace(ulong8 a, uchar8 b, uchar8 c, ulong8 d);
long2 __replace(long2 a, char2 b, char2 c, long2 d);
long4 __replace(long4 a, char4 b, char4 c, long4 d);
long8 __replace(long8 a, char8 b, char8 c, long8 d);
uint64_t __replace_dkkd(uint64_t a, uint8_t b, uint8_t c, uint64_t d);
int64_t __replace_dkkd(int64_t a, int8_t b, int8_t c, int64_t d);
ulong8 __replacev_dkkkv(uint64_t a, uint8_t b, uint8_t c, uint8_t d, ulong8 e);
long8 __replacev_dkkkv(int64_t a, int8_t b, int8_t c, int8_t d, long8 e);
uchar64 __reverse(uchar64 a);
char64 __reverse(char64 a);
ulong8 __reverse(ulong8 a);
long8 __reverse(long8 a);
ushort32 __reverse(ushort32 a);
short32 __reverse(short32 a);
uint16 __reverse(uint16 a);
int16 __reverse(int16 a);
int8_t __rhadd(int8_t a, int8_t b);
char2 __rhadd(char2 a, char2 b);
char4 __rhadd(char4 a, char4 b);
char8 __rhadd(char8 a, char8 b);
char16 __rhadd(char16 a, char16 b);
char32 __rhadd(char32 a, char32 b);
char64 __rhadd(char64 a, char64 b);
int64_t __rhadd(int64_t a, int64_t b);
long2 __rhadd(long2 a, long2 b);
long4 __rhadd(long4 a, long4 b);
long8 __rhadd(long8 a, long8 b);
int16_t __rhadd(int16_t a, int16_t b);
short2 __rhadd(short2 a, short2 b);
short4 __rhadd(short4 a, short4 b);
short8 __rhadd(short8 a, short8 b);
short16 __rhadd(short16 a, short16 b);
short32 __rhadd(short32 a, short32 b);
uint8_t __rhadd(uint8_t a, uint8_t b);
uchar2 __rhadd(uchar2 a, uchar2 b);
uchar4 __rhadd(uchar4 a, uchar4 b);
uchar8 __rhadd(uchar8 a, uchar8 b);
uchar16 __rhadd(uchar16 a, uchar16 b);
uchar32 __rhadd(uchar32 a, uchar32 b);
uchar64 __rhadd(uchar64 a, uchar64 b);
uint64_t __rhadd(uint64_t a, uint64_t b);
ulong2 __rhadd(ulong2 a, ulong2 b);
ulong4 __rhadd(ulong4 a, ulong4 b);
ulong8 __rhadd(ulong8 a, ulong8 b);
uint16_t __rhadd(uint16_t a, uint16_t b);
ushort2 __rhadd(ushort2 a, ushort2 b);
ushort4 __rhadd(ushort4 a, ushort4 b);
ushort8 __rhadd(ushort8 a, ushort8 b);
ushort16 __rhadd(ushort16 a, ushort16 b);
ushort32 __rhadd(ushort32 a, ushort32 b);
uint32_t __rhadd(uint32_t a, uint32_t b);
uint2 __rhadd(uint2 a, uint2 b);
uint4 __rhadd(uint4 a, uint4 b);
uint8 __rhadd(uint8 a, uint8 b);
uint16 __rhadd(uint16 a, uint16 b);
int32_t __rhadd(int32_t a, int32_t b);
int2 __rhadd(int2 a, int2 b);
int4 __rhadd(int4 a, int4 b);
int8 __rhadd(int8 a, int8 b);
int16 __rhadd(int16 a, int16 b);
uint32_t __rightmost_bit_detect_char(__vpred a);
uint32_t __rightmost_bit_detect_int(__vpred a);
uint32_t __rightmost_bit_detect_long(__vpred a);
uint32_t __rightmost_bit_detect_short(__vpred a);
uchar4 __rotate(uchar4 a, uint32_t b);
uchar8 __rotate(uchar8 a, uint2 b);
uchar16 __rotate(uchar16 a, uint4 b);
uchar32 __rotate(uchar32 a, uint8 b);
uchar64 __rotate(uchar64 a, uint16 b);
uint8_t __rotate(uint8_t a, uint8_t b);
uchar2 __rotate(uchar2 a, uchar2 b);
uchar4 __rotate(uchar4 a, uchar4 b);
uchar8 __rotate(uchar8 a, uchar8 b);
uchar16 __rotate(uchar16 a, uchar16 b);
uchar32 __rotate(uchar32 a, uchar32 b);
uchar64 __rotate(uchar64 a, uchar64 b);
uint64_t __rotate(uint64_t a, uint64_t b);
ulong2 __rotate(ulong2 a, ulong2 b);
ulong4 __rotate(ulong4 a, ulong4 b);
ulong8 __rotate(ulong8 a, ulong8 b);
uint64_t __rotate(uint64_t a, uint8_t b);
ulong2 __rotate(ulong2 a, uchar2 b);
ulong4 __rotate(ulong4 a, uchar4 b);
ulong8 __rotate(ulong8 a, uchar8 b);
ushort2 __rotate(ushort2 a, uint32_t b);
ushort4 __rotate(ushort4 a, uint2 b);
ushort8 __rotate(ushort8 a, uint4 b);
ushort16 __rotate(ushort16 a, uint8 b);
ushort32 __rotate(ushort32 a, uint16 b);
uint16_t __rotate(uint16_t a, uint16_t b);
ushort2 __rotate(ushort2 a, ushort2 b);
ushort4 __rotate(ushort4 a, ushort4 b);
ushort8 __rotate(ushort8 a, ushort8 b);
ushort16 __rotate(ushort16 a, ushort16 b);
ushort32 __rotate(ushort32 a, ushort32 b);
int32_t __rotate(int32_t a, uint32_t b);
int2 __rotate(int2 a, uint2 b);
int4 __rotate(int4 a, uint4 b);
int8 __rotate(int8 a, uint8 b);
int16 __rotate(int16 a, uint16 b);
int32_t __rotate(int32_t a, uint8_t b);
int2 __rotate(int2 a, uchar2 b);
int4 __rotate(int4 a, uchar4 b);
int8 __rotate(int8 a, uchar8 b);
int16 __rotate(int16 a, uchar16 b);
int64_t __saturate(int64_t a, uint8_t b);
long2 __saturate(long2 a, uchar2 b);
long4 __saturate(long4 a, uchar4 b);
long8 __saturate(long8 a, uchar8 b);
int16_t __saturate(int16_t a, uint8_t b);
short2 __saturate(short2 a, uchar2 b);
short4 __saturate(short4 a, uchar4 b);
short8 __saturate(short8 a, uchar8 b);
short16 __saturate(short16 a, uchar16 b);
short32 __saturate(short32 a, uchar32 b);
uint64_t __saturate(uint64_t a, uint8_t b);
ulong2 __saturate(ulong2 a, uchar2 b);
ulong4 __saturate(ulong4 a, uchar4 b);
ulong8 __saturate(ulong8 a, uchar8 b);
uint16_t __saturate(uint16_t a, uint8_t b);
ushort2 __saturate(ushort2 a, uchar2 b);
ushort4 __saturate(ushort4 a, uchar4 b);
ushort8 __saturate(ushort8 a, uchar8 b);
ushort16 __saturate(ushort16 a, uchar16 b);
ushort32 __saturate(ushort32 a, uchar32 b);
uint32_t __saturate(uint32_t a, uint8_t b);
uint2 __saturate(uint2 a, uchar2 b);
uint4 __saturate(uint4 a, uchar4 b);
uint8 __saturate(uint8 a, uchar8 b);
uint16 __saturate(uint16 a, uchar16 b);
int32_t __saturate(int32_t a, uint8_t b);
int2 __saturate(int2 a, uchar2 b);
int4 __saturate(int4 a, uchar4 b);
int8 __saturate(int8 a, uchar8 b);
int16 __saturate(int16 a, uchar16 b);
uint64_t __saturate_s2u(int64_t a, uint8_t b);
ulong2 __saturate_s2u(long2 a, uchar2 b);
ulong4 __saturate_s2u(long4 a, uchar4 b);
ulong8 __saturate_s2u(long8 a, uchar8 b);
uint16_t __saturate_s2u(int16_t a, uint8_t b);
ushort2 __saturate_s2u(short2 a, uchar2 b);
ushort4 __saturate_s2u(short4 a, uchar4 b);
ushort8 __saturate_s2u(short8 a, uchar8 b);
ushort16 __saturate_s2u(short16 a, uchar16 b);
ushort32 __saturate_s2u(short32 a, uchar32 b);
uint32_t __saturate_s2u(int32_t a, uint8_t b);
uint2 __saturate_s2u(int2 a, uchar2 b);
uint4 __saturate_s2u(int4 a, uchar4 b);
uint8 __saturate_s2u(int8 a, uchar8 b);
uint16 __saturate_s2u(int16 a, uchar16 b);
double __scale(double a, uint64_t b);
double2 __scale(double2 a, ulong2 b);
double4 __scale(double4 a, ulong4 b);
double8 __scale(double8 a, ulong8 b);
float __scale(float a, uint32_t b);
float2 __scale(float2 a, uint2 b);
float4 __scale(float4 a, uint4 b);
float8 __scale(float8 a, uint8 b);
float16 __scale(float16 a, uint16 b);
char64 __scatter_set_bits(__vpred a, char64 b);
char64 __scatter_unset_bits(__vpred a, char64 b);
int8_t __select(__vpred a, int8_t b, int8_t c);
char2 __select(__vpred a, char2 b, char2 c);
char4 __select(__vpred a, char4 b, char4 c);
char8 __select(__vpred a, char8 b, char8 c);
char16 __select(__vpred a, char16 b, char16 c);
char32 __select(__vpred a, char32 b, char32 c);
char64 __select(__vpred a, char64 b, char64 c);
int16_t __select(__vpred a, int16_t b, int16_t c);
short2 __select(__vpred a, short2 b, short2 c);
short4 __select(__vpred a, short4 b, short4 c);
short8 __select(__vpred a, short8 b, short8 c);
short16 __select(__vpred a, short16 b, short16 c);
short32 __select(__vpred a, short32 b, short32 c);
int32_t __select(__vpred a, int32_t b, int32_t c);
int2 __select(__vpred a, int2 b, int2 c);
int4 __select(__vpred a, int4 b, int4 c);
int8 __select(__vpred a, int8 b, int8 c);
int16 __select(__vpred a, int16 b, int16 c);
int64_t __select(__vpred a, int64_t b, int64_t c);
long2 __select(__vpred a, long2 b, long2 c);
long4 __select(__vpred a, long4 b, long4 c);
long8 __select(__vpred a, long8 b, long8 c);
int32_t __select(__vpred a, int32_t b, uint32_t c);
int2 __select(__vpred a, int2 b, uint2 c);
int4 __select(__vpred a, int4 b, uint4 c);
int8 __select(__vpred a, int8 b, uint8 c);
int16 __select(__vpred a, int16 b, uint16 c);
cchar __select(__vpred a, cchar b, cchar c);
cchar2 __select(__vpred a, cchar2 b, cchar2 c);
cchar4 __select(__vpred a, cchar4 b, cchar4 c);
cchar8 __select(__vpred a, cchar8 b, cchar8 c);
cchar16 __select(__vpred a, cchar16 b, cchar16 c);
cchar32 __select(__vpred a, cchar32 b, cchar32 c);
uint8_t __select(__vpred a, uint8_t b, uint8_t c);
uchar2 __select(__vpred a, uchar2 b, uchar2 c);
uchar4 __select(__vpred a, uchar4 b, uchar4 c);
uchar8 __select(__vpred a, uchar8 b, uchar8 c);
uchar16 __select(__vpred a, uchar16 b, uchar16 c);
uchar32 __select(__vpred a, uchar32 b, uchar32 c);
uchar64 __select(__vpred a, uchar64 b, uchar64 c);
cshort __select(__vpred a, cshort b, cshort c);
cshort2 __select(__vpred a, cshort2 b, cshort2 c);
cshort4 __select(__vpred a, cshort4 b, cshort4 c);
cshort8 __select(__vpred a, cshort8 b, cshort8 c);
cshort16 __select(__vpred a, cshort16 b, cshort16 c);
uint16_t __select(__vpred a, uint16_t b, uint16_t c);
ushort2 __select(__vpred a, ushort2 b, ushort2 c);
ushort4 __select(__vpred a, ushort4 b, ushort4 c);
ushort8 __select(__vpred a, ushort8 b, ushort8 c);
ushort16 __select(__vpred a, ushort16 b, ushort16 c);
ushort32 __select(__vpred a, ushort32 b, ushort32 c);
float __select(__vpred a, float b, float c);
float2 __select(__vpred a, float2 b, float2 c);
float4 __select(__vpred a, float4 b, float4 c);
float8 __select(__vpred a, float8 b, float8 c);
float16 __select(__vpred a, float16 b, float16 c);
cfloat __select(__vpred a, cfloat b, cfloat c);
cfloat2 __select(__vpred a, cfloat2 b, cfloat2 c);
cfloat4 __select(__vpred a, cfloat4 b, cfloat4 c);
cfloat8 __select(__vpred a, cfloat8 b, cfloat8 c);
cint __select(__vpred a, cint b, cint c);
cint2 __select(__vpred a, cint2 b, cint2 c);
cint4 __select(__vpred a, cint4 b, cint4 c);
cint8 __select(__vpred a, cint8 b, cint8 c);
uint32_t __select(__vpred a, uint32_t b, uint32_t c);
uint2 __select(__vpred a, uint2 b, uint2 c);
uint4 __select(__vpred a, uint4 b, uint4 c);
uint8 __select(__vpred a, uint8 b, uint8 c);
uint16 __select(__vpred a, uint16 b, uint16 c);
double __select(__vpred a, double b, double c);
double2 __select(__vpred a, double2 b, double2 c);
double4 __select(__vpred a, double4 b, double4 c);
double8 __select(__vpred a, double8 b, double8 c);
cdouble __select(__vpred a, cdouble b, cdouble c);
cdouble2 __select(__vpred a, cdouble2 b, cdouble2 c);
cdouble4 __select(__vpred a, cdouble4 b, cdouble4 c);
clong __select(__vpred a, clong b, clong c);
clong2 __select(__vpred a, clong2 b, clong2 c);
clong4 __select(__vpred a, clong4 b, clong4 c);
uint64_t __select(__vpred a, uint64_t b, uint64_t c);
ulong2 __select(__vpred a, ulong2 b, ulong2 c);
ulong4 __select(__vpred a, ulong4 b, ulong4 c);
ulong8 __select(__vpred a, ulong8 b, ulong8 c);
float __select(__vpred a, float b, uint32_t c);
float2 __select(__vpred a, float2 b, uint2 c);
float4 __select(__vpred a, float4 b, uint4 c);
float8 __select(__vpred a, float8 b, uint8 c);
float16 __select(__vpred a, float16 b, uint16 c);
cfloat __select(__vpred a, cfloat b, uint2 c);
cfloat2 __select(__vpred a, cfloat2 b, uint4 c);
cfloat4 __select(__vpred a, cfloat4 b, uint8 c);
cfloat8 __select(__vpred a, cfloat8 b, uint16 c);
cint __select(__vpred a, cint b, uint2 c);
cint2 __select(__vpred a, cint2 b, uint4 c);
cint4 __select(__vpred a, cint4 b, uint8 c);
cint8 __select(__vpred a, cint8 b, uint16 c);
int32_t __set(int32_t a, int32_t b);
int32_t __set_rrr(int32_t a, int32_t b);
int64_t __shift_left(int64_t a, int32_t b);
int64_t __shift_left(int64_t a, uint8_t b);
uint64_t __shift_left(uint64_t a, uint32_t b);
uint64_t __shift_left(uint64_t a, uint8_t b);
int32_t __shift_left(int32_t a, int32_t b);
int32_t __shift_left(int32_t a, uint8_t b);
uint32_t __shift_left(uint32_t a, uint32_t b);
uint32_t __shift_left(uint32_t a, uint8_t b);
char4 __shift_left(char4 a, int32_t b);
char8 __shift_left(char8 a, int2 b);
char16 __shift_left(char16 a, int4 b);
char32 __shift_left(char32 a, int8 b);
char64 __shift_left(char64 a, int16 b);
int8_t __shift_left(int8_t a, int8_t b);
char2 __shift_left(char2 a, char2 b);
char4 __shift_left(char4 a, char4 b);
char8 __shift_left(char8 a, char8 b);
char16 __shift_left(char16 a, char16 b);
char32 __shift_left(char32 a, char32 b);
char64 __shift_left(char64 a, char64 b);
uchar4 __shift_left(uchar4 a, uint32_t b);
uchar8 __shift_left(uchar8 a, uint2 b);
uchar16 __shift_left(uchar16 a, uint4 b);
uchar32 __shift_left(uchar32 a, uint8 b);
uchar64 __shift_left(uchar64 a, uint16 b);
uint8_t __shift_left(uint8_t a, uint8_t b);
uchar2 __shift_left(uchar2 a, uchar2 b);
uchar4 __shift_left(uchar4 a, uchar4 b);
uchar8 __shift_left(uchar8 a, uchar8 b);
uchar16 __shift_left(uchar16 a, uchar16 b);
uchar32 __shift_left(uchar32 a, uchar32 b);
uchar64 __shift_left(uchar64 a, uchar64 b);
int64_t __shift_left(int64_t a, int64_t b);
long2 __shift_left(long2 a, long2 b);
long4 __shift_left(long4 a, long4 b);
long8 __shift_left(long8 a, long8 b);
uint64_t __shift_left(uint64_t a, uint64_t b);
ulong2 __shift_left(ulong2 a, ulong2 b);
ulong4 __shift_left(ulong4 a, ulong4 b);
ulong8 __shift_left(ulong8 a, ulong8 b);
short2 __shift_left(short2 a, int32_t b);
short4 __shift_left(short4 a, int2 b);
short8 __shift_left(short8 a, int4 b);
short16 __shift_left(short16 a, int8 b);
short32 __shift_left(short32 a, int16 b);
int16_t __shift_left(int16_t a, int16_t b);
short2 __shift_left(short2 a, short2 b);
short4 __shift_left(short4 a, short4 b);
short8 __shift_left(short8 a, short8 b);
short16 __shift_left(short16 a, short16 b);
short32 __shift_left(short32 a, short32 b);
ushort2 __shift_left(ushort2 a, uint32_t b);
ushort4 __shift_left(ushort4 a, uint2 b);
ushort8 __shift_left(ushort8 a, uint4 b);
ushort16 __shift_left(ushort16 a, uint8 b);
ushort32 __shift_left(ushort32 a, uint16 b);
uint16_t __shift_left(uint16_t a, uint16_t b);
ushort2 __shift_left(ushort2 a, ushort2 b);
ushort4 __shift_left(ushort4 a, ushort4 b);
ushort8 __shift_left(ushort8 a, ushort8 b);
ushort16 __shift_left(ushort16 a, ushort16 b);
ushort32 __shift_left(ushort32 a, ushort32 b);
int2 __shift_left(int2 a, int2 b);
int4 __shift_left(int4 a, int4 b);
int8 __shift_left(int8 a, int8 b);
int16 __shift_left(int16 a, int16 b);
uint2 __shift_left(uint2 a, uint2 b);
uint4 __shift_left(uint4 a, uint4 b);
uint8 __shift_left(uint8 a, uint8 b);
uint16 __shift_left(uint16 a, uint16 b);
int8_t __shift_left_conditional(__vpred a, int8_t b, int8_t c);
char2 __shift_left_conditional(__vpred a, char2 b, char2 c);
char4 __shift_left_conditional(__vpred a, char4 b, char4 c);
char8 __shift_left_conditional(__vpred a, char8 b, char8 c);
char16 __shift_left_conditional(__vpred a, char16 b, char16 c);
char32 __shift_left_conditional(__vpred a, char32 b, char32 c);
char64 __shift_left_conditional(__vpred a, char64 b, char64 c);
uint8_t __shift_left_conditional(__vpred a, uint8_t b, uint8_t c);
uchar2 __shift_left_conditional(__vpred a, uchar2 b, uchar2 c);
uchar4 __shift_left_conditional(__vpred a, uchar4 b, uchar4 c);
uchar8 __shift_left_conditional(__vpred a, uchar8 b, uchar8 c);
uchar16 __shift_left_conditional(__vpred a, uchar16 b, uchar16 c);
uchar32 __shift_left_conditional(__vpred a, uchar32 b, uchar32 c);
uchar64 __shift_left_conditional(__vpred a, uchar64 b, uchar64 c);
int16_t __shift_left_conditional(__vpred a, int16_t b, int16_t c);
short2 __shift_left_conditional(__vpred a, short2 b, short2 c);
short4 __shift_left_conditional(__vpred a, short4 b, short4 c);
short8 __shift_left_conditional(__vpred a, short8 b, short8 c);
short16 __shift_left_conditional(__vpred a, short16 b, short16 c);
short32 __shift_left_conditional(__vpred a, short32 b, short32 c);
uint16_t __shift_left_conditional(__vpred a, uint16_t b, uint16_t c);
ushort2 __shift_left_conditional(__vpred a, ushort2 b, ushort2 c);
ushort4 __shift_left_conditional(__vpred a, ushort4 b, ushort4 c);
ushort8 __shift_left_conditional(__vpred a, ushort8 b, ushort8 c);
ushort16 __shift_left_conditional(__vpred a, ushort16 b, ushort16 c);
ushort32 __shift_left_conditional(__vpred a, ushort32 b, ushort32 c);
int32_t __shift_left_conditional(__vpred a, int32_t b, int32_t c);
int2 __shift_left_conditional(__vpred a, int2 b, int2 c);
int4 __shift_left_conditional(__vpred a, int4 b, int4 c);
int8 __shift_left_conditional(__vpred a, int8 b, int8 c);
int16 __shift_left_conditional(__vpred a, int16 b, int16 c);
uint32_t __shift_left_conditional(__vpred a, uint32_t b, uint32_t c);
uint2 __shift_left_conditional(__vpred a, uint2 b, uint2 c);
uint4 __shift_left_conditional(__vpred a, uint4 b, uint4 c);
uint8 __shift_left_conditional(__vpred a, uint8 b, uint8 c);
uint16 __shift_left_conditional(__vpred a, uint16 b, uint16 c);
ulong8 __shift_left_full(ulong8 a, uint8_t b);
ulong8 __shift_left_full(ulong8 a, ulong8 b);
char64 __shift_left_merge(char64 a, char16 b);
char64 __shift_left_merge(char64 a, int8_t b);
char64 __shift_left_merge(char64 a, char2 b);
char64 __shift_left_merge(char64 a, char4 b);
char64 __shift_left_merge(char64 a, char8 b);
int32_t __shift_left_merge(int32_t a, char4 b);
int2 __shift_left_merge(int2 a, char8 b);
int4 __shift_left_merge(int4 a, char16 b);
int8 __shift_left_merge(int8 a, char32 b);
int16 __shift_left_merge(int16 a, char64 b);
int2 __shift_left_round_sat(int64_t a, uint64_t b);
int4 __shift_left_round_sat(long2 a, ulong2 b);
int8 __shift_left_round_sat(long4 a, ulong4 b);
int16 __shift_left_round_sat(long8 a, ulong8 b);
int2 __shift_left_round_sat(int64_t a, uint8_t b);
int4 __shift_left_round_sat(long2 a, uchar2 b);
int8 __shift_left_round_sat(long4 a, uchar4 b);
int16 __shift_left_round_sat(long8 a, uchar8 b);
char4 __shift_left_round_sat(short2 a, uint32_t b);
char8 __shift_left_round_sat(short4 a, uint2 b);
char16 __shift_left_round_sat(short8 a, uint4 b);
char32 __shift_left_round_sat(short16 a, uint8 b);
char64 __shift_left_round_sat(short32 a, uint16 b);
char4 __shift_left_round_sat(short2 a, uint8_t b);
char8 __shift_left_round_sat(short4 a, uchar2 b);
char16 __shift_left_round_sat(short8 a, uchar4 b);
char32 __shift_left_round_sat(short16 a, uchar8 b);
char64 __shift_left_round_sat(short32 a, uchar16 b);
short2 __shift_left_round_sat(int32_t a, uint32_t b);
short4 __shift_left_round_sat(int2 a, uint2 b);
short8 __shift_left_round_sat(int4 a, uint4 b);
short16 __shift_left_round_sat(int8 a, uint8 b);
short32 __shift_left_round_sat(int16 a, uint16 b);
short2 __shift_left_round_sat(int32_t a, uint8_t b);
short4 __shift_left_round_sat(int2 a, uchar2 b);
short8 __shift_left_round_sat(int4 a, uchar4 b);
short16 __shift_left_round_sat(int8 a, uchar8 b);
short32 __shift_left_round_sat(int16 a, uchar16 b);
uint2 __shift_left_round_sat(uint64_t a, uint64_t b);
uint4 __shift_left_round_sat(ulong2 a, ulong2 b);
uint8 __shift_left_round_sat(ulong4 a, ulong4 b);
uint16 __shift_left_round_sat(ulong8 a, ulong8 b);
uint2 __shift_left_round_sat(uint64_t a, uint8_t b);
uint4 __shift_left_round_sat(ulong2 a, uchar2 b);
uint8 __shift_left_round_sat(ulong4 a, uchar4 b);
uint16 __shift_left_round_sat(ulong8 a, uchar8 b);
uchar4 __shift_left_round_sat(ushort2 a, uint32_t b);
uchar8 __shift_left_round_sat(ushort4 a, uint2 b);
uchar16 __shift_left_round_sat(ushort8 a, uint4 b);
uchar32 __shift_left_round_sat(ushort16 a, uint8 b);
uchar64 __shift_left_round_sat(ushort32 a, uint16 b);
uchar4 __shift_left_round_sat(ushort2 a, uint8_t b);
uchar8 __shift_left_round_sat(ushort4 a, uchar2 b);
uchar16 __shift_left_round_sat(ushort8 a, uchar4 b);
uchar32 __shift_left_round_sat(ushort16 a, uchar8 b);
uchar64 __shift_left_round_sat(ushort32 a, uchar16 b);
ushort2 __shift_left_round_sat(uint32_t a, uint32_t b);
ushort4 __shift_left_round_sat(uint2 a, uint2 b);
ushort8 __shift_left_round_sat(uint4 a, uint4 b);
ushort16 __shift_left_round_sat(uint8 a, uint8 b);
ushort32 __shift_left_round_sat(uint16 a, uint16 b);
ushort2 __shift_left_round_sat(uint32_t a, uint8_t b);
ushort4 __shift_left_round_sat(uint2 a, uchar2 b);
ushort8 __shift_left_round_sat(uint4 a, uchar4 b);
ushort16 __shift_left_round_sat(uint8 a, uchar8 b);
ushort32 __shift_left_round_sat(uint16 a, uchar16 b);
uint2 __shift_left_round_sat_to_unsigned(int64_t a, uint64_t b);
uint4 __shift_left_round_sat_to_unsigned(long2 a, ulong2 b);
uint8 __shift_left_round_sat_to_unsigned(long4 a, ulong4 b);
uint16 __shift_left_round_sat_to_unsigned(long8 a, ulong8 b);
uint2 __shift_left_round_sat_to_unsigned(int64_t a, uint8_t b);
uint4 __shift_left_round_sat_to_unsigned(long2 a, uchar2 b);
uint8 __shift_left_round_sat_to_unsigned(long4 a, uchar4 b);
uint16 __shift_left_round_sat_to_unsigned(long8 a, uchar8 b);
uchar4 __shift_left_round_sat_to_unsigned(short2 a, uint32_t b);
uchar8 __shift_left_round_sat_to_unsigned(short4 a, uint2 b);
uchar16 __shift_left_round_sat_to_unsigned(short8 a, uint4 b);
uchar32 __shift_left_round_sat_to_unsigned(short16 a, uint8 b);
uchar64 __shift_left_round_sat_to_unsigned(short32 a, uint16 b);
uchar4 __shift_left_round_sat_to_unsigned(short2 a, uint8_t b);
uchar8 __shift_left_round_sat_to_unsigned(short4 a, uchar2 b);
uchar16 __shift_left_round_sat_to_unsigned(short8 a, uchar4 b);
uchar32 __shift_left_round_sat_to_unsigned(short16 a, uchar8 b);
uchar64 __shift_left_round_sat_to_unsigned(short32 a, uchar16 b);
ushort2 __shift_left_round_sat_to_unsigned(int32_t a, uint32_t b);
ushort4 __shift_left_round_sat_to_unsigned(int2 a, uint2 b);
ushort8 __shift_left_round_sat_to_unsigned(int4 a, uint4 b);
ushort16 __shift_left_round_sat_to_unsigned(int8 a, uint8 b);
ushort32 __shift_left_round_sat_to_unsigned(int16 a, uint16 b);
ushort2 __shift_left_round_sat_to_unsigned(int32_t a, uint8_t b);
ushort4 __shift_left_round_sat_to_unsigned(int2 a, uchar2 b);
ushort8 __shift_left_round_sat_to_unsigned(int4 a, uchar4 b);
ushort16 __shift_left_round_sat_to_unsigned(int8 a, uchar8 b);
ushort32 __shift_left_round_sat_to_unsigned(int16 a, uchar16 b);
short2 __shift_left_sat(short2 a, uint32_t b);
short4 __shift_left_sat(short4 a, uint2 b);
short8 __shift_left_sat(short8 a, uint4 b);
short16 __shift_left_sat(short16 a, uint8 b);
short32 __shift_left_sat(short32 a, uint16 b);
int16_t __shift_left_sat(int16_t a, uint8_t b);
short2 __shift_left_sat(short2 a, uchar2 b);
short4 __shift_left_sat(short4 a, uchar4 b);
short8 __shift_left_sat(short8 a, uchar8 b);
short16 __shift_left_sat(short16 a, uchar16 b);
short32 __shift_left_sat(short32 a, uchar32 b);
ushort2 __shift_left_sat(ushort2 a, uint32_t b);
ushort4 __shift_left_sat(ushort4 a, uint2 b);
ushort8 __shift_left_sat(ushort8 a, uint4 b);
ushort16 __shift_left_sat(ushort16 a, uint8 b);
ushort32 __shift_left_sat(ushort32 a, uint16 b);
uint16_t __shift_left_sat(uint16_t a, uint8_t b);
ushort2 __shift_left_sat(ushort2 a, uchar2 b);
ushort4 __shift_left_sat(ushort4 a, uchar4 b);
ushort8 __shift_left_sat(ushort8 a, uchar8 b);
ushort16 __shift_left_sat(ushort16 a, uchar16 b);
ushort32 __shift_left_sat(ushort32 a, uchar32 b);
uint32_t __shift_left_sat(uint32_t a, uint32_t b);
uint2 __shift_left_sat(uint2 a, uint2 b);
uint4 __shift_left_sat(uint4 a, uint4 b);
uint8 __shift_left_sat(uint8 a, uint8 b);
uint16 __shift_left_sat(uint16 a, uint16 b);
uint32_t __shift_left_sat(uint32_t a, uint8_t b);
uint2 __shift_left_sat(uint2 a, uchar2 b);
uint4 __shift_left_sat(uint4 a, uchar4 b);
uint8 __shift_left_sat(uint8 a, uchar8 b);
uint16 __shift_left_sat(uint16 a, uchar16 b);
int32_t __shift_left_sat(int32_t a, uint32_t b);
int2 __shift_left_sat(int2 a, uint2 b);
int4 __shift_left_sat(int4 a, uint4 b);
int8 __shift_left_sat(int8 a, uint8 b);
int16 __shift_left_sat(int16 a, uint16 b);
int32_t __shift_left_sat(int32_t a, uint8_t b);
int2 __shift_left_sat(int2 a, uchar2 b);
int4 __shift_left_sat(int4 a, uchar4 b);
int8 __shift_left_sat(int8 a, uchar8 b);
int16 __shift_left_sat(int16 a, uchar16 b);
ushort2 __shift_left_sat_to_unsigned(short2 a, uint32_t b);
ushort4 __shift_left_sat_to_unsigned(short4 a, uint2 b);
ushort8 __shift_left_sat_to_unsigned(short8 a, uint4 b);
ushort16 __shift_left_sat_to_unsigned(short16 a, uint8 b);
ushort32 __shift_left_sat_to_unsigned(short32 a, uint16 b);
uint16_t __shift_left_sat_to_unsigned(int16_t a, uint8_t b);
ushort2 __shift_left_sat_to_unsigned(short2 a, uchar2 b);
ushort4 __shift_left_sat_to_unsigned(short4 a, uchar4 b);
ushort8 __shift_left_sat_to_unsigned(short8 a, uchar8 b);
ushort16 __shift_left_sat_to_unsigned(short16 a, uchar16 b);
ushort32 __shift_left_sat_to_unsigned(short32 a, uchar32 b);
uint32_t __shift_left_sat_to_unsigned(int32_t a, uint32_t b);
uint2 __shift_left_sat_to_unsigned(int2 a, uint2 b);
uint4 __shift_left_sat_to_unsigned(int4 a, uint4 b);
uint8 __shift_left_sat_to_unsigned(int8 a, uint8 b);
uint16 __shift_left_sat_to_unsigned(int16 a, uint16 b);
uint32_t __shift_left_sat_to_unsigned(int32_t a, uint8_t b);
uint2 __shift_left_sat_to_unsigned(int2 a, uchar2 b);
uint4 __shift_left_sat_to_unsigned(int4 a, uchar4 b);
uint8 __shift_left_sat_to_unsigned(int8 a, uchar8 b);
uint16 __shift_left_sat_to_unsigned(int16 a, uchar16 b);
uint32_t __shift_left_var(uint32_t a, int32_t b);
uint2 __shift_left_var(uint2 a, int2 b);
uint4 __shift_left_var(uint4 a, int4 b);
uint8 __shift_left_var(uint8 a, int8 b);
uint16 __shift_left_var(uint16 a, int16 b);
int32_t __shift_left_var(int32_t a, int32_t b);
int2 __shift_left_var(int2 a, int2 b);
int4 __shift_left_var(int4 a, int4 b);
int8 __shift_left_var(int8 a, int8 b);
int16 __shift_left_var(int16 a, int16 b);
int32_t __shift_left_var_sat(int32_t a, int32_t b);
int2 __shift_left_var_sat(int2 a, int2 b);
int4 __shift_left_var_sat(int4 a, int4 b);
int8 __shift_left_var_sat(int8 a, int8 b);
int16 __shift_left_var_sat(int16 a, int16 b);
int64_t __shift_right(int64_t a, int32_t b);
int64_t __shift_right(int64_t a, uint8_t b);
uint64_t __shift_right(uint64_t a, uint32_t b);
uint64_t __shift_right(uint64_t a, uint8_t b);
uint32_t __shift_right(uint32_t a, uint32_t b);
uint32_t __shift_right(uint32_t a, uint8_t b);
int32_t __shift_right(int32_t a, int32_t b);
int32_t __shift_right(int32_t a, uint8_t b);
char4 __shift_right(char4 a, int32_t b);
char8 __shift_right(char8 a, int2 b);
char16 __shift_right(char16 a, int4 b);
char32 __shift_right(char32 a, int8 b);
char64 __shift_right(char64 a, int16 b);
int8_t __shift_right(int8_t a, int8_t b);
char2 __shift_right(char2 a, char2 b);
char4 __shift_right(char4 a, char4 b);
char8 __shift_right(char8 a, char8 b);
char16 __shift_right(char16 a, char16 b);
char32 __shift_right(char32 a, char32 b);
char64 __shift_right(char64 a, char64 b);
int64_t __shift_right(int64_t a, int64_t b);
long2 __shift_right(long2 a, long2 b);
long4 __shift_right(long4 a, long4 b);
long8 __shift_right(long8 a, long8 b);
short2 __shift_right(short2 a, int32_t b);
short4 __shift_right(short4 a, int2 b);
short8 __shift_right(short8 a, int4 b);
short16 __shift_right(short16 a, int8 b);
short32 __shift_right(short32 a, int16 b);
int16_t __shift_right(int16_t a, int16_t b);
short2 __shift_right(short2 a, short2 b);
short4 __shift_right(short4 a, short4 b);
short8 __shift_right(short8 a, short8 b);
short16 __shift_right(short16 a, short16 b);
short32 __shift_right(short32 a, short32 b);
uchar4 __shift_right(uchar4 a, uint32_t b);
uchar8 __shift_right(uchar8 a, uint2 b);
uchar16 __shift_right(uchar16 a, uint4 b);
uchar32 __shift_right(uchar32 a, uint8 b);
uchar64 __shift_right(uchar64 a, uint16 b);
uint8_t __shift_right(uint8_t a, uint8_t b);
uchar2 __shift_right(uchar2 a, uchar2 b);
uchar4 __shift_right(uchar4 a, uchar4 b);
uchar8 __shift_right(uchar8 a, uchar8 b);
uchar16 __shift_right(uchar16 a, uchar16 b);
uchar32 __shift_right(uchar32 a, uchar32 b);
uchar64 __shift_right(uchar64 a, uchar64 b);
uint64_t __shift_right(uint64_t a, uint64_t b);
ulong2 __shift_right(ulong2 a, ulong2 b);
ulong4 __shift_right(ulong4 a, ulong4 b);
ulong8 __shift_right(ulong8 a, ulong8 b);
ushort2 __shift_right(ushort2 a, uint32_t b);
ushort4 __shift_right(ushort4 a, uint2 b);
ushort8 __shift_right(ushort8 a, uint4 b);
ushort16 __shift_right(ushort16 a, uint8 b);
ushort32 __shift_right(ushort32 a, uint16 b);
uint16_t __shift_right(uint16_t a, uint16_t b);
ushort2 __shift_right(ushort2 a, ushort2 b);
ushort4 __shift_right(ushort4 a, ushort4 b);
ushort8 __shift_right(ushort8 a, ushort8 b);
ushort16 __shift_right(ushort16 a, ushort16 b);
ushort32 __shift_right(ushort32 a, ushort32 b);
uint2 __shift_right(uint2 a, uint2 b);
uint4 __shift_right(uint4 a, uint4 b);
uint8 __shift_right(uint8 a, uint8 b);
uint16 __shift_right(uint16 a, uint16 b);
int2 __shift_right(int2 a, int2 b);
int4 __shift_right(int4 a, int4 b);
int8 __shift_right(int8 a, int8 b);
int16 __shift_right(int16 a, int16 b);
long8 __shift_right_full(long8 a, uint8_t b);
long8 __shift_right_full(long8 a, ulong8 b);
ulong8 __shift_right_full(ulong8 a, uint8_t b);
ulong8 __shift_right_full(ulong8 a, ulong8 b);
char64 __shift_right_merge(char64 a, char16 b);
char64 __shift_right_merge(char64 a, int8_t b);
char64 __shift_right_merge(char64 a, char2 b);
char64 __shift_right_merge(char64 a, char4 b);
char64 __shift_right_merge(char64 a, char8 b);
int32_t __shift_right_merge(int32_t a, char4 b);
int2 __shift_right_merge(int2 a, char8 b);
int4 __shift_right_merge(int4 a, char16 b);
int8 __shift_right_merge(int8 a, char32 b);
int16 __shift_right_merge(int16 a, char64 b);
char4 __shift_right_round(char4 a, uint32_t b);
char8 __shift_right_round(char8 a, uint2 b);
char16 __shift_right_round(char16 a, uint4 b);
char32 __shift_right_round(char32 a, uint8 b);
char64 __shift_right_round(char64 a, uint16 b);
int8_t __shift_right_round(int8_t a, uint8_t b);
char2 __shift_right_round(char2 a, uchar2 b);
char4 __shift_right_round(char4 a, uchar4 b);
char8 __shift_right_round(char8 a, uchar8 b);
char16 __shift_right_round(char16 a, uchar16 b);
char32 __shift_right_round(char32 a, uchar32 b);
char64 __shift_right_round(char64 a, uchar64 b);
int64_t __shift_right_round(int64_t a, uint32_t b);
long2 __shift_right_round(long2 a, uint2 b);
long4 __shift_right_round(long4 a, uint4 b);
long8 __shift_right_round(long8 a, uint8 b);
int64_t __shift_right_round(int64_t a, uint8_t b);
long2 __shift_right_round(long2 a, uchar2 b);
long4 __shift_right_round(long4 a, uchar4 b);
long8 __shift_right_round(long8 a, uchar8 b);
short2 __shift_right_round(short2 a, uint32_t b);
short4 __shift_right_round(short4 a, uint2 b);
short8 __shift_right_round(short8 a, uint4 b);
short16 __shift_right_round(short16 a, uint8 b);
short32 __shift_right_round(short32 a, uint16 b);
int16_t __shift_right_round(int16_t a, uint8_t b);
short2 __shift_right_round(short2 a, uchar2 b);
short4 __shift_right_round(short4 a, uchar4 b);
short8 __shift_right_round(short8 a, uchar8 b);
short16 __shift_right_round(short16 a, uchar16 b);
short32 __shift_right_round(short32 a, uchar32 b);
int32_t __shift_right_round(int32_t a, uint32_t b);
int2 __shift_right_round(int2 a, uint2 b);
int4 __shift_right_round(int4 a, uint4 b);
int8 __shift_right_round(int8 a, uint8 b);
int16 __shift_right_round(int16 a, uint16 b);
int32_t __shift_right_round(int32_t a, uint8_t b);
int2 __shift_right_round(int2 a, uchar2 b);
int4 __shift_right_round(int4 a, uchar4 b);
int8 __shift_right_round(int8 a, uchar8 b);
int16 __shift_right_round(int16 a, uchar16 b);
uchar4 __shift_right_round(uchar4 a, uint32_t b);
uchar8 __shift_right_round(uchar8 a, uint2 b);
uchar16 __shift_right_round(uchar16 a, uint4 b);
uchar32 __shift_right_round(uchar32 a, uint8 b);
uchar64 __shift_right_round(uchar64 a, uint16 b);
uint8_t __shift_right_round(uint8_t a, uint8_t b);
uchar2 __shift_right_round(uchar2 a, uchar2 b);
uchar4 __shift_right_round(uchar4 a, uchar4 b);
uchar8 __shift_right_round(uchar8 a, uchar8 b);
uchar16 __shift_right_round(uchar16 a, uchar16 b);
uchar32 __shift_right_round(uchar32 a, uchar32 b);
uchar64 __shift_right_round(uchar64 a, uchar64 b);
uint64_t __shift_right_round(uint64_t a, uint32_t b);
ulong2 __shift_right_round(ulong2 a, uint2 b);
ulong4 __shift_right_round(ulong4 a, uint4 b);
ulong8 __shift_right_round(ulong8 a, uint8 b);
uint64_t __shift_right_round(uint64_t a, uint8_t b);
ulong2 __shift_right_round(ulong2 a, uchar2 b);
ulong4 __shift_right_round(ulong4 a, uchar4 b);
ulong8 __shift_right_round(ulong8 a, uchar8 b);
ushort2 __shift_right_round(ushort2 a, uint32_t b);
ushort4 __shift_right_round(ushort4 a, uint2 b);
ushort8 __shift_right_round(ushort8 a, uint4 b);
ushort16 __shift_right_round(ushort16 a, uint8 b);
ushort32 __shift_right_round(ushort32 a, uint16 b);
uint16_t __shift_right_round(uint16_t a, uint8_t b);
ushort2 __shift_right_round(ushort2 a, uchar2 b);
ushort4 __shift_right_round(ushort4 a, uchar4 b);
ushort8 __shift_right_round(ushort8 a, uchar8 b);
ushort16 __shift_right_round(ushort16 a, uchar16 b);
ushort32 __shift_right_round(ushort32 a, uchar32 b);
uint32_t __shift_right_round(uint32_t a, uint32_t b);
uint2 __shift_right_round(uint2 a, uint2 b);
uint4 __shift_right_round(uint4 a, uint4 b);
uint8 __shift_right_round(uint8 a, uint8 b);
uint16 __shift_right_round(uint16 a, uint16 b);
uint32_t __shift_right_round(uint32_t a, uint8_t b);
uint2 __shift_right_round(uint2 a, uchar2 b);
uint4 __shift_right_round(uint4 a, uchar4 b);
uint8 __shift_right_round(uint8 a, uchar8 b);
uint16 __shift_right_round(uint16 a, uchar16 b);
uint32_t __shift_right_var(uint32_t a, int32_t b);
uint2 __shift_right_var(uint2 a, int2 b);
uint4 __shift_right_var(uint4 a, int4 b);
uint8 __shift_right_var(uint8 a, int8 b);
uint16 __shift_right_var(uint16 a, int16 b);
int32_t __shift_right_var(int32_t a, int32_t b);
int2 __shift_right_var(int2 a, int2 b);
int4 __shift_right_var(int4 a, int4 b);
int8 __shift_right_var(int8 a, int8 b);
int16 __shift_right_var(int16 a, int16 b);
int32_t __shift_right_var_sat(int32_t a, int32_t b);
int2 __shift_right_var_sat(int2 a, int2 b);
int4 __shift_right_var_sat(int4 a, int4 b);
int8 __shift_right_var_sat(int8 a, int8 b);
int16 __shift_right_var_sat(int16 a, int16 b);
int64_t __shld_dkd(int64_t a, uint8_t b);
uint64_t __shld_dkd(uint64_t a, uint8_t b);
int64_t __shld_drd(int64_t a, int32_t b);
uint64_t __shld_drd(uint64_t a, uint32_t b);
int32_t __shlw_rkr(int32_t a, uint8_t b);
uint32_t __shlw_rkr(uint32_t a, uint8_t b);
int32_t __shlw_rrr(int32_t a, int32_t b);
uint32_t __shlw_rrr(uint32_t a, uint32_t b);
int16_t __short_to_char_sat(int16_t a);
short2 __short_to_char_sat(short2 a);
short4 __short_to_char_sat(short4 a);
short8 __short_to_char_sat(short8 a);
short16 __short_to_char_sat(short16 a);
short32 __short_to_char_sat(short32 a);
int64_t __shrd_dkd(int64_t a, uint8_t b);
int64_t __shrd_drd(int64_t a, int32_t b);
uint64_t __shrud_dkd(uint64_t a, uint8_t b);
uint64_t __shrud_drd(uint64_t a, uint32_t b);
uint32_t __shruw_rkr(uint32_t a, uint8_t b);
uint32_t __shruw_rrr(uint32_t a, uint32_t b);
int32_t __shrw_rkr(int32_t a, uint8_t b);
int32_t __shrw_rrr(int32_t a, int32_t b);
uint64_t __shuffle_3way(uint2 a, uint2 b);
ulong2 __shuffle_3way(uint4 a, uint4 b);
ulong4 __shuffle_3way(uint8 a, uint8 b);
ulong8 __shuffle_3way(uint16 a, uint16 b);
int64_t __shuffle_3way(int2 a, int2 b);
long2 __shuffle_3way(int4 a, int4 b);
long4 __shuffle_3way(int8 a, int8 b);
long8 __shuffle_3way(int16 a, int16 b);
int64_t __shuffle_bit(int64_t a);
long2 __shuffle_bit(long2 a);
long4 __shuffle_bit(long4 a);
long8 __shuffle_bit(long8 a);
uint64_t __shuffle_bit(uint64_t a);
ulong2 __shuffle_bit(ulong2 a);
ulong4 __shuffle_bit(ulong4 a);
ulong8 __shuffle_bit(ulong8 a);
int32_t __shuffle_bit(int32_t a);
int2 __shuffle_bit(int2 a);
int4 __shuffle_bit(int4 a);
int8 __shuffle_bit(int8 a);
int16 __shuffle_bit(int16 a);
uint32_t __shuffle_bit(uint32_t a);
uint2 __shuffle_bit(uint2 a);
uint4 __shuffle_bit(uint4 a);
uint8 __shuffle_bit(uint8 a);
uint16 __shuffle_bit(uint16 a);
uchar64 __shuffle_stride2(uchar64 a);
char64 __shuffle_stride2(char64 a);
ulong8 __shuffle_stride2(ulong8 a);
long8 __shuffle_stride2(long8 a);
ushort32 __shuffle_stride2(ushort32 a);
short32 __shuffle_stride2(short32 a);
uint16 __shuffle_stride2(uint16 a);
int16 __shuffle_stride2(int16 a);
ulong8 __shuffle_stride2_even_even(ulong8 a, ulong8 b);
long8 __shuffle_stride2_even_even(long8 a, long8 b);
ulong8 __shuffle_stride2_even_odd(ulong8 a, ulong8 b);
long8 __shuffle_stride2_even_odd(long8 a, long8 b);
ulong8 __shuffle_stride2_high_high(ulong8 a, ulong8 b);
long8 __shuffle_stride2_high_high(long8 a, long8 b);
ushort32 __shuffle_stride2_high_high(ushort32 a, ushort32 b);
uint16 __shuffle_stride2_high_high(uint16 a, uint16 b);
ulong8 __shuffle_stride2_low_high(ulong8 a, ulong8 b);
long8 __shuffle_stride2_low_high(long8 a, long8 b);
ulong8 __shuffle_stride2_low_low(ulong8 a, ulong8 b);
long8 __shuffle_stride2_low_low(long8 a, long8 b);
ushort32 __shuffle_stride2_low_low(ushort32 a, ushort32 b);
uint16 __shuffle_stride2_low_low(uint16 a, uint16 b);
ulong8 __shuffle_stride2_odd_odd(ulong8 a, ulong8 b);
long8 __shuffle_stride2_odd_odd(long8 a, long8 b);
uchar64 __shuffle_stride4(uchar64 a);
char64 __shuffle_stride4(char64 a);
ulong8 __shuffle_stride4(ulong8 a);
long8 __shuffle_stride4(long8 a);
ushort32 __shuffle_stride4(ushort32 a);
short32 __shuffle_stride4(short32 a);
uint16 __shuffle_stride4(uint16 a);
int16 __shuffle_stride4(int16 a);
int32_t __smpyhw_rrr(int16_t a, int16_t b);
float16 __sort_asc(float16 a);
int16 __sort_asc(int16 a);
uint16 __sort_asc(uint16 a);
uchar64 __sort_asc_perm(float16 a);
uchar64 __sort_asc_perm(int16 a);
uchar64 __sort_asc_perm(uint16 a);
float16 __sort_desc(float16 a);
int16 __sort_desc(int16 a);
uint16 __sort_desc(uint16 a);
uchar64 __sort_desc_perm(float16 a);
uchar64 __sort_desc_perm(int16 a);
uchar64 __sort_desc_perm(uint16 a);
int32_t __sub_cond(int32_t a, int32_t b);
int2 __sub_cond(int2 a, int2 b);
int4 __sub_cond(int4 a, int4 b);
int8 __sub_cond(int8 a, int8 b);
int16 __sub_cond(int16 a, int16 b);
int64_t __sub_reverse(int64_t a, int64_t b);
uint64_t __sub_reverse(uint64_t a, uint64_t b);
int32_t __sub_reverse(int32_t a, int32_t b);
uint32_t __sub_reverse(uint32_t a, uint32_t b);
int8_t __sub_reverse(int8_t a, int8_t b);
char2 __sub_reverse(char2 a, char2 b);
char4 __sub_reverse(char4 a, char4 b);
char8 __sub_reverse(char8 a, char8 b);
char16 __sub_reverse(char16 a, char16 b);
char32 __sub_reverse(char32 a, char32 b);
char64 __sub_reverse(char64 a, char64 b);
cchar __sub_reverse(cchar a, cchar b);
cchar2 __sub_reverse(cchar2 a, cchar2 b);
cchar4 __sub_reverse(cchar4 a, cchar4 b);
cchar8 __sub_reverse(cchar8 a, cchar8 b);
cchar16 __sub_reverse(cchar16 a, cchar16 b);
cchar32 __sub_reverse(cchar32 a, cchar32 b);
uint8_t __sub_reverse(uint8_t a, uint8_t b);
uchar2 __sub_reverse(uchar2 a, uchar2 b);
uchar4 __sub_reverse(uchar4 a, uchar4 b);
uchar8 __sub_reverse(uchar8 a, uchar8 b);
uchar16 __sub_reverse(uchar16 a, uchar16 b);
uchar32 __sub_reverse(uchar32 a, uchar32 b);
uchar64 __sub_reverse(uchar64 a, uchar64 b);
long2 __sub_reverse(long2 a, long2 b);
long4 __sub_reverse(long4 a, long4 b);
long8 __sub_reverse(long8 a, long8 b);
clong __sub_reverse(clong a, clong b);
clong2 __sub_reverse(clong2 a, clong2 b);
clong4 __sub_reverse(clong4 a, clong4 b);
ulong2 __sub_reverse(ulong2 a, ulong2 b);
ulong4 __sub_reverse(ulong4 a, ulong4 b);
ulong8 __sub_reverse(ulong8 a, ulong8 b);
int16_t __sub_reverse(int16_t a, int16_t b);
short2 __sub_reverse(short2 a, short2 b);
short4 __sub_reverse(short4 a, short4 b);
short8 __sub_reverse(short8 a, short8 b);
short16 __sub_reverse(short16 a, short16 b);
short32 __sub_reverse(short32 a, short32 b);
cshort __sub_reverse(cshort a, cshort b);
cshort2 __sub_reverse(cshort2 a, cshort2 b);
cshort4 __sub_reverse(cshort4 a, cshort4 b);
cshort8 __sub_reverse(cshort8 a, cshort8 b);
cshort16 __sub_reverse(cshort16 a, cshort16 b);
uint16_t __sub_reverse(uint16_t a, uint16_t b);
ushort2 __sub_reverse(ushort2 a, ushort2 b);
ushort4 __sub_reverse(ushort4 a, ushort4 b);
ushort8 __sub_reverse(ushort8 a, ushort8 b);
ushort16 __sub_reverse(ushort16 a, ushort16 b);
ushort32 __sub_reverse(ushort32 a, ushort32 b);
int2 __sub_reverse(int2 a, int2 b);
int4 __sub_reverse(int4 a, int4 b);
int8 __sub_reverse(int8 a, int8 b);
int16 __sub_reverse(int16 a, int16 b);
cint __sub_reverse(cint a, cint b);
cint2 __sub_reverse(cint2 a, cint2 b);
cint4 __sub_reverse(cint4 a, cint4 b);
cint8 __sub_reverse(cint8 a, cint8 b);
uint2 __sub_reverse(uint2 a, uint2 b);
uint4 __sub_reverse(uint4 a, uint4 b);
uint8 __sub_reverse(uint8 a, uint8 b);
uint16 __sub_reverse(uint16 a, uint16 b);
int8_t __sub_sat(int8_t a, int8_t b);
char2 __sub_sat(char2 a, char2 b);
char4 __sub_sat(char4 a, char4 b);
char8 __sub_sat(char8 a, char8 b);
char16 __sub_sat(char16 a, char16 b);
char32 __sub_sat(char32 a, char32 b);
char64 __sub_sat(char64 a, char64 b);
cchar __sub_sat(cchar a, cchar b);
cchar2 __sub_sat(cchar2 a, cchar2 b);
cchar4 __sub_sat(cchar4 a, cchar4 b);
cchar8 __sub_sat(cchar8 a, cchar8 b);
cchar16 __sub_sat(cchar16 a, cchar16 b);
cchar32 __sub_sat(cchar32 a, cchar32 b);
int16_t __sub_sat(int16_t a, int16_t b);
short2 __sub_sat(short2 a, short2 b);
short4 __sub_sat(short4 a, short4 b);
short8 __sub_sat(short8 a, short8 b);
short16 __sub_sat(short16 a, short16 b);
short32 __sub_sat(short32 a, short32 b);
cshort __sub_sat(cshort a, cshort b);
cshort2 __sub_sat(cshort2 a, cshort2 b);
cshort4 __sub_sat(cshort4 a, cshort4 b);
cshort8 __sub_sat(cshort8 a, cshort8 b);
cshort16 __sub_sat(cshort16 a, cshort16 b);
int32_t __sub_sat(int32_t a, int32_t b);
int2 __sub_sat(int2 a, int2 b);
int4 __sub_sat(int4 a, int4 b);
int8 __sub_sat(int8 a, int8 b);
int16 __sub_sat(int16 a, int16 b);
cint __sub_sat(cint a, cint b);
cint2 __sub_sat(cint2 a, cint2 b);
cint4 __sub_sat(cint4 a, cint4 b);
cint8 __sub_sat(cint8 a, cint8 b);
int64_t __subd_ddd(int64_t a, int64_t b);
uint64_t __subd_ddd(uint64_t a, uint64_t b);
double __subdp_ddd(double a, double b);
int64_t __subrd_ddd(int64_t a, int64_t b);
uint64_t __subrd_ddd(uint64_t a, uint64_t b);
int64_t __subrd_dkd(int64_t a, int64_t b);
uint64_t __subrd_dkd(uint64_t a, uint64_t b);
int32_t __subrw_rkr(int32_t a, int32_t b);
uint32_t __subrw_rkr(uint32_t a, uint32_t b);
int32_t __subrw_rrr(int32_t a, int32_t b);
uint32_t __subrw_rrr(uint32_t a, uint32_t b);
float __subsp_rrr(float a, float b);
int32_t __subw_rrr(int32_t a, int32_t b);
uint32_t __subw_rrr(uint32_t a, uint32_t b);
char2 __swap(char2 a);
char4 __swap(char4 a);
char8 __swap(char8 a);
char16 __swap(char16 a);
char32 __swap(char32 a);
char64 __swap(char64 a);
uchar2 __swap(uchar2 a);
uchar4 __swap(uchar4 a);
uchar8 __swap(uchar8 a);
uchar16 __swap(uchar16 a);
uchar32 __swap(uchar32 a);
uchar64 __swap(uchar64 a);
long2 __swap(long2 a);
long4 __swap(long4 a);
long8 __swap(long8 a);
ulong2 __swap(ulong2 a);
ulong4 __swap(ulong4 a);
ulong8 __swap(ulong8 a);
short2 __swap(short2 a);
short4 __swap(short4 a);
short8 __swap(short8 a);
short16 __swap(short16 a);
short32 __swap(short32 a);
ushort2 __swap(ushort2 a);
ushort4 __swap(ushort4 a);
ushort8 __swap(ushort8 a);
ushort16 __swap(ushort16 a);
ushort32 __swap(ushort32 a);
int2 __swap(int2 a);
int4 __swap(int4 a);
int8 __swap(int8 a);
int16 __swap(int16 a);
uint2 __swap(uint2 a);
uint4 __swap(uint4 a);
uint8 __swap(uint8 a);
uint16 __swap(uint16 a);
short2 __unpack_high(char4 a);
short4 __unpack_high(char8 a);
short8 __unpack_high(char16 a);
short16 __unpack_high(char32 a);
short32 __unpack_high(char64 a);
int2 __unpack_high(short4 a);
int4 __unpack_high(short8 a);
int8 __unpack_high(short16 a);
int16 __unpack_high(short32 a);
ushort2 __unpack_high(uchar4 a);
ushort4 __unpack_high(uchar8 a);
ushort8 __unpack_high(uchar16 a);
ushort16 __unpack_high(uchar32 a);
ushort32 __unpack_high(uchar64 a);
uint2 __unpack_high(ushort4 a);
uint4 __unpack_high(ushort8 a);
uint8 __unpack_high(ushort16 a);
uint16 __unpack_high(ushort32 a);
short2 __unpack_low(char4 a);
short4 __unpack_low(char8 a);
short8 __unpack_low(char16 a);
short16 __unpack_low(char32 a);
short32 __unpack_low(char64 a);
int2 __unpack_low(short4 a);
int4 __unpack_low(short8 a);
int8 __unpack_low(short16 a);
int16 __unpack_low(short32 a);
ushort2 __unpack_low(uchar4 a);
ushort4 __unpack_low(uchar8 a);
ushort8 __unpack_low(uchar16 a);
ushort16 __unpack_low(uchar32 a);
ushort32 __unpack_low(uchar64 a);
uint2 __unpack_low(ushort4 a);
uint4 __unpack_low(ushort8 a);
uint8 __unpack_low(ushort16 a);
uint16 __unpack_low(ushort32 a);
uint64_t __unpack_low(uint2 a);
ulong2 __unpack_low(uint4 a);
ulong4 __unpack_low(uint8 a);
ulong8 __unpack_low(uint16 a);
int64_t __unpack_low(int2 a);
long2 __unpack_low(int4 a);
long4 __unpack_low(int8 a);
long8 __unpack_low(int16 a);
char64 __vabsb_vv(char64 a);
long8 __vabsd_vv(long8 a);
double8 __vabsdp_vv(double8 a);
short32 __vabsh_vv(short32 a);
float16 __vabssp_vv(float16 a);
int16 __vabsw_vv(int16 a);
char64 __vaddb_vkv(char64 a, char64 b);
uchar64 __vaddb_vkv(uchar64 a, uchar64 b);
char64 __vaddb_vvv(char64 a, char64 b);
uchar64 __vaddb_vvv(uchar64 a, uchar64 b);
char64 __vaddcb_pvv(__vpred a, char64 b, char64 c);
uchar64 __vaddcb_pvv(__vpred a, uchar64 b, uchar64 c);
long8 __vaddcd_pvv(__vpred a, long8 b, long8 c);
ulong8 __vaddcd_pvv(__vpred a, ulong8 b, ulong8 c);
short32 __vaddch_pvv(__vpred a, short32 b, short32 c);
ushort32 __vaddch_pvv(__vpred a, ushort32 b, ushort32 c);
int16 __vaddcw_pvv(__vpred a, int16 b, int16 c);
uint16 __vaddcw_pvv(__vpred a, uint16 b, uint16 c);
long8 __vaddd_vkv(long8 a, long8 b);
ulong8 __vaddd_vkv(ulong8 a, ulong8 b);
long8 __vaddd_vvv(long8 a, long8 b);
ulong8 __vaddd_vvv(ulong8 a, ulong8 b);
double8 __vadddp_vvv(double8 a, double8 b);
short32 __vaddh_vkv(short32 a, short32 b);
ushort32 __vaddh_vkv(ushort32 a, ushort32 b);
short32 __vaddh_vvv(short32 a, short32 b);
ushort32 __vaddh_vvv(ushort32 a, ushort32 b);
float16 __vaddsp_vvv(float16 a, float16 b);
int16 __vaddw_vkv(int16 a, int16 b);
uint16 __vaddw_vkv(uint16 a, uint16 b);
int16 __vaddw_vvv(int16 a, int16 b);
uint16 __vaddw_vvv(uint16 a, uint16 b);
int16 __vandnw_vkv(int16 a, int16 b);
char64 __vandnw_vvv(char64 a, char64 b);
short32 __vandnw_vvv(short32 a, short32 b);
int16 __vandnw_vvv(int16 a, int16 b);
long8 __vandnw_vvv(long8 a, long8 b);
int16 __vandw_vkv(int16 a, int16 b);
uint16 __vandw_vkv(uint16 a, uint16 b);
char64 __vandw_vvv(char64 a, char64 b);
short32 __vandw_vvv(short32 a, short32 b);
int16 __vandw_vvv(int16 a, int16 b);
long8 __vandw_vvv(long8 a, long8 b);
uchar64 __vandw_vvv(uchar64 a, uchar64 b);
ushort32 __vandw_vvv(ushort32 a, ushort32 b);
uint16 __vandw_vvv(uint16 a, uint16 b);
ulong8 __vandw_vvv(ulong8 a, ulong8 b);
char64 __vapysb_vvv(char64 a, char64 b);
long8 __vapysd_vvv(long8 a, long8 b);
short32 __vapysh_vvv(short32 a, short32 b);
int16 __vapysw_vvv(int16 a, int16 b);
char64 __vavgb_vvv(char64 a, char64 b);
long8 __vavgd_vvv(long8 a, long8 b);
short32 __vavgh_vvv(short32 a, short32 b);
char64 __vavgnrb_vvv(char64 a, char64 b);
long8 __vavgnrd_vvv(long8 a, long8 b);
short32 __vavgnrh_vvv(short32 a, short32 b);
uchar64 __vavgnrub_vvv(uchar64 a, uchar64 b);
ulong8 __vavgnrud_vvv(ulong8 a, ulong8 b);
ushort32 __vavgnruh_vvv(ushort32 a, ushort32 b);
uint16 __vavgnruw_vvv(uint16 a, uint16 b);
int16 __vavgnrw_vvv(int16 a, int16 b);
uchar64 __vavgub_vvv(uchar64 a, uchar64 b);
ulong8 __vavgud_vvv(ulong8 a, ulong8 b);
ushort32 __vavguh_vvv(ushort32 a, ushort32 b);
uint16 __vavguw_vvv(uint16 a, uint16 b);
int16 __vavgw_vvv(int16 a, int16 b);
uint16 __vbinlogw_vv(uint16 a);
char64 __vbitcntb_vv(char64 a);
uchar64 __vbitcntb_vv(uchar64 a);
long8 __vbitcntd_vv(long8 a);
ulong8 __vbitcntd_vv(ulong8 a);
short32 __vbitcnth_vv(short32 a);
ushort32 __vbitcnth_vv(ushort32 a);
int16 __vbitcntw_vv(int16 a);
uint16 __vbitcntw_vv(uint16 a);
long8 __vbitdeald_vv(long8 a);
ulong8 __vbitdeald_vv(ulong8 a);
int16 __vbitdealw_vv(int16 a);
uint16 __vbitdealw_vv(uint16 a);
long8 __vbitrd_vv(long8 a);
ulong8 __vbitrd_vv(ulong8 a);
int16 __vbitrw_vv(int16 a);
uint16 __vbitrw_vv(uint16 a);
long8 __vbitshfld_vv(long8 a);
ulong8 __vbitshfld_vv(ulong8 a);
int16 __vbitshflw_vv(int16 a);
uint16 __vbitshflw_vv(uint16 a);
uchar64 __vbittran8b_vv(uchar64 a);
char64 __vbpackh_vvv(char64 a, char64 b);
uchar64 __vbpackh_vvv(uchar64 a, uchar64 b);
char64 __vbpackl_vvv(char64 a, char64 b);
uchar64 __vbpackl_vvv(uchar64 a, uchar64 b);
long8 __vbunpkd_vv(char8 a);
ulong8 __vbunpkdu_vv(uchar8 a);
short32 __vbunpkh_vv(char32 a);
short32 __vbunpkhh_vv(char64 a);
short32 __vbunpkhl_vv(char64 a);
ushort32 __vbunpkhu_vv(uchar32 a);
ushort32 __vbunpkuhh_vv(uchar64 a);
ushort32 __vbunpkuhl_vv(uchar64 a);
int16 __vbunpkw_vv(char16 a);
uint16 __vbunpkwu_vv(uchar16 a);
cint8 __vccdotp2hw_vvv(cshort16 a, cshort16 b);
void __vccmatmpyhw_vww(cshort16 a, cshort16 b, cshort16 c, cint8::EQUIV_ACCESS_T<0>& d, cint8::EQUIV_ACCESS_T<0>& e);
void __vccmatmpyhw_se_vww(cshort16 a, __SE_REG_PAIR b, cint8::EQUIV_ACCESS_T<0>& c, cint8::EQUIV_ACCESS_T<0>& d);
cshort16 __vccmatmpyr1hh_vwv(cshort16 a, cshort16 b, cshort16 c);
cshort16 __vccmatmpyr1hh_se_vwv(cshort16 a, __SE_REG_PAIR b);
void __vccmpyhw_vvw(cshort16 a, cshort16 b, cint8::EQUIV_ACCESS_T<0>& c, cint8::EQUIV_ACCESS_T<0>& d);
cshort16 __vccmpyr1hh_vvv(cshort16 a, cshort16 b);
cint8 __vccmpyr1ww_vvv(cint8 a, cint8 b);
cint8 __vcdotp2hw_vvv(cshort16 a, cshort16 b);
cshort16 __vcdotpm2opn16b32h_yvvv(ushort32 a, uint64_t b, cchar32 c);
cshort16 __vcdotpm2opn1h32h_yvvv(ushort32 a, uint32_t b, cshort16 c);
cint8 __vcdotpm2opn8h16w_yvvv(ulong8 a, uint4 b, cshort8 c);
cint8 __vcdotpm2opn8w16w_yvvv(ulong8 a, uint4 b, cint8 c);
cshort16 __vcdotpm32opn16b32h_yvvv(ushort32 a, ulong4 b, cchar32 c);
long8 __vclassdp_vv(double8 a);
int16 __vclasssp_vv(float16 a);
void __vcmatmpyhw_vww(cshort16 a, cshort16 b, cshort16 c, cint8::EQUIV_ACCESS_T<0>& d, cint8::EQUIV_ACCESS_T<0>& e);
void __vcmatmpyhw_se_vww(cshort16 a, __SE_REG_PAIR b, cint8::EQUIV_ACCESS_T<0>& c, cint8::EQUIV_ACCESS_T<0>& d);
cshort16 __vcmatmpyr1hh_vwv(cshort16 a, cshort16 b, cshort16 c);
cshort16 __vcmatmpyr1hh_se_vwv(cshort16 a, __SE_REG_PAIR b);
char64 __vcmaxb_vvv(char64 a, char64 b);
short32 __vcmaxh_vvv(short32 a, short32 b);
void __vcmaxpb_vvp(char64 a, char64::EQUIV_ACCESS_T<0>& b, __vpred& c);
void __vcmaxph_vvp(short32 a, short32::EQUIV_ACCESS_T<0>& b, __vpred& c);
__vpred __vcmpeqb_vvp(char64 a, char64 b);
__vpred __vcmpeqb_vvp(uchar64 a, uchar64 b);
__vpred __vcmpeqd_vvp(long8 a, long8 b);
__vpred __vcmpeqd_vvp(ulong8 a, ulong8 b);
__vpred __vcmpeqdp_vvp(double8 a, double8 b);
__vpred __vcmpeqh_vvp(short32 a, short32 b);
__vpred __vcmpeqh_vvp(ushort32 a, ushort32 b);
__vpred __vcmpeqsp_vvp(float16 a, float16 b);
__vpred __vcmpeqw_vvp(int16 a, int16 b);
__vpred __vcmpeqw_vvp(uint16 a, uint16 b);
__vpred __vcmpgeb_vvp(char64 a, char64 b);
__vpred __vcmpged_vvp(long8 a, long8 b);
__vpred __vcmpgeh_vvp(short32 a, short32 b);
__vpred __vcmpgeub_vvp(uchar64 a, uchar64 b);
__vpred __vcmpgeud_vvp(ulong8 a, ulong8 b);
__vpred __vcmpgeuh_vvp(ushort32 a, ushort32 b);
__vpred __vcmpgeuw_vvp(uint16 a, uint16 b);
__vpred __vcmpgew_vvp(int16 a, int16 b);
__vpred __vcmpgtb_vvp(char64 a, char64 b);
__vpred __vcmpgtd_vvp(long8 a, long8 b);
__vpred __vcmpgth_vvp(short32 a, short32 b);
__vpred __vcmpgtub_vvp(uchar64 a, uchar64 b);
__vpred __vcmpgtud_vvp(ulong8 a, ulong8 b);
__vpred __vcmpgtuh_vvp(ushort32 a, ushort32 b);
__vpred __vcmpgtuw_vvp(uint16 a, uint16 b);
__vpred __vcmpgtw_vvp(int16 a, int16 b);
__vpred __vcmpledp_vvp(double8 a, double8 b);
__vpred __vcmplesp_vvp(float16 a, float16 b);
__vpred __vcmpltdp_vvp(double8 a, double8 b);
__vpred __vcmpltsp_vvp(float16 a, float16 b);
void __vcmpyhw_vvw(cshort16 a, cshort16 b, cint8::EQUIV_ACCESS_T<0>& c, cint8::EQUIV_ACCESS_T<0>& d);
cshort16 __vcmpyr1hh_vvv(cshort16 a, cshort16 b);
cint8 __vcmpyr1ww_vvv(cint8 a, cint8 b);
cshort16 __vcmpyrhh_vvv(cshort16 a, cshort16 b);
void __vcmpysp_vvw(cfloat8 a, cfloat8 b, float16::EQUIV_ACCESS_T<0>& c, float16::EQUIV_ACCESS_T<0>& d);
cshort16 __vcrot270h_vv(cshort16 a);
cfloat8 __vcrot270sp_vv(cfloat8 a);
cint8 __vcrot270w_vv(cint8 a);
cshort16 __vcrot90h_vv(cshort16 a);
cfloat8 __vcrot90sp_vv(cfloat8 a);
cint8 __vcrot90w_vv(cint8 a);
uchar64 __vdeal2b_vv(uchar64 a);
char64 __vdeal2b_vv(char64 a);
ushort32 __vdeal2h_vv(ushort32 a);
short32 __vdeal2h_vv(short32 a);
uint16 __vdeal2w_vv(uint16 a);
int16 __vdeal2w_vv(int16 a);
uchar64 __vdeal4b_vv(uchar64 a);
char64 __vdeal4b_vv(char64 a);
ushort32 __vdeal4h_vv(ushort32 a);
short32 __vdeal4h_vv(short32 a);
void __vdotp2hd_vvw(short32 a, short32 b, long8::EQUIV_ACCESS_T<0>& c, long8::EQUIV_ACCESS_T<0>& d);
int16 __vdotp2hw_vvv(short32 a, short32 b);
long8 __vdotp2nwd_vvv(int16 a, int16 b);
long8 __vdotp2nxwd_vvv(int16 a, int16 b);
short32 __vdotp2subh_vvv(char64 a, uchar64 b);
void __vdotp2suhd_vvw(short32 a, ushort32 b, long8::EQUIV_ACCESS_T<0>& c, long8::EQUIV_ACCESS_T<0>& d);
int16 __vdotp2suhw_vvv(short32 a, ushort32 b);
ushort32 __vdotp2ubh_vvv(uchar64 a, uchar64 b);
void __vdotp2uhd_vvw(ushort32 a, ushort32 b, ulong8::EQUIV_ACCESS_T<0>& c, ulong8::EQUIV_ACCESS_T<0>& d);
uint16 __vdotp2uhw_vvv(ushort32 a, ushort32 b);
long8 __vdotp2wd_vvv(int16 a, int16 b);
long8 __vdotp2xwd_vvv(int16 a, int16 b);
long8 __vdotp4hd_vvv(short32 a, short32 b);
int16 __vdotp4hw_wwv(short32 a, short32 b, short32 c, short32 d);
int16 __vdotp4hw_se1_wwv(__SE_REG_PAIR a, short32 b, short32 c);
int16 __vdotp4hw_se2_wwv(short32 a, short32 b, __SE_REG_PAIR c);
int16 __vdotp4hw_se12_wwv(__SE_REG_PAIR a, __SE_REG_PAIR b);
int16 __vdotp4subw_vvv(char64 a, uchar64 b);
long8 __vdotp4suhd_vvv(short32 a, ushort32 b);
int16 __vdotp4suhw_wwv(short32 a, short32 b, ushort32 c, ushort32 d);
int16 __vdotp4suhw_se1_wwv(__SE_REG_PAIR a, ushort32 b, ushort32 c);
int16 __vdotp4suhw_se2_wwv(short32 a, short32 b, __SE_REG_PAIR c);
int16 __vdotp4suhw_se12_wwv(__SE_REG_PAIR a, __SE_REG_PAIR b);
uint16 __vdotp4ubw_vvv(uchar64 a, uchar64 b);
ulong8 __vdotp4uhd_vvv(ushort32 a, ushort32 b);
int16 __vdotp8subw_vvv(char64 a, uchar64 b);
short32 __vdotpmpn16b32h_yvvv(ushort32 a, ushort32 b, char16 c);
int16 __vdotpmpn16h16w_yvvv(ushort32 a, ushort16 b, short16 c);
long8 __vdotpmpn16w8d_yvvv(ushort32 a, ushort8 b, int16 c);
short16 __vdotpmpn32b16h_yvvv(uint16 a, uint16 b, char32 c);
int16 __vdotpmpn32b16w_yvvv(uint16 a, uint16 b, char32 c);
int8 __vdotpmpn32h8w_yvvv(uint8 a, uint8 b, short32 c);
uint16 __vdotpmpnu16h16w_yvvv(ushort32 a, ushort16 b, ushort16 c);
ulong8 __vdotpmpnu16w8d_yvvv(ushort32 a, ushort8 b, uint16 c);
ushort16 __vdotpmpnu32b16h_yvvv(uint16 a, uint16 b, uchar32 c);
uint16 __vdotpmpnu32b16w_yvvv(uint16 a, uint16 b, uchar32 c);
uint8 __vdotpmpnu32h8w_yvvv(uint8 a, uint8 b, ushort32 c);
long8 __vdpackh_vvv(long8 a, long8 b);
ulong8 __vdpackh_vvv(ulong8 a, ulong8 b);
long8 __vdpackl_vvv(long8 a, long8 b);
ulong8 __vdpackl_vvv(ulong8 a, ulong8 b);
int16 __vdpint_vv(double8 a);
float16 __vdpsp_vv(double8 a);
int16 __vdptrunc_vv(double8 a);
uint16 __vdsad16ou8h8w_vvv(ushort32 a, ushort16 b);
ushort32 __vdsad8ou16b16h_vvv(uchar64 a, uchar32 b);
uint16 __vdsadm16ou8h8w_yvvv(uchar64 a, ushort32 b, ushort16 c);
ushort32 __vdsadm8ou16b16h_yvvv(uchar64 a, uchar64 b, uchar32 c);
short32 __vdsortdd16h_vv(short32 a);
ushort32 __vdsortddu16h_vv(ushort32 a);
short32 __vdsortdi16h_vv(short32 a);
ushort32 __vdsortdiu16h_vv(ushort32 a);
short32 __vdsortid16h_vv(short32 a);
ushort32 __vdsortidu16h_vv(ushort32 a);
short32 __vdsortii16h_vv(short32 a);
ushort32 __vdsortiiu16h_vv(ushort32 a);
uchar64 __vdsortpdd16h_vv(short32 a);
uchar64 __vdsortpddu16h_vv(ushort32 a);
uchar64 __vdsortpdi16h_vv(short32 a);
uchar64 __vdsortpdiu16h_vv(ushort32 a);
uchar64 __vdsortpid16h_vv(short32 a);
uchar64 __vdsortpidu16h_vv(ushort32 a);
uchar64 __vdsortpii16h_vv(short32 a);
uchar64 __vdsortpiiu16h_vv(ushort32 a);
char64 __vdup16b_vv(char4 a);
cchar32 __vdup16b_vv(cchar2 a);
uchar64 __vdup16b_vv(uchar4 a);
short32 __vdup16h_vv(short2 a);
cshort16 __vdup16h_vv(cshort a);
ushort32 __vdup16h_vv(ushort2 a);
char64 __vdup2b_vv(char32 a);
cchar32 __vdup2b_vv(cchar16 a);
uchar64 __vdup2b_vv(uchar32 a);
long8 __vdup2d_vv(long4 a);
clong4 __vdup2d_vv(clong2 a);
ulong8 __vdup2d_vv(ulong4 a);
short32 __vdup2h_vv(short16 a);
cshort16 __vdup2h_vv(cshort8 a);
ushort32 __vdup2h_vv(ushort16 a);
int16 __vdup2w_vv(int8 a);
cint8 __vdup2w_vv(cint4 a);
uint16 __vdup2w_vv(uint8 a);
char64 __vdup32b_vv(char2 a);
cchar32 __vdup32b_vv(cchar a);
uchar64 __vdup32b_vv(uchar2 a);
char64 __vdup4b_vv(char16 a);
cchar32 __vdup4b_vv(cchar8 a);
uchar64 __vdup4b_vv(uchar16 a);
long8 __vdup4d_vv(long2 a);
clong4 __vdup4d_vv(clong a);
ulong8 __vdup4d_vv(ulong2 a);
short32 __vdup4h_vv(short8 a);
cshort16 __vdup4h_vv(cshort4 a);
ushort32 __vdup4h_vv(ushort8 a);
int16 __vdup4w_vv(int4 a);
cint8 __vdup4w_vv(cint2 a);
uint16 __vdup4w_vv(uint4 a);
char64 __vdup8b_vv(char8 a);
cchar32 __vdup8b_vv(cchar4 a);
uchar64 __vdup8b_vv(uchar8 a);
short32 __vdup8h_vv(short4 a);
cshort16 __vdup8h_vv(cshort2 a);
ushort32 __vdup8h_vv(ushort4 a);
int16 __vdup8w_vv(int2 a);
cint8 __vdup8w_vv(cint a);
uint16 __vdup8w_vv(uint2 a);
char64 __vdupb_kv(int8_t a);
uchar64 __vdupb_kv(uint8_t a);
char64 __vdupb_rv(int8_t a);
uchar64 __vdupb_rv(uint8_t a);
long8 __vdupd_dv(int64_t a);
ulong8 __vdupd_dv(uint64_t a);
short32 __vduph_kv(int16_t a);
ushort32 __vduph_kv(uint16_t a);
short32 __vduph_rv(int16_t a);
ushort32 __vduph_rv(uint16_t a);
int16 __vdupw_kv(int32_t a);
uint16 __vdupw_kv(uint32_t a);
int16 __vdupw_rv(int32_t a);
uint16 __vdupw_rv(uint32_t a);
void __vfir4hw_vww(short32 a, __SE_REG_PAIR b, int16::EQUIV_ACCESS_T<0>& c, int16::EQUIV_ACCESS_T<0>& d);
void __vfir4suhw_vww(short32 a, __SE_REG_PAIR b, int16::EQUIV_ACCESS_T<0>& c, int16::EQUIV_ACCESS_T<0>& d);
void __vfir4uhw_vww(ushort32 a, __SE_REG_PAIR b, uint16::EQUIV_ACCESS_T<0>& c, uint16::EQUIV_ACCESS_T<0>& d);
void __vfir8hd_wvw(short32 a, short32 b, __SE_REG c, long8::EQUIV_ACCESS_T<0>& d, long8::EQUIV_ACCESS_T<0>& e);
int16 __vfir8hw_wvv(short32 a, short32 b, __SE_REG c);
void __vfir8suhd_wvw(short32 a, short32 b, __SE_REG c, long8::EQUIV_ACCESS_T<0>& d, long8::EQUIV_ACCESS_T<0>& e);
int16 __vfir8suhw_wvv(short32 a, short32 b, __SE_REG c);
void __vfir8uhd_wvw(ushort32 a, ushort32 b, __SE_REG c, ulong8::EQUIV_ACCESS_T<0>& d, ulong8::EQUIV_ACCESS_T<0>& e);
uint16 __vfir8uhw_wvv(ushort32 a, ushort32 b, __SE_REG c);
char64 __vgatherb_pvv(__vpred a, char64 b);
char64 __vgathernb_pvv(__vpred a, char64 b);
int8_t __vgetb_vkd(char64 a, uint8_t b);
int8_t __vgetb_vrd(char64 a, uint32_t b);
int64_t __vgetd_vkd(long8 a, uint32_t b);
int64_t __vgetd_vrd(long8 a, uint32_t b);
uchar64 __vgetdupb_vrv(uchar64 a, uint32_t b);
char64 __vgetdupb_vrv(char64 a, int32_t b);
ulong8 __vgetdupd_vrv(ulong8 a, uint32_t b);
long8 __vgetdupd_vrv(long8 a, int32_t b);
ushort32 __vgetduph_vrv(ushort32 a, uint32_t b);
short32 __vgetduph_vrv(short32 a, int32_t b);
uint16 __vgetdupw_vrv(uint16 a, uint32_t b);
int16 __vgetdupw_vrv(int16 a, int32_t b);
int16_t __vgeth_vkd(short32 a, uint32_t b);
int16_t __vgeth_vrd(short32 a, uint32_t b);
uint8_t __vgetub_vkd(uchar64 a, uint32_t b);
uint8_t __vgetub_vrd(uchar64 a, uint32_t b);
uint16_t __vgetuh_vkd(ushort32 a, uint32_t b);
uint16_t __vgetuh_vrd(ushort32 a, uint32_t b);
uint32_t __vgetuw_vkd(uint16 a, uint32_t b);
uint32_t __vgetuw_vrd(uint16 a, uint32_t b);
int32_t __vgetw_vkd(int16 a, uint8_t b);
int32_t __vgetw_vrd(int16 a, uint32_t b);
uchar64 __vgmpyb_vvv(uchar64 a, uchar64 b);
uint16 __vgmpyw_vvv(uint16 a, uint16 b);
long8 __vgsatd_vkv(long8 a, uchar8 b);
short32 __vgsath_vkv(short32 a, uchar32 b);
ulong8 __vgsatsud_vkv(long8 a, uchar8 b);
ushort32 __vgsatsuh_vkv(short32 a, uchar32 b);
uint16 __vgsatsuw_vkv(int16 a, uchar16 b);
ulong8 __vgsatud_vkv(ulong8 a, uchar8 b);
ushort32 __vgsatuh_vkv(ushort32 a, uchar32 b);
uint16 __vgsatuw_vkv(uint16 a, uchar16 b);
int16 __vgsatw_vkv(int16 a, uchar16 b);
int64_t __vhadd16w1d_vd(int16 a);
int64_t __vhadd32h1d_vd(short32 a);
int64_t __vhadd64b1d_vd(char64 a);
int64_t __vhadd8d1d_vd(long8 a);
int2 __vhaddeo16h2w_vd(short32 a);
cint __vhaddeo16h2w_vd(cshort16 a);
long2 __vhaddeo8w2d_vv(int16 a);
clong __vhaddeo8w2d_vv(cint8 a);
long4 __vhaddeo8w4d_vvv(int16 a, int16 b);
clong2 __vhaddeo8w4d_vvv(cint8 a, cint8 b);
uint64_t __vhaddu16w1d_vd(uint16 a);
uint64_t __vhaddu32h1d_vd(ushort32 a);
uint64_t __vhaddu64b1d_vd(uchar64 a);
uint64_t __vhaddu8d1d_vd(ulong8 a);
uint2 __vhaddueo16h2w_vd(ushort32 a);
ulong2 __vhaddueo8w2d_vv(uint16 a);
ulong4 __vhaddueo8w4d_vvv(uint16 a, uint16 b);
uchar64 __vhhmv_vvv(uchar64 a, uchar64 b);
uchar64 __vhlmv_vvv(uchar64 a, uchar64 b);
short32 __vhpackh_vvv(short32 a, short32 b);
ushort32 __vhpackh_vvv(ushort32 a, ushort32 b);
short32 __vhpackl_vvv(short32 a, short32 b);
ushort32 __vhpackl_vvv(ushort32 a, ushort32 b);
long8 __vhunpkd_vv(short8 a);
ulong8 __vhunpkdu_vv(ushort8 a);
uint16 __vhunpkuwh_vv(ushort32 a);
uint16 __vhunpkuwl_vv(ushort32 a);
int16 __vhunpkw_vv(short16 a);
int16 __vhunpkwh_vv(short32 a);
int16 __vhunpkwl_vv(short32 a);
uint16 __vhunpkwu_vv(ushort16 a);
int32_t __vhxor16w1w_vr(int16 a);
int16_t __vhxor32h1h_vr(short32 a);
int16_t __vhxor64b1b_vr(char64 a);
int64_t __vhxor8d1d_vd(long8 a);
double8 __vintdph_vv(int16 a);
double8 __vintdpl_vv(int16 a);
double8 __vintdpuh_vv(uint16 a);
double8 __vintdpul_vv(uint16 a);
float16 __vinthsph_vv(short32 a);
float16 __vinthspl_vv(short32 a);
float16 __vinthspuh_vv(ushort32 a);
float16 __vinthspul_vv(ushort32 a);
float16 __vintsp_vv(int16 a);
float16 __vintspu_vv(uint16 a);
uchar64 __vlhmv_vvv(uchar64 a, uchar64 b);
uchar64 __vllmv_vvv(uchar64 a, uchar64 b);
uchar64 __vlmbd0b_vv(uchar64 a);
ulong8 __vlmbd0d_vv(ulong8 a);
ushort32 __vlmbd0h_vv(ushort32 a);
uint16 __vlmbd0w_vv(uint16 a);
uchar64 __vlmbd1b_vv(uchar64 a);
ulong8 __vlmbd1d_vv(ulong8 a);
ushort32 __vlmbd1h_vv(ushort32 a);
uint16 __vlmbd1w_vv(uint16 a);
uchar64 __vlmbdb_vvv(uchar64 a, uchar64 b);
ulong8 __vlmbdd_vvv(ulong8 a, ulong8 b);
ushort32 __vlmbdh_vvv(ushort32 a, ushort32 b);
uint16 __vlmbdw_vvv(uint16 a, uint16 b);
void __vmatmpyhd_vvw(__SE_REG a, __SE_REG b, long8::EQUIV_ACCESS_T<0>& c, long8::EQUIV_ACCESS_T<0>& d);
int16 __vmatmpyhw_vvv(__SE_REG a, __SE_REG b);
void __vmatmpysp_vww(float16 a, float16 b, float16 c, float16::EQUIV_ACCESS_T<0>& d, float16::EQUIV_ACCESS_T<0>& e);
void __vmatmpysp_se_vww(float16 a, __SE_REG_PAIR b, float16::EQUIV_ACCESS_T<0>& c, float16::EQUIV_ACCESS_T<0>& d);
void __vmatmpysuhd_vvw(__SE_REG a, __SE_REG b, long8::EQUIV_ACCESS_T<0>& c, long8::EQUIV_ACCESS_T<0>& d);
int16 __vmatmpysuhw_vvv(__SE_REG a, __SE_REG b);
void __vmatmpyuhd_vvw(__SE_REG a, __SE_REG b, ulong8::EQUIV_ACCESS_T<0>& c, ulong8::EQUIV_ACCESS_T<0>& d);
uint16 __vmatmpyuhw_vvv(__SE_REG a, __SE_REG b);
void __vmatmpyushd_vvw(__SE_REG a, __SE_REG b, long8::EQUIV_ACCESS_T<0>& c, long8::EQUIV_ACCESS_T<0>& d);
int16 __vmatmpyushw_vvv(__SE_REG a, __SE_REG b);
char64 __vmaxb_vvv(char64 a, char64 b);
long8 __vmaxd_vvv(long8 a, long8 b);
double8 __vmaxdp_vvv(double8 a, double8 b);
short32 __vmaxh_vvv(short32 a, short32 b);
void __vmaxpb_vvp(char64 a, char64::EQUIV_ACCESS_T<0>& b, __vpred& c);
void __vmaxpd_vvp(long8 a, long8::EQUIV_ACCESS_T<0>& b, __vpred& c);
void __vmaxph_vvp(short32 a, short32::EQUIV_ACCESS_T<0>& b, __vpred& c);
void __vmaxpw_vvp(int16 a, int16::EQUIV_ACCESS_T<0>& b, __vpred& c);
float16 __vmaxsp_vvv(float16 a, float16 b);
uchar64 __vmaxub_vvv(uchar64 a, uchar64 b);
ulong8 __vmaxud_vvv(ulong8 a, ulong8 b);
ushort32 __vmaxuh_vvv(ushort32 a, ushort32 b);
void __vmaxupb_vvp(uchar64 a, uchar64::EQUIV_ACCESS_T<0>& b, __vpred& c);
void __vmaxupd_vvp(ulong8 a, ulong8::EQUIV_ACCESS_T<0>& b, __vpred& c);
void __vmaxuph_vvp(ushort32 a, ushort32::EQUIV_ACCESS_T<0>& b, __vpred& c);
void __vmaxupw_vvp(uint16 a, uint16::EQUIV_ACCESS_T<0>& b, __vpred& c);
uint16 __vmaxuw_vvv(uint16 a, uint16 b);
int16 __vmaxw_vvv(int16 a, int16 b);
char64 __vminb_vvv(char64 a, char64 b);
long8 __vmind_vvv(long8 a, long8 b);
double8 __vmindp_vvv(double8 a, double8 b);
short32 __vminh_vvv(short32 a, short32 b);
void __vminpb_vvp(char64 a, char64::EQUIV_ACCESS_T<0>& b, __vpred& c);
void __vminpd_vvp(long8 a, long8::EQUIV_ACCESS_T<0>& b, __vpred& c);
void __vminph_vvp(short32 a, short32::EQUIV_ACCESS_T<0>& b, __vpred& c);
void __vminpw_vvp(int16 a, int16::EQUIV_ACCESS_T<0>& b, __vpred& c);
float16 __vminsp_vvv(float16 a, float16 b);
uchar64 __vminub_vvv(uchar64 a, uchar64 b);
ulong8 __vminud_vvv(ulong8 a, ulong8 b);
ushort32 __vminuh_vvv(ushort32 a, ushort32 b);
void __vminupb_vvp(uchar64 a, uchar64::EQUIV_ACCESS_T<0>& b, __vpred& c);
void __vminupd_vvp(ulong8 a, ulong8::EQUIV_ACCESS_T<0>& b, __vpred& c);
void __vminuph_vvp(ushort32 a, ushort32::EQUIV_ACCESS_T<0>& b, __vpred& c);
void __vminupw_vvp(uint16 a, uint16::EQUIV_ACCESS_T<0>& b, __vpred& c);
uint16 __vminuw_vvv(uint16 a, uint16 b);
int16 __vminw_vvv(int16 a, int16 b);
char64 __vmpybb_vvv(char64 a, char64 b);
uchar64 __vmpybb_vvv(uchar64 a, uchar64 b);
long8 __vmpydd_vvv(long8 a, long8 b);
ulong8 __vmpydd_vvv(ulong8 a, ulong8 b);
double8 __vmpydp_vvv(double8 a, double8 b);
short32 __vmpyhh_vvv(short32 a, short32 b);
ushort32 __vmpyhh_vvv(ushort32 a, ushort32 b);
void __vmpyhw_vvw(short32 a, short32 b, int16::EQUIV_ACCESS_T<0>& c, int16::EQUIV_ACCESS_T<0>& d);
void __vmpysp2dp_vvw(float16 a, float16 b, double8::EQUIV_ACCESS_T<0>& c, double8::EQUIV_ACCESS_T<0>& d);
float16 __vmpysp_vvv(float16 a, float16 b);
void __vmpysubh_vvw(char64 a, uchar64 b, short32::EQUIV_ACCESS_T<0>& c, short32::EQUIV_ACCESS_T<0>& d);
void __vmpysuhw_vvw(short32 a, ushort32 b, int16::EQUIV_ACCESS_T<0>& c, int16::EQUIV_ACCESS_T<0>& d);
void __vmpysuwd_vvw(int16 a, uint16 b, long8::EQUIV_ACCESS_T<0>& c, long8::EQUIV_ACCESS_T<0>& d);
void __vmpyubh_vvw(uchar64 a, uchar64 b, ushort32::EQUIV_ACCESS_T<0>& c, ushort32::EQUIV_ACCESS_T<0>& d);
void __vmpyudq_vvw(ulong8 a, ulong8 b, ulong8::EQUIV_ACCESS_T<0>& c, ulong8::EQUIV_ACCESS_T<0>& d);
void __vmpyuhw_vvw(ushort32 a, ushort32 b, uint16::EQUIV_ACCESS_T<0>& c, uint16::EQUIV_ACCESS_T<0>& d);
void __vmpyuwd_vvw(uint16 a, uint16 b, ulong8::EQUIV_ACCESS_T<0>& c, ulong8::EQUIV_ACCESS_T<0>& d);
void __vmpywd_vvw(int16 a, int16 b, long8::EQUIV_ACCESS_T<0>& c, long8::EQUIV_ACCESS_T<0>& d);
int16 __vmpyww_vvv(int16 a, int16 b);
uint16 __vmpyww_vvv(uint16 a, uint16 b);
char64 __vnandw_vvv(char64 a, char64 b);
short32 __vnandw_vvv(short32 a, short32 b);
int16 __vnandw_vvv(int16 a, int16 b);
long8 __vnandw_vvv(long8 a, long8 b);
uchar64 __vnandw_vvv(uchar64 a, uchar64 b);
ushort32 __vnandw_vvv(ushort32 a, ushort32 b);
uint16 __vnandw_vvv(uint16 a, uint16 b);
ulong8 __vnandw_vvv(ulong8 a, ulong8 b);
ushort32 __vnorm2uh_vv(ushort32 a);
uint16 __vnorm2uw_vv(uint16 a);
char64 __vnormb_vv(char64 a);
long8 __vnormd_vv(long8 a);
short32 __vnormh_vv(short32 a);
int16 __vnormw_vv(int16 a);
char64 __vnorw_vvv(char64 a, char64 b);
short32 __vnorw_vvv(short32 a, short32 b);
int16 __vnorw_vvv(int16 a, int16 b);
long8 __vnorw_vvv(long8 a, long8 b);
void __vopmatmpysp_vvw(float16 a, float16 b, float16::EQUIV_ACCESS_T<0>& c, float16::EQUIV_ACCESS_T<0>& d);
int16 __vornw_vkv(int16 a, int16 b);
char64 __vornw_vvv(char64 a, char64 b);
short32 __vornw_vvv(short32 a, short32 b);
int16 __vornw_vvv(int16 a, int16 b);
long8 __vornw_vvv(long8 a, long8 b);
int16 __vorw_vkv(int16 a, int16 b);
uint16 __vorw_vkv(uint16 a, uint16 b);
char64 __vorw_vvv(char64 a, char64 b);
short32 __vorw_vvv(short32 a, short32 b);
int16 __vorw_vvv(int16 a, int16 b);
long8 __vorw_vvv(long8 a, long8 b);
uchar64 __vorw_vvv(uchar64 a, uchar64 b);
ushort32 __vorw_vvv(ushort32 a, ushort32 b);
uint16 __vorw_vvv(uint16 a, uint16 b);
ulong8 __vorw_vvv(ulong8 a, ulong8 b);
char64 __vpackh2_vvv(char64 a, char64 b);
short32 __vpackh2_vvv(short32 a, short32 b);
int16 __vpackh2_vvv(int16 a, int16 b);
long8 __vpackh2_vvv(long8 a, long8 b);
char64 __vpackh4_vvv(char64 a, char64 b);
short32 __vpackh4_vvv(short32 a, short32 b);
int16 __vpackh4_vvv(int16 a, int16 b);
long8 __vpackh4_vvv(long8 a, long8 b);
char64 __vpackhl2_vvv(char64 a, char64 b);
short32 __vpackhl2_vvv(short32 a, short32 b);
int16 __vpackhl2_vvv(int16 a, int16 b);
long8 __vpackhl2_vvv(long8 a, long8 b);
char64 __vpackl2_vvv(char64 a, char64 b);
short32 __vpackl2_vvv(short32 a, short32 b);
int16 __vpackl2_vvv(int16 a, int16 b);
long8 __vpackl2_vvv(long8 a, long8 b);
char64 __vpackl4_vvv(char64 a, char64 b);
short32 __vpackl4_vvv(short32 a, short32 b);
int16 __vpackl4_vvv(int16 a, int16 b);
long8 __vpackl4_vvv(long8 a, long8 b);
char64 __vpacklh2_vvv(char64 a, char64 b);
short32 __vpacklh2_vvv(short32 a, short32 b);
int16 __vpacklh2_vvv(int16 a, int16 b);
long8 __vpacklh2_vvv(long8 a, long8 b);
uchar64 __vpacklh2_vvv(uchar64 a, uchar64 b);
ushort32 __vpacklh2_vvv(ushort32 a, ushort32 b);
uint16 __vpacklh2_vvv(uint16 a, uint16 b);
ulong8 __vpacklh2_vvv(ulong8 a, ulong8 b);
char64 __vpacklh4_vvv(char64 a, char64 b);
short32 __vpacklh4_vvv(short32 a, short32 b);
int16 __vpacklh4_vvv(int16 a, int16 b);
long8 __vpacklh4_vvv(long8 a, long8 b);
uchar64 __vpacklh4_vvv(uchar64 a, uchar64 b);
ushort32 __vpacklh4_vvv(ushort32 a, ushort32 b);
uint16 __vpacklh4_vvv(uint16 a, uint16 b);
ulong8 __vpacklh4_vvv(ulong8 a, ulong8 b);
char64 __vpackp2_vvv(char64 a, char64 b);
short32 __vpackp2_vvv(short32 a, short32 b);
int16 __vpackp2_vvv(int16 a, int16 b);
long8 __vpackp2_vvv(long8 a, long8 b);
uchar64 __vpackp2_vvv(uchar64 a, uchar64 b);
ushort32 __vpackp2_vvv(ushort32 a, ushort32 b);
uint16 __vpackp2_vvv(uint16 a, uint16 b);
ulong8 __vpackp2_vvv(ulong8 a, ulong8 b);
int16 __vpackw_vvv(int16 a, int16 b);
uint16 __vpackw_vvv(uint16 a, uint16 b);
char64 __vpackx2_vvv(char64 a, char64 b);
short32 __vpackx2_vvv(short32 a, short32 b);
int16 __vpackx2_vvv(int16 a, int16 b);
long8 __vpackx2_vvv(long8 a, long8 b);
uchar64 __vpackx2_vvv(uchar64 a, uchar64 b);
ushort32 __vpackx2_vvv(ushort32 a, ushort32 b);
uint16 __vpackx2_vvv(uint16 a, uint16 b);
ulong8 __vpackx2_vvv(ulong8 a, ulong8 b);
uchar64 __vperm_vvv(uchar64 a, uchar64 b);
uchar64 __vperm_yvv(uchar64 a, uchar64 b);
uchar64 __vpermeeb_yvvv(uchar64 a, uchar64 b, uchar64 c);
uchar64 __vpermeed_yvvv(uchar64 a, uchar64 b, uchar64 c);
uchar64 __vpermeeh_yvvv(uchar64 a, uchar64 b, uchar64 c);
uchar64 __vpermeeq_yvvv(uchar64 a, uchar64 b, uchar64 c);
uchar64 __vpermeew_yvvv(uchar64 a, uchar64 b, uchar64 c);
uchar64 __vpermeob_yvvv(uchar64 a, uchar64 b, uchar64 c);
uchar64 __vpermeod_yvvv(uchar64 a, uchar64 b, uchar64 c);
uchar64 __vpermeoh_yvvv(uchar64 a, uchar64 b, uchar64 c);
uchar64 __vpermeoq_yvvv(uchar64 a, uchar64 b, uchar64 c);
uchar64 __vpermeow_yvvv(uchar64 a, uchar64 b, uchar64 c);
uchar64 __vpermhh_yvvv(uchar64 a, uchar64 b, uchar64 c);
uchar64 __vpermlh_yvvv(uchar64 a, uchar64 b, uchar64 c);
uchar64 __vpermll_yvvv(uchar64 a, uchar64 b, uchar64 c);
uchar64 __vpermoob_yvvv(uchar64 a, uchar64 b, uchar64 c);
uchar64 __vpermood_yvvv(uchar64 a, uchar64 b, uchar64 c);
uchar64 __vpermooh_yvvv(uchar64 a, uchar64 b, uchar64 c);
uchar64 __vpermooq_yvvv(uchar64 a, uchar64 b, uchar64 c);
uchar64 __vpermoow_yvvv(uchar64 a, uchar64 b, uchar64 c);
uint16 __vppackdup16w_pv(__vpred a);
uint16 __vppackdup8w_pv(__vpred a);
uchar64 __vputb_rkv(uint8_t a, uint8_t b, uchar64 c);
char64 __vputb_rkv(int8_t a, int8_t b, char64 c);
ulong8 __vputd_dkv(uint64_t a, uint8_t b, ulong8 c);
long8 __vputd_dkv(int64_t a, int8_t b, long8 c);
ushort32 __vputh_rkv(uint16_t a, uint8_t b, ushort32 c);
short32 __vputh_rkv(int16_t a, int8_t b, short32 c);
uint16 __vputw_rkv(uint32_t a, uint8_t b, uint16 c);
int16 __vputw_rkv(int32_t a, int8_t b, int16 c);
char64 __vpxpnd_pv(__vpred a);
double8 __vrcpdp_vv(double8 a);
float16 __vrcpsp_vv(float16 a);
ulong8 __vreplace_vkkv(ulong8 a, uchar8 b, uchar8 c, ulong8 d);
long8 __vreplace_vkkv(long8 a, char8 b, char8 c, long8 d);
uchar64 __vreverseb_vv(uchar64 a);
char64 __vreverseb_vv(char64 a);
ulong8 __vreversed_vv(ulong8 a);
long8 __vreversed_vv(long8 a);
ushort32 __vreverseh_vv(ushort32 a);
short32 __vreverseh_vv(short32 a);
uint16 __vreversew_vv(uint16 a);
int16 __vreversew_vv(int16 a);
uchar64 __vrotlb_vkv(uchar64 a, uchar64 b);
uchar64 __vrotlb_vvv(uchar64 a, uint16 b);
ulong8 __vrotld_vkv(ulong8 a, uchar8 b);
ulong8 __vrotld_vvv(ulong8 a, ulong8 b);
ushort32 __vrotlh_vkv(ushort32 a, ushort32 b);
ushort32 __vrotlh_vvv(ushort32 a, uint16 b);
int16 __vrotlw_vkv(int16 a, uchar16 b);
int16 __vrotlw_vvv(int16 a, uint16 b);
short32 __vrpackh_vvv(int16 a, int16 b);
double8 __vrsqrdp_vv(double8 a);
float16 __vrsqrsp_vv(float16 a);
uint16 __vsad16ou16h16w_vvv(ushort32 a, ushort16 b);
uint16 __vsad16ou8h16w_vvv(ushort32 a, ushort8 b);
ushort32 __vsad8ou16b32h_vvv(uchar64 a, uchar16 b);
char64 __vsaddb_vkv(char64 a, char64 b);
char64 __vsaddb_vvv(char64 a, char64 b);
short32 __vsaddh_vkv(short32 a, short32 b);
short32 __vsaddh_vvv(short32 a, short32 b);
uchar64 __vsaddub_vvv(uchar64 a, uchar64 b);
ushort32 __vsadduh_vvv(ushort32 a, ushort32 b);
uchar64 __vsaddusb_vvv(uchar64 a, char64 b);
ushort32 __vsaddush_vvv(ushort32 a, short32 b);
uint16 __vsaddusw_vvv(uint16 a, int16 b);
uint16 __vsadduw_vvv(uint16 a, uint16 b);
int16 __vsaddw_vkv(int16 a, int16 b);
int16 __vsaddw_vvv(int16 a, int16 b);
uint16 __vsadm16ou16h16w_yvvv(uchar64 a, ushort32 b, ushort16 c);
uint16 __vsadm16ou8h16w_yvvv(uchar64 a, ushort32 b, ushort8 c);
ushort32 __vsadm8ou16b32h_yvvv(uchar64 a, uchar64 b, uchar16 c);
long8 __vsatdl_vv(long8 a);
long8 __vsatdw_vv(long8 a);
short32 __vsathb_vv(short32 a);
long8 __vsatlw_vv(long8 a);
int16 __vsatwh_vv(int16 a);
double8 __vscaledp_vvv(double8 a, ulong8 b);
float16 __vscalesp_vvv(float16 a, uint16 b);
char64 __vscatterb_pvv(__vpred a, char64 b);
char64 __vscatternb_pvv(__vpred a, char64 b);
int16 __vsel_pvkv(__vpred a, int16 b, uint16 c);
float16 __vsel_pvkv(__vpred a, float16 b, uint16 c);
uint16 __vsel_pvkv(__vpred a, uint16 b, uint16 c);
char64 __vsel_pvvv(__vpred a, char64 b, char64 c);
short32 __vsel_pvvv(__vpred a, short32 b, short32 c);
int16 __vsel_pvvv(__vpred a, int16 b, int16 c);
long8 __vsel_pvvv(__vpred a, long8 b, long8 c);
uchar64 __vsel_pvvv(__vpred a, uchar64 b, uchar64 c);
ushort32 __vsel_pvvv(__vpred a, ushort32 b, ushort32 c);
uint16 __vsel_pvvv(__vpred a, uint16 b, uint16 c);
ulong8 __vsel_pvvv(__vpred a, ulong8 b, ulong8 c);
uchar64 __vshfl2b_vv(uchar64 a);
char64 __vshfl2b_vv(char64 a);
ulong8 __vshfl2d_vv(ulong8 a);
long8 __vshfl2d_vv(long8 a);
ulong8 __vshfl2dee_vvv(ulong8 a, ulong8 b);
long8 __vshfl2dee_vvv(long8 a, long8 b);
ulong8 __vshfl2deo_vvv(ulong8 a, ulong8 b);
long8 __vshfl2deo_vvv(long8 a, long8 b);
ulong8 __vshfl2dhh_vvv(ulong8 a, ulong8 b);
long8 __vshfl2dhh_vvv(long8 a, long8 b);
ulong8 __vshfl2dlh_vvv(ulong8 a, ulong8 b);
long8 __vshfl2dlh_vvv(long8 a, long8 b);
ulong8 __vshfl2dll_vvv(ulong8 a, ulong8 b);
long8 __vshfl2dll_vvv(long8 a, long8 b);
ulong8 __vshfl2doo_vvv(ulong8 a, ulong8 b);
long8 __vshfl2doo_vvv(long8 a, long8 b);
ushort32 __vshfl2h_vv(ushort32 a);
short32 __vshfl2h_vv(short32 a);
ushort32 __vshfl2hhh_vvv(ushort32 a, ushort32 b);
ushort32 __vshfl2hll_vvv(ushort32 a, ushort32 b);
uint16 __vshfl2w_vv(uint16 a);
int16 __vshfl2w_vv(int16 a);
uint16 __vshfl2whh_vvv(uint16 a, uint16 b);
uint16 __vshfl2wll_vvv(uint16 a, uint16 b);
ulong8 __vshfl3_vvv(uint16 a, uint16 b);
long8 __vshfl3_vvv(int16 a, int16 b);
uchar64 __vshfl4b_vv(uchar64 a);
char64 __vshfl4b_vv(char64 a);
ulong8 __vshfl4d_vv(ulong8 a);
long8 __vshfl4d_vv(long8 a);
ushort32 __vshfl4h_vv(ushort32 a);
short32 __vshfl4h_vv(short32 a);
uint16 __vshfl4w_vv(uint16 a);
int16 __vshfl4w_vv(int16 a);
ulong8 __vshl_vkv(ulong8 a, uint8_t b);
ulong8 __vshl_vvv(ulong8 a, ulong8 b);
char64 __vshlb_vkv(char64 a, char64 b);
uchar64 __vshlb_vkv(uchar64 a, uchar64 b);
char64 __vshlb_vvv(char64 a, int16 b);
uchar64 __vshlb_vvv(uchar64 a, uint16 b);
char64 __vshlcb_pvv(__vpred a, char64 b, char64 c);
uchar64 __vshlcb_pvv(__vpred a, uchar64 b, uchar64 c);
short32 __vshlch_pvv(__vpred a, short32 b, short32 c);
ushort32 __vshlch_pvv(__vpred a, ushort32 b, ushort32 c);
int16 __vshlcw_pvv(__vpred a, int16 b, int16 c);
uint16 __vshlcw_pvv(__vpred a, uint16 b, uint16 c);
long8 __vshld_vkv(long8 a, long8 b);
ulong8 __vshld_vkv(ulong8 a, ulong8 b);
long8 __vshld_vvv(long8 a, long8 b);
ulong8 __vshld_vvv(ulong8 a, ulong8 b);
short32 __vshlh_vkv(short32 a, short32 b);
ushort32 __vshlh_vkv(ushort32 a, ushort32 b);
short32 __vshlh_vvv(short32 a, int16 b);
ushort32 __vshlh_vvv(ushort32 a, uint16 b);
char64 __vshlm16b_vvv(char64 a, char16 b);
char64 __vshlm1b_vrv(char64 a, int8_t b);
char64 __vshlm2b_vrv(char64 a, char2 b);
char64 __vshlm4b_vrv(char64 a, char4 b);
char64 __vshlm8b_vdv(char64 a, char8 b);
int16 __vshlmb_vvv(int16 a, char64 b);
int16 __vshlw_vkv(int16 a, int16 b);
uint16 __vshlw_vkv(uint16 a, uint16 b);
int16 __vshlw_vvv(int16 a, int16 b);
uint16 __vshlw_vvv(uint16 a, uint16 b);
long8 __vshr_vkv(long8 a, uint8_t b);
long8 __vshr_vvv(long8 a, ulong8 b);
char64 __vshrb_vkv(char64 a, char64 b);
char64 __vshrb_vvv(char64 a, int16 b);
long8 __vshrd_vkv(long8 a, long8 b);
long8 __vshrd_vvv(long8 a, long8 b);
short32 __vshrh_vkv(short32 a, short32 b);
short32 __vshrh_vvv(short32 a, int16 b);
char64 __vshrm16b_vvv(char64 a, char16 b);
char64 __vshrm1b_vrv(char64 a, int8_t b);
char64 __vshrm2b_vrv(char64 a, char2 b);
char64 __vshrm4b_vrv(char64 a, char4 b);
char64 __vshrm8b_vdv(char64 a, char8 b);
int16 __vshrmb_vvv(int16 a, char64 b);
char64 __vshrrb_vkv(char64 a, uchar64 b);
char64 __vshrrb_vvv(char64 a, uint16 b);
long8 __vshrrd_vkv(long8 a, uchar8 b);
long8 __vshrrd_vvv(long8 a, uint8 b);
short32 __vshrrh_vkv(short32 a, uchar32 b);
short32 __vshrrh_vvv(short32 a, uint16 b);
int16 __vshrrw_vkv(int16 a, uchar16 b);
int16 __vshrrw_vvv(int16 a, uint16 b);
ulong8 __vshru_vkv(ulong8 a, uint8_t b);
ulong8 __vshru_vvv(ulong8 a, ulong8 b);
uchar64 __vshrub_vkv(uchar64 a, uchar64 b);
uchar64 __vshrub_vvv(uchar64 a, uint16 b);
ulong8 __vshrud_vkv(ulong8 a, ulong8 b);
ulong8 __vshrud_vvv(ulong8 a, ulong8 b);
ushort32 __vshruh_vkv(ushort32 a, ushort32 b);
ushort32 __vshruh_vvv(ushort32 a, uint16 b);
uchar64 __vshrurb_vkv(uchar64 a, uchar64 b);
uchar64 __vshrurb_vvv(uchar64 a, uint16 b);
ulong8 __vshrurd_vkv(ulong8 a, uchar8 b);
ulong8 __vshrurd_vvv(ulong8 a, uint8 b);
ushort32 __vshrurh_vkv(ushort32 a, uchar32 b);
ushort32 __vshrurh_vvv(ushort32 a, uint16 b);
uint16 __vshrurw_vkv(uint16 a, uchar16 b);
uint16 __vshrurw_vvv(uint16 a, uint16 b);
uint16 __vshruw_vkv(uint16 a, uint16 b);
uint16 __vshruw_vvv(uint16 a, uint16 b);
int16 __vshrw_vkv(int16 a, int16 b);
int16 __vshrw_vvv(int16 a, int16 b);
uint16 __vshvluw_vvv(uint16 a, int16 b);
int16 __vshvlw_vvv(int16 a, int16 b);
uint16 __vshvruw_vvv(uint16 a, int16 b);
int16 __vshvrw_vvv(int16 a, int16 b);
void __vsmpyhw_vvw(short32 a, short32 b, int16::EQUIV_ACCESS_T<0>& c, int16::EQUIV_ACCESS_T<0>& d);
int16 __vsmpyr17ww_vvv(int16 a, int16 b);
short32 __vsmpyr1hh_vvv(short32 a, short32 b);
int16 __vsmpyr1ww_vvv(int16 a, int16 b);
short32 __vsmpyrsuhh_vvv(short32 a, ushort32 b);
ushort32 __vsmpyruhh_vvv(ushort32 a, ushort32 b);
int16 __vsmpyww_vvv(int16 a, int16 b);
float16 __vsortd16sp_vv(float16 a);
int16 __vsortd16w_vv(int16 a);
uint16 __vsortdu16w_vv(uint16 a);
float16 __vsorti16sp_vv(float16 a);
int16 __vsorti16w_vv(int16 a);
uint16 __vsortiu16w_vv(uint16 a);
uchar64 __vsortpd16sp_vv(float16 a);
uchar64 __vsortpd16w_vv(int16 a);
uchar64 __vsortpdu16w_vv(uint16 a);
uchar64 __vsortpi16sp_vv(float16 a);
uchar64 __vsortpi16w_vv(int16 a);
uchar64 __vsortpiu16w_vv(uint16 a);
int16 __vspackdw_vvv(long8 a, long8 b);
char64 __vspackhb_vvv(short32 a, short32 b);
uint16 __vspackudw_vvv(ulong8 a, ulong8 b);
uchar64 __vspackuhb_vvv(ushort32 a, ushort32 b);
ushort32 __vspackuwh_vvv(uint16 a, uint16 b);
short32 __vspackwh_vvv(int16 a, int16 b);
double8 __vspdph_vv(float16 a);
double8 __vspdpl_vv(float16 a);
int16 __vspint_vv(float16 a);
short32 __vspinth_vv(float16 a);
short32 __vspinthpk_vv(float16 a);
int16 __vsptrunc_vv(float16 a);
short32 __vsshlh_vkv(short32 a, uchar32 b);
short32 __vsshlh_vvv(short32 a, uint16 b);
int16 __vsshlrdw_vkv(long8 a, uchar8 b);
int16 __vsshlrdw_vvv(long8 a, ulong8 b);
char64 __vsshlrhb_vkv(short32 a, uchar16 b);
char64 __vsshlrhb_vvv(short32 a, uint16 b);
short32 __vsshlrwh_vkv(int16 a, uchar16 b);
short32 __vsshlrwh_vvv(int16 a, uint16 b);
ushort32 __vsshlsuh_vkv(short32 a, uchar32 b);
ushort32 __vsshlsuh_vvv(short32 a, uint16 b);
uint16 __vsshlsurdw_vkv(long8 a, uchar8 b);
uint16 __vsshlsurdw_vvv(long8 a, ulong8 b);
uchar64 __vsshlsurhb_vkv(short32 a, uchar16 b);
uchar64 __vsshlsurhb_vvv(short32 a, uint16 b);
ushort32 __vsshlsurwh_vkv(int16 a, uchar16 b);
ushort32 __vsshlsurwh_vvv(int16 a, uint16 b);
uint16 __vsshlsuw_vkv(int16 a, uchar16 b);
uint16 __vsshlsuw_vvv(int16 a, uint16 b);
ushort32 __vsshluh_vkv(ushort32 a, uchar32 b);
ushort32 __vsshluh_vvv(ushort32 a, uint16 b);
uint16 __vsshlurdw_vkv(ulong8 a, uchar8 b);
uint16 __vsshlurdw_vvv(ulong8 a, ulong8 b);
uchar64 __vsshlurhb_vkv(ushort32 a, uchar16 b);
uchar64 __vsshlurhb_vvv(ushort32 a, uint16 b);
ushort32 __vsshlurwh_vkv(uint16 a, uchar16 b);
ushort32 __vsshlurwh_vvv(uint16 a, uint16 b);
uint16 __vsshluw_vkv(uint16 a, uchar16 b);
uint16 __vsshluw_vvv(uint16 a, uint16 b);
int16 __vsshlw_vkv(int16 a, uchar16 b);
int16 __vsshlw_vvv(int16 a, uint16 b);
int16 __vsshvlw_vvv(int16 a, int16 b);
int16 __vsshvrw_vvv(int16 a, int16 b);
char64 __vssubb_vkv(char64 a, char64 b);
char64 __vssubb_vvv(char64 a, char64 b);
short32 __vssubh_vkv(short32 a, short32 b);
short32 __vssubh_vvv(short32 a, short32 b);
int16 __vssubw_vkv(int16 a, int16 b);
int16 __vssubw_vvv(int16 a, int16 b);
uchar64 __vsubabsb_vvv(uchar64 a, uchar64 b);
ulong8 __vsubabsd_vvv(ulong8 a, ulong8 b);
ushort32 __vsubabsh_vvv(ushort32 a, ushort32 b);
uint16 __vsubabsw_vvv(uint16 a, uint16 b);
char64 __vsubb_vkv(char64 a, char64 b);
uchar64 __vsubb_vkv(uchar64 a, uchar64 b);
char64 __vsubb_vvv(char64 a, char64 b);
uchar64 __vsubb_vvv(uchar64 a, uchar64 b);
int16 __vsubcw_vvv(int16 a, int16 b);
long8 __vsubd_vkv(long8 a, long8 b);
ulong8 __vsubd_vkv(ulong8 a, ulong8 b);
long8 __vsubd_vvv(long8 a, long8 b);
ulong8 __vsubd_vvv(ulong8 a, ulong8 b);
double8 __vsubdp_vvv(double8 a, double8 b);
short32 __vsubh_vkv(short32 a, short32 b);
ushort32 __vsubh_vkv(ushort32 a, ushort32 b);
short32 __vsubh_vvv(short32 a, short32 b);
ushort32 __vsubh_vvv(ushort32 a, ushort32 b);
char64 __vsubrb_vkv(char64 a, char64 b);
uchar64 __vsubrb_vkv(uchar64 a, uchar64 b);
char64 __vsubrb_vvv(char64 a, char64 b);
uchar64 __vsubrb_vvv(uchar64 a, uchar64 b);
long8 __vsubrd_vkv(long8 a, long8 b);
ulong8 __vsubrd_vkv(ulong8 a, ulong8 b);
long8 __vsubrd_vvv(long8 a, long8 b);
ulong8 __vsubrd_vvv(ulong8 a, ulong8 b);
short32 __vsubrh_vkv(short32 a, short32 b);
ushort32 __vsubrh_vkv(ushort32 a, ushort32 b);
short32 __vsubrh_vvv(short32 a, short32 b);
ushort32 __vsubrh_vvv(ushort32 a, ushort32 b);
int16 __vsubrw_vkv(int16 a, int16 b);
uint16 __vsubrw_vkv(uint16 a, uint16 b);
int16 __vsubrw_vvv(int16 a, int16 b);
uint16 __vsubrw_vvv(uint16 a, uint16 b);
float16 __vsubsp_vvv(float16 a, float16 b);
int16 __vsubw_vkv(int16 a, int16 b);
uint16 __vsubw_vkv(uint16 a, uint16 b);
int16 __vsubw_vvv(int16 a, int16 b);
uint16 __vsubw_vvv(uint16 a, uint16 b);
char64 __vswapb_vv(char64 a);
uchar64 __vswapb_vv(uchar64 a);
long8 __vswapd_vv(long8 a);
ulong8 __vswapd_vv(ulong8 a);
short32 __vswaph_vv(short32 a);
ushort32 __vswaph_vv(ushort32 a);
int16 __vswapw_vv(int16 a);
uint16 __vswapw_vv(uint16 a);
short32 __vunpkhb_vv(char64 a);
int16 __vunpkhh_vv(short32 a);
ushort32 __vunpkhub_vv(uchar64 a);
uint16 __vunpkhuh_vv(ushort32 a);
short32 __vunpklb_vv(char64 a);
int16 __vunpklh_vv(short32 a);
ushort32 __vunpklub_vv(uchar64 a);
uint16 __vunpkluh_vv(ushort32 a);
ulong8 __vunpkluw_vv(uint16 a);
long8 __vunpklw_vv(int16 a);
uint16 __vwpackh_vvv(uint16 a, uint16 b);
int16 __vwpackh_vvv(int16 a, int16 b);
uint16 __vwpackl_vvv(uint16 a, uint16 b);
int16 __vwpackl_vvv(int16 a, int16 b);
long8 __vwunpkd_vv(int8 a);
long8 __vwunpkdh_vv(int16 a);
long8 __vwunpkdl_vv(int16 a);
ulong8 __vwunpkdu_vv(uint8 a);
ulong8 __vwunpkudh_vv(uint16 a);
ulong8 __vwunpkudl_vv(uint16 a);
char64 __vxnorw_vvv(char64 a, char64 b);
short32 __vxnorw_vvv(short32 a, short32 b);
int16 __vxnorw_vvv(int16 a, int16 b);
long8 __vxnorw_vvv(long8 a, long8 b);
uchar64 __vxnorw_vvv(uchar64 a, uchar64 b);
ushort32 __vxnorw_vvv(ushort32 a, ushort32 b);
uint16 __vxnorw_vvv(uint16 a, uint16 b);
ulong8 __vxnorw_vvv(ulong8 a, ulong8 b);
uint16 __vxormpyw_vvv(uint16 a, uint16 b);
int16 __vxorw_vkv(int16 a, int16 b);
uint16 __vxorw_vkv(uint16 a, uint16 b);
char64 __vxorw_vvv(char64 a, char64 b);
short32 __vxorw_vvv(short32 a, short32 b);
int16 __vxorw_vvv(int16 a, int16 b);
long8 __vxorw_vvv(long8 a, long8 b);
uchar64 __vxorw_vvv(uchar64 a, uchar64 b);
ushort32 __vxorw_vvv(ushort32 a, ushort32 b);
uint16 __vxorw_vvv(uint16 a, uint16 b);
ulong8 __vxorw_vvv(ulong8 a, ulong8 b);
int8_t __xnor(int8_t a, int8_t b);
char2 __xnor(char2 a, char2 b);
char4 __xnor(char4 a, char4 b);
char8 __xnor(char8 a, char8 b);
char16 __xnor(char16 a, char16 b);
char32 __xnor(char32 a, char32 b);
char64 __xnor(char64 a, char64 b);
int16_t __xnor(int16_t a, int16_t b);
short2 __xnor(short2 a, short2 b);
short4 __xnor(short4 a, short4 b);
short8 __xnor(short8 a, short8 b);
short16 __xnor(short16 a, short16 b);
short32 __xnor(short32 a, short32 b);
int32_t __xnor(int32_t a, int32_t b);
int2 __xnor(int2 a, int2 b);
int4 __xnor(int4 a, int4 b);
int8 __xnor(int8 a, int8 b);
int16 __xnor(int16 a, int16 b);
int64_t __xnor(int64_t a, int64_t b);
long2 __xnor(long2 a, long2 b);
long4 __xnor(long4 a, long4 b);
long8 __xnor(long8 a, long8 b);
uint8_t __xnor(uint8_t a, uint8_t b);
uchar2 __xnor(uchar2 a, uchar2 b);
uchar4 __xnor(uchar4 a, uchar4 b);
uchar8 __xnor(uchar8 a, uchar8 b);
uchar16 __xnor(uchar16 a, uchar16 b);
uchar32 __xnor(uchar32 a, uchar32 b);
uchar64 __xnor(uchar64 a, uchar64 b);
uint16_t __xnor(uint16_t a, uint16_t b);
ushort2 __xnor(ushort2 a, ushort2 b);
ushort4 __xnor(ushort4 a, ushort4 b);
ushort8 __xnor(ushort8 a, ushort8 b);
ushort16 __xnor(ushort16 a, ushort16 b);
ushort32 __xnor(ushort32 a, ushort32 b);
uint32_t __xnor(uint32_t a, uint32_t b);
uint2 __xnor(uint2 a, uint2 b);
uint4 __xnor(uint4 a, uint4 b);
uint8 __xnor(uint8 a, uint8 b);
uint16 __xnor(uint16 a, uint16 b);
uint64_t __xnor(uint64_t a, uint64_t b);
ulong2 __xnor(ulong2 a, ulong2 b);
ulong4 __xnor(ulong4 a, ulong4 b);
ulong8 __xnor(ulong8 a, ulong8 b);
__vpred __xnor(__vpred a, __vpred b);
__vpred __xnor_ppp(__vpred a, __vpred b);
char8 __xnord_ddd(char8 a, char8 b);
short4 __xnord_ddd(short4 a, short4 b);
int2 __xnord_ddd(int2 a, int2 b);
int64_t __xnord_ddd(int64_t a, int64_t b);
uchar8 __xnord_ddd(uchar8 a, uchar8 b);
ushort4 __xnord_ddd(ushort4 a, ushort4 b);
uint2 __xnord_ddd(uint2 a, uint2 b);
uint64_t __xnord_ddd(uint64_t a, uint64_t b);
int64_t __xnord_dkd(int64_t a, int64_t b);
uint64_t __xnord_dkd(uint64_t a, uint64_t b);
char4 __xnorw_rrr(char4 a, char4 b);
short2 __xnorw_rrr(short2 a, short2 b);
int32_t __xnorw_rrr(int32_t a, int32_t b);
uchar4 __xnorw_rrr(uchar4 a, uchar4 b);
ushort2 __xnorw_rrr(ushort2 a, ushort2 b);
uint32_t __xnorw_rrr(uint32_t a, uint32_t b);
__vpred __xor(__vpred a, __vpred b);
__vpred __xor_ppp(__vpred a, __vpred b);
char8 __xord_ddd(char8 a, char8 b);
short4 __xord_ddd(short4 a, short4 b);
int2 __xord_ddd(int2 a, int2 b);
int64_t __xord_ddd(int64_t a, int64_t b);
uchar8 __xord_ddd(uchar8 a, uchar8 b);
ushort4 __xord_ddd(ushort4 a, ushort4 b);
uint2 __xord_ddd(uint2 a, uint2 b);
uint64_t __xord_ddd(uint64_t a, uint64_t b);
int64_t __xord_dkd(int64_t a, int64_t b);
uint64_t __xord_dkd(uint64_t a, uint64_t b);
char4 __xorw_rkr(char4 a, char4 b);
short2 __xorw_rkr(short2 a, short2 b);
int32_t __xorw_rkr(int32_t a, int32_t b);
uchar4 __xorw_rkr(uchar4 a, uchar4 b);
ushort2 __xorw_rkr(ushort2 a, ushort2 b);
uint32_t __xorw_rkr(uint32_t a, uint32_t b);
char4 __xorw_rrr(char4 a, char4 b);
short2 __xorw_rrr(short2 a, short2 b);
int32_t __xorw_rrr(int32_t a, int32_t b);
uchar4 __xorw_rrr(uchar4 a, uchar4 b);
ushort2 __xorw_rrr(ushort2 a, ushort2 b);
uint32_t __xorw_rrr(uint32_t a, uint32_t b);
ushort4 __xpnd4h_rd(uint8_t a);
short4 __xpnd4h_rd(int8_t a);
uchar8 __xpnd8b_rd(uint8_t a);
char8 __xpnd8b_rd(int8_t a);

/*****************************************************************************/
/* GTSC CONTROL REGISTER ACCESS                                              */
/*****************************************************************************/
int64_t __get_GTSC(uint32_t opt);

/*****************************************************************************/
/* INDEXED CONTROL REGISTER ACCESS                                           */
/*****************************************************************************/
int64_t __get_indexed(__INDEXED_CR src, uint32_t idx);
void    __set_indexed(__INDEXED_CR dst, uint32_t idx, int64_t src);

/*****************************************************************************/
/* VECTOR PREDICATE TO REGISTER INTERFACE                                    */
/*****************************************************************************/
vpred   _mvrp(int64_t);
int64_t _mvpb(vpred);
int64_t _mvph(vpred);
int64_t _mvpw(vpred);
int64_t _mvpd(vpred);

/*****************************************************************************/
/* Floating point VMATMPY pseudo-instruction: VMATMPYSP + VADDSP             */
/*****************************************************************************/
__float2 __float_matmpy(__float2, __float4);
__float4 __float_matmpy(__float4, __float8);
__float8 __float_matmpy(__float8, __float16);

/*****************************************************************************/
/* Complex VMPYSP pseudo-instruction: VCMPYSP + VADDSP */
/*****************************************************************************/
__cfloat   __complex_multiply(__cfloat,  __cfloat);
__cfloat2  __complex_multiply(__cfloat2, __cfloat2);
__cfloat4  __complex_multiply(__cfloat4, __cfloat4);
__cfloat8  __complex_multiply(__cfloat8, __cfloat8);

/*****************************************************************************/
/* Complex Conjugate VMPYSP pseudo-instruction: VCMPYSP + VSUBSP */
/*****************************************************************************/
__cfloat   __complex_conjugate_multiply(__cfloat,  __cfloat);
__cfloat2  __complex_conjugate_multiply(__cfloat2, __cfloat2);
__cfloat4  __complex_conjugate_multiply(__cfloat4, __cfloat4);
__cfloat8  __complex_conjugate_multiply(__cfloat8, __cfloat8);

bool2 __mask_bool2(uint32_t a);
bool2 __mask_bool2(uint8_t a);
bool4 __mask_bool4(uint32_t a);
bool4 __mask_bool4(uint8_t a);
bool8 __mask_bool8(uint32_t a);
bool8 __mask_bool8(uint8_t a);
bool16 __mask_bool16(uint32_t a);
bool16 __mask_bool16(uint8_t a);
bool32 __mask_bool32(uint32_t a);
bool32 __mask_bool32(uint8_t a);
bool64 __mask_bool64(uint32_t a);
bool64 __mask_bool64(uint8_t a);

bool2   __reduce_bool2(bool4);
bool2   __reduce_bool2(bool8);
bool2   __reduce_bool2(bool16);
bool2   __reduce_bool2(bool32);
bool2   __reduce_bool2(bool64);
bool2   __create_bool2(uint64_t);
bool4   __extend_bool4(bool2);
bool4   __reduce_bool4(bool8);
bool4   __reduce_bool4(bool16);
bool4   __reduce_bool4(bool32);
bool4   __reduce_bool4(bool64);
bool4   __create_bool4(uint64_t);
bool8   __extend_bool8(bool2);
bool8   __extend_bool8(bool4);
bool8   __reduce_bool8(bool16);
bool8   __reduce_bool8(bool32);
bool8   __reduce_bool8(bool64);
bool8   __create_bool8(uint64_t);
bool16   __extend_bool16(bool2);
bool16   __extend_bool16(bool4);
bool16   __extend_bool16(bool8);
bool16   __reduce_bool16(bool32);
bool16   __reduce_bool16(bool64);
bool16   __create_bool16(uint64_t);
bool32   __extend_bool32(bool2);
bool32   __extend_bool32(bool4);
bool32   __extend_bool32(bool8);
bool32   __extend_bool32(bool16);
bool32   __reduce_bool32(bool64);
bool32   __create_bool32(uint64_t);
bool64   __extend_bool64(bool2);
bool64   __extend_bool64(bool4);
bool64   __extend_bool64(bool8);
bool64   __extend_bool64(bool16);
bool64   __extend_bool64(bool32);
bool64   __create_bool64(uint64_t);

bool2  __create_bool2(__vpred);
bool4  __create_bool4(__vpred);
bool8  __create_bool8(__vpred);
bool16 __create_bool16(__vpred);
bool32 __create_bool32(__vpred);
bool64 __create_bool64(__vpred);

__vpred __create_vpred(bool2);
__vpred __create_vpred(bool4);
__vpred __create_vpred(bool8);
__vpred __create_vpred(bool16);
__vpred __create_vpred(bool32);
__vpred __create_vpred(bool64);
__vpred __create_vpred(uint64_t);

uint64_t  __create_scalar(bool2);
uint64_t  __create_scalar(bool4);
uint64_t  __create_scalar(bool8);
uint64_t  __create_scalar(bool16);
uint64_t  __create_scalar(bool32);
uint64_t  __create_scalar(bool64);
uint64_t  __create_scalar(__vpred);

void  __vstore_pred_interleave(bool64, __char64_ptr,  __char64,  __char64);
void  __vstore_pred_interleave(bool32, __short32_ptr, __short32, __short32);
void  __vstore_pred_interleave(bool16, __int16_ptr,   __int16,   __int16);
void  __vstore_pred_interleave(bool8, __long8_ptr,   __long8,   __long8);
void  __vstore_pred_interleave(bool64, __uchar64_ptr, __uchar64, __uchar64);
void  __vstore_pred_interleave(bool32, __ushort32_ptr,__ushort32,__ushort32);
void  __vstore_pred_interleave(bool16, __uint16_ptr,  __uint16,  __uint16);
void  __vstore_pred_interleave(bool8, __ulong8_ptr,  __ulong8,  __ulong8);
void  __vstore_pred_interleave4(bool32, __char32_ptr,  __char64,   __char64);
void  __vstore_pred_interleave4(bool32, __uchar32_ptr, __uchar64,  __uchar64);
void  __vstore_pred(bool2,  __char2_ptr,   __char2);
void  __vstore_pred(bool4,  __char4_ptr,   __char4);
void  __vstore_pred(bool8,  __char8_ptr,   __char8);
void  __vstore_pred(bool16, __char16_ptr,  __char16);
void  __vstore_pred(bool32, __char32_ptr,  __char32);
void  __vstore_pred(bool64, __char64_ptr,  __char64);
void  __vstore_pred(bool2,  __uchar2_ptr,  __uchar2);
void  __vstore_pred(bool4,  __uchar4_ptr,  __uchar4);
void  __vstore_pred(bool8,  __uchar8_ptr,  __uchar8);
void  __vstore_pred(bool16, __uchar16_ptr, __uchar16);
void  __vstore_pred(bool32, __uchar32_ptr, __uchar32);
void  __vstore_pred(bool64, __uchar64_ptr, __uchar64);
void  __vstore_pred(bool2,  __short2_ptr, __short2);
void  __vstore_pred(bool4,  __short4_ptr, __short4);
void  __vstore_pred(bool8,  __short8_ptr, __short8);
void  __vstore_pred(bool16, __short16_ptr, __short16);
void  __vstore_pred(bool32, __short32_ptr, __short32);
void  __vstore_pred(bool2,  __ushort2_ptr, __ushort2);
void  __vstore_pred(bool4,  __ushort4_ptr, __ushort4);
void  __vstore_pred(bool8,  __ushort8_ptr, __ushort8);
void  __vstore_pred(bool16, __ushort16_ptr, __ushort16);
void  __vstore_pred(bool32, __ushort32_ptr, __ushort32);
void  __vstore_pred(bool2,  __cchar2_ptr, __cchar2);
void  __vstore_pred(bool4,  __cchar4_ptr, __cchar4);
void  __vstore_pred(bool8,  __cchar8_ptr, __cchar8);
void  __vstore_pred(bool16, __cchar16_ptr, __cchar16);
void  __vstore_pred(bool32, __cchar32_ptr, __cchar32);
void  __vstore_pred(bool2,  __int2_ptr,     __int2);
void  __vstore_pred(bool4,  __int4_ptr,     __int4);
void  __vstore_pred(bool8,  __int8_ptr,     __int8);
void  __vstore_pred(bool16, __int16_ptr,    __int16);
void  __vstore_pred(bool2,  __uint2_ptr,    __uint2);
void  __vstore_pred(bool4,  __uint4_ptr,    __uint4);
void  __vstore_pred(bool8,  __uint8_ptr,    __uint8);
void  __vstore_pred(bool16, __uint16_ptr,   __uint16);
void  __vstore_pred(bool2,  __float2_ptr,   __float2);
void  __vstore_pred(bool4,  __float4_ptr,   __float4);
void  __vstore_pred(bool8,  __float8_ptr,   __float8);
void  __vstore_pred(bool16, __float16_ptr,  __float16);
void  __vstore_pred(bool2,  __cshort2_ptr,  __cshort2);
void  __vstore_pred(bool4,  __cshort4_ptr,  __cshort4);
void  __vstore_pred(bool8,  __cshort8_ptr,  __cshort8);
void  __vstore_pred(bool16, __cshort16_ptr, __cshort16);
void  __vstore_pred(bool2, __long2_ptr,   __long2);
void  __vstore_pred(bool4, __long4_ptr,   __long4);
void  __vstore_pred(bool8, __long8_ptr,   __long8);
void  __vstore_pred(bool2, __ulong2_ptr,  __ulong2);
void  __vstore_pred(bool4, __ulong4_ptr,  __ulong4);
void  __vstore_pred(bool8, __ulong8_ptr,  __ulong8);
void  __vstore_pred(bool2, __double2_ptr, __double2);
void  __vstore_pred(bool4, __double4_ptr, __double4);
void  __vstore_pred(bool8, __double8_ptr, __double8);
void  __vstore_pred(bool2, __cint2_ptr,   __cint2);
void  __vstore_pred(bool4, __cint4_ptr,   __cint4);
void  __vstore_pred(bool8, __cint8_ptr,   __cint8);
void  __vstore_pred(bool2, __cfloat2_ptr, __cfloat2);
void  __vstore_pred(bool4, __cfloat4_ptr, __cfloat4);
void  __vstore_pred(bool8, __cfloat8_ptr, __cfloat8);
void  __vstore_pred_packl(bool32,   __char32_ptr,  __short32);
void  __vstore_pred_packl(bool32,   __uchar32_ptr, __ushort32);
void  __vstore_pred_packh(bool32,   __char32_ptr,  __short32);
void  __vstore_pred_packh(bool32,   __uchar32_ptr, __ushort32);
void  __vstore_pred_packhs1(bool32, __char32_ptr,  __short32);
void  __vstore_pred_packhs1(bool32, __uchar32_ptr, __ushort32);
void  __vstore_pred_packl(bool16,   __short16_ptr,  __int16);
void  __vstore_pred_packl(bool16,   __ushort16_ptr, __uint16);
void  __vstore_pred_packh(bool16,   __short16_ptr,  __int16);
void  __vstore_pred_packh(bool16,   __ushort16_ptr, __uint16);
void  __vstore_pred_packhs1(bool16, __short16_ptr,  __int16);
void  __vstore_pred_packhs1(bool16, __ushort16_ptr, __uint16);
void  __vstore_pred_pack_byte(bool16, __char16_ptr,  __int16);
void  __vstore_pred_pack_byte(bool16, __uchar16_ptr, __uint16);
void  __vstore_pred_packl(bool8,   __int8_ptr,  __long8);
void  __vstore_pred_packl(bool8,   __uint8_ptr, __ulong8);
void  __vstore_pred_packh(bool8,   __int8_ptr,  __long8);
void  __vstore_pred_packh(bool8,   __uint8_ptr, __ulong8);
void  __vstore_pred_packhs1(bool8, __int8_ptr,  __long8);
void  __vstore_pred_packhs1(bool8, __uint8_ptr, __ulong8);
void  __vstore_pred_packl_2src(bool64,   __char64_ptr, __short32,  __short32);
void  __vstore_pred_packl_2src(bool64,   __uchar64_ptr, __ushort32, __ushort32);
void  __vstore_pred_packh_2src(bool64,   __char64_ptr, __short32,  __short32);
void  __vstore_pred_packh_2src(bool64,   __uchar64_ptr, __ushort32, __ushort32);
void  __vstore_pred_packhs1_2src(bool64, __char64_ptr, __short32,  __short32);
void  __vstore_pred_packhs1_2src(bool64, __uchar64_ptr, __ushort32, __ushort32);
void  __vstore_pred_packl_2src(bool32,   __short32_ptr, __int16,   __int16);
void  __vstore_pred_packl_2src(bool32,   __ushort32_ptr, __uint16, __uint16);
void  __vstore_pred_packh_2src(bool32,   __short32_ptr, __int16,   __int16);
void  __vstore_pred_packh_2src(bool32,   __ushort32_ptr, __uint16, __uint16);
void  __vstore_pred_packhs1_2src(bool32, __short32_ptr, __int16,   __int16);
void  __vstore_pred_packhs1_2src(bool32, __ushort32_ptr, __uint16, __uint16);
void  __vstore_pred_pack_byte_2src(bool32, __char32_ptr, __int16,  __int16);
void  __vstore_pred_pack_byte_2src(bool32, __uchar32_ptr, __uint16, __uint16);
void  __vstore_pred_packl_2src(bool16,   __int16_ptr, __long8,  __long8);
void  __vstore_pred_packl_2src(bool16,   __uint16_ptr, __ulong8, __ulong8);
void  __vstore_pred_packh_2src(bool16,   __int16_ptr, __long8,   __long8);
void  __vstore_pred_packh_2src(bool16,   __uint16_ptr, __ulong8, __ulong8);
void  __vstore_pred_packhs1_2src(bool16, __int16_ptr, __long8,   __long8);
void  __vstore_pred_packhs1_2src(bool16, __uint16_ptr, __ulong8, __ulong8);
void  __vstore_pred_packl_long_2src(bool8,   __long8_ptr, __long8, __long8);
void  __vstore_pred_packl_long_2src(bool8,   __ulong8_ptr, __ulong8,__ulong8);
void  __vstore_pred_packh_long_2src(bool8,   __long8_ptr, __long8, __long8);
void  __vstore_pred_packh_long_2src(bool8,   __ulong8_ptr, __ulong8,__ulong8);
void  __vstore_pred_packhs1_long_2src(bool8, __long8_ptr, __long8, __long8);
void  __vstore_pred_packhs1_long_2src(bool8, __ulong8_ptr, __ulong8,__ulong8);
void  __vstore_pred_reverse_bit(bool16, __cshort16_ptr, __cshort16);
void  __vstore_pred_reverse_bit(bool8, __cint8_ptr,   __cint8);
void  __vstore_pred_reverse_bit(bool8, __cfloat8_ptr, __cfloat8);

char2 __add(bool2 a, char2 b, char2 c);
char4 __add(bool4 a, char4 b, char4 c);
char8 __add(bool8 a, char8 b, char8 c);
char16 __add(bool16 a, char16 b, char16 c);
char32 __add(bool32 a, char32 b, char32 c);
char64 __add(bool64 a, char64 b, char64 c);
uchar2 __add(bool2 a, uchar2 b, uchar2 c);
uchar4 __add(bool4 a, uchar4 b, uchar4 c);
uchar8 __add(bool8 a, uchar8 b, uchar8 c);
uchar16 __add(bool16 a, uchar16 b, uchar16 c);
uchar32 __add(bool32 a, uchar32 b, uchar32 c);
uchar64 __add(bool64 a, uchar64 b, uchar64 c);
long2 __add(bool2 a, long2 b, long2 c);
long4 __add(bool4 a, long4 b, long4 c);
long8 __add(bool8 a, long8 b, long8 c);
ulong2 __add(bool2 a, ulong2 b, ulong2 c);
ulong4 __add(bool4 a, ulong4 b, ulong4 c);
ulong8 __add(bool8 a, ulong8 b, ulong8 c);
short2 __add(bool2 a, short2 b, short2 c);
short4 __add(bool4 a, short4 b, short4 c);
short8 __add(bool8 a, short8 b, short8 c);
short16 __add(bool16 a, short16 b, short16 c);
short32 __add(bool32 a, short32 b, short32 c);
ushort2 __add(bool2 a, ushort2 b, ushort2 c);
ushort4 __add(bool4 a, ushort4 b, ushort4 c);
ushort8 __add(bool8 a, ushort8 b, ushort8 c);
ushort16 __add(bool16 a, ushort16 b, ushort16 c);
ushort32 __add(bool32 a, ushort32 b, ushort32 c);
int2 __add(bool2 a, int2 b, int2 c);
int4 __add(bool4 a, int4 b, int4 c);
int8 __add(bool8 a, int8 b, int8 c);
int16 __add(bool16 a, int16 b, int16 c);
uint2 __add(bool2 a, uint2 b, uint2 c);
uint4 __add(bool4 a, uint4 b, uint4 c);
uint8 __add(bool8 a, uint8 b, uint8 c);
uint16 __add(bool16 a, uint16 b, uint16 c);

bool2 __and(bool2, bool2);
bool4 __and(bool4, bool4);
bool8 __and(bool8, bool8);
bool16 __and(bool16, bool16);
bool32 __and(bool32, bool32);
bool64 __and(bool64, bool64);
bool2 __andn(bool2, bool2);
bool4 __andn(bool4, bool4);
bool8 __andn(bool8, bool8);
bool16 __andn(bool16, bool16);
bool32 __andn(bool32, bool32);
bool64 __andn(bool64, bool64);
bool64 __bit_reverse(bool64);

bool2 __cmp_eq_bool(char2, char2);
bool4 __cmp_eq_bool(char4, char4);
bool8 __cmp_eq_bool(char8, char8);
bool16 __cmp_eq_bool(char16, char16);
bool32 __cmp_eq_bool(char32, char32);
bool64 __cmp_eq_bool(char64, char64);
bool2 __cmp_eq_bool(uchar2, uchar2);
bool4 __cmp_eq_bool(uchar4, uchar4);
bool8 __cmp_eq_bool(uchar8, uchar8);
bool16 __cmp_eq_bool(uchar16, uchar16);
bool32 __cmp_eq_bool(uchar32, uchar32);
bool64 __cmp_eq_bool(uchar64, uchar64);
bool2 __cmp_eq_bool(long2, long2);
bool4 __cmp_eq_bool(long4, long4);
bool8 __cmp_eq_bool(long8, long8);
bool2 __cmp_eq_bool(ulong2, ulong2);
bool4 __cmp_eq_bool(ulong4, ulong4);
bool8 __cmp_eq_bool(ulong8, ulong8);
bool2 __cmp_eq_bool(double2, double2);
bool4 __cmp_eq_bool(double4, double4);
bool8 __cmp_eq_bool(double8, double8);
bool2 __cmp_eq_bool(short2, short2);
bool4 __cmp_eq_bool(short4, short4);
bool8 __cmp_eq_bool(short8, short8);
bool16 __cmp_eq_bool(short16, short16);
bool32 __cmp_eq_bool(short32, short32);
bool2 __cmp_eq_bool(ushort2, ushort2);
bool4 __cmp_eq_bool(ushort4, ushort4);
bool8 __cmp_eq_bool(ushort8, ushort8);
bool16 __cmp_eq_bool(ushort16, ushort16);
bool32 __cmp_eq_bool(ushort32, ushort32);
bool2 __cmp_eq_bool(float2, float2);
bool4 __cmp_eq_bool(float4, float4);
bool8 __cmp_eq_bool(float8, float8);
bool16 __cmp_eq_bool(float16, float16);
bool2 __cmp_eq_bool(int2, int2);
bool4 __cmp_eq_bool(int4, int4);
bool8 __cmp_eq_bool(int8, int8);
bool16 __cmp_eq_bool(int16, int16);
bool2 __cmp_eq_bool(uint2, uint2);
bool4 __cmp_eq_bool(uint4, uint4);
bool8 __cmp_eq_bool(uint8, uint8);
bool16 __cmp_eq_bool(uint16, uint16);

bool2 __cmp_ge_bool(char2, char2);
bool4 __cmp_ge_bool(char4, char4);
bool8 __cmp_ge_bool(char8, char8);
bool16 __cmp_ge_bool(char16, char16);
bool32 __cmp_ge_bool(char32, char32);
bool64 __cmp_ge_bool(char64, char64);
bool2 __cmp_ge_bool(long2, long2);
bool4 __cmp_ge_bool(long4, long4);
bool8 __cmp_ge_bool(long8, long8);
bool2 __cmp_ge_bool(short2, short2);
bool4 __cmp_ge_bool(short4, short4);
bool8 __cmp_ge_bool(short8, short8);
bool16 __cmp_ge_bool(short16, short16);
bool32 __cmp_ge_bool(short32, short32);
bool2 __cmp_ge_bool(uchar2, uchar2);
bool4 __cmp_ge_bool(uchar4, uchar4);
bool8 __cmp_ge_bool(uchar8, uchar8);
bool16 __cmp_ge_bool(uchar16, uchar16);
bool32 __cmp_ge_bool(uchar32, uchar32);
bool64 __cmp_ge_bool(uchar64, uchar64);
bool2 __cmp_ge_bool(ulong2, ulong2);
bool4 __cmp_ge_bool(ulong4, ulong4);
bool8 __cmp_ge_bool(ulong8, ulong8);
bool2 __cmp_ge_bool(ushort2, ushort2);
bool4 __cmp_ge_bool(ushort4, ushort4);
bool8 __cmp_ge_bool(ushort8, ushort8);
bool16 __cmp_ge_bool(ushort16, ushort16);
bool32 __cmp_ge_bool(ushort32, ushort32);
bool2 __cmp_ge_bool(uint2, uint2);
bool4 __cmp_ge_bool(uint4, uint4);
bool8 __cmp_ge_bool(uint8, uint8);
bool16 __cmp_ge_bool(uint16, uint16);
bool2 __cmp_ge_bool(int2, int2);
bool4 __cmp_ge_bool(int4, int4);
bool8 __cmp_ge_bool(int8, int8);
bool16 __cmp_ge_bool(int16, int16);

bool2 __cmp_gt_bool(char2, char2);
bool4 __cmp_gt_bool(char4, char4);
bool8 __cmp_gt_bool(char8, char8);
bool16 __cmp_gt_bool(char16, char16);
bool32 __cmp_gt_bool(char32, char32);
bool64 __cmp_gt_bool(char64, char64);
bool2 __cmp_gt_bool(long2, long2);
bool4 __cmp_gt_bool(long4, long4);
bool8 __cmp_gt_bool(long8, long8);
bool2 __cmp_gt_bool(short2, short2);
bool4 __cmp_gt_bool(short4, short4);
bool8 __cmp_gt_bool(short8, short8);
bool16 __cmp_gt_bool(short16, short16);
bool32 __cmp_gt_bool(short32, short32);
bool2 __cmp_gt_bool(uchar2, uchar2);
bool4 __cmp_gt_bool(uchar4, uchar4);
bool8 __cmp_gt_bool(uchar8, uchar8);
bool16 __cmp_gt_bool(uchar16, uchar16);
bool32 __cmp_gt_bool(uchar32, uchar32);
bool64 __cmp_gt_bool(uchar64, uchar64);
bool2 __cmp_gt_bool(ulong2, ulong2);
bool4 __cmp_gt_bool(ulong4, ulong4);
bool8 __cmp_gt_bool(ulong8, ulong8);
bool2 __cmp_gt_bool(ushort2, ushort2);
bool4 __cmp_gt_bool(ushort4, ushort4);
bool8 __cmp_gt_bool(ushort8, ushort8);
bool16 __cmp_gt_bool(ushort16, ushort16);
bool32 __cmp_gt_bool(ushort32, ushort32);
bool2 __cmp_gt_bool(uint2, uint2);
bool4 __cmp_gt_bool(uint4, uint4);
bool8 __cmp_gt_bool(uint8, uint8);
bool16 __cmp_gt_bool(uint16, uint16);
bool2 __cmp_gt_bool(int2, int2);
bool4 __cmp_gt_bool(int4, int4);
bool8 __cmp_gt_bool(int8, int8);
bool16 __cmp_gt_bool(int16, int16);

bool2 __cmp_le_bool(double2, double2);
bool4 __cmp_le_bool(double4, double4);
bool8 __cmp_le_bool(double8, double8);
bool2 __cmp_le_bool(float2, float2);
bool4 __cmp_le_bool(float4, float4);
bool8 __cmp_le_bool(float8, float8);
bool16 __cmp_le_bool(float16, float16);

bool2 __cmp_lt_bool(double2, double2);
bool4 __cmp_lt_bool(double4, double4);
bool8 __cmp_lt_bool(double8, double8);
bool2 __cmp_lt_bool(float2, float2);
bool4 __cmp_lt_bool(float4, float4);
bool8 __cmp_lt_bool(float8, float8);
bool16 __cmp_lt_bool(float16, float16);

bool64 __compress_set_bits_left(bool64);
bool64 __compress_set_bits_right(bool64);
bool64 __decimate(bool64, bool64);
bool64 __duplicate_pred_high(bool64);
bool64 __duplicate_pred_low(bool64);
char2 __expand(bool2);
char4 __expand(bool4);
char8 __expand(bool8);
char16 __expand(bool16);
char32 __expand(bool32);
char64 __expand(bool64);
char2 __gather_set_bits(bool2, char2);
char4 __gather_set_bits(bool4, char4);
char8 __gather_set_bits(bool8, char8);
char16 __gather_set_bits(bool16, char16);
char32 __gather_set_bits(bool32, char32);
char64 __gather_set_bits(bool64, char64);
char2 __gather_unset_bits(bool2, char2);
char4 __gather_unset_bits(bool4, char4);
char8 __gather_unset_bits(bool8, char8);
char16 __gather_unset_bits(bool16, char16);
char32 __gather_unset_bits(bool32, char32);
char64 __gather_unset_bits(bool64, char64);

template <size_t DEPTH>
void __max_circ_bool(char2 a, char2::EQUIV_ACCESS_T<DEPTH>& b, bool2& c);
template <size_t DEPTH>
void __max_circ_bool(char4 a, char4::EQUIV_ACCESS_T<DEPTH>& b, bool4& c);
template <size_t DEPTH>
void __max_circ_bool(char8 a, char8::EQUIV_ACCESS_T<DEPTH>& b, bool8& c);
template <size_t DEPTH>
void __max_circ_bool(char16 a, char16::EQUIV_ACCESS_T<DEPTH>& b, bool16& c);
template <size_t DEPTH>
void __max_circ_bool(char32 a, char32::EQUIV_ACCESS_T<DEPTH>& b, bool32& c);
template <size_t DEPTH>
void __max_circ_bool(char64 a, char64::EQUIV_ACCESS_T<DEPTH>& b, bool64& c);
template <size_t DEPTH>
void __max_circ_bool(short2 a, short2::EQUIV_ACCESS_T<DEPTH>& b, bool2& c);
template <size_t DEPTH>
void __max_circ_bool(short4 a, short4::EQUIV_ACCESS_T<DEPTH>& b, bool4& c);
template <size_t DEPTH>
void __max_circ_bool(short8 a, short8::EQUIV_ACCESS_T<DEPTH>& b, bool8& c);
template <size_t DEPTH>
void __max_circ_bool(short16 a, short16::EQUIV_ACCESS_T<DEPTH>& b, bool16& c);
template <size_t DEPTH>
void __max_circ_bool(short32 a, short32::EQUIV_ACCESS_T<DEPTH>& b, bool32& c);

template <size_t DEPTH>
void __max_index_bool(char2 a, char2::EQUIV_ACCESS_T<DEPTH>& b, bool2& c);
template <size_t DEPTH>
void __max_index_bool(char4 a, char4::EQUIV_ACCESS_T<DEPTH>& b, bool4& c);
template <size_t DEPTH>
void __max_index_bool(char8 a, char8::EQUIV_ACCESS_T<DEPTH>& b, bool8& c);
template <size_t DEPTH>
void __max_index_bool(char16 a, char16::EQUIV_ACCESS_T<DEPTH>& b, bool16& c);
template <size_t DEPTH>
void __max_index_bool(char32 a, char32::EQUIV_ACCESS_T<DEPTH>& b, bool32& c);
template <size_t DEPTH>
void __max_index_bool(char64 a, char64::EQUIV_ACCESS_T<DEPTH>& b, bool64& c);
template <size_t DEPTH>
void __max_index_bool(long2 a, long2::EQUIV_ACCESS_T<DEPTH>& b, bool2& c);
template <size_t DEPTH>
void __max_index_bool(long4 a, long4::EQUIV_ACCESS_T<DEPTH>& b, bool4& c);
template <size_t DEPTH>
void __max_index_bool(long8 a, long8::EQUIV_ACCESS_T<DEPTH>& b, bool8& c);
template <size_t DEPTH>
void __max_index_bool(short2 a, short2::EQUIV_ACCESS_T<DEPTH>& b, bool2& c);
template <size_t DEPTH>
void __max_index_bool(short4 a, short4::EQUIV_ACCESS_T<DEPTH>& b, bool4& c);
template <size_t DEPTH>
void __max_index_bool(short8 a, short8::EQUIV_ACCESS_T<DEPTH>& b, bool8& c);
template <size_t DEPTH>
void __max_index_bool(short16 a, short16::EQUIV_ACCESS_T<DEPTH>& b, bool16& c);
template <size_t DEPTH>
void __max_index_bool(short32 a, short32::EQUIV_ACCESS_T<DEPTH>& b, bool32& c);
template <size_t DEPTH>
void __max_index_bool(int2 a, int2::EQUIV_ACCESS_T<DEPTH>& b, bool2& c);
template <size_t DEPTH>
void __max_index_bool(int4 a, int4::EQUIV_ACCESS_T<DEPTH>& b, bool4& c);
template <size_t DEPTH>
void __max_index_bool(int8 a, int8::EQUIV_ACCESS_T<DEPTH>& b, bool8& c);
template <size_t DEPTH>
void __max_index_bool(int16 a, int16::EQUIV_ACCESS_T<DEPTH>& b, bool16& c);
template <size_t DEPTH>
void __max_index_bool(uchar2 a, uchar2::EQUIV_ACCESS_T<DEPTH>& b, bool2& c);
template <size_t DEPTH>
void __max_index_bool(uchar4 a, uchar4::EQUIV_ACCESS_T<DEPTH>& b, bool4& c);
template <size_t DEPTH>
void __max_index_bool(uchar8 a, uchar8::EQUIV_ACCESS_T<DEPTH>& b, bool8& c);
template <size_t DEPTH>
void __max_index_bool(uchar16 a, uchar16::EQUIV_ACCESS_T<DEPTH>& b, bool16& c);
template <size_t DEPTH>
void __max_index_bool(uchar32 a, uchar32::EQUIV_ACCESS_T<DEPTH>& b, bool32& c);
template <size_t DEPTH>
void __max_index_bool(uchar64 a, uchar64::EQUIV_ACCESS_T<DEPTH>& b, bool64& c);
template <size_t DEPTH>
void __max_index_bool(ulong2 a, ulong2::EQUIV_ACCESS_T<DEPTH>& b, bool2& c);
template <size_t DEPTH>
void __max_index_bool(ulong4 a, ulong4::EQUIV_ACCESS_T<DEPTH>& b, bool4& c);
template <size_t DEPTH>
void __max_index_bool(ulong8 a, ulong8::EQUIV_ACCESS_T<DEPTH>& b, bool8& c);
template <size_t DEPTH>
void __max_index_bool(ushort2 a, ushort2::EQUIV_ACCESS_T<DEPTH>& b, bool2& c);
template <size_t DEPTH>
void __max_index_bool(ushort4 a, ushort4::EQUIV_ACCESS_T<DEPTH>& b, bool4& c);
template <size_t DEPTH>
void __max_index_bool(ushort8 a, ushort8::EQUIV_ACCESS_T<DEPTH>& b, bool8& c);
template <size_t DEPTH>
void __max_index_bool(ushort16 a, ushort16::EQUIV_ACCESS_T<DEPTH>& b, bool16& c);
template <size_t DEPTH>
void __max_index_bool(ushort32 a, ushort32::EQUIV_ACCESS_T<DEPTH>& b, bool32& c);
template <size_t DEPTH>
void __max_index_bool(uint2 a, uint2::EQUIV_ACCESS_T<DEPTH>& b, bool2& c);
template <size_t DEPTH>
void __max_index_bool(uint4 a, uint4::EQUIV_ACCESS_T<DEPTH>& b, bool4& c);
template <size_t DEPTH>
void __max_index_bool(uint8 a, uint8::EQUIV_ACCESS_T<DEPTH>& b, bool8& c);
template <size_t DEPTH>
void __max_index_bool(uint16 a, uint16::EQUIV_ACCESS_T<DEPTH>& b, bool16& c);

template <size_t DEPTH>
void __min_index_bool(char2 a, char2::EQUIV_ACCESS_T<DEPTH>& b, bool2& c);
template <size_t DEPTH>
void __min_index_bool(char4 a, char4::EQUIV_ACCESS_T<DEPTH>& b, bool4& c);
template <size_t DEPTH>
void __min_index_bool(char8 a, char8::EQUIV_ACCESS_T<DEPTH>& b, bool8& c);
template <size_t DEPTH>
void __min_index_bool(char16 a, char16::EQUIV_ACCESS_T<DEPTH>& b, bool16& c);
template <size_t DEPTH>
void __min_index_bool(char32 a, char32::EQUIV_ACCESS_T<DEPTH>& b, bool32& c);
template <size_t DEPTH>
void __min_index_bool(char64 a, char64::EQUIV_ACCESS_T<DEPTH>& b, bool64& c);
template <size_t DEPTH>
void __min_index_bool(long2 a, long2::EQUIV_ACCESS_T<DEPTH>& b, bool2& c);
template <size_t DEPTH>
void __min_index_bool(long4 a, long4::EQUIV_ACCESS_T<DEPTH>& b, bool4& c);
template <size_t DEPTH>
void __min_index_bool(long8 a, long8::EQUIV_ACCESS_T<DEPTH>& b, bool8& c);
template <size_t DEPTH>
void __min_index_bool(short2 a, short2::EQUIV_ACCESS_T<DEPTH>& b, bool2& c);
template <size_t DEPTH>
void __min_index_bool(short4 a, short4::EQUIV_ACCESS_T<DEPTH>& b, bool4& c);
template <size_t DEPTH>
void __min_index_bool(short8 a, short8::EQUIV_ACCESS_T<DEPTH>& b, bool8& c);
template <size_t DEPTH>
void __min_index_bool(short16 a, short16::EQUIV_ACCESS_T<DEPTH>& b, bool16& c);
template <size_t DEPTH>
void __min_index_bool(short32 a, short32::EQUIV_ACCESS_T<DEPTH>& b, bool32& c);
template <size_t DEPTH>
void __min_index_bool(int2 a, int2::EQUIV_ACCESS_T<DEPTH>& b, bool2& c);
template <size_t DEPTH>
void __min_index_bool(int4 a, int4::EQUIV_ACCESS_T<DEPTH>& b, bool4& c);
template <size_t DEPTH>
void __min_index_bool(int8 a, int8::EQUIV_ACCESS_T<DEPTH>& b, bool8& c);
template <size_t DEPTH>
void __min_index_bool(int16 a, int16::EQUIV_ACCESS_T<DEPTH>& b, bool16& c);
template <size_t DEPTH>
void __min_index_bool(uchar2 a, uchar2::EQUIV_ACCESS_T<DEPTH>& b, bool2& c);
template <size_t DEPTH>
void __min_index_bool(uchar4 a, uchar4::EQUIV_ACCESS_T<DEPTH>& b, bool4& c);
template <size_t DEPTH>
void __min_index_bool(uchar8 a, uchar8::EQUIV_ACCESS_T<DEPTH>& b, bool8& c);
template <size_t DEPTH>
void __min_index_bool(uchar16 a, uchar16::EQUIV_ACCESS_T<DEPTH>& b, bool16& c);
template <size_t DEPTH>
void __min_index_bool(uchar32 a, uchar32::EQUIV_ACCESS_T<DEPTH>& b, bool32& c);
template <size_t DEPTH>
void __min_index_bool(uchar64 a, uchar64::EQUIV_ACCESS_T<DEPTH>& b, bool64& c);
template <size_t DEPTH>
void __min_index_bool(ulong2 a, ulong2::EQUIV_ACCESS_T<DEPTH>& b, bool2& c);
template <size_t DEPTH>
void __min_index_bool(ulong4 a, ulong4::EQUIV_ACCESS_T<DEPTH>& b, bool4& c);
template <size_t DEPTH>
void __min_index_bool(ulong8 a, ulong8::EQUIV_ACCESS_T<DEPTH>& b, bool8& c);
template <size_t DEPTH>
void __min_index_bool(ushort2 a, ushort2::EQUIV_ACCESS_T<DEPTH>& b, bool2& c);
template <size_t DEPTH>
void __min_index_bool(ushort4 a, ushort4::EQUIV_ACCESS_T<DEPTH>& b, bool4& c);
template <size_t DEPTH>
void __min_index_bool(ushort8 a, ushort8::EQUIV_ACCESS_T<DEPTH>& b, bool8& c);
template <size_t DEPTH>
void __min_index_bool(ushort16 a, ushort16::EQUIV_ACCESS_T<DEPTH>& b, bool16& c);
template <size_t DEPTH>
void __min_index_bool(ushort32 a, ushort32::EQUIV_ACCESS_T<DEPTH>& b, bool32& c);
template <size_t DEPTH>
void __min_index_bool(uint2 a, uint2::EQUIV_ACCESS_T<DEPTH>& b, bool2& c);
template <size_t DEPTH>
void __min_index_bool(uint4 a, uint4::EQUIV_ACCESS_T<DEPTH>& b, bool4& c);
template <size_t DEPTH>
void __min_index_bool(uint8 a, uint8::EQUIV_ACCESS_T<DEPTH>& b, bool8& c);
template <size_t DEPTH>
void __min_index_bool(uint16 a, uint16::EQUIV_ACCESS_T<DEPTH>& b, bool16& c);

bool2 __nand(bool2, bool2);
bool4 __nand(bool4, bool4);
bool8 __nand(bool8, bool8);
bool16 __nand(bool16, bool16);
bool32 __nand(bool32, bool32);
bool64 __nand(bool64, bool64);
bool2 __negate(bool2);
bool4 __negate(bool4);
bool8 __negate(bool8);
bool16 __negate(bool16);
bool32 __negate(bool32);
bool64 __negate(bool64);
bool2 __nor(bool2, bool2);
bool4 __nor(bool4, bool4);
bool8 __nor(bool8, bool8);
bool16 __nor(bool16, bool16);
bool32 __nor(bool32, bool32);
bool64 __nor(bool64, bool64);
bool2 __or(bool2, bool2);
bool4 __or(bool4, bool4);
bool8 __or(bool8, bool8);
bool16 __or(bool16, bool16);
bool32 __or(bool32, bool32);
bool64 __or(bool64, bool64);
bool2 __orn(bool2, bool2);
bool4 __orn(bool4, bool4);
bool8 __orn(bool8, bool8);
bool16 __orn(bool16, bool16);
bool32 __orn(bool32, bool32);
bool64 __orn(bool64, bool64);
uint16 __parallel_pack_dup_16way(bool16);
uint16 __parallel_pack_dup_8way(bool8);
uint32_t __popcount(bool2);
uint32_t __popcount(bool4);
uint32_t __popcount(bool8);
uint32_t __popcount(bool16);
uint32_t __popcount(bool32);
uint32_t __popcount(bool64);
void __popcount_gather(bool2, uint32_t&, bool2&);
void __popcount_gather(bool4, uint32_t&, bool4&);
void __popcount_gather(bool8, uint32_t&, bool8&);
void __popcount_gather(bool16, uint32_t&, bool16&);
void __popcount_gather(bool32, uint32_t&, bool32&);
void __popcount_gather(bool64, uint32_t&, bool64&);
uint32_t __rightmost_bit_detect(bool2);
uint32_t __rightmost_bit_detect(bool4);
uint32_t __rightmost_bit_detect(bool8);
uint32_t __rightmost_bit_detect(bool16);
uint32_t __rightmost_bit_detect(bool32);
uint32_t __rightmost_bit_detect(bool64);
char2 __scatter_set_bits(bool2, char2);
char4 __scatter_set_bits(bool4, char4);
char8 __scatter_set_bits(bool8, char8);
char16 __scatter_set_bits(bool16, char16);
char32 __scatter_set_bits(bool32, char32);
char64 __scatter_set_bits(bool64, char64);
char2 __scatter_unset_bits(bool2, char2);
char4 __scatter_unset_bits(bool4, char4);
char8 __scatter_unset_bits(bool8, char8);
char16 __scatter_unset_bits(bool16, char16);
char32 __scatter_unset_bits(bool32, char32);
char64 __scatter_unset_bits(bool64, char64);
char2 __select(bool2, char2, char2);
char4 __select(bool4, char4, char4);
char8 __select(bool8, char8, char8);
char16 __select(bool16, char16, char16);
char32 __select(bool32, char32, char32);
char64 __select(bool64, char64, char64);
short2 __select(bool2, short2, short2);
short4 __select(bool4, short4, short4);
short8 __select(bool8, short8, short8);
short16 __select(bool16, short16, short16);
short32 __select(bool32, short32, short32);
int2 __select(bool2, int2, int2);
int4 __select(bool4, int4, int4);
int8 __select(bool8, int8, int8);
int16 __select(bool16, int16, int16);
long2 __select(bool2, long2, long2);
long4 __select(bool4, long4, long4);
long8 __select(bool8, long8, long8);
cchar2 __select(bool2, cchar2, cchar2);
cchar4 __select(bool4, cchar4, cchar4);
cchar8 __select(bool8, cchar8, cchar8);
cchar16 __select(bool16, cchar16, cchar16);
cchar32 __select(bool32, cchar32, cchar32);
uchar2 __select(bool2, uchar2, uchar2);
uchar4 __select(bool4, uchar4, uchar4);
uchar8 __select(bool8, uchar8, uchar8);
uchar16 __select(bool16, uchar16, uchar16);
uchar32 __select(bool32, uchar32, uchar32);
uchar64 __select(bool64, uchar64, uchar64);
cshort2 __select(bool2, cshort2, cshort2);
cshort4 __select(bool4, cshort4, cshort4);
cshort8 __select(bool8, cshort8, cshort8);
cshort16 __select(bool16, cshort16, cshort16);
ushort2 __select(bool2, ushort2, ushort2);
ushort4 __select(bool4, ushort4, ushort4);
ushort8 __select(bool8, ushort8, ushort8);
ushort16 __select(bool16, ushort16, ushort16);
ushort32 __select(bool32, ushort32, ushort32);
float2 __select(bool2, float2, float2);
float4 __select(bool4, float4, float4);
float8 __select(bool8, float8, float8);
float16 __select(bool16, float16, float16);
cfloat2 __select(bool2, cfloat2, cfloat2);
cfloat4 __select(bool4, cfloat4, cfloat4);
cfloat8 __select(bool8, cfloat8, cfloat8);
cint2 __select(bool2, cint2, cint2);
cint4 __select(bool4, cint4, cint4);
cint8 __select(bool8, cint8, cint8);
uint2 __select(bool2, uint2, uint2);
uint4 __select(bool4, uint4, uint4);
uint8 __select(bool8, uint8, uint8);
uint16 __select(bool16, uint16, uint16);
double2 __select(bool2, double2, double2);
double4 __select(bool4, double4, double4);
double8 __select(bool8, double8, double8);
cdouble2 __select(bool2, cdouble2, cdouble2);
cdouble4 __select(bool4, cdouble4, cdouble4);
clong2 __select(bool2, clong2, clong2);
clong4 __select(bool4, clong4, clong4);
ulong2 __select(bool2, ulong2, ulong2);
ulong4 __select(bool4, ulong4, ulong4);
ulong8 __select(bool8, ulong8, ulong8);
float2 __select(bool2 a, float2 b, uint2 c);
float4 __select(bool4 a, float4 b, uint4 c);
float8 __select(bool8 a, float8 b, uint8 c);
float16 __select(bool16 a, float16 b, uint16 c);
cfloat2 __select(bool2 a, cfloat2 b, uint4 c);
cfloat4 __select(bool4 a, cfloat4 b, uint8 c);
cfloat8 __select(bool8 a, cfloat8 b, uint16 c);
cint2 __select(bool2 a, cint2 b, uint4 c);
cint4 __select(bool4 a, cint4 b, uint8 c);
cint8 __select(bool8 a, cint8 b, uint16 c);
int2 __select(bool2 a, int2 b, uint2 c);
int4 __select(bool4 a, int4 b, uint4 c);
int8 __select(bool8 a, int8 b, uint8 c);
int16 __select(bool16 a, int16 b, uint16 c);

char2 __shift_left_conditional(bool2, char2, char2);
char4 __shift_left_conditional(bool4, char4, char4);
char8 __shift_left_conditional(bool8, char8, char8);
char16 __shift_left_conditional(bool16, char16, char16);
char32 __shift_left_conditional(bool32, char32, char32);
char64 __shift_left_conditional(bool64, char64, char64);
uchar2 __shift_left_conditional(bool2, uchar2, uchar2);
uchar4 __shift_left_conditional(bool4, uchar4, uchar4);
uchar8 __shift_left_conditional(bool8, uchar8, uchar8);
uchar16 __shift_left_conditional(bool16, uchar16, uchar16);
uchar32 __shift_left_conditional(bool32, uchar32, uchar32);
uchar64 __shift_left_conditional(bool64, uchar64, uchar64);
short2 __shift_left_conditional(bool2, short2, short2);
short4 __shift_left_conditional(bool4, short4, short4);
short8 __shift_left_conditional(bool8, short8, short8);
short16 __shift_left_conditional(bool16, short16, short16);
short32 __shift_left_conditional(bool32, short32, short32);
ushort2 __shift_left_conditional(bool2, ushort2, ushort2);
ushort4 __shift_left_conditional(bool4, ushort4, ushort4);
ushort8 __shift_left_conditional(bool8, ushort8, ushort8);
ushort16 __shift_left_conditional(bool16, ushort16, ushort16);
ushort32 __shift_left_conditional(bool32, ushort32, ushort32);
int2 __shift_left_conditional(bool2, int2, int2);
int4 __shift_left_conditional(bool4, int4, int4);
int8 __shift_left_conditional(bool8, int8, int8);
int16 __shift_left_conditional(bool16, int16, int16);
uint2 __shift_left_conditional(bool2, uint2, uint2);
uint4 __shift_left_conditional(bool4, uint4, uint4);
uint8 __shift_left_conditional(bool8, uint8, uint8);
uint16 __shift_left_conditional(bool16, uint16, uint16);
bool2 __xnor(bool2, bool2);
bool4 __xnor(bool4, bool4);
bool8 __xnor(bool8, bool8);
bool16 __xnor(bool16, bool16);
bool32 __xnor(bool32, bool32);
bool64 __xnor(bool64, bool64);
bool2 __xor(bool2, bool2);
bool4 __xor(bool4, bool4);
bool8 __xor(bool8, bool8);
bool16 __xor(bool16, bool16);
bool32 __xor(bool32, bool32);
bool64 __xor(bool64, bool64);

template<size_t DEPTH>
void __max_circ_pred(char2 a, char2::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vcmaxpb_vvp((vreg_t)a, b_ref, c_ref);
	b = char2(b_ref);
	uint8_t mask_bits = 2 * (sizeof(int8_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __max_circ_pred(char4 a, char4::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vcmaxpb_vvp((vreg_t)a, b_ref, c_ref);
	b = char4(b_ref);
	uint8_t mask_bits = 4 * (sizeof(int8_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __max_circ_pred(char8 a, char8::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vcmaxpb_vvp((vreg_t)a, b_ref, c_ref);
	b = char8(b_ref);
	uint8_t mask_bits = 8 * (sizeof(int8_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __max_circ_pred(char16 a, char16::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vcmaxpb_vvp((vreg_t)a, b_ref, c_ref);
	b = char16(b_ref);
	uint8_t mask_bits = 16 * (sizeof(int8_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __max_circ_pred(char32 a, char32::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vcmaxpb_vvp((vreg_t)a, b_ref, c_ref);
	b = char32(b_ref);
	uint8_t mask_bits = 32 * (sizeof(int8_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __max_circ_pred(char64 a, char64::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vcmaxpb_vvp((vreg_t)a, b_ref, c_ref);
	b = char64(b_ref);
	uint8_t mask_bits = 64 * (sizeof(int8_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}

template<size_t DEPTH>
void __max_circ_pred(short2 a, short2::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vcmaxph_vvp((vreg_t)a, b_ref, c_ref);
	b = short2(b_ref);
	uint8_t mask_bits = 2 * (sizeof(int16_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __max_circ_pred(short4 a, short4::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vcmaxph_vvp((vreg_t)a, b_ref, c_ref);
	b = short4(b_ref);
	uint8_t mask_bits = 4 * (sizeof(int16_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __max_circ_pred(short8 a, short8::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vcmaxph_vvp((vreg_t)a, b_ref, c_ref);
	b = short8(b_ref);
	uint8_t mask_bits = 8 * (sizeof(int16_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __max_circ_pred(short16 a, short16::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vcmaxph_vvp((vreg_t)a, b_ref, c_ref);
	b = short16(b_ref);
	uint8_t mask_bits = 16 * (sizeof(int16_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __max_circ_pred(short32 a, short32::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vcmaxph_vvp((vreg_t)a, b_ref, c_ref);
	b = short32(b_ref);
	uint8_t mask_bits = 32 * (sizeof(int16_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __max_index(char2 a, char2::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vmaxpb_vvp((vreg_t)a, b_ref, c_ref);
	b = char2(b_ref);
	uint8_t mask_bits = 2 * (sizeof(int8_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __max_index(char4 a, char4::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vmaxpb_vvp((vreg_t)a, b_ref, c_ref);
	b = char4(b_ref);
	uint8_t mask_bits = 4 * (sizeof(int8_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __max_index(char8 a, char8::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vmaxpb_vvp((vreg_t)a, b_ref, c_ref);
	b = char8(b_ref);
	uint8_t mask_bits = 8 * (sizeof(int8_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __max_index(char16 a, char16::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vmaxpb_vvp((vreg_t)a, b_ref, c_ref);
	b = char16(b_ref);
	uint8_t mask_bits = 16 * (sizeof(int8_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __max_index(char32 a, char32::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vmaxpb_vvp((vreg_t)a, b_ref, c_ref);
	b = char32(b_ref);
	uint8_t mask_bits = 32 * (sizeof(int8_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __max_index(char64 a, char64::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vmaxpb_vvp((vreg_t)a, b_ref, c_ref);
	b = char64(b_ref);
	uint8_t mask_bits = 64 * (sizeof(int8_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __max_index(long2 a, long2::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vmaxpd_vvp((vreg_t)a, b_ref, c_ref);
	b = long2(b_ref);
	uint8_t mask_bits = 2 * (sizeof(int64_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __max_index(long4 a, long4::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vmaxpd_vvp((vreg_t)a, b_ref, c_ref);
	b = long4(b_ref);
	uint8_t mask_bits = 4 * (sizeof(int64_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __max_index(long8 a, long8::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vmaxpd_vvp((vreg_t)a, b_ref, c_ref);
	b = long8(b_ref);
	uint8_t mask_bits = 8 * (sizeof(int64_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}

template<size_t DEPTH>
void __max_index(short2 a, short2::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vmaxph_vvp((vreg_t)a, b_ref, c_ref);
	b = short2(b_ref);
	uint8_t mask_bits = 2 * (sizeof(int16_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __max_index(short4 a, short4::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vmaxph_vvp((vreg_t)a, b_ref, c_ref);
	b = short4(b_ref);
	uint8_t mask_bits = 4 * (sizeof(int16_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __max_index(short8 a, short8::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vmaxph_vvp((vreg_t)a, b_ref, c_ref);
	b = short8(b_ref);
	uint8_t mask_bits = 8 * (sizeof(int16_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __max_index(short16 a, short16::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vmaxph_vvp((vreg_t)a, b_ref, c_ref);
	b = short16(b_ref);
	uint8_t mask_bits = 16 * (sizeof(int16_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __max_index(short32 a, short32::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vmaxph_vvp((vreg_t)a, b_ref, c_ref);
	b = short32(b_ref);
	uint8_t mask_bits = 32 * (sizeof(int16_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __max_index(int2 a, int2::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vmaxpw_vvp((vreg_t)a, b_ref, c_ref);
	b = int2(b_ref);
	uint8_t mask_bits = 2 * (sizeof(int32_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __max_index(int4 a, int4::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vmaxpw_vvp((vreg_t)a, b_ref, c_ref);
	b = int4(b_ref);
	uint8_t mask_bits = 4 * (sizeof(int32_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __max_index(int8 a, int8::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vmaxpw_vvp((vreg_t)a, b_ref, c_ref);
	b = int8(b_ref);
	uint8_t mask_bits = 8 * (sizeof(int32_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __max_index(int16 a, int16::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vmaxpw_vvp((vreg_t)a, b_ref, c_ref);
	b = int16(b_ref);
	uint8_t mask_bits = 16 * (sizeof(int32_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __max_index(uchar2 a, uchar2::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vmaxupb_vvp((vreg_t)a, b_ref, c_ref);
	b = uchar2(b_ref);
	uint8_t mask_bits = 2 * (sizeof(uint8_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __max_index(uchar4 a, uchar4::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vmaxupb_vvp((vreg_t)a, b_ref, c_ref);
	b = uchar4(b_ref);
	uint8_t mask_bits = 4 * (sizeof(uint8_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __max_index(uchar8 a, uchar8::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vmaxupb_vvp((vreg_t)a, b_ref, c_ref);
	b = uchar8(b_ref);
	uint8_t mask_bits = 8 * (sizeof(uint8_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __max_index(uchar16 a, uchar16::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vmaxupb_vvp((vreg_t)a, b_ref, c_ref);
	b = uchar16(b_ref);
	uint8_t mask_bits = 16 * (sizeof(uint8_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __max_index(uchar32 a, uchar32::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vmaxupb_vvp((vreg_t)a, b_ref, c_ref);
	b = uchar32(b_ref);
	uint8_t mask_bits = 32 * (sizeof(uint8_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __max_index(uchar64 a, uchar64::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vmaxupb_vvp((vreg_t)a, b_ref, c_ref);
	b = uchar64(b_ref);
	uint8_t mask_bits = 64 * (sizeof(uint8_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __max_index(ulong2 a, ulong2::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vmaxupd_vvp((vreg_t)a, b_ref, c_ref);
	b = ulong2(b_ref);
	uint8_t mask_bits = 2 * (sizeof(uint64_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __max_index(ulong4 a, ulong4::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vmaxupd_vvp((vreg_t)a, b_ref, c_ref);
	b = ulong4(b_ref);
	uint8_t mask_bits = 4 * (sizeof(uint64_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __max_index(ulong8 a, ulong8::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vmaxupd_vvp((vreg_t)a, b_ref, c_ref);
	b = ulong8(b_ref);
	uint8_t mask_bits = 8 * (sizeof(uint64_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __max_index(ushort2 a, ushort2::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vmaxuph_vvp((vreg_t)a, b_ref, c_ref);
	b = ushort2(b_ref);
	uint8_t mask_bits = 2 * (sizeof(uint16_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __max_index(ushort4 a, ushort4::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vmaxuph_vvp((vreg_t)a, b_ref, c_ref);
	b = ushort4(b_ref);
	uint8_t mask_bits = 4 * (sizeof(uint16_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __max_index(ushort8 a, ushort8::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vmaxuph_vvp((vreg_t)a, b_ref, c_ref);
	b = ushort8(b_ref);
	uint8_t mask_bits = 8 * (sizeof(uint16_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __max_index(ushort16 a, ushort16::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vmaxuph_vvp((vreg_t)a, b_ref, c_ref);
	b = ushort16(b_ref);
	uint8_t mask_bits = 16 * (sizeof(uint16_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __max_index(ushort32 a, ushort32::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vmaxuph_vvp((vreg_t)a, b_ref, c_ref);
	b = ushort32(b_ref);
	uint8_t mask_bits = 32 * (sizeof(uint16_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __max_index(uint2 a, uint2::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vmaxupw_vvp((vreg_t)a, b_ref, c_ref);
	b = uint2(b_ref);
	uint8_t mask_bits = 2 * (sizeof(uint32_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __max_index(uint4 a, uint4::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vmaxupw_vvp((vreg_t)a, b_ref, c_ref);
	b = uint4(b_ref);
	uint8_t mask_bits = 4 * (sizeof(uint32_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __max_index(uint8 a, uint8::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vmaxupw_vvp((vreg_t)a, b_ref, c_ref);
	b = uint8(b_ref);
	uint8_t mask_bits = 8 * (sizeof(uint32_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __max_index(uint16 a, uint16::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vmaxupw_vvp((vreg_t)a, b_ref, c_ref);
	b = uint16(b_ref);
	uint8_t mask_bits = 16 * (sizeof(uint32_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __min_index(char2 a, char2::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vminpb_vvp((vreg_t)a, b_ref, c_ref);
	b = char2(b_ref);
	uint8_t mask_bits = 2 * (sizeof(int8_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __min_index(char4 a, char4::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vminpb_vvp((vreg_t)a, b_ref, c_ref);
	b = char4(b_ref);
	uint8_t mask_bits = 4 * (sizeof(int8_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __min_index(char8 a, char8::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vminpb_vvp((vreg_t)a, b_ref, c_ref);
	b = char8(b_ref);
	uint8_t mask_bits = 8 * (sizeof(int8_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __min_index(char16 a, char16::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vminpb_vvp((vreg_t)a, b_ref, c_ref);
	b = char16(b_ref);
	uint8_t mask_bits = 16 * (sizeof(int8_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __min_index(char32 a, char32::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vminpb_vvp((vreg_t)a, b_ref, c_ref);
	b = char32(b_ref);
	uint8_t mask_bits = 32 * (sizeof(int8_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __min_index(char64 a, char64::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vminpb_vvp((vreg_t)a, b_ref, c_ref);
	b = char64(b_ref);
	uint8_t mask_bits = 64 * (sizeof(int8_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __min_index(long2 a, long2::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vminpd_vvp((vreg_t)a, b_ref, c_ref);
	b = long2(b_ref);
	uint8_t mask_bits = 2 * (sizeof(int64_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __min_index(long4 a, long4::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vminpd_vvp((vreg_t)a, b_ref, c_ref);
	b = long4(b_ref);
	uint8_t mask_bits = 4 * (sizeof(int64_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __min_index(long8 a, long8::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vminpd_vvp((vreg_t)a, b_ref, c_ref);
	b = long8(b_ref);
	uint8_t mask_bits = 8 * (sizeof(int64_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}

template<size_t DEPTH>
void __min_index(short2 a, short2::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vminph_vvp((vreg_t)a, b_ref, c_ref);
	b = short2(b_ref);
	uint8_t mask_bits = 2 * (sizeof(int16_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __min_index(short4 a, short4::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vminph_vvp((vreg_t)a, b_ref, c_ref);
	b = short4(b_ref);
	uint8_t mask_bits = 4 * (sizeof(int16_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __min_index(short8 a, short8::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vminph_vvp((vreg_t)a, b_ref, c_ref);
	b = short8(b_ref);
	uint8_t mask_bits = 8 * (sizeof(int16_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __min_index(short16 a, short16::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vminph_vvp((vreg_t)a, b_ref, c_ref);
	b = short16(b_ref);
	uint8_t mask_bits = 16 * (sizeof(int16_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __min_index(short32 a, short32::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vminph_vvp((vreg_t)a, b_ref, c_ref);
	b = short32(b_ref);
	uint8_t mask_bits = 32 * (sizeof(int16_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __min_index(int2 a, int2::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vminpw_vvp((vreg_t)a, b_ref, c_ref);
	b = int2(b_ref);
	uint8_t mask_bits = 2 * (sizeof(int32_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __min_index(int4 a, int4::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vminpw_vvp((vreg_t)a, b_ref, c_ref);
	b = int4(b_ref);
	uint8_t mask_bits = 4 * (sizeof(int32_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __min_index(int8 a, int8::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vminpw_vvp((vreg_t)a, b_ref, c_ref);
	b = int8(b_ref);
	uint8_t mask_bits = 8 * (sizeof(int32_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __min_index(int16 a, int16::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vminpw_vvp((vreg_t)a, b_ref, c_ref);
	b = int16(b_ref);
	uint8_t mask_bits = 16 * (sizeof(int32_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __min_index(uchar2 a, uchar2::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vminupb_vvp((vreg_t)a, b_ref, c_ref);
	b = uchar2(b_ref);
	uint8_t mask_bits = 2 * (sizeof(uint8_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __min_index(uchar4 a, uchar4::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vminupb_vvp((vreg_t)a, b_ref, c_ref);
	b = uchar4(b_ref);
	uint8_t mask_bits = 4 * (sizeof(uint8_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __min_index(uchar8 a, uchar8::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vminupb_vvp((vreg_t)a, b_ref, c_ref);
	b = uchar8(b_ref);
	uint8_t mask_bits = 8 * (sizeof(uint8_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __min_index(uchar16 a, uchar16::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vminupb_vvp((vreg_t)a, b_ref, c_ref);
	b = uchar16(b_ref);
	uint8_t mask_bits = 16 * (sizeof(uint8_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __min_index(uchar32 a, uchar32::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vminupb_vvp((vreg_t)a, b_ref, c_ref);
	b = uchar32(b_ref);
	uint8_t mask_bits = 32 * (sizeof(uint8_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __min_index(uchar64 a, uchar64::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vminupb_vvp((vreg_t)a, b_ref, c_ref);
	b = uchar64(b_ref);
	uint8_t mask_bits = 64 * (sizeof(uint8_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __min_index(ulong2 a, ulong2::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vminupd_vvp((vreg_t)a, b_ref, c_ref);
	b = ulong2(b_ref);
	uint8_t mask_bits = 2 * (sizeof(uint64_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __min_index(ulong4 a, ulong4::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vminupd_vvp((vreg_t)a, b_ref, c_ref);
	b = ulong4(b_ref);
	uint8_t mask_bits = 4 * (sizeof(uint64_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __min_index(ulong8 a, ulong8::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vminupd_vvp((vreg_t)a, b_ref, c_ref);
	b = ulong8(b_ref);
	uint8_t mask_bits = 8 * (sizeof(uint64_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}

template<size_t DEPTH>
void __min_index(ushort2 a, ushort2::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vminuph_vvp((vreg_t)a, b_ref, c_ref);
	b = ushort2(b_ref);
	uint8_t mask_bits = 2 * (sizeof(uint16_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __min_index(ushort4 a, ushort4::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vminuph_vvp((vreg_t)a, b_ref, c_ref);
	b = ushort4(b_ref);
	uint8_t mask_bits = 4 * (sizeof(uint16_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __min_index(ushort8 a, ushort8::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vminuph_vvp((vreg_t)a, b_ref, c_ref);
	b = ushort8(b_ref);
	uint8_t mask_bits = 8 * (sizeof(uint16_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __min_index(ushort16 a, ushort16::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vminuph_vvp((vreg_t)a, b_ref, c_ref);
	b = ushort16(b_ref);
	uint8_t mask_bits = 16 * (sizeof(uint16_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __min_index(ushort32 a, ushort32::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vminuph_vvp((vreg_t)a, b_ref, c_ref);
	b = ushort32(b_ref);
	uint8_t mask_bits = 32 * (sizeof(uint16_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __min_index(uint2 a, uint2::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vminupw_vvp((vreg_t)a, b_ref, c_ref);
	b = uint2(b_ref);
	uint8_t mask_bits = 2 * (sizeof(uint32_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __min_index(uint4 a, uint4::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vminupw_vvp((vreg_t)a, b_ref, c_ref);
	b = uint4(b_ref);
	uint8_t mask_bits = 4 * (sizeof(uint32_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __min_index(uint8 a, uint8::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vminupw_vvp((vreg_t)a, b_ref, c_ref);
	b = uint8(b_ref);
	uint8_t mask_bits = 8 * (sizeof(uint32_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}
template<size_t DEPTH>
void __min_index(uint16 a, uint16::EQUIV_ACCESS_T<DEPTH>& b, __vpred& c)
{
	vreg_t b_ref = vreg_t(b);
	vpred_t c_ref = vpred_t(c);
	_vminupw_vvp((vreg_t)a, b_ref, c_ref);
	b = uint16(b_ref);
	uint8_t mask_bits = 16 * (sizeof(uint32_t));
	vpred_t ret_pred_tmp;
	_maskb_kp(mask_bits, ret_pred_tmp);
	_and_ppp(ret_pred_tmp, c_ref, c_ref);
	c = __vpred(c_ref);
}

#define __max_index_pred __max_index
#define __min_index_pred __min_index

#define FACTOR(type) (sizeof(type) == 16 ? 4 : \
                      sizeof(type) ==  8 ? 3 : \
                      sizeof(type) ==  4 ? 2 : \
                      sizeof(type) ==  2 ? 1 : 0)

#define BMINMAX(name,ftype,type,len) \
    template<size_t DEPTH> \
    void name##_bool(type##len a, type##len::EQUIV_ACCESS_T<DEPTH>& b, bool##len& c)\
    { vpred_t pred; _bitxpnd_pkp(c, FACTOR(ftype), pred);             \
      __vpred p_ref = __vpred(pred); name##_pred(a, b, p_ref);        \
      pred = vpred_t(p_ref); _bitpack_pkp(pred, FACTOR(ftype), pred); \
      c = bool##len(pred); \
      return; }

/*-----------------------------------------------------------------------------
* ID: __max_circ_bool()
*----------------------------------------------------------------------------*/
BMINMAX(__max_circ,uint8_t,char,2)
BMINMAX(__max_circ,uint8_t,char,4)
BMINMAX(__max_circ,uint8_t,char,8)
BMINMAX(__max_circ,uint8_t,char,16)
BMINMAX(__max_circ,uint8_t,char,32)
BMINMAX(__max_circ,uint8_t,char,64)

BMINMAX(__max_circ,uint16_t,short,2)
BMINMAX(__max_circ,uint16_t,short,4)
BMINMAX(__max_circ,uint16_t,short,8)
BMINMAX(__max_circ,uint16_t,short,16)
BMINMAX(__max_circ,uint16_t,short,32)

/*-----------------------------------------------------------------------------
* ID: __max_index_bool()
*----------------------------------------------------------------------------*/
BMINMAX(__max_index,uint8_t,char,2)
BMINMAX(__max_index,uint8_t,char,4)
BMINMAX(__max_index,uint8_t,char,8)
BMINMAX(__max_index,uint8_t,char,16)
BMINMAX(__max_index,uint8_t,char,32)
BMINMAX(__max_index,uint8_t,char,64)

BMINMAX(__max_index,uint8_t,uchar,2)
BMINMAX(__max_index,uint8_t,uchar,4)
BMINMAX(__max_index,uint8_t,uchar,8)
BMINMAX(__max_index,uint8_t,uchar,16)
BMINMAX(__max_index,uint8_t,uchar,32)
BMINMAX(__max_index,uint8_t,uchar,64)

BMINMAX(__max_index,uint16_t,short,2)
BMINMAX(__max_index,uint16_t,short,4)
BMINMAX(__max_index,uint16_t,short,8)
BMINMAX(__max_index,uint16_t,short,16)
BMINMAX(__max_index,uint16_t,short,32)

BMINMAX(__max_index,uint16_t,ushort,2)
BMINMAX(__max_index,uint16_t,ushort,4)
BMINMAX(__max_index,uint16_t,ushort,8)
BMINMAX(__max_index,uint16_t,ushort,16)
BMINMAX(__max_index,uint16_t,ushort,32)

BMINMAX(__max_index,uint32_t,int,2)
BMINMAX(__max_index,uint32_t,int,4)
BMINMAX(__max_index,uint32_t,int,8)
BMINMAX(__max_index,uint32_t,int,16)

BMINMAX(__max_index,uint32_t,uint,2)
BMINMAX(__max_index,uint32_t,uint,4)
BMINMAX(__max_index,uint32_t,uint,8)
BMINMAX(__max_index,uint32_t,uint,16)

BMINMAX(__max_index,uint64_t,long,2)
BMINMAX(__max_index,uint64_t,long,4)
BMINMAX(__max_index,uint64_t,long,8)

BMINMAX(__max_index,uint64_t,ulong,2)
BMINMAX(__max_index,uint64_t,ulong,4)
BMINMAX(__max_index,uint64_t,ulong,8)

/*-----------------------------------------------------------------------------
* ID: __min_index_bool()
*----------------------------------------------------------------------------*/
BMINMAX(__min_index,uint8_t,char,2)
BMINMAX(__min_index,uint8_t,char,4)
BMINMAX(__min_index,uint8_t,char,8)
BMINMAX(__min_index,uint8_t,char,16)
BMINMAX(__min_index,uint8_t,char,32)
BMINMAX(__min_index,uint8_t,char,64)

BMINMAX(__min_index,uint8_t,uchar,2)
BMINMAX(__min_index,uint8_t,uchar,4)
BMINMAX(__min_index,uint8_t,uchar,8)
BMINMAX(__min_index,uint8_t,uchar,16)
BMINMAX(__min_index,uint8_t,uchar,32)
BMINMAX(__min_index,uint8_t,uchar,64)

BMINMAX(__min_index,uint16_t,short,2)
BMINMAX(__min_index,uint16_t,short,4)
BMINMAX(__min_index,uint16_t,short,8)
BMINMAX(__min_index,uint16_t,short,16)
BMINMAX(__min_index,uint16_t,short,32)

BMINMAX(__min_index,uint16_t,ushort,2)
BMINMAX(__min_index,uint16_t,ushort,4)
BMINMAX(__min_index,uint16_t,ushort,8)
BMINMAX(__min_index,uint16_t,ushort,16)
BMINMAX(__min_index,uint16_t,ushort,32)

BMINMAX(__min_index,uint32_t,int,2)
BMINMAX(__min_index,uint32_t,int,4)
BMINMAX(__min_index,uint32_t,int,8)
BMINMAX(__min_index,uint32_t,int,16)

BMINMAX(__min_index,uint32_t,uint,2)
BMINMAX(__min_index,uint32_t,uint,4)
BMINMAX(__min_index,uint32_t,uint,8)
BMINMAX(__min_index,uint32_t,uint,16)

BMINMAX(__min_index,uint64_t,long,2)
BMINMAX(__min_index,uint64_t,long,4)
BMINMAX(__min_index,uint64_t,long,8)

BMINMAX(__min_index,uint64_t,ulong,2)
BMINMAX(__min_index,uint64_t,ulong,4)
BMINMAX(__min_index,uint64_t,ulong,8)

#undef __max_index_pred
#undef __min_index_pred
#undef BMINMAX

#endif /* C7X_HE_INTR_H */
