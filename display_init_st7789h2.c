#include "st7789h2_driver.h"

void lcd_display_on (void)
{
    LCD_IO_WriteReg(ST7789H2_DISPLAY_ON);
    LCD_IO_WriteReg(ST7789H2_SLEEP_OUT);
}

void lcd_init_st7789h2 (void)
{
    uint8_t parameter[14];

    // initialize st7789h2 low level bus layer
    LCD_IO_Init();
    LCD_IO_WriteReg(ST7789H2_SLEEP_IN);
    LCD_IO_Delay(10);

    // SW reset command
    LCD_IO_WriteReg(0x01);
    LCD_IO_Delay(200);

    LCD_IO_WriteReg(ST7789H2_SLEEP_OUT);
    LCD_IO_Delay(120);

    // normal display for driver down side
    parameter[0] = 0x00;
    lcd_write_reg(ST7789H2_NORMAL_DISPLAY, parameter, 1);

    // color mode 16bit / pixel
    parameter[0] = 0x05;
    lcd_write_reg(ST7789H2_COLOR_MODE, parameter, 1);

    // display inversion On
    LCD_IO_WriteReg(ST7789H2_DISPLAY_INVERSION);

    lcd_set_cursor (0, 0);

    // ST7789H2 frame rate setting
    // PORCH control setting 
    parameter[0] = 0x0C;
    parameter[1] = 0x0C;
    parameter[2] = 0x00;
    parameter[3] = 0x33;
    parameter[4] = 0x33;
    lcd_write_reg(ST7789H2_PORCH_CTRL, parameter, 5);

    // GATE control setting
    parameter[0] = 0x35;
    lcd_write_reg(ST7789H2_GATE_CTRL, parameter, 1);

    // ST7789H2 power setting
    // VCOM setting
    parameter[0] = 0x1F;
    lcd_write_reg(ST7789H2_VCOM_SET, parameter, 1);

    // LCM Control setting
    parameter[0] = 0x2C;
    lcd_write_reg(ST7789H2_LCM_CTRL, parameter, 1);

    // VDV and VRH command enable
    parameter[0] = 0x01;
    parameter[1] = 0xC3;
    lcd_write_reg(ST7789H2_VDV_VRH_EN, parameter, 2);

    // VDV set
    parameter[0] = 0x20;
    lcd_write_reg(ST7789H2_VDV_SET, parameter, 1);

    // frame rate control in normal mode
    parameter[0] = 0x0F;
    lcd_write_reg(ST7789H2_FR_CTRL, parameter, 1);

    // power control
    parameter[0] = 0xA4;
    parameter[1] = 0xA1;
    lcd_write_reg(ST7789H2_POWER_CTRL, parameter, 1);

    // ST7789H2 gamma setting
    parameter[0] = 0xD0;
    parameter[1] = 0x08;
    parameter[2] = 0x11;
    parameter[3] = 0x08;
    
    // positive voltage gamma control
    parameter[4] = 0x0C;
    parameter[5] = 0x15;
    parameter[6] = 0x39;
    parameter[7] = 0x33;
    parameter[8] = 0x50;
    parameter[9] = 0x36;
    parameter[10] = 0x13;
    parameter[11] = 0x14;
    parameter[12] = 0x29;
    parameter[13] = 0x2D;
    lcd_write_reg(ST7789H2_PV_GAMMA_CTRL, parameter, 14);
    // negative voltage gamma control
    parameter[4] = 0x06;
    parameter[5] = 0x06;
    parameter[6] = 0x39;
    parameter[7] = 0x44;
    parameter[8] = 0x51;
    parameter[9] = 0x0B;
    parameter[10] = 0x16;
    parameter[11] = 0x14;
    parameter[12] = 0x2F;
    parameter[13] = 0x31;
    lcd_write_reg(ST7789H2_NV_GAMMA_CTRL, parameter, 14);

    lcd_display_on();

    // tearing effect line on: option (00h:VSYNC interface OFF, 01h:VSYNC interface ON)
    parameter[0] = 0x00;
    lcd_write_reg(ST7789H2_TEARING_EFFECT, parameter, 1);
}

