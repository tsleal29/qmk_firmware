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

#include QMK_KEYBOARD_H
#include "keychron_common.h"

#define MC_LCK  C(G(KC_Q))  // Lock screen
#define MC_SELA LSG(KC_L)   // Select all occurrences
#define MC_LEND LSA(KC_I)   // Add cursor to line ends
#define MC_SELN G(KC_L)     // Select line
#define MC_DELN LSG(KC_K)   // Delete line
#define MC_UTAB S(KC_TAB)   // Untab
#define MC_SAVE G(KC_S)     // Save
#define MC_UNDO G(KC_Z)     // Undo
#define MC_REDO LSG(KC_Z)   // Redo
#define MC_CUT  G(KC_X)     // Cut
#define MC_COPY G(KC_C)     // Copy
#define MC_PAST G(KC_V)     // Paste
#define MC_CLIP LSG(KC_V)   // Open clipboard history
#define MC_COMT G(KC_SLSH)  // Comment line

enum layers {
    BASE,
    FN,
    L2,
    MACRO,
};
// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_tenkey_27(
        KC_MUTE,   KC_ESC, TO(MACRO), KC_BSPC, KC_DEL,
        TO(MACRO), KC_NUM, KC_PSLS,   KC_PAST, KC_PMNS,
        KC_NO,     KC_P7,  KC_P8,	  KC_P9,   KC_PPLS,
        KC_NO,	   KC_P4,  KC_P5,	  KC_P6,
        KC_NO,	   KC_P1,  KC_P2,	  KC_P3,   KC_PENT,
        MO(FN),    KC_P0,             KC_PDOT          ),

    [FN] = LAYOUT_tenkey_27(
        RGB_TOG, BT_HST1,  BT_HST2, BT_HST3, P2P4G,
        _______, RGB_MOD,  RGB_VAI, RGB_HUI, _______,
        _______, RGB_RMOD, RGB_VAD, RGB_HUD, _______,
        _______, RGB_SAI,  RGB_SPI, KC_MPRV,
        _______, RGB_SAD,  RGB_SPD, KC_MPLY, _______,
        _______, RGB_TOG,           KC_MNXT          ),

    [L2] = LAYOUT_tenkey_27(
        _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______, _______, _______,
        _______, _______,          _______          ),

    [MACRO] = LAYOUT_tenkey_27(
        KC_NO,    KC_ESC,  TO(BASE), KC_BSPC, KC_DEL,
        KC_NO,    KC_NO,   KC_NO,    KC_NO,   KC_NO,
        MC_SELA,  MC_UTAB, KC_TAB,   KC_NO,   MC_SAVE,
        MC_LEND,  MC_UNDO, MC_REDO,  KC_NO,
        MC_SELN,  MC_CUT,  MC_COPY,  MC_PAST, KC_PENT,
        MC_DELN,  MC_CLIP,           MC_COMT          )
};

// clang-format on
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [BASE]  = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [FN]    = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    [L2]    = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [MACRO] = {ENCODER_CCW_CW(KC_NO, KC_NO)},
};
#endif // ENCODER_MAP_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_keychron_common(keycode, record)) {
        return false;
    }
    return true;
}
