#include "DMA.h"

char Pix_Data[1];
//MCF52255有四路DMA Timer,据说可以用来计脉冲，也就是说可以用来测速，
//原理是将脉冲设置为DMA Timer的时钟源，在下降沿32位的DTIN寄存器会加一

//-------------------------------------------------------------------------*
//函数名DMA脉冲计数初始化                                                  *
//功  能: 脉冲计数                                                         *
//参  数:无                                                                *
//返  回:无                                                                *
//-------------------------------------------------------------------------*  
void DMA_init(void)
{

	//设置TC口 0 1 为DMA定时功能        
	MCF_GPIO_PTCPAR |= MCF_GPIO_PTCPAR_DTIN1_DTIN1|MCF_GPIO_PTCPAR_DTIN3_DTIN3; 
	
	MCF_DTIM_DTMR(1)=0;
	MCF_DTIM_DTMR(3)=0;
	
	//设置DTM模式寄存器
	MCF_DTIM_DTMR(1)|= MCF_DTIM_DTMR_CE_NONE //不进行捕捉
	                                        |MCF_DTIM_DTMR_CLK_DTIN //外部时钟源
	                                        |MCF_DTIM_DTMR_FRR;//触发事件之后计数值清零
	
	MCF_DTIM_DTMR(3)|= MCF_DTIM_DTMR_CE_NONE //不进行捕捉
	                                        |MCF_DTIM_DTMR_CLK_DTIN //外部时钟源
	                                        |MCF_DTIM_DTMR_FRR;//触发事件之后计数值清零
   
	MCF_DTIM_DTRR(1) = 0xFFFF;			    //计数器基准值,16位,可以计到0xFFFF   GAFF
	MCF_DTIM_DTRR(3) = 0xFFFF;			    //计数器基准值,16位,可以计到0xFFFF   GAFF
	MCF_DTIM1_DTCN   = 0x00;				//清零计数器
	MCF_DTIM3_DTCN   = 0x00;				//清零计数器

	MCF_DTIM_DTMR(1) |= MCF_DTIM_DTMR_RST;
	MCF_DTIM_DTMR(3) |= MCF_DTIM_DTMR_RST;

}   
     
//-------------------------------------------------------------------------*
//函数名:获取DMA脉冲计数 计数值    1                                       *
//功  能:                                                                  *
//参  数:无                                                                *
//返  回:计数值                                                            *
//-------------------------------------------------------------------------*  
uint32 GET_count1(void)
{
  uint32 count1;
  count1 = (uint32)MCF_DTIM1_DTCN;
  MCF_DTIM1_DTCN = 0x00;
  return count1;        
}
//-------------------------------------------------------------------------*
//函数名:计数值初始化    1                                       		   *
//功  能:                                                                  *
//参  数:无                                                                *
//返  回:计数值                                                            *
//-------------------------------------------------------------------------* 
void left_dma_counter_init(void)
{
	MCF_GPIO_PTCPAR |= MCF_GPIO_PTCPAR_DTIN1_DTIN1;
	MCF_DTIM_DTMR(1) = 0;//重置STMR寄存器
	MCF_DTIM_DTMR(1) = MCF_DTIM_DTMR_CE_RISE
	              	  |MCF_DTIM_DTMR_CLK_DTIN;
	MCF_DTIM_DTER(1) |= MCF_DTIM_DTER_CAP;//边沿捕捉触发
	MCF_DTIM_DTMR(1) |= MCF_DTIM_DTMR_RST;
}

//-------------------------------------------------------------------------*
//函数名:获取DMA脉冲计数 计数值    3                                       *
//功  能:                                                                  *
//参  数:无                                                                *
//返  回:计数值                                                            *
//-------------------------------------------------------------------------*  
uint32 GET_count3(void)
{
  uint32 count3;
  count3 = (uint32)MCF_DTIM3_DTCN;
  MCF_DTIM3_DTCN = 0x00;
  return count3 ;        
}

//-------------------------------------------------------------------------*
//函数名:计数值初始化    3                                       		   *
//功  能:                                                                  *
//参  数:无                                                                *
//返  回:计数值                                                            *
//-------------------------------------------------------------------------*  
void right_dma_counter_init(void)
{

	MCF_GPIO_PTCPAR |= MCF_GPIO_PTCPAR_DTIN3_DTIN3;
	MCF_DTIM_DTMR(3) = 0;//重置STMR寄存器
	MCF_DTIM_DTMR(3) = MCF_DTIM_DTMR_CE_RISE
	                  |MCF_DTIM_DTMR_CLK_DTIN;
	MCF_DTIM_DTER(3)|=MCF_DTIM_DTER_CAP;//边沿捕捉触发
	MCF_DTIM_DTMR(3)|=MCF_DTIM_DTMR_RST;
}




















