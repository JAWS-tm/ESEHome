/*
 * morse.c
 *
 *  Created on: 3 févr. 2022
 *      Author: nirgal
 *      Modified on: 3 févr. 2022
 *  	By: JosMl
 */
#include "../appli/objects/object_fall_sensor.h"
#include "../appli/common/systick.h"
#include "../appli/common/macro_types.h"
#include "morse.h"

static volatile uint32_t t = 0;

void MORSE_process_ms(void)
{
	if(t){
		t--;
	}
}

typedef enum
{
	NONE,
	TI,
	TA
}morse_e;

typedef struct
{
	morse_e symbols[6];	//il faut garder au moins une case de + que la quantité max de ti et ta.
}letter_t;

static const letter_t letters[26] =
{ 	(letter_t){{TI, TA}}, 			//A
	(letter_t){{TA, TI, TI, TI}}, 	//B
	(letter_t){{TA, TI, TA,TI}}, 	//C
	(letter_t){{TA, TI, TI}}, 		//D
	(letter_t){{TI}}, 				//E
	(letter_t){{TI, TI, TA, TI}}, 	//F
	(letter_t){{TA, TA, TI}}, 		//G
	(letter_t){{TI, TI, TI, TI}}, 	//H
	(letter_t){{TI, TI}}, 			//I
	(letter_t){{TI, TA, TA, TA}},	//J
	(letter_t){{TA, TI, TA}}, 		//K
	(letter_t){{TI, TA, TI, TI}}, 	//L
	(letter_t){{TA, TA}}, 			//M
	(letter_t){{TA, TI}}, 			//N
	(letter_t){{TA, TA, TA}},		//O
	(letter_t){{TI, TA, TA, TI}}, 	//P
	(letter_t){{TA, TA, TI, TA}}, 	//Q
	(letter_t){{TI, TA, TI}},	 	//R
	(letter_t){{TI, TI, TI}}, 		//S
	(letter_t){{TA}}, 				//T
	(letter_t){{TI, TI, TA}},		//U
	(letter_t){{TI, TI, TI, TA}}, 	//V
	(letter_t){{TI, TA, TA}}, 		//W
	(letter_t){{TA, TI, TI, TA}}, 	//X
	(letter_t){{TA, TI, TA, TA}}, 	//Y
	(letter_t){{TA, TA, TI, TI}}	//Z
};

/*
 * @author	nirgal
 * @date 03 feb 2022
 * @Modified by JosMl, 17 feb 2022
 *
 * @brief	Machine à état permettant la génération d'un code morse.
 * @param message: Message voulant être généré en morse
 *
 */

running_e MORSE_state_machine_process_ms(char * message, bool_e reset)
{
	typedef enum
	{
		INIT,
		IDLE,
		NEXT_SYMBOL,
		DO_TI,
		DO_TA,
		PAUSE_BETWEEN_TWO_SYMBOLS,
		LONG_PAUSE_BETWEEN_TWO_LETTERS
	}state_e;
	static state_e state = INIT;
	static state_e previous_state = INIT;
	running_e ret = IN_PROGRESS;
	static uint16_t index = 0;
	static uint8_t symbol_index = 0;
	static const letter_t * current_letter;
	bool_e entrance = (state!=previous_state)?TRUE:FALSE;
	previous_state = state;

	switch(state)
	{
		case INIT:
			Systick_add_callback_function(&MORSE_process_ms);
			state = IDLE;
			break;
		case IDLE:
			if(reset){
				state = INIT;
				debug_printf("dans reset");
			}
			if(message != NULL)
			{
				index = 0;
				symbol_index = 0;
				state = NEXT_SYMBOL;
			}
			break;
		case NEXT_SYMBOL:
			if(message[index]!=0 && message[index]>='A' && message[index]<='Z')
			{
				current_letter = &letters[message[index]-'A'];	//lettre acceptable
				if(reset){
					state = INIT;
					debug_printf("dans reset");
				}
				switch(current_letter->symbols[symbol_index])
				{
					case TI:
						state = DO_TI;
						symbol_index++;
						break;
					case TA:
						state = DO_TA;
						symbol_index++;
						break;
					case NONE:
					//no break;
					default:
						state = LONG_PAUSE_BETWEEN_TWO_LETTERS;
						index++;	//lettre suivante !
						symbol_index = 0; //premier symbol de la lettre suivante
						break;
				}
			}
			else
			{
				state = IDLE;
				//fin du message !
				ret = END_OK;
			}
			break;
		case DO_TI:
			if(entrance)
			{
				buzz(1);
				t = 150;
			}
			if(!t)
			{
				buzz(0);
				state = PAUSE_BETWEEN_TWO_SYMBOLS;
			}
			break;
		case DO_TA:
			if(entrance)
			{
				buzz(1);
				t = 500;
			}
			if(!t)
			{
				buzz(0);
				state = PAUSE_BETWEEN_TWO_SYMBOLS;
			}
			break;
		case PAUSE_BETWEEN_TWO_SYMBOLS:
			if(entrance)
				t = 300;
			if(!t)
				state = NEXT_SYMBOL;
			break;

		case LONG_PAUSE_BETWEEN_TWO_LETTERS:
			if(entrance)
				t = 1000;
			if(!t)
				state = NEXT_SYMBOL;
			break;
		default:
			break;
	}
	return ret;
}

void MORSE_demo(void)
{
	while(MORSE_state_machine_process_ms("SOS",FALSE) == IN_PROGRESS);
}



