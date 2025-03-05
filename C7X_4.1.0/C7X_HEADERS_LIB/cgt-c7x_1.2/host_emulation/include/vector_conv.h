/*****************************************************************************/
/*  VECTOR_CONV.H v#####                                                     */
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

#include <bitset>
#include <iostream>
#include <array>
#include <type_traits>
#include <functional>

#include <cstdint>
#include <cstring>
#include <climits>

//-----------------------------------------------------------------------------
// AS_<TYPE> REINTERPRETATION CONVERSIONS - THESE CONVERSIONS DO NOT CHANGE THE
// BIT REPRESENTATIONS OF ANY INPUT.  INSTEAD, THE CONVERSION REINTERPRETS THE
// SOURCE BITS INTO A NEW VECTOR WITH A DIFFERENT ELEMENT TYPE.  WE USE MEMCPY
// TO AVOID VIOLATING STRICT ALIASING RULES.
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// *** IMPORTANT NOTE IF YOU EVER NEED TO MODIFY THE ROUTINES BELOW ***
//-----------------------------------------------------------------------------
// The layout of complex elements in the underlying data array of the host
// emulation class reflects a real-first ordering of the complex components.
// This corresponds to the layout of complex values in MEMORY on the C7000.
// This is done so that a pointer can be returned via get_data_arr_ptr(), and
// the real and imaginary components will be seen in the expected order in
// MEMORY.
//
// Thus, whenever a complex element is reinterpreted as a vector (or scalar) in
// host emulation, the real and imaginary components must be SWAPPED in order
// to reflect an imaginary-first ordering of the components.  This layout
// corresponds to the layout of complex values in REGISTERS on the C7000.
//
// Accessing complex elements using the .r and .i accessors keeps these layout
// details hidden.  In the routines below, however, the real/imaginary swapping
// has to be explicitly handled.
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// _AS_CONV_V_TO_V: Vector to vector reinterpretation
//-----------------------------------------------------------------------------
#define _AS_CONV_V_TO_V(Name, Ty, Nelem)                                       \
template <typename SRC_T, size_t SRC_NELEM, size_t DEPTH>                      \
typename std::enable_if_t<std::is_arithmetic<SRC_T>::value,                    \
vtype<Ty, Nelem>> __as_ ## Name(const accessible<SRC_T, SRC_NELEM, DEPTH> &src)\
{                                                                              \
    using DST_T = Ty;                                                          \
                                                                               \
    constexpr size_t DST_SIZE  = sizeof(DST_T);                                \
    constexpr size_t DST_NELEM = Nelem;                                        \
    constexpr size_t SRC_SIZE  = sizeof(SRC_T);                                \
                                                                               \
    static_assert((SRC_SIZE * SRC_NELEM) == (DST_SIZE * DST_NELEM),            \
                  "Illegal reinterpret cast: Vector sizes must be the same");  \
                                                                               \
    vtype<DST_T, DST_NELEM> res;                                               \
                                                                               \
    /*----------------------------------------------------------------------*/ \
    /* Source lane type is larger than destination. Each lane in the source */ \
    /* vector will initialize more than destination lane.                   */ \
    /*----------------------------------------------------------------------*/ \
    if (SRC_SIZE > DST_SIZE)                                                   \
    {                                                                          \
        size_t dst_lanes_per_src = SRC_SIZE / DST_SIZE;                        \
        for (size_t src_idx = 0; src_idx < SRC_NELEM; src_idx++)               \
        {                                                                      \
            const char *curr_src =                                             \
                reinterpret_cast<const char *>(&(src.s[src_idx]));             \
                                                                               \
            for (size_t i = 0; i < dst_lanes_per_src; i++)                     \
            {                                                                  \
                DST_T res_lane;                                                \
                std::memcpy(&res_lane, (curr_src + i * DST_SIZE), DST_SIZE);   \
                res.s[src_idx * dst_lanes_per_src + i] = res_lane;             \
            }                                                                  \
        }                                                                      \
    }                                                                          \
                                                                               \
    /*----------------------------------------------------------------------*/ \
    /* Source lane type is the same or smaller than the destination, same   */ \
    /* as above, but each source element only initializes part of a single  */ \
    /* lane in the destination.                                             */ \
    /*----------------------------------------------------------------------*/ \
    else                                                                       \
    {                                                                          \
        size_t src_lanes_per_dst = DST_SIZE / SRC_SIZE;                        \
        for (size_t dst_idx = 0; dst_idx < DST_NELEM; dst_idx++)               \
        {                                                                      \
            DST_T res_lane;                                                    \
            for (size_t i = 0; i < src_lanes_per_dst; i++)                     \
            {                                                                  \
                size_t src_idx = i + dst_idx * src_lanes_per_dst;              \
                const char *curr_src =                                         \
                    reinterpret_cast<const char *>(&(src.s[src_idx]));         \
                                                                               \
                char *lane_ptr = reinterpret_cast<char *>(&res_lane);          \
                                                                               \
                std::memcpy((lane_ptr + i * SRC_SIZE), curr_src, SRC_SIZE);    \
            }                                                                  \
            res.s[dst_idx] = res_lane;                                         \
        }                                                                      \
    }                                                                          \
    return res;                                                                \
}

_AS_CONV_V_TO_V(long16, int64_t, 16)
_AS_CONV_V_TO_V(long8,  int64_t, 8)
_AS_CONV_V_TO_V(long4,  int64_t, 4)
_AS_CONV_V_TO_V(long2,  int64_t, 2)

_AS_CONV_V_TO_V(ulong16, uint64_t, 16)
_AS_CONV_V_TO_V(ulong8,  uint64_t, 8)
_AS_CONV_V_TO_V(ulong4,  uint64_t, 4)
_AS_CONV_V_TO_V(ulong2,  uint64_t, 2)

_AS_CONV_V_TO_V(double16, double, 16)
_AS_CONV_V_TO_V(double8,  double, 8)
_AS_CONV_V_TO_V(double4,  double, 4)
_AS_CONV_V_TO_V(double2,  double, 2)

_AS_CONV_V_TO_V(int16, int32_t, 16)
_AS_CONV_V_TO_V(int8,  int32_t, 8)
_AS_CONV_V_TO_V(int4,  int32_t, 4)
_AS_CONV_V_TO_V(int2,  int32_t, 2)

_AS_CONV_V_TO_V(uint16, uint32_t, 16)
_AS_CONV_V_TO_V(uint8,  uint32_t, 8)
_AS_CONV_V_TO_V(uint4,  uint32_t, 4)
_AS_CONV_V_TO_V(uint2,  uint32_t, 2)

_AS_CONV_V_TO_V(float16, float, 16)
_AS_CONV_V_TO_V(float8,  float, 8)
_AS_CONV_V_TO_V(float4,  float, 4)
_AS_CONV_V_TO_V(float2,  float, 2)

_AS_CONV_V_TO_V(short32, int16_t, 32)
_AS_CONV_V_TO_V(short16, int16_t, 16)
_AS_CONV_V_TO_V(short8,  int16_t, 8)
_AS_CONV_V_TO_V(short4,  int16_t, 4)
_AS_CONV_V_TO_V(short2,  int16_t, 2)

_AS_CONV_V_TO_V(ushort32, uint16_t, 32)
_AS_CONV_V_TO_V(ushort16, uint16_t, 16)
_AS_CONV_V_TO_V(ushort8,  uint16_t, 8)
_AS_CONV_V_TO_V(ushort4,  uint16_t, 4)
_AS_CONV_V_TO_V(ushort2,  uint16_t, 2)

_AS_CONV_V_TO_V(char64, int8_t, 64)
_AS_CONV_V_TO_V(char32, int8_t, 32)
_AS_CONV_V_TO_V(char16, int8_t, 16)
_AS_CONV_V_TO_V(char8,  int8_t, 8)
_AS_CONV_V_TO_V(char4,  int8_t, 4)
_AS_CONV_V_TO_V(char2,  int8_t, 2)

_AS_CONV_V_TO_V(uchar64, uint8_t, 64)
_AS_CONV_V_TO_V(uchar32, uint8_t, 32)
_AS_CONV_V_TO_V(uchar16, uint8_t, 16)
_AS_CONV_V_TO_V(uchar8,  uint8_t, 8)
_AS_CONV_V_TO_V(uchar4,  uint8_t, 4)
_AS_CONV_V_TO_V(uchar2,  uint8_t, 2)

