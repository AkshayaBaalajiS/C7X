#ifndef _STREAMING_ENGINE_BASE_H_
#define _STREAMING_ENGINE_BASE_H_

#include <string>
#include <sstream>
#include <array>
#include "butterfly.h"
#include <stdint.h>
#include "vector.h"

#define NUM_LOOPS 6

typedef uint64_t addr_t;
#define ADDRESS_BIT48_ROLLOVER        ( 0x1004 )
#define CPU_READ_WHILE_ACTIVE_LOW     ( 0x1003 )
#define INVALID_SE_STREAM             ( 0x1001 )
#define NO_SE_ERROR                   ( 0x0    )

typedef enum
{
  NO_OPCODE        = 0,
  STROPEN          = 6,

  BLKCMO_DCCU      = 16,
  BLKCMO_DCCIU     = 17,
  BLKCMO_DCCMIU    = 18,
  BLKCMO_DCCC      = 19,
  BLKCMO_DCCIC     = 20,
  BLKCMO_DCCMIC    = 21,

  BLKCMO_DCCU_NS   = 24,
  BLKCMO_DCCIU_NS  = 25,
  BLKCMO_DCCMIU_NS = 26,
  BLKCMO_DCCC_NS   = 27,
  BLKCMO_DCCIC_NS  = 28,
  BLKCMO_DCCMIC_NS = 29,

  BLKPLD_L2R       = 32,
  BLKPLD_L2W       = 33,
  BLKPLD_L3R       = 34,
  BLKPLD_L3W       = 35

} se_opcode_t;

class streaming_engine_base
{
  protected:
    using vreg_se           = vreg<SE_REG_REG32_COUNT>;
    using permute_fcn_t     = std::function<void (vreg_se &, element_type &)>;
    using read_stream_fcn_t = std::function<void ()>;
    using int_vec_t         = std::array<int32_t,  NUM_LOOPS>;
    using uint_vec_t        = std::array<uint32_t, NUM_LOOPS>;
    using addr_vec_t        = std::array<addr_t,   NUM_LOOPS>;

    // Streaming Engine Class properties
    uint32_t                _streamId;
    std::string             _name;

    // Debug
    static int              debug_level;

    vreg_se                 se;

    addr_t                  _base_addr;
    addr_t                  _base_addr_48;  // 48+ bit of the addr for rollover

    se_opcode_t             _se_opcode;

    // Stream Template properties
    int32_t                 _dir;

    uint_vec_t              _icnt;
    int_vec_t               _dim; // Now in terms of elem size

    //Stream element properties
    element_type            _sub_elem_t;
    element_type            _elem_t;
    promote_type            _elem_promote_t;
    uint32_t                _promote_factor;
    bool                    _isComplexNum;
    bool                    _swapComplexNum;
    uint32_t                _sub_elem_bytes;  // Sub-element bytes
    uint32_t                _tot_elem_bytes;  // Total bytes per elem
    uint32_t                _transpose_mode;
    std::array<char *, 7>   _transpose_decode_str;
    uint32_t                _granule;
    uint32_t                _veclen_flag; // Value in SE template
    uint32_t                _veclen_bytes; // This is the old vec_len in bytes
    uint32_t                _veclen_elems; // vec_len in elements
    uint32_t                _dim_fmt;     // Shows the number of dims
    bool                    _grp_dup;
    uint32_t                _elem_dup;
    uint32_t                _elem_decimate; // Values: 0, 2, 4
    uint32_t                _throttle; // Throttle rate, currently not used

    uint32_t                _decdim_icnt[2];  // Reset ICNT for dec_dim, read from template

    uint32_t                _decdim[2];       // Strip mining mode configuration
    uint32_t                _decdim_I[2];     // Count for dec_dim
    uint32_t                _decdim_LI[2];    // Late count

    uint32_t                _decdim_sd[2];    // Strip mining SD mode configuration
    uint32_t                _decdim_sd_I[2];  // Count for dec_dim sd
    uint32_t                _decdim_sd_LI[2]; // Late count sd

    uint32_t                _lezr_dim;
    uint32_t                _lezr_icnt;
    uint32_t                _lezr_I;

    //For circular addressing mode
    uint32_t                _cbk1;
    uint32_t                _cbk0;
    uint_vec_t              _addr_mode;
    addr_vec_t              _addr_mask;
    std::array<char *, 32>  _addr_mode_decode;  // Convert to string for DEBUG

    //Permute functions
    permute_fcn_t           promote_fcn;
    permute_fcn_t           swap_fcn;
    permute_fcn_t           decimate_fcn;
    read_stream_fcn_t       read_next_stream_data;

    //Stream status properties
    bool                    _isActive;
    bool                    _isAdvance;
    bool                    _is_first_stream_read;
    uint64_t                _exception_code;
    uint64_t                _exception_data;

