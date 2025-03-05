/*****************************************************************************/
/*  C7X_DIRECT.H                                                             */
/*                                                                           */
/* Copyright (c) 2015 Texas Instruments Incorporated                         */
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

#ifndef __C7X_DIRECT_H
#define __C7X_DIRECT_H

/*****************************************************************************/
/* Deprecated API names                                                      */
/*       OLD                 NEW                                             */
/*****************************************************************************/
#define  __vdsortdd16h_vv    __vdsortddh_vv
#define  __vdsortddu16h_vv   __vdsortdduh_vv
#define  __vdsortdi16h_vv    __vdsortdih_vv
#define  __vdsortdiu16h_vv   __vdsortdiuh_vv
#define  __vdsortid16h_vv    __vdsortidh_vv
#define  __vdsortidu16h_vv   __vdsortiduh_vv
#define  __vdsortii16h_vv    __vdsortiih_vv
#define  __vdsortiiu16h_vv   __vdsortiiuh_vv
#define  __vdsortpdd16h_vv   __vdsortpddh_vv
#define  __vdsortpddu16h_vv  __vdsortpdduh_vv
#define  __vdsortpdi16h_vv   __vdsortpdih_vv
#define  __vdsortpdiu16h_vv  __vdsortpdiuh_vv
#define  __vdsortpid16h_vv   __vdsortpidh_vv
#define  __vdsortpidu16h_vv  __vdsortpiduh_vv
#define  __vdsortpii16h_vv   __vdsortpiih_vv
#define  __vdsortpiiu16h_vv  __vdsortpiiuh_vv
#define  __vhadd16w1d_vd     __vhaddw1d_vd
#define  __vhadd32h1d_vd     __vhaddh1d_vd
#define  __vhadd64b1d_vd     __vhaddb1d_vd
#define  __vhadd8d1d_vd      __vhaddd1d_vd
#define  __vhaddeo16h2w_vd   __vhaddeoh2w_vd
#define  __vhaddeo8w2d_vv    __vhaddeow2d_vv
#define  __vhaddeo8w4d_vvv   __vhaddeow4d_vvv
#define  __vhaddu16w1d_vd    __vhadduw1d_vd
#define  __vhaddu32h1d_vd    __vhadduh1d_vd
#define  __vhaddu64b1d_vd    __vhaddub1d_vd
#define  __vhaddu8d1d_vd     __vhaddud1d_vd
#define  __vhaddueo16h2w_vd  __vhaddueoh2w_vd
#define  __vhaddueo8w2d_vv   __vhaddueow2d_vv
#define  __vhaddueo8w4d_vvv  __vhaddueow4d_vvv
#define  __vhxor16w1w_vr     __vhxorw1w_vr
#define  __vhxor32h1h_vr     __vhxorh1h_vr
#define  __vhxor64b1b_vr     __vhxorb1b_vr
#define  __vhxor8d1d_vd      __vhxord1d_vd
#define  __vsortd16sp_vv     __vsortdsp_vv
#define  __vsortd16w_vv      __vsortdw_vv
#define  __vsortdu16w_vv     __vsortduw_vv
#define  __vsorti16sp_vv     __vsortisp_vv
#define  __vsorti16w_vv      __vsortiw_vv
#define  __vsortiu16w_vv     __vsortiuw_vv
#define  __vsortpd16sp_vv    __vsortpdsp_vv
#define  __vsortpd16w_vv     __vsortpdw_vv
#define  __vsortpdu16w_vv    __vsortpduw_vv
#define  __vsortpi16sp_vv    __vsortpisp_vv
#define  __vsortpi16w_vv     __vsortpiw_vv
#define  __vsortpiu16w_vv    __vsortpiuw_vv
#if __C7X_VEC_SIZE_BITS__ == 512
#define  __vshfl4d_vv        __vdeal2d_vv
#endif

/******************************************************************************/
/* Direct Instruction Mapping                                                 */
/*                                                                            */
/* This file contains a list of intrinsics that map directly to instructions. */
/* Some of these intrinsics are particularly useful for operations that       */
/* require operand interleaving on input or operand deinterleaving on output. */
/* As such, they should only be used by advanced programmers.                 */
/*                                                                            */
/*  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -   */
/*                                                                            */
/* DIRECT INTRINSIC NAMING CONVENTION                                         */
/*                                                                            */
/* The first part of the intrinsic name is the mnemonic name.                 */
/*                                                                            */
/* The second part of the intrinsic name (the direct intrinsic "suffix")      */
/* represents the machine operand kinds for the arguments and return type.    */
/*                                                                            */
/* For example, a suffix of _ddr means that the first and second arguments    */
/* to the intrinsic are register operands that contain 64-bit scalar data     */
/* ('d') and the return value ('r') is a register operand that contains       */
/* 32-bit scalar data.                                                        */
/*                                                                            */
/*   Suffix    Machine operand kind                                           */
/*   ------    -------------------------------------------------------------  */
/*     v       Register operand that contains vector data                     */
/*     d       Register operand that contains 64-bit scalar data              */
/*     r       Register operand that contains 32-bit scalar data              */
/*     k       Immediate operand (i.e. a constant)                            */
/*     y       C unit control register operand                                */
/*     p       Predicate register operand                                     */
/*     z       Control predicate register operand                             */
/*                                                                            */
/*  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -   */
/*                                                                            */
/* There are a handful of complicated instructions listed here that do not    */
/* have a counterpart in c7x.h or cannot be access using a specific C idiom.  */
/* They can only be accessed using intrinsics listed in this file:            */
/*                                                                            */
/*  'EXTV'                                                                    */
/*  'EXTUV'                                                                   */
/*  'REPLACEV'                                                                */
/*  'VFIR8HD'                                                                 */
/*  'VFIR8HW'                                                                 */
/*  'VFIR8SUHD'                                                               */
/*  'VFIR8SUHW'                                                               */
/*  'VFIR8UHD'                                                                */
/*  'VFIR8UHW'                                                                */
/*  'VMATMPYHD'                                                               */
/*  'VMATMPYSP'                                                               */
/*  'VMATMPYSUHD'                                                             */
/*  'VMATMPYSUHW'                                                             */
/*  'VMATMPYUHD'                                                              */
/*  'VMATMPYUHW'                                                              */
/*  'VMATMPYUSHD'                                                             */
/*  'VSAD16OU16H16W'                                                          */
/*  'VSAD16OU8H16W'                                                           */
/*  'VSAD8OU16B32H'                                                           */
/*  'VSADM16OU16H16W'                                                         */
/*  'VSADM16OU8H16W'                                                          */
/*  'VSADM8OU16B32H'                                                          */
/*  'VDSAD16OU8H8W'                                                           */
/*  'VDSAD8OU16B16H'                                                          */
/*  'VDSADM16OU8H8W'                                                          */
/*  'VDSADM8OU16B16H'                                                         */
/*  'VCDOTPM2OPN16B32H'                                                       */
/*  'VCDOTPM2OPN1H32H'                                                        */
/*  'VCDOTPM2OPN8H16W'                                                        */
/*  'VCDOTPM2OPN8W16W'                                                        */
/*  'VCDOTPM32OPN16B32H'                                                      */
/*                                                                            */
/******************************************************************************/


/******************************************************************************/
/* __SE_REG and __SE_REG_PAIR Streaming Engine Operands                       */
/*                                                                            */
/* Some instructions can only take streaming engine operands (VFIR, VMATMPY). */
/* The intrinsics for these instructions take an immediate representing which */
/* streaming engine, as well as the advance option.                           */
/*----------------------------------------------------------------------------*/
/* Use the following for __SE_REG operands.                                   */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* typedef enum                                                               */
/* {                                                                          */
/*     __SE_REG_0     = 0,                                                    */
/*     __SE_REG_0_ADV = 1,                                                    */
/*     __SE_REG_1     = 2,                                                    */
/*     __SE_REG_1_ADV = 3                                                     */
/* } __SE_REG;                                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/* Use the following for __SE_REG_PAIR operands.                              */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* typedef enum                                                               */
/* {                                                                          */
/*     __SE_REG_PAIR_0     = 0,                                               */
/*     __SE_REG_PAIR_0_ADV = 1                                                */
/* } __SE_REG_PAIR;                                                           */
/*                                                                            */
/* All other values are invalid and will produce an error.                    */
/******************************************************************************/

/*----------------------------------------------------------------------------*/
/* ID: __vccmatmpyhw_se_vww                                                   */
/*----------------------------------------------------------------------------*/
/*

VCCMATMPYHW
#if __C7X_VEC_SIZE_BITS__ == 256
__vccmatmpyhw_se_vww(cshort8,  __SE_REG_PAIR, cint4&, cint4&);
#elif __C7X_VEC_SIZE_BITS__ == 512
__vccmatmpyhw_se_vww(cshort16, __SE_REG_PAIR, cint8&, cint8&);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __vccmatmpyr1hh_se_vwv                                                 */
/*----------------------------------------------------------------------------*/
/*

VCCMATMPYR1HH
#if __C7X_VEC_SIZE_BITS__ == 256
cshort8 = __vccmatmpyr1hh_se_vwv(cshort8, __SE_REG_PAIR);
#elif __C7X_VEC_SIZE_BITS__ == 512
cshort16 = __vccmatmpyr1hh_se_vwv(cshort16, __SE_REG_PAIR);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __vcmatmpyhw_se_vww                                                    */
/*----------------------------------------------------------------------------*/
/*

VCMATMPYHW
#if __C7X_VEC_SIZE_BITS__ == 256
__vcmatmpyhw_se_vww(cshort8,  __SE_REG_PAIR, cint4&, cint4&);
#elif __C7X_VEC_SIZE_BITS__ == 512
__vcmatmpyhw_se_vww(cshort16, __SE_REG_PAIR, cint8&, cint8&);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __vcmatmpyr1hh_se_vwv                                                  */
/*----------------------------------------------------------------------------*/
/*

VCMATMPYR1HH
#if __C7X_VEC_SIZE_BITS__ == 256
cshort8 = __vcmatmpyr1hh_se_vwv(cshort8, __SE_REG_PAIR);
#elif __C7X_VEC_SIZE_BITS__ == 512
cshort16 = __vcmatmpyr1hh_se_vwv(cshort16, __SE_REG_PAIR);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __vdotp4hw_se1_wwv                                                     */
/*----------------------------------------------------------------------------*/
/*

VDOTP4HW
#if __C7X_VEC_SIZE_BITS__ == 256
int8  = __vdotp4hw_se1_wwv(__SE_REG_PAIR, short16, short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __vdotp4hw_se1_wwv(__SE_REG_PAIR, short32, short32);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __vdotp4hw_se2_wwv                                                     */
/*----------------------------------------------------------------------------*/
/*

VDOTP4HW
#if __C7X_VEC_SIZE_BITS__ == 256
int8  = __vdotp4hw_se2_wwv(short16, short16, __SE_REG_PAIR);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __vdotp4hw_se2_wwv(short32, short32, __SE_REG_PAIR);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __vdotp4hw_se12_wwv                                                    */
/*----------------------------------------------------------------------------*/
/*

VDOTP4HW
#if __C7X_VEC_SIZE_BITS__ == 256
int8  = __vdotp4hw_se12_wwv(__SE_REG_PAIR, __SE_REG_PAIR);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __vdotp4hw_se12_wwv(__SE_REG_PAIR, __SE_REG_PAIR);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __vdotp4suhw_se1_wwv                                                   */
/*----------------------------------------------------------------------------*/
/*

VDOTP4SUHW
#if __C7X_VEC_SIZE_BITS__ == 256
int8  = __vdotp4suhw_se1_wwv(__SE_REG_PAIR, ushort16, ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __vdotp4suhw_se1_wwv(__SE_REG_PAIR, ushort32, ushort32);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __vdotp4suhw_se2_wwv                                                   */
/*----------------------------------------------------------------------------*/
/*

VDOTP4SUHW
#if __C7X_VEC_SIZE_BITS__ == 256
int8  = __vdotp4suhw_se2_wwv(short16, short16, __SE_REG_PAIR);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __vdotp4suhw_se2_wwv(short32, short32, __SE_REG_PAIR);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __vdotp4suhw_se12_wwv                                                  */
/*----------------------------------------------------------------------------*/
/*

VDOTP4SUHW
#if __C7X_VEC_SIZE_BITS__ == 256
int8  = __vdotp4suhw_se12_wwv(__SE_REG_PAIR, __SE_REG_PAIR);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __vdotp4suhw_se12_wwv(__SE_REG_PAIR, __SE_REG_PAIR);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __vfir4hw_vww                                                          */
/*----------------------------------------------------------------------------*/
/*

VFIR4HW
#if __C7X_VEC_SIZE_BITS__ == 256
__vfir4hw_vww(short16, __SE_REG_PAIR, int8&,  int8&);
#elif __C7X_VEC_SIZE_BITS__ == 512
__vfir4hw_vww(short32, __SE_REG_PAIR, int16&, int16&);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __vfir4suhw_vww                                                        */
/*----------------------------------------------------------------------------*/
/*

VFIR4SUHW
#if __C7X_VEC_SIZE_BITS__ == 256
__vfir4suhw_vww(short16, __SE_REG_PAIR, int8&,  int8&);
#elif __C7X_VEC_SIZE_BITS__ == 512
__vfir4suhw_vww(short32, __SE_REG_PAIR, int16&, int16&);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __vfir4uhw_vww                                                         */
/*----------------------------------------------------------------------------*/
/*

VFIR4UHW
#if __C7X_VEC_SIZE_BITS__ == 256
__vfir4uhw_vww(ushort16, __SE_REG_PAIR, uint8&,  uint8&);
#elif __C7X_VEC_SIZE_BITS__ == 512
__vfir4uhw_vww(ushort32, __SE_REG_PAIR, uint16&, uint16&);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __vfir8hd_wvw                                                          */
/*----------------------------------------------------------------------------*/
/*

VFIR8HD
#if   __C7X_VEC_SIZE_BITS__ == 256
__vfir8hd_wvw(short16, short16, __SE_REG, long4&, long4&);
#elif __C7X_VEC_SIZE_BITS__ == 512
__vfir8hd_wvw(short32, short32, __SE_REG, long8&, long8&);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __vfir8hw_wvv                                                          */
/*----------------------------------------------------------------------------*/
/*

VFIR8HW
#if   __C7X_VEC_SIZE_BITS__ == 256
int8 =  __vfir8hw_wvv(short16, short16, __SE_REG);
#elif __C7X_VEC_SIZE_BITS__ == 512
int16 = __vfir8hw_wvv(short32, short32, __SE_REG);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __vfir8suhd_wvw                                                        */
/*----------------------------------------------------------------------------*/
/*

VFIR8SUHD
#if   __C7X_VEC_SIZE_BITS__ == 256
__vfir8suhd_wvw(short16, short16, __SE_REG, long4&, long4&);
#elif __C7X_VEC_SIZE_BITS__ == 512
__vfir8suhd_wvw(short32, short32, __SE_REG, long8&, long8&);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __vfir8suhw_wvv                                                        */
/*----------------------------------------------------------------------------*/
/*

VFIR8SUHW
#if   __C7X_VEC_SIZE_BITS__ == 256
int8  = __vfir8suhw_wvv(short16, short16, __SE_REG);
#elif __C7X_VEC_SIZE_BITS__ == 512
int16 = __vfir8suhw_wvv(short32, short32, __SE_REG);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __vfir8uhd_wvw                                                         */
/*----------------------------------------------------------------------------*/
/*

VFIR8UHD
#if   __C7X_VEC_SIZE_BITS__ == 256
__vfir8uhd_wvw(ushort16, ushort16, __SE_REG, ulong4&, ulong4&);
#elif __C7X_VEC_SIZE_BITS__ == 512
__vfir8uhd_wvw(ushort32, ushort32, __SE_REG, ulong8&, ulong8&);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __vfir8uhw_wvv                                                         */
/*----------------------------------------------------------------------------*/
/*

VFIR8UHW
#if   __C7X_VEC_SIZE_BITS__ == 256
uint8  = __vfir8uhw_wvv(ushort16, ushort16, __SE_REG);
#elif __C7X_VEC_SIZE_BITS__ == 512
uint16 = __vfir8uhw_wvv(ushort32, ushort32, __SE_REG);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __vmatmpysp_se_vww                                                     */
/*----------------------------------------------------------------------------*/
/*

VMATMPYSP
#if __C7X_VEC_SIZE_BITS__ == 512
__vmatmpysp_se_vww(float16, __SE_REG_PAIR, float16&, float16&);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __vmatmpyhd_vvw                                                        */
/*----------------------------------------------------------------------------*/
/*

VMATMPYHD
#if __C7X_VEC_SIZE_BITS__ == 512
__vmatmpyhd_vvw(__SE_REG, __SE_REG, long8&, long8&);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __vmatmpyhw_vvv                                                        */
/*----------------------------------------------------------------------------*/
/*

VMATMPYHW
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __vmatmpyhw_vvv(__SE_REG, __SE_REG);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __vmatmpysuhd_vvw                                                      */
/*----------------------------------------------------------------------------*/
/*

VMATMPYSUHD
#if __C7X_VEC_SIZE_BITS__ == 512
__vmatmpysuhd_vvw(__SE_REG, __SE_REG, long8&, long8&);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __vmatmpysuhw_vvv                                                      */
/*----------------------------------------------------------------------------*/
/*

VMATMPYSUHW
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __vmatmpysuhw_vvv(__SE_REG, __SE_REG);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __vmatmpyuhd_vvw                                                       */
/*----------------------------------------------------------------------------*/
/*

VMATMPYUHD
#if __C7X_VEC_SIZE_BITS__ == 512
__vmatmpyuhd_vvw(__SE_REG, __SE_REG, ulong8&, ulong8&);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __vmatmpyuhw_vvv                                                       */
/*----------------------------------------------------------------------------*/
/*

VMATMPYUHW
#if __C7X_VEC_SIZE_BITS__ == 512
uint16 = __vmatmpyuhw_vvv(__SE_REG, __SE_REG);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __vmatmpyushd_vvw                                                      */
/*----------------------------------------------------------------------------*/
/*

VMATMPYUSHD
#if __C7X_VEC_SIZE_BITS__ == 512
__vmatmpyushd_vvw(__SE_REG, __SE_REG, long8&, long8&);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __vmatmpyushw_vvv                                                      */
/*----------------------------------------------------------------------------*/
/*

VMATMPYUSHW
#if __C7X_VEC_SIZE_BITS__ == 512
int16 = __vmatmpyushw_vvv(__SE_REG, __SE_REG);
#endif

*/

/* AUTOGEN MARKER */
/*----------------------------------------------------------------------------*/
/* ID: __addd_ddd                                                             */
/*----------------------------------------------------------------------------*/
/*
ADDD
*/
long __OVBIF __addd_ddd(long, long);
__ulong __OVBIF __addd_ddd(__ulong, __ulong);

/*----------------------------------------------------------------------------*/
/* ID: __addd_dkd                                                             */
/*----------------------------------------------------------------------------*/
/*
ADDD
*/
long __OVBIF __addd_dkd(long, int __CST(-2147483648, 2147483647));
__ulong __OVBIF __addd_dkd(__ulong, __uint __CST(0, 2147483647));

/*----------------------------------------------------------------------------*/
/* ID: __adddp_ddd                                                            */
/*----------------------------------------------------------------------------*/
/*
ADDDP
*/
double __BIF __adddp_ddd(double, double);

/*----------------------------------------------------------------------------*/
/* ID: __addsp_rrr                                                            */
/*----------------------------------------------------------------------------*/
/*
ADDSP
*/
float __BIF __addsp_rrr(float, float);

/*----------------------------------------------------------------------------*/
/* ID: __addw_rkr                                                             */
/*----------------------------------------------------------------------------*/
/*
ADDW
*/
int __OVBIF __addw_rkr(int, int __CST(-2147483648, 2147483647));
__uint __OVBIF __addw_rkr(__uint, __uint __CST(0, 4294967295));

/*----------------------------------------------------------------------------*/
/* ID: __addw_rrr                                                             */
/*----------------------------------------------------------------------------*/
/*
ADDW
*/
int __OVBIF __addw_rrr(int, int);
__uint __OVBIF __addw_rrr(__uint, __uint);

/*----------------------------------------------------------------------------*/
/* ID: __and_ppp                                                              */
/*----------------------------------------------------------------------------*/
/*
AND
*/
__vpred __BIF __and_ppp(__vpred, __vpred);

/*----------------------------------------------------------------------------*/
/* ID: __andd_ddd                                                             */
/*----------------------------------------------------------------------------*/
/*
ANDD
*/
__char8 __OVBIF __andd_ddd(__char8, __char8);
__uchar8 __OVBIF __andd_ddd(__uchar8, __uchar8);
__short4 __OVBIF __andd_ddd(__short4, __short4);
__ushort4 __OVBIF __andd_ddd(__ushort4, __ushort4);
__int2 __OVBIF __andd_ddd(__int2, __int2);
__uint2 __OVBIF __andd_ddd(__uint2, __uint2);
long __OVBIF __andd_ddd(long, long);
__ulong __OVBIF __andd_ddd(__ulong, __ulong);

/*----------------------------------------------------------------------------*/
/* ID: __andd_dkd                                                             */
/*----------------------------------------------------------------------------*/
/*
ANDD
*/
long __OVBIF __andd_dkd(long, int __CST(-2147483648, 2147483647));
__ulong __OVBIF __andd_dkd(__ulong, __uint __CST(0, 2147483647));

/*----------------------------------------------------------------------------*/
/* ID: __andn_ppp                                                             */
/*----------------------------------------------------------------------------*/
/*
ANDN
*/
__vpred __BIF __andn_ppp(__vpred, __vpred);

/*----------------------------------------------------------------------------*/
/* ID: __andnd_ddd                                                            */
/*----------------------------------------------------------------------------*/
/*
ANDND
*/
__char8 __OVBIF __andnd_ddd(__char8, __char8);
__uchar8 __OVBIF __andnd_ddd(__uchar8, __uchar8);
__short4 __OVBIF __andnd_ddd(__short4, __short4);
__ushort4 __OVBIF __andnd_ddd(__ushort4, __ushort4);
__int2 __OVBIF __andnd_ddd(__int2, __int2);
__uint2 __OVBIF __andnd_ddd(__uint2, __uint2);
long __OVBIF __andnd_ddd(long, long);
__ulong __OVBIF __andnd_ddd(__ulong, __ulong);

/*----------------------------------------------------------------------------*/
/* ID: __andnd_dkd                                                            */
/*----------------------------------------------------------------------------*/
/*
ANDND
*/
long __OVBIF __andnd_dkd(long, int __CST(-2147483648, 2147483647));
__ulong __OVBIF __andnd_dkd(__ulong, __uint __CST(0, 2147483647));

/*----------------------------------------------------------------------------*/
/* ID: __andnw_rkr                                                            */
/*----------------------------------------------------------------------------*/
/*
ANDNW
*/
__char4 __OVBIF __andnw_rkr(__char4, __char4 __CST(-128, 127));
__uchar4 __OVBIF __andnw_rkr(__uchar4, __uchar4 __CST(0, 255));
__short2 __OVBIF __andnw_rkr(__short2, __short2 __CST(-32768, 32767));
__ushort2 __OVBIF __andnw_rkr(__ushort2, __ushort2 __CST(0, 65535));
int __OVBIF __andnw_rkr(int, int __CST(-2147483648, 2147483647));
__uint __OVBIF __andnw_rkr(__uint, __uint __CST(0, 4294967295));

/*----------------------------------------------------------------------------*/
/* ID: __andnw_rrr                                                            */
/*----------------------------------------------------------------------------*/
/*
ANDNW
*/
__char4 __OVBIF __andnw_rrr(__char4, __char4);
__uchar4 __OVBIF __andnw_rrr(__uchar4, __uchar4);
__short2 __OVBIF __andnw_rrr(__short2, __short2);
__ushort2 __OVBIF __andnw_rrr(__ushort2, __ushort2);
int __OVBIF __andnw_rrr(int, int);
__uint __OVBIF __andnw_rrr(__uint, __uint);

/*----------------------------------------------------------------------------*/
/* ID: __andw_rkr                                                             */
/*----------------------------------------------------------------------------*/
/*
ANDW
*/
__char4 __OVBIF __andw_rkr(__char4, __char4 __CST(-128, 127));
__uchar4 __OVBIF __andw_rkr(__uchar4, __uchar4 __CST(0, 255));
__short2 __OVBIF __andw_rkr(__short2, __short2 __CST(-32768, 32767));
__ushort2 __OVBIF __andw_rkr(__ushort2, __ushort2 __CST(0, 65535));
int __OVBIF __andw_rkr(int, int __CST(-2147483648, 2147483647));
__uint __OVBIF __andw_rkr(__uint, __uint __CST(0, 4294967295));

/*----------------------------------------------------------------------------*/
/* ID: __andw_rrr                                                             */
/*----------------------------------------------------------------------------*/
/*
ANDW
*/
__char4 __OVBIF __andw_rrr(__char4, __char4);
__uchar4 __OVBIF __andw_rrr(__uchar4, __uchar4);
__short2 __OVBIF __andw_rrr(__short2, __short2);
__ushort2 __OVBIF __andw_rrr(__ushort2, __ushort2);
int __OVBIF __andw_rrr(int, int);
__uint __OVBIF __andw_rrr(__uint, __uint);

