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
		//TODO
		#if OBJECT_ID == OBJECT_MATRIX_LEDS


		#endif
    }
}



char * object_id_to_string(uint8_t id)
{
	char * ret = "unknown object";

	switch(id)
	{
		case OBJECT_BASE_STATION:	ret = "Base Station";	break;
		case OBJECT_SMART_LIGHT:	ret = "Smart Light";	break;
		//TODO
		default:
			break;
	}
	return ret;
}

