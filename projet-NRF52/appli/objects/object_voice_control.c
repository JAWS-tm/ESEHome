/*
 * object_touch_screen.c
 *
 *  Created on: 6 févr. 2021
 *      Author: malaryth
 */

#include "../config.h"

#if OBJECT_ID == OBJECT_VOICE_CONTROL
	#include "../common/gpio.h"
	#include "object_voice_control.h"

	typedef struct
	{
		bool_e initialized;
		uint8_t pin;
	}voice_control_t;

	static voice_control_t voice_control_var[VOICE_CONTROL_NB];
	static voice_control_read_e state;

	bool_e LED = FALSE;
	bool_e touch_screen = FALSE;

	void VOICE_CONTROL_init(void)
	{
		for(voice_control_e b = 0; b < VOICE_CONTROL_NB; b++)
		{
			voice_control_var[b].initialized = TRUE;
		}

		state = INIT_VOICE_CONTROL;
	}

	void VOICE_CONTROL_process_main(void)
	{
		switch(state) {
			case INIT_VOICE_CONTROL:

				VOICE_CONTROL_init();

				VOICE_CONTROL_add(VOICE_CONTROL_COMMAND_1, LED_PIN, TRUE);
				VOICE_CONTROL_add(VOICE_CONTROL_COMMAND_2, TOUCH_SCREEN_PIN, TRUE);

				state = READ_COMMAND_1;	//Changement d'état
				break;

			case READ_COMMAND_1:
				LED = GPIO_read(voice_control_var[0].pin);

				state = READ_COMMAND_2;	//Changement d'état
				break;

			case READ_COMMAND_2:
				touch_screen = GPIO_read(voice_control_var[1].pin);

				state = READ_COMMAND_3;	//Changement d'état
				break;

			case READ_COMMAND_3:
				state = READ_COMMAND_4;	//Changement d'état
				break;

			case READ_COMMAND_4:
				state = READ_COMMAND_5;	//Changement d'état
				break;

			case READ_COMMAND_5:
				state = READ_COMMAND_6;	//Changement d'état
				break;

			case READ_COMMAND_6:
				state = READ_COMMAND_7;	//Changement d'état
				break;

			case READ_COMMAND_7:
				state = READ_COMMAND_8;	//Changement d'état
				break;

			case READ_COMMAND_8:
				state = READ_COMMAND_1;	//Changement d'état
				break;

			default:
				state = INIT_VOICE_CONTROL;	//N'est jamais sensé se produire.
				break;
		}
	}

	void VOICE_CONTROL_add(voice_control_e id, uint8_t pin, bool_e pullup)
	{
		//configure la pin du voice controller concernée en entrée
		//enregistre le pin voice controller comme "initialisée"

		voice_control_var[id].pin = pin;

		GPIO_init();
		//on part du principe que tout les boutons sont no pullup
		GPIO_configure(voice_control_var[id].pin, (pullup)?NRF_GPIO_PIN_PULLUP:NRF_GPIO_PIN_NOPULL, 0);
		voice_control_var[id].initialized = TRUE;
	}

#endif
