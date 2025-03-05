/*****************************************************************************/
/*  C7X_HE_LOAD_STORES.H v#####                                              */
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
#ifndef C7X_HE_LDST_H
#define C7X_HE_LDST_H

#include "vector.h"

using namespace _c70_he_detail;

/*****************************************************************************
* VLOAD_DUP
*****************************************************************************/

/*****************************************************************************
* Enabled for vtypes and accessibles 
*****************************************************************************/
template<typename ELEM_T, size_t NELEM>
vtype<ELEM_T, 64/sizeof(ELEM_T)>
__vload_dup(const vtype_ptr<ELEM_T, NELEM> input)
{
    const int nelem_output = 64/sizeof(ELEM_T);
    int num_duplicate = nelem_output / NELEM;
    vtype<ELEM_T, nelem_output> ret = vtype<ELEM_T, nelem_output>(0);

    for(size_t i = 0; i < NELEM; i++)
    {
        for(int j = 0; j < num_duplicate; j++)
        {
            ret.s[num_duplicate*i+j] = (*input).s[i];
        }
    }
    return ret;
}

/*****************************************************************************
* Enabled if ELEM_T is an arithmetic type only (built-in scalar + floats + 
* doubles). Using decay here to ensure that at the lowest level,  ELEM_T is a 
* primitive type (example int& or const int).
* Note: using c++11 syntax here just in case, c++ 14 would allow 
* std::decay_t<ELEM_T> instead of typename std::decay<ELEM_T>::type
*****************************************************************************/
template<typename ELEM_T, 
         typename = typename std::enable_if<std::is_arithmetic<typename std::decay<ELEM_T>::type>::value>::type>
vtype<ELEM_T, 64/sizeof(ELEM_T)> __vload_dup(const ELEM_T* input)
{
    const int nelem_output = 64/sizeof(ELEM_T);
    vtype<ELEM_T, nelem_output> ret = vtype<ELEM_T, nelem_output>(0);
    
    for(size_t i = 0; i < nelem_output; i++)
    {
        ret.s[i] = (ELEM_T)(*input);
    }
    return ret;
}

/*****************************************************************************
* VLOAD_DUP_VEC
*****************************************************************************/
template<typename ELEM_T, size_t NELEM,
         typename = typename std::enable_if<std::is_same<ELEM_T, int16_t>::value 
           || std::is_same<ELEM_T, uint16_t>::value>::type>
vtype<ELEM_T, 32> __vload_dup_vec(const vtype_ptr<ELEM_T, NELEM> input)
{
    // Only defined for short and ushort vectors with 4 or 8 elements
    static_assert((NELEM == 4) || (NELEM == 8), "Input vector may only have 4 or 8 elements");

    const int nelem_output = 32;
    // Number of times the "group" (input vec) will be duplicated
    int num_group_duplicates = nelem_output / NELEM; 
    vtype<ELEM_T, nelem_output> ret = vtype<ELEM_T, nelem_output>(0);

    for(int i = 0; i < num_group_duplicates; i++)
    {
        for(size_t j = 0; j < NELEM; j++)
        {
            ret.s[NELEM*i+j] = (*input).s[j];
        }
    }
    return ret;
}

/*****************************************************************************
* VLOAD_UNPACK_SHORT
*****************************************************************************/

/*****************************************************************************
* Requires enable_if as there is a difference between a char* and 
* a signed char* (aka int8_t*)
*****************************************************************************/
template<typename ELEM_T, 
         typename = typename std::enable_if<std::is_signed<typename std::decay<ELEM_T>::type>::value 
           && (sizeof(ELEM_T) == sizeof(int8_t))>::type>
int16_t __vload_unpack_short(const ELEM_T* input)
{
    return (int16_t)(*input);
}

/*****************************************************************************
* There is no difference between a uint8_t* and an unsigned char*, 
* so no template is required here
****************************************************************************/
uint16_t __vload_unpack_short(const unsigned char* input);

__cshort __vload_unpack_short(const __cchar_ptr input);

template<size_t NELEM>
vtype<int16_t, NELEM>
__vload_unpack_short(const vtype_ptr<int8_t, NELEM> input)
{
    static_assert((NELEM <= 32), "Number of elements must be <= 32");

    vtype<int16_t, NELEM> ret = vtype<int16_t, NELEM>(0);

    for(size_t i = 0; i < NELEM; i++)
    {
        ret.s[i] = (int16_t)((*input).s[i]);
    }
    return ret;
}

template<size_t NELEM>
vtype<uint16_t, NELEM>
__vload_unpack_short(const vtype_ptr<uint8_t, NELEM> input)
{
    static_assert((NELEM <= 32), "Number of elements must be <= 32");

    vtype<uint16_t, NELEM> ret = vtype<uint16_t, NELEM>(0);

    for(size_t i = 0; i < NELEM; i++)
    {
        ret.s[i] = (uint16_t)((*input).s[i]);
    }
    return ret;
}

template<size_t NELEM>
vtype<__cshort, NELEM>
__vload_unpack_short(const vtype_ptr<__cchar, NELEM> input)
{
    static_assert((NELEM <= 16), "Number of elements must be <= 16");

    vtype<__cshort, NELEM> ret = vtype<__cshort, NELEM>();

    for(size_t i = 0; i < NELEM; i++)
    {
        ret.s[i] = __cshort((int16_t)(*input).s[i].r, (int16_t)(*input).s[i].i);
    }
    return ret;
}

/*****************************************************************************
* VLOAD_UNPACK_INT
*****************************************************************************/

/*****************************************************************************
* Only valid for vectors with signed char/short or char/short 
*****************************************************************************/
template<typename ELEM_T_IN, size_t NELEM,
         typename = typename std::enable_if<(std::is_signed<ELEM_T_IN>::value) 
           && ((sizeof(ELEM_T_IN) == sizeof(int8_t)) 
           || (sizeof(ELEM_T_IN) == sizeof(int16_t)))>::type>
vtype<int32_t, NELEM>
__vload_unpack_int(const vtype_ptr<ELEM_T_IN, NELEM> input)
{
    static_assert((NELEM <= 16), "Number of elements must be <= 16");

    vtype<int32_t, NELEM> ret = vtype<int32_t, NELEM>(0);

    for(size_t i = 0; i < NELEM; i++)
    {
        ret.s[i] = (int32_t)((*input).s[i]);
    }
    return ret;
}

template<typename ELEM_T_IN, size_t NELEM,
         typename = typename std::enable_if<(std::is_unsigned<ELEM_T_IN>::value) 
           && ((sizeof(ELEM_T_IN) == sizeof(uint8_t)) 
           || (sizeof(ELEM_T_IN) == sizeof(uint16_t)))>::type>
vtype<uint32_t, NELEM>
__vload_unpack_int(const vtype_ptr<ELEM_T_IN, NELEM> input)
{
    static_assert((NELEM <= 16), "Number of elements must be <= 16");

    vtype<uint32_t, NELEM> ret = vtype<uint32_t, NELEM>(0);

    for(size_t i = 0; i < NELEM; i++)
    {
        ret.s[i] = (uint32_t)((*input).s[i]);
    }
    return ret;
}

template<typename ELEM_T_IN, size_t NELEM,
         typename = typename std::enable_if<(std::is_signed<ELEM_T_IN>::value) 
           && ((sizeof(ELEM_T_IN) == sizeof(int8_t)) 
           || (sizeof(ELEM_T_IN) == sizeof(int16_t)))>::type>
vtype<__cint, NELEM>
__vload_unpack_int(const vtype_ptr<ctype<ELEM_T_IN>, NELEM> input)
{
    static_assert((NELEM <= 8), "Number of elements must be <= 8");

    vtype<__cint, NELEM> ret = vtype<__cint, NELEM>();

    for(size_t i = 0; i < NELEM; i++)
    {
        ret.s[i] = __cint((int32_t)(*input).s[i].r, (int32_t)(*input).s[i].i);
   }
    return ret;
}

template<typename ELEM_T,
         typename = typename std::enable_if<(std::is_signed<typename std::decay<ELEM_T>::type>::value) 
           && ((sizeof(ELEM_T) == sizeof(uint8_t)) 
           || (sizeof(ELEM_T) == sizeof(uint16_t)))>::type>
int32_t __vload_unpack_int(const ELEM_T* input)
{
    return (int32_t)(*input);
}

template<typename ELEM_T,
         typename = typename std::enable_if<(std::is_unsigned<typename std::decay<ELEM_T>::type>::value) 
           && ((sizeof(ELEM_T) == sizeof(uint8_t)) 
           || (sizeof(ELEM_T) == sizeof(uint16_t)))>::type>
