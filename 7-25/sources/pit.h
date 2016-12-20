#ifndef PIT_H_
#define PIT_H_
#include <stdio.h>
#include "support_common.h" 
void PIT0_init(void);
void delayms(int ms);
void PIT1_init(void);
//void PIT1_start();
//void PIT1_stop(void);
void EPORT_init(void);
#endif