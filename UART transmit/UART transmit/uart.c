/*
 * uart.c
 *
 * Created: 26-09-2026 20:37:58
 *  Author: hp
 */ 

#include "uart.h"

void init_uart(){
	/* step 1 : baud rate calculation for 9600
	---------------calculation--------------------
	frequency = 16000000
	baud rate = 9600
	
	UBRR = frequency / (16 x baud rate) - 1
	     =  16000000 / (16 x 9600) -1
		 = 103
	-----------------------------------------------*/
	UBRR0H = 0;
	UBRR0L = 103;
	// step 2 : enable transmittor and receiver
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0); 
	// step 3 : frame formate configuration
	UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01);
	UCSR0B &= ~(1 << UCSZ02);
	// no parity
	UCSR0B &= ~((1 << UPM00) | (1 << UPM01));
	// 1 stop bit select
	UCSR0C &= ~(1 << USBS0);
	//step 4 : 
}

void uart_transmit(char data){
	// waiting until the buffer is ready
	while(!(UCSR0A & (1 << UDRE0)));
	// giving data to the buffer once it
	UDR0 = data;
}