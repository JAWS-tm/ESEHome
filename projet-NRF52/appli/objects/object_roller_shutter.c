/*
 * object_roller_shutter.cs
 *
 *  Created on: 25 janv. 2022
 *      Author: tardychu
 */
#include "object_roller_shutter.h"
#include "../config.h"
#include "appli/common/adc.h"
#include "appli/common/gpio.h"
#include "appli/common/buttons.h"
#include "appli/common/parameters.h"
#include "bsp/pwm.h"
#include "appli/common/serial_dialog.h"
#include "appli/common/secretary.h"
#include "appli/common/systick.h"

#if OBJECT_ID == OBJECT_ROLLER_SHUTTER

static bool_e state_changement = FALSE;

static volatile bool_e flag_short_press_up;
static volatile bool_e flag_long_press_up;
static volatile bool_e flag_short_press_down;
static volatile bool_e flag_long_press_down;
static volatile bool_e flag_short_release_down;
static volatile bool_e flag_short_release_up;
static volatile bool_e flag_long_release_up;
static volatile bool_e flag_long_release_down;

static volatile bool_e arrived = FALSE;
static  int16_t value;
static  int16_t current;
static	int16_t seuil = 30;

static uint32_t t;
static uint32_t adc_current = 1000;
static int timeout = 0;

static volatile uint32_t up_time = FALSE;
static volatile uint32_t down_time = FALSE;
static volatile bool_e auto_mode = FALSE;

typedef enum
{
	ASK_NONE 	= 0,
	ASK_UP		= 1,
	ASK_DOWN 	= 2,
	ASK_STOP 	= 3,
	ASK_NB
}ask_of_movement_e;

static volatile ask_of_movement_e flag_ask_for_movement = ASK_NONE;

//cette fonction sera appelée par PARAMETERS lorsque on aura reçu un message nous demandant d'ouvrir / fermer / stopper le volet.
//ask_for_movement :
	//0 : none
	//1 : up
	//2 : down
	//3 : stop
void OBJECT_ROLLER_SHUTTER_ask_for_movement_callback(int32_t ask_for_movement)
{
	if(ask_for_movement < ASK_NB)
		flag_ask_for_movement = (ask_of_movement_e)ask_for_movement;
}
void short_press_up(){
	flag_short_press_up = TRUE;
}
void long_press_up(){
	flag_long_press_up = TRUE;
}
void short_press_down(){
	flag_short_press_down = TRUE;
}
void long_press_down(){
	flag_long_press_down = TRUE;
}
void short_release_up (){
	flag_short_release_up = TRUE;
}
void short_release_down (){
	flag_short_release_down = TRUE;
}
void long_release_up(){
	flag_long_release_up = TRUE;
}
void long_release_down(){
	flag_long_release_down = TRUE;
}
static volatile uint8_t hours = 0;
static volatile uint8_t minutes = 0;
static volatile uint8_t seconds = 0;
static volatile uint16_t ms = 0;
static uint32_t seconds_since_midnight = 0;
static volatile bool_e flag_auto_mode_ask_up = FALSE;
static volatile bool_e flag_auto_mode_ask_down = FALSE;


void process_ms(void){
	 if(timeout)
		 timeout--;
	 if(t)
		 t--;
	 if(adc_current)
		 adc_current --;

	 ms++;
	 if(ms == 1000)
	 {
		 ms = 0;
		 seconds++;
		 //debug_printf("sec : %d et min : %d\n",seconds,minutes);
		 if(seconds == 60)
		 {
			 seconds = 0;
			 minutes++;
			 if(minutes == 60)
			 {
				 minutes = 0;
				 hours++;
				 hours = hours %24;
			 }

		 }
		 seconds_since_midnight = seconds+minutes*60+hours*3600;
		 if(auto_mode == 1)
		 {	//Si le mode auto est actif, on lève les flags aux heures demandées
			 if(seconds_since_midnight == up_time)
				 flag_auto_mode_ask_up = TRUE;
			 else if(seconds_since_midnight == down_time)
				 flag_auto_mode_ask_down = TRUE;
		 }
	 }

}

void OBJECT_ROLLER_set_up_time_callback(int32_t new_up_time)
{
	up_time = new_up_time;
}

void OBJECT_ROLLER_set_down_time_callback(int32_t new_down_time)
{
	down_time = new_down_time;
}

void OBJECT_ROLLER_set_mode_callback(int32_t new_mode)
{
	if(new_mode <= 1)
		auto_mode = new_mode;
}

//Si le moteur arrive en fin de course il consomme plus de courant
//On récupère le courant consommé et on fixe un seuil
//Si le seuil est dépassé on passe arrive à TRUE
//Sinon arrived reste à FALSE

