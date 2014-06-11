
#include "key.h"
#include <conio.h>

char KEYS[KEY_NUM]={
#define KEY(k, s)   s,
#include "key.cfg"
#undef  KEY
};

void KEYS_Init(){
    CHECKPOINT();
}

KEY_e KEYS_SCan (void){
    KEY_e i=0;
    char ch;

    if(!kbhit())return KEY_NONE;
    ch=getch();
    for(i=0;i<KEY_NUM;i++){
        if(KEYS[i]==ch)return i;
    }
    return KEY_NONE; // 不是待检测的按键
}




// ACTIVE_KEY_NONE  change to KEY_NONE
//#define KEY_IO_LIST
// #define LEN(arr)  (sizeof arr/sizeof arr[0])
// LEN(KEYS);

