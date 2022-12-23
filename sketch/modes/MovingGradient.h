#ifndef MOVING_GRADIENT_H
#define MOVING_GRADIENT_H

class MovingGradient : public AbstractColorMode
{
public:
    MovingGradient()
    {
        _c1 = 0xffffff00;
        _c2 = 0xffffff00;
        _count = 0;
    }
    const byte id = MOVING_GRADIENT_ID;
    LCD_LINE name() { return LCD_LINE{"Moving Gradient"}; }
    byte *icon()
    {
        return _icon;
    }
    uint32_t get_color(KeyData &key_data, InputState &input_state, bool is_tabbed)
    {
        ++_count;
        _update_color(is_tabbed, (uint32_t)input_state);
        RGBWPixel a = RGBWPixel(_c1);
        RGBWPixel b = RGBWPixel(_c2);
        int c2_mid = _count % 88;
        if (key_data.pitch <= c2_mid)
        {
            return (uint32_t)a.lerp(b, key_data.pitch * 1.0 / (double)c2_mid);
        }
        else
        {
            return (uint32_t)b.lerp(a, (key_data.pitch - c2_mid) / 88.0 - c2_mid);
        }
    }
    LCD_LINE show_settings(InputState &input_state)
    {
        LCD_LINE rtrn = LCD_LINE{""};
        if (input_state.tab)
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
    int _count;
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
        0b00000111,
        0b00000011,
        0b00011101,
        0b00001100,
        0b01110100,
        0b00110000,
        0b01010000,
        0b10000000};
};

#endif