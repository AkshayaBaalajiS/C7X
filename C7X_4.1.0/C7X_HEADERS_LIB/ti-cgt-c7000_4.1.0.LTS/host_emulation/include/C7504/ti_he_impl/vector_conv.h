/*****************************************************************************/
/*  VECTOR_CONV.H                                                            */
/*                                                                           */
/* Copyright (c) 2018 Texas Instruments Incorporated                         */
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
#ifndef VECTOR_CONV_H
#define VECTOR_CONV_H

#include <type_traits>

#include <cstdint>

//-----------------------------------------------------------------------------
// CONVERT_<TYPE> CASTING CONVERSIONS - THESE CONVERSIONS TAKE TWO VECTORS OF
// VARYING TYPES AND IDENTICAL NUMBERS OF ELEMENTS AND CONVERTS EACH SOURCE
// ELEMENT INTO THE DESTINATION TYPE.
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// _CONV_CONV_V_TO_V: Vector to vector conversion
//-----------------------------------------------------------------------------
#define _CONV_CONV_V_TO_V(Name, Ty, Nelem)                                     \
template <typename SRC_T, size_t SRC_NELEM, VTYPE_KIND KIND>                   \
vtype<Ty, Nelem, VTYPE_KIND::DATA> __convert_ ## Name(const vtype<SRC_T, SRC_NELEM, KIND> &src) \
{                                                                              \
    using DST_T = Ty;                                                          \
                                                                               \
    constexpr size_t DST_NELEM = Nelem;                                        \
                                                                               \
    static_assert(SRC_NELEM == DST_NELEM,                                      \
                  "Illegal conversion cast: Element counts must be the same"); \
                                                                               \
    vtype<DST_T, DST_NELEM, VTYPE_KIND::DATA> res;                             \
    for (size_t i = 0; i < DST_NELEM; i++)                                     \
        res.s[i] = (DST_T)src.s[i];                                            \
                                                                               \
    return res;                                                                \
}

_CONV_CONV_V_TO_V(long16, int64_t, 16)
_CONV_CONV_V_TO_V(long8, int64_t, 8)
_CONV_CONV_V_TO_V(long4, int64_t, 4)
_CONV_CONV_V_TO_V(long3, int64_t, 3)
_CONV_CONV_V_TO_V(long2, int64_t, 2)

_CONV_CONV_V_TO_V(ulong16, uint64_t, 16)
_CONV_CONV_V_TO_V(ulong8, uint64_t, 8)
_CONV_CONV_V_TO_V(ulong4, uint64_t, 4)
_CONV_CONV_V_TO_V(ulong3, uint64_t, 3)
_CONV_CONV_V_TO_V(ulong2, uint64_t, 2)

_CONV_CONV_V_TO_V(double16, double, 16)
_CONV_CONV_V_TO_V(double8, double, 8)
_CONV_CONV_V_TO_V(double4, double, 4)
_CONV_CONV_V_TO_V(double3, double, 3)
_CONV_CONV_V_TO_V(double2, double, 2)

_CONV_CONV_V_TO_V(int16, int32_t, 16)
_CONV_CONV_V_TO_V(int8,  int32_t, 8)
_CONV_CONV_V_TO_V(int4,  int32_t, 4)
_CONV_CONV_V_TO_V(int3,  int32_t, 3)
_CONV_CONV_V_TO_V(int2,  int32_t, 2)

_CONV_CONV_V_TO_V(uint16, uint32_t, 16)
_CONV_CONV_V_TO_V(uint8,  uint32_t, 8)
_CONV_CONV_V_TO_V(uint4,  uint32_t, 4)
_CONV_CONV_V_TO_V(uint3,  uint32_t, 3)
_CONV_CONV_V_TO_V(uint2,  uint32_t, 2)

_CONV_CONV_V_TO_V(float16, float, 16)
_CONV_CONV_V_TO_V(float8,  float, 8)
_CONV_CONV_V_TO_V(float4,  float, 4)
_CONV_CONV_V_TO_V(float3,  float, 3)
_CONV_CONV_V_TO_V(float2,  float, 2)

