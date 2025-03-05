/*****************************************************************************/
/*  C7X_HE_LUTHIST.H v#####                                                  */
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
#ifndef C7X_HE_LUTHIST_H
#define C7X_HE_LUTHIST_H

#include <stdint.h>
#include "c7x_he_cr.h"
#include "lut.h"

extern lut LUT_SET0;
extern lut LUT_SET1;
extern lut LUT_SET2;
extern lut LUT_SET3;

/*****************************************************************************/
/* LOOKUP TABLE / HISTOGRAM DATA BLOCK (Size is size of L1D cache)           */
/*****************************************************************************/
extern int8_t lut_sram[32768];

/*****************************************************************************/
/* LOOKUP TABLE / HISTOGRAM CONTROLS AND SETUP FLAGS                         */
/*****************************************************************************/
/*----------------------------------------------------------------------------*/
/* Enable or disable LUT/HIST in TSR                                          */
/* Use these macros to enable or disable the 19th bit in TSR register         */
/* corresponding to turning ON or OFF the LUT/HIST feature.                   */
/*----------------------------------------------------------------------------*/
#define __LUT_DISABLE         (0)
#define __LUT_ENABLE          (1)

/*----------------------------------------------------------------------------*/
/* LUT/HIST L1D page sizes.                                                   */
/* Use the below options to indicate the LUT/HIST page size in L1D.           */
/* As per spec the page sizes can only be in multiples of 4kb, from a min of  */
/* 0kb to 16kb.                                                               */
/*----------------------------------------------------------------------------*/
#define __LUT_MAP_0KB        (0x00)
#define __LUT_MAP_4KB        (0x01)
#define __LUT_MAP_8KB        (0x03)
#define __LUT_MAP_12KB       (0x07)
#define __LUT_MAP_16KB       (0x0F)

/*----------------------------------------------------------------------------*/
/* LUT/HIST set number                                                        */
/* Upto 4 sets of different configurations can be pre programmed using the    */
/* LTBR0-3 and LTCR0-3 control registers. Use the indexes below to indicate   */
/* control register in use.                                                   */
/* Ex. using __LUT_SET2 will indicate that the programmer is using LTBR2      */
/* and LTCR2 registers.                                                       */
/*----------------------------------------------------------------------------*/
#define __LUT_SET0            (0)
#define __LUT_SET1            (1)
#define __LUT_SET2            (2)
#define __LUT_SET3            (3)

/*----------------------------------------------------------------------------*/
/* LUT/HIST LTCR configuration.                                               */
/*----------------------------------------------------------------------------*/
/* Histogram Weight Sizes.                                                    */
/* Use these macros to indicate weight sizes.                                 */
/* Supported values are 8bit and 16bit sizes.                                 */
/*----------------------------------------------------------------------------*/
#define __LUT_WSIZE_8BIT        (0)
#define __LUT_WSIZE_16BIT       (1)

/*----------------------------------------------------------------------------*/
/* LUT/HIST LTCR configuration.                                               */
/*----------------------------------------------------------------------------*/
/* Interpolation mode.                                                        */
/* Use these macros to enable or disable interpolated table lookup.           */
/*----------------------------------------------------------------------------*/
#define __LUT_INTERP_OFF (0)
#define __LUT_INTERP_2X  (1)
#define __LUT_INTERP_4X  (2)
#define __LUT_INTERP_8X  (3)

/*----------------------------------------------------------------------------*/
/* LUT/HIST LTCR configuration.                                               */
/*----------------------------------------------------------------------------*/
/* Saturation mode.                                                           */
/* Use these macros to enable or disable saturation while computing histogram */
/*----------------------------------------------------------------------------*/
#define __LUT_SAT_OFF   (0)
#define __LUT_SAT_ON    (1)

/*----------------------------------------------------------------------------*/
/* LUT/HIST LTCR configuration.                                               */
/*----------------------------------------------------------------------------*/
/* Sign of data.                                                              */
/* Use these macros to indicate signed or unsigned data.                      */
/*----------------------------------------------------------------------------*/
#define __LUT_UNSIGNED    (0)
#define __LUT_SIGNED      (1)

