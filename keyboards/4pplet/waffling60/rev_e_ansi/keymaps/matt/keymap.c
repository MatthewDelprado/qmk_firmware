/*
 * Waffling60 Rev E ANSI — ported from ~/qmk_firmware_06082023 (commit 0994d6b5df),
 * which edited the default keymap directly. Layers synced from the VIA backup
 * waffling60_rev_e_ansi.layout.json in this folder (via_to_keymap.py converts it).
 *
 * Esc on tap, Hyper on hold (no Grave): row 0 first key + row 2 first key (Caps position).
 * Grave: use Karabiner or set another key to KC_GRV in VIA.
 */
#include QMK_KEYBOARD_H

enum layer_names {
    _BASE,
    _FN,
    _FN2,
    _FN3,
};

enum custom_keycodes {
    LED_CAL = QK_USER, /* Fn+Z: map underglow LED positions (see ripple section below) */
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Layer 0: Base — synced from VIA waffling60_rev_e_ansi.layout-v3.json */
    [_BASE] = LAYOUT_all(
        /* Row 0: Esc/Hyper, 1–\, BSPC */
        HYPR_T(KC_ESC), KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSLS, KC_BSPC,
        /* Row 1: Tab, Q–], \ */
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
        /* Row 2: Caps/Hyper, A–', Enter */
        HYPR_T(KC_ESC), KC_A, LCTL_T(KC_S), LALT_T(KC_D), LGUI_T(KC_F), KC_G, KC_H, MT(MOD_LGUI | MOD_RGUI, KC_J), MT(MOD_LALT | MOD_RALT, KC_K), MT(MOD_LCTL | MOD_RCTL, KC_L), KC_SCLN, KC_QUOT, HYPR_T(KC_ENT),
        /* Row 3: Shift, Z–/, Up, MO(1) */
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, MT(MOD_LSFT | MOD_RSFT, KC_UP), MO(1),
        /* Row 4: bottom row — split spacebar */
        KC_LCTL, KC_LALT, KC_LGUI, LT(1, KC_SPC), LT(1, KC_ENT), LT(2, KC_SPC), MT(MOD_LGUI | MOD_RGUI, KC_LEFT), MT(MOD_LALT | MOD_RALT, KC_DOWN), MT(MOD_LCTL | MOD_RCTL, KC_RGHT)
    ),

    /* Layer 1: Fn — synced from VIA waffling60_rev_e_ansi.layout-v3.json */
    [_FN] = LAYOUT_all(
        /* Row 0: Esc/Hyper, 1–\, BSPC */
        QK_BOOT, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, _______, _______,
        /* Row 1: Tab, Q–], \ — Home/Up/End cluster + [ = Up (right-hand) */
        _______, KC_HOME, KC_UP, KC_END, _______, _______, _______, _______, _______, _______, _______, KC_UP,   _______, _______,
        /* Row 2: Caps/Hyper, A–', Enter — ASD = left-hand arrows, ;' = Left/Right (right-hand) */
        _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, _______, _______, _______, KC_LEFT, KC_RGHT, KC_MPLY,
        /* Row 3: Shift, Z–/, Up, MO(1) — Z = LED calibration, / = Down (right-hand) */
        _______, LED_CAL, _______, _______, _______, _______, _______, _______, _______, _______, KC_DOWN, KC_VOLU, _______,
        /* Row 4: bottom row */
        _______, _______, _______, _______, _______, KC_BSPC, KC_MPRV, KC_VOLD, KC_MNXT
    ),

    /* Layer 2: numrow on Q-P, arrows on A-S-D and H-J-K-L — synced from VIA */
    [_FN2] = LAYOUT_all(
        /* Row 0: Esc/Hyper, 1–\, BSPC */
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        /* Row 1: Tab, Q–], \ */
        _______, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, _______,
        /* Row 2: Caps/Hyper, A–', Enter */
        _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, _______, _______, _______,
        /* Row 3: Shift, Z–/, Up, MO(1) */
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        /* Row 4: bottom row */
        _______, _______, _______, KC_BSPC, _______, _______, _______, _______, _______
    ),

