
#include "quantum.h"
#include "wireless.h"
#include "indicator.h"
#include "lpm.h"
#if defined(PROTOCOL_CHIBIOS)
#    include <usb_main.h>
#elif if defined(PROTOCOL_LUFA)
#    include "lufa.h"
#endif
#include "eeprom.h"

#if (defined(LED_MATRIX_ENABLE) || defined(RGB_MATRIX_ENABLE)) && defined(BAT_LEVEL_LED_LIST)

#ifndef BAT_LEVEL_GROWING_INTERVAL
#    define BAT_LEVEL_GROWING_INTERVAL 150
#endif

#ifndef BAT_LEVEL_ON_INTERVAL
#    define BAT_LEVEL_ON_INTERVAL 3000
#endif

#ifdef LED_MATRIX_ENABLE
#    define LED_DRIVER_IS_ENABLED led_matrix_is_enabled
#endif

#ifdef RGB_MATRIX_ENABLE
#    define LED_DRIVER_IS_ENABLED rgb_matrix_is_enabled
#endif

#ifndef BAT_LEVEL_LED_LIST_SIZE
#    define BAT_LEVEL_LED_LIST_SIZE 10
#endif

#ifndef BAT_LEVEL_STEP
#    define BAT_LEVEL_STEP 10
#endif

enum {
    BAT_LVL_ANI_NONE,
    BAT_LVL_ANI_GROWING,
    BAT_LVL_ANI_BLINK_OFF,
    BAT_LVL_ANI_BLINK_ON,
};

static uint8_t  animation_state = 0;
static uint32_t bat_lvl_ani_timer_buffer = 0;
static uint8_t  bat_percentage;
static uint8_t  cur_percentage;
static uint32_t time_interval;
#ifdef RGB_MATRIX_ENABLE
static uint8_t r, g, b;
#endif

extern indicator_config_t indicator_config;
extern backlight_state_t  original_backlight_state;

void bat_level_animiation_start(uint8_t percentage) {
    /* Turn on backlight mode for indicator */
    indicator_enable();

    animation_state          = BAT_LVL_ANI_GROWING;
    bat_percentage           = percentage;
    bat_lvl_ani_timer_buffer = timer_read32();
    cur_percentage           = 0;
    time_interval            = BAT_LEVEL_GROWING_INTERVAL;
#ifdef RGB_MATRIX_ENABLE
    r = g = b = 255;
#endif
}

void bat_level_animiation_stop(void) {
    animation_state = BAT_LVL_ANI_NONE;
}

bool bat_level_animiation_actived(void) {
    return animation_state;
}

void bat_level_animiation_indicate(void) {
#ifdef LED_MATRIX_ENABLE
    uint8_t  bat_lvl_led_list[BAT_LEVEL_LED_LIST_SIZE] = BAT_LEVEL_LED_LIST;

#ifdef BAT_LEVEL_ANIMATION_NO_CLEAR_ALL
    for (uint8_t i = 0; i < BAT_LEVEL_LED_LIST_SIZE; i++) {
        led_matrix_set_value(bat_lvl_led_list[i], 0);
    }
#else
    for (uint8_t i = 0; i <= LED_MATRIX_LED_COUNT; i++) {
        led_matrix_set_value(i, 0);
    }
#endif

    if (animation_state == BAT_LVL_ANI_GROWING || animation_state == BAT_LVL_ANI_BLINK_ON)
        for (uint8_t i = 0; i < cur_percentage / BAT_LEVEL_STEP; i++)
            led_matrix_set_value(bat_lvl_led_list[i], 255);
#endif

#ifdef RGB_MATRIX_ENABLE
    uint8_t  bat_lvl_led_list[BAT_LEVEL_LED_LIST_SIZE] = BAT_LEVEL_LED_LIST;

#ifdef BAT_LEVEL_ANIMATION_NO_CLEAR_ALL
    for (uint8_t i = 0; i < BAT_LEVEL_LED_LIST_SIZE; i++) {
        rgb_matrix_set_color(bat_lvl_led_list[i], 0, 0, 0);
    }
#else
    for (uint8_t i = 0; i <= RGB_MATRIX_LED_COUNT; i++) {
        rgb_matrix_set_color(i, 0, 0, 0);
    }
#endif

    if (animation_state == BAT_LVL_ANI_GROWING || animation_state == BAT_LVL_ANI_BLINK_ON) {
        for (uint8_t i = 0; i < cur_percentage / BAT_LEVEL_STEP; i++) {
            rgb_matrix_set_color(bat_lvl_led_list[i], r, g, b);
        }
    }
#endif
}

void bat_level_animiation_update(void) {
    switch (animation_state) {
        case BAT_LVL_ANI_GROWING:
            if (cur_percentage < bat_percentage)
                cur_percentage += BAT_LEVEL_STEP;
            else {
                if (cur_percentage == 0) cur_percentage = BAT_LEVEL_STEP;
                animation_state = BAT_LVL_ANI_BLINK_OFF;
            }
            break;

        case BAT_LVL_ANI_BLINK_OFF:
#ifdef RGB_MATRIX_ENABLE
            if (bat_percentage < 30) {
                r = 255;
                b = g = 0;
            } else {
                r = b = 0;
                g     = 255;
            }
#endif
            time_interval   = BAT_LEVEL_ON_INTERVAL;
            animation_state = BAT_LVL_ANI_BLINK_ON;
            break;

        case BAT_LVL_ANI_BLINK_ON:
            animation_state = BAT_LVL_ANI_NONE;
            indicator_eeconfig_reload();
            if (indicator_config.value == 0 && !LED_DRIVER_IS_ENABLED()) {
                indicator_disable();
            }
            lpm_timer_reset();
            break;

        default:
            break;
    }

    bat_lvl_ani_timer_buffer = timer_read32();
}

void bat_level_animiation_task(void) {
    if (animation_state && sync_timer_elapsed32(bat_lvl_ani_timer_buffer) > time_interval) {
        bat_level_animiation_update();
    }
}

#endif
