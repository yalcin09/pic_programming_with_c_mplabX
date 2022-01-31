/*
 * File:   PWM
 * 
 * 
 *    ^
 *    |
 *    |
 * +5 |-------------             -----------
 *    |            |             |
 *    |            |             |
 *    |            |             |
 *    |            |             |
 *    |            |             |
 *  0 --------------------------------------->
 *    <-------------------------->
 *                  T
 *    <------------><------------>
 *          T1            T2
 * 
 *    T1 : G�rev �evrim s�resi (Duty Cycle)
 * 
 *    PWM periyodu (T)  =
 *                  (PR2 + 1) * (4 / Fosc) * (Timer2 prescale)
 * 
 *    G�rev �evrim (T1) =
 *                  (CCPR1L) * (4 / Fosc) * (Timer2 prescale)
 * 
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

void main(void) {
    
    // 1ms de?erinde bir priyoda sahip kare dalga �retme.
    // PWM Periyodu (T)) = 1ms = 0.001sn olacak
    // bu y�zden;
    // PR2 = 249
    // Timer2 prescale = 4
    // olarak al?nd?.
    
    // G�rev �evrim s�resinin 0.05ms = 0.0005sn olacak
    // CCPR1L = 125 olarak al?nd?.
    
    TRISC = 0;
    PORTC = 0;
    
    CCP1M3 = 1;         // CCP -> PWM MODA al?nd?.
    CCP1M2 = 1;
    PR2    = 249;
    CCPR1L = 125;
    T2CKPS1 = 0;
    T2CKPS0 = 1;        // B�lme oran? 4 olarak al?nd?.
    TMR2ON  = 1;
    
    while(1);
    
    
    return;
}
