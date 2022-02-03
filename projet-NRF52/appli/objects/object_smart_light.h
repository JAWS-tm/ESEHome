#ifndef OBJECT_SMART_LIGHTH
#define OBJECT_SMART_LIGHTH
#include "../config.h"

#if OBJECT_ID == OBJECT_SMART_SOCKET
typedef enum{
			DEBUT,
			ALLUMAGE,
			CHAUD,
			FROID,
			EXTINCTION,
		}mode_e;
		static mode_e mode = DEBUT;

void Configuration(void);
void Eteindre(void);
void AllumageTotale(void);
void Smart_light_Main(void);
void AllumageFroid(void);
void AllumageChaud(void);
bool_e DetectAppui(void);
void OBJECT_SMART_LIGHT_UPDATED_MODE_callback(mode_e new_mode);


#endif

#endif /* OBJECT_SMART_LIGHTH */
