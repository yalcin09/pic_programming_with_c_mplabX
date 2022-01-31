/*
 * File : TIMER1 Register
 * 
 * For PIC16F877:
 * 
 * ---------------------------------------------------------
 * |                    INTCON REGISTER                    |
 * ---------------------------------------------------------
 * |  GIE | PEIE | TOIE | INTE | RBIE | TIF  | INTF | RBIF |
 * ---------------------------------------------------------
 * | Bit7 | Bit6 | Bit5 | Bit4 | Bit3 | Bit2 | Bit1 | Bit0 |
 * ---------------------------------------------------------
 * 
 *  INTCON saklayic?lar?n?n 7,6,5,4 ve 3. bitleri kesme yetkilendirme bitidir.
 * Bu bitlerin de?eri 0 olursa kesme pasif, 1 olursa kesme aktif edilmi? olur.
 * 2,1 ve 0. bitler ise kesme g�sterge bitleridir. Kesme olu?tu?u anda 1 de?erini
 * al?rlar.
 * 
 *  GIE  : T�m kesmeleri yetkilendirme biti,
 *  PEIE : �evresel kesme yetkilendirme biti (PIC16F84A'da EIEE olarak ge�iyor)
 *  TOIE : TMR0 say?c? kesme yetkilendirme biti,
 *  INTE : Harici kesme (RB0) yetkilendirme bayra??,
 *  RBIE : PORTB (4,5,6,7) kesmesi yetkilendirmebiti,
 *  T0IF : TMR0 say?c? kesmesi g�sterge bayra??,
 *  INTF : Harici kesme g�sterge bayra??,
 *  RBIF : PortB (4,5,6,7) kesmesi g�sterge bayra??.
 * 
 * *****************************************************************************
 * 
 * -----------------------------------------------------------------
 * |                            PIE1 REGISTER                       |
 * ------------------------------------------------------------------
 * | PSPIE | ADIE | RCIE | TXIE | SSPIE | CCP1IE  | TMR2IE | TMR1IE |
 * ------------------------------------------------------------------
 * |  Bit7 | Bit6 | Bit5 | Bit4 |  Bit3 |   Bit2  |   Bit1 |  Bit0  |
 * ------------------------------------------------------------------
 * 
 *  - PSPIE  : Paralel port okuma/yazma yetkilendirme biti
 *  - ADIE   : A/D d�n�?t�rme kesme yetkilendirme biti
 *  - RCIE   : USART alma kesme yetkilendirme biti
 *  - TXIE   : USART g�nderme kesme yetkilendirme biti
 *  - SSPIE  : Senkron seri port kesme yetkilendirme biti
 *  - CCP1IE : Yakalama/Kar??la?t?rma/PWM kesme yetkilendirme biti
 *  - TMR2IE : TMR2 kesme g�sterge biti
 *  - TMR1IF : TMR1 kesme g�sterge biti
 * 
 * *****************************************************************************
 * 
 * * -----------------------------------------------------------------
 * |                            T1CON REGISTER                       |
 * ------------------------------------------------------------------
 * |  -   |   -  | T1CKPS1 | T1CKPS0 | T1OSCEN | T1SYNC | TMR1CS | TMR1ON |
 * ------------------------------------------------------------------
 * | Bit7 | Bit6 |   Bit5  |   Bit4  |  Bit3   |  Bit2  |   Bit1 |  Bit0  |
 * ------------------------------------------------------------------
 * 
 * B�lme ORANI:
 *  T1CKPS1-T1CKP0:
 *  ----------------------------
 *  | T1CKPS1 | T1CKPS0 | ORAN |
 *  ----------------------------
 *  |    0    |    0    |  1/1 |
 *  ----------------------------
 *  |    0    |    1    |  1/2 |
 *  ----------------------------
 *  |    1    |    0    |  1/4 |
 *  ----------------------------
 *  |    1    |    1    |  1/8 |
 *  ----------------------------
 * 
 *  - T1OSCEN : TIMER1 Osilat�r yetkilndirme biti. Dahili (32.768Hz)
 * osilat�r devresi vard?r i�erisinde ve PIC uyku modunda olsada
 * �al??maya devam eder. 
 * 
 *  - T1SYNC : TIMER1 harici saat giri?i e?leme kontrol biti
 *  - TMR1CS : TIMER1 saat kayna?? se�me biti;
 *             TMR1CS biti 0 ise TIMER1 zamanlay?c? olarak,
 *                         1 ise say?c? olarak �al???r.
 *  - TMR1ON : TIMER1 �al??t?rma / durdurma biti;
 *             0 ise TIMER1 durdurulur,
 *             1 ise TIMER1 yetkilendirilir.
 * 
 * *****************************************************************************
 * f_komut = �al??ma frekans? / 4
 * �rnek :
 *          f_komut = 4MHz / 4 = 1*1e6
 * T_komut = 1 / f_komut
 * �rnek :
 *          T_komut = 1 / 1*1e6 = 1*1e-6 = 1usn
 * Kesme olu?turma s�resi = T_komut*(B�lme oran?)*(65536-de?er)
 * �rnek :
 *          0.05sn = 1*1e-6*(1)*(65536-de?er) -> de?er = 15536
 * 
 * TIMER1 ayarlama:
 *  GIE    = 1;     // Genel yetkilendirme aktif
 *  PEIE   = 1;     // �evresel kesme aktif
 *  TMR1IE = 1;     // TIMER1 kesme aktif
 * 
 *  T1CKPS1 = 0;
 *  T1CKPS0 = 0;    // B�lme oran? 1/1 olarak al?nd?.
 * 
 *  TMR1CS  = 1;    // TIMER1 zamanlay?c? olarak ayarland?,
 *  TMR1ON  = 1;    // TIMER1 yetkilendilirdi.
 * 
 * 
 * 
 */


#include <xc.h>

// CONFIG
#pragma config FOSC = XT     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config CP = OFF         // FLASH Program Memory Code Protection bits (Code protection off)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low Voltage In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EE Memory Code Protection (Code Protection off)
#pragma config WRT = ON         // FLASH Program Memory Write Enable (Unprotected program memory may be written to by EECON control)

#define _XTAL_FREQ 4000000

int sayac = 0;

void __interrupt() interrupt_function(){
    if(TMR1IF){
        sayac++;
        if(sayac == 20){
            RB0 = RB0 ^ 1;
            sayac = 0;
        }
    }
    TMR1IF = 0;
    TMR1   = 15536;
}

void main(void){
    
    GIE     = 1;           // Genel olarak b�t�n kesmeler kullan?labilir.
    PEIE    = 1;           // �evresel kesme aktif edildi.
    TMR1IE  = 1;           // TIMER1 kesme aktif edildi.
    T1CKPS1 = 0;
    T1CKPS0 = 0;           // TIMER1 b�lme oran? 1/1 yap?ld?.
    TMR1CS  = 0;           // TIMER1 zamanlay?c? olarak ayarland?
    TMR1ON  = 1;           // TIMER1 a�?ld?.
    TMR1    = 15536;       // TIMER1 saymaya 15536'dan ba?layacak
    
    TRISB = 0;
    PORTB = 0;
    
    while(1);
    
    return;
}
