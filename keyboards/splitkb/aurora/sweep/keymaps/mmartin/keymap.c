#include QMK_KEYBOARD_H

#include "features/achordion.h"

enum Layouts {
    _BASE = 0,
    _NAV,
    _NUM,
    _FUN,
    _DANGER,
};

const key_override_t shift_lprn = ko_make_basic(MOD_MASK_SHIFT, KC_LPRN, KC_LCBR);
const key_override_t shift_rprn = ko_make_basic(MOD_MASK_SHIFT, KC_RPRN, KC_RCBR);
const key_override_t shift_0    = ko_make_basic(MOD_MASK_SHIFT, KC_0,    KC_TILD);
const key_override_t shift_9    = ko_make_basic(MOD_MASK_SHIFT, KC_9,    KC_GRV);

const key_override_t **key_overrides = (const key_override_t *[]) {
    &shift_lprn,
    &shift_rprn,
    &shift_0,
    &shift_9,
    NULL
};

#define LTHB1 LT(_NAV, KC_TAB)
#define LTHB2 LT(_NUM, KC_SPC)
#define RTHB1 KC_ENT
#define RTHB2 LT(_FUN, KC_BSPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        KC_Q,         KC_W,         KC_F,         KC_P,         KC_B,  /**/ KC_J,  KC_L,         KC_U,         KC_Y,           KC_SCLN,
        LGUI_T(KC_A), LALT_T(KC_R), LCTL_T(KC_S), LSFT_T(KC_T), KC_G,  /**/ KC_M,  RSFT_T(KC_N), RCTL_T(KC_E), LALT_T(KC_I),   RGUI_T(KC_O),
        KC_Z,         RALT_T(KC_X), KC_C,         KC_D,         KC_V,  /**/ KC_K,  KC_H,         KC_COMM,      RALT_T(KC_DOT), KC_SLSH,
                                                  LTHB1,        LTHB2, /**/ RTHB1, RTHB2
    ),
    [_NAV] = LAYOUT(
        KC_NO,   KC_NO,      KC_NO,      KC_NO,      KC_NO,   /**/ KC_NO,   KC_LBRC, KC_RBRC, KC_NO,   KC_NO,
        KC_LGUI, KC_LALT,    KC_LCTL,    KC_LSFT,    KC_NO,   /**/ KC_CAPS, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,
        KC_NO,   LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), KC_BTN3, /**/ KC_INS,  KC_HOME, KC_PGDN, KC_PGUP, KC_END,
                                         KC_TRNS,    KC_NO,   /**/ KC_DEL,  KC_BSPC
    ),
    [_NUM] = LAYOUT(
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   /**/ KC_MINS, KC_7,   KC_8,   KC_9, KC_BSLS,
        KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_NO,   /**/ KC_LPRN, KC_4,   KC_5,   KC_6, KC_RPRN,
        KC_NO,   KC_RALT, KC_NO,   KC_NO,   KC_NO,   /**/ KC_0,    KC_1,   KC_2,   KC_3, KC_EQL,
                                   KC_NO,   KC_TRNS, /**/ KC_QUOT, KC_BSPC
    ),
    [_FUN] = LAYOUT(
        KC_F12, KC_F7, KC_F8, KC_F9,  KC_NO,       /**/ KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_F11, KC_F4, KC_F5, KC_F6,  KC_NO,       /**/ KC_NO, KC_RSFT, KC_RCTL, KC_LALT, KC_RGUI,
        KC_F10, KC_F1, KC_F2, KC_F3,  KC_NO,       /**/ KC_NO, KC_NO,   KC_NO,   KC_RALT, KC_NO,
                              KC_ESC, MO(_DANGER), /**/ KC_NO, KC_TRNS
    ),
    [_DANGER] = LAYOUT(
        QK_BOOTLOADER, KC_NO, KC_NO, KC_NO, KC_NO, /**/ KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO,         KC_NO, KC_NO, KC_NO, KC_NO, /**/ KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO,         KC_NO, KC_NO, KC_NO, KC_NO, /**/ KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                                     KC_NO, KC_NO, /**/ KC_NO, KC_NO
    ),
};

void matrix_scan_user(void) {
  achordion_task();
}

bool is_left(keyrecord_t *record) {
  return record->event.key.row < MATRIX_ROWS / 2;
}

bool is_thumb(keyrecord_t *record) {
    return record->event.key.row % (MATRIX_ROWS / 2) >= 3;
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LGUI_T(KC_A):
        case LALT_T(KC_R):
        case RALT_T(KC_X):
        case LCTL_T(KC_S):
        case LSFT_T(KC_T):
            if (get_mods() & MOD_BIT(KC_RSFT)) { return 42069; }
            break;

        case RGUI_T(KC_O):
        case LALT_T(KC_I):
        case RALT_T(KC_DOT):
        case RCTL_T(KC_E):
        case RSFT_T(KC_N):
            if (get_mods() & MOD_BIT(KC_LSFT)) { return 42069; }
            break;
    }

    if (keycode == LSFT_T(KC_T) || keycode == RSFT_T(KC_N)) { return 169; }

    if (is_thumb(record)) { return 350; }

    return TAPPING_TERM;
}

bool achordion_chord(uint16_t tap_hold_keycode, keyrecord_t *tap_hold_record,
                     uint16_t other_keycode, keyrecord_t *other_record) {
    if (tap_hold_keycode == LT(_NAV, KC_TAB)) { return true; }
    if (is_thumb(other_record)) { return true; }
    return is_left(tap_hold_record) != is_left(other_record);
}

uint16_t achordion_timeout(uint16_t tap_hold_keycode) {
    switch (tap_hold_keycode) {
        case LT(_NAV, KC_TAB):
        case LT(_NUM, KC_SPC):
        case LT(_FUN, KC_BSPC):
            return 0;
    }
    return 1000;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_achordion(keycode, record)) { return false; }
    return true;
};

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    if (keycode == LT(_NAV, KC_TAB)) { return true; }
    return false;
}

void keyboard_post_init_user(void) {
    setPinOutput(24);
    writePinHigh(24);

#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv(200, 69, 13);
#endif
}
