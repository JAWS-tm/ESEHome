// Eclairage nocturne avec des LEDS RGB WS2812

#include "../config.h"
#include "../../bsp/WS2812.h"


#if OBJECT_ID == OBJECT_NIGHT_LIGHT

void RGB_state_machine(){
	typedef enum{
			INIT,
			RUN,
			SLEEP
		}state_e;

	static state_e state = INIT;

	switch(state){
		case INIT:
			LEDS_init(24,30);
			state = RUN;
		break;
	}

	case RUN:{
		LEDS_display_full();

		break;
	}

	case SLEEP:{
		break;
	}

	default:
		break;
	}
}

#endif
