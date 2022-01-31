/*
 * File:   matrix_app1.c
 * Author: 90541
 *
 * Created on 27 Aral?k 2021 Pazartesi, 00:01
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

int i, repatition;
int rows[]    = {0x03, 0x3A, 0x3B, 0x3A, 0x03};
int columns[] = {0x01, 0x02, 0x04, 0x08, 0x10}; 

void main(void) {
    
    TRISB = 0x00;
    TRISC = 0x00;
    
    PORTB = 0x00;
    PORTC = 0x00;
    
    while(1){
        for(repatition = 0; repatition < 10; repatition++){
            for(i = 0; i<5; i++){
                PORTC = columns[i];
                PORTB = rows[i];
                __delay_us(100);
            }
        }
    }
    
    return;
}
