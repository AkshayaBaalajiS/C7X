/*
* module name       : c7x_kalman_4x8_correct
*
* module descripton : Does a 4x8 (constant velocity) Kalman filter update
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#ifndef VXLIB_KALMANFILTER_H_
#define VXLIB_KALMANFILTER_H_ 1

#include "VXLIB_types.h"

#define mD_1x2 (1)
#define sD_1x2 (2)

#define mD_2x4 (2)
#define sD_2x4 (4)

#define mD_4x6 (4)
#define sD_4x6 (6)

#define mD_4x8 (4)
#define sD_4x8 (8)

#define mD_4x12 (4)
#define sD_4x12 (12)

/*!
 * \brief Structure defining the state of the Kalman filter, 2x4 (2-Dimension Observation x 4-Dimension State Vectors) variant
 */
typedef struct VXLIB_kalmanFilter_2x4 {
    int16_t transition[sD_2x4 * sD_2x4];          /*!< SQ15.0, state transition matrix, A */
    int16_t errorCov[sD_2x4 * sD_2x4];            /*!< SQ13.2, a priori error covariance matrix, P */
    int16_t predictedErrorCov[sD_2x4 * sD_2x4];   /*!< SQ13.2, predicted error covariance matrix, P1 */
    int16_t state[sD_2x4];                        /*!< SQ10.5, state of the process, X */
    int16_t predictedState[sD_2x4];               /*!< SQ10.5, predicted state of the process, X1 */
    int16_t measurement[mD_2x4 * sD_2x4];         /*!< SQ15.0, measurement matrix (relating state to measurement), H */
    int16_t processNoiseCov[sD_2x4 * sD_2x4];     /*!< SQ13.2, process noise covariance matrix, Q */
    int16_t measurementNoiseCov[mD_2x4 * mD_2x4]; /*!< SQ15.0, measurement noise covariance matrix, R */
    int16_t kalmanGain[sD_2x4 * mD_2x4];          /*!< SQ0.15, Kalman gain, K */
    int16_t temp1[sD_2x4 * sD_2x4];
    int16_t temp2[sD_2x4 * sD_2x4];
    int16_t temp3[sD_2x4 * sD_2x4];
} VXLIB_kalmanFilter_2x4;


/*!
 * \brief Structure defining the state of the Kalman filter, 4x6 (4-Dimension Observation x 6-Dimension State Vectors) variant
 */
typedef struct VXLIB_kalmanFilter_4x6 {
    int16_t transition[sD_4x6 * sD_4x6];          /*!< SQ15.0, state transition matrix, A */
    int16_t errorCov[sD_4x6 * sD_4x6];            /*!< SQ13.2, a priori error covariance matrix, P */
    int16_t predictedErrorCov[sD_4x6 * sD_4x6];   /*!< SQ13.2, predicted error covariance matrix, P1 */
    int16_t state[sD_4x6];                        /*!< SQ10.5, state of the process, X */
    int16_t predictedState[sD_4x6];               /*!< SQ10.5, predicted state of the process, X1 */
    int16_t measurement[mD_4x6 * sD_4x6];         /*!< SQ15.0, measurement matrix (relating state to measurement), H */
    int16_t processNoiseCov[sD_4x6 * sD_4x6];     /*!< SQ13.2, process noise covariance matrix, Q */
    int16_t measurementNoiseCov[mD_4x6 * mD_4x6]; /*!< SQ15.0, measurement noise covariance matrix, R */
    int16_t kalmanGain[sD_4x6 * mD_4x6];          /*!< SQ0.15, Kalman gain, K */
    int16_t temp1[sD_4x6 * sD_4x6];
    int16_t temp2[sD_4x6 * sD_4x6];
    int16_t temp3[sD_4x6 * sD_4x6];
    int32_t tempBuffers[mD_4x6 * mD_4x6 * 2];

    int32_t scaleFactor;   /*!< Scales the matrix M = (H*P1*H' + R) to ensure that its inverse does not overflow 32 bits.
                            The scaling is done by right shifting each element of M by the quantity assigned to scaleFactor.
                            The computed inverse is then scaled back to ensure the correct result based on the identity
                            inv(M) = inv(M/k)/k */

} VXLIB_kalmanFilter_4x6;

/*!
 * \brief Structure defining the state of the Kalman filter for the S16_F32, 2x4 (2-Dimension Observation x 4-Dimension State Vectors) variant
 */
