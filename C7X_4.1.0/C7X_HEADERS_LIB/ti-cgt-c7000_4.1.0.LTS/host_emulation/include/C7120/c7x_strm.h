/*****************************************************************************/
/*  C7X_STRM.H                                                               */
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

#ifndef C7X_STRM_H_
#define C7X_STRM_H_

#include <stdint.h>
#include <c7x_ecr.h>
#include <ti_he_impl/streaming_engine.h>
#include <ti_he_impl/sa_generator.h>
#include <ti_he_impl/vector.h>

#ifndef _WIN32
    #define PACKED_STRUCT_BEG(name) \
        typedef struct __attribute__((__packed__)) name##_t {
    #define PACKED_STRUCT_END(name) } name;
#else
    #define PACKED_STRUCT_BEG(name) \
        typedef struct name##_t {
    #define PACKED_STRUCT_END(name) } name;
#endif

/******************************************************************************/
/* SE/SA Feature Support                                                      */
/******************************************************************************/
#if defined(__C7100__)
  #define __SE_FEAT_TEMPLATE_V1 1
#elif defined(__C7120__)
  #define __SE_FEAT_TEMPLATE_V1 1
  #define __SE_FEAT_TEMPLATE_V2 1
  #define __SE_FEAT_TEMPLATE_V3 1
  #define __SE_FEAT_NONZERO_FILLVAL 1
#elif defined(__C7504__) || defined(__C7524__)
  #define __SE_FEAT_TEMPLATE_V1 1
  #define __SE_FEAT_TEMPLATE_V2 1
  #define __SE_FEAT_TEMPLATE_V3 1
  #define __SE_FEAT_NONZERO_FILLVAL 1
  #define __SE_FEAT_SUB_ELEM_EXPANSION 1
  #define __SE_FEAT_FLOAT 1
  #define __SE_FEAT_SPARSITY 1
#else
  #error "Unknown SE/SA feature configuration"
#endif

extern streaming_engine SE0;
extern streaming_engine SE1;

extern sa_generator SA0;
extern sa_generator SA1;
extern sa_generator SA2;
extern sa_generator SA3;

/*----------------------------------------------------------------------------*/
/* Streaming Engine element type options.                                     */
/* Use the below enumeration to indicate the element type of data read via    */
/* streaming engine.                                                          */
/*----------------------------------------------------------------------------*/
typedef enum __SE_ELETYPE
{
    __SE_ELETYPE_8BIT = 0,
    __SE_ELETYPE_16BIT = 1,
    __SE_ELETYPE_32BIT = 2,
    __SE_ELETYPE_64BIT = 3,
    /* reserved = 4 */
#if defined(__SE_FEAT_SUB_ELEM_EXPANSION)
    __SE_ELETYPE_DUAL_4BIT = 5,
    __SE_ELETYPE_QUAD_2BIT = 6,
    __SE_ELETYPE_OCT_1BIT = 7,
#endif /* __SE_FEAT_SUB_ELEM_EXPANSION */
    __SE_ELETYPE_8BIT_CMPLX_NOSWAP = 8,
    __SE_ELETYPE_16BIT_CMPLX_NOSWAP = 9,
    __SE_ELETYPE_32BIT_CMPLX_NOSWAP = 10,
    __SE_ELETYPE_64BIT_CMPLX_NOSWAP = 11,
    __SE_ELETYPE_8BIT_CMPLX_SWAP = 12,
    __SE_ELETYPE_16BIT_CMPLX_SWAP = 13,
    __SE_ELETYPE_32BIT_CMPLX_SWAP = 14,
    __SE_ELETYPE_64BIT_CMPLX_SWAP = 15,
    __SE_ELETYPE_LAST = 15 /* Don't use directly. */
} __SE_ELETYPE;

#if defined(__SE_FEAT_TEMPLATE_V1)
/*----------------------------------------------------------------------------*/
/* Streaming Engine transpose options.                                        */
/* Use the below enumeration to indicate the transpose settings.              */
/* Transpose "GRANULES" are of below sizes only.                              */
/*----------------------------------------------------------------------------*/
typedef enum __SE_TRANSPOSE
{
    __SE_TRANSPOSE_OFF = 0,
    __SE_TRANSPOSE_8BIT = 1,
    __SE_TRANSPOSE_16BIT = 2,
    __SE_TRANSPOSE_32BIT = 3,
    __SE_TRANSPOSE_64BIT = 4,
    __SE_TRANSPOSE_128BIT = 5,
#if __C7X_VEC_SIZE_BITS__ > 256
    __SE_TRANSPOSE_256BIT = 6,
#endif /* __C7X_VEC_SIZE_BITS__ > 256 */
    /* reserved = 7 */
    __SE_TRANSPOSE_LAST = 7 /* Don't use directly. */
} __SE_TRANSPOSE;
#endif /* __SE_FEAT_TEMPLATE_V1 */

/*----------------------------------------------------------------------------*/
/* Streaming Engine promote options.                                          */
/* Single power of 2 promotes are possible using below options.               */
/* Additionally the promotes can be sign or zero extended.                    */
/* Ex. If ELETYPE is 8bit the promoting it would result in 16 bit data.       */
/*----------------------------------------------------------------------------*/
/* When using __SE_FILLVAL_MIN or __SE_FILLVAL_MAX, specify __SE_PROMOTE_OFF  */
/* to generate an unsigned min or max. Specify __SE_PROMOTE_OFF_SIGNED to     */
/* generate a signed min or max. Otherwise, __SE_PROMOTE_OFF_SIGNED behaves   */
/* identically to __SE_PROMOTE_OFF.                                           */
/*----------------------------------------------------------------------------*/
typedef enum __SE_PROMOTE
{
    __SE_PROMOTE_OFF = 0,
    __SE_PROMOTE_2X_ZEROEXT = 1,
    __SE_PROMOTE_4X_ZEROEXT = 2,
    __SE_PROMOTE_8X_ZEROEXT = 3,
#if defined(__SE_FEAT_NONZERO_FILLVAL)
    __SE_PROMOTE_OFF_SIGNED = 4,
#endif /* __SE_FEAT_NONZERO_FILLVAL */
    __SE_PROMOTE_2X_SIGNEXT = 5,
    __SE_PROMOTE_4X_SIGNEXT = 6,
    __SE_PROMOTE_8X_SIGNEXT = 7,
    __SE_PROMOTE_LAST = 7 /* Don't use directly. */
} __SE_PROMOTE;

/*----------------------------------------------------------------------------*/
/* Streaming Engine vector lengths.                                           */
/* Use the below enumeration to indicate the vector lengths in powers of two. */
/* The vector lengths should be in multiples of ELETYPE.                      */
/* Ex. If the vector length is __SE_VECLEN_4ELEMS and __SE_ELETYPE_16BIT then */
/*     the data in the holding registers will contain 4 16 bit values for     */
/*     each SE advance. The rest of the SB0, SB1 register will be zeroed out. */
/*----------------------------------------------------------------------------*/
typedef enum __SE_VECLEN
{
    __SE_VECLEN_1ELEM = 0,
    __SE_VECLEN_2ELEMS = 1,
    __SE_VECLEN_4ELEMS = 2,
    __SE_VECLEN_8ELEMS = 3,
    __SE_VECLEN_16ELEMS = 4,
    __SE_VECLEN_32ELEMS = 5,
    __SE_VECLEN_64ELEMS = 6,
    /* reserved = 7 */
    __SE_VECLEN_LAST = 7 /* Don't use directly. */
} __SE_VECLEN;

#if defined(__SE_FEAT_TEMPLATE_V1)
/*----------------------------------------------------------------------------*/
/* Streaming Engine element duplication.                                      */
/* Use the below enumeration to duplicate the vector elements in powers of    */
/* two, 2x, 4x, 8x, 16x, 32x, 64x (subject to ELETYPE).                       */
/* Ex. Using __SE_ELEDUP_32X for a ELETYPE_16BIT duplicates 16bit elements    */
/*     32 times in SB0/SB1 double vector.                                     */
/*----------------------------------------------------------------------------*/
typedef enum __SE_ELEDUP
{
    __SE_ELEDUP_OFF = 0,
    __SE_ELEDUP_2X = 1,
    __SE_ELEDUP_4X = 2,
    __SE_ELEDUP_8X = 3,
    __SE_ELEDUP_16X = 4,
    __SE_ELEDUP_32X = 5,
#if __C7X_VEC_SIZE_BYTES__ > 32
    __SE_ELEDUP_64X = 6,
#endif /* __C7X_VEC_SIZE_BYTES__ > 32 */
    /* reserved = 7 */
    __SE_ELEDUP_LAST = 7 /* Don't use directly. */
} __SE_ELEDUP;
#endif /* __SE_FEAT_TEMPLATE_V1 */

#if defined(__SE_FEAT_TEMPLATE_V1)
/*----------------------------------------------------------------------------*/
/* Streaming Engine group duplication.                                        */
/* Depending on the vector lengths, enabling group duplication will fill up   */
/* 512bit holding registers with multiple copies.                             */
/* Ex. For __SE_ELETYPE_8BIT and __SE_VECLEN_4ELEMS with group duplication    */
/*     enabled, the streaming engine duplicates the 4 bytes in LSB 16 times   */
/*     to fill up the 512 bit vector holding register.                        */
/*----------------------------------------------------------------------------*/
typedef enum __SE_GRPDUP
{
    __SE_GRPDUP_OFF = 0,
    __SE_GRPDUP_ON = 1,
    __SE_GRPDUP_LAST = 1 /* Don't use directly. */
} __SE_GRPDUP;
#endif /* __SE_FEAT_TEMPLATE_V1 */

/*----------------------------------------------------------------------------*/
/* Streaming Engine decimation flags.                                         */
/* Use the below enumerations to indicate if the SE should decimate (only     */
/* keep every nth element.)                                                   */
/*----------------------------------------------------------------------------*/
typedef enum __SE_DECIM
{
    __SE_DECIM_OFF = 0,
    __SE_DECIM_2 = 1,
    __SE_DECIM_4 = 2,
    /* reserved = 3 */
    __SE_DECIM_LAST = 3 /* Don't use directly. */
} __SE_DECIM;

/*----------------------------------------------------------------------------*/
/* Streaming Engine fillval options.                                          */
/* Specifies the padding method for use with DECDIM, SPAD, LEZR, end of ICNT, */
/* or end of stream. If VECLEN does not fill all lanes of data and GRPDUP is  */
/* not enabled, the SE will only fill masked elements within VECLEN with      */
/* non-zero data. Elements outside of VECLEN will still be filled with 0s.    */
/*----------------------------------------------------------------------------*/
/* When using __SE_FILLVAL_USER, the fill value must be set in the            */
/* corresponding sideband ECR before opening the stream. The sideband ECRs    */
/* are:                                                                       */
/* - __ECR_SE0_SBND                                                           */
/* - __ECR_SE1_SBND                                                           */
/*----------------------------------------------------------------------------*/
typedef enum __SE_FILLVAL
{
    __SE_FILLVAL_ZERO = 0,
#if defined(__SE_FEAT_NONZERO_FILLVAL)
    __SE_FILLVAL_USER = 1,
    __SE_FILLVAL_MIN = 2,
    __SE_FILLVAL_MAX = 3,
#endif /* __SE_FEAT_NONZERO_FILLVAL */
    __SE_FILLVAL_LAST = 3 /* Don't use directly. */
} __SE_FILLVAL;

/*----------------------------------------------------------------------------*/
/* Template format selection for Streaming Engine                             */
/*----------------------------------------------------------------------------*/
typedef enum __SE_DIMFMT
{
    __SE_DIMFMT_1D = 0,
    __SE_DIMFMT_2D = 1,
    __SE_DIMFMT_3D = 2,
    __SE_DIMFMT_4D = 3,
    __SE_DIMFMT_5D = 4,
    __SE_DIMFMT_6D = 5,
    /* reserved = 6 */
    /* reserved = 7 */
    __SE_DIMFMT_LAST = 7 /* Don't use directly. */
} __SE_DIMFMT;

#if defined(__SE_FEAT_TEMPLATE_V1)
/*----------------------------------------------------------------------------*/
/* Streaming Engine increment/decrement directions.                           */
/* Use the below enumerations as needed to indicate the direction of transfer.*/
/* Setting to _INC mode increments the resulting address.                     */
/* Setting to _DEC mode decrements the resulting address.                     */
/*----------------------------------------------------------------------------*/
typedef enum __SE_DIR
{
    __SE_DIR_INC = 0,
    __SE_DIR_DEC = 1,
    __SE_DIR_LAST = 1 /* Don't use directly. */
} __SE_DIR;
#endif /* __SE_FEAT_TEMPLATE_V1 */

/*----------------------------------------------------------------------------*/
/* Streaming Engine Addressing Mode selection options.                        */
/* Choose either linear addressing or use CBK0 or CBK0+CBK1+1                 */
/*----------------------------------------------------------------------------*/
typedef enum __SE_AM
{
    __SE_AM_LINEAR = 0,
    __SE_AM_CIRC_CBK0 = 1,
    __SE_AM_CIRC_CBK1 = 2,
    /* reserved = 3 */
    __SE_AM_LAST = 3 /* Don't use directly. */
} __SE_AM;

