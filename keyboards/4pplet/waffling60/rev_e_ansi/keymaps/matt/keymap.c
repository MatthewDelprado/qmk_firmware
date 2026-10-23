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
 * Presets live in underglow.json; rules.mk regenerates underglow_presets.h from
 * it on every build. Each layer gets a base effect, optionally with pulses:
 *   solid    one colour
 *   rainbow  static, hue follows each LED's left→right position
 *   spin     conic gradient between two colours, slowly rotating
 *   pulse    every keypress sends a ring out from that key; rings fade as they
 *            grow and add up where they overlap
 * Changing layer ripples the new layer's colours out from the key that changed it.
 *
 * Positions are in quarter-key units: x 0–60 left→right, y 0–20 top→bottom.
 * ------------------------------------------------------------------------- */

enum { FX_SOLID, FX_RAINBOW, FX_SPIN };

typedef struct {
    uint8_t  effect;
    hsv_t    a, b;      /* solid uses a; spin blends a → b */
    uint16_t period_ms; /* spin: one full turn */
    bool     pulse;
    hsv_t    crest;     /* pulse ring colour */
} layer_fx_t;

typedef struct {
    layer_fx_t layers[4];
} underglow_preset_t;

#include "underglow_presets.h"

#define RIPPLE_MAX 10 /* rings alive at once; a new press replaces the oldest */
#define FRAME_MS   16
#define SPIN_CX    30 /* spin rotates around the middle of the board */
#define SPIN_CY    10

static const underglow_preset_t *preset = &underglow_presets[UNDERGLOW_ACTIVE_PRESET];

/* Centre of each matrix position, from LAYOUT_all in keyboard.json; {255, 255} = no key */
static const uint8_t key_pos[MATRIX_ROWS][MATRIX_COLS][2] = {
    {{2, 2}, {6, 2}, {10, 2}, {14, 2}, {18, 2}, {22, 2}, {26, 2}, {30, 2}, {34, 2}, {38, 2}, {42, 2}, {46, 2}, {50, 2}, {54, 2}},
    {{3, 6}, {8, 6}, {12, 6}, {16, 6}, {20, 6}, {24, 6}, {28, 6}, {32, 6}, {36, 6}, {40, 6}, {44, 6}, {48, 6}, {52, 6}, {58, 2}},
    {{4, 10}, {9, 10}, {13, 10}, {17, 10}, {21, 10}, {25, 10}, {29, 10}, {33, 10}, {37, 10}, {41, 10}, {45, 10}, {49, 10}, {57, 6}, {56, 10}},
    {{4, 14}, {255, 255}, {11, 14}, {15, 14}, {19, 14}, {23, 14}, {27, 14}, {31, 14}, {35, 14}, {39, 14}, {43, 14}, {47, 14}, {52, 14}, {58, 14}},
    {{3, 18}, {8, 18}, {13, 18}, {255, 255}, {22, 18}, {255, 255}, {30, 18}, {255, 255}, {38, 18}, {255, 255}, {255, 255}, {47, 18}, {52, 18}, {57, 18}},
};

/* Copied from led_positions in underglow.json at boot; LED_CAL rewrites it live.
 * {255, 255} = LED not visible; it is kept dark. */
static uint8_t led_pos[RGBLIGHT_LED_COUNT][2];
static uint8_t led_angle[RGBLIGHT_LED_COUNT]; /* around the spin centre, 0–255 = one turn */

typedef struct {
    bool     active;
    uint16_t start;
    uint8_t  dist[RGBLIGHT_LED_COUNT]; /* key → LED distance, worked out once at press time */
} ripple_t;

static ripple_t ripples[RIPPLE_MAX];
static uint8_t  ripple_next;
static bool     animating;       /* pulses or spin still need frames */
static int8_t   cal_led = -1;    /* LED being calibrated, -1 = not calibrating */

static matrix_row_t matrix_prev[MATRIX_ROWS]; /* matrix as of the last housekeeping pass */
static uint8_t      last_key[2] = {SPIN_CX, SPIN_CY};

/* Layer transition: the new layer spreads out from a key, over a snapshot of the old one */
static rgb_t    shown[RGBLIGHT_LED_COUNT]; /* what each LED shows right now */
static rgb_t    from[RGBLIGHT_LED_COUNT];  /* snapshot when the transition started */
static uint8_t  trans_dist[RGBLIGHT_LED_COUNT];
static uint16_t trans_start;
static bool     transitioning;

static uint8_t isqrt(uint16_t n) {
    uint8_t r = 0;
    while ((uint16_t)(r + 1) * (r + 1) <= n) r++;
    return r;
}

