/*****************************************************************************/
/*  C7X_LOAD_STORES.H                                                     */
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
#ifndef C7X_LDST_H
#define C7X_LDST_H

#include <c7x.h>
#include <limits> // std::numeric_limits
#include <type_traits>

using namespace _c70_he_detail;

/*****************************************************************************
* Helper function used to check if predicate is true at index
*****************************************************************************/
bool check_pred_at_index(__vpred pred, uint64_t index, uint64_t element_size);

/*****************************************************************************
* VLOAD (only predicated forms)
*****************************************************************************/
// __char2 __vload_pred(__vpred, const __char2*);
// __char4 __vload_pred(__vpred, const __char4*);
// __char8 __vload_pred(__vpred, const __char8*);
// __char16 __vload_pred(__vpred, const __char16*);
// __char32 __vload_pred(__vpred, const __char32*);
// __char64 __vload_pred(__vpred, const __char64*);
// __uchar2 __vload_pred(__vpred, const __uchar2*);
// __uchar4 __vload_pred(__vpred, const __uchar4*);
// __uchar8 __vload_pred(__vpred, const __uchar8*);
// __uchar16 __vload_pred(__vpred, const __uchar16*);
// __uchar32 __vload_pred(__vpred, const __uchar32*);
// __uchar64 __vload_pred(__vpred, const __uchar64*);
// __short2 __vload_pred(__vpred, const __short2*);
// __short4 __vload_pred(__vpred, const __short4*);
// __short8 __vload_pred(__vpred, const __short8*);
// __short16 __vload_pred(__vpred, const __short16*);
// __short32 __vload_pred(__vpred, const __short32*);
// __ushort2 __vload_pred(__vpred, const __ushort2*);
// __ushort4 __vload_pred(__vpred, const __ushort4*);
// __ushort8 __vload_pred(__vpred, const __ushort8*);
// __ushort16 __vload_pred(__vpred, const __ushort16*);
// __ushort32 __vload_pred(__vpred, const __ushort32*);
// __cchar2 __vload_pred(__vpred, const __cchar2*);
// __cchar4 __vload_pred(__vpred, const __cchar4*);
// __cchar8 __vload_pred(__vpred, const __cchar8*);
// __cchar16 __vload_pred(__vpred, const __cchar16*);
// __cchar32 __vload_pred(__vpred, const __cchar32*);
// __int2 __vload_pred(__vpred, const __int2*);
// __int4 __vload_pred(__vpred, const __int4*);
// __int8 __vload_pred(__vpred, const __int8*);
// __int16 __vload_pred(__vpred, const __int16*);
// __uint2 __vload_pred(__vpred, const __uint2*);
// __uint4 __vload_pred(__vpred, const __uint4*);
// __uint8 __vload_pred(__vpred, const __uint8*);
// __uint16 __vload_pred(__vpred, const __uint16*);
// __float2 __vload_pred(__vpred, const __float2*);
// __float4 __vload_pred(__vpred, const __float4*);
// __float8 __vload_pred(__vpred, const __float8*);
// __float16 __vload_pred(__vpred, const __float16*);
// __cshort2 __vload_pred(__vpred, const __cshort2*);
// __cshort4 __vload_pred(__vpred, const __cshort4*);
// __cshort8 __vload_pred(__vpred, const __cshort8*);
// __cshort16 __vload_pred(__vpred, const __cshort16*);
// __long2 __vload_pred(__vpred, const __long2*);
// __long4 __vload_pred(__vpred, const __long4*);
// __long8 __vload_pred(__vpred, const __long8*);
// __ulong2 __vload_pred(__vpred, const __ulong2*);
// __ulong4 __vload_pred(__vpred, const __ulong4*);
// __ulong8 __vload_pred(__vpred, const __ulong8*);
// __double2 __vload_pred(__vpred, const __double2*);
// __double4 __vload_pred(__vpred, const __double4*);
// __double8 __vload_pred(__vpred, const __double8*);
// __cint2 __vload_pred(__vpred, const __cint2*);
// __cint4 __vload_pred(__vpred, const __cint4*);
// __cint8 __vload_pred(__vpred, const __cint8*);
// __cfloat2 __vload_pred(__vpred, const __cfloat2*);
// __cfloat4 __vload_pred(__vpred, const __cfloat4*);
// __cfloat8 __vload_pred(__vpred, const __cfloat8*);
template<typename ELEM_T,
         size_t NELEM,
         typename RES_T = vtype<ELEM_T, NELEM, VTYPE_KIND::DATA> >
RES_T __vload_pred(__vpred pred,
                   const vtype<ELEM_T, NELEM, VTYPE_KIND::DATA> *input)
{
    RES_T ret;
    memset(&ret, 0, sizeof(RES_T));

    for(size_t i = 0; i < NELEM; i++)
        if (check_pred_at_index(pred, i, sa_scale<ELEM_T>::value))
            ret.s[i] = (*input).s[i];
    return ret;
}

// __cchar __vload_pred(__vpred, const __cchar*);
// __cshort __vload_pred(__vpred, const __cshort*);
// __cint __vload_pred(__vpred, const __cint*);
// __cfloat __vload_pred(__vpred, const __cfloat*);
template<typename COMP_T,
         typename RES_T = ctype<COMP_T> >
RES_T __vload_pred(__vpred pred, const ctype<COMP_T> *input)
{
    RES_T ret;
    memset(&ret, 0, sizeof(RES_T));

    if (check_pred_at_index(pred, 0, sizeof(COMP_T) * 2))
        ret = *input;
    return ret;
}

// int8_t __vload_pred(__vpred, const int8_t*);
// uint8_t __vload_pred(__vpred, const uint8_t*);
// int16_t __vload_pred(__vpred, const int16_t*);
// uint16_t __vload_pred(__vpred, const uint16_t*);
// uint32_t __vload_pred(__vpred, const uint32_t*);
// int32_t __vload_pred(__vpred, const int32_t*);
// float __vload_pred(__vpred, const float*);
// int64_t __vload_pred(__vpred, const int64_t*);
// __ulong __vload_pred(__vpred, const __ulong*);
// double __vload_pred(__vpred, const double*);
template<typename ELEM_T,
         // This enable_if keeps the complex type overload from conflicting
         // with this overload. Without this we get template resolution
         // ambiguity from the BLD macro.
         std::enable_if_t<std::is_arithmetic<ELEM_T>::value, int> = 0>
ELEM_T __vload_pred(__vpred pred, const ELEM_T *input)
{
    if (check_pred_at_index(pred, 0, sa_scale<ELEM_T>::value))
      return *input;
    return 0;
}

/*****************************************************************************
* VLOAD_DUP
*****************************************************************************/
// __char64 __vload_pred_dup(__vpred, const __char32*);
// __char64 __vload_pred_dup(__vpred, const __char16*);
// __char64 __vload_pred_dup(__vpred, const __char8*);
// __char64 __vload_pred_dup(__vpred, const __char4*);
// __char64 __vload_pred_dup(__vpred, const __char2*);
// __uchar64 __vload_pred_dup(__vpred, const __uchar32*);
// __uchar64 __vload_pred_dup(__vpred, const __uchar16*);
// __uchar64 __vload_pred_dup(__vpred, const __uchar8*);
// __uchar64 __vload_pred_dup(__vpred, const __uchar4*);
// __uchar64 __vload_pred_dup(__vpred, const __uchar2*);
// __short32 __vload_pred_dup(__vpred, const __short16*);
// __short32 __vload_pred_dup(__vpred, const __short8*);
// __short32 __vload_pred_dup(__vpred, const __short4*);
// __short32 __vload_pred_dup(__vpred, const __short2*);
// __ushort32 __vload_pred_dup(__vpred, const __ushort16*);
// __ushort32 __vload_pred_dup(__vpred, const __ushort8*);
// __ushort32 __vload_pred_dup(__vpred, const __ushort4*);
// __ushort32 __vload_pred_dup(__vpred, const __ushort2*);
// __int16 __vload_pred_dup(__vpred, const __int8*);
// __int16 __vload_pred_dup(__vpred, const __int4*);
// __int16 __vload_pred_dup(__vpred, const __int2*);
// __uint16 __vload_pred_dup(__vpred, const __uint8*);
// __uint16 __vload_pred_dup(__vpred, const __uint4*);
// __uint16 __vload_pred_dup(__vpred, const __uint2*);
// __float16 __vload_pred_dup(__vpred, const __float8*);
// __float16 __vload_pred_dup(__vpred, const __float4*);
// __float16 __vload_pred_dup(__vpred, const __float2*);
// __long8 __vload_pred_dup(__vpred, const __long4*);
// __long8 __vload_pred_dup(__vpred, const __long2*);
// __ulong8 __vload_pred_dup(__vpred, const __ulong4*);
// __ulong8 __vload_pred_dup(__vpred, const __ulong2*);
// __ulong8 __vload_pred_dup(__vpred, const __ulong*);
// __double8 __vload_pred_dup(__vpred, const __double4*);
// __double8 __vload_pred_dup(__vpred, const __double2*);
template<typename ELEM_T,
         size_t NELEM,
	 size_t RES_NELEM = __C7X_VEC_SIZE_BYTES__/sizeof(ELEM_T),
         typename RES_T = vtype<ELEM_T, RES_NELEM, VTYPE_KIND::DATA> >
RES_T __vload_pred_dup(__vpred pred,
                       const vtype<ELEM_T, NELEM, VTYPE_KIND::DATA> *input)
{
    constexpr size_t num_duplicate = RES_NELEM / NELEM;
    RES_T ret;
    memset(&ret, 0, sizeof(RES_T));

    for(size_t i = 0; i < NELEM; i++)
        if (check_pred_at_index(pred, i, sizeof(ELEM_T)))
            for(size_t j = 0; j < num_duplicate; j++)
                ret.s[num_duplicate*i+j] = (*input).s[i];
    return ret;
}

// __char64 __vload_dup(const __char32*);
// __char64 __vload_dup(const __char16*);
// __char64 __vload_dup(const __char8*);
// __char64 __vload_dup(const __char4*);
// __char64 __vload_dup(const __char2*);
// __uchar64 __vload_dup(const __uchar32*);
// __uchar64 __vload_dup(const __uchar16*);
// __uchar64 __vload_dup(const __uchar8*);
// __uchar64 __vload_dup(const __uchar4*);
// __uchar64 __vload_dup(const __uchar2*);
// __short32 __vload_dup(const __short16*);
// __short32 __vload_dup(const __short8*);
// __short32 __vload_dup(const __short4*);
// __short32 __vload_dup(const __short2*);
// __ushort32 __vload_dup(const __ushort16*);
// __ushort32 __vload_dup(const __ushort8*);
// __ushort32 __vload_dup(const __ushort4*);
// __ushort32 __vload_dup(const __ushort2*);
// __int16 __vload_dup(const __int8*);
// __int16 __vload_dup(const __int4*);
// __int16 __vload_dup(const __int2*);
// __uint16 __vload_dup(const __uint8*);
// __uint16 __vload_dup(const __uint4*);
// __uint16 __vload_dup(const __uint2*);
// __float16 __vload_dup(const __float8*);
// __float16 __vload_dup(const __float4*);
// __float16 __vload_dup(const __float2*);
// __long8 __vload_dup(const __long4*);
// __long8 __vload_dup(const __long2*);
// __ulong8 __vload_dup(const __ulong4*);
// __ulong8 __vload_dup(const __ulong2*);
// __double8 __vload_dup(const __double4*);
// __double8 __vload_dup(const __double2*);
template<typename ELEM_T,
         size_t NELEM,
         size_t RES_NELEM = __C7X_VEC_SIZE_BYTES__/sizeof(ELEM_T),
         typename RES_T = vtype<ELEM_T, RES_NELEM, VTYPE_KIND::DATA> >
