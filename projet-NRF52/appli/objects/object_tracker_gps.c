/*
 * object_tracker_gps.c
 */
#include "../config.h"



#if OBJECT_ID == OBJECT_TRACKER_GPS

#include "appli/common/gpio.h"
#include "object_tracker_gps.h"

#include <math.h>
#include <stdlib.h>
//Constantes priv�es
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



//Fonctions priv�es
static nmea_frame_e GPS_parse(uint8_t * buffer, gps_datas_t * gps_datas);
static bool_e GPS_parse_gprmc(uint8_t * string, gps_datas_t * coordinates);
static uint8_t hextoint(char c);
	/*
 * Cette fonction r�cup�re le nouveau caract�re fourni (c) et le range dans son propre buffer
 * Si l'on atteint le d�but de la trame ($) -> on reset l'index de lecture
 * Lorsqu'on atteint la fin de la trame (d�tection d'un caract�re '\n') -> on sous-traite le d�coupage de la trame au parser.
 * Une trame correctement lue donne lieu au remplissage de la structure gps_datas et au renvoi d'une valeur de retour diff�rente de NO_TRAME_RECEIVED (0)
 */

void GPS_main(void)
{
	static tracker_gps_state state = INIT;
	switch(state)
			{
				case INIT:
					// initialisation du gps
					GPS_On();
					Systick_init();
					SECRETARY_init();
					state = CONTAINER_TRAM;
					break;
				case CONTAINER_TRAM:
					SERIAL_DIALOG_set_rx_callback(&GPS_process_rx);

					break;
				case SENT_CONTAINER_TRAM:
					// mise en sommeil de la carte pour �viter une consomation top importante du module
					break;
				case STOP:
					//arret de l'utilisation du module gps
					break;
				default:
					break;
			}
}
void GPS_On(void)
{
	GPIO_configure(MOSFET_GND_GPS, NRF_GPIO_PIN_NOPULL, true);//configure la pin de du gps concern�e en sortie
	GPIO_write(MOSFET_GND_GPS, true);
}


static gps_datas_t gps_datas;
static uint8_t gps_tables[128];
static uint8_t i;

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
		buffer[index] = '\0';

		index = 0;
		//trame termin�e, on l'envoie !
		if(GPS_parse(buffer, &gps_datas) == TRAME_GPRMC)
		{
			//lorsqu'une trame compl�te et valide a �t� re�ue, on peut traiter les donn�es interpret�es.
			//printf("%lf, %lf\n",gps_datas.latitude_deg, gps_datas.longitude_deg);

			SECRETARY_send_msg(8, gps_datas);
			/*
			gps_tables[i] = gps_datas;
			i++;
			*/
		}
	}
}

uint8_t gps_calcul_distance(lat_a_degre, lon_a_degre, lat_b_degre, lon_b_degre)
{

	uint8_t lat_a = lat_a_degre*PI/180; // convertisseur degr� en rad
	uint8_t lon_a = lon_a_degre*PI/180;
	uint8_t lat_b = lat_b_degre*PI/180;
	uint8_t lon_b = lon_b_degre*PI/180;

	uint8_t distance =  EARTHRADIUS_M* (PI/2 - asin(sin(lat_b) * sin(lat_a) + cos(lon_b - lon_a) *cos(lat_b) * cos(lat_a)));
	return distance;
}

void GPS_test(void)
{
	//checksum calculator : http://www.hhhh.org/wiml/proj/nmeaxor.html
	//https://www.coordonnees-gps.fr/

	#define NB_TEST_STRINGS 7
	/*
	 * changer le char et récupérer
	 */

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
				printf("%lf, %lf\n",gps_datas.latitude_deg, gps_datas.longitude_deg);	//On affiche les coordonn�es lues
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




/*
 * Fonction permettant de savoir si la chaine string commence par le contenu de la chaine begin
 * Renvoi vrai si c'est le cas, faux sinon.
 */
static bool_e string_begins_with(uint8_t * string, uint8_t * begin)
{
	bool_e b;
	uint16_t i;
	b = TRUE;	//On fait l'hypoth�se que tout se passe bien...
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
 * - v�rifier si la trame founie dans "buffer" commence par un identifiant connu (GPRMC, ...)
 * - v�rifier la valeur du checksum
 * - sous-traiter la lecture de la trame reconnue � la bonne fonction
 * Si le checksum est faux -> renvoit CHECKSUM_INVALID
 * Si la trame n'est pas reconnue -> renvoit NO_TRAME_RECEIVED
 * Si la trame est jug�e invalide par les fonctions sous-traitantes -> renvoit TRAME_INVALID
 */
static nmea_frame_e GPS_parse(uint8_t * buffer, gps_datas_t * gps_datas)
{
	const char string_gprmc[] = "$GPRMC";
	nmea_frame_e ret;
	Uint8 i, checksum;
	ret = NO_TRAME_RECEIVED;	//On fait l'hypoth�se qu'aucune trame correcte est re�ue

	if(string_begins_with(buffer, (uint8_t *)string_gprmc))
		ret = TRAME_GPRMC;

	//TODO ajouter d'autres trames si besoin..

	if(ret != NO_TRAME_RECEIVED)	//un ent�te connu a �t� trouv�... calcul du checksum
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
 * Cette fonction d�coupe une trame GPRMC fournie dans string et remplit la structure coordinates
 * - Si la trame est invalide (notamment lorsque le GPS ne capte pas !) -> renvoit FALSE
 * - Si la trame est valide -> renvoit TRUE
 * Attention, cette fonction �crase la chaine pass�e en remplacant notamment certains caract�res ',' par des '\0' !!!
 */
bool_e GPS_parse_gprmc(uint8_t * string, gps_datas_t * coordinates)
{
	uint8_t i;
	uint8_t *message_field[14] = {'\0'};	//tableau des pointeur sur champ
	//tableau des pointeurs sur champ d�cimal
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
		coordinates->date32 = 	(	((Uint32)(current_date%100) + 20) << 25 ) 	//20 est la diff�rence entre 2000 et 1980.
				| 	((Uint32)((current_date/100)%100) << 21 )
				| 	((Uint32)(current_date/10000) << 16 )
				| 	((Uint32)(coordinates->time/10000) << 11 )
				| 	((Uint32)((coordinates->time/100)%100) << 5 )
				| 	((Uint32)(coordinates->time%100) >> 1 ) ;

		return TRUE;
	}
	return FALSE;
}


//converti un caract�re hexa (par exemple '4', ou 'B') en un nombre (dans cet exemple : 4, 11)
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
