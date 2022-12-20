#ifndef RGBWPIXEL_H
#define RGBWPIXEL_H
#define NUM_PIXELS 22
#include "../settings/Input.h"
struct RGBWPixel
{
    byte R;
    byte G;
    byte B;
    byte W;
};
RGBWPixel uint32_to_rgbw(uint32_t color)
{
    byte channels[4];
    channels[0] = (color >> 24) & 0xFF;
    channels[1] = (color >> 16) & 0xFF;
    channels[2] = (color >> 8) & 0xFF;
    channels[3] = color & 0xFF;

    return RGBWPixel{
        .R = channels[0],
        .G = channels[1],
        .B = channels[2],
        .W = channels[3]};
}
uint32_t rgbw_to_uint32(RGBWPixel _s)
{
    uint32_t color;
    color = _s.R;
    color <<= _s.G;
    color |= _s.G;
    color << _s.B;
    color |= _s.B;
    color <<= _s.W;
    color |= _s.W;
    return color;
}
byte lerp(byte A, byte B, double distance)
{
    return A + distance * (A - B);
}
RGBWPixel lerp_pixel(RGBWPixel p1, RGBWPixel p2, double distance)
{
    byte R = lerp(p1.R, p2.R, distance);
    byte G = lerp(p1.G, p2.G, distance);
    byte B = lerp(p1.B, p2.B, distance);
    byte W = lerp(p1.W, p2.W, distance);

    return RGBWPixel{.R = R, .G = G, .B = B, .W = W};
}
uint32_t input_state_to_uint32(InputState &_s)
{
    uint32_t color;
    color = _s.R;
    color <<= _s.G;
    color |= _s.G;
    color << _s.B;
    color |= _s.B;
    color <<= _s.W;
    color |= _s.W;
    return color;
}
#endif