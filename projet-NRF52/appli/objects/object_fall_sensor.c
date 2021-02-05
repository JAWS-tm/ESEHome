/*
 * object_fall_sensor.c
 *
 *  Created on: 2 févr. 2021
 *      Author: norab
 */
#include "../config.h"
#include "object_fall_sensor.h"
#include "bsp/mpu6050.h"
#include "appli/common/systick.h"

#if OBJECT_ID == OBJECT_FALL_SENSOR
static MPU6050_t mpu_datas;

static volatile uint32_t t = 0;
void process_ms(void)
{
	if(t)
		t--;
}


void OBJECT_FALL_SENSOR_state_machine(void){
	typedef enum{
		INIT,
		GET_DATA,
		ALERT,
		SLEEP,
		STOP
	}state_e;
	static state_e state = INIT;
	switch(state)
	{
		case INIT:
			MPU6050_Init(&mpu_datas, MPU6050_Accelerometer_4G, MPU6050_Gyroscope_1000s);
			Systick_add_callback_function(&process_ms);
			state = GET_DATA;
			break;
		case GET_DATA:
			if(!t)
			{
				t = 100;
				MPU6050_ReadAllType1(&mpu_datas);
			}
			break;
		default:
			break;
	}
}









#endif


