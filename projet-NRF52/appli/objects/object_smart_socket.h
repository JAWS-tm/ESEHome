#ifndef OBJECT_SMART_SOCKETH
#define OBJECT_SMART_SOCKETH
#include "../config.h"

typedef enum{
			INITSS,
			IDLE,
			DRIVEGPIO
		}stateSS_e;
		static stateSS_e stateSS = INITSS;

void OBJECT_SMART_SOCKET_Main(void);
void configPin(void);

#endif /* OBJECT_SMART_SOCKETH */
