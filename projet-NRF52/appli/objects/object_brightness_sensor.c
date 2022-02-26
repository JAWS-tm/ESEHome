/*
 * object_brightness_sensor.c
 *
 *  Created on: 26 février 2022
 *      Author: hugo morin
 */
 
#include "../config.h"

#if OBJECT_ID == OBJECT_BRIGHTNESS_SENSOR

#include "object_brightness_sensor.h"
#include "../../bsp/bh1750fvi.h"
#include "../common/leds.h"
#include "../common/buttons.h"
#include "../common/gpio.h"
#include "../common/systick.h"
#include "../common/parameters.h"

#define FAIBLE 50
#define FORT 500

static uint16_t luminosity = 0;
static uint16_t previous_luminosity = 0;
static bool boolean_btn_switch_ = FALSE;
static bool boolean_btn_sleep_ = FALSE;
static uint16_t save_state;

void OBJECT_BRIGHTNESS_SENSOR_MAIN(void)
{
	typedef enum{
		INIT,
		CONTINUOUS_MEASURE,
		SINGLE_MEASURE,
		SLEEP
	}state_e;

	static state_e state = INIT;

	switch(state){
	case INIT:
		//Initialisation
		BH1750FVI_init();
		PARAMETERS_init();
		PARAMETERS_enable(PARAM_BRIGHTNESS,0,FALSE,NULL,NULL);

		//Initialisation des LED
		LED_add(LED_ID_BATTERY, PIN_LED_BATTERY);
		LED_add(LED_ID_NETWORK, PIN_LED_NETWORK);

		GPIO_configure(BH1750FVI_VCC_PIN, GPIO_PIN_CNF_PULL_Pullup, TRUE);
		GPIO_write(BH1750FVI_VCC_PIN, TRUE);

		//Initialisation du bouton
		BUTTONS_add(BUTTON_NETWORK, PIN_BUTTON_NETWORK, TRUE,&btn_switch_measure_mode, NULL,&btn_sleep, NULL);


		state = CONTINUOUS_MEASURE;

		break;
		
	case CONTINUOUS_MEASURE:

		led_lighting_status(1);

		BH1750FVI_powerOn();
		BH1750FVI_measureMode(BH1750FVI_CON_H1); //BH1750FVI_CON_L

		while(1){
			previous_luminosity = luminosity;
			luminosity = BH1750FVI_readLuminosity();
			luminosity_observation(luminosity,previous_luminosity);
			PARAMETERS_update(PARAM_BRIGHTNESS, luminosity);

			SYSTICK_delay_ms(120);

			if(boolean_btn_switch_){
				BH1750FVI_powerDown();
				state = SINGLE_MEASURE;
			}
			else if(boolean_btn_sleep_){
				BH1750FVI_powerDown();
				save_state = 1;
				state = SLEEP;
			}

		}

		break;
		
	case SINGLE_MEASURE:

		led_lighting_status(2);

		BH1750FVI_powerOn();
		BH1750FVI_measureMode(BH1750FVI_OT_H1); // BH1750FVI_OT_L

		luminosity = BH1750FVI_readLuminosity();
		debug_printf("\n La luminosite est de %d lx.", luminosity);
		PARAMETERS_update(PARAM_BRIGHTNESS, luminosity);
		// En simple mesure le BH1750FVI se met automatiquement en powerDown après une mesure
		if(boolean_btn_switch_){
			state = CONTINUOUS_MEASURE;
		}
		else if(boolean_btn_sleep_){
			save_state = 2;
			state = SLEEP;
		}
		else{
			save_state = 2;
			state = SLEEP;
		}

		break;
	case SLEEP:
		led_lighting_status(0);

		if(boolean_btn_sleep_){
			if(save_state == 1){
				state = CONTINUOUS_MEASURE;
			}
			else if(save_state == 2){
				state = SINGLE_MEASURE;
			}
		}
		break;
	default:
		break;
	}

}

void luminosity_observation(uint16_t lux, uint16_t p_lux){
	if (lux < FAIBLE){
		debug_printf("\n LUMINOSITE FAIBLE");
	}
	else if( lux>FAIBLE && lux<FORT){
		debug_printf("\n LUMINOSITE MOYENNE");
	}
	else if(lux > FORT){
		debug_printf("\n LUMINOSITE FORTE");
	}

	if (lux > p_lux + 10){
		debug_printf("\n La luminosite à AUGMENTER  (%d lx).", lux);

	}
	else if(lux < p_lux + 10){
		debug_printf("\n La luminosite à DIMINUER (%d lx).", lux);
	}
	else{
		debug_printf("\n La luminosite est CONSTANTE (%d lx).", lux);
	}
}

void led_lighting_status(uint16_t nb_led_set){
	if(nb_led_set == 0){ // SLEEP
		LED_set(LED_ID_NETWORK, LED_MODE_OFF);
		LED_set(LED_ID_BATTERY, LED_MODE_BLINK);
	}
	else if(nb_led_set == 1){ // CONTINUOUS_MEASURE
		LED_set(LED_ID_NETWORK, LED_MODE_ON);
		LED_set(LED_ID_BATTERY, LED_MODE_OFF);
	}
	else if(nb_led_set == 2){ // SINGLE_MEASURE
		LED_set(LED_ID_NETWORK, LED_MODE_BLINK);
		LED_set(LED_ID_BATTERY, LED_MODE_OFF);
	}
	else{
		debug_printf("\n Erreur LED !");
	}
}

void btn_switch_measure_mode(void){
	boolean_btn_switch_ = TRUE;
}
void btn_sleep(void){
	boolean_btn_sleep_ = TRUE;
}

#endif