RES_T __vload_dup(const vtype<ELEM_T, NELEM, VTYPE_KIND::DATA> *input)
{
    return __vload_pred_dup(__vpred(UINT64_MAX), input);
}

// __char64 __vload_pred_dup(__vpred, const int8_t*);
// __uchar64 __vload_pred_dup(__vpred, const __uchar*);
// __short32 __vload_pred_dup(__vpred, const int16_t*);
// __ushort32 __vload_pred_dup(__vpred, const __ushort*);
// __int16 __vload_pred_dup(__vpred, const int32_t*);
// __uint16 __vload_pred_dup(__vpred, const __uint*);
// __float16 __vload_pred_dup(__vpred, const float*);
// __long8 __vload_pred_dup(__vpred, const int64_t*);
// __double8 __vload_pred_dup(__vpred, const double*);
template<typename ELEM_T,
         size_t RES_NELEM = __C7X_VEC_SIZE_BYTES__/sizeof(ELEM_T),
         typename RES_T = vtype<ELEM_T, RES_NELEM, VTYPE_KIND::DATA>,
         std::enable_if_t<std::is_arithmetic<ELEM_T>::value &&
         !std::is_same<ELEM_T, char>::value, int> = 0>
RES_T __vload_pred_dup(__vpred pred, const ELEM_T* input)
{
    RES_T ret;
    memset(&ret, 0, sizeof(RES_T));

    if (check_pred_at_index(pred, 0, sizeof(ELEM_T)))
        for(size_t i = 0; i < RES_NELEM; i++)
            ret.s[i] = *input;
    return ret;
}

// __char64 __vload_dup(const int8_t*);
// __uchar64 __vload_dup(const __uchar*);
// __short32 __vload_dup(const int16_t*);
// __ushort32 __vload_dup(const __ushort*);
// __int16 __vload_dup(const int32_t*);
// __uint16 __vload_dup(const __uint*);
// __float16 __vload_dup(const float*);
// __long8 __vload_dup(const int64_t*);
// __ulong8 __vload_dup(const __ulong*);
// __double8 __vload_dup(const double*);
template<typename ELEM_T,
         size_t RES_NELEM = __C7X_VEC_SIZE_BYTES__/sizeof(ELEM_T),
         typename RES_T = vtype<ELEM_T, RES_NELEM, VTYPE_KIND::DATA>,
         std::enable_if_t<std::is_arithmetic<ELEM_T>::value &&
         !std::is_same<ELEM_T, char>::value, int> = 0>
RES_T __vload_dup(const ELEM_T* input)
{
    return (RES_T)*input; // Cast to vector
}

/*****************************************************************************
* VLOAD_DUP_VEC
*****************************************************************************/
// __short32 __vload_pred_dup_vec(__vpred, const __short8*);
// __ushort32 __vload_pred_dup_vec(__vpred, const __ushort8*);
// __short32 __vload_pred_dup_vec(__vpred, const __short4*);
// __ushort32 __vload_pred_dup_vec(__vpred, const __ushort4*);
template<typename ELEM_T,
         size_t NELEM,
         size_t RES_NELEM = 32,
         typename RES_T = vtype<ELEM_T, RES_NELEM, VTYPE_KIND::DATA>,
         std::enable_if_t<(   std::is_same<ELEM_T, int16_t>::value
                           || std::is_same<ELEM_T, uint16_t>::value) &&
                          (NELEM == 4 || NELEM == 8), int> = 0>
RES_T __vload_pred_dup_vec(__vpred pred,
                           const vtype<ELEM_T, NELEM, VTYPE_KIND::DATA> *input)
{
    // Number of times the "group" (input vec) will be duplicated
    constexpr size_t num_group_duplicates = RES_NELEM / NELEM;
    RES_T ret;
    memset(&ret, 0, sizeof(RES_T));

    for(size_t i = 0; i < num_group_duplicates; i++)
        for(size_t j = 0; j < NELEM; j++)
            if (check_pred_at_index(pred, j, sizeof(ELEM_T)))
                ret.s[NELEM*i+j] = (*input).s[j];
    return ret;
}

// __short32 __vload_dup_vec(const __short8*);
// __ushort32 __vload_dup_vec(const __ushort8*);
// __short32 __vload_dup_vec(const __short4*);
// __ushort32 __vload_dup_vec(const __ushort4*);
template<typename ELEM_T,
         size_t NELEM,
         size_t RES_NELEM = 32,
         typename RES_T = vtype<ELEM_T, RES_NELEM, VTYPE_KIND::DATA>,
         std::enable_if_t<std::numeric_limits<ELEM_T>::is_integer &&
                          sizeof(ELEM_T) == sizeof(int16_t) &&
                          (NELEM == 4 || NELEM == 8), int> = 0>
RES_T __vload_dup_vec(const vtype<ELEM_T, NELEM, VTYPE_KIND::DATA> *input)
{
    return __vload_pred_dup_vec(__vpred(UINT64_MAX), input);
}

/*****************************************************************************
* VLOAD_UNPACK_SHORT
*****************************************************************************/
// __short2 __vload_pred_unpack_short(__vpred, const __char2*);
// __short4 __vload_pred_unpack_short(__vpred, const __char4*);
// __short8 __vload_pred_unpack_short(__vpred, const __char8*);
// __short16 __vload_pred_unpack_short(__vpred, const __char16*);
// __short32 __vload_pred_unpack_short(__vpred, const __char32*);
// __ushort2 __vload_pred_unpack_short(__vpred, const __uchar2*);
// __ushort4 __vload_pred_unpack_short(__vpred, const __uchar4*);
// __ushort8 __vload_pred_unpack_short(__vpred, const __uchar8*);
// __ushort16 __vload_pred_unpack_short(__vpred, const __uchar16*);
// __ushort32 __vload_pred_unpack_short(__vpred, const __uchar32*);
template<typename ELEM_T,
         size_t NELEM,
         typename RES_ELEM_T = typename std::conditional<std::is_signed<ELEM_T>::value,int16_t,uint16_t>::type,
         typename RES_T = vtype<RES_ELEM_T, NELEM, VTYPE_KIND::DATA>,
         std::enable_if_t<std::numeric_limits<ELEM_T>::is_integer &&
                          sizeof(ELEM_T) < sizeof(int16_t) &&
                          NELEM <= 32, int> = 0>
RES_T __vload_pred_unpack_short(__vpred pred,
                                const vtype<ELEM_T, NELEM, VTYPE_KIND::DATA> *input)
{
    RES_T ret;
    memset(&ret, 0, sizeof(RES_T));

    for(size_t i = 0; i < NELEM; i++)
        if (check_pred_at_index(pred, i, sizeof(ELEM_T)))
            ret.s[i] = (*input).s[i];
    return ret;
}

// __short2 __vload_unpack_short(const __char2*);
// __short4 __vload_unpack_short(const __char4*);
// __short8 __vload_unpack_short(const __char8*);
// __short16 __vload_unpack_short(const __char16*);
// __short32 __vload_unpack_short(const __char32*);
// __ushort2 __vload_unpack_short(const __uchar2*);
// __ushort4 __vload_unpack_short(const __uchar4*);
// __ushort8 __vload_unpack_short(const __uchar8*);
// __ushort16 __vload_unpack_short(const __uchar16*);
// __ushort32 __vload_unpack_short(const __uchar32*);
template<typename ELEM_T,
         size_t NELEM,
         typename RES_ELEM_T = typename std::conditional<std::is_signed<ELEM_T>::value,int16_t,uint16_t>::type,
         typename RES_T = vtype<RES_ELEM_T, NELEM, VTYPE_KIND::DATA>,
         std::enable_if_t<std::numeric_limits<ELEM_T>::is_integer &&
                          sizeof(ELEM_T) < sizeof(int16_t) &&
                          NELEM <= 32, int> = 0>
RES_T __vload_unpack_short(const vtype<ELEM_T, NELEM, VTYPE_KIND::DATA> *input)
{
    return __vload_pred_unpack_short(__vpred(UINT64_MAX), input);
}

// int16_t __vload_pred_unpack_short(__vpred, const int8_t*);
// __ushort __vload_pred_unpack_short(__vpred, const __uchar*);
template<typename ELEM_T,
         typename RES_T = typename std::conditional<std::is_signed<ELEM_T>::value,int16_t,uint16_t>::type,
         std::enable_if_t<std::numeric_limits<ELEM_T>::is_integer &&
                          sizeof(ELEM_T) < sizeof(int16_t) &&
                          !std::is_same<ELEM_T, char>::value, int> = 0>
RES_T __vload_pred_unpack_short(__vpred pred, const ELEM_T* input)
{
    if (check_pred_at_index(pred, 0, sizeof(ELEM_T)))
        return *input;
    return 0;
}

// int16_t __vload_unpack_short(const int8_t*);
// __ushort __vload_unpack_short(const __uchar*);
template<typename ELEM_T,
         typename RES_T = typename std::conditional<std::is_signed<ELEM_T>::value,int16_t,uint16_t>::type,
         std::enable_if_t<std::numeric_limits<ELEM_T>::is_integer &&
                          sizeof(ELEM_T) < sizeof(int16_t) &&
                          !std::is_same<ELEM_T, char>::value, int> = 0>
RES_T __vload_unpack_short(const ELEM_T* input)
{
    return __vload_pred_unpack_short(__vpred(UINT64_MAX), input);
}

