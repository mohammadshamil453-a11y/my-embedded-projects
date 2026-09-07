/*
 * external interrupt using INT0.c
 *
 * Created: 06-09-2026 22:31:44
 * Author : hp
 */ 
#define  F_CPU16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

void external_interrupt(){
	DDRD &= ~(1 << DDD2);
	PORTD |= (1 << PORTD2);
	// falling edge
	EICRA |= (1 <<  ISC01);
	EICRA &= ~(1 << ISC00);
	// enable external interrupt
	EIMSK |= (1 << INT0);
}
ISR(INT0_vect){
	PORTB ^= (1 << PORTB5);
}
int main(void)
{
    external_interrupt();
	DDRB |= (1 << DDB5);
	PORTB &= ~(1 << PORTB5);
	sei();
    while (1) 
    {
    }
}

