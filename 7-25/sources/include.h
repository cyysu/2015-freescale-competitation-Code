#include "support_common.h" 
#include <stdio.h>
#include "uart.h"
#include "I2C.h"
#include  "l3g4200d.h"
#include "adc.h"
#include "pit.h"
#include "gpio.h"
#include "pwm.h"
#include "gpt.h"
#include "lanzhou.h"
#include "keyboard.h"
#include "ccd.h"
#include "ccd2.h"
#include "DMA.H"
#include "pid.h"
void funcStopCar(void);
void protectCar();
void AngleCalculate(void);
void AngleControl(void);
void Serial_dis(void);
void AngleControlOutput(void); 
void DMATimerGet(void);
void SpeedControl(void); 
void SpeedControlOutput(void);
void DirectionControl();
void DirectionControlOutput(void);
__declspec(interrupt:0) void PIT0_handler(void);
__declspec(interrupt:0) void PIT1_handler(void);
__declspec(interrupt:0) void EPORT_irq1_handler(void);
__declspec(interrupt:0) void EPORT_irq3_handler(void);
void B_key();
void SetMotorVoltage(float fLeftVoltage, float fRightVoltage);
void MotorOut(void);
void MoterOutput(void); 
void ZHANG_DEAL();
/*********²âÊÔº¯Êý*********/ 
void printf_fun(int16 var);
void Z_check();
void P_check();
void together();
#define EnableInterrupts asm { move.w SR,D0; andi.l #0xF8FF,D0; move.w D0,SR;  }
