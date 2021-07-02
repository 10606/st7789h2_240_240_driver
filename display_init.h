#ifndef DISPLAY_INIT_H
#define DISPLAY_INIT_H

#include <stdint.h>
#include "stm32412g_discovery.h" 

#define display_init_error 1

#define LCD_RESET_PIN                    GPIO_PIN_11
#define LCD_RESET_GPIO_PORT              GPIOD
#define LCD_TE_PIN                       GPIO_PIN_3
#define LCD_TE_GPIO_PORT                 GPIOG
#define LCD_BL_CTRL_PIN                  GPIO_PIN_5
#define LCD_BL_CTRL_GPIO_PORT            GPIOF

extern void ST7789H2_Init (void);
uint8_t display_init ();
uint8_t display_init_ex (uint8_t orientation);

#endif

