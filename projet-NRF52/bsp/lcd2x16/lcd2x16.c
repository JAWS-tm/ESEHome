/**
 * @date 	10/02/2022
 * @author  Florentin LEPELTIER
 * Ce driver a �t� adapt� au module NRF via la SDK. La version originale est con�ue pour �C STM32. Il est incomplet et n'utilise qu'une seule des deux lignes du LCD en mode 4-bits. C'est du bricolage comme on en a jamais vu.
 * @INFOS IMPORTANTES :
 * Les pins de commande doivent �tre en pulldown de pr�f�rence (elles servent � set des configurations sp�cifiques � l'�cran --> Cf datasheet...)
 * ATTENTION : /!\ M�me non utilis�es, les pins de data D0-D3 doivent �tre reli�es au GND, sans quoi l'�cran sera incapable de'interpr�ter certaines commandes...
 * Certaines fonctions ont �t� reprises ici mais ne fonctionnement pas correctement...Il serait n�cessaire de revoir le driver afin de l'adapter enti�rement et non � moiti�.
 * Toutes les fonctions developp�es ici prennent en compte l'utilisation de l'�cran uniquement en mode 4 bits.
 * Pour plus d'informatiins, il est n�cessaire de lire et de comprendre la datasheet
 */
#include "../appli/config.h"

#if USE_SCREEN_LCD2X16

#include "lcd2x16.h"
#include "../appli/common/macro_types.h"
#include <stdarg.h>
#include <stdio.h>
#include "../appli/common/gpio.h"
#include "./appli/common/systick.h"
//Portage...
#define GPIO_SET_OUTPUT(pin)		GPIO_configure(pin, GPIO_PIN_CNF_PULL_Pulldown, true)
#define GPIO_SET_INPUT(pin)			GPIO_configure(pin, GPIO_PIN_CNF_PULL_Pulldown, false)
#define GPIO_WRITE(pin, value) 		GPIO_write(pin, value)
#define GPIO_READ(pin)				GPIO_read(pin)
#define DELAY_MS(x)					SYSTICK_delay_ms(x)

/**
 * Adresse de la deuxi�me ligne de l'�cran LCD.
 *
 * Adresse dans la RAM interne de l'�cran LCD du premier caract�re de la deuxi�me ligne.
 */
#define LCD2X16_LINE_TWO_AD 0x40

//NEW LIBRARY FUNCTIONS
static void LCD2X16_set_command_pins_to_output(void);
static void LCD2X16_set_data_pins_to_output(void);
static void LCD2X16_send_config_command(bool_e D4_value, bool_e D5_value, bool_e D6_value, bool_e D7_value);
static void LCD2X16_write_data(bool_e D4_value, bool_e D5_value, bool_e D6_value, bool_e D7_value, bool_e D4_2nd_value, bool_e D5_2nd_value, bool_e D6_2nd_value, bool_e D7_2nd_value);
static void LCD2X16_validate_data(void);
static void LCD2X16_set_all_pins_to_zero(void);
static void LCD2X16_validate_data(void);
static void LCD2X16_config_four_bit_mode_one_line(void);
static void LCD2X16_config_display_on_no_cursor(void);
static void LCD2X16_clear_display(void);
static void LCD2X16_return_home(void);
//STM32 LIBRARY
static uint8_t LCD2X16_getByte(uint8_t rs);
static void LCD2X16_sendNibble(unsigned char n);
static void LCD2X16_sendByte( unsigned char rs, unsigned char n);

/*=================================================================================================*/

/*
 * Cette fonction blocante a pour but de vous aider � appr�hender les fonctionnalit�s de ce module logiciel.
 */
void LCD2X16_demo(void)
{
	LCD2X16_init();
	LCD2X16_printf("LCD2x16 - demo");
	while(1)
	{

	}
}

void LCD2X16_set_command_pins_to_output(void){
	// Configuration des ports de commande et de donn�es en �criture
	GPIO_SET_OUTPUT(PIN_RW);
	GPIO_SET_OUTPUT(PIN_RS);
	GPIO_SET_OUTPUT(PIN_E);
}

void LCD2X16_set_data_pins_to_output(void){
	GPIO_SET_OUTPUT(PIN_DATA_0);
	GPIO_SET_OUTPUT(PIN_DATA_1);
	GPIO_SET_OUTPUT(PIN_DATA_2);
	GPIO_SET_OUTPUT(PIN_DATA_3);
}
//@pre : les pins de commande doivent �tre config en sorties
void LCD2X16_send_config_command(bool_e D4_value, bool_e D5_value, bool_e D6_value, bool_e D7_value){
	GPIO_WRITE(PIN_DATA_0, D4_value);
	GPIO_WRITE(PIN_DATA_1, D5_value);
	GPIO_WRITE(PIN_DATA_2, D6_value);
	GPIO_WRITE(PIN_DATA_3, D7_value);
	DELAY_MS(5);
	LCD2X16_validate_data(); //ie press enable
	DELAY_MS(5);

}

