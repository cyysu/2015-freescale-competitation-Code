#include "ccd.h"
#include "ccd2.h"
#include "gpio.h"
#include "uart.h"
#include "adc.h"
#include "MCF52259.H"

uint16 IntegrationTime=10; 
int16 currentline;
int16 lastcurrentline;
int16 midline[30]   = {64};	//midline值偏小，车体偏左；midline偏大，车体偏右
int16 leftline[30]  = {38};   	//车体向左移动leftline值增加
int16 rightline[30] = {38};
float pian_cha=0;
float pian_cha_1=0;
uint32 gpixel[128] = {0};
int16 RoadWidth = 0,RoadState = 0,RoadState1=0;
int16 PixelAverageVoltage=0;
int16 	siqu=8,//6,
		fangdaqu=18,
		fangdaxishu=3.18,//3.4,//2.8,
		buchangqu=24;
#define LINEWETH        					 10
#define ROADWETH        					 70
#define ERZHI           					 170
#define TargetLineError  	 				 6  //找线时最大误差
#define MAXTIME_TSL      				  	 20  //单位为1ms
#define MINTIME_TSL     					 3   //单位为1ms
////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void linefind(uint32 *pixel)
{
	int16 i = 0,judgepian_cha=0;
	 
    int16  lpixel[128],rpixel[128];
    static uint8 Count=0;
         
      currentline++;
      if(currentline>=30)
      {
      	currentline = 0;
        lastcurrentline=29;	
      }
      else
        lastcurrentline=currentline-1;

	for(i=0;i<128;i++)
	{
            rpixel[127-i] = *(pixel+i);
            lpixel[i]     = *(pixel+i);	
	}

    if((RoadState1 =='a')||(RoadState1=='m')||RoadState =='l'||RoadState =='r')
    {
        midline [currentline] = FindMid (rpixel,78);
        if( midline [currentline] != 0xfc )
        {
              leftline [ currentline ]  = 128-midline[currentline]-RoadWidth/2;
              rightline[ currentline ]  =  midline[currentline]-RoadWidth/2;
              pian_cha_1 = midline [currentline ] - ZHONGXIN ;
              RoadState1 = 'm';
              return;
        }
    }
    if(leftline[lastcurrentline] > 40)
    {

                  leftline[currentline]  = strfindl(lpixel,60);
                  rightline[currentline] = 0xfc;
    }
    else if(rightline[lastcurrentline] > 40)
    {

                  rightline[currentline] = strfindr(rpixel,60);
                  leftline[currentline] = 0xfc;
    }
    else
    {
                  leftline[currentline]  = strfindl(lpixel,60);
                  rightline[currentline] = strfindr(rpixel,60);
    }
 //////////////////////////////////////////////////////////////////////////   
    if((leftline [currentline ] == 0xfc) && (rightline [currentline ] != 0xfc))			 //左边线丢失
    {
                 RoadState = 'l';
                 leftline [currentline ] = 128 - rightline [currentline ] - RoadWidth ;//我们可以在这里检测直角弯
                 Count = 0;
    }
    else if((rightline [currentline ] == 0xfc) && (leftline [currentline ] != 0xfc))	        //右边线丢失
    {
                RoadState = 'r';
                rightline [currentline ] = 128 - leftline [currentline ] - RoadWidth ;
                Count = 0;
    }
    else if((leftline [currentline ] == 0xfc)&&(rightline [currentline ] == 0xfc))	//左右边线全丢失，全黑或全白
    {
                leftline  [currentline ]  = leftline  [lastcurrentline ];
                rightline [currentline ]  = rightline [lastcurrentline ];

                if((leftline [currentline ] < 60) && (rightline [currentline ] < 60))           //十字弯处全白，RoadState ong1赋值为a
                          RoadState1 = 'a';
                
               Count = 0;
   }
   else																																							//左右都未丢失
   {
              Count++;
              if(Count >= 3)
              {
                    Count = 3;
                    RoadState = 'n';
              }
              if(RoadState == 'n')
                RoadWidth = 128 - rightline[currentline] - leftline[currentline];
              if(RoadState == 'r')
                rightline[currentline] = 128 - leftline[currentline] - RoadWidth;
              if(RoadState == 'l')
                leftline[currentline] = 128 - rightline[currentline] - RoadWidth;
              RoadState1 = 'n';
   }
   
   if((leftline [currentline ] + rightline [currentline]) > 90)
   {
      leftline  [currentline ] =leftline  [lastcurrentline ];
      rightline [currentline ] =rightline [lastcurrentline ];
   }

	   midline  [currentline ] = (128 - leftline [currentline ] + rightline [currentline ])/2 ;	
	   pian_cha_1 = midline[currentline] - ZHONGXIN;
	   
	
/*				if(pian_cha_1<0)
				{
					judgepian_cha=1;
					pian_cha_1*=-1;
				}
	
	   if(pian_cha_1<(siqu-3))
	   		pian_cha_1 = pian_cha_1;
	   
	   else if(pian_cha_1<	(siqu+6))
	   		pian_cha_1= ((3+6*fangdaxishu)/9)*(pian_cha_1-siqu+3)+ siqu -3;
	   
	   else if(pian_cha_1<fangdaqu)
	   		pian_cha_1 = fangdaxishu*( pian_cha_1 - siqu)+siqu;
	   
	   else if(pian_cha_1 < buchangqu)
	   		pian_cha_1 = ((buchangqu-fangdaxishu*(fangdaqu-siqu)-siqu)/(buchangqu-fangdaqu))*(pian_cha_1-fangdaqu)+fangdaxishu*(fangdaqu - siqu)+siqu;
	   
	   else
	   		pian_cha_1=pian_cha_1;
	   
				if(judgepian_cha==1)
					pian_cha_1*=-1;*/
					
				   
}

