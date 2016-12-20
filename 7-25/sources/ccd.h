#ifndef CCD_H_
#define CCD_H_
#include <stdio.h>
#include "support_common.h"

///////////////////////////////////////////

#define ZHONGXIN				   60//63
#define TargetPixelAverageVoltage  40  //自调适应曝光    
#define TargetPixelAverageVoltageAllowError  3
//////////////////////////////////////
extern uint32 gpixel[128];
extern uint16 IntegrationTime;
extern int16  PixelAverageVoltage;
extern int16 RoadWidth;
extern int16 currentline;
extern int16 midline[30];	//midline值偏小，车体偏左；midline偏大，车体偏右
extern int16 rightline[30];
extern int16 leftline[30];
///////////////////////////////////////////
extern int16 siqu;
extern int16 fangdaqu;
extern int16 fangdaxishu;
extern int16 buchangqu;
///////////////////////////////////////////
extern int16 RoadState;
extern int16 RoadState1;
extern float pian_cha;
extern float pian_cha_1;
//////////////////////////////////////////////////////////////
int16 strfindl (int16 *str,uint16 rage);
int16 strfindr (int16 *str,uint16 rage);
int16 FindMid  (int16 *str,uint16 rage);
void linefind  (uint32 *pixel);
void CCD_IO_Init(void);
void ccd_clear(); //清除一次CCD
void ccd_get(uint32 * ImageData);
void CCD_display (void);
void CalculateIntegrationTime(uint32 *pixel);
void delay_us(int us);
/*
Roadstate1 = a十字
			 m单线
			 z直角
			 n正常
RoadState  = l左
			 r右
			 n正常
*/
#endif