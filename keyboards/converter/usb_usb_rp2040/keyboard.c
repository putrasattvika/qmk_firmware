// Copyright 2023 sekigon-gonnoc
// SPDX-License-Identifier: GPL-2.0-or-later

// Adapted from https://github.com/qmk/qmk_firmware/pull/20999/files#diff-fd7304baf2a0461e51b1d04e4c288ee99da5798f4251900c488bf1b4d9c8a5fd

// #include "pico/stdlib.h"

#include "hal.h"

#include "debug.h"
#include "keyboard.h"
#include "print.h"

#include "ledc.h"
#include "cmailbox.h"

static THD_WORKING_AREA(wa_mb_consumer, 2048);
static THD_FUNCTION(mb_consumer, arg) {
    mailbox_t* filled_mb = cmailbox_mailbox_filled();
    mailbox_t* free_mb = cmailbox_mailbox_free();

    while (true) {
        void *pbuf;

        /* Waiting for a filled buffer.*/
        msg_t msg = chMBFetchI(filled_mb, (msg_t *)&pbuf);

        /* Processing the event.*/
        if (msg == MSG_OK) {
            /* Returning the buffer to the free buffers pool.*/
            (void)chMBPostI(free_mb, (msg_t)pbuf);

            printf("[core%d] Consumer msg: [%s]\n", chThdGetSelfX()->owner->core_id, (char *)pbuf);

            blink_for(250);
        } else if (msg == MSG_TIMEOUT) {
            chThdSleepMilliseconds(50);
        }
    }
}

void keyboard_pre_init_kb(void) {
    // set_sys_clock_khz(120000, true);

    blink_init();

    chThdCreateStatic(
        wa_mb_consumer, sizeof(wa_mb_consumer), NORMALPRIO + 1,
        mb_consumer, NULL
    );
}

void keyboard_post_init_user(void) {
  debug_enable = true;
  debug_matrix = true;
}
