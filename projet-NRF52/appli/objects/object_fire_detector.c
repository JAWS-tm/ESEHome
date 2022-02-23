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

static uint16_t signal;

static volatile uint32_t t = 0;
static volatile uint32_t wait = 0;
static volatile uint32_t  Threshold = 400;




void process_ms(void)
{
	if(t)
		t--;
}

void FIRE_DETECTOR_MAIN(void){
	BUTTONS_init();
	LED_add(LED_ID_USER0, PIN_LED_USER);
	GPIO_configure(PIN_FIRE_DETECTOR, GPIO_PIN_CNF_PULL_Pullup, true);
	BUTTONS_add(BUTTON_USER0, PIN_BUTTON_USER, TRUE, NULL, NULL, NULL, NULL);


	static volatile state_e state = INIT;
	switch(state)
	{
		case INIT:
			//J'initialise le capteur
			ADC_init();
			GPIO_write(PIN_FIRE_DETECTOR, true);
			LED_set(LED_ID_USER0, LED_MODE_ON);
			Systick_add_callback_function(&process_ms);
			debug_printf("Je suis pret");
			state = GET_STATE;
		break;

		case GET_STATE:
			//On regarde l'état du capteur
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
				debug_printf("J'ai arreter l'alarme");
			}
			StopAlert();
			state = WAIT;
		break;

		case WAIT:
			// Carteur en état de veil
			if(!t){
				t=400;
				debug_printf("J'attend");
			}
			SYSTICK_delay_ms(5000);
			//Wait();
			state = INIT;
		break;

	}

}


void Wait(){

}

void FireAlert(void){
	//J'envoi un message a la SB
	RF_DIALOG_send_msg_id_to_basestation(PARAMETER_WRITE,01,1);
}


void StopAlert(void){
	//J'en un message "stop" a la SB
	RF_DIALOG_send_msg_id_to_basestation(PARAMETER_WRITE,05,0);
}

int WAIT_stop(){

	int stop = 0;

	if(BUTTONS_read(BUTTON_USER0)){
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



