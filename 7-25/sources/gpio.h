#ifndef GPIO_H_
#define GPIO_H_
#include "support_common.h" 

///蜂鸣器
#define BELL_L                MCF_GPIO_PORTUC &=~MCF_GPIO_PORTUC_PORTUC3 
#define BELL_H                MCF_GPIO_PORTUC  |=MCF_GPIO_PORTUC_PORTUC3 

/// 5110 用来测试执行的时间长度
#define SCLK_1                MCF_GPIO_PORTTG|=MCF_GPIO_PORTTG_PORTTG3 //A19 
#define SCLK_0                MCF_GPIO_PORTTG&=~MCF_GPIO_PORTTG_PORTTG3//A19
#define SDIN_1                MCF_GPIO_PORTTG|=MCF_GPIO_PORTTG_PORTTG2//A18
#define SDIN_0                MCF_GPIO_PORTTG&=~MCF_GPIO_PORTTG_PORTTG2//A18
#define LCD_DC_1              MCF_GPIO_PORTTG|=MCF_GPIO_PORTTG_PORTTG1//A17
#define LCD_DC_0              MCF_GPIO_PORTTG&=~MCF_GPIO_PORTTG_PORTTG1//A17
#define LCD_RST_1             MCF_GPIO_PORTTG|=MCF_GPIO_PORTTG_PORTTG0//A16
#define LCD_RST_0             MCF_GPIO_PORTTG&=~MCF_GPIO_PORTTG_PORTTG0//A16 
#define LCD_CE_1              MCF_GPIO_PORTTF|=MCF_GPIO_PORTTF_PORTTF7//A15
#define LCD_CE_0              MCF_GPIO_PORTTF&=~MCF_GPIO_PORTTF_PORTTF0//A15

/// 模拟开关
//#define L_GPT_COUNT_OPEN      MCF_GPIO_PORTTE |= MCF_GPIO_PORTTE_PORTTE6//A6
//#define L_GPT_COUNT_OFF		  MCF_GPIO_PORTTE &= ~MCF_GPIO_PORTTE_PORTTE6//A6

	
#define DDR_SCL_OUT	MCF_GPIO_DDRQS |=  MCF_GPIO_DDRQS_DDRQS0;   // SCL1 输出
#define DDR_SDA_OUT	MCF_GPIO_DDRQS |=  MCF_GPIO_DDRQS_DDRQS1;   // SDA1
#define DDR_SCL_IN	MCF_GPIO_DDRQS &=~ MCF_GPIO_DDRQS_DDRQS0;  // SCL1 输入
#define DDR_SDA_IN	MCF_GPIO_DDRQS &=~ MCF_GPIO_DDRQS_DDRQS1;  // SDA1
				
#define SCL_1    MCF_GPIO_PORTQS |=  MCF_GPIO_PORTQS_PORTQS0
#define SCL_0    MCF_GPIO_PORTQS &=~ MCF_GPIO_PORTQS_PORTQS0

#define SDA_1    MCF_GPIO_PORTQS |=  MCF_GPIO_PORTQS_PORTQS1
#define SDA_0    MCF_GPIO_PORTQS &=~ MCF_GPIO_PORTQS_PORTQS1

#define SDA_Read MCF_GPIO_SETQS&MCF_GPIO_SETQS_SETQS1   

/// 独立按键
#define KEY_1		         !(MCF_GPIO_SETTE&MCF_GPIO_SETTE_SETTE5)//A10
#define KEY_2		         !(MCF_GPIO_SETTE&MCF_GPIO_SETTE_SETTE7)//A10
#define KEY_4		         !(MCF_GPIO_SETTE&MCF_GPIO_SETTE_SETTE6)//A10


