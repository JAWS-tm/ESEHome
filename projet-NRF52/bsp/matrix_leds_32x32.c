/*
 * matrix_leds_32x32.c
 *
 *  Created on: 5 févr. 2021
 *      Author: meven
 */

#include "appli/config.h"
#include "matrix_leds_32x32.h"
#include "appli/common/gpio.h"
#include "appli/common/systick.h"



#if OBJECT_ID == OBJECT_MATRIX_LEDS

	//Simplification fonction d'écriture et de configuration
	#define WRITE(port_pin,value) 	GPIO_write(port_pin,value)
	#define CONFIG_OUTPUT(port_pin) GPIO_configure(port_pin, GPIO_PIN_CNF_PULL_Disabled , TRUE)

	//adaptation au choix hardware

	#define A 10
	#define B 9
	#define D 7
	#define C 5

	//partie haute de la matrice

	#define HIGH_B 14
	#define HIGH_G 15
	#define HIGH_R 16

	//partie basse de la matrice

	#define LOW_B 11
	#define LOW_G 12
	#define LOW_R 13

	//CLK, LAT et OE

	#define OE 2
	#define CLK 3
	#define LAT 4


static bool_e initialized = FALSE;

void MATRIX_init(void)
{
	CONFIG_OUTPUT(A);
	CONFIG_OUTPUT(B);
	CONFIG_OUTPUT(C);
	CONFIG_OUTPUT(D);
	CONFIG_OUTPUT(HIGH_R);
	CONFIG_OUTPUT(HIGH_G);
	CONFIG_OUTPUT(HIGH_B);
	CONFIG_OUTPUT(LOW_R);
	CONFIG_OUTPUT(LOW_G);
	CONFIG_OUTPUT(LOW_B);
	CONFIG_OUTPUT(CLK);
	CONFIG_OUTPUT(LAT);
	CONFIG_OUTPUT(OE);

    WRITE(OE, 0);
    WRITE(LAT, 0);
    initialized = TRUE;
}


void MATRIX_display(matrix_t color[32][32])
{
    uint8_t zone;
    uint8_t led;
    //Sécurité si l'initialisation n'a pas été appelée.
    if(!initialized)
    	MATRIX_init();


	for(zone= 0 ; zone < 16 ; zone++)
	{
		WRITE(OE, 0);
		WRITE(A,(zone >> 0)&1);
		WRITE(B,(zone >> 1)&1);
		WRITE(C,(zone >> 2)&1);
		WRITE(D,(zone >> 3)&1);
		SYSTICK_delay_ms(1);
		for(led = 0; led < 32; led++)
		{
			WRITE(HIGH_R, 	(color[zone][led] 		>> 2) & 1);
			WRITE(LOW_R, 		(color[16+zone][led] 	>> 2) & 1);

			WRITE(HIGH_G, 	(color[zone][led] 		>> 1) & 1);
			WRITE(LOW_G, 	(color[16+zone][led] 	>> 1) & 1);

			WRITE(HIGH_B, 	(color[zone][led] 		>> 0) & 1);
			WRITE(LOW_B, 	(color[16+zone][led]	>> 0) & 1);

			WRITE(CLK,1);
			WRITE(CLK,0);
		}
		WRITE(LAT, 1);
		WRITE(LAT, 0);
		WRITE(OE, 1);
	}

}

void MATRIX_french_flag(matrix_t matrix[32][32]){
    if(!initialized)
    	MATRIX_init();
	for(uint8_t i = 0; i < 32; i++){
		for(uint8_t j = 0; j < 32; j++){
			if(j <= 10){
				matrix[i][j] = COLOR_BLUE;
			}
			if(10 < j){
				matrix[i][j] = COLOR_WHITE;
			}
			if(20 < j){
				matrix[i][j] = COLOR_RED;
			}
		}
	}
}

void MATRIX_write_one_led(uint32_t i, uint32_t j, matrix_t matrix[32][32], uint32_t color){
    if(!initialized)
    	MATRIX_init();
    matrix[i - 1][j] = color;
}

#define WRITE_led(i, j, matrix, color)		MATRIX_write_one_led(i, j, matrix, color)

