#include"gpt.h"
void GPT_init(void)//��5�����һ�������������ֵ
{	
	MCF_GPT_GPTSCR1 = 0x00;//gptϵͳ����1
	MCF_GPIO_PTAPAR |= MCF_GPIO_PTAPAR_ICOC3_ICOC3;//��GPT3�������ó�GPTģ�������
	MCF_GPT_GPTDDR &=~0x8;//��GPT3�������ó�ΪGPTģ�������
	MCF_GPT_GPTSCR1 |= MCF_GPT_GPTSCR1_GPTEN;//GPTʹ��
//					|MCF_GPT_GPTSCR1_TFFCA;����������

	MCF_GPT_GPTSCR2_PR(3);//gptϵͳ����2
	MCF_GPT_GPTIOS=0x00;//����Ϊ���벶׽
	MCF_GPT_GPTCTL2|=0x80;//�½��ز�׽
	MCF_GPT_GPTPACTL=0//�½��ؼ�����ʱ��Ϊ��ʱ��ʱ�ӣ��������ж�
			|MCF_GPT_GPTPACTL_PAE;//�����ۼ�ʹ��
//			|MCF_GPT_GPTPACTL_CLK_PACLK_256;
//			|MCF_GPT_GPTPACTL_CLK_PACLK_65536 ;//65536��Ƶ
	
	MCF_GPT_GPTCNT=0X0000;//�������������
}