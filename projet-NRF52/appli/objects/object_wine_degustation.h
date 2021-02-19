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
const int mcp9804_address=0x35; // 00110101 : adresse prise de température (TA)
const int UpperByte;
const int LowerByte;
const int ACK=0x0; // bit d'acquittement
const int NAK=0x1; // bit de non acquittement
const int prctBatt;




#endif /* APPLI_OBJECTS_OBJECT_WINE_DEGUSTATION_H_ */
