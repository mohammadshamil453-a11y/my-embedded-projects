# define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>

int main(void){
	for(int i = 0; i < 8 ; i++ ){
		DDRD |= (1 << i);
	}
	while(1){
		for(int i = 0; i < 8 ; i++ ){
			PORTD |= (1 << i);
			_delay_ms(1000);
		}
		for(int i = 0; i < 8 ; i++ ){
			PORTD &= ~(1 << i);
			_delay_ms(1000);
		}
	}
}

 
