#ifndef DISPLAY_INIT_H
#define DISPLAY_INIT_H

#include <stdint.h>
#include "stm32412g_discovery.h" 

#define display_init_error 1

extern void ST7789H2_Init (void);
uint8_t display_init ();
uint8_t display_init_ex (uint8_t orientation);

#endif

