#ifndef __CAN_BSP_H
#define __CAN_BSP_H
#include "can.h"


typedef CAN_HandleTypeDef hcan_t;

void CAN_Filter_Init(void);

//π≤”√ÃÂ
void canx_send_data(CAN_HandleTypeDef* _hcan , uint16_t stdid , uint8_t* Data);
#endif