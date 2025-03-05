/*****************************************************************************/
/*  VECTOR.H                                                                 */
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

#include <cstdint>
#include <cstring>
#include <climits>
#include <cstddef>

#include <ti_he_impl/c7x_c_funcs.h>
#include <ti_he_impl/targ_defs.h>

namespace _c70_he_detail
{

/******************************************************************************
* VTYPE_KIND -- Controls the behavior of vtype in the context of subvector
*   accesses.
*
*   DATA: A normal vector. The vector will contain data.
*   REF: The result of a subvector accessor on a non-const vector. The vector
*     will contain references.
*   CONST_REF: The result of a subvector accessor on a const vector. The vector
*     will contain references to const data.
******************************************************************************/
enum class VTYPE_KIND { DATA, REF, CONST_REF };

/******************************************************************************
*
* Forward declarations
*
******************************************************************************/
template <typename ELEM_T, size_t NELEM, VTYPE_KIND KIND>
class vtype;

template<typename ELEM_T>
class ctype;


/******************************************************************************
*
* Utility templates
*
*******************************************************************************/

/******************************************************************************
* enable_if_cmplx_t -- Helpful alias used to detect if a type is a complex type
*******************************************************************************/
template <typename TEST_T, typename RET_T>
using enable_if_cmplx_t = std::enable_if_t<(!std::is_arithmetic<TEST_T>::value),
                                            RET_T>;

/******************************************************************************
* sa_scale -- host emulation implementation of the sizeof(t)/__numelemof(t) for
*   use in __SA* macros.
*******************************************************************************/
template <typename T>
struct sa_scale
{
    static constexpr int value = sizeof(T);
};
// Complex specialization
template <typename CE>
struct sa_scale<ctype<CE> >
{
    static constexpr int value = sizeof(CE) * 2;
};
// Vector specialization
template <typename VE,
          size_t NELEM,
          VTYPE_KIND KIND>
struct sa_scale<vtype<VE, NELEM, KIND> >
{
    static constexpr int value = sa_scale<VE>::value;
};


/******************************************************************************
*
* Helper functions to interface with the C functional description.
*
******************************************************************************/

/******************************************************************************
* init_from_vreg_t -- Converts a vreg_t to another class whose elements are
*   referenced via a reference wrapper array.
*******************************************************************************/
// Arithmetic variant
template <class ACCESS_T,
          typename ELEM_T,
          size_t NELEM,
          std::enable_if_t<std::is_arithmetic<ELEM_T>::value, int> = 0>
void init_from_vreg_t(const vreg_t &src, ACCESS_T &dst)
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

        // memcpy avoids strict aliasing issues when type-punning
        memcpy(&dst.s[i], &val, sizeof(ELEM_T));
    }
}

// Complex variant
template <class ACCESS_T,
          typename ELEM_T,
          size_t NELEM,
          enable_if_cmplx_t<ELEM_T, int> = 0>
void init_from_vreg_t(const vreg_t &src, ACCESS_T &dst)
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

        // memcpy avoids strict aliasing issues when type-punning
        memcpy(&val_i_cast, &val_imag, sizeof(typename ELEM_T::ELEM_TYPE));
        memcpy(&val_r_cast, &val_real, sizeof(typename ELEM_T::ELEM_TYPE));

        dst.s[i] = ELEM_T(val_r_cast, val_i_cast);

        vec_count += 2;
    }
}

/******************************************************************************
* convert_to_vreg_t -- Converts an object whose elements are referenced via a
*   reference wrapper array into a vreg_t for use by the C functional
*   description.
*******************************************************************************/
// Arithmetic variant
template<class ACCESS_T,
         typename ELEM_T,
         size_t NELEM,
         std::enable_if_t<std::is_arithmetic<ELEM_T>::value, int> = 0>
vreg_t convert_to_vreg_t(const ACCESS_T &src)
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

        uint64_t src_val = 0;
        memcpy(&src_val, &src.s[i], sizeof(ELEM_T));

        val = (val & val_mask) |
              ((src_val << lane_bit_offset) & lane_mask);

        put_unsigned_value(res, val, vindex);
    }

    return res;
}

// Complex variant
template<class ACCESS_T,
         typename ELEM_T,
         size_t NELEM,
         enable_if_cmplx_t<ELEM_T, int> = 0>
vreg_t convert_to_vreg_t(const ACCESS_T &src)
{
    vreg_t res;

    vtype<typename ELEM_T::ELEM_TYPE, NELEM * 2, VTYPE_KIND::DATA> vec_type =
              vtype<typename ELEM_T::ELEM_TYPE, NELEM * 2, VTYPE_KIND::DATA>(0);

    size_t vec_count = 0;
    for (uint32_t i = 0; i < NELEM ; i++)
    {
        // Grab ctype at index
        ELEM_T temp = src.s[i];
        vec_type.s[vec_count] = temp.i();
        vec_type.s[vec_count + 1] = temp.r();
        vec_count += 2;
    }

    res = convert_to_vreg_t<vtype<typename ELEM_T::ELEM_TYPE,
                                  NELEM * 2,
                                  VTYPE_KIND::DATA>,
                            typename ELEM_T::ELEM_TYPE,
                            NELEM * 2>(vec_type);

    return res;
}

/******************************************************************************
* convert_ctype_to_vreg_t -- Converts a complex element object whose elements
*   are referenced via a reference wrapper array into a vreg_t for use by the C
*   functional description.
*******************************************************************************/
template<typename ELEM_T>
vreg_t convert_ctype_to_vreg_t(const ctype<ELEM_T> &src)
{
    vreg_t res;

    vtype<ELEM_T, 2, VTYPE_KIND::DATA> vec_type =
                                          vtype<ELEM_T, 2, VTYPE_KIND::DATA>(0);

    vec_type.s[0] = src.i();
    vec_type.s[1] = src.r();

    res = convert_to_vreg_t<vtype<ELEM_T,
                                  2,
                                  VTYPE_KIND::DATA>,
                            ELEM_T,
                            2>(vec_type);

    return res;
}

/******************************************************************************
* init_ctype_from_vreg_t -- Converts a vreg_t to a complex element whose
*   elements are referenced via a reference wrapper array.
*******************************************************************************/
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

    // memcpy avoids strict aliasing issues when type-punning
    memcpy(&val_i_cast, &val_imag, sizeof(ELEM_T));
    memcpy(&val_r_cast, &val_real, sizeof(ELEM_T));

    dst.i() = val_i_cast;
    dst.r() = val_r_cast;
}

/******************************************************************************
* complex_swapper -- Utility class to swap complex components if the input is
*   complex. Used to generalize reinterpret conversions, which need complex
*   data to be swapped to/from the C7x register layout for the reinterpret.
*******************************************************************************/
// Scalar base case
template <typename T>
struct complex_swapper
{
    using RES_T = T;
    static RES_T swap(const T &in) { return in; }
};
// Complex specialization
template <typename CE>
struct complex_swapper<ctype<CE> >
{
    using RES_T = ctype<CE>;
    static RES_T swap(const ctype<CE> &in)
    {
        RES_T res;
        res.r() = in.i();
        res.i() = in.r();
        return res;
    }
};
// Vector specialization
template <typename VE,
          size_t NELEM,
          VTYPE_KIND KIND>
struct complex_swapper<vtype<VE, NELEM, KIND> >
{
    using RES_T = vtype<VE, NELEM, VTYPE_KIND::DATA>;
    static RES_T swap(const vtype<VE, NELEM, KIND> &in) { return in; }
};
// Complex vector specialization
template <typename CE,
          size_t NELEM,
          VTYPE_KIND KIND>
struct complex_swapper<vtype<ctype<CE>, NELEM, KIND> >
{
    using RES_T = vtype<ctype<CE>, NELEM, VTYPE_KIND::DATA>;
    static RES_T swap(const vtype<ctype<CE>, NELEM, KIND> &in)
    {
        RES_T res;
        res.r() = in.i();
        res.i() = in.r();
        return res;
    }
};

/******************************************************************************
* is_vtype_or_elem -- Utility class to detect whether a type is a vtype or a
*   valid vtype element.
*******************************************************************************/
// Scalar base case
template <typename T>
struct is_vtype_or_elem
{
    static constexpr bool value = std::is_arithmetic<T>::value;
};
// Complex element case
template <typename CE>
struct is_vtype_or_elem<ctype<CE> >
{
    static constexpr bool value = is_vtype_or_elem<CE>::value;
};
// Vector case
template <typename VE,
          size_t NELEM,
          VTYPE_KIND KIND>
struct is_vtype_or_elem<vtype<VE, NELEM, KIND> >
{
    static constexpr bool value = is_vtype_or_elem<VE>::value;
};

/******************************************************************************
* scalar_rank_is_gt_vec_elem -- Utility class to determine whether a scalar has
*   greater rank than that of a vector element for the purposes of usual
*   arithmetic conversions, which differ for vectors compared to C semantics.
*******************************************************************************/
template<typename SCALAR_T,
         typename ELEM_T>
struct scalar_rank_is_gt_vec_elem
{
    static constexpr bool value = /* continued below */
        /*---------------------------------------------------------------------
        * For floating point types, a larger type has greater rank.
        *---------------------------------------------------------------------*/
           (std::is_floating_point<SCALAR_T>::value &&
            std::is_floating_point<ELEM_T>::value &&
            sizeof(SCALAR_T) > sizeof(ELEM_T))
        /*---------------------------------------------------------------------
        * A floating point type has greater rank than any integral type.
        *---------------------------------------------------------------------*/
        || (std::is_floating_point<SCALAR_T>::value &&
            std::is_integral<ELEM_T>::value)
        /*---------------------------------------------------------------------
        * For integral types:
        *---------------------------------------------------------------------*/
        || (std::is_integral<SCALAR_T>::value &&
            std::is_integral<ELEM_T>::value &&
            (
             /*----------------------------------------------------------------
             * A larger type has greater rank.
             *----------------------------------------------------------------*/
                sizeof(SCALAR_T) > sizeof(ELEM_T)
             /*----------------------------------------------------------------
             * An unsigned type has greater rank than a signed type of the same
             * size.
             *----------------------------------------------------------------*/
             || ( sizeof(SCALAR_T) == sizeof(ELEM_T) &&
                 !std::is_signed<SCALAR_T>::value &&
                  std::is_signed<ELEM_T>::value)));
};

/******************************************************************************
* can_widen_to_vec_of_elem -- Utility class to determine whether an input type
*   can be widened into a vector.
*******************************************************************************/
template<typename OTHER_T, typename ELEM_T>
struct can_widen_to_vec_of_elem
{
    /*-------------------------------------------------------------------------
    * Only C arithmetic types currently support widening. (Not complex or other
    * vectors.) For C arithmetic types, the answer is derived from comparing
    * ranks.
    *-------------------------------------------------------------------------*/
    static constexpr bool value =
                             std::is_arithmetic<OTHER_T>::value &&
                             std::is_arithmetic<ELEM_T>::value &&
                            !scalar_rank_is_gt_vec_elem<OTHER_T, ELEM_T>::value;

};

/******************************************************************************
* ACCESS_TYPE -- Enumeration of valid access types for use with
*   ref_array_builder.
******************************************************************************/
enum class ACCESS_TYPE { LO, HI, EVEN, ODD, REAL, IMAG };

// Create struct here so that we don't have run-time
// overhead from passing access type as parameter
template<ACCESS_TYPE ATYPE>
struct access_types { };

/******************************************************************************
* ref_array_builder -- Used to construct an array of reference wrappers to the
*   elements of another array. This is used in the process of generating a
*   vector that represents an access of another vector. The ordering of the
*   reference binding is chosen based on ACCESS_TYPE.
*
*   Contains a "result" member that can then be used to initialize another
*   std::array.
*
* ELEM_T -- The type that should be referenced in the resulting array. May be
*   const in the case references to const types are needed.
* NELEM -- The size of the resulting array.
*
* NOTE: The number of index values provided must equal the number of elements
*       in the *resulting* std::array.
*
* WHY: A std::array must be initialized immediately. This may be handled by
*      default initializers in the elements. However, std::reference_wrapper
*      does not have a default constructor. Therefore, there must be some way
*      to initialize a std::array of std::reference_wrapper immediately, before
*      even entering a constructor body or similar. This class provides that
*      capability.
*******************************************************************************/
template <typename ELEM_T,
          size_t NELEM>
class ref_array_builder
{
    using ELEM_NOCONST_T = typename std::remove_cv<ELEM_T>::type;

    /*-------------------------------------------------------------------------
    * Expected input data array types. These are used to abstract out const
    * versus non-const contexts. If the input data array is const, then only
    * the data array is distinctly const (not the elements, which inherit their
    * const status from the containing array). However, references created to
    * the elements MUST still be references-to-const.
    *
    * DATA_ARRAY_T -- The expected input data array types for LO/HI/EVEN/ODD
    *   ACCESS_TYPEs.
    *
    * CDATA_ARRAY_T -- The expected input data array types for REAL/IMAG
    *   ACCESS_TYPEs. In these cases, the resulting element type (ELEM_T) does
    *   not match the input element type (ctype<ELEM_T>).
    *-------------------------------------------------------------------------*/
    using DATA_ARRAY_T = typename std::conditional<
                                      std::is_const<ELEM_T>::value,
                                      const std::array<ELEM_NOCONST_T, NELEM*2>,
                                      std::array<ELEM_T, NELEM*2> >::type;

