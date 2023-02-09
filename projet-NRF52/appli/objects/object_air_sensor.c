/*
 * object_air_sensor.c
 *
 *  Created on: 20 janv. 2022
 *      Author: maryquen
 */
#include "../config.h"

#if OBJECT_ID == OBJECT_AIR_SENSOR
	#include "../common/gpio.h"
	#include "../common/leds.h"
	#include "../common/buttons.h"
	#include "../common/systick.h"
	#include "object_air_sensor.h"
	#include "../common/parameters.h"




void write_led_status_on(void){
	LED_set(LED_ID_USER0, LED_MODE_ON);
}
void write_led_status_off(void){
	LED_set(LED_ID_USER0, LED_MODE_OFF);
}

void write_led_status_blink(void){
	LED_set(LED_ID_USER0, LED_MODE_FLASH);
}
void activate_boost(void){
	GPIO_write(BOOST_ENABLE, TRUE);
}
void desactivate_boost(void){
	GPIO_write(BOOST_ENABLE, FALSE);
}


void config_air_sensor(void){
	LED_add(LED_ID_USER0, LED_STATUS_SENSOR);
	GPIO_configure(BOOST_ENABLE, NRF_GPIO_PIN_NOPULL, TRUE);
}

#define BUFFER_SIZE	64

#define GET_DATA_PERIOD 16000 //en ms, durée de récupération des données
#define WAIT_BTW_GET_DATA_PERIOD 30000 //en ms, durée de la pause entre la récupération des données


static uint16_t write_index = 0;
static uint16_t read_index = 0;
static uint8_t buffer[BUFFER_SIZE];

bool check_begin = FALSE;
bool begin_process = FALSE;
static mode_rx mode_process_rx;
static uint8_t index;
static uint16_t sum;
static uint16_t checksum;
static uint16_t size;


static uint16_t data[32];

static uint16_t PM1_0;
static uint16_t PM2_5;
static uint16_t PM10;

static uint16_t particule_sup_0_3;
static uint16_t particule_sup_0_5;
static uint16_t particule_sup_1_0;
static uint16_t particule_sup_2_5;
static uint16_t particule_sup_5;
static uint16_t particule_sup_10;

static uint16_t count_PM1_0 = 0;
static uint16_t tab_PM1_0[(GET_DATA_PERIOD/1000)-1];
static uint16_t sum_PM1_0 = 0;
static uint16_t average_PM1_0 = 0;

static uint16_t count_PM2_5 = 0;
static uint16_t tab_PM2_5[(GET_DATA_PERIOD/1000)-1];
static uint16_t sum_PM2_5 = 0;
static uint16_t average_PM2_5 = 0;

static uint16_t count_PM10 = 0;
static uint16_t tab_PM10[(GET_DATA_PERIOD/1000)-1];
static uint16_t sum_PM10 = 0;
static uint16_t average_PM10 = 0;

static uint16_t count_data_management = 0;

static volatile uint32_t t = GET_DATA_PERIOD;


void process_ms(void)
{
	if(t)
		t--;
}

void Air_process_rx(uint8_t c){
	buffer[write_index] = c;
	if((write_index+1)%BUFFER_SIZE != read_index)
		write_index = (write_index+1)%BUFFER_SIZE;
}

void OBJECT_AIR_parse_frames(void)
{
	uint8_t c;
	while(read_index != write_index)
	{
		c = buffer[read_index];
		read_index = (read_index+1)%BUFFER_SIZE;

		//Nouvelle méthode
		//debug_printf("%02X ",c);
		if(c == 0x42){
			check_begin = TRUE;
		}
		if(c == 0x4D && check_begin == TRUE){
			index = 0;
			sum = 0x42+0x4D;
			mode_process_rx = WAIT_SIZE;
		}
		else{
			switch(mode_process_rx){
			case WAIT_SIZE:
				if(index == 0){
					size = (uint16_t)(c)<<8;
					sum += c;
					index++;
				}
				else if(index == 1){
					size |= c;
					index=0;
					sum+=c;
					mode_process_rx=WAIT_DATA;
					//debug_printf("Size trame : %X \n",size);
				}
			break;
			case WAIT_DATA:
				if(!(index%2)){
					data[index/2] =(uint16_t)(c)<<8;
				}
				else{
					data[index/2] |=c;
				}
				if(index < 64 - 1){
					index++;
				}
				if(index == size-2){
					mode_process_rx=CHECKSUM_HIGH;
				}
				sum+=c;
			break;
			case CHECKSUM_HIGH:
				checksum = (uint16_t)(c)<<8;
				//debug_printf("\nje suis dans check_sum high\n");
				mode_process_rx = CHECKSUM_LOW;
			break;
			case CHECKSUM_LOW:
				//debug_printf("je suis dans check_sum low\n");
				checksum |= c;
				if(sum == checksum){
					debug_printf("OK\n");
					frame_management(data,(size-2)/2);
					debug_printf("PM1.0 : %d\n",PM1_0);
					debug_printf("PM2.5 : %d\n",PM2_5);
					debug_printf("PM10 : %d\n",PM10);
					//Affichage de la trame data pour debug
					/*for(uint8_t i=0; i<((size-2)/2); i++){
						debug_printf("%02X ",data[i]);
					}*/
					//debug_printf("PM1.0 : %X\n",data[0]);
				}
				else
				{
					debug_printf("Sum=%d != %d\n", sum, checksum);
				}
				mode_process_rx = WAIT_NEXT_FRAME;
			break;
			case WAIT_NEXT_FRAME:
				//rien

				break;
			}
		}
	}
}

