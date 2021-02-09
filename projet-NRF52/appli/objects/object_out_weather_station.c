/*
 * object_out_weather_station.c
 *
 *  Created on: 2 févr. 2021
 *      Author: terri
 */

#include "../config.h"


#if OBJECT_ID == OBJECT_OUT_WEATHER_STATION


void Out_weather_measurement(void){
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
		state = SEND_DATAS;
		break;}
	case SEND_DATAS:{
		state = INIT;
		break;}
	default:
		break;
	}
}








#endif
