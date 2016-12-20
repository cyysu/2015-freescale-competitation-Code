#include "ccd2.h"
#include "ccd.h"
#include "gpio.h"
#include "uart.h"  
#include "adc.h"
#include "MCF52259.H"

int16 pian_cha_2;
int16 road='n';
int16 roadstate='n';
int16 RoadWidth_2 = 0;
int16 zhangstate='n';
uint16 IntegrationTime_2=16;
int16 PixelAverageVoltage_2=0;
int16 midline_2=64;	//midline值偏小，车体偏左；midline偏大，车体偏右
int16 leftline_2=32;   	//车体向左移动leftline值增加
int16 rightline_2=32;
int16 lastleftline_2 =32;   	//车体向左移动leftline值增加
int16 lastrightline_2=32;
uint32 gpixel_2[128] = {0};

/////////////////////////////////////////////////////
#define MAXTIME_TSL_2     35  //单位为1ms
#define MINTIME_TSL_2     2   //单位为1ms
#define ROADWETH_2        50
////////////////////////////////////////////////////

void ccd_clear_2(void) //初始条件
{

	uint8 i;
    CCD_AN0_SI_1;         // SI  = 1 
    __asm(nop);
    __asm(nop);
    CCD_AN0_CLK_1;        // CLK = 1 
    __asm(nop);
    __asm(nop);
    CCD_AN0_SI_0;         // SI  = 0
    __asm(nop);
	__asm(nop); 
    CCD_AN0_CLK_0;        // CLK = 0 
    __asm(nop);
    __asm(nop);
    for(i=0; i<127; i++) 
    {
        CCD_AN0_CLK_1;    // CLK = 1 
        __asm(nop);
        __asm(nop);
        CCD_AN0_CLK_0;    // CLK = 0 
        __asm(nop);
        __asm(nop);
    }
    CCD_AN0_CLK_1;        // CLK = 1 
    __asm(nop);
    __asm(nop);
    CCD_AN0_CLK_0;        // CLK = 0 
}

void ccd_get_2(uint32 * ImageData)
{
	uint32 i;
    uint16 temp_int;
    CCD_AN0_CLK_1;        /* CLK = 1 */
    CCD_AN0_SI_0;         /* SI  = 0 */
    delay_us(30);
    	temp_int = ADonce(0);
    	*ImageData++ = (uint8)(temp_int>>4);
    CCD_AN0_CLK_0;        /* CLK = 0 */
    for(i=0; i<127; i++) 
    {		
        CCD_AN0_CLK_1;    /* CLK = 1 */
        __asm(nop);
        __asm(nop);
        temp_int = ADonce(0);       
        *ImageData++ = (uint8)(temp_int>>4);
        __asm(nop);
        __asm(nop);
        CCD_AN0_CLK_0;    /* CLK = 0 */
        __asm(nop);
        __asm(nop);
    }
    CCD_AN0_CLK_1;        /* CLK = 1 */
    __asm(nop);
    __asm(nop);
    CCD_AN0_CLK_0;        /* CLK = 0 */
}
void ccd_display_2()
{
	  unsigned char i=0;
	  for(i=0; i<128; i++)
	  {
	    if(gpixel_2[i]>=0xFF)
	      gpixel_2[i] = 0xFE;        //遇到FF用FE替换即可
	      uart0_putchar(gpixel_2[i]);
	  }
	  uart0_putchar(255);
}

uint32 PixelAverage_2(uint16 len,uint32 *data)
{
  uint8 i;
  uint32 sum = 0;
  for(i = 0; i < 128; i++)
  {
    sum = sum + *data++;
  }
  return (sum/len);
}


void CalculateIntegrationTime_2(uint32 *pixel)
{
	int16 PixelAverageValue_2=0,PixelAverageVoltageError_2= 0;
    PixelAverageValue_2 = PixelAverage_2(128,pixel);
    PixelAverageVoltage_2 = PixelAverageValue_2 * 16 / 64;
    PixelAverageVoltageError_2 = PixelAverageVoltage_2 - TargetPixelAverageVoltage_2;
    if(PixelAverageVoltageError_2 > TargetPixelAverageVoltageAllowError_2)
        IntegrationTime_2--;
    if(PixelAverageVoltageError_2 < -TargetPixelAverageVoltageAllowError_2)
        IntegrationTime_2++;
    if(IntegrationTime_2 >= MAXTIME_TSL_2)
        IntegrationTime_2 = MAXTIME_TSL_2;
    if(IntegrationTime_2 <= MINTIME_TSL_2)
        IntegrationTime_2 = MINTIME_TSL_2;
}
 
