#include "Chassis_Task.h"

void CHhassiswheel_PID_Init(MOTOR_Typedef *ALL_MOTOR,Average *ALL_Average_Speed)
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

	ALL_Average_Speed->rxs.count=0;
	memset(ALL_Average_Speed->rxs.history,0,100);
	ALL_Average_Speed->rxs.index=0;
	ALL_Average_Speed->rxs.sum=0;

  ALL_Average_Speed->rys.count=0;
	memset(ALL_Average_Speed->rys.history,0,100);
	ALL_Average_Speed->rys.index=0;
	ALL_Average_Speed->rys.sum=0;

	ALL_Average_Speed->ros.count=0;
	memset(ALL_Average_Speed->ros.history,0,100);
	ALL_Average_Speed->ros.index=0;
	ALL_Average_Speed->ros.sum=0;

	ALL_Average_Speed->rxs1.count=0;
	memset(ALL_Average_Speed->rxs1.history,0,100);
	ALL_Average_Speed->rxs1.index=0;
	ALL_Average_Speed->rxs1.sum=0;

  ALL_Average_Speed->rys1.count=0;
	memset(ALL_Average_Speed->rys1.history,0,100);
	ALL_Average_Speed->rys1.index=0;
	ALL_Average_Speed->rys1.sum=0;

	ALL_Average_Speed->ros1.count=0;
	memset(ALL_Average_Speed->ros1.history,0,100);
	ALL_Average_Speed->ros1.index=0;
	ALL_Average_Speed->ros1.sum=0;

	ALL_Average_Speed->rx_2.count=0;
	memset(ALL_Average_Speed->rx_2.history,0,100);
	ALL_Average_Speed->rx_2.index=0;
	ALL_Average_Speed->rx_2.sum=0;

  ALL_Average_Speed->ry_2.count=0;
	memset(ALL_Average_Speed->ry_2.history,0,100);
	ALL_Average_Speed->ry_2.index=0;
	ALL_Average_Speed->ry_2.sum=0;

	ALL_Average_Speed->ro_2.count=0;
	memset(ALL_Average_Speed->ro_2.history,0,100);
	ALL_Average_Speed->ro_2.index=0;
	ALL_Average_Speed->ro_2.sum=0;

	ALL_Average_Speed->rx_2_.count=0;
	memset(ALL_Average_Speed->rx_2_.history,0,100);
	ALL_Average_Speed->rx_2_.index=0;
	ALL_Average_Speed->rx_2_.sum=0;

  ALL_Average_Speed->ry_2_.count=0;
	memset(ALL_Average_Speed->ry_2_.history,0,100);
	ALL_Average_Speed->ry_2_.index=0;
	ALL_Average_Speed->ry_2_.sum=0;

	ALL_Average_Speed->ro_2_.count=0;
	memset(ALL_Average_Speed->ro_2_.history,0,100);
	ALL_Average_Speed->ro_2_.index=0;
	ALL_Average_Speed->ro_2_.sum=0;

}

void Chassis_MecanumInit(void)
{
    MecanumData.Wheel_Perimeter = 480;
    MecanumData.Wheel_Track = 505;
    MecanumData.Wheel_Base = 505;
    MecanumData.Rotate_x_offset = 0;
    MecanumData.Rotate_y_offset = 0;
    MecanumData.Deceleration_ratio = 1.0f / 19.0f;
    MecanumData.Max_vx_speed = 5000;
    MecanumData.Max_vy_speed = 5000;
    MecanumData.Max_vr_speed = 500;
    MecanumData.Max_wheel_ramp = 7500;

    //������ת����
    MecanumData.raid_fr = ((MecanumData.Wheel_Track + MecanumData.Wheel_Base) / 2.0f
      - MecanumData.Rotate_x_offset + MecanumData.Rotate_y_offset) / radian_angle;

    MecanumData.raid_fl = ((MecanumData.Wheel_Track + MecanumData.Wheel_Base) / 2.0f
      - MecanumData.Rotate_x_offset - MecanumData.Rotate_y_offset) / radian_angle;

    MecanumData.raid_bl = ((MecanumData.Wheel_Track + MecanumData.Wheel_Base) / 2.0f
      + MecanumData.Rotate_x_offset - MecanumData.Rotate_y_offset) / radian_angle;

    MecanumData.raid_br = ((MecanumData.Wheel_Track + MecanumData.Wheel_Base) / 2.0f
      + MecanumData.Rotate_x_offset + MecanumData.Rotate_y_offset) / radian_angle;

    //������ת����תÿ���� 60/(���ٱ�*�ܳ�)
    MecanumData.Wheel_rpm_ratio = 60.0f / (MecanumData.Wheel_Perimeter * MecanumData.Deceleration_ratio);
}

