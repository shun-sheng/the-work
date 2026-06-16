#include "DJI_Motor.h"

void CAN_RX_DJI6020_DATA(DJI_MOTOR_DATA_Typedef* DATA , uint8_t* can_data)
{
		DATA->Angle_last = DATA->Angle_now;

    DATA->Angle_now = (int16_t) (((can_data[0] << 8) | can_data[1]) & 0xFFFF);

    DATA->Speed_last = DATA->Speed_now;

    DATA->Speed_now = (int16_t) (((can_data[2] << 8) | can_data[3]) & 0xFFFF);

    DATA->current   = (int16_t) (((can_data[4] << 8) | can_data[5]) & 0xFFFF);

    DATA->temperature = can_data[6];



    if (DATA->Angle_now - DATA->Angle_last < -4000)
    {
        DATA->Laps++;
    }
    else if (DATA->Angle_now - DATA->Angle_last > 4000)
    {
        DATA->Laps--;
    }

    if ((DATA->Laps > 32500) | (DATA->Laps < -32500))
    {
        DATA->Laps = 0;
        DATA->Aim  = DATA->Angle_now;
    }

    //DATA->ONLINE_JUDGE_TIME = RUI_DF_MOTOR_OFFLINE_TIME;

    DATA->Angle_Infinite = (int32_t) ((DATA->Laps << 13)+ DATA->Angle_now);
}

void CAN_RX_DJI3508_DATA(DJI_MOTOR_DATA_Typedef* DATA , uint8_t* can_data)
{
		DATA->Angle_last = DATA->Angle_now;

    DATA->Angle_now = (int16_t) (((can_data[0] << 8) | can_data[1]) & 0xFFFF);

    DATA->Speed_last = DATA->Speed_now;

    DATA->Speed_now = (int16_t) (((can_data[2] << 8) | can_data[3]) & 0xFFFF);

    DATA->current   = (int16_t) (((can_data[4] << 8) | can_data[5]) & 0xFFFF);

    DATA->temperature = can_data[6];



    if (DATA->Angle_now - DATA->Angle_last < -4000)
    {
        DATA->Laps++;
    }
    else if (DATA->Angle_now - DATA->Angle_last > 4000)
    {
        DATA->Laps--;
    }

    if ((DATA->Laps > 32500) | (DATA->Laps < -32500))
    {
        DATA->Laps = 0;
        DATA->Aim  = DATA->Angle_now;
    }

   // DATA->ONLINE_JUDGE_TIME = RUI_DF_MOTOR_OFFLINE_TIME;

    DATA->Angle_Infinite = (int32_t) ((DATA->Laps << 13)+ DATA->Angle_now);
}

void CAN_RX_DM4310_DATA(DJI_MOTOR_DATA_Typedef* DATA , uint8_t* can_data)
{
	
}

void DJI_Current_Ctrl(hcan_t* hcan, uint16_t stdid, int16_t num1, int16_t num2, int16_t num3, int16_t num4)
{
	uint8_t Data[8]={0};
	Data[0]=(num1>>8);
	Data[1]=num1;
	Data[2]=(num2>>8);
	Data[3]=num2;
	Data[4]=(num3>>8);
	Data[5]=num3;
	Data[6]=(num4>>8);
	Data[7]=num4;
	
	
}