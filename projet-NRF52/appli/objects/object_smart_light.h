#ifndef OBJECT_SMART_LIGHTH
#define OBJECT_SMART_LIGHTH
#include "../config.h"




void Configuration(void);
char hour();
void Matin(void);
void Soir(void);
void Eteindre(void);
void Ambiance(void);
void AllumageComplet(void);
void Smart_light_Main(void);
void AllumageFroid(void);
void AllumageChaud(void);
bool_e DetectAppui(void);
int process_ms();



#endif /* OBJECT_SMART_LIGHTH */
