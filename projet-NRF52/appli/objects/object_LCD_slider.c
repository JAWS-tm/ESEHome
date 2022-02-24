
/*
 * object_LCD_slider.c
 *
 *  Created on: janv to feb 2022
 *      Author: Florentin LEPELTIER
 */

#include "../config.h"
/*
 *  LCD SLIDER OBJECT :
 *  The lcd slider is composed of a rotary encoder (slider) and a lcd2x16 screen.
 *  When you turn the slider, the lcd should display the value corresponding to the counter incremented by the slider according to its rotation direction (clockwise or counterclockwise).
 *	Sensors info :
  	ENCODER : The slider is composed of three signals coming back on 3 pins of the NRF : Output_A(P0.12) / Output_B(P0.11) / Switch_output(P0.10)
  		-When the slider is turned clockwise, A!=B
  		-When it turns counterclockwise, A==B
  		-When the switch is pressed, the output pin goes from high to low (according to the pulling configuration you set)
  	LCD : The LCD is wired on the following pins : Enable(P0.25) / RW(P0.26) / RS(P0.27) / D7(P0.28) / D6(P0.29) / D5(P0.30) --> Updated to 9 / D4(P0.31)
  	INFO : Pins are defined in the config.h file.
*/

#if OBJECT_ID == OBJECT_LCD_SLIDER

#include "object_LCD_slider.h"
#include "../common/gpio.h"
#include "../common/buttons.h"
#include "../common/leds.h"
#include "../common/parameters.h"
#include "../common/systick.h"
#include "../bsp/lcd2x16/lcd2x16.h"
#include "object_LCD_slider.h"
#include "nrf_drv_gpiote.h"
#include "app_error.h"

typedef enum
	{
		INIT,
		RUN,
		IDLE,
	}mode_e;

/************************PRIVATE VAR DEFINITIONS****************************/
static uint8_t slider_display;
static uint32_t sending_timer;
static bool_e update_display;
static bool_e value_sent;
static uint8_t slider_A; //Cette variable peut changer via une it ext (on ne prend pas de raccourci)
static uint8_t slider_A_last_state;
static bool_e FLAG_DISPLAY_SENT = false;
static bool_e FLAG_IT_SLIDER_SWITCH = false;
static bool_e FLAG_IT_SLIDER_A = false;
static volatile uint32_t timer_extit_slider_switch = 0;
static volatile uint32_t timer_extit_slider_A = 0;

/*******************PRIVATE FUNCTIONS PROTOTYPES***************************/
//init
static void LCD_SLIDER_complete_init(void);
static void LCD_SLIDER_lcd_init(void);
static void LCD_SLIDER_encoder_init(void);
static void LCD_SLIDER_extit_init(void);
static void LCD_SLIDER_leds_init(void);
static void LCD_SLIDER_buttons_init(void);
static void LCD_SLIDER_parameters_init(void);
//Background
static void LCD_SLIDER_state_machine(void);
//Display
static void LCD_SLIDER_update_display(void);
static uint8_t LCD_SLIDER_get_slider_display_range(void);
//Callbacks
static void LCD_SLIDER_movement_callback_extit(void);
static void LCD_SLIDER_short_press_button_callback_event(void);
static void LCD_SLIDER_switch_button_pressed_callback_event(void);
static void LCD_SLIDER_parameter_read_callback_event(void);
//Extit
static void LCD_SLIDER_set_extit_callback(nrf_drv_gpiote_pin_t pin, pin_type_e pin_type, nrf_drv_gpiote_evt_handler_t callback_function);
//Utils
static uint16_t process_ms(void);

/************************INIT FUNCTIONS****************************/

/*
  * @brief Fonction initialisant complètement l'objet via l'appel des sous fonctions d'init
  */
void LCD_SLIDER_complete_init(void){
	LCD_SLIDER_lcd_init();
	LCD_SLIDER_encoder_init();
	LCD_SLIDER_leds_init();
	LCD_SLIDER_buttons_init();
	LCD_SLIDER_parameters_init();
	slider_display = 0;
	sending_timer = TIMER_BETWEEN_VALUE_SENDING;
	update_display = false;
	value_sent = false;
	slider_A = 0;
	slider_A_last_state = GPIO_read(LCD_A_SLIDER_PIN);
	Systick_add_callback_function(&process_ms);
	LCD2X16_printf("SLIDER LCD READY");
	debug_printf("Appli initialised\n");
};

/*
  * @brief Fonction initialisant le LCD sur ses broches respectives. On en profite pour activer le convertisseur Boost 5V qui alimente le LCD.
  */
void LCD_SLIDER_lcd_init(void){
	//Enable 5V boost converter to power on the screen
	GPIO_configure(BOOST_ENABLE_PIN, NRF_GPIO_PIN_PULLUP, 1);
	GPIO_write(BOOST_ENABLE_PIN, 1);
	LCD2X16_init();
}

/*
  * @brief Fonction initialisant l'encodeur digital (3 sorties : A, B et Switch) sur des it externes pour l'incrementation du slider
  */