/*----------------------------------------------------------------------------*/
/* Streaming Engine Data Strip Mining Decrement Dimension for innermost ICNT0 */
/* In this mode, the current I0 count is NOT reloaded with ICNT0 when each    */
/* dimension expires. Rather, when the selected DECDIM dimension is entered,  */
/* the current I0 count is decremented by the value of VECLEN when in Linear  */
/* Stream mode, or decremented by the GRANULE value when in Transpose Mode.   */
/* The I0 count is only reloaded when the selected DECDIM dimension expires,  */
/* or a dimension higher above it expires.                                    */
/*----------------------------------------------------------------------------*/
typedef enum __SE_DECDIM
{
    __SE_DECDIM_DIM0 = 0,
    __SE_DECDIM_DIM1 = 1,
    __SE_DECDIM_DIM2 = 2,
    __SE_DECDIM_DIM3 = 3,
    __SE_DECDIM_DIM4 = 4,
    __SE_DECDIM_DIM5 = 5,
    /* reserved = 6 */
    /* reserved = 7 */
    __SE_DECDIM_LAST = 7 /* Don't use directly. */
} __SE_DECDIM;

#if defined(__SE_FEAT_TEMPLATE_V3)
/*----------------------------------------------------------------------------*/
/* Streaming Engine SPAD Horizontal Block Dimension                           */
/*----------------------------------------------------------------------------*/
typedef enum __SE_SPAD_HORIZONTAL_BLOCK_DIM
{
    __SE_SPAD_HORIZONTAL_BLOCK_DIM0 = 0,
    __SE_SPAD_HORIZONTAL_BLOCK_DIM1 = 1,
    __SE_SPAD_HORIZONTAL_BLOCK_DIM2 = 2,
    __SE_SPAD_HORIZONTAL_BLOCK_DIM3 = 3,
    __SE_SPAD_HORIZONTAL_BLOCK_DIM4 = 4,
    __SE_SPAD_HORIZONTAL_BLOCK_DIM5 = 5,
    /* reserved = 6 */
    /* reserved = 7 */
    __SE_SPAD_HORIZONTAL_BLOCK_DIM_LAST = 7 /* Don't use directly. */
} __SE_SPAD_HORIZONTAL_BLOCK_DIM;
#endif /* __SE_FEAT_TEMPLATE_V3 */

/*----------------------------------------------------------------------------*/
/* Streaming Engine Secondary Data Strip Mining Decrement Dimension           */
/*----------------------------------------------------------------------------*/
typedef enum __SE_DECDIMSD
{
    __SE_DECDIMSD_DIM0 = 0,
    __SE_DECDIMSD_DIM1 = 1,
    __SE_DECDIMSD_DIM2 = 2,
    __SE_DECDIMSD_DIM3 = 3,
    __SE_DECDIMSD_LAST = 3 /* Don't use directly. */
} __SE_DECDIMSD;

#if defined(__SE_FEAT_TEMPLATE_V3)
/*----------------------------------------------------------------------------*/
/* Streaming Engine SPAD Horizontal Pixel Dimension                           */
/*----------------------------------------------------------------------------*/
typedef enum __SE_SPAD_HORIZONTAL_PIXEL_DIM
{
    __SE_SPAD_HORIZONTAL_PIXEL_DIM0 = 0,
    __SE_SPAD_HORIZONTAL_PIXEL_DIM1 = 1,
    __SE_SPAD_HORIZONTAL_PIXEL_DIM2 = 2,
    __SE_SPAD_HORIZONTAL_PIXEL_DIM3 = 3,
    __SE_SPAD_HORIZONTAL_PIXEL_DIM_LAST = 3 /* Don't use directly. */
} __SE_SPAD_HORIZONTAL_PIXEL_DIM;
#endif /* __SE_FEAT_TEMPLATE_V3 */

/*----------------------------------------------------------------------------*/
/* Selected Loop Dimension Count End, and Start Sending Zero-Padded Vectors   */
/* to CPU.  The number of zero-padded vectors sent to CPU is defined by the   */
/* LEZR_CNT field in the template.  Supported in Linear Stream Mode only.     */
/*----------------------------------------------------------------------------*/
typedef enum __SE_LEZR
{
    __SE_LEZR_OFF = 0,
    __SE_LEZR_ICNT0 = 1,
    __SE_LEZR_ICNT1 = 2,
    __SE_LEZR_ICNT2 = 3,
    __SE_LEZR_ICNT3 = 4,
    __SE_LEZR_ICNT4 = 5,
    __SE_LEZR_ICNT5 = 6,
    /* reserved = 7 */
    __SE_LEZR_LAST = 7 /* Don't use directly. */
} __SE_LEZR;

/*----------------------------------------------------------------------------*/
/* Streaming Engine DECDIM field mode.                                        */
/*----------------------------------------------------------------------------*/
typedef enum __SE_DECDIM2_MODE
{
    __SE_DECDIM2_MODE_NORMAL = 0,
    __SE_DECDIM2_MODE_HORIZ_ZERO_PAD = 1,
    __SE_DECDIM2_MODE_LAST = 1 /* Don't use directly. */
} __SE_DECDIM2_MODE;

/*----------------------------------------------------------------------------*/
/* Streaming Engine floating point data mode.                                 */
/* Enable to specify to the SE that the underlying data type is floating      */
/* point rather than integer. This information is used for two operations:    */
/* sub-element type promotion and non-zero fill values.                       */
/*----------------------------------------------------------------------------*/
typedef enum __SE_FLOAT
{
    __SE_FLOAT_OFF = 0,
#if defined(__SE_FEAT_FLOAT)
    __SE_FLOAT_ON = 1,
#endif /* __SE_FEAT_FLOAT */
    __SE_FLOAT_LAST = 1 /* Don't use directly. */
} __SE_FLOAT;

#if defined(__SE_FEAT_TEMPLATE_V2) || defined(__SE_FEAT_TEMPLATE_V3)
/*----------------------------------------------------------------------------*/
/* Streaming Engine sparsity mode.                                            */
/* Enable to specify to the SE that the input is compressed, sparse data.     */
/*----------------------------------------------------------------------------*/
typedef enum __SE_SPARSE_CFG
{
    __SE_SPARSE_CFG_NON_SPARSE = 0,
#if defined(__SE_FEAT_SPARSITY)
    __SE_SPARSE_CFG_SPARSE = 1,
    __SE_SPARSE_CFG_SPARSE_DIM1 = 2,
    __SE_SPARSE_CFG_SPARSE_DIM2 = 3,
#endif /* __SE_FEAT_SPARSITY */
    __SE_SPARSE_CFG_LAST = 3 /* Don't use directly. */
} __SE_SPARSE_CFG;
#endif /* __SE_FEAT_TEMPLATE_V2 || __SE_FEAT_TEMPLATE_V3 */

/*----------------------------------------------------------------------------*/
/* Streaming Engine template format.                                          */
/*----------------------------------------------------------------------------*/
typedef enum __SE_TEMPLATE_FMT
{
#if defined(__SE_FEAT_TEMPLATE_V1)
    __SE_TEMPLATE_FMT_v1 = 0,
#endif /* __SE_FEAT_TEMPLATE_V1 */
#if defined(__SE_FEAT_TEMPLATE_V2)
    __SE_TEMPLATE_FMT_v2 = 1,
#endif /* __SE_FEAT_TEMPLATE_V2 */
#if defined(__SE_FEAT_TEMPLATE_V3)
    __SE_TEMPLATE_FMT_v3 = 1, /* Duplicate encoding */
#endif /* __SE_FEAT_TEMPLATE_V3 */
    /* reserved = 2 */
    /* reserved = 3 */
    /* reserved = 4 */
    /* reserved = 5 */
    /* reserved = 6 */
    __SE_TEMPLATE_FMT_LAST = 7 /* Don't use directly. */
} __SE_TEMPLATE_FMT;

#if defined(__SE_FEAT_TEMPLATE_V1)
/*----------------------------------------------------------------------------*/
/* __SE_TEMPLATE_v1 struct for use with SE initialization via __SEn_OPEN()    */
/* intrinsics.                                                                */
/*----------------------------------------------------------------------------*/
PACKED_STRUCT_BEG(__SE_TEMPLATE_v1)
#if __little_endian__
    uint64_t ICNT0:32;
    uint64_t ICNT1:32;
    uint64_t ICNT2:32;
    uint64_t ICNT3:32;
    uint64_t ICNT4:32;
    uint64_t ICNT5:32;
    uint64_t DECDIM1_WIDTH:32;
    uint64_t DECDIM2_WIDTH:32;
    int64_t  DIM1:32;
    int64_t  DIM2:32;
    int64_t  DIM3:32;
    int64_t  DIM4:32;
    int64_t  DIM5:32;
    uint64_t LEZR_CNT:8;
    uint64_t _reserved1:24;
    /* Flags */
    __SE_ELETYPE ELETYPE:4;
    __SE_TRANSPOSE TRANSPOSE:3;
    uint64_t _reserved2:1;
    __SE_PROMOTE PROMOTE:3;
    __SE_FLOAT FLOAT:1;
    __SE_VECLEN VECLEN:3;
    uint64_t _reserved4:1;
    __SE_ELEDUP ELEDUP:3;
    __SE_GRPDUP GRPDUP:1;
    __SE_DECIM DECIM:2;
    __SE_FILLVAL FILLVAL:2;
    __SE_DIMFMT DIMFMT:3;
    __SE_DIR DIR:1;
    uint64_t CBK0:4;
    uint64_t CBK1:4;
    __SE_AM AM0:2;
    __SE_AM AM1:2;
    __SE_AM AM2:2;
    __SE_AM AM3:2;
    __SE_AM AM4:2;
    __SE_AM AM5:2;
    __SE_DECDIM DECDIM1:3;
    __SE_DECDIMSD DECDIM1SD:2;
    __SE_DECDIM DECDIM2:3;
    __SE_DECDIMSD DECDIM2SD:2;
    __SE_LEZR LEZR:3;
    __SE_TEMPLATE_FMT TEMPLATE_FMT:3;
#else
    /* Invert on 64 bit boundaries */
    uint64_t ICNT1:32;
    uint64_t ICNT0:32;

    uint64_t ICNT3:32;
    uint64_t ICNT2:32;

    uint64_t ICNT5:32;
    uint64_t ICNT4:32;

    uint64_t DECDIM2_WIDTH:32;
    uint64_t DECDIM1_WIDTH:32;

    int64_t  DIM2:32;
    int64_t  DIM1:32;

    int64_t  DIM4:32;
    int64_t  DIM3:32;

    uint64_t _reserved1:24;
    uint64_t LEZR_CNT:8;
    int64_t  DIM5:32;

    /* Flags */
    __SE_TEMPLATE_FMT TEMPLATE_FMT:3;
    __SE_LEZR LEZR:3;
    __SE_DECDIMSD DECDIM2SD:2;
    __SE_DECDIM DECDIM2:3;
    __SE_DECDIMSD DECDIM1SD:2;
    __SE_DECDIM DECDIM1:3;
    __SE_AM AM5:2;
    __SE_AM AM4:2;
    __SE_AM AM3:2;
    __SE_AM AM2:2;
    __SE_AM AM1:2;
    __SE_AM AM0:2;
    uint64_t CBK1:4;
    uint64_t CBK0:4;
    __SE_DIR DIR:1;
    __SE_DIMFMT DIMFMT:3;
    __SE_FILLVAL FILLVAL:2;
    __SE_DECIM DECIM:2;
    __SE_GRPDUP GRPDUP:1;
    __SE_ELEDUP ELEDUP:3;
    uint64_t _reserved4:1;
    __SE_VECLEN VECLEN:3;
    __SE_FLOAT FLOAT:1;
    __SE_PROMOTE PROMOTE:3;
    uint64_t _reserved2:1;
    __SE_TRANSPOSE TRANSPOSE:3;
    __SE_ELETYPE ELETYPE:4;
#endif
PACKED_STRUCT_END(__SE_TEMPLATE_v1)
#endif /* __SE_FEAT_TEMPLATE_V1 */

#if defined(__SE_FEAT_TEMPLATE_V2)
/*----------------------------------------------------------------------------*/
/* __SE_TEMPLATE_v2 struct for use with SE initialization via __SEnOPEN()     */
/* intrinsics.                                                                */
/*----------------------------------------------------------------------------*/
PACKED_STRUCT_BEG(__SE_TEMPLATE_v2)
#if __little_endian__
    uint64_t ICNT0:16;
    uint64_t SPAD_PAD_WIDTH:16;
    uint64_t ICNT1:16;
    uint64_t INVERSE_DECDIM1_WIDTH:16;
    uint64_t ICNT2:16;
    uint64_t INVERSE_DECDIM2_WIDTH:16;
    uint64_t ICNT3:32;
    uint64_t ICNT4:32;
    uint64_t ICNT5:32;
    uint64_t DECDIM1_WIDTH:32;
    uint64_t DECDIM2_WIDTH:32;
    int64_t  DIM1:32;
    int64_t  DIM2:32;
    int64_t  DIM3:32;
    int64_t  DIM4:32;
    int64_t  DIM5:32;
    uint64_t LEZR_CNT:8;
    uint64_t _reserved1:24;
    /* Flags */
    __SE_ELETYPE ELETYPE:4;
    __SE_SPARSE_CFG SPARSE_CFG:2;
    uint64_t _reserved2:2;
    __SE_PROMOTE PROMOTE:3;
    __SE_FLOAT FLOAT:1;
    __SE_VECLEN VECLEN:3;
    uint64_t _reserved4:1;
    uint64_t _reserved5:4;
    __SE_DECIM DECIM:2;
    __SE_FILLVAL FILLVAL:2;
    __SE_DIMFMT DIMFMT:3;
    __SE_DECDIM2_MODE DECDIM2_MODE:1;
    uint64_t CBK0:4;
    uint64_t CBK1:4;
    __SE_AM AM0:2;
    __SE_AM AM1:2;
    __SE_AM AM2:2;
    __SE_AM AM3:2;
    __SE_AM AM4:2;
    __SE_AM AM5:2;
    __SE_DECDIM DECDIM1:3;
    __SE_DECDIMSD DECDIM1SD:2;
    __SE_DECDIM DECDIM2:3;
    __SE_DECDIMSD DECDIM2SD:2;
    __SE_LEZR LEZR:3;
    __SE_TEMPLATE_FMT TEMPLATE_FMT:3;
