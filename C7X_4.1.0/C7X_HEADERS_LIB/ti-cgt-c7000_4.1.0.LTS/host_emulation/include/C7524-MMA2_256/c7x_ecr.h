/*****************************************************************************/
/* C7X_ECR.H                                                                 */
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

#ifndef C7X_H_INCLUDE
#error "This file can only be included by parent header c7x.h"
#endif

#ifndef C7X_ECR_H_
#define C7X_ECR_H_

/*****************************************************************************/
/* The following is a list of extended control register available on C7000.  */
/* NOTE: Some reset values may not be exact depending on external factors    */
/*       such as silicon version and configuration.                          */
/*                                                                           */
/* The extended control registers may be read and written through normal     */
/* assignments where permissions allow. To read or write a specific index    */
/* of an extended control register, use the following APIs:                  */
/*                                                                           */
/*   unsigned long __get_indexed(__ECR_NAME, unsigned int index);            */
/*   void __set_indexed(__ECR_NAME, unsigned int index, unsigned long val);  */
/*                                                                           */
/*****************************************************************************/

#include <ti_he_impl/control_reg.h>


extern _c70_he_detail::control_reg<1,1,0,0xFFFFFFFF,0x0> __ECR0;
/******************************************************************************/
/* ECR: DBG_CAP                                                               */
/* DESCRIPTION: DEVICE CAPABILITY Register                                    */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0xDEC00440                                            */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/*     Secure Supervisor: RO                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RO                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RO                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
#define __ECR_DBG_CAP __ECR0


extern _c70_he_detail::control_reg<1,1,0,0xFFFFFFFF,0x0> __ECR1;
/******************************************************************************/
/* ECR: DBG_PID                                                               */
/* DESCRIPTION: DEVICE PID Register                                           */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x62020400                                            */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/*     Secure Supervisor: RO                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RO                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RO                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
#define __ECR_DBG_PID __ECR1

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3;

extern _c70_he_detail::control_reg<1,1,1,0xBDFFFFFD,0x42003FFF> __ECR4;
/******************************************************************************/
/* ECR: DBG_CNTL                                                              */
/* DESCRIPTION: Debug control Register                                        */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x200                                                 */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_DBG_CNTL __ECR4


extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFF,0x38A00034> __ECR5;
/******************************************************************************/
/* ECR: DBG_STAT                                                              */
/* DESCRIPTION: Debug Status Register                                         */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_DBG_STAT __ECR5


extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFF,0x1> __ECR6;
/******************************************************************************/
/* ECR: DBG_OWN                                                               */
/* DESCRIPTION: Ownership Control and Status Register                         */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_DBG_OWN __ECR6

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR7;

extern _c70_he_detail::control_reg<1,1,0,0xFFFFFFFF,0x0> __ECR8;
/******************************************************************************/
/* ECR: DBG_INDRCT_CAP0                                                       */
/* DESCRIPTION: Indirect Access Port Capabilities Register for pages 0-3      */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x121212                                              */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/*     Secure Supervisor: RO                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RO                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RO                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
#define __ECR_DBG_INDRCT_CAP0 __ECR8


extern _c70_he_detail::control_reg<1,1,0,0xFFFFFFFF,0x0> __ECR9;
/******************************************************************************/
/* ECR: DBG_INDRCT_CAP1                                                       */
/* DESCRIPTION: Indirect Access Port Capabilities Register for pages 4-7      */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/*     Secure Supervisor: RO                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RO                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RO                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
#define __ECR_DBG_INDRCT_CAP1 __ECR9

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR10;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR11;

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFF,0xC000F77F> __ECR12;
/******************************************************************************/
/* ECR: DBG_INDRCT_CNTL                                                       */
/* DESCRIPTION: Indirect Memory Control and Status register                   */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x40080000                                            */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_DBG_INDRCT_CNTL __ECR12


extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFF,0xFFFFFFFF> __ECR13;
/******************************************************************************/
/* ECR: DBG_INDRCT_CTXT0                                                      */
/* DESCRIPTION: Indirect Memory Context ID Register 0                         */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_DBG_INDRCT_CTXT0 __ECR13


extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFF,0xFFFFFFFF> __ECR14;
/******************************************************************************/
/* ECR: DBG_INDRCT_CTXT1                                                      */
/* DESCRIPTION: Indirect Memory Context ID Register 1                         */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_DBG_INDRCT_CTXT1 __ECR14


extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFF,0x3FFF> __ECR15;
/******************************************************************************/
/* ECR: DBG_INDRCT_CTXT2                                                      */
/* DESCRIPTION: Indirect Memory Context ID Register 2                         */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_DBG_INDRCT_CTXT2 __ECR15


extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFF,0xFFFFFFFF> __ECR16;
/******************************************************************************/
/* ECR: DBG_INDRCT_ADDR0                                                      */
/* DESCRIPTION: Indirect Memory Address Register 0                            */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_DBG_INDRCT_ADDR0 __ECR16


extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFF,0xFFFFFFFF> __ECR17;
/******************************************************************************/
/* ECR: DBG_INDRCT_ADDR1                                                      */
/* DESCRIPTION: Indirect Memory Address Register 1                            */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_DBG_INDRCT_ADDR1 __ECR17


extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFF,0xFFFFFFFF> __ECR18;
/******************************************************************************/
/* ECR: DBG_INDRCT_DATA0                                                      */
/* DESCRIPTION: Indirect Memory Data Register 0                               */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_DBG_INDRCT_DATA0 __ECR18


extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFF,0xFFFFFFFF> __ECR19;
/******************************************************************************/
/* ECR: DBG_INDRCT_DATA1                                                      */
/* DESCRIPTION: Indirect Memory Data Register 1                               */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_DBG_INDRCT_DATA1 __ECR19

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR20;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR21;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR22;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR23;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR24;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR25;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR26;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR27;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR28;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR29;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR30;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR31;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR32;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR33;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR34;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR35;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR36;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR37;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR38;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR39;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR40;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR41;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR42;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR43;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR44;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR45;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR46;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR47;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR48;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR49;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR50;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR51;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR52;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR53;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR54;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR55;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR56;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR57;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR58;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR59;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR60;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR61;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR62;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR63;

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFF,0xFFFFF1EF> __ECR64;
/******************************************************************************/
/* ECR: DBG_HWBP_0_CNTL                                                       */
/* DESCRIPTION: HWBP_0 Control and Status Register                            */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x800                                                 */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_DBG_HWBP_0_CNTL __ECR64

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR65;

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFF,0xFFFFFFFF> __ECR66;
/******************************************************************************/
/* ECR: DBG_HWBP_0_CTXT0                                                      */
/* DESCRIPTION: HWBP_0 Context ID register 0                                  */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_DBG_HWBP_0_CTXT0 __ECR66


extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFF,0xFFFFFFFF> __ECR67;
/******************************************************************************/
/* ECR: DBG_HWBP_0_CTXT1                                                      */
/* DESCRIPTION: HWBP_0 Context ID register 1                                  */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_DBG_HWBP_0_CTXT1 __ECR67


extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFF,0x3FFF> __ECR68;
/******************************************************************************/
/* ECR: DBG_HWBP_0_CTXT2                                                      */
/* DESCRIPTION: HWBP_0 Context ID register 2                                  */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_DBG_HWBP_0_CTXT2 __ECR68

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR69;

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFF,0xFFFFFFFC> __ECR70;
/******************************************************************************/
/* ECR: DBG_HWBP_0_ADDR0                                                      */
/* DESCRIPTION: HWBP_0 Address Register 0                                     */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_DBG_HWBP_0_ADDR0 __ECR70


extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFF,0xFFFFFFFF> __ECR71;
/******************************************************************************/
/* ECR: DBG_HWBP_0_ADDR1                                                      */
/* DESCRIPTION: HWBP_0 Address Register 1                                     */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_DBG_HWBP_0_ADDR1 __ECR71


extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFF,0xFFFFFFFC> __ECR72;
/******************************************************************************/
/* ECR: DBG_HWBP_0_AMASK0                                                     */
/* DESCRIPTION: HWBP_0 Address Mask Register 0                                */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0xFFFFFFFC                                            */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_DBG_HWBP_0_AMASK0 __ECR72


extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFF,0xFFFFFFFF> __ECR73;
/******************************************************************************/
/* ECR: DBG_HWBP_0_AMASK1                                                     */
/* DESCRIPTION: HWBP_0 Address Mask Register 1                                */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0xFFFFFFFF                                            */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_DBG_HWBP_0_AMASK1 __ECR73

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR74;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR75;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR76;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR77;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR78;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR79;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR80;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR81;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR82;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR83;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR84;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR85;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR86;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR87;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR88;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR89;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR90;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR91;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR92;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR93;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR94;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR95;

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFF,0xFFFFF1EF> __ECR96;
/******************************************************************************/
/* ECR: DBG_HWBP_1_CNTL                                                       */
/* DESCRIPTION: HWBP_1 Control and Status Register                            */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x800                                                 */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_DBG_HWBP_1_CNTL __ECR96

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR97;

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFF,0xFFFFFFFF> __ECR98;
/******************************************************************************/
/* ECR: DBG_HWBP_1_CTXT0                                                      */
/* DESCRIPTION: HWBP_1 Context ID register 0                                  */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_DBG_HWBP_1_CTXT0 __ECR98


extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFF,0xFFFFFFFF> __ECR99;
/******************************************************************************/
/* ECR: DBG_HWBP_1_CTXT1                                                      */
/* DESCRIPTION: HWBP_1 Context ID register 1                                  */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_DBG_HWBP_1_CTXT1 __ECR99


extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFF,0x3FFF> __ECR100;
/******************************************************************************/
/* ECR: DBG_HWBP_1_CTXT2                                                      */
/* DESCRIPTION: HWBP_1 Context ID register 2                                  */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_DBG_HWBP_1_CTXT2 __ECR100

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR101;

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFF,0xFFFFFFFC> __ECR102;
/******************************************************************************/
/* ECR: DBG_HWBP_1_ADDR0                                                      */
/* DESCRIPTION: HWBP_1 Address Register 0                                     */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_DBG_HWBP_1_ADDR0 __ECR102


extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFF,0xFFFFFFFF> __ECR103;
/******************************************************************************/
/* ECR: DBG_HWBP_1_ADDR1                                                      */
/* DESCRIPTION: HWBP_1 Address Register 1                                     */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_DBG_HWBP_1_ADDR1 __ECR103


extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFF,0xFFFFFFFC> __ECR104;
/******************************************************************************/
/* ECR: DBG_HWBP_1_AMASK0                                                     */
/* DESCRIPTION: HWBP_1 Address Mask Register 0                                */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0xFFFFFFFC                                            */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_DBG_HWBP_1_AMASK0 __ECR104


extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFF,0xFFFFFFFF> __ECR105;
/******************************************************************************/
/* ECR: DBG_HWBP_1_AMASK1                                                     */
/* DESCRIPTION: HWBP_1 Address Mask Register 1                                */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0xFFFFFFFF                                            */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_DBG_HWBP_1_AMASK1 __ECR105

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR106;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR107;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR108;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR109;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR110;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR111;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR112;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR113;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR114;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR115;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR116;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR117;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR118;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR119;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR120;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR121;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR122;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR123;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR124;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR125;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR126;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR127;

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFF,0xFFFFF1EF> __ECR128;
/******************************************************************************/
/* ECR: DBG_HWBP_2_CNTL                                                       */
/* DESCRIPTION: HWBP_2 Control and Status Register                            */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_DBG_HWBP_2_CNTL __ECR128

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR129;

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFF,0xFFFFFFFF> __ECR130;
/******************************************************************************/
/* ECR: DBG_HWBP_2_CTXT0                                                      */
/* DESCRIPTION: HWBP_2 Context ID register 0                                  */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_DBG_HWBP_2_CTXT0 __ECR130


extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFF,0xFFFFFFFF> __ECR131;
/******************************************************************************/
/* ECR: DBG_HWBP_2_CTXT1                                                      */
/* DESCRIPTION: HWBP_2 Context ID register 1                                  */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_DBG_HWBP_2_CTXT1 __ECR131


extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFF,0x3FFF> __ECR132;
/******************************************************************************/
/* ECR: DBG_HWBP_2_CTXT2                                                      */
/* DESCRIPTION: HWBP_2 Context ID register 2                                  */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_DBG_HWBP_2_CTXT2 __ECR132

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR133;

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFF,0xFFFFFFFC> __ECR134;
/******************************************************************************/
/* ECR: DBG_HWBP_2_ADDR0                                                      */
/* DESCRIPTION: HWBP_2 Address Register 0                                     */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_DBG_HWBP_2_ADDR0 __ECR134


extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFF,0xFFFFFFFF> __ECR135;
/******************************************************************************/
/* ECR: DBG_HWBP_2_ADDR1                                                      */
/* DESCRIPTION: HWBP_2 Address Register 1                                     */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_DBG_HWBP_2_ADDR1 __ECR135


extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFF,0xFFFFFFFC> __ECR136;
/******************************************************************************/
/* ECR: DBG_HWBP_2_AMASK0                                                     */
/* DESCRIPTION: HWBP_2 Address Mask Register 0                                */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0xFFFFFFFC                                            */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_DBG_HWBP_2_AMASK0 __ECR136


extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFF,0xFFFFFFFF> __ECR137;
/******************************************************************************/
/* ECR: DBG_HWBP_2_AMASK1                                                     */
/* DESCRIPTION: HWBP_2 Address Mask Register 1                                */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0xFFFFFFFF                                            */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_DBG_HWBP_2_AMASK1 __ECR137

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR138;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR139;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR140;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR141;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR142;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR143;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR144;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR145;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR146;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR147;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR148;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR149;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR150;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR151;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR152;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR153;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR154;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR155;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR156;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR157;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR158;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR159;

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFF,0xFFFFF1EF> __ECR160;
/******************************************************************************/
/* ECR: DBG_HWBP_3_CNTL                                                       */
/* DESCRIPTION: HWBP_3 Control and Status Register                            */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_DBG_HWBP_3_CNTL __ECR160

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR161;

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFF,0xFFFFFFFF> __ECR162;
/******************************************************************************/
/* ECR: DBG_HWBP_3_CTXT0                                                      */
/* DESCRIPTION: HWBP_3 Context ID register 0                                  */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_DBG_HWBP_3_CTXT0 __ECR162


extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFF,0xFFFFFFFF> __ECR163;
/******************************************************************************/
/* ECR: DBG_HWBP_3_CTXT1                                                      */
/* DESCRIPTION: HWBP_3 Context ID register 1                                  */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_DBG_HWBP_3_CTXT1 __ECR163


extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFF,0x3FFF> __ECR164;
/******************************************************************************/
/* ECR: DBG_HWBP_3_CTXT2                                                      */
/* DESCRIPTION: HWBP_3 Context ID register 2                                  */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_DBG_HWBP_3_CTXT2 __ECR164

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR165;

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFF,0xFFFFFFFC> __ECR166;
/******************************************************************************/
/* ECR: DBG_HWBP_3_ADDR0                                                      */
/* DESCRIPTION: HWBP_3 Address Register 0                                     */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_DBG_HWBP_3_ADDR0 __ECR166


extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFF,0xFFFFFFFF> __ECR167;
/******************************************************************************/
/* ECR: DBG_HWBP_3_ADDR1                                                      */
/* DESCRIPTION: HWBP_3 Address Register 1                                     */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_DBG_HWBP_3_ADDR1 __ECR167


extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFF,0xFFFFFFFC> __ECR168;
/******************************************************************************/
/* ECR: DBG_HWBP_3_AMASK0                                                     */
/* DESCRIPTION: HWBP_3 Address Mask Register 0                                */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0xFFFFFFFC                                            */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_DBG_HWBP_3_AMASK0 __ECR168


extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFF,0xFFFFFFFF> __ECR169;
/******************************************************************************/
/* ECR: DBG_HWBP_3_AMASK1                                                     */
/* DESCRIPTION: HWBP_3 Address Mask Register 1                                */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0xFFFFFFFF                                            */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_DBG_HWBP_3_AMASK1 __ECR169

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR170;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR171;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR172;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR173;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR174;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR175;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR176;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR177;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR178;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR179;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR180;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR181;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR182;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR183;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR184;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR185;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR186;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR187;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR188;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR189;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR190;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR191;

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFF,0x8037FF1D> __ECR192;
/******************************************************************************/
/* ECR: DBG_HWWP_0_CNTL                                                       */
/* DESCRIPTION: HWWP_0 control and status register                            */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_DBG_HWWP_0_CNTL __ECR192

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR193;

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFF,0xFFFFFFFF> __ECR194;
/******************************************************************************/
/* ECR: DBG_HWWP_0_CTXT0                                                      */
/* DESCRIPTION: HWWP_0 Context ID Register 0                                  */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_DBG_HWWP_0_CTXT0 __ECR194


extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFF,0xFFFFFFFF> __ECR195;
/******************************************************************************/
/* ECR: DBG_HWWP_0_CTXT1                                                      */
/* DESCRIPTION: HWWP_0 Context ID Register 1                                  */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_DBG_HWWP_0_CTXT1 __ECR195


extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFF,0x3FFF> __ECR196;
/******************************************************************************/
/* ECR: DBG_HWWP_0_CTXT2                                                      */
/* DESCRIPTION: HWWP_0 Context ID Register 2                                  */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_DBG_HWWP_0_CTXT2 __ECR196

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR197;

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFF,0xFFFFFFFF> __ECR198;
/******************************************************************************/
/* ECR: DBG_HWWP_0_ADDR0                                                      */
/* DESCRIPTION: HWWP_0 Address Register 0                                     */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_DBG_HWWP_0_ADDR0 __ECR198


extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFF,0xFFFFFFFF> __ECR199;
/******************************************************************************/
/* ECR: DBG_HWWP_0_ADDR1                                                      */
/* DESCRIPTION: HWWP_0 Address Register 1                                     */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_DBG_HWWP_0_ADDR1 __ECR199


extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFF,0xFFFFFFFF> __ECR200;
/******************************************************************************/
/* ECR: DBG_HWWP_0_MASK0                                                      */
/* DESCRIPTION: HWWP_0 Address Qualification Mask Register 0                  */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0xFFFFFFFF                                            */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_DBG_HWWP_0_MASK0 __ECR200


extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFF,0xFFFFFFFF> __ECR201;
/******************************************************************************/
/* ECR: DBG_HWWP_0_MASK1                                                      */
/* DESCRIPTION: HWWP_0 Address Qualification Mask Register 1                  */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0xFFFFFFFF                                            */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_DBG_HWWP_0_MASK1 __ECR201

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR202;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR203;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR204;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR205;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR206;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR207;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR208;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR209;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR210;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR211;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR212;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR213;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR214;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR215;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR216;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR217;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR218;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR219;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR220;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR221;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR222;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR223;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR224;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR225;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR226;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR227;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR228;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR229;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR230;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR231;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR232;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR233;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR234;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR235;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR236;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR237;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR238;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR239;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR240;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR241;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR242;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR243;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR244;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR245;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR246;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR247;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR248;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR249;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR250;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR251;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR252;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR253;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR254;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR255;

#if defined(__C7100__) || defined(__C7120__)
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0x7> __ECR256;
/******************************************************************************/
/* ECR: L1DCFG                                                                */
/* DESCRIPTION: L1D Cache Configuration Register                              */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x7                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RO                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RO                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
#define __ECR_L1DCFG __ECR256
#elif defined(__C7504__) || defined(__C7524__)
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0x11> __ECR256;
/******************************************************************************/
/* ECR: L1DCFG                                                                */
/* DESCRIPTION: L1D Cache Configuration Register                              */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x11                                                  */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RO                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
#define __ECR_L1DCFG __ECR256
#endif

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR257;

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0x1> __ECR258;
/******************************************************************************/
/* ECR: L1DWB                                                                 */
/* DESCRIPTION: L1D Global Writeback Register                                 */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_L1DWB __ECR258


extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0x1> __ECR259;
/******************************************************************************/
/* ECR: L1DWBINV                                                              */
/* DESCRIPTION: L1D Global Writeback Invalidate Register                      */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_L1DWBINV __ECR259


#if defined(__C7100__) || defined(__C7120__)
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0x1> __ECR260;
/******************************************************************************/
/* ECR: L1DINV                                                                */
/* DESCRIPTION: L1D Invalidate Register                                       */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RO                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RO                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
#define __ECR_L1DINV __ECR260
#elif defined(__C7504__) || defined(__C7524__)
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0x1> __ECR260;
/******************************************************************************/
/* ECR: L1DINV                                                                */
/* DESCRIPTION: L1D Invalidate Register                                       */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RO                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
#define __ECR_L1DINV __ECR260
#endif

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR261;

extern _c70_he_detail::control_reg<1,0,0,0xFFFFFFFFFFFFFFFF,0x0> __ECR262;
/******************************************************************************/
/* ECR: L1DCTAG                                                               */
/* DESCRIPTION: L1D Cache tag View                                            */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/******************************************************************************/
/* Debug only; no macro provided.                                             */

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR263;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR264;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR265;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR266;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR267;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR268;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR269;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR270;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR271;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR272;

#if defined(__C7100__) || defined(__C7120__)
extern _c70_he_detail::control_reg<1,1,0,0xFFFFFFFFFFFFFFFF,0x0> __ECR273;
/******************************************************************************/
/* ECR: L1DADDREEA                                                            */
/* DESCRIPTION: L1D Addressing Error Event Address                            */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/*     Secure Supervisor: RO                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RO                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RO                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
#define __ECR_L1DADDREEA __ECR273
#elif defined(__C7504__) || defined(__C7524__)
extern _c70_he_detail::control_reg<1,1,0,0xFFFFFFFFFFFFFFFF,0x0> __ECR273;
/******************************************************************************/
/* ECR: L1DEEA                                                                */
/* DESCRIPTION: L1D Error Event Address                                       */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/*     Secure Supervisor: RO                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RO                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RO                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
#define __ECR_L1DEEA __ECR273
#endif


#if defined(__C7100__) || defined(__C7120__)
extern _c70_he_detail::control_reg<1,1,0,0xFFFFFFFFFFFFFFFF,0x0> __ECR274;
/******************************************************************************/
/* ECR: L1DADDREES                                                            */
/* DESCRIPTION: L1D Addressing Error Event Status                             */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/*     Secure Supervisor: RO                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RO                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RO                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
#define __ECR_L1DADDREES __ECR274
#elif defined(__C7504__) || defined(__C7524__)
extern _c70_he_detail::control_reg<1,1,0,0xFFFFFFFFFFFFFFFF,0x0> __ECR274;
/******************************************************************************/
/* ECR: L1DEES                                                                */
/* DESCRIPTION: L1D Error Event Status                                        */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/*     Secure Supervisor: RO                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RO                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RO                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
#define __ECR_L1DEES __ECR274
#endif


#if defined(__C7100__) || defined(__C7120__)
extern _c70_he_detail::control_reg<1,0,1,0xFFFFFFFFFFFFFFFE,0x1> __ECR275;
/******************************************************************************/
/* ECR: L1DADDREER                                                            */
/* DESCRIPTION: L1D Addressing Error Event Reset                              */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Supervisor: WO                                                  */
/*     Secure User:       WO                                                  */
/*     Supervisor:        WO                                                  */
/*     User:              WO                                                  */
/******************************************************************************/
#define __ECR_L1DADDREER __ECR275
#elif defined(__C7504__) || defined(__C7524__)
extern _c70_he_detail::control_reg<1,0,1,0xFFFFFFFFFFFFFFFE,0x1> __ECR275;
/******************************************************************************/
/* ECR: L1DEER                                                                */
/* DESCRIPTION: L1D Error Event Reset                                         */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Supervisor: WO                                                  */
/*     Secure User:       WO                                                  */
/*     Supervisor:        WO                                                  */
/*     User:              WO                                                  */
/******************************************************************************/
#define __ECR_L1DEER __ECR275
#endif


#if defined(__C7100__) || defined(__C7120__)
extern _c70_he_detail::control_reg<1,1,0,0xFFFFFFFFFFFFFFFF,0x0> __ECR276;
/******************************************************************************/
/* ECR: L1DCMDEEA                                                             */
/* DESCRIPTION: L1D CMD Error Event Address                                   */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/*     Secure Supervisor: RO                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RO                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RO                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
#define __ECR_L1DCMDEEA __ECR276
#else
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR276;
#endif


#if defined(__C7100__) || defined(__C7120__)
extern _c70_he_detail::control_reg<1,1,0,0xFFFFFFFFFFFFFFFF,0x0> __ECR277;
/******************************************************************************/
/* ECR: L1DCMDEES                                                             */
/* DESCRIPTION: L1D CMD Error Event Status                                    */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/*     Secure Supervisor: RO                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RO                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RO                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
#define __ECR_L1DCMDEES __ECR277
#else
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR277;
#endif


#if defined(__C7100__) || defined(__C7120__)
extern _c70_he_detail::control_reg<1,0,1,0xFFFFFFFFFFFFFFFE,0x1> __ECR278;
/******************************************************************************/
/* ECR: L1DCMDEER                                                             */
/* DESCRIPTION: L1D CMD Error Event Reset                                     */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Supervisor: WO                                                  */
/*     Secure User:       WO                                                  */
/*     Supervisor:        WO                                                  */
/*     User:              WO                                                  */
/******************************************************************************/
#define __ECR_L1DCMDEER __ECR278
#else
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR278;
#endif

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR279;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR280;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR281;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR282;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR283;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR284;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR285;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR286;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR287;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR288;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR289;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR290;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR291;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR292;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR293;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR294;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR295;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR296;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR297;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR298;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR299;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR300;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR301;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR302;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR303;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR304;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR305;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR306;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR307;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR308;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR309;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR310;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR311;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR312;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR313;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR314;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR315;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR316;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR317;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR318;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR319;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR320;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR321;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR322;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR323;

