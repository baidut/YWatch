
#include <stdio.h>
#include <stdlib.h>
#include "display.h"

#define BACKSPACE(x)                do{int i=x;while(i--)printf("\b");}while(0)
void DISPLAY_Init(){
    CHECKPOINT();
}

void DISPLAY_ShowTime(Time_t t){
    printf("%02d: %02d: %02d",t.hour,t.minute,t.second);
    BACKSPACE(10);
}

//printf("\r %02d: %02d: %02d",(t).hour,(t).minute,(t).second)
// #define DISPLAY_FlashLowBit()       printf("\b\b")
// #define DISPLAY_FlashHighBit()      printf("\r")
// ����ĳɺ꣬���Ҫ�������ű������������׳�������� DISPLAY_ShowTime(*t) �ͻ����
//#define DISPLAY_ShowTime(t)         do{\
                                        BACKSPACE(10);\
                                        printf("\b%02d: %02d: %02d",\
                                               (t).hour,(t).minute,(t).second)\
                                    }while(0)
