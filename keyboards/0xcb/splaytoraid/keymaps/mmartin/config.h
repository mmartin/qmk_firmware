#define DEBOUNCE 30

#define MY_CAPS_LOCK_PIN 17
#define MY_CAPS_LOCK_STATE(x) (x)

#define QUICK_TAP_TERM 69
#define TAPPING_TERM 300
#define TAPPING_TERM_PER_KEY
#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY
#define PERMISSIVE_HOLD

#define DUMMY_MOD_NEUTRALIZER_KEYCODE KC_F18
#define MODS_TO_NEUTRALIZE { MOD_BIT(KC_LEFT_GUI), MOD_BIT(KC_RIGHT_GUI), MOD_BIT(KC_LEFT_SHIFT), MOD_BIT(KC_RIGHT_SHIFT) }
