/*
 * adc.h
 *
 *  Created on: 9 juin 2020
 *      Author: Nirgal
 */

#ifndef APPLI_ADC_H_
#define APPLI_ADC_H_
#include "../config.h"
	#if USE_ADC
	#include "modules/nrfx/drivers/include/nrfx_saadc.h"

		void ADC_init(void);
		void ADC_read_sensors(nrf_saadc_value_t * front, nrf_saadc_value_t * back);
		void ADC_read_button_off(nrf_saadc_value_t * value);
	#endif
#endif /* APPLI_ADC_H_ */
