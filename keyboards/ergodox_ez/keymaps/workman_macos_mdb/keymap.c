#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"

#define LT1_K LT(SYMB,KC_K)
#define LT1_V LT(SYMB,KC_V)

#define SH_ESC LSFT_T(KC_ESCAPE)
#define SH_ENT RSFT_T(KC_ENTER)

#define CTL_Z  LCTL_T(KC_Z)
#define CTL_SL RCTL_T(KC_SLASH)
#define CTL_MN RCTL_T(KC_PMNS)

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

#define MB_TOP    LGUI(KC_UP)
#define MB_BTM    LGUI(KC_DOWN)
#define MB_HOME   LGUI(KC_LEFT)
#define MB_END    LGUI(KC_RIGHT)

#define MB_ZMI    LGUI(KC_PPLS)
#define MB_ZMO    LGUI(KC_PMNS)

#define MB_ALTU   LALT(KC_UP)
#define MB_ALTD   LALT(KC_DOWN)
#define MB_ALTL   LALT(KC_LEFT)
#define MB_ALTR   LALT(KC_RIGHT)


// For use in process_record_user
#define COMMAND ((keyboard_report->mods & MOD_BIT(KC_LGUI)) || (keyboard_report->mods & MOD_BIT(KC_RGUI)))
#define OPTION  ((keyboard_report->mods & MOD_BIT(KC_LALT)) || (keyboard_report->mods & MOD_BIT(KC_RALT)))
#define NO_MODIFIERS ((keyboard_report->mods != MOD_BIT(KC_LGUI)) && (keyboard_report->mods != MOD_BIT(KC_RGUI)) && (keyboard_report->mods != MOD_BIT(KC_LALT)) && (keyboard_report->mods != MOD_BIT(KC_RALT)) && (keyboard_report->mods != MOD_BIT(KC_LSHIFT)) && (keyboard_report->mods != MOD_BIT(KC_RSHIFT)) && (keyboard_report->mods != MOD_BIT(KC_LCTRL)) && (keyboard_report->mods != MOD_BIT(KC_RCTRL)))

enum layers {
  BASE = 0,
  SYMB,
  FUNC,
  MDIA
};

enum custom_keycodes {
  EPRM = SAFE_RANGE,
  VRSN,
  RGB_SLD,
  CB_PASTE,  // Combo
  CB_COPY,   // Combo
};

static bool reregisterLGui;
static bool reregisterRGui;
static bool reregisterLAlt;
static bool reregisterRAlt;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
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
[BASE] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        KC_ESC,         KC_1,         KC_2,    KC_3,   KC_4,   KC_5,   XXXXXXX,
        KC_TAB,         KC_Q,         KC_D,    KC_R,   KC_W,   KC_B,   XXXXXXX,
        TT(FUNC),       KC_A,         KC_S,    KC_H,   KC_T,   KC_G,
        MO(SYMB),       CTL_Z,        KC_X,    KC_M,   KC_C,   LT1_V,  XXXXXXX,
        XXXXXXX,        MB_ALL,       MB_UNDO, KC_LEFT,KC_RGHT,
                                               KC_LGUI,        KC_LALT,
                                                               CB_COPY,
                                               KC_BSPC,KC_LSFT,CB_PASTE,
        // right hand
             XXXXXXX,     KC_6,   KC_7,   KC_8,   KC_9,   KC_0,             KC_GRV,
             XXXXXXX,     KC_J,   KC_F,   KC_U,   KC_P,   KC_SCLN,          KC_BSLS,
                          KC_Y,   KC_N,   KC_E,   KC_O,   KC_I,             KC_QUOT,
             XXXXXXX,     LT1_K,  KC_L,   KC_COMM,KC_DOT, CTL_SL,           MO(SYMB),
                                  KC_UP,  KC_DOWN,MB_HOME,MB_END,           XXXXXXX,
             KC_RALT,     KC_RGUI,
             KC_PPLS,
             CTL_MN,      KC_ENT, KC_SPC
    ),
    /* Keymap 1: Symbol Layer
     *
     * ,--------------------------------------------------.           ,--------------------------------------------------.
     * |        |   !  |   @  |   #  |   $  |   %  |      |           |      |   ^  |   &  |   *  |   (  |   )  |    ~   |
     * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
     * |        |      |      |   =  |   _  |      |      |           |      |   +  |   -  |      |      |   :  |    |   |
     * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
     * |   L3   |   [  |   ]  |   {  |   }  |      |------|           |------|   (  |   )  |      |      |      |    "   |
     * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
     * |        |      |      |      |      |      |      |           |      |      |      |   <  |  >   |   ?  |        |
     * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
     *   |      | None | Redo |altlft|altrgt|                                       |  top |bottom|ScrolU|ScrolD|      |
     *   `----------------------------------'                                       `----------------------------------'
     *                                        ,-------------.       ,-------------.
     *                                        |      |      |       |      |      |
     *                                 ,------|------|------|       |------+------+------.
     *                                 |      |      | Cut  |       |cmd + |      |      |
     *                                 |Space |      |------|       |------|  Esc |Backsp|
     *                                 |      |      | Match|       |cmd - |      |   ace|
     *                                 `--------------------'       `--------------------'
     */
    // SYMBOLS