/*----------------------------------------------------------------------------*/
/* LUT/HIST LTCR configuration.                                               */
/*----------------------------------------------------------------------------*/
/* Number of tables.                                                          */
/* Use these macros to indicate number of parallel tables and histograms.     */
/* The supported number are 1, 2, 4, 8, 16 parallel tables/histograms         */
/*----------------------------------------------------------------------------*/
#define __LUT_NUM_TBL_16      (4)
#define __LUT_NUM_TBL_8       (3)
#define __LUT_NUM_TBL_4       (2)
#define __LUT_NUM_TBL_2       (1)
#define __LUT_NUM_TBL_1       (0)

/*----------------------------------------------------------------------------*/
/* LUT/HIST LTCR configuration.                                               */
/*----------------------------------------------------------------------------*/
/* Element size.                                                              */
/* Use these macros to indicate bit depth of data.                            */
/* Supported values are 8bit, 16bit and 32bit depths.                         */
/*----------------------------------------------------------------------------*/
#define __LUT_ELETYPE_8BIT        (0)
#define __LUT_ELETYPE_16BIT       (1)
#define __LUT_ELETYPE_32BIT       (2)

/*----------------------------------------------------------------------------*/
/* LUT/HIST LTCR configuration.                                               */
/*----------------------------------------------------------------------------*/
/* Table sizes.                                                               */
/* Use these macros to indicate the size of SRAM memory                       */
/* allocated to each table.                                                   */
/* Supported values are 0.5, 1, 2, 4, 8, 16, 32 KBytes.                       */
/*----------------------------------------------------------------------------*/
#define __LUT_TBL_SIZE_512BYTES      (0)
#define __LUT_TBL_SIZE_1KBYTES       (1)
#define __LUT_TBL_SIZE_2KBYTES       (2)
#define __LUT_TBL_SIZE_4KBYTES       (3)
#define __LUT_TBL_SIZE_8KBYTES       (4)
#define __LUT_TBL_SIZE_16KBYTES      (5)
#define __LUT_TBL_SIZE_32KBYTES      (6)

/*----------------------------------------------------------------------------*/
/* LUT/HIST LTCR configuration.                                               */
/*----------------------------------------------------------------------------*/
/* Promote options.                                                           */
/* Single power of 2 promotes are possible using below options.               */
/*----------------------------------------------------------------------------*/
#define __LUT_PROMOTE_OFF  (0)
#define __LUT_PROMOTE_2X   (1)
#define __LUT_PROMOTE_4X   (2)
#define __LUT_PROMOTE_8X   (3)

/*----------------------------------------------------------------------------*/
/* LUT/HIST LTCR configuration.                                               */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* struct : __sLTCRFlags_t                                                    */
/* Desc   : Structure to hold predefined LTCR flags.                          */
/*                                                                            */
/* elements:   uint8_t INTERPOLATION                                          */
/*              - Flag to enable/disable interpolated table lookup.           */
/*             uint8_t SATURATION                                             */
/*              - Flag to enable/disable saturation in histograms.            */
/*             uint8_t SIGNUNSIGN                                             */
/*              - Flag to inidicate signed or unsigned data.                  */
/*             uint8_t ELETYPE                                                */
/*              - Flag to indicate the bit depth of data.                     */
/*             uint8_t NUMTBLS                                                */
/*              - Flag to indicate the number of parallel tables.             */
/*             uint8_t TBLSIZE                                                */
/*              - Flag to indicate the size of mem allocated for each table.  */
/*             uint8_t WEIGHTSIZE                                             */
/*              - Flag to indicate the histogram weight sizes.                */
/*             uint8_t PROMOTION                                              */
/*              - Flag to indicate the data promotion level (unpack).         */
/*                                                                            */
/*----------------------------------------------------------------------------*/
typedef struct _sLTCR_t
{
   uint8_t INTERPOLATION;
   uint8_t SATURATION;
   uint8_t SIGNUNSIGN;
   uint8_t ELETYPE;
   uint8_t NUMTBLS;
   uint8_t TBLSIZE;
   uint8_t WEIGHTSIZE;
   uint8_t PROMOTION;

} __sLTCRFlags_t;

