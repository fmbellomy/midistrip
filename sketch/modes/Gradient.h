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
    uint32_t getColor(KeyData &key_data, InputState &input_state)
    {
        if (key_data.is_held)
        {
            // this is quite a lot of unnecessary conversions, but hopefully the arduino can handle it.
            RGBWPixel a = uint32_to_rgbw(_c1);
            RGBWPixel b = uint32_to_rgbw(_c2);
            return rgbw_to_uint32(lerp_pixel(a, b, key_data.pitch / 87.0));
        }
        else
        {
            return DECAY(key_data.previous_color);
        }
    }
    void setFirst(uint32_t c1)
    {
        _c1 = c1;
    }
    void setSecond(uint32_t c2)
    {
        _c2 = c2;
    }
    LCD_LINE showSettings(bool is_tabbed)
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
    bool _is_tabbed();
    uint32_t _c1;
    uint32_t _c2;
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