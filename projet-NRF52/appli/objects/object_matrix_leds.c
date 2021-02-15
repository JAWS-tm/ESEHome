/*
 * object_matrix_leds.c
 *
 *  Created on: 2 févr. 2021
 *      Author: meven
 */
#include "../config.h"
#include "object_matrix_leds.h"
#include "bsp/matrix_leds_32x32.h"


#if OBJECT_ID == OBJECT_MATRIX_LEDS

void MATRIX_afficheur(){
	typedef enum{
		INIT,
		TEST_MATRIX,
		SLEEP
	}state_e;

	static state_e state = INIT;
	static matrix_t matrix[32][32];
	switch(state){
	case INIT:
		MATRIX_show_temperature(matrix, 7, 3, FALSE, 1, 9, COLOR_RED);
		state = TEST_MATRIX;
		break;
	case TEST_MATRIX:{
		MATRIX_display(matrix);
		//state = SLEEP;
		break;}
	case SLEEP:{
		bool_e wait = FALSE;
		if(wait == TRUE){
			state = INIT;
		}
		break;}
	default:
		break;
	}
}

#endif



