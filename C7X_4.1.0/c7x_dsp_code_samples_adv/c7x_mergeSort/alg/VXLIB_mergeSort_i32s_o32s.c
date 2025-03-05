/*
* module name       : c7x_mergeSort
*
* module descripton : Performs sorting of 512, 32-bit elements
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#include "VXLIB_mergeSort_i32s_o32s.h"

#ifdef _DISPLAY_PARAMS
#include "paramv.h"
#endif

#define MAX_STAGES       (10)
#define SA_PARAM_BASE    (0x0000)

#define TRACE_SA_PARAM_OFFSET   (SA_PARAM_BASE)
#define STAGE1_SA_PARAM_OFFSET  (TRACE_SA_PARAM_OFFSET   + SA_PARAM_SIZE)
#define STAGE1_SA0_PARAM_OFFSET (STAGE1_SA_PARAM_OFFSET  + (MAX_STAGES * SA_PARAM_SIZE))
#define STAGE1_SA1_PARAM_OFFSET (STAGE1_SA0_PARAM_OFFSET + (MAX_STAGES * SA_PARAM_SIZE))

#define SIMD_WIDTH_SHIFT       (4) /* 2^4 = 16 32b elements in a 512b vector */
#define SIMD_WIDTH             (1 << SIMD_WIDTH_SHIFT)
#define SIMD_WIDTH_RND         (SIMD_WIDTH >> 1)
#define NUM_SIMD_BLOCKS(width) (((width) >> SIMD_WIDTH_SHIFT) + (((width) - (((width) >> SIMD_WIDTH_SHIFT) << SIMD_WIDTH_SHIFT)) > 0 ? 1 : 0))

VXLIB_STATUS VXLIB_mergeSort_i32s_o32s_init(int32_t dat[restrict],
                                            int32_t out[restrict],
                                            int16_t dat_size,
                                            void *pBlock)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#if defined(VXLIB_CHECK_PARAMS) || defined(VXLIB_MERGE_SORT_I32S_O32S_CHECK_PARAMS)
    status = VXLIB_mergeSort_i32s_o32s_checkParams(src, out, dat_size, pBlock);
    if( status == VXLIB_SUCCESS )
#endif
    {

        __STRM_TEMPLATE saTemplate;
        __SA_FLAGS saFlags;

        __STRM_PARAM_3D sa3DParam;
        __STRM_PARAM_4D sa4DParam;

        int32_t numCols, numRows, pitch;
        int32_t numStages, stage;

        numCols   = SIMD_WIDTH;
        numRows   = NUM_SIMD_BLOCKS(dat_size);
        pitch     = numCols;

        /*---------------------------------------------------------*/
        /* Trace                                                   */
        /*---------------------------------------------------------*/
        saFlags = __SA_FLAGS_default();
        saFlags.VECLEN  = __SA_VECLEN_16ELEMS;

        sa3DParam.ICNT0 = SIMD_WIDTH;
        sa3DParam.ICNT1 = numRows;
        sa3DParam.ICNT2 = 1;

        sa3DParam.DIM1  = pitch;
        sa3DParam.DIM2  = 0;

        saTemplate = __SA_SET_PARAM_3D(&sa3DParam, &saFlags);
        *stov_ptr(__STRM_TEMPLATE, (uint32_t*)((uint8_t *)pBlock + TRACE_SA_PARAM_OFFSET)) = saTemplate;

        saFlags = __SA_FLAGS_default();
        saFlags.VECLEN  = __SA_VECLEN_16ELEMS;

        sa3DParam.ICNT0 = SIMD_WIDTH;
        sa3DParam.ICNT1 = numRows >> 1;
        sa3DParam.ICNT2 = 1;

        sa3DParam.DIM1  = pitch << 1;
        sa3DParam.DIM2  = 0;

        saTemplate = __SA_SET_PARAM_3D(&sa3DParam, &saFlags);
        *stov_ptr(__STRM_TEMPLATE, (uint32_t*)((uint8_t *)pBlock + STAGE1_SA_PARAM_OFFSET)) = saTemplate;

        /* Prepare SA 0 tempate to store output */
        saFlags = __SA_FLAGS_default();
        saFlags.VECLEN   = __SA_VECLEN_16ELEMS;

        /* ITERATION COUNTERS */
        sa3DParam.ICNT0 = SIMD_WIDTH;
        sa3DParam.ICNT1 = numRows;
        sa3DParam.ICNT2 = 1;

        /* DIMENSIONS */
        sa3DParam.DIM1  = SIMD_WIDTH;
        sa3DParam.DIM2  = 0;

        saTemplate = __SA_SET_PARAM_3D(&sa3DParam, &saFlags);
        *stov_ptr(__STRM_TEMPLATE, (uint32_t*)((uint8_t *)pBlock + STAGE1_SA0_PARAM_OFFSET)) = saTemplate;

        numStages = 5;
        for(stage = 1; stage < numStages; stage++)
        {
            saFlags = __SA_FLAGS_default();
            saFlags.VECLEN = __SA_VECLEN_16ELEMS;

            sa4DParam.ICNT0 = SIMD_WIDTH;
            sa4DParam.ICNT1 = 1 << (stage - 1);
            sa4DParam.ICNT2 = numRows >> (stage + 1);
            sa4DParam.ICNT3 = 1;

            sa4DParam.DIM1  = pitch;
            sa4DParam.DIM2  = pitch << (stage + 1);
            sa4DParam.DIM3  = 0;

            saTemplate = __SA_SET_PARAM_4D(&sa4DParam, &saFlags);
            *stov_ptr(__STRM_TEMPLATE, (uint32_t*)((uint8_t *)pBlock + STAGE1_SA_PARAM_OFFSET + (stage * SA_PARAM_SIZE))) = saTemplate;

            /* Prepare SA 0 tempate to store output */
            saFlags = __SA_FLAGS_default();
            saFlags.VECLEN   = __SA_VECLEN_16ELEMS;

            sa3DParam.ICNT0 = SIMD_WIDTH;
            sa3DParam.ICNT1 = 1 << stage;
            sa3DParam.ICNT2 = numRows >> stage;

            sa3DParam.DIM1  = SIMD_WIDTH;
            sa3DParam.DIM2  = (SIMD_WIDTH) << (stage + 1);

            saTemplate = __SA_SET_PARAM_3D(&sa3DParam, &saFlags);
            *stov_ptr(__STRM_TEMPLATE, (uint32_t*)((uint8_t *)pBlock + STAGE1_SA0_PARAM_OFFSET + (stage * SA_PARAM_SIZE))) = saTemplate;

            /* Prepare SA 1 tempate to store output */
            saFlags = __SA_FLAGS_default();
            saFlags.VECLEN   = __SA_VECLEN_16ELEMS;

            sa3DParam.ICNT0 = SIMD_WIDTH;
            sa3DParam.ICNT1 = 1 << stage;
            sa3DParam.ICNT2 = numRows >> stage;

            sa3DParam.DIM1  = -(SIMD_WIDTH);
            sa3DParam.DIM2  =  (SIMD_WIDTH) << (stage + 1);

            saTemplate = __SA_SET_PARAM_3D(&sa3DParam, &saFlags);
            *stov_ptr(__STRM_TEMPLATE, (uint32_t*)((uint8_t *)pBlock + STAGE1_SA1_PARAM_OFFSET + (stage * SA_PARAM_SIZE))) = saTemplate;

        }

            stage = 5;

            saFlags = __SA_FLAGS_default();
            saFlags.VECLEN  = __SA_VECLEN_16ELEMS;

            sa4DParam.ICNT0 = SIMD_WIDTH;
            sa4DParam.ICNT1 = 1 << (stage - 1);
            sa4DParam.ICNT2 = 1;
            sa4DParam.ICNT3 = 1;

            sa4DParam.DIM1  = pitch;
            sa4DParam.DIM2  = 0;
            sa4DParam.DIM3  = 0;

            saTemplate = __SA_SET_PARAM_4D(&sa4DParam, &saFlags);
            *stov_ptr(__STRM_TEMPLATE, (uint32_t*)((uint8_t *)pBlock + STAGE1_SA_PARAM_OFFSET + (stage * SA_PARAM_SIZE))) = saTemplate;

            /* Prepare SA 0 tempate to store output */
            saFlags = __SA_FLAGS_default();
            saFlags.VECLEN    = __SA_VECLEN_16ELEMS;

            sa3DParam.ICNT0 = SIMD_WIDTH;
            sa3DParam.ICNT1 = 1 << stage;
            sa3DParam.ICNT2 = numRows >> stage;

            sa3DParam.DIM1  = SIMD_WIDTH;
            sa3DParam.DIM2  = (SIMD_WIDTH) << (stage + 1);

            saTemplate = __SA_SET_PARAM_3D(&sa3DParam, &saFlags);
            *stov_ptr(__STRM_TEMPLATE, (uint32_t*)((uint8_t *)pBlock + STAGE1_SA0_PARAM_OFFSET + (stage * SA_PARAM_SIZE))) = saTemplate;

            /* Prepare SA 1 tempate to store output */
            saFlags = __SA_FLAGS_default();
            saFlags.VECLEN    = __SA_VECLEN_16ELEMS;

            sa3DParam.ICNT0 = SIMD_WIDTH;
            sa3DParam.ICNT1 = 1 << stage;
            sa3DParam.ICNT2 = numRows >> stage;

            sa3DParam.DIM1  = -(SIMD_WIDTH);
            sa3DParam.DIM2  =  (SIMD_WIDTH) << (stage + 1);

            saTemplate = __SA_SET_PARAM_3D(&sa3DParam, &saFlags);
            *stov_ptr(__STRM_TEMPLATE, (uint32_t*)((uint8_t *)pBlock + STAGE1_SA1_PARAM_OFFSET + (stage * SA_PARAM_SIZE))) = saTemplate;
    }
    return (status);
}

VXLIB_STATUS VXLIB_mergeSort_i32s_o32s_kernel(int32_t dat[restrict],
                                              int32_t out[restrict],
                                              int16_t dat_size,
                                              void *pBlock)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#if defined(VXLIB_CHECK_PARAMS) || defined(VXLIB_MERGE_SORT_I32S_O32S_CHECK_PARAMS)
    status = VXLIB_mergeSort_i32s_o32s_checkParams(src, out, dat_size, pBlock);
    if( status == VXLIB_SUCCESS )
