#ifndef MOVING_GRADIENT_H
#define MOVING_GRADIENT_H

class MovingGradient : public AbstractColorMode
{
public:
    const byte id = MOVING_GRADIENT_ID;
    const char name[17] = "Moving Gradient";
    const byte icon[8] = {
        0b00000111,
        0b00000011,
        0b00011101,
        0b00001100,
        0b01110100,
        0b00110000,
        0b01010000,
        0b10000000};
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