int16 strfindl_2 (int16 *str,uint16 rage)
{
    int16 i,j=0,get=0,getzhang=0,jump=0,max=0,line=0,zhange;
    static int16 count=0,zhanglineold=0;
	for(i=16;i<108;i++)
	{
		  if((str[i+5] - str[i])> rage)
		  {
		      get = 1;
		      line = i+3;
		      break;
		  }
	}
	if(get)
	{
		for(i=line;i<line+18;i++)
		{
			if((str[i] - str[i+4])> rage)
			{
					getzhang = 1;
					break;	
			}
		}	
	}
	if(getzhang && RoadState1 == 'n')
	{
		count++;
		if(count==1)
			zhanglineold = i+3;
		if(count>=3)
		{
			zhange = i-zhanglineold;
			if(zhange<13&&zhange>-13)
			{
				zhangstate='l';	
				zhanglineold=0;
			}
		}
	      	
	}
	else
		count = 0;
////////////////////////////////////////
	if(get==0)
	        return 0;
	else
	        return line;

}


int16 strfindr_2 (int16 *str,uint16 rage)
{
    int16 i,j=0,get=0,getzhang=0,jump=0,max=0,line=0,zhange;
    static int16 count=0,zhanglineold=0;
	for(i=16;i<108;i++)
	{
		  if((str[i+5] - str[i])> rage)
		  {
		      get = 1;
		      line = i+3;
		      break;
		  }
	}
	if(get)
	{
		for(i=line;i<line+18;i++)
		{
			if((str[i] - str[i+4])> rage)
			{
					getzhang = 1;
					break;	
			}
		}	
	}
	if(getzhang && RoadState1 == 'n')
	{
		count++;
		if(count==1)
			zhanglineold = i+3;
		if(count>=2)
		{
			zhange = i-zhanglineold;
			if(zhange<13&&zhange>-13)
			{
				zhangstate='r';	
				zhanglineold=0;
			}
		}
	      	
	}
	else
		count = 0;
////////////////////////////////////////
	if(get==0)
	        return 0;
	else
	        return line;

}


void linefind_2(uint32 *pixel)
{
  	uint8 i;
    int16   lpixel[128] ={0},rpixel[128] = {0};
	for(i=0;i<128;i++)                                                                  //这个地方需要思考下
	{
            rpixel[127-i] = *(pixel+i);
            lpixel[i]     = *(pixel+i);
	}
   leftline_2  = strfindl_2 (lpixel,70);
   rightline_2 = strfindr_2 (rpixel,70);
   /************************此处可加对于边线的正确判断***************/
      /***********************防止出现不正常现象*****************************/
   //对于上次分析出的由于中线出弯的误判可能同样可以由此解决
   
   if(leftline_2 + rightline_2>120 && leftline_2 + rightline_2<135)//danxian
   {
   		road='a';
   		zhangstate = 'n';	
   }
   if(leftline_2 + rightline_2 >= 135)		//十字出弯
   {	
	     if (RoadState == 'r')
	     {
	    	 rightline_2 = 0;
	    	 RoadWidth_2 = 65;	
	     }
	     else if (RoadState == 'l')
	     {
	     	 leftline_2  = 0;
	     	 RoadWidth_2 = 65;	
	     }
	     else
	     {
	     	road = 'a';
	     	return;
	     }
	          
	     zhangstate='n';
   }
   //////////////////////////////////////////
   if((leftline_2 == 0) && (rightline_2 != 0))
   {
            leftline_2 = 128 - rightline_2 - RoadWidth_2;
            midline_2  = (128- leftline_2 + rightline_2)/2 ;
            roadstate='l';
            road='n';
   }
     else if((rightline_2 == 0) && (leftline_2 != 0))
    {
            rightline_2 = 128 - leftline_2 - RoadWidth_2 ;
            midline_2  = (128- leftline_2 + rightline_2)/2 ;
            roadstate='r';
            road='n';
    }
    else if((leftline_2 == 0)&&(rightline_2  == 0))//单线或十字
    {
          road='a';
    }
    else																																							//左右都未丢失
    {
	      RoadWidth_2 = 128 - leftline_2 - rightline_2 ;
	      midline_2  = (128- leftline_2 + rightline_2)/2 ;
	      roadstate='n';
	      road='n';
    }
    
    if(RoadWidth_2<30||RoadWidth_2>80)
    	road='a';
          
    lastleftline_2  =  leftline_2;
    lastrightline_2 =  rightline_2;
    pian_cha_2 =  midline_2 - ZHONGXIN_2;
}


