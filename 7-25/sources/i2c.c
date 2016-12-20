#include "support_common.h" /* include peripheral declarations and more */
#include "I2C.h"
#include "gpio.h"

void init_i2c(void)
{
	uint8 temp_i2c1;
		
	MCF_GPIO_PASPAR= MCF_GPIO_PASPAR_SCL0_SCL0
					|MCF_GPIO_PASPAR_SDA0_SDA0;
//set I2C address	
	MCF_I2C0_I2ADR=MCF_I2C_I2ADR_ADR(0x0D);
// 80,000/640=125KHz	
	MCF_I2C0_I2FDR=MCF_I2C_I2FDR_IC(0x12);
	
	MCF_I2C0_I2CR=0|MCF_I2C_I2CR_IEN;
				 //|MCF_I2C_I2CR_IIEN
				 //|MCF_I2C_I2CR_TXAK
				 //|MCF_I2C_I2CR_MSTA

//if busy set to be slave module and send a top
	if(MCF_I2C0_I2SR&MCF_I2C_I2SR_IBB)
	{
//clear control register	
		MCF_I2C0_I2CR=0;
//enable module and send a START condition
		MCF_I2C0_I2CR=MCF_I2C_I2CR_IEN
					 |MCF_I2C_I2CR_MSTA;
//dummy read					 
		temp_i2c1=MCF_I2C0_I2DR;
//clear status register		
		MCF_I2C0_I2SR=0;
//clear control register		
		MCF_I2C0_I2CR=0;
//enable the module
		MCF_I2C0_I2CR=MCF_I2C_I2CR_IEN;
	}
	
}

void i2c_start(void)
{
	while(MCF_I2C0_I2SR&MCF_I2C_I2SR_IBB) ;	
	MCF_I2C0_I2CR|=MCF_I2C_I2CR_MTX;
	MCF_I2C0_I2CR|=MCF_I2C_I2CR_MSTA;	
}

uint8 i2c_send_byte(uint8 c)
{
	MCF_I2C0_I2DR=c;
	while((MCF_I2C0_I2SR&MCF_I2C_I2SR_IIF)==0)
	{
		;
	}
	MCF_I2C0_I2SR&=~MCF_I2C_I2SR_IIF;

	//	while(MCF_I2C0_I2SR&MCF_I2C_I2SR_RXAK) ;
		
	if(MCF_I2C0_I2SR&MCF_I2C_I2SR_RXAK)
		return 0;//failed
	else
		return 1;//success
}

uint8 i2c_recv_byte(uint8 ack)
{
	uint8 temp_i2c2;

	MCF_I2C0_I2CR&=~MCF_I2C_I2CR_MTX;

	if(ack)	//send acknowledge single 
		MCF_I2C0_I2CR&=~MCF_I2C_I2CR_TXAK;
	else  //no acknowledge single 
		MCF_I2C0_I2CR|=MCF_I2C_I2CR_TXAK;
	temp_i2c2=MCF_I2C0_I2DR;
	//	uart0_putchar(temp);
	while((MCF_I2C0_I2SR&MCF_I2C_I2SR_IIF)==0)
	{
		;
	}
	MCF_I2C0_I2SR&=~MCF_I2C_I2SR_IIF;
	temp_i2c2=MCF_I2C0_I2DR;
	//	uart0_putchar(temp);
	while((MCF_I2C0_I2SR&MCF_I2C_I2SR_IIF)==0)
	{
		;
	}
	MCF_I2C0_I2SR&=~MCF_I2C_I2SR_IIF;
	return temp_i2c2;
}

void i2c_stop()
{
	MCF_I2C0_I2CR&=~MCF_I2C_I2CR_MSTA;
}

void i2c_restart()
{
	MCF_I2C0_I2CR|=MCF_I2C_I2CR_RSTA;
}

