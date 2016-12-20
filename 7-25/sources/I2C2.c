#include "I2C2.h"
#include "include.h"

int16 lss_CarAngle = 0;

void I2C_delay(void)
{
    uint16 n;
    for(n = 1; n < 20; n++)      //ע�⣬�������̫С���ᵼ�¶�ȡ����
    {
        asm("nop");
    }
}


void I2C1_init(uint8 addr)
{
	uint8 temp;
	MCF_GPIO_DDRAS=0;
	MCF_GPIO_PASPAR=MCF_GPIO_PASPAR_SDA0_SDA0|MCF_GPIO_PASPAR_SCL0_SCL0;
	MCF_I2C0_I2FDR=0x15;
	MCF_I2C0_I2CR=MCF_I2C_I2CR_IEN|0;

	if(MCF_I2C0_I2SR&MCF_I2C_I2SR_IBB)
	{ 
		MCF_I2C0_I2CR=0;
		MCF_I2C0_I2CR=MCF_I2C_I2CR_IEN|MCF_I2C_I2CR_MSTA;
		temp=MCF_I2C0_I2DR;
		MCF_I2C0_I2SR=0;
		MCF_I2C0_I2CR=0;
		MCF_I2C0_I2CR=MCF_I2C_I2CR_IEN|0;
	}
	MCF_I2C0_I2CR=0B10001000;
	return ;
}

uint8 I2C1_read(uint8 daddr,uint8 aaddr)
{
	uint8 result;
	while(MCF_I2C0_I2SR&MCF_I2C_I2SR_IBB);
	MCF_I2C0_I2CR|=MCF_I2C_I2CR_MTX;
	MCF_I2C0_I2CR|=MCF_I2C_I2CR_MSTA;
	MCF_I2C0_I2DR=(0x1c<<1)&0xfe;
	I2C_delay();
	while(!(MCF_I2C0_I2SR&MCF_I2C_I2SR_IIF));
	MCF_I2C0_I2SR&=~MCF_I2C_I2SR_IIF;
	MCF_I2C0_I2DR=(uint8)aaddr;
	I2C_delay();
	while(!(MCF_I2C0_I2SR&MCF_I2C_I2SR_IIF));
	MCF_I2C0_I2SR&=~MCF_I2C_I2SR_IIF;
	MCF_I2C0_I2CR|=MCF_I2C_I2CR_RSTA;
	MCF_I2C0_I2DR=0x1c|0x01;
	I2C_delay();
	while(!(MCF_I2C0_I2SR&MCF_I2C_I2SR_IIF));
	MCF_I2C0_I2SR&=~MCF_I2C_I2SR_IIF;
	MCF_I2C0_I2CR&=~MCF_I2C_I2CR_MTX;
	result=MCF_I2C0_I2DR;
	I2C_delay();
	while(!(MCF_I2C0_I2SR&MCF_I2C_I2SR_IIF));
	MCF_I2C0_I2SR&=~MCF_I2C_I2SR_IIF;
	MCF_I2C0_I2CR&=~MCF_I2C_I2CR_MSTA;
	result=MCF_I2C0_I2DR;
	I2C_delay();
	return result;

}


uint8 I2C1_read_05()
{
uint8 result;
while(MCF_I2C0_I2SR&MCF_I2C_I2SR_IBB);
MCF_I2C0_I2CR|=MCF_I2C_I2CR_MTX;
MCF_I2C0_I2CR|=MCF_I2C_I2CR_MSTA;
MCF_I2C0_I2DR=0b00111000;
I2C_delay();
while(!(MCF_I2C0_I2SR&MCF_I2C_I2SR_IIF));
MCF_I2C0_I2SR&=~MCF_I2C_I2SR_IIF;
MCF_I2C0_I2DR=0x05;
I2C_delay();
while(!(MCF_I2C0_I2SR&MCF_I2C_I2SR_IIF));
MCF_I2C0_I2SR&=~MCF_I2C_I2SR_IIF;
MCF_I2C0_I2CR|=MCF_I2C_I2CR_RSTA;
MCF_I2C0_I2DR=0b00111001;
I2C_delay();
while(!(MCF_I2C0_I2SR&MCF_I2C_I2SR_IIF));
MCF_I2C0_I2SR&=~MCF_I2C_I2SR_IIF;
MCF_I2C0_I2CR&=~MCF_I2C_I2CR_MTX;
result=MCF_I2C0_I2DR;
I2C_delay();
while(!(MCF_I2C0_I2SR&MCF_I2C_I2SR_IIF));
MCF_I2C0_I2SR&=~MCF_I2C_I2SR_IIF;
MCF_I2C0_I2CR&=~MCF_I2C_I2CR_MSTA;
result=MCF_I2C0_I2DR;
I2C_delay();
return result;

}



