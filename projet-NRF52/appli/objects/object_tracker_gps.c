/*
 * object_tracker_gps.c
 */
#include "../config.h"



#if OBJECT_ID == OBJECT_TRACKER_GPS

#include "appli/common/gpio.h"
#include "object_tracker_gps.h"

#include <math.h>
#include <stdlib.h>
//Constantes privï¿½es
#define BUFFER_SIZE	256

/** \brief NMEA message start-of-message (SOM) character */
#define NMEA_MESSAGE_SOM '$'

/** \brief NMEA message end-of-message (EOM) character */
#define NMEA_MESSAGE_EOM '*'

/** \brief NMEA message field separator */
#define NMEA_MESSAGE_FIELD_SEPARATOR ','

#define PI                     (3.141592653589793)        /**< PI value */
#define PI180                  (PI / 180)                 /**< PI division by 180 */
#define EARTHRADIUS_KM         (6378)                     /**< Earth's mean radius in km */
#define EARTHRADIUS_M          (EARTHRADIUS_KM * 1000)    /**< Earth's mean radius in m */



//Fonctions privï¿½es
static nmea_frame_e GPS_parse(uint8_t * buffer, gps_datas_t * gps_datas);
static bool_e GPS_parse_gprmc(uint8_t * string, gps_datas_t * coordinates);
static uint8_t hextoint(char c);
	/*
 * Cette fonction rï¿½cupï¿½re le nouveau caractï¿½re fourni (c) et le range dans son propre buffer
 * Si l'on atteint le dï¿½but de la trame ($) -> on reset l'index de lecture
 * Lorsqu'on atteint la fin de la trame (dï¿½tection d'un caractï¿½re '\n') -> on sous-traite le dï¿½coupage de la trame au parser.
 * Une trame correctement lue donne lieu au remplissage de la structure gps_datas et au renvoi d'une valeur de retour diffï¿½rente de NO_TRAME_RECEIVED (0)
 */

void GPS_main(void)
{
	static tracker_gps_state state = INIT;
		switch(state)
				{
					case INIT:
						// initialisation du gps

						debug_printf("init");
						LED_add(LED_ID_BATTERY, PIN_LED_BATTERY);
						LED_add(LED_ID_NETWORK, PIN_LED_NETWORK);
						LED_set(LED_ID_BATTERY, LED_MODE_ON);
						LED_set(LED_ID_NETWORK, LED_MODE_ON);

						GPS_On();
						Systick_init();
						SECRETARY_init();


						BUTTONS_init();
						BUTTONS_add(BUTTON_NETWORK, PIN_BUTTON_NETWORK, TRUE, &BUTTONS_network_process);


						state = CONTAINER_TRAM;
						break;
					case CONTAINER_TRAM: //recup곡tion des marker gps et stockage
						LED_set_flash_limited_nb(LED_ID_NETWORK, 3, 500);
						SERIAL_DIALOG_set_rx_callback(&GPS_process_rx);

    					state = WAIT;

						if(BUTTONS_read(BUTTON_NETWORK) == TRUE)
							state = SENT_CONTAINER_TRAM;

						break;
					case WAIT: // on attend 1min avant de retourner dans la case CONTAINER_TRAM pour reffaire un prelevement de coordonnꥍ
						LED_set(LED_ID_NETWORK, LED_MODE_BLINK);
						SYSTICK_delay_ms(10000);
						state = CONTAINER_TRAM;

						break;
					case SENT_CONTAINER_TRAM: // envoie des donnꥠvers la base
						LED_set(LED_ID_NETWORK, LED_MODE_FLASH);

						// test d'envoie message en uart
						for(int i = 0; i<33; i++)
						{
							debug_printf("%d\n",gps_lat[i]);
						}

						//SECRETARY_send_msg(8, gps_lat);
						//SECRETARY_send_msg(8, gps_long);
						break;
					case STOP: //arret de l'utilisation du module gps

						break;
					default:
						break;
				}
}
void GPS_On(void)
{
	GPIO_configure(MOSFET_GND_GPS, NRF_GPIO_PIN_NOPULL, true);//configure la pin de du gps concernée en sortie
	GPIO_write(MOSFET_GND_GPS, true);
}