#undef _AS_CONV_V_TO_V

//-----------------------------------------------------------------------------
// _AS_CONV_V_TO_CV: Vector to complex vector reinterpretation
//-----------------------------------------------------------------------------
#define _AS_CONV_V_TO_CV(Name, Ty, Nelem)                                      \
template <typename SRC_T, size_t SRC_NELEM, size_t DEPTH>                      \
typename std::enable_if_t<std::is_arithmetic<SRC_T>::value,                    \
vtype<ctype<Ty>, Nelem>> __as_ ## Name(const accessible<SRC_T, SRC_NELEM, DEPTH> &src)\
{                                                                              \
    using DST_T = Ty;                                                          \
                                                                               \
    constexpr size_t DST_SIZE  = sizeof(DST_T);                                \
    constexpr size_t DST_NELEM = Nelem;                                        \
    constexpr size_t SRC_SIZE  = sizeof(SRC_T);                                \
                                                                               \
    static_assert((SRC_SIZE * SRC_NELEM) == (DST_SIZE * DST_NELEM * 2),        \
                  "Illegal reinterpret cast: Vector sizes must be the same");  \
                                                                               \
    vtype<ctype<DST_T>, DST_NELEM> res;                                        \
                                                                               \
    /*----------------------------------------------------------------------*/ \
    /* Source lane type is larger than a destination complex vector lane.   */ \
    /* Each lane in the source vector will initialize more than one complex */ \
    /* vector lane.                                                         */ \
    /*----------------------------------------------------------------------*/ \
    if (SRC_SIZE >= DST_SIZE * 2)                                              \
    {                                                                          \
        size_t dst_lanes_per_src = SRC_SIZE / (DST_SIZE * 2);                  \
        for (size_t src_idx = 0; src_idx < SRC_NELEM; src_idx++)               \
        {                                                                      \
            const char *curr_src =                                             \
                reinterpret_cast<const char *>(&(src.s[src_idx]));             \
                                                                               \
            for (size_t i = 0; i < dst_lanes_per_src; i++)                     \
            {                                                                  \
                ctype<DST_T> res_lane;                                         \
                std::memcpy(&res_lane.i,                                       \
                        (curr_src + 2*i * DST_SIZE), DST_SIZE);                \
                std::memcpy(&res_lane.r,                                       \
                        (curr_src + (2*i+1) * DST_SIZE), DST_SIZE);            \
                res.s[src_idx * dst_lanes_per_src + i] = res_lane;             \
            }                                                                  \
        }                                                                      \
    }                                                                          \
                                                                               \
    /*----------------------------------------------------------------------*/ \
    /* Source lane type is the same or smaller than the destination. Each   */ \
    /* source element only initializes part of a single complex vector lane */ \
    /* in the destination.                                                  */ \
    /*----------------------------------------------------------------------*/ \
    else                                                                       \
    {                                                                          \
        size_t src_lanes_per_dst = (DST_SIZE * 2) / SRC_SIZE;                  \
        for (size_t dst_idx = 0; dst_idx < DST_NELEM; dst_idx++)               \
        {                                                                      \
            ctype<DST_T> res_lane;                                             \
            char *lp_i = reinterpret_cast<char *>(&res_lane.i);                \
            char *lp_r = reinterpret_cast<char *>(&res_lane.r);                \
                                                                               \
            /*--------------------------------------------------------------*/ \
            /* Copy into the imaginary part.                                */ \
            /*--------------------------------------------------------------*/ \
            for (size_t i = 0; i < src_lanes_per_dst/2; i++)                   \
            {                                                                  \
                size_t src_idx = i + dst_idx * src_lanes_per_dst;              \
                const char *curr_src =                                         \
                    reinterpret_cast<const char *>(&(src.s[src_idx]));         \
                                                                               \
                std::memcpy((lp_i + i * SRC_SIZE), curr_src, SRC_SIZE);        \
            }                                                                  \
                                                                               \
            /*--------------------------------------------------------------*/ \
            /* Copy into the real part.                                     */ \
            /*--------------------------------------------------------------*/ \
            for (size_t i = 0; i < src_lanes_per_dst/2; i++)                   \
            {                                                                  \
                size_t src_idx = i + src_lanes_per_dst/2 +                     \
                                dst_idx * src_lanes_per_dst;                   \
                const char *curr_src =                                         \
                    reinterpret_cast<const char *>(&(src.s[src_idx]));         \
                                                                               \
                std::memcpy((lp_r + i * SRC_SIZE), curr_src, SRC_SIZE);        \
            }                                                                  \
            res.s[dst_idx] = res_lane;                                         \
        }                                                                      \
    }                                                                          \
    return res;                                                                \
}

_AS_CONV_V_TO_CV(clong8, int64_t, 8)
_AS_CONV_V_TO_CV(clong4, int64_t, 4)
_AS_CONV_V_TO_CV(clong2, int64_t, 2)

_AS_CONV_V_TO_CV(cdouble8, double, 8)
_AS_CONV_V_TO_CV(cdouble4, double, 4)
_AS_CONV_V_TO_CV(cdouble2, double, 2)

_AS_CONV_V_TO_CV(cint8, int32_t, 8)
_AS_CONV_V_TO_CV(cint4, int32_t, 4)
_AS_CONV_V_TO_CV(cint2, int32_t, 2)

_AS_CONV_V_TO_CV(cfloat8, float, 8)
_AS_CONV_V_TO_CV(cfloat4, float, 4)
_AS_CONV_V_TO_CV(cfloat2, float, 2)

_AS_CONV_V_TO_CV(cshort16, int16_t, 16)
_AS_CONV_V_TO_CV(cshort8, int16_t, 8)
_AS_CONV_V_TO_CV(cshort4, int16_t, 4)
_AS_CONV_V_TO_CV(cshort2, int16_t, 2)

_AS_CONV_V_TO_CV(cchar32, int8_t, 32)
_AS_CONV_V_TO_CV(cchar16, int8_t, 16)
_AS_CONV_V_TO_CV(cchar8, int8_t, 8)
_AS_CONV_V_TO_CV(cchar4, int8_t, 4)
_AS_CONV_V_TO_CV(cchar2, int8_t, 2)

#undef _AS_CONV_V_TO_CV

//-----------------------------------------------------------------------------
// _AS_CONV_V_TO_S: Vector to scalar reinterpretation
//-----------------------------------------------------------------------------
#define _AS_CONV_V_TO_S(Name, Ty)                                              \
template <typename SRC_T, size_t SRC_NELEM, size_t DEPTH>                      \
typename std::enable_if_t<std::is_arithmetic<SRC_T>::value,                    \
Ty> __as_ ## Name(const accessible<SRC_T, SRC_NELEM, DEPTH> &src)              \
{                                                                              \
    using DST_T = Ty;                                                          \
                                                                               \
    constexpr size_t DST_SIZE = sizeof(DST_T);                                 \
    constexpr size_t SRC_SIZE = sizeof(SRC_T);                                 \
                                                                               \
    static_assert((SRC_SIZE * SRC_NELEM) == DST_SIZE,                          \
                  "Illegal reinterpret cast: Data sizes must be the same");    \
                                                                               \
    DST_T res = 0;                                                             \
                                                                               \
    /*----------------------------------------------------------------------*/ \
    /* We can do a straight-copy of the data from src to dst.               */ \
    /*----------------------------------------------------------------------*/ \
    vtype<SRC_T, SRC_NELEM> tmp(src);                                          \
    std::memcpy(&res, tmp.get_data_arr_ptr(), DST_SIZE);                       \
                                                                               \
    return res;                                                                \
}

_AS_CONV_V_TO_S(long,   int64_t)
_AS_CONV_V_TO_S(ulong,  uint64_t)
_AS_CONV_V_TO_S(double, double)
_AS_CONV_V_TO_S(int,    int32_t)
_AS_CONV_V_TO_S(uint,   uint32_t)
_AS_CONV_V_TO_S(float,  float)
_AS_CONV_V_TO_S(short,  int16_t)
_AS_CONV_V_TO_S(ushort, uint16_t)

#undef _AS_CONV_V_TO_S

