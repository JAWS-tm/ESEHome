/*
 * objects_night_light.c
 *
 * Created on: 01/02/2022
 *      Author: NolwennBARMOY
 */

// Eclairage nocturne

#include "../config.h"
#include "../../bsp/WS2812.h"
#include "../common/parameters.h"
#include "../common/buttons.h"
#include "../common/gpio.h"
#include "../common/leds.h"
#include "../common/systick.h"


#if OBJECT_ID == OBJECT_NIGHT_LIGHT

#define BUTTON_INTERVAL 20          		//intervalles de lecture du bouton, en ms
#define COUNT_DEBOUNCE 10                   //durée maximale autorisée de relâchement du bouton (en nombre d'intervalles)
#define COUNT_SHORT_PRESS 5                 //durée mini d'un appui court (en nombre d'intervalles)
#define COUNT_LONG_PRESS 50                 //durée d'un appui long (en nombre d'intervalles)

static volatile uint16_t temps_restant = 0;
static volatile uint16_t nb_appuis = 0;
static volatile uint16_t led_status = 0;
static volatile bool_e flag_led_status_updated = 0;
static volatile uint8_t led[] = {NIGHT_LED_PIN};
static volatile uint32_t option = 0;
static volatile uint32_t choix = 0;
static volatile uint32_t previous_choix = 0;

/*
 * Changement d'état de la LED en cas d'appuis sur le bouton USER
 */

void button_user_callback(void)
{
	flag_led_status_updated = TRUE;
	led_status = (led_status)?0:1;
}

void changer_etat_led_button(){
	GPIO_write(NIGHT_LED_PIN, (led_status)?1:0);
}

/*
 * LED qui clignote
 */
void led_blink(){
	LED_add(LED_ID_USER0, NIGHT_LED_PIN );
	LED_set(LED_ID_USER0, LED_MODE_BLINK);
}

/*
 * LED reste allumee 1 minute
 */
void led_timer_1min(){
	LED_add(LED_ID_USER0, NIGHT_LED_PIN );
	LED_set(LED_ID_USER0, LED_MODE_ON);
	SYSTICK_delay_ms(60000);
	LED_set(LED_ID_USER0, LED_MODE_OFF);
}

/*
 * LED reste allumee 5 minute
 */
void led_timer_5min(){
	LED_add(LED_ID_USER0, NIGHT_LED_PIN );
	LED_set(LED_ID_USER0, LED_MODE_ON);
	SYSTICK_delay_ms(300000);
	LED_set(LED_ID_USER0, LED_MODE_OFF);
}


void appuis_long_button()
{
	//comptage du temps d appui et anti-rebonds
	while(nb_appuis<COUNT_LONG_PRESS){
		SYSTICK_delay_ms(BUTTON_INTERVAL);
	    if(BUTTON_USER_PIN){
	        temps_restant=0;
	        nb_appuis++;
	    }
	    else{
	        temps_restant++;
	    }
	    if(temps_restant>=COUNT_DEBOUNCE){
	        break;
	    }
	}
}

/*
void OBJECT_NIGHT_LIGHT_actuator_state_callback(int32_t new_choix){
	if(new_choix > 0 && new_choix <= 4){
		debug_printf("Nouveau choix envoyé depuis la station de base : %lx\n", new_choix);
		choix = (uint32_t)new_choix;
		flag_led_status_updated = TRUE;
	}

}
*/

void OBJECT_NIGHT_LIGHT_state_machine(void){
	typedef enum{
			INIT,
			RUN,
			SLEEP
		}state_e;

	static state_e state = INIT;
	switch(state)
	{
		case INIT:
			//PARAMETERS_init();
			//PARAMETERS_enable(PARAM_MY_BASE_STATION_ID, 2, TRUE, NULL, NULL);
			//PARAMETERS_enable(PARAM_ACTUATOR_STATE, 1, TRUE, &OBJECT_NIGHT_LIGHT_actuator_state_callback, NULL);
			GPIO_configure(NIGHT_LED_PIN, NRF_GPIO_PIN_NOPULL, TRUE);
			BUTTONS_add(BUTTON_USER0, BUTTON_USER_PIN, FALSE, &button_user_callback, NULL, NULL, NULL);
			//option = choix;
			state = RUN;
		break;

		case RUN:
			option = 1;
			//debug_printf("%lx\n", choix);
			/*
				if(flag_led_status_updated){
					if(BUTTONS_read(BUTTON_USER0) == TRUE){
					    debug_printf("stop");
					    SYSTICK_delay_ms(50);
					    if(BUTTONS_read(BUTTON_USER0) == FALSE){
					    	changer_etat_led_button();
					    }
						else if(BUTTONS_read(BUTTON_USER0) == TRUE){
							debug_printf("stop1");
							SYSTICK_delay_ms(50);
							if(BUTTONS_read(BUTTON_USER0) == FALSE){
								led_blink();
							}
						}
						else if(BUTTONS_read(BUTTON_USER0) == TRUE){
							debug_printf("stop1");
							SYSTICK_delay_ms(50);
							if(BUTTONS_read(BUTTON_USER0) == FALSE){
								led_blink();
							}
						}
						else if(BUTTONS_read(BUTTON_USER0) == TRUE){
							debug_printf("stop1");
							SYSTICK_delay_ms(50);
							if(BUTTONS_read(BUTTON_USER0) == FALSE){
								led_blink();
							}
						}
					flag_led_status_updated = FALSE;
				}}*/


			switch(option){
			case 1:
				changer_etat_led_button();
				break;
			case 2:
				led_blink();
				break;
			case 3:
				led_timer_1min();
				break;
			case 4:
				led_timer_5min();
				break;
			default:
				break;
			}

			//previous_choix = choix;

		break;

		case SLEEP:{
			break;
		}

		default:
			break;
	}
}



#endif
