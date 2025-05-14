/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

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

#pragma once

/* Select hand configuration */
#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

// Enable SPLIT_MODS_ENABLE to ensure both halves receive the same mod state
#define SPLIT_MODS_ENABLE

// Allow the current layer to be synced between the halves
#define SPLIT_LAYER_STATE_ENABLE

// Allow caps lock and other LED states to be synced between halves
#define SPLIT_LED_STATE_ENABLE

// Enable serial communication between halves on pin D2
#define USE_SERIAL_PD2

// Setting for tapping term (time window to determine tap vs hold)
#define TAPPING_TERM 180

// Mouse key settings for smoother cursor movement
#define MOUSEKEY_INTERVAL 20
#define MOUSEKEY_DELAY 0
#define MOUSEKEY_MAX_SPEED 8
#define MOUSEKEY_TIME_TO_MAX 60
#define MOUSEKEY_WHEEL_INTERVAL 100
#define MOUSEKEY_WHEEL_MAX_SPEED 40
#define MOUSEKEY_WHEEL_TIME_TO_MAX 40
#define MOUSEKEY_WHEEL_DELAY 400

// Only need to tap twice to toggle a TT layer
#define TAPPING_TOGGLE 2

// Use variable combo timing for different combinations
#define COMBO_TERM_PER_COMBO

// Disable RGB features
#ifdef RGBLIGHT_ENABLE
    #undef RGBLIGHT_ENABLE
#endif

#ifdef RGB_MATRIX_ENABLE
    #undef RGB_MATRIX_ENABLE
#endif

// Force-disable RGB matrix even if enabled at the keyboard level
#define RGB_MATRIX_DISABLE_KEYCODES
