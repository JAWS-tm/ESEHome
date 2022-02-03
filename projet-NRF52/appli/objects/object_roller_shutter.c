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
static	int16_t seuil = 40;




static uint32_t t;
static uint32_t adc_current = 1000;
static int timeout = 0;

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

void process_ms(void){
	 if(timeout)
		 timeout--;
	 if(t)
		 t--;
	 if(adc_current)
		 adc_current --;
}
//Si le moteur arrive en fin de course il consomme plus de courant
//On récupère le courant consommé et on fixe un seuil
//Si le seuil est dépassé on passe arrive à TRUE
//Sinon arrived reste à FALSE

//TODO : lire l'ADC
//Si l'état actuel moteur est UP ou DOWN --> on regarde la valeur du courant consommé.
//il faudra peut être ignorer les premières 100aines de ms... car pic de courant normal au début.
//si le courant consommé est "fort" ==> arrived passe à TRUE. sinon FALSE.

void motor_arrived(void){
	if (!adc_current){
		adc_current = 1000;
		ADC_read(PIN_ADC, &value);
		//debug_printf("%d",value);
		current = (((value)*619)/64);
		debug_printf("%d",current);
		if (current > seuil){
			debug_printf("Fin de course\n");
			arrived = TRUE;
		}
	}
}

void ROLLER_SHUTTER_state_machine(void)
{
	typedef enum{
		 INIT,
		 MOTOR_FORWARD,
		 MOTOR_REVERSE,
		 MOTOR_OFF,
		 UP,
		 DOWN,
		 IDLE
	}state_e;

	static state_e state = INIT;
	static state_e previous_state = INIT;
	bool_e entrance = (state != previous_state);
	previous_state = state;

	switch(state) {

///NEW CODE 28/01////
		case INIT :
			Systick_add_callback_function(&process_ms);
			PARAMETERS_enable(PARAM_ACTUATOR_STATE, 0, FALSE, &OBJECT_ROLLER_SHUTTER_ask_for_movement_callback, NULL);
			ADC_init();
			GPIO_configure(PIN_RIN, NRF_GPIO_PIN_NOPULL, true);
			GPIO_configure(PIN_FIN, NRF_GPIO_PIN_NOPULL, true);
			BUTTONS_add(BUTTON_USER0, PIN_BP_UP, TRUE, &short_press_up, NULL, &long_press_up, NULL);
			BUTTONS_add(BUTTON_USER1, PIN_BP_DOWN, TRUE,&short_press_down, NULL,&long_press_down, NULL);
			state = IDLE;
			break;
		case UP :
			if (entrance){
				t = 1000;
				GPIO_write(PIN_RIN, true);
				GPIO_write(PIN_FIN, false);
				timeout = 10000;
			}
			if(flag_ask_for_movement == ASK_UP)
				state = IDLE;
			if(flag_ask_for_movement == ASK_DOWN)
				state = DOWN;
			else if (!timeout || flag_short_press_down || flag_short_press_up || arrived == TRUE|| (t && flag_short_release_up) || flag_ask_for_movement == ASK_STOP){
				arrived = FALSE;
				state = IDLE;
			}
			if (state != UP){        // OUT OF STATE
				GPIO_write(PIN_RIN, false);
				GPIO_write(PIN_FIN, false);
			}
			break;
		case DOWN :
			if (entrance){
				t = 1000;
				GPIO_write(PIN_RIN, false);
				GPIO_write(PIN_FIN, true);
				timeout = 10000;
			}

			if(flag_ask_for_movement == ASK_UP)
				state = UP;
			if(flag_ask_for_movement == ASK_DOWN)
				state = DOWN;
			else if (!timeout || flag_short_press_up || flag_short_press_down || arrived == TRUE || (t && flag_short_release_down) || flag_ask_for_movement == ASK_STOP){
				arrived = FALSE;
				state = IDLE;
			}
			if (state != DOWN ){        // OUT OF STATE
				GPIO_write(PIN_RIN, false);
				GPIO_write(PIN_FIN, false);
			}
			break;
		case IDLE :
			t = 2000;
			if(flag_short_press_down || flag_ask_for_movement == ASK_DOWN)
				state = DOWN;
			else if(flag_short_press_up || flag_ask_for_movement == ASK_UP)
				state = UP;
			break;
		default:
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



/// END NEW CODE ///



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
