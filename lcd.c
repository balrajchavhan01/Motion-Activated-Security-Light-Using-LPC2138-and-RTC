#include <LPC21xx.h>
#include "lcd.h"
#include "delay.h"

#define RS (1<<20)
#define EN (1<<21)
#define D4 (1<<22)
#define D5 (1<<23)
#define D6 (1<<24)
#define D7 (1<<25)

void lcd_pulse() {
    IOSET0 = EN;
    delay_ms(1);
    IOCLR0 = EN;
    delay_ms(1);
}

void lcd_send_nibble(unsigned char nibble) {
    IOCLR0 = D4|D5|D6|D7;
    if(nibble & 0x01) IOSET0 = D4;
    if(nibble & 0x02) IOSET0 = D5;
    if(nibble & 0x04) IOSET0 = D6;
    if(nibble & 0x08) IOSET0 = D7;
    lcd_pulse();
}

void lcd_cmd(unsigned char cmd) {
    IOCLR0 = RS;
    lcd_send_nibble(cmd >> 4);
    lcd_send_nibble(cmd & 0x0F);
    delay_ms(2);
}

void lcd_char(unsigned char data) {
    IOSET0 = RS;
    lcd_send_nibble(data >> 4);
    lcd_send_nibble(data & 0x0F);
    delay_ms(2);
}

void lcd_print(const char* str) {
    while(*str) lcd_char(*str++);
}

void lcd_goto(unsigned char row, unsigned char col) {
    unsigned char pos[] = {0x80, 0xC0};
    lcd_cmd(pos[row-1] + col - 1);
}

void lcd_init() {
    IOCLR0 = RS | EN | D4 | D5 | D6 | D7;
    lcd_send_nibble(0x03);
    delay_ms(5);
    lcd_send_nibble(0x03);
    delay_ms(5);
    lcd_send_nibble(0x03);
    delay_ms(5);
    lcd_send_nibble(0x02); // 4-bit mode

    lcd_cmd(0x28);
    lcd_cmd(0x0C);
    lcd_cmd(0x06);
    lcd_cmd(0x01);
}