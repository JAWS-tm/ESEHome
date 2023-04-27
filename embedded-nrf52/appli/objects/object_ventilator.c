/*
 * object_ventilator.c
 *
 *  Created on: 30 Janvier 2023
 *      Author: BAUDIQUEY Nicolas
 */


#include "../appli/config.h"
#include "../common/gpio.h"
#include "nrf_gpio.h"
#include "nrf52.h"
#include "bsp/pwm.h"
#include "appli/common/leds.h"
#include "appli/common/buttons.h"
#include "appli/common/serial_dialog.h"
#include "object_ventilator.h"
#include "appli/common/parameters.h"
#include "appli/common/rf_dialog.h"

#if OBJECT_ID == OBJECT_VENTILATOR

static bool_e state_change = FALSE;

static volatile bool_e flag_press_on;
static volatile bool_e flag_press_off;
static volatile bool_e flag_short_press_ON;
static volatile bool_e flag_long_press_ON;
static volatile bool_e flag_short_press_OFF;
static volatile bool_e flag_long_press_OFF;
static volatile bool_e flag_short_release_ON;
static volatile bool_e flag_long_release_ON;
static volatile bool_e flag_long_release_OFF;
static volatile bool_e flag_short_release_OFF;

typedef enum
{
	ASK_OFF 	= 0,
	ASK_ON		= 1,

}ask_of_activation;

static volatile ask_of_activation flag_ask_for_activation = ASK_OFF;

void OBJECT_VENTILATOR_ask_for_activation_callback(int32_t ask_for_activation)
{
	if(ask_for_activation < ASK_OFF)
		flag_ask_for_activation = (ask_of_activation)ask_for_activation;
}
void short_press_ON(){
	flag_short_press_ON = TRUE;
}
void long_press_ON(){
	flag_long_press_ON = TRUE;
}
void short_press_OFF(){
	flag_short_press_OFF = TRUE;
}
void long_press_OFF(){
	flag_long_press_OFF = TRUE;
}
void short_release_ON (){
	flag_short_release_ON = TRUE;
}
void short_release_OFF (){
	flag_short_release_OFF = TRUE;
}
void long_release_ON(){
	flag_long_release_ON = TRUE;
}
void long_release_OFF(){
	flag_long_release_OFF = TRUE;
}


//Main de VENTILATOR
void VENTILATOR_state_machine(void)
{
	//debug_printf("DEBUG state machine\n");
	typedef enum{
		 INIT,
		 ON,
		 OFF,
		 IDLE,
		 COMMUNICATION

	}state_e;

	static state_e state = INIT;
	static state_e previous_state = INIT;
	previous_state = state;

	switch(state) {
		////Initialisation
		case INIT :
			PARAMETERS_init();
			BUTTONS_init();
			PARAMETERS_enable(PARAM_ACTUATOR_STATE, 0, FALSE, &OBJECT_VENTILATOR_ask_for_activation_callback, NULL);

			BUTTONS_add(BUTTON_USER0, button_SB1_PIN, TRUE, &short_press_ON, NULL, &long_press_ON, NULL, NULL);
			BUTTONS_add(BUTTON_USER1, button_SB2_PIN, TRUE,&short_press_OFF, NULL,&long_press_OFF, NULL, NULL);
			GPIO_write(MOSFET_PIN, FALSE);
			state = IDLE;
			break;

		////Allumage du ventilateur
		case ON :
			debug_printf("DEBUG -- ON\n");
			//PWM_init(uint8_t * pins, uint8_t pin_nb, nrf_pwm_clk_t base_clock, uint16_t top_value);
			GPIO_write(MOSFET_PIN, TRUE);
			PWM_init(DATA_VENTILATEUR, 1, NRF_PWM_CLK_16MHz, 999);
			PWM_set_duty(0, 50);

			if (flag_short_press_OFF || flag_ask_for_activation == ASK_OFF){
				state = IDLE;
			}
			break;


			////Desactivation du ventilateur
		case OFF :
			debug_printf("DEBUG -- OFF\n");
			GPIO_write(DATA_VENTILATEUR, FALSE);
			GPIO_write(MOSFET_PIN, FALSE);
			state = IDLE;
			break;


		case IDLE :
			debug_printf("DEBUG -- IDLE\n");

			if (flag_short_press_OFF || flag_ask_for_activation == ASK_OFF){
				state = OFF;
			}
			if (flag_short_press_ON || flag_ask_for_activation == ASK_ON){
				state = ON;
			}
			state = COMMUNICATION;
			break;

		default:
			break;

			//On renvoie les informations que la station de base demande
		case COMMUNICATION :
			debug_printf("curent state :\n");
			PARAMETERS_send_param32_to_basestation(PARAM_ACTUATOR_STATE);
			debug_printf("parameters mode :\n");
			PARAMETERS_send_param32_to_basestation(PARAM_MODE);
			state = IDLE;
		break;


	}

	flag_ask_for_activation = ASK_OFF;
	flag_short_press_ON = FALSE;
	flag_long_press_ON = FALSE;
	flag_short_press_OFF = FALSE;
	flag_long_press_OFF = FALSE;
	flag_short_release_ON = FALSE;
	flag_short_release_OFF = FALSE;
	flag_long_release_OFF = FALSE;
	flag_long_release_ON = FALSE;
}

void VENTILATOR_state_change(void)
{
	state_change = TRUE;
}

#endif
