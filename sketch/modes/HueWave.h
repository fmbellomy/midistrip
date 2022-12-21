#ifndef HUE_WAVE_H
#define HUE_WAVE_H
#include "AbstractMode.h"
class HueWave : public AbstractColorMode
{
public:
    const byte id = HUE_WAVE_ID;
    LCD_LINE name()
    {
        return LCD_LINE{"Hue Wave"};
    }
    byte *icon()
    {
        return _icon;
    }
    uint32_t getColor(KeyData &key_data, InputState &input_state, bool is_tabbed)
    {
        byte r = 0, g = 0, b = 0;
        int target = count / ((NUM_PIXELS * 10) - (NUM_PIXELS / 2));
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
        0b10000001,
        0b01000010,
        0b01011010,
        0b00100100,
        0b00000000,
        0b00000000,
        0b00000000};
};
#endif