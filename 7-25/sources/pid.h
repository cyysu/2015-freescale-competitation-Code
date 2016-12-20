#ifndef PID_H_
#define PID_H_

//数据结构
typedef struct PID
{
	int SetPoint; //设定目标 Desired Value
	long SumError; //误差累计
	double Proportion; //比例常数 Proportional Const
	double Integral; //积分常数 Integral Const
	double Derivative; //微分常数 Derivative Const
	int LastError; //Error[-1]
	int PrevError; //Error[-2]
} PID;

static PID sPID;
static PID *sptr = &sPID;
//PID参数初始化
void IncPIDInit(void);


#endif