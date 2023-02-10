/*
 * object_base_station.h
 *
 *  Created on: 08 fev. 2023
 *      Author: demptjul
 */
 
#include "../config.h"

#if OBJECT_ID == OBJECT_BASE_STATION
#include "object_base_station.h"
#include "../common/macro_types.h"
#include "../common/rf_dialog.h"
#include "../common/serial_dialog.h"
#include "../common/verbose.h"

bool_e initialized = FALSE;

void BASE_STATION_pong_callback(void);


void BASE_STATION_init(void) {
	RF_DIALOG_set_callback_pong((callback_fun_t) &BASE_STATION_pong_callback);
}

void BASE_STATION_process_main()
{
	typedef enum {
		INIT,
		PROCESS
	} state_e;

	static state_e state = INIT;

	switch (state)
	{
		case INIT: {
			if (!initialized)
			{
				initialized = TRUE;
				BASE_STATION_init();
			}

			state = PROCESS;
			break;
		}
		case PROCESS: {
			VERBOSE_process_main();
			break;
		}
	}
}

void BASE_STATION_pong_callback(void) {
	debug_printf("BASE STATION: pong reçu");
}

#endif
