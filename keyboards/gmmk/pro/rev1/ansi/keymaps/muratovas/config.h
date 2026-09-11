/* Copyright 2021 Andre Brait
 * Copyright 2021 MuratovAS 
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

// https://github.com/qmk/qmk_firmware/blob/master/docs/feature_debounce_type.md
// Used with DEBOUNCE_TYPE = asym_eager_defer_pk (see rules.mk): a key press is
// reported immediately, a release only after DEBOUNCE ms without changes.
// Raise this if a worn switch still produces double inputs (max. 127).
#define DEBOUNCE 15

// https://github.com/qmk/qmk_firmware/blob/master/docs/feature_rgb_matrix.md
#ifdef RGB_MATRIX_ENABLE

    // Steps for the RM_HUEU/RM_HUED, RM_SATU/RM_SATD and RM_VALU/RM_VALD keys.
    // Hue and saturation are 0-255, so the number of reachable colors is
    // 256 / STEP: with the default step of 8 that is only 32 hues.
    #define RGB_MATRIX_HUE_STEP 4   // 64 hues
    #define RGB_MATRIX_SAT_STEP 8   // 32 saturation levels (default: 16)
    
    // Turn the LEDs off after this much inactivity. Deliberately NOT QMK's own
    // RGB_MATRIX_TIMEOUT: that one drops the rendered effect to RGB_MATRIX_NONE,
    // and rgb_matrix_task() only calls rgb_matrix_indicators_user() when an
    // effect is running - the CAPS LOCK indicator would go dark with it. keymap.c
    // blacks the LEDs out itself instead, so the indicator survives.
    #define RGB_IDLE_TIMEOUT 2400000        // 40 minutes (40 * 60 * 1000ms)

    // Sleep on USB suspend (RGB_DISABLE_WHEN_USB_SUSPENDED in older QMK) is
    // already ON data-driven: "sleep": true in keyboards/gmmk/pro/info.json.

    // Must name one of the few effects kept below. The effect enum is generated
    // from whatever survives that list, so a mode index written to EEPROM by an
    // older firmware now points at a different effect - or past the end of the
    // list, where nothing renders at all. After flashing, clear the EEPROM once
    // (hold Escape while plugging the cable in).
    #define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE

    // ---- Effect selection -------------------------------------------------
    // Careful: keyboards/gmmk/pro/info.json turns on 43 animations data-driven,
    // and QMK's generated info_config.h is included BEFORE this file (CONFIG_H
    // in builddefs/build_keyboard.mk lists it first). Deleting a #define here
    // would remove nothing on its own - the board switches it back on. So every
    // effect this QMK version ships is listed below and turned off explicitly.
    //
    // The list is the single source of truth: an effect ends up in the firmware
    // only if its #undef is commented out. To drop one, uncomment its line; to
    // get one back, comment its line out again.
    // SOLID_COLOR is the one exception - it is always built in and cannot go.
    //
    // Kept right now: MULTISPLASH, SOLID_MULTISPLASH, SOLID_REACTIVE_MULTIWIDE.
    // All three are key-reactive; RGB_MATRIX_KEYPRESSES gets defined for them
    // automatically by quantum/rgb_matrix/post_config.h, nothing to do here.

    #undef ENABLE_RGB_MATRIX_ALPHAS_MODS
    #undef ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
    #undef ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
    #undef ENABLE_RGB_MATRIX_BAND_SAT
    #undef ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
    #undef ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
    #undef ENABLE_RGB_MATRIX_BAND_VAL
    #undef ENABLE_RGB_MATRIX_BREATHING
    #undef ENABLE_RGB_MATRIX_CYCLE_ALL
    #undef ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
    #undef ENABLE_RGB_MATRIX_CYCLE_OUT_IN
    #undef ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
    #undef ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
    #undef ENABLE_RGB_MATRIX_CYCLE_SPIRAL
    #undef ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
    #undef ENABLE_RGB_MATRIX_DIGITAL_RAIN
    #undef ENABLE_RGB_MATRIX_DUAL_BEACON
    #undef ENABLE_RGB_MATRIX_FLOWER_BLOOMING
    #undef ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
    #undef ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
    #undef ENABLE_RGB_MATRIX_HUE_BREATHING
    #undef ENABLE_RGB_MATRIX_HUE_PENDULUM
    #undef ENABLE_RGB_MATRIX_HUE_WAVE
    #undef ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
    //#undef ENABLE_RGB_MATRIX_MULTISPLASH
    #undef ENABLE_RGB_MATRIX_PIXEL_FLOW
    #undef ENABLE_RGB_MATRIX_PIXEL_FRACTAL
    #undef ENABLE_RGB_MATRIX_PIXEL_RAIN
    #undef ENABLE_RGB_MATRIX_RAINBOW_BEACON
    #undef ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
    #undef ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
    #undef ENABLE_RGB_MATRIX_RAINDROPS
    #undef ENABLE_RGB_MATRIX_RIVERFLOW
    //#undef ENABLE_RGB_MATRIX_SOLID_MULTISPLASH
    #undef ENABLE_RGB_MATRIX_SOLID_REACTIVE
    #undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
    #undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
    #undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
    //#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
    #undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
    #undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
    #undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
    #undef ENABLE_RGB_MATRIX_SOLID_SPLASH
    #undef ENABLE_RGB_MATRIX_SPLASH
    #undef ENABLE_RGB_MATRIX_STARLIGHT
    #undef ENABLE_RGB_MATRIX_STARLIGHT_DUAL_HUE
    #undef ENABLE_RGB_MATRIX_STARLIGHT_DUAL_SAT
    #undef ENABLE_RGB_MATRIX_STARLIGHT_SMOOTH
    #undef ENABLE_RGB_MATRIX_TYPING_HEATMAP
#endif
