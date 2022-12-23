#ifndef HUE_FADE_H
#define HUE_FADE_H
#include "AbstractMode.h"
class HueFade : public AbstractColorMode
{
public:
    HueFade()
    {
        previous_color = 0xffffff00;
        count = 0;
    }
    const byte id = HUE_FADE_ID;
    LCD_LINE name()
    {
        return LCD_LINE{"Hue Fade"};
    }

    byte *icon()
    {
        return _icon;
    }
    uint32_t get_color(KeyData &key_data, InputState &input_state, bool is_tabbed)
    {
        byte r = 0, g = 0, b = 0;
        int target = count / NUM_PIXELS * 10;
        switch (target % 3)
        {
        case 0:
            r = count % 255;
            b = 255 - r;
            break;
        case 1:
            g = count % 255;
            r = 255 - g;
            break;
        case 2:
            b = count % 255;
            g = 255 - b;
            break;
        }
        ++count;
        return RGBWPixel(r, g, b, input_state.W);
    }
    LCD_LINE show_settings(bool is_tabbed)
    {
        LCD_LINE rtrn = LCD_LINE{""};
        snprintf(rtrn.str, 17, "C2: #%06x");
        return LCD_LINE{"#"};
    }

private:
    uint32_t previous_color;
    int count;
    byte _icon[8] = {
        0b00000000,
        0b01111110,
        0b01000000,
        0b01111110,
        0b01000000,
        0b01000000,
        0b01000000,
        0b00000000};
};
#endif