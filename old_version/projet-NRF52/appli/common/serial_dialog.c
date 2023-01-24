/*
 * serial_dialog.c
 *
 *  Created on: 15/11/2019
 *      Author: Nirgal
 */

#include "../config.h"
#include "nrf52.h"
#include "components/libraries/util/app_util_platform.h"
#include "components/libraries/util/sdk_common.h"
#include "serial_dialog.h"
#include "secretary.h"

#include "components/libraries/uart/app_uart.h"
#include "nrf_uart.h"
#include "nrf_uarte.h"
#include <stdarg.h>

/*
Norme des messages transmis :

SOH 	SIZE	DATA(s)	EOT
BA		01		HH		DA


Exemples de messages :


BA 00 DA

BA 01 01 DA

BA 01 00 DA

BA 04 D1 D2 D3 D4 DA

*/
static volatile bool_e initialized = FALSE;

void SERIAL_DIALOG_display_msg(uint8_t size, uint8_t * datas);
static void SERIAL_DIALOG_process_msg(uint8_t size, uint8_t * datas);
static void SERIAL_DIALOG_uart_event_handler(app_uart_evt_t * p_event);
static void SERIAL_DIALOG_parse_rx(uint8_t c);

#define RX_BUF_SIZE		128
#define TX_BUF_SIZE		128

static app_uart_buffers_t buffers;
static uint8_t     rx_buf[RX_BUF_SIZE];
static uint8_t     tx_buf[TX_BUF_SIZE];



/*
void SERIAL_DIALOG_uart_event_handler(nrfx_uart_event_t const * p_event, void * p_context)
{
	static volatile nrfx_err_t err_code;

	switch(p_event->type)
	{
		case NRFX_UART_EVT_TX_DONE:
			break;
		case NRFX_UART_EVT_RX_DONE:
			if(nb_datas_in_buf < RX_BUF_SIZE)
			{
				nb_datas_in_buf++;
				write_index = (write_index+1)%RX_BUF_SIZE;
			}
			err_code = nrfx_uart_rx(&uart_instance, &rx_buf[write_index], 1);
			break;
		case NRFX_UART_EVT_ERROR:
			nrf_uart_event_clear(NRF_UART0, NRF_UART_EVENT_TXDRDY);
			nrf_uart_event_clear(NRF_UART0, NRF_UART_EVENT_RXTO);
			nrf_uart_event_clear(NRF_UART0, NRF_UART_EVENT_ERROR);

			err_code = nrfx_uart_rx(&uart_instance, &rx_buf[write_index], 1);
			break;
		default:
			break;
	}
}
*/


#define DEBUG_PRINTF_BUFFER_SIZE	128
uint32_t debug_printf(char * format, ...)
{
	va_list args_list;
	va_start(args_list, format);

	static char buf[DEBUG_PRINTF_BUFFER_SIZE];
	int ret;
	ret = (uint32_t)vsnprintf((char*)buf, DEBUG_PRINTF_BUFFER_SIZE, format, args_list);	//Prépare la chaine à envoyer.

	SERIAL_DIALOG_puts(buf);

	va_end(args_list);
	return ret;
}

void SERIAL_DIALOG_init(void)
{
	/*static nrfx_uart_config_t uart_config = (nrfx_uart_config_t)NRFX_UART_DEFAULT_CONFIG;

	nrfx_uart_init(&uart_instance, &uart_config, &SERIAL_DIALOG_uart_event_handler);
	nrfx_uart_rx_enable(&uart_instance);
	nrfx_uart_rx(&uart_instance, &rx_buf[write_index], 1);
*/
	const app_uart_comm_params_t comm_params =
	  {
		  8,//RX_PIN_NUMBER,
		  6,//TX_PIN_NUMBER,
		  7,//RTS_PIN_NUMBER,
		  9,//CTS_PIN_NUMBER,
		  APP_UART_FLOW_CONTROL_DISABLED,
		  false,	//use parity
         // NRF_UARTE_BAUDRATE_9600
		  NRF_UARTE_BAUDRATE_115200
	  };

	buffers.rx_buf      = rx_buf;
	buffers.rx_buf_size = sizeof (rx_buf);
	buffers.tx_buf      = tx_buf;
	buffers.tx_buf_size = sizeof (tx_buf);

	app_uart_init(&comm_params, &buffers, &SERIAL_DIALOG_uart_event_handler, APP_IRQ_PRIORITY_LOWEST);
	initialized = TRUE;

	SERIAL_DIALOG_puts("uart initialized\n");
}

