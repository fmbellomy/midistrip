#ifndef ABSTRACT_MODE_H
#define ABSTRACT_MODE_H

#include <stdint.h>
#include <Adafruit_NeoPixel.h>
#include "Modes.h"
#include "../util/KeyData.h"
#include "../util/RGBWPixel.h"
#include "../settings/Input.h"

#ifndef MODE_IDS
#define MODE_IDS
#define SOLID_COLOR_ID 0
#define RANDOM_ID 1
#define HUE_FADE_ID 2
#define HUE_WAVE_ID 3
#define GRADIENT_ID 4
#define MOVING_GRADIENT_ID 5
#endif

// these macros are useful for classes deriving from this one.
// leave them here.
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define DECAY(a) (MAX((a - 1) & 0xFF, 0))
typedef struct LCD_LINE
{
    char str[17];
};
class AbstractColorMode
{
public:
    byte id;
    char name[17];
    byte icon[8];
    virtual LCD_LINE showSettings(bool is_tabbed, InputState &input_state);
    virtual uint32_t getColor(KeyData &key_data, InputState &input_state, bool is_tabbed);
};

#endif ABSTRACT_MODE_H