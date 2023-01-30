/*
 * morse.h
 *
 *  Created on: 3 févr. 2022
 *      Author: mljos
 */

#ifndef BSP_MORSE_H_
#define BSP_MORSE_H_

#include "../appli/common/macro_types.h"

running_e MORSE_state_machine_process_ms(char * message, bool_e reset);
void MORSE_demo(void);


#endif /* BSP_MORSE_H_ */
