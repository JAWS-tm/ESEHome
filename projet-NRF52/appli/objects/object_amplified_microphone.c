/*
 * object_amplified_microphone.c
 *
 *  Created on: 9 Feb 2023
 *      Author: flamm
 */
#import "object_amplified_microphone.h"
#import "../common/adc.h"
#import "../common/gpio.h"
#import "../config.h"

static uint16_t value;
static uint16_t valueMin = 0;
static uint16_t valueMax = 0;
static uint16_t seuil = 0;
//static uint16_t value;
static uint8_t isConfig = 0;

void main_Amplified_Microphone(void){
	if (!isConfig){
		GPIO_configure(VCC_IN, 3, TRUE);
		GPIO_write(VCC_IN,TRUE);
		ADC_read(ADC_PIN,&value);
		valueMin = valueMax = value;
	}
	GPIO_write(VCC_IN,TRUE);
	ADC_read(ADC_PIN,&value);

	if (valueMin < value){
		valueMin = value;
		seuil = (valueMax - valueMin)/2 + valueMin;
	}

	if (valueMax > value){
		valueMax = value;
		seuil = (valueMax - valueMin)/2 + valueMin;
	}

	if (seuil < value)
		printf("Seuil dépassé");



}
