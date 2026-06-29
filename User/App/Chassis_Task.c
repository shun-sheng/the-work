#include "Chassis_Task.h"
#include "controller.h"
#include "can.h"
#include "DJI_Motor.h"
ChassisData_TypDef chassis_data = {0};
Mecanum_typdef Mecanum_Chassis;
PID_t Vw_Follow_PID;
uint8_t chassis_mode=0;
void Chassiswheel_PID_Init(MOTOR_Typedef *ALL_MOTOR)
{

	float PID_S_wheel[3] = CHASSIS_PID_S;

	PID_Init(&ALL_MOTOR->DJI_3508_Chassis_1.PID_S, 6000.0f, 2000.0f,
              PID_S_wheel, 1000.0f, 1000.0f,
             0.7f, 0.7f, 2,
             Integral_Limit|OutputFilter|ErrorHandle//锟斤拷锟斤拷锟睫凤拷,锟斤拷锟斤拷瞬锟�,锟斤拷转锟斤拷锟�
             |Trapezoid_Intergral|ChangingIntegrationRate//锟斤拷锟轿伙拷锟斤拷,锟斤拷锟劫伙拷锟斤拷
             |Derivative_On_Measurement|DerivativeFilter);//微锟斤拷锟斤拷锟斤拷,微锟斤拷锟剿诧拷锟斤拷

	PID_Init(&ALL_MOTOR->DJI_3508_Chassis_2.PID_S, 6000.0f, 2000.0f,
              PID_S_wheel, 1000.0, 1000.0f,
             0.7f, 0.7f, 2,
             Integral_Limit|OutputFilter|ErrorHandle//锟斤拷锟斤拷锟睫凤拷,锟斤拷锟斤拷瞬锟�,锟斤拷转锟斤拷锟�
             |Trapezoid_Intergral|ChangingIntegrationRate//锟斤拷锟轿伙拷锟斤拷,锟斤拷锟劫伙拷锟斤拷
             |Derivative_On_Measurement|DerivativeFilter);//微锟斤拷锟斤拷锟斤拷,微锟斤拷锟剿诧拷锟斤拷

	PID_Init(&ALL_MOTOR->DJI_3508_Chassis_3.PID_S, 6000.0f, 2000.0f,
              PID_S_wheel, 1000.0f, 1000.0f,
             0.7f, 0.7f, 2,
             Integral_Limit|OutputFilter|ErrorHandle//锟斤拷锟斤拷锟睫凤拷,锟斤拷锟斤拷瞬锟�,锟斤拷转锟斤拷锟�
             |Trapezoid_Intergral|ChangingIntegrationRate//锟斤拷锟轿伙拷锟斤拷,锟斤拷锟劫伙拷锟斤拷
             |Derivative_On_Measurement|DerivativeFilter);//微锟斤拷锟斤拷锟斤拷,微锟斤拷锟剿诧拷锟斤拷

	PID_Init(&ALL_MOTOR->DJI_3508_Chassis_4.PID_S, 6000.0f, 2000.0f,
              PID_S_wheel, 1000.0f, 1000.0f,
             0.7f, 0.7f, 2,
             Integral_Limit|OutputFilter|ErrorHandle//锟斤拷锟斤拷锟睫凤拷,锟斤拷锟斤拷瞬锟�,锟斤拷转锟斤拷锟�
             |Trapezoid_Intergral|ChangingIntegrationRate//锟斤拷锟轿伙拷锟斤拷,锟斤拷锟劫伙拷锟斤拷
             |Derivative_On_Measurement|DerivativeFilter);//微锟斤拷锟斤拷锟斤拷,微锟斤拷锟剿诧拷锟斤拷

	float Mecanum_PID_Follow[3]={0.1,0,0};
	PID_Init(&Vw_Follow_PID,16384,7000,Mecanum_PID_Follow,0.0f,0.0f,0.0f,0.0f,0.0f,Integral_Limit);
}

void Chassiswheel_PID_Calculate(void)
{
	PID_Calculate(
		&ALL_MOTOR.DJI_3508_Chassis_1.PID_S,
		(float)ALL_MOTOR.DJI_3508_Chassis_1.DATA.Speed_now,
		chassis_data.wheel_rmp[MOTOR_D_CHASSIS_1]);
	PID_Calculate(
		&ALL_MOTOR.DJI_3508_Chassis_2.PID_S,
		(float)ALL_MOTOR.DJI_3508_Chassis_2.DATA.Speed_now,
		chassis_data.wheel_rmp[MOTOR_D_CHASSIS_2]);
	PID_Calculate(
		&ALL_MOTOR.DJI_3508_Chassis_3.PID_S,
		(float)ALL_MOTOR.DJI_3508_Chassis_3.DATA.Speed_now,
		chassis_data.wheel_rmp[MOTOR_D_CHASSIS_3]);
	PID_Calculate(
		&ALL_MOTOR.DJI_3508_Chassis_4.PID_S,
		(float)ALL_MOTOR.DJI_3508_Chassis_4.DATA.Speed_now,
		chassis_data.wheel_rmp[MOTOR_D_CHASSIS_4]);


}