    using CDATA_ARRAY_T = typename std::conditional<
                                 std::is_const<ELEM_T>::value,
                                 const std::array<ctype<ELEM_NOCONST_T>, NELEM>,
                                 std::array<ctype<ELEM_T>, NELEM> >::type;

    /*-------------------------------------------------------------------------
    * Expected reference array types. These are used to abstract out const
    * versus non-const contexts. For the general case, there's no difference:
    * references-to-const in, references-to-const out. However, when extracting
    * components of const complex types, the input complex type will be complex,
    * not the component type. The references created in this case MUST still be
    * references-to-const.
    *
    * REF_ARRAY_T -- The expected input reference array types for LO/HI/EVEN/ODD
    *   ACCESS_TYPEs. No condition is needed in this case as the element type
    *   input is always the same as the element type output.
    *
    * CREF_ARRAY_T -- The expected input reference array types for REAL/IMAG
    *   ACCESS_TYPEs. In these cases, the resulting element type (ELEM_T) does
    *   not match the input element type (ctype<ELEM_T>).
    *-------------------------------------------------------------------------*/
    using REF_ARRAY_T = const std::array<std::reference_wrapper<ELEM_T>, NELEM*2>;
    using CREF_ARRAY_T = typename std::conditional<
          std::is_const<ELEM_T>::value,
          const std::array<std::reference_wrapper<const ctype<ELEM_NOCONST_T> >,
                           NELEM>,
          const std::array<std::reference_wrapper<ctype<ELEM_T> >,
                           NELEM> >::type;

/*-----------------------------------------------------------------------------
* Constructors
*-----------------------------------------------------------------------------*/
public:
    /*-------------------------------------------------------------------------
    * Constructors used during a .lo() access.
    *-------------------------------------------------------------------------*/
    /* Data array to reference array */
    template<size_t... Is>
    ref_array_builder(DATA_ARRAY_T &data,
                      access_types<ACCESS_TYPE::LO>,
                      std::index_sequence<Is...>) :
        result({(data[Is])...})
    {}

    /* Reference array to reference array */
    template<size_t... Is>
    ref_array_builder(REF_ARRAY_T &refs,
                      access_types<ACCESS_TYPE::LO>,
                      std::index_sequence<Is...>) :
        result({(refs[Is])...})
    {}

    /*-------------------------------------------------------------------------
    * Constructors used during a .hi() access.
    *-------------------------------------------------------------------------*/
    /* Data array to reference array */
    template<size_t... Is>
    ref_array_builder(DATA_ARRAY_T &data,
                      access_types<ACCESS_TYPE::HI>,
                      std::index_sequence<Is...>) :
        result({(data[Is + NELEM])...})
    {}

    /* Reference array to reference array */
    template<size_t... Is>
    ref_array_builder(REF_ARRAY_T &refs,
                      access_types<ACCESS_TYPE::HI>,
                      std::index_sequence<Is...>) :
        result({(refs[Is + NELEM])...})
    {}

    /*-------------------------------------------------------------------------
    * Constructors used during a .even() access.
    *-------------------------------------------------------------------------*/
    /* Data array to reference array */
    template<size_t... Is>
    ref_array_builder(DATA_ARRAY_T &data,
                      access_types<ACCESS_TYPE::EVEN>,
                      std::index_sequence<Is...>) :
        result({(data[2*Is])...})
    {}

    /* Reference array to reference array */
    template<size_t... Is>
    ref_array_builder(REF_ARRAY_T &refs,
                      access_types<ACCESS_TYPE::EVEN>,
                      std::index_sequence<Is...>) :
        result({(refs[2*Is])...})
    {}

    /*-------------------------------------------------------------------------
    * Constructors used during a .odd() access.
    *-------------------------------------------------------------------------*/
    /* Data array to reference array */
    template<size_t... Is>
    ref_array_builder(DATA_ARRAY_T &data,
                      access_types<ACCESS_TYPE::ODD>,
                      std::index_sequence<Is...>) :
        result({(data[2*Is + 1])...})
    {}

    /* Reference array to reference array */
    template<size_t... Is>
    ref_array_builder(REF_ARRAY_T &refs,
                      access_types<ACCESS_TYPE::ODD>,
                      std::index_sequence<Is...>) :
        result({(refs[2*Is + 1])...})
    {}


    /*-------------------------------------------------------------------------
    * Constructors used during a .r() access.
    *-------------------------------------------------------------------------*/
    /* Data array to reference array */
    template<size_t... Is>
    ref_array_builder(CDATA_ARRAY_T &data,
                      access_types<ACCESS_TYPE::REAL>,
                      std::index_sequence<Is...>) :
        result({(data[Is].r())...})
    {}

    /* Reference array to reference array */
    template<size_t... Is>
    ref_array_builder(CREF_ARRAY_T &refs,
                      access_types<ACCESS_TYPE::REAL>,
                      std::index_sequence<Is...>) :
        result({(refs[Is].get().r())...})
    {}

    /*-------------------------------------------------------------------------
    * Constructors used during a .i() access.
    *-------------------------------------------------------------------------*/
    /* Data array to reference array */
    template<size_t... Is>
    ref_array_builder(CDATA_ARRAY_T &data,
                      access_types<ACCESS_TYPE::IMAG>,
                      std::index_sequence<Is...>) :
        result({(data[Is].i())...})
    {}

    /* Reference array to reference array */
    template<size_t... Is>
    ref_array_builder(CREF_ARRAY_T &refs,
                      access_types<ACCESS_TYPE::IMAG>,
                      std::index_sequence<Is...>) :
        result({(refs[Is].get().i())...})
    {}

/*-----------------------------------------------------------------------------
* Data
*-----------------------------------------------------------------------------*/
public:
    // Reference wrapper array member
    std::array<std::reference_wrapper<ELEM_T>, NELEM> result;
};

/******************************************************************************
* cond_value -- A utility template to implement the ternary operator for values.
*******************************************************************************/
// True (default)
template<bool B, int T, int F>
struct cond_value { static constexpr int value = T; };
// False specialization
template<int T, int F>
struct cond_value<false, T, F> { static constexpr int value = F; };

/******************************************************************************
* comp_type -- A utility template to find fundamental datatype that a vector or
*   complex uses.
*******************************************************************************/
template <typename TYPE, typename Enable = void>
struct comp_type;
// Arithmetic specialization
template <typename TYPE>
struct comp_type<TYPE,
                 std::enable_if_t<std::is_arithmetic<TYPE>::value> >
{
    using type = TYPE;
};
// Complex specialization
template <typename TYPE>
struct comp_type<TYPE,
                 std::enable_if_t<!std::is_arithmetic<TYPE>::value> >
{
    using type = typename comp_type<typename TYPE::ELEM_TYPE>::type;
};

/******************************************************************************
* vtype_array_member -- Struct used to allow for TI extension .s[k] syntax.
*   This is the only member in a vtype that is allowed to consume space.
*
* NOTE: This implements both arrays of data and arrays of references, with
*       slightly different specializations.
*
* WHY: Why not just put a std::array or plain C array in vtype?
*      std::reference_wrapper doesn't behave just like a reference. Most
*      importantly, you can't assign through the contained reference without
*      using get(). This class hides the members of its contained array behind
*      its own subscript operator, which hides the get() operation if needed.
******************************************************************************/
/* Data array specialization */
template<typename ELEM_T, size_t NELEM>
struct vtype_array_member
{
    const ELEM_T& operator[](size_t index) const
    {
        return raw_array[index];
    }

    ELEM_T& operator[](size_t index)
    {
        return raw_array[index];
    }

    std::array<ELEM_T, NELEM> raw_array;
};

/* Reference array specialization */
template<typename ELEM_T, size_t NELEM>
struct vtype_array_member<std::reference_wrapper<ELEM_T>, NELEM>
{
    /*-------------------------------------------------------------------------
    * Array index operator -- used to retrieve data from a reference wrapper at
    * an index. (Hides the get() operation.)
    *-------------------------------------------------------------------------*/
    ELEM_T& operator[](size_t index) const
    {
        return raw_array[index].get();
    }

    /*-------------------------------------------------------------------------
    * Constructor -- Initialize reference wrapper array raw_array using passed
    * in array of reference wrappers.
    *-------------------------------------------------------------------------*/
    vtype_array_member(std::array<std::reference_wrapper<ELEM_T>, NELEM> &refs):
           raw_array(refs)
    {}

    std::array<std::reference_wrapper<ELEM_T>, NELEM> raw_array;
};


/******************************************************************************
* vtype -- the high-level abstraction for vector types. It is instantiated with
*   an element type and a number of elements. The element types should be those
*   found in stdint so that bit widths are guaranteed.
*
*   e.g.: char64 = vtype<int8_t, 64, VTYPE_KIND::DATA>
*
* NOTE: For VTYPE_KIND::DATA, vtype is trivial, which allows it to be used with
*       memcpy() and memset() such as in the implementation of _AS_CONV. For
*       VTYPE_KIND::REF and VTYPE_KIND::CONST_REF, vtype must NOT be trivially
*       copyable (and therefore not trivial) because assignment has side
*       effects.
*******************************************************************************/
template <typename ELEM_T,
          size_t NELEM,
          VTYPE_KIND KIND>
class vtype
{
#if defined(__clang__)
#pragma clang diagnostic push
/* Deprecated in the C++ standard means normative for current edition, but is a
 * candidate for removal in a future revision.
 * The current implementation *relies* on the deprecated behavior of implicitly
 * declared copy assignment. See discussion at operator=().
 */
#pragma clang diagnostic ignored "-Wdeprecated-copy-with-user-provided-copy"
#endif
/*-----------------------------------------------------------------------------
* General information members
*-----------------------------------------------------------------------------*/
public:
    /*-------------------------------------------------------------------------
    * ELEM_TYPE -- The element type of the vector. (Saved here to be able to
    *   query the element type here outside of the context of the class body.)
    *-------------------------------------------------------------------------*/
    using ELEM_TYPE = ELEM_T;

    /*-------------------------------------------------------------------------
    * REAL_ELEM_TYPE -- The type of the data that will actually be stored in
    *   the vector. Driven by the VTYPE_KIND. If DATA, data is stored.
    *   Otherwise, this vector is an access and references are stored.
    *-------------------------------------------------------------------------*/
    using REAL_ELEM_TYPE = typename std::conditional<KIND == VTYPE_KIND::DATA,
                                                     ELEM_TYPE,
                           typename std::conditional<KIND == VTYPE_KIND::REF,
                                                     std::reference_wrapper<ELEM_TYPE>,
                           typename std::conditional<KIND == VTYPE_KIND::CONST_REF,
                                                     std::reference_wrapper<const ELEM_TYPE>, void>::type>::type>::type;

    /*-------------------------------------------------------------------------
    * LOG_RES_TYPE -- The logical result type is the type that is returned from
    *   logical style operations such as &&, ||, ==, etc.
    *-------------------------------------------------------------------------*/
    using LOG_RES_TYPE = vtype<typename std::conditional<sizeof(ELEM_TYPE) == 1,
                                                         int8_t,
                               typename std::conditional<sizeof(ELEM_TYPE) == 2,
                                                         int16_t,
                               typename std::conditional<sizeof(ELEM_TYPE) == 4,
                                                         int32_t,
                               typename std::conditional<sizeof(ELEM_TYPE) == 8,
                                                         int64_t, void>::type>::type>::type>::type,NELEM, VTYPE_KIND::DATA>;

    /*-------------------------------------------------------------------------
    * COMP_TYPE -- The component type of the vector. For complex vectors, this
    *   is the component type of the complex element. Otherwise, it is the same
    *   as the element type of the vector. For example, vtype<int> has a
    *   component type of int. vtype<ctype<int> > also has a component type of
    *   int.
    *-------------------------------------------------------------------------*/
    using COMP_TYPE = typename comp_type<ELEM_TYPE>::type;

    /*-------------------------------------------------------------------------
    * NUM_ELEM -- The number of elements in the vector.
    * PADDED_NUM_ELEM -- The number of elements in the vector, including
    *   potentially elements for padding. The key case is that 3 element vectors
    *   are really 4 element vectors where the last element is a don't-care.
    *-------------------------------------------------------------------------*/
    static constexpr size_t NUM_ELEM = NELEM;
    static constexpr size_t PADDED_NUM_ELEM = cond_value<NELEM == 3, 4, NELEM>::value;

/*-----------------------------------------------------------------------------
* Constructors and construction related data types
*-----------------------------------------------------------------------------*/
public:
    /*-------------------------------------------------------------------------
    * Vector literal syntax constructor, see init_helper for more.
    * e.g.: int4(int2(1, 2), 3, 4)
    *-------------------------------------------------------------------------*/
    template<class INIT0,
             VTYPE_KIND VTYPE_KIND_DUMMY = KIND,
             std::enable_if_t<VTYPE_KIND_DUMMY == VTYPE_KIND::DATA, int> = 0,
             class ...INITS>
    explicit vtype(const INIT0 &init0, const INITS &...inits)
    {
        init_helper<0>(init0, inits...);
    }

