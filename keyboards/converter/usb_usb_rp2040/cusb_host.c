
#include "pico/stdlib.h"

#include "pio_usb.h"
// #include "tusb.h"

#include "print.h"

#include "cusb_host.h"

static usb_device_t *usb_device = NULL;
static bool initialized = false;

void cusb_host_init(uint8_t pin_dp) {
    static pio_usb_configuration_t config = PIO_USB_DEFAULT_CONFIG;
    config.pin_dp = pin_dp;
    config.skip_alarm_pool = true;

    usb_device = pio_usb_host_init(&config);

    initialized = true;
}

void cusb_host_task(void) {
    if (!initialized) {
        return;
    }

    pio_usb_host_task();
}

void cusb_host_sof_timer_task(void) {
    if (!initialized) {
        return;
    }

    pio_usb_host_frame();
}

void cusb_host_print_keycodes(void) {
    if (usb_device == NULL) {
        // printf("usb_device is NULL\n");
        return;
    }

    for (int dev_idx = 0; dev_idx < PIO_USB_DEVICE_CNT; dev_idx++) {
        usb_device_t *device = &usb_device[dev_idx];
        if (!device->connected) {
            // printf("Device %d is not connected\n", dev_idx);
            continue;
        }

        for (int ep_idx = 0; ep_idx < PIO_USB_DEV_EP_CNT; ep_idx++) {
            endpoint_t *ep = pio_usb_get_endpoint(device, ep_idx);
            if (ep == NULL) {
                // printf("Device %d endpoint %d is null\n", dev_idx, ep_idx);
                break;
            }

            uint8_t in_buf[64];
            int len = pio_usb_get_in_data(ep, in_buf, sizeof(in_buf));
            if (len <= 0) {
                continue;
            }

            printf(
                "[ENDPOINT] id=%04x:%04x ep=0x%02x is_tx=%x:\t",
                device->vid, device->pid,
                ep->ep_num,
                ep->is_tx
            );
            for (int i = 0; i < len; i++) {
                printf("%02x ", in_buf[i]);
            }
            printf("\n");
        }
    }
}
