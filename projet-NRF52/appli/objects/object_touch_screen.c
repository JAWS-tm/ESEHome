/*
 * object_touch_screen.c
 *
 *  Created on: 22 fevr. 2022
 *      Author: Théo BENARD
 */

#include "../config.h"
#if OBJECT_ID == OBJECT_TOUCH_SCREEN

#include "object_touch_screen.h"
#include "../bsp/ili9341/ili9341_fonts.h"
#include "../bsp/ili9341/nrf_lcd.h"
#include "bsp/ili9341/ili9341.h"
//#include "nrfx_spi.h"
#include "bsp/ili9341/ili9341_xpt2046.h"
#include "../common/parameters.h"
#include "nrf_gpio.h"
#include "../common/gpio.h"

#define COLORMESSAGE 		PARAM_SCREEN_COLOR //ici on peut penser � recuperer la couleur depuis un parametre envoye de la station de base

extern const nrf_lcd_t nrf_lcd_ili9341;

static char title[20];
static Sint16 pX;
static Sint16 pY;
static uint16_t background_color;
static uint16_t background_color_alert;
static uint16_t previous_background_color;
static uint16_t temperature_value;
static uint16_t value_volet;
char text_temperature[20];
static bool_e flag_title_updated = FALSE;

static bool_e change_background_color(void);
static void arrow_menu(void);
static bool_e left_arrow(void);
static bool_e right_arrow(void);
static bool_e touch_screen(void);
static void square_display(void);
static void affichage_volet_roulant(void);
static void affichage_temperature(void);
static void affichage_menu(void);
static void affichage_couleur_ecran(void);
static void affichage_alert(void);

void callback_new_text_0(uint32_t p)
{
	uint8_t * p8;
	p8 = (uint8_t*)(p);

	snprintf(title, 20, "%s", p8);
	flag_title_updated = TRUE;
}

