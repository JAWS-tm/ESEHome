/*
 * object_smart_light.c
 *
 *  Created on: 10 févr. 2021
 *      Author: Thomas
 */
#include "../config.h"
#include "appli/common/gpio.h"
#include "object_smart_light.h"
#include "appli/common/buttons.h"
#include "appli/common/parameters.h"
#include "appli/common/serial_dialog.h"
#include "appli/common/systick.h"

#if OBJECT_ID == OBJECT_SMART_LIGHT
#define STEPS  5

//variables d'encodeur
#define pinA INPUT_A_ENCODEUR_ROTATIF
#define pinB INPUT_B_ENCODEUR_ROTATIF
#define pinC INPUT_SW_ENCODEUR_ROTATIF
int compteur = 0 ;
static bool_e etatA ;
static bool_e dernierEtatA ;

//variables de luminosité
static bool_e appui;
int luminosity = 0;
int maxLuminosity = 255;
int luminosity_received = 0;
unsigned char bright; // your brightness - range 0 (dark) to 255 (lght)
static unsigned char i = 0;


//variables de temps
static uint8_t seconds = 0;
static uint8_t minutes = 0;
static uint8_t hours = 0;
static uint32_t seconds_since_midnight = 0;

typedef enum{
			START,
			ALLUMAGE,
			FROID,
			CHAUD,
			ETEINT,
			AMBIANCE,
			MODE_NB
		}mode_e;


static mode_e mode = START;


/*time_t now;
char timeInfos;*/


/*
 * Smart Light est une technologies alliant plusieurs utilisations:
 * 1) Utilisation manuelle: à l'aide d'un bouton "local", l'utilisateur peut enclencher 4 modes d'éclairage
 * - Mode allumage: toutes les LED sont allumées
 * - Mode froid: seules les LED froides sont allumées
 * - Mode chaud: seules les LED chaudes sont allumées
 * - Mode éteint: aucune LED n'est allumée
 * - Mode ambiance: alternance chaud froid
 * 2) Utilisation automatique avec l'heure en temps réel (timer): (en cours)
 * - Le matin à ?? heure: les LED s'allument progressivement via 5 stades de luminosité ascendants
 * - Le soir à ?? heure: les LED s'éteignent progressivement via 5 stades de luminosité descendants
 * 3) Utilisation selon un mode "automatique" à l'aide d'un bouton "network": (en cours - le capteur lumière ne marche pas)
 * - Smart Light récupère les données recueillies par un capteur de luminosité à distance et
 *   allume/éteint les lumières à partir d'un certain seuil
 * 4) Réglage manuel avec encodeur rotatif (en cours)
 */

bool_e DetectAppui(void) //Appui sur le bouton local
{
	appui = TRUE;
	return appui;
}

/*
char hour(now){ //retourne l'heure en temps réel
	now = time(NULL);
	struct tm * timeInfos = localtime(&now);

	printf( "Local time : %02d:%02d:%02d\n",  timeInfos->tm_hour, timeInfos->tm_min, timeInfos->tm_sec);
	return timeInfos;
}*/

// Encodeur rotatif
/*
void setup() {
	dernierEtatA = digitalRead(pinA);
	tempsA = millis();
}

void loop() {

	etatA = digitalRead(pinA);

	if( etatA != dernierEtatA ){
		if( abs(millis() - tempsA) > 50 ){
			if(digitalRead(pinB) != dernierEtatA){
				compteur--;
				analogWrite(MOSFET_LED_FROIDE2, luminosity);
				analogWrite(MOSFET_LED_FROIDE, luminosity);
				analogWrite(MOSFET_LED_FROIDE2, luminosity);
				analogWrite(MOSFET_LED_FROIDE, luminosity);
				delay(10);
				luminosity = luminosity+(maxLuminosity/compteur);
			}
			else{
				compteur++;
				analogWrite(MOSFET_LED_FROIDE2, luminosity);
				analogWrite(MOSFET_LED_FROIDE, luminosity);
				analogWrite(MOSFET_LED_FROIDE2, luminosity);
				analogWrite(MOSFET_LED_FROIDE, luminosity);
				delay(10);
				luminosity = luminosity-(maxLuminosity/compteur);
			}
		tempsA = millis();
		}
	dernierEtatA = etatA ;
	}

	// delay pour tester
	delay(10000);

}
*/
// Fin

