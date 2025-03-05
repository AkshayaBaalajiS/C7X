/*****************************************************************************/
/*  C7X_SCALABLE.H                                                           */
/*                                                                           */
/* Copyright (c) 2021 Texas Instruments Incorporated                         */
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
/* This file provides types and APIs to program the C7x in a vector-width    */
/* agnostic fashion. That is, intead of using types like char64, using types */
/* like c7x::char_vec.                                                       */
/*                                                                           */
/* These types will work with typical arithmetic operations as specified in  */
/* c7x.h and c7x_direct.h as long as an operation is available on the        */
/* current C7x target.                                                       */
/*                                                                           */
/* In order to use these types and APIs, simply #include c7x_scalable.h      */
/* in your source code.                                                      */
/*                                                                           */
/* E.g.,                                                                     */
/* #include <c7x_scalable.h>                                                 */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/* MMA usage: There is also a set of scalable vector utilities that aid      */
/*            writing vector-length agnostic code for the MMA. These         */
/*            utilities are in the c7x_mma.h file.                           */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/* The following APIs are available, all of which are described in further   */
/* detail in the implementations below these comment blocks.                 */
/*                                                                           */
/* - Vector type query and construction                                      */
/*    - c7x::max_simd<T>::value                                              */
/*    - c7x::element_count_of<T>::value                                      */
/*    - c7x::element_type_of<T>::type                                        */
/*    - c7x::component_type_of<T>::type                                      */
/*    - c7x::make_vector<T,N>::type                                          */
/*    - c7x::make_full_vector<T>::type                                       */
/*    - c7x::is_target_vector<T>::value                                      */
/* - Full vector types                                                       */
/*    - c7x::char_vec                                                        */
/*    - c7x::short_vec                                                       */
/*    - etc                                                                  */
/* - Half vector types                                                       */
/*    - c7x::char_hvec                                                       */
/*    - c7x::short_hvec                                                      */
/*    - etc                                                                  */
/* - Quarter vector types                                                    */
/*    - c7x::char_qvec                                                       */
/*    - c7x::short_qvec                                                      */
/*    - etc                                                                  */
/* - Templated vector reinterprets and conversions                           */
/*    - c7x::reinterpret<T>(v)                                               */
/*    - c7x::convert<T>(v)                                                   */
/* - OpenCL style vector reinterprets and conversions                        */
/*    - c7x::as_char_vec(v)                                                  */
/*    - c7x::convert_short_vec(v)                                            */
/*    - etc                                                                  */
/* - Streaming engine and streaming address generator helpers                */
/*    - c7x::se_veclen<T>::value                                             */
/*    - c7x::se_eletype<T>::value                                            */
/*    - c7x::se_eledup<T1,T2>::value                                         */
/*    - c7x::sa_veclen<T>::value                                             */
/*    - c7x::strm_eng<I,T>::get()                                            */
/*    - c7x::strm_eng<I,T>::get_adv()                                        */
/*    - c7x::strm_agen<I,T>::get(p)                                          */
/*    - c7x::strm_agen<I,T>::get_adv(p)                                      */
/*    - c7x::strm_agen<I,T>::get_vpred()                                     */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/* Example usage:                                                            */
/*                                                                           */
/* #include <c7x_scalable.h>                                                 */
/*                                                                           */
/* using namespace c7x;                                                      */
/*                                                                           */
/* // memcpy_scalable_strm<typename S>(const S*in, S *out, int len)          */
/* //                                                                        */
/* // S - A basic data type such as short or float.                          */
/* // in - The input buffer.                                                 */
/* // out - The output buffer.                                               */
/* // len - The number of elements to copy.                                  */
/*                                                                           */
/* // Defaulted template arguments:                                          */
/* // V - A full vector type of S                                            */
/*                                                                           */
/* template<typename S,                                                      */
/*          typename V  = typename make_full_vector<S>::type>                */
/* void memcpy_scalable_strm(const S *restrict in, S *restrict out, int len) */
/* {                                                                         */
/*    //                                                                     */
/*    // Find the maximum number of vector loads/stores needed to copy the   */
/*    // buffer, including any remainder.                                    */
/*    //                                                                     */
/*    int cnt = len / element_count_of<V>::value;                            */
/*    cnt += (len % element_count_of<V>::value > 0);                         */
/*                                                                           */
/*    //                                                                     */
/*    // Initialize the SE for a linear read in and the SA for a linear      */
/*    // write out.                                                          */
/*    //                                                                     */
/*                                                                           */
/*    __SA_TEMPLATE_v1 out_tmplt = __gen_SA_TEMPLATE_v1();                   */
/*                                                                           */
/*    in_tmplt.VECLEN = se_veclen<V>::value;                                 */
/*    in_tmplt.ELETYPE = se_eletype<V>::value;                               */
/*    in_tmplt.ICNT0 = len;                                                  */
/*                                                                           */
/*    out_tmplt.VECLEN = sa_veclen<V>::value;                                */
/*    out_tmplt.ICNT0 = len;                                                 */
/*                                                                           */
/*    __SE0_OPEN(in, in_tmplt);                                              */
/*    __SA0_OPEN(out_tmplt);                                                 */
/*                                                                           */
/*    //                                                                     */
/*    // Perform the copy. If there is remainder, the last store will be     */
/*    // predicated.                                                         */
/*    //                                                                     */
/*    int i;                                                                 */
/*    for (i = 0; i < cnt; i++)                                              */
/*    {                                                                      */
/*        V tmp = strm_eng<0, V>::get_adv();                                 */
/*        __vpred pred = strm_agen<0, V>::get_vpred();                       */
/*        V *addr = strm_agen<0, V>::get_adv(out);                           */
/*        __vstore_pred(pred, addr, tmp);                                    */
/*    }                                                                      */
/*                                                                           */
/*    __SE0_CLOSE();                                                         */
/*    __SA0_CLOSE();                                                         */
/* }                                                                         */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/
#ifndef C7X_SCALABLE_H
#define C7X_SCALABLE_H

