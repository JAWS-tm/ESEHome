/*
 * object_station_meteo_int.c
 *
 *  Created on: 02 fevr. 2021
 *      Author: Thibault.R
 */
#include "../config.h"

#if OBJECT_ID == OBJECT_STATION_METEO_INT

#include "object_station_meteo_int.h"
#include "../../bsp/dht11.h"

void STATION_METEO_INT_MAIN(void) {
	DHT11_main();
}

#endif
