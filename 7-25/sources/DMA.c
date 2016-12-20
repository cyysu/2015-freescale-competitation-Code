#include "DMA.h"

char Pix_Data[1];
//MCF52255����·DMA Timer,��˵�������������壬Ҳ����˵�����������٣�
//ԭ���ǽ���������ΪDMA Timer��ʱ��Դ�����½���32λ��DTIN�Ĵ������һ

//-------------------------------------------------------------------------*
//������DMA���������ʼ��                                                  *
//��  ��: �������                                                         *
//��  ��:��                                                                *
//��  ��:��                                                                *
//-------------------------------------------------------------------------*  
void DMA_init(void)
{

	//����TC�� 0 1 ΪDMA��ʱ����        
	MCF_GPIO_PTCPAR |= MCF_GPIO_PTCPAR_DTIN1_DTIN1|MCF_GPIO_PTCPAR_DTIN3_DTIN3; 
	
	MCF_DTIM_DTMR(1)=0;
	MCF_DTIM_DTMR(3)=0;
	
	//����DTMģʽ�Ĵ���
	MCF_DTIM_DTMR(1)|= MCF_DTIM_DTMR_CE_NONE //�����в�׽
	                                        |MCF_DTIM_DTMR_CLK_DTIN //�ⲿʱ��Դ
	                                        |MCF_DTIM_DTMR_FRR;//�����¼�֮�����ֵ����
	
	MCF_DTIM_DTMR(3)|= MCF_DTIM_DTMR_CE_NONE //�����в�׽
	                                        |MCF_DTIM_DTMR_CLK_DTIN //�ⲿʱ��Դ
	                                        |MCF_DTIM_DTMR_FRR;//�����¼�֮�����ֵ����
   
	MCF_DTIM_DTRR(1) = 0xFFFF;			    //��������׼ֵ,16λ,���ԼƵ�0xFFFF   GAFF
	MCF_DTIM_DTRR(3) = 0xFFFF;			    //��������׼ֵ,16λ,���ԼƵ�0xFFFF   GAFF
	MCF_DTIM1_DTCN   = 0x00;				//���������
	MCF_DTIM3_DTCN   = 0x00;				//���������

	MCF_DTIM_DTMR(1) |= MCF_DTIM_DTMR_RST;
	MCF_DTIM_DTMR(3) |= MCF_DTIM_DTMR_RST;

}   
     
//-------------------------------------------------------------------------*
//������:��ȡDMA������� ����ֵ    1                                       *
//��  ��:                                                                  *
//��  ��:��                                                                *
//��  ��:����ֵ                                                            *
//-------------------------------------------------------------------------*  
uint32 GET_count1(void)
{
  uint32 count1;
  count1 = (uint32)MCF_DTIM1_DTCN;
  MCF_DTIM1_DTCN = 0x00;
  return count1;        
}
//-------------------------------------------------------------------------*
//������:����ֵ��ʼ��    1                                       		   *
//��  ��:                                                                  *
//��  ��:��                                                                *
//��  ��:����ֵ                                                            *
//-------------------------------------------------------------------------* 
void left_dma_counter_init(void)
{
	MCF_GPIO_PTCPAR |= MCF_GPIO_PTCPAR_DTIN1_DTIN1;
	MCF_DTIM_DTMR(1) = 0;//����STMR�Ĵ���
	MCF_DTIM_DTMR(1) = MCF_DTIM_DTMR_CE_RISE
	              	  |MCF_DTIM_DTMR_CLK_DTIN;
	MCF_DTIM_DTER(1) |= MCF_DTIM_DTER_CAP;//���ز�׽����
	MCF_DTIM_DTMR(1) |= MCF_DTIM_DTMR_RST;
}

//-------------------------------------------------------------------------*
//������:��ȡDMA������� ����ֵ    3                                       *
//��  ��:                                                                  *
//��  ��:��                                                                *
//��  ��:����ֵ                                                            *
//-------------------------------------------------------------------------*  
uint32 GET_count3(void)
{
  uint32 count3;
  count3 = (uint32)MCF_DTIM3_DTCN;
  MCF_DTIM3_DTCN = 0x00;
  return count3 ;        
}

//-------------------------------------------------------------------------*
//������:����ֵ��ʼ��    3                                       		   *
//��  ��:                                                                  *
//��  ��:��                                                                *
//��  ��:����ֵ                                                            *
//-------------------------------------------------------------------------*  
void right_dma_counter_init(void)
{

	MCF_GPIO_PTCPAR |= MCF_GPIO_PTCPAR_DTIN3_DTIN3;
	MCF_DTIM_DTMR(3) = 0;//����STMR�Ĵ���
	MCF_DTIM_DTMR(3) = MCF_DTIM_DTMR_CE_RISE
	                  |MCF_DTIM_DTMR_CLK_DTIN;
	MCF_DTIM_DTER(3)|=MCF_DTIM_DTER_CAP;//���ز�׽����
	MCF_DTIM_DTMR(3)|=MCF_DTIM_DTMR_RST;
}




















