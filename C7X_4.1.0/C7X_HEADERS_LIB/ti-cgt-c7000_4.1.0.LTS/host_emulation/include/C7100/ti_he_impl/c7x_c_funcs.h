/*****************************************************************************/
/*  C7X_C_FUNCS.H                                                            */
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
#ifndef _C7X_C_FUNCS_H_
#define _C7X_C_FUNCS_H_

#include <string>
#include <cmath>
/*** START CG REPLACE ***/
#include <ti_he_impl/global.h>
#include <ti_he_impl/get_endian.h>
#include <ti_he_impl/vreg.h>

// Definitions provided by c7x_core_global.h
#include <ti_he_impl/c7x_core_global.h>
#if 0
#define VEC_BIT_SIZE            (512)
#define NUM_BYTE_VEC            (VEC_BIT_SIZE / 8 )
#define NUM_HWORD_VEC           (VEC_BIT_SIZE / 16)
#define NUM_WORD_VEC            (VEC_BIT_SIZE / 32)
#define NUM_DWORD_VEC           (VEC_BIT_SIZE / 64)
#define NUM_BYTE_DVEC           ((VEC_BIT_SIZE * 2 ) /  8)
#define NUM_HWORD_DVEC          ((VEC_BIT_SIZE * 2 ) / 16)
#define NUM_WORD_DVEC           ((VEC_BIT_SIZE * 2 ) / 32)
#define NUM_DWORD_DVEC          ((VEC_BIT_SIZE * 2 ) / 64)
#define NUM_CR                  (80)
#endif
/*** END CG REPLACE ***/

#if defined(BYTE_BE)
  //Extract bytes/half words from a word
  #define INT8(x, i)            *((int8_t *) &x + (i ^ 3))
  #define UINT8(x, i)           *((uint8_t *) &x + (i ^ 3))
  #define INT16(x, i)           *((int16_t *) &x + (i ^ 1))
  #define UINT16(x, i)          *((uint16_t *) &x + (i ^ 1))
  //Extract bytes/half words from a double word
  #define DINT8(x, i)           *((int8_t *) &x + (i ^ 7))
  #define DUINT8(x, i)          *((uint8_t *) &x + (i ^ 7))
  #define DINT16(x, i)          *((int16_t *) &x + (i ^ 3))
  #define DUINT16(x, i)         *((uint16_t *) &x + (i ^ 3))
  //Extract low/high 32 bit int from a 64 bit int
  #define UINT32(x,i)           *((uint32_t *) &x + (i ^ 1))
  #define INT32(x,i)            *((int32_t *) &x + (i ^ 1))
#elif defined(BYTE_LE)
  //Extract bytes/half words from a word
  #define INT8(x, i)            *((int8_t *) &x + i)
  #define UINT8(x, i)           *((uint8_t *) &x + i)
  #define INT16(x, i)           *((int16_t *) &x + i)
  #define UINT16(x, i)          *((uint16_t *) &x + i)
  //Extract bytes/half words from a double word
  #define DINT8(x, i)           *((int8_t *) &x + i)
  #define DUINT8(x, i)          *((uint8_t *) &x + i)
  #define DINT16(x, i)          *((int16_t *) &x + i)
  #define DUINT16(x, i)         *((uint16_t *) &x + i)
  //Extract low/high 32 bit int from a 64 bit int
  #define UINT32(x,i)           *((uint32_t *) &x + i)
  #define INT32(x,i)            *((int32_t *) &x + i)
#endif

typedef vreg<4>                 __x128_t;    
typedef vreg<NUM_WORD_VEC>      vreg_t;    
typedef vreg<NUM_WORD_DVEC>     wreg_t;    
typedef uint64_t                vpred_t;

void get_unsigned_value         (int64_t val  , uint32_t &dst, uint32_t index);
void get_unsigned_value         (__x128_t val , uint32_t &dst, uint32_t index);
void get_unsigned_value         (vreg_t val   , uint32_t &dst, uint32_t index);
void get_unsigned_value         (wreg_t val   , uint32_t &dst, uint32_t index);

void get_unsigned_value         (vreg_t val   , uint64_t &dst, uint32_t index);
void get_unsigned_value         (wreg_t val   , uint64_t &dst, uint32_t index);

void get_signed_value           (int64_t val  , int32_t &dst , uint32_t index);
void get_signed_value           (__x128_t val , int32_t &dst , uint32_t index);
void get_signed_value           (vreg_t val   , int32_t &dst , uint32_t index);
void get_signed_value           (wreg_t val   , int32_t &dst , uint32_t index);

void get_signed_value           (vreg_t val   , int64_t &dst , uint32_t index);
void get_signed_value           (wreg_t val   , int64_t &dst , uint32_t index);

void put_unsigned_value         (int64_t &dst , uint32_t val , uint32_t index);
void put_unsigned_value         (__x128_t &dst, uint32_t val , uint32_t index);
void put_unsigned_value         (vreg_t &dst  , uint32_t val , uint32_t index);
void put_unsigned_value         (wreg_t &dst  , uint32_t val , uint32_t index);