uint32_t __vload_unpack_int(const ELEM_T* input)
{
    return (uint32_t)(*input);
}

template<typename ELEM_T,
         typename = typename std::enable_if<(std::is_signed<typename std::decay<ELEM_T>::type>::value) 
           && ((sizeof(ELEM_T) == sizeof(uint8_t)) 
           || (sizeof(ELEM_T) == sizeof(uint16_t)))>::type>
__cint __vload_unpack_int(const ctype_ptr<ELEM_T> input)
{
    return __cint((int32_t)(*input).r, (int32_t)(*input).i);
}

/*****************************************************************************
* VLOAD_UNPACK_LONG
*****************************************************************************/
template<typename ELEM_T_IN, size_t NELEM,
         typename = typename std::enable_if<!(std::is_floating_point<ELEM_T_IN>::value) 
           && (std::is_signed<ELEM_T_IN>::value) 
           && ((sizeof(ELEM_T_IN) == sizeof(int8_t)) 
           || (sizeof(ELEM_T_IN) == sizeof(int16_t)) 
           || (sizeof(ELEM_T_IN) == sizeof(int32_t)))>::type>
vtype<int64_t, NELEM>
__vload_unpack_long(const vtype_ptr<ELEM_T_IN, NELEM> input)
{
    static_assert((NELEM <= 8), "Number of elements must be <= 8");

    vtype<int64_t, NELEM> ret = vtype<int64_t, NELEM>(0);

    for(size_t i = 0; i < NELEM; i++)
    {
        ret.s[i] = (int64_t)((*input).s[i]);
    }
    return ret;
}

template<typename ELEM_T_IN, size_t NELEM,
         typename = typename std::enable_if<(std::is_unsigned<ELEM_T_IN>::value) 
           && ((sizeof(ELEM_T_IN) == sizeof(uint8_t)) 
           || (sizeof(ELEM_T_IN) == sizeof(uint16_t)) 
           || (sizeof(ELEM_T_IN) == sizeof(uint32_t)))>::type>
vtype<uint64_t, NELEM>
__vload_unpack_long(const vtype_ptr<ELEM_T_IN, NELEM> input)
{
    static_assert((NELEM <= 8), "Number of elements must be <= 8");

    vtype<uint64_t, NELEM> ret = vtype<uint64_t, NELEM>(0);

    for(size_t i = 0; i < NELEM; i++)
    {
        ret.s[i] = (uint64_t)((*input).s[i]);
    }
    return ret;
}

template<typename ELEM_T_IN, size_t NELEM,
         typename = typename std::enable_if<!(std::is_floating_point<ELEM_T_IN>::value) 
           && (std::is_signed<ELEM_T_IN>::value) 
           && ((sizeof(ELEM_T_IN) == sizeof(int8_t)) 
           || (sizeof(ELEM_T_IN) == sizeof(int16_t)) 
           || (sizeof(ELEM_T_IN) == sizeof(int32_t)))>::type>
vtype<__clong, NELEM>
__vload_unpack_long(const vtype_ptr<ctype<ELEM_T_IN>, NELEM> input)
{
    static_assert((NELEM <= 4), "Number of elements must be <= 4");

    vtype<__clong, NELEM> ret = vtype<__clong, NELEM>();

    for(size_t i = 0; i < NELEM; i++)
    {
        ret.s[i] = __clong((int64_t)(*input).s[i].r, (int64_t)(*input).s[i].i);
    }
    return ret;
}

template<typename ELEM_T,
         typename = typename std::enable_if<
           (!(std::is_floating_point<typename std::decay<ELEM_T>::type>::value) 
           && (std::is_signed<typename std::decay<ELEM_T>::type>::value) 
           && ((sizeof(ELEM_T) == sizeof(uint8_t)) 
           || (sizeof(ELEM_T) == sizeof(uint16_t)) 
           || (sizeof(ELEM_T) == sizeof(uint32_t))))>::type>
int64_t __vload_unpack_long(const ELEM_T* input)
{
    return (int64_t)(*input);
}

template<typename ELEM_T,
         typename = typename std::enable_if<
           (std::is_unsigned<typename std::decay<ELEM_T>::type>::value) 
           && ((sizeof(ELEM_T) == sizeof(uint8_t)) 
           || (sizeof(ELEM_T) == sizeof(uint16_t)) 
           || (sizeof(ELEM_T) == sizeof(uint32_t)))>::type>
uint64_t __vload_unpack_long(const ELEM_T* input)
{
    return (uint64_t)(*input);
}

template<typename ELEM_T,
         typename = typename std::enable_if<
           (!(std::is_floating_point<typename std::decay<ELEM_T>::type>::value) 
           && (std::is_signed<typename std::decay<ELEM_T>::type>::value) 
           && ((sizeof(ELEM_T) == sizeof(uint8_t)) 
           || (sizeof(ELEM_T) == sizeof(uint16_t)) 
           || (sizeof(ELEM_T) == sizeof(uint32_t))))>::type>
__clong __vload_unpack_long(const ctype_ptr<ELEM_T> input)
{
    return __clong((int64_t)(*input).r, (int64_t)(*input).i);
}

/*****************************************************************************
* VLOAD_DEINTERLEAVE_INT
*****************************************************************************/

/*****************************************************************************
* Enable for vectors with 4 <= NELEM <= 32
*****************************************************************************/
template<typename ELEM_T_IN, size_t NELEM,
         typename = typename std::enable_if<(std::is_signed<ELEM_T_IN>::value) 
           && ((sizeof(ELEM_T_IN) == sizeof(int8_t)) 
           || (sizeof(ELEM_T_IN) == sizeof(int16_t)))>::type,
         typename = typename std::enable_if<(NELEM <= 32) && (NELEM >= 4)>::type>
vtype<int32_t, NELEM/2>
__vload_deinterleave_int(const vtype_ptr<ELEM_T_IN, NELEM> input)
{
    vtype<int32_t, NELEM/2> ret = vtype<int32_t, NELEM/2>(0);

    for(size_t i = 0; i < NELEM/2; i++)
    {
        ret.s[i] = (int32_t)(*input).s[i * 2];
    }
    return ret;
}

template<typename ELEM_T_IN, size_t NELEM,
         typename = typename std::enable_if<(std::is_unsigned<ELEM_T_IN>::value) 
           && ((sizeof(ELEM_T_IN) == sizeof(int8_t)) 
           || (sizeof(ELEM_T_IN) == sizeof(int16_t)))>::type,
         typename = typename std::enable_if<(NELEM <= 32) && (NELEM >= 4)>::type>
vtype<uint32_t, NELEM/2>
__vload_deinterleave_int(const vtype_ptr<ELEM_T_IN, NELEM> input)
{
    vtype<uint32_t, NELEM/2> ret = vtype<uint32_t, NELEM/2>(0);

    for(size_t i = 0; i < NELEM/2; i++)
    {
        ret.s[i] = (uint32_t)(*input).s[i * 2];
    }
    return ret;
}

template<typename ELEM_T_IN,
         typename = typename std::enable_if<(std::is_signed<ELEM_T_IN>::value) 
           && ((sizeof(ELEM_T_IN) == sizeof(int8_t)) 
           || (sizeof(ELEM_T_IN) == sizeof(int16_t)))>::type>
int32_t __vload_deinterleave_int(const vtype_ptr<ELEM_T_IN, 2> input)
{
    return (int32_t)(*input).s0;
}

template<typename ELEM_T_IN,
         typename = typename std::enable_if<(std::is_unsigned<ELEM_T_IN>::value) 
           && ((sizeof(ELEM_T_IN) == sizeof(int8_t)) 
           || (sizeof(ELEM_T_IN) == sizeof(int16_t)))>::type>
uint32_t __vload_deinterleave_int(const vtype_ptr<ELEM_T_IN, 2> input)
{
    return (uint32_t)(*input).s0;
}

/*****************************************************************************
* VLOAD_DEINTERLEAVE_LONG
*****************************************************************************/

/*****************************************************************************
* Enable for vectors with 4 <= NELEM <= 16
*****************************************************************************/
template<typename ELEM_T_IN, size_t NELEM,
         typename = typename std::enable_if<(std::is_signed<ELEM_T_IN>::value) 
           && ((sizeof(ELEM_T_IN) == sizeof(int8_t)) 
           || (sizeof(ELEM_T_IN) == sizeof(int16_t)))>::type,
         typename = typename std::enable_if< (NELEM <= 16) && (NELEM >= 4) >::type>
