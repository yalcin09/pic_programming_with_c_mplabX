#include "LCD_LIB.h"

void wait(void){
    __delay_us(250);
}

void send_data(unsigned char c){
    RW          = 0;
    RS          = 1;
    E           = 1;
    PORT_LCD    = ((c & 0xF0) | (PORT_LCD & 0x0F));
    E           = 0;
    wait();
    E           = 1;
    PORT_LCD    = (((c & 0x0F) << 4) | (PORT_LCD & 0x0F));
    E           = 0;
    wait();
}

void lcd_clean(void){
    lcd_command(clean);
    __delay_ms(2);
}

void lcd_write(const char *s){
    wait();
    while(*s){
        send_data(*s++);
    }
}

void lcd_gotoxy(unsigned char x, unsigned char y){
    if(x == 1)
        lcd_command(0x80 + ((y - 1) % 16));
    else
        lcd_command(0xC0 + ((y - 1) % 16));
}

void lcd_prepare(void){
    RS          = 0;
    RW          = 0;
    E           = 0;
    __delay_ms(15);
    E           = 1;
    lcd_command(0x02);
    __delay_ms(2);
    lcd_command(pairRow);
    lcd_command(rightWrite);
    lcd_command(hideCursor);
    lcd_clean();
    lcd_command(firstRow);
}

void lcd_command(unsigned char c){
    RW          = 0;
    RS          = 0;
    E           = 1;
    PORT_LCD    = ((c & 0xF0) | (PORT_LCD & 0x0F));
    E           = 0;
    wait();
    E           = 1;
    PORT_LCD    = (((c & 0x0F) << 4) | (PORT_LCD & 0x0F));
    E           = 0;
    wait();   
}