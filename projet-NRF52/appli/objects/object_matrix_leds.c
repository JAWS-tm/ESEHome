/*
 * object_matrix_leds.c
 *
 *  Created on: 2 févr. 2021
 *      Author: meven
 */
#include "../config.h"
#include "object_matrix_leds.h"
#include "bsp/matrix_leds_32x32.h"
#include "appli/common/parameters.h"
#include "appli/common/leds.h"
#include "appli/common/buttons.h"
#include "nrf_gpio.h"
#include "bsp/WS2812.h"
#include "appli/common/systick.h"
#include <stdio.h>

#include <time.h>




#if OBJECT_ID == OBJECT_MATRIX_LEDS

typedef enum{
		INIT_DATA,
		DISPLAY_MATRIX
	}state_e;

static volatile uint32_t value = 0;
static volatile param_id_e param_id = PARAM_TEMPERATURE;

static uint16_t volatile ms = 0;
static bool flag_bp_hour = FALSE;
static bool flag_bp_chrono = FALSE;
static bool flag_bp_long_press_chrono = FALSE;

void OBJECT_MATRIX_LEDS_value_updated_callback(uint32_t new_value){
	value = new_value;
}


void button_network_short_press(void) {
	LED_toggle(LED_ID_USER0);
	debug_printf("\nbutton_network_short_press");
	//LED_set_flash_limited_nb(LED_ID_USER0, 5,100);
	//LED_set(LED_ID_USER0, LED_MODE_FLASH);
}
void start_timer_short_press(void){
	 flag_bp_chrono = TRUE;
	debug_printf("\nstart_timer_short_press");
}

void bp_long_press(void){
	flag_bp_long_press_chrono = TRUE;
	debug_printf("\nbp_long_press");
}


// void restart_time_short_press(void){
//	 flag_bp_restart_chrono = TRUE;
// }
void button_network_5press(void) {
	LED_set_flash_limited_nb(LED_ID_USER0, 5,100);
	debug_printf("\nbutton_network_5press");

}

typedef struct
{
	uint8_t lines[5];
}digit_t;

//   	O----------> x
//		|
//		|
//		|
//		|
//		|
//		v  y


const digit_t digits[11] =
{		//0
		(digit_t){	{0b11100000,
					0b10100000,
					0b10100000,
					0b10100000,
					0b11100000}},
		//1
		(digit_t){{	0b00100000,
					0b01100000,
					0b10100000,
					0b00100000,
					0b00100000}},
		//2
		(digit_t){{	0b11100000,
					0b00100000,
					0b11100000,
					0b10000000,
					0b11100000}},
		//3
		(digit_t){{	0b11100000,
					0b00100000,
					0b11100000,
					0b00100000,
					0b11100000}},
		//4
		(digit_t){{	0b10100000,
					0b10100000,
					0b11100000,
					0b00100000,
					0b00100000}},
		//5
		(digit_t){{	0b11100000,
					0b10000000,
					0b11100000,
					0b00100000,
					0b11100000}},
		//6
		(digit_t){{	0b11100000,
					0b10000000,
					0b11100000,
					0b10100000,
					0b11100000}},
		//7
		(digit_t){{	0b11100000,
					0b00100000,
					0b00100000,
					0b01000000,
					0b1000000}},
		//8
		(digit_t){{	0b11100000,
					0b10100000,
					0b11100000,
					0b10100000,
					0b11100000}},
		//9
		(digit_t){{	0b11100000,
					0b10100000,
					0b11100000,
					0b00100000,
					0b11100000}},
		//points clignotants
		(digit_t){{	0b000000,
					0b100000,
					0b000000,
					0b100000,
					0b000000}},
};


void MATRIX_LED_param_updated_callback(int32_t new_value)
{
	debug_printf("\nnew value : %d", new_value);
}

/*
 * Met toutes les leds de la matrice noir = éteint
 */