/* Cheap atan2: "diamond angle", monotonic in the true angle, 0–255 = one turn */
static uint8_t diamond_angle(int16_t dx, int16_t dy) {
    if (dx == 0 && dy == 0) return 0;
    int16_t r = (int32_t)dy * 64 / (abs(dx) + abs(dy)); /* -64..64 */
    return dx >= 0 ? (uint8_t)r : (uint8_t)(128 - r);
}

static void led_positions_changed(void) {
    for (uint8_t i = 0; i < RGBLIGHT_LED_COUNT; i++) {
        led_angle[i] = diamond_angle(led_pos[i][0] - SPIN_CX, led_pos[i][1] - SPIN_CY);
    }
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
    animating = true;
}

/* Adds up every live ring's brightness at each LED. Returns false once all have faded. */
static bool ripple_levels(uint16_t level[RGBLIGHT_LED_COUNT]) {
    bool any = false;
    for (uint8_t n = 0; n < RIPPLE_MAX; n++) {
        ripple_t *r = &ripples[n];
        if (!r->active) continue;
        uint16_t age = timer_elapsed(r->start);
        if (age >= PULSE_LIFE_MS) {
            r->active = false;
            continue;
        }
        any             = true;
        uint16_t radius = (uint32_t)age * PULSE_SPEED / 1000;
        uint16_t fade   = 255 - (uint32_t)age * 255 / PULSE_LIFE_MS;
        fade            = fade * fade / 255; /* ease out */
        for (uint8_t i = 0; i < RGBLIGHT_LED_COUNT; i++) {
            uint16_t off = abs((int16_t)r->dist[i] - (int16_t)radius);
            if (off < PULSE_WIDTH) level[i] += (PULSE_WIDTH - off) * fade / PULSE_WIDTH;
        }
    }
    return any;
}

static uint8_t lerp8(uint8_t a, uint8_t b, uint8_t t) {
    return a + ((int16_t)b - a) * t / 255;
}

static hsv_t base_color(const layer_fx_t *fx, uint8_t i, uint8_t spin_phase) {
    switch (fx->effect) {
        case FX_RAINBOW:
            return (hsv_t){led_pos[i][0] * 230 / 60, 255, fx->a.v}; /* red → magenta, not wrapping to red */
        case FX_SPIN: {
            /* t = 255 facing the gradient's colour-a side, 0 on the opposite side */
            uint8_t  d    = led_angle[i] - spin_phase;
            uint16_t away = d < 128 ? d : 256 - d; /* 0 facing colour a … 128 opposite */
            uint8_t  t    = 255 - MIN(away * 2, 255);
            return (hsv_t){lerp8(fx->b.h, fx->a.h, t), lerp8(fx->b.s, fx->a.s, t), fx->a.v};
        }
        default:
            return fx->a;
    }
}

/* Draws one frame of the current layer. Returns true while it still needs frames. */
static rgb_t blend(rgb_t a, rgb_t b, uint8_t t) {
    return (rgb_t){lerp8(a.r, b.r, t), lerp8(a.g, b.g, t), lerp8(a.b, b.b, t)};
}

static void transition_start(uint8_t x, uint8_t y) {
    if (!TRANSITION_SPEED) return; /* 0 = switch instantly */
    memcpy(from, shown, sizeof(from));
    for (uint8_t i = 0; i < RGBLIGHT_LED_COUNT; i++) {
        int16_t dx    = led_pos[i][0] - x;
        int16_t dy    = led_pos[i][1] - y;
        trans_dist[i] = led_pos[i][0] == 255 ? 0 : isqrt(dx * dx + dy * dy);
    }
    trans_start   = timer_read();
    transitioning = true;
}

