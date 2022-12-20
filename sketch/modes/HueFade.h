#ifndef HUE_FADE_H
#define HUE_FADE_H
#include "AbstractMode.h"
class HueFade : public AbstractColorMode
{
public:
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
        return 0xffffffff;
    }
    LCD_LINE showSettings(bool is_tabbed)
    {
        return LCD_LINE{""};
    }

private:
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