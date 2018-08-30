#include QMK_KEYBOARD_H

#include "key_combo_definitions.h"
#include "reregistering.h"
#include "custom_keys.h"
#include "layers.h"


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /****************************************************************************************************
  *
  * Keymap: Base layer
  *
  * ,-------------------------------------------------------------------------------------------------------------------.
  * | Esc    |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F8  |  F9  |  F10 |  F12 | PSCR | SLCK | PAUS |  FN0 |  BOOT  |
  * |--------+------+------+------+------+------+---------------------------+------+------+------+------+------+--------|
  * | =+     |  1!  |  2@  |  3#  |  4$  |  5%  |                           |  6^  |  7&  |  8*  |  9(  |  0)  |   `    |
  * |--------+------+------+------+------+------|                           +------+------+------+------+------+--------|
  * | Tab    |   Q  |   D  |   R  |   W  |   B  |                           |   J  |   F  |   U  |   P  |  ;:  | \|     |
  * |--------+------+------+------+------+------|                           |------+------+------+------+------+--------|
  * |   L2   |   A  |   S  |   H  |   T  |   G  |                           |   Y  |   N  |   E  |   O  |   I  | '"     |
  * |--------+------+------+------+------+------|                           |------+------+------+------+------+--------|
  * |   L1   |ctrl Z|   X  |   M  |   C  |   V  |                           |   K  |   L  |  ,.  |  .>  |ctrl /|   L1   |
  * `--------+------+------+------+------+-------                           `------+------+------+------+------+--------'
  *          | S.All| Undo | Left | Right|                                         | Up   | Down |  [{  |  ]}  |
  *          `---------------------------'                                         `---------------------------'
  *                                        ,-------------.         ,-------------.
  *                                        |  GUI | Alt  |         | Gui  | Alt  |
  *                                 ,------|------|------|         |------+------+------.
  *                                 |      |      | Copy |         |   +  |      |      |
  *                                 | BkSp | Shift|------|         |------|Return| Space|
  *                                 |      |      | Paste|         |ctrl -|      |      |
  *                                 `--------------------'         `--------------------'
  */
  [BASE] = LAYOUT_pretty(
    KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,         KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_PSCR,  KC_SLCK,  KC_PAUS,  KC_FN0,   KC_1,
    KC_ESC,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,                                                                      KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_GRV,
    KC_TAB,   KC_Q,     KC_D,     KC_R,     KC_W,     KC_B,                                                                      KC_J,     KC_F,     KC_U,     KC_P,     KC_SCLN,  KC_BSLS,
    MO(FUNC), KC_A,     KC_S,     KC_H,     KC_T,     KC_G,                                                                      KC_Y,     KC_N,     KC_E,     KC_O,     KC_I,     KC_QUOT,
    MO(SYMB), CTL_Z,    KC_X,     KC_M,     KC_C,     KC_V,                                                                      KC_K,     KC_L,     KC_COMM,  KC_DOT,   CTL_SL,   MO(SYMB),
              CB_ALL,   CB_UNDO,  KC_LEFT,  KC_RGHT,                                                                                       KC_UP,    KC_DOWN,  MB_HOME,  MB_END,
                                                      KC_LGUI,  KC_LALT,                                               KC_RGUI,  KC_RALT,
                                                                CB_COPY,                                               KC_PPLS,
                                            KC_BSPC,  KC_LSFT,  CB_PASTE,                                              CTL_MN,   KC_ENTER, KC_SPC
  ),

  /****************************************************************************************************
  *
  * Keymap: Symbols layer
  *
  * ,-------------------------------------------------------------------------------------------------------------------.
  * | Esc    |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F8  |  F9  |  F10 |  F12 | PSCR | SLCK | PAUS |  FN0 |  BOOT  |
  * |--------+------+------+------+------+------+---------------------------+------+------+------+------+------+--------|
  * | =+     |   !  |   @  |   #  |   $  |   %  |                           |   ^  |   &  |   *  |   (  |   )  |   ~    |
  * |--------+------+------+------+------+------|                           +------+------+------+------+------+--------|
  * | Tab    |      |      |   =  |   _  |      |                           |      |   +  |   -  |      |      |   |    |
  * |--------+------+------+------+------+------|                           |------+------+------+------+------+--------|
  * |   L2   |   [  |   ]  |   {  |   }  |      |                           |      |   (  |   )  |      |      |   "    |
  * |--------+------+------+------+------+------|                           |------+------+------+------+------+--------|
  * |        |      |      |      |      |      |                           |      |      |   <  |  >   |   ?  |        |
  * `--------+------+------+------+------+-------                           `------+------+------+------+------+--------'
  *          | S.All| Undo | Left | Right|                                         |ScrolD|ScrolU|  top |bottom|
  *          `---------------------------'                                         `---------------------------'
  *                                        ,-------------.         ,-------------.
  *                                        |  GUI | Alt  |         | Gui  | Alt  |
  *                                 ,------|------|------|         |------+------+------.
  *                                 |      |      | Copy |         |   +  |      |      |
  *                                 | BkSp | Shift|------|         |------|Return| Space|
  *                                 |      |      | Paste|         |ctrl -|      |      |
  *                                 `--------------------'         `--------------------'
  */
  [SYMB] = LAYOUT_pretty(
    KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,         KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_PSCR,  KC_SLCK,  KC_PAUS,  KC_FN0,   KC_1,
    XXXXXXX,  KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,                                                                   KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,  KC_TILD,
    TO(BASE), XXXXXXX,  XXXXXXX,  KC_EQL,   KC_UNDS,  XXXXXXX,                                                                   XXXXXXX,  KC_PLUS,  KC_MINS,  XXXXXXX,  XXXXXXX,  KC_PIPE,
    TO(FUNC), KC_LBRC,  KC_RBRC,  KC_LCBR,  KC_RCBR,  XXXXXXX,                                                                   XXXXXXX,  KC_LPRN,  KC_RPRN,  XXXXXXX,  XXXXXXX,  KC_DQT,
    _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                                                                   XXXXXXX,  XXXXXXX,  KC_LT,    KC_GT,    KC_QUES,  _______,
              MB_NONE,  MB_REDO,  MB_ALTL,  MB_ALTR,                                                                                       KC_WH_D,  KC_WH_U,  MB_TOP,   MB_BTM,
                                                      XXXXXXX,  XXXXXXX,                                               XXXXXXX,  XXXXXXX,
                                                                MB_CUT,                                                MB_ZMI,
                                            KC_BSPC,  XXXXXXX,  MB_MATCH,                                              MB_ZMO,   KC_ESC,   KC_BSPC
  )

};


const uint16_t PROGMEM fn_actions[] = {

};

void matrix_init_user(void) {

layer_dependant_rgblight = false;
}

void matrix_scan_user(void) {

}

void led_set_user(uint8_t usb_led) {

}
