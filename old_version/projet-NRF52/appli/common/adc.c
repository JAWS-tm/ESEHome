/*
 * adc.c
 *
 *  Created on: 9 juin 2020
 *      Author: Nirgal
 */

#include "adc.h"

#if USE_ADC

//TODO généraliser pour tout les canaux...


static nrfx_saadc_config_t adc_config;
static nrf_saadc_channel_config_t adc_channel_1;
static nrf_saadc_channel_config_t adc_channel_2;
static nrf_saadc_channel_config_t adc_channel_3;
static bool_e adc_initialized = FALSE;


void ADC_init(void)
{
	adc_config = (nrfx_saadc_config_t)NRFX_SAADC_DEFAULT_CONFIG;
	adc_channel_1 = (nrf_saadc_channel_config_t)NRFX_SAADC_DEFAULT_CHANNEL_CONFIG_SE(NRF_SAADC_INPUT_AIN1);	//P0.03 -> AN1
	adc_channel_2 = (nrf_saadc_channel_config_t)NRFX_SAADC_DEFAULT_CHANNEL_CONFIG_SE(NRF_SAADC_INPUT_AIN2);	//P0.04 -> AN2
	adc_channel_3 = (nrf_saadc_channel_config_t)NRFX_SAADC_DEFAULT_CHANNEL_CONFIG_SE(NRF_SAADC_INPUT_AIN3);	//P0.05 -> AN3

	adc_channel_1.acq_time = SAADC_CH_CONFIG_TACQ_40us;
	adc_channel_2.acq_time = SAADC_CH_CONFIG_TACQ_40us;
	adc_channel_3.acq_time = SAADC_CH_CONFIG_TACQ_40us;

	nrfx_saadc_init(&adc_config, NULL);
	nrfx_saadc_channel_init(0, &adc_channel_1);
	nrfx_saadc_channel_init(1, &adc_channel_2);
	nrfx_saadc_channel_init(2, &adc_channel_3);

	adc_initialized = TRUE;
}

void ADC_read(uint8_t channel, nrf_saadc_value_t * value)
{
	if(!adc_initialized)
		ADC_init();
	nrfx_saadc_sample_convert(channel, value);
}

#endif

