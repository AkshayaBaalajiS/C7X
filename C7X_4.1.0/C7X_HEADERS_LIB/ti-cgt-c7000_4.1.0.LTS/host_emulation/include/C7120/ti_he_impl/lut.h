/*****************************************************************************/
/*  LUT.H                                                                    */
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
#ifndef _LUT_H_
#define _LUT_H_

#include <cinttypes>
#include <string>
#include <sstream>
#include <stdint.h>
/*** START CG REPLACE ***/
#include <functional>
#include <vector>
#if 0
#include <utils/get_endian.h>
#include <utils/vreg.h>
#include <core/machine.h>
#include <core/operand_if.h>
#include <core/operands.h>
#include <utils/tlb.h>
#include <control/c7x_control.h>
#endif
#include <ti_he_impl/c7x_core_global.h>
#include <ti_he_impl/cpu_reg_config.h>

#define operand_base vreg_t
#define operand_base_if operand_base
typedef uint64_t addr_t;
/*** END CG REPLACE ***/

//class c7x_control;
class lut_cr {
  public:
    uint64_t     _cr_value;
    bool         isValidTemplate;

    uint32_t     table_indx;  // Number of tables
    uint32_t     num_tables;

    uint32_t     shft_amt;    // Element size
    element_type elem_type;
    uint32_t     bytes_p_elem;

    uint32_t     is_signed;   // Signed

    uint32_t     sat;         // Saturate

    uint32_t     interpolate; // Interpolation

    uint32_t     wsize;       // Weight Size

    uint32_t     table_size;  // Table size
    addr_t       table_baddr_mask; 
    addr_t       offset_mask; 

    uint32_t     promote;     // Promote
    uint32_t     elem_interp_promote_indx;

    uint32_t     eve_mode;    // VCOP

    // Debug
    static int   debug_level;
    static void  set_debug_level ( int lvl ) { debug_level = lvl; }

    bool decode_lut_properties ( uint64_t cr_val ) {
      _cr_value = cr_val;
      isValidTemplate = true;

      // Number of tables
      table_indx      = _cr_value & 0x7;
      num_tables      = 0x1 << table_indx;

      if (num_tables > 16) {
        isValidTemplate = false;
        fprintf (stderr, "Error: <LUT/HIST>: Invalid number of tables are defined\n");
      }

      // Element type
      shft_amt  = (_cr_value >> 3) & 0x7;
      elem_type = (element_type) shft_amt;
      bytes_p_elem = 1 << shft_amt;

      if ( shft_amt > 2 ) {
        isValidTemplate = false;
        fprintf (stderr, "Error: <LUT/HIST>: Invalid element type is defined\n");
      }

      /// Signed
      is_signed   = (_cr_value >> 6) & 0x1;

      // Saturation
      sat         = (_cr_value >> 7) & 0x1;

      // Interpolation
      interpolate = 0x1 << ((_cr_value >> 8) & 0x3);

      if (interpolate > 8) {
        isValidTemplate = false;
        fprintf (stderr, "Error: <LUT/HIST>: Invalid interpolation property is defined\n");
      }

      // Weight Size
      wsize       = (_cr_value >> 11) & 0x1;

      if (wsize > 1) {
        isValidTemplate = false;
        fprintf (stderr, "Error: <LUT/HIST>: Invalid wsize is defined\n");
      }

      // Table Size - Total LUT size, divide by number of tables to know table size
      table_size  = ((_cr_value >> 16) & 0x7); 
      if (table_size > 6) {
        isValidTemplate = false;
        fprintf (stderr, "Error: <LUT/HIST>: Invalid table size is defined\n");
      }

      table_baddr_mask = (table_size != 0) ? (( (addr_t) 0x1 << (table_size+9)) - 1)             : 0;
      offset_mask      = (table_size != 0) ? ((((addr_t) 0x1 << (table_size+9))/num_tables) - 1) : 0;

      // Promotion
      promote                  = ((_cr_value >> 24) & 0x3); 

      elem_interp_promote_indx = (((_cr_value >> 3) & 0x3) << 4) | (((_cr_value >> 8) & 0x3) << 2 ) | ((_cr_value >> 24) & 0x3);

      // VCOP / EVE mode
      eve_mode                 = ((_cr_value >> 28) & 0x1);

      if ( debug_level > 1 ) {
        fprintf( stderr, "Decoded LTCR:\n" );
        fprintf( stderr, "  Number of tables: %2d\n", num_tables );
        fprintf( stderr, "  Element size:     %2d Bytes\n", bytes_p_elem );
        fprintf( stderr, "  Signed:           %2d\n", is_signed );
        fprintf( stderr, "  Saturation:       %2d\n", sat );
        fprintf( stderr, "  Interpolation:    %2d\n", interpolate );
        fprintf( stderr, "  Weight size:      %2d Bytes\n", 1 << wsize );
        fprintf( stderr, "  Total Table size: %2d KBytes\n", table_size ? 1 << ( table_size - 1 ) : 0 );
        fprintf( stderr, "  Promotion factor:  x%d = %d Bytes\n", 1 << promote, 1 << ( promote + shft_amt ) );
        fprintf( stderr, "  VCOP/EVE mode:    %2d\n", eve_mode );
        fprintf( stderr, "  Table addr mask:  0x%016" PRIx64 "\n", table_baddr_mask );
        fprintf( stderr, "  Table offs mask:  0x%016" PRIx64 "\n", offset_mask );
      }

      return isValidTemplate;
    }

    bool update (uint64_t val) {
      return decode_lut_properties ( val );
    }
};

class lut 
{
  public:

