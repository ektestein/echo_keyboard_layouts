#include "ergodox_ez.h"
#include "debug.h"
#include "action_layer.h"
#include "version.h"
#include "keymap_german.h"
#include "keymap_nordic.h"
#include "keymap_french.h"
#include "keymap_spanish.h"

#define LCGS(code) LCTL(LGUI(LSFT(code)))
#define LCS(code) LCTL(LSFT(code))

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE,       // can always be here
  EPRM,
  RGB_SLD,

};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_ergodox(
    // left hand
    KC_ESC,          KC_LPRN,         KC_MINS,         KC_QUES,         KC_DQUO,         KC_RPRN,         KC_SLSH,
    KC_TAB,          KC_Y,            KC_P,            KC_O,            KC_U,            KC_J,            _______,
    KC_BSPC,         KC_I,            KC_N,            KC_E,            KC_A,            KC_COMM,
    KC_DEL,          KC_Q,            KC_Z,            KC_SCLN,         KC_DOT,          KC_GRV,          KC_APP,
    KC_P5,           KC_P7,           KC_P9,           KC_P3,           KC_P1,
                                                                                         KC_LALT,         KC_LCMD,
                                                                                                          _______,
                                                                        SFT_T(XXXXXXX),  KC_SPC,          CTL_T(XXXXXXX),
        // right hand
        KC_BSLS,         KC_SCLN,         KC_COLN,         KC_COMM,         KC_DOT,          KC_EXLM,         TO(1),
        KC_EQL,          KC_K,            KC_D,            KC_L,            KC_C,            KC_W,            KC_LBRC,
                         KC_M,            KC_H,            KC_T,            KC_S,            KC_R,            KC_QUOT,
        RALT_T(XXXXXXX), KC_B,            KC_F,            KC_G,            KC_V,            KC_X,            KC_RBRC,
        KC_P4,           KC_P8,           KC_P2,           KC_P6,           KC_P0,
        OSL(1),          KC_NLCK,
        KC_CLCK,
        RCTL_T(XXXXXXX), KC_ENT,          RSFT_T(XXXXXXX)
    ),


  [1] = LAYOUT_ergodox(
    // left hand
    KC_ESC,          KC_F1,           KC_F2,           KC_F3,           KC_F4,           KC_F5,           KC_F6,
    KC_TAB,          KC_F7,           KC_F8,           KC_F9,           KC_F10,          KC_F11,          KC_F12,
    KC_BSPC,         KC_LEFT,         KC_UP,           KC_DOWN,         KC_RGHT,         KC_ENT,
    KC_DEL,          LCTL(KC_Z),      LCTL(KC_X),      LCTL(KC_C),      LCTL(KC_V),      LCTL(KC_A),      KC_APP,
    _______,         KC_HOME,         KC_PGUP,         KC_PGDN,         KC_END,
                                                                                         ALT_T(XXXXXXX),  KC_LCMD,
                                                                                                          _______,
                                                                        SFT_T(XXXXXXX),  KC_SPC,          CTL_T(XXXXXXX),
        // right hand
        _______,         _______,         _______,         KC_0,            KC_PDOT,         KC_PSLS,         TO(0),
        KC_EQL,          _______,         KC_1,            KC_2,            KC_3,            KC_PMNS,         _______,
                         _______,         KC_4,            KC_5,            KC_6,            KC_PPLS,         _______,
        KC_ALGR,         _______,         KC_7,            KC_8,            KC_9,            KC_PAST,         _______,
        KC_LEFT,         KC_UP,           KC_DOWN,         KC_RGHT,         _______,
        _______,         KC_NLCK,
        KC_CLCK,
        KC_RCTL,         KC_ENT,          KC_RSFT
    ),


};

bool suspended = false;
const uint16_t PROGMEM fn_actions[] = {
  [1] = ACTION_LAYER_TAP_TOGGLE(1)
};

// leaving this in place for compatibilty with old keymaps cloned and re-compiled.
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
      switch(id) {
        case 0:
        if (record->event.pressed) {
          SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
        }
        break;
      }
    return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // dynamically generate these.
    case EPRM:
      if (record->event.pressed) {
        eeconfig_init();
      }
      return false;
      break;
  }
  return true;
}

uint32_t layer_state_set_user(uint32_t state) {

    uint8_t layer = biton32(state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
      case 1:
        ergodox_right_led_1_on();
        break;
      case 2:
        ergodox_right_led_2_on();
        break;
      case 3:
        ergodox_right_led_3_on();
        break;
      case 4:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        break;
      case 5:
        ergodox_right_led_1_on();
        ergodox_right_led_3_on();
        break;
      case 6:
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        break;
      case 7:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        break;
      default:
        break;
    }
    return state;

};
