/*****************************************************************************/
/*  SA_GENERATOR.H                                                           */
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
#ifndef _SA_GENERATOR_H_
#define _SA_GENERATOR_H_

#include <string>
#include <sstream>
/*** START CG REPLACE ***/
#if 0
#include <utils/get_endian.h>
#include <utils/vreg.h>
#include <core/machine.h>
#include <core/operands.h>
#include <core/protected_regs.h>
#include <utils/tlb.h>
#include <boost/function.hpp>
#include <include/c7x_core_global.h>
#endif
#include <ti_he_impl/sa_generator_base.h>
#include <ti_he_impl/cpu_reg_config.h>
/*** END CG REPLACE ***/

class sa_generator : public sa_generator_base
{
/*** START CG REPLACE ***/
#if 0
  using machine_reg_t = machine_fcn_register_base< uint64_t >;
#endif
/*** END CG REPLACE ***/

/*** START CG REPLACE ***/
  public:
/*** END CG REPLACE ***/
    // Interface with loki model
/*** START CG REPLACE ***/
#if 0
    machine_state          *_state;
#endif
    uint64_t               *tsr;
    vreg_t                  sacr;
    vreg_t                  sacntr0;
    vreg_t                  sacntr1;
    vpred_t                 psa;
    vreg_t                  sa;
/*** END CG REPLACE ***/

/*** START CG REPLACE ***/
  public:
/*** END CG REPLACE ***/
    // Interface with loki model

    /* Instantiate SACR/SACNTR/PSA/SA registers, use _saId as the SA index */
    virtual void   create_sa_reg_operands    (                  ) override;

    /* Update SACR register with the value provided in sa_temp */
    virtual void   update_sacr_regs          ( vreg_t   sa_temp ) override;

    /* Update sacntr register, then copy sacntr0_reg
       into SACNT registers */
    virtual void   update_sacntr_regs        (                  ) override;

    /* Update sacntr register, then copy sacntr0_reg, sa_pred, sa_offset
       into SACNT / SA / PSA registers */
    virtual void   update_sacntr_pred_regs   (                  ) override;

    /* Returns the value of SACR register */
    virtual vreg_t read_sacr_regs            (                  ) override;

    /* Returns the value of SACNTR register */
    virtual vreg_t read_sacntr_regs          ( uint32_t cr_idx  ) override;

    /* Sets SACR / SACNTR / SA / PSA to zero */
    virtual void   clear_control_regs        (                  ) override;

    /* Sets the corresponding SA in the TSR bit, use _saId as the SA index */
    virtual void   set_tsr_bit               (                  ) override;

    /* Clear the corresponding SA in the TSR bit, use _saId as the SA index */
    virtual void   clr_tsr_bit               (                  ) override;

/*** START CG REPLACE ***/
#if 0
    /* Calls the advance method at the end of the current cycle */
    virtual void   delay_advance             (                  ) override;
#endif
/*** END CG REPLACE ***/

  public:
/*** START CG REPLACE ***/
#if 0
    inline machine_state * state             () { return _state; }
#endif
/*** END CG REPLACE ***/

/*** START CG REPLACE ***/
                           sa_generator      ( uint32_t               id, 
                                               const std::string      name, 
                                               const cpu_reg_config&  reg_config
                                             );
/*** END CG REPLACE ***/
    virtual               ~sa_generator      () { }

    /* Sets SA / PSA to zero */
    virtual void   clear_output_regs         (                  ) override;

}; //end of sa_generator class

#endif
