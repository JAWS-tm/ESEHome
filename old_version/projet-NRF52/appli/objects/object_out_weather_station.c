/*
 * object_out_weather_station.c
 *
 *  Created on: 2 f�vr. 2021
 *      Author: terri
 */

#include "../config.h"
#include "object_out_weather_station.h"

#if OBJECT_ID == OBJECT_OUT_WEATHER_STATION


#include "../../bsp/dht11.h"
#include "../../bsp/bmp180.h"
#include "../../bsp/nmos_gnd.h"
#include "../common/gpio.h"

void OUT_WEATHER_STATION_MAIN(void){
	uint32_t time = SYSTICK_get_time_us();
	uint32_t time2 = 0;

	typedef enum{
		INIT,
		MEASUREMENT,
		WAIT,
		SEND_DATAS
	}state_e;

	static state_e state = INIT;
	switch(state){
	case INIT:
		RJ12_WindInit();
		RJ12_RainInit();
		DHT11_init(DHT11_PIN);
		state = MEASUREMENT;
		break;
	case MEASUREMENT:
		NMOS_On();
		debug_printf("Temperature : %d\n", BMP180_temperature());
		debug_printf("Pression : %d\n", BMP180_pressure());
		debug_printf("Humidite : %d\n", DHT11_humidity());
		debug_printf("WindReturn : %d \n",RJ12_ReadWindTest());
		debug_printf("Nombre de milimètre de pluie : %d (faire x0.1)\n",RJ12_ReadRainTest()*3);
		NMOS_Off();
		state = WAIT;
		break;
	case WAIT:
		time = SYSTICK_get_time_us();
		time2 = 0;
		while(time2 < time + 5000000 ){
			time2 = SYSTICK_get_time_us();
		}
		state = MEASUREMENT;
		break;
	default:
		break;
	}
}


void RJ12_WindInit(void){
	GPIO_configure(PIN_ANEMO_MOINS, NRF_GPIO_PIN_PULLUP, FALSE);
	GPIO_configure(PIN_ANEMO_PLUS, NRF_GPIO_PIN_NOPULL, TRUE);
}


float RJ12_ReadWindTest(void){
	RJ12_WindInit();
	uint32_t time = SYSTICK_get_time_us();
	uint32_t time2 = 0;
	GPIO_write(PIN_ANEMO_PLUS, TRUE);
	bool_e read = 0;
	volatile uint8_t tour_in_10_seconds = 0;
	while(time2 < time + 10000000){
		read = GPIO_read(PIN_ANEMO_MOINS);
		time2 = SYSTICK_get_time_us();
		if(read == 1){
			tour_in_10_seconds++;
		}
	}
	volatile float vitesse_en_ms = 2*3.14*0.07*(tour_in_10_seconds)/10; // Vitesse en m/s
	volatile float vitesse_en_kmh = 3.6*vitesse_en_ms; //Vitesse en km/h

	return (int)vitesse_en_kmh;
}


void RJ12_RainInit(void){
	GPIO_configure(PIN_PLUVIO_MOINS, NRF_GPIO_PIN_PULLUP, FALSE);
	GPIO_configure(PIN_PLUVIO_PLUS, NRF_GPIO_PIN_NOPULL, TRUE);
}


uint8_t RJ12_ReadRainTest(void){
	RJ12_RainInit();
	uint32_t time = SYSTICK_get_time_us();
	uint32_t time2 = 0;
	GPIO_write(PIN_PLUVIO_PLUS, TRUE);
	volatile bool_e read = 0;
	volatile uint8_t dose_pluie = 0;
	while(time2 < time + 10000000 ){
		read = GPIO_read(PIN_PLUVIO_MOINS);
		time2 = SYSTICK_get_time_us();
		uint32_t time3 = 0;
		if(read != 1){
			while(time3 < time2 + 100000 ){
				time3 = SYSTICK_get_time_us();
			}
			dose_pluie++;
		}
	}
	return dose_pluie;
}





#endif
