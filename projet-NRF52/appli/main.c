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
#include "common/parameters.h"
#include "common/rf_dialog.h"
#include "common/verbose.h"

//Tout les includes des header des objets.
#include "objects/object_base_station.h"
#include "objects/object_tracker_gps.h"
#include "objects/object_fall_sensor.h"
#include "objects/object_station_meteo_int.h"
#include "objects/object_rfid.h"
#include "objects/object_out_weather_station.h"
#include "objects/object_smart_light.h"
#include "objects/object_voice_control.h"
#include "objects/object_fluid_level_detector.h"
#include "objects/object_wine_degustation.h"
#include "objects/object_ventilator.h"
//#include "objects/objet_volet_roulant.h"
#include "objects/object_fire_detector.h"
#include "objects/object_roller_shutter.h"
#include "objects/object_LCD_slider.h"
#include "objects/object_night_light.h"
#include "objects/object_fire_detector.h"
#include "objects/object_roller_shutter.h"
#include "objects/object_LCD_slider.h"
#include "objects/object_night_light.h"
#include "objects/object_touch_screen.h"

//#include "objects/object_smart_socket.h"


void pong_callback(void);
void button_network_process_short_press(void);
void button_network_process_long_press(void);
void button_network_process_5press(void);

#undef NRF_LOG_ENABLED
#define NRF_LOG_ENABLED 1

void banque_de_fonctions_utiles(void)
{
	__unused uint32_t i;
	nrf_gpio_range_cfg_input(13, 16, GPIO_PIN_CNF_PULL_Pulldown);
	i = nrf_gpio_pin_read(16);
}

void clocks_start( void )
{
    NRF_CLOCK->EVENTS_HFCLKSTARTED = 0;
    NRF_CLOCK->TASKS_HFCLKSTART = 1;

    while (NRF_CLOCK->EVENTS_HFCLKSTARTED == 0);

    NRF_NVMC->ICACHECNF = 1;	//Turn CPU cache ON.
}

void button_network_process(void)
{
	//LED_set_flash_limited_nb(LED_ID_NETWORK, 3, 200);
}