extern _c70_he_detail::control_reg<1,0,0,0xFFFFFFFFFFFFFFFF,0x0> __ECR324;
/******************************************************************************/
/* ECR: L1PCTAG                                                               */
/* DESCRIPTION: L1P Cache Tag View                                            */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/******************************************************************************/
/* Debug only; no macro provided.                                             */

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR325;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR326;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR327;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR328;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR329;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR330;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR331;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR332;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR333;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR334;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR335;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR336;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR337;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR338;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR339;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR340;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR341;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR342;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR343;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR344;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR345;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR346;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR347;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR348;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR349;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR350;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR351;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR352;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR353;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR354;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR355;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR356;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR357;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR358;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR359;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR360;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR361;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR362;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR363;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR364;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR365;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR366;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR367;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR368;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR369;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR370;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR371;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR372;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR373;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR374;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR375;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR376;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR377;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR378;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR379;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR380;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR381;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR382;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR383;

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0x17> __ECR384;
/******************************************************************************/
/* ECR: L2CFG                                                                 */
/* DESCRIPTION: L2 Cache Configuration Register                               */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RO                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RO                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
#define __ECR_L2CFG __ECR384


extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0x39CE3F00000008> __ECR385;
/******************************************************************************/
/* ECR: L2CC                                                                  */
/* DESCRIPTION: L2 Cache Control Register                                     */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x10C60A00000000                                      */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
#define __ECR_L2CC __ECR385


extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0x1> __ECR386;
/******************************************************************************/
/* ECR: L2WB                                                                  */
/* DESCRIPTION: L2 Global Writeback Register                                  */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_L2WB __ECR386


extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0x1> __ECR387;
/******************************************************************************/
/* ECR: L2WBINV                                                               */
/* DESCRIPTION: L2 Global Writeback Invalidate Register                       */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_L2WBINV __ECR387


extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0x1> __ECR388;
/******************************************************************************/
/* ECR: L2INV                                                                 */
/* DESCRIPTION: L2 Invalidate Register                                        */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RO                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RO                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
#define __ECR_L2INV __ECR388

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR389;

extern _c70_he_detail::control_reg<1,0,0,0xFFFFFFFFFFFFFFFF,0x0> __ECR390;
/******************************************************************************/
/* ECR: L2CTAG                                                                */
/* DESCRIPTION: L2 Cache tag View                                             */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/******************************************************************************/
/* Debug only; no macro provided.                                             */


extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFF0001> __ECR391;
/******************************************************************************/
/* ECR: L2EDCFG                                                               */
/* DESCRIPTION: L2 EDC Configuration Control                                  */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x8000000004000001                                    */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RO                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RO                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
#define __ECR_L2EDCFG __ECR391

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR392;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR393;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR394;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR395;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR396;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR397;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR398;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR399;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR400;

extern _c70_he_detail::control_reg<1,1,0,0xFFFFFFFFFFFFFFFF,0x0> __ECR401;
/******************************************************************************/
/* ECR: L2ADDREEA                                                             */
/* DESCRIPTION: L2 Addressing Error Event Address                             */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/*     Secure Supervisor: RO                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RO                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RO                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
#define __ECR_L2ADDREEA __ECR401


extern _c70_he_detail::control_reg<1,1,0,0xFFFFFFFFFFFFFFFF,0x0> __ECR402;
/******************************************************************************/
/* ECR: L2ADDREES                                                             */
/* DESCRIPTION: L2 Addressing Error Event Status                              */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/*     Secure Supervisor: RO                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RO                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RO                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
#define __ECR_L2ADDREES __ECR402


extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFE,0x1> __ECR403;
/******************************************************************************/
/* ECR: L2ADDREER                                                             */
/* DESCRIPTION: L2 Addressing Error Event Reset                               */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RO                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RO                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
#define __ECR_L2ADDREER __ECR403


extern _c70_he_detail::control_reg<1,1,0,0xFFFFFFFFFFFFFFFF,0x0> __ECR404;
/******************************************************************************/
/* ECR: L2ALLOCEEA                                                            */
/* DESCRIPTION: L2 CMD Error Event Address                                    */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/*     Secure Supervisor: RO                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RO                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RO                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
#define __ECR_L2ALLOCEEA __ECR404


extern _c70_he_detail::control_reg<1,1,0,0xFFFFFFFFFFFFFFFF,0x0> __ECR405;
/******************************************************************************/
/* ECR: L2ALLOCEES                                                            */
/* DESCRIPTION: L2 CMD Error Event Status                                     */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/*     Secure Supervisor: RO                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RO                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RO                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
#define __ECR_L2ALLOCEES __ECR405


extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFE,0x1> __ECR406;
/******************************************************************************/
/* ECR: L2ALLOCEER                                                            */
/* DESCRIPTION: L2 CMD Error Event Reset                                      */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RO                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RO                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
#define __ECR_L2ALLOCEER __ECR406


extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0x11> __ECR407;
/******************************************************************************/
/* ECR: L2MEMMAP                                                              */
/* DESCRIPTION: L2 Memory Map Control                                         */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_L2MEMMAP __ECR407


extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0x11111> __ECR408;
/******************************************************************************/
/* ECR: L2MSWCTL                                                              */
/* DESCRIPTION: L2 Memory Switch Control                                      */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_L2MSWCTL __ECR408


extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFF8000FFFF8000> __ECR409;
/******************************************************************************/
/* ECR: L2MEMMAPIBUFA                                                         */
/* DESCRIPTION: L2 IBUFA Memory Base Control                                  */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_L2MEMMAPIBUFA __ECR409


extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFF8000FFFF8000> __ECR410;
/******************************************************************************/
/* ECR: L2MEMMAPIBUFB                                                         */
/* DESCRIPTION: L2 IBUFB Memory Base Address                                  */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_L2MEMMAPIBUFB __ECR410


extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFF8000> __ECR411;
/******************************************************************************/
/* ECR: L2MEMMAPWBUF                                                          */
/* DESCRIPTION: L2 WBUF Memory Base Address                                   */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_L2MEMMAPWBUF __ECR411


extern _c70_he_detail::control_reg<1,1,0,0xFFFFFFFFFFFFFFFF,0x0> __ECR412;
/******************************************************************************/
/* ECR: L2MSWERRSTAT                                                          */
/* DESCRIPTION: L2 Memory Switch Error Status                                 */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/*     Secure Supervisor: RO                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RO                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RO                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
#define __ECR_L2MSWERRSTAT __ECR412


extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFF09,0xF6> __ECR413;
/******************************************************************************/
/* ECR: L2MSWERRCLR                                                           */
/* DESCRIPTION: L2 Memory Switch Error Clear                                  */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RO                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RO                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
#define __ECR_L2MSWERRCLR __ECR413


extern _c70_he_detail::control_reg<1,1,0,0xFFFFFFFFFFFFFFFF,0x0> __ECR414;
/******************************************************************************/
/* ECR: L2MSWERRADDR                                                          */
/* DESCRIPTION: L2 Memory Switch Error Address                                */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/*     Secure Supervisor: RO                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RO                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RO                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
#define __ECR_L2MSWERRADDR __ECR414


extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFF00000001> __ECR415;
/******************************************************************************/
/* ECR: L2EDTST                                                               */
/* DESCRIPTION: L2 EDC Test Control                                           */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RO                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RO                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
#define __ECR_L2EDTST __ECR415

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR416;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR417;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR418;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR419;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR420;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR421;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR422;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR423;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR424;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR425;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR426;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR427;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR428;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR429;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR430;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR431;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR432;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR433;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR434;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR435;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR436;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR437;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR438;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR439;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR440;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR441;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR442;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR443;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR444;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR445;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR446;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR447;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR448;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR449;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR450;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR451;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR452;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR453;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR454;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR455;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR456;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR457;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR458;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR459;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR460;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR461;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR462;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR463;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR464;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR465;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR466;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR467;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR468;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR469;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR470;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR471;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR472;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR473;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR474;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR475;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR476;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR477;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR478;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR479;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR480;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR481;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR482;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR483;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR484;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR485;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR486;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR487;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR488;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR489;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR490;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR491;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR492;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR493;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR494;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR495;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR496;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR497;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR498;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR499;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR500;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR501;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR502;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR503;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR504;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR505;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR506;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR507;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR508;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR509;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR510;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR511;

extern _c70_he_detail::control_reg<1,1,0,0xFFFFFFFFFFFFFFFF,0x0> __ECR512;
/******************************************************************************/
/* ECR: SE0_PID                                                               */
/* DESCRIPTION: Stream 0 PID Register                                         */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x60E00800                                            */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/*     Secure Supervisor: RO                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RO                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RO                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
#define __ECR_SE0_PID __ECR512


#if defined(__C7100__) || defined(__C7120__)
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0x1FFFFFFFFFF80> __ECR513;
/******************************************************************************/
/* ECR: SE0_FAR                                                               */
/* DESCRIPTION: Stream 0 Fail Address Register                                */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Supervisor:        RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/******************************************************************************/
#define __ECR_SE0_FAR __ECR513
#elif defined(__C7504__) || defined(__C7524__)
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0x1FFFFFFFFFFFF> __ECR513;
/******************************************************************************/
/* ECR: SE0_FAR                                                               */
/* DESCRIPTION: Stream 0 Fail Address Register                                */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Supervisor:        RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/******************************************************************************/
#define __ECR_SE0_FAR __ECR513
#endif


extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0x1FFF> __ECR514;
/******************************************************************************/
/* ECR: SE0_FSR                                                               */
/* DESCRIPTION: Stream 0 Fail Status Register                                 */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Supervisor:        RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/******************************************************************************/
#define __ECR_SE0_FSR __ECR514

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR515;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR516;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR517;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR518;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR519;

#if defined(__C7100__) || defined(__C7120__)
extern _c70_he_detail::control_reg<16,0,0,0xFFFFFFFFFFFFFFFF,0x0> __ECR520;
/******************************************************************************/
/* ECR: SE0_TAG                                                               */
/* DESCRIPTION: Stream 0 Tag Data and Metadata Register                       */
/* INDEX RANGE: [0,15]                                                        */
/* GENERAL RESET VALUE: 0x6                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/******************************************************************************/
/* Debug only; no macro provided.                                             */
#elif defined(__C7504__) || defined(__C7524__)
extern _c70_he_detail::control_reg<32,0,0,0xFFFFFFFFFFFFFFFF,0x0> __ECR520;
/******************************************************************************/
/* ECR: SE0_TAG                                                               */
/* DESCRIPTION: Stream 0 Tag Data and Metadata Register                       */
/* INDEX RANGE: [0,31]                                                        */
/* GENERAL RESET VALUE: 0x6                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/******************************************************************************/
/* Debug only; no macro provided.                                             */
#endif


#if defined(__C7100__)
extern _c70_he_detail::control_reg<29,0,0,0xFFFFFFFFFFFFFFFF,0x0> __ECR521;
/******************************************************************************/
/* ECR: SE0_ICNT                                                              */
/* DESCRIPTION: Stream 0 Iteration Count Register                             */
/* INDEX RANGE: [0,28]                                                        */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/******************************************************************************/
/* Debug only; no macro provided.                                             */
#elif defined(__C7120__) || defined(__C7504__) || defined(__C7524__)
extern _c70_he_detail::control_reg<55,0,0,0xFFFFFFFFFFFFFFFF,0x0> __ECR521;
/******************************************************************************/
/* ECR: SE0_ICNT                                                              */
/* DESCRIPTION: Stream 0 Iteration Count Register                             */
/* INDEX RANGE: [0,54]                                                        */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/******************************************************************************/
/* Debug only; no macro provided.                                             */
#endif


extern _c70_he_detail::control_reg<5,0,0,0xFFFFFFFFFFFFFFFF,0x0> __ECR522;
/******************************************************************************/
/* ECR: SE0_DIM                                                               */
/* DESCRIPTION: Stream 0 Dimension Register                                   */
/* INDEX RANGE: [0,4]                                                         */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/******************************************************************************/
/* Debug only; no macro provided.                                             */


extern _c70_he_detail::control_reg<14,0,0,0xFFFFFFFFFFFFFFFF,0x0> __ECR523;
/******************************************************************************/
/* ECR: SE0_ADDR                                                              */
/* DESCRIPTION: Stream 0 Address Register                                     */
/* INDEX RANGE: [0,13]                                                        */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/******************************************************************************/
/* Debug only; no macro provided.                                             */