//-----------------------------------------------------------------------------
// _AS_CONV_V_TO_CE: Vector to complex element reinterpretation
//-----------------------------------------------------------------------------
#define _AS_CONV_V_TO_CE(Name, Ty)                                             \
template <typename SRC_T, size_t SRC_NELEM, size_t DEPTH>                      \
typename std::enable_if_t<std::is_arithmetic<SRC_T>::value,                    \
ctype<Ty>> __as_ ## Name(const accessible<SRC_T, SRC_NELEM, DEPTH> &src)       \
{                                                                              \
    using DST_T = Ty;                                                          \
                                                                               \
    constexpr size_t DST_SIZE = sizeof(DST_T);                                 \
    constexpr size_t SRC_SIZE = sizeof(SRC_T);                                 \
                                                                               \
    static_assert((SRC_SIZE * SRC_NELEM) == (DST_SIZE * 2),                    \
                  "Illegal reinterpret cast: Data sizes must be the same");    \
                                                                               \
    ctype<DST_T> res;                                                          \
                                                                               \
    /*----------------------------------------------------------------------*/ \
    /* We can do a copy of the source data from src into the real and imag  */ \
    /* parts of the destination complex element.                            */ \
    /*----------------------------------------------------------------------*/ \
    vtype<SRC_T, SRC_NELEM> tmp(src);                                          \
                                                                               \
    const char *curr_src =                                                     \
        reinterpret_cast<const char *>(tmp.get_data_arr_ptr());                \
                                                                               \
    std::memcpy(&res.r, curr_src + DST_SIZE, DST_SIZE);                        \
    std::memcpy(&res.i, curr_src,            DST_SIZE);                        \
                                                                               \
    return res;                                                                \
}

_AS_CONV_V_TO_CE(clong,   int64_t)
_AS_CONV_V_TO_CE(cdouble, double)
_AS_CONV_V_TO_CE(cint,    int32_t)
_AS_CONV_V_TO_CE(cfloat,  float)
_AS_CONV_V_TO_CE(cshort,  int16_t)
_AS_CONV_V_TO_CE(cchar,   int8_t)

#undef _AS_CONV_V_TO_CE

//-----------------------------------------------------------------------------
// _AS_CONV_CV_TO_V: Complex vector to vector reinterpretation
//-----------------------------------------------------------------------------
#define _AS_CONV_CV_TO_V(Name, Ty, Nelem)                                      \
template <typename SRC_T, size_t SRC_NELEM, size_t DEPTH,                      \
           typename = enable_if_cmplx_t<SRC_T, void>>                          \
vtype<Ty, Nelem> __as_ ## Name(const accessible<SRC_T, SRC_NELEM, DEPTH> &src) \
{                                                                              \
    using DST_T = Ty;                                                          \
                                                                               \
    constexpr size_t DST_SIZE  = sizeof(DST_T);                                \
    constexpr size_t DST_NELEM = Nelem;                                        \
    constexpr size_t SRC_SIZE  = sizeof(typename SRC_T::ELEM_TYPE);            \
                                                                               \
    static_assert((SRC_SIZE * SRC_NELEM * 2) == (DST_SIZE * DST_NELEM),        \
                  "Illegal reinterpret cast: Vector sizes must be the same");  \
                                                                               \
    vtype<DST_T, DST_NELEM> res;                                               \
                                                                               \
    /*----------------------------------------------------------------------*/ \
    /* Source lane type is larger than destination. Each lane in the source */ \
    /* vector will initialize more than 1 DST_T.                            */ \
    /*----------------------------------------------------------------------*/ \
    if (SRC_SIZE >= DST_SIZE)                                                  \
    {                                                                          \
        size_t dst_lanes_per_src = (SRC_SIZE * 2) / DST_SIZE;                  \
        for (size_t src_idx = 0; src_idx < SRC_NELEM; src_idx++)               \
        {                                                                      \
            const char *curr_src_imag =                                        \
                reinterpret_cast<const char *>(&(src.s[src_idx].i));           \
            const char *curr_src_real =                                        \
                reinterpret_cast<const char *>(&(src.s[src_idx].r));           \
                                                                               \
            /*--------------------------------------------------------------*/ \
            /* Copy from the imaginary part.                                */ \
            /*--------------------------------------------------------------*/ \
            for (size_t i = 0; i < dst_lanes_per_src/2; i++)                   \
            {                                                                  \
                DST_T res_lane;                                                \
                std::memcpy(&res_lane,                                         \
                            (curr_src_imag + i * DST_SIZE), DST_SIZE);         \
                res.s[src_idx * dst_lanes_per_src + i] = res_lane;             \
            }                                                                  \
                                                                               \
            /*--------------------------------------------------------------*/ \
            /* Copy from the real part.                                     */ \
            /*--------------------------------------------------------------*/ \
            for (size_t i = 0; i < dst_lanes_per_src/2; i++)                   \
            {                                                                  \
                DST_T res_lane;                                                \
                std::memcpy(&res_lane,                                         \
                            (curr_src_real + (i) * DST_SIZE), DST_SIZE);       \
                res.s[src_idx * dst_lanes_per_src + i + dst_lanes_per_src/2]   \
                  = res_lane;                                                  \
            }                                                                  \
        }                                                                      \
    }                                                                          \
                                                                               \
    /*----------------------------------------------------------------------*/ \
    /* Source lane type is smaller than the destination, same               */ \
    /* as above, but each source element only initializes part of a single  */ \
    /* lane in the destination.                                             */ \
    /*----------------------------------------------------------------------*/ \
    else                                                                       \
    {                                                                          \
        size_t src_lanes_per_dst = DST_SIZE / (SRC_SIZE * 2);                  \
        for (size_t dst_idx = 0; dst_idx < DST_NELEM; dst_idx++)               \
        {                                                                      \
            DST_T res_lane;                                                    \
            for (size_t i = 0; i < src_lanes_per_dst; i++)                     \
            {                                                                  \
                size_t src_idx = i + dst_idx * src_lanes_per_dst;              \
                const char *curr_src_imag =                                    \
                    reinterpret_cast<const char *>(&(src.s[src_idx].i));       \
                 const char *curr_src_real =                                   \
                    reinterpret_cast<const char *>(&(src.s[src_idx].r));       \
                                                                               \
                char *lane_ptr =                                               \
                    reinterpret_cast<char *>(&res_lane);                       \
                                                                               \
                std::memcpy((lane_ptr + 2*i * SRC_SIZE),                       \
                            curr_src_imag, SRC_SIZE);                          \
                std::memcpy((lane_ptr + (2*i + 1) * SRC_SIZE),                 \
                            curr_src_real, SRC_SIZE);                          \
            }                                                                  \
            res.s[dst_idx] = res_lane;                                         \
        }                                                                      \
    }                                                                          \
    return res;                                                                \
}

_AS_CONV_CV_TO_V(long16, int64_t, 16)
_AS_CONV_CV_TO_V(long8, int64_t, 8)
_AS_CONV_CV_TO_V(long4, int64_t, 4)
_AS_CONV_CV_TO_V(long2, int64_t, 2)

_AS_CONV_CV_TO_V(ulong16, uint64_t, 16)
_AS_CONV_CV_TO_V(ulong8, uint64_t, 8)
_AS_CONV_CV_TO_V(ulong4, uint64_t, 4)
_AS_CONV_CV_TO_V(ulong2, uint64_t, 2)

_AS_CONV_CV_TO_V(double16, double, 16)
_AS_CONV_CV_TO_V(double8, double, 8)
_AS_CONV_CV_TO_V(double4, double, 4)
_AS_CONV_CV_TO_V(double2, double, 2)

_AS_CONV_CV_TO_V(int16, int32_t, 16)
_AS_CONV_CV_TO_V(int8,  int32_t, 8)
_AS_CONV_CV_TO_V(int4,  int32_t, 4)
_AS_CONV_CV_TO_V(int2,  int32_t, 2)

_AS_CONV_CV_TO_V(uint16, uint32_t, 16)
_AS_CONV_CV_TO_V(uint8,  uint32_t, 8)
_AS_CONV_CV_TO_V(uint4,  uint32_t, 4)
_AS_CONV_CV_TO_V(uint2,  uint32_t, 2)

_AS_CONV_CV_TO_V(float16, float, 16)
_AS_CONV_CV_TO_V(float8,  float, 8)
_AS_CONV_CV_TO_V(float4,  float, 4)
_AS_CONV_CV_TO_V(float2,  float, 2)

_AS_CONV_CV_TO_V(short32, int16_t, 32)
_AS_CONV_CV_TO_V(short16, int16_t, 16)
_AS_CONV_CV_TO_V(short8,  int16_t, 8)
_AS_CONV_CV_TO_V(short4,  int16_t, 4)
_AS_CONV_CV_TO_V(short2,  int16_t, 2)

