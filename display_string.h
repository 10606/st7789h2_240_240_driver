#ifndef DISPLAY_STRING_H
#define DISPLAY_STRING_H

#include <stdint.h>
#include "fonts/fonts.h"

typedef struct color_t
{
    uint16_t text;
    uint16_t back;
} color_t;

typedef struct point_t
{
    uint32_t x;
    uint32_t y;
} point_t;

void display_string (point_t pos, char const * str, sFONT const * font, color_t const color);
void display_string_e (point_t pos, char const * str, sFONT const * font, color_t const color, char end);
void display_string_center (point_t pos, char const * str, sFONT const * font, color_t const color);
void display_string_center_e (point_t pos, char const * str, sFONT const * font, color_t const color, char end);
void fill_rect (point_t pos, point_t size, uint16_t color);

#endif

