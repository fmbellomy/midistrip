#ifndef INPUT_H
#define INPUT_H
struct InputState
{
    bool right;
    bool left;
    bool tab;
    uint8_t R;
    uint8_t G;
    uint8_t B;
    uint8_t W;
};
class Knob
{
public:
    Knob() = default;

    Knob(byte pin)
    {
        _pin = pin;
    }
    // Read the state of a knob
    // Return value ranges from 0 to 255.
    byte read()
    {
        // analogRead returns a range of 0 at 0v to 1023 at 5v.
        return (byte)((analogRead(_pin) * 255) / 1023);
    }

private:
    byte _pin;
};

class Button
{
public:
    Button() = default;
    Button(byte pin)
    {
        _pin = pin;
    }
    bool read()
    {
        return digitalRead(_pin);
    }

private:
    byte _pin;
};

/// @brief Class to simplify setting up and accessing input values.
class Input
{
public:
    Input(byte k0_pin, byte k1_pin,
          byte k2_pin, byte k3_pin,
          byte button_left_pin, byte button_right_pin,
          byte button_tab_pin)
    {
        // R
        _knobs[0] = Knob(k0_pin);
        // G
        _knobs[1] = Knob(k1_pin);
        // B
        _knobs[2] = Knob(k2_pin);
        // W
        _knobs[3] = Knob(k3_pin);
        _left = Button(button_left_pin);
        _right = Button(button_right_pin);
        _tab = Button(button_tab_pin);
    }
    bool is_left_pressed()
    {
        return _left.read();
    }
    bool is_right_pressed()
    {
        return _right.read();
    }
    bool is_tab_pressed()
    {
        return _tab.read();
    }
    InputState read_all()
    {
        return InputState{
            .right = is_right_pressed(),
            .left = is_left_pressed(),
            .tab = is_tab_pressed(),
            .R = read_knob(0),
            .G = read_knob(1),
            .B = read_knob(2),
            .W = read_knob(3)};
    }

    /// @brief
    /// @param knob_num number from 0 to 3; address of which knob you're reading.
    /// @return value from 0 to 255 from knob
    byte read_knob(int knob_num)
    {
        return _knobs[knob_num].read();
    }

private:
    Knob _knobs[4];
    Button _left;
    Button _right;
    Button _tab;
};
#endif