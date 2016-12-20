#include "l3g4200d.h"
#include "I2C.h"


//*****************************************************************

//初始化L3G4200D，根据需要请参考pdf进行修改************************
void InitL3G4200D()
{
   Single_WriteL3G4200D(CTRL_REG1, 0xff);   //使能三个轴
   Single_WriteL3G4200D(CTRL_REG2, 0x00);   //
   Single_WriteL3G4200D(CTRL_REG3, 0x08);   //
   Single_WriteL3G4200D(CTRL_REG4, 0x10);  //+-500dps
   Single_WriteL3G4200D(CTRL_REG5, 0x00);
}

//单字节写入*******************************************

void Single_WriteL3G4200D(uint8 REG_Address,uint8 REG_data)
{
 i2c_start();                  //起始信号
 i2c_send_byte(SlaveAddress);   //发送设备地址+写信号
 i2c_send_byte(REG_Address);    //内部寄存器地址，请参考中文pdf22页 
 i2c_send_byte(REG_data);       //内部寄存器数据，请参考中文pdf22页 
 i2c_stop();                   //发送停止信号
}

//单字节读取*****************************************

uint8 Single_ReadL3G4200D(uint8 REG_Address)
{     
	uint8 REG_data;
  	i2c_start();                          //起始信号
  	i2c_send_byte (SlaveAddress);           //发送设备地址+写信号
  	i2c_send_byte (REG_Address);            //发送存储单元地址，从0开始	
  	i2c_restart();                          //起始信号
  	i2c_send_byte(SlaveAddress+1);         //发送设备地址+读信号
  	REG_data=i2c_recv_byte(0);              //读出寄存器数据   
  	i2c_stop();                           //停止信号
  	return REG_data; 
}
//***********************************************************************
int16 cai_x()
{ 
    int8 xi,xj;
    int16 temp_x;
    xi= Single_ReadL3G4200D(OUT_X_L);
    xj= Single_ReadL3G4200D(OUT_X_H); //读取X轴数据
    temp_x=(int)((xj<<8)+xi);       //合成数据   
    return temp_x;
}

int16 cai_y()
{ 
    int8 yi,yj;
    int16 temp_y;
    yi= Single_ReadL3G4200D(OUT_Y_L);
    yj= Single_ReadL3G4200D(OUT_Y_H); //读取Y轴数据

    temp_y=(yj<<8)+yi;       //合成数据   
    return temp_y;
}
int16 cai_z()
{ 
    int8 zi,zj;
    int16 temp_z;
    zi= Single_ReadL3G4200D(OUT_Z_L);
    zj= Single_ReadL3G4200D(OUT_Z_H); //读取Z轴数据
    temp_z=(zj<<8)+zi;       //合成数据   
    return temp_z;
}
void delay1(int us)
{
	int a1,b1;
	if(us<1) us=1;
	for(a1=0;a1<us;a1++)
	for(b1=0;b1<3;b1++)
	{
		
	}//约为1微秒
}


/*****************************************************/
/***************加速度计部分函数**********************/
/*****************************************************/
BYTE BUF_MMA8452[8];
int  dis_data_MMA_Z;
int  dis_data_MMA_X;
int  dis_data_MMA_Y;
//初始化MMA8452，根据需要请参考pdf进行修改************************
void Init_MMA8452()
{
   Single_Write_MMA8452(0x2A,0x01);   
   Single_Write_MMA8452(0x2B,0x02);  
//   Single_Write_MMA8452(0x2A,0x10);   
   Single_Write_MMA8452(0x0E,0x00);
//   Single_Write_MMA8452(0x0F,0x10);
}
void Single_Write_MMA8452(unsigned char REG_Address,unsigned char REG_data)
{
    IIC_Start_2();                  //起始信号
    IIC_SendByte_2(SlaveAddress_MMA8452);   //发送设备地址+写信号
    IIC_SendByte_2(REG_Address);    //内部寄存器地址
    IIC_SendByte_2(REG_data);       //内部寄存器数据
    IIC_Stop_2();                   //发送停止信号
}
/************************************************/
/***          只读出加速度计Z轴角度           ***/
/************************************************/
int Read_MMA8452_Z(void) 
{
    unsigned char i;
    int16 sum;
    int sign;
    IIC_Start_2();                          //起始信号
    IIC_SendByte_2(SlaveAddress_MMA8452);           //发送设备地址+写信号
    IIC_SendByte_2(0x05);                   //发送存储单元地址，从0x05开始	
    IIC_Start_2();                          //起始信号
    IIC_SendByte_2(SlaveAddress_MMA8452+1);         //发送设备地址+读信号
    for (i=0; i<2; i++)                      //连续读取6个地址数据，存储中BUF
    {
        BUF_MMA8452[i] = IIC_RecvByte_2();          //BUF[0]存储0x32地址中的数据
        if (i == 2)
        {
           IIC_SendACK_2_NACK();                //最后一个数据需要回NOACK
        }
        else
        {
           IIC_SendACK_2_ACK();                //回应ACK
        }
   }
   IIC_Stop_2();                          //停止信号
   Delay5us();
   sum=(BUF_MMA8452[0]<<8)+BUF_MMA8452[1];
   
   if(BUF_MMA8452[0] > 0x7F && BUF_MMA8452[0] < 0XFF)
   {   
       dis_data_MMA_Z   = -(~((sum>>4)+1)&0x0FFF);	
       return dis_data_MMA_Z;
   } 
   if(BUF_MMA8452[0] >= 0 && BUF_MMA8452[0] < 0X7F)
   {
   	  dis_data_MMA_Z   = (sum>>4)&0X0FFF;
   	  return dis_data_MMA_Z;
   }

 /*  dis_data_MMA_Z=(BUF_MMA8452[4]<<8)|BUF_MMA8452[5];    //合成数据  
   dis_data_MMA_Z>>=4; 
   dis_data_MMA_Z   = (BUF_MMA8452[4]<<8)|BUF_MMA8452[5];
   if(dis_data_MMA_Z>2048)
   {
   	dis_data_MMA_Z = -((~dis_data_MMA_Z)+1);
   }*/
    
}

