
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
// 如果改成宏，务必要加上括号保护，否则容易出错，如调用 DISPLAY_ShowTime(*t) 就会出错
//#define DISPLAY_ShowTime(t)         do{\
                                        BACKSPACE(10);\
                                        printf("\b%02d: %02d: %02d",\
                                               (t).hour,(t).minute,(t).second)\
                                    }while(0)
