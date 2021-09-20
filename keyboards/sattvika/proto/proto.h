/* Copyright 2021 Putra Sattvika
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "quantum.h"

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */

// TODO: This is a layout only for the right hand
#define LAYOUT( \
    KL_00, KL_01, KL_02, KL_03,            KR_01, KR_02, KR_03, \
    KL_10, KL_11, KL_12,            KR_10, KR_11, KR_12, KR_13, \
    KL_20, KL_21, KL_22,            KR_20, KR_21, KR_22, KR_23  \
) { \
    { KL_00, KL_01, KL_02, KL_03 }, \
    { KL_10, KL_11, KL_12, KC_NO }, \
    { KL_20, KL_21, KL_22, KC_NO }, \
    { KC_NO, KR_01, KR_02, KR_03 }, \
    { KR_10, KR_11, KR_12, KR_13 }, \
    { KR_20, KR_21, KR_22, KR_23 }  \
}