    /*-------------------------------------------------------------------------
    * Scalar convert and widen constructor
    * e.g.: int2 int2_a = int_b;
    * NOTE: This constructor and the explicit constructor above for vector
    *       literal syntax can handle many of the same cases. However, because
    *       the above constructor uses a parameter pack template, this
    *       constructor will take precedence due to being more precise. However,
    *       the explicit constructor is more accepting to match cl7x. As such,
    *       we have the following cases:
    *       1. Implicit widen of lower or equal rank scalar:
    *          E.g. int2 int2_a = int_b;
    *          This constructor is used because the conversion is implicit.
    *       2. Implicit widen from higher rank scalar:
    *          E.g. int2 int2_a = long_b;
    *          Compilation error due to illegal implict widen. (Matches cl7x.)
    *       3. Explicit init from lower or equal rank scalar:
    *          E.g. int2 int2_a = int2(int_b);
    *          This constructor is used because it is more precise, although
    *          either constructor implements the operation.
    *       4. Explicit init from higher rank scalar:
    *          E.g. int2 int2_a = int2(long_b);
    *          The explicit constructor is used because this constructor fails
    *          to substitute due to the enable_if_t. (Matches cl7x.)
    *-------------------------------------------------------------------------*/
    template<typename SCALAR_T,
             VTYPE_KIND VTYPE_KIND_DUMMY = KIND,
             std::enable_if_t<VTYPE_KIND_DUMMY == VTYPE_KIND::DATA &&
                              can_widen_to_vec_of_elem<SCALAR_T, ELEM_TYPE>::value, int> = 0>
    vtype(SCALAR_T rhs)
    {
        for (size_t i = 0; i < NELEM; i++)
            (*this).s[i] = (ELEM_T)rhs;
    }

    /*-------------------------------------------------------------------------
    * Conversion constructor to VTYPE_KIND::DATA
    * e.g.: int2 int2_vec_a = int4_vec_b.even();
    *-------------------------------------------------------------------------*/
    template<VTYPE_KIND OTHER_KIND,
             VTYPE_KIND VTYPE_KIND_DUMMY = KIND,
             std::enable_if_t<VTYPE_KIND_DUMMY == VTYPE_KIND::DATA &&
                              VTYPE_KIND_DUMMY != OTHER_KIND, int> = 0 >
    vtype(const vtype<ELEM_TYPE, NELEM, OTHER_KIND> &v)
    {
        for(size_t i = 0 ; i < NELEM; i++)
            (*this).s[i] = v.s[i];
    }

    /*-------------------------------------------------------------------------
    * Copy constructor -- defaulted, trivially copyable
    * e.g.: int2 int2_a = int2_b;
    * NOTE: REF and CONST_REF kinds should not be variables in reasonable code.
    * NOTE: Implicit to avoid clang warning -Wdeprecated-copy.
    *-------------------------------------------------------------------------*/
    /* vtype(const vtype<ELEM_TYPE, NELEM, KIND> &rhs) = default; */

    /*-------------------------------------------------------------------------
    * Construct an access vector from an array of references. (For
    * implementation use when generating vector accesses.)
    *-------------------------------------------------------------------------*/
    template<VTYPE_KIND VTYPE_KIND_DUMMY = KIND,
             std::enable_if_t<VTYPE_KIND_DUMMY != VTYPE_KIND::DATA, int> = 0 >
    explicit vtype(std::array<REAL_ELEM_TYPE, NELEM> &refs): s(refs)
    {}

    /*-------------------------------------------------------------------------
    * Default constructor -- defaulted, trivially constructible
    * e.g.: int2 tmp;
    *-------------------------------------------------------------------------*/
    vtype() = default;

/*-----------------------------------------------------------------------------
* Recursive instantiations
*-----------------------------------------------------------------------------*/
private:
    /*-------------------------------------------------------------------------
    * The next initializer in the pack is a singular element
    * e.g.: (int4)(... 4, ...)
    * Add it to the current index and recurse.
    *-------------------------------------------------------------------------*/
    template<size_t curr_idx,
             class ...INITS>
    void init_helper(const ELEM_TYPE &next, const INITS &...inits)
    {
        static_assert(curr_idx < NELEM, "Illegal vector init, too many");

        (*this).s[curr_idx] = next;

        init_helper<curr_idx + 1>(inits...);
    }

    /*-------------------------------------------------------------------------
    * The next two initializers in the pack represent a single complex element
    * e.g.: (cint4)(... 4, 5, ...)
    * Add it to the current index and recurse.
    *-------------------------------------------------------------------------*/
    template<size_t curr_idx,
             typename DUMMY = ELEM_TYPE,
             class ...INITS,
             enable_if_cmplx_t<DUMMY, int> = 0>
    void init_helper(const typename DUMMY::ELEM_TYPE &next,
                     const typename DUMMY::ELEM_TYPE &next1,
                     const INITS &...inits)
    {
        static_assert(curr_idx < NELEM, "Illegal vector init, too many");

        ELEM_TYPE temp = ELEM_TYPE(next, next1);

        (*this).s[curr_idx] = temp;

        init_helper<curr_idx + 1>(inits...);
    }

    /*-------------------------------------------------------------------------
    * The next initializer is a vector
    * e.g.: (int8)(... int4(...), ...)
    * Add each element of the vector and recurse.
    *-------------------------------------------------------------------------*/
    template<size_t curr_idx,
             typename OELEM_T,
             size_t OTHER_NELEM,
             VTYPE_KIND OTHER_KIND,
             class ...INITS>
    void init_helper(const vtype<OELEM_T, OTHER_NELEM, OTHER_KIND> &next,
                     const INITS &...inits)
    {
        static_assert(curr_idx + OTHER_NELEM - 1 < NELEM,
                      "Illegal vector init, too many");

        for (size_t i = 0; i < OTHER_NELEM; i++)
            (*this).s[i + curr_idx] = next.s[i];

        init_helper<curr_idx + OTHER_NELEM>(inits...);
    }

    /*-------------------------------------------------------------------------
    * The only initializer is a vreg_t
    * Convert the vreg_t into its target vector representation.
    *-------------------------------------------------------------------------*/
    template <size_t curr_idx>
    void init_helper(const vreg_t &v)
    {
        static_assert(curr_idx == 0, "Accessor created illegal vector init.");
        init_from_vreg_t<vtype<ELEM_TYPE, NELEM, VTYPE_KIND::DATA>, ELEM_TYPE, NELEM>(v, *this);
    }

    /*-------------------------------------------------------------------------
    * Termination
    * When we've run out of things to process, ensure we've packed the full
    * vector, then we're done.
    *-------------------------------------------------------------------------*/
    template <size_t curr_idx>
    void init_helper()
    {
        static_assert(curr_idx == NELEM || curr_idx == 1,
                      "Illegal vector init, too few");

        // Vector literal duplication constructor
        // e.g.: int4(1)
        if (curr_idx == 1)
            for(size_t i = 0; i < NELEM; i++)
                (*this).s[i] = (*this).s[0];
    }

/*-----------------------------------------------------------------------------
* Operators
*-----------------------------------------------------------------------------*/
public:
    /*-------------------------------------------------------------------------
    * Assignment to non-data vector from data vector (not copy assignment)
    * e.g.: int8_vec_a.lo() = int4_vec_b;
    *-------------------------------------------------------------------------*/
    template<VTYPE_KIND VTYPE_KIND_DUMMY = KIND,
             std::enable_if_t<VTYPE_KIND_DUMMY != VTYPE_KIND::DATA, int> = 0 >
    vtype &operator=(const vtype<ELEM_TYPE, NELEM, VTYPE_KIND::DATA> &rhs)
    {
        for (size_t i = 0; i < NELEM; i++)
            (*this).s[i] = rhs.s[i];
        return *this;
    }

    /*-------------------------------------------------------------------------
    * Assignment from data vector to data vector (copy assignment, trivially
    * copyable)
    * - vtype<x, y, DATA> &operator=(const vtype<x, y, DATA> &rhs)
    * - NOTE: Not declared default to get the implicit definition without
    *         conflicting with the below definitions.
    * - WHY: We need the default copy assignment for VTYPE_KIND::DATA for it to
    *        be considered trivially copyable as well as trivial. Usually, you
    *        can just define the operator with "= default" for explicit
    *        representation of this behavior. However, for VTYPE_KIND::REF and
    *        VTYPE_KIND::CONST_REF, we need non-default assignment operators
    *        (below) so that we don't just copy the references. Additionally, a
    *        copy assignment cannot be templated and still be considered the
    *        copy assignment operator. Beyond that, "= default" cannot be used
    *        with a template. This puts us between the "rock" of we sometimes
    *        have special copy assignments which would conflict with a default
    *        definition and the "hard place" of we can't template a definition
    *        for VTYPE_KIND::DATA. However, if we define *nothing*, once the
    *        template class is expanded, the compiler will generate a default
    *        definition for VTYPE_KIND::DATA (because no copy assignment
    *        operator exists) but not for VTYPE_KIND::REF and
    *        VTYPE_KIND::CONST_REF (because a copy assignment operator does
    *        exist). This is a hack and the LACK OF any code here is meaningful.
    * e.g.: int4_vec_a = const_int8_vec_b.lo();
    *-------------------------------------------------------------------------*/

    /*-------------------------------------------------------------------------
    * Assignment from reference vector (sometimes copy assignment)
    * - vtype<x, y, DATA> &operator=(const vtype<x, y, REF> &rhs)
    *   - Converting assign (not copy assignment)
    * - vtype<x, y, REF> &operator=(const vtype<x, y, REF> &rhs)
    *   - Copy assignment. (Not trivially copyable)
    *   - Disallows implicit copy and move assignment/constructor for REF.
    *     - This prevents copying/assiging reference_wrapper instead of writing.
    * - vtype<x, y, CONST_REF> &operator=(const vtype<x, y, REF> &rhs)
    *   - Converting assign (not copy assignment)
    *   - NOTE: CONST_REF is not assignable in general due to const.
    * e.g.: int4_vec_a = int8_vec_b.lo();
    *-------------------------------------------------------------------------*/
    vtype &operator=(const vtype<ELEM_TYPE, NELEM, VTYPE_KIND::REF> &rhs)
    {
        for (size_t i = 0; i < NELEM; i++)
            (*this).s[i] = rhs.s[i];
        return *this;
    }

    /*-------------------------------------------------------------------------
    * Assignment from const reference vector (sometimes copy assignment)
    * - vtype<x, y, DATA> &operator=(const vtype<x, y, CONST_REF> &rhs)
    *   - Converting assign (not copy assignment)
    * - vtype<x, y, REF> &operator=(const vtype<x, y, CONST_REF> &rhs)
    *   - Converting assign (not copy assignment)
    * - vtype<x, y, CONST_REF> &operator=(const vtype<x, y, CONST_REF> &rhs)
    *   - Copy assignment. (Not trivially copyable)
    *   - Disallows implicit copy and move assignment/constructor for CONST_REF.
    *     - This prevents copying/assiging reference_wrapper instead of writing.
    *     - NOTE: CONST_REF is not assignable in general due to const.
    * e.g.: int4_vec_a = const_int8_vec_b.lo();
    *-------------------------------------------------------------------------*/
    vtype &operator=(const vtype<ELEM_TYPE, NELEM, VTYPE_KIND::CONST_REF> &rhs)
    {
        for (size_t i = 0; i < NELEM; i++)
            (*this).s[i] = rhs.s[i];
        return *this;
    }

    /*-------------------------------------------------------------------------
    * Cast to vreg_t
    *-------------------------------------------------------------------------*/
    operator vreg_t() const
    {
        return convert_to_vreg_t<vtype<ELEM_TYPE, NELEM, KIND>, ELEM_TYPE, NELEM>(*this);
    }

    /*-------------------------------------------------------------------------
    * Unary minus
    *-------------------------------------------------------------------------*/
    vtype<ELEM_TYPE, NELEM, VTYPE_KIND::DATA> operator-() const
    {
        static_assert(!std::is_same<ELEM_T, bool>::value,
                      "Error: bool vector unary-minus is not supported");
        vtype<ELEM_TYPE,NELEM, VTYPE_KIND::DATA> res;
        for (size_t i = 0; i < NELEM; i++)
            res.s[i] = -((*this).s[i]);
        return res;
    }

    /*-------------------------------------------------------------------------
    * Unary plus
    *-------------------------------------------------------------------------*/
    vtype<ELEM_TYPE, NELEM, VTYPE_KIND::DATA> operator+() const
    {
        static_assert(!std::is_same<ELEM_T, bool>::value,
                      "Error: bool vector unary-plus is not supported");
        vtype<ELEM_TYPE,NELEM, VTYPE_KIND::DATA> res;
        for (size_t i = 0; i < NELEM; i++)
            res.s[i] = +((*this).s[i]);
        return res;
    }

