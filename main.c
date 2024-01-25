/*
 * File:   main.c
 * Author: Sahan Kaushalya
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

#pragma warning disable 520 // disabled LCD warnings

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.


#include <xc.h>

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "esp8266.h"
#include "LCD.h"//LCD Library

#define _XTAL_FREQ 4000000    // Set the oscillator frequency (4 MHz)

//IR Sensor
#define TRISIRSensor TRISBbits.TRISB7
#define IRSensor PORTBbits.RB7

//Door lock motor wires
#define TRISLockV TRISBbits.TRISB6
#define LockV PORTBbits.RB6

#define TRISLockG TRISBbits.TRISB5
#define LockG PORTBbits.RB5


unsigned char StringReceive[30]; //Received Strings
unsigned int pos; // StringReceives
char StringDisplay[32];
int doorStatus = 0;
int StatusChange = 0;
//functions defining
void picInit(void);
void checkIR(void);
void openDoor(void);
void closeDoor(void);
void ClearStringReceive();


void main(void){
    picInit();
    LCD_clear();
    
    while(1){
        LCD_clear();
        LCD_cursor_set(2, 1);
        LCD_write_string("Open Door");
        openDoor();
        __delay_ms(5000);
        LCD_clear();
        LCD_cursor_set(2, 1);
        LCD_write_string("Close Door");
        closeDoor();
        __delay_ms(5000);
//        if(StatusChange == 1){
//            checkIR();
//            StatusChange = 0;
//        }
        
    }


}

void picInit(void){
    TRISIRSensor = 1; // Set IRSensor as input
    TRISLockV = 0; // Set IRSensor as output
    TRISLockG = 0; // Set IRSensor as output
    
    InitUART();
    LCD_init();
    LCD_clear();
    LCD_cursor_set(1, 1);
    LCD_write_string("PIC Initialized");
    __delay_ms(1000);
    LCD_clear();
}

//void checkIR(void){
//    if(IRSensor == 1 && doorStatus == 0){
//        LCD_clear();
//        LCD_cursor_set(1, 1);
//        LCD_write_string("Please close door");
//        while(IRSensor == 1);
//        if(IRSensor == 0 && doorStatus == 0){
//            closeDoor();
//        }
//    }else if(IRSensor == 0 && doorStatus == 0){
//        closeDoor();
//    }if(IRSensor == 0 && doorStatus == 1){
//        if(IRSensor == 0){
//            LCD_clear();
//            LCD_cursor_set(1, 1);
//            LCD_write_string("Unlocked, Open Door");
//            
//            //waiting to open door
//            for(int i = 0; i < 50; i++){//5seconds
//                if(IRSensor == 1){
//                    break;
//                }
//                __delay_ms(100);
//            }
//            
//            if(IRSensor == 0){//if not opened door, lock door again
//                doorStatus = 0;
//                closeDoor();
//            }else{//waiting to close door again
//                while(IRSensor == 1);
//                if(IRSensor == 0){
//                    doorStatus = 0;
//                    closeDoor();
//                }
//            }            
//        }
//    }
//}

void openDoor(void){
    if(doorStatus != 1){
        LCD_clear();
        doorStatus = 1;
        LCD_cursor_set(1, 1);
        LCD_write_string("Door Opening");
        LockV = 1;
        LockG = 0;
        __delay_ms(1500);
        LCD_clear();
        LCD_cursor_set(1, 1);
        LCD_write_string("Door Opened");
        LockV = 1;
        LockG = 1;
    }else{
        LCD_clear();
        LCD_cursor_set(1, 1);
        LCD_write_string("Door Opened Before");
    }  
}

void closeDoor(void){
    if(doorStatus != 0){
        LCD_clear();
        doorStatus = 0;
        
        LCD_cursor_set(1, 1);
        LCD_write_string("Door Closing");
        LockV = 0;
        LockG = 1;
        __delay_ms(1500);
        LCD_clear();
        LCD_cursor_set(1, 1);
        LCD_write_string("Door Closed");
        LockV = 0;
        LockG = 0;
        
    }else{
        LCD_clear();
        LCD_cursor_set(1, 1);
        LCD_write_string("Door Closed Before");        
    }
}


void __interrupt() ISR() {
    if (PIR1bits.RCIF == 1 && pos < 30) { // Check if USART RX interrupt flag is set
        StringReceive[pos] = RCREG; // Read the received data
        pos++;        
        RCIF = 0;
    }
    
    if(strstr(StringReceive, "Open") != NULL){
        doorStatus = 1; 
        StatusChange = 1;
        ClearStringReceive();
    }if(strstr(StringReceive, "Close") != NULL){
        doorStatus = 0;
        StatusChange = 1;
        ClearStringReceive();
    }
    
    if(pos >= 30){
        ClearStringReceive();
    }
    
}

void ClearStringReceive()    {
    pos = 0;
    for (int i = 0; i < 30; i++)
        StringReceive[i] = '\0';
}