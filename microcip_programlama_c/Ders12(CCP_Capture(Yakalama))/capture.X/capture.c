/*
 * File:   CCP -> CAPTURE (YAKALAMA)
 * 
 * ---------------------------------------------------------
 * |           CCP1CON1 / CCPCON2 REGISTER                 |
 * ---------------------------------------------------------
 * |  -   |  -   |CCPxX |CCPxY |CCPcM3|CCPcM2|CCPcM1|CCPcM0|
 * ---------------------------------------------------------
 * | Bit7 | Bit6 | Bit5 | Bit4 | Bit3 | Bit2 | Bit1 | Bit0 |
 * ---------------------------------------------------------
 * 
 *  - CCPxX / CCPxY : PWM i?leminde görev çevriminin (duty cycle) iki
 * LSB bitidir.
 * 
 *  - CCPxM3 / CCPxM0 : CCP birimleri için mod seçme bitleridir.
 * 
 * -----------------------------------------------------------------
 * |CCPcM3|CCPcM2|CCPcM1|CCPcM0|             Durum                 |
 * -----------------------------------------------------------------
 * |   0  |   0  |   0  |   0  | CCP Etkin de?il                   |
 * -----------------------------------------------------------------
 * |   0  |   1  |   0  |   0  | Her dü?en kenarda                 |
 * -----------------------------------------------------------------
 * |   0  |   1  |   0  |   1  | Her yükselen kenarda              |
 * -----------------------------------------------------------------
 * |   0  |   1  |   1  |   0  | Her 4. yükselen kenarda           |
 * -----------------------------------------------------------------
 * |   0  |   1  |   1  |   1  | Her 16. yükselen kenarda          |
 * -----------------------------------------------------------------
 * |   1  |   0  |   0  |   0  | E?le?me durumunda ç?k?? 1         |
 * -----------------------------------------------------------------
 * |   1  |   0  |   0  |   1  | E?le?me durumunda ç?k?? 0         |
 * -----------------------------------------------------------------
 * |   1  |   0  |   1  |   0  | E?le?me yaz?l?m kesmesi üretir    |
 * -----------------------------------------------------------------
 * |   1  |   0  |   1  |   1  | Kesme olu?ur ve Timer0 resetlenir |
 * -----------------------------------------------------------------
 * |   1  |   1  |   X  |   X  | PWM MODE                          |
 * -----------------------------------------------------------------
 * 
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
int time;

void __interrupt() interrupt_function(){
    if(TMR1IF == 1){
        count++;
    }
    if(CCP1IF == 1){
        time = (65536 * count + CCPR1 ) / 1000000;
        if(time >= 255){
            time = 0;
            count = 0;
        }
        PORTB = time;
        count = 0;
    }
    TMR1IF = 0;
    CCP1IF = 0;
}

void main(void) {
    
    GIE     = 1;             // Genel olarak kesmeler aktif edilebilir
    PEIE    = 1;             // Çevresel kesme aktif
    TMR1IE  = 1;             // Timer1 kesmesi aktif
    TMR1CS  = 0;             // Timer1 zamanlay?c? olarak ayarland?
    T1CKPS1 = 0;
    T1CKPS0 = 0;             // Timer1 bölme oran? 1 olarak ayarland?.
    TMR1ON  = 1;             // Timer1 çal???r 
    TMR1    = 0;             // Timer1 ba?lang?ç de?eri
    
    TRISB   = 0x00;
    TRISC   = 0x04;          // RC2 pini giri? yap?ld?
    
    PORTB   = 0x00;          // PORTB temizlendi.
    
    CCP1M0  = 1;             // Her yükselen kenarda yakala
    CCP1M1  = 0;
    CCP1M2  = 1;
    CCP1M3  = 0;
    
    CCP1IE  = 1;             // CCP1 kesmesi aktif
    
    while(1);
    
    return;
}