_AS_CONV_CV_TO_V(ushort32, uint16_t, 32)
_AS_CONV_CV_TO_V(ushort16, uint16_t, 16)
_AS_CONV_CV_TO_V(ushort8,  uint16_t, 8)
_AS_CONV_CV_TO_V(ushort4,  uint16_t, 4)
_AS_CONV_CV_TO_V(ushort2,  uint16_t, 2)

_AS_CONV_CV_TO_V(char64, int8_t, 64)
_AS_CONV_CV_TO_V(char32, int8_t, 32)
_AS_CONV_CV_TO_V(char16, int8_t, 16)
_AS_CONV_CV_TO_V(char8,  int8_t, 8)
_AS_CONV_CV_TO_V(char4,  int8_t, 4)
_AS_CONV_CV_TO_V(char2,  int8_t, 2)

_AS_CONV_CV_TO_V(uchar64, uint8_t, 64)
_AS_CONV_CV_TO_V(uchar32, uint8_t, 32)
_AS_CONV_CV_TO_V(uchar16, uint8_t, 16)
_AS_CONV_CV_TO_V(uchar8,  uint8_t, 8)
_AS_CONV_CV_TO_V(uchar4,  uint8_t, 4)
_AS_CONV_CV_TO_V(uchar2,  uint8_t, 2)

#undef _AS_CONV_CV_TO_V

//-----------------------------------------------------------------------------
// _AS_CONV_CV_TO_CV: Complex vector to complex vector reinterpretation
//-----------------------------------------------------------------------------
#define _AS_CONV_CV_TO_CV(Name, Ty, Nelem)                                     \
template <typename SRC_T, size_t SRC_NELEM, size_t DEPTH,                      \
           typename = enable_if_cmplx_t<SRC_T, void>>                          \
vtype<ctype<Ty>, Nelem> __as_ ## Name(const accessible<SRC_T, SRC_NELEM, DEPTH> &src) \
{                                                                              \
    using DST_T = Ty;                                                          \
                                                                               \
    constexpr size_t DST_SIZE  = sizeof(DST_T);                                \
    constexpr size_t DST_NELEM = Nelem;                                        \
    constexpr size_t SRC_SIZE  = sizeof(typename SRC_T::ELEM_TYPE);            \
                                                                               \
    static_assert((SRC_SIZE * SRC_NELEM * 2) == (DST_SIZE * DST_NELEM * 2),    \
                  "Illegal reinterpret cast: Vector sizes must be the same");  \
                                                                               \
    vtype<ctype<DST_T>, DST_NELEM> res;                                        \
                                                                               \
    /*----------------------------------------------------------------------*/ \
    /* Source lane type is equal to destination. Each lane in the source    */ \
    /* vector will initialize one DST_T.                                    */ \
    /*----------------------------------------------------------------------*/ \
    if (SRC_SIZE == DST_SIZE)                                                  \
    {                                                                          \
        for (size_t src_idx = 0; src_idx < SRC_NELEM; src_idx++)               \
        {                                                                      \
            ctype<DST_T> res_lane;                                             \
            std::memcpy(&res_lane.i, &(src.s[src_idx].i), DST_SIZE);           \
            std::memcpy(&res_lane.r, &(src.s[src_idx].r), DST_SIZE);           \
            res.s[src_idx] = res_lane;                                         \
        }                                                                      \
    }                                                                          \
                                                                               \
    /*----------------------------------------------------------------------*/ \
    /* Source lane type is larger than destination. Each lane in the source */ \
    /* vector will initialize more than 1 DST_T.                            */ \
    /*----------------------------------------------------------------------*/ \
    else if (SRC_SIZE > DST_SIZE)                                              \
    {                                                                          \
        size_t dst_lanes_per_src = SRC_SIZE / DST_SIZE;                        \
        for (size_t src_idx = 0; src_idx < SRC_NELEM; src_idx++)               \
        {                                                                      \
            const char *curr_src_i =                                           \
                reinterpret_cast<const char *>(&(src.s[src_idx].i));           \
            const char *curr_src_r =                                           \
                reinterpret_cast<const char *>(&(src.s[src_idx].r));           \
                                                                               \
            /*--------------------------------------------------------------*/ \
            /* Copy from the imaginary part.                                */ \
            /*--------------------------------------------------------------*/ \
            for (size_t i = 0; i < dst_lanes_per_src/2; i++)                   \
            {                                                                  \
                ctype<DST_T> res_lane;                                         \
                std::memcpy(&res_lane.i,                                       \
                            (curr_src_i + 2*i * DST_SIZE), DST_SIZE);          \
                std::memcpy(&res_lane.r,                                       \
                            (curr_src_i + (2*i+1) * DST_SIZE), DST_SIZE);      \
                res.s[src_idx * dst_lanes_per_src + i] = res_lane;             \
            }                                                                  \
                                                                               \
            /*--------------------------------------------------------------*/ \
            /* Copy from the real part.                                     */ \
            /*--------------------------------------------------------------*/ \
            for (size_t i = 0; i < dst_lanes_per_src/2; i++)                   \
            {                                                                  \
                ctype<DST_T> res_lane;                                         \
                std::memcpy(&res_lane.i,                                       \
                            (curr_src_r + 2*i * DST_SIZE), DST_SIZE);          \
                std::memcpy(&res_lane.r,                                       \
                            (curr_src_r + (2*i+1) * DST_SIZE), DST_SIZE);      \
                res.s[src_idx * dst_lanes_per_src + i + dst_lanes_per_src/2]   \
                   = res_lane;                                                 \
            }                                                                  \
        }                                                                      \
    }                                                                          \
                                                                               \
    /*----------------------------------------------------------------------*/ \
    /* Source lane type is smaller than the destination, same               */ \
    /* as above, but each source element only initializes part of a single  */ \
    /* lane in the destination.                                             */ \
    /*----------------------------------------------------------------------*/ \
    else                                                                       \
    {                                                                          \
        size_t src_lanes_per_dst = DST_SIZE / SRC_SIZE;                        \
        for (size_t dst_idx = 0; dst_idx < DST_NELEM; dst_idx++)               \
        {                                                                      \
            ctype<DST_T> res_lane;                                             \
            char *lp_i = reinterpret_cast<char *>(&res_lane.i);                \
            char *lp_r = reinterpret_cast<char *>(&res_lane.r);                \
                                                                               \
            /*--------------------------------------------------------------*/ \
            /* Copy into the imaginary part.                                */ \
            /*--------------------------------------------------------------*/ \
            for (size_t i = 0; i < src_lanes_per_dst/2; i++)                   \
            {                                                                  \
                size_t src_idx = i + dst_idx * src_lanes_per_dst;              \
                const char *curr_src_i =                                       \
                    reinterpret_cast<const char *>(&(src.s[src_idx].i));       \
                const char *curr_src_r =                                       \
                    reinterpret_cast<const char *>(&(src.s[src_idx].r));       \
                                                                               \
                std::memcpy((lp_i + 2*i * SRC_SIZE), curr_src_i, SRC_SIZE);    \
                std::memcpy((lp_i + (2*i+1) * SRC_SIZE), curr_src_r, SRC_SIZE);\
            }                                                                  \
                                                                               \
            /*--------------------------------------------------------------*/ \
            /* Copy into the real part.                                     */ \
            /*--------------------------------------------------------------*/ \
            for (size_t i = 0; i < src_lanes_per_dst/2; i++)                   \
            {                                                                  \
                size_t src_idx = i + src_lanes_per_dst/2 +                     \
                                 dst_idx * src_lanes_per_dst;                  \
                const char *curr_src_i =                                       \
                    reinterpret_cast<const char *>(&(src.s[src_idx].i));       \
                const char *curr_src_r =                                       \
                    reinterpret_cast<const char *>(&(src.s[src_idx].r));       \
                                                                               \
                std::memcpy((lp_r + 2*i * SRC_SIZE), curr_src_i, SRC_SIZE);    \
                std::memcpy((lp_r + (2*i+1) * SRC_SIZE), curr_src_r, SRC_SIZE);\
            }                                                                  \
            res.s[dst_idx] = res_lane;                                         \
        }                                                                      \
    }                                                                          \
    return res;                                                                \
}

