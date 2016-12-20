#ifndef I2C2_H_
#define I2C2_H_


#include "support_common.h"
extern void I2C_delay(void);
extern void I2C1_init(uint8 addr);
extern uint8 I2C1_read(uint8 daddr,uint8 aaddr);
extern uint8 I2C1_read_06();
extern uint8 I2C1_read_05();
extern void I2C1_writel(uint8 aaddr,uint8 data);
extern float get_mm845x();
extern void mm845x_init();
extern float MMA_Kalman_lvbo(float duixiang);
#include "include.h"
extern int16 lss_CarAngle;
#endif 