/*
 * object_ventilator.h
 *
 *  Created on: 10 févr. 2022
 *      Author: Pierre Nile
 */

#ifndef APPLI_OBJECTS_OBJECT_VENTILATOR_H_
#define APPLI_OBJECTS_OBJECT_VENTILATOR_H_

void object_ventilator_activation(void);
void object_ventilator_temperature(void);


typedef enum{
	 VENTILATOR_INIT,
	 VENTILATOR_ON
}ventilator_e;

#endif /* APPLI_OBJECTS_OBJECT_VENTILATOR_H_ */
