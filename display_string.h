#ifndef DISPLAY_STRING_H
#define DISPLAY_STRING_H

#include <stdint.h>
#include "fonts/fonts.h"

typedef struct color_t
{
    uint16_t text;
    uint16_t back;
} color_t;

void display_string (uint32_t x_pos, uint32_t y_pos, char const * str, sFONT const * font, color_t const color);
void display_string_e (uint32_t x_pos, uint32_t y_pos, char const * str, sFONT const * font, color_t const color, char end);
void display_string_center (int32_t x_pos, uint32_t y_pos, char const * str, sFONT const * font, color_t const color);
void display_string_center_e (int32_t x_pos, uint32_t y_pos, char const * str, sFONT const * font, color_t const color, char end);
void fill_rect (uint32_t x_pos, uint32_t y_pos, uint32_t width, uint32_t height, uint16_t color);

#endif

