#include "Keypad.h"

// Function name: InitKeypad
void InitKeypad(void)
{
    // Keypad_PORT	    = 0x00;	// Set Keypad port pin values zero
    Keypad_PORT_Direction = 0xF0; // Last 4 pins input, First 4 pins output

    // OPTION_REG &= 0x7F;
}

char keypad_scanner(void)
{
    C1 = 1;
    C2 = 0;
    C3 = 0;
    C4 = 0;

    if (R1 == 1)
    {
        __delay_ms(20);
        if (R1 == 1)
        {
            while (R1 == 1)
                ;
            return '1';
        }
    }
    if (R2 == 1)
    {
        __delay_ms(20);
        if (R2 == 1)
        {
            while (R2 == 1)
                ;
            return '2';
        }
    }
    if (R3 == 1)
    {
        __delay_ms(20);
        if (R3 == 1)
        {
            while (R3 == 1)
                ;
            return '3';
        }
    }
    if (R4 == 1)
    {
        __delay_ms(20);
        if (R4 == 1)
        {
            while (R4 == 1)
                ;
            return 'A';
        }
    }

    C1 = 0;
    C2 = 1;
    C3 = 0;
    C4 = 0;

    if (R1 == 1)
    {
        __delay_ms(20);
        if (R1 == 1)
        {
            while (R1 == 1)
                ;
            return '4';
        }
    }
    if (R2 == 1)
    {
        __delay_ms(20);
        if (R2 == 1)
        {
            while (R2 == 1)
                ;
            return '5';
        }
    }
    if (R3 == 1)
    {
        __delay_ms(20);
        if (R3 == 1)
        {
            while (R3 == 1)
                ;
            return '6';
        }
    }
    if (R4 == 1)
    {
        __delay_ms(20);
        if (R4 == 1)
        {
            while (R4 == 1)
                ;
            return 'B';
        }
    }

    C1 = 0;
    C2 = 0;
    C3 = 1;
    C4 = 0;

    if (R1 == 1)
    {
        __delay_ms(20);
        if (R1 == 1)
        {
            while (R1 == 1)
                ;
            return '7';
        }
    }
    if (R2 == 1)
    {
        __delay_ms(20);
        if (R2 == 1)
        {
            while (R2 == 1)
                ;
            return '8';
        }
    }
    if (R3 == 1)
    {
        __delay_ms(20);
        if (R3 == 1)
        {
            while (R3 == 1)
                ;
            return '9';
        }
    }
    if (R4 == 1)
    {
        __delay_ms(20);
        if (R4 == 1)
        {
            while (R4 == 1)
                ;
            return 'C';
        }
    }

    C1 = 0;
    C2 = 0;
    C3 = 0;
    C4 = 4;

    if (R1 == 1)
    {
        __delay_ms(20);
        if (R1 == 1)
        {
            while (R1 == 1)
                ;
            return '*';
        }
    }
    if (R2 == 1)
    {
        __delay_ms(20);
        if (R2 == 1)
        {
            while (R2 == 1)
                ;
            return '0';
        }
    }
    if (R3 == 1)
    {
        __delay_ms(20);
        if (R3 == 1)
        {
            while (R3 == 1)
                ;
            return '#';
        }
    }
    if (R4 == 1)
    {
        __delay_ms(20);
        if (R4 == 1)
        {
            while (R4 == 1)
                ;
            return 'D';
        }
    }

    return 'n';
}

// Function name: GetKey
// Read pressed key value from keypad and return its value
char switch_press_scan(void) // Get key from user
{
    char key = 'n'; // Assume no key pressed

    while (key == 'n')          // Wait untill a key is pressed
        key = keypad_scanner(); // Scan the keys again and again

    return key; // when key pressed then return its value
}