#include "include.h"


/************************************************** 
*  ����˵��: CodeFire �����  
*
*		
*		��־ģ��: 2015-7-5  2015��7��10�� 13:10:25
*		������ �ٶ�P�޷� �����޷� �ֱ��� 800 400	  	  
*		�ȽϺ��ʵ��ٶ�P I D		��P�޷�֮�� ���� ��ʱ������̫�����ǣ�
*       P   6.5
*       I   0.001  
*       ֱ��P 
*       P  200 
*       D  5.8  ��D����6ʱ ��ֹʱ ����΢����
*
*
**************************************************/

/*********��־����ر���*********/  
int16     ge  = 0,shi  = 0,bai  = 0,qian  = 0,wan  = 0;
int16 	  Ccd_clear = 0,temp2 = 0;
int16	  PWM_Test_variable1 = 0,PWM_Test_variable2 = 0,PWM_Test_variable3 = 0,Ccd_clear2 = 0;
int16     z_flag = 0,z_delay = 0,z_r = 0,z_l = 0,done = 0,Car_Go = 0,Car_Stand_Debug,temp5;
int16     up_flag=0,down_flag=0;
int       Condition_car = Wait;
int		  Time_1ms 		    = 0;
uint16    Judge_Ground1=0,Judge_Ground2=0;
int16	  DeBug=1;
///////////////////////////////////////////////////////////
int16	  z_pian_cha=60,//35,
		  z_time=70,
		  Z_DELAY=0;
int16	  zhang_pian_cha=18,//�ϰ��ߵ���ʱ��
		  zhang_time=200,	//�ϰ�ƫ��
		  zhang_bili=2.5;	
int16	  up_time=100;
//siqu=0,fangdaqu=0,fangdaxishu=0,buchangqu=0;
/*********ֱ������ر���*********/
#define   ERROR				  500
#define   DANGLE_P		      0.07          //��ѹ�ͽ��ٶȵı���ϵ��
int16     g_fgyro_get       = 0;    
int16     g_fangle_get      = 0; 
int16     g_fangle_once     = 0;
int16     Direction_gyro    = 0;            //�����ǵ������
int32     g_angle 			= 0;			//���ٶȼƷ���   
float     ANGLE_P 			= 0.08867;//0.09783;      //0.09���ٶȼƵı���ֵ  
float     GYROSCOPE_ANGLE   = 0.004;        //�ǶȻ���ʱ��    0.004  
float     g_fCar_Anglespeed = 0; 
float     g_fCar_Angle      = 0; 
float     g_fcarangle_I     = 0;
int16     angle             = 0;
float     g_gyro_x 			= 0;
float     gyro_offset_z          = -310;
float     g_gyro_y          = 0;
#define   TIME                1.8           //����ʱ�䳣��//1.35 //1.8
#define SPEED_CONTROL_PERIOD	80 	
#define OPTICAL_ENCODE_CONSTANT 500         //����������//
#define CAR_SPEED_CONSTANT 1000.0/SPEED_CONTROL_PERIOD/OPTICAL_ENCODE_CONSTANT      //��λת������ֵ

