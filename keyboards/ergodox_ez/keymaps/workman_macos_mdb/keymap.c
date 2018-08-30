#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"

#include "key_combo_definitions.h"
#include "reregistering.h"
#include "custom_keys.h"

static bool layer_dependant_rgblight = true;

/* Layers */

enum layers {
  BASE = 0,
  SYMB,
  FUNC,
  MACR,
  MDIA,
  CNFG,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap Base layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   Esc  |   1  |   2  |   3  |   4  |   5  |      |           |      |   6  |   7  |   8  |   9  |   0  |    `   |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |   Tab  |   Q  |   D  |   R  |   W  |   B  |      |           |      |   J  |   F  |   U  |   P  |   :  |    \   |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |   L2   |   A  |   S  |   H  |   T  |   G  |------|           |------|   Y  |   N  |   E  |   O  |   I  |    '   |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |   L1   |ctrl Z|   X  |   M  |   C  |   V  |      |           |      |   K  |   L  |   ,  |   .  |ctrl /|   L1   |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      | S-All| Undo | Left | Right|                                       |  Up  | Down | Home |  End |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | LGui | LAlt |       | RAlt | RGui |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      | Copy |       |   +  |      |      |
 *                                 |Backsp|LShift|------|       |------|Enter |Space |
 *                                 |   ace|      | Paste|       |ctrl -|      |      |
 *                                 `--------------------'       `--------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = LAYOUT_ergodox(
        // left hand
        KC_ESC,         KC_1,         KC_2,    KC_3,   KC_4,   KC_5,   XXXXXXX,
        KC_TAB,         KC_Q,         KC_D,    KC_R,   KC_W,   KC_B,   XXXXXXX,
        MO(FUNC),       KC_A,         KC_S,    KC_H,   KC_T,   KC_G,
        MO(SYMB),       CTL_Z,        KC_X,    KC_M,   KC_C,   KC_V,  XXXXXXX,
        XXXXXXX,        CB_ALL,       CB_UNDO, KC_LEFT,KC_RGHT,
                                               KC_LGUI,        KC_LALT,
                                                               CB_COPY,
                                               KC_BSPC,KC_LSFT,CB_PASTE,
        // right hand
             XXXXXXX,     KC_6,   KC_7,   KC_8,   KC_9,   KC_0,             KC_GRV,
             XXXXXXX,     KC_J,   KC_F,   KC_U,   KC_P,   KC_SCLN,          KC_BSLS,
                          KC_Y,   KC_N,   KC_E,   KC_O,   KC_I,             KC_QUOT,
             XXXXXXX,     KC_K,   KC_L,   KC_COMM,KC_DOT, CTL_SL,           MO(SYMB),
                                  KC_UP,  KC_DOWN,MB_HOME,MB_END,           XXXXXXX,
             KC_RALT,     KC_RGUI,
             KC_PPLS,
             CTL_MN,      KC_ENT, KC_SPC
    ),

    /* Keymap Symbol Layer
     *
     * ,--------------------------------------------------.           ,--------------------------------------------------.
     * |        |   !  |   @  |   #  |   $  |   %  |      |           |      |   ^  |   &  |   *  |   (  |   )  |    ~   |
     * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
     * |  BaseL |      |      |   =  |   _  |      |      |           |      |      |   +  |   -  |      |   :  |    |   |
     * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
     * |  FuncL  |   [  |   ]  |  {  |   }  |      |------|           |------|      |   (  |   )  |      |      |    "   |
     * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
     * |        |      |      |      |      |      |      |           |      |      |      |   <  |  >   |   ?  |        |
     * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
     *   |      | None | Redo |altlft|altrgt|                                       |ScrolD|ScrolU|  top | bottom|      |
     *   `----------------------------------'                                       `----------------------------------'
     *                                        ,-------------.       ,-------------.
     *                                        |      |      |       |      |      |
     *                                 ,------|------|------|       |------+------+------.
     *                                 |      |      | Cut  |       |cmd + |      |      |
     *                                 |Delete|      |------|       |------|  Esc |Backsp|
     *                                 |      |      | Match|       |cmd - |      |   ace|
     *                                 `--------------------'       `--------------------'
     */
    // SYMBOLS
    [SYMB] = LAYOUT_ergodox(
       // left hand
       TO(BASE),KC_EXLM, KC_AT,    KC_HASH, KC_DLR,  KC_PERC, XXXXXXX,
       TO(BASE),XXXXXXX, XXXXXXX,  KC_EQL,  KC_UNDS, XXXXXXX, XXXXXXX,
       TO(FUNC),KC_LBRC, KC_RBRC,  KC_LCBR, KC_RCBR, XXXXXXX,
       _______, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, _______,
       XXXXXXX, MB_NONE, MB_REDO,  MB_ALTL, MB_ALTR,
                                            XXXXXXX, XXXXXXX,
                                                     MB_CUT,
                                   KC_DELT, XXXXXXX, MB_MATCH,
       // right hand
       XXXXXXX, KC_CIRC, KC_AMPR,KC_ASTR, KC_LPRN,  KC_RPRN, KC_TILD,
       XXXXXXX, XXXXXXX, KC_PLUS, KC_MINS, XXXXXXX, KC_COLN, KC_PIPE,
                XXXXXXX, KC_LPRN, KC_RPRN, XXXXXXX, XXXXXXX, KC_DQT,
       XXXXXXX, XXXXXXX, XXXXXXX, KC_LT,   KC_GT,   KC_QUES, XXXXXXX,
                         KC_WH_D, KC_WH_U, MB_TOP,  MB_BTM,  XXXXXXX,
       XXXXXXX, XXXXXXX,
       MB_ZMI,
       MB_ZMO, KC_ESC,  KC_BSPC
    ),

