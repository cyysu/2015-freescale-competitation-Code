#ifndef PWM_H_
#define PWM_H_
#include "support_common.h" 
void PWM_init(void);
void PWM_left(int16 x);
void PWM_right(int16 x);
/**
void PWM_leftback(int16 x);
void PWM_rightback(int16 x);
void PWM_leftfront(int16 x);
void PWM_rightfront(int16 x);
**/
#endif