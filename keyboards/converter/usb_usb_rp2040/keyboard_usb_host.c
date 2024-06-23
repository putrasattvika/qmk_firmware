// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "ch.h"
#include "hal.h"
#include "pio_usb.h"
#include "tusb.h"

#include "config.h"

static virtual_timer_t vt;

static void usb_host_sof_timer_cb(virtual_timer_t *_vt, void *_) {
    pio_usb_host_frame();
}

static THD_WORKING_AREA(wa_usb_host_setup, 2048);
static THD_FUNCTION(usb_host_setup, arg) {
    pio_usb_configuration_t config = PIO_USB_DEFAULT_CONFIG;
    config.pin_dp = USB_DEVICE_DATAPLUS_PIN;
    config.skip_alarm_pool = true;

    tuh_configure(1, TUH_CFGID_RPI_PIO_USB_CONFIGURATION, &config);
    tuh_init(1);

    chVTObjectInit(&vt);
    chVTSetContinuous(&vt, TIME_MS2I(1), usb_host_sof_timer_cb, NULL);

    while (true) {
        tuh_task();
        chThdSleepMicroseconds(125);
    }
}

// Continuation of keyboard_pre_init_kb(). Has to be defined in a separate file
// as pico/stdlib.h cannot be included in the same file as ChibiOS.
void keyboard_pre_init_kb_2(void) {
    // Pico-PIO-USB host stack uses both PIOs and DMA
    hal_lld_peripheral_unreset(RESETS_ALLREG_PIO0);
    hal_lld_peripheral_unreset(RESETS_ALLREG_PIO1);
    hal_lld_peripheral_unreset(RESETS_ALLREG_DMA);

    // Start the USB host thread
    //
    // HACK: ideally this should be run in core1 instead, but that seems to
    // cause a crash when Via keymaps are written to flash
    chThdCreateStatic(
        wa_usb_host_setup, sizeof(wa_usb_host_setup), NORMALPRIO + 1,
        usb_host_setup, NULL
    );
}
