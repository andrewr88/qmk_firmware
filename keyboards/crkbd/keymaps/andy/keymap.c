/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

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
#include "version.h"
#include "swapper.h"
#include "transactions.h"
#include "customkeys.h"
#include "oneshot.h"
#include <stdio.h>

enum layers {
    _BASE,    // default layer
    _SYMB,    // symbols
    _NUM,     // numbers
    _FUN,     // fn keys
    _NAV,     // navigation keys
    _NAVWIN,  // navigation keys for my macOS global shortcuts between windows
    _NAVLH,   // navigation keys but sort of mirrored so that arrows are on the LH
    _MDIA,    // media keys
};

#define LT_NAV_SPACE LT(_NAV, KC_SPC)
#define LT_MDIA_O LT(_MDIA, KC_O)
#define MO_NAV MO(_NAV)
#define OSL_NAVWIN OSL(_NAVWIN)
#define MO_FUN MO(_FUN)
#define MO_NUM MO(_NUM)
#define MO_SYMB MO(_SYMB)

// The number of per-key LEDs on each side of a 6-column Corne.
#define NUM_LEDS_PER_SIDE 23

// keyboards/crkbd/rev4_1/rev4_1.c has a hard-coded g_led_config with 23 LEDs, so we
// have to work around this.
#define NUM_LEDS_PER_SIDE_ON_NORMAL_CORNE 23

// The LEDs are so bright on the Corne, so we set the intensity pretty low.
#define LED_INTENSITY 0x16

// Define the usual colors using the desired LED_INTENSITY defined above.
#define RGB_DARK_BLUE 0x00, 0x00, LED_INTENSITY
#define RGB_DARK_CYAN 0x00, LED_INTENSITY, LED_INTENSITY
#define RGB_DARK_GREEN 0x00, LED_INTENSITY, 0x00
#define RGB_DARK_MAGENTA LED_INTENSITY, 0x00, LED_INTENSITY
#define RGB_DARK_RED LED_INTENSITY, 0x00, 0x00
#define RGB_DARK_WHITE LED_INTENSITY, LED_INTENSITY, LED_INTENSITY
#define RGB_DARK_YELLOW LED_INTENSITY, LED_INTENSITY, 0x00

enum combos { NEI_CTRL, COMMADOT_SEMICOLON, HCOMMA_HYPHEN, ZD_TAB, XD_CTRL, DH_CTRL, PREV_NEXT_SELECT_ALL, COMBO_LENGTH };
uint16_t COMBO_LEN = COMBO_LENGTH;

const uint16_t PROGMEM nei_ctrl[]              = {KC_N, KC_E, KC_I, COMBO_END};
const uint16_t PROGMEM commadot_semicolon[]    = {KC_COMM, KC_DOT, COMBO_END};
const uint16_t PROGMEM hcomma_hyphen[]         = {KC_H, KC_COMM, COMBO_END};
const uint16_t PROGMEM xd_ctrl[]               = {KC_X, KC_D, COMBO_END};
const uint16_t PROGMEM dh_ctrl[]               = {KC_D, KC_H, COMBO_END};
const uint16_t PROGMEM zd_tab[]                = {KC_Z, KC_D, COMBO_END};
const uint16_t PROGMEM prev_next_select_all[]  = {PRV_TAB, NXT_TAB, COMBO_END};

