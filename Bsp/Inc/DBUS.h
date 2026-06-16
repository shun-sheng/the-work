#ifndef _DBUS_H_
#define _DBUS_H_

#include "gpio.h"
#include "usart.h"
#include "string.h"

typedef struct
{
    int8_t ONLINE_JUDGE_TIME; // 在线检测时间
    //遥控
    struct
    {
        int16_t CH0_int16;
        int16_t CH1_int16;
        int16_t CH2_int16;
        int16_t CH3_int16;
        int16_t Dial_int16;
        uint8_t S1_u8;
        uint8_t S2_u8;
        int8_t Error_int8;
    } Remote;
    //鼠标
    struct
    {
        float X_Flt;
        float X_Filter; // 处理后使用的鼠标值
        float X_Max;    // 记录鼠标的最大值用来校准鼠标
        float Y_Flt;
        float Y_Filter; // 处理后使用的鼠标值
        float Y_Max;    // 记录鼠标的最大值用来校准鼠标
        float Z_Flt;
        float Z_Filter; // 处理后使用的鼠标值
        float Z_Max;    // 记录鼠标的最大值用来校准鼠标
        uint8_t R_State : 4;
        uint8_t L_State : 4;
        uint8_t R_PressTime;
        uint8_t L_PressTime;
    } Mouse;
    //键盘
    struct
    {
        uint8_t W : 4;
        uint8_t S : 4;
        uint8_t A : 4;
        uint8_t D : 4;
        uint8_t Shift : 4;
        uint8_t Ctrl : 4;
        uint8_t Q : 4;
        uint8_t E : 4;
        uint8_t R : 4;
        uint8_t F : 4;
        uint8_t G : 4;
        uint8_t Z : 4;
        uint8_t X : 4;
        uint8_t C : 4;
        uint8_t V : 4;
        uint8_t B : 4;
        uint8_t W_PressTime;
        uint8_t S_PressTime;
        uint8_t A_PressTime;
        uint8_t D_PressTime;
        uint8_t Shift_PreeNumber : 1;
        uint8_t Ctrl_PreeNumber : 1;
        uint8_t Q_PreeNumber : 1;
        uint8_t E_PreeNumber : 1;
        uint8_t R_PreeNumber : 1;
        uint8_t F_PreeNumber : 1;
        uint8_t G_PreeNumber : 1;
        uint8_t Z_PreeNumber : 1;
        uint8_t X_PreeNumber : 1;
        uint8_t C_PreeNumber : 1;
        uint8_t V_PreeNumber : 1;
        uint8_t B_PreeNumber : 1;
    } KeyBoard;
    uint8_t DBUS_ONLINE_JUDGE_TIME;
}DBUS_Typedef;


typedef union  // 使用共用体整合数据
{
    struct
    {
// 遥控数据
        uint64_t CH0 : 11;
        uint64_t CH1 : 11;
        uint64_t CH2 : 11;
        uint64_t CH3 : 11;
        uint64_t S1 : 2;
        uint64_t S2 : 2;
        // 鼠标数据
        int64_t Mouse_X : 16;
        int64_t Mouse_Y : 16;
        int64_t Mouse_Z : 16;
        int64_t Mouse_R : 8;
        int64_t Mouse_L : 8;
        // 键盘数据
        uint64_t KeyBoard_W : 1;
        uint64_t KeyBoard_S : 1;
        uint64_t KeyBoard_A : 1;
        uint64_t KeyBoard_D : 1;
        uint64_t KeyBoard_Shift : 1;
        uint64_t KeyBoard_Ctrl : 1;
        uint64_t KeyBoard_Q : 1;
        uint64_t KeyBoard_E : 1;
        uint64_t KeyBoard_R : 1;
        uint64_t KeyBoard_F : 1;
        uint64_t KeyBoard_G : 1;
        uint64_t KeyBoard_Z : 1;
        uint64_t KeyBoard_X : 1;
        uint64_t KeyBoard_C : 1;
        uint64_t KeyBoard_V : 1;
        uint64_t KeyBoard_B : 1;
        // 遥控滑轮
        uint64_t Direction : 11;
        uint64_t : 0;
    } DataNeaten;
    // 接收到的数组
    uint8_t  GetData[19];
}DBUS_UNION_Typdef;


void DBUS_Resolved(uint8_t* Data, DBUS_Typedef *DBUS); 
#endif