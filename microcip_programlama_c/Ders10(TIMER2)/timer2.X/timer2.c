/*
 * File:   TIMER2 REGISTER
 * 
 *  TIMER2 8 bitlik bir registerd?r. En büyü özelli?i ise 8 bitlik periyod
 * saklay?c?s?d?r.  Yani 255'e kadar saymas? zorunlu de?ildir. En üst de?eri
 * (PR2) biz belirleriz. Saat frekans? için 2 bitlik bir ön ölçek (prescale) ve
 * 4 bitlik bir son ölçek (postscale) oranlar? vard?r. CCP modulünde PWM i?lemi
 * için zamanlay?c? olarak kullan?r?z.
 * 
 * *****************************************************************************
 * 
 * Timer2 için en önemli register T2CON'dur.
 * ---------------------------------------------------------------
 * |                            T2CON REGISTER                   |
 * ---------------------------------------------------------------
 * |  -   |TOUTPS3|TOUTPS2|TOUTPS1|TOUTPS0|TMR2ON|T2CKPS1|T2CKPS0|
 * ---------------------------------------------------------------
 * | Bit7 | Bit6  |  Bit5 |  Bit4 | Bit3  | Bit2 | Bit1  |  Bit0 |
 * ---------------------------------------------------------------
 * 
 *  - TOUTPS0 - TOUTPS3 : Timer2 ç?k?? son ölçek (postscale) seçme
 *          ----------------------------------------
 *          |TOUTPS3|TOUTPS2|TOUTPS1|TOUTPS0| Oran |
 *          ----------------------------------------
 *          |   0   |   0   |   0   |   0   |  1/1 |
 *          ----------------------------------------
 *          |   0   |   0   |   0   |   1   |  1/2 |
 *          ----------------------------------------
 *          |   0   |   0   |   1   |   0   |  1/3 |
 *          ----------------------------------------
 *          |   0   |   0   |   1   |   1   |  1/4 |
 *          ----------------------------------------
 *          |  ...  |  ...  |  ...  |  ...  |  ... |
 *          ----------------------------------------
 *          |   1   |   1   |   1   |   1   | 1/16 |
 *          ----------------------------------------
 * 
 *  - TMR2ON : Timer2 çal??ma biti
 *              0: Timer2 kapat
 *              1: Timer2 çal??
 * 
 *  - T2CKPS1 - T2CKPS0 : Timer2 saat ön-ölçek (prescale) seçme biti
 *          ------------------------
 *          |T2CKPS1|T2CKPS0| Oran |
 *          ------------------------
 *          |   0   |   0   |   1  |
 *          ------------------------
 *          |   0   |   1   |   4  |
 *          ------------------------
 *          |   1   |   0   |   8  |
 *          ------------------------
 *          |   1   |   1   |   16 |
 *          ------------------------
 * 
 * *****************************************************************************
 * Formül:
 * 
 *  f_komut = çal??ma frekans? / 4
 *  T_komut = 1 / f_komut
 *  kesme_süresi = T_komut*(Bölme oran?)*(PR2 - TMR2 + 1)*(postScale de?eri)
 */


#include <xc.h>

// CONFIG
#pragma config FOSC = XT     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config CP = OFF         // FLASH Program Memory Code Protection bits (Code protection off)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low Voltage In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EE Memory Code Protection (Code Protection off)
#pragma config WRT = ON         // FLASH Program Memory Write Enable (Unprotected program memory may be written to by EECON control)

#define _XTAL_FREQ 4000000

int count = 0;
void __interrupt() interrupt_function(){
    if(TMR2IF){
        count++;
        if(count == 10){
            count = 0;
            RB0 = RB0 ^ 1;
        }
    }
    TMR2IF = 0;
    TMR2 = 0;
}

void main(void) {
    
    GIE    = 1;
    PEIE   = 1;
    TMR2IE = 1;
    // Bölme oran? (prescale) = 16
    T2CKPS1 = 1;
    T2CKPS0 = 1;
    // postscale = 16
    TOUTPS3 = 1;
    TOUTPS2 = 1;
    TOUTPS1 = 1;
    TOUTPS0 = 1;
    // Timer2 aç?l?yor
    TMR2ON = 1;
    // Timer2 ba?lang?ç de?eri
    TMR2 = 0;
    // Giri?-ç?k? ayarlama
    TRISB = 0;
    // Port temizleme
    PORTB = 0;
    // PR2 de?eri (sayma i?leminin bitece?i nokta)
    PR2 = 255;
    
    while(1);
}