// clang-format off
combo_t key_combos[] = {
    [NEI_CTRL]          = COMBO(nei_ctrl, OS_CTRL),
    [COMMADOT_SEMICOLON]= COMBO(commadot_semicolon, KC_SCLN),
    [HCOMMA_HYPHEN]     = COMBO(hcomma_hyphen, KC_MINS),
    [XD_CTRL]           = COMBO(xd_ctrl, OS_CTRL),
    [DH_CTRL]           = COMBO(dh_ctrl, OS_CTRL),
    [ZD_TAB]            = COMBO(zd_tab, KC_TAB),
    [PREV_NEXT_SELECT_ALL] = COMBO(prev_next_select_all, MW_SELECT_ALL),
};
// clang-format on

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_split_3x6_3_ex2(
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_PSCR,    KC_HOME,  KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_QUOT,
        KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_END,     KC_INS,   KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, LT_MDIA_O,
        KC_DEL,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                          KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_SLSH,
                 MO_FUN,  LT_NAV_SPACE, MO_NUM,                                     OS_SHFT,     MO_NAV,   MO_SYMB
    ),

    [_SYMB] = LAYOUT_split_3x6_3_ex2(
        KC_ESC,  KC_MINS, S(KC_MINS), KC_EQL,       S(KC_EQL), KC_BSLS, KC_PSCR,    KC_HOME,  KC_INS,  MW_UNDO, S(KC_7),    S(KC_8),   KC_DOT,  MW_PSTE,
        KC_TAB,  KC_QUOT, S(KC_QUOT), KC_LEFT_ENCLOSE, KC_RIGHT_ENCLOSE, KC_GRV, KC_END,     KC_INS,   KC_PGUP, REV_COLON, OS_SHFT,    OS_CTRL,  OS_ALT,  OS_GUI,
        KC_DEL,  KC_SCLN, S(KC_SCLN), KC_LBRC,      KC_RBRC,   KC_3GRV, KC_PGDN,    KC_MINS,  S(KC_1), S(KC_COMM), S(KC_DOT), S(KC_SLSH),
                                        _______,     _______,   KC_ENT,              _______,   _______, _______
    ),

    [_NUM] = LAYOUT_split_3x6_3_ex2(
        KC_ESC,  KC_TAB,  KC_LEFT,  KC_DOT,   KC_RGHT, S(KC_MINS), KC_PSCR,    KC_HOME,  KC_INS,  VSC_EVAL, KC_7, KC_8, KC_9, S(KC_EQL),
        KC_TAB,  OS_GUI,  OS_ALT,   OS_CTRL,  OS_SHFT, MO_NAV,     KC_END,     KC_INS,   KC_PGUP, REV_COLON, KC_4, KC_5, KC_6, KC_MINS,
        KC_DEL,  MW_UNDO, _______,  KC_COMM,  REV_COLON, MW_REDO,  KC_PGDN,    KC_MINS,  KC_1,    KC_2,     KC_3, _______,
                      _______,      _______,   _______,             KC_ENT,     KC_BSPC,  KC_0
    ),

    [_FUN] = LAYOUT_split_3x6_3_ex2(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_PSCR,    KC_HOME,  KC_INS,  TO(_NAVLH), KC_F7, KC_F8, KC_F9, KC_F12,
        KC_TAB,  OS_GUI,  OS_ALT,  OS_CTRL, OS_SHFT, _______, KC_END,     KC_INS,   KC_PGUP, _______,    KC_F4, KC_F5, KC_F6, KC_F11,
        KC_DEL,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_PGDN,    _______,  KC_F1,   KC_F2,     KC_F3, KC_F10,
                      _______,      _______, _______,          _______,    KC_CAPS,  _______
    ),

    [_NAV] = LAYOUT_split_3x6_3_ex2(
        KC_ESC,  SW_WIN,  PRV_TAB, CLS_WIN, NXT_TAB, SW_APP,    KC_PSCR,    KC_HOME,  KC_INS,  KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_DWRD,
        KC_TAB,  OS_GUI,  OS_ALT,  OS_CTRL, OS_SHFT, OSL_NAVWIN, KC_END,     KC_INS,   KC_PGUP, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_SPC,
        KC_DEL,  MW_UNDO, MW_CUT,  MW_COPY, MW_PSTE, MW_REDO,   KC_PGDN,    KC_ESC,   KC_BSPC, KC_ENT,  KC_TAB,  KC_DEL,
                     MW_MKLNK,     _______, MW_NWTB,            KC_ENT,     KC_BSPC,  _______
    ),

    [_NAVWIN] = LAYOUT_split_3x6_3_ex2(
        KC_ESC,  A(KC_Q), A(KC_W), A(KC_F), A(KC_P), A(KC_B),    KC_PSCR,    KC_HOME,  KC_INS,  A(KC_J), A(KC_7), A(KC_8), A(KC_9), A(KC_QUOT),
        KC_TAB,  OS_GUI,  OS_ALT,  OS_CTRL, OS_SHFT, _______,    KC_END,     KC_INS,   KC_PGUP, A(KC_M), A(KC_4), A(KC_5), A(KC_6), A(KC_O),
        KC_DEL,  A(KC_Z), A(KC_X), A(KC_C), A(KC_D), A(KC_V),    KC_PGDN,    A(KC_K),  A(KC_1), A(KC_2), A(KC_3), A(KC_SLSH),
                      _______,      _______, _______,             _______,    _______,  _______
    ),

    [_NAVLH] = LAYOUT_split_3x6_3_ex2(
        KC_ESC,  TO(_BASE), KC_HOME, KC_UP,   KC_END, KC_PGUP,    KC_PSCR,    KC_HOME,  KC_INS,  _______, _______, _______, _______, _______,
        KC_TAB,  KC_SPC,    KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN,    KC_END,     KC_INS,   KC_PGUP, _______, OS_SHFT, OS_CTRL, OS_ALT,  OS_GUI,
        KC_DEL,  KC_DEL,    KC_TAB,  KC_ENT,  KC_BSPC, KC_ESC,    KC_PGDN,    _______,  _______, _______, _______, _______,
                    TO(_BASE),       TO(_BASE), _______,           KC_ENT,     KC_BSPC,  _______
    ),

    [_MDIA] = LAYOUT_split_3x6_3_ex2(
        KC_ESC,  QK_BOOT, _______, RGB_TOG, _______, CG_TOGG,    KC_PSCR,    KC_HOME,  KC_INS,  KC_WH_U, KC_MPRV, KC_MS_U, KC_MNXT, KC_PSCR,
        KC_TAB,  OS_GUI,  OS_ALT,  OS_CTRL, OS_SHFT, _______,    KC_END,     KC_INS,   KC_PGUP, KC_WH_D, KC_MS_L, KC_MS_D, KC_MS_R, _______,
        KC_DEL,  _______, _______, _______, _______, _______,    KC_PGDN,    KC_MUTE,  KC_VOLD, KC_MPLY, KC_VOLU, _______,
                        _______,   _______, _______,             KC_BTN3,    KC_BTN1,  KC_BTN2
    )
};
// clang-format on

