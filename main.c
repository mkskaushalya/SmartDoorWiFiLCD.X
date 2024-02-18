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

//LED Sensor
#define TRISLEDSensor TRISBbits.TRISB4
#define LEDSensor PORTBbits.RB4

//Door lock motor wires
#define TRISLockV TRISBbits.TRISB6
#define LockV PORTBbits.RB6

#define TRISLockG TRISBbits.TRISB5
#define LockG PORTBbits.RB5


unsigned char StringReceive[30]; //Received Strings
unsigned int pos; // StringReceives
char StringDisplay[32];
int doorStatus = 0; // 1 is open 0 close
int StatusChange = 0;
int doorClose = 0;
int LEDO = 0;

//functions defining
void picInit();
//void checkIR();
void openDoor();
void closeDoor();
void setDoorStatus();
void ClearStringReceive();

void __interrupt() ISR() {
    if (PIR1bits.RCIF == 1 && pos < 30) { // Check if USART RX interrupt flag is set
        StringReceive[pos] = RCREG; // Read the received data
        pos++;        
        RCIF = 0;
        
    }
    
    setDoorStatus();
}

void main(void){
    picInit();
    //LCD_clear();
    //LCD_cursor_set(1, 1);

    while(1){
        // Start ADC conversion
        GO_nDONE = 1;
//        LCD_cursor_set(2, 1);
//        LCD_write_string("SLTC 21UG0625 ICE");

        // Wait for conversion to complete
        while(GO_nDONE);
       // Read ADC result
        unsigned int adcResult = ADRESH << 8 | ADRESL;
        if(adcResult > 300 && doorStatus == 1){
            closeDoor();
        }
        if(adcResult < 300 && doorStatus == 0){
            openDoor();
        }
        
//        if(adcResult < 300 && LEDO == 0 && doorStatus == 1){
//            LEDO = 1;
//            //LCD_cursor_set(2, 1);
//            //LCD_write_string("LED ON ");
//            
//            doorClose = 1; 
//            StatusChange = 1;
//            
//            //LCD_write_variable(LEDO, 1);  
//        }else if(LEDO == 1&& doorStatus == 0 ){
//            //LCD_cursor_set(2, 1);
//            //LCD_write_string("LED OFF");
//            doorClose = 0;
//            StatusChange = 1;
//            LEDO = 0;
//            //LCD_write_variable(LEDO, 1);  
//        }
        //LCD_cursor_set(2, 1);
        //LCD_write_string("                ");
        
        
        LCD_cursor_set(1, 1);
        if(doorStatus == 0 && doorClose == 0 && IRSensor == 1){
            
            openDoor();
//            __delay_ms(10000);
            closeDoor();
//            __delay_ms(10000);
        }
        if(doorClose == 0 && doorStatus == 1 && StatusChange == 1){
            closeDoor();
            StatusChange = 0;
        }
        if(doorClose == 1 && doorStatus == 0 && StatusChange == 1){
            openDoor();
//            int i = 0;
//            while(doorClose == 1 && i < 100){
//                //LCD_cursor_set(2, 1);
//                __delay_ms(100);
//                
//                i++;
//            }
            //closeDoor();
            StatusChange = 0;
        }
        
        
        
//        LCD_clear();
//        LCD_cursor_set(2, 1);
//        LCD_write_string("Open Door");
//        openDoor();
//        __delay_ms(5000);
//        LCD_clear();
//        LCD_cursor_set(2, 1);
//        LCD_write_string("Close Door");
//        closeDoor();
//        __delay_ms(5000);
//        
//        
//        
//        if(StatusChange == 1){
//            checkIR();
//            StatusChange = 0;
//        }
    }


}

void picInit(){
    TRISIRSensor = 1; // Set IRSensor as input
    TRISLEDSensor = 1;
    TRISLockV = 0; // Set IRSensor as output
    TRISLockG = 0; // Set IRSensor as output
    ADCON1 = 0x80;  // Set AN0 to analog mode, Vref+ and Vref- are VDD and VSS
    ADCON0 = 0x01;  // Select channel 0 (AN0)
    
    InitUART();
    
    LCD_init();
    LCD_clear();
    LCD_cursor_set(1, 1);
    
            // Start ADC conversion
    GO_nDONE = 1;
//        LCD_cursor_set(2, 1);
//        LCD_write_string("SLTC 21UG0625 ICE");

    // Wait for conversion to complete
    while(GO_nDONE);
   // Read ADC result
    unsigned int adcResult = ADRESH << 8 | ADRESL;

    LCD_write_string("PIC Initialized");
    __delay_ms(1000);
    LCD_clear();
    closeDoor();
}

void openDoor(){
    LCD_clear();
    doorStatus = 1;
    LCD_cursor_set(1, 1);
    LCD_write_string("Door Opening");
    LockV = 1;
    LockG = 0;
    __delay_ms(750);
    LCD_clear();
    LCD_cursor_set(1, 1);
    LCD_write_string("Door Opened");
    LockV = 1;
    LockG = 1;
    StatusChange = 0;
}

void closeDoor(){
    LCD_clear();
    LCD_cursor_set(1, 1);
    LCD_write_string("IR Checking");
    if(IRSensor != 0){
        while(IRSensor != 0){
        
        }
    }
    LCD_clear();
    doorStatus = 0;
    LCD_cursor_set(1, 1);
    LCD_write_string("Door Closing");
    LockV = 0;
    LockG = 1;
    __delay_ms(750);
    LCD_clear();
    LCD_cursor_set(1, 1);
    LCD_write_string("Door Closed");
    LockV = 0;
    LockG = 0;
    StatusChange = 0;
}


void ClearStringReceive()    {
    pos = 0;
    for (int i = 0; i < 30; i++)
        StringReceive[i] = '\0';
}
void setDoorStatus(){
    if(strstr(StringReceive, "O") != NULL){
        doorClose = 1; 
        StatusChange = 1;
        ClearStringReceive();
    }if(strstr(StringReceive, "C") != NULL){
        doorClose = 0;
        StatusChange = 1;
        ClearStringReceive();
    }

    if(pos >= 30){       
        ClearStringReceive();
        LCD_cursor_set(2, 1);
        LCD_write_string("                ");
    }
}