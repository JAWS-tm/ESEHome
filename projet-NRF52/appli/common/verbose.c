/*
 * verbose.c
 *
 *  Created on: 8 févr. 2023
 *      Author: jules
 */

#include "../config.h"
#include "verbose.h"

#define MSG_BUFFER_SIZE 4

nrf_esb_payload_t received_messages_buffer[MSG_BUFFER_SIZE];
uint8_t buffer_index = 0;

char * VERBOSE_object_id_to_string(uint8_t id)
{
	char * ret = "unknown object";

	switch(id)
	{
		case OBJECT_BASE_STATION:		ret = "Base Station";		break;
		case OBJECT_SMART_LIGHT:		ret = "Smart Light";		break;
		case OBJECT_NIGHT_LIGHT:		ret = "Night Light";		break;
		case OBJECT_BRIGHTNESS_SENSOR:	ret = "Brightness Sensor";	break;
		case OBJECT_STATION_METEO_INT:	ret = "Station Meteo Int";	break;
		case OBJECT_OUT_WEATHER_STATION:ret = "Station Meteo Ext";	break;
		case OBJECT_ROLLER_SHUTTER:		ret = "Roller Shutter";		break;
		case OBJECT_ALARM:				ret = "Alarm";				break;
		case OBJECT_FIRE_DETECTOR:		ret = "Fire Detector";		break;
		case OBJECT_WINE_DEGUSTATION:	ret = "Wine Degustation";	break;
		case OBJECT_VENTILATOR:			ret = "Ventilator";			break;
		case OBJECT_GSM:				ret = "GSM";				break;
		case OBJECT_FALL_SENSOR:		ret = "Fall Sensor";		break;
		case OBJECT_WATER_LEVEL_DETECTOR: ret = "Water Level Detector"; break;
		case OBJECT_AIR_SENSOR:			ret = "Air Sensor";			break;
		case OBJECT_TRACKER_GPS:		ret = "Tracker GPS";		break;
		case OBJECT_VOICE_CONTROL:		ret = "Voice Control";		break;
		case OBJECT_TOUCH_SCREEN:		ret = "Touch Screen";		break;
		case OBJECT_E_PAPER:			ret = "E Paper";			break;
		case OBJECT_MATRIX_LEDS:		ret = "Matrix Leds";		break;
		case OBJECT_LCD_SLIDER:			ret = "LCD Slider";			break;
		case 0xFF:						ret = "BROADCAST";			break;
		default:
			break;
	}
	return ret;
}

char * VERBOSE_message_id_to_string(msg_id_e id)
{
	char * ret = "unknown message";

	switch(id)
	{
		case RECENT_RESET:				ret = "RECENT_RESET";			break;
		case ASK_FOR_SOFTWARE_RESET:	ret = "ASK_FOR_SOFTWARE_RESET";	break;
		case PING:						ret = "PING";					break;
		case PONG:						ret = "PONG";					break;
		case EVENT_OCCURED:				ret = "EVENT_OCCURED";			break;
		case PARAMETER_IS:				ret = "PARAMETER_IS";			break;
		case PARAMETER_ASK:				ret = "PARAMETER_ASK";			break;
		case PARAMETER_WRITE:			ret = "PARAMETER_WRITE";		break;
		case I_HAVE_NO_SERVER_ID:		ret = "I_HAVE_NO_SERVER_ID";	break;
		case YOUR_SERVER_ID_IS:			ret = "YOUR_SERVER_ID_IS";		break;
		default:
			break;
	}
	return ret;
}

