#ifndef ST7789H2_DRIVER_H
#define ST7789H2_DRIVER_H

#include <stdint.h>

void draw_h_line (uint16_t x_pos, uint16_t y_pos, uint16_t x_size, uint16_t * data);
void draw_h_line_mono (uint16_t x_pos, uint16_t y_pos, uint16_t x_size, uint16_t color);
void draw_RGB_image (uint16_t x_pos, uint16_t y_pos, uint16_t x_size, uint16_t y_size, uint16_t * data);

#endif

