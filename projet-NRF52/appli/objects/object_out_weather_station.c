/*
 * object_out_weather_station.c
 *
 *  Created on: 7 février 2023
 *      Author: Isaac MAUXION
 */

#include "../config.h"
#include "object_out_weather_station.h"

#if OBJECT_ID == OBJECT_OUT_WEATHER_STATION


#include "../../bsp/dht11.h"
#include "../../bsp/bmp180.h"
#include "../../bsp/nmos_gnd.h"
#include "../common/gpio.h"

uint32_t absolute_time;
uint32_t t;
uint32_t rain_counter;
uint32_t K = 2*1000*3.14*0.07;
float wind_speed;
char char_wind_speed[10];
uint32_t current_time;
uint32_t previous_time;
uint32_t duration;

static void process_ms(void);

void process_ms(void){
	if(t){
		t --;
		absolute_time ++;
	}
}

void OUT_WEATHER_STATION_MAIN(void){

	typedef enum{
		INIT,
		MEASUREMENT
	}state_e;

	static state_e state = INIT;
	switch(state){
	case INIT:
		RJ12_WindInit();
		RJ12_RainInit();
		Systick_add_callback_function(&process_ms);
		state = MEASUREMENT;
		break;
	case MEASUREMENT:
		state_machine_rain();
		state_machine_wind();

		if(!t){
			t = 10000;
			debug_printf("Quantité de pluie : %d mm \n",rain_counter/10);	//affichage de la quantité de pluie toutes les 10 secondes
			debug_printf("Vitesse du vent :  %s km/h \n", char_wind_speed);	//affichage de la vitesse du vent toutes les 10 secondes
		}
		break;
	default:
		break;
	}
}


void RJ12_WindInit(void){
	GPIO_configure(PIN_ANEMO_PLUS, NRF_GPIO_PIN_NOPULL, FALSE);
}

void RJ12_RainInit(void){
	GPIO_configure(PIN_PLUVIO_PLUS, NRF_GPIO_PIN_NOPULL, FALSE);
}

void state_machine_rain(){

	typedef enum{
		INIT,
		WAIT_EVENT,
		RAIN_EVENT
	}state_e;

	static state_e state = INIT;
	static state_e previous_state = INIT;
	bool_e entrance = (state != previous_state);
	previous_state = state;
	uint8_t rain_pin = GPIO_read(PIN_PLUVIO_PLUS);
	switch(state){
		case INIT:
			state = WAIT_EVENT;
			break;
		case WAIT_EVENT:
			if(rain_pin == 0){
				state = RAIN_EVENT;
			}
			break;
		case RAIN_EVENT:
			if(entrance){
				rain_counter ++;
				if(rain_counter % 10 == 0){
					debug_printf("Niveau de pluie : %dmm\n",rain_counter/10);	//affichage tout les 1mm
				}
			}
			if(rain_pin == 1){
				state = WAIT_EVENT;
			}
			break;
		default:
			break;
	}

}

void state_machine_wind(){

	typedef enum{
		INIT,
		WAIT_EVENT,
		WIND_EVENT
	}state_e;

	static state_e state = INIT;
	static state_e previous_state = INIT;
	bool_e entrance = (state != previous_state);
	previous_state = state;
	uint8_t wind_pin = GPIO_read(PIN_ANEMO_PLUS);
	switch(state){
		case INIT:
			state = WAIT_EVENT;
			break;
		case WAIT_EVENT:
			if(absolute_time > (previous_time + 5000)){
				wind_speed = 0;
			}
			if(wind_pin == 0){
				state = WIND_EVENT;
			}
			break;
		case WIND_EVENT:
			if(entrance){
				current_time = absolute_time;
				duration = current_time - previous_time;
				previous_time = current_time;
				if(duration){
					gcvt(wind_speed, 3, char_wind_speed);
					wind_speed = ((float)K/duration)*3.6;
				}
			}
			if(wind_pin == 1){
				state = WAIT_EVENT;
			}
			break;
		default:
			break;
	}

}


#endif
