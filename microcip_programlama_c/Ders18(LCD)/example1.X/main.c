/*
 * File:   main.c
 * Author: 90541
 *
 * Created on 30 Aral?k 2021 Per?embe, 19:00
 */


#include <xc.h>
#include "LCD_LIB.h"

void turkishCharacter(){

    // Ç character
    lcd_command(0x40);  send_data(14);
    lcd_command(0x41);  send_data(17);
    lcd_command(0x42);  send_data(16);
    lcd_command(0x43);  send_data(16);
    lcd_command(0x44);  send_data(16);
    lcd_command(0x45);  send_data(21);
    lcd_command(0x46);  send_data(14);
    lcd_command(0x47);  send_data(0);
    
    // G character
    lcd_command(0x48);  send_data(14);
    lcd_command(0x49);  send_data(0);
    lcd_command(0x4A);  send_data(15);
    lcd_command(0x4B);  send_data(16);
    lcd_command(0x4C);  send_data(19);
    lcd_command(0x4D);  send_data(17);
    lcd_command(0x4E);  send_data(15);
    lcd_command(0x4F);  send_data(0);
    
    // ? character
    lcd_command(0x50);  send_data(4);
    lcd_command(0x51);  send_data(0);
    lcd_command(0x52);  send_data(4);
    lcd_command(0x53);  send_data(4);
    lcd_command(0x54);  send_data(4);
    lcd_command(0x55);  send_data(4);
    lcd_command(0x56);  send_data(4);
    lcd_command(0x57);  send_data(0);
    
    lcd_command(firstRow);
}

void main(void) {
    
    TRISD   = 0;
    PORTD   = 0;
    
    lcd_prepare();
    turkishCharacter();
    send_data(0);
    send_data(1);
    send_data(2);
    
    while(1);

}