    /* Layer 3: unused — synced from VIA */
    [_FN3] = LAYOUT_all(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_FN]   = { ENCODER_CCW_CW(KC_BRID, KC_BRIU) },
    [_FN2]  = { ENCODER_CCW_CW(_______, _______) },
    [_FN3]  = { ENCODER_CCW_CW(_______, _______) },
};
#endif

/* Hold-on-other-key only for arrow mod-taps (Shift+Up etc.), not home row or spacebar */
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    if (keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) {
        uint16_t tap_key = QK_MOD_TAP_GET_TAP_KEYCODE(keycode);
        /* Only arrow keys: immediate mod when another key is pressed */
        if (tap_key == KC_UP || tap_key == KC_DOWN || tap_key == KC_LEFT || tap_key == KC_RGHT) {
            return true;
        }
    }
    /* Home row mods (S, D, F, J, K, L) and spacebar mod-tap: normal tap-hold */
    return false;
}

/* Give home-row mod-taps more time to qualify as taps.
 * This reduces accidental modifier activations when you roll into Space. */
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    (void)record;
    switch (keycode) {
        case LCTL_T(KC_S):
        case LALT_T(KC_D):
        case LGUI_T(KC_F):
        case MT(MOD_LGUI | MOD_RGUI,KC_J):
        case MT(MOD_LALT | MOD_RALT,KC_K):
        case MT(MOD_LCTL | MOD_RCTL,KC_L):
            return TAPPING_TERM + 50;
        default:
            return TAPPING_TERM;
    }
}


/* ---------------------------------------------------------------------------
 * Underglow (17 LEDs, drawn directly instead of through an rgblight mode)
 *
 *   _BASE  teal ripples    every keypress sends a ring of light out from that key;
 *   _FN    plum ripples    rings fade as they grow and add up where they overlap
 *   _FN2   static rainbow  hue follows each LED's left→right position
 *   _FN3   solid blue
 *
 * Positions are in quarter-key units: x 0–60 left→right, y 0–20 top→bottom.
 * ------------------------------------------------------------------------- */

#define RIPPLE_MAX      10   /* rings alive at once; a new press replaces the oldest */
#define RIPPLE_SPEED    80   /* ring growth, quarter-keys per second (20 keys/s) */
#define RIPPLE_WIDTH    10   /* ring thickness, quarter-keys */
#define RIPPLE_LIFE_MS  1000 /* ring fully faded after this */
#define FRAME_MS        16

/* Background (dim) and ring crest (bright) colour per ripple layer */
static const hsv_t ripple_bg[]    = {[_BASE] = {125, 255, 50}, [_FN] = {200, 255, 50}};
static const hsv_t ripple_crest[] = {[_BASE] = {125, 200, 255}, [_FN] = {200, 220, 255}};

/* Centre of each matrix position, from LAYOUT_all in keyboard.json; {255, 255} = no key */
static const uint8_t key_pos[MATRIX_ROWS][MATRIX_COLS][2] = {
    {{2, 2}, {6, 2}, {10, 2}, {14, 2}, {18, 2}, {22, 2}, {26, 2}, {30, 2}, {34, 2}, {38, 2}, {42, 2}, {46, 2}, {50, 2}, {54, 2}},
    {{3, 6}, {8, 6}, {12, 6}, {16, 6}, {20, 6}, {24, 6}, {28, 6}, {32, 6}, {36, 6}, {40, 6}, {44, 6}, {48, 6}, {52, 6}, {58, 2}},
    {{4, 10}, {9, 10}, {13, 10}, {17, 10}, {21, 10}, {25, 10}, {29, 10}, {33, 10}, {37, 10}, {41, 10}, {45, 10}, {49, 10}, {57, 6}, {56, 10}},
    {{4, 14}, {255, 255}, {11, 14}, {15, 14}, {19, 14}, {23, 14}, {27, 14}, {31, 14}, {35, 14}, {39, 14}, {43, 14}, {47, 14}, {52, 14}, {58, 14}},
    {{3, 18}, {8, 18}, {13, 18}, {255, 255}, {22, 18}, {255, 255}, {30, 18}, {255, 255}, {38, 18}, {255, 255}, {255, 255}, {47, 18}, {52, 18}, {57, 18}},
};