int16 strfindl (int16 *str,uint16 rage)
{ 
  int16 i,j=0,k,p,n,diff=0,diff_max=0,position[8]={0},positionL,e[8]={0},error=0;
  static int16 LastPostionL = 35,count=0;
  if(RoadState1 == 'a' || RoadState1=='m'||RoadState1=='z')

        LastPostionL = leftline[lastcurrentline];


  p = 18 + LastPostionL;         
  if(p > 90)
    p = 90;

  n = LastPostionL - 30;
  if(n < 18)
    n = 18;

  for(i = n; i <= p; i++)
  {
      diff = *(str + i + 7) - *(str+i); 

      if(diff > rage)
      {
            for(k = i;k < (i+8); k++)
            {
                diff = *(str + k + 4) - *(str + k);
                if(diff >= diff_max)
                {
                    position[j] = k;
                    diff_max = diff;
                }
            }
            j++;
            i = i + 10;  
            diff_max = 0;
      }

      if(j >= 8)
            break;
  }
  if(j == 0) 
     return 0xfc;


  for(i=0;i<j;i++)
  {
      e[i] = position[i] - LastPostionL;
      if(e[i] < 0)
            e[i] = -e[i];
  }

      positionL = position[0];
    for(i=0;i<(j-1);i++)
    {
      if(e[i+1] < e[i])
        positionL = position[i+1];
    }

  error = positionL - LastPostionL;    
  if(error < 0)
    error = -error;


  if(error <= TargetLineError) 
  {
          LastPostionL = positionL;
          count = 0;
          return positionL;
  }
  else
  {
          if(error <= (TargetLineError + count * 2))
        {
            LastPostionL = positionL;
            return positionL;
        }

        if(RoadState1 == 'a' || RoadState1=='m'||RoadState1=='z')
        {
            return positionL;
        }

        count++;
        if(count > 5)
            count = 5;
        return 0xfc;
  }
}


int16 strfindr (int16 *str,uint16 rage)
{
    int16 i,j=0,k,p,n,diff=0,diff_max=0,position[8]={0},positionL,e[8]={0},error=0;
          static int16 LastPostionL = 35,count=0;

   if(RoadState1 == 'a' || RoadState1=='m'||RoadState1=='z')
        LastPostionL = rightline[lastcurrentline ];


    p = 18+LastPostionL;
    if(p > 90)
      p = 90;

    n = LastPostionL-30;
    if(n < 18)
      n = 18;

    for(i=n; i<=p; i++)//here
    {
      diff = *(str+i+7) - *(str+i);
      if(diff > rage)
      {
        for(k=i;k < (i+8); k++)
        {
          diff = *(str+k+4) - *(str+k);
          if(diff >= diff_max)
          {
            position[j] = k;
            diff_max = diff;
          }
        }
        j++;
        i = i + 10;
        diff_max = 0;
      }
      if(j >= 8)
        break;
    }

    if(j == 0)
      return 0xfc;

    for(i=0;i<j;i++)
    {
      e[i] = position[i] - LastPostionL;
      if(e[i] < 0)
        e[i] = -e[i];
    }

      positionL = position[0];
    for(i=0;i<(j-1);i++)
    {
      if(e[i+1] < e[i])
        positionL = position[i+1];
    }

    error = positionL - LastPostionL;
    if(error < 0)
      error = -error;


    if(error <= TargetLineError)
    {
      LastPostionL = positionL;
      count = 0;
      return positionL;
    }
    else
    {
      if(error <= (TargetLineError + count*2))
      {
        LastPostionL = positionL;
        return positionL;
      }
      if(RoadState1 == 'a' || RoadState1=='m'||RoadState1=='z')
      {
        return positionL;
      }
      count++;
      if(count > 5)
        count = 5;
      return 0xfc;
    }
}

