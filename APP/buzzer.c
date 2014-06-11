
#include "buzzer.h"

#include <windows.h>

#define PRESS_KEY(key)    do{keybd_event ((key), 0, 0, 0);keybd_event ((key), 0, KEYEVENTF_KEYUP, 0);}while(0)

#define ADD_SOUND()       PRESS_KEY(0xAF)
#define SUB_SOUND()       PRESS_KEY(0xAE)
#define SWITCH_SOUND()    PRESS_KEY(0xAD)

int isBuzzerOn=1;

void BUZZER_Init(){
    CHECKPOINT();

    BUZZER_Off();
}
void BUZZER_On(){
    if(!isBuzzerOn){SWITCH_SOUND();isBuzzerOn=1;}
}
void BUZZER_Off(){
	if(isBuzzerOn){SWITCH_SOUND();isBuzzerOn=0;}
}
void BUZZER_Turn(){
	SWITCH_SOUND();
	isBuzzerOn=!isBuzzerOn;
}
// ��򵥵ı��ʵ��Windowsϵͳ���������� http://blog.csdn.net/santook/article/details/10949765
// http://www.360doc.com/content/11/0424/23/4780948_112079492.shtml
// ʹ��Windows API����ϵͳ����������
// һ������API����
// [DllImport("user32.dll", CharSet = CharSet.Auto, SetLastError = true)]  static extern IntPtr SendMessage(IntPtr hWnd, uint Msg, uint wParam, uint lParam);    const uint WM_APPCOMMAND = 0x319;  const uint APPCOMMAND_VOLUME_UP = 0x0a;  const uint APPCOMMAND_VOLUME_DOWN = 0x09;  const uint APPCOMMAND_VOLUME_MUTE = 0x08;
// ���� �������
// SendMessage(this.Handle, WM_APPCOMMAND, 0x30292, APPCOMMAND_VOLUME_UP * 0x10000);
// ���� ��������
// SendMessage(this.Handle, WM_APPCOMMAND, 0x30292, APPCOMMAND_VOLUME_DOWN * 0x10000);
// �ġ� ������ָ���ִ��2�λָ�ԭ״̬��
// SendMessage(this.Handle, WM_APPCOMMAND, 0x200eb0, APPCOMMAND_VOLUME_MUTE * 0x10000);

// Beep(587,500);
// Beep(659,500);
// Beep(698,500);
// Beep(784,500);

// fprintf(stderr,"\007");
// fprintf(stdout,"\007");
// printf("\007");

// MessageBeep(0xFFFFFFFF);//API����ǰ�ӡ�::�����ţ���ʾ����һ��ȫ�ֵĺ���������c++��ĳ�Ա����������
// Sleep(1000);
// MessageBeep(MB_ICONASTERISK);
// Sleep(1000);
// MessageBeep(MB_ICONEXCLAMATION);
// Sleep(1000);
// MessageBeep(MB_ICONHAND);
// Sleep(1000);
// MessageBeep(MB_ICONQUESTION);
// Sleep(1000);
// MessageBeep(MB_OK);
// Sleep(1000);