void Configuration(void) { //configure le pin des mosfets en sortie
	GPIO_configure(MOSFET_LED_FROIDE2, NRF_GPIO_PIN_NOPULL, TRUE);
	GPIO_configure(MOSFET_LED_FROIDE, NRF_GPIO_PIN_NOPULL, TRUE);
	GPIO_configure(MOSFET_LED_CHAUDE2, NRF_GPIO_PIN_NOPULL, TRUE);
	GPIO_configure(MOSFET_LED_CHAUDE, NRF_GPIO_PIN_NOPULL, TRUE);
	BUTTONS_add(BUTTON_USER0, PIN_BUTTON_LOCAL, TRUE, &DetectAppui,NULL,NULL,NULL);
}


void OBJECT_SMART_LIGHT_UPDATED_MODE_callback(int32_t new_mode){ //je ne sais pas
	if(new_mode < MODE_NB)
	{
		debug_printf("nouveau mode envoyÃ© depuis la station de base : %lx\n", mode);
		mode = (mode_e)new_mode;
	}
}


void Eteindre(void){ //on éteint l'ensemble des LED
	GPIO_write(MOSFET_LED_FROIDE2, FALSE);
	GPIO_write(MOSFET_LED_FROIDE, FALSE);
	GPIO_write(MOSFET_LED_CHAUDE2, FALSE);
	GPIO_write(MOSFET_LED_CHAUDE, FALSE);
}

void AllumageComplet(void){ //on allume l'ensemble des LED
	GPIO_write(MOSFET_LED_FROIDE2, TRUE);
	GPIO_write(MOSFET_LED_FROIDE, TRUE);
	GPIO_write(MOSFET_LED_CHAUDE2, TRUE);
	GPIO_write(MOSFET_LED_CHAUDE, TRUE);
}

void AllumageFroid(void){ //on allume seulement les LED froides
	GPIO_write(MOSFET_LED_FROIDE2, TRUE);
	GPIO_write(MOSFET_LED_FROIDE, TRUE);
}

void AllumageChaud(void){ //on allume seulement les LED chaudes
	GPIO_write(MOSFET_LED_CHAUDE2, TRUE);
	GPIO_write(MOSFET_LED_CHAUDE, TRUE);
}

void Ambiance(void){

	GPIO_write(MOSFET_LED_CHAUDE2, TRUE);
	GPIO_write(MOSFET_LED_FROIDE2, TRUE);
	SYSTICK_delay_ms(100);
	GPIO_write(MOSFET_LED_CHAUDE2, FALSE);
	GPIO_write(MOSFET_LED_FROIDE2, FALSE);
	GPIO_write(MOSFET_LED_FROIDE, TRUE);
	GPIO_write(MOSFET_LED_CHAUDE, TRUE);
	SYSTICK_delay_ms(100);
	GPIO_write(MOSFET_LED_FROIDE, FALSE);
	GPIO_write(MOSFET_LED_CHAUDE, FALSE);
}

int process_ms()
{
	static uint32_t ms = 0;
	ms = (ms+1)%1000;
	if(!ms)
	{
		seconds = (seconds+1)%60;
		if(!seconds)
		{
			minutes = (minutes+1)%60;
			if(!minutes){
				hours = (hours+1)%60;
			}
		}
		seconds_since_midnight = seconds + minutes*60 + hours*3600;
	}
	debug_printf("print : %d", seconds_since_midnight);
	return seconds_since_midnight;
}

