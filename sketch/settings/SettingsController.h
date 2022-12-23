#include "Input.h"
#include "../modes/Modes.h"
#include "../modes/AbstractMode.h"
#include "lcd/LCDController.h"
#include "dotmatrix/DotMatrixController.h"
class SettingsController
{
public:
    SettingsController()
    {
        _index = SOLID_COLOR_ID;
        _mode_list[SOLID_COLOR_ID] = SolidColor();
        _mode_list[RANDOM_ID] = Random();
        _mode_list[HUE_FADE_ID] = HueFade();
        _mode_list[HUE_WAVE_ID] = HueWave();
        _mode_list[GRADIENT_ID] = Gradient();
        _mode_list[MOVING_GRADIENT_ID] = MovingGradient();
        _tabbed = false;
        _lcd = LCDController();
        _dotmatrix = DotMatrixController();
    }
    uint32_t get_color(KeyData &key_data, InputState &input_state)
    {
        if (key_data.is_held)
        {
            return _mode_list[_index].get_color(key_data, input_state, _tabbed);
        }
        else
        {
            return DECAY(key_data.previous_color);
        }
    }
    void display_lcd(InputState &input_state)
    {
        char top[17];
        strncpy(_mode_list[_index].name().str, top, 17);
        char bottom[17];
        strncpy(_mode_list[_index].show_settings(_tabbed, input_state).str, bottom, 17);
        _lcd.show(top, bottom);
    }
    void display_dotmatrix()
    {
        _dotmatrix.draw(_mode_list[_index].icon());
    }
    void shift_list(byte direction)
    {
        if (direction)
        {
            _index = (_index + 1) % NUM_MODES;
        }
        else
        {
            // this is perhaps a little too clever for my own good.
            if (_index-- < 0)
            {
                _index = NUM_MODES;
            }
        }
    }
    void tab()
    {
        _tabbed = !_tabbed;
    }

private:
    LCDController _lcd;
    DotMatrixController _dotmatrix;
    bool _tabbed;
    byte _index;
    AbstractColorMode _mode_list[NUM_MODES];
    AbstractColorMode getActiveMode()
    {
        return _mode_list[_index];
    }
};