/*----------------------------------------------------------------------------*/
/* Use this macro to set the 19th TSR bit which enables or disables the       */
/* LUT/HIST at device level.                                                  */
/*----------------------------------------------------------------------------*/
#define __LUT_SET_TSR(enable) \
   TSR = (enable << 19);

/*----------------------------------------------------------------------------*/
/* Use this macro to set or clear the LTER bits to enable or disable          */
/* individual LUT/HIST sets.                                                  */
/*----------------------------------------------------------------------------*/
#define __LUT_ENABLE_0  0x1
#define __LUT_ENABLE_1  0x2
#define __LUT_ENABLE_2  0x4
#define __LUT_ENABLE_3  0x8

#define __LUT_SET_LTER(flags) \
   __LTER = flags; 

/*----------------------------------------------------------------------------*/
/* Use this macro to set the LTBR register. The setIdx is used to             */
/* indicate 1 out of 4 LTBR registers. The base address must be 128 bytes     */
/* aligned of 16bit length.                                                   */
/*----------------------------------------------------------------------------*/
#define __LUT_SET_LTBR(setIdx, baseAddr) \
if(setIdx == __LUT_SET0)\
   __LTBR0 = baseAddr;\
if(setIdx == __LUT_SET1)\
   __LTBR1 = baseAddr;\
if(setIdx == __LUT_SET2)\
   __LTBR2 = baseAddr;\
if(setIdx == __LUT_SET3)\
   __LTBR3 = baseAddr;

/*----------------------------------------------------------------------------*/
/* Use this macro to set the LTCR register. The setIdx is used to indicate 1  */
/* out of 4 LTCR registers, and flags indicates a 32bit value packed with the */
/* appropriate flags (as returned from __lut_set_param()).                    */
/*                                                                            */
/* e.g.: __LUT_SET_LTCR(__LUT_SET2, __lut_set_param(&flags));                 */
/*----------------------------------------------------------------------------*/
#define __LUT_SET_LTCR(setIdx, flags) \
if(setIdx == __LUT_SET0)\
   __LTCR0 = flags;\
if(setIdx == __LUT_SET1)\
   __LTCR1 = flags;\
if(setIdx == __LUT_SET2)\
   __LTCR2 = flags;\
if(setIdx == __LUT_SET3)\
   __LTCR3 = flags;

/*----------------------------------------------------------------------------*/
/* Func: __lut_set_param                                                      */
/*                                                                            */
/* Args: __sLTCRFlags_t *pLTCRFlags                                           */
/*            - Pointer to __sLTCRFlags_t structure.                          */
/*                                                                            */
/* Return: Returns a 32bit value packed with LTCR flags                       */
/*                                                                            */
/* Desc: This function is used to set the LTCR flags. The options are         */
/*       read from structure pointer and packed.                              */
/*                                                                            */
/*----------------------------------------------------------------------------*/
uint32_t __lut_set_param(__sLTCRFlags_t *pLTCRFlags);

/*****************************************************************************/
/* The __LUT_SET argument indicates which LTBRx/LTCRx set reg to use.  The   */
/* corresponding LTCR and LTBR registers are implied by the given __LUT_SET. */
/*****************************************************************************/

#define __LUT_SET int32_t

/*****************************************************************************/
/* __lookup_init function is only enabled for full (all lanes filled) vectors*/
/* with element type uint8_t, uint16_t or uint32_t.                          */
/*****************************************************************************/
template<typename ELEM_T, size_t NELEM,
         typename = typename std::enable_if< 
                       std::is_same<ELEM_T, uint8_t>::value
                    || std::is_same<ELEM_T, uint16_t>::value
                    || std::is_same<ELEM_T, uint32_t>::value>::type,
         typename = typename std::enable_if<(NELEM * sizeof(ELEM_T) == 64)>::type>
