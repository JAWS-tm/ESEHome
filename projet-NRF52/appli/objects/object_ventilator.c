/*
 * object_ventilator.c
 *
 *  Created on: 10 f�vr. 2021
 *      Author: Utilisateur
 */
#include "../config.h"


#if OBJECT_ID == OBJECT_VENTILATOR
#include "../common/gpio.h"
#include "nrf_gpio.h"
#include "nrf52.h"
#include "appli/common/buttons.h"
#include "object_ventilator.h"

static ventilator_e state = VENTILATOR_INIT;
static bool_e state_changement = FALSE;
void object_ventilator_changement_etat(void);

void object_ventilator_activation(void)
{
	switch(state) {
		case VENTILATOR_INIT:
			GPIO_init();
			GPIO_configure(MOSFET_PIN, NRF_GPIO_PIN_PULLUP, true);
			BUTTONS_add(BUTTON_NETWORK, PIN_BUTTON_NETWORK, TRUE, &object_ventilator_changement_etat, NULL, NULL, NULL);
			state = VENTILATOR_OFF;	//Changement d'�tat
			break;

		case VENTILATOR_ON:
			GPIO_write(MOSFET_PIN, true);

			if(state_changement)
			{
				state_changement = FALSE;
				state = VENTILATOR_OFF;	//Changement d'�tat
			}
			break;

		case VENTILATOR_OFF:
			GPIO_write(MOSFET_PIN, false);

			if(state_changement)
			{
				state_changement = FALSE;
				state = VENTILATOR_ON;	//Changement d'�tat
			}
			break;

		default:
			state = VENTILATOR_INIT;	//N'est jamais sens� se produire.
			break;
	}
	/*if(state == VENTILATOR_ON){
		GPIO_init();
		GPIO_configure(MOSFET_PIN, NRF_GPIO_PIN_PULLUP, true);
		GPIO_write(MOSFET_PIN, true); }
	else if (state == VENTILATOR_OFF){
		GPIO_write(MOSFET_PIN, false);
	}*/
}

void object_ventilator_changement_etat(void)
{

	state_changement = TRUE;
}


	//GPIO_write(MOSFET_PIN, false);

#endif


