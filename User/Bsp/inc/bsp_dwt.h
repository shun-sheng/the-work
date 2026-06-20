#ifndef _BSP_DWT_H
#define _BSP_DWT_H

#include "MY_Define.h"

void DWT_Init(uint32_t CPU_Freq_mHz);
float DWT_GetDeltaT(uint32_t *cnt_last);
double DWT_GetDeltaT64(uint32_t *cnt_last);
float DWT_GetTimeline_s(void);
float DWT_GetTimeline_ms(void);
uint64_t DWT_GetTimeline_us(void);
void DWT_Delay(float Delay);
void DWT_SysTimeUpdate(void);
void DWT_DelayUs(uint32_t us);
void DWT_Delay_us(float Delay);

#endif /* BSP_DWT_H_ */
