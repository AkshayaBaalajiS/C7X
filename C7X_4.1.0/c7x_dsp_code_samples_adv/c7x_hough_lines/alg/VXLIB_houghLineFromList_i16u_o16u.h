/*
* module name       : c7x_hough_lines
*
* module descripton : Computes Hough Lines
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#ifndef VLIB_HOUGHLINEFROMLIST_H_
#define VLIB_HOUGHLINEFROMLIST_H_ 1

#include "VXLIB_types.h"

#define VXLIB_HOUGHLINE_FROM_LIST_I16U_O16U_PBLOCK_SIZE (64)

#define SQRTof2_Q8 362    /* 1.414213 * 256 = 362.038*/

/** @defgroup VXLIB_houghLineFromList*/
/** @ingroup VXLIB_houghLineFromList */
/* @{ */

/**
 * @par Description
 *  Initialization function for the VXLIB_houghLineFromList_i16u_o16u_kernel() function
 *
 * @par
 *    @param [in]  *pEdgeMapList      Points to a list of 2xlistSize values of type uint16_t
 *                                      which represent x and y values of edge points         (UQ16.0)
 *    @param [out] *pOutHoughSpace    Points to the Hough space                               (UQ16.0)
 *    @param [in]   outBlkWidth       Width of the original image                             (UQ16.0)
 *    @param [in]   outBlkHeight      Height of original image                                (UQ16.0)
 *    @param [in]   listSize          Size of the edge list                                   (UQ32.0)
 *    @param [in]   thetaRange        Number of samples for theta Range                       (UQ16.0)
 *    @param [in]   rhoMaxLength      Number of samples for rho Range                         (UQ16.0)
 *    @param [in]  *pSIN              Sine lookup tables                                      (SQ15.0)
 *    @param [in]  *pCOS              Cosine lookup tables                                    (SQ15.0)
 *   @param [out]  pBlock          Pointer to the memory of size VXLIB_HOUGHLINE_FROM_LIST_I16U_O16U_PBLOCK_SIZE bytes, which will be used to store the streaming engine and streaming address generator parameters.
 *
 *
 *  @par Assumptions
 *  - pEdgeMapList points to a list of (2 * \c listSize) values of type uint16_t, which represent x and y
 *    values of edge points: x1,y1,x2,y2, ... While it should be located in the fastest memory available, its
 *    role is cache friendly so it can be stored in the external memory.
 *  - pOutHoughSpace points to the Hough space, which is a (\c thetaRange * \c rhoMaxLength) array of uint16_t.
 *    While it should be located in the fastest memory available, its role is cache friendly so it can be
 *    stored in the external memory.
 *  - outBlkWidth and outBlkHeight represent width and height of the original image
 *  - pSIN and pCOS are lookup tables for sine and cosine and can be generated during initialization.
 *    While it should be located in the fastest memory available, its role is cache friendly so it can
 *    be stored in the external memory.
 *  - The function is written so that the list of edge points can be broken into sublists and the function
 *    called on them separately. This is useful if the list needs to be in the fast memory, but is too big
 *    to fit there. In that case, the Hough space should be cleared only before the call on the first sublist.
 *
 *
 */
VXLIB_STATUS VXLIB_houghLineFromList_i16u_o16u_init(
    uint16_t * restrict pEdgeMapList,
    uint16_t * restrict pOutHoughSpace,
    uint16_t outBlkWidth,
    uint16_t outBlkHeight,
    uint32_t listSize,
    uint16_t thetaRange,
    uint16_t rhoMaxLength,
    const int16_t *pSIN,
    const int16_t *pCOS,
    void *pBlock
);


/**
 * @par Description
 * VXLIB_houghLineFromList_i16u_o16u_kernel() function
 *
 * @par
 *    @param [in]  *pEdgeMapList      Points to a list of 2xlistSize values of type uint16_t
 *                                      which represent x and y values of edge points         (UQ16.0)
 *    @param [out] *pOutHoughSpace    Points to the Hough space                               (UQ16.0)
 *    @param [in]   outBlkWidth       Width of the original image                             (UQ16.0)
 *    @param [in]   outBlkHeight      Height of original image                                (UQ16.0)
 *    @param [in]   listSize          Size of the edge list                                   (UQ32.0)
 *    @param [in]   thetaRange        Number of samples for theta Range                       (UQ16.0)
 *    @param [in]   rhoMaxLength      Number of samples for rho Range                         (UQ16.0)
 *    @param [in]  *pSIN              Sine lookup tables                                      (SQ15.0)
 *    @param [in]  *pCOS              Cosine lookup tables                                    (SQ15.0)
 *   @param [out]  pBlock          Pointer to the memory of size VXLIB_HOUGHLINE_FROM_LIST_I16U_O16U_PBLOCK_SIZE bytes, which was used to store the streaming engine and streaming address generator parameters.
 *
 *
 *  @par Assumptions
 *  - pEdgeMapList points to a list of (2 * \c listSize) values of type uint16_t, which represent x and y
 *    values of edge points: x1,y1,x2,y2, ... While it should be located in the fastest memory available, its
 *    role is cache friendly so it can be stored in the external memory.
 *  - pOutHoughSpace points to the Hough space, which is a (\c thetaRange * \c rhoMaxLength) array of uint16_t.
 *    While it should be located in the fastest memory available, its role is cache friendly so it can be
 *    stored in the external memory.
 *  - outBlkWidth and outBlkHeight represent width and height of the original image
 *  - pSIN and pCOS are lookup tables for sine and cosine and can be generated during initialization.
 *    While it should be located in the fastest memory available, its role is cache friendly so it can
 *    be stored in the external memory.
 *  - The function is written so that the list of edge points can be broken into sublists and the function
 *    called on them separately. This is useful if the list needs to be in the fast memory, but is too big
 *    to fit there. In that case, the Hough space should be cleared only before the call on the first sublist.
 *
 *
 */
VXLIB_STATUS VXLIB_houghLineFromList_i16u_o16u_kernel(
                             uint16_t * restrict pEdgeMapList,
                             uint16_t * restrict pOutHoughSpace,
                             uint16_t outBlkWidth,
                             uint16_t outBlkHeight,
                             uint32_t listSize,
                             uint16_t theta,
                             uint16_t rhoMaxLength,
                             const int16_t *pSIN,
                             const int16_t *pCOS,
                             void *pBlock
                             );


#endif /* VLIB_HOUGHLINEFROMLIST_H_ */
/** @} */
/* ======================================================================== */
/*  End of file:  VLIB_houghLineFromList.h                                  */
/* ======================================================================== */
