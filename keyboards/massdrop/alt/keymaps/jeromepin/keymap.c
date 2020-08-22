#include QMK_KEYBOARD_H

enum alt_keycodes {
    L_BRI = SAFE_RANGE, //LED Brightness Increase                                   //Working
    L_BRD,              //LED Brightness Decrease                                   //Working
    L_PTN,              //LED Pattern Select Next                                   //Working
    L_PTP,              //LED Pattern Select Previous                               //Working
    L_PSI,              //LED Pattern Speed Increase                                //Working
    L_PSD,              //LED Pattern Speed Decrease                                //Working
    L_T_MD,             //LED Toggle Mode                                           //Working
    L_T_ONF,            //LED Toggle On / Off                                       //Broken
    L_ON,               //LED On                                                    //Broken
    L_OFF,              //LED Off                                                   //Broken
    L_T_BR,             //LED Toggle Breath Effect                                  //Working
    L_T_PTD,            //LED Toggle Scrolling Pattern Direction                    //Working
    U_T_AUTO = SAFE_RANGE, //USB Extra Port Toggle Auto Detect / Always Active
    U_T_AGCR,           //USB Toggle Automatic GCR control                          //Working
    DBG_TOG,            //DEBUG Toggle On / Off                                     //
    DBG_MTRX,           //DEBUG Toggle Matrix Prints                                //
    DBG_KBD,            //DEBUG Toggle Keyboard Prints                              //
    DBG_MOU,            //DEBUG Toggle Mouse Prints                                 //
    MD_BOOT             //Restart into bootloader after hold timeout                //Working
};

keymap_config_t keymap_config;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_65_ansi_blocker(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,  \
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_HOME, \
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_PGUP, \
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   KC_PGDN, \
        KC_LCTL, KC_LALT, KC_LGUI,                            KC_SPC,                             KC_RGUI, MO(1),   KC_LEFT, KC_DOWN, KC_RGHT  \
    ),
    [1] = LAYOUT_65_ansi_blocker(
        KC_GRV,  KC_BRMD, KC_BRMU, KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MRWD, KC_MPLY, KC_MFFD, KC__MUTE,KC_VOLD, KC_VOLU, _______, KC_POWER, \
        L_T_BR,  L_PSD,   L_BRI,   L_PSI,   _______, _______, _______, _______, U_T_AGCR,_______, KC_PSCR, KC_SLCK, KC_PAUS, _______, _______,  \
        L_T_PTD, L_PTP,   L_BRD,   L_PTN,   _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,  \
        _______, L_T_MD,  L_T_ONF, _______, _______, MD_BOOT, NK_TOGG, DBG_TOG, _______, _______, _______, _______,          _______, _______,  \
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______   \
    ),
    /*
    [X] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, \
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______  \
    ),
    */
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
};

#define MODS_SHIFT  (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT))
#define MODS_CTRL  (get_mods() & MOD_BIT(KC_LCTL) || get_mods() & MOD_BIT(KC_RCTRL))
#define MODS_ALT  (get_mods() & MOD_BIT(KC_LALT) || get_mods() & MOD_BIT(KC_RALT))

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint32_t key_timer;

    switch (keycode) {
        case U_T_AUTO:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_extra_manual, "USB extra port manual mode");
            }
            return false;
        // case L_BRI:
        //     if (record->event.pressed) {
        //         if (LED_GCR_STEP > LED_GCR_MAX - gcr_desired) gcr_desired = LED_GCR_MAX;
        //         else gcr_desired += LED_GCR_STEP;
        //         if (led_animation_breathing) gcr_breathe = gcr_desired;
        //     }
        //     return false;
        // case L_BRD:
        //     if (record->event.pressed) {
        //         if (LED_GCR_STEP > gcr_desired) gcr_desired = 0;
        //         else gcr_desired -= LED_GCR_STEP;
        //         if (led_animation_breathing) gcr_breathe = gcr_desired;
        //     }
        //     return false;
        // case L_PTN:
        //     if (record->event.pressed) {
        //         if (led_animation_id == led_setups_count - 1) led_animation_id = 0;
        //         else led_animation_id++;
        //     }
        //     return false;
        // case L_PTP:
        //     if (record->event.pressed) {
        //         if (led_animation_id == 0) led_animation_id = led_setups_count - 1;
        //         else led_animation_id--;
        //     }
        //     return false;
        // case L_PSI:
        //     if (record->event.pressed) {
        //         led_animation_speed += ANIMATION_SPEED_STEP;
        //     }
        //     return false;
        // case L_PSD:
        //     if (record->event.pressed) {
        //         led_animation_speed -= ANIMATION_SPEED_STEP;
        //         if (led_animation_speed < 0) led_animation_speed = 0;
        //     }
        //     return false;
        // case L_T_MD:
        //     if (record->event.pressed) {
        //         led_lighting_mode++;
        //         if (led_lighting_mode > LED_MODE_MAX_INDEX) led_lighting_mode = LED_MODE_NORMAL;
        //     }
        //     return false;
        // case L_T_ONF:
        //     if (record->event.pressed) {
        //         led_enabled = !led_enabled;
        //         I2C3733_Control_Set(led_enabled);
        //     }
        //     return false;
        // case L_ON:
        //     if (record->event.pressed) {
        //         led_enabled = 1;
        //         I2C3733_Control_Set(led_enabled);
        //     }
        //     return false;
        // case L_OFF:
        //     if (record->event.pressed) {
        //         led_enabled = 0;
        //         I2C3733_Control_Set(led_enabled);
        //     }
        //     return false;
        // case L_T_BR:
        //     if (record->event.pressed) {
        //         led_animation_breathing = !led_animation_breathing;
        //         if (led_animation_breathing) {
        //             gcr_breathe = gcr_desired;
        //             led_animation_breathe_cur = BREATHE_MIN_STEP;
        //             breathe_dir = 1;
        //         }
        //     }
        //     return false;
        // case L_T_PTD:
        //     if (record->event.pressed) {
        //         led_animation_direction = !led_animation_direction;
        //     }
        //     return false;
        case U_T_AGCR:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_gcr_auto, "USB GCR auto mode");
            }
            return false;
        case DBG_TOG:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_enable, "Debug mode");
            }
            return false;
        case DBG_MTRX:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_matrix, "Debug matrix");
            }
            return false;
        case DBG_KBD:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_keyboard, "Debug keyboard");
            }
            return false;
        case DBG_MOU:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_mouse, "Debug mouse");
            }
            return false;
        case MD_BOOT:
            if (record->event.pressed) {
                key_timer = timer_read32();
            } else {
                if (timer_elapsed32(key_timer) >= 500) {
                    reset_keyboard();
                }
            }
            return false;
        // case RGB_TOG:
        //     if (record->event.pressed) {
        //       switch (rgb_matrix_get_flags()) {
        //         case LED_FLAG_ALL: {
        //             rgb_matrix_set_flags(LED_FLAG_KEYLIGHT);
        //             rgb_matrix_set_color_all(0, 0, 0);
        //           }
        //           break;
        //         case LED_FLAG_KEYLIGHT: {
        //             rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
        //             rgb_matrix_set_color_all(0, 0, 0);
        //           }
        //           break;
        //         case LED_FLAG_UNDERGLOW: {
        //             rgb_matrix_set_flags(LED_FLAG_NONE);
        //             rgb_matrix_disable_noeeprom();
        //           }
        //           break;
        //         default: {
        //             rgb_matrix_set_flags(LED_FLAG_ALL);
        //             rgb_matrix_enable_noeeprom();
        //           }
        //           break;
        //       }
        //     }
        //     return false;
        default:
            return true; //Process all other keycodes normally
    }
}

