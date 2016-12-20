#include"keyboard.h"
uint8 keyscan()//æÿ’Ûº¸≈Ã…®√Ë
{ 
   
   int temp;
   uint8 key=0;
   
   
	temp=MCF_GPIO_SETTH;
	temp=temp&0xFF;
		if(temp!=0xFF)
			{
			_delay_ms(10);
			temp=MCF_GPIO_SETTH;
	        temp=temp&0xFF;
				if(temp!=0xFF)
				{
					switch(temp)
					{
					  case 0x7F:
					  key=4;
					  break;
					  case 0xbF:
					  key=3;
					  break;
					  case 0xDF:
	                  key=7;
					  break;
					  case 0xEF:
					  key=8;
					  break;
				      case 0xf7:
				      key=6;
				      break;
					  case 0xfb:
					  key=5;
					  break;
					  case 0xfd:
					  key=2;
					  break;
					  case 0xfe:
					  key=1;
					  break;

	             	}
                 
              
                 }
		      }
		      
		      return key;
 
}

void _delay_ms(uint8 ms)      //—” ±“ª∫¡√Î
{
    int ii,jj;
   if (ms<1) ms=1;
   for(ii=0;ii<ms;ii++)     
   for(jj=0;jj<6676;jj++)
   {
   	
   }
    //80MHz--1ms  
}