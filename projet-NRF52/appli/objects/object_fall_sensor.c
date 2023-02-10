/*
 * object_fall_sensor.c
 *
 *  Created on: 2 févr. 2021
 *      Author: norab
 *  Modified on: 24 janv. 2022
 *  	By: JosMl
 */

#include "../config.h"
#include "object_fall_sensor.h"
#include "bsp/mpu6050.h"
#include "appli/common/gpio.h"
#include "appli/common/systick.h"
#include "appli/common/buttons.h"
#include "appli/common/leds.h"
#include "appli/common/parameters.h"
#include "../bsp/morse.h"

#if OBJECT_ID == OBJECT_FALL_SENSOR

static MPU6050_t mpu_datas;
static led_id_e led_alert_id = LED_ID_USER0;
static bool flag_bt_alert_SP = FALSE;
static bool flag_bt_alert_LP = FALSE;
static bool flag_reset_morse = FALSE;
static int32_t threshold_frome_bs;

typedef enum{
	INIT,
	GET_DATA,
	ALERT,
	SEND_ALERT,
	FALSE_ALERT
}state_e;

static volatile uint32_t t = 0;
static volatile uint32_t t_sos = 0;

void FALL_SENSOR_process_ms(void)
{
	if(t_sos){
		t_sos --;
	}
	if(t)
		t--;
}
/*
 * @author	JosMl
 * @date 24 jan 2022
 *
 * @brief	Machine à état de l'objet fall sensor.
 * @case INIT	Initialisation du capteur, des boutons et des sorties
 * @case GET_DATA Attente d'une donnée s'apparentant à une chute ou d'un appuie court pour déclencher une alerte
 * @case ALERT Allumage du buzzer et de la LED alerte
 * @case FALSE_ALERT lorsque le bouton alerte est pressé de façon longue, l'alerte est annulée, le buzzer et la led s'éteignent
 *
 */
void OBJECT_FALL_SENSOR_state_machine(void){
	static state_e state = INIT;
	static state_e previous_state = INIT;
	bool_e entrance = (state != previous_state);
	previous_state = state;
	debug_printf("Initialisation\n");
	switch(state)
	{
	case INIT:
		debug_printf("Case INIT\n");
		Systick_add_callback_function(&FALL_SENSOR_process_ms);
		debug_printf("BUTTONS_add\n");
		BUTTONS_add(BUTTON_ALERT,PIN_BUTTON_ALERT,TRUE,&cb_bt_alert_short_press_event,NULL,&cb_bt_alert_long_press_event,NULL,NULL); //Initialisation du bouton alerte
		debug_printf("LED_add\n");
		LED_add(led_alert_id,PIN_LED_ALERT);
		debug_printf("GPIO_configure\n");
		GPIO_configure(PIN_BUZZER,NRF_GPIO_PIN_NOPULL,TRUE);
		debug_printf("MPU_Init\n");
		MPU6050_Init(&mpu_datas, MPU6050_Accelerometer_4G, MPU6050_Gyroscope_1000s);
		debug_printf("Parameter_init\n");
		PARAMETERS_init(); //Initialisation de la communication RF
		debug_printf("Parameter enable\n");
		PARAMETERS_enable(PARAM_SENSOR_VALUE, 0, FALSE, NULL, NULL); //Initialisation du paramètre de l'état de l'alarme
		PARAMETERS_enable(PARAM_ALARM_TRESHOLD, 0, FALSE, NULL, NULL); // Initialisation du paramètre de seuil de détection de l'accéleromètre
		state = GET_DATA;
		break;
	case GET_DATA:{
		debug_printf("Case GET DATA\n");
		if(entrance){
			debug_printf("Parameters_send_param32_to_basestation");
			PARAMETERS_send_param32_to_basestation(PARAM_SENSOR_VALUE); // envoie de la valeur du capteur à 0
		}
		flag_bt_alert_LP = FALSE;
		debug_printf("PARAMETERS_get\n");
		getMPU6050_Datas(); //aide au debug pour afficher les valeurs du MPU6050
		threshold_frome_bs = PARAMETERS_get(PARAM_ALARM_TRESHOLD);


		int16_t gyro_x = 0;
		int16_t gyro_y = 0;
		int16_t gyro_z = 0;
		int16_t acc_x = 0;
		int16_t acc_y = 0;
		int16_t acc_z = 0;

		MPU6050_ReadAllType1(&mpu_datas);
		gyro_x += mpu_datas.Gyroscope_X;
		gyro_y += mpu_datas.Gyroscope_Y;
		gyro_z += mpu_datas.Gyroscope_Z;
		acc_x = mpu_datas.Accelerometer_X/410; //-> en pourcentage
		acc_y = mpu_datas.Accelerometer_Y/410; // -> en pourcentage
		acc_z = mpu_datas.Accelerometer_Z/410; // -> en pourcentage

		//debug_printf("AX%4d\tAY%4d\tAZ%4d\tGX%4d\tGY%4d\tGZ%4d\n",acc_x,acc_y,acc_z,gyro_x,gyro_y,gyro_z);
		if(acc_z < -15 || flag_bt_alert_LP || acc_z < threshold_frome_bs){
			state = ALERT;
		}
		}break;
	case ALERT :
		debug_printf("Case ALERT\n");
		if(entrance){
			flag_bt_alert_SP = FALSE;
			flag_reset_morse = TRUE;
			t = 8900;
			t_sos = 10000;
		}

		if(t){
			MORSE_state_machine_process_ms("SOS",flag_reset_morse);
			if(flag_reset_morse){
				flag_reset_morse = FALSE;
			}
		} else {
			t = 13500;
		}

		if(!t_sos){
			state = SEND_ALERT;
		}

		if(flag_bt_alert_SP){
			state = FALSE_ALERT;
		}
		break;
	case FALSE_ALERT :
		debug_printf("Case FALSE ALERT\n");
		PARAMETERS_update(PARAM_SENSOR_VALUE, 0);
		flag_bt_alert_LP = FALSE;
		LED_set(led_alert_id,LED_MODE_OFF);
		GPIO_write(PIN_BUZZER,FALSE);
		state = GET_DATA;
		break;
	case SEND_ALERT :
		debug_printf("Case SEND ALERT\n");
		PARAMETERS_update(PARAM_SENSOR_VALUE, 1);
		PARAMETERS_send_param32_to_basestation(PARAM_SENSOR_VALUE); // envoie de la valeur du capteur à 1
		state = ALERT;
		break;
	default:
		break;
	}
}

