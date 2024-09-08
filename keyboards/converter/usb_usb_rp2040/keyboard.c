// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "pico/stdlib.h"

#include "debug.h"
#include "keyboard.h"

void keyboard_pre_init_kb_2(void);

void keyboard_pre_init_kb(void) {
    // Sysclock should be multiple of 12MHz.
    // See https://github.com/sekigon-gonnoc/Pico-PIO-USB/blob/0.5.3/examples/capture_hid_report/capture_hid_report.c#L31-L32
    set_sys_clock_khz(120000, true);

    // keyboard_pre_init_kb_2();

    keyboard_pre_init_user();
}

void keyboard_post_init_user(void) {
  debug_enable = false;
  debug_matrix = false;
  debug_keyboard = false;
  debug_mouse = false;
}
