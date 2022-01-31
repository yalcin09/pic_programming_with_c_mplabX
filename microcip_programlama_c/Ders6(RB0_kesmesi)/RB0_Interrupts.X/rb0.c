/*
 * File : RB0_INTERRUPT
 * 
 * For PIC16F84A:
 * 
 * ---------------------------------------------------------
 * |                    INTCON REGISTER                    |
 * ---------------------------------------------------------
 * |  GIE | EIEE | TOIE | INTE | RBIE | TIF  | INTF | RBIF |
 * ---------------------------------------------------------
 * | Bit7 | Bit6 | Bit5 | Bit4 | Bit3 | Bit2 | Bit1 | Bit0 |
 * ---------------------------------------------------------
 * 
 *  INTCON saklay?c?lar?n?n 7,6,5,4 ve 3. bitleri kesme yetkilendirme bitidir.
 * Bu bitlerin de?eri 0 olursa kesme pasif, 1 olursa kesme aktif edilmi? olur.
 * 2,1 ve 0. bitler ise kesme gösterge bitleridir. Kesme olu?tu?u anda 1 de?erini
 * al?rlar.
 * 
 *  GIE  : Tüm kesmeleri yetkilendirme bayra??,
 *  EIEE : EEPROM kesmesi yetkilendirme bayra??,
 *  TOIE : TMR0 say?c? kesme yetkilendirme bayra??,
 *  INTE : Harici kesme (RB0) yetkilendirme bayra??,
 *  RBIE : PORTB (4,5,6,7) kesmesi yetkilendirme bayra??,
 *  T0IF : TMR0 say?c? kesmesi gösterge bayra??,
 *  INTF : Harici kesme gösterge bayra??,
 *  RBIF : PortB (4,5,6,7) kesmesi gösterge bayra??.
 * 
 */


#include <xc.h>

// CONFIG
#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF        // Watchdog Timer (WDT enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (Power-up Timer is disabled)
#pragma config CP = OFF         // Code Protection bit (Code protection disabled)

#define _XTAL_FREQ 4000000

void __interrupt() interrupts_function(){
    
    if(INTF){       // RB0 bayra?? kontrol ediliyor. 
        PORTA = 1;
        __delay_ms(2000);
        PORTA = 0;
    }
    
    INTF = 0;
}

void main(void) {
    
    GIE  = 1;                    // Tüm kesmeler yetkilendi
    INTE = 1;                    // RB0 yetkilendilirdi
    
    TRISA = 0;                   // A portunun bütün pinleri ç?k?? yap?ld?
    TRISB = 1;                   // B portunun 1. pini giri? di?er pinleri ç?k?? oldu
    
    PORTA = 0;
    PORTB = 0;                   // PORTA ve PORTB ç?k??lar? 0 yap?ld?.
    
    while(1){
        RB6 = 0;
        __delay_ms(1000);
        RB6 = 1;
        __delay_ms(1000);
        RB7 = 0;
        __delay_ms(1000);
        RB7 = 1;
        __delay_ms(1000);
        
    }
    return;
}
