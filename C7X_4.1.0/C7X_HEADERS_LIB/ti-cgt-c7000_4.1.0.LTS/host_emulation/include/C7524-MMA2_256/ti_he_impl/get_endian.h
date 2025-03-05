/*****************************************************************************/
/*  GET_ENDIAN.H                                                             */
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

/*** START CG ADD ***/
#define BYTE_LE
/*** END CG ADD ***/

#if defined(__arm__) && !defined(__BIG_ENDIAN) && !defined(__LITTLE_ENDIAN)
#   define __LITTLE_ENDIAN
#endif

#  if !defined(BYTE_BE) && !defined(BYTE_LE)
#    include <endian.h>
#    ifndef __BYTE_ORDER
#      error Please manually set your machine endian in 'config.h'
#    endif
#    if __BYTE_ORDER==4321
#      define BYTE_BE
#    endif
#    if __BYTE_ORDER==1234
#      define BYTE_LE
#    endif
#    if !defined(BYTE_BE) && !defined(BYTE_LE)
#      error Cannot determine target endian.  See 'endian.hpp' for details.
#    endif
#  endif

#if !defined(BYTE_BE) && !defined(BYTE_LE)
#  if defined(__BIG_ENDIAN__) || \
      defined(__BIG_ENDIAN)   || \
      defined( _BIG_ENDIAN)
#    define BYTE_BE
#  endif

#  if defined(__LITTLE_ENDIAN__) || \
      defined(__LITTLE_ENDIAN)   || \
      defined( _LITTLE_ENDIAN)
#    define BYTE_LE
#  endif

#  if !(defined(BYTE_BE) || defined(BYTE_LE)) && \
       (defined(sparc)   || defined(__sparc)    || defined(__sparc__)   || \
        defined(sparc64) || defined(__sparc64)  || defined(__sparc64__) || \
        defined(ppc)     || defined(__ppc)      || defined(__ppc__)     || \
        defined(ppc64)   || defined(__ppc64)    || defined(__ppc64__)   || \
        defined(POWERPC) || defined(__POWERPC)  || defined(__POWERPC__))
#    define BYTE_BE    
#  endif

#  if !(defined(BYTE_BE) || defined(BYTE_LE)) && \
       (defined(i386)    || defined(__i386)     || defined(__i386__)    || \
        defined(x86_64)  || defined(__x86_64)   || defined(__x86_64__)  || \
        defined(amd64)   || defined(__amd64)    || defined(__amd64__)   || \
        defined(ia64)    || defined(__ia64)     || defined(__ia64__)    || \
        defined(alpha)   || defined(__alpha)    || defined(__alpha__)) 
#    define BYTE_LE
#  endif
#endif

#if defined(BYTE_BE) && defined(BYTE_LE)
#  error Both BYTE_BE and BYTE_LE defined.  Pick only 1!
#endif

#if !defined(BYTE_BE) && !defined(BYTE_LE)
#  error One of BYTE_BE or BYTE_LE must be defined.
#endif
