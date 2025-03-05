/*****************************************************************************/
/*  VREG.H                                                                   */
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
#ifndef _VREG_H_
#define _VREG_H_

#include <stdint.h>

enum data_size {BYTE_T, HALF_T, WORD_T, DWORD_T, QWORD_T};

/*** START CG ADD ***/
typedef data_size element_type;
/*** END CG ADD ***/

template <unsigned SIZE> // size == number of words in a vector register
class vreg
{
  private:
/*** START CG REPLACE ***/
#if 1
/*** END CG REPLACE ***/
    static inline int bie(int i) { return i; } // byte index for endian
    static inline int hie(int i) { return i; } // half index for endian
    static inline int wie(int i) { return i; } // word index for endian
#elif defined(BYTE_BE)
    static inline int bie(int i) { return i ^ 3; }
    static inline int hie(int i) { return i ^ 1; }
    static inline int wie(int i) { return i;     }
#endif

  public:
    /*
    typedef uint32_t vreg_array[SIZE];
    vreg_array r;
        
    uint8_t  &u8 (int i) { return *(bie(i) + (uint8_t  *)r); } 
    int8_t   &s8 (int i) { return *(bie(i) + ( int8_t  *)r); }
    uint16_t &u16(int i) { return *(hie(i) + (uint16_t *)r); } 
    int16_t  &s16(int i) { return *(hie(i) + ( int16_t *)r); }
    uint32_t &u32(int i) { return *(wie(i) + (uint32_t *)r); } 
    int32_t  &s32(int i) { return *(wie(i) + ( int32_t *)r); }
    uint64_t &u64(int i) { return      *(i + (uint64_t *)r); } 
    int64_t  &s64(int i) { return      *(i + ( int64_t *)r); }
    */

    typedef uint8_t  vreg8_array[(SIZE*4)];
    typedef uint16_t vreg16_array[(SIZE*2)];
    typedef uint32_t vreg32_array[SIZE];
    typedef uint64_t vreg64_array[(SIZE/2)];

    typedef union {
      vreg32_array r32;
      vreg8_array r8;
      vreg16_array r16;
      vreg64_array r64;
    } vreg_array;

    vreg_array r; //Think of the vreg_array as an array of 32 bit integers even though 
                  //it is an Union for all type of element accesses u8, u16, u32, u64..etc 
        
/*** START CG REPLACE ***/
    uint8_t  &u8 (int i) { return *(this->bie(i) + r.r8); } 
    uint16_t &u16(int i) { return *(this->hie(i) + r.r16); } 
/*** END CG REPLACE ***/
    uint32_t &u32(int i) { return *(i + r.r32); } 
    uint64_t &u64(int i) { return *(i + r.r64); } 

/*** START CG REPLACE ***/
    int8_t  &s8 (int i) { return *(this->bie(i) + (int8_t  *) r.r8); }
    int16_t &s16(int i) { return *(this->hie(i) + (int16_t *) r.r16); }
/*** END CG REPLACE ***/
    int32_t &s32(int i) { return *(i + (int32_t *) r.r32); }
    int64_t &s64(int i) { return *(i + (int64_t *) r.r64); }
};

#endif
