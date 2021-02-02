#include "st7789h2_driver.h"

#include "st7789h2/st7789h2.h"

void draw_h_line (uint16_t x_pos, uint16_t y_pos, uint16_t x_size, uint16_t * data)
{
    ST7789H2_SetCursor(x_pos, y_pos);

    // prepare to write to LCD RAM
    ST7789H2_WriteReg(ST7789H2_WRITE_RAM, (uint8_t *)NULL, 0);

    for (uint32_t i = 0; i < x_size; i++)
    {
        LCD_IO_WriteData(data[i]);
    }
}

void draw_RGB_image (uint16_t x_pos, uint16_t y_pos, uint16_t x_size, uint16_t y_size, uint16_t * data)
{
    for (uint32_t i = 0; i < y_size; ++i)
    {
        // draw one line of the picture 
        draw_h_line(x_pos, y_pos + i, x_size, data + (i * x_size));
    }
}

void draw_h_line_mono (uint16_t x_pos, uint16_t y_pos, uint16_t x_size, uint16_t color)
{
    ST7789H2_SetCursor(x_pos, y_pos);
    
    // prepare to write to LCD RAM
    ST7789H2_WriteReg(ST7789H2_WRITE_RAM, (uint8_t *)NULL, 0);

    for (uint32_t i = 0; i != x_size; ++i)
    {
        LCD_IO_WriteData(color);
    }
}
