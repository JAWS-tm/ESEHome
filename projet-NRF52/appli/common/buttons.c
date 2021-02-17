/*
 * buttons.c
 *
 *  Created on: 20 janv. 2021
 *      Author: Nirgal & Thbault Malary & Yannis Verhasselt
 */
#include "buttons.h"
#include "systick.h"
#include "gpio.h"
#include "leds.h"

#define FIVE_FAST_PRESS_DURATION 2000	//unité : [1ms] => 2 seconde.

typedef struct
{
	bool_e initialized;
	uint8_t pin;
	bool_e pullup;
	callback_fun_t callback;
}button_t;

static button_t buttons[BUTTON_NB];
static button_event_functions_e state;

static bool_e initialized = FALSE;
static bool_e entrance;
static volatile uint32_t t = 0;
static volatile uint32_t t_for_5_fast_press = 0;
static volatile uint32_t t_for_long_press = 0;
static uint8_t nb_fast_press = 0;

void BUTTONS_process_ms(void);

void BUTTONS_init(void)
{
	for(button_id_e b = 0; b< BUTTON_NB; b++)
	{
		buttons[b].initialized = FALSE;
		buttons[b].callback = NULL;
		buttons[b].pullup = TRUE;
	}
	Systick_add_callback_function(&BUTTONS_process_ms);

	BUTTONS_add(BUTTON_NETWORK, PIN_BUTTON_NETWORK, TRUE, &BUTTONS_network_process);
	LED_add(LED_ID_NETWORK, PIN_LED_NETWORK);
	state = INIT_BUTTON;

	initialized = TRUE;
}

void BUTTONS_process_main(void)
{
	button_event_e event;
	button_id_e button;
	BUTTONS_get_event(&event, &button);

	switch(state) {
		case INIT_BUTTON:
			state = IDLE_READING_BUTTON;	//Changement d'état
			break;

		case IDLE_READING_BUTTON:
			if(event == BUTTON_PRESS_EVENT)
			{
				entrance = TRUE;
				state = BUTTON_WAIT_FOR_LONG_PRESS;        				//le bouton est appuyé... on attend de voir si c'est un appui long ou court
				if(t_for_5_fast_press == 0)                				//si le temps est écoulé
				{
					nb_fast_press = 0;                    				//on démarre un nouveau comptage
					t_for_5_fast_press = FIVE_FAST_PRESS_DURATION;		//pour les 2 prochaines secondes
				}
				nb_fast_press++;
				if(nb_fast_press == 5)
				{
					nb_fast_press = 0;
					state = BUTTON_5_FAST_PRESS;            			//alors c'est l'événement que lon cherchait
				}
			}
			break;

		case BUTTON_WAIT_FOR_LONG_PRESS:
			if(entrance)
			{
				t_for_long_press = OFF_BUTTON_LONG_PRESS_DURATION;
				entrance = FALSE;
			}
			if(event == BUTTON_RELEASE_EVENT)
			{
				state = SIMPLE_PRESS;        //c'était un appui court !
			}
			else if(!t_for_long_press)
			{
				state = WAIT_RELEASE_BUTTON;    //c'était un appui long, le temps est écoulé !
			}
			break;

		case WAIT_RELEASE_BUTTON:
			if(event == BUTTON_RELEASE_EVENT)
			{
				nb_fast_press = 0;
				state = POWERDOWN;
			}
			break;

		case BUTTON_5_FAST_PRESS:
			//TODO BUTTON_5_FAST_PRESS

			state = IDLE_READING_BUTTON;
			break;

		case SIMPLE_PRESS:
			//TODO SIMPLE_PRESS

			LED_toggle(LED_ID_NETWORK);

			state = IDLE_READING_BUTTON;
			break;

		case POWERDOWN:
			//TODO POWERDOWN

			state = IDLE_READING_BUTTON;
			break;

		default:
			state = INIT_BUTTON;	//N'est jamais sensé se produire.
			break;
	}
}


void BUTTONS_add(button_id_e id, uint8_t pin, bool_e pullup, callback_fun_t callback)
{
	//configure la pin du bouton concernée en entrée
	//enregistre le bouton comme "initialisée"

	buttons[id].pin = pin;

	GPIO_init();
	//on part du principe que tout les boutons sont no pullup
	GPIO_configure(buttons[id].pin, (pullup)?NRF_GPIO_PIN_PULLUP:NRF_GPIO_PIN_NOPULL, 0);
	if(callback != NULL){
		buttons[id].callback = callback;
	}else {
		buttons[id].callback = NULL;
	}
	buttons[id].pullup = pullup;
	buttons[id].initialized = TRUE;
}


void BUTTONS_process_ms(void)
{
    if(t)
    {
    	t--;
    }

    if(t_for_5_fast_press)
    {
        t_for_5_fast_press--;
    }

    if(t_for_long_press)
    {
    	t_for_long_press--;
    }
}

void BUTTONS_get_event(button_event_e * event, button_id_e * button)
{
	static bool_e previous_states[BUTTON_NB] = {FALSE};

	if(!initialized)
		BUTTONS_init();
	*event = BUTTON_EVENT_NONE;
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
				bool_e current_state;
				current_state = BUTTONS_read(b);

				if(current_state && !previous_states[b])
				{
					*event = BUTTON_PRESS_EVENT;
					*button = b;
					stop_loop = TRUE;
				}
				else if(!current_state && previous_states[b])
				{
					*event = BUTTON_RELEASE_EVENT;
					*button = b;
					stop_loop = TRUE;
				}
				previous_states[b] = current_state;

				if(stop_loop)
					break;
			}
		}
	}
}

//renvoie vrai si le bouton est actuellement appuyé.
bool_e BUTTONS_read(button_id_e id){
	bool_e read = TRUE;
	read = GPIO_read(buttons[id].pin);
	if(buttons[id].pullup)
		read = !read;
	return read;
}

void BUTTONS_network_process(void)
{
	LED_toggle(LED_ID_NETWORK);
}

//fonction de test du bouton network
void BUTTONS_network_test(void){
	bool_e init = TRUE;
	if(init){
		BUTTONS_add(BUTTON_NETWORK, PIN_BUTTON_NETWORK, TRUE, &BUTTONS_network_process);
		LED_add(LED_ID_NETWORK, PIN_LED_NETWORK);
		init = FALSE;
	}
}