/* Keymap 2: Function Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |   L0   | CMDQ | CMDD |  ... |      |      |      |           |      |      |      |      |      |      |   F12  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |   L+   |      |      |      |      |      |------|           |------|      |      |      |      |      |   F13  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |   L-   |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      | ^left|^right|                                       | pgup | pgdn |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      | Alt  |       | Alt  |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |Snippt|       |      |      |      |
 *                                 | Space| Shift|------|       |------|      |      |
 *                                 |      |      |Mpaste|       | Ctrl |      |      |
 *                                 `--------------------'       `--------------------'
 */
// FUNCTION
[FUNC] = LAYOUT_ergodox(
   // left hand
   XXXXXXX,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   XXXXXXX,
   TO(BASE), MB_CMDQ, MB_CMDD, MB_CMDR, MB_CMDW, MB_CMDB, XXXXXXX,
   TO(MACR), MB_CMDA, MB_CMDS, MB_CMDH, MB_CMDT, MB_CMDG,
   TO(BASE), MB_CMDZ, MB_CMDX, MB_CMDM, MB_CMDC, MB_CMDV, XXXXXXX,
   XXXXXXX,  XXXXXXX, XXXXXXX, MB_CTLT, MB_CTRT,
                                        XXXXXXX, KC_LALT,
                                                 MB_SNIP,
                              KC_SPACE, KC_LSFT, MB_PASTE,
   // right hand
   XXXXXXX, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
   XXXXXXX, MB_CMDJ, MB_CMDF, MB_CMDU, MB_CMDP, XXXXXXX, KC_F12,
            MB_CMDY, MB_CMDN, MB_CMDE, MB_CMDO, MB_CMDI, KC_F13,
   XXXXXXX, MB_CMDK, MB_CMDL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                     KC_PGUP, KC_PGDN, XXXXXXX, XXXXXXX, XXXXXXX,
   KC_RALT, XXXXXXX,
   XXXXXXX,
   KC_LCTRL,XXXXXXX, XXXXXXX
),

