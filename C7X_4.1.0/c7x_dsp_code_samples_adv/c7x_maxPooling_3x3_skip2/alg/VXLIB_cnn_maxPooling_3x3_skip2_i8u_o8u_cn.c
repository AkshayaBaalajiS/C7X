/*
* module name       : c7x_maxPooling_3x3_skip2
*
* module descripton : Max Pooling, 3x3 window, skip 2 positions horz/vert
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#include "VXLIB_cnn_maxPooling_3x3_skip2_i8u_o8u_cn.h"

VXLIB_STATUS VXLIB_cnnMaxPooling_3x3_skip2_i8u_o8u_cn
(
  uint8_t   src[],
  VXLIB_bufParams3D_t srcAddr[],
  uint8_t   dst[],
  VXLIB_bufParams3D_t dstAddr[],
  uint16_t  kernelW,
  uint16_t  kernelH,
  uint16_t  strideW,
  uint16_t  strideH
)
{
  uint16_t    width, height;
  uint16_t    inPitch, outPitch;
  uint32_t    inChPitch, outChPitch;
  uint16_t    numOutChannels;
  uint8_t     inRowCol;
  uint16_t    i1, i2, i3, i4, i5;
  uint8_t     maxValue, maxvalueBlock;

  width        = srcAddr->dim_x;
  height       = srcAddr->dim_y;
  inPitch      = srcAddr->stride_y;
  outPitch     = dstAddr->stride_y;
  inChPitch    = srcAddr->stride_z;
  outChPitch   = dstAddr->stride_z;
  numOutChannels   = dstAddr->dim_z;

  for(i1 = 0; i1< numOutChannels; i1++)
  {
    for (i2 = 0; i2 <(height/strideH) ; i2++)
    {
      for (i3 = 0; i3 < (width/strideW) ; i3++)
      {
        maxValue = 0;
        for (i4 = 0; i4 < kernelH; i4++)
        {
          for (i5 = 0; i5 <kernelW; i5++)
          {
            inRowCol = src[(i1* inChPitch) +
                       ((((uint32_t)i2 * strideH) + i4) * inPitch) + ((uint32_t)i3 * strideW) + i5];

            /* Maxpooling operations */
            maxvalueBlock = (maxValue > inRowCol) ? maxValue : inRowCol;
            maxValue = maxvalueBlock;
          }
        }

        dst[(i1*outChPitch) + ((uint32_t)i2 * outPitch) + i3] = maxvalueBlock;
      }
    }
  }

  return (VXLIB_SUCCESS);
}
