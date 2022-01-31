#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h> 

// CONFIG
#pragma config FOSC = XT        // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config CP = OFF         // FLASH Program Memory Code Protection bits (Code protection off)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low Voltage In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EE Memory Code Protection (Code Protection off)
#pragma config WRT = OFF         // FLASH Program Memory Write Enable (Unprotected program memory may be written to by EECON control)

#define _XTAL_FREQ 4000000


#define RS              RD0
#define RW              RD1
#define E               RD2
#define PORT_LCD        PORTD

#define clean           1
#define upCursor        2
#define leftWrite       4
#define rightWrite      6
#define hideCursor      12
#define downCursor      14
#define clippingCursor  15
#define backCursor      16
#define rightSlide      24
#define leftSlide       28
#define closeLCD        8
#define firstRow        128
#define secondRow       192
#define charGenerateAd  64    
#define pairRow         40
#define singleRow       32

extern void wait(void);
extern void send_data(unsigned char c);
extern void lcd_clean(void);
extern void lcd_write(const char *s);
extern void lcd_gotoxy(unsigned char x, unsigned char y);
extern void lcd_prepare(void);
extern void lcd_command(unsigned char c);

#endif