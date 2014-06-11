/*************************************************************************
 * 操作指南
 * 状态       ADD       SUB         OK          MENU
 * 空闲       添加闹钟 删除闹钟                 设置时间
 * 设置时间   加       减           确认返回    切换设置时/分
 * 添加闹钟   加       减           确认返回    切换设置时/分
 * 删除闹钟            删除         返回        切换闹钟
 *************************************************************************/
#include "usecases.h"
#include "key.h"
#include "timer.h"
#include "display.h"
#include "buzzer.h"

// 全局变量 ============================================================
#define MAX_ALARM_CLOCK_NUM 20 // 最多支持N个闹钟
struct {
    Time_t time;
    enum{NOTALERTED,ALERTED} status;
}alarmClock[MAX_ALARM_CLOCK_NUM];
int alarmClockNum=0;

// 自定义调试输出 ========================================================
#define DEBUG_OUT_CLOCK_STATUS(var) DEBUG_OUT_ENUM(var,NOTALERTED,ALERTED)
#define DEBUG_OUT_CLOCK(var)    \
do{\
    DEBUG_OUT_Time_t((var).time);\
    DEBUG_OUT_CLOCK_STATUS((var).status);\
}while(0)

/*************************************************************************
 * Parameters:    无
 * Return:        无
 *
 * Description: 初始化用例使用到的各个硬件模块
 *************************************************************************/
#define HINT_MAINMENU()    HINT_KEYS("CHANGE TIME","ADD ALARM CLOCK","DEL ALARM CLOCK","--")
void USECASES_Init(){
    DEBUG_Init();
    TIMER_Init();
    KEYS_Init();
    BUZZER_Init();
    DISPLAY_Init();

    HINT_MAINMENU();
}
/*************************************************************************
 * Parameters:    无
 * Return:        系统发生的事件
 *
 * Description: 通过按键触发各种系统事件。ADD按键添加闹钟，SUB按键删除
 * 闹钟，MENU按键设置时间
 *************************************************************************/
SYS_EVENT_e USECASES_CheckEvent(){
KEY_e key=KEY_NONE;
    key=KEYS_SCan();
    switch(key){
        case KEY_ADD    : return SYS_EVENT_ADD_ALARMCLOCK;
        case KEY_SUB    : return SYS_EVENT_DEL_ALARMCLOCK;
        case KEY_MENU   : return SYS_EVENT_SET_TIME;
        default :break;
    }
    return SYS_EVENT_NONE;
}
/*************************************************************************
 * Parameters:    无
 * Return:        无
 *
 * Description: 通过定时器获取时间，显示设备显示时间
 *************************************************************************/
void USECASES_ShowTime(){
Time_t now=TIMER_GetCurTime();
    DISPLAY_ShowTime(now);
}
/*************************************************************************
 * Parameters:    待修改的时间值
 * Return:        无
 *
 * Description: 通过显示设备和功能按键设置一个时间值，按键MENU切换
 * 设置小时和设置分钟，按键ADD和SUB进行值的加减，按键OK确认设置并返回。
 *************************************************************************/
static void setTime(Time_t* time2Set){
enum{
	MENU_SET_HOUR,
	MENU_SET_MINUTE,
	MENU_NUM
}menu=MENU_SET_HOUR;
int val2Set=0; // val2Set 不能用int*指针方式操作，不便扩展 而且直接修改值，不安全
KEY_e key = KEY_NONE;
int isSetFinished;

    HINT_KEYS("SWITCH HOUR/MINUTE","VALUE ADD 1","VALUE SUB 1","FINISHED AND BACK");

    isSetFinished=0;
    while(!isSetFinished){
        DISPLAY_ShowTime(*time2Set);
        switch(menu){
            case MENU_SET_HOUR  : val2Set = time2Set->hour;  break;
            case MENU_SET_MINUTE: val2Set = time2Set->minute;break;
            default :break;
        }
        key=KEYS_SCan();
        switch(key){
            case KEY_ADD  : val2Set++ ;break;
            case KEY_SUB  : val2Set-- ;break;
            case KEY_OK   : isSetFinished = 1; break;
            case KEY_MENU : menu++;menu%=MENU_NUM; break;
            default : break; // KEY_NONE
        }
        switch(key){
            case KEY_ADD  :
            case KEY_SUB  :
                switch(menu){
                    case MENU_SET_HOUR  : time2Set->hour = (val2Set+24)%24 ;  break;
                    case MENU_SET_MINUTE: time2Set->minute = (val2Set+60)%60 ;break;
                    default :break;
                }
                break;
            default : break; // KEY_NONE
        }
    }
}
/*************************************************************************
 * Parameters:    无
 * Return:        无
 *
 * Description: 通过显示设备和功能按键设置时间
 *************************************************************************/
