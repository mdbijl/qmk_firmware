// Netable differences vs. the default firmware for the ErgoDox EZ:
// 1. The Cmd key is now on the right side, making Cmd+Space easier.
// 2. The media keys work on OSX (But not on Windows).
#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"

#define _______ KC_TRNS
#define LT1_K LT(SYMB,KC_K)
#define LT1_V LT(SYMB,KC_V)

#define SH_ESC LSFT(KC_ESCAPE)
#define SH_ENT RSFT(KC_ENTER)

#define CTL_Z  LCTL(KC_Z)
#define CTL_SL RCTL(KC_SLASH)

#define MB_COPY   LGUI(KC_C)
#define MB_CUT    LGUI(KC_X)
#define MB_PASTE  LGUI(KC_V)
#define MB_MATCH  LSFT(LGUI(KC_V))

#define MB_UNDO   LGUI(KC_Z)
#define MB_REDO   LSFT(LGUI(KC_Z))
#define MB_ALL    LGUI(KC_A)
#define MB_NONE   LSFT(LGUI(KC_A))

#define MB_SNIP   HYPR(KC_C)
#define MB_MPAST  LCTL(LSFT(LGUI(KC_C)))

enum layers {
  BASE = 1,
  SYMB,
  FUNC,
  MDIA
};

enum macros {
  JJ_MACRO = SAFE_RANGE,
  JJ_OTHER
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   Esc  |   1  |   2  |   3  |   4  |   5  |      |           |      |   6  |   7  |   8  |   9  |   0  |    `   |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |   Tab  |   Q  |   D  |   R  |   W  |   B  |      |           |      |   J  |   F  |   U  |   P  |      |    \   |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |   L2   |   A  |   S  |   H  |   T  |   G  |------|           |------|   Y  |   N  |   E  |   O  |   I  |    '   |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |   L1   |   Z  |   X  |   M  |   C  |   V  |      |           |      |   N  |   M  |   ,  |   .  |   /  |   L1   |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      | Copy | Paste| Left | Right|                                       |  Up  | Down | Home |  End |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | LGui | LAlt |       | RAlt | RGui |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |Backsp|LShift|------|       |------|RShift|Space |
 *                                 |   ace| /ESC | LCtl |       | RCtl |/Enter|      |
 *                                 `--------------------'       `--------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        KC_ESC,         KC_1,         KC_2,    KC_3,   KC_4,   KC_5,   _______,
        KC_TAB,         KC_Q,         KC_D,    KC_R,   KC_W,   KC_B,   _______,
        MO(FUNC),       KC_A,         KC_S,    KC_H,   KC_T,   KC_G,
        MO(SYMB),       CTL_Z,        KC_X,    KC_M,   KC_C,   LT1_V,  _______,
        _______,        MB_COPY,      MB_PASTE,KC_LEFT,KC_RGHT,
                                               KC_LGUI,        KC_LALT,
                                                               _______,
                                               KC_BSPC,SH_ESC, KC_LCTL,
        // right hand
             _______,     KC_6,   KC_7,   KC_8,   KC_9,   KC_0,             KC_GRV,
             _______,     KC_J,   KC_F,   KC_U,   KC_P,   KC_P,             KC_BSLS,
                          KC_Y,   KC_N,   KC_O,   KC_I,   KC_U,             KC_QUOT,
             _______,     LT1_K,  KC_L,   KC_COMM,KC_DOT, CTL_SL,           MO(SYMB),
                                  KC_UP,  KC_DOWN,KC_HOME,KC_END,           _______,
             KC_RALT,         KC_RGUI,
             _______,
             KC_RCTL,SH_ENT, KC_SPC
    ),
    /* Keymap 1: Symbol Layer
     *
     * ,--------------------------------------------------.           ,--------------------------------------------------.
     * |        |   !  |   @  |   #  |   $  |   %  |      |           |      |   ^  |   &  |   *  |   (  |   )  |    ~   |
     * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
     * |        |      |      |      |      |      |      |           |      |   +  |   -  |      |      |   :  |    |   |
     * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
     * |        |   [  |   ]  |   {  |   }  |      |------|           |------|   (  |   )  |      |      |      |    "   |
     * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
     * |        | Undo | s-All|      |      |      |      |           |      |      |      |   <  |  >   |   ?  |        |
     * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
     *   |      | Cut  | Match|      |      |                                       |      |      |      |      |      |
     *   `----------------------------------'                                       `----------------------------------'
     *                                        ,-------------.       ,-------------.
     *                                        |      |      |       |      |      |
     *                                 ,------|------|------|       |------+------+------.
     *                                 |      |      |      |       |      |      |      |
     *                                 |      |      |------|       |------|      |      |
     *                                 |      |      |      |       |      |      |      |
     *                                 `--------------------'       `--------------------'
     */
    // SYMBOLS
