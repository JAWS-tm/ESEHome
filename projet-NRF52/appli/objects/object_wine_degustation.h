/*
 * object_wine_degustation.h
 *
 *  Created on: 8 févr. 2021
 *      Author: lebihata
 */

#ifndef OBJECT_WINE_DEGUSTATION_H_
#define OBJECT_WINE_DEGUSTATION_H_


void Wine_Degustation_Main(void);

#define PIN_LED_VERTE (9) //led verte = bouteille chambrée
#define PIN_LED_JAUNE (10) //led jaune = bouteille non chambrée
const int temp;
const int prctBatt;
const int datas=0x3; //adresse du pointer 0011
const int reg=0x5; //pointer 0101



#endif /* APPLI_OBJECTS_OBJECT_WINE_DEGUSTATION_H_ */
