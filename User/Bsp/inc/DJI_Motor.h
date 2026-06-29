
#ifndef __DJI_MOTOR_H
#define __DJI_MOTOR_H


#include "MY_Define.h"
#include "can_bsp.h"

void MOTOR_CAN_RX_3508RM(DJI_MOTOR_DATA_Typedef* DATA , uint8_t* can_data);
void MOTOR_CAN_RX_2006RM(DJI_MOTOR_DATA_Typedef* DATA , uint8_t* can_data);
void MOTOR_CAN_RX_6020RM(DJI_MOTOR_DATA_Typedef* DATA , uint8_t* can_data);
void HEAD_MOTOR_CLEAR(DJI_MOTOR_Typedef* MOTOR , uint8_t mode);
void DJI_Current_Ctrl(hcan_t* hcan, uint16_t stdid, int16_t num1, int16_t num2, int16_t num3, int16_t num4);

#endif
