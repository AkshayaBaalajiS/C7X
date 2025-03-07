/*
* module name       : c7x_common
*
* module descripton : Common utility functions
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#ifndef VXLIB_INLINES_H_
#define VXLIB_INLINES_H_ 1

#include <math.h>
#include <float.h>

#define VXLIB_RAND_MAX (0x7ffffffeU)
#define SQRT2 (1.414f)

static inline VXLIB_F32 VXLIB_oneByXF32(VXLIB_F32 x);
static inline VXLIB_D64 VXLIB_oneByXD64(VXLIB_D64 x);

static inline VXLIB_F32 VXLIB_yByXF32(VXLIB_F32 y, VXLIB_F32 x);
static inline VXLIB_D64 VXLIB_yByXD64(VXLIB_D64 y, VXLIB_D64 x);

static inline float16 VXLIB_yByXVecF32(float16 y, float16 x);
static inline double8 VXLIB_yByXVecD64(double8 y, double8 x);

static inline VXLIB_F32 VXLIB_oneBySqrtXF32(VXLIB_F32 x);
static inline VXLIB_D64 VXLIB_oneBySqrtXD64(VXLIB_D64 x);

static inline VXLIB_F32 VXLIB_sqrtXF32(VXLIB_F32 x);
static inline VXLIB_D64 VXLIB_sqrtXD64(VXLIB_D64 x);

static inline float16 VXLIB_oneBySqrtXVecF32(float16 vX);
static inline double8 VXLIB_oneBySqrtXVecD64(double8 vX);

static inline float16 VXLIB_sqrtXVecF32(float16 vX);
static inline double8 VXLIB_sqrtXVecD64(double8 vX);

static inline float16 VXLIB_oneByXVecF32(float16 vX);
static inline double8 VXLIB_oneByXVecD64(double8 vX);

static inline int32_t VXLIB_randPnpRansac(int32_t maxOp, uint32_t *nextCustGndPlnDetect);

static VXLIB_F32 findRelNormL2(VXLIB_F32 * a, VXLIB_F32 * b, int32_t numPoints);
static VXLIB_F32 findAbsNormL2(VXLIB_F32 * a, int32_t numPoints);

static inline VXLIB_F32 VXLIB_oneByXF32(VXLIB_F32 x)
{
    VXLIB_F32    TWO = 2.0f;
    VXLIB_F32    X,Y;

    Y = __abs(x);

    X = __recip(x);

    X = X  * (TWO - (x * X));
    X = X  * (TWO - (x * X));

    if( Y >= FLT_MAX ) {
        X = FLT_MIN;
    }

    if( Y <= FLT_MIN ) {
        X = FLT_MAX;
    }

    return (X);
}

static inline VXLIB_D64 VXLIB_oneByXD64(VXLIB_D64 x)
{
    VXLIB_D64    TWO = 2.0f;
    VXLIB_D64    X,Y;

    Y = __abs(x);

    X = __recip(x);

    X = X  * (TWO - (x * X));
    X = X  * (TWO - (x * X));

    if( Y >= DBL_MAX ) {
        X = DBL_MIN;
    }

    if( Y <= DBL_MIN ) {
        X = DBL_MAX;
    }

    return (X);
}

static inline VXLIB_F32 VXLIB_yByXF32(VXLIB_F32 y, VXLIB_F32 x)
{
    VXLIB_F32    X;

    X = y * VXLIB_oneByXF32(x);

    return (X);
}

static inline VXLIB_D64 VXLIB_yByXD64(VXLIB_D64 y, VXLIB_D64 x)
{
    VXLIB_D64    X;

    X = y * VXLIB_oneByXD64(x);

    return (X);
}

static inline float16 VXLIB_oneByXVecF32(float16 vX)
{

    float16    f2Pkd = (float16)2.0f;
    float16    vX0,vY;
    __vpred    vp;

    vY  = __abs(vX);
    vX0 = __recip(vX);

    vX0 = vX0 * (f2Pkd - (vX0 * vX));

    vX0 = vX0 * (f2Pkd - (vX0 * vX));

    /* If input value is higher or equal to FLT_MAX
    */
    vp  = __cmp_le_pred((float16)FLT_MAX, vY);

    vX0 = __select(vp,(float16)FLT_MIN,vX0);

    /* If input value is lesser or equal to FLT_MIN
    */
    vp  = __cmp_le_pred(vY, (float16)FLT_MIN);

    vX0 = __select(vp,(float16)FLT_MAX,vX0);

    return (vX0);
}

