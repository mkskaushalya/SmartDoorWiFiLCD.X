/*
 * File:   main.c
 * Author: mkska
 *
 * Created on January 5, 2024, 1:23 AM
 */


// CONFIG1
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator: High-speed crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown Out Reset Selection bits (BOR enabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)


// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "LCD.h"
#include "esp8266.h"
#include "KeyPad.h"

#define _XTAL_FREQ 4000000    // Set the oscillator frequency (4 MHz)

#define WIFI_NAME                   "Vinh Bac Bo"
#define PASSWORD                    "barcareal"
#define API                         "9YDIVRVEGBWI8JNF"
#define FIELD                       "field1"
#define WRITE_API_KEY               "9YDIVRVEGBWI8JNF"
#define OK                          'D'
#define CANCEL                      'C'
#define STAR                        '*'
#define SHARP                       '#'
#define MODE_DEFAULT                'B'

unsigned char StringReceive[30]; // Xau chua gia tri gui, nhan tu USART
unsigned int pos; // StringReceives
unsigned char WifiName[30]="_";
unsigned char PassWord[30]="_";
char mode = MODE_DEFAULT;
char StringDisplay[32];
void SetEsp8266AsClient(void);

char StringDisplay[32];
void SetEsp8266AsClient(void);
void ClearStringReceive()    {
    pos = 0;
    for (int i = 0; i < 30; i++)
        StringReceive[i] = '\0';
}

int test = 0;
void main(void){
    LCD_init();
    LCD_clear();
    LCD_cursor_set(1, 1);
    LCD_write_string("LCD_init()");
    __delay_ms(1000);
    InitKeypad();
    LCD_cursor_set(1, 1);
    LCD_write_string("InitKeyPad()");
    __delay_ms(1000);
    
    InitUART();
    LCD_cursor_set(2, 1);
    LCD_write_string("UART Init Success");
    __delay_ms(1000);
    
    /*** SENDING COMMANDS ***/
    
    
    LCD_clear();
    LCD_cursor_set(1, 1);
    SendCommandAT("AT");
    LCD_write_string("AT Sent");
    char x, flag;
    LCD_cursor_set(2, 1);
    SendCommandAT("Waiting to Response");
    while(1){
        x = strstr(StringReceive, "OK"); //Kiem tra phan hoi tu esp8266
        if (x != NULL){
            test = 1;
            SendCommandAT(StringReceive);
            break;
        }
    }
    __delay_ms(1000);
    LCD_clear();
    LCD_cursor_set(1, 1);
    LCD_write_string("Received OK");
    LCD_cursor_set(2, 1);
    LCD_write_string("ESP 8266 Connected");
    __delay_ms(1000);
    SendCommandAT("Received OK");
    SendCommandAT(StringReceive);
    
    __delay_ms(1000);
    
    
    
//    while(1){
//        LCD_clear();
//        LCD_cursor_set(1, 1);
//        LCD_write_string("Received Data");
//        LCD_cursor_set(2, 1);
//        LCD_write_string(StringReceive);
//        __delay_ms(1000);
//        
//    }

    int j = 0;
    LCD_clear();
    LCD_cursor_set(1, 1);
    LCD_write_string("Enter Key");
    char keyvalue = 's';
    while(1){
        LCD_cursor_set(2, 1);
        keyvalue = keypad_scanner();
        LCD_write_char(keyvalue);
//        LCD_clear();
//        LCD_cursor_set(1, 1);
//        LCD_write_string("Enter Key");
//        char Key = 'n';
//        LCD_cursor_set(2, 1);
//        while(1){
//            LCD_write_char('Z');
//            Key = switch_press_scan();
//            LCD_write_char(Key);
//            if(Key == 'C'){
//                break;
//            }
//        }
//        
//        __delay_ms(1000);
        
        
    }
    
        
    // Initialize UART for communication with ESP8266

}

void __interrupt() ISR() {
    if (PIR1bits.RCIF == 1 && pos < 28) { // Check if USART RX interrupt flag is set
        StringReceive[pos] = RCREG; // Read the received data
        pos++;
        
        RCIF = 0;
        // Your code to handle the received data goes here
        // For example, you can store it in a buffer or perform some processing
        
    }
    if(pos > 30){
     ClearStringReceive();
     pos = 0;
    }

}