void LCD_SLIDER_encoder_init(void){
	GPIO_write(LCD_A_SLIDER_PIN, 0);
	GPIO_write(LCD_B_SLIDER_PIN, 0);
	GPIO_write(LCD_SWITCH_SLIDER_PIN, 0);
	GPIO_configure(LCD_A_SLIDER_PIN, NRF_GPIO_PIN_PULLUP, 0);
	GPIO_configure(LCD_B_SLIDER_PIN, NRF_GPIO_PIN_PULLUP, 0);
	GPIO_configure(LCD_SWITCH_SLIDER_PIN, NRF_GPIO_PIN_PULLUP, 0);
	LCD_SLIDER_extit_init();
}

/*
  * @brief Fonction qui initialise les interruptions sur les 3 sorties du slider
  * @pre   Les 3 sorties du slider doivent avoir été préalablement configurées et définies
  */
void LCD_SLIDER_extit_init(){
	//Init NRF SDK gpiote module
	ret_code_t err_code;
	err_code = nrf_drv_gpiote_init();
	APP_ERROR_CHECK(err_code);
	//Extit slider switch config
	LCD_SLIDER_set_extit_callback(LCD_SWITCH_SLIDER_PIN, SWITCH, LCD_SLIDER_switch_button_pressed_callback_event);
	LCD_SLIDER_set_extit_callback(LCD_A_SLIDER_PIN, A, LCD_SLIDER_movement_callback_extit);

}

/*
  * @brief Fonction initialisant les LEDs de l'objet (network + battery)
  */
void LCD_SLIDER_leds_init(void){
	LED_add(LED_ID_NETWORK, PIN_LED_NETWORK);
	LED_add(LED_ID_BATTERY, PIN_LED_BATTERY);
}

/*
  * @brief Fonction initialisant le bouton network de l'objet
  */
void LCD_SLIDER_buttons_init(void){
	BUTTONS_add(BUTTON_NETWORK, PIN_BUTTON_NETWORK, TRUE, &LCD_SLIDER_short_press_button_callback_event, NULL, NULL, NULL);
}

void LCD_SLIDER_parameters_init(void){
	PARAMETERS_enable(PARAM_SENSOR_VALUE, 0, 0, NULL, &LCD_SLIDER_parameter_read_callback_event);
}

/************************BACKGROUND FUNCTIONS****************************/

/*
  * @brief Seule fonction publique du module appelée dans le main. Elle permet de lancer l'execution de la tâche de fond du module
  */
void LCD_SLIDER_process_main(void){
	LCD_SLIDER_state_machine();
};

/*
  * @brief Fonction appelée en tâche de fond. Cette machine à état gère les différents modes
  */
void LCD_SLIDER_state_machine(void){
	static mode_e state  = INIT;
	switch(state){
	case INIT :
		LCD_SLIDER_complete_init();
		state = RUN;
		debug_printf("Switching to 'RUN' mode\n");
		break;
	case RUN :
		if(update_display){
			LCD_SLIDER_update_display();
			update_display = false;
		}
		break;
	case IDLE :
		break;
	default :
		break;
	}
};

/**********************************DISPLAY FUNCTIONS************************************/

/*
  * @brief Cette fonction met à jour l'affichage du compteur incrémenté par le slider
  * @pre   L'écran lcd2x16 doit avoir été initialisé en amont
  */
void LCD_SLIDER_update_display(void){
	if(FLAG_DISPLAY_SENT){
		LCD2X16_printf("SPEED : %d%% <%d>", LCD_SLIDER_get_slider_display_range(), (uint32_t)sending_timer/1000);
		debug_printf("SENDING TIMER : %d\n", (uint32_t)sending_timer/1000);
	}
	else{
		LCD2X16_printf("SPEED : %d%%", LCD_SLIDER_get_slider_display_range());
		debug_printf("Value : %d\n", LCD_SLIDER_get_slider_display_range());
	}
}

uint8_t LCD_SLIDER_get_slider_display_range(void){
	uint8_t ret = 0;
	ret = (uint8_t)((slider_display/254.0)*100.0);
	return ret;
}

/**********************************CALLBACK FUNCTIONS************************************/

/*
  * @brief Cette fonction est appelée par une interruption ext dès que le slider tourne
  * @pre   Les broches du NRF sur lesquelles sont reliées les sorties A et B du slider doivent préalablement être configurées
  */
void LCD_SLIDER_movement_callback_extit(void){
	if(FLAG_IT_SLIDER_A && !value_sent){
		slider_A = GPIO_read(LCD_A_SLIDER_PIN);
		if(slider_A!=slider_A_last_state){
			if(GPIO_read(LCD_B_SLIDER_PIN)!=slider_A){ //ie clockwise
				if((slider_display+1)<=254){ //Block the maximum value
					slider_display++;
					debug_printf("+ : %d\n", slider_display);
				}
			}
			else{ //ie counterclockwise
				if((slider_display-1)>=0){ //Block the minimum value
					slider_display--;
					debug_printf("- : %d\n", slider_display);
				}
			}
			slider_A_last_state = slider_A;
			update_display = true;
		}
		FLAG_IT_SLIDER_A = false;
	}
}