/*****************************************************************************
* VLOAD_UNPACK_INT
*****************************************************************************/
// __int2 __vload_pred_unpack_int(__vpred, const __char2*);
// __int4 __vload_pred_unpack_int(__vpred, const __char4*);
// __int8 __vload_pred_unpack_int(__vpred, const __char8*);
// __int16 __vload_pred_unpack_int(__vpred, const __char16*);
// __uint2 __vload_pred_unpack_int(__vpred, const __uchar2*);
// __uint4 __vload_pred_unpack_int(__vpred, const __uchar4*);
// __uint8 __vload_pred_unpack_int(__vpred, const __uchar8*);
// __uint16 __vload_pred_unpack_int(__vpred, const __uchar16*);
// __int2 __vload_pred_unpack_int(__vpred, const __short2*);
// __int4 __vload_pred_unpack_int(__vpred, const __short4*);
// __int8 __vload_pred_unpack_int(__vpred, const __short8*);
// __int16 __vload_pred_unpack_int(__vpred, const __short16*);
// __uint2 __vload_pred_unpack_int(__vpred, const __ushort2*);
// __uint4 __vload_pred_unpack_int(__vpred, const __ushort4*);
// __uint8 __vload_pred_unpack_int(__vpred, const __ushort8*);
// __uint16 __vload_pred_unpack_int(__vpred, const __ushort16*);
template<typename ELEM_T,
         size_t NELEM,
         typename RES_ELEM_T = typename std::conditional<std::is_signed<ELEM_T>::value,int32_t,uint32_t>::type,
         typename RES_T = vtype<RES_ELEM_T, NELEM, VTYPE_KIND::DATA>,
         std::enable_if_t<std::numeric_limits<ELEM_T>::is_integer &&
                          sizeof(ELEM_T) < sizeof(int32_t) &&
                          NELEM <= 16, int> = 0>
RES_T __vload_pred_unpack_int(__vpred pred,
                              const vtype<ELEM_T, NELEM, VTYPE_KIND::DATA> *input)
{
    RES_T ret;
    memset(&ret, 0, sizeof(RES_T));

    for(size_t i = 0; i < NELEM; i++)
        if (check_pred_at_index(pred, i, sizeof(ELEM_T)))
            ret.s[i] = (*input).s[i];
    return ret;
}

// __int2 __vload_unpack_int(const __char2*);
// __int4 __vload_unpack_int(const __char4*);
// __int8 __vload_unpack_int(const __char8*);
// __int16 __vload_unpack_int(const __char16*);
// __uint2 __vload_unpack_int(const __uchar2*);
// __uint4 __vload_unpack_int(const __uchar4*);
// __uint8 __vload_unpack_int(const __uchar8*);
// __uint16 __vload_unpack_int(const __uchar16*);
// __int2 __vload_unpack_int(const __short2*);
// __int4 __vload_unpack_int(const __short4*);
// __int8 __vload_unpack_int(const __short8*);
// __int16 __vload_unpack_int(const __short16*);
// __uint2 __vload_unpack_int(const __ushort2*);
// __uint4 __vload_unpack_int(const __ushort4*);
// __uint8 __vload_unpack_int(const __ushort8*);
// __uint16 __vload_unpack_int(const __ushort16*);
template<typename ELEM_T,
         size_t NELEM,
         typename RES_ELEM_T = typename std::conditional<std::is_signed<ELEM_T>::value,int32_t,uint32_t>::type,
         typename RES_T = vtype<RES_ELEM_T, NELEM, VTYPE_KIND::DATA>,
         std::enable_if_t<std::numeric_limits<ELEM_T>::is_integer &&
                          sizeof(ELEM_T) < sizeof(int32_t) &&
                          NELEM <= 16, int> = 0>
RES_T __vload_unpack_int(const vtype<ELEM_T, NELEM, VTYPE_KIND::DATA> *input)
{
    return __vload_pred_unpack_int(__vpred(UINT64_MAX), input);
}

// int32_t __vload_pred_unpack_int(__vpred, const int8_t*);
// __uint __vload_pred_unpack_int(__vpred, const __uchar*);
// int32_t __vload_pred_unpack_int(__vpred, const int16_t*);
// __uint __vload_pred_unpack_int(__vpred, const __ushort*);
template<typename ELEM_T,
         typename RES_T = typename std::conditional<std::is_signed<ELEM_T>::value,int32_t,uint32_t>::type,
         std::enable_if_t<std::numeric_limits<ELEM_T>::is_integer &&
                          sizeof(ELEM_T) < sizeof(uint32_t) &&
                          !std::is_same<ELEM_T, char>::value, int> = 0>
RES_T __vload_pred_unpack_int(__vpred pred, const ELEM_T* input)
{
    if (check_pred_at_index(pred, 0, sizeof(ELEM_T)))
        return *input;
    return 0;
}

// int32_t __vload_unpack_int(const int8_t*);
// __uint __vload_unpack_int(const __uchar*);
// int32_t __vload_unpack_int(const int16_t*);
// __uint __vload_unpack_int(const __ushort*);
template<typename ELEM_T,
         typename RES_T = typename std::conditional<std::is_signed<ELEM_T>::value,int32_t,uint32_t>::type,
         std::enable_if_t<std::numeric_limits<ELEM_T>::is_integer &&
                          sizeof(ELEM_T) < sizeof(int32_t) &&
                          !std::is_same<ELEM_T, char>::value, int> = 0>
RES_T __vload_unpack_int(const ELEM_T* input)
{
    return __vload_pred_unpack_int(__vpred(UINT64_MAX), input);
}

/*****************************************************************************
* VLOAD_UNPACK_LONG
*****************************************************************************/
// __long2 __vload_pred_unpack_long(__vpred, const __char2*);
// __long4 __vload_pred_unpack_long(__vpred, const __char4*);
// __long8 __vload_pred_unpack_long(__vpred, const __char8*);
// __ulong2 __vload_pred_unpack_long(__vpred, const __uchar2*);
// __ulong4 __vload_pred_unpack_long(__vpred, const __uchar4*);
// __ulong8 __vload_pred_unpack_long(__vpred, const __uchar8*);
// __long2 __vload_pred_unpack_long(__vpred, const __short2*);
// __long4 __vload_pred_unpack_long(__vpred, const __short4*);
// __long8 __vload_pred_unpack_long(__vpred, const __short8*);
// __ulong2 __vload_pred_unpack_long(__vpred, const __ushort2*);
// __ulong4 __vload_pred_unpack_long(__vpred, const __ushort4*);
// __ulong8 __vload_pred_unpack_long(__vpred, const __ushort8*);
// __long2 __vload_pred_unpack_long(__vpred, const __int2*);
// __long4 __vload_pred_unpack_long(__vpred, const __int4*);
// __long8 __vload_pred_unpack_long(__vpred, const __int8*);
// __ulong2 __vload_pred_unpack_long(__vpred, const __uint2*);
// __ulong4 __vload_pred_unpack_long(__vpred, const __uint4*);
// __ulong8 __vload_pred_unpack_long(__vpred, const __uint8*);

template<typename ELEM_T,
         size_t NELEM,
         typename RES_ELEM_T = typename std::conditional<std::is_signed<ELEM_T>::value,int64_t,uint64_t>::type,
         typename RES_T = vtype<RES_ELEM_T, NELEM, VTYPE_KIND::DATA>,
         std::enable_if_t<std::numeric_limits<ELEM_T>::is_integer &&
                          sizeof(ELEM_T) < sizeof(int64_t) &&
                          NELEM <= 8, int> = 0>
RES_T __vload_pred_unpack_long(__vpred pred,
                               const vtype<ELEM_T, NELEM, VTYPE_KIND::DATA> *input)
{
    RES_T ret;
    memset(&ret, 0, sizeof(RES_T));

    for(size_t i = 0; i < NELEM; i++)
        if (check_pred_at_index(pred, i, sizeof(ELEM_T)))
            ret.s[i] = (*input).s[i];
    return ret;
}

// __long2 __vload_unpack_long(const __char2*);
// __long4 __vload_unpack_long(const __char4*);
// __long8 __vload_unpack_long(const __char8*);
// __ulong2 __vload_unpack_long(const __uchar2*);
// __ulong4 __vload_unpack_long(const __uchar4*);
// __ulong8 __vload_unpack_long(const __uchar8*);
// __long2 __vload_unpack_long(const __short2*);
// __long4 __vload_unpack_long(const __short4*);
// __long8 __vload_unpack_long(const __short8*);
// __ulong2 __vload_unpack_long(const __ushort2*);
// __ulong4 __vload_unpack_long(const __ushort4*);
// __ulong8 __vload_unpack_long(const __ushort8*);
// __long2 __vload_unpack_long(const __int2*);
// __long4 __vload_unpack_long(const __int4*);
// __long8 __vload_unpack_long(const __int8*);
// __ulong2 __vload_unpack_long(const __uint2*);
// __ulong4 __vload_unpack_long(const __uint4*);
// __ulong8 __vload_unpack_long(const __uint8*);
template<typename ELEM_T,
         size_t NELEM,
         typename RES_ELEM_T = typename std::conditional<std::is_signed<ELEM_T>::value,int64_t,uint64_t>::type,
         typename RES_T = vtype<RES_ELEM_T, NELEM, VTYPE_KIND::DATA>,
         std::enable_if_t<std::numeric_limits<ELEM_T>::is_integer &&
                          sizeof(ELEM_T) < sizeof(int64_t) &&
                          NELEM <= 8, int> = 0>
RES_T __vload_unpack_long(const vtype<ELEM_T, NELEM, VTYPE_KIND::DATA> *input)
{
    return __vload_pred_unpack_long(__vpred(UINT64_MAX), input);
}

// int64_t __vload_pred_unpack_long(__vpred, const int8_t*);
// __ulong __vload_pred_unpack_long(__vpred, const __uchar*);
// int64_t __vload_pred_unpack_long(__vpred, const int16_t*);
// __ulong __vload_pred_unpack_long(__vpred, const __ushort*);
// int64_t __vload_pred_unpack_long(__vpred, const int32_t*);
// __ulong __vload_pred_unpack_long(__vpred, const __uint*);
template<typename ELEM_T,
         typename RES_T = typename std::conditional<std::is_signed<ELEM_T>::value,int64_t,uint64_t>::type,
         std::enable_if_t<std::numeric_limits<ELEM_T>::is_integer &&
                          sizeof(ELEM_T) < sizeof(int64_t) &&
                          !std::is_same<ELEM_T, char>::value, int> = 0>
RES_T __vload_pred_unpack_long(__vpred pred, const ELEM_T* input)
{
    if (check_pred_at_index(pred, 0, sizeof(ELEM_T)))
        return *input;
    return 0;
}

// int64_t __vload_unpack_long(const int8_t*);
// __ulong __vload_unpack_long(const __uchar*);
// int64_t __vload_unpack_long(const int16_t*);
// __ulong __vload_unpack_long(const __ushort*);
// int64_t __vload_unpack_long(const int32_t*);
// __ulong __vload_unpack_long(const __uint*);
template<typename ELEM_T,
         typename RES_T = typename std::conditional<std::is_signed<ELEM_T>::value,int64_t,uint64_t>::type,
         std::enable_if_t<std::numeric_limits<ELEM_T>::is_integer &&
                          sizeof(ELEM_T) < sizeof(int64_t) &&
                          !std::is_same<ELEM_T, char>::value, int> = 0>
RES_T __vload_unpack_long(const ELEM_T* input)
{
    return __vload_pred_unpack_long(__vpred(UINT64_MAX), input);
}

