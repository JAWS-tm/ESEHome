#include "libraries/gfx/nrf_lcd.h"

extern const nrf_lcd_t nrf_lcd_ili9341;

void object_touch_screen_process_main(void)
{
	uint8_t x, y;
	nrf_lcd_ili9341.lcd_init();
	for(x=0; x<50; x++){
		for(y=100; y<150; y++){
			nrf_lcd_ili9341.lcd_pixel_draw(x, y, 0xFF00FF);
		}
	}

	while(1)
	{
		nrf_lcd_ili9341.lcd_pixel_draw(5, 6, 0x00FF00);
	}
}


