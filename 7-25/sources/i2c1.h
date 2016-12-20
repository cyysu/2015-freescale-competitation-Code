#ifndef _I2C1_H_
#define _I2C1_H_

void init_i2c1();
void i2c_start1();
unsigned char i2c_send_byte1(unsigned char c);
unsigned char i2c_recv_byte1(unsigned char ack);
void i2c_stop1();
void i2c_restart1();

#endif