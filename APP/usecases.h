#ifndef USECASES_H_INCLUDED
#define USECASES_H_INCLUDED

#include "common.h"

void        USECASES_Init();
SYS_EVENT_e USECASES_CheckEvent();
void        USECASES_ShowTime();
void        USECASES_SetTime();
void        USECASES_AddAlarmClock();
void        USECASES_DelAlarmClock();
void        USECASES_AlertWhenTimeUp();

#endif // USECASES_H_INCLUDED
