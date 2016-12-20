#include "pwm.h"
/*
	PWM控制程序的编写一般按照以下的一种流程：

		1，禁止PWM模块；//这是由于改变周期和脉宽等操作需要在PWM禁止的情况下才能被设置

		2，PWM级联选择，是否级联通道67,45,23,01；//最多单独使用8个8位和级联使用4个16位

		3，给通道选择时钟源控制位；//0,1,4,5通道可选择ClockA和ClockSA；2,3,6,7通道可选择ClockB和ClockSB

		4，给时钟源A\B预分频；//可对总线时钟进行预分频，确定ClockA和ClockB，满足1,2,4,8,16,32,64,128这8个分频量

		5，根据时钟源A\B确定时钟源SA\SB；//由ClockA和ClockB、分频设值来确定ClockA和ClockB，满足1-255的分频量

		6，输出极性的选择；//也就是选择输出极性先低后高还是先高后低

		7，对齐方式的选择；//可设置为左对齐或者中间对齐方式

		8，实际通道频率的计算；//也就是周期的设定

		9，占空比寄存器的设置；//占空比常数的设定，可以以此决定占空比

		10，使能PWM模块。

*/

void PWM_init(void)
{
	//function choose  开启pwm功能
	MCF_GPIO_PTCPAR = MCF_GPIO_PTCPAR_DTIN0_PWM0
					 |MCF_GPIO_PTCPAR_DTIN2_PWM4;

	MCF_GPIO_PTAPAR |= MCF_GPIO_PTAPAR_ICOC0_PWM1
				  	|  MCF_GPIO_PTAPAR_ICOC2_PWM5;


    //pwm Polarity Register 
	MCF_PWM_PWMPOL = MCF_PWM_PWMPOL_PPOL1
					|MCF_PWM_PWMPOL_PPOL5;
	
	//pwm Clock select register:1-SA or SB  0-A or B
	///给通道选择是SCLKA 还是 SCLKB时钟
//	MCF_PWM_PWMCLK =  MCF_PWM_PWMCLK_PCLK0
					//|MCF_PWM_PWMCLK_PCLK1
					//|MCF_PWM_PWMCLK_PCLK2
					//|MCF_PWM_PWMCLK_PCLK3;
					//|MCF_PWM_PWMCLK_PCLK4
					//|MCF_PWM_PWMCLK_PCLK5;
      
    //pwm prescale clock select register bit[6:4]PCKB  bit[2:0]PCKA////10M
//	MCF_PWM_PWMPRCLK |= MCF_PWM_PWMPRCLK_PCKA(1);
//	MCF_PWM_PWMPRCLK |= MCF_PWM_PWMPRCLK_PCKB(2);
	
//	MCF_PWM_PWMPRCLK |= MCF_PWM_PWMPRCLK_PCKA(1);
//	MCF_PWM_PWMPRCLK |= MCF_PWM_PWMPRCLK_PCKB(1);

	//pwm center align enable register:1-center-aligned 0-left-aligned
	MCF_PWM_PWMCAE=0x00;	
	
	//pwm scale A&B register Clock SA=Clock A/2*PWMSCLA
//	MCF_PWM_PWMSCLA=5;//250;
//	MCF_PWM_PWMSCLB=5;
	
	//pwm channel counter register
	MCF_PWM_PWMCNT0=0;
	MCF_PWM_PWMCNT1=0;
	
	MCF_PWM_PWMCNT4=0; 
	MCF_PWM_PWMCNT5=0;
	
	//pwm control register   级联选择			

	MCF_PWM_PWMCTL=   MCF_PWM_PWMCTL_CON01 //1000  --->  10khz  0.1us 一个
					 |MCF_PWM_PWMCTL_CON45;//					

	/**
		左对齐方式：计数器PWMCNT从0开始对时钟信号递增计数，当PWMCNT = PWMDTY时
		比较器1输出有效，触发器置位，输出电平翻转。当PWMCNT = PWMPER时，比较器2输出有效
		触发器复位，输出电平翻转。同时PWMCNT复位，一个周期结束。
	**/
	
	MCF_PWM_PWMPER(1)=4000&0x00ff;
	MCF_PWM_PWMDTY(1)=2000&0x00ff;		//
	MCF_PWM_PWMPER(0)=4000>>8;
	MCF_PWM_PWMDTY(0)=2000>>8;			//
	
	MCF_PWM_PWMPER(5)=4000&0x00ff;
	MCF_PWM_PWMDTY(5)=2000&0x00ff;		//
	MCF_PWM_PWMPER(4)=4000>>8;
	MCF_PWM_PWMDTY(4)=2000>>8;			//


/**
//	10KHZ
	MCF_PWM_PWMPRCLK |= MCF_PWM_PWMPRCLK_PCKA(1);
	MCF_PWM_PWMPRCLK |= MCF_PWM_PWMPRCLK_PCKB(1);

	MCF_PWM_PWMPER(1)=2000&0x00ff;
	MCF_PWM_PWMDTY(1)=1000&0x00ff;		//
	MCF_PWM_PWMPER(0)=2000>>8;
	MCF_PWM_PWMDTY(0)=1000>>8;			//
	
	MCF_PWM_PWMPER(5)=2000&0x00ff;
	MCF_PWM_PWMDTY(5)=1000&0x00ff;		//
	MCF_PWM_PWMPER(4)=2000>>8;
	MCF_PWM_PWMDTY(4)=1000>>8;			//
**/

	//pwm start
	MCF_PWM_PWMSDN = MCF_PWM_PWMSDN_IF;
	MCF_PWM_PWME   = MCF_PWM_PWME_PWME1
				    |MCF_PWM_PWME_PWME5;
}
//////////////////////
//右电机转速函数  ICO2
//0-1000
//500-1000正  500min  1000max    
//500-0反    500min  0max
//////////////////////
void PWM_right(int16 x)//youcuowu
{
	MCF_PWM_PWMDTY(4)=(x>>8);
	MCF_PWM_PWMDTY(5)=(x&0x00ff);
}
//////////////////////
//左电机转速函数 ICO0
//500-1000正  500min  1000max    
//500-0反    500min  0max
//////////////////////
void PWM_left(int16 x)
{
	MCF_PWM_PWMDTY(0)=(x>>8);
	MCF_PWM_PWMDTY(1)=(x&0x00ff);
}


