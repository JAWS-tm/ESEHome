/*
 * object_brightness_sensor.c
 *
 *  Created on: 4 févr. 2021
 *      Author: antho_9ak3x1e
 */
#include "../config.h"
#include "object_brightness_sensor.h"



void state_machine(void)
{
	state_e state = INIT;
	BUTTONS_add(BUTTON_NETWORK, PIN_BUTTON_NETWORK, TRUE, &BUTTON_action_sleep);
	switch(state)
	{
	case INIT :
			state = GET_DATA;
		break;
	case GET_DATA :
		LED_set(LED_ID_NETWORK, LED_MODE_OFF);
		LED_set(LED_ID_BATTERY, LED_MODE_OFF);
		state = SEND_DATA;
		break;
	case SEND_DATA :
		LED_add(LED_ID_NETWORK, PIN_LED_NETWORK);
		LED_set(LED_ID_NETWORK, LED_MODE_FLASH);


		state = GET_DATA;

		break;
	case SLEEP :
		LED_add(LED_ID_BATTERY, PIN_LED_BATTERY);
		LED_set(LED_ID_BATTERY, LED_MODE_FLASH);
		break;
	case STOP :

		break;
	default :
	}
}

void BUTTON_action_sleep(state_e state)
{
	if(state == SEND_DATA){
		state = SLEEP;
	}else if(state == GET_DATA){
		state = SLEEP;
	}else if (state == SLEEP){
		state = GET_DATA;
	}
}


