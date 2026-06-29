
#ifndef RUI_MATH_H
#define RUI_MATH_H

#include "MY_Define.h"

int16_t RUI_F_MATH_ABS_int16_t(int16_t DATA);
int32_t RUI_F_MATH_ABS_int32_t(int32_t DATA);
float RUI_F_MATH_ABS_float(float DATA);
float RUI_F_MATH_Limit_float(float MAX , float MIN , float DATA);
int16_t RUI_F_MATH_Limit_int16(int16_t MAX , int16_t MIN , int16_t DATA);
float RUI_F_MATH_INV_SQRT_float(float DATA);
//float uint_to_float(int16_t x_int, float span, int16_t value);
float Hex_To_Float(uint32_t *Byte,int num);
uint32_t FloatTohex(float HEX);
int float_to_uint(float x_float, float x_min, float x_max, int bits);
float uint_to_float(int x_int, float x_min, float x_max, int bits);
float get_vbus_input(uint16_t value);
float averageFilter(float in_data);
float IntervalCyclic(float max, float min, float* data);
float shortest_path(float Current,float Target);
float low(float*a,float b,float n);
float IntervalLimit(float max, float min, float data);
float limit(float max, float min, float* data);

#endif
