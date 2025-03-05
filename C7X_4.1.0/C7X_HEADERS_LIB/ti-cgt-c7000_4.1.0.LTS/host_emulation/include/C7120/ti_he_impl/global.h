/*****************************************************************************/
/*  GLOBAL.H                                                                 */
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
#ifndef _GLOBAL_H
#define _GLOBAL_H

#include <stdint.h>
#include <string>
#include <vector>
#include <utility>
#include <cassert>

typedef uint32_t uword;
typedef int32_t  word;

typedef struct {
  uword low;
  uword high;
} dword;

typedef struct {
  uword word0;
  uword word1;
  uword word2;
  uword word3;
} qword;

typedef struct {
  long long  low ;
  long long  high ;
} two_longlong ;

struct uint128_type
{
  uint64_t low;
  uint64_t high;
};

typedef struct uint128_type uint128_t;

enum fp_type_t : uint8_t
{
    FT_NUM,
    FT_ZERO,
    FT_INF,
    FT_NAN
};

/*** START CG REPLACE ***/
typedef uint64_t fp_excep_t;
/*** END CG REPLACE ***/
typedef uint8_t fp_ctrl_t;

const uint8_t  FPE_INVAL       =  (0x1 );
const uint8_t  FPE_DIV0        =  (0x2 );
const uint8_t  FPE_OVER        =  (0x4 );
const uint8_t  FPE_UNDER       =  (0x8 );
const uint8_t  FPE_INEX        =  (0x10);
const uint8_t  FPE_DEN         =  (0x20);
const uint8_t  FPE_UNORD       =  (0x40);
const uint8_t  FPE_SAT         =  (0x80);      // Not actually floating point...
const uint8_t  FC_ROUND_MASK   =  (0x03);
const uint8_t  FC_ROUND_EVEN   =  (0x00);      // Round to nearest even
const uint8_t  FC_ROUND_OFF    =  (0x01);      // Round toward 0 (truncate)
const uint8_t  FC_ROUND_UP     =  (0x02);      // Round toward +Inf (round up)
const uint8_t  FC_ROUND_DOWN   =  (0x03);      // Round toward -Inf (round down)
const uint8_t  FC_FLUSH_ZERO   =  (0x10);      // Enable legacy flush-to-zero mode

/*
enum fp_excep_t : uint8_t 
{
    FPE_INVAL    = 1 << 0,
    FPE_DIV0     = 1 << 1,
    FPE_OVER     = 1 << 2,
    FPE_UNDER    = 1 << 3,
    FPE_INEX     = 1 << 4,
    FPE_DEN      = 1 << 5,
    FPE_UNORD    = 1 << 6,
    FPE_SAT      = 1 << 7       // Not actually floating point...
};

enum fp_ctrl_t : uint8_t
{
    FC_ROUND_MASK = 0x03,
    FC_ROUND_EVEN = 0x00,       // Round to nearest even
    FC_ROUND_OFF  = 0x01,       // Round toward 0 (truncate)
    FC_ROUND_UP   = 0x02,       // Round toward +Inf (round up)
    FC_ROUND_DOWN = 0x03,       // Round toward -Inf (round down)

    FC_FLUSH_ZERO = 0x10        // Enable legacy flush-to-zero mode
};

inline fp_excep_t operator|( const fp_excep_t lhs, const fp_excep_t rhs )
{
    return fp_excep_t( uint8_t( lhs ) | uint8_t( rhs ) );
}

inline fp_excep_t operator&( const fp_excep_t lhs, const fp_excep_t rhs )
{
    return fp_excep_t( uint8_t( lhs ) & uint8_t( rhs ) );
}

inline fp_excep_t& operator|=( fp_excep_t& lhs, const fp_excep_t rhs )
{
    return lhs = fp_excep_t( uint8_t( lhs ) | uint8_t( rhs ) );
}

inline fp_excep_t& operator&=( fp_excep_t& lhs, const fp_excep_t rhs )
{
    return lhs = fp_excep_t( uint8_t( lhs ) & uint8_t( rhs ) );
}

inline constexpr fp_excep_t operator~( fp_excep_t lhs )
{
    return fp_excep_t( ~uint8_t( lhs ) );
}

inline fp_ctrl_t operator|( const fp_ctrl_t lhs, const fp_ctrl_t rhs )
{
    return fp_ctrl_t( uint8_t( lhs ) | uint8_t( rhs ) );
}

inline fp_ctrl_t operator&( const fp_ctrl_t lhs, const fp_ctrl_t rhs )
{
    return fp_ctrl_t( uint8_t( lhs ) & uint8_t( rhs ) );
}

inline fp_ctrl_t& operator|=( fp_ctrl_t& lhs, const fp_ctrl_t rhs )
{
    return lhs = fp_ctrl_t( uint8_t( lhs ) | uint8_t( rhs ) );
}

inline fp_ctrl_t& operator&=( fp_ctrl_t& lhs, const fp_ctrl_t rhs )
{
    return lhs = fp_ctrl_t( uint8_t( lhs ) & uint8_t( rhs ) );
}

inline constexpr fp_ctrl_t operator~( fp_ctrl_t lhs )
{
    return fp_ctrl_t( ~uint8_t( lhs ) );
}
*/

