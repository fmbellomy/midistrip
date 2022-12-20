#include <LedControl.h>

#include <USB-MIDI.h>
#include <Adafruit_NeoPixel.h>
#include "settings/SettingsController.h"
#include "util/PinDefines.h"
#include "util/KeyData.h"

Adafruit_NeoPixel strip(NUM_PIXELS, RGB_STRIP_PIN, NEO_BRG + NEO_KHZ800);

Input inputs = Input(K0_PIN, K1_PIN, K2_PIN, K3_PIN,
                     BUTTON_LEFT_PIN, BUTTON_RIGHT_PIN, BUTTON_TAB_PIN);

USBMIDI_CREATE_DEFAULT_INSTANCE();

void handleNoteOn(byte, byte, byte);
void handleNoteOff(byte, byte, byte);

SettingsController settings;

KeyData key_pixels[NUM_PIXELS];

InputState input_state;
bool last_tab_state;
bool last_right_state;
bool last_left_state;
void processInputs()
{
    if (!last_right_state && input_state.right)
    {
        settings.shift_list(true);
        // debounce
        delay(50);
    }
    if (!last_left_state && input_state.left)
    {
        settings.shift_list(false);
        // debounce
        delay(50);
    }
    if (!last_tab_state && input_state.tab)
    {
        settings.tab();
        // debounce
        delay(50);
    }
    last_tab_state = input_state.tab;
    last_right_state = input_state.right;
    last_left_state = input_state.left;
}

void setup()
{
    setPinStates();
    last_tab_state = digitalRead(BUTTON_TAB_PIN);
    last_right_state = digitalRead(BUTTON_RIGHT_PIN);
    last_left_state = digitalRead(BUTTON_LEFT_PIN);
    settings = SettingsController();
    // default initialize our pixel array
    for (int i = 0; i < NUM_PIXELS; i++)
    {
        key_pixels[i] = KeyData{
            .previous_color = 0xffffff00,
            .is_held = false,
            .velocity = 0,
            .pitch = 0};
    }
    strip.begin();
    MIDI.begin(1);
}

void loop()
{
    MIDI.read();
    input_state = inputs.read_all();
    processInputs();
    settings.display_dotmatrix();
    settings.display_lcd(input_state);
    for (int i = 0; i < NUM_PIXELS; i++)
    {
        uint32_t new_color = settings.getColor(key_pixels[i], input_state);
        key_pixels[i].previous_color = new_color;
        strip.setPixelColor(key_pixels[i].pitch, new_color);
    }
}

#define pitch_to_pixel(X) ((int)(X - 21) * NUM_PIXELS / 88.0)

void handleNoteOn(byte _, byte pitch, byte velocity)
{
    byte pos = pitch_to_pixel(pitch);
    key_pixels[pos].pitch = pitch;
    key_pixels[pos].is_held = true;
    key_pixels[pos].velocity = velocity;
}
void handleNoteOff(byte _, byte pitch, byte velocity)
{
    byte pos = pitch_to_pixel(pitch);
    key_pixels[pos].is_held = false;
}