//// ��Ҫ�䶯�Ĳ���
//ֱ�� P  D
//  P 200
//	D 6    ��D����6ʱ ����΢����
float     L3G4200_P 		= 0.03;//0.04;//0.0126;//�����ǵı���ֵ
int16     angle_offset      = -375;//-389;//-415;//�Ƕ����ֵ   
int16     gyro_offset_x     = -160;//-340;      	//ֱ�������Ǿ�ֹ���ֵ 
float     P_angle           = 200;//200;//200;//240;//180;//156;//150;//130;//200;//80;         //ֱ��P    ----> ��Ҫ�����Ĳ���
float     D_angle           = 3;//5.8;//		   //ֱ��D    ----> ��Ҫ�����Ĳ���
/*********�ٶȵ���ر���*********/  
#define   ANGLE_CONTROL_OUT_MAX           30000             
#define   ANGLE_CONTROL_OUT_MIN           -30000      
#define   Integral_MAX				  	  1000
#define   MOTOR_OUT_DEAD_VAL_R	          0					
#define   MOTOR_OUT_DEAD_VAL_L	          0				 
#define   CAR_ANGLE_SPEED_SET             0
#define   MOTOR_OUT_MAX                   3500
#define   MOTOR_OUT_MIN                   0
float     g_fLeftMotorOut 				= 0;
float     g_fRightMotorOut 				= 0;
float     CAR_ANGLE_SET					= 0;
float     g_fAngleControlOut			= 0;
float	  gf_SpeedControlOut 			= 0;		
float  	  gf_Left_DirectionControlout	= 0;		
float     gf_Right_DirectionControlout	= 0;	
float  	  gf_Left_GPT					= 0;	//�ɼ��������ҵ��������
float	  gf_Right_GPT					= 0;	//�ɼ�����������������
float     gf_CarSpeed 					= 0;	//�ɼ�������������
float	  gf_CarSpeed_n 				= 0;	//�����ĳ���
float	  gn_SpeedControlPeriod 		= 0;	//�ٶȿ��Ƽ���
float	  g_nDirectionControlPeriod 	= 0;	//������Ƽ���
int16     g_DetectionChange_Count		= 0;	//ģ�⿪�ؼ���
float	  gf_LeftMotorOut 				= 0;
float	  gf_RightMotorOut 				= 0;
float	  gf_SpeedControlIntegral		= 0;//���ٸ���ֵ��ʵ��ֵ��ֵ�Ļ���
float	  gf_SpeedControlOutOld			= 0,//��һ�ε��ٶȿ���ֵ�������ٶ�ƽ������
		  gf_SpeedControlOutNew			= 0;//��һ�ε��ٶȿ���ֵ�������ٶ�ƽ����?
uint32	  g_fLeftMotorPulseSigma		= 0;
uint32    g_fRightMotorPulseSigma		= 0;
uint32 	  leftpulse						= 0;
uint32 	  rightpulse					= 0;	
	
/// 1---0.1   ��Ҫ���ڵĲ�����PD����   P��������  D���������ֲ�	
//  
//��ֹʱ��I ��� �� 0.05
#define   SPEEDCONSTANT					0.5	
float     CAR_SPEED_SET					= -800;//-1000;
float     P_speed						= 1;//2;//2.4;//6.5;
float  	  I_speed						= 0;//5;//0.002;//0.002;//0.001;//0.004;//0.3;//0.015;//0.025;//0.05;//0.05;
float  	  D_speed   					= 0;//1.4;
float	  g_fSpeedControlIntegral       = 0;
/*********�������ر���*********/  
#define DIRECTION_CONTROL_PERIOD 		 4
float   
		gf_DirectionControlOut          = 0,	//ÿһ�εķ������ֵ�����ڷ���ƽ������
		gf_DirectionControlOut_OLD      = 0,	//��һ�εķ������ֵ�����ڷ���ƽ������
		gf_DirectionControlOut_NEW      = 0;	//��һ�εķ������ֵ�����ڷ���ƽ������
                                          //�����p���ܸ��ܴ� ������
float   Driection_P       			    = 110;//100;//93;  //����P -------> ��Ҫ�����Ĳ���
float   Driection_D1       		        = 4.8;//4;//3.5; 
float   Driection_D2       		        = 0; 
float   Driection_D3       		        = 0; 
float   linemid_old						= 0;
static float fDelta = 0,fDelta_old = 0;
float  fDelta_cha				   = 0;
int16  StopCarFlag;
float  g_nSpeedError[2] = {0,0};
/************************************************** 
*  ����˵��: CodeFire �����  
*
*  �༭ʱ��: 2015-7-7
*
*  �༭����: ��ɽ��ѧ
*
**************************************************/
int main(void)
{
    gpio_init();
	uart0_init(38400);   
	ADinit ();  
	CCD_IO_Init();
	PIT0_init();
//	PIT1_init();
	PWM_init();	
	init_i2c();
	IIC_Init_2();
	InitL3G4200D();
	Init_MMA8452();
	EPORT_init();
    DMA_init();
	EnableInterrupts;
	while(Condition_car --)
	{
		uart0_putchar('B');
	}
	Car_Go = 1;
	///�������ݲ������	
	while(1) 
	{
		//BELL_L;
	    B_key();	
	    protectCar();
	 //   printf_fun(pian_cha_1);
	   // PWM_left (2500);
	//   	 ADonce(4);
	//	PWM_right(2500);
//	   printf_fun(g_fangle_get);
//	   Serial_dis();
//	    uart0_putchar('\n');
//	    printf_fun(Judge_Ground2);
///		Serial_dis();
	

	}
	return 0;
}

