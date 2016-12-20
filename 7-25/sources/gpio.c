#include "gpio.h"
//// 配置输出的方向
void gpio_init(void)
{
	
	/**
			IO口的配置的一般过程: 判断某寄存器中的哪一个口 ----> 对应单片机中的某一功能
				1.确定端口号
				2.配置功能(PAR)
				3.端口数据的输入还是输出(DDR)
				4.端口输出寄存器（给出端口输出的状态） PORT
				5.如果是输入功能的话  那么通过设置 SET 可以读取这个管脚的状态
				
			Example：
				1) 配置TC口的RUNpin引脚为GPIO功能
				TC口有四个复用功能，根据“引脚配置寄存器”的编程方法，TC口的每个引脚功能具体定义为何种功能，由TC口引脚配置寄存器PTCPAR中的相应两位决定。在本书的工程实例中，PTCPAR被加上“MCF_GPIO_”前缀，变成MCF_GPIO_PTCPAR，用来表示TC口引脚配置寄存器，其他寄存器类似。
				MCF_GPIO_PTCPAR &= ~((0x03)<<(2*( RUNpin ))) //定义TC.RUNpin为GPIO
				
				2) 设置TC口的RUNpin引脚为输出
				MCF_GPIO_DDRTC |= (0x01<<RUNpin) //设置TC. RUNpin为输出
			
				3) 在TC的RUNpin引脚上输出高/低电平
				MCF_GPIO_PORTTC |= (0x01<<RUNpin) //TC. RUNpin=1(高电平)
				MCF_GPIO_PORTTC &= ~(0x01<< RUNpin) // TC. RUNpin=0(低电平)
			
				4) 设置TC口RUNpin引脚为输入并读取RUNpin引脚状态
				MCF_GPIO_DDRTC &= ~(0x01<<RUNpin) //设置TC. RUNpin为输入
				value = MCF_GPIO_SETTC &(0x01<< RUNpin) //获取TC. RUNpin状态	
			
	
	**/
	MCF_GPIO_PTEPAR = 0x00;//设置TE端口为gpio功能//接摄像头
	MCF_GPIO_PTFPAR = 0x00;//设置TF端口为gpio功能//拨码开关
	MCF_GPIO_PTHPAR = 0x00;
	MCF_GPIO_PUCPAR = 0x00;
	MCF_GPIO_PQSPAR = 0x00;
	
	MCF_GPIO_DDRTE |=  MCF_GPIO_DDRTE_DDRTE3; // A3   ccd2接口        					            
	MCF_GPIO_DDRTE |=  MCF_GPIO_DDRTE_DDRTE1; // A1
	  
	MCF_GPIO_DDRTH |=  MCF_GPIO_DDRTH_DDRTH1; // D3
	MCF_GPIO_DDRTE |=  MCF_GPIO_DDRTE_DDRTE2; // A2
	
	
	
	MCF_GPIO_DDRUC |= MCF_GPIO_DDRUC_DDRUC3;  	//蜂鸣器
		
	MCF_GPIO_DDRTG |= MCF_GPIO_DDRTG_DDRTG0;
	MCF_GPIO_DDRTG |= MCF_GPIO_DDRTG_DDRTG1;
	MCF_GPIO_DDRTG |= MCF_GPIO_DDRTG_DDRTG2;             					            
	MCF_GPIO_DDRTG |= MCF_GPIO_DDRTG_DDRTG3;              
	MCF_GPIO_DDRTF |= MCF_GPIO_DDRTF_DDRTF7;//A16~A19为5110的控制口

    MCF_GPIO_DDRNQ &=~MCF_GPIO_DDRNQ_DDRNQ3;	//IRQ3输入信号
	
	MCF_GPIO_DDRTF |= MCF_GPIO_DDRTF_DDRTF0;	//A8
	
	MCF_GPIO_DDRTH &=~ MCF_GPIO_DDRTH_DDRTH4;	//D4
	MCF_GPIO_DDRTH &=~ MCF_GPIO_DDRTH_DDRTH5;	//D4
	
	MCF_GPIO_DDRTE &=~ MCF_GPIO_DDRTE_DDRTE6;	//A6
   	MCF_GPIO_DDRTF &=~ MCF_GPIO_DDRTF_DDRTF1;	//A6
    //R_GPT_COUNT_OFF;
    //L_GPT_COUNT_OFF;//关脉冲计数	
 } 