////////////////////////////////////////////////////////////////////////////
///////////////          ���ּ��ٶȼ�      ////////////////////////////////
//////////////////////////////////////////////////////////////////////////

/*********************************/

void IIC_Init_2(void) 
{
	//DDR_SCL_OUT;
	//DDR_SDA_OUT;
    SCL_1;
    Delay5us();
    SDA_1;
    Delay5us(); 
}

/**************************************
��ʼ�ź�
**************************************/
void IIC_Start_2()
{
//	DDR_SCL_OUT;
//	DDR_SDA_OUT;
//    SDA_1;                    //����������
//    SCL_1;                    //����ʱ����
//    Delay5us();               //��ʱ
//    SDA_0;                    //�����½���
//    Delay5us();               //��ʱ
//    SCL_0;                    //����ʱ����
    DDR_SCL_OUT;   // SCLout;
	DDR_SDA_OUT;   // SDAout;
    SCL_0;         // SCL_L_;
    __asm(nop);    // asm("nop"); 
    SDA_1;         // SDA_H_;
    Delay5us();    // nop5();
    SCL_1;         // SCL_H_;
    __asm(nop);    // nops();
    SDA_0;         //SDA_L_;
    __asm(nop);    // nops();
    SCL_0;         //SCL_L_;

}

/**************************************
ֹͣ�ź�
**************************************/
void IIC_Stop_2()
{
/*    DDR_SCL_OUT;
	DDR_SDA_OUT;
    SDA_0;                    //����������
    SCL_1;                    //����ʱ����
    Delay5us();               //��ʱ
    SDA_1;                    //����������
    Delay5us();               //��ʱ     */
    
    DDR_SCL_OUT;  // SCLout;
	DDR_SDA_OUT;  // SDAout;    
    SCL_0;Delay5us(); //SCL_L_;nop5();
    SDA_0;Delay5us(); //SDA_L_;nop5();
    SCL_1;Delay5us(); //SCL_H_;nops();
    SDA_1;Delay5us(); //SDA_H_;nops();
    SCL_0; //SCL_L_;
}

/**************************************
����Ӧ���ź�1 NACK
��ڲ���:ack (0:ACK 1:NAK)
**************************************/
void IIC_SendACK_2_NACK()
{
    DDR_SCL_OUT;
	DDR_SDA_OUT;
    SDA_1;                  //дӦ���ź�
    SCL_1;                  //����ʱ����
    Delay5us();             //��ʱ
    SCL_0;                  //����ʱ����
    Delay5us();             //��ʱ    
}
/**************************************
����Ӧ���ź�0 ACK
��ڲ���:ack (0:ACK 1:NAK)
**************************************/
void IIC_SendACK_2_ACK()
{
	DDR_SCL_OUT;
	DDR_SDA_OUT;
    SDA_0;                  //дӦ���ź�
    SCL_1;                  //����ʱ����
    Delay5us();             //��ʱ
    SCL_0;                  //����ʱ����
    Delay5us();             //��ʱ      
}

/**************************************
����Ӧ���ź�
**************************************/
void IIC_RecvACK_2()
{
    unsigned int i=0;
	DDR_SCL_OUT;
	DDR_SDA_IN;
    SCL_1;                    //����ʱ����
    Delay5us();               //��ʱ
    while((SDA_Read == 1)&&(i<2000))i++;
    SCL_0;                    //����ʱ����
    Delay5us();               //��ʱ    
}

