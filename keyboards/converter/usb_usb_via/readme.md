# USB to USB keyboard protocol converter (with Via Support)

A small device to connect between your USB keyboard and your PC that makes (almost)
every TKL (or smaller) keyboard fully programmable, now with Via support. Original
code from the [TMK firmware](https://github.com/tmk/tmk_keyboard/tree/master/converter/usb_usb).
[Original QMK port](https://github.com/qmk/qmk_firmware/tree/master/keyboards/converter/usb_usb/)
by [Balz Guenat](https://github.com/BalzGuenat). Adjusted for Via support by
[Putra Sattvika](https://github.com/putrasattvika).

Keyboard Maintainer: [Putra Sattvika](https://github.com/putrasattvika)
Hardware Supported: [Arduino Leonardo + USB Host Shield](https://geekhack.org/index.php?topic=80421.0), maybe more
Hardware Availability: Self-built

Make example for this keyboard (after setting up your build environment):

```
qmk compile -kb converter/usb_usb_via/leonardo -km via
```

See [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools)
then the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide)
for more information.

Note that you have to choose the right hardware variant as your subproject,
otherwise you will probably have issues.


## Via JSON

> TODO: Move this to Via's repository
```json
{
  "name": "QMK USB to USB Converter",
  "vendorId": "0xFFFE",
  "productId": "0x005B",

  "matrix": { "rows": 6, "cols": 16 },

  "layouts": {
    "keymap": [
        ["0, 0",{"x":1},"0, 1","0, 2","0, 3","0, 4",{"x":0.5},"0, 5","0, 6","0, 7","0, 8",{"x":0.5},"0, 9","0, 10","0, 11","0, 12",{"x":0.25},"0, 13","0, 14","0, 15"],
        [{"y":0.25},"1, 0","1, 1","1, 2","1, 3","1, 4","1, 5","1, 6","1, 7","1, 8","1, 9","1, 10","1, 11","1, 12",{"w":2},"1, 13",{"x":0.25},"1, 14","1, 15","2, 0"],
        [{"w":1.5},"2, 1","2, 2","2, 3","2, 4","2, 5","2, 6","2, 7","2, 8","2, 9","2, 10","2, 11","2, 12","2, 13",{"w":1.5},"2, 14",{"x":0.25},"2, 15","3, 0","3, 1"],
        [{"w":1.75},"3, 2","3, 3","3, 4","3, 5","3, 6","3, 7","3, 8","3, 9","3, 10","3, 11","3, 12","3, 13",{"w":2.25},"3, 14"],
        [{"w":2.25},"3, 15","4, 0","4, 1","4, 2","4, 3","4, 4","4, 5","4, 6","4, 7","4, 8","4, 9",{"w":2.75},"4, 10",{"x":1.25},"4, 11"],
        [{"w":1.25},"4, 12",{"w":1.25},"4, 13",{"w":1.25},"4, 14",{"w":6.25},"4, 15",{"w":1.25},"5, 0",{"w":1.25},"5, 1",{"x":1.25,"w":1.25},"5, 2",{"x":0.25},"5, 3","5, 4","5, 5"]
    ]
  }
}
```


## Limitations

This variant of the USB-to-USB converter only supports TKL or smaller keyboards
because we're limited by atmega32u4's EEPROM size.

The limitations of the original port still applies, e.g. it only supports
'HID Boot protocol' (i.e. no NKRO).


## Resources
- [The original QMK port of the converter by Balz Guenat](https://github.com/qmk/qmk_firmware/tree/master/keyboards/converter/usb_usb/)
