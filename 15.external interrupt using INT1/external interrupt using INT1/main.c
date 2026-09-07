/*
 * external interrupt using INT1.c
 *
 * Created: 07-09-2026 09:26:32
 * Author : hp
 */ 
#define  F_CPU 16000000;
#include <avr/io.h>
#include <avr/interrupt.h>

void external_interrupt(){
	// configure pin D3 are input
	DDRD &= ~(1 << DDD3);
	PORTD |= (1 << PORTD3);
	// falling edge
	EICRA |= (1 << ISC11);
	EICRA &= ~(1 << ISC10);
	// enable external interrupt INT1
	EIMSK |= (1 << INT1);
}

ISR(INT1_vect){
	PORTB ^= (1 << PORTB3);
}

int main(void)
{
    external_interrupt();
	DDRB |= (1 << DDB3);
	PORTB &= ~(1 << PORTB3);
	sei(); 
    while (1) 
    {
    }
}

