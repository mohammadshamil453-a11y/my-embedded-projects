/*
 * 16X2 lcd display.c
 *
 * Created: 23-09-2026 00:18:42
 * Author : hp
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"



int main(void)
{
    lcd_init();
	lcd_set_cursor(0,0);
	lcd_print("Hello LCD");
	lcd_set_cursor(1,0);
	lcd_print("its works ");
	
    while (1) 
    {
	lcd_set_cursor(0,0);
	lcd_print("Hello LCD");
	lcd_set_cursor(1,0);
	lcd_print("its works ");
    }
}

