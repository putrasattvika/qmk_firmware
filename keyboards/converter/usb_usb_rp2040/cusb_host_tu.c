#include "pio_usb.h"
#include "tusb.h"

#include "cusb_host.h"

void cusb_host_init(uint8_t pin_dp) {
    static pio_usb_configuration_t config = PIO_USB_DEFAULT_CONFIG;
    config.pin_dp = pin_dp;

    tuh_configure(1, TUH_CFGID_RPI_PIO_USB_CONFIGURATION, &config);
    tuh_init(1);
}

void cusb_host_task(void) {
    tuh_task();
}

void tuh_hid_report_received_cb(uint8_t dev_addr, uint8_t instance, uint8_t const* report, uint16_t len) {
    (void) dev_addr;
    (void) instance;
    (void) report;
    (void) len;
}
