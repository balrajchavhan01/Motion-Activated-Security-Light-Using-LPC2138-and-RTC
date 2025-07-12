#include <LPC214x.h>
#include "i2c.h"

// I2C Initialization for LPC2129
void i2c_init() {
    // Proper function select for P0.27 (SDA) and P0.28 (SCL)
    PINSEL1 &= ~(0xF << 22);    // Clear bits 22–25
    PINSEL1 |=  (0x5 << 22);    // Set SDA and SCL (function 1)

    I2C0CONCLR = 0x6C;          // Clear control flags
    I2C0SCLH = 60;              // Clock high time
    I2C0SCLL = 60;              // Clock low time
    I2C0CONSET = 0x40;          // Enable I2C
}


// Generate I2C Start Condition
void i2c_start() {
    I2C0CONSET = 0x20;  // Set STA (Start condition)
    while (!(I2C0CONSET & 0x08));  // Wait for SI (Interrupt)
    I2C0CONCLR = 0x28;  // Clear STA and SI
}

// Generate I2C Stop Condition
void i2c_stop() {
    I2C0CONSET = 0x10;  // Set STO (Stop)
    I2C0CONCLR = 0x08;  // Clear SI
}

// Write one byte on I2C bus
void i2c_write(unsigned char data) {
    I2C0DAT = data;      // Load data into data register
    I2C0CONCLR = 0x08;   // Clear SI to continue
    while (!(I2C0CONSET & 0x08));  // Wait for data sent (SI set)
}

// Read one byte from I2C bus
unsigned char i2c_read(unsigned char ack) {
    if (ack)
        I2C0CONSET = 0x04;  // Set AA (Assert Acknowledge)
    else
        I2C0CONCLR = 0x04;  // Clear AA (No Acknowledge)

    I2C0CONCLR = 0x08;  // Clear SI
    while (!(I2C0CONSET & 0x08));  // Wait for byte received
    return I2C0DAT;
}
