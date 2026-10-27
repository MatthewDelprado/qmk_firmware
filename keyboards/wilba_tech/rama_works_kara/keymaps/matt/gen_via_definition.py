import json, sys
src, out = sys.argv[1], sys.argv[2]
kb = json.load(open(src))
keys = kb["layouts"]["LAYOUT_60_hhkb"]["layout"]

# KLE rows from the matrix layout: one array per y, labels are "row,col"
rows = {}
for k in keys:
    rows.setdefault(k["y"], []).append(k)
keymap = []
for y in sorted(rows):
    cursor, row = 0, []
    for k in sorted(rows[y], key=lambda k: k["x"]):
        props = {}
        if k["x"] != cursor:
            props["x"] = round(k["x"] - cursor, 4)
        w = k.get("w", 1)
        if w != 1:
            props["w"] = w
        if props:
            row.append(props)
        row.append("%d,%d" % tuple(k["matrix"]))
        cursor = k["x"] + w
    keymap.append(row)

effects = [["All Off", 0], ["Solid Color 1", 1], ["Alphas / Mods", 2], ["Gradient Up Down", 3],
           ["Raindrops", 4], ["Cycle All", 5], ["Cycle Left Right", 6], ["Cycle Up Down", 7],
           ["Jellybean Raindrops", 8], ["Radial All Hues", 9], ["Ripple (reactive)", 10]]

def ctl(label, typ, name, value, options=None):
    c = {"label": label, "type": typ, "content": [name, 0, value]}
    if options is not None:
        c["options"] = options
    return c

# Value ids match wt_rgb_backlight_api.h; channel 0 is id_custom_channel
menus = [{
    "label": "Lighting",
    "content": [{
        "label": "Kara lighting",
        "content": [
            ctl("Brightness (max)", "range", "id_wt_brightness", 0x09, [0, 255]),
            ctl("Effect", "dropdown", "id_wt_effect", 0x0A, effects),
            ctl("Effect speed", "range", "id_wt_effect_speed", 0x0B, [0, 3]),
            ctl("Color 1 (start)", "color", "id_wt_color_1", 0x0C),
            ctl("Color 2 (end)", "color", "id_wt_color_2", 0x0D),
            ctl("Ripple brightness (min)", "range", "id_wt_ripple_min", 0x18, [0, 255]),
        ],
    }],
}]

# Order must match enum wt_rgb_backlight_keycodes (starts at QK_KB_0)
names = ["BR+", "BR-", "EF+", "EF-", "ES+", "ES-", "H1+", "H1-", "S1+", "S1-", "H2+", "H2-", "S2+", "S2-", "RipMin-", "RipMin+"]
titles = ["Brightness up", "Brightness down", "Effect next", "Effect previous", "Effect speed up", "Effect speed down",
          "Color 1 hue up", "Color 1 hue down", "Color 1 saturation up", "Color 1 saturation down",
          "Color 2 hue up", "Color 2 hue down", "Color 2 saturation up", "Color 2 saturation down",
          "Ripple min brightness down", "Ripple min brightness up"]
custom = [{"name": n, "title": t, "shortName": n} for n, t in zip(names, titles)]

json.dump({
    "name": "RAMA WORKS KARA",
    "vendorId": "0x5241",
    "productId": "0x4B52",
    "matrix": {"rows": 5, "cols": 14},
    "customKeycodes": custom,
    "menus": menus,
    "layouts": {"keymap": keymap},
}, open(out, "w"), indent=2)
print("keys:", sum(len([i for i in r if isinstance(i, str)]) for r in keymap), "rows:", len(keymap))