    //Stream buffer local variables
    //Used to calculate the next address
    uint_vec_t              I;
    addr_vec_t              addr;
    bool                    stream_has_data;    //for early address gen counters

    uint_vec_t              LI;
    addr_vec_t              laddr;
    bool                    lstream_has_data;   //for late addr gen counters

    uint32_t                loop0_sz;     // Max number of elems that fit on vec_len
                                          // vec_len / ( dup * promote ) * decimate
    int32_t                 data[SE_REG_REG32_COUNT];
    vreg_t                  str_template; // Holds the original template entered by the user
    vreg_t                  zero_vector;
    addr_t                  addr_align;

    vreg_t                  restore0_vec;
    vreg_t                  restore1_vec;
    vreg_t                  restore2_vec;
    vreg_t                  restore3_vec;
    bool                    restore0_pending;
    bool                    restore1_pending;
    bool                    restore2_pending;
    bool                    restore3_pending;


    // Function: read_mem
    // Read bytes from memory, addr is the starting address,
    //  size is the number of bytes, and data is the buffer to store data
    virtual void read_mem   ( addr_t addr, uint8_t *data, uint32_t size ) = 0;

    // Function: update_streaming_engine_regs
    // Write the new SE data into CPU SE registers
    virtual void update_streaming_engine_regs    () = 0;

    // Function: set_exception
    // Sets error state in the streaming engine
    virtual void set_no_exception                () {}
    virtual void set_closed_str_exception        () {}
    virtual void set_invalid_str_exception       () {}
    virtual void set_addr_rollover_exception     () {}

    void         reset                           ( bool reset_restore=true );

    bool         decode_template_properties      (vreg_t &, addr_t);
    void         populate_decdim_cnts            ();
    bool         decode_addressing_masks         ();
    bool         decode_element_type             (uint32_t);
    bool         decode_element_promotion        (uint32_t);
    bool         decode_element_decimation       ();
    bool         decode_transpose_mode           ();
    bool         decode_se_dim_fmt_fwdrev        (vreg_t);
    bool         decode_se_dim_fmt_transpose     (vreg_t);
    bool         check_stream_parameters         ();

    void         read_next_fwdrev_stream_data    ();
    void         read_next_transpose_stream_data ();
    void         stream_break_fwdrev             (uint32_t);
    void         stream_break_transpose          (uint32_t);

    void         copy_data                       (int32_t, uint32_t, uint32_t);
    void         zero_fill_data                  (int32_t);

    bool         blockcmo_isvalid                (uint32_t);
    bool         blockpld_isvalid                (uint32_t);

    vreg_t       stream_save0                    ();
    vreg_t       stream_save1                    ();
    vreg_t       stream_save2                    ();
    vreg_t       stream_save3                    ();
    void         stream_restore0                 (vreg_t);
    void         stream_restore1                 (vreg_t);
    void         stream_restore2                 (vreg_t);
    void         stream_restore3                 (vreg_t);

    // Debug
    void         print_se_template               ();
    void         print_addr_stat                 ();

    // Exception decode
    std::string   decode_exception_data ();

  public:
    inline  std::string   name                  ()  { return _name;           }
    inline  uint32_t      get_id                ()  { return _streamId;       }
    inline  bool          isActive              ()  { return _isActive;       }
    inline  bool          isAdvance             ()  { return _isAdvance;      }
    inline  void          setAdvance            ()  { _isAdvance = true;      }
    inline  void          resetAdvance          ()  { _isAdvance = false;     }
    inline  vreg_se       get_se                ()  { return se;              }

    // Signal the SE engine that a read was performed
    // SE will signal back the machine state if there's an exception
    inline  uint64_t      get_exception_code    ()  { return _exception_code; }
    inline  uint64_t      get_exception_data    ()  { return _exception_data; }

    // Function: signal_read
    // This method should be called whenever an SE register is read
    // If SE is not open, this method should report the exception to the machine
    virtual bool          signal_read           () = 0;

    void                  stream_open           (vreg_t, addr_t);
    void                  stream_close          ();
    void                  advance               ();
    void                  blockcmo              (uint32_t);
    void                  blockpld              (uint32_t);
    void                  stream_break          (uint32_t);
    vreg_t                stream_save           (uint32_t);

    // The stream_restore function only prepares the SE for CTX restoring
    // The heavy lifting is done by restore function, which should be called
    // when the TSR.SE bit is set to active high again, e.g. by the RETE instr
    void                  stream_restore        (uint32_t, vreg_t);
    void                  restore               ();

    // Debug
    static void           set_debug_level       (int lvl) { debug_level = lvl; }

    // Constructor
    streaming_engine_base (
        uint32_t                     id,
        const std::string            name
    );

    virtual ~streaming_engine_base () { }

}; //end of streaming_engine_base

#endif