/************С����������*************/
void protectCar()
{
	if(StopCarFlag > 50 && (PWM_Test_variable1<1000 && PWM_Test_variable2 <1000))
	{
	
				DisablePIT(0);
				PWM_left (2000);
				PWM_right(2000);
	}
}

/************����ֹͣ���*************/
void funcStopCar(void)
{		
	 
	    if(Condition_car == 10)
	    {
	    	Condition_car = 1;
	    	delay_us(30);
	    	if(Condition_car == 10)	
	    	{
	    		while(Condition_car --)
		    	{
		    		uart0_putchar('O');
		    		uart0_putchar('O');
		    	}
	    		for(;;)
				{
					DisablePIT(0);
					PWM_left (2000);
					PWM_right(2000);
				}	
	    	}
		    				
	    }
}

/*****************************************************************
*
* ===================��ɽ��ѧ��������ģ��======================
*
* ��������: void B_key(void)
*
* ����˵��: ���뿪��
*
* ��������:
*
* �������: ��
****************************************************************/
void B_key(void)
{
  		if(KEY1_ON)
  		{
  			DeBug=1;
  		}
		if(SW1)
  		{
  			
  			if(DeBug)
  				CCD_display ();  
  			else	;
  		}
  		if(SW2)
  		{
  			if(DeBug)
  				ccd_display_2();
  			else	;
  		}
  		if(SW3)
  		{
  			if(DeBug)
	  			{
	  				    CAR_SPEED_SET   = 0;
					    P_speed			= 0;
						I_speed			= 0;
						D_speed   		= 0;
						Driection_P		= 0;
						Driection_D1	= 0;
						Driection_D2	= 0;
	  			}
	  		else	;
  		}
  		if(SW4)
  		{
  			if(DeBug)
  				{
  						CAR_SPEED_SET = -1000;	
  						Driection_P   = 97;	
  						Driection_D1  = 3.5;		
  				}
  			else	;

  		}
  		if(SW5)
  		{
		//	printf_fun(PixelAverageVoltage);
		//	printf_fun(PixelAverageVoltage_2);
		//	printf_fun(IntegrationTime);
		//	printf_fun(IntegrationTime_2);
			
  		}
  		if(SW8)
  		{
  			funcStopCar();
  		}
}