/*****************************************************************************
* VLOAD_DEINTERLEAVE_INT
*****************************************************************************/
// __int2 __vload_pred_deinterleave_int(__vpred, const __char4*);
// __int4 __vload_pred_deinterleave_int(__vpred, const __char8*);
// __int8 __vload_pred_deinterleave_int(__vpred, const __char16*);
// __int16 __vload_pred_deinterleave_int(__vpred, const __char32*);
// __int2 __vload_pred_deinterleave_int(__vpred, const __short4*);
// __int4 __vload_pred_deinterleave_int(__vpred, const __short8*);
// __int8 __vload_pred_deinterleave_int(__vpred, const __short16*);
// __int16 __vload_pred_deinterleave_int(__vpred, const __short32*);
// __uint2 __vload_pred_deinterleave_int(__vpred, const __uchar4*);
// __uint4 __vload_pred_deinterleave_int(__vpred, const __uchar8*);
// __uint8 __vload_pred_deinterleave_int(__vpred, const __uchar16*);
// __uint16 __vload_pred_deinterleave_int(__vpred, const __uchar32*);
// __uint2 __vload_pred_deinterleave_int(__vpred, const __ushort4*);
// __uint4 __vload_pred_deinterleave_int(__vpred, const __ushort8*);
// __uint8 __vload_pred_deinterleave_int(__vpred, const __ushort16*);
// __uint16 __vload_pred_deinterleave_int(__vpred, const __ushort32*);
template<typename ELEM_T,
         size_t NELEM,
         size_t RES_NELEM = NELEM/2,
         typename RES_ELEM_T = typename std::conditional<std::is_signed<ELEM_T>::value,int32_t,uint32_t>::type,
         typename RES_T = vtype<RES_ELEM_T, RES_NELEM, VTYPE_KIND::DATA>,
         std::enable_if_t<std::numeric_limits<ELEM_T>::is_integer &&
                          sizeof(ELEM_T) < sizeof(int32_t) &&
                          NELEM <= 32 &&
                          NELEM >= 4, int> = 0>
RES_T __vload_pred_deinterleave_int(__vpred pred,
                                    const vtype<ELEM_T, NELEM, VTYPE_KIND::DATA> *input)
{
    RES_T ret;
    memset(&ret, 0, sizeof(RES_T));

    for(size_t i = 0; i < RES_NELEM; i++)
        if (check_pred_at_index(pred, i*2, sizeof(ELEM_T)))
            ret.s[i] = (*input).s[i * 2];
    return ret;
}

// __int2 __vload_deinterleave_int(const __char4*);
// __int4 __vload_deinterleave_int(const __char8*);
// __int8 __vload_deinterleave_int(const __char16*);
// __int16 __vload_deinterleave_int(const __char32*);
// __int2 __vload_deinterleave_int(const __short4*);
// __int4 __vload_deinterleave_int(const __short8*);
// __int8 __vload_deinterleave_int(const __short16*);
// __int16 __vload_deinterleave_int(const __short32*);
// __uint2 __vload_deinterleave_int(const __uchar4*);
// __uint4 __vload_deinterleave_int(const __uchar8*);
// __uint8 __vload_deinterleave_int(const __uchar16*);
// __uint16 __vload_deinterleave_int(const __uchar32*);
// __uint2 __vload_deinterleave_int(const __ushort4*);
// __uint4 __vload_deinterleave_int(const __ushort8*);
// __uint8 __vload_deinterleave_int(const __ushort16*);
// __uint16 __vload_deinterleave_int(const __ushort32*);
template<typename ELEM_T,
         size_t NELEM,
         size_t RES_NELEM = NELEM/2,
         typename RES_ELEM_T = typename std::conditional<std::is_signed<ELEM_T>::value,int32_t,uint32_t>::type,
         typename RES_T = vtype<RES_ELEM_T, RES_NELEM, VTYPE_KIND::DATA>,
         std::enable_if_t<std::numeric_limits<ELEM_T>::is_integer &&
                          sizeof(ELEM_T) < sizeof(int32_t) &&
                          NELEM <= 32 &&
                          NELEM >= 4, int> = 0>
RES_T __vload_deinterleave_int(const vtype<ELEM_T, NELEM, VTYPE_KIND::DATA> *input)
{
    return __vload_pred_deinterleave_int(__vpred(UINT64_MAX), input);
}

// int32_t __vload_pred_deinterleave_int(__vpred, const __char2*);
// int32_t __vload_pred_deinterleave_int(__vpred, const __short2*);
// __uint __vload_pred_deinterleave_int(__vpred, const __uchar2*);
// __uint __vload_pred_deinterleave_int(__vpred, const __ushort2*);
template<typename ELEM_T,
         typename RES_T = typename std::conditional<std::is_signed<ELEM_T>::value,int32_t,uint32_t>::type,
         std::enable_if_t<std::numeric_limits<ELEM_T>::is_integer &&
                          sizeof(ELEM_T) < sizeof(int32_t), int> = 0>
RES_T __vload_pred_deinterleave_int(__vpred pred,
                                    const vtype<ELEM_T, 2, VTYPE_KIND::DATA> *input)
{
    if (check_pred_at_index(pred, 0, sizeof(ELEM_T)))
        return (*input).s[0];
    return 0;
}

// int32_t __vload_deinterleave_int(const __char2*);
// int32_t __vload_deinterleave_int(const __short2*);
// __uint __vload_deinterleave_int(const __uchar2*);
// __uint __vload_deinterleave_int(const __ushort2*);
template<typename ELEM_T,
         typename RES_T = typename std::conditional<std::is_signed<ELEM_T>::value,int32_t,uint32_t>::type,
         std::enable_if_t<std::numeric_limits<ELEM_T>::is_integer &&
                          sizeof(ELEM_T) < sizeof(int32_t), int> = 0>
RES_T __vload_deinterleave_int(const vtype<ELEM_T, 2, VTYPE_KIND::DATA> *input)
{
    return __vload_pred_deinterleave_int(__vpred(UINT64_MAX), input);
}

/*****************************************************************************
* VLOAD_DEINTERLEAVE_LONG
*****************************************************************************/
// __long2 __vload_pred_deinterleave_long(__vpred, const __char4*);
// __long4 __vload_pred_deinterleave_long(__vpred, const __char8*);
// __long8 __vload_pred_deinterleave_long(__vpred, const __char16*);
// __long2 __vload_pred_deinterleave_long(__vpred, const __short4*);
// __long4 __vload_pred_deinterleave_long(__vpred, const __short8*);
// __long8 __vload_pred_deinterleave_long(__vpred, const __short16*);
// __ulong2 __vload_pred_deinterleave_long(__vpred, const __uchar4*);
// __ulong4 __vload_pred_deinterleave_long(__vpred, const __uchar8*);
// __ulong8 __vload_pred_deinterleave_long(__vpred, const __uchar16*);
// __ulong2 __vload_pred_deinterleave_long(__vpred, const __ushort4*);
// __ulong4 __vload_pred_deinterleave_long(__vpred, const __ushort8*);
// __ulong8 __vload_pred_deinterleave_long(__vpred, const __ushort16*);
template<typename ELEM_T,
         size_t NELEM,
         size_t RES_NELEM = NELEM/2,
         typename RES_ELEM_T = typename std::conditional<std::is_signed<ELEM_T>::value,int64_t,uint64_t>::type,
         typename RES_T = vtype<RES_ELEM_T, RES_NELEM, VTYPE_KIND::DATA>,
         std::enable_if_t<std::numeric_limits<ELEM_T>::is_integer &&
                          sizeof(ELEM_T) < sizeof(int32_t) &&
                          NELEM <= 16 &&
                          NELEM >= 4, int> = 0>
RES_T __vload_pred_deinterleave_long(__vpred pred,
                                     const vtype<ELEM_T, NELEM, VTYPE_KIND::DATA> *input)
{
    RES_T ret;
    memset(&ret, 0, sizeof(RES_T));

    for(size_t i = 0; i < RES_NELEM; i++)
        if (check_pred_at_index(pred, i*2, sizeof(ELEM_T)))
            ret.s[i] = (*input).s[i * 2];
    return ret;
}

// __long2 __vload_deinterleave_long(const __char4*);
// __long4 __vload_deinterleave_long(const __char8*);
// __long8 __vload_deinterleave_long(const __char16*);
// __long2 __vload_deinterleave_long(const __short4*);
// __long4 __vload_deinterleave_long(const __short8*);
// __long8 __vload_deinterleave_long(const __short16*);
// __ulong2 __vload_deinterleave_long(const __uchar4*);
// __ulong4 __vload_deinterleave_long(const __uchar8*);
// __ulong8 __vload_deinterleave_long(const __uchar16*);
// __ulong2 __vload_deinterleave_long(const __ushort4*);
// __ulong4 __vload_deinterleave_long(const __ushort8*);
// __ulong8 __vload_deinterleave_long(const __ushort16*);
template<typename ELEM_T,
         size_t NELEM,
         size_t RES_NELEM = NELEM/2,
         typename RES_ELEM_T = typename std::conditional<std::is_signed<ELEM_T>::value,int64_t,uint64_t>::type,
         typename RES_T = vtype<RES_ELEM_T, RES_NELEM, VTYPE_KIND::DATA>,
         std::enable_if_t<std::numeric_limits<ELEM_T>::is_integer &&
                          sizeof(ELEM_T) < sizeof(int32_t) &&
                          NELEM <= 16 &&
                          NELEM >= 4, int> = 0>
RES_T __vload_deinterleave_long(const vtype<ELEM_T, NELEM, VTYPE_KIND::DATA> *input)
{
    return __vload_pred_deinterleave_long(__vpred(UINT64_MAX), input);
}

// int64_t __vload_pred_deinterleave_long(__vpred, const __char2*);
// int64_t __vload_pred_deinterleave_long(__vpred, const __short2*);
// __ulong __vload_pred_deinterleave_long(__vpred, const __uchar2*);
// __ulong __vload_pred_deinterleave_long(__vpred, const __ushort2*);
template<typename ELEM_T,
         typename RES_T = typename std::conditional<std::is_signed<ELEM_T>::value,int64_t,uint64_t>::type,
         std::enable_if_t<std::numeric_limits<ELEM_T>::is_integer &&
                          sizeof(ELEM_T) < sizeof(int32_t), int> = 0>
RES_T __vload_pred_deinterleave_long(__vpred pred,
                                     const vtype<ELEM_T, 2, VTYPE_KIND::DATA> *input)
{
    if (check_pred_at_index(pred, 0, sizeof(ELEM_T)))
        return (*input).s[0];
    return 0;
}

// int64_t __vload_deinterleave_long(const __char2*);
// int64_t __vload_deinterleave_long(const __short2*);
// __ulong __vload_deinterleave_long(const __uchar2*);
// __ulong __vload_deinterleave_long(const __ushort2*);
template<typename ELEM_T,
         typename RES_T = typename std::conditional<std::is_signed<ELEM_T>::value,int64_t,uint64_t>::type,
         std::enable_if_t<std::numeric_limits<ELEM_T>::is_integer &&
                          sizeof(ELEM_T) < sizeof(int32_t), int> = 0>
