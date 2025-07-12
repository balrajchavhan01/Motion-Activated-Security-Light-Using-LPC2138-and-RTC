#include <lpc21xx.h>
#include "lcd.h"
#include "i2c.h"
#include "ds1307.h"
#include "delay.h"

#define PIR (IOPIN0 &(1<<10))
#define LIGHT_ON() IOSET0=(1<<30)
#define LIGHT_OFF() IOCLR0=(1<<30)

void init_io(){
	IODIR0 &= ~(1<<10);  //PIR intput (p0.10)
	IODIR0 |= (1<<30); //Relay output (p0.30
	LIGHT_OFF();
	IODIR0 |= (0x3f <<20); //LCD pins : P0.20-P0.25
}

int main(){
	char time[9];
	
	init_io();
	lcd_init();
	i2c_init();
	ds1307_init();
	
	lcd_cmd(0x80);
	lcd_print("Motion Security");
	
	while(1){
		ds1307_get_time(time); //format : HH:MM:SS
		
		lcd_cmd(0xC0);
		lcd_print("Time:");
		lcd_print(time);
		
		if(!PIR){
			lcd_cmd(0x80);
			lcd_print("Motion Detected ");
			LIGHT_ON();
		}
		else{
			lcd_cmd(0x80);
			lcd_print("No Motion    ");
			LIGHT_OFF();
		}
		
		delay_ms(1000);
	}
}

