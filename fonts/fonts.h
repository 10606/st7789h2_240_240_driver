#ifndef FONTS_H
#define FONTS_H

#include <stdint.h>

typedef struct
{    
  const uint8_t * table;
  uint16_t Width;
  uint16_t Height;  
} sFONT;

extern sFONT font_12;
extern sFONT font_14;
extern sFONT font_16;
extern sFONT font_18;
extern sFONT font_20;
extern sFONT font_22;
extern sFONT font_24;


#endif

