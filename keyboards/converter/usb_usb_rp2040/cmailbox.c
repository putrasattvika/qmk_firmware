
#include "ch.h"
#include "hal.h"
#include "chmboxes.h"

#include "cmailbox.h"

#define NUM_BUFFERS 4
#define BUFFERS_SIZE 256

static char buffers[NUM_BUFFERS][BUFFERS_SIZE];

static msg_t free_buffers_queue[NUM_BUFFERS];
static mailbox_t free_buffers;

static msg_t filled_buffers_queue[NUM_BUFFERS];
static mailbox_t filled_buffers;

void cmailbox_init(void) {
    chMBObjectInit(&filled_buffers, filled_buffers_queue, NUM_BUFFERS);
    chMBObjectInit(&free_buffers, free_buffers_queue, NUM_BUFFERS);

    /* Pre-filling the free buffers pool with the available buffers, the post
        will not stop because the mailbox is large enough.*/
    for (uint8_t i = 0; i < NUM_BUFFERS; i++) {
        (void)chMBPostI(&free_buffers, (msg_t)&buffers[i]);
    }
}

mailbox_t* cmailbox_mailbox_filled(void) {
    return &filled_buffers;
}

mailbox_t* cmailbox_mailbox_free(void) {
    return &free_buffers;
}
