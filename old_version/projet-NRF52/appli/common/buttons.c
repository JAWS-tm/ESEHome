/*
 * buttons.c
 *
 *  Created on: 20 janv. 2021
 *      Author: Nirgal
 */
#include "buttons.h"
#include "systick.h"
#include "gpio.h"


typedef struct
{
	bool_e initialized;
	uint8_t pin;
	callback_fun_t callback;
}button_t;

static button_t buttons[BUTTON_NB];

static bool_e initialized = FALSE;
static volatile uint32_t t = 0;
void BUTTONS_process_ms(void);

void BUTTONS_init(void)
{
	for(button_id_e b = 0; b< BUTTON_NB; b++)
	{
		buttons[b].initialized = FALSE;
		buttons[b].callback = NULL;
	}
	Systick_add_callback_function(&BUTTONS_process_ms);

	initialized = TRUE;
}

void BUTTONS_process_main(void)
{
	button_event_e event;
	button_id_e button;
	BUTTONS_get_event(&event, &button);

	if(event == BUTTON_PRESS_EVENT)
	{
		if(buttons[button].callback != NULL)
			buttons[button].callback();
	}
}



void BUTTONS_add(button_id_e id, uint8_t pin, callback_fun_t callback)
{
	//TODO
}


void BUTTONS_process_ms(void)
{
	if(t)
		t--;
}

void BUTTONS_get_event(button_event_e * event, button_id_e * button)
{
	static bool_e previous_states[BUTTON_NB] = {FALSE};

	if(!initialized)
		BUTTONS_init();

	if(!t)
	{
		bool_e stop_loop;
		stop_loop = FALSE;

		t = 10;	//pour un antirebond logiciel, on ne lit les boutons que toutes les 10ms.

		//on parcourt tout les boutons, jusqu'à la fin, ou jusqu'à ce qu'on détecte un événement
		for(button_id_e b = 0; b< BUTTON_NB; b++)
		{
			if(buttons[b].initialized)
			{
				bool_e current;
				current = !GPIO_read(buttons[b].pin);

				if(current && !previous_states[b])
				{
					*event = BUTTON_PRESS_EVENT;
					*button = b;
					stop_loop = TRUE;
				}
				else if(!current && previous_states[b])
				{
					*event = BUTTON_RELEASE_EVENT;
					*button = b;
					stop_loop = TRUE;
				}
				previous_states[b] = current;

				if(stop_loop)
					break;
			}
		}
	}
	else
	{
		*event = BUTTON_EVENT_NONE;
	}
}









