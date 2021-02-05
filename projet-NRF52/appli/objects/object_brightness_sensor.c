/*
 * object_brightness_sensor.c
 *
 *  Created on: 4 févr. 2021
 *      Author: antho_9ak3x1e
 */
#include "../config.h"
#include "object_brightness_sensor.h"

#if OBJECT_ID == OBJECT_BRIGHTNESS_SENSOR

void state_machine(void)
{
	state_e state = INIT;
	switch(state)
	{
	case INIT :
			state = GET_DATA;
		break;
	case GET_DATA :
		state = SEND_DATA;
		break;
	case SEND_DATA :
		state = GET_DATA;
		break;
	case SLEEP :

		break;
	case STOP :

		break;
	default :
	}
}



#endif
