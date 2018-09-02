#include QMK_KEYBOARD_H

#include "key_combo_definitions.h"
#include "reregistering.h"
#include "custom_keys.h"
#include "layers.h"

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
  * ,-------------------------------------------------------------------------------------------------------------------.
  * | Esc    |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F8  |  F9  |  F10 |  F12 | PSCR | SLCK | PAUS |      |        |
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
    KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,         KC_F9,    KC_F10,   KC_F11,   KC_F12,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    KC_ESC,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,                                                                      KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_GRV,
    KC_TAB,   KC_Q,     KC_D,     KC_R,     KC_W,     KC_B,                                                                      KC_J,     KC_F,     KC_U,     KC_P,     KC_SCLN,  KC_BSLS,
    TT(FUNC), KC_A,     KC_S,     KC_H,     KC_T,     KC_G,                                                                      KC_Y,     KC_N,     KC_E,     KC_O,     KC_I,     KC_QUOT,
    MO(SYMB), CTL_Z,    KC_X,     KC_M,     KC_C,     KC_V,                                                                      KC_K,     KC_L,     KC_COMM,  KC_DOT,   CTL_SL,   MO(SYMB),
              CB_ALL,   CB_UNDO,  KC_LEFT,  KC_RGHT,                                                                                       KC_UP,    KC_DOWN,  MB_HOME,  MB_END,
                                                      KC_LGUI,  KC_LALT,                                               KC_RALT,  KC_RGUI,
                                                                CB_COPY,                                               KC_PPLS,
                                            KC_BSPC,  KC_LSFT,  CB_PASTE,                                              CTL_MN,   KC_ENTER, KC_SPC
  ),

  /****************************************************************************************************
  *
  * Keymap: Symbols layer
  *
  * ,-------------------------------------------------------------------------------------------------------------------.
  * | Esc    | Brig-| Brig+|      |      |      |      |      |      |      |     |       |      |      |      |        |
  * |--------+------+------+------+------+------+---------------------------+------+------+------+------+------+--------|
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
  *                                 |Delete| Shift|------|         |------| Esc  |BSpace|
  *                                 |      |      | Match|         | cmd- |      |      |
  *                                 `--------------------'         `--------------------'
  */
  [SYMB] = LAYOUT_pretty(
    XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,      XXXXXXX,  XXXXXXX, OSL(MACR), XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  TO(MDIA), TO(CNFG),
    XXXXXXX,  KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,                                                                   KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,  KC_TILD,
    _______,  XXXXXXX,  XXXXXXX,  KC_EQL,   KC_UNDS,  XXXXXXX,                                                                   XXXXXXX,  KC_PLUS,  KC_MINS,  XXXXXXX,  KC_COLN,  KC_PIPE,
    _______,  KC_LBRC,  KC_RBRC,  KC_LCBR,  KC_RCBR,  XXXXXXX,                                                                   XXXXXXX,  KC_LPRN,  KC_RPRN,  XXXXXXX,  XXXXXXX,  KC_DQT,
    _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                                                                   XXXXXXX,  XXXXXXX,  KC_LT,    KC_GT,    KC_QUES,  _______,
              MB_NONE,  MB_REDO,  MB_ALTL,  MB_ALTR,                                                                                       KC_WH_D,  KC_WH_U,  MB_TOP,   MB_BTM,
                                                      XXXXXXX,  XXXXXXX,                                               XXXXXXX,  XXXXXXX,
                                                                MB_CUT,                                                MB_ZMI,
                                            KC_DEL,   XXXXXXX,  MB_MATCH,                                              MB_ZMO,   KC_ESC,   KC_BSPC
  ),

  /****************************************************************************************************
  *
  * Keymap: Function layer
  *
  * ,-------------------------------------------------------------------------------------------------------------------.
  * | Esc    |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F8  |  F9  |  F10 |  F12 |      |      |      |      |        |
  * |--------+------+------+------+------+------+---------------------------+------+------+------+------+------+--------|
  * | =+     |   !  |   @  |   #  |   $  |   %  |                           |   ^  |   &  |   *  |   (  |   )  |   ~    |
  * |--------+------+------+------+------+------|                           +------+------+------+------+------+--------|
  * | Tab    |      |      |   =  |   _  |      |                           |      |   +  |   -  |      |      |   |    |
  * |--------+------+------+------+------+------|                           |------+------+------+------+------+--------|
  * |   L2   |   [  |   ]  |   {  |   }  |      |                           |      |   (  |   )  |      |      |   "    |
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
    XXXXXXX,  KC_F14,   KC_F15,  XXXXXXX,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,       XXXXXXX,  KC_MUTE,  KC_VOLD,  KC_VOLU,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    XXXXXXX,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,                                                                     KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,
    _______,  MB_CMDQ,  MB_CMDD,  MB_CMDR,  MB_CMDW,  MB_CMDB,                                                                   MB_CMDJ,  MB_CMDF,  MB_CMDU,  MB_CMDP,  XXXXXXX,  KC_F12,
    _______,  MB_CMDA,  MB_CMDS,  MB_CMDH,  MB_CMDT,  MB_CMDG,                                                                   MB_CMDY,  MB_CMDN,  MB_CMDE,  MB_CMDO,  MB_CMDI,  KC_F13,
    TO(BASE), MB_CMDZ,  MB_CMDX,  MB_CMDM,  MB_CMDC,  MB_CMDV,                                                                   MB_CMDK,  MB_CMDL,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
              XXXXXXX,  XXXXXXX,  MB_CTLT,  MB_CTRT,                                                                                       KC_PGUP,  KC_PGDN,  XXXXXXX,  XXXXXXX,
                                                      KC_LGUI,  XXXXXXX,                                               KC_RALT,  XXXXXXX,
                                                                MB_SNIP,                                               XXXXXXX,
                                            KC_SPC,   KC_LSFT,  MB_PASTE,                                              KC_LCTRL, XXXXXXX,  XXXXXXX
  ),

  /****************************************************************************************************
  *
  * Keymap: Macro layer
  *
  * ,-------------------------------------------------------------------------------------------------------------------.
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
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,     XXXXXXX,  XXXXXXX,  TO(BASE), XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                                                                 XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    _______,  XXXXXXX,  XXXXXXX,  MAIL2,    MAIL1,    XXXXXXX,                                                                 XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    _______,  XXXXXXX,  XXXXXXX,  PWD2,     PWD1,     XXXXXXX,                                                                 XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                                                                 XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
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
  [MDIA] = LAYOUT_pretty(
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,     XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  TO(BASE), XXXXXXX,
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                                                                 XXXXXXX,  XXXXXXX,  KC_MUTE,  KC_VOLD,  KC_VOLU,  XXXXXXX,
    _______,  XXXXXXX,  XXXXXXX,  KC_MS_U,  XXXXXXX,  XXXXXXX,                                                                 XXXXXXX,  XXXXXXX,  KC_MS_U,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    _______,  XXXXXXX,  KC_MS_L,  KC_MS_D,  KC_MS_R,  XXXXXXX,                                                                 XXXXXXX,  KC_MS_L,  KC_MS_D,  KC_MS_R,  XXXXXXX,  XXXXXXX,
    _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                                                                 XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
              XXXXXXX,  XXXXXXX,  KC_BTN1,  KC_BTN2,                                                                                     KC_BTN1,  KC_BTN2,  XXXXXXX,  XXXXXXX,
                                                      XXXXXXX,  XXXXXXX,                                             XXXXXXX,  XXXXXXX,
                                                                XXXXXXX,                                             XXXXXXX,
                                            XXXXXXX,  XXXXXXX,  XXXXXXX,                                             XXXXXXX,  XXXXXXX,  XXXXXXX
  )
  ,

  /****************************************************************************************************
  *
  * Keymap: Config layer
  *
  * ,-------------------------------------------------------------------------------------------------------------------.
  * |  Eprom |Vrsion| Click|      |      |      |      |      |      |      |      |      |      |      |      |        |
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
    EPRM,     VRSN,     CK_TOGG,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,    XXXXXXX,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  TO(BASE),
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                                                                 XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                                                                 XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                                                                 XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                                                                 XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
              XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                                                                                     XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
                                                      XXXXXXX,  XXXXXXX,                                             XXXXXXX,  XXXXXXX,
                                                                XXXXXXX,                                             XXXXXXX,
                                            XXXXXXX,  XXXXXXX,  XXXXXXX,                                             XXXXXXX,  XXXXXXX,  XXXXXXX
  )

};


const uint16_t PROGMEM fn_actions[] = {

};

void wait(int times) {
  for(int i=0; i<times; i++) {

  }
}

void matrix_init_user(void) {
  layer_dependant_rgblight = false;
  all_leds_off();

      kinesis_led_1_on();
      _delay_ms(50);
      all_leds_off();
      kinesis_led_2_on();
      _delay_ms(50);
      all_leds_off();
      kinesis_led_3_on();
      _delay_ms(50);
      all_leds_off();
      kinesis_led_4_on();
      _delay_ms(50);
      all_leds_off();
      kinesis_led_3_on();
      _delay_ms(50);
      all_leds_off();
      kinesis_led_2_on();
      _delay_ms(50);
      all_leds_off();

          kinesis_led_1_on();
          _delay_ms(100);
          all_leds_off();
          kinesis_led_2_on();
          _delay_ms(100);
          all_leds_off();
          kinesis_led_3_on();
          _delay_ms(100);
          all_leds_off();
          kinesis_led_4_on();
          _delay_ms(100);
          all_leds_off();
          kinesis_led_3_on();
          _delay_ms(100);
          all_leds_off();
          kinesis_led_2_on();
          _delay_ms(100);
          all_leds_off();

              kinesis_led_1_on();
              _delay_ms(150);
              all_leds_off();
              kinesis_led_2_on();
              _delay_ms(150);
              all_leds_off();
              kinesis_led_3_on();
              _delay_ms(150);
              all_leds_off();
              kinesis_led_4_on();
              _delay_ms(150);
              all_leds_off();
              kinesis_led_3_on();
              _delay_ms(150);
              all_leds_off();
              kinesis_led_2_on();
              _delay_ms(150);
              all_leds_off();

  kinesis_led_1_on();
  _delay_ms(150);
  all_leds_off();
}

void matrix_scan_user(void) {

}

uint32_t layer_state_set_user(uint32_t state) {

  all_leds_off();

  uint8_t layer = biton32(state);
  switch (layer) {
      case 0:
        all_leds_off();
        break;
      case 1:
        kinesis_led_1_on();
        break;
      case 2:
        kinesis_led_2_on();
        break;
      case 3:
        kinesis_led_3_on();
        break;
      case 4:
        kinesis_led_4_on();
        break;
      case 5:
        // kinesis_led_1_on();
        // kinesis_led_4_on();
        all_leds_on(); // config layer
        break;
      case 6:
        kinesis_led_2_on();
        kinesis_led_4_on();
        break;
      case 7:
        kinesis_led_3_on();
        kinesis_led_4_on();
        break;
      default:
        break;
    }

  return state;
};