[SYMB] = LAYOUT_ergodox(
       // left hand
       _______, KC_EXLM, KC_AT,    KC_HASH, KC_DLR,  KC_PERC, _______,
       _______, _______, _______,  KC_EQL,  KC_UNDS, _______, _______,
       _______, KC_LBRC, KC_RBRC,  KC_LCBR, KC_RCBR, _______,
       _______, MB_UNDO, MB_ALL,   KC_LT,   KC_GT,   KC_QUES, _______,
       _______, MB_CUT,  MB_MATCH, _______, _______,
                                            _______, _______,
                                                     _______,
                                   _______, _______, _______,
       // right hand
       _______, KC_CIRC, KC_AMPR,KC_ASTR, KC_LPRN,  KC_RPRN, KC_TILD,
       _______, _______, KC_PLUS, KC_MINS, _______, KC_COLN, KC_PIPE,
                _______, KC_LPRN, KC_RPRN, _______, _______, KC_DQT,
       _______, _______, _______, _______, _______, _______, _______,
                         _______, _______, _______, _______, _______,
       _______, _______,
       _______,
       _______, _______, _______
),
/* Keymap 2: Function Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |   F12  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------|      |      |      |      |      |   F13  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        | Redo | None |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |Snipts|Mpaste|      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// FUNCTION
[FUNC] = LAYOUT_ergodox(
   // left hand
   _______, KC_F1,   KC_F2,    KC_F3,   KC_F4,   KC_F5,   _______,
   _______, _______, _______,  _______, _______, _______, _______,
   _______, _______, _______,  _______, _______, _______,
   _______, MB_NONE, MB_NONE,  _______, _______, _______, _______,
   _______, MB_SNIP, MB_MPAST, _______, _______,
                                       _______, _______,
                                                _______,
                              _______, _______, _______,
   // right hand
   _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
   _______, _______, _______, _______, _______, _______, KC_F12,
            _______, _______, _______, _______, _______, KC_F13,
   _______, _______, _______, _______, _______, _______, _______,
                     _______, _______, _______, _______, _______,
   _______, _______,
   _______,
   _______, _______, _______
),
/* Keymap 3: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      | MsUp |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |MsLeft|MsDown|MsRght|      |------|           |------|      |      |      |      |      |  Play  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      | Prev | Next |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      | Lclk | Rclk |                                       |VolUp |VolDn | Mute |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |Brwser|
 *                                 |      |      |------|       |------|      |Back  |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// MEDIA AND MOUSE
[MDIA] = LAYOUT_ergodox(
       _______, _______, _______, _______, _______, _______, _______,
       _______, _______, _______, KC_MS_U, _______, _______, _______,
       _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, _______,
       _______, _______, _______, _______, _______, _______, _______,
       _______, _______, _______, KC_BTN1, KC_BTN2,
                                           _______, _______,
                                                    _______,
                                  _______, _______, _______,
    // right hand
       _______,  _______, _______, _______, _______, _______, _______,
       _______,  _______, _______, _______, _______, _______, _______,
                 _______, _______, _______, _______, _______, KC_MPLY,
       _______,  _______, _______, KC_MPRV, KC_MNXT, _______, _______,
                          KC_VOLU, KC_VOLD, KC_MUTE, _______, _______,
       _______, _______,
       _______,
       _______, _______, KC_WBAK
),
};

// Defines actions for my custom macros
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case JJ_MACRO:
      if (!record->event.pressed) {
        SEND_STRING(SS_LGUI("c"));
      }
      return false;
      break;
  }
  return true;
}


const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(SYMB)                // FN1 - Momentary Layer 1 (Symbols)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
  switch(id) {
    case 0:
      if (record->event.pressed) {
        register_code(KC_RSFT);
      } else {
        unregister_code(KC_RSFT);
      }
      break;
  }
  return MACRO_NONE;
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

  uint8_t layer = biton32(layer_state);

  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();
  switch (layer) {
    // TODO: Make this relevant to the ErgoDox EZ.
    case SYMB:
      ergodox_right_led_1_on();
      break;
    case MDIA:
      ergodox_right_led_2_on();
      break;
    default:
      // none
      break;
  }

};
