/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>
   Copyright 2021 Andre Brait <andrebrait@gmail.com>
   Copyright 2021 MuratovAS 
   
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

#include QMK_KEYBOARD_H

// https://github.com/qmk/qmk_firmware/blob/master/docs/feature_macros.md
enum custom_keycodes {
    KC_PSCR_LINUX,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    // To put the keyboard in bootloader mode, use FN+backslash. If you accidentally put it into bootloader, you can just unplug the USB cable and
    // it'll be back to normal when you plug it back in.
    //
    // This keyboard defaults to 6KRO instead of NKRO for compatibility reasons (some KVMs and BIOSes are incompatible with NKRO).
    // Since this is, among other things, a "gaming" keyboard, a key combination to enable NKRO on the fly is provided for convenience.
    // Press Fn+N to toggle between 6KRO and NKRO. This setting is persisted to the EEPROM and thus persists between restarts.
    //
    // https://github.com/qmk/qmk_firmware/blob/master/docs/keycodes.md
    
    [0] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR_LINUX,    KC_MEDIA_PLAY_PAUSE,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_DEL,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_INS,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_HOME,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_END,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(1),   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [1] = LAYOUT(
        _______, KC_MYCM, KC_WHOM, KC_CALC, KC_MSEL, KC_MPRV, KC_MNXT, KC_MPLY, KC_MSTP, _______, _______, _______, _______, KC_PSCR,          KC_MUTE,
        _______, RGB_TOG, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          KC_DEL,
        _______, _______, RGB_VAI, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RESET,            KC_INS,
        _______, _______, RGB_VAD, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          KC_PGUP,
        _______,          RGB_HUD, RGB_HUI, _______, _______, _______, NK_TOGG, _______, _______, _______, _______,          _______, RGB_MOD, KC_PGDN,
        _______, _______, _______,                            _______,                            _______, _______, _______, RGB_SPD, RGB_RMOD, RGB_SPI
    ),


};
// clang-format on

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    switch (biton32(layer_state)) {
    case 1:
        if (clockwise) {
          tap_code(KC_MNXT);
        } else {
          tap_code(KC_MPRV);
        }
        break;
    default:
        if (clockwise) {
          tap_code(KC_VOLU);
        } else {
          tap_code(KC_VOLD);
        }
        break;
    }
    return true;
}
#endif // ENCODER_ENABLE


#ifdef RGB_MATRIX_ENABLE
    #ifndef RGB_CONFIRMATION_BLINKING_TIME
        #define RGB_CONFIRMATION_BLINKING_TIME 1000 // 1 seconds
    #endif
#endif // RGB_MATRIX_ENABLE


#ifdef RGB_MATRIX_ENABLE

/* Renaming those to make the purpose on this keymap clearer */
#define LED_FLAG_CAPS LED_FLAG_NONE
#define LED_FLAG_EFFECTS LED_FLAG_INDICATOR

static void set_rgb_caps_leds(void);

#if RGB_CONFIRMATION_BLINKING_TIME > 0
static uint16_t effect_started_time = 0;
static uint8_t r_effect = 0x0, g_effect = 0x0, b_effect = 0x0;
static void start_effects(void);

/* The higher this is, the slower the blinking will be */
#ifndef TIME_SELECTED_BIT
    #define TIME_SELECTED_BIT 8
#endif
#if TIME_SELECTED_BIT < 0 || TIME_SELECTED_BIT >= 16
    #error "TIME_SELECTED_BIT must be a positive integer smaller than 16"
#endif
#define effect_red() r_effect = 0xFF, g_effect = 0x0, b_effect = 0x0
#define effect_green() r_effect = 0x0, g_effect = 0xFF, b_effect = 0x0
#endif // RGB_CONFIRMATION_BLINKING_TIME > 0

