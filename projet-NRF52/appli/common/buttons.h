/*
 * buttons.h
 *
 *  Created on: 20 janv. 2021
 *      Author: Nirgal
 */

#ifndef BUTTONS_H_
#define BUTTONS_H_
#include "../config.h"
#include "macro_types.h"


typedef enum
{
	BUTTON_NETWORK,
	BUTTON_USER0,
	BUTTON_USER1,
	BUTTON_ALERTE,
	BUTTON_NB	//Nombre max de boutons
}button_id_e;

typedef enum
{
	BUTTON_EVENT_NONE,
	BUTTON_PRESS_EVENT,
	BUTTON_RELEASE_EVENT
}button_event_e;




void BUTTONS_init(void);

void BUTTONS_process_main(void);

void BUTTONS_add(button_id_e id, uint8_t pin, bool_e pullup, callback_fun_t callback);

void BUTTONS_process_ms(void);

void BUTTONS_get_event(button_event_e * event, button_id_e * button);

bool_e BUTTONS_read(button_id_e id);

void BUTTONS_network_process(void);

void BUTTONS_network_test(void);


#endif /* BUTTONS_H_ */
