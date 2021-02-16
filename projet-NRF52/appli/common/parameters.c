/*
 * parameter.c
 *
 *  Created on: 15 févr. 2021
 *      Author: meven
 */

#include "appli/config.h"
#include "parameters.h"

typedef struct
{
	bool_e enable;
	bool_e updated;
	bool_e value_saved_in_flash;	//TODO gérer cette fonctionnalité
	uint32_t value;
	callback_fun_i32_t	callback;
}params_t;

static params_t params[PARAM_32_BITS_NB];


//Cette fonction doit être appelée lors de l'init, avant l'init des objets.
void PARAMETERS_init(void)
{
	for(uint8_t i = 0; i<PARAM_32_BITS_NB; i++)
	{
		params[i] = (params_t){
			.enable = FALSE,
			.updated = FALSE,
			.value = 0,
			.callback = NULL
			};
	}
}

//chaque objet doit appeler cette fonction pour chacun de ses paramètres
void PARAMETERS_enable(param_id_e param_id, int32_t default_value, bool_e value_saved_in_flash, callback_fun_i32_t callback)
{
	params[param_id].enable = TRUE;
	params[param_id].value = default_value;
	params[param_id].value_saved_in_flash = default_value;
	params[param_id].callback = callback;
	params[param_id].updated = FALSE;
}

void PARAMETERS_update(param_id_e param_id, int32_t new_value)
{
	params[param_id].value = new_value;

	if(params[param_id].enable)
	{
		params[param_id].updated = TRUE;
		if(params[param_id].callback != NULL)
			params[param_id].callback(new_value);

		if(params[param_id].value_saved_in_flash)
		{
			//TODO sauvegarder le paramètre en flash...
		}
	}
}

void PARAMETERS_restore_from_flash(void)
{
	//TODO pour tout les paramètres activés, et dont value_saved_in_flash est vrai, on va chercher leurs valeurs en flash.
}


int32_t PARAMETERS_get(param_id_e param_id)
{
	return params[param_id].value;
}


/*
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
