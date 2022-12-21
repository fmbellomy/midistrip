#ifndef HUE_FADE_H
#define HUE_FADE_H
#include "AbstractMode.h"
class HueFade : public AbstractColorMode
{
public:
    HueFade()
    {
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
    uint32_t getColor(KeyData &key_data, InputState &input_state, bool is_tabbed)
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
        return rgbw_to_uint32(RGBWPixel{
            .R = r,
            .G = g,
            .B = b,
            .W = input_state.W});
    }
    LCD_LINE showSettings(bool is_tabbed)
    {
        return LCD_LINE{""};
    }

private:
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