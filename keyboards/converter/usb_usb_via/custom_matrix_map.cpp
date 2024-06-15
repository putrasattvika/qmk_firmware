/*
Copyright 2024 Putra Sattvika <sattvikaputra@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdint.h>

#include "keycode.h"

extern "C" {
    /*
     * Converts a USB HID keyboard scan code to the key's coordinate on the
     * matrix (as a pair of bytes). Returns 0xFFFF on unhandled key.
     */
    uint16_t scancode_to_matrix_rowcol(uint8_t scancode) {
        switch (scancode) {
        case KC_ESC:
            return 0 << 8 | 0;

        case KC_F1:
            return 0 << 8 | 1;

        case KC_F2:
            return 0 << 8 | 2;

        case KC_F3:
            return 0 << 8 | 3;

        case KC_F4:
            return 0 << 8 | 4;

        case KC_F5:
            return 0 << 8 | 5;

        case KC_F6:
            return 0 << 8 | 6;

        case KC_F7:
            return 0 << 8 | 7;

        case KC_F8:
            return 0 << 8 | 8;

        case KC_F9:
            return 0 << 8 | 9;

        case KC_F10:
            return 0 << 8 | 10;

        case KC_F11:
            return 0 << 8 | 11;

        case KC_F12:
            return 0 << 8 | 12;

        case KC_PSCR:
            return 0 << 8 | 13;

        case KC_SCRL:
            return 0 << 8 | 14;

        case KC_PAUS:
            return 0 << 8 | 15;

        case KC_GRV:
            return 1 << 8 | 0;

        case KC_1:
            return 1 << 8 | 1;

        case KC_2:
            return 1 << 8 | 2;

        case KC_3:
            return 1 << 8 | 3;

        case KC_4:
            return 1 << 8 | 4;

        case KC_5:
            return 1 << 8 | 5;

        case KC_6:
            return 1 << 8 | 6;

        case KC_7:
            return 1 << 8 | 7;

        case KC_8:
            return 1 << 8 | 8;

        case KC_9:
            return 1 << 8 | 9;

        case KC_0:
            return 1 << 8 | 10;

        case KC_MINS:
            return 1 << 8 | 11;

        case KC_EQL:
            return 1 << 8 | 12;

        case KC_BSPC:
            return 1 << 8 | 13;

        case KC_INS:
            return 1 << 8 | 14;

        case KC_HOME:
            return 1 << 8 | 15;

        case KC_PGUP:
            return 2 << 8 | 0;

        case KC_TAB:
            return 2 << 8 | 1;

        case KC_Q:
            return 2 << 8 | 2;

        case KC_W:
            return 2 << 8 | 3;

        case KC_E:
            return 2 << 8 | 4;

        case KC_R:
            return 2 << 8 | 5;

        case KC_T:
            return 2 << 8 | 6;

        case KC_Y:
            return 2 << 8 | 7;

        case KC_U:
            return 2 << 8 | 8;

        case KC_I:
            return 2 << 8 | 9;

        case KC_O:
            return 2 << 8 | 10;

        case KC_P:
            return 2 << 8 | 11;

        case KC_LBRC:
            return 2 << 8 | 12;

        case KC_RBRC:
            return 2 << 8 | 13;

        case KC_BSLS:
            return 2 << 8 | 14;

        case KC_DEL:
            return 2 << 8 | 15;

        case KC_END:
            return 3 << 8 | 0;

        case KC_PGDN:
            return 3 << 8 | 1;

        case KC_CAPS:
            return 3 << 8 | 2;

        case KC_A:
            return 3 << 8 | 3;

        case KC_S:
            return 3 << 8 | 4;

        case KC_D:
            return 3 << 8 | 5;

        case KC_F:
            return 3 << 8 | 6;

        case KC_G:
            return 3 << 8 | 7;

        case KC_H:
            return 3 << 8 | 8;

        case KC_J:
            return 3 << 8 | 9;

        case KC_K:
            return 3 << 8 | 10;

        case KC_L:
            return 3 << 8 | 11;

        case KC_SCLN:
            return 3 << 8 | 12;

        case KC_QUOT:
            return 3 << 8 | 13;

        case KC_ENT:
            return 3 << 8 | 14;

        case KC_LSFT:
            return 3 << 8 | 15;

        case KC_Z:
            return 4 << 8 | 0;

        case KC_X:
            return 4 << 8 | 1;

        case KC_C:
            return 4 << 8 | 2;

        case KC_V:
            return 4 << 8 | 3;

        case KC_B:
            return 4 << 8 | 4;

        case KC_N:
            return 4 << 8 | 5;

        case KC_M:
            return 4 << 8 | 6;

        case KC_COMM:
            return 4 << 8 | 7;

        case KC_DOT:
            return 4 << 8 | 8;

        case KC_SLSH:
            return 4 << 8 | 9;

        case KC_RSFT:
            return 4 << 8 | 10;

        case KC_UP:
            return 4 << 8 | 11;

        case KC_LCTL:
            return 4 << 8 | 12;

        case KC_LGUI:
            return 4 << 8 | 13;

        case KC_LALT:
            return 4 << 8 | 14;

        case KC_SPC:
            return 4 << 8 | 15;

        case KC_RALT:
            return 5 << 8 | 0;

        case KC_RGUI:
            return 5 << 8 | 1;

        case KC_RCTL:
            return 5 << 8 | 2;

        case KC_LEFT:
            return 5 << 8 | 3;

        case KC_DOWN:
            return 5 << 8 | 4;

        case KC_RGHT:
            return 5 << 8 | 5;

        default:
            break;
        }

        return 0xFFFF;
    }

    /*
     * Converts a USB HID keyboard modifier bits and its offset to the modifier's
     * coordinate on the matrix (as a pair of bytes). Returns 0xFFFF when no
     * modifier key is pressed.
     */
    uint16_t modifier_bit_to_matrix_rowcol(uint8_t mods, uint8_t idx) {
        // mods retains state of 8 modifiers:
        //
        //  bit |0       |1       |2       |3       |4       |5       |6       |7
        // -----+--------+--------+--------+--------+--------+--------+--------+--------
        // desc |Lcontrol|Lshift  |Lalt    |Lgui    |Rcontrol|Rshift  |Ralt    |Rgui

        uint8_t on = mods & 1 << idx;
        if (on == 0) {
            return 0xFFFF;
        }

        switch (idx) {
        case 0:
            return scancode_to_matrix_rowcol(KC_LCTL);

        case 1:
            return scancode_to_matrix_rowcol(KC_LSFT);

        case 2:
            return scancode_to_matrix_rowcol(KC_LALT);

        case 3:
            return scancode_to_matrix_rowcol(KC_LGUI);

        case 4:
            return scancode_to_matrix_rowcol(KC_RCTL);

        case 5:
            return scancode_to_matrix_rowcol(KC_RSFT);

        case 6:
            return scancode_to_matrix_rowcol(KC_RALT);

        case 7:
            return scancode_to_matrix_rowcol(KC_RGUI);

        default:
            break;
        }

        return 0xFFFF;
    }
}