/* Where each underglow LED sits. PLACEHOLDER — evenly spaced along the middle until
 * the real positions are known. Replace with the table LED_CAL types out.
 * {255, 255} = LED not visible; it is kept dark. */
static uint8_t led_pos[RGBLIGHT_LED_COUNT][2] = {
    {2, 10}, {5, 10}, {9, 10}, {12, 10}, {16, 10}, {19, 10}, {23, 10}, {26, 10}, {30, 10},
    {33, 10}, {37, 10}, {40, 10}, {44, 10}, {47, 10}, {51, 10}, {54, 10}, {58, 10},
};

typedef struct {
    bool     active;
    uint16_t start;
    uint8_t  dist[RGBLIGHT_LED_COUNT]; /* key → LED distance, worked out once at press time */
} ripple_t;

static ripple_t ripples[RIPPLE_MAX];
static uint8_t  ripple_next;
static bool     ripples_running; /* frames still need drawing */
static int8_t   cal_led = -1;    /* LED being calibrated, -1 = not calibrating */

static uint8_t isqrt(uint16_t n) {
    uint8_t r = 0;
    while ((uint16_t)(r + 1) * (r + 1) <= n) r++;
    return r;
}

static void ripple_start(uint8_t row, uint8_t col) {
    const uint8_t *k = key_pos[row][col];
    if (k[0] == 255) return;
    ripple_t *r = &ripples[ripple_next];
    ripple_next = (ripple_next + 1) % RIPPLE_MAX;
    for (uint8_t i = 0; i < RGBLIGHT_LED_COUNT; i++) {
        int16_t dx = led_pos[i][0] - k[0];
        int16_t dy = led_pos[i][1] - k[1];
        r->dist[i] = led_pos[i][0] == 255 ? 255 : isqrt(dx * dx + dy * dy);
    }
    r->start        = timer_read();
    r->active       = true;
    ripples_running = true;
}

/* Draws one frame for a ripple layer. Returns false once every ring has faded
 * (that last frame is plain background, so drawing can stop). */
static bool ripple_draw(uint8_t layer) {
    uint16_t level[RGBLIGHT_LED_COUNT] = {0};
    bool     any                       = false;

    for (uint8_t n = 0; n < RIPPLE_MAX; n++) {
        ripple_t *r = &ripples[n];
        if (!r->active) continue;
        uint16_t age = timer_elapsed(r->start);
        if (age >= RIPPLE_LIFE_MS) {
            r->active = false;
            continue;
        }
        any             = true;
        uint16_t radius = (uint32_t)age * RIPPLE_SPEED / 1000;
        uint16_t fade   = 255 - (uint32_t)age * 255 / RIPPLE_LIFE_MS;
        fade            = fade * fade / 255; /* ease out */
        for (uint8_t i = 0; i < RGBLIGHT_LED_COUNT; i++) {
            uint16_t off = abs((int16_t)r->dist[i] - (int16_t)radius);
            if (off < RIPPLE_WIDTH) level[i] += (RIPPLE_WIDTH - off) * fade / RIPPLE_WIDTH;
        }
    }

    rgb_t bg    = hsv_to_rgb(ripple_bg[layer]);
    rgb_t crest = hsv_to_rgb(ripple_crest[layer]);
    for (uint8_t i = 0; i < RGBLIGHT_LED_COUNT; i++) {
        if (led_pos[i][0] == 255) {
            rgblight_driver.set_color(i, 0, 0, 0);
            continue;
        }
        uint16_t l = MIN(level[i], 255); /* overlapping rings add up, capped at full crest */
        rgblight_driver.set_color(i, bg.r + (crest.r - bg.r) * l / 255, bg.g + (crest.g - bg.g) * l / 255, bg.b + (crest.b - bg.b) * l / 255);
    }
    rgblight_driver.flush();
    return any;
}

static void rainbow_draw(void) {
    for (uint8_t i = 0; i < RGBLIGHT_LED_COUNT; i++) {
        if (led_pos[i][0] == 255) {
            rgblight_driver.set_color(i, 0, 0, 0);
            continue;
        }
        rgb_t c = hsv_to_rgb((hsv_t){led_pos[i][0] * 230 / 60, 255, 255}); /* red → magenta, not wrapping to red */
        rgblight_driver.set_color(i, c.r, c.g, c.b);
    }
    rgblight_driver.flush();
}

