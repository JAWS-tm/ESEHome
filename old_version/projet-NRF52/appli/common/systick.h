<<<<<<< HEAD:projet-NRF52/appli/common/systick.h
/*
 * systick.h
 *
 *  Created on: 4 mai 2016
 *      Author: Nirgal
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_

#include "macro_types.h"

void Systick_init(void);

//Routine d'interruption appelée automatiquement à chaque ms.
void SysTick_Handler(void);


bool_e Systick_add_callback_function(callback_fun_t func);


bool_e Systick_remove_callback_function(callback_fun_t func);

uint32_t SYSTICK_get_time_us(void);

void SYSTICK_delay_ms(uint32_t duration);

void SYSTICK_delay_us(uint32_t duration);

#endif /* SYSTICK_H_ */
=======
/*
 * systick.h
 *
 *  Created on: 4 mai 2016
 *      Author: Nirgal
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_

#include "macro_types.h"

void Systick_init(void);

//Routine d'interruption appelée automatiquement à chaque ms.
void SysTick_Handler(void);


bool_e Systick_add_callback_function(callback_fun_t func);


bool_e Systick_remove_callback_function(callback_fun_t func);

uint32_t SYSTICK_get_time_us(void);

#endif /* SYSTICK_H_ */
>>>>>>> db287b6c518b612159e83485572f37ae94a5d1f8:old_version/projet-NRF52/appli/common/systick.h
