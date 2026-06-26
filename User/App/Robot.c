#include "Robot.h"
float monitor_X;
float monitor_Y;
float monitor_W;
float yaw_TD;
float pitch_TD;
static float count=0.0f;
float VISION_connect;
void RobotTask(uint8_t mode,
               DBUS_Typedef *DBUS,
               CONTAL_Typedef *CONTAL,
               User_Data_T *User_data,
               CAPDATE_TYPDEF *CAP_DATA,
               TYPEDEF_VISION *Vision/* 普通视觉*/
							/*	VisionRxDataUnion *Vision 加预测视觉*/,
               RUI_ROOT_STATUS_Typedef *Root,
               MOTOR_Typedef *MOTOR,
               IMU_Data_t *IMU_Data,
							 TD_t *TDDD,
							VT13_Typedef* VT13_DBUS)
{
    switch (mode) {

        case 1://底盘
        {
            static float SLOW_START=0.0f;
            static float FIX_ANGLE=0.0f;
            static float FOLLOW_PREDICT=0.0f;
            float MAX_POWER;

            CONTAL->BOTTOM.VX=(float)DBUS->Remote.CH0*0.6;
            CONTAL->BOTTOM.VY=(float)DBUS->Remote.CH1*0.6;
            CONTAL->BOTTOM.VW=(float)DBUS->Remote.CH2*0.6;

            if (CONTAL->BOTTOM.VX!=0.0f || CONTAL->BOTTOM.VY!=0.0f||CONTAL->BOTTOM.VW!=0.0f) {
                SLOW_START+=0.002f;
                float SLOW_START_MAX=RUI_F_CHASSIS_GET_MAX_TARGET(MAX_POWER);
                if (SLOW_START>SLOW_START_MAX)
                {
                    SLOW_START=SLOW_START_MAX;

                }
            }
            else
                {
                    SLOW_START=0.0;

                }

            CONTAL->BOTTOM.VX*=(1-VAL_LIMIT(0,2750,abs((FIX_ANGLE))/ 2750.0f));
            CONTAL->BOTTOM.VY*=(1-VAL_LIMIT(0,2750,abs((FIX_ANGLE))/ 2750.0f));

            CONTAL->BOTTOM.VX *= SLOW_START;
            CONTAL->BOTTOM.VY *= SLOW_START;
            CONTAL->BOTTOM.VW *= SLOW_START;

            if (DBUS->Remote.S1)
            {
               CONTAL->BOTTOM.VW*=0.4;
            }
            if (CONTAL->BOTTOM.VW!=0||Root->RM_DBUS==RUI_DF_OFFLINE)
            {
                FIX_ANGLE=0;
            }
            else
            {
                float KP = 3.0f - (((float) DBUS->Remote.CH1 + RUI_F_MATH_Limit_float(660, -660, DBUS->Mouse.X_Flt)) / 220.0f );
                VAL_LIMIT(KP,3.0f,5.0f);
                //PID
                FIX_ANGLE = RUI_F_CHASSIS_PID(CONTAL->CG.RELATIVE_ANGLE, KP, 0.00001f, 0.05f);
                //FFC
                RUI_V_FOLLOW_PREDICT = (float) ( DBUS->Remote.CH2 << 2 ) + VAL_LIMIT(DBUS->Mouse.X_Flt * 12, -660,660 );

            }

            /*麦轮解算*/
            Chassis_ControlTask();
        } break;

        case 2://云台
        {
            CONTAL->HEAD.Pitch=(float)DBUS->Remote.CH3*0.3;
            CONTAL->HEAD.Yaw=(float)DBUS->Remote.CH2*0.3;
            VAL_LIMIT(CONTAL->HEAD.Pitch,CONTAL->HEAD.Pitch_MIN,CONTAL->HEAD.Pitch_MAX);
           // VAL_LIMIT(CONTAL->HEAD.Yaw,CONTAL->HEAD.)
            Gimbal_Task(&RUI_V_CONTAL,&ALL_MOTOR,&IMU_Data);


        } break;

        case 3://电容
        {

        } break;

        case 4://发射
        {
					
        } break;
    }
}

/************************************************************万能分隔符**************************************************************
 * 	@author:			//瑞
 *	@performance:	    //
 *	@parameter:		    //
 *	@time:				//24-2-25 下午1:24
 *	@ReadMe:			//获取摩擦轮的目标值
 ************************************************************万能分隔符**************************************************************/
float Shoot_Speed_P(float Kp, float measure, float ref, float OUT_Lim)
{
    float error = ref - measure;
    /*比例输出*/
    float ALL_Out = error * Kp;
    /*总输出限幅*/
    ALL_Out = MATH_Limit_float(OUT_Lim, -OUT_Lim, ALL_Out);

    return ALL_Out;
}

