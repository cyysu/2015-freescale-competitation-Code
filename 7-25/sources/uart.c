#include "UART.h"


void uart0_init(uint32 baudrate)
{	
	uint32 div,SYS_CLOCK;
	SYS_CLOCK=80000000;
	
	MCF_GPIO_PUAPAR= MCF_GPIO_PUAPAR_UTXD0_UTXD0
				    |MCF_GPIO_PUAPAR_URXD0_URXD0;
	
    //Reset Transmitter Receiver Mode Register
	MCF_UART0_UCR|=(0
				  |MCF_UART_UCR_RESET_TX
	              |MCF_UART_UCR_RESET_RX                                     
	              |MCF_UART_UCR_RESET_MR);             

    //No parity,8bit data
	MCF_UART0_UMR1=(0
		          |MCF_UART_UMR_PM_NONE
	              |MCF_UART_UMR_BC_8);
		
    //1bit stop
	MCF_UART0_UMR2|=MCF_UART_UMR_CM_NORMAL
				  |MCF_UART_UMR_SB_STOP_BITS_1;
		                
    //Set Rx and Tx buad by SYSTERM CLOCK
	MCF_UART0_UCSR=(0
				  |MCF_UART_UCSR_RCS_SYS_CLK
		  		  |MCF_UART_UCSR_TCS_SYS_CLK);
	
    //Set	UART interrupts	
	MCF_UART0_UIMR=0;//MCF_UART_UISR_FFULL_RXRDY;
				  //|MCF_UART_UISR_TXRDY;
				  //|MCF_UART_UISR_DB
				  //|MCF_UART_UISR_COS
	
	MCF_INTC0_IMRL&=~MCF_INTC_IMRL_MASKALL;
	MCF_INTC0_IMRL&=~MCF_INTC_IMRL_INT_MASK13;//UART0
	MCF_INTC0_ICR13=MCF_INTC_ICR_IP(6)+MCF_INTC_ICR_IL(2);//UART0	
	
	
    //set buad rate
	div=(SYS_CLOCK/32/baudrate);
	MCF_UART0_UBG1=(unsigned char)(div>>8);
	MCF_UART0_UBG2=(unsigned char)(div&0x00ff);
	
    //Enable Tx/Rx
	MCF_UART0_UCR=(0
				 |MCF_UART_UCR_TX_ENABLED
				 |MCF_UART_UCR_RX_ENABLED);
}

void uart0_putchar(uint8 c)
{
    //Wait until space is available in the FIFO 
    while (!(MCF_UART0_USR&MCF_UART_USR_TXRDY)) 
    {
    	;
    }
    //Send the character 
    MCF_UART0_UTB = c;
}



/***
void uart1_init(unsigned long baudrate)
{
    unsigned int div;
    uint32 sysclk=80000000;    //龙丘提示：修改主频，跟系统频率一致才行
    MCF_GPIO_PUBPAR=MCF_GPIO_PUBPAR_URXD1_URXD1
    			   |MCF_GPIO_PUBPAR_UTXD1_UTXD1;
    			   //|MCF_GPIO_PUBPAR_URTS1_URTS1
    			   //|MCF_GPIO_PUBPAR_UCTS1_UCTS1;
	
// Reset Transmitter/Receiver/Mode Register
	MCF_UART1_UCR =MCF_UART_UCR_RESET_TX
				  |MCF_UART_UCR_RESET_RX
				  |MCF_UART_UCR_RESET_MR;


//No parity, 8bit data
	MCF_UART1_UMR1=MCF_UART_UMR_PM_NONE
				  |MCF_UART_UMR_BC_8;
	 

//1bit stop
	MCF_UART1_UMR2=MCF_UART_UMR_SB_STOP_BITS_1;

//Set Rx and Tx baud by SYSTEM CLOCK
	MCF_UART1_UCSR =(0
				   |MCF_UART_UCSR_RCS_SYS_CLK
				   |MCF_UART_UCSR_TCS_SYS_CLK);


//Mask all UART interrupts
	MCF_UART1_UIMR =0;
	
//set baude rate
	div=sysclk/32/baudrate;
	MCF_UART1_UBG1=(unsigned char)(div>>8);
	MCF_UART1_UBG2=(unsigned char)(div&0x00ff);
	
	
//Set	UART interrupts	
	MCF_UART1_UIMR=0;//MCF_UART_UISR_FFULL_RXRDY;
				  //|MCF_UART_UISR_TXRDY;
				  //|MCF_UART_UISR_DB
				  //|MCF_UART_UISR_COS

// Enable Tx/Rx
	MCF_UART1_UCR =(0
				  |MCF_UART_UCR_TX_ENABLED
				  |MCF_UART_UCR_RX_ENABLED);
}

void uart1_putchar(uint8 c)
{
	while (!(MCF_UART1_USR & MCF_UART_USR_TXRDY)) 
    {
    	
    };
    MCF_UART1_UTB =(unsigned char) c;	
}

**/