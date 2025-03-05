/*****************************************************************************/
/* STREAMING_ENGINE_BASE.H                                                   */
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
#ifndef _STREAMING_ENGINE_BASE_H_
#define _STREAMING_ENGINE_BASE_H_

#include <string>
#include <array>
#include <sstream>
/*** START CG REPLACE ***/
#include <ti_he_impl/vreg.h>
#if 0
#include <boost/function.hpp>
#endif
#include <ti_he_impl/c7x_core_global.h>
#include <ti_he_impl/butterfly.h>
#include <ti_he_impl/cpu_reg_config.h>
#include <functional>
#include <array>
/*** END CG REPLACE ***/

#define NUM_LOOPS                     ( 6  )
#define SE_DECDIMS                    ( 2  )
#define STREAM_OPEN_STALL_CYCLES      ( 17 )

typedef uint64_t addr_t;
#define ILLEGAL_BREAK_EXCEPTION       ( 0x1007 )
#define SPARSE_HEADER_EXCEPTION       ( 0x1006 )
#define ADDRESS_BIT48_ROLLOVER        ( 0x1004 )
#define CPU_READ_WHILE_ACTIVE_LOW     ( 0x1003 )
#define INVALID_SE_STREAM             ( 0x1001 )
#define NO_SE_ERROR                   ( 0x0    )

#define SE_TEMPLATE_FMT_NORMAL        ( 0 )
#define SE_TEMPLATE_FMT_CNN           ( 1 )

#define HORIZONTAL_ADV_DIM            ( _decdim[ 1 ] )
#define HORIZONTAL_POS_DIM            ( _decdim_sd[ 1 ] )

#define SPARSE_PAYLOAD_SZ             ( 64 )

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

typedef enum
{
  FILLVAL_ZERO = 0,
  FILLVAL_USER = 1,
  FILLVAL_MIN  = 2,
  FILLVAL_MAX  = 3
} fillval_mode_t;

class streaming_engine_base 
{
  protected:
    using vreg_se           = vreg<SE_REG_REG32_COUNT>;
/*** START CG REPLACE ***/
    using permute_fcn_t     = std::function<void (vreg_se &, element_type &)>;
    using read_stream_fcn_t = std::function<void ()>;
/*** END CG REPLACE ***/
    using int_vec_t         = std::array<int32_t,  NUM_LOOPS>;
    using uint_vec_t        = std::array<uint32_t, NUM_LOOPS>;
    using addr_vec_t        = std::array<addr_t,   NUM_LOOPS>;

    // Streaming Engine Class properties
    uint32_t                _streamId;
    std::string             _name;

    const cpu_reg_config    _reg_config;
    uint32_t                _words_in_se_template;  // Number of words in SE template
    uint32_t                _words_in_vector_reg;   // Number of words in CPU vector
    uint32_t                _words_in_se_reg;       // Number of words in SE vector

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

    // Stream format
    uint32_t                _template_format;
    std::vector< char *>    _templdate_format_str;

    // CNN flags
    bool                    _decdim2_mode;
    uint32_t                _horizontal_width;
    uint32_t                _horizontal_width_I;

    uint32_t                _zero_pad_ofs;
    uint32_t                _zero_pad_width;

    uint32_t                _decdim_inv_icnt[ SE_DECDIMS ];  // Used to check if inverse is enabled
                                       
    uint32_t                _decdim_inv_I[SE_DECDIMS];     // Count for dec_dim
    uint32_t                _decdim_inv_LI[SE_DECDIMS];    // Late count
                                       
    uint32_t                _decdim_inv_sd_I[SE_DECDIMS];  // Count for dec_dim sd
    uint32_t                _decdim_inv_sd_LI[SE_DECDIMS]; // Late count sd

    uint32_t                _active_decdims;

