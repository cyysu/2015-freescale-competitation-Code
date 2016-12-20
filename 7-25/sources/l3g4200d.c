#include "l3g4200d.h"
#include "I2C.h"


//*****************************************************************

//��ʼ��L3G4200D��������Ҫ��ο�pdf�����޸�************************
void InitL3G4200D()
{
   Single_WriteL3G4200D(CTRL_REG1, 0xff);   //ʹ��������
   Single_WriteL3G4200D(CTRL_REG2, 0x00);   //
   Single_WriteL3G4200D(CTRL_REG3, 0x08);   //
   Single_WriteL3G4200D(CTRL_REG4, 0x10);  //+-500dps
   Single_WriteL3G4200D(CTRL_REG5, 0x00);
}

//���ֽ�д��*******************************************

void Single_WriteL3G4200D(uint8 REG_Address,uint8 REG_data)
{
 i2c_start();                  //��ʼ�ź�
 i2c_send_byte(SlaveAddress);   //�����豸��ַ+д�ź�
 i2c_send_byte(REG_Address);    //�ڲ��Ĵ�����ַ����ο�����pdf22ҳ 
 i2c_send_byte(REG_data);       //�ڲ��Ĵ������ݣ���ο�����pdf22ҳ 
 i2c_stop();                   //����ֹͣ�ź�
}

//���ֽڶ�ȡ*****************************************

uint8 Single_ReadL3G4200D(uint8 REG_Address)
{     
	uint8 REG_data;
  	i2c_start();                          //��ʼ�ź�
  	i2c_send_byte (SlaveAddress);           //�����豸��ַ+д�ź�
  	i2c_send_byte (REG_Address);            //���ʹ洢��Ԫ��ַ����0��ʼ	
  	i2c_restart();                          //��ʼ�ź�
  	i2c_send_byte(SlaveAddress+1);         //�����豸��ַ+���ź�
  	REG_data=i2c_recv_byte(0);              //�����Ĵ�������   
  	i2c_stop();                           //ֹͣ�ź�
  	return REG_data; 
}
//***********************************************************************
int16 cai_x()
{ 
    int8 xi,xj;
    int16 temp_x;
    xi= Single_ReadL3G4200D(OUT_X_L);
    xj= Single_ReadL3G4200D(OUT_X_H); //��ȡX������
    temp_x=(int)((xj<<8)+xi);       //�ϳ�����   
    return temp_x;
}

int16 cai_y()
{ 
    int8 yi,yj;
    int16 temp_y;
    yi= Single_ReadL3G4200D(OUT_Y_L);
    yj= Single_ReadL3G4200D(OUT_Y_H); //��ȡY������

    temp_y=(yj<<8)+yi;       //�ϳ�����   
    return temp_y;
}
int16 cai_z()
{ 
    int8 zi,zj;
    int16 temp_z;
    zi= Single_ReadL3G4200D(OUT_Z_L);
    zj= Single_ReadL3G4200D(OUT_Z_H); //��ȡZ������
    temp_z=(zj<<8)+zi;       //�ϳ�����   
    return temp_z;
}
void delay1(int us)
{
	int a1,b1;
	if(us<1) us=1;
	for(a1=0;a1<us;a1++)
	for(b1=0;b1<3;b1++)
	{
		
	}//ԼΪ1΢��
}