    /*-------------------------------------------------------------------------
    * Pre-increment
    *-------------------------------------------------------------------------*/
    vtype &operator++()
    {
        static_assert(!std::is_same<ELEM_TYPE, float>::value &&
                      !std::is_same<ELEM_TYPE, double>::value &&
                      !std::is_same<ELEM_T, bool>::value,
                      "Error: float, double, and bool vector pre-increment is not supported");
        for (size_t i = 0; i < NELEM; i++)
            s[i]++;
        return *this;
    }

    /*-------------------------------------------------------------------------
    * Post-increment
    *-------------------------------------------------------------------------*/
    vtype<ELEM_TYPE, NELEM, VTYPE_KIND::DATA> operator++(int)
    {
        static_assert(!std::is_same<ELEM_TYPE, float>::value &&
                      !std::is_same<ELEM_TYPE, double>::value &&
                      !std::is_same<ELEM_T, bool>::value,
                      "Error: float, double, and bool vector post-increment is not supported");
        vtype<ELEM_TYPE, NELEM, VTYPE_KIND::DATA> copy = *this;
        ++*this;
        return copy;
    }

    /*-------------------------------------------------------------------------
    * Pre-decrement
    *-------------------------------------------------------------------------*/
    vtype &operator--()
    {
        static_assert(!std::is_same<ELEM_TYPE, float>::value &&
                      !std::is_same<ELEM_TYPE, double>::value &&
                      !std::is_same<ELEM_T, bool>::value,
                      "Error: float, double, and bool vector pre-decrement is not supported");
        for (size_t i = 0; i < NELEM; i++)
            s[i]--;
        return *this;
    }

    /*-------------------------------------------------------------------------
    * Post-decrement
    *-------------------------------------------------------------------------*/
    vtype<ELEM_TYPE, NELEM, VTYPE_KIND::DATA> operator--(int)
    {
        static_assert(!std::is_same<ELEM_TYPE, float>::value &&
                      !std::is_same<ELEM_TYPE, double>::value,
                      "Error: float and double vector post-decrement is not supported");
        vtype<ELEM_TYPE, NELEM, VTYPE_KIND::DATA> copy = *this;
        --*this;
        return copy;
    }

    /*-------------------------------------------------------------------------
    * Bitwise not
    *-------------------------------------------------------------------------*/
    vtype<ELEM_TYPE, NELEM, VTYPE_KIND::DATA> operator~() const
    {
        static_assert(!std::is_same<ELEM_TYPE, float>::value &&
                      !std::is_same<ELEM_TYPE, double>::value &&
                      !std::is_same<ELEM_T, bool>::value,
                      "Error: float, double, and bool vector ~ is not supported");
        vtype<ELEM_TYPE, NELEM, VTYPE_KIND::DATA> res;
        for (size_t i = 0; i < NELEM; i++)
            res.s[i] = ~s[i];
        return res;
    }

    /*-------------------------------------------------------------------------
    * Plus assign with a vector
    *-------------------------------------------------------------------------*/
    vtype &operator+=(const vtype<ELEM_TYPE, NELEM, VTYPE_KIND::DATA> &rhs)
    {
        static_assert(!std::is_same<ELEM_T, bool>::value,
                      "Error: bool vector += is not supported");
        for (size_t i = 0; i < NELEM; i++)
            (*this).s[i] += rhs.s[i];
        return *this;
    }

    /*-------------------------------------------------------------------------
    * Minus assign with a vector
    *-------------------------------------------------------------------------*/
    vtype &operator-=(const vtype<ELEM_TYPE, NELEM, VTYPE_KIND::DATA> &rhs)
    {
        static_assert(!std::is_same<ELEM_T, bool>::value,
                      "Error: bool vector -= is not supported");
        for (size_t i = 0; i < NELEM; i++)
                (*this).s[i] -= rhs.s[i];
        return *this;
    }

    /*-------------------------------------------------------------------------
    * Multiply assign with a vector
    *-------------------------------------------------------------------------*/
    vtype &operator*=(const vtype<ELEM_TYPE, NELEM, VTYPE_KIND::DATA> &rhs)
    {
        static_assert(!std::is_same<ELEM_T, bool>::value,
                      "Error: bool vector *= is not supported");
        for (size_t i = 0; i < NELEM; i++)
                (*this).s[i] *= rhs.s[i];
        return *this;
    }

    /*-------------------------------------------------------------------------
    * Divide assign with a vector
    *-------------------------------------------------------------------------*/
    vtype &operator/=(const vtype<ELEM_TYPE, NELEM, VTYPE_KIND::DATA> &rhs)
    {
        static_assert(!std::is_same<ELEM_T, bool>::value,
                      "Error: bool vector /= is not supported");
        for (size_t i = 0; i < NELEM; i++)
                (*this).s[i] /= rhs.s[i];
        return *this;
    }

    /*-------------------------------------------------------------------------
    * Modulus assign with a vector
    *-------------------------------------------------------------------------*/
    vtype &operator%=(const vtype<ELEM_TYPE, NELEM, VTYPE_KIND::DATA> &rhs)
    {
        static_assert(!std::is_same<ELEM_TYPE, float>::value &&
                      !std::is_same<ELEM_TYPE, double>::value &&
                      !std::is_same<ELEM_T, bool>::value,
                      "Error: float, double, and bool vector %= is not supported");

        for (size_t i = 0; i < NELEM; i++)
            (*this).s[i] %= rhs.s[i];
        return *this;
    }

    /*-------------------------------------------------------------------------
    * Right shift assign with a vector
    *-------------------------------------------------------------------------*/
    vtype &operator>>=(const vtype<ELEM_TYPE, NELEM, VTYPE_KIND::DATA> &rhs)
    {
        static_assert(!std::is_same<ELEM_TYPE, float>::value &&
                      !std::is_same<ELEM_TYPE, double>::value &&
                      !std::is_same<ELEM_T, bool>::value,
                      "Error: float, double, and bool vector >>= not supported");

        for (size_t i = 0; i < NELEM; i++)
            (*this).s[i] >>= rhs.s[i];
        return *this;
    }

    /*-------------------------------------------------------------------------
    * Left shift assign with a vector
    *-------------------------------------------------------------------------*/
    vtype &operator<<=(const vtype<ELEM_TYPE, NELEM, VTYPE_KIND::DATA> &rhs)
    {
        static_assert(!std::is_same<ELEM_TYPE, float>::value &&
                      !std::is_same<ELEM_TYPE, double>::value &&
                      !std::is_same<ELEM_T, bool>::value,
                      "Error: float, double, and bool vector <<= is not supported");

        for (size_t i = 0; i < NELEM; i++)
            (*this).s[i] <<= rhs.s[i];
        return *this;
    }

    /*-------------------------------------------------------------------------
    * Bitwise and assign with a vector
    *-------------------------------------------------------------------------*/
    vtype &operator&=(const vtype<ELEM_TYPE, NELEM, VTYPE_KIND::DATA> &rhs)
    {
        static_assert(!std::is_same<ELEM_TYPE, float>::value &&
                      !std::is_same<ELEM_TYPE, double>::value &&
                      !std::is_same<ELEM_T, bool>::value,
                      "Error: float, double, and bool vector &= is not supported");

        for (size_t i = 0; i < NELEM; i++)
            (*this).s[i] &= rhs.s[i];
        return *this;
    }

    /*-------------------------------------------------------------------------
    * Bitwise or assign with a vector
    *-------------------------------------------------------------------------*/
    vtype &operator|=(const vtype<ELEM_TYPE, NELEM, VTYPE_KIND::DATA> &rhs)
    {
        static_assert(!std::is_same<ELEM_TYPE, float>::value &&
                      !std::is_same<ELEM_TYPE, double>::value &&
                      !std::is_same<ELEM_T, bool>::value,
                      "Error: float, double, and bool vector |= is not supported");

        for (size_t i = 0; i < NELEM; i++)
            (*this).s[i] |= rhs.s[i];
        return *this;
    }

    /*-------------------------------------------------------------------------
    * Bitwise xor assign with a vector
    *-------------------------------------------------------------------------*/
    vtype &operator^=(const vtype<ELEM_TYPE, NELEM, VTYPE_KIND::DATA> &rhs)
    {
        static_assert(!std::is_same<ELEM_TYPE, float>::value &&
                      !std::is_same<ELEM_TYPE, double>::value &&
                      !std::is_same<ELEM_T, bool>::value,
                      "Error: float, double, and bool vector ^= is not supported");

        for (size_t i = 0; i < NELEM; i++)
            (*this).s[i] ^= rhs.s[i];
        return *this;
    }

/*-----------------------------------------------------------------------------
* Vector function-style swizzle accessors
* e.g. vec.lo()
*
* For each allowed accessor, a case must handle whether the containing vector
* is const or non-const. If the containing vector is const, so is the result
* if the access. Furthermore, the result of the access will contain
* references-to-const.
*
* NOTE: Returned values must be const to ensure that a potential subaccess will
*       also use a const overload. (Look for const RV_TYPE, below.)
*-----------------------------------------------------------------------------*/
public:
    /*-------------------------------------------------------------------------
    * Scalar accessors. .s0() and similar. Always result in a scalar.
    *-------------------------------------------------------------------------*/
#define S_ACCESS(name,idx) \
    template <size_t V_SIZE = NELEM, \
              std::enable_if_t<idx < V_SIZE, int> = 0 > \
    ELEM_TYPE & name() { return s[idx]; } \
    \
    template <size_t V_SIZE = NELEM, \
              std::enable_if_t<idx < V_SIZE, int> = 0 > \
    const ELEM_TYPE & name() const { return s[idx]; } \

    S_ACCESS(s0,0)
    S_ACCESS(s1,1)
    S_ACCESS(s2,2)
    S_ACCESS(s3,3)
    S_ACCESS(s4,4)
    S_ACCESS(s5,5)
    S_ACCESS(s6,6)
    S_ACCESS(s7,7)
    S_ACCESS(s8,8)
    S_ACCESS(s9,9)
    S_ACCESS(sa,10)
    S_ACCESS(sb,11)
    S_ACCESS(sc,12)
    S_ACCESS(sd,13)
    S_ACCESS(se,14)
    S_ACCESS(sf,15)

    S_ACCESS(x,0)
    S_ACCESS(y,1)
    S_ACCESS(z,2)
    S_ACCESS(w,3)
#undef S_ACCESS

    /*-------------------------------------------------------------------------
    * Vector accessors. .lo() and similar. May result in a scalar or a vector,
    * but always with a half size result. If there is no true "half size result"
    * as with a 3 element vector, then the operation is illegal.
    *-------------------------------------------------------------------------*/
    /* .lo(), vector result */
    template <size_t RV_SIZE = NELEM / 2,
              typename RV_TYPE = vtype<ELEM_TYPE, RV_SIZE, VTYPE_KIND::CONST_REF>,
              std::enable_if_t<RV_SIZE != 1 && RV_SIZE*2 == NELEM, int> = 0>
    const RV_TYPE lo() const
    {
        ref_array_builder<const ELEM_TYPE, RV_SIZE> refs(
                                           s.raw_array,
                                           access_types<ACCESS_TYPE::LO>(),
                                           std::make_index_sequence<RV_SIZE>());
        return RV_TYPE(refs.result);
    }

    template <size_t RV_SIZE = NELEM / 2,
              typename RV_TYPE = vtype<ELEM_TYPE, RV_SIZE, VTYPE_KIND::REF>,
              std::enable_if_t<RV_SIZE != 1 && RV_SIZE*2 == NELEM, int> = 0>
    RV_TYPE lo()
    {
        ref_array_builder<ELEM_TYPE, RV_SIZE> refs(
                                           s.raw_array,
                                           access_types<ACCESS_TYPE::LO>(),
                                           std::make_index_sequence<RV_SIZE>());
        return RV_TYPE(refs.result);
    }

    /* .lo(), scalar result */
    template <size_t RV_SIZE = NELEM / 2,
              std::enable_if_t<RV_SIZE == 1 && RV_SIZE*2 == NELEM, int> = 0>
    const ELEM_TYPE &lo() const
    {
        return s[0];
    }

    template <size_t RV_SIZE = NELEM / 2,
              std::enable_if_t<RV_SIZE == 1 && RV_SIZE*2 == NELEM, int> = 0>
    ELEM_TYPE &lo()
    {
        return s[0];
    }

    /* .hi(), vector result */
    template <size_t RV_SIZE = NELEM / 2,
              typename RV_TYPE = vtype<ELEM_TYPE, RV_SIZE, VTYPE_KIND::CONST_REF>,
              std::enable_if_t<RV_SIZE != 1 && RV_SIZE*2 == NELEM, int> = 0>
    const RV_TYPE hi() const
    {
        ref_array_builder<const ELEM_TYPE, RV_SIZE> refs(
                                           s.raw_array,
                                           access_types<ACCESS_TYPE::HI>(),
                                           std::make_index_sequence<RV_SIZE>());
        return RV_TYPE(refs.result);
    }

