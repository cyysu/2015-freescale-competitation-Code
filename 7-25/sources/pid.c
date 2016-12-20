#include "pid.h"


//PID参数初始化
void IncPIDInit(void)
{
	sptr->SumError = 0;
	sptr->LastError = 0;  //Error[-1]
	sptr->PrevError = 0;  //Error[-2]
	sptr->Proportion = 0; //比例常数 
	sptr->Integral = 0;   //积分常数
	sptr->Derivative = 0; //微分常数 
	sptr->SetPoint = 0;
}