#else
    /* Invert on 64 bit boundaries */
    uint64_t INVERSE_DECDIM1_WIDTH:16;
    uint64_t ICNT1:16;
    uint64_t SPAD_PAD_WIDTH:16;
    uint64_t ICNT0:16;

    uint64_t ICNT3:32;
    uint64_t INVERSE_DECDIM2_WIDTH:16;
    uint64_t ICNT2:16;

    uint64_t ICNT5:32;
    uint64_t ICNT4:32;

    uint64_t DECDIM2_WIDTH:32;
    uint64_t DECDIM1_WIDTH:32;

    int64_t  DIM2:32;
    int64_t  DIM1:32;

    int64_t  DIM4:32;
    int64_t  DIM3:32;

    uint64_t _reserved1:24;
    uint64_t LEZR_CNT:8;
    int64_t  DIM5:32;

    /* Flags */
    __SE_TEMPLATE_FMT TEMPLATE_FMT:3;
    __SE_LEZR LEZR:3;
    __SE_DECDIMSD DECDIM2SD:2;
    __SE_DECDIM DECDIM2:3;
    __SE_DECDIMSD DECDIM1SD:2;
    __SE_DECDIM DECDIM1:3;
    __SE_AM AM5:2;
    __SE_AM AM4:2;
    __SE_AM AM3:2;
    __SE_AM AM2:2;
    __SE_AM AM1:2;
    __SE_AM AM0:2;
    uint64_t CBK1:4;
    uint64_t CBK0:4;
    __SE_DECDIM2_MODE DECDIM2_MODE:1;
    __SE_DIMFMT DIMFMT:3;
    __SE_FILLVAL FILLVAL:2;
    __SE_DECIM DECIM:2;
    uint64_t _reserved5:4;
    uint64_t _reserved4:1;
    __SE_VECLEN VECLEN:3;
    __SE_FLOAT FLOAT:1;
    __SE_PROMOTE PROMOTE:3;
    uint64_t _reserved2:2;
    __SE_SPARSE_CFG SPARSE_CFG:2;
    __SE_ELETYPE ELETYPE:4;
#endif
PACKED_STRUCT_END(__SE_TEMPLATE_v2)
#endif /* __SE_FEAT_TEMPLATE_V2 */

#if defined(__SE_FEAT_TEMPLATE_V3)
/*----------------------------------------------------------------------------*/
/* __SE_TEMPLATE_v3 struct for use with SE initialization via __SEnOPEN()     */
/* intrinsics.                                                                */
/*----------------------------------------------------------------------------*/
PACKED_STRUCT_BEG(__SE_TEMPLATE_v3)
#if __little_endian__
    uint64_t ICNT0:16;
    uint64_t SPAD_PAD_WIDTH:16;
    uint64_t ICNT1:16;
    uint64_t INVERSE_DECDIM1_WIDTH:16;
    uint64_t ICNT2:16;
    uint64_t SPAD_STARTING_OFFSET:16;
    uint64_t ICNT3:32;
    uint64_t ICNT4:32;
    uint64_t ICNT5:32;
    uint64_t DECDIM1_WIDTH:32;
    uint64_t SPAD_HORIZONTAL_WIDTH:16;
    uint64_t _reserved0:16;
    int64_t  DIM1:32;
    int64_t  DIM2:32;
    int64_t  DIM3:32;
    int64_t  DIM4:32;
    int64_t  DIM5:32;
    uint64_t LEZR_CNT:8;
    uint64_t _reserved1:24;
    /* Flags */
    __SE_ELETYPE ELETYPE:4;
    __SE_SPARSE_CFG SPARSE_CFG:2;
    uint64_t _reserved2:2;
    __SE_PROMOTE PROMOTE:3;
    __SE_FLOAT FLOAT:1;
    __SE_VECLEN VECLEN:3;
    uint64_t _reserved4:1;
    uint64_t _reserved5:4;
    __SE_DECIM DECIM:2;
    __SE_FILLVAL FILLVAL:2;
    __SE_DIMFMT DIMFMT:3;
    __SE_DECDIM2_MODE DECDIM2_MODE:1;
    uint64_t CBK0:4;
    uint64_t CBK1:4;
    __SE_AM AM0:2;
    __SE_AM AM1:2;
    __SE_AM AM2:2;
    __SE_AM AM3:2;
    __SE_AM AM4:2;
    __SE_AM AM5:2;
    __SE_DECDIM DECDIM1:3;
    __SE_DECDIMSD DECDIM1SD:2;
    __SE_SPAD_HORIZONTAL_BLOCK_DIM SPAD_HORIZONTAL_BLOCK_DIM:3;
    __SE_SPAD_HORIZONTAL_PIXEL_DIM SPAD_HORIZONTAL_PIXEL_DIM:2;
    __SE_LEZR LEZR:3;
    __SE_TEMPLATE_FMT TEMPLATE_FMT:3;
#else
    /* Invert on 64 bit boundaries */
    uint64_t INVERSE_DECDIM1_WIDTH:16;
    uint64_t ICNT1:16;
    uint64_t SPAD_PAD_WIDTH:16;
    uint64_t ICNT0:16;

    uint64_t ICNT3:32;
    uint64_t SPAD_STARTING_OFFSET:16;
    uint64_t ICNT2:16;

    uint64_t ICNT5:32;
    uint64_t ICNT4:32;

    uint64_t _reserved0:16;
    uint64_t SPAD_HORIZONTAL_WIDTH:16;
    uint64_t DECDIM1_WIDTH:32;

    int64_t  DIM2:32;
    int64_t  DIM1:32;

    int64_t  DIM4:32;
    int64_t  DIM3:32;

    uint64_t _reserved1:24;
    uint64_t LEZR_CNT:8;
    int64_t  DIM5:32;

    /* Flags */
    __SE_TEMPLATE_FMT TEMPLATE_FMT:3;
    __SE_LEZR LEZR:3;
    __SE_SPAD_HORIZONTAL_PIXEL_DIM SPAD_HORIZONTAL_PIXEL_DIM:2;
    __SE_SPAD_HORIZONTAL_BLOCK_DIM SPAD_HORIZONTAL_BLOCK_DIM:3;
    __SE_DECDIMSD DECDIM1SD:2;
    __SE_DECDIM DECDIM1:3;
    __SE_AM AM5:2;
    __SE_AM AM4:2;
    __SE_AM AM3:2;
    __SE_AM AM2:2;
    __SE_AM AM1:2;
    __SE_AM AM0:2;
    uint64_t CBK1:4;
    uint64_t CBK0:4;
    __SE_DECDIM2_MODE DECDIM2_MODE:1;
    __SE_DIMFMT DIMFMT:3;
    __SE_FILLVAL FILLVAL:2;
    __SE_DECIM DECIM:2;
    uint64_t _reserved5:4;
    uint64_t _reserved4:1;
    __SE_VECLEN VECLEN:3;
    __SE_FLOAT FLOAT:1;
    __SE_PROMOTE PROMOTE:3;
    uint64_t _reserved2:2;
    __SE_SPARSE_CFG SPARSE_CFG:2;
    __SE_ELETYPE ELETYPE:4;
#endif
PACKED_STRUCT_END(__SE_TEMPLATE_v3)
#endif /* __SE_FEAT_TEMPLATE_V3 */

/*----------------------------------------------------------------------------*/
/* Stream Address Generator vector lengths.                                   */
/* Use the below enumerations to indicate the vector lengths in elements.     */
/*----------------------------------------------------------------------------*/
typedef enum __SA_VECLEN
{
    __SA_VECLEN_1ELEM = 0,
    __SA_VECLEN_2ELEMS = 1,
    __SA_VECLEN_4ELEMS = 2,
    __SA_VECLEN_8ELEMS = 3,
    __SA_VECLEN_16ELEMS = 4,
    __SA_VECLEN_32ELEMS = 5,
#if __C7X_VEC_SIZE_BYTES__ > 32
    __SA_VECLEN_64ELEMS = 6,
#endif /* __C7X_VEC_SIZE_BYTES__ > 32 */
    /* reserved = 7 */
    __SA_VECLEN_LAST = 7 /* Don't use directly. */
} __SA_VECLEN;

typedef enum __SA_INV_DD
{
    __SA_INV_DD_OFF = 0,
    __SA_INV_DD_ON = 1,
    __SA_INV_DD_LAST = 1 /* Don't use directly. */
} __SA_INV_DD;

/*----------------------------------------------------------------------------*/
/* Template format selection for Stream Address Generator                     */
/*----------------------------------------------------------------------------*/
typedef enum __SA_DIMFMT
{
    __SA_DIMFMT_1D = 0,
    __SA_DIMFMT_2D = 1,
    __SA_DIMFMT_3D = 2,
    __SA_DIMFMT_4D = 3,
    __SA_DIMFMT_5D = 4,
    __SA_DIMFMT_6D = 5,
    /* reserved = 6 */
    /* reserved = 7 */
    __SA_DIMFMT_LAST = 7 /* Don't use directly. */
} __SA_DIMFMT;

/*----------------------------------------------------------------------------*/
/* Stream Address Generator Data Strip Mining Decrement Dimension for ICNT0   */
/* In this mode, the current I0 count is NOT reloaded with ICNT0 when each    */
/* dimension expires.  The I0 count is only reloaded when the selected DECDIM */
/* dimension expires, or a dimension higher above it expires.                 */
/*----------------------------------------------------------------------------*/
typedef enum __SA_DECDIM
{
    __SA_DECDIM_DIM0 = 0,
    __SA_DECDIM_DIM1 = 1,
    __SA_DECDIM_DIM2 = 2,
    __SA_DECDIM_DIM3 = 3,
    __SA_DECDIM_DIM4 = 4,
    __SA_DECDIM_DIM5 = 5,
    /* reserved = 6 */
    /* reserved = 7 */
    __SA_DECDIM_LAST = 7 /* Don't use directly. */
} __SA_DECDIM;

/*----------------------------------------------------------------------------*/
/* Stream Address Generator Secondary Data Strip Mining Decrement Dimension   */
/*----------------------------------------------------------------------------*/
typedef enum __SA_DECDIMSD
{
    __SA_DECDIMSD_DIM0 = 0,
    __SA_DECDIMSD_DIM1 = 1,
    __SA_DECDIMSD_DIM2 = 2,
    __SA_DECDIMSD_DIM3 = 3,
    __SA_DECDIMSD_LAST = 3 /* Don't use directly. */
} __SA_DECDIMSD;

/*----------------------------------------------------------------------------*/
/* __SA_TEMPLATE_v1 struct for use with SA initialization via __SAn_OPEN      */
/* intrinsics.                                                                */
/*----------------------------------------------------------------------------*/
PACKED_STRUCT_BEG(__SA_TEMPLATE_v1)
#if __little_endian__
    uint64_t ICNT0:32;
    uint64_t ICNT1:32;
    uint64_t ICNT2:32;
    uint64_t ICNT3:32;
    uint64_t ICNT4:32;
    uint64_t ICNT5:32;
    uint64_t DECDIM1_WIDTH:32;
    uint64_t DECDIM2_WIDTH:32;
    int64_t  DIM1:32;
    int64_t  DIM2:32;
    int64_t  DIM3:32;
    int64_t  DIM4:32;
    int64_t  DIM5:32;
    uint64_t DECDIM3_WIDTH:32;
    /* Flags */
    uint64_t _reserved2:12;
    __SA_VECLEN VECLEN:3;
    uint64_t _reserved3:6;
    __SA_INV_DD INV_DD3:1;
    __SA_INV_DD INV_DD1:1;
    __SA_INV_DD INV_DD2:1;
    __SA_DIMFMT DIMFMT:3;
    uint64_t _reserved4:5;
    uint64_t _reserved5:11;
    __SA_DECDIM DECDIM3:3;
    __SA_DECDIMSD DECDIM3SD:2;
    __SA_DECDIM DECDIM1:3;
    __SA_DECDIMSD DECDIM1SD:2;
    __SA_DECDIM DECDIM2:3;
    __SA_DECDIMSD DECDIM2SD:2;
    uint64_t _reserved:6;
#else
    /* Invert on 64 bit boundaries. */
    uint64_t ICNT1:32;
    uint64_t ICNT0:32;

    uint64_t ICNT3:32;
    uint64_t ICNT2:32;

    uint64_t ICNT5:32;
    uint64_t ICNT4:32;

    uint64_t DECDIM2_WIDTH:32;
    uint64_t DECDIM1_WIDTH:32;

    int64_t  DIM2:32;
    int64_t  DIM1:32;

    int64_t  DIM4:32;
    int64_t  DIM3:32;

    uint64_t DECDIM3_WIDTH:32;
    int64_t  DIM5:32;

    /* Flags */
    uint64_t _reserved:6;
    __SA_DECDIMSD DECDIM2SD:2;
    __SA_DECDIM DECDIM2:3;
    __SA_DECDIMSD DECDIM1SD:2;
    __SA_DECDIM DECDIM1:3;
    __SA_DECDIMSD DECDIM3SD:2;
    __SA_DECDIM DECDIM3:3;
    uint64_t _reserved5:11;
    uint64_t _reserved4:5;
    __SA_DIMFMT DIMFMT:3;
    __SA_INV_DD INV_DD2:1;
    __SA_INV_DD INV_DD1:1;
    __SA_INV_DD INV_DD3:1;
    uint64_t _reserved3:6;
    __SA_VECLEN VECLEN:3;
    uint64_t _reserved2:12;
#endif
PACKED_STRUCT_END(__SA_TEMPLATE_v1)

