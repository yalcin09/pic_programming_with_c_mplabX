/*
 * File:   EEPROM REGISTER
 * 
 * PIC16F84A'da 0x00 ile 0x3F adresleri bellek için ay?l?rm??t?r.
 * 64 bayt büyüklü?ünde EEPROM bellek bulunur.
 * EEPROM için 4 özel saklay?c? bulunmaktad?r.
 *  - EECON1 : Kontrol saklay?c?s?
 *  - EECON2 : Fiziksel bir saklay?c? de?ildir.
 *  - EEDATA : Okunacak veya yaz?lacak veriyi tutar.
 *  - EEADR  : Okuma veya yazma yap?lacak olan belle?in adresini tutar.
 * 
 *  EECON2 register'? yazma veya silme i?lemlerini onaylamak için (güvenlik
 * amaçl?) kullan?lmaktad?r. Yazma veya silme i?lemlerinden önce saklay?c?ya
 * ard???k olarak 0x55 ve 0xAA de?erleri yaz?lmal?d?r.
 * 
 * ---------------------------------------------------------
 * |                    EECON1 REGISTER                    |
 * ---------------------------------------------------------
 * |   -  |   -  |   -  | EEIF |WRERR | WREN |  WR  |  RD  |
 * ---------------------------------------------------------
 * | Bit7 | Bit6 | Bit5 | Bit4 | Bit3 | Bit2 | Bit1 | Bit0 |
 * ---------------------------------------------------------
 * 
 *  - EEIF  : EEPROM kesme gösterge biti (Yazma i?lemi bitince kesme olu?ur)
 *  - WRERR : Hata gösterge biti
 *  - WREN  : EEPROM belle?e yazma i?lemini aktif yapma biti
 *  - WR    : EEPROM belle?e yazma i?lemi ba?latma biti
 *  - RD    : EEPROM belle?e okuma i?lemi ba?latma biti
 *  Yazma i?lemi için WR=1 yap?ld?ktan sonra yazma i?lemi ba?lar ve bitti?inde
 * WR otomatk olarak 0 olur. Ayn? durum RD içinde geçerlidir.
 */


#include <xc.h>

// CONFIG
#pragma config FOSC = XT     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF        // Watchdog Timer (WDT enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (Power-up Timer is disabled)
#pragma config CP = OFF         // Code Protection bit (Code protection disabled)

#define _XTAL_FREQ 4000000

int count = 0;

void __interrupt() interrupt_function(){
    
    if(EEIF){
        EEADR = 0x1F;    // Bellekten ayr?r?lan adres tekrar tan?mland?
        RD    = 1;       // Okuma i?lemi gerçekle?ti. Veri -> EEDATA
        PORTB = EEDATA;  // EEDATA'daki veri PORTB'ye gönderirdi.
    }
    EEIF = 0;
}

void main(void) {
    
    EEIE = 1;               // EEPROM kesmesi aktif edildi.
    
    TRISA = 1;
    TRISB = 0;
    PORTB = 0;
    
    while(1){
        
        if(RA0){
            while(RA0);
            count++;
            EEADR  = 0x1F;   // EEPROM'dan bir adres ay?rt?k.
            EEDATA = count;  // Veri EEPROM'dan ayr?lan bölüme yaz?rd?.
            WREN   = 1;      // Yazma i?lemine izin verirdi.
            EECON2 = 0x55;
            EECON2 = 0xAA;
            WR     = 1;      // Yazma i?lemi gerçekle?ti.
            GIE    = 1;
        }
    }
}