typedef struct VXLIB_kalmanFilter_2x4_S16_F32 {
    VXLIB_F32 transition[sD_2x4 * sD_2x4];          /*!< state transition matrix, A */
    VXLIB_F32 errorCov[sD_2x4 * sD_2x4];            /*!< a priori error covariance matrix, P */
    VXLIB_F32 predictedErrorCov[sD_2x4 * sD_2x4];   /*!< predicted error covariance matrix, P1 */
    int16_t  state[sD_2x4];                       /*!< state of the process, X */
    VXLIB_F32 predictedState[sD_2x4];               /*!< predicted state of the process, X1 */
    VXLIB_F32 measurement[mD_2x4 * sD_2x4];         /*!< measurement matrix (relating state to measurement), H */
    VXLIB_F32 processNoiseCov[sD_2x4 * sD_2x4];     /*!< process noise covariance matrix, Q */
    VXLIB_F32 measurementNoiseCov[mD_2x4 * mD_2x4]; /*!< measurement noise covariance matrix, R */
    VXLIB_F32 kalmanGain[sD_2x4 * mD_2x4];          /*!< Kalman gain, K */
    VXLIB_F32 temp1[sD_2x4 * sD_2x4];
    VXLIB_F32 temp2[sD_2x4 * sD_2x4];
    VXLIB_F32 temp3[sD_2x4 * sD_2x4];
} VXLIB_kalmanFilter_2x4_S16_F32;

/*!
 * \brief Structure defining the state of the Kalman filter for the S16_F32, 4x6 (4-Dimension Observation x 6-Dimension State Vectors) variant
 */
typedef struct VXLIB_kalmanFilter_4x6_S16_F32 {
    VXLIB_F32 transition[sD_4x6 * sD_4x6];          /*!< state transition matrix, A */
    VXLIB_F32 errorCov[sD_4x6 * sD_4x6];            /*!< a priori error covariance matrix, P */
    VXLIB_F32 predictedErrorCov[sD_4x6 * sD_4x6];   /*!< predicted error covariance matrix, P1 */
    int16_t  state[sD_4x6];                       /*!< state of the process, X */
    VXLIB_F32 predictedState[sD_4x6];               /*!< predicted state of the process, X1 */
    VXLIB_F32 measurement[mD_4x6 * sD_4x6];         /*!< measurement matrix (relating state to measurement), H */
    VXLIB_F32 processNoiseCov[sD_4x6 * sD_4x6];     /*!< process noise covariance matrix, Q */
    VXLIB_F32 measurementNoiseCov[mD_4x6 * mD_4x6]; /*!< measurement noise covariance matrix, R */
    VXLIB_F32 kalmanGain[sD_4x6 * mD_4x6];          /*!< Kalman gain, K */
    VXLIB_F32 temp1[sD_4x6 * sD_4x6];
    VXLIB_F32 temp2[sD_4x6 * sD_4x6];
    VXLIB_F32 temp3[sD_4x6 * sD_4x6];
    VXLIB_F32 tempBuffers[mD_4x6 * mD_4x6 * 2];

    int32_t scaleFactor;   /*!< Scales the matrix M = (H*P1*H' + R) to ensure that its inverse does not overflow 32 bits.
                            The scaling is done by right shifting each element of M by the quantity assigned to scaleFactor.
                            The computed inverse is then scaled back to ensure the correct result based on the identity
                            inv(M) = inv(M/k)/k */

} VXLIB_kalmanFilter_4x6_S16_F32;

/*!
 * \brief Structure defining the state of the Kalman filter for the F32, 2x4 (2-Dimension Observation x 4-Dimension State Vectors) variant
 */
typedef struct VXLIB_kalmanFilter_2x4_F32 {
    VXLIB_F32 transition[sD_2x4 * sD_2x4];          /*!< state transition matrix, A*/
    VXLIB_F32 errorCov[sD_2x4 * sD_2x4];            /*!< a priori error covariance matrix, P*/
    VXLIB_F32 predictedErrorCov[sD_2x4 * sD_2x4];   /*!< predicted error covariance matrix, P1*/
    VXLIB_F32 state[sD_2x4];                        /*!< state of the process, X*/
    VXLIB_F32 predictedState[sD_2x4];               /*!< predicted state of the process, X1*/
    VXLIB_F32 measurement[mD_2x4 * sD_2x4];         /*!< measurement matrix (relating state to measurement), H*/
    VXLIB_F32 processNoiseCov[sD_2x4 * sD_2x4];     /*!< process noise covariance matrix, Q*/
    VXLIB_F32 measurementNoiseCov[mD_2x4 * mD_2x4]; /*!< measurement noise covariance matrix, R*/
    VXLIB_F32 kalmanGain[sD_2x4 * mD_2x4];          /*!< Kalman gain, K*/
    VXLIB_F32 temp1[sD_2x4 * sD_2x4];
    VXLIB_F32 temp2[sD_2x4 * sD_2x4];
    VXLIB_F32 temp3[sD_2x4 * sD_2x4];
} VXLIB_kalmanFilter_2x4_F32;

