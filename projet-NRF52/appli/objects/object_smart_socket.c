/*
 * object_smart_socket.c
 *
 *  Created on: 20 janv. 2022
 *      Author: Leopold
 */

#if OBJECT_ID == OBJECT_SMART_SOCKET
#include "../config.h"
#include "object_smart_socket.h"
#include "appli/common/gpio.h"
#include "appli/common/buttons.h"
#include "appli/common/leds.h"
#include "appli/common/adc.h"
#include "appli/common/systick.h"

static bool_e prevStatut = FALSE;
static bool_e statut = FALSE;
static uint16_t mesureCourant = 0;
static float courant = 0;
static uint32_t tperiod = 0;

const float courantMIN = 463;
const float courantMAX = 643;

void butPress(void){
	if (statut == TRUE){
		statut = FALSE;
	} else {
		statut = TRUE;
	}
}

void process_ms(void){
	if (tperiod){
		tperiod--;
	}
}

void configPin(void){
	LED_add(LED_ID_USER0, LED_STATUT);
	GPIO_configure(MOSFET_RELAIS, NRF_GPIO_PIN_NOPULL, TRUE);
	BUTTONS_add(BUTTON_USER0, BUTTON_USER, TRUE, &butPress, NULL, NULL, NULL);
	ADC_init();
}

void toggleSockect(void){
	if (statut) {
		LED_set(LED_ID_USER0, LED_MODE_ON);
		GPIO_write(MOSFET_RELAIS, TRUE);
	} else {
		LED_set(LED_ID_USER0, LED_MODE_OFF);
		GPIO_write(MOSFET_RELAIS, FALSE);
	}
}

// Fonction qui convertie une valeur sur un intervalle d'entrée vers un intervalle de sortie
float map(float val, float I_Min, float I_Max, float O_Min, float O_Max){
	return(((val-I_Min)*((O_Max-O_Min)/(I_Max-I_Min)))+O_Min);
}

void calculConsommation(void){
	courant = map(mesureCourant, courantMIN, courantMAX, 0, 6);
}

void backgroudTaskFunction(void){
	if (!tperiod) {
		tperiod = 10000;
		if (statut){
			ADC_read(MESURE_COURANT, &mesureCourant);
			if (mesureCourant >= courantMIN+4 && mesureCourant <= courantMAX-4){
				calculConsommation();
			}else{
				courant = 0;
			}

		} else {
			courant = 0;
		}
		debug_printf("Courant : %d mA\n", (int)(courant*1000));
	}
}

void OBJECT_SMART_SOCKET_Main(void){
	switch(stateSS){
		case INITSS:
			configPin();
			toggleSockect();
			tperiod = 10000;
			Systick_add_callback_function(process_ms);
			stateSS = IDLE;
			break;
		case IDLE:
			backgroudTaskFunction();
			stateSS = DRIVEGPIO;
			break;
		case DRIVEGPIO:
			if (statut != prevStatut){
				toggleSockect();
				prevStatut = statut;
			}
			stateSS = IDLE;
			break;
	}
}

#endif