void MATRIX_clear(uint32_t * matrix, uint16_t size)
{
	for(uint16_t i=0; i<size; i++)
		matrix[i] = COLOR_BLACK;
}
/*
 * Explication fonction MATRIX_putdigit_matrix
 *
 * 		MATRIX_putdigit_matrix(1, matrix_1, 8, 8, 0, 1, COLOR_LIGHTBLUE, COLOR_BLACK);
 * 			1 : numéro 1 en bits, dans la constante "digits"
 * 			matrix_1 : list de 64 cases, car 64 leds. Ne pas y toucher si utilisations 1 matrice
 * 			8, 8 : Nombre de pixels/leds en X et en Y, sur le panneau leds
 * 			0, 1 : Position affichage en X et en Y, sur le panneau leds
 * 			COLOR_LIGHTBLUE : couleur de l'ecriture
 * 			COLOR_BLACK : couleur de fond (noir = led éteinte)
 */
void MATRIX_putdigit_matrix(uint8_t d, uint32_t * matrix, uint16_t size_x, uint16_t size_y, uint8_t x, uint8_t y, uint32_t foreground, uint32_t background)
{
	for(uint16_t i=0; i<3; i++)
		for(uint16_t j=0; j<5; j++)
		{
			if(i+x<size_x && j+y<size_y)
				matrix[i+x  +  size_x*(j+y)] = ((digits[d].lines[j]>>(7-i))&1)?foreground:background;
		}
}


/*
 * Affiche sur la matrice ":0", en attendant qu'il se passe quelque chose
 */
void Set_Timer(uint32_t * matrix_1, uint32_t matrix_8X8){

	MATRIX_putdigit_matrix(0, matrix_1, 8, 8, 4, 1, COLOR_LIGHTBLUE, COLOR_BLACK);
	MATRIX_putdigit_matrix(10, matrix_1, 8, 8, 0, 1, COLOR_LIGHTBLUE, COLOR_BLACK);
	WS2812_display_matrix(matrix_1, matrix_8X8);
	WS2812_refresh();
}

/* fonction pour 2 matrices
 *void Set_Timer(uint32_t * matrix_1, uint32_t * m2, uint32_t matrix_8X8){
	MATRIX_putdigit_matrix(0, matrix_1, 16, 8, 13, 1, COLOR_LIGHTBLUE, COLOR_BLACK);
	MATRIX_putdigit_matrix(0, matrix_1, 16, 8, 9, 1, COLOR_LIGHTBLUE, COLOR_BLACK);
	MATRIX_putdigit_matrix(0, matrix_1, 16, 8, 4, 1, COLOR_LIGHTBLUE, COLOR_BLACK);
	MATRIX_putdigit_matrix(0, matrix_1, 16, 8, 0, 1, COLOR_LIGHTBLUE, COLOR_BLACK);
	MATRIX_movement(matrix_1, m2);
	WS2812_display_matrix(m2, matrix_8X8);
	WS2812_refresh();
}
*/

void Get_hours(uint32_t * matrix_1, uint32_t * m2, uint32_t matrix_8X8)