#if defined(__C7100__)
extern _c70_he_detail::control_reg<1,0,0,0xFFFFFFFFFFFFFFFF,0x0> __ECR524;
/******************************************************************************/
/* ECR: SE0_STATUS                                                            */
/* DESCRIPTION: Stream 0 Status and Flag Register                             */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/******************************************************************************/
/* Debug only; no macro provided.                                             */
#elif defined(__C7120__) || defined(__C7504__) || defined(__C7524__)
extern _c70_he_detail::control_reg<2,0,0,0xFFFFFFFFFFFFFFFF,0x0> __ECR524;
/******************************************************************************/
/* ECR: SE0_STATUS                                                            */
/* DESCRIPTION: Stream 0 Status and Flag Register                             */
/* INDEX RANGE: [0,1]                                                         */
/* INDEX 0 RESET VALUE: 0x0                                                   */
/* INDEX 1 RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/******************************************************************************/
/* Debug only; no macro provided.                                             */
#endif


#if defined(__C7120__) || defined(__C7504__) || defined(__C7524__)
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR525;
/******************************************************************************/
/* ECR: SE0_SBND                                                              */
/* DESCRIPTION: Stream 0 Sideband Register                                    */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_SE0_SBND __ECR525
#else
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR525;
#endif

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR526;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR527;

extern _c70_he_detail::control_reg<1,1,0,0xFFFFFFFFFFFFFFFF,0x0> __ECR528;
/******************************************************************************/
/* ECR: SE1_PID                                                               */
/* DESCRIPTION: Stream 1 PID Register                                         */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x60E00800                                            */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/*     Secure Supervisor: RO                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RO                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RO                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
#define __ECR_SE1_PID __ECR528


#if defined(__C7100__) || defined(__C7120__)
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0x1FFFFFFFFFF80> __ECR529;
/******************************************************************************/
/* ECR: SE1_FAR                                                               */
/* DESCRIPTION: Stream 1 Fail Address Register                                */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Supervisor:        RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/******************************************************************************/
#define __ECR_SE1_FAR __ECR529
#elif defined(__C7504__) || defined(__C7524__)
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0x1FFFFFFFFFFFF> __ECR529;
/******************************************************************************/
/* ECR: SE1_FAR                                                               */
/* DESCRIPTION: Stream 1 Fail Address Register                                */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Supervisor:        RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/******************************************************************************/
#define __ECR_SE1_FAR __ECR529
#endif


extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0x1FFF> __ECR530;
/******************************************************************************/
/* ECR: SE1_FSR                                                               */
/* DESCRIPTION: Stream 1 Fail Status Register                                 */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Supervisor:        RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/******************************************************************************/
#define __ECR_SE1_FSR __ECR530

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR531;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR532;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR533;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR534;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR535;

#if defined(__C7100__) || defined(__C7120__)
extern _c70_he_detail::control_reg<16,0,0,0xFFFFFFFFFFFFFFFF,0x0> __ECR536;
/******************************************************************************/
/* ECR: SE1_TAG                                                               */
/* DESCRIPTION: Stream 1 Tag Data and Metadata Register                       */
/* INDEX RANGE: [0,15]                                                        */
/* GENERAL RESET VALUE: 0x6                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/******************************************************************************/
/* Debug only; no macro provided.                                             */
#elif defined(__C7504__) || defined(__C7524__)
extern _c70_he_detail::control_reg<32,0,0,0xFFFFFFFFFFFFFFFF,0x0> __ECR536;
/******************************************************************************/
/* ECR: SE1_TAG                                                               */
/* DESCRIPTION: Stream 1 Tag Data and Metadata Register                       */
/* INDEX RANGE: [0,31]                                                        */
/* GENERAL RESET VALUE: 0x6                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/******************************************************************************/
/* Debug only; no macro provided.                                             */
#endif


#if defined(__C7100__)
extern _c70_he_detail::control_reg<29,0,0,0xFFFFFFFFFFFFFFFF,0x0> __ECR537;
/******************************************************************************/
/* ECR: SE1_ICNT                                                              */
/* DESCRIPTION: Stream 1 Iteration Count Register                             */
/* INDEX RANGE: [0,28]                                                        */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/******************************************************************************/
/* Debug only; no macro provided.                                             */
#elif defined(__C7120__) || defined(__C7504__) || defined(__C7524__)
extern _c70_he_detail::control_reg<55,0,0,0xFFFFFFFFFFFFFFFF,0x0> __ECR537;
/******************************************************************************/
/* ECR: SE1_ICNT                                                              */
/* DESCRIPTION: Stream 1 Iteration Count Register                             */
/* INDEX RANGE: [0,54]                                                        */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/******************************************************************************/
/* Debug only; no macro provided.                                             */
#endif


extern _c70_he_detail::control_reg<5,0,0,0xFFFFFFFFFFFFFFFF,0x0> __ECR538;
/******************************************************************************/
/* ECR: SE1_DIM                                                               */
/* DESCRIPTION: Stream 1 Dimension Register                                   */
/* INDEX RANGE: [0,4]                                                         */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/******************************************************************************/
/* Debug only; no macro provided.                                             */


extern _c70_he_detail::control_reg<14,0,0,0xFFFFFFFFFFFFFFFF,0x0> __ECR539;
/******************************************************************************/
/* ECR: SE1_ADDR                                                              */
/* DESCRIPTION: Stream 1 Address Register                                     */
/* INDEX RANGE: [0,13]                                                        */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/******************************************************************************/
/* Debug only; no macro provided.                                             */


#if defined(__C7100__)
extern _c70_he_detail::control_reg<1,0,0,0xFFFFFFFFFFFFFFFF,0x0> __ECR540;
/******************************************************************************/
/* ECR: SE1_STATUS                                                            */
/* DESCRIPTION: Stream 1 Status and Flag Register                             */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/******************************************************************************/
/* Debug only; no macro provided.                                             */
#elif defined(__C7120__) || defined(__C7504__) || defined(__C7524__)
extern _c70_he_detail::control_reg<2,0,0,0xFFFFFFFFFFFFFFFF,0x0> __ECR540;
/******************************************************************************/
/* ECR: SE1_STATUS                                                            */
/* DESCRIPTION: Stream 1 Status and Flag Register                             */
/* INDEX RANGE: [0,1]                                                         */
/* INDEX 0 RESET VALUE: 0x0                                                   */
/* INDEX 1 RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/******************************************************************************/
/* Debug only; no macro provided.                                             */
#endif


#if defined(__C7120__) || defined(__C7504__) || defined(__C7524__)
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR541;
/******************************************************************************/
/* ECR: SE1_SBND                                                              */
/* DESCRIPTION: Stream 1 Sideband Register                                    */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_SE1_SBND __ECR541
#else
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR541;
#endif

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR542;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR543;

extern _c70_he_detail::control_reg<1,1,0,0xFFFFFFFFFFFFFFFF,0x0> __ECR544;
/******************************************************************************/
/* ECR: SE2_PID                                                               */
/* DESCRIPTION: Stream 2 PID Register                                         */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/*     Secure Supervisor: RO                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RO                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RO                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
#define __ECR_SE2_PID __ECR544

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR545;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR546;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR547;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR548;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR549;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR550;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR551;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR552;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR553;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR554;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR555;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR556;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR557;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR558;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR559;

extern _c70_he_detail::control_reg<1,1,0,0xFFFFFFFFFFFFFFFF,0x0> __ECR560;
/******************************************************************************/
/* ECR: SE3_PID                                                               */
/* DESCRIPTION: Stream 3 PID Register                                         */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/*     Secure Supervisor: RO                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RO                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RO                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
#define __ECR_SE3_PID __ECR560

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR561;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR562;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR563;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR564;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR565;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR566;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR567;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR568;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR569;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR570;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR571;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR572;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR573;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR574;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR575;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR576;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR577;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR578;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR579;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR580;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR581;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR582;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR583;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR584;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR585;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR586;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR587;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR588;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR589;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR590;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR591;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR592;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR593;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR594;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR595;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR596;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR597;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR598;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR599;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR600;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR601;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR602;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR603;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR604;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR605;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR606;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR607;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR608;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR609;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR610;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR611;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR612;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR613;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR614;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR615;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR616;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR617;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR618;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR619;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR620;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR621;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR622;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR623;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR624;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR625;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR626;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR627;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR628;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR629;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR630;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR631;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR632;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR633;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR634;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR635;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR636;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR637;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR638;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR639;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR640;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR641;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR642;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR643;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR644;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR645;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR646;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR647;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR648;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR649;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR650;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR651;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR652;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR653;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR654;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR655;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR656;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR657;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR658;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR659;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR660;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR661;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR662;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR663;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR664;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR665;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR666;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR667;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR668;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR669;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR670;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR671;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR672;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR673;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR674;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR675;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR676;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR677;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR678;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR679;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR680;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR681;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR682;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR683;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR684;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR685;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR686;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR687;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR688;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR689;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR690;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR691;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR692;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR693;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR694;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR695;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR696;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR697;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR698;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR699;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR700;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR701;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR702;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR703;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR704;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR705;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR706;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR707;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR708;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR709;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR710;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR711;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR712;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR713;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR714;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR715;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR716;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR717;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR718;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR719;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR720;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR721;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR722;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR723;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR724;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR725;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR726;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR727;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR728;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR729;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR730;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR731;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR732;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR733;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR734;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR735;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR736;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR737;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR738;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR739;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR740;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR741;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR742;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR743;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR744;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR745;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR746;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR747;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR748;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR749;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR750;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR751;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR752;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR753;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR754;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR755;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR756;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR757;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR758;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR759;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR760;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR761;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR762;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR763;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR764;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR765;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR766;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR767;

extern _c70_he_detail::control_reg<1,1,0,0xFFFFFFFFFFFFFFFF,0x0> __ECR768;
/******************************************************************************/
/* ECR: MMU_PID                                                               */
/* DESCRIPTION: Physical ID Register                                          */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x60F00000                                            */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/*     Secure Supervisor: RO                                                  */
/*     Supervisor:        RO                                                  */
/*     Guest Supervisor:  RO                                                  */
/******************************************************************************/
#define __ECR_MMU_PID __ECR768

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR769;

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFF0001> __ECR770;
/******************************************************************************/
/* ECR: MMU_REPL                                                              */
/* DESCRIPTION: Replacement Policy Register                                   */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Supervisor:        RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/******************************************************************************/
#define __ECR_MMU_REPL __ECR770

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR771;

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0x81FF00FFFFFFFFFF> __ECR772;
/******************************************************************************/
/* ECR: TDRR                                                                  */
/* DESCRIPTION: Translation Debug Response Register                           */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Supervisor:        RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/******************************************************************************/
#define __ECR_TDRR __ECR772


extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR773;
/******************************************************************************/
/* ECR: TDFAR                                                                 */
/* DESCRIPTION: Translation Debug Fault Address Register                      */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Supervisor:        RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/******************************************************************************/
#define __ECR_TDFAR __ECR773

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR774;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR775;

extern _c70_he_detail::control_reg<1,0,1,0xFF00F80000000000,0xFF07FFFFFFFFFF> __ECR776;
/******************************************************************************/
/* ECR: TLB_INV                                                               */
/* DESCRIPTION: TLB Invalidation Register                                     */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      WO                                                  */
/*     Non-Secure Debug:  WO                                                  */
/*     Secure Supervisor: WO                                                  */
/*     Supervisor:        WO                                                  */
/*     Guest Supervisor:  WO                                                  */
/******************************************************************************/
#define __ECR_TLB_INV __ECR776

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR777;

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0x1> __ECR778;
/******************************************************************************/
/* ECR: TLB_INVC                                                              */
/* DESCRIPTION: TLB Complete Register                                         */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Supervisor:        RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/******************************************************************************/
#define __ECR_TLB_INVC __ECR778


extern _c70_he_detail::control_reg<1,0,0,0xFFFFFFFFFFFCCF80,0x3307F> __ECR779;
/******************************************************************************/
/* ECR: TLB_DBG                                                               */
/* DESCRIPTION: TLB Debug Access Register                                     */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      WO                                                  */
/*     Non-Secure Debug:  WO                                                  */
/******************************************************************************/
/* Debug only; no macro provided.                                             */


extern _c70_he_detail::control_reg<1,0,0,0xFFFFFFFFFFFFFFFF,0x0> __ECR780;
/******************************************************************************/
/* ECR: TLB_DBG_DATA0                                                         */
/* DESCRIPTION: TLB Debug Data 0 Register                                     */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/******************************************************************************/
/* Debug only; no macro provided.                                             */


extern _c70_he_detail::control_reg<1,0,0,0xFFFFFFFFFFFFFFFF,0x0> __ECR781;
/******************************************************************************/
/* ECR: TLB_DBG_DATA1                                                         */
/* DESCRIPTION: TLB Debug Data 1 Register                                     */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/******************************************************************************/
/* Debug only; no macro provided.                                             */

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR782;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR783;

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0x80000000000000FF> __ECR784;
/******************************************************************************/
/* ECR: SCR                                                                   */
/* DESCRIPTION: System Control Register                                       */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Supervisor:        RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/******************************************************************************/
#define __ECR_SCR __ECR784


extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0x1FFFF> __ECR785;
/******************************************************************************/
/* ECR: TCR0                                                                  */
/* DESCRIPTION: Table Control Register 0                                      */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Supervisor:        RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/******************************************************************************/
#define __ECR_TCR0 __ECR785


extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0x1FFFF> __ECR786;
/******************************************************************************/
/* ECR: TCR1                                                                  */
/* DESCRIPTION: Table Control Register 1                                      */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Supervisor:        RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/******************************************************************************/
#define __ECR_TCR1 __ECR786


extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFF00FFFFFFFFFF> __ECR787;
/******************************************************************************/
/* ECR: TBR0                                                                  */
/* DESCRIPTION: Table Base Register 0                                         */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Supervisor:        RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/******************************************************************************/
#define __ECR_TBR0 __ECR787


extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFF00FFFFFFFFFF> __ECR788;
/******************************************************************************/
/* ECR: TBR1                                                                  */
/* DESCRIPTION: Table Base Register 1                                         */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Supervisor:        RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/******************************************************************************/
#define __ECR_TBR1 __ECR788


extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR789;
/******************************************************************************/
/* ECR: MAR                                                                   */
/* DESCRIPTION: Memory Attribute Register                                     */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Supervisor:        RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/******************************************************************************/
#define __ECR_MAR __ECR789


extern _c70_he_detail::control_reg<1,0,1,0x0,0xFFFFFFFFFFFFFFFF> __ECR790;
/******************************************************************************/
/* ECR: TDAR                                                                  */
/* DESCRIPTION: Translation Debug Address Register                            */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      WO                                                  */
/*     Non-Secure Debug:  WO                                                  */
/*     Secure Supervisor: WO                                                  */
/*     Supervisor:        WO                                                  */
/*     Guest Supervisor:  WO                                                  */
/******************************************************************************/
#define __ECR_TDAR __ECR790

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR791;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR792;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR793;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR794;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR795;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR796;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR797;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR798;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR799;

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0x80000000000000FF> __ECR800;
/******************************************************************************/
/* ECR: SCR_GS                                                                */
/* DESCRIPTION: System Control Register - Non-Secure Guest Supervisor         */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Supervisor:        RW                                                  */
/******************************************************************************/
#define __ECR_SCR_GS __ECR800


extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0x1FFFF> __ECR801;
/******************************************************************************/
/* ECR: TCR0_GS                                                               */
/* DESCRIPTION: Table Control Register 0 - Non-Secure Guest Supervisor        */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Supervisor:        RW                                                  */
/******************************************************************************/
#define __ECR_TCR0_GS __ECR801


extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0x1FFFF> __ECR802;
/******************************************************************************/
/* ECR: TCR1_GS                                                               */
/* DESCRIPTION: Table Control Register 1 - Non-Secure Guest Supervisor        */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Supervisor:        RW                                                  */
/******************************************************************************/
#define __ECR_TCR1_GS __ECR802


extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFF00FFFFFFFFFF> __ECR803;
/******************************************************************************/
/* ECR: TBR0_GS                                                               */
/* DESCRIPTION: Table Base Register 0 - Non-Secure Guest Supervisor           */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Supervisor:        RW                                                  */
/******************************************************************************/
#define __ECR_TBR0_GS __ECR803


extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFF00FFFFFFFFFF> __ECR804;
/******************************************************************************/
/* ECR: TBR1_GS                                                               */
/* DESCRIPTION: Table Base Register 1 - Non-Secure Guest Supervisor           */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Supervisor:        RW                                                  */
/******************************************************************************/
#define __ECR_TBR1_GS __ECR804


extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR805;
/******************************************************************************/
/* ECR: MAR_GS                                                                */
/* DESCRIPTION: Memory Attribute Register - Non-Secure Guest Supervisor       */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Supervisor:        RW                                                  */
/******************************************************************************/
#define __ECR_MAR_GS __ECR805


extern _c70_he_detail::control_reg<1,0,1,0x0,0xFFFFFFFFFFFFFFFF> __ECR806;
/******************************************************************************/
/* ECR: TDAR_GS                                                               */
/* DESCRIPTION: Translation Debug Address Register - Non-Secure Guest Supervisor */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      WO                                                  */
/*     Non-Secure Debug:  WO                                                  */
/*     Secure Supervisor: WO                                                  */
/*     Supervisor:        WO                                                  */
/******************************************************************************/
#define __ECR_TDAR_GS __ECR806

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR807;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR808;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR809;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR810;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR811;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR812;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR813;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR814;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR815;

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0x80000000000000FF> __ECR816;
/******************************************************************************/
/* ECR: SCR_S                                                                 */
/* DESCRIPTION: System Control Register - Non-Secure Supervisor               */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Secure Supervisor: RW                                                  */
/******************************************************************************/
#define __ECR_SCR_S __ECR816


extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0x1FFFF> __ECR817;
/******************************************************************************/
/* ECR: TCR0_S                                                                */
/* DESCRIPTION: Table Control Register 0 - Non-Secure Supervisor              */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Secure Supervisor: RW                                                  */
/******************************************************************************/
#define __ECR_TCR0_S __ECR817


extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0x1FFFF> __ECR818;
/******************************************************************************/
/* ECR: TCR1_S                                                                */
/* DESCRIPTION: Table Control Register 1 - Non-Secure Supervisor              */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Secure Supervisor: RW                                                  */
/******************************************************************************/
#define __ECR_TCR1_S __ECR818


extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFF00FFFFFFFFFF> __ECR819;
/******************************************************************************/
/* ECR: TBR0_S                                                                */
/* DESCRIPTION: Table Base Register 0 - Non-Secure Supervisor                 */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Secure Supervisor: RW                                                  */
/******************************************************************************/
#define __ECR_TBR0_S __ECR819


extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFF00FFFFFFFFFF> __ECR820;
/******************************************************************************/
/* ECR: TBR1_S                                                                */
/* DESCRIPTION: Table Base Register 1 - Non-Secure Supervisor                 */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Secure Supervisor: RW                                                  */
/******************************************************************************/
#define __ECR_TBR1_S __ECR820


extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR821;
/******************************************************************************/
/* ECR: MAR_S                                                                 */
/* DESCRIPTION: Memory Attribute Register - Non-Secure Supervisor             */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Secure Supervisor: RW                                                  */
/******************************************************************************/
#define __ECR_MAR_S __ECR821


extern _c70_he_detail::control_reg<1,0,1,0x0,0xFFFFFFFFFFFFFFFF> __ECR822;
/******************************************************************************/
/* ECR: TDAR_S                                                                */
/* DESCRIPTION: Translation Debug Address Register - Non-Secure Supervisor    */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      WO                                                  */
/*     Secure Supervisor: WO                                                  */
/******************************************************************************/
#define __ECR_TDAR_S __ECR822

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR823;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR824;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR825;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR826;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR827;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR828;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR829;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR830;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR831;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR832;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR833;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR834;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR835;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR836;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR837;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR838;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR839;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR840;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR841;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR842;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR843;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR844;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR845;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR846;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR847;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR848;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR849;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR850;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR851;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR852;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR853;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR854;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR855;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR856;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR857;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR858;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR859;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR860;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR861;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR862;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR863;

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0x3F> __ECR864;
/******************************************************************************/
/* ECR: VCR                                                                   */
/* DESCRIPTION: Virtualization Control Register                               */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Supervisor:        RW                                                  */
/******************************************************************************/
#define __ECR_VCR __ECR864


extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0x7FFFE> __ECR865;
/******************************************************************************/
/* ECR: VTCR                                                                  */
/* DESCRIPTION: Virtualization Table Control Register                         */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Supervisor:        RW                                                  */
/******************************************************************************/
#define __ECR_VTCR __ECR865


extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFF00FFFFFFFFFF> __ECR866;
/******************************************************************************/
/* ECR: VTBR                                                                  */
/* DESCRIPTION: Virtualization Table Base Register                            */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Supervisor:        RW                                                  */
/******************************************************************************/
#define __ECR_VTBR __ECR866


extern _c70_he_detail::control_reg<1,0,1,0x0,0xFFFFFFFFFFFFFFFF> __ECR867;
/******************************************************************************/
/* ECR: VTDAR                                                                 */
/* DESCRIPTION: Virtualization Translation Debug Address Register             */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      WO                                                  */
/*     Non-Secure Debug:  WO                                                  */
/*     Secure Supervisor: WO                                                  */
/*     Supervisor:        WO                                                  */
/******************************************************************************/
#define __ECR_VTDAR __ECR867

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR868;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR869;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR870;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR871;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR872;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR873;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR874;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR875;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR876;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR877;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR878;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR879;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR880;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR881;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR882;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR883;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR884;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR885;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR886;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR887;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR888;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR889;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR890;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR891;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR892;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR893;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR894;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR895;

#if defined(__C7100__) || defined(__C7120__)
extern _c70_he_detail::control_reg<16,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFF71FFFFFFFFF> __ECR896;
/******************************************************************************/
/* ECR: L1D_UTLB_MATCH                                                        */
/* DESCRIPTION: Indexed uTLB Page Match Entry                                 */
/* INDEX RANGE: [0,15]                                                        */
/* GENERAL RESET VALUE: 0x0                                                   */
/* INDEX 0 RESET VALUE: 0xF000070000000000                                    */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_L1D_UTLB_MATCH __ECR896
#elif defined(__C7504__) || defined(__C7524__)
extern _c70_he_detail::control_reg<16,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFF71FFFFFFFFF> __ECR896;
/******************************************************************************/
/* ECR: L1D_UTLB_MATCH                                                        */
/* DESCRIPTION: Indexed uTLB Page Match Entry                                 */
/* INDEX RANGE: [0,15]                                                        */
/* GENERAL RESET VALUE: 0x0                                                   */
/* INDEX 0 RESET VALUE: 0xB000070000000000                                    */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_L1D_UTLB_MATCH __ECR896
#endif

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR897;

extern _c70_he_detail::control_reg<16,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFF0FFFFFFF> __ECR898;
/******************************************************************************/
/* ECR: L1D_UTLB_ATTR                                                         */
/* DESCRIPTION: Indexed uTLB Page Attribute Entry                             */
/* INDEX RANGE: [0,15]                                                        */
/* GENERAL RESET VALUE: 0x0                                                   */
/* INDEX 0 RESET VALUE: 0x8000500000000000                                    */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_L1D_UTLB_ATTR __ECR898

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR899;

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFF0001> __ECR900;
/******************************************************************************/
/* ECR: L1D_UTLB_REPL                                                         */
/* DESCRIPTION: uTLB Replacement Policy Register                              */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_L1D_UTLB_REPL __ECR900

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR901;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR902;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR903;

#if defined(__C7100__) || defined(__C7120__)
extern _c70_he_detail::control_reg<8,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFF71FFFFFFFFF> __ECR904;
/******************************************************************************/
/* ECR: L1P_UTLB_MATCH                                                        */
/* DESCRIPTION: Indexed uTLB Page Match Entry                                 */
/* INDEX RANGE: [0,7]                                                         */
/* GENERAL RESET VALUE: 0x0                                                   */
/* INDEX 0 RESET VALUE: 0xF000070000000000                                    */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_L1P_UTLB_MATCH __ECR904
#elif defined(__C7504__) || defined(__C7524__)
extern _c70_he_detail::control_reg<8,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFF71FFFFFFFFF> __ECR904;
/******************************************************************************/
/* ECR: L1P_UTLB_MATCH                                                        */
/* DESCRIPTION: Indexed uTLB Page Match Entry                                 */
/* INDEX RANGE: [0,7]                                                         */
/* GENERAL RESET VALUE: 0x0                                                   */
/* INDEX 0 RESET VALUE: 0xB000070000000000                                    */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_L1P_UTLB_MATCH __ECR904
#endif

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR905;

extern _c70_he_detail::control_reg<8,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFF0FFFFFFF> __ECR906;
/******************************************************************************/
/* ECR: L1P_UTLB_ATTR                                                         */
/* DESCRIPTION: Indexed uTLB Page Attribute Entry                             */
/* INDEX RANGE: [0,7]                                                         */
/* GENERAL RESET VALUE: 0x0                                                   */
/* INDEX 0 RESET VALUE: 0x8000500000000000                                    */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_L1P_UTLB_ATTR __ECR906

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR907;

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFF0001> __ECR908;
/******************************************************************************/
/* ECR: L1P_UTLB_REPL                                                         */
/* DESCRIPTION: uTLB Replacement Policy Register                              */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_L1P_UTLB_REPL __ECR908

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR909;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR910;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR911;

