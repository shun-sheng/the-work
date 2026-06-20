#ifndef __POWER_CTRL_H
#define __POWER_CTRL_H

#include "MY_Define.h"

void Power_control_init(model_t *model);
uint8_t chassis_power_control(CONTAL_Typedef *RUI_V_CONTAL_V,
                           User_Data_T *usr_data,
                           model_t *model,
                           CAP_RXDATA *CAP_GET,
                           MOTOR_Typedef *MOTOR);

#endif