/*!
 * \brief Structure defining the state of the Kalman filter for the F32, 4x6 (4-Dimension Observation x 6-Dimension State Vectors) variant
 */
typedef struct VXLIB_kalmanFilter_4x6_F32 {
    VXLIB_F32 transition[sD_4x6 * sD_4x6];          /*!< state transition matrix, A*/
    VXLIB_F32 errorCov[sD_4x6 * sD_4x6];            /*!< a priori error covariance matrix, P*/
    VXLIB_F32 predictedErrorCov[sD_4x6 * sD_4x6];   /*!< predicted error covariance matrix, P1*/
    VXLIB_F32 state[sD_4x6];                        /*!< state of the process, X*/
    VXLIB_F32 predictedState[sD_4x6];               /*!< predicted state of the process, X1*/
    VXLIB_F32 measurement[mD_4x6 * sD_4x6];         /*!< measurement matrix (relating state to measurement), H*/
    VXLIB_F32 processNoiseCov[sD_4x6 * sD_4x6];     /*!< process noise covariance matrix, Q*/
    VXLIB_F32 measurementNoiseCov[mD_4x6 * mD_4x6]; /*!< measurement noise covariance matrix, R*/
    VXLIB_F32 kalmanGain[sD_4x6 * mD_4x6];          /*!< Kalman gain, K*/
    VXLIB_F32 temp1[sD_4x6 * sD_4x6];
    VXLIB_F32 temp2[sD_4x6 * sD_4x6];
    VXLIB_F32 temp3[sD_4x6 * sD_4x6];
    int32_t  tempBuffers[mD_4x6 * mD_4x6 * 2];

    int32_t scaleFactor;   /*!< Scales the matrix M = (H*P1*H' + R) to ensure that its inverse does not overflow 32 bits.
                            The scaling is done by right shifting each element of M by the quantity assigned to scaleFactor.
                            The computed inverse is then scaled back to ensure the correct result based on the identity
                            inv(M) = inv(M/k)/k */

} VXLIB_kalmanFilter_4x6_F32;

/*!
 * \brief Structure defining the state of the Kalman filter for the F32, 4x8 (4-Dimension Observation x 8-Dimension State Vectors) variant
 */
typedef struct VXLIB_kalmanFilter_4x8_F32 {
    VXLIB_F32 transition[sD_4x8 * sD_4x8];          /*!< state transition matrix, A*/
    VXLIB_F32 errorCov[sD_4x8 * sD_4x8];            /*!< a priori error covariance matrix, P*/
    VXLIB_F32 predictedErrorCov[sD_4x8 * sD_4x8];   /*!< predicted error covariance matrix, P1*/
    VXLIB_F32 state[sD_4x8];                        /*!< state of the process, X*/
    VXLIB_F32 predictedState[sD_4x8];               /*!< predicted state of the process, X1*/
    VXLIB_F32 measurement[mD_4x8 * sD_4x8];         /*!< measurement matrix (relating state to measurement), H*/
    VXLIB_F32 processNoiseCov[sD_4x8 * sD_4x8];     /*!< process noise covariance matrix, Q*/
    VXLIB_F32 measurementNoiseCov[mD_4x8 * mD_4x8]; /*!< measurement noise covariance matrix, R*/
    VXLIB_F32 kalmanGain[sD_4x8 * mD_4x8];          /*!< Kalman gain, K*/
    VXLIB_F32 temp1[sD_4x8 * sD_4x8];
    VXLIB_F32 temp2[sD_4x8 * sD_4x8];
    VXLIB_F32 temp3[sD_4x8 * sD_4x8];
    int32_t  tempBuffers[mD_4x8 * mD_4x8 * 2];

    int32_t scaleFactor;   /*!< Scales the matrix M = (H*P1*H' + R) to ensure that its inverse does not overflow 32 bits.
                            The scaling is done by right shifting each element of M by the quantity assigned to scaleFactor.
                            The computed inverse is then scaled back to ensure the correct result based on the identity
                            inv(M) = inv(M/k)/k */

} VXLIB_kalmanFilter_4x8_F32;