int main(void)
{
	//Dmarrage de l'horloge.
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
    SERIAL_DIALOG_init();	//initialise l'UART et permet les dialogues avec le PC de dbogage.
#endif

    PARAMETERS_init();

    RF_DIALOG_init();

    //Fin de l'initialisation
    debug_printf("NRF52832 initialisï¿½\n");
    volatile char id;
    id = OBJECT_ID;

    debug_printf("My object id is %d.\nMy unique id is %x\n I am \"%s\" \n", id, RF_DIALOG_get_my_device_id(), object_id_to_string(id));

#if (OBJECT_ID != OBJECT_BASE_STATION)
    debug_printf("My base station is %x\n", RF_DIALOG_get_my_base_station_id());
    RF_DIALOG_set_callback_pong(&pong_callback);
#endif



    LED_add(LED_ID_NETWORK, PIN_LED_NETWORK);

	//LED_add(LED_ID_BATTERY, PIN_LED_BATTERY);
	//LED_set(LED_ID_BATTERY, LED_MODE_ON);


	LED_add(LED_ID_BATTERY, PIN_LED_BATTERY);
	LED_set(LED_ID_BATTERY, LED_MODE_ON);

	SECRETARY_init();

	BUTTONS_add(BUTTON_NETWORK, PIN_BUTTON_NETWORK, TRUE, &button_network_process_short_press, NULL, &button_network_process_long_press, NULL, &button_network_process_5press);

    while (1)
    {
    	//Code commun ï¿½ tout les objets
    	SECRETARY_process_main();

    	SERIAL_DIALOG_process_main();

    	BUTTONS_process_main();



    	//Orientation du main vers chaque code de chaque objets
		#if OBJECT_ID == OBJECT_BASE_STATION
			BASE_STATION_process_main();
		#endif


		#if OBJECT_ID == OBJECT_SMART_LIGHT
			Smart_light_Main();
		#endif

		#if OBJECT_ID == OBJECT_NIGHT_LIGHT
			OBJECT_NIGHT_LIGHT_state_machine();

		#endif

		#if OBJECT_ID == OBJECT_BRIGHTNESS_SENSOR
			OBJECT_BRIGHTNESS_SENSOR_MAIN();

		#endif

		#if OBJECT_ID == OBJECT_STATION_METEO_INT
			STATION_METEO_INT_MAIN();

		#endif

		#if OBJECT_ID == OBJECT_OUT_WEATHER_STATION
			OUT_WEATHER_STATION_MAIN();
		#endif

		#if OBJECT_ID == OBJECT_ROLLER_SHUTTER
			VOLET_ROULANT_MAIN(void);

		#endif

		#if OBJECT_ID == OBJECT_ALARM


		#endif

		#if OBJECT_ID == OBJECT_FIRE_DETECTOR


		#endif

		#if OBJECT_ID == OBJECT_WINE_DEGUSTATION
			Wine_Degustation_Main();

		#endif

		#if OBJECT_ID == OBJECT_VENTILATOR
		object_ventilator_activation();
		object_ventilator_temperature();
		OBJECT_VENTILATOR_etat_updated_callback();



		#endif

		#if OBJECT_ID == OBJECT_GSM


		#endif

		#if OBJECT_ID == OBJECT_FALL_SENSOR
			OBJECT_FALL_SENSOR_state_machine();
		#endif

		#if OBJECT_ID == OBJECT_WATER_LEVEL_DETECTOR
			OBJECT_WATER_LEVEL_DETECTOR_MAIN();
		#endif
		#if OBJECT_ID == OBJECT_AIR_SENSOR
			OBJECT_AIR_SENSOR_state_machine();

		#endif

		#if OBJECT_ID == OBJECT_TRACKER_GPS


		#endif

		#if OBJECT_ID == OBJECT_RFID

			object_rfid_process_main();

		#endif

		#if OBJECT_ID == OBJECT_TRACKER_GPS
			GPS_main();

		#endif

		#if OBJECT_ID == OBJECT_VOICE_CONTROL
			VOICE_CONTROL_process_main();

		#endif

		#if OBJECT_ID == OBJECT_TOUCH_SCREEN
			object_touch_screen_process_main();

		#endif

		#if OBJECT_ID == OBJECT_E_PAPER


		#endif

		#if OBJECT_ID == OBJECT_MATRIX_LEDS
			MATRIX_afficheur();

		#endif

		#if OBJECT_ID == OBJECTS_NB


		#endif

		#if OBJECT_ID == OBJECT_LCD_SLIDER
			//LCD_SLIDER_process_main();
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
		case OBJECT_WATER_LEVEL_DETECTOR: ret = "Water Level Detector"; break;
		case OBJECT_AIR_SENSOR:			ret = "Air Sensor";			break;
		case OBJECT_TRACKER_GPS:		ret = "Tracker GPS";		break;
		case OBJECT_VOICE_CONTROL:		ret = "Voice Control";		break;
		case OBJECT_TOUCH_SCREEN:		ret = "Touch Screen";		break;
		case OBJECT_E_PAPER:			ret = "E Paper";			break;
		case OBJECT_MATRIX_LEDS:		ret = "Matrix Leds";		break;
		case OBJECT_LCD_SLIDER:			ret="LCD Slider";			break;
		default:
			break;
	}
	return ret;
}


void pong_callback(void)
{
	LED_set(LED_ID_NETWORK, LED_MODE_OFF);
	debug_printf("The base station responded correctly\n");
}

void button_network_process_short_press(void)
{
#if OBJECT_ID != OBJECT_BASE_STATION
	LED_set(LED_ID_NETWORK, LED_MODE_ON);

	debug_printf("Ping base station\n");
	RF_DIALOG_send_msg_id_to_basestation(PING, 0, NULL);
#else
	LED_toggle(LED_ID_NETWORK);
#endif
}

void button_network_process_long_press(void)
{
#if OBJECT_ID != OBJECT_BASE_STATION
	if (RF_DIALOG_get_my_base_station_id() == 0xFFFFFFFF)
	{
		debug_printf("No base station, broadcast msg\n");
		RF_DIALOG_send_msg_id_to_basestation(I_HAVE_NO_SERVER_ID, 0, NULL);
	}
	else
	{
		debug_printf("My base station is 0x%x\n", RF_DIALOG_get_my_base_station_id());
	}
#else
	debug_printf("I'm the base station, my id is 0x%x\n", RF_DIALOG_get_my_device_id());
#endif
}


void button_network_process_5press(void)
{
	// TODO reset usine...

	uint8_t data_size = 5;
	uint8_t data[data_size];

	data[0] = PARAM_COLOR; // parameter id
	data[1] = 0xFF; // color R
	data[2] = 0x00; // color G
	data[3] = 0x00; // color B
	data[4] = 0xFF; // color A

	RF_DIALOG_send_msg_id_to_object(0xFFFFFFFF, PARAMETER_IS, data_size, data);
	debug_printf("Message fictif envoyé en broadcast\n");
}






