#pragma once

// Flow Tap: a home row mod pressed within 150 ms of the previous key is always
// a tap, so fast typing can't fire mod combos (e.g. "back " → K then Space).
#define FLOW_TAP_TERM 150
