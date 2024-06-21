# Adapted from https://github.com/qmk/qmk_firmware/pull/20999/files#diff-a4cf8cf8185c9432397cafdc9fb1bc1abb2e67169cb09ebcd5f402573d8cb845

# Hardware
OPT_DEFS += -DCRT0_EXTRA_CORES_NUMBER=1
OPT_DEFS += -Wno-unused-function

# Keyboard
CUSTOM_MATRIX = yes
SRC += c1_main.c
SRC += ledc.c cusb_host.c
SRC += keyboard.c matrix.c

# Pico-PIO-USB library
SRC += lib/Pico-PIO-USB/src/pio_usb.c
SRC += lib/Pico-PIO-USB/src/pio_usb_host.c
SRC += lib/Pico-PIO-USB/src/usb_crc.c
VPATH += lib/Pico-PIO-USB/src

# TinyUSB library
SRC += lib/tinyusb/src/common/tusb_fifo.c
SRC += lib/tinyusb/src/class/hid/hid_host.c
SRC += lib/tinyusb/src/host/hub.c
SRC += lib/tinyusb/src/host/usbh.c
SRC += lib/tinyusb/src/portable/raspberrypi/pio_usb/hcd_pio_usb.c
SRC += lib/tinyusb/src/tusb.c
VPATH += lib/tinyusb/src

# Additional pico libraries
# SRC += lib/pico-sdk/src/common/pico_time/time.c # NOT NEEDED
# SRC += lib/pico-sdk/src/common/pico_util/pheap.c
SRC += lib/pico-sdk/src/host/pico_stdlib/stdlib.c
SRC += lib/pico-sdk/src/rp2_common/hardware_dma/dma.c
# SRC += lib/pico-sdk/src/rp2_common/hardware_sync/sync.c
SRC += lib/pico-sdk/src/rp2_common/pico_stdio/stdio.c
# SRC += lib/pico-sdk/src/common/pico_sync/mutex.c # NOT NEEDED
# SRC += lib/pico-sdk/src/rp2_common/hardware_irq/irq.c
VPATH += lib/pico-sdk/src/common/pico_stdlib/include
VPATH += lib/pico-sdk/src/common/pico_sync/include
VPATH += lib/pico-sdk/src/common/pico_time/include
# VPATH += lib/pico-sdk/src/common/pico_util/include
VPATH += lib/pico-sdk/src/rp2_common/hardware_dma/include
VPATH += lib/pico-sdk/src/rp2_common/hardware_uart/include
VPATH += lib/pico-sdk/src/rp2_common/pico_stdio/include
# VPATH += lib/pico-sdk/src/rp2_common/hardware_irq/include
# VPATH += lib/pico-sdk/src/common/pico_binary_info/include