#if defined(__SE_FEAT_TEMPLATE_V1)
/*----------------------------------------------------------------------------*/
/* Generate an __SE_TEMPLATE_v1 with safe default values.                     */
/*----------------------------------------------------------------------------*/
static inline __SE_TEMPLATE_v1 __gen_SE_TEMPLATE_v1()
{
    const __SE_TEMPLATE_v1 se =
    {
#if __little_endian__
        /* ICNT0            = */ 0,
        /* ICNT1            = */ 0,
        /* ICNT2            = */ 0,
        /* ICNT3            = */ 0,
        /* ICNT4            = */ 0,
        /* ICNT5            = */ 0,
        /* DECDIM1_WIDTH    = */ 0,
        /* DECDIM2_WIDTH    = */ 0,
        /* DIM1             = */ 0,
        /* DIM2             = */ 0,
        /* DIM3             = */ 0,
        /* DIM4             = */ 0,
        /* DIM5             = */ 0,
        /* LEZR_CN          = */ 0,
        /* _reserved1       = */ 0,
        /*** Flags ***/
        /* ELETYPE          = */ __SE_ELETYPE_8BIT,
        /* TRANSPOSE        = */ __SE_TRANSPOSE_OFF,
        /* _reserved2       = */ 0,
        /* PROMOTE          = */ __SE_PROMOTE_OFF,
        /* FLOAT            = */ __SE_FLOAT_OFF,
        #if __C7X_VEC_SIZE_BYTES__ == 32
        /* VECLEN           = */ __SE_VECLEN_32ELEMS,
        #else
        /* VECLEN           = */ __SE_VECLEN_64ELEMS,
        #endif /* __C7X_VEC_SIZE_BYTES__ */
        /* _reserved4       = */ 0,
        /* ELEDUP           = */ __SE_ELEDUP_OFF,
        /* GRPDUP           = */ __SE_GRPDUP_OFF,
        /* DECIM            = */ __SE_DECIM_OFF,
        /* FILLVAL          = */ __SE_FILLVAL_ZERO,
        /* DIMFMT           = */ __SE_DIMFMT_1D,
        /* DIR              = */ __SE_DIR_INC,
        /* CBK0             = */ 0,
        /* CBK1             = */ 0,
        /* AM0              = */ __SE_AM_LINEAR,
        /* AM1              = */ __SE_AM_LINEAR,
        /* AM2              = */ __SE_AM_LINEAR,
        /* AM3              = */ __SE_AM_LINEAR,
        /* AM4              = */ __SE_AM_LINEAR,
        /* AM5              = */ __SE_AM_LINEAR,
        /* DECDIM1          = */ __SE_DECDIM_DIM0,
        /* DECDIM1SD        = */ __SE_DECDIMSD_DIM0,
        /* DECDIM2          = */ __SE_DECDIM_DIM0,
        /* DECDIM2SD        = */ __SE_DECDIMSD_DIM0,
        /* LEZR             = */ __SE_LEZR_OFF,
        /* TEMPLATE_FMT     = */ __SE_TEMPLATE_FMT_v1
#else
        /* Invert on 64 bit boundaries */
        /* ICNT1            = */ 0,
        /* ICNT0            = */ 0,

        /* ICNT3            = */ 0,
        /* ICNT2            = */ 0,

        /* ICNT5            = */ 0,
        /* ICNT4            = */ 0,

        /* DECDIM2_WIDTH    = */ 0,
        /* DECDIM1_WIDTH    = */ 0,

        /* DIM2             = */ 0,
        /* DIM1             = */ 0,

        /* DIM4             = */ 0,
        /* DIM3             = */ 0,

        /* _reserved1       = */ 0,
        /* LEZR_CN          = */ 0,
        /* DIM5             = */ 0,

        /*** Flags ***/
        /* TEMPLATE_FMT     = */ __SE_TEMPLATE_FMT_v1,
        /* LEZR             = */ __SE_LEZR_OFF,
        /* DECDIM2SD        = */ __SE_DECDIMSD_DIM0,
        /* DECDIM2          = */ __SE_DECDIM_DIM0,
        /* DECDIM1SD        = */ __SE_DECDIMSD_DIM0,
        /* DECDIM1          = */ __SE_DECDIM_DIM0,
        /* AM5              = */ __SE_AM_LINEAR,
        /* AM4              = */ __SE_AM_LINEAR,
        /* AM3              = */ __SE_AM_LINEAR,
        /* AM2              = */ __SE_AM_LINEAR,
        /* AM1              = */ __SE_AM_LINEAR,
        /* AM0              = */ __SE_AM_LINEAR,
        /* CBK1             = */ 0,
        /* CBK0             = */ 0,
        /* DIR              = */ __SE_DIR_INC,
        /* DIMFMT           = */ __SE_DIMFMT_1D,
        /* FILLVAL          = */ __SE_FILLVAL_ZERO,
        /* DECIM            = */ __SE_DECIM_OFF,
        /* GRPDUP           = */ __SE_GRPDUP_OFF,
        /* ELEDUP           = */ __SE_ELEDUP_OFF,
        /* _reserved4       = */ 0,
        #if __C7X_VEC_SIZE_BYTES__ == 32
        /* VECLEN           = */ __SE_VECLEN_32ELEMS,
        #else
        /* VECLEN           = */ __SE_VECLEN_64ELEMS,
        #endif /* __C7X_VEC_SIZE_BYTES__ */
        /* FLOAT            = */ __SE_FLOAT_OFF,
        /* PROMOTE          = */ __SE_PROMOTE_OFF,
        /* _reserved2       = */ 0,
        /* TRANSPOSE        = */ __SE_TRANSPOSE_OFF,
        /* ELETYPE          = */ __SE_ELETYPE_8BIT
#endif
    };
    return se;
}
#endif /* __SE_FEAT_TEMPLATE_V1 */

#if defined(__SE_FEAT_TEMPLATE_V2)
/*----------------------------------------------------------------------------*/
/* Generate an __SE_TEMPLATE_v2 with safe default values.                     */
/*----------------------------------------------------------------------------*/
static inline __SE_TEMPLATE_v2 __gen_SE_TEMPLATE_v2()
{
    const __SE_TEMPLATE_v2 se =
    {
#if __little_endian__
        /* ICNT0                 = */ 0,
        /* SPAD_PAD_WIDTH        = */ 0,
        /* ICNT1                 = */ 0,
        /* INVERSE_DECDIM1_WIDTH = */ 0,
        /* ICNT2                 = */ 0,
        /* INVERSE_DECDIM2_WIDTH = */ 0,
        /* ICNT3                 = */ 0,
        /* ICNT4                 = */ 0,
        /* ICNT5                 = */ 0,
        /* DECDIM1_WIDTH         = */ 0,
        /* DECDIM2_WIDTH         = */ 0,
        /* DIM1                  = */ 0,
        /* DIM2                  = */ 0,
        /* DIM3                  = */ 0,
        /* DIM4                  = */ 0,
        /* DIM5                  = */ 0,
        /* LEZR_CNT              = */ 0,
        /* _reserved1            = */ 0,
        /*** Flags ***/
        /* ELETYPE               = */ __SE_ELETYPE_8BIT,
        /* SPARSE_CFG            = */ __SE_SPARSE_CFG_NON_SPARSE,
        /* _reserved2            = */ 0,
        /* PROMOTE               = */ __SE_PROMOTE_OFF,
        /* FLOAT                 = */ __SE_FLOAT_OFF,
        #if __C7X_VEC_SIZE_BYTES__ == 32
        /* VECLEN                = */ __SE_VECLEN_32ELEMS,
        #else
        /* VECLEN                = */ __SE_VECLEN_64ELEMS,
        #endif /* __C7X_VEC_SIZE_BYTES__ */
        /* _reserved4            = */ 0,
        /* _reserved5            = */ 0,
        /* DECIM                 = */ __SE_DECIM_OFF,
        /* FILLVAL               = */ __SE_FILLVAL_ZERO,
        /* DIMFMT                = */ __SE_DIMFMT_1D,
        /* DECDIM2_MODE          = */ __SE_DECDIM2_MODE_NORMAL,
        /* CBK0                  = */ 0,
        /* CBK1                  = */ 0,
        /* AM0                   = */ __SE_AM_LINEAR,
        /* AM1                   = */ __SE_AM_LINEAR,
        /* AM2                   = */ __SE_AM_LINEAR,
        /* AM3                   = */ __SE_AM_LINEAR,
        /* AM4                   = */ __SE_AM_LINEAR,
        /* AM5                   = */ __SE_AM_LINEAR,
        /* DECDIM1               = */ __SE_DECDIM_DIM0,
        /* DECDIM1SD             = */ __SE_DECDIMSD_DIM0,
        /* DECDIM2               = */ __SE_DECDIM_DIM0,
        /* DECDIM2SD             = */ __SE_DECDIMSD_DIM0,
        /* LEZR                  = */ __SE_LEZR_OFF,
        /* TEMPLATE_FMT          = */ __SE_TEMPLATE_FMT_v2
#else
        /* Invert on 64 bit boundaries */
        /* INVERSE_DECDIM1_WIDTH = */ 0,
        /* ICNT1                 = */ 0,
        /* SPAD_PAD_WIDTH        = */ 0,
        /* ICNT0                 = */ 0,

        /* ICNT3                 = */ 0,
        /* INVERSE_DECDIM2_WIDTH = */ 0,
        /* ICNT2                 = */ 0,

        /* ICNT5                 = */ 0,
        /* ICNT4                 = */ 0,

        /* DECDIM2_WIDTH         = */ 0,
        /* DECDIM1_WIDTH         = */ 0,

        /* DIM2                  = */ 0,
        /* DIM1                  = */ 0,

        /* DIM4                  = */ 0,
        /* DIM3                  = */ 0,

        /* _reserved1            = */ 0,
        /* LEZR_CNT              = */ 0,
        /* DIM5                  = */ 0,

        /*** Flags ***/
        /* TEMPLATE_FMT          = */ __SE_TEMPLATE_FMT_v2,
        /* LEZR                  = */ __SE_LEZR_OFF,
        /* DECDIM2SD             = */ __SE_DECDIMSD_DIM0,
        /* DECDIM2               = */ __SE_DECDIM_DIM0,
        /* DECDIM1SD             = */ __SE_DECDIMSD_DIM0,
        /* DECDIM1               = */ __SE_DECDIM_DIM0,
        /* AM5                   = */ __SE_AM_LINEAR,
        /* AM4                   = */ __SE_AM_LINEAR,
        /* AM3                   = */ __SE_AM_LINEAR,
        /* AM2                   = */ __SE_AM_LINEAR,
        /* AM1                   = */ __SE_AM_LINEAR,
        /* AM0                   = */ __SE_AM_LINEAR,
        /* CBK1                  = */ 0,
        /* CBK0                  = */ 0,
        /* DECDIM2_MODE          = */ __SE_DECDIM2_MODE_NORMAL,
        /* DIMFMT                = */ __SE_DIMFMT_1D,
        /* FILLVAL               = */ __SE_FILLVAL_ZERO,
        /* DECIM                 = */ __SE_DECIM_OFF,
        /* _reserved5            = */ 0,
        /* _reserved4            = */ 0,
        #if __C7X_VEC_SIZE_BYTES__ == 32
        /* VECLEN                = */ __SE_VECLEN_32ELEMS,
        #else
        /* VECLEN                = */ __SE_VECLEN_64ELEMS,
        #endif /* __C7X_VEC_SIZE_BYTES__ */
        /* FLOAT                 = */ __SE_FLOAT_OFF,
        /* PROMOTE               = */ __SE_PROMOTE_OFF,
        /* _reserved2            = */ 0,
        /* SPARSE_CFG            = */ __SE_SPARSE_CFG_NON_SPARSE,
        /* ELETYPE               = */ __SE_ELETYPE_8BIT
#endif
    };
    return se;
}
#endif /* __SE_FEAT_TEMPLATE_V2 */

