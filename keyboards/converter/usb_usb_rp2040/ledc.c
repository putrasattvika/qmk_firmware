
#include "hal.h"

#include "led.h"

void blink_init(void) {
    palSetLineMode(25U, PAL_MODE_OUTPUT_PUSHPULL | PAL_RP_PAD_DRIVE12);
}

void blink_for(uint16_t ms) {
    palToggleLine(25U);
    chThdSleepMilliseconds(ms);
    palToggleLine(25U);
}

void blink_1s(void) {
    blink_for(1000);
}
