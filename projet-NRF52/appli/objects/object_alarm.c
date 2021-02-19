/*
 * object_alarm.c
 *
 *  Created on: 18 févr. 2021
 *      Author: briyd
 */

#include "../config.h"

#if OBJECT_ID == OBJECT_ALARM
#include "object_alarm.h"
#include "buttons.h"

static bool_e state_changement = FALSE;

void object_alarm_main(void){

	if incendie{
		while(incendie = true) {
			alarm(200, 2000, 20);
		}
		nosound();
	}

}

void alarm(int depart, int arrive,int pas){
	int a;
	for (a = depart; a <= arrive; a = a + pas)
	{
	     sound(a);
	     delay(25);
	}

}

void alarm_stop(){
	BUTTONS_set_long_press_callback(BUTTON_NETWORK, &etat_ampli);

}


void message_lu(){
	// reception d'un message du serveur

	switch(){
	case //incendie// :

		break;
	case //reveil//:
		break;
	case //infraction// :
		break;

	}
}

void etat_ampli(){
	state_changement = TRUE;
}

#endif

