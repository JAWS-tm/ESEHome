/*
 * object_fall_sensor.c
 *
 *  Created on: 2 f�vr. 2021
 *      Author: norab
 */
#include "../config.h"
#include "object_fall_sensor.h"
#include "bsp/mpu6050.h"
#include "appli/common/systick.h"
#include "appli/common/buttons.h"
#include "appli/common/leds.h"

#if OBJECT_ID == OBJECT_FALL_SENSOR
static MPU6050_t mpu_datas;

typedef enum{
	INIT,
	GET_DATA,
	ALERT,
	SLEEP,
	STOP
}state_e;

static volatile uint32_t t = 0;
void process_ms(void)
{
	if(t)
		t--;
}

void OBJECT_FALL_SENSOR_state_machine(void){

	static state_e state = INIT;
    LEDS_init(I_HAVE_LED_BATTERY);
	switch(state)
	{
		case INIT:{
			MPU6050_Init(&mpu_datas, MPU6050_Accelerometer_4G, MPU6050_Gyroscope_1000s);
			Systick_add_callback_function(&process_ms);
			LED_set(LED_ID_NETWORK, LED_MODE_OFF);
			LED_set(LED_ID_BATTERY, LED_MODE_OFF);
			state = GET_DATA;
			break;}

		case GET_DATA:{
			int32_t gyro_x = 0;
			int32_t gyro_y = 0;
			int32_t gyro_z = 0;
			int32_t acc_y = 0;
			int32_t acc_z = 0;
			debug_printf("MPU6050 Datas\n");

			MPU6050_ReadAllType1(&mpu_datas);
			gyro_x += mpu_datas.Gyroscope_X;
			gyro_y += mpu_datas.Gyroscope_Y;
			gyro_z += mpu_datas.Gyroscope_Z;
			acc_y = mpu_datas.Accelerometer_Y;
			acc_z = mpu_datas.Accelerometer_Z;
			debug_printf("AX%4d\tAY%4d\tAZ%4d\tGX%4d\tGY%4d\tGZ%4d\tgx%4ld�\tgy%4ld�\tgz%4ld�\tT%3.1f�\n",
							mpu_datas.Accelerometer_X/410,	//environ en %
							mpu_datas.Accelerometer_Y/410,	//environ en %
							mpu_datas.Accelerometer_Z/410,	//environ en %
							mpu_datas.Gyroscope_X,
							mpu_datas.Gyroscope_Y,
							mpu_datas.Gyroscope_Z,
							gyro_x/16400,						//environ en �
							gyro_y/16400,						//environ en �
							gyro_z/16400,						//environ en �
							mpu_datas.Temperature);

			LED_set(LED_ID_BATTERY, LED_MODE_OFF);

			if (acc_y > -20){
				if (acc_z < -10 || acc_z > 10){
					state = ALERT;
				}
			}

			break;}
		case ALERT:{
			debug_printf("ALERT\n");
			LED_set(LED_ID_BATTERY, LED_MODE_ON);
			//BUTTONS_alerte();
			SYSTICK_delay_ms(3000);
			state = GET_DATA;

			break;}

		case SLEEP:
			break;
		case STOP:
			break;
		default:
			break;
	}
}


void BUTTON_action_sleep(state_e state)
{
	if(state == GET_DATA){
		state = SLEEP;
	}else if (state == SLEEP){
		state = GET_DATA;
	}
}

//fonction du bouton ALERTE
void BUTTONS_alerte(void){
	bool_e init = TRUE;
	if(init){
		BUTTONS_add(BUTTON_ALERTE, PIN_BUTTON_ALERTE, TRUE, &BUTTONS_alerte_process);
		LED_add(LED_ID_BATTERY, PIN_LED_BATTERY);
		init = FALSE;
	}
}

//action a effectuer dans fonction btn alerte
void BUTTONS_alerte_process(void)
{
	LED_set(LED_ID_BATTERY, LED_MODE_ON);
	debug_printf("ALERT ! FALL DETECTED.");
}

#endif
