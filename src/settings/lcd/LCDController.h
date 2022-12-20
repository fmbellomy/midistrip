#ifndef LCDCONTROLLER_H
#define LCDCONTROLLER_H
#include <LiquidCrystal.h>
#include "../../util/PinDefines.h"
class LCDController
{
public:
    LCDController()
    {
        _lcd.begin(16, 2);
        _lcd.clear();
    }
    void show(const char *top, const char *bottom)
    {
        _lcd.setCursor(0, 0);
        _lcd.print(top);
        _lcd.setCursor(0, 1);
        _lcd.print(bottom);
    }

private:
    LiquidCrystal _lcd = LiquidCrystal(LCD_RS, LCD_ENABLE, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
    char _top_line[17];
    char _bottom_line[17];
};
#endif