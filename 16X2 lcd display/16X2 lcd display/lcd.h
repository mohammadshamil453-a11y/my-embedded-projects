/*
 * lcd.h
 *
 * Created: 23-09-2026 00:19:31
 *  Author: hp
 */ 


#ifndef LCD_H_
#define LCD_H_

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

// rs = 12    en = 11     d4 = 5     d5 = 4     d6 = 3      d7 = 2

//RS pin
#define LCD_RS_PORT     PORTB
#define LCD_RS_DDR     DDRB
#define LCD_RS_PIN     PB4

//Enable pin
#define LCD_EN_PORT    PORTB
#define LCD_EN_DDR     DDRB
#define LCD_EN_PIN     PB3

//Data pin
#define LCD_D_PORT     PORTD
#define LCD_D_DDR      DDRD
#define LCD_D7_PIN     PD2
#define LCD_D6_PIN     PD3
#define LCD_D5_PIN     PD4
#define LCD_D4_PIN     PD5

// functions
void lcd_init(void);
void lcd_cmd(uint8_t c);
void lcd_data(uint8_t d);
void lcd_set_cursor(uint8_t row, uint8_t col);
void lcd_print(const char *s);
void lcd_clear(void);
void lcd_home(void);
void lcd_print_uint16(uint16_t v);

#endif /* LCD_H_ */