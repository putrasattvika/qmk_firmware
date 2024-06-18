// Copyright 2023 sekigon-gonnoc
// SPDX-License-Identifier: GPL-2.0-or-later

#include "stdio.h"
#include "string.h"

#include "ch.h"
#include "hal.h"
// #include "chmboxes.h"

#include "print.h"

#include "ledc.h"
// #include "cmailbox.h"

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

    while (true) {
        cusb_host_task();
        chThdSleepMicroseconds(125);
    }
}

static THD_WORKING_AREA(wa_keycode_consumer, 2048);
static THD_FUNCTION(keycode_consumer, arg) {
    while (true) {
        cusb_host_print_keycodes();
        chThdSleepMilliseconds(50);
    }
}

static THD_WORKING_AREA(wa_blinker, 2048);
static THD_FUNCTION(blinker, arg) {
    while (true) {
        printf("core1 healthcheck: OK\n");
        blink_for(200);

        chThdSleepMilliseconds(800);
    }
}

// static THD_WORKING_AREA(wa_mb_producer, 2048);
// static THD_FUNCTION(mb_producer, arg) {
//     mailbox_t* filled_mb = cmailbox_mailbox_filled();
//     mailbox_t* free_mb = cmailbox_mailbox_free();

//     while (true) {
//         void *pbuf;

//         if (chMBFetchI(free_mb, (msg_t *)&pbuf) == MSG_OK) {
//             sprintf((char *)pbuf, "Message from code_id #%d", chThdGetSelfX()->owner->core_id);
//             // strncpy ((char *)pbuf, "Message from core1", 19);

//             printf("[core%d] Logging from core1\n", chThdGetSelfX()->owner->core_id);

//             (void)chMBPostI(filled_mb, (msg_t)pbuf);
//         }

//         chThdSleepMilliseconds(1000);
//     }
// }

// static THD_WORKING_AREA(wa_mb_consumer, 2048);
// static THD_FUNCTION(mb_consumer, arg) {
//     mailbox_t* filled_mb = cmailbox_mailbox_filled();
//     mailbox_t* free_mb = cmailbox_mailbox_free();

//     while (true) {
//         void *pbuf;

//         /* Waiting for a filled buffer.*/
//         msg_t msg = chMBFetchI(filled_mb, (msg_t *)&pbuf);

//         /* Processing the event.*/
//         if (msg == MSG_OK) {
//             /* Returning the buffer to the free buffers pool.*/
//             (void)chMBPostI(free_mb, (msg_t)pbuf);

//             blink_for(250);
//         } else if (msg == MSG_TIMEOUT) {
//             chThdSleepMilliseconds(50);
//         }
//     }
// }

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

    start_sof_timer();

    // Start main task
    chThdCreateStatic(
        wa_c1_main_task_wrapper, sizeof(wa_c1_main_task_wrapper), NORMALPRIO + 1,
        c1_main_task_wrapper, NULL
    );

    chThdCreateStatic(
        wa_keycode_consumer, sizeof(wa_keycode_consumer), NORMALPRIO + 1,
        keycode_consumer, NULL
    );

    chThdCreateStatic(
        wa_blinker, sizeof(wa_blinker), NORMALPRIO + 1,
        blinker, NULL
    );

    // chThdCreateStatic(
    //     wa_mb_consumer, sizeof(wa_mb_consumer), NORMALPRIO + 1,
    //     mb_consumer, NULL
    // );

}
