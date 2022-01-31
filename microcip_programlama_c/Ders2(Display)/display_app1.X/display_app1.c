/*
 * File:   display_app1.c
 * Author: 90541
 *
 * Created on 26 Aral?k 2021 Pazar, 23:11
 */


#include <xc.h>

// CONFIG
#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer (WDT enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (Power-up Timer is disabled)
#pragma config CP = OFF         // Code Protection bit (Code protection disabled)

#define _XTAL_FREQ 4000000

int i, array[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7C, 0x07, 0x7F, 0x6F}; 

void main(void) {
    
    // Giri? - ç?k?? ayarlama
    TRISB = 0x00;               // B portunun bütün pinleri ç?k?? yap?ld?
    
    // Port temizleme
    PORTB = 0x00;
    
    // Ana kod
    while(1){
        for(i=0; i<10; i++){
            PORTB = [i];   // Dizi elemanlar? s?ral? olarak port B'ye gönderiliyor
            __delay_ms(500);    // 500ms bekleme
        }
    }
    return;
}
