// RAMA WORKS KARA — layers mirror the VIA backup rama_works_kara.layout.json.
// Home row mods on S/D/F and J/K/L, plus Shift mod-taps on A and ; (new, to try).
// Fn is TL_LOWR (VIA's "FN_MO13"): hold Fn + Space for the RGB layer.

#include QMK_KEYBOARD_H
#include "keyboards/wilba_tech/wt_rgb_backlight.h"

enum layers {
    _BASE,
    _FN,
    _NAV,
    _RGB,
};

// Ripple brightness floor, on 9 / 0 of the RGB layer (next to the brightness max on - / =)
enum custom_keycodes {
    RIP_MIN_DEC = QK_USER,
    RIP_MIN_INC,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RIP_MIN_DEC:
            if (record->event.pressed) backlight_ripple_min_step(-1);
            return false;
        case RIP_MIN_INC:
            if (record->event.pressed) backlight_ripple_min_step(1);
            return false;
    }
    return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_60_hhkb(
        KC_ESC,         KC_1,          KC_2,          KC_3,          KC_4,          KC_5,    KC_6,    KC_7,          KC_8,          KC_9,          KC_0,          KC_MINS, KC_EQL,  KC_BSLS, KC_DEL,
        KC_TAB,         KC_Q,          KC_W,          KC_E,          KC_R,          KC_T,    KC_Y,    KC_U,          KC_I,          KC_O,          KC_P,          KC_LBRC, KC_RBRC, KC_BSPC,
        HYPR_T(KC_ESC), LSFT_T(KC_A),  LCTL_T(KC_S),  LALT_T(KC_D),  LGUI_T(KC_F),  KC_G,    KC_H,    RGUI_T(KC_J),  RALT_T(KC_K),  RCTL_T(KC_L),  RSFT_T(KC_SCLN), KC_QUOT, HYPR_T(KC_ENT),
        KC_LSFT,                       KC_Z,          KC_X,          KC_C,          KC_V,    KC_B,    KC_N,          KC_M,          KC_COMM,       KC_DOT,        KC_SLSH, KC_RSFT, TL_LOWR,
                        KC_LALT,       KC_LGUI,                                     LT(_NAV, KC_SPC),                                              KC_RGUI,       KC_RCTL
    ),

    [_FN] = LAYOUT_60_hhkb(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_INS,  KC_DEL,
        KC_CAPS, NK_TOGG, _______, _______, _______, _______, _______, _______, KC_PSCR, KC_SCRL, KC_PAUS, KC_UP,   _______, _______,
        _______, KC_VOLD, KC_VOLU, KC_MUTE, KC_EJCT, _______, KC_PAST, KC_PSLS, KC_HOME, KC_PGUP, KC_LEFT, KC_RGHT, _______,
        _______,          _______, _______, _______, _______, _______, KC_PPLS, KC_PMNS, KC_END,  KC_PGDN, KC_DOWN, _______, _______,
                 _______, _______,                            _______,                            _______, _______
    ),

    [_NAV] = LAYOUT_60_hhkb(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        QK_MACRO_0, KC_HOME, KC_UP, KC_END, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        KC_ENT,  KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        KC_BSPC,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                 _______, _______,                            _______,                            _______, _______
    ),

    [_RGB] = LAYOUT_60_hhkb(
        _______, EF_DEC,  EF_INC,  H1_DEC,  H1_INC,  H2_DEC,  H2_INC,  _______, _______, RIP_MIN_DEC, RIP_MIN_INC, BR_DEC,  BR_INC,  _______, _______,
        _______, _______, _______, S1_DEC,  S1_INC,  S2_DEC,  S2_INC,  _______, _______, _______, _______, ES_DEC,  ES_INC,  _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                 _______, _______,                            _______,                            _______, _______
    ),
};
