#ifndef CONFIG_WORKMANMACOSMDB_H
#define CONFIG_WORKMANMACOSMDB_H

#include "../../config.h"

#undef TAPPING_TOGGLE
#define TAPPING_TOGGLE 2 // Nr of taps before toggling to layer -- TT()

#define MOUSEKEY_INTERVAL       20
#define MOUSEKEY_DELAY          0
#undef MOUSEKEY_TIME_TO_MAX
#define MOUSEKEY_TIME_TO_MAX    15
#define MOUSEKEY_MAX_SPEED      7
#define MOUSEKEY_WHEEL_DELAY 0


/* Board led color */
#define RGBLIGHT_COLOR_LAYER_0 0xFF, 0xFF, 0xFF
#define RGBLIGHT_COLOR_LAYER_1 0xFF, 0x00, 0x00
#define RGBLIGHT_COLOR_LAYER_2 0x00, 0xFF, 0x00
#define RGBLIGHT_COLOR_LAYER_3 0x00, 0x00, 0xFF
#define RGBLIGHT_COLOR_LAYER_4 0xFF, 0xFF, 0x00
#define RGBLIGHT_COLOR_LAYER_5 0xFF, 0x00, 0xFF
#define RGBLIGHT_COLOR_LAYER_6 0xFF, 0x00, 0xFF
#define RGBLIGHT_COLOR_LAYER_7 0xFF, 0xFF, 0xFF

#endif