led_instruction_t led_instructions[] = {
    //LEDs are normally inactive, no processing is performed on them
    //Flags are used in matching criteria for an LED to be active and indicate how to color it
    //Flags can be found in tmk_core/protocol/arm_atsam/led_matrix.h (prefixed with LED_FLAG_)
    //LED IDs can be found in config_led.h in the keyboard's directory
    //Examples are below

    //All LEDs use the user's selected pattern (this is the factory default)
    //  { .flags = LED_FLAG_USE_ROTATE_PATTERN },

    /*
        Led coordinate system uses a bitmask to be able to select both a single key and a set of key (even non-adjacent keys)
        Online tool : http://daedalusrising.com/maskdrop/

        The bitmask is written as the following set with each led incrementing an `.id` from a power of 2 :
        .id0 = 0, .id1 = 1, .id2 = 0, .id3 = 0

        From "Esc" (included) to "s" (excluded) : increment .id0 (Esc = 1, 1 = 2, 2 = 4, ..., a = 2147483648)
        From "s" (included) to "Left Arrow" (excluded) : increment .id1
        From "Left Arrow" (included) to "Underglow LED under 4" (excluded) (bottom and left underglow + most of top underglow) : increment .id2
        From "Underglow LED under 4" (included) to "Underglow LED left of Ctrl" (included) (rest of top underglow + left underglow) : increment .id3
    */

    /**********************************************
                        Layer 0
    **********************************************/
    // All keys are white
    { .flags = LED_FLAG_MATCH_ID | LED_FLAG_MATCH_LAYER | LED_FLAG_USE_RGB, \
        .id0 = 4294967295, \
        .id1 = 4294967295, \
        .id2 = 7, \
        .id3 = 0, \
        .r = 255, \
        .g = 255, \
        .b = 225, \
    },

    /**********************************************
                        Layer 1
    **********************************************/
    // All keys are white
    { .flags = LED_FLAG_MATCH_ID | LED_FLAG_MATCH_LAYER | LED_FLAG_USE_RGB, \
        .id0 = 4294967295, \
        .id1 = 4294967295, \
        .id2 = 7, \
        .id3 = 0, \
        .r = 255, \
        .g = 255, \
        .b = 225, \
        .layer = 1, \
    },

    // But key "1" is red
    { .flags = LED_FLAG_MATCH_ID | LED_FLAG_MATCH_LAYER | LED_FLAG_USE_RGB, \
        .id0 = 2, \
        .id1 = 0, \
        .id2 = 0, \
        .id3 = 0, \
        .r = 255, \
        .g = 0, \
        .b = 0, \
        .layer = 1, \
    },

    /**********************************************
                        Layer 2
    **********************************************/
    // All keys are white
    { .flags = LED_FLAG_MATCH_ID | LED_FLAG_MATCH_LAYER | LED_FLAG_USE_RGB, \
        .id0 = 4294967295, \
        .id1 = 4294967295, \
        .id2 = 7, \
        .id3 = 0, \
        .r = 255, \
        .g = 255, \
        .b = 225, \
        .layer = 2, \
    },

    // But key "2" is red
    { .flags = LED_FLAG_MATCH_ID | LED_FLAG_MATCH_LAYER | LED_FLAG_USE_RGB, \
        .id0 = 4, \
        .id1 = 0, \
        .id2 = 0, \
        .id3 = 0, \
        .r = 255, \
        .g = 0, \
        .b = 0, \
        .layer = 2, \
    },

    //end must be set to 1 to indicate end of instruction set
     { .end = 1 }
};
