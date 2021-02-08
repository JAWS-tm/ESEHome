/*
 * object_tracker_gps.h
 *
 *  Created on: 1 f�vr. 2021
 *      Author: fabie
 */

#ifndef APPLI_OBJECTS_OBJECT_TRACKER_GPS_H_
#define APPLI_OBJECTS_OBJECT_TRACKER_GPS_H_

typedef struct
{
	uint16_t 	id;
	uint32_t 	time;		//[HHMMSS]
	uint32_t 	seconds;	//[sec since 0:00:00]
	double 		latitude_rad;		//rad
	double 		longitude_rad;		//rad
	double		latitude_deg;		//deg
	double		longitude_deg;		//deg
	int16_t		lat_degrees;	//Partie enti�re des degr�s
	double		lat_minutes;	//Minutes d'angle, avec d�cimales
	int16_t		long_degrees;	//Partie enti�re des degr�s
	double		long_minutes;	//Minutes d'angle, avec d�cimales
	bool_e		north;
	bool_e 		east;
	uint16_t	ground_speed;
	uint32_t 	date32;
	uint8_t checksum;
}gps_datas_t;

typedef enum
{
	NO_TRAME_RECEIVED = 0,	//Une trame est en cours de r�ception
	CHECKSUM_INVALID,
	TRAME_INVALID,
	TRAME_UNKNOW,			//Une trame inconnue a �t� re�ue
	TRAME_GPRMC,			//Une trame GPRMC a �t� re�ue
	TRAME_GPGGA				//Une trame GPGGA a �t� re�ue
}nmea_frame_e;

typedef enum
{
	INIT = 0,
	TRAME_RECEIVE,
	SLEEP,
	STOP,

}tracker_gps_state;

void GPS_main(void);

void GPS_test(void);

void GPS_process_rx(uint8_t c);

void GPS_On(void);

#endif /* APPLI_OBJECTS_OBJECT_TRACKER_GPS_H_ */
