
#include <HID.h>
//  tricking MIDIUSB into letting me do as I please.
#include <USB-MIDI.h>
#include <Adafruit_NeoPixel.h>
#include "settings/SettingsController.h"
#include "util/PinDefines.h"
#include "util/KeyData.h"

Adafruit_NeoPixel strip(NUM_PIXELS, RGB_STRIP_PIN, NEO_BRG + NEO_KHZ800);

Input inputs = Input(K0_PIN, K1_PIN, K2_PIN, K3_PIN,
                     BUTTON_LEFT_PIN, BUTTON_RIGHT_PIN, BUTTON_TAB_PIN);

USBMIDI_CREATE_DEFAULT_INSTANCE();

void handle_note_on(byte, byte, byte);
void handle_note_off(byte, byte, byte);

SettingsController settings;

KeyData key_pixels[NUM_PIXELS];

InputState input_state;
bool last_tab_state;
bool last_right_state;
bool last_left_state;
void process_inputs()
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
    MIDI.begin();
}

void loop()
{
    MIDI.read();
    input_state = inputs.read_all();
    process_inputs();
    settings.display_dotmatrix();
    settings.display_lcd(input_state);
    for (int i = 0; i < NUM_PIXELS; i++)
    {
        uint32_t new_color = settings.get_color(key_pixels[i], input_state);
        key_pixels[i].previous_color = new_color;
        strip.setPixelColor(key_pixels[i].pitch, new_color);
    }
}

#define pitch_to_pixel(X) (((X - 21) * NUM_PIXELS) / 88.0)

void handle_note_on(byte _, byte pitch, byte velocity)
{
    byte pos = pitch_to_pixel(pitch);
    key_pixels[pos].pitch = pitch;
    key_pixels[pos].is_held = true;
    key_pixels[pos].velocity = velocity;
}
void handle_note_off(byte _, byte pitch, byte velocity)
{
    byte pos = pitch_to_pixel(pitch);
    key_pixels[pos].is_held = false;
}
