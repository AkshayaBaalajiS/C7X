/*
* module name       : c7x_common
*
* module descripton : Common utility functions
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/
#include "memory.h"

#define A (0x41C64E6D)  //1103515245
#define C (0x00003039)  //12345
#define M (0x7FFFFFFF)  //2^31 - 1

#ifdef __cplusplus
#pragma DATA_SECTION(".randState");
#else
#pragma DATA_SECTION(randState, ".randState");
#endif
uint32_t randState [16] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53};

void fillRandFast(void *array, int32_t size, uint8_t elementSize, uint32_t wrapVal)
{
   __STRM_TEMPLATE saTemplate;
   __SA_FLAGS saFlags;

    uint16 vA = (uint16)(A);
    uint16 vC = (uint16)(C);
    uint16 vM = (uint16)(M);
    uint16 vState;

    uint32_t ctr;

   //Initialize SA flags to default
   saFlags = __SA_FLAGS_default();

   //Update necessary flags
   saFlags.DIMFMT  = __SA_DIMFMT_3D;
   saFlags.VECLEN  = __SA_VECLEN_16ELEMS;

   //Initialize template
   saTemplate = (uint16) (0);

   //Set SE_PARAMS
   saTemplate = __set_ICNT0(saTemplate, size);
   saTemplate = __set_ICNT1_DIM1(saTemplate, 1, 0);
   saTemplate = __set_ICNT2_DIM2(saTemplate, 1, 0);

   //Encode SE_FLAGS in the template
   saTemplate = __set_SA_FLAGS(saTemplate, &saFlags);

   //Init state
   uint16_ptr pState = stov_ptr(uint16, (uint32_t *)&randState[0]);

   vState = *pState;

    if( elementSize == MEMORY_ELEM_8BIT )
    {
        uint8_t *restrict pData = (uint8_t *)array;

        __SA0_OPEN(saTemplate);

        for( ctr = 0; ctr < size; ctr+=16 )
        {
            vState = ((vA * vState) + vC) & vM;

            uint16 vRes = __shift_right(vState, (uint16)(16)) & (uint16)(256 - 1);

            vRes  = vRes & (uint16)(wrapVal - 1);

            __vpred vpStore = __SA0_VPRED(uint16);
            __vstore_pred_pack_byte(vpStore, __SA0ADV(uchar16, pData), vRes);
        }

        __SA0_CLOSE();

    }
    else if( elementSize == MEMORY_ELEM_16BIT )
    {
        uint16_t *restrict pData = (uint16_t *)array;

        __SA0_OPEN(saTemplate);

        for( ctr = 0; ctr < size; ctr+=16 )
        {
            vState = ((vA * vState) + vC) & vM;
            uint16 vRes = __shift_right(vState, (uint16)(16)) & (uint16)(0XFFFF);

            vRes  = vRes & (uint16)(wrapVal - 1);

            __vpred vpStore = __SA0_VPRED(uint16);
            __vstore_pred_packl(vpStore, __SA0ADV(ushort16, pData), vRes);
        }

        __SA0_CLOSE();
    }
    else if( elementSize == MEMORY_ELEM_32BIT )
    {
        uint32_t *restrict pData = (uint32_t *)array;

        __SA0_OPEN(saTemplate);

        for( ctr = 0; ctr < size; ctr+=16 )
        {
            vState = ((vA * vState) + vC) & vM;
            uint16 vRes = __shift_right(vState, (uint16)(16)) & (uint16)(0xFFFFFFFF);

            vRes  = vRes & (uint16)(wrapVal - 1);

            __vpred vpStore = __SA0_VPRED(uint16);
            __vstore_pred(vpStore, __SA0ADV(uint16, pData), vRes);
        }

        __SA0_CLOSE();
    }

   //Save state
   *pState = vState;
}

void qc512(uint8_t* pOut, const uint8_t* pIn, size_t inlen)
{
  __STRM_TEMPLATE seTemplate;
  __SE_FLAGS seFlags;

  int32_t id;

  //Initialize SE flags to default
  seFlags = __SE_FLAGS_default();

  //Update necessary flags
  seFlags.DIMFMT  = __SE_DIMFMT_3D;
  seFlags.ELETYPE = __SE_ELETYPE_8BIT;
  seFlags.VECLEN  = __SE_VECLEN_64ELEMS;

  //Initialize template
  seTemplate = (uint16) (0);

  //Set SE_PARAMS
  seTemplate = __set_ICNT0(seTemplate, inlen);
  seTemplate = __set_ICNT1_DIM1(seTemplate, 1, 0);
  seTemplate = __set_ICNT2_DIM2(seTemplate, 1, 0);

  //Encode SE_FLAGS in the template
  seTemplate = __set_SE_FLAGS(seTemplate, &seFlags, NULL);

  //Open the stream
  __SE0_OPEN((void *)pIn, seTemplate);

  uchar64 vOut = (uchar64)(0);

  for(id = 0; id < inlen; id+=64) {
    vOut = vOut ^ __SE0ADV(uchar64);
  }

  __SE0_CLOSE();

  *stov_ptr(uchar64, (uint8_t *)pOut) = vOut;
}

void memsetFast(void *array, uint32_t value, int32_t size, uint8_t elementSize)
{
   __STRM_TEMPLATE saTemplate;
   __SA_FLAGS saFlags;

    uint32_t ctr;

   //Initialize SA flags to default
   saFlags = __SA_FLAGS_default();

   //Update necessary flags
   saFlags.DIMFMT  = __SA_DIMFMT_3D;

   //Initialize template
   saTemplate = (uint16) (0);

   //Set SE_PARAMS
   saTemplate = __set_ICNT0(saTemplate, size);
   saTemplate = __set_ICNT1_DIM1(saTemplate, 1, 0);
   saTemplate = __set_ICNT2_DIM2(saTemplate, 1, 0);

    if( elementSize == MEMORY_ELEM_8BIT )
    {
        uint8_t *restrict pData = (uint8_t *)array;
        uchar64 vVal = (uchar64)(value);

        saFlags.VECLEN  = __SA_VECLEN_64ELEMS;
        saTemplate = __set_SA_FLAGS(saTemplate, &saFlags);

        __SA0_OPEN(saTemplate);
        for( ctr = 0; ctr < size; ctr+=64 )
        {
            __vpred vpStore = __SA0_VPRED(uchar64);
            __vstore_pred(vpStore, __SA0ADV(uchar64, pData), vVal);
        }
        __SA0_CLOSE();

    }
    else if( elementSize == MEMORY_ELEM_16BIT )
    {
        uint16_t *restrict pData = (uint16_t *)array;
        ushort32 vVal = (ushort32)(value);

        saFlags.VECLEN  = __SA_VECLEN_32ELEMS;
        saTemplate = __set_SA_FLAGS(saTemplate, &saFlags);

        __SA0_OPEN(saTemplate);
        for( ctr = 0; ctr < size; ctr+=32 )
        {
            __vpred vpStore = __SA0_VPRED(ushort32);
            __vstore_pred(vpStore, __SA0ADV(ushort32, pData), vVal);
        }
        __SA0_CLOSE();

    }
    else if( elementSize == MEMORY_ELEM_32BIT )
    {
        uint32_t *restrict pData = (uint32_t *)array;
        uint16 vVal = (uint16)(value);

        saFlags.VECLEN  = __SA_VECLEN_16ELEMS;
        saTemplate = __set_SA_FLAGS(saTemplate, &saFlags);

        __SA0_OPEN(saTemplate);
        for( ctr = 0; ctr < size; ctr+=16 )
        {
            __vpred vpStore = __SA0_VPRED(uint16);
            __vstore_pred(vpStore, __SA0ADV(uint16, pData), vVal);
        }
        __SA0_CLOSE();
    }
}

void * alignAddress(void *pBase, int32_t bank_opt)
{
    uint64_t baseAddr = (uint64_t)pBase;

    uint8_t *pBank0;
    uint8_t *pBank1;
    uint8_t *pBank2;
    uint8_t *pBank3;

    void *pOut;

    pOut = pBase;

    if(((baseAddr >> 7) & 0x3) == MEMORY_BANK0)
    {
        pBank0 = (uint8_t *)pBase;
        pBank1 = (uint8_t *)pBase + 128;
        pBank2 = (uint8_t *)pBase + 256;
        pBank3 = (uint8_t *)pBase + 384;
    }
    else if(((baseAddr >> 7) & 0x3) == MEMORY_BANK1)
    {
        pBank1 = (uint8_t *)pBase;
        pBank2 = (uint8_t *)pBase + 128;
        pBank3 = (uint8_t *)pBase + 256;
        pBank0 = (uint8_t *)pBase + 384;
    }
    else if(((baseAddr >> 7) & 0x3) == MEMORY_BANK2)
    {
        pBank2 = (uint8_t *)pBase;
        pBank3 = (uint8_t *)pBase + 128;
        pBank1 = (uint8_t *)pBase + 256;
        pBank0 = (uint8_t *)pBase + 384;
    }
    else if(((baseAddr >> 7) & 0x3) == MEMORY_BANK3)
    {
        pBank3 = (uint8_t *)pBase;
        pBank0 = (uint8_t *)pBase + 128;
        pBank1 = (uint8_t *)pBase + 256;
        pBank2 = (uint8_t *)pBase + 384;
    }

    if (bank_opt == 0)
    {
      pOut = (void *)pBank0;
    }
    else if (bank_opt == 1)
    {
      pOut = (void *)pBank1;
    }
    else if (bank_opt == 2)
    {
      pOut = (void *)pBank2;
    }
    else if (bank_opt == 3)
    {
      pOut = (void *)pBank3;
    }

    return pOut;
}
