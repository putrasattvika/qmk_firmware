// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "matrix.h"
#include "print.h"

__attribute__((weak)) void matrix_init_kb(void) { matrix_init_user(); }

__attribute__((weak)) void matrix_scan_kb(void) { matrix_scan_user(); }

__attribute__((weak)) void matrix_init_user(void) {}

__attribute__((weak)) void matrix_scan_user(void) {}

matrix_row_t matrix_get_row(uint8_t row) {
    // TODO: return the requested row data
    return 0x00;
}

void matrix_print(void) {
    // TODO: use print() to dump the current matrix state to console
}

void matrix_init(void) {
    // TODO: initialize hardware and global matrix state here

    // This *must* be called for correct keyboard behavior
    matrix_init_kb();
}

uint8_t matrix_scan(void) {
    bool changed = false;

    static uint32_t call_cnt = 0;
    call_cnt++;

    if (call_cnt % 100000 == 0) {
        printf("matrix_scan() (cnt=%ld)\n", call_cnt);
        call_cnt = 0;
    }

    // TODO: add matrix scanning routine here

    // This *must* be called for correct keyboard behavior
    matrix_scan_kb();

    return changed;
}
