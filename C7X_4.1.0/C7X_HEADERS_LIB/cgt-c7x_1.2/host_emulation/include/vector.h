/*****************************************************************************/
/*  VECTOR.H v#####                                                          */
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
#ifndef VECTOR_H
#define VECTOR_H

#include <bitset>
#include <iostream>
#include <array>
#include <type_traits>
#include <functional>
#include <memory>

#include <cstdint>
#include <cstring>
#include <climits>

#include "c7x_c_funcs.h"
#include "c7x_auto_c_funcs.h"

// Unless otherwise defined, we default to little endian support
#ifndef __little_endian__
#define __little_endian__ 1
#endif
#ifndef __big_endian__
#define __big_endian__ 0
#endif

//-----------------------------------------------------------------------------
// Determines how many levels of nested accessors will be allowed.
//
// Currently set to 2 to minimize memory footprint. Compile-time is no longer
// affected by this value.
//---------------------------------------------------------------------------
#define __TI_MAX_ACCESSOR_DEPTH 2

namespace _c70_he_detail
{

/******************************************************************************
* Forward declaration of the vtype class
******************************************************************************/
template <typename ELEM_T, size_t NELEM>
class vtype;

/******************************************************************************
* Forward declaration of the ctype class
******************************************************************************/
template<typename ELEM_T>
class ctype;

/******************************************************************************
* Helpful alias used to detect if a type is a complex type
******************************************************************************/
template <typename TEST_T, typename RET_T>
using enable_if_cmplx_t = std::enable_if_t<(!std::is_arithmetic<TEST_T>::value),
                                            RET_T>;

/******************************************************************************
* Helper functions to interface with the C functional description.
******************************************************************************/

#if __big_endian__
// Swaps based on the type of the actual value within the 64bit container
template <typename T> uint64_t swap_endian_uint64(uint64_t val)
{
    switch (sizeof(T))
    {
        case 1:
            val = (val & 0x00FF00FF00FF00FF) << 8  |
                  (val & 0xFF00FF00FF00FF00) >> 8;
        case 2:
            val = (val & 0x0000FFFF0000FFFF) << 16 |
                  (val & 0xFFFF0000FFFF0000) >> 16;
        case 4:
            val = (val & 0x00000000FFFFFFFF) << 32 |
                  (val & 0xFFFFFFFF00000000) >> 32;
    }

    return val;
}
#endif

// Converts a vreg_t to another class whose elements are referenced via a
// reference wrapper array.
template <class ACCESS_T, typename ELEM_T, size_t NELEM>
std::enable_if_t<std::is_arithmetic<ELEM_T>::value>
init_from_vreg_t(const vreg_t &src, ACCESS_T &dst)
{
    for (uint32_t i = 0; i < NELEM; i++)
    {
        // Figure out which double-word the value is in. Multiply the index
        // by 2 to get the word index, which is the expected input for
        // get/put functions.
        uint32_t vindex = ((sizeof(ELEM_T) * i) / sizeof(uint64_t)) * 2;

        // Get the containing double-word, and then mask/shift to get the
        // bits we actually want
        uint64_t val = 0;
        get_unsigned_value(src, val, vindex);

        // Figure out the offset within the containing double-word
        uint64_t lane_bit_offset =
            ((sizeof(ELEM_T) * i) % sizeof(uint64_t)) * CHAR_BIT;

        if (lane_bit_offset != 0)
        {
            uint64_t mask = ((uint64_t)1 << lane_bit_offset) - 1;
            val = (val >> lane_bit_offset) & mask;
        }

#if __big_endian__
        val = swap_endian_uint64<ELEM_T>(val);
#endif

        // memcpy avoids strict aliasing issues when type-punning
        memcpy(&dst.s[i], &val, sizeof(ELEM_T));
    }
}

// Converts a vreg_t to another class whose elements are referenced via a
// reference wrapper array. Complex version.
template <class ACCESS_T, typename ELEM_T, size_t NELEM>
enable_if_cmplx_t<ELEM_T, void>
init_from_vreg_t(const vreg_t &src, ACCESS_T &dst)
{
    uint32_t vec_count = 0;
    for (uint32_t i = 0; i < NELEM; i++)
    {
        // Figure out which double-word the value is in. Multiply the index
        // by 2 to get the word index, which is the expected input for
        // get/put functions.

        // Grab the index where each value is stored
        uint32_t vindex_imag = ((sizeof(typename ELEM_T::ELEM_TYPE)
                                   * vec_count) / sizeof(uint64_t)) * 2;
        uint32_t vindex_real = ((sizeof(typename ELEM_T::ELEM_TYPE)
                                   * (vec_count + 1)) / sizeof(uint64_t)) * 2;

        // Get the containing double-word, and then mask/shift to get the
        // bits we actually want. These indicies can be the same,
        // it just means that the values are in the same double word
        uint64_t val_imag = 0;
        uint64_t val_real = 0;
        get_unsigned_value(src, val_imag, vindex_imag);
        get_unsigned_value(src, val_real, vindex_real);

        // Figure out the offset within the containing double-word
        uint64_t lane_bit_offset_imag =
            ((sizeof(typename ELEM_T::ELEM_TYPE) * vec_count)
            % sizeof(uint64_t)) * CHAR_BIT;

        uint64_t lane_bit_offset_real =
            ((sizeof(typename ELEM_T::ELEM_TYPE) * (vec_count + 1))
            % sizeof(uint64_t)) * CHAR_BIT;

        // If multiple values are contained within the double word, use mask to
        // retrieve correct bits
        if (lane_bit_offset_imag != 0)
        {
            uint64_t mask_imag = ((uint64_t)1 << lane_bit_offset_imag) - 1;
            val_imag = (val_imag >> lane_bit_offset_imag) & mask_imag;
        }
        if (lane_bit_offset_real != 0)
        {
            uint64_t mask_real = ((uint64_t)1 << lane_bit_offset_real) - 1;
            val_real = (val_real >> lane_bit_offset_real) & mask_real;
        }

        typename ELEM_T::ELEM_TYPE val_i_cast;
        typename ELEM_T::ELEM_TYPE val_r_cast;

#if __big_endian__
        val_imag = swap_endian_uint64<typename ELEM_T::ELEM_TYPE>(val_imag);
        val_real = swap_endian_uint64<typename ELEM_T::ELEM_TYPE>(val_real);
#endif

        // memcpy avoids strict aliasing issues when type-punning
        memcpy(&val_i_cast, &val_imag, sizeof(typename ELEM_T::ELEM_TYPE));
        memcpy(&val_r_cast, &val_real, sizeof(typename ELEM_T::ELEM_TYPE));

        dst.s[i] = ELEM_T(val_r_cast, val_i_cast);

        vec_count += 2;
    }
}

// Converts an object whose elements are referenced via a reference wrapper
// array into a vreg_t for use by the C functional description.
template<class ACCESS_T, typename ELEM_T, size_t NELEM>
typename std::enable_if_t<std::is_arithmetic<ELEM_T>::value, vreg_t>
convert_to_vreg_t(const ACCESS_T &src)
{
    vreg_t res;

    for (uint32_t i = 0; i < NELEM; i++)
    {
        // Figure out which double-word the value is in. Multiply the index
        // by 2 to get the word index, which is the expected input for
        // get/put functions.
        uint32_t vindex = ((sizeof(ELEM_T) * i) / sizeof(uint64_t)) * 2;

        // Get the containing double-word, and then mask/shift to modify
        // the bits we actually want to touch
        uint64_t val;
        get_unsigned_value(res, val, vindex);

        // Figure out the offset within the containing double-word
        uint64_t lane_bit_offset =
            ((sizeof(ELEM_T) * i) % sizeof(uint64_t)) * CHAR_BIT;

        // Generate masks to allow us to reconstruct the value with the
        // modified lane dropped in
        uint64_t val_mask = 0;
        for (uint64_t j = 0; j < sizeof(uint64_t) * CHAR_BIT; j += CHAR_BIT)
        {
            if (j < lane_bit_offset ||
                j >= lane_bit_offset + sizeof(ELEM_T) * CHAR_BIT)
            {
                val_mask |= (((uint64_t)1 << CHAR_BIT) - 1) << j;
            }
        }
        uint64_t lane_mask = ~val_mask;

        val = (val & val_mask) |
              (((uint64_t)src.s[i] << lane_bit_offset) & lane_mask);

        put_unsigned_value(res, val, vindex);
    }

    return res;
}

// Converts an object whose elements are referenced via a reference wrapper
// array into a vreg_t for use by the C functional description. Complex version.
template<class ACCESS_T, typename ELEM_T, size_t NELEM>
enable_if_cmplx_t<ELEM_T, vreg_t> convert_to_vreg_t(const ACCESS_T &src)
{
    vreg_t res;

    vtype<typename ELEM_T::ELEM_TYPE, NELEM * 2> vec_type =
        vtype<typename ELEM_T::ELEM_TYPE, NELEM * 2>(0);

    size_t vec_count = 0;
    for (uint32_t i = 0; i < NELEM ; i++)
    {
        // Grab ctype at index
        ELEM_T temp = src.s[i];
        vec_type.s[vec_count] = temp.i;
        vec_type.s[vec_count + 1] = temp.r;
        vec_count += 2;
    }

    res = convert_to_vreg_t<vtype<typename ELEM_T::ELEM_TYPE, NELEM * 2>,
                            typename ELEM_T::ELEM_TYPE, NELEM * 2>(vec_type);

    return res;
}

// Converts a complex element object whose elements are referenced via a
// reference wrapper array into a vreg_t for use by the C functional description.
template<typename ELEM_T>
vreg_t convert_ctype_to_vreg_t(const ctype<ELEM_T> &src)
{
    vreg_t res;

    vtype<ELEM_T, 2> vec_type = vtype<ELEM_T, 2>(0);

    vec_type.s[0] = src.i;
    vec_type.s[1] = src.r;

    res = convert_to_vreg_t<vtype<ELEM_T, 2>, ELEM_T, 2>(vec_type);

    return res;
}

// Converts a vreg_t to a complex element whose elements are referenced via a
// reference wrapper array.
template <typename ELEM_T>
void init_ctype_from_vreg_t(const vreg_t &src, ctype<ELEM_T> &dst)
{
        // Grab where each value is (which index)
        uint32_t vindex_imag = ((sizeof(ELEM_T) * 0) / sizeof(uint64_t)) * 2;
        uint32_t vindex_real = ((sizeof(ELEM_T) * 1) / sizeof(uint64_t)) * 2;

        uint64_t val_imag = 0;
        uint64_t val_real = 0;
        get_unsigned_value(src, val_imag, vindex_imag);
        get_unsigned_value(src, val_real, vindex_real);

        // Figure out the offset within the containing double-word
        uint64_t lane_bit_offset_imag =
            ((sizeof(ELEM_T) * 0) % sizeof(uint64_t)) * CHAR_BIT;

        uint64_t lane_bit_offset_real =
            ((sizeof(ELEM_T) * 1) % sizeof(uint64_t)) * CHAR_BIT;


        // If multiple values are contained within the double word,
        // use mask to retrieve correct bits
        if (lane_bit_offset_imag != 0)
        {
            uint64_t mask_imag = ((uint64_t)1 << lane_bit_offset_imag) - 1;
            val_imag = (val_imag >> lane_bit_offset_imag) & mask_imag;
        }
        if (lane_bit_offset_real != 0)
        {
            uint64_t mask_real = ((uint64_t)1 << lane_bit_offset_real) - 1;
            val_real = (val_real >> lane_bit_offset_real) & mask_real;
        }

        ELEM_T val_i_cast;
        ELEM_T val_r_cast;

#if __big_endian__
        val_imag = swap_endian_uint64<ELEM_T>(val_imag);
        val_real = swap_endian_uint64<ELEM_T>(val_real);
#endif

        // memcpy avoids strict aliasing issues when type-punning
        memcpy(&val_i_cast, &val_imag, sizeof(ELEM_T));
        memcpy(&val_r_cast, &val_real, sizeof(ELEM_T));

        dst.i = val_i_cast;
        dst.r = val_r_cast;
}

template<typename ELEM_T, size_t NELEM>
class vtype_ptr;

template<typename ELEM_T>
class ctype_ptr;

/******************************************************************************
* ENUM for all valid access types
******************************************************************************/
enum class ACCESS_TYPE { NORMAL, LO, HI, EVEN, ODD, REAL, IMAG };

// Create struct here so that we don't have run-time
// overhead from passing access type as parameter
template<ACCESS_TYPE ATYPE>
struct access_types { };

//-----------------------------------------------------------------------------
// ref_holder is used to construct an array of reference wrappers to a specific
// set of elements chosen based on ACCESS_TYPE. The accessible class derives
// from the ref_holder class, meaning that all accessibles (and thus all
// vtypes) will have an array of reference wrappers (refs_m). All index
// calculations are handled during compile time, meaning that all references
// are set up and ready to use without any run-time overhead.
//
// The complex-type variant of ref_holder has to save off copies of ctype_ptr
// pointers it allocates to a vector so that the objects can be freed when the
// object is destroyed.  To do this, we use a base class (ref_holder_base) to
// hold the vector that is only enabled when holding a complex vector.
//-----------------------------------------------------------------------------

template <typename ELEM_T, typename Enable=void>
class ref_holder_base;

template <typename ELEM_T>
class ref_holder_base<ELEM_T, enable_if_cmplx_t<ELEM_T,void>>
{
    public:
        std::vector<ctype_ptr<typename ELEM_T::ELEM_TYPE>> cptrs;
};

template <typename ELEM_T>
class ref_holder_base<ELEM_T,
      typename std::enable_if_t<std::is_arithmetic<ELEM_T>::value>>
{ };

template <typename ELEM_T, size_t NELEM>
class ref_holder : public ref_holder_base<ELEM_T>
{
public:

    // Constructor used during initialization of a vtype. Creates a reference
    // wrapper array with references to data found directly in vtype's "data"
    // member array.
    template<size_t... Is>
    ref_holder<ELEM_T, NELEM>(std::array<ELEM_T, NELEM> &data,
                              access_types<ACCESS_TYPE::NORMAL>,
                              std::index_sequence<Is...>)
                                  : refs_m({(data[Is])...})  { }

    // Constructor used during initialization of a vtype. Creates a reference
    // wrapper array with references found in a higher level reference wrapper
    // array.
    template<size_t... Is>
    ref_holder<ELEM_T, NELEM>(std::array<std::reference_wrapper<ELEM_T>, NELEM> &refs,
                              access_types<ACCESS_TYPE::NORMAL>,
                              std::index_sequence<Is...>)
                                  : refs_m({(refs[Is])...})  { }

    // Constructor used during initialization of a LO accessible. Creates
    // a reference wrapper array with references found in a higher level
    // reference wrapper array.
    template<size_t... Is>
    ref_holder<ELEM_T, NELEM>(std::array<std::reference_wrapper<ELEM_T>, NELEM*2> &refs,
                              access_types<ACCESS_TYPE::LO>,
                              std::index_sequence<Is...>)
                                  : refs_m({(refs[Is])...})  { }

    // Constructor used during initialization of a HI accessible
    template<size_t... Is>
    ref_holder<ELEM_T, NELEM>(std::array<std::reference_wrapper<ELEM_T>, NELEM*2> &refs,
                              access_types<ACCESS_TYPE::HI>,
                              std::index_sequence<Is...>)
                                  : refs_m({(refs[Is + NELEM])...})  { }

    // Constructor used during initialization of an EVEN accessible
    template<size_t... Is>
    ref_holder<ELEM_T, NELEM>(std::array<std::reference_wrapper<ELEM_T>, NELEM*2> &refs,
                              access_types<ACCESS_TYPE::EVEN>,
                              std::index_sequence<Is...>)
                                  : refs_m({(refs[2*Is])...})  { }

    // Constructor used during initialization of an ODD accessible
    template<size_t... Is>
    ref_holder<ELEM_T, NELEM>(std::array<std::reference_wrapper<ELEM_T>, NELEM*2> &refs,
                              access_types<ACCESS_TYPE::ODD>,
                              std::index_sequence<Is...>)
                                  : refs_m({(refs[2*Is + 1])...})  { }

    // Constructor used during initialization of a REAL accessible
    template<size_t... Is>
    ref_holder<ELEM_T, NELEM>(std::array<std::reference_wrapper<ctype<ELEM_T>>, NELEM> &refs,
                              access_types<ACCESS_TYPE::REAL>,
                              std::index_sequence<Is...>)
                                  : refs_m({(*(refs[Is].get().get_default_data_ptr()))...})  { }

    // Constructor used during initialization of an IMAG accessible
    template<size_t... Is>
    ref_holder<ELEM_T, NELEM>(std::array<std::reference_wrapper<ctype<ELEM_T>>, NELEM> &refs,
                              access_types<ACCESS_TYPE::IMAG>,
                              std::index_sequence<Is...>)
                                  : refs_m({(*(refs[Is].get().get_default_data_ptr() + 1 ))...})  { }

    // Constructor used during initialization of a vtype whose data is located
    // as a consecutive set of elements in memory.  This constructor
    // initializes refs_m to contain reference wrappers to that data in memory
    // instead of the data found in vtype's "data" member array. This
    // constructor is used for vectors with scalar element types and complex
    // element types (when constructed ctype objects exist in memory).
    template<size_t... Is>
    ref_holder<ELEM_T, NELEM>(ELEM_T* ptr,
                              access_types<ACCESS_TYPE::NORMAL>,
                              std::index_sequence<Is...>)
                                  : refs_m({init_from_vtype_ptr_ref(ptr, Is)...}) { }

    // Constructor used during initialization of a vtype whose data is located
    // as a consecutive set of complex components in memory. In this case, the
    // elements in memory are pairs of scalars that together represent a
    // complex element. A pointer is passed to this constructor and initializes
    // refs_m to contain reference wrappers to the data in memory instead of
    // the data found in vtype's "data" member array.
    template<size_t... Is, typename ELEM_DUMMY = ELEM_T,
             typename = enable_if_cmplx_t<ELEM_DUMMY, void>>
    ref_holder<ELEM_T, NELEM>(typename ELEM_DUMMY::ELEM_TYPE* ptr,
                              access_types<ACCESS_TYPE::NORMAL>,
                              std::index_sequence<Is...>)
                                  : refs_m({init_from_vtype_ptr_ref_comp(ptr, Is)...}) { }

    private:
        // Methods used to obtain ELEM_T references from data pointers

        // Grab constructed ctypes or scalar element types from memory
        ELEM_T& init_from_vtype_ptr_ref(ELEM_T* ptr, size_t index)
        {
            return *(ptr + index);
        }

        // Construct a ctype from pairs of component-type scalars that represent
        // a complex element.
        template<typename ELEM_DUMMY = ELEM_T,
                 typename = enable_if_cmplx_t<ELEM_DUMMY, void>>
        ELEM_T& init_from_vtype_ptr_ref_comp(typename ELEM_DUMMY::ELEM_TYPE* ptr, size_t index)
        {
            // ELEM_T is ctype<built in type>
            ctype_ptr<typename ELEM_DUMMY::ELEM_TYPE> cptr(ptr, 2*index);

            // Keep active pointers to the constructed ctypes so they can be
            // freed during object destruction. The ctype_ptr in this function
            // scope will be destroyed, leaving ctype object ownership to the
            // saved copy.
            this->cptrs.push_back(cptr);

            return *cptr;
        }

    public:
        // Reference wrapper array member
        std::array<std::reference_wrapper<ELEM_T>, NELEM> refs_m;
};

/******************************************************************************
* Forward declaration of the accessible object interface for use by vtype
******************************************************************************/
template <typename ELEM_T, size_t NELEM, size_t ACCESS_DEPTH>
class accessible;

// Class vtype is the high-level abstraction for OpenCL vector types. It is
// instantiated with an element type and a number of elements. The element
// types should be those found in stdint so that bit widths are guaranteed.
//
// e.g.: char64 = vtype<int8_t, 64>
template <typename ELEM_T, size_t NELEM>
class vtype : public accessible<ELEM_T, NELEM, 0>
{
    using ACCESS_T = accessible<ELEM_T, NELEM, 0>;

public:
    template <size_t OTHER_DEPTH>
    using EQUIV_ACCESS_T = accessible<ELEM_T, NELEM, OTHER_DEPTH>;

/******************************************************************************
* Fields to get ELEM_T and NELEM information of this vtype
******************************************************************************/
public:
    using ELEM_TYPE = ELEM_T;
    using PTR_TYPE = vtype_ptr<ELEM_T, NELEM>;

    static constexpr size_t NUM_ELEM = NELEM;

/******************************************************************************
* Construction of vector objects
******************************************************************************/
public:
    // OpenCL vector literal syntax constructor, see init_helper for more.
    // e.g.: int4(int2(1, 2), 3, 4)
    template<class ...INITS>
    explicit vtype(const INITS &...inits) :
        ACCESS_T(data, access_types<ACCESS_TYPE::NORMAL>())
    {
        init_helper<0>(inits...);
    }

    // Constructor to initialize vtype from an accessible (vtype.[lo|hi|even|odd])
    template<size_t ADEPTH>
    vtype(accessible<ELEM_T, NELEM, ADEPTH> &a) :
        ACCESS_T(data, access_types<ACCESS_TYPE::NORMAL>())
    {
        for(size_t i = 0 ; i < NELEM; i++) { (*this).s[i] = a.s[i]; }
    }

    // Constructor to initialize vtype from a pointer to an accessible using
    // refs from the accessible. This is useful in creating a pointer to a
    // subvector using a subvector accessor.
    template<size_t ADEPTH>
    explicit vtype(accessible<ELEM_T, NELEM, ADEPTH> *a) :
        ACCESS_T(a->s.refs_s, access_types<ACCESS_TYPE::NORMAL>()) { }

    // Constructor to initialize a vtype from another vtype
    vtype(const vtype &v) : ACCESS_T(data, access_types<ACCESS_TYPE::NORMAL>())
    {
        for(size_t i = 0 ; i < NELEM; i++) { (*this).s[i] = v.s[i]; }
    }

    // Constructor to initialize vtype from a memory location
    // This is only done via an intrinsic and should be not be used externally.
    // In this case, we need to update the array of reference wrappers to
    // reference elements found in a memory location. When a vtype is
    // constructed from this, the "data" member array is not modified and
    // remains as an array of 0's, which is its default state.
    explicit vtype(ELEM_T* ptr) :
             ACCESS_T(ptr, access_types<ACCESS_TYPE::NORMAL>()),
             mem_ptr_based(true) { }

    // Constructor to initialize vtype from a complex component-type pointer.
    // Similar to constructing from a memory address but the data pointer is
    // passed directly to differentiate from an ELEM_T*
    template<typename ELEM_DUMMY = ELEM_T,
             typename = enable_if_cmplx_t<ELEM_DUMMY, void>>
    explicit vtype(typename ELEM_DUMMY::ELEM_TYPE* ptr) :
             ACCESS_T(ptr, access_types<ACCESS_TYPE::NORMAL>()),
             mem_ptr_based(true) { }

    // Default constructor
    vtype() : ACCESS_T(data, access_types<ACCESS_TYPE::NORMAL>())
    {
        // Initialize differently based on what the element type is
        initialize_default<ELEM_T>();
    }

private:
    // Recursive instantiations

    // The next initializer in the pack is a singular element
    // e.g.: (int4)(... 4, ...)
    // Add it to the current index and recurse.
    template<size_t curr_idx, class ...INITS>
    void init_helper(const ELEM_T &next, const INITS &...inits)
    {
        static_assert(curr_idx < NELEM, "Illegal vector init, too many");

        (*this).s[curr_idx] = next;

        init_helper<curr_idx + 1>(inits...);
    }

    // The next two initializers in the pack represent a single complex element
    // e.g.: (cint4)(... 4, 5, ...)
    // Add it to the current index and recurse.
    template<size_t curr_idx, typename DUMMY = ELEM_T, class ...INITS>
    enable_if_cmplx_t<DUMMY, void>
    init_helper(const typename DUMMY::ELEM_TYPE &next,
                const typename DUMMY::ELEM_TYPE &next1, const INITS &...inits)
    {
        static_assert(curr_idx < NELEM, "Illegal vector init, too many");

        ELEM_T temp = ELEM_T(next, next1);

        (*this).s[curr_idx] = temp;

        init_helper<curr_idx + 1>(inits...);
    }

    // The next initializer is a vector
    // e.g.: (int8)(... int4(...), ...)
    // Add each element of the vector and recurse.
    template<size_t curr_idx, size_t OTHER_NELEM, size_t DEPTH, class ...INITS>
    void init_helper(
        const accessible<ELEM_T, OTHER_NELEM, DEPTH> &next,
        const INITS &...inits)
    {
        static_assert(curr_idx + OTHER_NELEM - 1 < NELEM,
                      "Illegal vector init, too many");

        // NOTE: when dealing with accessibles, use S to grab actual data
        for (size_t i = 0; i < OTHER_NELEM; i++)
            (*this).s[i + curr_idx] = next.s[i];

        init_helper<curr_idx + OTHER_NELEM>(inits...);
    }

    // The only initializer is a vreg_t
    // Convert the vreg_t into its target vector representation.
    template <size_t curr_idx>
    void init_helper(const vreg_t &v)
    {
        static_assert(curr_idx == 0, "Accessor created illegal vector init.");
        init_from_vreg_t<vtype<ELEM_T, NELEM>, ELEM_T, NELEM>(v, *this);
    }

    // Termination
    // When we've run out of things to process, ensure we've packed the full
    // vector, then we're done.
    template <size_t curr_idx>
    void init_helper()
    {
        static_assert(curr_idx == NELEM || curr_idx == 1,
                      "Illegal vector init, too few");

        // OpenCL vector literal duplication constructor
        // e.g.: int4(1)
        if (curr_idx == 1)
            for(size_t i = 0; i < NELEM; i++)
                (*this).s[i] = (*this).s[0];
    }

    // Break up to allow for different initializations based on type of ELEM_T
    template <typename E_TYPE>
    enable_if_cmplx_t<E_TYPE, void> initialize_default()
    {
            // Calls default ctype constructor
            data.fill(E_TYPE());
    }

    template <typename E_TYPE>
    typename std::enable_if_t<std::is_arithmetic<E_TYPE>::value> initialize_default()
    {
            data.fill((E_TYPE)(0));
    }

public:
    // Equals operator between two vtypes
    vtype<ELEM_T, NELEM> &operator=(const vtype<ELEM_T, NELEM> &rhs)
    {
        for (size_t i = 0; i < NELEM; i++)
        {
            (*this).s[i] = rhs.s[i];
        }
        return *this;
    }

//Explicit? (put explicit before)
    operator vreg_t() const
    {
        return convert_to_vreg_t<vtype<ELEM_T, NELEM>, ELEM_T, NELEM>(*this);
    }

    // Overload address-of operator
    vtype_ptr<ELEM_T, NELEM> operator &()
    {
        // Objects that inherit enable_shared_from_this<> must ensure that any
        // corresponding instantiated object of that type is owned by a shared
        // pointer.  In this case, it is the base class, accessible, that
        // inherits enable_shared_from_this<>.
        //
        // Problem: There are cases in which objects that inherit
        // enabled_shared_from_this<> are not dynamically-allocated and
        // therefore are not owned by a shared pointer. This is the case for
        // statically-allocated and automatically-allocated objects.  You can't
        // return a shared_ptr<> (actually a weak_ptr<>) to the current object
        // if it is not already owned by a shared_ptr<>. This is a known issue.
        //
        // Best Solution: Boost resolves a similar issue by creating a
        // temporary shared pointer with a custom null-deleter to manage a
        // shared_ptr to the object and avoid destroying the object when the
        // shared_ptr goes out of scope.  We will need to do something similar.
        // The temporary shared pointer owns the object if there are no other
        // shared pointers. The custom null-deleter ensures that the object
        // isn't destroyed when the temporary pointer goes out of function
        // scope. When the temporary pointer goes out of scope, the reference
        // count is properly decremented so that the object doesn't leak later.
        const auto wptr = std::shared_ptr<vtype<ELEM_T, NELEM>>(this,
                                                  [](vtype<ELEM_T, NELEM>*){});

        return vtype_ptr<ELEM_T, NELEM>(this->shared_from_this());
    }

/******************************************************************************
* Public member accessor methods
******************************************************************************/
public:

    // Return pointer to vector's underlying memory
    //
    // Important Note: The object's "underlying memory" depends on how the
    // object was constructed.  If this vector type object was constructed
    // based on a pointer to memory, then effectively it always references that
    // memory (via "struct s_impl<> s" in class accessible), and a pointer to
    // that memory should be returned here.  On the other hand, if this
    // object was not constructed based on a pointer to memory, then it
    // always references its internal "data" array below.  Here we return the
    // address to which "s" refers since that will always refer to the right
    // location.
    //
    // Previously, there was a defect where the location of the instance's
    // underlying "data" array was always returned. This was not correct for
    // cases in which the instance was constructed based on a pointer to
    // memory. (See CODEGEN-6186)

    // Return non-complex element scalar pointer (e.g. int* from int4)
    template <typename ED = ELEM_T,
        typename = std::enable_if_t<std::is_arithmetic<ED>::value>>
    ELEM_T* get_data_arr_ptr()
    {
        return &this->s[0];
    }

    // Return complex element scalar component pointer (e.g. int* from cint4)
    template <typename ED = ELEM_T, typename = enable_if_cmplx_t<ED, void>>
    typename ED::ELEM_TYPE* get_data_arr_ptr()
    {
        if (!is_mem_ptr_based())
            throw std::runtime_error("Cannot convert complex vector pointer"
                   " to scalar pointer: Vector was not previously initialized"
                   " using a scalar pointer");

        return (typename ED::ELEM_TYPE*)(&this->s[0]);
    }

    // Return complex type element pointer (e.g. cint_ptr from cint4)
    template <typename ED = ELEM_T, typename = enable_if_cmplx_t<ED, void>>
    ctype_ptr<typename ED::ELEM_TYPE> get_cdata_arr_ptr()
    {
        return &this->s[0];
    }

    // Was this vector constructed based on a pointer to memory?
    bool is_mem_ptr_based() { return mem_ptr_based; }

/******************************************************************************
* Private member data
******************************************************************************/
private:
    // Data array which represents lanes in the vector type.
    std::array<ELEM_T, NELEM> data;
    bool mem_ptr_based = false;
};


/******************************************************************************
* Class definition for the complex element type.
******************************************************************************/

// Class ctype is the high-level abstraction for complex element types. It is
// instantiated with an element type. The element types should be those found
// in stdint so that bit widths are guaranteed.
//
// e.g.: cchar = ctype<int8_t>
template <typename ELEM_T>
class ctype : public std::enable_shared_from_this<ctype<ELEM_T>>
{
/******************************************************************************
* Fields to get ELEM_T and NELEM information of this ctype
******************************************************************************/
public:
    using ELEM_TYPE = ELEM_T;
    static constexpr size_t NUM_ELEM = 1;

    using PTR_TYPE = ctype_ptr<ELEM_T>;

    using SHARED_T = std::enable_shared_from_this<ctype<ELEM_T>>;

/******************************************************************************
* Construction of complex element objects
******************************************************************************/
public:
    // Constructor to create a ctype from a real and imaginary component
    explicit ctype(const ELEM_T &real, const ELEM_T &imag) :
        complex_refs({data[0], data[1]}), r(complex_refs[0].get()), i(complex_refs[1].get())
    {
        complex_refs[0].get() = real;
        complex_refs[1].get() = imag;
    }

    // Constructor to initialize a ctype from another ctype
    ctype(const ctype<ELEM_T> &cmplx) :
       SHARED_T(),
       complex_refs({data[0], data[1]}), r(complex_refs[0].get()), i(complex_refs[1].get())
    {
        (*this).complex_refs[0].get() = cmplx.r;
        (*this).complex_refs[1].get() = cmplx.i;
    }

    // Constructor to create a ctype from a pointer
    // This constructor should not be used externally
    explicit ctype(ELEM_T* &ptr, const size_t &index = 0):
       mem_ptr_based(true),
       complex_refs({*(ptr + index), *(ptr + index + 1)}), r(complex_refs[0].get()), i(complex_refs[1].get()) { }

    // Constructor to initialize a ctype from a vreg_t
    explicit ctype(const vreg_t &src) :
        complex_refs({data[0], data[1]}), r(complex_refs[0].get()), i(complex_refs[1].get())
    {
        init_ctype_from_vreg_t(src, *this);
    }

    // Default constructor
    ctype() : complex_refs({data[0], data[1]}), r(complex_refs[0].get()), i(complex_refs[1].get())
    {
        complex_refs[0].get() = 0;
        complex_refs[1].get() = 0;
    }

/******************************************************************************
* Public member accessor methods
******************************************************************************/
public:
    // Return pointer to ctype's underlying memory
    //
    // Important Note: The object's "underlying memory" depends on how the
    // object was constructed. If this complex type object was constructed
    // based on a pointer to memory, then effectively it always references that
    // memory (via "complex_refs"), and a pointer to that memory should be
    // returned here.  On the other hand, if this object was not constructed
    // based on a pointer to memory, then it always references its internal
    // "data" array below.  Here we return the address to which "complex_refs"
    // refers since that will always refer to the right location.
    //
    // Previously, there was a defect where the location of the instance's
    // underlying "data" array was always returned. This was not correct for
    // cases in which the instance was constructed based on a pointer to
    // memory. (See CODEGEN-6186)
    ELEM_TYPE* get_data_arr_ptr()
    {
        return &(complex_refs[0].get());
    }

    // This is used during default construction of a ctype
    ELEM_TYPE* get_default_data_ptr()
    {
        return data.data();
    }

    // Was this vector constructed based on a pointer to memory?
    bool is_mem_ptr_based() { return mem_ptr_based; }

/******************************************************************************
* Private member data
******************************************************************************/
private:
    std::array<ELEM_T, 2> data;
    bool mem_ptr_based = false;

/******************************************************************************
* Public member data
******************************************************************************/
public:
    std::array<std::reference_wrapper<ELEM_T>, 2> complex_refs;

    ELEM_T &r, &i;

public:
    void print() const
    {
        using conv_t =
            typename std::conditional<(std::is_integral<ELEM_T>::value &&
                                sizeof(ELEM_T) < sizeof(int32_t)),
                                int32_t, ELEM_T>::type;

        std::cout << "{R = " << (conv_t)r << ", I = " << (conv_t)i << "}";
    }

/******************************************************************************
* Ctype Operators
******************************************************************************/

public:
    // Overload address-of operator
    ctype_ptr<ELEM_T> operator &()
    {
        // Objects that inherit enable_shared_from_this<> must ensure that any
        // corresponding instantiated object of that type is owned by a shared
        // pointer.
        //
        // Problem: There are cases in which objects that inherit
        // enabled_shared_from_this<> are not dynamically-allocated and
        // therefore are not owned by a shared pointer. This is the case for
        // statically-allocated and automatically-allocated objects.  You can't
        // return a shared_ptr<> (actually a weak_ptr<>) to the current object
        // if it is not already owned by a shared_ptr<>. This is a known issue.
        //
        // Best Solution: Boost resolves a similar issue by creating a
        // temporary shared pointer with a custom null-deleter to manage a
        // shared_ptr to the object and avoid destroying the object when the
        // shared_ptr goes out of scope.  We will need to do something similar.
        // The temporary shared pointer owns the object if there are no other
        // shared pointers. The custom null-deleter ensures that the object
        // isn't destroyed when the temporary pointer goes out of function
        // scope. When the temporary pointer goes out of scope, the reference
        // count is properly decremented so that the object doesn't leak later.
        const auto wptr = std::shared_ptr<ctype<ELEM_T>>(this,
                                                  [](ctype<ELEM_T>*){});

        return ctype_ptr<ELEM_T>(this->shared_from_this());
    }

    // Equals operator between two ctypes
    ctype<ELEM_T> &operator=(const ctype<ELEM_T> &rhs)
    {
        (*this).complex_refs[0].get() = rhs.r;
        (*this).complex_refs[1].get() = rhs.i;
        return (*this);
    }

    // Cast overload to convert a ctype to a vreg_t
    explicit operator vreg_t()
    {
        return convert_ctype_to_vreg_t<ELEM_T>(*this);
    }

    // Pre-increment
    ctype<ELEM_T> operator++()
    {
        static_assert(!std::is_same<ELEM_T, float>::value
                      && !std::is_same<ELEM_T, double>::value,
		      "Error, float and double vector pre-increment is not supported");
        r = r + 1;
	return *this;
    }

    // Post-increment
    ctype<ELEM_T> operator++(int)
    {
        static_assert(!std::is_same<ELEM_T, float>::value
                      && !std::is_same<ELEM_T, double>::value,
                      "Error, float and double vector post-increment is not supported");
        ctype<ELEM_T> copy;
        copy.r = r;
        ++*this;
        return copy;
    }

    // Pre-decrement
    ctype<ELEM_T> operator--()
    {
        static_assert(!std::is_same<ELEM_T, float>::value
                      && !std::is_same<ELEM_T, double>::value,
                      "Error, float and double vector pre-decrement is not supported");
        r = r - 1;
        return *this;
    }

    // Post-decrement
    ctype<ELEM_T> operator--(int)
    {
        static_assert(!std::is_same<ELEM_T, float>::value
                      && !std::is_same<ELEM_T, double>::value,
                      "Error, float and double vector post-decrement is not supported");
        ctype<ELEM_T> copy;
        copy.r = r;
        --*this;
        return copy;
    }

    // Addition operator
    ctype<ELEM_T> operator+(const ctype<ELEM_T> &rhs) const
    {
        ctype<ELEM_T> res;
        res.r = (*this).r + rhs.r;
        res.i = (*this).i + rhs.i;
        return res;
    }

    // Subtraction operator
    ctype<ELEM_T> operator-(const ctype<ELEM_T> &rhs) const
    {
        ctype<ELEM_T> res;
        res.r = (*this).r - rhs.r;
        res.i = (*this).i - rhs.i;
        return res;
    }

    // Multiply operator
    ctype<ELEM_T> operator*(const ctype<ELEM_T> &rhs) const
    {
        ctype<ELEM_T> res;
        res.r = (*this).r * rhs.r - ((*this).i * rhs.i);
        res.i = (*this).r * rhs.i + ((*this).i * rhs.r);
        return res;
    }

    // Divide operator
    ctype<ELEM_T> operator/(const ctype<ELEM_T> &rhs) const
    {
        ctype<ELEM_T> res;
        res.r = ((*this).r * rhs.r + ((*this).i * rhs.i)) /
                    (rhs.r * rhs.r + rhs.i * rhs.i);
        res.i = ((*this).i * rhs.r + ((*this).r * rhs.i)) /
                    (rhs.r * rhs.r + rhs.i * rhs.i);
        return res;
    }

    // +=
    ctype<ELEM_T> operator+=(const ctype<ELEM_T>& rhs)
    {
        (*this).r += rhs.r;
        (*this).i += rhs.i;
        return *this;
    }

    // -=
    ctype<ELEM_T> operator-=(const ctype<ELEM_T>& rhs)
    {
        (*this).r -= rhs.r;
        (*this).i -= rhs.i;
        return *this;
    }

    // *=
    ctype<ELEM_T> operator*=(const ctype<ELEM_T>& rhs)
    {
        *this = *this * rhs;
        return *this;
    }

    // /=
    ctype<ELEM_T> operator/=(const ctype<ELEM_T>& rhs)
    {
        *this = *this / rhs;
        return *this;
    }
};

/******************************************************************************
* Class vtype_ptr<> and ctype_ptr<>
*
* t_ptr<> (built with t_ptr_base<>) is used to construct vtype_ptr<> and
* ctype_ptr<> in an abstract way.  Other than the constructors, most of the
* operations, including those for pointer arithmetic, are abstracted.  Because
* some of the behavior changes depending on whether the vector element type is
* complex, we use the base class, t_ptr_base<> to track complex properties and
* to ensure that the underlying complex component type as well as the number of
* lanes reflects the right properties.
*
* OTYPE:    Object Type pointed to (e.g. "vtype<>" or "ctype<>")
* ETYPE:    Element type
* N:        Number of elements
* CMPLANES: Number of component lanes (== 2*N for complex; == N otherwise)
* CMPTYPE:  Component type (primarily for complex elements; == ETYPE otherwise)
******************************************************************************/
template<typename OTYPE, typename ETYPE, size_t N, typename Enable=void>
class t_ptr_base;

// Complex variant of t_ptr_base<>
// Complex elements consist of two components of the same underlying base type
template <typename OTYPE, typename ETYPE, size_t N>
class t_ptr_base<OTYPE, ETYPE, N, enable_if_cmplx_t<ETYPE,void>>
{
    public:
        const uint8_t CMPLANES = N * 2;
        using CMPTYPE = typename ETYPE::ELEM_TYPE;
};

// Non-complex variant of t_ptr_base<>
// Non-complex elements have no special properties
template <typename OTYPE, typename ETYPE, size_t N>
class t_ptr_base<OTYPE, ETYPE, N,
      typename std::enable_if_t<std::is_arithmetic<ETYPE>::value>>
{
    public:
        const uint8_t CMPLANES = N;
        using CMPTYPE = ETYPE;
};

template<typename OTYPE, typename ETYPE, size_t N>
class t_ptr : public t_ptr_base<OTYPE,ETYPE,N>
{
    public:

    // Base scalar type (Useful to identify component type of a complex type)
    using BTYPE = typename t_ptr_base<OTYPE,ETYPE,N>::CMPTYPE;

    // Component lane # (Useful to identify # of lanes in a complex vector)
    using t_ptr_base<OTYPE,ETYPE,N>::CMPLANES;

    // Constructor (new)
    t_ptr<OTYPE,ETYPE,N>() : sptr(std::shared_ptr<OTYPE>(new OTYPE())){};

    // Constructor (via shared pointer)
    t_ptr<OTYPE,ETYPE,N>(std::shared_ptr<OTYPE> sptr) : sptr(sptr) {};

    // Constructor (via existing vector type)
    t_ptr<OTYPE,ETYPE,N>(OTYPE *ptr)                  : sptr(ptr) {};

    // Constructor (via NULL pointer)
    t_ptr<OTYPE,ETYPE,N>(std::nullptr_t ptr)          : sptr(ptr) {}

    // Operations (for debug)
    long use_count()                            { return sptr.use_count(); }

    // Overloaded operators
    operator OTYPE& ()                                     { return *sptr; }
    operator const OTYPE& () const                         { return *sptr; }
    OTYPE& operator*()                                     { return *sptr; }
    const OTYPE& operator*() const                         { return *sptr; }
    std::shared_ptr<OTYPE> operator->()                    { return  sptr; }
    explicit operator BTYPE *()             { return sptr->get_data_arr_ptr(); }
    explicit operator const BTYPE *() const { return sptr->get_data_arr_ptr(); }
    operator void *()                       { return sptr->get_data_arr_ptr(); }

#define CHECK_MEM_OOR(v) { if (!v->is_mem_ptr_based()) \
        throw std::out_of_range("Memory out of allowable range"); }

    // Pre-increment
    t_ptr<OTYPE,ETYPE,N>& operator++()
    {
        CHECK_MEM_OOR(sptr)
        BTYPE* data = ((BTYPE*)((*sptr).get_data_arr_ptr())+CMPLANES);
        sptr = std::shared_ptr<OTYPE>(new OTYPE(data));
        return *this;
    }

    // Post-increment
    t_ptr<OTYPE,ETYPE,N> operator++(int)
    {
        t_ptr<OTYPE,ETYPE,N> old_view(*this);
        operator++();
        return old_view;
    }

    // Pre-decrement
    t_ptr<OTYPE,ETYPE,N>& operator--()
    {
        CHECK_MEM_OOR(sptr)
        BTYPE* data = ((BTYPE*)((*sptr).get_data_arr_ptr())-CMPLANES);
        sptr = std::shared_ptr<OTYPE>(new OTYPE(data));
        return *this;
    }

    // Post-decrement
    t_ptr<OTYPE,ETYPE,N> operator--(int)
    {
        t_ptr<OTYPE,ETYPE,N> old_view(*this);
        operator--();
        return old_view;
    }

    // Plus offset
    t_ptr<OTYPE,ETYPE,N> operator+(int n)
    {
        CHECK_MEM_OOR(sptr)
        BTYPE* data = ((BTYPE*)((*sptr).get_data_arr_ptr())+(CMPLANES*n));
        t_ptr<OTYPE,ETYPE,N> new_view(new OTYPE(data));
        return new_view;
    }

    // Minus offset
    t_ptr<OTYPE,ETYPE,N> operator-(int n)
    {
        CHECK_MEM_OOR(sptr)
        BTYPE* data = ((BTYPE*)((*sptr).get_data_arr_ptr())-(CMPLANES*n));
        t_ptr<OTYPE,ETYPE,N> new_view(new OTYPE(data));
        return new_view;
    }

    // Plus-asg offset
    t_ptr<OTYPE,ETYPE,N>& operator+=(int n)
    {
        CHECK_MEM_OOR(sptr)
        BTYPE* data = ((BTYPE*)((*sptr).get_data_arr_ptr())+(CMPLANES*n));
        sptr = std::shared_ptr<OTYPE>(new OTYPE(data));
        return *this;
    }

    // Minus-asg offset
    t_ptr<OTYPE,ETYPE,N>& operator-=(int n)
    {
        CHECK_MEM_OOR(sptr)
        BTYPE* data = ((BTYPE*)((*sptr).get_data_arr_ptr())-(CMPLANES*n));
        sptr = std::shared_ptr<OTYPE>(new OTYPE(data));
        return *this;
    }

#undef CHECK_MEM_OOR

    protected:

    // Internally managed shared_ptr<> to a vector or complex pointer
    std::shared_ptr<OTYPE> sptr;
};

/******************************************************************************
* Class vtype_ptr
******************************************************************************/
template<typename ETYPE, size_t N>
class vtype_ptr : public t_ptr<vtype<ETYPE,N>,ETYPE,N>
{
    public:

    using VTYPE = vtype<ETYPE,N>;

    // Constructor (new)
    vtype_ptr<ETYPE,N>() :
        t_ptr<VTYPE,ETYPE,N>(std::shared_ptr<VTYPE>(new VTYPE())) {};

    // Constructor (via shared pointer)
    vtype_ptr<ETYPE,N>(std::shared_ptr<VTYPE> sptr) :
        t_ptr<VTYPE,ETYPE,N>(sptr) {};

    // Constructor (via existing vector type)
    vtype_ptr<ETYPE,N>(VTYPE *ptr) :
        t_ptr<VTYPE,ETYPE,N>(ptr) {};

    // Constructor (via existing other vector type)
    template <typename OETYPE, size_t ON>
    explicit vtype_ptr<ETYPE,N>(vtype_ptr<OETYPE,ON>& ptr) :
        t_ptr<VTYPE,ETYPE,N>(std::shared_ptr<VTYPE>(
                    new VTYPE((ETYPE*)ptr->get_data_arr_ptr()))) {}

    // Constructor (via NULL pointer)
    vtype_ptr<ETYPE,N>(std::nullptr_t ptr) :
        t_ptr<VTYPE,ETYPE,N>(ptr) {}

    // Constructor (via scalar pointer, to facilitate C-style casting)
    vtype_ptr<ETYPE,N>(ETYPE *input) :
        t_ptr<VTYPE,ETYPE,N>(std::shared_ptr<VTYPE>(new VTYPE(input))) {};

    // Constructor (via complex pointer)
    template<typename ELEM_DUMMY = ETYPE,
             typename = enable_if_cmplx_t<ELEM_DUMMY, void>>
    vtype_ptr<ETYPE,N>(typename ELEM_DUMMY::ELEM_TYPE *input) :
        t_ptr<VTYPE,ETYPE,N>(std::shared_ptr<VTYPE>(new VTYPE(input))) {}

    // Cast conversion to complex element pointer (from complex vector pointer)
    template <typename ED = ETYPE, typename = enable_if_cmplx_t<ED, void>>
    explicit operator ctype_ptr<typename ED::ELEM_TYPE>()
                                 { return this->sptr->get_cdata_arr_ptr(); }
};

/******************************************************************************
* Class ctype_ptr
******************************************************************************/
template<typename ETYPE>
class ctype_ptr : public t_ptr<ctype<ETYPE>,ETYPE,2>
{
    public:

    using CTYPE = ctype<ETYPE>;

    // Constructor (new)
    ctype_ptr<ETYPE>() :
        t_ptr<CTYPE,ETYPE,2>(std::shared_ptr<CTYPE>(new CTYPE())) {};

    // Constructor (via shared pointer)
    ctype_ptr<ETYPE>(std::shared_ptr<CTYPE> sptr) :
        t_ptr<CTYPE,ETYPE,2>(sptr) {};

    // Constructor (via NULL pointer)
    ctype_ptr<ETYPE>(CTYPE *ptr) :
        t_ptr<CTYPE,ETYPE,2>(ptr) {}

    // Constructor (via NULL pointer)
    ctype_ptr<ETYPE>(std::nullptr_t ptr) :
        t_ptr<CTYPE,ETYPE,2>(ptr) {}

    // Constructor (via scalar pointer, to facilitate C-style casting)
    ctype_ptr<ETYPE>(ETYPE *input, const size_t i = 0) :
        t_ptr<CTYPE,ETYPE,2>(std::shared_ptr<CTYPE>(new CTYPE(input,i))) {};
};

/******************************************************************************
* Class definition for the vector predicate type.
******************************************************************************/
class __vpred
{
    public:
       // Default constructor.
       __vpred() {}

       // Constructor to initialize a __vpred from a vpred_t. A vpred_t is
       // a uint64_t used to represent vector predicates within C semantic
       // function definitions. Constructor must be explicit. Otherwise,
       // can do vpred = int which is not allowed on C7000
       explicit __vpred(vpred_t input)
       {
           pred = input;
       }

       // Cast that allows for implicit conversion to a vpred_t
       operator vpred_t() const
       {
           vpred_t conv = pred;
           return conv;
       }

       // Helpful print function, not supported on C7000
       // Display the predicate as a binary value of 64 bits
       void print()
       {
           std::cout << std::bitset<64>(pred) << std::endl;
       }

    private:
       // Underlying data is private
       uint64_t pred = 0;
};

template <size_t NELEM>
class bvtype
{
    public:
       static constexpr size_t NUM_ELEM = NELEM;

       // Default constructor.
       bvtype() {}

       // Constructor to initialize a bvtype from a vpred_t. A vpred_t is
       // a uint64_t used to represent vector predicates within C semantic
       // function definitions. Constructor must be explicit. Otherwise,
       // can do bvtype = int which is not allowed on C7000
       explicit bvtype(vpred_t input)
       {
           pred = input;
       }

       // Cast that allows for implicit conversion to a vpred_t
       operator vpred_t() const
       {
           vpred_t conv = pred;
           return conv;
       }

       // Helpful print function, not supported on C7000
       // Display the predicate as a binary value of NUM_ELEM bits
       void print()
       {
           std::cout << std::bitset<NUM_ELEM>(pred) << std::endl;
       }

    private:
       // Underlying data is private
       uint64_t pred = 0;
};

/******************************************************************************
* Implementation of the accessible interface. An accessible object defines
* the following accessors:
*   - .sk for k in the range [0-9, a-f, A-F] to access the first 16 elements
*   - .x, .y, .z, and .w to access elements 0, 1, 2, and 3
*   - .hi, .lo, .even, and .odd to access partitions of the vector
*
* Limitations:
*   - OpenCL "swizzle" accessors, which combine multiple accesses into a
*     single member are not supported. Examples: vector.xyz, vector.s3210
******************************************************************************/

//-----------------------------------------------------------------------------
// The scalar_accessors class is one base for the derived, common accessible
// interface that represents the dot-accessor syntax allowed by OpenCL. It does
// this by linking ELEM_T references to references found in the parent's
// reference wrapper array. Index calculations are already handled in the
// ref_holder class.
//
// Each valid scalar_accessor inherits from the previous, all the way to
// NELEM == 64.
//-----------------------------------------------------------------------------
template <typename ELEM_T, size_t NELEM>
class scalar_accessors { };

template<typename ELEM_T>
class scalar_accessors<ELEM_T, 2>
{
public:
    ELEM_T &x;
    ELEM_T &y;
public:
    ELEM_T &s0;
    ELEM_T &s1;
public:
    template<size_t N>
    scalar_accessors(std::array<std::reference_wrapper<ELEM_T>, N> &refs) :
        x(refs[0]), y(refs[1]), s0(refs[0]), s1(refs[1]) { }
};

template<typename ELEM_T>
class scalar_accessors<ELEM_T, 4> :
    public scalar_accessors<ELEM_T, 2>
{
public:
    ELEM_T &z;
    ELEM_T &w;
public:
    ELEM_T &s2;
    ELEM_T &s3;
public:
    template<size_t N>
    scalar_accessors(std::array<std::reference_wrapper<ELEM_T>, N> &refs) :
        scalar_accessors<ELEM_T, 2>(refs),
        z(refs[2]), w(refs[3]), s2(refs[2]), s3(refs[3]) { }
};

template<typename ELEM_T>
class scalar_accessors<ELEM_T, 8> :
    public scalar_accessors<ELEM_T, 4>
{
public:
    ELEM_T &s4;
    ELEM_T &s5;
    ELEM_T &s6;
    ELEM_T &s7;
public:
    template<size_t N>
    scalar_accessors(std::array<std::reference_wrapper<ELEM_T>, N> &refs) :
        scalar_accessors<ELEM_T, 4>(refs),
        s4(refs[4]), s5(refs[5]), s6(refs[6]), s7(refs[7]) { }
};

template<typename ELEM_T>
class scalar_accessors<ELEM_T, 16> :
    public scalar_accessors<ELEM_T, 8>
{
public:
    ELEM_T &s8;
    ELEM_T &s9;
    ELEM_T &sa;
    ELEM_T &sA;
    ELEM_T &sb;
    ELEM_T &sB;
    ELEM_T &sc;
    ELEM_T &sC;
    ELEM_T &sd;
    ELEM_T &sD;
    ELEM_T &se;
    ELEM_T &sE;
    ELEM_T &sf;
    ELEM_T &sF;
public:
    template<size_t N>
    scalar_accessors(std::array<std::reference_wrapper<ELEM_T>, N> &refs) :
        scalar_accessors<ELEM_T, 8>(refs),
        s8(refs[8]),  s9(refs[9]),  sa(refs[10]), sA(refs[10]),
        sb(refs[11]), sB(refs[11]), sc(refs[12]), sC(refs[12]),
        sd(refs[13]), sD(refs[13]), se(refs[14]), sE(refs[14]),
        sf(refs[15]), sF(refs[15]) { }
};

template<typename ELEM_T>
class scalar_accessors<ELEM_T, 32> :
    public scalar_accessors<ELEM_T, 16>
{
public:
    template<size_t N>
    scalar_accessors(std::array<std::reference_wrapper<ELEM_T>, N> &refs) :
        scalar_accessors<ELEM_T, 16>(refs) { }
};

template<typename ELEM_T>
class scalar_accessors<ELEM_T, 64> :
    public scalar_accessors<ELEM_T, 32>
{
public:
    template<size_t N>
    scalar_accessors(std::array<std::reference_wrapper<ELEM_T>, N> &refs) :
        scalar_accessors<ELEM_T, 32>(refs) { }
};

//-----------------------------------------------------------------------------
// Helper class which is instantiated conditionally by an instance of an
// accessible object. Contains subvector accessors real and imag. Instantiated
// by accessibles with complex element types.
//
// Note: complex_accessors also need to have a notion of depth, so that
// "cchar32.lo.lo.r" is still recognized as being "2-deep" and
// "cchar32.lo.lo.r.lo" isn't supported when the depth is limited to 2.
// Otherwise we end up with memory bloat for complex vectors.
//-----------------------------------------------------------------------------
template <typename ELEM_T, size_t NELEM, size_t DEPTH, typename ENABLED = void>
class complex_accessors;

// Accessibles whose element types are not complex will have no complex accessors
template <typename ELEM_T, size_t NELEM, size_t DEPTH>
class complex_accessors<ELEM_T, NELEM, DEPTH,
      typename std::enable_if_t<std::is_arithmetic<ELEM_T>::value>>
{
public:
    complex_accessors(std::array<std::reference_wrapper<ELEM_T>, NELEM> &refs)
    { (void)refs; }
};

