#include"lanzhou.h"
#include"uart.h"
void SCI_SendData(int16 a ,int16 b,int16 c,unsigned char*data)
{ 
  	int len;
   uint8 ah,al,bh,bl,ch,cl,lrc=0;
   uint16 aa,bb,cc;
   aa=a;//*200+20000;
   bb=b;//*10;//+20000;
   cc=c;//*200+20000;
   
 ah=(uint8)(aa>>8);
 al=(uint8)(aa&0x0f);
 bh=(uint8)(bb>>8);
 bl=(uint8)(bb&0x0f);
 ch=(uint8)(cc>>8);
 cl=(uint8)(cc&0x0f);
 
  data[0] = 0;    // ���ȸ��ֽڣ�������Ϊ0
  data[1] = 12+4;// 16
  data[2] = 0;    // �����ֽڣ�����Ϊ0
  data[3] = 0;    // �����ֽڣ�����Ϊ0
  data[4] = 0;    // �����ֽڣ�����Ϊ0
  data[5] = 0;    // �����ֽڣ�����Ϊ0
                // ���ɼ�����,��12���ֽ�
  data[6] = ah;   // ͨ��1�ĸ��ֽ�����
  data[7] = al;   // ͨ��1�ĵ��ֽ�����
  data[8] = bh;    // ͨ��2�ĸ��ֽ�����
  data[9] = bl;  // ͨ��2�ĵ��ֽ�����
  data[10] =ch;   // ͨ��3�ĸ��ֽ�����
  data[11] =cl; // ͨ��3�ĵ��ֽ�����
  data[12] = 4;   // ͨ��4�ĸ��ֽ�����
  data[13] = 15;  // ͨ��4�ĵ��ֽ�����
  data[14] = 1;   // ͨ��5�ĸ��ֽ�����
  data[15] = 25;  // ͨ��5�ĵ��ֽ�����
  data[16] = 13;  // ͨ��6�ĸ��ֽ�����
  data[17] = 123; // ͨ��6�ĵ��ֽ�����
  
  		
	    
  	uart0_putchar('*');               // ����֡ͷ��һ���ֽ�                             
    len = (int)(data[0]<<8) | (int)(data[1]) ;
    data += 2;                 // ����ָ��
    uart0_putchar('L');               // ����֡���ͣ��������ֽ�
    uart0_putchar('D');
	while(len--)                // �������ݵ�ASCII�룬�������ֽں�CCD����
	{
		SendHex(*data);	
		lrc += *data++;
	} 
	 lrc = 0-lrc;                 // ����CRC������Ϊ����ֵ
	 SendHex(lrc);              // ����CRCУ��ASCII
     uart0_putchar('#');               // ����֡β��һ���ֽ�
  
}

void SendHex(unsigned char data)
 {
    unsigned char	 temp;
    temp = data >> 4;
    if (temp >= 10)
    {
    	uart0_putchar(temp - 10 + 'A');
			}
    else
    {
    	uart0_putchar(temp + '0');
			}
    temp = data & 0x0F;
    if (temp >= 10)
    {
        uart0_putchar(temp - 10 + 'A');
    }
    else
    {
        uart0_putchar(temp + '0');
    }
}


