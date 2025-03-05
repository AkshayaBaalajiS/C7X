/*****************************************************************************/
/*  CPU_REG_CONFIG.H                                                         */
/*                                                                           */
/* Copyright (c) 2020 Texas Instruments Incorporated                         */
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
#ifndef __CPU_REG_CONFIG_H__
#define __CPU_REG_CONFIG_H__

/*** START CG REPLACE ***/
#include <stdint.h>
#include <stdio.h>
#include <ti_he_impl/c7x_core_global.h>
/*** END CG REPLACE ***/
#include <algorithm>
#include <string>
#define DEFULT_VVECTOR_WIDTH    ( 16 )    // Words in a vector


// C7x Architectures
enum c7x_isa_t
{
  C7X_ISA_NONE  = 0,  /* Seen when running a GNU RISCV test */
  C7X_ISA_7100  = 1,  /* Will never change */
  C7X_ISA_7120  = 2,  /* Can't change after 2.0.0 release, don't expect it to anyway */
  C7X_ISA_7502  = 3,  /* I only think this could change if the ATC project dies */
  C7X_ISA_7504  = 4,  /* Presumptively in there, depends on if it makes it to release or not */
  C7X_ISA_7508  = 5,  /* Presumptively in there, depends on if it makes it to release or not */
  C7X_ISA_7514  = 6,  /* Presumptively in there, depends on if it makes it to release or not */
  C7X_ISA_7524  = 7,  /* Presumptively in there, depends on if it makes it to release or not */
  C7X_ISA_7542  = 8,  /* Presumptively in there, depends on if it makes it to release or not */
  C7X_ISA_7548  = 9,  /* Presumptively in there, depends on if it makes it to release or not */
};

// MMA Architectures
enum mma_isa_t
{
  MMA_ISA_NONE  = 0,  /* J7ES MMA      */
  MMA_ISA_MMA1  = 1,  /* J7ES MMA      */
  MMA_ISA_MMA2  = 2,  /* J7AEP/AHP MMA */
  MMA_ISA_MMA2R = 3,  /* AM67 MMA      */
  MMA_ISA_MMA2S = 4,  /* Sparse MMA    */

  MAX_SINGLE_MMA_ISA   = 0x80000000,   /* Single version MMA should never get past this point */
                                       /* Dual version MMAs should include this bit */
  MMA_ISA_MMA2x2       = MAX_SINGLE_MMA_ISA | MMA_ISA_MMA2,  /* x2 J7AEP/AHP MMA */

};

inline c7x_isa_t str_to_isa( std::string& str )
{
  if ( str == "C7X_ISA_NONE" ) return C7X_ISA_NONE;
  if ( str == "C7X_ISA_7100" ) return C7X_ISA_7100;
  if ( str == "C7X_ISA_7120" ) return C7X_ISA_7120;
  if ( str == "C7X_ISA_7502" ) return C7X_ISA_7502;
  if ( str == "C7X_ISA_7504" ) return C7X_ISA_7504;
  if ( str == "C7X_ISA_7508" ) return C7X_ISA_7508;
  if ( str == "C7X_ISA_7514" ) return C7X_ISA_7514;
  if ( str == "C7X_ISA_7524" ) return C7X_ISA_7524;
  if ( str == "C7X_ISA_7542" ) return C7X_ISA_7542;
  if ( str == "C7X_ISA_7548" ) return C7X_ISA_7548;

  fprintf( stderr, "ERROR: unknown ISA: %s\n", str.c_str( ) );

  return C7X_ISA_NONE;
}