    template <size_t RV_SIZE = NELEM / 2,
              typename RV_TYPE = vtype<ELEM_TYPE, RV_SIZE, VTYPE_KIND::REF>,
              std::enable_if_t<RV_SIZE != 1 && RV_SIZE*2 == NELEM, int> = 0>
    RV_TYPE hi()
    {
        ref_array_builder<ELEM_TYPE, RV_SIZE> refs(
                                           s.raw_array,
                                           access_types<ACCESS_TYPE::HI>(),
                                           std::make_index_sequence<RV_SIZE>());
        return RV_TYPE(refs.result);
    }

    /* .hi(), scalar result */
    template <size_t RV_SIZE = NELEM / 2,
              std::enable_if_t<RV_SIZE == 1 && RV_SIZE*2 == NELEM, int> = 0>
    const ELEM_TYPE &hi() const
    {
        return s[1];
    }

    template <size_t RV_SIZE = NELEM / 2,
              std::enable_if_t<RV_SIZE == 1 && RV_SIZE*2 == NELEM, int> = 0>
    ELEM_TYPE &hi()
    {
        return s[1];
    }

    /* .even(), vector result */
    template <size_t RV_SIZE = NELEM / 2,
              typename RV_TYPE = vtype<ELEM_TYPE, RV_SIZE, VTYPE_KIND::CONST_REF>,
              std::enable_if_t<RV_SIZE != 1 && RV_SIZE*2 == NELEM, int> = 0>
    const RV_TYPE even() const
    {
        ref_array_builder<const ELEM_TYPE, RV_SIZE> refs(
                                           s.raw_array,
                                           access_types<ACCESS_TYPE::EVEN>(),
                                           std::make_index_sequence<RV_SIZE>());
        return RV_TYPE(refs.result);
    }

    template <size_t RV_SIZE = NELEM / 2,
              typename RV_TYPE = vtype<ELEM_TYPE, RV_SIZE, VTYPE_KIND::REF>,
              std::enable_if_t<RV_SIZE != 1 && RV_SIZE*2 == NELEM, int> = 0>
    RV_TYPE even()
    {
        ref_array_builder<ELEM_TYPE, RV_SIZE> refs(
                                           s.raw_array,
                                           access_types<ACCESS_TYPE::EVEN>(),
                                           std::make_index_sequence<RV_SIZE>());
        return RV_TYPE(refs.result);
    }

    /* .even(), scalar result */
    template <size_t RV_SIZE = NELEM / 2,
              std::enable_if_t<RV_SIZE == 1 && RV_SIZE*2 == NELEM, int> = 0>
    const ELEM_TYPE &even() const
    {
        return s[0];
    }

    template <size_t RV_SIZE = NELEM / 2,
              std::enable_if_t<RV_SIZE == 1 && RV_SIZE*2 == NELEM, int> = 0>
    ELEM_TYPE &even()
    {
        return s[0];
    }

    /* .odd(), vector result */
    template <size_t RV_SIZE = NELEM / 2,
              typename RV_TYPE = vtype<ELEM_TYPE, RV_SIZE, VTYPE_KIND::CONST_REF>,
              std::enable_if_t<RV_SIZE != 1 && RV_SIZE*2 == NELEM, int> = 0>
    const RV_TYPE odd() const
    {
        ref_array_builder<const ELEM_TYPE, RV_SIZE> refs(
                                           s.raw_array,
                                           access_types<ACCESS_TYPE::ODD>(),
                                           std::make_index_sequence<RV_SIZE>());
        return RV_TYPE(refs.result);
    }

    template <size_t RV_SIZE = NELEM / 2,
              typename RV_TYPE = vtype<ELEM_TYPE, RV_SIZE, VTYPE_KIND::REF>,
              std::enable_if_t<RV_SIZE != 1 && RV_SIZE*2 == NELEM, int> = 0>
    RV_TYPE odd()
    {
        ref_array_builder<ELEM_TYPE, RV_SIZE> refs(
                                           s.raw_array,
                                           access_types<ACCESS_TYPE::ODD>(),
                                           std::make_index_sequence<RV_SIZE>());
        return RV_TYPE(refs.result);
    }

    /* .odd(), scalar result */
    template <size_t RV_SIZE = NELEM / 2,
              std::enable_if_t<RV_SIZE == 1 && RV_SIZE*2 == NELEM, int> = 0>
    const ELEM_TYPE &odd() const
    {
        return s[1];
    }

    template <size_t RV_SIZE = NELEM / 2,
              std::enable_if_t<RV_SIZE == 1 && RV_SIZE*2 == NELEM, int> = 0>
    ELEM_TYPE &odd()
    {
        return s[1];
    }

    /*-------------------------------------------------------------------------
    * Complex vector accessors. .r() and similar. May result in a scalar or a
    * vector, but always with a result of equal length but parent component type
    * as the child element type.
    *-------------------------------------------------------------------------*/
    /* .r(), vector result */
    template <typename RV_TYPE = vtype<COMP_TYPE, NELEM, VTYPE_KIND::CONST_REF>,
              typename DUMMY = ELEM_TYPE,
              enable_if_cmplx_t<DUMMY, int> = 0>
    const RV_TYPE r() const
    {
        ref_array_builder<const COMP_TYPE, NELEM> refs(
                                             s.raw_array,
                                             access_types<ACCESS_TYPE::REAL>(),
                                             std::make_index_sequence<NELEM>());
        return RV_TYPE(refs.result);
    }

    template <typename RV_TYPE = vtype<COMP_TYPE, NELEM, VTYPE_KIND::REF>,
              typename DUMMY = ELEM_TYPE,
              enable_if_cmplx_t<DUMMY, int> = 0>
    RV_TYPE r()
    {
        ref_array_builder<COMP_TYPE, NELEM> refs(
                                             s.raw_array,
                                             access_types<ACCESS_TYPE::REAL>(),
                                             std::make_index_sequence<NELEM>());
        return RV_TYPE(refs.result);
    }

    /* .i(), vector result */
    template <typename RV_TYPE = vtype<COMP_TYPE, NELEM, VTYPE_KIND::CONST_REF>,
              typename DUMMY = ELEM_TYPE,
              enable_if_cmplx_t<DUMMY, int> = 0>
    const RV_TYPE i() const
    {
        ref_array_builder<const COMP_TYPE, NELEM> refs(
                                             s.raw_array,
                                             access_types<ACCESS_TYPE::IMAG>(),
                                             std::make_index_sequence<NELEM>());
        return RV_TYPE(refs.result);
    }

    template <typename RV_TYPE = vtype<COMP_TYPE, NELEM, VTYPE_KIND::REF>,
              typename DUMMY = ELEM_TYPE,
              enable_if_cmplx_t<DUMMY, int> = 0>
    RV_TYPE i()
    {
        ref_array_builder<COMP_TYPE, NELEM> refs(
                                             s.raw_array,
                                             access_types<ACCESS_TYPE::IMAG>(),
                                             std::make_index_sequence<NELEM>());
        return RV_TYPE(refs.result);
    }

/*-----------------------------------------------------------------------------
* Public data
*-----------------------------------------------------------------------------*/
public:
    struct vtype_array_member<REAL_ELEM_TYPE, PADDED_NUM_ELEM> s;

/*-----------------------------------------------------------------------------
* Public debug operations -- Will not compile on the target!
*-----------------------------------------------------------------------------*/
public:
    /*-------------------------------------------------------------------------
    * print -- display the contents of the vector
    *-------------------------------------------------------------------------*/
    void print() const
    {
        std::cout << "(";

        print_vec<ELEM_TYPE>();
    }

/*-----------------------------------------------------------------------------
* Private helper methods
*-----------------------------------------------------------------------------*/
private:
    /*-------------------------------------------------------------------------
    * print_vec -- display the contents of a vector
    *-------------------------------------------------------------------------*/
    // Scalar variant
    template <typename E_TYPE,
              std::enable_if_t<std::is_arithmetic<E_TYPE>::value, int> = 0>
    void print_vec() const
    {
        // Pick a reasonable type for printing, i.e. promote short/char to int
        using conv_t =
            typename std::conditional<(std::is_integral<ELEM_TYPE>::value &&
                                sizeof(ELEM_TYPE) < sizeof(int32_t)),
                                int32_t, ELEM_TYPE>::type;

        for (size_t i = 0; i < NELEM - 1; i++)
            std::cout << (conv_t)s[i] << ", ";
        std::cout << (conv_t)s[NELEM - 1] << ")" << std::endl;
    }

    // Complex variant
    template <typename E_TYPE,
              enable_if_cmplx_t<E_TYPE, int> = 0>
    void print_vec() const
    {
        for (size_t i = 0; i < NELEM - 1; i++)
        {
            s[i].print();
            std::cout << ", ";
        }
        s[NELEM-1].print();
        std::cout << ")" << std::endl;
   }
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
};

/******************************************************************************
* ctype -- Class ctype is the high-level abstraction for complex element types.
*   It is instantiated with an element type. The component types should be those
*   found in stdint so that bit widths are guaranteed.
*
*   e.g.: cchar = ctype<int8_t>
*******************************************************************************/
template <typename COMP_T>
class ctype
{
/*-----------------------------------------------------------------------------
* General information members
*-----------------------------------------------------------------------------*/
public:
    using ELEM_TYPE = COMP_T;
    static constexpr size_t NUM_ELEM = 1;

    using COMP_TYPE = COMP_T;

/*-----------------------------------------------------------------------------
* Constructors and construction related data types
*-----------------------------------------------------------------------------*/
public:

    /*-------------------------------------------------------------------------
    * Constructor to create a ctype from a real and imaginary component
    *-------------------------------------------------------------------------*/
    explicit ctype(const COMP_TYPE &real, const COMP_TYPE &imag) :
        r_(real),
        i_(imag)
    {
    }

    /*-------------------------------------------------------------------------
    * Copy constructor -- defaulted, trivially copyable
    *-------------------------------------------------------------------------*/
    ctype(const ctype<COMP_TYPE> &cmplx) = default;

    /*-------------------------------------------------------------------------
    * Constructor to initialize a ctype from a vreg_t
    *-------------------------------------------------------------------------*/
    explicit ctype(const vreg_t &src)
    {
        init_ctype_from_vreg_t(src, *this);
    }

    /*-------------------------------------------------------------------------
    * Default constructor -- defaulted, trivially constructible
    * e.g.: cint tmp;
    *-------------------------------------------------------------------------*/
    ctype() = default;

/*-----------------------------------------------------------------------------
* Internal data -- Not private as to not conflict with g++ versions that desire
*   no private members in classes that may be memcpy'd into.
*   (See -Wclass-memaccess.) DO NOT USE DIRECTLY.
*-----------------------------------------------------------------------------*/
public:
    COMP_TYPE r_, i_;

/*-----------------------------------------------------------------------------
* Component accessors
*-----------------------------------------------------------------------------*/
public:
    COMP_TYPE & r() { return r_; }
    const COMP_TYPE & r() const { return r_; }

    COMP_TYPE & i() { return i_; }
    const COMP_TYPE & i() const { return i_; }

/*-----------------------------------------------------------------------------
* Public debug operations -- Will not compile on the target!
*-----------------------------------------------------------------------------*/
public:
    /*-------------------------------------------------------------------------
    * print -- display the contents of the complex type
    *-------------------------------------------------------------------------*/
    void print() const
    {
        using conv_t =
            typename std::conditional<(std::is_integral<COMP_TYPE>::value &&
                                sizeof(COMP_TYPE) < sizeof(int32_t)),
                                int32_t, COMP_TYPE>::type;

        std::cout << "{R = " << (conv_t)r_ << ", I = " << (conv_t)i_ << "}";
    }

/*-----------------------------------------------------------------------------
* Operators
*-----------------------------------------------------------------------------*/
public:
    /*-------------------------------------------------------------------------
    * Assignment from ctype -- defaulted, trivially copyable
    *-------------------------------------------------------------------------*/
    ctype &operator=(const ctype<COMP_TYPE> &rhs) = default;

    /*-------------------------------------------------------------------------
    * Cast to vreg_t
    *-------------------------------------------------------------------------*/
    operator vreg_t() const
    {
        return convert_ctype_to_vreg_t<COMP_TYPE>(*this);
    }

    /*-------------------------------------------------------------------------
    * Pre-increment
    *-------------------------------------------------------------------------*/
    ctype operator++()
    {
        static_assert(!std::is_same<COMP_TYPE, float>::value
                      && !std::is_same<COMP_TYPE, double>::value,
                      "Error: float and double complex pre-increment is not supported");
        r_ = r_ + 1;
        return *this;
    }

    /*-------------------------------------------------------------------------
    * Post-increment
    *-------------------------------------------------------------------------*/
    ctype operator++(int)
    {
        static_assert(!std::is_same<COMP_TYPE, float>::value
                      && !std::is_same<COMP_TYPE, double>::value,
                      "Error: float and double complex post-increment is not supported");
        ctype<COMP_TYPE> copy;
        copy.r_ = r_;
        ++*this;
        return copy;
    }