static bool underglow_draw(uint8_t layer) {
    const layer_fx_t *fx = &preset->layers[MIN(layer, 3)];

    uint16_t level[RGBLIGHT_LED_COUNT] = {0};
    bool     pulsing                   = fx->pulse && ripple_levels(level);
    rgb_t    crest                     = hsv_to_rgb(fx->crest);
    uint8_t  spin_phase                = fx->effect == FX_SPIN ? timer_read32() % fx->period_ms * 256 / fx->period_ms : 0;
    uint16_t front                     = transitioning ? (uint32_t)timer_elapsed(trans_start) * TRANSITION_SPEED / 1000 : 0;
    bool     still_moving              = false;

    for (uint8_t i = 0; i < RGBLIGHT_LED_COUNT; i++) {
        rgb_t c = {0, 0, 0};
        if (led_pos[i][0] != 255) {
            uint8_t l = MIN(level[i], 255); /* overlapping rings add up, capped at full crest */
            c         = blend(hsv_to_rgb(base_color(fx, i, spin_phase)), crest, l);
        }
        if (transitioning) {
            /* Behind the front: new layer. Ahead of it: the old snapshot. A soft edge between. */
            uint16_t into = front > trans_dist[i] ? front - trans_dist[i] : 0;
            if (into < TRANSITION_WIDTH) {
                c            = blend(from[i], c, into * 255 / TRANSITION_WIDTH);
                still_moving = true;
            }
        }
        shown[i] = c;
        rgblight_driver.set_color(i, c.r, c.g, c.b);
    }
    rgblight_driver.flush();
    transitioning = still_moving;
    return pulsing || transitioning || fx->effect == FX_SPIN;
}

/* The key whose state just changed (the one that switched layer), else the last key pressed */
static void transition_origin(uint8_t *x, uint8_t *y) {
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        matrix_row_t changed = matrix_get_row(row) ^ matrix_prev[row];
        for (uint8_t col = 0; changed && col < MATRIX_COLS; col++, changed >>= 1) {
            if ((changed & 1) && key_pos[row][col][0] != 255) {
                *x = key_pos[row][col][0];
                *y = key_pos[row][col][1];
                return;
            }
        }
    }
    *x = last_key[0];
    *y = last_key[1];
}

static void cal_draw(void) {
    for (uint8_t i = 0; i < RGBLIGHT_LED_COUNT; i++) {
        uint8_t v = i == cal_led ? 255 : 0;
        rgblight_driver.set_color(i, v, v, v);
    }
    rgblight_driver.flush();
}

static void underglow_refresh(layer_state_t state) {
    static uint8_t current_layer;
    if (cal_led >= 0 || !rgblight_is_enabled()) return;
    uint8_t layer = get_highest_layer(state);
    if (layer != current_layer) {
        uint8_t x, y;
        transition_origin(&x, &y);
        transition_start(x, y);
        current_layer = layer;
    }
    /* Keep rgblight itself in a still mode so it never animates over our drawing */
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
    animating = underglow_draw(get_highest_layer(state));
}

/* Types the calibrated positions so they can be pasted over led_positions in underglow.json */
static void send_u8(uint8_t v) {
    char  buf[4];
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
    send_string("\"led_positions\": [");
    for (uint8_t i = 0; i < RGBLIGHT_LED_COUNT; i++) {
        send_string("[");
        send_u8(led_pos[i][0]);
        send_string(", ");
        send_u8(led_pos[i][1]);
        send_string(i < RGBLIGHT_LED_COUNT - 1 ? "], " : "]],\n");
    }
    led_positions_changed();
    underglow_refresh(layer_state);
}

/* LED_CAL: lights one LED at a time. Press the key closest to the lit LED to record
 * its position, or the Fn key if you can't see it. After the last LED the finished
 * list is typed out (have a text editor focused). New positions apply straight away
 * but are lost on unplug until pasted into underglow.json. */
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

/* Reads raw matrix presses instead of process_record so pulses start the instant a
 * key goes down, even on mod-taps that wait for the tapping term. */
void housekeeping_task_user(void) {
    static uint16_t     last_frame;
    uint8_t             layer = get_highest_layer(layer_state);

    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        matrix_row_t now     = matrix_get_row(row);
        matrix_row_t pressed = now & ~matrix_prev[row];
        matrix_prev[row]     = now;
        for (uint8_t col = 0; pressed && col < MATRIX_COLS; col++, pressed >>= 1) {
            if (!(pressed & 1)) continue;
            if (key_pos[row][col][0] != 255) {
                last_key[0] = key_pos[row][col][0];
                last_key[1] = key_pos[row][col][1];
            }
            if (cal_led >= 0) {
                cal_key(row, col);
            } else if (preset->layers[MIN(layer, 3)].pulse) {
                ripple_start(row, col);
            }
        }
    }

    if (cal_led < 0 && animating && rgblight_is_enabled() && timer_elapsed(last_frame) >= FRAME_MS) {
        last_frame      = timer_read();
        animating = underglow_draw(layer);
    }
}

void keyboard_post_init_user(void) {
    memcpy(led_pos, led_pos_default, sizeof(led_pos));
    led_positions_changed();
    underglow_refresh(layer_state); /* also stops the boot-time red flash */
}

layer_state_t layer_state_set_user(layer_state_t state) {
    underglow_refresh(state);
    return state;
}
