// Copyright (C) 2019, 2020  Keyboard.io, Inc
//
// this is the style you want to emulate.
// This is the canonical layout file for the Quantum project. If you want to add another keyboard,

#include QMK_KEYBOARD_H

enum layer_names {
    _QW,
    _RS,
    _LW,
};

enum custom_keycodes {
  RGB_RST = SAFE_RANGE,
  MCR0,
  MCR1,
  MCR2,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /*
   *      Q            W        E         R       T              ||           Y       U        I        O        P
   *      A            S        D         F       G              ||           H       J        J        L        ;
   *      Z            X        C         V       B       ~      ||  |        N       M        <        >        /
   *     esc          tab     super     shift    bksp     ctrl   || space   fn(_RS)  fn(_LW)   -        '      enter
   */
  [_QW] = LAYOUT( /* Qwerty */
    KC_Q,            KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P    ,
    KC_A,            KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN ,
    KC_Z,            KC_X,    KC_C,    KC_V,    KC_B,    KC_GRV,  KC_BSLS, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH ,
    KC_ESC,         KC_TAB,  KC_LSFT,  KC_LGUI, KC_BSPC,  KC_LCTL, KC_SPC,  MO(_RS), MO(_LW), KC_MINS, KC_QUOT, KC_ENT ),

  /*
   *      1            2         3         4       5              ||          pgup    home       up      end     *
   *      6            7         8         9       0              ||          pgdn    left      down    right    +
   *      [            ]         (         )       {        }     ||   &       !       #         $        @      /
   *     MACRO        tab      super     shift   delete    ctrl   || space     fn      fn       alt       =      =
   */
  [_RS] = LAYOUT( /* [> RAISE <] */
    KC_1,              KC_2,    KC_3,    KC_4,    KC_5,                      KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_ASTR,
    KC_6,              KC_7,    KC_8,    KC_9,    KC_0,                      KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_PLUS,
    KC_LBRC,           KC_RBRC, KC_LPRN, KC_RPRN, KC_LCBR, KC_RCBR, KC_AMPR, KC_EXLM, KC_HASH, KC_DLR,  KC_AT,   KC_SLSH,
    KC_NO,             _______, _______, _______, KC_DEL,  _______, _______, _______, _______, KC_LALT, KC_EQL,  KC_EQL ),
 // S(LWIN(SWIN(KC_DEL))), _______, _______, _______, KC_DEL, _______, _______, _______, _______, KC_LALT, KC_EQL,  KC_EQL),

  /*
   *      F1            F2        F3      F4       F5             ||
   *      F6            F7        F8      F9       F10            ||     down    F4    F5    F6   F11
   *      F11           F12       XX      XX       XX        XX   ||   &       MCR0    MCR1     MCR2    XX       XX
   *     reset          tab      super   shift    delete    ctrl  || space     fn       fn      alt     =        =
   */
  [_LW] = LAYOUT( /* [> LOWER <] */
    KC_F1,             KC_F2,   KC_F3,   KC_F4,   KC_F5,                     _______, _______, _______, _______, _______,
    KC_F6,             KC_F7,   KC_F8,   KC_F9,   KC_F10,                    _______, _______, _______, _______, _______,
    KC_F11,            KC_F12,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   _______, MCR0,    MCR1,    MCR2,    _______, _______,
    RESET,             _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ )
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  bool result = false;
  switch (keycode) {
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