/*****************************************************************
*
* ===================��ɽ��ѧ��������ģ��======================
*
* ��������: void AngleCalculate(void)
*
* ����˵��: ��һ��:  �Ƕȼ��㺯��
*
* ��������:
*
* �������: ��
****************************************************************/
void AngleCalculate(void)
{
    //���ٶȼ�
    //int j;
    //g_fangle_once = 0;
    //for(j=0;j<10;j++)  //10��
    //	g_fangle_once += ADonce(4);      
	//g_fangle_get   =(int16)(g_fangle_once/10);  

	g_fangle_get = Read_MMA8452_Z();  //���ٶȼƲɼ�(��ֵ�˲�)
	if(g_fangle_get > 20 || g_fangle_get <-900)	
		StopCarFlag++;

    //������
    g_fgyro_get    = 0;
    g_fgyro_get    = cai_x();	
}
/*****************************************************************
*
* ===================��ɽ��ѧ��������ģ��=======================
*
* ��������: void AngleControl()
*
* ����˵��: ��һ��:  �Ƕȿ���
*
* ��������:
*
* �������: ��
*****************************************************************/
void AngleControl(void)
{
    float value;
    angle = (int16)((g_fangle_get - angle_offset) * ANGLE_P); //  ANGLE_P = 180 / Zmax - Zmin   //���ٶȼƲ����ĽǶ�
    g_fCar_Anglespeed = (g_fgyro_get - gyro_offset_x) * L3G4200_P; //�������ǽ��ٶ�w
    g_fCar_Angle = g_fcarangle_I;   //�����ǻ���֮��ĽǶ�
    value = (angle - g_fCar_Angle) / TIME ;      //����ʱ��
    g_fcarangle_I += (g_fCar_Anglespeed + value) * GYROSCOPE_ANGLE;
}
/*****************************************************************
*
* ===================��ɽ��ѧ��������ģ��======================
*
* ��������: void AngleControlOutput(void)  //5us����
*
* ����˵��: �ڶ���:  ֱ�����ƺ���        PD�㷨
*
* ��������:
*
* �������: ��
****************************************************************/
void AngleControlOutput(void)  //5us����
{
    float fValue;   
    fValue = (CAR_ANGLE_SET - g_fCar_Angle) * P_angle +(CAR_ANGLE_SPEED_SET - g_fCar_Anglespeed) * D_angle;
    if(fValue >  ANGLE_CONTROL_OUT_MAX)     fValue =ANGLE_CONTROL_OUT_MAX;
    if(fValue <  ANGLE_CONTROL_OUT_MIN)     fValue =ANGLE_CONTROL_OUT_MIN;
    g_fAngleControlOut = fValue;
}
/*****************************************************************
*
* ===================��ɽ��ѧ��������ģ��======================
*
* ��������:  void Serial_dis(void)
*
* ����˵��:
*
* ��������: ��λ��������ʾ
*
* �������: ��
****************************************************************/
void Serial_dis(void)
{
   char a1=0,b1=0,c1=0,d1=0;
   a1=(char)(angle);             //���ٶȼƼ�����������
   b1=(char)(g_fCar_Angle);          //��ϳ����ĽǶ�
   c1=(char)(g_fCar_Anglespeed);         //�����ǵĽ��ٶ�
   uart0_putchar(255);
   uart0_putchar(a1);
   uart0_putchar(b1);
   uart0_putchar(c1);
   uart0_putchar(254);   
}
/*****************************************************************
*
* ===================��ɽ��ѧ��������ģ��======================
*
* ��������: void MotorOutput(void)
*
* ����˵��: ���߲�:     ���PWM���㺯��   ��    PWM������ú���
*
* ��������:
*
* �������: ��
****************************************************************/
void MoterOutput(void)
{
	float fLeft,fRight;
	if(Car_Go == 1){ 
		fLeft  = g_fAngleControlOut + gf_SpeedControlOut + gf_DirectionControlOut;
		fRight = g_fAngleControlOut + gf_SpeedControlOut - gf_DirectionControlOut;
	}else
	{
		fLeft  = g_fAngleControlOut;
		fRight = g_fAngleControlOut;
	}
	gf_LeftMotorOut  = fLeft;  //���ձ�Ȼ��Ӱ�����ٶ�
	gf_RightMotorOut = fRight; //���ձ�Ȼ��Ӱ�����ٶ�
	MotorOut();	
}

void MotorOut(void) 
{
    float fLeftVal, fRightVal;
    fLeftVal  = gf_LeftMotorOut; 
    fRightVal = gf_RightMotorOut;
	//�������ó���1000  �������0 ��ô���� �������ϴ������ֵ
	//�������ó���1000  ���С��0 ��ô���� ��������С�����ֵ
    if(fLeftVal > 0)   
    {
    	fLeftVal += MOTOR_OUT_DEAD_VAL_L;
    }    
    else if(fLeftVal < 0)   
    {
        fLeftVal -= MOTOR_OUT_DEAD_VAL_L;    
    }
    if(fRightVal > 0)  
    {
    	fRightVal += MOTOR_OUT_DEAD_VAL_R;
    } 
    else if(fRightVal < 0)  
    {
        fRightVal -= MOTOR_OUT_DEAD_VAL_R;
    }
    SetMotorVoltage(fLeftVal, fRightVal);
}

void SetMotorVoltage(float fLeftVoltage, float fRightVoltage) 
{
		PWM_Test_variable1 = fLeftVoltage  + 2000;
		PWM_Test_variable2 = fRightVoltage + 2000;
		if(PWM_Test_variable1 <= 0)
			PWM_Test_variable1 = 0;
		if(PWM_Test_variable2 <= 0)
			PWM_Test_variable2 = 0;
		if(PWM_Test_variable1  >= MOTOR_OUT_MAX) 
			PWM_Test_variable1  = MOTOR_OUT_MAX;
		if(PWM_Test_variable2  >= MOTOR_OUT_MAX) 
			PWM_Test_variable2  = MOTOR_OUT_MAX;
		PWM_left (PWM_Test_variable1);
		PWM_right(PWM_Test_variable2);	
} 

