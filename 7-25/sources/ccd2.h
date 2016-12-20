#ifndef CCD2_H_
#define CCD2_H_
#include <stdio.h>
#include "support_common.h"

///////////////////////////////////////
#define ZHONGXIN_2        64
#define TargetPixelAverageVoltage_2	38;
#define TargetPixelAverageVoltageAllowError_2  3
////////////////////////////////////////////

extern int16  pian_cha_2;
extern int16  road;
extern int16  roadstate;
extern int16  zhangstate;
extern int16  RoadWidth_2;
extern uint32 gpixel_2[128];
extern uint16 IntegrationTime_2;
extern int16  PixelAverageVoltage_2;
/////////////////////////////////////////////
void linefind_2(uint32 *pixel);
int16 strfindl_2 (int16 *str,uint16 rage);
int16 strfindr_2 (int16 *str,uint16 rage);
//////////////////////////////////////////
void ccd_clear_2(); //清除一次CCD
void ccd_get_2(uint32 * ImageData);   //读取一次CCD
void ccd_display_2();    //用于串口显示
uint32 PixelAverage_2(uint16 len, uint32 *data);
void CalculateIntegrationTime_2(uint32 *pixel);


#endif