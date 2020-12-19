#include QMK_KEYBOARD_H


#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
rgblight_config_t RGB_current_config;
#endif

enum layer_number {
    _QWERTY = 0,
    _ADJUST
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  ADJUST,
  RGBRST
};

// Fillers to make layering more clear
#define EISU LALT(KC_GRV)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  // keycodes
  //  

  [_QWERTY] = LAYOUT(
      _______, _______,   KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,       KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS,
      _______, _______,   KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,
      _______, _______,   KC_LGUI, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,       KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,  KC_ENT,
      _______, _______,   KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,       KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   ADJUST,
      _______, _______,   KC_LALT, KC_LALT, KC_LCTL, KC_LCTL, KC_SPC,  KC_SPC,     KC_SPC,  KC_SPC,  KC_RCTL, KC_RCTL, KC_RALT, KC_LEFT, KC_DOWN, KC_RGHT
      ),

  [_ADJUST] =  LAYOUT(
      _______, _______,   KC_ESC,  KC_F1,     KC_F2,       KC_F3,    KC_F4,   KC_F5,      KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_INSERT,
      _______, _______,   KC_TAB,  _______,   _______,     _______,  _______, _______,    _______, _______, _______, _______, _______, KC_UP,   _______, _______,
      _______, _______,   KC_LGUI, KC__VOLUP, KC__VOLDOWN, KC__MUTE, _______, _______,    _______, _______, _______, _______, KC_LEFT, KC_RGHT, _______, _______,
      _______, _______,   KC_LSFT, _______,   _______,     _______,  _______, _______,    _______, _______, _______, _______, _______, KC_DOWN, _______, _______,
      _______, _______,   KC_LALT, KC_LALT,   KC_LCTL,     _______,  _______, _______,    _______, _______, _______, KC_RCTL, KC_RALT, _______, _______, _______
      )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
      case QWERTY:
        if (record->event.pressed) {
           print("mode just switched to qwerty and this is a huge string\n");
          set_single_persistent_default_layer(_QWERTY);
        }
        break;

      case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        break;

      case RGBRST:
        #ifdef RGBLIGHT_ENABLE
          if (record->event.pressed) {
            eeconfig_update_rgblight_default();
            rgblight_enable();
            RGB_current_config = rgblight_config;
          }
        #endif
        break;
  }
  return true;
}
