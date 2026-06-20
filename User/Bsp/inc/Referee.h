#ifndef __REFEREE_H
#define __REFEREE_H
#include "MY_Define.h"

void Referee_System_Frame_Update(uint8_t *Buff, uint16_t Size);
void Referee_Send_KeyMouse(custom_client_data_t *control_data);
void Referee_Send_Data(uint16_t cmd_id, uint8_t *p_data, uint16_t len);

#endif