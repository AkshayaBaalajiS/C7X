/*****************************************************************************/
/*  C7X_ILUTHIST.H                                                           */
/*                                                                           */
/* Copyright (c) 2022 Texas Instruments Incorporated                         */
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
#ifndef __C7X_H_INCLUDE__
#error "This file can only be included by parent header c7x.h"
#endif

#if defined(__C7524__)

#ifndef __C7X_ILUTHIST_H
#define __C7X_ILUTHIST_H

/*----------------------------------------------------------------------------*/
/* NOTE: Some ILUT operations require the MMA. See c7x_mma.h for those        */
/*       operations.                                                          */
/*----------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* Use these macros to set or clear the ILTER bits to modify read and write  */
/* permissions for the ILUT.  (e.g. __ILTER = __ILUT_RW;)                    */
/*---------------------------------------------------------------------------*/
#define __ILUT_DISALLOWED 0x0
#define __ILUT_RD 0x1
#define __ILUT_WR 0x2
#define __ILUT_RW 0x3

/*---------------------------------------------------------------------------*/
/* Use these macros to set or clear ILTCR bits to configure signedness and   */
/* saturation of IWHIST increments.  (e.g __ILTCR = __ILUT_UNSIGNED |        */
/* __ILUT_SAT_ON;).                                                          */
/*---------------------------------------------------------------------------*/
#define __ILUT_UNSIGNED     0
#define __ILUT_SIGNED     0x1
#define __ILUT_SAT_OFF      0
#define __ILUT_SAT_ON   0x100

/*----------------------------------------------------------------------------*/
/* __ilut_init                                                                */
/*   Initialize the table by writing copies of the value src to entry number  */
/*   "idx" for all lanes.  These intrinsics map to the ILUTINIT[B/H/W]        */
/*   instructions.                                                            */
/*----------------------------------------------------------------------------*/
void __OVBIFM __ilut_init(unsigned idx, signed char src);
void __OVBIFM __ilut_init(unsigned idx, unsigned char src);
void __OVBIFM __ilut_init(unsigned idx, signed short src);
void __OVBIFM __ilut_init(unsigned idx, unsigned short src);
void __OVBIFM __ilut_init(unsigned idx, signed int src);
void __OVBIFM __ilut_init(unsigned idx, unsigned int src);

/*----------------------------------------------------------------------------*/
/* __ilut_read_*                                                              */
/*   Read the entries with indices specified by the LSB of each element of    */
/*   idx into the corresponding elements of the return value.  These          */
/*   intrinsics map to the ILUTRD[B/H/W] instructions.                        */
/*----------------------------------------------------------------------------*/
__char32   __BIFM __ilut_read_char  (__uchar32 idx);
__uchar32  __BIFM __ilut_read_uchar (__uchar32 idx);
__short16  __BIFM __ilut_read_short (__ushort16 idx);
__ushort16 __BIFM __ilut_read_ushort(__ushort16 idx);
__int8     __BIFM __ilut_read_int   (__uint8 idx);
__uint8    __BIFM __ilut_read_uint  (__uint8 idx);

/*----------------------------------------------------------------------------*/
/* __ilut_readh_*                                                             */
/*   Read the entries with indices specified by the MSB of each element of    */
/*   idx into the corresponding elements of the return value.  These          */
/*   intrinsics map to the ILUTRDH[B/H/W] instructions.                       */
/*----------------------------------------------------------------------------*/
__short16  __BIFM __ilut_readh_short (__ushort16 idx);
__ushort16 __BIFM __ilut_readh_ushort(__ushort16 idx);
__int8     __BIFM __ilut_readh_int   (__uint8 idx);
__uint8    __BIFM __ilut_readh_uint  (__uint8 idx);

/*----------------------------------------------------------------------------*/
/* __ilut_write                                                               */
/*   Write each element of src to entry number idx in the corresponding       */
/*   lane's table.  These intrinsics map to the ILUTWR instruction.           */
/*----------------------------------------------------------------------------*/
void __OVBIFM __ilut_write (unsigned idx, __char32 src);
void __OVBIFM __ilut_write (unsigned idx, __uchar32 src);
void __OVBIFM __ilut_write (unsigned idx, __short16 src);
void __OVBIFM __ilut_write (unsigned idx, __ushort16 src);
void __OVBIFM __ilut_write (unsigned idx, __int8 src);
void __OVBIFM __ilut_write (unsigned idx, __uint8 src);

/*----------------------------------------------------------------------------*/
/* __ihist                                                                    */
/*    Increment the entries specified by the LSB of each element of idx.      */
/*    Each lane has its own copy of the table, so you'll need to use a        */
/*    __horizontal_add to get the final total.  These intrinsics map to the   */
/*    IHIST[B/H/W] instructions.                                              */
/*----------------------------------------------------------------------------*/
void __OVBIFM __ihist (__uchar32 idx);
void __OVBIFM __ihist (__ushort16 idx);
void __OVBIFM __ihist (__uint8 idx);

/*----------------------------------------------------------------------------*/
/* __iwhist                                                                   */
/*   Increment the entries specified by the LSB of each element of idx by the */
/*   signed value given by the corresponding element of weight.  Each lane    */
/*   has its own copy of the table, so you'll need to use a __horizontal_add  */
/*   to get the final total.  These intrinsics map to the IWHIST[B/H/W]       */
/*   instructions.                                                            */
/*----------------------------------------------------------------------------*/
void __OVBIFM __iwhist (__uchar32 idx,  __char32 weight);
void __OVBIFM __iwhist (__ushort16 idx, __short16 weight);
void __OVBIFM __iwhist (__uint8 idx,    __int8 weight);

/*----------------------------------------------------------------------------*/
/* __ihist_read_*                                                             */
/*   Read entry number idx from each lane's instance of the table.  After     */
/*   each entry is read, it will be cleared to the value 0.  Each lane has    */
/*   its own instance of the table, so you'll need to use a __horizontal_add  */
/*   to get the final total.  These intrinsics map to the IHISTRD             */
/*   instruction.                                                             */
/*----------------------------------------------------------------------------*/
__char32   __BIFM __ihist_read_char  (unsigned idx);
__uchar32  __BIFM __ihist_read_uchar (unsigned idx);
__short16  __BIFM __ihist_read_short (unsigned idx);
__ushort16 __BIFM __ihist_read_ushort(unsigned idx);
__int8     __BIFM __ihist_read_int   (unsigned idx);
__uint8    __BIFM __ihist_read_uint  (unsigned idx);

#endif /* __C7X_ILUTHIST_H */

#endif /* __C7524__ */