void object_touch_screen_process_main(void)
{
    typedef enum{
    	INIT,
        MENU,
		BACKGROUND_COLOR,
		CHANGE_BACKGROUND_COLOR,
		TEMPERATURE,
		CHANGE_TEMPERATURE,
		VOLET_ROULANT,
		CHANGE_VOLET_ROULANT,
		ALERT
    }state_e;

    static state_e state = INIT;
    static state_e previous_state = INIT;
    static state_e last_state = INIT;
    static state_e previous_state_entrance;
    bool_e entrance = (state != previous_state)?TRUE:FALSE;
    previous_state = state;


    switch(state){
    case INIT:
    	ILI9341_init(); // init l'ecran
    	XPT2046_init(); // init le touchscreen
    	GPIO_configure(MOSFET_PIN, NRF_GPIO_PIN_PULLUP, true); // permet de configurer le transistor
    	ILI9341_rotation_set(NRF_LCD_ROTATE_90); // configurer l'orientation de l'écran
    	GPIO_write(MOSFET_PIN, false);
    	background_color = ILI9341_COLOR_WHITE;
    	background_color_alert = ILI9341_COLOR_RED;
    	temperature_value = 10;
    	value_volet = 0;

    	// communication avec la station de base
    	PARAMETERS_init(); //Initialisation de la communication RF
    	PARAMETERS_enable(PARAM_MODE, 0, FALSE, NULL, NULL);
    	PARAMETERS_enable(PARAM_ACTUATOR_STATE, 0, FALSE, NULL, NULL);

    	PARAMETERS_enable(PARAM_TEXT_PART0, 0, FALSE, &callback_new_text_0, NULL);
    	sprintf(title, "Capteur Chute"); // Detecteur Feu

    	state = MENU;
        break;

    case MENU:
    	if (entrance){
    		previous_state_entrance = state; // recupere la valeur du state pour remettre sur le meme menu avant de recevoir l'alerte
    		affichage_menu();
    	}

		if (touch_screen()){
			if (left_arrow()){
				PARAMETERS_update(PARAM_MODE, 0);
				state = ALERT;
			}
			if (right_arrow()){
				PARAMETERS_update(PARAM_MODE, 1);
				state = VOLET_ROULANT;
			}
		}
    	break;
    case BACKGROUND_COLOR:
    	if (entrance){
    		affichage_couleur_ecran();
    	}
		if (touch_screen()){
			if (left_arrow()){
				state = TEMPERATURE;
			}
			if (right_arrow()){
				state = MENU;
			}
			if (change_background_color()){
				state = CHANGE_BACKGROUND_COLOR;
			}
		}
    	break;

    case CHANGE_BACKGROUND_COLOR:
    	// Permet d'envoyer la valeur de la couleur du fond d'ecran à la station de base pour ensuite le modifier sur l'appli web
    	PARAMETERS_send_param32_to_basestation(PARAM_MODE);
    	state = BACKGROUND_COLOR;
    	break;

    case TEMPERATURE:
    	if (entrance){
    		previous_state_entrance = state; // recupere la valeur du state pour remettre sur le meme menu avant de recevoir l'alerte
    		affichage_temperature();
    	}

		if (touch_screen()){
			if (left_arrow()){
				state = MENU;
			}
			if (right_arrow()){
				state = BACKGROUND_COLOR;
			}

			if (pX > 115 && pX < 150 && pY > 70 && pY < 105){
				if (temperature_value > 0){
					temperature_value -= 1;
					sprintf(text_temperature, "%d", temperature_value);
					strcat(text_temperature, " *C ");
					ILI9341_printf(130,100, &Font_16x26, ILI9341_COLOR_BLACK, background_color, text_temperature);
					//state = CHANGE_TEMPERATURE;
				}
			}
			if (pX > 165 && pX < 200 && pY > 70 && pY < 105){
				if (temperature_value < 40){
					temperature_value += 1;

					sprintf(text_temperature, "%d", temperature_value);
					strcat(text_temperature, " *C ");
					ILI9341_printf(130,100, &Font_16x26, ILI9341_COLOR_BLACK, background_color, text_temperature);
					//state = CHANGE_TEMPERATURE;
				}
			}
		}

        break;
    case CHANGE_TEMPERATURE :
    	state = TEMPERATURE;
    	break;

    case VOLET_ROULANT:
    	if (entrance){
    		previous_state_entrance = state; // recupere la valeur du state pour remettre sur le meme menu avant de recevoir l'alerte
    		affichage_volet_roulant();
		}

		if (touch_screen()){
			if (left_arrow()){
				PARAMETERS_update(PARAM_MODE, 0);
				state = BACKGROUND_COLOR;
			}
			if (right_arrow()){
				PARAMETERS_update(PARAM_MODE, 1);
				state = TEMPERATURE;
			}
			if (pX > 185 && pX < 235 && pY > 80 && pY < 130){
				if (value_volet == 0){
					ILI9341_DrawFilledRectangle(210, 110, 260, 160, ILI9341_COLOR_RED);
					ILI9341_DrawFilledRectangle(85, 110, 135, 160, ILI9341_COLOR_GREEN);
					value_volet = 1;
				}
			}
			if (pX > 60 && pX < 110 && pY > 80 && pY < 130){
				if (value_volet == 1){
					ILI9341_DrawFilledRectangle(210, 110, 260, 160, ILI9341_COLOR_GREEN);
					ILI9341_DrawFilledRectangle(85, 110, 135, 160, ILI9341_COLOR_RED);
					value_volet = 0;
				}
			}
			if (pX > 75 && pX < 225 && pY > 20 && pY < 60){
				PARAMETERS_update(PARAM_MODE, value_volet);
				state = ALERT;
			}
		}

    	break;
    case CHANGE_VOLET_ROULANT:
    	PARAMETERS_send_param32_to_basestation(PARAM_ACTUATOR_STATE);
    	state = VOLET_ROULANT;
    	break;

	case ALERT:
		if (entrance){
			previous_state_entrance = last_state;
			affichage_alert();
		}

		if(flag_title_updated)
		{
			flag_title_updated = FALSE;
			//ILI9341_printf(75,30, &Font_16x26, ILI9341_COLOR_BLACK, background_color_alert, title);
			//ILI9341_printf(60,55, &Font_16x26,ILI9341_COLOR_BLACK, background_color_alert , "Capteur Chute");
		}

		if (touch_screen()){
			if (pX > 75 && pX < 225 && pY > 50 && pY < 90){
				PARAMETERS_update(PARAM_SENSOR_VALUE, 0);
				state = previous_state_entrance;
				PARAMETERS_send_param32_to_basestation(PARAM_ACTUATOR_STATE);
			 }
		}
		break;

    default:
    	break;
    }

    last_state = previous_state;
}

/*
 * @brief cette fonction permet de changer la couleur de fond de l'ecran
 * @return un booleen qui va etre utilise dans une condition afin de detecter ou
 * l'utilisateur a appuyé sur l'ecran et savoir quelle couleur il faut actualiser
 */
