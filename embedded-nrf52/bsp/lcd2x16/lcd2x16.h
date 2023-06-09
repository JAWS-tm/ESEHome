/**
 * @addtogroup lcd2x16
 *
 * Afficheur LCD 2 lignes de 16 caract�res.
 * 
 *
 * L'afficheur est utilis� en mode 4 bits. Les ports d'entr�e/sortie se d�composent par cons�quent en
 *    - trois bits de commande
 *    - quatre bits de donn�es
 *
 * Les bits de commande sont configur�es en sortie tandis que les bits de donn�es peuvent �tre acc�d�s
 * soit en lecture, soit en �criture.
 *
 * El�ments � modifier pour configurer l'�cran LCD :
 *    - pour la gestion des d�lais : #CLOCK_FREQUENCY
 *    - Configuration des ports de donn�es et de commande
 * @{
 */

/**
 * @file lcd2x16_c18.h
 *
 *  Driver d'afficheur LCD 2 lignes de 16 caract�res.
 *
 *  @version 1.3
 *  @date 24/08/2015
 */

#ifndef __LCD2X16_H
#define __LCD2X16_H

/**
 * Bits du port de donn�es.
 * Adaptez ces configurations � votre design (ports et pins utilis�s).
 */

	#define	PIN_DATA_0	LCD_DATA_1_PIN
	#define	PIN_DATA_1	LCD_DATA_2_PIN
	#define	PIN_DATA_2	LCD_DATA_3_PIN
	#define	PIN_DATA_3	LCD_DATA_4_PIN
	#define PIN_RS		LCD_RS_PIN
	#define PIN_RW		LCD_RW_PIN
	#define PIN_E		LCD_E_PIN

void LCD2X16_demo(void);

/**
 * Fonction d'initialisation du LCD.
 *
 * Cette fonction doit �tre appel�e pr�alablement � toute utilisation de l'�cran LCD.
 */
void LCD2X16_init(void);

/** Fonction de test de ce module logiciel. Elle pr�sente un exemple d'utilisation des fonctions.
 *
 */

void LCD2X16_putChar(char c);


/** Fonction de positionnement du curseur sur le LCD
 *
 *    @param x indice de colonne (1 � 16)
 *    @param y indice de ligne (1 ou 2)
 *    @pre     l'usage de cette fonction doit �tre pr�c�d� au moins une fois de l'appel de LCD2X16_init()
 */
void LCD2X16_setCursor( unsigned char column, unsigned char ligne);



/** Fonction de lecture d'un caract�re sur le LCD.
 *
 *    @param x indice de colonne du caract�re � lire (1 � 16)
 *    @param y indice de ligne du caract�re � lire (1 ou 2)
 *    @return  le caract�re lu en (x,y)
 *    @pre     l'usage de cette fonction doit �tre pr�c�d� au moins une fois de l'appel de LCD2X16_init()
 */
char LCD2X16_getChar( unsigned char x, unsigned char y);



/** Fonction d'affichage d'une chaine formatt�e (cf printf)
 * 	@param  premier param�tre = chaine de format
 * 	@param  param�tres suivantes = selon les balises %x indiqu�es dans la cha�ne de format
 * 	@pre 	La chaine fabriqu�e ne DOIT PAS exc�der 20 caract�res (et en pratique 16 caract�res pour un �cran de 16 caract�res par lignes). *    @pre     l'usage de cette fonction doit �tre pr�c�d� au moins une fois de l'appel de LCD2X16_init()
 * 	@post	Si la cha�ne fabriqu�e exc�de 20 caract�res, un message est affich�e via printf.
 */
void	LCD2X16_printf(const char *__restrict, ...) __attribute__ ((__format__ (__printf__, 1, 2)));


#endif