// This is a thin wrapper around rgb_matrix_set_color which allows you to put
// the same firmware on both halves of the keyboard (other than a #define for
// `MASTER_LEFT` or `MASTER_RIGHT`) and still have the correct LEDs light up
// regardless of which half has the USB cable in it.
//
// This complexity behind this logic is explained in the comments within the
// function itself.
void set_color_split(uint8_t key_code, uint8_t r, uint8_t g, uint8_t b) {
    // When using defines for MASTER_LEFT and MASTER_RIGHT, is_keyboard_left()
    // will be inaccurate. For example, (is_keyboard_left() &&
    // !is_keyboard_master()) can NEVER be true.
    //
    // See https://docs.qmk.fm/#/feature_split_keyboard?id=setting-handedness
    // for other ways to set handedness. If you use something other than the
    // #defines, then you can just set `is_left` to `is_keyboard_left()`.
#ifdef MASTER_LEFT
    bool is_left = true;
#endif
#ifdef MASTER_RIGHT
    bool is_left = false;
#endif

    bool left_is_master = (is_keyboard_master() && is_left) || (!is_keyboard_master() && !is_left);

    // Note on constants: 22 is the number of LEDs on each side (23) minus 1.
    // 23 is the number of LEDs that the Corne rev4.1 normally has with six columns.

    // Rule #1: you must set the LED based on what the master's range is. So if
    // the USB cable is in the left half, then the range is 0-22, otherwise it's
    // 23-45.

    // Rule #2: each half of the keyboard can only set its own LEDs, it's just
    // that the codes change according to Rule #1.

    // Rule #2
    if ((is_left && key_code >= NUM_LEDS_PER_SIDE) || (!is_left && key_code < NUM_LEDS_PER_SIDE)) {
        return;
    }

    // Rule #1
    if (left_is_master && key_code >= NUM_LEDS_PER_SIDE)
        key_code -= NUM_LEDS_PER_SIDE_ON_NORMAL_CORNE;
    else if (!left_is_master && key_code < NUM_LEDS_PER_SIDE)
        key_code += NUM_LEDS_PER_SIDE_ON_NORMAL_CORNE;
    rgb_matrix_set_color(key_code, r, g, b);
}

// Sets all keycodes specified in the array to the given color. This is good for
// coloring arbitrary keys like WASD or all of the number keys at once.
void set_all_keys_colors(const uint8_t keycodes[], uint8_t len, uint8_t r, uint8_t g, uint8_t b) {
    for (uint8_t i = 0; i < len; ++i) {
        set_color_split(keycodes[i], r, g, b);
    }
}