char * VERBOSE_parameter_id_to_string(param_id_e id)
{
	char * ret = "unknown parameter";

	switch(id)
	{
		case PARAM_MY_BASE_STATION_ID:	ret = "PARAM_MY_BASE_STATION_ID";	break;
		case PARAM_ACTUATOR_STATE:		ret = "PARAM_ACTUATOR_STATE";		break;
		case PARAM_SENSOR_VALUE:		ret = "PARAM_SENSOR_VALUE";			break;
		case PARAM_ALARM_TRESHOLD:		ret = "PARAM_ALARM_TRESHOLD";		break;
		case PARAM_ALARM_WAY:			ret = "PARAM_ALARM_WAY";			break;
		case PARAM_TEMPERATURE:			ret = "PARAM_TEMPERATURE";			break;
		case PARAM_HYGROMETRY:			ret = "PARAM_HYGROMETRY";			break;
		case PARAM_COLOR:				ret = "PARAM_COLOR";				break;
		case PARAM_REFRESH_PERIOD:		ret = "PARAM_REFRESH_PERIOD";		break;
		case PARAM_PRESSURE:			ret = "PARAM_PRESSURE";				break;
		case PARAM_BRIGHTNESS:			ret = "PARAM_BRIGHTNESS";			break;
		case PARAM_WINDSPEED:			ret = "PARAM_WINDSPEED";			break;
		case PARAM_PLUVIOMETRY:			ret = "PARAM_PLUVIOMETRY";			break;
		case PARAM_SCREEN_COLOR: 		ret = "PARAM_SCREEN_COLOR"; 		break;
		case PARAM_MODE:				ret = "PARAM_MODE";					break;
		case PARAM_DURATION:			ret = "PARAM_DURATION";				break;
		case PARAM_START_TIME:			ret = "PARAM_START_TIME";			break;
		case PARAM_STOP_TIME:			ret = "PARAM_STOP_TIME";			break;
		case PARAM_CURRENT_TIME:		ret = "PARAM_CURRENT_TIME";			break;
		//case PARAM_TRESHOLD:			ret = "PARAM_TRESHOLD";				break;
		case PARAM_PM1_0:				ret = "PARAM_PM1_0";				break;
		case PARAM_PM2_5:				ret = "PARAM_PM2_5";				break;
		case PARAM_PM10:				ret = "PARAM_PM10";					break;
		case PARAM_TEXT_PART0:			ret = "PARAM_TEXT_PART0";			break;
		case PARAM_TEXT_PART1:			ret = "PARAM_TEXT_PART1";			break;
		case PARAM_TEXT_PART2:			ret = "PARAM_TEXT_PART2";			break;
		case PARAM_TEXT_PART3:			ret = "PARAM_TEXT_PART3";			break;
		case PARAM_TEXT_PART4:			ret = "PARAM_TEXT_PART4";			break;
		case PARAM_TEXT_PART5:			ret = "PARAM_TEXT_PART5";			break;
		case PARAM_TEXT_PART6:			ret = "PARAM_TEXT_PART6";			break;
		case PARAM_TEXT_PART7:			ret = "PARAM_TEXT_PART7";			break;
		default:
			break;
	}
	return ret;
}

void VERBOSE_add_message_to_process(nrf_esb_payload_t * payload)
{
	if (buffer_index == MSG_BUFFER_SIZE)
	{
		// si buffer plein on ignore le msg
		debug_printf("VERBOSE: buffer plein");
		return;
	}
	received_messages_buffer[buffer_index++] = *payload;
}

void VERBOSE_process_main(void)
{
	if (buffer_index > 0)
	{
		VERBOSE_trame_message(&received_messages_buffer[buffer_index-1]);
		buffer_index--;
	}
}

// TODO: traiter l'affichage hors IT
char * VERBOSE_trame_message(nrf_esb_payload_t * payload)
{
	uint32_t recipient = U32FROMU8( payload->data[BYTE_POS_RECIPIENTS],  payload->data[BYTE_POS_RECIPIENTS+1],  payload->data[BYTE_POS_RECIPIENTS+2],  payload->data[BYTE_POS_RECIPIENTS+3]);
	uint32_t emitter = U32FROMU8( payload->data[BYTE_POS_EMITTER],  payload->data[BYTE_POS_EMITTER+1],  payload->data[BYTE_POS_EMITTER+2],  payload->data[BYTE_POS_EMITTER+3]);
	uint8_t msg_cnt = payload->data[BYTE_POS_MSG_CNT];
	msg_id_e msg_id = payload->data[BYTE_POS_MSG_ID];
	uint8_t data_size = payload->data[BYTE_POS_DATASIZE];
	uint8_t data[data_size];
	param_id_e param_id = PARAM_UNKNOW;

	if (data_size > 0) {
		param_id = payload->data[BYTE_POS_DATAS];
		// on ignore le premier octet qui est le type de paramètre
		for (int i = 1; i < data_size; i++) {
			data[i-1] = payload->data[BYTE_POS_DATAS + i];
		}
		data_size--; // On enlève l'octet de paramètre
	}

	debug_printf("\n%s(0x%08x)-(%d)->%s(0x%08x)", VERBOSE_object_id_to_string(emitter & 0xFF), emitter, msg_cnt, VERBOSE_object_id_to_string(recipient & 0xFF), recipient);
	debug_printf(":[%s(0x%02x)", VERBOSE_message_id_to_string(msg_id), msg_id);

	if (param_id != PARAM_UNKNOW) {
		debug_printf(":(0x%02x)%s=(%d)", param_id, VERBOSE_parameter_id_to_string(param_id), data_size);

		if (data_size > 0)
		{
			debug_printf("0x");
			for (int i = 0; i < data_size; i++) {
				debug_printf("%02x", data[i]);
			}
		}

	}
	debug_printf("]\n");
}
