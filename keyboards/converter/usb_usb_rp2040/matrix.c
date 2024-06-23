// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "tusb.h"

#include "debug.h"
#include "keycode.h"
#include "matrix.h"

static hid_keyboard_report_t matrix_kb_report = { 0, 0, {0} };
static hid_keyboard_report_t matrix_kb_report_prev = { 0, 0, {0} };

// Mapping between a "1" bit on a HID report modifiers bitmap and the modifier
// key it indicates.
//
//
// See: https://wiki.osdev.org/USB_Human_Interface_Devices#Report_format
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

//--------------------------------------------------------------------+
// Helpers
//--------------------------------------------------------------------+

// Returns true if two HID keyboard reports are identical
static bool reports_identical(
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

// Converts a USB HID keyboard modifier bits and its offset to the modifier's
// actual keycode
static uint8_t report_modifier_to_keycode(uint8_t mods, uint8_t mod_idx) {
    // Invalid modifier index or the specified index is not on
    if ((mod_idx >= 8) || ((mods & 1 << mod_idx) == 0)) {
        return KC_NO;
    }

    return hid_keyboard_report_modifier_to_rowcol_map[mod_idx];
}

//--------------------------------------------------------------------+
// QMK Custom Matrix Implementation
//--------------------------------------------------------------------+

__attribute__((weak)) void matrix_init_kb(void) { matrix_init_user(); }

__attribute__((weak)) void matrix_scan_kb(void) { matrix_scan_user(); }

__attribute__((weak)) void matrix_init_user(void) {}

__attribute__((weak)) void matrix_scan_user(void) {}

void matrix_init(void) {
    // This *must* be called for correct keyboard behavior
    matrix_init_kb();
}

uint8_t matrix_scan(void) {
    bool changed = false;

    if (!reports_identical(&matrix_kb_report, &matrix_kb_report_prev)) {
        matrix_kb_report_prev = matrix_kb_report;
        changed = true;
    }

    // This *must* be called for correct keyboard behavior
    matrix_scan_kb();

    return changed;
}

matrix_row_t matrix_get_row(uint8_t row) {
    hid_keyboard_report_t report = matrix_kb_report;
    uint16_t row_bits = 0;

    for (uint8_t i = 0; i < 8; i++) {
        uint8_t keycode = report_modifier_to_keycode(report.modifier, i);
        if (!IS_ANY(keycode)) {
            continue;
        }

        uint8_t mapped_row = keycode >> 4;
        uint8_t mapped_col = keycode & 0b00001111;

        if (mapped_row != row) {
            continue;
        }

        row_bits |= 1 << mapped_col;
    }

    for (uint8_t i = 0; i < 6; i++) {
        if (!IS_ANY(report.keycode[i])) {
            continue;
        }

        uint8_t keycode = report.keycode[i];
        if (!IS_ANY(keycode)) {
            continue;
        }

        uint8_t mapped_row = keycode >> 4;
        uint8_t mapped_col = keycode & 0b00001111;

        if (mapped_row != row) {
            continue;
        }

        row_bits |= 1 << mapped_col;
    }

    return (matrix_row_t)row_bits;
}

bool matrix_is_on(uint8_t row, uint8_t col) {
    return (matrix_get_row(row) & ((matrix_row_t)1 << col));
}

void matrix_print(void) {
    print("\nr/c 0123456789ABCDEF\n");

    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        print_hex8(row);
        print(": ");
        print_bin_reverse16(matrix_get_row(row));
        print("\n");
    }
}

//--------------------------------------------------------------------+
// TinyUSB Callbacks
//--------------------------------------------------------------------+

static void process_kbd_report(uint8_t dev_addr, hid_keyboard_report_t const *report) {
    (void) dev_addr;

    if (debug_enable && !reports_identical(&matrix_kb_report, report)) {
        dprintf(
            "[%u] Report: %02x | %02x %02x %02x %02x %02x %02x\n",
            dev_addr,
            report->modifier,
            report->keycode[0],
            report->keycode[1],
            report->keycode[2],
            report->keycode[3],
            report->keycode[4],
            report->keycode[5]
        );
    }

    matrix_kb_report = *report;
}

void tuh_hid_mount_cb(uint8_t dev_addr, uint8_t instance, uint8_t const* desc_report, uint16_t desc_len) {
    dprintf("[%02x] HID mounted: addr=%02x instance=%02x\n", dev_addr, dev_addr, instance);

    for (int instance = 0; instance < tuh_hid_instance_count(dev_addr); instance++) {
        tuh_hid_receive_report(dev_addr, instance);

        if (tuh_hid_interface_protocol(dev_addr, instance) == HID_ITF_PROTOCOL_KEYBOARD) {
            dprintf("[%02x] Found keyboard HID: addr=%02x instance=%02x\n", dev_addr, dev_addr, instance);
        }
    }
}

void tuh_hid_report_received_cb(uint8_t dev_addr, uint8_t instance, uint8_t const* report, uint16_t len) {
    (void) len;

    uint8_t const itf_protocol = tuh_hid_interface_protocol(dev_addr, instance);
    switch(itf_protocol) {
        case HID_ITF_PROTOCOL_KEYBOARD:
            dprintf("[%02x] Keyboard HID report received from instance=%02x\n", dev_addr, instance);
            process_kbd_report(dev_addr, (hid_keyboard_report_t const*) report );

            break;

        default:
            break;
    }

    tuh_hid_receive_report(dev_addr, instance);
}
