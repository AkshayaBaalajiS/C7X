/*****************************************************************************/
/*  C7X_DIRECT.H                                                             */
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
#ifndef C7X_H_INCLUDE
#error "This file can only be included by parent header c7x.h"
#endif

#ifndef C7X_DIRECT_H
#define C7X_DIRECT_H

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
/* VCCMATMPYHW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern void __vccmatmpyhw_se_vww(cshort8,  __SE_REG_PAIR, cint4&, cint4&);
#elif __C7X_VEC_SIZE_BITS__ == 512
extern void __vccmatmpyhw_se_vww(cshort16, __SE_REG_PAIR, cint8&, cint8&);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vccmatmpyr1hh_se_vwv                                                 */
/*----------------------------------------------------------------------------*/
/* VCCMATMPYR1HH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cshort8  __vccmatmpyr1hh_se_vwv(cshort8,  __SE_REG_PAIR);
#elif __C7X_VEC_SIZE_BITS__ == 512
extern cshort16 __vccmatmpyr1hh_se_vwv(cshort16, __SE_REG_PAIR);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcmatmpyhw_se_vww                                                    */
/*----------------------------------------------------------------------------*/
/* VCMATMPYHW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern void __vcmatmpyhw_se_vww(cshort8,  __SE_REG_PAIR, cint4&, cint4&);
#elif __C7X_VEC_SIZE_BITS__ == 512
extern void __vcmatmpyhw_se_vww(cshort16, __SE_REG_PAIR, cint8&, cint8&);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcmatmpyr1hh_se_vwv                                                  */
/*----------------------------------------------------------------------------*/
/* VCMATMPYR1HH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cshort8  __vcmatmpyr1hh_se_vwv(cshort8, __SE_REG_PAIR);
#elif __C7X_VEC_SIZE_BITS__ == 512
extern cshort16 __vcmatmpyr1hh_se_vwv(cshort16, __SE_REG_PAIR);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdotp4hw_se1_wwv                                                     */
/*----------------------------------------------------------------------------*/
/* VDOTP4HW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8  __vdotp4hw_se1_wwv(__SE_REG_PAIR, short16, short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vdotp4hw_se1_wwv(__SE_REG_PAIR, short32, short32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdotp4hw_se2_wwv                                                     */
/*----------------------------------------------------------------------------*/
/* VDOTP4HW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8  __vdotp4hw_se2_wwv(short16, short16, __SE_REG_PAIR);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vdotp4hw_se2_wwv(short32, short32, __SE_REG_PAIR);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdotp4hw_se12_wwv                                                    */
/*----------------------------------------------------------------------------*/
/* VDOTP4HW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8  __vdotp4hw_se12_wwv(__SE_REG_PAIR, __SE_REG_PAIR);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vdotp4hw_se12_wwv(__SE_REG_PAIR, __SE_REG_PAIR);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdotp4suhw_se1_wwv                                                   */
/*----------------------------------------------------------------------------*/
/* VDOTP4SUHW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8  __vdotp4suhw_se1_wwv(__SE_REG_PAIR, ushort16, ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vdotp4suhw_se1_wwv(__SE_REG_PAIR, ushort32, ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdotp4suhw_se2_wwv                                                   */
/*----------------------------------------------------------------------------*/
/* VDOTP4SUHW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8  __vdotp4suhw_se2_wwv(short16, short16, __SE_REG_PAIR);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vdotp4suhw_se2_wwv(short32, short32, __SE_REG_PAIR);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdotp4suhw_se12_wwv                                                  */
/*----------------------------------------------------------------------------*/
/* VDOTP4SUHW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8  __vdotp4suhw_se12_wwv(__SE_REG_PAIR, __SE_REG_PAIR);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vdotp4suhw_se12_wwv(__SE_REG_PAIR, __SE_REG_PAIR);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vfir4hw_vww                                                          */
/*----------------------------------------------------------------------------*/
/* VFIR4HW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern void __vfir4hw_vww(short16, __SE_REG_PAIR,  int8&,  int8&);
#elif __C7X_VEC_SIZE_BITS__ == 512
extern void __vfir4hw_vww(short32, __SE_REG_PAIR, int16&, int16&);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vfir4suhw_vww                                                        */
/*----------------------------------------------------------------------------*/

/* VFIR4SUHW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern void __vfir4suhw_vww(short16, __SE_REG_PAIR, int8&,  int8&);
#elif __C7X_VEC_SIZE_BITS__ == 512
extern void __vfir4suhw_vww(short32, __SE_REG_PAIR, int16&, int16&);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vfir4uhw_vww                                                         */
/*----------------------------------------------------------------------------*/
/* VFIR4UHW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern void __vfir4uhw_vww(ushort16, __SE_REG_PAIR,  uint8&, uint8&);
#elif __C7X_VEC_SIZE_BITS__ == 512
extern void __vfir4uhw_vww(ushort32, __SE_REG_PAIR, uint16&, uint16&);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vfir8hd_wvw                                                          */
/*----------------------------------------------------------------------------*/
/* VFIR8HD */
#if __C7X_VEC_SIZE_BITS__ == 256
extern void __vfir8hd_wvw(short16, short16, __SE_REG, long4&, long4&);
#elif __C7X_VEC_SIZE_BITS__ == 512
extern void __vfir8hd_wvw(short32, short32, __SE_REG, long8&, long8&);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vfir8hw_wvv                                                          */
/*----------------------------------------------------------------------------*/
/* VFIR8HW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8  __vfir8hw_wvv(short16, short16, __SE_REG);
#elif __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vfir8hw_wvv(short32, short32, __SE_REG);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vfir8suhd_wvw                                                        */
/*----------------------------------------------------------------------------*/
/* VFIR8SUHD */
#if __C7X_VEC_SIZE_BITS__ == 256
extern void __vfir8suhd_wvw(short16, short16, __SE_REG, long4&, long4&);
#elif __C7X_VEC_SIZE_BITS__ == 512
extern void __vfir8suhd_wvw(short32, short32, __SE_REG, long8&, long8&);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vfir8suhw_wvv                                                        */
/*----------------------------------------------------------------------------*/
/* VFIR8SUHW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8  __vfir8suhw_wvv(short16, short16, __SE_REG);
#elif __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vfir8suhw_wvv(short32, short32, __SE_REG);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vfir8uhd_wvw                                                         */
/*----------------------------------------------------------------------------*/
/* VFIR8UHD */
#if __C7X_VEC_SIZE_BITS__ == 256
extern void __vfir8uhd_wvw(ushort16, ushort16, __SE_REG, ulong4&, ulong4&);
#elif __C7X_VEC_SIZE_BITS__ == 512
extern void __vfir8uhd_wvw(ushort32, ushort32, __SE_REG, ulong8&, ulong8&);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vfir8uhw_wvv                                                         */
/*----------------------------------------------------------------------------*/
/* VFIR8UHW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8  __vfir8uhw_wvv(ushort16, ushort16, __SE_REG);
#elif __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vfir8uhw_wvv(ushort32, ushort32, __SE_REG);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vmatmpysp_se_vww                                                     */
/*----------------------------------------------------------------------------*/
/* VMATMPYSP */
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __vmatmpysp_se_vww(float16, __SE_REG_PAIR, float16&, float16&);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vmatmpyhd_vvw                                                        */
/*----------------------------------------------------------------------------*/
/* VMATMPYHD */
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __vmatmpyhd_vvw(__SE_REG, __SE_REG, long8&, long8&);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vmatmpyhw_vvv                                                        */
/*----------------------------------------------------------------------------*/
/* VMATMPYHW */
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vmatmpyhw_vvv(__SE_REG, __SE_REG);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vmatmpysuhd_vvw                                                      */
/*----------------------------------------------------------------------------*/
/* VMATMPYSUHD */
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __vmatmpysuhd_vvw(__SE_REG, __SE_REG, long8&, long8&);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vmatmpysuhw_vvv                                                      */
/*----------------------------------------------------------------------------*/
/* VMATMPYSUHW */
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vmatmpysuhw_vvv(__SE_REG, __SE_REG);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vmatmpyuhd_vvw                                                       */
/*----------------------------------------------------------------------------*/
/* VMATMPYUHD */
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __vmatmpyuhd_vvw(__SE_REG, __SE_REG, ulong8&, ulong8&);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vmatmpyuhw_vvv                                                       */
/*----------------------------------------------------------------------------*/
/* VMATMPYUHW */
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vmatmpyuhw_vvv(__SE_REG, __SE_REG);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vmatmpyushd_vvw                                                      */
/*----------------------------------------------------------------------------*/
/* VMATMPYUSHD */
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __vmatmpyushd_vvw(__SE_REG, __SE_REG, long8&, long8&);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vmatmpyushw_vvv                                                      */
/*----------------------------------------------------------------------------*/
/* VMATMPYUSHW */
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vmatmpyushw_vvv(__SE_REG, __SE_REG);
#endif

/* AUTOGEN MARKER */
/*----------------------------------------------------------------------------*/
/* ID: __addd_ddd                                                             */
/*----------------------------------------------------------------------------*/

/* ADDD */
extern int64_t __addd_ddd(int64_t, int64_t);
extern uint64_t __addd_ddd(uint64_t, uint64_t);

/*----------------------------------------------------------------------------*/
/* ID: __addd_dkd                                                             */
/*----------------------------------------------------------------------------*/

/* ADDD */
extern int64_t __addd_dkd(int64_t, int32_t/*(k)*/);
extern uint64_t __addd_dkd(uint64_t, uint32_t/*(k={0-2147483647})*/);

/*----------------------------------------------------------------------------*/
/* ID: __adddp_ddd                                                            */
/*----------------------------------------------------------------------------*/

/* ADDDP */
extern double __adddp_ddd(double, double);

/*----------------------------------------------------------------------------*/
/* ID: __addsp_rrr                                                            */
/*----------------------------------------------------------------------------*/

/* ADDSP */
extern float __addsp_rrr(float, float);

/*----------------------------------------------------------------------------*/
/* ID: __addw_rkr                                                             */
/*----------------------------------------------------------------------------*/

/* ADDW */
extern int32_t __addw_rkr(int32_t, int32_t/*(k)*/);
extern uint32_t __addw_rkr(uint32_t, uint32_t/*(k)*/);

/*----------------------------------------------------------------------------*/
/* ID: __addw_rrr                                                             */
/*----------------------------------------------------------------------------*/

/* ADDW */
extern int32_t __addw_rrr(int32_t, int32_t);
extern uint32_t __addw_rrr(uint32_t, uint32_t);

/*----------------------------------------------------------------------------*/
/* ID: __and_ppp                                                              */
/*----------------------------------------------------------------------------*/

/* AND */
extern __vpred __and_ppp(__vpred, __vpred);

/*----------------------------------------------------------------------------*/
/* ID: __andd_ddd                                                             */
/*----------------------------------------------------------------------------*/

/* ANDD */
extern char8 __andd_ddd(char8, char8);
extern uchar8 __andd_ddd(uchar8, uchar8);
extern short4 __andd_ddd(short4, short4);
extern ushort4 __andd_ddd(ushort4, ushort4);
extern int2 __andd_ddd(int2, int2);
extern uint2 __andd_ddd(uint2, uint2);
extern int64_t __andd_ddd(int64_t, int64_t);
extern uint64_t __andd_ddd(uint64_t, uint64_t);

/*----------------------------------------------------------------------------*/
/* ID: __andd_dkd                                                             */
/*----------------------------------------------------------------------------*/

/* ANDD */
extern int64_t __andd_dkd(int64_t, int32_t/*(k)*/);
extern uint64_t __andd_dkd(uint64_t, uint32_t/*(k={0-2147483647})*/);

/*----------------------------------------------------------------------------*/
/* ID: __andn_ppp                                                             */
/*----------------------------------------------------------------------------*/

/* ANDN */
extern __vpred __andn_ppp(__vpred, __vpred);

/*----------------------------------------------------------------------------*/
/* ID: __andnd_ddd                                                            */
/*----------------------------------------------------------------------------*/

/* ANDND */
extern char8 __andnd_ddd(char8, char8);
extern uchar8 __andnd_ddd(uchar8, uchar8);
extern short4 __andnd_ddd(short4, short4);
extern ushort4 __andnd_ddd(ushort4, ushort4);
extern int2 __andnd_ddd(int2, int2);
extern uint2 __andnd_ddd(uint2, uint2);
extern int64_t __andnd_ddd(int64_t, int64_t);
extern uint64_t __andnd_ddd(uint64_t, uint64_t);

/*----------------------------------------------------------------------------*/
/* ID: __andnd_dkd                                                            */
/*----------------------------------------------------------------------------*/

/* ANDND */
extern int64_t __andnd_dkd(int64_t, int32_t/*(k)*/);
extern uint64_t __andnd_dkd(uint64_t, uint32_t/*(k={0-2147483647})*/);

/*----------------------------------------------------------------------------*/
/* ID: __andnw_rkr                                                            */
/*----------------------------------------------------------------------------*/

/* ANDNW */
extern char4 __andnw_rkr(char4, char4/*(k)*/);
extern uchar4 __andnw_rkr(uchar4, uchar4/*(k)*/);
extern short2 __andnw_rkr(short2, short2/*(k)*/);
extern ushort2 __andnw_rkr(ushort2, ushort2/*(k)*/);
extern int32_t __andnw_rkr(int32_t, int32_t/*(k)*/);
extern uint32_t __andnw_rkr(uint32_t, uint32_t/*(k)*/);

/*----------------------------------------------------------------------------*/
/* ID: __andnw_rrr                                                            */
/*----------------------------------------------------------------------------*/

/* ANDNW */
extern char4 __andnw_rrr(char4, char4);
extern uchar4 __andnw_rrr(uchar4, uchar4);
extern short2 __andnw_rrr(short2, short2);
extern ushort2 __andnw_rrr(ushort2, ushort2);
extern int32_t __andnw_rrr(int32_t, int32_t);
extern uint32_t __andnw_rrr(uint32_t, uint32_t);

/*----------------------------------------------------------------------------*/
/* ID: __andw_rkr                                                             */
/*----------------------------------------------------------------------------*/

/* ANDW */
extern char4 __andw_rkr(char4, char4/*(k)*/);
extern uchar4 __andw_rkr(uchar4, uchar4/*(k)*/);
extern short2 __andw_rkr(short2, short2/*(k)*/);
extern ushort2 __andw_rkr(ushort2, ushort2/*(k)*/);
extern int32_t __andw_rkr(int32_t, int32_t/*(k)*/);
extern uint32_t __andw_rkr(uint32_t, uint32_t/*(k)*/);

/*----------------------------------------------------------------------------*/
/* ID: __andw_rrr                                                             */
/*----------------------------------------------------------------------------*/

/* ANDW */
extern char4 __andw_rrr(char4, char4);
extern uchar4 __andw_rrr(uchar4, uchar4);
extern short2 __andw_rrr(short2, short2);
extern ushort2 __andw_rrr(ushort2, ushort2);
extern int32_t __andw_rrr(int32_t, int32_t);
extern uint32_t __andw_rrr(uint32_t, uint32_t);

/*----------------------------------------------------------------------------*/
/* ID: __bitr_pp                                                              */
/*----------------------------------------------------------------------------*/