#if defined(__SE_FEAT_TEMPLATE_V3)
/*----------------------------------------------------------------------------*/
/* Generate an __SE_TEMPLATE_v3 with safe default values.                     */
/*----------------------------------------------------------------------------*/
static inline __SE_TEMPLATE_v3 __gen_SE_TEMPLATE_v3()
{
    const __SE_TEMPLATE_v3 se =
    {
#if __little_endian__
        /* ICNT0                 = */ 0,
        /* SPAD_PAD_WIDTH        = */ 0,
        /* ICNT1                 = */ 0,
        /* INVERSE_DECDIM1_WIDTH = */ 0,
        /* ICNT2                 = */ 0,
        /* SPAD_STARTING_OFFSET  = */ 0,
        /* ICNT3                 = */ 0,
        /* ICNT4                 = */ 0,
        /* ICNT5                 = */ 0,
        /* DECDIM1_WIDTH         = */ 0,
        /* SPAD_HORIZONTAL_WIDTH = */ 0,
        /* _reserved0            = */ 0,
        /* DIM1                  = */ 0,
        /* DIM2                  = */ 0,
        /* DIM3                  = */ 0,
        /* DIM4                  = */ 0,
        /* DIM5                  = */ 0,
        /* LEZR_CNT              = */ 0,
        /* _reserved1            = */ 0,
        /*** Flags ***/
        /* ELETYPE               = */ __SE_ELETYPE_8BIT,
        /* SPARSE_CFG            = */ __SE_SPARSE_CFG_NON_SPARSE,
        /* _reserved2            = */ 0,
        /* PROMOTE               = */ __SE_PROMOTE_OFF,
        /* FLOAT                 = */ __SE_FLOAT_OFF,
        #if __C7X_VEC_SIZE_BYTES__ == 32
        /* VECLEN                = */ __SE_VECLEN_32ELEMS,
        #else
        /* VECLEN                = */ __SE_VECLEN_64ELEMS,
        #endif /* __C7X_VEC_SIZE_BYTES__ */
        /* _reserved4            = */ 0,
        /* _reserved5            = */ 0,
        /* DECIM                 = */ __SE_DECIM_OFF,
        /* FILLVAL               = */ __SE_FILLVAL_ZERO,
        /* DIMFMT                = */ __SE_DIMFMT_1D,
        /* DECDIM2_MODE          = */ __SE_DECDIM2_MODE_HORIZ_ZERO_PAD,
        /* CBK0                  = */ 0,
        /* CBK1                  = */ 0,
        /* AM0                   = */ __SE_AM_LINEAR,
        /* AM1                   = */ __SE_AM_LINEAR,
        /* AM2                   = */ __SE_AM_LINEAR,
        /* AM3                   = */ __SE_AM_LINEAR,
        /* AM4                   = */ __SE_AM_LINEAR,
        /* AM5                   = */ __SE_AM_LINEAR,
        /* DECDIM1               = */ __SE_DECDIM_DIM0,
        /* DECDIM1SD             = */ __SE_DECDIMSD_DIM0,
        /* SPAD_HORIZONTAL_BLO.. = */ __SE_SPAD_HORIZONTAL_BLOCK_DIM0,
        /* SPAD_HORIZONTAL_PIX.. = */ __SE_SPAD_HORIZONTAL_PIXEL_DIM0,
        /* LEZR                  = */ __SE_LEZR_OFF,
        /* TEMPLATE_FMT          = */ __SE_TEMPLATE_FMT_v2
#else
        /* Invert on 64 bit boundaries */
        /* INVERSE_DECDIM1_WIDTH = */ 0,
        /* ICNT1                 = */ 0,
        /* SPAD_PAD_WIDTH        = */ 0,
        /* ICNT0                 = */ 0,

        /* ICNT3                 = */ 0,
        /* SPAD_STARTING_OFFSET  = */ 0,
        /* ICNT2                 = */ 0,

        /* ICNT5                 = */ 0,
        /* ICNT4                 = */ 0,

        /* _reserved0            = */ 0,
        /* SPAD_HORIZONTAL_WIDTH = */ 0,
        /* DECDIM1_WIDTH         = */ 0,

        /* DIM2                  = */ 0,
        /* DIM1                  = */ 0,

        /* DIM4                  = */ 0,
        /* DIM3                  = */ 0,

        /* _reserved1            = */ 0,
        /* LEZR_CNT              = */ 0,
        /* DIM5                  = */ 0,

        /*** Flags ***/
        /* TEMPLATE_FMT          = */ __SE_TEMPLATE_FMT_v2,
        /* LEZR                  = */ __SE_LEZR_OFF,
        /* SPAD_HORIZONTAL_PIX.. = */ __SE_SPAD_HORIZONTAL_PIXEL_DIM0,
        /* SPAD_HORIZONTAL_BLO.. = */ __SE_SPAD_HORIZONTAL_BLOCK_DIM0,
        /* DECDIM1SD             = */ __SE_DECDIMSD_DIM0,
        /* DECDIM1               = */ __SE_DECDIM_DIM0,
        /* AM5                   = */ __SE_AM_LINEAR,
        /* AM4                   = */ __SE_AM_LINEAR,
        /* AM3                   = */ __SE_AM_LINEAR,
        /* AM2                   = */ __SE_AM_LINEAR,
        /* AM1                   = */ __SE_AM_LINEAR,
        /* AM0                   = */ __SE_AM_LINEAR,
        /* CBK1                  = */ 0,
        /* CBK0                  = */ 0,
        /* DECDIM2_MODE          = */ __SE_DECDIM2_MODE_HORIZ_ZERO_PAD,
        /* DIMFMT                = */ __SE_DIMFMT_1D,
        /* FILLVAL               = */ __SE_FILLVAL_ZERO,
        /* DECIM                 = */ __SE_DECIM_OFF,
        /* _reserved5            = */ 0,
        /* _reserved4            = */ 0,
        #if __C7X_VEC_SIZE_BYTES__ == 32
        /* VECLEN                = */ __SE_VECLEN_32ELEMS,
        #else
        /* VECLEN                = */ __SE_VECLEN_64ELEMS,
        #endif /* __C7X_VEC_SIZE_BYTES__ */
        /* FLOAT                 = */ __SE_FLOAT_OFF,
        /* PROMOTE               = */ __SE_PROMOTE_OFF,
        /* _reserved2            = */ 0,
        /* SPARSE_CFG            = */ __SE_SPARSE_CFG_NON_SPARSE,
        /* ELETYPE               = */ __SE_ELETYPE_8BIT
#endif
    };
    return se;
}
#endif /* __SE_FEAT_TEMPLATE_V3 */

/*----------------------------------------------------------------------------*/
/* Generate an __SA_TEMPLATE_v1 with safe default values.                     */
/*----------------------------------------------------------------------------*/
static inline __SA_TEMPLATE_v1 __gen_SA_TEMPLATE_v1()
{
    const __SA_TEMPLATE_v1 sa =
    {
#if __little_endian__
        /* ICNT0            = */ 0,
        /* ICNT1            = */ 0,
        /* ICNT2            = */ 0,
        /* ICNT3            = */ 0,
        /* ICNT4            = */ 0,
        /* ICNT5            = */ 0,
        /* DECDIM1_WIDTH    = */ 0,
        /* DECDIM2_WIDTH    = */ 0,
        /* DIM1             = */ 0,
        /* DIM2             = */ 0,
        /* DIM3             = */ 0,
        /* DIM4             = */ 0,
        /* DIM5             = */ 0,
        /* DECDIM3_WIDTH    = */ 0,
        /*** Flags ***/
        /* _reserved2       = */ 0,
        #if __C7X_VEC_SIZE_BYTES__ == 32
        /* VECLEN           = */ __SA_VECLEN_32ELEMS,
        #else
        /* VECLEN           = */ __SA_VECLEN_64ELEMS,
        #endif /* __C7X_VEC_SIZE_BYTES__ */
        /* _reserved3       = */ 0,
        /* INV_DD3          = */ __SA_INV_DD_OFF,
        /* INV_DD1          = */ __SA_INV_DD_OFF,
        /* INV_DD2          = */ __SA_INV_DD_OFF,
        /* DIMFMT           = */ __SA_DIMFMT_1D,
        /* _reserved4       = */ 0,
        /* _reserved5       = */ 0,
        /* DECDIM3          = */ __SA_DECDIM_DIM0,
        /* DECDIM3SD        = */ __SA_DECDIMSD_DIM0,
        /* DECDIM1          = */ __SA_DECDIM_DIM0,
        /* DECDIM1SD        = */ __SA_DECDIMSD_DIM0,
        /* DECDIM2          = */ __SA_DECDIM_DIM0,
        /* DECDIM2SD        = */ __SA_DECDIMSD_DIM0,
        /* _reserved        = */ 0
#else
        /* Invert on 64 bit boundaries. */
        /* ICNT1            = */ 0,
        /* ICNT0            = */ 0,

        /* ICNT3            = */ 0,
        /* ICNT2            = */ 0,

        /* ICNT5            = */ 0,
        /* ICNT4            = */ 0,

        /* DECDIM2_WIDTH    = */ 0,
        /* DECDIM1_WIDTH    = */ 0,

        /* DIM2             = */ 0,
        /* DIM1             = */ 0,

        /* DIM4             = */ 0,
        /* DIM3             = */ 0,

        /* DECDIM3_WIDTH    = */ 0,
        /* DIM5             = */ 0,

        /*** Flags ***/
        /* _reserved        = */ 0,
        /* DECDIM2SD        = */ __SA_DECDIMSD_DIM0,
        /* DECDIM2          = */ __SA_DECDIM_DIM0,
        /* DECDIM1SD        = */ __SA_DECDIMSD_DIM0,
        /* DECDIM1          = */ __SA_DECDIM_DIM0,
        /* DECDIM3SD        = */ __SA_DECDIMSD_DIM0,
        /* DECDIM3          = */ __SA_DECDIM_DIM0,
        /* _reserved5       = */ 0,
        /* _reserved4       = */ 0,
        /* DIMFMT           = */ __SA_DIMFMT_1D,
        /* INV_DD2          = */ __SA_INV_DD_OFF,
        /* INV_DD1          = */ __SA_INV_DD_OFF,
        /* INV_DD3          = */ __SA_INV_DD_OFF,
        /* _reserved3       = */ 0,
        #if __C7X_VEC_SIZE_BYTES__ == 32
        /* VECLEN           = */ __SA_VECLEN_32ELEMS,
        #else
        /* VECLEN           = */ __SA_VECLEN_64ELEMS,
        #endif /* __C7X_VEC_SIZE_BYTES__ */
        /* _reserved2       = */ 0
#endif
    };
    return sa;
}

/*----------------------------------------------------------------------------*/
/* DEMONSTRATION FOR SETUP AND USAGE OF A STREAMING ENGINE STREAM WITHOUT     */
/* CIRCULAR ADDRESSING:                                                       */
/*                                                                            */
/* #include <c7x.h>                                                           */
/* #include <stddef.h>                                                        */
/* uint8 se_func(uint32_t *startaddr)                                         */
/* {                                                                          */
/*     int I0;                                                                */
/*     uint8 Vresult;                                                         */
/*     __SE_TEMPLATE_v1 params = __gen_SE_TEMPLATE_v1(); // SE PARAMETERS     */
/*                                                                            */
/*     params.DIMFMT   = __SE_DIMFMT_4D;                                      */
/*     params.ELETYPE  = __SE_ELETYPE_32BIT;                                  */
/*     params.VECLEN   = __SE_VECLEN_4ELEMS; // 4 ELEMENTS                    */
/*                                                                            */
/*     // SETUP TEMPLATE VECTOR BASED ON SETTINGS AND OPEN THE STREAM         */
/*     // BASED ON ITERATION COUNTERS AND DIMENSIONS (IN TERMS OF # OF ELEMS) */
/*     params.ICNT0 = 4;                                                      */
/*     params.ICNT1 = 2;                                                      */
/*     params.DIM1  = 4;                                                      */
/*     params.ICNT2 = 2;                                                      */
/*     params.DIM2  = 8;                                                      */
/*     params.ICNT3 = 4;                                                      */
/*     params.DIM3  = -16;                                                    */
/*                                                                            */
/*     // DECDIM1 WIDTH (0 by default)                                        */
/*     params.DECDIM1_WIDTH = 0;                                              */
/*                                                                            */
/*     // DECDIM2 WIDTH (0 by default)                                        */
/*     params.DECDIM2_WIDTH = 0;                                              */
/*                                                                            */
/*     // LEZR COUNT (0 by default)                                           */
/*     params.LEZR_CNT = 0;                                                   */
/*                                                                            */
/*     __SE1_OPEN((const void*)startaddr, params);                            */
/*                                                                            */
/*     // READ THE STREAM AND ADVANCE THE COUNTERS                            */
/*     for (I0 = 0; I0 < 8; I0++)                                             */
/*     {                                                                      */
/*         uint8 Vout;                                                        */
/*         Vout.lo() = __SE1ADV(uint4);                                       */
/*         Vout.hi() = __SE1ADV(uint4);                                       */
/*                                                                            */
/*         Vresult += Vout;                                                   */
/*     }                                                                      */
/*                                                                            */
/*     // CLOSE THE STREAM                                                    */
/*     __SE1_CLOSE();                                                         */
/*                                                                            */
/*     return Vresult;                                                        */
/* }                                                                          */
/*                                                                            */
/* DEMONSTRATION FOR SETUP AND USAGE OF A STREAMING ENGINE STREAM WITH        */
/* CIRCULAR ADDRESSING:                                                       */
/*                                                                            */
/* #include <c7x.h>                                                           */
/* #include <stddef.h>                                                        */
/* uint16 se_circ_func(uint32_t *startaddr)                                   */
/* {                                                                          */
/*     int I0;                                                                */
/*     uint16 Vresult;                                                        */
/*     __SE_TEMPLATE_v1  params = __gen_SE_TEMPLATE_v1();   // SE PARAMETERS  */
/*                                                                            */
/*     params.DIMFMT    = __SE_DIMFMT_3D;                                     */
/*     params.ELETYPE   = __SE_ELETYPE_32BIT;                                 */
/*     params.VECLEN    = __SE_VECLEN_16ELEMS; // 16 ELEMENTS                 */
/*                                                                            */
/*     // CIRCULAR ADDRESSING BLOCK CONFIGURATION (SEE SPEC FOR DETAILS)      */
/*     params.CBK0 = 0;                    // 512BYTE ENCODING                */
/*                                                                            */
/*     // CIRCULAR ADDRESSING ADDRESS MODE CONFIGURATION                      */
/*     params.AM0 = __SE_AM_CIRC_CBK0;                                        */
/*     params.AM1 = __SE_AM_CIRC_CBK0;                                        */
/*     params.AM2 = __SE_AM_CIRC_CBK0;                                        */
/*                                                                            */
/*     // SETUP TEMPLATE VECTOR BASED ON SETTINGS AND OPEN THE STREAM         */
/*     // BASED ON ITERATION COUNTERS AND DIMENSIONS (IN TERMS OF # OF ELEMS) */
/*     params.ICNT0 = 16;                                                     */
/*     params.ICNT1 = 16;                                                     */
/*     params.DIM1  = 16;                                                     */
/*     params.ICNT2 = 1;                                                      */
/*     params.DIM2  = 0;                                                      */
/*                                                                            */
/*     // DECDIM1 WIDTH (0 by default)                                        */
/*     params.DECDIM1_WIDTH = 0;                                              */
/*                                                                            */
/*     // DECDIM2 WIDTH (0 by default)                                        */
/*     params.DECDIM2_WIDTH = 0;                                              */
/*                                                                            */
/*     // LEZR COUNT (0 by default)                                           */
/*     params.LEZR_CNT      =  0;                                             */
/*                                                                            */
/*     __SE1_OPEN((const void*)startaddr, params);                            */
/*                                                                            */
/*     // READ THE STREAM AND ADVANCE THE COUNTERS                            */
/*     for (I0 = 0; I0 < 16; I0++)                                            */
/*     {                                                                      */
/*         uint16 Vout = __SE1ADV(uint16);                                    */
/*         Vresult += Vout;                                                   */
/*     }                                                                      */
/*                                                                            */
/*     // CLOSE THE STREAM                                                    */
/*     __SE1_CLOSE();                                                         */
/*                                                                            */
/*     return Vresult;                                                        */
/* }                                                                          */
/*                                                                            */
/* DEMONSTRATION FOR SETUP AND USAGE OF A STREAM ADDRESS GENERATOR:           */
/*                                                                            */
/* #include <c7x.h>                                                           */
/* #include <stddef.h>                                                        */
/* uint8 sa_func(uint32_t *startaddr)                                         */
/* {                                                                          */
/*     int I0;                                                                */
/*     uint8 Vresult;                                                         */
/*     __SA_TEMPLATE_v1 params = __gen_SA_TEMPLATE_v1(); // SA PARAMETER      */
/*                                                                            */
/*     params.DIMFMT  = __SA_DIMFMT_4D;                                       */
/*     params.VECLEN  = __SA_VECLEN_4ELEMS; // 4 ELEMENTS                     */
/*                                                                            */
/*     // SETUP TEMPLATE VECTOR BASED ON SETTINGS AND OPEN THE STREAM         */
/*     // BASED ON ITERATION COUNTERS AND DIMENSIONS (IN TERMS OF # OF ELEMS) */
/*     params.ICNT0 = 4;                                                      */
/*     params.ICNT1 = 2;                                                      */
/*     params.DIM1  = 4;                                                      */
/*     params.ICNT2 = 2;                                                      */
/*     params.DIM2  = 8;                                                      */
/*     params.ICNT3 = 4;                                                      */
/*     params.DIM3  = -16;                                                    */
/*                                                                            */
/*     // DECDIM1 WIDTH (0 by default)                                        */
/*     params.DECDIM1_WIDTH = 0;                                              */
/*                                                                            */
/*     // DECDIM2 WIDTH (0 by default)                                        */
/*     params.DECDIM2_WIDTH = 0;                                              */
/*                                                                            */
/*     __SA1_OPEN(params);                                                    */
/*                                                                            */
/*     // READ THE STREAM AND ADVANCE THE COUNTERS                            */
/*     for (I0 = 0; I0 < 8; I0++)                                             */
/*     {                                                                      */
/*         uint8 Vout;                                                        */
/*         Vout.lo() = *__SA1ADV(uint4, startaddr);                           */
/*         Vout.hi() = *__SA1ADV(uint4, startaddr);                           */
/*                                                                            */
/*         Vresult += Vout;                                                   */
/*     }                                                                      */
/*                                                                            */
/*     // CLOSE THE STREAM                                                    */
/*     __SA1_CLOSE();                                                         */
/*                                                                            */
/*     return Vresult;                                                        */
/* }                                                                          */
/*                                                                            */
/*----------------------------------------------------------------------------*/


