/*
* module name       : c7x_common
*
* module descripton : Common utility functions
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#include <stdio.h>

#include "printv.h"

/*----------------------------------------------------------------------------*/
/* Func: PRINTV                                                               */
/*                                                                            */
/* Args: const char *msg                                                      */
/*            - Input message string to be prefixed.                          */
/*       long8 Vec                                                            */
/*            - Input 512 bit data vector to be displayed                     */
/*       uint32_t data_type                                                    */
/*            - Predefined macro values indicating bitdepth and sign.         */
/*       uint32_t HEX                                                         */
/*            - Predefined macro value to indicate hex or decimal display.    */
/* Return: None                                                               */
/*                                                                            */
/* Desc: This function is used to display the contents of a vector            */
/*       horizontally with spacing as indicated by data_type and HEX flags.    */
/*       Ex. Using PRINTV_USIGN_16BIT with PRINTV_HEX_ON will print as,       */
/*                                                                            */
/*       0x0000 0x0001 0x0002 0x0003 0x0004 0x0005 0x0006 0x0007 0x0008 ....  */
/*                                                                            */
/*----------------------------------------------------------------------------*/
void PRINTV(const char *msg, long8 Vec, uint32_t data_type, uint32_t mode)
{

#if(PRINTV_QUIET)
#else
    /*------------------------------------------------------------------------*/
    /* Begin by displaying the input message string.                          */
    /*------------------------------------------------------------------------*/
    printf("%s",msg);

    /*------------------------------------------------------------------------*/
    /* Format the data in 8-bit unsigned representation before displaying.    */
    /*------------------------------------------------------------------------*/
    if(data_type == PRINTV_UNSIGNED_8BIT)
    {
        uint32_t ctr;
        for(ctr = 0; ctr < 64; ctr++)
        {
           uchar64 newVec = __as_uchar64(Vec);
           Vec = __vshr_vkv(Vec, 8);

            if(mode == PRINTV_HEX_OFF)
              printf(" %4d,", newVec.s0);
            else
            printf(" 0x%02x,", newVec.s0);
        }
        printf("\n");
    }

    /*------------------------------------------------------------------------*/
    /* Format the data in 16-bit unsigned representation before displaying.   */
    /*------------------------------------------------------------------------*/
    if(data_type == PRINTV_UNSIGNED_16BIT)
    {
        uint32_t ctr;
        for(ctr = 0; ctr < 32; ctr++)
        {
            ushort32 newVec = __as_ushort32(Vec);
            Vec = __vshr_vkv(Vec, 16);
            if(mode == PRINTV_HEX_OFF)
                printf(" %4d,", newVec.s0);
            else
                printf(" 0x%04x,", newVec.s0);
        }
        printf("\n");
    }

    /*------------------------------------------------------------------------*/
    /* Format the data in 32-bit unsigned representation before displaying.   */
    /*------------------------------------------------------------------------*/
    if(data_type == PRINTV_UNSIGNED_32BIT)
    {
        uint32_t ctr;
        for(ctr = 0; ctr < 16; ctr++)
        {
            uint16 newVec = __as_uint16(Vec);
            Vec = __vshr_vkv(Vec, 16);
            Vec = __vshr_vkv(Vec, 16);
            if(mode == PRINTV_HEX_OFF)
              printf(" %8d,", newVec.s0);
            else
            printf(" 0x%08x,", newVec.s0);

        }
        printf("\n");
    }

    /*------------------------------------------------------------------------*/
    /* Format the data in 64-bit unsigned representation before displaying.   */
    /*------------------------------------------------------------------------*/
    if(data_type == PRINTV_UNSIGNED_64BIT)
    {
        uint32_t ctr;
        for(ctr = 0; ctr < 8; ctr++)
        {
            ulong8 newVec = __as_ulong8(Vec);
            Vec = __vshr_vkv(Vec, 16);
            Vec = __vshr_vkv(Vec, 16);
            Vec = __vshr_vkv(Vec, 16);
            Vec = __vshr_vkv(Vec, 16);
            if(mode == PRINTV_HEX_OFF)
              printf(" %16lld,", newVec.s0);
            else
            printf(" 0x%016llx,", newVec.s0);

        }
        printf("\n");
    }

    /*------------------------------------------------------------------------*/
    /* Format the data in 8-bit signed representation before displaying.      */
    /*------------------------------------------------------------------------*/
    if(data_type == PRINTV_SIGNED_8BIT)
    {
        uint32_t ctr;
        for(ctr = 0; ctr < 64; ctr++)
        {
            char64 newVec = __as_char64(Vec);
            Vec = __vshr_vkv(Vec, 8);
            if(mode == PRINTV_HEX_OFF)
              printf(" %4d,", newVec.s0);
            else
            printf(" 0x%02x,", (newVec.s0 & 0xFF));
        }
        printf("\n");
    }

    /*------------------------------------------------------------------------*/
    /* Format the data in 16-bit signed representation before displaying.     */
    /*------------------------------------------------------------------------*/
    if(data_type == PRINTV_SIGNED_16BIT)
    {
        uint32_t ctr;
        for(ctr = 0; ctr < 32; ctr++)
        {
            short32 newVec = __as_short32(Vec);
            Vec = __vshr_vkv(Vec, 16);

            if(mode == PRINTV_HEX_OFF)
              printf(" %4d,", newVec.s0);
            else
            printf(" 0x%04x,", (newVec.s0 & 0xFFFF));

        }
        printf("\n");
    }

    /*------------------------------------------------------------------------*/
    /* Format the data in 32-bit signed representation before displaying.     */
    /*------------------------------------------------------------------------*/
    if(data_type == PRINTV_SIGNED_32BIT)
    {
        uint32_t ctr;
        for(ctr = 0; ctr < 16; ctr++)
        {
            int16 newVec = __as_int16(Vec);
            Vec = __vshr_vkv(Vec, 16);
            Vec = __vshr_vkv(Vec, 16);
            if(mode == PRINTV_HEX_OFF)
                printf(" %8d,", newVec.s0);
            else
                printf(" 0x%08x,", newVec.s0);
        }
        printf("\n");
    }

    /*------------------------------------------------------------------------*/
    /* Format the data in 64-bit signed representation before displaying.     */
    /*------------------------------------------------------------------------*/
    if(data_type == PRINTV_SIGNED_64BIT)
    {
        uint32_t ctr;
        for(ctr = 0; ctr < 8; ctr++)
        {
            long8 newVec = __as_long8(Vec);
            Vec = __vshr_vkv(Vec, 16);
            Vec = __vshr_vkv(Vec, 16);
            Vec = __vshr_vkv(Vec, 16);
            Vec = __vshr_vkv(Vec, 16);
            if(mode == PRINTV_HEX_OFF)
                printf(" %16lld,", newVec.s0);
            else
                printf(" 0x%016llx,", newVec.s0);

        }
        printf("\n");
    }

    /*------------------------------------------------------------------------*/
    /* Format the data in SP floating point esentation before displaying.     */
    /*------------------------------------------------------------------------*/
    if(data_type == PRINTV_FLOAT)
    {
        uint32_t ctr;
        for(ctr = 0; ctr < 16; ctr++)
        {
            float16 newVec = __as_float16(Vec);
            float value    = newVec.s0;
            Vec = __vshr_vkv(Vec, 16);
            Vec = __vshr_vkv(Vec, 16);
            printf(" %8.6F,", value);
        }
        printf("\n");
    }

#endif //PRINTV_QUIET
  return;
}
