/*
 * dc motor control using pwm.c
 *
 * Created: 29-08-2026 22:15:06
 * Author : hp
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

void dc_motor_control(){
	DDRD |= (1 << DDD6);
	
	TCCR0A |= (1 << WGM00);
	
	TCCR0A |= (1 << COM0A1);
	TCCR0A &= ~(1 << COM0A0);
	
/*----------------------calculations--------------------------------
frequency = 16000000
pre-scalar value = 8

Fpwm = Fclk / (2 x pre-scalar value x 255 )
	 = 16000000 / ( 2 x 8 x 255 )
	 = 3.922 kHz
	 
-------------------------------------------------------------------*/
	TCCR0B |= (1 << CS01);
	TCCR0B &= ~((1 << CS00) | (1 << CS02));
}

void dc_motor(){
	DDRD &= ~((1 << DDD1) | (1 << DDD2));
}

void forward(){
	PORTD |= (1 << PORTD1);
	PORTD &= ~(1 << PORTD2);
}

int main(void)
{
	dc_motor_control();
    dc_motor();
	forward();
    while (1) 
    {
		for (int i =0 ; i<255 ; i++ )
		{
			OCR0A = i;
			_delay_ms(100);
		}
    }
}