void MATRIX_write_number(matrix_t matrix[32][32], uint32_t i, uint32_t j, uint32_t number, uint32_t color){
	if(!initialized)
		MATRIX_init();
	switch(number){
	case 0:{
		WRITE_led(i, j, matrix, color);
		WRITE_led(i + 1, j, matrix, color);
		WRITE_led(i + 2, j, matrix, color);
		WRITE_led(i + 3, j, matrix, color);
		WRITE_led(i + 4, j, matrix, color);
		WRITE_led(i, j + 1, matrix, color);
		WRITE_led(i + 4, j + 1, matrix, color);
		WRITE_led(i, j + 2, matrix, color);
		WRITE_led(i + 4, j + 2, matrix, color);
		WRITE_led(i, j + 3, matrix, color);
		WRITE_led(i + 1, j +3, matrix, color);
		WRITE_led(i + 2, j + 3, matrix, color);
		WRITE_led(i + 3, j + 3, matrix, color);
		WRITE_led(i + 4, j + 3, matrix, color);
		break;
	}
	case 1:{
		WRITE_led(i + 2, j, matrix, color);
		WRITE_led(i + 1, j + 1, matrix, color);
		WRITE_led(i, j + 2, matrix, color);
		WRITE_led(i, j + 3, matrix, color);
		WRITE_led(i + 1, j + 3, matrix, color);
		WRITE_led(i + 2, j + 3, matrix, color);
		WRITE_led(i + 3, j + 3, matrix, color);
		WRITE_led(i + 4, j + 3, matrix, color);
		break;
	}
	case 2:{
		WRITE_led(i + 1, j, matrix, color);
		WRITE_led(i, j + 1, matrix, color);
		WRITE_led(i, j + 2, matrix, color);
		WRITE_led(i + 1, j + 3, matrix, color);
		WRITE_led(i + 2, j + 2, matrix, color);
		WRITE_led(i + 3, j + 1, matrix, color);
		WRITE_led(i + 4, j, matrix, color);
		WRITE_led(i + 4, j + 1, matrix, color);
		WRITE_led(i + 4, j + 2, matrix, color);
		WRITE_led(i + 4, j + 3, matrix, color);
		break;
	}
	case 3:{
		WRITE_led(i, j, matrix, color);
		WRITE_led(i, j + 1, matrix, color);
		WRITE_led(i, j + 2, matrix, color);
		WRITE_led(i + 1, j + 3, matrix, color);
		WRITE_led(i + 2, j + 1, matrix, color);
		WRITE_led(i + 2, j + 2, matrix, color);
		WRITE_led(i + 3, j + 3, matrix, color);
		WRITE_led(i + 4, j, matrix, color);
		WRITE_led(i + 4, j + 1, matrix, color);
		WRITE_led(i + 4, j + 2, matrix, color);
		break;
	}
	case 4:{
		WRITE_led(i + 2, j, matrix, color);
		WRITE_led(i + 3, j, matrix, color);
		WRITE_led(i + 1, j + 1, matrix, color);
		WRITE_led(i + 3, j + 1, matrix, color);
		WRITE_led(i, j + 2, matrix, color);
		WRITE_led(i + 3, j + 2, matrix, color);
		WRITE_led(i, j + 3, matrix, color);
		WRITE_led(i + 1, j + 3, matrix, color);
		WRITE_led(i + 2, j + 3, matrix, color);
		WRITE_led(i + 3, j + 3, matrix, color);
		WRITE_led(i + 4, j + 3, matrix, color);
		break;
	}
	case 5:{
		WRITE_led(i, j, matrix, color);
		WRITE_led(i + 1, j, matrix, color);
		WRITE_led(i + 2, j, matrix, color);
		WRITE_led(i + 4, j, matrix, color);
		WRITE_led(i, j + 1, matrix, color);
		WRITE_led(i + 2, j + 1, matrix, color);
		WRITE_led(i + 4, j + 1, matrix, color);
		WRITE_led(i, j + 2, matrix, color);
		WRITE_led(i + 2, j + 2, matrix, color);
		WRITE_led(i + 4, j + 2, matrix, color);
		WRITE_led(i + 3, j + 3, matrix, color);
		WRITE_led(i, j + 3, matrix, color);
		break;
	}
	case 6:{
		WRITE_led(i + 1, j, matrix, color);
		WRITE_led(i + 2, j, matrix, color);
		WRITE_led(i + 3, j, matrix, color);
		WRITE_led(i, j + 1, matrix, color);
		WRITE_led(i + 2, j + 1, matrix, color);
		WRITE_led(i + 4, j + 1, matrix, color);
		WRITE_led(i, j + 2, matrix, color);
		WRITE_led(i + 2, j + 2, matrix, color);
		WRITE_led(i + 4, j + 2, matrix, color);
		WRITE_led(i + 3, j + 3, matrix, color);
		break;
	}
	case 7:{
		WRITE_led(i, j, matrix, color);
		WRITE_led(i, j + 1, matrix, color);
		WRITE_led(i + 3, j + 1, matrix, color);
		WRITE_led(i + 4, j + 1, matrix, color);
		WRITE_led(i, j + 2, matrix, color);
		WRITE_led(i + 2, j + 2, matrix, color);
		WRITE_led(i, j + 3, matrix, color);
		WRITE_led(i + 1, j + 3, matrix, color);
		break;
	}
	case 8:{
		WRITE_led(i + 1, j, matrix, color);
		WRITE_led(i + 3, j, matrix, color);
		WRITE_led(i, j + 1, matrix, color);
		WRITE_led(i + 2, j + 1, matrix, color);
		WRITE_led(i + 4, j + 1, matrix, color);
		WRITE_led(i, j + 2, matrix, color);
		WRITE_led(i + 2, j + 2, matrix, color);
		WRITE_led(i + 4, j + 2, matrix, color);
		WRITE_led(i + 1, j + 3, matrix, color);
		WRITE_led(i + 3, j + 3, matrix, color);
		break;
	}
	case 9:{
		WRITE_led(i + 1, j, matrix, color);
		WRITE_led(i, j + 1, matrix, color);
		WRITE_led(i + 2, j + 1, matrix, color);
		WRITE_led(i + 4, j + 1, matrix, color);
		WRITE_led(i, j + 2, matrix, color);
		WRITE_led(i + 2, j + 2, matrix, color);
		WRITE_led(i + 4, j + 2, matrix, color);
		WRITE_led(i + 1, j + 3, matrix, color);
		WRITE_led(i + 3, j + 3, matrix, color);
		break;
	}
	default:
		break;
	}
}

#define WRITE_number(matrix, i, j, number, color) MATRIX_write_number(matrix, i, j, number, color)

#endif

