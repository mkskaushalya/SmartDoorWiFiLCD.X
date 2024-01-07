/*
 *           File: LCD.h
 *         Author: Sahan Kaushalya
 *     Created on: 2023/11/14
 *     Email:- mkskaushalya@gmail.com
 *
 *
 * Works with both 4x20 and 2x16 LCD displays.
 */

#ifndef LCD_H
#define LCD_H

//***************************************************************//
//*** "Project Definitions" below has to be changed according ***//
//***      to your connections, including "_XTAL_FREQ"!       ***//
//***        (No need to change other definitions)            ***//
//***************************************************************//

//****************** Project Definitions *** ***************//
#define LCD_RS_TRIS TRISDbits.TRISD2 // TRIS bit of the pin connected to "RS"
#define LCD_EN_TRIS TRISDbits.TRISD3 // TRIS bit of the pin connected to "EN"
#define LCD_D4_TRIS TRISDbits.TRISD4 // TRIS bit of the pin connected to "D4"
#define LCD_D5_TRIS TRISDbits.TRISD5 // TRIS bit of the pin connected to "D5"
#define LCD_D6_TRIS TRISDbits.TRISD6 // TRIS bit of the pin connected to "D6"
#define LCD_D7_TRIS TRISDbits.TRISD7 // TRIS bit of the pin connected to "D7"

#define LCD_RS_LAT PORTDbits.RD2 // LAT/PORT bit of the pin connected to "RS"
#define LCD_EN_LAT PORTDbits.RD3 // LAT/PORT bit of the pin connected to "EN"
#define LCD_D4_LAT PORTDbits.RD4 // LAT/PORT bit of the pin connected to "D4"
#define LCD_D5_LAT PORTDbits.RD5 // LAT/PORT bit of the pin connected to "D5"
#define LCD_D6_LAT PORTDbits.RD6 // LAT/PORT bit of the pin connected to "D6"
#define LCD_D7_LAT PORTDbits.RD7 // LAT/PORT bit of the pin connected to "D7"

#define _XTAL_FREQ 4000000 // Frequency of the sytem clock
//*********************************************************//

//******************* Other Definitions *******************//
#define LCD_BUSY_DELAY 40                               // Minimum delay required by short commands[uS]
#define LCD_BUSY_DELAY_EXTENDED (1600 - LCD_BUSY_DELAY) // Extra delay required by the longer commands[uS]

#define LCD_CMD_FUNCTION_SET 0x28     // Function Set(4-bit, 2 line, 5x8 dots)
#define LCD_CMD_DISPLAY_CONTROL 0x0C  // Display On/Off Control(Display on, cursor off, blinking off)
#define LCD_CMD_ENTRY_MODE 0x06       // Entry Mode Set(Increment, shift off)
#define LCD_CMD_CLEAR 0x01            // Clear Display
#define LCD_CMD_RETURN_HOME 0x02      // Return Home(or shift reset)
#define LCD_CMD_SHIFT_LEFT 0x18       // Shift Left
#define LCD_CMD_SHIFT_RIGHT 0x1C      // Shift Right
#define LCD_CMD_CURSOR_INCREMENT 0x14 // Increment Cursor
#define LCD_CMD_CURSOR_DECREMENT 0x10 // Decrement Cursor
#define LCD_CMD_CGRAM_SET 0x40        // Set CGRAM Address

#define LCD_CMD_DDRAM_LINE_1 (0x80 - 1)  // DDRAM address for line-1(-1 from row starting from 1 instead of 0)
#define LCD_CMD_DDRAM_LINE_2 (0xC0 - 1)  // DDRAM address for line-2(-1 from row starting from 1 instead of 0)
#define LCD_CMD_DDRAM_LINE_3 (0x80 + 19) // DDRAM address for line-3(+19 from 3rd line being the continuation of line-1)
#define LCD_CMD_DDRAM_LINE_4 (0xC0 + 19) // DDRAM address for line-4(+19 from 4th line being the continuation of line-2)
//*********************************************************//

//******************* Dependent Includes ******************//
#include <xc.h>
#include <stdint.h>
#include <math.h>>
//*********************************************************//

//****************** Function prototypes ******************//
void LCD_pulse_clock(void);
void LCD_write_command(char);
void LCD_write_data(char);

void LCD_init(void);
void LCD_cursor_set(uint8_t, uint8_t);
void LCD_cursor_increment(void);
void LCD_cursor_decrement(void);
void LCD_configure_lcd_display(uint8_t);
void LCD_configure_cursor_display(uint8_t);
void LCD_configure_cursor_blink(uint8_t);
void LCD_clear(void);
void LCD_shift_reset(void);
void LCD_shift_left(void);
void LCD_shift_right(void);
void LCD_configure_entry_id(uint8_t);
void LCD_configure_entry_shift(uint8_t);
void LCD_add_character(char *, uint8_t);

void LCD_write_string(char *);
void LCD_write_char(char);
void LCD_write_variable(int32_t, uint8_t);
void LCD_write_float(float, uint8_t, uint8_t);
//*********************************************************//

//******************** Global Variables *******************//
extern uint8_t LCD_display_control;
extern uint8_t LCD_entry_mode;
//*********************************************************//

#endif /* LCD_H */
