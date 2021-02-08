/*
 * matrix_leds_32x32.h
 *
 *  Created on: 5 févr. 2021
 *      Author: meven
 */

#ifndef BSP_MATRIX_LEDS_32X32_H_
#define BSP_MATRIX_LEDS_32X32_H_

#if USE_MATRIX

#include <stdint.h>

typedef uint8_t color_t;
#define COLOR_BLACK     0b00000000
#define COLOR_RED       0b00000100
#define COLOR_GREEN     0b00000010
#define COLOR_BLUE      0b00000001
#define COLOR_YELLOW    0b00000110
#define COLOR_CYAN      0b00000011
#define COLOR_PURPLE    0b00000101
#define COLOR_WHITE     0b00000111

#define xy_to_index(x, y) (32 * x + y)


void MATRIX_init(void);

void MATRIX_display(color_t * matrix);

void MATRIX_display_one_led(color_t matrix[32][32], uint8_t li, uint8_t col);


#endif /* BSP_MATRIX_LEDS_32X32_H_ */

#endif
