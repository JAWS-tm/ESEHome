/*
 * matrix_leds_32x32.h
 *
 *  Created on: 5 f�vr. 2021
 *      Author: meven
 */

#ifndef BSP_MATRIX_LEDS_32X32_H_
#define BSP_MATRIX_LEDS_32X32_H_


#include <stdint.h>

typedef uint8_t	matrix_t;

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

void MATRIX_display(matrix_t color[32][32]);

void MATRIX_french_flag(matrix_t matrix[32][32]);

void MATRIX_write_one_led(uint32_t i, uint32_t j, matrix_t matrix[32][32], uint32_t color);

void MATRIX_write_number(matrix_t matrix[32][32], uint32_t i, uint32_t j, uint32_t number, uint32_t color);

#endif /* BSP_MATRIX_LEDS_32X32_H_ */


