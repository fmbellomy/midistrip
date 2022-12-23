#ifndef PIN_DEFINES_H
#define PIN_DEFINES_H

#define RGB_STRIP_PIN 11
// controls
#define K0_PIN A0
#define K1_PIN A1
#define K2_PIN A2
#define K3_PIN A3
#define BUTTON_RIGHT_PIN 0
#define BUTTON_LEFT_PIN 1
#define BUTTON_TAB_PIN 2
// displays
#define DOTMATRIX_CLK 3
#define DOTMATRIX_CS 4
#define DOTMATRIX_DIN 5

#define LCD_RS 13
#define LCD_ENABLE 12
#define LCD_D4 6
#define LCD_D5 7
#define LCD_D6 8
#define LCD_D7 9

[[deprecated("`util/PinDefines.h::set_pin_states()` has not been implemented! Configure it to fit your board!")]] void set_pin_states()
{
}
#endif