// Accessibles with complex element types have r and i members
template <typename ELEM_T, size_t NELEM, size_t DEPTH>
class complex_accessors<ELEM_T, NELEM, DEPTH,
      enable_if_cmplx_t<ELEM_T, void>>
{
public:
    accessible<typename ELEM_T::ELEM_TYPE, NELEM, DEPTH> r;
    accessible<typename ELEM_T::ELEM_TYPE, NELEM, DEPTH> i;
public:
    complex_accessors(std::array<std::reference_wrapper<ELEM_T>, NELEM> &refs) :
        r(refs, access_types<ACCESS_TYPE::REAL>()),
        i(refs, access_types<ACCESS_TYPE::IMAG>()) { }
};

// Single complex element r and i accessors are define within the ctype class.

//-----------------------------------------------------------------------------
// Helper class which is instantiated conditionally by an instance of an
// accessible object. Contains subvector accessors lo, hi, even, and odd.
//-----------------------------------------------------------------------------
template <typename ELEM_T, size_t NELEM, size_t DEPTH, typename ENABLED = void>
class subvector_accessors
{
public:
    accessible<ELEM_T, NELEM / 2, DEPTH + 1>   lo;
    accessible<ELEM_T, NELEM / 2, DEPTH + 1>   hi;
    accessible<ELEM_T, NELEM / 2, DEPTH + 1> even;
    accessible<ELEM_T, NELEM / 2, DEPTH + 1>  odd;
public:
    subvector_accessors(std::array<std::reference_wrapper<ELEM_T>, NELEM> &refs) :
       lo(refs, access_types<ACCESS_TYPE::LO>()),
       hi(refs, access_types<ACCESS_TYPE::HI>()),
       even(refs, access_types<ACCESS_TYPE::EVEN>()),
       odd(refs, access_types<ACCESS_TYPE::ODD>()) { }
};

// Termination condition: We've reached scalar elements.
template <typename ELEM_T, size_t DEPTH>
class subvector_accessors<ELEM_T, 2, DEPTH>
{
public:
    ELEM_T &lo;
    ELEM_T &hi;
    ELEM_T &even;
    ELEM_T &odd;
public:
    subvector_accessors(std::array<std::reference_wrapper<ELEM_T>, 2> &refs) :
        lo(refs[0]), hi(refs[1]), even(refs[0]), odd(refs[1]) { }
};

// Termination condition: We've reached the maximum configured depth Use
// enable_if to avoid ambiguity with the 2-element subvector->scalar
// termination condition above by disabling this condition for 2-element
// vectors.
template <typename ELEM_T, size_t NELEM>
class subvector_accessors<ELEM_T, NELEM, __TI_MAX_ACCESSOR_DEPTH,
                          typename std::enable_if<NELEM != 2>::type>
{
public:
    subvector_accessors(std::array<std::reference_wrapper<ELEM_T>, NELEM> &refs)
    { (void)refs; }
};

/******************************************************************************
* Struct used to allow for TI extension .s[k] syntax. All accessibles will
* initialize an s_impl object.
******************************************************************************/
template<typename ELEM_T, size_t NELEM>
struct s_impl
{
    // Operators to retrieve data from a reference wrapper at an index
    ELEM_T& operator[](size_t index)
    {
        return refs_s[index].get();
    }

    const ELEM_T& operator[](size_t index) const
    {
        return refs_s[index].get();
    }

    // Reference to array of references
    std::array<std::reference_wrapper<ELEM_T>, NELEM>& refs_s;

    // Initialize reference wrapper array refs_s using passed in array
    // of reference wrappers
    s_impl(std::array<std::reference_wrapper<ELEM_T>, NELEM> &refs) :
           refs_s(refs) { }

};

//-----------------------------------------------------------------------------
// Implementation of the accessible class.
//
// Inherits from:
//   - ref_holder
//       Responsible for creating reference wrapper array with references
//       to data based on ACCESS_TYPE
//   - subvector_accessors
//       Provides access to the lo, hi, even, and odd members, which are each
//       themselves accessibles or ELEM_T& members
//   - scalar_accessors
//       Provides the ELEM_T& members s0-sf
//   - complex_accessors
//       Provides the ELEM_T& members r,i
//   - enable_shared_from_this<>
//       Allows a shared_ptr of an object's instance to be returned.
//       Must be given the "most-derived-class" (i.e. "vtype<>")
//-----------------------------------------------------------------------------
template <typename ELEM_T, size_t NELEM, size_t DEPTH>
class accessible :
    public ref_holder<ELEM_T, NELEM>,
    public subvector_accessors<ELEM_T, NELEM, DEPTH>,
    public scalar_accessors<ELEM_T, NELEM>,
    public complex_accessors<ELEM_T, NELEM, DEPTH>,
    public std::enable_shared_from_this<vtype<ELEM_T, NELEM>>
{
private:
    using ACCESS_T = accessible<ELEM_T, NELEM, DEPTH>;

    template <size_t OTHER_DEPTH>
    using EQUIV_ACCESS_T = accessible<ELEM_T, NELEM, OTHER_DEPTH>;

    using SUBVECTOR_ACCESSOR_T = subvector_accessors<ELEM_T, NELEM, DEPTH>;

    using SCALAR_ACCESSOR_T = scalar_accessors<ELEM_T, NELEM>;

    using COMPLEX_ACCESSOR_T = complex_accessors<ELEM_T, NELEM, DEPTH>;

    using ref_holder<ELEM_T, NELEM>::refs_m;

public:
/******************************************************************************
* Constructors
******************************************************************************/

    // Constructor is used when initializing an accessible from a vtype
    accessible(std::array<ELEM_T, NELEM> &data,
               access_types<ACCESS_TYPE::NORMAL>) :
                   ref_holder<ELEM_T, NELEM>(data, access_types<ACCESS_TYPE::NORMAL>(),
                       std::make_index_sequence<NELEM>()),
                   SUBVECTOR_ACCESSOR_T(refs_m),
                   SCALAR_ACCESSOR_T(refs_m),
                   COMPLEX_ACCESSOR_T(refs_m),
                   s(refs_m) { }

    // Constructor is used when initializing an accessible from a vtype from a
    // subvector vtype
    accessible(std::array<std::reference_wrapper<ELEM_T>, NELEM> &refs,
               access_types<ACCESS_TYPE::NORMAL>) :
                   ref_holder<ELEM_T, NELEM>(refs, access_types<ACCESS_TYPE::NORMAL>(),
                       std::make_index_sequence<NELEM>()),
                   SUBVECTOR_ACCESSOR_T(refs_m),
                   SCALAR_ACCESSOR_T(refs_m),
                   COMPLEX_ACCESSOR_T(refs_m),
                   s(refs_m) { }

    // Constructor is used to initialize a LO accessible
    accessible(std::array<std::reference_wrapper<ELEM_T>, NELEM*2> &refs,
               access_types<ACCESS_TYPE::HI>) :
                   ref_holder<ELEM_T, NELEM>(refs, access_types<ACCESS_TYPE::HI>(),
                       std::make_index_sequence<NELEM>()),
                   SUBVECTOR_ACCESSOR_T(refs_m),
                   SCALAR_ACCESSOR_T(refs_m),
                   COMPLEX_ACCESSOR_T(refs_m),
                   s(refs_m) { }

    // Constructor is used to initialize a HI accessible
    accessible(std::array<std::reference_wrapper<ELEM_T>, NELEM*2> &refs,
               access_types<ACCESS_TYPE::LO>) :
                   ref_holder<ELEM_T, NELEM>(refs, access_types<ACCESS_TYPE::LO>(),
                       std::make_index_sequence<NELEM>()),
                   SUBVECTOR_ACCESSOR_T(refs_m),
                   SCALAR_ACCESSOR_T(refs_m),
                   COMPLEX_ACCESSOR_T(refs_m),
                   s(refs_m) { }

    // Constructor is used to initialize an EVEN accessible
    accessible(std::array<std::reference_wrapper<ELEM_T>, NELEM*2> &refs,
               access_types<ACCESS_TYPE::EVEN>) :
                   ref_holder<ELEM_T, NELEM>(refs, access_types<ACCESS_TYPE::EVEN>(),
                       std::make_index_sequence<NELEM>()),
                   SUBVECTOR_ACCESSOR_T(refs_m),
                   SCALAR_ACCESSOR_T(refs_m),
                   COMPLEX_ACCESSOR_T(refs_m),
                   s(refs_m) { }

    // Constructor is used to initialize an ODD accessible
    accessible(std::array<std::reference_wrapper<ELEM_T>, NELEM*2> &refs,
               access_types<ACCESS_TYPE::ODD>) :
                   ref_holder<ELEM_T, NELEM>(refs, access_types<ACCESS_TYPE::ODD>(),
                       std::make_index_sequence<NELEM>()),
                   SUBVECTOR_ACCESSOR_T(refs_m),
                   SCALAR_ACCESSOR_T(refs_m),
                   COMPLEX_ACCESSOR_T(refs_m),
                   s(refs_m) { }

    // Constructor is used to initialize a REAL accessible
    accessible(std::array<std::reference_wrapper<ctype<ELEM_T>>, NELEM> &refs,
               access_types<ACCESS_TYPE::REAL>) :
                   ref_holder<ELEM_T, NELEM>(refs, access_types<ACCESS_TYPE::REAL>(),
                       std::make_index_sequence<NELEM>()),
                   SUBVECTOR_ACCESSOR_T(refs_m),
                   SCALAR_ACCESSOR_T(refs_m),
                   COMPLEX_ACCESSOR_T(refs_m),
                   s(refs_m) { }

    // Constructor is used to initialize an IMAG accessible
    accessible(std::array<std::reference_wrapper<ctype<ELEM_T>>, NELEM> &refs,
               access_types<ACCESS_TYPE::IMAG>) :
                   ref_holder<ELEM_T, NELEM>(refs, access_types<ACCESS_TYPE::IMAG>(),
                       std::make_index_sequence<NELEM>()),
                   SUBVECTOR_ACCESSOR_T(refs_m),
                   SCALAR_ACCESSOR_T(refs_m),
                   COMPLEX_ACCESSOR_T(refs_m),
                   s(refs_m) { }

    accessible(ELEM_T *ptr,
               access_types<ACCESS_TYPE::NORMAL>) :
                   ref_holder<ELEM_T, NELEM>(ptr, access_types<ACCESS_TYPE::NORMAL>(),
                       std::make_index_sequence<NELEM>()),
                   SUBVECTOR_ACCESSOR_T(refs_m),
                   SCALAR_ACCESSOR_T(refs_m),
                   COMPLEX_ACCESSOR_T(refs_m),
                   s(refs_m) { }

    // Constructor is used when initializing an accessible from a complex
    // component-type pointer
    template<typename ELEM_DUMMY = ELEM_T,
             typename = enable_if_cmplx_t<ELEM_DUMMY, void>>
    accessible(typename ELEM_DUMMY::ELEM_TYPE* ptr, access_types<ACCESS_TYPE::NORMAL>) :
                   ref_holder<ELEM_T, NELEM>(ptr, access_types<ACCESS_TYPE::NORMAL>(),
                       std::make_index_sequence<NELEM>()),
                   SUBVECTOR_ACCESSOR_T(refs_m),
                   SCALAR_ACCESSOR_T(refs_m),
                   COMPLEX_ACCESSOR_T(refs_m),
                   s(refs_m) { }

    // You should not be able to construct an accessible on its own
    accessible(const accessible &a)  = delete;
    accessible(accessible &&a) = delete;

/******************************************************************************
* Public Members
******************************************************************************/

    // Allows for TI syntax .s[k]
    struct s_impl<ELEM_T, NELEM> s;

/******************************************************************************
* Operator Overloads
******************************************************************************/

    // Conversion from an accessible to a vreg_t
    operator vreg_t() const
        { return convert_to_vreg_t<ACCESS_T, ELEM_T, NELEM>(*this); }

    // Equals operator between an accessible and an object that is
    // "equally" accessible (same number of elements and element type)
    template <size_t OTHER_DEPTH>
    ACCESS_T &operator=(const EQUIV_ACCESS_T<OTHER_DEPTH> &rhs)
    {
        for (size_t i = 0; i < NELEM; i++)
            s[i] = rhs.s[i];

        return *this;
    }

    // Equals operator between two accessibles that have the same number of
    // elements and the same element type
    ACCESS_T &operator=(const ACCESS_T &rhs)
    {
        for (size_t i = 0; i < NELEM; i++)
        {
            s[i] = rhs.s[i];
        }
        return *this;
    }

    // Address-of operator returns a vtype_ptr
    vtype_ptr<ELEM_T, NELEM> operator &()
    {
        return (new vtype<ELEM_T, NELEM>(this));
    }

/******************************************************************************
* Vector Operators
******************************************************************************/

    // Unary negate
    vtype<ELEM_T, NELEM> operator-()
    {
        return -1 * (*this);
    }

    // Unary plus
    vtype<ELEM_T, NELEM> operator+()
    {
        return *this;
    }

    // Pre-increment
    vtype<ELEM_T, NELEM> operator++()
    {
        static_assert(!std::is_same<ELEM_T, float>::value
                      && !std::is_same<ELEM_T, double>::value,
		      "Error, float and double vector pre-increment is not supported");
	for (size_t i = 0; i < NELEM; i++)
			s[i] = s[i] + 1;
	return *this;
    }

    // Post-increment
    vtype<ELEM_T, NELEM> operator++(int)
    {
        static_assert(!std::is_same<ELEM_T, float>::value
                      && !std::is_same<ELEM_T, double>::value,
                      "Error, float and double vector post-increment is not supported");
        vtype<ELEM_T, NELEM> copy;
        for (size_t i = 0; i < NELEM; i++)
                copy.s[i] = s[i];
        ++*this;
        return copy;
    }

    // Pre-decrement
    vtype<ELEM_T, NELEM> operator--()
    {
        static_assert(!std::is_same<ELEM_T, float>::value
                      && !std::is_same<ELEM_T, double>::value,
                      "Error, float and double vector pre-decrement is not supported");
        for (size_t i = 0; i < NELEM; i++)
                s[i] = s[i] - 1;
        return *this;
    }

    // Post-decrement
    vtype<ELEM_T, NELEM> operator--(int)
    {
        static_assert(!std::is_same<ELEM_T, float>::value
                      && !std::is_same<ELEM_T, double>::value,
                      "Error, float and double vector post-decrement is not supported");
        vtype<ELEM_T, NELEM> copy;
        for (size_t i = 0; i < NELEM; i++)
                copy.s[i] = s[i];
        --*this;
        return copy;
    }

    // Bitwise not
    vtype<ELEM_T, NELEM> operator~()
    {
        static_assert(!std::is_same<ELEM_T, float>::value
                      && !std::is_same<ELEM_T, double>::value,
                      "Error, float and double vector bitwise ~ is not supported");
        vtype<ELEM_T, NELEM> res;
        for (size_t i = 0; i < NELEM; i++)
                res.s[i] = ~s[i];
        return res;
    }

    // +=
    vtype<ELEM_T, NELEM> operator+=(const vtype<ELEM_T, NELEM>& rhs)
    {
        for (size_t i = 0; i < NELEM; i++)
                (*this).s[i] += rhs.s[i];
        return *this;
    }

    vtype<ELEM_T, NELEM> operator+=(const ELEM_T& rhs)
    {
        for (size_t i = 0; i < NELEM; i++)
                (*this).s[i] += rhs;
        return *this;
    }

    // -=
    vtype<ELEM_T, NELEM> operator-=(const vtype<ELEM_T, NELEM>& rhs)
    {
        for (size_t i = 0; i < NELEM; i++)
                (*this).s[i] -= rhs.s[i];
        return *this;
    }

    vtype<ELEM_T, NELEM> operator-=(const ELEM_T& rhs)
    {
        for (size_t i = 0; i < NELEM; i++)
                (*this).s[i] -= rhs;
        return *this;
    }

    // *=
    vtype<ELEM_T, NELEM> operator*=(const vtype<ELEM_T, NELEM>& rhs)
    {
        for (size_t i = 0; i < NELEM; i++)
                (*this).s[i] *= rhs.s[i];
        return *this;
    }

    vtype<ELEM_T, NELEM> operator*=(const ELEM_T& rhs)
    {
        for (size_t i = 0; i < NELEM; i++)
                (*this).s[i] *= rhs;
        return *this;
    }

    // /=
    vtype<ELEM_T, NELEM> operator/=(const vtype<ELEM_T, NELEM>& rhs)
    {
        for (size_t i = 0; i < NELEM; i++)
                (*this).s[i] /= rhs.s[i];
        return *this;
    }

    vtype<ELEM_T, NELEM> operator/=(const ELEM_T& rhs)
    {
        for (size_t i = 0; i < NELEM; i++)
                (*this).s[i] /= rhs;
        return *this;
    }

    // %=
    vtype<ELEM_T, NELEM> operator%=(const vtype<ELEM_T, NELEM>& rhs)
    {
        static_assert(!std::is_same<ELEM_T, float>::value
                      && !std::is_same<ELEM_T, double>::value,
                      "Error, float and double vec to vec %= is not supported");

        for (size_t i = 0; i < NELEM; i++)
                (*this).s[i] %= rhs.s[i];
        return *this;
    }

    vtype<ELEM_T, NELEM> operator%=(const ELEM_T& rhs)
    {

        static_assert(!std::is_same<ELEM_T, float>::value
                      && !std::is_same<ELEM_T, double>::value,
                      "Error, float and double vec to scalar %= is not supported");

        for (size_t i = 0; i < NELEM; i++)
                (*this).s[i] %= rhs;
        return *this;
    }

    // >>=
    vtype<ELEM_T, NELEM> operator>>=(const vtype<ELEM_T, NELEM>& rhs)
    {
        static_assert(!std::is_same<ELEM_T, float>::value
                      && !std::is_same<ELEM_T, double>::value,
                      "Error, float and double vec to vec >>= is not supported");

        for (size_t i = 0; i < NELEM; i++)
                (*this).s[i] >>= rhs.s[i];
        return *this;
    }

    vtype<ELEM_T, NELEM> operator>>=(const ELEM_T& rhs)
    {

        static_assert(!std::is_same<ELEM_T, float>::value
                      && !std::is_same<ELEM_T, double>::value,
                      "Error, float and double vec to scalar >>= is not supported");

        for (size_t i = 0; i < NELEM; i++)
                (*this).s[i] >>= rhs;
        return *this;
    }

    // <<=
    vtype<ELEM_T, NELEM> operator<<=(const vtype<ELEM_T, NELEM>& rhs)
    {
        static_assert(!std::is_same<ELEM_T, float>::value
                      && !std::is_same<ELEM_T, double>::value,
                      "Error, float and double vec to vec <<= is not supported");

        for (size_t i = 0; i < NELEM; i++)
                (*this).s[i] <<= rhs.s[i];
        return *this;
    }

    vtype<ELEM_T, NELEM> operator<<=(const ELEM_T& rhs)
    {

        static_assert(!std::is_same<ELEM_T, float>::value
                      && !std::is_same<ELEM_T, double>::value,
                      "Error, float and double vec to scalar <<= is not supported");

        for (size_t i = 0; i < NELEM; i++)
                (*this).s[i] <<= rhs;
        return *this;
    }

    // &=
    vtype<ELEM_T, NELEM> operator&=(const vtype<ELEM_T, NELEM>& rhs)
    {
        static_assert(!std::is_same<ELEM_T, float>::value
                      && !std::is_same<ELEM_T, double>::value,
                      "Error, float and double vec to vec &= is not supported");

        for (size_t i = 0; i < NELEM; i++)
                (*this).s[i] &= rhs.s[i];
        return *this;
    }

    vtype<ELEM_T, NELEM> operator&=(const ELEM_T& rhs)
    {

        static_assert(!std::is_same<ELEM_T, float>::value
                      && !std::is_same<ELEM_T, double>::value,
                      "Error, float and double vec to scalar &= is not supported");

        for (size_t i = 0; i < NELEM; i++)
                (*this).s[i] &= rhs;
        return *this;
    }

    // |=
    vtype<ELEM_T, NELEM> operator|=(const vtype<ELEM_T, NELEM>& rhs)
    {
        static_assert(!std::is_same<ELEM_T, float>::value
                      && !std::is_same<ELEM_T, double>::value,
                      "Error, float and double vec to vec |= is not supported");

        for (size_t i = 0; i < NELEM; i++)
                (*this).s[i] |= rhs.s[i];
        return *this;
    }

    vtype<ELEM_T, NELEM> operator|=(const ELEM_T& rhs)
    {

        static_assert(!std::is_same<ELEM_T, float>::value
                      && !std::is_same<ELEM_T, double>::value,
                      "Error, float and double vec to scalar |= is not supported");

        for (size_t i = 0; i < NELEM; i++)
                (*this).s[i] |= rhs;
        return *this;
    }

    // ^=
    vtype<ELEM_T, NELEM> operator^=(const vtype<ELEM_T, NELEM>& rhs)
    {
        static_assert(!std::is_same<ELEM_T, float>::value
                      && !std::is_same<ELEM_T, double>::value,
                      "Error, float and double vec to vec ^= is not supported");

        for (size_t i = 0; i < NELEM; i++)
                (*this).s[i] ^= rhs.s[i];
        return *this;
    }

    vtype<ELEM_T, NELEM> operator^=(const ELEM_T& rhs)
    {

        static_assert(!std::is_same<ELEM_T, float>::value
                      && !std::is_same<ELEM_T, double>::value,
                      "Error, float and double vec to scalar ^= is not supported");

        for (size_t i = 0; i < NELEM; i++)
                (*this).s[i] ^= rhs;
        return *this;
    }

/******************************************************************************
* Debugging capability (Not guaranteed to compile on the target!)
******************************************************************************/
public:
    void print() const
    {
        std::cout << "(";

        print_vec<ELEM_T>();
    }

private:
    // Print a scalar accessible
    template <typename E_TYPE>
    typename std::enable_if_t<std::is_arithmetic<E_TYPE>::value> print_vec() const
    {
        // Pick a reasonable type for printing, i.e. promote short/char to int
        using conv_t =
            typename std::conditional<(std::is_integral<ELEM_T>::value &&
                                sizeof(ELEM_T) < sizeof(int32_t)),
                                int32_t, ELEM_T>::type;

        for (size_t i = 0; i < NELEM - 1; i++)
            std::cout << (conv_t)s[i] << ", ";
        std::cout << (conv_t)s[NELEM - 1] << ")" << std::endl;
    }

    // Print a complex accessible
    template <typename E_TYPE>
    enable_if_cmplx_t<E_TYPE, void> print_vec() const
    {
        for (size_t i = 0; i < NELEM - 1; i++)
        {
            s[i].print();
            std::cout << ", ";
        }
        s[NELEM-1].print();
        std::cout << ")" << std::endl;
   }
};

/******************************************************************************
* Implementation of conversions that can be performed on vtypes
******************************************************************************/

// Functions to get source element size based on type (scalar or complex)
template <typename SRC_T>
constexpr enable_if_cmplx_t<SRC_T, size_t> get_src_size()
{
    return sizeof(typename SRC_T::ELEM_TYPE) * 2;
}

template <typename SRC_T>
constexpr typename std::enable_if_t<std::is_arithmetic<SRC_T>::value,
                                    size_t> get_src_size()
{
    return sizeof(SRC_T);
}

#include "vector_conv.h"

//-----------------------------------------------------------------------------
// any/all operations
//   Any takes an integral vector and returns 1 if the high bit is set in any
// lane.  All takes an integral vector and returns 1 if the high bit is set
// in all lanes.
//-----------------------------------------------------------------------------
template <typename ELEM_T,
          typename = std::enable_if_t<std::is_integral<ELEM_T>::value>>
int __all(const ELEM_T &input)
{
    typedef std::make_unsigned_t<ELEM_T> utype;
    constexpr int shift = (sizeof(ELEM_T) * CHAR_BIT) - 1;
    return (((utype)input) >> shift) & 1;
}

template <typename ELEM_T,
          typename = std::enable_if_t<std::is_integral<ELEM_T>::value>>
int __any(const ELEM_T &input)
{
    typedef std::make_unsigned_t<ELEM_T> utype;
    constexpr int shift = (sizeof(ELEM_T) * CHAR_BIT) - 1;
    return (((utype)input) >> shift) & 1;
}

template <typename ELEM_T, size_t NELEM, size_t DEPTH,
          typename = std::enable_if_t<std::is_integral<ELEM_T>::value>>
int __all(const accessible<ELEM_T, NELEM, DEPTH>& input)
{
    typedef std::make_unsigned_t<ELEM_T> utype;
    constexpr int shift = (sizeof(ELEM_T) * CHAR_BIT) - 1;
    ELEM_T result = 1;
    for (size_t i = 0; i < NELEM; i++)
    {
        result &= ((utype)input.s[i]) >> shift;
    }
    return result;
}

template <typename ELEM_T, size_t NELEM, size_t DEPTH,
          typename = std::enable_if_t<std::is_integral<ELEM_T>::value>>
int __any(const accessible<ELEM_T, NELEM, DEPTH>& input)
{
    typedef std::make_unsigned_t<ELEM_T> utype;
    constexpr int shift = (sizeof(ELEM_T) * CHAR_BIT) - 1;
    ELEM_T result = 0;
    for (size_t i = 0; i < NELEM; i++)
    {
        result |= ((utype)input.s[i]) >> shift;
    }
    return result;
}


/******************************************************************************
* Implementation of operations that can be performed on vtypes
******************************************************************************/