/* Macros
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |     |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |   L0   |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |   L+   |      |      | Mail2| Mail1|      |------|           |------|      | Pwd1 | Pwd2 |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |   L-   |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// MACROS
[MACR] = LAYOUT_ergodox(
   // left hand
   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
   TO(BASE),XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
   TO(MDIA),XXXXXXX, XXXXXXX, MAIL2,   MAIL1,   XXXXXXX,
   TO(FUNC),XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                       XXXXXXX, XXXXXXX,
                                                XXXXXXX,
                              XXXXXXX, XXXXXXX, XXXXXXX,
   // right hand
   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
            XXXXXXX, PWD1,    PWD2,    XXXXXXX, XXXXXXX, XXXXXXX,
   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
   XXXXXXX, XXXXXXX,
   XXXXXXX,
   XXXXXXX,XXXXXXX, XXXXXXX
),
/* Keymap Media and mouse keys
 *ergodox_ez/workman_macos_mdb @ 0.6.92-59-g9584d1-dirty
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |Brigh-|Brigh+|      |      |      |      |           |      |      |      | Mute | VolDn| VolUp|        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |   L0   |      |      | MsUp |      |      |      |           |      |      |      | MsUp |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |   L+   |      |MsLeft|MsDown|MsRght|      |------|           |------|      |MsLeft|MsDown|MsRght|      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |   L-   |      |      |      |      |      |      |           |      |      |      |      |      |      |   L0   |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      | Lclk | Rclk |                                       | Lclk | Rclk |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// MEDIA AND MOUSE
[MDIA] = LAYOUT_ergodox(
       XXXXXXX,  KC_F14,  KC_F15,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
       TO(BASE), XXXXXXX, XXXXXXX, KC_MS_U, XXXXXXX, XXXXXXX, XXXXXXX,
       TO(CNFG), XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_R, XXXXXXX,
       TO(MACR), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
       XXXXXXX,  XXXXXXX, XXXXXXX, KC_BTN1, KC_BTN2,
                                           XXXXXXX, XXXXXXX,
                                                    XXXXXXX,
                                  XXXXXXX, XXXXXXX, XXXXXXX,
    // right hand
       KC_MPRV,  KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU, XXXXXXX,
       XXXXXXX,  XXXXXXX, XXXXXXX, KC_MS_U, XXXXXXX, XXXXXXX, XXXXXXX,
                 XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_R, XXXXXXX, XXXXXXX,
       XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                          KC_BTN1, KC_BTN2, XXXXXXX, XXXXXXX, XXXXXXX,
       XXXXXXX, XXXXXXX,
       XXXXXXX,
       XXXXXXX, XXXXXXX, XXXXXXX
),

/* Keymap Keyboard rgb underflow light config
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  White | Br+  | Br+  | Hue+ | Hue- | Sat- | Sat+ |           |  Off |  On  | Solid| Layer| Anim | Anim |Version |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |   L0   |      |      |      |      |      |      |           |      | Anim | Anim | Anim | Anim | Anim |  Eprom |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |   L+   |      |      |      |      |      |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |   L-   |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[CNFG] = LAYOUT_ergodox(
       RGB_W,    RGB_VAD, RGB_VAI, RGB_HUI, RGB_HUD, RGB_SAD, RGB_SAI,
       TO(BASE), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
       XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
       TO(MDIA), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
       XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                           XXXXXXX, XXXXXXX,
                                                    XXXXXXX,
                                  XXXXXXX, XXXXXXX, XXXXXXX,
    // right hand
       RGB_OFF, RGB_ON,  RGB_LYR, RGB_M_B, RGB_M_R, RGB_M_SW,VRSN,
       XXXXXXX, RGB_M_SN,RGB_M_K, RGB_M_X, RGB_M_G, RGB_M_T, EPRM,
                XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
       XXXXXXX, XXXXXXX,
       XXXXXXX,
       XXXXXXX, XXXXXXX, XXXXXXX
),

};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(SYMB)                // FN1 - Momentary Layer 1 (Symbols)
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
#ifdef RGBLIGHT_COLOR_LAYER_0
  rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
#endif
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

};

// Runs whenever there is a layer state change.
uint32_t layer_state_set_user(uint32_t state) {
  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();

  uint8_t layer = biton32(state);
  switch (layer) {
      case 0:
        #ifdef RGBLIGHT_COLOR_LAYER_0
        if (layer_dependant_rgblight) {
          rgblight_sethsv (RGBLIGHT_COLOR_LAYER_0);
        }
        #else
        #ifdef RGBLIGHT_ENABLE
        if (layer_dependant_rgblight) {
          rgblight_init();
        }
        #endif
        #endif
        break;
      case 1:
        ergodox_right_led_1_on();
        #ifdef RGBLIGHT_COLOR_LAYER_1
        if (layer_dependant_rgblight) {
          rgblight_sethsv(RGBLIGHT_COLOR_LAYER_1);
        }
        #endif
        break;
      case 2:
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_2
        if (layer_dependant_rgblight) {
          rgblight_sethsv(RGBLIGHT_COLOR_LAYER_2);
        }
        #endif
        break;
      case 3:
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_3
        if (layer_dependant_rgblight) {
            rgblight_sethsv(RGBLIGHT_COLOR_LAYER_3);
        }
        #endif
        break;
      case 4:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_4
        if (layer_dependant_rgblight) {
          rgblight_sethsv(RGBLIGHT_COLOR_LAYER_4);
        }
        #endif
        break;
      case 5:
        ergodox_right_led_1_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_5
        if (layer_dependant_rgblight) {
          rgblight_sethsv(RGBLIGHT_COLOR_LAYER_5);
        }
        #endif
        break;
      case 6:
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_6
        if (layer_dependant_rgblight) {
          rgblight_sethsv(RGBLIGHT_COLOR_LAYER_6);
        }
        #endif
        break;
      case 7:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_7
        if (layer_dependant_rgblight) {
          rgblight_sethsv(RGBLIGHT_COLOR_LAYER_6);
        }
        #endif
        break;
      default:
        break;
    }

  return state;
};
