#ifndef ST7789H2_DRIVER_H
#define ST7789H2_DRIVER_H

#include <stdint.h>
#include "stm32412g_discovery.h"


typedef struct
{
    volatile uint16_t reg;
    volatile uint16_t ram;
} LCD_controller_t;

#define FMC_BANK1  ((LCD_controller_t *)(0x60000000 | 0x00000000))
#define FMC_BANK3  ((LCD_controller_t *)(0x60000000 | 0x08000000))

static inline void lcd_io_write_data (uint16_t data)
{
    FMC_BANK1->ram = data;
    __DSB();
}

static inline void lcd_io_write_reg (uint8_t reg)
{
    FMC_BANK1->reg = reg;
    __DSB();
}

static inline uint16_t lcd_io_read_data ()
{
    return FMC_BANK1->ram;
}


extern void LCD_IO_Init (void);

void draw_h_line (uint16_t x_pos, uint16_t y_pos, uint16_t x_size, uint16_t const * data);
void draw_h_line_mono (uint16_t x_pos, uint16_t y_pos, uint16_t x_size, uint16_t color);
void draw_RGB_image (uint16_t x_pos, uint16_t y_pos, uint16_t x_size, uint16_t y_size, uint16_t const * data);

void lcd_write_reg (uint8_t command, uint8_t * data, uint16_t size);
uint16_t lcd_read_reg (uint8_t command);
void lcd_set_orientation (uint8_t orientation);
void lcd_set_cursor (uint16_t x_pos, uint16_t y_pos);
void lcd_set_region (uint16_t x_pos, uint16_t y_pos, uint16_t x_size, uint16_t y_size);

void lcd_set_scroll_region (uint16_t top, uint16_t bottom);
void lcd_scroll (uint16_t vsp);



#define lcd_pixel_width 240
#define lcd_pixel_height 240

#define orientation_portrait         0x00
#define orientation_landscape        0x01
#define orientation_landscape_rot180 0x02








#define ST7789H2_DISPLAY_ON 0x29
#define ST7789H2_LCD_ID     0x04
#define ST7789H2_ID         0x85
#define ST7789H2_SLEEP_IN   0x10
#define ST7789H2_SLEEP_OUT  0x11
#define ST7789H2_CASET      0x2A
#define ST7789H2_RASET      0x2B
#define ST7789H2_COLOR_MODE 0x3A
#define ST7789H2_PORCH_CTRL 0xB2
#define ST7789H2_GATE_CTRL  0xB7
#define ST7789H2_VSCRDEF    0x33 
#define ST7789H2_VSCSAD     0x37
#define ST7789H2_WRITE_RAM  0x2C
#define ST7789H2_READ_RAM   0x2E
#define ST7789H2_VCOM_SET   0xBB
#define ST7789H2_LCM_CTRL   0xC0
#define ST7789H2_VDV_VRH_EN 0xC2
#define ST7789H2_VDV_SET    0xC4
#define ST7789H2_FR_CTRL    0xC6
#define ST7789H2_POWER_CTRL 0xD0
#define ST7789H2_PV_GAMMA_CTRL      0xE0
#define ST7789H2_NV_GAMMA_CTRL      0xE1
#define ST7789H2_NORMAL_DISPLAY     0x36
#define ST7789H2_TEARING_EFFECT     0x35
#define ST7789H2_DISPLAY_INVERSION  0x21

#define ST7789H2_RDDSM 0x0E






#endif