void LCD2X16_write_data(bool_e D4_value, bool_e D5_value, bool_e D6_value, bool_e D7_value, bool_e D4_2nd_value, bool_e D5_2nd_value, bool_e D6_2nd_value, bool_e D7_2nd_value){
	GPIO_WRITE(PIN_RS, 1);
	DELAY_MS(5);
	LCD2X16_send_config_command(D4_value, D5_value, D6_value, D7_value);
	LCD2X16_send_config_command(D4_2nd_value, D5_2nd_value, D6_2nd_value, D7_2nd_value);
	DELAY_MS(5);
	GPIO_WRITE(PIN_RS, 0);
	DELAY_MS(5);

}

void LCD2X16_validate_data(void){
	GPIO_WRITE(PIN_E, 1);
	DELAY_MS(1);
	GPIO_WRITE(PIN_E, 0);
	DELAY_MS(1);
}

void LCD2X16_set_all_pins_to_zero(void){
	GPIO_WRITE(PIN_DATA_0, 0);
	GPIO_WRITE(PIN_DATA_1, 0);
	GPIO_WRITE(PIN_DATA_2, 0);
	GPIO_WRITE(PIN_DATA_3, 0);
	GPIO_WRITE(PIN_E, 0);
	GPIO_WRITE(PIN_RS, 0);
	GPIO_WRITE(PIN_RW, 0);
	DELAY_MS(40);
}

void LCD2X16_init(void){
		LCD2X16_set_command_pins_to_output();
		LCD2X16_set_data_pins_to_output();
		//Initialisation de toutes les broches � 0
		LCD2X16_set_all_pins_to_zero();
		DELAY_MS(40);
		//4 bit mode, 1 line
		LCD2X16_config_four_bit_mode_one_line();
		//Clear the display
		LCD2X16_clear_display();
		//Return home
		LCD2X16_return_home();
		//Display on, no cursor
		LCD2X16_config_display_on_no_cursor();
		DELAY_MS(40);
		//Print init data : H (72 hexa)
		LCD2X16_write_data(0,0,1,0,0,0,0,1);
		//Print init data : I (73 hexa)
		LCD2X16_write_data(0,0,1,0,1,0,0,1);
		DELAY_MS(500); //L'init ne semble pas fonctionner sinon...
}

/***************************CONFIGURATION FUNCTIONS**********************/
void LCD2X16_config_four_bit_mode_one_line(void){
	LCD2X16_send_config_command(0,1,0,0);
}

void LCD2X16_config_display_on_no_cursor(void){
	LCD2X16_send_config_command(0,0,0,0);
	LCD2X16_send_config_command(0,0,1,1);
}

/***************************USER ACTIVE FUNCTIONS**********************/
void LCD2X16_clear_display(void){
	LCD2X16_send_config_command(0,0,0,0);
	LCD2X16_send_config_command(1,0,0,0); //D0-D3 via D4_D7
}

void LCD2X16_return_home(void){
	LCD2X16_send_config_command(0,0,0,0);
	LCD2X16_send_config_command(0,1,0,0);
}


/*************************STM32 LIBRARY**************************/

/** Fonction d'affichage d'une chaine format�e (cf printf)
 * 	@param  premier param�tre = chaine de format
 * 	@param  param�tres suivants = selon les balises %x indiqu�es dans la cha�ne de format
 * 	@pre 	La chaine fabriqu�e ne DOIT PAS exc�der 20 caract�res (et en pratique 16 caract�res pour un �cran de 16 caract�res par lignes).
 *  @pre     l'usage de cette fonction doit �tre pr�c�d� au moins une fois de l'appel de LCD2X16_init()
 * 	@post	Si la cha�ne fabriqu�e exc�de 20 caract�res, un message est affich� via printf.
 */
void	LCD2X16_printf(const char *__restrict string, ...)
{
	LCD2X16_putChar('\f'); //Sans cette ligne des disfonctionnement apparaissent...
	LCD2X16_clear_display();
	LCD2X16_return_home();
	DELAY_MS(20);
	char buffer[20];
	uint8_t i;
	uint8_t size;
	va_list args_list;
	va_start(args_list, string);
	size = vsnprintf(buffer, 20, string, args_list);
	if(size>21)
		printf("ATTENTION, chaine LCD trop grande !\n");
	va_end(args_list);
	for(i=0;i<size;i++)
		LCD2X16_putChar(buffer[i]);
}

/**
 * Fonction d'envoi d'un quartet sur le LCD
 *
 *    @param n le quartet � envoyer (les 4 bits de poids faible de n)
 *    @pre     le port de donn�es doit �tre configur� en �criture
 */
static void LCD2X16_sendNibble(unsigned char n)
{
	GPIO_WRITE(PIN_DATA_0, (n   )&0x01);
	GPIO_WRITE(PIN_DATA_1, (n>>1)&0x01);
	GPIO_WRITE(PIN_DATA_2, (n>>2)&0x01);
	GPIO_WRITE(PIN_DATA_3, (n>>3)&0x01);

	LCD2X16_validate_data();
}

/**
 * Fonction d'envoi d'un octet sur le LCD
 *
 *    @param rs   num�ro du registre du LCD (0 ou 1)
 *    @param n    octet a envoyer
 *    @pre        le port de donn�es doit �tre configur� en �criture
 */