inline std::string isa_to_str( c7x_isa_t isa )
{
  if ( isa == C7X_ISA_NONE ) return "C7X_ISA_NONE";
  if ( isa == C7X_ISA_7100 ) return "C7X_ISA_7100";
  if ( isa == C7X_ISA_7120 ) return "C7X_ISA_7120";
  if ( isa == C7X_ISA_7502 ) return "C7X_ISA_7502";
  if ( isa == C7X_ISA_7504 ) return "C7X_ISA_7504";
  if ( isa == C7X_ISA_7508 ) return "C7X_ISA_7508";
  if ( isa == C7X_ISA_7514 ) return "C7X_ISA_7514";
  if ( isa == C7X_ISA_7524 ) return "C7X_ISA_7524";
  if ( isa == C7X_ISA_7542 ) return "C7X_ISA_7542";
  if ( isa == C7X_ISA_7548 ) return "C7X_ISA_7548";

  fprintf( stderr, "ERROR: unknown ISA: %d\n", (uint32_t) isa );

  return "";
}

inline mma_isa_t mma_str_to_isa( std::string& str )
{
  std::transform( str.begin( ), str.end( ), str.begin( ), ::toupper );

  if ( str == "MMA_ISA_NONE"   ) return MMA_ISA_NONE;
  if ( str == "MMA_ISA_MMA1"   ) return MMA_ISA_MMA1;
  if ( str == "MMA_ISA_MMA2"   ) return MMA_ISA_MMA2;
  if ( str == "MMA_ISA_MMA2R"  ) return MMA_ISA_MMA2R;
  if ( str == "MMA_ISA_MMA2S"  ) return MMA_ISA_MMA2S;
  if ( str == "MMA_ISA_MMA2X2" ) return MMA_ISA_MMA2x2;

  fprintf( stderr, "ERROR: unknown MMA ISA: %s\n", str.c_str( ) );

  return MMA_ISA_NONE ;
}

struct cpu_reg_config
{
  cpu_reg_config( )
  {
    init( C7X_ISA_NONE );
  }

  cpu_reg_config( c7x_isa_t _isa )
  {
    init( _isa );
  }

  c7x_isa_t   isa;                      // ISA being used
  mma_isa_t   mma_isa;                  // MMA being used
  uint8_t     word_bit_size;            // Bits in a word
  uint8_t     words_in_scalar_reg;      // Words in a scalar register
  uint8_t     words_in_vector_reg;      // Words in a vector register
  uint8_t     words_in_predicate_reg;   // Words in a predicate register
  uint8_t     words_in_control_reg;     // Words in a control vector register
  uint8_t     words_in_sacr_reg;        // Words in SA control registers
  uint8_t     words_in_se_template;     // Words in SE template
  uint8_t     words_in_se_reg;          // Words in SE registers
  uint8_t     words_in_mma_reg;         // Words in MMA register

  uint8_t     num_a_regs;         // A global registers
  uint8_t     num_al_regs;        // AL registers
  uint8_t     num_am_regs;        // AM registers
  uint8_t     num_d_regs;         // D registers
  uint8_t     num_b_regs;         // B global vector registers
  uint8_t     num_bl_regs;        // BL vector registers
  uint8_t     num_bm_regs;        // BM vector registers
  uint8_t     num_cucr_regs;      // C unit control registers
  uint8_t     num_pred_regs;      // Predicate registers
  uint8_t     num_sa_regs;        // SA control registers
  uint8_t     num_se_regs;        // SE control registers

  uint32_t    ilut_row_width;     // Bytes
  uint32_t    ilut_num_rows;
  uint32_t    ilut_num_tables;

  inline uint32_t get_VEC_BIT_SIZE    ( ) const { return bits_in_vector_reg;          }
  inline uint32_t get_NUM_BYTE_VEC    ( ) const { return bytes_in_vector_reg;         }
  inline uint32_t get_NUM_HWORD_VEC   ( ) const { return hwords_in_vector_reg;        }
  inline uint32_t get_NUM_WORD_VEC    ( ) const { return words_in_vector_reg;         }
  inline uint32_t get_NUM_DWORD_VEC   ( ) const { return dwords_in_vector_reg;        }
  inline uint32_t get_NUM_BYTE_DVEC   ( ) const { return bits_in_double_vector_reg;   }
  inline uint32_t get_NUM_HWORD_DVEC  ( ) const { return hwords_in_double_vector_reg; }
  inline uint32_t get_NUM_WORD_DVEC   ( ) const { return words_in_double_vector_reg;  }
  inline uint32_t get_NUM_DWORD_DVEC  ( ) const { return dwords_in_double_vector_reg; }

