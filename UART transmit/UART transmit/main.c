/*
 * UART transmit.c
 *
 * Created: 26-09-2026 20:35:33
 * Author : hp
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"

int main(void)
{
    init_uart();
	char data = 'H';
    while (1) 
    {
		uart_transmit(data);
		uart_transmit('\n');
		_delay_ms(1000);
    }
}

