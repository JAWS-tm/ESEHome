#ifndef OBJECT_SMART_SOCKETH
#define OBJECT_SMART_SOCKETH
#include "../config.h"

#define REFRESH 10 //ms

#define CYCLE 100 //ms

#define LIM_COURANT 800 //mA


typedef enum{
			INITSS,
			IDLE,
			DRIVEGPIO,
			SENDBS
		}stateSS_e;
		static stateSS_e stateSS = INITSS;

void OBJECT_SMART_SOCKET_Main(void);

#endif /* OBJECT_SMART_SOCKETH */