    /*-------------------------------------------------------------------------
    * Pre-decrement
    *-------------------------------------------------------------------------*/
    ctype operator--()
    {
        static_assert(!std::is_same<COMP_TYPE, float>::value
                      && !std::is_same<COMP_TYPE, double>::value,
                      "Error: float and double complex pre-decrement is not supported");
        r_ = r_ - 1;
        return *this;
    }

    /*-------------------------------------------------------------------------
    * Post-decrement
    *-------------------------------------------------------------------------*/
    ctype operator--(int)
    {
        static_assert(!std::is_same<COMP_TYPE, float>::value
                      && !std::is_same<COMP_TYPE, double>::value,
                      "Error: float and double complex post-decrement is not supported");
        ctype<COMP_TYPE> copy;
        copy.r_ = r_;
        --*this;
        return copy;
    }

    /*-------------------------------------------------------------------------
    * Plus
    *-------------------------------------------------------------------------*/
    ctype operator+(const ctype<COMP_TYPE> rhs) const
    {
        ctype<COMP_TYPE> res;
        res.r_ = (*this).r_ + rhs.r_;
        res.i_ = (*this).i_ + rhs.i_;
        return res;
    }

    /*-------------------------------------------------------------------------
    * Unary plus (effectively a copy operation)
    *-------------------------------------------------------------------------*/
    ctype operator+() const
    {
        return *this;
    }

    /*-------------------------------------------------------------------------
    * Minus
    *-------------------------------------------------------------------------*/
    ctype operator-(const ctype<COMP_TYPE> rhs) const
    {
        ctype<COMP_TYPE> res;
        res.r_ = (*this).r_ - rhs.r_;
        res.i_ = (*this).i_ - rhs.i_;
        return res;
    }

    /*-------------------------------------------------------------------------
    * Unary minus
    *-------------------------------------------------------------------------*/
    ctype operator-() const
    {
        ctype<COMP_TYPE> res;
        res.r_ = -(*this).r_;
        res.i_ = -(*this).i_;
        return res;
    }

    /*-------------------------------------------------------------------------
    * Multiply
    *-------------------------------------------------------------------------*/
    ctype operator*(const ctype<COMP_TYPE> rhs) const
    {
        ctype<COMP_TYPE> res;
        res.r_ = (*this).r_ * rhs.r_ - ((*this).i_ * rhs.i_);
        res.i_ = (*this).r_ * rhs.i_ + ((*this).i_ * rhs.r_);
        return res;
    }

    /*-------------------------------------------------------------------------
    * Divide
    *-------------------------------------------------------------------------*/
    ctype operator/(const ctype<COMP_TYPE> rhs) const
    {
        ctype<COMP_TYPE> res;
        res.r_ = ((*this).r_ * rhs.r_ + ((*this).i_ * rhs.i_)) /
                    (rhs.r_ * rhs.r_ + rhs.i_ * rhs.i_);
        res.i_ = ((*this).i_ * rhs.r_ + ((*this).r_ * rhs.i_)) /
                    (rhs.r_ * rhs.r_ + rhs.i_ * rhs.i_);
        return res;
    }

    /*-------------------------------------------------------------------------
    * Plus Assign
    *-------------------------------------------------------------------------*/
    ctype &operator+=(const ctype<COMP_TYPE> rhs)
    {
        (*this).r_ += rhs.r_;
        (*this).i_ += rhs.i_;
        return *this;
    }

    /*-------------------------------------------------------------------------
    * Minus Assign
    *-------------------------------------------------------------------------*/
    ctype &operator-=(const ctype<COMP_TYPE> rhs)
    {
        (*this).r_ -= rhs.r_;
        (*this).i_ -= rhs.i_;
        return *this;
    }

    /*-------------------------------------------------------------------------
    * Multiply Assign
    *-------------------------------------------------------------------------*/
    ctype &operator*=(const ctype<COMP_TYPE> rhs)
    {
        *this = *this * rhs;
        return *this;
    }

    /*-------------------------------------------------------------------------
    * Divide Assign
    *-------------------------------------------------------------------------*/
    ctype &operator/=(const ctype<COMP_TYPE> rhs)
    {
        *this = *this / rhs;
        return *this;
    }
};

/******************************************************************************
* __vpred -- Implementation of the vector predicate type
******************************************************************************/
class __vpred
{
/*-----------------------------------------------------------------------------
* Constructors
*-----------------------------------------------------------------------------*/
public:
    /*-------------------------------------------------------------------------
    * Default constructor
    *-------------------------------------------------------------------------*/
    __vpred() :
        pred(0)
    {}

    /*-------------------------------------------------------------------------
    * Constructor to initialize a __vpred from a vpred_t. A vpred_t is
    * a uint64_t used to represent vector predicates within C semantic
    * function definitions. Constructor must be explicit. Otherwise,
    * can do vpred = int which is not allowed on C7000
    *-------------------------------------------------------------------------*/
    explicit __vpred(vpred_t input) :
        pred(input)
    {}

    /*-------------------------------------------------------------------------
    * Cast to vpred_t
    *-------------------------------------------------------------------------*/
    operator vpred_t() const
    {
        return pred;
    }

/*-----------------------------------------------------------------------------
* Public debug operations -- Will not compile on the target!
*-----------------------------------------------------------------------------*/
public:
    /*-------------------------------------------------------------------------
    * print -- Display the predicate as a binary value of 64 bits
    *-------------------------------------------------------------------------*/
    void print()
    {
        std::cout << std::bitset<__C7X_VEC_SIZE_BYTES__>(pred) << std::endl;
    }

/*-----------------------------------------------------------------------------
* Private data
*-----------------------------------------------------------------------------*/
private:
#if __C7X_VEC_SIZE_BYTES__ == 64
    uint64_t pred;
#elif __C7X_VEC_SIZE_BYTES__ == 32
    uint32_t pred;
#else
#error "Unknown vector size for vpred"
#endif
};

/******************************************************************************
*
* Conversion Operations
*
******************************************************************************/

// Functions to get source element size based on type (scalar or complex)
template <typename SRC_T,
          enable_if_cmplx_t<SRC_T, int> = 0>
constexpr size_t get_src_size()
{
    return sizeof(typename SRC_T::ELEM_TYPE) * 2;
}

template <typename SRC_T,
          std::enable_if_t<std::is_arithmetic<SRC_T>::value, int> = 0>
constexpr size_t get_src_size()
{
    return sizeof(SRC_T);
}

#include <ti_he_impl/vector_conv.h>

/******************************************************************************
*
* any/all Operations
*
*******************************************************************************/

/*-----------------------------------------------------------------------------
* __all - Takes an integral vector and returns 1 if the high bit is set in all
*   lanes.
*-----------------------------------------------------------------------------*/
// Scalar variant
template <typename ELEM_T>
int __all(ELEM_T input)
{
    static_assert(std::is_integral<ELEM_T>::value,
                  "Error: non-integral vector __all is not supported");
    static_assert(!std::is_same<ELEM_T, bool>::value,
                  "Error: __all not supported with bool vectors.");
    typedef std::make_unsigned_t<ELEM_T> utype;
    constexpr int shift = (sizeof(ELEM_T) * CHAR_BIT) - 1;
    return (((utype)input) >> shift) & 1;
}

// Vector variant
template <typename ELEM_T,
          size_t NELEM,
          VTYPE_KIND KIND>
int __all(const vtype<ELEM_T, NELEM, KIND> &input)
{
    static_assert(std::is_integral<ELEM_T>::value,
                  "Error: non-integral vector __all is not supported");
    static_assert(!std::is_same<ELEM_T, bool>::value,
                  "Error: __all not supported with bool vectors.");
    typedef std::make_unsigned_t<ELEM_T> utype;
    constexpr int shift = (sizeof(ELEM_T) * CHAR_BIT) - 1;
    ELEM_T result = 1;
    for (size_t i = 0; i < NELEM; i++)
    {
        result &= ((utype)input.s[i]) >> shift;
    }
    return result;
}

/*-----------------------------------------------------------------------------
* __any - Takes an integral vector and returns 1 if the high bit is set in any
*   lane.
*-----------------------------------------------------------------------------*/
// Scalar variant
template <typename ELEM_T>
int __any(ELEM_T input)
{
    static_assert(std::is_integral<ELEM_T>::value,
                  "Error: non-integral vector __any is not supported");
    static_assert(!std::is_same<ELEM_T, bool>::value,
                  "Error: __any not supported with bool vectors.");
    typedef std::make_unsigned_t<ELEM_T> utype;
    constexpr int shift = (sizeof(ELEM_T) * CHAR_BIT) - 1;
    return (((utype)input) >> shift) & 1;
}

// Vector variant
template <typename ELEM_T,
          size_t NELEM,
          VTYPE_KIND KIND>
