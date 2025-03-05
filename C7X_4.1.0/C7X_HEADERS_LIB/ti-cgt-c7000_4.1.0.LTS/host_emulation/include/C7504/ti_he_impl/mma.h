/*****************************************************************************/
/* MMA.H                                                                     */
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
#ifndef _MMA_H_
#define _MMA_H_

#include <stdio.h>
#include <string>
#include <sstream>
/*** START CG REPLACE ***/
#include <ti_he_impl/vreg.h>
#if 0
#include <include/c7x_core_global.h>
#endif
#include <ti_he_impl/vector.h>
#include <ti_he_impl/cpu_reg_config.h>
#include <ti_he_impl/arch_decl.h>
#include <ti_he_impl/arch128_decl.h>
#include <ti_he_impl/uarch_decl.h>
/*** END CG REPLACE ***/

class mma 
{
  public:
    inline std::string     name()                            { return _name;               }
    inline uint32_t        get_id()                          { return _id;                 }
    static void            set_debug_level(int lvl )         { _debug_level = lvl;         }
    static void            set_exception_backtrace(int lvl ) { _exception_backtrace = lvl; }

    void                   reset ();

    // This function is called on every CPU cycle for timing purposes
    void                   advance ();

    // This function is called after execute packets to completely evaluate the execute packet
    void                   advance_all ();

    // These functions access internal state by name
    void                   inspect( uint32_t           *result , std::string statename) ;
    void                   inspect( vreg<NUM_WORD_VEC> *result , std::string statename) ;

    // this is the instruction API
    void                   mma_hwalda( vreg_t src1 ) ;
    void                   mma_hwaldab( vreg_t src1 , vreg_t src2 ) ;
    void                   mma_hwaldb( vreg_t src1 ) ;
    void                   mma_hwaldc( vreg_t src1 ) ;
    void                   mma_hwaldbc( vreg_t src1 , vreg_t src2 ) ;
    void                   mma_hwaop( ) ;
    void                   mma_hwaop( int imm ) ;
    void                   mma_hwaopxfer( ) ;
    void                   mma_hwaopxfer( int imm ) ;
    void                   mma_hwaopxfer( int imm , uint64_t drm ) ;
    void                   mma_hwaxfer( int imm ) ;
    void                   mma_hwaxfer( int imm , uint64_t drm ) ;
    void                   mma_hwarcv( int hwaregindex ) ;
    int                    mma_hwarcv_loki( vreg<NUM_WORD_VEC> *reg , int hwaregindex ) ;  // DES 14 aug 2017: this was void
    int                    mma_hwarcv_loki_nocommit( vreg<NUM_WORD_VEC> *reg , int hwaregindex ) ;  // DES 7 aug 2020: hwarcv and don't update state
    void                   mma_hwarcv_loki_commit() ;  // DES 7 aug 2020: hwarcv and update state. nothing returned
    void                   mma_hwaopen( vreg_t src1 , vreg_t src2 , int dst ) ;
    void                   mma_hwareset( int imm ) ;
    void                   mma_hwaclose() ;
    void                   mma_pop_x() ;
    void                   mma_errorcode_update( uint32_t errorcode ) ;

