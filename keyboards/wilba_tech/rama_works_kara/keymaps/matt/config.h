#pragma once

// Flow Tap: a home row mod pressed within 150 ms of the previous key is always
// a tap, so fast typing can't fire mod combos (e.g. "back " → K then Space).
#define FLOW_TAP_TERM 150

// Reactive ripple lighting. It replaces effect 10 (VIA's "Radial Color 1") so it appears in
// VIA's Effect dropdown, see wt_rgb_backlight.c. Adds a ripple_min byte to the saved
// lighting config, so the EEPROM block grows by one.
#define RGB_BACKLIGHT_RIPPLE
#define RGB_BACKLIGHT_RIPPLE_MIN 0
#undef VIA_EEPROM_CUSTOM_CONFIG_SIZE
#define VIA_EEPROM_CUSTOM_CONFIG_SIZE 32

// Start the board in the ripple: lime green at the key, shifting to hot pink as it spreads.
// (Used when the lighting EEPROM is reset, which every flash does.)
#undef RGB_BACKLIGHT_EFFECT
#define RGB_BACKLIGHT_EFFECT 10
#undef RGB_BACKLIGHT_EFFECT_SPEED
#define RGB_BACKLIGHT_EFFECT_SPEED 1
#undef RGB_BACKLIGHT_COLOR_1
#define RGB_BACKLIGHT_COLOR_1 { .h = 85, .s = 255 }
#undef RGB_BACKLIGHT_COLOR_2
#define RGB_BACKLIGHT_COLOR_2 { .h = 235, .s = 255 }
