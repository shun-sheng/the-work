
#ifndef PID_TEMP_H
#define PID_TEMP_H
#include  "MY_Define.h"

extern void PID_init(pid_type_def *pid, uint8_t mode, const float PID[3], float max_out, float max_iout);
extern float PID_calc(pid_type_def *pid, float ref, float set);
extern void PID_clear(pid_type_def *pid);

#endif