vtype<int64_t, NELEM/2>
__vload_deinterleave_long(const vtype_ptr<ELEM_T_IN, NELEM> input)
{
    vtype<int64_t, NELEM/2> ret = vtype<int64_t, NELEM/2>(0);

    for(size_t i = 0; i < NELEM/2; i++)
    {
        ret.s[i] = (int64_t)(*input).s[i * 2];
    }
    return ret;
}

template<typename ELEM_T_IN, size_t NELEM,
         typename = typename std::enable_if<(std::is_unsigned<ELEM_T_IN>::value) 
             && ((sizeof(ELEM_T_IN) == sizeof(int8_t)) 
             || (sizeof(ELEM_T_IN) == sizeof(int16_t)))>::type,
         typename = typename std::enable_if< (NELEM <= 16) && (NELEM >= 4) >::type>
vtype<uint64_t, NELEM/2>
__vload_deinterleave_long(const vtype_ptr<ELEM_T_IN, NELEM> input)
{
    vtype<uint64_t, NELEM/2> ret = vtype<uint64_t, NELEM/2>(0);

    for(size_t i = 0; i < NELEM/2; i++)
    {
        ret.s[i] = (uint64_t)(*input).s[i * 2];
    }
    return ret;
}

template<typename ELEM_T_IN,
         typename = typename std::enable_if<(std::is_signed<ELEM_T_IN>::value) 
             && ((sizeof(ELEM_T_IN) == sizeof(int8_t)) 
             || (sizeof(ELEM_T_IN) == sizeof(int16_t)))>::type>
int64_t __vload_deinterleave_long(const vtype_ptr<ELEM_T_IN, 2> input)
{
    return (int64_t)(*input).s0;
}

template<typename ELEM_T_IN,
         typename = typename std::enable_if<(std::is_unsigned<ELEM_T_IN>::value) 
             && ((sizeof(ELEM_T_IN) == sizeof(int8_t)) 
             || (sizeof(ELEM_T_IN) == sizeof(int16_t)))>::type>
uint64_t __vload_deinterleave_long(const vtype_ptr<ELEM_T_IN, 2> input)
{
    return (uint64_t)(*input).s0;
}

/*****************************************************************************
* VSTORE_INTERLEAVE
*****************************************************************************/

/*****************************************************************************
* Template only enabled for full vectors.
* Note: param1 does not have to be an accessible* because only  full (512-bit) 
* vectors are allowed here. There is no way to make a full vector from an 
* accessible.
*****************************************************************************/
template<typename ELEM_T, size_t NELEM,
         typename = typename std::enable_if<!(std::is_floating_point<ELEM_T>::value) 
           && (NELEM == 64/sizeof(ELEM_T))>::type>
void __vstore_interleave(vtype_ptr<ELEM_T, NELEM> result, 
                         vtype<ELEM_T, NELEM> input1, 
                         vtype<ELEM_T, NELEM> input2) 
{
    (*result).even = input1.even;
    (*result).odd  = input2.even;
}


/*****************************************************************************
* Store every fourth element. Enabled if result vector is 32 characters and 
* both inputs are 64 characters long. Also only enabled if the element type 
* is of size 8 bits (sizeof(int8_t)) -> applies to unsigned and signed char
****************************************************************************/
template<typename ELEM_T, size_t NELEM,
         typename = typename std::enable_if<(NELEM == 64/sizeof(int8_t))>::type,
         typename = typename std::enable_if<(sizeof(ELEM_T) == sizeof(int8_t))>::type>
void __vstore_interleave(vtype_ptr<ELEM_T, NELEM/2> result, 
                         vtype<ELEM_T, NELEM> input1, 
                         vtype<ELEM_T, NELEM> input2) 
{
    (*result).even = input1.even.even;
    (*result).odd  = input2.even.even;
}

/*****************************************************************************
* Helper function used to check if predicate is true at index 
*****************************************************************************/
bool check_pred_at_index(__vpred pred, uint64_t index, uint64_t element_size);

/*****************************************************************************
* VSTORE_PRED_INTERLEAVE
*****************************************************************************/
template<typename ELEM_T, size_t NELEM,
         typename = typename std::enable_if<!(std::is_floating_point<ELEM_T>::value) 
           && (NELEM == 64/sizeof(ELEM_T))>::type>
void __vstore_pred_interleave(__vpred pred, 
                              vtype_ptr<ELEM_T, NELEM> result, 
                              vtype<ELEM_T, NELEM> input1,   
                              vtype<ELEM_T, NELEM> input2) 
{
    // Even part
    for (size_t i = 0; i < NELEM; i+=2)
    {
        if (check_pred_at_index(pred, i, sizeof(ELEM_T))) (*result).s[i] = input1.s[i];   
    }
    
    // Odd part
    for (size_t i = 1; i < NELEM; i+=2)
    {
        if (check_pred_at_index(pred, i, sizeof(ELEM_T))) (*result).s[i] = input2.s[i];
    }
}

/*****************************************************************************
* Store every fourth element based on pred. Enabled if result vector is 32 
* characters and both inputs are 64 characters long. Also only enabled if the 
* element type is of size 8 bits (sizeof(int8_t)) -> applies to unsigned 
* and signed char
*****************************************************************************/
template<typename ELEM_T, size_t NELEM,
         typename = typename std::enable_if<(NELEM == 64/sizeof(int8_t))>::type,
         typename = typename std::enable_if<(sizeof(ELEM_T) == sizeof(int8_t))>::type>
void __vstore_pred_interleave4(__vpred pred, 
                               vtype_ptr<ELEM_T, NELEM/2> result, 
                               vtype<ELEM_T, NELEM> input1, 
                               vtype<ELEM_T, NELEM> input2) 
{
    for (size_t i = 0; i < NELEM; i+=4)
    {
        if (check_pred_at_index(pred, i, sizeof(ELEM_T))) (*result).s[i/2] = input1.s[i];
    }
        
    for (size_t i = 1; i < NELEM; i+=4)
    {
        if (check_pred_at_index(pred, i, sizeof(ELEM_T))) (*result).s[(i/2 + 1)] = input2.s[i];
    }
}

/*****************************************************************************
* VSTORE_PRED
*****************************************************************************/

/*****************************************************************************
* Accept accessible reference as second parameter. This allows the function to 
* accept accessibles as parameters. Must be references as you cannot create a 
* copy of an accessible bc it does not hold any storage (so a copy of it 
* doesn't make sense). When a vtype is the parameter, inheritance rules allow 
* for the function to be matched as all vtypes are accessibles.
* Note: input is not modified in this function and shouldn't be
*****************************************************************************/
template<typename ELEM_T, size_t NELEM, size_t DEPTH>
void __vstore_pred(__vpred pred, vtype_ptr<ELEM_T, NELEM> result, 
                   accessible<ELEM_T, NELEM, DEPTH> &input)
{
    for(size_t i = 0; i < NELEM; i++)
    {
        if (check_pred_at_index(pred, i, sizeof(ELEM_T))) (*result).s[i] = input.s[i];
    }
}

template<typename ELEM_T, size_t NELEM>
void __vstore_pred(__vpred pred, 
                   vtype_ptr<ELEM_T, NELEM> result, 
                   vtype<ELEM_T, NELEM> input)
{
    for(size_t i = 0; i < NELEM; i++)
    {
        if (check_pred_at_index(pred, i, sizeof(ELEM_T))) (*result).s[i] = input.s[i];
    }
}

template<typename ELEM_T, size_t NELEM, size_t DEPTH>
void __vstore_pred(__vpred pred, vtype_ptr<ctype<ELEM_T>, NELEM> result, 
                   accessible<ctype<ELEM_T>, NELEM, DEPTH> &input)
{
    for(size_t i = 0; i < NELEM * 2; i++)
    {
        if (check_pred_at_index(pred, i, sizeof(ELEM_T)))
        { 
            if (i % 2 == 0)
                (*result).s[i/2].r = input.s[i/2].r;
            else
                (*result).s[i/2].i = input.s[i/2].i;
        }
    }
}

template<typename ELEM_T, size_t NELEM>
void __vstore_pred(__vpred pred, 
                   vtype_ptr<ctype<ELEM_T>, NELEM> result, 
                   vtype<ctype<ELEM_T>, NELEM> input)
{
    for(size_t i = 0; i < NELEM * 2; i++)
    {
        if (check_pred_at_index(pred, i, sizeof(ELEM_T))) 
        {
            if (i % 2 == 0)
                (*result).s[i/2].r = input.s[i/2].r;
            else
                (*result).s[i/2].i = input.s[i/2].i;
        }
    }
}

/*****************************************************************************
* VSTORE_PRED_PACKL
*****************************************************************************/

