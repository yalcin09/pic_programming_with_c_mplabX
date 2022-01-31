/*
 * File:   TIMER0 INTERRUPT
 * 
 *  INTCON Register'i içerisinde;
 *      GIE biti 1 yap?lacak,
 *      T0IE biti 1 yap?lacak,
 *      Kesme kontrolü için T0IF biti kontrol edilir.
 * 
 *  TIMER0 : 8 bitliktir.
 * 
 *  Timer0 istenilen bir de?er ile 0xFF aras?nda birer birer sayar. Birer birer
 * sayarken 0xFF de?erine kadar sayd?ktan sonra 0x00 de?erine gelir ve i?te 0x00
 * ula?t???nda kesme meydana gelir.
 * 
 *  f_komut = çal??ma frekans? / 4
 *  örnek : 
 *          f_komut = 4MHz / 4 = 1*10e6Hz
 *  
 *  T_komut = 1 / f_komut
 *  örnek :
 *          T_komut = 1 / 1*10e6 = 1*10e-6 = 1usn
 * 
 *  Kesme olu?ma süresi = T_komut*(Bölme oran?)*(256-de?er)
 * 
 *  Bölme oran? için OPTION Register'? kullan?l?r.
 * 
 * OPTION REGISTER'?;
 *  - PORTB ç?k??lar?n?n PULL_UP veya PULL_DOWN yap?lmas?n?,
 *  - Kesme sinyalinin tetikleme kenar?n?n seçilmesini,
 *  - TMR0 ve WDT frekans bölme seçiminin yap?lmas?n?,
 *  - TMR0 ve WDT seçiminin yap?lmas?n?
 * sa?lar.
 * 
 *  Frekans bölme oran? için OPTION REGISTER'?n son 3 bitine (PS2, PS1, PS0) bak?l?r.
 * 
 * --------------------------------
 * | PS2 | PS1 | PS0 | TMR0 | WDT |
 * --------------------------------
 * |  0  |  0  |  0  | 1/2  | 1/1 | 
 * --------------------------------
 * |  0  |  0  |  1  | 1/4  | 1/2 | 
 * --------------------------------
 * |  0  |  1  |  0  | 1/8  | 1/4 | 
 * --------------------------------
 * |  0  |  1  |  1  | 1/16 | 1/8 | 
 * --------------------------------
 * |  1  |  0  |  0  |1/32  |1/16 | 
 * --------------------------------
 * |  1  |  0  |  1  |1/64  |1/32 | 
 * --------------------------------
 * |  1  |  1  |  0  |1/128 |1/64 | 
 * --------------------------------
 * |  1  |  1  |  1  |1/256 |1/128| 
 * --------------------------------
 */


#include <xc.h>

// CONFIG
#pragma config FOSC = XT     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF        // Watchdog Timer (WDT enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (Power-up Timer is disabled)
#pragma config CP = OFF         // Code Protection bit (Code protection disabled)

#define _XTAL_FREQ 4000000

int sayac = 0;

void __interrupt() interrupt_funciton(){
    if(T0IF){
        sayac++;
        if(sayac == 10){
            sayac = 0;
            RB0 = RB0 ^ 1;          // ^ : xor i?lemi 0 xor 0 = 0
                                    //                0 xor 1 = 1
                                    //                1 xor 0 = 1
                                    //                1 xor 1 = 0
        }
    }
    T0IF = 0;
    TMR0 = 61;
}

void main(void) {
    
    GIE  = 1;
    T0IE = 1;               // TIMER0 aktif edildi.
    TMR0 = 61;              // Timer0 ba?lang?ç de?eri 61 olarak ayarland?.
    
    OPTION_REG = 0x07;      // OPTION Register son 3 biti 1 yap?ld?.
                            // 0b0000 0111 (PS2=1,PS1=0,PS0=1)
                            // Bölme oran? 256 olarak ayarlanm?? oldu.
    
    TRISB = 0;
    PORTB = 0;
    
    while(1);
    
    return;
}