uint8 I2C1_read_06()
{
uint8 result;
while(MCF_I2C0_I2SR&MCF_I2C_I2SR_IBB);//æ��ȴ�
MCF_I2C0_I2CR|=MCF_I2C_I2CR_MTX;//����Ϊ����ģʽ
MCF_I2C0_I2CR|=MCF_I2C_I2CR_MSTA;//����start�ź�
MCF_I2C0_I2DR=0b00111000;//�豸��ַ����λ����
I2C_delay();
while(!(MCF_I2C0_I2SR&MCF_I2C_I2SR_IIF));//ֱ���жϲ��˳�
MCF_I2C0_I2SR&=~MCF_I2C_I2SR_IIF;//����ɱ�־
MCF_I2C0_I2DR=0x06;//���ʵ�ַ
I2C_delay();
while(!(MCF_I2C0_I2SR&MCF_I2C_I2SR_IIF));
MCF_I2C0_I2SR&=~MCF_I2C_I2SR_IIF;
MCF_I2C0_I2CR|=MCF_I2C_I2CR_RSTA;//����ģʽ�£�rsta��λ�������ظ���ʼ�ź�
MCF_I2C0_I2DR=0b00111001;//��ַ��λ��1��֪ͨ�ӻ���Ϊ��������
I2C_delay();
while(!(MCF_I2C0_I2SR&MCF_I2C_I2SR_IIF));
MCF_I2C0_I2SR&=~MCF_I2C_I2SR_IIF;
MCF_I2C0_I2CR&=~MCF_I2C_I2CR_MTX;//Tx=0��mcuΪ����
result=MCF_I2C0_I2DR;//�ն�
I2C_delay();
while(!(MCF_I2C0_I2SR&MCF_I2C_I2SR_IIF));
MCF_I2C0_I2SR&=~MCF_I2C_I2SR_IIF;
MCF_I2C0_I2CR&=~MCF_I2C_I2CR_MSTA;//����stop�ź�
result=MCF_I2C0_I2DR;
I2C_delay();
return result;

}

void I2C1_writel(uint8 aaddr,uint8 data)
{
	while(MCF_I2C0_I2SR&MCF_I2C_I2SR_IBB);
	MCF_I2C0_I2CR|=MCF_I2C_I2CR_MTX;
	MCF_I2C0_I2CR|=MCF_I2C_I2CR_MSTA;
	MCF_I2C0_I2DR=0b00111000;
	I2C_delay();
		while(!(MCF_I2C0_I2SR&MCF_I2C_I2SR_IIF));
		MCF_I2C0_I2SR&=~MCF_I2C_I2SR_IIF;
		MCF_I2C0_I2DR=(uint8)aaddr;
		I2C_delay();
		while(!(MCF_I2C0_I2SR&MCF_I2C_I2SR_IIF));
		MCF_I2C0_I2SR&=~MCF_I2C_I2SR_IIF;
		MCF_I2C0_I2DR=data;		
			I2C_delay();
				while(!(MCF_I2C0_I2SR&MCF_I2C_I2SR_IIF));
		MCF_I2C0_I2SR&=~MCF_I2C_I2SR_IIF;
		MCF_I2C0_I2CR&=~MCF_I2C_I2CR_MSTA;		
			I2C_delay();
			return ;
			
	
}




float get_mm845x()//ת���ɽǶ�
{
  uint16 V1;uint8 dz[2];
  float vv;
  int sign;
  dz[0]   =  I2C1_read_05();
        dz[1]   =   I2C1_read_06();    
  if(dz[0] > 0x7F)
  {
    sign=-1;
    V1   = (int)dz[0];	
    dz[1]= dz[1]>>2;
    V1   = V1<<6 | dz[1];
    V1   = (~V1 + 1)&0X3FFF;
    //V1= (~(V.mword>>2) + 1);
  }
  else
  {
    sign=1;
    V1   = (int)dz[0];	
    dz[1]= dz[1]>>2;
    V1   = V1<<6 | dz[1];
   
  }
  vv=sign*(((float)V1)*0.0219726562);

  return vv;
}

float Q_MMA  =0.0003;//0.0003  
float R_MMA  =0.003;
float MMA_p_00=0.05;
float MMA_Y,MMA_s;
float MMA_k_0;
float MMA_x_out;
float MMA_Kalman_lvbo(float duixiang)
{
  MMA_p_00+=Q_MMA;
  MMA_Y = duixiang - MMA_x_out;
  MMA_s = MMA_p_00 + R_MMA;
  MMA_k_0 = MMA_p_00 / MMA_s;
 
  MMA_x_out +=  MMA_k_0 * MMA_Y;
  MMA_p_00 -= MMA_k_0 * MMA_p_00;
  return MMA_x_out;
}


void mm845x_init()
{
    int i=0;
    I2C1_writel( 0x0f, 0x10); //��ͨ�˲�
    I2C1_writel(0x0e, 0x00); //2G
    I2C1_writel(0x2a, 0x01); //����
    for(i=0;i<5;i++)
    	lss_CarAngle+=get_mm845x();
    lss_CarAngle/=5.0;
}