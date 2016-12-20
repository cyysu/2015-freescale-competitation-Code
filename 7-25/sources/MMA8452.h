#ifndef MMA8452_H_
#define MMA8452_H_

#include "support_common.h" 



#define SlaveAddress_MMA8452    0x38
typedef unsigned char  BYTE;
typedef unsigned short WORD;
#define SCL_2 PORTA_PA5
#define SDA_2 PORTA_PA4
#define DR_SCL_2 DDRA_DDRA5
#define DR_SDA_2 DDRA_DDRA4



void conversion_MMA8452(unsigned int temp_data);
void Single_Write_MMA8452(unsigned char REG_Address,unsigned char REG_data);
void Multiple_read_MMA8452(void);
void Init_MMA8452(void);
int Read_MMA8452_Z(void);
void MMA8452_x(void);
void MMA8452_y(void);
void MMA8452_z(void);
void IIC_Init_2(void);
void IIC_Start_2(void);
void IIC_Stop_2(void);
void IIC_SendACK_2(BYTE ack);
void IIC_RecvACK_2(void);
void IIC_SendByte_2(BYTE dat);
BYTE IIC_RecvByte_2(void);
void Delay5us(void);
