#include "st7789h2_driver.h"


/**
  ******************************************************************************
  * @file    stm32412g_discovery.c
  * @author  MCD Application Team
  * @brief   This file provides a set of firmware functions to manage LEDs,
  *          push-buttons and COM ports available on STM32412G-DISCOVERY board
  *          (MB1209) from STMicroelectronics.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */



void lcd_display_on (void)
{
    lcd_io_write_reg(ST7789H2_DISPLAY_ON);
    lcd_io_write_reg(ST7789H2_SLEEP_OUT);
}

void lcd_init_st7789h2 (void)
{
    uint8_t parameter[14];

    // initialize st7789h2 low level bus layer
    LCD_IO_Init();
    lcd_io_write_reg(ST7789H2_SLEEP_IN);
    HAL_Delay(10);

    // SW reset command
    lcd_io_write_reg(0x01);
    HAL_Delay(200);

    lcd_io_write_reg(ST7789H2_SLEEP_OUT);
    HAL_Delay(120);

    // normal display for driver down side
    parameter[0] = 0x00;
    lcd_write_reg(ST7789H2_NORMAL_DISPLAY, parameter, 1);

    // color mode 16bit / pixel
    parameter[0] = 0x05;
    lcd_write_reg(ST7789H2_COLOR_MODE, parameter, 1);

    // display inversion On
    lcd_io_write_reg(ST7789H2_DISPLAY_INVERSION);

    lcd_set_cursor(0, 0);

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
    parameter[0] = 0x01;
    lcd_write_reg(ST7789H2_TEARING_EFFECT, parameter, 0);
	
	// tearing modes
	parameter[0] = 0;
	parameter[1] = 0b11000000;
    lcd_write_reg(ST7789H2_RDDSM, parameter, 2);
}


void lcd_set_orientation (uint8_t orientation)
{
    uint8_t parameter[6];

    switch (orientation)
    {
    case orientation_landscape:
    default:
        parameter[0] = 0x00;
        break;
    case orientation_landscape_rot180:
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
    case orientation_portrait:
        parameter[0] = 0x60;
        break;
    }
    lcd_write_reg(ST7789H2_NORMAL_DISPLAY, parameter, 1);
}


