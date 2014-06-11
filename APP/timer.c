
#include "timer.h"
#include <time.h>

#ifdef USE_DEFAULT_CFG
    #define AUTO_GET_CUR_TIME // 自动获取当前时间
#endif

Time_t sysTime;
time_t time_last,time_now;

void TIMER_Init(){
    CHECKPOINT();
#ifdef AUTO_GET_CUR_TIME
    time_t rawtime;
    struct tm * timeinfo;

    time ( &rawtime ); // 获取时间，以秒计，从1970年1月一日起算，存于rawtime
    timeinfo = localtime ( &rawtime );
    sysTime.hour=timeinfo->tm_hour;
    sysTime.minute=timeinfo->tm_min;
    sysTime.second=timeinfo->tm_sec;
#else
    sysTime=(Time_t){0,0,0};
#endif
    time_now = time_last = time(NULL);
}
static int tim2sec(Time_t t){
    return ((t.hour)*3600+(t.minute)*60+t.second);
}
static Time_t sec2tim(int sec){
#define HOUR_PER_DAY        24
#define MINUTES_PER_HOUR    60
#define SECONDS_PER_MINUTES 60

    Time_t tim;
    tim.second = sec%SECONDS_PER_MINUTES;
    tim.minute = (sec/SECONDS_PER_MINUTES)%MINUTES_PER_HOUR;
    tim.hour = (sec/(SECONDS_PER_MINUTES*MINUTES_PER_HOUR))%HOUR_PER_DAY;
    return tim;
}
static void TIMER_Update(void){
    // static clock_t time_last=0,time_now=0;

    unsigned int secondsElapsed;

    time_now = time(NULL);// time_now = clock();
    secondsElapsed = difftime(time_now,time_last);
    time_last = time_now;

    sysTime = sec2tim( tim2sec(sysTime)+secondsElapsed );
}

Time_t TIMER_GetCurTime(){
    TIMER_Update();
    return sysTime;
}
void   TIMER_SetCurTime(Time_t t){
    TIMER_Update();// 更新timer才能去掉经过的时间
    sysTime=t;
}


// printf ( "Year: %d ", t->tm_year+1900 );
// printf ( "Month: %d ", t->tm_mon +1 );
// printf ( "day: %d ", t->tm_mday);
// printf ( "hour: %d ", t->tm_hour);
// printf ( "minute: %d ", t->tm_min);
// printf ( "second: %d\n", t->tm_sec);

// #ifdef DEMO_MODE
//     ret.hour=(secondsElapsed/60)%24;
//     ret.minute=secondsElapsed%60;
// #else
//     ret.hour=(secondsElapsed/60)%24;
//     ret.minute=secondsElapsed%60;
// #endif

// void wait ( int seconds )
// {
//   clock_t endwait;
//   endwait = clock () + seconds * CLOCKS_PER_SEC ;
//   while (clock() < endwait) {}
// }
