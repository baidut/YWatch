
#if 0 // 测试代码，请忽略

#include <stdio.h>
#include "defines.h"
#include "debug.h"

int main(void)
{
    int num=1225;
    char ch='c';
    char str[]="hello world!";

    DEBUG_Init();

    DEBUG_OUT_CHAR(ch);
    DEBUG_OUT_STR(str);

    DEBUG_OUT_DEC(num);
    DEBUG_OUT_HEX(num);
    DEBUG_OUT_OCT(num);
    DEBUG_OUT_BIN(num);

    return 0;
}

#else // main ===================================================================

#include "usecases.h"

int main(void)
{
SYS_EVENT_e sysEvent=SYS_EVENT_NONE;

    USECASES_Init();

    for(;;){
        USECASES_ShowTime();
        USECASES_AlertWhenTimeUp();

        sysEvent =  USECASES_CheckEvent();
        TRACK(sysEvent,SYS_EVENT_e);// 追踪sysEvent变量的变化，以及时监测系统状态变化

        switch(sysEvent){
            case SYS_EVENT_SET_TIME :
                USECASES_SetTime();
                break;
            case SYS_EVENT_ADD_ALARMCLOCK:
                USECASES_AddAlarmClock();
                break;
            case SYS_EVENT_DEL_ALARMCLOCK:
                 USECASES_DelAlarmClock();
                break;
            default :break;
        }
    }
}
#endif
