#include"adc.h"

void ADinit (void) //AD转换模块初始化
{

    //1.将引脚AN(0--7)配置为ADC转换功能                           
        //MCF_GPIO_PANPAR = 0xFFFF;
    	MCF_GPIO_PANPAR= MCF_GPIO_PANPAR_AN0_AN0  //CCD1
				   		|MCF_GPIO_PANPAR_AN1_AN1  //CCD2
				   		|MCF_GPIO_PANPAR_AN2_AN2
				   		|MCF_GPIO_PANPAR_AN3_AN3
					    |MCF_GPIO_PANPAR_AN4_AN4 //加速度计
					    |MCF_GPIO_PANPAR_AN5_AN5 //光电对管
				    	|MCF_GPIO_PANPAR_AN6_AN6
					    |MCF_GPIO_PANPAR_AN7_AN7;//光电对管

    //2.循环顺序扫描模式,AN0-7设为单端输入,禁止中断,停止转换
    MCF_ADC_CTRL1 =  0b0101000000000011;
                  //    ||||||||||| |||___SMODE=2,循环顺序扫描
                  //    |||||||||||_______CHNCFG=0,8路ANn都设为单端输入  
                  //    |||||||___________HLMTIE=0,禁止超上限中断
                  //    ||||||____________LLMTIE=0,禁止超下限中断
                  //    |||||_____________ZCIE=0,禁止过零中断
                  //    ||||______________EOSIE0=0,禁止转换完成中断
                  //    |||_______________SYNC0=1,由SYNC0输入或写START0启动扫描
                  //    ||________________START0=0,未启动扫描
                  //    |_________________STOP0=1,停止转换
    //3.ADC时钟频率5MHz
    MCF_ADC_CTRL2 = 0b0000000000100011;
                  //             |||||____DIV=40,ADC时钟频率2MHz 
                  //                      (fBUS=80MHz,fAD=fBUS/((DIV+1)*2=2MHz)
    //4.转换器A和B和参考电压电路上电,上电延时10个ADC时钟周期
    MCF_ADC_POWER = 0b0000000010100100;
                  //  |     ||||||||||____PD0=0,转换器A上电
                  //  |     |||||||||_____PD1=0,转换器B上电
                  //  |     ||||||||______PD2=1,参考电压电路上电依赖于转换器A/B
                  //  |     |||||||_______APD=0,禁止自动掉电
                  //  |     ||||||________PUDELAY=10,上电延时为10个ADC时钟周期     
                  //  |___________________ASB=0,禁止自动低功耗模式
    //5.使用内部参考电压VRH和VRL
    MCF_ADC_CAL   = 0b0000000000000000;
                  //  ||__________________SEL_VREFH=0,SEL_VREFL=0
                  //                      使用内部参考电压VRH和VRL
    
    //6.清停止0位,STOP0=0
    MCF_ADC_CTRL1 &= 0xBFFF;
    
    //7.过零控制禁止 即转换结果和上一次转换结果有符号变化
	MCF_ADC_ADZCC=0;
	
	//8.使能SAMPLEn采样槽			  
	MCF_ADC_ADSDIS=0;
	
	//9.偏移量寄存器为0  结果寄存器为无符号型
	MCF_ADC_ADOFS(0)=0X0000;
	
    //10.等待转换器A上电完成
    while (MCF_ADC_POWER & MCF_ADC_POWER_PSTS0);
    //11.等待转换器B上电完成
    while (MCF_ADC_POWER & MCF_ADC_POWER_PSTS1);
    //12.向START0写1,启动扫描
    MCF_ADC_CTRL1 |= 0x2000; 
    
    return;  
}
/**
	ANn 表示的是第几路模拟AD口
**/
uint16 ADonce(uint16 ANn) //12位精度采集某路模拟量的AD值
{
    uint16 result;
    //等待数据准备好
    while ((MCF_ADC_ADSTAT & (1 << ANn))==0);
    //取得结果
    result = (MCF_ADC_ADRSLT(ANn) & 0x7FF8) >> 3;
    return result;
}

