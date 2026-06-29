#ifndef __BOARD_TO_BOARD_H_
#define ___BOARD_TO_BOARD_H_

#include "MY_Define.h"
void Board_to_Board_Receive(board_Data_t *receive_data,uint16_t stdid,uint8_t *rx_data);
void Board_to_Board_Send(DBUS_Typedef *DBUS,board_Data_t *send_data,IMU_Data_t IMU,float vw,float Yaw_rad,float Yaw_degree);
#endif