// Sets keys that fall within a contiguous keycode range to a given color.
// The start and end codes are inclusive.
void set_color_for_contiguous_keycodes(uint8_t start_code, uint8_t end_code, uint8_t r, uint8_t g, uint8_t b) {
    for (uint8_t i = start_code; i <= end_code; ++i) {
        set_color_split(i, r, g, b);
    }
}

void light_up_left_mods(uint8_t r, uint8_t g, uint8_t b) {
    const uint8_t left_mod_keycodes[] = {22, 19, 16, 11};
    set_all_keys_colors(left_mod_keycodes, sizeof(left_mod_keycodes) / sizeof(uint8_t), r, g, b);
}

void light_up_right_mods(uint8_t r, uint8_t g, uint8_t b) {
    const uint8_t right_mod_keycodes[] = {38, 43, 46, 49};
    set_all_keys_colors(right_mod_keycodes, sizeof(right_mod_keycodes) / sizeof(uint8_t), r, g, b);
}

bool is_mac_the_default(void) { return keymap_config.swap_lctl_lgui; }

bool is_shift_held(void) { return (get_mods() & MOD_BIT(KC_LSFT)) || (get_mods() & MOD_BIT(KC_RSFT)); }
bool is_ctrl_held(void) { return get_mods() & MOD_BIT(KC_LCTL); }
bool is_gui_held(void) { return get_mods() & MOD_BIT(KC_LGUI); }
bool is_alt_held(void) { return get_mods() & MOD_BIT(KC_LALT); }

#ifdef RGB_MATRIX_ENABLE
// Note: all keys mentioned in this function go by QWERTY.
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    // Diagram of underglow LEDs on the LH side when viewed from above:
    // 2   1   0
    //
    // 3   4   5
    //
    // 6   7   8
    //
    // 9   10  11
    //
    // 12  13  14
    //
    // 15  16  17
    //
    // 18  19  20
    //
    // 21  22  23

    // Diagram of underglow LEDs on the RH side when viewed from above:
    // 23  22  21
    //
    // 20  19  18
    //
    // 17  16  15
    //
    // 14  13  12
    //
    // 11  10  9
    //
    // 8   7   6
    //
    // 5   4   3
    //
    // 2   1   0

    // Note: all keys mentioned in this function go by QWERTY.

    // Caps Lock
    if (get_mods() & MOD_MASK_SHIFT || host_keyboard_led_state().caps_lock) {
        // Left half
        set_color_split(0, RGB_DARK_MAGENTA);
        set_color_split(1, RGB_DARK_MAGENTA);
        set_color_split(2, RGB_DARK_MAGENTA);

        // Right half
        set_color_split(23, RGB_DARK_MAGENTA);
        set_color_split(22, RGB_DARK_MAGENTA);
        set_color_split(21, RGB_DARK_MAGENTA);
    }

    // Num Lock
    if (get_mods() & MOD_MASK_ALT || host_keyboard_led_state().num_lock) {
        // Left half
        set_color_split(21, RGB_DARK_YELLOW);
        set_color_split(22, RGB_DARK_YELLOW);
        set_color_split(23, RGB_DARK_YELLOW);

        // Right half
        set_color_split(2, RGB_DARK_YELLOW);
        set_color_split(1, RGB_DARK_YELLOW);
        set_color_split(0, RGB_DARK_YELLOW);
    }

    return false;
}
#endif

// Lots of this code comes from https://github.com/qmk/qmk_firmware/tree/c4551d7ef1ed2c1069f23cc8499b7c7fc30f3ecf/users/drashna/split
//
// The goal is to sync keymap_config between the two halves since I base several
// lighting decisions on its values.
uint16_t transport_keymap_config = 0;
void     user_keymap_sync(uint8_t initiator2target_buffer_size, const void *initiator2target_buffer, uint8_t target2initiator_buffer_size, void *target2initiator_buffer) {
    if (initiator2target_buffer_size == sizeof(transport_keymap_config)) {
        memcpy(&transport_keymap_config, initiator2target_buffer, initiator2target_buffer_size);
    }
}
void user_transport_update(void) {
    if (is_keyboard_master()) {
        transport_keymap_config = keymap_config.raw;
    } else {
        keymap_config.raw = transport_keymap_config;
    }
}