/*****************************************************************************
* Limits:
* No floating, size of result element = half size of input element, 
* full vectors only, no floating points, element size of input at least short
*****************************************************************************/
template<typename ELEM_T_IN, typename ELEM_T_RES, size_t NELEM,
         typename = typename std::enable_if<!(std::is_floating_point<ELEM_T_IN>::value) 
                    && !(std::is_floating_point<ELEM_T_RES>::value)>::type,
         typename = typename std::enable_if<(std::is_signed<ELEM_T_IN>::value == std::is_signed<ELEM_T_RES>::value) 
                    && (std::is_unsigned<ELEM_T_IN>::value == std::is_unsigned<ELEM_T_RES>::value)>::type,
         typename = typename std::enable_if<(NELEM == 64/sizeof(ELEM_T_IN))>::type,
         typename = typename std::enable_if<(sizeof(ELEM_T_IN) >= sizeof(int16_t)) 
                    && (sizeof(ELEM_T_IN) == sizeof(ELEM_T_RES)*2)>::type>
void __vstore_pred_packl(__vpred pred, 
                         vtype_ptr<ELEM_T_RES, NELEM> result, 
                         vtype<ELEM_T_IN, NELEM> input)
{
    for(size_t i = 0; i < NELEM; i++)
    {
        if (check_pred_at_index(pred, i, sizeof(ELEM_T_IN)))
            (*result).s[i] = (ELEM_T_RES)(input.s[i]); // Grabs low half
    }
}

/*****************************************************************************
* VSTORE_PRED_PACKL_2SRC
*****************************************************************************/
template<typename ELEM_T_IN, typename ELEM_T_RES, size_t NELEM,
         typename = typename std::enable_if<!(std::is_floating_point<ELEM_T_IN>::value) 
                    && !(std::is_floating_point<ELEM_T_RES>::value)>::type,
         typename = typename std::enable_if<(std::is_signed<ELEM_T_IN>::value == std::is_signed<ELEM_T_RES>::value) 
                    && (std::is_unsigned<ELEM_T_IN>::value == std::is_unsigned<ELEM_T_RES>::value)>::type,
         typename = typename std::enable_if<(NELEM == 64/sizeof(ELEM_T_IN))>::type,
         typename = typename std::enable_if<(sizeof(ELEM_T_IN) >= sizeof(int16_t)) 
                    && (sizeof(ELEM_T_IN) == sizeof(ELEM_T_RES)*2)>::type>
void __vstore_pred_packl_2src(__vpred pred, 
                         vtype_ptr<ELEM_T_RES, NELEM*2> result, 
                         vtype<ELEM_T_IN, NELEM> input1,
                         vtype<ELEM_T_IN, NELEM> input2)
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
template<typename ELEM_T_IN, typename ELEM_T_RES, size_t NELEM,
         typename = typename std::enable_if<!(std::is_floating_point<ELEM_T_IN>::value) 
                    && !(std::is_floating_point<ELEM_T_RES>::value)>::type,
         typename = typename std::enable_if<(std::is_signed<ELEM_T_IN>::value == std::is_signed<ELEM_T_RES>::value)
                    &&  (std::is_unsigned<ELEM_T_IN>::value == std::is_unsigned<ELEM_T_RES>::value)>::type,
         typename = typename std::enable_if<(NELEM == 64/sizeof(ELEM_T_IN))>::type,
         typename = typename std::enable_if<(sizeof(ELEM_T_IN) >= sizeof(int16_t)) 
                    && (sizeof(ELEM_T_IN) == sizeof(ELEM_T_RES)*2)>::type>
void __vstore_pred_packh(__vpred pred, 
                         vtype_ptr<ELEM_T_RES, NELEM> result,
                         vtype<ELEM_T_IN, NELEM> input)
{
    for(size_t i = 0; i < NELEM; i++)
    {
        if (check_pred_at_index(pred, i, sizeof(ELEM_T_IN)))
            (*result).s[i] = (input.s[i]) >> (sizeof(ELEM_T_RES)*8); // Grabs high half
    }
}

/*****************************************************************************
* VSTORE_PRED_PACKH_2SRC
*****************************************************************************/
template<typename ELEM_T_IN, typename ELEM_T_RES, size_t NELEM,
         typename = typename std::enable_if<!(std::is_floating_point<ELEM_T_IN>::value) 
                    && !(std::is_floating_point<ELEM_T_RES>::value)>::type,
         typename = typename std::enable_if<(std::is_signed<ELEM_T_IN>::value == std::is_signed<ELEM_T_RES>::value)
                    &&  (std::is_unsigned<ELEM_T_IN>::value == std::is_unsigned<ELEM_T_RES>::value)>::type,
         typename = typename std::enable_if<(NELEM == 64/sizeof(ELEM_T_IN))>::type,
         typename = typename std::enable_if<(sizeof(ELEM_T_IN) >= sizeof(int16_t)) 
                    && (sizeof(ELEM_T_IN) == sizeof(ELEM_T_RES)*2)>::type>
void __vstore_pred_packh_2src(__vpred pred, 
                         vtype_ptr<ELEM_T_RES, NELEM*2> result,
                         vtype<ELEM_T_IN, NELEM> input1,
                         vtype<ELEM_T_IN, NELEM> input2)
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
template<typename ELEM_T_IN, typename ELEM_T_RES, size_t NELEM,
         typename = typename std::enable_if<!(std::is_floating_point<ELEM_T_IN>::value) 
                    && !(std::is_floating_point<ELEM_T_RES>::value)>::type,
         typename = typename std::enable_if<(std::is_signed<ELEM_T_IN>::value == std::is_signed<ELEM_T_RES>::value)
                    && (std::is_unsigned<ELEM_T_IN>::value == std::is_unsigned<ELEM_T_RES>::value)>::type,
         typename = typename std::enable_if<(NELEM == 64/sizeof(ELEM_T_IN))>::type,
         typename = typename std::enable_if<(sizeof(ELEM_T_IN) >= sizeof(int16_t))
                    && (sizeof(ELEM_T_IN) == sizeof(ELEM_T_RES)*2)>::type>
void __vstore_pred_packhs1(__vpred pred, 
                           vtype_ptr<ELEM_T_RES, NELEM> result, 
                           vtype<ELEM_T_IN, NELEM> input)
{
    for(size_t i = 0; i < NELEM; i++)
    {
        if (check_pred_at_index(pred, i, sizeof(ELEM_T_IN)))
        {
            ELEM_T_IN val = input.s[i] << (ELEM_T_IN)1;
            (*result).s[i] = (val) >> (sizeof(ELEM_T_RES)*8); // Grabs high half
        }
    }
}

/*****************************************************************************
* VSTORE_PRED_PACKHS1_2SRC
*****************************************************************************/
template<typename ELEM_T_IN, typename ELEM_T_RES, size_t NELEM,
         typename = typename std::enable_if<!(std::is_floating_point<ELEM_T_IN>::value) 
                    && !(std::is_floating_point<ELEM_T_RES>::value)>::type,
         typename = typename std::enable_if<(std::is_signed<ELEM_T_IN>::value == std::is_signed<ELEM_T_RES>::value)
                    && (std::is_unsigned<ELEM_T_IN>::value == std::is_unsigned<ELEM_T_RES>::value)>::type,
         typename = typename std::enable_if<(NELEM == 64/sizeof(ELEM_T_IN))>::type,
         typename = typename std::enable_if<(sizeof(ELEM_T_IN) >= sizeof(int16_t))
                    && (sizeof(ELEM_T_IN) == sizeof(ELEM_T_RES)*2)>::type>
void __vstore_pred_packhs1_2src(__vpred pred, 
                           vtype_ptr<ELEM_T_RES, NELEM*2> result, 
                           vtype<ELEM_T_IN, NELEM> input1,
                           vtype<ELEM_T_IN, NELEM> input2)
{
    for(size_t i = 0; i < NELEM; i++)
    {
        if (check_pred_at_index(pred, i, sizeof(ELEM_T_RES)))
        {
            ELEM_T_IN val = input1.s[i] << (ELEM_T_IN)1;
            (*result).s[i] = (val) >> (sizeof(ELEM_T_RES)*8); // Grabs high half
        }
        if (check_pred_at_index(pred, i + NELEM, sizeof(ELEM_T_RES)))
        {
            ELEM_T_IN val = input2.s[i] << (ELEM_T_IN)1;
            (*result).s[i + NELEM] = (val) >> (sizeof(ELEM_T_RES)*8); // Grabs high half
        }
    }
}

/*****************************************************************************
* VSTORE_PRED_PACK_BYTE
*****************************************************************************/
void __vstore_pred_pack_byte(__vpred pred,
                             vtype_ptr<int8_t, 16> result, 
                             __int16 input);

