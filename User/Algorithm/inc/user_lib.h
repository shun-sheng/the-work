#ifndef _USER_LIB_H
#define _USER_LIB_H

#include  "MY_Define.h"

extern uint8_t GlobalDebugMode;

//快速开方
float Sqrt(float x);
//斜波函数初始化
void ramp_init(ramp_function_source_t *ramp_source_type, float frame_period, float max, float min);
//斜波函数计算
float ramp_calc(ramp_function_source_t *ramp_source_type, float input);
//绝对限制
float abs_limit(float num, float Limit);
//判断符号位
float sign(float value);
//浮点死区
float float_deadband(float Value, float minValue, float maxValue);
// int26死区
int16_t int16_deadline(int16_t Value, int16_t minValue, int16_t maxValue);
//限幅函数
float float_constrain(float Value, float minValue, float maxValue);
//限幅函数
int16_t int16_constrain(int16_t Value, int16_t minValue, int16_t maxValue);
//循环限幅函数
float loop_float_constrain(float Input, float minValue, float maxValue);
//角度 °限幅 180 ~ -180
float theta_format(float Ang);

int float_rounding(float raw);

void OLS_Init(Ordinary_Least_Squares_t *OLS, uint16_t order);
void OLS_Update(Ordinary_Least_Squares_t *OLS, float deltax, float y);
float OLS_Derivative(Ordinary_Least_Squares_t *OLS, float deltax, float y);
float OLS_Smooth(Ordinary_Least_Squares_t *OLS, float deltax, float y);
float Get_OLS_Derivative(Ordinary_Least_Squares_t *OLS);
float Get_OLS_Smooth(Ordinary_Least_Squares_t *OLS);

#endif