static gps_datas_t gps_datas;
double gps_lat[32];
double gps_long[32];
double gps_date[24];
double gps_heure[24];

uint8_t y = 0;
double lat_a_rad = 0;
double lon_a_rad = 0;

double lat_b_rad = 0;
double lon_b_rad = 0;
uint8_t compteur = 0;

void GPS_process_rx(uint8_t c)
{
	static uint8_t buffer[BUFFER_SIZE];
	static uint16_t index = 0;
	if(c == '$')
		index = 0;

	buffer[index] = c;

	if(index<BUFFER_SIZE-1)
		index++;
	if(c=='\n')
	{
		//lorsqu'une trame compl鵥 et valide a 굩 re趥, on peut traiter les donn꦳ interpret꦳.
		//debug_printf("%d, %d\n",gps_datas.latitude_deg, gps_datas.longitude_deg);

		//SECRETARY_send_msg(8, gps_datas);

		if(compteur %2 == 0) // tout les paire on stock la coordonnꥠdans a
			{
				lat_a_rad = gps_datas.latitude_rad;
				lon_a_rad = gps_datas.longitude_rad;
			}

		if(compteur %2 == 1) // tout les impaire on stock la coordonnꥠdans b
			{
				lat_b_rad = gps_datas.latitude_rad;
				lon_b_rad = gps_datas.longitude_rad;
			}

		compteur++;

		double distance = 0;
		distance = gps_calcul_distance(lat_a_rad, lon_a_rad, lat_b_rad, lon_b_rad);

		if(distance > 1000)
		{

			gps_lat[y] = gps_datas.latitude_rad;      // voir s'il faut mettre en degre pour le site
			gps_long[y] = gps_datas.longitude_rad;
			gps_date[y] =  gps_datas.date32;
			gps_heure[y] =  gps_datas.time;
			//debug_printf("%lf\n",gps_lat[y]);
			y++;

		}else // cas ou la distance n'est pas assez grande, on viens redonner l'ancienne valeur pour garder un bon referenciel
		{
			if(compteur %2 == 0)
				{
					lat_a_rad = lat_b_rad;
					lon_a_rad = lon_b_rad;
				}
			if(compteur %2 == 1)
				{
					lat_b_rad = lat_a_rad;
					lon_b_rad = lon_a_rad;
				}
		}
	}
}

double gps_calcul_distance(double lat_a_rad, double lon_a_rad, double lat_b_rad, double lon_b_rad)
{
	//formule certainement fausse, aller voir la formule de Haversine
	double distance =  EARTHRADIUS_M* (acos(sin(lat_a_rad) * sin(lat_b_rad) + cos(lat_a_rad) * cos(lat_b_rad) *cos(lon_b_rad - lon_a_rad)));

	return distance;
}
/*

void GPS_test(void)
{
	//checksum calculator : http://www.hhhh.org/wiml/proj/nmeaxor.html
	//https://www.coordonnees-gps.fr/

	#define NB_TEST_STRINGS 7


	char * test_strings[NB_TEST_STRINGS] = {
			"$GPRMC,063355.00,A,4729.60520,N,00033.05755,W,0.022,,170614,,,D*6F\r\n",
			"$GPRMC,Q63355.00,A,4729.60520,N,00033.05755,W,0.022,,170614,,,D*6F\r\n",	//checksum fail
			"$GPRMC,225446,A,4916.45,N,12311.12,W,000.5,054.7,191194,020.3,E*68\r\n",
			"$GPRMC,081836,A,3751.65,S,14507.36,E,000.0,360.0,130998,011.3,E*62\r\n",
			"$GPABC,ABCDEFGHIJKLMNOPQRSTUVWXYZ,E*09\r\n",		//Unknow frame
			"$GPGLL,3751.65,S,14507.36,E*77\r\n",				//GPGGL
			"$GPRMC,010203.00,A,8959.99999,N,17959.99999,E,254.000,,010418,,,D*74\r\n"};
	uint16_t i;
	gps_datas_t gps_datas;
	uint8_t buf[128];
	nmea_frame_e err;

	for(i=0;i<NB_TEST_STRINGS; i++)
	{
		sprintf((char*)buf, "%s", (uint8_t*)test_strings[i]);	//On recopie la chaine en RAM
		err = GPS_parse(buf, &gps_datas);	//On parse
		switch(err)
		{
			case TRAME_GPRMC:
				printf("%lf, %lf\n",gps_datas.latitude_deg, gps_datas.longitude_deg);	//On affiche les coordonnï¿½es lues
				break;
			case TRAME_INVALID:
				printf("Invalid trame\n");
				break;
			case CHECKSUM_INVALID:
				printf("Invalid checksum\n");
				break;
			case TRAME_UNKNOW:
				//No break;
			default:
				printf("unknow trame\n");
				break;
		}
	}
}
*/



