/* Copyright 2024 @ Keychron (https://www.keychron.com)
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

#ifdef RGB_MATRIX_ENABLE
/* RGB Matrix driver configuration */
#    define DRIVER_COUNT 1
#    define RGB_MATRIX_LED_COUNT 26

#    define SPI_SCK_PIN A5
#    define SPI_MISO_PIN A6
#    define SPI_MOSI_PIN A7

#    define DRIVER_CS_PINS \
        { A3 }
#    define SNLED23751_SPI_DIVISOR 16
#    define SPI_DRIVER SPID1

/* Scan phase of led driver set as MSKPHASE_12CHANNEL(defined as 0x03 in snled27351.h) */
#    define SNLED27351_PHASE_CHANNEL MSKPHASE_12CHANNEL

/* Set LED driver current */
#    define SNLED27351_CURRENT_TUNE \
	{ 0x9A, 0x9A, 0x9A, 0x9A, 0x9A, 0x9A, 0x9A, 0x9A, 0x9A, 0x9A, 0x9A, 0x9A }

/* Allow shutdown of led driver to save power */
#    define RGB_MATRIX_DRIVER_SHUTDOWN_ENABLE
/* Set to infinit, which is use in USB mode by default */
#    define RGB_MATRIX_TIMEOUT RGB_MATRIX_TIMEOUT_INFINITE

/* Turn off backlight on low brightness to save power */
#    define RGB_MATRIX_BRIGHTNESS_TURN_OFF_VAL 32

/* Indications */
#    define NUM_LOCK_INDEX	        5
#    define HOMING_KEY_INDEX            16
#    define MACRO_LAYER_INDEX           16
#    define BORDER_LED_LIST             { 0, 1, 2, 3, 4, 8, 9, 13, 14, 18, 22, 23, 24, 25 }
#    define BORDER_LED_LIST_SIZE        14
#    define LOW_BAT_IND_INDEX           { 23 }
#    define BAT_LEVEL_LED_LIST          { 23, 18, 14, 9, 4 }
#    define BAT_LEVEL_LED_LIST_SIZE     5  // size of BAT_LEVEL_LED_LIST
#    define BAT_LEVEL_STEP              20 // 100 / BAT_LEVEL_LED_LIST_SIZE
#    define BAT_LEVEL_ANIMATION_NO_CLEAR_ALL

/* Default animation */
#    define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_CUSTOM_homing_keys_bkg
#    define RGB_MATRIX_DEFAULT_HUE  168

#    define RGB_MATRIX_KEYPRESSES
#    define RGB_MATRIX_FRAMEBUFFER_EFFECTS

#    define BOOTMAGIC_LITE_ROW 0
#    define BOOTMAGIC_LITE_COLUMN 1

#endif
