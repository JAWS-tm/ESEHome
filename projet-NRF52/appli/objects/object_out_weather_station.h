/*
 * object_out_weather_station.h
 *
 *  Created on: 5 f�vr. 2021
 *      Author: terri
 */

#ifndef APPLI_OBJECTS_OBJECT_OUT_WEATHER_STATION_H_
#define APPLI_OBJECTS_OBJECT_OUT_WEATHER_STATION_H_

#if OBJECT_ID == OBJECT_OUT_WEATHER_STATION

void OUT_WEATHER_STATION_MAIN(void);
void RJ12_WindInit(void);
void RJ12_RainInit(void);
void state_machine_wind();
void state_machine_rain();

#endif /* APPLI_OBJECTS_OBJECT_OUT_WEATHER_STATION_H_ */

#endif
