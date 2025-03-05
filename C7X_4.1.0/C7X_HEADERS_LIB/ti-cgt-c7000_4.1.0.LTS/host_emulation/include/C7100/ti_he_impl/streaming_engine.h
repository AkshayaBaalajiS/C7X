/*****************************************************************************/
/*  STREAMING_ENGINE.H                                                       */
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
#ifndef _STREAMING_ENGINE_H_
#define _STREAMING_ENGINE_H_

/*** START CG REPLACE ***/
#if 0
#include <core/machine.h>
#include <core/protected_regs.h>
#include <core/memory_initiator_base.h>
#include <utils/tlb.h>
#include <callback/callback.hpp>
#endif
#include <ti_he_impl/streaming_engine_base.h>
/*** END CG REPLACE ***/

typedef uint64_t addr_t;

class streaming_engine : public streaming_engine_base
{
/*** START CG REPLACE ***/
#if 0
    using machine_reg       = machine_register_base<uint32_t>;
    using machine_fcn_reg   = machine_fcn_register_base<uint64_t>;
    using machine_reg_vec   = std::array<machine_reg *, SE_REG_REG32_COUNT>;
#endif
/*** END CG REPLACE ***/

  protected:
/*** START CG REPLACE ***/
#if 0
    machine_state                         *_state;
    loki::memory_initiator_base           *initiator_ptr; 
#endif
    uint64_t                              *tsr;
#if 0
    machine_reg_vec                       machine_se_ptrs;
#endif
/*** END CG REPLACE ***/

    // Memory read functions
/*** START CG REPLACE ***/
#if 0
    void          func_empty ( tlm::tlm_generic_payload &p) {}
#endif
/*** END CG REPLACE ***/
    virtual void  read_mem   (  addr_t    addr, 
                                uint8_t   *data, 
                                uint32_t  size    ) override;

    // Functions to access TSR register
    virtual void set_tsr_bit                     () override;
    virtual void clr_tsr_bit                     () override;
    virtual bool tsr_is_active                   () override;

/*** START CG REPLACE ***/
#if 0
    virtual bool is_x_endian                     () override;
#endif
/*** END CG REPLACE **/

    // SE register reserve and update
/*** START CG REPLACE ***/
#if 0
    virtual void reserve_se_regs                 (uint32_t) override;
#endif
/*** END CG REPLACE ***/
    virtual void update_streaming_engine_regs    () override;

/*** START CG REPLACE ***/
#if 0
    // Call the advance method at the end of the cycle
    virtual void delay_advance                   () override;

    virtual void do_linear_dmc_request           ( addr_t   req_addr, 
                                                   uint64_t rem_icnt ) override;
#endif
/*** END CG REPLACE ***/

    // Sets error state in the streaming engine
    virtual void set_no_exception                () override;
    virtual void set_closed_str_exception        () override;
    virtual void set_invalid_str_exception       () override;
    virtual void set_addr_rollover_exception     () override;

  public:
/*** START CG REPLACE ***/
#if 0
    inline  machine_state *state                 ()  { return _state; }
#endif
/*** END CG REPLACE ***/

    // Signal the SE engine that a read was performed
    // SE will signal back the machine state if there's an exception 
    virtual bool signal_read                     () override;

    // Constructor
    streaming_engine (
/*** START CG REPLACE ***/
        uint32_t                     id, 
        const std::string            name
/*** END CG REPLACE ***/
    );
      
    virtual ~streaming_engine ();

}; //end of streaming_engine class

#endif
