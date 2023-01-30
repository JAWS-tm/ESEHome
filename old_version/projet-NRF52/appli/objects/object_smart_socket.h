#ifndef OBJECT_SMART_SOCKETH
#define OBJECT_SMART_SOCKETH
#include "../config.h"

typedef enum{
			INITSS,
			IDLE,
			DRIVEGPIO,
			SENDBS
		}stateSS_e;
		static stateSS_e stateSS = INITSS;

void OBJECT_SMART_SOCKET_Main(void);

#endif /* OBJECT_SMART_SOCKETH */
