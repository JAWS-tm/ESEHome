/*
 * object_smart_socket.c
 *
 *  Created on: 20 janv. 2022
 *      Author: Leopold
 */
#include "../config.h"

#if OBJECT_ID == OBJECT_SMART_SOCKET
#include "object_smart_socket.h"
#include "appli/common/gpio.h"
#include "appli/common/buttons.h"
#include "appli/common/leds.h"
#include "appli/common/adc.h"
#include "appli/common/systick.h"
#include "appli/common/parameters.h"

static bool_e prevStatut = FALSE;
static bool_e statut = FALSE;
static uint16_t mesureCourant = 0;
static float courant = 0;
static float tabCourant[CYCLE];
static float moyenneCourant = 0;
static uint32_t tperiod = 0;
static uint32_t cycle = 0;


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

void configParam(void){
	PARAMETERS_init();
	PARAMETERS_enable(PARAM_MY_BASE_STATION_ID, 0, false, NULL, NULL);
	PARAMETERS_enable(PARAM_ACTUATOR_STATE, statut, false, NULL, NULL);
	PARAMETERS_enable(PARAM_SENSOR_VALUE, 0, false, NULL, NULL);

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



void calculConsommation(void){
	//Pour I=0 => Vout = Vin * 0.5
	//ADCmax => 1024
	//Vadc(0A) = 1024 * 0.5
	// 264 mv / A
	//(mesureCourant - 512) * 3300 / 1024 * 100 / 264
	courant = ((mesureCourant - 466) * 195) / 16;
}

void backgroudTaskFunction(void){
	ADC_read(MESURE_COURANT, &mesureCourant);
	//if (mesureCourant >= courantMIN+4 && mesureCourant <= courantMAX-4){
		calculConsommation();
		tabCourant[cycle] = courant;
	//}else{
		//courant = 0;
	//}
	if (courant > LIM_COURANT || courant < -LIM_COURANT){
		stateSS = DRIVEGPIO;
		return;
	}
	if (!tperiod) {
		cycle++;
		tperiod = REFRESH;
		if (cycle == CYCLE){
			cycle = 0;
			moyenneCourant = 0;
			for (int i = 0; i<CYCLE; i++){
				moyenneCourant = moyenneCourant - tabCourant[i];
			}
			moyenneCourant = moyenneCourant / CYCLE;
			if (moyenneCourant < 100 || moyenneCourant < -100){
				moyenneCourant = 0;
			}

			debug_printf("Courant : %d mA\n", (int)(moyenneCourant));


			if (statut){

				PARAMETERS_update(PARAM_SENSOR_VALUE, (int)(courant));
				stateSS = SENDBS;
			} else {
				//courant = 0;
				stateSS = DRIVEGPIO;
			}
		}
		//debug_printf("Courant : %d mA\n", (int)(courant*1000));


	} else {
		stateSS = DRIVEGPIO;
	}
}

void OBJECT_SMART_SOCKET_Main(void){
	switch(stateSS){
		case INITSS:
			configPin();
			// Éteinds, par défaut, la prise à l'allumage
			toggleSockect();
			// Timer en arrière plan
			tperiod = REFRESH;
			Systick_add_callback_function(process_ms);
			// Initiamisation des différents paramètres
			configParam();
			stateSS = IDLE;
			break;
		case IDLE:
			backgroudTaskFunction();
			break;
		case DRIVEGPIO:
			if (statut != prevStatut){
				toggleSockect();
				prevStatut = statut;
			}
			stateSS = IDLE;
			break;
		case SENDBS:
			PARAMETERS_update(PARAM_ACTUATOR_STATE, statut);
			PARAMETERS_send_param32_to_basestation(PARAM_SENSOR_VALUE);
			PARAMETERS_send_param32_to_basestation(PARAM_ACTUATOR_STATE);
			stateSS = IDLE;
			break;
	}
}

#endif

