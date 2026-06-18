#ifndef __CHASSIS_TASK_H
#define __CHASSIS_TASK_H
#include "MY_Define.h"
#include "DJI_Motor.h"
#include "DM_Motor.h"
#include "DBUS.h"
#include "MY_define.h"
#include "RUI_ROOT_INIT.h"
#include "Motors.h"
#include "Power_Ctrl.h"

/************************************************************小陀螺行进**************************************************************
 * 	@performance:	    //底盘控制模式与自旋参数
 ************************************************************万能分隔符**************************************************************/
#define CHASSIS_NORMAL_MODE 0       // 普通底盘模式
#define CHASSIS_SPIN_MODE   1       // 小陀螺自旋模式

#define CHASSIS_SPIN_SPEED_DEFAULT 180.0f   // 默认自旋速度 (degree/s)
#define CHASSIS_SPIN_DEADBAND      15       // 遥控死区值
#define CHASSIS_SPEED_SCALE_MAX    660.0f   // 遥控通道最大值

#define LimitMax(input, max) \
  {                          \
        if (input > max)     \
                {            \
        input = max;         \
        }                    \
        else if (input < -max)\
        {                    \
                input = -max;\
        }                    \
  }
#define radian_angle 57.3f

typedef struct
{
    float Wheel_Perimeter;    /* �ֵ��ܳ���mm��*/
    float Wheel_Track;        /* �־ࣨmm��*/
    float Wheel_Base;         /*��ࣨmm��*/
    float Rotate_x_offset;    /* ����ڵ������ĵ�x����תƫ����(mm) */
    float Rotate_y_offset;    /* ����ڵ������ĵ�y����תƫ����(mm) */
    float Deceleration_ratio; /*������ٱ�*/
    int Max_vx_speed;         /*���̵�x�������ٶ�(mm/s)*/
    int Max_vy_speed;         /*���̵�y�������ٶ�(mm/s)*/
    int Max_vr_speed;         /*���̵���ת������ٶ�(degree/s)*/
    int Max_wheel_ramp;       /*3508���ת��*/
    // ÿһ�����ӵ���ת����//����ת���ĵ����
    float raid_fr;         // ��ǰ
    float raid_fl;         // ��ǰ
    float raid_bl;         // ���
    float raid_br;         // �Һ�
    float Wheel_rpm_ratio; // �������ٶ�ת����תÿ����

    float MecanumOut[4];   // ���������

    // 小陀螺自旋控制
    uint8_t Spin_Flag;      // 小陀螺模式标志: 0-关闭, 1-开启
    float Spin_Speed;       // 自旋目标速度 (degree/s)
} Mecanum_typdef;

typedef struct
{
    float history[100];
    float sum;
    int count;
    int index;
    float speed;

}member;

typedef struct
{

    member rxs;
    member rys;
    member ros;

    member rxs1;
    member rys1;
    member ros1;

    member rx_2;
    member ry_2;
    member ro_2;

    member rx_2_;
    member ry_2_;
    member ro_2_;

    member ds1_;
    member ds2_;
    member ds3_;
    member ds4_;

    member DirAngle1_;
    member DirAngle2_;
    member DirAngle3_;
    member DirAngle4_;

    member DirAngle1_1;
    member DirAngle2_1;
    member DirAngle3_1;
    member DirAngle4_1;
}Average;

void CHhassiswheel_PID_Init(MOTOR_Typedef *ALL_MOTOR,Average *ALL_Average_Speed);
void Chassis_MecanumInit(void);
void Chassis_MecanumResolve(float Vx, float Vy, float Vr, float Angle);
void Chassis_SpinInit(void);
void Chassis_ControlTask(void);

#endif
