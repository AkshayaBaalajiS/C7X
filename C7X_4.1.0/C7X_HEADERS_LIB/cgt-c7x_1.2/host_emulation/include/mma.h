#ifndef _MMA_H_
#define _MMA_H_

#include <stdio.h>
#include <string>
#include <sstream>
//MAP#include <include/typedefs.h> 
//#include <utils/get_endian.h>
//MAP#include <utils/vreg.h>
//MAP#include <vreg.h>
//#include <core/machine.h>
//#include <core/operands.h>
//#include <core/protected_regs.h>
//#include <utils/tlb.h>
//#include <boost/function.hpp>
//MAP#include <include/c7x_core_global.h>
#include <c7x_c_funcs.h>
#include <vector.h>
//MAP#include "arch_decl.h"
#include "uarch_decl.h"

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
    void                   mma_hwaopxfer( ) ;
    void                   mma_hwaxfer( int imm ) ;
    void                   mma_hwarcv( int hwaregindex ) ;
    int                    mma_hwarcv_loki( vreg<NUM_WORD_VEC> *reg , int hwaregindex ) ;  // DES 14 aug 2017: this was void
    void                   mma_hwaopen( vreg_t src1 , vreg_t src2 , int dst ) ;
    void                   mma_hwaclose() ;
    void                   mma_pop_x() ;
    void                   mma_errorcode_update( uint32_t errorcode ) ;

    // Constructor
    mma ( uint32_t id, const std::string name ):
      _name ( name )
    , _id   ( id   )
    {
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

    // MMA properties
    std::string            _name                   ;
    uint64_t               _cycle                  ;
    uint32_t               _id                     ;
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

    vreg<NUM_WORD_VEC>     _src1                   ;  // incomming left operand
    vreg<NUM_WORD_VEC>     _src2                   ;  // incomming right operand
    int                    _hwaxfer_arg            ;  // hwaxfer instruction argument

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
    uint8_t                _B[MMA_BBANKS][MMA_BROWS][VEC_BIT_SIZE  ]     ;
    uint8_t                _C[MMA_CBANKS][MMA_CROWS][VEC_BIT_SIZE*4]     ;
    uint64_t               _C_ts[MMA_CBANKS][MMA_CROWS]                  ; // DES 20 july 2017: C row timestamp
    uint8_t                _X[MMA_X_DEPTH][VEC_BIT_SIZE]                 ;
    uint8_t                _xvalid[MMA_X_DEPTH]                          ; // transfer buffer valid bits
    uint8_t                _x_of_q                                       ; 
    uint8_t                _x_of_qq                                      ; 
    uint8_t                _x_uf_q                                       ; 
    uint8_t                _x_uf_qq                                      ; 
                                                        
    uint8_t                _a_fsm_state                  ;
    uint8_t                _b_fsm_state                  ;
    uint8_t                _c_fsm_state                  ;
    uint8_t                _x_fsm_state                  ;

    // this is the control pipeline for the accumulator operation and result processing pipeline element
    struct c_pipeline_stage {
      // these fields are related to the C FSM
      uint8_t             c_valid                        ;
      struct c_payload {
       uint8_t             prod[VEC_BIT_SIZE*4]          ;
       uint8_t             op                            ;
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
       uint8_t             relu                          ;
       uint8_t             sat                           ;
       uint8_t             crow                          ;
       uint8_t             cbank                         ;
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