void Chassis_MecanumResolve(float Vx, float Vy, float Vr, float Angle)
{
  float tempMax = 0;
  float AngleSin = 0;
  float AngleCos = 0;

  float angleSin = 0.0f, angleCos = 0.0f;
  float Vxout=0,Vyout=0;


  angleSin = sinf(Angle);
  angleCos = cosf(Angle);

  Vxout = -Vy * angleSin + Vx * angleCos;
  Vyout = Vy * angleCos + Vx * angleSin;

  LimitMax(Vxout, MecanumData.Max_vx_speed);
  LimitMax(Vyout, MecanumData.Max_vy_speed);
  LimitMax(Vr, MecanumData.Max_vr_speed);

  MecanumData.MecanumOut[0] = (Vxout + Vyout - Vr * MecanumData.raid_fl) * MecanumData.Wheel_rpm_ratio;
  MecanumData.MecanumOut[1] = (-Vxout + Vyout - Vr * MecanumData.raid_fr) * MecanumData.Wheel_rpm_ratio;
  MecanumData.MecanumOut[2] = (-Vxout - Vyout - Vr * MecanumData.raid_br) * MecanumData.Wheel_rpm_ratio;
  MecanumData.MecanumOut[3] = (Vxout - Vyout - Vr * MecanumData.raid_bl) * MecanumData.Wheel_rpm_ratio;

  for (uint8_t i = 0; i < 4; i++)
  {
    if (abs(MecanumData.MecanumOut[i]) >= tempMax)
    {
      tempMax = abs(MecanumData.MecanumOut[i]);
    }
  }

  if (tempMax > MecanumData.Max_wheel_ramp)
  {
    float rate = MecanumData.Max_wheel_ramp / tempMax;
    for (uint8_t i = 0; i < 4; i++)
    {
      MecanumData.MecanumOut[i] *= rate;
    }
  }
}


// void Chassis_SpinInit(void)
// {
//     MecanumData.Spin_Flag = CHASSIS_NORMAL_MODE;
//     MecanumData.Spin_Speed = CHASSIS_SPIN_SPEED_DEFAULT;
// }


void Chassis_ControlTask(void)
{
    float Vx = 0.0f, Vy = 0.0f, Vr = 0.0f;
    float Angle = 0.0f;
    float speed_scale = 0.0f;
    int16_t current[4] = {0};
    int8_t vx_dir = 0, vy_dir = 0;


    // /* ----- 遥控模式 ----- */
    // /* CH3: 左摇杆左右 → Vx (平移) */
    // if (abs(DBUS.Remote.CH3) > CHASSIS_SPIN_DEADBAND)
    // {
    //     speed_scale = (float)DBUS.Remote.CH3 / CHASSIS_SPEED_SCALE_MAX;
    //     Vx = speed_scale * (float)MecanumData.Max_vx_speed;
    // }
    // /* CH2: 左摇杆前后 → Vy (前进) */
    // if (abs(DBUS.Remote.CH2) > CHASSIS_SPIN_DEADBAND)
    // {
    //     speed_scale = (float)DBUS.Remote.CH2 / CHASSIS_SPEED_SCALE_MAX;
    //     Vy = speed_scale * (float)MecanumData.Max_vy_speed;
    // }
    // /* CH0: 右摇杆左右 → Vr (旋转) */
    // if (abs(DBUS.Remote.CH0) > CHASSIS_SPIN_DEADBAND)
    // {
    //     speed_scale = (float)DBUS.Remote.CH0 / CHASSIS_SPEED_SCALE_MAX;
    //     Vr = speed_scale * (float)MecanumData.Max_vr_speed;
    // }


    // /* ============================================================
    //    2. 小陀螺自旋模式
    //       开启后Vr固定为自旋速度
    //       使用IMU航向角做场定向控制(矢量定心)
    //    ============================================================ */
    // MecanumData.Spin_Flag = DBUS.Remote.S2;
    //
    // if (MecanumData.Spin_Flag == CHASSIS_SPIN_MODE)
    // {
    //     Vr = MecanumData.Spin_Speed;
    //     /* IMU航向角: 度→弧度, 用于场定向控制 */
    //     Angle = IMU_Data.yaw / radian_angle;
    // }

    /* ============================================================
       3. 麦轮逆解算 (角度用于场定向旋转Vx/Vy)
       ============================================================ */
    Chassis_MecanumResolve(Vx, Vy, Vr, Angle);

    /* ============================================================
       4. 四轮速度环PID (目标→MecanumOut, 反馈→Speed_now)
       ============================================================ */
    current[MOTOR_D_CHASSIS_1] = (int16_t)PID_Calculate(
        &ALL_MOTOR.DJI_3508_Chassis_1.PID_S,
        (float)ALL_MOTOR.DJI_3508_Chassis_1.DATA.Speed_now,
        MecanumData.MecanumOut[MOTOR_D_CHASSIS_1]);

    current[MOTOR_D_CHASSIS_2] = (int16_t)PID_Calculate(
        &ALL_MOTOR.DJI_3508_Chassis_2.PID_S,
        (float)ALL_MOTOR.DJI_3508_Chassis_2.DATA.Speed_now,
        MecanumData.MecanumOut[MOTOR_D_CHASSIS_2]);

    current[MOTOR_D_CHASSIS_3] = (int16_t)PID_Calculate(
        &ALL_MOTOR.DJI_3508_Chassis_3.PID_S,
        (float)ALL_MOTOR.DJI_3508_Chassis_3.DATA.Speed_now,
        MecanumData.MecanumOut[MOTOR_D_CHASSIS_3]);

    current[MOTOR_D_CHASSIS_4] = (int16_t)PID_Calculate(
        &ALL_MOTOR.DJI_3508_Chassis_4.PID_S,
        (float)ALL_MOTOR.DJI_3508_Chassis_4.DATA.Speed_now,
        MecanumData.MecanumOut[MOTOR_D_CHASSIS_4]);

    /* ============================================================
       5. CAN发送电流 (CAN1, stdid=0x200, 四路电流)
       ============================================================ */
    DJI_Current_Ctrl(&hcan1, 0x200,
                     current[MOTOR_D_CHASSIS_1],
                     current[MOTOR_D_CHASSIS_2],
                     current[MOTOR_D_CHASSIS_3],
                     current[MOTOR_D_CHASSIS_4]);
}