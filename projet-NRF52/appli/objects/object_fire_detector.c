/*
 * object_fire_detector.c
 *
 *  Created on: 26 janv. 2022
 *      Author: Raimbault PL
 */

#include "../config.h"
#include "../main.h"
#include "appli/common/buttons.h"
#include "appli/common/leds.h"
#include "object_fire_detector.h"
#include "appli/common/gpio.h"
#include "appli/common/adc.h"
#include "appli/common/rf_dialog.h"
#include "appli/common/parameters.h"
#include "unistd.h"

#if OBJECT_ID == OBJECT_FIRE_DETECTOR


typedef enum{
	INIT,
	GET_STATE,
	ALERT,
	STOP,
	WAIT,
	WAIT_STOP
}state_e;

static int16_t signal;

static volatile uint32_t t = 0;
static volatile uint32_t wait = 0;
static volatile uint32_t  Threshold = 400;
static volatile uint32_t  fire = 0;
static volatile uint32_t  envoi = 0;

static volatile uint32_t current_blind = 0;
static volatile uint32_t blind_duration = 50000;
static volatile bool_e flag_acknowledge = FALSE;


void process_ms(void)
{
	if(t)
		t--;
	if(current_blind)
		current_blind--;
}

void new_acknowledge_sensor_state_from_rf(int32_t n)
{
	if(n == 0)
		flag_acknowledge = TRUE;
}

void new_duration_set_from_rf(int32_t new_duration)
{
	blind_duration = (uint32_t)new_duration;
}

void new_treshold_sensor_from_rf(int32_t new_treshold)
{
	Threshold = (uint32_t)new_treshold;
}

void FIRE_DETECTOR_MAIN(void){


	static volatile state_e state = INIT;
	switch(state)
	{
		case INIT:
			//J'initialise le capteur
			BUTTONS_init();
			LED_add(LED_ID_USER0, PIN_LED_USER);
			BUTTONS_add(BUTTON_USER0, PIN_BUTTON_USER, TRUE, NULL, NULL, NULL, NULL);
			PARAMETERS_init();
			PARAMETERS_enable(PARAM_MY_BASE_STATION_ID, 9, TRUE, NULL, NULL);
			PARAMETERS_enable(PARAM_SENSOR_VALUE, 0, FALSE, &new_acknowledge_sensor_state_from_rf, NULL );
			PARAMETERS_enable(PARAM_ALARM_TRESHOLD, Threshold, TRUE, &new_treshold_sensor_from_rf, NULL );
			PARAMETERS_enable(PARAM_DURATION, blind_duration, TRUE, &new_duration_set_from_rf, NULL );
			ADC_init();
			GPIO_write(PIN_FIRE_DETECTOR, true);
			LED_set(LED_ID_USER0, LED_MODE_ON);
			PARAMETERS_send_param32_to_basestation(PARAM_ALARM_TRESHOLD);
			Systick_add_callback_function(&process_ms);
			debug_printf("Je suis pret");
			state = GET_STATE;
		break;

		case GET_STATE:
			//On regarde l'état du capteur
			GPIO_configure(PIN_FIRE_DETECTOR, GPIO_PIN_CNF_PULL_Pullup, true);
			ADC_read(AN_SIGNAL,&signal);

			if(signal >= Threshold){
				state = ALERT;
			}
		break;

		case ALERT:
			//On alerte
			if(!t){
				t=400;
				debug_printf("J'allume l'alarme");
			}
			FireAlert();
			current_blind = blind_duration;
			LED_set(LED_ID_USER0, LED_MODE_OFF);
			state = WAIT_STOP;
		break;

		case WAIT_STOP:
			//On attend la fin de l'alerte
			if(WAIT_stop() == 1){
				state = STOP;
			}
		break;

		case STOP:
			//on Stop ou on envoi un stop pour stoper l'alarme
			if(!t){
				t=400;
				debug_printf("J'ai arreté l'alarme");
			}
			envoi = 0;
			StopAlert();
			state = WAIT;
		break;

		case WAIT:
			// Carteur en état de veil
			GPIO_configure(PIN_FIRE_DETECTOR, GPIO_PIN_CNF_PULL_Pullup, false);
			if(!t){
				t=400;
				debug_printf("J'attend");
			}
			if(!current_blind)
				state = GET_STATE;
		break;

	}

	flag_acknowledge = FALSE;

}


void FireAlert(void){
	debug_printf("J'allume l'alarme");
	fire = 1;
	debug_printf("d% fire");
	PARAMETERS_update(PARAM_SENSOR_VALUE, fire);
	PARAMETERS_send_param32_to_basestation(PARAM_SENSOR_VALUE);
}


void StopAlert(void){
	fire = 0;
	PARAMETERS_update(PARAM_SENSOR_VALUE, fire);
	PARAMETERS_send_param32_to_basestation(PARAM_SENSOR_VALUE);
}

int WAIT_stop(){

	int stop = 0;

	if(BUTTONS_read(BUTTON_USER0) || flag_acknowledge){
		LED_set(LED_ID_USER0, LED_MODE_ON);
		stop = 1;
	}else{
		ADC_read(AN_SIGNAL,&signal);
		if(signal < Threshold){
			LED_set(LED_ID_USER0, LED_MODE_ON);
			stop = 1;
		}
	}

	return stop;
}

#endif



