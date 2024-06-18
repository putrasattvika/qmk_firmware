// Copyright 2023 sekigon-gonnoc
// SPDX-License-Identifier: GPL-2.0-or-later

#include "stdio.h"
#include "string.h"

#include "ch.h"
#include "hal.h"
#include "chmboxes.h"

#include "ledc.h"
#include "cmailbox.h"

// // Main process for core1
// static THD_WORKING_AREA(wa_c1_main_task_wrapper, 2048);
// static THD_FUNCTION(c1_main_task_wrapper, arg) {
//     while (1) {
//         blink_for(250);
//         chThdSleepMilliseconds(750);
//     }
// }

static THD_WORKING_AREA(wa_mb_producer, 2048);
static THD_FUNCTION(mb_producer, arg) {
    mailbox_t* filled_mb = cmailbox_mailbox_filled();
    mailbox_t* free_mb = cmailbox_mailbox_free();

    while (true) {
        void *pbuf;

        if (chMBFetchI(free_mb, (msg_t *)&pbuf) == MSG_OK) {
            sprintf((char *)pbuf, "Message from code_id #%d", chThdGetSelfX()->owner->core_id);
            // strncpy ((char *)pbuf, "Message from core1", 19);

            (void)chMBPostI(filled_mb, (msg_t)pbuf);
        }

        chThdSleepMilliseconds(1000);
    }
}

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

    // blink_init();

    cmailbox_init();

    // // Start main task
    // chThdCreateStatic(
    //     wa_c1_main_task_wrapper, sizeof(wa_c1_main_task_wrapper), NORMALPRIO + 1,
    //     c1_main_task_wrapper, NULL
    // );

    chThdCreateStatic(
        wa_mb_producer, sizeof(wa_mb_producer), NORMALPRIO + 1,
        mb_producer, NULL
    );

    // chThdCreateStatic(
    //     wa_mb_consumer, sizeof(wa_mb_consumer), NORMALPRIO + 1,
    //     mb_consumer, NULL
    // );
}