void __vstore_pred_pack_byte(__vpred pred, 
                             vtype_ptr<uint8_t, 16> result, 
                             __uint16 input);

/*****************************************************************************
* VSTORE_PRED_PACK_BYTE_2SRC
*****************************************************************************/
void __vstore_pred_pack_byte_2src(__vpred pred,
                                  vtype_ptr<int8_t, 32> result, 
                                  __int16 input1,
                                  __int16 input2);

void __vstore_pred_pack_byte_2src(__vpred pred, 
                                  vtype_ptr<uint8_t, 32> result, 
                                  __uint16 input1,
                                  __uint16 input2);

/*****************************************************************************
* __VSTORE_PRED_PACKL_LONG 
*****************************************************************************/
void __vstore_pred_packl_long(__vpred pred, 
                               vtype_ptr<int64_t, 4> result, 
                               __long8 input);

void __vstore_pred_packl_long(__vpred pred, 
                               vtype_ptr<uint64_t, 4> result,
                               __ulong8 input);

/*****************************************************************************
* __VSTORE_PRED_PACKL_LONG_2SRC 
*****************************************************************************/
void __vstore_pred_packl_long_2src(__vpred pred, 
                                    vtype_ptr<int64_t, 8> result, 
                                    __long8 input1,
                                    __long8 input2);

void __vstore_pred_packl_long_2src(__vpred pred, 
                                    vtype_ptr<uint64_t, 8> result,
                                    __ulong8 input1,
                                    __ulong8 input2);

/*****************************************************************************
* __VSTORE_PRED_PACKH_LONG 
*****************************************************************************/
void __vstore_pred_packh_long(__vpred pred, 
                               vtype_ptr<int64_t, 4> result, 
                               __long8 input);

void __vstore_pred_packh_long(__vpred pred,
                               vtype_ptr<uint64_t, 4> result,
                               __ulong8 input);

/*****************************************************************************
* __VSTORE_PRED_PACKH_LONG_2SRC 
*****************************************************************************/
void __vstore_pred_packh_long_2src(__vpred pred, 
                                    vtype_ptr<int64_t, 8> result, 
                                    __long8 input1,
                                    __long8 input2);

void __vstore_pred_packh_long_2src(__vpred pred,
                                    vtype_ptr<uint64_t, 8> result,
                                    __ulong8 input1,
                                    __ulong8 input2);

/*****************************************************************************
* __VSTORE_PRED_PACKHS1_LONG 
*****************************************************************************/
void __vstore_pred_packhs1_long(__vpred pred, 
                                 vtype_ptr<int64_t, 4> result, 
                                 __long8 input);

void __vstore_pred_packhs1_long(__vpred pred, 
                                 vtype_ptr<uint64_t, 4> result, 
                                 __ulong8 input);

/*****************************************************************************
* __VSTORE_PRED_PACKHS1_LONG_2SRC 
*****************************************************************************/
void __vstore_pred_packhs1_long_2src(__vpred pred, 
                                      vtype_ptr<int64_t, 8> result, 
                                      __long8 input1,
                                      __long8 input2);

void __vstore_pred_packhs1_long_2src(__vpred pred, 
                                      vtype_ptr<uint64_t, 8> result, 
                                      __ulong8 input1,
                                      __ulong8 input2);

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
template<typename ELEM_T, size_t NELEM,
         typename = typename std::enable_if<(NELEM == 64/(sizeof(ELEM_T) * 2))>::type,
         typename = typename std::enable_if<(sizeof(ELEM_T) >= sizeof(int16_t))
                                            && (sizeof(ELEM_T) < sizeof(int64_t))>::type>
void __vstore_pred_reverse_bit(__vpred pred, 
                               vtype_ptr<ctype<ELEM_T>, NELEM> result, 
                               vtype<ctype<ELEM_T>, NELEM> input)
{
   uint32_t num_of_bits = (uint32_t)std::log2(NELEM * 2);

   vtype<ELEM_T, NELEM * 2> non_complex_res;
   vtype<ELEM_T, NELEM * 2> non_complex_input;

   // Grab complex vector components as raw vector
   for (size_t i = 0; i < NELEM * 2; i++)
   {
       if (i % 2 == 0)
           non_complex_input.s[i] = input.s[i/2].r;
       else
           non_complex_input.s[i] = input.s[i/2].i;
   }
 
   for (size_t i = 0; i < NELEM * 2; i++)
   {
       if (check_pred_at_index(pred, i, sizeof(ELEM_T)))
       {
           size_t reverse_bit_index = reverse_bits((uint32_t)i, num_of_bits);
           
           non_complex_res.s[i] = non_complex_input.s[reverse_bit_index];
       }   
   }

   // Fill into complex vector result
   for (size_t i = 0; i < NELEM * 2; i++)
   {
       if (i % 2 == 0)
           (*result).s[i/2].r = non_complex_res.s[i];
       else
           (*result).s[i/2].i = non_complex_res.s[i];
   }
}

/*****************************************************************************
* VSTORE_REVERSE_BIT
*****************************************************************************/

/*****************************************************************************
* Limits: At least short, full vector
*****************************************************************************/
template<typename ELEM_T, size_t NELEM,
         typename = typename std::enable_if<(NELEM == 64/sizeof(ELEM_T))>::type,
         typename = typename std::enable_if<(sizeof(ELEM_T) >= sizeof(int16_t))>::type>
void __vstore_reverse_bit(vtype_ptr<ELEM_T, NELEM> result,
                          vtype<ELEM_T, NELEM> input)
{
    uint32_t num_of_bits = (uint32_t)std::log2(NELEM);
  
    for (size_t i = 0; i < NELEM; i++)
    {
        (*result).s[i] = (input.s[reverse_bits((uint32_t)i, num_of_bits)]); 
    }
}

template<typename ELEM_T, size_t NELEM,
         typename = typename std::enable_if<(NELEM == 64/(sizeof(ELEM_T) * 2))>::type,
         typename = typename std::enable_if<(sizeof(ELEM_T) >= sizeof(int16_t))
                                            && (sizeof(ELEM_T) < sizeof(int64_t))>::type>
void __vstore_reverse_bit(vtype_ptr<ctype<ELEM_T>, NELEM> result, 
                               vtype<ctype<ELEM_T>, NELEM> input)
{
   uint32_t num_of_bits = (uint32_t)std::log2(NELEM * 2);

   vtype<ELEM_T, NELEM * 2> non_complex_res;
   vtype<ELEM_T, NELEM * 2> non_complex_input;

   // Grab complex vector components as raw vector
   for (size_t i = 0; i < NELEM * 2; i++)
   {
       if (i % 2 == 0)
           non_complex_input.s[i] = input.s[i/2].r;
       else
           non_complex_input.s[i] = input.s[i/2].i;
   }
 
   for (size_t i = 0; i < NELEM * 2; i++)
   {
       size_t reverse_bit_index = reverse_bits((uint32_t)i, num_of_bits);
           
       non_complex_res.s[i] = non_complex_input.s[reverse_bit_index];
   }

   // Fill into complex vector result
   for (size_t i = 0; i < NELEM * 2; i++)
   {
       if (i % 2 == 0)
           (*result).s[i/2].r = non_complex_res.s[i];
       else
           (*result).s[i/2].i = non_complex_res.s[i];
   }
}

/*****************************************************************************
* VSTORE_CONST
*****************************************************************************/
void __vstore_const(uint32_t* result, uint32_t input);

/*****************************************************************************
* MULTI_WORD
*****************************************************************************/
template<size_t NELEM>
void __vstore_const_multi_word(vtype_ptr<uint32_t, NELEM> result, 
                               uint32_t input)
{
    assert(((input >= 0) && (input <= 0x7fffffff)) && "Input constant out of range");
    *result = vtype<uint32_t, NELEM>(input);;
}

/*****************************************************************************
* UINT2
*****************************************************************************/
void __vstore_const_uint2(vtype_ptr<uint32_t, 2> result, uint32_t input);

/*****************************************************************************
* UINT4
*****************************************************************************/
void __vstore_const_uint4(vtype_ptr<uint32_t, 4> result, uint32_t input);

/*****************************************************************************
* UINT8
*****************************************************************************/
void __vstore_const_uint8(vtype_ptr<uint32_t, 8> result, uint32_t input);

/*****************************************************************************
* UINT16
*****************************************************************************/
void __vstore_const_uint16(vtype_ptr<uint32_t, 16> result, uint32_t input);

/*****************************************************************************
* VSTORE_PACKL
*****************************************************************************/

