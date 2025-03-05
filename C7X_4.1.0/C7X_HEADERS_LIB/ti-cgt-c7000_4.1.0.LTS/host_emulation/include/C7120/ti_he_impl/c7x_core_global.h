/*****************************************************************************/
/*  C7X_CORE_GLOBAL.H                                                        */
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
#ifndef _C7X_CORE_GLOBAL_H_
#define _C7X_CORE_GLOBAL_H_

#include <stdint.h>
#include <string>
#include <map>
#include <unordered_map>
/*** START CG REPLACE ***/
#include <string>
#include <ti_he_impl/vreg.h>
/*** END CG REPLACE ***/

//C7X Register File
#define  C7X_WORD_WIDTH 32
#define  VECTOR_REG_COUNT 16
#define  VECTOR_REG_WIDTH 512

#define  MC_REG_COUNT 8
#define  MC_REG_WIDTH 512

#define  LS_REG_COUNT 8
#define  LS_REG_WIDTH 512

#define  D_REG_COUNT 16
#define  D_REG_WIDTH 64

#define  PRED_REG_COUNT 16
#define  PRED_REG_WIDTH 64

#define  SCALAR_REG_COUNT 16
#define  SCALAR_REG_WIDTH 64

#define  CUCR_COUNT 8
#define  CUCR_WIDTH 512

#define  SA_GEN_COUNT 4
#define  SACR_WIDTH 512
#define  SACR_REG_REG32_COUNT (SACR_WIDTH/C7X_WORD_WIDTH)
#define  SACNTR_WIDTH 512
#define  SACNTR_REG_REG32_COUNT (SACNTR_WIDTH/C7X_WORD_WIDTH)

#define  NUM_ECR_REGS 16

//Vector registers size
#define MAX_WRITES 8
#define VEC_BIT_SIZE 512
#define NUM_BYTE_VEC (VEC_BIT_SIZE/8)
#define NUM_HWORD_VEC (VEC_BIT_SIZE/16)
#define NUM_WORD_VEC (VEC_BIT_SIZE/32)
#define NUM_DWORD_VEC (VEC_BIT_SIZE/64)
#define NUM_BYTE_DVEC ((VEC_BIT_SIZE*2)/8)
#define NUM_HWORD_DVEC ((VEC_BIT_SIZE*2)/16)
#define NUM_WORD_DVEC ((VEC_BIT_SIZE*2)/32)
#define NUM_DWORD_DVEC ((VEC_BIT_SIZE*2)/64)

//Stream Buffer Parameters
#define SE_TEMPLATE_SIZE 512    // New template is now 512 bytes
#define SE_TEMPLATE_WORDS (SE_TEMPLATE_SIZE/C7X_WORD_WIDTH)
#define SE_REG_COUNT 2
#define SE_REG_WIDTH 512
#define SE_REG_REG32_COUNT (SE_REG_WIDTH/C7X_WORD_WIDTH)

//LUT Parameters
#define LUT_SETS 4
#define MAX_LUT 16
#define MAX_L1D_BYTES 128
#define LUT_OFFSET_REG_SIZE 256
#define NUM_BYTE_LUT_OFFSET_REG (LUT_OFFSET_REG_SIZE/8)
#define NUM_HWORD_LUT_OFFSET_REG (LUT_OFFSET_REG_SIZE/16)
#define NUM_WORD_LUT_OFFSET_REG (LUT_OFFSET_REG_SIZE/32)
#define LUT_DATA_BUS_SIZE 512
#define NUM_BYTE_LUT_DATA_BUS (LUT_DATA_BUS_SIZE/8)
#define NUM_HWORD_LUT_DATA_BUS (LUT_DATA_BUS_SIZE/16)
#define NUM_WORD_LUT_DATA_BUS (LUT_DATA_BUS_SIZE/32)

// ESTP handler offsets
#define ESTP_RESET_OFFSET      (     0x0 )
#define ESTP_INT_EVT_OFFSET    (   0x200 )
#define ESTP_PAGE_FAULT_OFFSET (   0x400 )
#define ESTP_NME_OFFSET        (   0x600 )
#define ESTP_EVT_OFFSET        (   0x800 )
#define ESTP_SYSCALL_OFFSET    (  0x1000 )
#define ESTP_ROOTCALL_OFFSET   ( 0x20000 )

typedef vreg<NUM_WORD_VEC> vreg_t;
typedef vreg<NUM_WORD_DVEC> wreg_t;

//typedef vreg<NUM_WORD_VEC> vreg8_t;
//typedef vreg<NUM_WORD_DVEC> vreg16_t;
typedef uint64_t vpred_t;

/*** START CG REPLACE ***/
#define BFE(x,y) y; x
/*** END CG REPLACE ***/

typedef struct {
  BFE( uint64_t RSVD6       : 7 ,
  BFE( uint64_t EN          : 1 ,
  BFE( uint64_t RSVD5       : 3 ,
  BFE( uint64_t MMA_PRESENT : 1 ,
  BFE( uint64_t RSVD4       : 3 ,
  BFE( uint64_t MMA         : 1 ,
  BFE( uint64_t SA          : 8 ,
  BFE( uint64_t SE          : 8 ,
  BFE( uint64_t RSVD3       : 3 ,
  BFE( uint64_t DBGM        : 1 ,
  BFE( uint64_t SUDEN       : 2 ,
  BFE( uint64_t GEE         : 1 ,
  BFE( uint64_t PROT        : 1 ,
  BFE( uint64_t MCOLOR      : 5 ,
  BFE( uint64_t RSVD2       : 2 ,
  BFE( uint64_t COP         : 9 ,
  BFE( uint64_t RSVD1       : 3 ,
  BFE( uint64_t SPFXEN      : 1 ,
  BFE( uint64_t EVT         : 1 ,
       uint64_t CXM         : 3 )))))))))))))))))));
} tsr_type;

#define TSR_SE_BITPOS 32
#define TSR_SA_BITPOS 40

typedef enum {emGU = 0, emGS = 1, emU = 2, emS = 3, emSU = 4, emSS = 5, emRSVD = 6, emSM = 7} execution_mode_t;

struct creg_prop_t {
  std::string reg;
  uint32_t    perms;
  uint32_t    indexrange;
  bool        isAddrtype;
};

typedef std::unordered_map< std::string, creg_prop_t > creg_map_t;
typedef std::unordered_map< std::string, uint64_t >    creg_addr_map_t;
typedef std::unordered_map< std::string, std::string > creg_alias_map_t;

#endif
