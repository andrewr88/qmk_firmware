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
#include <stdio.h>

// Simplified version that eliminates custom oneshot implementation
// and uses QMK's native features where possible

enum layers {
    _BASE,    // default layer
    _SYMB,    // symbols
    _NUM,     // numbers
    _FUN,     // fn keys
    _NAV,     // navigation keys
    _NAVWIN,  // navigation keys for macOS global shortcuts between windows
    _NAVLH,   // navigation keys mirrored so arrows are on the LH
    _MDIA,    // media keys
};

// Use QMK's built-in oneshot mods instead of custom implementation
#define OS_SHFT OSM(MOD_LSFT)
#define OS_CTRL OSM(MOD_LCTL)
#define OS_ALT  OSM(MOD_LALT)
#define OS_GUI  OSM(MOD_LGUI)

// Layer tap definitions
#define LT_NAV_SPACE LT(_NAV, KC_SPC)
#define LT_MDIA_O LT(_MDIA, KC_SCLN)
#define MO_NAV MO(_NAV)
#define OSL_NAVWIN OSL(_NAVWIN)
#define MO_FUN MO(_FUN)
#define MO_NUM MO(_NUM)
#define MO_SYMB MO(_SYMB)

// Custom keycodes for Mac/Windows compatibility
enum custom_keycodes {
    SW_APP = SAFE_RANGE,  // Switch app (Cmd+Tab or Alt+Tab)
    SW_WIN,               // Switch window (Cmd+` on Mac)
    CLS_WIN,              // Close window (Cmd+W or Ctrl+W)
    MW_UNDO,              // Undo (Cmd+Z or Ctrl+Z)
    MW_CUT,               // Cut (Cmd+X or Ctrl+X)
    MW_COPY,              // Copy (Cmd+C or Ctrl+C)
    MW_PSTE,              // Paste (Cmd+V or Ctrl+V)
    MW_REDO,              // Redo (Cmd+Shift+Z or Ctrl+Y)
    MW_NWTB,              // New tab (Cmd+T or Ctrl+T)
    MW_MKLNK,             // Make link (Cmd+K or Ctrl+K)
    MW_SELECT_ALL,        // Select all (Cmd+A or Ctrl+A)
    KC_DWRD,              // Delete word (Alt+Backspace or Ctrl+Backspace)
    VSC_EVAL,             // Evaluate in VS Code (Cmd+Shift+E or Ctrl+Shift+E)
    REV_COLON,            // Reverse colon/semicolon behavior
    PRV_TAB,              // Previous tab
    NXT_TAB,              // Next tab
    KC_LEFT_ENCLOSE,      // Left enclosure (parenthesis or brace)
    KC_RIGHT_ENCLOSE,     // Right enclosure (parenthesis or brace)
    KC_3GRV,              // Three backticks
};

// Key combos
enum combos { NEI_CTRL, COMMADOT_SEMICOLON, HCOMMA_HYPHEN, ZD_TAB, XD_CTRL, DH_CTRL, PREV_NEXT_SELECT_ALL, COMBO_LENGTH };
uint16_t COMBO_LEN = COMBO_LENGTH;

const uint16_t PROGMEM nei_ctrl[]              = {KC_N, KC_E, KC_I, COMBO_END};
const uint16_t PROGMEM commadot_semicolon[]    = {KC_COMM, KC_DOT, COMBO_END};
const uint16_t PROGMEM hcomma_hyphen[]         = {KC_H, KC_COMM, COMBO_END};
const uint16_t PROGMEM xd_ctrl[]               = {KC_X, KC_D, COMBO_END};
const uint16_t PROGMEM dh_ctrl[]               = {KC_D, KC_H, COMBO_END};
const uint16_t PROGMEM zd_tab[]                = {KC_Z, KC_D, COMBO_END};
const uint16_t PROGMEM prev_next_select_all[]  = {PRV_TAB, NXT_TAB, COMBO_END};

