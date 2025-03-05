/*****************************************************************************/
/*  C7X_HE_CR.H v#####                                                       */
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
#ifndef C7X_HE_CR_H
#define C7X_HE_CR_H
#include <stdint.h>
#include <array>

/*****************************************************************************/
/* CONTROL REGISTER DECLARATIONS (General)                                   */
/*****************************************************************************/
extern uint64_t __CPUID;
extern uint64_t __PMR;
extern uint64_t __DNUM;
extern uint64_t __TSC;
extern uint64_t __TSR;
extern uint64_t __RP;
extern uint64_t __BPCR;
extern uint64_t __STSC;

/*****************************************************************************/
/* CONTROL REGISTER DECLARATIONS (Computation)                               */
/*****************************************************************************/
extern uint64_t __FPCR;
extern uint64_t __FSR;
extern uint64_t __GPLY;
extern uint64_t __GFPGFR;

/*****************************************************************************/
/* CONTROL REGISTER DECLARATIONS (Events)                                    */
/*****************************************************************************/
extern uint64_t __DEPR;
extern uint64_t __IESET;
extern uint64_t __ESTP_SS;
extern uint64_t __ESTP_S;
extern uint64_t __ESTP_GS;
extern uint64_t __ECSP_SS;
extern uint64_t __ECSP_S;
extern uint64_t __ECSP_GS;
extern uint64_t __TCSP;
extern uint64_t __RXMR_SS;
extern uint64_t __RXMR_S;
extern uint64_t __AHPEE;
extern uint64_t __PHPEE;
extern uint64_t __IPE;
extern uint64_t __IERR;
extern uint64_t __IEAR;
extern uint64_t __IESR;
extern uint64_t __IEDR;
extern uint64_t __TCR;
extern uint64_t __TCCR;
extern uint64_t __GMER;
extern uint64_t __UMER;
extern uint64_t __SPBR;
extern uint64_t __UFCMR;

/*****************************************************************************/
/* CONTROL REGISTER DECLARATIONS (Lookup Table and Histogram)                */
/*****************************************************************************/
extern uint64_t __LTBR0;
extern uint64_t __LTBR1;
extern uint64_t __LTBR2;
extern uint64_t __LTBR3;
extern uint64_t __LTCR0;
extern uint64_t __LTCR1;
extern uint64_t __LTCR2;
extern uint64_t __LTCR3;
extern uint64_t __LTER;

/*****************************************************************************/
/* CONTROL REGISTER DECLARATIONS (Debug)                                     */
/*****************************************************************************/
extern uint64_t __DBGCTXT;
extern uint64_t __ILCNT;
extern uint64_t __OLCNT;
extern uint64_t __LCNTFLG;
extern uint64_t __SCRB;

/*****************************************************************************/
/* INDEXED CONTROL REGISTER ACCESS                                           */
/*                                                                           */
/* Use the enum below with the __get_indexed() or __set_indexed intrinsics.  */
/*****************************************************************************/
typedef enum
{
    __ECLMR = 0,
    __EASGR = 1,
    __EPRI  = 2,
    __EER   = 3,
    __EESET = 4,
    __EECLR = 5,
    __EFR   = 6,
    __EFSET = 7,
    __EFCLR = 8,
    __EDR   = 9
} __INDEXED_CR;

template <size_t NELEM>
struct indexed_creg_arr
{
    indexed_creg_arr(uint64_t init_val) : data()
    {
        for (size_t i = 0; i < NELEM; i++)
            data[i] = init_val;
    }

    uint64_t& operator[](size_t index)
    {
        return data[index];
    }

    uint64_t data[NELEM];
};

extern indexed_creg_arr<64> ECLMR_SET;
extern indexed_creg_arr<64> EASGR_SET;
extern indexed_creg_arr<64> EPRI_SET;
extern indexed_creg_arr<64> EER_SET;
extern indexed_creg_arr<64> EESET_SET;
extern indexed_creg_arr<64> EECLR_SET;
extern indexed_creg_arr<64> EFR_SET;
extern indexed_creg_arr<64> EFSET_SET;
extern indexed_creg_arr<64> EFCLR_SET;
extern indexed_creg_arr<64> EDR_SET;
extern indexed_creg_arr<64> GTSC_SET;

/*****************************************************************************/
/* Include the ECR (Extended Control Register) set.                          */
/*****************************************************************************/
#include "c7x_he_ecr.h"

#endif /* C7X_HE_CR_H */

