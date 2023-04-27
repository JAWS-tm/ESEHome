/*
 * object_alarm.h
 *
 *  Created on: 25 janv. 2022
 *      Author: franchan
 */

typedef enum {
	INIT_ALARM,
	LOOK_FOR_MESSAGE,
	MANUAL,
	MESSAGE_PROCESS,
	RESPONSE,
	SLEEP
}STATE;

typedef enum{
	NEXT_SONG = 0x01,
	PREV_SONG = 0x02,
	SLEEP_MODE = 0x0A,
	WAKE_UP = 0x0B,
	PLAY = 0x0D,
	PAUSE = 0x0E
}command_YX;

#ifndef APPLI_OBJECTS_OBJECT_ALARM_H_
#define APPLI_OBJECTS_OBJECT_ALARM_H_

/* Fonction central de notre alarme, elle va gérer les différents états possibles pour son bon fonctionnement
 *
 */
void ALARM_state_machine(void);



#endif /* APPLI_OBJECTS_OBJECT_ALARM_H_ */