/* pour le matin et le soir en incrémentation et décrémentation mais bon 
void Matin(timeInfos) { //luminosité progressive pour se réveiller (5 incrémentations --> 5 minutes)

}

void Soir(void) { //luminosité progressive pour s'endormir (5 incrémentations --> 5 minutes)
	luminosity = maxLuminosity; //1er stade de luminosité (maximale)
	if(timeInfos == '22:56:00') { //2e stade de luminosité (forte)
	  luminosity = luminosity - (maxLuminosity/STEPS); //3e stade de luminosité (moyenne)
	}
	if(timeInfos == '22:57:00') {
	  luminosity = luminosity - (maxLuminosity/STEPS); //4e stade de luminosité (forte)
	}
	if(timeInfos == '22:58:00') {
		  luminosity = luminosity - (maxLuminosity/STEPS); //4e stade de luminosité (forte)
		}
	if(timeInfos == '22:59:00')
	{
	  Eteindre(); //5e stade de luminosité (maximale)
	}
}
*/



void Smart_light_Main(void){
	{

		/*static mode_e previous_mode = DEBUT; //Sauvegarder l'Ã©tat prÃ©cÃ©dent.
		bool_e entrance = (mode != previous_mode)?TRUE:FALSE;*/

		switch(mode)
			{
				case START: //le cas initial, tout est éteint, on configure
					/*
					 * initial:
					 * - configuration
					 * - paramètres établis
					 */
					//Systick_add_callback_function(&process_ms);
					Configuration();
					PARAMETERS_enable(PARAM_MODE,START, TRUE, &OBJECT_SMART_LIGHT_UPDATED_MODE_callback, NULL);
					mode = ALLUMAGE;
					break;

				case ALLUMAGE:
					/*
					 * mode 1:
					 * - les LED sont toutes allumées
					 * - quand on appuie on passe au mode 2
					 * - quand il est ?? heure, on passe en mode allumage chaud
					 * - quand il est ?? heure, on passe en mode eteindre
					 */
					AllumageComplet();
							if(appui)
							{
								appui = FALSE;
								Eteindre();
								mode = FROID;
							}
							if(seconds_since_midnight == 64800){ //correspond à 18h10 pour test
								AllumageChaud();
							}
							if(seconds_since_midnight == 64900){
								Eteindre();
							}
					break;

				case FROID:
					/*
					 * mode 2:
					 * - seules les LED froides sont allumées
					 * - quand on appuie on passe au mode 3
					 * - quand il est ?? heure, on passe en mode allumage chaud
					 * - quand il est ?? heure, on passe en mode eteindre
					 */
					AllumageFroid();
							if(appui)
							{
								appui = FALSE;
								Eteindre();
								mode = CHAUD;
							}
							if(seconds_since_midnight == 64800){
								AllumageChaud();
							}
							if(seconds_since_midnight == 64900){
								Eteindre();
							}
					break;

				case CHAUD:
					/*
					 * mode 3:
					 * - seules les LED chaudes sont allumées
					 * - quand on appuie on passe au mode 4
					 * - quand il est ?? heure, on passe en mode allumage chaud
					 * - quand il est ?? heure, on passe en mode eteindre
					 */
					AllumageChaud();
							if(appui)
							{
								appui = FALSE;
								Eteindre();
								mode = ETEINT;
							}
							if(seconds_since_midnight == 64800){
								AllumageChaud();
							}
							if(seconds_since_midnight == 64900){
								Eteindre();
							}
					break;

				case ETEINT:
					/*
					 * mode 4:
					 * - les LED sont éteintes
					 * - quand on appuie on passe au mode 5
					 * - quand il est ?? heure, on passe en mode allumage chaud
					 * - quand il est ?? heure, on passe en mode eteindre
					 */
					Eteindre();
							if(appui)
								{
								appui = FALSE;
								mode = AMBIANCE;
								}
							if(seconds_since_midnight == 64800){
								AllumageChaud();
							}
							if(seconds_since_midnight == 64900){
								Eteindre();
							}
					break;

				case AMBIANCE:
				/*
				 * mode 5:
				 * - ambiance
				 * - quand on appuie on passe au mode 1
				 * - quand il est ?? heure, on passe en mode allumage chaud
				 * - quand il est ?? heure, on passe en mode eteindre
				 */
				Ambiance();
						if(appui)
							{
							appui = FALSE;
							mode = ALLUMAGE;
							}
						if(seconds_since_midnight == 64800){
							AllumageChaud();
						}
						if(seconds_since_midnight == 64900){
							Eteindre();
						}
				break;
			}
	}
}


#endif