void user_transport_sync(void) {
    if (is_keyboard_master()) {
        // Keep track of the last state, so that we can tell if we need to propagate to secondary
        static uint16_t last_keymap = 0;
        static uint32_t last_sync;
        bool            needs_sync = false;

        // Check if the state values are different
        if (memcmp(&transport_keymap_config, &last_keymap, sizeof(transport_keymap_config))) {
            needs_sync = true;
            memcpy(&last_keymap, &transport_keymap_config, sizeof(transport_keymap_config));
        }

        // Send to secondary every so often regardless of state change
        //
        // [Adam] Note: I toned this way down since I only really care about one
        // magic keycode, and that keycode represents a change in operating
        // systems (i.e. it's infrequent), and the result of a desync is just
        // having incorrect LEDs lit up. This code is mostly just if a sync
        // fails for whatever reason, which is actually pretty common (~10% of
        // the time?).
        if (timer_elapsed32(last_sync) > 1000) {
            needs_sync = true;
        }

        // Perform the sync if requested
        if (needs_sync) {
            if (transaction_rpc_send(RPC_ID_USER_KEYMAP_SYNC, sizeof(transport_keymap_config), &transport_keymap_config)) {
                last_sync = timer_read32();
            }
            needs_sync = false;
        }
    }
}

// Cycle the matrix color in a limited range of red/pinks/purples.
// https://docs.qmk.fm/#/feature_rgblight?id=color-selection
void change_matrix_color(void) {
    static uint16_t last_update;
    static bool     increase = true;

    if (timer_elapsed(last_update) > 1500) {
        last_update = timer_read();

        // I know about rgblight_increase_hue_noeeprom, but for some reason, I
        // can't #define a different step and I don't know why.
        rgblight_sethsv_noeeprom(rgblight_get_hue() + (increase ? 1 : -1), rgblight_get_sat(), rgblight_get_val());

        uint8_t hue = rgblight_get_hue();
        // 11 is definitely yellow despite the color wheel, so we stop in
        // orange.
        if ((increase && hue >= 2 && hue < 100) || (!increase && hue > 50 && hue < 180)) {
            increase = !increase;
        }
    }
}

void housekeeping_task_user(void) {
    // Update kb_state so we can send to secondary
    user_transport_update();

    // Data sync from master to secondary
    user_transport_sync();

    change_matrix_color();
}

void keyboard_post_init_user(void) {
    rgblight_sethsv_noeeprom(HSV_MAGENTA);

    transaction_register_rpc(RPC_ID_USER_KEYMAP_SYNC, user_keymap_sync);

    // This is good in case I screw anything up with bad code; it's REALLY hard
    // to fix it when mods get messed up since it can mess up the whole OS.
    //
    // Ctrl+alt+del can help on Windows, as can osk.exe sometimes.
    clear_mods();
}

bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
        case MO_NAV:
        case OSL_NAVWIN:
        case MO_FUN:
        case MO_NUM:
        case MO_SYMB:
            return true;
        default:
            return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
        case MO_NAV:
        case OSL_NAVWIN:
        case MO_FUN:
        case MO_NUM:
        case MO_SYMB:
        case KC_LSFT:
        case OS_SHFT:
        case OS_CTRL:
        case OS_ALT:
        case OS_GUI:
            return true;
        default:
            return false;
    }
}

bool          sw_app_active = false;
bool          sw_win_active = false;
oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state  = os_up_unqueued;
oneshot_state os_gui_state  = os_up_unqueued;

// Sends `mac_code` on macOS, `win_code` on Windows.
//
// Credit to Rhymu
void send_mac_or_win(uint16_t mac_code, uint16_t win_code, bool is_pressed) {
    uint16_t code = is_mac_the_default() ? mac_code : win_code;
    if (is_pressed) {
        register_code16(code);
    } else {
        unregister_code16(code);
    }
}

void tap_mac_or_win(uint16_t mac_code, uint16_t win_code) {
    uint16_t code = is_mac_the_default() ? mac_code : win_code;
    tap_code16(code);
}

