#include "i2c.h"
#include "ds1307.h"

unsigned char bcd_to_decimal(unsigned char bcd) {
    return ((bcd >> 4) * 10 + (bcd & 0x0F));
}

void ds1307_init() {
    i2c_start();
    i2c_write(0xD0);
    i2c_write(0x00);
    i2c_write(0x00);
    i2c_stop();
}

void ds1307_get_time(char *time) {
    unsigned char h, m, s;
    i2c_start();
    i2c_write(0xD0);
    i2c_write(0x00);
    i2c_start();
    i2c_write(0xD1);
    s = bcd_to_decimal(i2c_read(1));
    m = bcd_to_decimal(i2c_read(1));
    h = bcd_to_decimal(i2c_read(0));
    i2c_stop();

    time[0] = (h / 10) + '0';
    time[1] = (h % 10) + '0';
    time[2] = ':';
    time[3] = (m / 10) + '0';
    time[4] = (m % 10) + '0';
    time[5] = ':';
    time[6] = (s / 10) + '0';
    time[7] = (s % 10) + '0';
    time[8] = '\0';
}