/*****************************************************************************/
/* STREAMING ENGINE COMMON CONTROLS                                          */
/*****************************************************************************/
/*---------------------------------------------------------------------------*/
/* Implementation details.  Do not use directly.                             */
/*---------------------------------------------------------------------------*/
#if defined(__SE_FEAT_TEMPLATE_V1)
void     __se_open      (const void* addr, uint32_t se_index, __SE_TEMPLATE_v1& templ);
#endif /* __SE_FEAT_TEMPLATE_V1 */
#if defined(__SE_FEAT_TEMPLATE_V2)
void     __se_open      (const void* addr, uint32_t se_index, __SE_TEMPLATE_v2& templ);
#endif /* __SE_FEAT_TEMPLATE_V2 */
#if defined(__SE_FEAT_TEMPLATE_V3)
void     __se_open      (const void* addr, uint32_t se_index, __SE_TEMPLATE_v3& templ);
#endif /* __SE_FEAT_TEMPLATE_V3 */

#if !defined(__C7100__) && !defined(__C7120__)
void     __se_reset     (const void* addr, uint32_t se_index);
#endif /* !__C7100__ && !__C7120__ */

void     __se_close     (uint32_t se_index);
void     __se_break     (uint32_t loop_id, uint32_t se_index);

#if __C7X_VEC_SIZE_BITS__ == 512
__uint16 __se_save      (uint32_t loop_id, uint32_t se_index);
void     __se_restore   (uint32_t loop_id, uint32_t se_index, __uint16 templ);
#endif /* __C7X_VEC_SIZE_BITS__ == 512 */

#if !defined(__C7100__) && !defined(__C7120__)
typedef struct __SE_SAVE_DATA { uint64_t data[32]; } __SE_SAVE_DATA;
void     __se_savest    (__SE_SAVE_DATA *, uint32_t);
void     __se_restoreld (const __SE_SAVE_DATA *, uint32_t);
uint64_t __se_suspend   (uint32_t);
void     __se_resume    (uint32_t, uint64_t);
#endif /* !__C7100__ && !__C7120__ */

/*---------------------------------------------------------------------------*/
/* void __SEn_OPEN(const void *addr, __SE_TEMPLATE)                          */
/*   Opens streaming engine n at address addr.                               */
/*---------------------------------------------------------------------------*/
#define __SE0_OPEN(addr,tmpl) __se_open  (addr, 0U, tmpl)
#define __SE1_OPEN(addr,tmpl) __se_open  (addr, 1U, tmpl)

#if !defined(__C7100__) && !defined(__C7120__)
/*---------------------------------------------------------------------------*/
/* void __SEn_RESET(const void *addr)                                        */
/*   Reopens streaming engine n at address addr with the previous template   */
/*   configuration.                                                          */
/*---------------------------------------------------------------------------*/
#define __SE0_RESET(addr) __se_reset(addr, 0U)
#define __SE1_RESET(addr) __se_reset(addr, 1U)
#endif /* !__C7100__ && !__C7120__ */

/*---------------------------------------------------------------------------*/
/* void __SEn_CLOSE()                                                        */
/*   Closes streaming engine n.                                              */
/*---------------------------------------------------------------------------*/
#define __SE0_CLOSE()         __se_close(0U)
#define __SE1_CLOSE()         __se_close(1U)

/*---------------------------------------------------------------------------*/
/* type __SEn(type)                                                          */
/*   Retrieves a type from streaming engine n where type may be exactly:     */
/*     char, char2, char4, char8, char16, char32, char64                     */
/*     uchar, uchar2, uchar4, uchar8, uchar16, uchar32, uchar64              */
/*                                                                           */
/*     short, short2, short4, short8, short16, short32                       */
/*     ushort, ushort2, ushort4, ushort8, ushort16, ushort32                 */
/*     cchar, cchar2, cchar4, cchar8, cchar16, cchar32                       */
/*                                                                           */
/*     int, int2, int4, int8, int16                                          */
/*     uint, uint2, uint4, uint8, uint16                                     */
/*     float, float2, float4, float8, float16                                */
/*     cshort, cshort2, cshort4, cshort8, cshort16                           */
/*                                                                           */
/*     long, long2, long4, long8                                             */
/*     ulong, ulong2, ulong4, ulong8                                         */
/*     double, double2, double4, double8                                     */
/*     cint, cint2, cint4, cint8                                             */
/*     cfloat, cfloat2, cfloat4, cfloat8                                     */
/*                                                                           */
/*  The specified type cannot be larger than the size of a vector register.  */
/*---------------------------------------------------------------------------*/
#define __SE0(type)           __se_ac_##type(0U, 0U)
#define __SE1(type)           __se_ac_##type(1U, 0U)

/*---------------------------------------------------------------------------*/
/* type __SEnADV(type)                                                       */
/*   Retrieves a type from streaming engine n, then advances that engine.    */
/*   Argument restrictions and return types are the same as __SEn(type).     */
/*---------------------------------------------------------------------------*/
#define __SE0ADV(type)        __se_ac_##type(0U, 1U)
#define __SE1ADV(type)        __se_ac_##type(1U, 1U)

/*---------------------------------------------------------------------------*/
/* void __SEn_BREAK(__uint level)                                            */
/*   Causes streaming engine n to skip all remaining elements for the        */
/*   specified loop level.  level must be a constant.                        */
/*---------------------------------------------------------------------------*/
#define __SE0_BREAK(level)      __se_break(level, 0U)
#define __SE1_BREAK(level)      __se_break(level, 1U)

#if __C7X_VEC_SIZE_BITS__ == 512
/*---------------------------------------------------------------------------*/
/* __uint16 __SEn_SAVE(__uint segment)                                       */
/*   Saves the specified segment from streaming engine n.  segment must be a */
/*   constant.                                                               */
/*---------------------------------------------------------------------------*/
#define __SE0_SAVE(segment) __se_save(segment, 0U)
#define __SE1_SAVE(segment) __se_save(segment, 1U)

/*---------------------------------------------------------------------------*/
/* void __SEn_RESTORE(__uint segment, __uint16 state)                        */
/*   Restores state into the specified segment of streaming engine n.        */
/*---------------------------------------------------------------------------*/
#define __SE0_RESTORE(segment, state) __se_restore(segment, 0U, state)
#define __SE1_RESTORE(segment, state) __se_restore(segment, 1U, state)
#endif /* __C7X_VEC_SIZE_BITS__ == 512 */

#if !defined(__C7100__) && !defined(__C7120__)
/*---------------------------------------------------------------------------*/
/* void __SEn_SAVEST(__SE_SAVE_DATA *mem)                                    */
/*   Saves the state of streaming engine n to mem.                           */
/*---------------------------------------------------------------------------*/
#define __SE0_SAVEST(mem) __se_savest(mem, 0U)
#define __SE1_SAVEST(mem) __se_savest(mem, 1U)

/*---------------------------------------------------------------------------*/
/* void __SEn_RESTORELD(const __SE_SAVE_DATA *mem)                           */
/*   Restores the state of streaming engine n from mem.                      */
/*---------------------------------------------------------------------------*/
#define __SE0_RESTORELD(mem) __se_restoreld(mem, 0U)
#define __SE1_RESTORELD(mem) __se_restoreld(mem, 1U)

/*---------------------------------------------------------------------------*/
/* ulong __SEn_SUSPEND()                                                     */
/*   Suspends execution of streaming engine n. Returns 1 if the streaming    */
/*   engine was open; otherwise returns 0. The return value is meant for use */
/*   with __SEn_RESUME().                                                    */
/*---------------------------------------------------------------------------*/
#define __SE0_SUSPEND() __se_suspend(0U)
#define __SE1_SUSPEND() __se_suspend(1U)

/*---------------------------------------------------------------------------*/
/* void __SEn_RESUME(ulong)                                                  */
/*   Resumes execution of streaming engine n. If the argument is 1, the      */
/*   streaming engine is restored to an open state. If the argument is 0,    */
/*   the streaming engine will remain closed. The argument is expected to be */
/*   the prior output of __SEn_SUSPEND().                                    */
/*---------------------------------------------------------------------------*/
#define __SE0_RESUME(state) __se_resume(0U, state)
#define __SE1_RESUME(state) __se_resume(1U, state)
#endif /* !__C7100__ && !__C7120__ */

/*---------------------------------------------------------------------------*/
/* Implementation details.  Do not use directly.                             */
/*---------------------------------------------------------------------------*/
// __se_ac declarations
// 8 bit
extern int8_t (*__se_ac_char)(int, int);
extern uint8_t (*__se_ac_uchar)(int, int);

// 16 bit
extern int16_t (*__se_ac_short)(int, int);
extern uint16_t (*__se_ac_ushort)(int, int);
extern cchar (*__se_ac_cchar)(int, int);
extern char2 (*__se_ac_char2)(int, int);
extern uchar2 (*__se_ac_uchar2)(int, int);

// 32 bit
extern int32_t (*__se_ac_int)(int, int);
extern uint32_t (*__se_ac_uint)(int, int);
extern float (*__se_ac_float)(int, int);
extern cshort (*__se_ac_cshort)(int, int);
extern char4 (*__se_ac_char4)(int, int);
extern uchar4 (*__se_ac_uchar4)(int, int);
extern short2 (*__se_ac_short2)(int, int);
extern ushort2 (*__se_ac_ushort2)(int, int);
extern cchar2 (*__se_ac_cchar2)(int, int);

// 64 bit
extern int64_t (*__se_ac_long)(int, int);
extern uint64_t (*__se_ac_ulong)(int, int);
extern double (*__se_ac_double)(int, int);
extern cint (*__se_ac_cint)(int, int);
extern cfloat (*__se_ac_cfloat)(int, int);
extern char8 (*__se_ac_char8)(int, int);
extern uchar8 (*__se_ac_uchar8)(int, int);
extern short4 (*__se_ac_short4)(int, int);
extern ushort4 (*__se_ac_ushort4)(int, int);
extern int2 (*__se_ac_int2)(int, int);
extern uint2 (*__se_ac_uint2)(int, int);
extern float2 (*__se_ac_float2)(int, int);
extern cchar4 (*__se_ac_cchar4)(int, int);
extern cshort2 (*__se_ac_cshort2)(int, int);

