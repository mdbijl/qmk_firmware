// Dual role keys
#define CTL_Z  LCTL_T(KC_Z)
#define CTL_SL RCTL_T(KC_SLASH)
#define CTL_MN RCTL_T(KC_PMNS)

// Copy, paste, undo, select
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

// Ctrl left and right
#define MB_CTLT   LCTL(KC_LEFT)
#define MB_CTRT   LCTL(KC_RIGHT)

#define MB_LOCK   LSFT(LCTL(KC_POWER))

// Home and end
#define MB_TOP    LGUI(KC_UP)
#define MB_BTM    LGUI(KC_DOWN)
#define MB_HOME   LGUI(KC_LEFT)
#define MB_END    LGUI(KC_RIGHT)

// Zoom in and out
#define MB_ZMI    LGUI(KC_PPLS)
#define MB_ZMO    LGUI(KC_PMNS)

// Alt + cursor
#define MB_ALTU   LALT(KC_UP)
#define MB_ALTD   LALT(KC_DOWN)
#define MB_ALTL   LALT(KC_LEFT)
#define MB_ALTR   LALT(KC_RIGHT)

// All Cmd + combinations
#define MB_CMDA  LGUI(KC_A)
#define MB_CMDB  LGUI(KC_B)
#define MB_CMDC  LGUI(KC_C)
#define MB_CMDD  LGUI(KC_D)
#define MB_CMDE  LGUI(KC_E)
#define MB_CMDF  LGUI(KC_F)
#define MB_CMDG  LGUI(KC_G)
#define MB_CMDH  LGUI(KC_H)
#define MB_CMDI  LGUI(KC_I)
#define MB_CMDJ  LGUI(KC_J)
#define MB_CMDK  LGUI(KC_K)
#define MB_CMDL  LGUI(KC_L)
#define MB_CMDM  LGUI(KC_M)
#define MB_CMDN  LGUI(KC_N)
#define MB_CMDO  LGUI(KC_O)
#define MB_CMDP  LGUI(KC_P)
#define MB_CMDQ  LGUI(KC_Q)
#define MB_CMDR  LGUI(KC_R)
#define MB_CMDS  LGUI(KC_S)
#define MB_CMDT  LGUI(KC_T)
#define MB_CMDU  LGUI(KC_U)
#define MB_CMDV  LGUI(KC_V)
#define MB_CMDW  LGUI(KC_W)
#define MB_CMDX  LGUI(KC_X)
#define MB_CMDY  LGUI(KC_Y)
#define MB_CMDZ  LGUI(KC_Z)

// For use in process_record_user
#define COMMAND ((keyboard_report->mods & MOD_BIT(KC_LGUI)) || (keyboard_report->mods & MOD_BIT(KC_RGUI)))
#define OPTION  ((keyboard_report->mods & MOD_BIT(KC_LALT)) || (keyboard_report->mods & MOD_BIT(KC_RALT)))
#define NO_MODIFIERS ((keyboard_report->mods != MOD_BIT(KC_LGUI)) && (keyboard_report->mods != MOD_BIT(KC_RGUI)) && (keyboard_report->mods != MOD_BIT(KC_LALT)) && (keyboard_report->mods != MOD_BIT(KC_RALT)) && (keyboard_report->mods != MOD_BIT(KC_LSHIFT)) && (keyboard_report->mods != MOD_BIT(KC_RSHIFT)) && (keyboard_report->mods != MOD_BIT(KC_LCTRL)) && (keyboard_report->mods != MOD_BIT(KC_RCTRL)))
