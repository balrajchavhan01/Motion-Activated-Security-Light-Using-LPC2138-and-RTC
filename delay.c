#include "delay.h"

void delay_ms(unsigned int ms) {
    volatile unsigned int i,j;
    for(i=0;i<ms;i++) {
        for(j=0;j<6000;j++);
    }
}