/*
 * File:   COMPARE (KAR?ILA?TIRMA)
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
    if(CCP1IF){
        RC2 = RC2 ^ 1;
    }
    CCP1IF = 0;
}

void main(void) {
    
    GIE     = 1;                 // Genel kesmeler için izin verirdi
    PEIE    = 1;                 // Çevresel kesme aktif edildi
    TMR1IE  = 1;                 // Timer1 kesmesi aktif edildi
    TMR1CS  = 1;                 // Timer1 say?c? olarak kullan?lacak
    T1OSCEN = 1;                 // Dahili osilatör aktif
    TMR1ON  = 1;                 // Timer1 çal???r
    TMR1    = 1;                 // Timer1 1'den saymaya ba?l?yacak
    
    TRISB   = 0;                 // 0b0000 0000
    TRISC   = 1;                 // 0b0000 0001
    
    CCP1M3  = 1;                 // CCP kar??la?t?r?c? olarak çal??t?r?rd?
    CCP1M2  = 0;                 // Kesme olu?tur ve Timer1 resetle
    CCP1M1  = 1;                 // modu
    CCP1M0  = 1;
    CCP1IE  = 1;                 // CCP1 kesmesi aktif edildi
    CCPR1   = 5;                 // CCP de?eri 5 olarak tan?mland?.
    
    // CCP1 ayarlamalar?nda;
    // Sayac olarak ayarlanan TIMER1 CCPR1 de?erine (5) e?it olursa,
    // Kesme i?lemi gerçekle?ecek ve TIMER1 resetlenecektir.
    
    RC2 = 0;
    while(1);
}