combo_t key_combos[] = {
    [NEI_CTRL]          = COMBO(nei_ctrl, OS_CTRL),
    [COMMADOT_SEMICOLON]= COMBO(commadot_semicolon, KC_SCLN),
    [HCOMMA_HYPHEN]     = COMBO(hcomma_hyphen, KC_MINS),
    [XD_CTRL]           = COMBO(xd_ctrl, OS_CTRL),
    [DH_CTRL]           = COMBO(dh_ctrl, OS_CTRL),
    [ZD_TAB]            = COMBO(zd_tab, KC_TAB),
    [PREV_NEXT_SELECT_ALL] = COMBO(prev_next_select_all, MW_SELECT_ALL),
};

// Track state for window-switching
static bool alt_tab_active = false;
static bool gui_tab_active = false;

// OS detection for Mac/Windows key handling
bool is_mac_mode = true;  // Default to Mac, can be toggled with CG_TOGG

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_split_3x6_3_ex2(
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,   KC_PSCR,    KC_HOME,   KC_Y,    KC_U,    KC_I,    KC_O,       KC_P,   KC_BSPC,
        KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_END,     KC_INS,   KC_H,    KC_J,    KC_K,    KC_L,  LT_MDIA_O,   KC_QUOT,
       OS_SHFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                          KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,   OS_SHFT,
                             MO_FUN, MO_NUM, LT_NAV_SPACE,                          OS_SHFT, MO_NAV, MO_SYMB
    ),

    [_SYMB] = LAYOUT_split_3x6_3_ex2(
        KC_ESC,  KC_MINS, S(KC_MINS),          KC_EQL,        S(KC_EQL), KC_BSLS,  KC_PSCR,  KC_HOME,    MW_UNDO, S(KC_7),    S(KC_8),    KC_DOT,    MW_PSTE,  KC_BSPC,
        KC_TAB,  KC_QUOT, S(KC_QUOT), KC_LEFT_ENCLOSE, KC_RIGHT_ENCLOSE,  KC_GRV,   KC_END,   KC_INS,  REV_COLON, OS_SHFT,    OS_CTRL,    OS_ALT,     OS_GUI,  KC_QUOT,
        OS_SHFT,  KC_SCLN, S(KC_SCLN),         KC_LBRC,          KC_RBRC, KC_3GRV,                        KC_MINS, S(KC_1), S(KC_COMM), S(KC_DOT), S(KC_SLSH), OS_SHFT,
                                              _______,          _______,  KC_ENT,                        _______, _______, _______
    ),

    [_NUM] = LAYOUT_split_3x6_3_ex2(
        KC_ESC,   KC_TAB, KC_LEFT,   KC_DOT,   KC_RGHT, S(KC_MINS), KC_PSCR,    KC_HOME,   VSC_EVAL, KC_7, KC_8, KC_9, S(KC_EQL),  KC_BSPC,
        KC_TAB,   OS_GUI,  OS_ALT,  OS_CTRL,   OS_SHFT,     MO_NAV,  KC_END,     KC_INS,  REV_COLON, KC_4, KC_5, KC_6,  KC_MINS,   KC_QUOT,
        OS_SHFT,  MW_UNDO, _______,   KC_COMM,  REV_COLON, MW_REDO,                         KC_MINS, KC_1, KC_2, KC_3,  _______,   OS_SHFT,
                                    _______,   _______,    _______,                          KC_ENT, KC_BSPC, KC_0
    ),

    [_FUN] = LAYOUT_split_3x6_3_ex2(
        KC_ESC,   KC_1,    KC_2,     KC_3,    KC_4,    KC_5,    KC_PSCR,    KC_HOME, TO(_NAVLH), KC_F7, KC_F8, KC_F9, KC_F12,  KC_BSPC,
        KC_TAB, OS_GUI,  OS_ALT,  OS_CTRL, OS_SHFT, _______,     KC_END,     KC_INS,    _______, KC_F4, KC_F5, KC_F6, KC_F11,  KC_QUOT,
        OS_SHFT,   KC_6,    KC_7,     KC_8,    KC_9,    KC_0,                            _______, KC_F1, KC_F2, KC_F3, KC_F10, OS_SHFT,
                                  _______, _______, _______,                            _______, KC_CAPS, _______
    ),

    [_NAV] = LAYOUT_split_3x6_3_ex2(
        KC_ESC,  SW_WIN, PRV_TAB, CLS_WIN, NXT_TAB,     SW_APP, KC_PSCR,    KC_HOME,  KC_PGUP, KC_HOME,   KC_UP,  KC_END, KC_DWRD,  KC_BSPC,
        KC_TAB,  OS_GUI,  OS_ALT, OS_CTRL, OS_SHFT, OSL_NAVWIN,  KC_END,     KC_INS,  KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT,  KC_SPC,   KC_QUOT,
        OS_SHFT, MW_UNDO,  MW_CUT, MW_COPY, MW_PSTE,    MW_REDO,                        KC_ESC, KC_BSPC,  KC_ENT,  KC_TAB,  KC_DEL, OS_SHFT,
                                 MW_MKLNK, _______,    MW_NWTB,                        KC_ENT, KC_BSPC,  LT_MDIA_O
    ),

    [_NAVWIN] = LAYOUT_split_3x6_3_ex2(
        KC_ESC,  A(KC_Q), A(KC_W), A(KC_F), A(KC_P), A(KC_B),    KC_PSCR,    KC_HOME,  A(KC_J), A(KC_7), A(KC_8), A(KC_9), A(KC_QUOT), KC_BSPC,
        KC_TAB,   OS_GUI,  OS_ALT, OS_CTRL, OS_SHFT, _______,    KC_END,     KC_INS,   A(KC_M), A(KC_4), A(KC_5), A(KC_6),    A(KC_O), KC_QUOT,
        OS_SHFT, A(KC_Z), A(KC_X), A(KC_C), A(KC_D), A(KC_V),                          A(KC_K), A(KC_1), A(KC_2), A(KC_3), A(KC_SLSH), OS_SHFT,
                                   _______, _______, _______,                          _______, _______, _______
    ),

    [_NAVLH] = LAYOUT_split_3x6_3_ex2(
        KC_ESC, TO(_BASE), KC_HOME,   KC_UP,  KC_END, KC_PGUP,  KC_PSCR,    KC_HOME,   _______, _______, _______, _______, _______,  KC_BSPC,
        KC_TAB,    KC_SPC, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN,  KC_END,      KC_INS,   _______, OS_SHFT, OS_CTRL,  OS_ALT,  OS_GUI,  KC_QUOT,
        OS_SHFT,    KC_DEL,  KC_TAB,  KC_ENT, KC_BSPC,  KC_ESC,                         _______, _______, _______, _______, _______, OS_SHFT,
                                  TO(_BASE),TO(_BASE),_______,                          KC_ENT, KC_BSPC, _______
    ),

    [_MDIA] = LAYOUT_split_3x6_3_ex2(
        KC_ESC,  QK_BOOT, _______,  _______, _______, CG_TOGG,  KC_PSCR,    KC_HOME,   KC_WH_U, KC_MPRV, KC_MS_U, KC_MNXT, KC_PSCR,  KC_BSPC,
        KC_TAB,   OS_GUI,  OS_ALT,  OS_CTRL, OS_SHFT, _______,  KC_END,      KC_INS,   KC_WH_D, KC_MS_L, KC_MS_D, KC_MS_R, _______,  KC_QUOT,
        OS_SHFT,  _______, _______,  _______, _______, _______,                         KC_MUTE, KC_VOLD, KC_MPLY, KC_VOLU, _______, OS_SHFT,
                                    _______, _______, _______,                         KC_BTN3, KC_BTN1, KC_BTN2
    )
};
// clang-format on