    // Constructor
    mma ( uint32_t id, const std::string name , const cpu_reg_config& reg_config ):
      _name ( name )
    , _id   ( id   )
    {
     extern void mma_fail() ;
     _words_in_vector_reg = reg_config.words_in_vector_reg ;
     _bits_in_vector_reg  = reg_config.word_bit_size * reg_config.words_in_vector_reg  ;
     _words_in_mma_reg    = reg_config.words_in_mma_reg    ; 

     _mma_128             = _bits_in_vector_reg == 128     ; 
     _mma_256             = _bits_in_vector_reg == 256     ; 
     _mma_512             = _bits_in_vector_reg == 512     ; 

     _mma1                = 0 ;
     _mma2                = 0 ;
     _mma2r               = 0 ;
     _mma2s               = 0 ;

     auto mma_version = reg_config.mma_isa;
     if (reg_config.mma_isa & MAX_SINGLE_MMA_ISA )
     {
       mma_version = (mma_isa_t) ( (uint32_t) mma_version - MAX_SINGLE_MMA_ISA );
     }
     if        ( (mma_version == MMA_ISA_NONE) || (mma_version == MMA_ISA_MMA1)  ) {
      if ( mma_version == MMA_ISA_NONE ) {
       fprintf( stderr , "%s warning: (%s) MMA constructor called with reg_config.mma_isa == MMA_ISA_NONE ISA, defaulting to MMA1 behavior\n" , _name.c_str( ), __FUNCTION__ ) ;
      }
      _mma1 = 1 ;
     } else if ( mma_version == MMA_ISA_MMA2  ) {
      _mma2 = 1 ;
     } else if ( mma_version == MMA_ISA_MMA2R ) {
      _mma2r = 1 ;
     } else if ( mma_version == MMA_ISA_MMA2S ) {
      _mma2s = 1 ;
     } else {
      fprintf( stderr , "%s warning: (%s) unknown reg_config.mma_isa enumerated value, assuming MMA_ISA_MMA2.\n" , _name.c_str( ), __FUNCTION__ ) ;
      _mma2 = 1 ;
      // mma_fail() ;
     }
  
     // per-width pipeline depths
     if ( _mma_512 )        {
      _mma_c_pipeline_stages  = MMA_C_PIPELINE_STAGES ;
      _mma_x_pipeline_stages  = MMA_X_PIPELINE_STAGES ;
      _mma_r_pipeline_stages  = MMA_R_PIPELINE_STAGES ;
     } else if ( _mma_256 ) {
      // just making this one up
      // DES 23 June 2021:  not making this up now; pipeline depth is 4 less than 512b version
      _mma_c_pipeline_stages  = MMA_C_PIPELINE_STAGES-4 ; // remove 4 stages
      _mma_x_pipeline_stages  = MMA_X_PIPELINE_STAGES ; // no change in output pipeline
      _mma_r_pipeline_stages  = MMA_R_PIPELINE_STAGES ; // no change for output FIFO read
     } else if ( _mma_128 ) {
      _mma_c_pipeline_stages  = MMA_C_PIPELINE_STAGES-4 ; // same as 256b version
      _mma_x_pipeline_stages  = MMA_X_PIPELINE_STAGES   ; // same as 256b version
      _mma_r_pipeline_stages  = MMA_R_PIPELINE_STAGES ; // no change for output FIFO read
     }

     // bcope 8 Nov 2023: Initialize xmin/max accumulators to resolve debug=3 valgrind
     // issue during first hwaopen pipeup
     for (int i=0; i<9; i++) {
      _xmin_accumulator[i] = 0;
      _xmax_accumulator[i] = 0;
     }

     mma::reset() ;
    } 
      
    virtual ~mma () { }

    vreg<NUM_WORD_VEC>     mma_result              ;  
    int                    mma_status              ;  
    int                    mma_valid               ;  

    // internal fsms
    void                   a_fsm()                 ;
    void                   b_fsm()                 ;
    void                   c_fsm()                 ;
    void                   x_fsm()                 ;
    void                   confign_fsm()           ;
    void                   statusn_fsm()           ;
    void                   hwaopen_ctrl()          ;
    void                   hwaopen_partial()       ;
    void                   hwaopen_a_fsm(int)      ;
    void                   hwaopen_b_fsm(int)      ;
    void                   hwaopen_c_fsm(int)      ;
    void                   hwaopen_x_fsm(int)      ;
    void                   advance_c_pipeline()    ;
    void                   advance_x_pipeline()    ;
    void                   advance_r_pipeline()    ;
    uint64_t               b_offset(int)           ;
    void                   sp_fields(uint32_t *s, uint32_t *e, uint32_t *m, uint32_t f) ;
    void                   ieee_float_product(uint32_t *A, int bbank, uint32_t *r, uint32_t *ulp);
    void                   float_product(uint32_t *a, int bbank, uint32_t *r) ;
    void                   float_accumulate(uint8_t *cwvec, uint32_t *left, uint32_t *right, int sub) ;
    void                   float_error_check(uint32_t *exp, uint32_t *act, uint32_t *ulp);

    // MMA properties
    std::string            _name                   ;
    uint64_t               _cycle                  ;
    uint32_t               _id                     ;
    uint8_t                _words_in_vector_reg    ; // Words in a vector register from reg_config
    uint8_t                _words_in_mma_reg       ; // Words in MMA register from reg_config
    int                    _bits_in_vector_reg     ; // Bits in a vector register from reg_config

    uint8_t                _mma_128                ; // boolean for 128b  architecture
    uint8_t                _mma_256                ; // boolean for 256b  architecture
    uint8_t                _mma_512                ; // boolean for 512b  architecture
    uint8_t                _mma1                   ; // boolean for mma1  architecture
    uint8_t                _mma2                   ; // boolean for mma2  architecture
    uint8_t                _mma2r                  ; // boolean for mma2r architecture
    uint8_t                _mma2s                  ; // boolean for mma2s architecture

