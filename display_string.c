#include "display_string.h"
#include <stdint.h>
#include <string.h>
#include "st7789h2_driver.h"
#include "fonts/fonts.h"

void display_string_e (point_t pos, char const * str, sFONT const * font, color_t const color, char end)
{
    const uint32_t f_height = font->Height;
    const uint32_t f_width  = font->Width;
    const uint32_t f_b_width = (f_width + 7) / 8;
    const uint32_t f_t_width = 7 - (f_width + 7) % 8;
    pos.x %= lcd_pixel_width;
    pos.y %= lcd_pixel_height;
    
    const uint32_t x_str_size = (lcd_pixel_width - pos.x) / f_width;
    const uint32_t x_line_size = x_str_size * f_width;
    
    const uint32_t symbol_multiplier = f_b_width * f_height;
    uint32_t len = strlen(str);
    if (len > x_str_size)
        len = x_str_size;
    const uint32_t x_line_end = len * f_width;
 
    if (end)
        lcd_set_region(pos.x, pos.y, x_line_size - 1, f_height);
    else
        lcd_set_region(pos.x, pos.y, x_line_end - 1, f_height);
    lcd_io_write_reg(ST7789H2_WRITE_RAM);
    
    uint8_t const * line_addr = font->table;
    for (uint32_t i = 0; i != f_height; ++i, line_addr += f_b_width)
    {
        for (uint32_t j = 0; j != len; ++j)
        {
            uint8_t const * f_line = 
                line_addr +  //table + line
                (uint8_t)(str[j]) * symbol_multiplier; //symbol

            uint32_t k;
            for (k = 0; k != f_b_width - 1; ++k)
                for (uint32_t c = 8; c-- != 0;)     
                    lcd_io_write_data(((f_line[k] >> c) & 1)? color.text : color.back);

            // last can be not full
            for (uint32_t c = 8; c-- != f_t_width;)
                lcd_io_write_data(((f_line[k] >> c) & 1)? color.text : color.back);
        }
        if (end)
        {
            for (uint32_t j = x_line_end; j < x_line_size; ++j)
                lcd_io_write_data(color.back);
        }
    }
}

void display_string (point_t pos, char const * str, sFONT const * font, color_t const color)
{
    display_string_e(pos, str, font, color, 1);
}

void fill_rect (point_t pos, point_t size, uint16_t color)
{
    for (uint32_t i = 0; i != size.y; ++i)
        draw_h_line_mono(pos.x, pos.y + i, size.x, color);
}

void display_string_center_e (point_t pos, char const * str, sFONT const * font, color_t const color, char end)
{
    uint32_t f_width  = font->Width;
    uint32_t len = strlen(str);
    uint32_t x_lcd_size = lcd_pixel_width;
    pos.x %= x_lcd_size;
    len %= x_lcd_size;
    
    uint32_t start_x_pos = (x_lcd_size / 2) - (len * f_width / 2) + pos.x;
    if (start_x_pos < x_lcd_size) //start on screen
    {
        pos.x = start_x_pos;
        display_string_e(pos, str, font, color, end);
        return;
    }
    uint32_t end_x_pos = start_x_pos + len * f_width;
    if ((end_x_pos < x_lcd_size) ||
        (end_x_pos < start_x_pos)) //start on left
    {
        uint32_t start_index = (-start_x_pos + f_width - 1) / f_width;
        pos.x = start_x_pos + start_index * f_width;
        str += start_index;
        display_string_e(pos, str, font, color, end);
    }
}

void display_string_center (point_t pos, char const * str, sFONT const * font, color_t const color)
{
    display_string_center_e(pos, str, font, color, 1);
}

