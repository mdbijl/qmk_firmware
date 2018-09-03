#include QMK_KEYBOARD_H
#include "reregistering.h"

/* Reregistering keys */

static bool reregister_lgui = false;
static bool reregister_rgui = false;
static bool reregister_lalt = false;
static bool reregister_ralt = false;
static bool reregister_lshift = false;
static bool reregister_rshift = false;
static bool reregister_lctrl = false;
static bool reregister_rctrl = false;

void reset_reregistering(void) {
  reregister_rgui = false;
  reregister_lgui = false;
  reregister_ralt = false;
  reregister_lalt = false;
  reregister_rshift = false;
  reregister_lshift = false;
  reregister_rctrl = false;
  reregister_lctrl = false;
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
  if (reregister_rshift)   { register_code(KC_RSHIFT); }
  if (reregister_lshift)   { register_code(KC_LSHIFT); }
  if (reregister_rctrl)   { register_code(KC_RCTRL); }
  if (reregister_lctrl)   { register_code(KC_LCTRL); }  
}
