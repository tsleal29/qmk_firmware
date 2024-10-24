RGB_MATRIX_EFFECT(highlight_homing_keys)
RGB_MATRIX_EFFECT(homing_keys_bkg)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static bool highlight_homing_keys(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);

  RGB rgb = rgb_matrix_hsv_to_rgb(rgb_matrix_config.hsv);

  rgb_matrix_set_color(HOMING_KEY_INDEX, rgb.r, rgb.g, rgb.b);

  return rgb_matrix_check_finished_leds(led_max);
}

static bool homing_keys_bkg(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);

  rgb_matrix_set_color_all(RGB_OFF);

  uint8_t border_led_list[BORDER_LED_LIST_SIZE] = BORDER_LED_LIST;

  for (uint8_t i = 0; i < BORDER_LED_LIST_SIZE; i++) {
    rgb_matrix_set_color(border_led_list[i], 0x6a, 0xb4, 0xff);
  }

  RGB rgb = rgb_matrix_hsv_to_rgb(rgb_matrix_config.hsv);
  rgb_matrix_set_color(HOMING_KEY_INDEX, rgb.r, rgb.g, rgb.b);

  return rgb_matrix_check_finished_leds(led_max);
}

#endif