/*+
 * @author	Montreuil Joshua
 * @date 24 jan 2022
 *
 * @brief	Machine à état du capteur MPU6050, afin de tester la récupération des données pour les afficher avec l'UART.
 * @case INIT	Initialisation du capteur
 * @case GET_MPU Récupération et affichage des valeurs envoyées par le MPU
 *
 */
void getMPU6050_Datas(void){
	MPU6050_t datas;
	int16_t gyro_x_test = 0;
	int16_t gyro_y_test = 0;
	int16_t gyro_z_test = 0;
	int16_t acc_x_test = 0;
	int16_t acc_y_test = 0;
	int16_t acc_z_test = 0;

	typedef enum{
		INIT,
		GET_MPU
	}debug_state_e;

	static debug_state_e debug_state = INIT;

	switch(debug_state)
	{
		case INIT :{
			MPU6050_Init(&datas, MPU6050_Accelerometer_4G, MPU6050_Gyroscope_1000s);
			debug_state = GET_MPU;
			break;
		}case GET_MPU:{
			MPU6050_ReadAllType1(&datas);
			gyro_x_test += datas.Gyroscope_X;
			gyro_y_test += datas.Gyroscope_Y;
			gyro_z_test += datas.Gyroscope_Z;
			acc_x_test = datas.Accelerometer_X/410; //-> en pourcentage
			acc_y_test = datas.Accelerometer_Y/410; // -> en pourcentage
			acc_z_test = datas.Accelerometer_Z/410; // -> en pourcentage
			debug_printf("AX%4d\tAY%4d\tAZ%4d\tGX%4d\tGY%4d\tGZ%4d\n",acc_x_test,acc_y_test,acc_z_test,gyro_x_test,gyro_y_test,gyro_z_test);
			break;
		}default:
			debug_state = INIT;
			break;
	}
}

/*
 * @author	Montreuil Joshua
 * @date 02 fevr 2022
 *
 * @brief	Fonction permettant la génération du code S.O.S. en Morse.
 *
 */
void buzz(bool_e state){
	if(state){
		LED_set(led_alert_id,LED_MODE_ON);
		GPIO_write(PIN_BUZZER,TRUE);
	}else{
		LED_set(led_alert_id,LED_MODE_OFF);
		GPIO_write(PIN_BUZZER,FALSE);
	}
}

void cb_bt_alert_short_press_event(void){
	flag_bt_alert_SP = TRUE;
}
void cb_bt_alert_long_press_event(void){
	flag_bt_alert_LP = TRUE;
}

void init_for_demo(void){
	BUTTONS_add(BUTTON_ALERT,PIN_BUTTON_ALERT,TRUE,&cb_bt_alert_short_press_event,NULL,&cb_bt_alert_long_press_event,NULL, NULL); //Initialisation du bouton alerte
	LED_add(led_alert_id,PIN_LED_ALERT);
}

#endif
