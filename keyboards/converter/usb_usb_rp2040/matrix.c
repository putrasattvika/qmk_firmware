// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "tusb.h"

#include "keycode.h"
#include "matrix.h"
#include "print.h"
#include "usb_usb_rp2040/uu_common.h"

hid_keyboard_report_t matrix_kb_report = { 0, 0, {0} };
static hid_keyboard_report_t matrix_kb_report_prev = { 0, 0, {0} };

__attribute__((weak)) void matrix_init_kb(void) { matrix_init_user(); }

__attribute__((weak)) void matrix_scan_kb(void) { matrix_scan_user(); }

__attribute__((weak)) void matrix_init_user(void) {}

__attribute__((weak)) void matrix_scan_user(void) {}

void matrix_init(void) {
    // TODO: Should we wait for c1_main_task to start?

    // This *must* be called for correct keyboard behavior
    matrix_init_kb();
}

uint8_t matrix_scan(void) {
    bool changed = false;

    if (!hid_keyboard_reports_identical(&matrix_kb_report, &matrix_kb_report_prev)) {
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
        uint8_t keycode = hid_keyboard_report_modifier_to_keycode(report.modifier, i);
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