/* BITR */
extern __vpred __bitr_pp(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __c6dcmpeqb_ddr                                                        */
/*----------------------------------------------------------------------------*/

/* C6DCMPEQB */
extern uint8_t __c6dcmpeqb_ddr(char8, char8);

/*----------------------------------------------------------------------------*/
/* ID: __c6dcmpeqh_ddr                                                        */
/*----------------------------------------------------------------------------*/

/* C6DCMPEQH */
extern uint8_t __c6dcmpeqh_ddr(short4, short4);

/*----------------------------------------------------------------------------*/
/* ID: __c6dcmpgth_ddr                                                        */
/*----------------------------------------------------------------------------*/

/* C6DCMPGTH */
extern uint8_t __c6dcmpgth_ddr(short4, short4);

/*----------------------------------------------------------------------------*/
/* ID: __c6dcmpgtub_ddr                                                       */
/*----------------------------------------------------------------------------*/

/* C6DCMPGTUB */
extern uint8_t __c6dcmpgtub_ddr(uchar8, uchar8);

/*----------------------------------------------------------------------------*/
/* ID: __c6ddotp2hhw_drd                                                      */
/*----------------------------------------------------------------------------*/

/* C6DDOTP2HHW */
extern int2 __c6ddotp2hhw_drd(short4, short2);

/*----------------------------------------------------------------------------*/
/* ID: __c6ddotp2hrhh_drr                                                     */
/*----------------------------------------------------------------------------*/

/* C6DDOTP2HRHH */
extern short2 __c6ddotp2hrhh_drr(short4, short2);

/*----------------------------------------------------------------------------*/
/* ID: __c6ddotp2lhw_drd                                                      */
/*----------------------------------------------------------------------------*/

/* C6DDOTP2LHW */
extern int2 __c6ddotp2lhw_drd(short4, short2);

/*----------------------------------------------------------------------------*/
/* ID: __c6ddotp2lrhh_drr                                                     */
/*----------------------------------------------------------------------------*/

/* C6DDOTP2LRHH */
extern short2 __c6ddotp2lrhh_drr(short4, short2);

/*----------------------------------------------------------------------------*/
/* ID: __c6dmpyhw_vvw                                                         */
/*----------------------------------------------------------------------------*/

/* C6DMPYHW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern void __c6dmpyhw_vvw(short16, short16, int8&, int8&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __c6dmpyhw_vvw(short32, short32, int16&, int16&);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __c6dmpysubh_vvw                                                       */
/*----------------------------------------------------------------------------*/

/* C6DMPYSUBH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern void __c6dmpysubh_vvw(char32, uchar32, short16&, short16&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __c6dmpysubh_vvw(char64, uchar64, short32&, short32&);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __c6dmpyubh_vvw                                                        */
/*----------------------------------------------------------------------------*/

/* C6DMPYUBH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern void __c6dmpyubh_vvw(uchar32, uchar32, ushort16&, ushort16&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __c6dmpyubh_vvw(uchar64, uchar64, ushort32&, ushort32&);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __c6dmpyuhw_vvw                                                        */
/*----------------------------------------------------------------------------*/

/* C6DMPYUHW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern void __c6dmpyuhw_vvw(ushort16, ushort16, uint8&, uint8&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __c6dmpyuhw_vvw(ushort32, ushort32, uint16&, uint16&);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __c6dotp2rsuhw_rrr                                                     */
/*----------------------------------------------------------------------------*/

/* C6DOTP2RSUHW */
extern int32_t __c6dotp2rsuhw_rrr(short2, ushort2);

/*----------------------------------------------------------------------------*/
/* ID: __c6dotpn2hw_rrr                                                       */
/*----------------------------------------------------------------------------*/

/* C6DOTPN2HW */
extern int32_t __c6dotpn2hw_rrr(short2, short2);

/*----------------------------------------------------------------------------*/
/* ID: __c6dotpn2rsuhh_rrr                                                    */
/*----------------------------------------------------------------------------*/

/* C6DOTPN2RSUHH */
extern int32_t __c6dotpn2rsuhh_rrr(short2, ushort2);

/*----------------------------------------------------------------------------*/
/* ID: __c6dsmpyhw_vvw                                                        */
/*----------------------------------------------------------------------------*/

/* C6DSMPYHW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern void __c6dsmpyhw_vvw(short16, short16, int8&, int8&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __c6dsmpyhw_vvw(short32, short32, int16&, int16&);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __c6dspacku4_ddd                                                       */
/*----------------------------------------------------------------------------*/

/* C6DSPACKU4 */
extern uchar8 __c6dspacku4_ddd(short4, short4);

/*----------------------------------------------------------------------------*/
/* ID: __c6mpy2ir_rrd                                                         */
/*----------------------------------------------------------------------------*/

/* C6MPY2IR */
extern int2 __c6mpy2ir_rrd(short2, int32_t);

/*----------------------------------------------------------------------------*/
/* ID: __c6mpyhir_rrr                                                         */
/*----------------------------------------------------------------------------*/

/* C6MPYHIR */
extern int32_t __c6mpyhir_rrr(short2, int32_t);

/*----------------------------------------------------------------------------*/
/* ID: __c6mpylir_rrr                                                         */
/*----------------------------------------------------------------------------*/

/* C6MPYLIR */
extern int32_t __c6mpylir_rrr(short2, int32_t);

/*----------------------------------------------------------------------------*/
/* ID: __clr_rrr                                                              */
/*----------------------------------------------------------------------------*/

/* CLR */
extern uint32_t __clr_rrr(uint32_t, uint32_t);

/*----------------------------------------------------------------------------*/
/* ID: __cmpeqd_ddr                                                           */
/*----------------------------------------------------------------------------*/

/* CMPEQD */
extern int32_t __cmpeqd_ddr(int64_t, int64_t);

/*----------------------------------------------------------------------------*/
/* ID: __cmpeqd_dkr                                                           */
/*----------------------------------------------------------------------------*/

/* CMPEQD */
extern int32_t __cmpeqd_dkr(int64_t, int32_t/*(k)*/);

/*----------------------------------------------------------------------------*/
/* ID: __cmpeqdp_ddr                                                          */
/*----------------------------------------------------------------------------*/

/* CMPEQDP */
extern int32_t __cmpeqdp_ddr(double, double);

/*----------------------------------------------------------------------------*/
/* ID: __cmpeqsp_rrr                                                          */
/*----------------------------------------------------------------------------*/

/* CMPEQSP */
extern int32_t __cmpeqsp_rrr(float, float);

/*----------------------------------------------------------------------------*/
/* ID: __cmpeqw_rkr                                                           */
/*----------------------------------------------------------------------------*/

/* CMPEQW */
extern int32_t __cmpeqw_rkr(int32_t, int32_t/*(k)*/);

/*----------------------------------------------------------------------------*/
/* ID: __cmpeqw_rrr                                                           */
/*----------------------------------------------------------------------------*/

/* CMPEQW */
extern int32_t __cmpeqw_rrr(int32_t, int32_t);

/*----------------------------------------------------------------------------*/
/* ID: __cmpged_ddr                                                           */
/*----------------------------------------------------------------------------*/

/* CMPGED */
extern int32_t __cmpged_ddr(int64_t, int64_t);

/*----------------------------------------------------------------------------*/
/* ID: __cmpged_dkr                                                           */
/*----------------------------------------------------------------------------*/

/* CMPGED */
extern int32_t __cmpged_dkr(int64_t, int32_t/*(k)*/);

/*----------------------------------------------------------------------------*/
/* ID: __cmpgeud_ddr                                                          */
/*----------------------------------------------------------------------------*/

/* CMPGEUD */
extern int32_t __cmpgeud_ddr(uint64_t, uint64_t);

/*----------------------------------------------------------------------------*/
/* ID: __cmpgeud_dkr                                                          */
/*----------------------------------------------------------------------------*/

/* CMPGEUD */
extern int32_t __cmpgeud_dkr(uint64_t, uint32_t/*(k)*/);

/*----------------------------------------------------------------------------*/
/* ID: __cmpgeuw_rkr                                                          */
/*----------------------------------------------------------------------------*/

/* CMPGEUW */
extern int32_t __cmpgeuw_rkr(uint32_t, uint32_t/*(k)*/);

/*----------------------------------------------------------------------------*/
/* ID: __cmpgeuw_rrr                                                          */
/*----------------------------------------------------------------------------*/

/* CMPGEUW */
extern int32_t __cmpgeuw_rrr(uint32_t, uint32_t);

/*----------------------------------------------------------------------------*/
/* ID: __cmpgew_rkr                                                           */
/*----------------------------------------------------------------------------*/

/* CMPGEW */
extern int32_t __cmpgew_rkr(int32_t, int32_t/*(k)*/);

/*----------------------------------------------------------------------------*/
/* ID: __cmpgew_rrr                                                           */
/*----------------------------------------------------------------------------*/

/* CMPGEW */
extern int32_t __cmpgew_rrr(int32_t, int32_t);

/*----------------------------------------------------------------------------*/
/* ID: __cmpgtd_ddr                                                           */
/*----------------------------------------------------------------------------*/

/* CMPGTD */
extern int32_t __cmpgtd_ddr(int64_t, int64_t);

/*----------------------------------------------------------------------------*/
/* ID: __cmpgtd_dkr                                                           */
/*----------------------------------------------------------------------------*/

/* CMPGTD */
extern int32_t __cmpgtd_dkr(int64_t, int32_t/*(k)*/);

/*----------------------------------------------------------------------------*/
/* ID: __cmpgtud_ddr                                                          */
/*----------------------------------------------------------------------------*/

/* CMPGTUD */
extern int32_t __cmpgtud_ddr(uint64_t, uint64_t);

/*----------------------------------------------------------------------------*/
/* ID: __cmpgtud_dkr                                                          */
/*----------------------------------------------------------------------------*/

/* CMPGTUD */
extern int32_t __cmpgtud_dkr(uint64_t, uint32_t/*(k)*/);

/*----------------------------------------------------------------------------*/
/* ID: __cmpgtuw_rkr                                                          */
/*----------------------------------------------------------------------------*/

/* CMPGTUW */
extern int32_t __cmpgtuw_rkr(uint32_t, uint32_t/*(k)*/);

/*----------------------------------------------------------------------------*/
/* ID: __cmpgtuw_rrr                                                          */
/*----------------------------------------------------------------------------*/

/* CMPGTUW */
extern int32_t __cmpgtuw_rrr(uint32_t, uint32_t);

/*----------------------------------------------------------------------------*/
/* ID: __cmpgtw_rkr                                                           */
/*----------------------------------------------------------------------------*/

/* CMPGTW */
extern int32_t __cmpgtw_rkr(int32_t, int32_t/*(k)*/);

/*----------------------------------------------------------------------------*/
/* ID: __cmpgtw_rrr                                                           */
/*----------------------------------------------------------------------------*/

/* CMPGTW */
extern int32_t __cmpgtw_rrr(int32_t, int32_t);

/*----------------------------------------------------------------------------*/
/* ID: __cmpledp_ddr                                                          */
/*----------------------------------------------------------------------------*/

/* CMPLEDP */
extern int32_t __cmpledp_ddr(double, double);

/*----------------------------------------------------------------------------*/
/* ID: __cmplesp_rrr                                                          */
/*----------------------------------------------------------------------------*/

/* CMPLESP */
extern int32_t __cmplesp_rrr(float, float);

/*----------------------------------------------------------------------------*/
/* ID: __cmpltdp_ddr                                                          */
/*----------------------------------------------------------------------------*/

/* CMPLTDP */
extern int32_t __cmpltdp_ddr(double, double);

/*----------------------------------------------------------------------------*/
/* ID: __cmpltsp_rrr                                                          */
/*----------------------------------------------------------------------------*/

/* CMPLTSP */
extern int32_t __cmpltsp_rrr(float, float);

/*----------------------------------------------------------------------------*/
/* ID: __compressl_pp                                                         */
/*----------------------------------------------------------------------------*/

/* COMPRESSL */
extern __vpred __compressl_pp(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __compressr_pp                                                         */
/*----------------------------------------------------------------------------*/

/* COMPRESSR */
extern __vpred __compressr_pp(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __decimateb_ppp                                                        */
/*----------------------------------------------------------------------------*/

/* DECIMATEB */
extern __vpred __decimateb_ppp(__vpred, __vpred);

/*----------------------------------------------------------------------------*/
/* ID: __decimated_ppp                                                        */
/*----------------------------------------------------------------------------*/

/* DECIMATED */
extern __vpred __decimated_ppp(__vpred, __vpred);

/*----------------------------------------------------------------------------*/
/* ID: __decimateh_ppp                                                        */
/*----------------------------------------------------------------------------*/

/* DECIMATEH */
extern __vpred __decimateh_ppp(__vpred, __vpred);

/*----------------------------------------------------------------------------*/
/* ID: __decimatew_ppp                                                        */
/*----------------------------------------------------------------------------*/

/* DECIMATEW */
extern __vpred __decimatew_ppp(__vpred, __vpred);

/*----------------------------------------------------------------------------*/
/* ID: __divdw_drd                                                            */
/*----------------------------------------------------------------------------*/

/* DIVDW */
extern int64_t __divdw_drd(int64_t, int32_t);

/*----------------------------------------------------------------------------*/
/* ID: __divudw_drd                                                           */
/*----------------------------------------------------------------------------*/

/* DIVUDW */
extern uint64_t __divudw_drd(uint64_t, uint32_t);

/*----------------------------------------------------------------------------*/
/* ID: __divuw_rrr                                                            */
/*----------------------------------------------------------------------------*/

/* DIVUW */
extern uint32_t __divuw_rrr(uint32_t, uint32_t);

/*----------------------------------------------------------------------------*/
/* ID: __divw_rrr                                                             */
/*----------------------------------------------------------------------------*/

/* DIVW */
extern int32_t __divw_rrr(int32_t, int32_t);

/*----------------------------------------------------------------------------*/
/* ID: __ext_dkkd                                                             */
/*----------------------------------------------------------------------------*/

/* EXT */
extern int64_t __ext_dkkd(char8, uint8_t/*(k={0-63})*/, uint8_t/*(k={0-63})*/);
extern int64_t __ext_dkkd(short4, uint8_t/*(k={0-63})*/, uint8_t/*(k={0-63})*/);
extern int64_t __ext_dkkd(int2, uint8_t/*(k={0-63})*/, uint8_t/*(k={0-63})*/);
extern int64_t __ext_dkkd(int64_t, uint8_t/*(k={0-63})*/, uint8_t/*(k={0-63})*/);

/*----------------------------------------------------------------------------*/
/* ID: __extu_dkkd                                                            */
/*----------------------------------------------------------------------------*/

/* EXTU */
extern uint64_t __extu_dkkd(uchar8, uint8_t/*(k={0-63})*/, uint8_t/*(k={0-63})*/);
extern uint64_t __extu_dkkd(ushort4, uint8_t/*(k={0-63})*/, uint8_t/*(k={0-63})*/);
extern uint64_t __extu_dkkd(uint2, uint8_t/*(k={0-63})*/, uint8_t/*(k={0-63})*/);
extern uint64_t __extu_dkkd(uint64_t, uint8_t/*(k={0-63})*/, uint8_t/*(k={0-63})*/);

/*----------------------------------------------------------------------------*/
/* ID: __extuv_vkkkd                                                          */
/*----------------------------------------------------------------------------*/

/* EXTUV */
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint64_t __extuv_vkkkd(ulong8, uint8_t/*(k={0-7})*/, uint8_t/*(k={0-63})*/, uint8_t/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint64_t __extuv_vkkkd(ulong4, uint8_t/*(k={0-7})*/, uint8_t/*(k={0-63})*/, uint8_t/*(k={0-63})*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __extv_vkkkd                                                           */
/*----------------------------------------------------------------------------*/

/* EXTV */
#if __C7X_VEC_SIZE_BITS__ == 512
extern int64_t __extv_vkkkd(long8, uint8_t/*(k={0-7})*/, uint8_t/*(k={0-63})*/, uint8_t/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern int64_t __extv_vkkkd(long4, uint8_t/*(k={0-7})*/, uint8_t/*(k={0-63})*/, uint8_t/*(k={0-63})*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __landd_ddr                                                            */
/*----------------------------------------------------------------------------*/

/* LANDD */
extern int32_t __landd_ddr(int64_t, int64_t);

/*----------------------------------------------------------------------------*/
/* ID: __landnd_ddr                                                           */
/*----------------------------------------------------------------------------*/

/* LANDND */
extern int32_t __landnd_ddr(int64_t, int64_t);

/*----------------------------------------------------------------------------*/
/* ID: __lord_ddr                                                             */
/*----------------------------------------------------------------------------*/

/* LORD */
extern int32_t __lord_ddr(int64_t, int64_t);

/*----------------------------------------------------------------------------*/
/* ID: __maskb_kp                                                             */
/*----------------------------------------------------------------------------*/

/* MASKB */
extern __vpred __maskb_kp(uint8_t/*(k={0-63})*/);

/*----------------------------------------------------------------------------*/
/* ID: __maskb_rp                                                             */
/*----------------------------------------------------------------------------*/

/* MASKB */
extern __vpred __maskb_rp(uint32_t);

/*----------------------------------------------------------------------------*/
/* ID: __maskd_kp                                                             */
/*----------------------------------------------------------------------------*/

/* MASKD */
extern __vpred __maskd_kp(uint8_t/*(k={0-63})*/);

/*----------------------------------------------------------------------------*/
/* ID: __maskd_rp                                                             */
/*----------------------------------------------------------------------------*/

/* MASKD */
extern __vpred __maskd_rp(uint32_t);

/*----------------------------------------------------------------------------*/
/* ID: __maskh_kp                                                             */
/*----------------------------------------------------------------------------*/

/* MASKH */
extern __vpred __maskh_kp(uint8_t/*(k={0-63})*/);

/*----------------------------------------------------------------------------*/
/* ID: __maskh_rp                                                             */
/*----------------------------------------------------------------------------*/

/* MASKH */
extern __vpred __maskh_rp(uint32_t);

/*----------------------------------------------------------------------------*/
/* ID: __maskw_kp                                                             */
/*----------------------------------------------------------------------------*/

/* MASKW */
extern __vpred __maskw_kp(uint8_t/*(k={0-63})*/);

/*----------------------------------------------------------------------------*/
/* ID: __maskw_rp                                                             */
/*----------------------------------------------------------------------------*/

/* MASKW */
extern __vpred __maskw_rp(uint32_t);

/*----------------------------------------------------------------------------*/
/* ID: __moddw_drd                                                            */
/*----------------------------------------------------------------------------*/

/* MODDW */
extern int64_t __moddw_drd(int64_t, int32_t);

/*----------------------------------------------------------------------------*/
/* ID: __modudw_drd                                                           */
/*----------------------------------------------------------------------------*/

/* MODUDW */
extern uint64_t __modudw_drd(uint64_t, uint32_t);

/*----------------------------------------------------------------------------*/
/* ID: __moduw_rrr                                                            */
/*----------------------------------------------------------------------------*/

/* MODUW */
extern uint32_t __moduw_rrr(uint32_t, uint32_t);

/*----------------------------------------------------------------------------*/
/* ID: __modw_rrr                                                             */
/*----------------------------------------------------------------------------*/

/* MODW */
extern int32_t __modw_rrr(int32_t, int32_t);

/*----------------------------------------------------------------------------*/
/* ID: __mpydd_ddd                                                            */
/*----------------------------------------------------------------------------*/

/* MPYDD */
extern int64_t __mpydd_ddd(int64_t, int64_t);
extern uint64_t __mpydd_ddd(uint64_t, uint64_t);

/*----------------------------------------------------------------------------*/
/* ID: __mpydp_ddd                                                            */
/*----------------------------------------------------------------------------*/

/* MPYDP */
extern double __mpydp_ddd(double, double);

/*----------------------------------------------------------------------------*/
/* ID: __mpyhw_rrr                                                            */
/*----------------------------------------------------------------------------*/

/* MPYHW */
extern int32_t __mpyhw_rrr(int16_t, int16_t);

/*----------------------------------------------------------------------------*/
/* ID: __mpysp_rrr                                                            */
/*----------------------------------------------------------------------------*/

/* MPYSP */
extern float __mpysp_rrr(float, float);

/*----------------------------------------------------------------------------*/
/* ID: __mpysuhw_rrr                                                          */
/*----------------------------------------------------------------------------*/

/* MPYSUHW */
extern int32_t __mpysuhw_rrr(int16_t, uint16_t);

/*----------------------------------------------------------------------------*/
/* ID: __mpyuhw_rrr                                                           */
/*----------------------------------------------------------------------------*/

/* MPYUHW */
extern uint32_t __mpyuhw_rrr(uint16_t, uint16_t);

/*----------------------------------------------------------------------------*/
/* ID: __mpyww_rrr                                                            */
/*----------------------------------------------------------------------------*/

/* MPYWW */
extern int32_t __mpyww_rrr(int32_t, int32_t);
extern uint32_t __mpyww_rrr(uint32_t, uint32_t);

/*----------------------------------------------------------------------------*/
/* ID: __nand_ppp                                                             */
/*----------------------------------------------------------------------------*/

/* NAND */
extern __vpred __nand_ppp(__vpred, __vpred);

/*----------------------------------------------------------------------------*/
/* ID: __nandd_ddd                                                            */
/*----------------------------------------------------------------------------*/

/* NANDD */
extern char8 __nandd_ddd(char8, char8);
extern uchar8 __nandd_ddd(uchar8, uchar8);
extern short4 __nandd_ddd(short4, short4);
extern ushort4 __nandd_ddd(ushort4, ushort4);
extern int2 __nandd_ddd(int2, int2);
extern uint2 __nandd_ddd(uint2, uint2);
extern int64_t __nandd_ddd(int64_t, int64_t);
extern uint64_t __nandd_ddd(uint64_t, uint64_t);

/*----------------------------------------------------------------------------*/
/* ID: __nandd_dkd                                                            */
/*----------------------------------------------------------------------------*/

/* NANDD */
extern int64_t __nandd_dkd(int64_t, int32_t/*(k)*/);
extern uint64_t __nandd_dkd(uint64_t, uint32_t/*(k={0-2147483647})*/);

/*----------------------------------------------------------------------------*/
/* ID: __nandw_rrr                                                            */
/*----------------------------------------------------------------------------*/

/* NANDW */
extern char4 __nandw_rrr(char4, char4);
extern uchar4 __nandw_rrr(uchar4, uchar4);
extern short2 __nandw_rrr(short2, short2);
extern ushort2 __nandw_rrr(ushort2, ushort2);
extern int32_t __nandw_rrr(int32_t, int32_t);
extern uint32_t __nandw_rrr(uint32_t, uint32_t);

/*----------------------------------------------------------------------------*/
/* ID: __nor_ppp                                                              */
/*----------------------------------------------------------------------------*/

/* NOR */
extern __vpred __nor_ppp(__vpred, __vpred);

/*----------------------------------------------------------------------------*/
/* ID: __nord_ddd                                                             */
/*----------------------------------------------------------------------------*/

/* NORD */
extern char8 __nord_ddd(char8, char8);
extern uchar8 __nord_ddd(uchar8, uchar8);
extern short4 __nord_ddd(short4, short4);
extern ushort4 __nord_ddd(ushort4, ushort4);
extern int2 __nord_ddd(int2, int2);
extern uint2 __nord_ddd(uint2, uint2);
extern int64_t __nord_ddd(int64_t, int64_t);
extern uint64_t __nord_ddd(uint64_t, uint64_t);

/*----------------------------------------------------------------------------*/
/* ID: __nord_dkd                                                             */
/*----------------------------------------------------------------------------*/

/* NORD */
extern int64_t __nord_dkd(int64_t, int32_t/*(k)*/);
extern uint64_t __nord_dkd(uint64_t, uint32_t/*(k={0-2147483647})*/);

/*----------------------------------------------------------------------------*/
/* ID: __norw_rrr                                                             */
/*----------------------------------------------------------------------------*/

/* NORW */
extern char4 __norw_rrr(char4, char4);
extern uchar4 __norw_rrr(uchar4, uchar4);
extern short2 __norw_rrr(short2, short2);
extern ushort2 __norw_rrr(ushort2, ushort2);
extern int32_t __norw_rrr(int32_t, int32_t);
extern uint32_t __norw_rrr(uint32_t, uint32_t);

/*----------------------------------------------------------------------------*/
/* ID: __not_pp                                                               */
/*----------------------------------------------------------------------------*/

/* NOT */
extern __vpred __not_pp(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __or_ppp                                                               */
/*----------------------------------------------------------------------------*/

/* OR */
extern __vpred __or_ppp(__vpred, __vpred);

/*----------------------------------------------------------------------------*/
/* ID: __ord_ddd                                                              */
/*----------------------------------------------------------------------------*/

/* ORD */
extern char8 __ord_ddd(char8, char8);
extern uchar8 __ord_ddd(uchar8, uchar8);
extern short4 __ord_ddd(short4, short4);
extern ushort4 __ord_ddd(ushort4, ushort4);
extern int2 __ord_ddd(int2, int2);
extern uint2 __ord_ddd(uint2, uint2);
extern int64_t __ord_ddd(int64_t, int64_t);
extern uint64_t __ord_ddd(uint64_t, uint64_t);

/*----------------------------------------------------------------------------*/
/* ID: __ord_dkd                                                              */
/*----------------------------------------------------------------------------*/

/* ORD */
extern int64_t __ord_dkd(int64_t, int32_t/*(k)*/);
extern uint64_t __ord_dkd(uint64_t, uint32_t/*(k={0-2147483647})*/);

/*----------------------------------------------------------------------------*/
/* ID: __orn_ppp                                                              */
/*----------------------------------------------------------------------------*/

/* ORN */
extern __vpred __orn_ppp(__vpred, __vpred);

/*----------------------------------------------------------------------------*/
/* ID: __ornd_ddd                                                             */
/*----------------------------------------------------------------------------*/

/* ORND */
extern char8 __ornd_ddd(char8, char8);
extern uchar8 __ornd_ddd(uchar8, uchar8);
extern short4 __ornd_ddd(short4, short4);
extern ushort4 __ornd_ddd(ushort4, ushort4);
extern int2 __ornd_ddd(int2, int2);
extern uint2 __ornd_ddd(uint2, uint2);
extern int64_t __ornd_ddd(int64_t, int64_t);
extern uint64_t __ornd_ddd(uint64_t, uint64_t);

/*----------------------------------------------------------------------------*/
/* ID: __ornd_dkd                                                             */
/*----------------------------------------------------------------------------*/

/* ORND */
extern int64_t __ornd_dkd(int64_t, int32_t/*(k)*/);
extern uint64_t __ornd_dkd(uint64_t, uint32_t/*(k={0-2147483647})*/);

/*----------------------------------------------------------------------------*/
/* ID: __ornw_rkr                                                             */
/*----------------------------------------------------------------------------*/

/* ORNW */
extern char4 __ornw_rkr(char4, char4/*(k)*/);
extern uchar4 __ornw_rkr(uchar4, uchar4/*(k)*/);
extern short2 __ornw_rkr(short2, short2/*(k)*/);
extern ushort2 __ornw_rkr(ushort2, ushort2/*(k)*/);
extern int32_t __ornw_rkr(int32_t, int32_t/*(k)*/);
extern uint32_t __ornw_rkr(uint32_t, uint32_t/*(k)*/);

/*----------------------------------------------------------------------------*/
/* ID: __ornw_rrr                                                             */
/*----------------------------------------------------------------------------*/

/* ORNW */
extern char4 __ornw_rrr(char4, char4);
extern uchar4 __ornw_rrr(uchar4, uchar4);
extern short2 __ornw_rrr(short2, short2);
extern ushort2 __ornw_rrr(ushort2, ushort2);
extern int32_t __ornw_rrr(int32_t, int32_t);
extern uint32_t __ornw_rrr(uint32_t, uint32_t);

/*----------------------------------------------------------------------------*/
/* ID: __orw_rkr                                                              */
/*----------------------------------------------------------------------------*/

/* ORW */
extern char4 __orw_rkr(char4, char4/*(k)*/);
extern uchar4 __orw_rkr(uchar4, uchar4/*(k)*/);
extern short2 __orw_rkr(short2, short2/*(k)*/);
extern ushort2 __orw_rkr(ushort2, ushort2/*(k)*/);
extern int32_t __orw_rkr(int32_t, int32_t/*(k)*/);
extern uint32_t __orw_rkr(uint32_t, uint32_t/*(k)*/);

/*----------------------------------------------------------------------------*/
/* ID: __orw_rrr                                                              */
/*----------------------------------------------------------------------------*/

/* ORW */
extern char4 __orw_rrr(char4, char4);
extern uchar4 __orw_rrr(uchar4, uchar4);
extern short2 __orw_rrr(short2, short2);
extern ushort2 __orw_rrr(ushort2, ushort2);
extern int32_t __orw_rrr(int32_t, int32_t);
extern uint32_t __orw_rrr(uint32_t, uint32_t);

/*----------------------------------------------------------------------------*/
/* ID: __packw_rrd                                                            */
/*----------------------------------------------------------------------------*/

/* PACKW */
extern cshort2 __packw_rrd(cshort, cshort);
extern int2 __packw_rrd(int32_t, int32_t);
extern uint2 __packw_rrd(uint32_t, uint32_t);
extern float2 __packw_rrd(float, float);

/*----------------------------------------------------------------------------*/
/* ID: __packwdly4_rrd                                                        */
/*----------------------------------------------------------------------------*/

/* PACKWDLY4 */
extern int64_t __packwdly4_rrd(int32_t, int32_t);
extern uint64_t __packwdly4_rrd(uint32_t, uint32_t);

/*----------------------------------------------------------------------------*/
/* ID: __packx2_rrd                                                           */
/*----------------------------------------------------------------------------*/

/* PACKX2 */
extern cchar4 __packx2_rrd(cchar2, cchar2);
extern short4 __packx2_rrd(short2, short2);
extern ushort4 __packx2_rrd(ushort2, ushort2);

/*----------------------------------------------------------------------------*/
/* ID: __pbitcntb_pr                                                          */
/*----------------------------------------------------------------------------*/

/* PBITCNTB */
extern uint32_t __pbitcntb_pr(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __pbitcntd_pr                                                          */
/*----------------------------------------------------------------------------*/

/* PBITCNTD */
extern uint32_t __pbitcntd_pr(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __pbitcnth_pr                                                          */
/*----------------------------------------------------------------------------*/

/* PBITCNTH */
extern uint32_t __pbitcnth_pr(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __pbitcntw_pr                                                          */
/*----------------------------------------------------------------------------*/

/* PBITCNTW */
extern uint32_t __pbitcntw_pr(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __pcntgatherb_prp                                                      */
/*----------------------------------------------------------------------------*/

/* PCNTGATHERB */
extern void __pcntgatherb_prp(__vpred, uint32_t&, __vpred&);

/*----------------------------------------------------------------------------*/
/* ID: __pcntgatherd_prp                                                      */
/*----------------------------------------------------------------------------*/

/* PCNTGATHERD */
extern void __pcntgatherd_prp(__vpred, uint32_t&, __vpred&);

/*----------------------------------------------------------------------------*/
/* ID: __pcntgatherh_prp                                                      */
/*----------------------------------------------------------------------------*/

/* PCNTGATHERH */
extern void __pcntgatherh_prp(__vpred, uint32_t&, __vpred&);

/*----------------------------------------------------------------------------*/
/* ID: __pcntgatherw_prp                                                      */
/*----------------------------------------------------------------------------*/

/* PCNTGATHERW */
extern void __pcntgatherw_prp(__vpred, uint32_t&, __vpred&);

/*----------------------------------------------------------------------------*/
/* ID: __pduph2b_pp                                                           */
/*----------------------------------------------------------------------------*/

/* PDUPH2B */
extern __vpred __pduph2b_pp(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __pduph2d_pp                                                           */
/*----------------------------------------------------------------------------*/

/* PDUPH2D */
extern __vpred __pduph2d_pp(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __pduph2h_pp                                                           */
/*----------------------------------------------------------------------------*/

/* PDUPH2H */
extern __vpred __pduph2h_pp(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __pduph2w_pp                                                           */
/*----------------------------------------------------------------------------*/

/* PDUPH2W */
extern __vpred __pduph2w_pp(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __pdupl2b_pp                                                           */
/*----------------------------------------------------------------------------*/

/* PDUPL2B */
extern __vpred __pdupl2b_pp(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __pdupl2d_pp                                                           */
/*----------------------------------------------------------------------------*/

/* PDUPL2D */
extern __vpred __pdupl2d_pp(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __pdupl2h_pp                                                           */
/*----------------------------------------------------------------------------*/

/* PDUPL2H */
extern __vpred __pdupl2h_pp(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __pdupl2w_pp                                                           */
/*----------------------------------------------------------------------------*/

/* PDUPL2W */
extern __vpred __pdupl2w_pp(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __prmbdb_pr                                                            */
/*----------------------------------------------------------------------------*/

/* PRMBDB */
extern uint32_t __prmbdb_pr(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __prmbdd_pr                                                            */
/*----------------------------------------------------------------------------*/

/* PRMBDD */
extern uint32_t __prmbdd_pr(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __prmbdh_pr                                                            */
/*----------------------------------------------------------------------------*/

/* PRMBDH */
extern uint32_t __prmbdh_pr(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __prmbdw_pr                                                            */
/*----------------------------------------------------------------------------*/

/* PRMBDW */
extern uint32_t __prmbdw_pr(__vpred);

/*----------------------------------------------------------------------------*/
/* ID: __replace_dkkd                                                         */
/*----------------------------------------------------------------------------*/

/* REPLACE */
extern int64_t __replace_dkkd(int64_t, int8_t/*(k={0-63})*/, int8_t/*(k={0-63})*/, int64_t);
extern uint64_t __replace_dkkd(uint64_t, uint8_t/*(k={0-63})*/, uint8_t/*(k={0-63})*/, uint64_t);

/*----------------------------------------------------------------------------*/
/* ID: __replacev_dkkkv                                                       */
/*----------------------------------------------------------------------------*/

/* REPLACEV */
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __replacev_dkkkv(int64_t, int8_t/*(k={0-7})*/, int8_t/*(k={0-63})*/, int8_t/*(k={0-63})*/, long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __replacev_dkkkv(int64_t, int8_t/*(k={0-7})*/, int8_t/*(k={0-63})*/, int8_t/*(k={0-63})*/, long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __replacev_dkkkv(uint64_t, uint8_t/*(k={0-7})*/, uint8_t/*(k={0-63})*/, uint8_t/*(k={0-63})*/, ulong8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __replacev_dkkkv(uint64_t, uint8_t/*(k={0-7})*/, uint8_t/*(k={0-63})*/, uint8_t/*(k={0-63})*/, ulong4);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __set_rrr                                                              */
/*----------------------------------------------------------------------------*/

/* SET */
extern int32_t __set_rrr(int32_t, int32_t);

/*----------------------------------------------------------------------------*/
/* ID: __shld_dkd                                                             */
/*----------------------------------------------------------------------------*/

/* SHLD */
extern int64_t __shld_dkd(int64_t, uint8_t/*(k={0-63})*/);
extern uint64_t __shld_dkd(uint64_t, uint8_t/*(k={0-63})*/);

/*----------------------------------------------------------------------------*/
/* ID: __shld_drd                                                             */
/*----------------------------------------------------------------------------*/

/* SHLD */
extern int64_t __shld_drd(int64_t, int32_t);
extern uint64_t __shld_drd(uint64_t, uint32_t);

/*----------------------------------------------------------------------------*/
/* ID: __shlw_rkr                                                             */
/*----------------------------------------------------------------------------*/

/* SHLW */
extern int32_t __shlw_rkr(int32_t, uint8_t/*(k={0-63})*/);
extern uint32_t __shlw_rkr(uint32_t, uint8_t/*(k={0-63})*/);

/*----------------------------------------------------------------------------*/
/* ID: __shlw_rrr                                                             */
/*----------------------------------------------------------------------------*/

/* SHLW */
extern int32_t __shlw_rrr(int32_t, int32_t);
extern uint32_t __shlw_rrr(uint32_t, uint32_t);

/*----------------------------------------------------------------------------*/
/* ID: __shrd_dkd                                                             */
/*----------------------------------------------------------------------------*/

/* SHRD */
extern int64_t __shrd_dkd(int64_t, uint8_t/*(k={0-63})*/);

/*----------------------------------------------------------------------------*/
/* ID: __shrd_drd                                                             */
/*----------------------------------------------------------------------------*/

/* SHRD */
extern int64_t __shrd_drd(int64_t, int32_t);

/*----------------------------------------------------------------------------*/
/* ID: __shrud_dkd                                                            */
/*----------------------------------------------------------------------------*/

/* SHRUD */
extern uint64_t __shrud_dkd(uint64_t, uint8_t/*(k={0-63})*/);

/*----------------------------------------------------------------------------*/
/* ID: __shrud_drd                                                            */
/*----------------------------------------------------------------------------*/

/* SHRUD */
extern uint64_t __shrud_drd(uint64_t, uint32_t);

/*----------------------------------------------------------------------------*/
/* ID: __shruw_rkr                                                            */
/*----------------------------------------------------------------------------*/

/* SHRUW */
extern uint32_t __shruw_rkr(uint32_t, uint8_t/*(k={0-63})*/);

/*----------------------------------------------------------------------------*/
/* ID: __shruw_rrr                                                            */
/*----------------------------------------------------------------------------*/

/* SHRUW */
extern uint32_t __shruw_rrr(uint32_t, uint32_t);

/*----------------------------------------------------------------------------*/
/* ID: __shrw_rkr                                                             */
/*----------------------------------------------------------------------------*/

/* SHRW */
extern int32_t __shrw_rkr(int32_t, uint8_t/*(k={0-63})*/);

/*----------------------------------------------------------------------------*/
/* ID: __shrw_rrr                                                             */
/*----------------------------------------------------------------------------*/

/* SHRW */
extern int32_t __shrw_rrr(int32_t, int32_t);

/*----------------------------------------------------------------------------*/
/* ID: __smpyhw_rrr                                                           */
/*----------------------------------------------------------------------------*/

/* SMPYHW */
extern int32_t __smpyhw_rrr(int16_t, int16_t);

/*----------------------------------------------------------------------------*/
/* ID: __subd_ddd                                                             */
/*----------------------------------------------------------------------------*/

/* SUBD */
extern int64_t __subd_ddd(int64_t, int64_t);
extern uint64_t __subd_ddd(uint64_t, uint64_t);

/*----------------------------------------------------------------------------*/
/* ID: __subdp_ddd                                                            */
/*----------------------------------------------------------------------------*/

/* SUBDP */
extern double __subdp_ddd(double, double);

/*----------------------------------------------------------------------------*/
/* ID: __subrd_ddd                                                            */
/*----------------------------------------------------------------------------*/

/* SUBRD */
extern int64_t __subrd_ddd(int64_t, int64_t);
extern uint64_t __subrd_ddd(uint64_t, uint64_t);

/*----------------------------------------------------------------------------*/
/* ID: __subrd_dkd                                                            */
/*----------------------------------------------------------------------------*/

/* SUBRD */
extern int64_t __subrd_dkd(int64_t, int32_t/*(k)*/);
extern uint64_t __subrd_dkd(uint64_t, uint32_t/*(k={0-2147483647})*/);

/*----------------------------------------------------------------------------*/
/* ID: __subrw_rkr                                                            */
/*----------------------------------------------------------------------------*/

/* SUBRW */
extern int32_t __subrw_rkr(int32_t, int32_t/*(k)*/);
extern uint32_t __subrw_rkr(uint32_t, uint32_t/*(k)*/);

/*----------------------------------------------------------------------------*/
/* ID: __subrw_rrr                                                            */
/*----------------------------------------------------------------------------*/

/* SUBRW */
extern int32_t __subrw_rrr(int32_t, int32_t);
extern uint32_t __subrw_rrr(uint32_t, uint32_t);

/*----------------------------------------------------------------------------*/
/* ID: __subsp_rrr                                                            */
/*----------------------------------------------------------------------------*/

/* SUBSP */
extern float __subsp_rrr(float, float);

/*----------------------------------------------------------------------------*/
/* ID: __subw_rrr                                                             */
/*----------------------------------------------------------------------------*/

/* SUBW */
extern int32_t __subw_rrr(int32_t, int32_t);
extern uint32_t __subw_rrr(uint32_t, uint32_t);

/*----------------------------------------------------------------------------*/
/* ID: __vabsb_vv                                                             */
/*----------------------------------------------------------------------------*/

/* VABSB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __vabsb_vv(char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __vabsb_vv(char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cchar16 __vabsb_vv(cchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cchar32 __vabsb_vv(cchar32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vabsd_vv                                                             */
/*----------------------------------------------------------------------------*/

/* VABSD */
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __vabsd_vv(long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __vabsd_vv(long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern clong2 __vabsd_vv(clong2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern clong4 __vabsd_vv(clong4);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vabsdp_vv                                                            */
/*----------------------------------------------------------------------------*/

/* VABSDP */
#if __C7X_VEC_SIZE_BITS__ == 256
extern double4 __vabsdp_vv(double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern double8 __vabsdp_vv(double8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cdouble2 __vabsdp_vv(cdouble2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cdouble4 __vabsdp_vv(cdouble4);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vabsh_vv                                                             */
/*----------------------------------------------------------------------------*/

/* VABSH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vabsh_vv(short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vabsh_vv(short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cshort8 __vabsh_vv(cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cshort16 __vabsh_vv(cshort16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vabssp_vv                                                            */
/*----------------------------------------------------------------------------*/

/* VABSSP */
#if __C7X_VEC_SIZE_BITS__ == 256
extern float8 __vabssp_vv(float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern float16 __vabssp_vv(float16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cfloat4 __vabssp_vv(cfloat4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cfloat8 __vabssp_vv(cfloat8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vabsw_vv                                                             */
/*----------------------------------------------------------------------------*/

/* VABSW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vabsw_vv(int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vabsw_vv(int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cint4 __vabsw_vv(cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cint8 __vabsw_vv(cint8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vaddb_vkv                                                            */
/*----------------------------------------------------------------------------*/

/* VADDB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __vaddb_vkv(char32, char32/*(k)*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __vaddb_vkv(char64, char64/*(k)*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vaddb_vkv(uchar32, uchar32/*(k)*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vaddb_vkv(uchar64, uchar64/*(k)*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vaddb_vvv                                                            */
/*----------------------------------------------------------------------------*/

/* VADDB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __vaddb_vvv(char32, char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __vaddb_vvv(char64, char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vaddb_vvv(uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vaddb_vvv(uchar64, uchar64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cchar16 __vaddb_vvv(cchar16, cchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cchar32 __vaddb_vvv(cchar32, cchar32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vaddcb_pvv                                                           */
/*----------------------------------------------------------------------------*/

/* VADDCB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __vaddcb_pvv(__vpred, char32, char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __vaddcb_pvv(__vpred, char64, char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vaddcb_pvv(__vpred, uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vaddcb_pvv(__vpred, uchar64, uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vaddcd_pvv                                                           */
/*----------------------------------------------------------------------------*/

/* VADDCD */
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __vaddcd_pvv(__vpred, long4, long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __vaddcd_pvv(__vpred, long8, long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __vaddcd_pvv(__vpred, ulong4, ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __vaddcd_pvv(__vpred, ulong8, ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vaddch_pvv                                                           */
/*----------------------------------------------------------------------------*/

/* VADDCH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vaddch_pvv(__vpred, short16, short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vaddch_pvv(__vpred, short32, short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vaddch_pvv(__vpred, ushort16, ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vaddch_pvv(__vpred, ushort32, ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vaddcw_pvv                                                           */
/*----------------------------------------------------------------------------*/

/* VADDCW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vaddcw_pvv(__vpred, int8, int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vaddcw_pvv(__vpred, int16, int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vaddcw_pvv(__vpred, uint8, uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vaddcw_pvv(__vpred, uint16, uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vaddd_vkv                                                            */
/*----------------------------------------------------------------------------*/

/* VADDD */
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __vaddd_vkv(long4, int4/*(k)*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __vaddd_vkv(long8, int8/*(k)*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __vaddd_vkv(ulong4, uint4/*(k={0-2147483647})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __vaddd_vkv(ulong8, uint8/*(k={0-2147483647})*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vaddd_vvv                                                            */
/*----------------------------------------------------------------------------*/

/* VADDD */
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __vaddd_vvv(long4, long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __vaddd_vvv(long8, long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __vaddd_vvv(ulong4, ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __vaddd_vvv(ulong8, ulong8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern clong2 __vaddd_vvv(clong2, clong2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern clong4 __vaddd_vvv(clong4, clong4);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vadddp_vvv                                                           */
/*----------------------------------------------------------------------------*/

/* VADDDP */
#if __C7X_VEC_SIZE_BITS__ == 256
extern double4 __vadddp_vvv(double4, double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern double8 __vadddp_vvv(double8, double8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cdouble2 __vadddp_vvv(cdouble2, cdouble2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cdouble4 __vadddp_vvv(cdouble4, cdouble4);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vaddh_vkv                                                            */
/*----------------------------------------------------------------------------*/

/* VADDH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vaddh_vkv(short16, short16/*(k)*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vaddh_vkv(short32, short32/*(k)*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vaddh_vkv(ushort16, ushort16/*(k)*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vaddh_vkv(ushort32, ushort32/*(k)*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vaddh_vvv                                                            */
/*----------------------------------------------------------------------------*/

/* VADDH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vaddh_vvv(short16, short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vaddh_vvv(short32, short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vaddh_vvv(ushort16, ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vaddh_vvv(ushort32, ushort32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cshort8 __vaddh_vvv(cshort8, cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cshort16 __vaddh_vvv(cshort16, cshort16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vaddsp_vvv                                                           */
/*----------------------------------------------------------------------------*/

/* VADDSP */
#if __C7X_VEC_SIZE_BITS__ == 256
extern float8 __vaddsp_vvv(float8, float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern float16 __vaddsp_vvv(float16, float16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cfloat4 __vaddsp_vvv(cfloat4, cfloat4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cfloat8 __vaddsp_vvv(cfloat8, cfloat8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vaddw_vkv                                                            */
/*----------------------------------------------------------------------------*/

/* VADDW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vaddw_vkv(int8, int8/*(k)*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vaddw_vkv(int16, int16/*(k)*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vaddw_vkv(uint8, uint8/*(k)*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vaddw_vkv(uint16, uint16/*(k)*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vaddw_vvv                                                            */
/*----------------------------------------------------------------------------*/

/* VADDW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vaddw_vvv(int8, int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vaddw_vvv(int16, int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vaddw_vvv(uint8, uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vaddw_vvv(uint16, uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cint4 __vaddw_vvv(cint4, cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cint8 __vaddw_vvv(cint8, cint8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vandnw_vkv                                                           */
/*----------------------------------------------------------------------------*/

/* VANDNW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vandnw_vkv(int8, int8/*(k)*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vandnw_vkv(int16, int16/*(k)*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vandnw_vkv(uint8, uint8/*(k)*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vandnw_vkv(uint16, uint16/*(k)*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vandnw_vvv                                                           */
/*----------------------------------------------------------------------------*/

/* VANDNW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __vandnw_vvv(char32, char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __vandnw_vvv(char64, char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vandnw_vvv(uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vandnw_vvv(uchar64, uchar64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vandnw_vvv(short16, short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vandnw_vvv(short32, short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vandnw_vvv(ushort16, ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vandnw_vvv(ushort32, ushort32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vandnw_vvv(int8, int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vandnw_vvv(int16, int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vandnw_vvv(uint8, uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vandnw_vvv(uint16, uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __vandnw_vvv(long4, long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __vandnw_vvv(long8, long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __vandnw_vvv(ulong4, ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __vandnw_vvv(ulong8, ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vandw_vkv                                                            */
/*----------------------------------------------------------------------------*/

/* VANDW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vandw_vkv(int8, int8/*(k)*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vandw_vkv(int16, int16/*(k)*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vandw_vkv(uint8, uint8/*(k)*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vandw_vkv(uint16, uint16/*(k)*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vandw_vvv                                                            */
/*----------------------------------------------------------------------------*/

/* VANDW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __vandw_vvv(char32, char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __vandw_vvv(char64, char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vandw_vvv(uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vandw_vvv(uchar64, uchar64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vandw_vvv(short16, short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vandw_vvv(short32, short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vandw_vvv(ushort16, ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vandw_vvv(ushort32, ushort32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vandw_vvv(int8, int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vandw_vvv(int16, int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vandw_vvv(uint8, uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vandw_vvv(uint16, uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __vandw_vvv(long4, long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __vandw_vvv(long8, long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __vandw_vvv(ulong4, ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __vandw_vvv(ulong8, ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vapysb_vvv                                                           */
/*----------------------------------------------------------------------------*/

/* VAPYSB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __vapysb_vvv(char32, char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __vapysb_vvv(char64, char64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vapysd_vvv                                                           */
/*----------------------------------------------------------------------------*/

/* VAPYSD */
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __vapysd_vvv(long4, long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __vapysd_vvv(long8, long8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vapysh_vvv                                                           */
/*----------------------------------------------------------------------------*/

/* VAPYSH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vapysh_vvv(short16, short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vapysh_vvv(short32, short32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vapysw_vvv                                                           */
/*----------------------------------------------------------------------------*/

/* VAPYSW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vapysw_vvv(int8, int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vapysw_vvv(int16, int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vavgb_vvv                                                            */
/*----------------------------------------------------------------------------*/

/* VAVGB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __vavgb_vvv(char32, char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __vavgb_vvv(char64, char64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vavgd_vvv                                                            */
/*----------------------------------------------------------------------------*/

/* VAVGD */
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __vavgd_vvv(long4, long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __vavgd_vvv(long8, long8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vavgh_vvv                                                            */
/*----------------------------------------------------------------------------*/

/* VAVGH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vavgh_vvv(short16, short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vavgh_vvv(short32, short32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vavgnrb_vvv                                                          */
/*----------------------------------------------------------------------------*/

/* VAVGNRB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __vavgnrb_vvv(char32, char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __vavgnrb_vvv(char64, char64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vavgnrd_vvv                                                          */
/*----------------------------------------------------------------------------*/

/* VAVGNRD */
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __vavgnrd_vvv(long4, long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __vavgnrd_vvv(long8, long8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vavgnrh_vvv                                                          */
/*----------------------------------------------------------------------------*/

/* VAVGNRH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vavgnrh_vvv(short16, short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vavgnrh_vvv(short32, short32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vavgnrub_vvv                                                         */
/*----------------------------------------------------------------------------*/

/* VAVGNRUB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vavgnrub_vvv(uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vavgnrub_vvv(uchar64, uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vavgnrud_vvv                                                         */
/*----------------------------------------------------------------------------*/

/* VAVGNRUD */
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __vavgnrud_vvv(ulong4, ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __vavgnrud_vvv(ulong8, ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vavgnruh_vvv                                                         */
/*----------------------------------------------------------------------------*/

/* VAVGNRUH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vavgnruh_vvv(ushort16, ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vavgnruh_vvv(ushort32, ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vavgnruw_vvv                                                         */
/*----------------------------------------------------------------------------*/

/* VAVGNRUW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vavgnruw_vvv(uint8, uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vavgnruw_vvv(uint16, uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vavgnrw_vvv                                                          */
/*----------------------------------------------------------------------------*/

/* VAVGNRW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vavgnrw_vvv(int8, int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vavgnrw_vvv(int16, int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vavgub_vvv                                                           */
/*----------------------------------------------------------------------------*/

/* VAVGUB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vavgub_vvv(uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vavgub_vvv(uchar64, uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vavgud_vvv                                                           */
/*----------------------------------------------------------------------------*/

/* VAVGUD */
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __vavgud_vvv(ulong4, ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __vavgud_vvv(ulong8, ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vavguh_vvv                                                           */
/*----------------------------------------------------------------------------*/

/* VAVGUH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vavguh_vvv(ushort16, ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vavguh_vvv(ushort32, ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vavguw_vvv                                                           */
/*----------------------------------------------------------------------------*/

/* VAVGUW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vavguw_vvv(uint8, uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vavguw_vvv(uint16, uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vavgw_vvv                                                            */
/*----------------------------------------------------------------------------*/

/* VAVGW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vavgw_vvv(int8, int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vavgw_vvv(int16, int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vbinlogw_vv                                                          */
/*----------------------------------------------------------------------------*/

/* VBINLOGW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vbinlogw_vv(uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vbinlogw_vv(uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vbitcntb_vv                                                          */
/*----------------------------------------------------------------------------*/

/* VBITCNTB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __vbitcntb_vv(char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __vbitcntb_vv(char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vbitcntb_vv(uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vbitcntb_vv(uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vbitcntd_vv                                                          */
/*----------------------------------------------------------------------------*/

/* VBITCNTD */
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __vbitcntd_vv(long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __vbitcntd_vv(long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __vbitcntd_vv(ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __vbitcntd_vv(ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vbitcnth_vv                                                          */
/*----------------------------------------------------------------------------*/

/* VBITCNTH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vbitcnth_vv(short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vbitcnth_vv(short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vbitcnth_vv(ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vbitcnth_vv(ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vbitcntw_vv                                                          */
/*----------------------------------------------------------------------------*/

/* VBITCNTW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vbitcntw_vv(int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vbitcntw_vv(int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vbitcntw_vv(uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vbitcntw_vv(uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vbitdeald_vv                                                         */
/*----------------------------------------------------------------------------*/

/* VBITDEALD */
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __vbitdeald_vv(long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __vbitdeald_vv(long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __vbitdeald_vv(ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __vbitdeald_vv(ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vbitdealw_vv                                                         */
/*----------------------------------------------------------------------------*/

/* VBITDEALW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vbitdealw_vv(int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vbitdealw_vv(int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vbitdealw_vv(uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vbitdealw_vv(uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vbitrd_vv                                                            */
/*----------------------------------------------------------------------------*/

/* VBITRD */
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __vbitrd_vv(long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __vbitrd_vv(long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __vbitrd_vv(ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __vbitrd_vv(ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vbitrw_vv                                                            */
/*----------------------------------------------------------------------------*/

/* VBITRW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vbitrw_vv(int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vbitrw_vv(int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vbitrw_vv(uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vbitrw_vv(uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vbitshfld_vv                                                         */
/*----------------------------------------------------------------------------*/

/* VBITSHFLD */
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __vbitshfld_vv(long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __vbitshfld_vv(long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __vbitshfld_vv(ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __vbitshfld_vv(ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vbitshflw_vv                                                         */
/*----------------------------------------------------------------------------*/

/* VBITSHFLW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vbitshflw_vv(int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vbitshflw_vv(int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vbitshflw_vv(uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vbitshflw_vv(uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vbittran8b_vv                                                        */
/*----------------------------------------------------------------------------*/

/* VBITTRAN8B */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vbittran8b_vv(uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vbittran8b_vv(uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vbpackh_vvv                                                          */
/*----------------------------------------------------------------------------*/

/* VBPACKH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __vbpackh_vvv(char32, char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __vbpackh_vvv(char64, char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vbpackh_vvv(uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vbpackh_vvv(uchar64, uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vbpackl_vvv                                                          */
/*----------------------------------------------------------------------------*/

/* VBPACKL */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __vbpackl_vvv(char32, char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __vbpackl_vvv(char64, char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vbpackl_vvv(uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vbpackl_vvv(uchar64, uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vbunpkd_vv                                                           */
/*----------------------------------------------------------------------------*/

/* VBUNPKD */
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __vbunpkd_vv(char4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __vbunpkd_vv(char8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern clong2 __vbunpkd_vv(cchar2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern clong4 __vbunpkd_vv(cchar4);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vbunpkdu_vv                                                          */
/*----------------------------------------------------------------------------*/

/* VBUNPKDU */
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __vbunpkdu_vv(uchar4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __vbunpkdu_vv(uchar8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vbunpkh_vv                                                           */
/*----------------------------------------------------------------------------*/

/* VBUNPKH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vbunpkh_vv(char16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vbunpkh_vv(char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cshort8 __vbunpkh_vv(cchar8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cshort16 __vbunpkh_vv(cchar16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vbunpkhh_vv                                                          */
/*----------------------------------------------------------------------------*/

/* VBUNPKHH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vbunpkhh_vv(char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vbunpkhh_vv(char64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vbunpkhl_vv                                                          */
/*----------------------------------------------------------------------------*/

/* VBUNPKHL */
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vbunpkhl_vv(char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vbunpkhl_vv(char64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vbunpkhu_vv                                                          */
/*----------------------------------------------------------------------------*/

/* VBUNPKHU */
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vbunpkhu_vv(uchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vbunpkhu_vv(uchar32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vbunpkuhh_vv                                                         */
/*----------------------------------------------------------------------------*/

/* VBUNPKUHH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vbunpkuhh_vv(uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vbunpkuhh_vv(uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vbunpkuhl_vv                                                         */
/*----------------------------------------------------------------------------*/

/* VBUNPKUHL */
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vbunpkuhl_vv(uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vbunpkuhl_vv(uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vbunpkw_vv                                                           */
/*----------------------------------------------------------------------------*/

/* VBUNPKW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vbunpkw_vv(char8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vbunpkw_vv(char16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cint4 __vbunpkw_vv(cchar4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cint8 __vbunpkw_vv(cchar8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vbunpkwu_vv                                                          */
/*----------------------------------------------------------------------------*/

/* VBUNPKWU */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vbunpkwu_vv(uchar8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vbunpkwu_vv(uchar16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vccdotp2hw_vvv                                                       */
/*----------------------------------------------------------------------------*/

/* VCCDOTP2HW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cint4 __vccdotp2hw_vvv(cshort8, cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cint8 __vccdotp2hw_vvv(cshort16, cshort16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vccmatmpyhw_vww                                                      */
/*----------------------------------------------------------------------------*/

/* VCCMATMPYHW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern void __vccmatmpyhw_vww(cshort8, cshort8, cshort8, cint4&, cint4&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __vccmatmpyhw_vww(cshort16, cshort16, cshort16, cint8&, cint8&);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vccmatmpyr1hh_vwv                                                    */
/*----------------------------------------------------------------------------*/

/* VCCMATMPYR1HH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cshort8 __vccmatmpyr1hh_vwv(cshort8, cshort8, cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cshort16 __vccmatmpyr1hh_vwv(cshort16, cshort16, cshort16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vccmpyhw_vvw                                                         */
/*----------------------------------------------------------------------------*/

/* VCCMPYHW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern void __vccmpyhw_vvw(cshort8, cshort8, cint4&, cint4&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __vccmpyhw_vvw(cshort16, cshort16, cint8&, cint8&);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vccmpyr1hh_vvv                                                       */
/*----------------------------------------------------------------------------*/

/* VCCMPYR1HH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cshort8 __vccmpyr1hh_vvv(cshort8, cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cshort16 __vccmpyr1hh_vvv(cshort16, cshort16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vccmpyr1ww_vvv                                                       */
/*----------------------------------------------------------------------------*/

/* VCCMPYR1WW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cint4 __vccmpyr1ww_vvv(cint4, cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cint8 __vccmpyr1ww_vvv(cint8, cint8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcdotp2hw_vvv                                                        */
/*----------------------------------------------------------------------------*/

/* VCDOTP2HW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cint4 __vcdotp2hw_vvv(cshort8, cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cint8 __vcdotp2hw_vvv(cshort16, cshort16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcdotpm2opn16b32h_yvvv                                               */
/*----------------------------------------------------------------------------*/

/* VCDOTPM2OPN16B32H */
#if __C7X_VEC_SIZE_BITS__ == 512
extern cshort16 __vcdotpm2opn16b32h_yvvv(ushort32, uint64_t, cchar32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcdotpm2opn1h32h_yvvv                                                */
/*----------------------------------------------------------------------------*/

/* VCDOTPM2OPN1H32H */
#if __C7X_VEC_SIZE_BITS__ == 512
extern cshort16 __vcdotpm2opn1h32h_yvvv(ushort32, uint32_t, cshort16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcdotpm2opn8h16w_yvvv                                                */
/*----------------------------------------------------------------------------*/

/* VCDOTPM2OPN8H16W */
#if __C7X_VEC_SIZE_BITS__ == 512
extern cint8 __vcdotpm2opn8h16w_yvvv(ulong8, uint4, cshort8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcdotpm2opn8w16w_yvvv                                                */
/*----------------------------------------------------------------------------*/

/* VCDOTPM2OPN8W16W */
#if __C7X_VEC_SIZE_BITS__ == 512
extern cint8 __vcdotpm2opn8w16w_yvvv(ulong8, uint4, cint8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcdotpm32opn16b32h_yvvv                                              */
/*----------------------------------------------------------------------------*/

/* VCDOTPM32OPN16B32H */
#if __C7X_VEC_SIZE_BITS__ == 512
extern cshort16 __vcdotpm32opn16b32h_yvvv(ushort32, ulong4, cchar32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vclassdp_vv                                                          */
/*----------------------------------------------------------------------------*/

/* VCLASSDP */
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __vclassdp_vv(double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __vclassdp_vv(double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vclasssp_vv                                                          */
/*----------------------------------------------------------------------------*/

/* VCLASSSP */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vclasssp_vv(float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vclasssp_vv(float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcmatmpyhw_vww                                                       */
/*----------------------------------------------------------------------------*/

/* VCMATMPYHW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern void __vcmatmpyhw_vww(cshort8, cshort8, cshort8, cint4&, cint4&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __vcmatmpyhw_vww(cshort16, cshort16, cshort16, cint8&, cint8&);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcmatmpyr1hh_vwv                                                     */
/*----------------------------------------------------------------------------*/

/* VCMATMPYR1HH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cshort8 __vcmatmpyr1hh_vwv(cshort8, cshort8, cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cshort16 __vcmatmpyr1hh_vwv(cshort16, cshort16, cshort16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcmaxb_vvv                                                           */
/*----------------------------------------------------------------------------*/

/* VCMAXB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __vcmaxb_vvv(char32, char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __vcmaxb_vvv(char64, char64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcmaxh_vvv                                                           */
/*----------------------------------------------------------------------------*/

/* VCMAXH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vcmaxh_vvv(short16, short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vcmaxh_vvv(short32, short32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcmaxpb_vvp                                                          */
/*----------------------------------------------------------------------------*/

/* VCMAXPB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern void __vcmaxpb_vvp(char32, char32&, __vpred&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __vcmaxpb_vvp(char64, char64&, __vpred&);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcmaxph_vvp                                                          */
/*----------------------------------------------------------------------------*/

/* VCMAXPH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern void __vcmaxph_vvp(short16, short16&, __vpred&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __vcmaxph_vvp(short32, short32&, __vpred&);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcmpeqb_vvp                                                          */
/*----------------------------------------------------------------------------*/

/* VCMPEQB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern __vpred __vcmpeqb_vvp(char32, char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __vcmpeqb_vvp(char64, char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern __vpred __vcmpeqb_vvp(uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __vcmpeqb_vvp(uchar64, uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcmpeqd_vvp                                                          */
/*----------------------------------------------------------------------------*/

/* VCMPEQD */
#if __C7X_VEC_SIZE_BITS__ == 256
extern __vpred __vcmpeqd_vvp(long4, long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __vcmpeqd_vvp(long8, long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern __vpred __vcmpeqd_vvp(ulong4, ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __vcmpeqd_vvp(ulong8, ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcmpeqdp_vvp                                                         */
/*----------------------------------------------------------------------------*/

/* VCMPEQDP */
#if __C7X_VEC_SIZE_BITS__ == 256
extern __vpred __vcmpeqdp_vvp(double4, double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __vcmpeqdp_vvp(double8, double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcmpeqh_vvp                                                          */
/*----------------------------------------------------------------------------*/

/* VCMPEQH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern __vpred __vcmpeqh_vvp(short16, short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __vcmpeqh_vvp(short32, short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern __vpred __vcmpeqh_vvp(ushort16, ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __vcmpeqh_vvp(ushort32, ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcmpeqsp_vvp                                                         */
/*----------------------------------------------------------------------------*/

/* VCMPEQSP */
#if __C7X_VEC_SIZE_BITS__ == 256
extern __vpred __vcmpeqsp_vvp(float8, float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __vcmpeqsp_vvp(float16, float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcmpeqw_vvp                                                          */
/*----------------------------------------------------------------------------*/

/* VCMPEQW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern __vpred __vcmpeqw_vvp(int8, int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __vcmpeqw_vvp(int16, int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern __vpred __vcmpeqw_vvp(uint8, uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __vcmpeqw_vvp(uint16, uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcmpgeb_vvp                                                          */
/*----------------------------------------------------------------------------*/

/* VCMPGEB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern __vpred __vcmpgeb_vvp(char32, char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __vcmpgeb_vvp(char64, char64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcmpged_vvp                                                          */
/*----------------------------------------------------------------------------*/

/* VCMPGED */
#if __C7X_VEC_SIZE_BITS__ == 256
extern __vpred __vcmpged_vvp(long4, long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __vcmpged_vvp(long8, long8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcmpgeh_vvp                                                          */
/*----------------------------------------------------------------------------*/

/* VCMPGEH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern __vpred __vcmpgeh_vvp(short16, short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __vcmpgeh_vvp(short32, short32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcmpgeub_vvp                                                         */
/*----------------------------------------------------------------------------*/

/* VCMPGEUB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern __vpred __vcmpgeub_vvp(uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __vcmpgeub_vvp(uchar64, uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcmpgeud_vvp                                                         */
/*----------------------------------------------------------------------------*/

/* VCMPGEUD */
#if __C7X_VEC_SIZE_BITS__ == 256
extern __vpred __vcmpgeud_vvp(ulong4, ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __vcmpgeud_vvp(ulong8, ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcmpgeuh_vvp                                                         */
/*----------------------------------------------------------------------------*/

/* VCMPGEUH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern __vpred __vcmpgeuh_vvp(ushort16, ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __vcmpgeuh_vvp(ushort32, ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcmpgeuw_vvp                                                         */
/*----------------------------------------------------------------------------*/

/* VCMPGEUW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern __vpred __vcmpgeuw_vvp(uint8, uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __vcmpgeuw_vvp(uint16, uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcmpgew_vvp                                                          */
/*----------------------------------------------------------------------------*/

/* VCMPGEW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern __vpred __vcmpgew_vvp(int8, int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __vcmpgew_vvp(int16, int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcmpgtb_vvp                                                          */
/*----------------------------------------------------------------------------*/

/* VCMPGTB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern __vpred __vcmpgtb_vvp(char32, char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __vcmpgtb_vvp(char64, char64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcmpgtd_vvp                                                          */
/*----------------------------------------------------------------------------*/

/* VCMPGTD */
#if __C7X_VEC_SIZE_BITS__ == 256
extern __vpred __vcmpgtd_vvp(long4, long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __vcmpgtd_vvp(long8, long8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcmpgth_vvp                                                          */
/*----------------------------------------------------------------------------*/

/* VCMPGTH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern __vpred __vcmpgth_vvp(short16, short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __vcmpgth_vvp(short32, short32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcmpgtub_vvp                                                         */
/*----------------------------------------------------------------------------*/

/* VCMPGTUB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern __vpred __vcmpgtub_vvp(uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __vcmpgtub_vvp(uchar64, uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcmpgtud_vvp                                                         */
/*----------------------------------------------------------------------------*/

/* VCMPGTUD */
#if __C7X_VEC_SIZE_BITS__ == 256
extern __vpred __vcmpgtud_vvp(ulong4, ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __vcmpgtud_vvp(ulong8, ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcmpgtuh_vvp                                                         */
/*----------------------------------------------------------------------------*/

/* VCMPGTUH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern __vpred __vcmpgtuh_vvp(ushort16, ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __vcmpgtuh_vvp(ushort32, ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcmpgtuw_vvp                                                         */
/*----------------------------------------------------------------------------*/

/* VCMPGTUW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern __vpred __vcmpgtuw_vvp(uint8, uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __vcmpgtuw_vvp(uint16, uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcmpgtw_vvp                                                          */
/*----------------------------------------------------------------------------*/

/* VCMPGTW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern __vpred __vcmpgtw_vvp(int8, int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __vcmpgtw_vvp(int16, int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcmpledp_vvp                                                         */
/*----------------------------------------------------------------------------*/

/* VCMPLEDP */
#if __C7X_VEC_SIZE_BITS__ == 256
extern __vpred __vcmpledp_vvp(double4, double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __vcmpledp_vvp(double8, double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcmplesp_vvp                                                         */
/*----------------------------------------------------------------------------*/

/* VCMPLESP */
#if __C7X_VEC_SIZE_BITS__ == 256
extern __vpred __vcmplesp_vvp(float8, float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __vcmplesp_vvp(float16, float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcmpltdp_vvp                                                         */
/*----------------------------------------------------------------------------*/

/* VCMPLTDP */
#if __C7X_VEC_SIZE_BITS__ == 256
extern __vpred __vcmpltdp_vvp(double4, double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __vcmpltdp_vvp(double8, double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcmpltsp_vvp                                                         */
/*----------------------------------------------------------------------------*/

/* VCMPLTSP */
#if __C7X_VEC_SIZE_BITS__ == 256
extern __vpred __vcmpltsp_vvp(float8, float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern __vpred __vcmpltsp_vvp(float16, float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcmpyhw_vvw                                                          */
/*----------------------------------------------------------------------------*/

/* VCMPYHW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern void __vcmpyhw_vvw(cshort8, cshort8, cint4&, cint4&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __vcmpyhw_vvw(cshort16, cshort16, cint8&, cint8&);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcmpyr1hh_vvv                                                        */
/*----------------------------------------------------------------------------*/

/* VCMPYR1HH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cshort8 __vcmpyr1hh_vvv(cshort8, cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cshort16 __vcmpyr1hh_vvv(cshort16, cshort16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcmpyr1ww_vvv                                                        */
/*----------------------------------------------------------------------------*/

/* VCMPYR1WW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cint4 __vcmpyr1ww_vvv(cint4, cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cint8 __vcmpyr1ww_vvv(cint8, cint8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcmpyrhh_vvv                                                         */
/*----------------------------------------------------------------------------*/

/* VCMPYRHH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cshort8 __vcmpyrhh_vvv(cshort8, cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cshort16 __vcmpyrhh_vvv(cshort16, cshort16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcmpysp_vvw                                                          */
/*----------------------------------------------------------------------------*/

/* VCMPYSP */
#if __C7X_VEC_SIZE_BITS__ == 256
extern void __vcmpysp_vvw(cfloat4, cfloat4, float8&, float8&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __vcmpysp_vvw(cfloat8, cfloat8, float16&, float16&);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcrot270h_vv                                                         */
/*----------------------------------------------------------------------------*/

/* VCROT270H */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cshort8 __vcrot270h_vv(cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cshort16 __vcrot270h_vv(cshort16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcrot270sp_vv                                                        */
/*----------------------------------------------------------------------------*/

/* VCROT270SP */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cfloat4 __vcrot270sp_vv(cfloat4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cfloat8 __vcrot270sp_vv(cfloat8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcrot270w_vv                                                         */
/*----------------------------------------------------------------------------*/

/* VCROT270W */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cint4 __vcrot270w_vv(cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cint8 __vcrot270w_vv(cint8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcrot90h_vv                                                          */
/*----------------------------------------------------------------------------*/

/* VCROT90H */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cshort8 __vcrot90h_vv(cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cshort16 __vcrot90h_vv(cshort16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcrot90sp_vv                                                         */
/*----------------------------------------------------------------------------*/

/* VCROT90SP */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cfloat4 __vcrot90sp_vv(cfloat4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cfloat8 __vcrot90sp_vv(cfloat8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vcrot90w_vv                                                          */
/*----------------------------------------------------------------------------*/

/* VCROT90W */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cint4 __vcrot90w_vv(cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cint8 __vcrot90w_vv(cint8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdeal2b_vv                                                           */
/*----------------------------------------------------------------------------*/

/* VDEAL2B */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __vdeal2b_vv(char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __vdeal2b_vv(char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vdeal2b_vv(uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vdeal2b_vv(uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdeal2d_vv                                                           */
/*----------------------------------------------------------------------------*/

/* VDEAL2D */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cint4 __vdeal2d_vv(cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cint8 __vdeal2d_vv(cint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cfloat4 __vdeal2d_vv(cfloat4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cfloat8 __vdeal2d_vv(cfloat8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __vdeal2d_vv(long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __vdeal2d_vv(long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __vdeal2d_vv(ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __vdeal2d_vv(ulong8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern double4 __vdeal2d_vv(double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern double8 __vdeal2d_vv(double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdeal2h_vv                                                           */
/*----------------------------------------------------------------------------*/

/* VDEAL2H */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cchar16 __vdeal2h_vv(cchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cchar32 __vdeal2h_vv(cchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vdeal2h_vv(short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vdeal2h_vv(short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vdeal2h_vv(ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vdeal2h_vv(ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdeal2w_vv                                                           */
/*----------------------------------------------------------------------------*/

/* VDEAL2W */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cshort8 __vdeal2w_vv(cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cshort16 __vdeal2w_vv(cshort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vdeal2w_vv(int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vdeal2w_vv(int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vdeal2w_vv(uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vdeal2w_vv(uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern float8 __vdeal2w_vv(float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern float16 __vdeal2w_vv(float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdeal4b_vv                                                           */
/*----------------------------------------------------------------------------*/

/* VDEAL4B */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __vdeal4b_vv(char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __vdeal4b_vv(char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vdeal4b_vv(uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vdeal4b_vv(uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdeal4h_vv                                                           */
/*----------------------------------------------------------------------------*/

/* VDEAL4H */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cchar16 __vdeal4h_vv(cchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cchar32 __vdeal4h_vv(cchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vdeal4h_vv(short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vdeal4h_vv(short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vdeal4h_vv(ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vdeal4h_vv(ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdotp2hd_vvw                                                         */
/*----------------------------------------------------------------------------*/

/* VDOTP2HD */
#if __C7X_VEC_SIZE_BITS__ == 256
extern void __vdotp2hd_vvw(short16, short16, long4&, long4&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __vdotp2hd_vvw(short32, short32, long8&, long8&);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdotp2hw_vvv                                                         */
/*----------------------------------------------------------------------------*/

/* VDOTP2HW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vdotp2hw_vvv(short16, short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vdotp2hw_vvv(short32, short32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdotp2nwd_vvv                                                        */
/*----------------------------------------------------------------------------*/

/* VDOTP2NWD */
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __vdotp2nwd_vvv(int8, int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __vdotp2nwd_vvv(int16, int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdotp2nxwd_vvv                                                       */
/*----------------------------------------------------------------------------*/

/* VDOTP2NXWD */
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __vdotp2nxwd_vvv(int8, int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __vdotp2nxwd_vvv(int16, int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdotp2subh_vvv                                                       */
/*----------------------------------------------------------------------------*/

/* VDOTP2SUBH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vdotp2subh_vvv(char32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vdotp2subh_vvv(char64, uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdotp2suhd_vvw                                                       */
/*----------------------------------------------------------------------------*/

/* VDOTP2SUHD */
#if __C7X_VEC_SIZE_BITS__ == 256
extern void __vdotp2suhd_vvw(short16, ushort16, long4&, long4&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __vdotp2suhd_vvw(short32, ushort32, long8&, long8&);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdotp2suhw_vvv                                                       */
/*----------------------------------------------------------------------------*/

/* VDOTP2SUHW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vdotp2suhw_vvv(short16, ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vdotp2suhw_vvv(short32, ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdotp2ubh_vvv                                                        */
/*----------------------------------------------------------------------------*/

/* VDOTP2UBH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vdotp2ubh_vvv(uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vdotp2ubh_vvv(uchar64, uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdotp2uhd_vvw                                                        */
/*----------------------------------------------------------------------------*/

/* VDOTP2UHD */
#if __C7X_VEC_SIZE_BITS__ == 256
extern void __vdotp2uhd_vvw(ushort16, ushort16, ulong4&, ulong4&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __vdotp2uhd_vvw(ushort32, ushort32, ulong8&, ulong8&);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdotp2uhw_vvv                                                        */
/*----------------------------------------------------------------------------*/

/* VDOTP2UHW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vdotp2uhw_vvv(ushort16, ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vdotp2uhw_vvv(ushort32, ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdotp2wd_vvv                                                         */
/*----------------------------------------------------------------------------*/

/* VDOTP2WD */
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __vdotp2wd_vvv(int8, int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __vdotp2wd_vvv(int16, int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdotp2xwd_vvv                                                        */
/*----------------------------------------------------------------------------*/

/* VDOTP2XWD */
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __vdotp2xwd_vvv(int8, int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __vdotp2xwd_vvv(int16, int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdotp4hd_vvv                                                         */
/*----------------------------------------------------------------------------*/

/* VDOTP4HD */
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __vdotp4hd_vvv(short16, short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __vdotp4hd_vvv(short32, short32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdotp4hw_wwv                                                         */
/*----------------------------------------------------------------------------*/

/* VDOTP4HW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vdotp4hw_wwv(short16, short16, short16, short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vdotp4hw_wwv(short32, short32, short32, short32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdotp4subw_vvv                                                       */
/*----------------------------------------------------------------------------*/

/* VDOTP4SUBW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vdotp4subw_vvv(char32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vdotp4subw_vvv(char64, uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdotp4suhd_vvv                                                       */
/*----------------------------------------------------------------------------*/

/* VDOTP4SUHD */
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __vdotp4suhd_vvv(short16, ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __vdotp4suhd_vvv(short32, ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdotp4suhw_wwv                                                       */
/*----------------------------------------------------------------------------*/

/* VDOTP4SUHW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vdotp4suhw_wwv(short16, short16, ushort16, ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vdotp4suhw_wwv(short32, short32, ushort32, ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdotp4ubw_vvv                                                        */
/*----------------------------------------------------------------------------*/

/* VDOTP4UBW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vdotp4ubw_vvv(uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vdotp4ubw_vvv(uchar64, uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdotp4uhd_vvv                                                        */
/*----------------------------------------------------------------------------*/

/* VDOTP4UHD */
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __vdotp4uhd_vvv(ushort16, ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __vdotp4uhd_vvv(ushort32, ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdotp8subw_vvv                                                       */
/*----------------------------------------------------------------------------*/

/* VDOTP8SUBW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vdotp8subw_vvv(char32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vdotp8subw_vvv(char64, uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdotpmpn16b32h_yvvv                                                  */
/*----------------------------------------------------------------------------*/

/* VDOTPMPN16B32H */
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vdotpmpn16b32h_yvvv(ushort32, ushort32, char16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdotpmpn16h16w_yvvv                                                  */
/*----------------------------------------------------------------------------*/

/* VDOTPMPN16H16W */
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vdotpmpn16h16w_yvvv(ushort32, ushort16, short16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdotpmpn16w8d_yvvv                                                   */
/*----------------------------------------------------------------------------*/

/* VDOTPMPN16W8D */
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __vdotpmpn16w8d_yvvv(ushort32, ushort8, int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdotpmpn32b16h_yvvv                                                  */
/*----------------------------------------------------------------------------*/

/* VDOTPMPN32B16H */
#if __C7X_VEC_SIZE_BITS__ == 512
extern short16 __vdotpmpn32b16h_yvvv(uint16, uint16, char32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdotpmpn32b16w_yvvv                                                  */
/*----------------------------------------------------------------------------*/

/* VDOTPMPN32B16W */
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vdotpmpn32b16w_yvvv(uint16, uint16, char32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdotpmpn32h8w_yvvv                                                   */
/*----------------------------------------------------------------------------*/

/* VDOTPMPN32H8W */
#if __C7X_VEC_SIZE_BITS__ == 512
extern int8 __vdotpmpn32h8w_yvvv(uint8, uint8, short32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdotpmpnu16h16w_yvvv                                                 */
/*----------------------------------------------------------------------------*/

/* VDOTPMPNU16H16W */
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vdotpmpnu16h16w_yvvv(ushort32, ushort16, ushort16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdotpmpnu16w8d_yvvv                                                  */
/*----------------------------------------------------------------------------*/

/* VDOTPMPNU16W8D */
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __vdotpmpnu16w8d_yvvv(ushort32, ushort8, uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdotpmpnu32b16h_yvvv                                                 */
/*----------------------------------------------------------------------------*/

/* VDOTPMPNU32B16H */
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort16 __vdotpmpnu32b16h_yvvv(uint16, uint16, uchar32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdotpmpnu32b16w_yvvv                                                 */
/*----------------------------------------------------------------------------*/

/* VDOTPMPNU32B16W */
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vdotpmpnu32b16w_yvvv(uint16, uint16, uchar32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdotpmpnu32h8w_yvvv                                                  */
/*----------------------------------------------------------------------------*/

/* VDOTPMPNU32H8W */
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint8 __vdotpmpnu32h8w_yvvv(uint8, uint8, ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdpackh_vvv                                                          */
/*----------------------------------------------------------------------------*/

/* VDPACKH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cint4 __vdpackh_vvv(cint4, cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cint8 __vdpackh_vvv(cint8, cint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cfloat4 __vdpackh_vvv(cfloat4, cfloat4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cfloat8 __vdpackh_vvv(cfloat8, cfloat8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __vdpackh_vvv(long4, long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __vdpackh_vvv(long8, long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __vdpackh_vvv(ulong4, ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __vdpackh_vvv(ulong8, ulong8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern double4 __vdpackh_vvv(double4, double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern double8 __vdpackh_vvv(double8, double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdpackl_vvv                                                          */
/*----------------------------------------------------------------------------*/

/* VDPACKL */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cint4 __vdpackl_vvv(cint4, cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cint8 __vdpackl_vvv(cint8, cint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cfloat4 __vdpackl_vvv(cfloat4, cfloat4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cfloat8 __vdpackl_vvv(cfloat8, cfloat8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __vdpackl_vvv(long4, long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __vdpackl_vvv(long8, long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __vdpackl_vvv(ulong4, ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __vdpackl_vvv(ulong8, ulong8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern double4 __vdpackl_vvv(double4, double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern double8 __vdpackl_vvv(double8, double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdpint_vv                                                            */
/*----------------------------------------------------------------------------*/

/* VDPINT */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vdpint_vv(double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vdpint_vv(double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdpsp_vv                                                             */
/*----------------------------------------------------------------------------*/

/* VDPSP */
#if __C7X_VEC_SIZE_BITS__ == 256
extern float8 __vdpsp_vv(double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern float16 __vdpsp_vv(double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdptrunc_vv                                                          */
/*----------------------------------------------------------------------------*/

/* VDPTRUNC */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vdptrunc_vv(double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vdptrunc_vv(double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdsad16ou8h8w_vvv                                                    */
/*----------------------------------------------------------------------------*/

/* VDSAD16OU8H8W */
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vdsad16ou8h8w_vvv(ushort32, ushort16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdsad8ou16b16h_vvv                                                   */
/*----------------------------------------------------------------------------*/

/* VDSAD8OU16B16H */
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vdsad8ou16b16h_vvv(uchar64, uchar32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdsadm16ou8h8w_yvvv                                                  */
/*----------------------------------------------------------------------------*/

/* VDSADM16OU8H8W */
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vdsadm16ou8h8w_yvvv(uchar64, ushort32, ushort16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdsadm8ou16b16h_yvvv                                                 */
/*----------------------------------------------------------------------------*/

/* VDSADM8OU16B16H */
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vdsadm8ou16b16h_yvvv(uchar64, uchar64, uchar32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdsortddh_vv                                                         */
/*----------------------------------------------------------------------------*/

/* VDSORTDDH */
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vdsortddh_vv(short32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdsortdduh_vv                                                        */
/*----------------------------------------------------------------------------*/

/* VDSORTDDUH */
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vdsortdduh_vv(ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdsortdih_vv                                                         */
/*----------------------------------------------------------------------------*/

/* VDSORTDIH */
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vdsortdih_vv(short32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdsortdiuh_vv                                                        */
/*----------------------------------------------------------------------------*/

/* VDSORTDIUH */
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vdsortdiuh_vv(ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdsortidh_vv                                                         */
/*----------------------------------------------------------------------------*/

/* VDSORTIDH */
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vdsortidh_vv(short32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdsortiduh_vv                                                        */
/*----------------------------------------------------------------------------*/

/* VDSORTIDUH */
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vdsortiduh_vv(ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdsortiih_vv                                                         */
/*----------------------------------------------------------------------------*/

/* VDSORTIIH */
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vdsortiih_vv(short32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdsortiiuh_vv                                                        */
/*----------------------------------------------------------------------------*/

/* VDSORTIIUH */
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vdsortiiuh_vv(ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdsortpddh_vv                                                        */
/*----------------------------------------------------------------------------*/

/* VDSORTPDDH */
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vdsortpddh_vv(short32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdsortpdduh_vv                                                       */
/*----------------------------------------------------------------------------*/

/* VDSORTPDDUH */
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vdsortpdduh_vv(ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdsortpdih_vv                                                        */
/*----------------------------------------------------------------------------*/

/* VDSORTPDIH */
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vdsortpdih_vv(short32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdsortpdiuh_vv                                                       */
/*----------------------------------------------------------------------------*/

/* VDSORTPDIUH */
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vdsortpdiuh_vv(ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdsortpidh_vv                                                        */
/*----------------------------------------------------------------------------*/

/* VDSORTPIDH */
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vdsortpidh_vv(short32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdsortpiduh_vv                                                       */
/*----------------------------------------------------------------------------*/

/* VDSORTPIDUH */
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vdsortpiduh_vv(ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdsortpiih_vv                                                        */
/*----------------------------------------------------------------------------*/

/* VDSORTPIIH */
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vdsortpiih_vv(short32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdsortpiiuh_vv                                                       */
/*----------------------------------------------------------------------------*/

/* VDSORTPIIUH */
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vdsortpiiuh_vv(ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdup16b_vv                                                           */
/*----------------------------------------------------------------------------*/

/* VDUP16B */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __vdup16b_vv(char2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __vdup16b_vv(char4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vdup16b_vv(uchar2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vdup16b_vv(uchar4);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdup16h_vv                                                           */
/*----------------------------------------------------------------------------*/

/* VDUP16H */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cchar16 __vdup16h_vv(cchar);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cchar32 __vdup16h_vv(cchar2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vdup16h_vv(int16_t);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vdup16h_vv(short2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vdup16h_vv(uint16_t);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vdup16h_vv(ushort2);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdup2b_vv                                                            */
/*----------------------------------------------------------------------------*/

/* VDUP2B */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __vdup2b_vv(char16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __vdup2b_vv(char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vdup2b_vv(uchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vdup2b_vv(uchar32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdup2d_vv                                                            */
/*----------------------------------------------------------------------------*/

/* VDUP2D */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cint4 __vdup2d_vv(cint2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cint8 __vdup2d_vv(cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cfloat4 __vdup2d_vv(cfloat2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cfloat8 __vdup2d_vv(cfloat4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __vdup2d_vv(long2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __vdup2d_vv(long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __vdup2d_vv(ulong2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __vdup2d_vv(ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern double4 __vdup2d_vv(double2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern double8 __vdup2d_vv(double4);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdup2h_vv                                                            */
/*----------------------------------------------------------------------------*/

/* VDUP2H */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cchar16 __vdup2h_vv(cchar8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cchar32 __vdup2h_vv(cchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vdup2h_vv(short8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vdup2h_vv(short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vdup2h_vv(ushort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vdup2h_vv(ushort16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdup2w_vv                                                            */
/*----------------------------------------------------------------------------*/

/* VDUP2W */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cshort8 __vdup2w_vv(cshort4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cshort16 __vdup2w_vv(cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vdup2w_vv(int4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vdup2w_vv(int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vdup2w_vv(uint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vdup2w_vv(uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern float8 __vdup2w_vv(float4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern float16 __vdup2w_vv(float8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdup32b_vv                                                           */
/*----------------------------------------------------------------------------*/

/* VDUP32B */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __vdup32b_vv(int8_t);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __vdup32b_vv(char2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vdup32b_vv(uint8_t);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vdup32b_vv(uchar2);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdup4b_vv                                                            */
/*----------------------------------------------------------------------------*/

/* VDUP4B */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __vdup4b_vv(char8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __vdup4b_vv(char16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vdup4b_vv(uchar8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vdup4b_vv(uchar16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdup4d_vv                                                            */
/*----------------------------------------------------------------------------*/

/* VDUP4D */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cint4 __vdup4d_vv(cint);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cint8 __vdup4d_vv(cint2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cfloat4 __vdup4d_vv(cfloat);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cfloat8 __vdup4d_vv(cfloat2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __vdup4d_vv(int64_t);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __vdup4d_vv(long2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __vdup4d_vv(uint64_t);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __vdup4d_vv(ulong2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern double4 __vdup4d_vv(double);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern double8 __vdup4d_vv(double2);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdup4h_vv                                                            */
/*----------------------------------------------------------------------------*/

/* VDUP4H */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cchar16 __vdup4h_vv(cchar4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cchar32 __vdup4h_vv(cchar8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vdup4h_vv(short4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vdup4h_vv(short8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vdup4h_vv(ushort4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vdup4h_vv(ushort8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdup4w_vv                                                            */
/*----------------------------------------------------------------------------*/

/* VDUP4W */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cshort8 __vdup4w_vv(cshort2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cshort16 __vdup4w_vv(cshort4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vdup4w_vv(int2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vdup4w_vv(int4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vdup4w_vv(uint2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vdup4w_vv(uint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern float8 __vdup4w_vv(float2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern float16 __vdup4w_vv(float4);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdup8b_vv                                                            */
/*----------------------------------------------------------------------------*/

/* VDUP8B */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __vdup8b_vv(char4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __vdup8b_vv(char8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vdup8b_vv(uchar4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vdup8b_vv(uchar8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdup8h_vv                                                            */
/*----------------------------------------------------------------------------*/

/* VDUP8H */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cchar16 __vdup8h_vv(cchar2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cchar32 __vdup8h_vv(cchar4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vdup8h_vv(short2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vdup8h_vv(short4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vdup8h_vv(ushort2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vdup8h_vv(ushort4);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdup8w_vv                                                            */
/*----------------------------------------------------------------------------*/

/* VDUP8W */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cshort8 __vdup8w_vv(cshort);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cshort16 __vdup8w_vv(cshort2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vdup8w_vv(int32_t);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vdup8w_vv(int2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vdup8w_vv(uint32_t);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vdup8w_vv(uint2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern float8 __vdup8w_vv(float);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern float16 __vdup8w_vv(float2);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdupb_kv                                                             */
/*----------------------------------------------------------------------------*/

/* VDUPB */
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __vdupb_kv(int8_t/*(k)*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __vdupb_kv(int8_t/*(k)*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vdupb_kv(uint8_t/*(k)*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vdupb_kv(uint8_t/*(k)*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdupb_rv                                                             */
/*----------------------------------------------------------------------------*/

/* VDUPB */
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __vdupb_rv(int8_t);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __vdupb_rv(int8_t);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vdupb_rv(uint8_t);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vdupb_rv(uint8_t);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdupd_dv                                                             */
/*----------------------------------------------------------------------------*/

/* VDUPD */
#if __C7X_VEC_SIZE_BITS__ == 512
extern cint8 __vdupd_dv(cint);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cint4 __vdupd_dv(cint);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cfloat8 __vdupd_dv(cfloat);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cfloat4 __vdupd_dv(cfloat);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __vdupd_dv(int64_t);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __vdupd_dv(int64_t);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __vdupd_dv(uint64_t);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __vdupd_dv(uint64_t);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern double8 __vdupd_dv(double);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern double4 __vdupd_dv(double);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vduph_kv                                                             */
/*----------------------------------------------------------------------------*/

/* VDUPH */
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vduph_kv(int16_t/*(k)*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vduph_kv(int16_t/*(k)*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vduph_kv(uint16_t/*(k)*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vduph_kv(uint16_t/*(k)*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vduph_rv                                                             */
/*----------------------------------------------------------------------------*/

/* VDUPH */
#if __C7X_VEC_SIZE_BITS__ == 512
extern cchar32 __vduph_rv(cchar);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cchar16 __vduph_rv(cchar);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vduph_rv(int16_t);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vduph_rv(int16_t);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vduph_rv(uint16_t);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vduph_rv(uint16_t);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdupw_kv                                                             */
/*----------------------------------------------------------------------------*/

/* VDUPW */
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vdupw_kv(int32_t/*(k)*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vdupw_kv(int32_t/*(k)*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vdupw_kv(uint32_t/*(k)*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vdupw_kv(uint32_t/*(k)*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern float16 __vdupw_kv(float/*(k)*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern float8 __vdupw_kv(float/*(k)*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vdupw_rv                                                             */
/*----------------------------------------------------------------------------*/

/* VDUPW */
#if __C7X_VEC_SIZE_BITS__ == 512
extern cshort16 __vdupw_rv(cshort);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cshort8 __vdupw_rv(cshort);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vdupw_rv(int32_t);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vdupw_rv(int32_t);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vdupw_rv(uint32_t);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vdupw_rv(uint32_t);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern float16 __vdupw_rv(float);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern float8 __vdupw_rv(float);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vgatherb_pvv                                                         */
/*----------------------------------------------------------------------------*/

/* VGATHERB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __vgatherb_pvv(__vpred, char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __vgatherb_pvv(__vpred, char64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vgathernb_pvv                                                        */
/*----------------------------------------------------------------------------*/

/* VGATHERNB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __vgathernb_pvv(__vpred, char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __vgathernb_pvv(__vpred, char64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vgetb_vkd                                                            */
/*----------------------------------------------------------------------------*/

/* VGETB */
#if __C7X_VEC_SIZE_BITS__ == 512
extern int8_t __vgetb_vkd(char64, uint32_t/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8_t __vgetb_vkd(char32, uint32_t/*(k={0-63})*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vgetb_vrd                                                            */
/*----------------------------------------------------------------------------*/

/* VGETB */
#if __C7X_VEC_SIZE_BITS__ == 512
extern int8_t __vgetb_vrd(char64, uint32_t);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8_t __vgetb_vrd(char32, uint32_t);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vgetb_ykd                                                            */
/*----------------------------------------------------------------------------*/

/* VGETB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8_t __vgetb_ykd(char32, uint32_t/*(k={0-63})*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vgetd_vkd                                                            */
/*----------------------------------------------------------------------------*/

/* VGETD */
#if __C7X_VEC_SIZE_BITS__ == 512
extern cint __vgetd_vkd(cint8, uint32_t/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cint __vgetd_vkd(cint4, uint32_t/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cfloat __vgetd_vkd(cfloat8, uint32_t/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cfloat __vgetd_vkd(cfloat4, uint32_t/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int64_t __vgetd_vkd(long8, uint32_t/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern int64_t __vgetd_vkd(long4, uint32_t/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint64_t __vgetd_vkd(ulong8, uint32_t/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint64_t __vgetd_vkd(ulong4, uint32_t/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern double __vgetd_vkd(double8, uint32_t/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern double __vgetd_vkd(double4, uint32_t/*(k={0-63})*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vgetd_vrd                                                            */
/*----------------------------------------------------------------------------*/

/* VGETD */
#if __C7X_VEC_SIZE_BITS__ == 512
extern cint __vgetd_vrd(cint8, uint32_t);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cint __vgetd_vrd(cint4, uint32_t);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cfloat __vgetd_vrd(cfloat8, uint32_t);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cfloat __vgetd_vrd(cfloat4, uint32_t);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int64_t __vgetd_vrd(long8, uint32_t);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern int64_t __vgetd_vrd(long4, uint32_t);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint64_t __vgetd_vrd(ulong8, uint32_t);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint64_t __vgetd_vrd(ulong4, uint32_t);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern double __vgetd_vrd(double8, uint32_t);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern double __vgetd_vrd(double4, uint32_t);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vgetd_ykd                                                            */
/*----------------------------------------------------------------------------*/

/* VGETD */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cint __vgetd_ykd(cint4, uint32_t/*(k={0-63})*/);
extern cfloat __vgetd_ykd(cfloat4, uint32_t/*(k={0-63})*/);
extern int64_t __vgetd_ykd(long4, uint32_t/*(k={0-63})*/);
extern uint64_t __vgetd_ykd(ulong4, uint32_t/*(k={0-63})*/);
extern double __vgetd_ykd(double4, uint32_t/*(k={0-63})*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vgetdupb_vrv                                                         */
/*----------------------------------------------------------------------------*/

/* VGETDUPB */
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __vgetdupb_vrv(char64, int32_t);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __vgetdupb_vrv(char32, int32_t);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vgetdupb_vrv(uchar64, uint32_t);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vgetdupb_vrv(uchar32, uint32_t);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vgetdupd_vrv                                                         */
/*----------------------------------------------------------------------------*/

/* VGETDUPD */
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __vgetdupd_vrv(long8, int32_t);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __vgetdupd_vrv(long4, int32_t);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __vgetdupd_vrv(ulong8, uint32_t);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __vgetdupd_vrv(ulong4, uint32_t);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vgetduph_vrv                                                         */
/*----------------------------------------------------------------------------*/

/* VGETDUPH */
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vgetduph_vrv(short32, int32_t);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vgetduph_vrv(short16, int32_t);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vgetduph_vrv(ushort32, uint32_t);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vgetduph_vrv(ushort16, uint32_t);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vgetdupw_vrv                                                         */
/*----------------------------------------------------------------------------*/

/* VGETDUPW */
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vgetdupw_vrv(int16, int32_t);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vgetdupw_vrv(int8, int32_t);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vgetdupw_vrv(uint16, uint32_t);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vgetdupw_vrv(uint8, uint32_t);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vgeth_vkd                                                            */
/*----------------------------------------------------------------------------*/

/* VGETH */
#if __C7X_VEC_SIZE_BITS__ == 512
extern cchar __vgeth_vkd(cchar32, uint32_t/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cchar __vgeth_vkd(cchar16, uint32_t/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16_t __vgeth_vkd(short32, uint32_t/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern int16_t __vgeth_vkd(short16, uint32_t/*(k={0-63})*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vgeth_vrd                                                            */
/*----------------------------------------------------------------------------*/

/* VGETH */
#if __C7X_VEC_SIZE_BITS__ == 512
extern cchar __vgeth_vrd(cchar32, uint32_t);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cchar __vgeth_vrd(cchar16, uint32_t);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16_t __vgeth_vrd(short32, uint32_t);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern int16_t __vgeth_vrd(short16, uint32_t);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vgeth_ykd                                                            */
/*----------------------------------------------------------------------------*/

/* VGETH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cchar __vgeth_ykd(cchar16, uint32_t/*(k={0-63})*/);
extern int16_t __vgeth_ykd(short16, uint32_t/*(k={0-63})*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vgetub_vkd                                                           */
/*----------------------------------------------------------------------------*/

/* VGETUB */
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint8_t __vgetub_vkd(uchar64, uint32_t/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8_t __vgetub_vkd(uchar32, uint32_t/*(k={0-63})*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vgetub_vrd                                                           */
/*----------------------------------------------------------------------------*/

/* VGETUB */
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint8_t __vgetub_vrd(uchar64, uint32_t);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8_t __vgetub_vrd(uchar32, uint32_t);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vgetub_ykd                                                           */
/*----------------------------------------------------------------------------*/

/* VGETUB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8_t __vgetub_ykd(uchar32, uint32_t/*(k={0-63})*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vgetuh_vkd                                                           */
/*----------------------------------------------------------------------------*/

/* VGETUH */
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16_t __vgetuh_vkd(ushort32, uint32_t/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint16_t __vgetuh_vkd(ushort16, uint32_t/*(k={0-63})*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vgetuh_vrd                                                           */
/*----------------------------------------------------------------------------*/

/* VGETUH */
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16_t __vgetuh_vrd(ushort32, uint32_t);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint16_t __vgetuh_vrd(ushort16, uint32_t);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vgetuh_ykd                                                           */
/*----------------------------------------------------------------------------*/

/* VGETUH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint16_t __vgetuh_ykd(ushort16, uint32_t/*(k={0-63})*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vgetuw_vkd                                                           */
/*----------------------------------------------------------------------------*/

/* VGETUW */
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint32_t __vgetuw_vkd(uint16, uint32_t/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint32_t __vgetuw_vkd(uint8, uint32_t/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern float __vgetuw_vkd(float16, uint32_t/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern float __vgetuw_vkd(float8, uint32_t/*(k={0-63})*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vgetuw_vrd                                                           */
/*----------------------------------------------------------------------------*/

/* VGETUW */
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint32_t __vgetuw_vrd(uint16, uint32_t);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint32_t __vgetuw_vrd(uint8, uint32_t);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern float __vgetuw_vrd(float16, uint32_t);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern float __vgetuw_vrd(float8, uint32_t);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vgetuw_ykd                                                           */
/*----------------------------------------------------------------------------*/

/* VGETUW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint32_t __vgetuw_ykd(uint8, uint32_t/*(k={0-63})*/);
extern float __vgetuw_ykd(float8, uint32_t/*(k={0-63})*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vgetw_vkd                                                            */
/*----------------------------------------------------------------------------*/

/* VGETW */
#if __C7X_VEC_SIZE_BITS__ == 512
extern cshort __vgetw_vkd(cshort16, uint32_t/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cshort __vgetw_vkd(cshort8, uint32_t/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int32_t __vgetw_vkd(int16, uint32_t/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern int32_t __vgetw_vkd(int8, uint32_t/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern float __vgetw_vkd(float16, uint32_t/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern float __vgetw_vkd(float8, uint32_t/*(k={0-63})*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vgetw_vrd                                                            */
/*----------------------------------------------------------------------------*/

/* VGETW */
#if __C7X_VEC_SIZE_BITS__ == 512
extern cshort __vgetw_vrd(cshort16, uint32_t);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cshort __vgetw_vrd(cshort8, uint32_t);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int32_t __vgetw_vrd(int16, uint32_t);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern int32_t __vgetw_vrd(int8, uint32_t);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern float __vgetw_vrd(float16, uint32_t);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern float __vgetw_vrd(float8, uint32_t);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vgetw_ykd                                                            */
/*----------------------------------------------------------------------------*/

/* VGETW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cshort __vgetw_ykd(cshort8, uint32_t/*(k={0-63})*/);
extern int32_t __vgetw_ykd(int8, uint32_t/*(k={0-63})*/);
extern float __vgetw_ykd(float8, uint32_t/*(k={0-63})*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vgmpyb_vvv                                                           */
/*----------------------------------------------------------------------------*/

/* VGMPYB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vgmpyb_vvv(uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vgmpyb_vvv(uchar64, uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vgmpyw_vvv                                                           */
/*----------------------------------------------------------------------------*/

/* VGMPYW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vgmpyw_vvv(uint8, uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vgmpyw_vvv(uint16, uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vgsatd_vkv                                                           */
/*----------------------------------------------------------------------------*/

/* VGSATD */
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __vgsatd_vkv(long4, uchar4/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __vgsatd_vkv(long8, uchar8/*(k={0-63})*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vgsath_vkv                                                           */
/*----------------------------------------------------------------------------*/

/* VGSATH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vgsath_vkv(short16, uchar16/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vgsath_vkv(short32, uchar32/*(k={0-63})*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vgsatsud_vkv                                                         */
/*----------------------------------------------------------------------------*/

/* VGSATSUD */
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __vgsatsud_vkv(long4, uchar4/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __vgsatsud_vkv(long8, uchar8/*(k={0-63})*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vgsatsuh_vkv                                                         */
/*----------------------------------------------------------------------------*/

/* VGSATSUH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vgsatsuh_vkv(short16, uchar16/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vgsatsuh_vkv(short32, uchar32/*(k={0-63})*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vgsatsuw_vkv                                                         */
/*----------------------------------------------------------------------------*/

/* VGSATSUW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vgsatsuw_vkv(int8, uchar8/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vgsatsuw_vkv(int16, uchar16/*(k={0-63})*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vgsatud_vkv                                                          */
/*----------------------------------------------------------------------------*/

/* VGSATUD */
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __vgsatud_vkv(ulong4, uchar4/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __vgsatud_vkv(ulong8, uchar8/*(k={0-63})*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vgsatuh_vkv                                                          */
/*----------------------------------------------------------------------------*/

/* VGSATUH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vgsatuh_vkv(ushort16, uchar16/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vgsatuh_vkv(ushort32, uchar32/*(k={0-63})*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vgsatuw_vkv                                                          */
/*----------------------------------------------------------------------------*/

/* VGSATUW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vgsatuw_vkv(uint8, uchar8/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vgsatuw_vkv(uint16, uchar16/*(k={0-63})*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vgsatw_vkv                                                           */
/*----------------------------------------------------------------------------*/

/* VGSATW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vgsatw_vkv(int8, uchar8/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vgsatw_vkv(int16, uchar16/*(k={0-63})*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vhaddb1d_vd                                                          */
/*----------------------------------------------------------------------------*/

/* VHADDB1D */
#if __C7X_VEC_SIZE_BITS__ == 512
extern int64_t __vhaddb1d_vd(char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern int64_t __vhaddb1d_vd(char32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vhaddd1d_vd                                                          */
/*----------------------------------------------------------------------------*/

/* VHADDD1D */
#if __C7X_VEC_SIZE_BITS__ == 512
extern int64_t __vhaddd1d_vd(long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern int64_t __vhaddd1d_vd(long4);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vhaddeoh2w_vd                                                        */
/*----------------------------------------------------------------------------*/

/* VHADDEOH2W */
#if __C7X_VEC_SIZE_BITS__ == 512
extern int2 __vhaddeoh2w_vd(short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern int2 __vhaddeoh2w_vd(short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cint __vhaddeoh2w_vd(cshort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cint __vhaddeoh2w_vd(cshort8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vhaddeow2d_vv                                                        */
/*----------------------------------------------------------------------------*/

/* VHADDEOW2D */
#if __C7X_VEC_SIZE_BITS__ == 512
extern long2 __vhaddeow2d_vv(int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern long2 __vhaddeow2d_vv(int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern clong __vhaddeow2d_vv(cint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern clong __vhaddeow2d_vv(cint4);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vhaddeow4d_vvv                                                       */
/*----------------------------------------------------------------------------*/

/* VHADDEOW4D */
#if __C7X_VEC_SIZE_BITS__ == 512
extern long4 __vhaddeow4d_vvv(int16, int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __vhaddeow4d_vvv(int8, int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern clong2 __vhaddeow4d_vvv(cint8, cint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern clong2 __vhaddeow4d_vvv(cint4, cint4);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vhaddh1d_vd                                                          */
/*----------------------------------------------------------------------------*/

/* VHADDH1D */
#if __C7X_VEC_SIZE_BITS__ == 512
extern int64_t __vhaddh1d_vd(short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern int64_t __vhaddh1d_vd(short16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vhaddub1d_vd                                                         */
/*----------------------------------------------------------------------------*/

/* VHADDUB1D */
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint64_t __vhaddub1d_vd(uchar64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint64_t __vhaddub1d_vd(uchar32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vhaddud1d_vd                                                         */
/*----------------------------------------------------------------------------*/

/* VHADDUD1D */
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint64_t __vhaddud1d_vd(ulong8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint64_t __vhaddud1d_vd(ulong4);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vhaddueoh2w_vd                                                       */
/*----------------------------------------------------------------------------*/

/* VHADDUEOH2W */
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint2 __vhaddueoh2w_vd(ushort32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint2 __vhaddueoh2w_vd(ushort16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vhaddueow2d_vv                                                       */
/*----------------------------------------------------------------------------*/

/* VHADDUEOW2D */
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong2 __vhaddueow2d_vv(uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong2 __vhaddueow2d_vv(uint8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vhaddueow4d_vvv                                                      */
/*----------------------------------------------------------------------------*/

/* VHADDUEOW4D */
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong4 __vhaddueow4d_vvv(uint16, uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __vhaddueow4d_vvv(uint8, uint8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vhadduh1d_vd                                                         */
/*----------------------------------------------------------------------------*/

/* VHADDUH1D */
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint64_t __vhadduh1d_vd(ushort32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint64_t __vhadduh1d_vd(ushort16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vhadduw1d_vd                                                         */
/*----------------------------------------------------------------------------*/

/* VHADDUW1D */
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint64_t __vhadduw1d_vd(uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint64_t __vhadduw1d_vd(uint8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vhaddw1d_vd                                                          */
/*----------------------------------------------------------------------------*/

/* VHADDW1D */
#if __C7X_VEC_SIZE_BITS__ == 512
extern int64_t __vhaddw1d_vd(int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern int64_t __vhaddw1d_vd(int8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vhhmv_vvv                                                            */
/*----------------------------------------------------------------------------*/

/* VHHMV */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vhhmv_vvv(uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vhhmv_vvv(uchar64, uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vhlmv_vvv                                                            */
/*----------------------------------------------------------------------------*/

/* VHLMV */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vhlmv_vvv(uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vhlmv_vvv(uchar64, uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vhpackh_vvv                                                          */
/*----------------------------------------------------------------------------*/

/* VHPACKH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cchar16 __vhpackh_vvv(cchar16, cchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cchar32 __vhpackh_vvv(cchar32, cchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vhpackh_vvv(short16, short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vhpackh_vvv(short32, short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vhpackh_vvv(ushort16, ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vhpackh_vvv(ushort32, ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vhpackl_vvv                                                          */
/*----------------------------------------------------------------------------*/

/* VHPACKL */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cchar16 __vhpackl_vvv(cchar16, cchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cchar32 __vhpackl_vvv(cchar32, cchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vhpackl_vvv(short16, short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vhpackl_vvv(short32, short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vhpackl_vvv(ushort16, ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vhpackl_vvv(ushort32, ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vhpint_vv                                                            */
/*----------------------------------------------------------------------------*/

/* VHPINT */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vhpint_vv(uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vhpint_vv(uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vhpsp_vv                                                             */
/*----------------------------------------------------------------------------*/

/* VHPSP */
#if __C7X_VEC_SIZE_BITS__ == 256
extern float8 __vhpsp_vv(uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern float16 __vhpsp_vv(uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vhunpkd_vv                                                           */
/*----------------------------------------------------------------------------*/

/* VHUNPKD */
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __vhunpkd_vv(short4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __vhunpkd_vv(short8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern clong2 __vhunpkd_vv(cshort2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern clong4 __vhunpkd_vv(cshort4);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vhunpkdu_vv                                                          */
/*----------------------------------------------------------------------------*/

/* VHUNPKDU */
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __vhunpkdu_vv(ushort4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __vhunpkdu_vv(ushort8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vhunpkuwh_vv                                                         */
/*----------------------------------------------------------------------------*/

/* VHUNPKUWH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vhunpkuwh_vv(ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vhunpkuwh_vv(ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vhunpkuwl_vv                                                         */
/*----------------------------------------------------------------------------*/

/* VHUNPKUWL */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vhunpkuwl_vv(ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vhunpkuwl_vv(ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vhunpkw_vv                                                           */
/*----------------------------------------------------------------------------*/

/* VHUNPKW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vhunpkw_vv(short8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vhunpkw_vv(short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cint4 __vhunpkw_vv(cshort4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cint8 __vhunpkw_vv(cshort8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vhunpkwh_vv                                                          */
/*----------------------------------------------------------------------------*/

/* VHUNPKWH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vhunpkwh_vv(short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vhunpkwh_vv(short32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vhunpkwl_vv                                                          */
/*----------------------------------------------------------------------------*/

/* VHUNPKWL */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vhunpkwl_vv(short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vhunpkwl_vv(short32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vhunpkwu_vv                                                          */
/*----------------------------------------------------------------------------*/

/* VHUNPKWU */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vhunpkwu_vv(ushort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vhunpkwu_vv(ushort16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vhxorb1b_vr                                                          */
/*----------------------------------------------------------------------------*/

/* VHXORB1B */
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16_t __vhxorb1b_vr(char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern int16_t __vhxorb1b_vr(char32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vhxord1d_vd                                                          */
/*----------------------------------------------------------------------------*/

/* VHXORD1D */
#if __C7X_VEC_SIZE_BITS__ == 512
extern int64_t __vhxord1d_vd(long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern int64_t __vhxord1d_vd(long4);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vhxorh1h_vr                                                          */
/*----------------------------------------------------------------------------*/

/* VHXORH1H */
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16_t __vhxorh1h_vr(short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern int16_t __vhxorh1h_vr(short16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vhxorw1w_vr                                                          */
/*----------------------------------------------------------------------------*/

/* VHXORW1W */
#if __C7X_VEC_SIZE_BITS__ == 512
extern int32_t __vhxorw1w_vr(int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern int32_t __vhxorw1w_vr(int8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vintdph_vv                                                           */
/*----------------------------------------------------------------------------*/

/* VINTDPH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern double4 __vintdph_vv(int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern double8 __vintdph_vv(int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vintdpl_vv                                                           */
/*----------------------------------------------------------------------------*/

/* VINTDPL */
#if __C7X_VEC_SIZE_BITS__ == 256
extern double4 __vintdpl_vv(int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern double8 __vintdpl_vv(int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vintdpuh_vv                                                          */
/*----------------------------------------------------------------------------*/

/* VINTDPUH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern double4 __vintdpuh_vv(uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern double8 __vintdpuh_vv(uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vintdpul_vv                                                          */
/*----------------------------------------------------------------------------*/

/* VINTDPUL */
#if __C7X_VEC_SIZE_BITS__ == 256
extern double4 __vintdpul_vv(uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern double8 __vintdpul_vv(uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vinthp_vv                                                            */
/*----------------------------------------------------------------------------*/

/* VINTHP */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vinthp_vv(int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vinthp_vv(int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vinthsph_vv                                                          */
/*----------------------------------------------------------------------------*/

/* VINTHSPH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern float8 __vinthsph_vv(short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern float16 __vinthsph_vv(short32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vinthspl_vv                                                          */
/*----------------------------------------------------------------------------*/

/* VINTHSPL */
#if __C7X_VEC_SIZE_BITS__ == 256
extern float8 __vinthspl_vv(short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern float16 __vinthspl_vv(short32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vinthspuh_vv                                                         */
/*----------------------------------------------------------------------------*/

/* VINTHSPUH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern float8 __vinthspuh_vv(ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern float16 __vinthspuh_vv(ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vinthspul_vv                                                         */
/*----------------------------------------------------------------------------*/

/* VINTHSPUL */
#if __C7X_VEC_SIZE_BITS__ == 256
extern float8 __vinthspul_vv(ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern float16 __vinthspul_vv(ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vintsp_vv                                                            */
/*----------------------------------------------------------------------------*/

/* VINTSP */
#if __C7X_VEC_SIZE_BITS__ == 256
extern float8 __vintsp_vv(int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern float16 __vintsp_vv(int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vintspu_vv                                                           */
/*----------------------------------------------------------------------------*/

/* VINTSPU */
#if __C7X_VEC_SIZE_BITS__ == 256
extern float8 __vintspu_vv(uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern float16 __vintspu_vv(uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vlhmv_vvv                                                            */
/*----------------------------------------------------------------------------*/

/* VLHMV */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vlhmv_vvv(uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vlhmv_vvv(uchar64, uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vllmv_vvv                                                            */
/*----------------------------------------------------------------------------*/

/* VLLMV */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vllmv_vvv(uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vllmv_vvv(uchar64, uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vlmbd0b_vv                                                           */
/*----------------------------------------------------------------------------*/

/* VLMBD0B */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vlmbd0b_vv(uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vlmbd0b_vv(uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vlmbd0d_vv                                                           */
/*----------------------------------------------------------------------------*/

/* VLMBD0D */
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __vlmbd0d_vv(ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __vlmbd0d_vv(ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vlmbd0h_vv                                                           */
/*----------------------------------------------------------------------------*/

/* VLMBD0H */
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vlmbd0h_vv(ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vlmbd0h_vv(ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vlmbd0w_vv                                                           */
/*----------------------------------------------------------------------------*/

/* VLMBD0W */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vlmbd0w_vv(uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vlmbd0w_vv(uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vlmbd1b_vv                                                           */
/*----------------------------------------------------------------------------*/

/* VLMBD1B */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vlmbd1b_vv(uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vlmbd1b_vv(uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vlmbd1d_vv                                                           */
/*----------------------------------------------------------------------------*/

/* VLMBD1D */
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __vlmbd1d_vv(ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __vlmbd1d_vv(ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vlmbd1h_vv                                                           */
/*----------------------------------------------------------------------------*/

/* VLMBD1H */
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vlmbd1h_vv(ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vlmbd1h_vv(ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vlmbd1w_vv                                                           */
/*----------------------------------------------------------------------------*/

/* VLMBD1W */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vlmbd1w_vv(uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vlmbd1w_vv(uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vlmbdb_vvv                                                           */
/*----------------------------------------------------------------------------*/

/* VLMBDB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vlmbdb_vvv(uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vlmbdb_vvv(uchar64, uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vlmbdd_vvv                                                           */
/*----------------------------------------------------------------------------*/

/* VLMBDD */
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __vlmbdd_vvv(ulong4, ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __vlmbdd_vvv(ulong8, ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vlmbdh_vvv                                                           */
/*----------------------------------------------------------------------------*/

/* VLMBDH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vlmbdh_vvv(ushort16, ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vlmbdh_vvv(ushort32, ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vlmbdw_vvv                                                           */
/*----------------------------------------------------------------------------*/

/* VLMBDW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vlmbdw_vvv(uint8, uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vlmbdw_vvv(uint16, uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vmatmpysp_vww                                                        */
/*----------------------------------------------------------------------------*/

/* VMATMPYSP */
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __vmatmpysp_vww(float16, float16, float16, float16&, float16&);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vmaxb_vvv                                                            */
/*----------------------------------------------------------------------------*/

/* VMAXB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __vmaxb_vvv(char32, char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __vmaxb_vvv(char64, char64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vmaxd_vvv                                                            */
/*----------------------------------------------------------------------------*/

/* VMAXD */
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __vmaxd_vvv(long4, long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __vmaxd_vvv(long8, long8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vmaxdp_vvv                                                           */
/*----------------------------------------------------------------------------*/

/* VMAXDP */
#if __C7X_VEC_SIZE_BITS__ == 256
extern double4 __vmaxdp_vvv(double4, double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern double8 __vmaxdp_vvv(double8, double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vmaxh_vvv                                                            */
/*----------------------------------------------------------------------------*/

/* VMAXH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vmaxh_vvv(short16, short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vmaxh_vvv(short32, short32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vmaxpb_vvp                                                           */
/*----------------------------------------------------------------------------*/

/* VMAXPB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern void __vmaxpb_vvp(char32, char32&, __vpred&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __vmaxpb_vvp(char64, char64&, __vpred&);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vmaxpd_vvp                                                           */
/*----------------------------------------------------------------------------*/

/* VMAXPD */
#if __C7X_VEC_SIZE_BITS__ == 256
extern void __vmaxpd_vvp(long4, long4&, __vpred&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __vmaxpd_vvp(long8, long8&, __vpred&);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vmaxph_vvp                                                           */
/*----------------------------------------------------------------------------*/

/* VMAXPH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern void __vmaxph_vvp(short16, short16&, __vpred&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __vmaxph_vvp(short32, short32&, __vpred&);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vmaxpw_vvp                                                           */
/*----------------------------------------------------------------------------*/

/* VMAXPW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern void __vmaxpw_vvp(int8, int8&, __vpred&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __vmaxpw_vvp(int16, int16&, __vpred&);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vmaxsp_vvv                                                           */
/*----------------------------------------------------------------------------*/

/* VMAXSP */
#if __C7X_VEC_SIZE_BITS__ == 256
extern float8 __vmaxsp_vvv(float8, float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern float16 __vmaxsp_vvv(float16, float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vmaxub_vvv                                                           */
/*----------------------------------------------------------------------------*/

/* VMAXUB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vmaxub_vvv(uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vmaxub_vvv(uchar64, uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vmaxud_vvv                                                           */
/*----------------------------------------------------------------------------*/

/* VMAXUD */
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __vmaxud_vvv(ulong4, ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __vmaxud_vvv(ulong8, ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vmaxuh_vvv                                                           */
/*----------------------------------------------------------------------------*/

/* VMAXUH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vmaxuh_vvv(ushort16, ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vmaxuh_vvv(ushort32, ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vmaxupb_vvp                                                          */
/*----------------------------------------------------------------------------*/

/* VMAXUPB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern void __vmaxupb_vvp(uchar32, uchar32&, __vpred&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __vmaxupb_vvp(uchar64, uchar64&, __vpred&);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vmaxupd_vvp                                                          */
/*----------------------------------------------------------------------------*/

/* VMAXUPD */
#if __C7X_VEC_SIZE_BITS__ == 256
extern void __vmaxupd_vvp(ulong4, ulong4&, __vpred&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __vmaxupd_vvp(ulong8, ulong8&, __vpred&);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vmaxuph_vvp                                                          */
/*----------------------------------------------------------------------------*/

/* VMAXUPH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern void __vmaxuph_vvp(ushort16, ushort16&, __vpred&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __vmaxuph_vvp(ushort32, ushort32&, __vpred&);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vmaxupw_vvp                                                          */
/*----------------------------------------------------------------------------*/

/* VMAXUPW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern void __vmaxupw_vvp(uint8, uint8&, __vpred&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __vmaxupw_vvp(uint16, uint16&, __vpred&);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vmaxuw_vvv                                                           */
/*----------------------------------------------------------------------------*/

/* VMAXUW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vmaxuw_vvv(uint8, uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vmaxuw_vvv(uint16, uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vmaxw_vvv                                                            */
/*----------------------------------------------------------------------------*/

/* VMAXW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vmaxw_vvv(int8, int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vmaxw_vvv(int16, int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vminb_vvv                                                            */
/*----------------------------------------------------------------------------*/

/* VMINB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __vminb_vvv(char32, char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __vminb_vvv(char64, char64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vmind_vvv                                                            */
/*----------------------------------------------------------------------------*/

/* VMIND */
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __vmind_vvv(long4, long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __vmind_vvv(long8, long8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vmindp_vvv                                                           */
/*----------------------------------------------------------------------------*/

/* VMINDP */
#if __C7X_VEC_SIZE_BITS__ == 256
extern double4 __vmindp_vvv(double4, double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern double8 __vmindp_vvv(double8, double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vminh_vvv                                                            */
/*----------------------------------------------------------------------------*/

/* VMINH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vminh_vvv(short16, short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vminh_vvv(short32, short32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vminpb_vvp                                                           */
/*----------------------------------------------------------------------------*/

/* VMINPB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern void __vminpb_vvp(char32, char32&, __vpred&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __vminpb_vvp(char64, char64&, __vpred&);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vminpd_vvp                                                           */
/*----------------------------------------------------------------------------*/

/* VMINPD */
#if __C7X_VEC_SIZE_BITS__ == 256
extern void __vminpd_vvp(long4, long4&, __vpred&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __vminpd_vvp(long8, long8&, __vpred&);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vminph_vvp                                                           */
/*----------------------------------------------------------------------------*/

/* VMINPH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern void __vminph_vvp(short16, short16&, __vpred&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __vminph_vvp(short32, short32&, __vpred&);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vminpw_vvp                                                           */
/*----------------------------------------------------------------------------*/

/* VMINPW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern void __vminpw_vvp(int8, int8&, __vpred&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __vminpw_vvp(int16, int16&, __vpred&);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vminsp_vvv                                                           */
/*----------------------------------------------------------------------------*/

/* VMINSP */
#if __C7X_VEC_SIZE_BITS__ == 256
extern float8 __vminsp_vvv(float8, float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern float16 __vminsp_vvv(float16, float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vminub_vvv                                                           */
/*----------------------------------------------------------------------------*/

/* VMINUB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vminub_vvv(uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vminub_vvv(uchar64, uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vminud_vvv                                                           */
/*----------------------------------------------------------------------------*/

/* VMINUD */
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __vminud_vvv(ulong4, ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __vminud_vvv(ulong8, ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vminuh_vvv                                                           */
/*----------------------------------------------------------------------------*/

/* VMINUH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vminuh_vvv(ushort16, ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vminuh_vvv(ushort32, ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vminupb_vvp                                                          */
/*----------------------------------------------------------------------------*/

/* VMINUPB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern void __vminupb_vvp(uchar32, uchar32&, __vpred&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __vminupb_vvp(uchar64, uchar64&, __vpred&);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vminupd_vvp                                                          */
/*----------------------------------------------------------------------------*/

/* VMINUPD */
#if __C7X_VEC_SIZE_BITS__ == 256
extern void __vminupd_vvp(ulong4, ulong4&, __vpred&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __vminupd_vvp(ulong8, ulong8&, __vpred&);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vminuph_vvp                                                          */
/*----------------------------------------------------------------------------*/

/* VMINUPH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern void __vminuph_vvp(ushort16, ushort16&, __vpred&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __vminuph_vvp(ushort32, ushort32&, __vpred&);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vminupw_vvp                                                          */
/*----------------------------------------------------------------------------*/

/* VMINUPW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern void __vminupw_vvp(uint8, uint8&, __vpred&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __vminupw_vvp(uint16, uint16&, __vpred&);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vminuw_vvv                                                           */
/*----------------------------------------------------------------------------*/

/* VMINUW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vminuw_vvv(uint8, uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vminuw_vvv(uint16, uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vminw_vvv                                                            */
/*----------------------------------------------------------------------------*/

/* VMINW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vminw_vvv(int8, int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vminw_vvv(int16, int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vmpybb_vvv                                                           */
/*----------------------------------------------------------------------------*/

/* VMPYBB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __vmpybb_vvv(char32, char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __vmpybb_vvv(char64, char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vmpybb_vvv(uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vmpybb_vvv(uchar64, uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vmpydd_vvv                                                           */
/*----------------------------------------------------------------------------*/

/* VMPYDD */
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __vmpydd_vvv(long4, long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __vmpydd_vvv(long8, long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __vmpydd_vvv(ulong4, ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __vmpydd_vvv(ulong8, ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vmpydp_vvv                                                           */
/*----------------------------------------------------------------------------*/

/* VMPYDP */
#if __C7X_VEC_SIZE_BITS__ == 256
extern double4 __vmpydp_vvv(double4, double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern double8 __vmpydp_vvv(double8, double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vmpyhh_vvv                                                           */
/*----------------------------------------------------------------------------*/

/* VMPYHH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vmpyhh_vvv(short16, short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vmpyhh_vvv(short32, short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vmpyhh_vvv(ushort16, ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vmpyhh_vvv(ushort32, ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vmpyhw_vvw                                                           */
/*----------------------------------------------------------------------------*/

/* VMPYHW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern void __vmpyhw_vvw(short16, short16, int8&, int8&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __vmpyhw_vvw(short32, short32, int16&, int16&);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vmpysp2dp_vvw                                                        */
/*----------------------------------------------------------------------------*/

/* VMPYSP2DP */
#if __C7X_VEC_SIZE_BITS__ == 256
extern void __vmpysp2dp_vvw(float8, float8, double4&, double4&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __vmpysp2dp_vvw(float16, float16, double8&, double8&);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vmpysp_vvv                                                           */
/*----------------------------------------------------------------------------*/

/* VMPYSP */
#if __C7X_VEC_SIZE_BITS__ == 256
extern float8 __vmpysp_vvv(float8, float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern float16 __vmpysp_vvv(float16, float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vmpysubh_vvw                                                         */
/*----------------------------------------------------------------------------*/

/* VMPYSUBH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern void __vmpysubh_vvw(char32, uchar32, short16&, short16&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __vmpysubh_vvw(char64, uchar64, short32&, short32&);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vmpysuhw_vvw                                                         */
/*----------------------------------------------------------------------------*/

/* VMPYSUHW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern void __vmpysuhw_vvw(short16, ushort16, int8&, int8&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __vmpysuhw_vvw(short32, ushort32, int16&, int16&);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vmpysuwd_vvw                                                         */
/*----------------------------------------------------------------------------*/

/* VMPYSUWD */
#if __C7X_VEC_SIZE_BITS__ == 256
extern void __vmpysuwd_vvw(int8, uint8, long4&, long4&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __vmpysuwd_vvw(int16, uint16, long8&, long8&);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vmpyubh_vvw                                                          */
/*----------------------------------------------------------------------------*/

/* VMPYUBH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern void __vmpyubh_vvw(uchar32, uchar32, ushort16&, ushort16&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __vmpyubh_vvw(uchar64, uchar64, ushort32&, ushort32&);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vmpyudq_vvw                                                          */
/*----------------------------------------------------------------------------*/

/* VMPYUDQ */
#if __C7X_VEC_SIZE_BITS__ == 256
extern void __vmpyudq_vvw(ulong4, ulong4, ulong4&, ulong4&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __vmpyudq_vvw(ulong8, ulong8, ulong8&, ulong8&);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vmpyuhw_vvw                                                          */
/*----------------------------------------------------------------------------*/

/* VMPYUHW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern void __vmpyuhw_vvw(ushort16, ushort16, uint8&, uint8&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __vmpyuhw_vvw(ushort32, ushort32, uint16&, uint16&);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vmpyuwd_vvw                                                          */
/*----------------------------------------------------------------------------*/

/* VMPYUWD */
#if __C7X_VEC_SIZE_BITS__ == 256
extern void __vmpyuwd_vvw(uint8, uint8, ulong4&, ulong4&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __vmpyuwd_vvw(uint16, uint16, ulong8&, ulong8&);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vmpywd_vvw                                                           */
/*----------------------------------------------------------------------------*/

/* VMPYWD */
#if __C7X_VEC_SIZE_BITS__ == 256
extern void __vmpywd_vvw(int8, int8, long4&, long4&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __vmpywd_vvw(int16, int16, long8&, long8&);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vmpyww_vvv                                                           */
/*----------------------------------------------------------------------------*/

/* VMPYWW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vmpyww_vvv(int8, int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vmpyww_vvv(int16, int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vmpyww_vvv(uint8, uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vmpyww_vvv(uint16, uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vnandw_vvv                                                           */
/*----------------------------------------------------------------------------*/

/* VNANDW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __vnandw_vvv(char32, char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __vnandw_vvv(char64, char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vnandw_vvv(uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vnandw_vvv(uchar64, uchar64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vnandw_vvv(short16, short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vnandw_vvv(short32, short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vnandw_vvv(ushort16, ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vnandw_vvv(ushort32, ushort32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vnandw_vvv(int8, int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vnandw_vvv(int16, int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vnandw_vvv(uint8, uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vnandw_vvv(uint16, uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __vnandw_vvv(long4, long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __vnandw_vvv(long8, long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __vnandw_vvv(ulong4, ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __vnandw_vvv(ulong8, ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vnorm2uh_vv                                                          */
/*----------------------------------------------------------------------------*/

/* VNORM2UH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vnorm2uh_vv(ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vnorm2uh_vv(ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vnorm2uw_vv                                                          */
/*----------------------------------------------------------------------------*/

/* VNORM2UW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vnorm2uw_vv(uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vnorm2uw_vv(uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vnormb_vv                                                            */
/*----------------------------------------------------------------------------*/

/* VNORMB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __vnormb_vv(char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __vnormb_vv(char64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vnormd_vv                                                            */
/*----------------------------------------------------------------------------*/

/* VNORMD */
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __vnormd_vv(long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __vnormd_vv(long8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vnormh_vv                                                            */
/*----------------------------------------------------------------------------*/

/* VNORMH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vnormh_vv(short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vnormh_vv(short32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vnormw_vv                                                            */
/*----------------------------------------------------------------------------*/

/* VNORMW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vnormw_vv(int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vnormw_vv(int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vnorw_vvv                                                            */
/*----------------------------------------------------------------------------*/

/* VNORW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __vnorw_vvv(char32, char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __vnorw_vvv(char64, char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vnorw_vvv(uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vnorw_vvv(uchar64, uchar64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vnorw_vvv(short16, short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vnorw_vvv(short32, short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vnorw_vvv(ushort16, ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vnorw_vvv(ushort32, ushort32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vnorw_vvv(int8, int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vnorw_vvv(int16, int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vnorw_vvv(uint8, uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vnorw_vvv(uint16, uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __vnorw_vvv(long4, long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __vnorw_vvv(long8, long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __vnorw_vvv(ulong4, ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __vnorw_vvv(ulong8, ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vopmatmpysp_vvw                                                      */
/*----------------------------------------------------------------------------*/

/* VOPMATMPYSP */
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __vopmatmpysp_vvw(float16, float16, float16&, float16&);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vornw_vkv                                                            */
/*----------------------------------------------------------------------------*/

/* VORNW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vornw_vkv(int8, int8/*(k)*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vornw_vkv(int16, int16/*(k)*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vornw_vkv(uint8, uint8/*(k)*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vornw_vkv(uint16, uint16/*(k)*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vornw_vvv                                                            */
/*----------------------------------------------------------------------------*/

/* VORNW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __vornw_vvv(char32, char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __vornw_vvv(char64, char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vornw_vvv(uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vornw_vvv(uchar64, uchar64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vornw_vvv(short16, short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vornw_vvv(short32, short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vornw_vvv(ushort16, ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vornw_vvv(ushort32, ushort32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vornw_vvv(int8, int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vornw_vvv(int16, int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vornw_vvv(uint8, uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vornw_vvv(uint16, uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __vornw_vvv(long4, long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __vornw_vvv(long8, long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __vornw_vvv(ulong4, ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __vornw_vvv(ulong8, ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vorw_vkv                                                             */
/*----------------------------------------------------------------------------*/

/* VORW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vorw_vkv(int8, int8/*(k)*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vorw_vkv(int16, int16/*(k)*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vorw_vkv(uint8, uint8/*(k)*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vorw_vkv(uint16, uint16/*(k)*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vorw_vvv                                                             */
/*----------------------------------------------------------------------------*/

/* VORW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __vorw_vvv(char32, char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __vorw_vvv(char64, char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vorw_vvv(uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vorw_vvv(uchar64, uchar64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vorw_vvv(short16, short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vorw_vvv(short32, short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vorw_vvv(ushort16, ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vorw_vvv(ushort32, ushort32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vorw_vvv(int8, int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vorw_vvv(int16, int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vorw_vvv(uint8, uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vorw_vvv(uint16, uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __vorw_vvv(long4, long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __vorw_vvv(long8, long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __vorw_vvv(ulong4, ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __vorw_vvv(ulong8, ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vpackh2_vvv                                                          */
/*----------------------------------------------------------------------------*/

/* VPACKH2 */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cchar16 __vpackh2_vvv(cchar16, cchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cchar32 __vpackh2_vvv(cchar32, cchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vpackh2_vvv(short16, short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vpackh2_vvv(short32, short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vpackh2_vvv(ushort16, ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vpackh2_vvv(ushort32, ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vpackh4_vvv                                                          */
/*----------------------------------------------------------------------------*/

/* VPACKH4 */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __vpackh4_vvv(char32, char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __vpackh4_vvv(char64, char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vpackh4_vvv(uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vpackh4_vvv(uchar64, uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vpackhl2_vvv                                                         */
/*----------------------------------------------------------------------------*/

/* VPACKHL2 */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cchar16 __vpackhl2_vvv(cchar16, cchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cchar32 __vpackhl2_vvv(cchar32, cchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vpackhl2_vvv(short16, short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vpackhl2_vvv(short32, short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vpackhl2_vvv(ushort16, ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vpackhl2_vvv(ushort32, ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vpackl2_vvv                                                          */
/*----------------------------------------------------------------------------*/

/* VPACKL2 */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cchar16 __vpackl2_vvv(cchar16, cchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cchar32 __vpackl2_vvv(cchar32, cchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vpackl2_vvv(short16, short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vpackl2_vvv(short32, short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vpackl2_vvv(ushort16, ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vpackl2_vvv(ushort32, ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vpackl4_vvv                                                          */
/*----------------------------------------------------------------------------*/

/* VPACKL4 */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __vpackl4_vvv(char32, char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __vpackl4_vvv(char64, char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vpackl4_vvv(uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vpackl4_vvv(uchar64, uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vpacklh2_vvv                                                         */
/*----------------------------------------------------------------------------*/

/* VPACKLH2 */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cchar16 __vpacklh2_vvv(cchar16, cchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cchar32 __vpacklh2_vvv(cchar32, cchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vpacklh2_vvv(short16, short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vpacklh2_vvv(short32, short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vpacklh2_vvv(ushort16, ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vpacklh2_vvv(ushort32, ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vpacklh4_vvv                                                         */
/*----------------------------------------------------------------------------*/

/* VPACKLH4 */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __vpacklh4_vvv(char32, char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __vpacklh4_vvv(char64, char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vpacklh4_vvv(uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vpacklh4_vvv(uchar64, uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vpackp2_vvv                                                          */
/*----------------------------------------------------------------------------*/

/* VPACKP2 */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cchar16 __vpackp2_vvv(cchar16, cchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cchar32 __vpackp2_vvv(cchar32, cchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vpackp2_vvv(short16, short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vpackp2_vvv(short32, short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vpackp2_vvv(ushort16, ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vpackp2_vvv(ushort32, ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vpackw_vvv                                                           */
/*----------------------------------------------------------------------------*/

/* VPACKW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cshort8 __vpackw_vvv(cshort8, cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cshort16 __vpackw_vvv(cshort16, cshort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vpackw_vvv(int8, int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vpackw_vvv(int16, int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vpackw_vvv(uint8, uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vpackw_vvv(uint16, uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern float8 __vpackw_vvv(float8, float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern float16 __vpackw_vvv(float16, float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vpackx2_vvv                                                          */
/*----------------------------------------------------------------------------*/

/* VPACKX2 */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cchar16 __vpackx2_vvv(cchar16, cchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cchar32 __vpackx2_vvv(cchar32, cchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vpackx2_vvv(short16, short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vpackx2_vvv(short32, short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vpackx2_vvv(ushort16, ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vpackx2_vvv(ushort32, ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vperm_vvv                                                            */
/*----------------------------------------------------------------------------*/

/* VPERM */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vperm_vvv(uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vperm_vvv(uchar64, uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vperm_yvv                                                            */
/*----------------------------------------------------------------------------*/

/* VPERM */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vperm_yvv(uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vperm_yvv(uchar64, uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vpermeeb_yvvv                                                        */
/*----------------------------------------------------------------------------*/

/* VPERMEEB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vpermeeb_yvvv(uchar32, uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vpermeeb_yvvv(uchar64, uchar64, uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vpermeed_yvvv                                                        */
/*----------------------------------------------------------------------------*/

/* VPERMEED */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vpermeed_yvvv(uchar32, uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vpermeed_yvvv(uchar64, uchar64, uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vpermeeh_yvvv                                                        */
/*----------------------------------------------------------------------------*/

/* VPERMEEH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vpermeeh_yvvv(uchar32, uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vpermeeh_yvvv(uchar64, uchar64, uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vpermeeq_yvvv                                                        */
/*----------------------------------------------------------------------------*/

/* VPERMEEQ */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vpermeeq_yvvv(uchar32, uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vpermeeq_yvvv(uchar64, uchar64, uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vpermeew_yvvv                                                        */
/*----------------------------------------------------------------------------*/

/* VPERMEEW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vpermeew_yvvv(uchar32, uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vpermeew_yvvv(uchar64, uchar64, uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vpermeob_yvvv                                                        */
/*----------------------------------------------------------------------------*/

/* VPERMEOB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vpermeob_yvvv(uchar32, uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vpermeob_yvvv(uchar64, uchar64, uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vpermeod_yvvv                                                        */
/*----------------------------------------------------------------------------*/

/* VPERMEOD */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vpermeod_yvvv(uchar32, uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vpermeod_yvvv(uchar64, uchar64, uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vpermeoh_yvvv                                                        */
/*----------------------------------------------------------------------------*/

/* VPERMEOH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vpermeoh_yvvv(uchar32, uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vpermeoh_yvvv(uchar64, uchar64, uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vpermeoq_yvvv                                                        */
/*----------------------------------------------------------------------------*/

/* VPERMEOQ */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vpermeoq_yvvv(uchar32, uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vpermeoq_yvvv(uchar64, uchar64, uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vpermeow_yvvv                                                        */
/*----------------------------------------------------------------------------*/

/* VPERMEOW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vpermeow_yvvv(uchar32, uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vpermeow_yvvv(uchar64, uchar64, uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vpermhh_yvvv                                                         */
/*----------------------------------------------------------------------------*/

/* VPERMHH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vpermhh_yvvv(uchar32, uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vpermhh_yvvv(uchar64, uchar64, uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vpermlh_yvvv                                                         */
/*----------------------------------------------------------------------------*/

/* VPERMLH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vpermlh_yvvv(uchar32, uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vpermlh_yvvv(uchar64, uchar64, uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vpermll_yvvv                                                         */
/*----------------------------------------------------------------------------*/

/* VPERMLL */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vpermll_yvvv(uchar32, uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vpermll_yvvv(uchar64, uchar64, uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vpermoob_yvvv                                                        */
/*----------------------------------------------------------------------------*/

/* VPERMOOB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vpermoob_yvvv(uchar32, uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vpermoob_yvvv(uchar64, uchar64, uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vpermood_yvvv                                                        */
/*----------------------------------------------------------------------------*/

/* VPERMOOD */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vpermood_yvvv(uchar32, uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vpermood_yvvv(uchar64, uchar64, uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vpermooh_yvvv                                                        */
/*----------------------------------------------------------------------------*/

/* VPERMOOH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vpermooh_yvvv(uchar32, uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vpermooh_yvvv(uchar64, uchar64, uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vpermooq_yvvv                                                        */
/*----------------------------------------------------------------------------*/

/* VPERMOOQ */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vpermooq_yvvv(uchar32, uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vpermooq_yvvv(uchar64, uchar64, uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vpermoow_yvvv                                                        */
/*----------------------------------------------------------------------------*/

/* VPERMOOW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vpermoow_yvvv(uchar32, uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vpermoow_yvvv(uchar64, uchar64, uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vppackdup16w_pv                                                      */
/*----------------------------------------------------------------------------*/

/* VPPACKDUP16W */
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vppackdup16w_pv(__vpred);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vppackdup8w_pv                                                       */
/*----------------------------------------------------------------------------*/

/* VPPACKDUP8W */
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vppackdup8w_pv(__vpred);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vputb_dky                                                            */
/*----------------------------------------------------------------------------*/

/* VPUTB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __vputb_dky(int8_t, int8_t/*(k={0-63})*/, char32);
extern uchar32 __vputb_dky(uint8_t, uint8_t/*(k={0-63})*/, uchar32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vputb_rkv                                                            */
/*----------------------------------------------------------------------------*/

/* VPUTB */
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __vputb_rkv(int8_t, int8_t/*(k={0-63})*/, char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __vputb_rkv(int8_t, int8_t/*(k={0-63})*/, char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vputb_rkv(uint8_t, uint8_t/*(k={0-63})*/, uchar64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vputb_rkv(uint8_t, uint8_t/*(k={0-63})*/, uchar32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vputd_dkv                                                            */
/*----------------------------------------------------------------------------*/

/* VPUTD */
#if __C7X_VEC_SIZE_BITS__ == 512
extern cint8 __vputd_dkv(cint, int8_t/*(k={0-63})*/, cint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cint4 __vputd_dkv(cint, int8_t/*(k={0-63})*/, cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cfloat8 __vputd_dkv(cfloat, int8_t/*(k={0-63})*/, cfloat8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cfloat4 __vputd_dkv(cfloat, int8_t/*(k={0-63})*/, cfloat4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cfloat8 __vputd_dkv(cfloat, uint8_t/*(k={0-63})*/, cfloat8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cfloat4 __vputd_dkv(cfloat, uint8_t/*(k={0-63})*/, cfloat4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __vputd_dkv(int64_t, int8_t/*(k={0-63})*/, long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __vputd_dkv(int64_t, int8_t/*(k={0-63})*/, long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __vputd_dkv(uint64_t, uint8_t/*(k={0-63})*/, ulong8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __vputd_dkv(uint64_t, uint8_t/*(k={0-63})*/, ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern double8 __vputd_dkv(double, int8_t/*(k={0-63})*/, double8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern double4 __vputd_dkv(double, int8_t/*(k={0-63})*/, double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern double8 __vputd_dkv(double, uint8_t/*(k={0-63})*/, double8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern double4 __vputd_dkv(double, uint8_t/*(k={0-63})*/, double4);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vputd_dky                                                            */
/*----------------------------------------------------------------------------*/

/* VPUTD */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cint4 __vputd_dky(cint, int8_t/*(k={0-63})*/, cint4);
extern cfloat4 __vputd_dky(cfloat, int8_t/*(k={0-63})*/, cfloat4);
extern cfloat4 __vputd_dky(cfloat, uint8_t/*(k={0-63})*/, cfloat4);
extern long4 __vputd_dky(int64_t, int8_t/*(k={0-63})*/, long4);
extern ulong4 __vputd_dky(uint64_t, uint8_t/*(k={0-63})*/, ulong4);
extern double4 __vputd_dky(double, int8_t/*(k={0-63})*/, double4);
extern double4 __vputd_dky(double, uint8_t/*(k={0-63})*/, double4);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vputh_dky                                                            */
/*----------------------------------------------------------------------------*/

/* VPUTH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cchar16 __vputh_dky(cchar, int8_t/*(k={0-63})*/, cchar16);
extern short16 __vputh_dky(int16_t, int8_t/*(k={0-63})*/, short16);
extern ushort16 __vputh_dky(uint16_t, uint8_t/*(k={0-63})*/, ushort16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vputh_rkv                                                            */
/*----------------------------------------------------------------------------*/

/* VPUTH */
#if __C7X_VEC_SIZE_BITS__ == 512
extern cchar32 __vputh_rkv(cchar, int8_t/*(k={0-63})*/, cchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cchar16 __vputh_rkv(cchar, int8_t/*(k={0-63})*/, cchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vputh_rkv(int16_t, int8_t/*(k={0-63})*/, short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vputh_rkv(int16_t, int8_t/*(k={0-63})*/, short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vputh_rkv(uint16_t, uint8_t/*(k={0-63})*/, ushort32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vputh_rkv(uint16_t, uint8_t/*(k={0-63})*/, ushort16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vputw_dky                                                            */
/*----------------------------------------------------------------------------*/

/* VPUTW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cshort8 __vputw_dky(cshort, int8_t/*(k={0-63})*/, cshort8);
extern int8 __vputw_dky(int32_t, int8_t/*(k={0-63})*/, int8);
extern uint8 __vputw_dky(uint32_t, uint8_t/*(k={0-63})*/, uint8);
extern float8 __vputw_dky(float, int8_t/*(k={0-63})*/, float8);
extern float8 __vputw_dky(float, uint8_t/*(k={0-63})*/, float8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vputw_rkv                                                            */
/*----------------------------------------------------------------------------*/

/* VPUTW */
#if __C7X_VEC_SIZE_BITS__ == 512
extern cshort16 __vputw_rkv(cshort, int8_t/*(k={0-63})*/, cshort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cshort8 __vputw_rkv(cshort, int8_t/*(k={0-63})*/, cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vputw_rkv(int32_t, int8_t/*(k={0-63})*/, int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vputw_rkv(int32_t, int8_t/*(k={0-63})*/, int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vputw_rkv(uint32_t, uint8_t/*(k={0-63})*/, uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vputw_rkv(uint32_t, uint8_t/*(k={0-63})*/, uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern float16 __vputw_rkv(float, int8_t/*(k={0-63})*/, float16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern float8 __vputw_rkv(float, int8_t/*(k={0-63})*/, float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern float16 __vputw_rkv(float, uint8_t/*(k={0-63})*/, float16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern float8 __vputw_rkv(float, uint8_t/*(k={0-63})*/, float8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vpxpnd_pv                                                            */
/*----------------------------------------------------------------------------*/

/* VPXPND */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __vpxpnd_pv(__vpred);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __vpxpnd_pv(__vpred);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vrcpdp_vv                                                            */
/*----------------------------------------------------------------------------*/

/* VRCPDP */
#if __C7X_VEC_SIZE_BITS__ == 256
extern double4 __vrcpdp_vv(double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern double8 __vrcpdp_vv(double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vrcpsp_vv                                                            */
/*----------------------------------------------------------------------------*/

/* VRCPSP */
#if __C7X_VEC_SIZE_BITS__ == 256
extern float8 __vrcpsp_vv(float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern float16 __vrcpsp_vv(float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vreplace_vkkv                                                        */
/*----------------------------------------------------------------------------*/

/* VREPLACE */
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __vreplace_vkkv(long4, char4/*(k={0-63})*/, char4/*(k={0-63})*/, long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __vreplace_vkkv(long8, char8/*(k={0-63})*/, char8/*(k={0-63})*/, long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __vreplace_vkkv(ulong4, uchar4/*(k={0-63})*/, uchar4/*(k={0-63})*/, ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __vreplace_vkkv(ulong8, uchar8/*(k={0-63})*/, uchar8/*(k={0-63})*/, ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vreverseb_vv                                                         */
/*----------------------------------------------------------------------------*/

/* VREVERSEB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __vreverseb_vv(char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __vreverseb_vv(char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vreverseb_vv(uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vreverseb_vv(uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vreversed_vv                                                         */
/*----------------------------------------------------------------------------*/

/* VREVERSED */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cint4 __vreversed_vv(cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cint8 __vreversed_vv(cint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cfloat4 __vreversed_vv(cfloat4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cfloat8 __vreversed_vv(cfloat8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __vreversed_vv(long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __vreversed_vv(long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __vreversed_vv(ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __vreversed_vv(ulong8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern double4 __vreversed_vv(double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern double8 __vreversed_vv(double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vreverseh_vv                                                         */
/*----------------------------------------------------------------------------*/

/* VREVERSEH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cchar16 __vreverseh_vv(cchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cchar32 __vreverseh_vv(cchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vreverseh_vv(short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vreverseh_vv(short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vreverseh_vv(ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vreverseh_vv(ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vreversew_vv                                                         */
/*----------------------------------------------------------------------------*/

/* VREVERSEW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cshort8 __vreversew_vv(cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cshort16 __vreversew_vv(cshort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vreversew_vv(int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vreversew_vv(int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vreversew_vv(uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vreversew_vv(uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern float8 __vreversew_vv(float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern float16 __vreversew_vv(float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vrotlb_vkv                                                           */
/*----------------------------------------------------------------------------*/

/* VROTLB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vrotlb_vkv(uchar32, uchar32/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vrotlb_vkv(uchar64, uchar64/*(k={0-63})*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vrotlb_vvv                                                           */
/*----------------------------------------------------------------------------*/

/* VROTLB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vrotlb_vvv(uchar32, uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vrotlb_vvv(uchar64, uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vrotld_vkv                                                           */
/*----------------------------------------------------------------------------*/

/* VROTLD */
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __vrotld_vkv(ulong4, uchar4/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __vrotld_vkv(ulong8, uchar8/*(k={0-63})*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vrotld_vvv                                                           */
/*----------------------------------------------------------------------------*/

/* VROTLD */
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __vrotld_vvv(ulong4, ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __vrotld_vvv(ulong8, ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vrotlh_vkv                                                           */
/*----------------------------------------------------------------------------*/

/* VROTLH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vrotlh_vkv(ushort16, ushort16/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vrotlh_vkv(ushort32, ushort32/*(k={0-63})*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vrotlh_vvv                                                           */
/*----------------------------------------------------------------------------*/

/* VROTLH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vrotlh_vvv(ushort16, uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vrotlh_vvv(ushort32, uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vrotlw_vkv                                                           */
/*----------------------------------------------------------------------------*/

/* VROTLW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vrotlw_vkv(int8, uchar8/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vrotlw_vkv(int16, uchar16/*(k={0-63})*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vrotlw_vvv                                                           */
/*----------------------------------------------------------------------------*/

/* VROTLW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vrotlw_vvv(int8, uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vrotlw_vvv(int16, uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vrpackh_vvv                                                          */
/*----------------------------------------------------------------------------*/

/* VRPACKH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vrpackh_vvv(int8, int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vrpackh_vvv(int16, int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vrsqrdp_vv                                                           */
/*----------------------------------------------------------------------------*/

/* VRSQRDP */
#if __C7X_VEC_SIZE_BITS__ == 256
extern double4 __vrsqrdp_vv(double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern double8 __vrsqrdp_vv(double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vrsqrsp_vv                                                           */
/*----------------------------------------------------------------------------*/

/* VRSQRSP */
#if __C7X_VEC_SIZE_BITS__ == 256
extern float8 __vrsqrsp_vv(float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern float16 __vrsqrsp_vv(float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsad16ou16h16w_vvv                                                   */
/*----------------------------------------------------------------------------*/

/* VSAD16OU16H16W */
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vsad16ou16h16w_vvv(ushort32, ushort16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsad16ou8h16w_vvv                                                    */
/*----------------------------------------------------------------------------*/

/* VSAD16OU8H16W */
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vsad16ou8h16w_vvv(ushort32, ushort8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsad8ou16b32h_vvv                                                    */
/*----------------------------------------------------------------------------*/

/* VSAD8OU16B32H */
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vsad8ou16b32h_vvv(uchar64, uchar16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsaddb_vkv                                                           */
/*----------------------------------------------------------------------------*/

/* VSADDB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __vsaddb_vkv(char32, char32/*(k)*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __vsaddb_vkv(char64, char64/*(k)*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsaddb_vvv                                                           */
/*----------------------------------------------------------------------------*/

/* VSADDB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __vsaddb_vvv(char32, char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __vsaddb_vvv(char64, char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cchar16 __vsaddb_vvv(cchar16, cchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cchar32 __vsaddb_vvv(cchar32, cchar32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsaddh_vkv                                                           */
/*----------------------------------------------------------------------------*/

/* VSADDH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vsaddh_vkv(short16, short16/*(k)*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vsaddh_vkv(short32, short32/*(k)*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsaddh_vvv                                                           */
/*----------------------------------------------------------------------------*/

/* VSADDH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vsaddh_vvv(short16, short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vsaddh_vvv(short32, short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cshort8 __vsaddh_vvv(cshort8, cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cshort16 __vsaddh_vvv(cshort16, cshort16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsaddub_vvv                                                          */
/*----------------------------------------------------------------------------*/

/* VSADDUB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vsaddub_vvv(uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vsaddub_vvv(uchar64, uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsadduh_vvv                                                          */
/*----------------------------------------------------------------------------*/

/* VSADDUH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vsadduh_vvv(ushort16, ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vsadduh_vvv(ushort32, ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsaddusb_vvv                                                         */
/*----------------------------------------------------------------------------*/

/* VSADDUSB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vsaddusb_vvv(uchar32, char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vsaddusb_vvv(uchar64, char64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsaddush_vvv                                                         */
/*----------------------------------------------------------------------------*/

/* VSADDUSH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vsaddush_vvv(ushort16, short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vsaddush_vvv(ushort32, short32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsaddusw_vvv                                                         */
/*----------------------------------------------------------------------------*/

/* VSADDUSW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vsaddusw_vvv(uint8, int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vsaddusw_vvv(uint16, int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsadduw_vvv                                                          */
/*----------------------------------------------------------------------------*/

/* VSADDUW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vsadduw_vvv(uint8, uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vsadduw_vvv(uint16, uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsaddw_vkv                                                           */
/*----------------------------------------------------------------------------*/

/* VSADDW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vsaddw_vkv(int8, int8/*(k)*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vsaddw_vkv(int16, int16/*(k)*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsaddw_vvv                                                           */
/*----------------------------------------------------------------------------*/

/* VSADDW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vsaddw_vvv(int8, int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vsaddw_vvv(int16, int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cint4 __vsaddw_vvv(cint4, cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cint8 __vsaddw_vvv(cint8, cint8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsadm16ou16h16w_yvvv                                                 */
/*----------------------------------------------------------------------------*/

/* VSADM16OU16H16W */
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vsadm16ou16h16w_yvvv(uchar64, ushort32, ushort16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsadm16ou8h16w_yvvv                                                  */
/*----------------------------------------------------------------------------*/

/* VSADM16OU8H16W */
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vsadm16ou8h16w_yvvv(uchar64, ushort32, ushort8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsadm8ou16b32h_yvvv                                                  */
/*----------------------------------------------------------------------------*/

/* VSADM8OU16B32H */
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vsadm8ou16b32h_yvvv(uchar64, uchar64, uchar16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsatdl_vv                                                            */
/*----------------------------------------------------------------------------*/

/* VSATDL */
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __vsatdl_vv(long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __vsatdl_vv(long8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsatdw_vv                                                            */
/*----------------------------------------------------------------------------*/

/* VSATDW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __vsatdw_vv(long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __vsatdw_vv(long8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsathb_vv                                                            */
/*----------------------------------------------------------------------------*/

/* VSATHB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vsathb_vv(short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vsathb_vv(short32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsatlw_vv                                                            */
/*----------------------------------------------------------------------------*/

/* VSATLW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __vsatlw_vv(long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __vsatlw_vv(long8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsatwh_vv                                                            */
/*----------------------------------------------------------------------------*/

/* VSATWH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vsatwh_vv(int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vsatwh_vv(int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vscaledp_vvv                                                         */
/*----------------------------------------------------------------------------*/

/* VSCALEDP */
#if __C7X_VEC_SIZE_BITS__ == 256
extern double4 __vscaledp_vvv(double4, ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern double8 __vscaledp_vvv(double8, ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vscalesp_vvv                                                         */
/*----------------------------------------------------------------------------*/

/* VSCALESP */
#if __C7X_VEC_SIZE_BITS__ == 256
extern float8 __vscalesp_vvv(float8, uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern float16 __vscalesp_vvv(float16, uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vscatterb_pvv                                                        */
/*----------------------------------------------------------------------------*/

/* VSCATTERB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __vscatterb_pvv(__vpred, char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __vscatterb_pvv(__vpred, char64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vscatternb_pvv                                                       */
/*----------------------------------------------------------------------------*/

/* VSCATTERNB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __vscatternb_pvv(__vpred, char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __vscatternb_pvv(__vpred, char64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsel_pvkv                                                            */
/*----------------------------------------------------------------------------*/

/* VSEL */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vsel_pvkv(__vpred, int8, int8/*(k)*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vsel_pvkv(__vpred, int16, int16/*(k)*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vsel_pvkv(__vpred, uint8, uint8/*(k)*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vsel_pvkv(__vpred, uint16, uint16/*(k)*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern float8 __vsel_pvkv(__vpred, float8, float8/*(k)*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern float16 __vsel_pvkv(__vpred, float16, float16/*(k)*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsel_pvvv                                                            */
/*----------------------------------------------------------------------------*/

/* VSEL */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __vsel_pvvv(__vpred, char32, char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __vsel_pvvv(__vpred, char64, char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vsel_pvvv(__vpred, uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vsel_pvvv(__vpred, uchar64, uchar64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cchar16 __vsel_pvvv(__vpred, cchar16, cchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cchar32 __vsel_pvvv(__vpred, cchar32, cchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vsel_pvvv(__vpred, short16, short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vsel_pvvv(__vpred, short32, short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vsel_pvvv(__vpred, ushort16, ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vsel_pvvv(__vpred, ushort32, ushort32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cshort8 __vsel_pvvv(__vpred, cshort8, cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cshort16 __vsel_pvvv(__vpred, cshort16, cshort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vsel_pvvv(__vpred, int8, int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vsel_pvvv(__vpred, int16, int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vsel_pvvv(__vpred, uint8, uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vsel_pvvv(__vpred, uint16, uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern float8 __vsel_pvvv(__vpred, float8, float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern float16 __vsel_pvvv(__vpred, float16, float16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cint4 __vsel_pvvv(__vpred, cint4, cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cint8 __vsel_pvvv(__vpred, cint8, cint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cfloat4 __vsel_pvvv(__vpred, cfloat4, cfloat4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cfloat8 __vsel_pvvv(__vpred, cfloat8, cfloat8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __vsel_pvvv(__vpred, long4, long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __vsel_pvvv(__vpred, long8, long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __vsel_pvvv(__vpred, ulong4, ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __vsel_pvvv(__vpred, ulong8, ulong8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern double4 __vsel_pvvv(__vpred, double4, double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern double8 __vsel_pvvv(__vpred, double8, double8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern clong2 __vsel_pvvv(__vpred, clong2, clong2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern clong4 __vsel_pvvv(__vpred, clong4, clong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cdouble2 __vsel_pvvv(__vpred, cdouble2, cdouble2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cdouble4 __vsel_pvvv(__vpred, cdouble4, cdouble4);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshfl2b_vv                                                           */
/*----------------------------------------------------------------------------*/

/* VSHFL2B */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __vshfl2b_vv(char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __vshfl2b_vv(char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vshfl2b_vv(uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vshfl2b_vv(uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshfl2d_vv                                                           */
/*----------------------------------------------------------------------------*/

/* VSHFL2D */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cint4 __vshfl2d_vv(cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cint8 __vshfl2d_vv(cint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cfloat4 __vshfl2d_vv(cfloat4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cfloat8 __vshfl2d_vv(cfloat8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __vshfl2d_vv(long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __vshfl2d_vv(long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __vshfl2d_vv(ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __vshfl2d_vv(ulong8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern double4 __vshfl2d_vv(double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern double8 __vshfl2d_vv(double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshfl2dee_vvv                                                        */
/*----------------------------------------------------------------------------*/

/* VSHFL2DEE */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cint4 __vshfl2dee_vvv(cint4, cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cint8 __vshfl2dee_vvv(cint8, cint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cfloat4 __vshfl2dee_vvv(cfloat4, cfloat4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cfloat8 __vshfl2dee_vvv(cfloat8, cfloat8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __vshfl2dee_vvv(long4, long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __vshfl2dee_vvv(long8, long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __vshfl2dee_vvv(ulong4, ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __vshfl2dee_vvv(ulong8, ulong8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern double4 __vshfl2dee_vvv(double4, double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern double8 __vshfl2dee_vvv(double8, double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshfl2deo_vvv                                                        */
/*----------------------------------------------------------------------------*/

/* VSHFL2DEO */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cint4 __vshfl2deo_vvv(cint4, cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cint8 __vshfl2deo_vvv(cint8, cint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cfloat4 __vshfl2deo_vvv(cfloat4, cfloat4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cfloat8 __vshfl2deo_vvv(cfloat8, cfloat8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __vshfl2deo_vvv(long4, long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __vshfl2deo_vvv(long8, long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __vshfl2deo_vvv(ulong4, ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __vshfl2deo_vvv(ulong8, ulong8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern double4 __vshfl2deo_vvv(double4, double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern double8 __vshfl2deo_vvv(double8, double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshfl2dhh_vvv                                                        */
/*----------------------------------------------------------------------------*/

/* VSHFL2DHH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cint4 __vshfl2dhh_vvv(cint4, cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cint8 __vshfl2dhh_vvv(cint8, cint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cfloat4 __vshfl2dhh_vvv(cfloat4, cfloat4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cfloat8 __vshfl2dhh_vvv(cfloat8, cfloat8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __vshfl2dhh_vvv(long4, long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __vshfl2dhh_vvv(long8, long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __vshfl2dhh_vvv(ulong4, ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __vshfl2dhh_vvv(ulong8, ulong8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern double4 __vshfl2dhh_vvv(double4, double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern double8 __vshfl2dhh_vvv(double8, double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshfl2dlh_vvv                                                        */
/*----------------------------------------------------------------------------*/

/* VSHFL2DLH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cint4 __vshfl2dlh_vvv(cint4, cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cint8 __vshfl2dlh_vvv(cint8, cint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cfloat4 __vshfl2dlh_vvv(cfloat4, cfloat4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cfloat8 __vshfl2dlh_vvv(cfloat8, cfloat8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __vshfl2dlh_vvv(long4, long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __vshfl2dlh_vvv(long8, long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __vshfl2dlh_vvv(ulong4, ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __vshfl2dlh_vvv(ulong8, ulong8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern double4 __vshfl2dlh_vvv(double4, double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern double8 __vshfl2dlh_vvv(double8, double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshfl2dll_vvv                                                        */
/*----------------------------------------------------------------------------*/

/* VSHFL2DLL */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cint4 __vshfl2dll_vvv(cint4, cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cint8 __vshfl2dll_vvv(cint8, cint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cfloat4 __vshfl2dll_vvv(cfloat4, cfloat4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cfloat8 __vshfl2dll_vvv(cfloat8, cfloat8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __vshfl2dll_vvv(long4, long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __vshfl2dll_vvv(long8, long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __vshfl2dll_vvv(ulong4, ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __vshfl2dll_vvv(ulong8, ulong8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern double4 __vshfl2dll_vvv(double4, double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern double8 __vshfl2dll_vvv(double8, double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshfl2doo_vvv                                                        */
/*----------------------------------------------------------------------------*/

/* VSHFL2DOO */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cint4 __vshfl2doo_vvv(cint4, cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cint8 __vshfl2doo_vvv(cint8, cint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cfloat4 __vshfl2doo_vvv(cfloat4, cfloat4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cfloat8 __vshfl2doo_vvv(cfloat8, cfloat8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __vshfl2doo_vvv(long4, long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __vshfl2doo_vvv(long8, long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __vshfl2doo_vvv(ulong4, ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __vshfl2doo_vvv(ulong8, ulong8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern double4 __vshfl2doo_vvv(double4, double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern double8 __vshfl2doo_vvv(double8, double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshfl2h_vv                                                           */
/*----------------------------------------------------------------------------*/

/* VSHFL2H */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cchar16 __vshfl2h_vv(cchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cchar32 __vshfl2h_vv(cchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vshfl2h_vv(short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vshfl2h_vv(short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vshfl2h_vv(ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vshfl2h_vv(ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshfl2hhh_vvv                                                        */
/*----------------------------------------------------------------------------*/

/* VSHFL2HHH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cchar16 __vshfl2hhh_vvv(cchar16, cchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cchar32 __vshfl2hhh_vvv(cchar32, cchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vshfl2hhh_vvv(short16, short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vshfl2hhh_vvv(short32, short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vshfl2hhh_vvv(ushort16, ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vshfl2hhh_vvv(ushort32, ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshfl2hll_vvv                                                        */
/*----------------------------------------------------------------------------*/

/* VSHFL2HLL */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cchar16 __vshfl2hll_vvv(cchar16, cchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cchar32 __vshfl2hll_vvv(cchar32, cchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vshfl2hll_vvv(short16, short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vshfl2hll_vvv(short32, short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vshfl2hll_vvv(ushort16, ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vshfl2hll_vvv(ushort32, ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshfl2w_vv                                                           */
/*----------------------------------------------------------------------------*/

/* VSHFL2W */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cshort8 __vshfl2w_vv(cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cshort16 __vshfl2w_vv(cshort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vshfl2w_vv(int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vshfl2w_vv(int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vshfl2w_vv(uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vshfl2w_vv(uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern float8 __vshfl2w_vv(float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern float16 __vshfl2w_vv(float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshfl2whh_vvv                                                        */
/*----------------------------------------------------------------------------*/

/* VSHFL2WHH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cshort8 __vshfl2whh_vvv(cshort8, cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cshort16 __vshfl2whh_vvv(cshort16, cshort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vshfl2whh_vvv(int8, int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vshfl2whh_vvv(int16, int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vshfl2whh_vvv(uint8, uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vshfl2whh_vvv(uint16, uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern float8 __vshfl2whh_vvv(float8, float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern float16 __vshfl2whh_vvv(float16, float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshfl2wll_vvv                                                        */
/*----------------------------------------------------------------------------*/

/* VSHFL2WLL */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cshort8 __vshfl2wll_vvv(cshort8, cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cshort16 __vshfl2wll_vvv(cshort16, cshort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vshfl2wll_vvv(int8, int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vshfl2wll_vvv(int16, int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vshfl2wll_vvv(uint8, uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vshfl2wll_vvv(uint16, uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern float8 __vshfl2wll_vvv(float8, float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern float16 __vshfl2wll_vvv(float16, float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshfl3_vvv                                                           */
/*----------------------------------------------------------------------------*/

/* VSHFL3 */
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __vshfl3_vvv(int8, int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __vshfl3_vvv(int16, int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __vshfl3_vvv(uint8, uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __vshfl3_vvv(uint16, uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshfl4b_vv                                                           */
/*----------------------------------------------------------------------------*/

/* VSHFL4B */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __vshfl4b_vv(char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __vshfl4b_vv(char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vshfl4b_vv(uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vshfl4b_vv(uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshfl4h_vv                                                           */
/*----------------------------------------------------------------------------*/

/* VSHFL4H */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cchar16 __vshfl4h_vv(cchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cchar32 __vshfl4h_vv(cchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vshfl4h_vv(short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vshfl4h_vv(short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vshfl4h_vv(ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vshfl4h_vv(ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshfl4w_vv                                                           */
/*----------------------------------------------------------------------------*/

/* VSHFL4W */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cshort8 __vshfl4w_vv(cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cshort16 __vshfl4w_vv(cshort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vshfl4w_vv(int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vshfl4w_vv(int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vshfl4w_vv(uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vshfl4w_vv(uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern float8 __vshfl4w_vv(float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern float16 __vshfl4w_vv(float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshl_vkv                                                             */
/*----------------------------------------------------------------------------*/

/* VSHL */
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __vshl_vkv(ulong8, uint8_t/*(k={1-64})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __vshl_vkv(ulong4, uint8_t/*(k={1-64})*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshl_vvv                                                             */
/*----------------------------------------------------------------------------*/

/* VSHL */
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __vshl_vvv(ulong4, ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __vshl_vvv(ulong8, ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshlb_vkv                                                            */
/*----------------------------------------------------------------------------*/

/* VSHLB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __vshlb_vkv(char32, char32/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __vshlb_vkv(char64, char64/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vshlb_vkv(uchar32, uchar32/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vshlb_vkv(uchar64, uchar64/*(k={0-63})*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshlb_vvv                                                            */
/*----------------------------------------------------------------------------*/

/* VSHLB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __vshlb_vvv(char32, int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __vshlb_vvv(char64, int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vshlb_vvv(uchar32, uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vshlb_vvv(uchar64, uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshlcb_pvv                                                           */
/*----------------------------------------------------------------------------*/

/* VSHLCB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __vshlcb_pvv(__vpred, char32, char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __vshlcb_pvv(__vpred, char64, char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vshlcb_pvv(__vpred, uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vshlcb_pvv(__vpred, uchar64, uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshlch_pvv                                                           */
/*----------------------------------------------------------------------------*/

/* VSHLCH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vshlch_pvv(__vpred, short16, short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vshlch_pvv(__vpred, short32, short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vshlch_pvv(__vpred, ushort16, ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vshlch_pvv(__vpred, ushort32, ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshlcw_pvv                                                           */
/*----------------------------------------------------------------------------*/

/* VSHLCW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vshlcw_pvv(__vpred, int8, int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vshlcw_pvv(__vpred, int16, int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vshlcw_pvv(__vpred, uint8, uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vshlcw_pvv(__vpred, uint16, uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshld_vkv                                                            */
/*----------------------------------------------------------------------------*/

/* VSHLD */
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __vshld_vkv(long4, long4/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __vshld_vkv(long8, long8/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __vshld_vkv(ulong4, ulong4/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __vshld_vkv(ulong8, ulong8/*(k={0-63})*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshld_vvv                                                            */
/*----------------------------------------------------------------------------*/

/* VSHLD */
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __vshld_vvv(long4, long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __vshld_vvv(long8, long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __vshld_vvv(ulong4, ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __vshld_vvv(ulong8, ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshlh_vkv                                                            */
/*----------------------------------------------------------------------------*/

/* VSHLH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vshlh_vkv(short16, short16/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vshlh_vkv(short32, short32/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vshlh_vkv(ushort16, ushort16/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vshlh_vkv(ushort32, ushort32/*(k={0-63})*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshlh_vvv                                                            */
/*----------------------------------------------------------------------------*/

/* VSHLH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vshlh_vvv(short16, int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vshlh_vvv(short32, int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vshlh_vvv(ushort16, uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vshlh_vvv(ushort32, uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshlm16b_vvv                                                         */
/*----------------------------------------------------------------------------*/

/* VSHLM16B */
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __vshlm16b_vvv(char64, char16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __vshlm16b_vvv(char32, char16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshlm1b_vrv                                                          */
/*----------------------------------------------------------------------------*/

/* VSHLM1B */
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __vshlm1b_vrv(char64, int8_t);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __vshlm1b_vrv(char32, int8_t);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshlm2b_vrv                                                          */
/*----------------------------------------------------------------------------*/

/* VSHLM2B */
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __vshlm2b_vrv(char64, char2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __vshlm2b_vrv(char32, char2);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshlm4b_vrv                                                          */
/*----------------------------------------------------------------------------*/

/* VSHLM4B */
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __vshlm4b_vrv(char64, char4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __vshlm4b_vrv(char32, char4);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshlm8b_vdv                                                          */
/*----------------------------------------------------------------------------*/

/* VSHLM8B */
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __vshlm8b_vdv(char64, char8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __vshlm8b_vdv(char32, char8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshlmb_vvv                                                           */
/*----------------------------------------------------------------------------*/

/* VSHLMB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vshlmb_vvv(int8, char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vshlmb_vvv(int16, char64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshlw_vkv                                                            */
/*----------------------------------------------------------------------------*/

/* VSHLW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vshlw_vkv(int8, int8/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vshlw_vkv(int16, int16/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vshlw_vkv(uint8, uint8/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vshlw_vkv(uint16, uint16/*(k={0-63})*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshlw_vvv                                                            */
/*----------------------------------------------------------------------------*/

/* VSHLW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vshlw_vvv(int8, int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vshlw_vvv(int16, int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vshlw_vvv(uint8, uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vshlw_vvv(uint16, uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshr_vkv                                                             */
/*----------------------------------------------------------------------------*/

/* VSHR */
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __vshr_vkv(long8, uint8_t/*(k={1-64})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __vshr_vkv(long4, uint8_t/*(k={1-64})*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshr_vvv                                                             */
/*----------------------------------------------------------------------------*/

/* VSHR */
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __vshr_vvv(long4, ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __vshr_vvv(long8, ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshrb_vkv                                                            */
/*----------------------------------------------------------------------------*/

/* VSHRB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __vshrb_vkv(char32, char32/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __vshrb_vkv(char64, char64/*(k={0-63})*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshrb_vvv                                                            */
/*----------------------------------------------------------------------------*/

/* VSHRB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __vshrb_vvv(char32, int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __vshrb_vvv(char64, int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshrd_vkv                                                            */
/*----------------------------------------------------------------------------*/

/* VSHRD */
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __vshrd_vkv(long4, long4/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __vshrd_vkv(long8, long8/*(k={0-63})*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshrd_vvv                                                            */
/*----------------------------------------------------------------------------*/

/* VSHRD */
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __vshrd_vvv(long4, long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __vshrd_vvv(long8, long8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshrh_vkv                                                            */
/*----------------------------------------------------------------------------*/

/* VSHRH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vshrh_vkv(short16, short16/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vshrh_vkv(short32, short32/*(k={0-63})*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshrh_vvv                                                            */
/*----------------------------------------------------------------------------*/

/* VSHRH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vshrh_vvv(short16, int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vshrh_vvv(short32, int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshrm16b_vvv                                                         */
/*----------------------------------------------------------------------------*/

/* VSHRM16B */
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __vshrm16b_vvv(char64, char16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __vshrm16b_vvv(char32, char16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshrm1b_vrv                                                          */
/*----------------------------------------------------------------------------*/

/* VSHRM1B */
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __vshrm1b_vrv(char64, int8_t);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __vshrm1b_vrv(char32, int8_t);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshrm2b_vrv                                                          */
/*----------------------------------------------------------------------------*/

/* VSHRM2B */
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __vshrm2b_vrv(char64, char2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __vshrm2b_vrv(char32, char2);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshrm4b_vrv                                                          */
/*----------------------------------------------------------------------------*/

/* VSHRM4B */
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __vshrm4b_vrv(char64, char4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __vshrm4b_vrv(char32, char4);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshrm8b_vdv                                                          */
/*----------------------------------------------------------------------------*/

/* VSHRM8B */
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __vshrm8b_vdv(char64, char8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __vshrm8b_vdv(char32, char8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshrmb_vvv                                                           */
/*----------------------------------------------------------------------------*/

/* VSHRMB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vshrmb_vvv(int8, char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vshrmb_vvv(int16, char64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshrrb_vkv                                                           */
/*----------------------------------------------------------------------------*/

/* VSHRRB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __vshrrb_vkv(char32, uchar32/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __vshrrb_vkv(char64, uchar64/*(k={0-63})*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshrrb_vvv                                                           */
/*----------------------------------------------------------------------------*/

/* VSHRRB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __vshrrb_vvv(char32, uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __vshrrb_vvv(char64, uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshrrd_vkv                                                           */
/*----------------------------------------------------------------------------*/

/* VSHRRD */
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __vshrrd_vkv(long4, uchar4/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __vshrrd_vkv(long8, uchar8/*(k={0-63})*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshrrd_vvv                                                           */
/*----------------------------------------------------------------------------*/

/* VSHRRD */
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __vshrrd_vvv(long4, ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __vshrrd_vvv(long8, ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshrrh_vkv                                                           */
/*----------------------------------------------------------------------------*/

/* VSHRRH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vshrrh_vkv(short16, uchar16/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vshrrh_vkv(short32, uchar32/*(k={0-63})*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshrrh_vvv                                                           */
/*----------------------------------------------------------------------------*/

/* VSHRRH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vshrrh_vvv(short16, uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vshrrh_vvv(short32, uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshrrw_vkv                                                           */
/*----------------------------------------------------------------------------*/

/* VSHRRW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vshrrw_vkv(int8, uchar8/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vshrrw_vkv(int16, uchar16/*(k={0-63})*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshrrw_vvv                                                           */
/*----------------------------------------------------------------------------*/

/* VSHRRW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vshrrw_vvv(int8, uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vshrrw_vvv(int16, uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshru_vkv                                                            */
/*----------------------------------------------------------------------------*/

/* VSHRU */
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __vshru_vkv(ulong8, uint8_t/*(k={1-64})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __vshru_vkv(ulong4, uint8_t/*(k={1-64})*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshru_vvv                                                            */
/*----------------------------------------------------------------------------*/

/* VSHRU */
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __vshru_vvv(ulong4, ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __vshru_vvv(ulong8, ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshrub_vkv                                                           */
/*----------------------------------------------------------------------------*/

/* VSHRUB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vshrub_vkv(uchar32, uchar32/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vshrub_vkv(uchar64, uchar64/*(k={0-63})*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshrub_vvv                                                           */
/*----------------------------------------------------------------------------*/

/* VSHRUB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vshrub_vvv(uchar32, uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vshrub_vvv(uchar64, uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshrud_vkv                                                           */
/*----------------------------------------------------------------------------*/

/* VSHRUD */
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __vshrud_vkv(ulong4, ulong4/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __vshrud_vkv(ulong8, ulong8/*(k={0-63})*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshrud_vvv                                                           */
/*----------------------------------------------------------------------------*/

/* VSHRUD */
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __vshrud_vvv(ulong4, ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __vshrud_vvv(ulong8, ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshruh_vkv                                                           */
/*----------------------------------------------------------------------------*/

/* VSHRUH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vshruh_vkv(ushort16, ushort16/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vshruh_vkv(ushort32, ushort32/*(k={0-63})*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshruh_vvv                                                           */
/*----------------------------------------------------------------------------*/

/* VSHRUH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vshruh_vvv(ushort16, uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vshruh_vvv(ushort32, uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshrurb_vkv                                                          */
/*----------------------------------------------------------------------------*/

/* VSHRURB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vshrurb_vkv(uchar32, uchar32/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vshrurb_vkv(uchar64, uchar64/*(k={0-63})*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshrurb_vvv                                                          */
/*----------------------------------------------------------------------------*/

/* VSHRURB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vshrurb_vvv(uchar32, uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vshrurb_vvv(uchar64, uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshrurd_vkv                                                          */
/*----------------------------------------------------------------------------*/

/* VSHRURD */
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __vshrurd_vkv(ulong4, uchar4/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __vshrurd_vkv(ulong8, uchar8/*(k={0-63})*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshrurd_vvv                                                          */
/*----------------------------------------------------------------------------*/

/* VSHRURD */
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __vshrurd_vvv(ulong4, ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __vshrurd_vvv(ulong8, ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshrurh_vkv                                                          */
/*----------------------------------------------------------------------------*/

/* VSHRURH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vshrurh_vkv(ushort16, uchar16/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vshrurh_vkv(ushort32, uchar32/*(k={0-63})*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshrurh_vvv                                                          */
/*----------------------------------------------------------------------------*/

/* VSHRURH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vshrurh_vvv(ushort16, uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vshrurh_vvv(ushort32, uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshrurw_vkv                                                          */
/*----------------------------------------------------------------------------*/

/* VSHRURW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vshrurw_vkv(uint8, uchar8/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vshrurw_vkv(uint16, uchar16/*(k={0-63})*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshrurw_vvv                                                          */
/*----------------------------------------------------------------------------*/

/* VSHRURW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vshrurw_vvv(uint8, uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vshrurw_vvv(uint16, uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshruw_vkv                                                           */
/*----------------------------------------------------------------------------*/

/* VSHRUW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vshruw_vkv(uint8, uint8/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vshruw_vkv(uint16, uint16/*(k={0-63})*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshruw_vvv                                                           */
/*----------------------------------------------------------------------------*/

/* VSHRUW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vshruw_vvv(uint8, uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vshruw_vvv(uint16, uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshrw_vkv                                                            */
/*----------------------------------------------------------------------------*/

/* VSHRW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vshrw_vkv(int8, int8/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vshrw_vkv(int16, int16/*(k={0-63})*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshrw_vvv                                                            */
/*----------------------------------------------------------------------------*/

/* VSHRW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vshrw_vvv(int8, int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vshrw_vvv(int16, int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshvluw_vvv                                                          */
/*----------------------------------------------------------------------------*/

/* VSHVLUW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vshvluw_vvv(uint8, int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vshvluw_vvv(uint16, int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshvlw_vvv                                                           */
/*----------------------------------------------------------------------------*/

/* VSHVLW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vshvlw_vvv(int8, int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vshvlw_vvv(int16, int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshvruw_vvv                                                          */
/*----------------------------------------------------------------------------*/

/* VSHVRUW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vshvruw_vvv(uint8, int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vshvruw_vvv(uint16, int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vshvrw_vvv                                                           */
/*----------------------------------------------------------------------------*/

/* VSHVRW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vshvrw_vvv(int8, int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vshvrw_vvv(int16, int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsmpyhw_vvw                                                          */
/*----------------------------------------------------------------------------*/

/* VSMPYHW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern void __vsmpyhw_vvw(short16, short16, int8&, int8&);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern void __vsmpyhw_vvw(short32, short32, int16&, int16&);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsmpyr17ww_vvv                                                       */
/*----------------------------------------------------------------------------*/

/* VSMPYR17WW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vsmpyr17ww_vvv(int8, int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vsmpyr17ww_vvv(int16, int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsmpyr1hh_vvv                                                        */
/*----------------------------------------------------------------------------*/

/* VSMPYR1HH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vsmpyr1hh_vvv(short16, short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vsmpyr1hh_vvv(short32, short32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsmpyr1ww_vvv                                                        */
/*----------------------------------------------------------------------------*/

/* VSMPYR1WW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vsmpyr1ww_vvv(int8, int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vsmpyr1ww_vvv(int16, int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsmpyrsuhh_vvv                                                       */
/*----------------------------------------------------------------------------*/

/* VSMPYRSUHH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vsmpyrsuhh_vvv(short16, ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vsmpyrsuhh_vvv(short32, ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsmpyruhh_vvv                                                        */
/*----------------------------------------------------------------------------*/

/* VSMPYRUHH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vsmpyruhh_vvv(ushort16, ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vsmpyruhh_vvv(ushort32, ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsmpyww_vvv                                                          */
/*----------------------------------------------------------------------------*/

/* VSMPYWW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vsmpyww_vvv(int8, int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vsmpyww_vvv(int16, int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsortdh_vv                                                           */
/*----------------------------------------------------------------------------*/

/* VSORTDH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vsortdh_vv(short16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsortdsp_vv                                                          */
/*----------------------------------------------------------------------------*/

/* VSORTDSP */
#if __C7X_VEC_SIZE_BITS__ == 256
extern float8 __vsortdsp_vv(float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern float16 __vsortdsp_vv(float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsortduh_vv                                                          */
/*----------------------------------------------------------------------------*/

/* VSORTDUH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vsortduh_vv(ushort16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsortduw_vv                                                          */
/*----------------------------------------------------------------------------*/

/* VSORTDUW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vsortduw_vv(uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vsortduw_vv(uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsortdw_vv                                                           */
/*----------------------------------------------------------------------------*/

/* VSORTDW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vsortdw_vv(int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vsortdw_vv(int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsortih_vv                                                           */
/*----------------------------------------------------------------------------*/

/* VSORTIH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vsortih_vv(short16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsortisp_vv                                                          */
/*----------------------------------------------------------------------------*/

/* VSORTISP */
#if __C7X_VEC_SIZE_BITS__ == 256
extern float8 __vsortisp_vv(float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern float16 __vsortisp_vv(float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsortiuh_vv                                                          */
/*----------------------------------------------------------------------------*/

/* VSORTIUH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vsortiuh_vv(ushort16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsortiuw_vv                                                          */
/*----------------------------------------------------------------------------*/

/* VSORTIUW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vsortiuw_vv(uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vsortiuw_vv(uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsortiw_vv                                                           */
/*----------------------------------------------------------------------------*/

/* VSORTIW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vsortiw_vv(int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vsortiw_vv(int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsortpdsp_vv                                                         */
/*----------------------------------------------------------------------------*/

/* VSORTPDSP */
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vsortpdsp_vv(float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsortpduw_vv                                                         */
/*----------------------------------------------------------------------------*/

/* VSORTPDUW */
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vsortpduw_vv(uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsortpdw_vv                                                          */
/*----------------------------------------------------------------------------*/

/* VSORTPDW */
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vsortpdw_vv(int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsortpisp_vv                                                         */
/*----------------------------------------------------------------------------*/

/* VSORTPISP */
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vsortpisp_vv(float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsortpiuw_vv                                                         */
/*----------------------------------------------------------------------------*/

/* VSORTPIUW */
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vsortpiuw_vv(uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsortpiw_vv                                                          */
/*----------------------------------------------------------------------------*/

/* VSORTPIW */
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vsortpiw_vv(int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vspackdw_vvv                                                         */
/*----------------------------------------------------------------------------*/

/* VSPACKDW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vspackdw_vvv(long4, long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vspackdw_vvv(long8, long8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vspackhb_vvv                                                         */
/*----------------------------------------------------------------------------*/

/* VSPACKHB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __vspackhb_vvv(short16, short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __vspackhb_vvv(short32, short32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vspackudw_vvv                                                        */
/*----------------------------------------------------------------------------*/

/* VSPACKUDW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vspackudw_vvv(long4, long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vspackudw_vvv(long8, long8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vspackuhb_vvv                                                        */
/*----------------------------------------------------------------------------*/

/* VSPACKUHB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vspackuhb_vvv(short16, short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vspackuhb_vvv(short32, short32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vspackuwh_vvv                                                        */
/*----------------------------------------------------------------------------*/

/* VSPACKUWH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vspackuwh_vvv(int8, int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vspackuwh_vvv(int16, int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vspackwh_vvv                                                         */
/*----------------------------------------------------------------------------*/

/* VSPACKWH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vspackwh_vvv(int8, int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vspackwh_vvv(int16, int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vspdph_vv                                                            */
/*----------------------------------------------------------------------------*/

/* VSPDPH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern double4 __vspdph_vv(float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern double8 __vspdph_vv(float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vspdpl_vv                                                            */
/*----------------------------------------------------------------------------*/

/* VSPDPL */
#if __C7X_VEC_SIZE_BITS__ == 256
extern double4 __vspdpl_vv(float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern double8 __vspdpl_vv(float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsphp_vv                                                             */
/*----------------------------------------------------------------------------*/

/* VSPHP */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vsphp_vv(float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vsphp_vv(float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vspint_vv                                                            */
/*----------------------------------------------------------------------------*/

/* VSPINT */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vspint_vv(float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vspint_vv(float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vspinth_vv                                                           */
/*----------------------------------------------------------------------------*/

/* VSPINTH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vspinth_vv(float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vspinth_vv(float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vspinthpk_vv                                                         */
/*----------------------------------------------------------------------------*/

/* VSPINTHPK */
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vspinthpk_vv(float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vspinthpk_vv(float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsptrunc_vv                                                          */
/*----------------------------------------------------------------------------*/

/* VSPTRUNC */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vsptrunc_vv(float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vsptrunc_vv(float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsshlh_vkv                                                           */
/*----------------------------------------------------------------------------*/

/* VSSHLH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vsshlh_vkv(short16, uchar16/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vsshlh_vkv(short32, uchar32/*(k={0-63})*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsshlh_vvv                                                           */
/*----------------------------------------------------------------------------*/

/* VSSHLH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vsshlh_vvv(short16, uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vsshlh_vvv(short32, uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsshlrdw_vkv                                                         */
/*----------------------------------------------------------------------------*/

/* VSSHLRDW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vsshlrdw_vkv(long4, uchar4/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vsshlrdw_vkv(long8, uchar8/*(k={0-63})*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsshlrdw_vvv                                                         */
/*----------------------------------------------------------------------------*/

/* VSSHLRDW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vsshlrdw_vvv(long4, ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vsshlrdw_vvv(long8, ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsshlrhb_vkv                                                         */
/*----------------------------------------------------------------------------*/

/* VSSHLRHB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __vsshlrhb_vkv(short16, uchar8/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __vsshlrhb_vkv(short32, uchar16/*(k={0-63})*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsshlrhb_vvv                                                         */
/*----------------------------------------------------------------------------*/

/* VSSHLRHB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __vsshlrhb_vvv(short16, uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __vsshlrhb_vvv(short32, uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsshlrwh_vkv                                                         */
/*----------------------------------------------------------------------------*/

/* VSSHLRWH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vsshlrwh_vkv(int8, uchar8/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vsshlrwh_vkv(int16, uchar16/*(k={0-63})*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsshlrwh_vvv                                                         */
/*----------------------------------------------------------------------------*/

/* VSSHLRWH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vsshlrwh_vvv(int8, uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vsshlrwh_vvv(int16, uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsshlsuh_vkv                                                         */
/*----------------------------------------------------------------------------*/

/* VSSHLSUH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vsshlsuh_vkv(short16, uchar16/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vsshlsuh_vkv(short32, uchar32/*(k={0-63})*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsshlsuh_vvv                                                         */
/*----------------------------------------------------------------------------*/

/* VSSHLSUH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vsshlsuh_vvv(short16, uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vsshlsuh_vvv(short32, uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsshlsurdw_vkv                                                       */
/*----------------------------------------------------------------------------*/

/* VSSHLSURDW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vsshlsurdw_vkv(long4, uchar4/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vsshlsurdw_vkv(long8, uchar8/*(k={0-63})*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsshlsurdw_vvv                                                       */
/*----------------------------------------------------------------------------*/

/* VSSHLSURDW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vsshlsurdw_vvv(long4, ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vsshlsurdw_vvv(long8, ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsshlsurhb_vkv                                                       */
/*----------------------------------------------------------------------------*/

/* VSSHLSURHB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vsshlsurhb_vkv(short16, uchar8/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vsshlsurhb_vkv(short32, uchar16/*(k={0-63})*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsshlsurhb_vvv                                                       */
/*----------------------------------------------------------------------------*/

/* VSSHLSURHB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vsshlsurhb_vvv(short16, uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vsshlsurhb_vvv(short32, uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsshlsurwh_vkv                                                       */
/*----------------------------------------------------------------------------*/

/* VSSHLSURWH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vsshlsurwh_vkv(int8, uchar8/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vsshlsurwh_vkv(int16, uchar16/*(k={0-63})*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsshlsurwh_vvv                                                       */
/*----------------------------------------------------------------------------*/

/* VSSHLSURWH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vsshlsurwh_vvv(int8, uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vsshlsurwh_vvv(int16, uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsshlsuw_vkv                                                         */
/*----------------------------------------------------------------------------*/

/* VSSHLSUW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vsshlsuw_vkv(int8, uchar8/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vsshlsuw_vkv(int16, uchar16/*(k={0-63})*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsshlsuw_vvv                                                         */
/*----------------------------------------------------------------------------*/

/* VSSHLSUW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vsshlsuw_vvv(int8, uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vsshlsuw_vvv(int16, uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsshluh_vkv                                                          */
/*----------------------------------------------------------------------------*/

/* VSSHLUH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vsshluh_vkv(ushort16, uchar16/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vsshluh_vkv(ushort32, uchar32/*(k={0-63})*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsshluh_vvv                                                          */
/*----------------------------------------------------------------------------*/

/* VSSHLUH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vsshluh_vvv(ushort16, uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vsshluh_vvv(ushort32, uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsshlurdw_vkv                                                        */
/*----------------------------------------------------------------------------*/

/* VSSHLURDW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vsshlurdw_vkv(ulong4, uchar4/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vsshlurdw_vkv(ulong8, uchar8/*(k={0-63})*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsshlurdw_vvv                                                        */
/*----------------------------------------------------------------------------*/

/* VSSHLURDW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vsshlurdw_vvv(ulong4, ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vsshlurdw_vvv(ulong8, ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsshlurhb_vkv                                                        */
/*----------------------------------------------------------------------------*/

/* VSSHLURHB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vsshlurhb_vkv(ushort16, uchar8/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vsshlurhb_vkv(ushort32, uchar16/*(k={0-63})*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsshlurhb_vvv                                                        */
/*----------------------------------------------------------------------------*/

/* VSSHLURHB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vsshlurhb_vvv(ushort16, uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vsshlurhb_vvv(ushort32, uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsshlurwh_vkv                                                        */
/*----------------------------------------------------------------------------*/

/* VSSHLURWH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vsshlurwh_vkv(uint8, uchar8/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vsshlurwh_vkv(uint16, uchar16/*(k={0-63})*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsshlurwh_vvv                                                        */
/*----------------------------------------------------------------------------*/

/* VSSHLURWH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vsshlurwh_vvv(uint8, uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vsshlurwh_vvv(uint16, uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsshluw_vkv                                                          */
/*----------------------------------------------------------------------------*/

/* VSSHLUW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vsshluw_vkv(uint8, uchar8/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vsshluw_vkv(uint16, uchar16/*(k={0-63})*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsshluw_vvv                                                          */
/*----------------------------------------------------------------------------*/

/* VSSHLUW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vsshluw_vvv(uint8, uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vsshluw_vvv(uint16, uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsshlw_vkv                                                           */
/*----------------------------------------------------------------------------*/

/* VSSHLW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vsshlw_vkv(int8, uchar8/*(k={0-63})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vsshlw_vkv(int16, uchar16/*(k={0-63})*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsshlw_vvv                                                           */
/*----------------------------------------------------------------------------*/

/* VSSHLW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vsshlw_vvv(int8, uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vsshlw_vvv(int16, uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsshvlw_vvv                                                          */
/*----------------------------------------------------------------------------*/

/* VSSHVLW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vsshvlw_vvv(int8, int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vsshvlw_vvv(int16, int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsshvrw_vvv                                                          */
/*----------------------------------------------------------------------------*/

/* VSSHVRW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vsshvrw_vvv(int8, int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vsshvrw_vvv(int16, int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vssubb_vkv                                                           */
/*----------------------------------------------------------------------------*/

/* VSSUBB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __vssubb_vkv(char32, char32/*(k)*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __vssubb_vkv(char64, char64/*(k)*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vssubb_vvv                                                           */
/*----------------------------------------------------------------------------*/

/* VSSUBB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __vssubb_vvv(char32, char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __vssubb_vvv(char64, char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cchar16 __vssubb_vvv(cchar16, cchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cchar32 __vssubb_vvv(cchar32, cchar32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vssubh_vkv                                                           */
/*----------------------------------------------------------------------------*/

/* VSSUBH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vssubh_vkv(short16, short16/*(k)*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vssubh_vkv(short32, short32/*(k)*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vssubh_vvv                                                           */
/*----------------------------------------------------------------------------*/

/* VSSUBH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vssubh_vvv(short16, short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vssubh_vvv(short32, short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cshort8 __vssubh_vvv(cshort8, cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cshort16 __vssubh_vvv(cshort16, cshort16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vssubw_vkv                                                           */
/*----------------------------------------------------------------------------*/

/* VSSUBW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vssubw_vkv(int8, int8/*(k)*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vssubw_vkv(int16, int16/*(k)*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vssubw_vvv                                                           */
/*----------------------------------------------------------------------------*/

/* VSSUBW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vssubw_vvv(int8, int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vssubw_vvv(int16, int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cint4 __vssubw_vvv(cint4, cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cint8 __vssubw_vvv(cint8, cint8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsubabsb_vvv                                                         */
/*----------------------------------------------------------------------------*/

/* VSUBABSB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vsubabsb_vvv(uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vsubabsb_vvv(uchar64, uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsubabsd_vvv                                                         */
/*----------------------------------------------------------------------------*/

/* VSUBABSD */
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __vsubabsd_vvv(ulong4, ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __vsubabsd_vvv(ulong8, ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsubabsh_vvv                                                         */
/*----------------------------------------------------------------------------*/

/* VSUBABSH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vsubabsh_vvv(ushort16, ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vsubabsh_vvv(ushort32, ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsubabsw_vvv                                                         */
/*----------------------------------------------------------------------------*/

/* VSUBABSW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vsubabsw_vvv(uint8, uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vsubabsw_vvv(uint16, uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsubb_vkv                                                            */
/*----------------------------------------------------------------------------*/

/* VSUBB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __vsubb_vkv(char32, char32/*(k)*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __vsubb_vkv(char64, char64/*(k)*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vsubb_vkv(uchar32, uchar32/*(k)*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vsubb_vkv(uchar64, uchar64/*(k)*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsubb_vvv                                                            */
/*----------------------------------------------------------------------------*/

/* VSUBB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __vsubb_vvv(char32, char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __vsubb_vvv(char64, char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vsubb_vvv(uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vsubb_vvv(uchar64, uchar64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cchar16 __vsubb_vvv(cchar16, cchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cchar32 __vsubb_vvv(cchar32, cchar32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsubcw_vvv                                                           */
/*----------------------------------------------------------------------------*/

/* VSUBCW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vsubcw_vvv(uint8, uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vsubcw_vvv(uint16, uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsubd_vkv                                                            */
/*----------------------------------------------------------------------------*/

/* VSUBD */
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __vsubd_vkv(long4, int4/*(k)*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __vsubd_vkv(long8, int8/*(k)*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __vsubd_vkv(ulong4, uint4/*(k={0-2147483647})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __vsubd_vkv(ulong8, uint8/*(k={0-2147483647})*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsubd_vvv                                                            */
/*----------------------------------------------------------------------------*/

/* VSUBD */
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __vsubd_vvv(long4, long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __vsubd_vvv(long8, long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __vsubd_vvv(ulong4, ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __vsubd_vvv(ulong8, ulong8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern clong2 __vsubd_vvv(clong2, clong2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern clong4 __vsubd_vvv(clong4, clong4);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsubdp_vvv                                                           */
/*----------------------------------------------------------------------------*/

/* VSUBDP */
#if __C7X_VEC_SIZE_BITS__ == 256
extern double4 __vsubdp_vvv(double4, double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern double8 __vsubdp_vvv(double8, double8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cdouble2 __vsubdp_vvv(cdouble2, cdouble2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cdouble4 __vsubdp_vvv(cdouble4, cdouble4);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsubh_vkv                                                            */
/*----------------------------------------------------------------------------*/

/* VSUBH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vsubh_vkv(short16, short16/*(k)*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vsubh_vkv(short32, short32/*(k)*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vsubh_vkv(ushort16, ushort16/*(k)*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vsubh_vkv(ushort32, ushort32/*(k)*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsubh_vvv                                                            */
/*----------------------------------------------------------------------------*/

/* VSUBH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vsubh_vvv(short16, short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vsubh_vvv(short32, short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vsubh_vvv(ushort16, ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vsubh_vvv(ushort32, ushort32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cshort8 __vsubh_vvv(cshort8, cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cshort16 __vsubh_vvv(cshort16, cshort16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsubrb_vkv                                                           */
/*----------------------------------------------------------------------------*/

/* VSUBRB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __vsubrb_vkv(char32, char32/*(k)*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __vsubrb_vkv(char64, char64/*(k)*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vsubrb_vkv(uchar32, uchar32/*(k)*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vsubrb_vkv(uchar64, uchar64/*(k)*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsubrb_vvv                                                           */
/*----------------------------------------------------------------------------*/

/* VSUBRB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __vsubrb_vvv(char32, char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __vsubrb_vvv(char64, char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vsubrb_vvv(uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vsubrb_vvv(uchar64, uchar64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cchar16 __vsubrb_vvv(cchar16, cchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cchar32 __vsubrb_vvv(cchar32, cchar32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsubrd_vkv                                                           */
/*----------------------------------------------------------------------------*/

/* VSUBRD */
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __vsubrd_vkv(long4, int4/*(k)*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __vsubrd_vkv(long8, int8/*(k)*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __vsubrd_vkv(ulong4, uint4/*(k={0-2147483647})*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __vsubrd_vkv(ulong8, uint8/*(k={0-2147483647})*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsubrd_vvv                                                           */
/*----------------------------------------------------------------------------*/

/* VSUBRD */
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __vsubrd_vvv(long4, long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __vsubrd_vvv(long8, long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __vsubrd_vvv(ulong4, ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __vsubrd_vvv(ulong8, ulong8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern clong2 __vsubrd_vvv(clong2, clong2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern clong4 __vsubrd_vvv(clong4, clong4);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsubrh_vkv                                                           */
/*----------------------------------------------------------------------------*/

/* VSUBRH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vsubrh_vkv(short16, short16/*(k)*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vsubrh_vkv(short32, short32/*(k)*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vsubrh_vkv(ushort16, ushort16/*(k)*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vsubrh_vkv(ushort32, ushort32/*(k)*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsubrh_vvv                                                           */
/*----------------------------------------------------------------------------*/

/* VSUBRH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vsubrh_vvv(short16, short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vsubrh_vvv(short32, short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vsubrh_vvv(ushort16, ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vsubrh_vvv(ushort32, ushort32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cshort8 __vsubrh_vvv(cshort8, cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cshort16 __vsubrh_vvv(cshort16, cshort16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsubrw_vkv                                                           */
/*----------------------------------------------------------------------------*/

/* VSUBRW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vsubrw_vkv(int8, int8/*(k)*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vsubrw_vkv(int16, int16/*(k)*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vsubrw_vkv(uint8, uint8/*(k)*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vsubrw_vkv(uint16, uint16/*(k)*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsubrw_vvv                                                           */
/*----------------------------------------------------------------------------*/

/* VSUBRW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vsubrw_vvv(int8, int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vsubrw_vvv(int16, int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vsubrw_vvv(uint8, uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vsubrw_vvv(uint16, uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cint4 __vsubrw_vvv(cint4, cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cint8 __vsubrw_vvv(cint8, cint8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsubsp_vvv                                                           */
/*----------------------------------------------------------------------------*/

/* VSUBSP */
#if __C7X_VEC_SIZE_BITS__ == 256
extern float8 __vsubsp_vvv(float8, float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern float16 __vsubsp_vvv(float16, float16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cfloat4 __vsubsp_vvv(cfloat4, cfloat4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cfloat8 __vsubsp_vvv(cfloat8, cfloat8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsubw_vkv                                                            */
/*----------------------------------------------------------------------------*/

/* VSUBW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vsubw_vkv(int8, int8/*(k)*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vsubw_vkv(int16, int16/*(k)*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vsubw_vkv(uint8, uint8/*(k)*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vsubw_vkv(uint16, uint16/*(k)*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vsubw_vvv                                                            */
/*----------------------------------------------------------------------------*/

/* VSUBW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vsubw_vvv(int8, int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vsubw_vvv(int16, int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vsubw_vvv(uint8, uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vsubw_vvv(uint16, uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cint4 __vsubw_vvv(cint4, cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cint8 __vsubw_vvv(cint8, cint8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vswapb_vv                                                            */
/*----------------------------------------------------------------------------*/

/* VSWAPB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __vswapb_vv(char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __vswapb_vv(char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vswapb_vv(uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vswapb_vv(uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vswapd_vv                                                            */
/*----------------------------------------------------------------------------*/

/* VSWAPD */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cint4 __vswapd_vv(cint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cint8 __vswapd_vv(cint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern cfloat4 __vswapd_vv(cfloat4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cfloat8 __vswapd_vv(cfloat8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __vswapd_vv(long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __vswapd_vv(long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __vswapd_vv(ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __vswapd_vv(ulong8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern double4 __vswapd_vv(double4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern double8 __vswapd_vv(double8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vswaph_vv                                                            */
/*----------------------------------------------------------------------------*/

/* VSWAPH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cchar16 __vswaph_vv(cchar16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cchar32 __vswaph_vv(cchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vswaph_vv(short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vswaph_vv(short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vswaph_vv(ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vswaph_vv(ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vswapw_vv                                                            */
/*----------------------------------------------------------------------------*/

/* VSWAPW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cshort8 __vswapw_vv(cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cshort16 __vswapw_vv(cshort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vswapw_vv(int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vswapw_vv(int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vswapw_vv(uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vswapw_vv(uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern float8 __vswapw_vv(float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern float16 __vswapw_vv(float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vunpkhb_vv                                                           */
/*----------------------------------------------------------------------------*/

/* VUNPKHB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vunpkhb_vv(char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vunpkhb_vv(char64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vunpkhh_vv                                                           */
/*----------------------------------------------------------------------------*/

/* VUNPKHH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vunpkhh_vv(short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vunpkhh_vv(short32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vunpkhub_vv                                                          */
/*----------------------------------------------------------------------------*/

/* VUNPKHUB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vunpkhub_vv(uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vunpkhub_vv(uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vunpkhuh_vv                                                          */
/*----------------------------------------------------------------------------*/

/* VUNPKHUH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vunpkhuh_vv(ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vunpkhuh_vv(ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vunpklb_vv                                                           */
/*----------------------------------------------------------------------------*/

/* VUNPKLB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vunpklb_vv(char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vunpklb_vv(char64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vunpklh_vv                                                           */
/*----------------------------------------------------------------------------*/

/* VUNPKLH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vunpklh_vv(short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vunpklh_vv(short32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vunpklub_vv                                                          */
/*----------------------------------------------------------------------------*/

/* VUNPKLUB */
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vunpklub_vv(uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vunpklub_vv(uchar64);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vunpkluh_vv                                                          */
/*----------------------------------------------------------------------------*/

/* VUNPKLUH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vunpkluh_vv(ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vunpkluh_vv(ushort32);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vunpkluw_vv                                                          */
/*----------------------------------------------------------------------------*/

/* VUNPKLUW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __vunpkluw_vv(uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __vunpkluw_vv(uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vunpklw_vv                                                           */
/*----------------------------------------------------------------------------*/

/* VUNPKLW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __vunpklw_vv(int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __vunpklw_vv(int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vwpackh_vvv                                                          */
/*----------------------------------------------------------------------------*/

/* VWPACKH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cshort8 __vwpackh_vvv(cshort8, cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cshort16 __vwpackh_vvv(cshort16, cshort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vwpackh_vvv(int8, int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vwpackh_vvv(int16, int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vwpackh_vvv(uint8, uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vwpackh_vvv(uint16, uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern float8 __vwpackh_vvv(float8, float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern float16 __vwpackh_vvv(float16, float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vwpackl_vvv                                                          */
/*----------------------------------------------------------------------------*/

/* VWPACKL */
#if __C7X_VEC_SIZE_BITS__ == 256
extern cshort8 __vwpackl_vvv(cshort8, cshort8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern cshort16 __vwpackl_vvv(cshort16, cshort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vwpackl_vvv(int8, int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vwpackl_vvv(int16, int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vwpackl_vvv(uint8, uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vwpackl_vvv(uint16, uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern float8 __vwpackl_vvv(float8, float8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern float16 __vwpackl_vvv(float16, float16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vwunpkd_vv                                                           */
/*----------------------------------------------------------------------------*/

/* VWUNPKD */
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __vwunpkd_vv(int4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __vwunpkd_vv(int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern clong2 __vwunpkd_vv(cint2);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern clong4 __vwunpkd_vv(cint4);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vwunpkdh_vv                                                          */
/*----------------------------------------------------------------------------*/

/* VWUNPKDH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __vwunpkdh_vv(int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __vwunpkdh_vv(int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vwunpkdl_vv                                                          */
/*----------------------------------------------------------------------------*/

/* VWUNPKDL */
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __vwunpkdl_vv(int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __vwunpkdl_vv(int16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vwunpkdu_vv                                                          */
/*----------------------------------------------------------------------------*/

/* VWUNPKDU */
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __vwunpkdu_vv(uint4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __vwunpkdu_vv(uint8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vwunpkudh_vv                                                         */
/*----------------------------------------------------------------------------*/

/* VWUNPKUDH */
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __vwunpkudh_vv(uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __vwunpkudh_vv(uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vwunpkudl_vv                                                         */
/*----------------------------------------------------------------------------*/

/* VWUNPKUDL */
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __vwunpkudl_vv(uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __vwunpkudl_vv(uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vxnorw_vvv                                                           */
/*----------------------------------------------------------------------------*/

/* VXNORW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __vxnorw_vvv(char32, char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __vxnorw_vvv(char64, char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vxnorw_vvv(uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vxnorw_vvv(uchar64, uchar64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vxnorw_vvv(short16, short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vxnorw_vvv(short32, short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vxnorw_vvv(ushort16, ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vxnorw_vvv(ushort32, ushort32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vxnorw_vvv(int8, int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vxnorw_vvv(int16, int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vxnorw_vvv(uint8, uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vxnorw_vvv(uint16, uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __vxnorw_vvv(long4, long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __vxnorw_vvv(long8, long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __vxnorw_vvv(ulong4, ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __vxnorw_vvv(ulong8, ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vxormpyw_vvv                                                         */
/*----------------------------------------------------------------------------*/

/* VXORMPYW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vxormpyw_vvv(uint8, uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vxormpyw_vvv(uint16, uint16);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vxorw_vkv                                                            */
/*----------------------------------------------------------------------------*/

/* VXORW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vxorw_vkv(int8, int8/*(k)*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vxorw_vkv(int16, int16/*(k)*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vxorw_vkv(uint8, uint8/*(k)*/);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vxorw_vkv(uint16, uint16/*(k)*/);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __vxorw_vvv                                                            */
/*----------------------------------------------------------------------------*/

/* VXORW */
#if __C7X_VEC_SIZE_BITS__ == 256
extern char32 __vxorw_vvv(char32, char32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern char64 __vxorw_vvv(char64, char64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uchar32 __vxorw_vvv(uchar32, uchar32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uchar64 __vxorw_vvv(uchar64, uchar64);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern short16 __vxorw_vvv(short16, short16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern short32 __vxorw_vvv(short32, short32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ushort16 __vxorw_vvv(ushort16, ushort16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ushort32 __vxorw_vvv(ushort32, ushort32);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern int8 __vxorw_vvv(int8, int8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern int16 __vxorw_vvv(int16, int16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern uint8 __vxorw_vvv(uint8, uint8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern uint16 __vxorw_vvv(uint16, uint16);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern long4 __vxorw_vvv(long4, long4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern long8 __vxorw_vvv(long8, long8);
#endif
#if __C7X_VEC_SIZE_BITS__ == 256
extern ulong4 __vxorw_vvv(ulong4, ulong4);
#endif
#if __C7X_VEC_SIZE_BITS__ == 512
extern ulong8 __vxorw_vvv(ulong8, ulong8);
#endif

/*----------------------------------------------------------------------------*/
/* ID: __xnor_ppp                                                             */
/*----------------------------------------------------------------------------*/

/* XNOR */
extern __vpred __xnor_ppp(__vpred, __vpred);

/*----------------------------------------------------------------------------*/
/* ID: __xnord_ddd                                                            */
/*----------------------------------------------------------------------------*/

/* XNORD */
extern char8 __xnord_ddd(char8, char8);
extern uchar8 __xnord_ddd(uchar8, uchar8);
extern short4 __xnord_ddd(short4, short4);
extern ushort4 __xnord_ddd(ushort4, ushort4);
extern int2 __xnord_ddd(int2, int2);
extern uint2 __xnord_ddd(uint2, uint2);
extern int64_t __xnord_ddd(int64_t, int64_t);
extern uint64_t __xnord_ddd(uint64_t, uint64_t);

/*----------------------------------------------------------------------------*/
/* ID: __xnord_dkd                                                            */
/*----------------------------------------------------------------------------*/

/* XNORD */
extern int64_t __xnord_dkd(int64_t, int32_t/*(k)*/);
extern uint64_t __xnord_dkd(uint64_t, uint32_t/*(k={0-2147483647})*/);

/*----------------------------------------------------------------------------*/
/* ID: __xnorw_rrr                                                            */
/*----------------------------------------------------------------------------*/

/* XNORW */
extern char4 __xnorw_rrr(char4, char4);
extern uchar4 __xnorw_rrr(uchar4, uchar4);
extern short2 __xnorw_rrr(short2, short2);
extern ushort2 __xnorw_rrr(ushort2, ushort2);
extern int32_t __xnorw_rrr(int32_t, int32_t);
extern uint32_t __xnorw_rrr(uint32_t, uint32_t);

/*----------------------------------------------------------------------------*/
/* ID: __xor_ppp                                                              */
/*----------------------------------------------------------------------------*/

/* XOR */
extern __vpred __xor_ppp(__vpred, __vpred);

/*----------------------------------------------------------------------------*/
/* ID: __xord_ddd                                                             */
/*----------------------------------------------------------------------------*/

/* XORD */
extern char8 __xord_ddd(char8, char8);
extern uchar8 __xord_ddd(uchar8, uchar8);
extern short4 __xord_ddd(short4, short4);
extern ushort4 __xord_ddd(ushort4, ushort4);
extern int2 __xord_ddd(int2, int2);
extern uint2 __xord_ddd(uint2, uint2);
extern int64_t __xord_ddd(int64_t, int64_t);
extern uint64_t __xord_ddd(uint64_t, uint64_t);

/*----------------------------------------------------------------------------*/
/* ID: __xord_dkd                                                             */
/*----------------------------------------------------------------------------*/

/* XORD */
extern int64_t __xord_dkd(int64_t, int32_t/*(k)*/);
extern uint64_t __xord_dkd(uint64_t, uint32_t/*(k={0-2147483647})*/);

/*----------------------------------------------------------------------------*/
/* ID: __xorw_rkr                                                             */
/*----------------------------------------------------------------------------*/

/* XORW */
extern char4 __xorw_rkr(char4, char4/*(k)*/);
extern uchar4 __xorw_rkr(uchar4, uchar4/*(k)*/);
extern short2 __xorw_rkr(short2, short2/*(k)*/);
extern ushort2 __xorw_rkr(ushort2, ushort2/*(k)*/);
extern int32_t __xorw_rkr(int32_t, int32_t/*(k)*/);
extern uint32_t __xorw_rkr(uint32_t, uint32_t/*(k)*/);

/*----------------------------------------------------------------------------*/
/* ID: __xorw_rrr                                                             */
/*----------------------------------------------------------------------------*/

/* XORW */
extern char4 __xorw_rrr(char4, char4);
extern uchar4 __xorw_rrr(uchar4, uchar4);
extern short2 __xorw_rrr(short2, short2);
extern ushort2 __xorw_rrr(ushort2, ushort2);
extern int32_t __xorw_rrr(int32_t, int32_t);
extern uint32_t __xorw_rrr(uint32_t, uint32_t);

/*----------------------------------------------------------------------------*/
/* ID: __xpnd4h_rd                                                            */
/*----------------------------------------------------------------------------*/

/* XPND4H */
extern short4 __xpnd4h_rd(int8_t);
extern ushort4 __xpnd4h_rd(uint8_t);

/*----------------------------------------------------------------------------*/
/* ID: __xpnd8b_rd                                                            */
/*----------------------------------------------------------------------------*/

/* XPND8B */
extern char8 __xpnd8b_rd(int8_t);
extern uchar8 __xpnd8b_rd(uint8_t);

/* AUTOGEN MARKER */

#endif /* C7X_DIRECT_H */
