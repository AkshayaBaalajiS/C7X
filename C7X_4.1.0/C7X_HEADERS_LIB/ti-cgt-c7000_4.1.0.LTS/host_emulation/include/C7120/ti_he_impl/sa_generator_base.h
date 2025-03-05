/*****************************************************************************/
/* SA_GENERATOR_BASE.H                                                       */
/*                                                                           */
/* Copyright (c) 2019 Texas Instruments Incorporated                         */
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
#ifndef _SA_GENERATOR_BASE_H_
#define _SA_GENERATOR_BASE_H_

#include <string>
#include <sstream>
//#include <utils/get_endian.h>
/*** START CG REPLACE ***/
#include <ti_he_impl/vreg.h>
/*** END CG REPLACE ***/
//#include <core/machine.h>
//#include <core/operands.h>
//#include <core/protected_regs.h>
//#include <utils/tlb.h>
//#include <boost/function.hpp>
/*** START CG REPLACE ***/
#include <ti_he_impl/c7x_core_global.h>
#include <ti_he_impl/cpu_reg_config.h>
/*** END CG REPLACE ***/

/*** START CG ADD ***/
#include <array>
#include <ti_he_impl/c7x_c_funcs.h>
/*** END CG ADD ***/

#define  SA_LOOPS         6
#define  MAX_SA_DECDIMS   3

class sa_generator_base 
{
  protected:
    uint32_t               _saId;
    std::string            _name;
    const cpu_reg_config   _reg_config;

    using sacnt_t = uint32_t;
    uint32_t               _words_in_sacr;        // Number of words in the ctrl regs
    uint32_t               _words_in_vector_reg;  // Number of words in CPU vector
    uint32_t               _num_decdims;          // Number of active DECDIMS
    sacnt_t*               sacntr0_reg;
    sacnt_t*               sacntr1_reg;

    vreg_t                 _str_template;

    // SA offset and predication counts
    // These are the whole point of the model!
    uint32_t               sa_offset;
    vpred_t                sa_pred;

    // Model variable to keep track if a stream has is active/ has adv or ended
    // Makes model simpler rather than checking the condition every time
    bool                   _isActive;
    bool                   _isAdvance;
    bool                   _isBrkLock;
    bool                   I_stream_has_data;  // Future cycle
    bool                   LI_stream_has_data;

    uint64_t                _num_advances; //Track number of advances in the stream

    // DECDIM
    uint32_t               _decdim     [ MAX_SA_DECDIMS ];
    uint32_t               _decdim_sd  [ MAX_SA_DECDIMS ];
    uint32_t               _decdim_icnt[ MAX_SA_DECDIMS ];
    bool                   _decdim_inv [ MAX_SA_DECDIMS ];  // Invert DECDIM
    bool                   _decdim_enabled;

    // DECDIM counts
    // Similar to the offsets and loop counts
    uint32_t               _decdim_I    [ MAX_SA_DECDIMS ];
    uint32_t               _decdim_LI   [ MAX_SA_DECDIMS ];
    uint32_t               _decdim_sd_I [ MAX_SA_DECDIMS ];
    uint32_t               _decdim_sd_LI[ MAX_SA_DECDIMS ];

    // FLAGS
    uint32_t               _dim_fmt;       // # of dimensions
    uint32_t               _vec_len_raw;   // veclen from tem
    uint32_t               _vec_len;       // veclen in elements

    // DIMENSIONS
    uint32_t               _icnt[ SA_LOOPS ];
    int32_t                _dim [ SA_LOOPS ];

    // SA model calculate the offset and ICNTs for the future cycle and stores
    // this info in I variable, the current cycle data is stored in LI_
    uint32_t               I_offset [ SA_LOOPS ];
    uint32_t               LI_offset[ SA_LOOPS ];

    // Loop counts
    // These work similar to the offsets, we calculate the future counts
    uint32_t               I [ SA_LOOPS ];
    uint32_t               LI[ SA_LOOPS ];

    // Debug
    static int             debug_level;

  protected:
    // Interface with loki model
    virtual void           create_sa_reg_operands      (                  ) = 0;
    virtual void           update_sacr_regs            ( vreg_t   sa_temp ) = 0;
    virtual void           update_sacntr_regs          (                  ) = 0;
    virtual void           update_sacntr_pred_regs     (                  ) = 0;
    virtual vreg_t         read_sacr_regs              (                  ) = 0;
    virtual vreg_t         read_sacntr_regs            ( uint32_t idx     ) = 0;
    virtual void           clear_control_regs          (                  ) = 0;
    virtual void           set_tsr_bit                 (                  ) = 0;
    virtual void           clr_tsr_bit                 (                  ) = 0;
/*** START CG REPLACE ***/
#if 0
    virtual void           delay_advance               (                  ) = 0;
#endif
/*** END CG REPLACE ***/

    void                   update_sacntr_reg           (                  );

    void                   reset                       (                  );
    bool                   decode_sa_template          ( vreg_t   sa_temp );
    bool                   validate_sa_template        (                  );
    void                   advance_loop_counters       (                  );
    bool                   advance_loop_counters       ( vreg_t sa_cnt0, vreg_t sa_cnt1 );
    uint32_t               calculate_offset            (                  );
    vpred_t                calculate_predication       (                  );
    void                   loop_break                  ( uint32_t loop_i  );
    void                   copy_early_to_late_counters (                  );
    void                   copy_late_to_early_counters (                  );

  public:
    inline std::string     name                 ()    { return _name;       }
    inline uint32_t        get_id               ()    { return _saId;       }

    inline bool            isActive             ()    { return _isActive;   }
    inline void            setActive            ( bool a ) { _isActive = a; }
    inline bool            isAdvance            ()    { return _isAdvance;  }
    inline void            setAdvance           ()    { _isAdvance = true;  }
    inline void            resetAdvance         ()    { _isAdvance = false; }
    inline bool            isBrkLock            ()    { return _isBrkLock;  }
    inline void            setBrkLock           ()    { _isBrkLock = true;  }
    inline void            resetBrkLock         ()    { _isBrkLock = false; }

    void                   sa_open              ( vreg_t   sa_template    );
    void                   sa_reset             (                         );
    void                   sa_close             (                         );
    void                   advance              (                         );
    void                   advance_no_outputs   (                         );
    void                   sa_break             ( uint32_t loop_idx       );
    void                   restore              (                         );
    virtual void           clear_output_regs    (                         ) = 0;

                           sa_generator_base    ( uint32_t                id, 
                                                  const std::string       name,
                                                  const cpu_reg_config&   reg_config
                                                                          );
    virtual               ~sa_generator_base         ();

    // DEBUG
    static void            set_debug_level   ( int lvl ) { debug_level = lvl; }

  protected:
    void                   print_addr_stat   (                  );
    void                   print_sa_template (                  );


}; //end of sa_generator_base class

#endif
