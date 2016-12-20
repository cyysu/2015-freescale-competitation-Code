#include "pwm.h"
/*
	PWM���Ƴ���ı�дһ�㰴�����µ�һ�����̣�

		1����ֹPWMģ�飻//�������ڸı����ں�����Ȳ�����Ҫ��PWM��ֹ������²��ܱ�����

		2��PWM����ѡ���Ƿ���ͨ��67,45,23,01��//��൥��ʹ��8��8λ�ͼ���ʹ��4��16λ

		3����ͨ��ѡ��ʱ��Դ����λ��//0,1,4,5ͨ����ѡ��ClockA��ClockSA��2,3,6,7ͨ����ѡ��ClockB��ClockSB

		4����ʱ��ԴA\BԤ��Ƶ��//�ɶ�����ʱ�ӽ���Ԥ��Ƶ��ȷ��ClockA��ClockB������1,2,4,8,16,32,64,128��8����Ƶ��

		5������ʱ��ԴA\Bȷ��ʱ��ԴSA\SB��//��ClockA��ClockB����Ƶ��ֵ��ȷ��ClockA��ClockB������1-255�ķ�Ƶ��

		6��������Ե�ѡ��//Ҳ����ѡ����������ȵͺ�߻����ȸߺ��

		7�����뷽ʽ��ѡ��//������Ϊ���������м���뷽ʽ

		8��ʵ��ͨ��Ƶ�ʵļ��㣻//Ҳ�������ڵ��趨

		9��ռ�ձȼĴ��������ã�//ռ�ձȳ������趨�������Դ˾���ռ�ձ�

		10��ʹ��PWMģ�顣

*/

void PWM_init(void)
{
	//function choose  ����pwm����
	MCF_GPIO_PTCPAR = MCF_GPIO_PTCPAR_DTIN0_PWM0
					 |MCF_GPIO_PTCPAR_DTIN2_PWM4;

	MCF_GPIO_PTAPAR |= MCF_GPIO_PTAPAR_ICOC0_PWM1
				  	|  MCF_GPIO_PTAPAR_ICOC2_PWM5;


    //pwm Polarity Register 
	MCF_PWM_PWMPOL = MCF_PWM_PWMPOL_PPOL1
					|MCF_PWM_PWMPOL_PPOL5;
	
	//pwm Clock select register:1-SA or SB  0-A or B
	///��ͨ��ѡ����SCLKA ���� SCLKBʱ��
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
	
	//pwm control register   ����ѡ��			

	MCF_PWM_PWMCTL=   MCF_PWM_PWMCTL_CON01 //1000  --->  10khz  0.1us һ��
					 |MCF_PWM_PWMCTL_CON45;//					

	/**
		����뷽ʽ��������PWMCNT��0��ʼ��ʱ���źŵ�����������PWMCNT = PWMDTYʱ
		�Ƚ���1�����Ч����������λ�������ƽ��ת����PWMCNT = PWMPERʱ���Ƚ���2�����Ч
		��������λ�������ƽ��ת��ͬʱPWMCNT��λ��һ�����ڽ�����
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
//�ҵ��ת�ٺ���  ICO2
//0-1000
//500-1000��  500min  1000max    
//500-0��    500min  0max
//////////////////////
void PWM_right(int16 x)//youcuowu
{
	MCF_PWM_PWMDTY(4)=(x>>8);
	MCF_PWM_PWMDTY(5)=(x&0x00ff);
}
//////////////////////
//����ת�ٺ��� ICO0
//500-1000��  500min  1000max    
//500-0��    500min  0max
//////////////////////
void PWM_left(int16 x)
{
	MCF_PWM_PWMDTY(0)=(x>>8);
	MCF_PWM_PWMDTY(1)=(x&0x00ff);
}


