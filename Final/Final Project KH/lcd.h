#ifndef LCD_H
#define LCD_H

#include <stdint.h>

// LCD pins
#define LCD_RS_PIN 0
#define LCD_EN_PIN 1
#define LCD_D4_PIN 2
#define LCD_D5_PIN 3
#define LCD_D6_PIN 4
#define LCD_D7_PIN 5

void lcd_init(void);
void lcd_clear(void);
void lcd_set_cursor(uint8_t row, uint8_t col);
void lcd_write_string(const char *str);
void lcd_write_int(uint32_t value);
void display_steps(uint32_t steps);

#endif
