#ifndef LCD_H
#define LCD_H

void lcd_init(void);
void lcd_cmd(unsigned char);
void lcd_char(unsigned char);
void lcd_print(const char *);
void lcd_goto(unsigned char row, unsigned char col);

#endif