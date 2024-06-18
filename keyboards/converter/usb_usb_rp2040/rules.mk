# Adapted from https://github.com/qmk/qmk_firmware/pull/20999/files#diff-a4cf8cf8185c9432397cafdc9fb1bc1abb2e67169cb09ebcd5f402573d8cb845

# Hardware
OPT_DEFS += -DCRT0_EXTRA_CORES_NUMBER=1

# Keyboard
CUSTOM_MATRIX = yes
SRC += c1_main.c
SRC += ledc.c cmailbox.c
SRC += keyboard.c usb_host.c matrix.c

# Additional pico libraries
SRC += lib/pico-sdk/src/host/pico_stdlib/stdlib.c
VPATH += lib/pico-sdk/src/common/pico_stdlib/include
VPATH += lib/pico-sdk/src/common/pico_time/include
VPATH += lib/pico-sdk/src/rp2_common/pico_stdio/include
VPATH += lib/pico-sdk/src/rp2_common/hardware_uart/include
