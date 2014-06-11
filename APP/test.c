
#ifdef TEST_KEY
#include "key.h"
int main(void)
{
ACTIVE_KEY_e key = ACTIVE_KEY_NONE;

    for(;;){
        key=KEYS_SCan();
        switch(key){
            case ACTIVE_KEY_NONE : break;
            case ACTIVE_KEY_ADD  : printf("ACTIVE_KEY_ADD\n");break;
            case ACTIVE_KEY_SUB  : printf("ACTIVE_KEY_SUB\n");break;
            case ACTIVE_KEY_OK   : printf("ACTIVE_KEY_OK\n");break;

            default : printf("DEFAULT\n"); break;
        }
    }
    return 0;
}
#elif defined(TEST_TIMER)

#include "timer.h"

int main(void)
{
    Time_t t;
    TIMER_Init();
    for(;;){
        t=TIMER_GetCurTime ();
        printf("\r%02d:%02d:%02d",t.hour,t.minute,t.second);
    }
}
#elif defined(TEST_BUZZER)
#include <conio.h>
#include "buzzer.h"
int main(void)
{
char ch;


    BUZZER_Init();
    while(1){
        if( kbhit() ){
            ch=getch();
            switch(ch){
                case 'k'  : BUZZER_On();break;
                case 'g'  : BUZZER_Off();break;
                case 'h'  : BUZZER_Turn(); break;
                default : break; // KEY_NONE
            }
        }
    }
}
#endif




