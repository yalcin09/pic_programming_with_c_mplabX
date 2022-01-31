/*
 * File:   led_app.c
 * Author: 90541
 *
 * Created on 26 Aral?k 2021 Pazar, 22:51
 */


#include <xc.h>

// CONFIG
#pragma config FOSC = XT        // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = ON        // Watchdog Timer (WDT enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (Power-up Timer is disabled)
#pragma config CP = OFF         // Code Protection bit (Code protection disabled)

#define _XTAL_FREQ 4000000

void main(void) {
    
    // Giri? - ç?k?? portu tan?mlama
    TRISA = 0b00000001;             // A potunun 1. pini giri? olarak ayarland?. 
    TRISB = 0x00;                   // B portunun bütün pinleri ç?k?? olarak ayarland?.
    
    while(1){
        
        if(RA0 == 1)
            PORTB = 0x0F;           // 0b00001111
        if(RA0 == 0)
            PORTB = 0xF0;           // 0b11110000
    }
    
    
    return;
}
