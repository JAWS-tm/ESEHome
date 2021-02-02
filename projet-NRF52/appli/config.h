/*
 * config.h
 *
 *  Created on: 21 nov. 2019
 *      Author: Nirgal
 */

#ifndef CONFIG_CONFIG_H_
#define CONFIG_CONFIG_H_

#include <stdint.h>
#include "common/macro_types.h"
#include "modules/nrfx/mdk/nrf52.h"
#include "modules/nrfx/mdk/nrf52_bitfields.h"
#include "components/softdevice/s132/headers/nrf_error.h"
#include "../config/nrfx_config.h"

//liste des objets
#define OBJECT_BASE_STATION		0
#define OBJECT_SMART_LIGHT		1
#define OBJECT_NIGHT_LIGHT		2

#define OBJECT_STATION_METEO_INT	5

//TODO �num�rer les objets !
#define OBJECT_MATRIX_LEDS		24
#define OBJECTS_NB				25


///////////////////////////////////////////////////////////////////////////////////
//Num�ro de l'objet pour lequel on compile.
#include "config_perso.h"
///////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////
//Config propres � chaque objets.
	#if OBJECT_ID == OBJECT_BASE_STATION

	#endif
	#if OBJECT_ID == OBJECT_SMART_LIGHT

	#endif
	#if OBJECT_ID == OBJECT_NIGHT_LIGHT
		

	#endif
	#if OBJECT_ID == OBJECT_STATION_METEO_INT


	#endif

	
	//...
	#if OBJECT_ID == OBJECT_MATRIX_LEDS


	#endif


///////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////
//Configs communes � tout les objets.


#define PIN_UART_TX			6
#define PIN_UART_RX			8
#define PIN_BUTTON_NETWORK	18
#define PIN_LED_NETWORK		19
#define PIN_LED_BATTERY		20
#define PIN_RESET			21

//TODO compl�ter la liste des objets dot�s d'une led batterie !
#define I_HAVE_LED_BATTERY	(OBJECT_ID == OBJECT_BASE_STATION || OBJECT_ID == 4)


#define ENABLE_POWERDOWN_FROM_MCU		1	//si 1 : permet de couper l'alim avec un appui long sur le bouton poussoir. Impose le maintient du bouton pendant 1 seconde au d�marrage.


#ifndef USE_SERIAL_DIALOG		//si aucun objet n'a d�fini ceci � 0... alors on active la brique SERIAL_DIALOG
	#define USE_SERIAL_DIALOG	1
#endif

//pour voir les IRQ Radio...
#define SP_DEBUG_RADIO_IRQ_INIT()		nrf_gpio_cfg_output(12)
#define SP_DEBUG_RADIO_IRQ_SET()		NRF_P0->OUTSET = (1 << (12))
#define SP_DEBUG_RADIO_IRQ_RESET()		NRF_P0->OUTCLR = (1 << (12))


#define OFF_BUTTON_LONG_PRESS_DURATION	2000	//dur�e de l'appui sur le bouton OFF qui d�clenche l'extinction.
#define AUTO_OFF_IF_NO_EVENT_DURATION	(30*60*1000)	//extinction automatique au bout de 30mn

#define TIMESLOT_DURATION	1	//ms

#define OFFSET_TRANSMISSION_DURATION	13440

void uart_puts(char * s);
uint32_t debug_printf(char * format, ...);

//Constitution d'un message.
//				Master Group RECIPIENTS(6) MSG_ID DATASIZE DATAS
#define BYTE_POS_MASTER_ID	(0)
#define BYTE_POS_GROUP_ID	(BYTE_POS_MASTER_ID+1)
#define BYTE_POS_RECIPIENTS	(BYTE_POS_GROUP_ID+1)
#define BYTE_QTY_RECIPIENTS	(6)
#define BYTE_POS_MSG_ID		(BYTE_POS_RECIPIENTS+BYTE_QTY_RECIPIENTS)
#define BYTE_POS_DATASIZE	(BYTE_POS_MSG_ID+1)
#define BYTE_POS_DATAS		(BYTE_POS_DATASIZE+1)

#define MAX_DATA_SIZE		(32-BYTE_POS_DATAS)


#define USE_ADC						1

#ifndef USE_MPU6050
	#define USE_MPU6050		0
#endif


#if USE_MPU6050 //   || USE_... || USE...
	#ifndef I2C_SDA_PIN_NB
		#define	I2C_SDA_PIN_NB	25
	#endif
	#ifndef I2C_SCL_PIN_NB
		#define	I2C_SCL_PIN_NB	26
	#endif
#endif
///////////////////////////////////////////////////////////////////////////////////
#ifndef NRF52832_XXAA
	#define NRF52832_XXAA
#endif
#include "nrf.h"


#endif /* CONFIG_CONFIG_H_ */

