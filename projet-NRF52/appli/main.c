#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <sys/unistd.h>

#include "config.h"
#include "main.h"

#include "components/libraries/util/sdk_common.h"
#include "nrf.h"
#include "nrf52.h"
#include "nrfx.h"
#include "components/libraries/log/nrf_log_ctrl.h"
#include "components/libraries/log/nrf_log_default_backends.h"
#include "nrf_gpio.h"
#include "common/macro_types.h"
#include "common/secretary.h"
#include "common/serial_dialog.h"
#include "common/systick.h"
#include "common/leds.h"
#include "common/buttons.h"
#include "common/gpio.h"

//Tout les includes des header des objets.
#include "objects/object_tracker_gps.h"
#include "objects/object_fall_sensor.h"

#undef NRF_LOG_ENABLED
#define NRF_LOG_ENABLED 1

void banque_de_fonctions_utiles(void)
{
	uint32_t i;
	nrf_gpio_range_cfg_input(13, 16, GPIO_PIN_CNF_PULL_Pulldown);
	i = nrf_gpio_pin_read(16);
}

void clocks_start( void )
{
    NRF_CLOCK->EVENTS_HFCLKSTARTED = 0;
    NRF_CLOCK->TASKS_HFCLKSTART = 1;

    while (NRF_CLOCK->EVENTS_HFCLKSTARTED == 0);
}

void button_network_process(void)
{
	//LED_set_flash_limited_nb(LED_ID_NETWORK, 3, 200);
}

int main(void)
{
	//Démarrage de l'horloge.
    clocks_start();

    //Lancement du timer systick
    Systick_init();

    //Initialisation GPIO
    GPIO_init();

    //Initialisation du module LEDS
    LEDS_init(I_HAVE_LED_BATTERY);

    BUTTONS_init();

    //Initialisation du SERIAL_DIALOG
#if USE_SERIAL_DIALOG
    SERIAL_DIALOG_init();	//initialise l'UART et permet les dialogues avec le PC de débogage.
#endif

    //Fin de l'initialisation
    debug_printf("NRF52832 initialisé\n");
    volatile char id;
    id = OBJECT_ID;
    debug_printf("My id is %d. I am \"%s\"\n", id, object_id_to_string(id));
	LED_add(LED_ID_BATTERY, PIN_LED_BATTERY);
	LED_set(LED_ID_BATTERY, LED_MODE_ON);
	BUTTONS_network_test();
    while (1)
    {
    	//Code commun à tout les objets
    	SECRETARY_process_main();

    	BUTTONS_process_main();

    	//Orientation du main vers chaque code de chaque objets
    		#if OBJECT_ID == OBJECT_BASE_STATION

    		#endif


    		#if OBJECT_ID == OBJECT_SMART_LIGHT

    		#endif

    		#if OBJECT_ID == OBJECT_NIGHT_LIGHT


    		#endif

    		#if OBJECT_ID == OBJECT_BRIGHTNESS_SENSOR


    		#endif

    		#if OBJECT_ID == OBJECT_STATION_METEO_INT
    			STATION_METEO_INT_MAIN();

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
    			OBJECT_FALL_SENSOR_state_machine();

    		#endif


    		#if OBJECT_ID == OBJECT_RFID


    		#endif

    		#if OBJECT_ID == OBJECT_TRACKER_GPS
    			printf("main");
    			GPS_main();

    		#endif

    		#if OBJECT_ID == OBJECT_VOICE_CONTROL


    		#endif

    		#if OBJECT_ID == OBJECT_TOUCH_SCREEN
    			object_touch_screen_process_main();

    		#endif

    		#if OBJECT_ID == OBJECT_E_PAPER


    		#endif

    		#if OBJECT_ID == OBJECT_MATRIX_LEDS


    		#endif

    		#if OBJECT_ID == OBJECTS_NB


    		#endif
    }
}



char * object_id_to_string(uint8_t id)
{
	char * ret = "unknown object";

	switch(id)
	{
		case OBJECT_BASE_STATION:		ret = "Base Station";		break;
		case OBJECT_SMART_LIGHT:		ret = "Smart Light";		break;
		case OBJECT_NIGHT_LIGHT:		ret = "Night Light";		break;
		case OBJECT_BRIGHTNESS_SENSOR:	ret = "Brightness Sensor";	break;
		case OBJECT_STATION_METEO_INT:	ret = "Station Meteo Int";	break;
		case OBJECT_OUT_WEATHER_STATION:ret = "Station Meteo Ext";	break;
		case OBJECT_ROLLER_SHUTTER:		ret = "Roller Shutter";		break;
		case OBJECT_ALARM:				ret = "Alarm";				break;
		case OBJECT_FIRE_DETECTOR:		ret = "Fire Detector";		break;
		case OBJECT_WINE_DEGUSTATION:	ret = "Wine Degustation";	break;
		case OBJECT_VENTILATOR:			ret = "Ventilator";			break;
		case OBJECT_GSM:				ret = "GSM";				break;
		case OBJECT_FALL_SENSOR:		ret = "Fall Sensor";		break;
		case OBJECT_TRACKER_GPS:		ret = "Tracker GPS";		break;
		case OBJECT_VOICE_CONTROL:		ret = "Voice Control";		break;
		case OBJECT_TOUCH_SCREEN:		ret = "Touch Screen";		break;
		case OBJECT_E_PAPER:			ret = "E Paper";			break;
		case OBJECT_MATRIX_LEDS:		ret = "Matrix Leds";		break;


		//TODO
		default:
			break;
	}
	return ret;
}

