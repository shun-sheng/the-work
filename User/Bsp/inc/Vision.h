#ifndef _VISION_H_
#define _VISION_H_

#include "MY_Define.h"

uint8_t VISION_F_Cal(uint8_t *RxData, uint8_t type,TYPEDEF_VISION *VISION_DATA);
int ControltoVision(union RUI_U_VISION_SEND*  Send_t , uint8_t *buff, uint8_t type,User_Data_T *users,VT13_Typedef *VT13_DBUS,IMU_Data_t *IMU_Data,TYPEDEF_VISION *VISION_V_DATA,MOTOR_Typedef *ALL_MOTOR,uint8_t bspeed);
void VisionSendInit(union RUI_U_VISION_SEND*  Send_t,TYPEDEF_VISION *VISION_DATA,User_Data_T*User_Data_aaa,VT13_Typedef *DBUS_sss,IMU_Data_t *IMU_Data,MOTOR_Typedef*Motor_t,uint8_t bspeed);
void VISION_F_Monitor(TYPEDEF_VISION *VISION_V_DATA);
extern void TOP_T_Cal();
extern void TOP_T_Monitor();
void TOP_T_Cal_T();

#endif
