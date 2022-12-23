#ifndef DOT_MATRIX_CONTROLLER_H
#define DOT_MATRIX_CONTROLLER_H
#include <LedControl.h>
#include "../../util/PinDefines.h"
const byte heart[8] = {
    0b01100110,
    0b11111111,
    0b11111011,
    0b11111111,
    0b01111110,
    0b00111100,
    0b00011000,
    0b00000000};
class DotMatrixController
{
public:
    DotMatrixController()
    {
        _lc.shutdown(0, false);
        _lc.setIntensity(0, 15);
        _lc.clearDisplay(0);
    }
    void draw(const byte *img)
    {
        for (int i = 0; i < 8; i++)
        {
            _lc.setRow(0, i, img[i]);
        }
    }

private:
    LedControl _lc = LedControl(DOTMATRIX_DIN, DOTMATRIX_CLK, DOTMATRIX_CS);
};
#endif