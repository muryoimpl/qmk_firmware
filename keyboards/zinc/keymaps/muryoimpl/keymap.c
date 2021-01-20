#include QMK_KEYBOARD_H


extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
    _QWERTY = 0,
    _LOWER,
    _RAISE,
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  MCR0,
  MCR1,
  MCR2,
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

//Macros
#define M_SAMPLE M(KC_SAMPLEMACRO)
#define M_XSC S(LWIN(SWIN(KC_DEL)))
#define CTL_ESC LCTL_T(KC_ESC)

#define RAI _RAISE
#define LOW _LOWER

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = { \
  /* Qwerty
   * ,-----------------------------------------.             ,-----------------------------------------.
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |             |   Y  |   U  |   I  |   O  |   P  | Bksp |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |CTL_ESC|  A  |   S  |   D  |   F  |   G  |             |   H  |   J  |   K  |   L  |   ;  |  '   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  |             |   N  |   M  |   ,  |   .  |   /  |Enter |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Esc  | Alt  | WIN  |MO(RA)|   ~  |Space |             |MO(LO)|Space |Shift |  -   |   [  |  ]   |
   * `-----------------------------------------'             `-----------------------------------------'
   */
[_QWERTY] = LAYOUT_ortho_4x12(
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, \
      CTL_ESC, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
      KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                      KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT , \
      KC_ESC, KC_LALT,  KC_LGUI, MO(RAI), KC_GRV, KC_SPC,                     MO(LOW), KC_SPC,  KC_RSFT, KC_MINS, KC_LBRC, KC_RBRC \
      ),

  /* Lower
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      |   !  |   @  |   #  |   $  |   %  |             |PageUP| Home |  UP  | End  |      | Del  |
   * ,-----------------------------------------.             |------+------+------+------+------+------|
   * |      |   &  |   ^  |   (  |   )  |  _   |             |PageDN| LEFT | DOWN | RIGHT|      | PSCR |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |   \  |   -  |   *  |   /  |  =   |             | MCR0 | MCR1 | MCR2 |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      |      |             |      |      |      |      |   [  |   ]  |
   * `-----------------------------------------'             `-----------------------------------------'
   */
  [_LOWER] = LAYOUT_ortho_4x12( \
      _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_PGUP, KC_HOME, KC_UP,   KC_END,  _______, KC_DEL, \
      _______, KC_AMPR, KC_CIRC, KC_LPRN, KC_RPRN, KC_UNDS,                   KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, _______, KC_PSCR, \
      _______, KC_BSLS, KC_MINS, KC_PAST, KC_SLSH, KC_EQL,                    MCR0,    MCR1,    MCR2,    _______, _______, _______, \
      _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______ \
      ),

  /* Raise
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |   `  |   1  |   2  |   3  |   4  |   5  |             |  F1  |  F2  |  F3  |  F4  |  F5  | Del  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |   6  |   7  |   8  |   9  |   0  |             |  F6  |  F7  |  F8  |  F9  |  F10 | F11  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |   \  |   -  |   *  |   /  |   =  |             |  F12 |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      |      |             |      |      |      |M_XSC |      |RESET |
   * `-----------------------------------------'             `-----------------------------------------'
   */
  [_RAISE] = LAYOUT_ortho_4x12( \
      KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_DEL, \
      _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,                      KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11, \
      _______, KC_BSLS, KC_MINS, KC_PAST, KC_SLSH, KC_EQL,                    KC_F12,  _______, _______, _______, _______, _______, \
      _______, _______, _______, _______, _______, _______,                   _______, _______, _______, M_XSC,   _______, RESET \
      ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;

    case LOWER:
      if (record->event.pressed) {
          //not sure how to have keyboard check mode and set it to a variable, so my work around
          //uses another variable that would be set to true after the first time a reactive key is pressed.
        layer_on(_LOWER);
      } else {
        layer_off(_LOWER);
      }
      return false;
      break;

    case RAISE:
      if (record->event.pressed) {
        //not sure how to have keyboard check mode and set it to a variable, so my work around
        //uses another variable that would be set to true after the first time a reactive key is pressed.
        layer_on(_RAISE);
      } else {
        layer_off(_RAISE);
      }
      return false;
      break;

    case MCR0:
      if (record->event.pressed) {
        SEND_STRING(":house:");
      }
      break;

    case MCR1:
      if (record->event.pressed) {
        SEND_STRING(":end:");
      }
      break;

    case MCR2:
      if (record->event.pressed) {
        SEND_STRING(":rice:");
      }
      break;

  }
  return true;
}
