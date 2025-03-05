/*****************************************************************************/
/*  C7X_HOST_EMULATION.H v#####                                              */
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

/*****************************************************************************/
/*  This is the top level required for all C7000 host emulation programs.    */
/*  When writing a program for use with the C7000 host emulation package,    */
/*  the macro __C7X_HOSTEM__ should be defined on the command line. This     */
/*  can be used to differentiate host emulation code from target code if     */
/*  needed. Section 3.3 of the C7000 Host Emulation User's guide contains an */
/*  example program that illustrates how to include this header and the      */
/*  __C7X_HOSTEM__ macro.                                                    */
/*****************************************************************************/

#ifndef C7X_HOSTEM_H
#define C7X_HOSTEM_H

#define __C7X_HOSTEM__ 1

#define __C7000__ 1
#define __little_endian__ 1

#include "vector.h"
#include "c7x_he_strm.h"
#include "c7x_he_strm_struct.h"
#include "c7x_he_luthist.h"
#include "c7x_he_mma.h"
#include "c7x_he_intrinsics.h"
#include "c7x_he_load_stores.h"
#include "c7x_he_cr.h"
#include "vector_funcs.h"
#include "c6x_he_migration.h"

#endif /* C7X_HOSTEM_H */