    //Stream element properties
    uint32_t                _eltype_flag;
    element_type            _sub_elem_t;
    element_type            _elem_t;
    promote_type            _elem_promote_t;
    element_sign            _elem_sign;
    uint32_t                _promote_factor;
    uint32_t                _promote_flag;
    bool                    _float_flag;
    float                   _sub_elem_bytes;  // Sub-element bytes
    uint32_t                _tot_elem_bytes;  // Total bytes per elem
    uint32_t                _num_sub_elem;    // How many sub elements in an elem
    uint32_t                _output_num_sub_elem; // Number of subelements in output
    uint32_t                _output_sub_elem_t;
    uint32_t                _transpose_mode;
    std::array<char *, 8>   _transpose_decode_str;
    uint32_t                _granule;
    uint32_t                _veclen_flag; // Value in SE template
    uint32_t                _veclen_bytes; // This is the old vec_len in bytes
    uint32_t                _veclen_elems; // vec_len in elements
    uint32_t                _dim_fmt;     // Shows the number of dims
    bool                    _grp_dup;
    uint32_t                _elem_dup_flag;
    uint32_t                _elem_dup;
    uint32_t                _elem_decimate; // Values: 0, 2, 4
    bool                    _elem_decimate_128; // Special 128 element decimation

    fillval_mode_t          _fillval_mode;             // Fill value mode
    std::array< char *, 4 > _fillval_decode;           // Convert to string
/*** START CG REPLACE ***/
    uint64_t&               _fillval_ecr;              // ECR value
/*** END CG REPLACE ***/
    uint64_t                _fillval_ecr_snapshot;     // Active ECR value
    uint64_t                _fillval;                  // Computed_filval
    std::vector< uint32_t>  _fillval_elems;            // Store which indexes must be zeroed out

    // Sparsity
    uint32_t                _sparse_cfg_flag;
    std::array< char *, 4 > _sparse_cfg_decode_str;
    uint32_t                _sparse_packet_sz;          // Total bytes in a decompressed packet, bytes
    uint32_t                _sparse_segments_per_pckt;  // How many vectors can be obtained from a packet
    uint32_t                _sparse_remaining_segments; // Counter how many vectors are available from the packet
    uint64_t                _sparse_remaining_indbit;   // Current packet indicator bits, this value gets shifted
    uint8_t*                _sparse_payload_ptr;
    uint32_t                _sparse_payload_idx;        // Index to the next payload element
    uint64_t                _sparse_indbit;             // Byte enables for current packet
    bool                    _sparse_reuse_indbit;       // Signal to reuse indicator bits
    addr_t                  _sparse_addr0;

    uint32_t                _decdim_icnt[SE_DECDIMS];  // Reset ICNT for dec_dim, read from template

    uint32_t                _decdim[SE_DECDIMS];       // Strip mining mode configuration
    uint32_t                _decdim_I[SE_DECDIMS];     // Count for dec_dim
    uint32_t                _decdim_LI[SE_DECDIMS];    // Late count

    uint32_t                _decdim_sd[SE_DECDIMS];    // Strip mining SD mode configuration
    uint32_t                _decdim_sd_I[SE_DECDIMS];  // Count for dec_dim sd
    uint32_t                _decdim_sd_LI[SE_DECDIMS]; // Late count sd

    uint32_t                _lezr_dim;
    uint32_t                _lezr_icnt;
    uint32_t                _lezr_I;
    uint32_t                _lezr_LI;

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
    bool                    _isRMActive;
    bool                    _hasAdvanced;
    bool                    _brklock;
    bool                    _is_first_stream_read;
    uint64_t                _num_se_advances;
    bool                    _decode_error;
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
    int32_t                 data[SE_REG_REG32_COUNT * 2];
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

#ifdef SE_VISUAL
    virtual void mark_idecdim( addr_t addr, uint32_t size ) = 0;
    virtual void mark_decdim ( addr_t addr, uint32_t size ) = 0;
#endif

    // Function: set_tsr_bit
    // Set/Clear SE bit in TSR regiuster corresponding to this streaming engine,
    //  _streamId is the index of this streaming engine
    virtual void set_tsr_bit                     () = 0;
    virtual void clr_tsr_bit                     () = 0;

    // Function: tsr_is_active
    // Check if the SE bit in TSR corresponding to this SE is active
    virtual bool tsr_is_active                   () = 0;

    // Function: is_x_endian
    // Check if data should be swaped based on endian
/*** START CG REPLACE ***/
#if 0
    virtual bool is_x_endian                     () = 0;
#endif
/*** END CG REPLACE ***/

/*** START CG REPLACE ***/
#if 0
    // Function: reserve_se_regs
    // Wait 14 cycles after SEOPEN before data can be provided
    virtual void reserve_se_regs                 (uint32_t) = 0;
#endif
/*** END CG REPLACE ***/