{
	MATRIX_clear(matrix_1, matrix_8X8);
		int h = 0;
		int m = 0;
		int s = 0;
		MATRIX_putdigit_matrix(0, matrix_1, 8, 8, 6, 1, COLOR_LIGHTBLUE, COLOR_BLACK);
		MATRIX_putdigit_matrix(0, matrix_1, 8, 8, 4, 1, COLOR_LIGHTBLUE, COLOR_BLACK);
		MATRIX_putdigit_matrix(0, matrix_1, 8, 8, 2, 1, COLOR_LIGHTBLUE, COLOR_BLACK);
		MATRIX_putdigit_matrix(0, matrix_1, 8, 8, 0, 1, COLOR_LIGHTBLUE, COLOR_BLACK);
		MATRIX_movement(matrix_1, m2);
		WS2812_display_matrix(m2, matrix_8X8);
		WS2812_refresh();
		for (size_t i=0; i < 86400; i++) // nombre de seconde en une journée
		{
			 SYSTICK_delay_ms(10);
			 s++;

			 if (s == 60)
			 {
				 m++;
				 if (m >= 10){
					 int m_unite = (m%10); // unité minute
					 int m_dizaine = (m/10)%10; // dizaine minute
					 s = 0;
					 MATRIX_putdigit_matrix(m_unite, matrix_1, 8, 8, 8, 1, COLOR_LIGHTBLUE, COLOR_BLACK);
					 MATRIX_putdigit_matrix(m_dizaine, matrix_1, 8, 8, 5, 1, COLOR_LIGHTBLUE, COLOR_BLACK);
					 MATRIX_movement(matrix_1, m2);
					 WS2812_display_matrix(m2, matrix_8X8);
					 WS2812_refresh();

				 }else {
					 s = 0;
					 MATRIX_putdigit_matrix(m, matrix_1, 8, 8, 7, 1, COLOR_LIGHTBLUE, COLOR_BLACK);
					 MATRIX_movement(matrix_1, m2);
					 WS2812_display_matrix(m2, matrix_8X8);
					 WS2812_refresh();

				 }
				 if (m == 60)
				 {
					 h++;
					 if (h >= 10){
						 int h_unite = (s%10); // unité heure
						 int h_dizaine = (s/10)%10; // dizaine heures
						 MATRIX_putdigit_matrix(h_unite, matrix_1, 8, 8, 4, 1, COLOR_LIGHTBLUE, COLOR_BLACK);
						 MATRIX_putdigit_matrix(h_dizaine, matrix_1, 8, 8, 0, 1, COLOR_LIGHTBLUE, COLOR_BLACK);
						 MATRIX_movement(matrix_1, m2);
						 WS2812_display_matrix(m2, matrix_8X8);
						 WS2812_refresh();
					 } else {
						 m = 0;
						 MATRIX_putdigit_matrix(h, matrix_1, 8, 8, 4, 1, COLOR_LIGHTBLUE, COLOR_BLACK);
						 MATRIX_putdigit_matrix(m, matrix_1, 8, 8, 6, 1, COLOR_LIGHTBLUE, COLOR_BLACK);
						 MATRIX_putdigit_matrix(m, matrix_1, 8, 8, 8, 1, COLOR_LIGHTBLUE, COLOR_BLACK);
						 MATRIX_movement(matrix_1, m2);
						 WS2812_display_matrix(m2, matrix_8X8);
						 WS2812_refresh();
					 }
			 	 }

			 }
			 //debug_printf("%d:%d:%d \n", h, m, s);
		}
}



/*
 * Fonction qui lance le chrono
 */