static void cal_draw(void) {
    for (uint8_t i = 0; i < RGBLIGHT_LED_COUNT; i++) {
        uint8_t v = i == cal_led ? 255 : 0;
        rgblight_driver.set_color(i, v, v, v);
    }
    rgblight_driver.flush();
}

static void underglow_refresh(layer_state_t state) {
    if (cal_led >= 0 || !rgblight_is_enabled()) return;
    uint8_t layer = get_highest_layer(state);
    /* Keep rgblight itself in a still mode so it never animates over our drawing */
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
    switch (layer) {
        case _BASE:
        case _FN:
            ripples_running = ripple_draw(layer);
            break;
        case _FN2:
            rainbow_draw();
            break;
        default:
            rgblight_sethsv_noeeprom(170, 255, 255); /* blue */
            break;
    }
}

/* Types the calibrated table so it can be pasted over led_pos above */
static void send_u8(uint8_t v) {
    char buf[4];
    char *p = buf + sizeof(buf) - 1;
    *p      = '\0';
    do {
        *--p = '0' + v % 10;
        v /= 10;
    } while (v);
    send_string(p);
}

static void cal_finish(void) {
    cal_led = -1;
    send_string("led_pos = {");
    for (uint8_t i = 0; i < RGBLIGHT_LED_COUNT; i++) {
        send_string("{");
        send_u8(led_pos[i][0]);
        send_string(", ");
        send_u8(led_pos[i][1]);
        send_string(i < RGBLIGHT_LED_COUNT - 1 ? "}, " : "}};\n");
    }
    underglow_refresh(layer_state);
}

/* LED_CAL: lights one LED at a time. Press the key closest to the lit LED to record
 * its position, or the Fn key if you can't see it. After the last LED the finished
 * table is typed out (have a text editor focused). New positions apply straight away
 * but are lost on unplug until pasted into led_pos. */
static void cal_key(uint8_t row, uint8_t col) {
    if (row == 3 && col == 13) { /* Fn key = LED not visible */
        led_pos[cal_led][0] = led_pos[cal_led][1] = 255;
    } else if (key_pos[row][col][0] != 255) {
        led_pos[cal_led][0] = key_pos[row][col][0];
        led_pos[cal_led][1] = key_pos[row][col][1];
    }
    if (++cal_led >= RGBLIGHT_LED_COUNT) {
        cal_finish();
    } else {
        cal_draw();
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode == LED_CAL) {
        if (!record->event.pressed) { /* start on release so this press isn't recorded */
            cal_led = 0;
            cal_draw();
        }
        return false;
    }
    /* While calibrating, swallow keys (their positions are read from the matrix
     * in housekeeping) but let MO(1) through so the Fn layer can't get stuck. */
    return cal_led < 0 || keycode == MO(1);
}

/* Reads raw matrix presses instead of process_record so ripples start the instant a
 * key goes down, even on mod-taps that wait for the tapping term. */
void housekeeping_task_user(void) {
    static matrix_row_t prev[MATRIX_ROWS];
    static uint16_t     last_frame;
    uint8_t             layer = get_highest_layer(layer_state);

    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        matrix_row_t now     = matrix_get_row(row);
        matrix_row_t pressed = now & ~prev[row];
        prev[row]            = now;
        for (uint8_t col = 0; pressed && col < MATRIX_COLS; col++, pressed >>= 1) {
            if (!(pressed & 1)) continue;
            if (cal_led >= 0) {
                cal_key(row, col);
            } else if (layer == _BASE || layer == _FN) {
                ripple_start(row, col);
            }
        }
    }

    if (cal_led < 0 && ripples_running && (layer == _BASE || layer == _FN) && rgblight_is_enabled() && timer_elapsed(last_frame) >= FRAME_MS) {
        last_frame      = timer_read();
        ripples_running = ripple_draw(layer);
    }
}

void keyboard_post_init_user(void) {
    underglow_refresh(layer_state); /* also stops the boot-time red flash */
}

layer_state_t layer_state_set_user(layer_state_t state) {
    underglow_refresh(state);
    return state;
}
