#ifdef __cplusplus
extern "C"{
#endif

#include "defines.h"
#ifdef DEBUG

#include "debug.h"
#include<windows.h>

HANDLE consolehwnd;//�����������ϸ���֪ʶ����ٶ�һ�»��MSDN
DEBUG_COLOR_e   OUTPUT_COLOR;
OUTPUT_POS_e    OUTPUT_POS=OUT_TO_SCREEN;

// ����������Ļ������ڵ�����Ϣ������ɫ�������û�����
void DEBUG_Init(){
    consolehwnd=GetStdHandle(STD_OUTPUT_HANDLE);//ʵ�������
    LOG_INIT();
}

#define FOREGROUND_WHITE        (FOREGROUND_RED |FOREGROUND_GREEN |FOREGROUND_BLUE)
#define _SET_COLOR(x)           do{SetConsoleTextAttribute(consolehwnd,(x));}while(0)

// ������չ����Զ�����������
void DEBUG_SetColor(DEBUG_COLOR_e c){
    switch(c){
        case COLOR_ASSERT : /* fall through */
        case COLOR_ERROR  : _SET_COLOR(FOREGROUND_RED | FOREGROUND_INTENSITY);break;
        case COLOR_TRACK  : /* fall through */
        case COLOR_WARNING: _SET_COLOR(FOREGROUND_RED |FOREGROUND_INTENSITY|FOREGROUND_GREEN);break;
        case COLOR_DEBUG  : _SET_COLOR(FOREGROUND_GREEN);break;
        case COLOR_DEFAULT: /* fall through */
        case COLOR_NORMAL : _SET_COLOR(FOREGROUND_WHITE); break;
        case COLOR_HINT   : _SET_COLOR(FOREGROUND_BLUE | FOREGROUND_RED |  FOREGROUND_INTENSITY); break;
        case COLOR_WATCH  : _SET_COLOR(FOREGROUND_BLUE | FOREGROUND_INTENSITY); break;
        default :break;
    }
}

#endif // DEBUG

#ifdef __cplusplus
}
#endif