#if defined(__C7100__) || defined(__C7120__)
extern _c70_he_detail::control_reg<8,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFF71FFFFFFFFF> __ECR912;
/******************************************************************************/
/* ECR: SE0_UTLB_MATCH                                                        */
/* DESCRIPTION: Indexed uTLB Page Match Entry                                 */
/* INDEX RANGE: [0,7]                                                         */
/* GENERAL RESET VALUE: 0x0                                                   */
/* INDEX 0 RESET VALUE: 0xF000070000000000                                    */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_SE0_UTLB_MATCH __ECR912
#elif defined(__C7504__) || defined(__C7524__)
extern _c70_he_detail::control_reg<8,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFF71FFFFFFFFF> __ECR912;
/******************************************************************************/
/* ECR: SE0_UTLB_MATCH                                                        */
/* DESCRIPTION: Indexed uTLB Page Match Entry                                 */
/* INDEX RANGE: [0,7]                                                         */
/* GENERAL RESET VALUE: 0x0                                                   */
/* INDEX 0 RESET VALUE: 0xB000070000000000                                    */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_SE0_UTLB_MATCH __ECR912
#endif

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR913;

extern _c70_he_detail::control_reg<8,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFF0FFFFFFF> __ECR914;
/******************************************************************************/
/* ECR: SE0_UTLB_ATTR                                                         */
/* DESCRIPTION: Indexed uTLB Page Attribute Entry                             */
/* INDEX RANGE: [0,7]                                                         */
/* GENERAL RESET VALUE: 0x0                                                   */
/* INDEX 0 RESET VALUE: 0x8000500000000000                                    */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_SE0_UTLB_ATTR __ECR914

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR915;

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFF0001> __ECR916;
/******************************************************************************/
/* ECR: SE0_UTLB_REPL                                                         */
/* DESCRIPTION: uTLB Replacement Policy Register                              */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_SE0_UTLB_REPL __ECR916

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR917;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR918;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR919;

#if defined(__C7100__) || defined(__C7120__)
extern _c70_he_detail::control_reg<8,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFF71FFFFFFFFF> __ECR920;
/******************************************************************************/
/* ECR: SE1_UTLB_MATCH                                                        */
/* DESCRIPTION: Indexed uTLB Page Match Entry                                 */
/* INDEX RANGE: [0,7]                                                         */
/* GENERAL RESET VALUE: 0x0                                                   */
/* INDEX 0 RESET VALUE: 0xF000070000000000                                    */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_SE1_UTLB_MATCH __ECR920
#elif defined(__C7504__) || defined(__C7524__)
extern _c70_he_detail::control_reg<8,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFF71FFFFFFFFF> __ECR920;
/******************************************************************************/
/* ECR: SE1_UTLB_MATCH                                                        */
/* DESCRIPTION: Indexed uTLB Page Match Entry                                 */
/* INDEX RANGE: [0,7]                                                         */
/* GENERAL RESET VALUE: 0x0                                                   */
/* INDEX 0 RESET VALUE: 0xB000070000000000                                    */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_SE1_UTLB_MATCH __ECR920
#endif

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR921;

extern _c70_he_detail::control_reg<8,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFF0FFFFFFF> __ECR922;
/******************************************************************************/
/* ECR: SE1_UTLB_ATTR                                                         */
/* DESCRIPTION: Indexed uTLB Page Attribute Entry                             */
/* INDEX RANGE: [0,7]                                                         */
/* GENERAL RESET VALUE: 0x0                                                   */
/* INDEX 0 RESET VALUE: 0x8000500000000000                                    */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_SE1_UTLB_ATTR __ECR922

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR923;

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFF0001> __ECR924;
/******************************************************************************/
/* ECR: SE1_UTLB_REPL                                                         */
/* DESCRIPTION: uTLB Replacement Policy Register                              */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_SE1_UTLB_REPL __ECR924

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR925;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR926;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR927;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR928;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR929;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR930;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR931;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR932;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR933;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR934;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR935;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR936;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR937;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR938;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR939;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR940;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR941;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR942;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR943;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR944;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR945;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR946;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR947;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR948;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR949;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR950;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR951;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR952;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR953;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR954;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR955;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR956;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR957;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR958;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR959;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR960;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR961;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR962;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR963;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR964;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR965;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR966;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR967;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR968;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR969;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR970;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR971;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR972;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR973;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR974;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR975;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR976;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR977;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR978;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR979;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR980;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR981;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR982;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR983;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR984;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR985;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR986;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR987;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR988;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR989;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR990;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR991;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR992;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR993;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR994;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR995;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR996;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR997;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR998;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR999;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1000;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1001;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1002;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1003;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1004;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1005;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1006;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1007;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1008;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1009;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1010;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1011;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1012;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1013;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1014;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1015;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1016;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1017;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1018;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1019;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1020;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1021;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1022;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1023;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1024;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1025;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1026;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1027;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1028;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1029;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1030;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1031;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1032;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1033;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1034;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1035;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1036;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1037;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1038;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1039;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1040;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1041;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1042;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1043;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1044;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1045;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1046;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1047;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1048;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1049;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1050;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1051;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1052;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1053;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1054;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1055;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1056;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1057;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1058;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1059;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1060;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1061;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1062;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1063;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1064;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1065;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1066;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1067;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1068;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1069;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1070;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1071;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1072;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1073;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1074;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1075;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1076;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1077;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1078;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1079;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1080;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1081;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1082;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1083;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1084;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1085;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1086;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1087;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1088;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1089;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1090;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1091;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1092;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1093;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1094;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1095;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1096;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1097;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1098;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1099;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1100;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1101;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1102;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1103;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1104;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1105;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1106;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1107;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1108;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1109;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1110;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1111;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1112;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1113;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1114;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1115;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1116;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1117;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1118;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1119;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1120;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1121;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1122;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1123;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1124;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1125;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1126;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1127;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1128;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1129;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1130;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1131;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1132;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1133;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1134;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1135;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1136;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1137;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1138;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1139;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1140;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1141;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1142;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1143;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1144;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1145;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1146;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1147;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1148;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1149;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1150;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1151;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1152;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1153;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1154;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1155;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1156;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1157;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1158;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1159;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1160;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1161;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1162;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1163;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1164;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1165;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1166;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1167;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1168;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1169;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1170;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1171;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1172;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1173;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1174;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1175;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1176;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1177;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1178;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1179;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1180;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1181;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1182;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1183;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1184;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1185;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1186;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1187;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1188;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1189;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1190;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1191;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1192;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1193;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1194;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1195;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1196;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1197;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1198;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1199;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1200;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1201;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1202;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1203;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1204;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1205;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1206;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1207;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1208;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1209;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1210;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1211;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1212;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1213;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1214;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1215;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1216;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1217;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1218;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1219;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1220;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1221;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1222;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1223;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1224;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1225;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1226;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1227;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1228;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1229;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1230;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1231;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1232;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1233;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1234;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1235;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1236;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1237;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1238;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1239;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1240;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1241;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1242;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1243;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1244;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1245;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1246;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1247;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1248;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1249;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1250;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1251;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1252;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1253;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1254;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1255;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1256;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1257;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1258;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1259;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1260;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1261;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1262;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1263;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1264;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1265;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1266;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1267;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1268;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1269;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1270;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1271;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1272;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1273;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1274;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1275;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1276;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1277;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1278;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1279;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1280;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1281;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1282;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1283;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1284;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1285;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1286;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1287;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1288;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1289;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1290;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1291;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1292;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1293;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1294;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1295;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1296;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1297;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1298;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1299;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1300;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1301;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1302;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1303;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1304;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1305;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1306;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1307;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1308;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1309;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1310;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1311;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1312;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1313;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1314;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1315;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1316;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1317;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1318;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1319;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1320;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1321;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1322;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1323;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1324;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1325;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1326;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1327;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1328;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1329;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1330;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1331;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1332;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1333;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1334;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1335;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1336;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1337;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1338;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1339;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1340;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1341;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1342;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1343;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1344;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1345;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1346;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1347;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1348;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1349;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1350;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1351;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1352;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1353;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1354;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1355;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1356;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1357;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1358;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1359;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1360;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1361;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1362;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1363;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1364;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1365;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1366;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1367;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1368;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1369;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1370;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1371;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1372;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1373;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1374;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1375;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1376;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1377;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1378;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1379;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1380;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1381;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1382;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1383;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1384;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1385;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1386;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1387;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1388;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1389;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1390;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1391;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1392;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1393;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1394;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1395;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1396;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1397;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1398;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1399;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1400;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1401;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1402;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1403;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1404;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1405;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1406;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1407;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1408;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1409;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1410;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1411;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1412;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1413;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1414;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1415;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1416;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1417;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1418;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1419;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1420;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1421;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1422;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1423;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1424;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1425;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1426;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1427;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1428;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1429;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1430;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1431;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1432;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1433;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1434;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1435;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1436;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1437;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1438;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1439;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1440;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1441;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1442;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1443;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1444;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1445;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1446;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1447;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1448;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1449;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1450;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1451;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1452;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1453;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1454;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1455;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1456;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1457;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1458;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1459;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1460;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1461;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1462;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1463;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1464;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1465;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1466;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1467;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1468;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1469;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1470;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1471;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1472;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1473;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1474;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1475;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1476;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1477;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1478;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1479;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1480;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1481;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1482;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1483;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1484;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1485;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1486;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1487;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1488;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1489;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1490;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1491;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1492;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1493;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1494;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1495;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1496;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1497;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1498;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1499;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1500;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1501;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1502;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1503;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1504;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1505;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1506;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1507;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1508;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1509;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1510;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1511;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1512;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1513;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1514;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1515;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1516;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1517;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1518;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1519;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1520;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1521;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1522;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1523;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1524;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1525;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1526;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1527;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1528;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1529;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1530;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1531;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1532;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1533;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1534;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1535;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1536;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1537;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1538;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1539;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1540;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1541;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1542;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1543;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1544;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1545;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1546;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1547;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1548;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1549;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1550;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1551;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1552;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1553;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1554;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1555;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1556;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1557;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1558;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1559;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1560;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1561;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1562;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1563;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1564;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1565;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1566;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1567;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1568;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1569;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1570;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1571;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1572;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1573;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1574;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1575;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1576;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1577;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1578;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1579;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1580;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1581;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1582;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1583;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1584;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1585;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1586;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1587;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1588;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1589;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1590;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1591;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1592;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1593;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1594;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1595;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1596;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1597;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1598;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1599;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1600;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1601;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1602;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1603;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1604;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1605;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1606;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1607;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1608;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1609;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1610;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1611;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1612;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1613;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1614;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1615;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1616;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1617;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1618;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1619;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1620;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1621;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1622;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1623;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1624;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1625;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1626;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1627;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1628;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1629;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1630;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1631;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1632;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1633;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1634;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1635;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1636;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1637;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1638;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1639;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1640;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1641;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1642;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1643;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1644;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1645;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1646;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1647;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1648;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1649;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1650;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1651;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1652;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1653;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1654;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1655;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1656;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1657;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1658;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1659;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1660;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1661;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1662;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1663;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1664;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1665;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1666;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1667;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1668;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1669;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1670;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1671;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1672;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1673;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1674;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1675;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1676;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1677;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1678;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1679;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1680;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1681;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1682;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1683;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1684;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1685;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1686;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1687;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1688;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1689;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1690;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1691;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1692;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1693;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1694;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1695;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1696;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1697;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1698;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1699;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1700;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1701;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1702;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1703;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1704;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1705;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1706;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1707;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1708;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1709;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1710;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1711;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1712;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1713;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1714;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1715;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1716;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1717;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1718;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1719;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1720;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1721;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1722;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1723;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1724;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1725;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1726;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1727;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1728;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1729;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1730;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1731;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1732;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1733;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1734;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1735;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1736;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1737;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1738;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1739;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1740;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1741;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1742;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1743;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1744;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1745;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1746;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1747;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1748;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1749;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1750;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1751;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1752;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1753;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1754;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1755;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1756;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1757;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1758;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1759;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1760;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1761;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1762;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1763;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1764;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1765;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1766;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1767;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1768;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1769;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1770;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1771;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1772;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1773;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1774;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1775;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1776;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1777;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1778;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1779;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1780;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1781;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1782;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1783;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1784;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1785;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1786;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1787;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1788;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1789;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1790;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1791;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1792;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1793;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1794;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1795;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1796;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1797;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1798;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1799;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1800;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1801;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1802;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1803;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1804;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1805;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1806;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1807;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1808;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1809;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1810;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1811;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1812;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1813;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1814;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1815;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1816;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1817;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1818;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1819;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1820;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1821;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1822;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1823;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1824;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1825;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1826;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1827;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1828;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1829;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1830;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1831;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1832;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1833;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1834;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1835;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1836;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1837;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1838;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1839;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1840;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1841;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1842;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1843;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1844;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1845;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1846;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1847;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1848;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1849;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1850;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1851;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1852;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1853;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1854;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1855;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1856;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1857;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1858;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1859;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1860;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1861;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1862;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1863;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1864;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1865;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1866;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1867;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1868;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1869;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1870;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1871;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1872;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1873;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1874;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1875;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1876;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1877;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1878;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1879;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1880;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1881;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1882;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1883;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1884;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1885;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1886;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1887;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1888;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1889;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1890;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1891;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1892;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1893;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1894;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1895;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1896;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1897;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1898;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1899;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1900;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1901;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1902;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1903;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1904;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1905;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1906;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1907;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1908;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1909;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1910;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1911;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1912;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1913;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1914;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1915;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1916;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1917;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1918;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1919;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1920;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1921;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1922;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1923;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1924;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1925;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1926;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1927;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1928;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1929;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1930;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1931;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1932;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1933;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1934;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1935;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1936;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1937;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1938;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1939;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1940;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1941;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1942;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1943;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1944;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1945;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1946;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1947;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1948;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1949;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1950;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1951;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1952;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1953;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1954;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1955;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1956;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1957;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1958;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1959;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1960;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1961;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1962;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1963;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1964;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1965;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1966;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1967;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1968;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1969;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1970;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1971;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1972;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1973;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1974;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1975;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1976;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1977;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1978;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1979;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1980;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1981;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1982;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1983;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1984;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1985;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1986;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1987;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1988;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1989;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1990;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1991;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1992;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1993;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1994;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1995;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1996;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1997;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1998;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR1999;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2000;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2001;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2002;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2003;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2004;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2005;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2006;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2007;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2008;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2009;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2010;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2011;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2012;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2013;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2014;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2015;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2016;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2017;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2018;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2019;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2020;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2021;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2022;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2023;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2024;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2025;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2026;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2027;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2028;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2029;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2030;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2031;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2032;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2033;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2034;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2035;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2036;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2037;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2038;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2039;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2040;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2041;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2042;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2043;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2044;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2045;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2046;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2047;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2048;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2049;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2050;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2051;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2052;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2053;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2054;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2055;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2056;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2057;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2058;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2059;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2060;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2061;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2062;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2063;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2064;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2065;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2066;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2067;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2068;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2069;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2070;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2071;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2072;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2073;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2074;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2075;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2076;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2077;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2078;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2079;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2080;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2081;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2082;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2083;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2084;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2085;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2086;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2087;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2088;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2089;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2090;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2091;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2092;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2093;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2094;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2095;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2096;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2097;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2098;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2099;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2100;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2101;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2102;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2103;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2104;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2105;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2106;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2107;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2108;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2109;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2110;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2111;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2112;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2113;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2114;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2115;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2116;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2117;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2118;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2119;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2120;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2121;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2122;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2123;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2124;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2125;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2126;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2127;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2128;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2129;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2130;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2131;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2132;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2133;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2134;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2135;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2136;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2137;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2138;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2139;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2140;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2141;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2142;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2143;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2144;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2145;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2146;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2147;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2148;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2149;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2150;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2151;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2152;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2153;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2154;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2155;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2156;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2157;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2158;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2159;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2160;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2161;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2162;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2163;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2164;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2165;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2166;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2167;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2168;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2169;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2170;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2171;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2172;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2173;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2174;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2175;

