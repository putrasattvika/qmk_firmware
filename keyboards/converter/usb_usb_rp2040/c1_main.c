// Copyright 2023 sekigon-gonnoc
// SPDX-License-Identifier: GPL-2.0-or-later

#include "stdio.h"
#include "string.h"

#include "ch.h"
#include "hal.h"

#include "ledc.h"
#include "cusb_host.h"

static virtual_timer_t vt;

static void sof_timer_cb(virtual_timer_t *_vt, void *_) {
    cusb_host_sof_timer_task();
}

void start_sof_timer(void) {
    chVTObjectInit(&vt);
    chVTSetContinuous(&vt, TIME_MS2I(1), sof_timer_cb, NULL);
}

// Main thread for core1
static THD_WORKING_AREA(wa_c1_main_task_wrapper, 2048);
static THD_FUNCTION(c1_main_task_wrapper, arg) {
    cusb_host_init(18);
    start_sof_timer();

    while (true) {
        cusb_host_task();
        chThdSleepMicroseconds(125);
    }
}

static THD_WORKING_AREA(wa_blinker, 2048);
static THD_FUNCTION(blinker, arg) {
    while (true) {
        blink_for(200);

        chThdSleepMilliseconds(800);
    }
}

// Entry point of core1, the function name is hardcoded in chibios
void c1_main(void) {
    chSysWaitSystemState(ch_sys_running);
    chInstanceObjectInit(&ch1, &ch_core1_cfg);
    chSysUnlock();

    blink_init();

    // USB host stack uses PIO and DMA
    hal_lld_peripheral_unreset(RESETS_ALLREG_PIO0);
    hal_lld_peripheral_unreset(RESETS_ALLREG_PIO1);
    hal_lld_peripheral_unreset(RESETS_ALLREG_DMA);

    // Start main task
    chThdCreateStatic(
        wa_c1_main_task_wrapper, sizeof(wa_c1_main_task_wrapper), NORMALPRIO + 1,
        c1_main_task_wrapper, NULL
    );

    chThdCreateStatic(
        wa_blinker, sizeof(wa_blinker), NORMALPRIO + 1,
        blinker, NULL
    );
}
