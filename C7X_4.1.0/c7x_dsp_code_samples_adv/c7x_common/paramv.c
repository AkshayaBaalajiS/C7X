/*
* module name       : c7x_common
*
* module descripton : Common utility functions
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/
#include "paramv.h"

#define ALIGN_ADDR (64 - 1)
#define ALIGN_DIMS (64 - 1)

static char eleType[16][20] =
{
  "8BIT",
  "16BIT",
  "32BIT",
  "64BIT",
  "NA",
  "NA",
  "NA",
  "NA",
  "8BIT_CMPLX_NOSWAP",
  "16BIT_CMPLX_NOSWAP",
  "32BIT_CMPLX_NOSWAP",
  "64BIT_CMPLX_NOSWAP",
  "8BIT_CMPLX_SWAP",
  "16BIT_CMPLX_SWAP",
  "32BIT_CMPLX_SWAP",
  "64BIT_CMPLX_SWAP"
};

static char transposeType[7][10] =
{
 "OFF",
 "8BIT",
 "16BIT",
 "32BIT",
 "64BIT",
 "128BIT",
 "256BIT"
};

static char promoteType[8][15] =
{
 "OFF",
 "2X_ZEROEXT",
 "4X_ZEROEXT",
 "8X_ZEROEXT",
 "NA",
 "2X_SIGNEXT",
 "4X_SIGNEXT",
 "8X_SIGNEXT"
};

static char veclenType[7][10] =
{
 "1ELEM",
 "2ELEMS",
 "4ELEMS",
 "8ELEMS",
 "16ELEMS",
 "32ELEMS",
 "64ELEMS"
};

static char dimfmtType[6][10] =
{
  "1D",
  "2D",
  "3D",
  "4D",
  "5D",
  "6D"
};

static char eldupType[7][10] =
{
  "OFF",
  "2X",
  "4X",
  "8X",
  "16X",
  "32X",
  "64X"
};

static char grpdupType[2][10] =
{
  "OFF",
  "ON"
};

static char decimType[3][10] =
{
  "OFF",
  "2:1",
  "4:1"
};

static char dirType[2][10] =
{
 "INC",
 "DEC"
};

static char decdimType[6][10] =
{
 "DECDIM0",
 "DECDIM1",
 "DECDIM2",
 "DECDIM3",
 "DECDIM4",
 "DECDIM5"
};

static char lezrType[7][15] =
{
  "SE_LEZR_OFF",
  "SE_LEZR_ICNT0",
  "SE_LEZR_ICNT1",
  "SE_LEZR_ICNT2",
  "SE_LEZR_ICNT3",
  "SE_LEZR_ICNT4",
  "SE_LEZR_ICNT5"
};

static char alignType[2][10] =
{
  "NA",
  "A"
};

void displaySAParam(void *baseAddr, __STRM_TEMPLATE param, int32_t saNum)
{
    uint32_t baseAddrAlign = 1;
    uint32_t dim1Align = 1;
    uint32_t dim2Align = 1;
    uint32_t dim3Align = 1;
    uint32_t dim4Align = 1;
    uint32_t dim5Align = 1;

    __SA_FLAGS saFlags = __get_SA_FLAGS(param);

    uint32_t ICNT0 = __get_ICNT0(param);
    uint32_t ICNT1 = __get_ICNT1(param);
    uint32_t ICNT2 = __get_ICNT2(param);
    uint32_t ICNT3 = __get_ICNT3(param);
    uint32_t ICNT4 = __get_ICNT4(param);
    uint32_t ICNT5 = __get_ICNT5(param);

    int32_t DIM1 = __get_DIM1(param);
    int32_t DIM2 = __get_DIM2(param);
    int32_t DIM3 = __get_DIM3(param);
    int32_t DIM4 = __get_DIM4(param);
    int32_t DIM5 = __get_DIM5(param);

    if((uint64_t)baseAddr & ALIGN_ADDR) { baseAddrAlign = 0; }
    if(DIM1 & ALIGN_DIMS) { dim1Align = 0; }
    if(DIM2 & ALIGN_DIMS) { dim2Align = 0; }
    if(DIM3 & ALIGN_DIMS) { dim3Align = 0; }
    if(DIM4 & ALIGN_DIMS) { dim4Align = 0; }
    if(DIM5 & ALIGN_DIMS) { dim5Align = 0; }

    dim1Align *= baseAddrAlign;
    dim2Align *= baseAddrAlign;
    dim3Align *= baseAddrAlign;
    dim4Align *= baseAddrAlign;
    dim5Align *= baseAddrAlign;

    int32_t DECDIM1_WIDTH = __get_DECDIM1_WIDTH(param);
    int32_t DECDIM2_WIDTH = __get_DECDIM2_WIDTH(param);

    printf("-----------------------------------------------------------------------------\n");
    printf("SA %d open at 0x%016llX - %s(64), (A - aligned, NA - not aligned)\n", saNum, (uint64_t)baseAddr, alignType[baseAddrAlign]);
    printf("-----------------------------------------------------------------------------\n");
    printf("DECDIM1   = %-25s | DECDIM1_WIDTH = %d \n", decdimType[saFlags.DECDIM1], DECDIM1_WIDTH);
    printf("DECDIM2   = %-25s | DECDIM2_WIDTH = %d \n", decdimType[saFlags.DECDIM2], DECDIM2_WIDTH);
    printf("DIMFMT    = %-25s | \n", dimfmtType[saFlags.DIMFMT]);
    printf("VECLEN    = %-25s | ICNT0 = %-5d | \n", veclenType[saFlags.VECLEN], ICNT0);
    printf("            %-25s | ICNT1 = %-5d | DIM1 = %-5d - %-2s(64)\n", "", ICNT1, DIM1, alignType[dim1Align]);
    printf("            %-25s | ICNT2 = %-5d | DIM2 = %-5d - %-2s(64)\n", "", ICNT2, DIM2, alignType[dim2Align]);
    printf("            %-25s | ICNT3 = %-5d | DIM3 = %-5d - %-2s(64)\n", "", ICNT3, DIM3, alignType[dim3Align]);
    printf("            %-25s | ICNT4 = %-5d | DIM4 = %-5d - %-2s(64)\n", "", ICNT4, DIM4, alignType[dim4Align]);
    printf("            %-25s | ICNT5 = %-5d | DIM5 = %-5d - %-2s(64)\n", "", ICNT5, DIM5, alignType[dim5Align]);
    printf("-----------------------------------------------------------------------------\n");

    return;
}

void displaySEParam(void *baseAddr, __STRM_TEMPLATE param, int32_t seNum)
{
    uint32_t baseAddrAlign = 1;
    uint32_t dim1Align = 1;
    uint32_t dim2Align = 1;
    uint32_t dim3Align = 1;
    uint32_t dim4Align = 1;
    uint32_t dim5Align = 1;

    __SE_FLAGS seFlags = __get_SE_FLAGS(param);

    uint32_t ICNT0 = __get_ICNT0(param);
    uint32_t ICNT1 = __get_ICNT1(param);
    uint32_t ICNT2 = __get_ICNT2(param);
    uint32_t ICNT3 = __get_ICNT3(param);
    uint32_t ICNT4 = __get_ICNT4(param);
    uint32_t ICNT5 = __get_ICNT5(param);

    int32_t DIM1 = __get_DIM1(param);
    int32_t DIM2 = __get_DIM2(param);
    int32_t DIM3 = __get_DIM3(param);
    int32_t DIM4 = __get_DIM4(param);
    int32_t DIM5 = __get_DIM5(param);

    if(DIM1 & ALIGN_DIMS) { dim1Align = 0; }
    if(DIM2 & ALIGN_DIMS) { dim2Align = 0; }
    if(DIM3 & ALIGN_DIMS) { dim3Align = 0; }
    if(DIM4 & ALIGN_DIMS) { dim4Align = 0; }
    if(DIM5 & ALIGN_DIMS) { dim5Align = 0; }

    if((uint64_t)baseAddr & ALIGN_DIMS) { baseAddrAlign = 0; }

    dim1Align *= baseAddrAlign;
    dim2Align *= baseAddrAlign;
    dim3Align *= baseAddrAlign;
    dim4Align *= baseAddrAlign;
    dim5Align *= baseAddrAlign;

    if((uint64_t)baseAddr & ALIGN_ADDR) { baseAddrAlign = 0; }

    int32_t DECDIM1_WIDTH = __get_DECDIM1_WIDTH(param);
    int32_t DECDIM2_WIDTH = __get_DECDIM2_WIDTH(param);
    int32_t LEZR_CNT = __get_LEZR_CNT(param);

    printf("-----------------------------------------------------------------------------\n");
    printf("SE %d open at 0x%016llX - %s(64), (A - aligned, NA - not aligned)\n", seNum, (uint64_t)baseAddr, alignType[baseAddrAlign]);
    printf("-----------------------------------------------------------------------------\n");
    printf("DECDIM1   = %-25s | DECDIM1_WIDTH = %d \n", decdimType[seFlags.DECDIM1], DECDIM1_WIDTH);
    printf("DECDIM2   = %-25s | DECDIM2_WIDTH = %d \n", decdimType[seFlags.DECDIM2], DECDIM2_WIDTH);
    printf("LEZR      = %-25s | LEZR_CNT = %d \n", lezrType[seFlags.LEZR], LEZR_CNT);
    printf("DIMFMT    = %-25s | \n", dimfmtType[seFlags.DIMFMT]);
    printf("ELETYPE   = %-25s | ICNT0 = %-5d | \n", eleType[seFlags.ELETYPE], ICNT0);
    printf("TRANSPOSE = %-25s | ICNT1 = %-5d | DIM1 = %-5d - %-2s(64)\n", transposeType[seFlags.TRANSPOSE], ICNT1, DIM1, alignType[dim1Align]);
    printf("PROMOTE   = %-25s | ICNT2 = %-5d | DIM2 = %-5d - %-2s(64)\n", promoteType[seFlags.PROMOTE], ICNT2, DIM2, alignType[dim2Align]);
    printf("VECLEN    = %-25s | ICNT3 = %-5d | DIM3 = %-5d - %-2s(64)\n", veclenType[seFlags.VECLEN], ICNT3, DIM3, alignType[dim3Align]);
    printf("ELEDUP    = %-25s | ICNT4 = %-5d | DIM4 = %-5d - %-2s(64)\n", eldupType[seFlags.ELEDUP], ICNT4, DIM4, alignType[dim4Align]);
    printf("GRPDUP    = %-25s | ICNT5 = %-5d | DIM5 = %-5d - %-2s(64)\n", grpdupType[seFlags.GRPDUP], ICNT5, DIM5, alignType[dim5Align]);
    printf("DECIM     = %-25s |               |\n", decimType[seFlags.DECIM]);
    printf("DIR       = %-25s |               |\n", dirType[seFlags.DIR]);
    printf("-----------------------------------------------------------------------------\n");

    return;
}
