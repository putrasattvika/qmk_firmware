# USB to USB Converter for Raspberry Pi Pico (RP2040)

Flash this firmware to an RP2040-based board and connect it between your
USB keyboard and your PC to make (almost) every keyboard fully programmable.
Compared to the [AVR-based USB-to-USB converter](../usb_usb/readme.md), this
variant supports Via and does not require a USB host shield.

This project is a reimplementation of sekigon-gonnoc's
[Keyboard Quantizer Mini](https://github.com/qmk/qmk_firmware/pull/20999).

- Keyboard Maintainer: [Putra Sattvika](https://github.com/putrasattvika)

- Hardware Supported: Self-built, requiring only an RP2040 board with at least
  2 GPIO pins. See [Build Instructions](#build-instructions).

- Hardware Availability: [RP2040 on Raspberry Pi's official website](https://www.raspberrypi.com/products/rp2040/)

Make example for this keyboard (after setting up your build environment):

```shell
qmk compile -kb converter/usb_usb_rp2040 -km default
```

Flashing example for this keyboard:

```shell
qmk flash -kb converter/usb_usb_rp2040 -km default
```

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools)
and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide)
for more information. Brand new to QMK? Start with our
[Complete Newbs Guide](https://docs.qmk.fm/#/newbs).


## Build Instructions

For this project you will need two things:
  - An RP2040 board with the 5V pin, GND pin, and 2 available GPIO pins.
    These GPIO pins have to be next to each other (e.g. GPIO0 and GPIO0,
    GPIO11 and GPIO12, GPIO28 and GPIO29, etc.). The default GPIO pins are
    GPIO0 and GPIO1, which can be changed by modifying the `config.h` file.

  - A way to connect your USB keyboard to those four pins on the RP2040. For
    example:
      - Get a USB breakout board and connect it to the RP2040, or
      - Strip the male end of the USB cable to expose the [four USB 2.0 wires](https://en.wikipedia.org/wiki/USB_hardware#Pinouts)
        (usually black for GND, red for VCC/5V, green for D+, and white for D-).
        Using an USB 2.0 extender cable is reccommended so you don't need to
        make modification to your keyboard's original cable.

Wire the board like this:
  - Connect the board's 5V pin to the USB VCC/5V pin
  - Connect the board's GND pin to the USB GND pin
  - Connect the board's GPIO0 pin to the USB D+ pin
  - Connect the board's GPIO1 pin to the USB D+ pin

Hold the board's `BOOTSEL` button while connecting it to your PC to
[enter the bootloader mode](#bootloader) and flash the board.


## Limitations

- The USB keyboard connected to the converter must support the USB HID boot
  protocol (i.e. 6KRO); NKRO-only keyboards might not work.

- The Pico-PIO-USB library used in this project uses both PIOs. Thus, device
  drivers implemented with PIO (e.g. WS2812 according to the
  [RP2040 platform documentation](https://docs.qmk.fm/platformdev_rp2040))
  cannot be used as there's no more free PIO.


## Bootloader

Enter the bootloader in 3 ways:
- **Physical reset button**. This differs between boards:
  - For the official [Raspberry Pi Pico](https://www.raspberrypi.com/products/raspberry-pi-pico/),
    disconnect the USB cable from the board, then hold the `BOOTSEL` button down
    during board power-up (e.g. hold `BOOTSEL` down while connecting the USB cable).

    See the "4.1. Programming the flash" section of the
    [datasheet](https://datasheets.raspberrypi.com/pico/pico-datasheet.pdf)
    for more information.

  - For third-party boards with both the `BOOTSEL` button and the `RESET` (or `RST`)
    buttons (such as the YD-RP2040 and the RP2040-Zero), hold the `BOOTSEL` button
    down and press the `RESET` button.

- **QMK command**. When you already have QMK flashed:
  - [Press the `RESET` button twice](https://docs.qmk.fm/platformdev_rp2040#double-tap)
  - Press `LSHIFT + RSHIFT + ESC` (see [Command](https://docs.qmk.fm/features/command#usage))

- **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available


## Resources & Acknowledgements
- [QMK Keyboard Quantizer Mini by sekigon-gonnoc](https://github.com/qmk/qmk_firmware/pull/20999)
- [The Pico-PIO-USB library by sekigon-gonnoc](https://github.com/sekigon-gonnoc/Pico-PIO-USB)
  - [host_hid_to_device_cdc example by Ha Thach and sekigon-gonnoc](https://github.com/sekigon-gonnoc/Pico-PIO-USB/blob/0.5.3/examples/host_hid_to_device_cdc/host_hid_to_device_cdc.c)
  - [QMK simple_split keyboard by sekigon-gonnoc](https://github.com/sekigon-gonnoc/qmk_firmware/tree/rp2040/keyboards/pico_pico_usb)
- [AVR variant of this project by Balz Guenat](../usb_usb/readme.md)
