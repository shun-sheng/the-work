#include "Gimbal_Task.h"
#include "controller.h"
#include "can.h"
#include "DJI_Motor.h"

uint8_t Gimbal_PID_Init(MOTOR_Typedef *MOTOR)
{
    float Gimbal_PID_S_Pitch[3]={};
    float Gimbal_PID_P_Pitch[3]={};
    float Gimbal_PID_F_Pitch[3]={};

    Feedforward_Init(&MOTOR->DJI_6020_Pitch.PID_F, 3000, Gimbal_PID_F_Pitch,
                     0.5f, 2, 2);
    PID_Init(&MOTOR->DJI_6020_Pitch.PID_P, 6000.0f, 2000.0f,
             Gimbal_PID_P_Pitch, 1000.0f, 1000.0f,
             0.7f, 0.7f, 2,
             Integral_Limit|OutputFilter|ErrorHandle//积分限幅,输出滤波,堵转监测
             |Trapezoid_Intergral|ChangingIntegrationRate//梯形积分,变速积分
             |Derivative_On_Measurement|DerivativeFilter);//微分先行,微分滤波器
    PID_Init(&MOTOR->DJI_6020_Pitch.PID_S, 6000.0f, 2000.0f,
             Gimbal_PID_S_Pitch, 1000.0f, 1000.0f,
             0.7f, 0.7f, 2,
             Integral_Limit|OutputFilter|ErrorHandle//积分限幅,输出滤波,堵转监测
             |Trapezoid_Intergral|ChangingIntegrationRate//梯形积分,变速积分
             |Derivative_On_Measurement|DerivativeFilter);//微分先行
    float Gimbal_PID_S_Yaw[3]={};
    float Gimbal_PID_P_Yaw[3]={};
    float Gimbal_PID_F_Yaw[3]={};

    Feedforward_Init(&MOTOR->DJI_6020_Yaw.PID_F, 3000, Gimbal_PID_F_Yaw,
                     0.5f, 2, 2);
    PID_Init(&MOTOR->DJI_6020_Yaw.PID_P, 6000.0f, 2000.0f,
             Gimbal_PID_P_Yaw, 1000.0f, 1000.0f,
             0.7f, 0.7f, 2,
             Integral_Limit|OutputFilter|ErrorHandle//积分限幅,输出滤波,堵转监测
             |Trapezoid_Intergral|ChangingIntegrationRate//梯形积分,变速积分
             |Derivative_On_Measurement|DerivativeFilter);//微分先行,微分滤波器
    PID_Init(&MOTOR->DJI_6020_Yaw.PID_S, 6000.0f, 2000.0f,
             Gimbal_PID_S_Yaw, 1000.0f, 1000.0f,
             0.7f, 0.7f, 2,
             Integral_Limit|OutputFilter|ErrorHandle//积分限幅,输出滤波,堵转监测
             |Trapezoid_Intergral|ChangingIntegrationRate//梯形积分,变速积分
             |Derivative_On_Measurement|DerivativeFilter);//微分先行,微分滤波器

    return RUI_DF_READY;

}

uint8_t Gimbal_Task(CONTAL_Typedef *CONTAL,
    MOTOR_Typedef *MOTOR,
    IMU_Data_t *IMU)
{
    static uint8_t PID_INIT = RUI_DF_ERROR;
    static uint8_t AIM_INIT = RUI_DF_ERROR;

    //电机PID赋值
    if (PID_INIT != RUI_DF_READY)
    {
        PID_INIT = Gimbal_PID_Init(MOTOR);
        return RUI_DF_ERROR;
    }


    Feedforward_Calculate(&MOTOR->DJI_6020_Pitch.PID_F,
                          MOTOR->DJI_6020_Pitch.DATA.Aim);
    PID_Calculate(&MOTOR->DJI_6020_Pitch.PID_P,
                  IMU->pitch * 22.75555555555556f,
                  MOTOR->DJI_6020_Pitch.DATA.Aim);
    PID_Calculate(&MOTOR->DJI_6020_Pitch.PID_S,
                  IMU->gyro[1] * 100.0f,
                  MOTOR->DJI_6020_Pitch.PID_P.Output);

    /*Yaw计算*/
    /* 1. 期望角度限幅（防缠线/防过转） */
    VAL_LIMIT(MOTOR->DJI_6020_Yaw.DATA.Aim, GIMBAL_YAW_MIN, GIMBAL_YAW_MAX);

    Feedforward_Calculate(&MOTOR->DJI_6020_Yaw.PID_F,
                          MOTOR->DJI_6020_Yaw.DATA.Aim);
    PID_Calculate(&MOTOR->DJI_6020_Yaw.PID_P,
                  IMU->YawTotalAngle * 22.75555555555556f,
                  MOTOR->DJI_6020_Yaw.DATA.Aim);
    PID_Calculate(&MOTOR->DJI_6020_Yaw.PID_S,
                  IMU->gyro[2] * 100.0f,
                  MOTOR->DJI_6020_Yaw.PID_P.Output);

    /* 2. 位置环输出限幅（防止积分饱和时电流过大） */
    VAL_LIMIT(MOTOR->DJI_6020_Yaw.PID_P.Output, -2000, 2000);

    /*总输出计算*/
    float tmp_G[2];

    tmp_G[0] = MOTOR->DJI_6020_Pitch.PID_F.Output +
               MOTOR->DJI_6020_Pitch.PID_S.Output;

    tmp_G[1] = MOTOR->DJI_6020_Yaw.PID_F.Output +
               MOTOR->DJI_6020_Yaw.PID_S.Output;

    /*CAN发送*/
    DJI_Current_Ctrl(&hcan1,
                     0x1FF,
                     (int16_t)tmp_G[0],
                     (int16_t)tmp_G[1],
                     0,
                     0);
}
