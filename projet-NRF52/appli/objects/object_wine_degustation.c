/*
 * object_wine_degustation.c
 *
 *  Created on: 8 f�vr. 2021
 *      Author: lebihata
 */

#include "../config.h"
#include "object_wine_degustation.h"
#include "leds.h"
#include "battery.h"
//#include "i2c.h"

#if OBJECT_ID == OBJECT_WINE_DEGUSTATION

void object_wine_degustation_process_main(void){
	LEDS_init(I_HAVE_LED_BATTERY);

	LED_add(LED_ID_USER0, 24);  //led verte = bouteille chambr�e
	LED_add(LED_ID_USER0, 25); //led jaune = bouteille non chambr�e

	LED_set(LED_ID_USER0, LED_MODE_OFF);
	LED_set(LED_ID_USER1, LED_MODE_FLASH);

	/*If ( temp >11 && temp<13){ // exemple Reuilly "pinot gris" entre 11 et 13
		LED_set(LED_ID_USER0, LED_MODE_ON);
		LED_set(LED_ID_USER1, LED_MODE_OFF);
	}*/

}

#endif