static inline double8 VXLIB_oneByXVecD64(double8 vX)
{

    double8    f2Pkd = (double8)2.0f;
    double8    vX0,vY;
    __vpred    vp;

    vY  = __abs(vX);
    vX0 = __recip(vX);

    vX0 = vX0 * (f2Pkd - (vX0 * vX));

    vX0 = vX0 * (f2Pkd - (vX0 * vX));

    /* If input value is higher or equal to FLT_MAX
    */
    vp  = __cmp_le_pred((double8)DBL_MAX, vY);

    vX0 = __select(vp,(double8)DBL_MIN,vX0);

    /* If input value is lesser or equal to FLT_MIN
    */
    vp  = __cmp_le_pred(vY, (double8)DBL_MIN);

    vX0 = __select(vp,(double8)DBL_MAX,vX0);

    return (vX0);
}

static inline VXLIB_F32 VXLIB_oneBySqrtXF32(VXLIB_F32 x)
{
    VXLIB_F32    normInv, val;
    VXLIB_F32    Y;

    Y = __abs(x);

    normInv   = __recip_sqrt(x);
    val       = normInv * ((3.0f - (x * (normInv * normInv))) * 0.5f);
    normInv   = val * ((3.0f - (x * (val * val))) * 0.5f);

    if( Y >= FLT_MAX ) {
      normInv = FLT_MIN;
    }

    if( Y <= FLT_MIN ) {
      normInv = FLT_MAX;
    }

    /* If input is negative then this is undefined scenarion.
     * For now just making output as minimum in this undefined scenarion.
     */
    if(x <= 0.0f){
      normInv = FLT_MIN;
    }

    return (normInv);
}

static inline VXLIB_F32 VXLIB_sqrtXF32(VXLIB_F32 x)
{
    VXLIB_F32    X;

    X = x * VXLIB_oneBySqrtXF32(x);

    return (X);
}

static inline VXLIB_D64 VXLIB_oneBySqrtXD64(VXLIB_D64 x)
{
    VXLIB_D64    normInv, val;
    VXLIB_D64    Y;

    Y = __abs(x);

    normInv   = __recip_sqrt(x);
    val       = normInv * ((3.0f - (x * (normInv * normInv))) * 0.5f);
    normInv   = val * ((3.0f - (x * (val * val))) * 0.5f);

    if( Y >= DBL_MAX ) {
      normInv = DBL_MIN;
    }

    if( Y <= DBL_MIN ) {
      normInv = DBL_MAX;
    }

    /* If input is negative then this is undefined scenarion.
     * For now just making output as minimum in this undefined scenarion.
     */
    if(x <= 0.0){
      normInv = DBL_MIN;
    }

    return (normInv);
}

static inline VXLIB_D64 VXLIB_sqrtXD64(VXLIB_D64 x)
{
    VXLIB_D64    X;

    X = x * VXLIB_oneBySqrtXD64(x);

    return (X);
}

