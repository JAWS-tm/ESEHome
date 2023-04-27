/*
 * object_air_sensor.c
 *
 *  Created on: 20 janv. 2022
 *      Author: maryquen
 */

#ifndef OBJECT_AIR_SENSOR_H
#define OBJECT_AIR_SENSOR_H
#include "../config.h"

typedef enum{
		INIT,
		GET_DATA,
		SEND_DATA,
		WAIT
	}mode_e;

typedef enum{
	WAIT_SIZE,
	WAIT_DATA,
	CHECKSUM_HIGH,
	CHECKSUM_LOW,
	WAIT_NEXT_FRAME
}mode_rx;

void config_air_sensor(void);
void OBJECT_AIR_SENSOR_state_machine(void);
void write_led_status_on(void);
void write_led_status_off(void);
void write_led_status_blink(void);
//void activate_sensor(void);
void activate_boost(void);
void desactivate_boost(void);
void data_management(uint16_t count_PM, uint16_t * tab_PM, uint16_t average_PM, uint16_t sum_PM);
void frame_management(uint16_t * data,uint16_t size);

#endif /* OBJECT_AIR_SENSOR_H */