// Called when CG_TOGG is pressed to toggle between Mac and Windows mode
void housekeeping_task_user(void) {
    // CG_TOGG toggles the Gui/Ctrl swap which we can use to detect mode
    is_mac_mode = keymap_config.swap_lctl_lgui == false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    bool is_pressed = record->event.pressed;

    // Handle window switcher behavior (Alt-Tab / Cmd-Tab)
    if (keycode == SW_APP) {
        if (is_pressed) {
            if (!alt_tab_active) {
                alt_tab_active = true;
                if (is_mac_mode) {
                    register_code(KC_LGUI);
                } else {
                    register_code(KC_LALT);
                }
            }
            if (is_mac_mode) {
                tap_code(KC_TAB);
            } else {
                tap_code(KC_TAB);
            }
        } else {
            if (alt_tab_active) {
                alt_tab_active = false;
                if (is_mac_mode) {
                    unregister_code(KC_LGUI);
                } else {
                    unregister_code(KC_LALT);
                }
            }
        }
        return false;
    }

    // Handle window switcher behavior (Cmd-`)
    if (keycode == SW_WIN) {
        if (is_pressed) {
            if (!gui_tab_active) {
                gui_tab_active = true;
                register_code(KC_LGUI);
            }
            tap_code(KC_GRV);
        } else {
            if (gui_tab_active) {
                gui_tab_active = false;
                unregister_code(KC_LGUI);
            }
        }
        return false;
    }

    // Cancel window switcher if any other key is pressed
    if (alt_tab_active && keycode != SW_APP) {
        alt_tab_active = false;
        if (is_mac_mode) {
            unregister_code(KC_LGUI);
        } else {
            unregister_code(KC_LALT);
        }
    }

    if (gui_tab_active && keycode != SW_WIN) {
        gui_tab_active = false;
        unregister_code(KC_LGUI);
    }

    // Mac/Win compatibility keys
    switch (keycode) {
        case PRV_TAB:
            if (is_pressed) {
                register_code16(C(S(KC_TAB)));
            } else {
                unregister_code16(C(S(KC_TAB)));
            }
            return false;

        case NXT_TAB:
            if (is_pressed) {
                register_code16(C(KC_TAB));
            } else {
                unregister_code16(C(KC_TAB));
            }
            return false;

        case CLS_WIN:
            if (is_pressed) {
                if (is_mac_mode) {
                    register_code16(G(KC_W));
                } else {
                    register_code16(C(KC_W));
                }
            } else {
                if (is_mac_mode) {
                    unregister_code16(G(KC_W));
                } else {
                    unregister_code16(C(KC_W));
                }
            }
            return false;

        case MW_UNDO:
            if (is_pressed) {
                if (is_mac_mode) {
                    register_code16(G(KC_Z));
                } else {
                    register_code16(C(KC_Z));
                }
            } else {
                if (is_mac_mode) {
                    unregister_code16(G(KC_Z));
                } else {
                    unregister_code16(C(KC_Z));
                }
            }
            return false;

        case MW_CUT:
            if (is_pressed) {
                if (is_mac_mode) {
                    register_code16(G(KC_X));
                } else {
                    register_code16(C(KC_X));
                }
            } else {
                if (is_mac_mode) {
                    unregister_code16(G(KC_X));
                } else {
                    unregister_code16(C(KC_X));
                }
            }
            return false;

        case MW_COPY:
            if (is_pressed) {
                if (is_mac_mode) {
                    register_code16(G(KC_C));
                } else {
                    register_code16(C(KC_C));
                }
            } else {
                if (is_mac_mode) {
                    unregister_code16(G(KC_C));
                } else {
                    unregister_code16(C(KC_C));
                }
            }
            return false;

        case MW_PSTE:
            if (is_pressed) {
                if (is_mac_mode) {
                    register_code16(G(KC_V));
                } else {
                    register_code16(C(KC_V));
                }
            } else {
                if (is_mac_mode) {
                    unregister_code16(G(KC_V));
                } else {
                    unregister_code16(C(KC_V));
                }
            }
            return false;

        case MW_REDO:
            if (is_pressed) {
                if (is_mac_mode) {
                    register_code16(G(S(KC_Z)));
                } else {
                    register_code16(C(KC_Y));
                }
            } else {
                if (is_mac_mode) {
                    unregister_code16(G(S(KC_Z)));
                } else {
                    unregister_code16(C(KC_Y));
                }
            }
            return false;

        case MW_NWTB:
            if (is_pressed) {
                if (is_mac_mode) {
                    register_code16(G(KC_T));
                } else {
                    register_code16(C(KC_T));
                }
            } else {
                if (is_mac_mode) {
                    unregister_code16(G(KC_T));
                } else {
                    unregister_code16(C(KC_T));
                }
            }
            return false;

        case MW_MKLNK:
            if (is_pressed) {
                if (is_mac_mode) {
                    register_code16(G(KC_K));
                } else {
                    register_code16(C(KC_K));
                }
            } else {
                if (is_mac_mode) {
                    unregister_code16(G(KC_K));
                } else {
                    unregister_code16(C(KC_K));
                }
            }
            return false;

        case MW_SELECT_ALL:
            if (is_pressed) {
                if (is_mac_mode) {
                    register_code16(G(KC_A));
                } else {
                    register_code16(C(KC_A));
                }
            } else {
                if (is_mac_mode) {
                    unregister_code16(G(KC_A));
                } else {
                    unregister_code16(C(KC_A));
                }
            }
            return false;

        case KC_DWRD:
            if (is_pressed) {
                if (is_mac_mode) {
                    register_code16(A(KC_BSPC));
                } else {
                    register_code16(C(KC_BSPC));
                }
            } else {
                if (is_mac_mode) {
                    unregister_code16(A(KC_BSPC));
                } else {
                    unregister_code16(C(KC_BSPC));
                }
            }
            return false;

        case VSC_EVAL:
            if (is_pressed) {
                if (is_mac_mode) {
                    register_code16(G(S(KC_E)));
                } else {
                    register_code16(C(S(KC_E)));
                }
            } else {
                if (is_mac_mode) {
                    unregister_code16(G(S(KC_E)));
                } else {
                    unregister_code16(C(S(KC_E)));
                }
            }
            return false;

        case REV_COLON:
            // Sends colon by default, semicolon when shifted
            if (is_pressed) {
                if (get_mods() & MOD_MASK_SHIFT) {
                    del_mods(MOD_MASK_SHIFT); // Remove shift temporarily
                    tap_code(KC_SCLN);
                    set_mods(get_mods() | MOD_MASK_SHIFT); // Add shift back
                } else {
                    register_code16(S(KC_SCLN));
                    unregister_code16(S(KC_SCLN));
                }
            }
            return false;

        case KC_LEFT_ENCLOSE:
            // Sends ( by default, { when shifted
            if (is_pressed) {
                if (get_mods() & MOD_MASK_SHIFT) {
                    register_code(KC_LBRC);
                    unregister_code(KC_LBRC);
                } else {
                    register_code16(S(KC_9));
                    unregister_code16(S(KC_9));
                }
            }
            return false;

        case KC_RIGHT_ENCLOSE:
            // Sends ) by default, } when shifted
            if (is_pressed) {
                if (get_mods() & MOD_MASK_SHIFT) {
                    register_code(KC_RBRC);
                    unregister_code(KC_RBRC);
                } else {
                    register_code16(S(KC_0));
                    unregister_code16(S(KC_0));
                }
            }
            return false;

        case KC_3GRV:
            // Sends three backticks
            if (is_pressed) {
                tap_code(KC_GRV);
                tap_code(KC_GRV);
                tap_code(KC_GRV);
            }
            return false;
    }

    return true;
}
