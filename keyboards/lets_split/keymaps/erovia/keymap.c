#include QMK_KEYBOARD_H

enum planck_layers {
  _QWERTY,
  _COLEMAK,
  _LOWER,
  _RAISE,
  _ADJUST
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  LOWER,
  RAISE
};

enum {
  TD_SPACE_CADET_SHIFT = 0,
  TD_SPACE_CADET_ENTER,
  TD_A,
  TD_E,
  TD_I,
  TD_U,
  TD_O
};

#define ae "00E1"  // á
#define AE "00C1"  // Á
void tap_dance_a_finished (qk_tap_dance_state_t *state, void *user_data) {
  switch(state->count) {
    case 1: send_unicode_hex_string(ae); break;
    case 2: send_unicode_hex_string(AE); break;
  }
}

#define ee "00E9"  // é
#define EE "00C9"  // É
void tap_dance_e_finished (qk_tap_dance_state_t *state, void *user_data) {
  switch(state->count) {
    case 1: send_unicode_hex_string(ee); break;
    case 2: send_unicode_hex_string(EE); break;
  }
}

#define ie "00ED"  // í
#define IE "00CD"  // Í
void tap_dance_i_finished (qk_tap_dance_state_t *state, void *user_data) {
  switch(state->count) {
    case 1: send_unicode_hex_string(ie); break;
    case 2: send_unicode_hex_string(IE); break;
  }
}

#define ue "00FC"  // ü
#define UE "00DC"  // Ü
#define uee "0171" // ű
#define UEE "0170" // Ű
void tap_dance_u_finished (qk_tap_dance_state_t *state, void *user_data) {
  switch(state->count) {
    case 1: send_unicode_hex_string(ue); break;
    case 2: send_unicode_hex_string(UE); break;
    case 3: send_unicode_hex_string(uee); break;
    case 4: send_unicode_hex_string(UEE); break;
  }
}

#define oe "00F6"  // ö
#define OE "00D6"  // Ö
#define oee "0151" // ő
#define OEE "0150" // Ő
void tap_dance_o_finished (qk_tap_dance_state_t *state, void *user_data) {
  switch(state->count) {
    case 1: send_unicode_hex_string(oe); break;
    case 2: send_unicode_hex_string(OE); break;
    case 3: send_unicode_hex_string(oee); break;
    case 4: send_unicode_hex_string(OEE); break;
  }
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_SPACE_CADET_SHIFT] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_LPRN),
  [TD_SPACE_CADET_ENTER] = ACTION_TAP_DANCE_DOUBLE(KC_ENT, KC_RPRN),
  [TD_A] = ACTION_TAP_DANCE_FN(tap_dance_a_finished),
  [TD_E] = ACTION_TAP_DANCE_FN(tap_dance_e_finished),
  [TD_I] = ACTION_TAP_DANCE_FN(tap_dance_i_finished),
  [TD_U] = ACTION_TAP_DANCE_FN(tap_dance_u_finished),
  [TD_O] = ACTION_TAP_DANCE_FN(tap_dance_o_finished)
};

#define TD_SHFT TD(TD_SPACE_CADET_SHIFT)
#define TD_ENTR TD(TD_SPACE_CADET_ENTER)
#define TD_A TD(TD_A)
#define TD_E TD(TD_E)
#define TD_I TD(TD_I)
#define TD_U TD(TD_U)
#define TD_O TD(TD_O)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | `    |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  | Alt  |MBTN3 |Lower | Tab  |Space |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_ortho_4x12(
  KC_GRV,  KC_Q,    KC_W,    KC_E,    KC_R,  KC_T,   KC_Y,   KC_U,  KC_I,    KC_O,    KC_P,    KC_BSPC,
  KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,  KC_G,   KC_H,   KC_J,  KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  TD_SHFT, KC_Z,    KC_X,    KC_C,    KC_V,  KC_B,   KC_N,   KC_M,  KC_COMM, KC_DOT,  KC_SLSH, TD_ENTR,
  KC_LCTL, KC_LGUI, KC_LALT, KC_BTN3, LOWER, KC_TAB, KC_SPC, RAISE, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* Colemak
 * ,-----------------------------------------------------------------------------------.
 * | `    |   Q  |   W  |   F  |   P  |   B  |   J  |   L  |   U  |   Y  |   ;  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Ctrl |   A  |   R  |   S  |   T  |   G  |   M  |   N  |   E  |   I  |   O  |  '   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   D  |   V  |   K  |   H  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  | Alt  |MBTN3 |Lower | Tab  |Space |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_COLEMAK] = LAYOUT_ortho_4x12(
  KC_GRV,  KC_Q,    KC_W,    KC_F,    KC_P,  KC_B,   KC_J,   KC_L,  KC_U,    KC_Y,    KC_SCLN, KC_BSPC,
  KC_ESC,  KC_A,    KC_R,    KC_S,    KC_T,  KC_G,   KC_M,   KC_N,  KC_E,    KC_I,    KC_O,    KC_QUOT,
  TD_SHFT, KC_Z,    KC_X,    KC_C,    KC_D,  KC_V,   KC_K,   KC_H,  KC_COMM, KC_DOT,  KC_SLSH, TD_ENTR,
  KC_LCTL, KC_LGUI, KC_LALT, KC_BTN3, LOWER, KC_TAB, KC_SPC, RAISE, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO ~ |ISO | | Home | End  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_ortho_4x12(
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR,    KC_ASTR,    KC_LPRN, KC_RPRN, KC_BSPC,
  KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS,    KC_PLUS,    KC_LCBR, KC_RCBR, KC_PIPE,
  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  S(KC_NUHS), S(KC_NUBS), KC_HOME, KC_END,  _______,
  _______, _______, _______, _______, _______, _______, _______, _______,    KC_MNXT,    KC_VOLD, KC_VOLU, KC_MPLY
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Ins  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO # |ISO / |Pg Up |Pg Dn |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Prev | Vol- | Mute | Stop |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_ortho_4x12(
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  KC_INS,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NUHS, KC_NUBS, KC_PGUP, KC_PGDN, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, KC_MPRV, KC_VOLD, KC_MUTE, KC_MSTP
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |EEPRST|RESET |      |      |      |      |      |      |  Ue  |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  Ae  |      |      |      |      |Qwerty|Colemk|  Ee  |  Ie  |  Oe  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      | AuSh |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_ortho_4x12(
  EEP_RST, RESET,   _______, _______, _______, _______, _______, _______, TD_U,    _______, _______, _______,
  _______, TD_A   , _______, _______, _______, _______, QWERTY,  COLEMAK, TD_E,    TD_I,    TD_O,    _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, KC_ASDN, KC_ASUP, KC_ASRP, KC_ASTG
)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
  }
  return true;
}

void eeconfig_init_user() {
  set_unicode_input_mode(UC_LNX);
}