[SYMB] = LAYOUT_ergodox(
       // left hand
       XXXXXXX, KC_EXLM, KC_AT,    KC_HASH, KC_DLR,  KC_PERC, XXXXXXX,
       XXXXXXX, XXXXXXX, XXXXXXX,  KC_EQL,  KC_UNDS, XXXXXXX, XXXXXXX,
       TO(MDIA),KC_LBRC, KC_RBRC,  KC_LCBR, KC_RCBR, XXXXXXX,
       _______, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, _______,
       XXXXXXX, MB_NONE, MB_REDO,  MB_ALTL, MB_ALTR,
                                            XXXXXXX, XXXXXXX,
                                                     MB_CUT,
                                   KC_SPC,  XXXXXXX, MB_MATCH,
       // right hand
       XXXXXXX, KC_CIRC, KC_AMPR,KC_ASTR, KC_LPRN,  KC_RPRN, KC_TILD,
       XXXXXXX, XXXXXXX, KC_PLUS, KC_MINS, XXXXXXX, KC_COLN, KC_PIPE,
                XXXXXXX, KC_LPRN, KC_RPRN, XXXXXXX, XXXXXXX, KC_DQT,
       XXXXXXX, XXXXXXX, XXXXXXX, KC_LT,   KC_GT,   KC_QUES, XXXXXXX,
                         MB_TOP,  MB_BTM,  KC_WH_U, KC_WH_D, XXXXXXX,
       XXXXXXX, XXXXXXX,
       MB_ZMI,
       MB_ZMO, KC_ESC,  KC_BSPC
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
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      | pgup | pgdn |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |Snippt|       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |Mpaste|       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// FUNCTION
[FUNC] = LAYOUT_ergodox(
   // left hand
   XXXXXXX, KC_F1,   KC_F2,    KC_F3,   KC_F4,   KC_F5,   XXXXXXX,
   XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
   TO(BASE),XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX,
   _______, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                       XXXXXXX, XXXXXXX,
                                                MB_SNIP,
                              XXXXXXX, XXXXXXX, MB_PASTE,
   // right hand
   XXXXXXX, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_F12,
            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_F13,
   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
                     XXXXXXX, XXXXXXX, KC_PGUP, KC_PGDN,  XXXXXXX,
   XXXXXXX, XXXXXXX,
   XXXXXXX,
   XXXXXXX, XXXXXXX, XXXXXXX
),
/* Keymap 3: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      | Mute | VolDn| VolUp|        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      | MsUp |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |   L0   |      |MsLeft|MsDown|MsRght|      |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |   L0   |      |      |      |      |      |      |           |      |      |      |      |      |      |   L0   |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      | Lclk | Rclk |                                       |      |      |      |      |      |
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
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
       XXXXXXX, XXXXXXX, XXXXXXX, KC_MS_U, XXXXXXX, XXXXXXX, XXXXXXX,
       TO(BASE),XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_R, XXXXXXX,
       TO(BASE),XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
       XXXXXXX, XXXXXXX, XXXXXXX, KC_BTN1, KC_BTN2,
                                           XXXXXXX, XXXXXXX,
                                                    XXXXXXX,
                                  XXXXXXX, XXXXXXX, XXXXXXX,
    // right hand
       KC_MPRV,  KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU, XXXXXXX,
       XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
       XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TO(BASE),
                          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
       XXXXXXX, XXXXXXX,
       XXXXXXX,
       XXXXXXX, XXXXXXX, XXXXXXX
),
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(SYMB)                // FN1 - Momentary Layer 1 (Symbols)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
  switch(id) {
    case 0:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      break;
    case 1:
      if (record->event.pressed) { // For resetting EEPROM
        eeconfig_init();
      }
      break;
  }
  return MACRO_NONE;
};

bool unregister_if_needed(uint8_t code) {
  if (keyboard_report->mods & MOD_BIT(code)) {
    unregister_code(code);
    return true;
  } else {
    return false;
  }
}

void reregister_if_needed(void) {
  if (reregisterRGui)   { register_code(KC_LGUI); }
  if (reregisterLGui)   { register_code(KC_RGUI); }
  if (reregisterRAlt)   { register_code(KC_RALT); }
  if (reregisterLAlt)   { register_code(KC_LALT); }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {

    case CB_PASTE:
      if (record->event.pressed) {

        if (COMMAND && OPTION) {
        }

        // Alfred paste
        else if (COMMAND ) {
          reregisterLGui = unregister_if_needed(KC_LGUI);
          reregisterRGui = unregister_if_needed(KC_RGUI);
          SEND_STRING(SS_LCTRL(SS_LSFT(SS_LGUI("c"))));
          reregister_if_needed();
          return true;
        }

        // Match
        else if (OPTION) {
          reregisterLAlt = unregister_if_needed(KC_LALT);
          reregisterRAlt = unregister_if_needed(KC_RALT);
          SEND_STRING(SS_LGUI(SS_LSFT("v")));
          reregister_if_needed();
          return true;
        }

        // Normal paste
        else if (NO_MODIFIERS) {
          SEND_STRING(SS_LGUI("v"));
          return true;
        }
      }
      return false;
      break;

    case CB_COPY:
      if (record->event.pressed) {

        if (COMMAND && OPTION) {
        }

        // Alfred shippets
        else if (COMMAND) {
          reregisterLGui = unregister_if_needed(KC_LGUI);
          reregisterRGui = unregister_if_needed(KC_RGUI);
          SEND_STRING(SS_LSFT(SS_LCTRL(SS_LALT(SS_LGUI("c")))));
          reregister_if_needed();
          return true;
        }

        // Cut
        else if (OPTION) {
          reregisterLAlt = unregister_if_needed(KC_LALT);
          reregisterRAlt = unregister_if_needed(KC_RALT);
          SEND_STRING(SS_LGUI("x"));
          reregister_if_needed();
          return true;
        }

        // Copy
        else if (NO_MODIFIERS) {
          SEND_STRING(SS_LGUI("c"));
          return true;
        }
      }
      return false;
      break;
    case EPRM:
      if (record->event.pressed) {
        eeconfig_init();
      }
      return false;
      break;
    case VRSN:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      return false;
      break;
    case RGB_SLD:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          rgblight_mode(1);
        #endif
      }
      return false;
      break;
  }
  return true;
}

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
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
        #else
        #ifdef RGBLIGHT_ENABLE
          rgblight_init();
        #endif
        #endif
        break;
      case 1:
        ergodox_right_led_1_on();
        #ifdef RGBLIGHT_COLOR_LAYER_1
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_1);
        #endif
        break;
      case 2:
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_2
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_2);
        #endif
        break;
      case 3:
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_3
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_3);
        #endif
        break;
      case 4:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_4
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_4);
        #endif
        break;
      case 5:
        ergodox_right_led_1_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_5
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_5);
        #endif
        break;
      case 6:
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_6
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
        #endif
        break;
      case 7:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_7
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
        #endif
        break;
      default:
        break;
    }

  return state;
};
