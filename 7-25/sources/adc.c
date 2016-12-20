#include"adc.h"

void ADinit (void) //ADת��ģ���ʼ��
{

    //1.������AN(0--7)����ΪADCת������                           
        //MCF_GPIO_PANPAR = 0xFFFF;
    	MCF_GPIO_PANPAR= MCF_GPIO_PANPAR_AN0_AN0  //CCD1
				   		|MCF_GPIO_PANPAR_AN1_AN1  //CCD2
				   		|MCF_GPIO_PANPAR_AN2_AN2
				   		|MCF_GPIO_PANPAR_AN3_AN3
					    |MCF_GPIO_PANPAR_AN4_AN4 //���ٶȼ�
					    |MCF_GPIO_PANPAR_AN5_AN5 //���Թ�
				    	|MCF_GPIO_PANPAR_AN6_AN6
					    |MCF_GPIO_PANPAR_AN7_AN7;//���Թ�

    //2.ѭ��˳��ɨ��ģʽ,AN0-7��Ϊ��������,��ֹ�ж�,ֹͣת��
    MCF_ADC_CTRL1 =  0b0101000000000011;
                  //    ||||||||||| |||___SMODE=2,ѭ��˳��ɨ��
                  //    |||||||||||_______CHNCFG=0,8·ANn����Ϊ��������  
                  //    |||||||___________HLMTIE=0,��ֹ�������ж�
                  //    ||||||____________LLMTIE=0,��ֹ�������ж�
                  //    |||||_____________ZCIE=0,��ֹ�����ж�
                  //    ||||______________EOSIE0=0,��ֹת������ж�
                  //    |||_______________SYNC0=1,��SYNC0�����дSTART0����ɨ��
                  //    ||________________START0=0,δ����ɨ��
                  //    |_________________STOP0=1,ֹͣת��
    //3.ADCʱ��Ƶ��5MHz
    MCF_ADC_CTRL2 = 0b0000000000100011;
                  //             |||||____DIV=40,ADCʱ��Ƶ��2MHz 
                  //                      (fBUS=80MHz,fAD=fBUS/((DIV+1)*2=2MHz)
    //4.ת����A��B�Ͳο���ѹ��·�ϵ�,�ϵ���ʱ10��ADCʱ������
    MCF_ADC_POWER = 0b0000000010100100;
                  //  |     ||||||||||____PD0=0,ת����A�ϵ�
                  //  |     |||||||||_____PD1=0,ת����B�ϵ�
                  //  |     ||||||||______PD2=1,�ο���ѹ��·�ϵ�������ת����A/B
                  //  |     |||||||_______APD=0,��ֹ�Զ�����
                  //  |     ||||||________PUDELAY=10,�ϵ���ʱΪ10��ADCʱ������     
                  //  |___________________ASB=0,��ֹ�Զ��͹���ģʽ
    //5.ʹ���ڲ��ο���ѹVRH��VRL
    MCF_ADC_CAL   = 0b0000000000000000;
                  //  ||__________________SEL_VREFH=0,SEL_VREFL=0
                  //                      ʹ���ڲ��ο���ѹVRH��VRL
    
    //6.��ֹͣ0λ,STOP0=0
    MCF_ADC_CTRL1 &= 0xBFFF;
    
    //7.������ƽ�ֹ ��ת���������һ��ת������з��ű仯
	MCF_ADC_ADZCC=0;
	
	//8.ʹ��SAMPLEn������			  
	MCF_ADC_ADSDIS=0;
	
	//9.ƫ�����Ĵ���Ϊ0  ����Ĵ���Ϊ�޷�����
	MCF_ADC_ADOFS(0)=0X0000;
	
    //10.�ȴ�ת����A�ϵ����
    while (MCF_ADC_POWER & MCF_ADC_POWER_PSTS0);
    //11.�ȴ�ת����B�ϵ����
    while (MCF_ADC_POWER & MCF_ADC_POWER_PSTS1);
    //12.��START0д1,����ɨ��
    MCF_ADC_CTRL1 |= 0x2000; 
    
    return;  
}
/**
	ANn ��ʾ���ǵڼ�·ģ��AD��
**/
uint16 ADonce(uint16 ANn) //12λ���Ȳɼ�ĳ·ģ������ADֵ
{
    uint16 result;
    //�ȴ�����׼����
    while ((MCF_ADC_ADSTAT & (1 << ANn))==0);
    //ȡ�ý��
    result = (MCF_ADC_ADRSLT(ANn) & 0x7FF8) >> 3;
    return result;
}

