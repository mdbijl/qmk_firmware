#include QMK_KEYBOARD_H
#include "reregistering.h"

/* Reregistering keys */

static bool reregister_lgui = false;
static bool reregister_rgui = false;
static bool reregister_lalt = false;
static bool reregister_ralt = false;
static bool reregister_lctrl = false;
static bool reregister_rctrl = false;
static bool reregister_lshift = false;
static bool reregister_rshift = false;

void reset_reregistering(void) {
  reregister_lgui = false;
  reregister_rgui = false;
  reregister_lalt = false;
  reregister_ralt = false;
  reregister_lctrl = false;
  reregister_rctrl = false;
  reregister_lshift = false;
  reregister_rshift = false;
}

bool unregister_if_needed(uint8_t code) {
  if (keyboard_report->mods & MOD_BIT(code)) {
    unregister_code(code);
    return true;
  } else {
    return false;
  }
}

void unregister_modifiers(void) {
  unregister_code(KC_LGUI);
  unregister_code(KC_RGUI);
  unregister_code(KC_LALT);
  unregister_code(KC_RALT);
  unregister_code(KC_LCTRL);
  unregister_code(KC_RCTRL);
  unregister_code(KC_LSHIFT);
  unregister_code(KC_RSHIFT);
}

void unregister_and_store_modifiers(void) {
  reregister_lgui = unregister_if_needed(KC_LGUI);
  reregister_rgui = unregister_if_needed(KC_RGUI);
  reregister_lalt = unregister_if_needed(KC_LALT);
  reregister_ralt = unregister_if_needed(KC_RALT);
  reregister_lctrl = unregister_if_needed(KC_LCTRL);
  reregister_rctrl = unregister_if_needed(KC_RCTRL);
  reregister_lshift = unregister_if_needed(KC_LSHIFT);
  reregister_rshift = unregister_if_needed(KC_RSHIFT);
}


void reregister_modifiers(void) {
  if (reregister_lgui)   { register_code(KC_LGUI); }
  if (reregister_rgui)   { register_code(KC_RGUI); }
  if (reregister_lalt)   { register_code(KC_LALT); }
  if (reregister_ralt)   { register_code(KC_RALT); }
  if (reregister_lctrl)  { register_code(KC_LCTRL); }
  if (reregister_rctrl)  { register_code(KC_RCTRL); }
  if (reregister_lshift) { register_code(KC_LSHIFT); }
  if (reregister_rshift) { register_code(KC_RSHIFT); }
}
