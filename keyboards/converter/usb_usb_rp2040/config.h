// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// Where the USB data pins are connected to the board. Note that due technical
// limitations, the USB Data− pin has to be connected directly on the next pin
// after the Data+ pin (i.e. USB_DEVICE_DATAPLUS_PIN + 1).
//
// For example, if USB_DEVICE_DATAPLUS_PIN is 0, then connect:
//   - USB Data+ pin to GPIO0
//   - USB Data- pin to GPIO1
#define USB_DEVICE_DATAPLUS_PIN 0
// #define USB_DEVICE_DATAPLUS_PIN 18

// Size of the virtual matrix
#define MATRIX_ROWS 16
#define MATRIX_COLS 16
