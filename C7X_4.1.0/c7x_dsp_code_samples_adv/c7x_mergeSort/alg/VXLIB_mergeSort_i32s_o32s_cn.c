/*
* module name       : c7x_mergeSort
*
* module descripton : Performs sorting of 512, 32-bit elements
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#include "VXLIB_mergeSort_i32s_o32s_cn.h"
#include <stdio.h>

#define TRACE_ON (0)

VXLIB_STATUS VXLIB_mergeSort_i32s_o32s_cn(int32_t dat[],
                                          int16_t dat_size)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;
    int32_t i, j;
    int32_t temp;

#ifdef VXLIB_CHECK_PARAMS
    status = VXLIB_mergeSort_i32s_o32s_checkParams_cn(dat, dst_size);
    if( status == VXLIB_SUCCESS )
#endif
    {
#if (TRACE_ON)
        printf("Before sort:\n");
        for(i = 0; i < dat_size; i++)
        {
            printf(" %5d, ", dat[i]);
        }
        printf("\n");
#endif
        for(i = 0; i < dat_size; i++)
        {
            for(j = i + 1; j < dat_size; j++)
            {
                if(dat[i] > dat[j])
                {
                    temp = dat[j];
                    dat[j] = dat[i];
                    dat[i] = temp;
                }
            }
        }
#if (TRACE_ON)
        printf("After sort:\n");
        for(i = 0; i < dat_size; i++)
        {
            printf(" %5d, ", dat[i]);
        }
        printf("\n");
#endif
    }
    return (status);
}

VXLIB_STATUS VXLIB_mergeSort_i32s_o32s_checkParams_cn(int32_t dat[],
                                                      int16_t dat_size)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

    return (status);
}
