#ifndef MODES_H
#define MODES_H

#define NUM_MODES 6

#include "Gradient.h"
#include "HueFade.h"
#include "HueWave.h"
#include "MovingGradient.h"
#include "Random.h"
#include "SolidColor.h"

#ifndef MODE_IDS
#define MODE_IDS
#define SOLID_COLOR_ID 0
#define RANDOM_ID 1
#define HUE_FADE_ID 2
#define HUE_WAVE_ID 3
#define GRADIENT_ID 4
#define MOVING_GRADIENT_ID 5
#endif

#endif