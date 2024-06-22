#include "tusb.h"

#include "keycode.h"
#include "usb_usb_rp2040/uu_common.h"

// Mapping between a "1" bit on a HID report modifiers bitmap and the modifier
// key it indicates
static uint16_t hid_keyboard_report_modifier_to_rowcol_map[8] = {
    KC_LCTL,
    KC_LSFT,
    KC_LALT,
    KC_LGUI,
    KC_RCTL,
    KC_RSFT,
    KC_RALT,
    KC_RGUI
};

bool hid_keyboard_reports_identical(
    hid_keyboard_report_t const *report_a,
    hid_keyboard_report_t const *report_b
) {
    if (report_a->modifier != report_b->modifier) {
        return false;
    }

    for(uint8_t i = 0; i < 6; i++) {
        if (report_a->keycode[i] != report_b->keycode[i]) {
            return false;
        }
    }

    return true;
}

uint8_t hid_keyboard_report_modifier_to_keycode(uint8_t mods, uint8_t mod_idx) {
    // Invalid modifier index or the specified index is not on
    if ((mod_idx >= 8) || ((mods & 1 << mod_idx) == 0)) {
        return KC_NO;
    }

    return hid_keyboard_report_modifier_to_rowcol_map[mod_idx];
}