// https://github.com/qmk/qmk_firmware/issues/4611#issuecomment-446713700
// https://www.reddit.com/r/olkb/comments/oflwv6/how_do_i_change_qmk_layer_tap_behavior/h4l7u8n/?utm_source=reddit&utm_medium=web2x&context=3
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    bool isPressed    = record->event.pressed;
    bool sent_keycode = false;

    {
        uint16_t mod = is_mac_the_default() ? KC_LGUI : KC_LALT;
        update_swapper(&sw_app_active, mod, KC_TAB, SW_APP, keycode, record);
    }
    update_swapper(&sw_win_active, KC_LGUI, KC_GRV, SW_WIN, keycode, record);

    // Capture these values AFTER the swapper stuff is done since they
    // can change whether certain modifier are held.
    bool isCtrlHeld  = (is_gui_held() && is_mac_the_default()) || (is_ctrl_held() && !is_mac_the_default());
    bool isGuiHeld   = (is_ctrl_held() && is_mac_the_default()) || (is_gui_held() && !is_mac_the_default());
    bool isShiftHeld = is_shift_held();
    bool isAltHeld   = is_alt_held();

    // Handle these before one-shot modifiers so that the modifiers are still
    // pressed. Also, consider pressing these to have sent a keycode for
    // one-shot modifiers since the register_code() call in oneshot.c can't
    // understand these custom keycodes.
    switch (keycode) {
        case REV_COLON:
            // No mod → :
            // Shift → ;
            if (isPressed) {
                if (isShiftHeld) {
                    unregister_mods(MOD_BIT(KC_LSFT));
                    tap_code_delay(KC_SCLN, 0);
                    register_mods(MOD_BIT(KC_LSFT));
                } else {
                    tap_code16(S(KC_SCLN));
                }
                sent_keycode = true;
            }
            break;
        case MW_SELECT_ALL:
            if (isPressed) {
                tap_mac_or_win(G(KC_A), C(KC_A));
                sent_keycode = true;
            }
            break;
        case PRV_TAB:
            if (isPressed) {
                register_code16(RCS(KC_TAB));
            } else {
                unregister_code16(RCS(KC_TAB));
            }
            sent_keycode = true;
            break;
        case NXT_TAB:
            if (isPressed) {
                register_code16(C(KC_TAB));
            } else {
                unregister_code16(C(KC_TAB));
            }
            sent_keycode = true;
            break;
        case MW_PSTE:
            // No mod → paste
            // Shift → shift+paste
            //
            // (I frequently want to send shift+paste to paste unformatted text,
            // e.g. in documents or emails)
            if (isShiftHeld) {
                send_mac_or_win(G(S(KC_V)), C(S(KC_V)), isPressed);
            } else {
                send_mac_or_win(G(KC_V), C(KC_V), isPressed);
            }
            sent_keycode = true;
            break;
        case MW_MKLNK:
            // No mod → make link (ctrl+K or cmd+K)
            // Shift → evaluate in VSCode (ctrl+shift+E or cmd+shift+E)
            //   Note: this is in the NAV layer because I only ever use it right
            //         after selecting text, so this makes it natural.
            if (isShiftHeld) {
                if (isPressed) {
                    tap_mac_or_win(G(S(KC_E)), C(S(KC_E)));
                }
            } else {
                send_mac_or_win(G(KC_K), C(KC_K), isPressed);
            }
            sent_keycode = true;
            break;
        case MW_NWTB:
            // No mod → new tab (ctrl+T or cmd+T)
            // Shift → new window (ctrl+N or cmd+N)
            // Ctrl → go to homepage (alt+home or cmd+shift+H)
            // Alt → go to address bar in Chrome (ctrl+L or cmd+L)
            // Win → find (ctrl+F or cmd+F)
            if (isShiftHeld && isPressed) {
                unregister_mods(MOD_BIT(KC_LSFT));
                tap_mac_or_win(G(KC_N), C(KC_N));
                register_mods(MOD_BIT(KC_LSFT));
            } else if (isCtrlHeld && isPressed) {
                int mod = is_mac_the_default() ? MOD_BIT(KC_LGUI) : MOD_BIT(KC_LCTL);
                unregister_mods(mod);
                tap_mac_or_win(G(S(KC_H)), A(KC_HOME));
                register_mods(mod);
            } else if (isAltHeld && isPressed) {
                unregister_mods(MOD_BIT(KC_LALT));
                tap_mac_or_win(G(KC_L), C(KC_L));
                register_mods(MOD_BIT(KC_LALT));
            } else if (isGuiHeld && isPressed) {
                int mod = is_mac_the_default() ? MOD_BIT(KC_LCTL) : MOD_BIT(KC_LGUI);
                unregister_mods(mod);
                tap_mac_or_win(G(KC_F), C(KC_F));
                register_mods(mod);
            } else {
                send_mac_or_win(G(KC_T), C(KC_T), isPressed);
            }
            sent_keycode = true;
            break;
        case CLS_WIN:
            if (isShiftHeld && isPressed) {
                unregister_mods(MOD_BIT(KC_LSFT));
                tap_mac_or_win(G(KC_D), A(KC_N));
                register_mods(MOD_BIT(KC_LSFT));
            } else {
                send_mac_or_win(G(KC_W), C(KC_W), isPressed);
            }
            sent_keycode = true;
            break;
        case KC_LEFT_ENCLOSE:
            // No mod → (
            // Shift → {
            if (isPressed) {
                if (isShiftHeld) {
                    tap_code_delay(KC_LBRC, 0);
                } else {
                    tap_code16(S(KC_9));
                }
                sent_keycode = true;
            }
            break;
        case KC_RIGHT_ENCLOSE:
            // No mod → )
            // Shift → }
            if (isPressed) {
                if (isShiftHeld) {
                    tap_code_delay(KC_RBRC, 0);
                } else {
                    tap_code16(S(KC_0));
                }
                sent_keycode = true;
            }
            break;
    }

    update_oneshot(&os_shft_state, &sent_keycode, KC_LSFT, OS_SHFT, keycode, record);
    update_oneshot(&os_ctrl_state, &sent_keycode, is_mac_the_default() ? KC_LGUI : KC_LCTL, OS_CTRL, keycode, record);
    update_oneshot(&os_alt_state, &sent_keycode, KC_LALT, OS_ALT, keycode, record);
    update_oneshot(&os_gui_state, &sent_keycode, is_mac_the_default() ? KC_LCTL : KC_LGUI, OS_GUI, keycode, record);
    if (sent_keycode) return false;

    switch (keycode) {
        case MW_UNDO:
            send_mac_or_win(G(KC_Z), C(KC_Z), isPressed);
            return false;
        case MW_CUT:
            send_mac_or_win(G(KC_X), C(KC_X), isPressed);
            return false;
        case MW_COPY:
            send_mac_or_win(G(KC_C), C(KC_C), isPressed);
            return false;
        case VSC_EVAL:
            send_mac_or_win(G(S(KC_E)), C(S(KC_E)), isPressed);
            return false;
        case MW_REDO: {
            uint16_t code = is_mac_the_default() ? G(S(KC_Z)) : C(KC_Y);
            if (isPressed) {
                register_code16(code);
            } else {
                unregister_code16(code);
            }
            return false;
        }
        // Delete the previous word
        case KC_DWRD: {
            uint16_t CODE = is_mac_the_default() ? A(KC_BSPC) : C(KC_BSPC);
            if (isPressed) {
                register_code16(CODE);
            } else {
                unregister_code16(CODE);
            }
            return false;
        }
        case KC_3GRV: {
            if (isPressed) {
                for (uint8_t i = 0; i < 3; i++) tap_code16(KC_GRV);
            }

            return false;
        }
    }

    return true;
}

#ifdef TAPPING_TERM_PER_KEY
// Increasing the tapping term means that dual-function keys have to be held for
// longer before they're treated as their "hold" action.
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // I was making a bunch of typos presumably due to this shortcut, so I'm
        // trying a much longer TAPPING_TERM so that I hopefully only hit this
        // intentionally.
        case LT_NAV_SPACE:
            return TAPPING_TERM + 125;
        // I just hold my pinky down on O for too long for common words
        // like "out". An extra bit of time seems to help.
        case LT_MDIA_O:
            return TAPPING_TERM + 50;
        default:
            return TAPPING_TERM;
    }
}
#endif

// Note: by default, COMBO_TERM is 50ms (https://docs.qmk.fm/#/feature_combo?id=combo-term)
// This means you need to press both keys within 50ms to activate the combo.
// If you accidentally trigger it too much, lower it.
#ifdef COMBO_TERM_PER_COMBO
uint16_t get_combo_term(uint16_t index, combo_t *combo) {
    switch (index) {
        // "NEI" shows up in "friend", which I seem to type often enough
        // to accidentally trigger this. 😢
        case NEI_CTRL:
            return 30;
    }

    return COMBO_TERM;
}
#endif
