#!/usr/bin/env python3
"""
via_to_keymap.py — Convert a VIA JSON layout export into LAYOUT_all blocks
for the waffling60 Rev E ANSI keymap.c.

Usage:
    python3 via_to_keymap.py <via_json> <keymap_c>

Prints the converted LAYOUT_all blocks to stdout.

waffling60 Rev E ANSI — VIA JSON index → LAYOUT_all physical position mapping
(derived from the 70-entry VIA array vs 64-key LAYOUT_all):

  Row 0 (15): VIA[0-13, 27]
  Row 1 (14): VIA[14-26, 40]
  Row 2 (13): VIA[28-39, 41]
  Row 3 (13): VIA[42, 44-55]      (VIA[43] = structural KC_NO, skip)
  Row 4  (9): VIA[56-58, 60, 62, 64, 67-69]  (skip 59,61,63,65,66)
"""

import json
import sys

# Physical key order: list of VIA indices in LAYOUT_all slot order
VIA_TO_PHYSICAL = (
    # Row 0 (15 keys): Esc/Hyper, 1–\, BSPC
    [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 27] +
    # Row 1 (14 keys): Tab, Q–], backslash
    [14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 40] +
    # Row 2 (13 keys): Caps/Hyper, A–', Enter
    [28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 41] +
    # Row 3 (13 keys): Shift, Z–/, Up, MO(1)  — VIA[43] is structural KC_NO
    [42, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55] +
    # Row 4 (9 keys): bottom row — VIA[59,61,63,65,66] are structural KC_NO
    [56, 57, 58, 60, 62, 64, 67, 68, 69]
)

ROWS = [15, 14, 13, 13, 9]

ROW_COMMENTS = [
    "/* Row 0: Esc/Hyper, 1–\\, BSPC */",
    "/* Row 1: Tab, Q–], \\ */",
    "/* Row 2: Caps/Hyper, A–', Enter */",
    "/* Row 3: Shift, Z–/, Up, MO(1) */",
    "/* Row 4: bottom row */",
]

LAYER_NAMES = ["_BASE", "_FN", "_FN2", "_FN3"]


def translate_key(k: str) -> str:
    k = k.strip()
    if k in ("KC_TRNS", "KC_TRANSPARENT"):
        return "_______"
    if k == "RESET":
        return "QK_BOOT"
    return k


def via_layer_to_physical(via_keys: list) -> list:
    return [translate_key(via_keys[i]) for i in VIA_TO_PHYSICAL]


def format_layer(layer_name: str, physical: list) -> str:
    lines = [f"    [{layer_name}] = LAYOUT_all("]
    pos = 0
    for row_idx, width in enumerate(ROWS):
        keys = physical[pos:pos + width]
        pos += width
        is_last = (row_idx == len(ROWS) - 1)
        sep = "" if is_last else ","
        lines.append(f"        {ROW_COMMENTS[row_idx]}")
        lines.append(f"        {', '.join(keys)}{sep}")
    lines.append("    ),")
    lines.append("")
    return "\n".join(lines)


def main():
    if len(sys.argv) != 3:
        print(f"Usage: {sys.argv[0]} <via_json> <keymap_c>", file=sys.stderr)
        sys.exit(1)

    via_json_path = sys.argv[1]
    keymap_c_path = sys.argv[2]

    with open(via_json_path) as f:
        via = json.load(f)

    print("=" * 70)
    print("via_to_keymap.py — converted LAYOUT_all blocks")
    print(f"Source: {via_json_path}")
    print("=" * 70)
    print()

    for idx, (via_layer, name) in enumerate(zip(via["layers"], LAYER_NAMES)):
        physical = via_layer_to_physical(via_layer)
        if len(physical) != 64:
            print(f"WARNING: layer {idx} has {len(physical)} physical keys", file=sys.stderr)
        print(format_layer(name, physical))

    if "encoders" in via:
        enc = via["encoders"][0]
        print("#if defined(ENCODER_MAP_ENABLE)")
        print("const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {")
        for i, (enc_layer, lname) in enumerate(zip(enc, LAYER_NAMES)):
            ccw = translate_key(enc_layer[0])
            cw  = translate_key(enc_layer[1])
            comma = "," if i < len(enc) - 1 else ""
            print(f"    [{lname}]  = {{ ENCODER_CCW_CW({ccw}, {cw}) }}{comma}")
        print("};")
        print("#endif")
        print()


if __name__ == "__main__":
    main()
