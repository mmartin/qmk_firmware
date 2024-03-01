#include "mmartin.h"

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

void matrix_scan_user(void) {
  achordion_task();
}

void td_caps(tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1:
            if (host_keyboard_led_state().caps_lock) {
                tap_code(KC_CAPS);
            } else {
                caps_word_toggle();
            }
            return;

        case 2:
            tap_code(KC_CAPS);
            return;
    }
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_CAPS] = ACTION_TAP_DANCE_FN(td_caps),
};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TD(TD_CAPS):
            return 200;

        case LGUI_T(KC_A):
        case LALT_T(KC_R):
        case RALT_T(KC_X):
        case LCTL_T(KC_S):
        case LSFT_T(KC_T):
            if ((get_oneshot_mods() | get_mods()) & MOD_BIT(KC_RSFT)) { return 42069; }
            break;

        case RGUI_T(KC_O):
        case LALT_T(KC_I):
        case RALT_T(KC_DOT):
        case RCTL_T(KC_E):
        case RSFT_T(KC_N):
            if ((get_oneshot_mods() | get_mods()) & MOD_BIT(KC_LSFT)) { return 42069; }
            break;
    }

    if (keycode == LSFT_T(KC_T) || keycode == RSFT_T(KC_N)) { return 180; }

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
    return 10000;
}

bool achordion_eager_mod(uint8_t mod) {
    switch (mod) {
        case MOD_LGUI:
        case MOD_LSFT:
        case MOD_RSFT:
        case MOD_LCTL:
        case MOD_RCTL:
            return true;
    }
    return false;
}

uint8_t mod5_to_mod8(uint8_t mods) {
    return ((mods & 0b10000) == 0) ? mods : (mods << 4);
}

static uint8_t magic_mod = 0;
static uint8_t magic_mod_time = 0;
static keyrecord_t magic_mod_record = { 0 };
static bool magic_mod_tap = false;

static bool oneshot_mod_tap(uint16_t keycode, keyrecord_t *record) {
    uint8_t key_mod = mod5_to_mod8(mod_config(QK_MOD_TAP_GET_MODS(keycode)));
    uint8_t mods = get_mods() & ~key_mod;

    if (record->tap.count == 0) {
        if (record->event.pressed && !mods && !magic_mod) {
            add_oneshot_mods(key_mod);

            magic_mod = key_mod;
            magic_mod_time = record->event.time;
            magic_mod_tap = false;

            return false;
        } else if (!record->event.pressed && magic_mod) {
            magic_mod = 0;

            if (timer_elapsed(record->event.time) > 300) {
                del_oneshot_mods(key_mod);
            }
        }
    }

    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_achordion(keycode, record)) { return false; }

    switch (keycode) {
        case LSFT_T(KC_T):
        case RSFT_T(KC_N):
            if (!oneshot_mod_tap(keycode, record)) { return false; }
    }

    bool is_tappable = IS_QK_BASIC(keycode)
        || (IS_QK_MOD_TAP(keycode) && record->tap.count)
        || (IS_QK_LAYER_TAP(keycode) && record->tap.count);

    if (is_tappable) {
        if (magic_mod) {
            if (record->event.pressed && !get_oneshot_mods()) {
                magic_mod_record = *record;
                magic_mod_tap = true;
                return false;
            } else if (!record->event.pressed && magic_mod_tap) {
                add_mods(magic_mod);
                magic_mod = 0;
                process_record(&magic_mod_record);
                magic_mod_tap = 0;
            }
        } else if (magic_mod_tap && !record->event.pressed) {
            magic_mod_tap = false;
            process_record(&magic_mod_record);
        }
    } else if ((IS_QK_MOD_TAP(keycode) || IS_QK_LAYER_TAP(keycode))
                && magic_mod == get_oneshot_mods()
                && record->tap.count == 0 && record->event.pressed) {
        del_oneshot_mods(magic_mod);
        add_mods(magic_mod);
        magic_mod = 0;
    }

    return true;
};

#ifdef RGB_MATRIX_ENABLE
void oneshot_mods_changed_user(uint8_t mods) {
    if (mods) {
        rgb_matrix_sethsv(0, 255, rgb_matrix_get_val());
    } else {
        rgb_matrix_sethsv(200, 69, rgb_matrix_get_val());
    }
}
#endif

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    if (keycode == LT(_NAV, KC_TAB)) { return true; }
    return false;
}

// Copy pasta from QMK code
bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // To work properly with tap-dance
        case TD(TD_CAPS):
            return true;

        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
        case KC_MINS:
            add_weak_mods(MOD_BIT(KC_LSFT)); // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
            return true;

        default:
            return false; // Deactivate Caps Word.
    }
}

bool led_update_user(led_t led_state) {
    bool active = led_state.caps_lock || is_caps_word_on();
    gpio_write_pin(MY_CAPS_LOCK_PIN, MY_CAPS_LOCK_STATE(active));
    return true;
}

void caps_word_set_user(bool active) {
    active |= host_keyboard_led_state().caps_lock;
    gpio_write_pin(MY_CAPS_LOCK_PIN, MY_CAPS_LOCK_STATE(active));
}

void keyboard_post_init_user(void) {
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv(200, 69, 13);
#endif

    /* debug_enable=true; */
    /* debug_keyboard=true; */

    gpio_set_pin_output(MY_CAPS_LOCK_PIN);
    gpio_write_pin(MY_CAPS_LOCK_PIN, MY_CAPS_LOCK_STATE(false));
}