void Get_Timer(uint32_t * matrix_1, uint32_t * m2, uint32_t matrix_8X8){
	MATRIX_clear(matrix_1, matrix_8X8);

	int s = 0;
	debug_printf("\nGet timer");


	for (size_t i=0; i < 100; i++) // Timer de 10 seconde (0 a 9 car 1 matrice = affichage 2 chiffres)
	{
		// Attendre 1s
		SYSTICK_delay_ms(1000);

		if(s == 100){
			MATRIX_putdigit_matrix(1, matrix_1, 8, 8, 0, 1, COLOR_LIGHTBLUE, COLOR_BLACK);
			MATRIX_putdigit_matrix(0, matrix_1, 8, 8, 1, 1, COLOR_LIGHTBLUE, COLOR_BLACK);
			MATRIX_putdigit_matrix(0, matrix_1, 8, 8, 4, 1, COLOR_LIGHTBLUE, COLOR_BLACK);
		}
		else if (s >= 10){
			int s_unite = (s%10); // unité seconde
			int s_dizaine = (s/10)%10; // dizaine seconde
			MATRIX_putdigit_matrix(s_unite, matrix_1, 8, 8, 4, 1, COLOR_LIGHTBLUE, COLOR_BLACK);
			MATRIX_putdigit_matrix(s_dizaine, matrix_1, 8, 8, 0, 1, COLOR_LIGHTBLUE, COLOR_BLACK);
			WS2812_display_matrix(matrix_1, matrix_8X8);
			WS2812_refresh();
		} else{
			MATRIX_putdigit_matrix(0, matrix_1, 8, 8, 0, 1, COLOR_LIGHTBLUE, COLOR_BLACK);
			MATRIX_putdigit_matrix(s, matrix_1, 8, 8, 4, 1, COLOR_LIGHTBLUE, COLOR_BLACK);
			WS2812_display_matrix(matrix_1, matrix_8X8);
			WS2812_refresh();
		}

		 s++;
	}



/*		 if (s >= 10){
			 int s_unite = (s%10); // unité seconde
			 //int s_dizaine = (s/10)%10; // dizaine seconde
			 MATRIX_putdigit_matrix(s_unite, matrix_1, 8, 8, 4, 1, COLOR_LIGHTBLUE, COLOR_BLACK);
			 //MATRIX_putdigit_matrix(s_dizaine, matrix_1, 8, 8, 4, 1, COLOR_LIGHTBLUE, COLOR_BLACK);
			 //MATRIX_movement(matrix_1, m2);
			 //WS2812_display_matrix(m2, matrix_8X8);
			 WS2812_display_matrix(64, matrix_8X8);
			 WS2812_refresh();
		 } else {
		 MATRIX_putdigit_matrix(s, matrix_1, 8, 8, 4, 1, COLOR_LIGHTBLUE, COLOR_BLACK);
		 //MATRIX_movement(matrix_1, m2);
		 WS2812_display_matrix(64, matrix_8X8);
		 WS2812_refresh();
		 }
		 if (s == 60)
		 {
			 m++;
			 if (m >= 10){
				 int m_unite = (m%10); // unité minute
				 int m_dizaine = (m/10)%10; // dizaine minute
				 s = 0;
				 MATRIX_putdigit_matrix(s, matrix_1, 8, 8, 8, 1, COLOR_LIGHTBLUE, COLOR_BLACK);
				 MATRIX_putdigit_matrix(s, matrix_1, 8, 8, 7, 1, COLOR_LIGHTBLUE, COLOR_BLACK);
				 MATRIX_putdigit_matrix(m_unite, matrix_1, 8, 5, 4, 1, COLOR_LIGHTBLUE, COLOR_BLACK);
				 MATRIX_putdigit_matrix(m_dizaine, matrix_1, 8, 5, 0, 1, COLOR_LIGHTBLUE, COLOR_BLACK);
				 MATRIX_movement(matrix_1, m2);
				 WS2812_display_matrix(m2, matrix_8X8);
				 WS2812_refresh();

			 }else {
				 s = 0;
				 MATRIX_putdigit_matrix(s, matrix_1, 8, 8, 8, 1, COLOR_LIGHTBLUE, COLOR_BLACK);
				 MATRIX_putdigit_matrix(s, matrix_1, 8, 8, 5, 1, COLOR_LIGHTBLUE, COLOR_BLACK);
				 MATRIX_putdigit_matrix(m, matrix_1, 8, 8, 3, 1, COLOR_LIGHTBLUE, COLOR_BLACK);
				 MATRIX_movement(matrix_1, m2);
				 WS2812_display_matrix(m2, matrix_8X8);
				 WS2812_refresh();

			 }

		 }	*/
}