/*
 * Fonction permettant de savoir si la chaine string commence par le contenu de la chaine begin
 * Renvoi vrai si c'est le cas, faux sinon.
 */
static bool_e string_begins_with(uint8_t * string, uint8_t * begin)
{
	bool_e b;
	uint16_t i;
	b = TRUE;	//On fait l'hypothï¿½se que tout se passe bien...
	for(i=0;begin[i];i++)
	{
		if(string[i] == '\0' || (string[i] != begin[i]))
		{
			b = FALSE;
			break;
		}
	}
	return b;
}

/*
 * Cette fonction a pour but de :
 * - vï¿½rifier si la trame founie dans "buffer" commence par un identifiant connu (GPRMC, ...)
 * - vï¿½rifier la valeur du checksum
 * - sous-traiter la lecture de la trame reconnue ï¿½ la bonne fonction
 * Si le checksum est faux -> renvoit CHECKSUM_INVALID
 * Si la trame n'est pas reconnue -> renvoit NO_TRAME_RECEIVED
 * Si la trame est jugï¿½e invalide par les fonctions sous-traitantes -> renvoit TRAME_INVALID
 */
static nmea_frame_e GPS_parse(uint8_t * buffer, gps_datas_t * gps_datas)
{
	const char string_gprmc[] = "$GPRMC";
	nmea_frame_e ret;
	Uint8 i, checksum;
	ret = NO_TRAME_RECEIVED;	//On fait l'hypothï¿½se qu'aucune trame correcte est reï¿½ue

	if(string_begins_with(buffer, (uint8_t *)string_gprmc))
		ret = TRAME_GPRMC;

	//TODO ajouter d'autres trames si besoin..

	if(ret != NO_TRAME_RECEIVED)	//un entï¿½te connu a ï¿½tï¿½ trouvï¿½... calcul du checksum
	{
		checksum = 0;
		for(i=1; buffer[i]!='*' && buffer[i] != '\0'; i++)
		{
			checksum ^= buffer[i];
		}
		if(! (buffer[i] == '*' && (16*hextoint(buffer[i+1]) + hextoint(buffer[i+2]) == checksum)))
			ret = CHECKSUM_INVALID;	//Trame invalide : pas de checksum *XX ou checksum incorrect
	}

	switch(ret)
	{
		case TRAME_GPRMC:
			if(!GPS_parse_gprmc(buffer, gps_datas))
				ret = TRAME_INVALID;
			break;
		default:
			break;
	}

	return ret;
}



/*
 * Cette fonction dï¿½coupe une trame GPRMC fournie dans string et remplit la structure coordinates
 * - Si la trame est invalide (notamment lorsque le GPS ne capte pas !) -> renvoit FALSE
 * - Si la trame est valide -> renvoit TRUE
 * Attention, cette fonction ï¿½crase la chaine passï¿½e en remplacant notamment certains caractï¿½res ',' par des '\0' !!!
 */
