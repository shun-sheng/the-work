#ifndef __GIMBAL_TASK_H
#define __GIMBAL_TASK_H

#include "MY_Define.h"

uint8_t Gimbal_PID_Init(MOTOR_Typedef *MOTOR);
uint8_t Gimbal_Task(CONTAL_Typedef *CONTAL,
    MOTOR_Typedef *MOTOR,
    IMU_Data_t *IMU);
#endif
