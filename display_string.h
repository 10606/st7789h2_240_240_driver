#ifndef DISPLAY_STRING_H
#define DISPLAY_STRING_H

#include <stdint.h>
#include "Fonts/fonts.h"

typedef struct color_t
{
    uint16_t text;
    uint16_t back;
} color_t;

void display_string (uint32_t x_pos, uint32_t y_pos, char const * str, sFONT const * font, color_t const * color);
void display_string_c (uint32_t x_pos, uint32_t y_pos, char const * str, sFONT const * font, uint16_t color_back, uint16_t color_front);
void display_string_center (int32_t x_pos, uint32_t y_pos, char const * str, sFONT const * font, color_t const * color);
void display_string_center_c (int32_t x_pos, uint32_t y_pos, char const * str, sFONT const * font, uint16_t color_back, uint16_t color_text);
void fill_rect (uint32_t x_pos, uint32_t y_pos, uint32_t width, uint32_t height, uint16_t color);

#endif

