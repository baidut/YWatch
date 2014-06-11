#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

#include "common.h"

void    TIMER_Init();
Time_t  TIMER_GetCurTime();
void    TIMER_SetCurTime(Time_t);

#endif // TIMER_H_INCLUDED
