#ifndef _C7X_EXCEPTION_H_
#define _C7X_EXCEPTION_H_

#include <vector>
#include <map>

namespace c7x_exception
{

typedef enum : uint64_t
{
    EXCEPTION_BAD   = 0
  , EXCEPTION_PFX   = 1 << 0
  , EXCEPTION_IFX   = 1 << 1
  , EXCEPTION_FPX   = 1 << 2
  , EXCEPTION_EPX   = 1 << 3
  , EXCEPTION_OPX   = 1 << 4
  , EXCEPTION_RCX   = 1 << 5
  , EXCEPTION_RAX   = 1 << 6
  , EXCEPTION_PRX   = 1 << 7
  , EXCEPTION_LBX   = 1 << 8
  , EXCEPTION_MSX   = 1 << 9
  , EXCEPTION_DFX   = 1 << 10
  , EXCEPTION_SEX   = 1 << 11
  , EXCEPTION_EXX   = 1 << 12
  , EXCEPTION_ADX   = 1 << 13
  , EXCEPTION_MMX   = 1 << 14
} c7x_exception_group_t;

typedef enum : uint64_t
{
     EXCEPTION_NONE                 = 0x0

  ,  PMC_UTLB_FAULT                 = 0x1
  ,  D_UTLB_FAULT_NONSPEC           = PMC_UTLB_FAULT                 << 1
  ,  D_UTLB_FAULT_SPEC              = D_UTLB_FAULT_NONSPEC           << 1
  ,  SE_UTLB_FAULT                  = D_UTLB_FAULT_SPEC              << 1

  ,  CPU_PMC_L2_ERROR               = SE_UTLB_FAULT                  << 1

  ,  C64_BAD_FETCH_PKT              = CPU_PMC_L2_ERROR               << 1

  ,  OVERSIZED_EPKT                 = C64_BAD_FETCH_PKT              << 1
  ,  UNRECOGNIZED_INST_FMT          = OVERSIZED_EPKT                 << 1

  ,  INVALID_OPCODE                 = UNRECOGNIZED_INST_FMT          << 1
  ,  OVERSIZED_LDST_INST            = INVALID_OPCODE                 << 1
  ,  ILLEGAL_INST_SIDE              = OVERSIZED_LDST_INST            << 1
  ,  ILLEGAL_LDST_ADDR_MODE         = ILLEGAL_INST_SIDE              << 1
  ,  ILLEGAL_PFS_ADDR_MODE          = ILLEGAL_LDST_ADDR_MODE         << 1
  ,  ILLEGAL_CAS_ADDR_MODE          = ILLEGAL_PFS_ADDR_MODE          << 1

  ,  WRITE_CONFLICT                 = ILLEGAL_CAS_ADDR_MODE          << 1

  ,  SE_ACCESS_ON_CLOSED_STREAM     = WRITE_CONFLICT                 << 1
  ,  ILLEGAL_SE_INST_ON_OPEN_STREAM = SE_ACCESS_ON_CLOSED_STREAM     << 1  // SESAVE/SERSTR
  ,  LUT_ACCESS_WO_PERM             = ILLEGAL_SE_INST_ON_OPEN_STREAM << 1
  ,  BAD_ECR_RSTATUS                = LUT_ACCESS_WO_PERM             << 1
  ,  DSWBP_ON_DISABLED_SWBP         = BAD_ECR_RSTATUS                << 1

  ,  INTERN_MVC_PERMISSION          = DSWBP_ON_DISABLED_SWBP         << 1
  ,  EXTERN_MVC_PERMISSION          = INTERN_MVC_PERMISSION          << 1
  ,  INVALID_PERM_FOR_OPCODE        = EXTERN_MVC_PERMISSION          << 1
  ,  ILLEGAL_RETE_USE               = INVALID_PERM_FOR_OPCODE        << 1

// -------- SPLOOP -------------- //
// EXCEPTION_                  = 0x1000000
// EXCEPTION_                  = 0x2000000
// EXCEPTION_                  = 0x4000000

  ,  MISSED_STALL                   = ILLEGAL_RETE_USE               << 1

  ,  BAD_DMC_RSTATUS                = MISSED_STALL                   << 1

  ,  SE_L2_ERROR                    = BAD_DMC_RSTATUS                << 1
  ,  SE_INTERNAL_ERROR              = SE_L2_ERROR                    << 1

  ,  ILLEGAL_INSTR_IN_UNPROT        = SE_INTERNAL_ERROR              << 1
  ,  DIVIDE_BY_ZERO                 = ILLEGAL_INSTR_IN_UNPROT        << 1

  ,  OUT_OF_RANGE_ADDR_ON_DMC       = DIVIDE_BY_ZERO                 << 1
  ,  OUT_OF_RANGE_ADDR_ON_CR        = OUT_OF_RANGE_ADDR_ON_DMC       << 1

  ,  HWA_MMA_INSTR_WO_MMA           = OUT_OF_RANGE_ADDR_ON_CR        << 1
  ,  HWA_MMA_BAD_STATUS             = HWA_MMA_INSTR_WO_MMA           << 1
} c7x_exception_t;

// How to populate the IESR bit 15:0
typedef enum
{
    IESR_NOUPDATE    = 0
  , IESR_PMC_RS11
  , IESR_UTLB_RS
  , IESR_SE_RS11
  , IESR_PMC_RS3
  , IESR_LUT_BASE
  , IESR_ECR_STAT
  , IESR_DMC_RS
  , IESR_SE_RS3
  , IESR_MMA_RS
} c7x_iesr_update_t;

// Describes how the IEAR register gets populated in an exception
typedef enum
{
    IEAR_NONE                 = 0
  , IEAR_ATTEMPTED_FETCH_ADDR
  , IEAR_EPKT_ADDR
  , IEAR_ECR_REG_ADDR
  , IEAR_CR_ADDR
  , IEAR_FAULTING_ADDR              // LD/ST read/write address
} c7x_iear_update_t;

typedef enum
{
    IEDR_NONE = 0
  , IEDR_WRITE_DATA
} c7x_iedr_update_t;

struct c7x_exception_prop_t
{
  c7x_exception_t   exception_code;
  uint64_t          ierr_val;
  uint64_t          iesr_val;
  c7x_iesr_update_t iesr_update;
  c7x_iear_update_t iear_update;
  c7x_iedr_update_t iedr_update;
  uint32_t          priority;
  bool              isLoki;     // Supported by loki
  std::string       to_string;

  c7x_exception_prop_t( c7x_exception_t   code,
                        uint64_t          ierr,
                        uint64_t          iesr3,  // 63:20
                        uint64_t          iesr2,  // 19:16
                        uint64_t          iesr1,  // 15:0
                        c7x_iesr_update_t iesr_up,
                        c7x_iear_update_t iear,
                        c7x_iedr_update_t iedr,
                        uint32_t          prior,
                        bool              isL,
                        std::string       str )
  : exception_code ( code                           )
  , ierr_val       ( ierr                           )
  , iesr_val       ( (   iesr3            << 20 ) | 
                     ( ( iesr2 & 0xf    ) << 16 ) |
                     ( ( iesr1 & 0xffff )       )   )
  , iesr_update    ( iesr_up                        )
  , iear_update    ( iear                           )
  , iedr_update    ( iedr                           )
  , priority       ( prior                          )
  , isLoki         ( isL                            )
  , to_string      ( std::move( str )               ) { }
};

typedef struct
{
  uint64_t ierr;
  uint64_t iesr;
  uint64_t iear;
  uint64_t iedr;
} c7x_exception_registers_t;

extern std::map< c7x_exception_t, c7x_exception_prop_t > c7x_exception_prop_map;


} // end namespace
#endif




