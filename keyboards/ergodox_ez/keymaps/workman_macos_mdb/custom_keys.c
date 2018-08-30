#include QMK_KEYBOARD_H
#include "custom_keys.h"
#include "debug.h"
#include "action_layer.h"
#include "version.h"
#include "reregistering.h"
#include "key_combo_definitions.h"

static bool reregister_lgui;
static bool reregister_rgui;
static bool reregister_lalt;
static bool reregister_ralt;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  reset_reregistering();

  switch (keycode) {

    case CB_PASTE:
      if (record->event.pressed) {

        if (COMMAND && OPTION) { return true; }

        // Alfred paste
        else if (COMMAND ) {
          reregister_lgui = unregister_if_needed(KC_LGUI);
          reregister_rgui = unregister_if_needed(KC_RGUI);
          SEND_STRING(SS_LCTRL(SS_LSFT(SS_LGUI("c"))));
          reregister_if_needed();
          return false;
        }

        // Match
        else if (OPTION) {
          reregister_lalt = unregister_if_needed(KC_LALT);
          reregister_ralt = unregister_if_needed(KC_RALT);
          SEND_STRING(SS_LGUI(SS_LSFT("v")));
          reregister_if_needed();
          return false;
        }

        // Normal paste
        else if (NO_MODIFIERS) {
          SEND_STRING(SS_LGUI("v"));
          return false;
        }
      }
      return true;
      break;

    case CB_COPY:
      if (record->event.pressed) {

        if (COMMAND && OPTION) { return true; }

        // Alfred snippets
        else if (COMMAND) {
          reregister_lgui = unregister_if_needed(KC_LGUI);
          reregister_rgui = unregister_if_needed(KC_RGUI);
          SEND_STRING(SS_LSFT(SS_LCTRL(SS_LALT(SS_LGUI("c")))));
          reregister_if_needed();
          return false;
        }

        // Cut
        else if (OPTION) {
          reregister_lalt = unregister_if_needed(KC_LALT);
          reregister_ralt = unregister_if_needed(KC_RALT);
          SEND_STRING(SS_LGUI("x"));
          reregister_if_needed();
          return false;
        }

        // Copy
        else if (NO_MODIFIERS) {
          SEND_STRING(SS_LGUI("c"));
          return false;
        }
      }
      return true;
      break;

      case CB_UNDO:
        if (record->event.pressed) {

          if (COMMAND && OPTION) { return true; }
          else if (COMMAND) { return true; }

          // Redo
          else if (OPTION) {
            reregister_lalt = unregister_if_needed(KC_LALT);
            reregister_ralt = unregister_if_needed(KC_RALT);
            SEND_STRING(SS_LSFT(SS_LGUI("z")));
            reregister_if_needed();
            return false;
          }

          // Undo
          else if (NO_MODIFIERS) {
            SEND_STRING(SS_LGUI("z"));
            return false;
          }
        }
        return true;
        break;

      case CB_ALL:
        if (record->event.pressed) {

          if (COMMAND && OPTION) { return true; }
          else if (COMMAND) {return true; }

          // Redo
          else if (OPTION) {
            reregister_lalt = unregister_if_needed(KC_LALT);
            reregister_ralt = unregister_if_needed(KC_RALT);
            SEND_STRING(SS_LSFT(SS_LGUI("a")));
            reregister_if_needed();
            return true;
          }

          // Undo
          else if (NO_MODIFIERS) {
            SEND_STRING(SS_LGUI("a"));
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
    case RGB_ON:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          rgblight_enable();
          rgblight_mode(1);
          layer_dependant_rgblight = false;
        #endif
      }
      return false;
      break;
    case RGB_OFF:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
        rgblight_disable();
        #endif
      }
      return false;
      break;
    case RGB_LYR: {
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          rgblight_enable();
          rgblight_mode(1);
        #endif
        layer_dependant_rgblight = true;
      }
      return false;
      break;
    }
      case RGB_W: {
        if (record->event.pressed) {
          #ifdef RGBLIGHT_ENABLE
            rgblight_sethsv(0, 0, 255);
          #endif
        }
        return false;
        break;
      }
    case MAIL1:
      if (record->event.pressed) {
        SEND_STRING ("maurice@debijl.net");
      }
      return false;
      break;
    case MAIL2:
      if (record->event.pressed) {
        SEND_STRING ("maurice@conveniencefactory.com");
      }
      return false;
      break;
    case PWD1:
      if (record->event.pressed) {
        SEND_STRING ("M0n573r");
      }
      return false;
      break;
    case PWD2:
      if (record->event.pressed) {
        SEND_STRING ("M13k573r");
      }
      return false;
      break;
  }
  return true;
}


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
