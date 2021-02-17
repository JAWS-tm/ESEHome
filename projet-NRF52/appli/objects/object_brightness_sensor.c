/*
 * object_brightness_sensor.c
 *
 *  Created on: 4 févr. 2021
 *      Author: antho_9ak3x1e
 */
#include "../config.h"
#include "object_brightness_sensor.h"
#include "../common/leds.h"
#include "../common/buttons.h"
#include "../../bsp/bh1750fvi.h"

#if OBJECT_ID == OBJECT_BRIGHTNESS_SENSOR

void state_machine(void)
{
	static state state = INIT;
	switch(state)
	{
	case INIT :
		LED_add(LED_ID_BATTERY, PIN_LED_BATTERY);
		LED_add(LED_ID_NETWORK, PIN_LED_NETWORK);
		state = GET_DATA;
		BUTTONS_add(BUTTON_NETWORK, PIN_BUTTON_NETWORK, TRUE, &BUTTON_action_sleep, NULL, NULL, NULL);

		break;
	case GET_DATA :
		LED_set(LED_ID_NETWORK, LED_MODE_OFF);
		LED_set(LED_ID_BATTERY, LED_MODE_OFF);
		BH1750FVI_demo();

		state = SEND_DATA;
		break;
	case SEND_DATA :

		LED_set(LED_ID_NETWORK, LED_MODE_FLASH);
		state = GET_DATA;
		break;
	case SLEEP :
		LED_set(LED_ID_NETWORK, LED_MODE_OFF);
		LED_set(LED_ID_BATTERY, LED_MODE_FLASH);
		break;
	case STOP :

		break;

	}
}

void BUTTON_action_sleep(state state)
{
	if(state == SEND_DATA){
		state = SLEEP;
	}else if(state == GET_DATA){
		state = SLEEP;
	}else if (state == SLEEP){
		state = GET_DATA;
	}
}

#endif