RES_T __vload_deinterleave_long(const vtype<ELEM_T, 2, VTYPE_KIND::DATA> *input)
{
    return __vload_pred_deinterleave_long(__vpred(UINT64_MAX), input);
}

/*****************************************************************************
* VSTORE_INTERLEAVE
******************************************************************************
* Template only enabled for full vectors.
*****************************************************************************/
template<typename ELEM_T,
         size_t NELEM,
         VTYPE_KIND KIND1,
         VTYPE_KIND KIND2,
         std::enable_if_t<!std::is_floating_point<ELEM_T>::value &&
                          (NELEM == __C7X_VEC_SIZE_BYTES__/sizeof(ELEM_T)), int> = 0>
void __vstore_interleave(vtype<ELEM_T, NELEM, VTYPE_KIND::DATA> *result,
                         const vtype<ELEM_T, NELEM, KIND1> &input1,
                         const vtype<ELEM_T, NELEM, KIND2> &input2)
{
    (*result).even() = input1.even();
    (*result).odd()  = input2.even();
}

#ifndef __C7100__
/*****************************************************************************
* VSTORE_INTERLEAVE_ODD
*****************************************************************************/
template<typename ELEM_T,
         size_t NELEM,
         VTYPE_KIND KIND1,
         VTYPE_KIND KIND2,
         std::enable_if_t<!std::is_floating_point<ELEM_T>::value &&
                          (NELEM == __C7X_VEC_SIZE_BYTES__/sizeof(ELEM_T)), int> = 0>
void __vstore_interleave_odd(vtype<ELEM_T, NELEM, VTYPE_KIND::DATA> *result,
                             const vtype<ELEM_T, NELEM, KIND1> &input1,
                             const vtype<ELEM_T, NELEM, KIND2> &input2)
{
    (*result).even() = input1.odd();
    (*result).odd()  = input2.odd();
}

/*****************************************************************************
* VSTORE_INTERLEAVE_LOW_LOW - The full vector form where the source vectors
* input1, input2 have the same number of elements as result. The low halves
* of input1 and input2 are stored in the result.
*****************************************************************************/
template<typename ELEM_T,
         size_t NELEM,
         VTYPE_KIND KIND1,
         VTYPE_KIND KIND2,
         std::enable_if_t<!std::is_floating_point<ELEM_T>::value &&
                          (NELEM == __C7X_VEC_SIZE_BYTES__/sizeof(ELEM_T)), int> = 0>
void __vstore_interleave_low_low(vtype<ELEM_T, NELEM, VTYPE_KIND::DATA> *result,
                                 const vtype<ELEM_T, NELEM, KIND1> &input1,
                                 const vtype<ELEM_T, NELEM, KIND2> &input2)
{
    (*result).even() = input1.lo();
    (*result).odd()  = input2.lo();
}

/*****************************************************************************
* VSTORE_INTERLEAVE_LOW_LOW - The half vector form where the source vectors
* input1, input2 have half the number of elements as the result.
*****************************************************************************/
template<typename ELEM_T,
         size_t NELEM,
         VTYPE_KIND KIND1,
         VTYPE_KIND KIND2,
         std::enable_if_t<!std::is_floating_point<ELEM_T>::value &&
                          (NELEM == __C7X_VEC_SIZE_BYTES__/sizeof(ELEM_T)), int> = 0>
void __vstore_interleave_low_low(vtype<ELEM_T, NELEM, VTYPE_KIND::DATA> *result,
                                 const vtype<ELEM_T, NELEM/2, KIND1> &input1,
                                 const vtype<ELEM_T, NELEM/2, KIND2> &input2)
{
    (*result).even() = input1;
    (*result).odd()  = input2;
}

/*****************************************************************************
* VSTORE_INTERLEAVE_LOW_LOW - The half vector form where input1 and input2 are
* scalars. This implementation is currently used by the API
* __vstore_interleave_low_low(long2, long, long).
*****************************************************************************/
template<typename ELEM_T,
         std::enable_if_t<!std::is_floating_point<ELEM_T>::value, int> = 0>
void __vstore_interleave_low_low(vtype<ELEM_T, 2, VTYPE_KIND::DATA> *result,
                                 ELEM_T input1,
                                 ELEM_T input2)
{
    (*result).even() = input1;
    (*result).odd()  = input2;
}

/*****************************************************************************
* VSTORE_INTERLEAVE_HIGH_HIGH - Stores high vector halves.
*****************************************************************************/
template<typename ELEM_T,
         size_t NELEM,
         VTYPE_KIND KIND1,
         VTYPE_KIND KIND2,
         std::enable_if_t<!std::is_floating_point<ELEM_T>::value &&
                          (NELEM == __C7X_VEC_SIZE_BYTES__/sizeof(ELEM_T)), int> = 0>
void __vstore_interleave_high_high(vtype<ELEM_T, NELEM, VTYPE_KIND::DATA> *result,
                                   const vtype<ELEM_T, NELEM, KIND1> &input1,
                                   const vtype<ELEM_T, NELEM, KIND2> &input2)
{
    (*result).even() = input1.hi();
    (*result).odd()  = input2.hi();
}
#endif /* ! __C7100__ */


/*****************************************************************************
* Store every fourth element. Enabled if result vector is 32 characters and
* both inputs are 64 characters long. Also only enabled if the element type
* is of size 8 bits sizeof(int8_t) -> applies to unsigned and signed char
****************************************************************************/
template<typename ELEM_T,
         size_t NELEM,
         VTYPE_KIND KIND1,
         VTYPE_KIND KIND2,
         std::enable_if_t<NELEM == __C7X_VEC_SIZE_BYTES__/sizeof(int8_t) &&
                          sizeof(ELEM_T) == sizeof(int8_t), int> = 0>
void __vstore_interleave4(vtype<ELEM_T, NELEM/2, VTYPE_KIND::DATA> *result,
                          const vtype<ELEM_T, NELEM, KIND1> &input1,
                          const vtype<ELEM_T, NELEM, KIND2> &input2)
{
    (*result).even() = input1.even().even();
    (*result).odd()  = input2.even().even();
}

/*****************************************************************************
* VSTORE_PRED_INTERLEAVE
*****************************************************************************/
template<typename ELEM_T,
         size_t NELEM,
         VTYPE_KIND KIND1,
         VTYPE_KIND KIND2,
         std::enable_if_t<!std::is_floating_point<ELEM_T>::value &&
                          (NELEM == __C7X_VEC_SIZE_BYTES__/sizeof(ELEM_T)), int> = 0>
void __vstore_pred_interleave(__vpred pred,
                              vtype<ELEM_T, NELEM, VTYPE_KIND::DATA> *result,
                              const vtype<ELEM_T, NELEM, KIND1> &input1,
                              const vtype<ELEM_T, NELEM, KIND2> &input2)
{
    // Even part
    for (size_t i = 0; i < NELEM; i+=2)
        if (check_pred_at_index(pred, i, sizeof(ELEM_T)))
            (*result).s[i] = input1.s[i];

    // Odd part
    for (size_t i = 0; i < NELEM; i+=2)
        if (check_pred_at_index(pred, i+1, sizeof(ELEM_T)))
            (*result).s[i+1] = input2.s[i];
}

#ifndef __C7100__
/*****************************************************************************
* VSTORE_PRED_INTERLEAVE_ODD
*****************************************************************************/
template<typename ELEM_T,
         size_t NELEM,
         VTYPE_KIND KIND1,
         VTYPE_KIND KIND2,
         std::enable_if_t<!std::is_floating_point<ELEM_T>::value &&
                          (NELEM == __C7X_VEC_SIZE_BYTES__/sizeof(ELEM_T)), int> = 0>
void __vstore_pred_interleave_odd(__vpred pred,
                                  vtype<ELEM_T, NELEM, VTYPE_KIND::DATA> *result,
                                  const vtype<ELEM_T, NELEM, KIND1> &input1,
                                  const vtype<ELEM_T, NELEM, KIND2> &input2)
{
    // Even part
    for (size_t i = 0; i < NELEM; i+=2)
        if (check_pred_at_index(pred, i, sizeof(ELEM_T)))
            (*result).s[i] = input1.s[i+1];

    // Odd part
    for (size_t i = 0; i < NELEM; i+=2)
        if (check_pred_at_index(pred, i+1, sizeof(ELEM_T)))
            (*result).s[i+1] = input2.s[i+1];
}

/*****************************************************************************
* VSTORE_PRED_INTERLEAVE_LOW_LOW - The full vector form where source vectors
* input1 and input2 have the same number of elements as result. The low halves
* of input1 and input2 are stored in result.
*****************************************************************************/
template<typename ELEM_T,
         size_t NELEM,
         VTYPE_KIND KIND1,
         VTYPE_KIND KIND2,
         std::enable_if_t<!std::is_floating_point<ELEM_T>::value &&
                          (NELEM == __C7X_VEC_SIZE_BYTES__/sizeof(ELEM_T)), int> = 0>
void __vstore_pred_interleave_low_low(__vpred pred,
                                      vtype<ELEM_T, NELEM, VTYPE_KIND::DATA> *result,
                                      const vtype<ELEM_T, NELEM, KIND1> &input1,
                                      const vtype<ELEM_T, NELEM, KIND2> &input2)
{
    // Even part
    for (size_t i = 0; i < NELEM; i+=2)
        if (check_pred_at_index(pred, i, sizeof(ELEM_T)))
            (*result).s[i] = input1.s[i/2];

    // Odd part
    for (size_t i = 0; i < NELEM; i+=2)
        if (check_pred_at_index(pred, i+1, sizeof(ELEM_T)))
            (*result).s[i+1] = input2.s[i/2];
}

/*****************************************************************************
* VSTORE_PRED_INTERLEAVE_LOW_LOW - The half vector form where source vectors
* input1 and input2 have half the number of elements as result.
*****************************************************************************/
template<typename ELEM_T,
         size_t NELEM,
         VTYPE_KIND KIND1,
         VTYPE_KIND KIND2,
         std::enable_if_t<!std::is_floating_point<ELEM_T>::value &&
                          (NELEM == __C7X_VEC_SIZE_BYTES__/sizeof(ELEM_T)), int> = 0>
void __vstore_pred_interleave_low_low(__vpred pred,
                                      vtype<ELEM_T, NELEM, VTYPE_KIND::DATA> *result,
                                      const vtype<ELEM_T, NELEM/2, KIND1> &input1,
                                      const vtype<ELEM_T, NELEM/2, KIND2> &input2)
{
    // Even part
    for (size_t i = 0; i < NELEM; i+=2)
        if (check_pred_at_index(pred, i, sizeof(ELEM_T)))
            (*result).s[i] = input1.s[i/2];

    // Odd part
    for (size_t i = 0; i < NELEM; i+=2)
        if (check_pred_at_index(pred, i+1, sizeof(ELEM_T)))
            (*result).s[i+1] = input2.s[i/2];
}

