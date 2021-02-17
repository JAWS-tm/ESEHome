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




#if OBJECT_ID == OBJECT_VENTILATOR

void object_ventilator_activation(void)
{
	GPIO_init();
	GPIO_configure(MOSFET_PIN, NRF_GPIO_PIN_PULLUP, true);
	GPIO_write(MOSFET_PIN, true);





}

#endif


