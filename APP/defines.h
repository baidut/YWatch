#ifndef DEFINES_H_INCLUDED
#define DEFINES_H_INCLUDED

// Codeblock����������
// debug�汾Ԥ�����DEBUG_VERSION
// release�汾Ԥ�����RELEASE_VERSION

//#define USE_DEFAULT_CFG

#ifdef USE_DEFAULT_CFG
    #define AUTO_GET_CUR_TIME // �Զ���ȡ��ǰʱ��
    #ifdef DEBUG_VERSION
        #define DEBUG
        #define DEBUG_ASSERT    // ���ж��Լ��
        #define DEBUG_CHECKPOINT// ����
        #define DEBUG_WATCH     // �鿴������Ϣ
        #define DEBUG_TRACK     // ׷�ٱ���
        #define DEBUG_HINT      // ������ʾ
        #define DEBUG_LOG       // ������¼���ļ�
    #elif defined(RELEASE_VERSION)
    #elif defined(DEMO_VERSION)
        #define AUTO_GET_CUR_TIME // �Զ���ȡ��ǰʱ��
        #define DEBUG    // ���û�ж��壬������ĺ겻�������Ϣ
        #define DEBUG_HINT      // ������ʾ
        #define DEBUG_LOG       // ������¼���ļ�
    #endif // DEBUG_VERSION
#else
// �������������Զ�������
    #define AUTO_GET_CUR_TIME // �Զ���ȡ��ǰʱ��

    #define DEBUG    // ���û�ж��壬������ĺ겻�������Ϣ
    #define DEBUG_ASSERT    // ���ж��Լ��
    #define DEBUG_CHECKPOINT// ����
    #define DEBUG_WATCH     // �鿴������Ϣ
    #define DEBUG_TRACK     // ׷�ٱ���
    #define DEBUG_HINT      // ������ʾ
    #define DEBUG_LOG       // ������¼���ļ�
#endif

#endif // DEFINES_H_INCLUDED
