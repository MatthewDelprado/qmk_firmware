# Rama Works Kara: home row mods and ripple lighting — 2026-10-28

Session ran 2026-10-27 → 2026-10-28 on branch `feat/kara-matt-keymap`, later merged into `fork/master` (`d75bc435a1`).

## What was built
- `keyboards/wilba_tech/rama_works_kara/keymaps/matt/` — new keymap for Matt's Rama Works KARA (HHKB layout, atmega32u4, IS31FL3731 RGB). Layers ported from his VIA export (`~/Desktop/rama_works_kara.layout.json`); `HYPR_T` on Esc and Enter, `LT(2,SPC)`, home row mods on S/D/F and J/K/L, and new Shift mod-taps on `A` and `;`. `FLOW_TAP_TERM 150`, `VIA_ENABLE`, `LTO_ENABLE`.
- `keymaps/matt_restore/` — his exact pre-flash VIA layout with no Flow Tap and no Shift mod-taps; a known-good fallback.
- Reactive ripple lighting in the shared Wilba engine (`keyboards/wilba_tech/wt_rgb_backlight.c/.h`, `_api.h`, `_keycodes.h`), gated behind `RGB_BACKLIGHT_RIPPLE`, which only the Kara `matt` config.h defines. Every key-down sends a ring out from that key; colour shifts from Color 1 (start) to Color 2 (end) with distance, brightness falls from the global max to a saved `ripple_min`, then fades. Idle LEDs rest at `ripple_min` in Color 2.
- The ripple sits in effect 10 (VIA's "Radial Color 1" slot). `ripple_min` is VIA value `0x18` and RGB-layer keys `9`/`0` (`RIP_MIN_DEC`/`RIP_MIN_INC`, after `S2_DEC` in the keycode enum).
- `keymaps/matt/rama_works_kara.via.json` — a VIA v3 draft definition showing brightness max, effect, speed, Color 1, Color 2 and ripple min. `gen_via_definition.py` rebuilds it from `keyboard.json`.
- Firmware flashed to the board with `dfu-programmer` several times; final build 23,550/28,672 bytes (`matt`) and 21,476 (`matt_restore`).

## Why
- The symptom was the one seen on the Dropbear 60 and Waffling60: fast typing fired home row mods (e.g. K then Space → Option+Space). Flow Tap 150 was chosen as on the Dropbear; it is a tap-only window after the previous key and leaves deliberate holds alone. Side effect: `A`/`;` can't give Shift within 150 ms of another key.
- The ripple reads the raw matrix from `backlight_update_pwm_buffers()` (main loop, ~30 Hz) instead of the engine's 20 Hz timer interrupt, so mod-taps light instantly and the animation is smoother. All state lives in the main loop, so there is no ISR/main race. Distances use an integer approximation (no FPU).
- Putting it behind a compile flag in the shared engine file, rather than a fork of it, kept every other Wilba board byte-identical; `matt_restore` and a stock `rama_works_m60_a` build were checked to be unchanged.
- VIA's built-in Effect dropdown is a fixed list of effects 0..10 and only shows colour pickers an effect uses, so the ripple had to replace an existing slot. Matt chose "Radial Color 1" (effect 10), keeping "Radial All Hues" (9). Colour 2 and min brightness aren't in the built-in UI, hence the v3 definition.

## What was retired
- "Radial Color 1" (`backlight_effect_cycle_radial2`) is not reachable in the `matt` build (the ripple replaced it). Other builds are unchanged.
- First attempts: ripple at effect 11, then effect 9, and a `via_definition.json` using the wrong v3 field names (`vendorProductId`) — all replaced. The file is now `rama_works_kara.via.json`; `.gitignore` skips `via*.json`, so don't rename it back.

## Key decisions
- `FN_MO13` (VIA's label) isn't defined in current QMK; it maps to `TL_LOWR`, matching the stock `default` keymap. Fn + held Space (`LT(2,SPC)`) reaches the RGB layer.
- J/K/L were `MOD_LGUI | MOD_RGUI` etc. in the VIA export, which QMK treats as the right-hand mod; written as `RGUI_T`/`RALT_T`/`RCTL_T`.
- Config block grew 31 → 32 bytes (`ripple_min`), so the keymap sets `VIA_EEPROM_CUSTOM_CONFIG_SIZE 32`; a `_Static_assert` guards it. Each flash resets the lighting EEPROM, so defaults in `matt/config.h` apply (ripple, lime green 85 → hot pink 235, speed 1). Changing the defaults is how to tell a new flash from the old one.
- Kara is DFU via bootmagic: hold Esc while plugging in. `dfu-programmer atmega32u4 erase --force`, `flash <hex>`, `reset`. VIA/usevia.app: the Design tab needs "Use V2 definitions" **off** for v3 drafts; load `rama_works_kara.via.json`, not the `.layout.json` export.
- At Matt's request the branch was merged into `fork/master` (which already carried the pizzapad keymap) as `d75bc435a1`, not just kept on a feature branch.

## Follow-up
- `.claude/close-out.md` exists only on `feat/waffling60-matt-keymap` and says feature branches only, never `master`. `fork/master` now carries merged personal keymaps (pizzapad, Kara), so that line is out of date; update it where it is next merged.
- `CLAUDE.md` and its keyboard table live only on `feat/pizzapad-matt-keymap`, so the Kara isn't listed there yet.
- This summary is on `feat/kara-matt-keymap` only; `fork/master` doesn't include it unless that branch is merged again.
- The repo is in iCloud-synced `~/Documents`; builds can stall on evicted files (set GMK to Keep Downloaded).
- A copy of `rama_works_kara.via.json` sits on the Desktop for loading into VIA; it can be deleted.
- Memory notes `rama-works-kara-keymap` and `home-row-mod-fix-pattern`, and a private Notion draft "Rama Works Kara: home row mods and Flow Tap, explained", record the same details.
