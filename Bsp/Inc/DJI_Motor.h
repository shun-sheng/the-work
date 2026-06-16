#ifndef __DJI_MOTOR_H
#define __DJI_MOTOR_H

#include "can_bsp.h"
typedef struct
{
    int8_t ONLINE_JUDGE_TIME;
    int16_t Angle_last; // 上一个角度值
    int16_t Angle_now;  // 现在的角度值
    int16_t Speed_last; // 上一个速度值
    int16_t Speed_now;  // 现在的速度值
    int16_t current;
    int8_t temperature;
    int32_t Angle_Infinite;
    int64_t Stuck_Time;
    uint16_t Stuck_Flag[2];
    int32_t Laps;
    float Error;
    float Aim;
    float Aim_last;
    float dt;
    int16_t Angle_Init;
}DJI_MOTOR_DATA_Typedef;


void CAN_RX_DJI6020_DATA(DJI_MOTOR_DATA_Typedef* DATA , uint8_t* can_data);
void CAN_RX_DJI3508_DATA(DJI_MOTOR_DATA_Typedef* DATA , uint8_t* can_data);
void CAN_RX_DM4310_DATA(DJI_MOTOR_DATA_Typedef* DATA , uint8_t* can_data);
void DJI_Current_Ctrl(hcan_t* hcan, uint16_t stdid, int16_t num1, int16_t num2, int16_t num3, int16_t num4);

//typedef struct
//{
//    uint8_t PID_INIT;
//    DJI_MOTOR_DATA_Typedef DATA;
//    Feedforward_t PID_F;
//    PID_t PID_P;
//    PID_t PID_S;
//}DJI_MOTOR_Typedef;
#endif