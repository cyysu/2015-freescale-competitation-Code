#ifndef _I2C_H_
#define _I2C_H_


void init_i2c();
void i2c_start();
unsigned char i2c_send_byte(unsigned char c);
unsigned char i2c_recv_byte(unsigned char ack);
void i2c_stop();
void i2c_restart();

//////////////////数字加速度计/////////////////////

typedef unsigned char  BYTE;
typedef unsigned short WORD;

void IIC_Init_2(void);
void IIC_Start_2(void);
void IIC_Stop_2(void);
void IIC_RecvACK_2(void);
void IIC_SendByte_2(BYTE dat);
BYTE IIC_RecvByte_2(void);


void IIC_SendACK_2_NACK();
void IIC_SendACK_2_ACK();
void Delay5us(void);




#endif