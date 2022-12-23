#ifndef RGBWPIXEL_H
#define RGBWPIXEL_H
#define NUM_PIXELS 22
#include "../settings/Input.h"
byte lerp_channel(byte A, byte B, double distance)
{
    return A + distance * (A - B);
}
class RGBWPixel
{
public:
    byte R;
    byte G;
    byte B;
    byte W;
    operator uint32_t() const
    {
        return (this->R << 24) + (this->G << 16) + (this->B << 8) + this->W;
    }
    RGBWPixel(uint32_t color)
    {
        R = (color >> 24) & 0xFF;
        G = (color >> 16) & 0xFF;
        B = (color >> 8) & 0xFF;
        W = color & 0xFF;
    }
    RGBWPixel(byte r, byte g, byte b, byte w)
    {
        R = r;
        G = g;
        B = b;
        W = w;
    }
    RGBWPixel(InputState input_state)
    {
        R = input_state.R;
        G = input_state.G;
        B = input_state.B;
        W = input_state.W;
    }
    RGBWPixel lerp(RGBWPixel &other, double distance)
    {
        return (
            RGBWPixel(
                lerp_channel(R, other.R, distance),
                lerp_channel(G, other.G, distance),
                lerp_channel(B, other.B, distance),
                lerp_channel(W, other.W, distance)));
    }
};
#endif