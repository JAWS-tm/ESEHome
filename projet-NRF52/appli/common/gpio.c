/*
 * gpio.c
 *
 *  Created on: 13 janv. 2021
 *      Author: Nirgal
 */
#include "gpio.h"
#include "modules/nrfx/hal/nrf_gpio.h"
#include "nrf52.h"

void GPIO_init(void)
{
	//TODO !
}



void GPIO_configure_pins_9_and_10_as_gpio(void)
{
	if ((NRF_UICR->NFCPINS & UICR_NFCPINS_PROTECT_Msk) == (UICR_NFCPINS_PROTECT_NFC << UICR_NFCPINS_PROTECT_Pos)){
		NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Wen << NVMC_CONFIG_WEN_Pos;
		while (NRF_NVMC->READY == NVMC_READY_READY_Busy){}
		NRF_UICR->NFCPINS &= ~UICR_NFCPINS_PROTECT_Msk;
		while (NRF_NVMC->READY == NVMC_READY_READY_Busy){}
		NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Ren << NVMC_CONFIG_WEN_Pos;
		while (NRF_NVMC->READY == NVMC_READY_READY_Busy){}
		NVIC_SystemReset();
	}
}