void P_check()
{
	static int16 count=0,delay=0;
	if(ADonce(4)<2800 && RoadWidth >= 78 && RoadWidth_2>60 && pian_cha_1 < 10 && pian_cha_2<7)
	{
		count++;
		if(count>28)
		{
			up_flag=1;
			uart0_putchar('u');			
		}

	}
	if(up_flag ==1 && RoadWidth < 48&& RoadWidth_2<25 && pian_cha_1 < 10 && pian_cha_2<7)
	{
		down_flag=1;
		uart0_putchar('u');
	}
	if(up_flag)
	{
	  	CAR_SPEED_SET   = 0;
		delay++;
		if(delay>up_time)
		{
			delay=0;
			up_flag=0;
		}
	}
}

void Z_check()
{
    static int16 count=0;
    Judge_Ground1  = ADonce(5);
    Judge_Ground2  = ADonce(7);

    if(Judge_Ground1 > 2700 && Judge_Ground2 > 2700 && RoadWidth < 85)
          count ++;
    else
      	  count = 0;
    if(count == 4)
    {
        if(z_flag==1||z_flag==2)
            z_flag = 0;
        else
            z_flag = 1;
    }
    if((roadstate == 'l' && RoadState == 'l')
         && z_flag == 1  && pian_cha_1<10 && pian_cha_1>-10)//��ֹ����
    {
            z_l = 1;
            z_delay = 1;
    }
    if((roadstate == 'r' && RoadState == 'r')
         && z_flag == 1  && pian_cha_1<10 && pian_cha_1>-10)
    {
            z_r = 1;
            z_delay = 1;
    }
    if(z_delay >= 1)
    {
       z_delay++;
    }
    if(z_delay >= Z_DELAY+2)
    {
    	RoadState1='z';
        if(z_l >= 1)
        {	
        	z_l ++;
        	if(z_l < z_pian_cha/8)
        		pian_cha = 8*z_l;
        	
        	else if(z_l <= z_time - z_pian_cha/8)
            	pian_cha = z_pian_cha;
        	
            else if(z_l <= z_time)
            	pian_cha = z_pian_cha - 8*z_l;
            
            else
            {
                z_l     = 0;
                z_delay = 0;
                z_flag  = 2;
            }
        }
        if(z_r >= 1)
        {	
        	z_r ++;
        	if(z_r < z_pian_cha/8)
        		pian_cha = (-8)*z_r;
        	
        	else if(z_r <= z_time - z_pian_cha/8)
            	pian_cha = -z_pian_cha;
        	
            else if(z_r <= z_time)
            	pian_cha = -(z_pian_cha - 8*z_r);
            
            else
            {
                z_r     = 0;
                z_delay = 0;
                z_flag  = 2;
            }
        }
     }
}

void ZHANG_DEAL()
{
	static int16 count10;
	if(zhangstate != 'n')	
	{
		count10++;
        ////////////////////////////////////////////
		if(count10<(zhang_pian_cha/zhang_bili))
			if(zhangstate=='l')	
				pian_cha-=zhang_bili * count10;
			else
				pian_cha+=zhang_bili * count10;

		else if(count10<zhang_time-(zhang_pian_cha/zhang_bili))
			if(zhangstate=='l')	
				pian_cha-=zhang_pian_cha;
			else
				pian_cha+=zhang_pian_cha;
			
		else if(count10<zhang_time)
			if(zhangstate=='l')	
				pian_cha-=zhang_pian_cha - zhang_bili*(count10-zhang_time-(zhang_pian_cha/zhang_bili)) ;
			else
				pian_cha+=zhang_pian_cha - zhang_bili*(count10-zhang_time-(zhang_pian_cha/zhang_bili)) ;
		else
			zhangstate = 'n';
	}
	else		count10=0;
}

