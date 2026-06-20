#ifndef G4_FRAMEWORK_MAHONY_FILTER_H
#define G4_FRAMEWORK_MAHONY_FILTER_H

#include "MY_Define.h"

float invSqrt(float x);

extern struct MAHONY_FILTER_t mahony_filter;

void mahony_init(struct MAHONY_FILTER_t *f, float Kp, float Ki, float alpha,float dt);
void mahony_input(struct MAHONY_FILTER_t *mahony_filter, Axis3f gyro, Axis3f acc);
void mahony_update(struct MAHONY_FILTER_t *mahony_filter,
                   float gx, float gy, float gz,
                   float ax, float ay, float az,float dt);
void mahony_output(struct MAHONY_FILTER_t *mahony_filter);
void RotationMatrix_update(struct MAHONY_FILTER_t *mahony_filter);

#endif //G4_FRAMEWORK_MAHONY_FILTER_H