/*
 * object_station_meteo_int.c
 *
 *  Created on: 02 fevr. 2021
 *      Author: Thibault.R
 */
#include "../config.h"

#if OBJECT_ID == OBJECT_STATION_METEO_INT

#include "object_station_meteo_int.h"
#include "../../bsp/nmos_gnd.h"
#include "../../bsp/dht11.h"
#include "../../bsp/bmp180.h"
#include "../appli/common/parameters.h"
#include "object_e_paper.h"

void STATION_METEO_INT_MAIN(void) {
	typedef enum{
		INIT,
		DHT11,
		BMP180,
		OTHERS_MEASUREMENT,
		SEND_DATAS,
		EPAPER
	}state_e;

	static state_e state = INIT;
	switch(state){
	case INIT:
		state = DHT11;
		break;
	case DHT11:{
		NMOS_On();
		DHT11_main();
		NMOS_Off();
		state = BMP180;
		break;}
	case BMP180:{
		NMOS_On();
		BMP180_main();
		NMOS_Off();
		state = OTHERS_MEASUREMENT;
		break;}
	case OTHERS_MEASUREMENT:{
			state = SEND_DATAS;
		break;}
	case SEND_DATAS:{

		state = EPAPER;
		break;}
	case EPAPER:{
		//EPAPER_demo();
		//debug_printf("BMP180 : Pressure (%6ld Pascals)\n", BMP180_Data.Pressure);
		debug_printf("DHT11 epaper : (h=%d,%d | t=%d,%d)\n", humidity_int, humidity_dec, temperature_int, temperature_dec);
		//debug_printf("BMP180 : (p=%d)\n",BMP180_pressure);
		state = INIT;
		break;}
	default:
		break;
	}
}

#endif