bool_e change_background_color(void){
			/* PARAM_SCREEN_COLOR
				0 : green
				1 : orange
				2 : red
				3 : magenta
				4 : white
				5 : yellow
			*/
   	if (pX > 205 && pX < 255 && pY > 105 && pY < 155){
   		debug_printf("VERT");
   			background_color = ILI9341_COLOR_GREEN;
   			if (background_color != previous_background_color){
   				PARAMETERS_update(PARAM_SCREEN_COLOR, 0);
   				return true;
   			}
   		}
   		if (pX > 205 && pX < 255 && pY > 35 && pY < 85){
   			debug_printf("ORANGE");
   			background_color = ILI9341_COLOR_ORANGE;
   			if (background_color != previous_background_color){
   				PARAMETERS_update(PARAM_SCREEN_COLOR, 1);
   				return true;
   			}
   		}

   		if (pX > 135 && pX < 185 && pY > 105 && pY < 155){
   			background_color = ILI9341_COLOR_RED;
   			if (background_color != previous_background_color){
   				PARAMETERS_update(PARAM_SCREEN_COLOR, 2);
   				return true;
   			}
   		}
   		if (pX > 65 && pX < 115 && pY > 105 && pY < 155){
   			background_color = ILI9341_COLOR_MAGENTA;
   			if (background_color != previous_background_color){
   				PARAMETERS_update(PARAM_SCREEN_COLOR, 3);
   				return true;
   			}
   		}
   		if (pX > 135 && pX < 185 && pY > 35 && pY < 85){
   			background_color = ILI9341_COLOR_WHITE;
   			if (background_color != previous_background_color){
   				PARAMETERS_update(PARAM_SCREEN_COLOR, 4);
   				return true;
   			}
   		}
   		if (pX > 65 && pX < 115 && pY > 35 && pY < 85){
   			background_color = ILI9341_COLOR_YELLOW;
   			if (background_color != previous_background_color){
   				PARAMETERS_update(PARAM_SCREEN_COLOR, 5);
   				return true;
   			}
   		}
   		return 0;
   }

/*
 * @brief cette fonction est utiliser sur a plusieurs reprises dans ce fichier elle permet d'afficher
 * les fleches de chaque cote de l'ecran afin de permetttre a l'utilisateur de changer de menu plus facilement
 */
void arrow_menu(void){
// changer de menu vers la gauche
ILI9341_DrawFilledCircle(25,120, 13, ILI9341_COLOR_BLUE);
ILI9341_Putc(20, 112,'<', &Font_11x18, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLUE);

// changer de menu vers la droite
ILI9341_DrawFilledCircle(295,120, 13, ILI9341_COLOR_BLUE);
ILI9341_Putc(292, 112,'>', &Font_11x18, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLUE);
}

/*
 * @brief ces deux fonctions sont lier a la fonction "arrow_menu()" elles permettent de
 * detecter si l'utilisateur appuie sur l'une des deux fleches
 * @return un booleen qui va etre utilise dans une condition afin de detecter ou
 * l'utilisateur a appuyer sur l'ecran et savoir quel menu nouveau menu afficher
 */
bool_e left_arrow(void){
	if (pX > 280 && pX < 320 && pY > 100 && pY < 140){
		return true;
	}
	return 0;
}
bool_e right_arrow(void){
	if (pX > 0 && pX < 60 && pY > 100 && pY < 140){
		return true;
	}
	return 0;
}

/*
 * @brief cette fonction est relier a la fonction "change_background_color()" elle permet d'afficher
 * sur l'ecran les differentes couleurs disponible pour changer la couleur de fond de l'ecran
 */
void square_display(void){
// carre pour changer la couleur du fond d'ecran
ILI9341_DrawFilledRectangle(65, 85, 115, 135, ILI9341_COLOR_GREEN);
ILI9341_DrawRectangle(65, 85, 115, 135, ILI9341_COLOR_BLACK);
ILI9341_DrawFilledRectangle(135, 85, 185, 135, ILI9341_COLOR_RED);
ILI9341_DrawRectangle(135, 85, 185, 135, ILI9341_COLOR_BLACK);
ILI9341_DrawFilledRectangle(205, 85, 255, 135, ILI9341_COLOR_MAGENTA);
ILI9341_DrawRectangle(205, 85, 255, 135, ILI9341_COLOR_BLACK);

ILI9341_DrawFilledRectangle(65, 155, 115, 205, ILI9341_COLOR_ORANGE);
ILI9341_DrawRectangle(65, 155, 115, 205, ILI9341_COLOR_BLACK);
ILI9341_DrawFilledRectangle(135, 155, 185, 205, ILI9341_COLOR_WHITE);
ILI9341_DrawRectangle(135, 155, 185, 205, ILI9341_COLOR_BLACK);
ILI9341_DrawFilledRectangle(205, 155, 255, 205, ILI9341_COLOR_YELLOW);
ILI9341_DrawRectangle(205, 155, 255, 205, ILI9341_COLOR_BLACK);
}

/*
 * @brief cette fonction affiche le menu du volet roulant
 */