    // Function: update_streaming_engine_regs
    // Write the new SE data into CPU SE registers
    virtual void update_streaming_engine_regs    () = 0;

/*** START CG REPLACE ***/
#if 0
    // Function: delay_advance
    // Call the advance method at the end of the current cycle
    virtual void delay_advance                   () = 0;

    // Function: do_linear_dmc_request
    // Track the DMC requests done by SE0/1 to detect bank conflicts
    virtual void do_linear_dmc_request( addr_t req_addr, uint64_t rem_icnt ) = 0;
#endif
/*** END CG REPLACE ***/

    // Function: set_exception
    // Sets error state in the streaming engine
    virtual void set_no_exception                () {}
    virtual void set_closed_str_exception        () {}
    virtual void set_invalid_str_exception       () {}
    virtual void set_addr_rollover_exception     () {}
    virtual void set_sparse_header_exception     () {}
    virtual void set_illegal_break_exception     () {}

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
    void         read_next_sparse_data           ();
    void         fetch_more_sparse_data          ();
    void         advance_sparse                  ();
    void         stream_break_sparse             (uint32_t);
    void         stream_break_fwdrev             (uint32_t);
    void         stream_break_transpose          (uint32_t);

    void         copy_data                       (int32_t, uint32_t, uint32_t, uint32_t);
    void         zero_fill_data                  (uint32_t start_elem, uint32_t num_elem, uint32_t total_elems);
    void         zero_fill_se                    (int32_t idx );

    void         compute_fillval                 ( );
    uint64_t     get_fillval                     ( );
    uint64_t     extend_fillval                  ( uint32_t bits );
    void         do_fillval_se                   ( uint32_t invalid_elems, uint32_t valid_elems );

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
    std::string   decode_exception_data         ( uint64_t iex_data );

  public:
    inline  std::string   name                  ()  { return _name;           }
    inline  uint32_t      get_id                ()  { return _streamId;       }
    inline  bool          isActive              ()  { return _isActive;       }
/*** START CG ADD ***/
    inline  vreg_se       get_se                ()  { return se;              }
/*** END CG ADD ***/
    inline  bool          isRMActive            ()  { return _isRMActive;     }
    inline  void          setRMActive           ( bool a = true ) { _isRMActive = a; }
    inline  bool          isAdvance             ()  { return _hasAdvanced;    }
    inline  void          setAdvance            ( bool a = true ) { _hasAdvanced = a; }
    inline  void          resetAdvance          ()  { _hasAdvanced = false;     }
    inline  bool          isBrkLock             ()  { return _brklock; }
    inline  void          setBrkLock            ( bool b = true ) { _brklock = b; } 
    inline  void          resetBrkLock          ()  { _brklock = false; }
            bool          is_end_of_stream      () const;

            void          write_sbnd            ( uint64_t  val, uint32_t index );
            void          read_sbnd             ( uint64_t& val, uint32_t index );

    // Signal the SE engine that a read was performed
    // SE will signal back the machine state if there's an exception 
    inline  uint64_t      get_exception_code    ()  { return _exception_code; }
    inline  uint64_t      get_exception_data    ()  { return _exception_data; }

    // Function: signal_read
    // This method should be called whenever an SE register is read
    // If SE is not open, this method should report the exception to the machine
    virtual bool          signal_read           () = 0;

    void                  stream_open           (vreg_t, addr_t);
    void                  stream_reset          ( addr_t );
    void                  stream_close          ();
    void                  advance               ();
    bool                  advance_restore       ();
    void                  advance_addresses     ();
    void                  advance_decdim        ();
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
        const std::string            name,
        const cpu_reg_config&        reg_config
    );
      
    virtual ~streaming_engine_base () { }

}; //end of streaming_engine_base

// Utility functions for vreg fields
void     set_field( vreg_t& reg, uint32_t start_idx, uint32_t len, uint64_t data );
uint64_t get_field( vreg_t& reg, uint32_t start_idx, uint32_t len );

#endif