bool led_update_user(led_t led_state) {
    if (led_state.caps_lock) {
        if (!rgb_matrix_is_enabled()) {
            /* Turn ON the RGB Matrix for CAPS LOCK */
            rgb_matrix_set_flags(LED_FLAG_CAPS);
            rgb_matrix_enable();
        }
    } else if (rgb_matrix_get_flags() == LED_FLAG_CAPS) {
        /* RGB Matrix was only ON because of CAPS LOCK. Turn it OFF. */
        rgb_matrix_set_flags(LED_FLAG_ALL);
        rgb_matrix_disable();
    }
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_PSCR_LINUX:
        if (record->event.pressed) {
            // when keycode is pressed
            SEND_STRING(SS_DOWN(X_LSFT) SS_DOWN(X_LCTL) SS_TAP(X_PSCR) SS_UP(X_LSFT) SS_UP(X_LCTL));
        } else {
            // when keycode is released
        }
        break;
    #ifdef NKRO_ENABLE
    #if RGB_CONFIRMATION_BLINKING_TIME > 0
        case NK_TOGG:
            if (record->event.pressed) {
                if (keymap_config.nkro) {
                    /* Turning NKRO OFF */
                    effect_red();
                } else {
                    /* Turning NKRO ON */
                    effect_green();
                }
                start_effects();
            }
            break;
        case NK_ON:
            if (record->event.pressed) {
                if (!keymap_config.nkro) {
                    /* Turning NKRO ON */
                    effect_green();
                    start_effects();
                }
            }
            break;
        case NK_OFF:
            if (record->event.pressed) {
                if (keymap_config.nkro) {
                    /* Turning NKRO OFF */
                    effect_red();
                    start_effects();
                }
            }
            break;
    #endif // RGB_CONFIRMATION_BLINKING_TIME > 0
    #endif // NKRO_ENABLE
        case RGB_MOD:
        case RGB_RMOD:
        case RGB_HUI:
        case RGB_HUD:
        case RGB_SAI:
        case RGB_SAD:
        case RGB_VAI:
        case RGB_VAD:
        case RGB_SPI:
        case RGB_SPD:
            if (record->event.pressed) {
                if (rgb_matrix_get_flags() != LED_FLAG_ALL) {
                    /* Ignore changes to RGB settings while only it's supposed to be OFF */
                    return false;
                }
            }
            break;
        case RGB_TOG:
            if (record->event.pressed) {
                if (rgb_matrix_is_enabled()) {
                    switch (rgb_matrix_get_flags()) {
                        #if RGB_CONFIRMATION_BLINKING_TIME > 0
                        case LED_FLAG_EFFECTS:
                        #endif
                        case LED_FLAG_CAPS:
                            /* Turned ON because of EFFECTS or CAPS, is actually OFF */
                            /* Change to LED_FLAG_ALL to signal it's really ON */
                            rgb_matrix_set_flags(LED_FLAG_ALL);
                            /* Will be re-enabled by the processing of the toggle */
                            rgb_matrix_disable_noeeprom();
                            break;
                        case LED_FLAG_ALL:
                            /* Is actually ON */
                            #if RGB_CONFIRMATION_BLINKING_TIME > 0
                            if (effect_started_time > 0) {
                                /* Signal EFFECTS */
                                rgb_matrix_set_flags(LED_FLAG_EFFECTS);
                                /* Will be re-enabled by the processing of the toggle */
                                rgb_matrix_disable_noeeprom();
                            } else
                            #endif
                            if (host_keyboard_led_state().caps_lock) {
                                /* Signal CAPS */
                                rgb_matrix_set_flags(LED_FLAG_CAPS);
                                /* Will be re-enabled by the processing of the toggle */
                                rgb_matrix_disable_noeeprom();
                            }
                            break;
                    }
                }
            }
            break;
    }
    return true;
}


