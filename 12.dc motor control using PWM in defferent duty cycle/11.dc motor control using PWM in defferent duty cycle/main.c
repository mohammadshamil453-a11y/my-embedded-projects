#define F_CPU 16000000UL
#include <avr/io.h>

void init_dc_motor_control(void)
{
	// PD6 = OC0A = PWM output
	DDRD |= (1 << DDD6);

	// PB5 = button input
	DDRB &= ~(1 << DDB5);

	// Enable internal pull-up resistor
	PORTB |= (1 << PORTB5);

	// Timer0 Phase Correct PWM
	TCCR0A |= (1 << WGM00);
	TCCR0A |= (1 << COM0A1);

	// Prescaler = 8
	TCCR0B |= (1 << CS01);
}
/*----------------------------calculations---------------------------------- 
clock frequency = 16000000 
pre-scalar value = 8 
PWM frequency = Fclk /( 2 x pre-scalar value x 255 ) 
			  = 16000000 / ( 2 x 8 x 255) 
			  = 3.922 kHz 
for 0% duty cycle :- 
	OCR0A = 0 
for 25% duty cycle :- 
	OCR0A = ( 25 x 256 ) / 100 -1 
		  = 63 
for 50% duty cycle :- 
	OCR0A = ( 50 x 256 ) / 100 -1 
		  = 127 
for 75% duty cycle :- 
	OCR0A = ( 75 x 256 ) / 100 -1 
		  = 191 
for 100% duty cycle :- 
	OCR0A = ( 100 x 256 ) / 100 -1 
		  = 255 
--------------------------------------------------------------------------------------*/

void dc_motor(void)
{
	// PD1 and PD2 = motor direction outputs
	DDRD |= (1 << DDD1) | (1 << DDD2);
}

void forward(void)
{
	PORTD |= (1 << PORTD1);
	PORTD &= ~(1 << PORTD2);
}

int main(void)
{
	init_dc_motor_control();

	dc_motor();
	forward();

	uint8_t count = 0;
	uint8_t previous_button = 1;

	while (1)
	{
		uint8_t current_button = PINB & (1 << PINB5);

		// Detect button press
		if (previous_button && !current_button)
		{
			++count;

			if (count == 5) count = 0;
			
		}

		previous_button = current_button;

		switch (count)
		{
			case 0:
			OCR0A = 0;
			break;

			case 1:
			OCR0A = 63;
			break;

			case 2:
			OCR0A = 127;
			break;

			case 3:
			OCR0A = 191;
			break;

			case 4:
			OCR0A = 255;
			break;
		}
	}
}