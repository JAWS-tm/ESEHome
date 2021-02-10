/*
 * battery.c
 *
 *  Created on: 9 févr. 2021
 *      Author: norab
 */

#include "adc.h"
#include "battery.h"
#include "nrfx_saadc.h"

static nrfx_saadc_config_t adc_config;
static nrf_saadc_channel_config_t channel_battery;
static bool_e adc_initialized = FALSE;

void MEASURE_VBAT_init(uint8_t pin)
{
	adc_config = (nrfx_saadc_config_t)NRFX_SAADC_DEFAULT_CONFIG;
	channel_battery = (nrf_saadc_channel_config_t)NRFX_SAADC_DEFAULT_CHANNEL_CONFIG_SE(pin);
	channel_battery.acq_time = SAADC_CH_CONFIG_TACQ_40us;
	nrfx_saadc_init(&adc_config, NULL);
	nrfx_saadc_channel_init(0, &channel_battery);
	adc_initialized = TRUE;
}

/*uint16_t MEASURE_VBAT_get(uint8_t pin){
	uint8_t Vbat_mv = ADC_getValue(pin);
}*/
