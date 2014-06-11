#ifndef DEFINES_H_INCLUDED
#define DEFINES_H_INCLUDED

// Codeblock编译器设置
// debug版本预定义宏DEBUG_VERSION
// release版本预定义宏RELEASE_VERSION

//#define USE_DEFAULT_CFG

#ifdef USE_DEFAULT_CFG
    #define AUTO_GET_CUR_TIME // 自动获取当前时间
    #ifdef DEBUG_VERSION
        #define DEBUG
        #define DEBUG_ASSERT    // 进行断言检查
        #define DEBUG_CHECKPOINT// 检查点
        #define DEBUG_WATCH     // 查看变量信息
        #define DEBUG_TRACK     // 追踪变量
        #define DEBUG_HINT      // 操作提示
        #define DEBUG_LOG       // 操作记录入文件
    #elif defined(RELEASE_VERSION)
    #elif defined(DEMO_VERSION)
        #define AUTO_GET_CUR_TIME // 自动获取当前时间
        #define DEBUG    // 如果没有定义，则下面的宏不会输出信息
        #define DEBUG_HINT      // 操作提示
        #define DEBUG_LOG       // 操作记录入文件
    #endif // DEBUG_VERSION
#else
// 在这里添加你的自定义配置
    #define AUTO_GET_CUR_TIME // 自动获取当前时间

    #define DEBUG    // 如果没有定义，则下面的宏不会输出信息
    #define DEBUG_ASSERT    // 进行断言检查
    #define DEBUG_CHECKPOINT// 检查点
    #define DEBUG_WATCH     // 查看变量信息
    #define DEBUG_TRACK     // 追踪变量
    #define DEBUG_HINT      // 操作提示
    #define DEBUG_LOG       // 操作记录入文件
#endif

#endif // DEFINES_H_INCLUDED
