#ifndef __CAN_BSP_H
#define __CAN_BSP_H

#include "MY_define.h"

void CAN_Filter_Init(void);
//共用体
void canx_send_data(CAN_HandleTypeDef* _hcan , uint16_t stdid , uint8_t* Data);

#endif
