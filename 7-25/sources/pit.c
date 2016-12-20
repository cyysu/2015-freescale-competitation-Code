#include"pit.h"

void EPORT_init(void)
{
	//����ѡ��
	MCF_GPIO_PNQPAR = MCF_GPIO_PNQPAR_IRQ1_IRQ1
				     |MCF_GPIO_PNQPAR_IRQ3_IRQ3
				     |MCF_GPIO_PNQPAR_IRQ5_IRQ5
				     |MCF_GPIO_PNQPAR_IRQ7_IRQ7;
	//������ʽ���½��ش���
	MCF_EPORT_EPPAR = MCF_EPORT_EPPAR_EPPA1_FALLING
				 	 |MCF_EPORT_EPPAR_EPPA3_FALLING
				 	 |MCF_EPORT_EPPAR_EPPA5_FALLING
				 	 |MCF_EPORT_EPPAR_EPPA7_FALLING;
	//����Ĵ��������ݷ���Ϊ����			 	
	MCF_EPORT_EPDDR =(uint8)~MCF_EPORT_EPDDR_EPDD1
					 &~MCF_EPORT_EPDDR_EPDD3
					 &~MCF_EPORT_EPDDR_EPDD5
					 &~MCF_EPORT_EPDDR_EPDD7;
	//IRQ�ж�ʹ�ܼĴ������ж�ʹ��
    MCF_EPORT_EPIER =MCF_EPORT_EPIER_EPIE1
					|MCF_EPORT_EPIER_EPIE3
					|MCF_EPORT_EPIER_EPIE5
					|MCF_EPORT_EPIER_EPIE7;
	//״̬(����ģʽʱ��ӳ������״̬)			 	
	MCF_EPORT_EPDR = MCF_EPORT_EPDR_EPD1
	  			    |MCF_EPORT_EPDR_EPD3
	  			    |MCF_EPORT_EPDR_EPD5
	  			    |MCF_EPORT_EPDR_EPD7;
	//�жϱ�־λ����  			 
	MCF_EPORT_EPFR = MCF_EPORT_EPFR_EPF1
				    |MCF_EPORT_EPFR_EPF3
				    |MCF_EPORT_EPFR_EPF5
				    |MCF_EPORT_EPFR_EPF7;				   
	//�ж�ʹ��			   
	MCF_INTC0_IMRL&=~MCF_INTC_IMRL_MASKALL;
	MCF_INTC0_IMRL&=~MCF_INTC_IMRL_INT_MASK1 
				   &~MCF_INTC_IMRL_INT_MASK3
				   &~MCF_INTC_IMRL_INT_MASK5
				  &~MCF_INTC_IMRL_INT_MASK7;
	//�������ȼ�			   
	MCF_INTC0_ICR01=MCF_INTC_ICR_IP(5)+MCF_INTC_ICR_IL(4);
	MCF_INTC0_ICR03=MCF_INTC_ICR_IP(5)+MCF_INTC_ICR_IL(5);
	MCF_INTC0_ICR05=MCF_INTC_ICR_IP(5)+MCF_INTC_ICR_IL(3);
	MCF_INTC0_ICR05=MCF_INTC_ICR_IP(5)+MCF_INTC_ICR_IL(2);

}

void PIT0_init(void)
{
		
	MCF_PIT_PCSR(0)=MCF_PIT_PCSR_RLD
				   |MCF_PIT_PCSR_PIF
				   |MCF_PIT_PCSR_PIE
				   |MCF_PIT_PCSR_OVW
				   |MCF_PIT_PCSR_PRE(5);//at 80MHz
				   						 //(15-610Hz)(14-1220Hz)(13-4882Hz)
				   						 //(12-9765Hz)(11-19531Hz)(10-39062Hz)(9-78125Hz)
				  // |MCF_PIT_PCSR_DBG;
				   //|MCF_PIT_PCSR_DOZE
				   
	MCF_PIT_PMR(0)=(uint16)1250;//1ms 

	MCF_INTC0_IMRL&=~MCF_INTC_IMRL_MASKALL;
	MCF_INTC0_IMRH&=~MCF_INTC_IMRH_INT_MASK55;//PIT0
	MCF_INTC0_ICR55=MCF_INTC_ICR_IP(2)+MCF_INTC_ICR_IL(2);//PIT0
	
	MCF_PIT_PCSR(0)|=MCF_PIT_PCSR_EN;
}

void delayms(int ms)
{
   int ii,jj;
   if (ms<1) ms=1;
   for(ii=0;ii<ms;ii++)     
   for(jj=0;jj<6676;jj++)
   {
   	
   }
}

void PIT1_init()
{		
	MCF_PIT_PCSR(1)=MCF_PIT_PCSR_RLD
				   |MCF_PIT_PCSR_PIF
				   |MCF_PIT_PCSR_PIE
				   |MCF_PIT_PCSR_OVW
				   |MCF_PIT_PCSR_PRE(5);//fPIT=fsys/2/2^PER
				   						 //at 80MHz
												//0- 40000000Hz
												//1- 20000000Hz
												//2- 10000000Hz
												//3- 5000000Hz
												//4- 2500000Hz -0.4us
												//5- 1250000Hz
												//6- 625000Hz
												//7- 312500Hz
												//8- 156250Hz
												//9- 78125Hz   -12.8us
												//10-39062.5Hz
												//11-19531.25Hz
												//12-9765.625Hz
												//13-4882.8125Hz
												//14-2441.40625Hz
												//15-1220.703125Hz
				   //|MCF_PIT_PCSR_DBG; 
				   //|MCF_PIT_PCSR_DOZE				   
	MCF_PIT_PMR(1)=6250;//��ʱ5����
	MCF_INTC0_IMRL&=~MCF_INTC_IMRL_MASKALL;
	MCF_INTC0_IMRH&=~MCF_INTC_IMRH_INT_MASK56;//PIT1	
	MCF_INTC0_ICR56=MCF_INTC_ICR_IP(6)+MCF_INTC_ICR_IL(6);//PIT1	
	MCF_PIT_PCSR(1)|=MCF_PIT_PCSR_EN;
}
/*
void PIT1_start()
{

	MCF_PIT_PCSR(1)|=MCF_PIT_PCSR_EN;
}

void PIT1_stop(void)
{

	MCF_PIT_PCSR(1)&=~MCF_PIT_PCSR_EN;
}
*/