void rgb_matrix_indicators_user() {
    #if RGB_CONFIRMATION_BLINKING_TIME > 0
    if (effect_started_time > 0) {
        /* Render blinking EFFECTS */
        uint16_t deltaTime = sync_timer_elapsed(effect_started_time);
        if (deltaTime <= RGB_CONFIRMATION_BLINKING_TIME) {
            uint8_t led_state = ((~deltaTime) >> TIME_SELECTED_BIT) & 0x01;
            uint8_t val_r = led_state * r_effect;
            uint8_t val_g = led_state * g_effect;
            uint8_t val_b = led_state * b_effect;
            rgb_matrix_set_color_all(val_r, val_g, val_b);
            if (host_keyboard_led_state().caps_lock) {
                set_rgb_caps_leds();
            }
            return;
        } else {
            /* EFFECTS duration is finished */
            effect_started_time = 0;
            if (rgb_matrix_get_flags() == LED_FLAG_EFFECTS) {
                /* It was turned ON because of EFFECTS */
                if (host_keyboard_led_state().caps_lock) {
                    /* CAPS is still ON. Demote to CAPS */
                    rgb_matrix_set_flags(LED_FLAG_CAPS);
                } else {
                    /* There is nothing else keeping RGB enabled. Reset flags and turn if off. */
                    rgb_matrix_set_flags(LED_FLAG_ALL);
                    rgb_matrix_disable_noeeprom();
                }
            }
        }
    }
    #endif // RGB_CONFIRMATION_BLINKING_TIME > 0
    if (rgb_matrix_get_flags() == LED_FLAG_CAPS) {
        rgb_matrix_set_color_all(0x0, 0x0, 0x0);
    }
    if (host_keyboard_led_state().caps_lock) {
        set_rgb_caps_leds();
    }
}

#if RGB_CONFIRMATION_BLINKING_TIME > 0
static void start_effects() {
    effect_started_time = sync_timer_read();
    if (!rgb_matrix_is_enabled()) {
        /* Turn it ON, signal the cause (EFFECTS) */
        rgb_matrix_set_flags(LED_FLAG_EFFECTS);
        rgb_matrix_enable_noeeprom();
    } else if (rgb_matrix_get_flags() == LED_FLAG_CAPS) {
        /* It's already ON, promote the cause from CAPS to EFFECTS */
        rgb_matrix_set_flags(LED_FLAG_EFFECTS);
    }
}
#endif // RGB_CONFIRMATION_BLINKING_TIME > 0

static void set_rgb_caps_leds() {
    rgb_matrix_set_color(67, 0xFF, 0x0, 0x0); // Left side LED 1
    rgb_matrix_set_color(68, 0xFF, 0x0, 0x0); // Right side LED 1
    rgb_matrix_set_color(70, 0xFF, 0x0, 0x0); // Left side LED 2
    rgb_matrix_set_color(71, 0xFF, 0x0, 0x0); // Right side LED 2
    rgb_matrix_set_color(73, 0xFF, 0x0, 0x0); // Left side LED 3
    rgb_matrix_set_color(74, 0xFF, 0x0, 0x0); // Right side LED 3
    rgb_matrix_set_color(76, 0xFF, 0x0, 0x0); // Left side LED 4
    rgb_matrix_set_color(77, 0xFF, 0x0, 0x0); // Right side LED 4
    rgb_matrix_set_color(80, 0xFF, 0x0, 0x0); // Left side LED 5
    rgb_matrix_set_color(81, 0xFF, 0x0, 0x0); // Right side LED 5
    rgb_matrix_set_color(83, 0xFF, 0x0, 0x0); // Left side LED 6
    rgb_matrix_set_color(84, 0xFF, 0x0, 0x0); // Right side LED 6
    rgb_matrix_set_color(87, 0xFF, 0x0, 0x0); // Left side LED 7
    rgb_matrix_set_color(88, 0xFF, 0x0, 0x0); // Right side LED 7
    rgb_matrix_set_color(91, 0xFF, 0x0, 0x0); // Left side LED 8
    rgb_matrix_set_color(92, 0xFF, 0x0, 0x0); // Right side LED 8
    rgb_matrix_set_color(3, 0xFF, 0x0, 0x0); // CAPS LED
}

#endif // RGB_MATRIX_ENABLE