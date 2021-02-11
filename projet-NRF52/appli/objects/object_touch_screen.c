/*
 * object_touch_screen.c
 *
 *  Created on: 6 févr. 2021
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



    uint8_t x, y;
    static state_e state = INIT;
    switch(state){
    case INIT:
        nrf_lcd_ili9341.lcd_init();
        for(x=0; x<50; x++){
            for(y=100; y<150; y++){
                nrf_lcd_ili9341.lcd_pixel_draw(x, y, 0xFF00FF);
            }
        }
        state = DEFAULT;
        break;
    default:
        nrf_lcd_ili9341.lcd_pixel_draw(5, 6, 0x00FF00);
        break;
    }
}



#endif
