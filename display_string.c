#include "display_string.h"
#include <stdint.h>
#include <string.h>
#include "st7789h2_driver.h"
#include "Fonts/fonts.h"

void display_string (uint32_t x_pos, uint32_t y_pos, char const * str, sFONT const * font, color_t const * color)
{
    const uint32_t f_height = font->Height;
    const uint32_t f_width  = font->Width;
    const uint32_t f_b_width = (f_width + 7) / 8;
    const uint32_t x_lcd_size = lcd_pixel_width;
    const uint32_t y_lcd_size = lcd_pixel_height;
    x_pos %= x_lcd_size;
    y_pos %= y_lcd_size;
    
    const uint32_t x_str_size = (x_lcd_size - x_pos) / f_width;
    const uint32_t x_line_size = x_str_size * f_width;
    
    const uint32_t offset = 8 * f_b_width - 1;
    const uint32_t symbol_multiplier = f_b_width * f_height;
    uint32_t len = strlen(str);
    if (len > x_str_size)
        len = x_str_size;
    const uint32_t x_line_end = len * f_width;
 
    lcd_set_region(x_pos, y_pos, x_line_size - 1, f_height);
    lcd_io_write_reg(ST7789H2_WRITE_RAM);
    
    uint16_t colors[2] = {color->back, color->text};
    uint8_t const * line_addr = font->table;
    for (uint32_t i = 0; i != f_height; ++i, line_addr += f_b_width)
    {
        for (uint32_t j = 0; j != len; ++j)
        {
            uint8_t const * f_line = 
                line_addr +  //table + line
                (uint8_t)(str[j] - ' ') * symbol_multiplier; //symbol

            uint32_t f_line_v = f_line[0];
            for (uint32_t k = 1; k != f_b_width; ++k)
            {
                f_line_v <<= 8;
                f_line_v += f_line[k];
            }
            
            for (uint32_t k = 0, b_pos = offset; k < f_width; k++, b_pos--)
                lcd_io_write_data(colors[1 & (f_line_v >> b_pos)]);
        }
        for (uint32_t j = x_line_end; j < x_line_size; ++j)
            lcd_io_write_data(colors[0]);
    }
}

void display_string_c (uint32_t x_pos, uint32_t y_pos, char const * str, sFONT const * font, uint16_t color_back, uint16_t color_text)
{
    color_t color = {color_text, color_back};
    display_string(x_pos, y_pos, str, font, &color);
}

void fill_rect (uint32_t x_pos, uint32_t y_pos, uint32_t width, uint32_t height, uint16_t color)
{
    for (uint32_t i = 0; i != height; ++i)
        draw_h_line_mono(x_pos, y_pos + i, width, color);
}

void display_string_center (int32_t x_pos, uint32_t y_pos, char const * str, sFONT const * font, color_t const * color)
{
    uint32_t f_width  = font->Width;
    uint32_t len = strlen(str);
    uint32_t x_lcd_size = lcd_pixel_width;
    x_pos %= x_lcd_size;
    len %= x_lcd_size;
    
    uint32_t start_x_pos = (x_lcd_size / 2) - (len * f_width / 2) + x_pos;
    if (start_x_pos < x_lcd_size) //start on screen
    {
        display_string(start_x_pos, y_pos, str, font, color);
        return;
    }
    uint32_t end_x_pos = start_x_pos + len * f_width;
    if ((end_x_pos < x_lcd_size) ||
        (end_x_pos < start_x_pos)) //start on left
    {
        uint32_t start_index = (-start_x_pos + f_width - 1) / f_width;
        display_string(start_x_pos + start_index * f_width, y_pos, str + start_index, font, color);
    }
}

void display_string_center_c (int32_t x_pos, uint32_t y_pos, char const * str, sFONT const * font, uint16_t color_back, uint16_t color_text)
{
    color_t color = {color_text, color_back};
    display_string_center(x_pos, y_pos, str, font, &color);
}

