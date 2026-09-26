/*
 * uart.h
 *
 * Created: 26-09-2026 20:38:13
 *  Author: hp
 */ 


#ifndef UART_H_
#define UART_H_

#include <avr/io.h>

void init_uart();
void uart_transmit(char data);



#endif /* UART_H_ */