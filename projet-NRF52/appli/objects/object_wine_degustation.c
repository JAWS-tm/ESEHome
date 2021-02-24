/*
 * object_wine_degustation.c
 *
 *  Created on: 8 févr. 2021
 *      Author: lebihata
 */

#if OBJECT_ID == OBJECT_WINE_DEGUSTATION

#include "../config.h"
#include <stdio.h>
#include "object_wine_degustation.h"
#include "leds.h"
#include "battery.h"
#include "../nrf52_i2c.h"

void Wine_Degustation_Main(void) {

	//init battery
	/*MEASURE_VBAT_init();
	prctBatt= MEASURE_VBAT_get_level();
	printf("La batterie est à %u", prctBatt,"%.") ;*/

	//initialisation led verte et jaune
	LEDS_init(I_HAVE_LED_BATTERY);

	LED_add(LED_ID_USER0, PIN_LED_VERTE);
	LED_add(LED_ID_USER1, PIN_LED_JAUNE);

	LED_set(LED_ID_USER0, LED_MODE_OFF);
	LED_set(LED_ID_USER1, LED_MODE_ON);


	//configuration registre du mcp9804 via I2C
	I2C_init();

	//ecrire dans un registre
	I2C_write(datas, 3);

	//lire dans un registre
	I2C_write(reg, 1);
	I2C_read(reg, 2);

	/*i2c_start(); // send START command
	// 00110101 : adresse prise de température (TA)
	i2c_write (mcp9804_address && 0xFE); //WRITE Command
	//also, make sure bit 0 is cleared ‘0’
	i2c_write(0x05); // Write TA Register Address

	i2c_start(); //Repeat START
	i2c_write(mcp9804_address || 0x01); // READ Command

	//also, make sure bit 0 is Set ‘1’
	UpperByte = i2c_read(ACK); // READ 8 bits
	//and Send ACK bit
	LowerByte = i2c_read(NAK); // READ 8 bits
	//and Send NAK bit
	i2c_stop(); // send STOP command

	//Convertire la donnée du capteur en degres Celsus (°C)
	//First Check flag bits
	if ((UpperByte & 0x80) == 0x80){ //TA ≥ TCRIT
	}
	if ((UpperByte & 0x40) == 0x40){ //TA > TUPPER
	}
	if ((UpperByte & 0x20) == 0x20){ //TA < TLOWER
	}
	UpperByte = UpperByte & 0x1F; //Clear flag bits

	if ((UpperByte & 0x10) == 0x10){ //TA < 0°C
		UpperByte = UpperByte & 0x0F; //Clear SIGN
		temp = 256 - (UpperByte*16 + LowerByte / 16);
	}
	else {  //TA ≥ 0°C
		temp = (UpperByte*16 + LowerByte / 16);
	}*/

	// exemple d'assistance de dégustation avec un Reuilly "pinot gris" entre 11 et 13 °C
	if( temp >=11 && temp<=13){
		LED_set(LED_ID_USER0, LED_MODE_OFF);
		LED_set(LED_ID_USER1, LED_MODE_BLINK);
	}
	else if(temp<11){
		LED_set(LED_ID_USER0, LED_MODE_BLINK);
		LED_set(LED_ID_USER1, LED_MODE_OFF);
	}
	else if(temp>13){
		LED_set(LED_ID_USER0, LED_MODE_ON);
		LED_set(LED_ID_USER1, LED_MODE_OFF);
	}

}

#endif
