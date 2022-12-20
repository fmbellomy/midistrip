#ifndef HUE_WAVE_H
#define HUE_WAVE_H
#include "AbstractMode.h"
class HueWave : public AbstractColorMode
{
public:
    const byte id = HUE_WAVE_ID;
    const char name[17] = "Hue Wave";
    const byte icon[8] = {
        0b00000000,
        0b10000001,
        0b01000010,
        0b01011010,
        0b00100100,
        0b00000000,
        0b00000000,
        0b00000000};
    uint32_t getColor(KeyData &key_data, InputState &input_state, bool is_tabbed)
    {
        return 0xffffffff;
    }
    LCD_LINE showSettings(bool is_tabbed)
    {
        return LCD_LINE{.str = ""};
    }
};
#endif