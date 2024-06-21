#include "pio_usb.h"
#include "tusb.h"

#include "print.h"
#include "cusb_host.h"

static bool initialized = false;

void cusb_host_init(uint8_t pin_dp) {
    static pio_usb_configuration_t config = PIO_USB_DEFAULT_CONFIG;
    config.pin_dp = pin_dp;
    config.skip_alarm_pool = true;

    tuh_configure(1, TUH_CFGID_RPI_PIO_USB_CONFIGURATION, &config);
    tuh_init(1);

    initialized = true;
}

void cusb_host_task(void) {
    if (!initialized) {
        return;
    }

    tuh_task();
}

void cusb_host_sof_timer_task(void) {
    if (!initialized) {
        return;
    }

    pio_usb_host_frame();
}

void cusb_host_print_keycodes(void) {}

static inline bool reports_identical(
    hid_keyboard_report_t const *report_a,
    hid_keyboard_report_t const *report_b
) {
    if (report_a->modifier != report_b->modifier) {
        return false;
    }

    for(uint8_t i = 0; i < 6; i++) {
        if (report_a->keycode[i] != report_b->keycode[i]) {
            return false;
        }
    }

    return true;
}

static void process_kbd_report(uint8_t dev_addr, hid_keyboard_report_t const *report) {
    (void) dev_addr;

    // previous report to check key release
    static hid_keyboard_report_t prev_report = { 0, 0, {0} };

    if (!reports_identical(&prev_report, report)) {
        printf(
            "[%u] Report: %02x | %02x %02x %02x %02x %02x %02x\n",
            dev_addr,
            report->modifier,
            report->keycode[0],
            report->keycode[1],
            report->keycode[2],
            report->keycode[3],
            report->keycode[4],
            report->keycode[5]
        );
    }

    prev_report = *report;
}

void tuh_hid_mount_cb(uint8_t dev_addr, uint8_t instance, uint8_t const* desc_report, uint16_t desc_len) {
    printf("[%02x] HID mounted: addr=%02x instance=%02x\n", dev_addr, dev_addr, instance);

    for (int instance = 0; instance < tuh_hid_instance_count(dev_addr); instance++) {
        tuh_hid_receive_report(dev_addr, instance);

        if (tuh_hid_interface_protocol(dev_addr, instance) == HID_ITF_PROTOCOL_KEYBOARD) {
            printf("[%02x] Found keyboard HID: addr=%02x instance=%02x\n", dev_addr, dev_addr, instance);
        }
    }
}

void tuh_hid_report_received_cb(uint8_t dev_addr, uint8_t instance, uint8_t const* report, uint16_t len) {
    (void) len;

    uint8_t const itf_protocol = tuh_hid_interface_protocol(dev_addr, instance);

    switch(itf_protocol) {
        case HID_ITF_PROTOCOL_KEYBOARD:
            printf("[%02x] Keyboard HID report received from instance=%02x\n", dev_addr, instance);
            process_kbd_report(dev_addr, (hid_keyboard_report_t const*) report );

            break;

        default: break;
    }

    tuh_hid_receive_report(dev_addr, instance);
}