    uint8_t                _mma_c_pipeline_stages  ; // pipeline depth depends on vector width
    uint8_t                _mma_x_pipeline_stages  ; // pipeline depth depends on vector width
    uint8_t                _mma_r_pipeline_stages  ; // pipeline depth depends on vector width

    static int             _debug_level            ;
    static int             _exception_backtrace    ;
    int                    _hwalda                 ;
    int                    _hwaldab                ;
    int                    _hwaldb                 ;
    int                    _hwaldc                 ;
    int                    _hwaldbc                ;
    int                    _hwaop                  ;
    int                    _hwaopxfer              ;
    int                    _hwaxfer                ;
    int                    _hwarcv                 ;
    int                    _hwaopen_ctrl_a         ; // normal case
    int                    _hwaopen_partial_a      ; // period updates with advance
    int                    _hwaclose               ;
    int                    _bias01_count           ;
    int                    _bias23_count           ;
    int                    _scale01_count          ;
    int                    _shift01_count          ;
    int                    _scaleshift0_count      ;
    int                    _scaleshift1_count      ;
    int                    _confign_seg_next       ; // next config segment to be accessed for MMA-128 xfer confign instructions
    int                    _statusn_seg_next       ; // next status segment to be accessed for MMA-128 xfer statusn instructions

    vreg<NUM_WORD_VEC>     _src1                   ;  // incomming left operand
    vreg<NUM_WORD_VEC>     _src2                   ;  // incomming right operand
    int                    _hwaxfer_arg            ;  // hwaxfer instruction argument
    uint64_t               _hwaxfer_drm            ;  // hwaxfer dynamic range mask
    int                    _hwaop_arg              ;  // hwaop/hwaopxfer arg

    uint8_t                _hwa_config[VEC_BIT_SIZE]     ;  // all the bits of hwa_config
    uint8_t                _a_config_parity              ;  // parity over A FSM bits
    uint8_t                _b_config_parity              ;  // parity over B FSM bits
    uint8_t                _c_config_parity              ;  // parity over C FSM bits
    uint8_t                _x_config_parity              ;  // parity over X FSM bits
    uint8_t                _hwa_offset_parity            ;  // parity over X FSM bits
    uint8_t                _hwa_offset[VEC_BIT_SIZE]     ;  // all the bits of hwa_offset
    uint8_t                _hwa_status[VEC_BIT_SIZE]     ;  // all the bits of hwa_status
    uint8_t                _mma_busy[VEC_BIT_SIZE]       ;  // used in hwarcv

    uint8_t                _A[VEC_BIT_SIZE]              ;
    uint8_t                _ARF[A_FSM_PARAM_ARF_ENTRIES][VEC_BIT_SIZE]   ; // DES 23 april 2019: MMA 2.0 A operand storage
    uint8_t                _arf_initialized[A_FSM_PARAM_ARF_ENTRIES]     ; // DES  3 dec   2020: flag for uninitialized access

    uint8_t                _B[MMA_BBANKS][MMA_BROWS][VEC_BIT_SIZE  ]     ;
    uint16_t               _b8[MMA_BBANKS][MMA_BROWS][MMA_BCOLS     ]    ;
    uint32_t               _b16[MMA_BBANKS][MMA_BROWS/2][MMA_BCOLS/2]    ;
    uint64_t               _b32[MMA_BBANKS][MMA_BROWS/4][MMA_BCOLS/4]    ;
    uint16_t               _b_dirty[MMA_BBANKS]                          ;
    uint8_t                _B_min_row_valid[MMA_BBANKS]                  ;
    uint8_t                _B_max_row_valid[MMA_BBANKS]                  ;
    uint8_t                _B_min_col_valid[MMA_BBANKS]                  ;
    uint8_t                _B_max_col_valid[MMA_BBANKS]                  ;

