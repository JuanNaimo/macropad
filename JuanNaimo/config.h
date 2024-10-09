#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */

#define manufacturer    Gambito
#define keyboard_name         GambbitKeyboard

/* key matrix size */
#define MATRIX_ROWS 2
#define MATRIX_COLS 5

/* key matrix pins */
#define MATRIX_ROW_PINS { D4, C6 }
#define MATRIX_COL_PINS { D7, E6, B4, B5, B6 }


/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* Encoder support */
#define ENCODERS_PAD_A { B2, B3 }
#define ENCODERS_PAD_B { B1, B0 }

#define ENCODER_BUTTON_PIN_A D3
/* OLED Driver */
#define OLED_DISPLAY_128X64

/* Feature disable options */
/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT

