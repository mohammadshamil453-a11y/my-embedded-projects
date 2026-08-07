#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRD &= ~(1 << DDD5);  
	DDRB |= (1 << DDB2);

	uint8_t State = 0; 
	while (1)
	{
		if (PIND & (1 << PIND5))
		{
			State ^= 1;
			if (State & 1) 
			{
				PORTB |= (1 << PORTB2); 
		}	else{
				PORTB &= ~(1 << PORTB2); 
		}
			}
		else{
			if (State & 1)
			{
				PORTB |= (1 << PORTB2);
				}	
			else{
				PORTB &= ~(1 << PORTB2);
				}
			
		}
		
		
	}
}
