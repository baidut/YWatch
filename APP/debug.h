#ifndef DEBUG_H_INCLUDED
#define DEBUG_H_INCLUDED

#ifdef __cplusplus
extern "C"{
#endif

#define COMMENT_BEGIN    while(0){
#define COMMENT_END      }

// 调试信息属性设置
typedef enum{
	COLOR_WARNING,
	COLOR_ERROR,
	COLOR_DEFAULT,
	COLOR_DEBUG,
	COLOR_NORMAL,
	COLOR_HINT,
	COLOR_WATCH,
	COLOR_ASSERT,
	COLOR_TRACK
}DEBUG_COLOR_e;

typedef enum {
	OUT_TO_SCREEN,
	OUT_TO_FILE
}OUTPUT_POS_e;

// 禁用调试 ====================================================================
#ifndef DEBUG
	#define DEBUG_Init()
	#define DEBUG_OUT(FORMAT, ...)
#else

// 打开调试 ====================================================================
#include <stdio.h> // printf
#include <conio.h> // getch
#include <stdlib.h>// exit()
#include <string.h>// strlen()

extern DEBUG_COLOR_e OUTPUT_COLOR;
extern OUTPUT_POS_e OUTPUT_POS;

extern void DEBUG_Init();
extern void DEBUG_SetColor(DEBUG_COLOR_e color);

#define RESET_DEBUG_OUT()    \
do{\
	OUTPUT_COLOR=COLOR_DEFAULT;\
	OUTPUT_POS=OUT_TO_SCREEN;\
}while(0)

// 调试输出到文件或屏幕 ========================================================
#define DEBUG_FILE "D:/Users/admin/Desktop/watch/log.txt"//"/tmp/debugmsg" //log
#define DEBUG_BUFFER_MAX 4096//调试信息的缓冲长度

#define DEBUG_OUT(FORMAT,...)   do{\
		switch(OUTPUT_POS){\
			case OUT_TO_FILE:\
				do{\
					char buffer[DEBUG_BUFFER_MAX+1]={0};\
					snprintf( buffer, DEBUG_BUFFER_MAX, FORMAT, ##__VA_ARGS__ );\
					FILE* fd = fopen(DEBUG_FILE, "a");\
					if( fd != NULL ){\
						fwrite( buffer, strlen(buffer), 1, fd );\
						fflush( fd );\
						fclose( fd );\
					}\
				}while(0);\
				break;\
			case OUT_TO_SCREEN:\
				DEBUG_SetColor(OUTPUT_COLOR);\
				printf(FORMAT,##__VA_ARGS__);\
				DEBUG_SetColor(COLOR_NORMAL);\
				break;\
			default: break;\
		}\
	}while(0)
#endif // DEBUG

// 排版控制 ====================================================================
#define BR              DEBUG_OUT("\n")

// 变量按格式输出 ==============================================================
#define DEBUG_OUT_DATETIME()		DEBUG_OUT(" DATE: %s TIME: %s ",\
									__DATE__ , __TIME__)

#define DEBUG_OUT_STR(var)          DEBUG_OUT(" %s",(char*)var)
#define DEBUG_OUT_CHAR(var)         DEBUG_OUT(" %c",(char)var)

#define DEBUG_OUT_DEC(var)          DEBUG_OUT(" %d",(int)var)
#define DEBUG_OUT_HEX(var)          DEBUG_OUT(" %X",(int)var)
#define DEBUG_OUT_OCT(var)          DEBUG_OUT(" %o",(int)var)
#define DEBUG_OUT_BIN(var)  \
do{\
    int d=var;\
    long long int b=0;\
    long long int times=1;\
    while(d!=0){\
        b+=(d%2)*times;\
        d/=2;\
        times*=10;\
    }\
    DEBUG_OUT(" %I64d",b);\
}while(0)
// 可变参宏的参数遍历 ----------------------------------------------------------------------
#define STRINGIZE(arg)  STRINGIZE1(arg)
#define STRINGIZE1(arg) STRINGIZE2(arg)
#define STRINGIZE2(arg) #arg

#define CONCATENATE(arg1, arg2)   CONCATENATE1(arg1, arg2)
#define CONCATENATE1(arg1, arg2)  CONCATENATE2(arg1, arg2)
#define CONCATENATE2(arg1, arg2)  arg1##arg2

#define FOR_EACH_1(what, x, ...) what(x)
#define FOR_EACH_2(what, x, ...)\
  what(x);\
  FOR_EACH_1(what,  __VA_ARGS__);
#define FOR_EACH_3(what, x, ...)\
  what(x);\
  FOR_EACH_2(what, __VA_ARGS__);
#define FOR_EACH_4(what, x, ...)\
  what(x);\
  FOR_EACH_3(what,  __VA_ARGS__);
#define FOR_EACH_5(what, x, ...)\
  what(x);\
 FOR_EACH_4(what,  __VA_ARGS__);
#define FOR_EACH_6(what, x, ...)\
  what(x);\
  FOR_EACH_5(what,  __VA_ARGS__);
#define FOR_EACH_7(what, x, ...)\
  what(x);\
  FOR_EACH_6(what,  __VA_ARGS__);
#define FOR_EACH_8(what, x, ...)\
  what(x);\
  FOR_EACH_7(what,  __VA_ARGS__);

#define FOR_EACH_NARG(...) FOR_EACH_NARG_(__VA_ARGS__, FOR_EACH_RSEQ_N())
#define FOR_EACH_NARG_(...) FOR_EACH_ARG_N(__VA_ARGS__)
#define FOR_EACH_ARG_N(_1, _2, _3, _4, _5, _6, _7, _8, N, ...) N
#define FOR_EACH_RSEQ_N() 8, 7, 6, 5, 4, 3, 2, 1, 0

#define FOR_EACH_(N, what, x, ...) CONCATENATE(FOR_EACH_, N)(what, x, __VA_ARGS__)
#define FOR_EACH(what, x, ...) FOR_EACH_(FOR_EACH_NARG(x, __VA_ARGS__), what, x, __VA_ARGS__)

//#define DECLARE_DOUBLE(n) printf("double " #n "\n")
//#define MANY_DOUBLE(...) FOR_EACH(DECLARE_DOUBLE,##__VA_ARGS__)

#define DEBUG_OUT_ENUM(var,...)     \
	do{\
		switch(var){\
		FOR_EACH(_CASE,##__VA_ARGS__)\
		default:break;\
		}\
	}while(0)
	#define _CASE(i)    case i:DEBUG_OUT(" "#i);break;

// 特殊信息输出 ================================================================
#ifdef DEBUG_ASSERT
    #define ASSERT(expr) \
    do{\
	  if (expr) { ; } \
	  else  {\
		OUTPUT_COLOR=COLOR_ASSERT;\
		OUTPUT_POS=OUT_TO_SCREEN;\
		DEBUG_OUT("Assert failed: " #expr " \
		(function %s file %s line %d)\n", __FUNCTION__,__FILE__, (int) __LINE__ );\
		exit(1);/*while (1);*/\
	  }\
    }while(0)
#else
    #define	ASSERT(expr)
#endif
// -----------------------------------------------------------------------------
#ifdef DEBUG_CHECKPOINT
    #define CHECKPOINT()  \
        DEBUG_OUT("\r[%s] File:%s Line:%d\n", __FUNCTION__ ,__FILE__, __LINE__)
#else
    #define CHECKPOINT()
#endif // DEBUG_CHECKPOINT
// -----------------------------------------------------------------------------
#ifdef DEBUG_WATCH
#define WATCH(var,TYPE)  \
do{\
    OUTPUT_COLOR=COLOR_WATCH;\
    OUTPUT_POS=OUT_TO_SCREEN;\
    DEBUG_SetColor(COLOR_WARNING);\
    DEBUG_OUT(" $ %s = ",#var);\
    DEBUG_OUT_##TYPE (var);BR;\
}while(0)
#else
    #define	WATCH(var,TYPE)
#endif // DEBUG_WATCH
// -----------------------------------------------------------------------------
#ifdef DEBUG_TRACK
    #define TRACK(var,TYPE)  \
    do{\
        static void *p=NULL;\
        void *q=NULL;\
        void *tmp=NULL;\
        q=&(var);\
        if(p==NULL){\
            p=malloc(sizeof(var));\
            memcpy(p,q,sizeof(var));\
        }\
        if(0!=memcmp(p,q,sizeof(var))){\
            tmp=malloc(sizeof(var));\
            memcpy(tmp,q,sizeof(var));\
            memcpy(q,p,sizeof(var));\
            OUTPUT_COLOR=COLOR_TRACK;\
            OUTPUT_POS=OUT_TO_SCREEN;\
            DEBUG_OUT(" # %s CHANGED FROM ",#var);\
            DEBUG_OUT_##TYPE(var);\
            DEBUG_OUT(" TO ");\
            memcpy(q,tmp,sizeof(var));\
            DEBUG_OUT_##TYPE(var);\
            BR;\
            memcpy(p,q,sizeof(var));\
            free(tmp);\
        }\
    }while(0)
#else
    #define TRACK(var,TYPE)
#endif
// -----------------------------------------------------------------------------
#ifdef DEBUG_HINT
    #define HINT(FORMAT,...)     \
    do{\
        OUTPUT_COLOR=COLOR_HINT;\
        OUTPUT_POS=OUT_TO_SCREEN;\
        DEBUG_OUT(FORMAT,##__VA_ARGS__ );BR;\
    }while(0)
#else
    #define HINT(FORMAT,...)
#endif // DEBUG_HINT
// -----------------------------------------------------------------------------
#ifdef DEBUG_LOG
    #define LOG_BEGIN   \
    do{\
        OUTPUT_POS=OUT_TO_FILE;\
        DEBUG_OUT_DATETIME();\
    }while(0);
    #define LOG_END RESET_DEBUG_OUT();
#else
    #define LOG_BEGIN	COMMENT_BEGIN
    #define LOG_END		COMMENT_END
#endif // DEBUG_LOG
#define LOG_INIT()   \
		LOG_BEGIN\
			DEBUG_OUT("SYSTEM START ");BR;\
		LOG_END
// -----------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif

#endif  // DEBUG_H_INCLUDED