/**************************************
��IIC���߷���һ���ֽ�����
**************************************/
void IIC_SendByte_2(BYTE dat)
{
/*    BYTE i;
    DDR_SCL_OUT;
	DDR_SDA_OUT;       
    for (i=0; i<8; i++)          //8λ������
    {
        if(dat&0x80)
        	SDA_1;               //�����ݿ�
    	else
    		SDA_0;
        dat <<= 1;              //�Ƴ����ݵ����λ
        SCL_1;                  //����ʱ����
        Delay5us();             //��ʱ
        SCL_0;                  //����ʱ����
        Delay5us();             //��ʱ
    }  
    IIC_RecvACK_2();    */
    
    
    unsigned char i;
    DDR_SCL_OUT;               //SCLout;
    DDR_SDA_OUT;__asm(nop);    //SDAout;asm("nop");
    for(i=0;i<8;i++)
    {
        SCL_0;                 //SCL_L_;
        if((dat<<i) & 0x80)
            SDA_1;             //SDA_H_; //�жϷ���λ
        else
            SDA_0;             //SDA_L_;
        Delay5us();            //nop5();
        SCL_1;                 //SCL_H_;
        Delay5us();            //nops();
        SCL_0;                 //SCL_L_;
    }
    Delay5us();                //nops();
    SDA_1;                     //SDA_H_; //������8bit���ͷ�����׼������Ӧ��λ
    Delay5us();                //nop5();
    SCL_1;                     //SCL_H_;
    Delay5us();                //nops(); //sda�����ݼ��Ǵ�Ӧ��λ
    SCL_0;                     //SCL_L_; //�����Ǵ�Ӧ��λ|��Ҫ���ƺ�ʱ��
}

/**************************************
     ��IIC���߽���һ���ֽ�����
**************************************/
BYTE IIC_RecvByte_2()
{
/*    BYTE dat = 0;
    BYTE i;
    DDR_SCL_OUT;			    //ʹ���ڲ�����,׼����ȡ����,
	DDR_SDA_OUT;   
    SDA_1;  
    DDR_SDA_IN;                    
    for (i=0; i<8; i++)         //8λ������
    {
        dat <<= 1;                              //�����1�� 00000001
        SCL_1;                  //����ʱ����
        Delay5us();             //��ʱ
        dat |= SDA_Read;        //������      SDA  00000000 or 00000001         
        SCL_0;                  //����ʱ����
        Delay5us();             //��ʱ
    }
    return dat;       */
    unsigned char i;
    unsigned char dat;
    DDR_SDA_IN;                 //SDAin;
    DDR_SCL_OUT;                //SCLout;
    dat=0;                      //c=0;
    SCL_0;                      //SCL_L_;
    Delay5us();                 //nop5();
    for(i=0;i<8;i++)
    {
        Delay5us();             //nop5();
        SCL_0;                  //SCL_L_; //��ʱ����Ϊ�ͣ�׼����������λ
        Delay5us();             //nops();
        SCL_1;                  //SCL_H_; //��ʱ����Ϊ�ߣ�ʹ��������������Ч
        Delay5us();             //nop5();
        dat<<=1;                //c<<=1;
        if(SDA_Read)
            dat+=1;             //c+=1; //������λ�������յ����ݴ�c
    }
    SCL_0;                      //SCL_L_;
    return dat;
}
/************************************
��ʱ5΢��(STC90C52RC@12M)
��ͬ�Ĺ�������,��Ҫ�����˺�����ע��ʱ�ӹ���ʱ��Ҫ�޸�
������1T��MCUʱ,���������ʱ����
**************************************/
void Delay5us()
{
      __asm(nop); __asm(nop); __asm(nop); __asm(nop);\
      __asm(nop); __asm(nop); __asm(nop); __asm(nop);\
      __asm(nop); __asm(nop); __asm(nop); __asm(nop);\
      __asm(nop); __asm(nop); __asm(nop); __asm(nop);\
      __asm(nop); __asm(nop); __asm(nop); __asm(nop);\
      __asm(nop); __asm(nop); __asm(nop); __asm(nop);\
      __asm(nop); __asm(nop); __asm(nop); __asm(nop);\
      __asm(nop); __asm(nop); __asm(nop); __asm(nop);\
      __asm(nop); __asm(nop); __asm(nop); __asm(nop);\
      __asm(nop); __asm(nop); __asm(nop); __asm(nop);\
}















