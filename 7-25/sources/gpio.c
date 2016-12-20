#include "gpio.h"
//// ��������ķ���
void gpio_init(void)
{
	
	/**
			IO�ڵ����õ�һ�����: �ж�ĳ�Ĵ����е���һ���� ----> ��Ӧ��Ƭ���е�ĳһ����
				1.ȷ���˿ں�
				2.���ù���(PAR)
				3.�˿����ݵ����뻹�����(DDR)
				4.�˿�����Ĵ����������˿������״̬�� PORT
				5.��������빦�ܵĻ�  ��ôͨ������ SET ���Զ�ȡ����ܽŵ�״̬
				
			Example��
				1) ����TC�ڵ�RUNpin����ΪGPIO����
				TC�����ĸ����ù��ܣ����ݡ��������üĴ������ı�̷�����TC�ڵ�ÿ�����Ź��ܾ��嶨��Ϊ���ֹ��ܣ���TC���������üĴ���PTCPAR�е���Ӧ��λ�������ڱ���Ĺ���ʵ���У�PTCPAR�����ϡ�MCF_GPIO_��ǰ׺�����MCF_GPIO_PTCPAR��������ʾTC���������üĴ����������Ĵ������ơ�
				MCF_GPIO_PTCPAR &= ~((0x03)<<(2*( RUNpin ))) //����TC.RUNpinΪGPIO
				
				2) ����TC�ڵ�RUNpin����Ϊ���
				MCF_GPIO_DDRTC |= (0x01<<RUNpin) //����TC. RUNpinΪ���
			
				3) ��TC��RUNpin�����������/�͵�ƽ
				MCF_GPIO_PORTTC |= (0x01<<RUNpin) //TC. RUNpin=1(�ߵ�ƽ)
				MCF_GPIO_PORTTC &= ~(0x01<< RUNpin) // TC. RUNpin=0(�͵�ƽ)
			
				4) ����TC��RUNpin����Ϊ���벢��ȡRUNpin����״̬
				MCF_GPIO_DDRTC &= ~(0x01<<RUNpin) //����TC. RUNpinΪ����
				value = MCF_GPIO_SETTC &(0x01<< RUNpin) //��ȡTC. RUNpin״̬	
			
	
	**/
	MCF_GPIO_PTEPAR = 0x00;//����TE�˿�Ϊgpio����//������ͷ
	MCF_GPIO_PTFPAR = 0x00;//����TF�˿�Ϊgpio����//���뿪��
	MCF_GPIO_PTHPAR = 0x00;
	MCF_GPIO_PUCPAR = 0x00;
	MCF_GPIO_PQSPAR = 0x00;
	
	MCF_GPIO_DDRTE |=  MCF_GPIO_DDRTE_DDRTE3; // A3   ccd2�ӿ�        					            
	MCF_GPIO_DDRTE |=  MCF_GPIO_DDRTE_DDRTE1; // A1
	  
	MCF_GPIO_DDRTH |=  MCF_GPIO_DDRTH_DDRTH1; // D3
	MCF_GPIO_DDRTE |=  MCF_GPIO_DDRTE_DDRTE2; // A2
	
	
	
	MCF_GPIO_DDRUC |= MCF_GPIO_DDRUC_DDRUC3;  	//������
		
	MCF_GPIO_DDRTG |= MCF_GPIO_DDRTG_DDRTG0;
	MCF_GPIO_DDRTG |= MCF_GPIO_DDRTG_DDRTG1;
	MCF_GPIO_DDRTG |= MCF_GPIO_DDRTG_DDRTG2;             					            
	MCF_GPIO_DDRTG |= MCF_GPIO_DDRTG_DDRTG3;              
	MCF_GPIO_DDRTF |= MCF_GPIO_DDRTF_DDRTF7;//A16~A19Ϊ5110�Ŀ��ƿ�

    MCF_GPIO_DDRNQ &=~MCF_GPIO_DDRNQ_DDRNQ3;	//IRQ3�����ź�
	
	MCF_GPIO_DDRTF |= MCF_GPIO_DDRTF_DDRTF0;	//A8
	
	MCF_GPIO_DDRTH &=~ MCF_GPIO_DDRTH_DDRTH4;	//D4
	MCF_GPIO_DDRTH &=~ MCF_GPIO_DDRTH_DDRTH5;	//D4
	
	MCF_GPIO_DDRTE &=~ MCF_GPIO_DDRTE_DDRTE6;	//A6
   	MCF_GPIO_DDRTF &=~ MCF_GPIO_DDRTF_DDRTF1;	//A6
    //R_GPT_COUNT_OFF;
    //L_GPT_COUNT_OFF;//���������	
 } 