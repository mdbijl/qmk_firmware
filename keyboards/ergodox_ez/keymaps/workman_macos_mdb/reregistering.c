#include QMK_KEYBOARD_H
#include "reregistering.h"
#include "debug.h"
#include "action_layer.h"
#include "version.h"

/* Reregistering keys */

void reset_reregistering(void) {
  reregister_rgui = false;
  reregister_lgui = false;
  reregister_ralt = false;
  reregister_lalt = false;
}

bool unregister_if_needed(uint8_t code) {
  if (keyboard_report->mods & MOD_BIT(code)) {
    unregister_code(code);
    return true;
  } else {
    return false;
  }
}

void reregister_if_needed(void) {
  if (reregister_rgui)   { register_code(KC_RGUI); }
  if (reregister_lgui)   { register_code(KC_LGUI); }
  if (reregister_ralt)   { register_code(KC_RALT); }
  if (reregister_lalt)   { register_code(KC_LALT); }
}