void __lookup_init  (__LUT_SET index, 
                     _c70_he_detail::vtype<ELEM_T, NELEM> src, 
                     uint32_t off)
{
    switch(index)
    {
        case 0:
           LUT_SET0.lutinit(src, __LTBR0 + (uint64_t)&lut_sram[0], __LTCR0, off); 
           break;
        case 1:
           LUT_SET1.lutinit(src, __LTBR1 + (uint64_t)&lut_sram[0], __LTCR1, off); 
           break;
        case 2:
           LUT_SET2.lutinit(src, __LTBR2 + (uint64_t)&lut_sram[0], __LTCR2, off); 
           break;
        case 3:
           LUT_SET3.lutinit(src, __LTBR3 + (uint64_t)&lut_sram[0], __LTCR3, off); 
           break;
    }
}

void __lookup_write (__LUT_SET index, __uint16 src, __uint16 off);

template<typename ELEM_T>
_c70_he_detail::vtype<ELEM_T, 16> __lookup_read(__LUT_SET index, __uint16 off)
{
    _c70_he_detail::vtype<ELEM_T, 16> ret = _c70_he_detail::vtype<ELEM_T, 16>(0);
    vreg_t ret_vec = vreg_t(ret);

    switch(index)
    {
        case 0:
           LUT_SET0.lutrd(__LTBR0 + (uint64_t)&lut_sram[0], __LTCR0, off, &ret_vec, 16); 
           break;
        case 1:
           LUT_SET1.lutrd(__LTBR1 + (uint64_t)&lut_sram[0], __LTCR1, off, &ret_vec, 16); 
           break;
        case 2:
           LUT_SET2.lutrd(__LTBR2 + (uint64_t)&lut_sram[0], __LTCR2, off, &ret_vec, 16); 
           break;
        case 3:
           LUT_SET3.lutrd(__LTBR3 + (uint64_t)&lut_sram[0], __LTCR3, off, &ret_vec, 16); 
           break;
    }
    return _c70_he_detail::vtype<ELEM_T, 16>(ret_vec);
}

template<typename ELEM_T>
_c70_he_detail::vtype<ELEM_T, 8> __lookup_read_dword(__LUT_SET index, __uint8 off)
{
    _c70_he_detail::vtype<ELEM_T, 8> ret = _c70_he_detail::vtype<ELEM_T, 8>(0);
    vreg_t ret_vec = vreg_t(ret);

    switch(index)
    {
        case 0:
           LUT_SET0.lutrd(__LTBR0 + (uint64_t)&lut_sram[0], __LTCR0, off, &ret_vec, 8); 
           break;
        case 1:
           LUT_SET1.lutrd(__LTBR1 + (uint64_t)&lut_sram[0], __LTCR1, off, &ret_vec, 8); 
           break;
        case 2:
           LUT_SET2.lutrd(__LTBR2 + (uint64_t)&lut_sram[0], __LTCR2, off, &ret_vec, 8); 
           break;
        case 3:
           LUT_SET3.lutrd(__LTBR3 + (uint64_t)&lut_sram[0], __LTCR3, off, &ret_vec, 8); 
           break;
    }
    return _c70_he_detail::vtype<ELEM_T, 8>(ret_vec);
}

/*****************************************************************************/
/* Declare function pointers for __lookup_read_[type] functions. Will be     */
/* initialized to a specific template substitution of __lookup_read. This    */
/* allows a central definition to be used to define the entire               */
/* __lookup_read_[type] interface.                                           */ 
/*****************************************************************************/
extern __char16   (*__lookup_read_char)   (__LUT_SET, __uint16);
extern __uchar16  (*__lookup_read_uchar)  (__LUT_SET, __uint16);
extern __short16  (*__lookup_read_short)  (__LUT_SET, __uint16);
extern __ushort16 (*__lookup_read_ushort) (__LUT_SET, __uint16);
extern __int16    (*__lookup_read_int)    (__LUT_SET, __uint16);
extern __uint16   (*__lookup_read_uint)   (__LUT_SET, __uint16);
extern __long8    (*__lookup_read_long)   (__LUT_SET, __uint8);
extern __ulong8   (*__lookup_read_ulong)  (__LUT_SET, __uint8);

void __hist (__LUT_SET index, __uint16 off);

void __hist_weighted(__LUT_SET index, __int16 weight, __uint16 off);

#endif /* C7X_HE_LUTHIST_H */