static void LCD2X16_sendByte( unsigned char rs, unsigned char n)
{
	uint8_t nb_try = 3;
   while((LCD2X16_getByte(0) & 0b10000000) != 0 && nb_try--);

   if(nb_try)
   {
	   GPIO_WRITE(PIN_RS, (rs)?1:0);
	   GPIO_WRITE(PIN_RW, 0);
	   DELAY_MS(0.1);

	   LCD2X16_sendNibble(n >> 4);
	   LCD2X16_sendNibble(n & 0xf);
   }
}

/** Fonction d'�criture d'un caract�re sur le LCD. Cette fonction affiche un caract�re ascii sur l'afficheur
 *  Il existe des caract�res de contr�le :
 *     - \f  efface l'�cran
 *     - \n  saut au d�but de la seconde ligne
 *     - \b  retour arri�re d'un caract�re
 *
 *     @param c le caract�re � afficher
 *     @pre     l'usage de cette fonction doit �tre pr�c�d� au moins une fois de l'appel � LCD2X16_init().
 *     @post    les bits du port de donn�es sont configur�s en �criture.
 *  */
void LCD2X16_putChar(char c)
{
   switch (c)
   {
      case '\f':  // Effacer l'�cran
         LCD2X16_sendByte(0,1);
         DELAY_MS(10);
         break;

      case '\n':  // Passer � la ligne suivante
         LCD2X16_setCursor(1,2);
         break;

     case '\b':   // Retour au caract�re pr�c�dent
         LCD2X16_sendByte(0,0x10);
         break;

     default:     // Caract�re affichable
         LCD2X16_sendByte(1,c);
   }
}

/** Fonction de positionnement du curseur sur le LCD
 *
 *    @param column indice de colonne (1 � 16)
 *    @param line indice de ligne (1 ou 2)
 *    @pre     l'usage de cette fonction doit �tre pr�c�d� au moins une fois de l'appel de LCD2X16_init()
 */
void LCD2X16_setCursor( unsigned char column, unsigned char line)
{
   unsigned char address;

   // Calcul de l'adresse correspondant aux coordonn�es
   if(line!=1)
     address=LCD2X16_LINE_TWO_AD;
   else
     address=0;

   address+=column-1;

   // Envoi de la commande de positionnement au LCD
   LCD2X16_sendByte(0,0x80|address);
   DELAY_MS(0.2);	//  > 38us
}

/** Fonction de lecture d'un caract�re sur le LCD.
 *
 *    @param x indice de colonne du caract�re � lire (1 � 16)
 *    @param y indice de ligne du caract�re � lire (1 ou 2)
 *    @return  le caract�re lu en (x,y)
 *    @pre     l'usage de cette fonction doit �tre pr�c�d� au moins une fois de l'appel de LCD2X16_init()
 */
char LCD2X16_getChar( unsigned char x, unsigned char y)
{
   LCD2X16_setCursor(x,y);
   return LCD2X16_getByte(1);
}

/**
 * Fonction de lecture d'un octet sur le LCD
 *
 *    @param  rs   num�ro du registre du LCD (0 ou 1)
 *    @return l'octet lu
 *    @post   les bits du port de donn�es sont configur�s en �criture.
 */
static uint8_t LCD2X16_getByte(uint8_t rs)
{
	uint8_t read;

	GPIO_WRITE(PIN_RS, (rs)?1:0);

	// configuration de l'acc�s aux donn�es en lecture
	GPIO_SET_INPUT(PIN_DATA_0);
	GPIO_SET_INPUT(PIN_DATA_1);
	GPIO_SET_INPUT(PIN_DATA_2);
	GPIO_SET_INPUT(PIN_DATA_3);

	GPIO_WRITE(PIN_RW, 1);
	DELAY_MS(0.001);

	GPIO_WRITE(PIN_E, 1);
	DELAY_MS(0.01);;

	// Lecture du quartet de poids fort
	read  = (GPIO_READ(PIN_DATA_0)	 << 4) |
			(GPIO_READ(PIN_DATA_1)  << 5) |
			(GPIO_READ(PIN_DATA_2)  << 6) |
			(GPIO_READ(PIN_DATA_3)  << 7);

	GPIO_WRITE(PIN_E, 0);
	DELAY_MS(0.001);

	GPIO_WRITE(PIN_E, 1);
	DELAY_MS(0.01);

	// Lecture du quartet de poids faible
	read |= (GPIO_READ(PIN_DATA_0)  << 0) |
			(GPIO_READ(PIN_DATA_1)  << 1) |
			(GPIO_READ(PIN_DATA_2)  << 2) |
			(GPIO_READ(PIN_DATA_3)  << 3);

	GPIO_WRITE(PIN_E, 0);

	// Configuration de l'acc�s aux donn�es en �criture
	GPIO_SET_OUTPUT(PIN_DATA_0);
	GPIO_SET_OUTPUT(PIN_DATA_1);
	GPIO_SET_OUTPUT(PIN_DATA_2);
	GPIO_SET_OUTPUT(PIN_DATA_3);

	// Concat�nation des deux quartets lus et retour
	return read;
}


#endif
