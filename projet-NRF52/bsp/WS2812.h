 #ifndef NEOPIXEL_H
 #define NEOPIXEL_H


#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>


#define COLOR_BLUE	0x0000FF
#define COLOR_RED	0x00FF00
#define COLOR_GREEN	0xFF0000
#define COLOR_BLACK	0x000000
#define COLOR_WHITE	0xFFFFFF
#define COLOR_LOW_WHITE	0x7F7F7F

#define COLOR_YELLOW 0xFFFF00


/**
  @brief Initialize GPIO and data location
  @param[in] pointer to Strip structure
	@param[in] pin number for GPIO
*/
void LEDS_init(uint32_t pin_num, uint16_t num_leds);

void LEDS_refresh(void);

void LEDS_clear(void);

void LEDS_display_only_one_pixel(uint32_t pixel, uint32_t background, uint8_t rank);

void LEDS_display_full(uint32_t pixel);

void LEDS_display_matrix(uint32_t * pixels, uint32_t size);

#endif
