#include "st7789h2_driver.h"


void lcd_write_reg (uint8_t command, uint8_t * data, uint16_t size)
{
    // prepare to write to LCD RAM
    lcd_io_write_reg(command);

    for (uint16_t i = 0; i != size; i++)
        lcd_io_write_data(data[i]);
}

void lcd_set_cursor (uint16_t x_pos, uint16_t y_pos)
{
    uint8_t parameter[4];
    parameter[0] = 0x00;
    parameter[2] = 0x00;
    parameter[3] = 239; // end pos

    // comumn addrses set
    parameter[1] = x_pos;
    lcd_write_reg(ST7789H2_CASET, parameter, 4);
    // row addrses set
    parameter[1] = y_pos;
    lcd_write_reg(ST7789H2_RASET, parameter, 4);
}

void lcd_set_region (uint16_t x_pos, uint16_t y_pos, uint16_t x_size, uint16_t y_size)
{
    uint8_t parameter[4];
    parameter[0] = 0x00;
    parameter[2] = 0x00;

    // comumn addrses set
    parameter[1] = x_pos;
    parameter[3] = x_pos + x_size;
    lcd_write_reg(ST7789H2_CASET, parameter, 4);
    // row addrses set
    parameter[1] = y_pos;
    parameter[3] = y_pos + y_size;
    lcd_write_reg(ST7789H2_RASET, parameter, 4);
}

uint16_t lcd_read_reg (uint8_t command)
{
    lcd_io_write_reg(command);
    lcd_io_read_data();
    return lcd_io_read_data();
}

void draw_h_line (uint16_t x_pos, uint16_t y_pos, uint16_t x_size, uint16_t const * data)
{
    lcd_set_cursor(x_pos, y_pos);
    // prepare to write to LCD RAM
    lcd_io_write_reg(ST7789H2_WRITE_RAM);
    for (uint32_t i = 0; i != x_size; ++i)
        lcd_io_write_data(data[i]);
}

void draw_RGB_image (uint16_t x_pos, uint16_t y_pos, uint16_t x_size, uint16_t y_size, uint16_t const * data)
{
    lcd_set_region(x_pos, y_pos, x_size, y_size);
    // prepare to write to LCD RAM
    lcd_io_write_reg(ST7789H2_WRITE_RAM);
    for (uint32_t i = 0; i != x_size * y_size; ++i)
        lcd_io_write_data(data[i]);
}

void draw_h_line_mono (uint16_t x_pos, uint16_t y_pos, uint16_t x_size, uint16_t color)
{
    lcd_set_cursor(x_pos, y_pos);
    
    // prepare to write to LCD RAM
    lcd_io_write_reg(ST7789H2_WRITE_RAM);

    for (uint16_t i = 0; i != x_size; ++i)
        lcd_io_write_data(color);
}

void lcd_set_scroll_region (uint16_t top, uint16_t bottom)
{
    //static uint16_t scrolled = 0;

    uint16_t tfa = top;
    uint16_t vsa = bottom - top;
    uint16_t bfa = 80 + lcd_pixel_height - top - bottom;

    lcd_io_write_reg(ST7789H2_VSCRDEF);
    lcd_io_write_data(tfa >> 8);
    lcd_io_write_data(tfa & 0xff);
    lcd_io_write_data(vsa >> 8);
    lcd_io_write_data(vsa & 0xff);
    lcd_io_write_data(bfa >> 8);
    lcd_io_write_data(bfa & 0xff);
    
    //uint16_t vsp = tfa + (value + scrolled) % bottom;
    
    
    //scrolled = (scrolled + value) % bottom; 
}

void lcd_scroll (uint16_t vsp)
{
    lcd_io_write_reg(ST7789H2_VSCSAD);
    lcd_io_write_data(vsp >> 8);
    lcd_io_write_data(vsp & 0xff);
}

