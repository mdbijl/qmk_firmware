#include QMK_KEYBOARD_H
#include "custom_keys.h"
#include "debug.h"
#include "action_layer.h"
#include "version.h"
#include "reregistering.h"
#include "key_combo_definitions.h"
#include "layers.h"


enum triplet {
  commandOption,
  command,
  option,
  noModifiers
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  reset_reregistering();

  switch (keycode) {

    //
    // Custom keys
    //

      // Copy
      // Cmd + Copy     = Alfred snippets
      // Option + Copy  = Cut
    case CB_COPY: {
      static int copyModifiersPressed;

        // Key down
        if (record->event.pressed) {

          if (COMMAND && OPTION) {
            copyModifiersPressed = commandOption;
            return true;
          }

          // Alfred snippets
          else if (COMMAND) {
            copyModifiersPressed = command;
            unregister_and_store_modifiers();
            SEND_STRING(SS_LSFT(SS_LCTRL(SS_LALT(SS_LGUI("c")))));
            reregister_modifiers();
            return false;
          }

          // Cut
          else if (OPTION) {
            copyModifiersPressed = option;
            unregister_modifiers();
            register_code(KC_LGUI);
            register_code(KC_X);
            return false;
          }

          // Copy
          else if (NO_MODIFIERS) {
            copyModifiersPressed = noModifiers;
            unregister_modifiers();
            register_code(KC_LGUI);
            register_code(KC_C);
            return false;
          }

        // Key up
        } else {
          switch (copyModifiersPressed) {
            case option:
              unregister_code(KC_X);
              unregister_modifiers();
              break;
            case noModifiers:
              unregister_code(KC_C);
              unregister_modifiers();
              break;
          }
        }
        return true;
    }
      break;


      // Paste
      // Cmd + Paste     = Alfred multi paste
      // Option + Paste  = Match
    case CB_PASTE: {
      static int pasteModifiersPressed;

      // Key down
      if (record->event.pressed) {

        if (COMMAND && OPTION) {
          pasteModifiersPressed = commandOption;
          return true;
        }

        // Alfred paste
        else if (COMMAND ) {
          pasteModifiersPressed = command;
          unregister_and_store_modifiers();
          SEND_STRING(SS_LCTRL(SS_LSFT(SS_LGUI("c"))));
          reregister_modifiers();
          return false;
        }

        // Match
        else if (OPTION) {
          pasteModifiersPressed = option;
          unregister_modifiers();
          register_code(KC_LGUI);
          register_code(KC_LSHIFT);
          register_code(KC_V);
          return false;
        }

        // Normal paste
        else if (NO_MODIFIERS) {
          pasteModifiersPressed = noModifiers;
          unregister_modifiers();
          register_code(KC_LGUI);
          register_code(KC_V);
          return false;
        }

      // Key up
      } else {
        switch (pasteModifiersPressed) {
          case option:
          case noModifiers:
            unregister_code(KC_V);
            unregister_modifiers();
            break;
        }
      }
      return true;
    }
      break;

      // Undo
      // Option + Undo  = Redo
      case CB_UNDO: {
        static int undoModifiersPressed;

        if (record->event.pressed) {

          if (COMMAND && OPTION) {
            undoModifiersPressed = commandOption;
            return true;
          }

          else if (COMMAND) {
            undoModifiersPressed = command;
            return true;
          }

          // Redo
          else if (OPTION) {
            undoModifiersPressed = option;
            unregister_modifiers();
            register_code(KC_LGUI);
            register_code(KC_LSHIFT);
            register_code(KC_Z);
            return false;
          }

          // Undo
          else if (NO_MODIFIERS) {
            undoModifiersPressed = noModifiers;
            unregister_modifiers();
            register_code(KC_LGUI);
            register_code(KC_Z);
            return false;
          }

        // Key up
        } else {
          switch (undoModifiersPressed) {
            case option:
            case noModifiers:
              unregister_code(KC_Z);
              unregister_modifiers();
              break;
          }
        }
        return true;
      }
        break;

        // Select          = Select All
        // Option + Select = Select None
      case CB_ALL: {
        static int selectModifiersPressed;

        // Key down
        if (record->event.pressed) {

          if (COMMAND && OPTION) {
            selectModifiersPressed = commandOption;
            return true;
          }
          else if (COMMAND) {
            selectModifiersPressed = command;
            return true;
          }

          // Select none
          else if (OPTION) {
            selectModifiersPressed = option;
            unregister_modifiers();
            register_code(KC_LGUI);
            register_code(KC_LSHIFT);
            register_code(KC_A);
            return false;
          }

          // Select all
          else if (NO_MODIFIERS) {
            selectModifiersPressed = noModifiers;
            unregister_modifiers();
            register_code(KC_LGUI);
            register_code(KC_A);
            return false;
          }

        // Key up
        } else {
          switch (selectModifiersPressed) {
            case option:
            case noModifiers:
              unregister_code(KC_A);
              unregister_modifiers();
              break;
          }
        }
        return true;
      }
        break;

        //
        // QMK
        //
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

      //
      // RGB (ErgoDox)
      //
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

      //
      // Macros
      //
    case MAIL1:
      if (record->event.pressed) {
        SEND_STRING ("maurice@debijl.net");
        layer_off (MACR);
      }
      return false;
      break;
    case MAIL2:
      if (record->event.pressed) {
        SEND_STRING ("maurice@conveniencefactory.com");
        layer_off (MACR);
      }
      return false;
      break;
    case PWD1:
      if (record->event.pressed) {
        SEND_STRING ("M13k573r");
        layer_off (MACR);
      }
      return false;
      break;
    case PWD2:
      if (record->event.pressed) {
        SEND_STRING ("M0n573r");
        layer_off (MACR);
      }
      return false;
      break;
    case PWD3:
      if (record->event.pressed) {
        SEND_STRING ("0r1c355");
        layer_off (MACR);
      }
      return false;
      break;
    case NAME1:
      if (record->event.pressed) {
        SEND_STRING ("Maurice");
        layer_off (MACR);
      }
      return false;
      break;
    case NAME2:
      if (record->event.pressed) {
        SEND_STRING ("maurice");
        layer_off (MACR);
      }
      return false;
      break;
  }
  return true;
}


const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // // MACRODOWN only works in this function
  // switch(id) {
  //   case 0:
  //     if (record->event.pressed) {
  //       SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
  //     }
  //     break;
  //   case 1:
  //     if (record->event.pressed) { // For resetting EEPROM
  //       eeconfig_init();
  //     }
  //     break;
  // }
  return MACRO_NONE;
};