    typedef uint64_t addr_t;
/*** START CG REPLACE ***/
    typedef std::function<void (uint8_t *, uint32_t, uint32_t, uint32_t)> promote_fcn_t;
    typedef std::function<void (uint8_t *, uint32_t)>                     swap_fcn_t;
/*** END CG REPLACE ***/

    inline std::string name()      {return _name;}
/*** START CG REPLACE ***/
#if 0
    inline machine_state * state() {return _state;}

    //Getting the initiator from the c7x_core
    inline void set_lut_dmem_initiator(loki::memory_initiator_base* datamem_initiator){ lut_dmem_initiator = datamem_initiator; };
#endif
/*** END CG REPLACE ***/

/*** START CG REPLACE ***/
    virtual void read_mem (addr_t addr, uint8_t *data, uint32_t size) {
      memcpy(data, (void*)addr, size);
    }
/*** END CG REPLACE ***/
    
    void calculate_lut_base_addr (addr_t base_addr) {
      for (uint32_t i = 0; i < LTCR.num_tables; i++) {
        lut_addr[i] = base_addr + (i * (MAX_L1D_BYTES/LTCR.num_tables));
      }
    }

    //SK Adding Atomic swap instructions even though they are not a part of the LUT 
    //Atomic instructions will have to be rewritten like LUT instructions when integrated with
    //memory system model.
    template <typename T>
    void cas                                       (addr_t addr, uint8_t *data, operand_base_if *op_if);
    void cas32                                     (addr_t addr, uint8_t *data, operand_base_if *op_if);
    template <typename T>
    void atomic_swap                               (addr_t addr, T new_data, operand_base_if *op_if);
    void atomic_swap32                             (addr_t addr, uint32_t new_data, operand_base_if *op_if );

    void lutrd                                     (addr_t base_addr, uint64_t ltcr, vreg<NUM_WORD_LUT_OFFSET_REG> offsetVec, operand_base_if *op_if, uint32_t num_elements);
    void lutwr                                     (vreg<NUM_WORD_LUT_DATA_BUS> dataVec, addr_t base_addr, uint64_t ltcr, vreg<NUM_WORD_LUT_OFFSET_REG> offsetVec);
    void lutscatter                                (vreg<NUM_WORD_LUT_DATA_BUS> dataVec, addr_t base_addr, uint64_t ltcr, vreg<NUM_WORD_LUT_OFFSET_REG> offsetVec);
    void lutinit                                   (vreg<NUM_WORD_LUT_DATA_BUS> dataVec, addr_t base_addr, uint64_t ltcr, uint64_t offset);
    void translate_to_c7x_way_offsetIndx           (vreg<NUM_WORD_LUT_DATA_BUS> &dataVec, vreg<NUM_WORD_LUT_OFFSET_REG> &offsetVec);
    void translate_eve_addr_to_c7x_way_offsetIndx  (vreg<NUM_WORD_LUT_DATA_BUS> &dataVec, vreg<NUM_WORD_LUT_OFFSET_REG> &offsetVec);

    template <typename t>
    void write_elements                            (vreg<NUM_WORD_LUT_DATA_BUS> dataVec, vreg<NUM_WORD_LUT_OFFSET_REG> offsetVec);
    void hist                                      (addr_t base_addr, uint64_t ltcr, vreg<NUM_WORD_LUT_OFFSET_REG> offsetVec);
    void whist                                     (vreg<NUM_WORD_LUT_DATA_BUS> dataVec, addr_t base_addr, uint64_t ltcr, vreg<NUM_WORD_LUT_OFFSET_REG> offsetVec);

    template <typename T>
    static void zero_unused_lut_elements           (uint8_t *op, uint32_t num_tables, uint32_t num_elements, uint32_t isInterpolate);

    template <typename T, typename S>
    static void lut_unpk_elements                  (uint8_t *op, uint32_t num_tables, uint32_t num_elements, uint32_t isInterpolate);

    template <typename T> 
    T gsat                                         (T op, uint32_t num_bits);

    template <typename T> 
    T gsatu                                        (T op, uint32_t num_bits);

    template <typename T>
    static void eswap_elements                     (uint8_t *op, uint32_t num_elements);

    void read_lut_data                             (vreg<NUM_WORD_LUT_OFFSET_REG> offsetVec);

    template <typename T>
    void read_hist_buckets                         (vreg<NUM_WORD_LUT_OFFSET_REG> offsetVec);

    void init_fcns                                 ();

/*** START CG REPLACE ***/
    lut (const std::string name, const cpu_reg_config& _reg_config):
      _name(name),
      reg_config( _reg_config  )
/*** END CG REPLACE ***/
    {
      init_fcns ();
    } 
      
    virtual ~lut ()
    { 
    }

    static void  set_debug_level ( int lvl ) { debug_level = lvl;
                                               lut_cr::set_debug_level( lvl ); }

  private:
    std::string                  _name;
/*** START CG REPLACE ***/
#if 0
    machine_state                *_state;
    loki::memory_initiator_base* lut_dmem_initiator;            //Data memory initiator
#endif
/*** END CG REPLACE ***/
    
    bool                         valid_lutrd[5][48];
    std::vector<promote_fcn_t>   promote_fcns;
    std::vector<swap_fcn_t>      eswap_fcns;

    addr_t                       lut_addr[MAX_LUT];             //LUT base addresses
    lut_cr                       LTCR;                          //LUT properties
    uint64_t                     lut_data[NUM_WORD_LUT_DATA_BUS/2];
    uint32_t                     hist_buff[MAX_LUT];
/*** START CG REPLACE ***/
#if 0
    c7x_control                  *ctrl;
#endif
/*** END CG REPLACE ***/
    const cpu_reg_config         reg_config;

    static int                   debug_level;

}; //end of LUT class

#endif
