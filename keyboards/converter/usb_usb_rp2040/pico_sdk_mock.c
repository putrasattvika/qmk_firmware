// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "pico/stdlib.h"

// This file contains mocks for some pico-sdk functions referenced but not
// actually called during runtime by Pico-PIO-USB. These mocks are safe as long
// as pio_usb_configuration_t.skip_alarm_pool is set to true.

bool alarm_pool_add_repeating_timer_us(alarm_pool_t *pool, int64_t delay_us, repeating_timer_callback_t callback, void *user_data, repeating_timer_t *out) {
    return false;
}

alarm_pool_t *alarm_pool_create(uint hardware_alarm_num, uint max_timers) {
    return NULL;
}
