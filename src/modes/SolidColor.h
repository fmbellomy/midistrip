#ifndef SOLID_COLOR_H
#define SOLID_COLOR_H
#include "AbstractMode.h"
#include "../util/KeyData.h"
#include "../util/RGBWPixel.h"

class SolidColor : public AbstractColorMode
{
public:
    const byte id = SOLID_COLOR_ID;
    const char name[17] = "Solid Color";
    const byte icon[8] = {
        0b11111111,
        0b11111111,
        0b11111111,
        0b11111111,
        0b11111111,
        0b11111111,
        0b11111111,
        0b11111111};
    uint32_t getColor(int _, KeyData &key_data, InputState &input_state)
    {
        if (key_data.is_held)
        {
            return rgbw_to_uint32(
                RGBWPixel{
                    .R = input_state.R,
                    .G = input_state.G,
                    .B = input_state.B,
                    .W = input_state.W});
        }
        else
        {
            return DECAY(key_data.previous_color);
        }
    }
    LCD_LINE showSettings(bool is_tabbed, InputState &input_state)
    {
        LCD_LINE rtrn = LCD_LINE{.str = ""};
        snprintf(rtrn.str, 17, "C2: #%06x",
                 rgbw_to_uint32(
                     RGBWPixel{
                         .R = input_state.R,
                         .G = input_state.G,
                         .B = input_state.B,
                         .W = input_state.W}));
        return rtrn;
    }

private:
};
#endif