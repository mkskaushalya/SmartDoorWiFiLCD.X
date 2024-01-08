#ifndef __KEYPAD_H
#define __KEYPAD_H
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define _XTAL_FREQ 4000000 //Crystal Frequency, used in delay

// Define pins
#define ROWA                    RB0
#define ROWB                    RB1
#define ROWC                    RB2
#define ROWD                    RB3
#define COL1                    RB4
#define COL2                    RB5
#define COL3                    RB6
#define COL4                    RB7
#define ROW_TRIS(x)             (TRISB0=TRISB1=TRISB2=TRISB3=x)
#define COL_TRIS(x)             (TRISB4=TRISB5=TRISB6=TRISB7=x)



    /* Functions */
    void InitKeyPad(void); //ham khi dong Keypad
    char GetKey(void);   //ham lay ki tu
    char ScanKey(void); //Ham quet keypad


    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* KEYPAD_H */


