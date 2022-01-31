/*
 * File:   PWM 
 * 
 * H köprü mant??? ile motor sürmek.
 */


#include <xc.h>

// CONFIG
#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = ON        // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config CP = OFF         // FLASH Program Memory Code Protection bits (Code protection off)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low Voltage In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EE Memory Code Protection (Code Protection off)
#pragma config WRT = ON         // FLASH Program Memory Write Enable (Unprotected program memory may be written to by EECON control)

#define _XTAL_FREQ 4000000

void main(void) {
    
    TRISB = 0x07;
    TRISD = 0x00;
    PORTD = 0x00;
    
    while(1){
    
        if(RB0){
            PORTD = 5;
        }
        if(RB1){
            PORTD = 10;
        }
        if(RB2){
            PORTD = 0;
        }
    
    }
    
    return;
}