/*
  * @brief Cette fonction est appelée lorsque qu'un appui court est détecté sur le bouton network
  * @pre   Il faut préalablement avoir initialisé le bouton network et y avoir renseigné cette fonction de callback (via BUTTONS_add())
  */
void LCD_SLIDER_short_press_button_callback_event(void){
	debug_printf("Network button has been shortly pressed\n");
	//RF_DIALOG_send_msg_id_to_object(OBJECT_BASE_STATION, PING, 0, NULL);

}

/*
  * @brief Cette fonction est appelée lorsque qu'un appui est détecté sur le switch du slider
  * @pre   Il faut préalablement avoir initialisé la broche du NRF connectée au bouton
  */
void LCD_SLIDER_switch_button_pressed_callback_event(void){
	//Send slider value to the server
	if(FLAG_IT_SLIDER_SWITCH && !value_sent){
		//RF_DIALOG_send_msg_id_to_object(recipient_e obj_id,msg_id_e msg_id, uint8_t datasize, uint8_t * datas);
		//RF_DIALOG_send_msg_id_to_object(OBJECT_BASE_STATION, PING, 0, NULL);
		//RF_DIALOG_send_msg_id_to_basestation(PARAMETER_IS, 5, slider_display); ?//tab 5 donnï¿½es
		debug_printf("Switch button pressed\n");
		debug_printf("Slider value : %d\n", slider_display);
		PARAMETERS_update(PARAM_SENSOR_VALUE, LCD_SLIDER_get_slider_display_range());
		PARAMETERS_send_param32_to_basestation(PARAM_SENSOR_VALUE);
		value_sent = true;
		FLAG_DISPLAY_SENT = true;
		sending_timer = TIMER_BETWEEN_VALUE_SENDING;
		FLAG_IT_SLIDER_SWITCH = false;
	}
}

/*
  * @brief Cette fonction est appelée lorsque qu'une lecture d'un parametre est effectuee ou demandee par la RF
  */
void LCD_SLIDER_parameter_read_callback_event(void){
	debug_printf("Slider value parameter has been read");
}

/**********************************EXTIT FUNCTIONS************************************/

/*
  * @brief   Fonction permettant de paramétrer des interruptions sur des broches particulières du NRF
  * @pre     Le module gpiote ainsi que la pin associée doit avoir été initialisé(e) avant l'appel de cette fonction
  * @params  pin (pin concerné), pin_type (la broche correspondante - le switch ou A), callback_function (c'est explicite).
  */
void LCD_SLIDER_set_extit_callback(nrf_drv_gpiote_pin_t pin, pin_type_e pin_type, nrf_drv_gpiote_evt_handler_t callback_function){
	ret_code_t err_code;
	nrf_drv_gpiote_in_config_t in_config = GPIOTE_CONFIG_IN_SENSE_HITOLO(true);
	switch(pin_type){
		case SWITCH :	in_config.sense = NRF_GPIOTE_POLARITY_HITOLO;break;
		case A :		in_config.sense = NRF_GPIOTE_POLARITY_TOGGLE;break;
		default :		in_config.sense = NRF_GPIOTE_POLARITY_TOGGLE;break;
		}
	in_config.pull = NRF_GPIO_PIN_PULLUP;
	err_code = nrf_drv_gpiote_in_init(pin, &in_config, callback_function);
	APP_ERROR_CHECK(err_code);
	nrf_drv_gpiote_in_event_enable(pin, true);
}

/*****************************************UTILS***************************/
/*
 * @brief  Fonction qui sert de compteur pour un délai
 * @pre	  "Systick_add_callback_function(&process_ms)" doit être appelée en amont si l'on souhaite que cette fonction soit appelee toutes les ms
 * @info   Ce timer agit sur les interruptions externes liées au bouton switch du slider. Elle empêche que deux IT trop proches soient détectées.
 */
uint16_t process_ms(void){
	//EXTIT SLIDER SWITCH
	if(!timer_extit_slider_switch)
	{
		timer_extit_slider_switch = TIMER_BETWEEN_VALUE_SENDING;
		FLAG_IT_SLIDER_SWITCH = TRUE;
	}
	timer_extit_slider_switch--;
	//EXTIT SLIDER A
	if(!timer_extit_slider_A)
		{
			timer_extit_slider_A = 10;
			FLAG_IT_SLIDER_A = TRUE;
		}
	timer_extit_slider_A--;
	//Timer when a value has been sent
	if(value_sent)
	{
		sending_timer--;
		if(sending_timer==1000 || sending_timer==2000 || sending_timer==3000 || sending_timer==4000 || sending_timer==5000) //Display the timer each second
			update_display = true;
		if(!sending_timer)
		{
			value_sent = false;
			FLAG_DISPLAY_SENT = false;
			update_display = true;
		}
	}

	return 0;
}

#endif