static void SERIAL_DIALOG_uart_event_handler(app_uart_evt_t * p_event)
{
	uint8_t c;
	switch(p_event->evt_type)
	{
		case APP_UART_DATA_READY:
			while(app_uart_get(&c) == NRF_SUCCESS)
			{
				//SERIAL_DIALOG_putc(c);
				SERIAL_DIALOG_parse_rx(c);
			}
			break;
		case APP_UART_COMMUNICATION_ERROR:
			if(p_event->data.error_communication == 0x01)
				SERIAL_DIALOG_puts("overrun\n");
			/*else
				SERIAL_DIALOG_puts("unknow com error\n");
*/
			break;
		case APP_UART_FIFO_ERROR:
			SERIAL_DIALOG_puts("fifo error\n");
			break;
		case APP_UART_TX_EMPTY:
			break;
		case APP_UART_DATA:
			SERIAL_DIALOG_puts("data error\n");
			//never happen if fifo is enabled.
			break;
		default:
			break;
	}
}


void SERIAL_DIALOG_putc(char c)
{
	app_uart_put(c);
}

void SERIAL_DIALOG_puts(char * s)
{
	static bool_e reentrance_detection = FALSE;
	if(!reentrance_detection)
	{
		reentrance_detection = TRUE;
		if(!initialized)
			SERIAL_DIALOG_init();
		//nrfx_uart_tx(&uart_instance, (uint8_t *)(s), strlen(s));
		for(uint16_t i = 0; s[i]; i++)
			while(app_uart_put(s[i])!=NRF_SUCCESS);
		reentrance_detection = FALSE;
	}
}



void SERIAL_DIALOG_process_main()
{


}

/**
 * @brief	Cette fonction assure le traitement des caractères reçus sur l'UART. Les ocets sont rangés dans les variables size et datas, avant d'être traité lorsque le message complet et valide est reçu.
 * @post	La fonction SERIAL_DIALOG_process_msg() sera appelé si un message au format valide est reçu
 * @pre		Cette fonction doit être appelée pour chaque caractère reçu
 */
static void SERIAL_DIALOG_parse_rx(uint8_t c)
{
	static uint8_t datas[255];
	static uint16_t index = 0;
	static uint8_t size;
	switch(index)
	{
		case 0:
			if(c == SOH)
				index++;
			break;
		case 1:
			size = c;
			index++;
			break;
		default:
			if(index-2 == size)
			{
				if(c == EOT)//ok, fin du message !
					SERIAL_DIALOG_process_msg(size, datas);
				index = 0;
			}
			else if(c == SOH)				//ATTENTION, ce faisant, on interdit le SOH comme data !
				index = 1;
			else if(c == EOT)				//ATTENTION, ce faisant, on interdit le EOT comme data !
				index = 0;
			else if(index-2 < size)
			{
				datas[index-2] = c;
				index++;
			}
			else
				index = 0;
			break;
	}
}

/**
 * @brief	Cette fonction permet l'envoi d'un message sur la liaison série.
 * @pre		Le tableau datas doit contenir au moins 'size' octet. Sinon, le pointeur 'datas' peut être NULL.
 */
void SERIAL_DIALOG_send_msg(uint8_t size, uint8_t * datas)
{
	uint8_t i;
	char c;
	char s[64];
	if(size > 0 && datas == NULL)
		return;

	s[0] = SOH;			//SOH
	s[1] = size;			//size
	for(i=0; i<size; i++)
	{
		c = datas[i];
		if(c==SOH || c==EOT)	//si vous avez la mauvaise idée d'envoyer les mêmes octets que ceux utilisés pour SOH ou EOT... alors on les flingue. Par principe.
			c++;
		s[2+i]=c;	//datas...
	}
	s[2+i] = EOT;			//EOT
	s[3+i] = '\0';
	SERIAL_DIALOG_puts(s);
}

/**
 * @brief	Cette fonction traite le message reçu et agit en conséquence.
 */
static void SERIAL_DIALOG_process_msg(uint8_t size, uint8_t * datas)
{
	SECRETARY_process_msg_from_uart(size, datas);
}

/**
 * @brief Cette fonction privée affiche le contenu d'un message donné en paramètre
 */
void SERIAL_DIALOG_display_msg(uint8_t size, uint8_t * datas)
{
	debug_printf("[%d data%s ", size, (size>1)?"s]":"]");
	for(uint8_t i = 0 ; i<size ; i++)
		debug_printf("%02x ", datas[i]);
	debug_printf("\n");
}