void GIMBAL_RAD_FORWARD(void)
{
	// GM6020 编码器直接读数 ,不需要积分推算
	int32_t encoder = ALL_MOTOR.DJI_6020_Yaw.DATA.Angle_Infinite;
	float degree    = (float)encoder / 8192.0f * 360.0f;
	float rad       = degree / 57.3f;

	chassis_data.yaw_encoder = encoder;  // 编码器值

}

void Following_VwCalculate(void)
{
	chassis_data.vr_follow=PID_Calculate(&chassis_data.vr_follow_PID_P,chassis_data.yaw_encoder,0);

}

void Chassis_MecanumResolve(ChassisData_TypDef *remote_data,mecanumInit_typdef Mecanumdata ,DBUS_Typedef DBUS,uint8_t mode)
{
    switch (mode)
    {
    	case(SPINNING_MODE):
    	{
    		remote_data->vx=DBUS.Remote.CH1*Mecanumdata.max_vx_speed / 660.0;
    		remote_data->vy=DBUS.Remote.CH0*Mecanumdata.max_vy_speed/660.0;
    		remote_data->vr=DBUS.Remote.CH3 * MecanumData.max_vw_speed / 660.0;

    		remote_data->vx_real=remote_data->vx*cosf(ALL_MOTOR.DJI_6020_Yaw.DATA.Angle_now)+
    			remote_data->vy*(-sin(ALL_MOTOR.DJI_6020_Yaw.DATA.Angle_now));
    		remote_data->vy_real=remote_data->vx*sinf(ALL_MOTOR.DJI_6020_Yaw.DATA.Angle_now)
    								+remote_data->vy*cosf(ALL_MOTOR.DJI_6020_Yaw.DATA.Angle_now);
    		remote_data->vr_real=remote_data->vr+remote_data->vr_follow;
    		break;
    	}
    		case(FOLLOWING_MODE):
    		{
    		remote_data->vx=DBUS.Remote.CH1*Mecanumdata.max_vx_speed / 660.0;
    		remote_data->vy=DBUS.Remote.CH0*Mecanumdata.max_vy_speed/660.0;
    		remote_data->vr=DBUS.Remote.CH3 * MecanumData.max_vw_speed / 660.0;

    		remote_data->vx_real=remote_data->vx*cosf(ALL_MOTOR.DJI_6020_Yaw.DATA.Angle_now)+
				remote_data->vy*(-sin(ALL_MOTOR.DJI_6020_Yaw.DATA.Angle_now));
    		remote_data->vy_real=remote_data->vx*sinf(ALL_MOTOR.DJI_6020_Yaw.DATA.Angle_now)
									+remote_data->vy*cosf(ALL_MOTOR.DJI_6020_Yaw.DATA.Angle_now);
    		remote_data->vr_real=0;

    		remote_data->vx_real=remote_data->vx*cosf(ALL_MOTOR.DJI_6020_Yaw.DATA.Angle_now)+remote_data->vy*(-sin(ALL_MOTOR.DJI_6020_Yaw.DATA.Angle_now));
    		remote_data->vy_real=remote_data->vx*sinf(ALL_MOTOR.DJI_6020_Yaw.DATA.Angle_now)
									+remote_data->vy*cosf(ALL_MOTOR.DJI_6020_Yaw.DATA.Angle_now);
    		remote_data->vr_real=remote_data->vr+remote_data->vr_follow;
    		break;
    		}
    		default:
    			break;
    }
}


void Chassis_Task()
{
	GIMBAL_RAD_FORWARD();
	Following_VwCalculate();
	Chassis_MecanumResolve(&chassis_data, MecanumData, DBUS, chassis_mode);
	MecanumResolve(chassis_data.wheel_rmp,chassis_data.vx_real,
	chassis_data.vy_real,chassis_data.vr_real,&MecanumData);
	Chassiswheel_PID_Calculate();
	DJI_Current_Ctrl(&hcan2,
						 0x200,
						 (int16_t)ALL_MOTOR.DJI_3508_Chassis_1.PID_S.Output,
						 (int16_t)ALL_MOTOR.DJI_3508_Chassis_2.PID_S.Output,
						 (int16_t)ALL_MOTOR.DJI_3508_Chassis_3.PID_S.Output,
						 (int16_t)ALL_MOTOR.DJI_3508_Chassis_4.PID_S.Output);

}