/*****************************************************************************
* Limits:
* No floating, size of result element = half size of input element, 
* full vectors only, no floating points, element size of input at least short
*****************************************************************************/
template<typename ELEM_T_IN, typename ELEM_T_RES, size_t NELEM,
         typename = typename std::enable_if<!(std::is_floating_point<ELEM_T_IN>::value) 
                    && !(std::is_floating_point<ELEM_T_RES>::value)>::type,
         typename = typename std::enable_if<(std::is_signed<ELEM_T_IN>::value == std::is_signed<ELEM_T_RES>::value) 
                    && (std::is_unsigned<ELEM_T_IN>::value == std::is_unsigned<ELEM_T_RES>::value)>::type,
         typename = typename std::enable_if<(NELEM == 64/sizeof(ELEM_T_IN))>::type,
         typename = typename std::enable_if<(sizeof(ELEM_T_IN) >= sizeof(int16_t)) 
                    && (sizeof(ELEM_T_IN) == sizeof(ELEM_T_RES)*2)>::type>
void __vstore_packl(vtype_ptr<ELEM_T_RES, NELEM> result, 
                    vtype<ELEM_T_IN, NELEM> input)
{
    for(size_t i = 0; i < NELEM; i++)
    {
        (*result).s[i] = (ELEM_T_RES)(input.s[i]); // Grabs low half
    }
}

template<typename ELEM_T_IN, size_t NELEM,
         typename = typename std::enable_if<!(std::is_floating_point<ELEM_T_IN>::value)>::type, 
         typename = typename std::enable_if<(NELEM == 64/sizeof(ELEM_T_IN))>::type,
         typename = typename std::enable_if<(sizeof(ELEM_T_IN) == sizeof(int64_t))>::type> 
void __vstore_packl(vtype_ptr<ELEM_T_IN, NELEM/2> result, 
                    vtype<ELEM_T_IN, NELEM> input)
{
    for(size_t i = 0; i < NELEM; i += 2)
    {
        (*result).s[i/2] = (input.s[i]);
    }
}

template<typename ELEM_T_IN, typename ELEM_T_RES, size_t NELEM,
         typename = typename std::enable_if<!(std::is_floating_point<ELEM_T_IN>::value) 
                    && !(std::is_floating_point<ELEM_T_RES>::value)>::type,
         typename = typename std::enable_if<(std::is_signed<ELEM_T_IN>::value == std::is_signed<ELEM_T_RES>::value)>::type, 
         typename = typename std::enable_if<(NELEM == 64/(sizeof(ELEM_T_IN) * 2))>::type,
         typename = typename std::enable_if<(sizeof(ELEM_T_IN) >= sizeof(int16_t)) 
                    && (sizeof(ELEM_T_IN) == sizeof(ELEM_T_RES)*2)>::type>
void __vstore_packl(vtype_ptr<ctype<ELEM_T_RES>, NELEM> result, 
                         vtype<ctype<ELEM_T_IN>, NELEM> input)
{
    for(size_t i = 0; i < NELEM * 2; i++)
    {
        if (i % 2 == 0)
            (*result).s[i/2].r = (ELEM_T_RES)input.s[i/2].r;
        else
            (*result).s[i/2].i = (ELEM_T_RES)input.s[i/2].i;
    }
}

void __vstore_packl(vtype_ptr<int64_t, 4> result, 
                    vtype<ctype<int64_t>, 4> input);

/*****************************************************************************
* VSTORE_PACKL_2SRC
*****************************************************************************/

/*****************************************************************************
* Limits:
* No floating, size of result element = half size of input element, 
* full vectors only, no floating points, element size of input at least short
*****************************************************************************/
template<typename ELEM_T_IN, typename ELEM_T_RES, size_t NELEM,
         typename = typename std::enable_if<!(std::is_floating_point<ELEM_T_IN>::value) 
                    && !(std::is_floating_point<ELEM_T_RES>::value)>::type,
         typename = typename std::enable_if<(std::is_signed<ELEM_T_IN>::value == std::is_signed<ELEM_T_RES>::value) 
                    && (std::is_unsigned<ELEM_T_IN>::value == std::is_unsigned<ELEM_T_RES>::value)>::type,
         typename = typename std::enable_if<(NELEM == 64/sizeof(ELEM_T_IN))>::type,
         typename = typename std::enable_if<(sizeof(ELEM_T_IN) >= sizeof(int16_t)) 
                    && (sizeof(ELEM_T_IN) == sizeof(ELEM_T_RES)*2)>::type>
void __vstore_packl_2src(vtype_ptr<ELEM_T_RES, NELEM * 2> result, 
                         vtype<ELEM_T_IN, NELEM> input1,
                         vtype<ELEM_T_IN, NELEM> input2)
{
    for(size_t i = 0; i < NELEM; i++)
    {
        (*result).s[i] = (ELEM_T_RES)(input1.s[i]); // Grabs low half
        (*result).s[i + NELEM] = (ELEM_T_RES)(input2.s[i]); // Grabs low half

    }
}

template<typename ELEM_T_IN, size_t NELEM,
         typename = typename std::enable_if<!(std::is_floating_point<ELEM_T_IN>::value)>::type, 
         typename = typename std::enable_if<(NELEM == 64/sizeof(ELEM_T_IN))>::type,
         typename = typename std::enable_if<(sizeof(ELEM_T_IN) == sizeof(int64_t))>::type> 
void __vstore_packl_2src(vtype_ptr<ELEM_T_IN, NELEM> result, 
                         vtype<ELEM_T_IN, NELEM> input1,
                         vtype<ELEM_T_IN, NELEM> input2)
{
    for (size_t i = 0; i < NELEM; i += 2)
    {
        (*result).s[i/2] = input1.s[i];
        (*result).s[(i + NELEM)/2] = input2.s[i]; 
    }
}

template<typename ELEM_T_IN, typename ELEM_T_RES, size_t NELEM,
         typename = typename std::enable_if<!(std::is_floating_point<ELEM_T_IN>::value) 
                    && !(std::is_floating_point<ELEM_T_RES>::value)>::type,
         typename = typename std::enable_if<(std::is_signed<ELEM_T_IN>::value == std::is_signed<ELEM_T_RES>::value)>::type, 
         typename = typename std::enable_if<(NELEM == 64/(sizeof(ELEM_T_IN) * 2))>::type,
         typename = typename std::enable_if<(sizeof(ELEM_T_IN) >= sizeof(int16_t)) 
                    && (sizeof(ELEM_T_IN) == sizeof(ELEM_T_RES)*2)>::type>
void __vstore_packl_2src(vtype_ptr<ctype<ELEM_T_RES>, NELEM * 2> result, 
                         vtype<ctype<ELEM_T_IN>, NELEM> input1,
                         vtype<ctype<ELEM_T_IN>, NELEM> input2)
{
    for(size_t i = 0; i < NELEM * 2; i++)
    {
        if (i % 2 == 0)
        {
            (*result).s[i/2].r = (ELEM_T_RES)(input1.s[i/2].r); 
            (*result).s[i/2 + NELEM].r = (ELEM_T_RES)(input2.s[i/2].r);
        }
        else
        {
            (*result).s[i/2].i = (ELEM_T_RES)(input1.s[i/2].i); 
            (*result).s[i/2 + NELEM].i = (ELEM_T_RES)(input2.s[i/2].i); 
        }
    }
}

void __vstore_packl_2src(vtype_ptr<int64_t, 8> result, 
                         vtype<ctype<int64_t>, 4> input1,
                         vtype<ctype<int64_t>, 4> input2);

/*****************************************************************************
* VSTORE_PACKH
*****************************************************************************/
template<typename ELEM_T_IN, typename ELEM_T_RES, size_t NELEM,
         typename = typename std::enable_if<!(std::is_floating_point<ELEM_T_IN>::value) 
                    && !(std::is_floating_point<ELEM_T_RES>::value)>::type,
         typename = typename std::enable_if<(std::is_signed<ELEM_T_IN>::value == std::is_signed<ELEM_T_RES>::value) 
                    && (std::is_unsigned<ELEM_T_IN>::value == std::is_unsigned<ELEM_T_RES>::value)>::type,
         typename = typename std::enable_if<(NELEM == 64/sizeof(ELEM_T_IN))>::type,
         typename = typename std::enable_if<(sizeof(ELEM_T_IN) >= sizeof(int16_t)) 
                    && (sizeof(ELEM_T_IN) == sizeof(ELEM_T_RES)*2)>::type>