void together()
{   
	static int16 coun=0;
		pian_cha = pian_cha_1;
    ///////////////////////////////////////////////////
    if(RoadState1 == 'a' && road == 'n' && RoadState!='m')
    {
       coun ++;
       if(coun>60)
           pian_cha = pian_cha_2;
    }
    else
       coun=0;
    
    if(pian_cha >= 60)
    	pian_cha = 65;
    if(pian_cha <-65)
    	pian_cha = -65;
 ////////////////////////////
 	ZHANG_DEAL();
 //	P_check();
    Z_check();
}

/*****************************�жϺ���***************************************/

__declspec(interrupt:0) void PIT0_handler(void) //1ms   PIT0 CCD�ع�ʱ��ļ���
{	    
static int16 ccd_new=1,ccd_getnew=0,ccd_new2=1,ccd_getnew2=0;
	    MCF_PIT_PCSR(0) |= MCF_PIT_PCSR_PIF;//���жϱ�־λ
	    Time_1ms++;
	    Ccd_clear++;
	    Ccd_clear2++;
	    
	    gn_SpeedControlPeriod++;
	    g_nDirectionControlPeriod++;            
	    SpeedControlOutput();              
	    DirectionControlOutput();
		together();
//////////////////////////////
	    if(Ccd_clear == IntegrationTime)	
	    {
	        CCD_AN1_SI_1;
	        ccd_getnew=1;
	    }
	    if(Ccd_clear2 == IntegrationTime_2)	
	    {
	       CCD_AN0_SI_1;
	       ccd_getnew2=1;
	    }
////////////////////////////////////////////////////////////////
	    if(Time_1ms == 1)
	    {
	        DMATimerGet();
	    	AngleCalculate();
	    	AngleControl();
	    	if(ccd_new==1)
	    	{
	    		ccd_clear();
	    	//	CalculateIntegrationTime(gpixel);
	    		Ccd_clear = 0;
	    		ccd_new=0;
	    	}
	    	if(ccd_new2==1)
	    	{
	    		ccd_clear_2();
	    //		CalculateIntegrationTime_2(gpixel_2);
	    		Ccd_clear2 = 0;
	    		ccd_new2=0;
	    	}	
	    }
	    else if(Time_1ms == 2)
	    {
				AngleControlOutput();
				MoterOutput();
	    }
	    else if(Time_1ms == 3)
	    {
	           if(ccd_getnew==1)
	           {
	           	ccd_get(gpixel);
	           	linefind(gpixel);
	           	ccd_getnew=0;
	           	ccd_new=1;
	           }
	    }
	    else if(Time_1ms == 4)
	    {
	    	  if(ccd_getnew2==1)
	    	  {
	           	ccd_get_2(gpixel_2);
	           	linefind_2(gpixel_2);
	           	ccd_getnew2=0;
	           	ccd_new2=1;	    	  	
	    	  }	
	    }
	    else if(Time_1ms == 5)
	    {	
	        temp2++;
            if(temp2 == 20)     
	          {
	          
	              SpeedControl();
	              gn_SpeedControlPeriod = 0;
	              temp2 = 0;
	          }   
            DirectionControl();
            g_nDirectionControlPeriod = 0;
			Time_1ms = 0;	
	    }
}
/// Ԥ��PIT1
__declspec(interrupt:0) void PIT1_handler(void) // 5ms
{	
        	MCF_PIT_PCSR(1) |= MCF_PIT_PCSR_PIF;//���жϱ�־λ   
}

/// �ⲿ�ж�
__declspec(interrupt:0) void EPORT_irq3_handler(void)
{
		Condition_car = Wait;		
		uart0_putchar('B');
		Clear_IRQ3;	
}


void DMATimerGet(void)
{
	/// ����	
	leftpulse  = GET_count3();
	/// ����
	rightpulse = GET_count1();
    g_fLeftMotorPulseSigma 	+= leftpulse;
    g_fRightMotorPulseSigma	+= rightpulse;
    leftpulse = 0;
    rightpulse = 0;		
}