int16 FindMid (int16 *str,uint16 rage)
{
  int16 i,j=0,k,p,n,diff=0,diff_max=0,position[8]={0},positionL,e[8]={0},error=0,get=0;
  int16 LastPostionL ;//LastPostionL可改

  LastPostionL = midline[lastcurrentline];
  
  p = 16 + LastPostionL;          //这里的30可能需要改一下
  if(p > 95)
    p = 95;
  n = LastPostionL - 16;
  if(n < 30)
    n = 30;
  /***************************************************************************************/
  for(i = n; i <= p; )//可以进行从两边找中线
  {
      diff = *(str + i + 5) - *(str+i);
      if(diff > rage)  //相邻像素点大于rage时   需要进行精确处理  也就是左边线就在这个里面 需要把当前的像素点位置存储在 position数组里面
      {
            for(k = i;k < (i+4); k++)
            {
                diff = *(str + k + 1) - *(str + k);
                if(diff >= diff_max)
                {
                    position[j] = k;
                    diff_max = diff;
                }
            }
            j++;                //跳过这8个像素点
            diff_max = 0;
      }
      i+=2;
      if(j >= 1)
            break;
  }
  /*我们现在找到了j个跳变沿，开始判断*/
  if(j == 0)  //相邻的像素点相差不多
     return 0xfc;
  positionL = position[0];
  /****************************************************************************************/
    n=positionL-15;
    p=positionL;
  for(i = n; i <= p;)//可以进行从两边找中线
  {
      diff = *(str + i ) - *(str+i+ 5);     //相邻的7个像素点

      if(diff > rage)  //相邻像素点大于rage时   需要进行精确处理  也就是左边线就在这个里面 需要把当前的像素点位置存储在 position数组里面
      {
          get=1;
          break ;
      }
      i+=2;
  }
  if(get==0)
    return 0xfc;
  else
    return (positionL-3);

}
/////////////////////////srevo/////////////////////////////////
////////////////////////////////////////////////////////////////
void CCD_IO_Init(void) 
{
	CCD_AN0_CLK_0;
    CCD_AN0_SI_0;
    CCD_AN1_CLK_0;
    CCD_AN1_SI_0;
}
void CCD_display (void)
{	
		int16 c;
		unsigned char i=0;
		int16 k[128];
		for(c=0;c<128;c++)
		{
		k[c]=gpixel[c];
		}
	  
	  for(i=0; i<128; i++)
	  {
	    if(k[i]>=0xFF)
	      k[i] = 0xFE;        //遇到FF用FE替换即可
	      uart0_putchar(k[i]);
	  }
	  uart0_putchar(255);
}

void delay_us(int us)
{
	int a1,b1;
	if(us<1) us=1;
	for(a1=0;a1<us;a1++)
	for(b1=0;b1<3;b1++)
	{
		
	}//约为1微秒
}

void ccd_clear(void) //初始条件
{

	uint8 i;
    CCD_AN1_SI_1;         // SI  = 1 
    CCD_AN1_CLK_1;        // CLK = 1 
    CCD_AN1_SI_0;         // SI  = 0 
    CCD_AN1_CLK_0;        // CLK = 0 
    for(i=0; i<127; i++) 
    {
        CCD_AN1_CLK_1;    // CLK = 1 
        __asm(nop);
        __asm(nop);
        CCD_AN1_CLK_0;    // CLK = 0 
        __asm(nop);
        __asm(nop);
    }
    CCD_AN1_CLK_1;        // CLK = 1 
    __asm(nop);
    __asm(nop);
    CCD_AN1_CLK_0;        // CLK = 0 
}

void ccd_get(uint32 * ImageData)
{
	uint32 i;
    uint16 temp_int;
    CCD_AN1_CLK_1;        /* CLK = 1 */
    CCD_AN1_SI_0;         /* SI  = 0 */
    delay_us(30);
    	temp_int = ADonce(1);
    	*ImageData++ = (uint8)(temp_int>>4);
    CCD_AN1_CLK_0;        /* CLK = 0 */
    for(i=0; i<127; i++) 
    {		
        CCD_AN1_CLK_1;    /* CLK = 1 */
        __asm(nop);
        __asm(nop);
        temp_int = ADonce(1);       
        *ImageData++ = (uint8)(temp_int>>4);
        __asm(nop);
        __asm(nop);
        CCD_AN1_CLK_0;    /* CLK = 0 */
        __asm(nop);
        __asm(nop);
    }
    CCD_AN1_CLK_1;        /* CLK = 1 */
    __asm(nop);
    __asm(nop);
    CCD_AN1_CLK_0;        /* CLK = 0 */
}

uint32 PixelAverage(uint16 len,uint32 *data)
{
  uint8 i;
  uint32 sum = 0;
  for(i = 0; i < 128; i++)
  {
    sum = sum + *data++;
  }
  return (sum/len);
}


void CalculateIntegrationTime(uint32 *pixel)
{
int16 PixelAverageValue=0,PixelAverageVoltageError=0;
    PixelAverageValue = PixelAverage(128,pixel);
    PixelAverageVoltage = PixelAverageValue * 16 / 64;
    PixelAverageVoltageError = PixelAverageVoltage - TargetPixelAverageVoltage;
    if(PixelAverageVoltageError > TargetPixelAverageVoltageAllowError)
        IntegrationTime--;
    if(PixelAverageVoltageError < -TargetPixelAverageVoltageAllowError)
        IntegrationTime++;
    if(IntegrationTime >= MAXTIME_TSL)
        IntegrationTime = MAXTIME_TSL;
    if(IntegrationTime <= MINTIME_TSL)
        IntegrationTime = MINTIME_TSL;
}
 