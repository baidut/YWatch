/*************************************************************************
 * ����ָ��
 * ״̬       ADD       SUB         OK          MENU
 * ����       ������� ɾ������                 ����ʱ��
 * ����ʱ��   ��       ��           ȷ�Ϸ���    �л�����ʱ/��
 * �������   ��       ��           ȷ�Ϸ���    �л�����ʱ/��
 * ɾ������            ɾ��         ����        �л�����
 *************************************************************************/
#include "usecases.h"
#include "key.h"
#include "timer.h"
#include "display.h"
#include "buzzer.h"

// ȫ�ֱ��� ============================================================
#define MAX_ALARM_CLOCK_NUM 20 // ���֧��N������
struct {
    Time_t time;
    enum{NOTALERTED,ALERTED} status;
}alarmClock[MAX_ALARM_CLOCK_NUM];
int alarmClockNum=0;

// �Զ��������� ========================================================
#define DEBUG_OUT_CLOCK_STATUS(var) DEBUG_OUT_ENUM(var,NOTALERTED,ALERTED)
#define DEBUG_OUT_CLOCK(var)    \
do{\
    DEBUG_OUT_Time_t((var).time);\
    DEBUG_OUT_CLOCK_STATUS((var).status);\
}while(0)

/*************************************************************************
 * Parameters:    ��
 * Return:        ��
 *
 * Description: ��ʼ������ʹ�õ��ĸ���Ӳ��ģ��
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
 * Parameters:    ��
 * Return:        ϵͳ�������¼�
 *
 * Description: ͨ��������������ϵͳ�¼���ADD����������ӣ�SUB����ɾ��
 * ���ӣ�MENU��������ʱ��
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
 * Parameters:    ��
 * Return:        ��
 *
 * Description: ͨ����ʱ����ȡʱ�䣬��ʾ�豸��ʾʱ��
 *************************************************************************/
void USECASES_ShowTime(){
Time_t now=TIMER_GetCurTime();
    DISPLAY_ShowTime(now);
}
/*************************************************************************
 * Parameters:    ���޸ĵ�ʱ��ֵ
 * Return:        ��
 *
 * Description: ͨ����ʾ�豸�͹��ܰ�������һ��ʱ��ֵ������MENU�л�
 * ����Сʱ�����÷��ӣ�����ADD��SUB����ֵ�ļӼ�������OKȷ�����ò����ء�
 *************************************************************************/
static void setTime(Time_t* time2Set){
enum{
	MENU_SET_HOUR,
	MENU_SET_MINUTE,
	MENU_NUM
}menu=MENU_SET_HOUR;
int val2Set=0; // val2Set ������int*ָ�뷽ʽ������������չ ����ֱ���޸�ֵ������ȫ
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
 * Parameters:    ��
 * Return:        ��
 *
 * Description: ͨ����ʾ�豸�͹��ܰ�������ʱ��
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
 * Description:  ���һ��ʱ�䵽�˻����Ѿ���ȥ�ˣ��򷵻�true
 *************************************************************************/
static bool_t isPassed(Time_t t){
Time_t now = TIMER_GetCurTime();
    if(t.hour<now.hour)return true;
    if(t.hour>now.hour)return false;
    if(t.minute<=now.minute)return true;
    else return false;
}
/*************************************************************************
 * Parameters:    ��
 * Return:        ��
 *
 * Description: ͨ����ʾ�豸�͹��ܰ������һ������
 *************************************************************************/
void USECASES_AddAlarmClock(){
Time_t t=TIMER_GetCurTime();

    HINT("ADD ALARM CLOCK BEGIN");

    setTime(&t);
    alarmClock[alarmClockNum].time.hour=t.hour;// alarmClock[alarmClockNum].time=t;
    alarmClock[alarmClockNum].time.minute=t.minute;

    if(isPassed(t)) alarmClock[alarmClockNum].status = ALERTED;// ���ʱ���Ѿ����ˣ�������״̬Ϊ�Ѿ����ѹ��������������ˡ�
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
    // ����Ƿ���������õ������ظ�
}
/*************************************************************************
 * Parameters:    ��
 * Return:        ��
 *
 * Description: ͨ����ʾ�豸�͹��ܰ���ɾ�����õ����ӣ�����MENU�л�
 * ��ʾ�������ӣ�����SUBɾ�����ӣ�����OKȷ�����ò����ء�
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

                while(i<alarmClockNum){ // ��Ч����ֵ����
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

                i=0; // ��ͷ��ʼ��ʾ
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
 * Parameters:    ��
 * Return:        ��
 *
 * Description: ͨ����ʱ����ȡʱ��
 *************************************************************************/
void USECASES_AlertWhenTimeUp(){
int i;
    for(i=0;i<alarmClockNum;i++){
        if(isPassed(alarmClock[i].time)){ // ʱ���Ѿ�����
            if(NOTALERTED==alarmClock[i].status){
                alarmClock[i].status = ALERTED;
                BUZZER_On();

                HINT("ALARMCLOCK");
                DEBUG_OUT_CLOCK(alarmClock[i]);
                BR;

                break; // ����ѭ��
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
            break;// �������ֹͣ�죬5���Ӻ����죬��ɾ�����ӵĹ���
        }
    }
}
