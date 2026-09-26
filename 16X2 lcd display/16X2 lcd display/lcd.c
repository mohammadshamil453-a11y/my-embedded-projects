/*
 * lcd.c
 *
 * Created: 23-09-2026 00:19:19
 *  Author: hp
 */ 

#include "lcd.h"

// start with that enable pulse
static void lcd_enable_pulse(void){
	LCD_EN_PORT |= (1 << LCD_EN_PIN);
	_delay_us(1);
	LCD_EN_PORT &= ~(1 << LCD_EN_PIN);
	_delay_us(50);
}

//this function sent a nibble to the data pins (b3...b0 -> D7....D4)
static void lcd_send_nibble(uint8_t nib){
	// clear PD2...PD5 by our mapping
	LCD_D_PORT &= ~((1 << LCD_D7_PIN) | (1 << LCD_D6_PIN) | (1 << LCD_D5_PIN) | (1 << LCD_D4_PIN));
	
	// now set the pins according to the data/command bit 
	if(nib & (1 << 3)) LCD_D_PORT |= (1 << LCD_D7_PIN);
	if(nib & (1 << 2)) LCD_D_PORT |= (1 << LCD_D6_PIN);
	if(nib & (1 << 1)) LCD_D_PORT |= (1 << LCD_D5_PIN);
	if(nib & (1 << 0)) LCD_D_PORT |= (1 << LCD_D4_PIN);
	lcd_enable_pulse();
}

// this function allows us to send  a byte
static void lcd_send_byte(uint8_t value, uint8_t rs){
	if(rs == 1) LCD_RS_PORT |= (1 << LCD_RS_PIN);
	else LCD_RS_PORT &= ~(1 << LCD_RS_PIN);
	
	lcd_send_nibble(value >> 4);
	lcd_send_nibble((value & 0x0F));
}

//this function send command
void lcd_cmd(uint8_t c){
	lcd_send_byte(c,0);
	// clear (0x01) and return home (0x02) need longer delays in write-only mode
	if(c == 0x01 || c == 0x02)
	_delay_ms(2);
}

//this function allows us to send data
void lcd_data(uint8_t d){
	lcd_send_byte(d,1);
}

// this function allows us to set the cursor
void lcd_set_cursor(uint8_t row, uint8_t col){
	uint8_t addr = (row ? 0x40 : 0x00) + (col & 0x0F);
	lcd_cmd(0x80 | addr);
}

// this function allows us to print a string
void lcd_print(const char *s){
	while(*s){
		lcd_data((uint8_t)*s++);
	}
}

// this function allows us to clear the lcd
void lcd_clear(){
	lcd_cmd(0x02);
}

//this function allows us to return the cursor to home
void lcd_home(){
	lcd_cmd(0x02);
}

// this function initialises the lcd
void lcd_init(){
	LCD_RS_DDR |= (1 << LCD_RS_PIN);
	LCD_EN_DDR |= (1 << LCD_EN_PIN);
	LCD_D_DDR |= (1 << LCD_D7_PIN) | (1 << LCD_D6_PIN) | (1 << LCD_D5_PIN) | (1 << LCD_D4_PIN) | (1 << LCD_D7_PIN);
	
	_delay_ms(20);     // power-up wait
	
	LCD_RS_PORT &= ~(1 << LCD_RS_PIN);  // RS = 0
	LCD_EN_PORT &= ~(1 << LCD_EN_PIN);  // EN = 0
	
	lcd_send_nibble(0x03);
	_delay_ms(5);
	lcd_send_nibble(0x03);
	_delay_us(150);
	lcd_send_nibble(0x03);
	
	//switch to 4-bit
	lcd_send_nibble(0x02);
	_delay_us(150);
	
	//function set : 4-bits , 2 lines , 5x8 font
	lcd_cmd(0x28);
	
	//display off
	lcd_cmd(0x08);
	
	//clear
	lcd_cmd(0x01);
	
	// entry mode : increment , no shift
	lcd_cmd(0x06);
	
	// display on ,cursor off, blink off
	lcd_cmd(0x0C);
	
}

void lcd_print_uint16(uint16_t v){
	if(v >= 10) lcd_print_uint16(v / 10);
	lcd_data('0' + (v % 10));
}