#define TIME_TEST_1	  		  MCF_GPIO_PORTTF |=  MCF_GPIO_PORTTF_PORTTF0  //A8
#define TIME_TEST_0		  	  MCF_GPIO_PORTTF &=~ MCF_GPIO_PORTTF_PORTTF0  //A8
/**
/// CCD2   
#define TSL1401_SI_1          MCF_GPIO_PORTTH |=  MCF_GPIO_PORTTH_PORTTH3//D3
#define TSL1401_SI_0          MCF_GPIO_PORTTH &=~ MCF_GPIO_PORTTH_PORTTH3//D3
#define TSL1401_CLK_1         MCF_GPIO_PORTTH |=  MCF_GPIO_PORTTH_PORTTH1//D1
#define TSL1401_CLK_0         MCF_GPIO_PORTTH &=~ MCF_GPIO_PORTTH_PORTTH1//D1

/// CCD1  
#define TSL1401_2_SI_1        MCF_GPIO_PORTTE |=  MCF_GPIO_PORTTE_PORTTE3//A3
#define TSL1401_2_SI_0        MCF_GPIO_PORTTE &=~ MCF_GPIO_PORTTE_PORTTE3//A3
#define TSL1401_2_CLK_1       MCF_GPIO_PORTTE |=  MCF_GPIO_PORTTE_PORTTE1//A1
#define TSL1401_2_CLK_0       MCF_GPIO_PORTTE &=~ MCF_GPIO_PORTTE_PORTTE1//A1
**/

#define CCD_AN0_CLK_1		MCF_GPIO_PORTTE|= MCF_GPIO_PORTTE_PORTTE1  //A1
#define CCD_AN0_CLK_0		MCF_GPIO_PORTTE&=~MCF_GPIO_PORTTE_PORTTE1 
#define CCD_AN0_SI_1        MCF_GPIO_PORTTE|= MCF_GPIO_PORTTE_PORTTE3
#define CCD_AN0_SI_0		MCF_GPIO_PORTTE&=~MCF_GPIO_PORTTE_PORTTE3  //A3



#define CCD_AN1_SI_1		MCF_GPIO_PORTTH|= MCF_GPIO_PORTTH_PORTTH1  //D3
#define CCD_AN1_SI_0		MCF_GPIO_PORTTH&=~MCF_GPIO_PORTTH_PORTTH1
#define CCD_AN1_CLK_1       MCF_GPIO_PORTTE|= MCF_GPIO_PORTTE_PORTTE2
#define CCD_AN1_CLK_0		MCF_GPIO_PORTTE&=~MCF_GPIO_PORTTE_PORTTE2  //A2



/// 拨码开关
#define SW1                  !(MCF_GPIO_SETTF&MCF_GPIO_SETTF_SETTF2)//A10
#define SW2                  !(MCF_GPIO_SETTF&MCF_GPIO_SETTF_SETTF3)//A11
#define SW3                  !(MCF_GPIO_SETTF&MCF_GPIO_SETTF_SETTF4)//A12
#define SW4                  !(MCF_GPIO_SETTF&MCF_GPIO_SETTF_SETTF5)//A13
#define SW5                  !(MCF_GPIO_SETTF&MCF_GPIO_SETTF_SETTF6)//A14
#define SW6                  !(MCF_GPIO_SETTH&MCF_GPIO_SETTH_SETTH4)//D4
#define SW7                  !(MCF_GPIO_SETTH&MCF_GPIO_SETTH_SETTH5)//D5
#define SW8                  !(MCF_GPIO_SETTH&MCF_GPIO_SETTH_SETTH6)//D6



#define KEY1_ON              !(MCF_GPIO_SETTE & MCF_GPIO_SETTE_SETTE6)//A6
#define KEY2_ON              !(MCF_GPIO_SETTF & MCF_GPIO_SETTF_SETTF1)//A9


//外部中断标志位
#define Clear_IRQ3            (MCF_EPORT_EPFR |= MCF_EPORT_EPFR_EPF5)

//定时器开关
#define EnablePIT(number)   (MCF_PIT_PCSR(number)|=0x0001)
#define DisablePIT(number)  (MCF_PIT_PCSR(number)&=~(0x0001))

//车体状态
#define Go 1
#define Wait 10
#define Stop 2


void gpio_init(void);

#endif

