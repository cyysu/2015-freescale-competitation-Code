#ifndef _L3G4200D_H_
#define _L3G4200D_H_
#include "support_common.h" 
#include "I2C.h"
//**********L3G4200D内部寄存器地址*********
#define WHO_AM_I 0x0F
#define CTRL_REG1 0x20
#define CTRL_REG2 0x21
#define CTRL_REG3 0x22
#define CTRL_REG4 0x23
#define CTRL_REG5 0x24
#define REFERENCE 0x25
#define OUT_TEMP 0x26
#define STATUS_REG 0x27
#define OUT_X_L 0x28
#define OUT_X_H 0x29
#define OUT_Y_L 0x2A
#define OUT_Y_H 0x2B
#define OUT_Z_L 0x2C
#define OUT_Z_H 0x2D
#define FIFO_CTRL_REG 0x2E
#define FIFO_SRC_REG 0x2F
#define INT1_CFG 0x30
#define INT1_SRC 0x31
#define INT1_TSH_XH 0x32
#define INT1_TSH_XL 0x33
#define INT1_TSH_YH 0x34
#define INT1_TSH_YL 0x35
#define INT1_TSH_ZH 0x36
#define INT1_TSH_ZL 0x37
#define INT1_DURATION 0x38
//****************************************
#define	SlaveAddress   0xD2	  //定义器件在IIC总线中的从地址,根据ALT  ADDRESS地址引脚不同修改
//-----------------------------------------------------------------------------------------
void InitL3G4200D();                //初始化L3G4200D
void  Single_WriteL3G4200D(uint8 REG_Address,uint8 REG_data);   //单个写入数据
uint8 Single_ReadL3G4200D(uint8 REG_Address);                   //单个读取内部寄存器数据
int16 cai_x();
int16 cai_y();
int16 cai_z();
void delay1(int us);


/***************加速度计部分函数**********************/
#define SlaveAddress_MMA8452    0x38

void conversion_MMA8452(unsigned int temp_data);
void Single_Write_MMA8452(unsigned char REG_Address,unsigned char REG_data);
void Multiple_read_MMA8452(void);
void Init_MMA8452(void);
int Read_MMA8452_Z(void);
int Read_MMA8452_X(void);
int Read_MMA8452_Y(void);

void MMA8452_x(void);
void MMA8452_y(void);
void MMA8452_z(void);
void Get_Image(void);//将陀螺仪和加速度计数据整合在一起
// void display_4200D (void);



#endif