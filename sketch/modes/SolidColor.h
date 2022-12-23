#ifndef SOLID_COLOR_H
#define SOLID_COLOR_H
#include "AbstractMode.h"
#include "../util/KeyData.h"
#include "../util/RGBWPixel.h"

class SolidColor : public AbstractColorMode
{
public:
    const byte id = SOLID_COLOR_ID;
    LCD_LINE name() { return LCD_LINE{"Solid Color"}; }
    byte *icon()
    {
        return _icon;
    }
    uint32_t get_color(int _, KeyData &key_data, InputState &input_state)
    {
        return (uint32_t)input_state;
    }
    LCD_LINE show_settings(bool is_tabbed, InputState &input_state)
    {
        LCD_LINE rtrn = LCD_LINE{""};
        snprintf(rtrn.str, 17, "Color: #%08" PRIx32, (uint32_t)input_state);
        return rtrn;
    }

private:
    byte _icon[8] = {
        0b11111111,
        0b11111111,
        0b11111111,
        0b11111111,
        0b11111111,
        0b11111111,
        0b11111111,
        0b11111111};
};
#endif