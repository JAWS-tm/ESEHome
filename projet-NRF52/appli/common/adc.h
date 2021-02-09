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



		typedef enum{
		ADC_0 = 0,
		ADC_1,
		ADC_2,
		ADC_3,
		ADC_4,
		ADC_5,
		ADC_6,
		ADC_7,
		ADC_8,
		ADC_9,
		ADC_10,
		ADC_11,
		ADC_12,
		ADC_13,
		ADC_14,
		ADC_15,
		ADC_16,
		ADC_17,
		ADC_18,
		ADC_CHANNEL_NB
	}adc_id_e;

		void ADC_init(void);
		void ADC_read_sensors(nrf_saadc_value_t * front, nrf_saadc_value_t * back);
		void ADC_read_button_off(nrf_saadc_value_t * value);
		int16_t ADC_getValue(adc_id_e channel);
	#endif
#endif /* APPLI_ADC_H_ */
