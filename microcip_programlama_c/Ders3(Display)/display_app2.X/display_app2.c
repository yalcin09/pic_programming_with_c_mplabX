/*
 * File:   display_app2.c
 * Author: 90541
 *
 * Created on 26 Aral?k 2021 Pazar, 23:34
 */


#include <xc.h>

// CONFIG
#pragma config FOSC = XT        // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = ON        // Watchdog Timer (WDT enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (Power-up Timer is disabled)
#pragma config CP = OFF         // Code Protection bit (Code protection disabled)

#define _XTAL_FREQ 4000000

int numbers_array[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7C, 0x07, 0x7F, 0x6F};
int units_digit = 0, tens_digit = 0, number = 0;

void main(void) {
    
    // Giri?-ç?k?? ayarlar?
    TRISA = 0x00;
    TRISB = 0x00;
    
    // Port temizleme
    PORTA = 0x00;
    PORTB = 0x00;
    
    // main code
    while(1){
        
        units_digit = number % 10;
        tens_digit = number / 10;
        
        RA1 = 0;
        RA0 = 1;
        PORTB = numbers_array[units_digit];
        __delay_ms(10);
        
        RA0 = 0;
        RA1 = 1;
        PORTB = numbers_array[tens_digit];
        __delay_ms(10);
        
        number++;
        if(number > 99) number = 0;
    }
    return;
}
