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

#endif