#ifndef __cplusplus
#error "c7x_scalable.h requires C++"
#endif /* __cplusplus */

#include <c7x.h>
#include <type_traits> /* std::enable_if_t */

namespace c7x
{
/*****************************************************************************/
/*                                                                           */
/* VECTOR TRAITS                                                             */
/*                                                                           */
/*   Provides interfaces for querying details about vector types.            */
/*                                                                           */
/*****************************************************************************/
/*---------------------------------------------------------------------------*/
/* max_simd -- Query how many times a type may fit in a target vector.       */
/*   Members: size_t value                                                   */
/*   Example: max_simd<int>::value [yields 16 for C7100]                     */
/*---------------------------------------------------------------------------*/
template<typename T> struct max_simd
{ static constexpr size_t value = __C7X_VEC_SIZE_BYTES__ / sizeof(T); };

/*---------------------------------------------------------------------------*/
/* element_count_of -- Query the number of elements in a type.               */
/*   Members: size_t value                                                   */
/*   Example: element_count_of<int16>::value [yields 16]                     */
/*---------------------------------------------------------------------------*/
template<typename T> struct element_count_of {};

/*---------------------------------------------------------------------------*/
/* element_type_of -- Query the element type of a type.                      */
/*   Members: typedef type                                                   */
/*   Example: typename element_type_of<int16>::type [yields int]             */
/*---------------------------------------------------------------------------*/
template<typename T> struct element_type_of {};

/*---------------------------------------------------------------------------*/
/* component_type_of -- Query the compoment type of a type. This type is     */
/*   equivalent to the element type for non-complex types.                   */
/*   Members: typedef type                                                   */
/*   Example: typename component_type_of<cint16>::type [yields int]          */
/*---------------------------------------------------------------------------*/
template<typename T> struct component_type_of {};

/*---------------------------------------------------------------------------*/
/* make_vector -- Create a vector type.                                      */
/*   Members: typedef type                                                   */
/*   Example: typename make_vector<int, 16>::type [yields int16]             */
/*---------------------------------------------------------------------------*/
template<typename T, size_t N> struct make_vector {};

/*---------------------------------------------------------------------------*/
/* make_full_vector -- Create a vector sized to the target width.            */
/*   Members: typedef type                                                   */
/*   Example: make_full_vector<int>::type [yields int16 on C7100]            */
/*---------------------------------------------------------------------------*/
template<typename T> struct make_full_vector
{
    typedef typename make_vector<
                         typename element_type_of<T>::type,
                         max_simd<typename element_type_of<T>::type>::value
                     >::type type;
};

/*---------------------------------------------------------------------------*/
/* is_target_vector -- Query whether the vector type fits on the target.     */
/*   Members: bool value                                                     */
/*   Example: is_target_vector<int16>::value [yields true on C7100]          */
/*---------------------------------------------------------------------------*/
template<typename T> struct is_target_vector
{ static constexpr bool value = false; };

/* Implementation details; don't use directly. */
#define _make_template(_T, _E, _C, _N) \
template<> struct element_count_of<_T>        { static constexpr size_t value = _N; }; \
template<> struct element_count_of<const _T>  { static constexpr size_t value = _N; }; \
template<> struct element_type_of<_T>         { typedef _E type; }; \
template<> struct element_type_of<const _T>   { typedef const _E type; }; \
template<> struct component_type_of<_T>       { typedef _C type; }; \
template<> struct component_type_of<const _T> { typedef const _C type; }; \
template<> struct make_vector<_E, _N>         { typedef _T type; }; \
template<> struct make_vector<const _E, _N>   { typedef const _T type; }; \
template<> struct is_target_vector<_T>        { static constexpr bool value = sizeof(_T) <= __C7X_VEC_SIZE_BYTES__; }; \
template<> struct is_target_vector<const _T>  { static constexpr bool value = sizeof(_T) <= __C7X_VEC_SIZE_BYTES__; };

/* Integral Types */
_make_template(__char64,     signed char, signed char,  64)
_make_template(__char32,     signed char, signed char,  32)
_make_template(__char16,     signed char, signed char,  16)
_make_template(__char8,      signed char, signed char,  8)
_make_template(__char4,      signed char, signed char,  4)
_make_template(__char3,      signed char, signed char,  3)
_make_template(__char2,      signed char, signed char,  2)
_make_template(signed char,  signed char, signed char,  1)

_make_template(__uchar64,      unsigned char, unsigned char,  64)
_make_template(__uchar32,      unsigned char, unsigned char,  32)
_make_template(__uchar16,      unsigned char, unsigned char,  16)
_make_template(__uchar8,       unsigned char, unsigned char,  8)
_make_template(__uchar4,       unsigned char, unsigned char,  4)
_make_template(__uchar3,       unsigned char, unsigned char,  3)
_make_template(__uchar2,       unsigned char, unsigned char,  2)
_make_template(unsigned char,  unsigned char, unsigned char,  1)

_make_template(__bool64,      bool, bool,  64)
_make_template(__bool32,      bool, bool,  32)
_make_template(__bool16,      bool, bool,  16)
_make_template(__bool8,       bool, bool,  8)
_make_template(__bool4,       bool, bool,  4)
_make_template(__bool3,       bool, bool,  3)
_make_template(__bool2,       bool, bool,  2)
_make_template(bool,          bool, bool,  1)

_make_template(__short32,  short, short,  32)
_make_template(__short16,  short, short,  16)
_make_template(__short8,   short, short,  8)
_make_template(__short4,   short, short,  4)
_make_template(__short3,   short, short,  3)
_make_template(__short2,   short, short,  2)
_make_template(short,      short, short,  1)

_make_template(__ushort32,      unsigned short, unsigned short,  32)
_make_template(__ushort16,      unsigned short, unsigned short,  16)
_make_template(__ushort8,       unsigned short, unsigned short,  8)
_make_template(__ushort4,       unsigned short, unsigned short,  4)
_make_template(__ushort3,       unsigned short, unsigned short,  3)
_make_template(__ushort2,       unsigned short, unsigned short,  2)
_make_template(unsigned short,  unsigned short, unsigned short,  1)

_make_template(__int16,  int, int,  16)
_make_template(__int8,   int, int,  8)
_make_template(__int4,   int, int,  4)
_make_template(__int3,   int, int,  3)
_make_template(__int2,   int, int,  2)
_make_template(int,      int, int,  1)

_make_template(__uint16,      unsigned int, unsigned int,  16)
_make_template(__uint8,       unsigned int, unsigned int,  8)
_make_template(__uint4,       unsigned int, unsigned int,  4)
_make_template(__uint3,       unsigned int, unsigned int,  3)
_make_template(__uint2,       unsigned int, unsigned int,  2)
_make_template(unsigned int,  unsigned int, unsigned int,  1)

_make_template(__long8,  long, long,  8)
_make_template(__long4,  long, long,  4)
_make_template(__long3,  long, long,  3)
_make_template(__long2,  long, long,  2)
_make_template(long,     long, long,  1)

_make_template(__ulong8,       unsigned long, unsigned long,  8)
_make_template(__ulong4,       unsigned long, unsigned long,  4)
_make_template(__ulong3,       unsigned long, unsigned long,  3)
_make_template(__ulong2,       unsigned long, unsigned long,  2)
_make_template(unsigned long,  unsigned long, unsigned long,  1)

/* Floating-point types */
_make_template(__float16,  float, float,  16)
_make_template(__float8,   float, float,  8)
_make_template(__float4,   float, float,  4)
_make_template(__float3,   float, float,  3)
_make_template(__float2,   float, float,  2)
_make_template(float,      float, float,  1)

_make_template(__double8,  double, double,  8)
_make_template(__double4,  double, double,  4)
_make_template(__double3,  double, double,  3)
_make_template(__double2,  double, double,  2)
_make_template(double,     double, double,  1)

/* Complex integral types */
_make_template(__cchar32,  __cchar, signed char,  32)
_make_template(__cchar16,  __cchar, signed char,  16)
_make_template(__cchar8,   __cchar, signed char,  8)
_make_template(__cchar4,   __cchar, signed char,  4)
_make_template(__cchar2,   __cchar, signed char,  2)
_make_template(__cchar,    __cchar, signed char,  1)

_make_template(__cshort16,  __cshort, short,  16)
_make_template(__cshort8,   __cshort, short,  8)
_make_template(__cshort4,   __cshort, short,  4)
_make_template(__cshort2,   __cshort, short,  2)
_make_template(__cshort,    __cshort, short,  1)

_make_template(__cint8,  __cint, int,  8)
_make_template(__cint4,  __cint, int,  4)
_make_template(__cint2,  __cint, int,  2)
_make_template(__cint,   __cint, int,  1)

_make_template(__clong4,  __clong, long,  4)
_make_template(__clong2,  __clong, long,  2)
_make_template(__clong,   __clong, long,  1)

/* Complex floating-point types */
_make_template(__cfloat8,  __cfloat, float,  8)
_make_template(__cfloat4,  __cfloat, float,  4)
_make_template(__cfloat2,  __cfloat, float,  2)
_make_template(__cfloat,   __cfloat, float,  1)

_make_template(__cdouble4,  __cdouble, double,  4)
_make_template(__cdouble2,  __cdouble, double,  2)
_make_template(__cdouble,   __cdouble, double,  1)

#undef _make_template

/*****************************************************************************/
/*                                                                           */
/* SCALED VECTOR TYPES                                                       */
/*                                                                           */
/*   Provides types whose size depends on the target that is being compiled. */
/*                                                                           */
/*****************************************************************************/
/*---------------------------------------------------------------------------*/
/* FULL WIDTH VECTOR TYPES -- Types that fill a full target vector register. */
/*---------------------------------------------------------------------------*/
typedef typename make_full_vector<signed char>::type    char_vec;
typedef typename make_full_vector<unsigned char>::type  uchar_vec;
typedef typename make_full_vector<bool>::type           bool_vec;
typedef typename make_full_vector<__cchar>::type        cchar_vec;
typedef typename make_full_vector<short>::type          short_vec;
typedef typename make_full_vector<unsigned short>::type ushort_vec;
typedef typename make_full_vector<__cshort>::type       cshort_vec;
typedef typename make_full_vector<int>::type            int_vec;
typedef typename make_full_vector<unsigned int>::type   uint_vec;
typedef typename make_full_vector<float>::type          float_vec;
typedef typename make_full_vector<__cint>::type         cint_vec;
typedef typename make_full_vector<__cfloat>::type       cfloat_vec;
typedef typename make_full_vector<long>::type           long_vec;
typedef typename make_full_vector<unsigned long>::type  ulong_vec;
typedef typename make_full_vector<double>::type         double_vec;
typedef typename make_full_vector<__clong>::type        clong_vec;
typedef typename make_full_vector<__cdouble>::type      cdouble_vec;

/*---------------------------------------------------------------------------*/
/* HALF WIDTH VECTOR TYPES -- Types that fill one half of a target vector    */
/*   register.                                                               */
/*---------------------------------------------------------------------------*/
typedef typename make_vector<signed char, __C7X_VEC_SIZE_BYTES__/2>::type    char_hvec;
typedef typename make_vector<unsigned char, __C7X_VEC_SIZE_BYTES__/2>::type  uchar_hvec;
typedef typename make_vector<bool, __C7X_VEC_SIZE_BYTES__/2>::type           bool_hvec;
typedef typename make_vector<__cchar, __C7X_VEC_SIZE_BYTES__/4>::type        cchar_hvec;
typedef typename make_vector<short, __C7X_VEC_SIZE_BYTES__/4>::type          short_hvec;
typedef typename make_vector<unsigned short, __C7X_VEC_SIZE_BYTES__/4>::type ushort_hvec;
typedef typename make_vector<__cshort, __C7X_VEC_SIZE_BYTES__/8>::type       cshort_hvec;
typedef typename make_vector<int, __C7X_VEC_SIZE_BYTES__/8>::type            int_hvec;
typedef typename make_vector<unsigned int, __C7X_VEC_SIZE_BYTES__/8>::type   uint_hvec;
typedef typename make_vector<float, __C7X_VEC_SIZE_BYTES__/8>::type          float_hvec;
typedef typename make_vector<__cint, __C7X_VEC_SIZE_BYTES__/16>::type        cint_hvec;
typedef typename make_vector<__cfloat, __C7X_VEC_SIZE_BYTES__/16>::type      cfloat_hvec;
typedef typename make_vector<long, __C7X_VEC_SIZE_BYTES__/16>::type          long_hvec;
typedef typename make_vector<unsigned long, __C7X_VEC_SIZE_BYTES__/16>::type ulong_hvec;
typedef typename make_vector<double, __C7X_VEC_SIZE_BYTES__/16>::type        double_hvec;
typedef typename make_vector<__clong, __C7X_VEC_SIZE_BYTES__/32>::type       clong_hvec;
typedef typename make_vector<__cdouble, __C7X_VEC_SIZE_BYTES__/32>::type     cdouble_hvec;

/*---------------------------------------------------------------------------*/
/* QUARTER WIDTH VECTOR TYPES -- Types that fill one quarter of a target     */
/*   vector register.                                                        */
/*---------------------------------------------------------------------------*/
typedef typename make_vector<signed char, __C7X_VEC_SIZE_BYTES__/4>::type    char_qvec;
typedef typename make_vector<unsigned char, __C7X_VEC_SIZE_BYTES__/4>::type  uchar_qvec;
typedef typename make_vector<bool, __C7X_VEC_SIZE_BYTES__/4>::type           bool_qvec;
typedef typename make_vector<__cchar, __C7X_VEC_SIZE_BYTES__/8>::type        cchar_qvec;
typedef typename make_vector<short, __C7X_VEC_SIZE_BYTES__/8>::type          short_qvec;
typedef typename make_vector<unsigned short, __C7X_VEC_SIZE_BYTES__/8>::type ushort_qvec;
typedef typename make_vector<__cshort, __C7X_VEC_SIZE_BYTES__/16>::type      cshort_qvec;
typedef typename make_vector<int, __C7X_VEC_SIZE_BYTES__/16>::type           int_qvec;
typedef typename make_vector<unsigned int, __C7X_VEC_SIZE_BYTES__/16>::type  uint_qvec;
typedef typename make_vector<float, __C7X_VEC_SIZE_BYTES__/16>::type         float_qvec;
typedef typename make_vector<__cint, __C7X_VEC_SIZE_BYTES__/32>::type        cint_qvec;
typedef typename make_vector<__cfloat, __C7X_VEC_SIZE_BYTES__/32>::type      cfloat_qvec;
typedef typename make_vector<long, __C7X_VEC_SIZE_BYTES__/32>::type          long_qvec;
typedef typename make_vector<unsigned long, __C7X_VEC_SIZE_BYTES__/32>::type ulong_qvec;
typedef typename make_vector<double, __C7X_VEC_SIZE_BYTES__/32>::type        double_qvec;
#if __C7X_VEC_SIZE_BYTES__ >= 64
typedef typename make_vector<__clong, __C7X_VEC_SIZE_BYTES__/64>::type       clong_qvec;
typedef typename make_vector<__cdouble, __C7X_VEC_SIZE_BYTES__/64>::type     cdouble_qvec;
#endif /* __C7X_VEC_SIZE_BYTES__ >= 64 */

/*****************************************************************************/
/*                                                                           */
/* TEMPLATED VECTOR CONVERSIONS                                              */
/*                                                                           */
/*****************************************************************************/
/*---------------------------------------------------------------------------*/
/* reinterpret -- Reinterpret one vector type as another.                    */
/*   Example: reinterpret<int16>(v) [returns v as int16]                     */
/*   Example: reinterpret<int16, char64>(v) [returns v as int16]             */
/*---------------------------------------------------------------------------*/
/* convert -- Convert one vector type to another.                            */
/*   Example: convert<int16>(v) [returns v converted to int16]               */
/*   Example: convert<int16, char16>(v) [returns v converted to int16]       */
/*---------------------------------------------------------------------------*/

#define Always_Inline __attribute__((always_inline))

#define _make_template(_T, _S) \
template<typename TO, typename FROM> \
inline typename std::enable_if<std::is_same<typename std::remove_cv<TO>::type, _T>::value, _T>::type \
reinterpret(FROM in) Always_Inline { return __as_ ## _S(in); } \
template<typename TO, typename FROM> \
inline typename std::enable_if<std::is_same<typename std::remove_cv<TO>::type, _T>::value, _T>::type \
convert(FROM in) Always_Inline { return __convert_ ## _S(in); }

/* Integral Types */
_make_template(__char64, char64)
_make_template(__char32, char32)
_make_template(__char16, char16)
_make_template(__char8, char8)
_make_template(__char4, char4)
_make_template(__char3, char3)
_make_template(__char2, char2)
_make_template(signed char, char)

_make_template(__uchar64, uchar64)
_make_template(__uchar32, uchar32)
_make_template(__uchar16, uchar16)
_make_template(__uchar8, uchar8)
_make_template(__uchar4, uchar4)
_make_template(__uchar3, uchar3)
_make_template(__uchar2, uchar2)
_make_template(unsigned char, uchar)

_make_template(__bool64, bool64)
_make_template(__bool32, bool32)
_make_template(__bool16, bool16)
_make_template(__bool8, bool8)
_make_template(__bool4, bool4)
_make_template(__bool3, bool3)
_make_template(__bool2, bool2)
_make_template(bool, bool)

_make_template(__short32, short32)
_make_template(__short16, short16)
_make_template(__short8, short8)
_make_template(__short4, short4)
_make_template(__short3, short3)
_make_template(__short2, short2)
_make_template(short, short)

_make_template(__ushort32, ushort32)
_make_template(__ushort16, ushort16)
_make_template(__ushort8, ushort8)
_make_template(__ushort4, ushort4)
_make_template(__ushort3, ushort3)
_make_template(__ushort2, ushort2)
_make_template(unsigned short, ushort)

_make_template(__int16, int16)
_make_template(__int8, int8)
_make_template(__int4, int4)
_make_template(__int3, int3)
_make_template(__int2, int2)
_make_template(int, int)

_make_template(__uint16, uint16)
_make_template(__uint8, uint8)
_make_template(__uint4, uint4)
_make_template(__uint3, uint3)
_make_template(__uint2, uint2)
_make_template(unsigned int, uint)

_make_template(__long8, long8)
_make_template(__long4, long4)
_make_template(__long3, long3)
_make_template(__long2, long2)
_make_template(long, long)

_make_template(__ulong8, ulong8)
_make_template(__ulong4, ulong4)
_make_template(__ulong3, ulong3)
_make_template(__ulong2, ulong2)
_make_template(unsigned long, ulong)

/* Floating-point types */
_make_template(__float16, float16)
_make_template(__float8, float8)
_make_template(__float4, float4)
_make_template(__float3, float3)
_make_template(__float2, float2)
_make_template(float, float)

_make_template(__double8, double8)
_make_template(__double4, double4)
_make_template(__double3, double3)
_make_template(__double2, double2)
_make_template(double, double)

/* Complex integral types */
_make_template(__cchar32, cchar32)
_make_template(__cchar16, cchar16)
_make_template(__cchar8, cchar8)
_make_template(__cchar4, cchar4)
_make_template(__cchar2, cchar2)
_make_template(__cchar, cchar)

_make_template(__cshort16, cshort16)
_make_template(__cshort8, cshort8)
_make_template(__cshort4, cshort4)
_make_template(__cshort2, cshort2)
_make_template(__cshort, cshort)

_make_template(__cint8, cint8)
_make_template(__cint4, cint4)
_make_template(__cint2, cint2)
_make_template(__cint, cint)

_make_template(__clong4, clong4)
_make_template(__clong2, clong2)
_make_template(__clong, clong)

/* Complex floating-point types */
_make_template(__cfloat8, cfloat8)
_make_template(__cfloat4, cfloat4)
_make_template(__cfloat2, cfloat2)
_make_template(__cfloat, cfloat)

_make_template(__cdouble4, cdouble4)
_make_template(__cdouble2, cdouble2)
_make_template(__cdouble, cdouble)

#undef _make_template

/*****************************************************************************/
/*                                                                           */
/* VECTOR CONVERSIONS                                                        */
/*                                                                           */
/*   Wraps reinterpret() and convert() implementations for scaled vector     */
/*   types in vector style syntax.                                           */
/*                                                                           */
/*****************************************************************************/
/*---------------------------------------------------------------------------*/
/* as_[scaling type] -- Reinterpret one vector type as another scaling type. */
/*   Designed to be used similarly to vector as_* operators like as_char16.  */
/*   Example: as_char_vec(v) [returns v as target char_vec]                  */
/*---------------------------------------------------------------------------*/
/* convert_[scaling type] -- Convert one vector type to another scaling type.*/
/*   Designed to be used similarly to vector convert_* operators like        */
/*   convert_char16.                                                         */
/*   Example: convert_char_vec(v) [returns v converted to target char_vec]   */
/*---------------------------------------------------------------------------*/

#define _make_template(_T) \
template<typename FROM> \
static inline _T as_ ## _T(FROM f) Always_Inline { return reinterpret<_T, FROM>(f); } \
template<typename FROM> \
static inline _T convert_ ## _T(FROM f) Always_Inline { return convert<_T, FROM>(f); }

_make_template(char_vec)
_make_template(uchar_vec)
_make_template(bool_vec)
_make_template(cchar_vec)
_make_template(short_vec)
_make_template(ushort_vec)
_make_template(cshort_vec)
_make_template(int_vec)
_make_template(uint_vec)
_make_template(float_vec)
_make_template(cint_vec)
_make_template(cfloat_vec)
_make_template(long_vec)
_make_template(ulong_vec)
_make_template(double_vec)
_make_template(clong_vec)
_make_template(cdouble_vec)

_make_template(char_hvec)
_make_template(uchar_hvec)
_make_template(bool_hvec)
_make_template(cchar_hvec)
_make_template(short_hvec)
_make_template(ushort_hvec)
_make_template(cshort_hvec)
_make_template(int_hvec)
_make_template(uint_hvec)
_make_template(float_hvec)
_make_template(cint_hvec)
_make_template(cfloat_hvec)
_make_template(long_hvec)
_make_template(ulong_hvec)
_make_template(double_hvec)
_make_template(clong_hvec)
_make_template(cdouble_hvec)

_make_template(char_qvec)
_make_template(uchar_qvec)
_make_template(bool_qvec)
_make_template(cchar_qvec)
_make_template(short_qvec)
_make_template(ushort_qvec)
_make_template(cshort_qvec)
_make_template(int_qvec)
_make_template(uint_qvec)
_make_template(float_qvec)
_make_template(cint_qvec)
_make_template(cfloat_qvec)
_make_template(long_qvec)
_make_template(ulong_qvec)
_make_template(double_qvec)
#if __C7X_VEC_SIZE_BYTES__ >= 64
_make_template(clong_qvec)
_make_template(cdouble_qvec)
#endif /* __C7X_VEC_SIZE_BYTES__ >= 64 */

#undef _make_template

/*****************************************************************************/
/*                                                                           */
/* STREAMING ENGINE (SE), STREAMING ADDRESS GENERATOR (SA) TRAITS            */
/*                                                                           */
/*****************************************************************************/
/*---------------------------------------------------------------------------*/
/* se_veclen_from_traits -- Query for a corresponding __SE_VECLEN value      */
/*   given the number of elements in a vector. Generally, use of se_veclen   */
/*   is instead recommended.                                                 */
/*   Members: __SE_VECLEN value                                              */
/*   Example: se_veclen_from_traits<2>::value [yields __SE_VECLEN_2ELEMS]    */
/*---------------------------------------------------------------------------*/
template<size_t S> struct se_veclen_from_traits {};

template<> struct se_veclen_from_traits<1>
{ static constexpr __SE_VECLEN value = __SE_VECLEN_1ELEM; };
template<> struct se_veclen_from_traits<2>
{ static constexpr __SE_VECLEN value = __SE_VECLEN_2ELEMS; };
template<> struct se_veclen_from_traits<4>
{ static constexpr __SE_VECLEN value = __SE_VECLEN_4ELEMS; };
template<> struct se_veclen_from_traits<8>
{ static constexpr __SE_VECLEN value = __SE_VECLEN_8ELEMS; };
template<> struct se_veclen_from_traits<16>
{ static constexpr __SE_VECLEN value = __SE_VECLEN_16ELEMS; };
template<> struct se_veclen_from_traits<32>
{ static constexpr __SE_VECLEN value = __SE_VECLEN_32ELEMS; };
template<> struct se_veclen_from_traits<64>
{ static constexpr __SE_VECLEN value = __SE_VECLEN_64ELEMS; };

/*---------------------------------------------------------------------------*/
/* se_veclen -- Query for a corresponding __SE_VECLEN value for a given type.*/
/*   Members: __SE_VECLEN value                                              */
/*   Example: se_veclen<int16>::value [yields __SE_VECLEN_16ELEMS]           */
/*---------------------------------------------------------------------------*/
template<typename T> struct se_veclen
{
    static constexpr __SE_VECLEN value = se_veclen_from_traits<
                                             element_count_of<T>::value>::value;
};

/*---------------------------------------------------------------------------*/
/* se_eletype_from_traits -- Query for a corresponding __SE_ELETYPE given    */
/*   the size of elements, whether elements are complex, and whether to swap */
/*   complex elements. Generally, use of se_eletype is instead recommended.  */
/*   Members: __SE_ELETYPE value                                             */
/*   Example: se_eletype_from_traits<1, false, false>::value                 */
/*            [yields __SE_ELETYPE_8BIT]                                     */
/*---------------------------------------------------------------------------*/
template<size_t SIZE, bool CMPLX=false, bool SWAP=false>
struct se_eletype_from_traits {};

template<> struct se_eletype_from_traits<1, false, false>
{ static constexpr __SE_ELETYPE value = __SE_ELETYPE_8BIT; };
template<> struct se_eletype_from_traits<2, false, false>
{ static constexpr __SE_ELETYPE value = __SE_ELETYPE_16BIT; };
template<> struct se_eletype_from_traits<4, false, false>
{ static constexpr __SE_ELETYPE value = __SE_ELETYPE_32BIT; };
template<> struct se_eletype_from_traits<8, false, false>
{ static constexpr __SE_ELETYPE value = __SE_ELETYPE_64BIT; };
template<> struct se_eletype_from_traits<2, true, false>
{ static constexpr __SE_ELETYPE value = __SE_ELETYPE_8BIT_CMPLX_NOSWAP; };
template<> struct se_eletype_from_traits<4, true, false>
{ static constexpr __SE_ELETYPE value = __SE_ELETYPE_16BIT_CMPLX_NOSWAP; };
template<> struct se_eletype_from_traits<8, true, false>
{ static constexpr __SE_ELETYPE value = __SE_ELETYPE_32BIT_CMPLX_NOSWAP; };
template<> struct se_eletype_from_traits<16, true, false>
{ static constexpr __SE_ELETYPE value = __SE_ELETYPE_64BIT_CMPLX_NOSWAP; };
template<> struct se_eletype_from_traits<2, true, true>
{ static constexpr __SE_ELETYPE value = __SE_ELETYPE_8BIT_CMPLX_SWAP; };
template<> struct se_eletype_from_traits<4, true, true>
{ static constexpr __SE_ELETYPE value = __SE_ELETYPE_16BIT_CMPLX_SWAP; };
template<> struct se_eletype_from_traits<8, true, true>
{ static constexpr __SE_ELETYPE value = __SE_ELETYPE_32BIT_CMPLX_SWAP; };
template<> struct se_eletype_from_traits<16, true, true>
{ static constexpr __SE_ELETYPE value = __SE_ELETYPE_64BIT_CMPLX_SWAP; };

/*---------------------------------------------------------------------------*/
/* se_eletype -- Query for a corresponding __SE_ELETYPE given a scalar or    */
/*   vector type.                                                            */
/*   Members: __SE_ELETYPE value                                             */
/*   Example: se_eletype<char64>::value [yields __SE_ELETYPE_8BIT]           */
/*---------------------------------------------------------------------------*/
template<typename T>
struct se_eletype
{
    static constexpr size_t _ES = sizeof(typename element_type_of<T>::type);
    static constexpr size_t _CS = sizeof(typename component_type_of<T>::type);

    static constexpr __SE_ELETYPE value = se_eletype_from_traits<
                                                             _ES,
                                                             _CS != _ES,
                                                             _CS != _ES>::value;
};

/*---------------------------------------------------------------------------*/
/* se_eledup_from_traits -- Query for a corresponding __SE_ELEDUP value      */
/*   given the duplication multiplier. Generally, use of se_eledup is        */
/*   instead recommended.                                                    */
/*   Members: __SE_ELEDUP value                                              */
/*   Example: se_eledup_from_traits<4>::value [yields __SE_ELEDUP_4X]        */
/*---------------------------------------------------------------------------*/
/* Given enum value from int multiplier */
template<size_t DUP> struct se_eledup_from_traits {};

template<> struct se_eledup_from_traits<1>
{ static constexpr __SE_ELEDUP value = __SE_ELEDUP_OFF; };
template<> struct se_eledup_from_traits<2>
{ static constexpr __SE_ELEDUP value = __SE_ELEDUP_2X; };
template<> struct se_eledup_from_traits<4>
{ static constexpr __SE_ELEDUP value = __SE_ELEDUP_4X; };
template<> struct se_eledup_from_traits<8>
{ static constexpr __SE_ELEDUP value = __SE_ELEDUP_8X; };
template<> struct se_eledup_from_traits<16>
{ static constexpr __SE_ELEDUP value = __SE_ELEDUP_16X; };
template<> struct se_eledup_from_traits<32>
{ static constexpr __SE_ELEDUP value = __SE_ELEDUP_32X; };
#if __C7X_VEC_SIZE_BITS__ >= 512
template<> struct se_eledup_from_traits<64>
{ static constexpr __SE_ELEDUP value = __SE_ELEDUP_64X; };
#endif

/*---------------------------------------------------------------------------*/
/* se_eledup -- Query for a corresponding __SE_ELEDUP value for a given      */
/*   input type. If the second template parameter is not specified, the      */
/*   result type defaults to a full target vector of the input type.         */
/*   Members: __SE_ELEDUP value                                              */
/*   Example: se_eledup<int4,int8>::value [yields __SE_ELEDUP_2X]            */
/*   Example: se_eledup<int4>::value [yields __SE_ELEDUP_4X on C7100]        */
/*---------------------------------------------------------------------------*/
template<typename IN_T,
         typename RES_T = typename make_full_vector<IN_T>::type>
struct se_eledup
{
    static constexpr __SE_ELEDUP value =
                    se_eledup_from_traits<element_count_of<RES_T>::value /
                                          element_count_of<IN_T>::value>::value;
};

/*---------------------------------------------------------------------------*/
/* sa_veclen_from_traits -- Query for a corresponding __SA_VECLEN value      */
/*   given the number of elements in a vector. Generally, use of sa_veclen   */
/*   is instead recommended.                                                 */
/*   Members: __SA_VECLEN value                                              */
/*   Example: sa_veclen_from_traits<2>::value [yields __SA_VECLEN_2ELEMS]    */
/*---------------------------------------------------------------------------*/
template<size_t S> struct sa_veclen_from_traits {};

template<> struct sa_veclen_from_traits<1>
{ static constexpr __SA_VECLEN value = __SA_VECLEN_1ELEM; };
template<> struct sa_veclen_from_traits<2>
{ static constexpr __SA_VECLEN value = __SA_VECLEN_2ELEMS; };
template<> struct sa_veclen_from_traits<4>
{ static constexpr __SA_VECLEN value = __SA_VECLEN_4ELEMS; };
template<> struct sa_veclen_from_traits<8>
{ static constexpr __SA_VECLEN value = __SA_VECLEN_8ELEMS; };
template<> struct sa_veclen_from_traits<16>
{ static constexpr __SA_VECLEN value = __SA_VECLEN_16ELEMS; };
template<> struct sa_veclen_from_traits<32>
{ static constexpr __SA_VECLEN value = __SA_VECLEN_32ELEMS; };
#if __C7X_VEC_SIZE_BITS__ >= 512
template<> struct sa_veclen_from_traits<64>
{ static constexpr __SA_VECLEN value = __SA_VECLEN_64ELEMS; };
#endif

/*---------------------------------------------------------------------------*/
/* sa_veclen -- Query for a corresponding __SA_VECLEN value for a given type.*/
/*   Members: __SA_VECLEN value                                              */
/*   Example: sa_veclen<int16>::value [yields __SA_VECLEN_16ELEMS]           */
/*---------------------------------------------------------------------------*/
template<typename T> struct sa_veclen
{
    static constexpr __SA_VECLEN value = sa_veclen_from_traits<
                                             element_count_of<T>::value>::value;
};

/*****************************************************************************/
/*                                                                           */
/* STREAMING ENGINE (SE), STREAMING ADDRESS GENERATOR (SA) ACCESSORS         */
/*                                                                           */
/*****************************************************************************/
/*---------------------------------------------------------------------------*/
/* strm_eng -- Used to access an open streaming engine (SE) instance.        */
/*   Members: T get(): Get the stream value without advancing.               */
/*            T get_adv(): Get the stream value and advance.                 */
/*   Example: strm_eng<0, int16>::get_adv() [yields the next int16]          */
/*---------------------------------------------------------------------------*/
template<unsigned int id, typename T> struct strm_eng {};

/*---------------------------------------------------------------------------*/
/* strm_agen -- Used to access an open streaming address generator (SA)      */
/*   instance.                                                               */
/*   Members: T *get(): Get the stream value without advancing.              */
/*            T *get_adv(): Get the stream value and advance.                */
/*            __vpred get_vpred(): Get the next predicate value.             */
/*   Example: strm_agen<0, int16>::get_adv(ptr) [yields the next int16*]     */
/*---------------------------------------------------------------------------*/
template<unsigned int id, typename T> struct strm_agen {};

/* Implementation details; don't use directly. */
/* Bool not currently supported due to lack of 1 element interface. */
#define _make_template(_T, _t) \
template<unsigned int id> \
struct strm_eng<id, _T> \
{ \
    static Always_Inline _T get() \
    { \
        static_assert(id <= 1, "SE id is out of range."); \
        return __se_ac_ ## _t(id, /* adv= */0); \
    } \
 \
    static Always_Inline _T get_adv() \
    { \
        static_assert(id <= 1, "SE id is out of range."); \
        return __se_ac_ ## _t(id, /* adv= */1); \
    } \
}; \
 \
template<unsigned int id> \
struct strm_agen<id, _T> \
{ \
    static Always_Inline _T* get(const void *p) \
    { \
        static_assert(id <= 3, "SA id is out of range."); \
        return (_T*)__sa(id, sizeof(_T)/__numelemof(_T), p); \
    } \
 \
    static Always_Inline _T* get_adv(const void *p) \
    { \
        static_assert(id <= 3, "SA id is out of range."); \
        return (_T*)__sa_adv(id, sizeof(_T)/__numelemof(_T), p); \
    } \
 \
    static Always_Inline __vpred get_vpred() \
    { \
        static_assert(id <= 3, "SA id is out of range."); \
        return __sa_vpred(id, sizeof(_T)/__numelemof(_T)); \
    } \
};

#if __C7X_VEC_SIZE_BITS__ >= 512
/* Integral Types */
_make_template(__char64, char64)
_make_template(__uchar64, uchar64)
_make_template(__short32, short32)
_make_template(__ushort32, ushort32)
_make_template(__int16, int16)
_make_template(__uint16, uint16)
_make_template(__long8, long8)
_make_template(__ulong8, ulong8)

/* Floating-point types */
_make_template(__float16, float16)
_make_template(__double8, double8)

/* Complex integral types */
_make_template(__cchar32, cchar32)
_make_template(__cshort16, cshort16)
_make_template(__cint8, cint8)
_make_template(__clong4, clong4)

/* Complex floating-point types */
_make_template(__cfloat8, cfloat8)
_make_template(__cdouble4, cdouble4)
#endif

/* Integral Types */
_make_template(__char32, char32)
_make_template(__uchar32, uchar32)
_make_template(__short16, short16)
_make_template(__ushort16, ushort16)
_make_template(__int8, int8)
_make_template(__uint8, uint8)
_make_template(__long4, long4)
_make_template(__ulong4, ulong4)

/* Floating-point types */
_make_template(__float8, float8)
_make_template(__double4, double4)

/* Complex integral types */
_make_template(__cchar16, cchar16)
_make_template(__cshort8, cshort8)
_make_template(__cint4, cint4)
_make_template(__clong2, clong2)

/* Complex floating-point types */
_make_template(__cfloat4, cfloat4)
_make_template(__cdouble2, cdouble2)

/* Integral Types */
_make_template(__char16, char16)
_make_template(__char8, char8)
_make_template(__char4, char4)
_make_template(__char2, char2)
_make_template(signed char, char)

_make_template(__uchar16, uchar16)
_make_template(__uchar8, uchar8)
_make_template(__uchar4, uchar4)
_make_template(__uchar2, uchar2)
_make_template(unsigned char, uchar)

_make_template(__short8, short8)
_make_template(__short4, short4)
_make_template(__short2, short2)
_make_template(short, short)

_make_template(__ushort8, ushort8)
_make_template(__ushort4, ushort4)
_make_template(__ushort2, ushort2)
_make_template(unsigned short, ushort)

_make_template(__int4, int4)
_make_template(__int2, int2)
_make_template(int, int)

_make_template(__uint4, uint4)
_make_template(__uint2, uint2)
_make_template(unsigned int, uint)

_make_template(__long2, long2)
_make_template(long, long)

_make_template(__ulong2, ulong2)
_make_template(unsigned long, ulong)

/* Floating-point types */
_make_template(__float4, float4)
_make_template(__float2, float2)
_make_template(float, float)

_make_template(__double2, double2)
_make_template(double, double)

/* Complex integral types */
_make_template(__cchar8, cchar8)
_make_template(__cchar4, cchar4)
_make_template(__cchar2, cchar2)
_make_template(__cchar, cchar)

_make_template(__cshort4, cshort4)
_make_template(__cshort2, cshort2)
_make_template(__cshort, cshort)

_make_template(__cint2, cint2)
_make_template(__cint, cint)

_make_template(__clong, clong)

/* Complex floating-point types */
_make_template(__cfloat2, cfloat2)
_make_template(__cfloat, cfloat)

_make_template(__cdouble, cdouble)

#undef _make_template

#undef Always_Inline

} /* namespace c7x */

#endif /* C7X_SCALABLE_H */