/*****************************************************************************
* VSTORE_PRED_INTERLEAVE_LOW_LOW - The half vector form where input1 and input2
* are scalars. This implementation is currently used by the API
* __vstore_pred_interleave_low_low(__vpred, long2*, long, long).
*****************************************************************************/
template<typename ELEM_T,
         size_t NELEM,
         std::enable_if_t<NELEM == 2, int> = 0,
         std::enable_if_t<!std::is_floating_point<ELEM_T>::value &&
                          (NELEM == __C7X_VEC_SIZE_BYTES__/sizeof(ELEM_T)), int> = 0>
void __vstore_pred_interleave_low_low(__vpred pred,
                                      vtype<ELEM_T, NELEM, VTYPE_KIND::DATA> *result,
                                      ELEM_T input1,
                                      ELEM_T input2)
{
    // Even part
    for (size_t i = 0; i < NELEM; i+=2)
        if (check_pred_at_index(pred, i, sizeof(ELEM_T)))
            (*result).s[i] = input1;

    // Odd part
    for (size_t i = 0; i < NELEM; i+=2)
        if (check_pred_at_index(pred, i+1, sizeof(ELEM_T)))
            (*result).s[i+1] = input2;
}

/*****************************************************************************
* VSTORE_PRED_INTERLEAVE_HIGH_HIGH
*****************************************************************************/
template<typename ELEM_T,
         size_t NELEM,
         VTYPE_KIND KIND1,
         VTYPE_KIND KIND2,
         std::enable_if_t<!std::is_floating_point<ELEM_T>::value &&
                          (NELEM == __C7X_VEC_SIZE_BYTES__/sizeof(ELEM_T)), int> = 0>
void __vstore_pred_interleave_high_high(__vpred pred,
                                        vtype<ELEM_T, NELEM, VTYPE_KIND::DATA> *result,
                                        const vtype<ELEM_T, NELEM, KIND1> &input1,
                                        const vtype<ELEM_T, NELEM, KIND2> &input2)
{
    // Even part
    for (size_t i = 0; i < NELEM; i+=2)
        if (check_pred_at_index(pred, i, sizeof(ELEM_T)))
            (*result).s[i] = input1.s[(NELEM+i)/2];

    // Odd part
    for (size_t i = 0; i < NELEM; i+=2)
        if (check_pred_at_index(pred, i+1, sizeof(ELEM_T)))
            (*result).s[i+1] = input2.s[(NELEM+i)/2];
}
#endif /* ! __C7100__ */

/*****************************************************************************
* Store every fourth element based on pred. Enabled if result vector is 32
* characters and both inputs are 64 characters long. Also only enabled if the
* element type is of size 8 bits sizeof(int8_t) -> applies to unsigned
* and signed char
*****************************************************************************/
template<typename ELEM_T,
         size_t NELEM,
         VTYPE_KIND KIND1,
         VTYPE_KIND KIND2,
         std::enable_if_t<NELEM == __C7X_VEC_SIZE_BYTES__/sizeof(int8_t) &&
                          sizeof(ELEM_T) == sizeof(int8_t), int> = 0>
void __vstore_pred_interleave4(__vpred pred,
                               vtype<ELEM_T, NELEM/2, VTYPE_KIND::DATA> *result,
                               const vtype<ELEM_T, NELEM, KIND1> &input1,
                               const vtype<ELEM_T, NELEM, KIND2> &input2)
{
    for (size_t i = 0; i < NELEM; i+=4)
        if (check_pred_at_index(pred, (i/2), sizeof(ELEM_T)))
            (*result).s[i/2] = input1.s[i];

    for (size_t i = 0; i < NELEM; i+=4)
        if (check_pred_at_index(pred, (i/2) + 1, sizeof(ELEM_T)))
            (*result).s[(i/2) + 1] = input2.s[i];
}

/*****************************************************************************
* VSTORE_PRED
*****************************************************************************/

template<typename ELEM_T,
         size_t NELEM,
         VTYPE_KIND KIND>
void __vstore_pred(__vpred pred,
                   vtype<ELEM_T, NELEM, VTYPE_KIND::DATA> *result,
                   const vtype<ELEM_T, NELEM, KIND> &input)
{
    for(size_t i = 0; i < NELEM; i++)
        if (check_pred_at_index(pred, i, sizeof(ELEM_T)))
            (*result).s[i] = input.s[i];
}

// From 8bit to 64bit template overloads for the scalar __vstore_pred.
template<typename ELEM_T,
         // This enable_if keeps the complex type overload from conflicting
         // with this overload. Without this we get template resolution
         // ambiguity from the BST macro.
         std::enable_if_t<std::is_arithmetic<ELEM_T>::value, int> = 0>
void __vstore_pred(__vpred pred, ELEM_T *result, ELEM_T input)
{
    if (check_pred_at_index(pred, 0, sizeof(ELEM_T)))
      *result = input;
}

template<typename ELEM_T,
         size_t NELEM,
         VTYPE_KIND KIND>
void __vstore_pred(__vpred pred,
                   vtype<ctype<ELEM_T>, NELEM, VTYPE_KIND::DATA> *result,
                   const vtype<ctype<ELEM_T>, NELEM, KIND> &input)
{
    for(size_t i = 0; i < NELEM * 2; i++)
    {
        if (check_pred_at_index(pred, i, sizeof(ELEM_T)))
        {
            if (i % 2 == 0)
                (*result).s[i/2].r() = input.s[i/2].r();
            else
                (*result).s[i/2].i() = input.s[i/2].i();
        }
    }
}

template<typename ELEM_T>
void __vstore_pred(__vpred pred,
                   ctype<ELEM_T> *result,
                   const ctype<ELEM_T> &input)
{
    if (check_pred_at_index(pred, 0, sizeof(ELEM_T)))
        (*result).r() = input.r();
    if (check_pred_at_index(pred, 1, sizeof(ELEM_T)))
        (*result).i() = input.i();
}

/*****************************************************************************
* VSTORE_PRED_PACKL
*****************************************************************************/

/*****************************************************************************
* Limits:
* No floating, size of result element = half size of input element,
* full vectors only, no floating points, element size of input at least short
*****************************************************************************/
template<typename ELEM_T,
         typename ELEM_T_RES,
         size_t NELEM,
         VTYPE_KIND KIND,
         std::enable_if_t<!std::is_floating_point<ELEM_T>::value &&
                          !std::is_floating_point<ELEM_T_RES>::value &&
                          std::is_signed<ELEM_T>::value == std::is_signed<ELEM_T_RES>::value &&
                          std::is_unsigned<ELEM_T>::value == std::is_unsigned<ELEM_T_RES>::value &&
                          NELEM == __C7X_VEC_SIZE_BYTES__/sizeof(ELEM_T) &&
                          sizeof(ELEM_T) >= sizeof(int16_t) &&
                          sizeof(ELEM_T) == sizeof(ELEM_T_RES)*2, int> = 0>
void __vstore_pred_packl(__vpred pred,
                         vtype<ELEM_T_RES, NELEM, VTYPE_KIND::DATA> *result,
                         const vtype<ELEM_T, NELEM, KIND> &input)
{
    for(size_t i = 0; i < NELEM; i++)
        if (check_pred_at_index(pred, i, sizeof(ELEM_T)))
            (*result).s[i] = (ELEM_T_RES)(input.s[i]); // Grabs low half
}



/*****************************************************************************
* VSTORE_PRED_PACKL_2SRC
*****************************************************************************/
template<typename ELEM_T,
         typename ELEM_T_RES,
         size_t NELEM,
         VTYPE_KIND KIND1,
         VTYPE_KIND KIND2,
         std::enable_if_t<!std::is_floating_point<ELEM_T>::value &&
                          !std::is_floating_point<ELEM_T_RES>::value &&
                          std::is_signed<ELEM_T>::value == std::is_signed<ELEM_T_RES>::value &&
                          std::is_unsigned<ELEM_T>::value == std::is_unsigned<ELEM_T_RES>::value &&
                          NELEM == __C7X_VEC_SIZE_BYTES__/sizeof(ELEM_T) &&
                          sizeof(ELEM_T) >= sizeof(int16_t) &&
                          sizeof(ELEM_T) == sizeof(ELEM_T_RES)*2, int> = 0>
void __vstore_pred_packl_2src(__vpred pred,
                              vtype<ELEM_T_RES, NELEM*2, VTYPE_KIND::DATA> *result,
                              const vtype<ELEM_T, NELEM, KIND1> &input1,
                              const vtype<ELEM_T, NELEM, KIND2> &input2)
{
    // Loop num_input1/2 times
    for(size_t i = 0; i < NELEM; i++)
    {
        if (check_pred_at_index(pred, i, sizeof(ELEM_T_RES)))
            (*result).s[i] = (ELEM_T_RES)(input1.s[i]); // Grabs low half
        if (check_pred_at_index(pred, i + NELEM, sizeof(ELEM_T_RES)))
            (*result).s[i + NELEM] = (ELEM_T_RES)(input2.s[i]); // Grabs low half
    }
}


/*****************************************************************************
* VSTORE_PRED_PACKH
*****************************************************************************/
template<typename ELEM_T,
         typename ELEM_T_RES,
         size_t NELEM,
         VTYPE_KIND KIND,
         std::enable_if_t<!std::is_floating_point<ELEM_T>::value &&
                          !std::is_floating_point<ELEM_T_RES>::value &&
                          std::is_signed<ELEM_T>::value == std::is_signed<ELEM_T_RES>::value &&
                          std::is_unsigned<ELEM_T>::value == std::is_unsigned<ELEM_T_RES>::value &&
                          NELEM == __C7X_VEC_SIZE_BYTES__/sizeof(ELEM_T) &&
                          sizeof(ELEM_T) >= sizeof(int16_t) &&
                          sizeof(ELEM_T) == sizeof(ELEM_T_RES)*2, int> = 0>
void __vstore_pred_packh(__vpred pred,
                         vtype<ELEM_T_RES, NELEM, VTYPE_KIND::DATA> *result,
                         const vtype<ELEM_T, NELEM, KIND> &input)
{
    for(size_t i = 0; i < NELEM; i++)
        if (check_pred_at_index(pred, i, sizeof(ELEM_T)))
            (*result).s[i] = (input.s[i]) >> (sizeof(ELEM_T_RES)*8); // Grabs high half
}