extern _c70_he_detail::control_reg<1,1,0,0xFFFFFFFF,0x0> __ECR2176;
/******************************************************************************/
/* ECR: TRC_ID                                                                */
/* DESCRIPTION: Trace ID Register                                             */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x62010000                                            */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/*     Secure Supervisor: RO                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RO                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RO                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
#define __ECR_TRC_ID __ECR2176


extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFE,0x1> __ECR2177;
/******************************************************************************/
/* ECR: TRC_OWN                                                               */
/* DESCRIPTION: Trace OWN Register                                            */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_TRC_OWN __ECR2177


extern _c70_he_detail::control_reg<1,1,1,0xFC7FFFFF,0xFFFFFFFF> __ECR2178;
/******************************************************************************/
/* ECR: TRC_CNTL                                                              */
/* DESCRIPTION: Trace Control Register                                        */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_TRC_CNTL __ECR2178


extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFF,0xFFFF> __ECR2179;
/******************************************************************************/
/* ECR: TRC_PER_CNT                                                           */
/* DESCRIPTION: Trace Periodic Counter Register                               */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x400                                                 */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_TRC_PER_CNT __ECR2179


extern _c70_he_detail::control_reg<1,1,0,0xFFFFFFFF,0x0> __ECR2180;
/******************************************************************************/
/* ECR: TRC_STAT                                                              */
/* DESCRIPTION: Trace Status Register                                         */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x7F                                                  */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/*     Secure Supervisor: RO                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RO                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RO                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
#define __ECR_TRC_STAT __ECR2180


extern _c70_he_detail::control_reg<1,1,1,0x55555FFF,0xFFFFFFFF> __ECR2181;
/******************************************************************************/
/* ECR: TRC_TRIG0_CNTL_STAT                                                   */
/* DESCRIPTION: Trace Trigger0 Control and Status Register                    */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_TRC_TRIG0_CNTL_STAT __ECR2181


extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFC5,0x3F> __ECR2182;
/******************************************************************************/
/* ECR: TRC_TRIG1_CNTL_STAT                                                   */
/* DESCRIPTION: Trace Trigger0 Control and Status Register                    */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_TRC_TRIG1_CNTL_STAT __ECR2182


extern _c70_he_detail::control_reg<1,1,0,0xFFFFFFFF,0x0> __ECR2183;
/******************************************************************************/
/* ECR: TRC_TIMESTAMP_CNT_REG0                                                */
/* DESCRIPTION: Trace Time Stamp Counter Register 0                           */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/*     Secure Supervisor: RO                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RO                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RO                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
#define __ECR_TRC_TIMESTAMP_CNT_REG0 __ECR2183


extern _c70_he_detail::control_reg<1,1,0,0xFFFFFFFF,0x0> __ECR2184;
/******************************************************************************/
/* ECR: TRC_TIMESTAMP_CNT_REG1                                                */
/* DESCRIPTION: Trace Time Stamp Counter Register 1                           */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/*     Secure Supervisor: RO                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RO                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RO                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
#define __ECR_TRC_TIMESTAMP_CNT_REG1 __ECR2184


extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFF,0xFFFFFFFF> __ECR2185;
/******************************************************************************/
/* ECR: TRC_EXPT_CNTL                                                         */
/* DESCRIPTION: Trace Export Control Register                                 */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_TRC_EXPT_CNTL __ECR2185


extern _c70_he_detail::control_reg<1,1,0,0xFFFFFFFF,0x0> __ECR2186;
/******************************************************************************/
/* ECR: TRC_EXPT_STAT                                                         */
/* DESCRIPTION: Trace Export Status Register                                  */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x80000002                                            */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/*     Secure Supervisor: RO                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RO                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RO                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
#define __ECR_TRC_EXPT_STAT __ECR2186


extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFF,0x7F> __ECR2187;
/******************************************************************************/
/* ECR: TRC_EXPT_ATID                                                         */
/* DESCRIPTION: Trace Export Trace ID Register                                */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_TRC_EXPT_ATID __ECR2187

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2188;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2189;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2190;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2191;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2192;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2193;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2194;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2195;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2196;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2197;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2198;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2199;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2200;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2201;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2202;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2203;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2204;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2205;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2206;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2207;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2208;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2209;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2210;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2211;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2212;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2213;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2214;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2215;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2216;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2217;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2218;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2219;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2220;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2221;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2222;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2223;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2224;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2225;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2226;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2227;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2228;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2229;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2230;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2231;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2232;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2233;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2234;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2235;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2236;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2237;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2238;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2239;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2240;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2241;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2242;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2243;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2244;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2245;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2246;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2247;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2248;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2249;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2250;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2251;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2252;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2253;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2254;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2255;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2256;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2257;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2258;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2259;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2260;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2261;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2262;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2263;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2264;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2265;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2266;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2267;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2268;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2269;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2270;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2271;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2272;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2273;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2274;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2275;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2276;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2277;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2278;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2279;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2280;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2281;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2282;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2283;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2284;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2285;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2286;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2287;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2288;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2289;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2290;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2291;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2292;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2293;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2294;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2295;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2296;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2297;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2298;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2299;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2300;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2301;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2302;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2303;

extern _c70_he_detail::control_reg<1,1,0,0xFFFFFFFF,0x0> __ECR2304;
/******************************************************************************/
/* ECR: AET_ID                                                                */
/* DESCRIPTION: AET ID                                                        */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x62000100                                            */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/*     Secure Supervisor: RO                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RO                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RO                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
#define __ECR_AET_ID __ECR2304


extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFF,0x1> __ECR2305;
/******************************************************************************/
/* ECR: AET_OWN                                                               */
/* DESCRIPTION: AET Ownership Register                                        */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_AET_OWN __ECR2305


extern _c70_he_detail::control_reg<1,1,0,0xFFFFFFFF,0x0> __ECR2306;
/******************************************************************************/
/* ECR: AET_STAT                                                              */
/* DESCRIPTION: AET Status Register                                           */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/*     Secure Supervisor: RO                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RO                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RO                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
#define __ECR_AET_STAT __ECR2306

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2307;

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFF,0x80000000> __ECR2308;
/******************************************************************************/
/* ECR: AET_EVT                                                               */
/* DESCRIPTION: AET Event Register                                            */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_AET_EVT __ECR2308


extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFF,0x1> __ECR2309;
/******************************************************************************/
/* ECR: AET_PC0                                                               */
/* DESCRIPTION: AET PC0 Register                                              */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_AET_PC0 __ECR2309


extern _c70_he_detail::control_reg<1,1,0,0xFFFFFFFF,0x0> __ECR2310;
/******************************************************************************/
/* ECR: AET_PC1                                                               */
/* DESCRIPTION: AET PC1 Register                                              */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/*     Secure Supervisor: RO                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RO                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RO                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
#define __ECR_AET_PC1 __ECR2310

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2311;

extern _c70_he_detail::control_reg<1,1,1,0x301FFFFF,0xCFE007FF> __ECR2312;
/******************************************************************************/
/* ECR: AET_IAR_ADD                                                           */
/* DESCRIPTION: AET Indirect ADDR Register                                    */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_AET_IAR_ADD __ECR2312


extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFF,0xFFFFFFFF> __ECR2313;
/******************************************************************************/
/* ECR: AET_IAR_DAT                                                           */
/* DESCRIPTION: AET Indirect Data Register                                    */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
#define __ECR_AET_IAR_DAT __ECR2313

extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2314;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2315;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2316;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2317;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2318;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2319;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2320;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2321;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2322;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2323;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2324;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2325;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2326;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2327;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2328;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2329;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2330;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2331;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2332;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2333;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2334;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2335;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2336;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2337;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2338;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2339;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2340;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2341;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2342;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2343;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2344;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2345;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2346;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2347;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2348;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2349;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2350;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2351;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2352;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2353;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2354;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2355;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2356;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2357;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2358;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2359;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2360;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2361;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2362;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2363;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2364;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2365;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2366;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2367;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2368;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2369;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2370;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2371;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2372;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2373;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2374;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2375;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2376;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2377;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2378;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2379;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2380;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2381;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2382;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2383;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2384;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2385;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2386;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2387;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2388;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2389;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2390;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2391;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2392;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2393;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2394;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2395;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2396;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2397;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2398;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2399;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2400;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2401;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2402;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2403;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2404;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2405;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2406;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2407;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2408;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2409;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2410;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2411;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2412;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2413;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2414;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2415;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2416;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2417;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2418;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2419;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2420;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2421;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2422;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2423;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2424;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2425;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2426;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2427;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2428;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2429;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2430;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2431;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2432;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2433;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2434;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2435;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2436;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2437;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2438;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2439;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2440;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2441;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2442;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2443;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2444;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2445;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2446;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2447;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2448;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2449;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2450;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2451;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2452;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2453;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2454;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2455;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2456;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2457;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2458;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2459;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2460;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2461;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2462;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2463;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2464;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2465;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2466;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2467;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2468;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2469;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2470;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2471;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2472;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2473;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2474;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2475;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2476;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2477;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2478;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2479;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2480;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2481;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2482;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2483;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2484;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2485;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2486;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2487;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2488;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2489;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2490;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2491;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2492;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2493;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2494;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2495;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2496;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2497;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2498;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2499;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2500;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2501;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2502;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2503;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2504;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2505;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2506;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2507;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2508;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2509;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2510;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2511;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2512;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2513;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2514;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2515;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2516;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2517;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2518;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2519;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2520;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2521;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2522;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2523;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2524;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2525;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2526;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2527;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2528;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2529;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2530;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2531;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2532;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2533;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2534;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2535;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2536;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2537;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2538;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2539;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2540;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2541;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2542;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2543;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2544;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2545;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2546;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2547;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2548;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2549;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2550;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2551;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2552;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2553;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2554;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2555;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2556;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2557;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2558;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2559;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2560;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2561;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2562;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2563;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2564;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2565;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2566;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2567;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2568;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2569;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2570;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2571;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2572;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2573;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2574;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2575;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2576;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2577;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2578;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2579;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2580;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2581;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2582;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2583;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2584;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2585;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2586;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2587;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2588;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2589;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2590;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2591;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2592;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2593;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2594;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2595;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2596;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2597;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2598;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2599;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2600;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2601;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2602;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2603;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2604;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2605;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2606;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2607;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2608;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2609;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2610;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2611;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2612;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2613;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2614;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2615;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2616;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2617;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2618;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2619;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2620;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2621;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2622;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2623;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2624;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2625;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2626;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2627;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2628;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2629;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2630;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2631;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2632;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2633;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2634;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2635;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2636;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2637;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2638;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2639;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2640;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2641;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2642;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2643;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2644;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2645;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2646;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2647;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2648;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2649;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2650;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2651;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2652;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2653;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2654;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2655;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2656;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2657;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2658;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2659;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2660;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2661;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2662;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2663;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2664;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2665;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2666;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2667;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2668;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2669;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2670;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2671;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2672;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2673;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2674;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2675;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2676;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2677;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2678;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2679;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2680;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2681;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2682;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2683;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2684;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2685;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2686;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2687;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2688;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2689;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2690;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2691;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2692;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2693;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2694;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2695;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2696;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2697;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2698;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2699;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2700;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2701;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2702;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2703;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2704;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2705;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2706;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2707;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2708;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2709;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2710;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2711;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2712;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2713;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2714;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2715;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2716;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2717;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2718;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2719;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2720;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2721;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2722;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2723;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2724;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2725;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2726;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2727;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2728;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2729;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2730;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2731;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2732;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2733;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2734;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2735;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2736;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2737;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2738;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2739;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2740;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2741;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2742;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2743;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2744;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2745;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2746;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2747;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2748;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2749;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2750;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2751;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2752;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2753;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2754;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2755;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2756;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2757;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2758;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2759;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2760;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2761;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2762;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2763;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2764;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2765;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2766;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2767;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2768;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2769;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2770;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2771;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2772;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2773;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2774;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2775;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2776;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2777;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2778;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2779;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2780;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2781;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2782;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2783;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2784;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2785;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2786;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2787;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2788;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2789;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2790;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2791;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2792;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2793;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2794;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2795;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2796;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2797;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2798;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2799;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2800;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2801;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2802;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2803;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2804;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2805;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2806;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2807;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2808;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2809;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2810;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2811;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2812;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2813;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2814;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2815;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2816;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2817;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2818;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2819;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2820;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2821;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2822;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2823;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2824;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2825;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2826;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2827;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2828;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2829;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2830;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2831;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2832;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2833;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2834;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2835;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2836;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2837;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2838;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2839;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2840;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2841;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2842;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2843;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2844;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2845;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2846;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2847;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2848;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2849;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2850;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2851;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2852;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2853;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2854;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2855;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2856;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2857;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2858;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2859;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2860;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2861;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2862;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2863;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2864;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2865;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2866;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2867;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2868;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2869;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2870;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2871;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2872;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2873;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2874;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2875;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2876;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2877;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2878;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2879;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2880;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2881;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2882;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2883;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2884;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2885;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2886;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2887;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2888;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2889;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2890;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2891;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2892;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2893;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2894;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2895;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2896;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2897;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2898;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2899;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2900;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2901;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2902;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2903;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2904;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2905;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2906;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2907;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2908;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2909;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2910;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2911;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2912;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2913;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2914;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2915;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2916;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2917;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2918;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2919;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2920;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2921;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2922;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2923;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2924;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2925;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2926;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2927;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2928;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2929;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2930;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2931;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2932;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2933;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2934;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2935;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2936;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2937;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2938;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2939;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2940;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2941;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2942;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2943;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2944;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2945;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2946;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2947;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2948;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2949;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2950;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2951;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2952;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2953;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2954;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2955;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2956;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2957;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2958;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2959;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2960;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2961;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2962;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2963;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2964;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2965;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2966;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2967;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2968;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2969;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2970;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2971;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2972;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2973;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2974;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2975;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2976;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2977;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2978;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2979;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2980;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2981;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2982;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2983;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2984;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2985;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2986;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2987;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2988;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2989;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2990;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2991;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2992;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2993;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2994;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2995;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2996;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2997;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2998;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR2999;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3000;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3001;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3002;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3003;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3004;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3005;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3006;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3007;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3008;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3009;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3010;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3011;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3012;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3013;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3014;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3015;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3016;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3017;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3018;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3019;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3020;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3021;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3022;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3023;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3024;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3025;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3026;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3027;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3028;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3029;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3030;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3031;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3032;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3033;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3034;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3035;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3036;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3037;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3038;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3039;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3040;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3041;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3042;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3043;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3044;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3045;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3046;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3047;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3048;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3049;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3050;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3051;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3052;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3053;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3054;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3055;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3056;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3057;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3058;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3059;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3060;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3061;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3062;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3063;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3064;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3065;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3066;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3067;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3068;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3069;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3070;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3071;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3072;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3073;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3074;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3075;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3076;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3077;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3078;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3079;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3080;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3081;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3082;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3083;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3084;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3085;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3086;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3087;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3088;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3089;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3090;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3091;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3092;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3093;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3094;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3095;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3096;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3097;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3098;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3099;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3100;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3101;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3102;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3103;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3104;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3105;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3106;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3107;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3108;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3109;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3110;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3111;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3112;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3113;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3114;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3115;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3116;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3117;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3118;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3119;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3120;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3121;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3122;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3123;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3124;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3125;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3126;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3127;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3128;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3129;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3130;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3131;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3132;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3133;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3134;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3135;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3136;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3137;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3138;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3139;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3140;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3141;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3142;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3143;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3144;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3145;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3146;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3147;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3148;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3149;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3150;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3151;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3152;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3153;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3154;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3155;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3156;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3157;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3158;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3159;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3160;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3161;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3162;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3163;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3164;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3165;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3166;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3167;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3168;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3169;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3170;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3171;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3172;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3173;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3174;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3175;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3176;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3177;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3178;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3179;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3180;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3181;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3182;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3183;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3184;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3185;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3186;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3187;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3188;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3189;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3190;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3191;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3192;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3193;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3194;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3195;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3196;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3197;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3198;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3199;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3200;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3201;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3202;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3203;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3204;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3205;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3206;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3207;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3208;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3209;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3210;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3211;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3212;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3213;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3214;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3215;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3216;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3217;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3218;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3219;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3220;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3221;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3222;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3223;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3224;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3225;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3226;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3227;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3228;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3229;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3230;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3231;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3232;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3233;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3234;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3235;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3236;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3237;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3238;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3239;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3240;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3241;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3242;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3243;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3244;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3245;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3246;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3247;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3248;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3249;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3250;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3251;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3252;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3253;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3254;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3255;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3256;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3257;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3258;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3259;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3260;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3261;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3262;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3263;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3264;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3265;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3266;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3267;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3268;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3269;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3270;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3271;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3272;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3273;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3274;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3275;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3276;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3277;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3278;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3279;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3280;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3281;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3282;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3283;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3284;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3285;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3286;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3287;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3288;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3289;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3290;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3291;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3292;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3293;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3294;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3295;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3296;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3297;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3298;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3299;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3300;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3301;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3302;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3303;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3304;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3305;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3306;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3307;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3308;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3309;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3310;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3311;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3312;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3313;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3314;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3315;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3316;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3317;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3318;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3319;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3320;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3321;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3322;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3323;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3324;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3325;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3326;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3327;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3328;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3329;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3330;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3331;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3332;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3333;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3334;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3335;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3336;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3337;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3338;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3339;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3340;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3341;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3342;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3343;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3344;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3345;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3346;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3347;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3348;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3349;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3350;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3351;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3352;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3353;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3354;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3355;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3356;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3357;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3358;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3359;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3360;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3361;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3362;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3363;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3364;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3365;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3366;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3367;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3368;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3369;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3370;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3371;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3372;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3373;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3374;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3375;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3376;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3377;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3378;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3379;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3380;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3381;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3382;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3383;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3384;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3385;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3386;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3387;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3388;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3389;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3390;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3391;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3392;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3393;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3394;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3395;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3396;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3397;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3398;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3399;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3400;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3401;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3402;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3403;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3404;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3405;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3406;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3407;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3408;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3409;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3410;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3411;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3412;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3413;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3414;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3415;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3416;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3417;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3418;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3419;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3420;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3421;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3422;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3423;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3424;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3425;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3426;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3427;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3428;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3429;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3430;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3431;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3432;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3433;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3434;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3435;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3436;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3437;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3438;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3439;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3440;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3441;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3442;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3443;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3444;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3445;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3446;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3447;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3448;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3449;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3450;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3451;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3452;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3453;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3454;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3455;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3456;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3457;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3458;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3459;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3460;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3461;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3462;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3463;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3464;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3465;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3466;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3467;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3468;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3469;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3470;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3471;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3472;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3473;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3474;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3475;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3476;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3477;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3478;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3479;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3480;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3481;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3482;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3483;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3484;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3485;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3486;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3487;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3488;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3489;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3490;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3491;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3492;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3493;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3494;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3495;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3496;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3497;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3498;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3499;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3500;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3501;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3502;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3503;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3504;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3505;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3506;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3507;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3508;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3509;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3510;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3511;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3512;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3513;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3514;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3515;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3516;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3517;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3518;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3519;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3520;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3521;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3522;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3523;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3524;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3525;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3526;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3527;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3528;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3529;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3530;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3531;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3532;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3533;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3534;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3535;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3536;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3537;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3538;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3539;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3540;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3541;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3542;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3543;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3544;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3545;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3546;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3547;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3548;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3549;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3550;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3551;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3552;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3553;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3554;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3555;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3556;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3557;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3558;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3559;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3560;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3561;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3562;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3563;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3564;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3565;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3566;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3567;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3568;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3569;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3570;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3571;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3572;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3573;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3574;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3575;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3576;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3577;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3578;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3579;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3580;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3581;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3582;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3583;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3584;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3585;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3586;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3587;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3588;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3589;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3590;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3591;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3592;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3593;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3594;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3595;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3596;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3597;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3598;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3599;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3600;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3601;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3602;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3603;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3604;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3605;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3606;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3607;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3608;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3609;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3610;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3611;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3612;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3613;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3614;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3615;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3616;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3617;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3618;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3619;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3620;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3621;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3622;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3623;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3624;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3625;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3626;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3627;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3628;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3629;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3630;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3631;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3632;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3633;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3634;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3635;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3636;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3637;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3638;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3639;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3640;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3641;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3642;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3643;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3644;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3645;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3646;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3647;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3648;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3649;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3650;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3651;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3652;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3653;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3654;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3655;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3656;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3657;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3658;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3659;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3660;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3661;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3662;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3663;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3664;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3665;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3666;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3667;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3668;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3669;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3670;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3671;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3672;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3673;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3674;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3675;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3676;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3677;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3678;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3679;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3680;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3681;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3682;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3683;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3684;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3685;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3686;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3687;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3688;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3689;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3690;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3691;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3692;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3693;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3694;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3695;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3696;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3697;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3698;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3699;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3700;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3701;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3702;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3703;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3704;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3705;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3706;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3707;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3708;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3709;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3710;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3711;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3712;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3713;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3714;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3715;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3716;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3717;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3718;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3719;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3720;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3721;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3722;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3723;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3724;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3725;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3726;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3727;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3728;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3729;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3730;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3731;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3732;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3733;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3734;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3735;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3736;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3737;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3738;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3739;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3740;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3741;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3742;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3743;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3744;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3745;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3746;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3747;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3748;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3749;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3750;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3751;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3752;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3753;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3754;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3755;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3756;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3757;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3758;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3759;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3760;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3761;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3762;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3763;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3764;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3765;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3766;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3767;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3768;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3769;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3770;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3771;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3772;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3773;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3774;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3775;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3776;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3777;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3778;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3779;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3780;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3781;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3782;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3783;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3784;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3785;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3786;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3787;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3788;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3789;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3790;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3791;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3792;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3793;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3794;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3795;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3796;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3797;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3798;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3799;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3800;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3801;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3802;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3803;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3804;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3805;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3806;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3807;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3808;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3809;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3810;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3811;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3812;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3813;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3814;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3815;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3816;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3817;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3818;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3819;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3820;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3821;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3822;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3823;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3824;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3825;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3826;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3827;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3828;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3829;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3830;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3831;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3832;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3833;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3834;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3835;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3836;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3837;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3838;
extern _c70_he_detail::control_reg<1,1,1,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF> __ECR3839;

#endif /* C7X_ECR_H_ */
