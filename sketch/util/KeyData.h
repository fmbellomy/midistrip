#ifndef KEYDATA_H
#define KEYDATA_H

struct KeyData
{
    uint32_t previous_color;
    bool is_held;
    byte velocity;
    byte pitch;
};

#endif