const int16_t  ZERO_EXP = -1000; // Assumed exponent of floating pt zero.
const int16_t  INF_EXP  = 0x1FFFu;  // Exponent guaranteed to be an Infinity

const uint16_t SFPN_HP  = 0x0400u;
const uint16_t LFPN_HP  = 0x7BFFu;
const uint32_t pINF_HP  = 0x7C00u;
const uint32_t nINF_HP  = 0xFC00u;
const uint32_t pQNAN_HP = 0x7FFFu;
const uint32_t nQNAN_HP = 0xFFFFu;
const uint32_t pZERO_HP = 0x0000u;
const uint32_t nZERO_HP = 0x8000u;

const uint32_t SFPN_SP  = 0x00800000u;
const uint32_t LFPN_SP  = 0x7F7FFFFFu;
const uint32_t pINF_SP  = 0x7F800000u;
const uint32_t nINF_SP  = 0xFF800000u;
const uint32_t pQNAN_SP = 0x7FFFFFFFu;
const uint32_t nQNAN_SP = 0xFFFFFFFFu;
const uint32_t pZERO_SP = 0x00000000u;
const uint32_t nZERO_SP = 0x80000000u;

const uint64_t SFPN_DP  = 0x0010000000000000ull;
const uint64_t LFPN_DP  = 0x7FEFFFFFFFFFFFFFull;
const uint64_t pINF_DP  = 0x7FF0000000000000ull;
const uint64_t nINF_DP  = 0xFFF0000000000000ull;
const uint64_t pQNAN_DP = 0x7FFFFFFFFFFFFFFFull;
const uint64_t nQNAN_DP = 0xFFFFFFFFFFFFFFFFull;
const uint64_t pZERO_DP = 0x0000000000000000ull;
const uint64_t nZERO_DP = 0x8000000000000000ull;


typedef struct 
{
    fp_type_t   type;       // type of number (Normal, NaN, Inf, Zero)
    bool        signals;    // Is this an SNaN?
    bool        sign;       // true = '-', false = '+'
    int16_t     exp;        // usually 1 less than exp in packed number
    uint64_t    frac;       // fraction, << 2 for rounding support
} unpack_dp_t;

typedef struct 
{
    fp_type_t   type;       // type of number (Normal, NaN, Inf, Zero)
    bool        signals;    // Is this an SNaN?
    bool        sign;       // true = '-', false = '+'
    int16_t     exp;        // usually 1 less than exp in packed number
    uint32_t    frac;       // fraction, << 2 for rounding support
} unpack_sp_t;

typedef struct 
{
    fp_type_t   type;       // type of number (Normal, NaN, Inf, Zero)
    bool        signals;    // Is this an SNaN?
    bool        sign;       // true = '-', false = '+'
    int16_t     exp;        // usually 1 less than exp in packed number
    uint16_t    frac;       // fraction, << 2 for rounding support
} unpack_hp_t;

//For class_sp/class_dp instructions
#define CLASS_FP_ZERO      0
#define CLASS_FP_SUBNORMAL 1
#define CLASS_FP_NORMAL    2
#define CLASS_FP_INFINITE  3
#define CLASS_FP_NAN       4
#define CLASS_FP_SIGNALS   8

#ifdef USE_COVER_POINT
namespace { 
volatile int cover_point_reached;

#define COVER_POINT(x) \
    do { if (x) cover_point_reached = __LINE__; } while( 0 )

#define CPFPC(x,xt,y,yt) \
    do { \
        COVER_POINT( x.type == xt && y.type == yt &&  x.sign &&  y.sign ); \
        COVER_POINT( x.type == xt && y.type == yt &&  x.sign && !y.sign ); \
        COVER_POINT( x.type == xt && y.type == yt && !x.sign &&  y.sign ); \
        COVER_POINT( x.type == xt && y.type == yt && !x.sign && !y.sign ); \
    } while ( 0 )

#define COVER_POINT_FP_CROSS(x,y) \
    do { \
        CPFPC( x, FT_NUM  , y, FT_NUM  ); \
        CPFPC( x, FT_NUM  , y, FT_ZERO ); \
        CPFPC( x, FT_NUM  , y, FT_INF  ); \
        CPFPC( x, FT_NUM  , y, FT_NAN  ); \
        CPFPC( x, FT_ZERO , y, FT_NUM  ); \
        CPFPC( x, FT_ZERO , y, FT_ZERO ); \
        CPFPC( x, FT_ZERO , y, FT_INF  ); \
        CPFPC( x, FT_ZERO , y, FT_NAN  ); \
        CPFPC( x, FT_INF  , y, FT_NUM  ); \
        CPFPC( x, FT_INF  , y, FT_ZERO ); \
        CPFPC( x, FT_INF  , y, FT_INF  ); \
        CPFPC( x, FT_INF  , y, FT_NAN  ); \
        CPFPC( x, FT_NAN  , y, FT_NUM  ); \
        CPFPC( x, FT_NAN  , y, FT_ZERO ); \
        CPFPC( x, FT_NAN  , y, FT_INF  ); \
        CPFPC( x, FT_NAN  , y, FT_NAN  ); \
    } while ( 0 )

} // namespace
#else
#define COVER_POINT(x)
#define COVER_POINT_FP_CROSS(x,y)
#endif

#endif
