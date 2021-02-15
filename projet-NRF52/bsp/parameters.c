/*
 * parameter.c
 *
 *  Created on: 15 févr. 2021
 *      Author: meven
 */

/*#include "appli/config.h"
#include "parameters.h"

//ajout possible, choisir un mode general ou precisé pour l'objet

typedef enum{
	ON,
	OFF
}state_e;

uint32_t id_object;

uint32_t *id = &id_object;


//essai de fonction de parametrage (a revoir)
void PARAMETER_set(uint32_t object_id,uint32_t parametre, uint32_t value){
	*id = object_id;


}

//Orientation du main vers chaque code de chaque objets
    		#if id_object == OBJECT_BASE_STATION


    		#endif


    		#if id_object == OBJECT_SMART_LIGHT

			state_e state_led;

			typedef enum{
				DAY,
				NIGHT,
				FILM
			}mode_e;

			uint32_t brightness;

    		#endif

    		#if id_object == OBJECT_NIGHT_LIGHT

			state_e state_led;

			color_t color;

    		#endif

    		#if id_object == OBJECT_BRIGHTNESS_SENSOR

			uint32_t brightness;

    		#endif

    		#if id_object == OBJECT_STATION_METEO_INT

			uint32_t temperature;

			uint32_t pressure;

			uint32_t humidity;

    		#endif

    		#if id_object == OBJECT_OUT_WEATHER_STATION

			uint32_t temperature;

			uint32_t pressure;

			uint32_t humidity;

			uint32_t wind_speed;

			uint32_t rain;

    		#endif

    		#if id_object == OBJECT_ROLLER_SHUTTER



    		#endif

    		#if id_object == OBJECT_ALARM

			state_e alert;

    		#endif

    		#if id_object == OBJECT_FIRE_DETECTOR

			uint32_t smoke_concentration;

			uint32_t CO_concentration;

			uint32_t gas_concentration;

    		#endif

    		#if id_object == OBJECT_WINE_DEGUSTATION

			uint32_t temperature;

    		#endif

    		#if id_object == OBJECT_VENTILATOR

			uint32_t temperature;

    		#endif

    		#if id_object == OBJECT_GSM

			state_e sending_alert;

			//a compléter

    		#endif

    		#if id_object == OBJECT_FALL_SENSOR

			uint32_t limit_alert;

			parameters_e limit;

			state_e alert;

			state_e state_object;

    		#endif

    		#if id_object == OBJECT_TRACKER_GPS



    		#endif

    		#if id_object == OBJECT_RFID



    		#endif

    		#if id_object == OBJECT_TRACKER_GPS


    		#endif

    		#if id_object == OBJECT_VOICE_CONTROL


    		#endif

    		#if id_object == OBJECT_TOUCH_SCREEN


    		#endif

    		#if id_object == OBJECT_E_PAPER


    		#endif

    		#if id_object == OBJECT_MATRIX_LEDS

			state_e state_object;

    		#endif

    		#if id_object == OBJECTS_NB


    		#endif

*/