bool_e GPS_parse_gprmc(uint8_t * string, gps_datas_t * coordinates)
{
	uint8_t i;
	uint8_t *message_field[14] = {'\0'};	//tableau des pointeur sur champ
	//tableau des pointeurs sur champ dï¿½cimal
	//Header : $GPRMC
	//Data : 											,hhmmss.sss,A,ddmm.mmmm,N,ddmm.mmmm,W,X,X,ddmmyy,X,X,X*<CR><LF>
	//Chaine final :							\0		 hhmmss . sss \0 A \0 ddmm . mmmm \0 N \0 ddmm . mmmm \0 W \0 X \0 X \0 ddmmyy \0 X \0 X \0 X \0 <CR><LF>
	//indice de tableau dans la chaine : F0S0 = \0 ensuite F1	       \0 F2 \0 F3          \0 F4 \ F5           \0 F6\0 F7\0 F8\0 F9	 \0F10\0F11\0F12\0 F13

	i = 0;
	message_field[i] = string;
	while (*string != '\0' && *string != '\r' && *string != '\n')
	{
		if ((*string == NMEA_MESSAGE_FIELD_SEPARATOR) || (*string == NMEA_MESSAGE_EOM) )
		{
			// save position of the next token
			if(i<13)
				message_field[++i] = string + 1;
			*string = '\0';	// terminate string after field separator or end-of-message characters
		}
		string++;
	}

	if(i>2 && *message_field[2] == 'A')
	{
		coordinates->time =  (uint32_t)atoi((char*)message_field[1]); //conversion 32 bits
		coordinates->seconds = 	  ((uint32_t)(message_field[1][0] - '0')) * 36000
								+ ((uint32_t)(message_field[1][1] - '0')) * 3600
								+ ((uint32_t)(message_field[1][2] - '0')) * 600
								+ ((uint32_t)(message_field[1][3] - '0')) * 60
								+ ((uint32_t)(message_field[1][4] - '0')) * 10
								+ ((uint32_t)(message_field[1][5] - '0'));

		coordinates->north	= (message_field[4][0] == 'S')?FALSE:TRUE;
		coordinates->east	= (message_field[6][0] == 'W')?FALSE:TRUE;

		coordinates->lat_minutes = atof((char*)message_field[3]);
		coordinates->lat_degrees = (int16_t)(trunc(coordinates->lat_minutes));
		coordinates->lat_minutes -= (float)((coordinates->lat_degrees/100)*100);
		coordinates->lat_degrees = coordinates->lat_degrees/100;
		coordinates->latitude_deg = (double)coordinates->lat_degrees + coordinates->lat_minutes/60;
		if(coordinates->north==0)
			coordinates->latitude_deg*=-1;
		coordinates->latitude_rad = coordinates->latitude_deg * PI180;	//--> radians !

		coordinates->long_degrees = (int16_t)atoi((char*)message_field[5]);
		coordinates->long_minutes = atof((char*)message_field[5]);
		coordinates->long_minutes -= (float)((coordinates->long_degrees/100)*100);
		coordinates->long_degrees = coordinates->long_degrees/100;
		coordinates->longitude_deg = (double)coordinates->long_degrees + coordinates->long_minutes/60;
		if(coordinates->east==0)
			coordinates->longitude_deg*=-1;
		coordinates->longitude_rad = coordinates->longitude_deg * PI180;	//--> radians !

		coordinates->ground_speed =  (uint16_t)atoi((char*)message_field[7]);

		uint32_t current_date;
		current_date =  (uint32_t)atoi((char*)message_field[9]);
		coordinates->date32 = 	(	((Uint32)(current_date%100) + 20) << 25 ) 	//20 est la diffï¿½rence entre 2000 et 1980.
				| 	((Uint32)((current_date/100)%100) << 21 )
				| 	((Uint32)(current_date/10000) << 16 )
				| 	((Uint32)(coordinates->time/10000) << 11 )
				| 	((Uint32)((coordinates->time/100)%100) << 5 )
				| 	((Uint32)(coordinates->time%100) >> 1 ) ;

		return TRUE;
	}
	return FALSE;
}


//converti un caractï¿½re hexa (par exemple '4', ou 'B') en un nombre (dans cet exemple : 4, 11)
static uint8_t hextoint(char c)
{
	if(c >= 'A' && c <= 'F')
		return (uint8_t)(c - 'A' + 10);
	if(c >= 'a' && c <= 'f')
		return (uint8_t)(c - 'a' + 10);
	if(c >= '0' && c <= '9')
		return (uint8_t)(c - '0');
	return 0;
}


#endif