void __vstore_packh(vtype_ptr<ELEM_T_RES, NELEM> result, 
                    vtype<ELEM_T_IN, NELEM> input)
{
    for(size_t i = 0; i < NELEM; i++)
    {
        (*result).s[i] = (input.s[i]) >> (sizeof(ELEM_T_RES)*8); // Grabs high half
    }
}

template<typename ELEM_T_IN, size_t NELEM,
         typename = typename std::enable_if<!(std::is_floating_point<ELEM_T_IN>::value)>::type, 
         typename = typename std::enable_if<(NELEM == 64/sizeof(ELEM_T_IN))>::type,
         typename = typename std::enable_if<(sizeof(ELEM_T_IN) == sizeof(int64_t))>::type> 
void __vstore_packh(vtype_ptr<ELEM_T_IN, NELEM/2> result, 
                    vtype<ELEM_T_IN, NELEM> input)
{
    for(size_t i = 0; i < NELEM; i += 2)
    {
        (*result).s[i/2] = (input.s[i+1]);
    }
}

template<typename ELEM_T_IN, typename ELEM_T_RES, size_t NELEM,
         typename = typename std::enable_if<!(std::is_floating_point<ELEM_T_IN>::value) 
                    && !(std::is_floating_point<ELEM_T_RES>::value)>::type,
         typename = typename std::enable_if<(std::is_signed<ELEM_T_IN>::value == std::is_signed<ELEM_T_RES>::value)>::type, 
         typename = typename std::enable_if<(NELEM == 64/(sizeof(ELEM_T_IN) * 2))>::type,
         typename = typename std::enable_if<(sizeof(ELEM_T_IN) >= sizeof(int16_t)) 
                    && (sizeof(ELEM_T_IN) == sizeof(ELEM_T_RES)*2)>::type>
void __vstore_packh(vtype_ptr<ctype<ELEM_T_RES>, NELEM> result, 
                    vtype<ctype<ELEM_T_IN>, NELEM> input)
{
    for(size_t i = 0; i < NELEM * 2; i++)
    {
        if (i % 2 == 0)
            (*result).s[i/2].r = (input.s[i/2].r) >> (sizeof(ELEM_T_RES)*8);
        else
            (*result).s[i/2].i = (input.s[i/2].i) >> (sizeof(ELEM_T_RES)*8);
    }
}

void __vstore_packh(vtype_ptr<int64_t, 4> result, 
                    vtype<ctype<int64_t>, 4> input);

/*****************************************************************************
* VSTORE_PACKH_2SRC
*****************************************************************************/
template<typename ELEM_T_IN, typename ELEM_T_RES, size_t NELEM,
         typename = typename std::enable_if<!(std::is_floating_point<ELEM_T_IN>::value) 
                    && !(std::is_floating_point<ELEM_T_RES>::value)>::type,
         typename = typename std::enable_if<(std::is_signed<ELEM_T_IN>::value == std::is_signed<ELEM_T_RES>::value) 
                    && (std::is_unsigned<ELEM_T_IN>::value == std::is_unsigned<ELEM_T_RES>::value)>::type,
         typename = typename std::enable_if<(NELEM == 64/sizeof(ELEM_T_IN))>::type,
         typename = typename std::enable_if<(sizeof(ELEM_T_IN) >= sizeof(int16_t)) 
                    && (sizeof(ELEM_T_IN) == sizeof(ELEM_T_RES)*2)>::type>
void __vstore_packh_2src(vtype_ptr<ELEM_T_RES, NELEM * 2> result, 
                         vtype<ELEM_T_IN, NELEM> input1,
                         vtype<ELEM_T_IN, NELEM> input2)
{
    for(size_t i = 0; i < NELEM; i++)
    {
        (*result).s[i] = (input1.s[i]) >> (sizeof(ELEM_T_RES)*8); // Grabs high half
        (*result).s[i + NELEM] = (input2.s[i]) >> (sizeof(ELEM_T_RES)*8); // Grabs high half
    }
}

template<typename ELEM_T_IN, size_t NELEM,
         typename = typename std::enable_if<!(std::is_floating_point<ELEM_T_IN>::value)>::type, 
         typename = typename std::enable_if<(NELEM == 64/sizeof(ELEM_T_IN))>::type,
         typename = typename std::enable_if<(sizeof(ELEM_T_IN) == sizeof(int64_t))>::type> 
void __vstore_packh_2src(vtype_ptr<ELEM_T_IN, NELEM> result, 
                         vtype<ELEM_T_IN, NELEM> input1,
                         vtype<ELEM_T_IN, NELEM> input2)
{
    for (size_t i = 0; i < NELEM; i += 2)
    {
        (*result).s[i/2] = input1.s[i+1];
        (*result).s[(i + NELEM)/2] = input2.s[i+1]; 
    }
}

template<typename ELEM_T_IN, typename ELEM_T_RES, size_t NELEM,
         typename = typename std::enable_if<!(std::is_floating_point<ELEM_T_IN>::value) 
                    && !(std::is_floating_point<ELEM_T_RES>::value)>::type,
         typename = typename std::enable_if<(std::is_signed<ELEM_T_IN>::value == std::is_signed<ELEM_T_RES>::value)>::type, 
         typename = typename std::enable_if<(NELEM == 64/(sizeof(ELEM_T_IN) * 2))>::type,
         typename = typename std::enable_if<(sizeof(ELEM_T_IN) >= sizeof(int16_t)) 
                    && (sizeof(ELEM_T_IN) == sizeof(ELEM_T_RES)*2)>::type>
void __vstore_packh_2src(vtype_ptr<ctype<ELEM_T_RES>, NELEM * 2> result, 
                         vtype<ctype<ELEM_T_IN>, NELEM> input1,
                         vtype<ctype<ELEM_T_IN>, NELEM> input2)
{
    for(size_t i = 0; i < NELEM * 2; i++)
    {
        if (i % 2 == 0)
        {
            (*result).s[i/2].r = (input1.s[i/2].r) >> (sizeof(ELEM_T_RES)*8);
            (*result).s[i/2 + NELEM].r = 
                (input2.s[i/2].r) >> (sizeof(ELEM_T_RES)*8);
        }
        else
        {
            (*result).s[i/2].i = (input1.s[i/2].i) >> (sizeof(ELEM_T_RES)*8);
            (*result).s[i/2 + NELEM].i = 
                (input2.s[i/2].i) >> (sizeof(ELEM_T_RES)*8);
        }
    }
}

void __vstore_packh_2src(vtype_ptr<int64_t, 8> result, 
                         vtype<ctype<int64_t>, 4> input1,
                         vtype<ctype<int64_t>, 4> input2);

/*****************************************************************************
* VSTORE_PACKHS1
*****************************************************************************/
template<typename ELEM_T_IN, typename ELEM_T_RES, size_t NELEM,
         typename = typename std::enable_if<!(std::is_floating_point<ELEM_T_IN>::value) 
                    && !(std::is_floating_point<ELEM_T_RES>::value)>::type,
         typename = typename std::enable_if<(std::is_signed<ELEM_T_IN>::value == std::is_signed<ELEM_T_RES>::value) 
                    && (std::is_unsigned<ELEM_T_IN>::value == std::is_unsigned<ELEM_T_RES>::value)>::type,
         typename = typename std::enable_if<(NELEM == 64/sizeof(ELEM_T_IN))>::type,
         typename = typename std::enable_if<(sizeof(ELEM_T_IN) >= sizeof(int16_t)) 
                    && (sizeof(ELEM_T_IN) == sizeof(ELEM_T_RES)*2)>::type>
void __vstore_packhs1(vtype_ptr<ELEM_T_RES, NELEM> result,
                      vtype<ELEM_T_IN, NELEM> input)
{
    for(size_t i = 0; i < NELEM; i++)
    {
        ELEM_T_IN val = input.s[i] << (ELEM_T_IN)1;
        (*result).s[i] = (val) >> (sizeof(ELEM_T_RES)*8); // Grabs high half
    }
}

template<typename ELEM_T_IN, size_t NELEM,
         typename = typename std::enable_if<!(std::is_floating_point<ELEM_T_IN>::value)>::type, 
         typename = typename std::enable_if<(NELEM == 64/sizeof(ELEM_T_IN))>::type,
         typename = typename std::enable_if<(sizeof(ELEM_T_IN) == sizeof(int64_t))>::type> 
void __vstore_packhs1(vtype_ptr<ELEM_T_IN, NELEM/2> result, 
                      vtype<ELEM_T_IN, NELEM> input)
{
    for(size_t i = 0; i < NELEM; i += 2)
    {
        (*result).s[i/2]  = ((input.s[i+1]) << 1);
        (*result).s[i/2] |= ((input.s[i] >> 63) & 0x1);
    }
}