_AS_CONV_CV_TO_CV(clong8, int64_t, 8)
_AS_CONV_CV_TO_CV(clong4, int64_t, 4)
_AS_CONV_CV_TO_CV(clong2, int64_t, 2)

_AS_CONV_CV_TO_CV(cdouble8, double, 8)
_AS_CONV_CV_TO_CV(cdouble4, double, 4)
_AS_CONV_CV_TO_CV(cdouble2, double, 2)

_AS_CONV_CV_TO_CV(cint8, int32_t, 8)
_AS_CONV_CV_TO_CV(cint4, int32_t, 4)
_AS_CONV_CV_TO_CV(cint2, int32_t, 2)

_AS_CONV_CV_TO_CV(cfloat8, float, 8)
_AS_CONV_CV_TO_CV(cfloat4, float, 4)
_AS_CONV_CV_TO_CV(cfloat2, float, 2)

_AS_CONV_CV_TO_CV(cshort16, int16_t, 16)
_AS_CONV_CV_TO_CV(cshort8, int16_t, 8)
_AS_CONV_CV_TO_CV(cshort4, int16_t, 4)
_AS_CONV_CV_TO_CV(cshort2, int16_t, 2)

_AS_CONV_CV_TO_CV(cchar32, int8_t, 32)
_AS_CONV_CV_TO_CV(cchar16, int8_t, 16)
_AS_CONV_CV_TO_CV(cchar8, int8_t, 8)
_AS_CONV_CV_TO_CV(cchar4, int8_t, 4)
_AS_CONV_CV_TO_CV(cchar2, int8_t, 2)

#undef _AS_CONV_CV_TO_CV

//-----------------------------------------------------------------------------
// _AS_CONV_CV_TO_S: Vector to scalar reinterpretation
//-----------------------------------------------------------------------------
#define _AS_CONV_CV_TO_S(Name, Ty)                                             \
template <typename SRC_T, size_t SRC_NELEM, size_t DEPTH,                      \
           typename = enable_if_cmplx_t<SRC_T, void>>                          \
Ty __as_ ## Name(const accessible<SRC_T, SRC_NELEM, DEPTH> &src)               \
{                                                                              \
    using DST_T = Ty;                                                          \
                                                                               \
    constexpr size_t DST_SIZE = sizeof(DST_T);                                 \
    constexpr size_t SRC_SIZE = sizeof(typename SRC_T::ELEM_TYPE);             \
                                                                               \
    static_assert((SRC_SIZE * SRC_NELEM * 2) == DST_SIZE,                      \
                  "Illegal reinterpret cast: Data sizes must be the same");    \
                                                                               \
    DST_T res = 0;                                                             \
                                                                               \
    /*----------------------------------------------------------------------*/ \
    /* For every complex lane in the source vector, copy a data chunk into  */ \
    /* the destination scalar.                                              */ \
    /*----------------------------------------------------------------------*/ \
    char *lane_ptr = reinterpret_cast<char *>(&res);                           \
                                                                               \
    size_t src_lanes_per_dst = DST_SIZE / (SRC_SIZE * 2);                      \
    for (size_t i = 0; i < src_lanes_per_dst; i++)                             \
    {                                                                          \
        const char *curr_src_i =                                               \
            reinterpret_cast<const char *>(&(src.s[i].i));                     \
                                                                               \
        const char *curr_src_r =                                               \
            reinterpret_cast<const char *>(&(src.s[i].r));                     \
                                                                               \
        std::memcpy((lane_ptr + 2*i * SRC_SIZE), curr_src_i, SRC_SIZE);        \
        std::memcpy((lane_ptr + (2*i+1) * SRC_SIZE), curr_src_r, SRC_SIZE);    \
    }                                                                          \
                                                                               \
    return res;                                                                \
}

_AS_CONV_CV_TO_S(long,   int64_t)
_AS_CONV_CV_TO_S(ulong,  uint64_t)
_AS_CONV_CV_TO_S(double, double)
_AS_CONV_CV_TO_S(int,    int32_t)
_AS_CONV_CV_TO_S(uint,   uint32_t)
_AS_CONV_CV_TO_S(float,  float)
_AS_CONV_CV_TO_S(short,  int16_t)
_AS_CONV_CV_TO_S(ushort, uint16_t)

#undef _AS_CONV_CV_TO_S

//-----------------------------------------------------------------------------
// _AS_CONV_CV_TO_CE: Vector to scalar reinterpretation
//-----------------------------------------------------------------------------
#define _AS_CONV_CV_TO_CE(Name, Ty)                                            \
template <typename SRC_T, size_t SRC_NELEM, size_t DEPTH,                      \
           typename = enable_if_cmplx_t<SRC_T, void>>                          \
ctype<Ty> __as_ ## Name(const accessible<SRC_T, SRC_NELEM, DEPTH> &src)        \
{                                                                              \
    using DST_T = Ty;                                                          \
                                                                               \
    constexpr size_t DST_SIZE = sizeof(DST_T);                                 \
    constexpr size_t SRC_SIZE = sizeof(typename SRC_T::ELEM_TYPE);             \
                                                                               \
    static_assert((SRC_SIZE * SRC_NELEM * 2) == DST_SIZE * 2,                  \
                  "Illegal reinterpret cast: Data sizes must be the same");    \
                                                                               \
    ctype<DST_T> res;                                                          \
                                                                               \
    /*----------------------------------------------------------------------*/ \
    /* For every complex lane in the source vector, copy into a data chunk  */ \
    /* into the destination complex element.                                */ \
    /*----------------------------------------------------------------------*/ \
    size_t src_lanes_per_dst = DST_SIZE / SRC_SIZE;                            \
    char *lp_i = reinterpret_cast<char *>(&res.i);                             \
    char *lp_r = reinterpret_cast<char *>(&res.r);                             \
                                                                               \
    /*----------------------------------------------------------------------*/ \
    /* Copy into the imaginary part.                                        */ \
    /*----------------------------------------------------------------------*/ \
    for (size_t i = 0; i < src_lanes_per_dst/2; i++)                           \
    {                                                                          \
        size_t src_idx = i;                                                    \
        const char *curr_src_i =                                               \
            reinterpret_cast<const char *>(&(src.s[src_idx].i));               \
        const char *curr_src_r =                                               \
            reinterpret_cast<const char *>(&(src.s[src_idx].r));               \
                                                                               \
        std::memcpy((lp_i + 2*i * SRC_SIZE), curr_src_i, SRC_SIZE);            \
        std::memcpy((lp_i + (2*i+1) * SRC_SIZE), curr_src_r, SRC_SIZE);        \
    }                                                                          \
                                                                               \
    /*----------------------------------------------------------------------*/ \
    /* Copy into the real part.                                             */ \
    /*----------------------------------------------------------------------*/ \
    for (size_t i = 0; i < src_lanes_per_dst/2; i++)                           \
    {                                                                          \
        size_t src_idx = i + src_lanes_per_dst/2;                              \
        const char *curr_src_i =                                               \
            reinterpret_cast<const char *>(&(src.s[src_idx].i));               \
        const char *curr_src_r =                                               \
            reinterpret_cast<const char *>(&(src.s[src_idx].r));               \
                                                                               \
        std::memcpy((lp_r + 2*i * SRC_SIZE), curr_src_i, SRC_SIZE);            \
        std::memcpy((lp_r + (2*i+1) * SRC_SIZE), curr_src_r, SRC_SIZE);        \
    }                                                                          \
                                                                               \
    return res;                                                                \
}

_AS_CONV_CV_TO_CE(clong,   int64_t)
_AS_CONV_CV_TO_CE(cdouble, double)
_AS_CONV_CV_TO_CE(cint,    int32_t)
_AS_CONV_CV_TO_CE(cfloat,  float)
_AS_CONV_CV_TO_CE(cshort,  int16_t)

#undef _AS_CONV_CV_TO_CE

