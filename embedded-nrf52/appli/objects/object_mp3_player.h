/*
 * object_mp3_player.h
 *
 *  Created on: 8 fev. 2023
 *      Author: Hugo Dumartin
 *
 *      datasheet link : https://github.com/0xcafed00d/yx5300/blob/master/docs/Serial%20MP3%20Player%20v1.0%20Manual.pdf
 *
 */

typedef enum{
	NEXT_SONG = 0x01,
	PREVIOUS_SONG,
	PLAY_WITH_INDEX,
	VOLUME_UP,
	VOLUME_DOWN,
	SET_VOLUME,
	SINGLE_CYCLE_PLAY = 0x08,
	SELECT_DEVICE,
	SLEEP_MODE,
	WAKE_UP,
	RESET,
	PLAY,
	PAUSE,
	PLAY_WITH_FOLDER_AND_FILE_NAME,
	STOP_PLAY,
	CYCLE_PLAY_WITH_FOLDER_NAME,
	SHUFFLE_PLAY,
	SET_SINGLE_CYCLE_PLAY,

}command_e;

void YX6300_send_request(command_e command, bool_e feedback, uint8_t datasize, uint8_t * data);
void MP3_PLAYER_basic_command(command_e command);
void MP3_PLAYER_process_main();
