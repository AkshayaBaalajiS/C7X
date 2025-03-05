#ifndef _SA_GENERATOR_BASE_H_
#define _SA_GENERATOR_BASE_H_

#include <string>
#include <sstream>
#include <array>
#include <vreg.h>
#include <vector.h>

#define STRACNTR_REG_REG32_COUNT 16
#define STRACR_REG_REG32_COUNT 16
#define  SA_LOOPS     6
#define  SA_DECDIMS   2

class sa_generator_base
{
  protected:
    uint32_t               _saId;
    std::string            _name;

    using stracnt_t = std::array< uint32_t, STRACNTR_REG_REG32_COUNT >;
    stracnt_t              stracnt_reg;

    // SA offset and predication counts
    // These are the whole point of the model!
    uint32_t               sa_offset;
    vpred_t                sa_pred;

    // Model variable to keep track if a stream has is active/ has adv or ended
    // Makes model simpler rather than checking the condition every time
    bool                   _isActive;
    bool                   _isAdvance;
    bool                   I_stream_has_data;  // Future cycle
    bool                   LI_stream_has_data;

    // DECDIM
    uint32_t               _decdim     [ SA_DECDIMS ];
    uint32_t               _decdim_sd  [ SA_DECDIMS ];
    uint32_t               _decdim_icnt[ SA_DECDIMS ];
    bool                   _decdim_enabled;

    // DECDIM counts
    // Similat to the offsets and loop counts
    uint32_t               _decdim_I    [ SA_DECDIMS ];
    uint32_t               _decdim_LI   [ SA_DECDIMS ];
    uint32_t               _decdim_sd_I [ SA_DECDIMS ];
    uint32_t               _decdim_sd_LI[ SA_DECDIMS ];

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
    virtual void           update_stracr_regs          ( vreg_t   sa_temp ) = 0;
    virtual void           update_stracntr_pred_regs   (                  ) = 0;
    virtual vreg_t         read_stracr_regs            (                  ) = 0;
    virtual vreg_t         read_stracntr_regs          (                  ) = 0;
    virtual void           clear_control_regs          (                  ) = 0;

    void                   update_stracntr_reg         (                  );

    void                   reset                       (                  );
    bool                   decode_sa_template          ( vreg_t   sa_temp );
    bool                   validate_sa_template        (                  );
    void                   advance_loop_counters       (                  );
    bool                   advance_loop_counters       ( vreg_t sa_cnt    );
    uint32_t               calculate_offset            (                  );
    vpred_t                calculate_predication       (                  );
    void                   loop_break                  ( uint32_t loop_i  );
    void                   copy_early_to_late_counters (                  );
    void                   copy_late_to_early_counters (                  );

  public:
    inline std::string     name                 ()    { return _name;       }
    inline uint32_t        get_id               ()    { return _saId;       }

    inline bool            isActive             ()    { return _isActive;   }
    inline bool            isAdvance            ()    { return _isAdvance;  }
    inline void            setAdvance           ()    { _isAdvance = true;  }
    inline void            resetAdvance         ()    { _isAdvance = false; }

    void                   sa_open              ( vreg_t   sa_template    );
    void                   sa_close             (                         );
    void                   advance              (                         );
    void                   sa_break             ( uint32_t loop_idx       );
    void                   restore              (                         );

                           sa_generator_base    ( uint32_t          id,
                                                  const std::string name
                                                                          );
    virtual               ~sa_generator_base         () { }

    // DEBUG
    static void            set_debug_level   ( int lvl ) { debug_level = lvl; }

  protected:
    void                   print_addr_stat   (                  );
    void                   print_sa_template (                  );


}; //end of sa_generator_base class

#endif
