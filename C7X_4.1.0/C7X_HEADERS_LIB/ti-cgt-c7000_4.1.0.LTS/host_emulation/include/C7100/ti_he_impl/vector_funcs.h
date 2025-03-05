/*****************************************************************************/
/*  VECTOR_FUNCS.H                                                           */
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
#ifndef VECTOR_FUNCS_H
#define VECTOR_FUNCS_H

#include <ti_he_impl/vector.h>

/*****************************************************************************
* Function used to deinterleave wreg_t into 2 registers on 64-bit bounds.
* This function is always executed after a semantic function call and occurs
* in loki_c7x during simulation. 
*****************************************************************************/
void deinterleave_wreg_t_output(const wreg_t &src, vreg_t &lo, vreg_t &hi);

/*****************************************************************************
* Enum to classify how the output values of a register pair are interleaved  
*****************************************************************************/
enum class INTRLV_TYPE { HALF, WORD, DOUBLE };

/*****************************************************************************
* Function used to convert a wreg_t into a vreg_t based on how the output is
* interleaved. The output vreg_t is the lo portion of the register pair. 
* Currently, we can only expect 512 bit vectors and these relevant bits exist 
* in the lo porition of the reg pair.
*
* This function executes deinterleaving on 64-bit boundaries and then executes
* deinterleaving based on the INTRLV_TYPE enum value. This directly emulates
* how deinterleaving is executed for C7000.
*****************************************************************************/
vreg_t convert_from_wreg_t(const wreg_t &src, INTRLV_TYPE intrlv_type);

/*****************************************************************************
* Function used to take lo and hi portions of a "reg pair" and convert to a 
* wreg_t that semantic functions expect.
*****************************************************************************/
wreg_t interleave_wreg_t_input(const vreg_t &src_hi, const vreg_t &src_lo);

/*****************************************************************************
* Function used to convert vreg_ts into a wreg_t, inclusive of interleaving
* the compiler would perform, and interleaving needed for the semantic
* functions.
*****************************************************************************/
wreg_t convert_to_wreg_t(const vreg_t &src_hi, const vreg_t &src_lo);

#endif /* VECTOR_FUNCS_H */
