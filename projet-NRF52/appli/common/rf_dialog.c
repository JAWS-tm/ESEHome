/*
 * rc_dialog.c
 *
 *  Created on: 10 févr. 2021
 *      Author: Guillaume  & Thomas
 */
#include "../config.h"
#include "secretary.h"
#include "rf_dialog.h"
#include "parameters.h"
//Reception e transmission RF

static uint32_t my_device_id = -1;	//constitué de 3 octets d'identifiant unique et 1 octet d'OBJECT_ID
static uint32_t my_base_station_id = 0xFFFFFFFF;
static uint8_t index_msg_cnt = 0;

void RF_DIALOG_init(void)
{
	my_device_id = (NRF_FICR->DEVICEID[0] << 8) | OBJECT_ID;
	my_base_station_id = PARAMETERS_get(PARAM_MY_BASE_STATION_ID);
}

void RF_DIALOG_process_rx(nrf_esb_payload_t * payload){

	uint8_t msg_id;
	uint32_t recipient;
	if(payload->length > BYTE_POS_DATASIZE && payload->length <= NRF_ESB_MAX_PAYLOAD_LENGTH)
	{
		recipient = U32FROMU8( payload->data[BYTE_POS_RECIPIENTS],  payload->data[BYTE_POS_RECIPIENTS+1],  payload->data[BYTE_POS_RECIPIENTS+2],  payload->data[BYTE_POS_RECIPIENTS+3]);
		msg_id = payload->data[BYTE_POS_MSG_ID];

		switch(msg_id){
			case RECENT_RESET :{
				break;
			}
			case ASK_FOR_SOFTWARE_RESET :{
				break;
			}
			case PING :{
				break;
			}
			case PONG :{
				break;
			}
			case EVENT_OCCURED :{
				break;
			}
			case PARAMETER_IS :{
				break;
			}
			case PARAMETER_ASK :{
				//TODO répondre !!
				//RF_DIALOG_send_msg_id_to_basestation(PARAMETER_IS, );
				break;
			}
			case PARAMETER_WRITE :{
				break;
			}

			case I_HAVE_NO_SERVER_ID :{
				break;
			}

			case YOUR_SERVER_ID_IS :{
				break;
			}

			default:
				break;
		}
	}
}


void RF_DIALOG_send_msg_id_to_basestation(msg_id_e msg_id, uint8_t datasize, uint8_t * datas)
{
	uint8_t msg_to_send[NRF_ESB_MAX_PAYLOAD_LENGTH];
	uint8_t size = 0;

	msg_to_send[BYTE_POS_RECIPIENTS]   = (my_base_station_id>>24)	&0xFF;
	msg_to_send[BYTE_POS_RECIPIENTS+1] = (my_base_station_id>>16)	&0xFF;
	msg_to_send[BYTE_POS_RECIPIENTS+2] = (my_base_station_id>>8)	&0xFF;
	msg_to_send[BYTE_POS_RECIPIENTS+3] = (my_base_station_id>>0)	&0xFF;

	msg_to_send[BYTE_POS_MSG_CNT] = index_msg_cnt;
	index_msg_cnt++;

	msg_to_send[BYTE_POS_MSG_ID] = msg_id;

	datasize = MIN(datasize, MAX_DATA_SIZE);
	msg_to_send[BYTE_POS_DATASIZE] = datasize;

	for(uint8_t i = 0; i<datasize; i++)
	{
		msg_to_send[BYTE_POS_DATAS+i] = datas[i];
	}


	SECRETARY_send_msg(BYTE_POS_DATAS+datasize, msg_to_send);
}

void RF_DIALOG_send_msg_id_to_object(recipient_e obj_id,msg_id_e msg_id, uint8_t datasize, uint8_t * datas){
	uint8_t msg_to_send[NRF_ESB_MAX_PAYLOAD_LENGTH];
		uint8_t size = 0;

		msg_to_send[BYTE_POS_RECIPIENTS]   = (obj_id>>24)	&0xFF;
		msg_to_send[BYTE_POS_RECIPIENTS+1] = (obj_id>>16)	&0xFF;
		msg_to_send[BYTE_POS_RECIPIENTS+2] = (obj_id>>8)	&0xFF;
		msg_to_send[BYTE_POS_RECIPIENTS+3] = (obj_id>>0)	&0xFF;

		msg_to_send[BYTE_POS_MSG_CNT] = index_msg_cnt;
		index_msg_cnt++;

		msg_to_send[BYTE_POS_MSG_ID] = msg_id;

		datasize = MIN(datasize, MAX_DATA_SIZE);
		msg_to_send[BYTE_POS_DATASIZE] = datasize;

		for(uint8_t i = 0; i<datasize; i++)
		{
			msg_to_send[BYTE_POS_DATAS+i] = datas[i];
		}


		SECRETARY_send_msg(BYTE_POS_DATAS+datasize, msg_to_send);
}

void RF_dialog_sample_bank(void) // C'EST UN EXEMPLE!!!!!
{
	RF_DIALOG_send_msg_id_to_basestation(RECENT_RESET, 0, NULL);
	uint8_t param_id = 12;
	RF_DIALOG_send_msg_id_to_basestation(PARAMETER_ASK, 1, &param_id);

	uint8_t tab[4] = {0xCA, 0xFE, 0xDE, 0xCA};
	RF_DIALOG_send_msg_id_to_basestation(YOUR_SERVER_ID_IS, 4, &tab);

}