//-----------------------------------------------------------------------------
// Operator+ overloads
//-----------------------------------------------------------------------------
template <typename ELEM_T, size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<ELEM_T, NELEM> operator+(
    const accessible<ELEM_T, NELEM, DEPTH_L> &lhs,
    const accessible<ELEM_T, NELEM, DEPTH_R> &rhs)
{
    vtype<ELEM_T, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
        res.s[i] = lhs.s[i] + rhs.s[i];
    return res;
}
//-----------------------------------------------------------------------------
// int64_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int64_t, NELEM> operator+(
    const accessible<int64_t, NELEM, DEPTH_L> &lhs,
    const accessible<int64_t, NELEM, DEPTH_R> &rhs)
{
    vreg_t res;
    _vaddd_vvv(lhs, rhs, res);
    return vtype<int64_t, NELEM>(res);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int64_t, NELEM> operator+(
    const accessible<int64_t, NELEM, DEPTH_L> &lhs,
    const int64_t immediate)
{
    return vtype<int64_t, NELEM>(lhs) + vtype<int64_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int64_t, NELEM> operator+(
     const int64_t immediate,
     const accessible<int64_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<int64_t, NELEM>(immediate) + vtype<int64_t, NELEM>(rhs);
}

//-----------------------------------------------------------------------------
// double
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<double, NELEM> operator+(
    const accessible<double, NELEM, DEPTH_L> &lhs,
    const accessible<double, NELEM, DEPTH_R> &rhs)
{
        vtype<double, NELEM> res;
        for (size_t i = 0; i < NELEM; i++)
            res.s[i] = lhs.s[i] + rhs.s[i];
        return res;
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<double, NELEM> operator+(
    const accessible<double, NELEM, DEPTH_L> &lhs,
    const double immediate)
{
    return vtype<double, NELEM>(lhs) + vtype<double, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<double, NELEM> operator+(
     const double immediate,
     const accessible<double, NELEM, DEPTH_R> &rhs)
{
    return vtype<double, NELEM>(immediate) + vtype<double, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// int32_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int32_t, NELEM> operator+(
    const accessible<int32_t, NELEM, DEPTH_L> &lhs,
    const accessible<int32_t, NELEM, DEPTH_R> &rhs)
{
    vreg_t res;
    _vaddw_vvv(lhs, rhs, res);
    return vtype<int32_t, NELEM>(res);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int32_t, NELEM> operator+(
    const accessible<int32_t, NELEM, DEPTH_L> &lhs,
    const int32_t immediate)
{
       return vtype<int32_t, NELEM>(lhs) + vtype<int32_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int32_t, NELEM> operator+(
     const int32_t immediate,
     const accessible<int32_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<int32_t, NELEM>(immediate) + vtype<int32_t, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// float
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<float, NELEM> operator+(
    const accessible<float, NELEM, DEPTH_L> &lhs,
    const accessible<float, NELEM, DEPTH_R> &rhs)
{
    vtype<float, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
        res.s[i] = lhs.s[i] + rhs.s[i];
    return res;
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<float, NELEM> operator+(
    const accessible<float, NELEM, DEPTH_L> &lhs,
    const float immediate)
{
       return vtype<float, NELEM>(lhs) + vtype<float, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<float, NELEM> operator+(
     const float immediate,
     const accessible<float, NELEM, DEPTH_R> &rhs)
{
    return vtype<float, NELEM>(immediate) + vtype<float, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// int16_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int16_t, NELEM> operator+(
    const accessible<int16_t, NELEM, DEPTH_L> &lhs,
    const accessible<int16_t, NELEM, DEPTH_R> &rhs)
{
    vreg_t res;
    _vaddh_vvv(lhs, rhs, res);
    return vtype<int16_t, NELEM>(res);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int16_t, NELEM> operator+(
    const accessible<int16_t, NELEM, DEPTH_L> &lhs,
    const int16_t immediate)
{
       return vtype<int16_t, NELEM>(lhs) + vtype<int16_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int16_t, NELEM> operator+(
     const int16_t immediate,
     const accessible<int16_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<int16_t, NELEM>(immediate) + vtype<int16_t, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// int8_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int8_t, NELEM> operator+(
    const accessible<int8_t, NELEM, DEPTH_L> &lhs,
    const accessible<int8_t, NELEM, DEPTH_R> &rhs)
{
    vreg_t res;
    _vaddb_vvv(lhs, rhs, res);
    return vtype<int8_t, NELEM>(res);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int8_t, NELEM> operator+(
    const accessible<int8_t, NELEM, DEPTH_L> &lhs,
    const int8_t immediate)
{
       return vtype<int8_t, NELEM>(lhs) + vtype<int8_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int8_t, NELEM> operator+(
     const int8_t immediate,
     const accessible<int8_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<int8_t, NELEM>(immediate) + vtype<int8_t, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// uint64_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<uint64_t, NELEM> operator+(
    const accessible<uint64_t, NELEM, DEPTH_L> &lhs,
    const accessible<uint64_t, NELEM, DEPTH_R> &rhs)
{
    vreg_t res;
    _vaddd_vvv(lhs, rhs, res);
    return vtype<uint64_t, NELEM>(res);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<uint64_t, NELEM> operator+(
    const accessible<uint64_t, NELEM, DEPTH_L> &lhs,
    const uint64_t immediate)
{
       return vtype<uint64_t, NELEM>(lhs) + vtype<uint64_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<uint64_t, NELEM> operator+(
     const uint64_t immediate,
     const accessible<uint64_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<uint64_t, NELEM>(immediate) + vtype<uint64_t, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// uint32_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<uint32_t, NELEM> operator+(
    const accessible<uint32_t, NELEM, DEPTH_L> &lhs,
    const accessible<uint32_t, NELEM, DEPTH_R> &rhs)
{
    vreg_t res;
    _vaddw_vvv(lhs, rhs, res);
    return vtype<uint32_t, NELEM>(res);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<uint32_t, NELEM> operator+(
    const accessible<uint32_t, NELEM, DEPTH_L> &lhs,
    const uint32_t immediate)
{
       return vtype<uint32_t, NELEM>(lhs) + vtype<uint32_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<uint32_t, NELEM> operator+(
     const uint32_t immediate,
     const accessible<uint32_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<uint32_t, NELEM>(immediate) + vtype<uint32_t, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// uint16_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<uint16_t, NELEM> operator+(
    const accessible<uint16_t, NELEM, DEPTH_L> &lhs,
    const accessible<uint16_t, NELEM, DEPTH_R> &rhs)
{
    vreg_t res;
    _vaddh_vvv(lhs, rhs, res);
    return vtype<uint16_t, NELEM>(res);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<uint16_t, NELEM> operator+(
    const accessible<uint16_t, NELEM, DEPTH_L> &lhs,
    const uint16_t immediate)
{
       return vtype<uint16_t, NELEM>(lhs) + vtype<uint16_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<uint16_t, NELEM> operator+(
     const uint16_t immediate,
     const accessible<uint16_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<uint16_t, NELEM>(immediate) + vtype<uint16_t, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// uint8_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<uint8_t, NELEM> operator+(
    const accessible<uint8_t, NELEM, DEPTH_L> &lhs,
    const accessible<uint8_t, NELEM, DEPTH_R> &rhs)
{
    vreg_t res;
    _vaddb_vvv(lhs, rhs, res);
    return vtype<uint8_t, NELEM>(res);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<uint8_t, NELEM> operator+(
    const accessible<uint8_t, NELEM, DEPTH_L> &lhs,
    const uint8_t immediate)
{
       return vtype<uint8_t, NELEM>(lhs) + vtype<uint8_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<uint8_t, NELEM> operator+(
     const uint8_t immediate,
     const accessible<uint8_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<uint8_t, NELEM>(immediate) + vtype<uint8_t, NELEM>(rhs);
}

//-----------------------------------------------------------------------------
// Operator* overloads
//-----------------------------------------------------------------------------
template <typename ELEM_T, size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<ELEM_T, NELEM> operator*(
    const accessible<ELEM_T, NELEM, DEPTH_L> &lhs,
    const accessible<ELEM_T, NELEM, DEPTH_R> &rhs)
{
    vtype<ELEM_T, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
        res.s[i] = lhs.s[i] * rhs.s[i];
    return res;
}
//-----------------------------------------------------------------------------
// int64_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int64_t, NELEM> operator*(
    const accessible<int64_t, NELEM, DEPTH_L> &lhs,
    const accessible<int64_t, NELEM, DEPTH_R> &rhs)
{
    vreg_t res;
    _vmpydd_vvv(lhs, rhs, res);
    return vtype<int64_t, NELEM>(res);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int64_t, NELEM> operator*(
    const accessible<int64_t, NELEM, DEPTH_L> &lhs,
    const int64_t immediate)
{
       return vtype<int64_t, NELEM>(lhs) * vtype<int64_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int64_t, NELEM> operator*(
     const int64_t immediate,
     const accessible<int64_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<int64_t, NELEM>(immediate) * vtype<int64_t, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// double
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<double, NELEM> operator*(
    const accessible<double, NELEM, DEPTH_L> &lhs,
    const accessible<double, NELEM, DEPTH_R> &rhs)
{
        vtype<double, NELEM> res;
        for (size_t i = 0; i < NELEM; i++)
            res.s[i] = lhs.s[i] * rhs.s[i];
        return res;
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<double, NELEM> operator*(
    const accessible<double, NELEM, DEPTH_L> &lhs,
    const double immediate)
{
       return vtype<double, NELEM>(lhs) * vtype<double, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<double, NELEM> operator*(
     const double immediate,
     const accessible<double, NELEM, DEPTH_R> &rhs)
{
    return vtype<double, NELEM>(immediate) * vtype<double, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// int32_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int32_t, NELEM> operator*(
    const accessible<int32_t, NELEM, DEPTH_L> &lhs,
    const accessible<int32_t, NELEM, DEPTH_R> &rhs)
{
    vreg_t res;
    _vmpyww_vvv(lhs, rhs, res);
    return vtype<int32_t, NELEM>(res);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int32_t, NELEM> operator*(
    const accessible<int32_t, NELEM, DEPTH_L> &lhs,
    const int32_t immediate)
{
       return vtype<int32_t, NELEM>(lhs) * vtype<int32_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int32_t, NELEM> operator*(
     const int32_t immediate,
     const accessible<int32_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<int32_t, NELEM>(immediate) * vtype<int32_t, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// float
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<float, NELEM> operator*(
    const accessible<float, NELEM, DEPTH_L> &lhs,
    const accessible<float, NELEM, DEPTH_R> &rhs)
{
        vtype<float, NELEM> res;
        for (size_t i = 0; i < NELEM; i++)
            res.s[i] = lhs.s[i] * rhs.s[i];
        return res;
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<float, NELEM> operator*(
    const accessible<float, NELEM, DEPTH_L> &lhs,
    const float immediate)
{
       return vtype<float, NELEM>(lhs) * vtype<float, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<float, NELEM> operator*(
     const float immediate,
     const accessible<float, NELEM, DEPTH_R> &rhs)
{
    return vtype<float, NELEM>(immediate) * vtype<float, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// int16_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int16_t, NELEM> operator*(
    const accessible<int16_t, NELEM, DEPTH_L> &lhs,
    const accessible<int16_t, NELEM, DEPTH_R> &rhs)
{
    vreg_t res;
    _vmpyhh_vvv(lhs, rhs, res);
    return vtype<int16_t, NELEM>(res);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int16_t, NELEM> operator*(
    const accessible<int16_t, NELEM, DEPTH_L> &lhs,
    const int16_t immediate)
{
       return vtype<int16_t, NELEM>(lhs) * vtype<int16_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int16_t, NELEM> operator*(
     const int16_t immediate,
     const accessible<int16_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<int16_t, NELEM>(immediate) * vtype<int16_t, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// int8_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int8_t, NELEM> operator*(
    const accessible<int8_t, NELEM, DEPTH_L> &lhs,
    const accessible<int8_t, NELEM, DEPTH_R> &rhs)
{
    vreg_t res;
    _vmpybb_vvv(lhs, rhs, res);
    return vtype<int8_t, NELEM>(res);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int8_t, NELEM> operator*(
    const accessible<int8_t, NELEM, DEPTH_L> &lhs,
    const int8_t immediate)
{
       return vtype<int8_t, NELEM>(lhs) * vtype<int8_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int8_t, NELEM> operator*(
     const int8_t immediate,
     const accessible<int8_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<int8_t, NELEM>(immediate) * vtype<int8_t, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// uint64_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<uint64_t, NELEM> operator*(
    const accessible<uint64_t, NELEM, DEPTH_L> &lhs,
    const accessible<uint64_t, NELEM, DEPTH_R> &rhs)
{
    vreg_t res;
    _vmpydd_vvv(lhs, rhs, res);
    return vtype<uint64_t, NELEM>(res);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<uint64_t, NELEM> operator*(
    const accessible<uint64_t, NELEM, DEPTH_L> &lhs,
    const uint64_t immediate)
{
       return vtype<uint64_t, NELEM>(lhs) * vtype<uint64_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<uint64_t, NELEM> operator*(
     const uint64_t immediate,
     const accessible<uint64_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<uint64_t, NELEM>(immediate) * vtype<uint64_t, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// uint32_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<uint32_t, NELEM> operator*(
    const accessible<uint32_t, NELEM, DEPTH_L> &lhs,
    const accessible<uint32_t, NELEM, DEPTH_R> &rhs)
{
    vreg_t res;
    _vmpyww_vvv(lhs, rhs, res);
    return vtype<uint32_t, NELEM>(res);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<uint32_t, NELEM> operator*(
    const accessible<uint32_t, NELEM, DEPTH_L> &lhs,
    const uint32_t immediate)
{
       return vtype<uint32_t, NELEM>(lhs) * vtype<uint32_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<uint32_t, NELEM> operator*(
     const uint32_t immediate,
     const accessible<uint32_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<uint32_t, NELEM>(immediate) * vtype<uint32_t, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// uint16_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<uint16_t, NELEM> operator*(
    const accessible<uint16_t, NELEM, DEPTH_L> &lhs,
    const accessible<uint16_t, NELEM, DEPTH_R> &rhs)
{
    vreg_t res;
    _vmpyhh_vvv(lhs, rhs, res);
    return vtype<uint16_t, NELEM>(res);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<uint16_t, NELEM> operator*(
    const accessible<uint16_t, NELEM, DEPTH_L> &lhs,
    const uint16_t immediate)
{
       return vtype<uint16_t, NELEM>(lhs) * vtype<uint16_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<uint16_t, NELEM> operator*(
     const uint16_t immediate,
     const accessible<uint16_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<uint16_t, NELEM>(immediate) * vtype<uint16_t, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// uint8_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<uint8_t, NELEM> operator*(
    const accessible<uint8_t, NELEM, DEPTH_L> &lhs,
    const accessible<uint8_t, NELEM, DEPTH_R> &rhs)
{
    vreg_t res;
    _vmpybb_vvv(lhs, rhs, res);
    return vtype<uint8_t, NELEM>(res);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<uint8_t, NELEM> operator*(
    const accessible<uint8_t, NELEM, DEPTH_L> &lhs,
    const uint8_t immediate)
{
       return vtype<uint8_t, NELEM>(lhs) * vtype<uint8_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<uint8_t, NELEM> operator*(
     const uint8_t immediate,
     const accessible<uint8_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<uint8_t, NELEM>(immediate) * vtype<uint8_t, NELEM>(rhs);
}

//-----------------------------------------------------------------------------
// Operator- overloads
//-----------------------------------------------------------------------------
template <typename ELEM_T, size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<ELEM_T, NELEM> operator-(
    const accessible<ELEM_T, NELEM, DEPTH_L> &lhs,
    const accessible<ELEM_T, NELEM, DEPTH_R> &rhs)
{
    vtype<ELEM_T, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
        res.s[i] = lhs.s[i] - rhs.s[i];
    return res;
}
//-----------------------------------------------------------------------------
// int64_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int64_t, NELEM> operator-(
    const accessible<int64_t, NELEM, DEPTH_L> &lhs,
    const accessible<int64_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<int64_t, NELEM>(lhs) + -vtype<int64_t, NELEM>(rhs);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int64_t, NELEM> operator-(
    const accessible<int64_t, NELEM, DEPTH_L> &lhs,
    const int64_t immediate)
{
       return vtype<int64_t, NELEM>(lhs) + -vtype<int64_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int64_t, NELEM> operator-(
     const int64_t immediate,
     const accessible<int64_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<int64_t, NELEM>(immediate) + -vtype<int64_t, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// double
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<double, NELEM> operator-(
    const accessible<double, NELEM, DEPTH_L> &lhs,
    const accessible<double, NELEM, DEPTH_R> &rhs)
{
    return vtype<double, NELEM>(lhs) + -vtype<double, NELEM>(rhs);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<double, NELEM> operator-(
    const accessible<double, NELEM, DEPTH_L> &lhs,
    const double immediate)
{
       return vtype<double, NELEM>(lhs) + -vtype<double, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<double, NELEM> operator-(
     const double immediate,
     const accessible<double, NELEM, DEPTH_R> &rhs)
{
    return vtype<double, NELEM>(immediate) + -vtype<double, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// int32_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int32_t, NELEM> operator-(
    const accessible<int32_t, NELEM, DEPTH_L> &lhs,
    const accessible<int32_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<int32_t, NELEM>(lhs) + -vtype<int32_t, NELEM>(rhs);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int32_t, NELEM> operator-(
    const accessible<int32_t, NELEM, DEPTH_L> &lhs,
    const int32_t immediate)
{
       return vtype<int32_t, NELEM>(lhs) + -vtype<int32_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int32_t, NELEM> operator-(
     const int32_t immediate,
     const accessible<int32_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<int32_t, NELEM>(immediate) + -vtype<int32_t, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// float
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<float, NELEM> operator-(
    const accessible<float, NELEM, DEPTH_L> &lhs,
    const accessible<float, NELEM, DEPTH_R> &rhs)
{
    return vtype<float, NELEM>(lhs) + -vtype<float, NELEM>(rhs);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<float, NELEM> operator-(
    const accessible<float, NELEM, DEPTH_L> &lhs,
    const float immediate)
{
       return vtype<float, NELEM>(lhs) + -vtype<float, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<float, NELEM> operator-(
     const float immediate,
     const accessible<float, NELEM, DEPTH_R> &rhs)
{
    return vtype<float, NELEM>(immediate) + -vtype<float, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// int16_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int16_t, NELEM> operator-(
    const accessible<int16_t, NELEM, DEPTH_L> &lhs,
    const accessible<int16_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<int16_t, NELEM>(lhs) + -vtype<int16_t, NELEM>(rhs);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int16_t, NELEM> operator-(
    const accessible<int16_t, NELEM, DEPTH_L> &lhs,
    const int16_t immediate)
{
       return vtype<int16_t, NELEM>(lhs) + -vtype<int16_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int16_t, NELEM> operator-(
     const int16_t immediate,
     const accessible<int16_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<int16_t, NELEM>(immediate) + -vtype<int16_t, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// int8_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int8_t, NELEM> operator-(
    const accessible<int8_t, NELEM, DEPTH_L> &lhs,
    const accessible<int8_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<int8_t, NELEM>(lhs) + -vtype<int8_t, NELEM>(rhs);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int8_t, NELEM> operator-(
    const accessible<int8_t, NELEM, DEPTH_L> &lhs,
    const int8_t immediate)
{
       return vtype<int8_t, NELEM>(lhs) + -vtype<int8_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int8_t, NELEM> operator-(
     const int8_t immediate,
     const accessible<int8_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<int8_t, NELEM>(immediate) + -vtype<int8_t, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// uint64_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<uint64_t, NELEM> operator-(
    const accessible<uint64_t, NELEM, DEPTH_L> &lhs,
    const accessible<uint64_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<uint64_t, NELEM>(lhs) + -vtype<uint64_t, NELEM>(rhs);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<uint64_t, NELEM> operator-(
    const accessible<uint64_t, NELEM, DEPTH_L> &lhs,
    const uint64_t immediate)
{
       return vtype<uint64_t, NELEM>(lhs) + -vtype<uint64_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<uint64_t, NELEM> operator-(
     const uint64_t immediate,
     const accessible<uint64_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<uint64_t, NELEM>(immediate) + -vtype<uint64_t, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// uint32_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<uint32_t, NELEM> operator-(
    const accessible<uint32_t, NELEM, DEPTH_L> &lhs,
    const accessible<uint32_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<uint32_t, NELEM>(lhs) + -vtype<uint32_t, NELEM>(rhs);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<uint32_t, NELEM> operator-(
    const accessible<uint32_t, NELEM, DEPTH_L> &lhs,
    const uint32_t immediate)
{
       return vtype<uint32_t, NELEM>(lhs) + -vtype<uint32_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<uint32_t, NELEM> operator-(
     const uint32_t immediate,
     const accessible<uint32_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<uint32_t, NELEM>(immediate) + -vtype<uint32_t, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// uint16_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<uint16_t, NELEM> operator-(
    const accessible<uint16_t, NELEM, DEPTH_L> &lhs,
    const accessible<uint16_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<uint16_t, NELEM>(lhs) + -vtype<uint16_t, NELEM>(rhs);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<uint16_t, NELEM> operator-(
    const accessible<uint16_t, NELEM, DEPTH_L> &lhs,
    const uint16_t immediate)
{
       return vtype<uint16_t, NELEM>(lhs) + -vtype<uint16_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<uint16_t, NELEM> operator-(
     const uint16_t immediate,
     const accessible<uint16_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<uint16_t, NELEM>(immediate) + -vtype<uint16_t, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// uint8_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<uint8_t, NELEM> operator-(
    const accessible<uint8_t, NELEM, DEPTH_L> &lhs,
    const accessible<uint8_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<uint8_t, NELEM>(lhs) + -vtype<uint8_t, NELEM>(rhs);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<uint8_t, NELEM> operator-(
    const accessible<uint8_t, NELEM, DEPTH_L> &lhs,
    const uint8_t immediate)
{
       return vtype<uint8_t, NELEM>(lhs) + -vtype<uint8_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<uint8_t, NELEM> operator-(
     const uint8_t immediate,
     const accessible<uint8_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<uint8_t, NELEM>(immediate) + -vtype<uint8_t, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// Operator/ overloads
//-----------------------------------------------------------------------------
template <typename ELEM_T, size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<ELEM_T, NELEM> operator/(
    const accessible<ELEM_T, NELEM, DEPTH_L> &lhs,
    const accessible<ELEM_T, NELEM, DEPTH_R> &rhs)
{
    vtype<ELEM_T, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
        res.s[i] = lhs.s[i] / rhs.s[i];
    return res;
}
//-----------------------------------------------------------------------------
// int64_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int64_t, NELEM> operator/(
    const accessible<int64_t, NELEM, DEPTH_L> &lhs,
    const accessible<int64_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int64_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] / rhs.s[i];
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int64_t, NELEM> operator/(
    const accessible<int64_t, NELEM, DEPTH_L> &lhs,
    const int64_t immediate)
{
       return vtype<int64_t, NELEM>(lhs) / vtype<int64_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int64_t, NELEM> operator/(
     const int64_t immediate,
     const accessible<int64_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<int64_t, NELEM>(immediate) / vtype<int64_t, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// double
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<double, NELEM> operator/(
    const accessible<double, NELEM, DEPTH_L> &lhs,
    const accessible<double, NELEM, DEPTH_R> &rhs)
{
    vtype<double, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] / rhs.s[i];
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<double, NELEM> operator/(
    const accessible<double, NELEM, DEPTH_L> &lhs,
    const double immediate)
{
       return vtype<double, NELEM>(lhs) / vtype<double, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<double, NELEM> operator/(
     const double immediate,
     const accessible<double, NELEM, DEPTH_R> &rhs)
{
    return vtype<double, NELEM>(immediate) / vtype<double, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// int32_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int32_t, NELEM> operator/(
    const accessible<int32_t, NELEM, DEPTH_L> &lhs,
    const accessible<int32_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int32_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] / rhs.s[i];
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int32_t, NELEM> operator/(
    const accessible<int32_t, NELEM, DEPTH_L> &lhs,
    const int32_t immediate)
{
       return vtype<int32_t, NELEM>(lhs) / vtype<int32_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int32_t, NELEM> operator/(
     const int32_t immediate,
     const accessible<int32_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<int32_t, NELEM>(immediate) / vtype<int32_t, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// float
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<float, NELEM> operator/(
    const accessible<float, NELEM, DEPTH_L> &lhs,
    const accessible<float, NELEM, DEPTH_R> &rhs)
{
    vtype<float, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] / rhs.s[i];
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<float, NELEM> operator/(
    const accessible<float, NELEM, DEPTH_L> &lhs,
    const float immediate)
{
       return vtype<float, NELEM>(lhs) / vtype<float, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<float, NELEM> operator/(
     const float immediate,
     const accessible<float, NELEM, DEPTH_R> &rhs)
{
    return vtype<float, NELEM>(immediate) / vtype<float, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// int16_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int16_t, NELEM> operator/(
    const accessible<int16_t, NELEM, DEPTH_L> &lhs,
    const accessible<int16_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int16_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] / rhs.s[i];
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int16_t, NELEM> operator/(
    const accessible<int16_t, NELEM, DEPTH_L> &lhs,
    const int16_t immediate)
{
       return vtype<int16_t, NELEM>(lhs) / vtype<int16_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int16_t, NELEM> operator/(
     const int16_t immediate,
     const accessible<int16_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<int16_t, NELEM>(immediate) / vtype<int16_t, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// int8_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int8_t, NELEM> operator/(
    const accessible<int8_t, NELEM, DEPTH_L> &lhs,
    const accessible<int8_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int8_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] / rhs.s[i];
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int8_t, NELEM> operator/(
    const accessible<int8_t, NELEM, DEPTH_L> &lhs,
    const int8_t immediate)
{
       return vtype<int8_t, NELEM>(lhs) / vtype<int8_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int8_t, NELEM> operator/(
     const int8_t immediate,
     const accessible<int8_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<int8_t, NELEM>(immediate) / vtype<int8_t, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// uint64_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<uint64_t, NELEM> operator/(
    const accessible<uint64_t, NELEM, DEPTH_L> &lhs,
    const accessible<uint64_t, NELEM, DEPTH_R> &rhs)
{
    vtype<uint64_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] / rhs.s[i];
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<uint64_t, NELEM> operator/(
    const accessible<uint64_t, NELEM, DEPTH_L> &lhs,
    const uint64_t immediate)
{
       return vtype<uint64_t, NELEM>(lhs) / vtype<uint64_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<uint64_t, NELEM> operator/(
     const uint64_t immediate,
     const accessible<uint64_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<uint64_t, NELEM>(immediate) / vtype<uint64_t, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// uint32_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<uint32_t, NELEM> operator/(
    const accessible<uint32_t, NELEM, DEPTH_L> &lhs,
    const accessible<uint32_t, NELEM, DEPTH_R> &rhs)
{
    vtype<uint32_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] / rhs.s[i];
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<uint32_t, NELEM> operator/(
    const accessible<uint32_t, NELEM, DEPTH_L> &lhs,
    const uint32_t immediate)
{
       return vtype<uint32_t, NELEM>(lhs) / vtype<uint32_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<uint32_t, NELEM> operator/(
     const uint32_t immediate,
     const accessible<uint32_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<uint32_t, NELEM>(immediate) / vtype<uint32_t, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// uint16_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<uint16_t, NELEM> operator/(
    const accessible<uint16_t, NELEM, DEPTH_L> &lhs,
    const accessible<uint16_t, NELEM, DEPTH_R> &rhs)
{
    vtype<uint16_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] / rhs.s[i];
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<uint16_t, NELEM> operator/(
    const accessible<uint16_t, NELEM, DEPTH_L> &lhs,
    const uint16_t immediate)
{
       return vtype<uint16_t, NELEM>(lhs) / vtype<uint16_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<uint16_t, NELEM> operator/(
     const uint16_t immediate,
     const accessible<uint16_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<uint16_t, NELEM>(immediate) / vtype<uint16_t, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// uint8_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<uint8_t, NELEM> operator/(
    const accessible<uint8_t, NELEM, DEPTH_L> &lhs,
    const accessible<uint8_t, NELEM, DEPTH_R> &rhs)
{
    vtype<uint8_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] / rhs.s[i];
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<uint8_t, NELEM> operator/(
    const accessible<uint8_t, NELEM, DEPTH_L> &lhs,
    const uint8_t immediate)
{
       return vtype<uint8_t, NELEM>(lhs) / vtype<uint8_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<uint8_t, NELEM> operator/(
     const uint8_t immediate,
     const accessible<uint8_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<uint8_t, NELEM>(immediate) / vtype<uint8_t, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// Operator% overloads
//-----------------------------------------------------------------------------
template <typename ELEM_T, size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<ELEM_T, NELEM> operator%(
    const accessible<ELEM_T, NELEM, DEPTH_L> &lhs,
    const accessible<ELEM_T, NELEM, DEPTH_R> &rhs
);
//-----------------------------------------------------------------------------
// int64_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int64_t, NELEM> operator%(
    const accessible<int64_t, NELEM, DEPTH_L> &lhs,
    const accessible<int64_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int64_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] % rhs.s[i];
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int64_t, NELEM> operator%(
    const accessible<int64_t, NELEM, DEPTH_L> &lhs,
    const int64_t immediate)
{
       return vtype<int64_t, NELEM>(lhs) % vtype<int64_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int64_t, NELEM> operator%(
     const int64_t immediate,
     const accessible<int64_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<int64_t, NELEM>(immediate) % vtype<int64_t, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// int32_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int32_t, NELEM> operator%(
    const accessible<int32_t, NELEM, DEPTH_L> &lhs,
    const accessible<int32_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int32_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] % rhs.s[i];
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int32_t, NELEM> operator%(
    const accessible<int32_t, NELEM, DEPTH_L> &lhs,
    const int32_t immediate)
{
       return vtype<int32_t, NELEM>(lhs) % vtype<int32_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int32_t, NELEM> operator%(
     const int32_t immediate,
     const accessible<int32_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<int32_t, NELEM>(immediate) % vtype<int32_t, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// int16_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int16_t, NELEM> operator%(
    const accessible<int16_t, NELEM, DEPTH_L> &lhs,
    const accessible<int16_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int16_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] % rhs.s[i];
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int16_t, NELEM> operator%(
    const accessible<int16_t, NELEM, DEPTH_L> &lhs,
    const int16_t immediate)
{
       return vtype<int16_t, NELEM>(lhs) % vtype<int16_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int16_t, NELEM> operator%(
     const int16_t immediate,
     const accessible<int16_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<int16_t, NELEM>(immediate) % vtype<int16_t, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// int8_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int8_t, NELEM> operator%(
    const accessible<int8_t, NELEM, DEPTH_L> &lhs,
    const accessible<int8_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int8_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] % rhs.s[i];
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int8_t, NELEM> operator%(
    const accessible<int8_t, NELEM, DEPTH_L> &lhs,
    const int8_t immediate)
{
       return vtype<int8_t, NELEM>(lhs) % vtype<int8_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int8_t, NELEM> operator%(
     const int8_t immediate,
     const accessible<int8_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<int8_t, NELEM>(immediate) % vtype<int8_t, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// uint64_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<uint64_t, NELEM> operator%(
    const accessible<uint64_t, NELEM, DEPTH_L> &lhs,
    const accessible<uint64_t, NELEM, DEPTH_R> &rhs)
{
    vtype<uint64_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] % rhs.s[i];
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<uint64_t, NELEM> operator%(
    const accessible<uint64_t, NELEM, DEPTH_L> &lhs,
    const uint64_t immediate)
{
       return vtype<uint64_t, NELEM>(lhs) % vtype<uint64_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<uint64_t, NELEM> operator%(
     const uint64_t immediate,
     const accessible<uint64_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<uint64_t, NELEM>(immediate) % vtype<uint64_t, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// uint32_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<uint32_t, NELEM> operator%(
    const accessible<uint32_t, NELEM, DEPTH_L> &lhs,
    const accessible<uint32_t, NELEM, DEPTH_R> &rhs)
{
    vtype<uint32_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] % rhs.s[i];
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<uint32_t, NELEM> operator%(
    const accessible<uint32_t, NELEM, DEPTH_L> &lhs,
    const uint32_t immediate)
{
       return vtype<uint32_t, NELEM>(lhs) % vtype<uint32_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<uint32_t, NELEM> operator%(
     const uint32_t immediate,
     const accessible<uint32_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<uint32_t, NELEM>(immediate) % vtype<uint32_t, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// uint16_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<uint16_t, NELEM> operator%(
    const accessible<uint16_t, NELEM, DEPTH_L> &lhs,
    const accessible<uint16_t, NELEM, DEPTH_R> &rhs)
{
    vtype<uint16_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] % rhs.s[i];
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<uint16_t, NELEM> operator%(
    const accessible<uint16_t, NELEM, DEPTH_L> &lhs,
    const uint16_t immediate)
{
       return vtype<uint16_t, NELEM>(lhs) % vtype<uint16_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<uint16_t, NELEM> operator%(
     const uint16_t immediate,
     const accessible<uint16_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<uint16_t, NELEM>(immediate) % vtype<uint16_t, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// uint8_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<uint8_t, NELEM> operator%(
    const accessible<uint8_t, NELEM, DEPTH_L> &lhs,
    const accessible<uint8_t, NELEM, DEPTH_R> &rhs)
{
    vtype<uint8_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] % rhs.s[i];
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<uint8_t, NELEM> operator%(
    const accessible<uint8_t, NELEM, DEPTH_L> &lhs,
    const uint8_t immediate)
{
       return vtype<uint8_t, NELEM>(lhs) % vtype<uint8_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<uint8_t, NELEM> operator%(
     const uint8_t immediate,
     const accessible<uint8_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<uint8_t, NELEM>(immediate) % vtype<uint8_t, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// Relational Operator overloads
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// int64_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int64_t, NELEM> operator>(
    const accessible<int64_t, NELEM, DEPTH_L> &lhs,
    const accessible<int64_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int64_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] > rhs.s[i] ? (int64_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int64_t, NELEM> operator>=(
    const accessible<int64_t, NELEM, DEPTH_L> &lhs,
    const accessible<int64_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int64_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] >= rhs.s[i] ? (int64_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int64_t, NELEM> operator<(
    const accessible<int64_t, NELEM, DEPTH_L> &lhs,
    const accessible<int64_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int64_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] < rhs.s[i] ? (int64_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int64_t, NELEM> operator<=(
    const accessible<int64_t, NELEM, DEPTH_L> &lhs,
    const accessible<int64_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int64_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] <= rhs.s[i] ? (int64_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int64_t, NELEM> operator==(
    const accessible<int64_t, NELEM, DEPTH_L> &lhs,
    const accessible<int64_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int64_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] == rhs.s[i] ? (int64_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int64_t, NELEM> operator!=(
    const accessible<int64_t, NELEM, DEPTH_L> &lhs,
    const accessible<int64_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int64_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] != rhs.s[i] ? (int64_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int64_t, NELEM> operator>(
    const accessible<int64_t, NELEM, DEPTH_L> &lhs,
    const int64_t immediate)
{
	return  vtype<int64_t, NELEM>(lhs) > vtype<int64_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int64_t, NELEM> operator>(
     const int64_t immediate,
     const accessible<int64_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<int64_t, NELEM>(immediate) > vtype<int64_t, NELEM>(rhs);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int64_t, NELEM> operator>=(
    const accessible<int64_t, NELEM, DEPTH_L> &lhs,
    const int64_t immediate)
{
	return  vtype<int64_t, NELEM>(lhs) >= vtype<int64_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int64_t, NELEM> operator>=(
     const int64_t immediate,
     const accessible<int64_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<int64_t, NELEM>(immediate) >= vtype<int64_t, NELEM>(rhs);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int64_t, NELEM> operator<(
    const accessible<int64_t, NELEM, DEPTH_L> &lhs,
    const int64_t immediate)
{
	return  vtype<int64_t, NELEM>(lhs) < vtype<int64_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int64_t, NELEM> operator<(
     const int64_t immediate,
     const accessible<int64_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<int64_t, NELEM>(immediate) < vtype<int64_t, NELEM>(rhs);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int64_t, NELEM> operator<=(
    const accessible<int64_t, NELEM, DEPTH_L> &lhs,
    const int64_t immediate)
{
	return  vtype<int64_t, NELEM>(lhs) <= vtype<int64_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int64_t, NELEM> operator<=(
     const int64_t immediate,
     const accessible<int64_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<int64_t, NELEM>(immediate) <= vtype<int64_t, NELEM>(rhs);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int64_t, NELEM> operator==(
    const accessible<int64_t, NELEM, DEPTH_L> &lhs,
    const int64_t immediate)
{
	return  vtype<int64_t, NELEM>(lhs) == vtype<int64_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int64_t, NELEM> operator==(
     const int64_t immediate,
     const accessible<int64_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<int64_t, NELEM>(immediate) == vtype<int64_t, NELEM>(rhs);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int64_t, NELEM> operator!=(
    const accessible<int64_t, NELEM, DEPTH_L> &lhs,
    const int64_t immediate)
{
	return  vtype<int64_t, NELEM>(lhs) != vtype<int64_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int64_t, NELEM> operator!=(
     const int64_t immediate,
     const accessible<int64_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<int64_t, NELEM>(immediate) != vtype<int64_t, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// double
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int64_t, NELEM> operator>(
    const accessible<double, NELEM, DEPTH_L> &lhs,
    const accessible<double, NELEM, DEPTH_R> &rhs)
{
    vtype<int64_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] > rhs.s[i] ? (int64_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int64_t, NELEM> operator>=(
    const accessible<double, NELEM, DEPTH_L> &lhs,
    const accessible<double, NELEM, DEPTH_R> &rhs)
{
    vtype<int64_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] >= rhs.s[i] ? (int64_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int64_t, NELEM> operator<(
    const accessible<double, NELEM, DEPTH_L> &lhs,
    const accessible<double, NELEM, DEPTH_R> &rhs)
{
    vtype<int64_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] < rhs.s[i] ? (int64_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int64_t, NELEM> operator<=(
    const accessible<double, NELEM, DEPTH_L> &lhs,
    const accessible<double, NELEM, DEPTH_R> &rhs)
{
    vtype<int64_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] <= rhs.s[i] ? (int64_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int64_t, NELEM> operator==(
    const accessible<double, NELEM, DEPTH_L> &lhs,
    const accessible<double, NELEM, DEPTH_R> &rhs)
{
    vtype<int64_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] == rhs.s[i] ? (int64_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int64_t, NELEM> operator!=(
    const accessible<double, NELEM, DEPTH_L> &lhs,
    const accessible<double, NELEM, DEPTH_R> &rhs)
{
    vtype<int64_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] != rhs.s[i] ? (int64_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int64_t, NELEM> operator>(
    const accessible<double, NELEM, DEPTH_L> &lhs,
    const double immediate)
{
	return  vtype<double, NELEM>(lhs) > vtype<double, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int64_t, NELEM> operator>(
     const double immediate,
     const accessible<double, NELEM, DEPTH_R> &rhs)
{
    return vtype<double, NELEM>(immediate) > vtype<double, NELEM>(rhs);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int64_t, NELEM> operator>=(
    const accessible<double, NELEM, DEPTH_L> &lhs,
    const double immediate)
{
	return  vtype<double, NELEM>(lhs) >= vtype<double, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int64_t, NELEM> operator>=(
     const double immediate,
     const accessible<double, NELEM, DEPTH_R> &rhs)
{
    return vtype<double, NELEM>(immediate) >= vtype<double, NELEM>(rhs);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int64_t, NELEM> operator<(
    const accessible<double, NELEM, DEPTH_L> &lhs,
    const double immediate)
{
	return  vtype<double, NELEM>(lhs) < vtype<double, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int64_t, NELEM> operator<(
     const double immediate,
     const accessible<double, NELEM, DEPTH_R> &rhs)
{
    return vtype<double, NELEM>(immediate) < vtype<double, NELEM>(rhs);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int64_t, NELEM> operator<=(
    const accessible<double, NELEM, DEPTH_L> &lhs,
    const double immediate)
{
	return  vtype<double, NELEM>(lhs) <= vtype<double, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int64_t, NELEM> operator<=(
     const double immediate,
     const accessible<double, NELEM, DEPTH_R> &rhs)
{
    return vtype<double, NELEM>(immediate) <= vtype<double, NELEM>(rhs);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int64_t, NELEM> operator==(
    const accessible<double, NELEM, DEPTH_L> &lhs,
    const double immediate)
{
	return  vtype<double, NELEM>(lhs) == vtype<double, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int64_t, NELEM> operator==(
     const double immediate,
     const accessible<double, NELEM, DEPTH_R> &rhs)
{
    return vtype<double, NELEM>(immediate) == vtype<double, NELEM>(rhs);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int64_t, NELEM> operator!=(
    const accessible<double, NELEM, DEPTH_L> &lhs,
    const double immediate)
{
	return  vtype<double, NELEM>(lhs) != vtype<double, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int64_t, NELEM> operator!=(
     const double immediate,
     const accessible<double, NELEM, DEPTH_R> &rhs)
{
    return vtype<double, NELEM>(immediate) != vtype<double, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// int32_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int32_t, NELEM> operator>(
    const accessible<int32_t, NELEM, DEPTH_L> &lhs,
    const accessible<int32_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int32_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] > rhs.s[i] ? (int32_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int32_t, NELEM> operator>=(
    const accessible<int32_t, NELEM, DEPTH_L> &lhs,
    const accessible<int32_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int32_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] >= rhs.s[i] ? (int32_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int32_t, NELEM> operator<(
    const accessible<int32_t, NELEM, DEPTH_L> &lhs,
    const accessible<int32_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int32_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] < rhs.s[i] ? (int32_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int32_t, NELEM> operator<=(
    const accessible<int32_t, NELEM, DEPTH_L> &lhs,
    const accessible<int32_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int32_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] <= rhs.s[i] ? (int32_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int32_t, NELEM> operator==(
    const accessible<int32_t, NELEM, DEPTH_L> &lhs,
    const accessible<int32_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int32_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] == rhs.s[i] ? (int32_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int32_t, NELEM> operator!=(
    const accessible<int32_t, NELEM, DEPTH_L> &lhs,
    const accessible<int32_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int32_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] != rhs.s[i] ? (int32_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int32_t, NELEM> operator>(
    const accessible<int32_t, NELEM, DEPTH_L> &lhs,
    const int32_t immediate)
{
	return  vtype<int32_t, NELEM>(lhs) > vtype<int32_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int32_t, NELEM> operator>(
     const int32_t immediate,
     const accessible<int32_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<int32_t, NELEM>(immediate) > vtype<int32_t, NELEM>(rhs);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int32_t, NELEM> operator>=(
    const accessible<int32_t, NELEM, DEPTH_L> &lhs,
    const int32_t immediate)
{
	return  vtype<int32_t, NELEM>(lhs) >= vtype<int32_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int32_t, NELEM> operator>=(
     const int32_t immediate,
     const accessible<int32_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<int32_t, NELEM>(immediate) >= vtype<int32_t, NELEM>(rhs);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int32_t, NELEM> operator<(
    const accessible<int32_t, NELEM, DEPTH_L> &lhs,
    const int32_t immediate)
{
	return  vtype<int32_t, NELEM>(lhs) < vtype<int32_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int32_t, NELEM> operator<(
     const int32_t immediate,
     const accessible<int32_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<int32_t, NELEM>(immediate) < vtype<int32_t, NELEM>(rhs);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int32_t, NELEM> operator<=(
    const accessible<int32_t, NELEM, DEPTH_L> &lhs,
    const int32_t immediate)
{
	return  vtype<int32_t, NELEM>(lhs) <= vtype<int32_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int32_t, NELEM> operator<=(
     const int32_t immediate,
     const accessible<int32_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<int32_t, NELEM>(immediate) <= vtype<int32_t, NELEM>(rhs);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int32_t, NELEM> operator==(
    const accessible<int32_t, NELEM, DEPTH_L> &lhs,
    const int32_t immediate)
{
	return  vtype<int32_t, NELEM>(lhs) == vtype<int32_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int32_t, NELEM> operator==(
     const int32_t immediate,
     const accessible<int32_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<int32_t, NELEM>(immediate) == vtype<int32_t, NELEM>(rhs);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int32_t, NELEM> operator!=(
    const accessible<int32_t, NELEM, DEPTH_L> &lhs,
    const int32_t immediate)
{
	return  vtype<int32_t, NELEM>(lhs) != vtype<int32_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int32_t, NELEM> operator!=(
     const int32_t immediate,
     const accessible<int32_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<int32_t, NELEM>(immediate) != vtype<int32_t, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// float
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int32_t, NELEM> operator>(
    const accessible<float, NELEM, DEPTH_L> &lhs,
    const accessible<float, NELEM, DEPTH_R> &rhs)
{
    vtype<int32_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] > rhs.s[i] ? (int32_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int32_t, NELEM> operator>=(
    const accessible<float, NELEM, DEPTH_L> &lhs,
    const accessible<float, NELEM, DEPTH_R> &rhs)
{
    vtype<int32_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] >= rhs.s[i] ? (int32_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int32_t, NELEM> operator<(
    const accessible<float, NELEM, DEPTH_L> &lhs,
    const accessible<float, NELEM, DEPTH_R> &rhs)
{
    vtype<int32_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] < rhs.s[i] ? (int32_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int32_t, NELEM> operator<=(
    const accessible<float, NELEM, DEPTH_L> &lhs,
    const accessible<float, NELEM, DEPTH_R> &rhs)
{
    vtype<int32_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] <= rhs.s[i] ? (int32_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int32_t, NELEM> operator==(
    const accessible<float, NELEM, DEPTH_L> &lhs,
    const accessible<float, NELEM, DEPTH_R> &rhs)
{
    vtype<int32_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] == rhs.s[i] ? (int32_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int32_t, NELEM> operator!=(
    const accessible<float, NELEM, DEPTH_L> &lhs,
    const accessible<float, NELEM, DEPTH_R> &rhs)
{
    vtype<int32_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] != rhs.s[i] ? (int32_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int32_t, NELEM> operator>(
    const accessible<float, NELEM, DEPTH_L> &lhs,
    const float immediate)
{
	return  vtype<float, NELEM>(lhs) > vtype<float, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int32_t, NELEM> operator>(
     const float immediate,
     const accessible<float, NELEM, DEPTH_R> &rhs)
{
    return vtype<float, NELEM>(immediate) > vtype<float, NELEM>(rhs);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int32_t, NELEM> operator>=(
    const accessible<float, NELEM, DEPTH_L> &lhs,
    const float immediate)
{
	return  vtype<float, NELEM>(lhs) >= vtype<float, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int32_t, NELEM> operator>=(
     const float immediate,
     const accessible<float, NELEM, DEPTH_R> &rhs)
{
    return vtype<float, NELEM>(immediate) >= vtype<float, NELEM>(rhs);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int32_t, NELEM> operator<(
    const accessible<float, NELEM, DEPTH_L> &lhs,
    const float immediate)
{
	return  vtype<float, NELEM>(lhs) < vtype<float, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int32_t, NELEM> operator<(
     const float immediate,
     const accessible<float, NELEM, DEPTH_R> &rhs)
{
    return vtype<float, NELEM>(immediate) < vtype<float, NELEM>(rhs);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int32_t, NELEM> operator<=(
    const accessible<float, NELEM, DEPTH_L> &lhs,
    const float immediate)
{
	return  vtype<float, NELEM>(lhs) <= vtype<float, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int32_t, NELEM> operator<=(
     const float immediate,
     const accessible<float, NELEM, DEPTH_R> &rhs)
{
    return vtype<float, NELEM>(immediate) <= vtype<float, NELEM>(rhs);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int32_t, NELEM> operator==(
    const accessible<float, NELEM, DEPTH_L> &lhs,
    const float immediate)
{
	return  vtype<float, NELEM>(lhs) == vtype<float, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int32_t, NELEM> operator==(
     const float immediate,
     const accessible<float, NELEM, DEPTH_R> &rhs)
{
    return vtype<float, NELEM>(immediate) == vtype<float, NELEM>(rhs);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int32_t, NELEM> operator!=(
    const accessible<float, NELEM, DEPTH_L> &lhs,
    const float immediate)
{
	return  vtype<float, NELEM>(lhs) != vtype<float, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int32_t, NELEM> operator!=(
     const float immediate,
     const accessible<float, NELEM, DEPTH_R> &rhs)
{
    return vtype<float, NELEM>(immediate) != vtype<float, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// int16_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int16_t, NELEM> operator>(
    const accessible<int16_t, NELEM, DEPTH_L> &lhs,
    const accessible<int16_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int16_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] > rhs.s[i] ? (int16_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int16_t, NELEM> operator>=(
    const accessible<int16_t, NELEM, DEPTH_L> &lhs,
    const accessible<int16_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int16_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] >= rhs.s[i] ? (int16_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int16_t, NELEM> operator<(
    const accessible<int16_t, NELEM, DEPTH_L> &lhs,
    const accessible<int16_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int16_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] < rhs.s[i] ? (int16_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int16_t, NELEM> operator<=(
    const accessible<int16_t, NELEM, DEPTH_L> &lhs,
    const accessible<int16_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int16_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] <= rhs.s[i] ? (int16_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int16_t, NELEM> operator==(
    const accessible<int16_t, NELEM, DEPTH_L> &lhs,
    const accessible<int16_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int16_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] == rhs.s[i] ? (int16_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int16_t, NELEM> operator!=(
    const accessible<int16_t, NELEM, DEPTH_L> &lhs,
    const accessible<int16_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int16_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] != rhs.s[i] ? (int16_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int16_t, NELEM> operator>(
    const accessible<int16_t, NELEM, DEPTH_L> &lhs,
    const int16_t immediate)
{
	return  vtype<int16_t, NELEM>(lhs) > vtype<int16_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int16_t, NELEM> operator>(
     const int16_t immediate,
     const accessible<int16_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<int16_t, NELEM>(immediate) > vtype<int16_t, NELEM>(rhs);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int16_t, NELEM> operator>=(
    const accessible<int16_t, NELEM, DEPTH_L> &lhs,
    const int16_t immediate)
{
	return  vtype<int16_t, NELEM>(lhs) >= vtype<int16_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int16_t, NELEM> operator>=(
     const int16_t immediate,
     const accessible<int16_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<int16_t, NELEM>(immediate) >= vtype<int16_t, NELEM>(rhs);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int16_t, NELEM> operator<(
    const accessible<int16_t, NELEM, DEPTH_L> &lhs,
    const int16_t immediate)
{
	return  vtype<int16_t, NELEM>(lhs) < vtype<int16_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int16_t, NELEM> operator<(
     const int16_t immediate,
     const accessible<int16_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<int16_t, NELEM>(immediate) < vtype<int16_t, NELEM>(rhs);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int16_t, NELEM> operator<=(
    const accessible<int16_t, NELEM, DEPTH_L> &lhs,
    const int16_t immediate)
{
	return  vtype<int16_t, NELEM>(lhs) <= vtype<int16_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int16_t, NELEM> operator<=(
     const int16_t immediate,
     const accessible<int16_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<int16_t, NELEM>(immediate) <= vtype<int16_t, NELEM>(rhs);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int16_t, NELEM> operator==(
    const accessible<int16_t, NELEM, DEPTH_L> &lhs,
    const int16_t immediate)
{
	return  vtype<int16_t, NELEM>(lhs) == vtype<int16_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int16_t, NELEM> operator==(
     const int16_t immediate,
     const accessible<int16_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<int16_t, NELEM>(immediate) == vtype<int16_t, NELEM>(rhs);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int16_t, NELEM> operator!=(
    const accessible<int16_t, NELEM, DEPTH_L> &lhs,
    const int16_t immediate)
{
	return  vtype<int16_t, NELEM>(lhs) != vtype<int16_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int16_t, NELEM> operator!=(
     const int16_t immediate,
     const accessible<int16_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<int16_t, NELEM>(immediate) != vtype<int16_t, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// int8_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int8_t, NELEM> operator>(
    const accessible<int8_t, NELEM, DEPTH_L> &lhs,
    const accessible<int8_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int8_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] > rhs.s[i] ? (int8_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int8_t, NELEM> operator>=(
    const accessible<int8_t, NELEM, DEPTH_L> &lhs,
    const accessible<int8_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int8_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] >= rhs.s[i] ? (int8_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int8_t, NELEM> operator<(
    const accessible<int8_t, NELEM, DEPTH_L> &lhs,
    const accessible<int8_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int8_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] < rhs.s[i] ? (int8_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int8_t, NELEM> operator<=(
    const accessible<int8_t, NELEM, DEPTH_L> &lhs,
    const accessible<int8_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int8_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] <= rhs.s[i] ? (int8_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int8_t, NELEM> operator==(
    const accessible<int8_t, NELEM, DEPTH_L> &lhs,
    const accessible<int8_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int8_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] == rhs.s[i] ? (int8_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int8_t, NELEM> operator!=(
    const accessible<int8_t, NELEM, DEPTH_L> &lhs,
    const accessible<int8_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int8_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] != rhs.s[i] ? (int8_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int8_t, NELEM> operator>(
    const accessible<int8_t, NELEM, DEPTH_L> &lhs,
    const int8_t immediate)
{
	return  vtype<int8_t, NELEM>(lhs) > vtype<int8_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int8_t, NELEM> operator>(
     const int8_t immediate,
     const accessible<int8_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<int8_t, NELEM>(immediate) > vtype<int8_t, NELEM>(rhs);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int8_t, NELEM> operator>=(
    const accessible<int8_t, NELEM, DEPTH_L> &lhs,
    const int8_t immediate)
{
	return  vtype<int8_t, NELEM>(lhs) >= vtype<int8_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int8_t, NELEM> operator>=(
     const int8_t immediate,
     const accessible<int8_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<int8_t, NELEM>(immediate) >= vtype<int8_t, NELEM>(rhs);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int8_t, NELEM> operator<(
    const accessible<int8_t, NELEM, DEPTH_L> &lhs,
    const int8_t immediate)
{
	return  vtype<int8_t, NELEM>(lhs) < vtype<int8_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int8_t, NELEM> operator<(
     const int8_t immediate,
     const accessible<int8_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<int8_t, NELEM>(immediate) < vtype<int8_t, NELEM>(rhs);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int8_t, NELEM> operator<=(
    const accessible<int8_t, NELEM, DEPTH_L> &lhs,
    const int8_t immediate)
{
	return  vtype<int8_t, NELEM>(lhs) <= vtype<int8_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int8_t, NELEM> operator<=(
     const int8_t immediate,
     const accessible<int8_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<int8_t, NELEM>(immediate) <= vtype<int8_t, NELEM>(rhs);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int8_t, NELEM> operator==(
    const accessible<int8_t, NELEM, DEPTH_L> &lhs,
    const int8_t immediate)
{
	return  vtype<int8_t, NELEM>(lhs) == vtype<int8_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int8_t, NELEM> operator==(
     const int8_t immediate,
     const accessible<int8_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<int8_t, NELEM>(immediate) == vtype<int8_t, NELEM>(rhs);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int8_t, NELEM> operator!=(
    const accessible<int8_t, NELEM, DEPTH_L> &lhs,
    const int8_t immediate)
{
	return  vtype<int8_t, NELEM>(lhs) != vtype<int8_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int8_t, NELEM> operator!=(
     const int8_t immediate,
     const accessible<int8_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<int8_t, NELEM>(immediate) != vtype<int8_t, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// uint64_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int64_t, NELEM> operator>(
    const accessible<uint64_t, NELEM, DEPTH_L> &lhs,
    const accessible<uint64_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int64_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] > rhs.s[i] ? (int64_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int64_t, NELEM> operator>=(
    const accessible<uint64_t, NELEM, DEPTH_L> &lhs,
    const accessible<uint64_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int64_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] >= rhs.s[i] ? (int64_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int64_t, NELEM> operator<(
    const accessible<uint64_t, NELEM, DEPTH_L> &lhs,
    const accessible<uint64_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int64_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] < rhs.s[i] ? (int64_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int64_t, NELEM> operator<=(
    const accessible<uint64_t, NELEM, DEPTH_L> &lhs,
    const accessible<uint64_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int64_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] <= rhs.s[i] ? (int64_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int64_t, NELEM> operator==(
    const accessible<uint64_t, NELEM, DEPTH_L> &lhs,
    const accessible<uint64_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int64_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] == rhs.s[i] ? (int64_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int64_t, NELEM> operator!=(
    const accessible<uint64_t, NELEM, DEPTH_L> &lhs,
    const accessible<uint64_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int64_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] != rhs.s[i] ? (int64_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int64_t, NELEM> operator>(
    const accessible<uint64_t, NELEM, DEPTH_L> &lhs,
    const uint64_t immediate)
{
	return  vtype<uint64_t, NELEM>(lhs) > vtype<uint64_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int64_t, NELEM> operator>(
     const uint64_t immediate,
     const accessible<uint64_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<uint64_t, NELEM>(immediate) > vtype<uint64_t, NELEM>(rhs);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int64_t, NELEM> operator>=(
    const accessible<uint64_t, NELEM, DEPTH_L> &lhs,
    const uint64_t immediate)
{
	return  vtype<uint64_t, NELEM>(lhs) >= vtype<uint64_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int64_t, NELEM> operator>=(
     const uint64_t immediate,
     const accessible<uint64_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<uint64_t, NELEM>(immediate) >= vtype<uint64_t, NELEM>(rhs);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int64_t, NELEM> operator<(
    const accessible<uint64_t, NELEM, DEPTH_L> &lhs,
    const uint64_t immediate)
{
	return  vtype<uint64_t, NELEM>(lhs) < vtype<uint64_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int64_t, NELEM> operator<(
     const uint64_t immediate,
     const accessible<uint64_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<uint64_t, NELEM>(immediate) < vtype<uint64_t, NELEM>(rhs);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int64_t, NELEM> operator<=(
    const accessible<uint64_t, NELEM, DEPTH_L> &lhs,
    const uint64_t immediate)
{
	return  vtype<uint64_t, NELEM>(lhs) <= vtype<uint64_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int64_t, NELEM> operator<=(
     const uint64_t immediate,
     const accessible<uint64_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<uint64_t, NELEM>(immediate) <= vtype<uint64_t, NELEM>(rhs);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int64_t, NELEM> operator==(
    const accessible<uint64_t, NELEM, DEPTH_L> &lhs,
    const uint64_t immediate)
{
	return  vtype<uint64_t, NELEM>(lhs) == vtype<uint64_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int64_t, NELEM> operator==(
     const uint64_t immediate,
     const accessible<uint64_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<uint64_t, NELEM>(immediate) == vtype<uint64_t, NELEM>(rhs);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int64_t, NELEM> operator!=(
    const accessible<uint64_t, NELEM, DEPTH_L> &lhs,
    const uint64_t immediate)
{
	return  vtype<uint64_t, NELEM>(lhs) != vtype<uint64_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int64_t, NELEM> operator!=(
     const uint64_t immediate,
     const accessible<uint64_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<uint64_t, NELEM>(immediate) != vtype<uint64_t, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// uint32_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int32_t, NELEM> operator>(
    const accessible<uint32_t, NELEM, DEPTH_L> &lhs,
    const accessible<uint32_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int32_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] > rhs.s[i] ? (int32_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int32_t, NELEM> operator>=(
    const accessible<uint32_t, NELEM, DEPTH_L> &lhs,
    const accessible<uint32_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int32_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] >= rhs.s[i] ? (int32_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int32_t, NELEM> operator<(
    const accessible<uint32_t, NELEM, DEPTH_L> &lhs,
    const accessible<uint32_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int32_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] < rhs.s[i] ? (int32_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int32_t, NELEM> operator<=(
    const accessible<uint32_t, NELEM, DEPTH_L> &lhs,
    const accessible<uint32_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int32_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] <= rhs.s[i] ? (int32_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int32_t, NELEM> operator==(
    const accessible<uint32_t, NELEM, DEPTH_L> &lhs,
    const accessible<uint32_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int32_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] == rhs.s[i] ? (int32_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int32_t, NELEM> operator!=(
    const accessible<uint32_t, NELEM, DEPTH_L> &lhs,
    const accessible<uint32_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int32_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] != rhs.s[i] ? (int32_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int32_t, NELEM> operator>(
    const accessible<uint32_t, NELEM, DEPTH_L> &lhs,
    const uint32_t immediate)
{
	return  vtype<uint32_t, NELEM>(lhs) > vtype<uint32_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int32_t, NELEM> operator>(
     const uint32_t immediate,
     const accessible<uint32_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<uint32_t, NELEM>(immediate) > vtype<uint32_t, NELEM>(rhs);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int32_t, NELEM> operator>=(
    const accessible<uint32_t, NELEM, DEPTH_L> &lhs,
    const uint32_t immediate)
{
	return  vtype<uint32_t, NELEM>(lhs) >= vtype<uint32_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int32_t, NELEM> operator>=(
     const uint32_t immediate,
     const accessible<uint32_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<uint32_t, NELEM>(immediate) >= vtype<uint32_t, NELEM>(rhs);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int32_t, NELEM> operator<(
    const accessible<uint32_t, NELEM, DEPTH_L> &lhs,
    const uint32_t immediate)
{
	return  vtype<uint32_t, NELEM>(lhs) < vtype<uint32_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int32_t, NELEM> operator<(
     const uint32_t immediate,
     const accessible<uint32_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<uint32_t, NELEM>(immediate) < vtype<uint32_t, NELEM>(rhs);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int32_t, NELEM> operator<=(
    const accessible<uint32_t, NELEM, DEPTH_L> &lhs,
    const uint32_t immediate)
{
	return  vtype<uint32_t, NELEM>(lhs) <= vtype<uint32_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int32_t, NELEM> operator<=(
     const uint32_t immediate,
     const accessible<uint32_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<uint32_t, NELEM>(immediate) <= vtype<uint32_t, NELEM>(rhs);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int32_t, NELEM> operator==(
    const accessible<uint32_t, NELEM, DEPTH_L> &lhs,
    const uint32_t immediate)
{
	return  vtype<uint32_t, NELEM>(lhs) == vtype<uint32_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int32_t, NELEM> operator==(
     const uint32_t immediate,
     const accessible<uint32_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<uint32_t, NELEM>(immediate) == vtype<uint32_t, NELEM>(rhs);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int32_t, NELEM> operator!=(
    const accessible<uint32_t, NELEM, DEPTH_L> &lhs,
    const uint32_t immediate)
{
	return  vtype<uint32_t, NELEM>(lhs) != vtype<uint32_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int32_t, NELEM> operator!=(
     const uint32_t immediate,
     const accessible<uint32_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<uint32_t, NELEM>(immediate) != vtype<uint32_t, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// uint16_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int16_t, NELEM> operator>(
    const accessible<uint16_t, NELEM, DEPTH_L> &lhs,
    const accessible<uint16_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int16_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] > rhs.s[i] ? (int16_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int16_t, NELEM> operator>=(
    const accessible<uint16_t, NELEM, DEPTH_L> &lhs,
    const accessible<uint16_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int16_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] >= rhs.s[i] ? (int16_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int16_t, NELEM> operator<(
    const accessible<uint16_t, NELEM, DEPTH_L> &lhs,
    const accessible<uint16_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int16_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] < rhs.s[i] ? (int16_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int16_t, NELEM> operator<=(
    const accessible<uint16_t, NELEM, DEPTH_L> &lhs,
    const accessible<uint16_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int16_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] <= rhs.s[i] ? (int16_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int16_t, NELEM> operator==(
    const accessible<uint16_t, NELEM, DEPTH_L> &lhs,
    const accessible<uint16_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int16_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] == rhs.s[i] ? (int16_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int16_t, NELEM> operator!=(
    const accessible<uint16_t, NELEM, DEPTH_L> &lhs,
    const accessible<uint16_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int16_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] != rhs.s[i] ? (int16_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int16_t, NELEM> operator>(
    const accessible<uint16_t, NELEM, DEPTH_L> &lhs,
    const uint16_t immediate)
{
	return  vtype<uint16_t, NELEM>(lhs) > vtype<uint16_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int16_t, NELEM> operator>(
     const uint16_t immediate,
     const accessible<uint16_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<uint16_t, NELEM>(immediate) > vtype<uint16_t, NELEM>(rhs);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int16_t, NELEM> operator>=(
    const accessible<uint16_t, NELEM, DEPTH_L> &lhs,
    const uint16_t immediate)
{
	return  vtype<uint16_t, NELEM>(lhs) >= vtype<uint16_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int16_t, NELEM> operator>=(
     const uint16_t immediate,
     const accessible<uint16_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<uint16_t, NELEM>(immediate) >= vtype<uint16_t, NELEM>(rhs);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int16_t, NELEM> operator<(
    const accessible<uint16_t, NELEM, DEPTH_L> &lhs,
    const uint16_t immediate)
{
	return  vtype<uint16_t, NELEM>(lhs) < vtype<uint16_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int16_t, NELEM> operator<(
     const uint16_t immediate,
     const accessible<uint16_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<uint16_t, NELEM>(immediate) < vtype<uint16_t, NELEM>(rhs);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int16_t, NELEM> operator<=(
    const accessible<uint16_t, NELEM, DEPTH_L> &lhs,
    const uint16_t immediate)
{
	return  vtype<uint16_t, NELEM>(lhs) <= vtype<uint16_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int16_t, NELEM> operator<=(
     const uint16_t immediate,
     const accessible<uint16_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<uint16_t, NELEM>(immediate) <= vtype<uint16_t, NELEM>(rhs);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int16_t, NELEM> operator==(
    const accessible<uint16_t, NELEM, DEPTH_L> &lhs,
    const uint16_t immediate)
{
	return  vtype<uint16_t, NELEM>(lhs) == vtype<uint16_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int16_t, NELEM> operator==(
     const uint16_t immediate,
     const accessible<uint16_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<uint16_t, NELEM>(immediate) == vtype<uint16_t, NELEM>(rhs);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int16_t, NELEM> operator!=(
    const accessible<uint16_t, NELEM, DEPTH_L> &lhs,
    const uint16_t immediate)
{
	return  vtype<uint16_t, NELEM>(lhs) != vtype<uint16_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int16_t, NELEM> operator!=(
     const uint16_t immediate,
     const accessible<uint16_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<uint16_t, NELEM>(immediate) != vtype<uint16_t, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// uint8_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int8_t, NELEM> operator>(
    const accessible<uint8_t, NELEM, DEPTH_L> &lhs,
    const accessible<uint8_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int8_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] > rhs.s[i] ? (int8_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int8_t, NELEM> operator>=(
    const accessible<uint8_t, NELEM, DEPTH_L> &lhs,
    const accessible<uint8_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int8_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] >= rhs.s[i] ? (int8_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int8_t, NELEM> operator<(
    const accessible<uint8_t, NELEM, DEPTH_L> &lhs,
    const accessible<uint8_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int8_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] < rhs.s[i] ? (int8_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int8_t, NELEM> operator<=(
    const accessible<uint8_t, NELEM, DEPTH_L> &lhs,
    const accessible<uint8_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int8_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] <= rhs.s[i] ? (int8_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int8_t, NELEM> operator==(
    const accessible<uint8_t, NELEM, DEPTH_L> &lhs,
    const accessible<uint8_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int8_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] == rhs.s[i] ? (int8_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int8_t, NELEM> operator!=(
    const accessible<uint8_t, NELEM, DEPTH_L> &lhs,
    const accessible<uint8_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int8_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] != rhs.s[i] ? (int8_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int8_t, NELEM> operator>(
    const accessible<uint8_t, NELEM, DEPTH_L> &lhs,
    const uint8_t immediate)
{
	return  vtype<uint8_t, NELEM>(lhs) > vtype<uint8_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int8_t, NELEM> operator>(
     const uint8_t immediate,
     const accessible<uint8_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<uint8_t, NELEM>(immediate) > vtype<uint8_t, NELEM>(rhs);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int8_t, NELEM> operator>=(
    const accessible<uint8_t, NELEM, DEPTH_L> &lhs,
    const uint8_t immediate)
{
	return  vtype<uint8_t, NELEM>(lhs) >= vtype<uint8_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int8_t, NELEM> operator>=(
     const uint8_t immediate,
     const accessible<uint8_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<uint8_t, NELEM>(immediate) >= vtype<uint8_t, NELEM>(rhs);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int8_t, NELEM> operator<(
    const accessible<uint8_t, NELEM, DEPTH_L> &lhs,
    const uint8_t immediate)
{
	return  vtype<uint8_t, NELEM>(lhs) < vtype<uint8_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int8_t, NELEM> operator<(
     const uint8_t immediate,
     const accessible<uint8_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<uint8_t, NELEM>(immediate) < vtype<uint8_t, NELEM>(rhs);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int8_t, NELEM> operator<=(
    const accessible<uint8_t, NELEM, DEPTH_L> &lhs,
    const uint8_t immediate)
{
	return  vtype<uint8_t, NELEM>(lhs) <= vtype<uint8_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int8_t, NELEM> operator<=(
     const uint8_t immediate,
     const accessible<uint8_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<uint8_t, NELEM>(immediate) <= vtype<uint8_t, NELEM>(rhs);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int8_t, NELEM> operator==(
    const accessible<uint8_t, NELEM, DEPTH_L> &lhs,
    const uint8_t immediate)
{
	return  vtype<uint8_t, NELEM>(lhs) == vtype<uint8_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int8_t, NELEM> operator==(
     const uint8_t immediate,
     const accessible<uint8_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<uint8_t, NELEM>(immediate) == vtype<uint8_t, NELEM>(rhs);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int8_t, NELEM> operator!=(
    const accessible<uint8_t, NELEM, DEPTH_L> &lhs,
    const uint8_t immediate)
{
	return  vtype<uint8_t, NELEM>(lhs) != vtype<uint8_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int8_t, NELEM> operator!=(
     const uint8_t immediate,
     const accessible<uint8_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<uint8_t, NELEM>(immediate) != vtype<uint8_t, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// Operator& overloads
//-----------------------------------------------------------------------------
template <typename ELEM_T, size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<ELEM_T, NELEM> operator&(
    const accessible<ELEM_T, NELEM, DEPTH_L> &lhs,
    const accessible<ELEM_T, NELEM, DEPTH_R> &rhs
);
//-----------------------------------------------------------------------------
// int64_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int64_t, NELEM> operator&(
    const accessible<int64_t, NELEM, DEPTH_L> &lhs,
    const accessible<int64_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int64_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] & rhs.s[i];
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int64_t, NELEM> operator&(
    const accessible<int64_t, NELEM, DEPTH_L> &lhs,
    const int64_t immediate)
{
       return vtype<int64_t, NELEM>(lhs) & vtype<int64_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int64_t, NELEM> operator&(
     const int64_t immediate,
     const accessible<int64_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<int64_t, NELEM>(immediate) & vtype<int64_t, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// int32_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int32_t, NELEM> operator&(
    const accessible<int32_t, NELEM, DEPTH_L> &lhs,
    const accessible<int32_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int32_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] & rhs.s[i];
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int32_t, NELEM> operator&(
    const accessible<int32_t, NELEM, DEPTH_L> &lhs,
    const int32_t immediate)
{
       return vtype<int32_t, NELEM>(lhs) & vtype<int32_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int32_t, NELEM> operator&(
     const int32_t immediate,
     const accessible<int32_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<int32_t, NELEM>(immediate) & vtype<int32_t, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// int16_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int16_t, NELEM> operator&(
    const accessible<int16_t, NELEM, DEPTH_L> &lhs,
    const accessible<int16_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int16_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] & rhs.s[i];
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int16_t, NELEM> operator&(
    const accessible<int16_t, NELEM, DEPTH_L> &lhs,
    const int16_t immediate)
{
       return vtype<int16_t, NELEM>(lhs) & vtype<int16_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int16_t, NELEM> operator&(
     const int16_t immediate,
     const accessible<int16_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<int16_t, NELEM>(immediate) & vtype<int16_t, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// int8_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int8_t, NELEM> operator&(
    const accessible<int8_t, NELEM, DEPTH_L> &lhs,
    const accessible<int8_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int8_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] & rhs.s[i];
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int8_t, NELEM> operator&(
    const accessible<int8_t, NELEM, DEPTH_L> &lhs,
    const int8_t immediate)
{
       return vtype<int8_t, NELEM>(lhs) & vtype<int8_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int8_t, NELEM> operator&(
     const int8_t immediate,
     const accessible<int8_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<int8_t, NELEM>(immediate) & vtype<int8_t, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// uint64_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<uint64_t, NELEM> operator&(
    const accessible<uint64_t, NELEM, DEPTH_L> &lhs,
    const accessible<uint64_t, NELEM, DEPTH_R> &rhs)
{
    vtype<uint64_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] & rhs.s[i];
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<uint64_t, NELEM> operator&(
    const accessible<uint64_t, NELEM, DEPTH_L> &lhs,
    const uint64_t immediate)
{
       return vtype<uint64_t, NELEM>(lhs) & vtype<uint64_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<uint64_t, NELEM> operator&(
     const uint64_t immediate,
     const accessible<uint64_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<uint64_t, NELEM>(immediate) & vtype<uint64_t, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// uint32_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<uint32_t, NELEM> operator&(
    const accessible<uint32_t, NELEM, DEPTH_L> &lhs,
    const accessible<uint32_t, NELEM, DEPTH_R> &rhs)
{
    vtype<uint32_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] & rhs.s[i];
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<uint32_t, NELEM> operator&(
    const accessible<uint32_t, NELEM, DEPTH_L> &lhs,
    const uint32_t immediate)
{
       return vtype<uint32_t, NELEM>(lhs) & vtype<uint32_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<uint32_t, NELEM> operator&(
     const uint32_t immediate,
     const accessible<uint32_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<uint32_t, NELEM>(immediate) & vtype<uint32_t, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// uint16_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<uint16_t, NELEM> operator&(
    const accessible<uint16_t, NELEM, DEPTH_L> &lhs,
    const accessible<uint16_t, NELEM, DEPTH_R> &rhs)
{
    vtype<uint16_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] & rhs.s[i];
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<uint16_t, NELEM> operator&(
    const accessible<uint16_t, NELEM, DEPTH_L> &lhs,
    const uint16_t immediate)
{
       return vtype<uint16_t, NELEM>(lhs) & vtype<uint16_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<uint16_t, NELEM> operator&(
     const uint16_t immediate,
     const accessible<uint16_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<uint16_t, NELEM>(immediate) & vtype<uint16_t, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// uint8_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<uint8_t, NELEM> operator&(
    const accessible<uint8_t, NELEM, DEPTH_L> &lhs,
    const accessible<uint8_t, NELEM, DEPTH_R> &rhs)
{
    vtype<uint8_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] & rhs.s[i];
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<uint8_t, NELEM> operator&(
    const accessible<uint8_t, NELEM, DEPTH_L> &lhs,
    const uint8_t immediate)
{
       return vtype<uint8_t, NELEM>(lhs) & vtype<uint8_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<uint8_t, NELEM> operator&(
     const uint8_t immediate,
     const accessible<uint8_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<uint8_t, NELEM>(immediate) & vtype<uint8_t, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// Operator| overloads
//-----------------------------------------------------------------------------
template <typename ELEM_T, size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<ELEM_T, NELEM> operator|(
    const accessible<ELEM_T, NELEM, DEPTH_L> &lhs,
    const accessible<ELEM_T, NELEM, DEPTH_R> &rhs
);
//-----------------------------------------------------------------------------
// int64_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int64_t, NELEM> operator|(
    const accessible<int64_t, NELEM, DEPTH_L> &lhs,
    const accessible<int64_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int64_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] | rhs.s[i];
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int64_t, NELEM> operator|(
    const accessible<int64_t, NELEM, DEPTH_L> &lhs,
    const int64_t immediate)
{
       return vtype<int64_t, NELEM>(lhs) | vtype<int64_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int64_t, NELEM> operator|(
     const int64_t immediate,
     const accessible<int64_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<int64_t, NELEM>(immediate) | vtype<int64_t, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// int32_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int32_t, NELEM> operator|(
    const accessible<int32_t, NELEM, DEPTH_L> &lhs,
    const accessible<int32_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int32_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] | rhs.s[i];
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int32_t, NELEM> operator|(
    const accessible<int32_t, NELEM, DEPTH_L> &lhs,
    const int32_t immediate)
{
       return vtype<int32_t, NELEM>(lhs) | vtype<int32_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int32_t, NELEM> operator|(
     const int32_t immediate,
     const accessible<int32_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<int32_t, NELEM>(immediate) | vtype<int32_t, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// int16_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int16_t, NELEM> operator|(
    const accessible<int16_t, NELEM, DEPTH_L> &lhs,
    const accessible<int16_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int16_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] | rhs.s[i];
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int16_t, NELEM> operator|(
    const accessible<int16_t, NELEM, DEPTH_L> &lhs,
    const int16_t immediate)
{
       return vtype<int16_t, NELEM>(lhs) | vtype<int16_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int16_t, NELEM> operator|(
     const int16_t immediate,
     const accessible<int16_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<int16_t, NELEM>(immediate) | vtype<int16_t, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// int8_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int8_t, NELEM> operator|(
    const accessible<int8_t, NELEM, DEPTH_L> &lhs,
    const accessible<int8_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int8_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] | rhs.s[i];
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int8_t, NELEM> operator|(
    const accessible<int8_t, NELEM, DEPTH_L> &lhs,
    const int8_t immediate)
{
       return vtype<int8_t, NELEM>(lhs) | vtype<int8_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int8_t, NELEM> operator|(
     const int8_t immediate,
     const accessible<int8_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<int8_t, NELEM>(immediate) | vtype<int8_t, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// uint64_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<uint64_t, NELEM> operator|(
    const accessible<uint64_t, NELEM, DEPTH_L> &lhs,
    const accessible<uint64_t, NELEM, DEPTH_R> &rhs)
{
    vtype<uint64_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] | rhs.s[i];
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<uint64_t, NELEM> operator|(
    const accessible<uint64_t, NELEM, DEPTH_L> &lhs,
    const uint64_t immediate)
{
       return vtype<uint64_t, NELEM>(lhs) | vtype<uint64_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<uint64_t, NELEM> operator|(
     const uint64_t immediate,
     const accessible<uint64_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<uint64_t, NELEM>(immediate) | vtype<uint64_t, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// uint32_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<uint32_t, NELEM> operator|(
    const accessible<uint32_t, NELEM, DEPTH_L> &lhs,
    const accessible<uint32_t, NELEM, DEPTH_R> &rhs)
{
    vtype<uint32_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] | rhs.s[i];
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<uint32_t, NELEM> operator|(
    const accessible<uint32_t, NELEM, DEPTH_L> &lhs,
    const uint32_t immediate)
{
       return vtype<uint32_t, NELEM>(lhs) | vtype<uint32_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<uint32_t, NELEM> operator|(
     const uint32_t immediate,
     const accessible<uint32_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<uint32_t, NELEM>(immediate) | vtype<uint32_t, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// uint16_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<uint16_t, NELEM> operator|(
    const accessible<uint16_t, NELEM, DEPTH_L> &lhs,
    const accessible<uint16_t, NELEM, DEPTH_R> &rhs)
{
    vtype<uint16_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] | rhs.s[i];
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<uint16_t, NELEM> operator|(
    const accessible<uint16_t, NELEM, DEPTH_L> &lhs,
    const uint16_t immediate)
{
       return vtype<uint16_t, NELEM>(lhs) | vtype<uint16_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<uint16_t, NELEM> operator|(
     const uint16_t immediate,
     const accessible<uint16_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<uint16_t, NELEM>(immediate) | vtype<uint16_t, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// uint8_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<uint8_t, NELEM> operator|(
    const accessible<uint8_t, NELEM, DEPTH_L> &lhs,
    const accessible<uint8_t, NELEM, DEPTH_R> &rhs)
{
    vtype<uint8_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] | rhs.s[i];
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<uint8_t, NELEM> operator|(
    const accessible<uint8_t, NELEM, DEPTH_L> &lhs,
    const uint8_t immediate)
{
       return vtype<uint8_t, NELEM>(lhs) | vtype<uint8_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<uint8_t, NELEM> operator|(
     const uint8_t immediate,
     const accessible<uint8_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<uint8_t, NELEM>(immediate) | vtype<uint8_t, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// Operator^ overloads
//-----------------------------------------------------------------------------
template <typename ELEM_T, size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<ELEM_T, NELEM> operator^(
    const accessible<ELEM_T, NELEM, DEPTH_L> &lhs,
    const accessible<ELEM_T, NELEM, DEPTH_R> &rhs
);
//-----------------------------------------------------------------------------
// int64_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int64_t, NELEM> operator^(
    const accessible<int64_t, NELEM, DEPTH_L> &lhs,
    const accessible<int64_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int64_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] ^ rhs.s[i];
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int64_t, NELEM> operator^(
    const accessible<int64_t, NELEM, DEPTH_L> &lhs,
    const int64_t immediate)
{
       return vtype<int64_t, NELEM>(lhs) ^ vtype<int64_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int64_t, NELEM> operator^(
     const int64_t immediate,
     const accessible<int64_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<int64_t, NELEM>(immediate) ^ vtype<int64_t, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// int32_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int32_t, NELEM> operator^(
    const accessible<int32_t, NELEM, DEPTH_L> &lhs,
    const accessible<int32_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int32_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] ^ rhs.s[i];
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int32_t, NELEM> operator^(
    const accessible<int32_t, NELEM, DEPTH_L> &lhs,
    const int32_t immediate)
{
       return vtype<int32_t, NELEM>(lhs) ^ vtype<int32_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int32_t, NELEM> operator^(
     const int32_t immediate,
     const accessible<int32_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<int32_t, NELEM>(immediate) ^ vtype<int32_t, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// int16_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int16_t, NELEM> operator^(
    const accessible<int16_t, NELEM, DEPTH_L> &lhs,
    const accessible<int16_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int16_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] ^ rhs.s[i];
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int16_t, NELEM> operator^(
    const accessible<int16_t, NELEM, DEPTH_L> &lhs,
    const int16_t immediate)
{
       return vtype<int16_t, NELEM>(lhs) ^ vtype<int16_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int16_t, NELEM> operator^(
     const int16_t immediate,
     const accessible<int16_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<int16_t, NELEM>(immediate) ^ vtype<int16_t, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// int8_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int8_t, NELEM> operator^(
    const accessible<int8_t, NELEM, DEPTH_L> &lhs,
    const accessible<int8_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int8_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] ^ rhs.s[i];
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int8_t, NELEM> operator^(
    const accessible<int8_t, NELEM, DEPTH_L> &lhs,
    const int8_t immediate)
{
       return vtype<int8_t, NELEM>(lhs) ^ vtype<int8_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int8_t, NELEM> operator^(
     const int8_t immediate,
     const accessible<int8_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<int8_t, NELEM>(immediate) ^ vtype<int8_t, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// uint64_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<uint64_t, NELEM> operator^(
    const accessible<uint64_t, NELEM, DEPTH_L> &lhs,
    const accessible<uint64_t, NELEM, DEPTH_R> &rhs)
{
    vtype<uint64_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] ^ rhs.s[i];
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<uint64_t, NELEM> operator^(
    const accessible<uint64_t, NELEM, DEPTH_L> &lhs,
    const uint64_t immediate)
{
       return vtype<uint64_t, NELEM>(lhs) ^ vtype<uint64_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<uint64_t, NELEM> operator^(
     const uint64_t immediate,
     const accessible<uint64_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<uint64_t, NELEM>(immediate) ^ vtype<uint64_t, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// uint32_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<uint32_t, NELEM> operator^(
    const accessible<uint32_t, NELEM, DEPTH_L> &lhs,
    const accessible<uint32_t, NELEM, DEPTH_R> &rhs)
{
    vtype<uint32_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] ^ rhs.s[i];
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<uint32_t, NELEM> operator^(
    const accessible<uint32_t, NELEM, DEPTH_L> &lhs,
    const uint32_t immediate)
{
       return vtype<uint32_t, NELEM>(lhs) ^ vtype<uint32_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<uint32_t, NELEM> operator^(
     const uint32_t immediate,
     const accessible<uint32_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<uint32_t, NELEM>(immediate) ^ vtype<uint32_t, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// uint16_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<uint16_t, NELEM> operator^(
    const accessible<uint16_t, NELEM, DEPTH_L> &lhs,
    const accessible<uint16_t, NELEM, DEPTH_R> &rhs)
{
    vtype<uint16_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] ^ rhs.s[i];
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<uint16_t, NELEM> operator^(
    const accessible<uint16_t, NELEM, DEPTH_L> &lhs,
    const uint16_t immediate)
{
       return vtype<uint16_t, NELEM>(lhs) ^ vtype<uint16_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<uint16_t, NELEM> operator^(
     const uint16_t immediate,
     const accessible<uint16_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<uint16_t, NELEM>(immediate) ^ vtype<uint16_t, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// uint8_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<uint8_t, NELEM> operator^(
    const accessible<uint8_t, NELEM, DEPTH_L> &lhs,
    const accessible<uint8_t, NELEM, DEPTH_R> &rhs)
{
    vtype<uint8_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] ^ rhs.s[i];
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<uint8_t, NELEM> operator^(
    const accessible<uint8_t, NELEM, DEPTH_L> &lhs,
    const uint8_t immediate)
{
       return vtype<uint8_t, NELEM>(lhs) ^ vtype<uint8_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<uint8_t, NELEM> operator^(
     const uint8_t immediate,
     const accessible<uint8_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<uint8_t, NELEM>(immediate) ^ vtype<uint8_t, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// Logical AND/OR &&/|| Operator overloads
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// int64_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int64_t, NELEM> operator&&(
    const accessible<int64_t, NELEM, DEPTH_L> &lhs,
    const accessible<int64_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int64_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] && rhs.s[i] ? (int64_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int64_t, NELEM> operator||(
    const accessible<int64_t, NELEM, DEPTH_L> &lhs,
    const accessible<int64_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int64_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] || rhs.s[i] ? (int64_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int64_t, NELEM> operator&&(
    const accessible<int64_t, NELEM, DEPTH_L> &lhs,
    const int64_t immediate)
{
	return  vtype<int64_t, NELEM>(lhs) && vtype<int64_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int64_t, NELEM> operator&&(
     const int64_t immediate,
     const accessible<int64_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<int64_t, NELEM>(immediate) && vtype<int64_t, NELEM>(rhs);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int64_t, NELEM> operator||(
    const accessible<int64_t, NELEM, DEPTH_L> &lhs,
    const int64_t immediate)
{
	return  vtype<int64_t, NELEM>(lhs) || vtype<int64_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int64_t, NELEM> operator||(
     const int64_t immediate,
     const accessible<int64_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<int64_t, NELEM>(immediate) || vtype<int64_t, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// double
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int64_t, NELEM> operator&&(
    const accessible<double, NELEM, DEPTH_L> &lhs,
    const accessible<double, NELEM, DEPTH_R> &rhs)
{
    vtype<int64_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] && rhs.s[i] ? (int64_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int64_t, NELEM> operator||(
    const accessible<double, NELEM, DEPTH_L> &lhs,
    const accessible<double, NELEM, DEPTH_R> &rhs)
{
    vtype<int64_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] || rhs.s[i] ? (int64_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int64_t, NELEM> operator&&(
    const accessible<double, NELEM, DEPTH_L> &lhs,
    const double immediate)
{
	return  vtype<double, NELEM>(lhs) && vtype<double, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int64_t, NELEM> operator&&(
     const double immediate,
     const accessible<double, NELEM, DEPTH_R> &rhs)
{
    return vtype<double, NELEM>(immediate) && vtype<double, NELEM>(rhs);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int64_t, NELEM> operator||(
    const accessible<double, NELEM, DEPTH_L> &lhs,
    const double immediate)
{
	return  vtype<double, NELEM>(lhs) || vtype<double, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int64_t, NELEM> operator||(
     const double immediate,
     const accessible<double, NELEM, DEPTH_R> &rhs)
{
    return vtype<double, NELEM>(immediate) || vtype<double, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// int32_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int32_t, NELEM> operator&&(
    const accessible<int32_t, NELEM, DEPTH_L> &lhs,
    const accessible<int32_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int32_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] && rhs.s[i] ? (int32_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int32_t, NELEM> operator||(
    const accessible<int32_t, NELEM, DEPTH_L> &lhs,
    const accessible<int32_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int32_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] || rhs.s[i] ? (int32_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int32_t, NELEM> operator&&(
    const accessible<int32_t, NELEM, DEPTH_L> &lhs,
    const int32_t immediate)
{
	return  vtype<int32_t, NELEM>(lhs) && vtype<int32_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int32_t, NELEM> operator&&(
     const int32_t immediate,
     const accessible<int32_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<int32_t, NELEM>(immediate) && vtype<int32_t, NELEM>(rhs);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int32_t, NELEM> operator||(
    const accessible<int32_t, NELEM, DEPTH_L> &lhs,
    const int32_t immediate)
{
	return  vtype<int32_t, NELEM>(lhs) || vtype<int32_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int32_t, NELEM> operator||(
     const int32_t immediate,
     const accessible<int32_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<int32_t, NELEM>(immediate) || vtype<int32_t, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// float
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int32_t, NELEM> operator&&(
    const accessible<float, NELEM, DEPTH_L> &lhs,
    const accessible<float, NELEM, DEPTH_R> &rhs)
{
    vtype<int32_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] && rhs.s[i] ? (int32_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int32_t, NELEM> operator||(
    const accessible<float, NELEM, DEPTH_L> &lhs,
    const accessible<float, NELEM, DEPTH_R> &rhs)
{
    vtype<int32_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] || rhs.s[i] ? (int32_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int32_t, NELEM> operator&&(
    const accessible<float, NELEM, DEPTH_L> &lhs,
    const float immediate)
{
	return  vtype<float, NELEM>(lhs) && vtype<float, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int32_t, NELEM> operator&&(
     const float immediate,
     const accessible<float, NELEM, DEPTH_R> &rhs)
{
    return vtype<float, NELEM>(immediate) && vtype<float, NELEM>(rhs);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int32_t, NELEM> operator||(
    const accessible<float, NELEM, DEPTH_L> &lhs,
    const float immediate)
{
	return  vtype<float, NELEM>(lhs) || vtype<float, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int32_t, NELEM> operator||(
     const float immediate,
     const accessible<float, NELEM, DEPTH_R> &rhs)
{
    return vtype<float, NELEM>(immediate) || vtype<float, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// int16_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int16_t, NELEM> operator&&(
    const accessible<int16_t, NELEM, DEPTH_L> &lhs,
    const accessible<int16_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int16_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] && rhs.s[i] ? (int16_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int16_t, NELEM> operator||(
    const accessible<int16_t, NELEM, DEPTH_L> &lhs,
    const accessible<int16_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int16_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] || rhs.s[i] ? (int16_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int16_t, NELEM> operator&&(
    const accessible<int16_t, NELEM, DEPTH_L> &lhs,
    const int16_t immediate)
{
	return  vtype<int16_t, NELEM>(lhs) && vtype<int16_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int16_t, NELEM> operator&&(
     const int16_t immediate,
     const accessible<int16_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<int16_t, NELEM>(immediate) && vtype<int16_t, NELEM>(rhs);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int16_t, NELEM> operator||(
    const accessible<int16_t, NELEM, DEPTH_L> &lhs,
    const int16_t immediate)
{
	return  vtype<int16_t, NELEM>(lhs) || vtype<int16_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int16_t, NELEM> operator||(
     const int16_t immediate,
     const accessible<int16_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<int16_t, NELEM>(immediate) || vtype<int16_t, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// int8_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int8_t, NELEM> operator&&(
    const accessible<int8_t, NELEM, DEPTH_L> &lhs,
    const accessible<int8_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int8_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] && rhs.s[i] ? (int8_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int8_t, NELEM> operator||(
    const accessible<int8_t, NELEM, DEPTH_L> &lhs,
    const accessible<int8_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int8_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] || rhs.s[i] ? (int8_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int8_t, NELEM> operator&&(
    const accessible<int8_t, NELEM, DEPTH_L> &lhs,
    const int8_t immediate)
{
	return  vtype<int8_t, NELEM>(lhs) && vtype<int8_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int8_t, NELEM> operator&&(
     const int8_t immediate,
     const accessible<int8_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<int8_t, NELEM>(immediate) && vtype<int8_t, NELEM>(rhs);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int8_t, NELEM> operator||(
    const accessible<int8_t, NELEM, DEPTH_L> &lhs,
    const int8_t immediate)
{
	return  vtype<int8_t, NELEM>(lhs) || vtype<int8_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int8_t, NELEM> operator||(
     const int8_t immediate,
     const accessible<int8_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<int8_t, NELEM>(immediate) || vtype<int8_t, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// uint64_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int64_t, NELEM> operator&&(
    const accessible<uint64_t, NELEM, DEPTH_L> &lhs,
    const accessible<uint64_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int64_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] && rhs.s[i] ? (int64_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int64_t, NELEM> operator||(
    const accessible<uint64_t, NELEM, DEPTH_L> &lhs,
    const accessible<uint64_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int64_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] || rhs.s[i] ? (int64_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int64_t, NELEM> operator&&(
    const accessible<uint64_t, NELEM, DEPTH_L> &lhs,
    const uint64_t immediate)
{
	return  vtype<uint64_t, NELEM>(lhs) && vtype<uint64_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int64_t, NELEM> operator&&(
     const uint64_t immediate,
     const accessible<uint64_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<uint64_t, NELEM>(immediate) && vtype<uint64_t, NELEM>(rhs);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int64_t, NELEM> operator||(
    const accessible<uint64_t, NELEM, DEPTH_L> &lhs,
    const uint64_t immediate)
{
	return  vtype<uint64_t, NELEM>(lhs) || vtype<uint64_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int64_t, NELEM> operator||(
     const uint64_t immediate,
     const accessible<uint64_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<uint64_t, NELEM>(immediate) || vtype<uint64_t, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// uint32_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int32_t, NELEM> operator&&(
    const accessible<uint32_t, NELEM, DEPTH_L> &lhs,
    const accessible<uint32_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int32_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] && rhs.s[i] ? (int32_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int32_t, NELEM> operator||(
    const accessible<uint32_t, NELEM, DEPTH_L> &lhs,
    const accessible<uint32_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int32_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] || rhs.s[i] ? (int32_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int32_t, NELEM> operator&&(
    const accessible<uint32_t, NELEM, DEPTH_L> &lhs,
    const uint32_t immediate)
{
	return  vtype<uint32_t, NELEM>(lhs) && vtype<uint32_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int32_t, NELEM> operator&&(
     const uint32_t immediate,
     const accessible<uint32_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<uint32_t, NELEM>(immediate) && vtype<uint32_t, NELEM>(rhs);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int32_t, NELEM> operator||(
    const accessible<uint32_t, NELEM, DEPTH_L> &lhs,
    const uint32_t immediate)
{
	return  vtype<uint32_t, NELEM>(lhs) || vtype<uint32_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int32_t, NELEM> operator||(
     const uint32_t immediate,
     const accessible<uint32_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<uint32_t, NELEM>(immediate) || vtype<uint32_t, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// uint16_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int16_t, NELEM> operator&&(
    const accessible<uint16_t, NELEM, DEPTH_L> &lhs,
    const accessible<uint16_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int16_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] && rhs.s[i] ? (int16_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int16_t, NELEM> operator||(
    const accessible<uint16_t, NELEM, DEPTH_L> &lhs,
    const accessible<uint16_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int16_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] || rhs.s[i] ? (int16_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int16_t, NELEM> operator&&(
    const accessible<uint16_t, NELEM, DEPTH_L> &lhs,
    const uint16_t immediate)
{
	return  vtype<uint16_t, NELEM>(lhs) && vtype<uint16_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int16_t, NELEM> operator&&(
     const uint16_t immediate,
     const accessible<uint16_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<uint16_t, NELEM>(immediate) && vtype<uint16_t, NELEM>(rhs);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int16_t, NELEM> operator||(
    const accessible<uint16_t, NELEM, DEPTH_L> &lhs,
    const uint16_t immediate)
{
	return  vtype<uint16_t, NELEM>(lhs) || vtype<uint16_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int16_t, NELEM> operator||(
     const uint16_t immediate,
     const accessible<uint16_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<uint16_t, NELEM>(immediate) || vtype<uint16_t, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// uint8_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int8_t, NELEM> operator&&(
    const accessible<uint8_t, NELEM, DEPTH_L> &lhs,
    const accessible<uint8_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int8_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] && rhs.s[i] ? (int8_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int8_t, NELEM> operator||(
    const accessible<uint8_t, NELEM, DEPTH_L> &lhs,
    const accessible<uint8_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int8_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] || rhs.s[i] ? (int8_t)-1 : 0;
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int8_t, NELEM> operator&&(
    const accessible<uint8_t, NELEM, DEPTH_L> &lhs,
    const uint8_t immediate)
{
	return  vtype<uint8_t, NELEM>(lhs) && vtype<uint8_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int8_t, NELEM> operator&&(
     const uint8_t immediate,
     const accessible<uint8_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<uint8_t, NELEM>(immediate) && vtype<uint8_t, NELEM>(rhs);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int8_t, NELEM> operator||(
    const accessible<uint8_t, NELEM, DEPTH_L> &lhs,
    const uint8_t immediate)
{
	return  vtype<uint8_t, NELEM>(lhs) || vtype<uint8_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int8_t, NELEM> operator||(
     const uint8_t immediate,
     const accessible<uint8_t, NELEM, DEPTH_R> &rhs)
{
    return vtype<uint8_t, NELEM>(immediate) || vtype<uint8_t, NELEM>(rhs);
}
//-----------------------------------------------------------------------------
// Logical Not ! Operator overloads
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// int64_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int64_t, NELEM> operator!(
    const accessible<int64_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int64_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = !rhs.s[i] ? (int64_t)-1 : 0;
	return res;
}
//-----------------------------------------------------------------------------
// double
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int64_t, NELEM> operator!(
    const accessible<double, NELEM, DEPTH_R> &rhs)
{
    vtype<int64_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = !rhs.s[i] ? (int64_t)-1 : 0;
	return res;
}
//-----------------------------------------------------------------------------
// int32_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int32_t, NELEM> operator!(
    const accessible<int32_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int32_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = !rhs.s[i] ? (int32_t)-1 : 0;
	return res;
}
//-----------------------------------------------------------------------------
// float
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int32_t, NELEM> operator!(
    const accessible<float, NELEM, DEPTH_R> &rhs)
{
    vtype<int32_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = !rhs.s[i] ? (int32_t)-1 : 0;
	return res;
}
//-----------------------------------------------------------------------------
// int16_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int16_t, NELEM> operator!(
    const accessible<int16_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int16_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = !rhs.s[i] ? (int16_t)-1 : 0;
	return res;
}
//-----------------------------------------------------------------------------
// int8_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int8_t, NELEM> operator!(
    const accessible<int8_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int8_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = !rhs.s[i] ? (int8_t)-1 : 0;
	return res;
}
//-----------------------------------------------------------------------------
// uint64_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int64_t, NELEM> operator!(
    const accessible<uint64_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int64_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = !rhs.s[i] ? (int64_t)-1 : 0;
	return res;
}
//-----------------------------------------------------------------------------
// uint32_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int32_t, NELEM> operator!(
    const accessible<uint32_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int32_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = !rhs.s[i] ? (int32_t)-1 : 0;
	return res;
}
//-----------------------------------------------------------------------------
// uint16_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int16_t, NELEM> operator!(
    const accessible<uint16_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int16_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = !rhs.s[i] ? (int16_t)-1 : 0;
	return res;
}
//-----------------------------------------------------------------------------
// uint8_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_R>
vtype<int8_t, NELEM> operator!(
    const accessible<uint8_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int8_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = !rhs.s[i] ? (int8_t)-1 : 0;
	return res;
}
//-----------------------------------------------------------------------------
// Operator <</>> overloads
//-----------------------------------------------------------------------------
template <typename ELEM_T, size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<ELEM_T, NELEM> operator>>(
    const accessible<ELEM_T, NELEM, DEPTH_L> &lhs,
    const accessible<ELEM_T, NELEM, DEPTH_R> &rhs
);
template <typename ELEM_T, size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<ELEM_T, NELEM> operator<<(
    const accessible<ELEM_T, NELEM, DEPTH_L> &lhs,
    const accessible<ELEM_T, NELEM, DEPTH_R> &rhs
);
//-----------------------------------------------------------------------------
// int64_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int64_t, NELEM> operator>>(
    const accessible<int64_t, NELEM, DEPTH_L> &lhs,
    const accessible<int64_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int64_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] >> rhs.s[i];
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int64_t, NELEM> operator<<(
    const accessible<int64_t, NELEM, DEPTH_L> &lhs,
    const accessible<int64_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int64_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] << rhs.s[i];
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int64_t, NELEM> operator>>(
    const accessible<int64_t, NELEM, DEPTH_L> &lhs,
    const int64_t immediate)
{
       return vtype<int64_t, NELEM>(lhs) >> vtype<int64_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int64_t, NELEM> operator<<(
    const accessible<int64_t, NELEM, DEPTH_L> &lhs,
    const int64_t immediate)
{
       return vtype<int64_t, NELEM>(lhs) << vtype<int64_t, NELEM>(immediate);
}
//-----------------------------------------------------------------------------
// int32_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int32_t, NELEM> operator>>(
    const accessible<int32_t, NELEM, DEPTH_L> &lhs,
    const accessible<int32_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int32_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] >> rhs.s[i];
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int32_t, NELEM> operator<<(
    const accessible<int32_t, NELEM, DEPTH_L> &lhs,
    const accessible<int32_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int32_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] << rhs.s[i];
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int32_t, NELEM> operator>>(
    const accessible<int32_t, NELEM, DEPTH_L> &lhs,
    const int32_t immediate)
{
       return vtype<int32_t, NELEM>(lhs) >> vtype<int32_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int32_t, NELEM> operator<<(
    const accessible<int32_t, NELEM, DEPTH_L> &lhs,
    const int32_t immediate)
{
       return vtype<int32_t, NELEM>(lhs) << vtype<int32_t, NELEM>(immediate);
}
//-----------------------------------------------------------------------------
// int16_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int16_t, NELEM> operator>>(
    const accessible<int16_t, NELEM, DEPTH_L> &lhs,
    const accessible<int16_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int16_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] >> rhs.s[i];
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int16_t, NELEM> operator<<(
    const accessible<int16_t, NELEM, DEPTH_L> &lhs,
    const accessible<int16_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int16_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] << rhs.s[i];
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int16_t, NELEM> operator>>(
    const accessible<int16_t, NELEM, DEPTH_L> &lhs,
    const int16_t immediate)
{
       return vtype<int16_t, NELEM>(lhs) >> vtype<int16_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int16_t, NELEM> operator<<(
    const accessible<int16_t, NELEM, DEPTH_L> &lhs,
    const int16_t immediate)
{
       return vtype<int16_t, NELEM>(lhs) << vtype<int16_t, NELEM>(immediate);
}
//-----------------------------------------------------------------------------
// int8_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int8_t, NELEM> operator>>(
    const accessible<int8_t, NELEM, DEPTH_L> &lhs,
    const accessible<int8_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int8_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] >> rhs.s[i];
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<int8_t, NELEM> operator<<(
    const accessible<int8_t, NELEM, DEPTH_L> &lhs,
    const accessible<int8_t, NELEM, DEPTH_R> &rhs)
{
    vtype<int8_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] << rhs.s[i];
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int8_t, NELEM> operator>>(
    const accessible<int8_t, NELEM, DEPTH_L> &lhs,
    const int8_t immediate)
{
       return vtype<int8_t, NELEM>(lhs) >> vtype<int8_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<int8_t, NELEM> operator<<(
    const accessible<int8_t, NELEM, DEPTH_L> &lhs,
    const int8_t immediate)
{
       return vtype<int8_t, NELEM>(lhs) << vtype<int8_t, NELEM>(immediate);
}
//-----------------------------------------------------------------------------
// uint64_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<uint64_t, NELEM> operator>>(
    const accessible<uint64_t, NELEM, DEPTH_L> &lhs,
    const accessible<uint64_t, NELEM, DEPTH_R> &rhs)
{
    vtype<uint64_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] >> rhs.s[i];
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<uint64_t, NELEM> operator<<(
    const accessible<uint64_t, NELEM, DEPTH_L> &lhs,
    const accessible<uint64_t, NELEM, DEPTH_R> &rhs)
{
    vtype<uint64_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] << rhs.s[i];
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<uint64_t, NELEM> operator>>(
    const accessible<uint64_t, NELEM, DEPTH_L> &lhs,
    const uint64_t immediate)
{
       return vtype<uint64_t, NELEM>(lhs) >> vtype<uint64_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<uint64_t, NELEM> operator<<(
    const accessible<uint64_t, NELEM, DEPTH_L> &lhs,
    const uint64_t immediate)
{
       return vtype<uint64_t, NELEM>(lhs) << vtype<uint64_t, NELEM>(immediate);
}
//-----------------------------------------------------------------------------
// uint32_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<uint32_t, NELEM> operator>>(
    const accessible<uint32_t, NELEM, DEPTH_L> &lhs,
    const accessible<uint32_t, NELEM, DEPTH_R> &rhs)
{
    vtype<uint32_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] >> rhs.s[i];
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<uint32_t, NELEM> operator<<(
    const accessible<uint32_t, NELEM, DEPTH_L> &lhs,
    const accessible<uint32_t, NELEM, DEPTH_R> &rhs)
{
    vtype<uint32_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] << rhs.s[i];
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<uint32_t, NELEM> operator>>(
    const accessible<uint32_t, NELEM, DEPTH_L> &lhs,
    const uint32_t immediate)
{
       return vtype<uint32_t, NELEM>(lhs) >> vtype<uint32_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<uint32_t, NELEM> operator<<(
    const accessible<uint32_t, NELEM, DEPTH_L> &lhs,
    const uint32_t immediate)
{
       return vtype<uint32_t, NELEM>(lhs) << vtype<uint32_t, NELEM>(immediate);
}
//-----------------------------------------------------------------------------
// uint16_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<uint16_t, NELEM> operator>>(
    const accessible<uint16_t, NELEM, DEPTH_L> &lhs,
    const accessible<uint16_t, NELEM, DEPTH_R> &rhs)
{
    vtype<uint16_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] >> rhs.s[i];
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<uint16_t, NELEM> operator<<(
    const accessible<uint16_t, NELEM, DEPTH_L> &lhs,
    const accessible<uint16_t, NELEM, DEPTH_R> &rhs)
{
    vtype<uint16_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] << rhs.s[i];
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<uint16_t, NELEM> operator>>(
    const accessible<uint16_t, NELEM, DEPTH_L> &lhs,
    const uint16_t immediate)
{
       return vtype<uint16_t, NELEM>(lhs) >> vtype<uint16_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<uint16_t, NELEM> operator<<(
    const accessible<uint16_t, NELEM, DEPTH_L> &lhs,
    const uint16_t immediate)
{
       return vtype<uint16_t, NELEM>(lhs) << vtype<uint16_t, NELEM>(immediate);
}
//-----------------------------------------------------------------------------
// uint8_t
//-----------------------------------------------------------------------------
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<uint8_t, NELEM> operator>>(
    const accessible<uint8_t, NELEM, DEPTH_L> &lhs,
    const accessible<uint8_t, NELEM, DEPTH_R> &rhs)
{
    vtype<uint8_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] >> rhs.s[i];
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L,
          size_t DEPTH_R>
vtype<uint8_t, NELEM> operator<<(
    const accessible<uint8_t, NELEM, DEPTH_L> &lhs,
    const accessible<uint8_t, NELEM, DEPTH_R> &rhs)
{
    vtype<uint8_t, NELEM> res;
    for (size_t i = 0; i < NELEM; i++)
		res.s[i] = lhs.s[i] << rhs.s[i];
	return res;
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<uint8_t, NELEM> operator>>(
    const accessible<uint8_t, NELEM, DEPTH_L> &lhs,
    const uint8_t immediate)
{
       return vtype<uint8_t, NELEM>(lhs) >> vtype<uint8_t, NELEM>(immediate);
}
template <size_t NELEM,
          size_t DEPTH_L>
vtype<uint8_t, NELEM> operator<<(
    const accessible<uint8_t, NELEM, DEPTH_L> &lhs,
    const uint8_t immediate)
{
       return vtype<uint8_t, NELEM>(lhs) << vtype<uint8_t, NELEM>(immediate);
}

} /* namespace _c70_he_detail */

/******************************************************************************
* Definition of vector types in the global namespace.
******************************************************************************/
typedef uint8_t  __uchar;
typedef uint16_t __ushort;
typedef uint32_t __uint;
typedef uint64_t __ulong;

typedef _c70_he_detail::__vpred vpred;
using _c70_he_detail::__vpred;

using __bool2  = _c70_he_detail::bvtype<2>;
using __bool4  = _c70_he_detail::bvtype<4>;
using __bool8  = _c70_he_detail::bvtype<8>;
using __bool16 = _c70_he_detail::bvtype<16>;
using __bool32 = _c70_he_detail::bvtype<32>;
using __bool64 = _c70_he_detail::bvtype<64>;

using __char2  = _c70_he_detail::vtype<int8_t, 2>;
using __char4  = _c70_he_detail::vtype<int8_t, 4>;
using __char8  = _c70_he_detail::vtype<int8_t, 8>;
using __char16 = _c70_he_detail::vtype<int8_t, 16>;
using __char32 = _c70_he_detail::vtype<int8_t, 32>;
using __char64 = _c70_he_detail::vtype<int8_t, 64>;

using __uchar2  = _c70_he_detail::vtype<uint8_t, 2>;
using __uchar4  = _c70_he_detail::vtype<uint8_t, 4>;
using __uchar8  = _c70_he_detail::vtype<uint8_t, 8>;
using __uchar16 = _c70_he_detail::vtype<uint8_t, 16>;
using __uchar32 = _c70_he_detail::vtype<uint8_t, 32>;
using __uchar64 = _c70_he_detail::vtype<uint8_t, 64>;

using __short2  = _c70_he_detail::vtype<int16_t, 2>;
using __short4  = _c70_he_detail::vtype<int16_t, 4>;
using __short8  = _c70_he_detail::vtype<int16_t, 8>;
using __short16 = _c70_he_detail::vtype<int16_t, 16>;
using __short32 = _c70_he_detail::vtype<int16_t, 32>;

using __ushort2  = _c70_he_detail::vtype<uint16_t, 2>;
using __ushort4  = _c70_he_detail::vtype<uint16_t, 4>;
using __ushort8  = _c70_he_detail::vtype<uint16_t, 8>;
using __ushort16 = _c70_he_detail::vtype<uint16_t, 16>;
using __ushort32 = _c70_he_detail::vtype<uint16_t, 32>;

using __int2  = _c70_he_detail::vtype<int32_t, 2>;
using __int4  = _c70_he_detail::vtype<int32_t, 4>;

#ifdef _MSC_VER
#define __int16 int16
#define __int8 int8
/* __MINGW32__ is defined in both 32 bit and 64 bit MINGW */
#elif defined __MINGW32__
#define __int16 int16
#define __int8 int8
#else
using __int8  = _c70_he_detail::vtype<int32_t, 8>;
using __int16 = _c70_he_detail::vtype<int32_t, 16>;
#endif

using __uint2  = _c70_he_detail::vtype<uint32_t, 2>;
using __uint4  = _c70_he_detail::vtype<uint32_t, 4>;
using __uint8  = _c70_he_detail::vtype<uint32_t, 8>;
using __uint16 = _c70_he_detail::vtype<uint32_t, 16>;

using __float2  = _c70_he_detail::vtype<float, 2>;
using __float4  = _c70_he_detail::vtype<float, 4>;
using __float8  = _c70_he_detail::vtype<float, 8>;
using __float16 = _c70_he_detail::vtype<float, 16>;

using __long2   = _c70_he_detail::vtype<int64_t, 2>;
using __long4   = _c70_he_detail::vtype<int64_t, 4>;
using __long8   = _c70_he_detail::vtype<int64_t, 8>;
using __long16  = _c70_he_detail::vtype<int64_t, 16>;

using __ulong2  = _c70_he_detail::vtype<uint64_t, 2>;
using __ulong4  = _c70_he_detail::vtype<uint64_t, 4>;
using __ulong8  = _c70_he_detail::vtype<uint64_t, 8>;
using __ulong16 = _c70_he_detail::vtype<uint64_t, 16>;

using __double2  = _c70_he_detail::vtype<double, 2>;
using __double4  = _c70_he_detail::vtype<double, 4>;
using __double8  = _c70_he_detail::vtype<double, 8>;
using __double16 = _c70_he_detail::vtype<double, 16>;

using __cchar   = _c70_he_detail::ctype<int8_t>;
using __cshort  = _c70_he_detail::ctype<int16_t>;
using __cint    = _c70_he_detail::ctype<int32_t>;
using __clong   = _c70_he_detail::ctype<int64_t>;
using __cfloat  = _c70_he_detail::ctype<float>;
using __cdouble = _c70_he_detail::ctype<double>;

using __cchar2  = _c70_he_detail::vtype<__cchar, 2>;
using __cchar4  = _c70_he_detail::vtype<__cchar, 4>;
using __cchar8  = _c70_he_detail::vtype<__cchar, 8>;
using __cchar16 = _c70_he_detail::vtype<__cchar, 16>;
using __cchar32 = _c70_he_detail::vtype<__cchar, 32>;

using __cshort2  = _c70_he_detail::vtype<__cshort, 2>;
using __cshort4  = _c70_he_detail::vtype<__cshort, 4>;
using __cshort8  = _c70_he_detail::vtype<__cshort, 8>;
using __cshort16 = _c70_he_detail::vtype<__cshort, 16>;

using __cint2  = _c70_he_detail::vtype<__cint, 2>;
using __cint4  = _c70_he_detail::vtype<__cint, 4>;
using __cint8  = _c70_he_detail::vtype<__cint, 8>;

using __cfloat2  = _c70_he_detail::vtype<__cfloat, 2>;
using __cfloat4  = _c70_he_detail::vtype<__cfloat, 4>;
using __cfloat8  = _c70_he_detail::vtype<__cfloat, 8>;

using __clong2  = _c70_he_detail::vtype<__clong, 2>;
using __clong4  = _c70_he_detail::vtype<__clong, 4>;
using __clong8  = _c70_he_detail::vtype<__clong, 8>;

using __cdouble2  = _c70_he_detail::vtype<__cdouble, 2>;
using __cdouble4  = _c70_he_detail::vtype<__cdouble, 4>;
using __cdouble8  = _c70_he_detail::vtype<__cdouble, 8>;


using __char2_ptr  = _c70_he_detail::vtype_ptr<int8_t, 2>;
using __char4_ptr  = _c70_he_detail::vtype_ptr<int8_t, 4>;
using __char8_ptr  = _c70_he_detail::vtype_ptr<int8_t, 8>;
using __char16_ptr = _c70_he_detail::vtype_ptr<int8_t, 16>;
using __char32_ptr = _c70_he_detail::vtype_ptr<int8_t, 32>;
using __char64_ptr = _c70_he_detail::vtype_ptr<int8_t, 64>;

using __uchar2_ptr  = _c70_he_detail::vtype_ptr<uint8_t, 2>;
using __uchar4_ptr  = _c70_he_detail::vtype_ptr<uint8_t, 4>;
using __uchar8_ptr  = _c70_he_detail::vtype_ptr<uint8_t, 8>;
using __uchar16_ptr = _c70_he_detail::vtype_ptr<uint8_t, 16>;
using __uchar32_ptr = _c70_he_detail::vtype_ptr<uint8_t, 32>;
using __uchar64_ptr = _c70_he_detail::vtype_ptr<uint8_t, 64>;

using __short2_ptr  = _c70_he_detail::vtype_ptr<int16_t, 2>;
using __short4_ptr  = _c70_he_detail::vtype_ptr<int16_t, 4>;
using __short8_ptr  = _c70_he_detail::vtype_ptr<int16_t, 8>;
using __short16_ptr = _c70_he_detail::vtype_ptr<int16_t, 16>;
using __short32_ptr = _c70_he_detail::vtype_ptr<int16_t, 32>;

using __ushort2_ptr  = _c70_he_detail::vtype_ptr<uint16_t, 2>;
using __ushort4_ptr  = _c70_he_detail::vtype_ptr<uint16_t, 4>;
using __ushort8_ptr  = _c70_he_detail::vtype_ptr<uint16_t, 8>;
using __ushort16_ptr = _c70_he_detail::vtype_ptr<uint16_t, 16>;
using __ushort32_ptr = _c70_he_detail::vtype_ptr<uint16_t, 32>;

using __int2_ptr  = _c70_he_detail::vtype_ptr<int32_t, 2>;
using __int4_ptr  = _c70_he_detail::vtype_ptr<int32_t, 4>;
using __int8_ptr  = _c70_he_detail::vtype_ptr<int32_t, 8>;
using __int16_ptr = _c70_he_detail::vtype_ptr<int32_t, 16>;

using __uint2_ptr  = _c70_he_detail::vtype_ptr<uint32_t, 2>;
using __uint4_ptr  = _c70_he_detail::vtype_ptr<uint32_t, 4>;
using __uint8_ptr  = _c70_he_detail::vtype_ptr<uint32_t, 8>;
using __uint16_ptr = _c70_he_detail::vtype_ptr<uint32_t, 16>;

using __float2_ptr  = _c70_he_detail::vtype_ptr<float, 2>;
using __float4_ptr  = _c70_he_detail::vtype_ptr<float, 4>;
using __float8_ptr  = _c70_he_detail::vtype_ptr<float, 8>;
using __float16_ptr = _c70_he_detail::vtype_ptr<float, 16>;

using __long2_ptr   = _c70_he_detail::vtype_ptr<int64_t, 2>;
using __long4_ptr   = _c70_he_detail::vtype_ptr<int64_t, 4>;
using __long8_ptr   = _c70_he_detail::vtype_ptr<int64_t, 8>;
using __long16_ptr  = _c70_he_detail::vtype_ptr<int64_t, 16>;

using __ulong2_ptr  = _c70_he_detail::vtype_ptr<uint64_t, 2>;
using __ulong4_ptr  = _c70_he_detail::vtype_ptr<uint64_t, 4>;
using __ulong8_ptr  = _c70_he_detail::vtype_ptr<uint64_t, 8>;
using __ulong16_ptr = _c70_he_detail::vtype_ptr<uint64_t, 16>;

using __double2_ptr  = _c70_he_detail::vtype_ptr<double, 2>;
using __double4_ptr  = _c70_he_detail::vtype_ptr<double, 4>;
using __double8_ptr  = _c70_he_detail::vtype_ptr<double, 8>;
using __double16_ptr = _c70_he_detail::vtype_ptr<double, 16>;

using __cchar   = _c70_he_detail::ctype<int8_t>;
using __cshort  = _c70_he_detail::ctype<int16_t>;
using __cint    = _c70_he_detail::ctype<int32_t>;
using __clong   = _c70_he_detail::ctype<int64_t>;
using __cfloat  = _c70_he_detail::ctype<float>;
using __cdouble = _c70_he_detail::ctype<double>;

using __cchar_ptr   = _c70_he_detail::ctype_ptr<int8_t>;
using __cshort_ptr  = _c70_he_detail::ctype_ptr<int16_t>;
using __cint_ptr    = _c70_he_detail::ctype_ptr<int32_t>;
using __clong_ptr   = _c70_he_detail::ctype_ptr<int64_t>;
using __cfloat_ptr  = _c70_he_detail::ctype_ptr<float>;
using __cdouble_ptr = _c70_he_detail::ctype_ptr<double>;

using __cchar2_ptr  = _c70_he_detail::vtype_ptr<__cchar, 2>;
using __cchar4_ptr  = _c70_he_detail::vtype_ptr<__cchar, 4>;
using __cchar8_ptr  = _c70_he_detail::vtype_ptr<__cchar, 8>;
using __cchar16_ptr = _c70_he_detail::vtype_ptr<__cchar, 16>;
using __cchar32_ptr = _c70_he_detail::vtype_ptr<__cchar, 32>;

using __cshort2_ptr  = _c70_he_detail::vtype_ptr<__cshort, 2>;
using __cshort4_ptr  = _c70_he_detail::vtype_ptr<__cshort, 4>;
using __cshort8_ptr  = _c70_he_detail::vtype_ptr<__cshort, 8>;
using __cshort16_ptr = _c70_he_detail::vtype_ptr<__cshort, 16>;

using __cint2_ptr  = _c70_he_detail::vtype_ptr<__cint, 2>;
using __cint4_ptr  = _c70_he_detail::vtype_ptr<__cint, 4>;
using __cint8_ptr  = _c70_he_detail::vtype_ptr<__cint, 8>;

using __cfloat2_ptr  = _c70_he_detail::vtype_ptr<__cfloat, 2>;
using __cfloat4_ptr  = _c70_he_detail::vtype_ptr<__cfloat, 4>;
using __cfloat8_ptr  = _c70_he_detail::vtype_ptr<__cfloat, 8>;

using __clong2_ptr  = _c70_he_detail::vtype_ptr<__clong, 2>;
using __clong4_ptr  = _c70_he_detail::vtype_ptr<__clong, 4>;
using __clong8_ptr  = _c70_he_detail::vtype_ptr<__clong, 8>;

using __cdouble2_ptr  = _c70_he_detail::vtype_ptr<__cdouble, 2>;
using __cdouble4_ptr  = _c70_he_detail::vtype_ptr<__cdouble, 4>;
using __cdouble8_ptr  = _c70_he_detail::vtype_ptr<__cdouble, 8>;


typedef uint8_t  uchar;
typedef uint16_t ushort;
typedef uint32_t uint;
typedef uint64_t ulong;

using bool2  = _c70_he_detail::bvtype<2>;
using bool4  = _c70_he_detail::bvtype<4>;
using bool8  = _c70_he_detail::bvtype<8>;
using bool16 = _c70_he_detail::bvtype<16>;
using bool32 = _c70_he_detail::bvtype<32>;
using bool64 = _c70_he_detail::bvtype<64>;

using char2  = _c70_he_detail::vtype<int8_t, 2>;
using char4  = _c70_he_detail::vtype<int8_t, 4>;
using char8  = _c70_he_detail::vtype<int8_t, 8>;
using char16 = _c70_he_detail::vtype<int8_t, 16>;
using char32 = _c70_he_detail::vtype<int8_t, 32>;
using char64 = _c70_he_detail::vtype<int8_t, 64>;

using uchar2  = _c70_he_detail::vtype<uint8_t, 2>;
using uchar4  = _c70_he_detail::vtype<uint8_t, 4>;
using uchar8  = _c70_he_detail::vtype<uint8_t, 8>;
using uchar16 = _c70_he_detail::vtype<uint8_t, 16>;
using uchar32 = _c70_he_detail::vtype<uint8_t, 32>;
using uchar64 = _c70_he_detail::vtype<uint8_t, 64>;

using short2  = _c70_he_detail::vtype<int16_t, 2>;
using short4  = _c70_he_detail::vtype<int16_t, 4>;
using short8  = _c70_he_detail::vtype<int16_t, 8>;
using short16 = _c70_he_detail::vtype<int16_t, 16>;
using short32 = _c70_he_detail::vtype<int16_t, 32>;

using ushort2  = _c70_he_detail::vtype<uint16_t, 2>;
using ushort4  = _c70_he_detail::vtype<uint16_t, 4>;
using ushort8  = _c70_he_detail::vtype<uint16_t, 8>;
using ushort16 = _c70_he_detail::vtype<uint16_t, 16>;
using ushort32 = _c70_he_detail::vtype<uint16_t, 32>;

using int2  = _c70_he_detail::vtype<int32_t, 2>;
using int4  = _c70_he_detail::vtype<int32_t, 4>;
using int8  = _c70_he_detail::vtype<int32_t, 8>;
using int16 = _c70_he_detail::vtype<int32_t, 16>;

using uint2  = _c70_he_detail::vtype<uint32_t, 2>;
using uint4  = _c70_he_detail::vtype<uint32_t, 4>;
using uint8  = _c70_he_detail::vtype<uint32_t, 8>;
using uint16 = _c70_he_detail::vtype<uint32_t, 16>;

using float2  = _c70_he_detail::vtype<float, 2>;
using float4  = _c70_he_detail::vtype<float, 4>;
using float8  = _c70_he_detail::vtype<float, 8>;
using float16 = _c70_he_detail::vtype<float, 16>;

using long2  = _c70_he_detail::vtype<int64_t, 2>;
using long4  = _c70_he_detail::vtype<int64_t, 4>;
using long8  = _c70_he_detail::vtype<int64_t, 8>;
using long16 = _c70_he_detail::vtype<int64_t, 16>;

using ulong2  = _c70_he_detail::vtype<uint64_t, 2>;
using ulong4  = _c70_he_detail::vtype<uint64_t, 4>;
using ulong8  = _c70_he_detail::vtype<uint64_t, 8>;
using ulong16 = _c70_he_detail::vtype<uint64_t, 16>;

using double2  = _c70_he_detail::vtype<double, 2>;
using double4  = _c70_he_detail::vtype<double, 4>;
using double8  = _c70_he_detail::vtype<double, 8>;
using double16 = _c70_he_detail::vtype<double, 16>;

using cchar   = _c70_he_detail::ctype<int8_t>;
using cshort  = _c70_he_detail::ctype<int16_t>;
using cint    = _c70_he_detail::ctype<int32_t>;
using clong   = _c70_he_detail::ctype<int64_t>;
using cfloat  = _c70_he_detail::ctype<float>;
using cdouble = _c70_he_detail::ctype<double>;

using cchar2  = _c70_he_detail::vtype<cchar, 2>;
using cchar4  = _c70_he_detail::vtype<cchar, 4>;
using cchar8  = _c70_he_detail::vtype<cchar, 8>;
using cchar16 = _c70_he_detail::vtype<cchar, 16>;
using cchar32 = _c70_he_detail::vtype<cchar, 32>;

using cshort2  = _c70_he_detail::vtype<cshort, 2>;
using cshort4  = _c70_he_detail::vtype<cshort, 4>;
using cshort8  = _c70_he_detail::vtype<cshort, 8>;
using cshort16 = _c70_he_detail::vtype<cshort, 16>;

using cint2  = _c70_he_detail::vtype<cint, 2>;
using cint4  = _c70_he_detail::vtype<cint, 4>;
using cint8  = _c70_he_detail::vtype<cint, 8>;

using cfloat2  = _c70_he_detail::vtype<cfloat, 2>;
using cfloat4  = _c70_he_detail::vtype<cfloat, 4>;
using cfloat8  = _c70_he_detail::vtype<cfloat, 8>;

using clong2  = _c70_he_detail::vtype<clong, 2>;
using clong4  = _c70_he_detail::vtype<clong, 4>;
using clong8  = _c70_he_detail::vtype<clong, 8>;

using cdouble2  = _c70_he_detail::vtype<cdouble, 2>;
using cdouble4  = _c70_he_detail::vtype<cdouble, 4>;
using cdouble8  = _c70_he_detail::vtype<cdouble, 8>;


using char2_ptr  = _c70_he_detail::vtype_ptr<int8_t, 2>;
using char4_ptr  = _c70_he_detail::vtype_ptr<int8_t, 4>;
using char8_ptr  = _c70_he_detail::vtype_ptr<int8_t, 8>;
using char16_ptr = _c70_he_detail::vtype_ptr<int8_t, 16>;
using char32_ptr = _c70_he_detail::vtype_ptr<int8_t, 32>;
using char64_ptr = _c70_he_detail::vtype_ptr<int8_t, 64>;

using uchar2_ptr  = _c70_he_detail::vtype_ptr<uint8_t, 2>;
using uchar4_ptr  = _c70_he_detail::vtype_ptr<uint8_t, 4>;
using uchar8_ptr  = _c70_he_detail::vtype_ptr<uint8_t, 8>;
using uchar16_ptr = _c70_he_detail::vtype_ptr<uint8_t, 16>;
using uchar32_ptr = _c70_he_detail::vtype_ptr<uint8_t, 32>;
using uchar64_ptr = _c70_he_detail::vtype_ptr<uint8_t, 64>;

using short2_ptr  = _c70_he_detail::vtype_ptr<int16_t, 2>;
using short4_ptr  = _c70_he_detail::vtype_ptr<int16_t, 4>;
using short8_ptr  = _c70_he_detail::vtype_ptr<int16_t, 8>;
using short16_ptr = _c70_he_detail::vtype_ptr<int16_t, 16>;
using short32_ptr = _c70_he_detail::vtype_ptr<int16_t, 32>;

using ushort2_ptr  = _c70_he_detail::vtype_ptr<uint16_t, 2>;
using ushort4_ptr  = _c70_he_detail::vtype_ptr<uint16_t, 4>;
using ushort8_ptr  = _c70_he_detail::vtype_ptr<uint16_t, 8>;
using ushort16_ptr = _c70_he_detail::vtype_ptr<uint16_t, 16>;
using ushort32_ptr = _c70_he_detail::vtype_ptr<uint16_t, 32>;

using int2_ptr  = _c70_he_detail::vtype_ptr<int32_t, 2>;
using int4_ptr  = _c70_he_detail::vtype_ptr<int32_t, 4>;
using int8_ptr  = _c70_he_detail::vtype_ptr<int32_t, 8>;
using int16_ptr = _c70_he_detail::vtype_ptr<int32_t, 16>;

using uint2_ptr  = _c70_he_detail::vtype_ptr<uint32_t, 2>;
using uint4_ptr  = _c70_he_detail::vtype_ptr<uint32_t, 4>;
using uint8_ptr  = _c70_he_detail::vtype_ptr<uint32_t, 8>;
using uint16_ptr = _c70_he_detail::vtype_ptr<uint32_t, 16>;

using float2_ptr  = _c70_he_detail::vtype_ptr<float, 2>;
using float4_ptr  = _c70_he_detail::vtype_ptr<float, 4>;
using float8_ptr  = _c70_he_detail::vtype_ptr<float, 8>;
using float16_ptr = _c70_he_detail::vtype_ptr<float, 16>;

using long2_ptr  = _c70_he_detail::vtype_ptr<int64_t, 2>;
using long4_ptr  = _c70_he_detail::vtype_ptr<int64_t, 4>;
using long8_ptr  = _c70_he_detail::vtype_ptr<int64_t, 8>;
using long16_ptr = _c70_he_detail::vtype_ptr<int64_t, 16>;

using ulong2_ptr  = _c70_he_detail::vtype_ptr<uint64_t, 2>;
using ulong4_ptr  = _c70_he_detail::vtype_ptr<uint64_t, 4>;
using ulong8_ptr  = _c70_he_detail::vtype_ptr<uint64_t, 8>;
using ulong16_ptr = _c70_he_detail::vtype_ptr<uint64_t, 16>;

using double2_ptr  = _c70_he_detail::vtype_ptr<double, 2>;
using double4_ptr  = _c70_he_detail::vtype_ptr<double, 4>;
using double8_ptr  = _c70_he_detail::vtype_ptr<double, 8>;
using double16_ptr = _c70_he_detail::vtype_ptr<double, 16>;

using cchar   = _c70_he_detail::ctype<int8_t>;
using cshort  = _c70_he_detail::ctype<int16_t>;
using cint    = _c70_he_detail::ctype<int32_t>;
using clong   = _c70_he_detail::ctype<int64_t>;
using cfloat  = _c70_he_detail::ctype<float>;
using cdouble = _c70_he_detail::ctype<double>;

using cchar_ptr   = _c70_he_detail::ctype_ptr<int8_t>;
using cshort_ptr  = _c70_he_detail::ctype_ptr<int16_t>;
using cint_ptr    = _c70_he_detail::ctype_ptr<int32_t>;
using clong_ptr   = _c70_he_detail::ctype_ptr<int64_t>;
using cfloat_ptr  = _c70_he_detail::ctype_ptr<float>;
using cdouble_ptr = _c70_he_detail::ctype_ptr<double>;

using cchar2_ptr  = _c70_he_detail::vtype_ptr<cchar, 2>;
using cchar4_ptr  = _c70_he_detail::vtype_ptr<cchar, 4>;
using cchar8_ptr  = _c70_he_detail::vtype_ptr<cchar, 8>;
using cchar16_ptr = _c70_he_detail::vtype_ptr<cchar, 16>;
using cchar32_ptr = _c70_he_detail::vtype_ptr<cchar, 32>;

using cshort2_ptr  = _c70_he_detail::vtype_ptr<cshort, 2>;
using cshort4_ptr  = _c70_he_detail::vtype_ptr<cshort, 4>;
using cshort8_ptr  = _c70_he_detail::vtype_ptr<cshort, 8>;
using cshort16_ptr = _c70_he_detail::vtype_ptr<cshort, 16>;

using cint2_ptr  = _c70_he_detail::vtype_ptr<cint, 2>;
using cint4_ptr  = _c70_he_detail::vtype_ptr<cint, 4>;
using cint8_ptr  = _c70_he_detail::vtype_ptr<cint, 8>;

using cfloat2_ptr  = _c70_he_detail::vtype_ptr<cfloat, 2>;
using cfloat4_ptr  = _c70_he_detail::vtype_ptr<cfloat, 4>;
using cfloat8_ptr  = _c70_he_detail::vtype_ptr<cfloat, 8>;

using clong2_ptr  = _c70_he_detail::vtype_ptr<clong, 2>;
using clong4_ptr  = _c70_he_detail::vtype_ptr<clong, 4>;
using clong8_ptr  = _c70_he_detail::vtype_ptr<clong, 8>;

using cdouble2_ptr  = _c70_he_detail::vtype_ptr<cdouble, 2>;
using cdouble4_ptr  = _c70_he_detail::vtype_ptr<cdouble, 4>;
using cdouble8_ptr  = _c70_he_detail::vtype_ptr<cdouble, 8>;

/******************************************************************************
* Definition of vector utilities.
******************************************************************************/

//-----------------------------------------------------------------------------
// Reinterpretation casts
//-----------------------------------------------------------------------------

using _c70_he_detail::__as_long16;
using _c70_he_detail::__as_long8;
using _c70_he_detail::__as_long4;
using _c70_he_detail::__as_long2;
using _c70_he_detail::__as_long;

using _c70_he_detail::__as_ulong16;
using _c70_he_detail::__as_ulong8;
using _c70_he_detail::__as_ulong4;
using _c70_he_detail::__as_ulong2;
using _c70_he_detail::__as_ulong;

using _c70_he_detail::__as_double16;
using _c70_he_detail::__as_double8;
using _c70_he_detail::__as_double4;
using _c70_he_detail::__as_double2;
using _c70_he_detail::__as_double;

using _c70_he_detail::__as_int16;
using _c70_he_detail::__as_int8;
using _c70_he_detail::__as_int4;
using _c70_he_detail::__as_int2;
using _c70_he_detail::__as_int;

using _c70_he_detail::__as_uint16;
using _c70_he_detail::__as_uint8;
using _c70_he_detail::__as_uint4;
using _c70_he_detail::__as_uint2;
using _c70_he_detail::__as_uint;

using _c70_he_detail::__as_float16;
using _c70_he_detail::__as_float8;
using _c70_he_detail::__as_float4;
using _c70_he_detail::__as_float2;
using _c70_he_detail::__as_float;

using _c70_he_detail::__as_short32;
using _c70_he_detail::__as_short16;
using _c70_he_detail::__as_short8;
using _c70_he_detail::__as_short4;
using _c70_he_detail::__as_short2;
using _c70_he_detail::__as_short;

using _c70_he_detail::__as_ushort32;
using _c70_he_detail::__as_ushort16;
using _c70_he_detail::__as_ushort8;
using _c70_he_detail::__as_ushort4;
using _c70_he_detail::__as_ushort2;
using _c70_he_detail::__as_ushort;

using _c70_he_detail::__as_char64;
using _c70_he_detail::__as_char32;
using _c70_he_detail::__as_char16;
using _c70_he_detail::__as_char8;
using _c70_he_detail::__as_char4;
using _c70_he_detail::__as_char2;
using _c70_he_detail::__as_char;

using _c70_he_detail::__as_uchar64;
using _c70_he_detail::__as_uchar32;
using _c70_he_detail::__as_uchar16;
using _c70_he_detail::__as_uchar8;
using _c70_he_detail::__as_uchar4;
using _c70_he_detail::__as_uchar2;
using _c70_he_detail::__as_uchar;

using _c70_he_detail::__as_clong8;
using _c70_he_detail::__as_clong4;
using _c70_he_detail::__as_clong2;
using _c70_he_detail::__as_clong;

using _c70_he_detail::__as_cdouble8;
using _c70_he_detail::__as_cdouble4;
using _c70_he_detail::__as_cdouble2;
using _c70_he_detail::__as_cdouble;

using _c70_he_detail::__as_cint8;
using _c70_he_detail::__as_cint4;
using _c70_he_detail::__as_cint2;
using _c70_he_detail::__as_cint;

using _c70_he_detail::__as_cfloat8;
using _c70_he_detail::__as_cfloat4;
using _c70_he_detail::__as_cfloat2;
using _c70_he_detail::__as_cfloat;

using _c70_he_detail::__as_cshort16;
using _c70_he_detail::__as_cshort8;
using _c70_he_detail::__as_cshort4;
using _c70_he_detail::__as_cshort2;
using _c70_he_detail::__as_cshort;

using _c70_he_detail::__as_cchar32;
using _c70_he_detail::__as_cchar16;
using _c70_he_detail::__as_cchar8;
using _c70_he_detail::__as_cchar4;
using _c70_he_detail::__as_cchar2;
using _c70_he_detail::__as_cchar;

//-----------------------------------------------------------------------------
// Conversion casts
//-----------------------------------------------------------------------------
using _c70_he_detail::__convert_long16;
using _c70_he_detail::__convert_long8;
using _c70_he_detail::__convert_long4;
using _c70_he_detail::__convert_long2;
using _c70_he_detail::__convert_long;

using _c70_he_detail::__convert_ulong16;
using _c70_he_detail::__convert_ulong8;
using _c70_he_detail::__convert_ulong4;
using _c70_he_detail::__convert_ulong2;
using _c70_he_detail::__convert_ulong;

using _c70_he_detail::__convert_double16;
using _c70_he_detail::__convert_double8;
using _c70_he_detail::__convert_double4;
using _c70_he_detail::__convert_double2;
using _c70_he_detail::__convert_double;

using _c70_he_detail::__convert_int16;
using _c70_he_detail::__convert_int8;
using _c70_he_detail::__convert_int4;
using _c70_he_detail::__convert_int2;
using _c70_he_detail::__convert_int;

using _c70_he_detail::__convert_uint16;
using _c70_he_detail::__convert_uint8;
using _c70_he_detail::__convert_uint4;
using _c70_he_detail::__convert_uint2;
using _c70_he_detail::__convert_uint;

using _c70_he_detail::__convert_float16;
using _c70_he_detail::__convert_float8;
using _c70_he_detail::__convert_float4;
using _c70_he_detail::__convert_float2;
using _c70_he_detail::__convert_float;

using _c70_he_detail::__convert_short32;
using _c70_he_detail::__convert_short16;
using _c70_he_detail::__convert_short8;
using _c70_he_detail::__convert_short4;
using _c70_he_detail::__convert_short2;
using _c70_he_detail::__convert_short;

using _c70_he_detail::__convert_ushort32;
using _c70_he_detail::__convert_ushort16;
using _c70_he_detail::__convert_ushort8;
using _c70_he_detail::__convert_ushort4;
using _c70_he_detail::__convert_ushort2;
using _c70_he_detail::__convert_ushort;

using _c70_he_detail::__convert_char64;
using _c70_he_detail::__convert_char32;
using _c70_he_detail::__convert_char16;
using _c70_he_detail::__convert_char8;
using _c70_he_detail::__convert_char4;
using _c70_he_detail::__convert_char2;
using _c70_he_detail::__convert_char;

using _c70_he_detail::__convert_uchar64;
using _c70_he_detail::__convert_uchar32;
using _c70_he_detail::__convert_uchar16;
using _c70_he_detail::__convert_uchar8;
using _c70_he_detail::__convert_uchar4;
using _c70_he_detail::__convert_uchar2;
using _c70_he_detail::__convert_uchar;

using _c70_he_detail::__convert_clong8;
using _c70_he_detail::__convert_clong4;
using _c70_he_detail::__convert_clong2;
using _c70_he_detail::__convert_clong;

using _c70_he_detail::__convert_cdouble8;
using _c70_he_detail::__convert_cdouble4;
using _c70_he_detail::__convert_cdouble2;
using _c70_he_detail::__convert_cdouble;

using _c70_he_detail::__convert_cint8;
using _c70_he_detail::__convert_cint4;
using _c70_he_detail::__convert_cint2;
using _c70_he_detail::__convert_cint;

using _c70_he_detail::__convert_cfloat8;
using _c70_he_detail::__convert_cfloat4;
using _c70_he_detail::__convert_cfloat2;
using _c70_he_detail::__convert_cfloat;

using _c70_he_detail::__convert_cshort16;
using _c70_he_detail::__convert_cshort8;
using _c70_he_detail::__convert_cshort4;
using _c70_he_detail::__convert_cshort2;
using _c70_he_detail::__convert_cshort;

using _c70_he_detail::__convert_cchar32;
using _c70_he_detail::__convert_cchar16;
using _c70_he_detail::__convert_cchar8;
using _c70_he_detail::__convert_cchar4;
using _c70_he_detail::__convert_cchar2;
using _c70_he_detail::__convert_cchar;

//-----------------------------------------------------------------------------
// Pointer Conversion Intrinsics (DEPRECATED IN FAVOR OF C-STYLE CASTS))
//-----------------------------------------------------------------------------

// Convert from vector pointer to an "element type" pointer
// Ex: int4_ptr  to int32_t*
// Ex: cint4_ptr to int32_t* (only allowed when previously init'd using int*)
// Ex: cint4_ptr to cint_ptr
// C-style cast: uint8_t *p = (uint8_t*)(pointer);
#define vtos_ptr(type, addr) ((type*)(addr))

// Convert from scalar pointer to vector pointer
// Ex: int32_t* to int4_ptr
// Ex: int32_t* to cint4_ptr
// Ex: cint* to cint4_ptr
// C-style cast: uchar64_ptr p = (uchar64_ptr)(pointer);
#define stov_ptr(type, addr) ((type##_ptr)(addr))

// Convert from complex element pointer to scalar pointer
// Ex: cint to int32_t*
// C-style cast: int32_t* p = (int32_t*)(pointer);
#define ctos_ptr(type, addr) ((type*)(addr))

// Convert from scalar pointer to complex element type pointer
// Ex: int32_t* to cint
// C-style cast: cint_ptr p = (cint_ptr)(pointer);
#define stoc_ptr(type, addr) ((type##_ptr)(addr))

// Convert from vector pointer to vector pointer (not supported for complex)
// Note: Use with care for where the original vector's memory is allocated.
// Ex: int4_ptr to char16_ptr
// C-style cast: char16_ptr p = (char16_ptr)(pointer);

#endif /* VECTOR_H */
