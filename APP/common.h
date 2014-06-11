#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

// 实用工具宏 ===================================================================
#define LEN(arr)  (sizeof arr/sizeof arr[0])        // 求数组长度

// 位操作 ----------------------------------------------------------------------
/* avr/sfr_defs.h
http://www.nongnu.org/avr-libc/user-manual/sfr__defs_8h_source.html
 */
/* Bit manipulation */
#define _BV(bit) (1 << (bit))

/* IO register bit manipulation */
#define SET_BIT(reg, bit) ((reg) |= _BV(bit))
#define CLR_BIT(reg, bit) ((reg) &= ~_BV(bit)))

#define BIT_CLR_MSK(LVALUE, MASK)   (LVALUE &= ~(MASK))             /* 位清0,操作MASK指定的位,可以多位 */
#define BIT_REV_MSK(LVALUE, MASK)   (LVALUE ^=  (MASK))             /* 位取反,操作MASK指定的位,可以多位*/

// #define MALLOC(p,TYPE)              do{while( ! (p=(TYPE*)malloc(sizeof(TYPE))) );}while(0)

// 值为传入宏的参数个数 ----------------------------------------------------------------------
/* The PP_NARG macro returns the number of arguments that have been
  * passed to it.
  */
#define PP_NARG(...) \
         PP_NARG_(__VA_ARGS__,PP_RSEQ_N())
#define PP_NARG_(...) \
         PP_ARG_N(__VA_ARGS__)
#define PP_ARG_N( \
          _1, _2, _3, _4, _5, _6, _7, _8, _9,_10, \
         _11,_12,_13,_14,_15,_16,_17,_18,_19,_20, \
         _21,_22,_23,_24,_25,_26,_27,_28,_29,_30, \
         _31,_32,_33,_34,_35,_36,_37,_38,_39,_40, \
         _41,_42,_43,_44,_45,_46,_47,_48,_49,_50, \
         _51,_52,_53,_54,_55,_56,_57,_58,_59,_60, \
         _61,_62,_63,N,...) N
#define PP_RSEQ_N() \
         63,62,61,60, \
         59,58,57,56,55,54,53,52,51,50, \
         49,48,47,46,45,44,43,42,41,40, \
         39,38,37,36,35,34,33,32,31,30, \
         29,28,27,26,25,24,23,22,21,20, \
         19,18,17,16,15,14,13,12,11,10, \
         9,8,7,6,5,4,3,2,1,0
/**
 *  @brief 仿二进制赋值
 */
#define  HEX__(n)   0x##n##UL
#define  B8__(x)   ( (x & 0x0000000FUL) ? 1:0 )\
    +( (x & 0x000000F0UL) ? 2:0 )\
    +( (x & 0x00000F00UL) ? 4:0 )\
    +( (x & 0x0000F000UL) ? 8:0 )\
    +( (x & 0x000F0000UL) ? 16:0 )\
    +( (x & 0x00F00000UL) ? 32:0 )\
    +( (x & 0x0F000000UL) ? 64:0 )\
    +( (x & 0xF0000000UL) ? 128:0 )
#define  B8(x)                                     ((unsigned char)B8__(HEX__(x)))
#define  B16(x_msb,x_lsb)                (((unsigned int)B8(x_msb)<<8) + B8(x_lsb))
#define  B32(x_msb,x_2,x_3,x_lsb)   (((unsigned long)B8(x_msb)<<24) + ((unsigned long)B8(x_2)<<16) + ((unsigned long)B8(x_3)<<8) + B8(x_lsb))
/* Sample usage:
B8(01010101) = 85
B16(10101010,01010101) = 43605
B32(10000000,11111111,10101010,01010101) = 2164238933
*/

/*
 * 求最大值和最小值
 */
#define MAX( x, y ) ( ((x) > (y)) ? (x) : (y) )
#define MIN( x, y ) ( ((x) < (y)) ? (x) : (y) )

/*
 * 返回数组元素的个数
 */
#define ARR_SIZE( a ) ( sizeof( (a) ) / sizeof( ((a)[0]) ) )

/*
 * 宏定义实现返回绝对值（x里不能有自加自减的语句，否则变量出错）
 */
#define ABS(x) (((x) > 0) ? (x) : (-x))

/*
 * 获取结构体某成员偏移
 */
#define OFFSET(type, member)    (uint32)(&(((type *)0)->member))

/*
 * 确保x的范围为 min~max
 */
#define RANGE(x,max,min)        ((uint8)((x)<(min) ? (min) : ( (x)>(max) ? (max):(x) )))

/*
 * 交换32位数据的4字节顺序
 */
#define SWAP32(data)    (uint32)((((uint32)(data) & (0xFFu<<0 ))<<24)      \
                          | (((uint32)(data) & (0xFFu<<8 ))<<8)            \
                          | (((uint32)(data) & (0xFFu<<16))>>8)            \
                          | (((uint32)(data) & (0xFFu<<24))>>24)           \
                        )

/*
 * 交换16位数据的2字节顺序
 */
#define SWAP16(data)    (uint32)((((uint16)(data) & (0xFF<<0 ))<<8)      \
                          | (((uint32)(data) & (0xFF<<8))>>8)            \
                        )

/*
 * 交换 x, y 的值
 */
#define SWAP(x,y)           do{x^=y;y^=x;x^=y;}while(0)


#include "defines.h"
#include "types.h"
#include "debug.h"

#endif // COMMON_H_INCLUDED