float RUI_F_GET_FIRE_WIPE_SPEED(CONTAL_Typedef *CONTAL, DBUS_Typedef *DBUS, User_Data_T *User_data, RUI_ROOT_STATUS_Typedef *Root)
{
    static uint8_t LOCK = 0, MOD = 0, KEYBOARD_LOCK = 0, JUDGE_LOCK = 0;
    static float AIM = 0.0f, TEMP = 0.0f, SPEED_NOW = 0.0f, SPEED_LAST = 0.0f;
    MOD = DBUS->Remote.S2-1 | DBUS->Mouse.L_State | LOCK;
    //停止
    if (MOD == 0 || DBUS->Remote.S2-1 == 1 || Root->RM_DBUS == RUI_DF_OFFLINE)
    {
        AIM = 0.0f;//0.0
        LOCK = 0;
    } else
    {
        LOCK = 1;
        SPEED_LAST = SPEED_NOW;
        SPEED_NOW = User_data->shoot_data.initial_speed;

        /*弹速PID,仅限于修正摩擦轮发热所带来的弹速变化,优化为打一发弹算一次*/
        if (CONTAL->SHOOT_Bask.Shoot_Number - CONTAL->SHOOT_Bask.Shoot_Number_Last > 0)
        {
            if(MATH_ABS_float(SPEED_NOW - SPEED_LAST) > 0.1f)
                TEMP = Shoot_Speed_P(5.0f, SPEED_NOW, 29.5f, 50);
            CONTAL->SHOOT_Bask.Shoot_Number_Last = CONTAL->SHOOT_Bask.Shoot_Number;
        }

        AIM = (float) CONTAL->SHOOT.Shoot_Speed + TEMP;

    }
    return AIM;
}


/************************************************************万能分隔符**************************************************************
 * 	@author:			//瑞
 *	@performance:	    //
 *	@parameter:		    //
 *	@time:				//24-5-8 上午9:44
 *	@ReadMe:			//获取最大目标值
 ************************************************************万能分隔符**************************************************************/
float RUI_F_CHASSIS_GET_MAX_TARGET(float MAX_POWER)
{
    // 200w 0.04f
    // 100w 0.065f
    //  90w 0.065f
    //  80w 0.07f
    //  75w 0.08f
    //  70w 0.09f
    //  65w 0.1f
    //  60w 0.08f
    //  55w 0.06f
    //  50w 0.04f
    //  45w 0.02f
    if (MAX_POWER == 45)
    {
        return 0.03f * MAX_POWER;
    } else if (MAX_POWER == 50 || MAX_POWER == 200)
    {
        return 0.04f * MAX_POWER;
    } else if (MAX_POWER == 55)
    {
        return 0.06f * MAX_POWER;
    } else if (MAX_POWER == 60 || MAX_POWER == 75)
    {
        return 0.08f * MAX_POWER;
    } else if (MAX_POWER == 65)
    {
        return 0.1f * MAX_POWER;
    } else if (MAX_POWER == 70)
    {
        return 0.09f * MAX_POWER;
    } else if (MAX_POWER == 80)
    {
        return 0.07f * MAX_POWER;
    } else if (MAX_POWER == 90 || MAX_POWER == 100)
    {
        return 0.065f * MAX_POWER;
    } else
    {
        return 0.1f * MAX_POWER;
    }
}

/************************************************************万能分隔符**************************************************************
 * 	@author:			//瑞
 *	@performance:	    //底盘走直线单环PID
 *	@parameter:		    //
 *	@time:				//23-12-17 18:08
 *	@ReadMe:			//
 ************************************************************万能分隔符**************************************************************/
float RUI_F_CHASSIS_PID(int16_t RELATIVE_ANGLE, float KP, float KI, float KD)
{
    static float INTEGRAL = 0.0;
    float ERROR[2] = { 0 }, DERIVATIVE;
    ERROR[ 1 ] = (float) RELATIVE_ANGLE;
    //积分
    INTEGRAL += ( ERROR[ 1 ] * KI );
    INTEGRAL = MATH_Limit_float(100, -100, INTEGRAL);

    //微分
    DERIVATIVE = ( ERROR[ 1 ] - ERROR[ 0 ] ) * KD;

    ERROR[ 0 ] = ERROR[ 1 ];
    float OUTPUT = MATH_Limit_float(3000, -3000, ( KP * ERROR[ 1 ] + INTEGRAL + DERIVATIVE ));

    return OUTPUT;
}

