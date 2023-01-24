/*
 * secretary.c
 *
 *  Created on: 21 nov. 2019
 *      Author: Nirgal
 */

#include "../config.h"
#include "secretary.h"
#include "nrf.h"
#include "components/libraries/util/sdk_common.h"
#include "components/libraries/util/sdk_macros.h"
#include "components/libraries/log/nrf_log.h"
#include "components/libraries/log/nrf_log_ctrl.h"
#include "components/libraries/log/nrf_log_default_backends.h"
#include "modules/nrfx/hal/nrf_gpio.h"
#include "components/proprietary_rf/esb/nrf_esb.h"

static nrf_esb_payload_t        rx_payload;
static nrf_esb_payload_t        tx_payload;
#if SNIFFER_MODE
static nrf_esb_payload_t        rx_payload_process_main;
volatile static _Bool flag_rx_payload_process_main = false;
#endif
static volatile _Bool initialized = false;

static void SECRETARY_frame_parse(nrf_esb_payload_t * payload);

void SECRETARY_init(void)
{
	uint32_t err_code;
    uint8_t base_addr_0[4] = {0xE5, 0xE5, 0xE5, 0xE5};
    uint8_t base_addr_1[4] = {0xE0, 0xE0, 0xE0, 0xE0};
    uint8_t addr_prefix[8] = {0xE5, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8 };

	nrf_esb_config_t nrf_esb_config         = NRF_ESB_DEFAULT_CONFIG;
	nrf_esb_config.protocol                 = NRF_ESB_PROTOCOL_ESB_DPL;
	nrf_esb_config.retransmit_delay         = 300+(OBJECT_ID%4)*300;	//300us + 300us*ID !
	nrf_esb_config.bitrate                  = NRF_ESB_BITRATE_1MBPS;
	nrf_esb_config.event_handler            = SECRETARY_esb_event_handler;
	nrf_esb_config.mode                     = NRF_ESB_MODE_PTX;
	nrf_esb_config.selective_auto_ack       = true;	//on rend les acquittements dépendant de l'argument du transmetteur !...

	err_code = nrf_esb_init(&nrf_esb_config);

	if(err_code == NRF_SUCCESS)
		nrf_esb_set_base_address_0(base_addr_0);

	if(err_code == NRF_SUCCESS)
		nrf_esb_set_base_address_1(base_addr_1);

	if(err_code == NRF_SUCCESS)
		nrf_esb_set_prefixes(addr_prefix, NRF_ESB_PIPE_COUNT);

	tx_payload.pipe = 0;

	if(err_code == NRF_SUCCESS)
		initialized = true;

#if SHOE_MODE
	fifo.index_read = 0;
	fifo.index_write = 0;
#endif

	nrf_esb_start_rx();
}



void SECRETARY_process_main(void)
{

}


void SECRETARY_esb_event_handler(nrf_esb_evt_t const * p_event)
{
    switch (p_event->evt_id)
    {
        case NRF_ESB_EVENT_TX_SUCCESS:
        	nrf_esb_start_rx();
            break;
        case NRF_ESB_EVENT_TX_FAILED:
            nrf_esb_flush_tx();
            nrf_esb_start_tx();
            break;
        case NRF_ESB_EVENT_RX_RECEIVED:
            while (nrf_esb_read_rx_payload(&rx_payload) == NRF_SUCCESS)
            {
                if (rx_payload.length > 0)
                {
                    SECRETARY_frame_parse(&rx_payload);
                }
            }

            break;
    }
}

void SECRETARY_frame_parse(nrf_esb_payload_t * payload)
{
	#if 0
		if(payload->length == 4)
		{
			if(payload->data[0] == 0xE5 && payload->data[1] == 0xE0)
			{
				//événement reçu !
				//...
			}
		}
	#endif
}




//Cette fonction permet de convertir un message reçu sur l'UART en une "fausse trame RF"... à des fins de tests.
void SECRETARY_process_msg_from_uart(uint8_t size, uint8_t * datas)
{
	static nrf_esb_payload_t fake_payload;
	bool_e initialized = FALSE;
	if(!initialized)
	{
		initialized = TRUE;
		fake_payload.noack = FALSE;
		fake_payload.pid = 0;
		fake_payload.pipe = 0;
		fake_payload.rssi = 0;
	}

	fake_payload.length = size;
	for(uint8_t i=0; i<size; i++)
	{
		fake_payload.data[i] = datas[i];
	}

	SECRETARY_frame_parse(&fake_payload);
}


void SECRETARY_send_msg(uint8_t size, uint8_t * datas)
{
	tx_payload.length = MIN(size,NRF_ESB_MAX_PAYLOAD_LENGTH);
	for(uint8_t i = 0; i<tx_payload.length; i++)
	{
		tx_payload.data[i] = datas[i];
	}
	tx_payload.noack = FALSE;	//On demande un acquittement !
	nrf_esb_stop_rx();

	if (nrf_esb_write_payload(&tx_payload) == NRF_SUCCESS)
	{

	}
	else
	{
		nrf_esb_flush_tx();
	}
}


