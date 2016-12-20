#ifndef UART_H_
#define UART_H_
#include <stdio.h>
#include "support_common.h" 

void uart0_init(uint32 baudrate);
void uart0_putchar(uint8 c);

/**
void uart1_init(uint32 baudrate);
void uart1_putchar(uint8 c);
**/
#endif