/*****************************************************************************
* VSTORE_PRED_PACKH_2SRC
*****************************************************************************/
template<typename ELEM_T,
         typename ELEM_T_RES,
         size_t NELEM,
         VTYPE_KIND KIND1,
         VTYPE_KIND KIND2,
         std::enable_if_t<!std::is_floating_point<ELEM_T>::value &&
                          !std::is_floating_point<ELEM_T_RES>::value &&
                          std::is_signed<ELEM_T>::value == std::is_signed<ELEM_T_RES>::value &&
                          std::is_unsigned<ELEM_T>::value == std::is_unsigned<ELEM_T_RES>::value &&
                          NELEM == __C7X_VEC_SIZE_BYTES__/sizeof(ELEM_T) &&
                          sizeof(ELEM_T) >= sizeof(int16_t) &&
                          sizeof(ELEM_T) == sizeof(ELEM_T_RES)*2, int> = 0>
void __vstore_pred_packh_2src(__vpred pred,
                              vtype<ELEM_T_RES, NELEM*2, VTYPE_KIND::DATA> *result,
                              const vtype<ELEM_T, NELEM, KIND1> &input1,
                              const vtype<ELEM_T, NELEM, KIND2> &input2)
{
    for(size_t i = 0; i < NELEM; i++)
    {
        if (check_pred_at_index(pred, i, sizeof(ELEM_T_RES)))
            (*result).s[i] = (input1.s[i]) >> (sizeof(ELEM_T_RES)*8); // Grabs high half
        if (check_pred_at_index(pred, i + NELEM, sizeof(ELEM_T_RES)))
            (*result).s[i + NELEM] = (input2.s[i]) >> (sizeof(ELEM_T_RES)*8); // Grabs high half
    }
}

/*****************************************************************************
* VSTORE_PRED_PACKHS1
*****************************************************************************/
template<typename ELEM_T,
         typename ELEM_T_RES,
         size_t NELEM,
         VTYPE_KIND KIND,
         std::enable_if_t<!std::is_floating_point<ELEM_T>::value &&
                          !std::is_floating_point<ELEM_T_RES>::value &&
                          std::is_signed<ELEM_T>::value == std::is_signed<ELEM_T_RES>::value &&
                          std::is_unsigned<ELEM_T>::value == std::is_unsigned<ELEM_T_RES>::value &&
                          NELEM == __C7X_VEC_SIZE_BYTES__/sizeof(ELEM_T) &&
                          sizeof(ELEM_T) >= sizeof(int16_t) &&
                          sizeof(ELEM_T) == sizeof(ELEM_T_RES)*2, int> = 0>
void __vstore_pred_packhs1(__vpred pred,
                           vtype<ELEM_T_RES, NELEM, VTYPE_KIND::DATA> *result,
                           const vtype<ELEM_T, NELEM, KIND> &input)
{
    for(size_t i = 0; i < NELEM; i++)
    {
        if (check_pred_at_index(pred, i, sizeof(ELEM_T)))
        {
            ELEM_T val = input.s[i] << (ELEM_T)1;
            (*result).s[i] = (val) >> (sizeof(ELEM_T_RES)*8); // Grabs high half
        }
    }
}

/*****************************************************************************
* VSTORE_PRED_PACKHS1_2SRC
*****************************************************************************/
template<typename ELEM_T,
         typename ELEM_T_RES,
         size_t NELEM,
         VTYPE_KIND KIND1,
         VTYPE_KIND KIND2,
         std::enable_if_t<!std::is_floating_point<ELEM_T>::value &&
                          !std::is_floating_point<ELEM_T_RES>::value &&
                          std::is_signed<ELEM_T>::value == std::is_signed<ELEM_T_RES>::value &&
                          std::is_unsigned<ELEM_T>::value == std::is_unsigned<ELEM_T_RES>::value &&
                          NELEM == __C7X_VEC_SIZE_BYTES__/sizeof(ELEM_T) &&
                          sizeof(ELEM_T) >= sizeof(int16_t) &&
                          sizeof(ELEM_T) == sizeof(ELEM_T_RES)*2, int> = 0>
void __vstore_pred_packhs1_2src(__vpred pred,
                                vtype<ELEM_T_RES, NELEM*2, VTYPE_KIND::DATA> *result,
                                const vtype<ELEM_T, NELEM, KIND1> &input1,
                                const vtype<ELEM_T, NELEM, KIND2> &input2)
{
    for(size_t i = 0; i < NELEM; i++)
    {
        if (check_pred_at_index(pred, i, sizeof(ELEM_T_RES)))
        {
            ELEM_T val = input1.s[i] << (ELEM_T)1;
            (*result).s[i] = (val) >> (sizeof(ELEM_T_RES)*8); // Grabs high half
        }
        if (check_pred_at_index(pred, i + NELEM, sizeof(ELEM_T_RES)))
        {
            ELEM_T val = input2.s[i] << (ELEM_T)1;
            (*result).s[i + NELEM] = (val) >> (sizeof(ELEM_T_RES)*8); // Grabs high half
        }
    }
}

/*****************************************************************************
* Helper function used with bit reverse intrinsics
*****************************************************************************/
uint32_t reverse_bits(uint32_t index, uint32_t num_of_bits);

/*****************************************************************************
* VSTORE_PRED_REVERSE_BIT
*****************************************************************************/

/*****************************************************************************
* Limits: At least short, full vector
*****************************************************************************/
template<typename ELEM_T,
         size_t NELEM,
         VTYPE_KIND KIND,
         std::enable_if_t<NELEM == __C7X_VEC_SIZE_BYTES__/(sizeof(ELEM_T) * 2) &&
                          sizeof(ELEM_T) >= sizeof(int16_t) &&
                          sizeof(ELEM_T) < sizeof(int64_t), int> = 0>
void __vstore_pred_reverse_bit(__vpred pred,
                               vtype<ctype<ELEM_T>, NELEM, VTYPE_KIND::DATA> *result,
                               const vtype<ctype<ELEM_T>, NELEM, KIND> &input)
{
    uint32_t num_of_bits = (uint32_t)std::log2(NELEM * 2);

    for (size_t i = 0; i < NELEM; i++)
    {
        size_t src_pos = reverse_bits((uint32_t)i*2, num_of_bits);
        if (check_pred_at_index(pred, i*2, sizeof(ELEM_T)))
            (*result).s[i].r() = input.s[src_pos].r();
        if (check_pred_at_index(pred, (i*2)+1, sizeof(ELEM_T)))
            (*result).s[i].i() = input.s[src_pos].i();
    }
}

/*****************************************************************************
* VSTORE_REVERSE_BIT
*****************************************************************************/

/*****************************************************************************
* Limits: At least short, full vector
*****************************************************************************/
template<typename ELEM_T,
         size_t NELEM,
         VTYPE_KIND KIND,
         std::enable_if_t<NELEM == __C7X_VEC_SIZE_BYTES__/sizeof(ELEM_T) &&
                          sizeof(ELEM_T) >= sizeof(int16_t), int> = 0>
void __vstore_reverse_bit(vtype<ELEM_T, NELEM, VTYPE_KIND::DATA> *result,
                          const vtype<ELEM_T, NELEM, KIND> &input)
{
    uint32_t num_of_bits = (uint32_t)std::log2(NELEM);

    for (size_t i = 0; i < NELEM; i += 2)
    {
        size_t src_pos = reverse_bits((uint32_t)i, num_of_bits) * 2;
        (*result).s[i] =   input.s[src_pos];
        (*result).s[i+1] = input.s[src_pos+1];
    }
}

template<typename ELEM_T,
         size_t NELEM,
         VTYPE_KIND KIND,
         std::enable_if_t<NELEM == __C7X_VEC_SIZE_BYTES__/(sizeof(ELEM_T) * 2) &&
                          sizeof(ELEM_T) >= sizeof(int16_t) &&
                          sizeof(ELEM_T) < sizeof(int64_t), int> = 0>
void __vstore_reverse_bit(vtype<ctype<ELEM_T>, NELEM, VTYPE_KIND::DATA> *result,
                          const vtype<ctype<ELEM_T>, NELEM, KIND> &input)
{
    uint32_t num_of_bits = (uint32_t)std::log2(NELEM * 2);

    for (size_t i = 0; i < NELEM; i++)
    {
        size_t src_pos = reverse_bits((uint32_t)i*2, num_of_bits);
        (*result).s[i] = input.s[src_pos];
    }
}

/*****************************************************************************
* MULTI_WORD
*****************************************************************************/
template<size_t NELEM>
void __vstore_const_multi_word(vtype<uint32_t, NELEM, VTYPE_KIND::DATA> *result,
                               int32_t input)
{
    assert(((input >= 0) && (input <= 0x7fffffff)) && "Input constant out of range");
    *result = vtype<uint32_t, NELEM, VTYPE_KIND::DATA>(input);;
}

/*****************************************************************************
* VSTORE_PACKL
*****************************************************************************/

/*****************************************************************************
* Limits:
* No floating, size of result element = half size of input element,
* full vectors only, no floating points, element size of input at least short
*****************************************************************************/
template<typename ELEM_T,
         typename ELEM_T_RES,
         size_t NELEM,
         VTYPE_KIND KIND,
         std::enable_if_t<!std::is_floating_point<ELEM_T>::value &&
                          !std::is_floating_point<ELEM_T_RES>::value &&
                          std::is_signed<ELEM_T>::value == std::is_signed<ELEM_T_RES>::value &&
                          std::is_unsigned<ELEM_T>::value == std::is_unsigned<ELEM_T_RES>::value &&
                          NELEM == __C7X_VEC_SIZE_BYTES__/sizeof(ELEM_T) &&
                          sizeof(ELEM_T) >= sizeof(int16_t) &&
                          sizeof(ELEM_T) == sizeof(ELEM_T_RES)*2, int> = 0>
void __vstore_packl(vtype<ELEM_T_RES, NELEM, VTYPE_KIND::DATA> *result,
                    const vtype<ELEM_T, NELEM, KIND> &input)
{
    for(size_t i = 0; i < NELEM; i++)
        (*result).s[i] = (ELEM_T_RES)(input.s[i]); // Grabs low half
}

template<typename ELEM_T,
         size_t NELEM,
         VTYPE_KIND KIND,
         std::enable_if_t<!std::is_floating_point<ELEM_T>::value &&
                          NELEM == __C7X_VEC_SIZE_BYTES__/sizeof(ELEM_T) &&
                          sizeof(ELEM_T) == sizeof(int64_t), int> = 0>
void __vstore_packl(vtype<ELEM_T, NELEM/2, VTYPE_KIND::DATA> *result,
                    const vtype<ELEM_T, NELEM, KIND> &input)
{
    for(size_t i = 0; i < NELEM; i += 2)
        (*result).s[i/2] = (input.s[i]);
}


/*****************************************************************************
* VSTORE_PACKL_2SRC
*****************************************************************************/