    uint8_t                _C[MMA_CBANKS][MMA_CROWS][VEC_BIT_SIZE*4]     ;
    uint8_t                _BIAS[4][VEC_BIT_SIZE]                        ; // DES 23 april 2019: MMA 2.0 HWA_BIAS[0:3] storage
    uint8_t                _SCALE[4][VEC_BIT_SIZE]                       ; // DES 9 september 2020: MMA output scale
    uint8_t                _SHIFT[4][VEC_BIT_SIZE]                       ; // DES 9 september 2020: MMA output post-scale shift
    uint64_t               _C_ts[MMA_CBANKS][MMA_CROWS]                  ; // DES 20 july 2017: C row timestamp
    uint64_t               _xmin_accumulator[9]                          ; 
    uint64_t               _xmax_accumulator[9]                          ; 
    uint8_t                _X[MMA_X_DEPTH][VEC_BIT_SIZE]                 ;
    uint8_t                _xvalid[MMA_X_DEPTH]                          ; // transfer buffer valid bits
    uint8_t                _x_of_q                                       ; 
    uint8_t                _x_of_qq                                      ; 
    uint8_t                _x_uf_q                                       ; 
    uint8_t                _x_uf_qq                                      ; 
    uint8_t                _A_valid                                      ; // DES 7 aug 2021: persistence warning
                                                        
    uint8_t                _a_fsm_state                  ;
    uint8_t                _b_fsm_state                  ;
    uint8_t                _c_fsm_state                  ;
    uint8_t                _x_fsm_state                  ;
    uint8_t                _confign_fsm_state            ;
    uint8_t                _statusn_fsm_state            ;

    // this is the control pipeline for the accumulator operation and result processing pipeline element
    struct c_pipeline_stage {
      // these fields are related to the C FSM
      uint8_t             c_valid                        ;
      struct c_payload {
       uint8_t             prod[VEC_BIT_SIZE*4]          ;
       uint8_t             bias[4][VEC_BIT_SIZE]         ; // pipelined bias values
       uint8_t             lop                           ;
       uint8_t             op                            ;
       uint8_t             biasorder                     ;
       uint8_t             bbank                         ;
       uint8_t             crbank                        ;
       uint8_t             crrow                         ;
       uint8_t             cwbank                        ;
       uint8_t             cwrow                         ;
       uint8_t             btype                         ;
       uint8_t             atype                         ;
      } cp ; // C FSM pipelined payload
      // these fields are related to the X FSM
      uint8_t             x_valid                        ;
      struct x_payload {
       uint8_t             arg                           ;
       uint8_t             ctype                         ;
       uint8_t             xtype                         ;
       uint8_t             shift                         ;
       uint8_t             re                            ;
       uint8_t             rc                            ; // DES 3 may 2019: range function control
       uint8_t             relu                          ;
       uint8_t             psat                          ;
       uint8_t             sat                           ;
       uint8_t             crow                          ;
       uint8_t             cbank                         ;
       uint32_t            sat_max                       ;
       uint32_t            sat_min                       ;
       uint64_t            drm                           ;
       uint8_t             ss_en                         ; // DES 11 sep 2020: ss (scale_shift) fields. ss_en is enable
       uint8_t             ss_ss                         ; // signed scale
       uint8_t             ss_scale[64]                  ; // scale vector (col/row resolved here)
       uint8_t             ss_shift[64]                  ; // shift vector (col/row resolved here)
      } xp ; // X FSM pipeline payload
    } ;
    struct c_pipeline_stage _cpl[MMA_C_PIPELINE_STAGES]  ;

    // this is the transfer buffer write pipeline element
    struct x_pipeline_stage {
      uint8_t             write_data[VEC_BIT_SIZE]       ;
      uint8_t             x_valid                        ;
      uint8_t             c_read_error                   ;
      uint8_t             c_write_error                  ;
    } ;
    struct x_pipeline_stage _xpl[MMA_X_PIPELINE_STAGES]  ;

    // this is the transfer buffer write pipeline element
    struct r_pipeline_stage {
      uint8_t             result[VEC_BIT_SIZE]           ;
      uint8_t             xrrow                          ;
      uint8_t             status                         ;
      uint8_t             r_valid                        ;
    } ;
    struct r_pipeline_stage _rpl[MMA_R_PIPELINE_STAGES]  ;

    // hazard detection flags
    uint8_t                _b_write[2]                   ;
    uint8_t                _b_read[2]                    ;
    uint8_t                _c_write[2]                   ;
    uint8_t                _c_read[2]                    ;
    uint8_t                _x_access[2]                  ;

    // address trace strings
    char                  _xr_str[20]                    ;
    char                  _xw_str[20]                    ;
    char                  _xcr_str[20]                   ;
    char                  _ccr_str[20]                   ;
    char                  _ccw_str[20]                   ;
    char                  _ccl_str[20]                   ;
    char                  _op_str[20]                    ;
    char                  _aaw_str[20]                   ;
    char                  _bbw_str[20]                   ;

}; //end of mma class

#endif