//-----------------------------------------------------------------------------
// _AS_CONV_CE_TO_S: Complex element to scalar reinterpretation
//-----------------------------------------------------------------------------
#define _AS_CONV_CE_TO_S(Name, Ty)                                             \
template <typename SRC_T>                                                      \
Ty __as_ ## Name(const ctype<SRC_T> &src)                                      \
{                                                                              \
    using DST_T = Ty;                                                          \
                                                                               \
    constexpr size_t DST_SIZE = sizeof(DST_T);                                 \
    constexpr size_t SRC_SIZE = sizeof(SRC_T);                                 \
                                                                               \
    static_assert((SRC_SIZE * 2) == (DST_SIZE),                                \
                  "Illegal reinterpret cast: Data sizes must be the same");    \
                                                                               \
    DST_T res = 0;                                                             \
                                                                               \
    /*----------------------------------------------------------------------*/ \
    /* We can do a copy of the real and imag parts of the source data into  */ \
    /* the destination scalar.                                              */ \
    /*----------------------------------------------------------------------*/ \
    char *res_ptr = (char*)(&res);                                             \
                                                                               \
    /*----------------------------------------------------------------------*/ \
    /* Copy from the real part.                                             */ \
    /*----------------------------------------------------------------------*/ \
    std::memcpy(res_ptr + SRC_SIZE, &src.r, SRC_SIZE);                         \
                                                                               \
    /*----------------------------------------------------------------------*/ \
    /* Copy from the imaginary part.                                        */ \
    /*----------------------------------------------------------------------*/ \
    std::memcpy(res_ptr, &src.i, SRC_SIZE);                                    \
                                                                               \
    return res;                                                                \
}

_AS_CONV_CE_TO_S(long,   int64_t)
_AS_CONV_CE_TO_S(ulong,  uint64_t)
_AS_CONV_CE_TO_S(double, double)
_AS_CONV_CE_TO_S(int,    int32_t)
_AS_CONV_CE_TO_S(uint,   uint32_t)
_AS_CONV_CE_TO_S(float,  float)
_AS_CONV_CE_TO_S(short,  int16_t)
_AS_CONV_CE_TO_S(ushort, uint16_t)

#undef _AS_CONV_CE_TO_S

//-----------------------------------------------------------------------------
// _AS_CONV_CE_TO_V: Complex element to vector reinterpretation
//-----------------------------------------------------------------------------
#define _AS_CONV_CE_TO_V(Name, Ty, Nelem)                                      \
template <typename SRC_T>                                                      \
vtype<Ty, Nelem> __as_ ## Name(const ctype<SRC_T> &src)                        \
{                                                                              \
    using DST_T = Ty;                                                          \
                                                                               \
    constexpr size_t DST_SIZE  = sizeof(DST_T);                                \
    constexpr size_t DST_NELEM = Nelem;                                        \
                                                                               \
    constexpr size_t SRC_SIZE = sizeof(SRC_T);                                 \
                                                                               \
    static_assert((SRC_SIZE * 2) == (DST_SIZE * DST_NELEM),                    \
                  "Illegal reinterpret cast: Data sizes must be the same");    \
                                                                               \
    vtype<DST_T, DST_NELEM> res;                                               \
                                                                               \
    /*----------------------------------------------------------------------*/ \
    /* We can do a copy of the real and imag parts of the source data into  */ \
    /* the destination vector.                                              */ \
    /*----------------------------------------------------------------------*/ \
    size_t dst_lanes_per_src = SRC_SIZE / DST_SIZE;                            \
                                                                               \
    const char *curr_src_real =                                                \
        reinterpret_cast<const char *>(&(src.r));                              \
                                                                               \
    const char *curr_src_imag =                                                \
        reinterpret_cast<const char *>(&(src.i));                              \
                                                                               \
    for (size_t i = 0; i < dst_lanes_per_src; i++)                             \
    {                                                                          \
        DST_T res_lane_real;                                                   \
        DST_T res_lane_imag;                                                   \
        std::memcpy(&res_lane_real,                                            \
                    (curr_src_real + i * DST_SIZE),                            \
                    DST_SIZE);                                                 \
        std::memcpy(&res_lane_imag,                                            \
                    (curr_src_imag + i * DST_SIZE),                            \
                    DST_SIZE);                                                 \
        res.s[dst_lanes_per_src + i] = res_lane_real;                          \
        res.s[i] = res_lane_imag;                                              \
    }                                                                          \
                                                                               \
    return res;                                                                \
}

_AS_CONV_CE_TO_V(long2, int64_t, 2)
_AS_CONV_CE_TO_V(ulong2, uint64_t, 2)
_AS_CONV_CE_TO_V(double2, double, 2)

_AS_CONV_CE_TO_V(int4,  int32_t, 4)
_AS_CONV_CE_TO_V(int2,  int32_t, 2)

_AS_CONV_CE_TO_V(uint4,  uint32_t, 4)
_AS_CONV_CE_TO_V(uint2,  uint32_t, 2)

_AS_CONV_CE_TO_V(float4,  float, 4)
_AS_CONV_CE_TO_V(float2,  float, 2)

_AS_CONV_CE_TO_V(short8,  int16_t, 8)
_AS_CONV_CE_TO_V(short4,  int16_t, 4)
_AS_CONV_CE_TO_V(short2,  int16_t, 2)

_AS_CONV_CE_TO_V(ushort8,  uint16_t, 8)
_AS_CONV_CE_TO_V(ushort4,  uint16_t, 4)
_AS_CONV_CE_TO_V(ushort2,  uint16_t, 2)

_AS_CONV_CE_TO_V(char16, int8_t, 16)
_AS_CONV_CE_TO_V(char8,  int8_t, 8)
_AS_CONV_CE_TO_V(char4,  int8_t, 4)
_AS_CONV_CE_TO_V(char2,  int8_t, 2)

_AS_CONV_CE_TO_V(uchar16, uint8_t, 16)
_AS_CONV_CE_TO_V(uchar8,  uint8_t, 8)
_AS_CONV_CE_TO_V(uchar4,  uint8_t, 4)
_AS_CONV_CE_TO_V(uchar2,  uint8_t, 2)

#undef _AS_CONV_CE_TO_V

//-----------------------------------------------------------------------------
// _AS_CONV_CE_TO_CV: Complex element to complex vector reinterpretation
//-----------------------------------------------------------------------------
#define _AS_CONV_CE_TO_CV(Name, Ty, Nelem)                                     \
template <typename SRC_T>                                                      \
vtype<ctype<Ty>, Nelem> __as_ ## Name(const ctype<SRC_T> &src)                 \
{                                                                              \
    using DST_T = Ty;                                                          \
                                                                               \
    constexpr size_t DST_SIZE  = sizeof(DST_T);                                \
    constexpr size_t DST_NELEM = Nelem;                                        \
    constexpr size_t SRC_SIZE  = sizeof(SRC_T);                                \
                                                                               \
    static_assert((SRC_SIZE * 2) == (DST_SIZE * DST_NELEM * 2),                \
                  "Illegal reinterpret cast: Data sizes must be the same");    \
                                                                               \
    vtype<ctype<DST_T>, DST_NELEM> res;                                        \
                                                                               \
    /*----------------------------------------------------------------------*/ \
    /* We can do a copy of the real and imag parts of the source data into  */ \
    /* the destination complex vector.                                      */ \
    /*----------------------------------------------------------------------*/ \
    size_t dst_lanes_per_src = SRC_SIZE / DST_SIZE;                            \
                                                                               \
    const char *curr_src_i = reinterpret_cast<const char *>(&(src.i));         \
    const char *curr_src_r = reinterpret_cast<const char *>(&(src.r));         \
                                                                               \
    /*----------------------------------------------------------------------*/ \
    /* Copy from imaginary part                                             */ \
    /*----------------------------------------------------------------------*/ \
    for (size_t i = 0; i < dst_lanes_per_src/2; i++)                           \
    {                                                                          \
        ctype<DST_T> res_lane;                                                 \
        std::memcpy(&res_lane.i,                                               \
                    (curr_src_i + 2*i * DST_SIZE), DST_SIZE);                  \
        std::memcpy(&res_lane.r,                                               \
                    (curr_src_i + (2*i+1) * DST_SIZE), DST_SIZE);              \
        res.s[i] = res_lane;                                                   \
    }                                                                          \
                                                                               \
    /*----------------------------------------------------------------------*/ \
    /* Copy from real part                                                  */ \
    /*----------------------------------------------------------------------*/ \
    for (size_t i = 0; i < dst_lanes_per_src/2; i++)                           \
    {                                                                          \
        ctype<DST_T> res_lane;                                                 \
        std::memcpy(&res_lane.i,                                               \
                    (curr_src_r + 2*i * DST_SIZE), DST_SIZE);                  \
        std::memcpy(&res_lane.r,                                               \
                    (curr_src_r + (2*i+1) * DST_SIZE), DST_SIZE);              \
        res.s[i + dst_lanes_per_src/2] = res_lane;                             \
    }                                                                          \
                                                                               \
    return res;                                                                \
}