void MATRIX_movement(uint32_t * m, uint32_t * m2)	// Utile quand on utilise 1 matrice ???
{
	uint32_t i = 0;
	for(i=0; i<8; i++){
		m2[i-0-8*0] = m[i];			//matrice gauche -  ligne 0

	}
	for(i=8; i<16; i++){
		m2[i-8-8*0+64] = m[i];		//matrice droite - ligne 0
	}

	for(i=16; i<24; i++){
		m2[i-0-8*1] = m[i];			//matrice gauche -  ligne 1
	}
	for(i=24; i<32; i++){
		m2[i-8-8*1+64] = m[i];		//matrice droite -  ligne 1
	}

	for(i=32; i<40; i++){
		m2[i-0-8*2] = m[i];			//matrice gauche -  ligne 2
	}
	for(i=40; i<48; i++){
		m2[i-8-8*2+64] = m[i];		//matrice droite - ligne 2
	}


	for(i=48; i<56; i++){
		m2[i-0-8*3] = m[i];			//matrice gauche -  ligne 3
	}
	for(i=56; i<64; i++){
		m2[i-8-8*3+64] = m[i];		//matrice droite - ligne 3
	}

	for(i=64; i<72; i++){
		m2[i-0-8*4] = m[i];			//matrice gauche -  ligne 4
	}
	for(i=72; i<80; i++){
		m2[i-8-8*4+64] = m[i];		//matrice droite - ligne 4
	}

	for(i=80; i<88; i++){
		m2[i-0-8*5] = m[i];			//matrice gauche -  ligne 5
	}
	for(i=88; i<96; i++){
		m2[i-8-8*5+64] = m[i];		//matrice droite - ligne 5
	}

	for(i=96; i<104; i++){
		m2[i-0-8*6] = m[i];			//matrice gauche -  ligne 6
	}
	for(i=104; i<112; i++){
		m2[i-8-8*6+64] = m[i];		//matrice droite - ligne 6
	}

	for(i=112; i<120; i++){
		m2[i-0-8*7] = m[i];			//matrice gauche -  ligne 7
	}
	for(i=120; i<128; i++){
		m2[i-8-8*7+64] = m[i];		//matrice droite - ligne 7
	}

}

void MATRIX_afficheur(uint32_t colorDonnees, uint32_t colorType){


	typedef enum{
		INIT_DATA,
		IDLE,
		CHRONO,
		HOURS,
		COMMUNICATION,
		TEST

	}state_e;

	static state_e state = INIT_DATA;
	static state_e previous_state = INIT_DATA;
	bool_e entrance = (state != previous_state);
	previous_state = state;
	static uint32_t matrix_8X8 = 64;
	static uint32_t matrix_16X8 = 128;
	static uint32_t matrix_1[64];
	static uint32_t m2[128];

	switch(state){

		case INIT_DATA:
			debug_printf("\nINIT DATA");

			PARAMETERS_enable(PARAM_MODE, 0, FALSE, NULL, NULL); // 0 quand chrono pas lancé sinon 1
			PARAMETERS_init();
			//BUTTONS_add(BUTTON_CHRONO, 18, TRUE, &start_timer_short_press, NULL, NULL, &bp_long_press);
			WS2812_init(2,matrix_8X8);
			state = IDLE;
			debug_printf("\nINIT DATA OK");
//			state = TEST;

			break;

		case CHRONO:
			debug_printf("\nCHRONO");


			if(entrance){
				Get_Timer(matrix_1,m2,matrix_8X8);
				PARAMETERS_update(PARAM_MODE, 1); // chrono lancé
				state = COMMUNICATION;		// Une fois la fonction terminée, un message est envoyé à lz station de base
				if(flag_bp_chrono){
					state = CHRONO;
				}
			}

		break;

		case IDLE:
			//Set_Timer(matrix_1, m2, matrix_8X8);		// Fonction pour 2 matrices
			Set_Timer(matrix_1, matrix_8X8);   			// Fonction pour 1 matrice

			//if(flag_bp_chrono){
			if(true){	// True, pour lancer le chrono direct
				flag_bp_chrono = FALSE;
				state = CHRONO;
			}else if (flag_bp_long_press_chrono){
				state = HOURS;
			}
		break;

		case HOURS:
			debug_printf("\nHOUR");
			flag_bp_long_press_chrono = FALSE;
			Get_hours(matrix_1,m2,matrix_8X8);
			PARAMETERS_update(PARAM_MODE, 0); // heure
			state = COMMUNICATION;
		break;

		case COMMUNICATION:
			PARAMETERS_send_param32_to_basestation(PARAM_MODE);
			state = IDLE;
		break;

		case TEST:
			MATRIX_putdigit_matrix(0, matrix_1, 8, 8, 1, 1, COLOR_YELLOW, COLOR_BLACK);
			MATRIX_putdigit_matrix(0, matrix_1, 8, 8, 2, 2, COLOR_GREEN, COLOR_BLACK);
			MATRIX_putdigit_matrix(0, matrix_1, 8, 8, 3, 3, COLOR_GREEN, COLOR_BLACK);
		break;

		default:
			break;
		}

}

#endif