int __any(const vtype<ELEM_T, NELEM, KIND> &input)
{
    static_assert(std::is_integral<ELEM_T>::value,
                  "Error: non-integral vector __any is not supported");
    static_assert(!std::is_same<ELEM_T, bool>::value,
                  "Error: __any not supported with bool vectors.");
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
*
* Vector Operations
*
******************************************************************************/
#define DEFINE_ARITH_OP_OVERLOAD(op) \
template <typename ELEM_T, \
          size_t NELEM, \
          VTYPE_KIND KIND1, \
          VTYPE_KIND KIND2> \
vtype<ELEM_T, NELEM, VTYPE_KIND::DATA> operator op( \
    const vtype<ELEM_T, NELEM, KIND1> &lhs, \
    const vtype<ELEM_T, NELEM, KIND2> &rhs) \
{ \
    static_assert(!std::is_same<ELEM_T, bool>::value, \
                  "Error: bool vector " #op " is not supported"); \
    vtype<ELEM_T, NELEM, VTYPE_KIND::DATA> res; \
    for (size_t i = 0; i < NELEM; i++) \
        res.s[i] = lhs.s[i] op rhs.s[i]; \
    return res; \
} \
template <typename ELEM_T, size_t NELEM, VTYPE_KIND KIND, typename SCAL_T> \
vtype<ELEM_T, NELEM, VTYPE_KIND::DATA> operator op( \
    const vtype<ELEM_T, NELEM, KIND> &lhs, \
    SCAL_T scalar) \
{ \
    static_assert(!std::is_same<ELEM_T, bool>::value, \
                  "Error: bool vector " #op " is not supported"); \
    static_assert(can_widen_to_vec_of_elem<SCAL_T, ELEM_T>::value, \
                  "Error: cannot widen to vector type."); \
    return lhs op vtype<ELEM_T, NELEM, VTYPE_KIND::DATA>(scalar); \
} \
template <typename ELEM_T, size_t NELEM, VTYPE_KIND KIND, typename SCAL_T> \
vtype<ELEM_T, NELEM, VTYPE_KIND::DATA> operator op( \
     SCAL_T scalar, \
     const vtype<ELEM_T, NELEM, KIND> &rhs) \
{ \
    static_assert(!std::is_same<ELEM_T, bool>::value, \
                  "Error: bool vector " #op " is not supported"); \
    static_assert(can_widen_to_vec_of_elem<SCAL_T, ELEM_T>::value, \
                  "Error: cannot widen to vector type."); \
    return vtype<ELEM_T, NELEM, VTYPE_KIND::DATA>(scalar) op rhs; \
}

DEFINE_ARITH_OP_OVERLOAD(+)
DEFINE_ARITH_OP_OVERLOAD(-)
DEFINE_ARITH_OP_OVERLOAD(*)
DEFINE_ARITH_OP_OVERLOAD(/)

#define DEFINE_INTEGRAL_ARITH_OP_OVERLOAD(op) \
template <typename ELEM_T, \
          size_t NELEM, \
          VTYPE_KIND KIND1, \
          VTYPE_KIND KIND2> \
vtype<ELEM_T, NELEM, VTYPE_KIND::DATA> operator op( \
    const vtype<ELEM_T, NELEM, KIND1> &lhs, \
    const vtype<ELEM_T, NELEM, KIND2> &rhs) \
{ \
    static_assert(std::is_integral<ELEM_T>::value, \
                  "Error: non-integral vector " #op " is not supported"); \
    static_assert(!std::is_same<ELEM_T, bool>::value, \
                  "Error: bool vector " #op " is not supported"); \
    vtype<ELEM_T, NELEM, VTYPE_KIND::DATA> res; \
    for (size_t i = 0; i < NELEM; i++) \
        res.s[i] = lhs.s[i] op rhs.s[i]; \
    return res; \
} \
template <typename ELEM_T, \
          size_t NELEM, \
          VTYPE_KIND KIND, \
          typename SCAL_T> \
vtype<ELEM_T, NELEM, VTYPE_KIND::DATA> operator op( \
    const vtype<ELEM_T, NELEM, KIND> &lhs, \
    SCAL_T scalar) \
{ \
    static_assert(std::is_integral<ELEM_T>::value, \
                  "Error: non-integral vector " #op " is not supported"); \
    static_assert(!std::is_same<ELEM_T, bool>::value, \
                  "Error: bool vector " #op " is not supported"); \
    static_assert(can_widen_to_vec_of_elem<SCAL_T, ELEM_T>::value, \
                  "Error: cannot widen to vector type."); \
    return lhs op vtype<ELEM_T, NELEM, VTYPE_KIND::DATA>(scalar); \
} \
template <typename ELEM_T, \
          size_t NELEM, \
          VTYPE_KIND KIND, \
          typename SCAL_T> \
vtype<ELEM_T, NELEM, VTYPE_KIND::DATA> operator op( \
     SCAL_T scalar, \
     const vtype<ELEM_T, NELEM, KIND> &rhs) \
{ \
    static_assert(std::is_integral<ELEM_T>::value, \
                  "Error: non-integral vector " #op " is not supported"); \
    static_assert(!std::is_same<ELEM_T, bool>::value, \
                  "Error: bool vector " #op " is not supported"); \
    static_assert(can_widen_to_vec_of_elem<SCAL_T, ELEM_T>::value, \
                  "Error: cannot widen to vector type."); \
    return vtype<ELEM_T, NELEM, VTYPE_KIND::DATA>(scalar) op rhs; \
}

DEFINE_INTEGRAL_ARITH_OP_OVERLOAD(&)
DEFINE_INTEGRAL_ARITH_OP_OVERLOAD(|)
DEFINE_INTEGRAL_ARITH_OP_OVERLOAD(^)
DEFINE_INTEGRAL_ARITH_OP_OVERLOAD(%)
DEFINE_INTEGRAL_ARITH_OP_OVERLOAD(<<)
DEFINE_INTEGRAL_ARITH_OP_OVERLOAD(>>)

#define DEFINE_LOG_OP_OVERLOAD(op) \
template <typename ELEM_T, \
          size_t NELEM, \
          VTYPE_KIND KIND1, \
          VTYPE_KIND KIND2> \
typename vtype<ELEM_T, NELEM, VTYPE_KIND::DATA>::LOG_RES_TYPE operator op( \
    const vtype<ELEM_T, NELEM, KIND1> &lhs, \
    const vtype<ELEM_T, NELEM, KIND2> &rhs) \
{ \
    static_assert(!std::is_same<ELEM_T, bool>::value, \
                  "Error: bool vector " #op " is not supported"); \
    typename vtype<ELEM_T, NELEM, VTYPE_KIND::DATA>::LOG_RES_TYPE res; \
    for (size_t i = 0; i < NELEM; i++) \
        res.s[i] = lhs.s[i] op rhs.s[i] ? -1 : 0; \
    return res; \
} \
template <typename ELEM_T, size_t NELEM, VTYPE_KIND KIND, typename SCAL_T> \
typename vtype<ELEM_T, NELEM, VTYPE_KIND::DATA>::LOG_RES_TYPE operator op( \
    const vtype<ELEM_T, NELEM, KIND> &lhs, \
    SCAL_T scalar) \
{ \
    static_assert(!std::is_same<ELEM_T, bool>::value, \
                  "Error: bool vector " #op " is not supported"); \
    static_assert(can_widen_to_vec_of_elem<SCAL_T, ELEM_T>::value, \
                  "Error: cannot widen to vector type."); \
    return lhs op vtype<ELEM_T, NELEM, VTYPE_KIND::DATA>(scalar); \
} \
template <typename ELEM_T, size_t NELEM, VTYPE_KIND KIND, typename SCAL_T> \
typename vtype<ELEM_T, NELEM, VTYPE_KIND::DATA>::LOG_RES_TYPE operator op( \
     SCAL_T scalar, \
     const vtype<ELEM_T, NELEM, KIND> &rhs) \
{ \
    static_assert(!std::is_same<ELEM_T, bool>::value, \
                  "Error: bool vector " #op " is not supported"); \
    static_assert(can_widen_to_vec_of_elem<SCAL_T, ELEM_T>::value, \
                  "Error: cannot widen to vector type."); \
    return vtype<ELEM_T, NELEM, VTYPE_KIND::DATA>(scalar) op rhs; \
}

DEFINE_LOG_OP_OVERLOAD(>)
DEFINE_LOG_OP_OVERLOAD(>=)
DEFINE_LOG_OP_OVERLOAD(<)
DEFINE_LOG_OP_OVERLOAD(<=)
DEFINE_LOG_OP_OVERLOAD(==)
DEFINE_LOG_OP_OVERLOAD(!=)
DEFINE_LOG_OP_OVERLOAD(&&)
DEFINE_LOG_OP_OVERLOAD(||)

/*-----------------------------------------------------------------------------
* Logical Not ! Operator overloads
*-----------------------------------------------------------------------------*/
template <typename ELEM_T,
          size_t NELEM,
          VTYPE_KIND KIND>
typename vtype<ELEM_T, NELEM, VTYPE_KIND::DATA>::LOG_RES_TYPE operator!(
    const vtype<ELEM_T, NELEM, KIND> &rhs)
{
    static_assert(!std::is_same<ELEM_T, bool>::value,
                  "Error: bool vector ! is not supported");
    typename vtype<ELEM_T, NELEM, VTYPE_KIND::DATA>::LOG_RES_TYPE res;
    for (size_t i = 0; i < NELEM; i++)
        res.s[i] = !rhs.s[i] ? -1 : 0;
    return res;
}

} /* namespace _c70_he_detail */


/******************************************************************************
*
* Definition of vector types in the global namespace.
*
******************************************************************************/
typedef _c70_he_detail::__vpred vpred;
using _c70_he_detail::__vpred;

/* Base complex types */
using __cchar   = _c70_he_detail::ctype<int8_t>;
using cchar = __cchar;
using __const_cchar = const __cchar;
using const_cchar = __const_cchar;
using __cshort  = _c70_he_detail::ctype<int16_t>;
using cshort = __cshort;
using __const_cshort = const __cshort;
using const_cshort = __const_cshort;
using __cint    = _c70_he_detail::ctype<int32_t>;
using cint = __cint;
using __const_cint = const __cint;
using const_cint= __const_cint;
using __clong   = _c70_he_detail::ctype<int64_t>;
using clong = __clong;
using __const_clong = const __clong;
using const_clong = __const_clong;
using __cfloat  = _c70_he_detail::ctype<float>;
using cfloat = __cfloat;
using __const_cfloat = const __cfloat;
using const_cfloat = __const_cfloat;
using __cdouble = _c70_he_detail::ctype<double>;
using cdouble = __cdouble;
using __const_cdouble = const __cdouble;
using const_cdouble = __const_cdouble;

/* Arithmetic vector types and pointers */
#define DECLARE_VEC_TYPES(namebase,realbase,lanes) \
    using __ ## namebase ## lanes = _c70_he_detail::vtype<realbase,lanes, _c70_he_detail::VTYPE_KIND::DATA>; \
    using namebase ## lanes = __ ## namebase ## lanes; \
    using __ ## namebase ## lanes ## _ptr = namebase ## lanes *; \
    using namebase ## lanes ## _ptr = __ ## namebase ## lanes ## _ptr; \
    using __const_ ## namebase ## lanes = const namebase ## lanes; \
    using const_ ## namebase ## lanes = __const_ ## namebase ## lanes; \
    using __const_ ## namebase ## lanes ## _ptr = const namebase ## lanes *; \
    using const_ ## namebase ## lanes ## _ptr = __const_ ## namebase ## lanes ## _ptr;

#define DECLARE_NONVEC_TYPES(namebase,realbase) \
    using __ ## namebase = realbase; \
    using namebase = __ ## namebase; \
    using __const_ ## namebase = const realbase; \
    using const_ ## namebase = __const_ ## namebase; \
    using __ ## namebase ## _ptr = realbase*; \
    using namebase ## _ptr = __ ## namebase ## _ptr; \
    using __const_ ## namebase ## _ptr = const realbase*; \
    using const_ ## namebase ## _ptr = __const_ ## namebase ## _ptr;

/* char types */
DECLARE_VEC_TYPES(char,int8_t,2)
DECLARE_VEC_TYPES(char,int8_t,3)
DECLARE_VEC_TYPES(char,int8_t,4)
DECLARE_VEC_TYPES(char,int8_t,8)
DECLARE_VEC_TYPES(char,int8_t,16)
DECLARE_VEC_TYPES(char,int8_t,32)
DECLARE_VEC_TYPES(char,int8_t,64)

DECLARE_NONVEC_TYPES(uchar,uint8_t)
DECLARE_VEC_TYPES(uchar,uint8_t,2)
DECLARE_VEC_TYPES(uchar,uint8_t,3)
DECLARE_VEC_TYPES(uchar,uint8_t,4)
DECLARE_VEC_TYPES(uchar,uint8_t,8)
DECLARE_VEC_TYPES(uchar,uint8_t,16)
DECLARE_VEC_TYPES(uchar,uint8_t,32)
DECLARE_VEC_TYPES(uchar,uint8_t,64)

/* boolean types */
DECLARE_VEC_TYPES(bool,bool,2)
DECLARE_VEC_TYPES(bool,bool,3)
DECLARE_VEC_TYPES(bool,bool,4)
DECLARE_VEC_TYPES(bool,bool,8)
DECLARE_VEC_TYPES(bool,bool,16)
DECLARE_VEC_TYPES(bool,bool,32)
DECLARE_VEC_TYPES(bool,bool,64)

/* short types */
DECLARE_VEC_TYPES(short,int16_t,2)
DECLARE_VEC_TYPES(short,int16_t,3)
DECLARE_VEC_TYPES(short,int16_t,4)
DECLARE_VEC_TYPES(short,int16_t,8)
DECLARE_VEC_TYPES(short,int16_t,16)
DECLARE_VEC_TYPES(short,int16_t,32)

DECLARE_NONVEC_TYPES(ushort,uint16_t)
DECLARE_VEC_TYPES(ushort,uint16_t,2)
DECLARE_VEC_TYPES(ushort,uint16_t,3)
DECLARE_VEC_TYPES(ushort,uint16_t,4)
DECLARE_VEC_TYPES(ushort,uint16_t,8)
DECLARE_VEC_TYPES(ushort,uint16_t,16)
DECLARE_VEC_TYPES(ushort,uint16_t,32)

/* int types */
DECLARE_VEC_TYPES(int,int32_t,2)
DECLARE_VEC_TYPES(int,int32_t,3)
DECLARE_VEC_TYPES(int,int32_t,4)

/* Account for definition of __intn on Microsoft systems. */
/* __MINGW32__ is defined in both 32 bit and 64 bit MINGW */
#if defined(_MSC_VER) || defined(__MINGW32__)
#if defined(__int8)
#undef __int8
#endif
#define __int8 int8
using int8 = _c70_he_detail::vtype<int32_t,8, _c70_he_detail::VTYPE_KIND::DATA>;
using __int8_ptr = int8 *;
using int8_ptr = __int8_ptr;
using __const_int8 = const int8;
using const_int8 = __const_int8;
using __const_int8_ptr = const int8 *;
using const_int8_ptr = __const_int8_ptr;

#if defined(__int16)
#undef __int16
#endif
#define __int16 int16
using int16 = _c70_he_detail::vtype<int32_t,16, _c70_he_detail::VTYPE_KIND::DATA>;
using __int16_ptr = int16 *;
using int16_ptr = __int16_ptr;
using __const_int16 = const int16;
using const_int16 = __const_int16;
using __const_int16_ptr = const int16 *;
using const_int16_ptr = __const_int16_ptr;
#else
DECLARE_VEC_TYPES(int,int32_t,8)
DECLARE_VEC_TYPES(int,int32_t,16)
#endif

DECLARE_NONVEC_TYPES(uint,uint32_t)
DECLARE_VEC_TYPES(uint,uint32_t,2)
DECLARE_VEC_TYPES(uint,uint32_t,3)
DECLARE_VEC_TYPES(uint,uint32_t,4)
DECLARE_VEC_TYPES(uint,uint32_t,8)
DECLARE_VEC_TYPES(uint,uint32_t,16)

/* float types */
DECLARE_VEC_TYPES(float,float,2)
DECLARE_VEC_TYPES(float,float,3)
DECLARE_VEC_TYPES(float,float,4)
DECLARE_VEC_TYPES(float,float,8)
DECLARE_VEC_TYPES(float,float,16)

/* long types */
DECLARE_VEC_TYPES(long,int64_t,2)
DECLARE_VEC_TYPES(long,int64_t,3)
DECLARE_VEC_TYPES(long,int64_t,4)
DECLARE_VEC_TYPES(long,int64_t,8)
DECLARE_VEC_TYPES(long,int64_t,16)

DECLARE_NONVEC_TYPES(ulong,uint64_t)
DECLARE_VEC_TYPES(ulong,uint64_t,2)
DECLARE_VEC_TYPES(ulong,uint64_t,3)
DECLARE_VEC_TYPES(ulong,uint64_t,4)
DECLARE_VEC_TYPES(ulong,uint64_t,8)
DECLARE_VEC_TYPES(ulong,uint64_t,16)

/* double types */
DECLARE_VEC_TYPES(double,double,2)
DECLARE_VEC_TYPES(double,double,3)
DECLARE_VEC_TYPES(double,double,4)
DECLARE_VEC_TYPES(double,double,8)
DECLARE_VEC_TYPES(double,double,16)

#define DECLARE_CMPLX_VEC_TYPES(namebase,realbase,lanes) \
    using __ ## namebase ## lanes = _c70_he_detail::vtype<realbase,lanes, _c70_he_detail::VTYPE_KIND::DATA>; \
    using namebase ## lanes = __ ## namebase ## lanes; \
    using __ ## namebase ## lanes ## _ptr = namebase ## lanes*; \
    using namebase ## lanes ## _ptr = __ ## namebase ## lanes ## _ptr; \
    using __const_ ## namebase ## lanes = const namebase ## lanes; \
    using const_ ## namebase ## lanes = __const_ ## namebase ## lanes; \
    using __const_ ## namebase ## lanes ## _ptr = const namebase ## lanes *; \
    using const_ ## namebase ## lanes ## _ptr = __const_ ## namebase ## lanes ## _ptr;

/* cchar types */
using __cchar_ptr   = __cchar*;
using cchar_ptr = __cchar_ptr;
using __const_cchar_ptr = const cchar *;
using const_cchar_ptr = __const_cchar_ptr;
DECLARE_CMPLX_VEC_TYPES(cchar,cchar,2)
DECLARE_CMPLX_VEC_TYPES(cchar,cchar,4)
DECLARE_CMPLX_VEC_TYPES(cchar,cchar,8)
DECLARE_CMPLX_VEC_TYPES(cchar,cchar,16)
DECLARE_CMPLX_VEC_TYPES(cchar,cchar,32)

/* cshort types */
using __cshort_ptr   = __cshort*;
using cshort_ptr = __cshort_ptr;
using __const_cshort_ptr = const cshort*;
using const_cshort_ptr = __const_cshort_ptr;
DECLARE_CMPLX_VEC_TYPES(cshort,cshort,2)
DECLARE_CMPLX_VEC_TYPES(cshort,cshort,4)
DECLARE_CMPLX_VEC_TYPES(cshort,cshort,8)
DECLARE_CMPLX_VEC_TYPES(cshort,cshort,16)

/* cint types */
using __cint_ptr   = __cint*;
using cint_ptr = __cint_ptr;
using __const_cint_ptr = const cint *;
using const_cint_ptr = __const_cint_ptr;
DECLARE_CMPLX_VEC_TYPES(cint,cint,2)
DECLARE_CMPLX_VEC_TYPES(cint,cint,4)
DECLARE_CMPLX_VEC_TYPES(cint,cint,8)

/* cfloat types */
using __cfloat_ptr   = __cfloat*;
using cfloat_ptr = __cfloat_ptr;
using __const_cfloat_ptr = const cfloat *;
using const_cfloat_ptr = __const_cfloat_ptr;
DECLARE_CMPLX_VEC_TYPES(cfloat,cfloat,2)
DECLARE_CMPLX_VEC_TYPES(cfloat,cfloat,4)
DECLARE_CMPLX_VEC_TYPES(cfloat,cfloat,8)

/* clong types */
using __clong_ptr   = __clong*;
using clong_ptr = __clong_ptr;
using __const_clong_ptr = const clong *;
using const_clong_ptr = __const_clong_ptr;
DECLARE_CMPLX_VEC_TYPES(clong,clong,2)
DECLARE_CMPLX_VEC_TYPES(clong,clong,4)
DECLARE_CMPLX_VEC_TYPES(clong,clong,8)

/* cdouble types */
using __cdouble_ptr   = __cdouble *;
using cdouble_ptr = __cdouble_ptr;
using __const_cdouble_ptr = const __cdouble *;
using const_cdouble_ptr = __const_cdouble_ptr;
DECLARE_CMPLX_VEC_TYPES(cdouble,cdouble,2)
DECLARE_CMPLX_VEC_TYPES(cdouble,cdouble,4)
DECLARE_CMPLX_VEC_TYPES(cdouble,cdouble,8)

#undef DECLARE_VEC_TYPES


/******************************************************************************
*
* Definition of vector utilities.
*
******************************************************************************/

/*-----------------------------------------------------------------------------
* Reinterpretation casts
*-----------------------------------------------------------------------------*/
#define _AS_CONV(CONV_OUT_NAME, CONV_OUT_T) \
template <typename CONV_IN_T> \
CONV_OUT_T __as_ ## CONV_OUT_NAME(const CONV_IN_T &in) \
{ \
    typedef typename _c70_he_detail::complex_swapper<CONV_IN_T>::RES_T IN_DATA_T; \
    static_assert(_c70_he_detail::is_vtype_or_elem<CONV_IN_T>::value, \
                  "Illegal reinterpret cast: Bad input type"); \
    static_assert(sizeof(IN_DATA_T) == sizeof(CONV_OUT_T), \
                  "Illegal reinterpret cast: Type sizes must be the same"); \
    IN_DATA_T tmp_src = _c70_he_detail::complex_swapper<CONV_IN_T>::swap(in); \
    CONV_OUT_T tmp_dst; \
    static_assert(std::is_trivial<CONV_OUT_T>::value, \
                  "Unexpected: Not a trivial destination."); \
    memcpy(&tmp_dst, &tmp_src, sizeof(CONV_OUT_T)); \
    return _c70_he_detail::complex_swapper<CONV_OUT_T>::swap(tmp_dst); \
}
_AS_CONV(long16, long16)
_AS_CONV(long8, long8)
_AS_CONV(long4, long4)
_AS_CONV(long3, long3)
_AS_CONV(long2, long2)
_AS_CONV(long, int64_t)

_AS_CONV(ulong16, ulong16)
_AS_CONV(ulong8, ulong8)
_AS_CONV(ulong4, ulong4)
_AS_CONV(ulong3, ulong3)
_AS_CONV(ulong2, ulong2)
_AS_CONV(ulong, ulong)

_AS_CONV(double16, double16)
_AS_CONV(double8, double8)
_AS_CONV(double4, double4)
_AS_CONV(double3, double3)
_AS_CONV(double2, double2)
_AS_CONV(double, double)

_AS_CONV(int16, int16)
_AS_CONV(int8, int8)
_AS_CONV(int4, int4)
_AS_CONV(int3, int3)
_AS_CONV(int2, int2)
_AS_CONV(int, int32_t)

_AS_CONV(uint16, uint16)
_AS_CONV(uint8, uint8)
_AS_CONV(uint4, uint4)
_AS_CONV(uint3, uint3)
_AS_CONV(uint2, uint2)
_AS_CONV(uint, uint)

_AS_CONV(float16, float16)
_AS_CONV(float8, float8)
_AS_CONV(float4, float4)
_AS_CONV(float3, float3)
_AS_CONV(float2, float2)
_AS_CONV(float, float)

_AS_CONV(short32, short32)
_AS_CONV(short16, short16)
_AS_CONV(short8, short8)
_AS_CONV(short4, short4)
_AS_CONV(short3, short3)
_AS_CONV(short2, short2)
_AS_CONV(short, int16_t)

_AS_CONV(ushort32, ushort32)
_AS_CONV(ushort16, ushort16)
_AS_CONV(ushort8, ushort8)
_AS_CONV(ushort4, ushort4)
_AS_CONV(ushort3, ushort3)
_AS_CONV(ushort2, ushort2)
_AS_CONV(ushort, ushort)

_AS_CONV(char64, char64)
_AS_CONV(char32, char32)
_AS_CONV(char16, char16)
_AS_CONV(char8, char8)
_AS_CONV(char4, char4)
_AS_CONV(char3, char3)
_AS_CONV(char2, char2)
_AS_CONV(char, int8_t)

_AS_CONV(uchar64, uchar64)
_AS_CONV(uchar32, uchar32)
_AS_CONV(uchar16, uchar16)
_AS_CONV(uchar8, uchar8)
_AS_CONV(uchar4, uchar4)
_AS_CONV(uchar3, uchar3)
_AS_CONV(uchar2, uchar2)
_AS_CONV(uchar, uchar)

_AS_CONV(bool64, bool64)
_AS_CONV(bool32, bool32)
_AS_CONV(bool16, bool16)
_AS_CONV(bool8, bool8)
_AS_CONV(bool4, bool4)
_AS_CONV(bool3, bool3)
_AS_CONV(bool2, bool2)
_AS_CONV(bool, bool)

_AS_CONV(clong8, clong8)
_AS_CONV(clong4, clong4)
_AS_CONV(clong2, clong2)
_AS_CONV(clong, clong)

_AS_CONV(cdouble8, cdouble8)
_AS_CONV(cdouble4, cdouble4)
_AS_CONV(cdouble2, cdouble2)
_AS_CONV(cdouble, cdouble)

_AS_CONV(cint8, cint8)
_AS_CONV(cint4, cint4)
_AS_CONV(cint2, cint2)
_AS_CONV(cint, cint)

_AS_CONV(cfloat8, cfloat8)
_AS_CONV(cfloat4, cfloat4)
_AS_CONV(cfloat2, cfloat2)
_AS_CONV(cfloat, cfloat)

_AS_CONV(cshort16, cshort16)
_AS_CONV(cshort8, cshort8)
_AS_CONV(cshort4, cshort4)
_AS_CONV(cshort2, cshort2)
_AS_CONV(cshort, cshort)

_AS_CONV(cchar32, cchar32)
_AS_CONV(cchar16, cchar16)
_AS_CONV(cchar8, cchar8)
_AS_CONV(cchar4, cchar4)
_AS_CONV(cchar2, cchar2)
_AS_CONV(cchar, cchar)

/*-----------------------------------------------------------------------------
* Conversion casts
*-----------------------------------------------------------------------------*/
using _c70_he_detail::__convert_long16;
using _c70_he_detail::__convert_long8;
using _c70_he_detail::__convert_long4;
using _c70_he_detail::__convert_long3;
using _c70_he_detail::__convert_long2;
using _c70_he_detail::__convert_long;

using _c70_he_detail::__convert_ulong16;
using _c70_he_detail::__convert_ulong8;
using _c70_he_detail::__convert_ulong4;
using _c70_he_detail::__convert_ulong3;
using _c70_he_detail::__convert_ulong2;
using _c70_he_detail::__convert_ulong;

using _c70_he_detail::__convert_double16;
using _c70_he_detail::__convert_double8;
using _c70_he_detail::__convert_double4;
using _c70_he_detail::__convert_double3;
using _c70_he_detail::__convert_double2;
using _c70_he_detail::__convert_double;

using _c70_he_detail::__convert_int16;
using _c70_he_detail::__convert_int8;
using _c70_he_detail::__convert_int4;
using _c70_he_detail::__convert_int3;
using _c70_he_detail::__convert_int2;
using _c70_he_detail::__convert_int;

using _c70_he_detail::__convert_uint16;
using _c70_he_detail::__convert_uint8;
using _c70_he_detail::__convert_uint4;
using _c70_he_detail::__convert_uint3;
using _c70_he_detail::__convert_uint2;
using _c70_he_detail::__convert_uint;

using _c70_he_detail::__convert_float16;
using _c70_he_detail::__convert_float8;
using _c70_he_detail::__convert_float4;
using _c70_he_detail::__convert_float3;
using _c70_he_detail::__convert_float2;
using _c70_he_detail::__convert_float;

using _c70_he_detail::__convert_short32;
using _c70_he_detail::__convert_short16;
using _c70_he_detail::__convert_short8;
using _c70_he_detail::__convert_short4;
using _c70_he_detail::__convert_short3;
using _c70_he_detail::__convert_short2;
using _c70_he_detail::__convert_short;

using _c70_he_detail::__convert_ushort32;
using _c70_he_detail::__convert_ushort16;
using _c70_he_detail::__convert_ushort8;
using _c70_he_detail::__convert_ushort4;
using _c70_he_detail::__convert_ushort3;
using _c70_he_detail::__convert_ushort2;
using _c70_he_detail::__convert_ushort;

using _c70_he_detail::__convert_char64;
using _c70_he_detail::__convert_char32;
using _c70_he_detail::__convert_char16;
using _c70_he_detail::__convert_char8;
using _c70_he_detail::__convert_char4;
using _c70_he_detail::__convert_char3;
using _c70_he_detail::__convert_char2;
using _c70_he_detail::__convert_char;

using _c70_he_detail::__convert_uchar64;
using _c70_he_detail::__convert_uchar32;
using _c70_he_detail::__convert_uchar16;
using _c70_he_detail::__convert_uchar8;
using _c70_he_detail::__convert_uchar4;
using _c70_he_detail::__convert_uchar3;
using _c70_he_detail::__convert_uchar2;
using _c70_he_detail::__convert_uchar;

using _c70_he_detail::__convert_bool64;
using _c70_he_detail::__convert_bool32;
using _c70_he_detail::__convert_bool16;
using _c70_he_detail::__convert_bool8;
using _c70_he_detail::__convert_bool4;
using _c70_he_detail::__convert_bool3;
using _c70_he_detail::__convert_bool2;
using _c70_he_detail::__convert_bool;

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

#endif /* VECTOR_H */