// 128 bit
extern clong (*__se_ac_clong)(int, int);
extern cdouble (*__se_ac_cdouble)(int, int);
extern char16 (*__se_ac_char16)(int, int);
extern uchar16 (*__se_ac_uchar16)(int, int);
extern short8 (*__se_ac_short8)(int, int);
extern ushort8 (*__se_ac_ushort8)(int, int);
extern int4 (*__se_ac_int4)(int, int);
extern uint4 (*__se_ac_uint4)(int, int);
extern float4 (*__se_ac_float4)(int, int);
extern long2 (*__se_ac_long2)(int, int);
extern ulong2 (*__se_ac_ulong2)(int, int);
extern double2 (*__se_ac_double2)(int, int);
extern cchar8 (*__se_ac_cchar8)(int, int);
extern cshort4 (*__se_ac_cshort4)(int, int);
extern cint2 (*__se_ac_cint2)(int, int);
extern cfloat2 (*__se_ac_cfloat2)(int, int);

// 256 bit
extern char32 (*__se_ac_char32)(int, int);
extern uchar32 (*__se_ac_uchar32)(int, int);
extern short16 (*__se_ac_short16)(int, int);
extern ushort16 (*__se_ac_ushort16)(int, int);
extern int8 (*__se_ac_int8)(int, int);
extern uint8 (*__se_ac_uint8)(int, int);
extern float8 (*__se_ac_float8)(int, int);
extern long4 (*__se_ac_long4)(int, int);
extern ulong4 (*__se_ac_ulong4)(int, int);
extern double4 (*__se_ac_double4)(int, int);
extern cchar16 (*__se_ac_cchar16)(int, int);
extern cshort8 (*__se_ac_cshort8)(int, int);
extern cint4 (*__se_ac_cint4)(int, int);
extern cfloat4 (*__se_ac_cfloat4)(int, int);
extern clong2 (*__se_ac_clong2)(int, int);
extern cdouble2 (*__se_ac_cdouble2)(int, int);

#if __C7X_VEC_SIZE_BITS__ > 256
// 512 bit
extern char64 (*__se_ac_char64)(int, int);
extern uchar64 (*__se_ac_uchar64)(int, int);
extern short32 (*__se_ac_short32)(int, int);
extern ushort32 (*__se_ac_ushort32)(int, int);
extern int16 (*__se_ac_int16)(int, int);
extern uint16 (*__se_ac_uint16)(int, int);
extern float16 (*__se_ac_float16)(int, int);
extern long8 (*__se_ac_long8)(int, int);
extern ulong8 (*__se_ac_ulong8)(int, int);
extern double8 (*__se_ac_double8)(int, int);
extern cchar32 (*__se_ac_cchar32)(int, int);
extern cshort16 (*__se_ac_cshort16)(int, int);
extern cint8 (*__se_ac_cint8)(int, int);
extern cfloat8 (*__se_ac_cfloat8)(int, int);
extern clong4 (*__se_ac_clong4)(int, int);
extern cdouble4 (*__se_ac_cdouble4)(int, int);
#endif /* __C7X_VEC_SIZE_BITS__ > 256 */


/*----------------------------------------------------------------------------*/
/* Function used to read scalar values from SE.  Implementation detail.       */
/*----------------------------------------------------------------------------*/
template<class STYPE,
         std::enable_if_t<std::is_arithmetic<STYPE>::value, int> = 0>
STYPE read(streaming_engine* desired_se)
{
    uint64_t res;
    get_unsigned_value((*desired_se).get_se(), res, 0);
    return (STYPE)res;
}

/*----------------------------------------------------------------------------*/
/* Function used to read vector values from SE.  Implementation detail.       */
/*----------------------------------------------------------------------------*/
template<class VTYPE,
         std::enable_if_t<!std::is_arithmetic<VTYPE>::value &&
         VTYPE::NUM_ELEM != 1, int> = 0>
VTYPE read(streaming_engine* desired_se)
{
    return VTYPE((*desired_se).get_se());
}

/*----------------------------------------------------------------------------*/
/* Function used to read complex values from SE.  Implementation detail.      */
/*----------------------------------------------------------------------------*/
template<class CTYPE,
         std::enable_if_t<!std::is_arithmetic<CTYPE>::value &&
                          CTYPE::NUM_ELEM == 1, int> = 0>
CTYPE read(streaming_engine* desired_se)
{
    return CTYPE((*desired_se).get_se());
}

/*----------------------------------------------------------------------------*/
/* SE read function that external interface will map to.  Implementation      */
/* detail.                                                                    */
/*----------------------------------------------------------------------------*/
template<class TYPE>
TYPE se_read(int se_index, int adv)
{
    streaming_engine* desired_se = nullptr;
    if (se_index == 0) desired_se = &SE0;
    else if (se_index == 1) desired_se = &SE1;

    // Read based on type
    TYPE read_value = read<TYPE>(desired_se);

    // Now advance if needed
    if (adv)
    {
        (*desired_se).setAdvance();
        (*desired_se).advance();
    }

    return read_value;
}

/*----------------------------------------------------------------------------*/
/* Streaming Engine Shortcut-Open Arguments.                                  */
/* The type of shortcut argument can be used in place of a vector template to */
/* open a stream using __SE0_OPEN_SHORTCUT() or __SE1_OPEN_SHORTCUT().        */
/*----------------------------------------------------------------------------*/
typedef enum
{
    __STROPENB   = 0x0,
    __STROPENBH  = 0x1,
    __STROPENBUH = 0x2,
    __STROPENH   = 0x3,
    __STROPENHW  = 0x4,
    __STROPENHUW = 0x5,
    __STROPENW   = 0x6,
    __STROPENWD  = 0x7,
    __STROPENWUD = 0x8,
    __STROPEND   = 0x9,
    __SE_SHORTCUT_LAST = 0x9 /* Don't use directly. */
} __SE_SHORTCUT;

/*----------------------------------------------------------------------------*/
/* Implementation detail.  Do not use directly.                               */
/*----------------------------------------------------------------------------*/
void       __se_open_sc      (const void* addr , uint32_t se_index, __SE_SHORTCUT templ);

/*----------------------------------------------------------------------------*/
/* void __SEn_OPEN_SHORTCUT(addr, sc)                                         */
/*   Open streaming engine n at addr using configuration sc.                  */
/*----------------------------------------------------------------------------*/
#define __SE0_OPEN_SHORTCUT(addr, sc) __se_open_sc(addr, 0U, sc)
#define __SE1_OPEN_SHORTCUT(addr, sc) __se_open_sc(addr, 1U, sc)

/*----------------------------------------------------------------------------*/
/* Block Cache Maintenance Instruction Arguments                              */
/* These arguments are used with __se_cache_op() to operate on a contiguous   */
/* block of addresses.                                                        */
/*----------------------------------------------------------------------------*/
typedef enum
{
    /* Sharable */
    __DCCIC     = 0x14, /* DataCache Clean/Invalidate to Point of Coherence   */
    __DCCMIC    = 0x15, /* DataCache Invalidate to Point of Coherence         */
    __BLK_OPTYPE_LAST = 0x15 /* Don't use directly. */
} __BLK_OPTYPE;

/*----------------------------------------------------------------------------*/
/* __se_cache_op(const void*, __BLK_OPTYPE, __uint bytes)                     */
/*   Direct access to BLKCMO instruction.                                     */
/*----------------------------------------------------------------------------*/
/* No operation performed under host emulation. */
void       __se_cache_op     (const void*, __BLK_OPTYPE,  uint32_t);

/*----------------------------------------------------------------------------*/
/* Block Cache Preload Instruction Arguments                                  */
/* These arguments are used with __se_cache_preload() to operate on a         */
/* contiguous block of addresses.                                             */
/*----------------------------------------------------------------------------*/
typedef enum
{
    __L2R = 0x0, /* Preload to L2 for reading */
    __L2W = 0x1, /* Preload to L2 for writing */
    __L3R = 0x2, /* Preload to L3 for reading */
    __L3W = 0x3, /* Preload to L3 for writing */
    __BLK_PLDTYPE_LAST = 0x3 /* Don't use directly. */
} __BLK_PLDTYPE;

#if defined(__C7100__) || defined(__C7120__)
/*----------------------------------------------------------------------------*/
/* __se_cache_preload(const void*, __BLK_PLDTYPE, __uint bytes)               */
/*   Direct access to BLKPLD instruction.                                     */
/*----------------------------------------------------------------------------*/
/* No operation performed under host emulation. */
void       __se_cache_preload(const void*, __BLK_PLDTYPE, uint32_t);
#endif /* __C7100__ || __C7120__ */

/*----------------------------------------------------------------------------*/
/* __se_cache_wait()                                                          */
/*   Blocks execution until __se_cache_preload or __se_cache_op completes.    */
/*----------------------------------------------------------------------------*/
void       __se_cache_wait();

/*----------------------------------------------------------------------------*/
/* Streaming Engine param size is 64 bytes. All the above options             */
/* including iteration counts(ICNT) and dimensions(DIM) are packed in a       */
/* 512bit vector. Use this macro to derrive offsets while writing to L1D SRAM */
/*----------------------------------------------------------------------------*/
#define SE_PARAM_SIZE (64)

/*----------------------------------------------------------------------------*/
/* Stream Address Generator param size is 64 bytes. All the above options     */
/* including iteration counts(ICNT) and dimensions(DIM) are packed in a       */
/* 512bit vector. Use this macro to derrive offsets while writing to L1D SRAM */
/*----------------------------------------------------------------------------*/
#define SA_PARAM_SIZE (64)

/*****************************************************************************/
/* STREAMING ADDRESS GENERATOR COMMON CONTROLS                               */
/*****************************************************************************/
/*---------------------------------------------------------------------------*/
/* Implementation details.  Do not use directly.                             */
/*---------------------------------------------------------------------------*/
void     __sa_open     (uint32_t sa_index, __SA_TEMPLATE_v1& templ);

#if !defined(__C7100__) && !defined(__C7120__)
void     __sa_reset   (uint32_t sa_index);
#endif /* !__C7100__ && !__C7120__ */

void     __sa_close    (uint32_t sa_index);
void     __sa_break    (uint32_t loop_id, uint32_t sa_index);

#if __C7X_VEC_SIZE_BITS__ == 512
void     __sa_set_cr   (uint32_t sa_index, __uint16 reg_val);
__uint16 __sa_get_cr   (uint32_t sa_index);
__uint16 __sa_get_cntr (uint32_t sa_index);
#define __sa_get_cntr0(x) __sa_get_cntr(x)
#ifndef __C7100__
__uint16 __sa_get_cntr1(uint32_t sa_index);
#endif /* ! __C7100__ */
#endif /* __C7X_VEC_SIZE_BITS__ == 512 */

__vpred  __sa_vpred    (uint32_t sa_index, int sa_scale);
void* __sa(uint32_t, uint32_t, const void *);
void* __sa_adv(uint32_t, uint32_t, const void *);

#if !defined(__C7100__) && !defined(__C7120__)
typedef struct __SA_SAVE_DATA { uint64_t data[24]; } __SA_SAVE_DATA;
void     __sa_savest    (__SA_SAVE_DATA *, uint32_t);
void     __sa_restoreld (const __SA_SAVE_DATA *, uint32_t);
uint64_t __sa_suspend   (uint32_t);
void     __sa_resume    (uint32_t, uint64_t);
#endif /* !__C7100__ && !__C7120__ */

#define SABOOL_decl(type, len) bool##len __sa_bool_##type##len(__vpred a);

// 16 bits
SABOOL_decl(char, 2)
SABOOL_decl(uchar, 2)

// 32 bits
SABOOL_decl(char, 4)
SABOOL_decl(uchar, 4)
SABOOL_decl(cchar, 2)
SABOOL_decl(short, 2)
SABOOL_decl(ushort, 2)

// 64 bits
SABOOL_decl(char, 8)
SABOOL_decl(uchar, 8)
SABOOL_decl(cchar, 4)
SABOOL_decl(short, 4)
SABOOL_decl(ushort, 4)
SABOOL_decl(cshort, 2)
SABOOL_decl(int, 2)
SABOOL_decl(uint, 2)
SABOOL_decl(float, 2)

// 128 bits
SABOOL_decl(char, 16)
SABOOL_decl(uchar, 16)
SABOOL_decl(cchar, 8)
SABOOL_decl(short, 8)
SABOOL_decl(ushort, 8)
SABOOL_decl(cshort, 4)
SABOOL_decl(int, 4)
SABOOL_decl(uint, 4)
SABOOL_decl(float, 4)
SABOOL_decl(cint, 2)
SABOOL_decl(cfloat, 2)
SABOOL_decl(long, 2)
SABOOL_decl(ulong, 2)
SABOOL_decl(double, 2)

// 256 bits
SABOOL_decl(char, 32)
SABOOL_decl(uchar, 32)
SABOOL_decl(cchar, 16)
SABOOL_decl(short, 16)
SABOOL_decl(ushort, 16)
SABOOL_decl(cshort, 8)
SABOOL_decl(int, 8)
SABOOL_decl(uint, 8)
SABOOL_decl(float, 8)
SABOOL_decl(cint, 4)
SABOOL_decl(cfloat, 4)
SABOOL_decl(long, 4)
SABOOL_decl(ulong, 4)
SABOOL_decl(double, 4)
SABOOL_decl(clong, 2)
SABOOL_decl(cdouble, 2)

#if __C7X_VEC_SIZE_BITS__ > 256
// 512 bits
SABOOL_decl(char, 64)
SABOOL_decl(uchar, 64)
SABOOL_decl(cchar, 32)
SABOOL_decl(short, 32)
SABOOL_decl(ushort, 32)
SABOOL_decl(cshort, 16)
SABOOL_decl(int, 16)
SABOOL_decl(uint, 16)
SABOOL_decl(float, 16)
SABOOL_decl(cint, 8)
SABOOL_decl(cfloat, 8)
SABOOL_decl(long, 8)
SABOOL_decl(ulong, 8)
SABOOL_decl(double, 8)
SABOOL_decl(clong, 4)
SABOOL_decl(cdouble, 4)
#endif /* __C7X_VEC_SIZE_BITS__ > 256 */