template<typename ELEM_T_IN, typename ELEM_T_RES, size_t NELEM,
         typename = typename std::enable_if<!(std::is_floating_point<ELEM_T_IN>::value) 
                    && !(std::is_floating_point<ELEM_T_RES>::value)>::type,
         typename = typename std::enable_if<(std::is_signed<ELEM_T_IN>::value == std::is_signed<ELEM_T_RES>::value)>::type, 
         typename = typename std::enable_if<(NELEM == 64/(sizeof(ELEM_T_IN) * 2))>::type,
         typename = typename std::enable_if<(sizeof(ELEM_T_IN) >= sizeof(int16_t)) 
                    && (sizeof(ELEM_T_IN) == sizeof(ELEM_T_RES)*2)>::type>
void __vstore_packhs1(vtype_ptr<ctype<ELEM_T_RES>, NELEM> result, 
                      vtype<ctype<ELEM_T_IN>, NELEM> input)
{
    for(size_t i = 0; i < NELEM * 2; i++)
    {
        if (i % 2 == 0)
        {
            ELEM_T_IN val = input.s[i/2].r << (ELEM_T_IN)1;
            (*result).s[i/2].r = (val) >> (sizeof(ELEM_T_RES)*8);
        }
        else
        {
            ELEM_T_IN val = input.s[i/2].i << (ELEM_T_IN)1;
            (*result).s[i/2].i = (val) >> (sizeof(ELEM_T_RES)*8);
        }
    }
}

void __vstore_packhs1(vtype_ptr<int64_t, 4> result, 
                      vtype<ctype<int64_t>, 4> input);



/*****************************************************************************
* VSTORE_PACKHS1_2SRC
*****************************************************************************/
template<typename ELEM_T_IN, typename ELEM_T_RES, size_t NELEM,
         typename = typename std::enable_if<!(std::is_floating_point<ELEM_T_IN>::value) 
                    && !(std::is_floating_point<ELEM_T_RES>::value)>::type,
         typename = typename std::enable_if<(std::is_signed<ELEM_T_IN>::value == std::is_signed<ELEM_T_RES>::value) 
                    && (std::is_unsigned<ELEM_T_IN>::value == std::is_unsigned<ELEM_T_RES>::value)>::type,
         typename = typename std::enable_if<(NELEM == 64/sizeof(ELEM_T_IN))>::type,
         typename = typename std::enable_if<(sizeof(ELEM_T_IN) >= sizeof(int16_t)) 
                    && (sizeof(ELEM_T_IN) == sizeof(ELEM_T_RES)*2)>::type>
void __vstore_packhs1_2src(vtype_ptr<ELEM_T_RES, NELEM * 2> result,
                           vtype<ELEM_T_IN, NELEM> input1,
                           vtype<ELEM_T_IN, NELEM> input2)
{
    for(size_t i = 0; i < NELEM; i++)
    {
        ELEM_T_IN val = input1.s[i] << (ELEM_T_IN)1;
        (*result).s[i] = (val) >> (sizeof(ELEM_T_RES)*8); // Grabs high half
        ELEM_T_IN val2 = input2.s[i] << (ELEM_T_IN)1;
        (*result).s[i + NELEM] = (val2) >> (sizeof(ELEM_T_RES)*8); // Grabs high half
    }
}

template<typename ELEM_T_IN, size_t NELEM,
         typename = typename std::enable_if<!(std::is_floating_point<ELEM_T_IN>::value)>::type, 
         typename = typename std::enable_if<(NELEM == 64/sizeof(ELEM_T_IN))>::type,
         typename = typename std::enable_if<(sizeof(ELEM_T_IN) == sizeof(int64_t))>::type> 
void __vstore_packhs1_2src(vtype_ptr<ELEM_T_IN, NELEM> result, 
                           vtype<ELEM_T_IN, NELEM> input1,
                           vtype<ELEM_T_IN, NELEM> input2)
{
    for (size_t i = 0; i < NELEM; i += 2)
    {
        (*result).s[i/2]  = (input1.s[i+1] << 1);
        (*result).s[i/2] |= ((input1.s[i] >> 63) & 0x1);
        (*result).s[(i + NELEM)/2]  = (input2.s[i+1] << 1);
        (*result).s[(i + NELEM)/2] |= ((input2.s[i] >> 63) & 0x1); 
    }
}

template<typename ELEM_T_IN, typename ELEM_T_RES, size_t NELEM,
         typename = typename std::enable_if<!(std::is_floating_point<ELEM_T_IN>::value) 
                    && !(std::is_floating_point<ELEM_T_RES>::value)>::type,
         typename = typename std::enable_if<(std::is_signed<ELEM_T_IN>::value == std::is_signed<ELEM_T_RES>::value)>::type, 
         typename = typename std::enable_if<(NELEM == 64/(sizeof(ELEM_T_IN) * 2))>::type,
         typename = typename std::enable_if<(sizeof(ELEM_T_IN) >= sizeof(int16_t)) 
                    && (sizeof(ELEM_T_IN) == sizeof(ELEM_T_RES)*2)>::type>
void __vstore_packhs1_2src(vtype_ptr<ctype<ELEM_T_RES>, NELEM * 2> result, 
                           vtype<ctype<ELEM_T_IN>, NELEM> input1,
                           vtype<ctype<ELEM_T_IN>, NELEM> input2)
{
    for(size_t i = 0; i < NELEM * 2; i++)
    {
        if (i % 2 == 0)
        {
            ELEM_T_IN val = input1.s[i/2].r << (ELEM_T_IN)1;
            (*result).s[i/2].r = (val) >> (sizeof(ELEM_T_RES)*8); 
            ELEM_T_IN val2 = input2.s[i/2].r << (ELEM_T_IN)1;
            (*result).s[i/2 + NELEM].r = (val2) >> (sizeof(ELEM_T_RES)*8); 
        }
        else
        {
            ELEM_T_IN val = input1.s[i/2].i << (ELEM_T_IN)1;
            (*result).s[i/2].i = (val) >> (sizeof(ELEM_T_RES)*8); 
            ELEM_T_IN val2 = input2.s[i/2].i << (ELEM_T_IN)1;
            (*result).s[i/2 + NELEM].i = (val2) >> (sizeof(ELEM_T_RES)*8); 
        }
    }
}

void __vstore_packhs1_2src(vtype_ptr<int64_t, 8> result, 
                           vtype<ctype<int64_t>, 4> input1,
                           vtype<ctype<int64_t>, 4> input2);

/*****************************************************************************
* VSTORE_PACK_BYTE
*****************************************************************************/
void __vstore_pack_byte(vtype_ptr<int8_t, 16> result, __int16 input);

void __vstore_pack_byte(vtype_ptr<uint8_t, 16> result, __uint16 input);

void __vstore_pack_byte(vtype_ptr<__cchar, 8> result, __cint8 input);

/*****************************************************************************
* VSTORE_PACK_BYTE_2SRC
*****************************************************************************/
void __vstore_pack_byte_2src(vtype_ptr<int8_t, 32> result, 
                             __int16 input1,
                             __int16 input2);

void __vstore_pack_byte_2src(vtype_ptr<uint8_t, 32> result, 
                              __uint16 input1,
                              __uint16 input2);

void __vstore_pack_byte_2src(vtype_ptr<__cchar, 16> result, 
                             __cint8 input1,
                             __cint8 input2);

/*****************************************************************************
* STORE_PREDICATE_[TYPE]
*****************************************************************************/
void __store_predicate_char(uint64_t* result, __vpred pred);

void __store_predicate_short(uint32_t* result, __vpred pred);

void __store_predicate_int(uint16_t* result, __vpred pred);

void __store_predicate_long(uint8_t* result, __vpred pred);

/*****************************************************************************
* ATOMIC COMPARE SWAP
*****************************************************************************/
int32_t __atomic_compare_swap(int32_t* ptr, int32_t src1, int32_t src2);

int64_t __atomic_compare_swap(int64_t* ptr, int64_t src1, int64_t src2);

/*****************************************************************************
* ATOMIC SWAP
*****************************************************************************/
int32_t __atomic_swap(int32_t* ptr, int32_t src1, int32_t src2);

int64_t __atomic_swap(int64_t* ptr, int64_t src1, int64_t src2);

/*****************************************************************************
* PREFETCH
*****************************************************************************/
void __prefetch(void* ptr, unsigned input);

/*****************************************************************************
* MFENCE
*****************************************************************************/
void __memory_fence(char input);

/*****************************************************************************
* MFENCEST
*****************************************************************************/
void __memory_fence_store(char input);

#endif /* C7X_HE_LDST_H */
