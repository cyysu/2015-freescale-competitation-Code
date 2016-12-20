#include "support_common.h" /* include peripheral declarations and more */
#include "I2C1.h"



void init_i2c1(void)
{
	uint8 temp_i2c1;
		
	MCF_GPIO_PASPAR= MCF_GPIO_PQSPAR_QSPI_DOUT_SCL1
					 |MCF_GPIO_PQSPAR_QSPI_DIN_SDA1;
//set I2C address	需要改动
	MCF_I2C1_I2ADR=MCF_I2C_I2ADR_ADR(0x0D);
// 80,000/640=125KHz	
	MCF_I2C1_I2FDR=MCF_I2C_I2FDR_IC(0x12);
	
	MCF_I2C1_I2CR=0|MCF_I2C_I2CR_IEN;
				 //|MCF_I2C_I2CR_IIEN
				 //|MCF_I2C_I2CR_TXAK
				 //|MCF_I2C_I2CR_MSTA

//if busy set to be slave module and send a top
	if(MCF_I2C1_I2SR&MCF_I2C_I2SR_IBB)
	{
//clear control register	
		MCF_I2C1_I2CR=0;
//enable module and send a START condition
		MCF_I2C1_I2CR=MCF_I2C_I2CR_IEN
					 |MCF_I2C_I2CR_MSTA;
//dummy read					 
		temp_i2c1=MCF_I2C0_I2DR;
//clear status register		
		MCF_I2C1_I2SR=0;
//clear control register		
		MCF_I2C1_I2CR=0;
//enable the module
		MCF_I2C1_I2CR=MCF_I2C_I2CR_IEN;
	}
	
}

void i2c_start1(void)
{
	while(MCF_I2C1_I2SR&MCF_I2C_I2SR_IBB) ;	
	MCF_I2C1_I2CR|=MCF_I2C_I2CR_MTX;
	MCF_I2C1_I2CR|=MCF_I2C_I2CR_MSTA;	
}

uint8 i2c_send_byte1(uint8 c)
{
	MCF_I2C1_I2DR=c;
	while((MCF_I2C1_I2SR&MCF_I2C_I2SR_IIF)==0)
	{
		;
	}
	MCF_I2C1_I2SR&=~MCF_I2C_I2SR_IIF;

	//	while(MCF_I2C0_I2SR&MCF_I2C_I2SR_RXAK) ;
		
	if(MCF_I2C1_I2SR&MCF_I2C_I2SR_RXAK)
		return 0;//failed
	else
		return 1;//success
}

uint8 i2c_recv_byte1(uint8 ack)
{
	uint8 temp_i2c2;

	MCF_I2C1_I2CR&=~MCF_I2C_I2CR_MTX;

	if(ack)	//send acknowledge single 
		MCF_I2C1_I2CR&=~MCF_I2C_I2CR_TXAK;
	else  //no acknowledge single 
		MCF_I2C1_I2CR|=MCF_I2C_I2CR_TXAK;
	temp_i2c2=MCF_I2C1_I2DR;
	//	uart0_putchar(temp);
	while((MCF_I2C1_I2SR&MCF_I2C_I2SR_IIF)==0)
	{
		;
	}
	MCF_I2C0_I2SR&=~MCF_I2C_I2SR_IIF;
	temp_i2c2=MCF_I2C0_I2DR;
	//	uart0_putchar(temp);
	while((MCF_I2C1_I2SR&MCF_I2C_I2SR_IIF)==0)
	{
		;
	}
	MCF_I2C1_I2SR&=~MCF_I2C_I2SR_IIF;
	
	return temp_i2c2;

}

void i2c_stop1()
{
	MCF_I2C1_I2CR&=~MCF_I2C_I2CR_MSTA;
}

void i2c_restart1()
{
	MCF_I2C1_I2CR|=MCF_I2C_I2CR_RSTA;
}


