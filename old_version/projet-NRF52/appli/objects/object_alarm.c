/*
 * object_alarm.c
 *
 *  Created on: 25 janv. 2022
 *      Author: franchan
 */

#include "../config.h"
#include "../common/buttons.h"
#include "../common/systick.h"

#if OBJECT_ID == OBJECT_ALARM
	#include "object_alarm.h"
	#define DATA_SIZE 8

	void init(void);
	void send_message(command_YX command);
	void button_press_cb(void);
	void button_release_cb(void);
	void process_ms(void);
	running_e how_many_press(uint8_t * nb_press);
	void manual_mode(uint8_t * nb_press, uint8_t press);

static command_YX last_command;
static volatile uint32_t t = 0;

void process_ms(void)
{
	if(t)
		t--;
}

/*
 * Machine à états de notre alarme :
 * -> initialisation
 * -> mode manuel
 * -> recherche d'un message de la station de base
 * -> traitement du message reçu
 * -> réponse à la station de base
 * -> mode veille
 */
void ALARM_state_machine(void){

	static STATE state = INIT_ALARM;
	static STATE previous_state = INIT_ALARM;
	bool_e entrance = (state != previous_state)?TRUE:FALSE;

	static uint8_t nb_press;

	switch(state)
	{
		case INIT_ALARM:

			init();
			state = LOOK_FOR_MESSAGE;

		break;

		case MANUAL:
			/*Cas où l'appui se fait par le button network
			 * -> un appui : pause/play
			 * -> deux appuis : musique suivante
			 * -> trois appuis : son précédent
			 * -> rien : on regarde si un message a été reçu
			 */

			if(how_many_press(&nb_press) == END_OK)
				manual_mode(&nb_press, nb_press);

			state = SLEEP;
			break;
		case LOOK_FOR_MESSAGE:
			/*Liaison avec la station de base
			 if(message_reçu)
			 	 on le traite
			 	 state = MESSAGE_PROCESS;
			sinon
				on n'a rien reçu --> on met en veille
				state = SLEEP;
			 */
			state = MESSAGE_PROCESS;
			break;

		case MESSAGE_PROCESS:
			//Traitement du message reçu
			//fonction qui va traiter et déduire de la commande à envoyer
			//send_message(PLAY);
			state = RESPONSE;
			break;

		case RESPONSE:
			//Envoi de message à la station de base
			//https://reseaueseo-my.sharepoint.com/:x:/r/personal/samuel_poiraud_eseo_fr/_layouts/15/Doc.aspx?sourcedoc=%7B288C6EBE-360B-46DB-8AB1-4490476E35E8%7D&file=Protocole%20d%27%C3%A9change%20des%20messages.xlsx&action=default&mobileredirect=true
			state = MANUAL;
			break;
		case SLEEP:

			//Veille de l'appareil
			if(entrance){
				t = 10000;
				send_message(SLEEP_MODE);
			}
			if(!t){
				send_message(WAKE_UP);
				state = LOOK_FOR_MESSAGE;
			}else if(how_many_press(&nb_press) == END_OK){	//Il y a eu un appui bouton -> on le traite directement
				send_message(WAKE_UP);
				t = 0;	//On réinitialise notre compteur
				manual_mode(&nb_press, nb_press);
				state = MANUAL;
			}
			break;
		default:
			//ON N'EST PAS CENSÉ ARRIVER LÀ
			state = SLEEP;
			break;
	}
}

/* Initialisation des composants que l'on va utiliser
 * ici on ne prend que l'UART en plus des initialisations du main
 *
 */

void init(void){
	//INITIALISATION DE LA STATION DE BASE
	PARAMETERS_init();
	PARAMETERS_enable(PARAM_ACTUATOR_STATE, 0, FALSE, NULL, NULL);

	//INIT DES OBJETS
	SERIAL_DIALOG_init();
	send_message(PLAY);
}

/* Va permettre de créer notre trame et de l'envoyer sur la liaison UART afin de pilote l'YX5300
 *@command : type de commande qu'on demandera de faire à notre pilote (PLAY, PAUSE etc.)
 */

void send_message(command_YX command){
	uint8_t data[DATA_SIZE];
	data[0] = 0x7E; 					//starting byte
	data[1] = 0xFF; 					//version
	data[2] = 0x06; 					//the number of bytes of the command without starting byte and ending byte
	data[3] = command; 					//
	data[4] = 0x00;						//0x00 = no feedback, 0x01 = feedback
	data[5] = 0x00;						//datah 0x00 for what I want to use as command
	data[6] = 0x00; 					//datal 0x00 for what I want to use as command
	data[7] = 0xEF; 					//ending byte

	last_command = command;

	SERIAL_DIALOG_send_data(&data, DATA_SIZE);

}

static volatile bool_e flag_button_press = FALSE;
static volatile bool_e flag_button_release = FALSE;

void button_press_cb(void)
{
	flag_button_press = TRUE;
}

void button_release_cb(void)
{
	flag_button_release = TRUE;
}

/*
 * Fonction permettant de compter le nombre d'appuis bouton de suite
 *
 * @author : Nirgal and Anton
 */

running_e how_many_press(uint8_t * nb_press){

	typedef enum{
		INIT,
		WAIT,
		WAIT_RELEASE,
		END
	}state_e;
	static state_e state = INIT;
	static state_e previous_state = INIT;
	bool_e entrance = (state != previous_state)?TRUE:FALSE;
	previous_state = state;

	running_e ret = IN_PROGRESS;
	static uint8_t press = 0;

	switch(state){
		case INIT:
			BUTTONS_set_short_press_callback(BUTTON_NETWORK, &button_press_cb);
			BUTTONS_set_short_release_callback(BUTTON_NETWORK, &button_release_cb);
			Systick_add_callback_function(&process_ms);
			state = WAIT;
			break;

		case WAIT:
			if(flag_button_press)
			{
					state = WAIT_RELEASE;

			}
			else if(!t)
			{
				ret = END_OK;
				*nb_press = press;
				if(press == 1)
					button_network_process_short_press();	//pour respecter le cahier des charges.
				press = 0;

			}
			break;
		case WAIT_RELEASE:
			if(entrance)
			{
				press++;
				t = 1000;
				state = WAIT;
			}
			break;

			default:
				//On n'est pas censé arriver ici
				break;
			}

	flag_button_release = FALSE;
	flag_button_press = FALSE;
	return ret;
}


/*
 * Switch permettant de faire une action en fonction du nombre d'appuis de boutons de l'utilisateur
 */
void manual_mode(uint8_t * nb_press, uint8_t press){
	uint8_t appui = *nb_press;
	switch(appui){
	case 0:
		//il n'y a eu aucuns appuis de la part de l'utilisateur
		break;
	case 1:
		if(last_command != PAUSE){
			send_message(PAUSE);
		}else{
			send_message(PLAY);
		}
		break;
	case 2:
		send_message(NEXT_SONG);
		break;
	case 3:
		send_message(PREV_SONG);
		break;
	default:
		//On n'est pas censé arriver là
		break;
	}
}
#endif

