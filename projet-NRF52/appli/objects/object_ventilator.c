/*
 * object_ventilator.c
 *
 *  Created on: 10 févr. 2021
 *      Author: Utilisateur
 */
#include "../config.h"
#include "../common/gpio.h"
#include "nrf_gpio.h"
#include "nrf52.h"
#include "object_ventilator.h"

static ventilator_e state = VENTILATOR_INIT;
static bool_e state_changement = FALSE;

#if OBJECT_ID == OBJECT_VENTILATOR

void object_ventilator_activation(void)
{
	switch(state) {
	case VENTILATOR_INIT:
		GPIO_init();
		GPIO_configure(MOSFET_PIN, NRF_GPIO_PIN_PULLUP, true);

		state = VENTILATOR_OFF;	//Changement d'état
		break;

		case VENTILATOR_ON:
			GPIO_write(MOSFET_PIN, true);

			if(state_changement)
			{
				state_changement = FALSE;
				state = VENTILATOR_OFF;	//Changement d'état
			}
			break;

		case VENTILATOR_OFF:
			GPIO_write(MOSFET_PIN, false);

			if(state_changement)
			{
				state_changement = FALSE;
				state = VENTILATOR_ON;	//Changement d'état
			}
			break;

		default:
			state = VENTILATOR_INIT;	//N'est jamais sensé se produire.
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


