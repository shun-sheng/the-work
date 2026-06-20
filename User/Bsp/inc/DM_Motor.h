#ifndef __DM_MOTOR_H
#define __DM_MOTOR_H


#include  "MY_Define.h"


float uint_to_float(int x_int, float x_min, float x_max, int bits);
void dm4310_fbdata(DM_MOTOR_Typdef *motor, uint8_t *rx_data);
void motor_mode(hcan_t* hcan, uint16_t motor_id, uint16_t mode_id, DMMotor_Mode_e what);
void mit_ctrl(hcan_t* hcan, uint16_t motor_id, float pos, float vel,float kp, float kd, float torq);
void pos_speed_ctrl(hcan_t* hcan,uint16_t motor_id, float pos, float vel);
void speed_ctrl(hcan_t* hcan,uint16_t motor_id, float vel);
void DM_Motor_Send(hcan_t* hcan, uint16_t id, float m1_cur, float m2_cur, float m3_cur, float m4_cur);
void dm4310_RXdata(DM_MOTOR_Typdef *motor, uint8_t *rx_data); //一拖四模式下
int16_t OneFilter1(int16_t last, int16_t now, float thresholdValue);
void dm_motor_init(void);
void pos_ctrl(hcan_t* hcan,uint16_t motor_id, float pos, float vel);
void RUI_F_HEAD_MOTOR_CLEAR_DM(DM_MOTOR_Typdef* MOTOR , uint8_t mode);
#endif
