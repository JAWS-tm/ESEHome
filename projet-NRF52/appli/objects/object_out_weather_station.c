/*
 * object_out_weather_station.c
 *
 *  Created on: 2 févr. 2021
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
	typedef enum{
		INIT,
		RAIN_WAITING,
		RAIN_MEASUREMENT,
		OTHERS_MEASUREMENT,
		SEND_DATAS
	}state_e;

	static state_e state = INIT;
	switch(state){
	case INIT:

		state = RAIN_WAITING;
		break;
	case RAIN_WAITING:{
		state = RAIN_MEASUREMENT;
		state = OTHERS_MEASUREMENT;
		break;}
	case RAIN_MEASUREMENT:{
		state = OTHERS_MEASUREMENT;
		break;}
	case OTHERS_MEASUREMENT:{
		NMOS_On();
		//BMP180_StartTemperature();
		//BMP180_ReadTemperature();
		NMOS_Off();
		//RJ12_WindInit();
		state = SEND_DATAS;
		break;}
	case SEND_DATAS:{
		state = INIT;
		break;}
	default:
		break;
	}
}


/*void RJ12_WindInit(void){

}*/
bool_e RJ12_ReadWindTest(void){
	uint32_t time = SYSTICK_get_time_us();
	uint32_t time2 = 0;
	GPIO_write(PIN_ANEMO_PLUS, TRUE);
	bool_e read = FALSE;
	volatile uint8_t tour_in_10_seconds = 0;
	while(time2 < time + 10000000 ){
		read = GPIO_read(PIN_ANEMO_MOINS);
		time2 = SYSTICK_get_time_us();
		if(read == TRUE){
			tour_in_10_seconds++;
		}
	}

	return read;
}








#endif
