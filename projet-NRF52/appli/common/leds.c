/*
 * leds.C
 *
 *  Created on: 28 janv. 2021
 *      Author: Nirgal
 */
#include "../config.h"
#include "leds.h"
#include "systick.h"
#include "gpio.h"

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
	leds[id].pin = pin;

	GPIO_init();
	GPIO_configure(pin, GPIO_PIN_CNF_PULL_Pullup, true);//configure la pin de la led concernée en sortie
	leds[id].initialized = true;//enregistre la led comme "initialisée"
}

void LED_set(led_id_e id, led_mode_e mode)
{

	if(mode == LED_MODE_ON){
		leds[id].mode = LED_MODE_ON;
		GPIO_write(leds[id].pin, true);
	}else if (mode == LED_MODE_OFF){
		leds[id].mode = LED_MODE_OFF;
		GPIO_write(leds[id].pin, false);
	}
}

void LED_toggle(led_id_e id)
{
	if(leds[id].mode == LED_MODE_OFF)
		LED_set(id, LED_MODE_ON);
	else
		LED_set(id, LED_MODE_OFF);
}


led_mode_e LED_get(led_id_e id)
{
	return leds[id].mode;
}

void LED_process_ms()
{
	//TODO

}