int Read_MMA8452_X(void)
{
	unsigned char i;
    IIC_Start_2();                          //起始信号
    IIC_SendByte_2(SlaveAddress_MMA8452);           //发送设备地址+写信号
    IIC_SendByte_2(0x01);                   //发送存储单元地址，从0x01开始	
    IIC_Start_2();                          //起始信号
    IIC_SendByte_2(SlaveAddress_MMA8452+1);         //发送设备地址+读信号
    for (i=0; i<6; i++)                      //连续读取6个地址数据，存储中BUF
    {
        BUF_MMA8452[i] = IIC_RecvByte_2();          //BUF[0]存储0x32地址中的数据
        if (i == 5)
        {
           IIC_SendACK_2_NACK();                //最后一个数据需要回NOACK
        }
        else
        {
          IIC_SendACK_2_ACK();                //回应ACK
        }
   }
    IIC_Stop_2();                          //停止信号
    Delay5us();
    
   dis_data_MMA_X=(BUF_MMA8452[0]<<8)|BUF_MMA8452[1];    //合成数据  
   dis_data_MMA_X>>=4; 
   return dis_data_MMA_X; 
}

int Read_MMA8452_Y(void)
{
	unsigned char i;
    IIC_Start_2();                          //起始信号
    IIC_SendByte_2(SlaveAddress_MMA8452);           //发送设备地址+写信号
    IIC_SendByte_2(0x01);                   //发送存储单元地址，从0x01开始	
    IIC_Start_2();                          //起始信号
    IIC_SendByte_2(SlaveAddress_MMA8452+1);         //发送设备地址+读信号
    for (i=0; i<6; i++)                      //连续读取6个地址数据，存储中BUF
    {
        BUF_MMA8452[i] = IIC_RecvByte_2();          //BUF[0]存储0x32地址中的数据
        if (i == 5)
        {
           IIC_SendACK_2_NACK();                //最后一个数据需要回NOACK
        }
        else
        {
          IIC_SendACK_2_ACK();                //回应ACK
        }
   }
    IIC_Stop_2();                          //停止信号
    Delay5us();
    
   dis_data_MMA_Y=(BUF_MMA8452[2]<<8)|BUF_MMA8452[3];    //合成数据  
   dis_data_MMA_Y>>=4; 
   return dis_data_MMA_Y; 
}

//*********************************************************
//
//连续读出MMA8452内部加速度数据，地址范围0x01~0x06
//
//*********************************************************
void Multiple_read_MMA8452(void)
{   
	unsigned char i;
    IIC_Start_2();                          //起始信号
    IIC_SendByte_2(SlaveAddress_MMA8452);           //发送设备地址+写信号
    IIC_SendByte_2(0x01);                   //发送存储单元地址，从0x01开始	
    IIC_Start_2();                          //起始信号
    IIC_SendByte_2(SlaveAddress_MMA8452+1);         //发送设备地址+读信号
	for (i=0; i<6; i++)                      //连续读取6个地址数据，存储中BUF
    {
        BUF_MMA8452[i] = IIC_RecvByte_2();          //BUF[0]存储0x32地址中的数据
        if (i == 5)
        {
           IIC_SendACK_2_NACK();                //最后一个数据需要回NOACK
        }
        else
        {
          IIC_SendACK_2_ACK();                //回应ACK
        }
    }
    IIC_Stop_2();                          //停止信号
    Delay5us();
}
