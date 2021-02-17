/*
 * object_touch_screen.c
 *
 *  Created on: 6 f�vr. 2021
 *      Author: verhasya
 */



#include "libraries/gfx/nrf_lcd.h"
#include "../config.h"
#include "object_touch_screen.h"
#include "nrfx_spi.h"



#if OBJECT_ID == OBJECT_TOUCH_SCREEN



extern const nrf_lcd_t nrf_lcd_ili9341;



void object_touch_screen_process_main(void)
{
    typedef enum{
        INIT,
        DEFAULT
    }state_e;



    uint16_t x, y;
    static state_e state = INIT;
    switch(state){
    case INIT:
        nrf_lcd_ili9341.lcd_init();
        /*
        for(x=0; x<40; x++){
            for(y=0; y<320; y++){
                nrf_lcd_ili9341.lcd_pixel_draw(x, y, ILI9341_COLOR_MAGENTA);
            }
        }
        for(x=40; x<80; x++){
            for(y=0; y<320; y++){
                nrf_lcd_ili9341.lcd_pixel_draw(x, y, ILI9341_COLOR_BLUE);
            }
        }
        for(x=80; x<120; x++){
            for(y=0; y<320; y++){
                nrf_lcd_ili9341.lcd_pixel_draw(x, y, ILI9341_COLOR_GREEN);
            }
        }
        for(x=120; x<160; x++){
            for(y=0; y<320; y++){
                nrf_lcd_ili9341.lcd_pixel_draw(x, y, ILI9341_COLOR_YELLOW);
            }
        }
        for(x=160; x<200; x++){
            for(y=0; y<320; y++){
                nrf_lcd_ili9341.lcd_pixel_draw(x, y, ILI9341_COLOR_ORANGE);
            }
        }
        for(x=200; x<240; x++){
            for(y=0; y<320; y++){
                nrf_lcd_ili9341.lcd_pixel_draw(x, y, ILI9341_COLOR_RED);
            }
        }*/
        nrf_lcd_ili9341.lcd_rect_draw(110, 50, 10, 20, ILI9341_COLOR_RED);
        state = DEFAULT;
        break;
    default:
        nrf_lcd_ili9341.lcd_pixel_draw(5, 6, 0x00FF00);
        break;
    }
}



#endif
