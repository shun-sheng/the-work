#ifndef BOTTOM_H
#define BOTTOM_H

#include "MY_Define.h"

uint8_t MecanumInit(mecanumInit_typdef *mecanumInitT);
void MecanumResolve(float *wheel_rpm, float vx_temp, float vy_temp, float vr, mecanumInit_typdef *mecanumInit_t);
void Mecanum_SpinResolve(float *wheel_rpm, float vx, float vy, float vr,
                         float yaw_angle, uint8_t spin_enable,
                         mecanumInit_typdef *param);

uint8_t OmniInit(OmniInit_typdef *OmniInitT);
void Omni_calc(float *wheel_rpm, float vx_temp, float vy_temp, float vr, OmniInit_typdef *OmniInit_t);

#endif
