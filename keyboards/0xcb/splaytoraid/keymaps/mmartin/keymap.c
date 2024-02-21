#include QMK_KEYBOARD_H

#include "mmartin.h"

#define LTHB1 LT(_NAV, KC_TAB)
#define LTHB2 LT(_NUM, KC_SPC)
#define RTHB1 KC_ENT
#define RTHB2 LT(_FUN, KC_BSPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_40(
    KC_NO, KC_Q,         KC_W,         KC_F,         KC_P,         KC_B,  /*  */ KC_J,  KC_L,         KC_U,         KC_Y,           KC_SCLN,      KC_NO,
    KC_NO, LGUI_T(KC_A), LALT_T(KC_R), LCTL_T(KC_S), LSFT_T(KC_T), KC_G,  /*  */ KC_M,  RSFT_T(KC_N), RCTL_T(KC_E), LALT_T(KC_I),   RGUI_T(KC_O), KC_NO,
           KC_Z,         RALT_T(KC_X), KC_C,         KC_D,         KC_V,  /*  */ KC_K,  KC_H,         KC_COMM,      RALT_T(KC_DOT), KC_SLSH,
                                       KC_NO,        LTHB1,        LTHB2, KC_NO, RTHB1, RTHB2,        KC_NO
    ),
    [_NAV] = LAYOUT_40(
    KC_NO, KC_NO,   KC_NO,      KC_NO,      KC_NO,      KC_NO,   /*  */ KC_NO,       KC_LBRC, KC_RBRC, KC_NO,   KC_NO,   KC_NO,
    KC_NO, KC_LGUI, KC_LALT,    KC_LCTL,    KC_LSFT,    KC_NO,   /*  */ TD(TD_CAPS), KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_NO,
           KC_NO,   LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), KC_BTN3, /*  */ KC_INS,      KC_HOME, KC_PGDN, KC_PGUP, KC_END,
                                KC_NO,      KC_NO,      KC_TRNS, KC_NO, KC_DEL,      KC_BSPC, KC_NO
    ),
    [_NUM] = LAYOUT_40(
    KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   /*  */ KC_MINS, KC_7,    KC_8,   KC_9, KC_BSLS, KC_NO,
    KC_NO, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_NO,   /*  */ KC_LPRN, KC_4,    KC_5,   KC_6, KC_RPRN, KC_NO,
           KC_NO,   KC_RALT, KC_NO,   KC_NO,   KC_NO,   /*  */ KC_0,    KC_1,    KC_2,   KC_3, KC_EQL,
                             KC_NO,   KC_NO,   KC_TRNS, KC_NO, KC_QUOT, KC_BSPC, KC_NO
    ),
    [_FUN] = LAYOUT_40(
    KC_NO, KC_F12, KC_F7, KC_F8, KC_F9,  KC_NO,        /*  */ KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    KC_NO, KC_F11, KC_F4, KC_F5, KC_F6,  KC_NO,        /*  */ KC_NO, KC_RSFT, KC_RCTL, KC_LALT, KC_RGUI, KC_NO,
           KC_F10, KC_F1, KC_F2, KC_F3,  KC_NO,        /*  */ KC_NO, KC_NO,   KC_NO,   KC_RALT, KC_NO,
                           KC_NO, KC_ESC, MO(_DANGER), KC_NO, KC_NO, KC_TRNS, KC_NO
    ),
    [_DANGER] = LAYOUT_40(
    KC_NO, QK_BOOTLOADER, KC_NO, KC_NO, KC_NO, KC_NO, /*  */ KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    KC_NO, KC_NO,         KC_NO, KC_NO, KC_NO, KC_NO, /*  */ KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
           KC_NO,         KC_NO, KC_NO, KC_NO, KC_NO, /*  */ KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                                 KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
    ),
};

bool is_left(keyrecord_t *record) {
    return (record->event.key.col == 0 && record->event.key.row == 1)
        || (record->event.key.col == 0 && record->event.key.row == 3)
        || (record->event.key.col == 0 && record->event.key.row == 5)
        || (record->event.key.col == 0 && record->event.key.row == 7)
        || (record->event.key.col == 1 && record->event.key.row == 0)
        || (record->event.key.col == 1 && record->event.key.row == 1)
        || (record->event.key.col == 1 && record->event.key.row == 2)
        || (record->event.key.col == 1 && record->event.key.row == 3)
        || (record->event.key.col == 1 && record->event.key.row == 4)
        || (record->event.key.col == 1 && record->event.key.row == 5)
        || (record->event.key.col == 1 && record->event.key.row == 6)
        || (record->event.key.col == 1 && record->event.key.row == 7)
        || (record->event.key.col == 2 && record->event.key.row == 0)
        || (record->event.key.col == 2 && record->event.key.row == 1)
        || (record->event.key.col == 2 && record->event.key.row == 2)
        || (record->event.key.col == 2 && record->event.key.row == 3)
        || (record->event.key.col == 2 && record->event.key.row == 4)
        || (record->event.key.col == 2 && record->event.key.row == 6)
        || (record->event.key.col == 3 && record->event.key.row == 1)
        || (record->event.key.col == 3 && record->event.key.row == 3);
}

bool is_thumb(keyrecord_t *record) {
    return (record->event.key.col == 1 && record->event.key.row == 6)
        || (record->event.key.col == 2 && record->event.key.row == 6)
        || (record->event.key.col == 3 && record->event.key.row == 3)
        || (record->event.key.col == 3 && record->event.key.row == 6)
        || (record->event.key.col == 3 && record->event.key.row == 7)
        || (record->event.key.col == 4 && record->event.key.row == 6);
}

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_BASE]   = { ENCODER_CCW_CW(KC_BRID, KC_BRIU) },
    [_NAV]    = { ENCODER_CCW_CW(KC_BRID, KC_BRIU) },
    [_NUM]    = { ENCODER_CCW_CW(KC_BRID, KC_BRIU) },
    [_FUN]    = { ENCODER_CCW_CW(KC_BRID, KC_BRIU) },
    [_DANGER] = { ENCODER_CCW_CW(KC_BRID, KC_BRIU) },
};
