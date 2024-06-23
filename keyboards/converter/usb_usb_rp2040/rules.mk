# Keyboard
CUSTOM_MATRIX = yes
SRC += pico_sdk_mock.c
SRC += keyboard.c
SRC += keyboard_usb_host.c
SRC += matrix.c

# Pico-PIO-USB
SRC += lib/Pico-PIO-USB/src/pio_usb.c
SRC += lib/Pico-PIO-USB/src/pio_usb_host.c
SRC += lib/Pico-PIO-USB/src/usb_crc.c
VPATH += lib/Pico-PIO-USB/src

# TinyUSB
SRC += lib/tinyusb/src/common/tusb_fifo.c
SRC += lib/tinyusb/src/class/hid/hid_host.c
SRC += lib/tinyusb/src/host/hub.c
SRC += lib/tinyusb/src/host/usbh.c
SRC += lib/tinyusb/src/portable/raspberrypi/pio_usb/hcd_pio_usb.c
SRC += lib/tinyusb/src/tusb.c
VPATH += lib/tinyusb/src

# pico-sdk
SRC += lib/pico-sdk/src/host/pico_stdlib/stdlib.c
SRC += lib/pico-sdk/src/rp2_common/hardware_dma/dma.c
VPATH += lib/pico-sdk/src/common/pico_stdlib/include
VPATH += lib/pico-sdk/src/common/pico_sync/include
VPATH += lib/pico-sdk/src/common/pico_time/include
VPATH += lib/pico-sdk/src/rp2_common/hardware_dma/include
VPATH += lib/pico-sdk/src/rp2_common/hardware_uart/include
VPATH += lib/pico-sdk/src/rp2_common/pico_stdio/include
