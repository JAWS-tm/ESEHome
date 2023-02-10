#include "../config.h"
#include "../common/serial_dialog.h"
#include "object_mp3_player.h"

#if OBJECT_ID == OBJECT_MP3_PLAYER

	#warning "ce code est à l'état d'ébauche, non testé, non terminé"
	#warning "vous êtes invités à remonter toute suggestion de complétion ou d'amélioration !"



#define UART_AT_BAUDRATE_9600 		1
#define FIRST_SONG	0x01
#define PLAY_WITH_INDEX	0x03

bool_e initialization = FALSE;

void YX6300_demo(void)
{
	uint8_t data[2];
	data[0] = 0x00;
	data[1] = 0x00;
	YX6300_send_request(FIRST_SONG, FALSE, 2, data);

	uint16_t index_song = 4;
	data[0] = HIGHINT(index_song);
	data[1] = LOWINT(index_song);
	YX6300_send_request(PLAY_WITH_INDEX, FALSE, 2, data);

	YX6300_send_request_with_2bytes_of_datas(PLAY_WITH_INDEX, FALSE, index_song);
}


void YX6300_send_request_with_2bytes_of_datas(command_e command, bool_e feedback, uint16_t data16)
{
	uint8_t msg[2+4+10];	//on fait le choix de refuser la demmande si datasize > 10
	uint8_t i = 0;
	msg[i++] = 0x7E; 		// every command should start with 0x7E
	msg[i++] = 0xFF;		// version of information
	msg[i++] = 2+4;			//length = (FF+length+command+feedback) + datasize
	msg[i++] = command;		// command such as PLAY, PAUSE ...
	msg[i++] = (feedback)?1:0;

	msg[i++] = HIGHINT(data16);
	msg[i++] = LOWINT(data16);

	msg[i++] = 0xEF;		// every command should finish with 0xEF

	//UART_puts(YX6300_UART_ID, msg, i);
	SERIAL_DIALOG_send_data(msg, i);
}



void YX6300_send_request(command_e command, bool_e feedback, uint8_t datasize, uint8_t * data)
{
	uint8_t msg[2+4+10];	//on fait le choix de refuser la demmande si datasize > 10

	uint8_t i = 0;

	if(datasize<=10)
	{
		msg[i++] = 0x7E;
		msg[i++] = 0xFF;
		msg[i++] = datasize+4;	//length = (FF+length+command+feedback) + datasize
		msg[i++] = command;
		msg[i++] = (feedback)?1:0;

		uint8_t d;
		for(d=0; d<datasize; d++)
			msg[i++] = data[d];

		msg[i++] = 0xEF;

		//UART_puts(YX6300_UART_ID, msg, i);
		SERIAL_DIALOG_send_data(msg, i);
	}
	else
	{
		debug_printf("you should correct this function or respect the datasize limit!\n");
	}
}

void MP3_PLAYER_use_sd_card(){
	uint8_t data[2];
	data[0] = 0x00;
	data[1] = 0x02;

	YX6300_send_request(SELECT_DEVICE, FALSE, 2, data);
}

void MP3_PLAYER_basic_command(command_e command){

	/* basic command include all commands that don't need variable data,
	 *  unlike select song command	*/

	uint8_t data[2];
	data[0] = 0x00;
	data[1] = 0x00;

	YX6300_send_request(command, FALSE, 2, data);

}

void MP3_PLAYER_process_main(){

	typedef enum {
			INIT,
			PROCESS,
		}state_e;

		static state_e state = INIT;

		switch (state)
		{
			case INIT: {
				if (!initialization)
				{
					initialization = TRUE;
				    MP3_PLAYER_use_sd_card();
				}

				state = PROCESS;
				break;
			}
			case PROCESS: {

				break;
			}
		}
}

#endif
