#include "lcd.h"
#include "gpio.h"
#include "timer.h"
#include <stdio.h>

static void lcd_write_4bit(uint8_t data);
static void lcd_write_cmd(uint8_t cmd);
static void lcd_write_data(uint8_t data);

void lcd_init(void)
{
    // Configure LCD pins as outputs
    PORTD->PCR[LCD_RS_PIN] = PORT_PCR_MUX(1);
    PORTD->PCR[LCD_EN_PIN] = PORT_PCR_MUX(1);
    PORTD->PCR[LCD_D4_PIN] = PORT_PCR_MUX(1);
    PORTD->PCR[LCD_D5_PIN] = PORT_PCR_MUX(1);
    PORTD->PCR[LCD_D6_PIN] = PORT_PCR_MUX(1);
    PORTD->PCR[LCD_D7_PIN] = PORT_PCR_MUX(1);

    GPIOD->PDDR |= (1 << LCD_RS_PIN) | (1 << LCD_EN_PIN) |
                   (1 << LCD_D4_PIN) | (1 << LCD_D5_PIN) |
                   (1 << LCD_D6_PIN) | (1 << LCD_D7_PIN);

    // Initialize LCD in 4-bit mode
    delay_ms(50);

    lcd_write_cmd(0x33);
    delay_ms(5);
    lcd_write_cmd(0x32);
    delay_ms(1);
    lcd_write_cmd(0x28); // 4-bit, 2 lines, 5x8 font
    lcd_write_cmd(0x0C); // Display ON, cursor OFF
    lcd_write_cmd(0x06); // Auto increment cursor
    lcd_write_cmd(0x01); // Clear display

    delay_ms(2);
}

void lcd_clear(void)
{
    lcd_write_cmd(0x01);
    delay_ms(2);
}

void lcd_set_cursor(uint8_t row, uint8_t col)
{
    uint8_t row_offsets[] = {0x00, 0x40};
    lcd_write_cmd(0x80 | (col + row_offsets[row]));
}

void lcd_write_string(const char *str)
{
    while (*str)
        lcd_write_data(*str++);
}

void lcd_write_int(uint32_t value)
{
    char buffer[16];
    sprintf(buffer, "%lu", value);
    lcd_write_string(buffer);
}

void display_steps(uint32_t steps)
{
    lcd_clear();
    lcd_set_cursor(0, 0);
    lcd_write_string("Steps: ");
    lcd_write_int(steps);
}

static void lcd_write_4bit(uint8_t data)
{
    // Write high nibble
    GPIOD->PDOR = (GPIOD->PDOR & 0xFFFFFFC3) | ((data & 0xF0) >> 2);

    // Generate enable pulse
    gpio_set_pin(GPIOD, LCD_EN_PIN);
    delay_ms(1);
    gpio_clear_pin(GPIOD, LCD_EN_PIN);
}

static void lcd_write_cmd(uint8_t cmd)
{
    gpio_clear_pin(GPIOD, LCD_RS_PIN);
    lcd_write_4bit(cmd);
    lcd_write_4bit(cmd << 4);
}

static void lcd_write_data(uint8_t data)
{
    gpio_set_pin(GPIOD, LCD_RS_PIN);
    lcd_write_4bit(data);
    lcd_write_4bit(data << 4);
}