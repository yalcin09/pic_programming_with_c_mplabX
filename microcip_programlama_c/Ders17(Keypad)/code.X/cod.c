/*
 * File:   cod.c
 * Author: 90541
 *
 * Created on 30 Aral?k 2021 Per?embe, 00:52
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

int keypad_array[] = {0x11, 0x12, 0x14,
                      0x21, 0x22, 0x24,
                      0x41, 0x42, 0x44,
                      0x81, 0x82, 0x84};

int display_array[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7C, 0x07, 0x7F, 0x6F};
int numbers[] = {0x3F, 0x3F, 0x3F, 0x3F};

int step = 0, count = 0;

void __interrupt() interrupt_function(void){
    
    int number;
    
    if(RBIF){
        for(number = 0; number < 12; number++){
            if(PORTB == keypad_array[number])
                break;
        }
        
        switch (number){
            case 0:
                numbers[step]   = display_array[1];
                break;
            case 1:
                numbers[step]   = display_array[2];
                break;
            case 2:
                numbers[step]   = display_array[3];
                break;
            case 3:
                numbers[step]   = display_array[4];
                break;   
            case 4:
                numbers[step]   = display_array[5];
                break;
            case 5:
                numbers[step]   = display_array[6];
                break;
            case 6:
                numbers[step]   = display_array[7];
                break;
            case 7:
                numbers[step]   = display_array[8];
                break;
            case 8:
                numbers[step]   = display_array[9];
                break;
            case 9:
                //numbers[step]   = display_array[0];
                break;
            case 10:
                numbers[step]   = display_array[0];
                break;
            case 11:
                //numbers[step]   = display_array[0];
                break;
        }
        
    step++;
    if(step == 4)
        step = 0;    
    __delay_ms(1);
    RBIF    = 0;
    }
    
    if(TMR1IF){
        
        //KEYPAD
        PORTB <<= 1;
        if(RB3 == 1)
            PORTB   = 0x01;
        
        //TIMER1 RESET
        TMR1IF    = 0;
        TMR0    = 15536;
    }
}

void main(void) {
    
    GIE     = 1;
    PEIE    = 1;
    RBIE    = 1;
    TMR1IE  = 1;
    
    T1CKPS1  = 0;           // TIMER1 bölme oran? 1 al?nd?.
    T1CKPS0  = 0;           //
    TMR1CS   = 0;           // TIMER1 zamanlay?c? olarak ayarland?.
    TMR1ON   = 1;           // TIMER1 çal??t?r?ld?
    TMR1     = 15536;       // TMR1 = 15536 => 0.05 sn
    
    TRISB   = 0xF0;
    TRISD   = 0x00;
    
    
    PORTB   = 0x01;
    PORTD   = 0x00;
    
    while(1){
    }
}
