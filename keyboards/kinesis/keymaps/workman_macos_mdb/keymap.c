#include QMK_KEYBOARD_H

#include "key_combo_definitions.h"
#include "reregistering.h"
#include "custom_keys.h"
#include "layers.h"

// extern bool music_activated;

void kinesis_led_1_on(void) { DDRF|= (1<<3); }
void kinesis_led_1_off(void) { DDRF &= ~(1<<3); }
void kinesis_led_2_on(void) { DDRF|= (1<<2); }
void kinesis_led_2_off(void) { DDRF &= ~(1<<2); }
void kinesis_led_3_on(void) { DDRF|= (1<<1); }
void kinesis_led_3_off(void) { DDRF &= ~(1<<1); }
void kinesis_led_4_on(void) { DDRF|= (1<<0); }
void kinesis_led_4_off(void) { DDRF &= ~(1<<0); }

void all_leds_off(void) {
  kinesis_led_1_off();
  kinesis_led_2_off();
  kinesis_led_3_off();
  kinesis_led_4_off();
}

void all_leds_on(void) {
  kinesis_led_1_on();
  kinesis_led_2_on();
  kinesis_led_3_on();
  kinesis_led_4_on();
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /****************************************************************************************************
  *
  * Keymap: Base layer
  *
  * ,--------------------------------------------+                         +--------------------------------------------.
  * | Esc| F1 | F2 | F3 | F4 | F5 | F6 | F7 | F8 |                         | F9 | F10| F11| F12|MUTE|VOL-|VOL+|KYPD|CNFG|
  * `----+----+----+----+----+----+----+----+----'                         `----+----+----+----+----+----+----+----+----'
  * ,--------+------+------+------+------+------+                           +------+------+------+------+------+--------.
  * | =+     |  1!  |  2@  |  3#  |  4$  |  5%  |                           |  6^  |  7&  |  8*  |  9(  |  0)  |   `    |
  * |--------+------+------+------+------+------|                           +------+------+------+------+------+--------|
  * | Tab    |   Q  |   D  |   R  |   W  |   B  |                           |   J  |   F  |   U  |   P  |  ;:  | \|     |
  * |--------+------+------+------+------+------|                           |------+------+------+------+------+--------|
  * |   L2   |   A  |   S  |   H  |   T  |   G  |                           |   Y  |   N  |   E  |   O  |   I  | '"     |
  * |--------+------+------+------+------+------|                           |------+------+------+------+------+--------|
  * |   L1   |ctrl Z|   X  |   M  |   C  |   V  |                           |   K  |   L  |  ,.  |  .>  |ctrl /|   L1   |
  * `--------+------+------+------+------+------'                          `------+------+------+------+------+--------'
  *          | S.All| Undo | Left | Right|                                         | Up   | Down | Home | End  |
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
    KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,         KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_MUTE,  KC_VOLD,  KC_VOLU,  TO(KPAD), TO(CNFG),
    KC_ESC,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,                                                                      KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_GRV,
    KC_TAB,   KC_Q,     KC_D,     KC_R,     KC_W,     KC_B,                                                                      KC_J,     KC_F,     KC_U,     KC_P,     KC_SCLN,  KC_BSLS,
    TT(FUNC), KC_A,     KC_S,     KC_H,     KC_T,     KC_G,                                                                      KC_Y,     KC_N,     KC_E,     KC_O,     KC_I,     KC_QUOT,
    MO(SYMBL),CTL_Z,    KC_X,     KC_M,     KC_C,     KC_V,                                                                      KC_K,     KC_L,     KC_COMM,  KC_DOT,   CTL_SL,   MO(SYMBR),
              CB_ALL,   CB_UNDO,  KC_LEFT,  KC_RGHT,                                                                                       KC_UP,    KC_DOWN,  MB_HOME,  MB_END,
                                                      KC_LGUI,  KC_LALT,                                               KC_RALT,  KC_RGUI,
                                                                CB_COPY,                                               KC_PPLS,
                                            KC_BSPC,  KC_LSFT,  CB_PASTE,                                              CTL_MN,   KC_ENTER, KC_SPC
  ),

  /****************************************************************************************************
  *
  * Keymap: Symbols layer
  *
  * ,--------------------------------------------+                         +--------------------------------------------.
  * |Lock|Bri-|Bri+|    |    |    |    |    |    |                         |    |    |    |MACR|MUTE|VOL-|VOL+|KYPD|CNFG|
  * `----+----+----+----+----+----+----+----+----'                         `----+----+----+----+----+----+----+----+----'
  * ,--------+------+------+------+------+------+                           +------+------+------+------+------+--------.
  * | =+     |   !  |   @  |   #  |   $  |   %  |                           |   ^  |   &  |   *  |   (  |   )  |   ~    |
  * |--------+------+------+------+------+------|                           +------+------+------+------+------+--------|
  * | Tab    |      |      |   =  |   _  |      |                           |      |   +  |   -  |      |   :  |   |    |
  * |--------+------+------+------+------+------|                           |------+------+------+------+------+--------|
  * |   L2   |   [  |   ]  |   {  |   }  |      |                           |      |   (  |   )  |      |      |   "    |
  * |--------+------+------+------+------+------|                           |------+------+------+------+------+--------|
  * |        |      |      |      |      |      |                           |      |      |   <  |  >   |   ?  |        |
  * `--------+------+------+------+------+-------                           `------+------+------+------+------+--------'
  *          | S.All| Undo | Left | Right|                                         |ScrolD|ScrolU|  top |bottom|
  *          `---------------------------'                                         `---------------------------'
  *                                        ,-------------.         ,-------------.
  *                                        |      |      |         |      |      |
  *                                 ,------|------|------|         |------+------+------.
  *                                 |      |      | Cut  |         | cmd+ |      |      |
  *                                 |Delete| Shift|------|         |------| Esc  |Space |
  *                                 |      |      | Match|         | cmd- |      |      |
  *                                 `--------------------'         `--------------------'
  */
  [SYMBL] = LAYOUT_pretty(
    MB_SLEEP,  KC_F14,   KC_F15,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,      MB_FQUIT, XXXXXXX, OSL(MACR), XXXXXXX,  _______,  _______,  _______,  XXXXXXX,  XXXXXXX,
    XXXXXXX,  KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,                                                                   KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,  KC_TILD,
    XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_EQL,   KC_UNDS,  XXXXXXX,                                                                   XXXXXXX,  KC_PLUS,  KC_MINS,  XXXXXXX,  KC_COLN,  KC_PIPE,
    TO(MACR), KC_LBRC,  KC_RBRC,  KC_LCBR,  KC_RCBR,  XXXXXXX,                                                                   XXXXXXX,  KC_LPRN,  KC_RPRN,  XXXXXXX,  XXXXXXX,  KC_DQT,
    _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                                                                   XXXXXXX,  XXXXXXX,  KC_LT,    KC_GT,    KC_QUES,  _______,
              MB_NONE,  MB_REDO,  MB_ALTL,  MB_ALTR,                                                                                       KC_WH_D,  KC_WH_U,  MB_TOP,   MB_BTM,
                                                      _______,  _______,                                               _______,  _______,
                                                                MB_CUT,                                                MB_ZMI,
                                            KC_DEL,   XXXXXXX,  MB_MATCH,                                              MB_ZMO,   KC_ESC,   _______
  ),

  [SYMBR] = LAYOUT_pretty(
    MB_LOCK,  KC_F14,   KC_F15,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,      MB_FQUIT, XXXXXXX, OSL(MACR), XXXXXXX,  _______,  _______,  _______,  XXXXXXX,  XXXXXXX,
    XXXXXXX,  KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,                                                                   KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,  KC_TILD,
    XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_EQL,   KC_UNDS,  XXXXXXX,                                                                   XXXXXXX,  KC_PLUS,  KC_MINS,  XXXXXXX,  KC_COLN,  KC_PIPE,
    TO(MACR), KC_LBRC,  KC_RBRC,  KC_LCBR,  KC_RCBR,  XXXXXXX,                                                                   XXXXXXX,  KC_LPRN,  KC_RPRN,  XXXXXXX,  XXXXXXX,  TO(MACR), //<----- this one is different
    _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                                                                   XXXXXXX,  XXXXXXX,  KC_LT,    KC_GT,    KC_QUES,  _______,
              MB_NONE,  MB_REDO,  MB_ALTL,  MB_ALTR,                                                                                       KC_WH_D,  KC_WH_U,  MB_TOP,   MB_BTM,
                                                      _______,  _______,                                               _______,  _______,
                                                                MB_CUT,                                                MB_ZMI,
                                            KC_DEL,   XXXXXXX,  MB_MATCH,                                              MB_ZMO,   KC_ESC,   _______
  ),

  /****************************************************************************************************
  *
  * Keymap: Function layer
  *
  * ,--------------------------------------------+                         +--------------------------------------------.
  * |Powr|Bri-|Bri+|    |    |    |    |    |    |                         |    |    |    |MACR|MUTE|VOL-|VOL+|KYPD|CNFG|
  * `----+----+----+----+----+----+----+----+----'                         `----+----+----+----+----+----+----+----+----'
  * ,--------+------+------+------+------+------+---------------------------+------+------+------+------+------+--------.
  * |        |   !  |   @  |   #  |   $  |   %  |                           |   ^  |   &  |   *  |   (  |   )  |   ~    |
  * |--------+------+------+------+------+------|                           +------+------+------+------+------+--------|
  * |        |      |      |   =  |   _  |      |                           |      |   +  |   -  |      |      |   |    |
  * |--------+------+------+------+------+------|                           |------+------+------+------+------+--------|
  * |        |   [  |   ]  |   {  |   }  |      |                           |      |   (  |   )  |      |      |   "    |
  * |--------+------+------+------+------+------|                           |------+------+------+------+------+--------|
  * |        |      |      |      |      |      |                           |      |      |   <  |  >   |   ?  |        |
  * `--------+------+------+------+------+-------                           `------+------+------+------+------+--------'
  *          | S.All| Undo | ^left|^right|                                         |ScrolD|ScrolU|  top |bottom|
  *          `---------------------------'                                         `---------------------------'
  *                                        ,-------------.         ,-------------.
  *                                        |      | Alt  |         | Alt  |      |
  *                                 ,------|------|------|         |------+------+------.
  *                                 |      |      |Snippt|         |      |      |      |
  *                                 | BkSp | Shift|------|         |------|      |      |
  *                                 |      |      |MPaste|         | ctrl |      |      |
  *                                 `--------------------'         `--------------------'
  */
  [FUNC] = LAYOUT_pretty(
    KC_POWER, KC_F14,   KC_F15,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,       XXXXXXX,  XXXXXXX, OSL(MACR), XXXXXXX,  _______,  _______,  _______,  XXXXXXX,  XXXXXXX,
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                                                                   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                                                                   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                                                                   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    TO(BASE), XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                                                                   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  TO(BASE),
              XXXXXXX,  XXXXXXX,  MB_CTLT,  MB_CTRT,                                                                                       KC_PGUP,  KC_PGDN,  XXXXXXX,  XXXXXXX,
                                                      _______,  _______,                                               _______,  _______,
                                                                MB_SNIP,                                               XXXXXXX,
                                            KC_SPC,   KC_LSFT,  MB_PASTE,                                              KC_RCTRL, XXXXXXX,  XXXXXXX
  ),

  /****************************************************************************************************
  *
  * Keymap: Macro layer
  *
  * ,--------------------------------------------+                         +--------------------------------------------.
  * |    |   |     |    |    |    |    |    |    |                         |    |    |    |MACR|    |    |    |    |    |
  * `----+----+----+----+----+----+----+----+----'                         `----+----+----+----+----+----+----+----+----'
  * ,--------+------+------+------+------+------+---------------------------+------+------+------+------+------+--------.
  * |        |      |      |      |      |      |      |      |      |      |      |      |      |      |      |        |
  * |--------+------+------+------+------+------+---------------------------+------+------+------+------+------+--------|
  * |        |      |      |      |      |      |                           |      |      |      |      |      |        |
  * |--------+------+------+------+------+------|                           +------+------+------+------+------+--------|
  * |        |      |      |      |      |      |                           |      |      |      |      |      |        |
  * |--------+------+------+------+------+------|                           |------+------+------+------+------+--------|
  * |        |      |      |      |      |      |                           |      |      |      |      |      |        |
  * |--------+------+------+------+------+------|                           |------+------+------+------+------+--------|
  * |        |      |      |      |      |      |                           |      |      |      |      |      |        |
  * `--------+------+------+------+------+-------                           `------+------+------+------+------+--------'
  *          |      |      |      |      |                                         |      |      |      |      |
  *          `---------------------------'                                         `---------------------------'
  *                                        ,-------------.         ,-------------.
  *                                        |      |      |         |      |      |
  *                                 ,------|------|------|         |------+------+------.
  *                                 |      |      |      |         |      |      |      |
  *                                 |      |      |------|         |------|      |      |
  *                                 |      |      |      |         |      |      |      |
  *                                 `--------------------'         `--------------------'
  */
  [MACR] = LAYOUT_pretty(
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,     XXXXXXX,  XXXXXXX,  TO(BASE), XXXXXXX,  _______,  _______,  _______,  XXXXXXX,  XXXXXXX,
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                                                                 XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    XXXXXXX,  XXXXXXX,  XXXXXXX,  MAIL2,    MAIL1,    XXXXXXX,                                                                 XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    TO(FUNC), NAME1,    NAME2,    PWD1,     PWD2,     PWD3,                                                                    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  TO(BASE),
    TO(BASE), XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                                                                 XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  TO(BASE),
              XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                                                                                     XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
                                                      XXXXXXX,  XXXXXXX,                                             XXXXXXX,  XXXXXXX,
                                                                XXXXXXX,                                             XXXXXXX,
                                            XXXXXXX,  XXXXXXX,  XXXXXXX,                                             XXXXXXX,  XXXXXXX,  XXXXXXX
  ),

  /****************************************************************************************************
  *
  * Keymap: Media layer
  *
  * ,-------------------------------------------------------------------------------------------------------------------.
  * |        |     -|      |      |      |      |      |      |      |      |      |      |      |      |      |        |
  * |--------+------+------+------+------+------+---------------------------+------+------+------+------+------+--------|
  * |        |     -|     +|      |      |      |                           |      |      |      |      |      |        |
  * |--------+------+------+------+------+------|                           +------+------+------+------+------+--------|
  * |        |      |      | MsUp |      |      |                           |      |      | MsUp |      |      |        |
  * |--------+------+------+------+------+------|                           |------+------+------+------+------+--------|
  * |        |      |MsLeft|MsDown|MsRght|      |                           |      |MsLeft|MsDown|MsRght|      |        |
  * |--------+------+------+------+------+------|                           |------+------+------+------+------+--------|
  * |        |      |      |      |      |      |                           |      |      |      |      |      |        |
  * `--------+------+------+------+------+-------                           `------+------+------+------+------+--------'
  *          |      |      |      |      |                                         |      |      |      |      |
  *          `---------------------------'                                         `---------------------------'
  *                                        ,-------------.         ,-------------.
  *                                        |      |      |         |      |      |
  *                                 ,------|------|------|         |------+------+------.
  *                                 |      |      |      |         |      |      |      |
  *                                 |      |      |------|         |------|      |      |
  *                                 |      |      |      |         |      |      |      |
  *                                 `--------------------'         `--------------------'
  */
  [KPAD] = LAYOUT_pretty(
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,     XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  _______,  _______,  _______,     TO(BASE), TO(CNFG),
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                                                                 XXXXXXX,  KC_KP_EQUAL,  KC_KP_SLASH,  KC_KP_ASTERISK,     XXXXXXX,  XXXXXXX,
    XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_MS_U,  XXXXXXX,  XXXXXXX,                                                                 XXXXXXX,  KC_KP_7,  KC_KP_8,  KC_KP_9,     KC_KP_MINUS,  XXXXXXX,
    TO(FUNC), XXXXXXX,  KC_MS_L,  KC_MS_D,  KC_MS_R,  XXXXXXX,                                                                 XXXXXXX,  KC_KP_4,  KC_KP_5,  KC_KP_6,     KC_KP_PLUS,  TO(BASE),
    TO(BASE), XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                                                                 XXXXXXX,  KC_KP_1,  KC_KP_2,  KC_KP_3,     KC_KP_ENTER,  TO(BASE),
              XXXXXXX,  XXXXXXX,  KC_BTN1,  KC_BTN2,                                                                                     XXXXXXX,  XXXXXXX,  KC_KP_DOT,   KC_KP_ENTER,
                                                      XXXXXXX,  XXXXXXX,                                             XXXXXXX,  XXXXXXX,
                                                                XXXXXXX,                                             XXXXXXX,
                                            XXXXXXX,  XXXXXXX,  XXXXXXX,                                             XXXXXXX,  KC_KP_ENTER,  KC_KP_0
  )
  ,

  /****************************************************************************************************
  *
  * Keymap: Config layer
  *
  * ,-------------------------------------------------------------------------------------------------------------------.
  * |  Vrsion|      |      |      |      |      |      |      | Click|BTooth|      |      |      |      |      |        |
  * |--------+------+------+------+------+------+---------------------------+------+------+------+------+------+--------|
  * |        |      |      |      |      |      |                           |      |      |      |      |      |        |
  * |--------+------+------+------+------+------|                           +------+------+------+------+------+--------|
  * |        |      |      |      |      |      |                           |      |      |      |      |      |        |
  * |--------+------+------+------+------+------|                           |------+------+------+------+------+--------|
  * |        |      |      |      |      |      |                           |      |      |      |      |      |        |
  * |--------+------+------+------+------+------|                           |------+------+------+------+------+--------|
  * |        |      |      |      |      |      |                           |      |      |      |      |      |        |
  * `--------+------+------+------+------+-------                           `------+------+------+------+------+--------'
  *          |      |      |      |      |                                         |      |      |      |      |
  *          `---------------------------'                                         `---------------------------'
  *                                        ,-------------.         ,-------------.
  *                                        |      |      |         |      |      |
  *                                 ,------|------|------|         |------+------+------.
  *                                 |      |      |      |         |      |      |      |
  *                                 |      |      |------|         |------|      |      |
  *                                 |      |      |      |         |      |      |      |
  *                                 `--------------------'         `--------------------'
  */
  [CNFG] = LAYOUT_pretty(
    VRSN,     XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  CK_TOGG,    MB_BTCMD, XXXXXXX,    XXXXXXX,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  TO(KPAD), TO(BASE),
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                                                                   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                                                                   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    TO(FUNC), XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                                                                   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  TO(BASE),
    TO(BASE), XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                                                                   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  TO(BASE),
              XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                                                                                       XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
                                                      XXXXXXX,  XXXXXXX,                                               XXXXXXX,  XXXXXXX,
                                                                XXXXXXX,                                               XXXXXXX,
                                            XXXXXXX,  XXXXXXX,  XXXXXXX,                                               XXXXXXX,  XXXXXXX,  XXXXXXX
  )

};


