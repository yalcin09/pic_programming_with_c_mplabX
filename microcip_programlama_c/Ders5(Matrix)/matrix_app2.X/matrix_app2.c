/*
 * File:   matrix_app2.c
 * Author: 90541
 *
 * Created on 27 Aral?k 2021 Pazartesi, 00:16
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

int i, j, k;
int rows[2][5]    = {{0x03, 0x3A, 0x3B, 0x3A, 0x03},
                     {0x40, 0x5E, 0x1E, 0x5E, 0x5E}};
// int columns[] = {0x01, 0x02, 0x04, 0x08, 0x10}; 

void main(void) {
    
    TRISB = 0x00;
    TRISC = 0x00;
    PORTB = 0x00;
    PORTC = 0x00;
    
    while(1){
        for(k = 0; k < 2; k++){
            for(j = 0; j < 100; j++){
                PORTC = 0x01;
                for(i = 0; i < 5; i++){
                    PORTB = rows[k][i];
                    __delay_ms(1);
                    PORTC = PORTC << 1;         // Bir bit sola kayd?r.
                }
            }
        }
    }
    
    return;
}