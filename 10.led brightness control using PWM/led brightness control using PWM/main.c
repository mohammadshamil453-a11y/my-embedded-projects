/*
 * led brightness control using PWM.c
 *
 * Created: 26-08-2026 19:11:04
 * Author : hp
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>

void brightness_control(){
	DDRD |= (1 << DDD6);
	// PWM
	TCCR0A |= ( 1 << WGM01) | ( 1 << WGM00);
	// non-inverting 
	TCCR0A |= ( 1<< COM0A1);
	TCCR0A &= ~( 1<< COM0A0);
	// pre-scalar = 64
	TCCR0B |= ( 1 << CS01) | ( 1 << CS00);
	/* OCR0A = ( duty cycle x 256 ) / 100
			 = ( 50 x 256 ) / 100
			 = 128
	*/
	OCR0A = 128;
}
int main(void)
{
	brightness_control();
    while (1) 
    {
    }
}

