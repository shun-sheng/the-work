#ifndef __IMU_TASK_H
#define __IMU_TASK_H

#include  "MY_Define.h"

void IMU_Temperature_Ctrl(IMU_Data_t *IMU, pid_type_def *imu_temp_pid);
void IMU_Gyro_Zero_Calibration_Task(IMU_Data_t *IMU);
void INS_Task(IMU_Data_t *IMU, pid_type_def *imu_temp_pid);

#endif