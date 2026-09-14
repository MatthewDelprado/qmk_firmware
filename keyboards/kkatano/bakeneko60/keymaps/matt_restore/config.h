#pragma once

// Keep the USB vendor ID the board shipped with (QMK's bakeneko60 uses 0x3A0E)
// so VIA still matches the "Dropbear60 Solder (Bakeneko 60 v3)" definition.
#undef VENDOR_ID
#define VENDOR_ID 0x6A6A

// VIA layout options the board had before the first custom flash (read back as 7):
// split backspace + split right shift + tsangan bottom row. Only affects VIA's display.
#define VIA_EEPROM_LAYOUT_OPTIONS_DEFAULT 0x00000007