void frame_management(uint16_t * data, uint16_t size){
	//Permet de print toutes les datas à exploiter selon les envies
	/*for(uint16_t i=0; i<size; i++){
		debug_printf("%02X ",data[i]);
	}*/
	PM1_0 = data[0];
	PM2_5 = data[1];
	PM10 = data[2];

	particule_sup_0_3 = data[6];
	particule_sup_0_5 = data[7];
	particule_sup_1_0 = data[8];
	particule_sup_2_5 = data[9];
	particule_sup_5 = data[10];
	particule_sup_10 = data[11];


	//Ajout dans le tableau des valeurs de PM1_0
	tab_PM1_0[count_PM1_0] = PM1_0;
	count_PM1_0++;

	tab_PM2_5[count_PM2_5] = PM2_5;
	count_PM2_5++;

	tab_PM10[count_PM10] = PM10;
	count_PM10++;

	//Fonctionne pour choisir une data en particulier
	//debug_printf("PM1.0 : %X\n",data[0]);
}

void data_management(uint16_t count_PM, uint16_t * tab_PM, uint16_t average_PM, uint16_t sum_PM){

	//debug_printf("%d : nb compté\n",count_PM);

	for(uint16_t i=0; i<count_PM; i++){
		//debug_printf("%d ",tab_PM[i]);
		sum_PM = sum_PM + tab_PM[i];
	}
	average_PM = sum_PM / count_PM;

//	debug_printf("Somme : %d\n",sum_PM);
//	debug_printf("Moyenne de PM : %d\n\n",average_PM);
	if(count_data_management == 0){
		average_PM1_0 = average_PM;
		count_data_management++;
	}
	else if(count_data_management == 1){
		average_PM2_5 = average_PM;
		count_data_management++;
	}
	else if (count_data_management == 2){
		average_PM10 = average_PM;
		count_data_management = 0;
	}


}
void OBJECT_AIR_SENSOR_state_machine(void){
	static mode_e mode_state = INIT;

	//on consomme les octets reçus.
	OBJECT_AIR_parse_frames();

	switch(mode_state){

		case INIT:
			config_air_sensor();
			Systick_add_callback_function(&process_ms);

			PARAMETERS_init();
			PARAMETERS_enable(PARAM_MY_BASE_STATION_ID, 0, false, NULL,NULL);
			PARAMETERS_enable(PARAM_PM1_0, 0,false, NULL, NULL);
			PARAMETERS_enable(PARAM_PM2_5, 0,false, NULL, NULL);
			PARAMETERS_enable(PARAM_PM10, 0,false, NULL, NULL);
			//PARAMETERS_enable(PARAM_ACTUATOR_STATE, 0,false, NULL, NULL);
			PARAMETERS_enable(PARAM_REFRESH_PERIOD,30000,false,NULL,NULL);

			mode_state = GET_DATA;
			break;

		case GET_DATA:
			//debug_printf("%d ",t);
			if(t){
				activate_boost();
				write_led_status_on();
				SERIAL_DIALOG_set_rx_callback(&Air_process_rx);
			}
			if(!t){
				data_management(count_PM1_0, tab_PM1_0, average_PM1_0, sum_PM1_0);
				debug_printf("Moyenne de PM1_0 : %d\n\n",average_PM1_0);
				PARAMETERS_update(PARAM_PM1_0, average_PM1_0);

				data_management(count_PM2_5, tab_PM2_5, average_PM2_5, sum_PM2_5);
				debug_printf("Moyenne de PM2_5 : %d\n\n",average_PM2_5);
				PARAMETERS_update(PARAM_PM2_5, average_PM2_5);

				data_management(count_PM10, tab_PM10, average_PM10, sum_PM10);
				debug_printf("Moyenne de PM10 : %d\n\n",average_PM10);
				PARAMETERS_update(PARAM_PM10, average_PM10);

				average_PM1_0 = 0;
				sum_PM1_0 = 0;
				count_PM1_0 = 0;

				average_PM2_5 = 0;
				sum_PM2_5 = 0;
				count_PM2_5 = 0;

				average_PM10 = 0;
				sum_PM10 = 0;
				count_PM10 = 0;

				desactivate_boost();
				write_led_status_off();

				mode_state = SEND_DATA;
			}
			break;

		case SEND_DATA:
			PARAMETERS_send_param32_to_basestation(PARAM_PM1_0);
			PARAMETERS_send_param32_to_basestation(PARAM_PM2_5);
			PARAMETERS_send_param32_to_basestation(PARAM_PM10);
			PARAMETERS_send_param32_to_basestation(PARAM_REFRESH_PERIOD);
			mode_state = WAIT;
			break;

		case WAIT:
			debug_printf("Je suis dans le wait de %d ms",WAIT_BTW_GET_DATA_PERIOD);
			SYSTICK_delay_ms(WAIT_BTW_GET_DATA_PERIOD);
			t = GET_DATA_PERIOD;
			mode_state = GET_DATA;
			break;

	}
}
#endif


