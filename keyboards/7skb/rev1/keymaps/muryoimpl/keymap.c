#include QMK_KEYBOARD_H


#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
  _QWERTY = 0,
  _FN,
  _ADJUST,
};

enum custom_keycodes {
  RGB_RST = SAFE_RANGE,
  MCR0,
  MCR1,
  MCR2,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(
  //,-----------------------------------------------------|   |--------------------------------------------------------------------------------.
       KC_GRV,    KC_1,    KC_2,    KC_3,    KC_4,   KC_5,        KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_MINS,  KC_EQL, KC_BSLS,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------+--------|
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_LBRC, KC_RBRC, KC_ESC,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------|
     KC_LCTRL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,        KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,  KC_ENT,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,        KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT, RCTL(KC_Q),
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
           MO(_ADJUST), KC_LGUI, KC_LALT, KC_SPC,             KC_SPC, MO(_ADJUST), KC_RALT, S(LWIN(SWIN(KC_DEL)))
          //`---------------------------------------------|   |--------------------------------------------'
  ),

  [_FN] = LAYOUT(
  //,-----------------------------------------------------|   |--------------------------------------------------------------------------------.
  TG(_ADJUST), KC_MUTE, KC_VOLD, KC_VOLU, KC_F4, KC_BRIU,       KC_BRID,  KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12, XXXXXXX,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,     _______, _______, KC_PSCR, KC_SLCK,KC_PAUSE,  KC_UP, _______, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,     _______, _______, KC_HOME, KC_PGUP, KC_LEFT,KC_RIGHT, _______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,     _______, _______,  KC_END, KC_PGDN, KC_DOWN, _______, _______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
               _______, _______, _______, _______,              _______, _______,          KC_STOP, _______
          //`---------------------------------------------|   |--------------------------------------------'
  ),

  [_ADJUST] = LAYOUT( /* Base */
  //,-----------------------------------------------------|   |--------------------------------------------------------------------------------.
     KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,       KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  XXXXXXX, KC_DEL,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_DEL, KC_PSCR, XXXXXXX,  RESET,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     MCR0,    MCR1,   MCR2,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
               XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,              XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX
          //`---------------------------------------------|   |--------------------------------------------'
  )

};


//A description for expressing the layer position in LED mode.
layer_state_t layer_state_set_user(layer_state_t state) {
#ifdef RGBLIGHT_ENABLE
    switch (get_highest_layer(state)) {
    case _FN:
      rgblight_sethsv_at(HSV_BLUE, 0);
      break;
    case _ADJUST:
      rgblight_sethsv_at(HSV_PURPLE, 0);
      break;
    default: //  for any other layers, or the default layer
      rgblight_sethsv_at(HSV_GREEN, 0);
      break;
    }
    rgblight_set_effect_range( 1, 4);
#endif
return state;
}

int RGB_current_mode;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  bool result = false;
  switch (keycode) {
    #ifdef RGBLIGHT_ENABLE
      case RGB_MOD:
          if (record->event.pressed) {
            rgblight_mode(RGB_current_mode);
            rgblight_step();
            RGB_current_mode = rgblight_config.mode;
          }
        break;
      case RGB_RST:
          if (record->event.pressed) {
            eeconfig_update_rgblight_default();
            rgblight_enable();
            RGB_current_mode = rgblight_config.mode;
          }
        break;
    #endif
      case MCR0:
          if (record->event.pressed) {
            SEND_STRING(":house:");
          }
          result = true;
        break;
      case MCR1:
          if (record->event.pressed) {
            SEND_STRING(":end:");
          }
          result = true;
        break;
      case MCR2:
          if (record->event.pressed) {
            SEND_STRING(":rice:");
          }
          result = true;
        break;
    default:
      result = true;
      break;
  }

  return result;
}