void put_unsigned_value         (vreg_t &dst  , uint64_t val , uint32_t index);
void put_unsigned_value         (wreg_t &dst  , uint64_t val , uint32_t index);

void put_signed_value           (int64_t &dst , int32_t val  , uint32_t index);
void put_signed_value           (__x128_t &dst, int32_t val  , uint32_t index);
void put_signed_value           (vreg_t &dst  , int32_t val  , uint32_t index);
void put_signed_value           (wreg_t &dst  , int32_t val  , uint32_t index);

void put_signed_value           (vreg_t &dst  , int64_t val  , uint32_t index);
void put_signed_value           (wreg_t &dst  , int64_t val  , uint32_t index);

/*** START CG REPLACE ***/
// All we use from this file is the (get|put)_(un)?signed_value decls.
// We generate our own semantic function declarations.
#if 0
void _vmatmpyhw_vvv             (vreg_t src1a, vreg_t src1b, vreg_t src2a, vreg_t src2b, vreg_t &dst_result, bool isMunit);
void _vmatmpysuhw_vvv           (vreg_t src1a, vreg_t src1b, vreg_t src2a, vreg_t src2b, vreg_t &dst_result, bool isMunit);
void _vmatmpyushw_vvv           (vreg_t src1a, vreg_t src1b, vreg_t src2a, vreg_t src2b, vreg_t &dst_result, bool isMunit);
void _vmatmpyuhw_vvv            (vreg_t src1a, vreg_t src1b, vreg_t src2a, vreg_t src2b, vreg_t &dst_result, bool isMunit);
void _vmatmpyrhd_vvw            (vreg_t src1a, vreg_t src1b, vreg_t src2a, vreg_t src2b, vreg_t &dst_result);
void _vmatmpyrsuhd_vvw          (vreg_t src1a, vreg_t src1b, vreg_t src2a, vreg_t src2b, vreg_t &dst_result);
void _vmatmpyrushd_vvw          (vreg_t src1a, vreg_t src1b, vreg_t src2a, vreg_t src2b, vreg_t &dst_result);
void _vmatmpyruhd_vvw           (vreg_t src1a, vreg_t src1b, vreg_t src2a, vreg_t src2b, vreg_t &dst_result);

void _vfir4hw_vww               (vreg_t src1, vreg_t src2a, vreg_t src2b, vreg_t &dst_result);
void _vfir4suhw_vww             (vreg_t src1, vreg_t src2a, vreg_t src2b, vreg_t &dst_result);
void _vfir4uhw_vww              (vreg_t src1, vreg_t src2a, vreg_t src2b, vreg_t &dst_result);

void _vfir8hw_wvv               (vreg_t src1a, vreg_t src1b, vreg_t src2a, vreg_t src2b, vreg_t &dst_result, bool isMunit);
void _vfir8suhw_wvv             (vreg_t src1a, vreg_t src1b, vreg_t src2a, vreg_t src2b, vreg_t &dst_result, bool isMunit);
void _vfir8shw_wvv              (vreg_t src1a, vreg_t src1b, vreg_t src2a, vreg_t src2b, vreg_t &dst_result, bool isMunit);

void _vfir8hd_wvw               (vreg_t src1a, vreg_t src1b, vreg_t src2a, vreg_t src2b, vreg_t &dst_result);
void _vfir8suhd_wvw             (vreg_t src1a, vreg_t src1b, vreg_t src2a, vreg_t src2b, vreg_t &dst_result);
void _vfir8shd_wvw              (vreg_t src1a, vreg_t src1b, vreg_t src2a, vreg_t src2b, vreg_t &dst_result);

void _divudw_drd                (int64_t src1, int32_t src2, int64_t &dst_result, fp_excep_t &fsr);
void _divuw_rrr                 (int32_t src1, int32_t src2, int64_t &dst_result, fp_excep_t &fsr);
void _divdw_drd                 (int64_t src1, int32_t src2, int64_t &dst_result, fp_excep_t &fsr);
void _divw_rrr                  (int32_t src1, int32_t src2, int64_t &dst_result, fp_excep_t &fsr);  

void _modudw_drd                (int64_t src1, int32_t src2, int64_t &dst_result, fp_excep_t &fsr);
void _moduw_rrr                 (int32_t src1, int32_t src2, int64_t &dst_result, fp_excep_t &fsr);
void _moddw_drd                 (int64_t src1, int32_t src2, int64_t &dst_result, fp_excep_t &fsr);
void _modw_rrr                  (int32_t src1, int32_t src2, int64_t &dst_result, fp_excep_t &fsr);

void _mvc_fv                    (vreg_t src1, vreg_t &dst_result);
void _mvc_vf                    (vreg_t src1, vreg_t &dst_result);
#endif
/*** END CG REPLACE ***/

#endif                                                                      
                                                                            
                                                                            
