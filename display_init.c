#include "display_init.h"

#include "st7789h2_driver.h"

#define LCD_RESET_PIN                    GPIO_PIN_11
#define LCD_RESET_GPIO_PORT              GPIOD
#define LCD_TE_PIN                       GPIO_PIN_3
#define LCD_TE_GPIO_PORT                 GPIOG
#define LCD_BL_CTRL_PIN                  GPIO_PIN_5
#define LCD_BL_CTRL_GPIO_PORT            GPIOF

#define LCD_RESET_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOD_CLK_ENABLE()
#define LCD_TE_GPIO_CLK_ENABLE()         __HAL_RCC_GPIOG_CLK_ENABLE()
#define LCD_BL_CTRL_GPIO_CLK_ENABLE()    __HAL_RCC_GPIOF_CLK_ENABLE()

extern void lcd_init_st7789h2 (void);

void display_LCD_MspInit ()
{
    GPIO_InitTypeDef gpio_init_structure;

    // Enable GPIOs clock
    LCD_RESET_GPIO_CLK_ENABLE();
    LCD_TE_GPIO_CLK_ENABLE();
    LCD_BL_CTRL_GPIO_CLK_ENABLE();

    // LCD_RESET GPIO configuration
    gpio_init_structure.Pin       = LCD_RESET_PIN;     // LCD_RESET pin has to be manually controlled
    gpio_init_structure.Pull      = GPIO_NOPULL;
    gpio_init_structure.Speed     = GPIO_SPEED_FAST;
    gpio_init_structure.Mode      = GPIO_MODE_OUTPUT_PP;
    HAL_GPIO_Init(LCD_RESET_GPIO_PORT, &gpio_init_structure);

    // LCD_TE GPIO configuration
    gpio_init_structure.Pin       = LCD_TE_PIN;        // LCD_TE pin has to be manually managed
    gpio_init_structure.Mode      = GPIO_MODE_INPUT;
    HAL_GPIO_Init(LCD_TE_GPIO_PORT, &gpio_init_structure);

    // LCD_BL_CTRL GPIO configuration
    gpio_init_structure.Pin       = LCD_BL_CTRL_PIN;   // LCD_BL_CTRL pin has to be manually controlled
    gpio_init_structure.Mode      = GPIO_MODE_OUTPUT_PP;
    HAL_GPIO_Init(LCD_BL_CTRL_GPIO_PORT, &gpio_init_structure);
}


uint16_t lcd_read_id ()
{
    LCD_IO_Init();
    return lcd_read_reg(ST7789H2_LCD_ID);
}


uint8_t display_init_ex (uint8_t orientation)
{ 
    uint8_t ret = display_init_error;

    // Initialize LCD special pins GPIOs
    display_LCD_MspInit();
  
    // Backlight control signal assertion
    HAL_GPIO_WritePin(LCD_BL_CTRL_GPIO_PORT, LCD_BL_CTRL_PIN, GPIO_PIN_SET);
  
    // Apply hardware reset according to procedure indicated in FRD154BP2901 documentation 
    HAL_GPIO_WritePin(LCD_RESET_GPIO_PORT, LCD_RESET_PIN, GPIO_PIN_RESET);
    HAL_Delay(5);   // Reset signal asserted during 5ms 
    HAL_GPIO_WritePin(LCD_RESET_GPIO_PORT, LCD_RESET_PIN, GPIO_PIN_SET);
    HAL_Delay(10);  // Reset signal released during 10ms
    HAL_GPIO_WritePin(LCD_RESET_GPIO_PORT, LCD_RESET_PIN, GPIO_PIN_RESET);
    HAL_Delay(20);  // Reset signal asserted during 20ms
    HAL_GPIO_WritePin(LCD_RESET_GPIO_PORT, LCD_RESET_PIN, GPIO_PIN_SET);
    HAL_Delay(10);  // Reset signal released during 10ms
  
    if (lcd_read_id() == ST7789H2_ID)
    {    
        lcd_init_st7789h2();
        lcd_set_orientation(orientation);
        ret = 0;
    }
    return ret;
}


uint8_t display_init ()
{
    //ST7789H2_ORIENTATION_PORTRAIT
    //ST7789H2_ORIENTATION_LANDSCAPE
    //ST7789H2_ORIENTATION_LANDSCAPE_ROT180
    return display_init_ex(ST7789H2_ORIENTATION_LANDSCAPE);
}

