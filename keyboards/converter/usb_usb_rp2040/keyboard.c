// Copyright 2023 sekigon-gonnoc
// SPDX-License-Identifier: GPL-2.0-or-later

// Adapted from https://github.com/qmk/qmk_firmware/pull/20999/files#diff-fd7304baf2a0461e51b1d04e4c288ee99da5798f4251900c488bf1b4d9c8a5fd

#include "pico/stdlib.h"

#include "debug.h"
#include "keyboard.h"

void keyboard_pre_init_kb(void) {
    set_sys_clock_khz(120000, true);
}

void keyboard_post_init_user(void) {
  debug_enable = true;
  debug_matrix = true;
}