#endif
    {
        __STRM_TEMPLATE saTemplate;

        int32_t *buf[2];

        int32_t blkY;
        int32_t numRows;
        int32_t numSets;
        int32_t stage;
        uint8_t ping_nPong;

        int32_t *restrict pIn1;
	int32_t *restrict pIn2;
	int32_t *restrict pOut;

        numRows = NUM_SIMD_BLOCKS(dat_size);

#if(TRACE_ON)
        int32_t numCols = SIMD_WIDTH;
        printf("Input : ");
        printf("numCols = %d, numRows = %d\n", numCols, numRows);

        saTemplate =   *stov_ptr(__STRM_TEMPLATE, (uint32_t*)((uint8_t *)pBlock + TRACE_SA_PARAM_OFFSET));
        __SA0_OPEN(saTemplate);

        for(blkY = 0; blkY < numRows; blkY++)
        {
            int16 vIn  = *__SA0ADV(int16, (int32_t *)dat);
            PRINTV("vIn =", __as_long8(vIn), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
        }

        __SA0_CLOSE();
#endif

        ping_nPong = 0;
        buf[0] = dat;
        buf[1] = out;

        saTemplate = *stov_ptr(__STRM_TEMPLATE, (uint32_t*)((uint8_t *)pBlock + STAGE1_SA_PARAM_OFFSET));
        __SA2_OPEN(saTemplate);
        __SA3_OPEN(saTemplate);

        saTemplate = *stov_ptr(__STRM_TEMPLATE, (uint32_t*)((uint8_t *)pBlock + STAGE1_SA0_PARAM_OFFSET));
        __SA0_OPEN(saTemplate);

        pIn1 = (int32_t *)buf[ping_nPong];
        pIn2 = (int32_t *)buf[ping_nPong] + SIMD_WIDTH;

        ping_nPong = !ping_nPong;

        pOut = (int32_t *)buf[ping_nPong];

#pragma MUST_ITERATE(1,,)
        for(blkY = 0; blkY < numRows; blkY+=2)
        {
            int16 vIn0 = *__SA2ADV(int16, pIn1);
            int16 vIn1 = *__SA3ADV(int16, pIn2);

            vIn0 = __sort_asc(vIn0);
            vIn1 = __sort_desc(vIn1);

            *__SA0ADV(int16, pOut) = vIn0;
            *__SA0ADV(int16, pOut) = vIn1;
        }

        __SA2_CLOSE();
        __SA3_CLOSE();
        __SA0_CLOSE();

#if(TRACE_ON)
            printf("Stage %d : ", 0);
            printf("numCols = %d, numRows = %d, bufID = %d\n", numCols, numRows, ping_nPong);

            saTemplate =   *stov_ptr(__STRM_TEMPLATE, (uint32_t*)((uint8_t *)pBlock + TRACE_SA_PARAM_OFFSET));
            __SA0_OPEN(saTemplate);

            for(blkY = 0; blkY < numRows; blkY++)
            {
                int16 vIn  = *__SA0ADV(int16, (int32_t *)buf[ping_nPong]);
                PRINTV("vOut =", __as_long8(vIn), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
            }

            __SA0_CLOSE();
#endif

        {
            stage   = 1;
            numSets = 1;

            saTemplate =   *stov_ptr(__STRM_TEMPLATE, (uint32_t*)((uint8_t *)pBlock + STAGE1_SA_PARAM_OFFSET + (stage * SA_PARAM_SIZE)));
            __SA2_OPEN(saTemplate);
            __SA3_OPEN(saTemplate);

            saTemplate =   *stov_ptr(__STRM_TEMPLATE, (uint32_t*)((uint8_t *)pBlock + STAGE1_SA0_PARAM_OFFSET + (stage * SA_PARAM_SIZE)));
            __SA0_OPEN(saTemplate);

            pIn1 = (int32_t *)buf[ping_nPong];
            pIn2 = (int32_t *)buf[ping_nPong] + (SIMD_WIDTH * numSets);

            ping_nPong = !ping_nPong;

            pOut = (int32_t *)buf[ping_nPong];
#pragma MUST_ITERATE(1,,)
            for(blkY = 0; blkY < numRows; blkY+=(1 << (stage + 1)))
            {
                    int16 vIn0 = *__SA2ADV(int16, pIn1);
                    int16 vIn1 = *__SA3ADV(int16, pIn2);

#if(TRACE_ON)
                    printf("blkY: %d\n", blkY);
                    PRINTV("vIn0 =", __as_long8(vIn0), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn1 =", __as_long8(vIn1), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
#endif

                    int16 voutIn0 = __min(vIn0, vIn1);
                    int16 voutIn1 = __max(vIn0, vIn1);

                    vIn0 = __sort_asc(voutIn0);
                    vIn1 = __sort_asc(voutIn1);

#if(TRACE_ON)
                    PRINTV("vIn0 =", __as_long8(vIn0), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn1 =", __as_long8(vIn1), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
#endif

                    *__SA0ADV(int16, pOut) = vIn0;
                    *__SA0ADV(int16, pOut) = vIn1;
            }

            __SA2_CLOSE();
            __SA3_CLOSE();
            __SA0_CLOSE();

////////
            ping_nPong = !ping_nPong;

            saTemplate =   *stov_ptr(__STRM_TEMPLATE, (uint32_t*)((uint8_t *)pBlock + STAGE1_SA_PARAM_OFFSET + (stage * SA_PARAM_SIZE)));
            __SA2_OPEN(saTemplate);
            __SA3_OPEN(saTemplate);

            saTemplate =   *stov_ptr(__STRM_TEMPLATE, (uint32_t*)((uint8_t *)pBlock + STAGE1_SA1_PARAM_OFFSET + (stage * SA_PARAM_SIZE)));
            __SA1_OPEN(saTemplate);

            pIn1 = (int32_t *)buf[ping_nPong] + (SIMD_WIDTH * (1 << stage));
            pIn2 = (int32_t *)buf[ping_nPong] + (SIMD_WIDTH * numSets) + (SIMD_WIDTH * (1 << stage));

            ping_nPong = !ping_nPong;

            pOut = (int32_t *)buf[ping_nPong] + (SIMD_WIDTH * ((1 << (stage + 1)) - 1));
#pragma MUST_ITERATE(1,,)
            for(blkY = 0; blkY < numRows; blkY+=(1 << (stage + 1)))
            {
                int16 vIn0 = *__SA2ADV(int16, pIn1);
                int16 vIn1 = *__SA3ADV(int16, pIn2);

#if(TRACE_ON)
                printf("blkY: %d\n", blkY);
                PRINTV("vIn0 =", __as_long8(vIn0), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                PRINTV("vIn1 =", __as_long8(vIn1), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
#endif
                int16 voutIn0 = __min(vIn0, vIn1);
                int16 voutIn1 = __max(vIn0, vIn1);

                vIn0 = __sort_desc(voutIn0);
                vIn1 = __sort_desc(voutIn1);

#if(TRACE_ON)
                PRINTV("vIn0 =", __as_long8(vIn0), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                PRINTV("vIn1 =", __as_long8(vIn1), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
#endif

                *__SA1ADV(int16, pOut) = vIn0;
                *__SA1ADV(int16, pOut) = vIn1;
            }

            __SA2_CLOSE();
            __SA3_CLOSE();
            __SA1_CLOSE();

#if(TRACE_ON)
            printf("Stage %d : ", stage);
            printf("numCols = %d, numRows = %d, bufID = %d\n", numCols, numRows, ping_nPong);

            saTemplate =   *stov_ptr(__STRM_TEMPLATE, (uint32_t*)((uint8_t *)pBlock + TRACE_SA_PARAM_OFFSET));
            __SA0_OPEN(saTemplate);

#pragma MUST_ITERATE(1,,)
            for(blkY = 0; blkY < numRows; blkY++)
            {
                int16 vIn  = *__SA0ADV(int16, (int32_t *)buf[ping_nPong]);
                PRINTV("vOut =", __as_long8(vIn), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
            }

            __SA0_CLOSE();
#endif
        }

        {
            stage = 2;
            numSets = 2;

            saTemplate =   *stov_ptr(__STRM_TEMPLATE, (uint32_t*)((uint8_t *)pBlock + STAGE1_SA_PARAM_OFFSET + (stage * SA_PARAM_SIZE)));
            __SA2_OPEN(saTemplate);
            __SA3_OPEN(saTemplate);

            saTemplate =   *stov_ptr(__STRM_TEMPLATE, (uint32_t*)((uint8_t *)pBlock + STAGE1_SA0_PARAM_OFFSET + (stage * SA_PARAM_SIZE)));
            __SA0_OPEN(saTemplate);

            pIn1 = (int32_t *)buf[ping_nPong];
            pIn2 = (int32_t *)buf[ping_nPong] + (SIMD_WIDTH * numSets);

            ping_nPong = !ping_nPong;

            pOut = (int32_t *)buf[ping_nPong];
#pragma MUST_ITERATE(1,,)
            for(blkY = 0; blkY < numRows; blkY+=(1 << (stage + 1)))
            {
                    int16 vIn0 = *__SA2ADV(int16, pIn1);
                    int16 vIn1 = *__SA2ADV(int16, pIn1);
                    int16 vIn2 = *__SA3ADV(int16, pIn2);
                    int16 vIn3 = *__SA3ADV(int16, pIn2);

#if(TRACE_ON)
                    PRINTV("vIn0 =", __as_long8(vIn0), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn1 =", __as_long8(vIn1), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn2 =", __as_long8(vIn2), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn3 =", __as_long8(vIn3), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
#endif

                    int16 vTmpIn0 = __min(vIn0, vIn2);
                    int16 vTmpIn1 = __max(vIn0, vIn2);
                    int16 vTmpIn2 = __min(vIn1, vIn3);
                    int16 vTmpIn3 = __max(vIn1, vIn3);

                    int16 vOutIn0 = __min(vTmpIn0, vTmpIn2);
                    int16 vOutIn1 = __max(vTmpIn0, vTmpIn2);
                    int16 vOutIn2 = __min(vTmpIn1, vTmpIn3);
                    int16 vOutIn3 = __max(vTmpIn1, vTmpIn3);

                    vIn0 = __sort_asc(vOutIn0);
                    vIn1 = __sort_asc(vOutIn1);
                    vIn2 = __sort_asc(vOutIn2);
                    vIn3 = __sort_asc(vOutIn3);

#if(TRACE_ON)
                    PRINTV("vIn0s =", __as_long8(vIn0), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn1s =", __as_long8(vIn1), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn2s =", __as_long8(vIn2), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn3s =", __as_long8(vIn3), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
#endif

                    *__SA0ADV(int16, pOut) = vIn0;
                    *__SA0ADV(int16, pOut) = vIn1;
                    *__SA0ADV(int16, pOut) = vIn2;
                    *__SA0ADV(int16, pOut) = vIn3;
            }

            __SA2_CLOSE();
            __SA3_CLOSE();
            __SA0_CLOSE();

//////

            ping_nPong = !ping_nPong;

            saTemplate =   *stov_ptr(__STRM_TEMPLATE, (uint32_t*)((uint8_t *)pBlock + STAGE1_SA_PARAM_OFFSET + (stage * SA_PARAM_SIZE)));
            __SA2_OPEN(saTemplate);
            __SA3_OPEN(saTemplate);

            saTemplate =   *stov_ptr(__STRM_TEMPLATE, (uint32_t*)((uint8_t *)pBlock + STAGE1_SA1_PARAM_OFFSET + (stage * SA_PARAM_SIZE)));
            __SA1_OPEN(saTemplate);

            pIn1 = (int32_t *)buf[ping_nPong] + (SIMD_WIDTH * (1 << stage));
            pIn2 = (int32_t *)buf[ping_nPong] + (SIMD_WIDTH * numSets) + (SIMD_WIDTH * (1 << stage));

            ping_nPong = !ping_nPong;

            pOut = (int32_t *)buf[ping_nPong] + (SIMD_WIDTH * ((1 << (stage + 1)) - 1));

#pragma MUST_ITERATE(1,,)
            for(blkY = 0; blkY < numRows; blkY+=(1 << (stage + 1)))
            {
                int16 vIn0 = *__SA2ADV(int16, pIn1);
                int16 vIn1 = *__SA2ADV(int16, pIn1);
                int16 vIn2 = *__SA3ADV(int16, pIn2);
                int16 vIn3 = *__SA3ADV(int16, pIn2);

#if(TRACE_ON)
                PRINTV("vIn0 =", __as_long8(vIn0), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                PRINTV("vIn1 =", __as_long8(vIn1), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                PRINTV("vIn2 =", __as_long8(vIn2), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                PRINTV("vIn3 =", __as_long8(vIn3), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
#endif
                int16 vTmpIn0 = __min(vIn0, vIn2);
                int16 vTmpIn1 = __max(vIn0, vIn2);
                int16 vTmpIn2 = __min(vIn1, vIn3);
                int16 vTmpIn3 = __max(vIn1, vIn3);

                int16 vOutIn0 = __min(vTmpIn0, vTmpIn2);
                int16 vOutIn1 = __max(vTmpIn0, vTmpIn2);
                int16 vOutIn2 = __min(vTmpIn1, vTmpIn3);
                int16 vOutIn3 = __max(vTmpIn1, vTmpIn3);

                vIn0 = __sort_desc(vOutIn0);
                vIn1 = __sort_desc(vOutIn1);
                vIn2 = __sort_desc(vOutIn2);
                vIn3 = __sort_desc(vOutIn3);

#if(TRACE_ON)
                PRINTV("vIn0s =", __as_long8(vIn0), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                PRINTV("vIn1s =", __as_long8(vIn1), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                PRINTV("vIn2s =", __as_long8(vIn2), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                PRINTV("vIn3s =", __as_long8(vIn3), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
#endif

                *__SA1ADV(int16, pOut) = vIn0;
                *__SA1ADV(int16, pOut) = vIn1;
                *__SA1ADV(int16, pOut) = vIn2;
                *__SA1ADV(int16, pOut) = vIn3;

            }

            __SA2_CLOSE();
            __SA3_CLOSE();
            __SA1_CLOSE();

#if(TRACE_ON)
            printf("Stage %d : ", stage);
            printf("numCols = %d, numRows = %d, bufID = %d\n", numCols, numRows, ping_nPong);

            saTemplate =   *stov_ptr(__STRM_TEMPLATE, (uint32_t*)((uint8_t *)pBlock + TRACE_SA_PARAM_OFFSET));
            __SA0_OPEN(saTemplate);

#pragma MUST_ITERATE(1,,)
            for(blkY = 0; blkY < numRows; blkY++)
            {
                int16 vIn  = *__SA0ADV(int16, (int32_t *)buf[ping_nPong]);
                PRINTV("vOut =", __as_long8(vIn), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
            }

            __SA0_CLOSE();
#endif
        }

        {
            stage = 3;
            numSets = 4;

            saTemplate =   *stov_ptr(__STRM_TEMPLATE, (uint32_t*)((uint8_t *)pBlock + STAGE1_SA_PARAM_OFFSET + (stage * SA_PARAM_SIZE)));
            __SA2_OPEN(saTemplate);
            __SA3_OPEN(saTemplate);

            saTemplate =   *stov_ptr(__STRM_TEMPLATE, (uint32_t*)((uint8_t *)pBlock + STAGE1_SA0_PARAM_OFFSET + (stage * SA_PARAM_SIZE)));
            __SA0_OPEN(saTemplate);

            pIn1 = (int32_t *)buf[ping_nPong];
            pIn2 = (int32_t *)buf[ping_nPong] + (SIMD_WIDTH * numSets);

            ping_nPong = !ping_nPong;

            pOut = (int32_t *)buf[ping_nPong];

#pragma MUST_ITERATE(1,,)
            for(blkY = 0; blkY < numRows; blkY+=(1 << (stage + 1)))
            {
                int16 vIn0 = *__SA2ADV(int16, pIn1);
                int16 vIn1 = *__SA2ADV(int16, pIn1);
                int16 vIn2 = *__SA2ADV(int16, pIn1);
                int16 vIn3 = *__SA2ADV(int16, pIn1);

                int16 vIn4 = *__SA3ADV(int16, pIn2);
                int16 vIn5 = *__SA3ADV(int16, pIn2);
                int16 vIn6 = *__SA3ADV(int16, pIn2);
                int16 vIn7 = *__SA3ADV(int16, pIn2);

#if(TRACE_ON)
                PRINTV("vIn0 =", __as_long8(vIn0), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                PRINTV("vIn1 =", __as_long8(vIn1), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                PRINTV("vIn2 =", __as_long8(vIn2), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                PRINTV("vIn3 =", __as_long8(vIn3), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);

                PRINTV("vIn4 =", __as_long8(vIn4), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                PRINTV("vIn5 =", __as_long8(vIn5), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                PRINTV("vIn6 =", __as_long8(vIn6), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                PRINTV("vIn7 =", __as_long8(vIn7), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);

#endif
                int16 vTmpIn0 = __min(vIn0, vIn4);
                int16 vTmpIn1 = __max(vIn0, vIn4);
                int16 vTmpIn2 = __min(vIn1, vIn5);
                int16 vTmpIn3 = __max(vIn1, vIn5);
                int16 vTmpIn4 = __min(vIn2, vIn6);
                int16 vTmpIn5 = __max(vIn2, vIn6);
                int16 vTmpIn6 = __min(vIn3, vIn7);
                int16 vTmpIn7 = __max(vIn3, vIn7);

                int16 vTmp1In0 = __min(vTmpIn0, vTmpIn4);
                int16 vTmp1In1 = __max(vTmpIn0, vTmpIn4);
                int16 vTmp1In2 = __min(vTmpIn1, vTmpIn5);
                int16 vTmp1In3 = __max(vTmpIn1, vTmpIn5);
                int16 vTmp1In4 = __min(vTmpIn2, vTmpIn6);
                int16 vTmp1In5 = __max(vTmpIn2, vTmpIn6);
                int16 vTmp1In6 = __min(vTmpIn3, vTmpIn7);
                int16 vTmp1In7 = __max(vTmpIn3, vTmpIn7);

                int16 vOutIn0 = __min(vTmp1In0, vTmp1In4);
                int16 vOutIn1 = __max(vTmp1In0, vTmp1In4);
                int16 vOutIn2 = __min(vTmp1In1, vTmp1In5);
                int16 vOutIn3 = __max(vTmp1In1, vTmp1In5);
                int16 vOutIn4 = __min(vTmp1In2, vTmp1In6);
                int16 vOutIn5 = __max(vTmp1In2, vTmp1In6);
                int16 vOutIn6 = __min(vTmp1In3, vTmp1In7);
                int16 vOutIn7 = __max(vTmp1In3, vTmp1In7);

                vIn0 = __sort_asc(vOutIn0);
                vIn1 = __sort_asc(vOutIn1);
                vIn2 = __sort_asc(vOutIn2);
                vIn3 = __sort_asc(vOutIn3);

                vIn4 = __sort_asc(vOutIn4);
                vIn5 = __sort_asc(vOutIn5);
                vIn6 = __sort_asc(vOutIn6);
                vIn7 = __sort_asc(vOutIn7);

#if(TRACE_ON)
                PRINTV("vIn0s =", __as_long8(vIn0), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                PRINTV("vIn1s =", __as_long8(vIn1), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                PRINTV("vIn2s =", __as_long8(vIn2), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                PRINTV("vIn3s =", __as_long8(vIn3), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);

                PRINTV("vIn4s =", __as_long8(vIn4), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                PRINTV("vIn5s =", __as_long8(vIn5), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                PRINTV("vIn6s =", __as_long8(vIn6), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                PRINTV("vIn7s =", __as_long8(vIn7), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
#endif

                *__SA0ADV(int16, pOut) = vIn0;
                *__SA0ADV(int16, pOut) = vIn1;
                *__SA0ADV(int16, pOut) = vIn2;
                *__SA0ADV(int16, pOut) = vIn3;

                *__SA0ADV(int16, pOut) = vIn4;
                *__SA0ADV(int16, pOut) = vIn5;
                *__SA0ADV(int16, pOut) = vIn6;
                *__SA0ADV(int16, pOut) = vIn7;
            }

            __SA2_CLOSE();
            __SA3_CLOSE();
            __SA0_CLOSE();

/////
            ping_nPong = !ping_nPong;

            saTemplate =   *stov_ptr(__STRM_TEMPLATE, (uint32_t*)((uint8_t *)pBlock + STAGE1_SA_PARAM_OFFSET + (stage * SA_PARAM_SIZE)));
            __SA2_OPEN(saTemplate);
            __SA3_OPEN(saTemplate);

            saTemplate =   *stov_ptr(__STRM_TEMPLATE, (uint32_t*)((uint8_t *)pBlock + STAGE1_SA1_PARAM_OFFSET + (stage * SA_PARAM_SIZE)));
            __SA1_OPEN(saTemplate);

            pIn1 = (int32_t *)buf[ping_nPong] + (SIMD_WIDTH * (1 << stage));
            pIn2 = (int32_t *)buf[ping_nPong] + (SIMD_WIDTH * numSets) + (SIMD_WIDTH * (1 << stage));

            ping_nPong = !ping_nPong;

            pOut = (int32_t *)buf[ping_nPong] + (SIMD_WIDTH * ((1 << (stage + 1)) - 1));
#pragma MUST_ITERATE(1,,)
            for(blkY = 0; blkY < numRows; blkY+=(1 << (stage + 1)))
            {
                    int16 vIn0 = *__SA2ADV(int16, pIn1);
                    int16 vIn1 = *__SA2ADV(int16, pIn1);
                    int16 vIn2 = *__SA2ADV(int16, pIn1);
                    int16 vIn3 = *__SA2ADV(int16, pIn1);

                    int16 vIn4 = *__SA3ADV(int16, pIn2);
                    int16 vIn5 = *__SA3ADV(int16, pIn2);
                    int16 vIn6 = *__SA3ADV(int16, pIn2);
                    int16 vIn7 = *__SA3ADV(int16, pIn2);

#if(TRACE_ON)
                    PRINTV("vIn0 =", __as_long8(vIn0), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn1 =", __as_long8(vIn1), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn2 =", __as_long8(vIn2), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn3 =", __as_long8(vIn3), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);

                    PRINTV("vIn4 =", __as_long8(vIn4), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn5 =", __as_long8(vIn5), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn6 =", __as_long8(vIn6), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn7 =", __as_long8(vIn7), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
#endif
                    int16 vTmpIn0 = __min(vIn0, vIn4);
                    int16 vTmpIn1 = __max(vIn0, vIn4);
                    int16 vTmpIn2 = __min(vIn1, vIn5);
                    int16 vTmpIn3 = __max(vIn1, vIn5);
                    int16 vTmpIn4 = __min(vIn2, vIn6);
                    int16 vTmpIn5 = __max(vIn2, vIn6);
                    int16 vTmpIn6 = __min(vIn3, vIn7);
                    int16 vTmpIn7 = __max(vIn3, vIn7);

                    int16 vTmp1In0 = __min(vTmpIn0, vTmpIn4);
                    int16 vTmp1In1 = __max(vTmpIn0, vTmpIn4);
                    int16 vTmp1In2 = __min(vTmpIn1, vTmpIn5);
                    int16 vTmp1In3 = __max(vTmpIn1, vTmpIn5);
                    int16 vTmp1In4 = __min(vTmpIn2, vTmpIn6);
                    int16 vTmp1In5 = __max(vTmpIn2, vTmpIn6);
                    int16 vTmp1In6 = __min(vTmpIn3, vTmpIn7);
                    int16 vTmp1In7 = __max(vTmpIn3, vTmpIn7);

                    int16 vOutIn0 = __min(vTmp1In0, vTmp1In4);
                    int16 vOutIn1 = __max(vTmp1In0, vTmp1In4);
                    int16 vOutIn2 = __min(vTmp1In1, vTmp1In5);
                    int16 vOutIn3 = __max(vTmp1In1, vTmp1In5);
                    int16 vOutIn4 = __min(vTmp1In2, vTmp1In6);
                    int16 vOutIn5 = __max(vTmp1In2, vTmp1In6);
                    int16 vOutIn6 = __min(vTmp1In3, vTmp1In7);
                    int16 vOutIn7 = __max(vTmp1In3, vTmp1In7);

                    vIn0 = __sort_desc(vOutIn0);
                    vIn1 = __sort_desc(vOutIn1);
                    vIn2 = __sort_desc(vOutIn2);
                    vIn3 = __sort_desc(vOutIn3);

                    vIn4 = __sort_desc(vOutIn4);
                    vIn5 = __sort_desc(vOutIn5);
                    vIn6 = __sort_desc(vOutIn6);
                    vIn7 = __sort_desc(vOutIn7);

#if(TRACE_ON)
                    PRINTV("vIn0s =", __as_long8(vIn0), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn1s =", __as_long8(vIn1), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn2s =", __as_long8(vIn2), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn3s =", __as_long8(vIn3), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);

                    PRINTV("vIn4s =", __as_long8(vIn4), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn5s =", __as_long8(vIn5), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn6s =", __as_long8(vIn6), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn7s =", __as_long8(vIn7), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);

#endif

                    *__SA1ADV(int16, pOut) = vIn0;
                    *__SA1ADV(int16, pOut) = vIn1;
                    *__SA1ADV(int16, pOut) = vIn2;
                    *__SA1ADV(int16, pOut) = vIn3;

                    *__SA1ADV(int16, pOut) = vIn4;
                    *__SA1ADV(int16, pOut) = vIn5;
                    *__SA1ADV(int16, pOut) = vIn6;
                    *__SA1ADV(int16, pOut) = vIn7;

            }

            __SA2_CLOSE();
            __SA3_CLOSE();
            __SA1_CLOSE();

#if(TRACE_ON)
            printf("Stage %d : ", stage);
            printf("numCols = %d, numRows = %d, bufID = %d\n", numCols, numRows, ping_nPong);

            saTemplate =   *stov_ptr(__STRM_TEMPLATE, (uint32_t*)((uint8_t *)pBlock + TRACE_SA_PARAM_OFFSET));
            __SA0_OPEN(saTemplate);

#pragma MUST_ITERATE(1,,)
            for(blkY = 0; blkY < numRows; blkY++)
            {
                int16 vIn  = *__SA0ADV(int16, (int32_t *)buf[ping_nPong]);
                PRINTV("vOut =", __as_long8(vIn), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
            }

            __SA0_CLOSE();
#endif
        }
        {
            stage = 4;
            numSets = 8;

            saTemplate =   *stov_ptr(__STRM_TEMPLATE, (uint32_t*)((uint8_t *)pBlock + STAGE1_SA_PARAM_OFFSET + (stage * SA_PARAM_SIZE)));
            __SA2_OPEN(saTemplate);
            __SA3_OPEN(saTemplate);

            saTemplate =   *stov_ptr(__STRM_TEMPLATE, (uint32_t*)((uint8_t *)pBlock + STAGE1_SA0_PARAM_OFFSET + (stage * SA_PARAM_SIZE)));
            __SA0_OPEN(saTemplate);

            pIn1 = (int32_t *)buf[ping_nPong];
            pIn2 = (int32_t *)buf[ping_nPong] + (SIMD_WIDTH * numSets);
            ping_nPong = !ping_nPong;

            pOut = (int32_t *)buf[ping_nPong];

#pragma MUST_ITERATE(1,,)
            for(blkY = 0; blkY < numRows; blkY+=(1 << (stage + 1)))
            {
                    int16 vIn0 = *__SA2ADV(int16, pIn1);
                    int16 vIn1 = *__SA2ADV(int16, pIn1);
                    int16 vIn2 = *__SA2ADV(int16, pIn1);
                    int16 vIn3 = *__SA2ADV(int16, pIn1);
                    int16 vIn4 = *__SA2ADV(int16, pIn1);
                    int16 vIn5 = *__SA2ADV(int16, pIn1);
                    int16 vIn6 = *__SA2ADV(int16, pIn1);
                    int16 vIn7 = *__SA2ADV(int16, pIn1);

                    int16 vIn8 = *__SA3ADV(int16, pIn2);
                    int16 vIn9 = *__SA3ADV(int16, pIn2);
                    int16 vInA = *__SA3ADV(int16, pIn2);
                    int16 vInB = *__SA3ADV(int16, pIn2);
                    int16 vInC = *__SA3ADV(int16, pIn2);
                    int16 vInD = *__SA3ADV(int16, pIn2);
                    int16 vInE = *__SA3ADV(int16, pIn2);
                    int16 vInF = *__SA3ADV(int16, pIn2);

#if(TRACE_ON)
                    PRINTV("vIn0 =", __as_long8(vIn0), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn1 =", __as_long8(vIn1), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn2 =", __as_long8(vIn2), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn3 =", __as_long8(vIn3), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn4 =", __as_long8(vIn4), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn5 =", __as_long8(vIn5), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn6 =", __as_long8(vIn6), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn7 =", __as_long8(vIn7), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);

                    PRINTV("vIn8 =", __as_long8(vIn8), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn9 =", __as_long8(vIn9), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vInA =", __as_long8(vInA), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vInB =", __as_long8(vInB), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vInC =", __as_long8(vInC), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vInD =", __as_long8(vInD), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vInE =", __as_long8(vInE), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vInF =", __as_long8(vInF), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);

#endif
                    int16 vTmpIn0 = __min(vIn0, vIn8);
                    int16 vTmpIn1 = __max(vIn0, vIn8);
                    int16 vTmpIn2 = __min(vIn1, vIn9);
                    int16 vTmpIn3 = __max(vIn1, vIn9);
                    int16 vTmpIn4 = __min(vIn2, vInA);
                    int16 vTmpIn5 = __max(vIn2, vInA);
                    int16 vTmpIn6 = __min(vIn3, vInB);
                    int16 vTmpIn7 = __max(vIn3, vInB);

                    int16 vTmpIn8 = __min(vIn4, vInC);
                    int16 vTmpIn9 = __max(vIn4, vInC);
                    int16 vTmpInA = __min(vIn5, vInD);
                    int16 vTmpInB = __max(vIn5, vInD);
                    int16 vTmpInC = __min(vIn6, vInE);
                    int16 vTmpInD = __max(vIn6, vInE);
                    int16 vTmpInE = __min(vIn7, vInF);
                    int16 vTmpInF = __max(vIn7, vInF);

                    int16 vTmp1In0 = __min(vTmpIn0, vTmpIn8);
                    int16 vTmp1In1 = __max(vTmpIn0, vTmpIn8);
                    int16 vTmp1In2 = __min(vTmpIn1, vTmpIn9);
                    int16 vTmp1In3 = __max(vTmpIn1, vTmpIn9);
                    int16 vTmp1In4 = __min(vTmpIn2, vTmpInA);
                    int16 vTmp1In5 = __max(vTmpIn2, vTmpInA);
                    int16 vTmp1In6 = __min(vTmpIn3, vTmpInB);
                    int16 vTmp1In7 = __max(vTmpIn3, vTmpInB);
                    int16 vTmp1In8 = __min(vTmpIn4, vTmpInC);
                    int16 vTmp1In9 = __max(vTmpIn4, vTmpInC);
                    int16 vTmp1InA = __min(vTmpIn5, vTmpInD);
                    int16 vTmp1InB = __max(vTmpIn5, vTmpInD);
                    int16 vTmp1InC = __min(vTmpIn6, vTmpInE);
                    int16 vTmp1InD = __max(vTmpIn6, vTmpInE);
                    int16 vTmp1InE = __min(vTmpIn7, vTmpInF);
                    int16 vTmp1InF = __max(vTmpIn7, vTmpInF);

                    int16 vTmp2In0 = __min(vTmp1In0, vTmp1In8);
                    int16 vTmp2In1 = __max(vTmp1In0, vTmp1In8);
                    int16 vTmp2In2 = __min(vTmp1In1, vTmp1In9);
                    int16 vTmp2In3 = __max(vTmp1In1, vTmp1In9);
                    int16 vTmp2In4 = __min(vTmp1In2, vTmp1InA);
                    int16 vTmp2In5 = __max(vTmp1In2, vTmp1InA);
                    int16 vTmp2In6 = __min(vTmp1In3, vTmp1InB);
                    int16 vTmp2In7 = __max(vTmp1In3, vTmp1InB);
                    int16 vTmp2In8 = __min(vTmp1In4, vTmp1InC);
                    int16 vTmp2In9 = __max(vTmp1In4, vTmp1InC);
                    int16 vTmp2InA = __min(vTmp1In5, vTmp1InD);
                    int16 vTmp2InB = __max(vTmp1In5, vTmp1InD);
                    int16 vTmp2InC = __min(vTmp1In6, vTmp1InE);
                    int16 vTmp2InD = __max(vTmp1In6, vTmp1InE);
                    int16 vTmp2InE = __min(vTmp1In7, vTmp1InF);
                    int16 vTmp2InF = __max(vTmp1In7, vTmp1InF);

                    int16 vOutIn0 = __min(vTmp2In0, vTmp2In8);
                    int16 vOutIn1 = __max(vTmp2In0, vTmp2In8);
                    int16 vOutIn2 = __min(vTmp2In1, vTmp2In9);
                    int16 vOutIn3 = __max(vTmp2In1, vTmp2In9);
                    int16 vOutIn4 = __min(vTmp2In2, vTmp2InA);
                    int16 vOutIn5 = __max(vTmp2In2, vTmp2InA);
                    int16 vOutIn6 = __min(vTmp2In3, vTmp2InB);
                    int16 vOutIn7 = __max(vTmp2In3, vTmp2InB);
                    int16 vOutIn8 = __min(vTmp2In4, vTmp2InC);
                    int16 vOutIn9 = __max(vTmp2In4, vTmp2InC);
                    int16 vOutInA = __min(vTmp2In5, vTmp2InD);
                    int16 vOutInB = __max(vTmp2In5, vTmp2InD);
                    int16 vOutInC = __min(vTmp2In6, vTmp2InE);
                    int16 vOutInD = __max(vTmp2In6, vTmp2InE);
                    int16 vOutInE = __min(vTmp2In7, vTmp2InF);
                    int16 vOutInF = __max(vTmp2In7, vTmp2InF);

                    vIn0 = __sort_asc(vOutIn0);
                    vIn1 = __sort_asc(vOutIn1);
                    vIn2 = __sort_asc(vOutIn2);
                    vIn3 = __sort_asc(vOutIn3);
                    vIn4 = __sort_asc(vOutIn4);
                    vIn5 = __sort_asc(vOutIn5);
                    vIn6 = __sort_asc(vOutIn6);
                    vIn7 = __sort_asc(vOutIn7);

                    vIn8 = __sort_asc(vOutIn8);
                    vIn9 = __sort_asc(vOutIn9);
                    vInA = __sort_asc(vOutInA);
                    vInB = __sort_asc(vOutInB);
                    vInC = __sort_asc(vOutInC);
                    vInD = __sort_asc(vOutInD);
                    vInE = __sort_asc(vOutInE);
                    vInF = __sort_asc(vOutInF);

#if(TRACE_ON)
                    PRINTV("vIn0s =", __as_long8(vIn0), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn1s =", __as_long8(vIn1), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn2s =", __as_long8(vIn2), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn3s =", __as_long8(vIn3), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn4s =", __as_long8(vIn4), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn5s =", __as_long8(vIn5), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn6s =", __as_long8(vIn6), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn7s =", __as_long8(vIn7), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);

                    PRINTV("vIn8s =", __as_long8(vIn8), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn9s =", __as_long8(vIn9), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vInAs =", __as_long8(vInA), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vInBs =", __as_long8(vInB), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vInCs =", __as_long8(vInC), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vInDs =", __as_long8(vInD), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vInEs =", __as_long8(vInE), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vInFs =", __as_long8(vInF), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);

#endif

                    *__SA0ADV(int16, pOut) = vIn0;
                    *__SA0ADV(int16, pOut) = vIn1;
                    *__SA0ADV(int16, pOut) = vIn2;
                    *__SA0ADV(int16, pOut) = vIn3;
                    *__SA0ADV(int16, pOut) = vIn4;
                    *__SA0ADV(int16, pOut) = vIn5;
                    *__SA0ADV(int16, pOut) = vIn6;
                    *__SA0ADV(int16, pOut) = vIn7;

                    *__SA0ADV(int16, pOut) = vIn8;
                    *__SA0ADV(int16, pOut) = vIn9;
                    *__SA0ADV(int16, pOut) = vInA;
                    *__SA0ADV(int16, pOut) = vInB;
                    *__SA0ADV(int16, pOut) = vInC;
                    *__SA0ADV(int16, pOut) = vInD;
                    *__SA0ADV(int16, pOut) = vInE;
                    *__SA0ADV(int16, pOut) = vInF;

            }

            __SA2_CLOSE();
            __SA3_CLOSE();
            __SA0_CLOSE();

            ping_nPong = !ping_nPong;

            saTemplate =   *stov_ptr(__STRM_TEMPLATE, (uint32_t*)((uint8_t *)pBlock + STAGE1_SA_PARAM_OFFSET + (stage * SA_PARAM_SIZE)));
            __SA2_OPEN(saTemplate);
            __SA3_OPEN(saTemplate);

            saTemplate =   *stov_ptr(__STRM_TEMPLATE, (uint32_t*)((uint8_t *)pBlock + STAGE1_SA1_PARAM_OFFSET + (stage * SA_PARAM_SIZE)));
            __SA1_OPEN(saTemplate);

            pIn1  = (int32_t *)buf[ping_nPong] + (SIMD_WIDTH * (1 << stage));
            pIn2  = (int32_t *)buf[ping_nPong] + (SIMD_WIDTH * numSets) + (SIMD_WIDTH * (1 << stage));

            ping_nPong = !ping_nPong;

            pOut  = (int32_t *)buf[ping_nPong] + (SIMD_WIDTH * ((1 << (stage + 1)) - 1));

#pragma MUST_ITERATE(1,,)
            for(blkY = 0; blkY < numRows; blkY+=(1 << (stage + 1)))
            {
                    int16 vIn0 = *__SA2ADV(int16, pIn1);
                    int16 vIn1 = *__SA2ADV(int16, pIn1);
                    int16 vIn2 = *__SA2ADV(int16, pIn1);
                    int16 vIn3 = *__SA2ADV(int16, pIn1);
                    int16 vIn4 = *__SA2ADV(int16, pIn1);
                    int16 vIn5 = *__SA2ADV(int16, pIn1);
                    int16 vIn6 = *__SA2ADV(int16, pIn1);
                    int16 vIn7 = *__SA2ADV(int16, pIn1);

                    int16 vIn8 = *__SA3ADV(int16, pIn2);
                    int16 vIn9 = *__SA3ADV(int16, pIn2);
                    int16 vInA = *__SA3ADV(int16, pIn2);
                    int16 vInB = *__SA3ADV(int16, pIn2);
                    int16 vInC = *__SA3ADV(int16, pIn2);
                    int16 vInD = *__SA3ADV(int16, pIn2);
                    int16 vInE = *__SA3ADV(int16, pIn2);
                    int16 vInF = *__SA3ADV(int16, pIn2);

#if(TRACE_ON)
                    PRINTV("vIn0 =", __as_long8(vIn0), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn1 =", __as_long8(vIn1), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn2 =", __as_long8(vIn2), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn3 =", __as_long8(vIn3), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn4 =", __as_long8(vIn4), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn5 =", __as_long8(vIn5), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn6 =", __as_long8(vIn6), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn7 =", __as_long8(vIn7), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);

                    PRINTV("vIn8 =", __as_long8(vIn8), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn9 =", __as_long8(vIn9), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vInA =", __as_long8(vInA), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vInB =", __as_long8(vInB), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vInC =", __as_long8(vInC), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vInD =", __as_long8(vInD), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vInE =", __as_long8(vInE), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vInF =", __as_long8(vInF), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);

#endif
                    int16 vTmpIn0 = __min(vIn0, vIn8);
                    int16 vTmpIn1 = __max(vIn0, vIn8);
                    int16 vTmpIn2 = __min(vIn1, vIn9);
                    int16 vTmpIn3 = __max(vIn1, vIn9);
                    int16 vTmpIn4 = __min(vIn2, vInA);
                    int16 vTmpIn5 = __max(vIn2, vInA);
                    int16 vTmpIn6 = __min(vIn3, vInB);
                    int16 vTmpIn7 = __max(vIn3, vInB);

                    int16 vTmpIn8 = __min(vIn4, vInC);
                    int16 vTmpIn9 = __max(vIn4, vInC);
                    int16 vTmpInA = __min(vIn5, vInD);
                    int16 vTmpInB = __max(vIn5, vInD);
                    int16 vTmpInC = __min(vIn6, vInE);
                    int16 vTmpInD = __max(vIn6, vInE);
                    int16 vTmpInE = __min(vIn7, vInF);
                    int16 vTmpInF = __max(vIn7, vInF);

                    int16 vTmp1In0 = __min(vTmpIn0, vTmpIn8);
                    int16 vTmp1In1 = __max(vTmpIn0, vTmpIn8);
                    int16 vTmp1In2 = __min(vTmpIn1, vTmpIn9);
                    int16 vTmp1In3 = __max(vTmpIn1, vTmpIn9);
                    int16 vTmp1In4 = __min(vTmpIn2, vTmpInA);
                    int16 vTmp1In5 = __max(vTmpIn2, vTmpInA);
                    int16 vTmp1In6 = __min(vTmpIn3, vTmpInB);
                    int16 vTmp1In7 = __max(vTmpIn3, vTmpInB);
                    int16 vTmp1In8 = __min(vTmpIn4, vTmpInC);
                    int16 vTmp1In9 = __max(vTmpIn4, vTmpInC);
                    int16 vTmp1InA = __min(vTmpIn5, vTmpInD);
                    int16 vTmp1InB = __max(vTmpIn5, vTmpInD);
                    int16 vTmp1InC = __min(vTmpIn6, vTmpInE);
                    int16 vTmp1InD = __max(vTmpIn6, vTmpInE);
                    int16 vTmp1InE = __min(vTmpIn7, vTmpInF);
                    int16 vTmp1InF = __max(vTmpIn7, vTmpInF);

                    int16 vTmp2In0 = __min(vTmp1In0, vTmp1In8);
                    int16 vTmp2In1 = __max(vTmp1In0, vTmp1In8);
                    int16 vTmp2In2 = __min(vTmp1In1, vTmp1In9);
                    int16 vTmp2In3 = __max(vTmp1In1, vTmp1In9);
                    int16 vTmp2In4 = __min(vTmp1In2, vTmp1InA);
                    int16 vTmp2In5 = __max(vTmp1In2, vTmp1InA);
                    int16 vTmp2In6 = __min(vTmp1In3, vTmp1InB);
                    int16 vTmp2In7 = __max(vTmp1In3, vTmp1InB);
                    int16 vTmp2In8 = __min(vTmp1In4, vTmp1InC);
                    int16 vTmp2In9 = __max(vTmp1In4, vTmp1InC);
                    int16 vTmp2InA = __min(vTmp1In5, vTmp1InD);
                    int16 vTmp2InB = __max(vTmp1In5, vTmp1InD);
                    int16 vTmp2InC = __min(vTmp1In6, vTmp1InE);
                    int16 vTmp2InD = __max(vTmp1In6, vTmp1InE);
                    int16 vTmp2InE = __min(vTmp1In7, vTmp1InF);
                    int16 vTmp2InF = __max(vTmp1In7, vTmp1InF);

                    int16 vOutIn0 = __min(vTmp2In0, vTmp2In8);
                    int16 vOutIn1 = __max(vTmp2In0, vTmp2In8);
                    int16 vOutIn2 = __min(vTmp2In1, vTmp2In9);
                    int16 vOutIn3 = __max(vTmp2In1, vTmp2In9);
                    int16 vOutIn4 = __min(vTmp2In2, vTmp2InA);
                    int16 vOutIn5 = __max(vTmp2In2, vTmp2InA);
                    int16 vOutIn6 = __min(vTmp2In3, vTmp2InB);
                    int16 vOutIn7 = __max(vTmp2In3, vTmp2InB);

                    int16 vOutIn8 = __min(vTmp2In4, vTmp2InC);
                    int16 vOutIn9 = __max(vTmp2In4, vTmp2InC);
                    int16 vOutInA = __min(vTmp2In5, vTmp2InD);
                    int16 vOutInB = __max(vTmp2In5, vTmp2InD);
                    int16 vOutInC = __min(vTmp2In6, vTmp2InE);
                    int16 vOutInD = __max(vTmp2In6, vTmp2InE);
                    int16 vOutInE = __min(vTmp2In7, vTmp2InF);
                    int16 vOutInF = __max(vTmp2In7, vTmp2InF);

                    vIn0 = __sort_desc(vOutIn0);
                    vIn1 = __sort_desc(vOutIn1);
                    vIn2 = __sort_desc(vOutIn2);
                    vIn3 = __sort_desc(vOutIn3);
                    vIn4 = __sort_desc(vOutIn4);
                    vIn5 = __sort_desc(vOutIn5);
                    vIn6 = __sort_desc(vOutIn6);
                    vIn7 = __sort_desc(vOutIn7);

                    vIn8 = __sort_desc(vOutIn8);
                    vIn9 = __sort_desc(vOutIn9);
                    vInA = __sort_desc(vOutInA);
                    vInB = __sort_desc(vOutInB);
                    vInC = __sort_desc(vOutInC);
                    vInD = __sort_desc(vOutInD);
                    vInE = __sort_desc(vOutInE);
                    vInF = __sort_desc(vOutInF);

#if(TRACE_ON)
                    PRINTV("vIn0s =", __as_long8(vIn0), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn1s =", __as_long8(vIn1), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn2s =", __as_long8(vIn2), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn3s =", __as_long8(vIn3), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn4s =", __as_long8(vIn4), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn5s =", __as_long8(vIn5), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn6s =", __as_long8(vIn6), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn7s =", __as_long8(vIn7), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);

                    PRINTV("vIn8s =", __as_long8(vIn8), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn9s =", __as_long8(vIn9), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vInAs =", __as_long8(vInA), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vInBs =", __as_long8(vInB), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vInCs =", __as_long8(vInC), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vInDs =", __as_long8(vInD), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vInEs =", __as_long8(vInE), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vInFs =", __as_long8(vInF), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);

#endif

                    *__SA1ADV(int16, pOut) = vIn0;
                    *__SA1ADV(int16, pOut) = vIn1;
                    *__SA1ADV(int16, pOut) = vIn2;
                    *__SA1ADV(int16, pOut) = vIn3;
                    *__SA1ADV(int16, pOut) = vIn4;
                    *__SA1ADV(int16, pOut) = vIn5;
                    *__SA1ADV(int16, pOut) = vIn6;
                    *__SA1ADV(int16, pOut) = vIn7;

                    *__SA1ADV(int16, pOut) = vIn8;
                    *__SA1ADV(int16, pOut) = vIn9;
                    *__SA1ADV(int16, pOut) = vInA;
                    *__SA1ADV(int16, pOut) = vInB;
                    *__SA1ADV(int16, pOut) = vInC;
                    *__SA1ADV(int16, pOut) = vInD;
                    *__SA1ADV(int16, pOut) = vInE;
                    *__SA1ADV(int16, pOut) = vInF;

            }

            __SA2_CLOSE();
            __SA3_CLOSE();
            __SA1_CLOSE();

#if(TRACE_ON)
            printf("Stage %d : ", stage);
            printf("numCols = %d, numRows = %d, bufID = %d\n", numCols, numRows, ping_nPong);

            saTemplate =   *stov_ptr(__STRM_TEMPLATE, (uint32_t*)((uint8_t *)pBlock + TRACE_SA_PARAM_OFFSET));
            __SA0_OPEN(saTemplate);

#pragma MUST_ITERATE(1,,)
            for(blkY = 0; blkY < numRows; blkY++)
            {
                int16 vIn  = *__SA0ADV(int16, (int32_t *)buf[ping_nPong]);
                PRINTV("vOut =", __as_long8(vIn), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
            }

            __SA0_CLOSE();
#endif
        }

        {
            stage = 5;
            numSets = 16;

            saTemplate =   *stov_ptr(__STRM_TEMPLATE, (uint32_t*)((uint8_t *)pBlock + STAGE1_SA_PARAM_OFFSET + (stage * SA_PARAM_SIZE)));
            __SA2_OPEN(saTemplate);
            __SA3_OPEN(saTemplate);

            saTemplate =   *stov_ptr(__STRM_TEMPLATE, (uint32_t*)((uint8_t *)pBlock + STAGE1_SA0_PARAM_OFFSET + (stage * SA_PARAM_SIZE)));
            __SA0_OPEN(saTemplate);

            pIn1 = (int32_t *)buf[ping_nPong];
            pIn2 = (int32_t *)buf[ping_nPong] + (SIMD_WIDTH * numSets);

            ping_nPong = !ping_nPong;

            pOut = buf[ping_nPong];
            //As loop is fully unrolled, no need to put a loop construct here
#pragma MUST_ITERATE(1,,)
            for(blkY = 0; blkY < numRows; blkY+=(1 << (stage + 1)))
            {
                    int16 vIn0 = *__SA2ADV(int16, pIn1);
                    int16 vIn1 = *__SA2ADV(int16, pIn1);
                    int16 vIn2 = *__SA2ADV(int16, pIn1);
                    int16 vIn3 = *__SA2ADV(int16, pIn1);
                    int16 vIn4 = *__SA2ADV(int16, pIn1);
                    int16 vIn5 = *__SA2ADV(int16, pIn1);
                    int16 vIn6 = *__SA2ADV(int16, pIn1);
                    int16 vIn7 = *__SA2ADV(int16, pIn1);
                    int16 vIn8 = *__SA2ADV(int16, pIn1);
                    int16 vIn9 = *__SA2ADV(int16, pIn1);
                    int16 vInA = *__SA2ADV(int16, pIn1);
                    int16 vInB = *__SA2ADV(int16, pIn1);
                    int16 vInC = *__SA2ADV(int16, pIn1);
                    int16 vInD = *__SA2ADV(int16, pIn1);
                    int16 vInE = *__SA2ADV(int16, pIn1);
                    int16 vInF = *__SA2ADV(int16, pIn1);

                    int16 vIn10 = *__SA3ADV(int16, pIn2);
                    int16 vIn11 = *__SA3ADV(int16, pIn2);
                    int16 vIn12 = *__SA3ADV(int16, pIn2);
                    int16 vIn13 = *__SA3ADV(int16, pIn2);
                    int16 vIn14 = *__SA3ADV(int16, pIn2);
                    int16 vIn15 = *__SA3ADV(int16, pIn2);
                    int16 vIn16 = *__SA3ADV(int16, pIn2);
                    int16 vIn17 = *__SA3ADV(int16, pIn2);
                    int16 vIn18 = *__SA3ADV(int16, pIn2);
                    int16 vIn19 = *__SA3ADV(int16, pIn2);
                    int16 vIn1A = *__SA3ADV(int16, pIn2);
                    int16 vIn1B = *__SA3ADV(int16, pIn2);
                    int16 vIn1C = *__SA3ADV(int16, pIn2);
                    int16 vIn1D = *__SA3ADV(int16, pIn2);
                    int16 vIn1E = *__SA3ADV(int16, pIn2);
                    int16 vIn1F = *__SA3ADV(int16, pIn2);

#if(TRACE_ON)
                    PRINTV("vIn0 =", __as_long8(vIn0), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn1 =", __as_long8(vIn1), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn2 =", __as_long8(vIn2), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn3 =", __as_long8(vIn3), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn4 =", __as_long8(vIn4), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn5 =", __as_long8(vIn5), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn6 =", __as_long8(vIn6), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn7 =", __as_long8(vIn7), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn8 =", __as_long8(vIn8), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn9 =", __as_long8(vIn9), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vInA =", __as_long8(vInA), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vInB =", __as_long8(vInB), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vInC =", __as_long8(vInC), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vInD =", __as_long8(vInD), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vInE =", __as_long8(vInE), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vInF =", __as_long8(vInF), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);

                    PRINTV("vIn10 =", __as_long8(vIn10), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn11 =", __as_long8(vIn11), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn12 =", __as_long8(vIn12), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn13 =", __as_long8(vIn13), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn14 =", __as_long8(vIn14), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn15 =", __as_long8(vIn15), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn16 =", __as_long8(vIn16), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn17 =", __as_long8(vIn17), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn18 =", __as_long8(vIn18), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn19 =", __as_long8(vIn19), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn1A =", __as_long8(vIn1A), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn1B =", __as_long8(vIn1B), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn1C =", __as_long8(vIn1C), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn1D =", __as_long8(vIn1D), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn1E =", __as_long8(vIn1E), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn1F =", __as_long8(vIn1F), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);

#endif
                    int16 vTmpIn0  = __min(vIn0, vIn10);
                    int16 vTmpIn1  = __max(vIn0, vIn10);
                    int16 vTmpIn2  = __min(vIn1, vIn11);
                    int16 vTmpIn3  = __max(vIn1, vIn11);
                    int16 vTmpIn4  = __min(vIn2, vIn12);
                    int16 vTmpIn5  = __max(vIn2, vIn12);
                    int16 vTmpIn6  = __min(vIn3, vIn13);
                    int16 vTmpIn7  = __max(vIn3, vIn13);
                    int16 vTmpIn8  = __min(vIn4, vIn14);
                    int16 vTmpIn9  = __max(vIn4, vIn14);
                    int16 vTmpInA  = __min(vIn5, vIn15);
                    int16 vTmpInB  = __max(vIn5, vIn15);
                    int16 vTmpInC  = __min(vIn6, vIn16);
                    int16 vTmpInD  = __max(vIn6, vIn16);
                    int16 vTmpInE  = __min(vIn7, vIn17);
                    int16 vTmpInF  = __max(vIn7, vIn17);
                    int16 vTmpIn10 = __min(vIn8, vIn18);
                    int16 vTmpIn11 = __max(vIn8, vIn18);
                    int16 vTmpIn12 = __min(vIn9, vIn19);
                    int16 vTmpIn13 = __max(vIn9, vIn19);
                    int16 vTmpIn14 = __min(vInA, vIn1A);
                    int16 vTmpIn15 = __max(vInA, vIn1A);
                    int16 vTmpIn16 = __min(vInB, vIn1B);
                    int16 vTmpIn17 = __max(vInB, vIn1B);
                    int16 vTmpIn18 = __min(vInC, vIn1C);
                    int16 vTmpIn19 = __max(vInC, vIn1C);
                    int16 vTmpIn1A = __min(vInD, vIn1D);
                    int16 vTmpIn1B = __max(vInD, vIn1D);
                    int16 vTmpIn1C = __min(vInE, vIn1E);
                    int16 vTmpIn1D = __max(vInE, vIn1E);
                    int16 vTmpIn1E = __min(vInF, vIn1F);
                    int16 vTmpIn1F = __max(vInF, vIn1F);

                    int16 vTmp1In0  = __min(vTmpIn0, vTmpIn10);
                    int16 vTmp1In1  = __max(vTmpIn0, vTmpIn10);
                    int16 vTmp1In2  = __min(vTmpIn1, vTmpIn11);
                    int16 vTmp1In3  = __max(vTmpIn1, vTmpIn11);
                    int16 vTmp1In4  = __min(vTmpIn2, vTmpIn12);
                    int16 vTmp1In5  = __max(vTmpIn2, vTmpIn12);
                    int16 vTmp1In6  = __min(vTmpIn3, vTmpIn13);
                    int16 vTmp1In7  = __max(vTmpIn3, vTmpIn13);
                    int16 vTmp1In8  = __min(vTmpIn4, vTmpIn14);
                    int16 vTmp1In9  = __max(vTmpIn4, vTmpIn14);
                    int16 vTmp1InA  = __min(vTmpIn5, vTmpIn15);
                    int16 vTmp1InB  = __max(vTmpIn5, vTmpIn15);
                    int16 vTmp1InC  = __min(vTmpIn6, vTmpIn16);
                    int16 vTmp1InD  = __max(vTmpIn6, vTmpIn16);
                    int16 vTmp1InE  = __min(vTmpIn7, vTmpIn17);
                    int16 vTmp1InF  = __max(vTmpIn7, vTmpIn17);
                    int16 vTmp1In10 = __min(vTmpIn8, vTmpIn18);
                    int16 vTmp1In11 = __max(vTmpIn8, vTmpIn18);
                    int16 vTmp1In12 = __min(vTmpIn9, vTmpIn19);
                    int16 vTmp1In13 = __max(vTmpIn9, vTmpIn19);
                    int16 vTmp1In14 = __min(vTmpInA, vTmpIn1A);
                    int16 vTmp1In15 = __max(vTmpInA, vTmpIn1A);
                    int16 vTmp1In16 = __min(vTmpInB, vTmpIn1B);
                    int16 vTmp1In17 = __max(vTmpInB, vTmpIn1B);
                    int16 vTmp1In18 = __min(vTmpInC, vTmpIn1C);
                    int16 vTmp1In19 = __max(vTmpInC, vTmpIn1C);
                    int16 vTmp1In1A = __min(vTmpInD, vTmpIn1D);
                    int16 vTmp1In1B = __max(vTmpInD, vTmpIn1D);
                    int16 vTmp1In1C = __min(vTmpInE, vTmpIn1E);
                    int16 vTmp1In1D = __max(vTmpInE, vTmpIn1E);
                    int16 vTmp1In1E = __min(vTmpInF, vTmpIn1F);
                    int16 vTmp1In1F = __max(vTmpInF, vTmpIn1F);

                    int16 vTmp2In0  = __min(vTmp1In0, vTmp1In10);
                    int16 vTmp2In1  = __max(vTmp1In0, vTmp1In10);
                    int16 vTmp2In2  = __min(vTmp1In1, vTmp1In11);
                    int16 vTmp2In3  = __max(vTmp1In1, vTmp1In11);
                    int16 vTmp2In4  = __min(vTmp1In2, vTmp1In12);
                    int16 vTmp2In5  = __max(vTmp1In2, vTmp1In12);
                    int16 vTmp2In6  = __min(vTmp1In3, vTmp1In13);
                    int16 vTmp2In7  = __max(vTmp1In3, vTmp1In13);
                    int16 vTmp2In8  = __min(vTmp1In4, vTmp1In14);
                    int16 vTmp2In9  = __max(vTmp1In4, vTmp1In14);
                    int16 vTmp2InA  = __min(vTmp1In5, vTmp1In15);
                    int16 vTmp2InB  = __max(vTmp1In5, vTmp1In15);
                    int16 vTmp2InC  = __min(vTmp1In6, vTmp1In16);
                    int16 vTmp2InD  = __max(vTmp1In6, vTmp1In16);
                    int16 vTmp2InE  = __min(vTmp1In7, vTmp1In17);
                    int16 vTmp2InF  = __max(vTmp1In7, vTmp1In17);
                    int16 vTmp2In10 = __min(vTmp1In8, vTmp1In18);
                    int16 vTmp2In11 = __max(vTmp1In8, vTmp1In18);
                    int16 vTmp2In12 = __min(vTmp1In9, vTmp1In19);
                    int16 vTmp2In13 = __max(vTmp1In9, vTmp1In19);
                    int16 vTmp2In14 = __min(vTmp1InA, vTmp1In1A);
                    int16 vTmp2In15 = __max(vTmp1InA, vTmp1In1A);
                    int16 vTmp2In16 = __min(vTmp1InB, vTmp1In1B);
                    int16 vTmp2In17 = __max(vTmp1InB, vTmp1In1B);
                    int16 vTmp2In18 = __min(vTmp1InC, vTmp1In1C);
                    int16 vTmp2In19 = __max(vTmp1InC, vTmp1In1C);
                    int16 vTmp2In1A = __min(vTmp1InD, vTmp1In1D);
                    int16 vTmp2In1B = __max(vTmp1InD, vTmp1In1D);
                    int16 vTmp2In1C = __min(vTmp1InE, vTmp1In1E);
                    int16 vTmp2In1D = __max(vTmp1InE, vTmp1In1E);
                    int16 vTmp2In1E = __min(vTmp1InF, vTmp1In1F);
                    int16 vTmp2In1F = __max(vTmp1InF, vTmp1In1F);

                    int16 vTmp3In0  = __min(vTmp2In0, vTmp2In10);
                    int16 vTmp3In1  = __max(vTmp2In0, vTmp2In10);
                    int16 vTmp3In2  = __min(vTmp2In1, vTmp2In11);
                    int16 vTmp3In3  = __max(vTmp2In1, vTmp2In11);
                    int16 vTmp3In4  = __min(vTmp2In2, vTmp2In12);
                    int16 vTmp3In5  = __max(vTmp2In2, vTmp2In12);
                    int16 vTmp3In6  = __min(vTmp2In3, vTmp2In13);
                    int16 vTmp3In7  = __max(vTmp2In3, vTmp2In13);
                    int16 vTmp3In8  = __min(vTmp2In4, vTmp2In14);
                    int16 vTmp3In9  = __max(vTmp2In4, vTmp2In14);
                    int16 vTmp3InA  = __min(vTmp2In5, vTmp2In15);
                    int16 vTmp3InB  = __max(vTmp2In5, vTmp2In15);
                    int16 vTmp3InC  = __min(vTmp2In6, vTmp2In16);
                    int16 vTmp3InD  = __max(vTmp2In6, vTmp2In16);
                    int16 vTmp3InE  = __min(vTmp2In7, vTmp2In17);
                    int16 vTmp3InF  = __max(vTmp2In7, vTmp2In17);
                    int16 vTmp3In10 = __min(vTmp2In8, vTmp2In18);
                    int16 vTmp3In11 = __max(vTmp2In8, vTmp2In18);
                    int16 vTmp3In12 = __min(vTmp2In9, vTmp2In19);
                    int16 vTmp3In13 = __max(vTmp2In9, vTmp2In19);
                    int16 vTmp3In14 = __min(vTmp2InA, vTmp2In1A);
                    int16 vTmp3In15 = __max(vTmp2InA, vTmp2In1A);
                    int16 vTmp3In16 = __min(vTmp2InB, vTmp2In1B);
                    int16 vTmp3In17 = __max(vTmp2InB, vTmp2In1B);
                    int16 vTmp3In18 = __min(vTmp2InC, vTmp2In1C);
                    int16 vTmp3In19 = __max(vTmp2InC, vTmp2In1C);
                    int16 vTmp3In1A = __min(vTmp2InD, vTmp2In1D);
                    int16 vTmp3In1B = __max(vTmp2InD, vTmp2In1D);
                    int16 vTmp3In1C = __min(vTmp2InE, vTmp2In1E);
                    int16 vTmp3In1D = __max(vTmp2InE, vTmp2In1E);
                    int16 vTmp3In1E = __min(vTmp2InF, vTmp2In1F);
                    int16 vTmp3In1F = __max(vTmp2InF, vTmp2In1F);

                    int16 vTmp4In0  = __min(vTmp3In0, vTmp3In10);
                    int16 vTmp4In1  = __max(vTmp3In0, vTmp3In10);
                    int16 vTmp4In2  = __min(vTmp3In1, vTmp3In11);
                    int16 vTmp4In3  = __max(vTmp3In1, vTmp3In11);
                    int16 vTmp4In4  = __min(vTmp3In2, vTmp3In12);
                    int16 vTmp4In5  = __max(vTmp3In2, vTmp3In12);
                    int16 vTmp4In6  = __min(vTmp3In3, vTmp3In13);
                    int16 vTmp4In7  = __max(vTmp3In3, vTmp3In13);
                    int16 vTmp4In8  = __min(vTmp3In4, vTmp3In14);
                    int16 vTmp4In9  = __max(vTmp3In4, vTmp3In14);
                    int16 vTmp4InA  = __min(vTmp3In5, vTmp3In15);
                    int16 vTmp4InB  = __max(vTmp3In5, vTmp3In15);
                    int16 vTmp4InC  = __min(vTmp3In6, vTmp3In16);
                    int16 vTmp4InD  = __max(vTmp3In6, vTmp3In16);
                    int16 vTmp4InE  = __min(vTmp3In7, vTmp3In17);
                    int16 vTmp4InF  = __max(vTmp3In7, vTmp3In17);
                    int16 vTmp4In10 = __min(vTmp3In8, vTmp3In18);
                    int16 vTmp4In11 = __max(vTmp3In8, vTmp3In18);
                    int16 vTmp4In12 = __min(vTmp3In9, vTmp3In19);
                    int16 vTmp4In13 = __max(vTmp3In9, vTmp3In19);
                    int16 vTmp4In14 = __min(vTmp3InA, vTmp3In1A);
                    int16 vTmp4In15 = __max(vTmp3InA, vTmp3In1A);
                    int16 vTmp4In16 = __min(vTmp3InB, vTmp3In1B);
                    int16 vTmp4In17 = __max(vTmp3InB, vTmp3In1B);
                    int16 vTmp4In18 = __min(vTmp3InC, vTmp3In1C);
                    int16 vTmp4In19 = __max(vTmp3InC, vTmp3In1C);
                    int16 vTmp4In1A = __min(vTmp3InD, vTmp3In1D);
                    int16 vTmp4In1B = __max(vTmp3InD, vTmp3In1D);
                    int16 vTmp4In1C = __min(vTmp3InE, vTmp3In1E);
                    int16 vTmp4In1D = __max(vTmp3InE, vTmp3In1E);
                    int16 vTmp4In1E = __min(vTmp3InF, vTmp3In1F);
                    int16 vTmp4In1F = __max(vTmp3InF, vTmp3In1F);

                    vIn0 = __sort_asc(vTmp4In0);
                    vIn1 = __sort_asc(vTmp4In1);
                    vIn2 = __sort_asc(vTmp4In2);
                    vIn3 = __sort_asc(vTmp4In3);
                    vIn4 = __sort_asc(vTmp4In4);
                    vIn5 = __sort_asc(vTmp4In5);
                    vIn6 = __sort_asc(vTmp4In6);
                    vIn7 = __sort_asc(vTmp4In7);
                    vIn8 = __sort_asc(vTmp4In8);
                    vIn9 = __sort_asc(vTmp4In9);
                    vInA = __sort_asc(vTmp4InA);
                    vInB = __sort_asc(vTmp4InB);
                    vInC = __sort_asc(vTmp4InC);
                    vInD = __sort_asc(vTmp4InD);
                    vInE = __sort_asc(vTmp4InE);
                    vInF = __sort_asc(vTmp4InF);

                    vIn10 = __sort_asc(vTmp4In10);
                    vIn11 = __sort_asc(vTmp4In11);
                    vIn12 = __sort_asc(vTmp4In12);
                    vIn13 = __sort_asc(vTmp4In13);
                    vIn14 = __sort_asc(vTmp4In14);
                    vIn15 = __sort_asc(vTmp4In15);
                    vIn16 = __sort_asc(vTmp4In16);
                    vIn17 = __sort_asc(vTmp4In17);
                    vIn18 = __sort_asc(vTmp4In18);
                    vIn19 = __sort_asc(vTmp4In19);
                    vIn1A = __sort_asc(vTmp4In1A);
                    vIn1B = __sort_asc(vTmp4In1B);
                    vIn1C = __sort_asc(vTmp4In1C);
                    vIn1D = __sort_asc(vTmp4In1D);
                    vIn1E = __sort_asc(vTmp4In1E);
                    vIn1F = __sort_asc(vTmp4In1F);

#if(TRACE_ON)
                    PRINTV("vIn0s =", __as_long8(vIn0), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn1s =", __as_long8(vIn1), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn2s =", __as_long8(vIn2), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn3s =", __as_long8(vIn3), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn4s =", __as_long8(vIn4), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn5s =", __as_long8(vIn5), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn6s =", __as_long8(vIn6), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn7s =", __as_long8(vIn7), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn8s =", __as_long8(vIn8), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn9s =", __as_long8(vIn9), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vInAs =", __as_long8(vInA), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vInBs =", __as_long8(vInB), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vInCs =", __as_long8(vInC), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vInDs =", __as_long8(vInD), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vInEs =", __as_long8(vInE), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vInFs =", __as_long8(vInF), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);

                    PRINTV("vIn10s =", __as_long8(vIn10), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn11s =", __as_long8(vIn11), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn12s =", __as_long8(vIn12), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn13s =", __as_long8(vIn13), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn14s =", __as_long8(vIn14), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn15s =", __as_long8(vIn15), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn16s =", __as_long8(vIn16), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn17s =", __as_long8(vIn17), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn18s =", __as_long8(vIn18), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn19s =", __as_long8(vIn19), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn1As =", __as_long8(vIn1A), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn1Bs =", __as_long8(vIn1B), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn1Cs =", __as_long8(vIn1C), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn1Ds =", __as_long8(vIn1D), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn1Es =", __as_long8(vIn1E), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
                    PRINTV("vIn1Fs =", __as_long8(vIn1F), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);

#endif

                    *__SA0ADV(int16, pOut) = vIn0;
                    *__SA0ADV(int16, pOut) = vIn1;
                    *__SA0ADV(int16, pOut) = vIn2;
                    *__SA0ADV(int16, pOut) = vIn3;
                    *__SA0ADV(int16, pOut) = vIn4;
                    *__SA0ADV(int16, pOut) = vIn5;
                    *__SA0ADV(int16, pOut) = vIn6;
                    *__SA0ADV(int16, pOut) = vIn7;
                    *__SA0ADV(int16, pOut) = vIn8;
                    *__SA0ADV(int16, pOut) = vIn9;
                    *__SA0ADV(int16, pOut) = vInA;
                    *__SA0ADV(int16, pOut) = vInB;
                    *__SA0ADV(int16, pOut) = vInC;
                    *__SA0ADV(int16, pOut) = vInD;
                    *__SA0ADV(int16, pOut) = vInE;
                    *__SA0ADV(int16, pOut) = vInF;

                    *__SA0ADV(int16, pOut) = vIn10;
                    *__SA0ADV(int16, pOut) = vIn11;
                    *__SA0ADV(int16, pOut) = vIn12;
                    *__SA0ADV(int16, pOut) = vIn13;
                    *__SA0ADV(int16, pOut) = vIn14;
                    *__SA0ADV(int16, pOut) = vIn15;
                    *__SA0ADV(int16, pOut) = vIn16;
                    *__SA0ADV(int16, pOut) = vIn17;
                    *__SA0ADV(int16, pOut) = vIn18;
                    *__SA0ADV(int16, pOut) = vIn19;
                    *__SA0ADV(int16, pOut) = vIn1A;
                    *__SA0ADV(int16, pOut) = vIn1B;
                    *__SA0ADV(int16, pOut) = vIn1C;
                    *__SA0ADV(int16, pOut) = vIn1D;
                    *__SA0ADV(int16, pOut) = vIn1E;
                    *__SA0ADV(int16, pOut) = vIn1F;

            }

            __SA2_CLOSE();
            __SA3_CLOSE();
            __SA0_CLOSE();

#if(TRACE_ON)
            printf("Stage %d : ", stage);
            printf("numCols = %d, numRows = %d, bufID = %d\n", numCols, numRows, ping_nPong);

            saTemplate =   *stov_ptr(__STRM_TEMPLATE, (uint32_t*)((uint8_t *)pBlock + TRACE_SA_PARAM_OFFSET));
            __SA0_OPEN(saTemplate);

#pragma MUST_ITERATE(1,,)
            for(blkY = 0; blkY < numRows; blkY++)
            {
                int16 vIn  = *__SA0ADV(int16, (int32_t *)buf[ping_nPong]);
                PRINTV("vOut =", __as_long8(vIn), PRINTV_SIGNED_32BIT, PRINTV_HEX_OFF);
            }

            __SA0_CLOSE();
#endif
        }

    }
    return (status);
}

#if (!defined(VXLIB_REMOVE_CHECK_PARAMS) && !defined(VXLIB_MERGE_SORT_I32S_O32S_REMOVE_CHECK_PARAMS)) || (defined(VXLIB_CHECK_PARAMS)) || (defined(VXLIB_MERGE_SORT_I32S_O32S_CHECK_PARAMS))

VXLIB_STATUS VXLIB_mergeSort_i32s_o32s_checkParams(int32_t dat[],
                                                   int32_t out[],
                                                   int16_t dat_size,
                                                   void *pBlock)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

    return (status);
}

#endif
