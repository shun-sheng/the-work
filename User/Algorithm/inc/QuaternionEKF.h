#ifndef _QUAT_EKF_H
#define _QUAT_EKF_H
#include "MY_Define.h"

void IMU_QuaternionEKF_Init(float process_noise1, float process_noise2, float measure_noise, float lambda, float dt, float lpf);
void IMU_QuaternionEKF_Update(float gx, float gy, float gz, float ax, float ay, float az);
void IMU_QuaternionEKF_Reset(void);

float Get_Pitch(void);//get pitch
float Get_Roll(void);//get roll
float Get_Yaw(void);//get yaw
float Get_YawTotalAngle(void);
#endif