void motor_arrived(void){
	debug_printf("motor_arrived void\n");
	if (!adc_current){
		adc_current = 1000;
		ADC_read(1, &value);
		debug_printf("%d value of ADC\n",value);
		if(value<0)
			current = 0;
		else
			current = (((value)*619)/64); //permet de calculer le courant consommé par le moteur
		debug_printf("Courant consommé par le moteur : ");
		debug_printf("#%d->%d\n",value,current);
		if (current > seuil){
			debug_printf("Fin de course\n");
			arrived = TRUE;
		}
	}
}

//Main de Roller Shutter
void ROLLER_SHUTTER_state_machine(void)
{
	//debug_printf("-----state machine ----\n");
	typedef enum{
		 INIT,
		 MOTOR_FORWARD,
		 MOTOR_REVERSE,
		 MOTOR_OFF,
		 UP,
		 DOWN,
		 IDLE,
		 COMMUNICATION,
		 AUTO

	}state_e;

	static state_e state = INIT;
	static state_e previous_state = INIT;
	bool_e entrance = (state != previous_state);
	previous_state = state;

	switch(state) {
		////Initialisation
		case INIT :
			Systick_add_callback_function(&process_ms);
			PARAMETERS_init();
			PARAMETERS_enable(PARAM_ACTUATOR_STATE, 0, FALSE, &OBJECT_ROLLER_SHUTTER_ask_for_movement_callback, NULL);

			up_time = 8*3600;
			down_time = 22*3600;
			PARAMETERS_enable(PARAM_START_TIME, up_time, FALSE, &OBJECT_ROLLER_set_up_time_callback, NULL);
			PARAMETERS_enable(PARAM_STOP_TIME, down_time, FALSE, &OBJECT_ROLLER_set_down_time_callback, NULL);

			auto_mode = FALSE;
			PARAMETERS_enable(PARAM_MODE, auto_mode, FALSE, &OBJECT_ROLLER_set_mode_callback, NULL);

			ADC_init();
			GPIO_configure(PIN_RIN, NRF_GPIO_PIN_PULLUP, true);
			GPIO_configure(PIN_FIN, NRF_GPIO_PIN_PULLUP, true);
			BUTTONS_add(BUTTON_USER0, PIN_BP_UP, TRUE, &short_press_up, NULL, &long_press_up, NULL);
			BUTTONS_add(BUTTON_USER1, PIN_BP_DOWN, TRUE,&short_press_down, NULL,&long_press_down, NULL);
			state = IDLE;
			//timer();
			break;

		////MONTEE DU VOLET
		case UP :
			//debug
			ADC_read(1, &value);
			debug_printf("%d value of ADC\n",value);
			if (entrance){
				debug_printf("Montée du volet\n");
				t = 1000;
				GPIO_write(PIN_RIN, true);
				GPIO_write(PIN_FIN, false);
				timeout = 10000;
			}
			/*if(flag_ask_for_movement == ASK_UP)
				state = IDLE;
			if(flag_ask_for_movement == ASK_DOWN)
				state = DOWN;*/
			else if (!timeout){
				debug_printf("Temps écoulé \n");
				state = IDLE;
			}
			else if (flag_short_press_down || flag_short_press_up /*|| (t && flag_short_release_up)*/ || flag_ask_for_movement == ASK_STOP){
				state = IDLE;
			}
			else if (arrived == TRUE){
				debug_printf("volet ouvert\n");
				PARAMETERS_update(PARAM_ACTUATOR_STATE, 1);
				arrived = FALSE;
				state = COMMUNICATION;
			}
			if (state != UP){        // OUT OF STATE
				GPIO_write(PIN_RIN, false);
				GPIO_write(PIN_FIN, false);
			}
			break;

			////DESCENTE DU VOLET
		case DOWN :
			if (entrance){
				debug_printf("Descente du volet\n");
				t = 1000;
				GPIO_write(PIN_RIN, false);
				GPIO_write(PIN_FIN, true);
				timeout = 10000;
			}

			/*if(flag_ask_for_movement == ASK_UP)
				state = UP;
			if(flag_ask_for_movement == ASK_DOWN)
				state = DOWN;*/
			else if (!timeout){
				debug_printf("Temps écoulé \n");
				state = IDLE;
			}
			else if (flag_short_press_up || flag_short_press_down /*|| (t && flag_short_release_down)*/ || flag_ask_for_movement == ASK_STOP){
				arrived = FALSE;
				state = IDLE;
			}
			else if (arrived == TRUE){
				debug_printf("volet fermé\n");
				PARAMETERS_update(PARAM_ACTUATOR_STATE, 0);
				arrived = FALSE;
				state = COMMUNICATION;
			}
			if (state != DOWN ){        // OUT OF STATE
				GPIO_write(PIN_RIN, false);
				GPIO_write(PIN_FIN, false);
			}
			break;

			/////cas eteint
		case IDLE :
			if(entrance)
			{
				flag_auto_mode_ask_up = FALSE;
				flag_auto_mode_ask_down = FALSE;
			}
			if(flag_short_press_down || flag_ask_for_movement == ASK_DOWN || flag_auto_mode_ask_down)
				state = DOWN;
			else if(flag_short_press_up || flag_ask_for_movement == ASK_UP || flag_auto_mode_ask_up)
				state = UP;
			flag_auto_mode_ask_up = FALSE;
			flag_auto_mode_ask_down = FALSE;

			break;
		default:
			break;

			/////On envoie l'etat actuel du volet à la station de base
		case COMMUNICATION :
			debug_printf("param actuel state\n");
			PARAMETERS_send_param32_to_basestation(PARAM_ACTUATOR_STATE);
			debug_printf("param mode\n");
			PARAMETERS_send_param32_to_basestation(PARAM_MODE);
			state = IDLE;
		break;


	}

	flag_ask_for_movement = ASK_NONE;
	flag_short_press_up = FALSE;
	flag_long_press_up = FALSE;
	flag_short_press_down = FALSE;
	flag_long_press_down = FALSE;
	flag_short_release_up = FALSE;
	flag_short_release_down = FALSE;
	flag_long_release_down = FALSE;
	flag_long_release_up = FALSE;
}

