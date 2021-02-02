#ifndef DISPLAY_INIT_H
#define DISPLAY_INIT_H

#include <stdint.h>
#include "st7789h2/st7789h2.h"
#include "stm32412g_discovery.h" 

#define display_init_error 1

uint8_t display_init ();
uint8_t display_init_ex (uint32_t orientation);

#endif