/*----------------------------------------------------------------------------*/
/* ID: __bitr_pp                                                              */
/*----------------------------------------------------------------------------*/
/*
BITR
*/
__vpred __BIF __bitr_pp(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __c6dcmpeqb_ddr                                                        */
/*----------------------------------------------------------------------------*/
/*
C6DCMPEQB
*/
__uchar __BIF __c6dcmpeqb_ddr(__char8, __char8);

/*----------------------------------------------------------------------------*/
/* ID: __c6dcmpeqh_ddr                                                        */
/*----------------------------------------------------------------------------*/
/*
C6DCMPEQH
*/
__uchar __BIF __c6dcmpeqh_ddr(__short4, __short4);

/*----------------------------------------------------------------------------*/
/* ID: __c6dcmpgth_ddr                                                        */
/*----------------------------------------------------------------------------*/
/*
C6DCMPGTH
*/
__uchar __BIF __c6dcmpgth_ddr(__short4, __short4);

/*----------------------------------------------------------------------------*/
/* ID: __c6dcmpgtub_ddr                                                       */
/*----------------------------------------------------------------------------*/
/*
C6DCMPGTUB
*/
__uchar __BIF __c6dcmpgtub_ddr(__uchar8, __uchar8);

/*----------------------------------------------------------------------------*/
/* ID: __c6ddotp2hhw_drd                                                      */
/*----------------------------------------------------------------------------*/
/*
C6DDOTP2HHW
*/
__int2 __BIF __c6ddotp2hhw_drd(__short4, __short2);

/*----------------------------------------------------------------------------*/
/* ID: __c6ddotp2hrhh_drr                                                     */
/*----------------------------------------------------------------------------*/
/*
C6DDOTP2HRHH
*/
__short2 __BIF __c6ddotp2hrhh_drr(__short4, __short2);

/*----------------------------------------------------------------------------*/
/* ID: __c6ddotp2lhw_drd                                                      */
/*----------------------------------------------------------------------------*/
/*
C6DDOTP2LHW
*/
__int2 __BIF __c6ddotp2lhw_drd(__short4, __short2);

/*----------------------------------------------------------------------------*/
/* ID: __c6ddotp2lrhh_drr                                                     */
/*----------------------------------------------------------------------------*/
/*
C6DDOTP2LRHH
*/
__short2 __BIF __c6ddotp2lrhh_drr(__short4, __short2);

/*----------------------------------------------------------------------------*/
/* ID: __c6dmpyhw_vvw                                                         */
/*----------------------------------------------------------------------------*/
/*

C6DMPYHW
#if __C7X_VEC_SIZE_BITS__ == 256
void __c6dmpyhw_vvw(short16, short16, int8&, int8&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
void __c6dmpyhw_vvw(short32, short32, int16&, int16&);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __c6dmpysubh_vvw                                                       */
/*----------------------------------------------------------------------------*/
/*

C6DMPYSUBH
#if __C7X_VEC_SIZE_BITS__ == 256
void __c6dmpysubh_vvw(char32, uchar32, short16&, short16&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
void __c6dmpysubh_vvw(char64, uchar64, short32&, short32&);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __c6dmpyubh_vvw                                                        */
/*----------------------------------------------------------------------------*/
/*

C6DMPYUBH
#if __C7X_VEC_SIZE_BITS__ == 256
void __c6dmpyubh_vvw(uchar32, uchar32, ushort16&, ushort16&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
void __c6dmpyubh_vvw(uchar64, uchar64, ushort32&, ushort32&);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __c6dmpyuhw_vvw                                                        */
/*----------------------------------------------------------------------------*/
/*

C6DMPYUHW
#if __C7X_VEC_SIZE_BITS__ == 256
void __c6dmpyuhw_vvw(ushort16, ushort16, uint8&, uint8&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
void __c6dmpyuhw_vvw(ushort32, ushort32, uint16&, uint16&);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __c6dotp2rsuhw_rrr                                                     */
/*----------------------------------------------------------------------------*/
/*
C6DOTP2RSUHW
*/
int __BIF __c6dotp2rsuhw_rrr(__short2, __ushort2);

/*----------------------------------------------------------------------------*/
/* ID: __c6dotpn2hw_rrr                                                       */
/*----------------------------------------------------------------------------*/
/*
C6DOTPN2HW
*/
int __BIF __c6dotpn2hw_rrr(__short2, __short2);

/*----------------------------------------------------------------------------*/
/* ID: __c6dotpn2rsuhh_rrr                                                    */
/*----------------------------------------------------------------------------*/
/*
C6DOTPN2RSUHH
*/
int __BIF __c6dotpn2rsuhh_rrr(__short2, __ushort2);

/*----------------------------------------------------------------------------*/
/* ID: __c6dsmpyhw_vvw                                                        */
/*----------------------------------------------------------------------------*/
/*

C6DSMPYHW
#if __C7X_VEC_SIZE_BITS__ == 256
void __c6dsmpyhw_vvw(short16, short16, int8&, int8&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
void __c6dsmpyhw_vvw(short32, short32, int16&, int16&);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __c6dspacku4_ddd                                                       */
/*----------------------------------------------------------------------------*/
/*
C6DSPACKU4
*/
__uchar8 __BIF __c6dspacku4_ddd(__short4, __short4);

/*----------------------------------------------------------------------------*/
/* ID: __c6mpy2ir_rrd                                                         */
/*----------------------------------------------------------------------------*/
/*
C6MPY2IR
*/
__int2 __BIF __c6mpy2ir_rrd(__short2, int);

/*----------------------------------------------------------------------------*/
/* ID: __c6mpyhir_rrr                                                         */
/*----------------------------------------------------------------------------*/
/*
C6MPYHIR
*/
int __BIF __c6mpyhir_rrr(__short2, int);

/*----------------------------------------------------------------------------*/
/* ID: __c6mpylir_rrr                                                         */
/*----------------------------------------------------------------------------*/
/*
C6MPYLIR
*/
int __BIF __c6mpylir_rrr(__short2, int);

/*----------------------------------------------------------------------------*/
/* ID: __clr_rrr                                                              */
/*----------------------------------------------------------------------------*/
/*
CLR
*/
__uint __BIF __clr_rrr(__uint, __uint);

/*----------------------------------------------------------------------------*/
/* ID: __cmpeqd_ddr                                                           */
/*----------------------------------------------------------------------------*/
/*
CMPEQD
*/
int __BIF __cmpeqd_ddr(long, long);

/*----------------------------------------------------------------------------*/
/* ID: __cmpeqd_dkr                                                           */
/*----------------------------------------------------------------------------*/
/*
CMPEQD
*/
int __BIF __cmpeqd_dkr(long, int __CST(-2147483648, 2147483647));

/*----------------------------------------------------------------------------*/
/* ID: __cmpeqdp_ddr                                                          */
/*----------------------------------------------------------------------------*/
/*
CMPEQDP
*/
int __BIF __cmpeqdp_ddr(double, double);

/*----------------------------------------------------------------------------*/
/* ID: __cmpeqsp_rrr                                                          */
/*----------------------------------------------------------------------------*/
/*
CMPEQSP
*/
int __BIF __cmpeqsp_rrr(float, float);

/*----------------------------------------------------------------------------*/
/* ID: __cmpeqw_rkr                                                           */
/*----------------------------------------------------------------------------*/
/*
CMPEQW
*/
int __BIF __cmpeqw_rkr(int, int __CST(-2147483648, 2147483647));

/*----------------------------------------------------------------------------*/
/* ID: __cmpeqw_rrr                                                           */
/*----------------------------------------------------------------------------*/
/*
CMPEQW
*/
int __BIF __cmpeqw_rrr(int, int);

/*----------------------------------------------------------------------------*/
/* ID: __cmpged_ddr                                                           */
/*----------------------------------------------------------------------------*/
/*
CMPGED
*/
int __BIF __cmpged_ddr(long, long);

/*----------------------------------------------------------------------------*/
/* ID: __cmpged_dkr                                                           */
/*----------------------------------------------------------------------------*/
/*
CMPGED
*/
int __BIF __cmpged_dkr(long, int __CST(-2147483648, 2147483647));

/*----------------------------------------------------------------------------*/
/* ID: __cmpgeud_ddr                                                          */
/*----------------------------------------------------------------------------*/
/*
CMPGEUD
*/
int __BIF __cmpgeud_ddr(__ulong, __ulong);

/*----------------------------------------------------------------------------*/
/* ID: __cmpgeud_dkr                                                          */
/*----------------------------------------------------------------------------*/
/*
CMPGEUD
*/
int __BIF __cmpgeud_dkr(__ulong, __uint __CST(0, 4294967295));

/*----------------------------------------------------------------------------*/
/* ID: __cmpgeuw_rkr                                                          */
/*----------------------------------------------------------------------------*/
/*
CMPGEUW
*/
int __BIF __cmpgeuw_rkr(__uint, __uint __CST(0, 4294967295));

/*----------------------------------------------------------------------------*/
/* ID: __cmpgeuw_rrr                                                          */
/*----------------------------------------------------------------------------*/
/*
CMPGEUW
*/
int __BIF __cmpgeuw_rrr(__uint, __uint);

/*----------------------------------------------------------------------------*/
/* ID: __cmpgew_rkr                                                           */
/*----------------------------------------------------------------------------*/
/*
CMPGEW
*/
int __BIF __cmpgew_rkr(int, int __CST(-2147483648, 2147483647));

/*----------------------------------------------------------------------------*/
/* ID: __cmpgew_rrr                                                           */
/*----------------------------------------------------------------------------*/
/*
CMPGEW
*/
int __BIF __cmpgew_rrr(int, int);

/*----------------------------------------------------------------------------*/
/* ID: __cmpgtd_ddr                                                           */
/*----------------------------------------------------------------------------*/
/*
CMPGTD
*/
int __BIF __cmpgtd_ddr(long, long);

/*----------------------------------------------------------------------------*/
/* ID: __cmpgtd_dkr                                                           */
/*----------------------------------------------------------------------------*/
/*
CMPGTD
*/
int __BIF __cmpgtd_dkr(long, int __CST(-2147483648, 2147483647));

/*----------------------------------------------------------------------------*/
/* ID: __cmpgtud_ddr                                                          */
/*----------------------------------------------------------------------------*/
/*
CMPGTUD
*/
int __BIF __cmpgtud_ddr(__ulong, __ulong);

/*----------------------------------------------------------------------------*/
/* ID: __cmpgtud_dkr                                                          */
/*----------------------------------------------------------------------------*/
/*
CMPGTUD
*/
int __BIF __cmpgtud_dkr(__ulong, __uint __CST(0, 4294967295));

/*----------------------------------------------------------------------------*/
/* ID: __cmpgtuw_rkr                                                          */
/*----------------------------------------------------------------------------*/
/*
CMPGTUW
*/
int __BIF __cmpgtuw_rkr(__uint, __uint __CST(0, 4294967295));

/*----------------------------------------------------------------------------*/
/* ID: __cmpgtuw_rrr                                                          */
/*----------------------------------------------------------------------------*/
/*
CMPGTUW
*/
int __BIF __cmpgtuw_rrr(__uint, __uint);

/*----------------------------------------------------------------------------*/
/* ID: __cmpgtw_rkr                                                           */
/*----------------------------------------------------------------------------*/
/*
CMPGTW
*/
int __BIF __cmpgtw_rkr(int, int __CST(-2147483648, 2147483647));

/*----------------------------------------------------------------------------*/
/* ID: __cmpgtw_rrr                                                           */
/*----------------------------------------------------------------------------*/
/*
CMPGTW
*/
int __BIF __cmpgtw_rrr(int, int);

/*----------------------------------------------------------------------------*/
/* ID: __cmpledp_ddr                                                          */
/*----------------------------------------------------------------------------*/
/*
CMPLEDP
*/
int __BIF __cmpledp_ddr(double, double);

/*----------------------------------------------------------------------------*/
/* ID: __cmplesp_rrr                                                          */
/*----------------------------------------------------------------------------*/
/*
CMPLESP
*/
int __BIF __cmplesp_rrr(float, float);

/*----------------------------------------------------------------------------*/
/* ID: __cmpltdp_ddr                                                          */
/*----------------------------------------------------------------------------*/
/*
CMPLTDP
*/
int __BIF __cmpltdp_ddr(double, double);

/*----------------------------------------------------------------------------*/
/* ID: __cmpltsp_rrr                                                          */
/*----------------------------------------------------------------------------*/
/*
CMPLTSP
*/
int __BIF __cmpltsp_rrr(float, float);

/*----------------------------------------------------------------------------*/
/* ID: __compressl_pp                                                         */
/*----------------------------------------------------------------------------*/
/*
COMPRESSL
*/
__vpred __BIF __compressl_pp(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __compressr_pp                                                         */
/*----------------------------------------------------------------------------*/
/*
COMPRESSR
*/
__vpred __BIF __compressr_pp(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __decimateb_ppp                                                        */
/*----------------------------------------------------------------------------*/
/*
DECIMATEB
*/
__vpred __BIF __decimateb_ppp(__vpred, __vpred);

/*----------------------------------------------------------------------------*/
/* ID: __decimated_ppp                                                        */
/*----------------------------------------------------------------------------*/
/*
DECIMATED
*/
__vpred __BIF __decimated_ppp(__vpred, __vpred);

/*----------------------------------------------------------------------------*/
/* ID: __decimateh_ppp                                                        */
/*----------------------------------------------------------------------------*/
/*
DECIMATEH
*/
__vpred __BIF __decimateh_ppp(__vpred, __vpred);

/*----------------------------------------------------------------------------*/
/* ID: __decimatew_ppp                                                        */
/*----------------------------------------------------------------------------*/
/*
DECIMATEW
*/
__vpred __BIF __decimatew_ppp(__vpred, __vpred);

/*----------------------------------------------------------------------------*/
/* ID: __divdw_drd                                                            */
/*----------------------------------------------------------------------------*/
/*
DIVDW
*/
long __BIF __divdw_drd(long, int);

/*----------------------------------------------------------------------------*/
/* ID: __divudw_drd                                                           */
/*----------------------------------------------------------------------------*/
/*
DIVUDW
*/
__ulong __BIF __divudw_drd(__ulong, __uint);

/*----------------------------------------------------------------------------*/
/* ID: __divuw_rrr                                                            */
/*----------------------------------------------------------------------------*/
/*
DIVUW
*/
__uint __BIF __divuw_rrr(__uint, __uint);

/*----------------------------------------------------------------------------*/
/* ID: __divw_rrr                                                             */
/*----------------------------------------------------------------------------*/
/*
DIVW
*/
int __BIF __divw_rrr(int, int);

/*----------------------------------------------------------------------------*/
/* ID: __ext_dkkd                                                             */
/*----------------------------------------------------------------------------*/
/*
EXT
*/
long __OVBIF __ext_dkkd(__char8, __uchar __CST(0, 63), __uchar __CST(0, 63));
long __OVBIF __ext_dkkd(__short4, __uchar __CST(0, 63), __uchar __CST(0, 63));
long __OVBIF __ext_dkkd(__int2, __uchar __CST(0, 63), __uchar __CST(0, 63));
long __OVBIF __ext_dkkd(long, __uchar __CST(0, 63), __uchar __CST(0, 63));

/*----------------------------------------------------------------------------*/
/* ID: __extu_dkkd                                                            */
/*----------------------------------------------------------------------------*/
/*
EXTU
*/
__ulong __OVBIF __extu_dkkd(__uchar8, __uchar __CST(0, 63), __uchar __CST(0, 63));
__ulong __OVBIF __extu_dkkd(__ushort4, __uchar __CST(0, 63), __uchar __CST(0, 63));
__ulong __OVBIF __extu_dkkd(__uint2, __uchar __CST(0, 63), __uchar __CST(0, 63));
__ulong __OVBIF __extu_dkkd(__ulong, __uchar __CST(0, 63), __uchar __CST(0, 63));

/*----------------------------------------------------------------------------*/
/* ID: __extuv_vkkkd                                                          */
/*----------------------------------------------------------------------------*/
/*
EXTUV
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong __BIF __extuv_vkkkd(__ulong8, __uchar __CST(0, 7), __uchar __CST(0, 63), __uchar __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong __BIF __extuv_vkkkd(__ulong4, __uchar __CST(0, 7), __uchar __CST(0, 63), __uchar __CST(0, 63));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __extv_vkkkd                                                           */
/*----------------------------------------------------------------------------*/
/*
EXTV
*/
#if __C7X_VEC_SIZE_BITS__ == 512
long __BIF __extv_vkkkd(__long8, __uchar __CST(0, 7), __uchar __CST(0, 63), __uchar __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
long __BIF __extv_vkkkd(__long4, __uchar __CST(0, 7), __uchar __CST(0, 63), __uchar __CST(0, 63));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __landd_ddr                                                            */
/*----------------------------------------------------------------------------*/
/*
LANDD
*/
int __BIF __landd_ddr(long, long);

/*----------------------------------------------------------------------------*/
/* ID: __landnd_ddr                                                           */
/*----------------------------------------------------------------------------*/
/*
LANDND
*/
int __BIF __landnd_ddr(long, long);

/*----------------------------------------------------------------------------*/
/* ID: __lord_ddr                                                             */
/*----------------------------------------------------------------------------*/
/*
LORD
*/
int __BIF __lord_ddr(long, long);

/*----------------------------------------------------------------------------*/
/* ID: __maskb_kp                                                             */
/*----------------------------------------------------------------------------*/
/*
MASKB
*/
__vpred __BIF __maskb_kp(__uchar __CST(0, 63));

/*----------------------------------------------------------------------------*/
/* ID: __maskb_rp                                                             */
/*----------------------------------------------------------------------------*/
/*
MASKB
*/
__vpred __BIF __maskb_rp(__uint);

/*----------------------------------------------------------------------------*/
/* ID: __maskd_kp                                                             */
/*----------------------------------------------------------------------------*/
/*
MASKD
*/
__vpred __BIF __maskd_kp(__uchar __CST(0, 63));

/*----------------------------------------------------------------------------*/
/* ID: __maskd_rp                                                             */
/*----------------------------------------------------------------------------*/
/*
MASKD
*/
__vpred __BIF __maskd_rp(__uint);

/*----------------------------------------------------------------------------*/
/* ID: __maskh_kp                                                             */
/*----------------------------------------------------------------------------*/
/*
MASKH
*/
__vpred __BIF __maskh_kp(__uchar __CST(0, 63));

/*----------------------------------------------------------------------------*/
/* ID: __maskh_rp                                                             */
/*----------------------------------------------------------------------------*/
/*
MASKH
*/
__vpred __BIF __maskh_rp(__uint);

/*----------------------------------------------------------------------------*/
/* ID: __maskw_kp                                                             */
/*----------------------------------------------------------------------------*/
/*
MASKW
*/
__vpred __BIF __maskw_kp(__uchar __CST(0, 63));

/*----------------------------------------------------------------------------*/
/* ID: __maskw_rp                                                             */
/*----------------------------------------------------------------------------*/
/*
MASKW
*/
__vpred __BIF __maskw_rp(__uint);

/*----------------------------------------------------------------------------*/
/* ID: __moddw_drd                                                            */
/*----------------------------------------------------------------------------*/
/*
MODDW
*/
long __BIF __moddw_drd(long, int);

/*----------------------------------------------------------------------------*/
/* ID: __modudw_drd                                                           */
/*----------------------------------------------------------------------------*/
/*
MODUDW
*/
__ulong __BIF __modudw_drd(__ulong, __uint);

/*----------------------------------------------------------------------------*/
/* ID: __moduw_rrr                                                            */
/*----------------------------------------------------------------------------*/
/*
MODUW
*/
__uint __BIF __moduw_rrr(__uint, __uint);

/*----------------------------------------------------------------------------*/
/* ID: __modw_rrr                                                             */
/*----------------------------------------------------------------------------*/
/*
MODW
*/
int __BIF __modw_rrr(int, int);

/*----------------------------------------------------------------------------*/
/* ID: __mpydd_ddd                                                            */
/*----------------------------------------------------------------------------*/
/*
MPYDD
*/
long __OVBIF __mpydd_ddd(long, long);
__ulong __OVBIF __mpydd_ddd(__ulong, __ulong);

/*----------------------------------------------------------------------------*/
/* ID: __mpydp_ddd                                                            */
/*----------------------------------------------------------------------------*/
/*
MPYDP
*/
double __BIF __mpydp_ddd(double, double);

/*----------------------------------------------------------------------------*/
/* ID: __mpyhw_rrr                                                            */
/*----------------------------------------------------------------------------*/
/*
MPYHW
*/
int __BIF __mpyhw_rrr(short, short);

/*----------------------------------------------------------------------------*/
/* ID: __mpysp_rrr                                                            */
/*----------------------------------------------------------------------------*/
/*
MPYSP
*/
float __BIF __mpysp_rrr(float, float);

/*----------------------------------------------------------------------------*/
/* ID: __mpysuhw_rrr                                                          */
/*----------------------------------------------------------------------------*/
/*
MPYSUHW
*/
int __BIF __mpysuhw_rrr(short, __ushort);

/*----------------------------------------------------------------------------*/
/* ID: __mpyuhw_rrr                                                           */
/*----------------------------------------------------------------------------*/
/*
MPYUHW
*/
__uint __BIF __mpyuhw_rrr(__ushort, __ushort);

/*----------------------------------------------------------------------------*/
/* ID: __mpyww_rrr                                                            */
/*----------------------------------------------------------------------------*/
/*
MPYWW
*/
int __OVBIF __mpyww_rrr(int, int);
__uint __OVBIF __mpyww_rrr(__uint, __uint);

/*----------------------------------------------------------------------------*/
/* ID: __nand_ppp                                                             */
/*----------------------------------------------------------------------------*/
/*
NAND
*/
__vpred __BIF __nand_ppp(__vpred, __vpred);

/*----------------------------------------------------------------------------*/
/* ID: __nandd_ddd                                                            */
/*----------------------------------------------------------------------------*/
/*
NANDD
*/
__char8 __OVBIF __nandd_ddd(__char8, __char8);
__uchar8 __OVBIF __nandd_ddd(__uchar8, __uchar8);
__short4 __OVBIF __nandd_ddd(__short4, __short4);
__ushort4 __OVBIF __nandd_ddd(__ushort4, __ushort4);
__int2 __OVBIF __nandd_ddd(__int2, __int2);
__uint2 __OVBIF __nandd_ddd(__uint2, __uint2);
long __OVBIF __nandd_ddd(long, long);
__ulong __OVBIF __nandd_ddd(__ulong, __ulong);

/*----------------------------------------------------------------------------*/
/* ID: __nandd_dkd                                                            */
/*----------------------------------------------------------------------------*/
/*
NANDD
*/
long __OVBIF __nandd_dkd(long, int __CST(-2147483648, 2147483647));
__ulong __OVBIF __nandd_dkd(__ulong, __uint __CST(0, 2147483647));

/*----------------------------------------------------------------------------*/
/* ID: __nandw_rrr                                                            */
/*----------------------------------------------------------------------------*/
/*
NANDW
*/
__char4 __OVBIF __nandw_rrr(__char4, __char4);
__uchar4 __OVBIF __nandw_rrr(__uchar4, __uchar4);
__short2 __OVBIF __nandw_rrr(__short2, __short2);
__ushort2 __OVBIF __nandw_rrr(__ushort2, __ushort2);
int __OVBIF __nandw_rrr(int, int);
__uint __OVBIF __nandw_rrr(__uint, __uint);

/*----------------------------------------------------------------------------*/
/* ID: __nor_ppp                                                              */
/*----------------------------------------------------------------------------*/
/*
NOR
*/
__vpred __BIF __nor_ppp(__vpred, __vpred);

/*----------------------------------------------------------------------------*/
/* ID: __nord_ddd                                                             */
/*----------------------------------------------------------------------------*/
/*
NORD
*/
__char8 __OVBIF __nord_ddd(__char8, __char8);
__uchar8 __OVBIF __nord_ddd(__uchar8, __uchar8);
__short4 __OVBIF __nord_ddd(__short4, __short4);
__ushort4 __OVBIF __nord_ddd(__ushort4, __ushort4);
__int2 __OVBIF __nord_ddd(__int2, __int2);
__uint2 __OVBIF __nord_ddd(__uint2, __uint2);
long __OVBIF __nord_ddd(long, long);
__ulong __OVBIF __nord_ddd(__ulong, __ulong);

/*----------------------------------------------------------------------------*/
/* ID: __nord_dkd                                                             */
/*----------------------------------------------------------------------------*/
/*
NORD
*/
long __OVBIF __nord_dkd(long, int __CST(-2147483648, 2147483647));
__ulong __OVBIF __nord_dkd(__ulong, __uint __CST(0, 2147483647));

/*----------------------------------------------------------------------------*/
/* ID: __norw_rrr                                                             */
/*----------------------------------------------------------------------------*/
/*
NORW
*/
__char4 __OVBIF __norw_rrr(__char4, __char4);
__uchar4 __OVBIF __norw_rrr(__uchar4, __uchar4);
__short2 __OVBIF __norw_rrr(__short2, __short2);
__ushort2 __OVBIF __norw_rrr(__ushort2, __ushort2);
int __OVBIF __norw_rrr(int, int);
__uint __OVBIF __norw_rrr(__uint, __uint);

/*----------------------------------------------------------------------------*/
/* ID: __not_pp                                                               */
/*----------------------------------------------------------------------------*/
/*
NOT
*/
__vpred __BIF __not_pp(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __or_ppp                                                               */
/*----------------------------------------------------------------------------*/
/*
OR
*/
__vpred __BIF __or_ppp(__vpred, __vpred);

/*----------------------------------------------------------------------------*/
/* ID: __ord_ddd                                                              */
/*----------------------------------------------------------------------------*/
/*
ORD
*/
__char8 __OVBIF __ord_ddd(__char8, __char8);
__uchar8 __OVBIF __ord_ddd(__uchar8, __uchar8);
__short4 __OVBIF __ord_ddd(__short4, __short4);
__ushort4 __OVBIF __ord_ddd(__ushort4, __ushort4);
__int2 __OVBIF __ord_ddd(__int2, __int2);
__uint2 __OVBIF __ord_ddd(__uint2, __uint2);
long __OVBIF __ord_ddd(long, long);
__ulong __OVBIF __ord_ddd(__ulong, __ulong);

/*----------------------------------------------------------------------------*/
/* ID: __ord_dkd                                                              */
/*----------------------------------------------------------------------------*/
/*
ORD
*/
long __OVBIF __ord_dkd(long, int __CST(-2147483648, 2147483647));
__ulong __OVBIF __ord_dkd(__ulong, __uint __CST(0, 2147483647));

/*----------------------------------------------------------------------------*/
/* ID: __orn_ppp                                                              */
/*----------------------------------------------------------------------------*/
/*
ORN
*/
__vpred __BIF __orn_ppp(__vpred, __vpred);

/*----------------------------------------------------------------------------*/
/* ID: __ornd_ddd                                                             */
/*----------------------------------------------------------------------------*/
/*
ORND
*/
__char8 __OVBIF __ornd_ddd(__char8, __char8);
__uchar8 __OVBIF __ornd_ddd(__uchar8, __uchar8);
__short4 __OVBIF __ornd_ddd(__short4, __short4);
__ushort4 __OVBIF __ornd_ddd(__ushort4, __ushort4);
__int2 __OVBIF __ornd_ddd(__int2, __int2);
__uint2 __OVBIF __ornd_ddd(__uint2, __uint2);
long __OVBIF __ornd_ddd(long, long);
__ulong __OVBIF __ornd_ddd(__ulong, __ulong);

/*----------------------------------------------------------------------------*/
/* ID: __ornd_dkd                                                             */
/*----------------------------------------------------------------------------*/
/*
ORND
*/
long __OVBIF __ornd_dkd(long, int __CST(-2147483648, 2147483647));
__ulong __OVBIF __ornd_dkd(__ulong, __uint __CST(0, 2147483647));

/*----------------------------------------------------------------------------*/
/* ID: __ornw_rkr                                                             */
/*----------------------------------------------------------------------------*/
/*
ORNW
*/
__char4 __OVBIF __ornw_rkr(__char4, __char4 __CST(-128, 127));
__uchar4 __OVBIF __ornw_rkr(__uchar4, __uchar4 __CST(0, 255));
__short2 __OVBIF __ornw_rkr(__short2, __short2 __CST(-32768, 32767));
__ushort2 __OVBIF __ornw_rkr(__ushort2, __ushort2 __CST(0, 65535));
int __OVBIF __ornw_rkr(int, int __CST(-2147483648, 2147483647));
__uint __OVBIF __ornw_rkr(__uint, __uint __CST(0, 4294967295));

/*----------------------------------------------------------------------------*/
/* ID: __ornw_rrr                                                             */
/*----------------------------------------------------------------------------*/
/*
ORNW
*/
__char4 __OVBIF __ornw_rrr(__char4, __char4);
__uchar4 __OVBIF __ornw_rrr(__uchar4, __uchar4);
__short2 __OVBIF __ornw_rrr(__short2, __short2);
__ushort2 __OVBIF __ornw_rrr(__ushort2, __ushort2);
int __OVBIF __ornw_rrr(int, int);
__uint __OVBIF __ornw_rrr(__uint, __uint);

/*----------------------------------------------------------------------------*/
/* ID: __orw_rkr                                                              */
/*----------------------------------------------------------------------------*/
/*
ORW
*/
__char4 __OVBIF __orw_rkr(__char4, __char4 __CST(-128, 127));
__uchar4 __OVBIF __orw_rkr(__uchar4, __uchar4 __CST(0, 255));
__short2 __OVBIF __orw_rkr(__short2, __short2 __CST(-32768, 32767));
__ushort2 __OVBIF __orw_rkr(__ushort2, __ushort2 __CST(0, 65535));
int __OVBIF __orw_rkr(int, int __CST(-2147483648, 2147483647));
__uint __OVBIF __orw_rkr(__uint, __uint __CST(0, 4294967295));

/*----------------------------------------------------------------------------*/
/* ID: __orw_rrr                                                              */
/*----------------------------------------------------------------------------*/
/*
ORW
*/
__char4 __OVBIF __orw_rrr(__char4, __char4);
__uchar4 __OVBIF __orw_rrr(__uchar4, __uchar4);
__short2 __OVBIF __orw_rrr(__short2, __short2);
__ushort2 __OVBIF __orw_rrr(__ushort2, __ushort2);
int __OVBIF __orw_rrr(int, int);
__uint __OVBIF __orw_rrr(__uint, __uint);

/*----------------------------------------------------------------------------*/
/* ID: __packw_rrd                                                            */
/*----------------------------------------------------------------------------*/
/*
PACKW
*/
__cshort2 __OVBIF __packw_rrd(__cshort, __cshort);
__int2 __OVBIF __packw_rrd(int, int);
__uint2 __OVBIF __packw_rrd(__uint, __uint);
__float2 __OVBIF __packw_rrd(float, float);

/*----------------------------------------------------------------------------*/
/* ID: __packwdly4_rrd                                                        */
/*----------------------------------------------------------------------------*/
/*
PACKWDLY4
*/
long __OVBIF __packwdly4_rrd(int, int);
__ulong __OVBIF __packwdly4_rrd(__uint, __uint);

/*----------------------------------------------------------------------------*/
/* ID: __packx2_rrd                                                           */
/*----------------------------------------------------------------------------*/
/*
PACKX2
*/
__cchar4 __OVBIF __packx2_rrd(__cchar2, __cchar2);
__short4 __OVBIF __packx2_rrd(__short2, __short2);
__ushort4 __OVBIF __packx2_rrd(__ushort2, __ushort2);

/*----------------------------------------------------------------------------*/
/* ID: __pbitcntb_pr                                                          */
/*----------------------------------------------------------------------------*/
/*
PBITCNTB
*/
__uint __BIF __pbitcntb_pr(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __pbitcntd_pr                                                          */
/*----------------------------------------------------------------------------*/
/*
PBITCNTD
*/
__uint __BIF __pbitcntd_pr(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __pbitcnth_pr                                                          */
/*----------------------------------------------------------------------------*/
/*
PBITCNTH
*/
__uint __BIF __pbitcnth_pr(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __pbitcntw_pr                                                          */
/*----------------------------------------------------------------------------*/
/*
PBITCNTW
*/
__uint __BIF __pbitcntw_pr(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __pcntgatherb_prp                                                      */
/*----------------------------------------------------------------------------*/
/*

PCNTGATHERB
void __pcntgatherb_prp(__vpred, uint&, __vpred&);

*/

/*----------------------------------------------------------------------------*/
/* ID: __pcntgatherd_prp                                                      */
/*----------------------------------------------------------------------------*/
/*

PCNTGATHERD
void __pcntgatherd_prp(__vpred, uint&, __vpred&);

*/

/*----------------------------------------------------------------------------*/
/* ID: __pcntgatherh_prp                                                      */
/*----------------------------------------------------------------------------*/
/*

PCNTGATHERH
void __pcntgatherh_prp(__vpred, uint&, __vpred&);

*/

/*----------------------------------------------------------------------------*/
/* ID: __pcntgatherw_prp                                                      */
/*----------------------------------------------------------------------------*/
/*

PCNTGATHERW
void __pcntgatherw_prp(__vpred, uint&, __vpred&);

*/

/*----------------------------------------------------------------------------*/
/* ID: __pduph2b_pp                                                           */
/*----------------------------------------------------------------------------*/
/*
PDUPH2B
*/
__vpred __BIF __pduph2b_pp(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __pduph2d_pp                                                           */
/*----------------------------------------------------------------------------*/
/*
PDUPH2D
*/
__vpred __BIF __pduph2d_pp(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __pduph2h_pp                                                           */
/*----------------------------------------------------------------------------*/
/*
PDUPH2H
*/
__vpred __BIF __pduph2h_pp(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __pduph2w_pp                                                           */
/*----------------------------------------------------------------------------*/
/*
PDUPH2W
*/
__vpred __BIF __pduph2w_pp(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __pdupl2b_pp                                                           */
/*----------------------------------------------------------------------------*/
/*
PDUPL2B
*/
__vpred __BIF __pdupl2b_pp(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __pdupl2d_pp                                                           */
/*----------------------------------------------------------------------------*/
/*
PDUPL2D
*/
__vpred __BIF __pdupl2d_pp(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __pdupl2h_pp                                                           */
/*----------------------------------------------------------------------------*/
/*
PDUPL2H
*/
__vpred __BIF __pdupl2h_pp(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __pdupl2w_pp                                                           */
/*----------------------------------------------------------------------------*/
/*
PDUPL2W
*/
__vpred __BIF __pdupl2w_pp(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __prmbdb_pr                                                            */
/*----------------------------------------------------------------------------*/
/*
PRMBDB
*/
__uint __BIF __prmbdb_pr(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __prmbdd_pr                                                            */
/*----------------------------------------------------------------------------*/
/*
PRMBDD
*/
__uint __BIF __prmbdd_pr(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __prmbdh_pr                                                            */
/*----------------------------------------------------------------------------*/
/*
PRMBDH
*/
__uint __BIF __prmbdh_pr(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __prmbdw_pr                                                            */
/*----------------------------------------------------------------------------*/
/*
PRMBDW
*/
__uint __BIF __prmbdw_pr(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __replace_dkkd                                                         */
/*----------------------------------------------------------------------------*/
/*
REPLACE
*/
long __OVBIF __replace_dkkd(long, signed char __CST(0, 63), signed char __CST(0, 63), long);
__ulong __OVBIF __replace_dkkd(__ulong, __uchar __CST(0, 63), __uchar __CST(0, 63), __ulong);

/*----------------------------------------------------------------------------*/
/* ID: __replacev_dkkkv                                                       */
/*----------------------------------------------------------------------------*/
/*
REPLACEV
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __replacev_dkkkv(long, signed char __CST(0, 7), signed char __CST(0, 63), signed char __CST(0, 63), __long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __OVBIF __replacev_dkkkv(long, signed char __CST(0, 7), signed char __CST(0, 63), signed char __CST(0, 63), __long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __replacev_dkkkv(__ulong, __uchar __CST(0, 7), __uchar __CST(0, 63), __uchar __CST(0, 63), __ulong8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __OVBIF __replacev_dkkkv(__ulong, __uchar __CST(0, 7), __uchar __CST(0, 63), __uchar __CST(0, 63), __ulong4);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __set_rrr                                                              */
/*----------------------------------------------------------------------------*/
/*
SET
*/
int __BIF __set_rrr(int, int);

/*----------------------------------------------------------------------------*/
/* ID: __shld_dkd                                                             */
/*----------------------------------------------------------------------------*/
/*
SHLD
*/
long __OVBIF __shld_dkd(long, __uchar __CST(0, 63));
__ulong __OVBIF __shld_dkd(__ulong, __uchar __CST(0, 63));

/*----------------------------------------------------------------------------*/
/* ID: __shld_drd                                                             */
/*----------------------------------------------------------------------------*/
/*
SHLD
*/
long __OVBIF __shld_drd(long, int);
__ulong __OVBIF __shld_drd(__ulong, __uint);

/*----------------------------------------------------------------------------*/
/* ID: __shlw_rkr                                                             */
/*----------------------------------------------------------------------------*/
/*
SHLW
*/
int __OVBIF __shlw_rkr(int, __uchar __CST(0, 63));
__uint __OVBIF __shlw_rkr(__uint, __uchar __CST(0, 63));

/*----------------------------------------------------------------------------*/
/* ID: __shlw_rrr                                                             */
/*----------------------------------------------------------------------------*/
/*
SHLW
*/
int __OVBIF __shlw_rrr(int, int);
__uint __OVBIF __shlw_rrr(__uint, __uint);

/*----------------------------------------------------------------------------*/
/* ID: __shrd_dkd                                                             */
/*----------------------------------------------------------------------------*/
/*
SHRD
*/
long __BIF __shrd_dkd(long, __uchar __CST(0, 63));

/*----------------------------------------------------------------------------*/
/* ID: __shrd_drd                                                             */
/*----------------------------------------------------------------------------*/
/*
SHRD
*/
long __BIF __shrd_drd(long, int);

/*----------------------------------------------------------------------------*/
/* ID: __shrud_dkd                                                            */
/*----------------------------------------------------------------------------*/
/*
SHRUD
*/
__ulong __BIF __shrud_dkd(__ulong, __uchar __CST(0, 63));

/*----------------------------------------------------------------------------*/
/* ID: __shrud_drd                                                            */
/*----------------------------------------------------------------------------*/
/*
SHRUD
*/
__ulong __BIF __shrud_drd(__ulong, __uint);

/*----------------------------------------------------------------------------*/
/* ID: __shruw_rkr                                                            */
/*----------------------------------------------------------------------------*/
/*
SHRUW
*/
__uint __BIF __shruw_rkr(__uint, __uchar __CST(0, 63));

/*----------------------------------------------------------------------------*/
/* ID: __shruw_rrr                                                            */
/*----------------------------------------------------------------------------*/
/*
SHRUW
*/
__uint __BIF __shruw_rrr(__uint, __uint);

/*----------------------------------------------------------------------------*/
/* ID: __shrw_rkr                                                             */
/*----------------------------------------------------------------------------*/
/*
SHRW
*/
int __BIF __shrw_rkr(int, __uchar __CST(0, 63));

/*----------------------------------------------------------------------------*/
/* ID: __shrw_rrr                                                             */
/*----------------------------------------------------------------------------*/
/*
SHRW
*/
int __BIF __shrw_rrr(int, int);

/*----------------------------------------------------------------------------*/
/* ID: __smpyhw_rrr                                                           */
/*----------------------------------------------------------------------------*/
/*
SMPYHW
*/
int __BIF __smpyhw_rrr(short, short);

/*----------------------------------------------------------------------------*/
/* ID: __subd_ddd                                                             */
/*----------------------------------------------------------------------------*/
/*
SUBD
*/
long __OVBIF __subd_ddd(long, long);
__ulong __OVBIF __subd_ddd(__ulong, __ulong);

/*----------------------------------------------------------------------------*/
/* ID: __subdp_ddd                                                            */
/*----------------------------------------------------------------------------*/
/*
SUBDP
*/
double __BIF __subdp_ddd(double, double);

/*----------------------------------------------------------------------------*/
/* ID: __subrd_ddd                                                            */
/*----------------------------------------------------------------------------*/
/*
SUBRD
*/
long __OVBIF __subrd_ddd(long, long);
__ulong __OVBIF __subrd_ddd(__ulong, __ulong);

/*----------------------------------------------------------------------------*/
/* ID: __subrd_dkd                                                            */
/*----------------------------------------------------------------------------*/
/*
SUBRD
*/
long __OVBIF __subrd_dkd(long, int __CST(-2147483648, 2147483647));
__ulong __OVBIF __subrd_dkd(__ulong, __uint __CST(0, 2147483647));

/*----------------------------------------------------------------------------*/
/* ID: __subrw_rkr                                                            */
/*----------------------------------------------------------------------------*/
/*
SUBRW
*/
int __OVBIF __subrw_rkr(int, int __CST(-2147483648, 2147483647));
__uint __OVBIF __subrw_rkr(__uint, __uint __CST(0, 4294967295));

/*----------------------------------------------------------------------------*/
/* ID: __subrw_rrr                                                            */
/*----------------------------------------------------------------------------*/
/*
SUBRW
*/
int __OVBIF __subrw_rrr(int, int);
__uint __OVBIF __subrw_rrr(__uint, __uint);

/*----------------------------------------------------------------------------*/
/* ID: __subsp_rrr                                                            */
/*----------------------------------------------------------------------------*/
/*
SUBSP
*/
float __BIF __subsp_rrr(float, float);

/*----------------------------------------------------------------------------*/
/* ID: __subw_rrr                                                             */
/*----------------------------------------------------------------------------*/
/*
SUBW
*/
int __OVBIF __subw_rrr(int, int);
__uint __OVBIF __subw_rrr(__uint, __uint);

/*----------------------------------------------------------------------------*/
/* ID: __vabsb_vv                                                             */
/*----------------------------------------------------------------------------*/
/*
VABSB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __OVBIF __vabsb_vv(__char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __vabsb_vv(__char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cchar16 __OVBIF __vabsb_vv(__cchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cchar32 __OVBIF __vabsb_vv(__cchar32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vabsd_vv                                                             */
/*----------------------------------------------------------------------------*/
/*
VABSD
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __OVBIF __vabsd_vv(__long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __vabsd_vv(__long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__clong2 __OVBIF __vabsd_vv(__clong2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__clong4 __OVBIF __vabsd_vv(__clong4);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vabsdp_vv                                                            */
/*----------------------------------------------------------------------------*/
/*
VABSDP
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__double4 __OVBIF __vabsdp_vv(__double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__double8 __OVBIF __vabsdp_vv(__double8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cdouble2 __OVBIF __vabsdp_vv(__cdouble2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cdouble4 __OVBIF __vabsdp_vv(__cdouble4);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vabsh_vv                                                             */
/*----------------------------------------------------------------------------*/
/*
VABSH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __OVBIF __vabsh_vv(__short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __vabsh_vv(__short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cshort8 __OVBIF __vabsh_vv(__cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cshort16 __OVBIF __vabsh_vv(__cshort16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vabssp_vv                                                            */
/*----------------------------------------------------------------------------*/
/*
VABSSP
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__float8 __OVBIF __vabssp_vv(__float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__float16 __OVBIF __vabssp_vv(__float16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cfloat4 __OVBIF __vabssp_vv(__cfloat4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cfloat8 __OVBIF __vabssp_vv(__cfloat8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vabsw_vv                                                             */
/*----------------------------------------------------------------------------*/
/*
VABSW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __OVBIF __vabsw_vv(__int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __vabsw_vv(__int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cint4 __OVBIF __vabsw_vv(__cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cint8 __OVBIF __vabsw_vv(__cint8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vaddb_vkv                                                            */
/*----------------------------------------------------------------------------*/
/*
VADDB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __OVBIF __vaddb_vkv(__char32, __char32 __CST(-128, 127));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __vaddb_vkv(__char64, __char64 __CST(-128, 127));
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __OVBIF __vaddb_vkv(__uchar32, __uchar32 __CST(0, 255));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __vaddb_vkv(__uchar64, __uchar64 __CST(0, 255));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vaddb_vvv                                                            */
/*----------------------------------------------------------------------------*/
/*
VADDB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __OVBIF __vaddb_vvv(__char32, __char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __vaddb_vvv(__char64, __char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __OVBIF __vaddb_vvv(__uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __vaddb_vvv(__uchar64, __uchar64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cchar16 __OVBIF __vaddb_vvv(__cchar16, __cchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cchar32 __OVBIF __vaddb_vvv(__cchar32, __cchar32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vaddcb_pvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VADDCB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __OVBIF __vaddcb_pvv(__vpred, __char32, __char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __vaddcb_pvv(__vpred, __char64, __char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __OVBIF __vaddcb_pvv(__vpred, __uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __vaddcb_pvv(__vpred, __uchar64, __uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vaddcd_pvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VADDCD
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __OVBIF __vaddcd_pvv(__vpred, __long4, __long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __vaddcd_pvv(__vpred, __long8, __long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __OVBIF __vaddcd_pvv(__vpred, __ulong4, __ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __vaddcd_pvv(__vpred, __ulong8, __ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vaddch_pvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VADDCH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __OVBIF __vaddch_pvv(__vpred, __short16, __short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __vaddch_pvv(__vpred, __short32, __short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __OVBIF __vaddch_pvv(__vpred, __ushort16, __ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __vaddch_pvv(__vpred, __ushort32, __ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vaddcw_pvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VADDCW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __OVBIF __vaddcw_pvv(__vpred, __int8, __int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __vaddcw_pvv(__vpred, __int16, __int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __OVBIF __vaddcw_pvv(__vpred, __uint8, __uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __vaddcw_pvv(__vpred, __uint16, __uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vaddd_vkv                                                            */
/*----------------------------------------------------------------------------*/
/*
VADDD
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __OVBIF __vaddd_vkv(__long4, __int4 __CST(-2147483648, 2147483647));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __vaddd_vkv(__long8, __int8 __CST(-2147483648, 2147483647));
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __OVBIF __vaddd_vkv(__ulong4, __uint4 __CST(0, 2147483647));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __vaddd_vkv(__ulong8, __uint8 __CST(0, 2147483647));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vaddd_vvv                                                            */
/*----------------------------------------------------------------------------*/
/*
VADDD
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __OVBIF __vaddd_vvv(__long4, __long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __vaddd_vvv(__long8, __long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __OVBIF __vaddd_vvv(__ulong4, __ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __vaddd_vvv(__ulong8, __ulong8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__clong2 __OVBIF __vaddd_vvv(__clong2, __clong2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__clong4 __OVBIF __vaddd_vvv(__clong4, __clong4);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vadddp_vvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VADDDP
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__double4 __OVBIF __vadddp_vvv(__double4, __double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__double8 __OVBIF __vadddp_vvv(__double8, __double8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cdouble2 __OVBIF __vadddp_vvv(__cdouble2, __cdouble2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cdouble4 __OVBIF __vadddp_vvv(__cdouble4, __cdouble4);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vaddh_vkv                                                            */
/*----------------------------------------------------------------------------*/
/*
VADDH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __OVBIF __vaddh_vkv(__short16, __short16 __CST(-32768, 32767));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __vaddh_vkv(__short32, __short32 __CST(-32768, 32767));
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __OVBIF __vaddh_vkv(__ushort16, __ushort16 __CST(0, 65535));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __vaddh_vkv(__ushort32, __ushort32 __CST(0, 65535));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vaddh_vvv                                                            */
/*----------------------------------------------------------------------------*/
/*
VADDH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __OVBIF __vaddh_vvv(__short16, __short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __vaddh_vvv(__short32, __short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __OVBIF __vaddh_vvv(__ushort16, __ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __vaddh_vvv(__ushort32, __ushort32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cshort8 __OVBIF __vaddh_vvv(__cshort8, __cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cshort16 __OVBIF __vaddh_vvv(__cshort16, __cshort16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vaddsp_vvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VADDSP
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__float8 __OVBIF __vaddsp_vvv(__float8, __float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__float16 __OVBIF __vaddsp_vvv(__float16, __float16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cfloat4 __OVBIF __vaddsp_vvv(__cfloat4, __cfloat4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cfloat8 __OVBIF __vaddsp_vvv(__cfloat8, __cfloat8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vaddw_vkv                                                            */
/*----------------------------------------------------------------------------*/
/*
VADDW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __OVBIF __vaddw_vkv(__int8, __int8 __CST(-2147483648, 2147483647));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __vaddw_vkv(__int16, __int16 __CST(-2147483648, 2147483647));
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __OVBIF __vaddw_vkv(__uint8, __uint8 __CST(0, 4294967295));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __vaddw_vkv(__uint16, __uint16 __CST(0, 4294967295));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vaddw_vvv                                                            */
/*----------------------------------------------------------------------------*/
/*
VADDW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __OVBIF __vaddw_vvv(__int8, __int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __vaddw_vvv(__int16, __int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __OVBIF __vaddw_vvv(__uint8, __uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __vaddw_vvv(__uint16, __uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cint4 __OVBIF __vaddw_vvv(__cint4, __cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cint8 __OVBIF __vaddw_vvv(__cint8, __cint8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vandnw_vkv                                                           */
/*----------------------------------------------------------------------------*/
/*
VANDNW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __OVBIF __vandnw_vkv(__int8, __int8 __CST(-2147483648, 2147483647));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __vandnw_vkv(__int16, __int16 __CST(-2147483648, 2147483647));
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __OVBIF __vandnw_vkv(__uint8, __uint8 __CST(0, 4294967295));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __vandnw_vkv(__uint16, __uint16 __CST(0, 4294967295));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vandnw_vvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VANDNW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __OVBIF __vandnw_vvv(__char32, __char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __vandnw_vvv(__char64, __char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __OVBIF __vandnw_vvv(__uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __vandnw_vvv(__uchar64, __uchar64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __OVBIF __vandnw_vvv(__short16, __short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __vandnw_vvv(__short32, __short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __OVBIF __vandnw_vvv(__ushort16, __ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __vandnw_vvv(__ushort32, __ushort32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __OVBIF __vandnw_vvv(__int8, __int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __vandnw_vvv(__int16, __int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __OVBIF __vandnw_vvv(__uint8, __uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __vandnw_vvv(__uint16, __uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __OVBIF __vandnw_vvv(__long4, __long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __vandnw_vvv(__long8, __long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __OVBIF __vandnw_vvv(__ulong4, __ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __vandnw_vvv(__ulong8, __ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vandw_vkv                                                            */
/*----------------------------------------------------------------------------*/
/*
VANDW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __OVBIF __vandw_vkv(__int8, __int8 __CST(-2147483648, 2147483647));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __vandw_vkv(__int16, __int16 __CST(-2147483648, 2147483647));
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __OVBIF __vandw_vkv(__uint8, __uint8 __CST(0, 4294967295));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __vandw_vkv(__uint16, __uint16 __CST(0, 4294967295));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vandw_vvv                                                            */
/*----------------------------------------------------------------------------*/
/*
VANDW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __OVBIF __vandw_vvv(__char32, __char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __vandw_vvv(__char64, __char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __OVBIF __vandw_vvv(__uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __vandw_vvv(__uchar64, __uchar64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __OVBIF __vandw_vvv(__short16, __short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __vandw_vvv(__short32, __short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __OVBIF __vandw_vvv(__ushort16, __ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __vandw_vvv(__ushort32, __ushort32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __OVBIF __vandw_vvv(__int8, __int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __vandw_vvv(__int16, __int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __OVBIF __vandw_vvv(__uint8, __uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __vandw_vvv(__uint16, __uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __OVBIF __vandw_vvv(__long4, __long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __vandw_vvv(__long8, __long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __OVBIF __vandw_vvv(__ulong4, __ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __vandw_vvv(__ulong8, __ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vapysb_vvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VAPYSB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __BIF __vapysb_vvv(__char32, __char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __BIF __vapysb_vvv(__char64, __char64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vapysd_vvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VAPYSD
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __BIF __vapysd_vvv(__long4, __long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __BIF __vapysd_vvv(__long8, __long8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vapysh_vvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VAPYSH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __BIF __vapysh_vvv(__short16, __short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __BIF __vapysh_vvv(__short32, __short32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vapysw_vvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VAPYSW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __BIF __vapysw_vvv(__int8, __int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __BIF __vapysw_vvv(__int16, __int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vavgb_vvv                                                            */
/*----------------------------------------------------------------------------*/
/*
VAVGB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __BIF __vavgb_vvv(__char32, __char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __BIF __vavgb_vvv(__char64, __char64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vavgd_vvv                                                            */
/*----------------------------------------------------------------------------*/
/*
VAVGD
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __BIF __vavgd_vvv(__long4, __long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __BIF __vavgd_vvv(__long8, __long8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vavgh_vvv                                                            */
/*----------------------------------------------------------------------------*/
/*
VAVGH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __BIF __vavgh_vvv(__short16, __short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __BIF __vavgh_vvv(__short32, __short32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vavgnrb_vvv                                                          */
/*----------------------------------------------------------------------------*/
/*
VAVGNRB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __BIF __vavgnrb_vvv(__char32, __char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __BIF __vavgnrb_vvv(__char64, __char64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vavgnrd_vvv                                                          */
/*----------------------------------------------------------------------------*/
/*
VAVGNRD
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __BIF __vavgnrd_vvv(__long4, __long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __BIF __vavgnrd_vvv(__long8, __long8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vavgnrh_vvv                                                          */
/*----------------------------------------------------------------------------*/
/*
VAVGNRH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __BIF __vavgnrh_vvv(__short16, __short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __BIF __vavgnrh_vvv(__short32, __short32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vavgnrub_vvv                                                         */
/*----------------------------------------------------------------------------*/
/*
VAVGNRUB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __BIF __vavgnrub_vvv(__uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __vavgnrub_vvv(__uchar64, __uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vavgnrud_vvv                                                         */
/*----------------------------------------------------------------------------*/
/*
VAVGNRUD
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __BIF __vavgnrud_vvv(__ulong4, __ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __BIF __vavgnrud_vvv(__ulong8, __ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vavgnruh_vvv                                                         */
/*----------------------------------------------------------------------------*/
/*
VAVGNRUH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __BIF __vavgnruh_vvv(__ushort16, __ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __BIF __vavgnruh_vvv(__ushort32, __ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vavgnruw_vvv                                                         */
/*----------------------------------------------------------------------------*/
/*
VAVGNRUW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __BIF __vavgnruw_vvv(__uint8, __uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __BIF __vavgnruw_vvv(__uint16, __uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vavgnrw_vvv                                                          */
/*----------------------------------------------------------------------------*/
/*
VAVGNRW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __BIF __vavgnrw_vvv(__int8, __int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __BIF __vavgnrw_vvv(__int16, __int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vavgub_vvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VAVGUB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __BIF __vavgub_vvv(__uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __vavgub_vvv(__uchar64, __uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vavgud_vvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VAVGUD
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __BIF __vavgud_vvv(__ulong4, __ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __BIF __vavgud_vvv(__ulong8, __ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vavguh_vvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VAVGUH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __BIF __vavguh_vvv(__ushort16, __ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __BIF __vavguh_vvv(__ushort32, __ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vavguw_vvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VAVGUW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __BIF __vavguw_vvv(__uint8, __uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __BIF __vavguw_vvv(__uint16, __uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vavgw_vvv                                                            */
/*----------------------------------------------------------------------------*/
/*
VAVGW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __BIF __vavgw_vvv(__int8, __int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __BIF __vavgw_vvv(__int16, __int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vbinlogw_vv                                                          */
/*----------------------------------------------------------------------------*/
/*
VBINLOGW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __BIF __vbinlogw_vv(__uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __BIF __vbinlogw_vv(__uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vbitcntb_vv                                                          */
/*----------------------------------------------------------------------------*/
/*
VBITCNTB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __OVBIF __vbitcntb_vv(__char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __vbitcntb_vv(__char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __OVBIF __vbitcntb_vv(__uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __vbitcntb_vv(__uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vbitcntd_vv                                                          */
/*----------------------------------------------------------------------------*/
/*
VBITCNTD
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __OVBIF __vbitcntd_vv(__long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __vbitcntd_vv(__long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __OVBIF __vbitcntd_vv(__ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __vbitcntd_vv(__ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vbitcnth_vv                                                          */
/*----------------------------------------------------------------------------*/
/*
VBITCNTH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __OVBIF __vbitcnth_vv(__short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __vbitcnth_vv(__short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __OVBIF __vbitcnth_vv(__ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __vbitcnth_vv(__ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vbitcntw_vv                                                          */
/*----------------------------------------------------------------------------*/
/*
VBITCNTW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __OVBIF __vbitcntw_vv(__int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __vbitcntw_vv(__int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __OVBIF __vbitcntw_vv(__uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __vbitcntw_vv(__uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vbitdeald_vv                                                         */
/*----------------------------------------------------------------------------*/
/*
VBITDEALD
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __OVBIF __vbitdeald_vv(__long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __vbitdeald_vv(__long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __OVBIF __vbitdeald_vv(__ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __vbitdeald_vv(__ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vbitdealw_vv                                                         */
/*----------------------------------------------------------------------------*/
/*
VBITDEALW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __OVBIF __vbitdealw_vv(__int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __vbitdealw_vv(__int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __OVBIF __vbitdealw_vv(__uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __vbitdealw_vv(__uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vbitrd_vv                                                            */
/*----------------------------------------------------------------------------*/
/*
VBITRD
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __OVBIF __vbitrd_vv(__long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __vbitrd_vv(__long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __OVBIF __vbitrd_vv(__ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __vbitrd_vv(__ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vbitrw_vv                                                            */
/*----------------------------------------------------------------------------*/
/*
VBITRW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __OVBIF __vbitrw_vv(__int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __vbitrw_vv(__int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __OVBIF __vbitrw_vv(__uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __vbitrw_vv(__uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vbitshfld_vv                                                         */
/*----------------------------------------------------------------------------*/
/*
VBITSHFLD
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __OVBIF __vbitshfld_vv(__long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __vbitshfld_vv(__long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __OVBIF __vbitshfld_vv(__ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __vbitshfld_vv(__ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vbitshflw_vv                                                         */
/*----------------------------------------------------------------------------*/
/*
VBITSHFLW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __OVBIF __vbitshflw_vv(__int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __vbitshflw_vv(__int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __OVBIF __vbitshflw_vv(__uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __vbitshflw_vv(__uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vbittran8b_vv                                                        */
/*----------------------------------------------------------------------------*/
/*
VBITTRAN8B
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __BIF __vbittran8b_vv(__uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __vbittran8b_vv(__uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vbpackh_vvv                                                          */
/*----------------------------------------------------------------------------*/
/*
VBPACKH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __OVBIF __vbpackh_vvv(__char32, __char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __vbpackh_vvv(__char64, __char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __OVBIF __vbpackh_vvv(__uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __vbpackh_vvv(__uchar64, __uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vbpackl_vvv                                                          */
/*----------------------------------------------------------------------------*/
/*
VBPACKL
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __OVBIF __vbpackl_vvv(__char32, __char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __vbpackl_vvv(__char64, __char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __OVBIF __vbpackl_vvv(__uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __vbpackl_vvv(__uchar64, __uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vbunpkd_vv                                                           */
/*----------------------------------------------------------------------------*/
/*
VBUNPKD
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __OVBIF __vbunpkd_vv(__char4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __vbunpkd_vv(__char8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__clong2 __OVBIF __vbunpkd_vv(__cchar2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__clong4 __OVBIF __vbunpkd_vv(__cchar4);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vbunpkdu_vv                                                          */
/*----------------------------------------------------------------------------*/
/*
VBUNPKDU
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __BIF __vbunpkdu_vv(__uchar4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __BIF __vbunpkdu_vv(__uchar8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vbunpkh_vv                                                           */
/*----------------------------------------------------------------------------*/
/*
VBUNPKH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __OVBIF __vbunpkh_vv(__char16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __vbunpkh_vv(__char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cshort8 __OVBIF __vbunpkh_vv(__cchar8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cshort16 __OVBIF __vbunpkh_vv(__cchar16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vbunpkhh_vv                                                          */
/*----------------------------------------------------------------------------*/
/*
VBUNPKHH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __BIF __vbunpkhh_vv(__char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __BIF __vbunpkhh_vv(__char64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vbunpkhl_vv                                                          */
/*----------------------------------------------------------------------------*/
/*
VBUNPKHL
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __BIF __vbunpkhl_vv(__char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __BIF __vbunpkhl_vv(__char64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vbunpkhu_vv                                                          */
/*----------------------------------------------------------------------------*/
/*
VBUNPKHU
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __BIF __vbunpkhu_vv(__uchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __BIF __vbunpkhu_vv(__uchar32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vbunpkuhh_vv                                                         */
/*----------------------------------------------------------------------------*/
/*
VBUNPKUHH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __BIF __vbunpkuhh_vv(__uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __BIF __vbunpkuhh_vv(__uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vbunpkuhl_vv                                                         */
/*----------------------------------------------------------------------------*/
/*
VBUNPKUHL
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __BIF __vbunpkuhl_vv(__uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __BIF __vbunpkuhl_vv(__uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vbunpkw_vv                                                           */
/*----------------------------------------------------------------------------*/
/*
VBUNPKW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __OVBIF __vbunpkw_vv(__char8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __vbunpkw_vv(__char16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cint4 __OVBIF __vbunpkw_vv(__cchar4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cint8 __OVBIF __vbunpkw_vv(__cchar8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vbunpkwu_vv                                                          */
/*----------------------------------------------------------------------------*/
/*
VBUNPKWU
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __BIF __vbunpkwu_vv(__uchar8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __BIF __vbunpkwu_vv(__uchar16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vccdotp2hw_vvv                                                       */
/*----------------------------------------------------------------------------*/
/*
VCCDOTP2HW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cint4 __BIF __vccdotp2hw_vvv(__cshort8, __cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cint8 __BIF __vccdotp2hw_vvv(__cshort16, __cshort16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vccmatmpyhw_vww                                                      */
/*----------------------------------------------------------------------------*/
/*

VCCMATMPYHW
#if __C7X_VEC_SIZE_BITS__ == 256
void __vccmatmpyhw_vww(cshort8, cshort8, cshort8, cint4&, cint4&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
void __vccmatmpyhw_vww(cshort16, cshort16, cshort16, cint8&, cint8&);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __vccmatmpyr1hh_vwv                                                    */
/*----------------------------------------------------------------------------*/
/*
VCCMATMPYR1HH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cshort8 __BIF __vccmatmpyr1hh_vwv(__cshort8, __cshort8, __cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cshort16 __BIF __vccmatmpyr1hh_vwv(__cshort16, __cshort16, __cshort16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vccmpyhw_vvw                                                         */
/*----------------------------------------------------------------------------*/
/*

VCCMPYHW
#if __C7X_VEC_SIZE_BITS__ == 256
void __vccmpyhw_vvw(cshort8, cshort8, cint4&, cint4&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
void __vccmpyhw_vvw(cshort16, cshort16, cint8&, cint8&);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __vccmpyr1hh_vvv                                                       */
/*----------------------------------------------------------------------------*/
/*
VCCMPYR1HH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cshort8 __BIF __vccmpyr1hh_vvv(__cshort8, __cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cshort16 __BIF __vccmpyr1hh_vvv(__cshort16, __cshort16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vccmpyr1ww_vvv                                                       */
/*----------------------------------------------------------------------------*/
/*
VCCMPYR1WW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cint4 __BIF __vccmpyr1ww_vvv(__cint4, __cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cint8 __BIF __vccmpyr1ww_vvv(__cint8, __cint8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcdotp2hw_vvv                                                        */
/*----------------------------------------------------------------------------*/
/*
VCDOTP2HW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cint4 __BIF __vcdotp2hw_vvv(__cshort8, __cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cint8 __BIF __vcdotp2hw_vvv(__cshort16, __cshort16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcdotpm2opn16b32h_yvvv                                               */
/*----------------------------------------------------------------------------*/
/*
VCDOTPM2OPN16B32H
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__cshort16 __BIF __vcdotpm2opn16b32h_yvvv(__ushort32, __ulong, __cchar32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcdotpm2opn1h32h_yvvv                                                */
/*----------------------------------------------------------------------------*/
/*
VCDOTPM2OPN1H32H
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__cshort16 __BIF __vcdotpm2opn1h32h_yvvv(__ushort32, __uint, __cshort16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcdotpm2opn8h16w_yvvv                                                */
/*----------------------------------------------------------------------------*/
/*
VCDOTPM2OPN8H16W
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__cint8 __BIF __vcdotpm2opn8h16w_yvvv(__ulong8, __uint4, __cshort8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcdotpm2opn8w16w_yvvv                                                */
/*----------------------------------------------------------------------------*/
/*
VCDOTPM2OPN8W16W
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__cint8 __BIF __vcdotpm2opn8w16w_yvvv(__ulong8, __uint4, __cint8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcdotpm32opn16b32h_yvvv                                              */
/*----------------------------------------------------------------------------*/
/*
VCDOTPM32OPN16B32H
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__cshort16 __BIF __vcdotpm32opn16b32h_yvvv(__ushort32, __ulong4, __cchar32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vclassdp_vv                                                          */
/*----------------------------------------------------------------------------*/
/*
VCLASSDP
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __BIF __vclassdp_vv(__double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __BIF __vclassdp_vv(__double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vclasssp_vv                                                          */
/*----------------------------------------------------------------------------*/
/*
VCLASSSP
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __BIF __vclasssp_vv(__float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __BIF __vclasssp_vv(__float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcmatmpyhw_vww                                                       */
/*----------------------------------------------------------------------------*/
/*

VCMATMPYHW
#if __C7X_VEC_SIZE_BITS__ == 256
void __vcmatmpyhw_vww(cshort8, cshort8, cshort8, cint4&, cint4&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
void __vcmatmpyhw_vww(cshort16, cshort16, cshort16, cint8&, cint8&);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __vcmatmpyr1hh_vwv                                                     */
/*----------------------------------------------------------------------------*/
/*
VCMATMPYR1HH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cshort8 __BIF __vcmatmpyr1hh_vwv(__cshort8, __cshort8, __cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cshort16 __BIF __vcmatmpyr1hh_vwv(__cshort16, __cshort16, __cshort16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcmaxb_vvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VCMAXB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __BIF __vcmaxb_vvv(__char32, __char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __BIF __vcmaxb_vvv(__char64, __char64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcmaxh_vvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VCMAXH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __BIF __vcmaxh_vvv(__short16, __short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __BIF __vcmaxh_vvv(__short32, __short32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcmaxpb_vvp                                                          */
/*----------------------------------------------------------------------------*/
/*

VCMAXPB
#if __C7X_VEC_SIZE_BITS__ == 256
void __vcmaxpb_vvp(char32, char32&, __vpred&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
void __vcmaxpb_vvp(char64, char64&, __vpred&);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __vcmaxph_vvp                                                          */
/*----------------------------------------------------------------------------*/
/*

VCMAXPH
#if __C7X_VEC_SIZE_BITS__ == 256
void __vcmaxph_vvp(short16, short16&, __vpred&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
void __vcmaxph_vvp(short32, short32&, __vpred&);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __vcmpeqb_vvp                                                          */
/*----------------------------------------------------------------------------*/
/*
VCMPEQB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__vpred __OVBIF __vcmpeqb_vvp(__char32, __char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __OVBIF __vcmpeqb_vvp(__char64, __char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__vpred __OVBIF __vcmpeqb_vvp(__uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __OVBIF __vcmpeqb_vvp(__uchar64, __uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcmpeqd_vvp                                                          */
/*----------------------------------------------------------------------------*/
/*
VCMPEQD
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__vpred __OVBIF __vcmpeqd_vvp(__long4, __long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __OVBIF __vcmpeqd_vvp(__long8, __long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__vpred __OVBIF __vcmpeqd_vvp(__ulong4, __ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __OVBIF __vcmpeqd_vvp(__ulong8, __ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcmpeqdp_vvp                                                         */
/*----------------------------------------------------------------------------*/
/*
VCMPEQDP
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__vpred __BIF __vcmpeqdp_vvp(__double4, __double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __BIF __vcmpeqdp_vvp(__double8, __double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcmpeqh_vvp                                                          */
/*----------------------------------------------------------------------------*/
/*
VCMPEQH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__vpred __OVBIF __vcmpeqh_vvp(__short16, __short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __OVBIF __vcmpeqh_vvp(__short32, __short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__vpred __OVBIF __vcmpeqh_vvp(__ushort16, __ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __OVBIF __vcmpeqh_vvp(__ushort32, __ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcmpeqsp_vvp                                                         */
/*----------------------------------------------------------------------------*/
/*
VCMPEQSP
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__vpred __BIF __vcmpeqsp_vvp(__float8, __float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __BIF __vcmpeqsp_vvp(__float16, __float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcmpeqw_vvp                                                          */
/*----------------------------------------------------------------------------*/
/*
VCMPEQW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__vpred __OVBIF __vcmpeqw_vvp(__int8, __int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __OVBIF __vcmpeqw_vvp(__int16, __int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__vpred __OVBIF __vcmpeqw_vvp(__uint8, __uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __OVBIF __vcmpeqw_vvp(__uint16, __uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcmpgeb_vvp                                                          */
/*----------------------------------------------------------------------------*/
/*
VCMPGEB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__vpred __BIF __vcmpgeb_vvp(__char32, __char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __BIF __vcmpgeb_vvp(__char64, __char64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcmpged_vvp                                                          */
/*----------------------------------------------------------------------------*/
/*
VCMPGED
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__vpred __BIF __vcmpged_vvp(__long4, __long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __BIF __vcmpged_vvp(__long8, __long8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcmpgeh_vvp                                                          */
/*----------------------------------------------------------------------------*/
/*
VCMPGEH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__vpred __BIF __vcmpgeh_vvp(__short16, __short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __BIF __vcmpgeh_vvp(__short32, __short32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcmpgeub_vvp                                                         */
/*----------------------------------------------------------------------------*/
/*
VCMPGEUB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__vpred __BIF __vcmpgeub_vvp(__uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __BIF __vcmpgeub_vvp(__uchar64, __uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcmpgeud_vvp                                                         */
/*----------------------------------------------------------------------------*/
/*
VCMPGEUD
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__vpred __BIF __vcmpgeud_vvp(__ulong4, __ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __BIF __vcmpgeud_vvp(__ulong8, __ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcmpgeuh_vvp                                                         */
/*----------------------------------------------------------------------------*/
/*
VCMPGEUH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__vpred __BIF __vcmpgeuh_vvp(__ushort16, __ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __BIF __vcmpgeuh_vvp(__ushort32, __ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcmpgeuw_vvp                                                         */
/*----------------------------------------------------------------------------*/
/*
VCMPGEUW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__vpred __BIF __vcmpgeuw_vvp(__uint8, __uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __BIF __vcmpgeuw_vvp(__uint16, __uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcmpgew_vvp                                                          */
/*----------------------------------------------------------------------------*/
/*
VCMPGEW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__vpred __BIF __vcmpgew_vvp(__int8, __int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __BIF __vcmpgew_vvp(__int16, __int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcmpgtb_vvp                                                          */
/*----------------------------------------------------------------------------*/
/*
VCMPGTB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__vpred __BIF __vcmpgtb_vvp(__char32, __char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __BIF __vcmpgtb_vvp(__char64, __char64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcmpgtd_vvp                                                          */
/*----------------------------------------------------------------------------*/
/*
VCMPGTD
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__vpred __BIF __vcmpgtd_vvp(__long4, __long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __BIF __vcmpgtd_vvp(__long8, __long8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcmpgth_vvp                                                          */
/*----------------------------------------------------------------------------*/
/*
VCMPGTH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__vpred __BIF __vcmpgth_vvp(__short16, __short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __BIF __vcmpgth_vvp(__short32, __short32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcmpgtub_vvp                                                         */
/*----------------------------------------------------------------------------*/
/*
VCMPGTUB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__vpred __BIF __vcmpgtub_vvp(__uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __BIF __vcmpgtub_vvp(__uchar64, __uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcmpgtud_vvp                                                         */
/*----------------------------------------------------------------------------*/
/*
VCMPGTUD
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__vpred __BIF __vcmpgtud_vvp(__ulong4, __ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __BIF __vcmpgtud_vvp(__ulong8, __ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcmpgtuh_vvp                                                         */
/*----------------------------------------------------------------------------*/
/*
VCMPGTUH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__vpred __BIF __vcmpgtuh_vvp(__ushort16, __ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __BIF __vcmpgtuh_vvp(__ushort32, __ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcmpgtuw_vvp                                                         */
/*----------------------------------------------------------------------------*/
/*
VCMPGTUW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__vpred __BIF __vcmpgtuw_vvp(__uint8, __uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __BIF __vcmpgtuw_vvp(__uint16, __uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcmpgtw_vvp                                                          */
/*----------------------------------------------------------------------------*/
/*
VCMPGTW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__vpred __BIF __vcmpgtw_vvp(__int8, __int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __BIF __vcmpgtw_vvp(__int16, __int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcmpledp_vvp                                                         */
/*----------------------------------------------------------------------------*/
/*
VCMPLEDP
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__vpred __BIF __vcmpledp_vvp(__double4, __double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __BIF __vcmpledp_vvp(__double8, __double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcmplesp_vvp                                                         */
/*----------------------------------------------------------------------------*/
/*
VCMPLESP
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__vpred __BIF __vcmplesp_vvp(__float8, __float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __BIF __vcmplesp_vvp(__float16, __float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcmpltdp_vvp                                                         */
/*----------------------------------------------------------------------------*/
/*
VCMPLTDP
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__vpred __BIF __vcmpltdp_vvp(__double4, __double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __BIF __vcmpltdp_vvp(__double8, __double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcmpltsp_vvp                                                         */
/*----------------------------------------------------------------------------*/
/*
VCMPLTSP
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__vpred __BIF __vcmpltsp_vvp(__float8, __float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__vpred __BIF __vcmpltsp_vvp(__float16, __float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcmpyhw_vvw                                                          */
/*----------------------------------------------------------------------------*/
/*

VCMPYHW
#if __C7X_VEC_SIZE_BITS__ == 256
void __vcmpyhw_vvw(cshort8, cshort8, cint4&, cint4&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
void __vcmpyhw_vvw(cshort16, cshort16, cint8&, cint8&);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __vcmpyr1hh_vvv                                                        */
/*----------------------------------------------------------------------------*/
/*
VCMPYR1HH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cshort8 __BIF __vcmpyr1hh_vvv(__cshort8, __cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cshort16 __BIF __vcmpyr1hh_vvv(__cshort16, __cshort16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcmpyr1ww_vvv                                                        */
/*----------------------------------------------------------------------------*/
/*
VCMPYR1WW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cint4 __BIF __vcmpyr1ww_vvv(__cint4, __cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cint8 __BIF __vcmpyr1ww_vvv(__cint8, __cint8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcmpyrhh_vvv                                                         */
/*----------------------------------------------------------------------------*/
/*
VCMPYRHH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cshort8 __BIF __vcmpyrhh_vvv(__cshort8, __cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cshort16 __BIF __vcmpyrhh_vvv(__cshort16, __cshort16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcmpysp_vvw                                                          */
/*----------------------------------------------------------------------------*/
/*

VCMPYSP
#if __C7X_VEC_SIZE_BITS__ == 256
void __vcmpysp_vvw(cfloat4, cfloat4, float8&, float8&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
void __vcmpysp_vvw(cfloat8, cfloat8, float16&, float16&);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __vcrot270h_vv                                                         */
/*----------------------------------------------------------------------------*/
/*
VCROT270H
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cshort8 __BIF __vcrot270h_vv(__cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cshort16 __BIF __vcrot270h_vv(__cshort16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcrot270sp_vv                                                        */
/*----------------------------------------------------------------------------*/
/*
VCROT270SP
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cfloat4 __BIF __vcrot270sp_vv(__cfloat4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cfloat8 __BIF __vcrot270sp_vv(__cfloat8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcrot270w_vv                                                         */
/*----------------------------------------------------------------------------*/
/*
VCROT270W
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cint4 __BIF __vcrot270w_vv(__cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cint8 __BIF __vcrot270w_vv(__cint8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcrot90h_vv                                                          */
/*----------------------------------------------------------------------------*/
/*
VCROT90H
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cshort8 __BIF __vcrot90h_vv(__cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cshort16 __BIF __vcrot90h_vv(__cshort16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcrot90sp_vv                                                         */
/*----------------------------------------------------------------------------*/
/*
VCROT90SP
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cfloat4 __BIF __vcrot90sp_vv(__cfloat4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cfloat8 __BIF __vcrot90sp_vv(__cfloat8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcrot90w_vv                                                          */
/*----------------------------------------------------------------------------*/
/*
VCROT90W
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cint4 __BIF __vcrot90w_vv(__cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cint8 __BIF __vcrot90w_vv(__cint8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdeal2b_vv                                                           */
/*----------------------------------------------------------------------------*/
/*
VDEAL2B
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __OVBIF __vdeal2b_vv(__char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __vdeal2b_vv(__char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __OVBIF __vdeal2b_vv(__uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __vdeal2b_vv(__uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdeal2d_vv                                                           */
/*----------------------------------------------------------------------------*/
/*
VDEAL2D
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cint4 __OVBIF __vdeal2d_vv(__cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cint8 __OVBIF __vdeal2d_vv(__cint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cfloat4 __OVBIF __vdeal2d_vv(__cfloat4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cfloat8 __OVBIF __vdeal2d_vv(__cfloat8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __OVBIF __vdeal2d_vv(__long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __vdeal2d_vv(__long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __OVBIF __vdeal2d_vv(__ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __vdeal2d_vv(__ulong8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__double4 __OVBIF __vdeal2d_vv(__double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__double8 __OVBIF __vdeal2d_vv(__double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdeal2h_vv                                                           */
/*----------------------------------------------------------------------------*/
/*
VDEAL2H
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cchar16 __OVBIF __vdeal2h_vv(__cchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cchar32 __OVBIF __vdeal2h_vv(__cchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __OVBIF __vdeal2h_vv(__short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __vdeal2h_vv(__short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __OVBIF __vdeal2h_vv(__ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __vdeal2h_vv(__ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdeal2w_vv                                                           */
/*----------------------------------------------------------------------------*/
/*
VDEAL2W
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cshort8 __OVBIF __vdeal2w_vv(__cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cshort16 __OVBIF __vdeal2w_vv(__cshort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __OVBIF __vdeal2w_vv(__int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __vdeal2w_vv(__int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __OVBIF __vdeal2w_vv(__uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __vdeal2w_vv(__uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__float8 __OVBIF __vdeal2w_vv(__float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__float16 __OVBIF __vdeal2w_vv(__float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdeal4b_vv                                                           */
/*----------------------------------------------------------------------------*/
/*
VDEAL4B
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __OVBIF __vdeal4b_vv(__char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __vdeal4b_vv(__char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __OVBIF __vdeal4b_vv(__uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __vdeal4b_vv(__uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdeal4h_vv                                                           */
/*----------------------------------------------------------------------------*/
/*
VDEAL4H
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cchar16 __OVBIF __vdeal4h_vv(__cchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cchar32 __OVBIF __vdeal4h_vv(__cchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __OVBIF __vdeal4h_vv(__short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __vdeal4h_vv(__short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __OVBIF __vdeal4h_vv(__ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __vdeal4h_vv(__ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdotp2hd_vvw                                                         */
/*----------------------------------------------------------------------------*/
/*

VDOTP2HD
#if __C7X_VEC_SIZE_BITS__ == 256
void __vdotp2hd_vvw(short16, short16, long4&, long4&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
void __vdotp2hd_vvw(short32, short32, long8&, long8&);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __vdotp2hw_vvv                                                         */
/*----------------------------------------------------------------------------*/
/*
VDOTP2HW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __BIF __vdotp2hw_vvv(__short16, __short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __BIF __vdotp2hw_vvv(__short32, __short32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdotp2nwd_vvv                                                        */
/*----------------------------------------------------------------------------*/
/*
VDOTP2NWD
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __BIF __vdotp2nwd_vvv(__int8, __int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __BIF __vdotp2nwd_vvv(__int16, __int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdotp2nxwd_vvv                                                       */
/*----------------------------------------------------------------------------*/
/*
VDOTP2NXWD
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __BIF __vdotp2nxwd_vvv(__int8, __int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __BIF __vdotp2nxwd_vvv(__int16, __int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdotp2subh_vvv                                                       */
/*----------------------------------------------------------------------------*/
/*
VDOTP2SUBH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __BIF __vdotp2subh_vvv(__char32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __BIF __vdotp2subh_vvv(__char64, __uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdotp2suhd_vvw                                                       */
/*----------------------------------------------------------------------------*/
/*

VDOTP2SUHD
#if __C7X_VEC_SIZE_BITS__ == 256
void __vdotp2suhd_vvw(short16, ushort16, long4&, long4&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
void __vdotp2suhd_vvw(short32, ushort32, long8&, long8&);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __vdotp2suhw_vvv                                                       */
/*----------------------------------------------------------------------------*/
/*
VDOTP2SUHW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __BIF __vdotp2suhw_vvv(__short16, __ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __BIF __vdotp2suhw_vvv(__short32, __ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdotp2ubh_vvv                                                        */
/*----------------------------------------------------------------------------*/
/*
VDOTP2UBH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __BIF __vdotp2ubh_vvv(__uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __BIF __vdotp2ubh_vvv(__uchar64, __uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdotp2uhd_vvw                                                        */
/*----------------------------------------------------------------------------*/
/*

VDOTP2UHD
#if __C7X_VEC_SIZE_BITS__ == 256
void __vdotp2uhd_vvw(ushort16, ushort16, ulong4&, ulong4&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
void __vdotp2uhd_vvw(ushort32, ushort32, ulong8&, ulong8&);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __vdotp2uhw_vvv                                                        */
/*----------------------------------------------------------------------------*/
/*
VDOTP2UHW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __BIF __vdotp2uhw_vvv(__ushort16, __ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __BIF __vdotp2uhw_vvv(__ushort32, __ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdotp2wd_vvv                                                         */
/*----------------------------------------------------------------------------*/
/*
VDOTP2WD
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __BIF __vdotp2wd_vvv(__int8, __int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __BIF __vdotp2wd_vvv(__int16, __int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdotp2xwd_vvv                                                        */
/*----------------------------------------------------------------------------*/
/*
VDOTP2XWD
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __BIF __vdotp2xwd_vvv(__int8, __int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __BIF __vdotp2xwd_vvv(__int16, __int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdotp4hd_vvv                                                         */
/*----------------------------------------------------------------------------*/
/*
VDOTP4HD
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __BIF __vdotp4hd_vvv(__short16, __short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __BIF __vdotp4hd_vvv(__short32, __short32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdotp4hw_wwv                                                         */
/*----------------------------------------------------------------------------*/
/*
VDOTP4HW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __BIF __vdotp4hw_wwv(__short16, __short16, __short16, __short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __BIF __vdotp4hw_wwv(__short32, __short32, __short32, __short32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdotp4subw_vvv                                                       */
/*----------------------------------------------------------------------------*/
/*
VDOTP4SUBW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __BIF __vdotp4subw_vvv(__char32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __BIF __vdotp4subw_vvv(__char64, __uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdotp4suhd_vvv                                                       */
/*----------------------------------------------------------------------------*/
/*
VDOTP4SUHD
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __BIF __vdotp4suhd_vvv(__short16, __ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __BIF __vdotp4suhd_vvv(__short32, __ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdotp4suhw_wwv                                                       */
/*----------------------------------------------------------------------------*/
/*
VDOTP4SUHW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __BIF __vdotp4suhw_wwv(__short16, __short16, __ushort16, __ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __BIF __vdotp4suhw_wwv(__short32, __short32, __ushort32, __ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdotp4ubw_vvv                                                        */
/*----------------------------------------------------------------------------*/
/*
VDOTP4UBW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __BIF __vdotp4ubw_vvv(__uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __BIF __vdotp4ubw_vvv(__uchar64, __uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdotp4uhd_vvv                                                        */
/*----------------------------------------------------------------------------*/
/*
VDOTP4UHD
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __BIF __vdotp4uhd_vvv(__ushort16, __ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __BIF __vdotp4uhd_vvv(__ushort32, __ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdotp8subw_vvv                                                       */
/*----------------------------------------------------------------------------*/
/*
VDOTP8SUBW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __BIF __vdotp8subw_vvv(__char32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __BIF __vdotp8subw_vvv(__char64, __uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdotpmpn16b32h_yvvv                                                  */
/*----------------------------------------------------------------------------*/
/*
VDOTPMPN16B32H
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __BIF __vdotpmpn16b32h_yvvv(__ushort32, __ushort32, __char16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdotpmpn16h16w_yvvv                                                  */
/*----------------------------------------------------------------------------*/
/*
VDOTPMPN16H16W
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __BIF __vdotpmpn16h16w_yvvv(__ushort32, __ushort16, __short16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdotpmpn16w8d_yvvv                                                   */
/*----------------------------------------------------------------------------*/
/*
VDOTPMPN16W8D
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __BIF __vdotpmpn16w8d_yvvv(__ushort32, __ushort8, __int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdotpmpn32b16h_yvvv                                                  */
/*----------------------------------------------------------------------------*/
/*
VDOTPMPN32B16H
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__short16 __BIF __vdotpmpn32b16h_yvvv(__uint16, __uint16, __char32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdotpmpn32b16w_yvvv                                                  */
/*----------------------------------------------------------------------------*/
/*
VDOTPMPN32B16W
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __BIF __vdotpmpn32b16w_yvvv(__uint16, __uint16, __char32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdotpmpn32h8w_yvvv                                                   */
/*----------------------------------------------------------------------------*/
/*
VDOTPMPN32H8W
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__int8 __BIF __vdotpmpn32h8w_yvvv(__uint8, __uint8, __short32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdotpmpnu16h16w_yvvv                                                 */
/*----------------------------------------------------------------------------*/
/*
VDOTPMPNU16H16W
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __BIF __vdotpmpnu16h16w_yvvv(__ushort32, __ushort16, __ushort16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdotpmpnu16w8d_yvvv                                                  */
/*----------------------------------------------------------------------------*/
/*
VDOTPMPNU16W8D
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __BIF __vdotpmpnu16w8d_yvvv(__ushort32, __ushort8, __uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdotpmpnu32b16h_yvvv                                                 */
/*----------------------------------------------------------------------------*/
/*
VDOTPMPNU32B16H
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort16 __BIF __vdotpmpnu32b16h_yvvv(__uint16, __uint16, __uchar32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdotpmpnu32b16w_yvvv                                                 */
/*----------------------------------------------------------------------------*/
/*
VDOTPMPNU32B16W
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __BIF __vdotpmpnu32b16w_yvvv(__uint16, __uint16, __uchar32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdotpmpnu32h8w_yvvv                                                  */
/*----------------------------------------------------------------------------*/
/*
VDOTPMPNU32H8W
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__uint8 __BIF __vdotpmpnu32h8w_yvvv(__uint8, __uint8, __ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdpackh_vvv                                                          */
/*----------------------------------------------------------------------------*/
/*
VDPACKH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cint4 __OVBIF __vdpackh_vvv(__cint4, __cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cint8 __OVBIF __vdpackh_vvv(__cint8, __cint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cfloat4 __OVBIF __vdpackh_vvv(__cfloat4, __cfloat4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cfloat8 __OVBIF __vdpackh_vvv(__cfloat8, __cfloat8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __OVBIF __vdpackh_vvv(__long4, __long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __vdpackh_vvv(__long8, __long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __OVBIF __vdpackh_vvv(__ulong4, __ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __vdpackh_vvv(__ulong8, __ulong8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__double4 __OVBIF __vdpackh_vvv(__double4, __double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__double8 __OVBIF __vdpackh_vvv(__double8, __double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdpackl_vvv                                                          */
/*----------------------------------------------------------------------------*/
/*
VDPACKL
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cint4 __OVBIF __vdpackl_vvv(__cint4, __cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cint8 __OVBIF __vdpackl_vvv(__cint8, __cint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cfloat4 __OVBIF __vdpackl_vvv(__cfloat4, __cfloat4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cfloat8 __OVBIF __vdpackl_vvv(__cfloat8, __cfloat8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __OVBIF __vdpackl_vvv(__long4, __long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __vdpackl_vvv(__long8, __long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __OVBIF __vdpackl_vvv(__ulong4, __ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __vdpackl_vvv(__ulong8, __ulong8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__double4 __OVBIF __vdpackl_vvv(__double4, __double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__double8 __OVBIF __vdpackl_vvv(__double8, __double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdpint_vv                                                            */
/*----------------------------------------------------------------------------*/
/*
VDPINT
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __BIF __vdpint_vv(__double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __BIF __vdpint_vv(__double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdpsp_vv                                                             */
/*----------------------------------------------------------------------------*/
/*
VDPSP
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__float8 __BIF __vdpsp_vv(__double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__float16 __BIF __vdpsp_vv(__double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdptrunc_vv                                                          */
/*----------------------------------------------------------------------------*/
/*
VDPTRUNC
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __BIF __vdptrunc_vv(__double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __BIF __vdptrunc_vv(__double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdsad16ou8h8w_vvv                                                    */
/*----------------------------------------------------------------------------*/
/*
VDSAD16OU8H8W
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __BIF __vdsad16ou8h8w_vvv(__ushort32, __ushort16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdsad8ou16b16h_vvv                                                   */
/*----------------------------------------------------------------------------*/
/*
VDSAD8OU16B16H
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __BIF __vdsad8ou16b16h_vvv(__uchar64, __uchar32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdsadm16ou8h8w_yvvv                                                  */
/*----------------------------------------------------------------------------*/
/*
VDSADM16OU8H8W
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __BIF __vdsadm16ou8h8w_yvvv(__uchar64, __ushort32, __ushort16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdsadm8ou16b16h_yvvv                                                 */
/*----------------------------------------------------------------------------*/
/*
VDSADM8OU16B16H
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __BIF __vdsadm8ou16b16h_yvvv(__uchar64, __uchar64, __uchar32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdsortddh_vv                                                         */
/*----------------------------------------------------------------------------*/
/*
VDSORTDDH
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __BIF __vdsortddh_vv(__short32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdsortdduh_vv                                                        */
/*----------------------------------------------------------------------------*/
/*
VDSORTDDUH
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __BIF __vdsortdduh_vv(__ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdsortdih_vv                                                         */
/*----------------------------------------------------------------------------*/
/*
VDSORTDIH
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __BIF __vdsortdih_vv(__short32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdsortdiuh_vv                                                        */
/*----------------------------------------------------------------------------*/
/*
VDSORTDIUH
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __BIF __vdsortdiuh_vv(__ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdsortidh_vv                                                         */
/*----------------------------------------------------------------------------*/
/*
VDSORTIDH
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __BIF __vdsortidh_vv(__short32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdsortiduh_vv                                                        */
/*----------------------------------------------------------------------------*/
/*
VDSORTIDUH
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __BIF __vdsortiduh_vv(__ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdsortiih_vv                                                         */
/*----------------------------------------------------------------------------*/
/*
VDSORTIIH
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __BIF __vdsortiih_vv(__short32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdsortiiuh_vv                                                        */
/*----------------------------------------------------------------------------*/
/*
VDSORTIIUH
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __BIF __vdsortiiuh_vv(__ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdsortpddh_vv                                                        */
/*----------------------------------------------------------------------------*/
/*
VDSORTPDDH
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __vdsortpddh_vv(__short32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdsortpdduh_vv                                                       */
/*----------------------------------------------------------------------------*/
/*
VDSORTPDDUH
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __vdsortpdduh_vv(__ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdsortpdih_vv                                                        */
/*----------------------------------------------------------------------------*/
/*
VDSORTPDIH
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __vdsortpdih_vv(__short32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdsortpdiuh_vv                                                       */
/*----------------------------------------------------------------------------*/
/*
VDSORTPDIUH
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __vdsortpdiuh_vv(__ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdsortpidh_vv                                                        */
/*----------------------------------------------------------------------------*/
/*
VDSORTPIDH
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __vdsortpidh_vv(__short32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdsortpiduh_vv                                                       */
/*----------------------------------------------------------------------------*/
/*
VDSORTPIDUH
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __vdsortpiduh_vv(__ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdsortpiih_vv                                                        */
/*----------------------------------------------------------------------------*/
/*
VDSORTPIIH
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __vdsortpiih_vv(__short32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdsortpiiuh_vv                                                       */
/*----------------------------------------------------------------------------*/
/*
VDSORTPIIUH
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __vdsortpiiuh_vv(__ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdup16b_vv                                                           */
/*----------------------------------------------------------------------------*/
/*
VDUP16B
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __OVBIF __vdup16b_vv(__char2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __vdup16b_vv(__char4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __OVBIF __vdup16b_vv(__uchar2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __vdup16b_vv(__uchar4);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdup16h_vv                                                           */
/*----------------------------------------------------------------------------*/
/*
VDUP16H
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cchar16 __OVBIF __vdup16h_vv(__cchar);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cchar32 __OVBIF __vdup16h_vv(__cchar2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __OVBIF __vdup16h_vv(short);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __vdup16h_vv(__short2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __OVBIF __vdup16h_vv(__ushort);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __vdup16h_vv(__ushort2);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdup2b_vv                                                            */
/*----------------------------------------------------------------------------*/
/*
VDUP2B
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __OVBIF __vdup2b_vv(__char16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __vdup2b_vv(__char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __OVBIF __vdup2b_vv(__uchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __vdup2b_vv(__uchar32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdup2d_vv                                                            */
/*----------------------------------------------------------------------------*/
/*
VDUP2D
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cint4 __OVBIF __vdup2d_vv(__cint2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cint8 __OVBIF __vdup2d_vv(__cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cfloat4 __OVBIF __vdup2d_vv(__cfloat2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cfloat8 __OVBIF __vdup2d_vv(__cfloat4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __OVBIF __vdup2d_vv(__long2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __vdup2d_vv(__long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __OVBIF __vdup2d_vv(__ulong2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __vdup2d_vv(__ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__double4 __OVBIF __vdup2d_vv(__double2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__double8 __OVBIF __vdup2d_vv(__double4);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdup2h_vv                                                            */
/*----------------------------------------------------------------------------*/
/*
VDUP2H
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cchar16 __OVBIF __vdup2h_vv(__cchar8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cchar32 __OVBIF __vdup2h_vv(__cchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __OVBIF __vdup2h_vv(__short8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __vdup2h_vv(__short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __OVBIF __vdup2h_vv(__ushort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __vdup2h_vv(__ushort16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdup2w_vv                                                            */
/*----------------------------------------------------------------------------*/
/*
VDUP2W
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cshort8 __OVBIF __vdup2w_vv(__cshort4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cshort16 __OVBIF __vdup2w_vv(__cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __OVBIF __vdup2w_vv(__int4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __vdup2w_vv(__int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __OVBIF __vdup2w_vv(__uint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __vdup2w_vv(__uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__float8 __OVBIF __vdup2w_vv(__float4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__float16 __OVBIF __vdup2w_vv(__float8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdup32b_vv                                                           */
/*----------------------------------------------------------------------------*/
/*
VDUP32B
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __OVBIF __vdup32b_vv(signed char);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __vdup32b_vv(__char2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __OVBIF __vdup32b_vv(__uchar);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __vdup32b_vv(__uchar2);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdup4b_vv                                                            */
/*----------------------------------------------------------------------------*/
/*
VDUP4B
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __OVBIF __vdup4b_vv(__char8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __vdup4b_vv(__char16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __OVBIF __vdup4b_vv(__uchar8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __vdup4b_vv(__uchar16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdup4d_vv                                                            */
/*----------------------------------------------------------------------------*/
/*
VDUP4D
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cint4 __OVBIF __vdup4d_vv(__cint);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cint8 __OVBIF __vdup4d_vv(__cint2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cfloat4 __OVBIF __vdup4d_vv(__cfloat);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cfloat8 __OVBIF __vdup4d_vv(__cfloat2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __OVBIF __vdup4d_vv(long);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __vdup4d_vv(__long2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __OVBIF __vdup4d_vv(__ulong);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __vdup4d_vv(__ulong2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__double4 __OVBIF __vdup4d_vv(double);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__double8 __OVBIF __vdup4d_vv(__double2);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdup4h_vv                                                            */
/*----------------------------------------------------------------------------*/
/*
VDUP4H
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cchar16 __OVBIF __vdup4h_vv(__cchar4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cchar32 __OVBIF __vdup4h_vv(__cchar8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __OVBIF __vdup4h_vv(__short4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __vdup4h_vv(__short8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __OVBIF __vdup4h_vv(__ushort4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __vdup4h_vv(__ushort8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdup4w_vv                                                            */
/*----------------------------------------------------------------------------*/
/*
VDUP4W
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cshort8 __OVBIF __vdup4w_vv(__cshort2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cshort16 __OVBIF __vdup4w_vv(__cshort4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __OVBIF __vdup4w_vv(__int2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __vdup4w_vv(__int4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __OVBIF __vdup4w_vv(__uint2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __vdup4w_vv(__uint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__float8 __OVBIF __vdup4w_vv(__float2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__float16 __OVBIF __vdup4w_vv(__float4);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdup8b_vv                                                            */
/*----------------------------------------------------------------------------*/
/*
VDUP8B
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __OVBIF __vdup8b_vv(__char4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __vdup8b_vv(__char8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __OVBIF __vdup8b_vv(__uchar4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __vdup8b_vv(__uchar8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdup8h_vv                                                            */
/*----------------------------------------------------------------------------*/
/*
VDUP8H
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cchar16 __OVBIF __vdup8h_vv(__cchar2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cchar32 __OVBIF __vdup8h_vv(__cchar4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __OVBIF __vdup8h_vv(__short2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __vdup8h_vv(__short4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __OVBIF __vdup8h_vv(__ushort2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __vdup8h_vv(__ushort4);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdup8w_vv                                                            */
/*----------------------------------------------------------------------------*/
/*
VDUP8W
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cshort8 __OVBIF __vdup8w_vv(__cshort);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cshort16 __OVBIF __vdup8w_vv(__cshort2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __OVBIF __vdup8w_vv(int);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __vdup8w_vv(__int2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __OVBIF __vdup8w_vv(__uint);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __vdup8w_vv(__uint2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__float8 __OVBIF __vdup8w_vv(float);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__float16 __OVBIF __vdup8w_vv(__float2);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdupb_kv                                                             */
/*----------------------------------------------------------------------------*/
/*
VDUPB
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __vdupb_kv(signed char __CST(-128, 127));
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __OVBIF __vdupb_kv(signed char __CST(-128, 127));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __vdupb_kv(__uchar __CST(0, 255));
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __OVBIF __vdupb_kv(__uchar __CST(0, 255));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdupb_rv                                                             */
/*----------------------------------------------------------------------------*/
/*
VDUPB
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __vdupb_rv(signed char);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __OVBIF __vdupb_rv(signed char);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __vdupb_rv(__uchar);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __OVBIF __vdupb_rv(__uchar);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdupd_dv                                                             */
/*----------------------------------------------------------------------------*/
/*
VDUPD
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__cint8 __OVBIF __vdupd_dv(__cint);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cint4 __OVBIF __vdupd_dv(__cint);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cfloat8 __OVBIF __vdupd_dv(__cfloat);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cfloat4 __OVBIF __vdupd_dv(__cfloat);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __vdupd_dv(long);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __OVBIF __vdupd_dv(long);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __vdupd_dv(__ulong);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __OVBIF __vdupd_dv(__ulong);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__double8 __OVBIF __vdupd_dv(double);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__double4 __OVBIF __vdupd_dv(double);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vduph_kv                                                             */
/*----------------------------------------------------------------------------*/
/*
VDUPH
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __vduph_kv(short __CST(-32768, 32767));
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __OVBIF __vduph_kv(short __CST(-32768, 32767));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __vduph_kv(__ushort __CST(0, 65535));
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __OVBIF __vduph_kv(__ushort __CST(0, 65535));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vduph_rv                                                             */
/*----------------------------------------------------------------------------*/
/*
VDUPH
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__cchar32 __OVBIF __vduph_rv(__cchar);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cchar16 __OVBIF __vduph_rv(__cchar);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __vduph_rv(short);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __OVBIF __vduph_rv(short);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __vduph_rv(__ushort);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __OVBIF __vduph_rv(__ushort);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdupw_kv                                                             */
/*----------------------------------------------------------------------------*/
/*
VDUPW
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __vdupw_kv(int __CST(-2147483648, 2147483647));
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __OVBIF __vdupw_kv(int __CST(-2147483648, 2147483647));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __vdupw_kv(__uint __CST(0, 4294967295));
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __OVBIF __vdupw_kv(__uint __CST(0, 4294967295));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__float16 __OVBIF __vdupw_kv(float k);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__float8 __OVBIF __vdupw_kv(float k);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdupw_rv                                                             */
/*----------------------------------------------------------------------------*/
/*
VDUPW
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__cshort16 __OVBIF __vdupw_rv(__cshort);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cshort8 __OVBIF __vdupw_rv(__cshort);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __vdupw_rv(int);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __OVBIF __vdupw_rv(int);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __vdupw_rv(__uint);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __OVBIF __vdupw_rv(__uint);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__float16 __OVBIF __vdupw_rv(float);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__float8 __OVBIF __vdupw_rv(float);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vgatherb_pvv                                                         */
/*----------------------------------------------------------------------------*/
/*
VGATHERB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __BIF __vgatherb_pvv(__vpred, __char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __BIF __vgatherb_pvv(__vpred, __char64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vgathernb_pvv                                                        */
/*----------------------------------------------------------------------------*/
/*
VGATHERNB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __BIF __vgathernb_pvv(__vpred, __char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __BIF __vgathernb_pvv(__vpred, __char64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vgetb_vkd                                                            */
/*----------------------------------------------------------------------------*/
/*
VGETB
*/
#if __C7X_VEC_SIZE_BITS__ == 512
signed char __BIF __vgetb_vkd(__char64, __uint __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
signed char __BIF __vgetb_vkd(__char32, __uint __CST(0, 63));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vgetb_vrd                                                            */
/*----------------------------------------------------------------------------*/
/*
VGETB
*/
#if __C7X_VEC_SIZE_BITS__ == 512
signed char __BIF __vgetb_vrd(__char64, __uint);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
signed char __BIF __vgetb_vrd(__char32, __uint);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vgetb_ykd                                                            */
/*----------------------------------------------------------------------------*/
/*
VGETB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
signed char __BIF __vgetb_ykd(__char32, __uint __CST(0, 63));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vgetd_vkd                                                            */
/*----------------------------------------------------------------------------*/
/*
VGETD
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__cint __OVBIF __vgetd_vkd(__cint8, __uint __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cint __OVBIF __vgetd_vkd(__cint4, __uint __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cfloat __OVBIF __vgetd_vkd(__cfloat8, __uint __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cfloat __OVBIF __vgetd_vkd(__cfloat4, __uint __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
long __OVBIF __vgetd_vkd(__long8, __uint __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
long __OVBIF __vgetd_vkd(__long4, __uint __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong __OVBIF __vgetd_vkd(__ulong8, __uint __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong __OVBIF __vgetd_vkd(__ulong4, __uint __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
double __OVBIF __vgetd_vkd(__double8, __uint __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
double __OVBIF __vgetd_vkd(__double4, __uint __CST(0, 63));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vgetd_vrd                                                            */
/*----------------------------------------------------------------------------*/
/*
VGETD
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__cint __OVBIF __vgetd_vrd(__cint8, __uint);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cint __OVBIF __vgetd_vrd(__cint4, __uint);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cfloat __OVBIF __vgetd_vrd(__cfloat8, __uint);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cfloat __OVBIF __vgetd_vrd(__cfloat4, __uint);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
long __OVBIF __vgetd_vrd(__long8, __uint);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
long __OVBIF __vgetd_vrd(__long4, __uint);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong __OVBIF __vgetd_vrd(__ulong8, __uint);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong __OVBIF __vgetd_vrd(__ulong4, __uint);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
double __OVBIF __vgetd_vrd(__double8, __uint);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
double __OVBIF __vgetd_vrd(__double4, __uint);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vgetd_ykd                                                            */
/*----------------------------------------------------------------------------*/
/*
VGETD
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cint __OVBIF __vgetd_ykd(__cint4, __uint __CST(0, 63));
__cfloat __OVBIF __vgetd_ykd(__cfloat4, __uint __CST(0, 63));
long __OVBIF __vgetd_ykd(__long4, __uint __CST(0, 63));
__ulong __OVBIF __vgetd_ykd(__ulong4, __uint __CST(0, 63));
double __OVBIF __vgetd_ykd(__double4, __uint __CST(0, 63));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vgetdupb_vrv                                                         */
/*----------------------------------------------------------------------------*/
/*
VGETDUPB
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __vgetdupb_vrv(__char64, int);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __OVBIF __vgetdupb_vrv(__char32, int);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __vgetdupb_vrv(__uchar64, __uint);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __OVBIF __vgetdupb_vrv(__uchar32, __uint);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vgetdupd_vrv                                                         */
/*----------------------------------------------------------------------------*/
/*
VGETDUPD
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __vgetdupd_vrv(__long8, int);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __OVBIF __vgetdupd_vrv(__long4, int);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __vgetdupd_vrv(__ulong8, __uint);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __OVBIF __vgetdupd_vrv(__ulong4, __uint);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vgetduph_vrv                                                         */
/*----------------------------------------------------------------------------*/
/*
VGETDUPH
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __vgetduph_vrv(__short32, int);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __OVBIF __vgetduph_vrv(__short16, int);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __vgetduph_vrv(__ushort32, __uint);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __OVBIF __vgetduph_vrv(__ushort16, __uint);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vgetdupw_vrv                                                         */
/*----------------------------------------------------------------------------*/
/*
VGETDUPW
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __vgetdupw_vrv(__int16, int);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __OVBIF __vgetdupw_vrv(__int8, int);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __vgetdupw_vrv(__uint16, __uint);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __OVBIF __vgetdupw_vrv(__uint8, __uint);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vgeth_vkd                                                            */
/*----------------------------------------------------------------------------*/
/*
VGETH
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__cchar __OVBIF __vgeth_vkd(__cchar32, __uint __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cchar __OVBIF __vgeth_vkd(__cchar16, __uint __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
short __OVBIF __vgeth_vkd(__short32, __uint __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
short __OVBIF __vgeth_vkd(__short16, __uint __CST(0, 63));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vgeth_vrd                                                            */
/*----------------------------------------------------------------------------*/
/*
VGETH
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__cchar __OVBIF __vgeth_vrd(__cchar32, __uint);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cchar __OVBIF __vgeth_vrd(__cchar16, __uint);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
short __OVBIF __vgeth_vrd(__short32, __uint);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
short __OVBIF __vgeth_vrd(__short16, __uint);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vgeth_ykd                                                            */
/*----------------------------------------------------------------------------*/
/*
VGETH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cchar __OVBIF __vgeth_ykd(__cchar16, __uint __CST(0, 63));
short __OVBIF __vgeth_ykd(__short16, __uint __CST(0, 63));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vgetub_vkd                                                           */
/*----------------------------------------------------------------------------*/
/*
VGETUB
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar __BIF __vgetub_vkd(__uchar64, __uint __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar __BIF __vgetub_vkd(__uchar32, __uint __CST(0, 63));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vgetub_vrd                                                           */
/*----------------------------------------------------------------------------*/
/*
VGETUB
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar __BIF __vgetub_vrd(__uchar64, __uint);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar __BIF __vgetub_vrd(__uchar32, __uint);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vgetub_ykd                                                           */
/*----------------------------------------------------------------------------*/
/*
VGETUB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar __BIF __vgetub_ykd(__uchar32, __uint __CST(0, 63));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vgetuh_vkd                                                           */
/*----------------------------------------------------------------------------*/
/*
VGETUH
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort __BIF __vgetuh_vkd(__ushort32, __uint __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort __BIF __vgetuh_vkd(__ushort16, __uint __CST(0, 63));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vgetuh_vrd                                                           */
/*----------------------------------------------------------------------------*/
/*
VGETUH
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort __BIF __vgetuh_vrd(__ushort32, __uint);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort __BIF __vgetuh_vrd(__ushort16, __uint);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vgetuh_ykd                                                           */
/*----------------------------------------------------------------------------*/
/*
VGETUH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort __BIF __vgetuh_ykd(__ushort16, __uint __CST(0, 63));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vgetuw_vkd                                                           */
/*----------------------------------------------------------------------------*/
/*
VGETUW
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__uint __OVBIF __vgetuw_vkd(__uint16, __uint __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uint __OVBIF __vgetuw_vkd(__uint8, __uint __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
float __OVBIF __vgetuw_vkd(__float16, __uint __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
float __OVBIF __vgetuw_vkd(__float8, __uint __CST(0, 63));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vgetuw_vrd                                                           */
/*----------------------------------------------------------------------------*/
/*
VGETUW
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__uint __OVBIF __vgetuw_vrd(__uint16, __uint);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uint __OVBIF __vgetuw_vrd(__uint8, __uint);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
float __OVBIF __vgetuw_vrd(__float16, __uint);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
float __OVBIF __vgetuw_vrd(__float8, __uint);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vgetuw_ykd                                                           */
/*----------------------------------------------------------------------------*/
/*
VGETUW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uint __OVBIF __vgetuw_ykd(__uint8, __uint __CST(0, 63));
float __OVBIF __vgetuw_ykd(__float8, __uint __CST(0, 63));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vgetw_vkd                                                            */
/*----------------------------------------------------------------------------*/
/*
VGETW
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__cshort __OVBIF __vgetw_vkd(__cshort16, __uint __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cshort __OVBIF __vgetw_vkd(__cshort8, __uint __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
int __OVBIF __vgetw_vkd(__int16, __uint __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
int __OVBIF __vgetw_vkd(__int8, __uint __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
float __OVBIF __vgetw_vkd(__float16, __uint __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
float __OVBIF __vgetw_vkd(__float8, __uint __CST(0, 63));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vgetw_vrd                                                            */
/*----------------------------------------------------------------------------*/
/*
VGETW
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__cshort __OVBIF __vgetw_vrd(__cshort16, __uint);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cshort __OVBIF __vgetw_vrd(__cshort8, __uint);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
int __OVBIF __vgetw_vrd(__int16, __uint);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
int __OVBIF __vgetw_vrd(__int8, __uint);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
float __OVBIF __vgetw_vrd(__float16, __uint);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
float __OVBIF __vgetw_vrd(__float8, __uint);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vgetw_ykd                                                            */
/*----------------------------------------------------------------------------*/
/*
VGETW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cshort __OVBIF __vgetw_ykd(__cshort8, __uint __CST(0, 63));
int __OVBIF __vgetw_ykd(__int8, __uint __CST(0, 63));
float __OVBIF __vgetw_ykd(__float8, __uint __CST(0, 63));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vgmpyb_vvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VGMPYB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __BIF __vgmpyb_vvv(__uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __vgmpyb_vvv(__uchar64, __uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vgmpyw_vvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VGMPYW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __BIF __vgmpyw_vvv(__uint8, __uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __BIF __vgmpyw_vvv(__uint16, __uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vgsatd_vkv                                                           */
/*----------------------------------------------------------------------------*/
/*
VGSATD
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __BIF __vgsatd_vkv(__long4, __uchar4 __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __BIF __vgsatd_vkv(__long8, __uchar8 __CST(0, 63));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vgsath_vkv                                                           */
/*----------------------------------------------------------------------------*/
/*
VGSATH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __BIF __vgsath_vkv(__short16, __uchar16 __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __BIF __vgsath_vkv(__short32, __uchar32 __CST(0, 63));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vgsatsud_vkv                                                         */
/*----------------------------------------------------------------------------*/
/*
VGSATSUD
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __BIF __vgsatsud_vkv(__long4, __uchar4 __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __BIF __vgsatsud_vkv(__long8, __uchar8 __CST(0, 63));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vgsatsuh_vkv                                                         */
/*----------------------------------------------------------------------------*/
/*
VGSATSUH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __BIF __vgsatsuh_vkv(__short16, __uchar16 __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __BIF __vgsatsuh_vkv(__short32, __uchar32 __CST(0, 63));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vgsatsuw_vkv                                                         */
/*----------------------------------------------------------------------------*/
/*
VGSATSUW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __BIF __vgsatsuw_vkv(__int8, __uchar8 __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __BIF __vgsatsuw_vkv(__int16, __uchar16 __CST(0, 63));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vgsatud_vkv                                                          */
/*----------------------------------------------------------------------------*/
/*
VGSATUD
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __BIF __vgsatud_vkv(__ulong4, __uchar4 __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __BIF __vgsatud_vkv(__ulong8, __uchar8 __CST(0, 63));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vgsatuh_vkv                                                          */
/*----------------------------------------------------------------------------*/
/*
VGSATUH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __BIF __vgsatuh_vkv(__ushort16, __uchar16 __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __BIF __vgsatuh_vkv(__ushort32, __uchar32 __CST(0, 63));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vgsatuw_vkv                                                          */
/*----------------------------------------------------------------------------*/
/*
VGSATUW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __BIF __vgsatuw_vkv(__uint8, __uchar8 __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __BIF __vgsatuw_vkv(__uint16, __uchar16 __CST(0, 63));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vgsatw_vkv                                                           */
/*----------------------------------------------------------------------------*/
/*
VGSATW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __BIF __vgsatw_vkv(__int8, __uchar8 __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __BIF __vgsatw_vkv(__int16, __uchar16 __CST(0, 63));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vhaddb1d_vd                                                          */
/*----------------------------------------------------------------------------*/
/*
VHADDB1D
*/
#if __C7X_VEC_SIZE_BITS__ == 512
long __BIF __vhaddb1d_vd(__char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
long __BIF __vhaddb1d_vd(__char32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vhaddd1d_vd                                                          */
/*----------------------------------------------------------------------------*/
/*
VHADDD1D
*/
#if __C7X_VEC_SIZE_BITS__ == 512
long __BIF __vhaddd1d_vd(__long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
long __BIF __vhaddd1d_vd(__long4);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vhaddeoh2w_vd                                                        */
/*----------------------------------------------------------------------------*/
/*
VHADDEOH2W
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__int2 __OVBIF __vhaddeoh2w_vd(__short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__int2 __OVBIF __vhaddeoh2w_vd(__short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cint __OVBIF __vhaddeoh2w_vd(__cshort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cint __OVBIF __vhaddeoh2w_vd(__cshort8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vhaddeow2d_vv                                                        */
/*----------------------------------------------------------------------------*/
/*
VHADDEOW2D
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__long2 __OVBIF __vhaddeow2d_vv(__int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__long2 __OVBIF __vhaddeow2d_vv(__int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__clong __OVBIF __vhaddeow2d_vv(__cint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__clong __OVBIF __vhaddeow2d_vv(__cint4);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vhaddeow4d_vvv                                                       */
/*----------------------------------------------------------------------------*/
/*
VHADDEOW4D
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__long4 __OVBIF __vhaddeow4d_vvv(__int16, __int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __OVBIF __vhaddeow4d_vvv(__int8, __int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__clong2 __OVBIF __vhaddeow4d_vvv(__cint8, __cint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__clong2 __OVBIF __vhaddeow4d_vvv(__cint4, __cint4);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vhaddh1d_vd                                                          */
/*----------------------------------------------------------------------------*/
/*
VHADDH1D
*/
#if __C7X_VEC_SIZE_BITS__ == 512
long __BIF __vhaddh1d_vd(__short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
long __BIF __vhaddh1d_vd(__short16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vhaddub1d_vd                                                         */
/*----------------------------------------------------------------------------*/
/*
VHADDUB1D
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong __BIF __vhaddub1d_vd(__uchar64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong __BIF __vhaddub1d_vd(__uchar32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vhaddud1d_vd                                                         */
/*----------------------------------------------------------------------------*/
/*
VHADDUD1D
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong __BIF __vhaddud1d_vd(__ulong8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong __BIF __vhaddud1d_vd(__ulong4);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vhaddueoh2w_vd                                                       */
/*----------------------------------------------------------------------------*/
/*
VHADDUEOH2W
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__uint2 __BIF __vhaddueoh2w_vd(__ushort32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uint2 __BIF __vhaddueoh2w_vd(__ushort16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vhaddueow2d_vv                                                       */
/*----------------------------------------------------------------------------*/
/*
VHADDUEOW2D
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong2 __BIF __vhaddueow2d_vv(__uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong2 __BIF __vhaddueow2d_vv(__uint8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vhaddueow4d_vvv                                                      */
/*----------------------------------------------------------------------------*/
/*
VHADDUEOW4D
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong4 __BIF __vhaddueow4d_vvv(__uint16, __uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __BIF __vhaddueow4d_vvv(__uint8, __uint8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vhadduh1d_vd                                                         */
/*----------------------------------------------------------------------------*/
/*
VHADDUH1D
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong __BIF __vhadduh1d_vd(__ushort32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong __BIF __vhadduh1d_vd(__ushort16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vhadduw1d_vd                                                         */
/*----------------------------------------------------------------------------*/
/*
VHADDUW1D
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong __BIF __vhadduw1d_vd(__uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong __BIF __vhadduw1d_vd(__uint8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vhaddw1d_vd                                                          */
/*----------------------------------------------------------------------------*/
/*
VHADDW1D
*/
#if __C7X_VEC_SIZE_BITS__ == 512
long __BIF __vhaddw1d_vd(__int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
long __BIF __vhaddw1d_vd(__int8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vhhmv_vvv                                                            */
/*----------------------------------------------------------------------------*/
/*
VHHMV
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __BIF __vhhmv_vvv(__uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __vhhmv_vvv(__uchar64, __uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vhlmv_vvv                                                            */
/*----------------------------------------------------------------------------*/
/*
VHLMV
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __BIF __vhlmv_vvv(__uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __vhlmv_vvv(__uchar64, __uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vhpackh_vvv                                                          */
/*----------------------------------------------------------------------------*/
/*
VHPACKH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cchar16 __OVBIF __vhpackh_vvv(__cchar16, __cchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cchar32 __OVBIF __vhpackh_vvv(__cchar32, __cchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __OVBIF __vhpackh_vvv(__short16, __short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __vhpackh_vvv(__short32, __short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __OVBIF __vhpackh_vvv(__ushort16, __ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __vhpackh_vvv(__ushort32, __ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vhpackl_vvv                                                          */
/*----------------------------------------------------------------------------*/
/*
VHPACKL
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cchar16 __OVBIF __vhpackl_vvv(__cchar16, __cchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cchar32 __OVBIF __vhpackl_vvv(__cchar32, __cchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __OVBIF __vhpackl_vvv(__short16, __short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __vhpackl_vvv(__short32, __short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __OVBIF __vhpackl_vvv(__ushort16, __ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __vhpackl_vvv(__ushort32, __ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vhpint_vv                                                            */
/*----------------------------------------------------------------------------*/
/*
VHPINT
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __BIF __vhpint_vv(__uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __BIF __vhpint_vv(__uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vhpsp_vv                                                             */
/*----------------------------------------------------------------------------*/
/*
VHPSP
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__float8 __BIF __vhpsp_vv(__uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__float16 __BIF __vhpsp_vv(__uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vhunpkd_vv                                                           */
/*----------------------------------------------------------------------------*/
/*
VHUNPKD
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __OVBIF __vhunpkd_vv(__short4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __vhunpkd_vv(__short8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__clong2 __OVBIF __vhunpkd_vv(__cshort2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__clong4 __OVBIF __vhunpkd_vv(__cshort4);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vhunpkdu_vv                                                          */
/*----------------------------------------------------------------------------*/
/*
VHUNPKDU
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __BIF __vhunpkdu_vv(__ushort4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __BIF __vhunpkdu_vv(__ushort8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vhunpkuwh_vv                                                         */
/*----------------------------------------------------------------------------*/
/*
VHUNPKUWH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __BIF __vhunpkuwh_vv(__ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __BIF __vhunpkuwh_vv(__ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vhunpkuwl_vv                                                         */
/*----------------------------------------------------------------------------*/
/*
VHUNPKUWL
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __BIF __vhunpkuwl_vv(__ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __BIF __vhunpkuwl_vv(__ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vhunpkw_vv                                                           */
/*----------------------------------------------------------------------------*/
/*
VHUNPKW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __OVBIF __vhunpkw_vv(__short8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __vhunpkw_vv(__short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cint4 __OVBIF __vhunpkw_vv(__cshort4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cint8 __OVBIF __vhunpkw_vv(__cshort8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vhunpkwh_vv                                                          */
/*----------------------------------------------------------------------------*/
/*
VHUNPKWH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __BIF __vhunpkwh_vv(__short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __BIF __vhunpkwh_vv(__short32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vhunpkwl_vv                                                          */
/*----------------------------------------------------------------------------*/
/*
VHUNPKWL
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __BIF __vhunpkwl_vv(__short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __BIF __vhunpkwl_vv(__short32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vhunpkwu_vv                                                          */
/*----------------------------------------------------------------------------*/
/*
VHUNPKWU
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __BIF __vhunpkwu_vv(__ushort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __BIF __vhunpkwu_vv(__ushort16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vhxorb1b_vr                                                          */
/*----------------------------------------------------------------------------*/
/*
VHXORB1B
*/
#if __C7X_VEC_SIZE_BITS__ == 512
short __BIF __vhxorb1b_vr(__char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
short __BIF __vhxorb1b_vr(__char32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vhxord1d_vd                                                          */
/*----------------------------------------------------------------------------*/
/*
VHXORD1D
*/
#if __C7X_VEC_SIZE_BITS__ == 512
long __BIF __vhxord1d_vd(__long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
long __BIF __vhxord1d_vd(__long4);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vhxorh1h_vr                                                          */
/*----------------------------------------------------------------------------*/
/*
VHXORH1H
*/
#if __C7X_VEC_SIZE_BITS__ == 512
short __BIF __vhxorh1h_vr(__short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
short __BIF __vhxorh1h_vr(__short16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vhxorw1w_vr                                                          */
/*----------------------------------------------------------------------------*/
/*
VHXORW1W
*/
#if __C7X_VEC_SIZE_BITS__ == 512
int __BIF __vhxorw1w_vr(__int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
int __BIF __vhxorw1w_vr(__int8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vintdph_vv                                                           */
/*----------------------------------------------------------------------------*/
/*
VINTDPH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__double4 __BIF __vintdph_vv(__int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__double8 __BIF __vintdph_vv(__int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vintdpl_vv                                                           */
/*----------------------------------------------------------------------------*/
/*
VINTDPL
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__double4 __BIF __vintdpl_vv(__int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__double8 __BIF __vintdpl_vv(__int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vintdpuh_vv                                                          */
/*----------------------------------------------------------------------------*/
/*
VINTDPUH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__double4 __BIF __vintdpuh_vv(__uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__double8 __BIF __vintdpuh_vv(__uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vintdpul_vv                                                          */
/*----------------------------------------------------------------------------*/
/*
VINTDPUL
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__double4 __BIF __vintdpul_vv(__uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__double8 __BIF __vintdpul_vv(__uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vinthp_vv                                                            */
/*----------------------------------------------------------------------------*/
/*
VINTHP
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __BIF __vinthp_vv(__int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __BIF __vinthp_vv(__int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vinthsph_vv                                                          */
/*----------------------------------------------------------------------------*/
/*
VINTHSPH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__float8 __BIF __vinthsph_vv(__short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__float16 __BIF __vinthsph_vv(__short32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vinthspl_vv                                                          */
/*----------------------------------------------------------------------------*/
/*
VINTHSPL
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__float8 __BIF __vinthspl_vv(__short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__float16 __BIF __vinthspl_vv(__short32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vinthspuh_vv                                                         */
/*----------------------------------------------------------------------------*/
/*
VINTHSPUH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__float8 __BIF __vinthspuh_vv(__ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__float16 __BIF __vinthspuh_vv(__ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vinthspul_vv                                                         */
/*----------------------------------------------------------------------------*/
/*
VINTHSPUL
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__float8 __BIF __vinthspul_vv(__ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__float16 __BIF __vinthspul_vv(__ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vintsp_vv                                                            */
/*----------------------------------------------------------------------------*/
/*
VINTSP
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__float8 __BIF __vintsp_vv(__int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__float16 __BIF __vintsp_vv(__int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vintspu_vv                                                           */
/*----------------------------------------------------------------------------*/
/*
VINTSPU
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__float8 __BIF __vintspu_vv(__uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__float16 __BIF __vintspu_vv(__uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vlhmv_vvv                                                            */
/*----------------------------------------------------------------------------*/
/*
VLHMV
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __BIF __vlhmv_vvv(__uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __vlhmv_vvv(__uchar64, __uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vllmv_vvv                                                            */
/*----------------------------------------------------------------------------*/
/*
VLLMV
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __BIF __vllmv_vvv(__uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __vllmv_vvv(__uchar64, __uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vlmbd0b_vv                                                           */
/*----------------------------------------------------------------------------*/
/*
VLMBD0B
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __BIF __vlmbd0b_vv(__uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __vlmbd0b_vv(__uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vlmbd0d_vv                                                           */
/*----------------------------------------------------------------------------*/
/*
VLMBD0D
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __BIF __vlmbd0d_vv(__ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __BIF __vlmbd0d_vv(__ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vlmbd0h_vv                                                           */
/*----------------------------------------------------------------------------*/
/*
VLMBD0H
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __BIF __vlmbd0h_vv(__ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __BIF __vlmbd0h_vv(__ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vlmbd0w_vv                                                           */
/*----------------------------------------------------------------------------*/
/*
VLMBD0W
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __BIF __vlmbd0w_vv(__uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __BIF __vlmbd0w_vv(__uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vlmbd1b_vv                                                           */
/*----------------------------------------------------------------------------*/
/*
VLMBD1B
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __BIF __vlmbd1b_vv(__uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __vlmbd1b_vv(__uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vlmbd1d_vv                                                           */
/*----------------------------------------------------------------------------*/
/*
VLMBD1D
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __BIF __vlmbd1d_vv(__ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __BIF __vlmbd1d_vv(__ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vlmbd1h_vv                                                           */
/*----------------------------------------------------------------------------*/
/*
VLMBD1H
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __BIF __vlmbd1h_vv(__ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __BIF __vlmbd1h_vv(__ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vlmbd1w_vv                                                           */
/*----------------------------------------------------------------------------*/
/*
VLMBD1W
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __BIF __vlmbd1w_vv(__uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __BIF __vlmbd1w_vv(__uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vlmbdb_vvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VLMBDB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __BIF __vlmbdb_vvv(__uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __vlmbdb_vvv(__uchar64, __uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vlmbdd_vvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VLMBDD
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __BIF __vlmbdd_vvv(__ulong4, __ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __BIF __vlmbdd_vvv(__ulong8, __ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vlmbdh_vvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VLMBDH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __BIF __vlmbdh_vvv(__ushort16, __ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __BIF __vlmbdh_vvv(__ushort32, __ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vlmbdw_vvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VLMBDW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __BIF __vlmbdw_vvv(__uint8, __uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __BIF __vlmbdw_vvv(__uint16, __uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vmatmpysp_vww                                                        */
/*----------------------------------------------------------------------------*/
/*

VMATMPYSP
#if __C7X_VEC_SIZE_BITS__ == 512
void __vmatmpysp_vww(float16, float16, float16, float16&, float16&);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __vmaxb_vvv                                                            */
/*----------------------------------------------------------------------------*/
/*
VMAXB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __BIF __vmaxb_vvv(__char32, __char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __BIF __vmaxb_vvv(__char64, __char64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vmaxd_vvv                                                            */
/*----------------------------------------------------------------------------*/
/*
VMAXD
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __BIF __vmaxd_vvv(__long4, __long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __BIF __vmaxd_vvv(__long8, __long8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vmaxdp_vvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VMAXDP
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__double4 __BIF __vmaxdp_vvv(__double4, __double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__double8 __BIF __vmaxdp_vvv(__double8, __double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vmaxh_vvv                                                            */
/*----------------------------------------------------------------------------*/
/*
VMAXH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __BIF __vmaxh_vvv(__short16, __short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __BIF __vmaxh_vvv(__short32, __short32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vmaxpb_vvp                                                           */
/*----------------------------------------------------------------------------*/
/*

VMAXPB
#if __C7X_VEC_SIZE_BITS__ == 256
void __vmaxpb_vvp(char32, char32&, __vpred&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
void __vmaxpb_vvp(char64, char64&, __vpred&);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __vmaxpd_vvp                                                           */
/*----------------------------------------------------------------------------*/
/*

VMAXPD
#if __C7X_VEC_SIZE_BITS__ == 256
void __vmaxpd_vvp(long4, long4&, __vpred&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
void __vmaxpd_vvp(long8, long8&, __vpred&);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __vmaxph_vvp                                                           */
/*----------------------------------------------------------------------------*/
/*

VMAXPH
#if __C7X_VEC_SIZE_BITS__ == 256
void __vmaxph_vvp(short16, short16&, __vpred&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
void __vmaxph_vvp(short32, short32&, __vpred&);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __vmaxpw_vvp                                                           */
/*----------------------------------------------------------------------------*/
/*

VMAXPW
#if __C7X_VEC_SIZE_BITS__ == 256
void __vmaxpw_vvp(int8, int8&, __vpred&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
void __vmaxpw_vvp(int16, int16&, __vpred&);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __vmaxsp_vvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VMAXSP
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__float8 __BIF __vmaxsp_vvv(__float8, __float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__float16 __BIF __vmaxsp_vvv(__float16, __float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vmaxub_vvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VMAXUB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __BIF __vmaxub_vvv(__uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __vmaxub_vvv(__uchar64, __uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vmaxud_vvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VMAXUD
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __BIF __vmaxud_vvv(__ulong4, __ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __BIF __vmaxud_vvv(__ulong8, __ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vmaxuh_vvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VMAXUH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __BIF __vmaxuh_vvv(__ushort16, __ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __BIF __vmaxuh_vvv(__ushort32, __ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vmaxupb_vvp                                                          */
/*----------------------------------------------------------------------------*/
/*

VMAXUPB
#if __C7X_VEC_SIZE_BITS__ == 256
void __vmaxupb_vvp(uchar32, uchar32&, __vpred&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
void __vmaxupb_vvp(uchar64, uchar64&, __vpred&);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __vmaxupd_vvp                                                          */
/*----------------------------------------------------------------------------*/
/*

VMAXUPD
#if __C7X_VEC_SIZE_BITS__ == 256
void __vmaxupd_vvp(ulong4, ulong4&, __vpred&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
void __vmaxupd_vvp(ulong8, ulong8&, __vpred&);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __vmaxuph_vvp                                                          */
/*----------------------------------------------------------------------------*/
/*

VMAXUPH
#if __C7X_VEC_SIZE_BITS__ == 256
void __vmaxuph_vvp(ushort16, ushort16&, __vpred&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
void __vmaxuph_vvp(ushort32, ushort32&, __vpred&);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __vmaxupw_vvp                                                          */
/*----------------------------------------------------------------------------*/
/*

VMAXUPW
#if __C7X_VEC_SIZE_BITS__ == 256
void __vmaxupw_vvp(uint8, uint8&, __vpred&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
void __vmaxupw_vvp(uint16, uint16&, __vpred&);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __vmaxuw_vvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VMAXUW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __BIF __vmaxuw_vvv(__uint8, __uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __BIF __vmaxuw_vvv(__uint16, __uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vmaxw_vvv                                                            */
/*----------------------------------------------------------------------------*/
/*
VMAXW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __BIF __vmaxw_vvv(__int8, __int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __BIF __vmaxw_vvv(__int16, __int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vminb_vvv                                                            */
/*----------------------------------------------------------------------------*/
/*
VMINB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __BIF __vminb_vvv(__char32, __char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __BIF __vminb_vvv(__char64, __char64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vmind_vvv                                                            */
/*----------------------------------------------------------------------------*/
/*
VMIND
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __BIF __vmind_vvv(__long4, __long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __BIF __vmind_vvv(__long8, __long8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vmindp_vvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VMINDP
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__double4 __BIF __vmindp_vvv(__double4, __double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__double8 __BIF __vmindp_vvv(__double8, __double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vminh_vvv                                                            */
/*----------------------------------------------------------------------------*/
/*
VMINH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __BIF __vminh_vvv(__short16, __short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __BIF __vminh_vvv(__short32, __short32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vminpb_vvp                                                           */
/*----------------------------------------------------------------------------*/
/*

VMINPB
#if __C7X_VEC_SIZE_BITS__ == 256
void __vminpb_vvp(char32, char32&, __vpred&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
void __vminpb_vvp(char64, char64&, __vpred&);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __vminpd_vvp                                                           */
/*----------------------------------------------------------------------------*/
/*

VMINPD
#if __C7X_VEC_SIZE_BITS__ == 256
void __vminpd_vvp(long4, long4&, __vpred&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
void __vminpd_vvp(long8, long8&, __vpred&);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __vminph_vvp                                                           */
/*----------------------------------------------------------------------------*/
/*

VMINPH
#if __C7X_VEC_SIZE_BITS__ == 256
void __vminph_vvp(short16, short16&, __vpred&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
void __vminph_vvp(short32, short32&, __vpred&);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __vminpw_vvp                                                           */
/*----------------------------------------------------------------------------*/
/*

VMINPW
#if __C7X_VEC_SIZE_BITS__ == 256
void __vminpw_vvp(int8, int8&, __vpred&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
void __vminpw_vvp(int16, int16&, __vpred&);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __vminsp_vvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VMINSP
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__float8 __BIF __vminsp_vvv(__float8, __float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__float16 __BIF __vminsp_vvv(__float16, __float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vminub_vvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VMINUB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __BIF __vminub_vvv(__uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __vminub_vvv(__uchar64, __uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vminud_vvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VMINUD
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __BIF __vminud_vvv(__ulong4, __ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __BIF __vminud_vvv(__ulong8, __ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vminuh_vvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VMINUH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __BIF __vminuh_vvv(__ushort16, __ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __BIF __vminuh_vvv(__ushort32, __ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vminupb_vvp                                                          */
/*----------------------------------------------------------------------------*/
/*

VMINUPB
#if __C7X_VEC_SIZE_BITS__ == 256
void __vminupb_vvp(uchar32, uchar32&, __vpred&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
void __vminupb_vvp(uchar64, uchar64&, __vpred&);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __vminupd_vvp                                                          */
/*----------------------------------------------------------------------------*/
/*

VMINUPD
#if __C7X_VEC_SIZE_BITS__ == 256
void __vminupd_vvp(ulong4, ulong4&, __vpred&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
void __vminupd_vvp(ulong8, ulong8&, __vpred&);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __vminuph_vvp                                                          */
/*----------------------------------------------------------------------------*/
/*

VMINUPH
#if __C7X_VEC_SIZE_BITS__ == 256
void __vminuph_vvp(ushort16, ushort16&, __vpred&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
void __vminuph_vvp(ushort32, ushort32&, __vpred&);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __vminupw_vvp                                                          */
/*----------------------------------------------------------------------------*/
/*

VMINUPW
#if __C7X_VEC_SIZE_BITS__ == 256
void __vminupw_vvp(uint8, uint8&, __vpred&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
void __vminupw_vvp(uint16, uint16&, __vpred&);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __vminuw_vvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VMINUW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __BIF __vminuw_vvv(__uint8, __uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __BIF __vminuw_vvv(__uint16, __uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vminw_vvv                                                            */
/*----------------------------------------------------------------------------*/
/*
VMINW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __BIF __vminw_vvv(__int8, __int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __BIF __vminw_vvv(__int16, __int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vmpybb_vvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VMPYBB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __OVBIF __vmpybb_vvv(__char32, __char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __vmpybb_vvv(__char64, __char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __OVBIF __vmpybb_vvv(__uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __vmpybb_vvv(__uchar64, __uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vmpydd_vvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VMPYDD
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __OVBIF __vmpydd_vvv(__long4, __long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __vmpydd_vvv(__long8, __long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __OVBIF __vmpydd_vvv(__ulong4, __ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __vmpydd_vvv(__ulong8, __ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vmpydp_vvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VMPYDP
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__double4 __BIF __vmpydp_vvv(__double4, __double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__double8 __BIF __vmpydp_vvv(__double8, __double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vmpyhh_vvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VMPYHH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __OVBIF __vmpyhh_vvv(__short16, __short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __vmpyhh_vvv(__short32, __short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __OVBIF __vmpyhh_vvv(__ushort16, __ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __vmpyhh_vvv(__ushort32, __ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vmpyhw_vvw                                                           */
/*----------------------------------------------------------------------------*/
/*

VMPYHW
#if __C7X_VEC_SIZE_BITS__ == 256
void __vmpyhw_vvw(short16, short16, int8&, int8&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
void __vmpyhw_vvw(short32, short32, int16&, int16&);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __vmpysp2dp_vvw                                                        */
/*----------------------------------------------------------------------------*/
/*

VMPYSP2DP
#if __C7X_VEC_SIZE_BITS__ == 256
void __vmpysp2dp_vvw(float8, float8, double4&, double4&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
void __vmpysp2dp_vvw(float16, float16, double8&, double8&);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __vmpysp_vvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VMPYSP
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__float8 __BIF __vmpysp_vvv(__float8, __float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__float16 __BIF __vmpysp_vvv(__float16, __float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vmpysubh_vvw                                                         */
/*----------------------------------------------------------------------------*/
/*

VMPYSUBH
#if __C7X_VEC_SIZE_BITS__ == 256
void __vmpysubh_vvw(char32, uchar32, short16&, short16&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
void __vmpysubh_vvw(char64, uchar64, short32&, short32&);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __vmpysuhw_vvw                                                         */
/*----------------------------------------------------------------------------*/
/*

VMPYSUHW
#if __C7X_VEC_SIZE_BITS__ == 256
void __vmpysuhw_vvw(short16, ushort16, int8&, int8&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
void __vmpysuhw_vvw(short32, ushort32, int16&, int16&);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __vmpysuwd_vvw                                                         */
/*----------------------------------------------------------------------------*/
/*

VMPYSUWD
#if __C7X_VEC_SIZE_BITS__ == 256
void __vmpysuwd_vvw(int8, uint8, long4&, long4&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
void __vmpysuwd_vvw(int16, uint16, long8&, long8&);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __vmpyubh_vvw                                                          */
/*----------------------------------------------------------------------------*/
/*

VMPYUBH
#if __C7X_VEC_SIZE_BITS__ == 256
void __vmpyubh_vvw(uchar32, uchar32, ushort16&, ushort16&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
void __vmpyubh_vvw(uchar64, uchar64, ushort32&, ushort32&);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __vmpyudq_vvw                                                          */
/*----------------------------------------------------------------------------*/
/*

VMPYUDQ
#if __C7X_VEC_SIZE_BITS__ == 256
void __vmpyudq_vvw(ulong4, ulong4, ulong4&, ulong4&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
void __vmpyudq_vvw(ulong8, ulong8, ulong8&, ulong8&);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __vmpyuhw_vvw                                                          */
/*----------------------------------------------------------------------------*/
/*

VMPYUHW
#if __C7X_VEC_SIZE_BITS__ == 256
void __vmpyuhw_vvw(ushort16, ushort16, uint8&, uint8&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
void __vmpyuhw_vvw(ushort32, ushort32, uint16&, uint16&);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __vmpyuwd_vvw                                                          */
/*----------------------------------------------------------------------------*/
/*

VMPYUWD
#if __C7X_VEC_SIZE_BITS__ == 256
void __vmpyuwd_vvw(uint8, uint8, ulong4&, ulong4&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
void __vmpyuwd_vvw(uint16, uint16, ulong8&, ulong8&);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __vmpywd_vvw                                                           */
/*----------------------------------------------------------------------------*/
/*

VMPYWD
#if __C7X_VEC_SIZE_BITS__ == 256
void __vmpywd_vvw(int8, int8, long4&, long4&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
void __vmpywd_vvw(int16, int16, long8&, long8&);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __vmpyww_vvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VMPYWW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __OVBIF __vmpyww_vvv(__int8, __int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __vmpyww_vvv(__int16, __int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __OVBIF __vmpyww_vvv(__uint8, __uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __vmpyww_vvv(__uint16, __uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vnandw_vvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VNANDW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __OVBIF __vnandw_vvv(__char32, __char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __vnandw_vvv(__char64, __char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __OVBIF __vnandw_vvv(__uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __vnandw_vvv(__uchar64, __uchar64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __OVBIF __vnandw_vvv(__short16, __short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __vnandw_vvv(__short32, __short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __OVBIF __vnandw_vvv(__ushort16, __ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __vnandw_vvv(__ushort32, __ushort32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __OVBIF __vnandw_vvv(__int8, __int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __vnandw_vvv(__int16, __int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __OVBIF __vnandw_vvv(__uint8, __uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __vnandw_vvv(__uint16, __uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __OVBIF __vnandw_vvv(__long4, __long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __vnandw_vvv(__long8, __long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __OVBIF __vnandw_vvv(__ulong4, __ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __vnandw_vvv(__ulong8, __ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vnorm2uh_vv                                                          */
/*----------------------------------------------------------------------------*/
/*
VNORM2UH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __BIF __vnorm2uh_vv(__ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __BIF __vnorm2uh_vv(__ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vnorm2uw_vv                                                          */
/*----------------------------------------------------------------------------*/
/*
VNORM2UW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __BIF __vnorm2uw_vv(__uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __BIF __vnorm2uw_vv(__uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vnormb_vv                                                            */
/*----------------------------------------------------------------------------*/
/*
VNORMB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __BIF __vnormb_vv(__char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __BIF __vnormb_vv(__char64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vnormd_vv                                                            */
/*----------------------------------------------------------------------------*/
/*
VNORMD
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __BIF __vnormd_vv(__long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __BIF __vnormd_vv(__long8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vnormh_vv                                                            */
/*----------------------------------------------------------------------------*/
/*
VNORMH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __BIF __vnormh_vv(__short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __BIF __vnormh_vv(__short32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vnormw_vv                                                            */
/*----------------------------------------------------------------------------*/
/*
VNORMW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __BIF __vnormw_vv(__int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __BIF __vnormw_vv(__int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vnorw_vvv                                                            */
/*----------------------------------------------------------------------------*/
/*
VNORW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __OVBIF __vnorw_vvv(__char32, __char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __vnorw_vvv(__char64, __char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __OVBIF __vnorw_vvv(__uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __vnorw_vvv(__uchar64, __uchar64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __OVBIF __vnorw_vvv(__short16, __short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __vnorw_vvv(__short32, __short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __OVBIF __vnorw_vvv(__ushort16, __ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __vnorw_vvv(__ushort32, __ushort32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __OVBIF __vnorw_vvv(__int8, __int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __vnorw_vvv(__int16, __int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __OVBIF __vnorw_vvv(__uint8, __uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __vnorw_vvv(__uint16, __uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __OVBIF __vnorw_vvv(__long4, __long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __vnorw_vvv(__long8, __long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __OVBIF __vnorw_vvv(__ulong4, __ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __vnorw_vvv(__ulong8, __ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vopmatmpysp_vvw                                                      */
/*----------------------------------------------------------------------------*/
/*

VOPMATMPYSP
#if __C7X_VEC_SIZE_BITS__ == 512
void __vopmatmpysp_vvw(float16, float16, float16&, float16&);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __vornw_vkv                                                            */
/*----------------------------------------------------------------------------*/
/*
VORNW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __OVBIF __vornw_vkv(__int8, __int8 __CST(-2147483648, 2147483647));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __vornw_vkv(__int16, __int16 __CST(-2147483648, 2147483647));
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __OVBIF __vornw_vkv(__uint8, __uint8 __CST(0, 4294967295));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __vornw_vkv(__uint16, __uint16 __CST(0, 4294967295));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vornw_vvv                                                            */
/*----------------------------------------------------------------------------*/
/*
VORNW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __OVBIF __vornw_vvv(__char32, __char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __vornw_vvv(__char64, __char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __OVBIF __vornw_vvv(__uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __vornw_vvv(__uchar64, __uchar64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __OVBIF __vornw_vvv(__short16, __short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __vornw_vvv(__short32, __short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __OVBIF __vornw_vvv(__ushort16, __ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __vornw_vvv(__ushort32, __ushort32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __OVBIF __vornw_vvv(__int8, __int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __vornw_vvv(__int16, __int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __OVBIF __vornw_vvv(__uint8, __uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __vornw_vvv(__uint16, __uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __OVBIF __vornw_vvv(__long4, __long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __vornw_vvv(__long8, __long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __OVBIF __vornw_vvv(__ulong4, __ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __vornw_vvv(__ulong8, __ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vorw_vkv                                                             */
/*----------------------------------------------------------------------------*/
/*
VORW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __OVBIF __vorw_vkv(__int8, __int8 __CST(-2147483648, 2147483647));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __vorw_vkv(__int16, __int16 __CST(-2147483648, 2147483647));
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __OVBIF __vorw_vkv(__uint8, __uint8 __CST(0, 4294967295));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __vorw_vkv(__uint16, __uint16 __CST(0, 4294967295));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vorw_vvv                                                             */
/*----------------------------------------------------------------------------*/
/*
VORW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __OVBIF __vorw_vvv(__char32, __char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __vorw_vvv(__char64, __char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __OVBIF __vorw_vvv(__uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __vorw_vvv(__uchar64, __uchar64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __OVBIF __vorw_vvv(__short16, __short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __vorw_vvv(__short32, __short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __OVBIF __vorw_vvv(__ushort16, __ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __vorw_vvv(__ushort32, __ushort32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __OVBIF __vorw_vvv(__int8, __int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __vorw_vvv(__int16, __int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __OVBIF __vorw_vvv(__uint8, __uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __vorw_vvv(__uint16, __uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __OVBIF __vorw_vvv(__long4, __long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __vorw_vvv(__long8, __long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __OVBIF __vorw_vvv(__ulong4, __ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __vorw_vvv(__ulong8, __ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vpackh2_vvv                                                          */
/*----------------------------------------------------------------------------*/
/*
VPACKH2
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cchar16 __OVBIF __vpackh2_vvv(__cchar16, __cchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cchar32 __OVBIF __vpackh2_vvv(__cchar32, __cchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __OVBIF __vpackh2_vvv(__short16, __short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __vpackh2_vvv(__short32, __short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __OVBIF __vpackh2_vvv(__ushort16, __ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __vpackh2_vvv(__ushort32, __ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vpackh4_vvv                                                          */
/*----------------------------------------------------------------------------*/
/*
VPACKH4
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __OVBIF __vpackh4_vvv(__char32, __char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __vpackh4_vvv(__char64, __char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __OVBIF __vpackh4_vvv(__uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __vpackh4_vvv(__uchar64, __uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vpackhl2_vvv                                                         */
/*----------------------------------------------------------------------------*/
/*
VPACKHL2
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cchar16 __OVBIF __vpackhl2_vvv(__cchar16, __cchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cchar32 __OVBIF __vpackhl2_vvv(__cchar32, __cchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __OVBIF __vpackhl2_vvv(__short16, __short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __vpackhl2_vvv(__short32, __short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __OVBIF __vpackhl2_vvv(__ushort16, __ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __vpackhl2_vvv(__ushort32, __ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vpackl2_vvv                                                          */
/*----------------------------------------------------------------------------*/
/*
VPACKL2
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cchar16 __OVBIF __vpackl2_vvv(__cchar16, __cchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cchar32 __OVBIF __vpackl2_vvv(__cchar32, __cchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __OVBIF __vpackl2_vvv(__short16, __short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __vpackl2_vvv(__short32, __short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __OVBIF __vpackl2_vvv(__ushort16, __ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __vpackl2_vvv(__ushort32, __ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vpackl4_vvv                                                          */
/*----------------------------------------------------------------------------*/
/*
VPACKL4
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __OVBIF __vpackl4_vvv(__char32, __char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __vpackl4_vvv(__char64, __char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __OVBIF __vpackl4_vvv(__uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __vpackl4_vvv(__uchar64, __uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vpacklh2_vvv                                                         */
/*----------------------------------------------------------------------------*/
/*
VPACKLH2
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cchar16 __OVBIF __vpacklh2_vvv(__cchar16, __cchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cchar32 __OVBIF __vpacklh2_vvv(__cchar32, __cchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __OVBIF __vpacklh2_vvv(__short16, __short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __vpacklh2_vvv(__short32, __short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __OVBIF __vpacklh2_vvv(__ushort16, __ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __vpacklh2_vvv(__ushort32, __ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vpacklh4_vvv                                                         */
/*----------------------------------------------------------------------------*/
/*
VPACKLH4
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __OVBIF __vpacklh4_vvv(__char32, __char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __vpacklh4_vvv(__char64, __char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __OVBIF __vpacklh4_vvv(__uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __vpacklh4_vvv(__uchar64, __uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vpackp2_vvv                                                          */
/*----------------------------------------------------------------------------*/
/*
VPACKP2
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cchar16 __OVBIF __vpackp2_vvv(__cchar16, __cchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cchar32 __OVBIF __vpackp2_vvv(__cchar32, __cchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __OVBIF __vpackp2_vvv(__short16, __short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __vpackp2_vvv(__short32, __short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __OVBIF __vpackp2_vvv(__ushort16, __ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __vpackp2_vvv(__ushort32, __ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vpackw_vvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VPACKW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cshort8 __OVBIF __vpackw_vvv(__cshort8, __cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cshort16 __OVBIF __vpackw_vvv(__cshort16, __cshort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __OVBIF __vpackw_vvv(__int8, __int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __vpackw_vvv(__int16, __int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __OVBIF __vpackw_vvv(__uint8, __uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __vpackw_vvv(__uint16, __uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__float8 __OVBIF __vpackw_vvv(__float8, __float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__float16 __OVBIF __vpackw_vvv(__float16, __float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vpackx2_vvv                                                          */
/*----------------------------------------------------------------------------*/
/*
VPACKX2
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cchar16 __OVBIF __vpackx2_vvv(__cchar16, __cchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cchar32 __OVBIF __vpackx2_vvv(__cchar32, __cchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __OVBIF __vpackx2_vvv(__short16, __short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __vpackx2_vvv(__short32, __short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __OVBIF __vpackx2_vvv(__ushort16, __ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __vpackx2_vvv(__ushort32, __ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vperm_vvv                                                            */
/*----------------------------------------------------------------------------*/
/*
VPERM
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __BIF __vperm_vvv(__uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __vperm_vvv(__uchar64, __uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vperm_yvv                                                            */
/*----------------------------------------------------------------------------*/
/*
VPERM
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __BIF __vperm_yvv(__uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __vperm_yvv(__uchar64, __uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vpermeeb_yvvv                                                        */
/*----------------------------------------------------------------------------*/
/*
VPERMEEB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __BIF __vpermeeb_yvvv(__uchar32, __uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __vpermeeb_yvvv(__uchar64, __uchar64, __uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vpermeed_yvvv                                                        */
/*----------------------------------------------------------------------------*/
/*
VPERMEED
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __BIF __vpermeed_yvvv(__uchar32, __uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __vpermeed_yvvv(__uchar64, __uchar64, __uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vpermeeh_yvvv                                                        */
/*----------------------------------------------------------------------------*/
/*
VPERMEEH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __BIF __vpermeeh_yvvv(__uchar32, __uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __vpermeeh_yvvv(__uchar64, __uchar64, __uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vpermeeq_yvvv                                                        */
/*----------------------------------------------------------------------------*/
/*
VPERMEEQ
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __BIF __vpermeeq_yvvv(__uchar32, __uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __vpermeeq_yvvv(__uchar64, __uchar64, __uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vpermeew_yvvv                                                        */
/*----------------------------------------------------------------------------*/
/*
VPERMEEW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __BIF __vpermeew_yvvv(__uchar32, __uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __vpermeew_yvvv(__uchar64, __uchar64, __uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vpermeob_yvvv                                                        */
/*----------------------------------------------------------------------------*/
/*
VPERMEOB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __BIF __vpermeob_yvvv(__uchar32, __uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __vpermeob_yvvv(__uchar64, __uchar64, __uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vpermeod_yvvv                                                        */
/*----------------------------------------------------------------------------*/
/*
VPERMEOD
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __BIF __vpermeod_yvvv(__uchar32, __uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __vpermeod_yvvv(__uchar64, __uchar64, __uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vpermeoh_yvvv                                                        */
/*----------------------------------------------------------------------------*/
/*
VPERMEOH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __BIF __vpermeoh_yvvv(__uchar32, __uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __vpermeoh_yvvv(__uchar64, __uchar64, __uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vpermeoq_yvvv                                                        */
/*----------------------------------------------------------------------------*/
/*
VPERMEOQ
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __BIF __vpermeoq_yvvv(__uchar32, __uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __vpermeoq_yvvv(__uchar64, __uchar64, __uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vpermeow_yvvv                                                        */
/*----------------------------------------------------------------------------*/
/*
VPERMEOW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __BIF __vpermeow_yvvv(__uchar32, __uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __vpermeow_yvvv(__uchar64, __uchar64, __uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vpermhh_yvvv                                                         */
/*----------------------------------------------------------------------------*/
/*
VPERMHH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __BIF __vpermhh_yvvv(__uchar32, __uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __vpermhh_yvvv(__uchar64, __uchar64, __uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vpermlh_yvvv                                                         */
/*----------------------------------------------------------------------------*/
/*
VPERMLH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __BIF __vpermlh_yvvv(__uchar32, __uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __vpermlh_yvvv(__uchar64, __uchar64, __uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vpermll_yvvv                                                         */
/*----------------------------------------------------------------------------*/
/*
VPERMLL
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __BIF __vpermll_yvvv(__uchar32, __uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __vpermll_yvvv(__uchar64, __uchar64, __uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vpermoob_yvvv                                                        */
/*----------------------------------------------------------------------------*/
/*
VPERMOOB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __BIF __vpermoob_yvvv(__uchar32, __uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __vpermoob_yvvv(__uchar64, __uchar64, __uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vpermood_yvvv                                                        */
/*----------------------------------------------------------------------------*/
/*
VPERMOOD
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __BIF __vpermood_yvvv(__uchar32, __uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __vpermood_yvvv(__uchar64, __uchar64, __uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vpermooh_yvvv                                                        */
/*----------------------------------------------------------------------------*/
/*
VPERMOOH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __BIF __vpermooh_yvvv(__uchar32, __uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __vpermooh_yvvv(__uchar64, __uchar64, __uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vpermooq_yvvv                                                        */
/*----------------------------------------------------------------------------*/
/*
VPERMOOQ
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __BIF __vpermooq_yvvv(__uchar32, __uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __vpermooq_yvvv(__uchar64, __uchar64, __uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vpermoow_yvvv                                                        */
/*----------------------------------------------------------------------------*/
/*
VPERMOOW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __BIF __vpermoow_yvvv(__uchar32, __uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __vpermoow_yvvv(__uchar64, __uchar64, __uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vppackdup16w_pv                                                      */
/*----------------------------------------------------------------------------*/
/*
VPPACKDUP16W
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __BIF __vppackdup16w_pv(__vpred);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vppackdup8w_pv                                                       */
/*----------------------------------------------------------------------------*/
/*
VPPACKDUP8W
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __BIF __vppackdup8w_pv(__vpred);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vputb_dky                                                            */
/*----------------------------------------------------------------------------*/
/*
VPUTB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __OVBIF __vputb_dky(signed char, signed char __CST(0, 63), __char32);
__uchar32 __OVBIF __vputb_dky(__uchar, __uchar __CST(0, 63), __uchar32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vputb_rkv                                                            */
/*----------------------------------------------------------------------------*/
/*
VPUTB
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __vputb_rkv(signed char, signed char __CST(0, 63), __char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __OVBIF __vputb_rkv(signed char, signed char __CST(0, 63), __char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __vputb_rkv(__uchar, __uchar __CST(0, 63), __uchar64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __OVBIF __vputb_rkv(__uchar, __uchar __CST(0, 63), __uchar32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vputd_dkv                                                            */
/*----------------------------------------------------------------------------*/
/*
VPUTD
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__cint8 __OVBIF __vputd_dkv(__cint, signed char __CST(0, 63), __cint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cint4 __OVBIF __vputd_dkv(__cint, signed char __CST(0, 63), __cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cfloat8 __OVBIF __vputd_dkv(__cfloat, signed char __CST(0, 63), __cfloat8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cfloat4 __OVBIF __vputd_dkv(__cfloat, signed char __CST(0, 63), __cfloat4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cfloat8 __OVBIF __vputd_dkv(__cfloat, __uchar __CST(0, 63), __cfloat8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cfloat4 __OVBIF __vputd_dkv(__cfloat, __uchar __CST(0, 63), __cfloat4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __vputd_dkv(long, signed char __CST(0, 63), __long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __OVBIF __vputd_dkv(long, signed char __CST(0, 63), __long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __vputd_dkv(__ulong, __uchar __CST(0, 63), __ulong8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __OVBIF __vputd_dkv(__ulong, __uchar __CST(0, 63), __ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__double8 __OVBIF __vputd_dkv(double, signed char __CST(0, 63), __double8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__double4 __OVBIF __vputd_dkv(double, signed char __CST(0, 63), __double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__double8 __OVBIF __vputd_dkv(double, __uchar __CST(0, 63), __double8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__double4 __OVBIF __vputd_dkv(double, __uchar __CST(0, 63), __double4);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vputd_dky                                                            */
/*----------------------------------------------------------------------------*/
/*
VPUTD
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cint4 __OVBIF __vputd_dky(__cint, signed char __CST(0, 63), __cint4);
__cfloat4 __OVBIF __vputd_dky(__cfloat, signed char __CST(0, 63), __cfloat4);
__cfloat4 __OVBIF __vputd_dky(__cfloat, __uchar __CST(0, 63), __cfloat4);
__long4 __OVBIF __vputd_dky(long, signed char __CST(0, 63), __long4);
__ulong4 __OVBIF __vputd_dky(__ulong, __uchar __CST(0, 63), __ulong4);
__double4 __OVBIF __vputd_dky(double, signed char __CST(0, 63), __double4);
__double4 __OVBIF __vputd_dky(double, __uchar __CST(0, 63), __double4);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vputh_dky                                                            */
/*----------------------------------------------------------------------------*/
/*
VPUTH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cchar16 __OVBIF __vputh_dky(__cchar, signed char __CST(0, 63), __cchar16);
__short16 __OVBIF __vputh_dky(short, signed char __CST(0, 63), __short16);
__ushort16 __OVBIF __vputh_dky(__ushort, __uchar __CST(0, 63), __ushort16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vputh_rkv                                                            */
/*----------------------------------------------------------------------------*/
/*
VPUTH
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__cchar32 __OVBIF __vputh_rkv(__cchar, signed char __CST(0, 63), __cchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cchar16 __OVBIF __vputh_rkv(__cchar, signed char __CST(0, 63), __cchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __vputh_rkv(short, signed char __CST(0, 63), __short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __OVBIF __vputh_rkv(short, signed char __CST(0, 63), __short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __vputh_rkv(__ushort, __uchar __CST(0, 63), __ushort32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __OVBIF __vputh_rkv(__ushort, __uchar __CST(0, 63), __ushort16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vputw_dky                                                            */
/*----------------------------------------------------------------------------*/
/*
VPUTW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cshort8 __OVBIF __vputw_dky(__cshort, signed char __CST(0, 63), __cshort8);
__int8 __OVBIF __vputw_dky(int, signed char __CST(0, 63), __int8);
__uint8 __OVBIF __vputw_dky(__uint, __uchar __CST(0, 63), __uint8);
__float8 __OVBIF __vputw_dky(float, signed char __CST(0, 63), __float8);
__float8 __OVBIF __vputw_dky(float, __uchar __CST(0, 63), __float8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vputw_rkv                                                            */
/*----------------------------------------------------------------------------*/
/*
VPUTW
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__cshort16 __OVBIF __vputw_rkv(__cshort, signed char __CST(0, 63), __cshort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cshort8 __OVBIF __vputw_rkv(__cshort, signed char __CST(0, 63), __cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __vputw_rkv(int, signed char __CST(0, 63), __int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __OVBIF __vputw_rkv(int, signed char __CST(0, 63), __int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __vputw_rkv(__uint, __uchar __CST(0, 63), __uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __OVBIF __vputw_rkv(__uint, __uchar __CST(0, 63), __uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__float16 __OVBIF __vputw_rkv(float, signed char __CST(0, 63), __float16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__float8 __OVBIF __vputw_rkv(float, signed char __CST(0, 63), __float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__float16 __OVBIF __vputw_rkv(float, __uchar __CST(0, 63), __float16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__float8 __OVBIF __vputw_rkv(float, __uchar __CST(0, 63), __float8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vpxpnd_pv                                                            */
/*----------------------------------------------------------------------------*/
/*
VPXPND
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __BIF __vpxpnd_pv(__vpred);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __BIF __vpxpnd_pv(__vpred);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vrcpdp_vv                                                            */
/*----------------------------------------------------------------------------*/
/*
VRCPDP
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__double4 __BIF __vrcpdp_vv(__double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__double8 __BIF __vrcpdp_vv(__double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vrcpsp_vv                                                            */
/*----------------------------------------------------------------------------*/
/*
VRCPSP
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__float8 __BIF __vrcpsp_vv(__float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__float16 __BIF __vrcpsp_vv(__float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vreplace_vkkv                                                        */
/*----------------------------------------------------------------------------*/
/*
VREPLACE
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __OVBIF __vreplace_vkkv(__long4, __char4 __CST(0, 63), __char4 __CST(0, 63), __long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __vreplace_vkkv(__long8, __char8 __CST(0, 63), __char8 __CST(0, 63), __long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __OVBIF __vreplace_vkkv(__ulong4, __uchar4 __CST(0, 63), __uchar4 __CST(0, 63), __ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __vreplace_vkkv(__ulong8, __uchar8 __CST(0, 63), __uchar8 __CST(0, 63), __ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vreverseb_vv                                                         */
/*----------------------------------------------------------------------------*/
/*
VREVERSEB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __OVBIF __vreverseb_vv(__char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __vreverseb_vv(__char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __OVBIF __vreverseb_vv(__uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __vreverseb_vv(__uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vreversed_vv                                                         */
/*----------------------------------------------------------------------------*/
/*
VREVERSED
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cint4 __OVBIF __vreversed_vv(__cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cint8 __OVBIF __vreversed_vv(__cint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cfloat4 __OVBIF __vreversed_vv(__cfloat4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cfloat8 __OVBIF __vreversed_vv(__cfloat8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __OVBIF __vreversed_vv(__long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __vreversed_vv(__long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __OVBIF __vreversed_vv(__ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __vreversed_vv(__ulong8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__double4 __OVBIF __vreversed_vv(__double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__double8 __OVBIF __vreversed_vv(__double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vreverseh_vv                                                         */
/*----------------------------------------------------------------------------*/
/*
VREVERSEH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cchar16 __OVBIF __vreverseh_vv(__cchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cchar32 __OVBIF __vreverseh_vv(__cchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __OVBIF __vreverseh_vv(__short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __vreverseh_vv(__short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __OVBIF __vreverseh_vv(__ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __vreverseh_vv(__ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vreversew_vv                                                         */
/*----------------------------------------------------------------------------*/
/*
VREVERSEW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cshort8 __OVBIF __vreversew_vv(__cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cshort16 __OVBIF __vreversew_vv(__cshort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __OVBIF __vreversew_vv(__int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __vreversew_vv(__int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __OVBIF __vreversew_vv(__uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __vreversew_vv(__uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__float8 __OVBIF __vreversew_vv(__float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__float16 __OVBIF __vreversew_vv(__float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vrotlb_vkv                                                           */
/*----------------------------------------------------------------------------*/
/*
VROTLB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __BIF __vrotlb_vkv(__uchar32, __uchar32 __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __vrotlb_vkv(__uchar64, __uchar64 __CST(0, 63));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vrotlb_vvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VROTLB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __BIF __vrotlb_vvv(__uchar32, __uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __vrotlb_vvv(__uchar64, __uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vrotld_vkv                                                           */
/*----------------------------------------------------------------------------*/
/*
VROTLD
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __BIF __vrotld_vkv(__ulong4, __uchar4 __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __BIF __vrotld_vkv(__ulong8, __uchar8 __CST(0, 63));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vrotld_vvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VROTLD
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __BIF __vrotld_vvv(__ulong4, __ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __BIF __vrotld_vvv(__ulong8, __ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vrotlh_vkv                                                           */
/*----------------------------------------------------------------------------*/
/*
VROTLH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __BIF __vrotlh_vkv(__ushort16, __ushort16 __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __BIF __vrotlh_vkv(__ushort32, __ushort32 __CST(0, 63));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vrotlh_vvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VROTLH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __BIF __vrotlh_vvv(__ushort16, __uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __BIF __vrotlh_vvv(__ushort32, __uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vrotlw_vkv                                                           */
/*----------------------------------------------------------------------------*/
/*
VROTLW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __BIF __vrotlw_vkv(__int8, __uchar8 __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __BIF __vrotlw_vkv(__int16, __uchar16 __CST(0, 63));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vrotlw_vvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VROTLW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __BIF __vrotlw_vvv(__int8, __uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __BIF __vrotlw_vvv(__int16, __uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vrpackh_vvv                                                          */
/*----------------------------------------------------------------------------*/
/*
VRPACKH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __BIF __vrpackh_vvv(__int8, __int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __BIF __vrpackh_vvv(__int16, __int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vrsqrdp_vv                                                           */
/*----------------------------------------------------------------------------*/
/*
VRSQRDP
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__double4 __BIF __vrsqrdp_vv(__double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__double8 __BIF __vrsqrdp_vv(__double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vrsqrsp_vv                                                           */
/*----------------------------------------------------------------------------*/
/*
VRSQRSP
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__float8 __BIF __vrsqrsp_vv(__float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__float16 __BIF __vrsqrsp_vv(__float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsad16ou16h16w_vvv                                                   */
/*----------------------------------------------------------------------------*/
/*
VSAD16OU16H16W
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __BIF __vsad16ou16h16w_vvv(__ushort32, __ushort16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsad16ou8h16w_vvv                                                    */
/*----------------------------------------------------------------------------*/
/*
VSAD16OU8H16W
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __BIF __vsad16ou8h16w_vvv(__ushort32, __ushort8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsad8ou16b32h_vvv                                                    */
/*----------------------------------------------------------------------------*/
/*
VSAD8OU16B32H
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __BIF __vsad8ou16b32h_vvv(__uchar64, __uchar16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsaddb_vkv                                                           */
/*----------------------------------------------------------------------------*/
/*
VSADDB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __BIF __vsaddb_vkv(__char32, __char32 __CST(-128, 127));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __BIF __vsaddb_vkv(__char64, __char64 __CST(-128, 127));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsaddb_vvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VSADDB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __OVBIF __vsaddb_vvv(__char32, __char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __vsaddb_vvv(__char64, __char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cchar16 __OVBIF __vsaddb_vvv(__cchar16, __cchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cchar32 __OVBIF __vsaddb_vvv(__cchar32, __cchar32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsaddh_vkv                                                           */
/*----------------------------------------------------------------------------*/
/*
VSADDH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __BIF __vsaddh_vkv(__short16, __short16 __CST(-32768, 32767));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __BIF __vsaddh_vkv(__short32, __short32 __CST(-32768, 32767));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsaddh_vvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VSADDH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __OVBIF __vsaddh_vvv(__short16, __short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __vsaddh_vvv(__short32, __short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cshort8 __OVBIF __vsaddh_vvv(__cshort8, __cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cshort16 __OVBIF __vsaddh_vvv(__cshort16, __cshort16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsaddub_vvv                                                          */
/*----------------------------------------------------------------------------*/
/*
VSADDUB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __BIF __vsaddub_vvv(__uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __vsaddub_vvv(__uchar64, __uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsadduh_vvv                                                          */
/*----------------------------------------------------------------------------*/
/*
VSADDUH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __BIF __vsadduh_vvv(__ushort16, __ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __BIF __vsadduh_vvv(__ushort32, __ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsaddusb_vvv                                                         */
/*----------------------------------------------------------------------------*/
/*
VSADDUSB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __BIF __vsaddusb_vvv(__uchar32, __char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __vsaddusb_vvv(__uchar64, __char64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsaddush_vvv                                                         */
/*----------------------------------------------------------------------------*/
/*
VSADDUSH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __BIF __vsaddush_vvv(__ushort16, __short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __BIF __vsaddush_vvv(__ushort32, __short32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsaddusw_vvv                                                         */
/*----------------------------------------------------------------------------*/
/*
VSADDUSW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __BIF __vsaddusw_vvv(__uint8, __int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __BIF __vsaddusw_vvv(__uint16, __int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsadduw_vvv                                                          */
/*----------------------------------------------------------------------------*/
/*
VSADDUW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __BIF __vsadduw_vvv(__uint8, __uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __BIF __vsadduw_vvv(__uint16, __uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsaddw_vkv                                                           */
/*----------------------------------------------------------------------------*/
/*
VSADDW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __BIF __vsaddw_vkv(__int8, __int8 __CST(-2147483648, 2147483647));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __BIF __vsaddw_vkv(__int16, __int16 __CST(-2147483648, 2147483647));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsaddw_vvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VSADDW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __OVBIF __vsaddw_vvv(__int8, __int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __vsaddw_vvv(__int16, __int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cint4 __OVBIF __vsaddw_vvv(__cint4, __cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cint8 __OVBIF __vsaddw_vvv(__cint8, __cint8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsadm16ou16h16w_yvvv                                                 */
/*----------------------------------------------------------------------------*/
/*
VSADM16OU16H16W
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __BIF __vsadm16ou16h16w_yvvv(__uchar64, __ushort32, __ushort16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsadm16ou8h16w_yvvv                                                  */
/*----------------------------------------------------------------------------*/
/*
VSADM16OU8H16W
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __BIF __vsadm16ou8h16w_yvvv(__uchar64, __ushort32, __ushort8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsadm8ou16b32h_yvvv                                                  */
/*----------------------------------------------------------------------------*/
/*
VSADM8OU16B32H
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __BIF __vsadm8ou16b32h_yvvv(__uchar64, __uchar64, __uchar16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsatdl_vv                                                            */
/*----------------------------------------------------------------------------*/
/*
VSATDL
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __BIF __vsatdl_vv(__long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __BIF __vsatdl_vv(__long8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsatdw_vv                                                            */
/*----------------------------------------------------------------------------*/
/*
VSATDW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __BIF __vsatdw_vv(__long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __BIF __vsatdw_vv(__long8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsathb_vv                                                            */
/*----------------------------------------------------------------------------*/
/*
VSATHB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __BIF __vsathb_vv(__short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __BIF __vsathb_vv(__short32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsatlw_vv                                                            */
/*----------------------------------------------------------------------------*/
/*
VSATLW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __BIF __vsatlw_vv(__long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __BIF __vsatlw_vv(__long8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsatwh_vv                                                            */
/*----------------------------------------------------------------------------*/
/*
VSATWH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __BIF __vsatwh_vv(__int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __BIF __vsatwh_vv(__int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vscaledp_vvv                                                         */
/*----------------------------------------------------------------------------*/
/*
VSCALEDP
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__double4 __BIF __vscaledp_vvv(__double4, __ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__double8 __BIF __vscaledp_vvv(__double8, __ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vscalesp_vvv                                                         */
/*----------------------------------------------------------------------------*/
/*
VSCALESP
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__float8 __BIF __vscalesp_vvv(__float8, __uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__float16 __BIF __vscalesp_vvv(__float16, __uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vscatterb_pvv                                                        */
/*----------------------------------------------------------------------------*/
/*
VSCATTERB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __BIF __vscatterb_pvv(__vpred, __char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __BIF __vscatterb_pvv(__vpred, __char64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vscatternb_pvv                                                       */
/*----------------------------------------------------------------------------*/
/*
VSCATTERNB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __BIF __vscatternb_pvv(__vpred, __char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __BIF __vscatternb_pvv(__vpred, __char64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsel_pvkv                                                            */
/*----------------------------------------------------------------------------*/
/*
VSEL
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __OVBIF __vsel_pvkv(__vpred, __int8, __int8 __CST(-2147483648, 2147483647));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __vsel_pvkv(__vpred, __int16, __int16 __CST(-2147483648, 2147483647));
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __OVBIF __vsel_pvkv(__vpred, __uint8, __uint8 __CST(0, 4294967295));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __vsel_pvkv(__vpred, __uint16, __uint16 __CST(0, 4294967295));
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__float8 __OVBIF __vsel_pvkv(__vpred, __float8, __float8 k);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__float16 __OVBIF __vsel_pvkv(__vpred, __float16, __float16 k);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsel_pvvv                                                            */
/*----------------------------------------------------------------------------*/
/*
VSEL
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __OVBIF __vsel_pvvv(__vpred, __char32, __char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __vsel_pvvv(__vpred, __char64, __char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __OVBIF __vsel_pvvv(__vpred, __uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __vsel_pvvv(__vpred, __uchar64, __uchar64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cchar16 __OVBIF __vsel_pvvv(__vpred, __cchar16, __cchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cchar32 __OVBIF __vsel_pvvv(__vpred, __cchar32, __cchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __OVBIF __vsel_pvvv(__vpred, __short16, __short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __vsel_pvvv(__vpred, __short32, __short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __OVBIF __vsel_pvvv(__vpred, __ushort16, __ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __vsel_pvvv(__vpred, __ushort32, __ushort32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cshort8 __OVBIF __vsel_pvvv(__vpred, __cshort8, __cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cshort16 __OVBIF __vsel_pvvv(__vpred, __cshort16, __cshort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __OVBIF __vsel_pvvv(__vpred, __int8, __int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __vsel_pvvv(__vpred, __int16, __int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __OVBIF __vsel_pvvv(__vpred, __uint8, __uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __vsel_pvvv(__vpred, __uint16, __uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__float8 __OVBIF __vsel_pvvv(__vpred, __float8, __float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__float16 __OVBIF __vsel_pvvv(__vpred, __float16, __float16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cint4 __OVBIF __vsel_pvvv(__vpred, __cint4, __cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cint8 __OVBIF __vsel_pvvv(__vpred, __cint8, __cint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cfloat4 __OVBIF __vsel_pvvv(__vpred, __cfloat4, __cfloat4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cfloat8 __OVBIF __vsel_pvvv(__vpred, __cfloat8, __cfloat8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __OVBIF __vsel_pvvv(__vpred, __long4, __long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __vsel_pvvv(__vpred, __long8, __long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __OVBIF __vsel_pvvv(__vpred, __ulong4, __ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __vsel_pvvv(__vpred, __ulong8, __ulong8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__double4 __OVBIF __vsel_pvvv(__vpred, __double4, __double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__double8 __OVBIF __vsel_pvvv(__vpred, __double8, __double8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__clong2 __OVBIF __vsel_pvvv(__vpred, __clong2, __clong2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__clong4 __OVBIF __vsel_pvvv(__vpred, __clong4, __clong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cdouble2 __OVBIF __vsel_pvvv(__vpred, __cdouble2, __cdouble2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cdouble4 __OVBIF __vsel_pvvv(__vpred, __cdouble4, __cdouble4);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshfl2b_vv                                                           */
/*----------------------------------------------------------------------------*/
/*
VSHFL2B
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __OVBIF __vshfl2b_vv(__char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __vshfl2b_vv(__char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __OVBIF __vshfl2b_vv(__uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __vshfl2b_vv(__uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshfl2d_vv                                                           */
/*----------------------------------------------------------------------------*/
/*
VSHFL2D
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cint4 __OVBIF __vshfl2d_vv(__cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cint8 __OVBIF __vshfl2d_vv(__cint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cfloat4 __OVBIF __vshfl2d_vv(__cfloat4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cfloat8 __OVBIF __vshfl2d_vv(__cfloat8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __OVBIF __vshfl2d_vv(__long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __vshfl2d_vv(__long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __OVBIF __vshfl2d_vv(__ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __vshfl2d_vv(__ulong8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__double4 __OVBIF __vshfl2d_vv(__double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__double8 __OVBIF __vshfl2d_vv(__double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshfl2dee_vvv                                                        */
/*----------------------------------------------------------------------------*/
/*
VSHFL2DEE
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cint4 __OVBIF __vshfl2dee_vvv(__cint4, __cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cint8 __OVBIF __vshfl2dee_vvv(__cint8, __cint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cfloat4 __OVBIF __vshfl2dee_vvv(__cfloat4, __cfloat4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cfloat8 __OVBIF __vshfl2dee_vvv(__cfloat8, __cfloat8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __OVBIF __vshfl2dee_vvv(__long4, __long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __vshfl2dee_vvv(__long8, __long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __OVBIF __vshfl2dee_vvv(__ulong4, __ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __vshfl2dee_vvv(__ulong8, __ulong8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__double4 __OVBIF __vshfl2dee_vvv(__double4, __double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__double8 __OVBIF __vshfl2dee_vvv(__double8, __double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshfl2deo_vvv                                                        */
/*----------------------------------------------------------------------------*/
/*
VSHFL2DEO
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cint4 __OVBIF __vshfl2deo_vvv(__cint4, __cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cint8 __OVBIF __vshfl2deo_vvv(__cint8, __cint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cfloat4 __OVBIF __vshfl2deo_vvv(__cfloat4, __cfloat4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cfloat8 __OVBIF __vshfl2deo_vvv(__cfloat8, __cfloat8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __OVBIF __vshfl2deo_vvv(__long4, __long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __vshfl2deo_vvv(__long8, __long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __OVBIF __vshfl2deo_vvv(__ulong4, __ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __vshfl2deo_vvv(__ulong8, __ulong8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__double4 __OVBIF __vshfl2deo_vvv(__double4, __double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__double8 __OVBIF __vshfl2deo_vvv(__double8, __double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshfl2dhh_vvv                                                        */
/*----------------------------------------------------------------------------*/
/*
VSHFL2DHH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cint4 __OVBIF __vshfl2dhh_vvv(__cint4, __cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cint8 __OVBIF __vshfl2dhh_vvv(__cint8, __cint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cfloat4 __OVBIF __vshfl2dhh_vvv(__cfloat4, __cfloat4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cfloat8 __OVBIF __vshfl2dhh_vvv(__cfloat8, __cfloat8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __OVBIF __vshfl2dhh_vvv(__long4, __long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __vshfl2dhh_vvv(__long8, __long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __OVBIF __vshfl2dhh_vvv(__ulong4, __ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __vshfl2dhh_vvv(__ulong8, __ulong8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__double4 __OVBIF __vshfl2dhh_vvv(__double4, __double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__double8 __OVBIF __vshfl2dhh_vvv(__double8, __double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshfl2dlh_vvv                                                        */
/*----------------------------------------------------------------------------*/
/*
VSHFL2DLH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cint4 __OVBIF __vshfl2dlh_vvv(__cint4, __cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cint8 __OVBIF __vshfl2dlh_vvv(__cint8, __cint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cfloat4 __OVBIF __vshfl2dlh_vvv(__cfloat4, __cfloat4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cfloat8 __OVBIF __vshfl2dlh_vvv(__cfloat8, __cfloat8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __OVBIF __vshfl2dlh_vvv(__long4, __long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __vshfl2dlh_vvv(__long8, __long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __OVBIF __vshfl2dlh_vvv(__ulong4, __ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __vshfl2dlh_vvv(__ulong8, __ulong8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__double4 __OVBIF __vshfl2dlh_vvv(__double4, __double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__double8 __OVBIF __vshfl2dlh_vvv(__double8, __double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshfl2dll_vvv                                                        */
/*----------------------------------------------------------------------------*/
/*
VSHFL2DLL
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cint4 __OVBIF __vshfl2dll_vvv(__cint4, __cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cint8 __OVBIF __vshfl2dll_vvv(__cint8, __cint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cfloat4 __OVBIF __vshfl2dll_vvv(__cfloat4, __cfloat4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cfloat8 __OVBIF __vshfl2dll_vvv(__cfloat8, __cfloat8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __OVBIF __vshfl2dll_vvv(__long4, __long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __vshfl2dll_vvv(__long8, __long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __OVBIF __vshfl2dll_vvv(__ulong4, __ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __vshfl2dll_vvv(__ulong8, __ulong8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__double4 __OVBIF __vshfl2dll_vvv(__double4, __double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__double8 __OVBIF __vshfl2dll_vvv(__double8, __double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshfl2doo_vvv                                                        */
/*----------------------------------------------------------------------------*/
/*
VSHFL2DOO
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cint4 __OVBIF __vshfl2doo_vvv(__cint4, __cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cint8 __OVBIF __vshfl2doo_vvv(__cint8, __cint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cfloat4 __OVBIF __vshfl2doo_vvv(__cfloat4, __cfloat4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cfloat8 __OVBIF __vshfl2doo_vvv(__cfloat8, __cfloat8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __OVBIF __vshfl2doo_vvv(__long4, __long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __vshfl2doo_vvv(__long8, __long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __OVBIF __vshfl2doo_vvv(__ulong4, __ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __vshfl2doo_vvv(__ulong8, __ulong8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__double4 __OVBIF __vshfl2doo_vvv(__double4, __double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__double8 __OVBIF __vshfl2doo_vvv(__double8, __double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshfl2h_vv                                                           */
/*----------------------------------------------------------------------------*/
/*
VSHFL2H
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cchar16 __OVBIF __vshfl2h_vv(__cchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cchar32 __OVBIF __vshfl2h_vv(__cchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __OVBIF __vshfl2h_vv(__short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __vshfl2h_vv(__short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __OVBIF __vshfl2h_vv(__ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __vshfl2h_vv(__ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshfl2hhh_vvv                                                        */
/*----------------------------------------------------------------------------*/
/*
VSHFL2HHH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cchar16 __OVBIF __vshfl2hhh_vvv(__cchar16, __cchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cchar32 __OVBIF __vshfl2hhh_vvv(__cchar32, __cchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __OVBIF __vshfl2hhh_vvv(__short16, __short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __vshfl2hhh_vvv(__short32, __short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __OVBIF __vshfl2hhh_vvv(__ushort16, __ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __vshfl2hhh_vvv(__ushort32, __ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshfl2hll_vvv                                                        */
/*----------------------------------------------------------------------------*/
/*
VSHFL2HLL
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cchar16 __OVBIF __vshfl2hll_vvv(__cchar16, __cchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cchar32 __OVBIF __vshfl2hll_vvv(__cchar32, __cchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __OVBIF __vshfl2hll_vvv(__short16, __short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __vshfl2hll_vvv(__short32, __short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __OVBIF __vshfl2hll_vvv(__ushort16, __ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __vshfl2hll_vvv(__ushort32, __ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshfl2w_vv                                                           */
/*----------------------------------------------------------------------------*/
/*
VSHFL2W
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cshort8 __OVBIF __vshfl2w_vv(__cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cshort16 __OVBIF __vshfl2w_vv(__cshort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __OVBIF __vshfl2w_vv(__int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __vshfl2w_vv(__int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __OVBIF __vshfl2w_vv(__uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __vshfl2w_vv(__uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__float8 __OVBIF __vshfl2w_vv(__float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__float16 __OVBIF __vshfl2w_vv(__float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshfl2whh_vvv                                                        */
/*----------------------------------------------------------------------------*/
/*
VSHFL2WHH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cshort8 __OVBIF __vshfl2whh_vvv(__cshort8, __cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cshort16 __OVBIF __vshfl2whh_vvv(__cshort16, __cshort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __OVBIF __vshfl2whh_vvv(__int8, __int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __vshfl2whh_vvv(__int16, __int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __OVBIF __vshfl2whh_vvv(__uint8, __uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __vshfl2whh_vvv(__uint16, __uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__float8 __OVBIF __vshfl2whh_vvv(__float8, __float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__float16 __OVBIF __vshfl2whh_vvv(__float16, __float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshfl2wll_vvv                                                        */
/*----------------------------------------------------------------------------*/
/*
VSHFL2WLL
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cshort8 __OVBIF __vshfl2wll_vvv(__cshort8, __cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cshort16 __OVBIF __vshfl2wll_vvv(__cshort16, __cshort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __OVBIF __vshfl2wll_vvv(__int8, __int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __vshfl2wll_vvv(__int16, __int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __OVBIF __vshfl2wll_vvv(__uint8, __uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __vshfl2wll_vvv(__uint16, __uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__float8 __OVBIF __vshfl2wll_vvv(__float8, __float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__float16 __OVBIF __vshfl2wll_vvv(__float16, __float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshfl3_vvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VSHFL3
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __OVBIF __vshfl3_vvv(__int8, __int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __vshfl3_vvv(__int16, __int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __OVBIF __vshfl3_vvv(__uint8, __uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __vshfl3_vvv(__uint16, __uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshfl4b_vv                                                           */
/*----------------------------------------------------------------------------*/
/*
VSHFL4B
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __OVBIF __vshfl4b_vv(__char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __vshfl4b_vv(__char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __OVBIF __vshfl4b_vv(__uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __vshfl4b_vv(__uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshfl4h_vv                                                           */
/*----------------------------------------------------------------------------*/
/*
VSHFL4H
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cchar16 __OVBIF __vshfl4h_vv(__cchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cchar32 __OVBIF __vshfl4h_vv(__cchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __OVBIF __vshfl4h_vv(__short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __vshfl4h_vv(__short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __OVBIF __vshfl4h_vv(__ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __vshfl4h_vv(__ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshfl4w_vv                                                           */
/*----------------------------------------------------------------------------*/
/*
VSHFL4W
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cshort8 __OVBIF __vshfl4w_vv(__cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cshort16 __OVBIF __vshfl4w_vv(__cshort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __OVBIF __vshfl4w_vv(__int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __vshfl4w_vv(__int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __OVBIF __vshfl4w_vv(__uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __vshfl4w_vv(__uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__float8 __OVBIF __vshfl4w_vv(__float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__float16 __OVBIF __vshfl4w_vv(__float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshl_vkv                                                             */
/*----------------------------------------------------------------------------*/
/*
VSHL
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __BIF __vshl_vkv(__ulong8, __uchar __CST(1, 64));
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __BIF __vshl_vkv(__ulong4, __uchar __CST(1, 64));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshl_vvv                                                             */
/*----------------------------------------------------------------------------*/
/*
VSHL
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __BIF __vshl_vvv(__ulong4, __ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __BIF __vshl_vvv(__ulong8, __ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshlb_vkv                                                            */
/*----------------------------------------------------------------------------*/
/*
VSHLB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __OVBIF __vshlb_vkv(__char32, __char32 __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __vshlb_vkv(__char64, __char64 __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __OVBIF __vshlb_vkv(__uchar32, __uchar32 __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __vshlb_vkv(__uchar64, __uchar64 __CST(0, 63));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshlb_vvv                                                            */
/*----------------------------------------------------------------------------*/
/*
VSHLB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __OVBIF __vshlb_vvv(__char32, __int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __vshlb_vvv(__char64, __int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __OVBIF __vshlb_vvv(__uchar32, __uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __vshlb_vvv(__uchar64, __uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshlcb_pvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VSHLCB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __OVBIF __vshlcb_pvv(__vpred, __char32, __char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __vshlcb_pvv(__vpred, __char64, __char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __OVBIF __vshlcb_pvv(__vpred, __uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __vshlcb_pvv(__vpred, __uchar64, __uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshlch_pvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VSHLCH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __OVBIF __vshlch_pvv(__vpred, __short16, __short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __vshlch_pvv(__vpred, __short32, __short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __OVBIF __vshlch_pvv(__vpred, __ushort16, __ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __vshlch_pvv(__vpred, __ushort32, __ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshlcw_pvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VSHLCW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __OVBIF __vshlcw_pvv(__vpred, __int8, __int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __vshlcw_pvv(__vpred, __int16, __int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __OVBIF __vshlcw_pvv(__vpred, __uint8, __uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __vshlcw_pvv(__vpred, __uint16, __uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshld_vkv                                                            */
/*----------------------------------------------------------------------------*/
/*
VSHLD
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __OVBIF __vshld_vkv(__long4, __long4 __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __vshld_vkv(__long8, __long8 __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __OVBIF __vshld_vkv(__ulong4, __ulong4 __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __vshld_vkv(__ulong8, __ulong8 __CST(0, 63));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshld_vvv                                                            */
/*----------------------------------------------------------------------------*/
/*
VSHLD
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __OVBIF __vshld_vvv(__long4, __long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __vshld_vvv(__long8, __long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __OVBIF __vshld_vvv(__ulong4, __ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __vshld_vvv(__ulong8, __ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshlh_vkv                                                            */
/*----------------------------------------------------------------------------*/
/*
VSHLH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __OVBIF __vshlh_vkv(__short16, __short16 __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __vshlh_vkv(__short32, __short32 __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __OVBIF __vshlh_vkv(__ushort16, __ushort16 __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __vshlh_vkv(__ushort32, __ushort32 __CST(0, 63));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshlh_vvv                                                            */
/*----------------------------------------------------------------------------*/
/*
VSHLH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __OVBIF __vshlh_vvv(__short16, __int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __vshlh_vvv(__short32, __int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __OVBIF __vshlh_vvv(__ushort16, __uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __vshlh_vvv(__ushort32, __uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshlm16b_vvv                                                         */
/*----------------------------------------------------------------------------*/
/*
VSHLM16B
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __BIF __vshlm16b_vvv(__char64, __char16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __BIF __vshlm16b_vvv(__char32, __char16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshlm1b_vrv                                                          */
/*----------------------------------------------------------------------------*/
/*
VSHLM1B
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __BIF __vshlm1b_vrv(__char64, signed char);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __BIF __vshlm1b_vrv(__char32, signed char);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshlm2b_vrv                                                          */
/*----------------------------------------------------------------------------*/
/*
VSHLM2B
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __BIF __vshlm2b_vrv(__char64, __char2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __BIF __vshlm2b_vrv(__char32, __char2);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshlm4b_vrv                                                          */
/*----------------------------------------------------------------------------*/
/*
VSHLM4B
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __BIF __vshlm4b_vrv(__char64, __char4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __BIF __vshlm4b_vrv(__char32, __char4);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshlm8b_vdv                                                          */
/*----------------------------------------------------------------------------*/
/*
VSHLM8B
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __BIF __vshlm8b_vdv(__char64, __char8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __BIF __vshlm8b_vdv(__char32, __char8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshlmb_vvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VSHLMB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __BIF __vshlmb_vvv(__int8, __char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __BIF __vshlmb_vvv(__int16, __char64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshlw_vkv                                                            */
/*----------------------------------------------------------------------------*/
/*
VSHLW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __OVBIF __vshlw_vkv(__int8, __int8 __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __vshlw_vkv(__int16, __int16 __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __OVBIF __vshlw_vkv(__uint8, __uint8 __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __vshlw_vkv(__uint16, __uint16 __CST(0, 63));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshlw_vvv                                                            */
/*----------------------------------------------------------------------------*/
/*
VSHLW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __OVBIF __vshlw_vvv(__int8, __int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __vshlw_vvv(__int16, __int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __OVBIF __vshlw_vvv(__uint8, __uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __vshlw_vvv(__uint16, __uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshr_vkv                                                             */
/*----------------------------------------------------------------------------*/
/*
VSHR
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __BIF __vshr_vkv(__long8, __uchar __CST(1, 64));
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __BIF __vshr_vkv(__long4, __uchar __CST(1, 64));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshr_vvv                                                             */
/*----------------------------------------------------------------------------*/
/*
VSHR
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __BIF __vshr_vvv(__long4, __ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __BIF __vshr_vvv(__long8, __ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshrb_vkv                                                            */
/*----------------------------------------------------------------------------*/
/*
VSHRB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __BIF __vshrb_vkv(__char32, __char32 __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __BIF __vshrb_vkv(__char64, __char64 __CST(0, 63));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshrb_vvv                                                            */
/*----------------------------------------------------------------------------*/
/*
VSHRB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __BIF __vshrb_vvv(__char32, __int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __BIF __vshrb_vvv(__char64, __int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshrd_vkv                                                            */
/*----------------------------------------------------------------------------*/
/*
VSHRD
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __BIF __vshrd_vkv(__long4, __long4 __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __BIF __vshrd_vkv(__long8, __long8 __CST(0, 63));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshrd_vvv                                                            */
/*----------------------------------------------------------------------------*/
/*
VSHRD
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __BIF __vshrd_vvv(__long4, __long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __BIF __vshrd_vvv(__long8, __long8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshrh_vkv                                                            */
/*----------------------------------------------------------------------------*/
/*
VSHRH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __BIF __vshrh_vkv(__short16, __short16 __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __BIF __vshrh_vkv(__short32, __short32 __CST(0, 63));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshrh_vvv                                                            */
/*----------------------------------------------------------------------------*/
/*
VSHRH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __BIF __vshrh_vvv(__short16, __int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __BIF __vshrh_vvv(__short32, __int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshrm16b_vvv                                                         */
/*----------------------------------------------------------------------------*/
/*
VSHRM16B
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __BIF __vshrm16b_vvv(__char64, __char16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __BIF __vshrm16b_vvv(__char32, __char16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshrm1b_vrv                                                          */
/*----------------------------------------------------------------------------*/
/*
VSHRM1B
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __BIF __vshrm1b_vrv(__char64, signed char);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __BIF __vshrm1b_vrv(__char32, signed char);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshrm2b_vrv                                                          */
/*----------------------------------------------------------------------------*/
/*
VSHRM2B
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __BIF __vshrm2b_vrv(__char64, __char2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __BIF __vshrm2b_vrv(__char32, __char2);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshrm4b_vrv                                                          */
/*----------------------------------------------------------------------------*/
/*
VSHRM4B
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __BIF __vshrm4b_vrv(__char64, __char4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __BIF __vshrm4b_vrv(__char32, __char4);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshrm8b_vdv                                                          */
/*----------------------------------------------------------------------------*/
/*
VSHRM8B
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __BIF __vshrm8b_vdv(__char64, __char8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __BIF __vshrm8b_vdv(__char32, __char8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshrmb_vvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VSHRMB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __BIF __vshrmb_vvv(__int8, __char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __BIF __vshrmb_vvv(__int16, __char64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshrrb_vkv                                                           */
/*----------------------------------------------------------------------------*/
/*
VSHRRB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __BIF __vshrrb_vkv(__char32, __uchar32 __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __BIF __vshrrb_vkv(__char64, __uchar64 __CST(0, 63));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshrrb_vvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VSHRRB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __BIF __vshrrb_vvv(__char32, __uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __BIF __vshrrb_vvv(__char64, __uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshrrd_vkv                                                           */
/*----------------------------------------------------------------------------*/
/*
VSHRRD
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __BIF __vshrrd_vkv(__long4, __uchar4 __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __BIF __vshrrd_vkv(__long8, __uchar8 __CST(0, 63));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshrrd_vvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VSHRRD
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __BIF __vshrrd_vvv(__long4, __ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __BIF __vshrrd_vvv(__long8, __ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshrrh_vkv                                                           */
/*----------------------------------------------------------------------------*/
/*
VSHRRH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __BIF __vshrrh_vkv(__short16, __uchar16 __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __BIF __vshrrh_vkv(__short32, __uchar32 __CST(0, 63));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshrrh_vvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VSHRRH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __BIF __vshrrh_vvv(__short16, __uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __BIF __vshrrh_vvv(__short32, __uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshrrw_vkv                                                           */
/*----------------------------------------------------------------------------*/
/*
VSHRRW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __BIF __vshrrw_vkv(__int8, __uchar8 __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __BIF __vshrrw_vkv(__int16, __uchar16 __CST(0, 63));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshrrw_vvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VSHRRW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __BIF __vshrrw_vvv(__int8, __uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __BIF __vshrrw_vvv(__int16, __uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshru_vkv                                                            */
/*----------------------------------------------------------------------------*/
/*
VSHRU
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __BIF __vshru_vkv(__ulong8, __uchar __CST(1, 64));
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __BIF __vshru_vkv(__ulong4, __uchar __CST(1, 64));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshru_vvv                                                            */
/*----------------------------------------------------------------------------*/
/*
VSHRU
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __BIF __vshru_vvv(__ulong4, __ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __BIF __vshru_vvv(__ulong8, __ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshrub_vkv                                                           */
/*----------------------------------------------------------------------------*/
/*
VSHRUB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __BIF __vshrub_vkv(__uchar32, __uchar32 __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __vshrub_vkv(__uchar64, __uchar64 __CST(0, 63));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshrub_vvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VSHRUB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __BIF __vshrub_vvv(__uchar32, __uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __vshrub_vvv(__uchar64, __uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshrud_vkv                                                           */
/*----------------------------------------------------------------------------*/
/*
VSHRUD
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __BIF __vshrud_vkv(__ulong4, __ulong4 __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __BIF __vshrud_vkv(__ulong8, __ulong8 __CST(0, 63));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshrud_vvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VSHRUD
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __BIF __vshrud_vvv(__ulong4, __ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __BIF __vshrud_vvv(__ulong8, __ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshruh_vkv                                                           */
/*----------------------------------------------------------------------------*/
/*
VSHRUH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __BIF __vshruh_vkv(__ushort16, __ushort16 __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __BIF __vshruh_vkv(__ushort32, __ushort32 __CST(0, 63));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshruh_vvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VSHRUH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __BIF __vshruh_vvv(__ushort16, __uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __BIF __vshruh_vvv(__ushort32, __uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshrurb_vkv                                                          */
/*----------------------------------------------------------------------------*/
/*
VSHRURB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __BIF __vshrurb_vkv(__uchar32, __uchar32 __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __vshrurb_vkv(__uchar64, __uchar64 __CST(0, 63));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshrurb_vvv                                                          */
/*----------------------------------------------------------------------------*/
/*
VSHRURB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __BIF __vshrurb_vvv(__uchar32, __uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __vshrurb_vvv(__uchar64, __uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshrurd_vkv                                                          */
/*----------------------------------------------------------------------------*/
/*
VSHRURD
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __BIF __vshrurd_vkv(__ulong4, __uchar4 __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __BIF __vshrurd_vkv(__ulong8, __uchar8 __CST(0, 63));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshrurd_vvv                                                          */
/*----------------------------------------------------------------------------*/
/*
VSHRURD
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __BIF __vshrurd_vvv(__ulong4, __ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __BIF __vshrurd_vvv(__ulong8, __ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshrurh_vkv                                                          */
/*----------------------------------------------------------------------------*/
/*
VSHRURH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __BIF __vshrurh_vkv(__ushort16, __uchar16 __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __BIF __vshrurh_vkv(__ushort32, __uchar32 __CST(0, 63));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshrurh_vvv                                                          */
/*----------------------------------------------------------------------------*/
/*
VSHRURH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __BIF __vshrurh_vvv(__ushort16, __uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __BIF __vshrurh_vvv(__ushort32, __uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshrurw_vkv                                                          */
/*----------------------------------------------------------------------------*/
/*
VSHRURW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __BIF __vshrurw_vkv(__uint8, __uchar8 __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __BIF __vshrurw_vkv(__uint16, __uchar16 __CST(0, 63));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshrurw_vvv                                                          */
/*----------------------------------------------------------------------------*/
/*
VSHRURW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __BIF __vshrurw_vvv(__uint8, __uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __BIF __vshrurw_vvv(__uint16, __uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshruw_vkv                                                           */
/*----------------------------------------------------------------------------*/
/*
VSHRUW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __BIF __vshruw_vkv(__uint8, __uint8 __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __BIF __vshruw_vkv(__uint16, __uint16 __CST(0, 63));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshruw_vvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VSHRUW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __BIF __vshruw_vvv(__uint8, __uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __BIF __vshruw_vvv(__uint16, __uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshrw_vkv                                                            */
/*----------------------------------------------------------------------------*/
/*
VSHRW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __BIF __vshrw_vkv(__int8, __int8 __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __BIF __vshrw_vkv(__int16, __int16 __CST(0, 63));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshrw_vvv                                                            */
/*----------------------------------------------------------------------------*/
/*
VSHRW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __BIF __vshrw_vvv(__int8, __int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __BIF __vshrw_vvv(__int16, __int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshvluw_vvv                                                          */
/*----------------------------------------------------------------------------*/
/*
VSHVLUW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __BIF __vshvluw_vvv(__uint8, __int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __BIF __vshvluw_vvv(__uint16, __int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshvlw_vvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VSHVLW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __BIF __vshvlw_vvv(__int8, __int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __BIF __vshvlw_vvv(__int16, __int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshvruw_vvv                                                          */
/*----------------------------------------------------------------------------*/
/*
VSHVRUW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __BIF __vshvruw_vvv(__uint8, __int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __BIF __vshvruw_vvv(__uint16, __int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshvrw_vvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VSHVRW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __BIF __vshvrw_vvv(__int8, __int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __BIF __vshvrw_vvv(__int16, __int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsmpyhw_vvw                                                          */
/*----------------------------------------------------------------------------*/
/*

VSMPYHW
#if __C7X_VEC_SIZE_BITS__ == 256
void __vsmpyhw_vvw(short16, short16, int8&, int8&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
void __vsmpyhw_vvw(short32, short32, int16&, int16&);
#endif

*/

/*----------------------------------------------------------------------------*/
/* ID: __vsmpyr17ww_vvv                                                       */
/*----------------------------------------------------------------------------*/
/*
VSMPYR17WW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __BIF __vsmpyr17ww_vvv(__int8, __int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __BIF __vsmpyr17ww_vvv(__int16, __int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsmpyr1hh_vvv                                                        */
/*----------------------------------------------------------------------------*/
/*
VSMPYR1HH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __BIF __vsmpyr1hh_vvv(__short16, __short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __BIF __vsmpyr1hh_vvv(__short32, __short32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsmpyr1ww_vvv                                                        */
/*----------------------------------------------------------------------------*/
/*
VSMPYR1WW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __BIF __vsmpyr1ww_vvv(__int8, __int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __BIF __vsmpyr1ww_vvv(__int16, __int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsmpyrsuhh_vvv                                                       */
/*----------------------------------------------------------------------------*/
/*
VSMPYRSUHH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __BIF __vsmpyrsuhh_vvv(__short16, __ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __BIF __vsmpyrsuhh_vvv(__short32, __ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsmpyruhh_vvv                                                        */
/*----------------------------------------------------------------------------*/
/*
VSMPYRUHH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __BIF __vsmpyruhh_vvv(__ushort16, __ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __BIF __vsmpyruhh_vvv(__ushort32, __ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsmpyww_vvv                                                          */
/*----------------------------------------------------------------------------*/
/*
VSMPYWW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __BIF __vsmpyww_vvv(__int8, __int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __BIF __vsmpyww_vvv(__int16, __int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsortdh_vv                                                           */
/*----------------------------------------------------------------------------*/
/*
VSORTDH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __BIF __vsortdh_vv(__short16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsortdsp_vv                                                          */
/*----------------------------------------------------------------------------*/
/*
VSORTDSP
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__float8 __BIF __vsortdsp_vv(__float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__float16 __BIF __vsortdsp_vv(__float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsortduh_vv                                                          */
/*----------------------------------------------------------------------------*/
/*
VSORTDUH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __BIF __vsortduh_vv(__ushort16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsortduw_vv                                                          */
/*----------------------------------------------------------------------------*/
/*
VSORTDUW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __BIF __vsortduw_vv(__uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __BIF __vsortduw_vv(__uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsortdw_vv                                                           */
/*----------------------------------------------------------------------------*/
/*
VSORTDW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __BIF __vsortdw_vv(__int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __BIF __vsortdw_vv(__int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsortih_vv                                                           */
/*----------------------------------------------------------------------------*/
/*
VSORTIH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __BIF __vsortih_vv(__short16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsortisp_vv                                                          */
/*----------------------------------------------------------------------------*/
/*
VSORTISP
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__float8 __BIF __vsortisp_vv(__float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__float16 __BIF __vsortisp_vv(__float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsortiuh_vv                                                          */
/*----------------------------------------------------------------------------*/
/*
VSORTIUH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __BIF __vsortiuh_vv(__ushort16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsortiuw_vv                                                          */
/*----------------------------------------------------------------------------*/
/*
VSORTIUW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __BIF __vsortiuw_vv(__uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __BIF __vsortiuw_vv(__uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsortiw_vv                                                           */
/*----------------------------------------------------------------------------*/
/*
VSORTIW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __BIF __vsortiw_vv(__int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __BIF __vsortiw_vv(__int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsortpdsp_vv                                                         */
/*----------------------------------------------------------------------------*/
/*
VSORTPDSP
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __vsortpdsp_vv(__float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsortpduw_vv                                                         */
/*----------------------------------------------------------------------------*/
/*
VSORTPDUW
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __vsortpduw_vv(__uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsortpdw_vv                                                          */
/*----------------------------------------------------------------------------*/
/*
VSORTPDW
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __vsortpdw_vv(__int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsortpisp_vv                                                         */
/*----------------------------------------------------------------------------*/
/*
VSORTPISP
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __vsortpisp_vv(__float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsortpiuw_vv                                                         */
/*----------------------------------------------------------------------------*/
/*
VSORTPIUW
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __vsortpiuw_vv(__uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsortpiw_vv                                                          */
/*----------------------------------------------------------------------------*/
/*
VSORTPIW
*/
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __vsortpiw_vv(__int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vspackdw_vvv                                                         */
/*----------------------------------------------------------------------------*/
/*
VSPACKDW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __BIF __vspackdw_vvv(__long4, __long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __BIF __vspackdw_vvv(__long8, __long8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vspackhb_vvv                                                         */
/*----------------------------------------------------------------------------*/
/*
VSPACKHB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __BIF __vspackhb_vvv(__short16, __short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __BIF __vspackhb_vvv(__short32, __short32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vspackudw_vvv                                                        */
/*----------------------------------------------------------------------------*/
/*
VSPACKUDW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __BIF __vspackudw_vvv(__long4, __long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __BIF __vspackudw_vvv(__long8, __long8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vspackuhb_vvv                                                        */
/*----------------------------------------------------------------------------*/
/*
VSPACKUHB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __BIF __vspackuhb_vvv(__short16, __short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __vspackuhb_vvv(__short32, __short32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vspackuwh_vvv                                                        */
/*----------------------------------------------------------------------------*/
/*
VSPACKUWH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __BIF __vspackuwh_vvv(__int8, __int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __BIF __vspackuwh_vvv(__int16, __int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vspackwh_vvv                                                         */
/*----------------------------------------------------------------------------*/
/*
VSPACKWH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __BIF __vspackwh_vvv(__int8, __int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __BIF __vspackwh_vvv(__int16, __int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vspdph_vv                                                            */
/*----------------------------------------------------------------------------*/
/*
VSPDPH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__double4 __BIF __vspdph_vv(__float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__double8 __BIF __vspdph_vv(__float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vspdpl_vv                                                            */
/*----------------------------------------------------------------------------*/
/*
VSPDPL
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__double4 __BIF __vspdpl_vv(__float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__double8 __BIF __vspdpl_vv(__float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsphp_vv                                                             */
/*----------------------------------------------------------------------------*/
/*
VSPHP
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __BIF __vsphp_vv(__float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __BIF __vsphp_vv(__float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vspint_vv                                                            */
/*----------------------------------------------------------------------------*/
/*
VSPINT
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __BIF __vspint_vv(__float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __BIF __vspint_vv(__float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vspinth_vv                                                           */
/*----------------------------------------------------------------------------*/
/*
VSPINTH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __BIF __vspinth_vv(__float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __BIF __vspinth_vv(__float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vspinthpk_vv                                                         */
/*----------------------------------------------------------------------------*/
/*
VSPINTHPK
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __BIF __vspinthpk_vv(__float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __BIF __vspinthpk_vv(__float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsptrunc_vv                                                          */
/*----------------------------------------------------------------------------*/
/*
VSPTRUNC
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __BIF __vsptrunc_vv(__float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __BIF __vsptrunc_vv(__float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsshlh_vkv                                                           */
/*----------------------------------------------------------------------------*/
/*
VSSHLH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __BIF __vsshlh_vkv(__short16, __uchar16 __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __BIF __vsshlh_vkv(__short32, __uchar32 __CST(0, 63));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsshlh_vvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VSSHLH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __BIF __vsshlh_vvv(__short16, __uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __BIF __vsshlh_vvv(__short32, __uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsshlrdw_vkv                                                         */
/*----------------------------------------------------------------------------*/
/*
VSSHLRDW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __BIF __vsshlrdw_vkv(__long4, __uchar4 __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __BIF __vsshlrdw_vkv(__long8, __uchar8 __CST(0, 63));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsshlrdw_vvv                                                         */
/*----------------------------------------------------------------------------*/
/*
VSSHLRDW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __BIF __vsshlrdw_vvv(__long4, __ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __BIF __vsshlrdw_vvv(__long8, __ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsshlrhb_vkv                                                         */
/*----------------------------------------------------------------------------*/
/*
VSSHLRHB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __BIF __vsshlrhb_vkv(__short16, __uchar8 __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __BIF __vsshlrhb_vkv(__short32, __uchar16 __CST(0, 63));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsshlrhb_vvv                                                         */
/*----------------------------------------------------------------------------*/
/*
VSSHLRHB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __BIF __vsshlrhb_vvv(__short16, __uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __BIF __vsshlrhb_vvv(__short32, __uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsshlrwh_vkv                                                         */
/*----------------------------------------------------------------------------*/
/*
VSSHLRWH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __BIF __vsshlrwh_vkv(__int8, __uchar8 __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __BIF __vsshlrwh_vkv(__int16, __uchar16 __CST(0, 63));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsshlrwh_vvv                                                         */
/*----------------------------------------------------------------------------*/
/*
VSSHLRWH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __BIF __vsshlrwh_vvv(__int8, __uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __BIF __vsshlrwh_vvv(__int16, __uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsshlsuh_vkv                                                         */
/*----------------------------------------------------------------------------*/
/*
VSSHLSUH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __BIF __vsshlsuh_vkv(__short16, __uchar16 __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __BIF __vsshlsuh_vkv(__short32, __uchar32 __CST(0, 63));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsshlsuh_vvv                                                         */
/*----------------------------------------------------------------------------*/
/*
VSSHLSUH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __BIF __vsshlsuh_vvv(__short16, __uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __BIF __vsshlsuh_vvv(__short32, __uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsshlsurdw_vkv                                                       */
/*----------------------------------------------------------------------------*/
/*
VSSHLSURDW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __BIF __vsshlsurdw_vkv(__long4, __uchar4 __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __BIF __vsshlsurdw_vkv(__long8, __uchar8 __CST(0, 63));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsshlsurdw_vvv                                                       */
/*----------------------------------------------------------------------------*/
/*
VSSHLSURDW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __BIF __vsshlsurdw_vvv(__long4, __ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __BIF __vsshlsurdw_vvv(__long8, __ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsshlsurhb_vkv                                                       */
/*----------------------------------------------------------------------------*/
/*
VSSHLSURHB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __BIF __vsshlsurhb_vkv(__short16, __uchar8 __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __vsshlsurhb_vkv(__short32, __uchar16 __CST(0, 63));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsshlsurhb_vvv                                                       */
/*----------------------------------------------------------------------------*/
/*
VSSHLSURHB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __BIF __vsshlsurhb_vvv(__short16, __uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __vsshlsurhb_vvv(__short32, __uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsshlsurwh_vkv                                                       */
/*----------------------------------------------------------------------------*/
/*
VSSHLSURWH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __BIF __vsshlsurwh_vkv(__int8, __uchar8 __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __BIF __vsshlsurwh_vkv(__int16, __uchar16 __CST(0, 63));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsshlsurwh_vvv                                                       */
/*----------------------------------------------------------------------------*/
/*
VSSHLSURWH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __BIF __vsshlsurwh_vvv(__int8, __uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __BIF __vsshlsurwh_vvv(__int16, __uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsshlsuw_vkv                                                         */
/*----------------------------------------------------------------------------*/
/*
VSSHLSUW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __BIF __vsshlsuw_vkv(__int8, __uchar8 __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __BIF __vsshlsuw_vkv(__int16, __uchar16 __CST(0, 63));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsshlsuw_vvv                                                         */
/*----------------------------------------------------------------------------*/
/*
VSSHLSUW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __BIF __vsshlsuw_vvv(__int8, __uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __BIF __vsshlsuw_vvv(__int16, __uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsshluh_vkv                                                          */
/*----------------------------------------------------------------------------*/
/*
VSSHLUH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __BIF __vsshluh_vkv(__ushort16, __uchar16 __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __BIF __vsshluh_vkv(__ushort32, __uchar32 __CST(0, 63));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsshluh_vvv                                                          */
/*----------------------------------------------------------------------------*/
/*
VSSHLUH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __BIF __vsshluh_vvv(__ushort16, __uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __BIF __vsshluh_vvv(__ushort32, __uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsshlurdw_vkv                                                        */
/*----------------------------------------------------------------------------*/
/*
VSSHLURDW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __BIF __vsshlurdw_vkv(__ulong4, __uchar4 __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __BIF __vsshlurdw_vkv(__ulong8, __uchar8 __CST(0, 63));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsshlurdw_vvv                                                        */
/*----------------------------------------------------------------------------*/
/*
VSSHLURDW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __BIF __vsshlurdw_vvv(__ulong4, __ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __BIF __vsshlurdw_vvv(__ulong8, __ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsshlurhb_vkv                                                        */
/*----------------------------------------------------------------------------*/
/*
VSSHLURHB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __BIF __vsshlurhb_vkv(__ushort16, __uchar8 __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __vsshlurhb_vkv(__ushort32, __uchar16 __CST(0, 63));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsshlurhb_vvv                                                        */
/*----------------------------------------------------------------------------*/
/*
VSSHLURHB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __BIF __vsshlurhb_vvv(__ushort16, __uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __vsshlurhb_vvv(__ushort32, __uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsshlurwh_vkv                                                        */
/*----------------------------------------------------------------------------*/
/*
VSSHLURWH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __BIF __vsshlurwh_vkv(__uint8, __uchar8 __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __BIF __vsshlurwh_vkv(__uint16, __uchar16 __CST(0, 63));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsshlurwh_vvv                                                        */
/*----------------------------------------------------------------------------*/
/*
VSSHLURWH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __BIF __vsshlurwh_vvv(__uint8, __uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __BIF __vsshlurwh_vvv(__uint16, __uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsshluw_vkv                                                          */
/*----------------------------------------------------------------------------*/
/*
VSSHLUW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __BIF __vsshluw_vkv(__uint8, __uchar8 __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __BIF __vsshluw_vkv(__uint16, __uchar16 __CST(0, 63));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsshluw_vvv                                                          */
/*----------------------------------------------------------------------------*/
/*
VSSHLUW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __BIF __vsshluw_vvv(__uint8, __uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __BIF __vsshluw_vvv(__uint16, __uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsshlw_vkv                                                           */
/*----------------------------------------------------------------------------*/
/*
VSSHLW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __BIF __vsshlw_vkv(__int8, __uchar8 __CST(0, 63));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __BIF __vsshlw_vkv(__int16, __uchar16 __CST(0, 63));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsshlw_vvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VSSHLW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __BIF __vsshlw_vvv(__int8, __uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __BIF __vsshlw_vvv(__int16, __uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsshvlw_vvv                                                          */
/*----------------------------------------------------------------------------*/
/*
VSSHVLW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __BIF __vsshvlw_vvv(__int8, __int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __BIF __vsshvlw_vvv(__int16, __int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsshvrw_vvv                                                          */
/*----------------------------------------------------------------------------*/
/*
VSSHVRW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __BIF __vsshvrw_vvv(__int8, __int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __BIF __vsshvrw_vvv(__int16, __int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vssubb_vkv                                                           */
/*----------------------------------------------------------------------------*/
/*
VSSUBB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __BIF __vssubb_vkv(__char32, __char32 __CST(-128, 127));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __BIF __vssubb_vkv(__char64, __char64 __CST(-128, 127));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vssubb_vvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VSSUBB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __OVBIF __vssubb_vvv(__char32, __char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __vssubb_vvv(__char64, __char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cchar16 __OVBIF __vssubb_vvv(__cchar16, __cchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cchar32 __OVBIF __vssubb_vvv(__cchar32, __cchar32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vssubh_vkv                                                           */
/*----------------------------------------------------------------------------*/
/*
VSSUBH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __BIF __vssubh_vkv(__short16, __short16 __CST(-32768, 32767));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __BIF __vssubh_vkv(__short32, __short32 __CST(-32768, 32767));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vssubh_vvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VSSUBH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __OVBIF __vssubh_vvv(__short16, __short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __vssubh_vvv(__short32, __short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cshort8 __OVBIF __vssubh_vvv(__cshort8, __cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cshort16 __OVBIF __vssubh_vvv(__cshort16, __cshort16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vssubw_vkv                                                           */
/*----------------------------------------------------------------------------*/
/*
VSSUBW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __BIF __vssubw_vkv(__int8, __int8 __CST(-2147483648, 2147483647));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __BIF __vssubw_vkv(__int16, __int16 __CST(-2147483648, 2147483647));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vssubw_vvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VSSUBW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __OVBIF __vssubw_vvv(__int8, __int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __vssubw_vvv(__int16, __int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cint4 __OVBIF __vssubw_vvv(__cint4, __cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cint8 __OVBIF __vssubw_vvv(__cint8, __cint8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsubabsb_vvv                                                         */
/*----------------------------------------------------------------------------*/
/*
VSUBABSB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __BIF __vsubabsb_vvv(__uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __BIF __vsubabsb_vvv(__uchar64, __uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsubabsd_vvv                                                         */
/*----------------------------------------------------------------------------*/
/*
VSUBABSD
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __BIF __vsubabsd_vvv(__ulong4, __ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __BIF __vsubabsd_vvv(__ulong8, __ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsubabsh_vvv                                                         */
/*----------------------------------------------------------------------------*/
/*
VSUBABSH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __BIF __vsubabsh_vvv(__ushort16, __ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __BIF __vsubabsh_vvv(__ushort32, __ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsubabsw_vvv                                                         */
/*----------------------------------------------------------------------------*/
/*
VSUBABSW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __BIF __vsubabsw_vvv(__uint8, __uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __BIF __vsubabsw_vvv(__uint16, __uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsubb_vkv                                                            */
/*----------------------------------------------------------------------------*/
/*
VSUBB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __OVBIF __vsubb_vkv(__char32, __char32 __CST(-128, 127));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __vsubb_vkv(__char64, __char64 __CST(-128, 127));
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __OVBIF __vsubb_vkv(__uchar32, __uchar32 __CST(0, 255));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __vsubb_vkv(__uchar64, __uchar64 __CST(0, 255));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsubb_vvv                                                            */
/*----------------------------------------------------------------------------*/
/*
VSUBB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __OVBIF __vsubb_vvv(__char32, __char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __vsubb_vvv(__char64, __char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __OVBIF __vsubb_vvv(__uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __vsubb_vvv(__uchar64, __uchar64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cchar16 __OVBIF __vsubb_vvv(__cchar16, __cchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cchar32 __OVBIF __vsubb_vvv(__cchar32, __cchar32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsubcw_vvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VSUBCW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __BIF __vsubcw_vvv(__uint8, __uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __BIF __vsubcw_vvv(__uint16, __uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsubd_vkv                                                            */
/*----------------------------------------------------------------------------*/
/*
VSUBD
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __OVBIF __vsubd_vkv(__long4, __int4 __CST(-2147483648, 2147483647));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __vsubd_vkv(__long8, __int8 __CST(-2147483648, 2147483647));
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __OVBIF __vsubd_vkv(__ulong4, __uint4 __CST(0, 2147483647));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __vsubd_vkv(__ulong8, __uint8 __CST(0, 2147483647));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsubd_vvv                                                            */
/*----------------------------------------------------------------------------*/
/*
VSUBD
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __OVBIF __vsubd_vvv(__long4, __long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __vsubd_vvv(__long8, __long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __OVBIF __vsubd_vvv(__ulong4, __ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __vsubd_vvv(__ulong8, __ulong8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__clong2 __OVBIF __vsubd_vvv(__clong2, __clong2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__clong4 __OVBIF __vsubd_vvv(__clong4, __clong4);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsubdp_vvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VSUBDP
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__double4 __OVBIF __vsubdp_vvv(__double4, __double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__double8 __OVBIF __vsubdp_vvv(__double8, __double8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cdouble2 __OVBIF __vsubdp_vvv(__cdouble2, __cdouble2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cdouble4 __OVBIF __vsubdp_vvv(__cdouble4, __cdouble4);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsubh_vkv                                                            */
/*----------------------------------------------------------------------------*/
/*
VSUBH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __OVBIF __vsubh_vkv(__short16, __short16 __CST(-32768, 32767));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __vsubh_vkv(__short32, __short32 __CST(-32768, 32767));
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __OVBIF __vsubh_vkv(__ushort16, __ushort16 __CST(0, 65535));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __vsubh_vkv(__ushort32, __ushort32 __CST(0, 65535));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsubh_vvv                                                            */
/*----------------------------------------------------------------------------*/
/*
VSUBH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __OVBIF __vsubh_vvv(__short16, __short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __vsubh_vvv(__short32, __short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __OVBIF __vsubh_vvv(__ushort16, __ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __vsubh_vvv(__ushort32, __ushort32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cshort8 __OVBIF __vsubh_vvv(__cshort8, __cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cshort16 __OVBIF __vsubh_vvv(__cshort16, __cshort16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsubrb_vkv                                                           */
/*----------------------------------------------------------------------------*/
/*
VSUBRB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __OVBIF __vsubrb_vkv(__char32, __char32 __CST(-128, 127));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __vsubrb_vkv(__char64, __char64 __CST(-128, 127));
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __OVBIF __vsubrb_vkv(__uchar32, __uchar32 __CST(0, 255));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __vsubrb_vkv(__uchar64, __uchar64 __CST(0, 255));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsubrb_vvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VSUBRB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __OVBIF __vsubrb_vvv(__char32, __char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __vsubrb_vvv(__char64, __char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __OVBIF __vsubrb_vvv(__uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __vsubrb_vvv(__uchar64, __uchar64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cchar16 __OVBIF __vsubrb_vvv(__cchar16, __cchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cchar32 __OVBIF __vsubrb_vvv(__cchar32, __cchar32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsubrd_vkv                                                           */
/*----------------------------------------------------------------------------*/
/*
VSUBRD
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __OVBIF __vsubrd_vkv(__long4, __int4 __CST(-2147483648, 2147483647));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __vsubrd_vkv(__long8, __int8 __CST(-2147483648, 2147483647));
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __OVBIF __vsubrd_vkv(__ulong4, __uint4 __CST(0, 2147483647));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __vsubrd_vkv(__ulong8, __uint8 __CST(0, 2147483647));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsubrd_vvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VSUBRD
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __OVBIF __vsubrd_vvv(__long4, __long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __vsubrd_vvv(__long8, __long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __OVBIF __vsubrd_vvv(__ulong4, __ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __vsubrd_vvv(__ulong8, __ulong8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__clong2 __OVBIF __vsubrd_vvv(__clong2, __clong2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__clong4 __OVBIF __vsubrd_vvv(__clong4, __clong4);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsubrh_vkv                                                           */
/*----------------------------------------------------------------------------*/
/*
VSUBRH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __OVBIF __vsubrh_vkv(__short16, __short16 __CST(-32768, 32767));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __vsubrh_vkv(__short32, __short32 __CST(-32768, 32767));
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __OVBIF __vsubrh_vkv(__ushort16, __ushort16 __CST(0, 65535));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __vsubrh_vkv(__ushort32, __ushort32 __CST(0, 65535));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsubrh_vvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VSUBRH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __OVBIF __vsubrh_vvv(__short16, __short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __vsubrh_vvv(__short32, __short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __OVBIF __vsubrh_vvv(__ushort16, __ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __vsubrh_vvv(__ushort32, __ushort32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cshort8 __OVBIF __vsubrh_vvv(__cshort8, __cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cshort16 __OVBIF __vsubrh_vvv(__cshort16, __cshort16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsubrw_vkv                                                           */
/*----------------------------------------------------------------------------*/
/*
VSUBRW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __OVBIF __vsubrw_vkv(__int8, __int8 __CST(-2147483648, 2147483647));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __vsubrw_vkv(__int16, __int16 __CST(-2147483648, 2147483647));
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __OVBIF __vsubrw_vkv(__uint8, __uint8 __CST(0, 4294967295));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __vsubrw_vkv(__uint16, __uint16 __CST(0, 4294967295));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsubrw_vvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VSUBRW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __OVBIF __vsubrw_vvv(__int8, __int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __vsubrw_vvv(__int16, __int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __OVBIF __vsubrw_vvv(__uint8, __uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __vsubrw_vvv(__uint16, __uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cint4 __OVBIF __vsubrw_vvv(__cint4, __cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cint8 __OVBIF __vsubrw_vvv(__cint8, __cint8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsubsp_vvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VSUBSP
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__float8 __OVBIF __vsubsp_vvv(__float8, __float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__float16 __OVBIF __vsubsp_vvv(__float16, __float16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cfloat4 __OVBIF __vsubsp_vvv(__cfloat4, __cfloat4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cfloat8 __OVBIF __vsubsp_vvv(__cfloat8, __cfloat8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsubw_vkv                                                            */
/*----------------------------------------------------------------------------*/
/*
VSUBW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __OVBIF __vsubw_vkv(__int8, __int8 __CST(-2147483648, 2147483647));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __vsubw_vkv(__int16, __int16 __CST(-2147483648, 2147483647));
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __OVBIF __vsubw_vkv(__uint8, __uint8 __CST(0, 4294967295));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __vsubw_vkv(__uint16, __uint16 __CST(0, 4294967295));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsubw_vvv                                                            */
/*----------------------------------------------------------------------------*/
/*
VSUBW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __OVBIF __vsubw_vvv(__int8, __int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __vsubw_vvv(__int16, __int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __OVBIF __vsubw_vvv(__uint8, __uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __vsubw_vvv(__uint16, __uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cint4 __OVBIF __vsubw_vvv(__cint4, __cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cint8 __OVBIF __vsubw_vvv(__cint8, __cint8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vswapb_vv                                                            */
/*----------------------------------------------------------------------------*/
/*
VSWAPB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __OVBIF __vswapb_vv(__char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __vswapb_vv(__char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __OVBIF __vswapb_vv(__uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __vswapb_vv(__uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vswapd_vv                                                            */
/*----------------------------------------------------------------------------*/
/*
VSWAPD
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cint4 __OVBIF __vswapd_vv(__cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cint8 __OVBIF __vswapd_vv(__cint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__cfloat4 __OVBIF __vswapd_vv(__cfloat4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cfloat8 __OVBIF __vswapd_vv(__cfloat8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __OVBIF __vswapd_vv(__long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __vswapd_vv(__long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __OVBIF __vswapd_vv(__ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __vswapd_vv(__ulong8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__double4 __OVBIF __vswapd_vv(__double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__double8 __OVBIF __vswapd_vv(__double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vswaph_vv                                                            */
/*----------------------------------------------------------------------------*/
/*
VSWAPH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cchar16 __OVBIF __vswaph_vv(__cchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cchar32 __OVBIF __vswaph_vv(__cchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __OVBIF __vswaph_vv(__short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __vswaph_vv(__short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __OVBIF __vswaph_vv(__ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __vswaph_vv(__ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vswapw_vv                                                            */
/*----------------------------------------------------------------------------*/
/*
VSWAPW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cshort8 __OVBIF __vswapw_vv(__cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cshort16 __OVBIF __vswapw_vv(__cshort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __OVBIF __vswapw_vv(__int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __vswapw_vv(__int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __OVBIF __vswapw_vv(__uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __vswapw_vv(__uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__float8 __OVBIF __vswapw_vv(__float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__float16 __OVBIF __vswapw_vv(__float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vunpkhb_vv                                                           */
/*----------------------------------------------------------------------------*/
/*
VUNPKHB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __BIF __vunpkhb_vv(__char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __BIF __vunpkhb_vv(__char64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vunpkhh_vv                                                           */
/*----------------------------------------------------------------------------*/
/*
VUNPKHH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __BIF __vunpkhh_vv(__short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __BIF __vunpkhh_vv(__short32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vunpkhub_vv                                                          */
/*----------------------------------------------------------------------------*/
/*
VUNPKHUB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __BIF __vunpkhub_vv(__uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __BIF __vunpkhub_vv(__uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vunpkhuh_vv                                                          */
/*----------------------------------------------------------------------------*/
/*
VUNPKHUH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __BIF __vunpkhuh_vv(__ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __BIF __vunpkhuh_vv(__ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vunpklb_vv                                                           */
/*----------------------------------------------------------------------------*/
/*
VUNPKLB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __BIF __vunpklb_vv(__char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __BIF __vunpklb_vv(__char64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vunpklh_vv                                                           */
/*----------------------------------------------------------------------------*/
/*
VUNPKLH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __BIF __vunpklh_vv(__short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __BIF __vunpklh_vv(__short32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vunpklub_vv                                                          */
/*----------------------------------------------------------------------------*/
/*
VUNPKLUB
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __BIF __vunpklub_vv(__uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __BIF __vunpklub_vv(__uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vunpkluh_vv                                                          */
/*----------------------------------------------------------------------------*/
/*
VUNPKLUH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __BIF __vunpkluh_vv(__ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __BIF __vunpkluh_vv(__ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vunpkluw_vv                                                          */
/*----------------------------------------------------------------------------*/
/*
VUNPKLUW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __BIF __vunpkluw_vv(__uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __BIF __vunpkluw_vv(__uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vunpklw_vv                                                           */
/*----------------------------------------------------------------------------*/
/*
VUNPKLW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __BIF __vunpklw_vv(__int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __BIF __vunpklw_vv(__int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vwpackh_vvv                                                          */
/*----------------------------------------------------------------------------*/
/*
VWPACKH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cshort8 __OVBIF __vwpackh_vvv(__cshort8, __cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cshort16 __OVBIF __vwpackh_vvv(__cshort16, __cshort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __OVBIF __vwpackh_vvv(__int8, __int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __vwpackh_vvv(__int16, __int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __OVBIF __vwpackh_vvv(__uint8, __uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __vwpackh_vvv(__uint16, __uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__float8 __OVBIF __vwpackh_vvv(__float8, __float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__float16 __OVBIF __vwpackh_vvv(__float16, __float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vwpackl_vvv                                                          */
/*----------------------------------------------------------------------------*/
/*
VWPACKL
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__cshort8 __OVBIF __vwpackl_vvv(__cshort8, __cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__cshort16 __OVBIF __vwpackl_vvv(__cshort16, __cshort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __OVBIF __vwpackl_vvv(__int8, __int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __vwpackl_vvv(__int16, __int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __OVBIF __vwpackl_vvv(__uint8, __uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __vwpackl_vvv(__uint16, __uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__float8 __OVBIF __vwpackl_vvv(__float8, __float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__float16 __OVBIF __vwpackl_vvv(__float16, __float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vwunpkd_vv                                                           */
/*----------------------------------------------------------------------------*/
/*
VWUNPKD
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __OVBIF __vwunpkd_vv(__int4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __vwunpkd_vv(__int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__clong2 __OVBIF __vwunpkd_vv(__cint2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__clong4 __OVBIF __vwunpkd_vv(__cint4);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vwunpkdh_vv                                                          */
/*----------------------------------------------------------------------------*/
/*
VWUNPKDH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __BIF __vwunpkdh_vv(__int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __BIF __vwunpkdh_vv(__int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vwunpkdl_vv                                                          */
/*----------------------------------------------------------------------------*/
/*
VWUNPKDL
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __BIF __vwunpkdl_vv(__int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __BIF __vwunpkdl_vv(__int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vwunpkdu_vv                                                          */
/*----------------------------------------------------------------------------*/
/*
VWUNPKDU
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __BIF __vwunpkdu_vv(__uint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __BIF __vwunpkdu_vv(__uint8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vwunpkudh_vv                                                         */
/*----------------------------------------------------------------------------*/
/*
VWUNPKUDH
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __BIF __vwunpkudh_vv(__uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __BIF __vwunpkudh_vv(__uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vwunpkudl_vv                                                         */
/*----------------------------------------------------------------------------*/
/*
VWUNPKUDL
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __BIF __vwunpkudl_vv(__uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __BIF __vwunpkudl_vv(__uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vxnorw_vvv                                                           */
/*----------------------------------------------------------------------------*/
/*
VXNORW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __OVBIF __vxnorw_vvv(__char32, __char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __vxnorw_vvv(__char64, __char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __OVBIF __vxnorw_vvv(__uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __vxnorw_vvv(__uchar64, __uchar64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __OVBIF __vxnorw_vvv(__short16, __short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __vxnorw_vvv(__short32, __short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __OVBIF __vxnorw_vvv(__ushort16, __ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __vxnorw_vvv(__ushort32, __ushort32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __OVBIF __vxnorw_vvv(__int8, __int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __vxnorw_vvv(__int16, __int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __OVBIF __vxnorw_vvv(__uint8, __uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __vxnorw_vvv(__uint16, __uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __OVBIF __vxnorw_vvv(__long4, __long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __vxnorw_vvv(__long8, __long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __OVBIF __vxnorw_vvv(__ulong4, __ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __vxnorw_vvv(__ulong8, __ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vxormpyw_vvv                                                         */
/*----------------------------------------------------------------------------*/
/*
VXORMPYW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __BIF __vxormpyw_vvv(__uint8, __uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __BIF __vxormpyw_vvv(__uint16, __uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vxorw_vkv                                                            */
/*----------------------------------------------------------------------------*/
/*
VXORW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __OVBIF __vxorw_vkv(__int8, __int8 __CST(-2147483648, 2147483647));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __vxorw_vkv(__int16, __int16 __CST(-2147483648, 2147483647));
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __OVBIF __vxorw_vkv(__uint8, __uint8 __CST(0, 4294967295));
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __vxorw_vkv(__uint16, __uint16 __CST(0, 4294967295));
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vxorw_vvv                                                            */
/*----------------------------------------------------------------------------*/
/*
VXORW
*/
#if __C7X_VEC_SIZE_BITS__ == 256
__char32 __OVBIF __vxorw_vvv(__char32, __char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__char64 __OVBIF __vxorw_vvv(__char64, __char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uchar32 __OVBIF __vxorw_vvv(__uchar32, __uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uchar64 __OVBIF __vxorw_vvv(__uchar64, __uchar64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__short16 __OVBIF __vxorw_vvv(__short16, __short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__short32 __OVBIF __vxorw_vvv(__short32, __short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ushort16 __OVBIF __vxorw_vvv(__ushort16, __ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ushort32 __OVBIF __vxorw_vvv(__ushort32, __ushort32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__int8 __OVBIF __vxorw_vvv(__int8, __int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__int16 __OVBIF __vxorw_vvv(__int16, __int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__uint8 __OVBIF __vxorw_vvv(__uint8, __uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __OVBIF __vxorw_vvv(__uint16, __uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__long4 __OVBIF __vxorw_vvv(__long4, __long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__long8 __OVBIF __vxorw_vvv(__long8, __long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
__ulong4 __OVBIF __vxorw_vvv(__ulong4, __ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
__ulong8 __OVBIF __vxorw_vvv(__ulong8, __ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __xnor_ppp                                                             */
/*----------------------------------------------------------------------------*/
/*
XNOR
*/
__vpred __BIF __xnor_ppp(__vpred, __vpred);

/*----------------------------------------------------------------------------*/
/* ID: __xnord_ddd                                                            */
/*----------------------------------------------------------------------------*/
/*
XNORD
*/
__char8 __OVBIF __xnord_ddd(__char8, __char8);
__uchar8 __OVBIF __xnord_ddd(__uchar8, __uchar8);
__short4 __OVBIF __xnord_ddd(__short4, __short4);
__ushort4 __OVBIF __xnord_ddd(__ushort4, __ushort4);
__int2 __OVBIF __xnord_ddd(__int2, __int2);
__uint2 __OVBIF __xnord_ddd(__uint2, __uint2);
long __OVBIF __xnord_ddd(long, long);
__ulong __OVBIF __xnord_ddd(__ulong, __ulong);

/*----------------------------------------------------------------------------*/
/* ID: __xnord_dkd                                                            */
/*----------------------------------------------------------------------------*/
/*
XNORD
*/
long __OVBIF __xnord_dkd(long, int __CST(-2147483648, 2147483647));
__ulong __OVBIF __xnord_dkd(__ulong, __uint __CST(0, 2147483647));

/*----------------------------------------------------------------------------*/
/* ID: __xnorw_rrr                                                            */
/*----------------------------------------------------------------------------*/
/*
XNORW
*/
__char4 __OVBIF __xnorw_rrr(__char4, __char4);
__uchar4 __OVBIF __xnorw_rrr(__uchar4, __uchar4);
__short2 __OVBIF __xnorw_rrr(__short2, __short2);
__ushort2 __OVBIF __xnorw_rrr(__ushort2, __ushort2);
int __OVBIF __xnorw_rrr(int, int);
__uint __OVBIF __xnorw_rrr(__uint, __uint);

/*----------------------------------------------------------------------------*/
/* ID: __xor_ppp                                                              */
/*----------------------------------------------------------------------------*/
/*
XOR
*/
__vpred __BIF __xor_ppp(__vpred, __vpred);

/*----------------------------------------------------------------------------*/
/* ID: __xord_ddd                                                             */
/*----------------------------------------------------------------------------*/
/*
XORD
*/
__char8 __OVBIF __xord_ddd(__char8, __char8);
__uchar8 __OVBIF __xord_ddd(__uchar8, __uchar8);
__short4 __OVBIF __xord_ddd(__short4, __short4);
__ushort4 __OVBIF __xord_ddd(__ushort4, __ushort4);
__int2 __OVBIF __xord_ddd(__int2, __int2);
__uint2 __OVBIF __xord_ddd(__uint2, __uint2);
long __OVBIF __xord_ddd(long, long);
__ulong __OVBIF __xord_ddd(__ulong, __ulong);

/*----------------------------------------------------------------------------*/
/* ID: __xord_dkd                                                             */
/*----------------------------------------------------------------------------*/
/*
XORD
*/
long __OVBIF __xord_dkd(long, int __CST(-2147483648, 2147483647));
__ulong __OVBIF __xord_dkd(__ulong, __uint __CST(0, 2147483647));

/*----------------------------------------------------------------------------*/
/* ID: __xorw_rkr                                                             */
/*----------------------------------------------------------------------------*/
/*
XORW
*/
__char4 __OVBIF __xorw_rkr(__char4, __char4 __CST(-128, 127));
__uchar4 __OVBIF __xorw_rkr(__uchar4, __uchar4 __CST(0, 255));
__short2 __OVBIF __xorw_rkr(__short2, __short2 __CST(-32768, 32767));
__ushort2 __OVBIF __xorw_rkr(__ushort2, __ushort2 __CST(0, 65535));
int __OVBIF __xorw_rkr(int, int __CST(-2147483648, 2147483647));
__uint __OVBIF __xorw_rkr(__uint, __uint __CST(0, 4294967295));

/*----------------------------------------------------------------------------*/
/* ID: __xorw_rrr                                                             */
/*----------------------------------------------------------------------------*/
/*
XORW
*/
__char4 __OVBIF __xorw_rrr(__char4, __char4);
__uchar4 __OVBIF __xorw_rrr(__uchar4, __uchar4);
__short2 __OVBIF __xorw_rrr(__short2, __short2);
__ushort2 __OVBIF __xorw_rrr(__ushort2, __ushort2);
int __OVBIF __xorw_rrr(int, int);
__uint __OVBIF __xorw_rrr(__uint, __uint);

/*----------------------------------------------------------------------------*/
/* ID: __xpnd4h_rd                                                            */
/*----------------------------------------------------------------------------*/
/*
XPND4H
*/
__short4 __OVBIF __xpnd4h_rd(signed char);
__ushort4 __OVBIF __xpnd4h_rd(__uchar);

/*----------------------------------------------------------------------------*/
/* ID: __xpnd8b_rd                                                            */
/*----------------------------------------------------------------------------*/
/*
XPND8B
*/
__char8 __OVBIF __xpnd8b_rd(signed char);
__uchar8 __OVBIF __xpnd8b_rd(__uchar);

/* AUTOGEN MARKER */

#endif /* __C7X_DIRECT_H */
