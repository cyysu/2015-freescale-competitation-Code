#include "pid.h"


//PID������ʼ��
void IncPIDInit(void)
{
	sptr->SumError = 0;
	sptr->LastError = 0;  //Error[-1]
	sptr->PrevError = 0;  //Error[-2]
	sptr->Proportion = 0; //�������� 
	sptr->Integral = 0;   //���ֳ���
	sptr->Derivative = 0; //΢�ֳ��� 
	sptr->SetPoint = 0;
}