_CONV_CONV_V_TO_V(short32, int16_t, 32)
_CONV_CONV_V_TO_V(short16, int16_t, 16)
_CONV_CONV_V_TO_V(short8,  int16_t, 8)
_CONV_CONV_V_TO_V(short4,  int16_t, 4)
_CONV_CONV_V_TO_V(short3,  int16_t, 3)
_CONV_CONV_V_TO_V(short2,  int16_t, 2)

_CONV_CONV_V_TO_V(ushort32, uint16_t, 32)
_CONV_CONV_V_TO_V(ushort16, uint16_t, 16)
_CONV_CONV_V_TO_V(ushort8,  uint16_t, 8)
_CONV_CONV_V_TO_V(ushort4,  uint16_t, 4)
_CONV_CONV_V_TO_V(ushort3,  uint16_t, 3)
_CONV_CONV_V_TO_V(ushort2,  uint16_t, 2)

_CONV_CONV_V_TO_V(char64, int8_t, 64)
_CONV_CONV_V_TO_V(char32, int8_t, 32)
_CONV_CONV_V_TO_V(char16, int8_t, 16)
_CONV_CONV_V_TO_V(char8,  int8_t, 8)
_CONV_CONV_V_TO_V(char4,  int8_t, 4)
_CONV_CONV_V_TO_V(char3,  int8_t, 3)
_CONV_CONV_V_TO_V(char2,  int8_t, 2)

_CONV_CONV_V_TO_V(uchar64, uint8_t, 64)
_CONV_CONV_V_TO_V(uchar32, uint8_t, 32)
_CONV_CONV_V_TO_V(uchar16, uint8_t, 16)
_CONV_CONV_V_TO_V(uchar8,  uint8_t, 8)
_CONV_CONV_V_TO_V(uchar4,  uint8_t, 4)
_CONV_CONV_V_TO_V(uchar3,  uint8_t, 3)
_CONV_CONV_V_TO_V(uchar2,  uint8_t, 2)

_CONV_CONV_V_TO_V(bool64, bool, 64)
_CONV_CONV_V_TO_V(bool32, bool, 32)
_CONV_CONV_V_TO_V(bool16, bool, 16)
_CONV_CONV_V_TO_V(bool8,  bool, 8)
_CONV_CONV_V_TO_V(bool4,  bool, 4)
_CONV_CONV_V_TO_V(bool3,  bool, 3)
_CONV_CONV_V_TO_V(bool2,  bool, 2)

#undef _CONV_CONV_V_TO_V

//-----------------------------------------------------------------------------
// _CONV_CONV_S_TO_S: Scalar to scalar conversion
//-----------------------------------------------------------------------------
#define _CONV_CONV_S_TO_S(Name, Ty)                                            \
template <typename SRC_T,                                                      \
           typename = typename std::enable_if_t<std::is_arithmetic<SRC_T>::value>>\
Ty __convert_ ## Name(const SRC_T &src)                                        \
{                                                                              \
    using DST_T = Ty;                                                          \
    return (DST_T)src;                                                         \
}

_CONV_CONV_S_TO_S(long,   int64_t)
_CONV_CONV_S_TO_S(ulong,  uint64_t)
_CONV_CONV_S_TO_S(double, double)
_CONV_CONV_S_TO_S(int,    int32_t)
_CONV_CONV_S_TO_S(uint,   uint32_t)
_CONV_CONV_S_TO_S(float,  float)
_CONV_CONV_S_TO_S(short,  int16_t)
_CONV_CONV_S_TO_S(ushort, uint16_t)
_CONV_CONV_S_TO_S(char,   int8_t)
_CONV_CONV_S_TO_S(uchar,  uint8_t)
_CONV_CONV_S_TO_S(bool,   bool)

#undef _CONV_CONV_S_TO_S

