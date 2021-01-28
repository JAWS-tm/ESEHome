/*
 * leds.C
 *
 *  Created on: 28 janv. 2021
 *      Author: Nirgal
 */
#include "../config.h"
#include "leds.h"
#include "systick.h"


typedef struct
{
	bool_e initialized;
	uint8_t pin;
	led_mode_e mode;
}leds_t;

static leds_t leds[LED_ID_NB];

void LEDS_init(bool_e i_have_led_battery)
{
	for(uint8_t i = 0; i<LED_ID_NB; i++)
		leds[i].initialized = FALSE;			//nettoyage du tableau.

	//TODO   //ajoute par défaut la led network + led battery si indiqué

	Systick_add_callback_function(&LED_process_ms);
	//TODO déclare au systick la fonction LED_process_ms() qui sera désormais appelée à chaque ms.
}



void LED_add(led_id_e id, uint8_t pin)
{

	//configure la pin de la led concernée en sortie
	//enregistre la led comme "initialisée"
}

void LED_set(led_id_e id, led_mode_e mode)
{

}

void LED_process_ms()
{
	//TODO

}


