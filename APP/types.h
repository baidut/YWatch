#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

// Basic Types =====================================================================
typedef enum{false,true=!false} bool_t;

typedef signed char int8_t;
typedef unsigned char uint8_t;

typedef int int16_t;
typedef unsigned int uint16_t;

typedef long int32_t;
typedef unsigned long uint32_t;

// typedef long long int64_t;
// typedef unsigned long long uint64_t;

// typedef int16_t* intptr_t;
// typedef uint16_t* uintptr_t;

// User Types =====================================================================

typedef struct{
	uint8_t minute;
    uint8_t second;
    uint8_t hour;
}Time_t;

#define DEBUG_OUT_Time_t(t)           DEBUG_OUT(" %02d: %02d: %02d",\
                                                (t).hour,(t).minute,(t).second)

typedef enum {
	SYS_EVENT_SET_TIME,
	SYS_EVENT_ADD_ALARMCLOCK,
	SYS_EVENT_DEL_ALARMCLOCK,

	SYS_EVENT_NONE
}SYS_EVENT_e;

#define DEBUG_OUT_SYS_EVENT_e(s)     DEBUG_OUT_ENUM(s,  SYS_EVENT_SET_TIME,\
                                                        SYS_EVENT_ADD_ALARMCLOCK,\
                                                        SYS_EVENT_DEL_ALARMCLOCK,\
                                                        SYS_EVENT_NONE)
#endif // TYPES_H_INCLUDED
