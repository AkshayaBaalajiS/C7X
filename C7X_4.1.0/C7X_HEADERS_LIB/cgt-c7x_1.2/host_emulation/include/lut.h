/*****************************************************************************/
/*  LUT.H v#####                                                             */
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
#ifndef _LUT_H_
#define _LUT_H_

#include <string>
#include <sstream>
#include <stdint.h>
#include "vector.h"

#define operand_base vreg_t
#define operand_base_if operand_base
typedef uint64_t addr_type;

#define NUM_WORD_LUT_OFFSET_REG 16
#define NUM_WORD_LUT_DATA_BUS 16
#define MAX_LUT 16 
#define MAX_L1D_BYTES 128

class lut_cr {
  public:
    uint64_t     value;

    uint32_t     num_tables;
    element_type elem_type;
    uint32_t     shft_amt;
    uint32_t     is_signed;
    uint32_t     sat;
    uint32_t     interpolate;
    uint32_t     wsize;
    uint32_t     table_size;
    addr_type    table_baddr_mask; 
    addr_type    offset_mask; 
    uint32_t     promote;
    bool         isValidTemplate;
    uint32_t     table_indx;
    uint32_t     elem_interp_promote_indx;
    uint32_t     eve_mode;

    void decode_lut_properties () {
      isValidTemplate = true;

      num_tables      = 0x1 << (value & 0x7);
      table_indx      = value & 0x7;

      if (num_tables > 16) {
        isValidTemplate = false;
        fprintf (stderr, "Error: <LUT/HIST>: Invalid number of tables are defined\n");
      }

      if (((value >> 3) & 0x7) > 2) {
        isValidTemplate = false;
        fprintf (stderr, "Error: <LUT/HIST>: Invalid element type is defined\n");
      }

      elem_type = (element_type) ((value >> 3) & 0x7);
      shft_amt  = (value >> 3) & 0x7;
      if ((int) elem_type > 2) {
        isValidTemplate = false;
        fprintf (stderr, "Error: <LUT/HIST>: Invalid element type is defined\n");
      }

      is_signed   = (value >> 6) & 0x1;
      sat         = (value >> 7) & 0x1;

      interpolate = 0x1 << ((value >> 8) & 0x7);
      if (interpolate > 8) {
        isValidTemplate = false;
        fprintf (stderr, "Error: <LUT/HIST>: Invalid interpolation property is defined\n");
      }

      wsize       = (value >> 11) & 0x3;
      if (wsize > 1) {
        isValidTemplate = false;
        fprintf (stderr, "Error: <LUT/HIST>: Invalid wsize is defined\n");
      }

      table_size  = ((value >> 16) & 0xff); 
      if (table_size > 6) {
        isValidTemplate = false;
        fprintf (stderr, "Error: <LUT/HIST>: Invalid table size is defined\n");
      }

      table_baddr_mask = (table_size != 0) ? (( (addr_type) 0x1 << (table_size+9)) - 1)             : 0;
      offset_mask      = (table_size != 0) ? ((((addr_type) 0x1 << (table_size+9))/num_tables) - 1) : 0;

      promote                  = ((value >> 24) & 0x3); 
      elem_interp_promote_indx = (((value >> 3) & 0x3) << 4) | (((value >> 8) & 0x3) << 2 ) | ((value >> 24) & 0x3);

      eve_mode                 = ((value >> 28) & 0x1);

    }

    void update (uint64_t val) {
      value = val;
      decode_lut_properties ();
    }
};

class lut 
{
  public:

    typedef std::function<void (uint8_t *, uint32_t, uint32_t, uint32_t)> promote_fcn_t;
    typedef std::function<void (uint8_t *, uint32_t)>                     swap_fcn_t;

    inline std::string name()      {return _name;}

    virtual void read_mem (addr_type addr, uint8_t *data, uint32_t size) {
       memcpy(data, (void*)addr, size);
    }
    
    void calculate_lut_base_addr (addr_type base_addr) {
      for (uint32_t i = 0; i < LTCR.num_tables; i++) {
        lut_addr[i] = base_addr + (i * (MAX_L1D_BYTES/LTCR.num_tables));
      }
    }

    //SK Adding Atomic swap instructions even though they are not a part of the LUT 
    //Atomic instructions will have to be rewritten like LUT instructions when integrated with
    //memory system model.
    template <typename T>
    void cas                                       (addr_type addr, uint8_t *data, operand_base_if *op_if);
    template <typename T>
    void atomic_swap                               (addr_type addr, T new_data, operand_base_if *op_if);

    void lutrd                                     (addr_type base_addr, uint64_t ltcr, vreg<NUM_WORD_LUT_OFFSET_REG> offsetVec, operand_base_if *op_if, uint32_t num_elements);
    void lutwr                                     (vreg<NUM_WORD_LUT_DATA_BUS> dataVec, addr_type base_addr, uint64_t ltcr, vreg<NUM_WORD_LUT_OFFSET_REG> offsetVec);
    void lutscatter                                (vreg<NUM_WORD_LUT_DATA_BUS> dataVec, addr_type base_addr, uint64_t ltcr, vreg<NUM_WORD_LUT_OFFSET_REG> offsetVec);
    void lutinit                                   (vreg<NUM_WORD_LUT_DATA_BUS> dataVec, addr_type base_addr, uint64_t ltcr, uint64_t offset);
    void translate_to_c7x_way_offsetIndx           (vreg<NUM_WORD_LUT_DATA_BUS> &dataVec, vreg<NUM_WORD_LUT_OFFSET_REG> &offsetVec);
    void translate_eve_addr_to_c7x_way_offsetIndx  (vreg<NUM_WORD_LUT_DATA_BUS> &dataVec, vreg<NUM_WORD_LUT_OFFSET_REG> &offsetVec);

    template <typename t>
    void write_elements                            (vreg<NUM_WORD_LUT_DATA_BUS> dataVec, vreg<NUM_WORD_LUT_OFFSET_REG> offsetVec);
    void hist                                      (addr_type base_addr, uint64_t ltcr, vreg<NUM_WORD_LUT_OFFSET_REG> offsetVec);
    void whist                                     (vreg<NUM_WORD_LUT_DATA_BUS> dataVec, addr_type base_addr, uint64_t ltcr, vreg<NUM_WORD_LUT_OFFSET_REG> offsetVec);

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

    lut (const std::string name):
      _name(name)
    {
      init_fcns ();
    } 
      
    virtual ~lut ()
    { 
    }

  private:
    std::string                  _name;
    
    bool                         valid_lutrd[5][48];
    std::vector<promote_fcn_t>   promote_fcns;
    std::vector<swap_fcn_t>      eswap_fcns;

    addr_type                    lut_addr[MAX_LUT];             //LUT base addresses
    lut_cr                       LTCR;                          //LUT properties
    uint64_t                     lut_data[NUM_WORD_LUT_DATA_BUS/2];
    uint32_t                     hist_buff[MAX_LUT];

}; //end of LUT class

#endif
