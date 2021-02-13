#include "st7789h2_driver.h"

#include "stm32f4xx.h"

typedef struct
{
    uint16_t reg;
    uint16_t ram;
} LCD_controller_t;

#define FMC_BANK1  ((LCD_controller_t *)(0x60000000 | 0x00000000))
#define FMC_BANK3  ((LCD_controller_t *)(0x60000000 | 0x08000000))

void lcd_io_write_data (uint16_t data)
{
    FMC_BANK1->ram = data;
    __DSB();
}

void lcd_io_write_reg (uint8_t reg)
{
    FMC_BANK1->reg = reg;
    __DSB();
}

uint16_t lcd_io_read_data ()
{
    return FMC_BANK1->ram;
}



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

void draw_h_line (uint16_t x_pos, uint16_t y_pos, uint16_t x_size, uint16_t * data)
{
    lcd_set_cursor(x_pos, y_pos);
    // prepare to write to LCD RAM
    lcd_io_write_reg(ST7789H2_WRITE_RAM);
    for (uint32_t i = 0; i != x_size; ++i)
        lcd_io_write_data(data[i]);
}

void draw_RGB_image (uint16_t x_pos, uint16_t y_pos, uint16_t x_size, uint16_t y_size, uint16_t * data)
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

