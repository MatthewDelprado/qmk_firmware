# QMK Firmware — Matt's Keyboard Repo

This is a local clone of [qmk/qmk_firmware](https://github.com/qmk/qmk_firmware).
Primary purpose: custom keymaps for Matt's keyboards when VIA isn't enough.

Custom keymaps live at: `keyboards/<manufacturer>/<board>/keymaps/matt/`

---

## Keyboard Directory

| Nickname(s) | QMK path | MCU | Layout | Notes |
|---|---|---|---|---|
| pretty paddy, pretty pad, paddy pad, pizza pad | `keyboards/idyllic/pizzapad` | RP2040 (Seeed XIAO) | 3×3 ortho (9 keys) | Optional rotary encoder on GP2/GP3. Sold by MechStock AU. VIA name: "Pizza Pad". |

---

## Flashing / Bootloader

To enter bootloader mode on a board using the **Seeed XIAO RP2040** (e.g. Pretty Paddy), use any of these three methods:

1. **Bootmagic** (easiest): Hold the **top-left key (K0)** while plugging in the USB-C cable — board mounts as `RPI-RP2` drive, drag on the `.uf2` file.
2. **Physical buttons**: With USB already connected, press **BOOT + RESET simultaneously** — board remounts as `RPI-RP2`.
3. **Keycode**: If `QK_BOOT` is mapped in the layout, just press that key.

---

## Build Commands

```bash
# Compile a keymap
qmk compile -kb <qmk-path> -km matt

# Flash directly
qmk flash -kb <qmk-path> -km matt

# Example: Pretty Paddy
qmk compile -kb idyllic/pizzapad -km matt
```

## Setup

```bash
# First time only
brew install qmk/qmk/qmk
qmk setup   # run from repo root
```
