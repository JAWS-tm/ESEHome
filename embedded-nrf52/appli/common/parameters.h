/*
 * parameters.h
 *
 *  Created on: 15 f�vr. 2021
 *      Author: meven
 */

#ifndef BSP_PARAMETERS_H_
#define BSP_PARAMETERS_H_
#include "macro_types.h"
#include "../config.h"

//Liste des param�tres, tout objets confondus.
typedef enum
{
	PARAM_UNKNOW = 0,
	PARAM_MY_BASE_STATION_ID,
	PARAM_ACTUATOR_STATE,
	PARAM_SENSOR_VALUE,
	PARAM_ALARM_TRESHOLD,
	PARAM_ALARM_WAY,
	PARAM_TEMPERATURE,
	PARAM_HYGROMETRY,
	PARAM_COLOR,
	PARAM_REFRESH_PERIOD,
	PARAM_PRESSURE,
	PARAM_BRIGHTNESS,
	PARAM_WINDSPEED,
	PARAM_PLUVIOMETRY,
	PARAM_SCREEN_COLOR,
	PARAM_MODE,
	PARAM_DURATION = 19,
	PARAM_START_TIME = 16,
	PARAM_STOP_TIME = 17,
	PARAM_CURRENT_TIME,
	PARAM_TRESHOLD,
	PARAM_PM1_0, //Ajout de param�tres pour l'objet "Air Sensor" (ID = 15)
	PARAM_PM2_5,
	PARAM_PM10,
	PARAM_MP3_TRACK,
	PARAM_32_BITS_NB = 63,	//avant ce define, tout les param�tres tiennent sur 32 bits.


	//Param�tres dont la taille d�passe 32 bits... et dont le traitement est sp�cifiquement confi� � l'objet par des fonctions de callback.
	PARAM_TEXT_PART0,
	PARAM_TEXT_PART1,
	PARAM_TEXT_PART2,
	PARAM_TEXT_PART3,
	PARAM_TEXT_PART4,
	PARAM_TEXT_PART5,
	PARAM_TEXT_PART6,
	PARAM_TEXT_PART7,
	PARAM_NB
}param_id_e;

typedef enum
{
	ALARM_WAY_MAX,	//le seuil est un maximum � ne pas d�passer
	ALARM_WAY_MIN,	//le seuil est un minimum � ne pas d�passer
	ALARM_WAY_DIFF, //le seuil est une valeur � ne pas quitter (pour un capteur tout ou rien ... !)
}alarm_way_e;



void PARAMETERS_init(void);

//chaque objet doit appeler cette fonction pour chacun de ses param�tres
void PARAMETERS_enable(param_id_e param_id, int32_t default_value, bool_e value_saved_in_flash, callback_fun_i32_t callback_after_set_from_RF, callback_i32_fun_t callback_if_get_from_RF);

//cette fonction est appel�e soit par l'objet qui met � jour une valeur (accessible sur demande par la station)
//  soit suite � la station qui met � jour une valeur (accessible sur demande de l'objet)
void PARAMETERS_update(param_id_e param_id, int32_t new_value);

void PARAMETERS_update_custom(param_id_e param_id, uint8_t * datas);

void PARAMETERS_restore_from_flash(void);

void PARAMETERS_read_from_flash(param_id_e param_id);

//permet de r�cup�rer la valeur d'un param�tre
int32_t PARAMETERS_get(param_id_e param_id);

void PARAMETERS_send_param32_to_basestation(param_id_e param_id);


#endif /* BSP_PARAMETERS_H_ */
