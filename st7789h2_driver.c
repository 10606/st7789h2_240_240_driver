#include "st7789h2_driver.h"

void lcd_write_reg (uint8_t command, uint8_t * data, uint16_t size)
{
    // prepare to write to LCD RAM
    LCD_IO_WriteReg(command);

    for (uint16_t i = 0; i != size; i++)
        LCD_IO_WriteData(data[i]);
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
    LCD_IO_WriteReg(command);
    LCD_IO_ReadData();
    return LCD_IO_ReadData();
}


void lcd_set_orientation (uint8_t orientation)
{
    uint8_t parameter[6];

    switch (orientation)
    {
    case ST7789H2_ORIENTATION_LANDSCAPE:
    default:
        parameter[0] = 0x00;
        break;
    case ST7789H2_ORIENTATION_LANDSCAPE_ROT180:
        // vertical scrolling definition
        // TFA describes the Top Fixed Area
        parameter[0] = 0x00;
        parameter[1] = 0x00;
        // VSA describes the height of the Vertical Scrolling Area
        parameter[2] = 0x01;
        parameter[3] = 0xF0;
        // BFA describes the Bottom Fixed Area
        parameter[4] = 0x00;
        parameter[5] = 0x00;
        lcd_write_reg(ST7789H2_VSCRDEF, parameter, 6);

        // vertical scroll start address of RAM 
        // GRAM row nbr (320) - display row nbr (240) = 80 = 0x50 
        parameter[0] = 0x00;
        parameter[1] = 0x50;
        lcd_write_reg(ST7789H2_VSCSAD, parameter, 2);

        parameter[0] = 0xC0;
        break;
    case ST7789H2_ORIENTATION_PORTRAIT:
        parameter[0] = 0x60;
        break;
    }
    lcd_write_reg(ST7789H2_NORMAL_DISPLAY, parameter, 1);
}


void draw_h_line (uint16_t x_pos, uint16_t y_pos, uint16_t x_size, uint16_t * data)
{
    lcd_set_cursor(x_pos, y_pos);
    // prepare to write to LCD RAM
    LCD_IO_WriteReg(ST7789H2_WRITE_RAM);
    LCD_IO_WriteMultipleData(data, x_size);
}

void draw_RGB_image (uint16_t x_pos, uint16_t y_pos, uint16_t x_size, uint16_t y_size, uint16_t * data)
{
    lcd_set_region(x_pos, y_pos, x_size, y_size);
    // prepare to write to LCD RAM
    LCD_IO_WriteReg(ST7789H2_WRITE_RAM);
    LCD_IO_WriteMultipleData(data, x_size * y_size);
}

void draw_h_line_mono (uint16_t x_pos, uint16_t y_pos, uint16_t x_size, uint16_t color)
{
    lcd_set_cursor(x_pos, y_pos);
    
    // prepare to write to LCD RAM
    LCD_IO_WriteReg(ST7789H2_WRITE_RAM);

    for (uint16_t i = 0; i != x_size; ++i)
        LCD_IO_WriteData(color);
}

