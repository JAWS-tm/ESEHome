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
//#include "../config/nrfx_config.h"
//#include "modules/nrfx/hal/nrf_gpio.h"

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
//Num�ro de l'objet pour lequel on compile
#include "config_perso.h"
///////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////
//Config propres � chaque objets.
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
		#define USE_DHT11	1
		#define MOSFET_GND  27
		#define DHT11_PIN	2

	#endif

	#if OBJECT_ID == OBJECT_OUT_WEATHER_STATION
		#define PIN_MOSFET   		27
		#define USE_MPU6050  		1
		#define PIN_DHT11    		2
		#define PIN_PLUVIO-  		3
		#define PIN_ANEMO-   		4
		#define PIN_PLUVIO+  		9
		#define PIN_ANEMO+   		10
		#define PIN_MEASURE_BATT    31

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
		#define USE_MPU6050 1

	#endif

	#if OBJECT_ID == OBJECT_TRACKER_GPS
		#define MOSFET_GND_GPS   17
		#define UART_AT_BAUDRATE_9600

	#endif

	#if OBJECT_ID == OBJECT_RFID
		#define RC522_RST_PIN   11
		#define RC522_MOSI_PIN  13
		#define RC522_MISO_PIN 14
		#define RC522_IRQ_PIN 15
		#define RC522_SCK_PIN 12
		#define RC522_CS_PIN	25
		#define USE_RC522	1
		#define RC522_SPI_INSTANCE	0
	#endif


	#if OBJECT_ID == OBJECT_VOICE_CONTROL


	#endif

	#if OBJECT_ID == OBJECT_TOUCH_SCREEN
		#define ILI9341_ENABLED	1
		#define ILI9341_SPI_INSTANCE	0
		#define ILI9341_DC_PIN		11
		#define ILI9341_SCK_PIN		12
		#define ILI9341_MISO_PIN 	14
		#define ILI9341_MOSI_PIN	13
		#define	ILI9341_SS_PIN		9
		#define ILI9341_RST_PIN		10
		#define ILI9341_HEIGHT	240
		#define ILI9341_WIDTH	320

	#endif

	#if OBJECT_ID == OBJECT_E_PAPER


	#endif

	#if OBJECT_ID == OBJECT_MATRIX_LEDS


		#define USE_MATRIX		1


	#endif

	#if OBJECT_ID == OBJECTS_NB


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
#define I_HAVE_LED_BATTERY	(OBJECT_ID == OBJECT_BASE_STATION || OBJECT_ID == 6 || OBJECT_ID == OBJECT_FALL_SENSOR || OBJECT_ID == 13)
#define I_HAVE_MEASURE_VBAT	(OBJECT_ID == OBJECT_BASE_STATION || OBJECT_ID == 6 || OBJECT_ID == OBJECT_FALL_SENSOR || OBJECT_ID == 13)

#define USE_SPI	(OBJECT_ID == OBJECT_TOUCH_SCREEN || OBJECT_ID == OBJECT_RFID)

#define USE_TWI	(OBJECT_ID == OBJECT_FALL_SENSOR)


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




#define USE_ADC						1
#define USE_ADC_CHANNEL_AIN0		0	//P0.02
#define USE_ADC_CHANNEL_AIN1		(OBJECT_ID == OBJECT_VENTILATOR)	//P0.03
#define USE_ADC_CHANNEL_AIN2		0	//P0.04
#define USE_ADC_CHANNEL_AIN3		0	//P0.05
#define USE_ADC_CHANNEL_AIN4		0	//P0.06
#define USE_ADC_CHANNEL_AIN7		I_HAVE_MEASURE_VBAT	//P0.31

#define ADC_USE_CHANNELS_NB			(USE_ADC_CHANNEL_AIN0+USE_ADC_CHANNEL_AIN1+USE_ADC_CHANNEL_AIN7)

#define CHANNEL_ADC_MEASURE_VBAT	7
#if OBJECT_ID == OBJECT_VENTILATOR
	#define CHANNEL_ADC_MCP9701			1
#endif





#ifndef USE_DHT11
	#define USE_DHT11		0
#endif

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
