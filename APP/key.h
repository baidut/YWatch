#ifndef __KEY_H__

#include "common.h"

typedef enum{
#define KEY(k, s)   k,
#include "key.cfg"
#undef  KEY
    KEY_NONE,
    KEY_NUM = KEY_NONE
}KEY_e;

void KEYS_Init(void);
KEY_e KEYS_SCan (void);

#endif // __KEY_H__