  inline execution_mode_t get_initial_mode( ) const
  {
    execution_mode_t mode;

    switch( isa )
    {
      case C7X_ISA_NONE :
      case C7X_ISA_7100 :
      case C7X_ISA_7120 :
        mode = emSS;
        break;
      case C7X_ISA_7502 :
      case C7X_ISA_7504 :
      case C7X_ISA_7508 :
      case C7X_ISA_7514 :
      case C7X_ISA_7524 :
      case C7X_ISA_7542 :
      case C7X_ISA_7548 :
        mode = emS;
        break;
      default :
        fprintf( stderr, "ERROR in %s: Unknown execution mode\n", __FUNCTION__ );
        exit( 1 );
    }

    return mode;
  }

  inline void set_mma_isa( mma_isa_t misa )
  {
    mma_isa = misa;
  }

  inline void set_mma_isa( std::string mma_str )
  {
    mma_isa = mma_str_to_isa( mma_str );
  }

  // Derived parameters
  private:
  void init( c7x_isa_t _isa )
  {
    uint8_t words_in_vector;

    isa = _isa;

         if ( isa == C7X_ISA_NONE )  words_in_vector = DEFULT_VVECTOR_WIDTH;
    else if ( isa == C7X_ISA_7100 )  words_in_vector = 16;
    else if ( isa == C7X_ISA_7120 )  words_in_vector = 16;
    else if ( isa == C7X_ISA_7502 )  words_in_vector = 4;
    else if ( isa == C7X_ISA_7504 )  words_in_vector = 8;
    else if ( isa == C7X_ISA_7508 )  words_in_vector = 16;
    else if ( isa == C7X_ISA_7514 )  words_in_vector = 8;
    else if ( isa == C7X_ISA_7524 )  words_in_vector = 8;
    else if ( isa == C7X_ISA_7542 )  words_in_vector = 4;
    else if ( isa == C7X_ISA_7548 )  words_in_vector = 16;
    else
    {
      fprintf( stderr, "Unknown ISA\n" );
      exit( 1 );
    }

    word_bit_size            = 32;
    words_in_scalar_reg      = 2;
    words_in_vector_reg      = words_in_vector;
    words_in_predicate_reg   = 2;
    words_in_control_reg     = words_in_vector;
    words_in_sacr_reg        = 16;
    words_in_se_template     = 16;
    words_in_se_reg          = words_in_vector;
    if ( ( isa == C7X_ISA_7524 ) || ( isa == C7X_ISA_7542 ) || ( isa == C7X_ISA_7548 ) ) words_in_se_reg = words_in_se_reg * 2;
    words_in_mma_reg         = 16;
    num_a_regs               = 16;
#ifdef RISCV
    num_al_regs              = 16;
    num_am_regs              = 16;
#else
    num_al_regs              = 8;
    num_am_regs              = 8;
#endif
    num_d_regs               = 16;
    num_b_regs               = 16;
    num_bl_regs              = 8;
    num_bm_regs              = 8;

         if ( isa == C7X_ISA_NONE )  num_cucr_regs = 4;
    else if ( isa == C7X_ISA_7100 )  num_cucr_regs = 4;
    else if ( isa == C7X_ISA_7120 )  num_cucr_regs = 4;
    else if ( isa == C7X_ISA_7502 )  num_cucr_regs = 16;
    else if ( isa == C7X_ISA_7504 )  num_cucr_regs = 8;
    else if ( isa == C7X_ISA_7508 )  num_cucr_regs = 4;
    else if ( isa == C7X_ISA_7514 )  num_cucr_regs = 8;
    else if ( isa == C7X_ISA_7524 )  num_cucr_regs = 8;
    else if ( isa == C7X_ISA_7542 )  num_cucr_regs = 16;
    else if ( isa == C7X_ISA_7548 )  num_cucr_regs = 4;
    else
    {
      fprintf( stderr, "Unknown ISA\n" );
      exit( 1 );
    }

    num_pred_regs            = 8;
    num_sa_regs              = 4;
    num_se_regs              = 2;

         if ( isa == C7X_ISA_NONE )  mma_isa = MMA_ISA_NONE;
    else if ( isa == C7X_ISA_7100 )  mma_isa = MMA_ISA_MMA1;
    else if ( isa == C7X_ISA_7120 )  mma_isa = MMA_ISA_MMA2;
    else if ( isa == C7X_ISA_7502 )  mma_isa = MMA_ISA_MMA2;
    else if ( isa == C7X_ISA_7504 )  mma_isa = MMA_ISA_MMA2;
    else if ( isa == C7X_ISA_7508 )  mma_isa = MMA_ISA_MMA2;
    else if ( isa == C7X_ISA_7514 )  mma_isa = MMA_ISA_MMA2;
    else if ( isa == C7X_ISA_7524 )  mma_isa = MMA_ISA_MMA2x2;
    else if ( isa == C7X_ISA_7542 )  mma_isa = MMA_ISA_MMA2x2;
    else if ( isa == C7X_ISA_7548 )  mma_isa = MMA_ISA_MMA2x2;
    else
    {
      fprintf( stderr, "Unknown ISA\n" );
      exit( 1 );
    }

    ilut_row_width = 0;
         if ( isa == C7X_ISA_7514 ) ilut_row_width = 32;
    else if ( isa == C7X_ISA_7524 ) ilut_row_width = 32;
    else if ( isa == C7X_ISA_7542 ) ilut_row_width = 16;
    else if ( isa == C7X_ISA_7548 ) ilut_row_width = 64;
    ilut_num_rows = 0;
         if ( isa == C7X_ISA_7514 ) ilut_num_rows = 256;
    else if ( isa == C7X_ISA_7524 ) ilut_num_rows = 256;
    else if ( isa == C7X_ISA_7542 ) ilut_num_rows = 256;
    else if ( isa == C7X_ISA_7548 ) ilut_num_rows = 256;
    ilut_num_tables = 0;
         if ( isa == C7X_ISA_7514 ) ilut_num_tables = 1;
    else if ( isa == C7X_ISA_7524 ) ilut_num_tables = 1;
    else if ( isa == C7X_ISA_7542 ) ilut_num_tables = 1;
    else if ( isa == C7X_ISA_7548 ) ilut_num_tables = 1;

    compute_derived_params( );
  }

/*** START CG ADD ***/
  public:
/*** END CG ADD ***/
  // This function computes any derived parameter
  inline void  compute_derived_params( )
  {
    bits_in_vector_reg   = word_bit_size * words_in_vector_reg;
    bytes_in_vector_reg  = bits_in_vector_reg / 8 ;
    hwords_in_vector_reg = words_in_vector_reg * 2;
    dwords_in_vector_reg = words_in_vector_reg / 2;

    bits_in_double_vector_reg    = bits_in_vector_reg   * 2;
    bytes_in_double_vector_reg   = bytes_in_vector_reg  * 2;
    hwords_in_double_vector_reg  = hwords_in_vector_reg * 2;
    words_in_double_vector_reg   = words_in_vector_reg  * 2;
    dwords_in_double_vector_reg  = dwords_in_vector_reg * 2;
  }

/*** START CG ADD ***/
  private:
/*** END CG ADD ***/
  uint32_t    bits_in_vector_reg;
  uint32_t    bytes_in_vector_reg;
  uint32_t    hwords_in_vector_reg;
  uint32_t    dwords_in_vector_reg;
  uint32_t    bits_in_double_vector_reg;
  uint32_t    bytes_in_double_vector_reg;
  uint32_t    hwords_in_double_vector_reg;
  uint32_t    words_in_double_vector_reg;
  uint32_t    dwords_in_double_vector_reg;

};

#endif /* __CPU_REG_CONFIG_H__ */
