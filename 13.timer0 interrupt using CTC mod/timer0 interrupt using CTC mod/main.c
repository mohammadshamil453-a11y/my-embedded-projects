/*
 * timer0 interrupt using CTC mod.c
 *
 * Created: 04-09-2026 10:42:41
 * Author : hp
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint16_t count = 0;

void init_timer0_interrupt(){
	// CTC mode
	TCCR0A |= (1 << WGM01);
	// pre-scalar value = 64
	TCCR0B |= (1 << CS00) | (1 << CS01);
/*---------------------calculations---------------------
clock frequency = 16000000
pre-scalar value = 64
current frequency = 16000000 / 64
				  = 250000
time taken for 1 tick = 1 / 250000
					  = 4 micro seconds
for 1 millisecond = 1 x 10^-3 / 4 x 10^-6
				  = 250 
OCR0A = 249
--------------------------------------------------------*/
	OCR0A = 249;
	// compare match A interrupt
	TIMSK0 |= (1 << OCIE0A);
	// global interrupt
	sei(); 
}
ISR(TIMER0_COMPA_vect){
	count++;
	if (count >= 1000)
	{
		PORTB ^= (1 << PORTB2);
		count = 0;
	}
	
}

int main(void)
{
    init_timer0_interrupt();
	DDRB |= (1 << DDB2);
	PORTB &= ~(1 << PORTB2);
    while (1) 
    {
    }
}

