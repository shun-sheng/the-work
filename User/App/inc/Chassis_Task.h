#ifndef __CHASSIS_TASK_H
#define __CHASSIS_TASK_H
#include "MY_Define.h"
#include "Bottom.h"
typedef struct
{
    float vx;              // X方向速度目标（摇杆映射后，未旋转）
    float vy;              // Y方向速度目标
    float vr;              // 自转速度目标

    float vx_real;         // 实际 X 速度（小陀螺坐标旋转后）
    float vy_real;         // 实际 Y 速度
    float vr_real;         // 实际自转速度（遥控指令 + 跟随补偿）

    float vr_follow;       // 底盘跟随补偿角速度（PID 输出）
    PID_t vr_follow_PID_P; // 底盘跟随位置环 PID 实例

    float yaw_encoder;     // 当前 yaw 编码器值（积分估算）

    float wheel_rmp[4];    // 四个轮子的目标转速 RPM
} ChassisData_TypDef;
extern uint8_t chassis_mode;

void Chassiswheel_PID_Init(MOTOR_Typedef *ALL_MOTOR);
void Chassiswheel_PID_Calculate(void);
void Chassis_MecanumResolve(ChassisData_TypDef *remote_data,mecanumInit_typdef Mecanumdata ,DBUS_Typedef DBUS,uint8_t mode);
void Chassis_SpinInit(void);
void Chassis_ControlTask(void);
void GIMBAL_RAD_FORWARD(void);
void Chassis_Task();


extern ChassisData_TypDef chassis_data;  // 全局变量，定义在 Chassis_Task.c:3
#define SPINNING_MODE 1
#define FOLLOWING_MODE 0


#endif