const uint16_t PROGMEM fn_actions[] = {

};

void waitSome(int times) {
  for(int i=0; i<times; i++) {
    _delay_ms(25);
  }
}

void matrix_init_user(void) {
  layer_dependant_rgblight = false;
  all_leds_off();

  int cycles = 4;
  for (int i=1; i<=cycles; i++) {
      kinesis_led_1_on();
      waitSome(i);
      all_leds_off();
      kinesis_led_2_on();
      waitSome(i);
      all_leds_off();
      kinesis_led_3_on();
      waitSome(i);
      all_leds_off();
      kinesis_led_4_on();
      waitSome(i);
      all_leds_off();
      kinesis_led_3_on();
      waitSome(i);
      all_leds_off();
      kinesis_led_2_on();
      waitSome(i);
      all_leds_off();
    }

  kinesis_led_1_on();
  waitSome(cycles);
  all_leds_off();
}

void matrix_scan_user(void) {

}

uint32_t layer_state_set_user(uint32_t state) {

  // float layer_on_sound[][2] = SONG(E__NOTE(_E3));
  // float layer_off_sound[][2] = SONG(E__NOTE(_A2));

  all_leds_off();

  uint8_t layer = biton32(state);
  // static uint8_t last_layer;
  switch (layer) {
      case BASE:
        // if (last_layer >= MACR) {
        //   // PLAY_SONG(layer_off_sound);
        // }
        all_leds_off();
        break;
      case SYMBL:
        kinesis_led_1_on();
        break;
      case SYMBR:
        kinesis_led_1_on();
        break;
      case FUNC:
        kinesis_led_2_on();
        break;
      case MACR:
        // PLAY_SONG(layer_on_sound);
        kinesis_led_3_on();
        break;
      case KPAD:
        // PLAY_SONG(layer_on_sound);
      kinesis_led_4_on();
        break;
      case CNFG:
  //       music_activated = true;
  //       PLAY_SONG(layer_on_sound);
  // music_activated = false;
        // kinesis_led_1_on();
        // kinesis_led_4_on();
        all_leds_on(); // config layer
        break;
      case 7:
        kinesis_led_2_on();
        kinesis_led_4_on();
        break;
      case 8:
        kinesis_led_3_on();
        kinesis_led_4_on();
        break;
      default:
        break;
    }

  // last_layer = layer;
  return state;
};