/*****************************************************************************
* Limits:
* No floating, size of result element = half size of input element,
* full vectors only, no floating points, element size of input at least short
*****************************************************************************/
template<typename ELEM_T,
         typename ELEM_T_RES,
         size_t NELEM,
         VTYPE_KIND KIND1,
         VTYPE_KIND KIND2,
         std::enable_if_t<!std::is_floating_point<ELEM_T>::value &&
                          !std::is_floating_point<ELEM_T_RES>::value &&
                          std::is_signed<ELEM_T>::value == std::is_signed<ELEM_T_RES>::value &&
                          std::is_unsigned<ELEM_T>::value == std::is_unsigned<ELEM_T_RES>::value &&
                          NELEM == __C7X_VEC_SIZE_BYTES__/sizeof(ELEM_T) &&
                          sizeof(ELEM_T) >= sizeof(int16_t) &&
                          sizeof(ELEM_T) == sizeof(ELEM_T_RES)*2, int> = 0>
void __vstore_packl_2src(vtype<ELEM_T_RES, NELEM * 2, VTYPE_KIND::DATA> *result,
                         const vtype<ELEM_T, NELEM, KIND1> &input1,
                         const vtype<ELEM_T, NELEM, KIND2> &input2)
{
    for(size_t i = 0; i < NELEM; i++)
    {
        (*result).s[i] = (ELEM_T_RES)(input1.s[i]); // Grabs low half
        (*result).s[i + NELEM] = (ELEM_T_RES)(input2.s[i]); // Grabs low half
    }
}

template<typename ELEM_T,
         size_t NELEM,
         VTYPE_KIND KIND1,
         VTYPE_KIND KIND2,
         std::enable_if_t<!std::is_floating_point<ELEM_T>::value &&
                          NELEM == __C7X_VEC_SIZE_BYTES__/sizeof(ELEM_T) &&
                          sizeof(ELEM_T) == sizeof(int64_t), int> = 0>
void __vstore_packl_2src(vtype<ELEM_T, NELEM, VTYPE_KIND::DATA> *result,
                         const vtype<ELEM_T, NELEM, KIND1> &input1,
                         const vtype<ELEM_T, NELEM, KIND2> &input2)
{
    for (size_t i = 0; i < NELEM; i += 2)
    {
        (*result).s[i/2] = input1.s[i];
        (*result).s[(i + NELEM)/2] = input2.s[i];
    }
}


/*****************************************************************************
* VSTORE_PACKH
*****************************************************************************/
template<typename ELEM_T,
         typename ELEM_T_RES,
         size_t NELEM,
         VTYPE_KIND KIND,
         std::enable_if_t<!std::is_floating_point<ELEM_T>::value &&
                          !std::is_floating_point<ELEM_T_RES>::value &&
                          std::is_signed<ELEM_T>::value == std::is_signed<ELEM_T_RES>::value &&
                          std::is_unsigned<ELEM_T>::value == std::is_unsigned<ELEM_T_RES>::value &&
                          NELEM == __C7X_VEC_SIZE_BYTES__/sizeof(ELEM_T) &&
                          sizeof(ELEM_T) >= sizeof(int16_t) &&
                          sizeof(ELEM_T) == sizeof(ELEM_T_RES)*2, int> = 0>
void __vstore_packh(vtype<ELEM_T_RES, NELEM, VTYPE_KIND::DATA> *result,
                    const vtype<ELEM_T, NELEM, KIND> &input)
{
    for(size_t i = 0; i < NELEM; i++)
        (*result).s[i] = (input.s[i]) >> (sizeof(ELEM_T_RES)*8); // Grabs high half
}

template<typename ELEM_T,
         size_t NELEM,
         VTYPE_KIND KIND,
         std::enable_if_t<!std::is_floating_point<ELEM_T>::value &&
                          NELEM == __C7X_VEC_SIZE_BYTES__/sizeof(ELEM_T) &&
                          sizeof(ELEM_T) == sizeof(int64_t), int> = 0>
void __vstore_packh(vtype<ELEM_T, NELEM/2, VTYPE_KIND::DATA> *result,
                    const vtype<ELEM_T, NELEM, KIND> &input)
{
    for(size_t i = 0; i < NELEM; i += 2)
        (*result).s[i/2] = (input.s[i+1]);
}


/*****************************************************************************
* VSTORE_PACKH_2SRC
*****************************************************************************/
template<typename ELEM_T,
         typename ELEM_T_RES,
         size_t NELEM,
         VTYPE_KIND KIND1,
         VTYPE_KIND KIND2,
         std::enable_if_t<!std::is_floating_point<ELEM_T>::value &&
                          !std::is_floating_point<ELEM_T_RES>::value &&
                          std::is_signed<ELEM_T>::value == std::is_signed<ELEM_T_RES>::value &&
                          std::is_unsigned<ELEM_T>::value == std::is_unsigned<ELEM_T_RES>::value &&
                          NELEM == __C7X_VEC_SIZE_BYTES__/sizeof(ELEM_T) &&
                          sizeof(ELEM_T) >= sizeof(int16_t) &&
                          sizeof(ELEM_T) == sizeof(ELEM_T_RES)*2, int> = 0>
void __vstore_packh_2src(vtype<ELEM_T_RES, NELEM * 2, VTYPE_KIND::DATA> *result,
                         const vtype<ELEM_T, NELEM, KIND1> &input1,
                         const vtype<ELEM_T, NELEM, KIND2> &input2)
{
    for(size_t i = 0; i < NELEM; i++)
    {
        (*result).s[i] = (input1.s[i]) >> (sizeof(ELEM_T_RES)*8); // Grabs high half
        (*result).s[i + NELEM] = (input2.s[i]) >> (sizeof(ELEM_T_RES)*8); // Grabs high half
    }
}

template<typename ELEM_T,
         size_t NELEM,
         VTYPE_KIND KIND1,
         VTYPE_KIND KIND2,
         std::enable_if_t<!std::is_floating_point<ELEM_T>::value &&
                          NELEM == __C7X_VEC_SIZE_BYTES__/sizeof(ELEM_T) &&
                          sizeof(ELEM_T) == sizeof(int64_t), int> = 0>
void __vstore_packh_2src(vtype<ELEM_T, NELEM, VTYPE_KIND::DATA> *result,
                         const vtype<ELEM_T, NELEM, KIND1> &input1,
                         const vtype<ELEM_T, NELEM, KIND2> &input2)
{
    for (size_t i = 0; i < NELEM; i += 2)
    {
        (*result).s[i/2] = input1.s[i+1];
        (*result).s[(i + NELEM)/2] = input2.s[i+1];
    }
}


/*****************************************************************************
* VSTORE_PACKHS1
*****************************************************************************/
template<typename ELEM_T,
         typename ELEM_T_RES,
         size_t NELEM,
         VTYPE_KIND KIND,
         std::enable_if_t<!std::is_floating_point<ELEM_T>::value &&
                          !std::is_floating_point<ELEM_T_RES>::value &&
                          std::is_signed<ELEM_T>::value == std::is_signed<ELEM_T_RES>::value &&
                          std::is_unsigned<ELEM_T>::value == std::is_unsigned<ELEM_T_RES>::value &&
                          NELEM == __C7X_VEC_SIZE_BYTES__/sizeof(ELEM_T) &&
                          sizeof(ELEM_T) >= sizeof(int16_t) &&
                          sizeof(ELEM_T) == sizeof(ELEM_T_RES)*2, int> = 0>
void __vstore_packhs1(vtype<ELEM_T_RES, NELEM, VTYPE_KIND::DATA> *result,
                      const vtype<ELEM_T, NELEM, KIND> &input)
{
    for(size_t i = 0; i < NELEM; i++)
    {
        ELEM_T val = input.s[i] << (ELEM_T)1;
        (*result).s[i] = (val) >> (sizeof(ELEM_T_RES)*8); // Grabs high half
    }
}

template<typename ELEM_T,
         size_t NELEM,
         VTYPE_KIND KIND,
         std::enable_if_t<!std::is_floating_point<ELEM_T>::value &&
                          NELEM == __C7X_VEC_SIZE_BYTES__/sizeof(ELEM_T) &&
                          sizeof(ELEM_T) == sizeof(int64_t), int> = 0>
void __vstore_packhs1(vtype<ELEM_T, NELEM/2, VTYPE_KIND::DATA> *result,
                      const vtype<ELEM_T, NELEM, KIND> &input)
{
    for(size_t i = 0; i < NELEM; i += 2)
    {
        (*result).s[i/2]  = ((input.s[i+1]) << 1);
        (*result).s[i/2] |= ((input.s[i] >> 63) & 0x1);
    }
}


/*****************************************************************************
* VSTORE_PACKHS1_2SRC
*****************************************************************************/
template<typename ELEM_T,
         typename ELEM_T_RES,
         size_t NELEM,
         VTYPE_KIND KIND1,
         VTYPE_KIND KIND2,
         std::enable_if_t<!std::is_floating_point<ELEM_T>::value &&
                          !std::is_floating_point<ELEM_T_RES>::value &&
                          std::is_signed<ELEM_T>::value == std::is_signed<ELEM_T_RES>::value &&
                          std::is_unsigned<ELEM_T>::value == std::is_unsigned<ELEM_T_RES>::value &&
                          NELEM == __C7X_VEC_SIZE_BYTES__/sizeof(ELEM_T) &&
                          sizeof(ELEM_T) >= sizeof(int16_t) &&
                          sizeof(ELEM_T) == sizeof(ELEM_T_RES)*2, int> = 0>
void __vstore_packhs1_2src(vtype<ELEM_T_RES, NELEM * 2, VTYPE_KIND::DATA> *result,
                           const vtype<ELEM_T, NELEM, KIND1> &input1,
                           const vtype<ELEM_T, NELEM, KIND2> &input2)
{
    for(size_t i = 0; i < NELEM; i++)
    {
        ELEM_T val = input1.s[i] << (ELEM_T)1;
        (*result).s[i] = (val) >> (sizeof(ELEM_T_RES)*8); // Grabs high half
        ELEM_T val2 = input2.s[i] << (ELEM_T)1;
        (*result).s[i + NELEM] = (val2) >> (sizeof(ELEM_T_RES)*8); // Grabs high half
    }
}

template<typename ELEM_T,
         size_t NELEM,
         VTYPE_KIND KIND1,
         VTYPE_KIND KIND2,
         std::enable_if_t<!std::is_floating_point<ELEM_T>::value &&
                          NELEM == __C7X_VEC_SIZE_BYTES__/sizeof(ELEM_T) &&
                          sizeof(ELEM_T) == sizeof(int64_t), int> = 0>
void __vstore_packhs1_2src(vtype<ELEM_T, NELEM, VTYPE_KIND::DATA> *result,
                           const vtype<ELEM_T, NELEM, KIND1> &input1,
                           const vtype<ELEM_T, NELEM, KIND2> &input2)
{
    for (size_t i = 0; i < NELEM; i += 2)
    {
        (*result).s[i/2]  = (input1.s[i+1] << 1);
        (*result).s[i/2] |= ((input1.s[i] >> 63) & 0x1);
        (*result).s[(i + NELEM)/2]  = (input2.s[i+1] << 1);
        (*result).s[(i + NELEM)/2] |= ((input2.s[i] >> 63) & 0x1);
    }
}


#endif /* C7X_LDST_H */
