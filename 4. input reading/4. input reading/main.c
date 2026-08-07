/*
 * 4. input reading.c
 *
 * Created: 05-08-2026 17:42:39
 * Author : hp
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
    DDRD &= ~(1 << DDD5 );
	DDRB |= ( 1 << DDB2 );
    while (1) 
    {
		if(PIND &= (1 << PIND5)){
			PORTB |= ( 1 << PORTB2);
		}else{
			PORTB &= ~( 1 << PORTB2);
		}
	}
}