/*----------------------------------------------------------------------------*/
/* Function used to abstract core logic in retrieving address from SA.        */
/* Implementation detail.                                                     */
/*----------------------------------------------------------------------------*/
uint64_t get_sa_address(int sa_index, int scale, const void* baseptr, bool adv);

/*----------------------------------------------------------------------------*/
/* Function used to retrieve correct pointer type from sa address calculation.*/
/* Used to ensure that the correct component type pointer is used when        */
/* referencing vectors in memory.  Implementation detail.                     */
/*----------------------------------------------------------------------------*/
template <typename VTYPE,
          typename = typename std::enable_if_t<!(std::is_arithmetic<VTYPE>::value)>>
typename VTYPE::ELEM_TYPE* get_sa_address_pntr(int sa_index,
                                               int scale,
                                               const void* baseptr,
                                               bool adv)
{
    return (typename VTYPE::ELEM_TYPE*)get_sa_address(sa_index, scale, baseptr, adv);
}

template <typename STYPE,
          typename = typename std::enable_if_t<(std::is_arithmetic<STYPE>::value)>>
STYPE* get_sa_address_pntr(int sa_index, int scale, const void* baseptr, bool adv)
{
    return (STYPE*)get_sa_address(sa_index, scale, baseptr, adv);
}

/*---------------------------------------------------------------------------*/
/* void __SAn_OPEN(__SA_TEMPLATE)                                            */
/*   Opens streaming address generator n.                                    */
/*---------------------------------------------------------------------------*/
#define __SA0_OPEN(tmpl) __sa_open(0U, tmpl)
#define __SA1_OPEN(tmpl) __sa_open(1U, tmpl)
#define __SA2_OPEN(tmpl) __sa_open(2U, tmpl)
#define __SA3_OPEN(tmpl) __sa_open(3U, tmpl)

#if !defined(__C7100__) && !defined(__C7120__)
/*---------------------------------------------------------------------------*/
/* void __SAn_RESET()                                                        */
/*   Reopens streaming address generator n with the previous template        */
/*   configuration.                                                          */
/*---------------------------------------------------------------------------*/
#define __SA0_RESET() __sa_reset(0U)
#define __SA1_RESET() __sa_reset(1U)
#define __SA2_RESET() __sa_reset(2U)
#define __SA3_RESET() __sa_reset(3U)
#endif /* !__C7100__ && !__C7120__ */

/*---------------------------------------------------------------------------*/
/* void __SAn_CLOSE()                                                        */
/*   Closes streaming address generator n.                                   */
/*---------------------------------------------------------------------------*/
#define __SA0_CLOSE()           __sa_close(0U)
#define __SA1_CLOSE()           __sa_close(1U)
#define __SA2_CLOSE()           __sa_close(2U)
#define __SA3_CLOSE()           __sa_close(3U)

#if !defined(__C7100__) && !defined(__C7120__)
/*---------------------------------------------------------------------------*/
/* void __SAn_SAVEST(__SA_SAVE_DATA *mem)                                    */
/*   Saves the state of streaming address generator n to mem.                */
/*---------------------------------------------------------------------------*/
#define __SA0_SAVEST(mem) __sa_savest(mem, 0U)
#define __SA1_SAVEST(mem) __sa_savest(mem, 1U)
#define __SA2_SAVEST(mem) __sa_savest(mem, 2U)
#define __SA3_SAVEST(mem) __sa_savest(mem, 3U)

/*---------------------------------------------------------------------------*/
/* void __SAn_RESTORELD(const __SA_SAVE_DATA *mem)                           */
/*   Restores the state of streaming address generator n from mem.           */
/*---------------------------------------------------------------------------*/
#define __SA0_RESTORELD(mem) __sa_restoreld(mem, 0U)
#define __SA1_RESTORELD(mem) __sa_restoreld(mem, 1U)
#define __SA2_RESTORELD(mem) __sa_restoreld(mem, 2U)
#define __SA3_RESTORELD(mem) __sa_restoreld(mem, 3U)

/*---------------------------------------------------------------------------*/
/* ulong __SAn_SUSPEND()                                                     */
/*   Suspends execution of streaming address generator n. Returns 1 if the   */
/*   streaming address generator was open; otherwise returns 0. The return   */
/*   value is meant for use with __SAn_RESUME().                             */
/*---------------------------------------------------------------------------*/
#define __SA0_SUSPEND() __sa_suspend(0U)
#define __SA1_SUSPEND() __sa_suspend(1U)
#define __SA2_SUSPEND() __sa_suspend(2U)
#define __SA3_SUSPEND() __sa_suspend(3U)

/*---------------------------------------------------------------------------*/
/* void __SAn_RESUME(ulong)                                                  */
/*   Resumes execution of streaming address generator n. If the argument is  */
/*   1, the streaming address generator is restored to an open state. If the */
/*   argument is 0, the streaming address generator will remain closed. The  */
/*   argument is expected to be the prior output of __SAn_SUSPEND().         */
/*---------------------------------------------------------------------------*/
#define __SA0_RESUME(state) __sa_resume(0U, state)
#define __SA1_RESUME(state) __sa_resume(1U, state)
#define __SA2_RESUME(state) __sa_resume(2U, state)
#define __SA3_RESUME(state) __sa_resume(3U, state)
#endif /* !__C7100__ && !__C7120__ */

/*---------------------------------------------------------------------------*/
/* type *__SAn(type, baseptr)                                                */
/*   Retrieves the current address from streaming address generator n.  The  */
/*   address will be based off of baseptr and point to type, where type may  */
/*   be any scalar or vector type that:                                      */
/*     1) Has a total size no larger than 512 bits.                          */
/*     2) Has an element size no larger than 64 bits.  (A complex vector     */
/*        considers the complex type to be the element type.)                */
/*   Typedef'd types and qualified types are allowed.  For example, the      */
/*   following are all legal:                                                */
/*     - __SA0(int2, baseptr) -> returns int2*                               */
/*     - __SA0(__int2, baseptr) -> returns __int2*                           */
/*     - __SA0(const __int2, baseptr) -> returns const __int2*               */
/*                                                                           */
/*  The specified type cannot be larger than the size of a vector register.  */
/*---------------------------------------------------------------------------*/
#define __SA0(_type, baseptr)    (_type*) __sa(0U, _c70_he_detail::sa_scale<_type>::value, baseptr)
#define __SA1(_type, baseptr)    (_type*) __sa(1U, _c70_he_detail::sa_scale<_type>::value, baseptr)
#define __SA2(_type, baseptr)    (_type*) __sa(2U, _c70_he_detail::sa_scale<_type>::value, baseptr)
#define __SA3(_type, baseptr)    (_type*) __sa(3U, _c70_he_detail::sa_scale<_type>::value, baseptr)

/*---------------------------------------------------------------------------*/
/* type *__SAnADV(type, baseptr)                                             */
/*   Retrieves the current address from streaming address generator n, then  */
/*   advances that generator.  Argument restrictions and return types are    */
/*   the same as __SAn(type, baseptr).                                       */
/*---------------------------------------------------------------------------*/
#define __SA0ADV(_type, baseptr) (_type*) __sa_adv(0U, _c70_he_detail::sa_scale<_type>::value, baseptr)
#define __SA1ADV(_type, baseptr) (_type*) __sa_adv(1U, _c70_he_detail::sa_scale<_type>::value, baseptr)
#define __SA2ADV(_type, baseptr) (_type*) __sa_adv(2U, _c70_he_detail::sa_scale<_type>::value, baseptr)
#define __SA3ADV(_type, baseptr) (_type*) __sa_adv(3U, _c70_he_detail::sa_scale<_type>::value, baseptr)

/*---------------------------------------------------------------------------*/
/* void __SAn_BREAK(level)                                                   */
/*   Causes streaming address generator n to skip all remaining elements for */
/*   the specified loop level.  level must be a constant.                    */
/*---------------------------------------------------------------------------*/
#define __SA0_BREAK(level)      __sa_break(level, 0U)
#define __SA1_BREAK(level)      __sa_break(level, 1U)
#define __SA2_BREAK(level)      __sa_break(level, 2U)
#define __SA3_BREAK(level)      __sa_break(level, 3U)

#if __C7X_VEC_SIZE_BITS__ == 512
/*---------------------------------------------------------------------------*/
/* void __SAn_SET_CR(__uint16 data)                                          */
/*   Set the contents of the streaming address generator n's configuration   */
/*   control register.                                                       */
/*---------------------------------------------------------------------------*/
#define __SA0_SET_CR(data)      __sa_set_cr(0U, data)
#define __SA1_SET_CR(data)      __sa_set_cr(1U, data)
#define __SA2_SET_CR(data)      __sa_set_cr(2U, data)
#define __SA3_SET_CR(data)      __sa_set_cr(3U, data)

/*---------------------------------------------------------------------------*/
/* __uint16 __SAn_GET_CR()                                                   */
/*   Retrieve the contents of streaming address generator n's configuration  */
/*   control register.                                                       */
/*---------------------------------------------------------------------------*/
#define __SA0_GET_CR()          __sa_get_cr(0U)
#define __SA1_GET_CR()          __sa_get_cr(1U)
#define __SA2_GET_CR()          __sa_get_cr(2U)
#define __SA3_GET_CR()          __sa_get_cr(3U)

/*---------------------------------------------------------------------------*/
/* __uint16 __SAn_GET_CNTR0()                                                */
/*   Retrieve the contents of streaming address generator n's counter 0      */
/*   control register.                                                       */
/*---------------------------------------------------------------------------*/
#define __SA0_GET_CNTR0()       __sa_get_cntr0(0U)
#define __SA1_GET_CNTR0()       __sa_get_cntr0(1U)
#define __SA2_GET_CNTR0()       __sa_get_cntr0(2U)
#define __SA3_GET_CNTR0()       __sa_get_cntr0(3U)

#if !defined(__C7100__)
/*---------------------------------------------------------------------------*/
/* __uint16 __SAn_GET_CNTR1()                                                */
/*   Retrieve the contents of streaming address generator n's counter 1      */
/*   control register.                                                       */
/*---------------------------------------------------------------------------*/
#define __SA0_GET_CNTR1()       __sa_get_cntr1(0U)
#define __SA1_GET_CNTR1()       __sa_get_cntr1(1U)
#define __SA2_GET_CNTR1()       __sa_get_cntr1(2U)
#define __SA3_GET_CNTR1()       __sa_get_cntr1(3U)
#endif /* !__C7100__ */
#endif /* __C7X_VEC_SIZE_BITS__ == 512 */

/*----------------------------------------------------------------------------*/
/* __vpred __SAn_VPRED(type)                                                  */
/*   Extracts the vector predicate associated with streaming address generator*/
/*   n, scaled for type, where type may be exactly:                           */
/*     char, char2, char4, char8, char16, char32, char64                      */
/*     uchar, uchar2, uchar4, uchar8, uchar16, uchar32, uchar64               */
/*                                                                            */
/*     short, short2, short4, short8, short16, short32                        */
/*     ushort, ushort2, ushort4, ushort8, ushort16, ushort32                  */
/*     cchar, cchar2, cchar4, cchar8, cchar16, cchar32                        */
/*                                                                            */
/*     int, int2, int4, int8, int16                                           */
/*     uint, uint2, uint4, uint8, uint16                                      */
/*     float, float2, float4, float8, float16                                 */
/*     cshort, cshort2, cshort4, cshort8, cshort16                            */
/*                                                                            */
/*     long, long2, long4, long8                                              */
/*     ulong, ulong2, ulong4, ulong8                                          */
/*     double, double2, double4, double8                                      */
/*     cint, cint2, cint4, cint8                                              */
/*     cfloat, cfloat2, cfloat4, cfloat8                                      */
/*                                                                            */
/* NOTE: According to C rules, the order in which paramaters of a call are    */
/*   evaluated is unspecified, such that the shorthand way of using these     */
/*   predicates:                                                              */
/*     __vstore_pred(__SA0_VPRED(int16), __SA0ADV(int16, ptr), data)          */
/*   Invokes undefined behavior because SA0ADV modifies the value SA0_VPRED.  */
/*----------------------------------------------------------------------------*/
#define __SA0_VPRED(_type)  __sa_vpred(0U, _c70_he_detail::sa_scale<_type>::value)
#define __SA1_VPRED(_type)  __sa_vpred(1U, _c70_he_detail::sa_scale<_type>::value)
#define __SA2_VPRED(_type)  __sa_vpred(2U, _c70_he_detail::sa_scale<_type>::value)
#define __SA3_VPRED(_type)  __sa_vpred(3U, _c70_he_detail::sa_scale<_type>::value)

/*----------------------------------------------------------------------------*/
/* boolv __SAn_BOOL(type)                                                     */
/*   Extracts the vector predicate associated with streaming address generator*/
/*   n as a boolean vector.  Argument restrictions are the same as            */
/*   __SAn_VPRED(type).  boolv is a boolean vector with lanes equal to the    */
/*   number of lanes in type.  For example, if type is int2, boolv will be    */
/*   __bool2.                                                                 */
/*----------------------------------------------------------------------------*/
#define __SA0_BOOL(_type)   __sa_bool_##_type(__sa_vpred(0U, _c70_he_detail::sa_scale<_type>::value))
#define __SA1_BOOL(_type)   __sa_bool_##_type(__sa_vpred(1U, _c70_he_detail::sa_scale<_type>::value))
#define __SA2_BOOL(_type)   __sa_bool_##_type(__sa_vpred(2U, _c70_he_detail::sa_scale<_type>::value))
#define __SA3_BOOL(_type)   __sa_bool_##_type(__sa_vpred(3U, _c70_he_detail::sa_scale<_type>::value))

#endif /* C7X_STRM_H_ */