void object_roller_shutter_changement_etat(void)
{
	state_changement = TRUE;
}

#endif

/////TEST 2022////
/*
	#if 0
		case MOTOR_INIT:
			PARAMETERS_enable(PARAM_ACTUATOR_STATE, 0, TRUE, &OBJECT_ROLLER_SHUTTER_etat_updated_callback, NULL);
			GPIO_init();
			ADC_init();
			GPIO_configure(PIN_RIN, NRF_GPIO_PIN_NOPULL, true);
			GPIO_configure(PIN_FIN, NRF_GPIO_PIN_NOPULL, true);
			BUTTONS_add(BUTTON_USER0, PIN_BP_UP, TRUE, &object_roller_shutter_changement_etat, NULL, NULL, NULL);
			BUTTONS_add(BUTTON_USER1, PIN_BP_DOWN, TRUE, &object_roller_shutter_changement_etat, NULL, NULL, NULL);
			state = MOTOR_REVERSE;	//Changement d'état
			break;

		case MOTOR_FORWARD:
			GPIO_write(PIN_FIN, true);
			GPIO_write(PIN_RIN, false);
			if(BUTTONS_read(BUTTON_USER0))	//button UP
			{
				state = MOTOR_REVERSE;	//Changement d'état
			}
			break;

		case MOTOR_REVERSE:
			GPIO_write(PIN_RIN, true);
			GPIO_write(PIN_FIN, false);
			if(BUTTONS_read(BUTTON_USER1))		//button down
			{
				state = MOTOR_FORWARD;	//Changement d'état
			}
			break;

		case MOTOR_OFF:
			if(BUTTONS_read(BUTTON_USER1))
			{
				state = MOTOR_REVERSE;	//Changement d'état
			}
			break;

		default:
			state = MOTOR_INIT;	//N'est jamais sensé se produire.
			break;
	#endif
*/
//////END TEST 2022//////




///////LAST YEAR CODE/////////

/*void ROLLER_SHUTTER_state_machine(void){
	if (SERIAL_DIALOG_process_msg(8, 1)){
		PWM_init(Pin_BP_UP, 1)
				PWM_set_duty(1, 75);
	}
	else if(SERIAL_DIALOG_process_msg(8, 2)){
		PWM_init(Pin_BP_DOWN, 1)
				PWM_set_duty(2, 125);
	}else{
		if ((HAL_GPIO_ReadPin(Pin_BP_UP,2) == true) &&(HAL_GPIO_ReadPin(Pin_BP_DOWN,3) == false)){
			PWM_init(Pin_BP_UP, 1)
				PWM_set_duty(1, 75);
		}
		if((HAL_GPIO_ReadPin(Pin_BP_DOWN,3) == true) && (HAL_GPIO_ReadPin(Pin_BP_UP,2) == false)){
			PWM_init(Pin_BP_DOWN, 1)
				PWM_set_duty(2, 125);
		}
	}
	state static_e
	if (HAL_GPIO_ReadPin(PIN_BP_UP,16) == 1){
		PIN_LED_NETWORK == 1;
	}
	else (HAL_GPIO_ReadPin(PIN_BP_UP,16) == 0){
		PIN_LED_NETWORK == 0;
	}
}*/

///// TEST NOT FONTCIONNAL /////
/*if(state == VENTILATOR_ON){
	GPIO_init();
	GPIO_configure(MOSFET_PIN, NRF_GPIO_PIN_PULLUP, true);
	GPIO_write(MOSFET_PIN, true); }
else if (state == VENTILATOR_OFF){
	GPIO_write(MOSFET_PIN, false);
}*/
