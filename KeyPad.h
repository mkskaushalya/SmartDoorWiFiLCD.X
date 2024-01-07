#ifndef __KEYPAD_H
#define __KEYPAD_H
#include <xc.h>

#define _XTAL_FREQ 4000000 //Crystal Frequency, used in delay

// Define pins
#define R1 PORTBbits.RB0
#define R2 PORTBbits.RB1
#define R3 PORTBbits.RB2
#define R4 PORTBbits.RB3
#define C1 PORTBbits.RB4
#define C2 PORTBbits.RB5
#define C3 PORTBbits.RB6
#define C4 PORTBbits.RB7

#define Keypad_PORT	PORTB
#define Keypad_PORT_Direction TRISB




// Function declarations
void InitKeypad(void);
char switch_press_scan(void);

#endif