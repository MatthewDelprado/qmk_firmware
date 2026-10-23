# Waffling60 underglow presets — 2026-10-23

Session ran 2026-09-26 → 2026-10-23 on branch `feat/waffling60-matt-keymap`.

## What was built
- `keyboards/4pplet/waffling60/rev_e_ansi/keymaps/matt/` — new keymap for the 4pplet waffling60 Rev E ANSI HS (17-LED underglow), ported from `~/qmk_firmware_06082023` commit 0994d6b5df, which had edited the board's `default` keymap directly (home-row mods, per-key tapping term, VIA layout baked in).
- Underglow drawn per LED from `housekeeping_task_user` instead of via rgblight modes:
  - **pulse:** each keypress (read from the raw matrix, so it's instant even on mod-taps) sends a ring outward; rings fade and add up where they overlap. Works as a bright ring on a dim layer or a dark ring on a bright one.
  - **spin:** conic teal→purple gradient rotating around the board centre.
  - **rainbow** (static) and **solid**.
  - **layer transition:** on a layer change the new layer ripples out from the key that changed it, over a snapshot of the old colours.
- `underglow.json` — all lighting config: LED positions, named colours, pulse/transition timing, and presets. `gen_underglow.py` turns it into `underglow_presets.h`; `rules.mk` runs it on every build and fails the build with a readable message on bad JSON.
- Presets: `teal purple pulse` (original), `teal purple spin`, `teal purple spin dim` (dark rings on full-brightness layers), `teal purple spin cross` (**active and flashed**, commit 1ad8fc056c: teal layers pulse purple and vice versa).
- `LED_CAL` on Fn+Z: lights one LED at a time, records the nearest key pressed, then types a `"led_positions"` JSON line.
- Reference page with live previews of every preset: https://claude.ai/artifact/U19ZBegu6LyotVY5TbsbRc (built from `underglow.json`; republish to the same URL when presets change).

## Why
- Lighting is drawn directly rather than with rgblight layers because rgblight can only do whole-strip modes or static segments; pulses, spin and per-LED transitions need per-frame control.
- Presets live in JSON (the user's ask) so they can be swapped and tuned without touching C. Generating a header at build time keeps the firmware free of any JSON parsing and keeps the header from going stale.
- Presses come from the matrix diff, not `process_record_user`, because mod-taps only reach `process_record` after the tapping term and the ripple would lag by up to 250 ms.
- Distances to each LED are worked out once per press (integer sqrt), and the spin uses a "diamond angle" in place of atan2 — the MCU is a Cortex-M0 with no FPU.
- LED positions come from on-board calibration because 4pplet's PCB files are Altium and the docs don't show the underglow layout.

## Key decisions
- The board's MCU is an **APM32**, not STM32: in bootloader it shows as `314b:0106` ("APM32 DFU ISP Mode"), so `qmk flash` / watchers for `0483:df11` miss it. Flash with `dfu-util -a 0 -d 314b:0106 -s 0x08000000:leave -D .build/4pplet_waffling60_rev_e_ansi_matt.bin`, then unplug/replug (it doesn't reset itself).
- The LEDs run clockwise around the board edge starting near Tab. LED 9 (lower right edge) is hidden by the case and estimated at (56, 14). LED 16 is the Caps Lock LED, not fitted on the hotswap PCB, so it's kept dark.
- Flashing resets VIA's EEPROM keymap (VIA's magic is the build date), which is why the VIA layout is baked into `keymap.c`.

## Follow-up
- A stray calibration line pasted near the end (LED 8 hidden, LED 16 at (56, 10)) was judged an accidental Fn+Z during a bootloader attempt and not saved.
- `CLAUDE.md` and its keyboard table live only on `feat/pizzapad-matt-keymap`; this branch was cut from `master`, so the waffling60 isn't listed there yet.
- The repo is in iCloud-synced `~/Documents`; ~22k files were evicted and stalled builds. Setting `GMK` to Keep Downloaded (Finder) or moving the repo out of iCloud would prevent it.
