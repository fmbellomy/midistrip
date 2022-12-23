#ifndef GRADIENT_H
#define GRADIENT_H
#include "AbstractMode.h"
class Gradient : public AbstractColorMode
{
public:
    const byte id = GRADIENT_ID;
    LCD_LINE name()
    {
        return LCD_LINE{"Gradient"};
    }

    byte *icon()
    {
        return _icon;
    }
    Gradient()
    {
        _c1 = 0xffffff00;
        _c2 = 0xffffff00;
    }
    Gradient(AbstractColorMode);
    uint32_t get_color(KeyData &key_data, InputState &input_state, bool is_tabbed)
    {
        _update_color(is_tabbed, (uint32_t)input_state);
        RGBWPixel a = RGBWPixel(_c1);
        RGBWPixel b = RGBWPixel(_c2);
        return (uint32_t)a.lerp(b, key_data.pitch / 87.0);
    }
    LCD_LINE show_settings(bool is_tabbed, InputState &input_state)
    {
        LCD_LINE rtrn = LCD_LINE{""};
        if (is_tabbed)
        {
            snprintf(rtrn.str, 17, "C2: #%06x", _c2);
        }
        else
        {
            snprintf(rtrn.str, 17, "C1: #%06x", _c1);
        }
        return rtrn;
    }

private:
    uint32_t _c1;
    uint32_t _c2;
    void _update_color(bool is_tabbed, uint32_t color)
    {
        if (is_tabbed)
        {
            _c1 = color;
        }
        else
        {
            _c2 = color;
        }
    }
    byte _icon[8] = {
        0b00000001,
        0b00000010,
        0b00000100,
        0b00001000,
        0b00010000,
        0b00100000,
        0b01000000,
        0b10000000};
};
#endif