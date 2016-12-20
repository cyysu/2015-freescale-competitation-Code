#include"gpt.h"
void GPT_init(void)//过5毫秒读一次脉冲计数器的值
{	
	MCF_GPT_GPTSCR1 = 0x00;//gpt系统设置1
	MCF_GPIO_PTAPAR |= MCF_GPIO_PTAPAR_ICOC3_ICOC3;//将GPT3引脚设置成GPT模块的引脚
	MCF_GPT_GPTDDR &=~0x8;//将GPT3引脚设置成为GPT模块的引脚
	MCF_GPT_GPTSCR1 |= MCF_GPT_GPTSCR1_GPTEN;//GPT使能
//					|MCF_GPT_GPTSCR1_TFFCA;不快速清零

	MCF_GPT_GPTSCR2_PR(3);//gpt系统设置2
	MCF_GPT_GPTIOS=0x00;//设置为输入捕捉
	MCF_GPT_GPTCTL2|=0x80;//下降沿捕捉
	MCF_GPT_GPTPACTL=0//下降沿计数，时钟为计时器时钟，不触发中断
			|MCF_GPT_GPTPACTL_PAE;//脉冲累加使能
//			|MCF_GPT_GPTPACTL_CLK_PACLK_256;
//			|MCF_GPT_GPTPACTL_CLK_PACLK_65536 ;//65536分频
	
	MCF_GPT_GPTCNT=0X0000;//脉冲计数器清零
}