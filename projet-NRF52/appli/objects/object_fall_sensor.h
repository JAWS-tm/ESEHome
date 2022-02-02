/*
 * object_fall_sensor.h
 *
 *  Created on:  févr. 2021
 *      Author: norab
 *  Modified on: 24 janv. 2022
 *  	By: JosMl
 */

#ifndef APPLI_OBJECTS_OBJECT_FALL_SENSOR_H_
#define APPLI_OBJECTS_OBJECT_FALL_SENSOR_H_

void OBJECT_FALL_SENSOR_state_machineTest(void);

void getMPU6050_Datas(void);
void cb_bt_alert_short_press_event(void);
void cb_bt_alert_long_press_event(void);


#endif /* APPLI_OBJECTS_OBJECT_FALL_SENSOR_H_ */
