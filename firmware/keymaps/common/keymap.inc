// SPDX-License-Identifier: GPL-2.0-or-later

/*
 *
 * +-------+-------+-------+-------+
 * |  ENC  |  SW1  |  SW2  |  SW3  |
 * | press |  F13  |  F14  |  F15  |
 * +-------+-------+-------+-------+
 * |  SW4  |  SW5  |  SW6  |  SW7  |
 * |  F16  |  F17  |  F18  |  F19  |
 * +-------+-------+-------+-------+
 * |  SW8  |  SW9  | SW10  | SW11  |
 * |  F20  |  F21  |  F22  |  F23  |
 * +-------+-------+-------+-------+
 *
 * Encoder turn: CCW = volume down, CW = volume up.
 * Hold its press switch to use the RGB-control layer.
 */

#include QMK_KEYBOARD_H

enum layer_names {
    _BASE,
    _RGB,
    _USER_1,
    _USER_2,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        MO(_RGB),
        KC_F13, KC_F14, KC_F15,
        KC_F16, KC_F17, KC_F18, KC_F19,
        KC_F20, KC_F21, KC_F22, KC_F23
    ),
    [_RGB] = LAYOUT(
        KC_TRNS,
        RM_TOGG, RM_PREV, RM_NEXT,
        RM_HUED, RM_HUEU, RM_SATD, RM_SATU,
        RM_VALD, RM_VALU, QK_BOOT, QK_CLEAR_EEPROM
    ),
    [_USER_1] = LAYOUT(
        KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [_USER_2] = LAYOUT(
        KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE]   = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_RGB]    = { ENCODER_CCW_CW(RM_VALD, RM_VALU) },
    [_USER_1] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [_USER_2] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
};
#endif

#if defined(RGB_MATRIX_ENABLE)
// LEDs 1-5 are the LED bar. The remaining 11 LEDs are associated with switch matrix positions in keyboard.json.

bool rgb_matrix_indicators_user(void) {
    const uint8_t brightness = rgb_matrix_get_val();
    const uint8_t lit = (uint16_t)(brightness * 5U + RGB_MATRIX_MAXIMUM_BRIGHTNESS - 1U) / RGB_MATRIX_MAXIMUM_BRIGHTNESS;

    for (uint8_t led = 0; led < 5; led++) {
        rgb_matrix_set_color(led, 0, led < lit ? brightness : 0, 0);
    }
    return false;
}
#endif
