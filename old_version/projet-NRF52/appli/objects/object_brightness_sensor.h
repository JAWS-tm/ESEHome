/*
 * object_brightness_sensor.h
 *
 *  Created on: 2 février 2022
 *      Author: hugo morin
 */

#ifndef APPLI_OBJECTS_OBJECT_BRIGHTNESS_SENSOR_H_
#define APPLI_OBJECTS_OBJECT_BRIGHTNESS_SENSOR_H_

#include "../config.h"

#if OBJECT_ID == OBJECT_BRIGHTNESS_SENSOR

	void OBJECT_BRIGHTNESS_SENSOR_MAIN();

	void luminosity_observation(uint16_t lux, uint16_t p_lux);
	void led_lighting_status(uint16_t nb_led_set);
	void btn_switch_measure_mode();
	void btn_sleep();

#endif

#endif /* APPLI_OBJECTS_OBJECT_BRIGHTNESS_SENSOR_H_ */
