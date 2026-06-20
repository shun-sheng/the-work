#ifndef __POWER_CAP_H
#define __POWER_CAP_H

#include "MY_Define.h"

void Power_CAP_CAN_RX(CAPDATE_TYPDEF *CAP_DATA, uint8_t *DATA);
void Power_CAP_CAN_TX(hcan_t* hcan,uint16_t cap_id, CAP_SETDATA *CAP_SET, User_Data_T *User_data);

#endif
