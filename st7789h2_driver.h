#ifndef ST7789H2_DRIVER_H
#define ST7789H2_DRIVER_H

#include <stdint.h>
#include "stm32412g_discovery.h"

extern void     LCD_IO_Init (void);
extern void     LCD_IO_WriteReg (uint8_t Reg);
extern void     LCD_IO_WriteData (uint16_t RegValue);
extern void     LCD_IO_WriteMultipleData (uint16_t *pData, uint32_t Size);
extern uint16_t LCD_IO_ReadData (void);
extern void     LCD_IO_Delay (uint32_t Delay);

void draw_h_line (uint16_t x_pos, uint16_t y_pos, uint16_t x_size, uint16_t * data);
void draw_h_line_mono (uint16_t x_pos, uint16_t y_pos, uint16_t x_size, uint16_t color);
void draw_RGB_image (uint16_t x_pos, uint16_t y_pos, uint16_t x_size, uint16_t y_size, uint16_t * data);

void lcd_write_reg (uint8_t command, uint8_t * data, uint16_t size);
uint16_t lcd_read_reg (uint8_t command);
void lcd_set_orientation (uint8_t orientation);
void lcd_set_cursor (uint16_t x_pos, uint16_t y_pos);

#define lcd_pixel_width 240
#define lcd_pixel_height 240

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

#define ST7789H2_ORIENTATION_PORTRAIT         0x00
#define ST7789H2_ORIENTATION_LANDSCAPE        0x01
#define ST7789H2_ORIENTATION_LANDSCAPE_ROT180 0x02


#endif

