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
#define OBJECT_BRIGHTNESS_SENSOR    4
#define OBJECT_STATION_METEO_INT    5
#define OBJECT_OUT_WEATHER_STATION  6
#define OBJECT_ROLLER_SHUTTER       7
#define OBJECT_ALARM                8
#define OBJECT_FIRE_DETECTOR        9
#define OBJECT_WINE_DEGUSTATION     10
#define OBJECT_VENTILATOR           11
#define OBJECT_GSM                  12
#define OBJECT_FALL_SENSOR          13
#define OBJECT_TRACKER_GPS          16
#define OBJECT_RFID                 17
#define OBJECT_VOICE_CONTROL        19
#define OBJECT_TOUCH_SCREEN         20
#define OBJECT_E_PAPER              21
#define OBJECT_MATRIX_LEDS		24
#define OBJECTS_NB				25


///////////////////////////////////////////////////////////////////////////////////
//Numéro de l'objet pour lequel on compile
#include "config_perso.h"
///////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////
//Config propres à chaque objets.
	#if OBJECT_ID == OBJECT_BASE_STATION

	#endif

	#if OBJECT_ID == OBJECT_SMART_LIGHT

	#endif

	#if OBJECT_ID == OBJECT_SMART_LIGHT

	#endif

	#if OBJECT_ID == OBJECT_NIGHT_LIGHT
		

	#endif

	#if OBJECT_ID == OBJECT_BRIGHTNESS_SENSOR


	#endif

	#if OBJECT_ID == OBJECT_STATION_METEO_INT


	#endif

	#if OBJECT_ID == OBJECT_OUT_WEATHER_STATION


	#endif

	#if OBJECT_ID == OBJECT_ROLLER_SHUTTER


	#endif

	#if OBJECT_ID == OBJECT_ALARM


	#endif

	#if OBJECT_ID == OBJECT_FIRE_DETECTOR


	#endif

	#if OBJECT_ID == OBJECT_WINE_DEGUSTATION


	#endif

	#if OBJECT_ID == OBJECT_VENTILATOR


	#endif

	#if OBJECT_ID == OBJECT_GSM


	#endif

	#if OBJECT_ID == OBJECT_FALL_SENSOR


	#endif

	#if OBJECT_ID == OBJECT_TRACKER_GPS


	#endif

	#if OBJECT_ID == OBJECT_RFID


	#endif

	#if OBJECT_ID == OBJECT_TRACKER_GPS


	#endif

	#if OBJECT_ID == OBJECT_VOICE_CONTROL


	#endif

	#if OBJECT_ID == OBJECT_TOUCH_SCREEN


	#endif

	#if OBJECT_ID == OBJECT_E_PAPER


	#endif

	#if OBJECT_ID == OBJECT_MATRIX_LEDS

	//adaptation au choix hardware

	#define A 10
	#define B 9
	#define D 7
	#define C 5

	//partie haute de la matrice

	#define HIGH_B 14
	#define HIGH_G 15
	#define HIGH_R 16

	//partie basse de la matrice

	#define LOW_B 11
	#define LOW_G 12
	#define LOW_R 13

	//CLK, LAT et OE

	#define OE 2
	#define CLK 3
	#define LAT 4

	//Simplification fonction d'écriture et de configuration
	#define WRITE(x,y) GPIO_write(uint8_t pin, bool_e value)
	#define CONFIG_OUTPUT(port_pin) GPIO_configure(uint8_t pin, NRF_GPIO_PIN_PULLUP , 1)

	//variable de couleurs
	typedef uint8_t color_t;
	#define COLOR_BLACK     0b00000000
	#define COLOR_RED       0b00000100
	#define COLOR_GREEN     0b00000010
	#define COLOR_BLUE      0b00000001
	#define COLOR_YELLOW    0b00000110
	#define COLOR_CYAN      0b00000011
	#define COLOR_PURPLE    0b00000101
	#define COLOR_WHITE     0b00000111

	//Simplification fonction d'écriture et de configuration
	#define WRITE(port_pin, value) 	GPIO_write(port_pin, value)
	#define CONFIG_OUTPUT(port_pin) 	GPIO_configure(port_pin, NRF_GPIO_PIN_PULLUP , 1)


	#endif

	#if OBJECT_ID == OBJECTS_NB


	#endif

///////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////
//Configs communes à tout les objets.


#define PIN_UART_TX			6
#define PIN_UART_RX			8
#define PIN_BUTTON_NETWORK	18
#define PIN_LED_NETWORK		19
#define PIN_LED_BATTERY		20
#define PIN_RESET			21

//TODO compléter la liste des objets dotés d'une led batterie !
#define I_HAVE_LED_BATTERY	(OBJECT_ID == OBJECT_BASE_STATION || OBJECT_ID == 4)


#define ENABLE_POWERDOWN_FROM_MCU		1	//si 1 : permet de couper l'alim avec un appui long sur le bouton poussoir. Impose le maintient du bouton pendant 1 seconde au démarrage.


#ifndef USE_SERIAL_DIALOG		//si aucun objet n'a défini ceci à 0... alors on active la brique SERIAL_DIALOG
	#define USE_SERIAL_DIALOG	1
#endif

//pour voir les IRQ Radio...
#define SP_DEBUG_RADIO_IRQ_INIT()		nrf_gpio_cfg_output(12)
#define SP_DEBUG_RADIO_IRQ_SET()		NRF_P0->OUTSET = (1 << (12))
#define SP_DEBUG_RADIO_IRQ_RESET()		NRF_P0->OUTCLR = (1 << (12))


#define OFF_BUTTON_LONG_PRESS_DURATION	2000	//durée de l'appui sur le bouton OFF qui déclenche l'extinction.
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