void USECASES_SetTime(){
Time_t now = TIMER_GetCurTime();

    HINT("SET TIME BEGIN");

    setTime(&now);
    TIMER_SetCurTime(now);

    LOG_BEGIN
        DEBUG_OUT("SET TIME TO");
        DEBUG_OUT_Time_t(now);
        BR;
    LOG_END

    HINT("SET TIME FINISHED");
    HINT_MAINMENU();
}
/*************************************************************************
 * Description:  如果一个时间到了或者已经过去了，则返回true
 *************************************************************************/
static bool_t isPassed(Time_t t){
Time_t now = TIMER_GetCurTime();
    if(t.hour<now.hour)return true;
    if(t.hour>now.hour)return false;
    if(t.minute<=now.minute)return true;
    else return false;
}
/*************************************************************************
 * Parameters:    无
 * Return:        无
 *
 * Description: 通过显示设备和功能按键添加一个闹钟
 *************************************************************************/
void USECASES_AddAlarmClock(){
Time_t t=TIMER_GetCurTime();

    HINT("ADD ALARM CLOCK BEGIN");

    setTime(&t);
    alarmClock[alarmClockNum].time.hour=t.hour;// alarmClock[alarmClockNum].time=t;
    alarmClock[alarmClockNum].time.minute=t.minute;

    if(isPassed(t)) alarmClock[alarmClockNum].status = ALERTED;// 如果时间已经过了，就设置状态为已经提醒过，无需再提醒了。
    else alarmClock[alarmClockNum].status = NOTALERTED;

    CHECKPOINT();
    WATCH(alarmClockNum,DEC);
    WATCH(alarmClock[alarmClockNum],CLOCK);

    LOG_BEGIN
        DEBUG_OUT("NEW CLOCK: ");
        DEBUG_OUT_CLOCK(alarmClock[alarmClockNum]);
        BR;
    LOG_END

    HINT("ADD ALARM CLOCK FINISHED");
    HINT_MAINMENU();

    alarmClockNum++;
    // 检查是否和以往设置的闹钟重复
}
/*************************************************************************
 * Parameters:    无
 * Return:        无
 *
 * Description: 通过显示设备和功能按键删除设置的闹钟，按键MENU切换
 * 显示各个闹钟，按键SUB删除闹钟，按键OK确认设置并返回。
 *************************************************************************/
void USECASES_DelAlarmClock(){
int i=0;
KEY_e key=KEY_NONE;
bool_t isSetFinished=0;

    HINT("DELETE ALARM CLOCK");
    HINT_KEYS("SWITCH CLOCK"," ","DELETE IT","FINISHED AND BACK");

    if(0==alarmClockNum) return;
    while(!isSetFinished){
        DISPLAY_ShowTime(alarmClock[i].time);
        key=KEYS_SCan();
        switch(key){
            /*case KEY_ADD  :
                alarmClock[i]=setTime(&(alarmClock[i]));
                break;*/
            case KEY_SUB  :
                if(alarmClockNum>0)alarmClockNum--;

                while(i<alarmClockNum){ // 有效闹钟值更新
                    alarmClock[i] = alarmClock[i+1];
                    i++;
                }
                HINT("DELETE FINISHED");
                CHECKPOINT();
                WATCH(alarmClock[i],CLOCK);
                LOG_BEGIN
                    DEBUG_OUT("DEL CLOCK: ");
                    DEBUG_OUT_CLOCK(alarmClock[alarmClockNum]);
                    BR;
                LOG_END

                i=0; // 从头开始显示
                break;
            case KEY_OK   :
                isSetFinished=1;

                HINT_MAINMENU();

                break;
            case KEY_MENU :
                i++;
                i%=alarmClockNum;
                break;
            default : break; // KEY_NONE
        }
    }

}
/*************************************************************************
 * Parameters:    无
 * Return:        无
 *
 * Description: 通过定时器获取时间
 *************************************************************************/
void USECASES_AlertWhenTimeUp(){
int i;
    for(i=0;i<alarmClockNum;i++){
        if(isPassed(alarmClock[i].time)){ // 时间已经过了
            if(NOTALERTED==alarmClock[i].status){
                alarmClock[i].status = ALERTED;
                BUZZER_On();

                HINT("ALARMCLOCK");
                DEBUG_OUT_CLOCK(alarmClock[i]);
                BR;

                break; // 跳出循环
            }
        }
        else{
            alarmClock[i].status=NOTALERTED;
        }
    }
    if(i==alarmClockNum)return;
    while(1){
        BUZZER_On();
        if(KEY_NONE!=KEYS_SCan()){
            BUZZER_Off();
            break;// 可以添加停止响，5分钟后再响，和删除闹钟的功能
        }
    }
}