/**
void SpeedControl(void)
{
	float fDelta,CarOld,CarNew,error,flag_0;
	float fP,fI_0,fD,oldgpt,newgpt;
	//newgpt = oldgpt;
	gf_CarSpeed = (float)(g_fLeftMotorPulseSigma * 0.5 + g_fRightMotorPulseSigma * 0.5);	
	
	if(gf_CarSpeed<0)
		gf_CarSpeed = -gf_CarSpeed;
    //gf_CarSpeed_n = gf_CarSpeed * CAR_SPEED_CONSTANT;
    
    gf_CarSpeed = gf_CarSpeed * CAR_SPEED_CONSTANT;
   // newgpt = gf_CarSpeed;
    g_fLeftMotorPulseSigma  = 0;
    g_fRightMotorPulseSigma = 0;
    //////////////����Ϊ�ٶȼ��ĺ��ڴ���////////////////////
    //////////////    ����Ϊ�ٶȿ���//////////////////////////
	fDelta =(float)CAR_SPEED_SET - gf_CarSpeed;	
    fP = fDelta * (float)P_speed;
	fD = (oldgpt-newgpt)*(float)D_speed; ///������һ�ε��ٶ�
	fI_0 = fDelta * (float)(I_speed);

	
	///���ٶȼ�����ʱ����ô����Ҫ��������������ٶ�
  
    error = fDelta + gf_CarSpeed;\
    if(error < 0)
    	error = -error;
    	
	if(error>-15)
	{
	   uart0_putchar('+');
	   uart0_putchar('\n');
	   CAR_ANGLE_SET+=2; //0.05
	}
	else
	{
	   uart0_putchar('+');
	   uart0_putchar('+');
	   uart0_putchar('\n');
	   CAR_ANGLE_SET-=0.5;//0.01
	   if(CAR_ANGLE_SET<3) 
	   {
	   	  CAR_ANGLE_SET=3;
	   }
	}
	//�趨��ǵ����ֵ �����Ҫ�Լ�����һ��
	if(CAR_ANGLE_SET>5) 
	{
	   CAR_ANGLE_SET=5;
	}
	//��֤CAR_ANGLE_SET ��Ϊ��ֵ���³����쳣
	if(CAR_ANGLE_SET<0) 
	{
	   CAR_ANGLE_SET=0;
	}


	if((fP > 1000))
 	   fP = 1000;
	if(fP < -1000)
	   fP = -1000;

	
	gf_SpeedControlIntegral += fI_0;
	gf_SpeedControlOutOld = gf_SpeedControlOutNew;
	gf_SpeedControlOutNew = fD + fP + gf_SpeedControlIntegral;

	if(gf_SpeedControlIntegral>Integral_MAX)//��ֹ�ٶȻ��ֻ�����
		gf_SpeedControlIntegral=Integral_MAX;
    if(gf_SpeedControlIntegral<-Integral_MAX) 
	    gf_SpeedControlIntegral=-Integral_MAX;
					
	///��������Ƿ�ֹ���ֵ�����(�����Ƿ�ֹ�����ܵ�ʱ��ͻȻֹͣ)
	
	if(( gf_CarSpeed_n+CAR_SPEED_SET)>0) 
	{
		uart0_putchar('L');
		uart0_putchar('\n');
	    if(gf_SpeedControlIntegral>0)
	        gf_SpeedControlIntegral*=2;
	
	} 
	else
	{
		 uart0_putchar('A');
		 uart0_putchar('\n');
	     if(gf_SpeedControlIntegral<0)
	        gf_SpeedControlIntegral*=2;
	}



}
*/




