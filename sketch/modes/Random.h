#ifndef RANDOM_H
#define RANDOM_H

class Random : public AbstractColorMode
{
public:
    const byte id = RANDOM_ID;
    LCD_LINE name()
    {
        return LCD_LINE{"Random"};
    }
    byte *icon()
    {
        return _icon;
    }
    uint32_t get_color(KeyData &key_data, InputState &input_state, bool is_tabbed)
    {
        uint32_t color = random();
        // return random color, but still use the brightness from key_data.
        return (color - ~(color & 0xff)) + (key_data.previous_color & 0xff);
    }
    LCD_LINE show_settings(bool is_tabbed)
    {
        return LCD_LINE{""};
    }

private:
    byte _icon[8] = {
        0b01011100,
        0b10100010,
        0b00001000,
        0b01000110,
        0b10100110,
        0b10001010,
        0b11110111,
        0b10001101};
};
#endif