/*****************************************************/
/***************���ٶȼƲ��ֺ���**********************/
/*****************************************************/
BYTE BUF_MMA8452[8];
int  dis_data_MMA_Z;
int  dis_data_MMA_X;
int  dis_data_MMA_Y;
//��ʼ��MMA8452��������Ҫ��ο�pdf�����޸�************************
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
    IIC_Start_2();                  //��ʼ�ź�
    IIC_SendByte_2(SlaveAddress_MMA8452);   //�����豸��ַ+д�ź�
    IIC_SendByte_2(REG_Address);    //�ڲ��Ĵ�����ַ
    IIC_SendByte_2(REG_data);       //�ڲ��Ĵ�������
    IIC_Stop_2();                   //����ֹͣ�ź�
}
/************************************************/
/***          ֻ�������ٶȼ�Z��Ƕ�           ***/
/************************************************/
int Read_MMA8452_Z(void) 
{
    unsigned char i;
    int16 sum;
    int sign;
    IIC_Start_2();                          //��ʼ�ź�
    IIC_SendByte_2(SlaveAddress_MMA8452);           //�����豸��ַ+д�ź�
    IIC_SendByte_2(0x05);                   //���ʹ洢��Ԫ��ַ����0x05��ʼ	
    IIC_Start_2();                          //��ʼ�ź�
    IIC_SendByte_2(SlaveAddress_MMA8452+1);         //�����豸��ַ+���ź�
    for (i=0; i<2; i++)                      //������ȡ6����ַ���ݣ��洢��BUF
    {
        BUF_MMA8452[i] = IIC_RecvByte_2();          //BUF[0]�洢0x32��ַ�е�����
        if (i == 2)
        {
           IIC_SendACK_2_NACK();                //���һ��������Ҫ��NOACK
        }
        else
        {
           IIC_SendACK_2_ACK();                //��ӦACK
        }
   }
   IIC_Stop_2();                          //ֹͣ�ź�
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

 /*  dis_data_MMA_Z=(BUF_MMA8452[4]<<8)|BUF_MMA8452[5];    //�ϳ�����  
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
    IIC_Start_2();                          //��ʼ�ź�
    IIC_SendByte_2(SlaveAddress_MMA8452);           //�����豸��ַ+д�ź�
    IIC_SendByte_2(0x01);                   //���ʹ洢��Ԫ��ַ����0x01��ʼ	
    IIC_Start_2();                          //��ʼ�ź�
    IIC_SendByte_2(SlaveAddress_MMA8452+1);         //�����豸��ַ+���ź�
    for (i=0; i<6; i++)                      //������ȡ6����ַ���ݣ��洢��BUF
    {
        BUF_MMA8452[i] = IIC_RecvByte_2();          //BUF[0]�洢0x32��ַ�е�����
        if (i == 5)
        {
           IIC_SendACK_2_NACK();                //���һ��������Ҫ��NOACK
        }
        else
        {
          IIC_SendACK_2_ACK();                //��ӦACK
        }
   }
    IIC_Stop_2();                          //ֹͣ�ź�
    Delay5us();
    
   dis_data_MMA_X=(BUF_MMA8452[0]<<8)|BUF_MMA8452[1];    //�ϳ�����  
   dis_data_MMA_X>>=4; 
   return dis_data_MMA_X; 
}

int Read_MMA8452_Y(void)
{
	unsigned char i;
    IIC_Start_2();                          //��ʼ�ź�
    IIC_SendByte_2(SlaveAddress_MMA8452);           //�����豸��ַ+д�ź�
    IIC_SendByte_2(0x01);                   //���ʹ洢��Ԫ��ַ����0x01��ʼ	
    IIC_Start_2();                          //��ʼ�ź�
    IIC_SendByte_2(SlaveAddress_MMA8452+1);         //�����豸��ַ+���ź�
    for (i=0; i<6; i++)                      //������ȡ6����ַ���ݣ��洢��BUF
    {
        BUF_MMA8452[i] = IIC_RecvByte_2();          //BUF[0]�洢0x32��ַ�е�����
        if (i == 5)
        {
           IIC_SendACK_2_NACK();                //���һ��������Ҫ��NOACK
        }
        else
        {
          IIC_SendACK_2_ACK();                //��ӦACK
        }
   }
    IIC_Stop_2();                          //ֹͣ�ź�
    Delay5us();
    
   dis_data_MMA_Y=(BUF_MMA8452[2]<<8)|BUF_MMA8452[3];    //�ϳ�����  
   dis_data_MMA_Y>>=4; 
   return dis_data_MMA_Y; 
}

//*********************************************************
//
//��������MMA8452�ڲ����ٶ����ݣ���ַ��Χ0x01~0x06
//
//*********************************************************
void Multiple_read_MMA8452(void)
{   
	unsigned char i;
    IIC_Start_2();                          //��ʼ�ź�
    IIC_SendByte_2(SlaveAddress_MMA8452);           //�����豸��ַ+д�ź�
    IIC_SendByte_2(0x01);                   //���ʹ洢��Ԫ��ַ����0x01��ʼ	
    IIC_Start_2();                          //��ʼ�ź�
    IIC_SendByte_2(SlaveAddress_MMA8452+1);         //�����豸��ַ+���ź�
	for (i=0; i<6; i++)                      //������ȡ6����ַ���ݣ��洢��BUF
    {
        BUF_MMA8452[i] = IIC_RecvByte_2();          //BUF[0]�洢0x32��ַ�е�����
        if (i == 5)
        {
           IIC_SendACK_2_NACK();                //���һ��������Ҫ��NOACK
        }
        else
        {
          IIC_SendACK_2_ACK();                //��ӦACK
        }
    }
    IIC_Stop_2();                          //ֹͣ�ź�
    Delay5us();
}
