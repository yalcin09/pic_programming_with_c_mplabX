/*
 * File:   PWM HIZ Kontrolü
 * 
 * 
 * 
 */


#include <xc.h>

// CONFIG
#pragma config FOSC = XT        // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config CP = OFF         // FLASH Program Memory Code Protection bits (Code protection off)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low Voltage In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EE Memory Code Protection (Code Protection off)
#pragma config WRT = ON         // FLASH Program Memory Write Enable (Unprotected program memory may be written to by EECON control)

#define _XTAL_FREQ 4000000


void __interrupt() interrupt_function(void){
    
    if(RBIF){
        if(RB4)
            PORTD = PORTD ^ 0b000001010;
        if(RB5){
            if(CCPR1L < 245)
                CCPR1L +=20;
            else
                CCPR1L = 245;
        }
        if(RB6){
            if(CCPR1L > 5)
                CCPR1L -=20;
            else
                CCPR1L = 5;
        }
    }
    RBIF = 0;
}

void main(void) {
    
    GIE   = 1;
    PEIE  = 1;
    RBIE  = 1;                  // PORTB kesmesi aktif
    
    // PWM Periyot (T) = 
    //      (PR2 + 1) * (4 / F_osc) * (Bölme oran? (prescale))
    // Duyt Cycle  (T1)=
    //      (CCPR1L) *  (4 / F_osc) + (Bölme oran? (prescale))
    
    CCP1M3  = 1;                 // CCP PWM MODE
    CCP1M2  = 1;
    PR2     = 249;
    CCPR1L  = 125;
    T2CKPS1 = 0;                 // Bölme oran? 4 olarak al?nd?.
    T2CKPS0 = 1;
    TMR2ON  = 1;
    
    TRISB   = 0xFF;
    TRISC   = 0x00;
    TRISD   = 0x00;
    PORTD   = 0x05;
    
    while(1);
}
