/*
 * File:   portb_interrupt.c
 * Author: 90541
 *
 * Created on 27 Aral?k 2021 Pazartesi, 12:04
 */


#include <xc.h>

// CONFIG
#pragma config FOSC = XT     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF        // Watchdog Timer (WDT enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (Power-up Timer is disabled)
#pragma config CP = OFF         // Code Protection bit (Code protection disabled)

#define _XTAL_FREQ 4000000

void __interrupt() interrupts_function(void){
    if(RBIF == 1 & ((RB4 == 1) | (RB5 == 1) | (RB6 == 1) | (RB7 == 1))){
        RA0 = 1;
        __delay_ms(2000);
        RA0 = 0;
    }
    RBIF = 0;
}

void main(void) {
    
    GIE  = 1;                   // Bütün kesmeler kullan?lmas?na izin verirdi
    RBIE = 1;                   // PortB kesmesi aktif edildi
    
    TRISA = 0x00;               // 0b0000 0000
    TRISB = 0xF0;               // 0b1111 0000
    
    PORTA = 0x00;
    
    while(1){
        
        RB1 = 0;
        __delay_ms(100);
        RB1 = 1;
        __delay_ms(100);
    }
    
    return;
}