_AS_CONV_CE_TO_CV(cint2, int32_t, 2)
_AS_CONV_CE_TO_CV(cfloat2, float, 2)

_AS_CONV_CE_TO_CV(cshort4, int16_t, 4)
_AS_CONV_CE_TO_CV(cshort2, int16_t, 2)

_AS_CONV_CE_TO_CV(cchar8, int8_t, 8)
_AS_CONV_CE_TO_CV(cchar4, int8_t, 4)
_AS_CONV_CE_TO_CV(cchar2, int8_t, 2)

#undef _AS_CONV_CE_TO_CV

//-----------------------------------------------------------------------------
// _AS_CONV_S_TO_V: Scalar to vector reinterpretation
//-----------------------------------------------------------------------------
#define _AS_CONV_S_TO_V(Name, Ty, Nelem)                                       \
template <typename SRC_T,                                                      \
           typename = typename std::enable_if_t<std::is_arithmetic<SRC_T>::value>>\
vtype<Ty, Nelem> __as_ ## Name(const SRC_T &src)                               \
{                                                                              \
    using DST_T = Ty;                                                          \
                                                                               \
    constexpr size_t DST_SIZE  = sizeof(DST_T);                                \
    constexpr size_t DST_NELEM = Nelem;                                        \
    constexpr size_t SRC_SIZE  = sizeof(SRC_T);                                \
                                                                               \
    static_assert(SRC_SIZE == (DST_SIZE * DST_NELEM),                          \
                  "Illegal reinterpret cast: Data sizes must be the same");    \
                                                                               \
    vtype<DST_T, DST_NELEM> res;                                               \
                                                                               \
    /*----------------------------------------------------------------------*/ \
    /* We can do a straight-copy of the data from src to dst.               */ \
    /*----------------------------------------------------------------------*/ \
    std::memcpy(res.get_data_arr_ptr(), &src, SRC_SIZE);                       \
                                                                               \
    /*----------------------------------------------------------------------*/ \
    /* Source lane type cannot be the smaller than the destination          */ \
    /*----------------------------------------------------------------------*/ \
    return res;                                                                \
}

_AS_CONV_S_TO_V(int2,    int32_t, 2)
_AS_CONV_S_TO_V(uint2,   uint32_t, 2)

_AS_CONV_S_TO_V(float2,  float, 2)

_AS_CONV_S_TO_V(short4,  int16_t, 4)
_AS_CONV_S_TO_V(short2,  int16_t, 2)

_AS_CONV_S_TO_V(ushort4, uint16_t, 4)
_AS_CONV_S_TO_V(ushort2, uint16_t, 2)

_AS_CONV_S_TO_V(char8,   int8_t, 8)
_AS_CONV_S_TO_V(char4,   int8_t, 4)
_AS_CONV_S_TO_V(char2,   int8_t, 2)

_AS_CONV_S_TO_V(uchar8,  uint8_t, 8)
_AS_CONV_S_TO_V(uchar4,  uint8_t, 4)
_AS_CONV_S_TO_V(uchar2,  uint8_t, 2)

#undef _AS_CONV_S_TO_V

//-----------------------------------------------------------------------------
// _AS_CONV_S_TO_CV: Scalar to complex vector reinterpretation
//-----------------------------------------------------------------------------
#define _AS_CONV_S_TO_CV(Name, Ty, Nelem)                                      \
template <typename SRC_T,                                                      \
           typename = typename std::enable_if_t<std::is_arithmetic<SRC_T>::value>>\
vtype<ctype<Ty>, Nelem> __as_ ## Name(const SRC_T &src)                        \
{                                                                              \
    using DST_T = Ty;                                                          \
                                                                               \
    constexpr size_t DST_SIZE  = sizeof(DST_T);                                \
    constexpr size_t DST_NELEM = Nelem;                                        \
    constexpr size_t SRC_SIZE  = sizeof(SRC_T);                                \
                                                                               \
    static_assert(SRC_SIZE == (DST_SIZE * DST_NELEM * 2),                      \
                  "Illegal reinterpret cast: Data sizes must be the same");    \
                                                                               \
    vtype<ctype<DST_T>, DST_NELEM> res;                                        \
                                                                               \
    /*----------------------------------------------------------------------*/ \
    /* We can do a copy of the source data into the real and imag parts of  */ \
    /* each destination complex vector lane.                                */ \
    /*----------------------------------------------------------------------*/ \
    size_t dst_lanes_per_src = SRC_SIZE / (DST_SIZE * 2);                      \
                                                                               \
    const char *curr_src = reinterpret_cast<const char *>(&src);               \
                                                                               \
    for (size_t i = 0; i < dst_lanes_per_src; i++)                             \
    {                                                                          \
        ctype<DST_T> res_lane;                                                 \
        std::memcpy(&res_lane.i, curr_src + 2*i * DST_SIZE, DST_SIZE);         \
        std::memcpy(&res_lane.r, curr_src + (2*i+1) * DST_SIZE, DST_SIZE);     \
        res.s[i] = res_lane;                                                   \
    }                                                                          \
                                                                               \
    return res;                                                                \
}

_AS_CONV_S_TO_CV(cshort2, int16_t, 2)
_AS_CONV_S_TO_CV(cchar4,  int8_t, 4)
_AS_CONV_S_TO_CV(cchar2,  int8_t, 2)

#undef _AS_CONV_S_TO_CV

//-----------------------------------------------------------------------------
// _AS_CONV_S_TO_CE: Scalar to complex element reinterpretation
//-----------------------------------------------------------------------------
#define _AS_CONV_S_TO_CE(Name, Ty)                                             \
template <typename SRC_T,                                                      \
           typename = typename std::enable_if_t<std::is_arithmetic<SRC_T>::value>>\
ctype<Ty> __as_ ## Name(const SRC_T &src)                                      \
{                                                                              \
    using DST_T = Ty;                                                          \
                                                                               \
    constexpr size_t DST_SIZE = sizeof(DST_T);                                 \
    constexpr size_t SRC_SIZE = sizeof(SRC_T);                                 \
                                                                               \
    static_assert(SRC_SIZE == DST_SIZE * 2,                                    \
                  "Illegal reinterpret cast: Data sizes must be the same");    \
                                                                               \
    ctype<DST_T> res;                                                          \
                                                                               \
    /*----------------------------------------------------------------------*/ \
    /* We can do a copy of the source data into the real and imag parts of  */ \
    /* the destination complex element.                                     */ \
    /*----------------------------------------------------------------------*/ \
    const char *curr_src = reinterpret_cast<const char *>(&src);               \
    std::memcpy(&res.i, curr_src,            DST_SIZE);                        \
    std::memcpy(&res.r, curr_src + DST_SIZE, DST_SIZE);                        \
                                                                               \
    return res;                                                                \
}

_AS_CONV_S_TO_CE(cint,   int32_t)
_AS_CONV_S_TO_CE(cfloat, float)
_AS_CONV_S_TO_CE(cshort, int16_t)
_AS_CONV_S_TO_CE(cchar,  int8_t)

#undef _AS_CONV_S_TO_CE

//-----------------------------------------------------------------------------
// _AS_CONV_S_TO_S: Scalar to scalar reinterpretation
//-----------------------------------------------------------------------------
#define _AS_CONV_S_TO_S(Name, Ty)                                              \
template <typename SRC_T,                                                      \
           typename = typename std::enable_if_t<std::is_arithmetic<SRC_T>::value>>\
Ty __as_ ## Name(const SRC_T &src)                                             \
{                                                                              \
    using DST_T = Ty;                                                          \
                                                                               \
    constexpr size_t DST_SIZE = sizeof(DST_T);                                 \
    constexpr size_t SRC_SIZE = sizeof(SRC_T);                                 \
                                                                               \
    static_assert(SRC_SIZE == DST_SIZE,                                        \
                  "Illegal reinterpret cast: Data sizes must be the same");    \
                                                                               \
    DST_T res;                                                                 \
                                                                               \
    /*----------------------------------------------------------------------*/ \
    /* We can do a straight-copy of the data from src to dst.               */ \
    /*----------------------------------------------------------------------*/ \
    std::memcpy(&res, &src, DST_SIZE);                                         \
                                                                               \
    return res;                                                                \
}

