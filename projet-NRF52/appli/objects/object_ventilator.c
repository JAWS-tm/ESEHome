/*
 * object_ventilator.c
 *
 *  Created on: 10 fvr. 2022
 *      Author: Pierre Nile
 */
#include "../config.h"


#if OBJECT_ID == OBJECT_VENTILATOR
#include "../common/gpio.h"
#include "nrf_gpio.h"
#include "nrf52.h"
#include "appli/common/leds.h"
#include "appli/common/buttons.h"
#include "appli/common/adc.h"
#include "appli/common/serial_dialog.h"
#include "object_ventilator.h"
#include "appli/common/adc.h"
#include "appli/common/parameters.h"
#include "appli/common/rf_dialog.h"
void BUTTON_action(void);
void BUTTON_action_long_press(void);

static volatile int etat = 0;


void OBJECT_VENTILATOR_etat_updated_callback(int new_etat)
{
	etat = new_etat;
}

static ventilator_e state = VENTILATOR_INIT;
int16_t temperature;
int temp_deg;

void object_ventilator_temperature(void)
{
	ADC_read(TEMP_OUTPUT, &temperature);
	debug_printf("Temperature est %d.\n", temperature);
	
	//VOUT=TCxTA + V0°C
	//19.5mV/°C

	temp_deg = (temperature)*10000 / 195000 ;

	debug_printf("La temperature en degre est %d. \n",temp_deg);
}

static volatile bool_e flag_new_ask_from_rf = FALSE;
static volatile int32_t new_speed_asked_from_rf = 0;

void object_fan_set_speed_from_rf(int32_t speed)
{
	new_speed_asked_from_rf = speed;
	flag_new_ask_from_rf = TRUE;
}

static int8_t current_speed;

void object_ventilator_activation(void)
{
	object_ventilator_temperature();

	if(flag_new_ask_from_rf)	//demande de la station de base de piloter le ventilo  la vitesse XXXX)
	{
		flag_new_ask_from_rf = FALSE;
		if(new_speed_asked_from_rf < 8)
			current_speed =  new_speed_asked_from_rf;
	}

	switch(state) {
		case VENTILATOR_INIT:
			PARAMETERS_init();
			PARAMETERS_enable(PARAM_ACTUATOR_STATE, 0, FALSE, &object_fan_set_speed_from_rf, NULL);

			GPIO_init();
			ADC_init();
			GPIO_configure(MOSFET_PIN_1, NRF_GPIO_PIN_PULLUP, true);
			GPIO_configure(MOSFET_PIN_2, NRF_GPIO_PIN_PULLUP, true);
			GPIO_configure(MOSFET_PIN_3, NRF_GPIO_PIN_PULLUP, true);
			LED_add(LED_ID_NETWORK, PIN_LED_NETWORK);
			BUTTONS_add(BUTTON_NETWORK, PIN_BUTTON_NETWORK, TRUE, &BUTTON_action, NULL, &BUTTON_action_long_press, NULL);
			state = VENTILATOR_ON;	//Changement d'tat
			break;

		case VENTILATOR_ON:

			GPIO_write(MOSFET_PIN_1, current_speed>>0 & 1);
			GPIO_write(MOSFET_PIN_2, current_speed>>1 & 1);
			GPIO_write(MOSFET_PIN_3, current_speed>>2 & 1);


			LED_set(LED_ID_NETWORK, (current_speed)?LED_MODE_ON:LED_MODE_OFF);

			//TODO : disposer de deux modes, pilotables par la station... et activant le suivi en temprature
			/*if(temp_deg >= 20) {
				current_speed = 3;
			}

			if(temp_deg >= 30) {
				current_speed = 5;
			}*/

			if(temp_deg >= 50) {
				current_speed = 7;
			}

			break;

		default:
			state = VENTILATOR_INIT;	//N'est jamais sens se produire.
			break;
	}

}

void BUTTON_action(void)
{
	current_speed = (current_speed+1)%8;
}

void BUTTON_action_long_press(void)
{
	current_speed = (current_speed)?0:7;
}

#endif
