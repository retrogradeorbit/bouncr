#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include <Arduino.h>

#define MENU_ITEM_COUNT 2
#define MENU_ITEM_DUTYCYCLE 0
#define MENU_ITEM_FREQUENCY 1
#define MENU_ITEM_INTENSITY 2

void display_menu(uint8_t num);
void display_value(uint8_t x, uint8_t width, const char *str);
void display_intensity(uint8_t intensity, uint8_t width);
void display_frequency(float freq, uint8_t width);
void display_dutycycle(uint8_t delay, uint8_t width);

#endif
