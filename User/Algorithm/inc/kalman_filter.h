
#ifndef __KALMAN_FILTER_H
#define __KALMAN_FILTER_H

#include  "MY_Define.h"

void Kalman_Filter_Init(KalmanFilter_t *kf, uint8_t xhatSize, uint8_t uSize, uint8_t zSize);
void Kalman_Filter_Reset(KalmanFilter_t *kf, uint8_t xhatSize, uint8_t uSize, uint8_t zSize);
void Kalman_Filter_Measure(KalmanFilter_t *kf);
void Kalman_Filter_xhatMinusUpdate(KalmanFilter_t *kf);
void Kalman_Filter_PminusUpdate(KalmanFilter_t *kf);
void Kalman_Filter_SetK(KalmanFilter_t *kf);
void Kalman_Filter_xhatUpdate(KalmanFilter_t *kf);
void Kalman_Filter_P_Update(KalmanFilter_t *kf);
float *Kalman_Filter_Update(KalmanFilter_t *kf);

#endif //__KALMAN_FILTER_H
