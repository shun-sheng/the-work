#ifndef __CHASSIS_TASK_H
#define __CHASSIS_TASK_H
#include "MY_Define.h"

void CHhassiswheel_PID_Init(MOTOR_Typedef *ALL_MOTOR,Average *ALL_Average_Speed);
void Chassis_MecanumInit(void);
void Chassis_MecanumResolve(float Vx, float Vy, float Vr, float Angle);
void Chassis_SpinInit(void);
void Chassis_ControlTask(void);

#endif