void SpeedControl(void)  //11us����
{
  //static float fDelta = 0,fDelta_old = 0;
  float fP, fI, fD,error;
  gf_CarSpeed = (float)(g_fLeftMotorPulseSigma * 0.5 + g_fRightMotorPulseSigma * 0.5);
  g_fLeftMotorPulseSigma  = 0;
  g_fRightMotorPulseSigma = 0;
  /// ��ǰ gf_CarSpeedΪ��ֵ  �������ֵ����500         ��� gf_CarSpeedΪ��ֱ �������ֵ����500
  /// ����ٶȵ�����
  if(PWM_Test_variable1 + PWM_Test_variable2 >= 4000)
  	 gf_CarSpeed = -gf_CarSpeed;
  
  gf_CarSpeed *= SPEEDCONSTANT;
  fDelta = CAR_SPEED_SET - gf_CarSpeed;    //����Ŀ���ٶȵĲ�ֵ
  error = fDelta - CAR_SPEED_SET;
/**
  if(error < 500)
  	CAR_ANGLE_SET+=0.2;
  else
  { 
  	CAR_ANGLE_SET-=0.1;
  	if(CAR_ANGLE_SET <= 0)
  		CAR_ANGLE_SET = 0;	
  }
  if(CAR_ANGLE_SET >2)
  	CAR_ANGLE_SET = 2;
**/  
  //�������������ٶ�ֵ������֮ǰ���ٶ�  ��ô�ͱ�����һ���ٶ�
  //if(fDelta > fDelta_old)
  //	 fDelta = fDelta_old;
  
  fP = fDelta * P_speed;
  fI = fDelta * I_speed;
  if(fP > 500)  //2000
  	fP = 500;
  if(fP < -500)
  	fP = -500;
  g_fSpeedControlIntegral += fI;
  if(g_fSpeedControlIntegral > 1000)  //200   10000
     g_fSpeedControlIntegral = 1000;
  if(g_fSpeedControlIntegral < -1000)
     g_fSpeedControlIntegral = -1000;
 /// printf_fun(g_fSpeedControlIntegral);
  // �ٶ��ֲ�
   fD = fDelta_cha * D_speed;
  gf_SpeedControlOutOld = gf_SpeedControlOutNew;
  gf_SpeedControlOutNew = fP - fD + g_fSpeedControlIntegral;
  fDelta_old = fDelta;
  
}



void SpeedControlOutput(void)
{
	float fValue;
	fValue = gf_SpeedControlOutNew - gf_SpeedControlOutOld;
	gf_SpeedControlOut = fValue * (gn_SpeedControlPeriod + 1)/SPEED_CONTROL_PERIOD + gf_SpeedControlOutOld;    	
}



/// ������ƺ�����Ҫ����
void DirectionControl()
{
	int16   angle_out_error;//����Ϊ���ٶ�
	int16	Driection_OUT;	
	Direction_gyro = cai_z();
	angle_out_error = -DANGLE_P * (Direction_gyro + gyro_offset_z);	
	Driection_OUT = Driection_P * pian_cha + Driection_D1*angle_out_error;//������תΪ����������תΪ��	
	gf_DirectionControlOut_OLD = gf_DirectionControlOut_NEW;
	gf_DirectionControlOut_NEW = Driection_OUT; 				
}

void DirectionControlOutput(void)
{
	float fValue;
	fValue = gf_DirectionControlOut_NEW-gf_DirectionControlOut_OLD;
	gf_DirectionControlOut = fValue *(g_nDirectionControlPeriod)/DIRECTION_CONTROL_PERIOD + gf_DirectionControlOut_OLD;
//	if(gf_DirectionControlOut > 1000)	gf_DirectionControlOut = 1000;
//	if(gf_DirectionControlOut < -1000)	gf_DirectionControlOut = -1000;
}


void printf_fun(int16 var)
{
			int16 va1cop;
			va1cop = var;
			if(va1cop <= 0)
			{
				va1cop = -va1cop;
				ge  	=	(int16)va1cop % 10 		  	    + 0x30;
				shi		=	(int16)va1cop % 100/10    		+ 0x30;
				bai		=	(int16)va1cop % 1000/100 		+ 0x30;
				qian	=	(int16)va1cop % 10000/1000		+ 0x30;
				wan		=	(int16)va1cop / 10000			+ 0x30;
				uart0_putchar('-');
				uart0_putchar(wan);
			    uart0_putchar(qian);
			    uart0_putchar(bai);
			    uart0_putchar(shi);
				uart0_putchar(ge);
				uart0_putchar('\n');	
			}
			else
			{
				ge  	=	(int16)va1cop % 10 		  	    + 0x30;
				shi		=	(int16)va1cop % 100/10    		+ 0x30;
				bai		=	(int16)va1cop % 1000/100 		+ 0x30;
				qian	=	(int16)va1cop % 10000/1000		+ 0x30;
				wan		=	(int16)va1cop / 10000			+ 0x30;
				uart0_putchar(wan);
			    uart0_putchar(qian);
			    uart0_putchar(bai);
			    uart0_putchar(shi);
				uart0_putchar(ge);
				uart0_putchar('\n');
			}
}
 

__declspec(interrupt:0) void EPORT_irq1_handler(void)
{
	
}






