#include "tusb.h"

/*
 * Returns true if two HID keyboard reports are identical
 */
bool hid_keyboard_reports_identical(hid_keyboard_report_t const *report_a, hid_keyboard_report_t const *report_b);

/*
 * Converts a USB HID keyboard modifier bits and its offset to the modifier's
 * actual keycode
 */
uint8_t hid_keyboard_report_modifier_to_keycode(uint8_t mods, uint8_t mod_idx);