void affichage_volet_roulant(void){

	ILI9341_Fill(background_color);
	ILI9341_printf(65,30, &Font_16x26, ILI9341_COLOR_BLACK, background_color, "Volet Roulant");

	//fleche pour switch de menu
	arrow_menu();

	if (value_volet == 0){
		ILI9341_DrawFilledRectangle(85, 110, 135, 160, ILI9341_COLOR_RED);
		ILI9341_DrawFilledRectangle(210, 110, 260, 160, ILI9341_COLOR_GREEN);
	}else if  (value_volet == 1){
		ILI9341_DrawFilledRectangle(210, 110, 260, 160, ILI9341_COLOR_RED);
		ILI9341_DrawFilledRectangle(85, 110, 135, 160, ILI9341_COLOR_GREEN);
	}

	ILI9341_printf(60,70, &Font_16x26, ILI9341_COLOR_BLACK, background_color, "Ouvert");
	ILI9341_DrawRectangle(85, 110, 135, 160, ILI9341_COLOR_BLACK);

	ILI9341_printf(190,70, &Font_16x26, ILI9341_COLOR_BLACK, background_color, "Ferme");
	ILI9341_DrawRectangle(210, 110, 260, 160, ILI9341_COLOR_BLACK);

	ILI9341_printf(98,190, &Font_16x26, ILI9341_COLOR_BLACK, background_color, "Confirmer");
	ILI9341_DrawRectangle(95, 180, 245, 220, ILI9341_COLOR_BLACK);
}

/*
 * @brief cette fonction affiche le menu de la temperature
 */
void affichage_temperature(void){
   ILI9341_Fill(background_color);
	//fleche pour switch de menu
	arrow_menu();

	ILI9341_printf(70,30, &Font_16x26, ILI9341_COLOR_BLACK, background_color, "Temperature");

	ILI9341_DrawRectangle(120, 135, 155, 170, ILI9341_COLOR_BLACK);
	ILI9341_Putc(130, 140,'+', &Font_16x26, ILI9341_COLOR_BLACK, background_color);


	ILI9341_DrawRectangle(170, 135, 205, 170, ILI9341_COLOR_BLACK);
	ILI9341_Putc(180, 141,'-', &Font_16x26, ILI9341_COLOR_BLACK, background_color);


	sprintf(text_temperature, "%d", temperature_value);
	strcat(text_temperature, " *C");
	ILI9341_printf(130,100, &Font_16x26, ILI9341_COLOR_BLACK, background_color, text_temperature);
}

/*
 * @brief cette fonction affiche le menu principal
 */
void affichage_menu(void){
    ILI9341_Fill(background_color);
	ILI9341_printf(135,30, &Font_16x26,ILI9341_COLOR_BLACK, background_color , "MENU");
	ILI9341_printf(65,30, &Font_16x26,ILI9341_COLOR_BLACK, background_color , "Bienvenue");

	//fleche pour switch de menu
	arrow_menu();
}

/*
 * @brief cette fonction affiche le menu pour changer la couleur de fond
 */
void affichage_couleur_ecran(void){
	   ILI9341_Fill(background_color);
	   previous_background_color = background_color;
	   	ILI9341_printf(61,30, &Font_16x26, ILI9341_COLOR_BLACK, background_color, "Couleur Ecran");

	   	arrow_menu(); //fleche pour switch de menu
	   	square_display(); // affichage de toutes les couleurs pour changer le fond d'ecran
   }

/*
 * @brief cette fonction detecte l'appui de l'utilisateur sur l'ecran
 * @return un booleen true si l'utilisateur a appuyer qui est ensuite
 * utiliser dans plusieurs conditions
 */
bool_e touch_screen(void){
	if (XPT2046_getAverageCoordinates(&pX, &pY, 10 , XPT2046_COORDINATE_SCREEN_RELATIVE)){
		return true;
	}
	return 0;
}

/*
 * @brief cette fonction affiche l'alerte
 * TODO relier cette alerte en fonction de l'alerte qu'on recevra de la station de base
 */
void affichage_alert(void){
	ILI9341_DrawFilledRectangle(55, 45, 275, 200, background_color_alert);
	ILI9341_DrawRectangle(55, 45, 275, 200, ILI9341_COLOR_BLACK);
	ILI9341_printf(60,55, &Font_16x26,ILI9341_COLOR_BLACK, background_color_alert , "Capteur Chute");
	ILI9341_printf(110,100, &Font_16x26,ILI9341_COLOR_BLACK, background_color_alert , "ALERTE !");
	ILI9341_printf(98,160, &Font_16x26, ILI9341_COLOR_BLACK, background_color_alert, "Confirmer");
	ILI9341_DrawRectangle(95, 150, 245, 190, ILI9341_COLOR_BLACK);
}


#endif