_AS_CONV_S_TO_S(long,   int64_t)
_AS_CONV_S_TO_S(ulong,  uint64_t)
_AS_CONV_S_TO_S(double, double)
_AS_CONV_S_TO_S(int,    int32_t)
_AS_CONV_S_TO_S(uint,   uint32_t)
_AS_CONV_S_TO_S(float,  float)
_AS_CONV_S_TO_S(short,  int16_t)
_AS_CONV_S_TO_S(ushort, uint16_t)
_AS_CONV_S_TO_S(char,   int8_t)
_AS_CONV_S_TO_S(uchar,  uint8_t)

#undef _AS_CONV_S_TO_S

//-----------------------------------------------------------------------------
// _AS_CONV_CE_TO_CE: Complex element to Complex element reinterpretation
//-----------------------------------------------------------------------------
#define _AS_CONV_CE_TO_CE(Name, Ty)                                            \
template <typename SRC_T>                                                      \
ctype<Ty> __as_ ## Name(const ctype<SRC_T> &src)                               \
{                                                                              \
    using DST_T = Ty;                                                          \
                                                                               \
    constexpr size_t DST_SIZE = sizeof(DST_T) * 2;                             \
    constexpr size_t SRC_SIZE = sizeof(SRC_T) * 2;                             \
                                                                               \
    static_assert(SRC_SIZE == DST_SIZE,                                        \
                  "Illegal reinterpret cast: Data sizes must be the same");    \
                                                                               \
    /*----------------------------------------------------------------------*/ \
    /* We can do a straight-copy of the data from src to dst. Since the src */ \
    /* and dst are same size, the real and imag parts will also be the same */ \
    /* size.                                                                */ \
    /*----------------------------------------------------------------------*/ \
    ctype<DST_T> res;                                                          \
    ctype<SRC_T> src_tmp(src);                                                 \
                                                                               \
    std::memcpy(res.get_data_arr_ptr(), src_tmp.get_data_arr_ptr(), DST_SIZE); \
                                                                               \
    return res;                                                                \
}

_AS_CONV_CE_TO_CE(clong,   int64_t)
_AS_CONV_CE_TO_CE(cdouble, double)
_AS_CONV_CE_TO_CE(cint,    int32_t)
_AS_CONV_CE_TO_CE(cfloat,  float)
_AS_CONV_CE_TO_CE(cchar,   int8_t)
_AS_CONV_CE_TO_CE(cshort,  int16_t)

#undef _AS_CONV_CE_TO_CE

//-----------------------------------------------------------------------------
// CONVERT_<TYPE> CASTING CONVERSIONS - THESE CONVERSIONS TAKE TWO VECTORS OF
// VARYING TYPES AND IDENTICAL NUMBERS OF ELEMENTS AND CONVERTS EACH SOURCE
// ELEMENT INTO THE DESTINATION TYPE.
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// _CONV_CONV_V_TO_V: Vector to vector conversion
//-----------------------------------------------------------------------------
#define _CONV_CONV_V_TO_V(Name, Ty, Nelem)                                     \
template <typename SRC_T, size_t SRC_NELEM, size_t DEPTH>                      \
vtype<Ty, Nelem> __convert_ ## Name(const accessible<SRC_T, SRC_NELEM, DEPTH> &src)   \
{                                                                              \
    using DST_T = Ty;                                                          \
                                                                               \
    constexpr size_t DST_NELEM = Nelem;                                        \
                                                                               \
    static_assert(SRC_NELEM == DST_NELEM,                                      \
                  "Illegal conversion cast: Element counts must be the same"); \
                                                                               \
    vtype<DST_T, DST_NELEM> res;                                               \
    for (size_t i = 0; i < DST_NELEM; i++)                                     \
        res.s[i] = (DST_T)src.s[i];                                            \
                                                                               \
    return res;                                                                \
}

_CONV_CONV_V_TO_V(long16, int64_t, 16)
_CONV_CONV_V_TO_V(long8, int64_t, 8)
_CONV_CONV_V_TO_V(long4, int64_t, 4)
_CONV_CONV_V_TO_V(long2, int64_t, 2)

_CONV_CONV_V_TO_V(ulong16, uint64_t, 16)
_CONV_CONV_V_TO_V(ulong8, uint64_t, 8)
_CONV_CONV_V_TO_V(ulong4, uint64_t, 4)
_CONV_CONV_V_TO_V(ulong2, uint64_t, 2)

_CONV_CONV_V_TO_V(double16, double, 16)
_CONV_CONV_V_TO_V(double8, double, 8)
_CONV_CONV_V_TO_V(double4, double, 4)
_CONV_CONV_V_TO_V(double2, double, 2)

_CONV_CONV_V_TO_V(int16, int32_t, 16)
_CONV_CONV_V_TO_V(int8,  int32_t, 8)
_CONV_CONV_V_TO_V(int4,  int32_t, 4)
_CONV_CONV_V_TO_V(int2,  int32_t, 2)

_CONV_CONV_V_TO_V(uint16, uint32_t, 16)
_CONV_CONV_V_TO_V(uint8,  uint32_t, 8)
_CONV_CONV_V_TO_V(uint4,  uint32_t, 4)
_CONV_CONV_V_TO_V(uint2,  uint32_t, 2)

_CONV_CONV_V_TO_V(float16, float, 16)
_CONV_CONV_V_TO_V(float8,  float, 8)
_CONV_CONV_V_TO_V(float4,  float, 4)
_CONV_CONV_V_TO_V(float2,  float, 2)

_CONV_CONV_V_TO_V(short32, int16_t, 32)
_CONV_CONV_V_TO_V(short16, int16_t, 16)
_CONV_CONV_V_TO_V(short8,  int16_t, 8)
_CONV_CONV_V_TO_V(short4,  int16_t, 4)
_CONV_CONV_V_TO_V(short2,  int16_t, 2)

_CONV_CONV_V_TO_V(ushort32, uint16_t, 32)
_CONV_CONV_V_TO_V(ushort16, uint16_t, 16)
_CONV_CONV_V_TO_V(ushort8,  uint16_t, 8)
_CONV_CONV_V_TO_V(ushort4,  uint16_t, 4)
_CONV_CONV_V_TO_V(ushort2,  uint16_t, 2)

_CONV_CONV_V_TO_V(char64, int8_t, 64)
_CONV_CONV_V_TO_V(char32, int8_t, 32)
_CONV_CONV_V_TO_V(char16, int8_t, 16)
_CONV_CONV_V_TO_V(char8,  int8_t, 8)
_CONV_CONV_V_TO_V(char4,  int8_t, 4)
_CONV_CONV_V_TO_V(char2,  int8_t, 2)

_CONV_CONV_V_TO_V(uchar64, uint8_t, 64)
_CONV_CONV_V_TO_V(uchar32, uint8_t, 32)
_CONV_CONV_V_TO_V(uchar16, uint8_t, 16)
_CONV_CONV_V_TO_V(uchar8,  uint8_t, 8)
_CONV_CONV_V_TO_V(uchar4,  uint8_t, 4)
_CONV_CONV_V_TO_V(uchar2,  uint8_t, 2)

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

#undef _CONV_CONV_S_TO_S

//-----------------------------------------------------------------------------
// _CONV_CONV_CV_TO_CV: Complex vector to complex vector conversion
//-----------------------------------------------------------------------------
#define _CONV_CONV_CV_TO_CV(Name, Ty, Nelem)                                   \
template <typename SRC_T, size_t SRC_NELEM, size_t DEPTH,                      \
          typename = enable_if_cmplx_t<SRC_T, void>>                           \
vtype<ctype<Ty>, Nelem> __convert_ ## Name(const accessible<SRC_T, SRC_NELEM, DEPTH> &src)   \
{                                                                              \
    using DST_T = Ty;                                                          \
                                                                               \
    constexpr size_t DST_NELEM = Nelem;                                        \
                                                                               \
    static_assert(SRC_NELEM == DST_NELEM,                                      \
                  "Illegal conversion cast: Element counts must be the same"); \
                                                                               \
    vtype<ctype<DST_T>, DST_NELEM> res;                                        \
    for (size_t i = 0; i < DST_NELEM; i++)                                     \
    {                                                                          \
        res.s[i].r = (DST_T)src.s[i].r;                                        \
        res.s[i].i = (DST_T)src.s[i].i;                                        \
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
    res.r = (DST_T)src.r;                                                      \
    res.i = (DST_T)src.i;                                                      \
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
