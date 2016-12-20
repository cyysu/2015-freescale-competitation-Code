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
 
  data[0] = 0;    // 长度高字节，此设置为0
  data[1] = 12+4;// 16
  data[2] = 0;    // 保留字节，设置为0
  data[3] = 0;    // 保留字节，设置为0
  data[4] = 0;    // 保留字节，设置为0
  data[5] = 0;    // 保留字节，设置为0
                // 填充采集数据,共12个字节
  data[6] = ah;   // 通道1的高字节数据
  data[7] = al;   // 通道1的低字节数据
  data[8] = bh;    // 通道2的高字节数据
  data[9] = bl;  // 通道2的低字节数据
  data[10] =ch;   // 通道3的高字节数据
  data[11] =cl; // 通道3的低字节数据
  data[12] = 4;   // 通道4的高字节数据
  data[13] = 15;  // 通道4的低字节数据
  data[14] = 1;   // 通道5的高字节数据
  data[15] = 25;  // 通道5的低字节数据
  data[16] = 13;  // 通道6的高字节数据
  data[17] = 123; // 通道6的低字节数据
  
  		
	    
  	uart0_putchar('*');               // 发送帧头，一个字节                             
    len = (int)(data[0]<<8) | (int)(data[1]) ;
    data += 2;                 // 调整指针
    uart0_putchar('L');               // 发送帧类型，共两个字节
    uart0_putchar('D');
	while(len--)                // 发送数据的ASCII码，含保留字节和CCD数据
	{
		SendHex(*data);	
		lrc += *data++;
	} 
	 lrc = 0-lrc;                 // 计算CRC，可以为任意值
	 SendHex(lrc);              // 发送CRC校验ASCII
     uart0_putchar('#');               // 发送帧尾，一个字节
  
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