/*!
 * \brief Structure defining the state of the Kalman filter for the F32, 4x12 (4-Dimension Observation x 12-Dimension State Vectors) variant
 */
typedef struct VXLIB_kalmanFilter_4x12_F32 {
    VXLIB_F32 transition[sD_4x12 * sD_4x12];          /*!< state transition matrix, A*/
    VXLIB_F32 errorCov[sD_4x12 * sD_4x12];            /*!< a priori error covariance matrix, P*/
    VXLIB_F32 predictedErrorCov[sD_4x12 * sD_4x12];   /*!< predicted error covariance matrix, P1*/
    VXLIB_F32 state[sD_4x12];                        /*!< state of the process, X*/
    VXLIB_F32 predictedState[sD_4x12];               /*!< predicted state of the process, X1*/
    VXLIB_F32 measurement[mD_4x12 * sD_4x12];         /*!< measurement matrix (relating state to measurement), H*/
    VXLIB_F32 processNoiseCov[sD_4x12 * sD_4x12];     /*!< process noise covariance matrix, Q*/
    VXLIB_F32 measurementNoiseCov[mD_4x12 * mD_4x12]; /*!< measurement noise covariance matrix, R*/
    VXLIB_F32 kalmanGain[sD_4x12 * mD_4x12];          /*!< Kalman gain, K*/
    VXLIB_F32 temp1[sD_4x12 * sD_4x12];
    VXLIB_F32 temp2[sD_4x12 * sD_4x12];
    VXLIB_F32 temp3[sD_4x12 * sD_4x12];
    int32_t  tempBuffers[mD_4x12 * mD_4x12 * 2];

    int32_t scaleFactor;   /*!< Scales the matrix M = (H*P1*H' + R) to ensure that its inverse does not overflow 32 bits.
                            The scaling is done by right shifting each element of M by the quantity assigned to scaleFactor.
                            The computed inverse is then scaled back to ensure the correct result based on the identity
                            inv(M) = inv(M/k)/k */

} VXLIB_kalmanFilter_4x12_F32;

/*!
 * \brief Structure defining the state of the Kalman filter for the F32, 4x12 (4-Dimension Observation x 12-Dimension State Vectors) variant
 */
typedef struct VXLIB_kalmanFilter_1x2_F32 {
    VXLIB_F32 transition[sD_1x2 * sD_1x2];          /*!< state transition matrix, A*/
    VXLIB_F32 errorCov[sD_1x2 * sD_1x2];            /*!< a priori error covariance matrix, P*/
    VXLIB_F32 predictedErrorCov[sD_1x2 * sD_1x2];   /*!< predicted error covariance matrix, P1*/
    VXLIB_F32 state[sD_1x2];                        /*!< state of the process, X*/
    VXLIB_F32 predictedState[sD_1x2];               /*!< predicted state of the process, X1*/
    VXLIB_F32 measurement[mD_1x2 * sD_1x2];         /*!< measurement matrix (relating state to measurement), H*/
    VXLIB_F32 processNoiseCov[sD_1x2 * sD_1x2];     /*!< process noise covariance matrix, Q*/
    VXLIB_F32 measurementNoiseCov[mD_1x2 * mD_1x2]; /*!< measurement noise covariance matrix, R*/
    VXLIB_F32 kalmanGain[sD_1x2 * mD_1x2];          /*!< Kalman gain, K*/
    VXLIB_F32 temp1[sD_1x2 * sD_1x2];
    VXLIB_F32 temp2[sD_1x2 * sD_1x2];
    VXLIB_F32 temp3[sD_1x2 * sD_1x2];
    int32_t  tempBuffers[mD_1x2 * mD_1x2 * 2];

    int32_t scaleFactor;   /*!< Scales the matrix M = (H*P1*H' + R) to ensure that its inverse does not overflow 32 bits.
                            The scaling is done by right shifting each element of M by the quantity assigned to scaleFactor.
                            The computed inverse is then scaled back to ensure the correct result based on the identity
                            inv(M) = inv(M/k)/k */

} VXLIB_kalmanFilter_1x2_F32;
#endif