//-----------------------------------------------------------------------------
// _CONV_CONV_CV_TO_CV: Complex vector to complex vector conversion
//-----------------------------------------------------------------------------
#define _CONV_CONV_CV_TO_CV(Name, Ty, Nelem)                                   \
template <typename SRC_T, size_t SRC_NELEM, VTYPE_KIND KIND,                   \
          typename = enable_if_cmplx_t<SRC_T, void>>                           \
vtype<ctype<Ty>, Nelem, VTYPE_KIND::DATA> __convert_ ## Name(const vtype<SRC_T, SRC_NELEM, KIND> &src) \
{                                                                              \
    using DST_T = Ty;                                                          \
                                                                               \
    constexpr size_t DST_NELEM = Nelem;                                        \
                                                                               \
    static_assert(SRC_NELEM == DST_NELEM,                                      \
                  "Illegal conversion cast: Element counts must be the same"); \
                                                                               \
    vtype<ctype<DST_T>, DST_NELEM, VTYPE_KIND::DATA> res;                      \
    for (size_t i = 0; i < DST_NELEM; i++)                                     \
    {                                                                          \
        res.s[i].r() = (DST_T)src.s[i].r();                                    \
        res.s[i].i() = (DST_T)src.s[i].i();                                    \
    }                                                                          \
                                                                               \
    return res;                                                                \
}

_CONV_CONV_CV_TO_CV(clong8, int64_t, 8)
_CONV_CONV_CV_TO_CV(clong4, int64_t, 4)
_CONV_CONV_CV_TO_CV(clong2, int64_t, 2)

_CONV_CONV_CV_TO_CV(cdouble8, double, 8)
_CONV_CONV_CV_TO_CV(cdouble4, double, 4)
_CONV_CONV_CV_TO_CV(cdouble2, double, 2)

_CONV_CONV_CV_TO_CV(cint8, int32_t, 8)
_CONV_CONV_CV_TO_CV(cint4, int32_t, 4)
_CONV_CONV_CV_TO_CV(cint2, int32_t, 2)

_CONV_CONV_CV_TO_CV(cfloat8, float, 8)
_CONV_CONV_CV_TO_CV(cfloat4, float, 4)
_CONV_CONV_CV_TO_CV(cfloat2, float, 2)

_CONV_CONV_CV_TO_CV(cshort16, int16_t, 16)
_CONV_CONV_CV_TO_CV(cshort8, int16_t, 8)
_CONV_CONV_CV_TO_CV(cshort4, int16_t, 4)
_CONV_CONV_CV_TO_CV(cshort2, int16_t, 2)

_CONV_CONV_CV_TO_CV(cchar32, int8_t, 32)
_CONV_CONV_CV_TO_CV(cchar16, int8_t, 16)
_CONV_CONV_CV_TO_CV(cchar8, int8_t, 8)
_CONV_CONV_CV_TO_CV(cchar4, int8_t, 4)
_CONV_CONV_CV_TO_CV(cchar2, int8_t, 2)

#undef _CONV_CONV_CV_TO_CV

//-----------------------------------------------------------------------------
// _CONV_CONV_CE_TO_CE: Complex element to complex element conversion
//-----------------------------------------------------------------------------
#define _CONV_CONV_CE_TO_CE(Name, Ty)                                          \
template <typename SRC_T>                                                      \
ctype<Ty> __convert_ ## Name(const ctype<SRC_T> &src)                          \
{                                                                              \
    using DST_T = Ty;                                                          \
                                                                               \
    ctype<DST_T> res;                                                          \
                                                                               \
    res.r() = (DST_T)src.r();                                                  \
    res.i() = (DST_T)src.i();                                                  \
                                                                               \
    return res;                                                                \
}

_CONV_CONV_CE_TO_CE(clong,   int64_t)
_CONV_CONV_CE_TO_CE(cdouble, double)
_CONV_CONV_CE_TO_CE(cint,    int32_t)
_CONV_CONV_CE_TO_CE(cfloat,  float)
_CONV_CONV_CE_TO_CE(cchar,   int8_t)
_CONV_CONV_CE_TO_CE(cshort,  int16_t)

#undef _CONV_CONV_CE_TO_CE

#endif /* VECTOR_CONV_H */
