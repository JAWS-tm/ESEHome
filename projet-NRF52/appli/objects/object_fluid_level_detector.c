/*
 * object_fluid_level_detector.c
 *
 *  Created on: 1 févr. 2022
 *      Author: pcpcapi
 *
 *  Source file for a water tank level detector.
 *  The following code is to be used with the distance sensor Sensopart FT 92 ILA-PSL5 F 9x,
 *  which asks for a minimal distance of about 15 centimeters from the sensor's surface in order to get accurate results.
 */

#include "../config.h"

#if OBJECT_ID == OBJECT_WATER_LEVEL_DETECTOR

#include "object_fluid_level_detector.h"
#include "appli/common/adc.h"
#include "../main.h"
#include "appli/common/parameters.h"


/*Values relating to the sensor's (in this case, laser's) calibration.
 *In the following test case, the detected value ranges from 180 to 1000. The sensor is functional on a distance of up to 5 meters.
 *Thus, one obtains the following calibration rate : (1000 - 180) / 5000 (cm) = 0.164.
 */
#define CALIBRATION_MAX_VALUE 1000  //The maximum value of the detected value.
#define CALIBRATION_MIN_VALUE 180	//The minimum value of the detected value.
#define CALIBRATION_RATE 0.164		//The rate of influence of a centimeter's distance on the detected value.



/*Indicates the recipient's maximum liquid level in centimeters.
 *Must not exceed the maximum distance range of the sensor (in this case, 5000 cm).
 *Preferably, the recipient would be a perfect cylinder whose width is invariable all along its length/height.
 */
#define RECIPIENT_HEIGHT 570


static uint16_t detected_value; 	//The current value indicated by the sensor.
static uint16_t water_level;    	//The "distance" from the recipient's lowest level, or the current water level "height".
static int water_level_percentage;  //The percentage of the water level's height
static float WATER_VARIABILITY = RECIPIENT_HEIGHT * CALIBRATION_RATE; //Recipient's height translated to the sensor's calibration.
static float MIN_RECIPIENT = CALIBRATION_MAX_VALUE - (RECIPIENT_HEIGHT * CALIBRATION_RATE); //The minimum possible detected value, indicates an empty recipient.
static uint32_t alarm_threshold = 20;
static uint32_t

static volatile uint32_t t = 0;

void set_alarm_treshold(int32_t a) {

	alarm_threshold = a;

}

void detect_value() {

	ADC_read(PIN_CAPTEUR, &detected_value);

	//Detects the height of the current water level.
	water_level = detected_value - MIN_RECIPIENT;

	//Calculates the percentage of the recipient that is "occupied" by the current water level.
	water_level_percentage = (water_level * 100) / WATER_VARIABILITY;

	debug_printf("The water tank is filled %d percent of the way.\n", water_level_percentage);
}

void process_ms(void) {
   if(t)
	   t--;
}

void water_level_alarm(bool_e alarm_state) {

	PARAMETERS_update(PARAM_SENSOR_VALUE, water_level_percentage);
	PARAMETERS_send_param32_to_basestation(PARAM_SENSOR_VALUE);
}

void OBJECT_WATER_LEVEL_DETECTOR_MAIN(){

	typedef enum {

			INIT,
			DETECT_VALUE,
			ALARM
	    } state_e;

	static state_e state = INIT;
	static state_e previous_state = INIT;
	bool_e entrance = (state!=previous_state)?TRUE:FALSE;
	previous_state = state;

	switch(state) {

	case INIT:

		ADC_init();
		debug_printf("Pret\n");
		Systick_add_callback_function(&process_ms);
		PARAMETERS_enable(PARAM_ALARM_TRESHOLD, alarm_threshold, TRUE, &set_alarm_treshold, NULL);
		state = DETECT_VALUE;

		break;

	case DETECT_VALUE:
		if(entrance)
			water_level_alarm(FALSE);

		detected_value();

		water_level();

		if(water_level_percentage <= alarm_threshold  - TOLERANCE) {

			state = ALARM;
		}


		break;

	case ALARM:
		if(entrance)
			water_level_alarm(TRUE);

		detected_value();

		if(water_level_percentage > alarm_threshold + TOLERANCE) {

					state = DETECT_VALUE;
				}

		break;



	default:

		break;

	}
}

#endif
