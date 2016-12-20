#ifndef PID_H_
#define PID_H_

//���ݽṹ
typedef struct PID
{
	int SetPoint; //�趨Ŀ�� Desired Value
	long SumError; //����ۼ�
	double Proportion; //�������� Proportional Const
	double Integral; //���ֳ��� Integral Const
	double Derivative; //΢�ֳ��� Derivative Const
	int LastError; //Error[-1]
	int PrevError; //Error[-2]
} PID;

static PID sPID;
static PID *sptr = &sPID;
//PID������ʼ��
void IncPIDInit(void);


#endif