static inline float16 VXLIB_oneBySqrtXVecF32(float16 vX)
{
    float16    vY,vX0;
    float16    f3Pkd = (float16)3.0f;
    __vpred    vp;

    vY       = __abs(vX);
    vX0      = __recip_sqrt(vX);

    vX0  = vX0 * ((f3Pkd - (vX * (vX0 * vX0))) * (float16)0.5f);
    vX0  = vX0 * ((f3Pkd - (vX * (vX0 * vX0))) * (float16)0.5f);

    /* If input value is higher or equal to FLT_MAX
    */
    vp  = __cmp_le_pred((float16)FLT_MAX, vY);

    vX0 = __select(vp,(float16)FLT_MIN,vX0);

    /* If input value is lesser or equal to FLT_MIN
    */
    vp  = __cmp_le_pred(vY, (float16)FLT_MIN);

    vX0 = __select(vp,(float16)FLT_MAX,vX0);


    /* If input is negative then this is undefined scenarion.
     * For now just making output as FLT_MIN in this undefined scenarion.
     */
    vp  = __cmp_le_pred(vX, (float16)0.0f);

    vX0 = __select(vp,(float16)FLT_MIN,vX0);

    return (vX0);
}

static inline float16 VXLIB_sqrtXVecF32(float16 vX)
{
  return(vX*VXLIB_oneBySqrtXVecF32(vX));
}

static inline double8 VXLIB_oneBySqrtXVecD64(double8 vX)
{
    double8    vY,vX0;
    double8    f3Pkd = (double8)3.0f;
    __vpred    vp;

    vY       = __abs(vX);
    vX0      = __recip_sqrt(vX);

    vX0  = vX0 * ((f3Pkd - (vX * (vX0 * vX0))) * (double8)0.5f);
    vX0  = vX0 * ((f3Pkd - (vX * (vX0 * vX0))) * (double8)0.5f);

    /* If input value is higher or equal to FLT_MAX
    */
    vp  = __cmp_le_pred((double8)DBL_MAX, vY);

    vX0 = __select(vp,(double8)DBL_MIN,vX0);

    /* If input value is lesser or equal to FLT_MIN
    */
    vp  = __cmp_le_pred(vY, (double8)DBL_MIN);

    vX0 = __select(vp,(double8)DBL_MAX,vX0);


    /* If input is negative then this is undefined scenarion.
     * For now just making output as DBL_MIN in this undefined scenarion.
     */
    vp  = __cmp_le_pred(vX, (double8)0.0f);

    vX0 = __select(vp,(double8)DBL_MIN,vX0);

    return (vX0);
}

static inline double8 VXLIB_sqrtXVecD64(double8 vX)
{
  return(vX*VXLIB_oneBySqrtXVecD64(vX));
}

static inline float16 VXLIB_yByXVecF32(float16 y, float16 x){

 return(y*VXLIB_oneByXVecF32(x));

}

static inline double8 VXLIB_yByXVecD64(double8 y, double8 x){

  return(y*VXLIB_oneByXVecD64(x));

}

/**
 * Customized random number generator for gnd plane detect
 */

static int32_t VXLIB_randPnpRansac(int32_t maxOp, uint32_t *nextCust)
{
  int32_t r;
  uint32_t localNextCust = *nextCust;


  localNextCust = localNextCust * 1103515245 + 12345;

  //TODO :: remove RTSC modulo operation
  r = (int32_t) (((localNextCust) >> 16) % (maxOp + 1));

  *nextCust = localNextCust;

  return r;
}
static VXLIB_F32 findAbsNormL2(VXLIB_F32 * a, int32_t numPoints)
{
  VXLIB_F32 sum = 0;
  int32_t i;

  for(i = 0; i < numPoints; i++)
  {
    sum += a[i] * a[i];
  }

  return (VXLIB_sqrtXF32(sum));

}

static VXLIB_F32 findRelNormL2(VXLIB_F32 * a, VXLIB_F32 * b, int32_t numPoints)
{
  VXLIB_F32 sum = 0;
  int32_t i;

  for(i = 0; i < numPoints; i++)
  {
    sum += (a[i] - b[i])*(a[i] - b[i]);
  }

  return (VXLIB_sqrtXF32(sum));
}

#endif
